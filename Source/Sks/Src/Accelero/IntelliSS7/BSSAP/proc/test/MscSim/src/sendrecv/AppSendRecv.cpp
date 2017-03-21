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
 *  ID: $Id: AppSendRecv.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:42  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:58  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/30 12:23:28  adutta
 * LOG: Modified for UDT (SS)
 * LOG:
 * LOG: Revision 1.1.2.2  2005/09/28 10:53:51  adutta
 * LOG: Remodeled for MSC Sim
 * LOG:
 * LOG: Revision 1.3  2005/02/23 10:15:39  csireesh
 * LOG: IOSCDMA Codec Implementation.
 * LOG:
 * LOG: Revision 1.2  2005/02/11 10:21:10  csireesh
 * LOG: Committing after sanitizing Sample App (send-recv) for SCCP-CO: yet to take care of Codec
 * LOG:
 * LOG: Revision 1.1  2004/02/12 13:46:55  aganguly
 * LOG: Initial version of CDMA test application on SCCP-CO.
 * LOG:
 ****************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <sys/timeb.h>
#include <malloc.h>
#include <string.h>

#include <its++.h>
#include <engine++.h>
#include <sccp++.h>
#include <its_types.h>
#include <its_route.h>
#include <its_sctp.h>
#include <its_service.h>
#include <its_iniparse.h>
#include <its_sctp_trans.h>
#include <its_gen_disp.h>

#include <App.h>
#include <AppTrace.h>
#include <AppDbc.h>
#include <AppDsm.h>
#include <AppCodec.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif


#if defined(CCITT)
#define ISS7_Stack    ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack    ISS7_ANSI_Stack
#endif

#ifdef ANSI
#define FILENAME        "ansi_params.txt"
#else
#define FILENAME        "ccitt_params.txt"
#endif

static char filename[50] = FILENAME;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads an SCCP message from a file and stores the
 *      information in an array of information elements (ITS_SCCP_IE).
 *
 *  Input Parameters:
 *      sccpMsgType - SCCP message code
 *      filename - pointer to name of file to search for the SCCP message
 *      sccpParam - SCCP Message Parameter.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ie - pointer to the first member an information element structure
 *      ieCount - number of parameters in current message being read
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if SCCP message is read successfully.
 *      Any other return code indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadMsgParam(ITS_OCTET sccpMsgType, ITS_OCTET sccpParam, char* filename, ITS_OCTET *ie,
            int *ie_len)
{
    int        parCode = 0;
    char       pCode[10];
    int        nFields = 0;
    char       *p = NULL, typeOfInfo;
    FILE       *fp = NULL;
    int        mType = 0;
    char       buf[1024];

    memset(buf, 1024, 0);
    fp = fopen( filename, "r" );

    if ( fp )
    {
        //File opened successfully.
    }
    else
    {
        //File opened failed.
        return !ITS_SUCCESS;
    }

    do
    {
        fgets(buf, 110, fp);

        if (feof(fp))
        {
            //eof reached.
            fclose(fp);
            return !ITS_SUCCESS;
        }

        if (buf[0] == 'M')
        {
            /* Read Message Type */
            p = (char *)strtok( buf, " \t" );

            mType = (ITS_OCTET) strtol(strtok(NULL, " \t"), (char **)0, 16);
        }
    } while (mType != sccpMsgType);

    do
    {
        /* Read info type and parameter code */
        nFields = fscanf(fp, "%c\t%x\t", &typeOfInfo, &parCode);

        if (nFields != 2)
            break;
        if ( (typeOfInfo == 'P') || (typeOfInfo == 'p') )
        {
            /* do nothing .... fall through */
        }
        else
        {
            break;
        }

            /* do nothing .... fall through */

        /* Read in 100 characters */
        fgets(buf, 500, fp);

        switch ( parCode )
        {

            case RL_OPC:

            case RL_DPC:

            case RL_SLS:

            case CGP_PC:

            case CDP_PC:

            case CDP_SSN:

            case CGP_SSN:

            case CDP_NI:

            case CDP_ROUT_TYPE:

            case CDP_GTT_TYPE:

            case CDP_GTT_DIG:

            case CGP_NI:

            case CGP_ROUT_TYPE:

            case CGP_GTT_TYPE:

            case CGP_GTT_DIG:

            case SCCP_PRM_PROTOCOL_CLASS:

            case SCCP_PRM_CREDIT:

            case SCCP_PRM_HOP_COUNTER:
                *ie_len = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);
                GetOctetsFromStr(ie, *ie_len);
                break;

            default:
                break;
        }
    } while (!feof(fp) && parCode != sccpParam);

    fclose( fp );
    return ITS_SUCCESS;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets an SCCP Address by reading from a file and stores the
 *      information in MTP3 Header,CallingParty Address CalledParty Address. 
 *      
 *  Input Parameters:
 *      msgType - SCCP message code
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      mtp3_hdr - reference to MTP3_Header
 *      cpa - reference to SCCP_CallingPartyAddr
 *      cdp - pointer to SCCP_CalledPartyAddr 
 *
 *  Return Value:
 *      None.
 *
 *  See Also:
 ****************************************************************************/
