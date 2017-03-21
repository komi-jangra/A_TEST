/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
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
 * LOG: Revision 1.1.2.6  2006/07/18 15:21:33  sjaddu
 * LOG: MTP2 : 2 link alignment changes
 * LOG:
 * LOG: Revision 1.1.2.5  2006/07/04 12:21:52  gdevanand
 * LOG: Combined driver for MTP and LAPD (Badri)
 * LOG:
 * LOG: Revision 1.1.2.4  2006/06/14 13:22:18  gdevanand
 * LOG: Test
 * LOG:
 * LOG: Revision 1.1.2.3  2006/03/16 21:23:50  lbana
 * LOG: added register dump functions and also added channel
 * LOG: programming for mcc2.
 * LOG:
 * LOG: Revision 1.1.2.2  2005/09/19 18:10:56  lbana
 * LOG: got correct fix from Mitch on oops at extra base ptr. xtrabase
 * LOG: and sctpbase are shorts and the bug was in getting right offset.
 * LOG:
 * LOG:
 *
 ****************************************************************************/
/*
 * CPM2 MCC device control
 * Copyright (c) 2005 Mitch Miers (mmiers@cfl.rr.com)
 */

/*
 * We need the memory map here
 */
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/stddef.h>

#include <asm/cpm2.h>
#include <asm/immap_cpm2.h>
#include <asm/cpm2_si.h>
#include <asm/cpm2_mcc.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/mpc85xx.h>
#include <asm/page.h>
#include <asm/hw_irq.h>

#include <its.h>
#include <itu/mtp2.h>

#ident "$Id: mcc.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

#define MCC_XTRA_OFF    0
#define MCC_XTRA_SIZE   2048
#define MCC1_SCTP_OFF   MCC_XTRA_SIZE
#define MCC2_SCTP_OFF   (MCC_XTRA_SIZE + 256)
#define MCC_SCTP_SIZE   512

static cpm2_map_t *cpm2_immr = NULL;
static cpm_cpm2_t *cpmp = NULL;

/* Memory barrier on PPC */
extern void eieio(void);

/*
 * When a channel number is passed in or out, it is implicitly
 * assumed that the number represents a physical channel number.
 * This means that the channel number will have to be normalized
 * to the relevent MCC (subtract base_chan), and for SS7 divided
 * by two to get the channel struct offset.
 */
#define LCHAN(c,m)  (((c) - (m)->config.base_chan) / 2)

/*
 * For development purposes (when attempting loopback on the CPM
 * connector).  So far, we didn't get it to work.
 */
#define DEV_ASSUMPTIONS 0

/********************************** DEBUG SECTION ************************/
static void
dump_io_pports(volatile iop_cpm2_t *iop)
{
    printk("IO-PORTA:\n");
    printk("pdira    = 0x%08x\n", iop->iop_pdira);
    printk("ppara    = 0x%08x\n", iop->iop_ppara);
    printk("psora    = 0x%08x\n", iop->iop_psora);
    printk("podra    = 0x%08x\n", iop->iop_podra);
    printk("pdata    = 0x%08x\n", iop->iop_pdata);

    printk("IO-PORTB:\n");
    printk("pdirb    = 0x%08x\n", iop->iop_pdirb);
    printk("pparb    = 0x%08x\n", iop->iop_pparb);
    printk("psorb    = 0x%08x\n", iop->iop_psorb);
    printk("podrb    = 0x%08x\n", iop->iop_podrb);
    printk("pdatb    = 0x%08x\n", iop->iop_pdatb);

    printk("IO-PORTC:\n");
    printk("pdirc    = 0x%08x\n", iop->iop_pdirc);
    printk("pparc    = 0x%08x\n", iop->iop_pparc);
    printk("psorc    = 0x%08x\n", iop->iop_psorc);
    printk("podrc    = 0x%08x\n", iop->iop_podrc);
    printk("pdatc    = 0x%08x\n", iop->iop_pdatc);

    printk("IO-PORTD:\n");
    printk("pdird    = 0x%08x\n", iop->iop_pdird);
    printk("ppard    = 0x%08x\n", iop->iop_ppard);
    printk("psord    = 0x%08x\n", iop->iop_psord);
    printk("podrd    = 0x%08x\n", iop->iop_podrd);
    printk("pdatd    = 0x%08x\n", iop->iop_pdatd);
}

/*
 * Dump the MCC parameters.
 */
void
dump_mcc(mcc_run_t *mcc_config)
{
    volatile mcc_global_param_t *mcc_params = mcc_config->mcc_params;

    printk("MCC: runtime setup: mcc at address %p, offset %08x\n",
           mcc_params, (u32)mcc_params - (u32)cpm2_immr->im_dprambase);
    printk("MCC: regs at address %p, offset %08x\n",
           mcc_config->mcc_regs,
           (u32)mcc_config->mcc_regs - (u32)cpm2_immr->im_dprambase);
    printk("MCC: regs contents: mccf %02x mccm %04x\n",
           mcc_config->mcc_regs->mcc_mccf, mcc_config->mcc_regs->mcc_mccm);
    printk("   mccbase   : %08x\n", mcc_params->mccbase);
    printk("   mccstate  : %04x\n", mcc_params->mccstate);
    printk("   mrblr     : %04x\n", mcc_params->mrblr);
    printk("   grfthr    : %04x\n", mcc_params->grfthr);
    printk("   grfcnt    : %04x\n", mcc_params->grfcnt);
    printk("   rinttmp   : %08x\n", mcc_params->rinttmp);
    printk("   data0     : %08x\n", mcc_params->data0);
    printk("   data1     : %08x\n", mcc_params->data1);
    printk("   tintbase  : %08x\n", mcc_params->tintbase);
    printk("   tintptr   : %08x\n", mcc_params->tintptr);
    printk("   tinttmp   : %08x\n", mcc_params->tinttmp);
    printk("   sctpbase  : %04x\n", mcc_params->sctpbase);
    printk("   c_mask32  : %08x\n", mcc_params->c_mask32);
    printk("   xtrabase  : %04x\n", mcc_params->xtrabase);
    printk("   c_mask16  : %04x\n", mcc_params->c_mask16);
    printk("   rinttmp0  : %08x\n", mcc_params->rinttmp0);
    printk("   rinttmp1  : %08x\n", mcc_params->rinttmp1);
    printk("   rinttmp2  : %08x\n", mcc_params->rinttmp2);
    printk("   rinttmp3  : %08x\n", mcc_params->rinttmp3);
    printk("   rintbase0 : %08x\n", mcc_params->rintbase0);
    printk("   rintptr0  : %08x\n", mcc_params->rintptr0);
    printk("   rintbase1 : %08x\n", mcc_params->rintbase1);
    printk("   rintptr1  : %08x\n", mcc_params->rintptr1);
    printk("   rintbase2 : %08x\n", mcc_params->rintbase2);
    printk("   rintptr2  : %08x\n", mcc_params->rintptr2);
    printk("   rintbase3 : %08x\n", mcc_params->rintbase3);
    printk("   rintptr3  : %08x\n", mcc_params->rintptr3);

    printk("MCC: config data at address %p\n", mcc_config);
    printk("   dpbase   : %08x\n", mcc_config->config.dpbase);
    printk("   bdbase   : %08x\n", mcc_config->config.bdbase);
    printk("   intbase  : %08x\n", mcc_config->config.intbase);
    printk("   intsize  : %08x\n", mcc_config->config.intsize);
    printk("   bufbase  : %08x\n", mcc_config->config.bufbase);
    printk("   sctpbase : %04x\n", mcc_config->config.sctpbase);
    printk("   xtrabase : %04x\n", mcc_config->config.xtrabase);
    printk("   bds_per  : %04x\n", mcc_config->config.bds_per);
    printk("\n");
}

static void
dump_inttbl(mcc_run_t *mcc)
{
    unsigned i, nents;
    u32 *ints;

    ints = (u32 *)mcc->config.intbase;
    nents = mcc->config.intsize / sizeof(mcc_interrupt_table_entry_t);
    printk("Interrupt tables\n");
    printk("     TX        RX0       RX1       RX2       RX3\n");
    for (i = 0; i < nents; i++)
    {
        printk("%3d  %08x %08x %08x %08x %08x\n",
               i,
               ints[i],
               ints[nents + i],
               ints[nents * 2 + i],
               ints[nents * 3 + i],
               ints[nents * 4 + i]);
    }
}

static void
dump_siram_ctl(volatile siramctl_t *sir)
{
    printk("Register :Addr        :     value\n");
    printk("SI_AMR   :0x%p      :0x%04x\n", &sir->si_amr, sir->si_amr);
    printk("SI_BMR   :0x%p      :0x%04x\n", &sir->si_bmr, sir->si_bmr);
    printk("SI_CMR   :0x%p      :0x%04x\n", &sir->si_cmr, sir->si_cmr);
    printk("SI_DMR   :0x%p      :0x%04x\n", &sir->si_dmr, sir->si_dmr);
    printk("SI_GMR   :0x%p      :0x%02x\n", &sir->si_gmr, sir->si_gmr);
    printk("SI_CMDR  :0x%p      :0x%02x\n", &sir->si_cmdr, sir->si_cmdr);
    printk("SI_STR   :0x%p      :0x%02x\n", &sir->si_str, sir->si_str);
    printk("SI_RSR   :0x%p      :0x%04x\n", &sir->si_rsr, sir->si_rsr);

    return;
}

static void
dump_siram(mcc_run_t *mcc)
{
    unsigned i;

    printk("SIRAM: Tx        Rx\n");
    for (i = 0; i < 256; i++)
    {
        printk("%3d    %04x      %04x\n", i, mcc->sitxram[i], mcc->sirxram[i]);
    }
}

void
dump_mcc_channel_ss7(mcc_run_t *mcc, int channel, mcc_channel_run_t *chan)
{
    volatile mcc_channel_specific_ss7_t *ss7 = chan->type.ss7;

    printk("MCC: SS7 channel %d at address %p offset %08x\n",
           channel, ss7, (u32)ss7 - (u32)cpm2_immr + 0x80000);
    printk("    tstate  : %08x\n", ss7->tstate);
    printk("    zistate : %08x\n", ss7->zistate);
    printk("    zidata0 : %08x\n", ss7->zidata0);
    printk("    zidata1 : %08x\n", ss7->zidata1);
    printk("    tbdflags: %04x\n", ss7->tbdflags);
    printk("    tbdcnt  : %04x\n", ss7->tbdcnt);
    printk("    tbdptr  : %08x\n", ss7->tbdptr);
    printk("    echamr  : %08x\n", ss7->echamr);
    printk("    tcrc    : %08x\n", ss7->tcrc);
    printk("    rstate  : %08x\n", ss7->rstate);
    printk("    zdstate : %08x\n", ss7->zdstate);
    printk("    zddata0 : %08x\n", ss7->zddata0);
    printk("    zddata1 : %08x\n", ss7->zddata1);
    printk("    rbdflags: %04x\n", ss7->rbdflags);
    printk("    rbdcnt  : %04x\n", ss7->rbdcnt);
    printk("    dbdptr  : %08x\n", ss7->rbdptr);
    printk("    mflr    : %04x\n", ss7->mflr);
    printk("    max_cnt : %04x\n", ss7->max_cnt);
    printk("    rcrc    : %04x\n", ss7->rcrc);
    printk("    n       : %04x\n", ss7->familydata.ansi_itu.n);
    printk("    n_cnt   : %04x\n", ss7->familydata.ansi_itu.n_cnt);
    printk("    d       : %04x\n", ss7->familydata.ansi_itu.d);
    printk("    d_cnt   : %04x\n", ss7->familydata.ansi_itu.d_cnt);
    printk("    mask1   : %08x\n", ss7->mask1);
    printk("    mask2   : %04x\n", ss7->mask2);
    printk("    ss7_opt : %04x\n", ss7->ss7_opt);
    printk("    lrb1_tmp: %08x\n", ss7->lrb1_tmp);
    printk("    lrb2_tmp: %04x\n", ss7->lrb2_tmp);
    printk("    suerm   : %04x\n", ss7->suerm);
    printk("    lrb1    : %08x\n", ss7->lrb1);
    printk("    lrb2    : %04x\n", ss7->lrb2);
    printk("    t       : %04x\n", ss7->t);
    printk("    lhdr    : %08x\n", ss7->lhdr);
    printk("    lhdr_tmp: %08x\n", ss7->lhdr_tmp);
    printk("    efsuc   : %08x\n", ss7->efsuc);
    printk("    suec    : %08x\n", ss7->suec);
    printk("    ss7state: %08x\n", ss7->ss7state);
    printk("    tmpstmp : %08x\n", ss7->tmpstmp);
    printk("    delay   : %04x\n", ss7->delay);
    printk("    m       : %04x\n", ss7->m);
    printk("    m_cnt   : %04x\n", ss7->m_cnt);
}

