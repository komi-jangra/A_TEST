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
 * LOG: Revision 1.1.2.2  2006/07/18 15:21:33  sjaddu
 * LOG: MTP2 : 2 link alignment changes
 * LOG:
 * LOG: Revision 1.1.2.1  2006/07/04 12:27:39  gdevanand
 * LOG: Combined driver for MTP and LAPD (Badri)
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: mtp2-ifc_minor.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

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

#include <mtp2_intern.h>

extern mcc_run_t *mcc;

extern int   is_ctl_device_inuse(void);
extern int   is_ctl_device_configured(void);
extern void  inc_ctl_device(void);
extern void  set_minor_pd(struct file *fil, void *pd);
extern void* get_minor_pd(struct file *fil);
extern void mcc_enable_ints(mcc_run_t *mcc, u32 mch, u16 bits);

/* Device testing */
/* #define TEST_DEV */

/*
 * Minor number is MCC channel number / 2, and vice versa.
 * Array access to channel is MCC channel number - MCC base channel number / 2
 */
#define LCHAN(c, m)   (((c) - (m)->config.base_chan) / 2)
#define MINOROF(c)    ((c) / 2)
#define CHANOF(m)     ((m) * 2)

/*
 * identify a timeout
 */
#define MAKE_TIMER_DATA(l,t) \
    (((l) << 16) | (t))

#define TIMER_DATA_LINK(d) \
    ((d) >> 16)

#define TIMER_DATA_TIMER(d) \
    ((d) & 0x0000FFFFU)

#define MAX_MTP2_NODES 128

/*
 * Per instance structure
 * NOTES:
 * o Unfortunately we have some concurrent timers
 */
static struct mtp2_device
{
    /* OS stuff */
    struct semaphore       mutex;
    atomic_t               in_use;
    wait_queue_head_t      rx;
    wait_queue_head_t      tx;

    struct tasklet_struct  task;
    struct timer_list      t1;
    struct timer_list      t2;
    struct timer_list      t3;
    struct timer_list      t4;
    struct timer_list      t5;
    struct timer_list      t6;
    struct timer_list      t7;

    /* Link state */
    MTP2_LinkState         link;
}
mtp2_devices[MAX_MTP2_NODES];

/*
 * Our timer handler
 */
static void mtp2_fire(unsigned long);

/*
 * prototypes
 */
static int mtp2_open(struct inode *inode, struct file *file);
static int mtp2_release(struct inode *inode, struct file *file);
static ssize_t mtp2_read(struct file *file, char *buf,
                         size_t len, loff_t *ppos);
static ssize_t mtp2_write(struct file *file, const char *data,
                          size_t len, loff_t *ppos);
static unsigned int mtp2_poll(struct file *file, poll_table *wait);
static void mtp2_run(unsigned long data);

struct file_operations mtp2_fops =
{
    owner:    THIS_MODULE,
    llseek:   no_llseek,
    read:     mtp2_read,
    write:    mtp2_write,
    poll:     mtp2_poll,
    open:     mtp2_open,
    release:  mtp2_release
};

