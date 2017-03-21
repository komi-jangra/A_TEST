/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 9.1  2005/03/23 12:53:33  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:10  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.4.4.5  2005/02/22 11:01:29  sjaddu
 * LOG: Changed the desc of alarms according to doc,
 * LOG: This fixes bugs 1623, 1624, 1625, 1626.
 * LOG:
 * LOG: Revision 1.1.2.4.4.4  2005/01/10 06:03:28  ssingh
 * LOG: more commit on previous.
 * LOG:
 * LOG: Revision 1.1.2.4.4.3  2005/01/07 14:56:41  ssingh
 * LOG: Changed to enhance ACTIVE-BACKUP redundancy; tested for sigtran one.
 * LOG:
 * LOG: Revision 1.1.2.4.4.2  2004/12/20 12:33:54  mmanikandan
 * LOG: Support for windows compilation.
 * LOG:
 * LOG: Revision 1.1.2.4.4.1  2004/12/15 15:59:30  ssingh
 * LOG: Added ITS_RED_MODULE_SRC
 * LOG:
 * LOG: Revision 1.1.2.4  2004/11/18 11:28:46  sjaddu
 * LOG: configuration checks added.
 * LOG:
 * LOG: Revision 1.1.2.3  2004/02/12 13:46:34  sjaddu
 * LOG: Alarms added to redundancy feature.
 * LOG:
 * LOG: Revision 1.1.2.2  2004/01/30 06:21:14  sjaddu
 * LOG: Added notification event to app inc case of active
 * LOG: -active configuration.
 * LOG:
 * LOG: Revision 1.1.2.1  2004/01/27 13:42:07  sjaddu
 * LOG: Added files for active-backup redundancy.
 * LOG:                                                             *
 *                                                                          *
 ****************************************************************************/


#include <its_redundancy.h>
#include <its_dsm.h>
#include <string.h>
#include <its_app.h>
#include <its_route.h>
#include <isup_cmn.h>
#include <engine.h>
#include <its_alarm.h>

REDDLLAPI CALLBACK_Manager* ITS_RedundancyConfig_Callback = NULL;
REDDLLAPI CALLBACK_Manager  *ITS_RedundancyMgmtCallbacks = NULL;

ITS_USR_PART_STATE ITS_usrPartState = { ITS_STATE_PRIMARY };

static ROUTE_AppSelector    appSelectAll  = NULL;
static ROUTE_AppSelector    appSelectNode = NULL;

#define REDUNDANCY_ALARM_START   9001
#define REDUNDANCY_ALARM_END     9050 /* Change this value in case more */

REDDLLAPI void
REDUNDANCY_Alarm(int which, const char *file, const int line,
            char *fmt, ...);

ALARM_FORMAT_SUBSYS(REDUNDANCY, 9001,
                    "Redundancy feature intialize",
                    ALARM_LVL_INFO, "Node Initial configuration",
                    "HA/FT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(REDUNDANCY, 9002,
                    "Connection with Peer Node Lost",
                    ALARM_LVL_CRIT, "Node leave received",
                    "HA/FT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(REDUNDANCY, 9003,
                    "Connection with Peer Node resumed",
                    ALARM_LVL_INFO, "Join received",
                    "HA/FT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(REDUNDANCY, 9004,
                    "Change over from",
                    ALARM_LVL_INFO, "Change over",
                    "HA/FT", ITS_TRUE);

ALARM_FORMAT_SUBSYS(REDUNDANCY, 9005,
                    "State change request received:",
                    ALARM_LVL_CRIT, "request",
                    "HA/FT", ITS_TRUE);

static ALARM_Format *REDUNDANCY_Alarms[] =
{
    &ALARM_REDUNDANCY9001 ,
    &ALARM_REDUNDANCY9002 ,
    &ALARM_REDUNDANCY9003 ,
    &ALARM_REDUNDANCY9004 ,
    &ALARM_REDUNDANCY9005 
};

/* StartUp flag table in DSM; for bringup seqencing */
static ITS_INT REDUNDANCY_AllocNodeStartUpFlag(ITS_OCTET **status);
static ITS_INT REDUNDANCY_FindNodeStartUpFlag(ITS_OCTET **status);
static ITS_INT REDUNDANCY_ReleaseNodeStartUpFlag(ITS_OCTET *status);
static void REDUNDANCY_SendChangeEventToStack(ITS_OCTET changeType);


