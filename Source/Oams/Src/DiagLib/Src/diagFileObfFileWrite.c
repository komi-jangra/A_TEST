#include "bpmDiaglib.h"
#include "bpmInclude.h"
extern FILE *filePtr; 
extern sLibGlobalParam libGlobalParam;
extern sParamKeySet paramKeySet[MAX_TCT_ID][MAX_TEST_ID];



void writeObfDetailInFile(void *BpmRespPtr)
{
  if(libGlobalParam.suppress)
  {
  }
  else
  {
    switch(((sDiagnosticResult*)BpmRespPtr)->testType)
    {
      case DIAGNOS_TCT_OBF:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            //case TEST_ID_OBF_ALL:
            case TEST_ID_OBF_1:
            //case TEST_ID_OBF_2:
              {
                sObfDiag *obfDiag;
                obfDiag = (sObfDiag *)(((sDiagnosticResult*)BpmRespPtr)->data);
                /* cp post string prepairation */
                { 
                  if(obfDiag->obfAPresence == PRESENT)
                  {
                   fprintf(filePtr, "\n OBF A Presence: PRESENT\n");
                  }
                  else
                  {
                   fprintf(filePtr, "\n OBF A Presence: NOT_PRESENT\n");
                  }
                  if(obfDiag->obfBPresence == PRESENT)
                  {
                   fprintf(filePtr, "\n OBF B Presence: PRESENT\n");
                  }
                  else
                  {
                   fprintf(filePtr, "\n OBF B Presence: NOT_PRESENT\n");
                  }
                  if(obfDiag->powerFeedAPresence == PRESENT)
                  {
                   fprintf(filePtr, "\n POWER FEED A Presence : PRESENT\n");
                  }
                  else
                  {
                   fprintf(filePtr, "\n POWER FEED A Presence : NOT_PRESENT\n");
                  }
                  if(obfDiag->powerFeedBPresence == PRESENT)
                  {
                   fprintf(filePtr, "\n POWER FEED B Presence : PRESENT\n");
                  }
                  else
                  {
                   fprintf(filePtr, "\n POWER FEED B Presence : NOT_PRESENT\n");
                  }
		              fflush(filePtr);
                  if(libGlobalParam.errCode != 0)
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                  }

                }
                break;
                default:
                LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for OBF ", 
                    ((sDiagnosticResult*)BpmRespPtr)->testID);
                break;
              }
          }
          break;
        }

      default:
        LOG_PRINT(CRITICAL,"DiagLib: TEST TYPE '%d' not defined for OBF", 
            ((sDiagnosticResult*)BpmRespPtr)->testType);
        break;
    }
  }


}