void
SetMTP3andSCCPAddress(int msgtype, 
               MTP3_Header &mtp3_hdr,
               SCCP_CallingPartyAddr *cpa,
               SCCP_CalledPartyAddr *cdp)
{
    ITS_OCTET    ie[100];
    ITS_INT      ieLen = 0;

    ITS_OCTET M_Opc = 0;
    ITS_OCTET M_Dpc = 0;
    ITS_OCTET Sls = 0;

    ITS_OCTET cdp_pc = 0;
    ITS_OCTET cdp_ssn = 0;
    ITS_OCTET cdp_gtt_dig[SCCP_MAX_ADDR_LEN];
    ITS_USHORT cdp_gtt_len = 0;
    ITS_OCTET cdp_gtt_type = 0;
    ITS_OCTET cdp_ni = 0;
    ITS_OCTET cdp_route_type = 0;

    ITS_OCTET cgp_pc = 0;
    ITS_OCTET cgp_ssn = 0;
    ITS_OCTET cgp_gtt_dig[SCCP_MAX_ADDR_LEN];
    ITS_USHORT cgp_gtt_len = 0;
    ITS_OCTET cgp_gtt_type = 0;
    ITS_OCTET cgp_ni = 0;
    ITS_OCTET cgp_route_type = 0;
    
    printf("SetMTP3andSCCPAddress::Setting up MTP3 Routing Lable\n");

    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, RL_OPC, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&M_Opc, ie, ieLen);
        mtp3_hdr.SetOPC(M_Opc);
        printf(" Parameter:: MTP3 OPC is %d\n", M_Opc);
    }

    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, RL_DPC, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&M_Dpc, ie, ieLen);
        mtp3_hdr.SetDPC(M_Dpc);
        printf(" Parameter:: MTP3 DPC is %d\n", M_Dpc);
    }

    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, RL_SLS, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&Sls, ie, ieLen);
        mtp3_hdr.SetDPC(Sls);
        printf(" Parameter:: MTP3 SLS is %d\n", Sls);
    }

    printf("SetMTP3andSCCPAddress::Setting up called party address\n");

    /* Set the Point code for Called Party Address */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_PC, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_pc, ie, ieLen);
        cdp->SetPointCode(cdp_pc);
        printf(" Parameter:: CDP_PC is %d\n", cdp_pc);
    }

    /* Set the Destination Sub System Number in Called Party Address*/
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_SSN, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_ssn, ie, ieLen);
        cdp->SetSSN(cdp_ssn);
        printf(" Parameter:: CDP_SSN is %d\n", cdp->GetSSN());
    }

    /* Setting this true sets routing by PC-SSN, 
     Set this false for GTT Routing */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_ROUT_TYPE, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_route_type, ie, ieLen);
        cdp->SetRouteByPCSSN(cdp_route_type);
        printf(" Parameter:: CDP_RoutingType is %d\n", cdp_route_type);
    }

    /* ITU */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_NI, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_ni, ie, ieLen);
        cdp->SetInternationalRouting(cdp_ni);
        printf(" Parameter:: CDP_NI is %d\n", cdp_ni);
    }

    /* Set for GTT Based Routing */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_GTT_TYPE, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_gtt_type, ie, ieLen);
        printf(" Parameter:: CDP_GTT_TYPE is %d\n", cdp_gtt_type);
    }

    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_GTT_DIG, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(cdp_gtt_dig, ie, ieLen);
        cdp_gtt_len = ieLen; 
        cdp->SetGlobalTitle(cdp_gtt_type, cdp_gtt_dig, cdp_gtt_len);
        printf(" Parameter:: CDP_GTT_DIG:");
        for (int i = 0; i < cdp_gtt_len; i++)
        printf("%02x ", cdp_gtt_dig[i]);
        printf("\n");
    }

    /*Calling party is populated only in case of CR*/
    if ((msgtype == SCCP_MSG_CR) || (msgtype == SCCP_MSG_UDT)) 
    {
        printf("SetMTP3andSCCPAddress::Setting up calling party address\n");

        /* Set Originating Point code */
        memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
        ReadMsgParam(SCCP_MSG_CR, CGP_PC, filename, ie, &ieLen);
        if (ie[0] != NULL)
        {
            memcpy(&cgp_pc, ie, ieLen);
            cpa->SetPointCode(cgp_pc);
            printf(" Parameter:: CGP_PC is %d\n", cgp_pc);
        }
      
        /* Set the Originating Sub System Number */
        memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
        ReadMsgParam(SCCP_MSG_CR, CGP_SSN, filename, ie, &ieLen);
        if (ie[0] != NULL)
        {
            memcpy(&cgp_ssn, ie, ieLen);
            cpa->SetSSN(cgp_ssn);
            printf(" Parameter:: CGP_SSN is %d\n", cgp_ssn);
        }

        /* Set Routing Routing by Point Code SSN TRUE */
        memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
        ReadMsgParam(msgtype, CGP_ROUT_TYPE, filename, ie, &ieLen);
        if (ie[0] != NULL)
        {
            memcpy(&cgp_route_type, ie, ieLen);
            cpa->SetRouteByPCSSN(cgp_route_type);
            printf(" Parameter:: CGP_RoutingType is %d\n", cgp_route_type);
        }

        /* Set InterNational routing to true */
        memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
        ReadMsgParam(msgtype, CGP_NI, filename, ie, &ieLen);
        if (ie[0] != NULL)
        {
            memcpy(&cgp_ni, ie, ieLen);
            cpa->SetInternationalRouting(cgp_ni);
            printf(" Parameter:: CGP_NI is %d\n", cgp_ni);
        }

        /* Set for GTT Based Routing */
        memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
        ReadMsgParam(msgtype, CGP_GTT_TYPE, filename, ie, &ieLen);
        if (ie[0] != NULL)
        {
            memcpy(&cgp_gtt_type, ie, ieLen);
            printf(" Parameter:: CGP_GTT_TYPE is %d\n", cgp_gtt_type);
        }
        memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
        ReadMsgParam(msgtype, CGP_GTT_DIG, filename, ie, &ieLen);

        if (ie[0] != NULL)
        {
            memcpy(cgp_gtt_dig, ie, ieLen);
            cgp_gtt_len = ieLen;
            cpa->SetGlobalTitle(cgp_gtt_type, cgp_gtt_dig, cgp_gtt_len);
            printf(" Parameter:: CGP_GTTDIG:");
            for (int i = 0; i < cgp_gtt_len; i++)
            printf("%02x ", cgp_gtt_dig[i]);
            printf("\n");
        }
    }

    printf("\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sets an SCCP Address by reading from a file and stores the
 *      information in MTP3 Header, CalledParty Address.
 *
 *  Input Parameters:
 *      msgType - SCCP message code
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      mtp3_hdr - reference to MTP3_Header
 *      cdp - pointer to SCCP_CalledPartyAddr
 *
 *  Return Value:
 *     None.
 *
 *  See Also:
 ****************************************************************************/
void
SetMTP3andSCCPAddress(int msgtype,
               MTP3_Header &mtp3_hdr,
               SCCP_CalledPartyAddr *cdp)
{
    int          ieLen = 0;
    ITS_OCTET    ie[100];

    ITS_OCTET M_Dpc = 0;
    ITS_OCTET Sls = 0;

    ITS_OCTET cdp_pc = 0;
    ITS_OCTET cdp_ssn = 0;
    ITS_OCTET cdp_gtt_dig[SCCP_MAX_ADDR_LEN];
    ITS_USHORT cdp_gtt_len = 0;
    ITS_OCTET cdp_gtt_type = 0;
    ITS_OCTET cdp_ni = 0;
    ITS_OCTET cdp_route_type = 0;

    printf("SetMTP3andSCCPAddress::Setting up MTP3 Routing Lable\n");

    ITS_OCTET M_Opc = 0;
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, RL_OPC, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&M_Opc, ie, ieLen);
        printf(" Parameter:: MTP3 OPC is %d\n", M_Opc);
        mtp3_hdr.SetOPC(M_Opc);
    }

    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, RL_DPC, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&M_Dpc, ie, ieLen);
        printf(" Parameter:: MTP3 DPC is %d\n", M_Dpc);
        mtp3_hdr.SetDPC(M_Dpc);
    }

    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, RL_SLS, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&Sls, ie, ieLen);
        printf(" Parameter:: MTP3 SLS is %d\n", Sls);
        mtp3_hdr.SetDPC(Sls);
    }

    printf("SetMTP3andSCCPAddress::Setting up called party address\n");

    /* Set the Point code for Called Party Address */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_PC, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_pc, ie, ieLen);
        printf(" Parameter:: CDP_PC is %d\n", cdp_pc);
        cdp->SetPointCode(cdp_pc);
    }

    /* Set the Destination Sub System Number in Called Party Address*/
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_SSN, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_ssn, ie, ieLen);
        printf(" Parameter:: CDP_SSN is %d\n", cdp_ssn);
        cdp->SetSSN(cdp_ssn);
    }

    /* Setting this true sets routing by PC-SSN,
     Set this false for GTT Routing */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_ROUT_TYPE, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_route_type, ie, ieLen);
        printf(" Parameter:: CDP_RoutingType is %d\n", cdp_route_type);
        cdp->SetRouteByPCSSN(cdp_route_type);
    }

    /* ITU */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_NI, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_ni, ie, ieLen);
        printf(" Parameter:: CDP_NI is %d\n", cdp_ni);
        cdp->SetInternationalRouting(cdp_ni);
    }

    /* Set for GTT Based Routing */
    /* SetGlobalTitleAddr(cdp); */

    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_GTT_TYPE, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&cdp_gtt_type, ie, ieLen);
        printf(" Parameter:: CDP_GTT_TYPE is %d\n", cdp_gtt_type);
    }

    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(msgtype, CDP_GTT_DIG, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(cdp_gtt_dig, ie, ieLen);
        cdp_gtt_len = ieLen;
        cdp->SetGlobalTitle(cdp_gtt_type, cdp_gtt_dig, cdp_gtt_len);
        printf(" Parameter:: CDP_GTT_DIG:");
        for (int i = 0; i < cdp_gtt_len; i++)
        printf("%02x ", cdp_gtt_dig[i]);
        printf("\n");
    }

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function saves the slr, dlr, mtp3 header, Calling Party Addr 
 *      and Called Party Addr in the DSM table w.r.t conref.
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
 *      ITS_TRUE  - On Success
 *      ITS_FALSE - On Failed
 ****************************************************************************/
