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
 *                  
 * CONTRACT: INTERNAL
 *      
 *  ID: $Id: sua.c,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $
 *
 *  LOG: $Log: not supported by cvs2svn $
 *  LOG: Revision 1.1.1.1  2007/10/04 13:23:53  bsccs2
 *  LOG: init tree
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/08/03 06:48:51  cvsadmin
 *  LOG: BscCs2
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/03/08 15:13:22  cvsadmin
 *  LOG: BSC project
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:52:24  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:50:22  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.2  2002/05/28 19:04:47  ngoel
 *  LOG: port sua to current
 *  LOG:
 *  LOG: Revision 6.1  2002/02/28 16:14:02  mmiers
 *  LOG: Begin PR7.
 *  LOG:
 *  LOG: Revision 5.5  2002/01/10 21:46:20  mmiers
 *  LOG: Get things building again.
 *  LOG:
 *  LOG: Revision 5.4  2002/01/10 14:37:33  ngoel
 *  LOG: work in progress
 *  LOG:
 *  LOG: Revision 5.3  2002/01/04 18:13:28  ngoel
 *  LOG: upgrading to draft 9 work in progress
 *  LOG:
 *  LOG: Revision 5.2  2001/10/08 20:08:02  mmiers
 *  LOG: Warning removal
 *  LOG:
 *  LOG: Revision 5.1  2001/08/16 20:45:48  mmiers
 *  LOG: Start PR6.
 *  LOG:
 *  LOG: Revision 4.2  2001/07/26 14:48:52  labuser
 *  LOG: commit SUA v5 to current.
 *  LOG:
 *  LOG: Revision 1.14.2.1  2001/06/22 20:23:25  labuser
 *  LOG: SUA draft v5 codec.
 *  LOG:
 *                 
 ****************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <its.h>

#include <sua.h>

#include <its_sockets.h>
#include <its_transports.h>
#include <its_trace.h>
#include <its_app.h>
#include <its_sctp_trans.h>

int _sua_itw_mode = 0;
/*
 *   Connectionless Messages
 */


/*
 **** CLDT ***
 * this message corresponds to the SCCP: UDT, XUDT, LUDT
 */
static ITS_USHORT    cldtMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_PROT_CLASS, 
    SUA_PRM_SRC_ADDR,
    SUA_PRM_DST_ADDR,
    SUA_PRM_SEQ_CTL,
    SUA_PRM_DATA
};

static ITS_USHORT    cldtOArgs[] =
{
    SUA_PRM_HOP_CNT,
    SUA_PRM_IMPORTANCE,
    SUA_PRM_MSG_PRIOR,
    SUA_PRM_COR_ID,
    SUA_PRM_SEGMENTATION
};

SUADLLAPI SUA_MSG_DESC SUA_CLDT_Desc =
{
    cldtMArgs, sizeof(cldtMArgs) / sizeof(ITS_USHORT),
    cldtOArgs, sizeof(cldtOArgs) / sizeof(ITS_USHORT)
};

/*
 *** CLDR ***
 * this message corresponds to the SCCP: ERR, UDTS, LUDTS, XUDTS
 */
static ITS_USHORT    cldrMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_SCCP_CAUSE,
    SUA_PRM_SRC_ADDR,
    SUA_PRM_DST_ADDR,
};

static ITS_USHORT    cldrOArgs[] =
{
    SUA_PRM_HOP_CNT, 
    SUA_PRM_IMPORTANCE,
    SUA_PRM_MSG_PRIOR, 
    SUA_PRM_COR_ID,
    SUA_PRM_SEGMENTATION,
    SUA_PRM_DATA
};

SUADLLAPI SUA_MSG_DESC SUA_CLDR_Desc =
{
    cldrMArgs, sizeof(cldrMArgs) / sizeof(ITS_USHORT),
    cldrOArgs, sizeof(cldrOArgs) / sizeof(ITS_USHORT)
};



/*
 * Connection oriented messages
 */

/*
 *** CODT ***
 * This message corresponds to the SCCP: DT1, DT2, ED
 * The Sequence Number is mandatory when the message maps to DT2
 */
static ITS_USHORT    codtMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_DATA
};

static ITS_USHORT    codtOArgs[] =
{
    SUA_PRM_SEQ_NUM, 
    SUA_PRM_MSG_PRIOR, 
    SUA_PRM_COR_ID
};


SUA_MSG_DESC SUA_CODT_Desc =
{
    codtMArgs, sizeof(codtMArgs) / sizeof(ITS_USHORT),
    codtOArgs, sizeof(codtOArgs) / sizeof(ITS_USHORT)
};

/*
 *** CODA ***
 * This message corresponds to the SCCP: AK, EA
 */
static ITS_USHORT    codaMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_CREDIT
};

static ITS_USHORT    codaOArgs[] =
{
    SUA_PRM_REC_SEQ_NUM,
};


SUADLLAPI SUA_MSG_DESC SUA_CODA_Desc =
{
    codaMArgs, sizeof(codaMArgs) / sizeof(ITS_USHORT),
    codaOArgs, sizeof(codaOArgs) / sizeof(ITS_USHORT)
};

/*
 *** CORE ***
 * This message corresponds to the SCCP: CR
 */
static ITS_USHORT    coreMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_PROT_CLASS, 
    SUA_PRM_SRC_REF_NUM,
    SUA_PRM_DST_ADDR,
    SUA_PRM_SEQ_CTL
    
};

static ITS_USHORT    coreOArgs[] =
{
    SUA_PRM_SEQ_NUM, 
    SUA_PRM_SRC_ADDR,
    SUA_PRM_HOP_CNT, 
    SUA_PRM_IMPORTANCE,
    SUA_PRM_MSG_PRIOR, 
    SUA_PRM_CREDIT,
    SUA_PRM_DATA
};


SUADLLAPI SUA_MSG_DESC SUA_CORE_Desc =
{
    coreMArgs, sizeof(coreMArgs) / sizeof(ITS_USHORT),
    coreOArgs, sizeof(coreOArgs) / sizeof(ITS_USHORT)
};


/*
 *** COAK ***
 * This message corresponds to the SCCP: CC, CREF
 */
static ITS_USHORT    coakMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_PROT_CLASS, 
    SUA_PRM_SRC_REF_NUM,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_SEQ_CTL
};

static ITS_USHORT    coakOArgs[] =
{
    SUA_PRM_CREDIT,
    SUA_PRM_IMPORTANCE,
    SUA_PRM_MSG_PRIOR, 
    SUA_PRM_DST_ADDR,
    SUA_PRM_DATA

};


SUADLLAPI SUA_MSG_DESC SUA_COAK_Desc =
{
    coakMArgs, sizeof(coakMArgs) / sizeof(ITS_USHORT),
    coakOArgs, sizeof(coakOArgs) / sizeof(ITS_USHORT)
};


