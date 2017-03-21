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
 *  ID: $Id: ansi-tcap_cvt.c,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:56  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:54  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:30  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:36  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4  2003/02/06 10:19:44  vjatti
 * LOG: PR 6.2 Fixes propagated
 * LOG:
 * LOG: Revision 7.3  2003/01/07 15:26:07  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2002/09/16 18:37:49  mmiers
 * LOG: Add U-ABORT for ANSI
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.7  2002/08/15 19:41:00  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.6  2002/07/30 19:50:10  mmiers
 * LOG: What to do when param is empty
 * LOG:
 * LOG: Revision 6.5  2002/07/09 14:30:36  omayor
 * LOG: ANSI-96 changes tested in PR5 ported to current. Now to be tested.
 * LOG:
 * LOG: Revision 6.4  2002/06/24 18:50:20  mmiers
 * LOG: Test ANSI encode/decode.
 * LOG:
 * LOG: Revision 6.3  2002/06/10 21:38:55  mmiers
 * LOG: Add ANSI dialogue portion.
 * LOG:
 * LOG: Revision 6.2  2002/03/20 20:07:48  mmiers
 * LOG: Move the ASNC library to the VFrame (as on UNIX).
 * LOG:
 * LOG: Revision 6.1  2002/03/20 17:56:24  mmiers
 * LOG: Move the codecs back.  It's consistent, so I'll just deal
 * LOG: with the VFrame pain (ASN).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/12/19 18:03:02  mmiers
 * LOG: Adax testing on Solaris revealed several build flaws.
 * LOG:
 * LOG: Revision 5.1  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:50:49  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:44  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/06/08 14:27:06  mmiers
 * LOG:
 * LOG:
 * LOG: Forgot REJECT param on decode.
 * LOG:
 * LOG: Revision 2.2  2000/03/23 20:21:30  mmiers
 * LOG:
 * LOG:
 * LOG: Final IntelliSS7 changes from Plano.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:28  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:07  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/08/19 22:33:12  mmiers
 * LOG:
 * LOG:
 * LOG: Remove dead parameter.
 * LOG:
 * LOG: Revision 1.3  1999/06/15 22:41:41  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build for function signatures, predefines.
 * LOG:
 * LOG: Revision 1.2  1999/06/01 17:20:16  labuser
 * LOG:
 * LOG:
 * LOG: remove berkeley byte functions.
 * LOG:
 * LOG: Revision 1.1  1999/05/24 20:25:45  mmiers
 * LOG:
 * LOG:
 * LOG: Move the codec into the library for sharing.
 * LOG:
 * LOG: Revision 1.3  1999/04/09 15:45:57  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks to address check.  Update TODO
 * LOG:
 * LOG: Revision 1.2  1999/03/17 21:37:49  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:44  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.6  1999/02/26 04:10:22  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.5  1999/02/17 20:45:27  mmiers
 * LOG:
 * LOG:
 * LOG: Get ITU conversion to compile.
 * LOG:
 * LOG: Revision 1.4  1998/11/19 01:32:15  mmiers
 * LOG: Build with warning at max.  5 bugs found.
 * LOG:
 * LOG: Revision 1.3  1998/10/21 20:32:40  mmiers
 * LOG: Use forward slash in include so UNIX understands.
 * LOG:
 * LOG: Revision 1.2  1998/10/21 18:29:40  mmiers
 * LOG: Update vendor to use compiler directly
 * LOG:
 * LOG: Revision 1.1  1998/09/24 19:24:40  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.9  1998/08/13 00:57:21  whu
 * LOG: ECI for error, NOT OCI.
 * LOG:
 * LOG: Revision 1.8  1998/08/13 00:46:16  whu
 * LOG: Type conversions to int must use signed types to avoid extra (nul) bytes
 * LOG: in a 1 or 2 character wide integer.
 * LOG:
 * LOG: Add length in to error code.
 * LOG:
 * LOG: Revision 1.7  1998/08/10 15:05:19  whu
 * LOG: The Return Error used OCI instead of ECI
 * LOG:
 * LOG: Revision 1.6  1998/07/17 16:27:12  ahanda
 * LOG: Correct logic for TIDs where local end did NOT originate the transaction.
 * LOG:
 * LOG: Revision 1.5  1998/07/01 22:15:35  mmiers
 * LOG: Remove stub crap needed for obsolete PSAP mess.
 * LOG:
 * LOG: Revision 1.4  1998/06/25 15:27:01  ahanda
 * LOG: HLR debugging fixes.
 * LOG:
 * LOG: Revision 1.3  1998/06/19 22:25:27  mmiers
 * LOG: Nearing the end for TCAP.  Initial implementation of SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 23:38:43  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:30  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.14  1998/06/16 21:52:08  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.13  1998/05/31 22:20:12  mmiers
 * LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
 * LOG: Solaris.
 * LOG:
 * LOG: Revision 1.12  1998/05/19 21:27:42  mmiers
 * LOG: Almost finished with TCAP++.
 * LOG:
 * LOG: Revision 1.11  1998/05/19 02:38:50  mmiers
 * LOG: Modify itu/tcap.h to remove the redundant structures (such as rrl/rrnl,
 * LOG: uerror/lerror, etc.).  If you have problems with this, update tcap.h
 * LOG: using "cvs update -r 1.11 tcap.h (for itu/tcap.h).
 * LOG:
 * LOG: Revision 1.10  1998/05/05 01:59:00  mmiers
 * LOG: Sanitize the build environment a bit.  This gets the Solaris
 * LOG: environment to build cleanly.
 * LOG:
 * LOG: Revision 1.9  1998/04/29 21:10:18  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.8  1998/04/29 00:23:16  mmiers
 * LOG: Start putting in context functions.  Should be starting debug
 * LOG: tommorrow.
 * LOG:
 * LOG: Revision 1.7  1998/04/28 22:51:59  mmiers
 * LOG: Complete the pepsy<->ITS conversion code.  This is pretty close to
 * LOG: actually working, now.  Must fill in the context management functions
 * LOG: and then debug.
 * LOG:
 * LOG: Revision 1.6  1998/04/27 20:00:23  mmiers
 * LOG: Get trace working (portably).  More work on TCAP.
 * LOG:
 * LOG: Revision 1.5  1998/04/23 23:53:52  mmiers
 * LOG: More work on TCAP.  Down to about 30 fixme's.
 * LOG:
 * LOG: Revision 1.4  1998/04/23 17:04:02  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.3  1998/04/16 16:40:02  mmiers
 * LOG: Build on NT, reduce error count.  Need to finish this.
 * LOG:
 * LOG: Revision 1.2  1998/03/19 16:34:37  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#ident "$Id: ansi-tcap_cvt.c,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $"

#include <ansi/sccp.h>
#include <ansi/tcap.h>

#include <stdlib.h>

#define TID_TO_DATA(d,t)                    \
    ((d)[0] = (char)(((t) >> 24) & 0xFFU),  \
     (d)[1] = (char)(((t) >> 16) & 0xFFU),  \
     (d)[2] = (char)(((t) >> 8) & 0xFFU),   \
     (d)[3] = (char)((t) & 0xFFU))
#define DATA_TO_TID(d,t) \
    ((t) = ((d)[0] << 24) | ((d)[1] << 16) | ((d)[2] << 8) | (d)[3])

/*
 * local use
 */
SS7DLLAPI ITS_OCTET ANSI_EmptyParam[2] = { 0xF2U, 0x00U };
SS7DLLAPI ITS_UINT  ANSI_EmptyParamLen = sizeof(ANSI_EmptyParam);
SS7DLLAPI ITS_OCTET ANSI_EmptyAbort[2] = { 0xD8U, 0x00U };
SS7DLLAPI ITS_UINT  ANSI_EmptyAbortLen = sizeof(ANSI_EmptyAbort);

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
QBufToStr(struct qbuf *q, char *buf, int *iolen)
{
    int    len;
    char   *d;
    struct qbuf   *p;

    *buf = 0;
    p = q->qb_forw;
    len = 0;
    do
    {
        len += p->qb_len;

        p = p->qb_forw;
    }
    while (p != q);

    q->qb_len = len;

    if (len > *iolen)
    {
        *iolen = 0;

        return;
    }

    d = buf;
    *iolen = len;

    p = q->qb_forw;
    do
    {
        memcpy(d, p->qb_data, p->qb_len);
        d += p->qb_len;

        p = p->qb_forw;
    }
    while (p != q);

    *d = 0;

    return;
}

