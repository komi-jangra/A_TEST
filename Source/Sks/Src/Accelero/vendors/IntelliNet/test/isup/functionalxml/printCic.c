/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: printCic.c,v 1.1.1.1 2007-10-08 11:12:21 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:24:57  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:15:15  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:55:07  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.4  2005/03/21 13:54:19  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.5.2.2.6.1  2004/03/23 10:44:04  sjaddu
 * Some funcs are changed for 6.3
 *
 * Revision 7.5.2.2  2003/05/07 11:10:02  ssingh
 * Conformation Indication related code removed. Not in Use.
 *
 * Revision 7.5.2.1  2003/03/27 13:07:33  akumar
 * Removed Extra Ref to the Stack
 *
 * Revision 7.5  2003/02/07 05:08:58  ssingh
 * ReserveCIC related Changes.
 *
 * Revision 7.4  2003/01/31 13:10:08  ssingh
 * Changes done to support new state intorduced for CRI; WAIT_FOR_LPA
 *
 * Revision 7.3  2003/01/17 16:25:22  sjaddu
 * added Cic Rule ..
 *
 * Revision 7.2  2002/10/30 10:27:09  sjaddu
 * Added new COT states.
 *
 * Revision 7.1  2002/08/26 22:10:38  mmiers
 * Begin PR6.2
 *
 * Revision 1.7  2002/08/02 16:18:40  ssingh
 * Peg functionality updated.
 *
 * Revision 1.6  2002/08/01 16:01:45  ssharma
 * Merge from ISUP_PR7 branch.
 *
 * Revision 1.5.2.9  2002/07/31 22:26:19  ssharma
 * ITU pegs.
 *
 * Revision 1.5.2.8  2002/07/25 21:21:24  ssingh
 * Indication handling ISUP_ReceiveMsg.
 *
 * Revision 1.5.2.7  2002/07/12 14:05:26  hbalimid
 * CQM moved to CSC.
 *
 * Revision 1.5.2.6  2002/07/10 21:54:53  ssingh
 * Modified PrintCic for ANSI
 *
 * Revision 1.5.2.5  2002/07/10 14:31:19  hbalimid
 * Added Cic State descriptions for ANSI
 *
 * Revision 1.5.2.4  2002/07/07 00:45:31  hbalimid
 * fixed ansi states.
 *
 * Revision 1.5.2.3  2002/07/06 23:53:50  hbalimid
 * Modified the ANSI states.
 *
 * Revision 1.5.2.2  2002/07/06 18:36:32  hbalimid
 * CVTR for ANSI in place.
 *
 * Revision 1.5.2.1  2002/07/06 06:16:21  hbalimid
 * Took care of all the warnings.
 *
 * Revision 1.5  2002/06/27 18:50:50  hbalimid
 * modifed PrintCicRecInfo for ANSI opc, dpc
 *
 * Revision 1.4  2002/06/27 18:07:13  ssingh
 * ANSI specific states updated.
 *
 * Revision 1.3  2002/06/27 17:43:51  hbalimid
 * Modified for ANSI testing.
 *
 * Revision 1.2  2002/05/20 15:58:48  sjaddu
 * Merge from PR6, remove unwanted directories.
 *
 * Revision 1.1.2.4  2002/05/09 18:42:32  labuser
 * Merge from ISUP_APR_19_2002 to PR6.
 *
 * Revision 1.1.2.3.2.3  2002/04/28 00:12:00  labuser
 * pcic used in validation of cic in place of ISUPvalidateCic
 *
 * Revision 1.1.2.3.2.2  2002/04/27 23:19:17  labuser
 * Added functionality for cic status over a range of cics
 *
 * Revision 1.1.2.3.2.1  2002/04/24 22:12:12  labuser
 * modified to get CIC status
 *
 * Revision 1.1.2.3  2002/04/13 06:20:56  hbalimid
 * modified for multiple variants
 *
 * Revision 1.1.2.2  2002/04/13 06:09:04  hbalimid
 * ISUP Functional test with NMS MTP3 and multiple vendor support at layer 2
 *
 *
 ****************************************************************************/

