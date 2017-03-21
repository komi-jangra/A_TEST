#include "bpmDiaglib.h"
#include "bpmInclude.h"
extern FILE *filePtr; 
extern sLibGlobalParam libGlobalParam;
extern sParamKeySet paramKeySet[MAX_TCT_ID][MAX_TEST_ID];

void writeIccDetailInFile(void *BpmRespPtr)
{
    I_U8 tdm_lsr,i;
 // I_U8 fileAddress[100];
 // fclose(filePtr); /* diag response File */
  
 // strcpy(fileAddress, libGlobalParam.filePath);
 // strcat(fileAddress, libGlobalParam.fileName);
 // filePtr = fopen((I_U8*)fileAddress, "r+");


  if(libGlobalParam.suppress)
  {
  }
  else
  {
    switch(((sDiagnosticResult*)BpmRespPtr)->testType)
    {
      case DIAGNOS_TCT_ICC_GEN:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_GEN_ALL:
              {
                sIccGenResult *iccGenAllResult;
                iccGenAllResult = (sIccGenResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                /* cp post string prepairation */
                {
                  fprintf(filePtr, "\nControl Processor  POST:\n");
                  LOG_PRINT(DEBUG,"writeIccDetailInFile: ICC_GEN Test case");
                  printf("writeIccDetailInFile: ICC_GEN Test case\n\n");
                  fflush(filePtr);
		  switch(iccGenAllResult->postResult.cpPostResult.mem_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Mem Test:                %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.cpPostResult.mem_test]);
			  break;
		      default:
			  fprintf(filePtr," Mem Test:                Invalid Result(%d)\n",iccGenAllResult->postResult.cpPostResult.mem_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.cpPostResult.nand_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Nand Test:               %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.cpPostResult.nand_test]);
			  break;
		      default:
			  fprintf(filePtr," Nand Test:               Invalid Result(%d)\n", iccGenAllResult->postResult.cpPostResult.nand_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.cpPostResult.nvram_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RamDisk Test:            %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.cpPostResult.nvram_test]);
			  break;
		      default:
			  fprintf(filePtr," RamDisk Test:            Invalid Result(%d)\n", iccGenAllResult->postResult.cpPostResult.nvram_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.cpPostResult.fec_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," FCC Test:                %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.cpPostResult.fec_test]);
			  break;
		      default:
			  fprintf(filePtr," FCC Test:                Invalid Result(%d)\n", iccGenAllResult->postResult.cpPostResult.fec_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.cpPostResult.tsec1_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," TSEC Test:               %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.cpPostResult.tsec1_test]);
			  break;
		      default:
			  fprintf(filePtr," TSEC Test:               Invalid Result(%d)\n", iccGenAllResult->postResult.cpPostResult.tsec1_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.cpPostResult.mc_reg_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Register Read Test:   %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.cpPostResult.mc_reg_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Register Read Test:   Invalid Result(%d)\n", iccGenAllResult->postResult.cpPostResult.mc_reg_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.cpPostResult.mc_volt_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Voltage Test:         %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.cpPostResult.mc_volt_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Voltage Test:         Invalid Result(%d)\n", iccGenAllResult->postResult.cpPostResult.mc_volt_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.cpPostResult.rtc_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RTC Test:                %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.cpPostResult.rtc_test]);
			  break;
		      default:
			  fprintf(filePtr," RTC Test:                Invalid Result(%d)\n", iccGenAllResult->postResult.cpPostResult.rtc_test);
			  break;
		  }
                  fprintf(filePtr," Core Frequency:          %Lf MHz\n", iccGenAllResult->interFreq.cpInterFreq.coreFreq);
                  //fprintf(filePtr," Platform Frequency:      %Lf\n", iccGenAllResult->interFreq.cpInterFreq.platFreq);
                  fprintf(filePtr," DDR Frequency:           %Lf MHz\n", iccGenAllResult->interFreq.cpInterFreq.ddrFreq);
                  fprintf(filePtr," Bus Frequency:           %Lf MHz\n", iccGenAllResult->interFreq.cpInterFreq.busFreq);

                  fflush(filePtr);
                }

                /* pp post result */
                {
                  fprintf(filePtr, "\nProtocol Processor  POST:\n");
		  switch(iccGenAllResult->postResult.ppPostResult.mem_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Mem Test:                %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.mem_test]);
			  break;
		      default:
			  fprintf(filePtr," Mem Test:                Invalid Result(%d)\n",iccGenAllResult->postResult.ppPostResult.mem_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.nand_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Nand Test:               %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.nand_test]);
			  break;
		      default:
			  fprintf(filePtr," Nand Test:               Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.nand_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.nvram_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RamDisk Test:            %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.nvram_test]);
			  break;
		      default:
			  fprintf(filePtr," RamDisk Test:            Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.nvram_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.fcc_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," FCC Test:                %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.fcc_test]);
			  break;
		      default:
			  fprintf(filePtr," FCC Test:                Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.fcc_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.fcc_dsp_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," FCC DSP Test:            %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.fcc_dsp_test]);
			  break;
		      default:
			  fprintf(filePtr," FCC DSP Test:            Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.fcc_dsp_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.tsec1_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," TSEC Test:               %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.tsec1_test]);
			  break;
		      default:
			  fprintf(filePtr," TSEC Test:               Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.tsec1_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.mc_reg_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Register Read Test:   %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.mc_reg_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Register Read Test:   Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.mc_reg_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.mc_volt_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Voltage Test:         %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.mc_volt_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Voltage Test:         Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.mc_volt_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.rtc_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RTC Test:                %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.rtc_test]);
			  break;
		      default:
			  fprintf(filePtr," RTC Test:                Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.rtc_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.dsp_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," DSP Test:                %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.dsp_test]);
			  break;
		      default:
			  fprintf(filePtr," DSP Test:                Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.dsp_test);
			  break;
		  }
		  switch(iccGenAllResult->postResult.ppPostResult.framer_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," FRAMER Test:             %s\n", libGlobalParam.TestResp[iccGenAllResult->postResult.ppPostResult.framer_test]);
			  break;
		      default:
			  fprintf(filePtr," FRAMER Test:             Invalid Result(%d)\n", iccGenAllResult->postResult.ppPostResult.framer_test);
			  break;
		  }
                  fprintf(filePtr," Core Frequency:          %Lf MHz\n", iccGenAllResult->interFreq.ppInterFreq.coreFreq);
                  //fprintf(filePtr," Platform Frequency:      %Lf\n", iccGenAllResult->interFreq.ppInterFreq.platFreq);
                  fprintf(filePtr," DDR Frequency:           %Lf MHz\n", iccGenAllResult->interFreq.ppInterFreq.ddrFreq);
                  fprintf(filePtr," Bus Frequency:           %Lf MHz\n", iccGenAllResult->interFreq.ppInterFreq.busFreq);

                  fflush(filePtr);
                }
                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_GEN_1:
              {
                sPostResult *postResult;
                postResult = (sPostResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                /* cp post string prepairation */
                {
                  fprintf(filePtr, "\nControl Processor  POST:\n");
		  switch(postResult->cpPostResult.mem_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Mem Test:                %s\n", libGlobalParam.TestResp[postResult->cpPostResult.mem_test]);
			  break;
		      default:
			  fprintf(filePtr," Mem Test:                Invalid Result(%d)\n",postResult->cpPostResult.mem_test);
			  break;
		  }
		  switch(postResult->cpPostResult.nand_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Nand Test:               %s\n", libGlobalParam.TestResp[postResult->cpPostResult.nand_test]);
			  break;
		      default:
			  fprintf(filePtr," Nand Test:               Invalid Result(%d)\n", postResult->cpPostResult.nand_test);
			  break;
		  }
		  switch(postResult->cpPostResult.nvram_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RamDisk Test:            %s\n", libGlobalParam.TestResp[postResult->cpPostResult.nvram_test]);
			  break;
		      default:
			  fprintf(filePtr," RamDisk Test:            Invalid Result(%d)\n", postResult->cpPostResult.nvram_test);
			  break;
		  }
		  switch(postResult->cpPostResult.fec_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," FCC Test:                %s\n", libGlobalParam.TestResp[postResult->cpPostResult.fec_test]);
			  break;
		      default:
			  fprintf(filePtr," FCC Test:                Invalid Result(%d)\n", postResult->cpPostResult.fec_test);
			  break;
		  }
		  switch(postResult->cpPostResult.tsec1_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," TSEC Test:               %s\n", libGlobalParam.TestResp[postResult->cpPostResult.tsec1_test]);
			  break;
		      default:
			  fprintf(filePtr," TSEC Test:               Invalid Result(%d)\n", postResult->cpPostResult.tsec1_test);
			  break;
		  }
		  switch(postResult->cpPostResult.mc_reg_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Register Read Test:   %s\n", libGlobalParam.TestResp[postResult->cpPostResult.mc_reg_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Register Read Test:   Invalid Result(%d)\n", postResult->cpPostResult.mc_reg_test);
			  break;
		  }
		  switch(postResult->cpPostResult.mc_volt_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Voltage Test:         %s\n", libGlobalParam.TestResp[postResult->cpPostResult.mc_volt_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Voltage Test:         Invalid Result(%d)\n", postResult->cpPostResult.mc_volt_test);
			  break;
		  }
		  switch(postResult->cpPostResult.rtc_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RTC Test:                %s\n", libGlobalParam.TestResp[postResult->cpPostResult.rtc_test]);
			  break;
		      default:
			  fprintf(filePtr," RTC Test:                Invalid Result(%d)\n", postResult->cpPostResult.rtc_test);
			  break;
		  }

		  fflush(filePtr);
                }

                /* pp post result */
                {
                  fprintf(filePtr, "\nProtocol Processor  POST:\n");
		  switch(postResult->ppPostResult.mem_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Mem Test:                %s\n", libGlobalParam.TestResp[postResult->ppPostResult.mem_test]);
			  break;
		      default:
			  fprintf(filePtr," Mem Test:                Invalid Result(%d)\n",postResult->ppPostResult.mem_test);
			  break;
		  }
		  switch(postResult->ppPostResult.nand_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Nand Test:               %s\n", libGlobalParam.TestResp[postResult->ppPostResult.nand_test]);
			  break;
		      default:
			  fprintf(filePtr," Nand Test:               Invalid Result(%d)\n", postResult->ppPostResult.nand_test);
			  break;
		  }
		  switch(postResult->ppPostResult.nvram_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RamDisk Test:            %s\n", libGlobalParam.TestResp[postResult->ppPostResult.nvram_test]);
			  break;
		      default:
			  fprintf(filePtr," RamDisk Test:            Invalid Result(%d)\n", postResult->ppPostResult.nvram_test);
			  break;
		  }
		  switch(postResult->ppPostResult.fcc_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," FCC Test:                %s\n", libGlobalParam.TestResp[postResult->ppPostResult.fcc_test]);
			  break;
		      default:
			  fprintf(filePtr," FCC Test:                Invalid Result(%d)\n", postResult->ppPostResult.fcc_test);
			  break;
		  }
		  switch(postResult->ppPostResult.fcc_dsp_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," FCC DSP Test:            %s\n", libGlobalParam.TestResp[postResult->ppPostResult.fcc_dsp_test]);
			  break;
		      default:
			  fprintf(filePtr," FCC DSP Test:            Invalid Result(%d)\n", postResult->ppPostResult.fcc_dsp_test);
			  break;
		  }
		  switch(postResult->ppPostResult.tsec1_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," TSEC Test:               %s\n", libGlobalParam.TestResp[postResult->ppPostResult.tsec1_test]);
			  break;
		      default:
			  fprintf(filePtr," TSEC Test:               Invalid Result(%d)\n", postResult->ppPostResult.tsec1_test);
			  break;
		  }
		  switch(postResult->ppPostResult.mc_reg_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Register Read Test:   %s\n", libGlobalParam.TestResp[postResult->ppPostResult.mc_reg_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Register Read Test:   Invalid Result(%d)\n", postResult->ppPostResult.mc_reg_test);
			  break;
		  }
		  switch(postResult->ppPostResult.mc_volt_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Voltage Test:         %s\n", libGlobalParam.TestResp[postResult->ppPostResult.mc_volt_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Voltage Test:         Invalid Result(%d)\n", postResult->ppPostResult.mc_volt_test);
			  break;
		  }
		  switch(postResult->ppPostResult.rtc_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RTC Test:                %s\n", libGlobalParam.TestResp[postResult->ppPostResult.rtc_test]);
			  break;
		      default:
			  fprintf(filePtr," RTC Test:                Invalid Result(%d)\n", postResult->ppPostResult.rtc_test);
			  break;
		  }
		  switch(postResult->ppPostResult.dsp_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," DSP Test:                %s\n", libGlobalParam.TestResp[postResult->ppPostResult.dsp_test]);
			  break;
		      default:
			  fprintf(filePtr," DSP Test:                Invalid Result(%d)\n", postResult->ppPostResult.dsp_test);
			  break;
		  }
		  switch(postResult->ppPostResult.framer_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," FRAMER Test:             %s\n", libGlobalParam.TestResp[postResult->ppPostResult.framer_test]);
			  break;
		      default:
			  fprintf(filePtr," FRAMER Test:             Invalid Result(%d)\n", postResult->ppPostResult.framer_test);
			  break;
		  }

		  fflush(filePtr);
                }
                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_GEN_2:
              {
                sInterfaceFrequency *interfaceFrequency;
                interfaceFrequency = (sInterfaceFrequency*)(((sDiagnosticResult*)BpmRespPtr)->data);

                /* cp post string prepairation */
                {
                  fprintf(filePtr, "\nControl Processor  Feq test:\n");
                  fprintf(filePtr," Core Frequency:          %Lf MHz\n", interfaceFrequency->cpInterFreq.coreFreq);
                  //fprintf(filePtr," Platform Frequency:      %Lf\n", interfaceFrequency->cpInterFreq.platFreq);
                  fprintf(filePtr," DDR Frequency:           %Lf MHz\n", interfaceFrequency->cpInterFreq.ddrFreq);
                  fprintf(filePtr," Bus Frequency:           %Lf MHz\n", interfaceFrequency->cpInterFreq.busFreq);

		  fflush(filePtr);
                }

                /* pp post result */
                {
                  fprintf(filePtr, "\nProtocol Processor  Feq test:\n");
                  fprintf(filePtr," Core Frequency:          %Lf MHz\n", interfaceFrequency->ppInterFreq.coreFreq);
                  //fprintf(filePtr," Platform Frequency:      %Lf\n", interfaceFrequency->ppInterFreq.platFreq);
                  fprintf(filePtr," DDR Frequency:           %Lf MHz\n", interfaceFrequency->ppInterFreq.ddrFreq);
                  fprintf(filePtr," Bus Frequency:           %Lf MHz\n", interfaceFrequency->ppInterFreq.busFreq);

		  fflush(filePtr);
                }

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC GEN ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }
        }
        break;
      case DIAGNOS_TCT_ICC_RAM_CP:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_CP_RAM_ALL:
              {
                sIccRamTestAllResult *iccRamTestAllResult;
                iccRamTestAllResult = (sIccRamTestAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ram disk Total Size:       %u\n", iccRamTestAllResult->ddrStats.stats.totalSize);
                fprintf(filePtr," Ram disk Free space:       %u\n", iccRamTestAllResult->ddrStats.stats.freeSpace);
                //fprintf(filePtr," Ram Disk speed:            %u\n", iccRamTestAllResult->ddrStats.stats.speed);
                fprintf(filePtr," Ram Disk total Folder:     %u\n", iccRamTestAllResult->ddrStats.stats.totalFolders);

                if(iccRamTestAllResult->walkTest.errCode == 0)
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :                    Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :                    Fail\n");
                }

                if(iccRamTestAllResult->pattern32BitTest.errCode == 0)
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :  Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :  Fail\n");
                }

                if(iccRamTestAllResult->pattern16BitTest.errCode == 0)
                {
                  fprintf(filePtr,"\n 16 Bits Read  and write Operation  Test :  Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n 16 Bits Read  and write Operation  Test :  Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_CP_RAM_1: 
              {
                sDDRStats *DDRStats;
                DDRStats = (sDDRStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ram disk Total Size:       %u\n", DDRStats->stats.totalSize);
                fprintf(filePtr," Ram disk Free space:       %u\n", DDRStats->stats.freeSpace);
                //fprintf(filePtr," Ram Disk speed:            %u\n", DDRStats->stats.speed);
                fprintf(filePtr," Ram Disk total Folder:     %u\n", DDRStats->stats.totalFolders);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 
            case TEST_ID_ICC_CP_RAM_2: 
              {
                sPmCpDiagResHdr *pmCpDiagResHdr;
                pmCpDiagResHdr = (sPmCpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmCpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :   Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 
            case TEST_ID_ICC_CP_RAM_3: 
              {
                sPmCpDiagResHdr *pmCpDiagResHdr;
                pmCpDiagResHdr = (sPmCpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmCpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :   Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;

            case TEST_ID_ICC_CP_RAM_4: 
              {
                sPmCpDiagResHdr *pmCpDiagResHdr;
                pmCpDiagResHdr = (sPmCpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmCpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n 16 Bits Read  and write Operation  Test :   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n 16 Bits Read  and write Operation  Test :   Fail\n");
                }
		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 
            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC CP RAM ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }
        }
	break;
      case DIAGNOS_TCT_ICC_RAM_PP:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_PP_RAM_ALL:
              {
                sIccRamTestAllResult *iccRamTestAllResult;
                iccRamTestAllResult = (sIccRamTestAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ram disk Total Size:       %u\n", iccRamTestAllResult->ddrStats.stats.totalSize);
                fprintf(filePtr," Ram disk Free space:       %u\n", iccRamTestAllResult->ddrStats.stats.freeSpace);
                //fprintf(filePtr," Ram Disk speed:            %u\n", iccRamTestAllResult->ddrStats.stats.speed);
                fprintf(filePtr," Ram Disk total Folder:     %u\n", iccRamTestAllResult->ddrStats.stats.totalFolders);
                if(iccRamTestAllResult->walkTest.errCode == 0)
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :                    Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :                    Fail\n");
                }

                if(iccRamTestAllResult->pattern32BitTest.errCode == 0)
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :  Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :  Fail\n");
                }

                if(iccRamTestAllResult->pattern16BitTest.errCode == 0)
                {
                  fprintf(filePtr,"\n 16 Bits Read  and write Operation  Test :  Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n 16 Bits Read  and write Operation  Test :  Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_PP_RAM_1: 
              {
                sDDRStats *DDRStats;
                DDRStats = (sDDRStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ram disk Total Size:       %u\n", DDRStats->stats.totalSize);
                fprintf(filePtr," Ram disk Free space:       %u\n", DDRStats->stats.freeSpace);
                //fprintf(filePtr," Ram Disk speed:            %u\n", DDRStats->stats.speed);
                fprintf(filePtr," Ram Disk total Folder:     %u\n", DDRStats->stats.totalFolders);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 
            case TEST_ID_ICC_PP_RAM_2: 
              {
                sPmPpDiagResHdr *pmPpDiagResHdr;
                pmPpDiagResHdr = (sPmPpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmPpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :   Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 
            case TEST_ID_ICC_PP_RAM_3: 
              {
                sPmPpDiagResHdr *pmPpDiagResHdr;
                pmPpDiagResHdr = (sPmPpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmPpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :  Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :  Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;

            case TEST_ID_ICC_PP_RAM_4: 
              {
                sPmPpDiagResHdr *pmPpDiagResHdr;
                pmPpDiagResHdr = (sPmPpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmPpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n 16 Bits Read  and write Operation  Test :  Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n 16 Bits Read  and write Operation  Test :  Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 
            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC PP RAM ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }
        }
	break;
      case DIAGNOS_TCT_ICC_ETHERNET_CP:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_CP_ETH_1:
              {
                sCPEthStats *CPEthStats;
                CPEthStats = (sCPEthStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ethernet Port Mac Address eth0:  %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    CPEthStats->ethStats[0].macAddr[0], CPEthStats->ethStats[0].macAddr[1],
                    CPEthStats->ethStats[0].macAddr[2], CPEthStats->ethStats[0].macAddr[3],
                    CPEthStats->ethStats[0].macAddr[4], CPEthStats->ethStats[0].macAddr[5]);

                fprintf(filePtr," IP address eth0:                 %d.%d.%d.%d\n", CPEthStats->ethStats[0].ipAddress[0],
                    CPEthStats->ethStats[0].ipAddress[1], CPEthStats->ethStats[0].ipAddress[2],
                    CPEthStats->ethStats[0].ipAddress[3]);
                fprintf(filePtr," Transmitted Packet eth0:         %u\n", CPEthStats->ethStats[0].txPkts);
                fprintf(filePtr," Received Packet  eth0:           %u\n", CPEthStats->ethStats[0].rxPkts);
                fprintf(filePtr," Transmitted Byte  eth0:          %u\n", CPEthStats->ethStats[0].txBytes);
                fprintf(filePtr," Received Byte eth0:              %u\n", CPEthStats->ethStats[0].rxBytes);
                fprintf(filePtr," Number of Collisions eth0:       %u\n", CPEthStats->ethStats[0].collisions);
                fprintf(filePtr," Transmitted Packet Dropped eth0: %u\n", CPEthStats->ethStats[0].txPktDrop);
                fprintf(filePtr," Received Packet  Dropped eth0:   %u\n", CPEthStats->ethStats[0].rxPktDrop);

                fprintf(filePtr,"\n Ethernet Port Mac Address eth1:  %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    CPEthStats->ethStats[1].macAddr[0], CPEthStats->ethStats[1].macAddr[1],
                    CPEthStats->ethStats[1].macAddr[2], CPEthStats->ethStats[1].macAddr[3],
                    CPEthStats->ethStats[1].macAddr[4], CPEthStats->ethStats[1].macAddr[5]);

                fprintf(filePtr," IP address eth1:                 %d.%d.%d.%d\n", CPEthStats->ethStats[1].ipAddress[0],
                    CPEthStats->ethStats[1].ipAddress[1], CPEthStats->ethStats[1].ipAddress[2],
                    CPEthStats->ethStats[1].ipAddress[3]);
                fprintf(filePtr," Transmitted Packet eth1:         %u\n", CPEthStats->ethStats[1].txPkts);
                fprintf(filePtr," Received Packet  eth1:           %u\n", CPEthStats->ethStats[1].rxPkts);
                fprintf(filePtr," Transmitted Byte  eth1:          %u\n", CPEthStats->ethStats[1].txBytes);
                fprintf(filePtr," Received Byte eth1:              %u\n", CPEthStats->ethStats[1].rxBytes);
                fprintf(filePtr," Number of Collisions eth1:       %u\n", CPEthStats->ethStats[1].collisions);
                fprintf(filePtr," Transmitted Packet Dropped eth1: %u\n", CPEthStats->ethStats[1].txPktDrop);
                fprintf(filePtr," Received Packet  Dropped eth1:   %u\n", CPEthStats->ethStats[1].rxPktDrop);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 
            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC ETH CP ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;
      case DIAGNOS_TCT_ICC_ETHERNET_PP:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_PP_ETH_ALL:
              {
                sPPEthStats *PPEthStats;
                PPEthStats = (sPPEthStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ethernet Port Mac Address eth0:  %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    PPEthStats->ethStats[0].macAddr[0], PPEthStats->ethStats[0].macAddr[1],
                    PPEthStats->ethStats[0].macAddr[2], PPEthStats->ethStats[0].macAddr[3],
                    PPEthStats->ethStats[0].macAddr[4], PPEthStats->ethStats[0].macAddr[5]);

                fprintf(filePtr," IP address eth0:                 %d.%d.%d.%d\n", PPEthStats->ethStats[0].ipAddress[0],
                    PPEthStats->ethStats[0].ipAddress[1], PPEthStats->ethStats[0].ipAddress[2],
                    PPEthStats->ethStats[0].ipAddress[3]);


                fprintf(filePtr," Transmitted Packet eth0:         %u\n", PPEthStats->ethStats[0].txPkts);
                fprintf(filePtr," Received Packet  eth0:           %u\n", PPEthStats->ethStats[0].rxPkts);
                fprintf(filePtr," Transmitted Byte  eth0:          %u\n", PPEthStats->ethStats[0].txBytes);
                fprintf(filePtr," Received Byte eth0:              %u\n", PPEthStats->ethStats[0].rxBytes);
                fprintf(filePtr," Number of Collisions eth0:       %u\n", PPEthStats->ethStats[0].collisions);
                fprintf(filePtr," Transmitted Packet Dropped eth0: %u\n", PPEthStats->ethStats[0].txPktDrop);
                fprintf(filePtr," Received Packet  Dropped eth0:   %u\n", PPEthStats->ethStats[0].rxPktDrop);

                fprintf(filePtr,"\n Ethernet Port Mac Address eth1:  %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    PPEthStats->ethStats[1].macAddr[0], PPEthStats->ethStats[1].macAddr[1],
                    PPEthStats->ethStats[1].macAddr[2], PPEthStats->ethStats[1].macAddr[3],
                    PPEthStats->ethStats[1].macAddr[4], PPEthStats->ethStats[1].macAddr[5]);

                fprintf(filePtr," IP address eth1:                 %d.%d.%d.%d\n", PPEthStats->ethStats[1].ipAddress[0],
                    PPEthStats->ethStats[1].ipAddress[1], PPEthStats->ethStats[1].ipAddress[2],
                    PPEthStats->ethStats[1].ipAddress[3]);

                fprintf(filePtr," Transmitted Packet eth1:         %u\n", PPEthStats->ethStats[1].txPkts);
                fprintf(filePtr," Received Packet  eth1:           %u\n", PPEthStats->ethStats[1].rxPkts);
                fprintf(filePtr," Transmitted Byte  eth1:          %u\n", PPEthStats->ethStats[1].txBytes);
                fprintf(filePtr," Received Byte eth1:              %u\n", PPEthStats->ethStats[1].rxBytes);
                fprintf(filePtr," Number of Collisions eth1:       %u\n", PPEthStats->ethStats[1].collisions);
                fprintf(filePtr," Transmitted Packet Dropped eth1: %u\n", PPEthStats->ethStats[1].txPktDrop);
                fprintf(filePtr," Received Packet  Dropped eth1:   %u\n", PPEthStats->ethStats[1].rxPktDrop);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 
            case TEST_ID_ICC_PP_ETH_1:
              {
                sPPEthStats *PPEthStats;
                PPEthStats = (sPPEthStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ethernet Port Mac Address eth0:  %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    PPEthStats->ethStats[0].macAddr[0], PPEthStats->ethStats[0].macAddr[1],
                    PPEthStats->ethStats[0].macAddr[2], PPEthStats->ethStats[0].macAddr[3],
                    PPEthStats->ethStats[0].macAddr[4], PPEthStats->ethStats[0].macAddr[5]);

                fprintf(filePtr," IP address eth0:                 %d.%d.%d.%d\n", PPEthStats->ethStats[0].ipAddress[0],
                    PPEthStats->ethStats[0].ipAddress[1], PPEthStats->ethStats[0].ipAddress[2],
                    PPEthStats->ethStats[0].ipAddress[3]);

                fprintf(filePtr," Transmitted Packet eth0:         %u\n", PPEthStats->ethStats[0].txPkts);
                fprintf(filePtr," Received Packet  eth0:           %u\n", PPEthStats->ethStats[0].rxPkts);
                fprintf(filePtr," Transmitted Byte  eth0:          %u\n", PPEthStats->ethStats[0].txBytes);
                fprintf(filePtr," Received Byte eth0:              %u\n", PPEthStats->ethStats[0].rxBytes);
                fprintf(filePtr," Number of Collisions eth0:       %u\n", PPEthStats->ethStats[0].collisions);
                fprintf(filePtr," Transmitted Packet Dropped eth0: %u\n", PPEthStats->ethStats[0].txPktDrop);
                fprintf(filePtr," Received Packet  Dropped eth0:   %u\n", PPEthStats->ethStats[0].rxPktDrop);

                fprintf(filePtr,"\n Ethernet Port Mac Address eth1:  %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    PPEthStats->ethStats[1].macAddr[0], PPEthStats->ethStats[1].macAddr[1],
                    PPEthStats->ethStats[1].macAddr[2], PPEthStats->ethStats[1].macAddr[3],
                    PPEthStats->ethStats[1].macAddr[4], PPEthStats->ethStats[1].macAddr[5]);

                fprintf(filePtr," IP address eth1:                 %d.%d.%d.%d\n", PPEthStats->ethStats[1].ipAddress[0],
                    PPEthStats->ethStats[1].ipAddress[1], PPEthStats->ethStats[1].ipAddress[2],
                    PPEthStats->ethStats[1].ipAddress[3]);

                fprintf(filePtr," Transmitted Packet eth1:         %u\n", PPEthStats->ethStats[1].txPkts);
                fprintf(filePtr," Received Packet  eth1:           %u\n", PPEthStats->ethStats[1].rxPkts);
                fprintf(filePtr," Transmitted Byte  eth1:          %u\n", PPEthStats->ethStats[1].txBytes);
                fprintf(filePtr," Received Byte eth1:              %u\n", PPEthStats->ethStats[1].rxBytes);
                fprintf(filePtr," Number of Collisions eth1:       %u\n", PPEthStats->ethStats[1].collisions);
                fprintf(filePtr," Transmitted Packet Dropped eth1: %u\n", PPEthStats->ethStats[1].txPktDrop);
                fprintf(filePtr," Received Packet  Dropped eth1:   %u\n", PPEthStats->ethStats[1].rxPktDrop);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 
            case TEST_ID_ICC_PP_ETH_2:
              {
                sPPEthPortStats *PPEthPortStats;
                PPEthPortStats = (sPPEthPortStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ethernet Port Mac Address :      %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    PPEthPortStats->macAddr[0], PPEthPortStats->macAddr[1],
                    PPEthPortStats->macAddr[2], PPEthPortStats->macAddr[3],
                    PPEthPortStats->macAddr[4], PPEthPortStats->macAddr[5]);

                fprintf(filePtr," IP address :                     %d.%d.%d.%d\n", PPEthPortStats->ipAddress[0],
                    PPEthPortStats->ipAddress[1], PPEthPortStats->ipAddress[2],
                    PPEthPortStats->ipAddress[3]);


                fprintf(filePtr," Transmitted Packet :             %u\n", PPEthPortStats->txPkts);
                fprintf(filePtr," Received Packet  :               %u\n", PPEthPortStats->rxPkts);
                fprintf(filePtr," Transmitted Byte  :              %u\n", PPEthPortStats->txBytes);
                fprintf(filePtr," Received Byte :                  %u\n", PPEthPortStats->rxBytes);
                fprintf(filePtr," Number of Collisions :           %u\n", PPEthPortStats->collisions);
                fprintf(filePtr," Transmitted Packet Dropped  :    %u\n", PPEthPortStats->txPktDrop);
                fprintf(filePtr," Received Packet  Dropped :       %u\n", PPEthPortStats->rxPktDrop);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break; 

            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC ETH PP ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;
      case DIAGNOS_TCT_ICC_FLASHDISK_CP:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_CP_FD_ALL:
              {
                sIccFlashDiskAllResult *iccFlashDiskAllResult;
                iccFlashDiskAllResult = (sIccFlashDiskAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Home Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", iccFlashDiskAllResult->homeStats.homeStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", iccFlashDiskAllResult->homeStats.homeStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", iccFlashDiskAllResult->homeStats.homeStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", iccFlashDiskAllResult->homeStats.homeStats.totalFolders);
                fprintf(filePtr,"\n BackUp Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", iccFlashDiskAllResult->homeStats.backupStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", iccFlashDiskAllResult->homeStats.backupStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", iccFlashDiskAllResult->homeStats.backupStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", iccFlashDiskAllResult->homeStats.backupStats.totalFolders);
                if(iccFlashDiskAllResult->patternWriteResult.errCode == 0)
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Fail\n");
                }

                if(iccFlashDiskAllResult->eraseWriteResult.errCode == 0)
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Sector:       Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Sector :      Fail\n");
                }             

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_CP_FD_1:
              {
                sFlashStats *flashStats;
                flashStats = (sFlashStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Home Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", flashStats->homeStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", flashStats->homeStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", flashStats->homeStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", flashStats->homeStats.totalFolders);
                fprintf(filePtr,"\n BackUp Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", flashStats->backupStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", flashStats->backupStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", flashStats->backupStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", flashStats->backupStats.totalFolders);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_CP_FD_2:
              {
                sPmCpDiagResHdr *pmCpDiagResHdr;
                pmCpDiagResHdr = (sPmCpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmCpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_CP_FD_3:
              {
                sPmCpDiagResHdr *pmCpDiagResHdr;
                pmCpDiagResHdr = (sPmCpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmCpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Sector:   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Sector:   Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;

            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC FLASHDISK CP ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;
      case DIAGNOS_TCT_ICC_FLASHDISK_PP:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_PP_FD_ALL:
              {
                sIccFlashDiskAllResult *iccFlashDiskAllResult;
                iccFlashDiskAllResult = (sIccFlashDiskAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Home Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", iccFlashDiskAllResult->homeStats.homeStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", iccFlashDiskAllResult->homeStats.homeStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", iccFlashDiskAllResult->homeStats.homeStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", iccFlashDiskAllResult->homeStats.homeStats.totalFolders);
                fprintf(filePtr,"\n BackUp Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", iccFlashDiskAllResult->homeStats.backupStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", iccFlashDiskAllResult->homeStats.backupStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", iccFlashDiskAllResult->homeStats.backupStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", iccFlashDiskAllResult->homeStats.backupStats.totalFolders);
                if(iccFlashDiskAllResult->patternWriteResult.errCode == 0)
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Fail\n");
                }

                if(iccFlashDiskAllResult->eraseWriteResult.errCode == 0)
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Sector:       Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Sector :      Fail\n");
                }             

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_PP_FD_1:
              {
                sFlashStats *flashStats;
                flashStats = (sFlashStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Home Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", flashStats->homeStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", flashStats->homeStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", flashStats->homeStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", flashStats->homeStats.totalFolders);
                fprintf(filePtr,"\n BackUp Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", flashStats->backupStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", flashStats->backupStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", flashStats->backupStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", flashStats->backupStats.totalFolders);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_PP_FD_2:
              {
                sPmPpDiagResHdr *pmPpDiagResHdr;
                pmPpDiagResHdr = (sPmPpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmPpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_PP_FD_3:
              {
                sPmPpDiagResHdr *pmPpDiagResHdr;
                pmPpDiagResHdr = (sPmPpDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmPpDiagResHdr->errCode == 0)
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Sector:   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Sector:   Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;

            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC FLASHDISK PP ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;
      case DIAGNOS_TCT_ICC_CPLD:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_CPLD_ALL:
              {
                sIccCpldAllResult *iccCpldAllResult;
                iccCpldAllResult = (sIccCpldAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                switch(iccCpldAllResult->cpldStats.selfCardState)
                {
                  case BPM_CARDSTATE_ACTIVE:
                    fprintf(filePtr," Self Card State :              Active\n");
                    break;

                  case BPM_CARDSTATE_STANDBY :
                    fprintf(filePtr," Self Card State :              Standby\n");
                    break;

                  case BPM_CARDSTATE_OUT_OF_SERVICE:
                    fprintf(filePtr," Self Card State :              OOS\n");
                    break;

                  case BPM_CARDSTATE_PLATFORM_INS:
                    fprintf(filePtr," Self Card State :              Platform_Ins\n");
                    break;

                  case BPM_CARDSTATE_IN_SERVICE:
                    fprintf(filePtr," Self Card State :              In-Service\n");
                    break;
                  case BPM_CARDSTATE_RECOVERY:
                    fprintf(filePtr," Self Card State :              Recovery\n");
                    break;
                  case BPM_CARDSTATE_DIAGNOSTIC :
                    fprintf(filePtr," Self Card State :              Diagnostics\n");
                    break;
                  case BPM_CARDSTATE_INIT:
                    fprintf(filePtr," Self Card State :              Init\n");
                    break;
                  case BPM_CARDSTATE_FAIL:
                    fprintf(filePtr," Self Card State :              Fail\n");
                    break;
                  case BPM_CARDSTATE_ABSENT:
                    fprintf(filePtr," Self Card State :              Absent\n");
                    break;
                  case BPM_CARDSTATE_ACTIVE_IN_PROGRESS:
                    fprintf(filePtr," Self Card State :              Active-In-Progress\n");
                    break;
                  case BPM_CARDSTATE_UPGRADE:
                    fprintf(filePtr," Self Card State :              Upgrade\n");
                    break;
                  case BPM_CARDSTATE_RESTART:
                    fprintf(filePtr," Self Card State :              Restart\n");
                    break;
                  case BPM_CARDSTATE_SHUTDOWN:
                    fprintf(filePtr," Self Card State :              Shutdown\n");
                    break;
                  case BPM_CARDSTATE_BD_INIT:
                    fprintf(filePtr," Self Card State :              BD_Init\n");
                    break;
		  default:
                    fprintf(filePtr," Self Card State :              Invalid\n");
                    break;
                }
                switch(iccCpldAllResult->cpldStats.peerCardState)
                {
                  case BPM_CARDSTATE_ACTIVE:
                    fprintf(filePtr," Peer Card State :              Active\n");
                    break;

                  case BPM_CARDSTATE_STANDBY :
                    fprintf(filePtr," Peer Card State :              Standby\n");
                    break;

                  case BPM_CARDSTATE_OUT_OF_SERVICE:
                    fprintf(filePtr," Peer Card State :              OOS\n");
                    break;

                  case BPM_CARDSTATE_PLATFORM_INS:
                    fprintf(filePtr," Peer Card State :              Platform_Ins\n");
                    break;

                  case BPM_CARDSTATE_IN_SERVICE:
                    fprintf(filePtr," Peer Card State :              In-Service\n");
                    break;
                  case BPM_CARDSTATE_RECOVERY:
                    fprintf(filePtr," Peer Card State :              Recovery\n");
                    break;
                  case BPM_CARDSTATE_DIAGNOSTIC :
                    fprintf(filePtr," Peer Card State :              Diagnostics\n");
                    break;
                  case BPM_CARDSTATE_INIT:
                    fprintf(filePtr," Peer Card State :              Init\n");
                    break;
                  case BPM_CARDSTATE_FAIL:
                    fprintf(filePtr," Peer Card State :              Fail\n");
                    break;
                  case BPM_CARDSTATE_ABSENT:
                    fprintf(filePtr," Peer Card State :              Absent\n");
                    break;
                  case BPM_CARDSTATE_ACTIVE_IN_PROGRESS:
                    fprintf(filePtr," Peer Card State :              Active-In-Progress\n");
                    break;
                  case BPM_CARDSTATE_UPGRADE:
                    fprintf(filePtr," Peer Card State :              Upgrade\n");
                    break;
                  case BPM_CARDSTATE_RESTART:
                    fprintf(filePtr," Peer Card State :              Restart\n");
                    break;
                  case BPM_CARDSTATE_SHUTDOWN:
                    fprintf(filePtr," Peer Card State :              Shutdown\n");
                    break;
                  case BPM_CARDSTATE_BD_INIT:
                    fprintf(filePtr," Peer Card State :              BD_Init\n");
                    break;
		  default:
                    fprintf(filePtr," Peer Card State :              Invalid\n");
                    break;
                }

                fprintf(filePtr,"\n CPLD Verson :                  %d.%d.%d\n",
			((iccCpldAllResult->cpldRegs.mjver & 0xF0) >> 4),
			(iccCpldAllResult->cpldRegs.mjver & 0x0F),
			(iccCpldAllResult->cpldRegs.mnver & 0x0F));

		switch(iccCpldAllResult->cpldRegs.cir)
		{
		    case 0x0b:
			fprintf(filePtr," Card Identification:           ICC Rev B(0x%02x)\n",iccCpldAllResult->cpldRegs.cir);
			break;
		    case 0x0c:
			fprintf(filePtr," Card Identification:           ICC Rev C(0x%02x)\n",iccCpldAllResult->cpldRegs.cir);
			break;
		    case 0x0d:
			fprintf(filePtr," Card Identification:           ICC Rev D(0x%02x)\n",iccCpldAllResult->cpldRegs.cir);
			break;
		    default:
			break;
		}

		for(i=0;i<8;i++)
		{
		    tdm_lsr = ((iccCpldAllResult->cpldRegs.lsr >> i) & 0x01);
		    if(tdm_lsr == 0x01)
		    {
			fprintf(filePtr," TDM Link %d Selection:          Copy 1(0x%02x)\n",i+1,tdm_lsr);
		    }
		    else
		    {
			fprintf(filePtr," TDM Link %d Selection:          Copy 0(0x%02x)\n",i+1,tdm_lsr);
		    }
		}

		fprintf(filePtr,"\nSelf Status Register:\n");
		switch(iccCpldAllResult->cpldRegs.ssr & 0x0F)
		{
		    case 0x00:
			fprintf(filePtr," Status =                       Initializing(0000)\n");
			break;
		    case 0x01:
			fprintf(filePtr," Status =                       Standby(0001)\n");
			break;
		    case 0x02:
			fprintf(filePtr," Status =                       Active(0010)\n");
			break;
		    case 0x03:
			fprintf(filePtr," Status =                       OOS(0011)\n");
			break;
		    case 0x04:
			fprintf(filePtr," Status =                       Recovery(0100)\n");
			break;
		    case 0x05:
			fprintf(filePtr," Status =                       Under Test(0101)\n");
			break;
		    case 0x06:
			fprintf(filePtr," Status =                       PlatformIns(0110)\n");
			break;
		    case 0x07:
			fprintf(filePtr," Status =                       Upgrade(0111)\n");
			break;
		    case 0x08:
			fprintf(filePtr," Status =                       Error(1000)\n");
			break;
		    case 0x0A:
			fprintf(filePtr," Status =                       ActiveInProgress(1010)\n");
			break;
		    default:
			fprintf(filePtr," Status =                       Invalid\n");
			break;
		}

		if(iccCpldAllResult->cpldRegs.ssr & 0x80)
		{
		    fprintf(filePtr," Clock Status =                 Clock0 Normal(1)\n");
		}
		else
		{
		    fprintf(filePtr," Clock Status =                 Clock0 Failure(0)\n");
		}

		if(iccCpldAllResult->cpldRegs.ssr & 0x40)
		{
		    fprintf(filePtr," Clock Status =                 Clock1 Normal(1)\n");
		}
		else
		{
		    fprintf(filePtr," Clock Status =                 Clock1 Failure(0)\n");
		}

		fprintf(filePtr,"\nMate Status Register:\n");
		switch(iccCpldAllResult->cpldRegs.msr & 0x0F)
		{
		    case 0x00:
			fprintf(filePtr," Status =                       Initializing(0000)\n");
			break;
		    case 0x01:
			fprintf(filePtr," Status =                       Standby(0001)\n");
			break;
		    case 0x02:
			fprintf(filePtr," Status =                       Active(0010)\n");
			break;
		    case 0x03:
			fprintf(filePtr," Status =                       OOS(0011)\n");
			break;
		    case 0x04:
			fprintf(filePtr," Status =                       Recovery(0100)\n");
			break;
		    case 0x05:
			fprintf(filePtr," Status =                       Under Test(0101)\n");
			break;
		    case 0x06:
			fprintf(filePtr," Status =                       PlatformIns(0110)\n");
			break;
		    case 0x07:
			fprintf(filePtr," Status =                       Upgrade(0111)\n");
			break;
		    case 0x08:
			fprintf(filePtr," Status =                       Error(1000)\n");
			break;
		    case 0x0A:
			fprintf(filePtr," Status =                       ActiveInProgress(1010)\n");
			break;
		    default:
			fprintf(filePtr," Status =                       Invalid\n");
			break;
		}

		if((iccCpldAllResult->cpldRegs.msr & 0x80) == 0)
		{
		    fprintf(filePtr," CP or PP Watch Dog Timer Failure\n");
		}

                fprintf(filePtr,"\nWatch Dog Status Register: \n");
		if(iccCpldAllResult->cpldRegs.war & 0x01)
		{
		    fprintf(filePtr," CP Watch Dog Timer Status :    Running(1), Processor is Good\n");
		}
		else
		{
		    fprintf(filePtr," CP Watch Dog Timer Status :    TimeOut(0), Processor Failure\n");
		}

		if(iccCpldAllResult->cpldRegs.war & 0x02)
		{
		    fprintf(filePtr," PP Watch Dog Timer Status :    Running(1), Processor is Good\n");
		}
		else
		{
		    fprintf(filePtr," PP Watch Dog Timer Status :    TimeOut(0), Processor Failure\n");
		}

		if(iccCpldAllResult->cpldRegs.war & 0x10)
		{
		    fprintf(filePtr," Mate card Presence=            Absent(1)\n");
		}
		else
		{
		    fprintf(filePtr," Mate card Presence=            Present(0)\n");
		}

		if(iccCpldAllResult->cpldRegs.war & 0x80)
		{
		    fprintf(filePtr," WDT Failure Detection Logic=   Enable(1)\n");
		}
		else
		{
		    fprintf(filePtr," WDT Failure Detection Logic=   Disable(0)\n");
		}

		if(iccCpldAllResult->cpldRegs.war & 0x40)
		{
		    fprintf(filePtr," Selects T1/E1 Clock to LIU=    T1(1) 1.544MHz\n");
		}
		else
		{
		    fprintf(filePtr," Selects T1/E1 Clock to LIU=    E1(0) 2.048MHz\n");
		}

		if(iccCpldAllResult->cpldRegs.war & 0x20)
		{
		    fprintf(filePtr," Configuration=                 Redundant(1)\n");
		}
		else
		{
		    fprintf(filePtr," Configuration=                 Non Redundant(0)\n");
		}

                fprintf(filePtr,"\nBuffer Control Register: \n");
		if(iccCpldAllResult->cpldRegs.bcr & 0x02)
		{
		    fprintf(filePtr," Transmit Buffer Enable:        Enable(1)\n");
		}
		else
		{
		    fprintf(filePtr," Transmit Buffer Enable:        Disable(0)\n");
		}

		if(iccCpldAllResult->cpldRegs.bcr & 0x04)
		{
		    fprintf(filePtr," Receive Buffer Enable:         Enable(1)\n");
		}
		else
		{
		    fprintf(filePtr," Receive Buffer Enable:         Disable(0)\n");
		}

		if(iccCpldAllResult->cpldRegs.bcr & 0x20)
		{
		    fprintf(filePtr," Wrong configuration Detection: Detected(1)\n");
		}
		else
		{
		    fprintf(filePtr," Wrong configuration Detection: Normal(0)\n");
		}

                fprintf(filePtr,"\nCPLD Reg Dumps :- \n");
                fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
                    iccCpldAllResult->cpldRegs.mjver,
                    iccCpldAllResult->cpldRegs.cir, iccCpldAllResult->cpldRegs.lsr,
                    iccCpldAllResult->cpldRegs.ssr, iccCpldAllResult->cpldRegs.msr,
                    iccCpldAllResult->cpldRegs.war, iccCpldAllResult->cpldRegs.bcr,
                    iccCpldAllResult->cpldRegs.apr, iccCpldAllResult->cpldRegs.spr,
                    iccCpldAllResult->cpldRegs.swpr, iccCpldAllResult->cpldRegs.scr,
                    iccCpldAllResult->cpldRegs.lrpr1, iccCpldAllResult->cpldRegs.lrpr2,
                    iccCpldAllResult->cpldRegs.lrpr3, iccCpldAllResult->cpldRegs.isr);
                fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
                    iccCpldAllResult->cpldRegs.esr1, iccCpldAllResult->cpldRegs.dcr,
                    iccCpldAllResult->cpldRegs.dsr, iccCpldAllResult->cpldRegs.wlb1,
                    iccCpldAllResult->cpldRegs.wlb2, iccCpldAllResult->cpldRegs.lrpr4,
                    iccCpldAllResult->cpldRegs.mnver, iccCpldAllResult->cpldRegs.tcsr,
                    iccCpldAllResult->cpldRegs.tbsr1, iccCpldAllResult->cpldRegs.tbsr2,
                    iccCpldAllResult->cpldRegs.wlb3, iccCpldAllResult->cpldRegs.wlb4,
                    iccCpldAllResult->cpldRegs.sys_id, iccCpldAllResult->cpldRegs.dac_lsb,
		    iccCpldAllResult->cpldRegs.dac_msb);
                fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
                    iccCpldAllResult->cpldRegs.esr2,
                    iccCpldAllResult->cpldRegs.csid, iccCpldAllResult->cpldRegs.tlmen1,
                    iccCpldAllResult->cpldRegs.tlmen2, iccCpldAllResult->cpldRegs.e1los,
                    iccCpldAllResult->cpldRegs.eicst, iccCpldAllResult->cpldRegs.tdmclk);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;

            case TEST_ID_ICC_CPLD_1:
              {
                sCpldStats *cpldStats;
                cpldStats = (sCpldStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                switch(cpldStats->selfCardState)
                {
                  case BPM_CARDSTATE_ACTIVE:
                    fprintf(filePtr," Self Card State :              Active\n");
                    break;

                  case BPM_CARDSTATE_STANDBY :
                    fprintf(filePtr," Self Card State :              Standby\n");
                    break;

                  case BPM_CARDSTATE_OUT_OF_SERVICE:
                    fprintf(filePtr," Self Card State :              OOS\n");
                    break;

                  case BPM_CARDSTATE_PLATFORM_INS:
                    fprintf(filePtr," Self Card State :              Platform_Ins\n");
                    break;

                  case BPM_CARDSTATE_IN_SERVICE:
                    fprintf(filePtr," Self Card State :              In-Service\n");
                    break;
                  case BPM_CARDSTATE_RECOVERY:
                    fprintf(filePtr," Self Card State :              Recovery\n");
                    break;
                  case BPM_CARDSTATE_DIAGNOSTIC :
                    fprintf(filePtr," Self Card State :              Diagnostics\n");
                    break;
                  case BPM_CARDSTATE_INIT:
                    fprintf(filePtr," Self Card State :              Init\n");
                    break;
                  case BPM_CARDSTATE_FAIL:
                    fprintf(filePtr," Self Card State :              Fail\n");
                    break;
                  case BPM_CARDSTATE_ABSENT:
                    fprintf(filePtr," Self Card State :              Absent\n");
                    break;
                  case BPM_CARDSTATE_ACTIVE_IN_PROGRESS:
                    fprintf(filePtr," Self Card State :              Active-In-Progress\n");
                    break;
                  case BPM_CARDSTATE_UPGRADE:
                    fprintf(filePtr," Self Card State :              Upgrade\n");
                    break;
                  case BPM_CARDSTATE_RESTART:
                    fprintf(filePtr," Self Card State :              Restart\n");
                    break;
                  case BPM_CARDSTATE_SHUTDOWN:
                    fprintf(filePtr," Self Card State :              Shutdown\n");
                    break;
                  case BPM_CARDSTATE_BD_INIT:
                    fprintf(filePtr," Self Card State :              BD_Init\n");
                    break;
		  default:
                    fprintf(filePtr," Self Card State :              Invalid\n");
                    break;
                }
                switch(cpldStats->peerCardState)
                {
                  case BPM_CARDSTATE_ACTIVE:
                    fprintf(filePtr," Peer Card State :              Active\n");
                    break;

                  case BPM_CARDSTATE_STANDBY :
                    fprintf(filePtr," Peer Card State :              Standby\n");
                    break;

                  case BPM_CARDSTATE_OUT_OF_SERVICE:
                    fprintf(filePtr," Peer Card State :              OOS\n");
                    break;

                  case BPM_CARDSTATE_PLATFORM_INS:
                    fprintf(filePtr," Peer Card State :              Platform_Ins\n");
                    break;

                  case BPM_CARDSTATE_IN_SERVICE:
                    fprintf(filePtr," Peer Card State :              In-Service\n");
                    break;
                  case BPM_CARDSTATE_RECOVERY:
                    fprintf(filePtr," Peer Card State :              Recovery\n");
                    break;
                  case BPM_CARDSTATE_DIAGNOSTIC :
                    fprintf(filePtr," Peer Card State :              Diagnostics\n");
                    break;
                  case BPM_CARDSTATE_INIT:
                    fprintf(filePtr," Peer Card State :              Init\n");
                    break;
                  case BPM_CARDSTATE_FAIL:
                    fprintf(filePtr," Peer Card State :              Fail\n");
                    break;
                  case BPM_CARDSTATE_ABSENT:
                    fprintf(filePtr," Peer Card State :              Absent\n");
                    break;
                  case BPM_CARDSTATE_ACTIVE_IN_PROGRESS:
                    fprintf(filePtr," Peer Card State :              Active-In-Progress\n");
                    break;
                  case BPM_CARDSTATE_UPGRADE:
                    fprintf(filePtr," Peer Card State :              Upgrade\n");
                    break;
                  case BPM_CARDSTATE_RESTART:
                    fprintf(filePtr," Peer Card State :              Restart\n");
                    break;
                  case BPM_CARDSTATE_SHUTDOWN:
                    fprintf(filePtr," Peer Card State :              Shutdown\n");
                    break;
                  case BPM_CARDSTATE_BD_INIT:
                    fprintf(filePtr," Peer Card State :              BD_Init\n");
                    break;
		  default:
                    fprintf(filePtr," Peer Card State :              Invalid\n");
                    break;
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_CPLD_2:
              {
                sCpldRegData *cpldRegData;
                cpldRegData = (sCpldRegData*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n CPLD Verson :                  %d.%d.%d\n",
			((cpldRegData->mjver & 0xF0) >> 4),
			(cpldRegData->mjver & 0x0F),
			(cpldRegData->mnver & 0x0F));

		switch(cpldRegData->cir)
		{
		    case 0x0b:
			fprintf(filePtr," Card Identification:           ICC Rev B(0x%02x)\n",cpldRegData->cir);
			break;
		    case 0x0c:
			fprintf(filePtr," Card Identification:           ICC Rev C(0x%02x)\n",cpldRegData->cir);
			break;
		    case 0x0d:
			fprintf(filePtr," Card Identification:           ICC Rev D(0x%02x)\n",cpldRegData->cir);
			break;
		    default:
			break;
		}

		for(i=0;i<8;i++)
		{
		    tdm_lsr = ((cpldRegData->lsr >> i) & 0x01);
		    if(tdm_lsr == 0x01)
		    {
			fprintf(filePtr," TDM Link %d Selection:          Copy 1(0x%02x)\n",i+1,tdm_lsr);
		    }
		    else
		    {
			fprintf(filePtr," TDM Link %d Selection:          Copy 0(0x%02x)\n",i+1,tdm_lsr);
		    }
		}

		fprintf(filePtr,"\nSelf Status Register:\n");
		switch(cpldRegData->ssr & 0x0F)
		{
		    case 0x00:
			fprintf(filePtr," Status =                       Initializing(0000)\n");
			break;
		    case 0x01:
			fprintf(filePtr," Status =                       Standby(0001)\n");
			break;
		    case 0x02:
			fprintf(filePtr," Status =                       Active(0010)\n");
			break;
		    case 0x03:
			fprintf(filePtr," Status =                       OOS(0011)\n");
			break;
		    case 0x04:
			fprintf(filePtr," Status =                       Recovery(0100)\n");
			break;
		    case 0x05:
			fprintf(filePtr," Status =                       Under Test(0101)\n");
			break;
		    case 0x06:
			fprintf(filePtr," Status =                       PlatformIns(0110)\n");
			break;
		    case 0x07:
			fprintf(filePtr," Status =                       Upgrade(0111)\n");
			break;
		    case 0x08:
			fprintf(filePtr," Status =                       Error(1000)\n");
			break;
		    case 0x0A:
			fprintf(filePtr," Status =                       ActiveInProgress(1010)\n");
			break;
		    default:
			fprintf(filePtr," Status =                       Invalid\n");
			break;
		}

		if(cpldRegData->ssr & 0x80)
		{
		    fprintf(filePtr," Clock Status =                 Clock0 Normal(1)\n");
		}
		else
		{
		    fprintf(filePtr," Clock Status =                 Clock0 Failure(0)\n");
		}

		if(cpldRegData->ssr & 0x40)
		{
		    fprintf(filePtr," Clock Status =                 Clock1 Normal(1)\n");
		}
		else
		{
		    fprintf(filePtr," Clock Status =                 Clock1 Failure(0)\n");
		}

		fprintf(filePtr,"\nMate Status Register:\n");
		switch(cpldRegData->msr & 0x0F)
		{
		    case 0x00:
			fprintf(filePtr," Status =                       Initializing(0000)\n");
			break;
		    case 0x01:
			fprintf(filePtr," Status =                       Standby(0001)\n");
			break;
		    case 0x02:
			fprintf(filePtr," Status =                       Active(0010)\n");
			break;
		    case 0x03:
			fprintf(filePtr," Status =                       OOS(0011)\n");
			break;
		    case 0x04:
			fprintf(filePtr," Status =                       Recovery(0100)\n");
			break;
		    case 0x05:
			fprintf(filePtr," Status =                       Under Test(0101)\n");
			break;
		    case 0x06:
			fprintf(filePtr," Status =                       PlatformIns(0110)\n");
			break;
		    case 0x07:
			fprintf(filePtr," Status =                       Upgrade(0111)\n");
			break;
		    case 0x08:
			fprintf(filePtr," Status =                       Error(1000)\n");
			break;
		    case 0x0A:
			fprintf(filePtr," Status =                       ActiveInProgress(1010)\n");
			break;
		    default:
			fprintf(filePtr," Status =                       Invalid\n");
			break;
		}

		if((cpldRegData->msr & 0x80) == 0)
		{
		    fprintf(filePtr," CP or PP Watch Dog Timer Failure\n");
		}

                fprintf(filePtr,"\nWatch Dog Status Register: \n");
		if(cpldRegData->war & 0x01)
		{
		    fprintf(filePtr," CP Watch Dog Timer Status :    Running(1), Processor is Good\n");
		}
		else
		{
		    fprintf(filePtr," CP Watch Dog Timer Status :    TimeOut(0), Processor Failure\n");
		}

		if(cpldRegData->war & 0x02)
		{
		    fprintf(filePtr," PP Watch Dog Timer Status :    Running(1), Processor is Good\n");
		}
		else
		{
		    fprintf(filePtr," PP Watch Dog Timer Status :    TimeOut(0), Processor Failure\n");
		}

		if(cpldRegData->war & 0x10)
		{
		    fprintf(filePtr," Mate card Presence=            Absent(1)\n");
		}
		else
		{
		    fprintf(filePtr," Mate card Presence=            Present(0)\n");
		}

		if(cpldRegData->war & 0x80)
		{
		    fprintf(filePtr," WDT Failure Detection Logic=   Enable(1)\n");
		}
		else
		{
		    fprintf(filePtr," WDT Failure Detection Logic=   Disable(0)\n");
		}

		if(cpldRegData->war & 0x40)
		{
		    fprintf(filePtr," Selects T1/E1 Clock to LIU=    T1(1) 1.544MHz\n");
		}
		else
		{
		    fprintf(filePtr," Selects T1/E1 Clock to LIU=    E1(0) 2.048MHz\n");
		}

		if(cpldRegData->war & 0x20)
		{
		    fprintf(filePtr," Configuration=                 Redundant(1)\n");
		}
		else
		{
		    fprintf(filePtr," Configuration=                 Non Redundant(0)\n");
		}

                fprintf(filePtr,"\nBuffer Control Register: \n");
		if(cpldRegData->bcr & 0x02)
		{
		    fprintf(filePtr," Transmit Buffer Enable:        Enable(1)\n");
		}
		else
		{
		    fprintf(filePtr," Transmit Buffer Enable:        Disable(0)\n");
		}

		if(cpldRegData->bcr & 0x04)
		{
		    fprintf(filePtr," Receive Buffer Enable:         Enable(1)\n");
		}
		else
		{
		    fprintf(filePtr," Receive Buffer Enable:         Disable(0)\n");
		}

		if(cpldRegData->bcr & 0x20)
		{
		    fprintf(filePtr," Wrong configuration Detection: Detected(1)\n");
		}
		else
		{
		    fprintf(filePtr," Wrong configuration Detection: Normal(0)\n");
		}

                fprintf(filePtr,"\nCPLD Reg Dumps :- \n");
                fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
                    cpldRegData->mjver,
                    cpldRegData->cir, cpldRegData->lsr,
                    cpldRegData->ssr, cpldRegData->msr,
                    cpldRegData->war, cpldRegData->bcr,
                    cpldRegData->apr, cpldRegData->spr,
                    cpldRegData->swpr, cpldRegData->scr,
                    cpldRegData->lrpr1, cpldRegData->lrpr2,
                    cpldRegData->lrpr3, cpldRegData->isr);
                fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
                    cpldRegData->esr1, cpldRegData->dcr,
                    cpldRegData->dsr, cpldRegData->wlb1,
                    cpldRegData->wlb2, cpldRegData->lrpr4,
                    cpldRegData->mnver, cpldRegData->tcsr,
                    cpldRegData->tbsr1, cpldRegData->tbsr2,
                    cpldRegData->wlb3, cpldRegData->wlb4,
                    cpldRegData->sys_id, cpldRegData->dac_lsb,
		    cpldRegData->dac_msb);
                fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
                    cpldRegData->esr2,
                    cpldRegData->csid, cpldRegData->tlmen1,
                    cpldRegData->tlmen2, cpldRegData->e1los,
                    cpldRegData->eicst, cpldRegData->tdmclk);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;

            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC CPLD ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;
      case DIAGNOS_TCT_ICC_FRAMER:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_FRAMER_1:
              {
                sIccFramerPortInfo *iccFramerPortInfo;
                iccFramerPortInfo = (sIccFramerPortInfo*)(((sDiagnosticResult*)BpmRespPtr)->data);
                fprintf(filePtr,"<Port:                      %d>\n", iccFramerPortInfo->portId);
                if(iccFramerPortInfo->portConfStatus == 1)
                {
                  fprintf(filePtr," Port Configuration Status: Activated(1)\n");
                }
                else
                {
                  fprintf(filePtr," Port Configuration Status: Deactivated(0)\n");
                }
		switch(iccFramerPortInfo->portMode)
		{
		    case BPM_TRUNK_TYPE_E1:
			fprintf(filePtr," Port Mode(E1/T1):          E1(1)\n");
			break;
		    case BPM_TRUNK_TYPE_T1:
			fprintf(filePtr," Port Mode(E1/T1):          T1(2)\n");
			break;
		    case BPM_TRUNK_TYPE_INVALID:
			fprintf(filePtr," Port Mode(E1/T1):          Invalid(0)\n");
			break;
		}
		switch(iccFramerPortInfo->loopType)
		{
		    case BPM_REMOTE_LOOPBACK:
			fprintf(filePtr," Loop Type:                 Remote Loopback(0)\n");
			break;
		    case BPM_LOCAL_LOOPBACK:
			fprintf(filePtr," Loop Type:                 Local Loopback(1)\n");
			break;
		    case BPM_PAYLOAD_LOOPBACK:
			fprintf(filePtr," Loop Type:                 Payload Loopback(2)\n");
			break;
		    case BPM_FRAMER_LOOPBACK:
			fprintf(filePtr," Loop Type:                 Framer Loopback(3)\n");
			break;
		    case BPM_ANALOG_LOOPBACK:
			fprintf(filePtr," Loop Type:                 Analog Loopback(4)\n");
			break;
		    case BPM_LOOPBACK_INVALID:
			fprintf(filePtr," Loop Type:                 Invalid Loopback Type(0xFF)\n");
			break;
		}
                if(iccFramerPortInfo->loopStatus == 0)
                {
                  fprintf(filePtr," Loopback Status:           Disable(0)\n");
                }
                else
                {
                  fprintf(filePtr," Loopback Status:           Enable(1)\n");
                }
		switch(iccFramerPortInfo->framing)
		{
		    case BPM_TRUNK_FRAMING_OPT_T1_D4:
			fprintf(filePtr," Framing Option:            T1 D4(0)\n" );
			break;
		    case BPM_TRUNK_FRAMING_OPT_T1_ESF:
			fprintf(filePtr," Framing Option:            T1 ESF(1)\n" );
			break;
		    case BPM_TRUNK_FRAMING_OPT_E1_CRC4:
			fprintf(filePtr," Framing Option:            E1 CRC(2)\n" );
			break;
		    case BPM_TRUNK_FRAMING_OPT_E1_NOCRC4:
			fprintf(filePtr," Framing Option:            E1 NOCRC(3)\n" );
			break;
		    case BPM_TRUNK_FRAMING_OPT_INVALID:
			fprintf(filePtr," Framing Option:            Invalid(0xFF)\n" );
			break;
		}
		switch(iccFramerPortInfo->lineCoding)
		{
		    case BPM_TRUNK_ENCODE_OPT_T1_E1_AMI:
			fprintf(filePtr," Encoding Option:           T1 E1 AMI(0)\n" );
			break;
		    case BPM_TRUNK_ENCODE_OPT_T1_B8ZS:
			fprintf(filePtr," Encoding Option:           T1 B8ZS(1)\n" );
			break;
		    case BPM_TRUNK_ENCODE_OPT_E1_HDB3:
			fprintf(filePtr," Encoding Option:           E1 HDB3(2)\n" );
			break;
		    case BPM_TRUNK_ENCODE_TYPE_INVALID:
			fprintf(filePtr," Encoding Option:           Invalid(0xFF)\n" );
			break;
		}
		switch(iccFramerPortInfo->sigStrength)
		{
		    case BPM_TRUNK_SIG_STRENGH_0:
			fprintf(filePtr," sigStrength:             Sig Strength_0(0)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGH_1:
			fprintf(filePtr," sigStrength:             Sig Strength_1(1)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGH_2:
			fprintf(filePtr," sigStrength:             Sig Strength_2(2)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGH_3:
			fprintf(filePtr," sigStrength:             Sig Strength_3(3)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGH_4:
			fprintf(filePtr," sigStrength:             Sig Strength_4(4)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGTH_INVALID:
			fprintf(filePtr," sigStrength:             Invalid Sig Strength(0xFF)\n");
			break;
		}

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_FRAMER_2:
              {
                sIccFramerPortRTInfo *iccFramerPortRTInfo;
                iccFramerPortRTInfo = (sIccFramerPortRTInfo*)(((sDiagnosticResult*)BpmRespPtr)->data);
                fprintf(filePtr,"<Port:                                    %d>\n", iccFramerPortRTInfo->portId);
                if(iccFramerPortRTInfo->portConfStatus == 1)
                {
                  fprintf(filePtr," Port Configuration Status:               Activated(1)\n");
                }
                else
                {
                  fprintf(filePtr," Port Configuration Status:               Deactivated(0)\n");
                }
                if(iccFramerPortRTInfo->liuLos == 0)
                {
                  fprintf(filePtr," Line interface unit LOS:                 Absent(0)\n");
                }
                else
                {
                  fprintf(filePtr," Line interface unit LOS:                 Present(1)\n");
                }
                if(iccFramerPortRTInfo->rLos == 0)
                {
                  fprintf(filePtr," Remote LOS:                              Absent(0)\n");
                }
                else
                {
                  fprintf(filePtr," Remote LOS:                              Present(1)\n");
                }
                if(iccFramerPortRTInfo->rLof  == 0)
                {
                  fprintf(filePtr," Remote Loss of Frame(LOF):               Absent(0)\n" );
                }
                else
                {
                  fprintf(filePtr," Remote Loss of Frame(LOF):               Present(1)\n");
                }
                if(iccFramerPortRTInfo->isPortUp == 1)
                {
                  fprintf(filePtr," Port Status:                             Enable(1)\n");
                }
                else
                {
                  fprintf(filePtr," Port Status:                             Disable(0)\n");
                }
                fprintf(filePtr,"\n LIU Jitter Attenuator Limit Trip Clear:  %u\n", iccFramerPortRTInfo->framerPegs.liu_clr_jitter_attenuator_limit_trip);
                fprintf(filePtr," LIU Open-Circuit Clear Detected:         %u\n", iccFramerPortRTInfo->framerPegs.liu_clr_open_ckt_detect);
                fprintf(filePtr," LIU Short-Circuit Clear Detected:        %u\n", iccFramerPortRTInfo->framerPegs.liu_clr_short_ckt_detect);
                fprintf(filePtr," LIU Loss of Signal Clear Detected:       %u\n", iccFramerPortRTInfo->framerPegs.liu_clr_los_detect);
                fprintf(filePtr," LIU Jitter Attenuator Limit Trip Set:    %u\n", iccFramerPortRTInfo->framerPegs.liu_jitter_attenuator_limit_trip);
                fprintf(filePtr," LIU Open-Circuit Detect:                 %u\n", iccFramerPortRTInfo->framerPegs.liu_open_ckt_detect);
                fprintf(filePtr," LIU Short-Circuit Detect:                %u\n", iccFramerPortRTInfo->framerPegs.liu_short_ckt_detect);
                fprintf(filePtr," LIU Loss of Signal Detect:               %u\n", iccFramerPortRTInfo->framerPegs.liu_los_detect);
                fprintf(filePtr," Receive Remote Alarm Set Clear:          %u\n", iccFramerPortRTInfo->framerPegs.rx_remote_alarmInd_clr);
                fprintf(filePtr," Receive Alarm Set Clear:                 %u\n", iccFramerPortRTInfo->framerPegs.rx_alarm_condition_clr);
                fprintf(filePtr," Receive Loss of Signal Clear:            %u\n", iccFramerPortRTInfo->framerPegs.rx_los_clr);
                fprintf(filePtr," Receive Loss of Frame Clear:             %u\n", iccFramerPortRTInfo->framerPegs.rx_lof_clr);
                fprintf(filePtr," Receive Remote Alarm Set Condition:      %u\n", iccFramerPortRTInfo->framerPegs.rx_remote_alarmInd);
                fprintf(filePtr," Receive Alarm Set Condition:             %u\n", iccFramerPortRTInfo->framerPegs.rx_alarm_condition);
                fprintf(filePtr," Receive Loss of Signal Set:              %u\n", iccFramerPortRTInfo->framerPegs.rx_los);
                fprintf(filePtr," Receive Loss of Frame Set:               %u\n", iccFramerPortRTInfo->framerPegs.rx_lof);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_FRAMER_3:
              {
                sLoopBackResult *loopBackResult;
                loopBackResult = (sLoopBackResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"<Port:                                    %d>\n", loopBackResult->portId);

                if(loopBackResult->loopBackResult.errCode == 0)
                {
                  fprintf(filePtr,"\n Internal Digital and  Analog  Loop Back: Pass\n" );
                }
                else
                {
                  fprintf(filePtr,"\n Internal Digital and  Analog  Loop Back: Fail\n" );
                }

                fprintf(filePtr,"\n Bit Error Rate:                          %d\n", loopBackResult->loopBackResult.berErrorCnt);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_FRAMER_4:
              {
                sLoopBackResult *loopBackResult;
                loopBackResult = (sLoopBackResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"<Port:                                    %d>\n", loopBackResult->portId);

                if(loopBackResult->loopBackResult.errCode == 0)
                {
                  fprintf(filePtr,"\n Remote Loop Back:                        Pass\n" );
                }
                else
                {
                  fprintf(filePtr,"\n Remote Loop Back:                        Fail\n" );
                }

                fprintf(filePtr,"\n Bit Error Rate:                          Not Applicable\n");

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
            case TEST_ID_ICC_FRAMER_5:
              {
                sOverallLoopBackResult *overallLoopBackResult;
                overallLoopBackResult = (sOverallLoopBackResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"<Port:                                    %d>\n", overallLoopBackResult->portId);

                if(overallLoopBackResult->localLoopBackResult.errCode == 0)
                {
                  fprintf(filePtr,"\n Internal Digital and  Analog  Loop Back: Pass\n" );
                }
                else
                {
                  fprintf(filePtr,"\n Internal Digital and  Analog  Loop Back: Fail\n");
                }

                fprintf(filePtr,"\n Bit Error Rate:                          %d\n", overallLoopBackResult->localLoopBackResult.berErrorCnt);

                if(overallLoopBackResult->remoteLoopBackResult.errCode == 0)
                {
                  fprintf(filePtr,"\n Remote Loop Back:                        Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Remote Loop Back:                        Fail\n");
                }

                fprintf(filePtr,"\n Bit Error Rate:                          Not Applicable\n");

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
#if 0
            case TEST_ID_ICC_FRAMER_6:
              {
                sLoopBackResult *tdmConnectivityResult;
                tdmConnectivityResult = (sLoopBackResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"<Port:                      %d>\n", tdmConnectivityResult->portId);

                if(tdmConnectivityResult->loopBackResult.errCode == 0)
                {
                  fprintf(filePtr,"\n TDM Connectivity Test:   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n TDM Connectivity Test:   Fail\n");
                }

                fprintf(filePtr,"\n Bit Error Rate:            %d\n", tdmConnectivityResult->loopBackResult.berErrorCnt);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }
              break;
#endif
            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC FRAMER ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;

          }    
        }
	break;
      case DIAGNOS_TCT_ICC_I2C_BUS:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_I2C_ALL:
            case TEST_ID_ICC_I2C_1:
            case TEST_ID_ICC_I2C_2:
            case TEST_ID_ICC_I2C_3:
            case TEST_ID_ICC_I2C_4:
            case TEST_ID_ICC_I2C_5:
            case TEST_ID_ICC_I2C_6:
            case TEST_ID_ICC_I2C_7:
            case TEST_ID_ICC_I2C_8:
              {
                LOG_PRINT(CRITICAL,"I2C Diag not implemented yet"); 
                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);

                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);

                  }
                }  
              }    
              break;
            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC I2C ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;

          }  
        }
	break;

      case DIAGNOS_TCT_ICC_DSP:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_DSP_ALL:
              {
                sIccDspAllResult *iccDspAllResult;
                iccDspAllResult = (sIccDspAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);
                if(iccDspAllResult->connectivityCheck.errCode == 0)
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the Protocol Processor and  DSP:  Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the Protocol Processor and  DSP:  Fail\n");
                }
                if(iccDspAllResult->verifyDsiBusInterface.errCode == 0)
                {
                  fprintf(filePtr,"\n DSI  connectivity between the Protocol Processor and  DSP:      Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n DSI  connectivity between the Protocol Processor and  DSP:      Fail\n");
                }
                if(iccDspAllResult->rdWrOperation.errCode == 0)
                {
                  fprintf(filePtr,"\n DSP internal Memory Read/Write Test:                            Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n DSP internal Memory Read/Write Test:                            Fail\n");
                }
                if(iccDspAllResult->dspLoopBack.errCode == 0)
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI:                Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI:                Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:                                                %d\n", iccDspAllResult->dspLoopBack.berErrorCnt);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }    
              break;
            case TEST_ID_ICC_DSP_1:
              {
                sIccDspConnectivityRes *iccDspConnectivityRes;
                iccDspConnectivityRes = (sIccDspConnectivityRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(iccDspConnectivityRes->errCode == 0)
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the Protocol Processor and  DSP : Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the Protocol Processor and  DSP : Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }    
              break;
            case TEST_ID_ICC_DSP_2:
              {
                sIccDspDsiBusInterfaceRes *iccDspDsiBusInterfaceRes;
                iccDspDsiBusInterfaceRes = (sIccDspDsiBusInterfaceRes*)(((sDiagnosticResult*)BpmRespPtr)->data);
                if(iccDspDsiBusInterfaceRes->errCode == 0)
                {
                  fprintf(filePtr,"\n DSI  connectivity between the Protocol Processor and  DSP:      Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n DSI  connectivity between the Protocol Processor and  DSP:      Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }    
              break;
            case TEST_ID_ICC_DSP_3:
              {
                sIccDspRdWrOperRes *iccDspRdWrOperRes;
                iccDspRdWrOperRes = (sIccDspRdWrOperRes*)(((sDiagnosticResult*)BpmRespPtr)->data);
                if(iccDspRdWrOperRes->errCode == 0)
                {
                  fprintf(filePtr,"\n DSP internal Memory Read/Write Test  :                          Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n DSP internal Memory Read/Write Test  :                          Fail\n");
                }

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }    
              break;

            case TEST_ID_ICC_DSP_4:
              {
                sIccDspLoopBackRes *iccDspLoopBackRes;
                iccDspLoopBackRes = (sIccDspLoopBackRes*)(((sDiagnosticResult*)BpmRespPtr)->data);
                if(iccDspLoopBackRes->errCode == 0)
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI:                Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI:                Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:                                                 %d\n", iccDspLoopBackRes->berErrorCnt);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }    
              break;

            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC DSP ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }  
        }
	break;
      case DIAGNOS_TCT_ICC_MCC:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_MCC_3:
              {
                sIccMccChanProtocolStats *iccMccChanProtocolStats;
                iccMccChanProtocolStats = (sIccMccChanProtocolStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

		switch(iccMccChanProtocolStats->chanType)
		{
		    case CHAN_TYPE_MTP2:
			fprintf(filePtr,"\n Channel Type:                                  MTP2");
			fprintf(filePtr,"\n Channel Number:                                %d\n", iccMccChanProtocolStats->chanNum);
			fprintf(filePtr,"\n link failures due to abn BSNR:                 %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.SLFail_abnormBSNR);
			fprintf(filePtr," link failures due to abn FIBR:                 %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.SLFail_abnormFIBR);
			fprintf(filePtr," link failures due to T7 Expiry:                %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.SLFail_T7);
			fprintf(filePtr," link failures due to T6 Expiry:                %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.SLFail_suerm);
			fprintf(filePtr," alignment failures due to T2 or T3:            %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.SLFail_cong);
			fprintf(filePtr," alignment failures due to aerm:                %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.ALFail_T2T3);
			fprintf(filePtr," Number of Negative Acks:                       %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.ALFail_aerm);
			fprintf(filePtr," Number of SUs in error:                        %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.numNegAck);
			fprintf(filePtr," Number of SUs in error:                        %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.numErrSu);
			fprintf(filePtr," SIBs Tx'd:                                     %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.SIBtx);
			fprintf(filePtr," SIBs Rx'd:                                     %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.SIBrx);
			fprintf(filePtr," Number of Retransmissions due to N1:           %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.N1rtx);
			fprintf(filePtr," Number of Retransmissions due to N2:           %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.N2rtx);
			fprintf(filePtr," Number of MSUs Retransmitted:                  %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.MSUrtx);
			fprintf(filePtr," Number of MSUs Rx'd from MTP3:                 %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.MSUrtx_octets);
			fprintf(filePtr," Number of MSUs Tx'd to MTP3:                   %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.MSUhsrx);
			fprintf(filePtr," Number of MSUs Rx'd from MCC:                  %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.MSUhstx);
			fprintf(filePtr," Number of MSUs Rx'd from MCC:                  %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.MSUrx);
			fprintf(filePtr," Number of MSUs Tx'd to MCC:                    %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.MSUtx);
			fprintf(filePtr," Number of MSU octets Tx'd to MCC:              %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.MSUtx_octets);
			fprintf(filePtr," Number of MSU octets Rx'd from MCC:            %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.MSUrx_octets);
			fprintf(filePtr," Number of times RQ crossed threshold:          %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.RQThresCross);
			fprintf(filePtr," Number of times TQ crossed threshold:          %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.TQThresCross);
			fprintf(filePtr," Number of times TB crossed threshold:          %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.TBThresCross);
			fprintf(filePtr," Number of times RTB crossed threshold:         %u\n",iccMccChanProtocolStats->protoStats.mtp2ChanStats.RTBThresCross);
			break;
		    case CHAN_TYPE_LAPD:
			fprintf(filePtr,"\nChannel Type:                                   LAPD");
			fprintf(filePtr,"\nChannel Number:                                 %d\n", iccMccChanProtocolStats->chanNum);
			fprintf(filePtr,"\n Total Number of INFO Message Send:             %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.txI);
			fprintf(filePtr," Total Number of INFO Message Received:         %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.rxI);
			fprintf(filePtr," Total Number of UI Send:                       %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.txUI);
			fprintf(filePtr," Total Number of UI Received:                   %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.rxUI);
			fprintf(filePtr," Total Number of RR Command Send:               %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.txRR_C);
			fprintf(filePtr," Total Number of RR Command Received:           %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.rxRR_C);
			fprintf(filePtr," Total Number of RR Response Send:              %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.txRR_R);
			fprintf(filePtr," Total Number of RR Response Received:          %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.rxRR_R);
			fprintf(filePtr," Total Number of REJ Command Send:              %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.txREJ_C);
			fprintf(filePtr," Total Number of REJ Command Received:          %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.rxREJ_C);
			fprintf(filePtr," Total Number of REJ Response Send:             %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.txREJ_R);
			fprintf(filePtr," Total Number of REJ Response Received:         %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.rxREJ_R);
			fprintf(filePtr," Total Number of RNR Command Send:              %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.txRNR_C);
			fprintf(filePtr," Total Number of RNR Command Received:          %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.rxRNR_C);
			fprintf(filePtr," Total Number of RNR Response Send:             %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.txRNR_R);
			fprintf(filePtr," Total Number of RNR Response Received:         %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.rxRNR_R);
			fprintf(filePtr," Total Number of Message Decode Failed:         %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.num_decode_fail);
			fprintf(filePtr," Total Number of Message Encode Failed:         %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.num_encode_fail);
			fprintf(filePtr," Number of MSUs Rx'd from Lapd User:            %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.PDUhsrx);
			fprintf(filePtr," Number of MSUs Tx'd to Lapd User:              %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.PDUhstx);
			fprintf(filePtr," Number of MSUs Rx'd from MCC:                  %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.PDUrx);
			fprintf(filePtr," Number of MSUs Tx'd to MCC:                    %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.PDUtx);
			fprintf(filePtr," Number of MSU octets Tx'd to MCC:              %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.PDUtx_octets);
			fprintf(filePtr," Number of MSU octets Rx'd from MCC:            %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.PDUrx_octets);
			fprintf(filePtr," Number of times User RdQ crossed threshold:    %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.UserRdQThresCross);
			fprintf(filePtr," Number of times I Frame Q crossed threshold:   %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.I_QThresCross);
			fprintf(filePtr," Number of times UI Frame Q crossed threshold:  %u\n",iccMccChanProtocolStats->protoStats.lapdChanStats.UI_QThresCross);
			break;
		    case CHAN_TYPE_MLPPP:
			fprintf(filePtr,"\nProtocol Statistics of MLPPP Bundle (All Activated Channels):\n");
			fprintf(filePtr,"\n Master Chan:                                   %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.masterChan);
			fprintf(filePtr," Master Chan IPCP State:                        %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.mChanIpcpState);
			fprintf(filePtr," Total number of MLPPP chan configured:         %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.numChan);
			fprintf(filePtr," Is CONFIG Request Received:                    %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.isConfigured);
			fprintf(filePtr," Is DISCONNECT ALARM sent to User :             %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.isDisconnectedInd);
			fprintf(filePtr," Is MLPPP User Stopped:                         %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.isNetifcStopped);
			fprintf(filePtr," Profile Status:                                %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.profileStatus);
			fprintf(filePtr," Total Tx'd packet on PPP Interface:            %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.txPkt);
			fprintf(filePtr," Total Rx'd packet on PPP Interface:            %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.rxPkt);
			fprintf(filePtr," Previous Echo Req Count:                       %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.prevEchoReqCnt);
			fprintf(filePtr," Echo Req Count:                                %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.echoReqCnt);
			fprintf(filePtr," Total Small Buffers Used:                      %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.smallBufUsed);
			fprintf(filePtr," Total Small Buffers Free:                      %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.smallBufFree);
			fprintf(filePtr," Total Medium Buffers Used:                     %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.mediumBufUsed);
			fprintf(filePtr," Total Medium Buffers Free:                     %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.mediumBufFree);
			fprintf(filePtr," Total Large Buffers Used:                      %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.largeBufUsed);
			fprintf(filePtr," Total Large Buffers Free:                      %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.largeBufFree);
			fprintf(filePtr," Number of Packets in CEPP MQ:                  %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.ceppsLotCnt);
			fprintf(filePtr," Number of Packets in LLPP MQ:                  %u\n",iccMccChanProtocolStats->protoStats.mlpppChanStats.llppsLotCnt);
			break;
		    case CHAN_TYPE_FR:
			fprintf(filePtr,"\nChannel Type: FR");
			fprintf(filePtr,"\n Not Supported\n");
			break;
		    case CHAN_TYPE_PCU:
			fprintf(filePtr,"\nChannel Type: PCU");
			fprintf(filePtr,"\n Not Supported\n");
			break;
		    default:
			break;
		}

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }    
              break;

            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC MCC ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;

          }  
        }
	break;
      case DIAGNOS_TCT_ICC_TSI:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_ICC_TSI_ALL:
              {
                int loop;
                sIccTsiAllResult *iccTsiAllResult;
                iccTsiAllResult = (sIccTsiAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);
                for(loop = 0; loop < MAX_TSI_STREAMS; loop++)
                {
		  switch(iccTsiAllResult->tsiAllStreamsStats.tsiStreamStats[loop].streamId)
		  {
		      case ICC_DSP_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           ICC DSP(1)\n");
		          break;
		      case ICC_PP_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           ICC PP(2)\n");
		          break;
		      case ICC_FRAMER_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           ICC FRAMER(3)\n");
		          break;
		      case EIC0_DSP1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC0 DSP1(4)\n");
		          break;
		      case EIC0_DSP2_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC0 DSP2(5)\n");
		          break;
		      case EIC1_DSP1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC1 DSP1(6)\n");
		          break;
		      case EIC1_DSP2_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC1 DSP2(7)\n");
		          break;
		      case TU1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           TU1(8)\n");
		          break;
		      case TU2_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           TU2(9)\n");
		          break;
		      case ICC_PP_MATE_PP_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           ICC PP MATE PP(10)\n");
		          break;
		      case EIC0_FRAMER0_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC0 FRAMER0(11)\n");
		          break;
		      case EIC0_FRAMER1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC0 FRAMER1(12)\n");
		          break;
		      case EIC1_FRAMER0_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC1 FRAMER0(13)\n");
		          break;
		      case EIC1_FRAMER1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC1 FRAMER1(14)\n");
		          break;
		  }
                  if(iccTsiAllResult->tsiAllStreamsStats.tsiStreamStats[loop].isStreamEnabled == 1)
                  {
                    fprintf(filePtr," Stream Status:       Enable(1)\n");
                  }
                  else
                  {
                    fprintf(filePtr," Stream Status:       Disable(0)\n");
                  }
		  switch(iccTsiAllResult->tsiAllStreamsStats.tsiStreamStats[loop].streamDataRate)
		  {
		      case STREAM_RATE_UNDERFLOW:
			  fprintf(filePtr," Stream Rate:         UnderFlow(0)\n");
			  break;
		      case STREAM_RATE_UNUSED:
			  fprintf(filePtr," Stream Rate:         Unused(1)\n");
			  break;
		      case STREAM_RATE_02048KHz:
			  fprintf(filePtr," Stream Rate:         2048KHz(2)\n");
			  break;
		      case STREAM_RATE_04096KHz:
			  fprintf(filePtr," Stream Rate:         4096KHz(3)\n");
			  break;
		      case STREAM_RATE_08192KHz:
			  fprintf(filePtr," Stream Rate:         8192KHz(4)\n");
			  break;
		      case STREAM_RATE_16384KHz:
			  fprintf(filePtr," Stream Rate:         16384KHz(5)\n");
			  break;
		      case STREAM_RATE_OVERFLOW:
			  fprintf(filePtr," Stream Rate:         OverFlow(6)\n");
			  break;
		  }
                  if(iccTsiAllResult->tsiAllStreamsStats.tsiStreamStats[loop].ts0Pattern == ACTIVE_PATTERN)
                  {
                    fprintf(filePtr," Pattern :            ACTIVE_PATTERN(0x%02x)\n",ACTIVE_PATTERN);
                  }
                  else if(iccTsiAllResult->tsiAllStreamsStats.tsiStreamStats[loop].ts0Pattern == STANDBY_PATTERN)
                  {
                    fprintf(filePtr," Pattern :            STANDBY_PATTERN(0x%02x)\n",STANDBY_PATTERN);
                  }
		  else if(iccTsiAllResult->tsiAllStreamsStats.tsiStreamStats[loop].ts0Pattern == UNUSED_PATTERN)
		  {
                    fprintf(filePtr," Pattern :            UNUSED_PATTERN(0x%02x)\n",UNUSED_PATTERN);
		  }
                  else
                  {
                    fprintf(filePtr," Pattern :            INVALID_PATTERN(0x%02x)\n",iccTsiAllResult->tsiAllStreamsStats.tsiStreamStats[loop].ts0Pattern);
                  }
                }/* for */

                fprintf(filePtr,"\n Port :                                           %d\n", iccTsiAllResult->dspTsiLoopBackRes.streamId);
                if(iccTsiAllResult->dspTsiLoopBackRes.loopBackRes.errCode == 0)
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI: Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI: Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:                                  %d\n", iccTsiAllResult->dspTsiLoopBackRes.loopBackRes.berErrorCnt);
                fprintf(filePtr,"\n Port :                                           %d\n", iccTsiAllResult->ppTsiLoopBackRes.streamId);
                if(iccTsiAllResult->ppTsiLoopBackRes.loopBackRes.errCode == 0)
                {
                  fprintf(filePtr,"\n PP-TSI TDM Connectivity Test:                    Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n PP-TSI TDM Connectivity Test:                    Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:                                  %d\n", iccTsiAllResult->ppTsiLoopBackRes.loopBackRes.berErrorCnt);
                fprintf(filePtr,"\n Port :                                           %d\n", iccTsiAllResult->mateTsiTsiLoopBackRes.streamId);
                if(iccTsiAllResult->mateTsiTsiLoopBackRes.loopBackRes.errCode == 0)
                {
                  fprintf(filePtr,"\n MATE-TSI TDM Connectivity Test:                  Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n MATE-TSI TDM Connectivity Test:                  Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:                                  %d\n", iccTsiAllResult->mateTsiTsiLoopBackRes.loopBackRes.berErrorCnt);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  

              }  
              break;

            case TEST_ID_ICC_TSI_1:
              {
                int loop;
                sIccTsiAllStreamStats *iccTsiAllStreamStats;
                iccTsiAllStreamStats = (sIccTsiAllStreamStats*)(((sDiagnosticResult*)BpmRespPtr)->data);
                for(loop = 0; loop < MAX_TSI_STREAMS; loop++)
                {
		  switch(iccTsiAllStreamStats->tsiStreamStats[loop].streamId)
		  {
		      case ICC_DSP_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           ICC DSP(1)\n");
		          break;
		      case ICC_PP_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           ICC PP(2)\n");
		          break;
		      case ICC_FRAMER_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           ICC FRAMER(3)\n");
		          break;
		      case EIC0_DSP1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC0 DSP1(4)\n");
		          break;
		      case EIC0_DSP2_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC0 DSP2(5)\n");
		          break;
		      case EIC1_DSP1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC1 DSP1(6)\n");
		          break;
		      case EIC1_DSP2_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC1 DSP2(7)\n");
		          break;
		      case TU1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           TU1(8)\n");
		          break;
		      case TU2_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           TU2(9)\n");
		          break;
		      case ICC_PP_MATE_PP_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           ICC PP MATE PP(10)\n");
		          break;
		      case EIC0_FRAMER0_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC0 FRAMER0(11)\n");
		          break;
		      case EIC0_FRAMER1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC0 FRAMER1(12)\n");
		          break;
		      case EIC1_FRAMER0_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC1 FRAMER0(13)\n");
		          break;
		      case EIC1_FRAMER1_STRM_ID:
			  fprintf(filePtr,"\n Stream Id:           EIC1 FRAMER1(14)\n");
		          break;
		  }
                  if(iccTsiAllStreamStats->tsiStreamStats[loop].isStreamEnabled == 1)
                  {
                    fprintf(filePtr," Stream Status:       Enable(1)\n");
                  }
                  else
                  {
                    fprintf(filePtr," Stream Status:       Disable(0)\n");
                  }
		  switch(iccTsiAllStreamStats->tsiStreamStats[loop].streamDataRate)
		  {
		      case STREAM_RATE_UNDERFLOW:
			  fprintf(filePtr," Stream Rate:         UnderFlow(0)\n");
			  break;
		      case STREAM_RATE_UNUSED:
			  fprintf(filePtr," Stream Rate:         Unused(1)\n");
			  break;
		      case STREAM_RATE_02048KHz:
			  fprintf(filePtr," Stream Rate:         2048KHz(2)\n");
			  break;
		      case STREAM_RATE_04096KHz:
			  fprintf(filePtr," Stream Rate:         4096KHz(3)\n");
			  break;
		      case STREAM_RATE_08192KHz:
			  fprintf(filePtr," Stream Rate:         8192KHz(4)\n");
			  break;
		      case STREAM_RATE_16384KHz:
			  fprintf(filePtr," Stream Rate:         16384KHz(5)\n");
			  break;
		      case STREAM_RATE_OVERFLOW:
			  fprintf(filePtr," Stream Rate:         OverFlow(6)\n");
			  break;
		  }
                  if(iccTsiAllStreamStats->tsiStreamStats[loop].ts0Pattern == ACTIVE_PATTERN)
                  {
                    fprintf(filePtr," Pattern :            ACTIVE_PATTERN(0x%02x)\n",ACTIVE_PATTERN);
                  }
                  else if(iccTsiAllStreamStats->tsiStreamStats[loop].ts0Pattern == STANDBY_PATTERN)
                  {
                    fprintf(filePtr," Pattern :            STANDBY_PATTERN(0x%02x)\n",STANDBY_PATTERN);
                  }
                  else if(iccTsiAllStreamStats->tsiStreamStats[loop].ts0Pattern == UNUSED_PATTERN)
                  {
                    fprintf(filePtr," Pattern :            UNUSED_PATTERN(0x%02x)\n",UNUSED_PATTERN);
                  }
                  else
                  {
                    fprintf(filePtr," Pattern :            INVALID_PATTERN(0x%02x)\n",iccTsiAllStreamStats->tsiStreamStats[loop].ts0Pattern);
                  }
                }/* for */

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  

              }  
              break;
            case TEST_ID_ICC_TSI_2:
              {
                sTsiLoopBackRes *tsiLoopBackRes;
                tsiLoopBackRes = (sTsiLoopBackRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Port :                                           %d\n", tsiLoopBackRes->streamId);
                if(tsiLoopBackRes->loopBackRes.errCode == 0)
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI: Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI: Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:                                  %d\n", tsiLoopBackRes->loopBackRes.berErrorCnt);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }  
              break;
            case TEST_ID_ICC_TSI_3:
              {
                sTsiLoopBackRes *tsiLoopBackRes;
                tsiLoopBackRes = (sTsiLoopBackRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Port :                        %d\n", tsiLoopBackRes->streamId);
                if(tsiLoopBackRes->loopBackRes.errCode == 0)
                {
                  fprintf(filePtr,"\n PP-TSI TDM Connectivity Test: Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n PP-TSI TDM Connectivity Test: Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:               %d\n", tsiLoopBackRes->loopBackRes.berErrorCnt);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }  
              break;
            case TEST_ID_ICC_TSI_4:
	      {
		  sIccFramerTsiLoopBackRes *iccFramerTsiLoopBackRes;
		  iccFramerTsiLoopBackRes = (sIccFramerTsiLoopBackRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

		  for(i=0;i< MAX_ICC_FRAMER_PORTS;i++)
		  {
		      fprintf(filePtr,"\n Port :                            %d", iccFramerTsiLoopBackRes->loopBackRes[i].portId);
		      if(iccFramerTsiLoopBackRes->loopBackRes[i].loopBackResult.errCode == 0)
		      {
			  fprintf(filePtr,"\n FRAMER-TSI TDM Connectivity Test: Pass");
		      }
		      else
		      {
			  fprintf(filePtr,"\n FRAMER-TSI TDM Connectivity Test: Fail");
		      }
		      fprintf(filePtr,"\n Bit Error Rate:                   %d\n", iccFramerTsiLoopBackRes->loopBackRes[i].loopBackResult.berErrorCnt);

		      fflush(filePtr);
		  }

		  if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
		  {
		      if(libGlobalParam.errCode != 0) 
		      {
			  fprintf(filePtr, "\nResolution : Replace the Card\n");
			  fflush(filePtr);
		      }
		      else
		      {
			  fprintf(filePtr, "\nResolution : None\n");
			  fflush(filePtr);
		      }
		  }  
	      }  
              break;
            case TEST_ID_ICC_TSI_5:
              {
                sTsiLoopBackRes *tsiLoopBackRes;
                tsiLoopBackRes = (sTsiLoopBackRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Port :                          %d\n", tsiLoopBackRes->streamId);
                if(tsiLoopBackRes->loopBackRes.errCode == 0)
                {
                  fprintf(filePtr,"\n MATE-TSI TDM Connectivity Test: Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n MATE-TSI TDM Connectivity Test: Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:                 %d\n", tsiLoopBackRes->loopBackRes.berErrorCnt);

		fflush(filePtr);

                if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
                {
                  if(libGlobalParam.errCode != 0) 
                  {
                    fprintf(filePtr, "\nResolution : Replace the Card\n");
                    fflush(filePtr);
                  }
                  else
                  {
                    fprintf(filePtr, "\nResolution : None\n");
                    fflush(filePtr);
                  }
                }  
              }  
              break;


            default:
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for ICC TSI ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;

          }  
        }
	break;

      default:
        LOG_PRINT(CRITICAL,"DiagLib: TEST TYPE '%d' not defined for ICC", 
            ((sDiagnosticResult*)BpmRespPtr)->testType);
        break;
    }
  }
}