ITS_BOOLEAN
SaveContextInfo(ITS_CTXT conref, SCCP_CONN_STATE state,
                MTP3_Header *mtp3,
                SCCP_CallingPartyAddr *cgpa, 
                SCCP_CalledPartyAddr *cdpa,
                ITS_CTXT dlref, ITS_CTXT slref)
{
    DsmInfo *dsm_ptr = NULL;
    int error;
    ITS_BOOLEAN ret = ITS_FALSE;
    ITS_BOOLEAN initiator = ITS_FALSE;

    if (RetrieveContext(&dsm_ptr, (ITS_OCTET*)&conref, sizeof(ITS_USHORT)) != ITS_SUCCESS)
    {
        /* First time you alloc it - sending/receiving CR */

        if ((state == SCCP_CONN_OUT_PEND) || (state == SCCP_CONN_IN_PEND))
        {
            APP_TRACE_DEBUG(("SaveContext::DSM_Find failed: conref %d ", conref));

             dsm_ptr = (DsmInfo*) DSM_Alloc(APP_FT_GROUP_ID, APP_FT_TABLE_ID,
                                (ITS_OCTET*)&conref, sizeof(ITS_USHORT),
                                sizeof(DsmInfo), &error);

            if (state == SCCP_CONN_IN_PEND)
            {
                dsm_ptr->src = ITS_FALSE;
            }
            else 
            {
                dsm_ptr->src = ITS_TRUE;
            } 
        }
        else
        {
            APP_TRACE_DEBUG(("SaveContextInfo::Retrieve Context failed: conref %x \n",
                                                                              conref));
            return ITS_FALSE;
        }
    }

    if (mtp3 != NULL)
    {
        dsm_ptr->opc = mtp3->GetOPC();
        dsm_ptr->dpc = mtp3->GetDPC();
    }

    if (cgpa != NULL)
    {
        dsm_ptr->cgpa = cgpa;
    }

    if (cdpa != NULL)
    {
        dsm_ptr->cdpa = cdpa;
    }

    if (dlref != 0)
    {
        dsm_ptr->sccpinfo.dlr = dlref;
    }

    if (slref != 0)
    {
        dsm_ptr->sccpinfo.slr = slref;
    }

    dsm_ptr->sccpinfo.state = state;

    if (SaveContext(dsm_ptr, (ITS_OCTET*)&conref, sizeof(ITS_USHORT)) == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SaveContextInfo: Saving SCCP Context Info: %d ", conref));
        ret = ITS_TRUE;
    }
    else
    {
        APP_TRACE_DEBUG(("SaveContextInfo:: Saving SCCP Context Info failed"
                          " for conref:%d \n", conref));
    }

    return ret;
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Connection Request Message
 *
 *  Input Parameters:
 *      its::HDR hdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
void
SendCR(ITS_HDR hdr)
{
    SCCP_ConnectionRequest cr;
    ITS_HDR     shdr;
    ITS_INT     ret = ITS_SUCCESS;
    ITS_INT     result = ITS_SUCCESS;
    ITS_OCTET   pclass = 0;
    ITS_OCTET   hcount = 0;
    ITS_OCTET   credit_value = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];
    ITS_INT     conref;

    SCCP_UserData ud;
    ITS_OCTET data[1024];
    int len;


    MTP3_Header mtp3_hdr;
    SCCP_CallingPartyAddr *cpa = new SCCP_CallingPartyAddr;
    SCCP_CalledPartyAddr *cdp = new SCCP_CalledPartyAddr;

    /* build a message */
    printf("Reading Parameters from File: %s\n", filename); 

    SetMTP3andSCCPAddress(SCCP_MSG_CR, mtp3_hdr, cpa, cdp);

    ret = SCCP_GetNextLocalRef(ISS7_Stack, &shdr.context.conref);
    if(ret == ITS_SUCCESS)
    {
       printf(" Successfully assigned Conref \n");
    }
    else
    {
       printf(" Failure to assign Conref \n");
    }

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(hdr.context.conref);

    cr.AddIE(&slr);

    /* Protocol Class */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CR, SCCP_PRM_PROTOCOL_CLASS, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&pclass, ie, ieLen);
        printf(" Parameter:: PCLASS is %d\n", pclass);
    }

    SCCP_ProtocolClass pc;
    pc.SetProtocolClass(pclass);
    cr.AddIE(&pc);

    /* Called Party Address */
    cr.AddIE(cdp);

    /* Calling Party Address */
    cr.AddIE(cpa);

    SaveContextInfo(shdr.context.conref, SCCP_CONN_OUT_PEND, &mtp3_hdr, cpa, cdp,
                    0, hdr.context.conref);

    /*Credit Value*/
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CR, SCCP_PRM_CREDIT, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&credit_value, ie, ieLen);
        printf(" Parameter:: Credit_value is %d\n", credit_value);
    }

    SCCP_Credit credit;
    credit.SetCredit(credit_value);
    cr.AddIE(&credit);

    /* Data */
    BuildMsg(data, &len);
    ud.SetUserData(data, len);
    cr.AddIE(&ud);

    /*Hop Count*/
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CR, SCCP_PRM_HOP_COUNTER, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&hcount, ie, ieLen);
        printf(" Parameter:: Hop Count is %d\n", hcount);
    }

    SCCP_HopCount hc;
    hc.SetHopCount(hcount);
    cr.AddIE(&hc);

    printf("\n");
    //PrintCR((SCCP_MessageClass*)&cr);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &hdr, &cr);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendCR:: SCCP Send CR successful \n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendCR:: SCCP Send CR failure ret = %x \n", ret));
    }
}