static void
dump_mcc_channel_hdlc(mcc_run_t *mcc, int channel, mcc_channel_run_t *chan)
{
    volatile mcc_channel_specific_hdlc_t *hdlc = chan->type.hdlc;

    printk("MCC: HDLC channel %d at address %p offset %08x\n",
           channel, hdlc, (u32)hdlc - (u32)cpm2_immr->im_dprambase);
    printk("    tstate  : %08x\n", hdlc->tstate);
    printk("    zistate : %08x\n", hdlc->zistate);
    printk("    zidata0 : %08x\n", hdlc->zidata0);
    printk("    zidata1 : %08x\n", hdlc->zidata1);
    printk("    tbdflags: %04x\n", hdlc->tbdflags);
    printk("    tbdcnt  : %04x\n", hdlc->tbdcnt);
    printk("    tbdptr  : %08x\n", hdlc->tbdptr);
    printk("    intmask : %04x\n", hdlc->intmask);
    printk("    chamr   : %04x\n", hdlc->chamr);
    printk("    tcrc    : %08x\n", hdlc->tcrc);
    printk("    rstate  : %08x\n", hdlc->rstate);
    printk("    zdstate : %08x\n", hdlc->zdstate);
    printk("    zddata0 : %08x\n", hdlc->zddata0);
    printk("    zddata1 : %08x\n", hdlc->zddata1);
    printk("    rbdflags: %04x\n", hdlc->rbdflags);
    printk("    rbdcnt  : %04x\n", hdlc->rbdcnt);
    printk("    rbdptr  : %08x\n", hdlc->rbdptr);
    printk("    mflr    : %04x\n", hdlc->mflr);
    printk("    maxcnt  : %04x\n", hdlc->maxcnt);
    printk("    rcrc    : %08x\n", hdlc->rcrc);
}

static void
dump_mcc_channel_transparent(mcc_run_t *mcc, int channel, mcc_channel_run_t *chan)
{
    volatile mcc_channel_specific_transparent_t *trans = chan->type.transparent;

    printk("MCC: transparent channel %d at address %p offset %08x\n",
           channel, trans, (u32)trans - (u32)cpm2_immr->im_dprambase);
    printk("    tstate  : %08x\n", trans->tstate);
    printk("    zistate : %08x\n", trans->zistate);
    printk("    zidata0 : %08x\n", trans->zidata0);
    printk("    zidata1 : %08x\n", trans->zidata1);
    printk("    tbdflags: %04x\n", trans->tbdflags);
    printk("    tbdcnt  : %04x\n", trans->tbdcnt);
    printk("    tbdptr  : %04x\n", trans->tbdptr);
    printk("    intmask : %04x\n", trans->intmask);
    printk("    chamr   : %04x\n", trans->chamr);
    printk("    rsvrd   : %08x\n", trans->reserved);
    printk("    rstate  : %08x\n", trans->rstate);
    printk("    zdstate : %08x\n", trans->zdstate);
    printk("    zddata0 : %08x\n", trans->zddata0);
    printk("    zddata1 : %08x\n", trans->zddata1);
    printk("    rbdflags: %04x\n", trans->rbdflags);
    printk("    rbdcnt  : %04x\n", trans->rbdcnt);
    printk("    rbdptr  : %04x\n", trans->rbdptr);
    printk("    tmrblr  : %04x\n", trans->tmrblr);
    printk("    rcvsync : %04x\n", trans->rcvsync);
    printk("    rsvrd1  : %08x\n", trans->reserved1);
}

static void
dump_mcc_channel_extra(mcc_run_t *mcc, int channel, mcc_channel_run_t *chan)
{
    int i;

    printk("MCC channel extra run data: %p\n", chan);
    printk("   extra    : %p, offset %08x\n",
           chan->extra, (u32)chan->extra - (u32)cpm2_immr + 0x80000);
    printk("   extra    : tbase %04x tptr %04x rbase %04x rptr %04x\n",
           chan->extra->tbase, chan->extra->tptr,
           chan->extra->rbase, chan->extra->rptr);
    printk("   rxbase   : %p, offset %08x\n",
           chan->rxbase, (u32)chan->rxbase - mcc->config.bdbase);
    printk("   rx       : %p, offset from base %08x\n",
           chan->rx, (u32)(chan->rx - chan->rxbase));
    for (i = 0; i < mcc->config.bds_per; i++)
    {
        printk("      bd %d : status %04x length %d buffer %p, offset %08x\n",
               i, chan->rxbase[i].status, chan->rxbase[i].length,
               chan->rxbase[i].buffer,
               (u32)(chan->rxbase[i].buffer - __pa(mcc->config.bufbase)));
    }
    printk("   txbase   : %p, offset %08x\n",
           chan->txbase, (u32)chan->txbase - mcc->config.bdbase);
    printk("   tx       : %p, offset from base %08x\n",
           chan->tx, (u32)(chan->tx - chan->txbase));
    for (i = 0; i < mcc->config.bds_per; i++)
    {
        printk("      bd %d : status %04x length %d buffer %p, offset %08x\n",
               i, chan->txbase[i].status, chan->txbase[i].length,
               chan->txbase[i].buffer,
               (u32)(chan->txbase[i].buffer - __pa(mcc->config.bufbase)));
    }

    printk("    stats    : read %d write %d\n",
           chan->stats->rxFrames, chan->stats->txFrames);
    printk("    valid    : %d\n", chan->valid);
    printk("\n");
}

static void
dump_int_cfg(void)
{
    printk("INTERRUPT CONTROLLER:\n");
    printk("sicr %08x siexr %08x\n",
           cpm2_immr->im_intctl.ic_sicr, cpm2_immr->im_intctl.ic_siexr);
    printk("scprr_h %08x scprr_l %08x\n",
           cpm2_immr->im_intctl.ic_scprrh, cpm2_immr->im_intctl.ic_scprrl);
    printk("simr_h %08x simr_l %08x sipnr_h %08x sipnr_l %08x\n",
           cpm2_immr->im_intctl.ic_simrh, cpm2_immr->im_intctl.ic_simrl,
           cpm2_immr->im_intctl.ic_sipnrh, cpm2_immr->im_intctl.ic_sipnrl);
    printk("\n");
}

/*
 * Things nice to know about the current CPM configuration.
 */
static void
dump_cpm(void)
{
    printk("CPM INFO:\n");
    printk("Base structure info\n");
    printk("cpm2_immr: %08x ccsr: %08x\n", (u32)cpm2_immr, (u32)get_ccsrbar());
    printk("\n");
    printk("CP INFORMATION:\n");
    printk("cpcr: %08x (address %p)\n",
           cpmp->cp_cpcr, &cpmp->cp_cpcr);
    printk("rccr: %08x rter: %04x rtmr: %04x rtscr: %04x rtsr: %08x\n",
           cpm2_immr->im_cpm.cp_rccr, cpm2_immr->im_cpm.cp_rter,
           cpm2_immr->im_cpm.cp_rtmr, cpm2_immr->im_cpm.cp_rtscr,
           cpm2_immr->im_cpm.cp_rtsr);
    printk("\n");
    printk("SYSCONF INFORMATION:\n");
    printk("cear %08x ceer %04x cemr %04x\n",
           cpm2_immr->im_siu_conf.siu_85xx.sc_cear,
           cpm2_immr->im_siu_conf.siu_85xx.sc_ceer,
           cpm2_immr->im_siu_conf.siu_85xx.sc_cemr);
    printk("smaer %08x smevr %08x smctr %08x\n",
           cpm2_immr->im_siu_conf.siu_85xx.sc_smaer,
           cpm2_immr->im_siu_conf.siu_85xx.sc_smevr,
           cpm2_immr->im_siu_conf.siu_85xx.sc_smctr);
    printk("lmaer %08x lmevr %08x lmctr %08x\n",
           cpm2_immr->im_siu_conf.siu_85xx.sc_lmaer,
           cpm2_immr->im_siu_conf.siu_85xx.sc_lmevr,
           cpm2_immr->im_siu_conf.siu_85xx.sc_lmctr);
    printk("\n");
    printk("CMX:\n");
    printk("si1cr = %02x si2cr = %02x\n", 
           cpm2_immr->im_cpmux.cmx_si1cr, cpm2_immr->im_cpmux.cmx_si2cr);
    printk("fcr = %08x scr = %08x smr = %08x uar %04x\n", 
           cpm2_immr->im_cpmux.cmx_fcr,
           cpm2_immr->im_cpmux.cmx_scr,
           cpm2_immr->im_cpmux.cmx_smr,
           cpm2_immr->im_cpmux.cmx_uar);
    printk("\n");
    printk("BRG Informations\n");
    printk("brg1: %08x brg2: %08x brg3: %08x brg4: %08x\n",
           cpm2_immr->im_brgc1, cpm2_immr->im_brgc2,
           cpm2_immr->im_brgc3, cpm2_immr->im_brgc4);
    printk("brg5: %08x brg6: %08x brg7: %08x brg8: %08x\n",
           cpm2_immr->im_brgc5, cpm2_immr->im_brgc6,
           cpm2_immr->im_brgc7, cpm2_immr->im_brgc8);
    printk("\n");
    printk("TIMER Configuration\n");
    printk("tgcr1 %02x tgcr2 %02x\n",
           cpm2_immr->im_cpmtimer.cpmt_tgcr1, cpm2_immr->im_cpmtimer.cpmt_tgcr2);
    printk("tmr1 %04x tmr2 %04x tmr3 %04x tmr4 %04x\n",
           cpm2_immr->im_cpmtimer.cpmt_tmr1, cpm2_immr->im_cpmtimer.cpmt_tmr2,
           cpm2_immr->im_cpmtimer.cpmt_tmr3, cpm2_immr->im_cpmtimer.cpmt_tmr4);
    printk("trr1 %04x trr2 %04x trr3 %04x trr4 %04x\n",
           cpm2_immr->im_cpmtimer.cpmt_trr1, cpm2_immr->im_cpmtimer.cpmt_trr2,
           cpm2_immr->im_cpmtimer.cpmt_trr3, cpm2_immr->im_cpmtimer.cpmt_trr4);
    printk("tcr1 %04x tcr2 %04x tcr3 %04x tcr4 %04x\n",
           cpm2_immr->im_cpmtimer.cpmt_tcr1, cpm2_immr->im_cpmtimer.cpmt_tcr2,
           cpm2_immr->im_cpmtimer.cpmt_tcr3, cpm2_immr->im_cpmtimer.cpmt_tcr4);
    printk("tcn1 %04x tcn2 %04x tcn3 %04x tcn4 %04x\n",
           cpm2_immr->im_cpmtimer.cpmt_tcn1, cpm2_immr->im_cpmtimer.cpmt_tcn2,
           cpm2_immr->im_cpmtimer.cpmt_tcn3, cpm2_immr->im_cpmtimer.cpmt_tcn4);
    printk("ter1 %04x ter2 %04x ter3 %04x ter4 %04x\n",
           cpm2_immr->im_cpmtimer.cpmt_ter1, cpm2_immr->im_cpmtimer.cpmt_ter2,
           cpm2_immr->im_cpmtimer.cpmt_ter3, cpm2_immr->im_cpmtimer.cpmt_ter4);
    printk("\n");
}

void
dump_chans(mcc_run_t *mcc, mcc_chan_config_t *chans, u32 num_chan)
{
    unsigned i;

    for (i = 0; i < num_chan; i++)
    {
        u8 lchan = LCHAN(chans[i].chan, mcc);

        switch (chans[i].mode)
        {
        default:
        case MCC_TYPE_SS7:
            dump_mcc_channel_ss7(mcc, chans[i].chan, &mcc->channels[lchan]);
            break;
        case MCC_TYPE_HDLC:
            dump_mcc_channel_hdlc(mcc, chans[i].chan, &mcc->channels[lchan]);
            break;
        case MCC_TYPE_TRANS:
            dump_mcc_channel_transparent(mcc, chans[i].chan, &mcc->channels[lchan]);
            break;
        }

        dump_mcc_channel_extra(mcc, chans[i].chan, &mcc->channels[lchan]);
    }
}