/* system includes */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* ITS includes */
#include <its_ss7_trans.h>

/* IntelliISUP includes */
#include <isup_intern.h>
#include <isup_variants.h>


#if defined (CCITT)
#define MAXCIC (1<<12)
#elif defined(ANSI)
#define MAXCIC  (1<<14)
#else
#error "Protocol family not defined."
#endif


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Validates a given cic range.
 *
 *  Input Parameters:
 *      ie - pointer to an ISUP information element
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
 ****************************************************************************/

int
ValidateCicRange(const char* cmdLine, ITS_USHORT* startcic, ITS_USHORT* endcic)
{
    char* tmp=NULL;
    char* sep=" \t";
    char *start, *end; 
    char cmd[256];
    ushort count=0;
    ushort len=0;
    ushort swap=0;

    if(cmdLine == NULL || startcic == NULL || endcic == NULL)
    {
        return !(ITS_SUCCESS);
    }

    memset(cmd, 0, sizeof(cmd));
    strcpy(cmd,cmdLine);
    tmp = strtok(cmd, sep);
    /* printf("tmp = *%s*, cmd = *%s*\n",tmp,cmd); */

    while( (tmp=strtok(NULL,sep)) != NULL )
    {
        count++;
        if( count == 1)
        {
            start = tmp;
            printf("start = *%s*\n", start);
        }
        else if( count == 2)
        {
            end = tmp;
            printf("end = *%s*\n", end);
        }
    }
    if( count != 2 )
    {
        printf("\nInvalid command given: \"%s\"\n",cmdLine);
        printf("Usage: cicrange <startcic> <endcic>\n");
        return !(ITS_SUCCESS);
    }

    len = strlen(start);
    tmp = start;
    while( isdigit((int)*tmp) ) tmp++;
    *tmp = 0;
    if( len == strlen(start) )
    {
        *startcic = atoi(start);
    }
    else
    {
        printf("\nInvalid command given: \"%s\"\n",cmdLine);
        printf("Usage: cicrange <startcic> <endcic>\n");
        return !(ITS_SUCCESS);
    }

    len = strlen(end);
    tmp = end;
    while( isdigit((int)*tmp) ) tmp++;
    *tmp = 0;
    if( len == strlen(end) )
    {
        *endcic = atoi(end);
    }
    else
    {
        printf("\nInvalid command given: \"%s\"\n",cmdLine);
        printf("Usage: cicrange <startcic> <endcic>\n");
        return !(ITS_SUCCESS);
    }

    /* swap */
    if( *startcic > *endcic ) 
    {
        printf("Given startcic(%d) is > endcic(%d); so swapping.\n", *startcic, *endcic);
        swap = *startcic;
        *startcic = *endcic;
        *endcic = swap;
    }

    /* printf("ValidateCicRange: startcic = *%d* endcic = *%d*\n", *startcic, *endcic); */
    return (ITS_SUCCESS);
}


/********************************************************************/
#if defined(CCITT)
/********************************************************************/

static char CPCFsmState[][64] = { "IDLE",
                                       "WAIT_INCOMING_ACM",
                                       "WAIT_INCOMING_ANM",
                                       "RCVD_INCOMING_ANM",
                                       "WAIT_INCOMING_RLC",
                                       "WAIT_INCOMING_RES",
                                       "WAIT_OUTGOING_ACM",
                                       "WAIT_OUTGOING_ANM",
                                       "SENT_OUTGOING_ANM",
                                       "WAIT_OUTGOING_RLC",
                                       "WAIT_OUTGOING_RES",
                                       "WAIT_OUTGOING_REL",
                                       "WAIT_OUTGOING_RSC",
                                       "WAIT_OUTGOING_GRA",
                                       "WAIT_CONTINUITY_REPORT",
                                       "WAIT_INCOMING_COT" };

static char BLSFsmState[][64] = { "BLS_IDLE",
                                      "BLS_WAIT_FOR_BLA",
                                      "BLS_LBLOCKED",
                                      "BLS_WAIT_FOR_UBA" };

