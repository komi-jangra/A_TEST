#include <its_assertion.h>
#include <bssap-alarm.h>
//#include <../include/bssap-alarm.h>

ITS_UINT _BSSAP_AlarmLevel_CCITT = ALARM_LVL_OFF;

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5101,"Time out no Block Ack received",
                         ALARM_LVL_MAJOR,"HandleTimeout","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5102,"Time out no UnBlock Ack received",
                        ALARM_LVL_MAJOR,"HandleTimeout","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5103,"Time out no ResetAck received",
                        ALARM_LVL_MAJOR,"HandleTimeout","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5104,"Time out no ResetCkt Ack received",
                        ALARM_LVL_MAJOR,"HandleTimeout","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5105,"Time out no RLSD recieved",
                        ALARM_LVL_MAJOR,"HandleTimeout","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5106,"BSSAP Initialize successfully",
                        ALARM_LVL_MAJOR,"BSSAP Init","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5107,"BSSAP Terminate successfully",
                        ALARM_LVL_MAJOR,"BSSAP Term","BSSMAP MSG",ITS_TRUE);

/*   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5108,"Fail to start Timer",
                        ALARM_LVL_MAJOR,"Start TIMER","BSSMAP MSG",ITS_TRUE); */

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5115,"Wrong message direction",
                        ALARM_LVL_MAJOR,"ProcessDTAPMessage","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5116,"Wrong message type",
                        ALARM_LVL_MAJOR,"ProcessLayer3BSSAPMessage","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5117,"Remote subsystem down:",
                       ALARM_LVL_MAJOR,"SSP","BSSMAP MSG",ITS_TRUE);

  ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5118,"Network Down:",
                       ALARM_LVL_MAJOR,"PAUSE","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5119,"Neither Map nor Dtap message",
                       ALARM_LVL_MAJOR,"ProcessLayer3BSSAPMessage:","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5120,"Failed to dispatch message to peer",
                       ALARM_LVL_MAJOR,"ProcessBSSAPMessage:","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5125,"Config data (PC) not found ",
                       ALARM_LVL_MAJOR,"BSSAP_CfgDB::FetchPCEntry","BSSMAP MSG",ITS_TRUE);

/*   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5126,"Config data (BscId) not found :",
                       ALARM_LVL_MAJOR,"BSSAP_CfgDB::FetchNWIDEntry","BSSMAP MSG",ITS_TRUE);*/

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5127,"Fail to remove DPC",
                       ALARM_LVL_MAJOR,"BSSAP_CfgDB::RemoveNWIDEntry","BSSMAP MSG",ITS_TRUE);

/*   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5128,"Fail to remove Bsc Id:",
                       ALARM_LVL_MAJOR,"UNBLK Ack","BSSAP_CfgDB::RemoveNWIDEntry",ITS_TRUE);*/

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5129,"Cannot Add DPC (BSCId):",
                       ALARM_LVL_MAJOR,"BSSAP_CfgDB::AddCfg","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5130,"Contest already exist:",
                      ALARM_LVL_MAJOR,"BSSAP_CicDB::AddCIC","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5131,"CIC Context not found :",
                     ALARM_LVL_MAJOR,"BSSAP_CicDB::FetchCICRecord","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5132,"Failed to remove Context :",
                     ALARM_LVL_MAJOR,"BSSAP_CicDB::RemoveCICRecord","BSSMAP MSG",ITS_TRUE);
   
   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5133,"Could not modify Context:",
                     ALARM_LVL_MAJOR,"BSSAP_CicDB::ModifyCICRecord","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5134,"Call in busy State :",
                     ALARM_LVL_MAJOR,"ProcessAssignmentRequest","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5135,"CIC in Block State",
                     ALARM_LVL_MAJOR,"ProcessAssignmentRequest","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5136,"CIC Pool mismatch",
                     ALARM_LVL_MAJOR,"ProcessAssignmentRequest","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5137,"Call in busy State :",
                     ALARM_LVL_MAJOR,"ProcessAssignmentRequest","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5138,"CIC in Block State",
                     ALARM_LVL_MAJOR,"ProcessAssignmentRequest","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5139,"CIC Pool mismatch",
                     ALARM_LVL_MAJOR,"ProcessAssignmentRequest","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5140,"No CIC Found:",
                    ALARM_LVL_MAJOR,"ProcessAssignmentFail:","BSSMAP MSG",ITS_TRUE);

   ALARM_FORMAT_SUBSYS(CCITT_BSSAP,5141,"Invalid PCM and Time slot:",
                    ALARM_LVL_MAJOR,"ProcessResetCktReq:","BSSMAP MSG",ITS_TRUE);










  ALARM_Format *CCITT_BSSAP_ALARM[]=
                                  {
                                    &ALARM_CCITT_BSSAP5101,
                                    &ALARM_CCITT_BSSAP5102,
                                    &ALARM_CCITT_BSSAP5103,
                                    &ALARM_CCITT_BSSAP5104,
                                    &ALARM_CCITT_BSSAP5105,
                                    &ALARM_CCITT_BSSAP5106,
                                    &ALARM_CCITT_BSSAP5107,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL,
				    NULL,	
                                    &ALARM_CCITT_BSSAP5115,
                                    &ALARM_CCITT_BSSAP5116,
                                    &ALARM_CCITT_BSSAP5117,
                                    &ALARM_CCITT_BSSAP5118,
                                    &ALARM_CCITT_BSSAP5119,
                                    &ALARM_CCITT_BSSAP5120,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL,
                                    &ALARM_CCITT_BSSAP5125,
				    NULL,
                                    &ALARM_CCITT_BSSAP5127,
 				    NULL,	                                  
                                    &ALARM_CCITT_BSSAP5129,
                                    &ALARM_CCITT_BSSAP5130,
                                    &ALARM_CCITT_BSSAP5131,
                                    &ALARM_CCITT_BSSAP5132,
                                    &ALARM_CCITT_BSSAP5133,
                                    &ALARM_CCITT_BSSAP5134,
                                    &ALARM_CCITT_BSSAP5135,
                                    &ALARM_CCITT_BSSAP5136,
                                    &ALARM_CCITT_BSSAP5137,
                                    &ALARM_CCITT_BSSAP5138,
                                    &ALARM_CCITT_BSSAP5139,
                                    &ALARM_CCITT_BSSAP5140,
                                    &ALARM_CCITT_BSSAP5141
                                };

void
BSSAP_Alarm_CCITT(int which, const char *file, const int line,
                char *format, ...)
{
    va_list alist;
    ALARM_Format *fmt;

    ITS_C_ASSERT(which >= CCITT_BSSAP_ALARM_START &&
                 which <= CCITT_BSSAP_ALARM_END);

    fmt = CCITT_BSSAP_ALARM[which - CCITT_BSSAP_ALARM_START];

    if (fmt->severity > _BSSAP_AlarmLevel_CCITT)
    {
        return;
    }

    va_start(alist, format);

    ALARM_VIssueAlarm(itsALARM_Class, fmt, file, line, format, alist);

    va_end(alist);
}