void
dump_stats(mcc_run_t *mcc)
{
    unsigned i;

    printk("MCC Statistics:\n");
    printk("txintcnt   : %d\n", mcc->stats.txintcnt);
    printk("rxintcnt   : %d\n", mcc->stats.rxintcnt);
    printk("txunderflow: %d\n", mcc->stats.txunderflow);
    printk("rxbusy     : %d\n", mcc->stats.rxbusy);
    printk("mfv        : %d\n", mcc->stats.mfv);
    printk("gov        : %d\n", mcc->stats.gov);
    printk("gun        : %d\n", mcc->stats.gun);
    printk("tint       : %d\n", mcc->stats.tint);
    printk("tqov       : %d\n", mcc->stats.tqov);
    printk("rqov0      : %d\n", mcc->stats.rqov0);
    printk("rint0      : %d\n", mcc->stats.rint0);
    printk("rqov1      : %d\n", mcc->stats.rqov1);
    printk("rint1      : %d\n", mcc->stats.rint1);
    printk("rqov2      : %d\n", mcc->stats.rqov2);
    printk("rint2      : %d\n", mcc->stats.rint2);
    printk("rqov3      : %d\n", mcc->stats.rqov3);
    printk("rint3      : %d\n", mcc->stats.rint3);
    printk("unknown    : %d\n", mcc->stats.unknown);
    for (i = 0; i < MCC_MAX_CHAN_SS7; i++)
    {
        if (mcc->channels[i].valid)
        {
            printk("Channel %d statistics:\n", i * 2);
            printk("length vio : %d\n", mcc->channels[i].stats->rxLengthViolation);
            printk("non aligned: %d\n", mcc->channels[i].stats->rxNonAligned);
            printk("abort      : %d\n", mcc->channels[i].stats->rxAbort);
            printk("CRC error  : %d\n", mcc->channels[i].stats->rxCRCError);
            printk("rx overflow: %d\n", mcc->channels[i].stats->rxOverflow);
            printk("rx frames  : %d\n", mcc->channels[i].stats->rxFrames);
            printk("tx frames  : %d\n", mcc->channels[i].stats->txFrames);
            printk("sig idle   : %d\n", mcc->channels[i].stats->sigIdle);
            printk("sig nonidle: %d\n", mcc->channels[i].stats->sigNonIdle);
            printk("sig AERM   : %d\n", mcc->channels[i].stats->sigAERM);
            printk("sig FISU   : %d\n", mcc->channels[i].stats->sigFISU);
            printk("sig SUERM  : %d\n", mcc->channels[i].stats->sigSUERM);
            printk("sig OCT    : %d\n", mcc->channels[i].stats->sigOCT);
        }
    }
}

void
dump_all(mcc_run_t *mcc)
{
    unsigned i;

    printk("###############################################################\n");
    if (irqs_disabled())
    {
        printk("IRQs are disabled\n");
    }
    else
    {
        printk("IRQs are enabled\n");
    }
    dump_io_pports(&cpm2_immr->im_ioport);
    dump_cpm();
    dump_int_cfg();
    dump_mcc(mcc);
    dump_siram_ctl(mcc->siramctl);
    dump_siram(mcc);
    dump_inttbl(mcc);
    for (i = 0; i < MCC_MAX_CHAN_SS7; i++)
    {
        if (mcc->channels[i].valid)
        {
            dump_mcc_channel_ss7(mcc,
                                 mcc->config.base_chan + i * 2,
                                 &mcc->channels[i]);
            dump_mcc_channel_extra(mcc,
                                   mcc->config.base_chan + i * 2,
                                   &mcc->channels[i]);
        }
    }
}

/********************************** API SECTION ************************/
/*
 * TDMs are disabled
 */
void
mcc_disable_si(mcc_run_t *mcc)
{
    mcc->siramctl->si_gmr = 0;
}

/*
 * TDMs are enabled
 */
void
mcc_enable_si(mcc_run_t *mcc)
{
    /* enable the serial interfaces */
#if DEV_ASSUMPTIONS
    mcc->siramctl->si_gmr = SIGMR_ENA /* | SIGMR_ENB | SIGMR_ENC | SIGMR_END */;
#else
    mcc->siramctl->si_gmr = SIGMR_ENA | SIGMR_ENB| SIGMR_ENC | SIGMR_END;
#endif
}

/*
 * ints to enable
 */
void
mcc_enable_ints(mcc_run_t *mcc, u32 mch, u16 bits)
{
    unsigned lchan = LCHAN(mch, mcc);

    if (mcc->channels[lchan].mode == MCC_TYPE_SS7)
    {
        mcc->channels[lchan].type.ss7->echamr |=
            (bits << MCC_ECHAMR_INTS_SHIFT);
    }
    else
    {
        mcc->channels[lchan].type.hdlc->intmask |= bits;
    }
}

/*
 * ints to disable
 */
void
mcc_disable_ints(mcc_run_t *mcc, u32 mch, u16 bits)
{
    unsigned lchan = LCHAN(mch, mcc);

    if (mcc->channels[lchan].mode == MCC_TYPE_SS7)
    {
        mcc->channels[lchan].type.ss7->echamr &=
            ~(bits << MCC_ECHAMR_INTS_SHIFT);
    }
    else
    {
        mcc->channels[lchan].type.hdlc->intmask &= ~bits;
    }
}

/*
 * Initialize an MCC.  It is the user's responsibility to ensure that
 * the mixture of SS7, HDLC and transparent channels is good.
 */
static void
mcc_init(mcc_run_t *mcc_run,
         volatile mcc_t *mcc,
         volatile mcc_global_param_t *mcc_params,
         volatile siramctl_t *siramctl,
         volatile u16 *siTxRAM, volatile u16 *siRxRAM)
{
    u32 i, j;
    mcc_interrupt_table_entry_t *ptr;

    /*
     * Save off some info for helper routines
     */
    mcc_run->mcc_regs = mcc;
    mcc_run->mcc_params = mcc_params;
    mcc_run->siramctl = siramctl;
    mcc_run->sitxram = siTxRAM;
    mcc_run->sirxram = siRxRAM;

    /* Disconnect the clock and sync signals */
    mcc_disable_si(mcc_run);

    /* Reset the MCC */
    mcc_issue_command(mcc_run, CPM_CR_MCC_RST, mcc_run->config.base_chan);

    /*
     * Initialize the SI registers & RAM.  We assume 4 E1s, directly attached.
     */

    /*
     * Clear the SI1 TX and RX RAM.  We do ALL half words
     */
    for (i = 0; i < MCC_TDMS_PER_MCC; i++)
    {
        for (j = 0; j < MCC_CHANS_PER_TDM_E1; j++)
        {
	    unsigned first32base, second32base;

            first32base = i * 2 * MCC_CHANS_PER_TDM_E1;
            second32base = (i * 2 + 1) * MCC_CHANS_PER_TDM_E1;

            /* Normal */
            siTxRAM[first32base + j] = SIxRAM_BYT_BYTES;
            siRxRAM[first32base + j] = SIxRAM_BYT_BYTES;
            /* Shadow */
            siTxRAM[second32base + j] = SIxRAM_BYT_BYTES;
            siRxRAM[second32base + j] = SIxRAM_BYT_BYTES;

            /* Terminate the TDM groups */
            if ((j + 1) == MCC_CHANS_PER_TDM_E1)
            {
                /* Normal */
                siTxRAM[first32base + j] |= SIxRAM_LST_LAST;
                siRxRAM[first32base + j] |= SIxRAM_LST_LAST;
                /* Shadow */
                siTxRAM[second32base + j] |= SIxRAM_LST_LAST;
                siRxRAM[second32base + j] |= SIxRAM_LST_LAST;
            }
        }
    }

    /*
     * The hardware is going to say how to do this.  For now, assume
     * SAD - as appropriate
     * SDM - normal mode (loopback for testing)
     * RFSD - no bit delay
     * DSC - channel clock = data clock
     * CRT - common pins for Tx/Rx clock and sync
     * SL - sync level active high
     * CE - data received on falling edge, sent on rising
     * FE - frame sync sampled on falling edge
     * GM - FCI/SCIT mode
     * TFD - no bit delay
     */
#if DEV_ASSUMPTIONS
    siramctl->si_amr =
        SIxMR_SAD_1BF32         | SIxMR_SDM_NORMAL   | SIxMR_RFSD_NO_DELAY |
        SIxMR_DSC_EQUAL         | SIxMR_CRT_COMMON   | SIxMR_SL_ON_ONE     |
        SIxMR_CE_DSC0_RISE_FALL | SIxMR_FE_FALL      | SIxMR_GM_GCI_SCIT   |
        SIxMR_TFSD_NO_DELAY;
    siramctl->si_bmr =
        SIxMR_SAD_2BF32         | SIxMR_SDM_NORMAL   | SIxMR_RFSD_NO_DELAY |
        SIxMR_DSC_EQUAL         | SIxMR_CRT_COMMON   | SIxMR_SL_ON_ONE     |
        SIxMR_CE_DSC0_RISE_FALL | SIxMR_FE_FALL      | SIxMR_GM_GCI_SCIT   |
        SIxMR_TFSD_NO_DELAY;
#endif
    siramctl->si_cmr =
        SIxMR_SAD_4BF32         | SIxMR_SDM_NORMAL   | SIxMR_RFSD_NO_DELAY |
        SIxMR_DSC_DOUBLE        | SIxMR_CRT_COMMON   | SIxMR_SL_ON_ZERO    |
        SIxMR_CE_DSC1_FALL_RISE | SIxMR_FE_FALL      | SIxMR_GM_GCI_SCIT   |
        SIxMR_TFSD_NO_DELAY;

    siramctl->si_amr = siramctl->si_bmr = siramctl->si_dmr = 0;
#if DEV_ASSUMPTIONS
    siramctl->si_dmr =
        SIxMR_SAD_4BF32         | SIxMR_SDM_NORMAL   | SIxMR_RFSD_NO_DELAY |
        SIxMR_DSC_EQUAL         | SIxMR_CRT_COMMON   | SIxMR_SL_ON_ONE     |
        SIxMR_CE_DSC0_RISE_FALL | SIxMR_FE_FALL      | SIxMR_GM_GCI_SCIT   |
        SIxMR_TFSD_NO_DELAY;
#endif

    /* Shadow not used, but initialize anyway */
#if DEV_ASSUMPTIONS
    siramctl->si_rsr =
        SIxRSR_SSAD_1BS32 << SIxRSR_SSADA_SHIFT |
        SIxRSR_SSAD_2BS32 << SIxRSR_SSADB_SHIFT |
        SIxRSR_SSAD_3BS32 << SIxRSR_SSADC_SHIFT |
        SIxRSR_SSAD_4BS32 << SIxRSR_SSADD_SHIFT;
#else
    siramctl->si_rsr = 0;
#endif

    /* command register */
    siramctl->si_cmdr = 0;

    /*
     * Initialize the MCC param area
     */
    mcc_params->mccbase   = __pa(mcc_run->config.bdbase);
    mcc_params->mccstate  = 0;
    mcc_params->mrblr     = MTP2_MAX_DRIVER_BYTES;
    mcc_params->grfthr    = 1;
    mcc_params->grfcnt    = mcc_params->grfthr;
    mcc_params->rinttmp   = 0;
    mcc_params->data0     = 0;
    mcc_params->data1     = 0;
    mcc_params->tintbase  = __pa(mcc_run->config.intbase);
    mcc_params->tintptr   = mcc_params->tintbase;
    mcc_params->tinttmp   = 0;
    mcc_params->sctpbase  = mcc_run->config.sctpbase;
    mcc_params->c_mask32  = MASK_32BIT_CRC;
    mcc_params->xtrabase  = mcc_run->config.xtrabase;
    mcc_params->c_mask16  = MASK_16BIT_CRC;
    mcc_params->rinttmp0  = 0;
    mcc_params->rinttmp1  = 0;
    mcc_params->rinttmp2  = 0;
    mcc_params->rinttmp3  = 0;
    mcc_params->rintbase0 = __pa(mcc_run->config.intbase) +
                                mcc_run->config.intsize;
    mcc_params->rintptr0  = mcc_params->rintbase0;
    mcc_params->rintbase1 = mcc_params->rintbase0 + mcc_run->config.intsize;
    mcc_params->rintptr1  = mcc_params->rintbase1;
    mcc_params->rintbase2 = mcc_params->rintbase1 + mcc_run->config.intsize;
    mcc_params->rintptr2  = mcc_params->rintbase2;
    mcc_params->rintbase3 = mcc_params->rintbase2 + mcc_run->config.intsize;
    mcc_params->rintptr3  = mcc_params->rintbase3;

    /*
     * Initialize the interrupt tables
     */
    memset((void *)mcc_run->config.intbase, 0, mcc_run->config.intsize * 5);
    for (i = 1; i <= 5; i++)
    {
        ptr = (mcc_interrupt_table_entry_t *) (mcc_run->config.intbase +
                                               (i * mcc_run->config.intsize) - 
                                               sizeof(u32));
        ptr->status |= MCC_ICTE_W;
    }

    /*
     * Save off some info for the interrupt handler
     */
    mcc_run->stats.txintcnt = 0;
    mcc_run->stats.rxintcnt = 0;
    mcc_run->txints =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->tintbase);
    mcc_run->txintbase =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->tintbase);
    mcc_run->rxints[0] =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->rintbase0);
    mcc_run->rxints[1] =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->rintbase1);
    mcc_run->rxints[2] =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->rintbase2);
    mcc_run->rxints[3] =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->rintbase3);
    mcc_run->rxintbases[0] =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->rintbase0);
    mcc_run->rxintbases[1] =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->rintbase1);
    mcc_run->rxintbases[2] =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->rintbase2);
    mcc_run->rxintbases[3] =
        (mcc_interrupt_table_entry_t *)__va(mcc_params->rintbase3);

    /* Reset the channels.  All of them */
    for (i = 0; i < MCC_TDMS_PER_MCC; i++)
    {
        mcc_issue_command(mcc_run, CPM_CR_INIT_TRX,
                          mcc_run->config.base_chan + i * MCC_CHANS_PER_TDM_E1);
    }

    /*
     * MCC span setup.  All spans are on TDMa.
     */
