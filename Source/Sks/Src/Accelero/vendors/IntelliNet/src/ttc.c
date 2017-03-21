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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: ttc.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:36  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:11  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.1  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.4.1  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 1.1.2.1  2004/10/26 00:23:54  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#include <its.h>
#include <its_object.h>
#include <its_ss7_trans.h>

#ident "$Id: ttc.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

#undef ANSI
#undef CCITT
#define CCITT
#if !defined(SPLIT_STACK) && !defined(USE_ITU_SCCP)
#include <itu/tcap.h>
#endif
#include <itu/isup.h>
#if !defined(SPLIT_STACK) && !defined(USE_ANSI_SCCP)
#include <ansi/tcap.h>
#endif
#include <ansi/isup.h>

#include <vframe.h>

/*
 * layer functions
 */
extern int IMTP3_Initialize_CCITT(ITS_SS7_HANDLE);
extern int IISUP_Initialize_CCITT(ITS_SS7_HANDLE);
extern int ISCCP_Initialize_CCITT(ITS_SS7_HANDLE);
extern int ITCAP_Initialize_ANSI(ITS_SS7_HANDLE);
extern int ITCAP_Initialize_CCITT(ITS_SS7_HANDLE);
extern int IMTP3_Terminate_CCITT(ITS_SS7_HANDLE);
extern int IISUP_Terminate_CCITT(ITS_SS7_HANDLE);
extern int ISCCP_Terminate_CCITT(ITS_SS7_HANDLE);
extern int ITCAP_Terminate_ANSI(ITS_SS7_HANDLE);
extern int ITCAP_Terminate_CCITT(ITS_SS7_HANDLE);

extern int INTELLINET_SendMTP3Event_CCITT(ITS_SS7_HANDLE handl,
                                          ITS_OCTET type,
                                          MTP3_HEADER_CCITT *mtp3,
                                          ITS_OCTET *buf, ITS_USHORT len);
extern int INTELLINET_ReserveCIC_CCITT(ITS_SS7_HANDLE handle,
                                        ITS_OCTET sio,
                                        ITS_UINT opc, ITS_UINT dpc,
                                        ITS_USHORT cic,
                                        ITS_OCTET *status, ITS_CTXT *vcic);
extern int INTELLINET_UnReserveCIC_CCITT(ITS_SS7_HANDLE handle,
                                        ITS_OCTET sio,
                                        ITS_UINT opc, ITS_UINT dpc,
                                        ITS_USHORT cic);
extern int INTELLINET_SendISUPEvent_CCITT(ITS_HANDLE handle, ITS_OCTET type,
                                          ITS_HDR *hdr,
                                          ITS_ISUP_IE *ies, int ieCount,
                                          ISUP_MSG_DESC *desc);
extern int INTELLINET_ReceiveISUPEvent_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE *ies, int *ieCount,
                                             ISUP_MSG_DESC *desc);
extern int INTELLINET_SendSCCPEvent_CCITT(ITS_HANDLE handle, ITS_OCTET type,
                                          ITS_HDR *hdr,
                                          ITS_SCCP_IE *ies, int ieCount,
                                          SCCP_MSG_DESC* desc);
extern int INTELLINET_SendUOS_CCITT(ITS_HANDLE handle, ITS_OCTET ni,
                                    ITS_UINT pc, ITS_OCTET ssn);
extern int INTELLINET_SendUIS_CCITT(ITS_HANDLE handle, ITS_OCTET ni,
                                    ITS_UINT pc, ITS_OCTET ssn);
extern int INTELLINET_SetCongestion_CCITT(ITS_HANDLE handle, ITS_OCTET ni,
                                          ITS_UINT pc, ITS_OCTET ssn,
                                          ITS_OCTET cong);
extern int INTELLINET_GetSCCPNextRef_CCITT(ITS_SS7_HANDLE handle,
                                                ITS_CTXT *cref);
extern int INTELLINET_SendComp_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_CPT *cpt);
extern int INTELLINET_SendComp_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_CPT *cpt);
extern int INTELLINET_SendDlg_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                   TCAP_DLG *dlg);
extern int INTELLINET_SendDlg_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                    TCAP_DLG *dlg);
extern int INTELLINET_AllocateDID_ANSI(ITS_SS7_HANDLE handle,
                                       ITS_CTXT *did);
extern int INTELLINET_AllocateDID_CCITT(ITS_SS7_HANDLE handle,
                                        ITS_CTXT *did);