void
SendUDT(ITS_HDR hdr)
{
    SCCP_UnitData ud;
    ITS_HDR     shdr;
    ITS_INT     ret = ITS_SUCCESS;
    ITS_INT     result = ITS_SUCCESS;
    ITS_OCTET   pclass = 0;
    ITS_OCTET   hcount = 0;
    ITS_OCTET   credit_value = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];
    ITS_INT     conref;

    ITS_OCTET data[1024];
    int len;


    MTP3_Header mtp3_hdr;
    SCCP_CallingPartyAddr *cpa = new SCCP_CallingPartyAddr;
    SCCP_CalledPartyAddr *cdp = new SCCP_CalledPartyAddr;

    /* build a message */
    printf("Reading Parameters from File: %s\n", filename); 

    SetMTP3andSCCPAddress(SCCP_MSG_UDT, mtp3_hdr, cpa, cdp);

    /* Protocol Class */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_UDT, SCCP_PRM_PROTOCOL_CLASS, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&pclass, ie, ieLen);
        printf(" Parameter:: PCLASS is %d\n", pclass);
    }

    SCCP_ProtocolClass pc;
    pc.SetProtocolClass(pclass);
    ud.AddIE(&pc);

    /* Called Party Address */
    ud.AddIE(cdp);

    /* Calling Party Address */
    ud.AddIE(cpa);

    /* Data */
    SCCP_UserData udt;
    BuildMsg(data, &len);
    udt.SetUserData(data, len);
    ud.AddIE(&udt);

    printf("\n");

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &hdr, &ud);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendUDT:: SCCP Send UDT successful \n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendUDT:: SCCP Send UDT failure ret = %x \n", ret));
    }
}