#if DEV_ASSUMPTIONS
    mcc->mcc_mccf = MCCF_GROUP_TDMa << MCCF_GROUP1_SHIFT |
                    MCCF_GROUP_TDMb << MCCF_GROUP2_SHIFT |
                    MCCF_GROUP_TDMc << MCCF_GROUP3_SHIFT |
                    MCCF_GROUP_TDMd << MCCF_GROUP4_SHIFT;
#else
    mcc->mcc_mccf = MCCF_GROUP_TDMc << MCCF_GROUP3_SHIFT;
#endif

    /* Clear the mask for events for now */
    mcc->mcc_mccm =
        MCCE_RQOV0 | MCCE_RINT0 | MCCE_RQOV1 | MCCE_RINT1 |
        MCCE_RQOV2 | MCCE_RINT2 | MCCE_RQOV3 | MCCE_RINT3 |
        MCCE_TQOV  | MCCE_TINT  | MCCE_GUN   | MCCE_GOV;

    mcc->mcc_mcce = MCCE_CLEAR;
}

/*
 * Program SI RAM.  This works regardless of channel type.
 */
static void
mcc_config_siram(mcc_run_t *mcc,
                 mcc_channel_run_t *channels,
                 mcc_chan_config_t *chans, u32 num_chan)
{
    unsigned i, mchan, idx;
#if DEV_ASSUMPTIONS
    unsigned span, slot;
#endif

    /*
     * Program the SI Tx RAM entries for TDMx
     */
    for (i = 0; i < num_chan; i++)
    {
        mchan = chans[i].chan - mcc->config.base_chan;

        if (mchan >= MCC_MAX_CHAN_NORMAL)
        {
            /* Notify user, just this first time */
            printk("Invalid channel %d in mcc_config_siram\n",
                   chans[i].chan);

            continue;
        }

        if (chans[i].chan_type == MCC_RX)
        {
            continue;
        }

#if DEV_ASSUMPTIONS
        /*
         * For now, use a fixed mapping from mchan to span/slot
         */
        span = mchan / MCC_CHANS_PER_TDM_E1;
        slot = mchan % MCC_CHANS_PER_TDM_E1;
        idx = span * 2 * MCC_CHANS_PER_TDM_E1 + slot;
#else
        /*
         * Since all E1s are mapped to TDMc, we can simply say the channel
         * number the user wants is the channel number they'll get.  It is
         * the user's responsibility to manage the interleaving.
         * NOTE: RECALL THAT SS7 CHANNELS CANNOT BE ODD NUMBERED.  This
         * means that the user had better pick the right timeslots to put
         * SS7 on, and not use the adjacent slot (NOT adjacent on the E1,
         * but adjacent as the framer maps them to the MCC).
         *
         * If you'd rather not burden the user with the mapping, and instead
         * want the channel number to mean span and slot, you can use the
         * following mapping (note we don't multiply by 2 as above because
         * we aren't reserving shadow RAM).
         *    span = mchan % MCC_TDMS_PER_MCC;      // mchan % 4
         *    slot = mchan / MCC_TDMS_PER_MCC;  // mchan / 4
         */
        idx = mchan + mcc->config.base_chan;
#endif
        printk("Using SIRAM(TX) idx %d\n", idx);

        /* NOTE THE |=.  The bits done when we did the MCC are preserved */
        mcc->sitxram[idx] |=
            SIxRAM_MCC_ENABLE                | /* MCC to TDM          */
            SIxRAM_LE_NORMAL                 | /* NOOP                */
            SIxRAM_SUP_NOT_SUPER             | /* Not a super channel */
            SIxRAM_MCSEL_CHAN(chans[i].chan) | /* Channel id          */
            SIxRAM_CNT_1_UNIT;                 /* NOOP                */

        /* Sync */
        eieio();
        barrier();
    }

    /*
     * Program SI Rx RAM for TDMx
     */
    for (i = 0; i < num_chan; i++)
    {
        mchan = chans[i].chan - mcc->config.base_chan;

        if (mchan >= MCC_MAX_CHAN_NORMAL)
        {
            continue;
        }

        if (chans[i].chan_type == MCC_TX)
        {
            continue;
        }

#if DEV_ASSUMPTIONS
        /*
         * For now, use a fixed mapping from mchan to span/slot
         */
        span = mchan / MCC_CHANS_PER_TDM_E1;
        slot = mchan % MCC_CHANS_PER_TDM_E1;
        idx = span * 2 * MCC_CHANS_PER_TDM_E1 + slot;
#else
        /*
         * See comments above.
         */
        idx = mchan + mcc->config.base_chan;
#endif
        printk("Using SIRAM(RX) idx %d\n", idx);

        /* NOTE THE |=.  The bits done when we did the MCC are preserved */
        mcc->sirxram[idx] |=
            SIxRAM_MCC_ENABLE                | /* MCC to TDM          */
            SIxRAM_LE_NORMAL                 | /* NOOP                */
            SIxRAM_SUP_NOT_SUPER             | /* Not a super channel */
            SIxRAM_MCSEL_CHAN(chans[i].chan) | /* Channel id          */
            SIxRAM_CNT_1_UNIT;                 /* NOOP                */

        if (chans[i].loopback) /* not required for internal loop */
        {
            mcc->sirxram[idx] |= SIxRAM_LE_LOOP;  /* Loopback */ // org
            //mcc->sirxram[idx] |= SIxRAM_LE_NORMAL;  /* NO Loopback */
        }

        /* Sync */
        eieio();
        barrier();
    }
}

/*
 * Setup the runtime struct for a single channel
 */
static void
mcc_init_one_run_channel(mcc_run_t *mcc,
                         mcc_channel_run_t *rchan, mcc_chan_config_t *cchan)
{
    mcc_channel_specific_hdlc_t *hdlc;
    mcc_channel_extra_param_t *extra;

    printk("%s:%d init_one_run_channel params rchan %p cchan %p\n",
           __FILE__, __LINE__, rchan, cchan);

    rchan->valid = 1;
    rchan->onread = cchan->onread;
    rchan->onwrite = cchan->onwrite;
    rchan->onsignal = cchan->onsignal;
    if (cchan->stats)
    {
        rchan->stats = cchan->stats;
    }
    else
    {
        rchan->stats = &rchan->lstats;
    }

    /*
     * find the channel specific info for this guy.
     */
    printk("%s:%d init_one_run_channel dpbase %08x extra %04x\n",
           __FILE__, __LINE__, mcc->config.dpbase, mcc->config.xtrabase);

    hdlc = (mcc_channel_specific_hdlc_t *)mcc->config.dpbase;
    extra = (mcc_channel_extra_param_t *)(mcc->config.dpbase +
                                          mcc->config.xtrabase);
    rchan->type.hdlc = &hdlc[cchan->chan];
    rchan->extra = &extra[cchan->chan];

    printk("%s:%d init_one_run_channel chanbase %p extra %p\n",
           __FILE__, __LINE__, rchan->type.hdlc, rchan->extra);
}

/*
 * Setup the BDs for a channel
 */
static void
mcc_init_one_channel_extra(mcc_run_t *mcc,
                           mcc_channel_run_t *rchan, u32 xidx)
{
    volatile mcc_channel_bd_t *bd;
    u8 *thisbuf;
    u32 i, onebufsz = MTP2_MAX_DRIVER_BYTES + 16;

    printk("%s:%d init_one_run_channel_extra params rchan %p xidx %08x\n",
           __FILE__, __LINE__, rchan, xidx);

    /*
     * Note that bds aren't so much pointers as offsets
     */
    rchan->extra->tbase = (xidx * 2) * mcc->config.bds_per;
    rchan->extra->tptr  = rchan->extra->tbase;
    rchan->extra->rbase = (xidx * 2 + 1) * mcc->config.bds_per;
    rchan->extra->rptr  = rchan->extra->rbase;

    /*
     * Save off real pointers for faster access
     */
    rchan->txbase = (mcc_channel_bd_t *)
        (mcc->config.bdbase +
         (xidx * 2) * mcc->config.bds_per * sizeof(mcc_channel_bd_t));
    rchan->tx = rchan->txbase;

    rchan->rxbase = (mcc_channel_bd_t *)
        (mcc->config.bdbase +
         (xidx * 2 + 1) * mcc->config.bds_per * sizeof(mcc_channel_bd_t));
    rchan->rx = rchan->rxbase;

    /*
     * Initialize the BDs
     */
    thisbuf = (u8 *)(mcc->config.bufbase +
                     ((xidx * 2) * mcc->config.bds_per * onebufsz));
    bd = rchan->tx;

    /* First transmit */
    for (i = 0; i < mcc->config.bds_per; i++)
    {
        bd->status = MCC_TXBD_I | MCC_TXBD_L | MCC_TXBD_TC;
        bd->length = 0;
        bd->buffer = (u8 *)__pa(thisbuf) + i * onebufsz;
        memset(__va(bd->buffer), 0, onebufsz);
        bd++;
    }
    bd--;
    bd->status |= MCC_TXBD_W; /* Wrap bit */
    bd++;
    /* Then receive */
    for (i = 0; i < mcc->config.bds_per; i++)
    {
        bd->status = MCC_RXBD_E | MCC_RXBD_I;
        bd->length = 0;
        bd->buffer = (u8 *)__pa(thisbuf) +
                            (mcc->config.bds_per * onebufsz) + (i * onebufsz);
        memset(__va(bd->buffer), 0, onebufsz);
        bd++;
    }
    bd--;
    bd->status |= MCC_RXBD_W;

    /* Sync */
    eieio();
    barrier();
}

/*
 * Initialize a channel in SS7 mode
 */
static void
mcc_init_one_channel_ss7(volatile mcc_channel_specific_ss7_t *ss7,
                         u8 bits)
{
    /* BigEndian SystemBus SystemBus */
    ss7->tstate = MCC_TSTATE_GLB_SNOOP_ON | MCC_TSTATE_BE_BIG_END |
                  MCC_TSTATE_DTB_SYSTEM   | MCC_TSTATE_BDB_SYSTEM;
    ss7->zistate = MCC_ZISTATE_REGULAR;
    ss7->zidata0 = MCC_ZIDATA_HL_WORD;
    ss7->zidata1 = MCC_ZIDATA_HL_WORD;
    ss7->tbdflags = 0;
    ss7->tbdcnt = 0;
    ss7->tbdptr = 0;
    ss7->echamr =
        /* Mode & reserved */
        MCC_ECHAMR_MODE_SS7   | MCC_ECHAMR_RESERVED_BITS |
        /* Interrupt mask  */
        ((MCC_INTMASK_UN   | MCC_INTMASK_TXB  | MCC_INTMASK_NID  |
          MCC_INTMASK_IDL  | MCC_INTMASK_MRF  | MCC_INTMASK_RXF  |
          MCC_INTMASK_BSY  | MCC_INTMASK_RXB) << MCC_ECHAMR_INTS_SHIFT) |
        /* Polling, idle mode, timestamp, int q, num flags */
        MCC_CHAMR_POL_ENABLE | MCC_CHAMR_IDLM_OFF   | MCC_CHAMR_TS_OFF  |
        (bits << MCC_CHAMR_RQN_SHIFT) | MCC_CHAMR_NOF_8;
    ss7->tcrc = 0;
    /* BigEndian SystemBus SystemBus */
    ss7->rstate = MCC_RSTATE_GLB_SNOOP_ON | MCC_RSTATE_BE_BIG_END |
                  MCC_RSTATE_DTB_SYSTEM   | MCC_RSTATE_BDB_SYSTEM;
    ss7->zdstate = MCC_ZDSTATE_REGULAR;
    ss7->zddata0 = MCC_ZDDATA_HL_WORD;
    ss7->zddata1 = MCC_ZDDATA_HL_WORD;
    ss7->rbdflags = 0;
    ss7->rbdcnt = 0;
    ss7->rbdptr = 0;
    ss7->mflr = MTP2_MAX_DRIVER_BYTES;
    ss7->max_cnt = 0;
    ss7->rcrc = 0;

    /*
     * The following may get overridden by the MTP2 driver.
     * Assume initialization for ANSI/ITU.
     */
    ss7->familydata.ansi_itu.n     = MCC_SS7MODE_N_INIT;
    ss7->familydata.ansi_itu.n_cnt = MCC_SS7MODE_N_CNT_INIT;
    ss7->familydata.ansi_itu.d     = MCC_SS7MODE_D_INIT;
    ss7->familydata.ansi_itu.d_cnt = MCC_SS7MODE_D_CNT_INIT;
    ss7->mask1 = 0xFFFFFFFFU;
    ss7->mask2 = 0xFFFFU;
    ss7->ss7_opt =
        MCC_SS7OPT_AERM_ENABLE   | MCC_SS7OPT_ENABLE_SUERM  |
        MCC_SS7OPT_ANSI_ITU      | MCC_SS7OPT_SF_DIS_TOSS   |
        MCC_SS7OPT_SU_FIL_ENABLE | MCC_SS7OPT_SEN_FIS_FISUS |
        MCC_SS7OPT_O_ORN_ENABLE  | MCC_SS7OPT_O_ITUT_ENABLE |
        MCC_SS7OPT_FISU_PAD_0;
    ss7->lrb1_tmp = 0;
    ss7->lrb2_tmp = 0;
    ss7->suerm    = MCC_SS7MODE_SUERM_INIT;
    ss7->lrb1     = 0;
    ss7->lrb2     = 0;
    ss7->t        = MCC_SS7MODE_T_INIT;
    ss7->lhdr     = 0;
    ss7->lhdr_tmp = 0;
    ss7->efsuc    = MCC_SS7MODE_EFSUC_INIT;
    ss7->suec     = MCC_SS7MODE_SUEC_INIT;
    ss7->ss7state = MCC_SS7MODE_SS7STATE_INIT;
    ss7->tmpstmp  = 0;
    ss7->delay    = 0;
    ss7->m        = MCC_SS7MODE_M_INIT;
    ss7->m_cnt    = MCC_SS7MODE_M_CNT_INIT;

    /* Sync */
    eieio();
    barrier();
}

