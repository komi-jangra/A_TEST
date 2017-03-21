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
 *  ID: $Id: AppTransports.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
 *
 ****************************************************************************
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
 * LOG: Revision 1.1  2004/02/12 13:46:55  aganguly
 * LOG: Initial version of CDMA test application on SCCP-CO.
 * LOG:
 * 
 * 
 * LOG:
 ****************************************************************************/

#include <iostream>

#include <its++.h>
#include <sccp++.h>
#include <engine++.h>
#include <its_service.h>
#include <its_iniparse.h>

#include <App.h>
#include <AppDbc.h>
#include <AppTrace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#define NUM_WORKER_POOL_THREADS 2

extern void
ActivateWorkerPoolThreads();

extern void
InitiateSCCPTransaction();

extern "C"
{
/*****************************************************************************
 *  Purpose:
 *      An Engine Callback to perform App-Specific initialization duties. For
 *      example : Connect to a Database etc.
 *
 *  Input Parameters:
 *      argc - arg count, argv - arg vector.
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
void
AppPreFunc() //OK
{
    cout << " App_PreFunc " << endl;
    APP_TRACE_DEBUG(("PRE-FUNC"));

    cout << "How this application going to work?" << endl;

    cout << "1.Initiator" << endl;

    cout << "2.Responder" << endl;

    cout << "Enter Your Option : ";

    int choice;

    cin >> choice; 

    if (choice == 1) 
    {
        InitiateSCCPTransaction();
    }
}

/*****************************************************************************
 *  Purpose:
 *      This is a Callback to get all SCCP messages.
 *
 *  Input Parameters:
 *      its::ThreadPoolThread *thr, its::Event& event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE.
 ****************************************************************************/

int
ReceiverMsgHandler(its::ThreadPoolThread *thr, its::Event& event)
{
    APP_TRACE_DEBUG(("ReceiverMsgHandler::Received  Message\n"));

     ProcessSCCPMsg(thr, event);
    return ITS_TRUE;
}

/*****************************************************************************
 *  Purpose:
 *      An engine callback triggered when an event occurs from third party source.
 *      It is invoked after Get/Peek succeeds. The received event is passed to this callback.
 *      If it doesn't return ITS_SUCCESS, the event is not dispatched further, the dispatcher 
 *          will return to the top of the dispatch loop skipping bottom level dispatch functions.       
 *
 *  Input Parameters:
 *      its::ThreadPoolThread thr, its::Event evt.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Success or Failure.
 ****************************************************************************/
int
BorderTransPostNext(its::ThreadPoolThread *thr, its::Event &evt)
{
    cout << " Border Transport Post Next " << endl;
    for (int i = 0; i < evt.GetLength(); i++)
    {
         printf("%02x ", evt.GetData()[i]);
    }
    cout << endl;

    return (ITS_SUCCESS);

}

/*****************************************************************************
 *  Purpose:
 *      This function decides whether to continue or terminate 
 *          the loop for next event at the receiver thread. Its invoked 
 *          if either GetNextEvent() or PeekNextEvent() failed.
 *          The int err passed to this is the return
 *          value of Get/Peek function invoked. If it returns False indicates
 *          that the receiver loop for events needs to be terminated.
 *
 *  Input Parameters:
 *      its::ThreadPoolThread thr, int err.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Boolean true or false.
 ****************************************************************************/
int
ReceiverNextEventFailed(its::ThreadPoolThread *thr, int err)
{
    engine::Worker *work = reinterpret_cast<engine::Worker *>(thr);
    return (ITS_SUCCESS);
}
}
