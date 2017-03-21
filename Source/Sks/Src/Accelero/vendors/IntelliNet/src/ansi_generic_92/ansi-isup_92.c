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
 *  ID: $Id: ansi-isup_92.c,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:08  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:56  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1.38.1  2004/12/06 13:34:50  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 7.3.2.1  2003/05/07 10:38:00  ssingh
 * LOG: Latest Changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.3  2003/05/02 11:20:40  sjaddu
 * LOG: Bug fix in ansi 92 compute size function.
 * LOG:
 * LOG: Revision 8.2  2003/04/03 15:24:34  sjaddu
 * LOG: ISUP DSM reorganization.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.3  2003/01/31 13:06:03  ssingh
 * LOG: Getting key for messageproc/timerproc is changed; Macro used.
 * LOG:
 * LOG: Revision 7.2  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/08/16 20:00:03  ssingh
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.7  2002/07/06 20:06:42  hbalimid
 * LOG: Fixed all warnings.
 * LOG:
 * LOG: Revision 1.1.2.6  2002/07/05 22:00:52  hbalimid
 * LOG: Default behavour of timers, handled by STACK.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/07/04 23:28:48  hbalimid
 * LOG: Missing Base class inheritance completed.
 * LOG: Missing mandatory parameters added for computeMsize.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/03 16:41:16  hbalimid
 * LOG: Modified according to ANSI92.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/02 22:53:22  hbalimid
 * LOG: Removed FAC and OLM. Not in ANSI92.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/02 20:04:23  hbalimid
 * LOG: FAC removed from MsgProc Table.
 * LOG: This is according to ISUP ANSI92 specifications.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/01 20:17:50  hbalimid
 * LOG: Baseline for ISUP ANSI GENERIC 92.
 * LOG:
 *
 *****************************************************************************/

#undef CCITT
#undef ANSI
#define ANSI 

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <its.h>
#include <its_hash.h>
#include <isup_variants.h>
#include <ansi/isup_92.h>
#include <isup_sn.h>