/*
 * Initialize one channel in HDLC mode
 */
static void
mcc_init_one_channel_hdlc(volatile mcc_channel_specific_hdlc_t *hdlc,
                          u8 bits)
{
    /* BigEndian SystemBus SystemBus */
    hdlc->tstate = MCC_TSTATE_GLB_SNOOP_ON | MCC_TSTATE_BE_BIG_END |
                   MCC_TSTATE_DTB_SYSTEM   | MCC_TSTATE_BDB_SYSTEM;
    hdlc->zistate = MCC_ZISTATE_REGULAR;
    hdlc->zidata0 = MCC_ZIDATA_HL_WORD;
    hdlc->zidata1 = MCC_ZIDATA_HL_WORD;
    hdlc->tbdflags = 0;
    hdlc->tbdcnt   = 0;
    hdlc->tbdptr   = 0;
    hdlc->intmask = MCC_INTMASK_BSY | MCC_INTMASK_RXF | MCC_INTMASK_MRF |
                    MCC_INTMASK_RXB | MCC_INTMASK_TXB | MCC_INTMASK_UN;
    hdlc->chamr   = MCC_CHAMR_MODE_HDLC | MCC_CHAMR_RESET_HDLC |
                    MCC_CHAMR_NOF_2 | (bits << MCC_CHAMR_RQN_SHIFT);

    printk("CHARM Bits = 0x%0x \n", hdlc->chamr);

    hdlc->tcrc    = 0;
    /* BigEndian SystemBus SystemBus */
    hdlc->rstate = MCC_RSTATE_GLB_SNOOP_ON | MCC_RSTATE_BE_BIG_END |
                   MCC_RSTATE_DTB_SYSTEM   | MCC_RSTATE_BDB_SYSTEM;
    hdlc->zdstate = MCC_ZDSTATE_SYNC_RSYNC0_REG;
    hdlc->zddata0 = MCC_ZDDATA_HL_WORD;
    hdlc->zddata1 = MCC_ZDDATA_HL_WORD;
    hdlc->rbdflags = 0;
    hdlc->rbdcnt   = 0;
    hdlc->rbdptr   = 0;
    hdlc->mflr = MTP2_MAX_DRIVER_BYTES;
    hdlc->maxcnt = 0;
    hdlc->rcrc   = 0;

    /* Sync */
    eieio();
    barrier();
}

/*
 * Initialize one channel in transparent mode
 */
static void
mcc_init_one_channel_transparent(volatile mcc_channel_specific_transparent_t *trans,
                                 u8 bits)
{
    /* BigEndian SystemBus SystemBus */
    trans->tstate = MCC_TSTATE_GLB_SNOOP_ON | MCC_TSTATE_BE_BIG_END |
                    MCC_TSTATE_DTB_SYSTEM   | MCC_TSTATE_BDB_SYSTEM;
    trans->zistate = MCC_ZISTATE_REGULAR;
    trans->zidata0 = MCC_ZIDATA_HL_WORD;
    trans->zidata1 = MCC_ZIDATA_HL_WORD;
    trans->tbdflags = 0;
    trans->tbdcnt   = 0;
    trans->tbdptr   = 0;
    trans->intmask = MCC_INTMASK_BSY | MCC_INTMASK_RXF | MCC_INTMASK_MRF |
                     MCC_INTMASK_RXB | MCC_INTMASK_TXB | MCC_INTMASK_UN;
    trans->chamr   = MCC_CHAMR_MODE_TRANS | MCC_CHAMR_RESET_TRAN |
                     (bits << MCC_CHAMR_RQN_SHIFT);
    trans->reserved = 0;
    /* BigEndian SystemBus SystemBus */
    trans->rstate = MCC_RSTATE_GLB_SNOOP_ON | MCC_RSTATE_BE_BIG_END |
                    MCC_RSTATE_DTB_SYSTEM   | MCC_RSTATE_BDB_SYSTEM;
    trans->zdstate = MCC_ZDSTATE_REGULAR;
    trans->zddata0 = MCC_ZDDATA_HL_WORD;
    trans->zddata1 = MCC_ZDDATA_HL_WORD;
    trans->rbdflags = 0;
    trans->rbdcnt   = 0;
    trans->rbdptr   = 0;
    trans->tmrblr = MTP2_MAX_DRIVER_BYTES;
    trans->rcvsync = 0;
    trans->reserved1 = 0;

    /* Sync */
    eieio();
    barrier();
}

/*
 * Initialize the channels within this MCC.
 */
static void
mcc_init_channels(mcc_run_t *mcc,
                  mcc_channel_run_t *channels,
                  mcc_chan_config_t *chans, u32 num_chan)
{
    unsigned i;

    /*
     * Set the channel parameters for SS7
     * Tricky bit.  The base of the DPRAM area is where the channels go.
     */
    for (i = 0; i < num_chan; i++)
    {
        u8 lchan = LCHAN(chans[i].chan, mcc);

        printk("mcc_init_channels: %d lchan %d\n", chans[i].chan, lchan);

        if (lchan >= MCC_MAX_CHAN_SS7)
        {
            continue;
        }

        /* Mark this channel as configured. */
        mcc_init_one_run_channel(mcc, &channels[lchan], &chans[i]);

        /* BDs & Buffers */
        mcc_init_one_channel_extra(mcc, &channels[lchan], i);

        /*
         * Now to get to the channel specific parameters
         */
        channels[lchan].mode = chans[i].mode;
        printk("channel mode configured as %d\n", chans[i].mode);
        switch (chans[i].mode)
        {
        default:
        case MCC_TYPE_SS7:
            printk("SS7 Channle initialization....\n");
            mcc_init_one_channel_ss7(channels[lchan].type.ss7,
                                     i & 3);
            break;
        case MCC_TYPE_HDLC:
            mcc_init_one_channel_hdlc(channels[lchan].type.hdlc,
                                      i & 3);
            break;
        case MCC_TYPE_TRANS:
            mcc_init_one_channel_transparent(channels[lchan].type.transparent,
                                             i &  3);
            break;
        }

        /* enable our channels */
        mcc_start_channel_tx(mcc, chans[i].chan);
        mcc_start_channel_rx(mcc, chans[i].chan);
    }

    /* Initialize the SIRAM entries */
    mcc_config_siram(mcc, channels, chans, num_chan);
}

spinlock_t cmd_cplock;
/*
 * This really issues a command the the CPM, but this version is specific
 * to MCCs.
 */
void
mcc_issue_command(mcc_run_t *mcc, u32 command, int channel)
{
    volatile cpm_cpm2_t *cp;

    printk("issue_command: reg at %p command %08x chan: %d\n",
           &cpmp->cp_cpcr, command, channel);

    /* 
     * Issue command uses global registers and it is
     * in busy loop.
     */
    spin_lock(&cmd_cplock);

    cp = cpmp;
    while (cp->cp_cpcr & CPM_CR_FLG)
    {
    }

    if (command == CPM_CR_RST)
    {
        cp->cp_cpcr = CPM_CR_RST | CPM_CR_FLG;
    }
    else
    {
        cp->cp_cpcr = mk_cr_cmd(mcc->page, mcc->code, channel, command) |
                           CPM_CR_FLG;
    }

    while (cp->cp_cpcr & CPM_CR_FLG)
    {
    }

    spin_unlock(&cmd_cplock);
}

/*
 * Start receiving on a channel
 */
void
mcc_start_channel_rx(mcc_run_t *mcc, int channel)
{
    unsigned lchan = LCHAN(channel, mcc);

    if (mcc->channels[lchan].valid)
    {
        mcc->channels[lchan].type.hdlc->rstate =
            (mcc->channels[lchan].type.hdlc->rstate | MCC_RSTATE_START) &
            MCC_RSTATE_MASK;
    }
}

/*
 * Start sending on a channel
 */
void
mcc_start_channel_tx(mcc_run_t *mcc, int channel)
{
    unsigned lchan = LCHAN(channel, mcc);

    if (mcc->channels[lchan].valid)
    {
        mcc->channels[lchan].type.hdlc->tstate =
            (mcc->channels[lchan].type.hdlc->tstate | MCC_TSTATE_START) &
            MCC_TSTATE_MASK;
    }
}

/*
 * Stop receiving on a channel
 */
void
mcc_stop_channel_rx(mcc_run_t *mcc, int channel)
{
    unsigned lchan = LCHAN(channel, mcc);

    if (mcc->channels[lchan].valid)
    {
        mcc_issue_command(mcc, CPM_CR_STOP_MCC_RX, channel);
    }
}

/*
 * Stop sending on a channel
 */
void
mcc_stop_channel_tx(mcc_run_t *mcc, int channel)
{
    unsigned lchan = LCHAN(channel, mcc);

    if (mcc->channels[lchan].valid)
    {
        mcc_issue_command(mcc, CPM_CR_STOP_MCC_TX, channel);
    }
}

/*
 * reset the filtering mechanism on channel
 */
void
mcc_reset_filter(mcc_run_t *mcc, int channel)
{
    unsigned lchan = LCHAN(channel, mcc);

    if (mcc->channels[lchan].valid)
    {
        /* See 33.9.4.4.4 */
        mcc_issue_command(mcc, 0x0E, channel);
    }
}

/*
 * Send data to a channel.  In essence, this is the L2->L1 interface
 */
int
mcc_send_data(mcc_run_t *mcc, int channel, void *buf, u32 size)
{
    int retry = 3;
    unsigned lchan = LCHAN(channel, mcc);

    if (mcc == NULL || lchan >= MCC_MAX_CHAN_SS7 ||
        buf == NULL || size == 0 || !mcc->channels[lchan].valid)
    {
        printk("configuration problem sending data:\n");
        printk("     mcc %p lchan %d buf %p size= %d valid= %d\n",
               mcc, lchan, buf, size, mcc->channels[lchan].valid);

        return -EINVAL;
    }

    if (size > mcc->mcc_params->mrblr)
    {
        printk("overflow sending data\n");

        return -EOVERFLOW;
    }

    while (1)
    {
        volatile mcc_channel_bd_t *bd = mcc->channels[lchan].tx;
        volatile u16 status = bd->status;

        /* Copy the data */
        if (!(status & MCC_TXBD_R))
        {
            u8 *tmp;
            memcpy(__va(bd->buffer), buf, size);

            bd->length = size;
            bd->status |= MCC_TXBD_R;

#if 0
            if (mcc->channels[lchan].mode == MCC_TYPE_SS7)
            {
                printk("echamr bits before POL: %08x mccm %04x mcce %04x\n",
                       mcc->channels[lchan].type.ss7->echamr,
                       mcc->mcc_regs->mcc_mccm, mcc->mcc_regs->mcc_mcce);
            }
            else
            {
                printk("chamr bits before POL: %04x mccm %04x mcce %04x\n",
                       mcc->channels[lchan].type.hdlc->chamr,
                       mcc->mcc_regs->mcc_mccm, mcc->mcc_regs->mcc_mcce);
            }
#endif

            /* Set POL */
            if (mcc->channels[lchan].mode == MCC_TYPE_SS7)
            {
                mcc->channels[lchan].type.ss7->echamr |= MCC_CHAMR_POL_ENABLE;
            }
            else
            {
                mcc->channels[lchan].type.hdlc->chamr |= MCC_CHAMR_POL_ENABLE;
            }

            /* Sync */
            eieio();
            barrier();

            /* Get the next BD in the ring */
            if (status & MCC_TXBD_W)
            {
                mcc->channels[lchan].tx = mcc->channels[lchan].txbase;
            }
            else
            {
                mcc->channels[lchan].tx++;
            }

            tmp = __va(bd->buffer);
#if 0
            printk("mcc_send_data: good transmission %p BDSTatus = 0x%x length %d\n",
                    mcc->channels[lchan].tx, bd->status, bd->length);
            if (mcc->channels[lchan].mode == MCC_TYPE_SS7)
            {
                printk("echamr bits: %08x mccm %04x mcce %04x\n",
                       mcc->channels[lchan].type.ss7->echamr,
                       mcc->mcc_regs->mcc_mccm, mcc->mcc_regs->mcc_mcce);
            }
            else
            {
                printk("chamr bits: %04x mccm %04x mcce %04x\n",
                       mcc->channels[lchan].type.hdlc->chamr,
                       mcc->mcc_regs->mcc_mccm, mcc->mcc_regs->mcc_mcce);
            }
#endif
            printk("Sending data channel %d len %d %02x %02x %02x %02x\n",
                   channel, bd->length,
                   tmp[0], tmp[1], tmp[2], tmp[3]);

            /* Good transmission, bail */
            return (int)size;
        }
        else
        {
            retry--;
            if (retry <= 0)
            {
                /* Give it up */
                return -ENOMEM;
            }

            printk("mcc_send_data: go schedule()\n");

            /* Maybe an interrupt can give us space */
            if (mcc->channels[lchan].mode == MCC_TYPE_SS7)
            {
                mcc->channels[lchan].type.ss7->echamr |= MCC_CHAMR_POL_ENABLE;
            }
            else
            {
                mcc->channels[lchan].type.hdlc->chamr |= MCC_CHAMR_POL_ENABLE;
            }
        }
    }

    /* NOTREACHED */
    return 0;
}

