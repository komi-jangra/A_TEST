/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: mtp2_cmn.h,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:45  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.4  2006/07/18 15:39:38  sjaddu
 * LOG: Fix for Issue Id : #3946, #3955
 * LOG:
 * LOG: Revision 9.1.8.3  2006/06/14 17:49:15  gdevanand
 * LOG: Commiting after mtp2 testing.
 * LOG:
 * LOG: Revision 9.1.8.1  2005/09/14 16:23:29  lbana
 * LOG: Added macros for MTP2 implementation. Defined by Mitch Miers.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:15  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/21 06:48:54  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.11  2001/12/11 23:50:19  mmiers
 * LOG: Redundant signal.
 * LOG:
 * LOG: Revision 5.10  2001/11/30 15:28:17  mmiers
 * LOG: Add a few commands.
 * LOG:
 * LOG: Revision 5.9  2001/10/05 22:59:15  mmiers
 * LOG: Update from working on NMS MTP2 API
 * LOG:
 * LOG: Revision 5.8  2001/09/28 21:32:32  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.7  2001/09/20 22:52:19  mmiers
 * LOG: Congestion addition
 * LOG:
 * LOG: Revision 5.6  2001/09/13 15:29:37  mmiers
 * LOG: Make all signals hex
 * LOG:
 * LOG: Revision 5.5  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.4  2001/09/06 17:24:39  mmiers
 * LOG: Closing in.
 * LOG:
 * LOG: Revision 5.3  2001/09/05 23:06:40  mmiers
 * LOG: Initial cut at an MTP2 interface.  Likely to change.
 * LOG:
 * LOG: Revision 5.2  2001/08/27 22:57:25  mmiers
 * LOG: More L2 signals.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/08/07 20:28:30  mmiers
 * LOG: Adjust common codes.
 * LOG:
 * LOG: Revision 4.5  2001/08/02 16:33:16  mmiers
 * LOG: Update signals.
 * LOG:
 * LOG: Revision 4.4  2001/08/01 21:51:07  mmiers
 * LOG: Add additional signals.
 * LOG:
 * LOG: Revision 4.3  2001/07/27 21:49:47  mmiers
 * LOG: Add MTP2 signals.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 *                 
 ****************************************************************************/

#if !defined(_ITS_MTP2_CMN_H_)
#define _ITS_MTP2_CMN_H_

#ident "$Id: mtp2_cmn.h,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $"

/*
 * fill this in (the header I think is family independent)
 */

/******************************** SIGNALS ***********************************/

#define MTP2_SIGNAL_DIR_BIT     (0x80)

#define MTP2_SIGNAL_FROM_L2(s)  (((s) & MTP2_SIGNAL_DIR_BIT) == 0)
#define MTP2_SIGNAL_TO_L2(s)    ((s) & MTP2_SIGNAL_DIR_BIT))

/*
 * NOTE:
 *
 * These codes MUST NOT overlap with the MTP3 message type codes.
 * MTP3 message types are allocated the range 0 - 64.
 * L2 to L3 are allocated 64-127.
 * L3 to L2 are allocated 128-255.
 */

/*
 * FROM L2
 */
#define L2_L3_IN_SERVICE                (0x41)
#define L2_L3_REMOTE_PROCESSOR_OUT      (0x42)
#define L2_L3_OUT_OF_SERVICE            (0x43)
#define L2_L3_REMOTE_PROCESSOR_REC      (0x44)
#define L2_L3_DATA                      (0x45)
#define L2_L3_BSNT                      (0x46)
#define L2_L3_BSNT_NOT_RETRIEVABLE      (0x47)
#define L2_L3_RETRIEVED_MSG             (0x48)
#define L2_L3_RETRIEVAL_COMPLETE        (0x49)
#define L2_L3_RETRIEVAL_NOT_POSSIBLE    (0x4A)
#define L2_L3_RB_CLEARED                (0x4B) /* Defined, used, NOP in MTP3 */
#define L2_L3_RTB_CLEARED               (0x4C) /* Defined, used, NOP in MTP3 */
#define L2_L3_CONGESTION_ONSET          (0x4D) /* Mentioned as FIXME in MTP3 */
#define L2_L3_CONGESTION_ABATES         (0x4E) /* Mentioned as FIXME in MTP3 */
#define L2_L3_CURRENT_TRACE             (0x4F)
#define L2_L3_CURRENT_CONFIG            (0x50)
#define L2_L3_CURRENT_PEGS              (0x51)
#define L2_L3_TRACE_DATA                (0x52)