/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Connection Confirm Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/

void
SendCC(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET pclass = 0;
    ITS_OCTET credit_value = 0;
    int          ieLen = 0;
    ITS_OCTET    ie[100];

    MTP3_Header mtp3_hdr;
    SCCP_CalledPartyAddr *cdp = new SCCP_CalledPartyAddr;

    /*Send a CC message*/
    printf("Reading Parameters from File: %s\n", filename);

    SetMTP3andSCCPAddress(SCCP_MSG_CC, mtp3_hdr, cdp);

    SCCP_ConnectionConfirm cc;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    cc.AddIE(&dlr);
    printf(" Parameter:: DLR is %d\n", reshdr.context.conref);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(srchdr.context.conref);
    cc.AddIE(&slr);
    printf(" Parameter:: SLR is %d\n", srchdr.context.conref);

    /*CC Protocol Class Input */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CC, SCCP_PRM_PROTOCOL_CLASS, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&pclass, ie, ieLen);
        printf(" Parameter:: PCLASS is %d\n", pclass);
    }

    SCCP_ProtocolClass pc;
    pc.SetProtocolClass(pclass);
    cc.AddIE(&pc);

    /*Credit value */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CC, SCCP_PRM_CREDIT, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&credit_value, ie, ieLen);
        printf(" Parameter:: Credit_value is %d\n", credit_value);
    }

    SCCP_Credit credit;
    credit.SetCredit(credit_value);
    cc.AddIE(&credit);

    /* Called Party Address*/
    cc.AddIE(cdp);

    /* Future: Populate Data */
    /* Data */
    SCCP_UserData ud;
    cc.AddIE(&ud);

    printf("\n");

    SaveContextInfo(conref, SCCP_DATA_TRANSFER, 0, 0, 0,
                    reshdr.context.conref, srchdr.context.conref);

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &cc);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendCC: SCCP Send CC successful \n"));
    }
    else
    {
         APP_TRACE_DEBUG(("SendCC: SCCP Send CC failure ret = %x \n", ret));
    }
}
/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Connection Refused Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
void
SendCREF(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET   refusal_cause = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];

    MTP3_Header mtp3_hdr;
    SCCP_CalledPartyAddr *cdp = new SCCP_CalledPartyAddr;

    // Send a CREF message
    printf("Reading Parameters from File: %s\n", filename);

    SetMTP3andSCCPAddress(SCCP_MSG_CREF, mtp3_hdr, cdp);

    SCCP_ConnectionRefused cref;

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    cref.AddIE(&dlr);

    /* Refusal Cause */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CREF, SCCP_PRM_REFUSAL_CAUSE, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&refusal_cause, ie, ieLen);
        printf(" Parameter:: REFUSAL_CAUSE is %d\n", refusal_cause);
    }

    SCCP_RefusalCause rc(refusal_cause);
    cref.AddIE(&rc);

    /*** Data ***/
    SCCP_UserData ud;
    cref.AddIE(&ud);

    printf("\n");

    DeleteContext((ITS_OCTET*)&conref, sizeof(ITS_USHORT));

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &cref);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendCREF: SCCP Send CREF successful\n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendCREF:: SCCP Send CREF failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Released Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
void
SendRLSD(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET   release_cause = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];

    SCCP_Released rlsd;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    rlsd.AddIE(&dlr);
    printf(" Parameter:: DLR is %d\n", reshdr.context.conref);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(srchdr.context.conref);
    rlsd.AddIE(&slr);
    printf(" Parameter:: SLR is %d\n", srchdr.context.conref);

    /* Released Cause */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_RLSD, SCCP_PRM_RELEASE_CAUSE, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&release_cause, ie, ieLen);
        printf(" Parameter:: RELEASE_CAUSE is %d\n", release_cause);
    }

    SCCP_ReleaseCause rc(release_cause); 
    rlsd.AddIE(&rc);

    /* Data */
    SCCP_UserData ud;
    rlsd.AddIE(&ud);

    printf("\n");

    SaveContextInfo(conref,SCCP_OUT_RELEASE_PEND, 0, 0, 0, 0, 0);

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &rlsd);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendRLSD::SCCP Send RLSD successful\n"));
        printf(" ############## RLSD Send ###########\n");
    }
    else
    {
        APP_TRACE_DEBUG(("SendRLSD:: SCCP Send RLSD failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Release Complete Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/

void
SendRLC(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    SCCP_ReleaseComplete rlc;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    rlc.AddIE(&dlr);
    printf(" Parameter:: DLR is %d\n", reshdr.context.conref);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(srchdr.context.conref);
    rlc.AddIE(&slr);
    printf(" Parameter:: SLR is %d\n", srchdr.context.conref);

    printf("\n");

    DeleteContext((ITS_OCTET*)&conref, sizeof(ITS_USHORT));

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &rlc);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendRLC:: SCCP Send RLC successful\n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendRLC:: SCCP Send RLC failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Data Transfer Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/

void
SendDT1(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_HDR crefhdr;
    ITS_OCTET   seg_reassmb = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];

    SCCP_UserData ud;
    ITS_OCTET data[1024];
    int len;

    /* create a message */
    SCCP_DataForm1 dt1;

    printf("Reading Parameters from File: %s\n", filename);

    crefhdr.context.conref = conref;
    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    dt1.AddIE(&dlr);

    /* segmenting/reassembling */
    SCCP_SegmentReassem sr(0); //more data
    dt1.AddIE(&sr);

    /*  implementation can be changed to:
    SCCP_SegmentReassem sr();
    sr.SetSegmentReassem(seg_reassmb);   NOTE: 0 means no data */

    SaveContextInfo(conref, SCCP_DATA_TRANSFER, 0, 0, 0, 0, 0);

    /* Data */                                  //2-256
    BuildMsg(data, &len);
    ud.SetUserData(data, len);
    dt1.AddIE(&ud);

    printf("\n");

    ret = SCCP_MessageClass::Send(ISS7_Stack, &crefhdr, &dt1);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(( "SendDT1: SCCP Send DT1 successful\n"));
    }
    else
    {
        APP_TRACE_DEBUG(( "SendDT1: SCCP Send DT1 failure ret = %x\n", ret));
    }

}

/*****************************************************************************
 *  Purpose:
 *  This function is used for Data Transfer Message for Protocol class 3
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
void
SendDT2(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET   seq_segm = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];

    SCCP_UserData ud;
    ITS_OCTET data[1024];
    int len;

    /* create a message */
    SCCP_DataForm2 dt2;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    dt2.AddIE(&dlr);

    /* Sequencing/segmenting */
    SCCP_SequenceSegment ss(1,2,1); // tsn=1, rsn=2, haveMore=1
    dt2.AddIE(&ss);

    /* Data */
    BuildMsg(data, &len);
    ud.SetUserData(data, len);
    dt2.AddIE(&ud);

    printf("\n");

    SaveContextInfo(conref, SCCP_DATA_TRANSFER, 0, 0, 0, reshdr.context.conref, 0);

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &dt2);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendDT2::SCCP Send DT2 successfully \n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendDT2::SCCP Send DT2 failed, ret = %x\n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Acknowledgement Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/