/*
 * Handle an error.  Without detailed knowledge about the target, there
 * isn't much to do here
 */
void
mcc_handle_error(mcc_run_t *mcc, u16 error)
{
    switch (error)
    {
    case TX_ERR_UN:
        mcc->stats.txunderflow++;
        break;
    case RX_ERR_BSY:
        mcc->stats.rxbusy++;
        break;
    case RX_ERR_MFV:
        mcc->stats.mfv++;
        break;
    case MCC_ERR_GOV:
        mcc->stats.gov++;
        break;
    case MCC_ERR_GUN:
        mcc->stats.gun++;
        break;
    case MCC_ERR_TQOV:
        mcc->stats.tqov++;
        break;
    case MCC_ERR_RQOV0:
        mcc->stats.rqov0++;
        break;
    case MCC_ERR_RQOV1:
        mcc->stats.rqov1++;
        break;
    case MCC_ERR_RQOV2:
        mcc->stats.rqov2++;
        break;
    case MCC_ERR_RQOV3:
        mcc->stats.rqov3++;
        break;
    case UNKNOWN_ERR:
    default:
        mcc->stats.unknown++;
        break;
    }
}

/*
 * The ISR.  Essentially, this is the L1->L2 interface.
 */
static void
mcc_interrupt(int irq, void *device, struct pt_regs *regs)
{
    register mcc_run_t *mcc;
    register u16  event;
    register u16  mcce;
    register u16  mccm;
    register u16  chan; 
    register u16  mchm = 0;
    register u8   rint; /* a mask to the Rx interrupts bits. */
    register u8   rxq;
    register u8   lchan;
    volatile mcc_channel_bd_t    *bd;
    u16           status;
    int           rerr = 0;

    /*
     * recover ourselves
     */
    mcc = (mcc_run_t *)device;

    /*
     * Get our events and mask
     */
    mcce = mcc->mcc_regs->mcc_mcce;
    mccm = mcc->mcc_regs->mcc_mccm;

    /*
     * Clear event bits of the global event register for next time.
     */
    mcc->mcc_regs->mcc_mcce = MCCE_CLEAR; /* mcce; */

    /*
     * 'mcce' will now contain all interrupts that will be handled below.
     */
    mcce = mcce & mccm;

    /*
     * Get the Rx interrupts only.
     */
    rint = (MCCE_RINT & mcce) >> 8;

    /*
     * See if there's a write interrupt pending.
     */
    if (mcce & MCCE_TINT)
    {
        /*
         * Read from the next table entry the channel's events and
         * channel number and read mask from DPR.
         */
        mcc->stats.txintcnt++;
        event = mcc->txints->status;
        chan  = mcc->txints->channel >> MCC_ICTE_CHANNEL_SHIFT;
        lchan = LCHAN(chan, mcc);
        mchm  = mcc->channels[lchan].type.ss7->echamr >> MCC_ICTE_SHIFT;
   
        /*
         * 'event' will now contain all interrupts that will be handled below.
         */
        event &= (mchm | MCC_ICTE_V | MCC_ICTE_W);

        /* Handle all events in the Tx interrupts table. */
        while (event & MCC_ICTE_V)
        {
            /*
             * Clear event bits, V bit, and channel number in a single store.
             */
            *(u32 *)&mcc->txints->status =
                (u32 )((event & MCC_ICTE_W) << MCC_ICTE_SHIFT);

            /* Frame was successfully transmitted. */
            mcc->channels[lchan].stats->txFrames++;

            /*
             * If error event, call the upper layer's error handler routine.
             */
            if (event & MCC_ICTE_UN)
            {
                mcc_handle_error(mcc, TX_ERR_UN);
            }

            /* Notify the application that a write happened */
            if (mcc->channels[lchan].onwrite)
            {
                (*mcc->channels[lchan].onwrite)(chan);
            }

            /*
             * Get next entry.
             */
            if (event & MCC_ICTE_W)
            {
                mcc->txints =
                    (mcc_interrupt_table_entry_t *)mcc->txintbase;
            }
            else
            {
                mcc->txints++;
            }

            event = mcc->txints->status;
            chan  = (mcc->txints->channel) >> MCC_ICTE_CHANNEL_SHIFT;
            lchan = LCHAN(chan, mcc);

            /*
             * 'event' will now contain all interrupts that will
             * be handled during the next loop iteration.
             */
            event &= (mchm | MCC_ICTE_V | MCC_ICTE_W);
        }
    }

    /*
     * rint contains the 4 bits signifying the 4 Rx interrupt queues.
     * By shifting rint, and decrementing rxq, we test each one of
     * the queues.
     */
    rxq = 3;
    while (rint)
    {
        if ( (rint & 1) && (mcc->rxints[rxq] != NULL) )
        {
            mcc->stats.rxintcnt++;

            switch (rxq)
            {
            case 3:
                mcc->stats.rint3++;
                break;
            case 2:
                mcc->stats.rint2++;
                break;
            case 1:
                mcc->stats.rint1++;
                break;
            case 0:
            default:
                mcc->stats.rint0++;
                break;
            }

            /*
             * Read from the next table entry the channel's events and
             * channel number and read mask from DPR.
             */
            event = mcc->rxints[rxq]->status;
            chan  = mcc->rxints[rxq]->channel >> MCC_ICTE_CHANNEL_SHIFT;
            lchan = LCHAN(chan, mcc);
            mchm  = mcc->channels[lchan].type.ss7->echamr >> MCC_ICTE_SHIFT;

            /*
             * 'event' will now contain interrupts that will be handled below.
             */
            event &= (mchm | MCC_ICTE_V | MCC_ICTE_W);
            while (event & MCC_ICTE_V)
            { 
                /* Clear event bits, V bit, and channel number. */
                *(u32 *)&mcc->rxints[rxq]->status =
                   (u32)((event & MCC_ICTE_W) << MCC_ICTE_SHIFT);

                /* If Rx event, call the upper layer's Rx handler routine. */
                if (event & (MCC_ICTE_RXF | MCC_ICTE_RXB))
                {
                    /*
                     * While there are received buffers:
                     * BD is empty (R_E) and not hold (R_H)
                     */
                    bd = mcc->channels[lchan].rx;
                    status = bd->status;
                    while (!(status & MCC_RXBD_E))
                    {
                        /* Check for errors. */
                        rerr = 0;
                        if (status & MCC_RXBD_LG)
                        {
                            mcc->channels[lchan].stats->rxLengthViolation++;
                            rerr = 1;
                        }
                        if (status & MCC_RXBD_NO)
                        {
                            mcc->channels[lchan].stats->rxNonAligned++;
                            rerr = 1;
                        }
                        if (status & MCC_RXBD_AB)
                        {
                            mcc->channels[lchan].stats->rxAbort++;
                            rerr = 1;
                        }
                        if (status & MCC_RXBD_CR)
                        {
                            mcc->channels[lchan].stats->rxCRCError++;
                            rerr = 1;
                            /* There's not a signal for this.  Use a reserved */
                            if (mcc->channels[lchan].onsignal)
                            {
                                (*mcc->channels[lchan].onsignal)(chan,
                                                                 MCC_ICTE_RSVD1);
                            }
                        }
                        if (!(status & MCC_RXBD_F) || !(status & MCC_RXBD_L))
                        {
                            /*
                             * Since we made the assumption that all received
                             * frames fit into one Rx buffer, we expect both
                             * the F (first) and L (last) bits to be set.  If
                             * they are not both set, means a frame larger
                             * than the size of our Rx buffer was received.
                             * In that case, we must discard the frame.
                             */
                            mcc->channels[lchan].stats->rxOverflow++;
                            rerr = 1;
                        }
                        if (bd->length == 0)
                        {
                            rerr = 1;
                        }

                        if (rerr)
                        {
                            /* Ready this Rx BD for next use. */
                            bd->status = ((bd->status) & MCC_RXBD_W) |
                                                 MCC_RXBD_E | MCC_RXBD_I;
                            bd->length = 0;
                        }
                        else
                        {
                            /* Get buffer associated with this BD. */
                            if (!bd->buffer)
                            {
                                /* Ready this Rx BD for next use. */
                                bd->status = ((bd->status) & MCC_RXBD_W) |
                                                   MCC_RXBD_E | MCC_RXBD_I;
                                bd->length = 0;
   
                            }
                            else
                            {
                                mcc->channels[lchan].stats->rxFrames++;

                                /*
                                 * Application layer must to copy data.
                                 */
                                if (mcc->channels[lchan].onread)
                                {
                                    (*mcc->channels[lchan].onread)(chan, bd);
                                }
                            }

                            /* Ready this Rx BD for next use. */
                            bd->status = ((bd->status) & MCC_RXBD_W) |
                                                MCC_RXBD_E | MCC_RXBD_I;
                            bd->length = 0; 
                        }

                        /* Advance pointer to buffer descriptor. */
                        if (status & MCC_RXBD_W)
                        {
                            mcc->channels[lchan].rx = mcc->channels[lchan].rxbase;
                        }
                        else
                        {
                            mcc->channels[lchan].rx++;
                        }

                        bd = mcc->channels[lchan].rx;
                        status = bd->status;
                    }
                }

                /*
                 * Handle data-less interrupts.  For SS7, these need to get to
                 * the application.
                 */
                if (event & MCC_ICTE_IDLE)
                {
                    if (mcc->channels[lchan].onsignal)
                    {
                        (*mcc->channels[lchan].onsignal)(chan, MCC_ICTE_IDLE);
                    }
                    mcc->channels[lchan].stats->sigIdle++;
                }
                if (event & MCC_ICTE_NID)
                {
                    if (mcc->channels[lchan].onsignal)
                    {
                        (*mcc->channels[lchan].onsignal)(chan, MCC_ICTE_NID);
                    }
                    mcc->channels[lchan].stats->sigNonIdle++;
                }
                if (event & MCC_ICTE_AERM)
                {
                    if (mcc->channels[lchan].onsignal)
                    {
                        (*mcc->channels[lchan].onsignal)(chan, MCC_ICTE_AERM);
                    }
                    mcc->channels[lchan].stats->sigAERM++;
                }
                if (event & MCC_ICTE_FISU)
                {
                    if (mcc->channels[lchan].onsignal)
                    {
                        (*mcc->channels[lchan].onsignal)(chan, MCC_ICTE_FISU);
                    }
                    mcc->channels[lchan].stats->sigFISU++;
                }
                if (event & MCC_ICTE_SUERM)
                {
                    if (mcc->channels[lchan].onsignal)
                    {
                        (*mcc->channels[lchan].onsignal)(chan, MCC_ICTE_SUERM);
                    }
                    mcc->channels[lchan].stats->sigSUERM++;
                }
                if (event & MCC_ICTE_OCT)
                {
                    if (mcc->channels[lchan].onsignal)
                    {
                        (*mcc->channels[lchan].onsignal)(chan, MCC_ICTE_OCT);
                    }
                    mcc->channels[lchan].stats->sigOCT++;
                }
                 
                /*
                 * If error event, call the upper layer's error handler routine.
                 */
                if (event & MCC_ICTE_BSY)
                {
                   mcc_handle_error(mcc, RX_ERR_BSY);
                }
                if (event & MCC_ICTE_MRF)
                {
                   mcc_handle_error(mcc, RX_ERR_MFV);
                }

                /*
                 * Get next entry.
                 */
                if (event & MCC_ICTE_W)
                {
                    mcc->rxints[rxq] = mcc->rxintbases[rxq];
                }
                else
                {
                    mcc->rxints[rxq]++;
                }

                event = (mcc->rxints[rxq])->status;
                chan = (mcc->rxints[rxq]->channel) >> MCC_ICTE_CHANNEL_SHIFT;
                lchan = LCHAN(chan, mcc);

                /*
                 * 'event' will now contain all interrupts that will be
                 * handled during the next loop iteration.
                 */
                event &= (mchm | MCC_ICTE_V | MCC_ICTE_W);
            }
        }

        /*
         * Get next Rx int queue.
         */
        rxq--;
        rint = (rint >> 2);
    }

    /* If error, call the upper layer's error handler routine. */
    if (mcce & MCCE_TQOV)
    {
        mcc_handle_error(mcc, MCC_ERR_TQOV);
    }
    if (mcce & MCCE_GOV)
    {
        mcc_handle_error(mcc, MCC_ERR_GOV);
    }
    if (mcce & MCCE_GUN)
    {
        mcc_handle_error(mcc, MCC_ERR_GUN);
    }
    if (mcce & MCCE_RQOV0)
    {
        mcc_handle_error(mcc, MCC_ERR_RQOV0);
    }
    if (mcce & MCCE_RQOV1)
    {
        mcc_handle_error(mcc, MCC_ERR_RQOV1);
    }
    if (mcce & MCCE_RQOV2)
    {
        mcc_handle_error(mcc, MCC_ERR_RQOV2);
    }
    if (mcce & MCCE_RQOV3)
    {
        mcc_handle_error(mcc, MCC_ERR_RQOV3);
    }
}