/*
 * TO L2
 */
#define L3_L2_START                     (0x80)
#define L3_L2_STOP                      (0x81)
#define L3_L2_RESUME                    (0x82)
#define L3_L2_CLEAR_BUFFERS             (0x83)
#define L3_L2_CLEAR_RTB                 (0x84) /* Used, but as alias above */
#define L3_L2_EMERGENCY                 (0x85)
#define L3_L2_EMERGENCY_CEASE           (0x86)
#define L3_L2_DATA                      (0x87)
#define L3_L2_RETRIEVE_BSNT             (0x88)
#define L3_L2_RETRIEVE_MSGS             (0x89)
#define L3_L2_FLOW_CONTROL_START        (0x8A) /* sent to MTP2 on CONG_ONSET */
#define L3_L2_FLOW_CONTROL_STOP         (0x8B) /* sent to MTP2 on CONG_ABATE */
#define L3_L2_LOCAL_PROCESSOR_OUT       (0x8C)
#define L3_L2_LOCAL_PROCESSOR_REC       (0x8D)
#define L3_L2_GET_TRACE                 (0x8E)
#define L3_L2_SET_TRACE                 (0x8F)
#define L3_L2_GET_CONFIG                (0x90)
#define L3_L2_SET_CONFIG                (0x91)
#define L3_L2_GET_PEGS                  (0x92)
#define L3_L2_RESET_PEGS                (0x93)


/*
 * This one says L3 to L1.  I suspect L2 needs to know.
 */
#define L3_L2_CONNECT                   (0x94)
#define L3_L2_DISCONNECT                (0x95)

/* New Hash Defs for MTP2 Satellite support */
#define L3_L2_GET_PEGS_NEW              (0x96)
#define L3_L2_GET_CONFIG_NEW            (0x97)
#define L3_L2_SET_CONFIG_NEW            (0x98)
#define L3_L2_RESET_PEGS_NEW            (0x99)

/*
 * the format of a message to/from L2
 * data[0]   - signal
 * data[1]   - link set
 * data[2]   - link code
 * data[3-n] - message
 */
#define L2_MSG_TYPE(ev)     ((ev)->data[0])
#define L2_LINK_SET(ev)     ((ev)->data[1])
#define L2_LINK_CODE(ev)    ((ev)->data[2])
#define L2_LINK_DATA(ev)    (&(ev)->data[3])

/*
 * When implementing MTP2, you need to know about
 * these
 */
#define MTP2_STAT_O         0x00U /* Out of alignment */
#define MTP2_STAT_N         0x01U /* Normal alignment */
#define MTP2_STAT_E         0x02U /* Emergency alignment */
#define MTP2_STAT_OS        0x03U /* Out of service */
#define MTP2_STAT_PO        0x04U /* Processor outage */
#define MTP2_STAT_B         0x05U /* Congestion */

/*
 * Once a signal hits the TB or RTB, the meaning of the first three
 * bytes changes.  They are reused as the MTP2 header.  Adjusting
 * the size of a transfer to compensate is necessary when passing data.
 */
#define MTP2_FIXED_HDR_SIZE (3 * sizeof(ITS_OCTET))

/*
 * Configuration data
 */
