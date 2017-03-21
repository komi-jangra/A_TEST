#include "bpmDiaglib.h"
#include "bpmInclude.h"
extern FILE *filePtr; 
extern sLibGlobalParam libGlobalParam;
extern sParamKeySet paramKeySet[MAX_TCT_ID][MAX_TEST_ID];



void writePsuDetailInFile(void *BpmRespPtr)
{
  if(libGlobalParam.suppress)
  {
  }
  else
  {
    switch(((sDiagnosticResult*)BpmRespPtr)->testType)
    {
      case DIAGNOS_TCT_PSU:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_PSU_ALL:
            case TEST_ID_PSU_1:
            case TEST_ID_PSU_2:
              {
                /* cp post string prepairation */
                {
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
                LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for PSU ", 
                    ((sDiagnosticResult*)BpmRespPtr)->testID);
                break;
              }
          }
          break;
        }

      default:
        LOG_PRINT(CRITICAL,"DiagLib: TEST TYPE '%d' not defined for PSU", 
            ((sDiagnosticResult*)BpmRespPtr)->testType);
        break;
    }
  }


}