void
SendAK(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET   credit_value = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];

    /* create a message */

    SCCP_Acknowledge ack;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    ack.AddIE(&dlr);

    /* receive sequence number */
    SCCP_ReceiveSequenceNum rsn(1,0); //rsn=1, haveMore=0
    ack.AddIE(&rsn);

    /*Credit Value*/
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_AK, SCCP_PRM_CREDIT, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&credit_value, ie, ieLen);
        printf(" Parameter:: Credit_value is %d\n", credit_value);
    }

    SCCP_Credit credit(credit_value);
    ack.AddIE(&credit);

    printf("\n");

    SaveContextInfo(conref, SCCP_DATA_TRANSFER, 0, 0, 0, 0, 0);

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &ack);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendAK::SCCP Send AK successfull\n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendAK:: SCCP Send AK failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Expedited Data  Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/

void
SendED(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET   pclass = 0;
    ITS_OCTET   ie[100];
    ITS_INT     ieLen = 0;

    /* build a message */
    SCCP_ExpeditedData ed;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    ed.AddIE(&dlr);

    /* Protocol Class */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CR, SCCP_PRM_PROTOCOL_CLASS, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&pclass, ie, ieLen);
        printf(" Parameter:: PCLASS is %d\n", pclass);
    }

    SCCP_ProtocolClass pc;
    pc.SetProtocolClass(pclass);
    ed.AddIE(&pc);

    /* Data */                                      //2-33
    SCCP_UserData ud;
    ed.AddIE(&ud);

    printf("\n");

    /* Send the message  */
    SaveContextInfo(conref, SCCP_DATA_TRANSFER, 0, 0, 0, 0, 0);

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &ed);

    if(ret == ITS_SUCCESS)
    {

        APP_TRACE_DEBUG(("SendED::SCCP Send ED successful\n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendED:: SCCP Send ED failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Expedited Data Ack Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/

void
SendEA(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET   pclass = 0;
    ITS_OCTET   ie[100];
    ITS_INT     ieLen = 0;

    /* build a message */
    SCCP_ExpeditedDataAcknowledge ea;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    ea.AddIE(&dlr);

    /* Protocol Class */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CR, SCCP_PRM_PROTOCOL_CLASS, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&pclass, ie, ieLen);
        printf(" Parameter:: PCLASS is %d\n", pclass);
    }

    SCCP_ProtocolClass pc;
    pc.SetProtocolClass(pclass);
    ea.AddIE(&pc);

    printf("\n");

    /* Send the message  */
    SaveContextInfo(conref, SCCP_DATA_TRANSFER, 0, 0, 0, 0, 0);

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &ea);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendEA::SCCP Send EA successfull\n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendEA:: SCCP Send EA failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Reset Request Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 ****************************************************************************/
void
SendRSR(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET   reset_cause = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];

    /* build a message */
    SCCP_ResetRequest rsr;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    rsr.AddIE(&dlr);
    printf(" Parameter:: DLR is %d\n", reshdr.context.conref);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(srchdr.context.conref);
    rsr.AddIE(&slr);
    printf(" Parameter:: SLR is %d\n", srchdr.context.conref);

    /* Reset cause */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_RSR, SCCP_PRM_RESET_CAUSE, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&reset_cause, ie, ieLen);
        printf(" Parameter:: RELEASE_CAUSE is %d\n", reset_cause);
    }

    SCCP_ResetCause rc(reset_cause);
    rsr.AddIE(&rc);

    printf("\n");

    SaveContextInfo(conref, SCCP_OUT_RESET_PEND, 0, 0, 0, 0, 0);

    /* Send the message  */
    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &rsr);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendRSR::SCCP Send RSR successful\n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendRSR:: SCCP Send RSR failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Reset Confirmation Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/

