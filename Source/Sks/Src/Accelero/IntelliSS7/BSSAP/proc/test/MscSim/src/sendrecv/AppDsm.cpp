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
 *  ID: $Id: AppDsm.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.1  2005/09/28 05:57:02  adutta
 * LOG: Remodeled for MSC
 * LOG:
 * LOG: Revision 1.2  2005/02/11 10:21:10  csireesh
 * LOG: Committing after sanitizing Sample App (send-recv) for SCCP-CO: yet to take care of Codec
 * LOG:
 * LOG: Revision 1.1  2004/02/12 13:46:55  aganguly
 * LOG: Initial version of CDMA test application on SCCP-CO.
 * LOG:
 ****************************************************************************/

#include<stdio.h>
#include <App.h>
#include <AppDsm.h>
#include <AppTrace.h>

/*.implementation:extern
 *******************************************************************************
 *  Purpose:
 *      The Function is used to save the SCCP Connection information. First it 
 *  checks if the record for the given key is available in the DSM. If yes it 
 *  updates the information else  it allocates memory for the DsmInfo and stores
 *  in the DSM.
 *
 *  Input Parameters:
 *      info   - This is the information to be stored in the DSM.
 *      key    - This is the SCCP Conref.(Connection Reference-id)
 *      keylen - This is the length of the key.Size of Key conref is ITS_USHORT.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns ITS_SUCCESS if the information is successfuly stored in the DSM.
 ******************************************************************************/
int SaveContext(DsmInfo* info, ITS_OCTET *key, ITS_USHORT keylen)
{
    bool ret = !ITS_SUCCESS;
    int error;

    if (DSM_Commit(APP_FT_GROUP_ID, APP_FT_TABLE_ID, 
                       key, keylen, (void*)info) == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("SaveContext::DSM_Commit successful "));
        ret = ITS_SUCCESS;
    } 
    else
    {
        APP_TRACE_ERROR(("SaveContext::DSM_Commit failed "));
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The function is used to retrieve the SCCP Connection information. First 
 *  it checks if the record for the given key is available in the DSM. If yes 
 *  it gets the Conref information and returns ITS_SUCCESS. 
 *
 *  Input Parameters:
 *      key    - This is the SCCP Conref.(Connection Reference Id)
 *      keylen - This is the length of the key. Now the key is the Conref which
 *               has the size of ITS_USHORT.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      info   - This object to be filled from the DSM. 
 *
 *  Return Value:
 *      Returns ITS_SUCCESS if the information retrieved from the DSM .
 ****************************************************************************/
int RetrieveContext(DsmInfo **info, ITS_OCTET *key, ITS_USHORT keylen)
{
    bool ret = !ITS_SUCCESS;
    int error;
    void *dsm_ptr = NULL;

    do
    {
        *info = (DsmInfo*)
                DSM_Find(APP_FT_GROUP_ID, APP_FT_TABLE_ID, key, keylen, &error);

        if (error == ITS_EINUSE)
        {
            TIMERS_USleep(200);
        }
    }
    while (error == ITS_EINUSE);

    if (*info != NULL)
    {
        ret = ITS_SUCCESS;
    }
    else
    {
        APP_TRACE_ERROR(("RetrieveContext::DSM_UnlockRow failed "));
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      The function is used to delete the  SCCP Connection information. First 
 *  it checks if the record for the given key is available in the DSM. If yes 
 *  it deletes the connection information and returns ITS_SUCCESS.
 *
 *  Input Parameters:
 *      key    - This is the SCCP Conref (Connection Ref id) for which the 
 *               context is to be deleted.
 *      keylen - This is the length of the key. The key is the Conref id 
 *               of size ITS_USHORT.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns ITS_SUCCESS if the information deleted from the DSM .
 ****************************************************************************/
int DeleteContext(ITS_OCTET *key, ITS_USHORT keylen)
{
    bool ret = !ITS_SUCCESS;
    int error;
    void *dsm_ptr = NULL;
    DsmInfo* tmp = NULL;

    do
    {
        dsm_ptr = DSM_Find(APP_FT_GROUP_ID, APP_FT_TABLE_ID, key, keylen, &error);

        if (error == ITS_EINUSE)
        {
            TIMERS_USleep(200);
        }
    }
    while (error == ITS_EINUSE);

    if (!dsm_ptr)
    {
       return ITS_ENOTFOUND;
    }

    tmp = (DsmInfo*)dsm_ptr;
    if (tmp->cdpa)
    {
        delete tmp->cdpa;
        tmp->cdpa = NULL;
    }

    if (tmp->cgpa)
    {
        delete tmp->cgpa;
        tmp->cgpa = NULL;
    }

    ret = DSM_Free(APP_FT_GROUP_ID, APP_FT_TABLE_ID, key, keylen, dsm_ptr);

    if (ret == ITS_SUCCESS)
    {
        APP_TRACE_ERROR(("DeleteContext:: is Successful\n"));
        dsm_ptr = NULL;
    }

    return ret;
}