struct type_ANSI__TCAP_DialoguePortion*
BuildDialoguePortion(ITS_OCTET *applicationContext, ITS_USHORT acLen,
                     ITS_OCTET *userInformation, ITS_USHORT uiLen,
                     ITS_OCTET *security, ITS_USHORT securityLen,
                     ITS_OCTET *confidentiality, ITS_USHORT confidentialityLen,
                     ITS_BOOLEAN includePV)
{
    int err;
    PE ac;
    PE ui;
    struct type_ANSI__TCAP_DialoguePortion* dlg;

    if (acLen == 0 && uiLen == 0 && (!includePV))
    {
        return (NULL);
    }

    dlg = (struct type_ANSI__TCAP_DialoguePortion *)
        calloc(1, sizeof(struct type_ANSI__TCAP_DialoguePortion));

    if (dlg == NULL)
    {
        return (NULL);
    }

    /* protocol version */
    if (includePV)
    {
        dlg->protocolVersion = str2qb("\001", 1, 0);
    }

    /* application context */
    if (acLen)
    {
        ac = ssdu2pe((char *)applicationContext, acLen, NULL, &err);

        if (err != PS_ERR_NONE)
        {
            free(dlg);

            return (NULL);
        }

        if (decode_ANSI__TCAP_ApplicationContext(ac, 1, NULL, NULL,
                                                       (char **)&dlg->
                                                        applicationContext) ==
            NOTOK)
        {
            if (ac)
            {
                pe_free(ac);
            }
            free(dlg);

            return (NULL);
        }
    }

    /* user information */
    if (uiLen)
    {
        ui = ssdu2pe((char *)userInformation, uiLen, NULL, &err);

        if (err != PS_ERR_NONE)
        {
            if (dlg->applicationContext)
            {
                free_ANSI__TCAP_ApplicationContext(dlg->applicationContext);
            }
            free(dlg);

            return (NULL);
        }

        if (decode_ANSI__TCAP_UserInformation(ui, 1, NULL, NULL,
                                                    (char **)&dlg->
                                                        userInformation) ==
            NOTOK)
        {
            if (dlg->applicationContext)
            {
                free_ANSI__TCAP_ApplicationContext(dlg->applicationContext);
            }
            free(dlg);

            return (NULL);
        }
    }

    return (dlg);
}

