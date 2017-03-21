#include "bpmDiaglib.h"
#include "bpmInclude.h"
extern FILE *filePtr; 
extern sLibGlobalParam libGlobalParam;
extern sParamKeySet paramKeySet[MAX_TCT_ID][MAX_TEST_ID];

void writeObmDetailInFile(void *BpmRespPtr)
{
  I_U8 tdm_lsr,i;
  I_U32 fanIndex=ZERO;

  if(libGlobalParam.suppress)
  {
    LOG_PRINT(DEBUG,"writeObmDetailInFile: supress case do nothing");
  }
  else
  {
    switch(((sDiagnosticResult*)BpmRespPtr)->testType)
    {
      case DIAGNOS_TCT_OBM_GEN:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            #if 0 
            case TEST_ID_OBM_GEN_ALL:
              {
                sObmGenResult *obmGenAllResult; //sIccGenResult
                obmGenAllResult = (sObmGenResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                /* cp post string prepairation */
                {
                  fprintf(filePtr, "\nControl Processor  POST:\n");
                  LOG_PRINT(DEBUG,"writeObmDetailInFile: OBM_GEN Test case");
                  printf("writeObmDetailInFile: OBM_GEN Test case\n\n");
                  fflush(filePtr);
		  switch(obmGenAllResult->postResult.mem_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Mem Test:                %s\n", libGlobalParam.TestResp[obmGenAllResult->postResult.mem_test]);
			  break;
		      default:
			  fprintf(filePtr," Mem Test:                Invalid Result(%d)\n",obmGenAllResult->postResult.mem_test);
			  break;
		  }
		  switch(obmGenAllResult->postResult.nand_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," Nand Test:               %s\n", libGlobalParam.TestResp[obmGenAllResult->postResult.nand_test]);
			  break;
		      default:
			  fprintf(filePtr," Nand Test:               Invalid Result(%d)\n", obmGenAllResult->postResult.nand_test);
			  break;
		  }
		  switch(obmGenAllResult->postResult.nvram_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RamDisk Test:            %s\n", libGlobalParam.TestResp[obmGenAllResult->postResult.nvram_test]);
			  break;
		      default:
			  fprintf(filePtr," RamDisk Test:            Invalid Result(%d)\n", obmGenAllResult->postResult.nvram_test);
			  break;
		  }
		  switch(obmGenAllResult->postResult.fec_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," FCC Test:                %s\n", libGlobalParam.TestResp[obmGenAllResult->postResult.fec_test]);
			  break;
		      default:
			  fprintf(filePtr," FCC Test:                Invalid Result(%d)\n", obmGenAllResult->postResult.fec_test);
			  break;
		  }
		  switch(obmGenAllResult->postResult.tsec1_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," TSEC Test:               %s\n", libGlobalParam.TestResp[obmGenAllResult->postResult.tsec1_test]);
			  break;
		      default:
			  fprintf(filePtr," TSEC Test:               Invalid Result(%d)\n", obmGenAllResult->postResult.tsec1_test);
			  break;
		  }
		  switch(obmGenAllResult->postResult.mc_reg_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Register Read Test:   %s\n", libGlobalParam.TestResp[obmGenAllResult->postResult.mc_reg_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Register Read Test:   Invalid Result(%d)\n", obmGenAllResult->postResult.mc_reg_test);
			  break;
		  }
		  switch(obmGenAllResult->postResult.mc_volt_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," MC Voltage Test:         %s\n", libGlobalParam.TestResp[obmGenAllResult->postResult.mc_volt_test]);
			  break;
		      default:
			  fprintf(filePtr," MC Voltage Test:         Invalid Result(%d)\n", obmGenAllResult->postResult.mc_volt_test);
			  break;
		  }
		  switch(obmGenAllResult->postResult.rtc_test)
		  {
		      case 0:
		      case 1:
			  fprintf(filePtr," RTC Test:                %s\n", libGlobalParam.TestResp[obmGenAllResult->postResult.rtc_test]);
			  break;
		      default:
			  fprintf(filePtr," RTC Test:                Invalid Result(%d)\n", obmGenAllResult->postResult.rtc_test);
			  break;
		  }
                  fprintf(filePtr," Core Frequency:          %Lf MHz\n", obmGenAllResult->interFreq.coreFreq);
                  //fprintf(filePtr," Platform Frequency:      %Lf\n", obmGenAllResult->interFreq.platFreq);
                  fprintf(filePtr," DDR Frequency:           %Lf MHz\n", obmGenAllResult->interFreq.ddrFreq);
                  fprintf(filePtr," Bus Frequency:           %Lf MHz\n", obmGenAllResult->interFreq.busFreq);

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
            case TEST_ID_OBM_GEN_1:
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
						#endif
            case TEST_ID_OBM_GEN_1:
              {
                sObmInterfaceFrequency *interfaceFrequency;
                interfaceFrequency = (sObmInterfaceFrequency *)(((sDiagnosticResult*)BpmRespPtr)->data);

                /* cp post string prepairation */
                {
                  fprintf(filePtr, "\nControl Processor  Feq test:\n");
                  fprintf(filePtr," Core Frequency:          %Lf MHz\n", interfaceFrequency->coreFreq);
                  //fprintf(filePtr," Platform Frequency:      %Lf\n", interfaceFrequency->cpInterFreq.platFreq);
                  fprintf(filePtr," DDR Frequency:           %Lf MHz\n", interfaceFrequency->ddrFreq);
                  fprintf(filePtr," Bus Frequency:           %Lf MHz\n", interfaceFrequency->busFreq);

		  fflush(filePtr);
                }
#if 0
                /* pp post result */
                {
                  fprintf(filePtr, "\nProtocol Processor  Feq test:\n");
                  fprintf(filePtr," Core Frequency:          %Lf MHz\n", interfaceFrequency->ppInterFreq.coreFreq);
                  //fprintf(filePtr," Platform Frequency:      %Lf\n", interfaceFrequency->ppInterFreq.platFreq);
                  fprintf(filePtr," DDR Frequency:           %Lf MHz\n", interfaceFrequency->ppInterFreq.ddrFreq);
                  fprintf(filePtr," Bus Frequency:           %Lf MHz\n", interfaceFrequency->ppInterFreq.busFreq);

		  fflush(filePtr);
                }
#endif

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
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for OBM GEN ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }
        }
        break;
      case DIAGNOS_TCT_OBM_RAM:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_OBM_RAM_ALL:
              {
                sObmRamTestAllResult *obmRamTestAllResult; //sIccRamTestAllResult
                obmRamTestAllResult = (sObmRamTestAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ram disk Total Size:       %u\n", obmRamTestAllResult->ddrStats.stats.totalSize);
                fprintf(filePtr," Ram disk Free space:       %u\n", obmRamTestAllResult->ddrStats.stats.freeSpace);
                //fprintf(filePtr," Ram Disk speed:            %u\n", obmRamTestAllResult->ddrStats.stats.speed);
                fprintf(filePtr," Ram Disk total Folder:     %u\n", obmRamTestAllResult->ddrStats.stats.totalFolders);

                if(obmRamTestAllResult->walkTest.errCode == 0)
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :                    Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ram Disk Walking Test :                    Fail\n");
                }

                if(obmRamTestAllResult->pattern32BitTest.errCode == 0)
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :  Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n 32 Bits Read  and write Operation  Test :  Fail\n");
                }

                if(obmRamTestAllResult->pattern16BitTest.errCode == 0)
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
            case TEST_ID_OBM_RAM_1: 
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
            case TEST_ID_OBM_RAM_2: 
              {
                sPmDiagResHdr *pmDiagResHdr;
                pmDiagResHdr = (sPmDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmDiagResHdr->errCode == 0)
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
            case TEST_ID_OBM_RAM_3: 
              {
                sPmDiagResHdr *pmDiagResHdr;
                pmDiagResHdr = (sPmDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmDiagResHdr->errCode == 0)
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

            case TEST_ID_OBM_RAM_4: 
              {
                sPmDiagResHdr *pmDiagResHdr;
                pmDiagResHdr = (sPmDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmDiagResHdr->errCode == 0)
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
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for OBM RAM ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }
        }
	break;
      case DIAGNOS_TCT_OBM_ETHERNET:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_OBM_ETH_1:
              {
                sEthStats *EthStats; //sCPEthStats
                EthStats = (sEthStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Ethernet Port Mac Address eth0:  %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    EthStats->ethStats[0].macAddr[0], EthStats->ethStats[0].macAddr[1],
                    EthStats->ethStats[0].macAddr[2], EthStats->ethStats[0].macAddr[3],
                    EthStats->ethStats[0].macAddr[4], EthStats->ethStats[0].macAddr[5]);

                fprintf(filePtr," IP address eth0:                 %d.%d.%d.%d\n", EthStats->ethStats[0].ipAddress[0],
                    EthStats->ethStats[0].ipAddress[1], EthStats->ethStats[0].ipAddress[2],
                    EthStats->ethStats[0].ipAddress[3]);
                fprintf(filePtr," Transmitted Packet eth0:         %u\n", EthStats->ethStats[0].txPkts);
                fprintf(filePtr," Received Packet  eth0:           %u\n", EthStats->ethStats[0].rxPkts);
                fprintf(filePtr," Transmitted Byte  eth0:          %u\n", EthStats->ethStats[0].txBytes);
                fprintf(filePtr," Received Byte eth0:              %u\n", EthStats->ethStats[0].rxBytes);
                fprintf(filePtr," Number of Collisions eth0:       %u\n", EthStats->ethStats[0].collisions);
                fprintf(filePtr," Transmitted Packet Dropped eth0: %u\n", EthStats->ethStats[0].txPktDrop);
                fprintf(filePtr," Received Packet  Dropped eth0:   %u\n", EthStats->ethStats[0].rxPktDrop);

                fprintf(filePtr,"\n Ethernet Port Mac Address eth1:  %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    EthStats->ethStats[1].macAddr[0], EthStats->ethStats[1].macAddr[1],
                    EthStats->ethStats[1].macAddr[2], EthStats->ethStats[1].macAddr[3],
                    EthStats->ethStats[1].macAddr[4], EthStats->ethStats[1].macAddr[5]);

                fprintf(filePtr," IP address eth1:                 %d.%d.%d.%d\n", EthStats->ethStats[1].ipAddress[0],
                    EthStats->ethStats[1].ipAddress[1], EthStats->ethStats[1].ipAddress[2],
                    EthStats->ethStats[1].ipAddress[3]);
                fprintf(filePtr," Transmitted Packet eth1:         %u\n", EthStats->ethStats[1].txPkts);
                fprintf(filePtr," Received Packet  eth1:           %u\n", EthStats->ethStats[1].rxPkts);
                fprintf(filePtr," Transmitted Byte  eth1:          %u\n", EthStats->ethStats[1].txBytes);
                fprintf(filePtr," Received Byte eth1:              %u\n", EthStats->ethStats[1].rxBytes);
                fprintf(filePtr," Number of Collisions eth1:       %u\n", EthStats->ethStats[1].collisions);
                fprintf(filePtr," Transmitted Packet Dropped eth1: %u\n", EthStats->ethStats[1].txPktDrop);
                fprintf(filePtr," Received Packet  Dropped eth1:   %u\n", EthStats->ethStats[1].rxPktDrop);

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
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for OBM ETH ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;
      case DIAGNOS_TCT_OBM_FLASHDISK:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_OBM_FD_ALL:
              {
                sObmFlashDiskAllResult *obmFlashDiskAllResult; //sIccFlashDiskAllResult
                obmFlashDiskAllResult = (sObmFlashDiskAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Home Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", obmFlashDiskAllResult->homeStats.homeStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", obmFlashDiskAllResult->homeStats.homeStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", obmFlashDiskAllResult->homeStats.homeStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", obmFlashDiskAllResult->homeStats.homeStats.totalFolders);
                fprintf(filePtr,"\n BackUp Partition: \n");
                fprintf(filePtr," Flash Disk Total Size:     %u\n", obmFlashDiskAllResult->homeStats.backupStats.totalSize);
                fprintf(filePtr," Flash Disk Free space:     %u\n", obmFlashDiskAllResult->homeStats.backupStats.freeSpace);
                //fprintf(filePtr," Flash Disk speed:          %u\n", obmFlashDiskAllResult->homeStats.backupStats.speed);
                fprintf(filePtr," Flash Disk total Folder:   %u\n", obmFlashDiskAllResult->homeStats.backupStats.totalFolders);
                if(obmFlashDiskAllResult->patternWriteResult.errCode == 0)
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Read  and write Operation on Reserved Area  Test:   Fail\n");
                }

                if(obmFlashDiskAllResult->eraseWriteResult.errCode == 0)
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
            case TEST_ID_OBM_FD_1:
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
            case TEST_ID_OBM_FD_2:
              {
                sPmDiagResHdr *pmDiagResHdr;
                pmDiagResHdr = (sPmDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmDiagResHdr->errCode == 0)
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
            case TEST_ID_OBM_FD_3:
              {
                sPmDiagResHdr *pmDiagResHdr;
                pmDiagResHdr = (sPmDiagResHdr*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(pmDiagResHdr->errCode == 0)
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
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for OBM FLASHDISK ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;

      case DIAGNOS_TCT_OBM_FAN:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
	  {
	      case TEST_ID_FAN_ALL:
        {
                sObmFanAllTestResult *obmFanAllTestResult; 
                obmFanAllTestResult = (sObmFanAllTestResult *)(((sDiagnosticResult*)BpmRespPtr)->data);
                if(obmFanAllTestResult->connectivityCheck.errCode == 0)
                fprintf(filePtr,"\n Fanspeed, Fan&OBM Connectivity Result : Pass\n\n");
                else
                fprintf(filePtr,"\n Fanspeed, Fan&OBM Connectivity Result : Fail \n\n");
								for(fanIndex = 0;fanIndex < 2 ;fanIndex++)
								{
									fprintf(filePtr, "Fan[%d] Speed: %d\n",fanIndex+1,obmFanAllTestResult->changeFanSpeed.Speed[fanIndex]);  
									fflush(filePtr);
								}
                
								/* cp post string prepairation */
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

	      case TEST_ID_FAN_1:
        {
                sObmFanDiagSpeedRes *obmFanDiagSpeedRes;
                obmFanDiagSpeedRes = (sObmFanDiagSpeedRes *)(((sDiagnosticResult*)BpmRespPtr)->data);
                fprintf(filePtr,"\n Fanspeed\n\n");
								for(fanIndex = 0;fanIndex < 2 ;fanIndex++)
								{
									fprintf(filePtr, "Fan[%d] Speed: %d\n",fanIndex+1,obmFanDiagSpeedRes->Speed[fanIndex]);  
									fflush(filePtr);
								}

						/* cp post string prepairation */
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
	      case TEST_ID_FAN_2:
          {
             sObmFanDiagRes *obmFanDiagRes;
             obmFanDiagRes = (sObmFanDiagRes *)(((sDiagnosticResult*)BpmRespPtr)->data);
             if(obmFanDiagRes->errCode == 0)
             fprintf(filePtr,"\n Fan&OBM Connectivity Result : Pass\n\n");
             else
             fprintf(filePtr,"\n Fan&OBM Connectivity Result : Fail \n\n");
						/* cp post string prepairation */
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
		  LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for FAN ", 
			  ((sDiagnosticResult*)BpmRespPtr)->testID);
		  break;
	  }
        }
	break;

      default:
        LOG_PRINT(CRITICAL,"DiagLib: TEST TYPE '%d' not defined for OBM", 
            ((sDiagnosticResult*)BpmRespPtr)->testType);
        break;
    }
  }
}