void
SendRSC(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;

    /* build a message */
    SCCP_ResetConfirm rsc;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    rsc.AddIE(&dlr);
    printf(" Parameter:: DLR is %d\n", reshdr.context.conref);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(srchdr.context.conref);
    rsc.AddIE(&slr);
    printf(" Parameter:: SLR is %d\n", srchdr.context.conref);

    printf("\n");

    /* Send the message  */
    SaveContextInfo(conref, SCCP_DATA_TRANSFER, 0, 0, 0, 0, 0);

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &rsc);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendRSC::SCCP Send RSC successful\n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendRSC:: SCCP Send RSC failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending Error Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, its::HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/

void
SendERR(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET   err_cause = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];

    /* build a message */
    SCCP_Error err;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    err.AddIE(&dlr);

    /* error cause */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_ERR, SCCP_PRM_ERROR_CAUSE, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&err_cause, ie, ieLen);
        printf(" Parameter:: ERROR_CAUSE is %d\n", err_cause);
    }

    SCCP_ErrorCause ec(err_cause);
    err.AddIE(&ec);

    printf("\n");

    /* Send the message  */
    DeleteContext((ITS_OCTET*)&conref, sizeof(ITS_USHORT));

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &err);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG((" SendERR::SCCP Send ERR successful \n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendERR:: SCCP Send ERR failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Sending In-Activity  Message
 *
 *  Input Parameters:
 *     ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/

void
SendIT(ITS_CTXT conref, ITS_HDR srchdr, ITS_HDR reshdr)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_OCTET   seq_segm = 0;
    ITS_OCTET   pclass = 0;
    ITS_OCTET   credit_value = 0;
    ITS_INT     ieLen = 0;
    ITS_OCTET   ie[100];

    /* build a message */
    SCCP_InactivityTest it;

    printf("Reading Parameters from File: %s\n", filename);

    /* Destination Local Reference */
    SCCP_DestinationLocalRef dlr(reshdr.context.conref);
    it.AddIE(&dlr);
    printf(" Parameter:: DLR is %d\n", reshdr.context.conref);

    /* Source Local Reference */
    SCCP_SourceLocalRef slr(srchdr.context.conref);
    it.AddIE(&slr);
    printf(" Parameter:: SLR is %d\n", srchdr.context.conref);

    /* Protocol Class */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CR, SCCP_PRM_PROTOCOL_CLASS, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&pclass, ie, ieLen);
        printf(" Parameter:: PCLASS is %d\n", pclass);
    }

    SCCP_ProtocolClass pc;
    pc.SetProtocolClass(pclass);
    it.AddIE(&pc);

    /* Sequencing/segmenting */
    SCCP_SequenceSegment ss(1,2,1); // tsn=1, rsn=2, haveMore=1
    it.AddIE(&ss);

    /* Credit */
    memset((void*)ie, 0, 100*sizeof(ITS_OCTET));
    ReadMsgParam(SCCP_MSG_CR, SCCP_PRM_CREDIT, filename, ie, &ieLen);
    if (ie[0] != NULL)
    {
        memcpy(&credit_value, ie, ieLen);
        printf(" Parameter:: Credit_value is %d\n", credit_value);
    }

    SCCP_Credit credit;
    credit.SetCredit(credit_value);
    it.AddIE(&credit);

    printf("\n");

    /* Send the message  */

    ret = SCCP_MessageClass::Send(ISS7_Stack, &srchdr, &it);

    if(ret == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SendIT::SCCP Send IT successfull \n"));
    }
    else
    {
        APP_TRACE_DEBUG(("SendIT:: SCCP Send IT failure ret = %x \n", ret));
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function This is a blocking call waits till it receives an event.
 *      And when an event occurs processes it based on message type.
 *
 *  Input Parameters:
 *      engine::Worker work, its::Event event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE. On returning this value the worker thread will be
 *                returned to avail threads.
 ****************************************************************************/
int
ProcessSCCPMsg(its::ThreadPoolThread *thr, Event& evt)
{
    ITS_INT    ret   = ITS_SUCCESS;
    SCCP_MessageClass *sccpmsg;
    ITS_HDR hdr, rhdr;
    ITS_UINT slr_get, dlr_get;
    int          offset = 0;
    ITS_CTXT     Conref =0;
    MTP3_Header  mtp3_hdr;
    MTP3_HEADER  mtp3;
    MTP3_ROUTING_LABEL label;
    ITS_OCTET* event_data;

    engine::Worker* work = (engine::Worker*)thr;
    int instance = work->GetInstance();

    APP_TRACE_DEBUG(("ProcessSCCPMsg\n"));

    offset = PrintMsg(evt);

    memset((void*)&mtp3, 0, sizeof(MTP3_Header));

    event_data = (ITS_OCTET*)malloc(evt.GetLength() * sizeof(ITS_OCTET));
    memcpy((void*)event_data, evt.GetData(), evt.GetLength());

    memcpy((void*)&mtp3, &event_data[offset], sizeof(MTP3_HEADER));

    mtp3_hdr.SetHeader(mtp3);

    if(evt.GetSource() == ITS_SCCP_SRC)
    {
        /* receive the message */
        int ret = SCCP_MessageClass::Receive(ISS7_Stack, &hdr, evt,
                                              &sccpmsg);

        if (ret == ITS_SUCCESS)
        {
            APP_TRACE_DEBUG(("ProcessSCCPMsg:: SCCP_MessageClass Received "
                                             "Successful\n"));
        }
        else
        {
            APP_TRACE_DEBUG(("ProcessSCCPMsg:: SCCP_MessageClass Received "
                                             "Failed\n"));
        }

        switch (sccpmsg->GetMsgType())
        {
            case SCCP_MSG_UDT:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message UDT\n"));
                                                                                                                                              
                PrintUDT(sccpmsg);
                                                                                                                                              
             #if 0
                SCCP_SourceLocalRef *slr =
                (SCCP_SourceLocalRef *)sccpmsg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
                slr_get = slr->GetRefNum();
             #endif

                SCCP_CalledPartyAddr *called_pa =
                (SCCP_CalledPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);
                                                                                                                                              
                SCCP_CallingPartyAddr *calling_pa =
                (SCCP_CallingPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
                                                                                                                                              
                /* Saving mtp3_hdr, calling_pa, called_pa in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_DATA_TRANSFER,
                                &mtp3_hdr, calling_pa, called_pa,
                                0, 0);
                break;
            }
 
            case SCCP_MSG_CR:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message CR\n"));

                //PrintCR(sccpmsg);

                SCCP_SourceLocalRef *slr =
                (SCCP_SourceLocalRef *)sccpmsg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
                slr_get = slr->GetRefNum();


                SCCP_CalledPartyAddr *called_pa =
                (SCCP_CalledPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);

                SCCP_CallingPartyAddr *calling_pa =
                (SCCP_CallingPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
              
                /* Saving mtp3_hdr, calling_pa, called_pa, slr in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_CONN_IN_PEND, 
                                &mtp3_hdr, calling_pa, called_pa, 
                                0, slr_get);
                break;
            }

            case SCCP_MSG_CC:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message CC"));

                PrintCC(sccpmsg);

                SCCP_DestinationLocalRef *dlr =
                (SCCP_DestinationLocalRef *)sccpmsg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
                dlr_get = dlr->GetRefNum();

                SCCP_SourceLocalRef *slr =
                (SCCP_SourceLocalRef *)sccpmsg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
                slr_get = slr->GetRefNum();

                /* Updating dlr and connection State in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_DATA_TRANSFER, 0, 0, 0, 
                                dlr_get, slr_get);
                break;
            }

            case SCCP_MSG_DT1:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message DT1"));

                PrintDT1(sccpmsg);

                /* Updating connection State in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_DATA_TRANSFER,
                                0, 0, 0, 0, 0);
                break;
            }

            case SCCP_MSG_DT2:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message DT2"));

                PrintDT2(sccpmsg);

                /* Updating connection State in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_DATA_TRANSFER,
                                0, 0, 0, 0, 0);
                break;
            }

            case SCCP_MSG_RLSD:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message RLSD"));

                PrintRLSD(sccpmsg);

                /* Remember to delete context before winding up session */
                DeleteContext((ITS_OCTET*)&hdr.context.conref,
                                sizeof(ITS_USHORT));
                break;
            }

            case SCCP_MSG_RLC:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP message RLC\n"));

                PrintRLC(sccpmsg);

                /* Remember to delete context before winding up session */
                DeleteContext((ITS_OCTET*)&hdr.context.conref, sizeof(ITS_USHORT));
                break;
            }

            case SCCP_MSG_CREF:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message CREF"));

                PrintCREF(sccpmsg);

                /* Remember to delete context before winding up session */
                DeleteContext((ITS_OCTET*)&hdr.context.conref, sizeof(ITS_USHORT));
                break;
            }

            case SCCP_MSG_RSR:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message RSR"));

                PrintRSR(sccpmsg);

                /* Updating connection State in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_IN_RESET_PEND,
                                0, 0, 0, 0, 0);
                break;

            }

            case SCCP_MSG_RSC:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message RSC"));

                PrintRSC(sccpmsg);

                /* Updating connection State in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_DATA_TRANSFER,
                                0, 0, 0, 0, 0);
                break;

            }

            case SCCP_MSG_ERR:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message ERR"));

                PrintERR(sccpmsg);

                /* Remember to delete context before winding up session */
                DeleteContext((ITS_OCTET*)&hdr.context.conref, sizeof(ITS_USHORT));
                break;
            }

            case SCCP_MSG_IT:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message IT"));

                PrintIT(sccpmsg);
                break;
            }

            case SCCP_MSG_ED:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message ED \n"));

                PrintED(sccpmsg);

                /* Updating connection State in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_DATA_TRANSFER,
                                0, 0, 0, 0, 0);
                break;

            }

            case SCCP_MSG_EA:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message EA\n"));

                PrintEA(sccpmsg);

                /* Updating connection State in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_DATA_TRANSFER,
                                0, 0, 0, 0, 0);
                break;
            }

            case SCCP_MSG_AK:
            {
                APP_TRACE_DEBUG(("ProcessSCCPMsg::Received SCCP Message AK"));

                PrintAK(sccpmsg);

                /* Updating connection State in DSM */
                SaveContextInfo(hdr.context.conref, SCCP_DATA_TRANSFER,
                                0, 0, 0, 0, 0);
                break;
            }

            default:
                APP_TRACE_ERROR(("ProcessSCCPMsg::Received UNKNOWN Message %x",
                                                       sccpmsg->GetMsgType()));
                break;
        }

    }
    return ITS_TRUE;
}