static char BLRFsmState[][64] = { "BLR_IDLE",
                                      "BLR_WAIT_FOR_BLO_RESP",
                                      "BLR_RBLOCKED",
                                      "BLR_WAIT_FOR_UBL_RESP" };

static char MGBSFsmState[][64] = { "MGBS_IDLE",
                                       "MGBS_WAIT_FOR_CGBA",
                                       "MGBS_WAIT_FOR_CGUA" };

static char MGBRFsmState[][64] = { "MGBR_IDLE",
                                       "MGBR_WAIT_FOR_BLO_RESP",
                                       "MGBR_WAIT_FOR_UBL_RESP" };

static char HLBFsmState[][64] = { "HLB_IDLE", "HLB_LBLOCKED" };

static char HRBFsmState[][64] = { "HRB_IDLE", "HRB_RBLOCKED" };


static char HGBSFsmState[][64] = { "HGBS_IDLE",
                                       "HGBS_WAIT_FOR_CGBA",
                                       "HGBS_WAIT_FOR_CGUA" };

static char HGBRFsmState[][64] = { "HGBR_IDLE",
                                       "HGBR_WAIT_FOR_BLO_RESP",
                                       "HGBR_WAIT_FOR_UBL_RESP" };

static char CRSFsmState[][64] = { "CRS_IDLE",
                                       "CRS_WAIT_FOR_RELEASE" };

static char CRRFsmState[][64] = { "CRR_IDLE",
                                       "CRR_WAIT_FOR_RESPONSE" };

static char CGRSFsmState[][64] = { "CGRS_IDLE",
                                       "CGRS_WAIT_FOR_GRA" };

