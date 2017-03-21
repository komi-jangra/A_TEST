/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: itu-isup_93.c,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:54  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:11  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:57  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:54:06  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.1.38.2  2005/02/08 12:30:26  ssingh
 * LOG: Peg increament after receiving Unexpected Msg in given FSM state.
 * LOG: Bug# 1448. (Ramesh KV, Abhijit Dutta)
 * LOG:
 * LOG: Revision 7.1.4.1.38.1  2004/12/07 11:07:55  mmanikandan
 * LOG: Windows Compilation support testing bugs.
 * LOG:
 * LOG: Revision 7.1.4.1  2003/05/07 11:03:12  ssingh
 * LOG: Latest Changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.2  2003/04/22 08:59:29  akumar
 * LOG: Replaced Number of CICs Magic Number with meaningful MACRO.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:30  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/08/01 15:57:49  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 6.5.2.2  2002/07/10 19:34:16  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.5.2.1  2002/07/06 20:06:42  hbalimid
 * LOG: Fixed all warnings.
 * LOG:
 * LOG: Revision 6.5  2002/06/03 16:23:50  sjaddu
 * LOG: Added Param level confusion.
 * LOG:
 * LOG: Revision 6.4  2002/05/28 16:38:32  sjaddu
 * LOG: Added CFN Procedures.
 * LOG:
 * LOG: Revision 6.3  2002/05/20 15:49:09  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 1.4.2.4  2002/04/04 22:19:42  ssanyal
 * LOG: Timer values as per Table A.1/Q764.
 * LOG:
 * LOG: Revision 1.4.2.3  2002/04/02 23:53:54  ssharma
 * LOG: Completion of phase 2, coding standards conformance.
 * LOG:
 * LOG: Revision 1.4.2.2  2002/03/22 16:24:12  ssharma
 * LOG: Warning removal, CGRS related changes.
 * LOG:
 * LOG: Revision 1.4.2.1  2002/03/01 19:01:59  ssharma
 * LOG: Build on NT PR6.
 * LOG:
 * LOG: Revision 1.4  2002/02/26 17:04:50  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 1.3  2002/02/19 23:04:07  ssharma
 * LOG: Fix traces, .ini file after functional test.
 * LOG:
 * LOG: Revision 1.2  2002/02/13 23:23:05  mmiers
 * LOG: Warning removal, debug.
 * LOG:
 * LOG: Revision 1.1  2002/02/13 18:28:33  mmiers
 * LOG: Finish off the ISUP integration.  Still need to add CHINA
 * LOG: variant lib.
 * LOG:
 * LOG: Revision 5.4  2002/02/12 23:29:04  mmiers
 * LOG: ISUP parser in place.
 * LOG:
 * LOG: Revision 5.3  2002/02/08 21:48:16  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.2  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.1  2002/02/01 20:07:31  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/01/28 15:50:28  yranade
 * LOG: Set the appropriate flags at the beginning.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/22 23:37:11  ssharma
 * LOG: New files for IntelliNet ISUP stack.
 * LOG:
 * LOG: 
 *****************************************************************************/

#undef ANSI
#undef CCITT
#define CCITT

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <its.h>
#include <its_hash.h>
#include <isup_variants.h>
#include <itu/isup_93.h>
#include <isup_sn.h>