int mtp2_init(int chan)
{
    MTP2_QEntry sig;
    int minor = MINOROF(chan);

    if (minor < MAX_MTP2_NODES)
    {
        struct mtp2_device *mtp2 = &mtp2_devices[minor];

        /* Synchronization */
        init_MUTEX(&mtp2->mutex);

        /* atomic */
        atomic_set(&mtp2->in_use, 1);

        /* waiting */
        init_waitqueue_head(&mtp2->rx);
        init_waitqueue_head(&mtp2->tx);

        /*
         * The tasklet.  MTP2 runs mostly here.  Scheduled by interrupts,
         * write, and timeouts.
         */
        tasklet_init(&mtp2->task, mtp2_run, (unsigned long)mtp2);
        tasklet_disable(&mtp2->task);

        /* Our timers */
        init_timer(&mtp2->t1);
        mtp2->t1.data = MAKE_TIMER_DATA(minor, MTP2_T1);
        mtp2->t1.function = mtp2_fire;
        init_timer(&mtp2->t2);
        mtp2->t2.data = MAKE_TIMER_DATA(minor, MTP2_T2);
        mtp2->t2.function = mtp2_fire;
        init_timer(&mtp2->t3);
        mtp2->t3.data = MAKE_TIMER_DATA(minor, MTP2_T3);
        mtp2->t3.function = mtp2_fire;
        init_timer(&mtp2->t4);
        mtp2->t4.data = MAKE_TIMER_DATA(minor, MTP2_T4);
        mtp2->t4.function = mtp2_fire;
        init_timer(&mtp2->t5);
        mtp2->t5.data = MAKE_TIMER_DATA(minor, MTP2_T5);
        mtp2->t5.function = mtp2_fire;
        init_timer(&mtp2->t6);
        mtp2->t6.data = MAKE_TIMER_DATA(minor, MTP2_T6);
        mtp2->t6.function = mtp2_fire;
        init_timer(&mtp2->t7);
        mtp2->t7.data = MAKE_TIMER_DATA(minor, MTP2_T7);
        mtp2->t7.function = mtp2_fire;

        /*
         * The OS independent code needs to call into the dependent stuff,
         * and vice versa.  The OS independent stuff doesn't know about
         * the device data structure.  Saving the index there allows
         * the container to be recovered in these functions.
         */
        mtp2->link.linkNum = minor;

        /* queues */
        arrayq_init(&mtp2->link.rq, MTP2_SIGNAL_QUEUE_EXP,
                    sizeof(MTP2_QEntry));
        arrayq_init(&mtp2->link.tq, MTP2_SIGNAL_QUEUE_EXP,
                    sizeof(MTP2_QEntry));
        arrayq_init(&mtp2->link.rtb, MTP2_SIGNAL_QUEUE_EXP - 2,
                    sizeof(MTP2_QEntry));
        arrayq_init(&mtp2->link.tb, MTP2_SIGNAL_QUEUE_EXP - 1,
                    sizeof(MTP2_QEntry));

        /* Queue (1) start signal */
        sig.signal.signal = MTP2_QUEUED_TRIG;
        sig.signal.linkSet = MGMT_LSC_TRIGGER_PowerOn;
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        QueueIncoming(&mtp2->link, &sig);
    }
    else
    {
        return -ENODEV;
    }
    return 0;
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Handle timer expiration
 *
 *  Input Parameters:
 *      data - encoded timer id and link number
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
static void
mtp2_fire(unsigned long data)
{
    struct mtp2_device *mtp2 = &mtp2_devices[TIMER_DATA_LINK(data)];
    MTP2_QEntry sig;

    /* Build the signal */
    sig.elem.size = MTP2_FIXED_HDR_SIZE;
    sig.signal.signal = TIMER_DATA_TIMER(data);

    /* Dispatch appropriate timer to link */
    QueueIncoming(&mtp2->link, &sig);

    /* Remember: interrupts, writes, and timers */
    tasklet_schedule(&mtp2->task);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Handle device open
 *
 *  Input Parameters:
 *      inode - the device inode
 *      file  - this file
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      0 on successful release, < 0 otherwise
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
static int
mtp2_open(struct inode *inode, struct file *file)
{
    int minor = MINOR(inode->i_rdev);
    struct mtp2_device *mtp2;

    /*
     * If we haven't been configured, forget it.
     */
    if (!is_ctl_device_inuse())
    {
        inc_ctl_device();
        return -EBUSY;
    }

    if (!is_ctl_device_configured())
    {
        inc_ctl_device();
        return -EAGAIN;
    }

    inc_ctl_device();

    /*
     * Avoid illegal accesses
     */
    if (minor < 0 || minor > MAX_MTP2_NODES)
    {
        return -EINVAL;
    }

    /*
     * Ensure an open on a configured channel
     */
    if (!mcc->channels[LCHAN(CHANOF(minor), mcc)].valid)
    {
        return -EINVAL;
    }

    mtp2 = &mtp2_devices[minor];

    /*
     * We are a single open device.  If you need multiple accessors, use
     * threads.
     */
    if (!atomic_dec_and_test(&mtp2->in_use))
    {
        atomic_inc(&mtp2->in_use);

        return -EBUSY;
    }

    /* default timer values */
    mtp2->link.configData.T1 = 40000;  /* Assume 64Kbps */
    mtp2->link.configData.T2 = 100000; /* Assume not terminal allocation */
    mtp2->link.configData.T3 = 2000;
    mtp2->link.configData.T4 = 8200;
    mtp2->link.configData.T5 = 120;
    mtp2->link.configData.T6 = 4500;   /* Assume 64Kbps */
    mtp2->link.configData.T7 = 2000;

    /* Can't forget these */
    mtp2->link.iacInfo.Pn = 8200;      /* Assume 64Kbps */
    mtp2->link.iacInfo.Pe = 500;       /* Assume 64Kbps */

    /* AERM too */
    mtp2->link.aermInfo.Tin = 4;
    mtp2->link.aermInfo.Tie = 1;

    mcc_start_channel_tx(mcc, CHANOF(minor));
    mcc_start_channel_rx(mcc, CHANOF(minor));

    /* Enable SS7 interrupts */
    mcc_enable_ints(mcc, CHANOF(minor), MCC_INTMASK_FISU);

    /* enable the tasklet for processing */
    tasklet_enable(&mtp2->task);

    /* faster access */
    set_minor_pd(file, mtp2);
    /*file->private_data = mtp2;*/

    /* schedule the tasklet */
    tasklet_schedule(&mtp2->task);

    return 0;
}

static void
mtp2_stop_timers(struct mtp2_device *mtp2)
{
    if (mtp2)
    {
        if (timer_pending(&mtp2->t1))
        {
            del_timer_sync(&mtp2->t1);
        }

        if (timer_pending(&mtp2->t2))
        {
            del_timer_sync(&mtp2->t2);
        }

        if (timer_pending(&mtp2->t3))
        {
            del_timer_sync(&mtp2->t3);
        }

        if (timer_pending(&mtp2->t4))
        {
            del_timer_sync(&mtp2->t4);
        }

        if (timer_pending(&mtp2->t5))
        {
            del_timer_sync(&mtp2->t5);
        }

        if (timer_pending(&mtp2->t6))
        {
            del_timer_sync(&mtp2->t6);
        }

        if (timer_pending(&mtp2->t7))
        {
            del_timer_sync(&mtp2->t7);
        }
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      release for an MTP2 device
 *
 *  Input Parameters:
 *      inode - the device inode
 *      file  - this file
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      0 on successful release, < 0 otherwise
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
static int
mtp2_release(struct inode *inode, struct file *file)
{
    int minor = MINOR(inode->i_rdev), ret;
    struct mtp2_device *mtp2 = get_minor_pd(file);
    MTP2_LinkState *link = &mtp2->link;
    MTP2_QEntry sig;

    printk("mtp2_release: begin\n");
    if (down_interruptible(&mtp2->mutex))
    {
        return -ERESTARTSYS;
    }

    /* Don't need these anymore */
    mtp2_stop_timers(mtp2);

    /* Probably need to change this to a buffering call */
    sig.signal.signal = MTP2_QUEUED_TRIG;
    sig.signal.linkSet = MGMT_LSC_TRIGGER_L3_Failure;
    sig.elem.size = MTP2_FIXED_HDR_SIZE;
    QueueIncoming(&mtp2->link, &sig);

    /* Run the last trigger */
    ret = arrayq_empty(&link->tq);
    while (!ret)
    {
        up(&mtp2->mutex);

        tasklet_schedule(&mtp2->task);

        /* This will be signalled after the above has run */
        wait_event_interruptible(mtp2->tx,
                                 !(ret = arrayq_empty(&link->tq)));

        if (down_interruptible(&mtp2->mutex))
        {
            return -ERESTARTSYS;
        }
    }

    /* Don't clobber selectors */
    wake_up_interruptible(&mtp2->tx);
    wake_up_interruptible(&mtp2->rx);

    /* Disable SS7 interrupts */
    mcc_disable_ints(mcc, CHANOF(minor), MCC_INTMASK_FISU);

    /* disable the task, so we don't fill the queue with garbage */
    tasklet_disable(&mtp2->task);

    /* release the hounds */
    up(&mtp2->mutex);

    /* reenable access */
    atomic_inc(&mtp2->in_use);

    printk("mtp2_release: end.\n");

    return 0;
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      implement read for an MTP2 device
 *
 *  Input Parameters:
 *      file - kernel file representation for this device
 *      data - data to write
 *      len  - sizeof data
 *      ppos - position to write
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      Number of bytes read
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
static ssize_t
mtp2_read(struct file *file, char *buf, size_t len, loff_t *ppos)
{
    struct mtp2_device *mtp2 = get_minor_pd(file);
    MTP2_LinkState *link = &mtp2->link;
    MTP2_QEntry sig;
    volatile int ret;

    /*
     * Paranoid.  I suppose it is possible to have two threads perform
     * a read, though.
     */
    if (down_interruptible(&mtp2->mutex))
    {
        return -ERESTARTSYS;
    }

    /*
     * Make sure the buffer is big enough for the worst case.
     * We do this first, rather than check to see if the buffer is just
     * bigger than the next signal, because we don't have a way to
     * requeue the signal, and dropping it would be "a bad thing".
     */
    if (!access_ok(VERIFY_WRITE, buf, sizeof(MTP2_Signal)))
    {
        up(&mtp2->mutex);

        return -EFAULT;
    }

    /*
     * Fairly simple, but it's surprising how much you do have to do.
     */
    sig.elem.size = sizeof(MTP2_QEntry);
    ret = arrayq_get(&link->rq, link->rqData, &sig.elem);
    while (!ret)
    {
        /* Release mutex */
        up(&mtp2->mutex);

        /* Check for no sleeping allowed */
        if (file->f_flags & O_NONBLOCK)
        {
            return -EAGAIN;
        }

        /*
         * I'm being tricky here.  Conditions to wait_event() & friends
         * are not supposed to have side effects.  Obviously, arrayq_get()
         * does.  There are two things that save me:
         *  o as long as arrayq_get() fails, it has no side effects on the
         *    queue
         *  o when it succeeds, the condition is satisfied.  The get is
         *    atomic wrt the queue (and in addition, happends inside a
         *    spinlock)
         */
        wait_event_interruptible(mtp2->rx,
                                 !(ret = arrayq_get(&link->rq,
                                                    link->rqData, &sig.elem)));

        /* Must satisfy the normal release */
        if (down_interruptible(&mtp2->mutex))
        {
            return -ERESTARTSYS;
        }
    }

    /* Got one now, give it to the user */
    copy_to_user(buf, &sig.signal, sig.elem.size);

    /* release the hounds */
    up(&mtp2->mutex);

    return (ssize_t)sig.elem.size;
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      implement write() for an MTP2 device
 *
 *  Input Parameters:
 *      file - kernel file representation for this device
 *      data - data to write
 *      len  - sizeof data
 *      ppos - position to write
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      Number of bytes written
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
static ssize_t
mtp2_write(struct file *file, const char *data, size_t len, loff_t *ppos)
{
    struct mtp2_device *mtp2 = get_minor_pd(file);
    MTP2_LinkState *link = &mtp2->link;
    MTP2_QEntry sig;
    int ret;

    /*
     * Paranoid.  I suppose it is possible to have two threads perform
     * a write, though.
     */
    if (down_interruptible(&mtp2->mutex))
    {
        return -ERESTARTSYS;
    }

    /*
     * Make sure they follow the API
     */
    if (len > sizeof(MTP2_Signal))
    {
        up(&mtp2->mutex);

        return -EPROTO;
    }

    /*
     * Transfer their signal to the pending queue
     */
    sig.elem.size = len;
    if (copy_from_user(&sig.signal.signal, data, len))
    {
        printk("mtp2_write: %s:%d \n", __FILE__, __LINE__);
        up(&mtp2->mutex);

        return -EFAULT;
    }

    /*
     * send to L3
     */
    ret = L3_Buffer(link, &sig);

    while (ret == -ENOMEM)
    {
        /* Can't go to sleep holding this */
        up(&mtp2->mutex);

        /* Check for no sleeping allowed */
        if (file->f_flags & O_NONBLOCK)
        {
            return -EAGAIN;
        }

        /*
         * Pretty much the same arguments as the ones for read's condition
         * above apply here.
         */
        wait_event_interruptible(mtp2->tx,
                                 ((ret = L3_Buffer(link, &sig)) == -ENOMEM));

        if (down_interruptible(&mtp2->mutex))
        {
            return -ERESTARTSYS;
        }
    }

    /* release the hounds */
    up(&mtp2->mutex);

    /* Writes, timers, and interrupts schedule work */
    if (ret == sig.elem.size)
    {
        tasklet_schedule(&mtp2->task);
    }

    return (ssize_t)sig.elem.size;
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      implement poll() for an MTP2 device
 *
 *  Input Parameters:
 *      file - kernel file representation for this device
 *      wait - the poll table
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      bitmask of operations possible
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
static unsigned int
mtp2_poll(struct file *file, poll_table *wait)
{
    struct mtp2_device *mtp2 = get_minor_pd(file);
    unsigned int mask = 0;

    /*
     * This is actually not 100% safe in a multithreaded environment,
     * due to the possibility of an interrupt changing the ability of
     * the user to write.  The possibility is small, however, and not
     * fatal in any sense; the writer may block for a short while, but
     * it shouldn't be long.  If this is unwanted, then the user can
     * say O_NONBLOCK and get EAGAIN out of the write.
     *
     * I'm not sure how other drivers handle this possibility.
     */
    if (down_interruptible(&mtp2->mutex))
    {
        return -ERESTARTSYS;
    }

    poll_wait(file, &mtp2->tx, wait);
    poll_wait(file, &mtp2->rx, wait);

    /*
     * This is the icky bit.  Read actually should be fine,  write
     * mostly should be but no guarantees
     */
    if (!arrayq_empty(&mtp2->link.rq))
    {
        mask |= POLLIN | POLLRDNORM; /* something to read */
    }
    if (!arrayq_full(&mtp2->link.tq))
    {
        mask |= POLLOUT | POLLWRNORM; /* write space available */
    }

    /* Let 'er rip */
    up(&mtp2->mutex);

    return mask;
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      The meat and potatoes routine.  MTP2 mostly runs here
 *
 *  Input Parameters:
 *      data - a pointer to this device
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      jiffy increment.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
static void
mtp2_run(unsigned long data)
{
    struct mtp2_device *mtp2 = (struct mtp2_device *)data;
    MTP2_QEntry signal;

    /* Dispatch pending signals */
    signal.elem.size = sizeof(MTP2_QEntry);
    while (arrayq_get(&mtp2->link.tq, mtp2->link.tqData, &signal.elem))
    {
        L3_Dispatch(&mtp2->link, &signal);
    }

    /* awaken any writers pending */
    wake_up_interruptible(&mtp2->tx);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Handle notification of write complete.
 *
 *  Input Parameters:
 *      chan - the MCC channel the write is completing on
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
mtp2_write_complete(int chan)
{
#if !defined(TEST_DEV)
    struct mtp2_device *mtp2 = &mtp2_devices[MINOROF(chan)];
#if 0
    MTP2_QEntry sig;

    sig.signal.signal = MTP2_QUEUED_TRIG;
    sig.elem.size = MTP2_FIXED_HDR_SIZE;
    sig.signal.linkSet = DAEDT_TXC_TRIGGER_TransmissionRequest;
    QueueIncoming(&mtp2->link, &sig);
#endif

    tasklet_schedule(&mtp2->task);
#else
    testwrite++;
#endif
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Handle notification of read complete.
 *
 *  Input Parameters:
 *      chan - the MCC channel the write is completing on
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
mtp2_read_complete(int chan, volatile mcc_channel_bd_t *bd)
{
#if !defined(TEST_DEV)
    struct mtp2_device *mtp2 = &mtp2_devices[MINOROF(chan)];
    MTP2_QEntry sig;

    if (bd->length >= 2) /* Trim CRC */
    {
        sig.signal.signal = MTP2_QUEUED_TRIG;
        sig.signal.linkSet = L1_DAEDR_TRIGGER_SignalUnit;
        sig.elem.size = MTP2_FIXED_HDR_SIZE + bd->length - 2;
        memcpy(sig.signal.data.sif, __va(bd->buffer), bd->length - 2);
        QueueIncoming(&mtp2->link, &sig);

        sig.signal.signal = MTP2_QUEUED_TRIG;
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.linkSet = DAEDT_TXC_TRIGGER_TransmissionRequest;
        QueueIncoming(&mtp2->link, &sig);

        tasklet_schedule(&mtp2->task);
    }
#else
    memcpy(testbuf, __va(bd->buffer), bd->length);
    testbuf[bd->length] = 0;
    testlen = bd->length;
    teststat = bd->status;
#endif
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Handle notification of a signal
 *
 *  Input Parameters:
 *      chan - the MCC channel the write is completing on
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
mtp2_on_signal(int chan, u32 signal)
{
#if !defined(TEST_DEV)
    struct mtp2_device *mtp2 = &mtp2_devices[MINOROF(chan)];
    MTP2_QEntry sig;

    sig.signal.signal = MTP2_QUEUED_TRIG;
    sig.elem.size = MTP2_FIXED_HDR_SIZE;

    switch (signal)
    {
    case MCC_ICTE_OCT:
        sig.signal.linkSet = L1_DAEDR_TRIGGER_OctetCountingMode;
        QueueIncoming(&mtp2->link, &sig);
        break;

    case MCC_ICTE_RSVD1: /* No signal for CRC error, use reserved */
        sig.signal.linkSet = L1_DAEDR_TRIGGER_BadCheckSum;
        QueueIncoming(&mtp2->link, &sig);
        break;

    case MCC_ICTE_SUERM:
        sig.signal.linkSet = SUERM_LSC_TRIGGER_LinkFailure;
        QueueIncoming(&mtp2->link, &sig);
        break;

    case MCC_ICTE_AERM:
        sig.signal.linkSet = AERM_IAC_TRIGGER_AbortProving;
        QueueIncoming(&mtp2->link, &sig);
        break;

    case MCC_ICTE_IDLE:
        //printk("IDLE interrupt\n");
        break;
    case MCC_ICTE_NID:
        //printk("NID interrupt\n");
        break;
    case MCC_ICTE_FISU:
        /* printk("FISU interrupt\n"); */
        break;
    default:
        break;
    }

    tasklet_schedule(&mtp2->task);
#else
    lastsig = signal;
#endif
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Determine if this link has gone congested
 *
 *  Input Parameters:
 *      link    - the link to act on
 *      array   - the array to check for fullness
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
static int
MTP2Congested(MTP2_LinkState *link, arrayq_t *q)
{
#if 0
    /* FIXME: This probably wants to move to FLOW_CONTROL */
    RC_Main(link, MGMT_RC_TRIGGER_CongestionDiscard, NULL, 0);
#define L2_L3_CONGESTION_ONSET          (0x4D)
#define L2_L3_CONGESTION_ABATES         (0x4E)
    MGMT_RC_TRIGGER_CongestionAccept,         /* MGMT->RC      */
    MGMT_RC_TRIGGER_CongestionDiscard,        /* MGMT->RC      */
    MGMT_RC_TRIGGER_NoCongestion,             /* MGMT->RC      */
#endif
    return 0;
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Queue a message for transmission
 *
 *  Input Parameters:
 *      link    - the link to act on
 *      signal  - signal to queue
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
QueueOutgoing(MTP2_LinkState *link, MTP2_QEntry *signal)
{
    struct mtp2_device *mtp2 = &mtp2_devices[link->linkNum];

    /* Determine if we are congested */
    MTP2Congested(link, &link->rq);

    /* We have something for the user */
    arrayq_put(&link->rq, link->rqData, &signal->elem);

    /* We have something.  Maybe awaken a sleeper */
    wake_up_interruptible(&mtp2->rx);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Queue a signal for the user
 *
 *  Input Parameters:
 *      link    - the link to act on
 *      trigger - the event that's happening
 *      data    - buffer
 *      len     - sizeof buffer
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
int
QueueIncoming(MTP2_LinkState *link, MTP2_QEntry *sig)
{
    /* May send a signal */
    MTP2Congested(link, &link->tq);

    if (!arrayq_put(&link->tq, link->tqData, &sig->elem))
    {
        return -ENOMEM;
    }

    return sig->elem.size;
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Compute when a timer should expire
 *
 *  Input Parameters:
 *      msec - how far in the future to expire, milliseconds
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      jiffy increment.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
static unsigned long
CalcJiffies(ITS_UINT msec)
{
    struct timespec ts;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    return timespec_to_jiffies(&ts);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Handle timer trigger
 *
 *  Input Parameters:
 *      link    - the link to act on
 *      trigger - the event that's happening
 *      data    - buffer
 *      len     - sizeof buffer
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
TIMER_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
           ITS_OCTET *data, ITS_USHORT size)
{
    struct mtp2_device *mtp2 = &mtp2_devices[link->linkNum];

#if defined(DEBUG_TRIGGERS)
    printk("TIMER_Main: trigger %s\n", MTP2_TriggerToString(trigger));
#endif
    switch (trigger)
    {
    case TIMER_TRIGGER_StartT1:
        mtp2->t1.expires = jiffies + CalcJiffies(link->configData.T1);
        add_timer(&mtp2->t1);
        break;

    case TIMER_TRIGGER_StopT1:
        if (timer_pending(&mtp2->t1))
        {
            del_timer(&mtp2->t1);
        }
        break;

    case TIMER_TRIGGER_StartT2:
        mtp2->t2.expires = jiffies + CalcJiffies(link->configData.T2);
        add_timer(&mtp2->t2);
        break;

    case TIMER_TRIGGER_StopT2:
        if (timer_pending(&mtp2->t2))
        {
            del_timer(&mtp2->t2);
        }
        break;

    case TIMER_TRIGGER_StartT3:
        mtp2->t3.expires = jiffies + CalcJiffies(link->configData.T3);
        add_timer(&mtp2->t3);
        break;

    case TIMER_TRIGGER_StopT3:
        if (timer_pending(&mtp2->t3))
        {
            del_timer(&mtp2->t3);
        }
        break;

    case TIMER_TRIGGER_StartT4:
        mtp2->t4.expires = jiffies + CalcJiffies(link->configData.T4);
        add_timer(&mtp2->t4);
        break;

    case TIMER_TRIGGER_StopT4:
        if (timer_pending(&mtp2->t4))
        {
            del_timer(&mtp2->t4);
        }
        break;

    case TIMER_TRIGGER_StartT5:
        mtp2->t5.expires = jiffies + CalcJiffies(link->configData.T5);
        add_timer(&mtp2->t5);
        break;

    case TIMER_TRIGGER_StopT5:
        if (timer_pending(&mtp2->t5))
        {
            del_timer(&mtp2->t5);
        }
        break;

    case TIMER_TRIGGER_StartT6:
        mtp2->t6.expires = jiffies + CalcJiffies(link->configData.T6);
        add_timer(&mtp2->t6);
        break;

    case TIMER_TRIGGER_StopT6:
        if (timer_pending(&mtp2->t6))
        {
            del_timer(&mtp2->t6);
        }
        break;

    case TIMER_TRIGGER_StartT7:
        mtp2->t7.expires = jiffies + CalcJiffies(link->configData.T7);
        add_timer(&mtp2->t7);
        break;

    case TIMER_TRIGGER_StopT7:
        if (timer_pending(&mtp2->t7))
        {
            del_timer(&mtp2->t7);
        }
        break;

    default:
        break;
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      L1 entry point
 *
 *  Input Parameters:
 *      link    - the link to act on
 *      trigger - the event that's happening
 *      data    - buffer
 *      len     - sizeof buffer
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
L1_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
        ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("L1_Main: trigger %s\n", MTP2_TriggerToString(trigger));
#endif
    switch (trigger)
    {
    case DAEDT_L1_TRIGGER_BitsForTransmission:
        mcc_send_data(mcc, CHANOF(link->linkNum), data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for L1\n",
                    trigger);
        break;
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Handle timer trigger
 *
 *  Input Parameters:
 *      level  - the level to act on
 *      format - the event that's happening
 *      args   - args
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
MTP2_Trace(MTP2_LinkState *link, int level, const char *format, ...)
{
    MTP2_QEntry sig;
    va_list alist;

    if (!link->traceData.traceOnOff[level])
    {
        return;
    }

    va_start(alist, format);

    sig.elem.size = MTP2_MAX_DRIVER_BYTES;
    sig.signal.signal = L2_L3_TRACE_DATA;
    sig.signal.data.sif[0] = level;
    vsnprintf(&sig.signal.data.sif[1], MTP2_MAX_DRIVER_BYTES - 1,
              format, alist);

    va_end(alist);

#if APP_DEBUG_TRACE 
    QueueOutgoing(link, &sig);
#elif DEBUG_PRINT_ENABLED
    printk("%s", &sig.signal.data.sif[1]);
#endif
}

static const char *triggerNames[] =
{
    "MGMT_LSC_TRIGGER_PowerOn",
    "MGMT_LSC_TRIGGER_L3_Failure",
    "MGMT_LSC_TRIGGER_LocalProcessorOutage",
    "MGMT_LSC_TRIGGER_LocalProcessorRecovered",
    "MGMT_RC_TRIGGER_CongestionAccept",
    "MGMT_RC_TRIGGER_CongestionDiscard",
    "MGMT_RC_TRIGGER_NoCongestion",
    "L1_DAEDR_TRIGGER_BadCheckSum",
    "L1_DAEDR_TRIGGER_OctetCountingMode",
    "L1_DAEDR_TRIGGER_16_Octets",
    "L1_DAEDR_TRIGGER_SignalUnit",
    "L3_LSC_TRIGGER_Start",
    "L3_LSC_TRIGGER_Stop",
    "L3_LSC_TRIGGER_Continue",
    "L3_LSC_TRIGGER_RetrieveBSNT",
    "L3_LSC_TRIGGER_RetrievalFSNC",
    "L3_LSC_TRIGGER_Emergency",
    "L3_LSC_TRIGGER_EmergencyEnd",
    "L3_LSC_TRIGGER_LocalProcessorRecovered",
    "L3_LSC_TRIGGER_FlushBuffers",
    "L3_TXC_TRIGGER_MessageForTransmission",
    "LSC_L3_TRIGGER_InService",
    "LSC_L3_TRIGGER_OutOfService",
    "LSC_L3_TRIGGER_Stop",
    "LSC_L3_TRIGGER_RemoteProcessorOutage",
    "LSC_L3_TRIGGER_RemoteProcessorRecovered",
    "LSC_IAC_TRIGGER_Start",
    "LSC_IAC_TRIGGER_Stop",
    "LSC_IAC_TRIGGER_Emergency",
    "LSC_POC_TRIGGER_Stop",
    "LSC_POC_TRIGGER_LocalProcessorOutage",
    "LSC_POC_TRIGGER_LocalProcessorRecovered",
    "LSC_POC_TRIGGER_RemoteProcessorOutage",
    "LSC_POC_TRIGGER_RemoteProcessorRecovered",
    "LSC_POC_TRIGGER_NoProcessorOutage",
    "LSC_TXC_TRIGGER_Start",
    "LSC_TXC_TRIGGER_Stop",
    "LSC_TXC_TRIGGER_RetrievalFSNC",
    "LSC_TXC_TRIGGER_SendSIOS",
    "LSC_TXC_TRIGGER_SendFISU",
    "LSC_TXC_TRIGGER_SendSIPO",
    "LSC_TXC_TRIGGER_SendMSU",
    "LSC_TXC_TRIGGER_FlushBuffers",
    "LSC_RC_TRIGGER_Start",
    "LSC_RC_TRIGGER_Stop",
    "LSC_RC_TRIGGER_RetrieveBSNT",
    "LSC_RC_TRIGGER_RetrieveFSNX",
    "LSC_RC_TRIGGER_AcceptMSUOrFISU",
    "LSC_RC_TRIGGER_RejectMSUOrFISU",
    "LSC_AERM_TRIGGER_SetTiToTin",
    "LSC_SUERM_TRIGGER_Start",
    "LSC_SUERM_TRIGGER_Stop",
    "IAC_LSC_TRIGGER_AlignmentComplete",
    "IAC_LSC_TRIGGER_AlignmentNotPossible",
    "IAC_TXC_TRIGGER_SendSIO",
    "IAC_TXC_TRIGGER_SendSIN",
    "IAC_TXC_TRIGGER_SendSIE",
    "IAC_AERM_TRIGGER_Start",
    "IAC_AERM_TRIGGER_Stop",
    "IAC_AERM_TRIGGER_SetTiToTin",
    "IAC_AERM_TRIGGER_SetTiToTie",
    "POC_LSC_TRIGGER_NoProcessorOutage",
    "DAEDR_IAC_TRIGGER_CorrectSU",
    "DAEDR_RC_TRIGGER_SignalUnit",
    "DAEDR_SUERM_TRIGGER_SUInError",
    "DAEDR_SUERM_TRIGGER_CorrectSU",
    "DAEDR_AERM_TRIGGER_SUInError",
    "DAEDR_L1_TRIGGER_Start",
    "DAEDT_TXC_TRIGGER_TransmissionRequest",
    "DAEDT_L1_TRIGGER_BitsForTransmission",
    "TXC_L3_TRIGGER_RetrievedMessage",
    "TXC_L3_TRIGGER_RetrievalNotPossible",
    "TXC_L3_TRIGGER_RetrievalComplete",
    "TXC_L3_TRIGGER_RTBCleared",
    "TXC_LSC_TRIGGER_LinkFailure",
    "TXC_DAEDT_TRIGGER_Start",
    "TXC_DAEDT_TRIGGER_SignalUnit",
    "TXC_RC_TRIGGER_FSNTValue",
    "RC_L3_TRIGGER_ReceivedMessage",
    "RC_L3_TRIGGER_BSNT",
    "RC_L3_TRIGGER_BSNTNotRetrievable",
    "RC_L3_TRIGGER_RBCleared",
    "RC_LSC_TRIGGER_LinkFailure",
    "RC_LSC_TRIGGER_ReceiveSIO",
    "RC_LSC_TRIGGER_ReceiveSIN",
    "RC_LSC_TRIGGER_ReceiveSIE",
    "RC_LSC_TRIGGER_ReceiveSIOS",
    "RC_LSC_TRIGGER_ReceiveSIPO",
    "RC_LSC_TRIGGER_ReceiveMSUOrFISU",
    "RC_IAC_TRIGGER_ReceiveSIO",
    "RC_IAC_TRIGGER_ReceiveSIN",
    "RC_IAC_TRIGGER_ReceiveSIE",
    "RC_IAC_TRIGGER_ReceiveSIOS",
    "RC_DAEDR_TRIGGER_Start",
    "RC_TXC_TRIGGER_NACKToBeSent",
    "RC_TXC_TRIGGER_SIBReceived",
    "RC_TXC_TRIGGER_BSNRAndBIBR",
    "RC_TXC_TRIGGER_FSNXValue",
    "RC_CC_TRIGGER_Normal",
    "RC_CC_TRIGGER_Busy",
    "AERM_IAC_TRIGGER_AbortProving",
    "SUERM_LSC_TRIGGER_LinkFailure",
    "CC_TXC_TRIGGER_SendSIB",
    "TIMER_TRIGGER_StartT1",
    "TIMER_TRIGGER_StopT1",
    "TIMER_TRIGGER_T1Expired",
    "TIMER_TRIGGER_StartT2",
    "TIMER_TRIGGER_StopT2",
    "TIMER_TRIGGER_T2Expired",
    "TIMER_TRIGGER_StartT3",
    "TIMER_TRIGGER_StopT3",
    "TIMER_TRIGGER_T3Expired",
    "TIMER_TRIGGER_StartT4",
    "TIMER_TRIGGER_StopT4",
    "TIMER_TRIGGER_T4Expired",
    "TIMER_TRIGGER_StartT5",
    "TIMER_TRIGGER_StopT5",
    "TIMER_TRIGGER_T5Expired",
    "TIMER_TRIGGER_StartT6",
    "TIMER_TRIGGER_StopT6",
    "TIMER_TRIGGER_T6Expired",
    "TIMER_TRIGGER_StartT7",
    "TIMER_TRIGGER_StopT7",
    "TIMER_TRIGGER_T7Expired",
    "(bad trigger)"
};

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Convert a trigger to a string
 *
 *  Input Parameters:
 *      trigger  - the trigger to act on
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
const char *
MTP2_TriggerToString(MTP2_Trigger trigger)
{
    if (trigger < MGMT_LSC_TRIGGER_PowerOn || trigger > TIMER_TRIGGER_T7Expired)
    {
        return "Invalid trigger";
    }

    return triggerNames[trigger];
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Turn hardware AERM on or off
 *
 *  Input Parameters:
 *      link  - the link to act on
 *      onOff - turn AERM on or off
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
MTP2_ToggleAERM(MTP2_LinkState *link, int onOff)
{
    if (onOff)
    {
        mcc_enable_ints(mcc, CHANOF(link->linkNum), MCC_INTMASK_AERM);
    }
    else
    {
        mcc_disable_ints(mcc, CHANOF(link->linkNum), MCC_INTMASK_AERM);
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Turn hardware SUERM on or off
 *
 *  Input Parameters:
 *      link  - the link to act on
 *      onOff - turn SUERM on or off
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
MTP2_ToggleSUERM(MTP2_LinkState *link, int onOff)
{
    if (onOff)
    {
        mcc_enable_ints(mcc, CHANOF(link->linkNum), MCC_INTMASK_SUERM);
    }
    else
    {
        mcc_disable_ints(mcc, CHANOF(link->linkNum), MCC_INTMASK_SUERM);
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Turn hardware OCM on or off
 *
 *  Input Parameters:
 *      link  - the link to act on
 *      onOff - turn OCM on or off
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
MTP2_ToggleOCM(MTP2_LinkState *link, int onOff)
{
    if (onOff)
    {
        mcc_enable_ints(mcc, CHANOF(link->linkNum), MCC_INTMASK_OCT);
    }
    else
    {
        mcc_disable_ints(mcc, CHANOF(link->linkNum), MCC_INTMASK_OCT);
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Reset the FISU filter
 *
 *  Input Parameters:
 *      link  - the link to act on
 *
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *      None.
 *  
 *  Notes:
 *  
 *  See Also:
 *
 ************************************************************************/
void
MTP2_ResetFISUFilter(MTP2_LinkState *link)
{
    mcc_reset_filter(mcc, CHANOF(link->linkNum));
}