static ITS_BOOLEAN
ParseDialoguePortion(struct type_ANSI__TCAP_DialoguePortion* dlg,
                     ITS_OCTET *applicationContext, ITS_USHORT *acLen,
                     ITS_OCTET *userInformation, ITS_USHORT *uiLen,
                     ITS_OCTET *securityInfo, ITS_USHORT *secLen,
                     ITS_OCTET *confInfo, ITS_USHORT *confLen,
                     ITS_BOOLEAN *hasPV)
{
    int tval;
    PE ac;
    PE ui;
    char *tmp;

    *acLen = 0;
    *uiLen = 0;
    *hasPV = ITS_FALSE;

    if (dlg == NULL)
    {
        return (ITS_TRUE);
    }

    /* protocol version */
    if (dlg->protocolVersion != NULL)
    {
        *hasPV = ITS_TRUE;
    }

    /* application context */
    if (dlg->applicationContext)
    {
        if (encode_ANSI__TCAP_ApplicationContext(&ac, 1, 0, NULL,
                                                       (char *)dlg->applicationContext)
            == NOTOK)
        {
            free_ANSI__TCAP_DialoguePortion(dlg);

            return (ITS_FALSE);
        }
        if (pe2ssdu(ac, &tmp, &tval) != OK)
        {
            free_ANSI__TCAP_DialoguePortion(dlg);

            return (ITS_FALSE);
        }

        *acLen = (ITS_USHORT)tval;
        memcpy(applicationContext, tmp, tval);

        if (tval)
        {
            free(tmp);
        }

        pe_free(ac);
    }

    /* user information */
    if (dlg->userInformation)
    {
        if (encode_ANSI__TCAP_UserInformation(&ui, 1, 0, NULL,
                                                    (char *)dlg->userInformation)
            == NOTOK)
        {
            free_ANSI__TCAP_DialoguePortion(dlg);

            return (ITS_FALSE);
        }

        if (pe2ssdu(ui, &tmp, &tval) != OK)
        {
            free_ANSI__TCAP_DialoguePortion(dlg);

            return (ITS_FALSE);
        }

        *uiLen = (ITS_USHORT)tval;

        memcpy(userInformation, tmp, tval);

        pe_free(ui);

        if (tval)
        {
            free(tmp);
        }
    }

    return (ITS_TRUE);
}

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI struct type_ANSI__TCAP_ComponentPDU *
TCAP_CvtCPTToComponentPDU_ANSI(TCAP_CPT *cpt)
{
    struct type_ANSI__TCAP_ComponentPDU *ret;

    /* allocate the component */
    ret = (struct type_ANSI__TCAP_ComponentPDU *)
         calloc(1, sizeof(struct type_ANSI__TCAP_ComponentPDU));
    if (ret == NULL)
    {
        return ret;
    }

    switch (cpt->ptype)
    {
    case TCPPT_TC_INVOKE:
        ret->offset = type_ANSI__TCAP_ComponentPDU_invoke;

        /* allocate the invoke */
        ret->un.invoke = (struct type_ANSI__TCAP_Invoke *)
            calloc(1, sizeof(struct type_ANSI__TCAP_Invoke));
        if (ret == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* allocate the componentID */
        ret->un.invoke->componentID = (struct type_ANSI__TCAP_ComponentID *)
            calloc(1, sizeof(struct type_ANSI__TCAP_ComponentID) + 2);
        if (ret == NULL)
        {
            free(ret->un.invoke);
            free(ret);

            return (NULL);
        }
        /* copy in the invoke info */
        ret->un.invoke->componentID->qb_data = 
            ret->un.invoke->componentID->qb_base;

        ret->un.invoke->componentID->qb_data[0] =
            cpt->u.invoke.invoke_id.data[2];
        if (cpt->u.invoke.correlation_id.len != 0)
        {
            ret->un.invoke->componentID->qb_data[1] =
                cpt->u.invoke.correlation_id.data[2];
            ret->un.invoke->componentID->qb_len = 2;
        }
        else
        {
            ret->un.invoke->componentID->qb_len = 1;
        }
        /* link up the qbufs */
    	ret->un.invoke->componentID->qb_forw = ret->un.invoke->componentID;
        ret->un.invoke->componentID->qb_back = ret->un.invoke->componentID;

        /* allocate the operationCode */
        ret->un.invoke->operationCode =
            (struct type_ANSI__TCAP_OperationCode *)
            calloc(1, sizeof(struct type_ANSI__TCAP_OperationCode));
        if (ret == NULL)
        {
            free(ret->un.invoke->componentID);
            free(ret->un.invoke);
            free(ret);

            return (NULL);
        }
        if (cpt->u.invoke.operation.data[0] == TCPPN_OCI_NATIONAL_TCAP)
        {
            ret->un.invoke->operationCode->offset =
                type_ANSI__TCAP_OperationCode_nationalOperation;
            ret->un.invoke->operationCode->un.nationalOperation =
                (short)((cpt->u.invoke.operation.data[2] << 8) |
                        cpt->u.invoke.operation.data[3]);
        }
        else if (cpt->u.invoke.operation.data[0] == TCPPN_OCI_PRIVATE_TCAP)
        {
            ret->un.invoke->operationCode->offset =
                type_ANSI__TCAP_OperationCode_privateOperation;
            ret->un.invoke->operationCode->un.privateOperation =
                (short)((cpt->u.invoke.operation.data[2] << 8) |
                        cpt->u.invoke.operation.data[3]);
        }

        /* set up the PE for the param */
        if (cpt->u.invoke.param.len == 0)
        {
            int err;

            ret->un.invoke->parameter =
                ssdu2pe((char *)ANSI_EmptyParam,
                        (int)ANSI_EmptyParamLen,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.invoke->componentID);
                free(ret->un.invoke);
                free(ret);

                return (NULL);
            }
        }
        else
        {
            int err;

            ret->un.invoke->parameter =
                ssdu2pe((char *)cpt->u.invoke.param.data,
                        cpt->u.invoke.param.len,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.invoke->componentID);
                free(ret->un.invoke);
                free(ret);

                return (NULL);
            }
        }

        break;

    case TCPPT_TC_INVOKE_NL:
        ret->offset = type_ANSI__TCAP_ComponentPDU_invokeNotLast;

        /* allocate the invoke */
        ret->un.invokeNotLast = (struct type_ANSI__TCAP_Invoke *)
            calloc(1, sizeof(struct type_ANSI__TCAP_Invoke));
        if (ret == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* allocate the componentID */
        ret->un.invokeNotLast->componentID =
            (struct type_ANSI__TCAP_ComponentID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_ComponentID) + 2);
        if (ret == NULL)
        {
            free(ret->un.invokeNotLast);
            free(ret);

            return (NULL);
        }
        /* copy in the invoke info */
        /* copy in the invoke info */
        ret->un.invokeNotLast->componentID->qb_data = 
            ret->un.invokeNotLast->componentID->qb_base;
        ret->un.invokeNotLast->componentID->qb_data[0] =
            cpt->u.invoke.invoke_id.data[2];
        if (cpt->u.invoke.correlation_id.len != 0)
        {
            ret->un.invokeNotLast->componentID->qb_data[1] =
                cpt->u.invoke.correlation_id.data[2];
            ret->un.invokeNotLast->componentID->qb_len = 2;
        }
        else
        {
            ret->un.invokeNotLast->componentID->qb_len = 1;
        }
        /* link up the qbufs */
    	ret->un.invokeNotLast->componentID->qb_forw =
            ret->un.invokeNotLast->componentID;
	    ret->un.invokeNotLast->componentID->qb_back =
            ret->un.invokeNotLast->componentID;

        /* allocate the operationCode */
        ret->un.invokeNotLast->operationCode =
            (struct type_ANSI__TCAP_OperationCode *)
                calloc(1, sizeof(struct type_ANSI__TCAP_OperationCode));
        if (ret == NULL)
        {
            free(ret->un.invokeNotLast->componentID);
            free(ret->un.invokeNotLast);
            free(ret);

            return (NULL);
        }
        if (cpt->u.invoke.operation.data[0] == TCPPN_OCI_NATIONAL_TCAP)
        {
            ret->un.invokeNotLast->operationCode->offset =
                type_ANSI__TCAP_OperationCode_nationalOperation;
            ret->un.invokeNotLast->operationCode->un.nationalOperation =
                (short)((cpt->u.invoke.operation.data[2] << 8) |
                        cpt->u.invoke.operation.data[3]);
        }
        else if (cpt->u.invoke.operation.data[0] == TCPPN_OCI_PRIVATE_TCAP)
        {
            ret->un.invokeNotLast->operationCode->offset =
                type_ANSI__TCAP_OperationCode_privateOperation;
            ret->un.invokeNotLast->operationCode->un.privateOperation =
                (short)((cpt->u.invoke.operation.data[2] << 8) |
                        cpt->u.invoke.operation.data[3]);
        }

        /* set up the PE for the param */
        if (cpt->u.invoke.param.len == 0)
        {
            int err;

            ret->un.invokeNotLast->parameter =
                ssdu2pe((char *)ANSI_EmptyParam,
                        (int)ANSI_EmptyParamLen,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.invokeNotLast->componentID);
                free(ret->un.invokeNotLast);
                free(ret);

                return (NULL);
            }
        }
        else
        {
            int err;

            ret->un.invokeNotLast->parameter =
                ssdu2pe((char *)cpt->u.invoke.param.data,
                        cpt->u.invoke.param.len,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.invokeNotLast->componentID);
                free(ret->un.invokeNotLast);
                free(ret);

                return (NULL);
            }
        }

        break;

    case TCPPT_TC_RESULT_L:
        ret->offset = type_ANSI__TCAP_ComponentPDU_returnResultLast;

        ret->un.returnResultLast = (struct type_ANSI__TCAP_ReturnResult *)
            calloc(1, sizeof(struct type_ANSI__TCAP_ReturnResult));
        if (ret->un.returnResultLast == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* allocate the componentID */
        ret->un.returnResultLast->componentID =
            (struct type_ANSI__TCAP_ComponentID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_ComponentID) + 2);
        if (ret == NULL)
        {
            free(ret->un.returnResultLast);
            free(ret);

            return (NULL);
        }
        /* copy in the invoke info */
        ret->un.returnResultLast->componentID->qb_data = 
            ret->un.returnResultLast->componentID->qb_base;

        ret->un.returnResultLast->componentID->qb_data[0] =
            cpt->u.result.invoke_id.data[2];
        ret->un.returnResultLast->componentID->qb_len = 1;
        /* link up the qbufs */
    	ret->un.returnResultLast->componentID->qb_forw =
            ret->un.returnResultLast->componentID;
	    ret->un.returnResultLast->componentID->qb_back =
            ret->un.returnResultLast->componentID;

        /* set up the PE for the param */
        if (cpt->u.result.param.len == 0)
        {
            int err;

            ret->un.returnResultLast->parameter =
                ssdu2pe((char *)ANSI_EmptyParam,
                        (int)ANSI_EmptyParamLen,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.returnResultLast->componentID);
                free(ret->un.returnResultLast);
                free(ret);

                return (NULL);
            }
        }
        else
        {
            int err;

            ret->un.returnResultLast->parameter =
                ssdu2pe((char *)cpt->u.result.param.data,
                        cpt->u.result.param.len,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.returnResultLast->componentID);
                free(ret->un.returnResultLast);
                free(ret);

                return (NULL);
            }
        }

        break;

    case TCPPT_TC_RESULT_NL:
        ret->offset = type_ANSI__TCAP_ComponentPDU_returnResultNotLast;

        ret->un.returnResultNotLast = (struct type_ANSI__TCAP_ReturnResult *)
            calloc(1, sizeof(struct type_ANSI__TCAP_ReturnResult));
        if (ret->un.returnResultNotLast == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* allocate the componentID */
        ret->un.returnResultNotLast->componentID =
            (struct type_ANSI__TCAP_ComponentID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_ComponentID) + 2);
        if (ret == NULL)
        {
            free(ret->un.returnResultNotLast);
            free(ret);

            return (NULL);
        }
        /* copy in the invoke info */
        ret->un.returnResultNotLast->componentID->qb_data = 
            ret->un.returnResultNotLast->componentID->qb_base;
        ret->un.returnResultNotLast->componentID->qb_data[0] =
            cpt->u.result.invoke_id.data[2];
        ret->un.returnResultNotLast->componentID->qb_len = 1;
        /* link up the qbufs */
    	ret->un.returnResultNotLast->componentID->qb_forw =
            ret->un.returnResultNotLast->componentID;
	    ret->un.returnResultNotLast->componentID->qb_back =
            ret->un.returnResultNotLast->componentID;

        /* set up the PE for the param */
        if (cpt->u.result.param.len == 0)
        {
            int err;

            ret->un.returnResultNotLast->parameter =
                ssdu2pe((char *)ANSI_EmptyParam,
                        (int)ANSI_EmptyParamLen,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.returnResultLast->componentID);
                free(ret->un.returnResultLast);
                free(ret);

                return (NULL);
            }
        }
        else
        {
            int err;

            ret->un.returnResultNotLast->parameter =
                ssdu2pe((char *)cpt->u.result.param.data,
                        cpt->u.result.param.len,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.returnResultNotLast->componentID);
                free(ret->un.returnResultNotLast);
                free(ret);

                return (NULL);
            }
        }

        break;

    case TCPPT_TC_ERROR:
        ret->offset = type_ANSI__TCAP_ComponentPDU_returnError;

        ret->un.returnError = (struct type_ANSI__TCAP_ReturnError *)
            calloc(1, sizeof(struct type_ANSI__TCAP_ReturnError));
        if (ret->un.returnError == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* allocate the componentID */
        ret->un.returnError->componentID =
            (struct type_ANSI__TCAP_ComponentID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_ComponentID) + 2);
        if (ret == NULL)
        {
            free(ret->un.returnError);
            free(ret);

            return (NULL);
        }
        /* copy in the invoke info */
        ret->un.returnError->componentID->qb_data = 
            ret->un.returnError->componentID->qb_base;
        ret->un.returnError->componentID->qb_data[0] =
            cpt->u.error.invoke_id.data[2];
        ret->un.returnError->componentID->qb_len = 1;
        /* link up the qbufs */
    	ret->un.returnError->componentID->qb_forw =
            ret->un.returnError->componentID;
	    ret->un.returnError->componentID->qb_back =
            ret->un.returnError->componentID;

        /* allocate the errorCode */
        ret->un.returnError->errorCode =
            (struct type_ANSI__TCAP_ErrorCode *)
                calloc(1, sizeof(struct type_ANSI__TCAP_ErrorCode));
        if (ret == NULL)
        {
            free(ret->un.returnError->componentID);
            free(ret->un.returnError);
            free(ret);

            return (NULL);
        }
        if (cpt->u.error.error.data[0] == TCPPN_ECI_NATIONAL_TCAP)
        {
            ret->un.returnError->errorCode->offset =
                type_ANSI__TCAP_ErrorCode_nationalError;
            ret->un.returnError->errorCode->un.nationalError =
                (signed char)cpt->u.error.error.data[2];
        }
        else if (cpt->u.error.error.data[0] == TCPPN_ECI_PRIVATE_TCAP)
        {
            ret->un.returnError->errorCode->offset =
                type_ANSI__TCAP_ErrorCode_privateError;
            ret->un.returnError->errorCode->un.privateError =
                (signed char)cpt->u.error.error.data[2];
        }

        /* set up the PE for the param */
        if (cpt->u.error.param.len == 0)
        {
            int err;

            ret->un.returnError->parameter =
                ssdu2pe((char *)ANSI_EmptyParam,
                        (int)ANSI_EmptyParamLen,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.returnError->componentID);
                free(ret->un.returnError);
                free(ret);

                return (NULL);
            }
        }
        else
        {
            int err;

            ret->un.returnError->parameter =
                ssdu2pe((char *)cpt->u.error.param.data,
                        cpt->u.error.param.len,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.returnError->componentID);
                free(ret->un.returnError);
                free(ret);

                return (NULL);
            }
        }

        break;

    case TCPPT_TC_REJECT:
        ret->offset = type_ANSI__TCAP_ComponentPDU_reject;

        ret->un.reject = (struct type_ANSI__TCAP_Reject *)
            calloc(1, sizeof(struct type_ANSI__TCAP_Reject));
        if (ret->un.reject == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* allocate the componentID */
        ret->un.reject->componentID =
            (struct type_ANSI__TCAP_ComponentID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_ComponentID) + 2);
        if (ret == NULL)
        {
            free(ret->un.reject);
            free(ret);

            return (NULL);
        }
        /* copy in the invoke info */
        ret->un.reject->componentID->qb_data = 
            ret->un.reject->componentID->qb_base;
        ret->un.reject->componentID->qb_data[0] =
            cpt->u.reject.invoke_id.data[2];
        ret->un.reject->componentID->qb_len = 1;
        /* link up the qbufs */
    	ret->un.reject->componentID->qb_forw = ret->un.reject->componentID;
	    ret->un.reject->componentID->qb_back = ret->un.reject->componentID;

        /* allocate the problem */
        ret->un.reject->problem =
            (struct type_ANSI__TCAP_Problem *)
                calloc(1, sizeof(struct type_ANSI__TCAP_Problem));
        if (ret == NULL)
        {
            free(ret->un.reject->componentID);
            free(ret->un.reject);
            free(ret);

            return (NULL);
        }
        /* we could handle each problem type separately, but there is no
         * need to do that, as each choice value is given the same layout. */
        ret->un.reject->problem->un.choice_ANSI__TCAP_0 =
            (struct type_ANSI__TCAP_GeneralProblem *)
                calloc(1, sizeof(struct type_ANSI__TCAP_GeneralProblem));
        if (ret->un.reject->problem->un.choice_ANSI__TCAP_0 == NULL)
        {
            free(ret->un.reject->problem);
            free(ret->un.reject->componentID);
            free(ret->un.reject);
            free(ret);

            return (NULL);
        }
        ret->un.reject->problem->offset = type_ANSI__TCAP_Problem_1;
        ret->un.reject->problem->un.choice_ANSI__TCAP_0->parm =
            (short)((cpt->u.reject.problem.data[2] << 8) |
                    cpt->u.reject.problem.data[3]);

        /* set up the PE for the param */
        if (cpt->u.reject.param.len == 0)
        {
            int err;

            ret->un.reject->parameter =
                ssdu2pe((char *)ANSI_EmptyParam,
                        (int)ANSI_EmptyParamLen,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.reject->componentID);
                free(ret->un.reject);
                free(ret);

                return (NULL);
            }
        }
        else
        {
            int err;

            ret->un.reject->parameter =
                ssdu2pe((char *)cpt->u.reject.param.data,
                        cpt->u.reject.param.len,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.reject->componentID);
                free(ret->un.reject);
                free(ret);

                return (NULL);
            }
        }

        break;

    }

    return (ret);
}

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI struct type_ANSI__TCAP_PackageType *
TCAP_CvtDLGToPackage_ANSI(TCAP_DLG *dlg,
                          ITS_INT ltid, ITS_INT rtid)
{
    struct type_ANSI__TCAP_PackageType *ret = NULL;

    if ((!dlg->u.uni.cpt_present) && (dlg->ptype != TCPPT_TC_ABORT))
    {
        if (dlg->u.uni.ac_name.len == 0 &&
            dlg->u.uni.user_info.len == 0 &&
            !(dlg->u.uni.qos.indicator & QOSI_PROT_VER))
        {
            /* Missing dialog Portion as well as Component Portion
               ANSI-Specs Figure 3/T1.114.3 Note 2
            */
            return (NULL);
        }
    }

    /* allocate the component */
    ret = (struct type_ANSI__TCAP_PackageType *)
         calloc(1, sizeof(struct type_ANSI__TCAP_PackageType));
    if (ret == NULL)
    {
        return ret;
    }

    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        ret->offset = type_ANSI__TCAP_PackageType_unidirectional;

        ret->un.unidirectional = (struct type_ANSI__TCAP_UniTransactionPDU *)
            calloc(1, sizeof(struct type_ANSI__TCAP_UniTransactionPDU));
        if (ret->un.unidirectional == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.unidirectional->transactionID =
            (struct type_ANSI__TCAP_TransactionID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_TransactionID) + 8);
        if (ret->un.unidirectional->transactionID == NULL)
        {
            free(ret->un.unidirectional);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.unidirectional->transactionID->qb_data =
            ret->un.unidirectional->transactionID->qb_base;
        /* link up the qbufs */
    	ret->un.unidirectional->transactionID->qb_forw =
            ret->un.unidirectional->transactionID;
	    ret->un.unidirectional->transactionID->qb_back =
            ret->un.unidirectional->transactionID;
        ret->un.unidirectional->transactionID->qb_len = 0;

        /* protocol version */
        ret->un.unidirectional->dialoguePortion =
            BuildDialoguePortion(dlg->u.uni.ac_name.data,
                                 dlg->u.uni.ac_name.len,
                                 dlg->u.uni.user_info.data,
                                 dlg->u.uni.user_info.len,
                                 NULL, 0, NULL, 0,
                                 dlg->u.uni.qos.indicator & QOSI_PROT_VER
                                    ? ITS_TRUE
                                    : ITS_FALSE);
        break;

    case TCPPT_TC_QUERY_W_PERM:
        ret->offset = type_ANSI__TCAP_PackageType_queryWithPerm;

        ret->un.queryWithPerm = (struct type_ANSI__TCAP_TransactionPDU *)
            calloc(1, sizeof(struct type_ANSI__TCAP_TransactionPDU));
        if (ret->un.queryWithPerm == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.queryWithPerm->transactionID =
            (struct type_ANSI__TCAP_TransactionID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_TransactionID) + 8);
        if (ret->un.queryWithPerm->transactionID == NULL)
        {
            free(ret->un.queryWithPerm);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.queryWithPerm->transactionID->qb_data =
            ret->un.queryWithPerm->transactionID->qb_base;
        /* link up the qbufs */
    	ret->un.queryWithPerm->transactionID->qb_forw =
            ret->un.queryWithPerm->transactionID;
	    ret->un.queryWithPerm->transactionID->qb_back =
            ret->un.queryWithPerm->transactionID;
        /* allocate a new local tid */
        ret->un.queryWithPerm->transactionID->qb_len = sizeof(ITS_INT);

        TID_TO_DATA(ret->un.queryWithPerm->transactionID->qb_data, ltid);

        /* dialogue portion */
        ret->un.queryWithPerm->dialoguePortion =
            BuildDialoguePortion(dlg->u.begin.ac_name.data,
                                 dlg->u.begin.ac_name.len,
                                 dlg->u.begin.user_info.data,
                                 dlg->u.begin.user_info.len,
                                 NULL, 0, NULL, 0,
                                 dlg->u.begin.qos.indicator & QOSI_PROT_VER
                                    ? ITS_TRUE
                                    : ITS_FALSE);
        break;

    case TCPPT_TC_QUERY_WO_PERM:
        ret->offset = type_ANSI__TCAP_PackageType_queryWithoutPerm;

        ret->un.queryWithoutPerm = (struct type_ANSI__TCAP_TransactionPDU *)
            calloc(1, sizeof(struct type_ANSI__TCAP_TransactionPDU));
        if (ret->un.queryWithoutPerm == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.queryWithoutPerm->transactionID =
            (struct type_ANSI__TCAP_TransactionID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_TransactionID) + 8);
        if (ret->un.queryWithoutPerm->transactionID == NULL)
        {
            free(ret->un.queryWithoutPerm);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.queryWithoutPerm->transactionID->qb_data =
            ret->un.queryWithoutPerm->transactionID->qb_base;
        /* link up the qbufs */
    	ret->un.queryWithoutPerm->transactionID->qb_forw =
            ret->un.queryWithoutPerm->transactionID;
	    ret->un.queryWithoutPerm->transactionID->qb_back =
            ret->un.queryWithoutPerm->transactionID;
        /* allocate a new local tid */
        ret->un.queryWithoutPerm->transactionID->qb_len = sizeof(ITS_INT);

        TID_TO_DATA(ret->un.queryWithoutPerm->transactionID->qb_data, ltid);

        /* dialogue portion */
        ret->un.queryWithoutPerm->dialoguePortion =
            BuildDialoguePortion(dlg->u.begin.ac_name.data,
                                 dlg->u.begin.ac_name.len,
                                 dlg->u.begin.user_info.data,
                                 dlg->u.begin.user_info.len,
                                 NULL, 0, NULL, 0,
                                 dlg->u.begin.qos.indicator & QOSI_PROT_VER
                                    ? ITS_TRUE
                                    : ITS_FALSE);
        break;

    case TCPPT_TC_CONV_W_PERM:
        ret->offset = type_ANSI__TCAP_PackageType_conversationWithPerm;

        ret->un.conversationWithPerm = (struct type_ANSI__TCAP_TransactionPDU *)
            calloc(1, sizeof(struct type_ANSI__TCAP_TransactionPDU));
        if (ret->un.conversationWithPerm == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.conversationWithPerm->transactionID =
            (struct type_ANSI__TCAP_TransactionID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_TransactionID) + 8);
        if (ret->un.conversationWithPerm->transactionID == NULL)
        {
            free(ret->un.conversationWithPerm);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.conversationWithPerm->transactionID->qb_data =
            ret->un.conversationWithPerm->transactionID->qb_base;
        /* link up the qbufs */
    	ret->un.conversationWithPerm->transactionID->qb_forw =
            ret->un.conversationWithPerm->transactionID;
	    ret->un.conversationWithPerm->transactionID->qb_back =
            ret->un.conversationWithPerm->transactionID;
        /* set the tid's */
        ret->un.conversationWithPerm->transactionID->qb_len =
            sizeof(ITS_INT) * 2;

        TID_TO_DATA(ret->un.conversationWithPerm->transactionID->qb_data,
                    ltid);
        TID_TO_DATA(ret->un.conversationWithPerm->transactionID->qb_data +
                        sizeof(ITS_INT),
                    rtid);

        /* dialogue portion */
        ret->un.conversationWithPerm->dialoguePortion =
            BuildDialoguePortion(dlg->u.cont.ac_name.data,
                                 dlg->u.cont.ac_name.len,
                                 dlg->u.cont.user_info.data,
                                 dlg->u.cont.user_info.len,
                                 NULL, 0, NULL, 0,
                                 dlg->u.cont.qos.indicator & QOSI_PROT_VER
                                    ? ITS_TRUE
                                    : ITS_FALSE);
        break;

    case TCPPT_TC_CONV_WO_PERM:
        ret->offset = type_ANSI__TCAP_PackageType_conversationWithoutPerm;

        ret->un.conversationWithoutPerm =
            (struct type_ANSI__TCAP_TransactionPDU *)
                calloc(1, sizeof(struct type_ANSI__TCAP_TransactionPDU));
        if (ret->un.conversationWithoutPerm == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.conversationWithoutPerm->transactionID =
            (struct type_ANSI__TCAP_TransactionID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_TransactionID) + 8);
        if (ret->un.conversationWithoutPerm->transactionID == NULL)
        {
            free(ret->un.conversationWithoutPerm);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.conversationWithoutPerm->transactionID->qb_data =
            ret->un.conversationWithoutPerm->transactionID->qb_base;
        /* link up the qbufs */
    	ret->un.conversationWithoutPerm->transactionID->qb_forw =
            ret->un.conversationWithoutPerm->transactionID;
	    ret->un.conversationWithoutPerm->transactionID->qb_back =
            ret->un.conversationWithoutPerm->transactionID;
        /* set the tid's */
        ret->un.queryWithoutPerm->transactionID->qb_len = sizeof(ITS_INT) * 2;

        TID_TO_DATA(ret->un.conversationWithoutPerm->transactionID->qb_data,
                    ltid);
        TID_TO_DATA(ret->un.conversationWithoutPerm->transactionID->qb_data +
                        sizeof(ITS_INT),
                    rtid);

        /* dialogue portion */
        ret->un.conversationWithoutPerm->dialoguePortion =
            BuildDialoguePortion(dlg->u.cont.ac_name.data,
                                 dlg->u.cont.ac_name.len,
                                 dlg->u.cont.user_info.data,
                                 dlg->u.cont.user_info.len,
                                 NULL, 0, NULL, 0,
                                 dlg->u.cont.qos.indicator & QOSI_PROT_VER
                                    ? ITS_TRUE
                                    : ITS_FALSE);
        break;

    case TCPPT_TC_RESP:
        ret->offset = type_ANSI__TCAP_PackageType_response;

        ret->un.response = (struct type_ANSI__TCAP_TransactionPDU *)
            calloc(1, sizeof(struct type_ANSI__TCAP_TransactionPDU));
        if (ret->un.response == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.response->transactionID =
            (struct type_ANSI__TCAP_TransactionID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_TransactionID) + 8);
        if (ret->un.response->transactionID == NULL)
        {
            free(ret->un.response);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.response->transactionID->qb_data =
            ret->un.response->transactionID->qb_base;
        /* link up the qbufs */
    	ret->un.response->transactionID->qb_forw =
            ret->un.response->transactionID;
	    ret->un.response->transactionID->qb_back =
            ret->un.response->transactionID;
        /* set the tid */
        ret->un.response->transactionID->qb_len = sizeof(ITS_INT);
        TID_TO_DATA(ret->un.response->transactionID->qb_data,
                    rtid);

        /* dialogue portion */
        ret->un.response->dialoguePortion =
            BuildDialoguePortion(dlg->u.end.ac_name.data,
                                 dlg->u.end.ac_name.len,
                                 dlg->u.end.user_info.data,
                                 dlg->u.end.user_info.len,
                                 NULL, 0, NULL, 0,
                                 dlg->u.end.qos.indicator & QOSI_PROT_VER
                                    ? ITS_TRUE
                                    : ITS_FALSE);
        break;

    case TCPPT_TC_ABORT:
        ret->offset = type_ANSI__TCAP_PackageType_abort;

        ret->un.abort = (struct type_ANSI__TCAP_Abort *)
            calloc(1, sizeof(struct type_ANSI__TCAP_Abort));
        if (ret->un.abort == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.abort->transactionID =
            (struct type_ANSI__TCAP_TransactionID *)
                calloc(1, sizeof(struct type_ANSI__TCAP_TransactionID) + 8);
        if (ret->un.abort->transactionID == NULL)
        {
            free(ret->un.abort);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.abort->transactionID->qb_data =
            ret->un.abort->transactionID->qb_base;
        /* link up the qbufs */
    	ret->un.abort->transactionID->qb_forw =
            ret->un.abort->transactionID;
	    ret->un.abort->transactionID->qb_back =
            ret->un.abort->transactionID;
        /* set the tid */
        ret->un.abort->transactionID->qb_len = sizeof(ITS_INT);
        TID_TO_DATA(ret->un.abort->transactionID->qb_data,
                    rtid);

        /* fill in the abort cause */
        if (dlg->u.abort.abort_reason != 0) /* P-ABORT? */
        {
            ret->un.abort->element_ANSI__TCAP_1 =
                (struct choice_ANSI__TCAP_7 *)
                    calloc(1, sizeof(struct choice_ANSI__TCAP_7));
            if (ret->un.abort->element_ANSI__TCAP_1 == NULL)
            {
                free(ret->un.abort->transactionID);
                free(ret->un.abort);
                free(ret);

                return (NULL);
            }
            ret->un.abort->element_ANSI__TCAP_1->offset = choice_ANSI__TCAP_7_1;
            ret->un.abort->element_ANSI__TCAP_1->un.choice_ANSI__TCAP_8 =
                (struct type_ANSI__TCAP_P__Abort__Cause *)
                    calloc(1, sizeof(struct type_ANSI__TCAP_P__Abort__Cause));
            if (ret->un.abort->element_ANSI__TCAP_1->un.choice_ANSI__TCAP_8 ==
                NULL)
            {
                free(ret->un.abort->element_ANSI__TCAP_1);
                free(ret->un.abort->transactionID);
                free(ret->un.abort);
                free(ret);

                return (NULL);
            }
            ret->un.abort->element_ANSI__TCAP_1->un.choice_ANSI__TCAP_8->parm =
                dlg->u.abort.abort_reason;
        }
        else /* U-ABORT */
        {
            ret->un.abort->element_ANSI__TCAP_1 =
                (struct choice_ANSI__TCAP_7 *)
                    calloc(1, sizeof(struct choice_ANSI__TCAP_7));
            if (ret->un.abort->element_ANSI__TCAP_1 == NULL)
            {
                free(ret->un.abort->transactionID);
                free(ret->un.abort);
                free(ret);

                return (NULL);
            }

            ret->un.abort->element_ANSI__TCAP_1->offset = choice_ANSI__TCAP_7_2;

            if (dlg->u.abort.abort_info.len == 0)
            {
                int err;

                ret->un.abort->element_ANSI__TCAP_1->un.choice_ANSI__TCAP_9 =
                    ssdu2pe((char *)ANSI_EmptyAbort,
                            (int)ANSI_EmptyAbortLen,
                            NULL,
                            &err);

                if (err != PS_ERR_NONE)
                {
                    free(ret->un.abort->transactionID);
                    free(ret->un.abort);
                    free(ret);

                    return (NULL);
                }
            }
            else
            {
                int err;

                ret->un.abort->element_ANSI__TCAP_1->un.choice_ANSI__TCAP_9 =
                    ssdu2pe((char *)dlg->u.abort.abort_info.data,
                            dlg->u.abort.abort_info.len,
                            NULL,
                            &err);

                if (err != PS_ERR_NONE)
                {
                    free(ret->un.abort->transactionID);
                    free(ret->un.abort);
                    free(ret);

                    return (NULL);
                }
            }

            /* dialogue portion (only in U-ABORT) */
            ret->un.abort->dialoguePortion =
                BuildDialoguePortion(dlg->u.abort.ac_name.data,
                                     dlg->u.abort.ac_name.len,
                                     dlg->u.abort.user_info.data,
                                     dlg->u.abort.user_info.len,
                                     NULL, 0, NULL, 0,
                                     dlg->u.abort.qos.indicator & QOSI_PROT_VER
                                        ? ITS_TRUE
                                        : ITS_FALSE);
        }

        break;
    }

    return (ret);
}

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_CvtComponentPDUToCPT_ANSI(TCAP_CPT *cpt,
                               struct type_ANSI__TCAP_ComponentPDU *comp)
{
    struct type_ANSI__TCAP_ComponentID *cid;
    char buf[32], *tmp;
    int len;
    PE param;

    memset(cpt, 0, sizeof(TCAP_CPT));

    if (comp == NULL)
    {
        return (ITS_EPROTERR);
    }

    switch (comp->offset)
    {
    case type_ANSI__TCAP_ComponentPDU_invoke:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_INVOKE;

        if (comp->un.invoke == NULL ||
            comp->un.invoke->componentID == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        cid = comp->un.invoke->componentID;
        len = 32;
        QBufToStr(cid, buf, &len);
        if (len != 1 && len != 2)
        {
            return (ITS_EPROTERR);
        }

        cpt->u.invoke.invoke_id.len = 3;
        cpt->u.invoke.invoke_id.data[0] = TCPPN_COMPONENT_ID;
        cpt->u.invoke.invoke_id.data[1] = 1;
        cpt->u.invoke.invoke_id.data[2] = buf[0];
        if (len == 2)
        {
            cpt->u.invoke.correlation_id.len = 3;
            cpt->u.invoke.correlation_id.data[0] = TCPPN_COMPONENT_ID;
            cpt->u.invoke.correlation_id.data[1] = 1;
            cpt->u.invoke.correlation_id.data[2] = buf[1];
        }

        /* get the op code */
        if (comp->un.invoke->operationCode->offset ==
            type_ANSI__TCAP_OperationCode_nationalOperation)
        {
            cpt->u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
            cpt->u.invoke.operation.data[1] = 2;
            cpt->u.invoke.operation.data[2] =
                (ITS_OCTET)((comp->un.invoke->operationCode->
                            un.nationalOperation >> 8) & 0xFFU);
            cpt->u.invoke.operation.data[3] =
                (ITS_OCTET)(comp->un.invoke->operationCode->
                            un.nationalOperation & 0xFFU);
            cpt->u.invoke.operation.len = 4;
        }
        else if (comp->un.invoke->operationCode->offset ==
                 type_ANSI__TCAP_OperationCode_privateOperation)
        {
            cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
            cpt->u.invoke.operation.data[1] = 2;
            cpt->u.invoke.operation.data[2] =
                (ITS_OCTET)((comp->un.invoke->operationCode->
                            un.privateOperation >> 8) & 0xFFU);
            cpt->u.invoke.operation.data[3] =
                (ITS_OCTET)(comp->un.invoke->operationCode->
                            un.privateOperation & 0xFFU);
            cpt->u.invoke.operation.len = 4;
        }

        /* get the parameter */
        param = comp->un.invoke->parameter;
        len = 0;
        if (param)
        {
            if (pe2ssdu(param, &tmp, &len) != OK)
            {
                return (ITS_EPROTERR);
            }
        }
        cpt->u.invoke.param.len = (ITS_USHORT)len;
        if (len)
        {
            memcpy(cpt->u.invoke.param.data, tmp, len);

            free(tmp);
        }

        break;

    case type_ANSI__TCAP_ComponentPDU_invokeNotLast:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_INVOKE_NL;

        if (comp->un.invokeNotLast == NULL ||
            comp->un.invokeNotLast->componentID == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        cid = comp->un.invokeNotLast->componentID;
        len = 32;
        QBufToStr(cid, buf, &len);
        if (len != 1 && len != 2)
        {
            return (ITS_EPROTERR);
        }

        cpt->u.invoke.invoke_id.len = 3;
        cpt->u.invoke.invoke_id.data[0] = TCPPN_COMPONENT_ID;
        cpt->u.invoke.invoke_id.data[1] = 1;
        cpt->u.invoke.invoke_id.data[2] = buf[0];
        if (len == 2)
        {
            cpt->u.invoke.correlation_id.len = 3;
            cpt->u.invoke.correlation_id.data[0] = TCPPN_COMPONENT_ID;
            cpt->u.invoke.correlation_id.data[1] = 1;
            cpt->u.invoke.correlation_id.data[2] = buf[1];
        }

        /* get the op code */
        if (comp->un.invoke->operationCode->offset ==
            type_ANSI__TCAP_OperationCode_nationalOperation)
        {
            cpt->u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
            cpt->u.invoke.operation.data[1] = 2;
            cpt->u.invoke.operation.data[2] =
                (ITS_OCTET)((comp->un.invoke->operationCode->
                            un.nationalOperation >> 8) & 0xFFU);
            cpt->u.invoke.operation.data[3] =
                (ITS_OCTET)(comp->un.invoke->operationCode->
                            un.nationalOperation & 0xFFU);
            cpt->u.invoke.operation.len = 4;
        }
        else if (comp->un.invoke->operationCode->offset ==
                 type_ANSI__TCAP_OperationCode_privateOperation)
        {
            cpt->u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
            cpt->u.invoke.operation.data[1] = 2;
            cpt->u.invoke.operation.data[2] =
                (ITS_OCTET)((comp->un.invoke->operationCode->
                            un.privateOperation >> 8) & 0xFFU);
            cpt->u.invoke.operation.data[3] =
                (ITS_OCTET)(comp->un.invoke->operationCode->
                            un.privateOperation & 0xFFU);
            cpt->u.invoke.operation.len = 4;
        }

        /* get the parameter */
        param = comp->un.invokeNotLast->parameter;
        len = 0;
        if (param)
        {
            if (pe2ssdu(param, &tmp, &len) != OK)
            {
                return (ITS_EPROTERR);
            }
        }
        cpt->u.invoke.param.len = (ITS_USHORT)len;
        if (len)
        {
            memcpy(cpt->u.invoke.param.data, tmp, len);

            free(tmp);
        }
        break;

    case type_ANSI__TCAP_ComponentPDU_returnResultNotLast:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_RESULT_NL;

        if (comp->un.returnResultNotLast == NULL ||
            comp->un.returnResultNotLast->componentID == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        cid = comp->un.returnResultNotLast->componentID;
        len = 32;
        QBufToStr(cid, buf, &len);
        if (len != 1)
        {
            return (ITS_EPROTERR);
        }

        cpt->u.result.invoke_id.len = 3;
        cpt->u.result.invoke_id.data[0] = TCPPN_COMPONENT_ID;
        cpt->u.result.invoke_id.data[1] = 1;
        cpt->u.result.invoke_id.data[2] = buf[0];

        /* get the parameter */
        param = comp->un.returnResultNotLast->parameter;
        len = 0;
        if (param)
        {
            if (pe2ssdu(param, &tmp, &len) != OK)
            {
                return (ITS_EPROTERR);
            }
        }
        cpt->u.result.param.len = (ITS_USHORT)len;
        if (len)
        {
            memcpy(cpt->u.result.param.data, tmp, len);

            free(tmp);
        }

        break;

    case type_ANSI__TCAP_ComponentPDU_returnResultLast:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_RESULT_L;

        if (comp->un.returnResultLast == NULL ||
            comp->un.returnResultLast->componentID == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        cid = comp->un.returnResultLast->componentID;
        len = 32;
        QBufToStr(cid, buf, &len);
        if (len != 1)
        {
            return (ITS_EPROTERR);
        }

        cpt->u.result.invoke_id.len = 3;
        cpt->u.result.invoke_id.data[0] = TCPPN_COMPONENT_ID;
        cpt->u.result.invoke_id.data[1] = 1;
        cpt->u.result.invoke_id.data[2] = buf[0];

        /* get the parameter */
        param = comp->un.returnResultLast->parameter;
        len = 0;
        if (param)
        {
            if (pe2ssdu(param, &tmp, &len) != OK)
            {
                return (ITS_EPROTERR);
            }
        }
        cpt->u.result.param.len = (ITS_USHORT)len;
        if (len)
        {
            memcpy(cpt->u.result.param.data, tmp, len);

            free(tmp);
        }

        break;

    case type_ANSI__TCAP_ComponentPDU_returnError:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_ERROR;

        if (comp->un.returnError == NULL ||
            comp->un.returnError->componentID == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        cid = comp->un.returnError->componentID;
        len = 32;
        QBufToStr(cid, buf, &len);
        if (len != 1)
        {
            return (ITS_EPROTERR);
        }

        cpt->u.error.invoke_id.len = 3;
        cpt->u.error.invoke_id.data[0] = TCPPN_COMPONENT_ID;
        cpt->u.error.invoke_id.data[1] = 1;
        cpt->u.error.invoke_id.data[2] = buf[0];

        /* get the problem code */
        if (comp->un.returnError->errorCode->offset ==
            type_ANSI__TCAP_ErrorCode_nationalError)
        {
            cpt->u.error.error.len = 3;
            cpt->u.error.error.data[0] = TCPPN_ECI_NATIONAL_TCAP;
            cpt->u.error.error.data[1] = 1;
            cpt->u.error.error.data[2] =
                (ITS_OCTET)(comp->un.returnError->errorCode->
                            un.nationalError & 0xFFU);
        }
        else if(comp->un.returnError->errorCode->offset ==
                type_ANSI__TCAP_ErrorCode_privateError)
        {
            cpt->u.error.error.len = 3;
            cpt->u.error.error.data[0] = TCPPN_ECI_PRIVATE_TCAP;
            cpt->u.error.error.data[1] = 1;
            cpt->u.error.error.data[2] =
                (ITS_OCTET)(comp->un.returnError->errorCode->
                            un.privateError & 0xFFU);
        }

        /* get the parameter */
        param = comp->un.returnError->parameter;
        len = 0;
        if (param)
        {
            if (pe2ssdu(param, &tmp, &len) != OK)
            {
                return (ITS_EPROTERR);
            }
        }
        cpt->u.error.param.len = (ITS_USHORT)len;
        if (len)
        {
            memcpy(cpt->u.error.param.data, tmp, len);

            free(tmp);
        }

        break;

    case type_ANSI__TCAP_ComponentPDU_reject:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_REJECT;

        if (comp->un.reject == NULL ||
            comp->un.reject->componentID == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        cid = comp->un.reject->componentID;
        len = 32;
        QBufToStr(cid, buf, &len);
        if (len != 1)
        {
            return (ITS_EPROTERR);
        }

        cpt->u.reject.invoke_id.len = 3;
        cpt->u.reject.invoke_id.data[0] = TCPPN_COMPONENT_ID;
        cpt->u.reject.invoke_id.data[1] = 1;
        cpt->u.reject.invoke_id.data[2] = buf[0];

        /* get the problem */
        if (comp->un.reject->problem != NULL)
        {
            cpt->u.reject.problem.len = 4;
            cpt->u.reject.problem.data[0] = TCPPROB_IDENT;
            cpt->u.reject.problem.data[1] = 2;
            cpt->u.reject.problem.data[2] =
                (ITS_OCTET)(
                    (comp->un.reject->problem->un.choice_ANSI__TCAP_0->parm >>
                     8) & 0xFFU);
            cpt->u.reject.problem.data[3] =
                (ITS_OCTET)(
                    (comp->un.reject->problem->un.choice_ANSI__TCAP_0->parm &
                     0xFFU));
        }

        /* add in parameter */
        if (comp->un.reject->parameter)
        {
            if (pe2ssdu(comp->un.reject->parameter, &tmp, &len) != OK)
            {
                return (ITS_EPROTERR);
            }

            cpt->u.reject.param.len = (ITS_USHORT)len;
            if (len)
            {
                memcpy(cpt->u.reject.param.data, tmp, len);

                free(tmp);
            }
        }

        break;

    default:
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_CvtPackageToDLG_ANSI(TCAP_DLG *dlg,
                          struct type_ANSI__TCAP_PackageType *dialog)
{
    ITS_BOOLEAN hasPV;

    memset(dlg, 0, sizeof(TCAP_DLG));

    if (dialog == NULL)
    {
        return (ITS_EPROTERR);
    }

    switch (dialog->offset)
    {
    case type_ANSI__TCAP_PackageType_unidirectional:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_UNI;

        /* parse dialogue portion */
        if (!ParseDialoguePortion(dialog->un.unidirectional->dialoguePortion,
                                  dlg->u.uni.ac_name.data,
                                  &dlg->u.uni.ac_name.len,
                                  dlg->u.uni.user_info.data,
                                  &dlg->u.uni.user_info.len,
                                  NULL, NULL, NULL, NULL,
                                  &hasPV))
        {
            return (ITS_EPROTERR);
        }

        if (hasPV)
        {
            dlg->u.uni.qos.indicator |= QOSI_PROT_VER;
        }
        /* check for components */
        if (dialog->un.unidirectional->componentSequence != NULL)
        {
            dlg->u.uni.cpt_present = 1;
        }
        else /* Fix for 174, 175, 188 */
        {
            if (dlg->u.uni.ac_name.len == 0 &&
                dlg->u.uni.user_info.len == 0 &&
                !hasPV)
            {
                /* Missing dialog Portion as well as Component Portion
                   ANSI-Specs Figure 3/T1.114.3 Note 2
                */
 
                return (ITS_EPROTERR);
            }
        }

        break;

    case type_ANSI__TCAP_PackageType_queryWithPerm:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_QUERY_W_PERM;

        /* parse dialogue portion */
        if (!ParseDialoguePortion(dialog->un.queryWithPerm->dialoguePortion,
                                  dlg->u.begin.ac_name.data,
                                  &dlg->u.begin.ac_name.len,
                                  dlg->u.begin.user_info.data,
                                  &dlg->u.begin.user_info.len,
                                  NULL, NULL, NULL, NULL,
                                  &hasPV))
        {
            return (ITS_EPROTERR);
        }

        if (hasPV)
        {
            dlg->u.begin.qos.indicator |= QOSI_PROT_VER;
        }

        /* check for components */
        if (dialog->un.queryWithPerm->componentSequence != NULL)
        {
            dlg->u.begin.cpt_present = 1;
        }
        else /* Fix for 174, 175, 188 */
        {
            if (dlg->u.begin.ac_name.len == 0 &&
                dlg->u.begin.user_info.len == 0 &&
                !hasPV)
            {
                /* Missing dialog Portion as well as Component Portion
                   ANSI-Specs Figure 3/T1.114.3 Note 2
                */
  
                return (ITS_EPROTERR);
            }
        }
        
        break;

    case type_ANSI__TCAP_PackageType_queryWithoutPerm:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_QUERY_WO_PERM;

        /* parse dialogue portion */
        if (!ParseDialoguePortion(dialog->un.queryWithoutPerm->dialoguePortion,
                                  dlg->u.begin.ac_name.data,
                                  &dlg->u.begin.ac_name.len,
                                  dlg->u.begin.user_info.data,
                                  &dlg->u.begin.user_info.len,
                                  NULL, NULL, NULL, NULL,
                                  &hasPV))
        {
            return (ITS_EPROTERR);
        }

        if (hasPV)
        {
            dlg->u.begin.qos.indicator |= QOSI_PROT_VER;
        }

        /* check for components */
        if (dialog->un.queryWithoutPerm->componentSequence != NULL)
        {
            dlg->u.begin.cpt_present = 1;
        }
        else
        {
            if (dlg->u.begin.ac_name.len == 0 &&
                dlg->u.begin.user_info.len == 0 &&
                !hasPV)
            {
                /* Missing dialog Portion as well as Component Portion
                   ANSI-Specs Figure 3/T1.114.3 Note 2
                */

                return (ITS_EPROTERR);
            }
        }

        break;

    case type_ANSI__TCAP_PackageType_response:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_RESP;

        /* parse dialogue portion */
        if (!ParseDialoguePortion(dialog->un.response->dialoguePortion,
                                  dlg->u.end.ac_name.data,
                                  &dlg->u.end.ac_name.len,
                                  dlg->u.end.user_info.data,
                                  &dlg->u.end.user_info.len,
                                  NULL, NULL, NULL, NULL,
                                  &hasPV))
        {
            return (ITS_EPROTERR);
        }

        if (hasPV)
        {
            dlg->u.end.qos.indicator |= QOSI_PROT_VER;
        }

        /* check for components */
        if (dialog->un.response->componentSequence != NULL)
        {
            dlg->u.end.cpt_present = 1;
        }
        else
        {
            if (dlg->u.end.ac_name.len == 0 &&
                dlg->u.end.user_info.len == 0 &&
                !hasPV)
            {
                /* Missing dialog Portion as well as Component Portion
                   ANSI-Specs Figure 3/T1.114.3 Note 2
                */

                return (ITS_EPROTERR);
            }
        }

        break;

    case type_ANSI__TCAP_PackageType_conversationWithPerm:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_CONV_W_PERM;

        /* parse dialogue portion */
        if (!ParseDialoguePortion(dialog->un.conversationWithPerm->dialoguePortion,
                                  dlg->u.cont.ac_name.data,
                                  &dlg->u.cont.ac_name.len,
                                  dlg->u.cont.user_info.data,
                                  &dlg->u.cont.user_info.len,
                                  NULL, NULL, NULL, NULL,
                                  &hasPV))
        {
            return (ITS_EPROTERR);
        }

        if (hasPV)
        {
            dlg->u.cont.qos.indicator |= QOSI_PROT_VER;
        }

        /* check for components */
        if (dialog->un.conversationWithPerm->componentSequence != NULL)
        {
            dlg->u.cont.cpt_present = 1;
        }
        else
        {
            if (dlg->u.cont.ac_name.len == 0 &&
                dlg->u.cont.user_info.len == 0 &&
                !hasPV)
            {
                /* Missing dialog Portion as well as Component Portion
                   ANSI-Specs Figure 3/T1.114.3 Note 2
                */

                return (ITS_EPROTERR);
            }
        }

        break;

    case type_ANSI__TCAP_PackageType_conversationWithoutPerm:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_CONV_WO_PERM;

        /* parse dialogue portion */
        if (!ParseDialoguePortion(dialog->un.conversationWithoutPerm->dialoguePortion,
                                  dlg->u.cont.ac_name.data,
                                  &dlg->u.cont.ac_name.len,
                                  dlg->u.cont.user_info.data,
                                  &dlg->u.cont.user_info.len,
                                  NULL, NULL, NULL, NULL,
                                  &hasPV))
        {
            return (ITS_EPROTERR);
        }

        if (hasPV)
        {
            dlg->u.cont.qos.indicator |= QOSI_PROT_VER;
        }

        /* check for components */
        if (dialog->un.conversationWithoutPerm->componentSequence != NULL)
        {
            dlg->u.cont.cpt_present = 1;
        }
        else /* fix for 174, 175, 188 */
        {
            if (dlg->u.cont.ac_name.len == 0 &&
                dlg->u.cont.user_info.len == 0 &&
                !hasPV)
            {
                /* Missing dialog Portion as well as Component Portion
                   ANSI-Specs Figure 3/T1.114.3 Note 2
                */

                return (ITS_EPROTERR);
            }
        }

        break;

    case type_ANSI__TCAP_PackageType_abort:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_ABORT;

        /* parse dialogue portion */
        if (!ParseDialoguePortion(dialog->un.abort->dialoguePortion,
                                  dlg->u.abort.ac_name.data,
                                  &dlg->u.abort.ac_name.len,
                                  dlg->u.abort.user_info.data,
                                  &dlg->u.abort.user_info.len,
                                  NULL, NULL, NULL, NULL,
                                  &hasPV))
        {
            return (ITS_EPROTERR);
        }

        if (hasPV)
        {
            dlg->u.abort.qos.indicator |= QOSI_PROT_VER;
        }

        if (dialog->un.abort->element_ANSI__TCAP_1 != NULL)
        {
            if (dialog->un.abort->element_ANSI__TCAP_1->offset ==
                choice_ANSI__TCAP_7_1)
            {
                dlg->u.abort.abort_reason =
                    (ITS_OCTET)dialog->un.abort->element_ANSI__TCAP_1->
                        un.choice_ANSI__TCAP_8->parm;
            }
            else if (dialog->un.abort->element_ANSI__TCAP_1->offset ==
                     choice_ANSI__TCAP_7_2)
            {
                char *tmp;
                int len;
                PE abt_info;

                abt_info = dialog->un.abort->element_ANSI__TCAP_1->un.choice_ANSI__TCAP_9;

                if (abt_info)
                {
                    if (pe2ssdu(abt_info, &tmp, &len) != OK)
                    {
                        return (ITS_EPROTERR);
                    }
                }

                dlg->u.abort.abort_info.len = (ITS_USHORT)len;
                if (len)
                {
                    memcpy(dlg->u.abort.abort_info.data, tmp, len);

                    free(tmp);
                }
            }
        }

        break;

    default:
        break;
    }

    return (ITS_SUCCESS);
}
