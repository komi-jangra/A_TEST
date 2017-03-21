/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2005 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *
 * CONTRACT: INTERNAL
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:35  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:10  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.2  2006/07/13 05:35:47  sjaddu
 * LOG: Fixed the copy to user problem (badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2006/07/04 12:27:39  gdevanand
 * LOG: Combined driver for MTP and LAPD (Badri)
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: lapd-ifc_minor.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"
                                                                                       
/*
 * Credit where credit is due.  Most of this came from reading Alan
 * Cox's softdog module.  It's nice and small, it does timers, it does
 * fops, it slices, it dices, it juliennes.
 *
 * Pretty good to use for a role model.  Pretty much in all senses of the
 * phrase.
 */
#include <linux/module.h>
#include <linux/config.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/smp_lock.h>
#include <linux/interrupt.h>
#include <linux/poll.h>
#include <linux/init.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <asm/cpm2_mcc.h>

#include <lapd_intern.h>

#define MAX_LAPD_NODES 128

extern mcc_run_t *mcc;

extern unsigned short Lbuf_cnt;

/*
 * Minor number is MCC channel number / 2, and vice versa.
 * Array access to channel is MCC channel number - MCC base channel number / 2
 */
#define LCHAN(c, m)   (((c) - (m)->config.base_chan) / 2)
#define MINOROF(c)    ((c) / 2)
#define CHANOF(m)     ((m) * 2)

#define LCI_CH_IFC(lci) (lci>>8 & 0xFF)

extern int is_ctl_device_inuse(void);
extern int is_ctl_device_configured(void);
extern int is_ctl_device_cup_loaded(void);
extern void inc_ctl_device(void);
extern void set_minor_pd(struct file *fil, void *pd);
extern void* get_minor_pd(struct file *fil);

extern short mapPChanToMCC(short ifc, short chan);
extern short mapMCCToPChan(short mcc, short ch_type);

/*
 * Per instance structure
 * NOTES:
 * o Unfortunately we have some concurrent timers
 */
static struct lapd_device
{
    /* OS stuff */
    struct semaphore       mutex;
    atomic_t               in_use;
    wait_queue_head_t      rx;
    u32                    lci_chantype;
    struct tasklet_struct  task;

    LAPD_TRx               lapdQ;
}
lapd_devices[MAX_LAPD_NODES];

/*
 * prototypes
 */
static int lapd_open(struct inode *inode, struct file *file);
static int lapd_release(struct inode *inode, struct file *file);
static ssize_t lapd_read(struct file *file, char *buf,
                         size_t len, loff_t *ppos);
static ssize_t lapd_write(struct file *file, const char *data,
                          size_t len, loff_t *ppos);
static unsigned int lapd_poll(struct file *file, poll_table *wait);

struct file_operations lapd_fops =
{
    owner:    THIS_MODULE,
    llseek:   no_llseek,
    read:     lapd_read,
    write:    lapd_write,
    poll:     lapd_poll,
    open:     lapd_open,
    release:  lapd_release
};


static int 
lapd_open(struct inode *inode, struct file *file)
{
    int minor = MINOR(inode->i_rdev);
    struct lapd_device *ldev;

    if (!is_ctl_device_inuse())
    {
        inc_ctl_device();
        return -EBUSY;
    }

    if (!is_ctl_device_configured() ||
        !is_ctl_device_cup_loaded())
    {
        inc_ctl_device();
        return -EAGAIN;
    }

    inc_ctl_device();

    /* Check minor numbers */
    if (minor < 0 || minor > MAX_LAPD_NODES)
    {
        atomic_inc(&ldev->in_use);
        return -EINVAL;
    }

    ldev = &lapd_devices[minor];

    if (!atomic_dec_and_test(&ldev->in_use))
    {
        atomic_inc(&ldev->in_use);
        return -EBUSY;
    }

    set_minor_pd(file, ldev);

    /* Enable if we use tasklets */

    return 0;
}

static int 
lapd_release(struct inode *inode, struct file *file)
{
    struct lapd_device *ldev = get_minor_pd(file);
    int    minor = MINOR(inode->i_rdev);

    mcc_stop_channel_tx(mcc, CHANOF(minor));
    mcc_stop_channel_rx(mcc, CHANOF(minor));

    /* TODO: Send any L4 indications if ncecessary */
    atomic_inc(&ldev->in_use);

    return 0;
}

static ssize_t 
lapd_read(struct file *file, char *buf, size_t len, loff_t *ppos)
{
    struct lapd_device *ldev = get_minor_pd(file);
    LAPD_QEntry        sig;
    volatile int       ret; /* no optimization please... */

    printk("lapd_read: begin.\n");

    if (down_interruptible(&ldev->mutex))
    {
        printk("down_interruptible: failed.\n");
        return -ERESTARTSYS;
    }

    sig.elem.size = sizeof(LAPD_QEntry);

    ret = arrayq_get(&ldev->lapdQ.rq, ldev->lapdQ.rqData, &sig.elem);
printk("lapd_read: ret = %d \n", ret);
    while (!ret)
    {
        up(&ldev->mutex);

        wait_event_interruptible(ldev->rx,
                                 !(ret = arrayq_get(&ldev->lapdQ.rq,
                                                    ldev->lapdQ.rqData, 
                                                    &sig.elem)));
        printk("\n\nREAD LAPD: ret = %d ...\n\n\n", ret);
        /* Must satisfy the normal release */
        if (down_interruptible(&ldev->mutex))
        {
            return -ERESTARTSYS;
        }
    }

    //if (copy_to_user(buf, &sig.data.ce_l4, sizeof(struct put_rqst)))

    if (copy_to_user(buf, &sig.data.ce_l4.command, sizeof(struct l4_ce_l3_msg))) // badri
    {
        up(&ldev->mutex);

        printk("failed to get data from user land.\n");
        return -EFAULT;
    }

    /* if there is a Tsl3 Indirect Parameter Block (IPB), copy it too */
    if (sig.data.ce_l4.datalen)
    {
        copy_to_user(buf+sizeof(struct l4_ce_l3_msg),
                     sig.data.ce_l4.msg_data, sig.data.ce_l4.datalen);
    }

    up(&ldev->mutex);

    printk("lapd_read: done.\n");

    return (sizeof(struct l4_ce_l3_msg) + sig.data.ce_l4.datalen);
}

static ssize_t 
lapd_write(struct file *file, const char *buffer, size_t len, loff_t *ppos)
{
    struct lapd_device   *ldev = get_minor_pd(file);
    struct req_data_xfer txmsg;
    struct l4_ce_l3_msg  *l4_ce_ptr;
    unsigned short       buf_hole_len;
    unsigned short       nleft = len;

    if (down_interruptible(&ldev->mutex))
    {
        printk("down_interruptible: failed.\n");
        return -ERESTARTSYS;
    }

    if (len > (sizeof(struct req_data_xfer) + SYSBUFSIZ))
    {
        printk("length is more than specified size.\n");
        up(&ldev->mutex);
        return -EPROTO;
    }

    /* TODO: clean up this code. */
    if (copy_from_user(&txmsg, buffer, 
                       sizeof(struct req_data_xfer)))
    {
        return -EFAULT;
    }

    nleft -= sizeof(struct req_data_xfer);

    l4_ce_ptr = (struct l4_ce_l3_msg *)txmsg.l4_ce_ptr;

    if(txmsg.datalen > 0)
    {
        /*
         *  Create a buf to copy the data to coming from the app, copy
         *  the data and assign the buffer to the message
         */
        if(getbuf(SYSBUFSIZ, &l4_ce_ptr->dataptr, &l4_ce_ptr->refnum) < 0)
        {
            printk("write_func_tsi ! No buffer allocation !");

            up(&ldev->mutex);

            return -ENOMEM;
        }

        /* for N_DATA_RQ, make room for protocol header bytes */
        if(l4_ce_ptr->primcode == N_DATA_RQ)
        {
            buf_hole_len = HDRSSIZE;
        }
        else
        {
            buf_hole_len = 0;
        }

        l4_ce_ptr->dataptr += buf_hole_len;

#if defined(DEBUG_UK_INTERFACE)
        printk("Source data\n");
        for(i = 0, j = 0;i < txmsg.datalen;i++)
        {
            printk("%x ",*(srcbuf + i));
            if(j++ >= 20)
            {
                printk("\n");
                j = 0;
            }
        }
#endif
        if (copy_from_user(l4_ce_ptr->dataptr, 
                           txmsg.tsl3_ipb_ptr, txmsg.datalen))
        {
            up(&ldev->mutex);

            return -EFAULT;
        }

        nleft -= txmsg.datalen;
    }

    l4_ceproc(l4_ce_ptr, 0);   /* call main L4->CE msg processing ******/

    if(l4_ce_ptr->primcode == N_CONN_RQ)
    {
        put_user(l4_ce_ptr->connid, txmsg.connid);
    }

#if 0
    /* TODO: Should this be in ctl device????? 
     *       Need to give deep thoughts....
     */
    /* Count number of CUP_PARMS loads and continue suspended TsL3 init
     * with up() when CUP_PARMS for all interfaces have been downloaded.
     */
    if(Cup_parm_load_cnt >= 0)
    {
        if(Cup_parm_load_cnt == (NUM_IFC - 1))
        {
             if(Logdebug)
                 log_msg("*** CUP_PARMS received for all (NUM_IFC) interfaces");
             Cup_parm_load_cnt = -1;
        }
        else
            Cup_parm_load_cnt++;
    }
#endif

    up(&ldev->mutex);

    printk("lapd_write: done.\n");
    return len;
}

static unsigned int 
lapd_poll(struct file *file, poll_table *wait)
{
    struct lapd_device *ldev = get_minor_pd(file);
    unsigned int       mask = 0;

    if (down_interruptible(&ldev->mutex))
    {
        return -ERESTARTSYS;
    }

    poll_wait(file, &ldev->rx, wait);

    if (!arrayq_empty(&ldev->lapdQ.rq))
    {
        mask |= POLLIN | POLLRDNORM;
    }

    /* 
     * From tslink3.h file the LBUFLEN size is SYSBUFSIZ
     * which is what we are requesting for user data.
     *
     * if (Sbug_cnt < MAXSBUFCNT ||
     *   Mbuf_cnt < MAXMBUFCNT ||
     *   Lbuf_cnt < MAXLBUFCNT)
     *
     * TODO: The Lbuf_cnt count is global and is incremented everytime
     *       getbuf is invoked. Need to check for the race conditions
     *  There is no wait queue indication so write indications are
     *  not blocked...at least for now. 
     */
    if (Lbuf_cnt < MAXLBUFCNT)
    {
        /* We have write bufs */
        mask |= POLLOUT | POLLWRNORM; 
    }

    up(&ldev->mutex);

    return mask;
}

/* Init channel for LAPD */ 
int lapd_init(int chan)
{
    int minor = MINOROF(chan);
    struct lapd_device *ldev = &lapd_devices[minor];

    printk("minor of chan = %d chan = %d\n", minor, chan);

    init_MUTEX(&ldev->mutex);

    atomic_set(&ldev->in_use, 1);

    if (minor < MAX_LAPD_NODES)
    {
        if ( (ldev->lci_chantype = mapMCCToPChan(chan, DCH_PCHAN)) 
              == -1)
        {
            return -1;
        }
    }

    init_waitqueue_head(&ldev->rx);

    arrayq_init(&ldev->lapdQ.rq, LAPD_SIGNAL_QUEUE_EXP,
                sizeof(LAPD_QEntry));

    /* Send power on signal */

    return 0;
}

#if !defined TELESOFT_PROC_DD
/*
 * Telesoft ce_l4el_snd() function is not needed if we
 * use intellinet dd interface.
 */
void
ce_l4el_snd(struct l4_ce_l3_msg *l4_ce_l3_ptr)
{
    int                pchan;
    struct lapd_device *ldev;
    LAPD_QEntry        sig;
    struct put_rqst    *msg;

    sig.elem.size = sizeof(struct put_rqst); /*sizeof(LAPD_QEntry);*/

    msg = &sig.data.ce_l4;

    pchan = mapPChanToMCC(LCI_CH_IFC(l4_ce_l3_ptr->lci_chantype),
                          DCH_PCHAN);

    printk("pchan = %d lchan = %d \n", pchan, MINOROF(pchan));

    ldev = &lapd_devices[MINOROF(pchan)];

    memcpy(msg->command, l4_ce_l3_ptr, 
           sizeof(struct l4_ce_l3_msg));

    if ( (msg->datalen = l4_ce_l3_ptr->datalen))
    {
        memcpy(msg->msg_data, l4_ce_l3_ptr->dataptr,
               l4_ce_l3_ptr->datalen);

        freebuf(l4_ce_l3_ptr->refnum, 0xddaa);	
    }

    if (down_interruptible(&ldev->mutex))
    {	
        return;
    }

    if (!arrayq_put(&ldev->lapdQ.rq, ldev->lapdQ.rqData,
                    &sig.elem))
    {
        printk("Failed to put element in RxQ.\n");
    }

    wake_up_interruptible(&ldev->rx);

    up(&ldev->mutex);
}
#endif
void
lapd_write_complete(int chan)
{
}
extern void
lldHdlcDispatch(int chan, int type, void *data, unsigned short len);

void
lapd_read_complete(int chan, volatile mcc_channel_bd_t *bd)
{
    struct lapd_device *ldev;
    int minor = MINOROF(chan);

    if (minor < MAX_LAPD_NODES)
    {
        ldev = &lapd_devices[minor];
    }
    else
    {
        printk("lapd_read_complete: Invalid minor number.\n");
        return;
    }

    if (bd->length > 2)
    {
        lldHdlcDispatch(ldev->lci_chantype,
                        PH_DA_IN,
                        (void *)__va(bd->buffer),
                        bd->length - 2);
    }
}


void
lapd_on_signal(int chan, u32 signal)
{
}

int
lapd_load_cup_parms(char *args)
{
    struct req_data_xfer cupdata; 
    struct l4_ce_l3_msg  *l4_ce_ptr;

    printk("11111111111111111111111111\n");
    if (!access_ok(VERIFY_READ, args, sizeof(struct req_data_xfer)))
    {
        printk("Access verification failed.\n");
        return -EFAULT;
    }

    if (copy_from_user(&cupdata, args, sizeof(cupdata)))
    {
        printk("Failed after validation...!\n");
        return -EFAULT;
    }

    printk("222222222222222222222\n");
    l4_ce_ptr = (struct l4_ce_l3_msg *)cupdata.l4_ce_ptr;

    if (cupdata.datalen)
    {
        if (getbuf(SYSBUFSIZ, &l4_ce_ptr->dataptr, &l4_ce_ptr->refnum) < 0)
        {
            printk("Failed to get buffer.\n");
            return -ENOMEM;
        }

        if (copy_from_user(l4_ce_ptr->dataptr, cupdata.tsl3_ipb_ptr,
                           cupdata.datalen))
        {
            printk("Failed to get cupdata params.\n");
            return -EFAULT;
        }

        /*
         * wait_for_L4_sem is waiting for l4 to send all cup params
         * for each interface in init_module();
         * Need to remove above wait.
         */
        l4_ceproc(l4_ce_ptr, 0);
    }

    return 0;
}

int
get_lap_ifc_num(int mcc_ch)
{
    struct lapd_device *ldev;
    int minor = MINOROF(mcc_ch);

    if (minor < MAX_LAPD_NODES)
    {
        ldev = &lapd_devices[minor];
        return ((ldev->lci_chantype >> 8) & 0xFF);
    }

    return -1;
}
