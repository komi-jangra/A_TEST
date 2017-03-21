/*
 Organization : Virtualwire

 Project : BPM-IMR

 $Author $

 $Id:OAMS_CCUH.c $


*/
#include "linuxWrapper.h"
#include "bpmxxx_platformLib.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#ifdef PLATFORM_LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
SysAddr slfAddr;
#endif
#define MODULE "OAMS_CCUH"
void bpmAisCallbackFunc(struct sAisParam* param)
{

        bpmLog(DBG_MSG,MODULE,FUNC,"In AIS Handler Function\n");

        switch(param->messageId)
        {
                case BPM_HEALTHCHECK_MESSAGE:

                        bpmLog(DBG_MSG,MODULE,FUNC,"   **** HealthCheck Callback Function by ****  \n");
                        fflush(stdout);
                        bpmRespondToAis (param->invocation,OK);
                        break;

                case BPM_SELFCARD_STATE_CHANGE:

                        bpmLog(DBG_MSG,MODULE,FUNC,"         ///////////  SelfCard State Change Callback called /////////\n");
                        bpmLog(DBG_MSG,MODULE,FUNC," self card Present State[%d]\n", param->aisMsgLoad.cardStateLoad.presentState);
                        bpmLog(DBG_MSG,MODULE,FUNC," self card Previous State[%d]\n", param->aisMsgLoad.cardStateLoad.previousState);
                        bpmLog(DBG_MSG,MODULE,FUNC,"CARD STATE :%d",param->cardState);
                        bpmRespondToAis (param->invocation,OK);
                        break;

                case BPM_PEERCARD_STATE_CHANGE:

                        bpmLog(DBG_MSG,MODULE,FUNC,"....PeerCard State Change Callback called....\n");
                        bpmLog(DBG_MSG,MODULE,FUNC," peer card Present State[%d]\n", param->aisMsgLoad.cardStateLoad.presentState);
                        bpmLog(DBG_MSG,MODULE,FUNC," self card Previous State[%d]\n", param->aisMsgLoad.cardStateLoad.previousState);
                        bpmRespondToAis (param->invocation,OK);
                        break;
	
					case BPM_MSG_ACK_PEER_HEALTH_BAD:

                        break;

               case BPM_MSG_ACK_CONFIGURE:
                        bpmLog(DBG_MSG,MODULE,FUNC,"....BPM_MSG_ACK_CONFIGURE called....\n");
                        bpmLog(DBG_MSG,MODULE,FUNC," slotID[%d]\n", param->aisMsgLoad.aisParamLoad.slotID);
                        bpmLog(DBG_MSG,MODULE,FUNC, "frameID %d\n", param->aisMsgLoad.aisParamLoad.frameID);
                        bpmLog(DBG_MSG,MODULE,FUNC, "MateCardPresence %d\n", param->aisMsgLoad.aisParamLoad.MateCardPresence);
                        bpmLog(DBG_MSG,MODULE,FUNC, "systemType %d\n", param->aisMsgLoad.aisParamLoad.systemType);
                        bpmLog(DBG_MSG,MODULE,FUNC, "version %d.%d.%d\n", param->aisMsgLoad.aisParamLoad.version.major, param->aisMsgLoad.aisParamLoad.version.minor, param->aisMsgLoad.aisParamLoad.version.revision);
                        break;

               case BPM_MSG_ACK_CONFIGURE_RESET:
                        break;
			
                case BPM_SHUTDOWN:
                //sleep(2);
                       bpmLog(DBG_MSG,MODULE,FUNC,"\n Shutdown received by OAMS_CCUH\n");
                exit(1);
                        break;

                default:
                        break;
        }
}

int
main (int argc, char *argv[])
{
  #ifdef PLATFORM_LOGGER_IMR
    slfAddr.prcr = 0;
    slfAddr.entity = APPID_OAMS_CCUH; /*TS-PI APPID*/
    slfAddr.clsId = 0;
    slfAddr.rfu = 0;
    slfAddr.inst = 0;
    if(InitLoggingUtility(slfAddr) == 0)
    {
      bpmLog(DBG_MSG,MODULE,FUNC," OAMS_CCUH GET REGISTERED  with LOGGER Utility   ");
    }
    else
    {
      printf ("OAMS_CCUH couldnot  REGISTERED  with LOGGER Utility   ");
    }
                                                                                                                             
    #endif
  
//getComponentRegister ();
bpmLog(DBG_MSG,MODULE,FUNC,"OAMS_CCUH\n");
bpmGetComponentRegister(bpmAisCallbackFunc,APPID_OAMS_CCUH);

#ifdef BPM_DEBUG
//  printf ("chld\n");
#endif

/*sleep(1);*/

bpmComponentConfigure();

 for (;;)
    {
      sleep (1);
    }
#ifdef BPM_DEBUG
  //printf ("Exiting child process.... %s\n", argv[0]);
#endif
  return 0;
}