/********************************** DRIVER SECTION ************************/

#if DEV_ASSUMPTIONS
/*
 * We don't need this with real hardware.
 */
static void
init_clk_brgs(volatile cpm2_map_t *cp2)
{
    volatile cpmux_t *mux = &cp2->im_cpmux;
    volatile cpmtimer_cpm2_t *tmr = &cp2->im_cpmtimer;
    volatile cpm_cpm2_t *cp = cpmp;

    /* Arrange for the timestamp control register to prescale a 1MHz clock */
    cp->cp_rtscr = 0x0548;

    /* Apparently this isn't affected by anything */
    /* sccr == 0x01000018?? */

    /* Arrange for default clock sources for all TDMs */
    mux->cmx_si1cr = 0x00;
    mux->cmx_si2cr = 0x00;

    /* Set up a timer for the sync pulse */
    tmr->cpmt_tgcr1 = CPM_TIMER_GCR_CAS_NORMAL  |
                      CPM_TIMER_GCR_GM1_NORMAL  |
                      CPM_TIMER_GCR_RST1_ENABLE;

    tmr->cpmt_tmr1  = 
                 (CPM_TMR_PRESCALER_DIV1_VAL << CPM_TMR_PS_VALUE_SHIFT) | 
                  CPM_TMR_OM_ACTIVE   | CPM_TMR_FRR_RESTART             |
                  CPM_TMR_ICLK_INTRL_FALLING_TINX;

    tmr->cpmt_trr1  = 0x00FF; /* Timeout Reference value */

    /*
     * Ask the kernel to set us up a fast BRG.
     * Note the kernel numbers from 0
     */
    cpm2_fastbrg(4, 2048000, 0);

    printk("tgcr1 = 0x%x tmr1 = 0x%x \n", 
            tmr->cpmt_tgcr1, tmr->cpmt_tmr1);

    printk("System clock: sccr = 0x%08x (at loc %p)\n",
           cp2->im_clkrst.car_sccr, &cp2->im_clkrst.car_sccr);
    printk("cp2->im_brgc5 = 0x%0x \n", cp2->im_brgc5);
}
#endif

static void
init_parallel_ports(volatile cpm2_map_t *cp2)
{
    volatile iop_cpm2_t *iop = &cp2->im_ioport;

#if 0
    /* Program the Port Special Options Registers */
    iop->iop_psora |= 0x03C00000;
    iop->iop_psorb |= 0x00000000;
    iop->iop_psorc |= 0x00000002; /* TOUT */
    iop->iop_psord |= 0x00000000;

    /* Program the Port Data Direction Registers */
    iop->iop_pdira |= 0x00000000;
    iop->iop_pdirb |= 0x0000C000;
    iop->iop_pdirc |= 0x00000102; /* TOUT */
    iop->iop_pdird |= 0x00000000;

    /* Program The Port Open-Drain Registers */
    iop->iop_podra |= 0x00000000;
    iop->iop_podrb |= 0x00000000;
    iop->iop_podrc |= 0x00000000;
    iop->iop_podrd |= 0x00000000;

    /* Program the Port Pin Assignment Registers */
    iop->iop_ppara |= 0x03C00000;
    iop->iop_pparb |= 0x0000C000;
    iop->iop_pparc |= 0x0000010B;
    iop->iop_ppard |= 0x00000000;
#endif
#if 0
/* FROM FREESCALE.  DOESN'T WORK EITHER */
    /* Program the Port Special Options Registers */
    iop->iop_psora = 0x00000000;
    iop->iop_psorb = 0x0f000000;
    iop->iop_psorc = 0xc0000802; /* TOUT */
    /* iop->iop_psord |= 0x00000000; */

    /* Program the Port Data Direction Registers */
    iop->iop_pdira = 0x00000000;
    iop->iop_pdirb = 0x00000000;
    iop->iop_pdirc = 0xc0000102; /* TOUT */
    /* iop->iop_pdird |= 0x00000000; */

    /* Program The Port Open-Drain Registers */
    iop->iop_podra = 0x00000000;
    iop->iop_podrb = 0x00000000;
    iop->iop_podrc = 0x00000000;
    /* iop->iop_podrd |= 0x00000000; */

    /* Program the Port Pin Assignment Registers */
    iop->iop_ppara = 0x00000000;
    iop->iop_pparb = 0x0f000000;
    iop->iop_pparc = 0xc000390A;
    /* iop->iop_ppard |= 0x00000000; */
#endif
#if 1
    iop->iop_pparb |= 0x000000F0;
    iop->iop_psorb |= 0x000000F0;
    iop->iop_podrb &= ~0x000000F0;
    iop->iop_pdirb &= ~0x000000F0;

    iop->iop_pparc |= 0x0000000C;
    iop->iop_psorc &= ~0x0000000C;
    iop->iop_podrc &= ~0x0000000C;
    iop->iop_pdirc &= ~0x0000000C;
#endif
#if 0
    /* Program the Port Special Options Registers */
    iop->iop_psora |= 0x00000000;
    iop->iop_psorb |= 0x08000000;
    iop->iop_psorc |= 0x00000002; /* TOUT */
    iop->iop_psord |= 0x00000000;

    /* Program the Port Data Direction Registers */
    iop->iop_pdira |= 0x00000000;
    iop->iop_pdirb |= 0x00000000;
    iop->iop_pdirc |= 0x00000102; /* TOUT */
    iop->iop_pdird |= 0x00000000;

    /* Program The Port Open-Drain Registers */
    iop->iop_podra |= 0x00000000;
    iop->iop_podrb |= 0x00000000;
    iop->iop_podrc |= 0x00000000;
    iop->iop_podrd |= 0x00000000;

    /* Program the Port Pin Assignment Registers */
    iop->iop_ppara |= 0x00000000;
    iop->iop_pparb |= 0x08000000;
    iop->iop_pparc |= 0x0000110a;
    iop->iop_ppard |= 0x00000000;
#endif
}

/*
 * Everybody needs globals sometimes.
 */
mcc_run_t mcc1;
mcc_run_t mcc2;
mcc_channel_run_t mcc1_channels[MCC_MAX_CHAN_SS7];
mcc_channel_run_t mcc2_channels[MCC_MAX_CHAN_SS7];

#define CPM_MAP_SIZE (0x40000)

/*
 * Initialize MCC1
 */
void
init_mcc1(void)
{
#if 1
        cpm2_immr = (volatile cpm2_map_t *)ioremap(CPM_MAP_ADDR,
                                                   CPM_MAP_SIZE);
        cpmp = &cpm2_immr->im_cpm;
#endif

    /*
     * clear this controller's channel area
     */
    memset((void *)cpm2_immr->im_dprambase, 0, 8 * 1024);

#if DEV_ASSUMPTIONS
    /* Development settings */
    init_clk_brgs(cpm2_immr); /* Init clock and brg registers */
#endif
    init_parallel_ports(cpm2_immr); /* Set TDM ports for Tx/Rx */

    /*
     * Hook the interrupt.
     */
    request_irq(SIU_INT_MCC1, mcc_interrupt, 0, "mcc1", &mcc1);

    /*
     * MCC1 interrupts are expected to be disabled here.  The caller is
     * responsible.
     */
    disable_irq(SIU_INT_MCC1);

    /*
     * BDs per.  We're going with 64.  For why, read the following comments.
     */
    mcc1.config.bds_per = 64;

    /*
     * Base channel
     */
    mcc1.config.base_chan = 0;

    /*
     * Number of interrupts per INT table.  We'll go with 64, or 256 bytes
     * per table.
     */
    mcc1.config.intsize = 64 * sizeof(mcc_interrupt_table_entry_t);

    /*
     * Build memory map in config area.
     *
     * The immap struct defines a few regions for the DPRAM.  They are
     * as follows:
     *  o im_dpram1 = first 16K.  MCC channel specific MUST live in
     *    here
     *  o res1 = next 16K.  Reserved in processor memory map.  Must not
     *    be used.
     *  o im_dpram2 = next 4K.  This region is reserved for parameter RAM
     *    for the various CCs.  Must not be used, except for parameters.
     *  o res2 = the immap says this is reserved, but the processor manual
     *    for an _8560_ will tell you it's not (I'm assuming it is on an 8260).
     *    This is the region I speak of below.
     *  o im_dpram3 = the next 4K.  This memory is reserved for FCC data.
     *
     * We have a couple of areas that aren't reserved for channel structs.
     * (those live in the first 16K of the DPRAM, so avoid using them if you
     * can).  Starting at offset 0x9000, there is 8K of memory available that
     * can _only_ be used for BDs and data.  So, we'll put the XTRABASE and
     * SCTPBASE in that region.
     */

    /*
     * First, we'll save off a pointer to the channel area for this MCC.
     */
    mcc1.config.dpbase = (u32)(cpm2_immr->im_dpram1);

    /*
     * SCTPBASE:  This (if defined) must be 128 * sizeof(u16) bytes in size.
     * MCC1 and MCC2 share this space.
     */
    mcc1.config.sctpbase = offsetof(cpm2_map_t, res2) + MCC1_SCTP_OFF;
    mcc2.config.sctpbase = 0;

    /*
     * XTRABASE: This can be at most 256 * 8 bytes in size.  This is where
     * channel extra parameters will live.
     * We wipe the first 1K (128 * 8), as those are the extra params for
     * MCC1.
     */
    mcc1.config.xtrabase = offsetof(cpm2_map_t, res2) + MCC_XTRA_OFF;
    memset((void *)(cpm2_immr->res2 + MCC_XTRA_OFF), 0, 1024);

    /*
     * This is the xtra size.
     * MCC_MAX_CHAN_NORMAL * sizeof(mcc_channel_extra_param_t);
     * So, at this point we've used  256 + 1024 bytes.  MCC2 can use another
     * 1.25K, so overhead is a total of 2.5K.
     */

    /*
     * The rest of the memory regions live in the regular address space
     * (not in the DP area).  These regions consist of
     *  o BD _table_ area.  The channel extra parameters contain half words
     *    that represent offsets in the bdbase region (the offsets are
     *    expressed as the offset of 8 byte double words.  The math shows
     *    that this can conceivably fill the 512K region allowed for mccbase
     *    (MAX_USHORT * sizeof(BD)), or 512K.
     *  o The interrupt table, which is basically an array of words as big
     *    as you want.  We'll use 64 entries per table, and we need 5 tables,
     *    so this is 1280 bytes.
     *  o The actual buffer areas themselves.  The do NOT have to be in the
     *    512K region.  The 512K region is simply for the BD tables, not the
     *    buffers they point to.
     *
     * Here's the key to the mccbase, and the BD tables:
     *  o 512K region.  This is a bit misleading.  Think of it as:
     *    mcc_channel_bd_t  bds[MAX_USHORT];
     *  o You need both TX and RX BD areas; assume for the sake of example
     *    that you split it down the middle:
     *    mcc_channel_bd_t  txbds[MAX_USHORT/2];
     *    mcc_channel_bd_t  rxbds[MAX_USHORT/2];
     *    (we actually lay them out sequentially, but this is merely an
     *    example).
     *  o This means you have 32K BDs for TX, 32K for RX.
     *  o You have a maximum of 128 channels allowed for each MCC.  This means
     *    your BD tables can be at most (using exponents here) 15 - 7 BD
     *    entries per channel, or 256, if you want to keep an equal allocation
     *    for all of your channels.  For pretty much any application that
     *    is overkill, unless you configure every possible channel.  So, we're
     *    going to assume 64 entries in each BD table per channel, or 128
     *    BDs total, which means we need (exponents again, and + 1 for TX/RX)
     *    6 + 1 + 7, or 2**14 entries, or 2**17 bytes, or 128K.  To put it
     *    another way, since we are only asking for a fourth of the possible
     *    BDs that we can have, we only need a fourth of the 512K allowed.
     *
     *    Note that all this is true of each MCC, since we have two.
     *    I'm writing this at 10pm with a buzz on, so forgive me if my math
     *    is off a hair.
     */
    /*
     * Allocate the BD table area.  The calculation represents how we get
     * the 128K requirement.  The "2" represents the combination of Tx and Rx.
     */
    mcc1.config.bdbase = (u32)kmalloc(MCC_MAX_CHAN_NORMAL * 2 *
                                          mcc1.config.bds_per *
                                          sizeof(mcc_channel_bd_t),
                                      GFP_KERNEL);
    if (mcc1.config.bdbase == 0)
    {
        printk("Can't allocate BD table region.\n");

        return;
    }
    memset((void *)mcc1.config.bdbase,
           0,
           MCC_MAX_CHAN_NORMAL * 2 *
                mcc1.config.bds_per * sizeof(mcc_channel_bd_t));

    /*
     * allocate the interrupt table area.  The calculation represents how
     * we get to the size.  The "5" represents one Tx table and 4 Rx tables.
     */
    mcc1.config.intbase = (u32)kmalloc(mcc1.config.intsize * 5,
                                       GFP_KERNEL);
    if (mcc1.config.intbase == 0)
    {
        printk("Can't allocate INT table region.\n");

        kfree((void *)mcc1.config.bdbase);

        return;
    }

    /*
     * allocate the buffer area.  The calculation represents how we get to
     * the size for this region.  Again, the "2" represents Tx/Rx.
     * This monster is ~ 4.5MB.
     */
    mcc1.config.bufbase = __get_free_pages(GFP_KERNEL, 8);
    if (mcc1.config.bufbase == 0)
    {
        printk("Can't allocate BUF region.\n");

        kfree((void *)mcc1.config.bdbase);
        kfree((void *)mcc1.config.intbase);

        return;
    }

    /*
     * Save the page and code off for issuing commands
     */
    mcc1.page = CPM_CR_MCC1_PAGE;
    mcc1.code = CPM_CR_MCC1_SBLOCK;

    /*
     * Wipe the control struct
     */
    memset(&mcc1_channels, 0, 
           MCC_MAX_CHAN_SS7 * sizeof(mcc_channel_run_t));

    /*
     * Initialize the MCC
     */
    mcc_init(&mcc1,
             &cpm2_immr->im_mcc1,
             (mcc_global_param_t *)
                 &cpm2_immr->im_dpram2[CPM_CR_MCC1_PAGE << 8],
             &cpm2_immr->im_siramctl1,
             (u16 *)cpm2_immr->im_si1txram,
             (u16 *)cpm2_immr->im_si1rxram);
}

