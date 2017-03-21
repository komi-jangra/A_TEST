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
 *  ID: $Id: isup_variants.c,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:06  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:02  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:58  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/31 13:03:39  ssingh
 * LOG: getting key for message proc and timer proc is changed; Macro used.
 * LOG:
 * LOG: Revision 7.2  2003/01/13 23:51:25  vnitin
 * LOG: Add Typecasting changes for Tandem Port
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/05/28 16:41:09  sjaddu
 * LOG: Added CNF Procedures.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/02/26 16:49:49  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.4  2002/02/13 22:26:52  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.3  2002/02/08 21:49:43  mmiers
 * LOG: Reorg is complete.
 * LOG:
 * LOG: Revision 5.2  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.1  2002/02/01 20:07:31  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/01/25 18:18:28  yranade
 * LOG: Include files based on family.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/22 23:37:11  ssharma
 * LOG: New files for IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:30  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/03 18:16:07  omayor
 * LOG: First draft to create ISUP variant hierachy.
 * LOG:
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#include <its.h>

#include <isup_cmn.h>
#include <isup_variants.h>

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to check is the ISUP variant support
 *      a given message.
 *
 *  Input Parameters:
 *      msgType - the message tag to be checked.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE  - if the message msgType is supported by the variant.
 *      ITS_FALSE - if the message is not supported by the variant.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_BOOLEAN
