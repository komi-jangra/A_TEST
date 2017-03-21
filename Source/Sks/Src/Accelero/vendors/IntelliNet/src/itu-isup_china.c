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
 *  ID: $Id: itu-isup_china.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:33  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:08  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:53:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:18:58  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3.2.1  2002/03/22 16:21:27  ssharma
 * LOG: Change assert to ITS_C_ASSERT
 * LOG:
 * LOG: Revision 5.3  2002/02/12 23:29:04  mmiers
 * LOG: ISUP parser in place.
 * LOG:
 * LOG: Revision 5.2  2002/02/08 21:48:16  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.1  2002/02/01 20:07:31  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/22 23:37:11  ssharma
 * LOG: New files for IntelliNet ISUP stack.
 * LOG:
 * LOG: 
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <its.h>

#undef ANSI
#undef CCITT
#if !defined(PRC)
#define CCITT
#endif

#include <isup_variants.h>
#include <itu/isup_china.h>
#include <isup_intern.h>

static ITS_BOOLEAN initialized = ITS_FALSE;

/*****************************************************************************
 *
 * ISUP CHINA Variant "Derived Class" ("Base Class": ITU93 Variant).
 *
 ****************************************************************************/

void
CHINA_TestFunc1(ITS_EVENT* ev, ITS_UINT u1, ITS_UINT u2, ITS_OCTET msg)
{
    printf("\n Executing: CHINA_TestFunc1");
}