/*
 *** COREF ***
 * This message corresponds to the SCCP: CC, CREF
 */
static ITS_USHORT    corefMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_SCCP_CAUSE
};

static ITS_USHORT    corefOArgs[] =
{
    SUA_PRM_SRC_ADDR,
    SUA_PRM_DST_ADDR,
    SUA_PRM_IMPORTANCE,
    SUA_PRM_DATA

};


SUADLLAPI SUA_MSG_DESC SUA_COREF_Desc =
{
    corefMArgs, sizeof(corefMArgs) / sizeof(ITS_USHORT),
    corefOArgs, sizeof(corefOArgs) / sizeof(ITS_USHORT)
};



/*
 *** RESRE ***
 * This message corresponds to the SCCP: RSR
 */
static ITS_USHORT    resreMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_SRC_REF_NUM,
    SUA_PRM_SCCP_CAUSE
};

SUADLLAPI SUA_MSG_DESC SUA_RESRE_Desc =
{
    resreMArgs, sizeof(resreMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};

/*
 *** RESCO ***
 * This message corresponds to the SCCP: RSC
 */
static ITS_USHORT    rescoMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_SRC_REF_NUM,
};

SUADLLAPI SUA_MSG_DESC SUA_RESCO_Desc =
{
    rescoMArgs, sizeof(rescoMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};



/*
 *** RELRE ***
 * This message corresponds to the SCCP: RLSD
 */
static ITS_USHORT    relreMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_SRC_REF_NUM,
    SUA_PRM_SCCP_CAUSE
};

static ITS_USHORT    relreOArgs[] =
{
    SUA_PRM_IMPORTANCE,
    SUA_PRM_DATA
};


SUADLLAPI SUA_MSG_DESC SUA_RELRE_Desc =
{
    relreMArgs, sizeof(relreMArgs) / sizeof(ITS_USHORT),
    relreOArgs, sizeof(relreOArgs) / sizeof(ITS_USHORT)
};


/*
 *** RELCO ***
 * This message corresponds to the SCCP: RLC
 */
static ITS_USHORT    relcoMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_SRC_REF_NUM
};

static ITS_USHORT    relcoOArgs[] =
{
    SUA_PRM_IMPORTANCE
};

SUADLLAPI SUA_MSG_DESC SUA_RELCO_Desc =
{
    relcoMArgs, sizeof(relcoMArgs) / sizeof(ITS_USHORT),
    relcoOArgs, sizeof(relcoOArgs) / sizeof(ITS_USHORT)
};


/*
 *** COERR ***
 * This message corresponds to the SCCP: Protocol Data Unit ERR
 */
static ITS_USHORT    coerrMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_SCCP_CAUSE
};


SUADLLAPI SUA_MSG_DESC SUA_COERR_Desc =
{
    coerrMArgs, sizeof(coerrMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};

/*
 *** COIT ***
 */
static ITS_USHORT    coitMArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_PROT_CLASS, 
    SUA_PRM_SRC_REF_NUM,
    SUA_PRM_DST_REF_NUM,
    SUA_PRM_SEQ_NUM,
    SUA_PRM_CREDIT
};