VAR_IsMsgSupported(ITS_Class V_Class, ITS_OCTET msgType)
{
    
    int row = 0;
    int index = 0;

    assert(V_Class != NULL);

    row = (int)msgType / 8; /* 8 bits in ITS_OCTET */
    index = msgType % 8;

    return (ISUP_CLASS_INFO(V_Class)->ISUP_MsgSupported[row] & ( 1 << index ));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to check if the variant supports the
 *      Message Compatibility Info Parameter.
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
 *      ITS_TRUE  - the Message Compatibility Info Parameter is supported.
 *      ITS_FALSE - the Message Compatibility Info Parameter is not supported.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_BOOLEAN
VAR_IsMsgCompInfoSupported(ITS_Class V_Class)
{
    assert(V_Class != NULL);

    return ISUP_CLASS_INFO(V_Class)->ISUP_supportMsgCompInfo;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to check if the variant supports the Parameter
 *      Compatibility Info Parameter.
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
 *      ITS_TRUE  - the Parameter Compatibility Info Parameter is supported.
 *      ITS_FALSE - the Parameter Compatibility Info Parameter is not.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_BOOLEAN
VAR_IsParamCompInfoSupported(ITS_Class V_Class)
{
    assert(V_Class != NULL);

    return ISUP_CLASS_INFO(V_Class)->ISUP_supportParamCompInfo;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return a pointer to a given message description
 *      data structure for the variant.
 *
 *  Input Parameters:
 *      msgType - the message tag for witch we want the description.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to ISUP_MSG_DESC data structure
 *      NULL - if the message is not supported by the variant.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ISUP_MSG_DESC*
VAR_GetMsgDescription(ITS_Class V_Class, ITS_OCTET msgType)
{
    assert(V_Class != NULL);

    return ISUP_CLASS_INFO(V_Class)->ISUP_MsgDescription[(int)msgType]; 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return a pointer to the array of timer data 
 *      for the variant.
 *
 *  Input Parameters:
 *      V_Class - Variant Class Record. 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the timer information for the variant. 
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ISUP_TMR_HNDL_INFO*
VAR_GetTimerInfo(ITS_Class V_Class)
{
    assert(V_Class != NULL);

    return ISUP_CLASS_INFO(V_Class)->ISUP_TimerData; 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return the number of CICs in a Circuit Group
 *      as specified by a particular variant.
 *
 *  Input Parameters:
 *      V_Class - ClassRecord for the variant.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Number of Cics in a Circuit Group (24 for ANSI/ 32 for ITU).
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_OCTET
VAR_GetNumCICs_Ckgp(ITS_Class V_Class)
{
    assert(V_Class != NULL);

    return ISUP_CLASS_INFO(V_Class)->CICsInCkgp; 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used return to the first CIC number in a Circuit Group
 *      as specified by a particular variant.
 *
 *  Input Parameters:
 *      V_Class - ClassRecord for the variant.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      1st Cic number in Circuit Group (Genearlly 1, rarely 0).
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_USHORT
VAR_GetFirstCIC_Ckgp(ITS_Class V_Class)
{
    assert(V_Class != NULL);

    return ISUP_CLASS_INFO(V_Class)->FirstCICInCkgp; 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return the number of CICs left in a
 *      Circuit Group in which the first used CIC is known.
 *
 *  Input Parameters:
 *      V_Class - ClassRecord for the variant.
 *      cic - CIC for which the group information is needed.
 *
 *  Input/Output Parameters:
 *      pointer to circuit groupId - cktGroup to which the start CIC belongs.
 *      pointer to number of CICs - number of CICs left in the group (including
 *                                  startCic.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      Ckgp-id as of now is for internal use: it always starts from 0.
 *      Index will start from 0: ie. 1st Cic in the Ckgp. will be always 0.
 *      startCic# in ckgp may be 0 or 1 depending on variant.
 *      If only the ckgpId is needed, the other two pointers should be passed 
 *      NULL.
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI void
VAR_GetCkgpFromCIC(ITS_Class V_Class, ITS_USHORT cic, 
            ITS_USHORT *cicIndex, ITS_USHORT *ckgpId, ITS_USHORT *numCics)
{
    /*
     * Note: Ckgp-id as of now is for internal use: it always starts from 0
     *       startCic# in ckgp may be 0 or 1 depending on variant
     *       cicIndex will always start for 0
     */

    ITS_USHORT startOffset = 0;
    ITS_USHORT CicsInCkgp = 0;
    ITS_USHORT logical = 0;

    assert (V_Class != NULL);

    startOffset = VAR_GetFirstCIC_Ckgp(V_Class);
    CicsInCkgp = VAR_GetNumCICs_Ckgp(V_Class);

    logical = (ITS_USHORT) (cic - startOffset); 

    if (ckgpId != NULL)
    {
        *ckgpId = (ITS_USHORT)(logical / CicsInCkgp);
    }
    
    if (cicIndex != NULL) 
    {
        *cicIndex = (ITS_USHORT)(logical % CicsInCkgp);
    }

    if (numCics != NULL)
    {
        *numCics = (ITS_USHORT)(CicsInCkgp - *cicIndex);
    }
    
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return a particular CIC given its index 
 *      within a Circuit Group.
 *
 *  Input Parameters:
 *      V_Class - ClassRecord for the variant.
 *      Ckgp - circuit group of which the CIC is a part 
 *      index - Index of the CIC within the group
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      CIC Number
 *
 *  Notes:
 *      Ckgp-id as of now is for internal use: it always starts from 0.
 *      Index will start from 0: ie. 1st Cic in the Ckgp. will be always 0.
 *      startCic# in ckgp may be 0 or 1 depending on variant.
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_USHORT
VAR_GetCICFromCkgp(ITS_Class V_Class, ITS_USHORT ckgp, ITS_OCTET CicIndex) 
{
    /*
     * Note: Ckgp-id as of now is for internal use: it always starts from 0
     *       startCic# in ckgp may be 0 or 1 depending on variant
     *       cicIndex will always start from 0
     */

    ITS_USHORT startOffset = 0;
    ITS_USHORT CicsInCkgp = 0;
    ITS_USHORT cic = 0;

    assert (V_Class != NULL);

    startOffset = VAR_GetFirstCIC_Ckgp(V_Class);
    CicsInCkgp = VAR_GetNumCICs_Ckgp(V_Class);

    cic = (ITS_USHORT)(ckgp * CicsInCkgp + CicIndex + startOffset);

    return cic;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to get the address of a particular Message
 *      Handler function in a given state for a particular variant.
 *
 *  Input Parameters:
 *      classRec - the variant class record pointer 
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
 *      a particular Message Handler function corresponding to the received
 *      timeout and current state pair.
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI __ISUP_MsgHandlerProc
VAR_GetMsgProc(ITS_Class V_Class, ITS_OCTET msg, ITS_ISUP_STATE state)
{
   __ISUP_MsgHandlerProc func = NULL;
   HASH_Table msgProcs = NULL;
   ITS_USHORT key = 0;

   assert(V_Class != NULL);

   if ((msgProcs = (ISUP_CLASS_INFO(V_Class)->ISUP_MsgProcedures)) == NULL)
   {
       return (__ISUP_MsgHandlerProc)NULL;
   }
   else
   {
       key = (ITS_USHORT) ISUP_MSG_PROC_KEY(state, msg);

       if (HASH_FindEntry(msgProcs, 0, key,
                                (ITS_POINTER*)(&func)) != ITS_SUCCESS)
       {
           return (__ISUP_MsgHandlerProc)NULL;
       }
       else
       {
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
SS7DLLAPI __ISUP_TimeoutHandlerProc
VAR_GetTimeoutProc(ITS_Class V_Class, ITS_UINT Timer, ITS_ISUP_STATE state)
{
   __ISUP_TimeoutHandlerProc func = NULL;
   HASH_Table timeoutProcs = NULL;
   ITS_USHORT key = 0;

   assert(V_Class != NULL);

   if ((timeoutProcs = (ISUP_CLASS_INFO(V_Class)->ISUP_TimeOutProcedures))
                                                                    == NULL)
   {
       return (__ISUP_TimeoutHandlerProc)NULL;
   }
   else
   {
       key = (ITS_USHORT) ISUP_TMR_PROC_KEY(state, Timer);

       if (HASH_FindEntry(timeoutProcs, 0, key,
                                (ITS_POINTER*)(&func)) != ITS_SUCCESS)
       {
           return (__ISUP_TimeoutHandlerProc)NULL;
       }                                                   
       else
       {
           return (__ISUP_TimeoutHandlerProc)func;
       }
   }
}
                                                              

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return a pointer to the message Decoding 
 *      function for a particular variant.
 *
 *  Input Parameters:
 *      ClassRecordPointer for the variant.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the DecodeFunction
 *      NULL - if not registered.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI __ISUP_DecodeMsgProc
VAR_DecodeMsg(ITS_Class V_Class) 
{
    assert(V_Class != NULL);

    return ISUP_DECODE_MSG(V_Class);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return a pointer to the message Encoding 
 *      function for a particular variant.
 *
 *  Input Parameters:
 *      ClassRecordPointer for the variant.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the EncodeFunction
 *      NULL - if not registered.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI __ISUP_EncodeMsgProc
VAR_EncodeMsg(ITS_Class V_Class)
{
    assert(V_Class != NULL);

    return ISUP_ENCODE_MSG(V_Class);
}
                                         


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return a pointer to the function which 
 *      calculates message size for a particular variant.
 *
 *  Input Parameters:
 *      ClassRecordPointer for the variant.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the function
 *      NULL - if not registered.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI __ISUP_ComputeMSizeProc
VAR_ComputeMsize(ITS_Class V_Class)
{
    assert(V_Class != NULL);

    return ISUP_COMPUTE_MSIZE(V_Class);
}
                                         


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return a pointer to the function for handling 
 *      unrecognized message for a particular variant.
 *
 *  Input Parameters:
 *      ClassRecordPointer for the variant.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the function
 *      NULL - if not registered.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI __ISUP_HandleUnrecMsgProc
VAR_HandleUnrecMsg(ITS_Class V_Class)
{
    assert(V_Class != NULL);

    return ISUP_HANDLE_UNREC_MSG(V_Class);
}
 

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to dump all the information in a variant record. 
 *
 *  Input Parameters:
 *      ClassRecordPointer for the variant.
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
SS7DLLAPI void
VAR_PrintRecord(ITS_Class V_Class)
{
    const char *tmr_id_str = NULL;
    const char *tmr_hndl_str = NULL;
    ISUP_TMR_HNDL_INFO  *tmr_info = NULL;
    int i = 0;

    assert (V_Class != NULL);

    printf("\n FIRST CIC IN CIRCUIT GROUP : %d \n",
                                     VAR_GetFirstCIC_Ckgp(V_Class));

    printf("\n NUMBER OF CICS IN CIRCUIT GROUP : %d \n",
                                     VAR_GetNumCICs_Ckgp(V_Class));

    printf("\n SUPPORT MESSAGE COMPATIBILITY INFORMATION : %d \n",
                    (ISUP_CLASS_INFO(V_Class))->ISUP_supportMsgCompInfo);

    printf("\n SUPPORT PARAMETER COMPATIBILITY INFORMATION : %d \n",
                    (ISUP_CLASS_INFO(V_Class))->ISUP_supportParamCompInfo);
    
    printf("\n EXCHANGE TYPE : %d \n",
                    (ISUP_CLASS_INFO(V_Class))->ISUP_exchangeType);

    printf("\n TIMER DATA : \n");

    for (i = 1; i < ITS_ISUP_TIMER_LAST; i++)
    {
        tmr_id_str = ISUP_TimerToString((ITS_OCTET)i);
        assert(tmr_id_str != NULL);

        tmr_info = VAR_GetTimerInfo(V_Class) + i - 1;
        
        tmr_hndl_str = ISUP_TimerHandlerToString(tmr_info->tmr_hndl_layer);
        assert(tmr_hndl_str != NULL);

        printf("\n \t %s \t %s \t %d \n", tmr_id_str, tmr_hndl_str, 
                            tmr_info->tmr_value);
    }

    printf("\n----- Variant Record Done -----\n");
} 