void
exit_mcc1(void)
{
    /* Disable all TDMs */
    mcc_disable_si(&mcc1);
    /* Disable IRQ */
    disable_irq(SIU_INT_MCC1);
    /* Unregsiter IRQ */
    free_irq(SIU_INT_MCC1, &mcc1);
    /* Free allocated memory */
    kfree((void *)mcc1.config.bdbase);
    kfree((void *)mcc1.config.intbase);

    /* Unmap the device */
    if (cpm2_immr)
    {
        iounmap(cpm2_immr);
        cpm2_immr = NULL;
    }
}
/*
 * Initialize the SS7 channels
 */
void
init_mcc1_channels(mcc_chan_config_t *channels, int nchan)
{
    mcc1.channels = mcc1_channels;

    mcc_init_channels(&mcc1, mcc1_channels, channels, nchan);

    enable_irq(SIU_INT_MCC1);
}

/*
 * Initialize MCC2
 */
void
init_mcc2(void)
{
#if 1
        cpm2_immr = (volatile cpm2_map_t *)ioremap(CPM_MAP_ADDR,
                                                   CPM_MAP_SIZE);
        cpmp = &cpm2_immr->im_cpm;
#endif

    /*
     * clear this controller's channel area
     */
    memset((void *)(cpm2_immr->im_dprambase + 8 * 1024), 0, 8 * 1024);

#if DEV_ASSUMPTIONS
    /* Development settings */
    init_clk_brgs(cpm2_immr); /* Init clock and brg registers */
#endif
    init_parallel_ports(cpm2_immr); /* Set TDM ports for Tx/Rx */

    /*
     * Hook the interrupt.
     */
    request_irq(SIU_INT_MCC2, mcc_interrupt, 0, "mcc2", &mcc2);

    /*
     * MCC2 interrupts are expected to be disabled here.
     */
    disable_irq(SIU_INT_MCC2);

    /*
     * BDs per.  We're going with 64.  For why, read the following comments.
     */
    mcc2.config.bds_per = 64;

    /*
     * Base channel
     */
    mcc2.config.base_chan = 128;

    /*
     * Number of interrupts per INT table.  We'll go with 64, or 256 bytes
     * per table.
     */
    mcc2.config.intsize = 64 * sizeof(mcc_interrupt_table_entry_t);

    /*
     * Build memory map in config area.
     *
     * The immap struct defines a few regions for the DPRAM.  They are
     * as follows:
     *  o im_dpram1 = first 16K.  MCC channel specific MUST live in
     *    here
     *  o res1 = next 16K.  Reserved in processor memory map.  Must not
     *    be used.
     *  o im_dpram2 = next 4K.  This region is reserved for parameter RAM
     *    for the various CCs.  Must not be used, except for parameters.
     *  o res2 = the immap says this is reserved, but the processor manual
     *    for an _8560_ will tell you it's not (I'm assuming it is on an 8260).
     *    This is the region I speak of below.
     *  o im_dpram3 = the next 4K.  This memory is reserved for FCC data.
     *
     * We have a couple of areas that aren't reserved for channel structs.
     * (those live in the first 16K of the DPRAM, so avoid using them if you
     * can).  Starting at offset 0x9000, there is 8K of memory available that
     * can _only_ be used for BDs and data.  So, we'll put the XTRABASE and
     * SCTPBASE in that region.
     */

    /*
     * First, we'll save off a pointer to the channel area for this MCC.
     * Don't blindly copy this for MCC2, thinking there's nothing to it.
     * MCC2 needs to be at this offset PLUS 8K.
     */
    mcc2.config.dpbase = (u32)(cpm2_immr->im_dpram1);

    /*
     * SCTPBASE:  This (if defined) must be 128 * sizeof(u16) bytes in size.
     */
    mcc2.config.sctpbase = offsetof(cpm2_map_t, res2) + MCC2_SCTP_OFF;
    mcc2.config.sctpbase = 0;

    /*
     * XTRABASE: This can be at most 256 * 8 bytes in size.  This is where
     * channel extra parameters will live.
     * We wipe the second 1K of this, as that's where the extra params
     * will be for MCC2.
     */
    mcc2.config.xtrabase = offsetof(cpm2_map_t, res2) + MCC_XTRA_OFF;
    memset((void *)(cpm2_immr->res2 + MCC_XTRA_OFF + 1024), 0, 1024);

    /*
     * The rest of the memory regions live in the regular address space
     * (not in the DP area).  These regions consist of
     *  o BD _table_ area.  The channel extra parameters contain half words
     *    that represent offsets in the bdbase region (the offsets are
     *    expressed as the offset of 8 byte double words.  The math shows
     *    that this can conceivably fill the 512K region allowed for mccbase
     *    (MAX_USHORT * sizeof(BD)), or 512K.
     *  o The interrupt table, which is basically an array of words as big
     *    as you want.  We'll use 64 entries per table, and we need 5 tables,
     *    so this is 1280 bytes.
     *  o The actual buffer areas themselves.  The do NOT have to be in the
     *    512K region.  The 512K region is simply for the BD tables, not the
     *    buffers they point to.
     *
     * Here's the key to the mccbase, and the BD tables:
     *  o 512K region.  This is a bit misleading.  Think of it as:
     *    mcc_channel_bd_t  bds[MAX_USHORT];
     *  o You need both TX and RX BD areas; assume for the sake of example
     *    that you split it down the middle:
     *    mcc_channel_bd_t  txbds[MAX_USHORT/2];
     *    mcc_channel_bd_t  rxbds[MAX_USHORT/2];
     *    (we actually lay them out sequentially, but this is merely an
     *    example).
     *  o This means you have 32K BDs for TX, 32K for RX.
     *  o You have a maximum of 128 channels allowed for each MCC.  This means
     *    your BD tables can be at most (using exponents here) 15 - 7 BD
     *    entries per channel, or 256, if you want to keep an equal allocation
     *    for all of your channels.  For pretty much any application that
     *    is overkill, unless you configure every possible channel.  So, we're
     *    going to assume 64 entries in each BD table per channel, or 128
     *    BDs total, which means we need (exponents again, and + 1 for TX/RX)
     *    6 + 1 + 7, or 2**14 entries, or 2**17 bytes, or 128K.  To put it
     *    another way, since we are only asking for a fourth of the possible
     *    BDs that we can have, we only need a fourth of the 512K allowed.
     *
     *    Note that all this is true of each MCC, since we have two.
     *    I'm writing this at 10pm with a buzz on, so forgive me if my math
     *    is off a hair.
     */
    /*
     * Allocate the BD table area.  The calculation represents how we get
     * the 128K requirement.  The "2" represents the combination of Tx and Rx.
     */
    mcc2.config.bdbase = (u32)kmalloc(MCC_MAX_CHAN_NORMAL * 2 *
                                          mcc2.config.bds_per *
                                          sizeof(mcc_channel_bd_t),
                                      GFP_KERNEL);
    if (mcc2.config.bdbase == 0)
    {
        printk("Can't allocate BD table region.\n");

        return;
    }
    memset((void *)mcc2.config.bdbase,
           0,
           MCC_MAX_CHAN_NORMAL * 2 *
               mcc2.config.bds_per * sizeof(mcc_channel_bd_t));

    /*
     * allocate the interrupt table area.  The calculation represents how
     * we get to the size.  The "5" represents one Tx table and 4 Rx tables.
     */
    mcc2.config.intbase = (u32)kmalloc(mcc2.config.intsize * 5,
                                       GFP_KERNEL);
    if (mcc2.config.intbase == 0)
    {
        printk("Can't allocate INT table region.\n");

        kfree((void *)mcc2.config.bdbase);

        return;
    }

    /*
     * allocate the buffer area.  The calculation represents how we get to
     * the size for this region.  Again, the "2" represents Tx/Rx.
     * This monster is ~ 4.5MB.
     */
    mcc2.config.bufbase = __get_free_pages(GFP_KERNEL, 8);
    if (mcc2.config.bufbase == 0)
    {
        printk("Can't allocate BUF region.\n");

        kfree((void *)mcc2.config.bdbase);
        kfree((void *)mcc2.config.intbase);

        return;
    }

    /*
     * Save the page and code off for issuing commands
     */
    mcc2.page = CPM_CR_MCC2_PAGE;
    mcc2.code = CPM_CR_MCC2_SBLOCK;

    /*
     * Wipe the control struct
     */
    memset(&mcc2_channels, 0,
           MCC_MAX_CHAN_SS7 * sizeof(mcc_channel_run_t));

    /*
     * Initialize the MCC
     */
    mcc_init(&mcc2,
             &cpm2_immr->im_mcc2,
             (mcc_global_param_t *)
                 &cpm2_immr->im_dpram2[CPM_CR_MCC2_PAGE << 8],
             &cpm2_immr->im_siramctl2,
             (u16 *)cpm2_immr->im_si2txram,
             (u16 *)cpm2_immr->im_si2rxram);
}

void
exit_mcc2()
{
    printk("exit_mcc2:\n");
    /* Disable all TDMs */
    mcc_disable_si(&mcc2);
    /* Disable IRQ */
    disable_irq(SIU_INT_MCC2);
    /* Unregsiter IRQ */
    free_irq(SIU_INT_MCC2, &mcc2);
    /* Free allocated memory */
    kfree((void *)mcc2.config.bdbase);
    kfree((void *)mcc2.config.intbase);

    free_page(mcc1.config.bufbase);

    /* Unmap the device */
    if (cpm2_immr)
    {
        iounmap(cpm2_immr);
        cpm2_immr = NULL;
    }
}

/*
 * Initialize the SS7 channels
 */
void
init_mcc2_channels(mcc_chan_config_t *channels, int nchan)
{
    mcc2.channels = mcc2_channels;

    mcc_init_channels(&mcc2, mcc2_channels, channels, nchan);

    enable_irq(SIU_INT_MCC2);
}

EXPORT_SYMBOL(mcc_enable_si);
EXPORT_SYMBOL(mcc_disable_si);
EXPORT_SYMBOL(mcc_send_data);