/*****************************************************************************
 *
 * ISUP ANSI 92 Variant Class
 *
 ****************************************************************************/
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ANSI92 class record.
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
    int msg = 0;

    ITS_CLASS_SUPERCLASS(objClass) = itsCORE_Class;

    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[0] = NULL;
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[1] = &ISUP_IAM_Desc;     /* 0x01 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[2] = NULL;               /* 0x02 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[3] = &ISUP_INR_Desc;     /* 0x03 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[4] = &ISUP_INF_Desc;     /* 0x04 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[5] = &ISUP_COT_Desc;     /* 0x05 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[6] = &ISUP_ACM_Desc;     /* 0x06 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[7] = NULL;               /* 0x07 */
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
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[31] = NULL;               /* 0x1F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[32] = NULL;               /* 0x20 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[33] = NULL;               /* 0x21 */
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
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[45] = NULL;               /* 0x2D */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[46] = &ISUP_UCIC_Desc;    /* 0x2E */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[47] = &ISUP_CFN_Desc;     /* 0x2F */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[48] = NULL;               /* 0x30 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[49] = NULL;               /* 0x31 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[50] = NULL;               /* 0x32 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[51] = NULL;               /* 0x33 */

    /* No msg. codes from 52 through 232 for ANSI */
    for (msg = 52; msg < 233; msg++)
    {
        ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[msg] = NULL;    /* 0x34
                                                                       through
                                                                       0xE8 */
    }
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[233] = &ISUP_CRA_Desc;    /* 0xE9 */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[234] = &ISUP_CRM_Desc;    /* 0xEA */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[235] = &ISUP_CVR_Desc;    /* 0xEB */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[236] = &ISUP_CVT_Desc;    /* 0xEC */
    ISUP_VI_MSG_DESC(ISUP_CLASS_INFO(objClass))[237] = &ISUP_EXM_Desc;    /* 0xED */

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ANSI92 class record.
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
 *      Initialize the ANSI92 class part record.
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
ANSI92_ClassPartInitialize(ITS_Class classRec)
{
    ISUP_DEBUG(("Executing: ANSI92_ClassPartInitialize for %s\n",
                ITS_CLASS_CLASSNAME(classRec)));

    if (ISUP_CLASS_INFO(classRec) == ISUP_INFO_INHERIT)
    {
        ISUP_DEBUG(("Deriving ClassInfo. from BaseClass\n"));
        ISUP_CLASS_INFO(classRec) =
            ISUP_CLASS_INFO(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Class %s Registered Own Class Info\n",
                     ITS_CLASS_CLASSNAME(classRec)));
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
            ISUP_DEBUG(("Successfully Initialized TimeoutProc. HashTable\n"));
        }
        else
        {
            ISUP_DEBUG(("TimeoutProc. HashTable Init fail: exiting.\n"));
            return ITS_EINITFAIL;
        }
    }

    if (ISUP_GET_MSG_PROC(classRec) == ISUP_GET_MSG_PROC_INHERIT)
    {
        ISUP_DEBUG(("Deriving GetMsgProc func. from BaseClass\n"));
        ISUP_GET_MSG_PROC(classRec) =
            ISUP_GET_MSG_PROC(ITS_CLASS_SUPERCLASS(classRec));
    }
    else
    {
        ISUP_DEBUG(("Variant registered Own GetMsgProc. Handler function\n"));
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

    ISUP_DEBUG(("\nANSI92_ClassPartInitialize()::"
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
ANSI92_ClassPartDestroy(ITS_Class classRec)
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
ITSSS7DLLAPI int
ANSI92_SetTimeoutProc(ITS_Class V_Class, HASH_Table TimeoutProcTable,
                     ITS_UINT tmr, ITS_ISUP_STATE state, 
                     __ISUP_TimeoutHandlerProc func)
{
    ITS_USHORT key = 0;
    
    key = (ITS_USHORT) ISUP_TMR_PROC_KEY(state, tmr);

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
ITSSS7DLLAPI int
ANSI92_SetMsgProc(ITS_Class V_Class, HASH_Table MsgProcTable,
                 ITS_OCTET msg, ITS_ISUP_STATE state,
                 __ISUP_MsgHandlerProc func)
{
    ITS_USHORT key = 0;

    key = (ITS_USHORT) ISUP_MSG_PROC_KEY(state, msg);

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
ITSSS7DLLAPI int
ANSI92_InitTimeoutProcs(ITS_Class V_Class)
{
    ITS_USHORT state = 0;
    ITS_UINT tmr = 0;
    ITS_USHORT key = 0;
    __ISUP_TimeoutHandlerProc func = NULL;
    ISUP_VariantInfo* var_info = NULL;

    ISUP_DEBUG(("Executing: ANSI92_InitTimeoutProc function\n"));

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
            func = __ISUP_GetTimeoutHandler_ANSI92(tmr, (ITS_ISUP_STATE)state);

            if (ANSI92_SetTimeoutProc(V_Class, var_info->ISUP_TimeOutProcedures,
                                         tmr, (ITS_ISUP_STATE)state, func)
                                         != ITS_SUCCESS)
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
ITSSS7DLLAPI int
ANSI92_InitMsgProcs(ITS_Class V_Class)
{
    ITS_USHORT state = 0;
    ITS_USHORT msg = 0;
    ITS_USHORT key = 0;
    __ISUP_MsgHandlerProc func = NULL;
    ISUP_VariantInfo *var_info = NULL;

    ISUP_DEBUG(("Executing: ANSI92_InitMsgProc function\n"));

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
            func = __ISUP_GetMsgHandler_ANSI92((ITS_OCTET)msg,
                      (ITS_ISUP_STATE)state);

            if (ANSI92_SetMsgProc(V_Class, var_info->ISUP_MsgProcedures,
                                     (ITS_OCTET)msg, (ITS_ISUP_STATE)state,
                                     func) != ITS_SUCCESS)
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
ITSSS7DLLAPI __ISUP_MsgHandlerProc
ANSI92_GetMsgProc(ITS_Class V_Class, ITS_OCTET msg, ITS_ISUP_STATE state)
{
     __ISUP_MsgHandlerProc func = NULL;
     HASH_Table msgProcs = NULL;
     ITS_USHORT key = 0;

     ISUP_DEBUG(("Executing: ANSI92_GetMsgProc:mtype %x, state %x\n",
                 msg, state));
     
     if ((msgProcs = (ISUP_CLASS_INFO(V_Class)->ISUP_MsgProcedures)) == NULL)
     {
         ISUP_DEBUG(("ANSI92_GetMsgProc: HASH_Table access error\n"));
     
         return (__ISUP_MsgHandlerProc)NULL;
     }
     else
     {
         key = (ITS_USHORT) ISUP_MSG_PROC_KEY(state, msg);

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
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
ANSI92_GetTimeoutProc(ITS_Class V_Class, ITS_UINT Timer, ITS_ISUP_STATE state)
{
     __ISUP_TimeoutHandlerProc func = NULL;
     HASH_Table timeoutProcs = NULL;
     ITS_USHORT key = 0;

     ISUP_DEBUG(("Executing: ANSI92_GetTimeoutProc. timer %x, state %x\n",
                 Timer, state));

     if ((timeoutProcs = (ISUP_CLASS_INFO(V_Class)->ISUP_TimeOutProcedures))
                                                                    == NULL)
     {
         ISUP_DEBUG(("ANSI92_GetTimeoutProc: HASH_Table access error\n"));
     
         return (__ISUP_TimeoutHandlerProc)NULL;
     }
     else
     {
         key = (ITS_USHORT) ISUP_TMR_PROC_KEY(state, Timer);

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
 *      a particular message received within the stack.  For other ANSI variants
 *      this method will be internally called if the particular variant inherits
 *      this method from the ANSI92 genre.
 *
 *  See Also:
 ****************************************************************************/
ITSSS7DLLAPI int
ANSI92_DecodeMsg(ITS_Class V_Class, ITS_EVENT event, ITS_OCTET o1, ITS_OCTET o2,
                ITS_ISUP_IE* ie, int* count , ITS_HDR* hdr)
{
     ISUP_DEBUG(("Executing: ANSI92_Decode\n"));

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
 *      a particular message .For other ANSI variants this method will be 
 *      internally called if the particular variant inherit this method from 
 *      the ANSI92 genre.
 *
 *  See Also:
 ****************************************************************************/
ITSSS7DLLAPI int
ANSI92_EncodeMsg(ITS_Class V_Class, ITS_ISUP_IE* ie, int i, 
                ITS_OCTET o1, ITS_OCTET o2,
                ITS_HDR* hdr, ITS_EVENT* event)
{
     ISUP_DEBUG(("Executing: ANSI92_Encode\n"));

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
ITSSS7DLLAPI ITS_UINT
ANSI92_ComputeMsize(ITS_Class V_Class, ITS_OCTET which)
{
    ISUP_DEBUG(("Executing: ANSI92_ComputeMsize. arg %x\n", which));

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

    case ISUP_PRM_CKT_VALIDATION_RESP:
        return sizeof(ISUP_CIRCUIT_VALIDATION_RESPONSE);

    case ISUP_PRM_CKT_GRP_CHARACTERISTIC:
        return sizeof(ISUP_CIRCUIT_GROUP_CHARACTERISTIC);

    default:
        return (0);

    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function defines a method to handle a message unrecognized in 
 *      ANSI92.
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
 *      a particular message not supported in ANSI92. For other ANSI variants 
 *      this method will be internally called if the particular variant
 *      inherits this method from the ANSI92 genre.
 *
 *  See Also:
 ****************************************************************************/
ITSSS7DLLAPI ITS_OCTET
ANSI92_HandleUnrecMsg(ITS_Class V_Class, ITS_EVENT *event)
{
    int eventDataIndex = sizeof(MTP3_HEADER) + 3; /* point to ptr to opt par */
    ITS_BOOLEAN found = ITS_FALSE;
    ITS_OCTET action = 0; /* MLM: FIXME: This wants initializing to sane val */
     
    ISUP_DEBUG(("Executing: ANSI92_HandleUnrecMsgProc\n"));

    if (!ISUP_CLASS_INFO(V_Class)->ISUP_supportMsgCompInfo)
    {
        action = DISCARD_AND_SEND_CONFUSION;
    }
    else
    {
        if (event == NULL)
        {
            return DISCARD_AND_SEND_CONFUSION;
        }

        if (event->data[eventDataIndex] != 1 )
        {
             /* cannot do anything with the message */
             action = DISCARD_AND_SEND_CONFUSION;
        }
        else
        {
             eventDataIndex++;

             while (!found && (eventDataIndex <= event->len))       
             {
                 if (event->data[eventDataIndex] == MCIP)
                 {
                      found = ITS_TRUE;
                      action = event->data[eventDataIndex + 2] ;
                 }
                 eventDataIndex += event->data[eventDataIndex + 1];
             }
         } 
    }

    return action;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function defines a method to handle an Unrecognized Param in
 *      ANSI92.
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
 *      a particular message not supported in ANSI92. For other ANSI variants
 *      this method will be internally called if the particular variant
 *      inherits this method from the ANSI92 genre.
 *
 *  See Also:
 ****************************************************************************/
ITSSS7DLLAPI ITS_OCTET
ANSI92_HandleUnrecParamProc(ITS_Class V_Class,ITS_OCTET mType,ITS_OCTET *compInfo)
{
    ITS_OCTET action = 0;

    /* To be Implemented */

    return action;
}


/****************************************************************************/
/*
** the Variant Info. record
*/
ITSSS7DLLAPI ISUP_VariantInfo   ANSI92_Info =
{
    {
        /* Bitwise table for msgs. supported in the variant. */
        TABLE_MSG_SUPPORTED_ROW0_ANSI92,
        TABLE_MSG_SUPPORTED_ROW1_ANSI92,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROW3_ANSI92,
        TABLE_MSG_SUPPORTED_ROW4_ANSI92,
        TABLE_MSG_SUPPORTED_ROW5_ANSI92,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,   /* Row 10 */
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,   /* Row 15 */
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,   /* Row 20 */
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,   /* Row 25 */
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROW29_ANSI92,
    },
    {
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T1.  4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */ 
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T5.  1 min.               */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T6.  10-32 s.             */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer T7.  20-30 s.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T8.  10-15 s.             */
        { ISUP_TMR_HNDL_STACK, 180 },  /* Timer T9.  2-4 mins.            */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */ 
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer T11. 15-20 s.             */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T12. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T13. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T14. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T15. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T16. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T17. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T18. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T19. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T20. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T21. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T22. 4-15 s.              */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer T23. 1 min.               */
        { ISUP_TMR_HNDL_STACK, 1   },  /* Timer T24. < 2 s.               */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T25. 1-10 s.              */
        { ISUP_TMR_HNDL_STACK, 120 },  /* Timer T26. 1-3 mins.            */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer T27. > 3 mins.            */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer T28. 10 s.                */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */ 
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */ 
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer T31. > 6 mins.            */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer T32. 3-5 s.               */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T33. 12-15 s.             */
        { ISUP_TMR_HNDL_STACK, 15  },  /* Timer T34. 10-15 s.             */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */ 
        { ISUP_TMR_HNDL_STACK, 3   },  /* Timer T36. 2-4 s.               */
        { ISUP_TMR_HNDL_STACK, 30  },  /* Timer T37. 30 s.                */
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */ 
        { ISUP_TMR_HNDL_STACK, 0   },  /* Not Specified for U.S networks. */ 
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer TACCr. 5 s.               */
        { ISUP_TMR_HNDL_STACK, 2   },  /* Timer TCCR. 2 s.                */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer TCCRr. 20 s.              */
        { ISUP_TMR_HNDL_STACK, 5   },  /* Timer TCGB. 5 s.                */
        { ISUP_TMR_HNDL_STACK, 20  },  /* Timer TCRA. 20 s.               */
        { ISUP_TMR_HNDL_STACK, 3   },  /* Timer TCRM. 3-4 s.              */
        { ISUP_TMR_HNDL_STACK, 10  },  /* Timer TCVT. 10 s.               */
        { ISUP_TMR_HNDL_STACK, 600 },  /* Timer TEXMd. network dependent  */
        { ISUP_TMR_HNDL_STACK, 50  },  /* Timer TGRS. 5 s.                */
        { ISUP_TMR_HNDL_STACK, 300 },  /* Timer THGA. 0-5 min.            */
        { ISUP_TMR_HNDL_STACK, 120 },  /* Timer TSCGA. 0-2 min.           */
        { ISUP_TMR_HNDL_STACK, 60  },  /* Timer TSCGAd. 5-120 s.          */
    },                                                                         
    {
        NULL /* Array of msg. descriptors : updated within ClassInitialize() */
    },
    NULL,   /* Hash Table for message procs. : Table ptr. updated after init.*/
    NULL,   /* Hash Table for timeout procs. : Table ptr. updated after init.*/
    0,      /* First CIC in Ckgp. */ 
    ISUP_ANSI_MAX_CICS_IN_GP,     /* Number of CICs in Circuit Group */ 
    0x00U,  /* supportMsgCompInfo */
    0x00U,  /* supportParamCompInfo */
    0x01U   /* exchangeType */
};

/*
** the class record
*/
ITSSS7DLLAPI ANSI92_VARIANT_ClassRec isupANSI92_ClassRec =
{
    /* core part */
    {
        NULL,                           /* superclass is CORE */
        sizeof(ISUP_VariantInfo),       /* sizeof instance  ??? */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial refCount */
        ANSI92_VARIANT_CLASS_NAME,       /* class name */
        ClassInitialize,                /* class initialize ??? inherit */
        ClassDestroy,                   /* class destroy ??? inherit */
        ANSI92_ClassPartInitialize,      /* class initialize part */
        ANSI92_ClassPartDestroy,         /* class destroy part */
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
        &ANSI92_Info,                    /* info at the base class */
        ANSI92_DecodeMsg,                /* decode msg */
        ANSI92_EncodeMsg,                /* encode msg */
        ANSI92_ComputeMsize,             /* calculate size of fixed IE */
        ANSI92_HandleUnrecMsg,           /* find action for unrec msgs */
        ANSI92_GetMsgProc,               /* get msg proc. from Hash Table */
        ANSI92_GetTimeoutProc,           /* get timeout proc. from Hash Table */

        /* Private functions for ClassInit: Users stay out */

        ANSI92_InitMsgProcs,             /* Init Hash Table for msg procs. */
        ANSI92_InitTimeoutProcs,         /* Init Hash Table for timeout procs. */
        ANSI92_SetMsgProc,               /* set msg proc. from Hash Table */
        ANSI92_SetTimeoutProc,           /* set timeout proc. from Hash Table */
        ANSI92_HandleUnrecParamProc      /* Unrecognized Parameter Proc */
    }
};

ITSSS7DLLAPI ITS_Class isupANSI92_Class = (ITS_Class)&isupANSI92_ClassRec;            