void
CHINA_TestFunc2(ITS_EVENT* ev, ITS_UINT u1, ITS_UINT u2, ITS_OCTET msg)
{
    printf("\n Executing: CHINA_TestFunc2");
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the variant class-specific functionality.
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
 *      If the variant class does not have any specific handling of the 
 *      function, then it will use (inherit) the function definition in the
 *      generic variant class (ITU93). Note that this is because initialization 
 *      of the ITU93 class (base class) has been already done before calling
 *      this function. 
 *
 *  See Also:
 ****************************************************************************/
static int
CHINA_ClassPartInitialize(ITS_Class classRec)
{
    printf("\n Executing: CHINA_ClassPartInitialize");

    if (CHINA_InitMsgProcs(classRec) != ITS_SUCCESS)
    {
        return ITS_EINITFAIL;
    }

    if (CHINA_InitTimeoutProcs(classRec) != ITS_SUCCESS)
    {
        return ITS_EINITFAIL;
    }

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
CHINA_ClassPartDestroy(ITS_Class classRec)
{
    /*  Call HASH_DeleteTable for function pointers */
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to initialize the variant class-specific
 *      Timeout Handler function addresses.
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
 *      Within this function, ONLY those addresses need to be inserted in
 *      Hash Table, which are either new or need to overwrite function 
 *      addresses laid down by the base class. 
 *
 *  See Also:
 ****************************************************************************/
int
CHINA_InitTimeoutProcs(ITS_Class classRec)
{
    HASH_Table TimeoutProcTable = NULL;

    printf("\n Executing: CHINA_InitTimeoutProcs");

    if ((TimeoutProcTable = ISUP_CLASS_HASH_TIMEOUT_PROCS(classRec)) == NULL)
    {
        printf("\n TimeoutProcTable access error: exiting");
        return ITS_EINITFAIL;
    }

    /* Try to add new function pointer in the HashTable, if any */

    /* Try to modify existing pointers inherited from BaseClass, if any
     * needed */

    return ITS_SUCCESS;
}                                                                


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to initialize the variant class-specific
 *      Message Handler function addresses.
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
 *      Within this function, ONLY those addresses need to be inserted in
 *      Hash Table, which are either new or need to overwrite function 
 *      addresses laid down by the base class. 
 *
 *  See Also:
 ****************************************************************************/
int
CHINA_InitMsgProcs(ITS_Class classRec)
{
    HASH_Table MsgProcTable = NULL;

    printf("\n Executing: CHINA_InitMsgProcs");

    if ((MsgProcTable = ISUP_CLASS_HASH_MSG_PROCS(classRec)) == NULL)
    {
        printf("\n MsgProcTable access error: exiting");
        return ITS_EINITFAIL;
    }

    /* Try to add new function pointer */
#if 0
    if (CHINA_SetMsgProc(classRec, MsgProcTable, 0x01, 15, CHINA_TestFunc1)
                                                           != ITS_SUCCESS)
    {
        return ITS_EINITFAIL;
    }
#endif

    /* Try to modify existing new function pointer */
#if 0
    if (CHINA_SetMsgProc(classRec, MsgProcTable, 0x01, 0, CHINA_TestFunc2)
                                                           != ITS_SUCCESS)
    {
        return ITS_EINITFAIL;
    }
    else
    {
        printf("\n Overwriting existing ptr: mtype 1, state 0, new func. %x",
                                                          CHINA_TestFunc2);
    }
#endif
    return ITS_SUCCESS;
}                                                                

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the variant-specific processing of a particular
 *      message.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *      event - a pointer to ITS_EVENT structure
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
ITS_INT
CHINA_VARIANT_SpecificMsg(ITS_Class V_class, ITS_EVENT* event)
{
    printf((" Execute: VARIANT_SpecificMsg at CHINA Class:\n"));
    return 0;
}


/*
** the Variant Info. record
*/
ISUP_VariantInfo   CHINA_Info =
{
    {
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROWX_SET,
        TABLE_MSG_SUPPORTED_ROWX_CLEAR
    },
    {
        { ISUP_TMR_HNDL_APP,   10 },
        { ISUP_TMR_HNDL_STACK, 20 } 
    },
    {
        NULL                                                                   
    },
    NULL,   /* Hash Table for message procs. */
    NULL,   /* Hash Table for timeout procs. */
    1,      /* First CIC in Circuit Group */
    32,     /* Number of CICs in Circuit Group */
    0xFFU,  /* supportMsgCompInfo */
    0x00U,  /* supportParamCompInfo */
    0x01U   /* exchangeType */
};

/*
** the class record
*/
CHINA_VARIANT_ClassRec isupCHINA_ClassRec =
{
    /* core part */
    {
        (ITS_Class)&isupITU93_ClassRec,            /* superclass is ITU93 */
        sizeof(ISUP_VariantInfo),       /* sizeof instance  ??? */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial refCount */
        CHINA_VARIANT_CLASS_NAME,       /* class name */
        NULL,                           /* class initialize ??? inherit */
        NULL,                           /* class destroy ??? inherit */
        CHINA_ClassPartInitialize,      /* class initialize part */
        CHINA_ClassPartDestroy,         /* class destroy part */
        NULL,                           /* instantiate */
        NULL,                           /* destroy */                         
        NULL                            /* no extension of interest */
    },
    /* VARIANT part */
    {
        &CHINA_Info,                      /* info at the base class */
        ISUP_DECODE_MSG_INHERIT,          /* inherit from base ISUP VARIANT */
        ISUP_ENCODE_MSG_INHERIT,          /* inherit from base ISUP VARIANT */
        ISUP_COMPUTE_MSIZE_INHERIT,       /* inherit from base ISUP VARIANT */
        ISUP_HANDLE_UNREC_MSG_INHERIT,    /* inherit from base ISUP VARIANT */
        ISUP_GET_MSG_PROC_INHERIT,        /* inherit from base ISUP VARIANT */
        ISUP_GET_TIMEOUT_PROC_INHERIT,    /* inherit from base ISUP VARIANT */

        /* Private Functions for Class Init. : Users stay out */

        ISUP_INIT_MSG_PROCS_INHERIT,      /* inherit from base ISUP VARIANT */
        ISUP_INIT_TIMEOUT_PROCS_INHERIT,  /* inherit from base ISUP VARIANT */
        ISUP_SET_MSG_PROC_INHERIT,        /* inherit from base ISUP VARIANT */
        ISUP_SET_TIMEOUT_PROC_INHERIT     /* inherit from base ISUP VARIANT */
    },
    /* CHINA_VARIANT part */
    {
        CHINA_VARIANT_SpecificMsg   /* Variant Specific processing of msgs */
    }
};

ITS_Class isupCHINA_VARIANT_Class = (ITS_Class)&isupCHINA_ClassRec;            



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the CHINA Variant Class.
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
 *      As a part of this function, the class derives the generic functions
 *      of ITU93 genre and wherever required, overrides those with its own
 *      variant specific handler functions.
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
CHINAVAR_Initialize(CHINA_VARIANT_Class vclass)
{
     printf("\n Executing: CHINAVAR_Initialize");
     return ITS_InitializeClass((ITS_Class)vclass);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creates the CHINA Variant Class.
 *
 *  Input Parameters:
 *      classRec - the class record pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      A pointer to the Variant Class created.
 *                                                                             
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      The Class creation takes place in 2 steps:
 *      1. The typical functions of the Variant are loaded onto the 
 *         Class Record first. This refers to those specific functions, which
 *         are not listed in the ITU93 genre.
 *      2. Then the functions listed in the ITU93 base are loaded onto the
 *         Variant Record, taking care to override the base function pointers 
 *         by those of the Variant's own, wherever required.
 *
 *  See Also:
 ****************************************************************************/
CHINA_VARIANT_Class
CHINA_CreateClass()
{
    if (initialized)
    {
        printf("\n CHINAVAR_Initialize already done: returning!!! \n");
        return &isupCHINA_ClassRec;
    }
                                                                             
    if (CHINAVAR_Initialize(&isupCHINA_ClassRec) == ITS_SUCCESS)
    {
        printf("\n CHINAVAR_Initialize SUCCESS !!! \n");
        initialized = ITS_TRUE;
        return &isupCHINA_ClassRec;
    }
    else
    {
        printf("\n CHINAVAR_Initialize FAIL: Exiting !!! \n");
        return (CHINA_VARIANT_Class)NULL;
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
 *
 *  Return Value:
 *      On success, returns ITS_SUCCESS
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function may be recursively called during initialization of the
 *      variant. For each msg-state combination which requires a variant 
 *      specific handling, this function is called to store the address of 
 *      the variant specific Message Handler function in the Hash Table.
 *
 *  See Also:
 ****************************************************************************/ 
int
CHINA_SetMsgProc(ITS_Class V_Class, HASH_Table MsgProcTable,
                 ITS_OCTET msgType, ITS_ISUP_STATE state,
                 __ISUP_MsgHandlerProc func)
{
    printf("\n CHINA_SetMsgProc: mtype %x, state %x, func %x\n",
                                                 msgType, state, func);

    return ISUP_SET_MSG_PROC(V_Class) ((ITS_Class)V_Class, MsgProcTable,
                                        msgType, state, func);
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
CHINA_SetTimeoutProc(ITS_Class V_Class, HASH_Table TimeoutProcTable,                                 ITS_UINT tmr, ITS_ISUP_STATE state,                                             __ISUP_TimeoutHandlerProc func)
{
    printf("\n CHINA_SetTimeoutProc:\n");

    return ISUP_SET_TIMEOUT_PROC(V_Class) ((ITS_Class)V_Class, TimeoutProcTable,                                            tmr, state, func);
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
 *
 *  Notes:
 *      This is the function to be used by a Vendor code writer for finding
 *      a particular message Handler function corresponding to the received
 *      message and current state pair.
 *
 *  See Also:
 ****************************************************************************/ 
__ISUP_MsgHandlerProc
CHINA_GetMsgProc(CHINA_VARIANT_Class V_Class, ITS_OCTET msg,                                     ITS_ISUP_STATE state)
{
    printf("\n CHINA_GetMsgProc:\n");

    return ISUP_GET_MSG_PROC(V_Class)((ITS_Class)V_Class, msg, state);
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
CHINA_GetTimeoutProc(CHINA_VARIANT_Class V_Class, ITS_UINT tmr,                                      ITS_ISUP_STATE state)
{
    printf("\n CHINA_GetTimeoutProc:\n");

    return ISUP_GET_TIMEOUT_PROC(V_Class)((ITS_Class)V_Class, tmr, state);
}                                                                    

