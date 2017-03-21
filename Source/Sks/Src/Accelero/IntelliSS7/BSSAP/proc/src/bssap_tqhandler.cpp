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
 *  ID: $Id: bssap_tqhandler.cpp,v 1.2 2008-02-01 04:29:53 amaresh.prasad Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:15  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.5  2005/12/12 08:59:41  mkrishna
 * LOG: Memory leak rectified
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/24 04:43:41  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/26 20:19:13  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 06:39:20  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:00:43  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             
#include <bssap_tqhandler.h>
#include <bssap_sccphandler.h>
#include <bssap_discriminator.h>
#include <bssap_timer.h>
#include <bssap_cfgdb.h> //19-01-08
#include <bssap_dbc.h> //19-01-08
#include <bssap-alarm.h> //16-01-08 by Amaresh
#include <its_redundancy.h>
#include <sched.h> 

extern ITS_BOOLEAN pauseFlag;
extern ITS_BOOLEAN sspFlag;
extern ITS_UINT alarmrpc;


/*implementation:internal
*
* PURPOSE:
*      Thread function to receive application and SCCP stack data.
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0270, ID :: D0280,
*                        ID :: D1060
*/
THREAD_RET_TYPE
BSSAP_MssgHandler(void* arg)
{
    ITS_INT ret = 0;
    TQUEUETRAN_Manager* recvQ = (TQUEUETRAN_Manager*)arg;
    ITS_EVENT bssapEvent;
    BSSAP_SCCPHandler sccpHndl;
    BSSAP_Discriminator dis; 
    BSSAP_Interface bssIf;
    BSSAP_Timer timer;
    /* Added by Amaresh  start for Alarm DPC 19-01-08*/
    ITS_UINT PC=0;
    ITS_EVENT evt_data;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAPData data;
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT pc=0;
    ITS_UINT DPC = 0;
    ITS_EVENT *ev;
    ITS_OCTET bscId;
    static ITS_INT StatusCount = 0;

    /* Added by Amaresh  end for Alarm DPC 19-01-08*/
    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    ret = SCCP_EnableUserPart(SCCP_SSN_BSSAP, ITS_BSSAP_SRC);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_CRITICAL(("BSSAP_MssgHandler: SCCP registration failed %d\n", 
                                                                  ret));
        exit(0);
    }
    else
    {
        BSSAP_DEBUG(("BSSAP_MssgHandler: User Part enabled. ssn 0x%02X \n",
                                                         SCCP_SSN_BSSAP));
    }

    for (;;)
    {
        //BSSAP_DEBUG(("In Loop BSSAP Thread\n"));
        memset(&bssapEvent, 0, sizeof(ITS_EVENT));

        ret = TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(recvQ))
                                                        (recvQ,
                                                         &bssapEvent);
        if (ret != ITS_SUCCESS)
        {
            continue;
        }
   /*      if(DSM_MulticastStackEventToFtGroupMembers(DSM_TcapFtGroupId,bssapEvent,
                                  (bssapEvent.src == ITS_SCCP_SRC)?ITS_GCS_EVENT_FROM_STACK  :
                                   ((bssapEvent.src == BSSAP_LAYER3_SRC)?ITS_GCS_EVENT_FROM_APPL_CL3I:
                                   ITS_GCS_EVENT_FROM_APPL),ITS_BSSAP_SRC) == ITS_SUCCESS )
        {
            continue;
        }*/
       //BSSAP_DEBUG(("bssapEvent.src=%d.\n",bssapEvent.src));



     ITS_Event evt(&bssapEvent);
    // ev = &evt.GetEvent(); 
     //memcpy(&data, ev->data, sizeof(BSSAPData));

        BSSAP_DEBUG(("BSSAP_MssgHandler: Received event[0x%x]\n",evt.GetSource()));
        switch(evt.GetSource())
        {
            case ITS_BSSAP_SRC:
                break;

            case ITS_SCCP_SRC:
            case ITS_GCS_EVENT_FROM_STACK:

                if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
                {
                   BSSAP_DEBUG(("Backup Node Cannot Initiate Messages.\n"));
                   ret = (!ITS_SUCCESS);
                }
                else
                {
                   //BSSAP_DEBUG(("BSSAP_MssgHandler: Received SCCP event\n"));
                   sccpHndl.BSSAP_ProcessSCCPdata(evt);
                }
     
                break;

            case ITS_TIMER_SRC:

                if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
                {
                   BSSAP_DEBUG(("Backup Node Cannot Initiate Messages.\n"));
                   ret = (!ITS_SUCCESS);
                }
               else
                {

                   BSSAP_DEBUG(("BSSAP_MssgHandler: Received Timeout event\n"));
                   timer.ProcessTimeout(evt); 
                }
                break;

            case ITS_ISUP_SRC:

                 BSSAP_DEBUG(("BSSAP_MssgHandler: Received BSSAP_SCCP_SRC event\n"));
                if(StatusCount == 0)
                {
                  BSSAP_ERROR(("BSSAP_MssgHandler:BEFORE getSccpReq_status:: pauseFlag[%d] sspFlag[%d]\n",pauseFlag,sspFlag));
                   getSccpReq_status(&pauseFlag,&sspFlag,evt,254);
                   StatusCount++;
                  BSSAP_ERROR(("BSSAP_MssgHandler:AFTER getSccpReq_status:: pauseFlag[%d] sspFlag[%d]\n",pauseFlag,sspFlag));
                }
                  BSSAP_DEBUG(("BSSAP_MssgHandler:BSSAP_SCCP_SRC event: pauseFlag[%d] sspFlag[%d]\n",pauseFlag,sspFlag));
                  if (!pauseFlag)
                  {
                      if (!sspFlag)
                      {
			ret = dis.ProcessSCCPHandellingMessage(evt);
                      }
                     else
                      {
                        DPC = alarmrpc;
                        BSSAP_CRITICAL(("BSSAP_MssgHandler: "
                                           "Remote sub-system down\n"));
                         BSSAP_Alarm_CCITT(5117,__FILE__,__LINE__,"dpc %d,SSN %d",DPC,SCCP_SSN_BSSAP); //OAM
                         ret = (!ITS_SUCCESS);
                    }
                 }
                else
                 {
                     DPC =alarmrpc;
                     BSSAP_CRITICAL(("BSSAP_MssgHandler: Network down\n"));
								     BSSAP_Alarm_CCITT(5118,__FILE__,__LINE__,"dpc %d",DPC); //OAM
                               
                      ret = (!ITS_SUCCESS);
                 }
            break;
            case BSSAP_LAYER3_SRC:
            case ITS_GCS_EVENT_FROM_APPL_CL3I:
               if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
               {
                   BSSAP_DEBUG(("Backup Node Cannot Initiate Messages.\n"));
                   ret = (!ITS_SUCCESS);

               }
             else
               {
                  BSSAP_DEBUG(("BSSAP_MssgHandler: Received Layer3 event\n"));
                if(StatusCount == 0)
                {
                  BSSAP_ERROR(("BSSAP_MssgHandler:BEFORE getconfig_status:: pauseFlag[%d] sspFlag[%d]\n",pauseFlag,sspFlag));
                   getconfig_status(&pauseFlag,&sspFlag,evt,254);
                   StatusCount++;
                  BSSAP_ERROR(("BSSAP_MssgHandler:AFTER getconfig_status:: pauseFlag[%d] sspFlag[%d]\n",pauseFlag,sspFlag));
                }
                  BSSAP_DEBUG(("BSSAP_MssgHandler:LAYER3 event: pauseFlag[%d] sspFlag[%d]\n",pauseFlag,sspFlag));
                  if (!pauseFlag)
                  {
                      if (!sspFlag)
                      {
                          ret = dis.ProcessLayer3BSSAPMessage(evt);
                      }
                     else
                      {
                         /*  BSSAP_Api* mssg = new BSSAP_Api(&data);
                           bscId= mssg->GetBssId();
                           cfgdata = db.FetchRPCEntry(bscId);
                           if (cfgdata)
                            {
                              DPC=cfgdata->rpc;
                              BSSAP_DEBUG(("BSSAP_Config:PC=%d\n",DPC));
                            }
                           delete mssg;
                           mssg=NULL;
*/
                          DPC =alarmrpc;
                         BSSAP_CRITICAL(("BSSAP_MssgHandler: "
                                           "Remote sub-system down\n"));
                         BSSAP_Alarm_CCITT(5117,__FILE__,__LINE__,"dpc %d,SSN %d",DPC,SCCP_SSN_BSSAP); //OAM
                                                                                                                                    
                         ret = (!ITS_SUCCESS);
                    }
                 }
                else
                 {
  /*                         BSSAP_Api* mssg = new BSSAP_Api(&data);
                           bscId= mssg->GetBssId();
                           cfgdata = db.FetchRPCEntry(bscId);
                           if (cfgdata)
                            {
                              DPC=cfgdata->rpc;
                              BSSAP_DEBUG(("BSSAP_Config:PC=%d\n",DPC));
                            }
                           delete mssg;
                           mssg=NULL;*/
                          DPC =alarmrpc;
                     BSSAP_CRITICAL(("BSSAP_MssgHandler: Network down\n"));
								     BSSAP_Alarm_CCITT(5118,__FILE__,__LINE__,"dpc %d",DPC); //OAM
                               
                      ret = (!ITS_SUCCESS);
                 }

               }
              break;
            case ITS_GCS_EVENT_FROM_APPL: 
            default:
                if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
                {
                   BSSAP_DEBUG(("Backup Node Cannot Initiate Messages.\n"));
                   ret = (!ITS_SUCCESS);

                }
               else
               {

                  BSSAP_DEBUG(("BSSAP_MssgHandler: Received app. event\n"));
                if(StatusCount == 0)
                {
                  BSSAP_ERROR(("BSSAP_MssgHandler:BEFORE getconfig_status:: pauseFlag[%d] sspFlag[%d]\n",pauseFlag,sspFlag));
                   getconfig_status(&pauseFlag,&sspFlag,evt,254);
                   StatusCount++;
                  BSSAP_ERROR(("BSSAP_MssgHandler:AFTER getconfig_status:: pauseFlag[%d] sspFlag[%d]\n",pauseFlag,sspFlag));
                }
                  BSSAP_DEBUG(("BSSAP_MssgHandler:APP event: pauseFlag[%d] sspFlag[%d]\n",pauseFlag,sspFlag));
                  if (!pauseFlag)
                  {
                     if (!sspFlag)
                     {
                        		ret = dis.ProcessOutBSSAPMessage(evt); 
                     }
                     else
                     {
/*                           BSSAP_Api* mssg = new BSSAP_Api(&data);
                           bscId= mssg->GetBssId();
                           cfgdata = db.FetchRPCEntry(bscId);
                           if (cfgdata)
                            {
                              DPC=cfgdata->rpc;
                              BSSAP_DEBUG(("BSSAP_Config:PC=%d\n",DPC));
                            }
                           delete mssg;
                           mssg=NULL;
*/
                          DPC =alarmrpc;
                        BSSAP_CRITICAL(("BSSAP_MssgHandler: "
                                           "Remote sub-system down\n"));
    			  						BSSAP_Alarm_CCITT(5117,__FILE__,__LINE__,"dpc %d,SSN %d",DPC,SCCP_SSN_BSSAP); //OAM 
	                      ret = (!ITS_SUCCESS);
                     }
                 }
                else
                 {
 /*                          BSSAP_Api* mssg = new BSSAP_Api(&data);
                           bscId= mssg->GetBssId();
                           cfgdata = db.FetchRPCEntry(bscId);
                           if (cfgdata)
                            {
                              DPC=cfgdata->rpc;
                              BSSAP_DEBUG(("BSSAP_Config:PC=%d\n",DPC));
                            }
                           delete mssg;
                           mssg=NULL;
*/
                          DPC =alarmrpc;
                     BSSAP_CRITICAL(("BSSAP_MssgHandler: Network down\n"));
									   BSSAP_Alarm_CCITT(5118,__FILE__,__LINE__,"dpc %d",DPC); //OAM
                               
                     ret = (!ITS_SUCCESS);
                 }
               }
               break; 
          }
           

        if (ret != ITS_SUCCESS)
         {
             BSSAP_ERROR(("BSSAP_MssgHandler: Message sent failed\n"));
             bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EMSGSENTFAIL);
         }

        if (bssapEvent.data)
         {
            delete bssapEvent.data;
            bssapEvent.data = NULL;
         }
        sched_yield();
    }
}