/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *        Returns the call back manager
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
 *          CALLBACK_Manager* or NULL
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
static CALLBACK_Manager*
GetRedundancyCallbackMgr()
{
    if (ITS_RedundancyConfig_Callback)
    {
        return ITS_RedundancyConfig_Callback;
    }
    return NULL;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *        Chnages the node state
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
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
static int 
SetNodeState(ITS_NODE_STATE state)
{
    ITS_usrPartState.state = state;
    return ITS_SUCCESS;
}
    
/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *        Returns the current node state
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
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
static ITS_NODE_STATE 
GetNodeState()
{
    return ITS_usrPartState.state;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *        Changes state from stand to active and inform the users
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
 *  See Also:
 *****************************************************************************/
static void
ChangeStateFromStandbyToActive()
{
    ITS_EVENT evt;

    ITS_EVENT_INIT(&evt, 2, 3);
    evt.data[0] = ITS_STATE_CHANGE_EVENT;
    evt.data[1] = ITS_STATE_PRIMARY;
    evt.data[2] = DSM_GetNodeId();

    /*send state change event to the mate & change own state also*/
    SetNodeState(ITS_STATE_PRIMARY);

    ITS_TRACE_CRITICAL(("StateChangeEvent:: Changing state Active \n"));

    /* Multicast the event guess why mtp3 ? */
    DSM_MulticastStackEventToFtGroupMembers(DSM_Mtp3FtGroupId,
                                            evt,
                                            ITS_GCS_EVENT_FROM_APPL,
                                            ITS_ENODESTINATION);

    /* Inform the local users also, I am assuming that the above
     * event is not freed yet*/
    if (!CALLBACK_IsListEmpty(ITS_RedundancyConfig_Callback))
    {
        CALLBACK_CallCallbackList(ITS_RedundancyConfig_Callback,
                              (void*)NULL,
                              (void*)&evt);
    }
    else
    {
        ITS_TRACE_WARNING(("Redundancy call back list is emtpy \n"));
    }

    REDUNDANCY_Alarm(9004, __FILE__, __LINE__,
                  " backup to active Node##%d",
                  DSM_GetNodeId());

    /* free the event we no longer require*/
    ITS_EVENT_TERM(&evt);
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *        Sends the state chanage event to stack
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
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *      This is the  idea this function works if app & stack are  same
 *      exe. When they are defferent this function defintion we will provide
 *      as part of client library.
 *  See Also:
 *****************************************************************************/
REDDLLAPI int
ITS_SendStateChangeEventToStack(ITS_NODE_STATE type)
{
    int ret =0;

    if (GetNodeState() == ITS_STATE_BACKUP && type == ITS_STATE_PRIMARY)
    {
        ChangeStateFromStandbyToActive();        
        REDUNDANCY_Alarm(9005, __FILE__, __LINE__, 
                      "Node##%d from application", DSM_GetNodeId());
        ret = ITS_SUCCESS;
    }
    else
    {
        if (GetNodeState() == ITS_STATE_PRIMARY)
        {
            if (type == ITS_STATE_BACKUP)
            {
                ITS_TRACE_ERROR(("HanDleStateChangeEvent:: Request failed "
                            "App can't change state from active to backup"));
                ret = ITS_ENOINVID;
            }
            else if (type == ITS_STATE_PRIMARY)
            {
                ITS_TRACE_ERROR(("ITS_SendStateChangeEventToStack::"
                                " Request failed"
                            " App can't change state from active to active"));
                ret = ITS_ENOINVID;
            }

        }
        else if (GetNodeState() == ITS_STATE_BACKUP)
        {
            if (type == ITS_STATE_BACKUP)
            {
                ITS_TRACE_ERROR(("ITS_SendStateChangeEventToStack::"
                                 " Request failed"
                            " App can't change state from backup to backup"));
                ret = ITS_ENOINVID;
            }
        }
    }
    return ret;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *        Sends the state chanage event to App
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
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *     Actually src and ctxt are not required, if app check the its_type
 *     in the selector function it is going to probelm. As of now leave it
 *  See Also:
 *****************************************************************************/
//static int SendStateChangeEventToApp(ITS_NODE_STATE type,ITS_USHORT src,ITS_CTXT ctxt)//chaged to send notification to ISIL
static int SendStateChangeEventToApp(ITS_NODE_STATE type, ITS_USHORT src, ITS_CTXT ctxt,ITS_OCTET event_notfication)
{
    ITS_EVENT evt;
    ITS_HDR header;
    ITS_USHORT dest = 0;

    ITS_EVENT_INIT(&evt, src, 3);
    //evt.data[0] = ITS_STATE_CHANGE_EVENT;
    evt.data[0] = event_notfication;
    evt.data[1] = type;
    evt.data[2] = DSM_GetNodeId();
    memset((char*)&header, 0, sizeof(ITS_HDR));

    header.type = 0xFF;
    header.context.dialogue_id = ctxt;

    dest = ROUTE_SelectApplication(&header, &evt, ITS_TRUE);
    printf("SendStateChangeEventToApp funcion is called and dest = %x",dest);
		
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        int ret =0;
        ret = TRANSPORT_PutEvent(dest, &evt);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&evt);
        ITS_TRACE_ERROR(("1) %d  2) %d ITS_SendStateChangeEventToApp::Error sending event", dest, ret));
        printf("1) %d  2) %d ITS_SendStateChangeEventToApp::Error sending event", dest, ret);
        }
        return ret;
    }
    else
    {
        ITS_TRACE_ERROR(("ITS_SendStateChangeEventToApp::Error sending event"));
        printf(("ITS_SendStateChangeEventToApp::Error sending event"));
        return ITS_ENODESTINATION;
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *        Sends the notifications to App
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
 *      ITS_SUCCESS on success or and ITS error code on failure.
 *
 *  Notes:
 *    As of now this is used in only active-active
 *    Actually src and ctxt are not required, if app check the its_type
 *    in the selector function it is going to probelm. As of now leave it
 *  See Also:
 *****************************************************************************/
static int
SendNotificationEventToApp(ITS_OCTET notification,
                           ITS_USHORT src,
                           ITS_CTXT ctxt)
{
    ITS_EVENT evt;
    ITS_HDR header;
    ITS_USHORT dest = 0;

    ITS_EVENT_INIT(&evt, src, 1);
    evt.data[0] = notification;

    memset((char*)&header, 0, sizeof(ITS_HDR));

    header.type = 0xFF;
    header.context.dialogue_id = ctxt;

    dest = ROUTE_SelectApplication(&header, &evt, ITS_TRUE);
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        int ret =0;
        ret = TRANSPORT_PutEvent(dest, &evt);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&evt);
        ITS_TRACE_ERROR(("1) %d  2) %d SendNotificationEventToApp::Error seding event", dest, ret));
        }
        return ret;
    }
    else
    {
        ITS_TRACE_ERROR(("SendNotificationEventToApp::Error seding event"));
        return ITS_ENODESTINATION;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This is DSM call back function for state changes.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void ApplicationMembershipChangeCb(ITS_POINTER object,ITS_POINTER userData,ITS_POINTER callData)
{
    DSM_MembershipChangeCbData* membershipChangeCbData = (DSM_MembershipChangeCbData*)callData;
     ITS_Class redunClass = ITS_FindFeature (REDUNDANCY_CLASS_NAME);

    ITS_OCTET changeType = membershipChangeCbData->membershipChangeType;

    if (membershipChangeCbData-> membershipChangeType == DSM_FT_GROUP_MEMBER_LEAVE)
    {
        if (REDUNDANCY_CONFIGURED_TYPE(itsREDUNDANCY_Class) == ITS_ACTIVE_ACTIVE)
        {
            /* Change the routing style to node general */
            ROUTE_SetApplicationSelector(appSelectAll);

            /* Active-Active config here we do have to inform App abt this*/
            SendNotificationEventToApp(ITS_NODE_LEFT_NOTIFICATION_EVENT,ITS_RED_MODULE_SRC,0);

            REDUNDANCY_Alarm(9002, __FILE__, __LINE__, 
                             "Node##%d Peer node down changing routing"
                             " func to All", DSM_GetNodeId());

            ITS_TRACE_CRITICAL(("ApplicationMembershipChangeCb:: Node LEAVE ----\n"));
            return;
        }

        if (GetNodeState() == ITS_STATE_PRIMARY)
        {   int ret_val=0;
            ITS_TRACE_WARNING(("Back up node left, no change over ----\n"));
            /* for enabling the procedure Leave to be reported to ISIL*/
            //ret_val = SendStateChangeEventToApp(ITS_STATE_PRIMARY, ITS_RED_MODULE_SRC,0,ITS_STATE_CHANGE_EVENT);              
            ret_val = SendStateChangeEventToApp(ITS_STATE_PRIMARY, ITS_RED_MODULE_SRC,0,DSM_FT_GROUP_MEMBER_LEAVE);              
            REDUNDANCY_Alarm(9002, __FILE__, __LINE__, 
                             "Node##%d Backup node down no action at"
                             " active", DSM_GetNodeId());

        }
        else
        {
            int ret =0;

            ITS_TRACE_CRITICAL(("Active node left, change over procedure in progress\n"));
            REDUNDANCY_Alarm(9002, __FILE__, __LINE__, 
                             "Node##%d Active node down,"
                             " change over in progress", DSM_GetNodeId());
             /* for enabling the procedure Leave to be reported to ISIL*/
            //ret = SendStateChangeEventToApp(ITS_STATE_PRIMARY, ITS_RED_MODULE_SRC,0,ITS_STATE_CHANGE_EVENT);              
            /* 09-FEB-2011 Fast detection and making it active so when a node is leaving*/
            SetNodeState(ITS_STATE_PRIMARY); 
            ret = SendStateChangeEventToApp(ITS_STATE_PRIMARY, ITS_RED_MODULE_SRC,0,DSM_FT_GROUP_MEMBER_LEAVE);              
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_CRITICAL(("Could not send change over event to app"
                                ":: Change over proc aborted\n"));
            }
            else
            {
                ITS_EVENT evt;

                ITS_EVENT_INIT(&evt, 2, 3);
                evt.data[0] = ITS_STATE_CHANGE_EVENT;
                evt.data[1] = ITS_STATE_PRIMARY;
                evt.data[2] = DSM_GetNodeId();

                /*send state change event to the mate & change own state also*/
                //SetNodeState(ITS_STATE_PRIMARY); /VNL PLATFORM

                ITS_TRACE_CRITICAL(("StateChangeEvent:: Changing state ACTIVE \n"));
                /* Inform the local users also, I am assuming that the above
                 * event is not freed yet*/
                if (!CALLBACK_IsListEmpty(ITS_RedundancyConfig_Callback))
                {
                    CALLBACK_CallCallbackList(ITS_RedundancyConfig_Callback,
                                          (void*)NULL,
                                          (void*)&evt);
                }
                else
                {
                    ITS_TRACE_WARNING(("Redundancy call back list is emtpy \n"));
                }

                /* free the event we no longer require*/
                ITS_EVENT_TERM(&evt);

                REDUNDANCY_Alarm(9004, __FILE__, __LINE__, 
                              " backup to active Node##%d"
                              " successfull", DSM_GetNodeId());
                ITS_TRACE_CRITICAL(("Change over Successful\n"));
            }

            REDUNDANCY_SendChangeEventToStack(changeType);
        }
    }
    else if (membershipChangeCbData->membershipChangeType == DSM_FT_GROUP_MEMBER_JOIN)
    {
        int ret =0;
        REDUNDANCY_Alarm(9003, __FILE__, __LINE__, 
                         "Node##%d Mate Node joined", DSM_GetNodeId());
        ITS_TRACE_CRITICAL((" \t\t\t\tMate node JOINED \n"));

        if (REDUNDANCY_CONFIGURED_TYPE(itsREDUNDANCY_Class) == ITS_ACTIVE_ACTIVE)
        {
            /*Change routing style temp to all specific one*/
            ROUTE_SetApplicationSelector(appSelectAll);

            /* join notification to app*/
            SendNotificationEventToApp(ITS_NODE_JOIN_NOTIFICATION_EVENT,
                                       ITS_RED_MODULE_SRC,
                                       0);

            /*Change routing style node specific one*/
            ROUTE_SetApplicationSelector(appSelectNode);
        }
        else
        {
            ITS_TRACE_DEBUG(("\t\t\tApplicationMembershipChangeCb:: Node join \n"));
            TIMERS_Sleep(1);
            /* If this node is active send standby notification to other one*/
            if (GetNodeState() == ITS_STATE_PRIMARY)
            {
                ITS_EVENT evt;
                ITS_EVENT_INIT(&evt, 2, 3);
                evt.data[0] = ITS_STATE_CHANGE_EVENT;
                evt.data[1] = ITS_STATE_BACKUP;
                evt.data[2] = DSM_GetNodeId();

                /*send state change event to the mate & change own state also*/
               // SetNodeState(ITS_STATE_PRIMARY); //VNL PLATFORM:

                /* Multicast the event guess why mtp3 ? */
                DSM_MulticastStackEventToFtGroupMembers(DSM_Mtp3FtGroupId,
                                                        evt,
                                                        ITS_GCS_EVENT_FROM_APPL,
                                                        ITS_ENODESTINATION);
                ITS_EVENT_TERM(&evt);
                /* for enabling the procedure join to be reported to ISIL*/
                //ret = SendStateChangeEventToApp(ITS_STATE_PRIMARY,ITS_RED_MODULE_SRC,0,ITS_STATE_CHANGE_EVENT);
                ret = SendStateChangeEventToApp(ITS_STATE_PRIMARY,ITS_RED_MODULE_SRC,0,DSM_FT_GROUP_MEMBER_JOIN);
                if (ret != ITS_SUCCESS)
                {
                   ITS_TRACE_CRITICAL(("Failed to send Startup Node Status to App"));
                }
            }
        }
        REDUNDANCY_SendChangeEventToStack(changeType);
    }
    else if (membershipChangeCbData-> membershipChangeType == ITS_STATE_CHANGE_EVENT)
    {
        /* 
         * This is state change event, change our state to stand by
         *  and inform users also
         */
        int ret =0;

        if (GetNodeState() == ITS_STATE_BACKUP)
        {
            return;
        }

        REDUNDANCY_Alarm(9005, __FILE__, __LINE__, 
                      "Node##%d from peer node", DSM_GetNodeId());

        ITS_TRACE_CRITICAL(("Request from mate to become stand by,"
                            " change over procedure in progress\n"));
        ret = SendStateChangeEventToApp(ITS_STATE_BACKUP,ITS_RED_MODULE_SRC,0,ITS_STATE_CHANGE_EVENT);             
         
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_CRITICAL(("Could not send change over event to app"
                            ":: Change over proc aborted\n"));
        }
        else
        {
            ITS_EVENT evt;
            ITS_USHORT src=0;

            ITS_EVENT_INIT(&evt, src, 2);
            evt.data[0] = ITS_STATE_CHANGE_EVENT;
            evt.data[1] = ITS_STATE_BACKUP;


            /*let the protocols also know*/
            if (!CALLBACK_IsListEmpty(ITS_RedundancyConfig_Callback))
            {
              //  CALLBACK_CallCallbackList(ITS_RedundancyConfig_Callback,(void*)NULL,(void*)&evt);//VNL PLATFORM
            }
            else
            {
                ITS_TRACE_WARNING(("Redundancy call back list is emtpy \n"));
            }

            /* free the event we no longer require*/
            ITS_EVENT_TERM(&evt);
            
          //  SetNodeState(ITS_STATE_BACKUP); VNL PLATFORM

            REDUNDANCY_Alarm(9004, __FILE__, __LINE__, 
                             " active to backup Node##%d",
                             DSM_GetNodeId()); 
            
            ITS_TRACE_CRITICAL(("Change over Successful\n"));
        }

        REDUNDANCY_SendChangeEventToStack(changeType);
    }
    else if (membershipChangeCbData->membershipChangeType == ITS_PLATFORM_ACTIVE_NOTIFICATION_EVENT)
    {
        int ret =0;
        printf("REDUNDANCY:BACKUP to ACTIVE ::::ITS_PLATFORM_ACTIVE_NOTIFICATION_EVENT\n");
        if (GetNodeState() == ITS_STATE_PRIMARY)
        {
            return;
        }

        REDUNDANCY_Alarm(9005, __FILE__, __LINE__,"Node##%d from peer node", DSM_GetNodeId());

       // ITS_TRACE_CRITICAL(("Request from PLATFORM  to become ACTIVE by change over procedure in progress\n"));
        ret = SendStateChangeEventToApp(ITS_STATE_PRIMARY,ITS_RED_MODULE_SRC,0,ITS_PLATFORM_ACTIVE_NOTIFICATION_EVENT);    
        ITS_TRACE_CRITICAL(("Return Value of ret=%d\n",ret));         
        if (ret != ITS_SUCCESS)
        {
            printf("Could not Able to  send change over event to app:: Change over proc aborted\n");
            ITS_TRACE_CRITICAL(("Could not Able to  send change over event to app:: Change over proc aborted\n"));
        }
        else
        {
            ITS_EVENT evt;
            ITS_USHORT src=0;

            ITS_EVENT_INIT(&evt, src, 2);
            evt.data[0] = ITS_PLATFORM_ACTIVE_NOTIFICATION_EVENT;
            evt.data[1] = ITS_STATE_PRIMARY;


            /*let the protocols also know*/
            if (!CALLBACK_IsListEmpty(ITS_RedundancyConfig_Callback))
            {
                CALLBACK_CallCallbackList(ITS_RedundancyConfig_Callback,
                                      (void*)NULL,
                                      (void*)&evt);
            }
            else
            {
                ITS_TRACE_WARNING(("Redundancy call back list is emtpy \n"));
                        }

            /* free the event we no longer require*/
            ITS_EVENT_TERM(&evt);

            SetNodeState(ITS_STATE_PRIMARY);

            REDUNDANCY_Alarm(9004, __FILE__, __LINE__, "!!!!!! BACKUP TO ACTIVE NODE STATE!!!!!!##%d", DSM_GetNodeId());

            ITS_TRACE_CRITICAL(("Change over Successful\n"));
        }

        REDUNDANCY_SendChangeEventToStack(changeType);
       }
    else if (membershipChangeCbData->membershipChangeType == ITS_PLATFORM_BACKUP_NOTIFICATION_EVENT)
    {
        /*
         * This is state change event, change our state from BACKUP to ACTIVE
         *  and inform users also
         */
        int ret =0;
        printf("REDUNDANCY:ACTIVE TO BACKUP::::ITS_PLATFORM_BACKUP_NOTIFICATION_EVENT\n");
        if (GetNodeState() == ITS_STATE_BACKUP)
        {
            return;
        }

        REDUNDANCY_Alarm(9005, __FILE__, __LINE__,"Node##%d from peer node", DSM_GetNodeId());

      //  ITS_TRACE_CRITICAL(("Request from PLATFORM  to become ACTIVE by change over procedure in progress\n"));
        ret = SendStateChangeEventToApp(ITS_STATE_BACKUP,ITS_RED_MODULE_SRC,0,ITS_PLATFORM_BACKUP_NOTIFICATION_EVENT);             
        if (ret != ITS_SUCCESS)
        {
            printf("Could not Able to  send change over event to app:: Change over proc aborted\n");
            ITS_TRACE_CRITICAL(("Could not Able to  send change over event to app:: Change over proc aborted\n"));
        }
        else
        {
            ITS_EVENT evt;
            ITS_USHORT src=0;

            ITS_EVENT_INIT(&evt, src, 2);
            evt.data[0] = ITS_PLATFORM_BACKUP_NOTIFICATION_EVENT;
            evt.data[1] = ITS_STATE_BACKUP;


            /*let the protocols also know*/
            if (!CALLBACK_IsListEmpty(ITS_RedundancyConfig_Callback))
            {
                CALLBACK_CallCallbackList(ITS_RedundancyConfig_Callback,(void*)NULL,(void*)&evt);
            }
            else
            {
                ITS_TRACE_WARNING(("Redundancy call back list is emtpy \n"));
                        }

            /* free the event we no longer require*/
            ITS_EVENT_TERM(&evt);

            SetNodeState(ITS_STATE_BACKUP);

            REDUNDANCY_Alarm(9004, __FILE__, __LINE__,
                             "!!!!!! ACTIVE TO BACKUP NODE STATE!!!!!!##%d",
                             DSM_GetNodeId());

            ITS_TRACE_CRITICAL(("Change over Successful\n"));
        }

        REDUNDANCY_SendChangeEventToStack(changeType);
       }
      printf("NODE STATE=%d",REDUNDANCY_GET_NODE_STATE (redunClass));
      ITS_TRACE_CRITICAL(("NODE STATE=%d",REDUNDANCY_GET_NODE_STATE (redunClass)));

}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ITS_RedundancyClass  class.
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
 *      ITS_SUCCESS
 *
 *  Notes:
 *
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    CALLBACK_Manager *callbackManager = NULL;
    RESFILE_Manager  *resMgr = NULL;
    char value[ITS_PATH_MAX];
    ENGINE_LibCache appLib;

    /*Initialize redundancy call back manager */
    ITS_RedundancyConfig_Callback = CALLBACK_InitManager();

    /*
     * Here we have to read from resource manager, what redundancy
     * configured type
     */ 
    resMgr = RESFILE_CreateResourceManager(APPL_GetConfigFileName());
    if (resMgr != NULL)
    {
        const char *name = NULL;

        /* redundancyType */
        if (RESFILE_GetKeyValueOf(resMgr, name, REDUNDANCY_APP_OPTION_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            if (strstr(value, REDUNDANCY_ACTIVE_BACKUP_STRING) != NULL)
            {
                REDUNDANCY_CONFIGURED_TYPE(objClass) = ITS_ACTIVE_STANDBY;
                ITS_TRACE_CRITICAL(("Reduandancy type configured  ACTIVE-BACKUP\n"));
                if (RESFILE_GetKeyValueOf(resMgr, name,
                                          REDUNDANCY_NODE_STATE_STRING,
                                          value, ITS_PATH_MAX) == ITS_SUCCESS)
                {
                    if (strstr(value, REDUNDANCY_NODE_STATE_BACKUP_STRING) 
                                         != NULL)
                    {
                        /* then become backup and wait*/
                        SetNodeState(ITS_STATE_BACKUP);

                        REDUNDANCY_Alarm(9001, __FILE__, __LINE__, 
                                         "Node##%d up configured as backup",
                                         DSM_GetNodeId()); 

                        ITS_TRACE_CRITICAL(("\n configured node state as BACKUP\n"));
                    }
                    else if (strstr(value, REDUNDANCY_NODE_STATE_ACTIVE_STRING) 
                                         != NULL)
                    {
                        SetNodeState(ITS_STATE_PRIMARY);

                        REDUNDANCY_Alarm(9001, __FILE__, __LINE__, 
                                    "Configuration active-backup Node##%d up"
                                    " configured as active", DSM_GetNodeId()); 

                        ITS_TRACE_CRITICAL(("\n configured node state as ACTIVE\n"));
                    }
                    else
                    {
                        ITS_TRACE_CRITICAL(("Invalid nodeState type configured %s \n", value));
                        exit(0);
                    }
                }
                else
                {
                    ITS_TRACE_CRITICAL(("nodeState must be configured, if "
                                        "redundancy type is active-backup \n"));
                    exit(0);
                }
            }
            else if (strstr(value, REDUNDANCY_ACTIVE_ACTIVE_STRING) != NULL)
            {
                ITS_TRACE_CRITICAL(("Reduandancy type configured ACTIVE-ACTIVE\n"));
            }
            else
            {
                ITS_TRACE_CRITICAL(("Invalid Redundancy type configured %s\n, value "));
                ITS_TRACE_CRITICAL(("Supported types active-active or active-backup \n"));
                exit(0);
            }
        }
        else
        {
            ITS_TRACE_CRITICAL((" Redundancy type not configured \n "));
            ITS_TRACE_CRITICAL(("pls configure it first, or remove this feature"
                                  " from XML if you are using standalone \n"));
            exit(0);
        }


        if (REDUNDANCY_CONFIGURED_TYPE(objClass) == ITS_ACTIVE_ACTIVE)
        {
            /* do the selectors, if present */
            appLib = ENGINE_LibGet(application, ENGINE_APP_LIB_NAME(application));
            if (appLib != NULL)
            {
                if (ENGINE_APP_APP_SELECTOR(application))
                {
                    appSelectNode = (ROUTE_AppSelector)
                                    DLSYM_Resolve(ENGINE_LC_LIBRARY(appLib),
                                    ENGINE_APP_APP_SELECTOR(application));

                    ITS_C_ASSERT(appSelectNode != NULL);
                    ROUTE_SetApplicationSelector(appSelectNode);
                }
            }

            if (RESFILE_GetKeyValueOf(resMgr, name, REDUNDANCY_APP_SELECT_ALL,
                                      value, ITS_PATH_MAX) == ITS_SUCCESS)
            {
                if (appLib != NULL)
                {
                    /*we have to check whether this function exists or not*/
                    appSelectAll = (ROUTE_AppSelector)
                                   DLSYM_Resolve(ENGINE_LC_LIBRARY(appLib),
                                                 value);
                    ITS_C_ASSERT(appSelectAll != NULL);
                }
            }
            else
            {
                ITS_TRACE_ERROR(("Not configured appSelectAll for active-active\n"));
            }
        }
        free(resMgr);
    }

    /*
     * Register call back with DSM-SUB system
     * Get the DSM call back manager and register our own function
     * for procedure network change
     */
    callbackManager = DSM_GetMembershipChangeCallbacks(DSM_Mtp3FtGroupId);
    if (callbackManager != NULL)
    {
        CALLBACK_AddCallback(callbackManager,
                             ApplicationMembershipChangeCb,
                             NULL);
    }
    else
    {
        ITS_TRACE_CRITICAL((" CallBack registration failed\n "));
    }

    ITS_RedundancyMgmtCallbacks = CALLBACK_InitManager();
    if (ITS_RedundancyMgmtCallbacks == NULL)
    {
        ITS_TRACE_CRITICAL((" RedMgmt CallBack initialisation failed\n "));
        return (ITS_ENOMEM);
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the ITS_RedundancyClass class.
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
 *      a constant pointer to the application name
 *
 *  Notes:
 *
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    /* Nothing much to do delete the call back manager*/
    CALLBACK_DestroyManager(ITS_RedundancyConfig_Callback);
}

/*
 * this is the class record
 */
REDDLLAPI REDUNDANCY_ClassRec its_REDUNDANCYClassRec =
{
    /* core part */
    {
#if defined(WIN32)
        NULL,
#else
		&itsCORE_ClassRec,              /* CORE is superclass */
#endif
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        REDUNDANCY_CLASS_NAME,          /* class name */
        ClassInitialize,                /* class init */
        ClassDestroy,                   /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },

    /* active standby class */
    {
        ITS_ACTIVE_ACTIVE,       /* by default it is active-active */
        GetNodeState,
        ChangeStateFromStandbyToActive,
        GetRedundancyCallbackMgr
    }
};

REDDLLAPI ITS_Class itsREDUNDANCY_Class = (ITS_Class)&its_REDUNDANCYClassRec;



/*Alarms section */

REDDLLAPI void
REDUNDANCY_Alarm(int which, const char *file, const int line,
            char *fmt, ...)
{
    va_list      alist;
    ALARM_Format *tmp_fmt;

    ITS_C_ASSERT(which >= REDUNDANCY_ALARM_START &&
                 which <= REDUNDANCY_ALARM_END);

    tmp_fmt = REDUNDANCY_Alarms[which - REDUNDANCY_ALARM_START];


    va_start(alist, fmt);

    ALARM_VIssueAlarm(itsALARM_Class, tmp_fmt, file, line, fmt, alist);

    va_end(alist);

    return;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Setting the Redundancy node status flag into DSM. This is done for
 *      distinguishing for coming alone (first time) or Joining later to
 *      already Up and running redundant node.
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
 *      
 *
 *  Notes:
 *
 ****************************************************************************/
static ITS_INT
REDUNDANCY_AllocNodeStartUpFlag(ITS_OCTET **status)
{
    ITS_OCTET key = 1;
    int error = 0;

    ITS_TRACE_DEBUG(("AllocStartUpFlag called"));

    /* Allocate here */
    *status = (ITS_OCTET *)DSM_Alloc(DSM_Mtp3FtGroupId,
                               RED_NODE_STARTUP_FLAG_TABLE_ID,
                               (ITS_OCTET *)&key, sizeof(ITS_OCTET),
                               sizeof(ITS_OCTET), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            ITS_TRACE_CRITICAL(("Couldn't acquire mutex"));
            break;
        case (ITS_ENOMEM):
            ITS_TRACE_CRITICAL(("No Memory to allocate"));
            break;
        default:
            ITS_TRACE_CRITICAL(("Error %d\n", error));
            break;
        }
    }

    return error;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Setting the Redundancy node status flag into DSM. This is done for
 *      distinguishing for coming alone (first time) or Joining later to
 *      already Up and running redundant node.
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
 *      
 *
 *  Notes:
 *
 ****************************************************************************/
static ITS_INT
REDUNDANCY_FindNodeStartUpFlag(ITS_OCTET **status) 
{
    int error = 0;
    ITS_OCTET key = 1;

    ITS_TRACE_DEBUG(("FindStartUpFlag called"));

    *status = (ITS_OCTET *) DSM_Find(DSM_Mtp3FtGroupId,
                             RED_NODE_STARTUP_FLAG_TABLE_ID,
                             (ITS_OCTET*)&key, sizeof(ITS_OCTET), &error);
    if (error != ITS_SUCCESS)
    {
       switch (error)
       {
       case ITS_ENOTFOUND:
          ITS_TRACE_DEBUG(("Entry not  present\n"));
          break;
       default:
          /* DSM internal error */
          ITS_TRACE_CRITICAL(("DSM internal error: %d.\n", error));
          break;
       }
    }

    return error;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Setting the Redundancy node status flag into DSM. This is done for
 *      distinguishing for coming alone (first time) or Joining later to
 *      already Up and running redundant node.
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
 *      
 *
 *  Notes:
 *
 ****************************************************************************/
static ITS_INT
REDUNDANCY_ReleaseNodeStartUpFlag(ITS_OCTET *status)
{
    ITS_OCTET key = 1;
    int error = 0;

    ITS_TRACE_DEBUG(("ReleaseStartUpFlag called"));

    if (status == NULL)
    {
       return !ITS_SUCCESS;
    }

    error = DSM_Commit(DSM_Mtp3FtGroupId,
                       RED_NODE_STARTUP_FLAG_TABLE_ID,
                       (ITS_OCTET *) &key,
                       sizeof(ITS_OCTET), status);

    if (error != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("ReleaseNodeStatus:Commit Failed error %d.\n", error));
        return (error);
    }
    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Setting the Redundancy node status flag into DSM. This is done for
 *      distinguishing for coming alone (first time) or Joining later to
 *      already Up and running redundant node.
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
 *      
 *
 *  Notes:
 *
 ****************************************************************************/
REDDLLAPI ITS_INT
REDUNDANCY_GetNodeStartUpFlagAndState(ITS_NODE_STATE *state)
{
    int ret = ITS_SUCCESS;
    ITS_OCTET *status = NULL;

    ITS_Class redClass;
    if ( (redClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME)) == NULL)
    {
       return ITS_ENOTCONFIG;
    }

    if (REDUNDANCY_CONFIGURED_TYPE(redClass) == ITS_ACTIVE_ACTIVE)
    {
       /* Not a active-backup redundancy */
       return ITS_ENOTCONFIG;
    }

    /* Find if already there */ 
    ret = REDUNDANCY_FindNodeStartUpFlag(&status);
    if ((ret == ITS_ENOTFOUND) && (GetNodeState() == ITS_STATE_PRIMARY))
    {
       int ret1 = ITS_SUCCESS;

       /* First time, allocate here */
       ret1 = REDUNDANCY_AllocNodeStartUpFlag (&status);
       if (ret1 == ITS_SUCCESS)
       {
          /* Release here */
          REDUNDANCY_ReleaseNodeStartUpFlag(status);
       }
    }
    else if (ret == ITS_SUCCESS)
    {
       if (status == NULL)
       {
           ITS_TRACE_ERROR (("Error Getting NodeStartUpFlag"));
       }
       else
       {
           /* Release here */
           REDUNDANCY_ReleaseNodeStartUpFlag(status);
       }
    }

    *state = GetNodeState();

    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
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
 *      
 *
 *  Notes:
 *
 ****************************************************************************/
static void
REDUNDANCY_SendChangeEventToStack(ITS_OCTET changeType)
{
    ITS_EVENT event;
    ITS_EVENT_INIT(&event, ITS_RED_MODULE_SRC, 3);
    event.data[0] = changeType;          //Event type
    event.data[1] = GetNodeState();      //Node State 
    event.data[2] = DSM_GetNodeId();     //node id

    CALLBACK_CallCallbackList(ITS_RedundancyMgmtCallbacks,
                             (ITS_POINTER) NULL, (void*)&event);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      API to provide Node State at Application level
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_NODE_STATE (ITS_STATE_PRIMARY/ITS_STATE_BACKUP)
 *
 *  Return Value:
 *      ITS_SUCCESS/ITS_NOTCONFIG 
 *
 *  Notes:
 *
 ****************************************************************************/
REDDLLAPI ITS_INT
ITS_GetNodeState(ITS_NODE_STATE *state)
{
    int ret = ITS_SUCCESS;
    ITS_Class redClass;

    if ( (redClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME)) == NULL)
    {
       return ITS_ENOTCONFIG;
    }

    *state = GetNodeState();

    return ret;
}
