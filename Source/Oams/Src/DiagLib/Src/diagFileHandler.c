#include <time.h>
#include <stdio.h>
#include "bpmDiaglib.h"
#include "bpmInclude.h"

extern FILE *filePtr; 
extern sLibGlobalParam libGlobalParam;
extern sParamKeySet paramKeySet[MAX_TCT_ID][MAX_TEST_ID];
extern I_U8 gTestFail;

I_U32 doFileOperation(void *BpmRespPtr, I_U8 testResult, I_U32 action) /* test result -  DIAG_CMD_CANCEL, DIAG_CMD_ABORTED DIAG_CMD_AWAITED, DIAG_CMD_COMPLETE */
{
  struct tm *local = NULL;
  time_t t;
  I_U32 duration = 0;
  char fanTray[16] = {0};

  I_U8 fileAddress[100] = {0} ;
  char time2[200] = {0};
  char *time1 = NULL;
  I_U16 timelen = 0;

  LOG_PRINT(INFO,"Entering Function: : %s ErrCode [%d]",__func__,((sDiagnosticResult*)BpmRespPtr)->errCode);

  /* If Test is canceled from User */
  if(action == E_ACTION_DIAG_TEST_CANCEL)
  {
    if(strcmp((char *)libGlobalParam.fileName, "NULL") != 0) 
    {
      /* delete existing file */
      strcpy((char *)fileAddress, (char *)libGlobalParam.filePath);
      strcat((char *)fileAddress, (char *)libGlobalParam.fileName);
      remove((char *)fileAddress);
    }
    /* make new file and update */
    t = time(NULL);
    local = gmtime(&t);
    LOG_PRINT(LOG_INFO,"UTC time and date: %s\n", asctime(local));

    sprintf((char *)libGlobalParam.fileName,"%s_%d_R%d_%s", 
        libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType],
        ((sDiagnosticResult*)BpmRespPtr)->testID, 
        ((sDiagnosticResult*)BpmRespPtr)->testRef,
        libGlobalParam.testResultString[TEST_CANCEL]);

    strcpy((char *)fileAddress, (char *)libGlobalParam.filePath);
    strcat((char *)fileAddress, (char *)libGlobalParam.fileName);
    remove((char *)fileAddress);
    if((filePtr = fopen((char *)fileAddress, "w")) == NULL)
    {
      LOG_PRINT(CRITICAL,"fopen %s failed ",fileAddress);
      return 0;
    }

    switch(libGlobalParam.ApiId)
    {
      case OAMS_OBJTYPE_ICC:
        {
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'ICC' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  Result : Fail \n\n", 
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_EIC:
        {
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'EIC' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec Result : Fail \n\n",
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_PSU:
        {   
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Start*/
          /*
          if(((sDiagnosticResult*)BpmRespPtr)->slotID == PSU0)
          {
            ((sDiagnosticResult*)BpmRespPtr)->slotID =  1 ;
          }
          else if(((sDiagnosticResult*)BpmRespPtr)->slotID == PSU1)
          {
            ((sDiagnosticResult*)BpmRespPtr)->slotID =  2 ;
          }
          */
          
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Start*/
          ((sDiagnosticResult*)BpmRespPtr)->slotID = REPLACEPSUSLOTID(((sDiagnosticResult*)BpmRespPtr)->slotID);
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Ends*/

          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'Power Supply Unit' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  "
              "Result : Fail \n\n",
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);


          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_FANTRAY:
        {
          /*((sDiagnosticResult*)BpmRespPtr)->slotID == 1 is for FAN_TRAY_NORTH, as per the request message sent to BPM */
          if( ((sDiagnosticResult*)BpmRespPtr)->slotID == 1 )
          {
            strcpy(fanTray,"FAN_TRAY_NORTH");
          }
          else
          {
            strcpy(fanTray,"FAN_TRAY_SOUTH");
          }
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          /*
             fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
             "'Fan Tray' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  Result : Fail \n\n",
             libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
             libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
             ((sDiagnosticResult*)BpmRespPtr)->frameID, 
             ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
           */
          fprintf(filePtr,"Summary: Test Case: Test Type \"%s\" TestId \"%s\" executed on "
              "\"%s\" FrameId \"%d\" UTC Time %s Duration: %dsec Result : Fail \n\n",
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID],
              fanTray, ((sDiagnosticResult*)BpmRespPtr)->frameID, time2, duration);

          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_OBM:
        {
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'OBM' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  Result : Fail \n\n", 
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_OBF:
        {
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'OBF' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  Result : Fail \n\n", 
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      default:
        {
          LOG_PRINT(CRITICAL,"Wrong ApiId file opration failed ");
          if(filePtr != NULL)
          {
            fclose(filePtr);
          }
          return 0;
        }
        break;
    }/*switch(libGlobalParam.ApiId) */

    fprintf(filePtr, "\nDetails: \n<TestCase %s>\n",libGlobalParam.testResultString[TEST_CANCEL]);
    fflush(filePtr);

    if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
    {
      /* Print ErrCode String returned from BPM */
      printErrCode(BpmRespPtr);
    }

    if(filePtr != NULL)
    {
      fclose(filePtr);
    }
    return 1;
  }
  if((testResult == TEST_ABORT) || (testResult == TEST_CANCEL))
  {
    if(strcmp((char *)libGlobalParam.fileName, "NULL") != 0) 
    {
      /* delete existing file */
      strcpy((char *)fileAddress, (char *)libGlobalParam.filePath);
      strcat((char *)fileAddress, (char *)libGlobalParam.fileName);
      remove((char *)fileAddress);
    }
    /* make new file and update */
    t = time(NULL);
    local = gmtime(&t);
    LOG_PRINT(LOG_INFO,"UTC time and date: %s\n", asctime(local));
    /* NOTE: If TestCase not Supported then filename is suffixed by Completed */
    if(((sDiagnosticResult*)BpmRespPtr)->errCode == ERROR_TEST_NOT_SUPPORTED)
    {
      sprintf((char *)libGlobalParam.fileName,"%s_%d_R%d_%s", 
          libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType],
          ((sDiagnosticResult*)BpmRespPtr)->testID, 
          ((sDiagnosticResult*)BpmRespPtr)->testRef,
          libGlobalParam.testResultString[TEST_COMPLETE]);
    }
    else
    {
      sprintf((char *)libGlobalParam.fileName,"%s_%d_R%d_%s", 
          libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType],
          ((sDiagnosticResult*)BpmRespPtr)->testID, 
          ((sDiagnosticResult*)BpmRespPtr)->testRef,
          libGlobalParam.testResultString[testResult]);
    }
    strcpy((char *)fileAddress, (char *)libGlobalParam.filePath);
    strcat((char *)fileAddress, (char *)libGlobalParam.fileName);
    remove((char *)fileAddress);
    if((filePtr = fopen((char *)fileAddress, "w")) == NULL)
    {
      LOG_PRINT(CRITICAL,"fopen %s failed ",fileAddress);
      return 0;
    }

    switch(libGlobalParam.ApiId)
    {
      case OAMS_OBJTYPE_ICC:
        {
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'ICC' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  Result : Fail \n\n", 
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_EIC:
        {
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';

          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'EIC' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec Result : Fail \n\n",
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_PSU:
        {
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Start*/
          /*
          if(((sDiagnosticResult*)BpmRespPtr)->slotID == PSU0)
          {
            ((sDiagnosticResult*)BpmRespPtr)->slotID =  1 ;
          }
          else if(((sDiagnosticResult*)BpmRespPtr)->slotID == PSU1)
          {
            ((sDiagnosticResult*)BpmRespPtr)->slotID =  2 ;
          }
          */
          
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Start*/
          ((sDiagnosticResult*)BpmRespPtr)->slotID = REPLACEPSUSLOTID(((sDiagnosticResult*)BpmRespPtr)->slotID);
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Ends*/

          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'Power Supply Unit' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  "
              "Result : Fail \n\n",
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);

          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_FANTRAY:
        {
          /*((sDiagnosticResult*)BpmRespPtr)->slotID == 1 is for FAN_TRAY_NORTH, as per the request message sent to BPM */
          if( ((sDiagnosticResult*)BpmRespPtr)->slotID == 1 )
          {
            strcpy(fanTray,"FAN_TRAY_NORTH");
          }
          else
          {
            strcpy(fanTray,"FAN_TRAY_SOUTH");
          }
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          /*
             fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
             "'Fan Tray' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  Result : Fail \n\n",
             libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
             libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
             ((sDiagnosticResult*)BpmRespPtr)->frameID, 
             ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
           */  
          fprintf(filePtr,"Summary: Test Case: Test Type \"%s\" TestId \"%s\" executed on "
              "\"%s\" FrameId \"%d\" UTC Time %s Duration: %dsec Result : Fail \n\n",
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID],
              fanTray, ((sDiagnosticResult*)BpmRespPtr)->frameID, time2, duration);

          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_OBM:
        {
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'OBM' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  Result : Fail \n\n", 
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      case OAMS_OBJTYPE_OBF:
        {
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'OBF' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  Result : Fail \n\n", 
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
        }
        break;
      default:
        {
          LOG_PRINT(CRITICAL,"Wrong ApiId file opration failed ");
          if(filePtr != NULL)
          {
            fclose(filePtr);
          }
          return 0;
        }
        break;
    }/*switch(libGlobalParam.ApiId) */

    fprintf(filePtr, "\nDetails: \n<TestCase %s>\n",libGlobalParam.testResultString[testResult]);
    fflush(filePtr);

    if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
    {
      /* Print ErrCode String returned from BPM */
      printErrCode(BpmRespPtr);
    }

    if(filePtr != NULL)
    {
      fclose(filePtr);
    }
    return 1;
  }

  if(strcmp((char *)libGlobalParam.fileName, "NULL") == 0)
  {

    t = time(NULL);
    local = gmtime(&t);


    /* If testrepetition is one */
    gTestFail = 0;
    if(((sDiagnosticResult*)BpmRespPtr)->testResult == TEST_FAIL)
    {
      gTestFail = 1;
    }
    LOG_PRINT(LOG_INFO,"UTC time and date: %s\n", asctime(local));
    sprintf((char *)libGlobalParam.fileName,"%s_%d_R%d_%s", 
        libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType],
        ((sDiagnosticResult*)BpmRespPtr)->testID, 
        ((sDiagnosticResult*)BpmRespPtr)->testRef,
        libGlobalParam.testResultString[testResult]);
    strcpy((char *)fileAddress, (char *)libGlobalParam.filePath);
    strcat((char *)fileAddress, (char *)libGlobalParam.fileName);
    remove((char *)fileAddress);
    if((filePtr = fopen((char *)fileAddress, "w")) == NULL)
    {
      LOG_PRINT(CRITICAL,"fopen %s failed ",fileAddress);
      return 0;
    }

    switch(libGlobalParam.ApiId)
    {
      case OAMS_OBJTYPE_ICC:
        {
          time1 = asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'ICC' card Frame Id  \"%d\"  SlotId \"%d\" UTC Time %s Duration: %dsec Result : Pass \n\n", 
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
          fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
          fflush(filePtr);
          if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
          {
            /* Print ErrCode String returned from BPM */
            printErrCode(BpmRespPtr);
          }
          else
          {
            writeIccDetailInFile( BpmRespPtr);
          }
        }
        break;
      case OAMS_OBJTYPE_EIC:
        {
          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';

          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'EIC' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec Result : Pass \n\n",
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2,duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
          fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
          fflush(filePtr);
          if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
          {
            /* Print ErrCode String returned from BPM */
            printErrCode(BpmRespPtr);
          }
          else
          {
            writeEicDetailInFile(BpmRespPtr);
          }
        }
        break;
      case OAMS_OBJTYPE_PSU:
        {

          /*Adding follwing structure to print data part received from platform via OIL*/
          sPsuVoltThermStatus psuData ;
          memcpy(&psuData, &(((sDiagnosticResult*)BpmRespPtr)->data),sizeof(sPsuVoltThermStatus));

          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Start*/
          /*
          if(((sDiagnosticResult*)BpmRespPtr)->slotID == PSU0)
          {
            ((sDiagnosticResult*)BpmRespPtr)->slotID =  1 ;
          }
          else if(((sDiagnosticResult*)BpmRespPtr)->slotID == PSU1)
          {
            ((sDiagnosticResult*)BpmRespPtr)->slotID =  2 ;
          }
          */
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Ends*/
         
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Start*/
          ((sDiagnosticResult*)BpmRespPtr)->slotID = REPLACEPSUSLOTID(((sDiagnosticResult*)BpmRespPtr)->slotID);
          /* Convert BPM SlotID PSU(E,F) to CFG(1,2) MantisId -0029835 Ends*/
        
          /*
             fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on 
             'Power Supply Unit' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s \
Duration: %dsec  Result : Pass \n\n",
libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
((sDiagnosticResult*)BpmRespPtr)->frameID, 
((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
           */
          /* Changes done for matisId - 0029838 Starts*/
          if ( ( ((sDiagnosticResult*)BpmRespPtr)->testID == TEST_ID_PSU_ALL ) )
          {
            fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
                "'Power Supply Unit' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec "
                "Voltage Status, PSU & ICC Connectivity Result : Pass \n\n",
                libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
                libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
                ((sDiagnosticResult*)BpmRespPtr)->frameID, 
                ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          }
          else if( ( ((sDiagnosticResult*)BpmRespPtr)->testID == TEST_ID_PSU_1 ) )
          {
            fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
                "'Power Supply Unit' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec "
                "Voltage Status Result : Pass \n\n",
                libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
                libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
                ((sDiagnosticResult*)BpmRespPtr)->frameID, 
                ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);

          }
          else
          {
            fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
                "'Power Supply Unit' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec "
                "PSU & ICC Connectivity Result : Pass \n\n",
                libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
                libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
                ((sDiagnosticResult*)BpmRespPtr)->frameID, 
                ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          }
          /* Changes done for matisId - 0029838 Ends*/
          /* Write data buffered in user-space */
          fflush(filePtr);
          fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
          fflush(filePtr);
          /*writing data of for voltage and other details received from PM*/
          /* Changes for mantis Id - 0029834 Start  */
          if ( (((sDiagnosticResult*)BpmRespPtr)->testID == TEST_ID_PSU_ALL) || 
              (((sDiagnosticResult*)BpmRespPtr)->testID == TEST_ID_PSU_1) )
          {
            fprintf(filePtr,"sp_3P3Aux: %d\n",psuData.sp_3P3Aux);
            fflush(filePtr);
            fprintf(filePtr,"sp_cardTop: %d\n",psuData.sp_cardTop);
            fflush(filePtr);
            fprintf(filePtr,"sp_28VPM1: %d\n",psuData.sp_28VPM1);   
            fflush(filePtr);
            fprintf(filePtr,"sp_3P3PM2: %d\n",psuData.sp_3P3PM2); 
            fflush(filePtr);
          }


          /* Changes for mantis Id - 0029834 Ends  */
          if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
          {
            /* Print ErrCode String returned from BPM */
            printErrCode(BpmRespPtr);
          }
          else
          {
            writePsuDetailInFile(BpmRespPtr);
          }
        }
        break;
      case OAMS_OBJTYPE_FANTRAY:
        {
          /*Adding follwing structure to print data part received from platform via OIL*/
          I_U8 fanIndex = 0;
          sFanTrayAllTestResult fanTrayData;
          memcpy(&fanTrayData, &(((sDiagnosticResult*)BpmRespPtr)->data),sizeof(sFanTrayAllTestResult)); 

          time1 = (char *)asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          /*
             fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on \
             'Fan Tray' card Frame Id  \"%d\"  SlotId \"%d\"  UTC Time %s Duration: %dsec  Result : Pass \n\n",
             libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
             libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
             ((sDiagnosticResult*)BpmRespPtr)->frameID, 
             ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
           */

          /*((sDiagnosticResult*)BpmRespPtr)->slotID == 1 is for FAN_TRAY_NORTH, as per the request message sent to BPM Mantis- 29833,29834, 29745 */
          if( ((sDiagnosticResult*)BpmRespPtr)->slotID == 1 )
          {
            strcpy(fanTray,"FAN_TRAY_NORTH");
          }
          else
          {
            strcpy(fanTray,"FAN_TRAY_SOUTH");
          }
          if( ( ((sDiagnosticResult*)BpmRespPtr)->testID == TEST_ID_FAN_ALL )  )
          {
            fprintf(filePtr,"Summary: Test Case: Test Type \"%s\" TestId \"%s\" executed on "
                "\"%s\" FrameId \"%d\" UTC Time %s Duration: %dsec "
                "Fanspeed, FanTray&ICC Connectivity Result : Pass\n\n",
                libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
                libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID],
                fanTray, ((sDiagnosticResult*)BpmRespPtr)->frameID, time2, duration);
          }
          else if( ( ((sDiagnosticResult*)BpmRespPtr)->testID == TEST_ID_FAN_1 ) )
          {
            fprintf(filePtr,"Summary: Test Case: Test Type \"%s\" TestId \"%s\" executed on "
                "\"%s\" FrameId \"%d\" UTC Time %s Duration: %dsec Fanspeed "
                "Result : Pass\n\n",
                libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
                libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
                fanTray, ((sDiagnosticResult*)BpmRespPtr)->frameID, time2, duration);
          } 
          else
          {
            fprintf(filePtr, "Summary: Test Case: Test Type \"%s\" TestId \"%s\" executed on "
                "\"%s\" FrameId \"%d\" UTC Time %s Duration: %dsec "
                "FanTray&ICC Connectivity Result : Pass\n\n",
                libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
                libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
                fanTray, ((sDiagnosticResult*)BpmRespPtr)->frameID, time2, duration);
          }
          fflush(filePtr);
          /* Write data buffered in user-space */
          fflush(filePtr);
          fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
          fflush(filePtr);

          /* Changes for mantis Id - 0029834 Start  */
          if( (((sDiagnosticResult*)BpmRespPtr)->testID == TEST_ID_FAN_ALL) 
              || (((sDiagnosticResult*)BpmRespPtr)->testID == TEST_ID_FAN_1) )
          {
            /*((sDiagnosticResult*)BpmRespPtr)->slotID == 1 is for NORTH FANTRAY and 
              ((sDiagnosticResult*)BpmRespPtr)->slotID == 2 is for SOUTH FANTRAY*/
            if( ((sDiagnosticResult*)BpmRespPtr)->slotID == 1 )
            {
              for(fanIndex = 6;fanIndex < 8 ;fanIndex++)
              {
                fprintf(filePtr, "Fan[%d] Speed: %d\n",fanIndex+1,fanTrayData.changeFanSpeed.Speed[fanIndex]);  
                fflush(filePtr);
              }
            }
            else
            {
              for(fanIndex = 0;fanIndex < 6 ;fanIndex++)
              {
                fprintf(filePtr, "Fan[%d] Speed: %d\n",fanIndex+1,fanTrayData.changeFanSpeed.Speed[fanIndex]);  
                fflush(filePtr);
              } 
            }

          }
          /* Changes for mantis Id - 0029834 Ends  */
          if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
          {
            /* Print ErrCode String returned from BPM */
            printErrCode(BpmRespPtr);
          }
          else
          {
            writeFanTrayDetailInFile(BpmRespPtr);
          }
        }
        break;
      case OAMS_OBJTYPE_OBM:
        {
          time1 = asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'OBM' card Frame Id  \"%d\"  SlotId \"%d\" UTC Time %s Duration: %dsec Result : Pass \n\n", 
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
          fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
          fflush(filePtr);
          if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
          {
            /* Print ErrCode String returned from BPM */
            printErrCode(BpmRespPtr);
          }
          else
          {
            writeObmDetailInFile( BpmRespPtr);
          }
        }
        break;
      case OAMS_OBJTYPE_OBF:
        {
          time1 = asctime(local);
          timelen = strlen(time1);
          memcpy(time2,time1,timelen);
          time2[timelen-1]='\0';
          fprintf(filePtr, "Summary: Test Case: Test Type \"%s\"  TestId  \"%s\" executed on "
              "'OBF' card Frame Id  \"%d\"  SlotId \"%d\" UTC Time %s Duration: %dsec Result : Pass \n\n", 
              libGlobalParam.TCT_String[((sDiagnosticResult*)BpmRespPtr)->testType], 
              libGlobalParam.TCID_String[((sDiagnosticResult*)BpmRespPtr)->testID], 
              ((sDiagnosticResult*)BpmRespPtr)->frameID, 
              ((sDiagnosticResult*)BpmRespPtr)->slotID, time2, duration);
          /* Write data buffered in user-space */
          fflush(filePtr);
          fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
          fflush(filePtr);
          if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
          {
            /* Print ErrCode String returned from BPM */
            printErrCode(BpmRespPtr);
          }
          else
          {
            writeObfDetailInFile( BpmRespPtr);
          }
        }
        break;
      default:
        {
          LOG_PRINT(CRITICAL,"Wrong ApiId file opration failed ");
          if(filePtr != NULL)
          {
            fclose(filePtr);
          }
          return 0;
        }
        break;
    }/*switch(libGlobalParam.ApiId) */
    if(filePtr != NULL)
    {
      fclose(filePtr);
    }
  }        
  else /* If repetition is more than one */
  {
    if(((sDiagnosticResult*)BpmRespPtr)->testResult == TEST_FAIL)
    {
      /* If repetition Result is Fail */
      gTestFail = 1;
    }
    strcpy((char *)fileAddress, (char *)libGlobalParam.filePath);
    strcat((char *)fileAddress, (char *)libGlobalParam.fileName);
    if((filePtr = fopen((char *)fileAddress, "a")) == NULL)
    {
      LOG_PRINT(CRITICAL,"fopen %s failed ",fileAddress);
      return 0;
    }
    switch(libGlobalParam.ApiId)
    {
      case OAMS_OBJTYPE_ICC:
        fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
        if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
        {
          /* Print ErrCode String returned from BPM */
          printErrCode(BpmRespPtr);
        }
        else
        {
          writeIccDetailInFile(BpmRespPtr);
        }
        break;
      case OAMS_OBJTYPE_EIC:
        fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
        if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
        {
          /* Print ErrCode String returned from BPM */
          printErrCode(BpmRespPtr);
        }
        else
        {
          writeEicDetailInFile(BpmRespPtr);
        }
        break;
      case OAMS_OBJTYPE_PSU:

        fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
        if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
        {
          /* Print ErrCode String returned from BPM */
          printErrCode(BpmRespPtr);
        }
        else
        {
          writePsuDetailInFile(BpmRespPtr);
        }
        break;
      case OAMS_OBJTYPE_FANTRAY:
        fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
        if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
        {
          /* Print ErrCode String returned from BPM */
          printErrCode(BpmRespPtr);
        }
        else
        {
          writeFanTrayDetailInFile(BpmRespPtr);
        }
        break;
      case OAMS_OBJTYPE_OBM:
        fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
        if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
        {
          /* Print ErrCode String returned from BPM */
          printErrCode(BpmRespPtr);
        }
        else
        {
          writeObmDetailInFile(BpmRespPtr);
        }
        break;
      case OAMS_OBJTYPE_OBF:
        fprintf(filePtr, "\nDetails: \n<Repetition  %d>\n",libGlobalParam.repititionCnt);
        if(((sDiagnosticResult*)BpmRespPtr)->errCode != 0)
        {
          /* Print ErrCode String returned from BPM */
          printErrCode(BpmRespPtr);
        }
        else
        {
          writeObfDetailInFile(BpmRespPtr);
        }
        break;
      default: 
        LOG_PRINT(CRITICAL,"Wrong object type file opration failed ");
        return 0;
        break;
    }
    /* Since we are opening in append mode for each repetition */
    if(filePtr != NULL)
    {
      fclose(filePtr);
    }
  }
  return 1;
}

I_U32 getCardSerialNum(I_U32 slotId, I_U32 frameId, I_U8* cardSerialNum)
{
  I_S32 dbSts;
  IccCardInfoTableIndices iccCardInfoTableIndices;
  EicCardInfoTableIndices eicCardInfoTableIndices;
  PowerSupplyInfoTableIndices powerSupplyInfoTableIndices;

  I_S16 rowSize = 0;
  I_S32 rowCount = 0;

  EicCardInfoTableApi     *eicCardInfoTableApi;
  PowerSupplyInfoTableApi *powerSupplyInfoTableApi;
  IccCardInfoTableApi     *iccCardInfoTableApi;

  iccCardInfoTableApi = NULL;
  eicCardInfoTableApi = NULL;
  powerSupplyInfoTableApi = NULL;

  if((slotId == ICC0) || (slotId == ICC1))
  {
    iccCardInfoTableIndices.chasisFrameId = frameId;
    iccCardInfoTableIndices.slotId = slotId;
    /* do icc card info get query */
    dbSts = clib_get((I_S32)SCM_DAO_ICCCARDINFOTABLE, (I_S32)SCM_MET_GET_ICCCARDINFOTABLE,
        (I_PVoid)&iccCardInfoTableIndices,(I_S16)sizeof(IccCardInfoTableIndices),(I_PVoid*)&iccCardInfoTableApi,(I_S16 *)&rowSize,(I_S32 *)&rowCount);

    if(dbSts != CLIB_SUCCESS)
    {
      LOG_PRINT(CRITICAL,"DB get fail");
      return 0;
    }
    else
    {
      if((cardSerialNum == NULL) || (iccCardInfoTableApi->cardSerialNumber == NULL))
      {
        LOG_PRINT(CRITICAL,"cardSerialNum is NULL");
        free(iccCardInfoTableApi);
        return 0;
      }
      memcpy(cardSerialNum,iccCardInfoTableApi->cardSerialNumber, 20);
      cardSerialNum[CARD_SERIAL_NUM_SIZE] = '\0';
      free(iccCardInfoTableApi);
      return 1;
    }
  }
  else if((slotId == EIC0) || (slotId == EIC1))
  {
    /* do eic card info get query */
    eicCardInfoTableIndices.chasisFrameId = frameId;
    eicCardInfoTableIndices.slotId = slotId;
    dbSts = clib_get((I_S32)SCM_DAO_EICCARDINFOTABLE, (I_S32)SCM_MET_GET_EICCARDINFOTABLE,
        (I_PVoid)&eicCardInfoTableIndices,(I_S16)sizeof(EicCardInfoTableIndices),(I_PVoid*)&eicCardInfoTableApi,(I_S16 *)&rowSize,(I_S32 *)&rowCount);

    if(dbSts != CLIB_SUCCESS)
    {
      LOG_PRINT(CRITICAL,"DB get fail");
      return 0;
    }
    else
    {
      if((cardSerialNum == NULL) || (eicCardInfoTableApi->cardSerialNumber == NULL))
      {
        LOG_PRINT(CRITICAL,"cardSerialNum is NULL");
        free(eicCardInfoTableApi);
        return 0;
      }
      memcpy(cardSerialNum,eicCardInfoTableApi->cardSerialNumber, 20);
      cardSerialNum[CARD_SERIAL_NUM_SIZE] = '\0';
      free(eicCardInfoTableApi);
      return 1;
    }
  }
  else if((slotId == 1) || (slotId == 2))
  {
    /* do psu card info query */

    powerSupplyInfoTableIndices.chasisFrameId = frameId;
    powerSupplyInfoTableIndices.slotId = slotId;
    dbSts = clib_get((I_S32)SCM_DAO_POWERSUPPLYINFOTABLE, (I_S32)SCM_MET_GET_POWERSUPPLYINFOTABLE,
        (I_PVoid)&powerSupplyInfoTableIndices,(I_S16)sizeof(PowerSupplyInfoTableIndices),(I_PVoid*)&powerSupplyInfoTableApi,(I_S16 *)&rowSize,(I_S32 *)&rowCount);

    if(dbSts != CLIB_SUCCESS)
    {
      LOG_PRINT(CRITICAL,"DB get fail");
      return 0;
    }
    else
    {
      if((cardSerialNum == NULL) || (powerSupplyInfoTableApi->cardSerialNumber == NULL))
      {
        LOG_PRINT(CRITICAL,"cardSerialNum is NULL");
        free(powerSupplyInfoTableApi);
        return 0;
      }
      memcpy(cardSerialNum,powerSupplyInfoTableApi->cardSerialNumber, 20);
      cardSerialNum[CARD_SERIAL_NUM_SIZE] = '\0';
      free(powerSupplyInfoTableApi);
      return 1;
    }
  }
  LOG_PRINT(CRITICAL,"getCardSerialNum: Invalid SlotId [%d]",slotId);
  return 0;
}
//Changed for 1U Diagnostics
I_U32 getCardSerialNum1U(I_U32 slotId, I_U32 frameId, I_U8* cardSerialNum)
{
  I_S32 dbSts;
  ObmCardInfoTableIndices obmCardInfoTableIndices;
  I_S16 rowSize = 0;
  I_S32 rowCount = 0;
  ObmCardInfoTableApi *obmCardInfoTableApi=NULL;
  if((slotId == SLOTID_1_1U) || (slotId == SLOTID_2_1U))
  {
    obmCardInfoTableIndices.chasisFrameId = frameId;
    obmCardInfoTableIndices.slotID = slotId;
    dbSts = clib_get((I_S32)SCM_DAO_OBMCARDINFOTABLE, (I_S32)SCM_MET_GET_OBMCARDINFOTABLE,
        (I_PVoid)&obmCardInfoTableIndices,(I_S16)sizeof(obmCardInfoTableIndices),(I_PVoid*)&obmCardInfoTableApi,(I_S16 *)&rowSize,(I_S32 *)&rowCount);

    if(dbSts != CLIB_SUCCESS)
    {
      LOG_PRINT(CRITICAL,"DB get fail");
      return 0;
    }
    else
    {
      if((cardSerialNum == NULL) || (obmCardInfoTableApi->cardSerialNumber == NULL))
      {
        LOG_PRINT(CRITICAL,"cardSerialNum is NULL");
        free(obmCardInfoTableApi);
        return 0;
      }
      memcpy(cardSerialNum,obmCardInfoTableApi->cardSerialNumber, 20);
      //cardSerialNum[CARD_SERIAL_NUM_SIZE] = '\0';
      cardSerialNum[20] = '\0';
      free(obmCardInfoTableApi);
      return 1;
    }
  }
  LOG_PRINT(CRITICAL,"getCardSerialNum: Invalid SlotId [%d]",slotId);
  return 0;
}
//Changed for 1U Diagnostics
I_S8 *replace(I_S8 *st, I_S8 *orig, I_S8 *repl) {

  //  static I_S8 buffer[200];

  /*Fix for mantisId 0029809 */
  static I_S8 buffer[300];

  I_S8 *ch;
  if (!(ch = strstr(st, orig)))
    return st;
  strncpy(buffer, st, ch-st);
  buffer[ch-st] = 0;
  sprintf(buffer+(ch-st), "%s%s", repl, ch+strlen(orig));
  return buffer;
}

void doFileResultManipulation(I_U32 slotId, I_U32 frameId)
{
  I_U8 t[20]={0};
  I_S8 chari;
  I_U32 count =0;
  I_U8 cardSerialNum[20];
  I_U8 fileAddress[100];
  size_t len;
  ssize_t read;
  ssize_t buffLen = 0;
  I_S8 *buff=NULL;
  I_S8 *buff_new;
  I_S8 duration[20];

  memset(t,0,20);
  memset(duration,0,20);

  /* Open File */
  strcpy((char *)fileAddress, (char *)libGlobalParam.filePath);
  strcat((char *)fileAddress, (char *)libGlobalParam.fileName);

  if((filePtr = fopen((char *)fileAddress, "r+")) == NULL)
  {
    LOG_PRINT(CRITICAL,"fopen %s failed ",fileAddress);
    return;
  }
  LOG_PRINT(CRITICAL, "%s",fileAddress);

  if(filePtr ==NULL) {
    LOG_PRINT(CRITICAL, "File open failed for result manipulaiton");
    exit(1);
  }
  /*Test for mantisId 0029809 Starts*/


  /*Test for mantisId 0029809 Ends*/
  /* Replace the duration in Report File with the calculated time */
  read = getline(&buff,&len,filePtr);
  sprintf(duration,"%dsec",libGlobalParam.duration);
  LOG_PRINT(CRITICAL,"DiagLib:Duration[%d] String[%s]",libGlobalParam.duration, duration);
  LOG_PRINT(CRITICAL,"DiagLib:Orig Buff[%s]",buff);
  buff_new = replace(buff, "0sec", duration);
  rewind(filePtr);
  LOG_PRINT(CRITICAL,"DiagLib:Changed Buff[%s]",buff_new);
  fputs(buff_new,filePtr);
  fflush(filePtr);
  rewind(filePtr);
  fflush(filePtr);

  /* Update the Summary Result only if errCode is not Zero */
  if( libGlobalParam.errCode )
  {
    while(strcmp((char *)t, "Result") != 0)
    {

      chari = fgetc(filePtr);
      if(chari == EOF)
      {
        count=0;
        if(filePtr != NULL)
        {
          fclose(filePtr);
        }
        return;
      }
      memset(t,0,20);
      while (chari == ' '){chari = fgetc(filePtr);}
      t[count]=chari;
      while(((chari != ' ')&&(chari != '\n')&&(chari != '\t') && (chari !=EOF)))
      {
        count++;
        chari = fgetc(filePtr);
        if(((chari == ' ') || (chari == '\n')||(chari == '\t') || (chari ==EOF)))
        {
          t[count] = '\0';
          count=0;
          break;
        }
        t[count]=chari;
      } 
      count=0;
    }
    ungetc(1,filePtr);
    /* If any of the repetition in Test case is Failed then set Summary Result is Fail */
    if(gTestFail == 1)
    {
      fprintf(filePtr, " : Fail");
      fflush(filePtr);
    }
  }

  fseek(filePtr, 0L, SEEK_END);
  fflush(filePtr);

  /* Update HW Serial Number at the End */
  //if((getCardSerialNum(slotId, frameId, cardSerialNum)) == 1)
  if((getCardSerialNum1U(slotId, frameId, cardSerialNum)) == 1)
  {
    //if(libGlobalParam.ApiId != OAMS_OBJTYPE_FANTRAY)
    //Changed for 1U Diagnostics
    if(libGlobalParam.ApiId == OAMS_OBJTYPE_OBM)
    //Changed for 1U Diagnostics
    {
      fprintf(filePtr, "\nHardware Serial Number:  %s \n\n", cardSerialNum);
      fflush(filePtr);
    }
  } 

  if(filePtr != NULL)
  {
    fclose(filePtr);
  }
}

void printErrCode(void *BpmRespPtr)
{
  I_U32 errCode = ((sDiagnosticResult*)BpmRespPtr)->errCode;

  if((errCode >= ERR_CODE_DIAG_BASE) && 
      (errCode <= ERR_CODE_DIAG_END))
  {
    fprintf(filePtr, "\n<ERROR_CODE: %s[%d]>\n",libGlobalParam.errCodeString[errCode - ERR_CODE_DIAG_BASE],errCode);
    fflush(filePtr);
  }
  else if((errCode >= OAM_BPM_MF_ERROR_BASE) &&
      (errCode <= ERR_SYSTEMTYPE_INVALID))
  {
    fprintf(filePtr, "\n<ERROR_CODE: %s[%d]>\n",libGlobalParam.errCodeString[errCode - ERR_CODE_FRAMER_BASE],errCode);
    fflush(filePtr);
  }
  else if(errCode == BPM_FAILURE)
  {
    fprintf(filePtr, "\n<ERROR_CODE: BPM_FAILURE>\n");
    fflush(filePtr);
  }
  else
  {
    fprintf(filePtr, "\n<ERROR_CODE: UNDEFINED ERROR_CODE_STRING(%d)>\n",errCode);
    fflush(filePtr);
  }
}