typedef struct
{
    ITS_OCTET pad[sizeof(ITS_UINT) - MTP2_FIXED_HDR_SIZE];
    ITS_UINT T1;	/* Value of Timer "Alignment Ready" */
    ITS_UINT T2;	/* Value of Timer "Not Aligned" */
    ITS_UINT T3;	/* Value of Timer "Aligned" */
    ITS_UINT T4;	/* Value of Timer "Proving Period" */
    ITS_UINT T5;	/* Value of Timer "Sending SIB" */
    ITS_UINT T6;	/* Value of Timer "Remote Congestion" */
    ITS_UINT T7;	/* Value of Timer "Excessive Delay of Ack" */
    ITS_UINT Pn;	/* Emergency Proving Period */
    ITS_UINT Pe;	/* Normal Proving Period */
    ITS_BOOLEAN PCR;	/* PCR Flag Enabled (1) or Disabled (0) */
    ITS_OCTET rcOnset;	/* Rx side Congestion Onset Threshold */
    ITS_OCTET rcAbates;	/* Rx side Congestion Abates Threshold */
    ITS_OCTET txOnset1; /* Tx side Congestion level1 Onset Threshold */
    ITS_OCTET txOnset2; /* Tx side Congestion level2 Onset Threshold */
    ITS_OCTET txOnset3; /* Tx side Congestion level3 Onset Threshold */
    ITS_OCTET txAbates1; /* Tx side Congestion level1 Abates Threshold */
    ITS_OCTET txAbates2; /* Tx side Congestion level2 Abates Threshold */
    ITS_OCTET txAbates3; /* Tx side Congestion level3 Abates Threshold */
}
MTP2_ConfigData;





/*
 * Link Performance Statistics Data Structure
 */
typedef struct
{
    unsigned int SLFail_abnormBSNR;  /* link failures due to abn BSNR */
    unsigned int SLFail_abnormFIBR;  /* link failures due to abn FIBR */
    unsigned int SLFail_T7;      /* link failures due to T7 Expiry */
    unsigned int SLFail_suerm;   /* link failures due to SUERM */
    unsigned int SLFail_cong;    /* link failures due to T6 Expiry */
    unsigned int ALFail_T2T3;    /* alignment failures due to T2 or T3 */
    unsigned int ALFail_aerm;    /* alignment failures due to aerm */
    unsigned int numNegAck;      /* Number of Negative Acks */
    unsigned int numErrSu;       /* Number of SUs in error */
    unsigned int SIBtx;          /* SIBs Tx'd */
    unsigned int SIBrx;          /* SIBs Rx'd */
    unsigned int N1rtx;          /* Number of Retransmissions due to N1 */
    unsigned int N2rtx;          /* Number of Retransmissions due to N2 */
    unsigned int MSUrtx;         /* Number of MSUs Retransmitted */
    unsigned int MSUrtx_octets;  /* Number of MSU Octets Retransmitted */
    unsigned int MSUhsrx;        /* Number of MSUs Rx'd from MTP3 */
    unsigned int MSUhstx;        /* Number of MSUs Tx'd to MTP3 */
    unsigned int MSUrx;          /* Number of MSUs Rx'd from MCC */
    unsigned int MSUtx;          /* Number of MSUs Tx'd to MCC */
    unsigned int MSUtx_octets;   /* Number of MSU octets Tx'd to MCC */
    unsigned int MSUrx_octets;   /* Number of MSU octets Rx'd from MCC */
    unsigned int RQThresCross;   /* Number of times RQ crossed threshold */
    unsigned int TQThresCross;   /* Number of times TQ crossed threshold */
    unsigned int TBThresCross;   /* Number of times TB crossed threshold */
    unsigned int RTBThresCross;  /* Number of times RTB crossed threshold */
}
MTP2_PerfData;









/*
 * Stats
 */