/*
 *
 * ISUP ITU 93 Variant Class
 *
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ITU93 class record.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(objClass) = itsCORE_Class;

    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[0] = NULL;
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[1] = &ISUP_IAM_Desc;     /* 0x01 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[2] = &ISUP_SAM_Desc;     /* 0x02 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[3] = &ISUP_INR_Desc;     /* 0x03 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[4] = &ISUP_INF_Desc;     /* 0x04 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[5] = &ISUP_COT_Desc;     /* 0x05 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[6] = &ISUP_ACM_Desc;     /* 0x06 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[7] = &ISUP_CON_Desc;     /* 0x07 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[8] = &ISUP_FOT_Desc;     /* 0x08 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[9] = &ISUP_ANM_Desc;     /* 0x09 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[10] = NULL;               /* 0x0A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[11] = NULL;               /* 0x0B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[12] = &ISUP_REL_Desc;     /* 0x0C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[13] = &ISUP_SUS_Desc;     /* 0x0D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[14] = &ISUP_RES_Desc;     /* 0x0E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[15] = NULL;               /* 0x0F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[16] = &ISUP_RLC_Desc;     /* 0x10 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[17] = &ISUP_CCR_Desc;     /* 0x11 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[18] = &ISUP_RSC_Desc;     /* 0x12 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[19] = &ISUP_BLO_Desc;     /* 0x13 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[20] = &ISUP_UBL_Desc;     /* 0x14 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[21] = &ISUP_BLA_Desc;     /* 0x15 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[22] = &ISUP_UBA_Desc;     /* 0x16 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[23] = &ISUP_GRS_Desc;     /* 0x17 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[24] = &ISUP_CGB_Desc;     /* 0x18 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[25] = &ISUP_CGU_Desc;     /* 0x19 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[26] = &ISUP_CGBA_Desc;    /* 0x1A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[27] = &ISUP_CGUA_Desc;    /* 0x1B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[28] = NULL;               /* 0x1C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[29] = NULL;               /* 0x1D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[30] = NULL;               /* 0x1E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[31] = &ISUP_FAR_Desc;     /* 0x1F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[32] = &ISUP_FAA_Desc;     /* 0x20 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[33] = &ISUP_FRJ_Desc;     /* 0x21 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[34] = NULL;               /* 0x22 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[35] = NULL;               /* 0x23 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[36] = &ISUP_LPA_Desc;     /* 0x24 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[37] = NULL;               /* 0x25 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[38] = NULL;               /* 0x26 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[39] = NULL;               /* 0x27 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[40] = &ISUP_PAM_Desc;     /* 0x28 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[41] = &ISUP_GRA_Desc;     /* 0x29 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[42] = &ISUP_CQM_Desc;     /* 0x2A */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[43] = &ISUP_CQR_Desc;     /* 0x2B */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[44] = &ISUP_CPG_Desc;     /* 0x2C */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[45] = &ISUP_USR_Desc;     /* 0x2D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[46] = &ISUP_UCIC_Desc;    /* 0x2E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[47] = &ISUP_CFN_Desc;     /* 0x2F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[48] = &ISUP_OLM_Desc;     /* 0x30 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[49] = NULL;               /* 0x31 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[50] = &ISUP_NRM_Desc;     /* 0x32 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[51] = &ISUP_FAC_Desc;     /* 0x33 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[52] = &ISUP_UPT_Desc;     /* 0x34 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[53] = &ISUP_UPA_Desc;     /* 0x35 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[54] = &ISUP_IDR_Desc;     /* 0x36 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[55] = &ISUP_IRS_Desc;     /* 0x37 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[56] = &ISUP_SGM_Desc;     /* 0x38 */

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ITU93 class record.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ITU93 class part record.
 *
 *  Input Parameters:
 *      classRec - the class to init
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ITU93_ClassPartInitialize(ITS_Class classRec)
{
    ISUP_DEBUG(("Executing: ITU93_ClassPartInitialize for %s\n",
                ITS_CLASS_CLASSNAME(classRec)));

    if (ISUP_CLASS_INFO(classRec) == ISUP_INFO_INHERIT)
    {
        ISUP_DEBUG(("Deriving ClassInfo. from BaseClass\n"));
        ISUP_CLASS_INFO(classRec) =
            ISUP_CLASS_INFO(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Registered Own Class Info\n"));
    }

    if (ISUP_DECODE_MSG(classRec) == ISUP_DECODE_MSG_INHERIT)
    {
        ISUP_DEBUG(("Deriving Decode func. from BaseClass\n"));
        ISUP_DECODE_MSG(classRec) =
            ISUP_DECODE_MSG(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own Decode function\n"));
    }                                                                     

    if (ISUP_ENCODE_MSG(classRec) == ISUP_ENCODE_MSG_INHERIT)
    {
        ISUP_DEBUG(("Deriving Encode func. from BaseClass\n"));
        ISUP_ENCODE_MSG(classRec) =
            ISUP_ENCODE_MSG(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own Encode function\n"));
    }

    if (ISUP_COMPUTE_MSIZE(classRec) == ISUP_COMPUTE_MSIZE_INHERIT)
    {
        ISUP_DEBUG(("Deriving ComputeMsize func. from BaseClass\n"));
        ISUP_COMPUTE_MSIZE(classRec) =
            ISUP_COMPUTE_MSIZE(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own ComputeMsize function\n"));
    }

    if (ISUP_HANDLE_UNREC_MSG(classRec) == ISUP_HANDLE_UNREC_MSG_INHERIT)
    {
        ISUP_DEBUG(("Deriving UnrecMsg Handler func. from BaseClass\n"));
        ISUP_HANDLE_UNREC_MSG(classRec) =
            ISUP_HANDLE_UNREC_MSG(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own UnrecMsg. Handler function\n"));
    }

    if (ISUP_INIT_MSG_PROCS(classRec) == ISUP_INIT_MSG_PROCS_INHERIT)
    {
        ISUP_DEBUG(("Deriving MsgProcs Hash Table from BaseClass\n"));
        ISUP_CLASS_HASH_MSG_PROCS(classRec) =
            ISUP_CLASS_HASH_MSG_PROCS(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own InitMsgProcs. Handler function\n"));

        if ((ISUP_INIT_MSG_PROCS(classRec)(classRec)) == ITS_SUCCESS)
        {
            ISUP_DEBUG(("Successfully Initialized MsgProc. HashTable\n"));
        }
        else
        {
            ISUP_DEBUG(("MsgProc. HashTable Init fail: exiting.\n"));
            return ITS_EINITFAIL;
        }
    }

    if (ISUP_INIT_TIMEOUT_PROCS(classRec) == ISUP_INIT_TIMEOUT_PROCS_INHERIT)
    {
        ISUP_DEBUG(("Deriving TimeoutProc Hash Table from BaseClass\n"));
        ISUP_CLASS_HASH_TIMEOUT_PROCS(classRec) =
            ISUP_CLASS_HASH_TIMEOUT_PROCS(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own InitTimeoutProc. Handler function\n"));
                                                                               
        if ((ISUP_INIT_TIMEOUT_PROCS(classRec)(classRec)) == ITS_SUCCESS)
        {
            ISUP_DEBUG(("\n Successfully Initialized TimeoutProc. HashTable\n"));
        }
        else
        {
            ISUP_DEBUG(("\n TimeoutProc. HashTable Init fail: exiting.\n"));
            return ITS_EINITFAIL;
        }                                          
    }                                                                                                                                                         
    if (ISUP_GET_MSG_PROC(classRec) == ISUP_GET_MSG_PROC_INHERIT)
    {
        ISUP_DEBUG(("\n Deriving GetMsgProc func. from BaseClass\n"));
        ISUP_GET_MSG_PROC(classRec) =
            ISUP_GET_MSG_PROC(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("\n Variant registered Own GetMsgProc. Handler function\n"));
    }
                                                                               
    if (ISUP_GET_TIMEOUT_PROC(classRec) == ISUP_GET_TIMEOUT_PROC_INHERIT)
    {
        ISUP_DEBUG(("Deriving GetTimeoutProcs func. from BaseClass\n"));
        ISUP_GET_TIMEOUT_PROC(classRec) =
            ISUP_GET_TIMEOUT_PROC(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own GetTimeoutProcs. Handler function\n"));
    }

    if (ISUP_SET_MSG_PROC(classRec) == ISUP_SET_MSG_PROC_INHERIT)
    {
        ISUP_DEBUG(("Deriving SetMsgProc func. from BaseClass\n"));
        ISUP_SET_MSG_PROC(classRec) =
            ISUP_SET_MSG_PROC(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own SetMsgProc. Handler function\n"));
    }

    if (ISUP_SET_TIMEOUT_PROC(classRec) == ISUP_SET_TIMEOUT_PROC_INHERIT)
    {
        ISUP_DEBUG(("Deriving SetTimeoutProcs func. from BaseClass\n"));
        ISUP_SET_TIMEOUT_PROC(classRec) =
            ISUP_SET_TIMEOUT_PROC(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own SetTimeoutProcs. Handler function\n"));
    }                                                                          

    if (ISUP_HANDLE_UNREC_PARAM(classRec) == ISUP_HANDLE_UNREC_PARAM_INHERIT)
    {
        ISUP_DEBUG(("Deriving HandleUnrecParam func. from BaseClass\n"));
        ISUP_HANDLE_UNREC_PARAM(classRec) =
            ISUP_HANDLE_UNREC_PARAM(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own HandleUnrecParam. Handler function\n"));
    }

    ISUP_DEBUG(("\nITU93_ClassPartInitialize()::"
                  " End executing VARIANT_ClassPartInitialize() for %s\n\n",
                    ITS_CLASS_CLASSNAME(classRec)));

    return (ITS_SUCCESS);
}



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the class record.
 *
 *  Input Parameters:
 *      classRec - the class to destroy
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
static void
ITU93_ClassPartDestroy(ITS_Class classRec)
{
    /* Nothing to do */
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to set the address of a Timeout Handler function
 *      in the Hash Table.  
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      HashTable - placeholder for Timeout Handling function addresses 
 *      Timer - particular timer which popped.
 *      State - state where the timeout indication was received.
 *      func - function address to be inserted in the Table. 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function is recursively called during initialization of the 
 *      variant. For each timer-state combination this function is called to 
 *      store the particular Timeout Handler function pointer in the Hash
 *      Table. 
 *
 *  See Also:
 ****************************************************************************/
int
ITU93_SetTimeoutProc(ITS_Class V_Class, HASH_Table TimeoutProcTable,
                     ITS_UINT tmr, ITS_ISUP_STATE state, 
                     __ISUP_TimeoutHandlerProc func)
{
    ITS_USHORT key = 0;
    
    key = ((state << 8) & 0x0000FF00) | tmr;

    if (HASH_AddEntry(TimeoutProcTable, 0, key,
                              (ITS_POINTER)func) != ITS_SUCCESS)
    {
        ISUP_DEBUG(("could not add function entry in HASH_Table:"
                    " Timer = %x, state = %x: key %x\n", tmr, state, key));

        return ITS_ENOMEM;
    }
    else
    {
        return ITS_SUCCESS;
    }                                                                  
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to store the address of a message Handling
 *      function in the HashTable. 
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      msg - particular message to be handled. 
 *      HashTable - placeholder for Message Handling function addresses 
 *      State - state where the msg was received.
 *      func - function address to be inserted in the Table. 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function is recursively called during initialization of the 
 *      variant. For each msg-state combination this function is called to 
 *      store the particular Message Handler function pointer in the Hash
 *      Table. 
 *
 *  See Also:
 ****************************************************************************/
int
ITU93_SetMsgProc(ITS_Class V_Class, HASH_Table MsgProcTable,
                 ITS_OCTET msg, ITS_ISUP_STATE state,
                 __ISUP_MsgHandlerProc func)
{
    ITS_USHORT key = 0;
    
    key = ((state << 8) & 0x0000FF00) | msg;

    if (HASH_AddEntry(MsgProcTable, 0, key, (ITS_POINTER)func) != ITS_SUCCESS)
    {
        ISUP_DEBUG(("could not add function entry in HASH_Table:"
                    " Msg = %x, state = %x: key %x\n", msg, state, key));
        return ITS_ENOMEM;
    }
    else
    {
        return ITS_SUCCESS;
    }                                                                  
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to initialize the function pointers in the
 *      Timeout Handler Hash Table. 
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ITU93_InitTimeoutProcs(ITS_Class V_Class)
{
    ITS_USHORT state = 0;
    ITS_UINT tmr = 0;
    ITS_USHORT key = 0;
    __ISUP_TimeoutHandlerProc func = NULL;
    ISUP_VariantInfo* var_info = NULL;

    ISUP_DEBUG(("Executing: ITU93_InitTimeoutProc function\n"));

    if ((var_info = ISUP_CLASS_INFO(V_Class)) == NULL)
    {
        ISUP_DEBUG(("could not obtain variant_Info ptr. : returning\n"));

        return ITS_ENOMEM;
    }

    var_info->ISUP_TimeOutProcedures = HASH_CreateTable();
    if (var_info-> ISUP_TimeOutProcedures == NULL)
    {
        ISUP_DEBUG(("could not create HASH_Table\n"));

        return ITS_ENOMEM;
    }                                                                          

    for (state = 0; state < ISUP_NB_STATES; state++)
    {
        for (tmr = 0; tmr < ISUP_NB_TIMERS; tmr++)
        {
            func = __ISUP_GetTimeoutHandler_ITU93(tmr, state);

            if (ITU93_SetTimeoutProc(V_Class, var_info->ISUP_TimeOutProcedures,
                                     tmr, state, func) != ITS_SUCCESS)
            {
                ISUP_DEBUG(("could not add function entry in HASH_Table:"
                            " Timer = %x, state = %x: key %x\n",
                            tmr, state, key));

                return ITS_ENOMEM;
            }
            else
            {
                func = NULL;
                key = 0;
            }
        }
    }

    return ITS_SUCCESS;
}                                                                    


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to write the address of each Message Handler
 *      function in the Hash Table.  
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ITU93_InitMsgProcs(ITS_Class V_Class)
{
    ITS_USHORT state = 0;
    ITS_USHORT msg = 0;
    ITS_USHORT key = 0;
    __ISUP_MsgHandlerProc func = NULL;
    ISUP_VariantInfo *var_info = NULL;

    ISUP_DEBUG(("Executing: ITU93_InitMsgProc function\n"));

    if ((var_info = ISUP_CLASS_INFO(V_Class)) == NULL)
    {
        ISUP_DEBUG(("could not obtain variant_Info ptr. : returning\n"));
        return ITS_ENOMEM;
    }

    var_info->ISUP_MsgProcedures = HASH_CreateTable();
    if (var_info-> ISUP_MsgProcedures == NULL)
    {
        ISUP_DEBUG(("could not create HASH_Table\n"));

        return ITS_ENOMEM;
    }                                                                          

    for (state = 0; state < ISUP_NB_STATES; state++)
    {
        for (msg = 0; msg < ISUP_NB_MSGS; msg++)
        {
            func = __ISUP_GetMsgHandler_ITU93((ITS_OCTET)msg, state);

            if (ITU93_SetMsgProc(V_Class, var_info->ISUP_MsgProcedures,
                                     (ITS_OCTET)msg, state, func) != ITS_SUCCESS)
            {
                ISUP_DEBUG(("\n could not add function entry in HASH_Table:"
                            " msg = %x, state = %x: key %x\n",
                            msg, state, key));

                return ITS_ENOMEM;
            }
            else
            {
                func = NULL;
                key = 0;
            }                                                                 
        }
    }
    return ITS_SUCCESS;
}                                                                    


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to get the address of a particular Message
 *      Handler function in a given state. 
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      msg - particular message received. 
 *      state - the state in which message was received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, a valid function address is returned. 
 *      Otherwise the function returns NULL. 
 *
 *  Notes:
 *      This is the function to be used by a Vendor code writer for finding
 *      a particular message Handler function corresponding to the received
 *      message and current state pair. 
 *
 *  See Also:
 ****************************************************************************/
__ISUP_MsgHandlerProc
ITU93_GetMsgProc(ITS_Class V_Class, ITS_OCTET msg, ITS_ISUP_STATE state)
{
     __ISUP_MsgHandlerProc func = NULL;
     HASH_Table msgProcs = NULL;
     ITS_USHORT key = 0;

     ISUP_DEBUG(("Executing: ITU93_GetMsgProc:mtype %x, state %x\n",
                 msg, state));
     
     if ((msgProcs = (ISUP_CLASS_INFO(V_Class)->ISUP_MsgProcedures)) == NULL)
     {
         ISUP_DEBUG(("ITU93_GetMsgProc: HASH_Table access error\n"));
     
         return (__ISUP_MsgHandlerProc)NULL;
     }
     else
     {
         key = ((state << 8) & 0x0000FF00) | msg;

         ISUP_DEBUG(("mtype = 0x%x, state = 0x%x, key 0x%x \n", msg, state, key));

         if (HASH_FindEntry(msgProcs, 0, key,
                                (ITS_POINTER*)(&func)) != ITS_SUCCESS)
         {
             ISUP_DEBUG(("could not find function entry in HASH_Table\n"));

             return (__ISUP_MsgHandlerProc)NULL;
         }
         else
         {
             ISUP_DEBUG(("\n func ptr. returned is %p \n", func));

             return (__ISUP_MsgHandlerProc)func;
         }
    }
}                                                                    

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to retrieve the address of a Timeout Handler
 *      function for a particular timer in a given state.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      Timer - particular timer which popped. 
 *      state - the state in which message was received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, a valid function address is returned. 
 *      Otherwise the function returns NULL. 
 *
 *  Notes:
 *      This is the function to be used by a Vendor code writer for finding
 *      a particular Timeout Handler function corresponding to the received
 *      message and current state pair. 
 *
 *  See Also:
 ****************************************************************************/
__ISUP_TimeoutHandlerProc
ITU93_GetTimeoutProc(ITS_Class V_Class, ITS_UINT Timer, ITS_ISUP_STATE state)
{
     __ISUP_TimeoutHandlerProc func = NULL;
     HASH_Table timeoutProcs = NULL;
     ITS_USHORT key = 0;

     ISUP_DEBUG(("Executing: ITU93_GetTimeoutProc. timer %x, state %x\n",
                 Timer, state));

     if ((timeoutProcs = (ISUP_CLASS_INFO(V_Class)->ISUP_TimeOutProcedures))
                                                                    == NULL)
     {
         ISUP_DEBUG(("ITU93_GetTimeoutProc: HASH_Table access error\n"));
     
         return (__ISUP_TimeoutHandlerProc)NULL;
     }
     else
     {
         key = ((state << 8) & 0x0000FF00) | Timer;

         ISUP_DEBUG(("state = 0x%x, timer = 0x%x, key 0x%x \n",
                     state, Timer, key));

         if (HASH_FindEntry(timeoutProcs, 0, key,
                                (ITS_POINTER*)(&func)) != ITS_SUCCESS)
         {
             ISUP_DEBUG(("could not find function entry in HASH_Table\n"));

             return (__ISUP_TimeoutHandlerProc)NULL;
         }
         else
         {
             ISUP_DEBUG(("func ptr. returned is %x \n", func));
             return (__ISUP_TimeoutHandlerProc)func;
         }
     }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function defines a method to decode an ISUP message received.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      event - A pointer to the ITS_EVENT structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This is the function to be used by a Vendor code writer for decoding
 *      a particular message received within the stack.  For other ITU variants
 *      this method will be internally called if the particular variant inherits
 *      this method from the ITU93 genre.
 *
 *  See Also:
 ****************************************************************************/
int
ITU93_DecodeMsg(ITS_Class V_Class, ITS_EVENT event, ITS_OCTET o1, ITS_OCTET o2,
                ITS_ISUP_IE* ie, int* count , ITS_HDR* hdr)
{
     ISUP_DEBUG(("Executing: ITU93_Decode\n"));

     return (0); 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function defines a method to encode an ISUP message.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      event - A pointer to the ITS_EVENT structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This is the function to be used by a Vendor code writer for encoding
 *      a particular message .For other ITU variants this method will be 
 *      internally called if the particular variant inherit this method from 
 *      the ITU93 genre.
 *
 *  See Also:
 ****************************************************************************/
int
ITU93_EncodeMsg(ITS_Class V_Class, ITS_ISUP_IE* ie, int i, 
                ITS_OCTET o1, ITS_OCTET o2,
                ITS_HDR* hdr, ITS_EVENT* event)
{
     ISUP_DEBUG(("Executing: ITU93_Encode\n"));

     return (0); 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function defines a method to compute the size of an IE in an ISUP
 *      message.
 *
 *  Input Parameters:
 *      which - the IE for which size is required
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The sizeof the IE.
 *                                                                             
 *  Notes:
 *      This is the function to be used by a Vendor code writer for computing
 *      size of a particular IE .
 *
 *  See Also:
 ****************************************************************************/
ITS_UINT
ITU93_ComputeMsize(ITS_Class V_Class, ITS_OCTET which)
{
    ISUP_DEBUG(("Executing: ITU93_ComputeMsize. arg %x\n", which));

    switch (which)
    {
    case ISUP_PRM_NATURE_CONN_INDICATORS:
        return sizeof(ISUP_CONNECTION_INDICATORS);

    case ISUP_PRM_BKWD_CALL_INDICATORS:
        return sizeof(ISUP_BKWD_CALL_INDICATORS);

    case ISUP_PRM_EVENT_INFO:
        return sizeof(ISUP_EVENT_INFO);                                       

    case ISUP_PRM_CONTINUITY_INDICATORS:
        return sizeof(ISUP_CONTINUITY_INDICATORS);

    case ISUP_PRM_INFO_INDICATORS:
        return sizeof(ISUP_INFORMATION_INDICATORS);

    case ISUP_PRM_INFO_REQ_INDICATORS:
        return sizeof(ISUP_INFORMATION_REQUEST_INDICATORS);

    case ISUP_PRM_FWD_CALL_INDICATORS:
        return sizeof(ISUP_FORWARD_CALL_INDICATORS);

    case ISUP_PRM_CALLING_PARTY_CATEGORY:
        return sizeof(ISUP_CALLING_PARTY_CATEGORY);

    case ISUP_PRM_SUSP_RESUM_INDICATORS:
        return sizeof(ISUP_SUSPEND_RESUME_INDICATORS);

    case ISUP_PRM_CKT_GRP_SUPRVN_MT_IND:
        return sizeof(ISUP_SUPERVISION_MSG_TYPE);                              

#ifdef CCITT
    case ISUP_PRM_FACILITY_INDICATOR:
        return sizeof(ISUP_FACILITY_INDICATOR);

    case ISUP_PRM_TX_MEDIUM_REQMNT:
        return sizeof(ISUP_TX_MEDIUM_REQUIREMENT);
#endif

    default:
        return (0);

    }                                                                          
}
                                                             
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function defines a method to handle a message unrecognized in 
 *      ITU93.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      event - A pointer to the ITS_EVENT structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This is the function to be used by a Vendor code writer for handling
 *      a particular message not supported in ITU93. For other ITU variants 
 *      this method will be internally called if the particular variant
 *      inherits this method from the ITU93 genre.
 *
 *  See Also:
 ****************************************************************************/
ITS_OCTET
ITU93_HandleUnrecMsg(ITS_Class V_Class, ITS_EVENT *evt)
{

    int evoffset = sizeof(ITS_OCTET) + sizeof(ITS_USHORT) +
                   sizeof(MTP3_HEADER) + sizeof(ITS_OCTET)*2;
    ISUP_MSG_COMPATIBILITY_INFO msg_comp;
    ITS_BOOLEAN msgcompFound = ITS_FALSE;
    ITS_OCTET action;


    ISUP_DEBUG(("Entering ITU93_HandleUnrecMsg ...\n"));

    while (evt->data[evoffset] != ISUP_PRM_EOP)
    {
        if (evt->data[evoffset] != ISUP_PRM_MSG_COMPAT_INFO)
        {
            evoffset += evt->data[evoffset + 1];
            evoffset += 2;
        }
        else
        {
            msg_comp.data[0] = evt->data[evoffset];
            msg_comp.data[1] = evt->data[evoffset + 1];

            memcpy(&msg_comp.data[2],&evt->data[evoffset + 1 + 1],
                                                     msg_comp.data[1]);
            msgcompFound = ITS_TRUE;
            break;
        }
    }

    if (!msgcompFound)
    {
        ISUP_DEBUG(("Msg Compatability not found Msg Type %d @@@@@@\n",
                                        evt->data[sizeof(ITS_OCTET)*2 + 
                                                  sizeof(ITS_USHORT) +
                                                  sizeof(MTP3_HEADER)]));
        return ISUP_SEND_CFN_MSG;
    }

    ISUP_WARNING(("ISUP::Unknow msg recieved CFN CFN CFN \n"));

    /* Type B Exanche &&  bit A = 0(Transit Node) */
    if ((ISUP_CLASS_INFO(V_Class)->ISUP_exchangeType == 0x01/*TYPE_B*/) &&
        ((msg_comp.data[2] & 0x01)/*Transit*/== 0x00))
    {
        /* Pass on if possible */
        if (ISUP_CLASS_INFO(V_Class)->pass_on_flag != ITS_TRUE)
        {
            /* Check BIT E */
            if ((msg_comp.data[2] & 0x16 /*PASSON NOT POSSIBLE*/) == 0x016)
            {
                action = ISUP_RELEASE_CALL;
            }
            else
            {
                action = ISUP_DISCARD_MSG;
            }
        }
        else
        {
            action = ISUP_PASS_ON_MSG;
        }
    }
    else /* TYPE_A EXCHANGE (OR) END NODE */
    {
        if ((msg_comp.data[2] & 0x02 /*RELEASE_CALL_MASK*/) == 0x02)
        {
            /* Release the call */
            action = ISUP_RELEASE_CALL;
        }
        else if ((msg_comp.data[2] & 0x04 /*NOTIFICATION_MASK*/) == 0x04)
        {
            /* Send Confusion msg */
            action = ISUP_SEND_CFN_MSG;
        }
        else if ((msg_comp.data[2] & 0x08 /*Discard_mask*/) == 0x08)
        {
            /* Discard msg */
            action = ISUP_DISCARD_MSG;
        }
        else
        {
            /* Pass on */
            if (ISUP_CLASS_INFO(V_Class)->pass_on_flag != ITS_TRUE)
            {
                /* Check bit E */
                if ((msg_comp.data[2] & 0x10 /*Passon not possible*/) == 0x00)
                {
                    action = ISUP_RELEASE_CALL;
                }
                else
                {
                    action = ISUP_DISCARD_MSG;
                }
            }
            else
            {   
                action = ISUP_PASS_ON_MSG;
            }
        }
    }

    return action;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function defines a method to handle an Unrecognized Param in
 *      ITU93.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      mType    - message type
 *      event - A pointer to the ITS_EVENT structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This is the function to be used by a Vendor code writer for handling
 *      a particular message not supported in ITU93. For other ITU variants 
 *      this method will be internally called if the particular variant
 *      inherits this method from the ITU93 genre.
 *
 *  See Also:
 ****************************************************************************/
ITS_OCTET
ITU93_HandleUnrecParamProc(ITS_Class V_Class,ITS_OCTET mType,ITS_OCTET *compInfo)
{
    ITS_OCTET action;

    ISUP_DEBUG(("ISUP::Unknow Paramter recieved  @@@@@@@@@@ CFN CFN CFN \n"));

    /* Type B Exanche &&  bit A = 0(Transit Node) */
    if ((ISUP_CLASS_INFO(V_Class)->ISUP_exchangeType == 0x01/*TYPE_B*/) &&
        ((compInfo[0] & 0x01)/*Transit*/== 0x00))
    {
        /* Pass on if possible */
        if (ISUP_CLASS_INFO(V_Class)->pass_on_flag != ITS_TRUE)
        {
            /* Check BIT E */
            if ((compInfo[0] & 0x16 /*PASSON NOT POSSIBLE*/) == 0x016)
            {
                action = ISUP_DISCARD_PARAM;
            }
            else
            {
                action = ITS_SUCCESS;
            }
        }
        else
        {
            action = ISUP_PASS_ON_MSG;
        }
    }
    else /* TYPE_A EXCHANGE (OR) END NODE */
    {
        if ((compInfo[0] & 0x02 /*RELEASE_CALL_MASK*/) == 0x02)
        {
            /* Release the call */
            action = ISUP_RELEASE_CALL;
        }
        else if ((compInfo[0] & 0x04 /*NOTIFICATION_MASK*/) == 0x04)
        {
            /* Send Confusion msg */
            action = ISUP_SEND_CFN_MSG;
        }
        else if ((compInfo[0] & 0x08 /*Discard_mask*/) == 0x08)
        {
            /* Discard msg */
            action = ISUP_DISCARD_MSG;
        }
        else
        {
            /* Pass on */
            if (ISUP_CLASS_INFO(V_Class)->pass_on_flag != ITS_TRUE)
            {
                /* Check bit E */
                if ((compInfo[0] & 0x10 /*Passon not possible*/) == 0x00)
                {
                    action = ITS_SUCCESS;;
                }
                else
                {
                    action = ISUP_DISCARD_PARAM;
                }
            }
            else
            {
                action = ISUP_PASS_ON_MSG;
            }
        }
    }

    return action;


}

/****************************************************************************/
/*
 * the Variant Info. record
 */
ISUP_VariantInfo   ITU93_Info =
{
    {
        /* Bitwise table for msgs. supported in the variant. */
        TABLE_MSG_SUPPORTED_ROW0_ITU93,
        TABLE_MSG_SUPPORTED_ROW1_ITU93,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROW3_ITU93,
        TABLE_MSG_SUPPORTED_ROW4_ITU93,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROW7_ITU93
    },
    {
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T1.  15-60 s.             */
        { ISUP_TMR_HNDL_STACK, 180 },  /* Timer T2.  3 mins.              */
        { ISUP_TMR_HNDL_STACK, 120 },  /* Timer T3.  2 mins.              */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T4.  5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T5.  5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T6.  per Q.118            */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer T7.  20-30 s.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T8.  10-15 s.             */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T9.  per Q.118            */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T10. 4-6 s.               */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer T11. 15-20 s.             */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T12. 15-60 s.             */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T13. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T14. 15-60 s.             */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T15. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T16. 15-60 s.             */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T17. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T18. 15-60 s.             */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T19. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T20. 15-60 s.             */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T21. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T22. 15-60 s.             */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T23. 5-15 mins.           */
        { ISUP_TMR_HNDL_STACK, 1   },  /* Timer T24. < 2 s.               */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T25. 1-10 s.              */
        { ISUP_TMR_HNDL_STACK, 120 },  /* Timer T26. 1-3 mins.            */
        { ISUP_TMR_HNDL_STACK, 240 },  /* Timer T27. 4 mins.              */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T28. 10 s.                */
        { ISUP_TMR_HNDL_STACK, 1   },  /* Timer T29. 300-600 ms. (FIXME)  */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T30. 5-10 s.              */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T31. > 6 mins.            */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T32. 3-5 s.               */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T33. 12-15 s.             */
        { ISUP_TMR_HNDL_STACK, 3   },  /* Timer T34. 2-4 s.               */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer T35. 15-20 s.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T36. 10-15 s.             */
        { ISUP_TMR_HNDL_STACK, 3   },  /* Timer T37. 2-4 s.               */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T38. per Q.118            */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T39. per Q.730            */
    },                                                                         
    {
        NULL /* Array of msg. descriptors : updated within ClassInitialize() */
    },
    NULL,   /* Hash Table for message procs. : Table ptr. updated after init.*/
    NULL,   /* Hash Table for timeout procs. : Table ptr. updated after init.*/
    1,      /* First CIC in Ckgp. */ 
    ISUP_ITU_MAX_CICS_IN_GP,     /* Number of CICs in Circuit Group */ 
    0xFFU,  /* supportMsgCompInfo */
    0x00U,  /* supportParamCompInfo */
    0x01U,   /* exchangeType */
    ITS_FALSE /* pass on flag */   
};

/*
 * the class record
 */
ITSSS7DLLAPI ITU93_VARIANT_ClassRec isupITU93_ClassRec =
{
    /* core part */
    {
        NULL,                           /* superclass is CORE */
        sizeof(ISUP_VariantInfo),       /* sizeof instance  ??? */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial refCount */
        ITU93_VARIANT_CLASS_NAME,       /* class name */
        ClassInitialize,                /* class initialize ??? inherit */
        ClassDestroy,                   /* class destroy ??? inherit */
        ITU93_ClassPartInitialize,      /* class initialize part */
        ITU93_ClassPartDestroy,         /* class destroy part */
        NULL,                           /* instantiate */
        NULL,                           /* destroy */                         
        ITS_INST_CLONE_INHERIT,         /* inherit clone */ 
        ITS_INST_PRINT_INHERIT,         /* inherit print */ 
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */ 
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */ 
        ITS_INST_HASH_INHERIT,          /* inherit hash */ 
        NULL                            /* no extension of interest */
    },
    /* VARIANT part */
    {
        &ITU93_Info,                    /* info at the base class */
        ITU93_DecodeMsg,                /* decode msg */
        ITU93_EncodeMsg,                /* encode msg */ 
        ITU93_ComputeMsize,             /* calculate size of fixed IE */ 
        ITU93_HandleUnrecMsg,           /* find action for unrec msgs */
        ITU93_GetMsgProc,               /* get msg proc. from Hash Table */
        ITU93_GetTimeoutProc,           /* get timeout proc. from Hash Table */

        /* Private functions for ClassInit: Users stay out */

        ITU93_InitMsgProcs,             /* Init Hash Table for msg procs. */
        ITU93_InitTimeoutProcs,         /* Init Hash Table for timeout procs. */
        ITU93_SetMsgProc,               /* set msg proc. from Hash Table */
        ITU93_SetTimeoutProc,           /* set timeout proc. from Hash Table */
        ITU93_HandleUnrecParamProc      /* Unrecognized Parameter Proc */
    }
};

ITSSS7DLLAPI ITS_Class isupITU93_Class = (ITS_Class)&isupITU93_ClassRec;            