SUADLLAPI SUA_MSG_DESC SUA_COIT_Desc =
{
    coitMArgs, sizeof(coitMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};



/*
 * SS7 signaling network management messages
 */

/*
 *** DUNA ***
 * This message corresponds to the SCCP: SSP
 */
static ITS_USHORT    dunaMArgs[] =
{
    SUA_PRM_AFFECTED_PC
};

static ITS_USHORT    dunaOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_SPRM_SSN,
    SUA_PRM_SMI, 
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_DUNA_Desc =
{
    dunaMArgs, sizeof(dunaMArgs) / sizeof(ITS_USHORT),
    dunaOArgs, sizeof(dunaOArgs) / sizeof(ITS_USHORT)
};


/*
 *** DAVA ***
 * This message corresponds to the SCCP: SSA
 */
static ITS_USHORT    davaMArgs[] =
{
    SUA_PRM_AFFECTED_PC
};

static ITS_USHORT    davaOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_SPRM_SSN,
    SUA_PRM_SMI, 
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_DAVA_Desc =
{
    davaMArgs, sizeof(davaMArgs) / sizeof(ITS_USHORT),
    davaOArgs, sizeof(davaOArgs) / sizeof(ITS_USHORT)
};


/*
 *** DAUD ***
 * This message corresponds to the SCCP: SST
 */
static ITS_USHORT    daudMArgs[] =
{
    SUA_PRM_AFFECTED_PC
};

static ITS_USHORT    daudOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_SPRM_SSN,
    SUA_PRM_SMI, 
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_DAUD_Desc =
{
    daudMArgs, sizeof(daudMArgs) / sizeof(ITS_USHORT),
    daudOArgs, sizeof(daudOArgs) / sizeof(ITS_USHORT)
};



/*
 *** SCON ***
 */

static ITS_USHORT    sconMArgs[] =
{
    SUA_PRM_CONG_LEVEL,
    SUA_PRM_AFFECTED_PC
};

static ITS_USHORT    sconOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_SPRM_SSN,
    SUA_PRM_SMI, 
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_SCON_Desc =
{
    sconMArgs, sizeof(sconMArgs) / sizeof(ITS_USHORT),
    sconOArgs, sizeof(sconOArgs) / sizeof(ITS_USHORT)
};






/*
 *** DUPU ***
 * This message corresponds to the MTP3: UPU
 */
static ITS_USHORT    dupuMArgs[] =
{
    SUA_PRM_AFFECTED_PC,
    SUA_PRM_CAUSE_USER
};

static ITS_USHORT    dupuOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_SPRM_SSN,
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_DUPU_Desc =
{
    dupuMArgs, sizeof(dupuMArgs) / sizeof(ITS_USHORT),
    dupuOArgs, sizeof(dupuOArgs) / sizeof(ITS_USHORT)
};


/*
 * application server process maintenance messages
 */

/*** ASPUP ***/
 


static ITS_USHORT    aspupOArgs[] =
{
    SUA_PRM_ASP_CAPAB,
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_ASPUP_Desc =
{
    NULL, 0,
    aspupOArgs, sizeof(aspupOArgs) / sizeof(ITS_USHORT)
};


/*** UPACK ***/

static ITS_USHORT    upackOArgs[] =
{
    SUA_PRM_ASP_CAPAB,
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_UPACK_Desc =
{
    NULL, 0,
    upackOArgs, sizeof(upackOArgs) / sizeof(ITS_USHORT)
};


/*** ASPDN ***/
 
static ITS_USHORT    aspdnMArgs[] =
{
};

static ITS_USHORT    aspdnOArgs[] =
{
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_ASPDN_Desc =
{
    aspdnMArgs, sizeof(aspdnMArgs) / sizeof(ITS_USHORT),
    aspdnOArgs, sizeof(aspdnOArgs) / sizeof(ITS_USHORT)
};


/*** DNACK ***/
 
static ITS_USHORT    dnackMArgs[] =
{
};

static ITS_USHORT    dnackOArgs[] =
{
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_DNACK_Desc =
{
    dnackMArgs, sizeof(dnackMArgs) / sizeof(ITS_USHORT),
    dnackOArgs, sizeof(dnackOArgs) / sizeof(ITS_USHORT)
};


/*
 * HEARTBEAT
 */

static ITS_USHORT    beatOArgs[] =
{
    SUA_PRM_HEARTBEAT_DATA
};

SUADLLAPI SUA_MSG_DESC SUA_HEARTBEAT_Desc =
{
    NULL, 0,
    beatOArgs, sizeof(beatOArgs) / sizeof(ITS_USHORT)
};


static ITS_USHORT    beatackOArgs[] =
{
    SUA_PRM_HEARTBEAT_DATA
};

SUADLLAPI SUA_MSG_DESC SUA_HEARTBEAT_ACK_Desc =
{
    NULL, 0,
    beatackOArgs, sizeof(beatackOArgs) / sizeof(ITS_USHORT)
};

/*
 *** ASPAC ***
 * This message corresponds to the SCCP: SSA
 */
 
static ITS_USHORT    aspacMArgs[] =
{
    SUA_PRM_TRAFFIC_MODE
};

static ITS_USHORT    aspacOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_ASPAC_Desc =
{
    aspacMArgs, sizeof(aspacMArgs) / sizeof(ITS_USHORT),
    aspacOArgs, sizeof(aspacOArgs) / sizeof(ITS_USHORT)
};


/*
 *** ASPAC_ACK ***
 * This message corresponds to the SCCP: SSA
 */
 
static ITS_USHORT    aspac_ackMArgs[] =
{
    SUA_PRM_TRAFFIC_MODE
};

static ITS_USHORT    aspac_ackOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_ASPAC_ACK_Desc =
{
    aspac_ackMArgs, sizeof(aspac_ackMArgs) / sizeof(ITS_USHORT),
    aspac_ackOArgs, sizeof(aspac_ackOArgs) / sizeof(ITS_USHORT)
};



/*
 *** ASPIA ***
 * This message corresponds to the SCCP: SOR
 */
 

static ITS_USHORT    aspiaOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_ASPIA_Desc =
{
    NULL, 0,
    aspiaOArgs, sizeof(aspiaOArgs) / sizeof(ITS_USHORT)
};


/*
 *** ASPIA_ACK ***
 * This message corresponds to the SCCP: SOR
 */
 

static ITS_USHORT    aspia_ackOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_ASPIA_ACK_Desc =
{
    NULL, 0,
    aspia_ackOArgs, sizeof(aspia_ackOArgs) / sizeof(ITS_USHORT)
};


/*** NTFY ***/

static ITS_USHORT    ntfyMArgs[] =
{
    SUA_PRM_STATUS_TYPE_ID
};

static ITS_USHORT    ntfyOArgs[] =
{
    SUA_PRM_ROUT_CTX,
    SUA_PRM_INFO_STR
};


SUADLLAPI SUA_MSG_DESC SUA_NTFY_Desc =
{
    ntfyMArgs, sizeof(ntfyMArgs) / sizeof(ITS_USHORT),
    ntfyOArgs, sizeof(ntfyOArgs) / sizeof(ITS_USHORT)
};


/*
 * Management messages
 */

/*** ERR ***/

static ITS_USHORT    errMArgs[] =
{
    SUA_PRM_ERROR_CODE
};

static ITS_USHORT    errOArgs[] =
{
    SUA_PRM_DIAG_INFO
};


SUADLLAPI SUA_MSG_DESC SUA_ERR_Desc =
{
    errMArgs, sizeof(errMArgs) / sizeof(ITS_USHORT),
    errOArgs, sizeof(errOArgs) / sizeof(ITS_USHORT)
};

/*
 * REGREQ
 */

static ITS_USHORT    regreqMArgs[] =
{
    SUA_PRM_RKEY
};

SUA_MSG_DESC SUA_REGREQ_Desc =
{
    regreqMArgs, sizeof(regreqMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};

/*
 * REGRSP
 */

static ITS_USHORT    regrspMArgs[] =
{
    SUA_PRM_REG_RES
};

SUA_MSG_DESC SUA_REGRSP_Desc =
{
    regrspMArgs, sizeof(regrspMArgs) / sizeof(ITS_USHORT),
    NULL, 0
};





/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      Small helper function to calculate the padding length.
 *     
 *  Input Parameters:
 *      size - size of the parameter to be padded
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      number of padding bytes.
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
int
SUA_GetPadding(int size)
{
    if ((size % 4) == 0)
    {
        return 0;
    }
    else
    {
        return 4 - (size % 4);
    }
}




SUADLLAPI int
SUA_EncodeAddress(SUA_ADDRS *suaAddr, ITS_OCTET routIndic, ITS_OCTET addrIndic,
                  ITS_UINT pc, ITS_OCTET ssn, SUA_GT *gt, int gtLen)
{
    int ret = ITS_SUCCESS;
    ITS_SUA_IE ies[3]; /* for PC, SSN and GT */
    int ieCount = 0, offset = 0, padding = 0, i;
    int len = 0;

    suaAddr->routIndic[0] = 0x00;
    suaAddr->routIndic[1] = routIndic;
    suaAddr->addrIndic[0] = 0x00;
    suaAddr->addrIndic[1] = addrIndic;

    suaAddr->len = 0;

    if (addrIndic & SUA_CPA_HAS_PC_MASK)
    {
        assert(pc != 0);

        ies[ieCount].param_id = SUA_SPRM_PC;
        ies[ieCount].param_length = sizeof(SUA_PC);
        memset(&ies[ieCount].param_data.pc, 0, 3);
        SUA_PC_SET_VALUE(ies[ieCount].param_data.pc, pc);

        ieCount++;
    }

    if (addrIndic & SUA_CPA_HAS_SSN_MASK)
    {
        assert(ssn != 0);

        ies[ieCount].param_id = SUA_SPRM_SSN;
        ies[ieCount].param_length = sizeof(SUA_SSN);
        ies[ieCount].param_data.ssn.ssn = ssn;

        ies[ieCount].param_data.ssn.ssn = 
                                 SOCK_HToNL(ies[ieCount].param_data.ssn.ssn);
        ieCount++;
    }

    if (addrIndic & SUA_CPA_HAS_GT_MASK)
    {
        assert(gt != NULL && gtLen != 0);

        ies[ieCount].param_id = SUA_SPRM_GT;
        ies[ieCount].param_length = 4 + gtLen;
        memcpy(&ies[ieCount].param_data.gt, gt, sizeof(SUA_GT));

        ieCount++;
    }


    for (i = 0; i < ieCount; i++)
    {
        /* cpy param id */
        ies[i].param_id = SOCK_HToNS(ies[i].param_id);

        memcpy(&suaAddr->addrData[offset], &ies[i].param_id, 
               sizeof(ITS_USHORT));

        offset += 2;

        /* cpy param len */
        len = ies[i].param_length;
        padding = SUA_GetPadding(len);
        ies[i].param_length = SOCK_HToNS(ies[i].param_length + 4);

        memcpy(&suaAddr->addrData[offset], &ies[i].param_length, 
               sizeof(ITS_USHORT));

        offset += 2;

        memset(&suaAddr->addrData[offset], 0, (len + padding)); 
        memcpy(&suaAddr->addrData[offset], &ies[i].param_data, len);
  
        offset += (len + padding);
    }

    suaAddr->len += offset; /* addr len includes parameters len and padding 
                               plus addr and routing indicators (4 bytes)*/

    return (ret);    

}
                  

SUADLLAPI int
SUA_EncodeAddressRange(SUA_ADDRS_RANGE *addrRange, ITS_OCTET *totLen, SUA_ADDRS *addr1, 
                       SUA_ADDRS *addr2, ITS_USHORT addrType)
{
    int addrLen; 
    int offset = 0;
    int padding = 0;
    ITS_USHORT len;


    addrType= SOCK_HToNS(addrType);

    memcpy(&addrRange->data[offset], &addrType,
           sizeof(ITS_USHORT));
    offset += 2;

    /* cpy param len */
    len = addr1->len + 4; 

    padding = SUA_GetPadding(len);
    len = SOCK_HToNS(len + 8);

    memcpy(&addrRange->data[offset], &len,
           sizeof(ITS_USHORT));

    offset += 2;

    addrLen =  addr1->len + 4;

    padding = SUA_GetPadding(addrLen);

    memset(&addrRange->data[offset], 0, (addrLen + padding));
            
    memcpy(&addrRange->data[offset], 
           addr1->routIndic, 2);
    
    memcpy(&addrRange->data[offset + 2], 
           addr1->addrIndic, 2);

    memcpy(&addrRange->data[offset + 4], 
           addr1->addrData, 
           addr1->len);

    offset += (addrLen + padding);           

    memcpy(&addrRange->data[offset], &addrType,
           sizeof(ITS_USHORT));
    offset += 2;

    /* cpy param len */
    len = addr2->len + 4; 

    padding = SUA_GetPadding(len);
    len = SOCK_HToNS(len + 4);

    memcpy(&addrRange->data[offset], &len,
           sizeof(ITS_USHORT));

    offset += 2;

    addrLen =  addr2->len + 4;

    padding = SUA_GetPadding(addrLen);

    memset(&addrRange->data[offset], 0, (addrLen + padding));
            
    memcpy(&addrRange->data[offset], 
           addr2->routIndic, 2);
    
    memcpy(&addrRange->data[offset + 2], 
           addr2->addrIndic, 2);

    memcpy(&addrRange->data[offset + 4], 
           addr2->addrData, 
           addr2->len);

    offset += (addrLen + padding);           

   *totLen = offset;

   return ITS_SUCCESS;
}

SUADLLAPI int
SUA_DecodeAddress(ITS_OCTET *suaAddr, int len, ITS_OCTET *routIndic, 
                  ITS_OCTET *addrIndic, ITS_UINT *pc, ITS_OCTET *ssn, 
                  SUA_GT *gt, int *gtLen)
{
    int ret = ITS_SUCCESS;
    int  offset = 0;
    ITS_USHORT paramId, paramLen;

    *routIndic = suaAddr[1];
    *addrIndic = suaAddr[3];

    offset = 4;

    while (offset < (len - 4))
    {
        paramId = suaAddr[offset] << 8 | 
                  suaAddr[offset + 1];
         
        offset += 2;

        paramLen = (suaAddr[offset] << 8 | 
                    suaAddr[offset + 1]) - 4;

        offset += 2;

        if (paramId == SUA_SPRM_PC)
        {
            SUA_PC suaPC;

            memcpy(&suaPC, &suaAddr[offset], paramLen);

            *pc = SUA_PC_GET_VALUE(suaPC);
        }
        else if (paramId == SUA_SPRM_SSN)
        {
            int localSSN = 0;

            memcpy(&localSSN, &suaAddr[offset], paramLen);

            *ssn = (ITS_OCTET)SOCK_NToHL(localSSN);
        }
        else if (paramId == SUA_SPRM_GT)
        {
            memcpy(gt, &suaAddr[offset], paramLen);

            *gtLen = paramLen;
        }

        offset += paramLen + SUA_GetPadding(paramLen); 

    }
    
    return (ret);
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This is a helper function that prints a SUA IE element.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      IE - pointer to the SUA_IE to be displayed.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
SUADLLAPI void
SUA_PrintSUA_IES(ITS_SUA_IE *IE)
{
    if (IE != NULL)
    {
        int i;

        printf("------------ SUA_IE Begin ------------\n");
        printf("Prarmeter Type: 0x%04x \n", IE->param_id);
        printf("Parameter len : 0x%04x \n", IE->param_length);

        for (i = 0; i < IE->param_length; i++)
        {
            printf("0x%02x ", *((unsigned char *)&(IE->param_data) + i));
        }
        printf("\n------------ SUA_IE End ------------\n");
    }
    else
    {
        printf("IE * is NULL \n");
    }

    return;
}







/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This is a helper function that find a SUA IE element.
 *     
 *  Input Parameters:
 *      ies - pointer to th first element of an array of ITS_SUA_IE
 *      ieCount - Number of ies in the array
 *      paramId - ie Id of the searched IE
 *
 *  Input/Output Parameters:
 *      None
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to the IE if found, else NULL
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
SUADLLAPI ITS_SUA_IE*
SUA_FindSUAIE(ITS_SUA_IE *ies, int ieCount, ITS_USHORT paramId)
{
    int i;
    
    for (i=0; i < ieCount; i++)
    {
        if (ies[i].param_id == paramId)
        {
            return &ies[i];
        }
    }

    return NULL;
}





/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change the common message header from host
 *      to network format.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      msgHdr - pointer to the message common message header.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
SUADLLAPI void
SUA_HComHdrToN(SUA_MSG_HDR *msgHdr)
{
    msgHdr->msgLen = SOCK_HToNL(msgHdr->msgLen);

    return;
}





/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to convert the common message header from
 *      network to host format.
 *     
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      msgHdr - pointer to the message common message header.
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
 ******************************************************************************/
SUADLLAPI void
SUA_NComHdrToH(SUA_MSG_HDR *msgHdr)
{

    msgHdr->msgLen = SOCK_NToHL(msgHdr->msgLen);

    return;
}





/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change an ITS_SUA_IE array to the network 
 *      format
 *     
 *  Input Parameters:
 *      ieCount - number of element in the array.
 *
 *  Input/Output Parameters:
 *      ies - pointer to the first element of the array.
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
 ******************************************************************************/
void
SUA_HsuaIESToN(ITS_SUA_IE *ies)
{
    
    switch (ies->param_id)
    {
    case SUA_PRM_MSG_HDR:

        ies->param_data.msgHeader.msgLen = 
                          SOCK_HToNL(ies->param_data.msgHeader.msgLen);
    
        break;

    case SUA_PRM_CAUSE_USER:

        ies->param_data.causeUsr.cause = 
                          SOCK_HToNS(ies->param_data.causeUsr.cause);

        ies->param_data.causeUsr.user = 
                          SOCK_HToNS(ies->param_data.causeUsr.user);
    
        break;

#if 0
    case SUA_PRM_REASON:

        ies->param_data.reason.reason = 
                          SOCK_HToNL(ies->param_data.reason.reason);

        break;
#endif

    case SUA_PRM_TRAFFIC_MODE:

        ies->param_data.trafMd.tm = 
                       SOCK_HToNL(ies->param_data.trafMd.tm);

        break;           

    case SUA_PRM_ERROR_CODE:

        ies->param_data.errorCode.errCode = 
                          SOCK_HToNL(ies->param_data.errorCode.errCode);

        break;           

    case SUA_PRM_STATUS_TYPE_ID:

        ies->param_data.statusType.id = 
                          SOCK_HToNS(ies->param_data.statusType.id);

        ies->param_data.statusType.type = 
                          SOCK_HToNS(ies->param_data.statusType.type);

        break;

    case SUA_PRM_CONG_LEVEL:

        ies->param_data.congestion.level = 
                          SOCK_HToNL(ies->param_data.congestion.level);

        break;

    case SUA_PRM_SRC_REF_NUM:
    case SUA_PRM_DST_REF_NUM:

        ies->param_data.srcRefNum.refNum = 
                          SOCK_HToNL(ies->param_data.srcRefNum.refNum);

        break;

#if 0
    case SUA_PRM_FORMAT_ID:

        ies->param_data.scmg.formatId = 
                          SOCK_HToNL(ies->param_data.scmg.formatId);

        break;
#endif

    case SUA_PRM_SMI:

        ies->param_data.smi.smi = 
                          SOCK_HToNS(ies->param_data.smi.smi);

        break;


    case SUA_PRM_PROT_CLASS:

        ies->param_data.pClass.value = 
                          SOCK_HToNL(ies->param_data.pClass.value); 

        break;

    case SUA_PRM_IMPORTANCE:

        ies->param_data.importance.value = 
                          SOCK_HToNL(ies->param_data.importance.value); 

        break;

    case SUA_PRM_HOP_CNT:

        ies->param_data.hopCount.value = 
                          SOCK_HToNL(ies->param_data.hopCount.value); 

        break;

       default :

          break;

    }


    return;
}





/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to change an ITS_SUA_IE array to the HOST 
 *      format.
 *     
 *  Input Parameters:
 *      ieCount - number of element in the array.
 *
 *  Input/Output Parameters:
 *      ies - pointer to the first element of the array.
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
 ******************************************************************************/
void
SUA_NsuaIESToH(ITS_SUA_IE *ies)
{ 
    switch (ies->param_id)
    {
    case SUA_PRM_MSG_HDR:

        ies->param_data.msgHeader.msgLen = 
                          SOCK_NToHL(ies->param_data.msgHeader.msgLen);
        
        break;

    case SUA_PRM_CAUSE_USER:

        ies->param_data.causeUsr.cause = 
                          SOCK_NToHS(ies->param_data.causeUsr.cause);

        ies->param_data.causeUsr.user = 
                          SOCK_NToHS(ies->param_data.causeUsr.user);
        
        break;

#if 0
    case SUA_PRM_REASON:

        ies->param_data.reason.reason = 
                          SOCK_NToHL(ies->param_data.reason.reason);

        break;

#endif
    case SUA_PRM_TRAFFIC_MODE:

        ies->param_data.trafMd.tm = 
                       SOCK_NToHL(ies->param_data.trafMd.tm);

        break;           

    case SUA_PRM_ERROR_CODE:

        ies->param_data.errorCode.errCode = 
                          SOCK_NToHL(ies->param_data.errorCode.errCode);

        break;           

    case SUA_PRM_STATUS_TYPE_ID:

        ies->param_data.statusType.id = 
                          SOCK_NToHS(ies->param_data.statusType.id);

        ies->param_data.statusType.type = 
                          SOCK_NToHS(ies->param_data.statusType.type);

        break;

    case SUA_PRM_CONG_LEVEL:

        ies->param_data.congestion.level = 
                          SOCK_NToHL(ies->param_data.congestion.level);

        break;

    case SUA_PRM_SRC_REF_NUM:
    case SUA_PRM_DST_REF_NUM:

        ies->param_data.srcRefNum.refNum = 
                          SOCK_NToHL(ies->param_data.srcRefNum.refNum);

        break;

#if 0
    case SUA_PRM_FORMAT_ID:

        ies->param_data.scmg.formatId = 
                          SOCK_NToHL(ies->param_data.scmg.formatId);

        break;
#endif

    case SUA_PRM_SMI:

        ies->param_data.smi.smi = 
                          SOCK_NToHS(ies->param_data.smi.smi);

        break;
    
    case SUA_PRM_PROT_CLASS:

        ies->param_data.pClass.value = 
                          SOCK_NToHL(ies->param_data.pClass.value);

        break;
    
    case SUA_PRM_IMPORTANCE:

        ies->param_data.importance.value = 
                          SOCK_NToHL(ies->param_data.importance.value);

        break;
    
    case SUA_PRM_HOP_CNT:

        ies->param_data.hopCount.value = 
                          SOCK_NToHL(ies->param_data.hopCount.value);

        break;

    }

    return;
}







/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to encode a SUA message from a given array of
 *      SUA IES.
 *     
 *  Input Parameters:
 *      ies - pointer to the first element of IES array (common msg header).
 *      ieCount - number of IES in the array.
 *      desc - pointer to SUA message descriptor.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      event - pointer to ITS_EVENT containing the built SUA message.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
SUADLLAPI int
SUA_EncodeMsg(ITS_SUA_IE *ies, int ieCount,ITS_EVENT *event,
              SUA_MSG_DESC* desc)
{
    int i, j, offset, evoffset;
    ITS_SUA_IE* ieRef[ITS_MAX_SUA_IES];
    ITS_USHORT *margs = desc->mParam;
    int nmargs = desc->nmParam;
    ITS_USHORT *oargs = desc->oParam;
    int noargs = desc->noParam;
    ITS_USHORT len = 0, padding = 0;
    ITS_BOOLEAN sawOpt = ITS_FALSE;
    ITS_USHORT  suaMsgLen = 0;

    assert(event != NULL);

    ITS_EVENT_TERM(event);

    /* sanity */
    if (ieCount > ITS_MAX_SUA_IES)
    {
        return (ITS_EOVERFLOW);
    }
     

    /* 
     * The first step is to use a temporary array of IES* to
     * store ptrs to the message parameters in the following order
     * - the common header
     * - the madatory parameters
     * - the optional parameters if any
     * In the meanwhile we can check if all mandatory parameters are 
     * present for sanity purposes
     */

    /*
     * The first IE int the array should be the common message header
     * this is common to all SUA messages
     */
    if(ies[0].param_id != SUA_PRM_MSG_HDR)
    {
        return (ITS_EINVALIDARGS);
    }

    ieRef[0] = ies;
    suaMsgLen += 8;

    /* start at one, 0 is the common msg header */
    offset = 1;

    /* find the mandatory parameters */
    for (i = 0; i < nmargs; i++)
    {
        for (j = 1; j < ieCount; j++) /* we can start at 1, 0 is message header */
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                suaMsgLen += ies[j].param_length + SUA_GetPadding(ies[j].param_length) + 4;
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }
    
    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                suaMsgLen += ies[j].param_length + SUA_GetPadding(ies[j].param_length) + 4;
                offset++;
                sawOpt = ITS_TRUE;
                break;
            }
        }
        /* if missing, that's ok */
    }

    ITS_EVENT_INIT (event, 0, suaMsgLen);

    /* skip extras */
    while (offset <= ieCount)   /* we use <= because of the common 
                                   message header offset starts at 1 */
    {
        ieRef[offset] = NULL;
        offset++;
    }

    evoffset = sizeof(SUA_MSG_HDR);

    /* copy in the mandatories */
    for (i = 1; i <= nmargs; i++)
    {
        ITS_USHORT paramId = ieRef[i]->param_id;

        /* change the params to network format */
        SUA_HsuaIESToN(ieRef[i]);

        /* cpy param id */
        ieRef[i]->param_id = SOCK_HToNS(ieRef[i]->param_id);

        memcpy(&event->data[evoffset], &ieRef[i]->param_id, 
               sizeof(ITS_USHORT));
        evoffset += 2;
        /* cpy param len */
        len = ieRef[i]->param_length;
        padding = SUA_GetPadding(len);
        ieRef[i]->param_length = SOCK_HToNS(ieRef[i]->param_length + 4);

        memcpy(&event->data[evoffset], &ieRef[i]->param_length, 
               sizeof(ITS_USHORT));

        evoffset += 2;
        
        if (paramId == SUA_PRM_SRC_ADDR ||
            paramId == SUA_PRM_DST_ADDR)
        {
            int addrLen = ieRef[i]->param_data.dstAddrs.len + 4;

            padding = SUA_GetPadding(addrLen);

            memset(&event->data[evoffset], 0, (addrLen + padding));
            
            memcpy(&event->data[evoffset], 
                   ieRef[i]->param_data.dstAddrs.routIndic, 2);
            
            memcpy(&event->data[evoffset + 2], 
                   ieRef[i]->param_data.dstAddrs.addrIndic, 2);

            memcpy(&event->data[evoffset + 4], 
                   ieRef[i]->param_data.dstAddrs.addrData, 
                   ieRef[i]->param_data.dstAddrs.len);

            evoffset += (addrLen + padding);           
        }
        else
        {
            memset(&event->data[evoffset], 0, (len + padding));

            memcpy(&event->data[evoffset], &ieRef[i]->param_data, len);

            evoffset += (len + padding);
        }

        
    }

    /* copy in the optionals */

    for (i = 1; i <= noargs; i++)
    {
        ITS_USHORT paramId;

        if (ieRef[i + nmargs] == NULL )
        {
            break;
        }

        paramId = ieRef[i+nmargs]->param_id;

        /* change the params to network format */
        SUA_HsuaIESToN(ieRef[i + nmargs]);

        /* cpy param id */
        ieRef[i + nmargs]->param_id = SOCK_HToNS(ieRef[i+nmargs]->param_id);


        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_id, 
               sizeof(ITS_USHORT));
        evoffset += 2;
        /* cpy param len */
        len = ieRef[i+nmargs]->param_length;
        padding = SUA_GetPadding(len);
        ieRef[i + nmargs]->param_length = 
                                 SOCK_HToNS(ieRef[i+nmargs]->param_length + 4);


        memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_length, 
               sizeof(ITS_USHORT));

        evoffset += 2;

        
        if (paramId == SUA_PRM_SRC_ADDR ||
            paramId == SUA_PRM_DST_ADDR)
        {
            int addrLen = ieRef[i + nmargs]->param_data.dstAddrs.len + 4;

            padding = SUA_GetPadding(addrLen);

            memset(&event->data[evoffset], 0, (addrLen + padding));
            
            memcpy(&event->data[evoffset], 
                   ieRef[i + nmargs]->param_data.dstAddrs.routIndic, 2);
            
            memcpy(&event->data[evoffset + 2], 
                   ieRef[i + nmargs]->param_data.dstAddrs.addrIndic, 2);

            memcpy(&event->data[evoffset + 4], 
                   ieRef[i + nmargs]->param_data.dstAddrs.addrData, 
                   ieRef[i + nmargs]->param_data.dstAddrs.len);

            evoffset += (addrLen + padding);           
        }
        else
        {

            memset(&event->data[evoffset], 0, (len + padding));

            memcpy(&event->data[evoffset], &ieRef[i+nmargs]->param_data, len);

            evoffset += (len + padding);
        }
    }

    /* set final length */
    event->len = evoffset;

    /* take care of the message length */
    ieRef[0]->param_data.msgHeader.msgLen = SOCK_HToNL(event->len);

    /* copy in the message header with updated message pointers */
    memcpy(&event->data[0], &ieRef[0]->param_data, sizeof(SUA_MSG_HDR));

    /* WHAT ABOUT THE EVENT SOURCE -> left to the user to fill in */

    return (ITS_SUCCESS);

}






/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to decode a SUA message to an array of SUA IES.
 *     
 *  Input Parameters:
 *      ev - pointer to ITS_EVENT containing the SUA message to be decoded.
 *      desc - pointer to the message descriptor.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      ies - pointer to the array of IES where the message is decoded.
 *      ieCount - number of decode IES in the array.
 *
 *  Return Value:
 *      ITS_SUCCESS - any other return value would indicate an IntelliSS7 
 *                    error has occured.
 *
 *  Notes:
 *      This function is used internally that is not directly by the user.
 *
 *  See Also:
 *      SUA_EncodeMsg().
 *
 ******************************************************************************/
SUADLLAPI int
SUA_DecodeMsg(ITS_SUA_IE *ies, int *ieCount, ITS_EVENT *ev,
              SUA_MSG_DESC *desc)
{
    ITS_USHORT msgLen = ev->len;
    int evOffset = 0;
    ITS_SUA_IE *ieRef = ies;

    *ieCount = 0;

    /* take care of the common msg header */
    ies[0].param_id = SUA_PRM_MSG_HDR;
    ies[0].param_length = sizeof(SUA_MSG_HDR);
    memcpy(&ies[0].param_data.msgHeader, &ev->data[evOffset], 
           sizeof(SUA_MSG_HDR));

    SUA_NComHdrToH(&ies[0].param_data.msgHeader);

    (*ieCount)++;
    ies++;
    evOffset += sizeof(SUA_MSG_HDR);
    
    
    /* mandatory parameters */
    if (desc->nmParam != 0)   /* It can be possible */
    {
        int i;

        for (i = 0; i < desc->nmParam; i++)
        {
            ies[0].param_id = ev->data[evOffset] << 8 | 
                              ev->data[evOffset + 1];
            evOffset += 2;
            ies[0].param_length = (ev->data[evOffset] << 8 | 
                                  ev->data[evOffset + 1]) - 4;
            evOffset += 2;
          
            if (ies[0].param_id == SUA_PRM_SRC_ADDR ||
                ies[0].param_id == SUA_PRM_DST_ADDR)
            {
                memcpy(ies[0].param_data.dstAddrs.routIndic, 
                       &ev->data[evOffset], 2);

                memcpy(ies[0].param_data.dstAddrs.addrIndic, 
                       &ev->data[evOffset + 2], 2);

                memcpy(ies[0].param_data.dstAddrs.addrData,
                       &ev->data[evOffset + 4], ies[0].param_length - 4);
            }
            else
            {
                memcpy(&ies[0].param_data.data, &ev->data[evOffset], 
                       ies[0].param_length);
            }

            evOffset += ies[0].param_length + SUA_GetPadding(ies[0].param_length);
            
            (*ieCount)++;
    
            if (*ieCount > ITS_MAX_SUA_IES)
            {
                return (ITS_EOVERFLOW);
            }

            /* put the params in the host format */
            SUA_NsuaIESToH(ies);

            ies++;
        }  
    }


    /* if we have optional parameters take care of them too */
    if (desc->noParam != 0)
    {
        while (evOffset < msgLen)
        {
            ies[0].param_id = ev->data[evOffset] << 8 | 
                              ev->data[evOffset + 1];
            evOffset += 2;

            ies[0].param_length = (ev->data[evOffset] << 8 | 
                                  ev->data[evOffset + 1]) - 4;

            evOffset += 2;
            
            memcpy(&ies[0].param_data.data, &ev->data[evOffset], 
                   ies[0].param_length);

            evOffset += ies[0].param_length + SUA_GetPadding(ies[0].param_length); 

            (*ieCount)++;

            if (*ieCount > ITS_MAX_SUA_IES)
            {
                return (ITS_EOVERFLOW);
            }

            /* put the params in the host format */
            SUA_NsuaIESToH(ies);

            ies++;
        }
    }

    /* put the params in the host format */
    SUA_NsuaIESToH(ieRef);

    return (ITS_SUCCESS);
}




SUADLLAPI int 
SUA_EncodeRoutingContext(ITS_OCTET *data, ITS_USHORT *len, ITS_UINT *rkList, 
                         int size)
{
    int ret = ITS_SUCCESS, i;
    int offset = 0;
    
    if (rkList == NULL)
    {
        *len = 0;
    }
    else
    {
        for (i = 0; i<size; i++)
        {
            rkList[i] = SOCK_HToNL(rkList[i]);
            memcpy(&data[offset], &rkList[i], sizeof(ITS_UINT));
            offset += sizeof(ITS_UINT);      
        }

        *len = offset;

    }
    return ret;
}


SUADLLAPI int
SUA_DecodeRoutingContext(ITS_OCTET *data, ITS_USHORT len, ITS_UINT *rkList,
                         int *size)
{
    int ret = ITS_SUCCESS;
    int num = len / sizeof(ITS_UINT);

    *size = 0;

    if (!(len % sizeof(ITS_UINT)) && (num < SUA_MAX_RK_NUM))
    {
        int i;

        for (i = 0; i < num; i++)
        {
            memcpy(&rkList[i], data, sizeof(ITS_UINT));
            rkList[i] = SOCK_NToHL(rkList[i]);
            data += sizeof(ITS_UINT);
            (*size)++;
        }
    }
    else
    {
        return -1; /* TODO pick error code */
    }

    return ret;
}


SUADLLAPI int
SUA_EncodeRoutingKey(SUA_ROUT_KEY *rkey, ITS_USHORT *rKeyLen, ITS_UINT rkid, 
                     SUA_TRAFFIC_MODE *tm, SUA_NET_APP *na, SUA_ADDRS *srcAddr, 
                     SUA_ADDRS *dstAddr, SUA_ADDRS_RANGE *addrRange, ITS_USHORT addrRangeLen)
{
    int addrLen; 
    int offset = 0;
    int padding = 0;
    ITS_USHORT len;
    ITS_USHORT param_id;

    rkid = SOCK_HToNL(rkid);
    memcpy(&rkey->routKey[offset], &rkid,
           sizeof(ITS_UINT));
    offset += 4;

    if (tm != NULL)
    {
        param_id = SUA_PRM_TRAFFIC_MODE;

        param_id = SOCK_HToNS(param_id);

        memcpy(&rkey->routKey[offset], &param_id,
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = 8; 

        len = SOCK_HToNS(len);

        memcpy(&rkey->routKey[offset], &len,
               sizeof(ITS_USHORT));

        offset += 2;
       
        tm->tm = SOCK_HToNL(tm->tm);

        memcpy(&rkey->routKey[offset], &tm->tm,
               sizeof(ITS_UINT));
        offset += 4;

    }

    if (na != NULL)
    {
        param_id = SUA_PRM_NET_APP;

        param_id= SOCK_HToNS(param_id);

        memcpy(&rkey->routKey[offset], &param_id,
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = 8; 

        len = SOCK_HToNS(len);

        memcpy(&rkey->routKey[offset], &len,
               sizeof(ITS_USHORT));

        offset += 2;
       
        na->networkApp = SOCK_HToNL(na->networkApp);

        memcpy(&rkey->routKey[offset], &na->networkApp,
               sizeof(ITS_UINT));
        offset += 4;

    }


    if ( srcAddr != NULL)
    {
        param_id = SUA_PRM_SRC_ADDR;
        param_id= SOCK_HToNS(param_id);

        memcpy(&rkey->routKey[offset], &param_id,
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = srcAddr->len + 4; 

        padding = SUA_GetPadding(len);
        len = SOCK_HToNS(len + 8);

        memcpy(&rkey->routKey[offset], &len,
               sizeof(ITS_USHORT));

        offset += 2;

        addrLen =  srcAddr->len + 4;

        padding = SUA_GetPadding(addrLen);

        memset(&rkey->routKey[offset], 0, (addrLen + padding));
            
        memcpy(&rkey->routKey[offset], 
               srcAddr->routIndic, 2);
    
        memcpy(&rkey->routKey[offset + 2], 
               srcAddr->addrIndic, 2);

        memcpy(&rkey->routKey[offset + 4], 
               srcAddr->addrData, 
               srcAddr->len);

        offset += (addrLen + padding);           
    }

    if ( dstAddr != NULL)
    {
        param_id = SUA_PRM_DST_ADDR;
        param_id= SOCK_HToNS(param_id);

        memcpy(&rkey->routKey[offset], &param_id,
               sizeof(ITS_USHORT));
        offset += 2;

        /* cpy param len */
        len = dstAddr->len + 4; 

        padding = SUA_GetPadding(len);
        len = SOCK_HToNS(len + 8);

        memcpy(&rkey->routKey[offset], &len,
               sizeof(ITS_USHORT));

        offset += 2;

        addrLen =  dstAddr->len + 4;

        padding = SUA_GetPadding(addrLen);

        memset(&rkey->routKey[offset], 0, (addrLen + padding));
            
        memcpy(&rkey->routKey[offset], 
               dstAddr->routIndic, 2);
    
        memcpy(&rkey->routKey[offset + 2], 
               dstAddr->addrIndic, 2);

        memcpy(&rkey->routKey[offset + 4], 
               dstAddr->addrData, 
               dstAddr->len);

        offset += (addrLen + padding);           
    }

    *rKeyLen = offset;

    return ITS_SUCCESS;
}

SUADLLAPI int
SUA_DecodeRoutingKey(ITS_OCTET *rkey, ITS_USHORT rKeyLen,ITS_UINT *rkid,
                     ITS_SUA_IE *ies, ITS_OCTET *ieCount)
{
    int ret = ITS_SUCCESS;
    int  offset = 0;
    ITS_USHORT paramId, paramLen;


    memcpy(rkid, &rkey[offset], sizeof(ITS_UINT));

    *rkid = SOCK_NToHL(*rkid);

    offset += 4;

    while (offset < (rKeyLen - 4))
    {
        paramId = rkey[offset] << 8 | 
                  rkey[offset + 1];
         
        offset += 2;

        paramLen = (rkey[offset] << 8 | 
                    rkey[offset + 1]) - 4;

        offset += 2;

        switch(paramId)
        {
            case SUA_PRM_TRAFFIC_MODE :
                memcpy(&ies[0].param_data.data, &rkey[offset], 
                       paramLen);
            break;

            case SUA_PRM_SRC_ADDR :
                memcpy(ies[0].param_data.srcAddrs.routIndic, 
                       &rkey[offset], 2);

                memcpy(ies[0].param_data.srcAddrs.addrIndic, 
                       &rkey[offset + 2], 2);

                memcpy(ies[0].param_data.srcAddrs.addrData,
                       &rkey[offset + 4], paramLen - 4);
            break;

            case SUA_PRM_DST_ADDR :
                memcpy(ies[0].param_data.dstAddrs.routIndic, 
                       &rkey[offset], 2);

                memcpy(ies[0].param_data.dstAddrs.addrIndic, 
                       &rkey[offset + 2], 2);

                memcpy(ies[0].param_data.dstAddrs.addrData,
                       &rkey[offset + 4], paramLen - 4);
            break;

            case SUA_PRM_NET_APP :
                memcpy(&ies[0].param_data.data, &rkey[offset], 
                       paramLen);
            break;

            case SUA_PRM_ADDR_RANG :
                memcpy(&ies[0].param_data.data, &rkey[offset], 
                       paramLen);
            break;

            default :
               return !ITS_SUCCESS;
            break;
        }

        offset += paramLen + SUA_GetPadding(paramLen); 

        ies[0].param_id = paramId;

        ies[0].param_length = paramLen;
        
        (*ieCount)++;
    
        if (*ieCount > ITS_MAX_SUA_IES)
        {
            return (ITS_EOVERFLOW);
        }

        /* put the params in the host format */
        SUA_NsuaIESToH(ies);

        ies++;

    }
    
    return (ret);
}



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the SUA transport subsytem.
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
 *      If the SUA subsystem is initialized correctly, ITS_SUCCESS is
 *          returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    char buf[ITS_PATH_MAX];
    char value[ITS_PATH_MAX];
    const char *name;
    RESFILE_Manager*    res;
    int ret;

    if (APPL_GetName() == NULL)
    {
        ITS_TRACE_ERROR(("Create: No application name!\n"));

    }

    if (APPL_GetConfigFileName())
    {
        strcpy(buf, APPL_GetConfigFileName());
    }

    res = RESFILE_CreateResourceManager(buf);

    if (RESFILE_GetKeyValueOf(res, "UAL_Manager", SUA_INTERWORK_MODE_STRING,
                              value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        if (strstr(value, SUA_SG_MODE_STRING) != NULL)
        {
            _sua_itw_mode = SUA_ITW_SG;
        }
        else
        {
            _sua_itw_mode = SUA_ITW_ASP;
        }
    }

    ITS_TRACE_DEBUG(("Initialize\n"));

    return SCTPTRAN_RegisterCodec(SUA_CLASS_NAME, SCTP_PAYLOAD_SUA,
                                  SCCP_To_SUA_Codec, SUA_To_SCCP_Codec);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the SUA transport subsystem.
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
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_Initialize()
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    ITS_TRACE_DEBUG(("Terminate:\n"));

    SCTPTRAN_DeregisterCodec(SUA_CLASS_NAME);
}

static ITS_ClassRec itsSUA_ClassRec =
{
    /* core part */
    {
        NULL,                           /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        SUA_CLASS_NAME,                 /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

SUADLLAPI ITS_Class itsSUA_Class = &itsSUA_ClassRec;