#define MTP2_MAX_STATS 20
#define MTP2_STAT_TX_CNT      0
#define MTP2_STAT_RX_CNT      1
#define MTP2_STAT_RX_BAD_LEN  2
#define MTP2_STAT_NON_ALIGN   3
#define MTP2_STAT_ABORT       4
#define MTP2_STAT_CRC_ERROR   5
#define MTP2_STAT_RX_OVERFLOW 6
typedef struct
{
    ITS_OCTET pad[sizeof(ITS_LONG) - MTP2_FIXED_HDR_SIZE];
    ITS_LONG  peg[MTP2_MAX_STATS];
}
MTP2_StatsData;

/*
 * Trace.  The indices of the level is exactly that defined in its_trace.h
 */
#define MTP2_MAX_TRACE_LEVELS   5
typedef struct
{
    ITS_OCTET traceOnOff[MTP2_MAX_TRACE_LEVELS];
}
MTP2_TraceData;

/*
 * BIG FAT FIXME: MTP2_MAX_MSG_SIZE is defined as 4K, to handle the case
 * when SAAL links are being used.
 *
 * This is massive overkill.  I'm pretty sure I'm the one who did it, and
 * I ought to be shot.
 *
 * In the Linux kernel, this will explode the kernel stack.  A different
 * define is needed (TEMPORARILY).
 *
 * FIXME: Change MTP2_MAX_MSG_SIZE to depend on whether SAAL is present
 * or not.  It might be nice to mix them (decide at run time).
 */
#define MTP2_MAX_DRIVER_BYTES     300 

/*
 * MTP2 signal transfer
 */
typedef struct
{
    ITS_OCTET signal;   /* AKA: BSN in the driver */
    ITS_OCTET linkSet;  /* AKA: FSN in the driver */
    ITS_OCTET linkCode; /* AKA: LI  in the driver */
    union
    {
        ITS_OCTET       sif[MTP2_MAX_DRIVER_BYTES]; /* SIO onwards */
        ITS_OCTET       bsnt;
        MTP2_TraceData  traceData;
    }
    data;
}
MTP2_Signal;

#define MTP2_SIGNAL_BSNT(x) (((MTP2_Signal *)x)->data.bsnt)
/*
 * Only matters when using our MTP2 device
 */
#ifdef INTELLI_MTP2
#ifdef linux

#include <linux/ioctl.h>

#define MTP2_IOC_MAGIC 252  /* Same as device number as of now */

#define MTP2_IOCRESET    _IO(MTP2_IOC_MAGIC, 0)

#define MTP2_IOCSCONFIG  _IOW(MTP2_IOC_MAGIC, 1, int)

#define MTP2_IOCENABLE   _IO(MTP2_IOC_MAGIC, 2)
#define MTP2_IOCDISABLE  _IO(MTP2_IOC_MAGIC, 3)
#define MTP2_IOCTSEND    _IO(MTP2_IOC_MAGIC, 4)
#define MTP2_IOCTDUMP    _IO(MTP2_IOC_MAGIC, 5)

/*
 * struct for configuration
 */
struct mtp2_cfg
{
    unsigned int num_chan;
    struct mtp2_channel
    {
        unsigned char  chan;  /* Which channel index.             */
        unsigned char  mode; /* For superchannel.  Not used here */
        unsigned char  type; /* Channel type.  Here always SS7   */
        unsigned char  loop;  /* Loopback or not (simple boolean) */
    }
    channels[1];   /* At least 1.  Up to 32            */
};

/*
 * Things we need to know.
 */
#define MTP2_MAJOR        252  /* Device major.  MAX_LINKS minors   */
#define MTP2_CTL_MINOR    252  /* Misc major, this is the minor     */
#define MTP2_MAX_LINKS    32   /* Maximum number of links per board */

/* Temporarily keep them here */
#define MCC_TYPE_SS7   0
#define MCC_TYPE_HDLC  1
#define MCC_TYPE_TRANS 2

#endif /* linux */
#endif /* INTELLI_MTP2 */

#endif /* _ITS_MTP2_CMN_H_ */