extern int INTELLINET_FetchAddrs_ANSI(ITS_SS7_HANDLE handle,
                                      ITS_CTXT did,
                                      SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_FetchAddrs_CCITT(ITS_SS7_HANDLE handle,
                                       ITS_CTXT did,
                                       SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_SetAddrs_ANSI(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did,
                                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_SetAddrs_CCITT(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did,
                                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
extern int INTELLINET_FetchQOS_ANSI(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_FetchQOS_CCITT(ITS_SS7_HANDLE handle,
                                     ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_SetQOS_ANSI(ITS_SS7_HANDLE handle,
                                  ITS_CTXT did, DLG_QOS *qos);
extern int INTELLINET_SetQOS_CCITT(ITS_SS7_HANDLE handle,
                                   ITS_CTXT did, DLG_QOS *qos);


/*
 * undocumented
 */
ITSDLLAPI extern ITS_UINT ITS_SS7_Mask;

/*
 * stack record.
 */
ITSSS7DLLAPI SS7TRAN_Manager* ISS7_TTC_Stack = NULL;

/*
 * class init.
 */
static int
ClassInit(ITS_Class objClass)
{
    /*
     * plug the superclass hole.
     */
    ITS_CLASS_SUPERCLASS(itsINTELLISS7_ClassTTC) = itsSS7STACK_ClassTTC;

    /*
     * create the TTC stack instance
     */
    ISS7_TTC_Stack = (SS7TRAN_Manager *)calloc(1, sizeof(SS7TRAN_Manager));
    if (ISS7_TTC_Stack == NULL)
    {
        return (ITS_ENOMEM);
    }

    /*
     * initialize the relevent mechanisms.
     */
    TRANSPORT_MASK(ISS7_TTC_Stack) = ITS_SS7_Mask;
    SS7TRAN_SUBORDINATE(ISS7_TTC_Stack) =
        (SS7STACK_ClassRec *)itsINTELLISS7_ClassTTC;

    /*
     * invoke the initialize method (note that we're calling
     * the constructor from it's own ClassInit).
     */
    SS7TRAN_HANDLE(ISS7_TTC_Stack) =
        ITS_ConstructObject(itsINTELLISS7_ClassTTC, ISS7_TTC_Stack);

    if (SS7TRAN_HANDLE(ISS7_TTC_Stack) == NULL)
    {
        free(ISS7_TTC_Stack);
        ISS7_TTC_Stack = NULL;

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*
 * class destroy
 */
static void
ClassDest(ITS_Class objClass)
{
    if (ISS7_TTC_Stack)
    {
        if (SS7TRAN_HANDLE(ISS7_TTC_Stack))
        {
            ITS_DestructObject(SS7TRAN_HANDLE(ISS7_TTC_Stack));
        }

        free(ISS7_TTC_Stack);

        ISS7_TTC_Stack = NULL;
    }
}

/*
 * the TTC stack class record
 */
ITSSS7DLLAPI VENDOR_ClassRec itsINTELLISS7_ClassRecTTC =
{
    /* core part */
    {
        NULL,                           /* no superclass in a DLL */
        sizeof(VENDOR_Instance),        /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        INTELLISS7_CLASS_NAME "TTC",    /* class name */
        ClassInit,                      /* class init */
        ClassDest,                      /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* stack part */
    {
        NULL,                           /* get next */
        NULL,                           /* peek next */
        NULL                            /* put */
    },
    /* vendor part */
    {
        NULL,                               /* no load resources */
        NULL,                               /* no await indication */
        /* MTP2 */
        {
            NULL,                           /* no initialize */
            NULL,                           /* no terminate */
            NULL,                           /* no retrieve */
            NULL                            /* no send */
        },
        /* MTP3 */
        {
            IMTP3_Initialize_CCITT,         /* initialize */
            IMTP3_Terminate_CCITT,          /* terminate */
            NULL,                           /* no retrieve */
            NULL,                           /* no send ANSI */
            INTELLINET_SendMTP3Event_CCITT, /* send CCITT */
            NULL                            /* no send TTC */
        },
        /* ISUP */
        {
            IISUP_Initialize_CCITT,         /* initialize */
            IISUP_Terminate_CCITT,          /* terminate */
            INTELLINET_ReserveCIC_CCITT,   /* getCIC */
            INTELLINET_UnReserveCIC_CCITT,    /* unserveCIC */
            NULL,                           /* no retrieve ANSI */
            INTELLINET_ReceiveISUPEvent_CCITT, /* retrieve */
            NULL,                           /* no send ANSI */
            INTELLINET_SendISUPEvent_CCITT, /* send event */
        },
        /* SCCP */
        {
            ISCCP_Initialize_CCITT,         /* initialize */
            ISCCP_Terminate_CCITT,          /* terminate */
            INTELLINET_GetSCCPNextRef_CCITT,/* getRef */
            NULL,                           /* no retrieve */
            INTELLINET_SendSCCPEvent_CCITT, /* send */
            INTELLINET_SendUOS_CCITT,       /* UOS */
            INTELLINET_SendUIS_CCITT,       /* UIS */
            INTELLINET_SetCongestion_CCITT  /* setCong */
        },
        /* TCAP */
        {
#if defined(SPLIT_STACK)
            ITCAP_Initialize_ANSI,          /* initialize */
            ITCAP_Terminate_ANSI,           /* terminate */
            INTELLINET_AllocateDID_ANSI,    /* getDID */
            NULL,                           /* no retrieve */
            INTELLINET_SendComp_ANSI,       /* sendCmp */
            INTELLINET_SendDlg_ANSI,        /* sendDlg */
            INTELLINET_FetchAddrs_ANSI,     /* fetchAddrs */
            INTELLINET_SetAddrs_ANSI,       /* setAddrs */
            INTELLINET_FetchQOS_ANSI,       /* fetchQOS */
            INTELLINET_SetQOS_ANSI,         /* setQOS */
            NULL,                           /* no UOS */
            NULL,                           /* no UIS */
            NULL                            /* no set congestion */
#else
            ITCAP_Initialize_CCITT,         /* initialize */
            ITCAP_Terminate_CCITT,          /* terminate */
            INTELLINET_AllocateDID_CCITT,   /* getDID */
            NULL,                           /* no retrieve */
            INTELLINET_SendComp_CCITT,      /* sendCmp */
            INTELLINET_SendDlg_CCITT,       /* sendDlg */
            INTELLINET_FetchAddrs_CCITT,    /* fetchAddrs */
            INTELLINET_SetAddrs_CCITT,      /* setAddrs */
            INTELLINET_FetchQOS_CCITT,      /* fetchQOS */
            INTELLINET_SetQOS_CCITT,        /* setQOS */
            NULL,                           /* no UOS */
            NULL,                           /* no UIS */
            NULL                            /* no set congestion */
#endif
        }
    }
};

ITSSS7DLLAPI ITS_Class itsINTELLISS7_ClassTTC =
    (ITS_Class)&itsINTELLISS7_ClassRecTTC;