static char CGRRFsmState[][64] = { "CGRR_IDLE",
                                       "CGRR_WAIT_FOR_GROUP_RESET_COMPLETE" };



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Print the cic info
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
PrintCICRecInfo(ITS_USHORT opc, ITS_USHORT dpc, ITS_USHORT sio, ITS_USHORT cic)
{
    int ret = 0;
    ISUP_PCIC pcic;
    ISUP_CIC_INFO *cic_rec = NULL;

    /* Convert cic, opc, dpc to pcic */
    ISUP_PCICFromParts( &pcic, opc, dpc, sio, cic );

    /* Get cic_rec using the pcic as key */
    cic_rec = ISUP_FindPcic( pcic, ITS_TRUE);
    if (cic_rec == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    printf("\n======================================================================\n",cic);
    printf("CIC States for cic %d:\n",cic);
    printf("----------------------\n");
    printf("vcic = 0x%x (internal to stack)\n", cic_rec->vcic);
    printf("\ncic number = %d\n", cic);

    switch(cic_rec->cic_state & 0x0cU) /* check bits DC */
    {
        case 0x00: /* DC is 00 */
            /* Now check for BA */
            switch(cic_rec->cic_state & 0x03)
            {
                case 0x00:
                    printf("cic Maintenance blocking state: TRANSIENT\n");
                    break;

                case 0x11:
                    printf("cic Maintenance blocking state: UNEQUIPPED\n");
                    break;

                default:
                    printf("Spare!\n");
                    break;
            }
        goto printstates;
    }

    /* Bits DC not equal to 00 */
    switch(cic_rec->cic_state & 0x03U) /* Bits BA */
    {
        case 0x00:
            printf("cic Maintenance blocking state: UNBLOCKED (ACTIVE)\n");
            break;

        case 0x01:
            printf("cic Maintenance blocking state: LOCALLY BLOCKED\n");
            break;

        case 0x02:
            printf("cic Maintenance blocking state: REMOTELY BLOCKED\n");
            break;

        case 0x03:
            printf("cic Maintenance blocking state: LOCALLY & REMOTELY BLOCKED\n");
            break;

        default:
            printf("cic Maintenance state: INVALID STATE!\n");
            break;
    }

    switch(cic_rec->cic_state & 0x0cU) /* Bits DC */
    {
        case 0x04:
            printf("cic Call processing state: CIRCUIT INCOMING BUSY\n");
            break;

        case 0x08:
            printf("cic Call processing state: CIRCUIT OUTGOING BUSY\n");
            break;

        case 0x0c:
            printf("cic Call processing state: IDLE\n");
            break;

        default:
            printf("cic Call processing state: INVALID STATE!\n");
            break;
    }

    switch(cic_rec->cic_state & 0x30U)
    {
        case 0x00:
            printf("cic Hardware blocking state: UNBLOCKED\n");
            break;

        case 0x10:
            printf("cic Hardware blocking state: LOCALLY BLOCKED\n");
            break;

        case 0x20:
            printf("cic Hardware blocking state: REMOTELY BLOCKED\n");
            break;

        case 0x30:
            printf("cic Hardware blocking state: LOCALLY & REMOTELY BLOCKED\n");
            break;

        default:
            printf("cic Hardware blocking state: INVALID STATE!\n");
            break;
    }



printstates:
    printf("\n");;
    printf("CPC  FSM State: %s\n", CPCFsmState[cic_rec->fsm_state]);
    printf("BLS  FSM State: %s\n", BLSFsmState[cic_rec->bls_state]);
    printf("BLR  FSM State: %s\n", BLRFsmState[cic_rec->blr_state]);
    printf("MGBS FSM State: %s\n", MGBSFsmState[cic_rec->mgbs_state]);
    printf("MGBR FSM State: %s\n", MGBRFsmState[cic_rec->mgbr_state]);
    printf("HLB  FSM State: %s\n", HLBFsmState[cic_rec->hlb_state]);
    printf("HRB  FSM State: %s\n", HRBFsmState[cic_rec->hrb_state]);
    printf("HGBS FSM State: %s\n", HGBSFsmState[cic_rec->hgbs_state]);
    printf("HGBR FSM State: %s\n", HGBRFsmState[cic_rec->hgbr_state]);
    printf("CRS  FSM State: %s\n", CRSFsmState[cic_rec->crs_state]);
    printf("CRR  FSM State: %s\n", CRRFsmState[cic_rec->crr_state]);
    printf("CGRS FSM State: %s\n", CGRSFsmState[cic_rec->cgrs_state]);
    printf("CGRR FSM State: %s\n", CGRRFsmState[cic_rec->cgrr_state]);

    printf("\n======================================================================\n",cic);
    printf("\n");;

    /* release cic_rec */
    ISUP_ReleaseCic(cic_rec, ITS_TRUE);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Print the cic range info
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      For printing cic information, the function calls stack internals, like,
 *      ISUP_FindPcic, ISUP_PCICFromParts, ISUP_ReleaseCic. It is strictly
 *      recommended that the app. maintains its own cic data structure and 
 *      refrains from refering to internal stack data. 
 *
 *  See Also:
 ****************************************************************************/
int
PrintCicRangeInfo(ITS_USHORT opc, ITS_USHORT dpc, ITS_USHORT sio,
              ITS_USHORT startcic, ITS_USHORT endcic)
{
    ITS_INT valid_cics[MAXCIC];
    ITS_INT ret;
    ITS_USHORT i = 0;

    ITS_OCTET cicstate;
    ITS_USHORT vcic;
    ITS_BOOLEAN valFlag=ITS_FALSE;

    ISUP_PCIC pcic;
    ISUP_CIC_INFO *cic_rec = NULL;


    printf("PrintCicRangeInfo(): dpc = %d    opc = %d    sio = %d    "
           "startcic = %d    endcic = %d\n", dpc,opc,sio,startcic,endcic);

    memset((void*)&valid_cics[0], ITS_FALSE, MAXCIC);

    for(i = startcic; i <= endcic; i++)
    {
        /* Convert cic, opc, dpc to pcic */
        ISUP_PCICFromParts( &pcic, opc, dpc, sio, i );

        /* Get cic_rec using the pcic as key */
        cic_rec = ISUP_FindPcic( pcic, ITS_TRUE);
        if (cic_rec != NULL)
        {
            valid_cics[i] = ITS_TRUE;
            ISUP_ReleaseCic(cic_rec, ITS_TRUE);
        }

        /* reset vcic */
        vcic = -1;
    }

   
    for(i = startcic; i <= endcic; i++ )
    {
        if( valid_cics[i] == ITS_TRUE )
        {
            ret = PrintCICRecInfo(opc, dpc, sio, i);
            if( ret != ITS_SUCCESS )
            {
                printf("**Problem Encountered in printing info for cic %d", i);
            }
            printf("\n");
        }
    }
    printf("\n");

    printf("\nValid cics in the given range %d to %d are:\n", startcic, endcic);
    for( i = startcic; i <= endcic; i++ )
    {
        if( valid_cics[i] == ITS_TRUE )
        {
            printf("%d, ", i);
            valFlag = ITS_TRUE;
        }
    }
    if(valFlag == ITS_FALSE)
    {
        printf("No valid cic found in the specified range: %d to %d\n", startcic, endcic);
    }
    printf("\n");

    return ITS_SUCCESS;
}


/********************************************************************/
#elif defined(ANSI)
/********************************************************************/

#define MAX_DESC_STR 128

static char CPCFsmState[][MAX_DESC_STR] =
{
    " IDLE                  (CPC  Idle)",

    " WAIT_INCOMING_ACM     (CPC  Outgoing: Wait for Address Complete)",
    " WAIT_INCOMING_ANM     (CPC  Outgoing: Wait for Answer)",
    " RCVD_INCOMING_ANM     (CPC  Outgoing: OGC Answered)",
    " WAIT_INCOMING_RLC     (CPC  Outgoing: Wait for RLC: i.e. REL sent to Nwk)",
    " WAIT_INCOMING_RES     (CPC  Outgoing: OGC Suspended: SUS rcvd form Nwk)",

    " WAIT_OUTGOING_ACM     (CPC  Incoming: Wait for OGC Complete)",
    " WAIT_OUTGOING_ANM     (CPC  Incoming: Wait for Answer)",
    " SENT_OUTGOING_ANM     (CPC  Incoming: ICC Answered)",
    " WAIT_OUTGOING_RLC     (CPC  Incoming: Wait for RLC: i.e. REL rcvd from Nwk)",
    " WAIT_OUTGOING_RES     (CPC  Incoming: ICC Suspended: SUS sent to Nwk)",
 
    " WAIT_OUTGOING_REL     (Timeout/error, waiting to send REL to Nwk)",
    " WAIT_OUTGOING_RSC     (RSC sent to Nwk, waiting for RLC)",
    " WAIT_OUTGOING_GRA     (GRS rcvd from Nwk, waiting to send GRA to Nwk)",
    " WAIT_CONTINUITY_REPORT",
    " WAIT_INCOMING_COT",
    " WAIT_COT_REPORTS_AND_CRA",
    " WAIT_COT_REPORTS_HAVE_CRA",
    " WAIT_INCOMING_CRA",
    " WAIT_OUTGOING_IAM",
    " WAIT_INCOMING_IAM",
    " WAIT_INCOMING_COT_AND_IAM"
};

static char BLSFsmState[][MAX_DESC_STR] =
{
    "BLS_IDLE              (BLS  Outgoing: Idle)",
    "BLS_WAIT_FOR_BLA      (BLS  Outgoing: Wait for BLA from Nwk)",
    "BLS_WAIT_FOR_UBA      (BLS  Outgoing: Wait for UBA from Nwk)"
};

static char BLRFsmState[][MAX_DESC_STR] =
{
    "BLR_IDLE              (BLR  Incoming: Idle)"
};

static char MGBSFsmState[][MAX_DESC_STR] =
{
    "MGBS_IDLE             (MGBS Outgoing: Idle)",
    "MGBS_WAIT_FOR_CGBA    (MGBS Outgoing: Wait for CGBA from Nwk)",
    "MGBS_WAIT_FOR_CGUA    (MGBS Outgoing: Wiat for CGUA from Nwk)"
};

static char MGBRFsmState[][MAX_DESC_STR] =
{
    "MGBR_IDLE             (MGBR Incoming: Idle)"
};

static char CRSFsmState[][MAX_DESC_STR] =
{
    "CRS_IDLE              (CRS  Outgoing: Idle)",
    "CRS_WAIT_FOR_RELEASE  (CRS  Outgoing: Wait for RLC from Nwk)"
};

static char CRRFsmState[][MAX_DESC_STR] =
{
    "CRR_IDLE              (CRR  Incoming: Idle)"
};

static char CGRSFsmState[][MAX_DESC_STR] =
{
    "CGRS_IDLE             (CGRS Outgoing: Idle)",
    "CGRS_WAIT_FOR_GRA     (CGRS Outgoing: Wiat for GRA from Nwk)"
};

static char CGRRFsmState[][MAX_DESC_STR] =
{
    "CGRR_IDLE             (CGRR Incoming: Idle)"
};

static char CVTSFsmState[][MAX_DESC_STR] =
{
    "CVTS_IDLE             (CVT  Outgoing: Idle)",
    "CVTS_WAIT_FOR_CVR     (CVT  Outgoing: Wait for CVR from Nwk)"
};

static char CVTRFsmState[][MAX_DESC_STR] =
{
    "CVTR_IDLE             (CVT  Incoming: Idle)",
    "CVTR_WAIT_FOR_CVR     (CVT  Incoming: CVT rcvd from Nwk, waiting to send CVR)"
};

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Print the cic info
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      For printing cic information, the function calls stack internals, like,
 *      ISUP_FindPcic, ISUP_PCICFromParts, ISUP_ReleaseCic. It is strictly
 *      recommended that the app. maintains its own cic data structure and 
 *      refrains from refering to internal stack data. 
 *
 *  See Also:
 ****************************************************************************/
int
PrintCICRecInfo(ITS_UINT opc, ITS_UINT dpc, ITS_UINT sio, ITS_USHORT cic)
{
    ISUP_PCIC pcic;
    ISUP_CIC_INFO *cic_rec = NULL;
    char *cco , *cro ,*dco;
    char *cci, *cri;

    /* Convert cic, opc, dpc to pcic */
    ISUP_PCICFromParts( &pcic, opc, dpc, sio, cic );

    /* Get cic_rec using the pcic as key */
    cic_rec = ISUP_FindPcic( pcic, ITS_TRUE);
    if (cic_rec == NULL)
    {
        printf("Cic record not found for given cic %d.\n", cic);
        return ITS_ENOTCONFIG;
    }

    printf("\n======================================================================\n");
    printf("Cic States for cic %d:\n",cic);
    printf("----------------------\n");
    printf("Virtual cic (vcic) = 0x%x (internal to stack)\n", cic_rec->vcic);
    printf("Original cic number = %d\n", cic);
    printf("CIC Rule String =  %s\n", ISUP_CkgpCtrlToString(cic_rec->cic_rule));
    printf("** (cpc, mpc) : ");
    switch(cic_rec->cic_state) 
    {
       /* H G F E  D C B A */
       /* 0 0 0 0  0 0 0 0 */
        case 0x00: /* Transient */
            printf("Circuit State: 0x%x : TRANSIENT\n", cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 0 0 1 */
        case 0x01: /* spare (no interpretation) */
            printf("Circuit State: 0x%x : Spare "
                   "(no Interpretation)\n", cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 0 1 0 */
        case 0x02: /* spare (no interpretation) */
            printf("Circuit State: 0x%x : Spare "
                   "(no Interpretation)\n", cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 0 1 1 */
        case 0x03: /* Unequipped */
            printf("Circuit State: 0x%x : UNEQUIPPED\n", cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 1 0 0 */
        case 0x04: /* Incoming Circuit Busy, Active */
            printf("Circuit State: 0x%x : INCOMING CIRCUIT BUSY, ACTIVE\n",
                    cic_rec->cic_state);
            break;


       /* H G F E  D C B A */
       /* 0 0 0 0  0 1 0 1 */
        case 0x05: /* Incoming Circuit Busy, Locally Blocked */
            printf("Circuit State: 0x%x : INCOMING CIRCUIT BUSY, LOCALLY BLOCKED\n",
                   cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 1 1 0 */
        case 0x06: /* Incoming Circuit Busy, Remotely Blocked */
            printf("Circuit State: 0x%x : INCOMING CIRCUIT BUSY, REMOTELY BLOCKED\n",
                   cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  0 1 1 1 */
        case 0x07: /* Incoming Circuit Busy, Locally & Remotely Blocked */
            printf("Circuit State: 0x%x : INCOMING CIRCUIT BUSY, LOCALLY & REMOTELY BLOCKED\n",
                   cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 0 0 0 */
        case 0x08: /* Outgoing Circuit Busy, Active */
            printf("Circuit State: 0x%x : OUTGOING CIRCUIT BUSY, ACTIVE\n",
                   cic_rec->cic_state);
            break;


       /* H G F E  D C B A */
       /* 0 0 0 0  1 0 0 1 */
        case 0x09: /* Outgoing Circuit Busy, Locally Blocked */
            printf("Circuit State: 0x%x : OUTGOING CIRCUIT BUSY, LOCALLY BLOCKED\n",
                   cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 0 1 0 */
        case 0x0A: /* Outgoing Circuit Busy, Remotely Blocked */
            printf("Circuit State: 0x%x : OUTGOING CIRCUIT BUSY, REMOTELY BLOCKED\n",
                   cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 0 1 1 */
        case 0x0B: /* Outgoing Circuit Busy, Locally & Remotely Blocked */
            printf("Circuit State: 0x%x : OUTGOING CIRCUIT BUSY, LOCALLY & REMOTELY BLOCKED\n",
                   cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 1 0 0 */
        case 0x0C: /* Idle, local UNblok, remote UNblock*/
            printf("Circuit State: 0x%x : IDLE, LOCAL UNBLOCK, REMOTE UNBLOCK\n", cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 1 0 1 */
        case 0x0D: /* Idle, Locally Blocked */
            printf("Circuit State: 0x%x : IDLE, LOCALLY BLOCKED\n",
                   cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 1 1 0 */
        case 0x0E: /* Idle, Remotely Blocked */
            printf("Circuit State: 0x%x : IDLE, REMOTELY BLOCKED\n",
                   cic_rec->cic_state);
            break;

       /* H G F E  D C B A */
       /* 0 0 0 0  1 1 1 1 */
        case 0x0F: /* Idle, Locally & Remotely Blocked */
            printf("Circuit State: 0x%x : IDLE, LOCALLY & REMOTELY BLOCKED\n",
                   cic_rec->cic_state);
            break;

        default:
            printf("Circuit State: 0x%x : Spare "
                   "(no Interpretation)\n", cic_rec->cic_state);
            break;
    }

    printf("\nCall Processing Control Fsm State:\n");
    printf("CPC  State: %s\n", CPCFsmState[cic_rec->fsm_state]);

    printf("\nMaintenance Processing Control Fsm States:\n");
    printf("BLS  State: %s\n", BLSFsmState[cic_rec->bls_state]);
    printf("BLR  State: %s\n", BLRFsmState[cic_rec->blr_state]);
    printf("MGBS State: %s\n", MGBSFsmState[cic_rec->mgbs_state]);
    printf("MGBR State: %s\n", MGBRFsmState[cic_rec->mgbr_state]);
    printf("CRS  State: %s\n", CRSFsmState[cic_rec->crs_state]);
    printf("CRR  State: %s\n", CRRFsmState[cic_rec->crr_state]);
    printf("CGRS State: %s\n", CGRSFsmState[cic_rec->cgrs_state]);
    printf("CGRR State: %s\n", CGRRFsmState[cic_rec->cgrr_state]);
    printf("CVTS State: %s\n", CVTSFsmState[cic_rec->cvts_state]);
    printf("CVTR State: %s\n", CVTRFsmState[cic_rec->cvtr_state]);

    switch(cic_rec->cco_state)
    {
    case CCO_IDLE :
        cco = "CCO_IDLE";
        break;
    case CCO_WAIT_COT_REPORT :
        cco = "CCO_WAIT_COT_REPORT";
        break;
    }
    printf("CCO State:  %s\n",cco);

    switch(cic_rec->cci_state)
    {
    case CCI_IDLE :
        cci = "CCI_IDLE";
        break;
    case CCI_WAIT_FOR_COT :
        cci = "CCI_WAIT_FOR_COT";
        break;
    }
    printf("CCI State:  %s\n",cci);

    switch(cic_rec->cro_state)
    {
    case CRO_IDLE :
        cro = "CRO_IDLE";
        break;
    case CRO_WAIT_TIMER_EXPIRY :
        cro = "CRO_WAIT_TIMER_EXPIRY";
        break;
    case CRO_WAIT_FOR_COT :
        cro = "CRO_WAIT_FOR_COT";
        break;
    case CRO_WAIT_FOR_RLC :
        cro = "CRO_WAIT_FOR_RLC";
        break;
    }
    printf("CRO State:  %s\n",cro);

    switch(cic_rec->cri_state)
    {
    case CRI_IDLE :
        cri = "CRI_IDLE";
        break;
    case CRI_WAIT_FOR_CCR :
        cri = "CRI_WAIT_FOR_CCR";
        break;
    case CRI_WAIT_FOR_REL :
        cri = "CRI_WAIT_FOR_REL";
        break;
    case CRI_WAIT_FOR_LPA :
        cri = "CRI_WAIT_FOR_LPA";
        break;
    }
    printf("CRI State:  %s\n",cri);

    switch(cic_rec->dco_state)
    {
    case DCO_IDLE :
        dco = "DCO_IDLE";
        break;
    case DCO_WAIT_FOR_LPA :
        dco = "DCO_WAIT_FOR_LPA";
        break;
    }
    printf("DCO State:  %s\n",dco);
    printf("\n======================================================================\n");

    /* release cic_rec */
    ISUP_ReleaseCic(cic_rec, ITS_TRUE);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Print the cic info over a given range
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
PrintCicRangeInfo(ITS_UINT opc, ITS_UINT dpc, ITS_USHORT sio,
              ITS_USHORT startcic, ITS_USHORT endcic)
{
    ITS_INT valid_cics[MAXCIC];
    ITS_INT ret;
    ITS_USHORT i = 0;

    ITS_USHORT vcic;
    ITS_BOOLEAN valFlag=ITS_FALSE;

    ISUP_PCIC pcic;
    ISUP_CIC_INFO *cic_rec = NULL;


    printf("PrintCicRangeInfo(): dpc = %d    opc = %d    sio = %d    "
           "startcic = %d    endcic = %d\n", dpc,opc,sio,startcic,endcic);

    memset((void*)&valid_cics[0], ITS_FALSE, MAXCIC);

    for(i = startcic; i <= endcic; i++)
    {


        /* Convert cic, opc, dpc to pcic */
        ISUP_PCICFromParts( &pcic, opc, dpc, sio, i );

        /* Get cic_rec using the pcic as key */
        cic_rec = ISUP_FindPcic( pcic, ITS_TRUE);
        if (cic_rec != NULL)
        {
            valid_cics[i] = ITS_TRUE;
            ISUP_ReleaseCic(cic_rec, ITS_TRUE);
        }

        /* reset vcic */
        vcic = -1;
    }

   
    for(i = startcic; i <= endcic; i++ )
    {
        if( valid_cics[i] == ITS_TRUE )
        {
            ret = PrintCICRecInfo(opc, dpc, sio, i);
            if( ret != ITS_SUCCESS )
            {
                printf("**Problem Encountered in printing info for cic %d", i);
            }
            printf("\n");
        }
    }

    printf("\nValid cics in the given range %d to %d are:\n", startcic, endcic);
    for( i = startcic; i <= endcic; i++ )
    {
        if( valid_cics[i] == ITS_TRUE )
        {
            printf("%d, ", i);
            valFlag = ITS_TRUE;
        }
    }
    if(valFlag == ITS_FALSE)
    {
        printf("No valid cic found in the specified range: %d to %d\n", startcic, endcic);
    }
    printf("\n");

    return ITS_SUCCESS;
}

/********************************************************************/
#endif /* for ANSI */
/********************************************************************/
