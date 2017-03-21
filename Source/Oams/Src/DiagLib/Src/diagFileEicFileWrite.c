#include "bpmDiaglib.h"
#include "bpmInclude.h"
extern FILE *filePtr; 
extern sLibGlobalParam libGlobalParam;
extern sParamKeySet paramKeySet[MAX_TCT_ID][MAX_TEST_ID];

void writeEicDetailInFile(void *BpmRespPtr)
{
  I_U8 i;
  if(libGlobalParam.suppress)
  {
  }
  else
  {
    switch(((sDiagnosticResult*)BpmRespPtr)->testType)
    {
      case DIAGNOS_TCT_EIC_FRAMER:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
	  {
            case TEST_ID_EIC_FRAMER_1:
              {
                sEicFramerInfo *eicFramerInfo;
                eicFramerInfo = (sEicFramerInfo*)(((sDiagnosticResult*)BpmRespPtr)->data);
                fprintf(filePtr,"<Port:                      %d>\n", eicFramerInfo->portId);
                if(eicFramerInfo->portConfStatus == 1)
                {
                  fprintf(filePtr," Port Configuration Status: Activated(1)\n");
                }
                else
                {
                  fprintf(filePtr," Port Configuration Status: Deactivated(0)\n");
                }
		switch(eicFramerInfo->portMode)
		{
		    case BPM_TRUNK_TYPE_E1:
			fprintf(filePtr," Port Mode(E1/T1):          E1(1)\n");
			break;
		    case BPM_TRUNK_TYPE_T1:
			fprintf(filePtr," Port Mode(E1/T1):          T1(2)\n");
			break;
		    case BPM_TRUNK_TYPE_INVALID:
			fprintf(filePtr," Port Mode(E1/T1):    Invalid(0)\n");
			break;
		}
		switch(eicFramerInfo->loopType)
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
                if(eicFramerInfo->loopStatus == 0)
                {
                  fprintf(filePtr," Loopback Status:           Disable(0)\n");
                }
                else
                {
                  fprintf(filePtr," Loopback Status:           Enable(1)\n");
                }
		switch(eicFramerInfo->framing)
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
		switch(eicFramerInfo->lineCoding)
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
		switch(eicFramerInfo->sigStrength)
		{
		    case BPM_TRUNK_SIG_STRENGH_0:
			fprintf(filePtr," sigStrength:         Sig Strength_0(0)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGH_1:
			fprintf(filePtr," sigStrength:         Sig Strength_1(1)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGH_2:
			fprintf(filePtr," sigStrength:         Sig Strength_2(2)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGH_3:
			fprintf(filePtr," sigStrength:         Sig Strength_3(3)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGH_4:
			fprintf(filePtr," sigStrength:         Sig Strength_4(4)\n");
			break;
		    case BPM_TRUNK_SIG_STRENGTH_INVALID:
			fprintf(filePtr," sigStrength:         Invalid Sig Strength(0xFF)\n");
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
            case TEST_ID_EIC_FRAMER_2:
              {
                sEicFramerPortRTInfo *eicFramerPortRTInfo;
                eicFramerPortRTInfo = (sEicFramerPortRTInfo*)(((sDiagnosticResult*)BpmRespPtr)->data);
                fprintf(filePtr,"<Port:                                                %d>\n", eicFramerPortRTInfo->portId);
                if(eicFramerPortRTInfo->portConfStatus == 1)
                {
                  fprintf(filePtr," Port Configuration Status:                           Activated(1)\n");
                }
                else
                {
                  fprintf(filePtr," Port Configuration Status:                           Deactivated(0)\n");
                }
                if(eicFramerPortRTInfo->liuLos == 0)
                {
                  fprintf(filePtr," Line interface unit LOS:                             Present(0)\n");
                }
                else
                {
                  fprintf(filePtr," Line interface unit LOS:                             Absent(1)\n");
                }
                if(eicFramerPortRTInfo->rxLoss == 0)
                {
                  fprintf(filePtr," Rx LOS:                                              Present(0)\n");
                }
                else
                {
                  fprintf(filePtr," Rx LOS:                                              Enable(1)\n");
                }
                if(eicFramerPortRTInfo->frameLoss  == 0)
                {
                  fprintf(filePtr," FrameLoss:                                           Present(0)\n" );
                }
                else
                {
                  fprintf(filePtr," FrameLoss:                                           Enable(1)\n");
                }
                if(eicFramerPortRTInfo->isPortUp == 1)
                {
                  fprintf(filePtr," Port Status:                                         UP(1)\n");
                }
                else
                {
                  fprintf(filePtr," Port Status:                                         Down(0)\n");
                }
                fprintf(filePtr,"\n LIU Jitter Attenuator Limit Trip Clear:              %u\n", eicFramerPortRTInfo->framerPegs.liu_clr_jitter_attenuator_limit_trip);
                fprintf(filePtr," LIU Open-Circuit Clear Detected:                     %u\n", eicFramerPortRTInfo->framerPegs.liu_clr_open_ckt_detect);
                fprintf(filePtr," LIU Short-Circuit Clear Detected:                    %u\n", eicFramerPortRTInfo->framerPegs.liu_clr_short_ckt_detect);
                fprintf(filePtr," LIU Loss of Signal Clear Detected:                   %u\n", eicFramerPortRTInfo->framerPegs.liu_clr_los_detect);
                fprintf(filePtr," LIU Jitter Attenuator Limit Trip Set:                %u\n", eicFramerPortRTInfo->framerPegs.liu_jitter_attenuator_limit_trip);
                fprintf(filePtr," LIU Open-Circuit Detect:                             %u\n", eicFramerPortRTInfo->framerPegs.liu_open_ckt_detect);
                fprintf(filePtr," LIU Short-Circuit Detect:                            %u\n", eicFramerPortRTInfo->framerPegs.liu_short_ckt_detect);
                fprintf(filePtr," LIU Loss of Signal Detect:                           %u\n", eicFramerPortRTInfo->framerPegs.liu_los_detect);
                fprintf(filePtr," Receive Remote Alarm Set Clear:                      %u\n", eicFramerPortRTInfo->framerPegs.rx_remote_alarmInd_clr);
                fprintf(filePtr," Receive Alarm Set Clear:                             %u\n", eicFramerPortRTInfo->framerPegs.rx_alarm_condition_clr);
                fprintf(filePtr," Receive Loss of Signal Clear:                        %u\n", eicFramerPortRTInfo->framerPegs.rx_los_clr);
                fprintf(filePtr," Receive Loss of Frame Clear:                         %u\n", eicFramerPortRTInfo->framerPegs.rx_lof_clr);
                fprintf(filePtr," Receive Remote Alarm Set Condition:                  %u\n", eicFramerPortRTInfo->framerPegs.rx_remote_alarmInd);
                fprintf(filePtr," Receive Alarm Set Condition:                         %u\n", eicFramerPortRTInfo->framerPegs.rx_alarm_condition);
                fprintf(filePtr," Receive Loss of Signal Set:                          %u\n", eicFramerPortRTInfo->framerPegs.rx_los);
                fprintf(filePtr," Receive Loss of Frame Set:                           %u\n", eicFramerPortRTInfo->framerPegs.rx_lof);

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
            case TEST_ID_EIC_FRAMER_3:
              {
                sPortLoopBackAnalogLocalRes *portLoopBackAnalogLocalRes;
                portLoopBackAnalogLocalRes = (sPortLoopBackAnalogLocalRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"<Port:                      %d>\n", portLoopBackAnalogLocalRes->portId);

                if(portLoopBackAnalogLocalRes->loopAnalogRes.errCode == 0)
                {
                  fprintf(filePtr," Analog  Loop Back:         Pass\n" );
                }
                else
                {
                  fprintf(filePtr," Analog  Loop Back:         Fail\n" );
                }

                fprintf(filePtr,"Bit Error Rate:             %d\n", portLoopBackAnalogLocalRes->loopAnalogRes.berErrorCnt);

                if(portLoopBackAnalogLocalRes->loopLocalRes.errCode == 0)
                {
                  fprintf(filePtr," Local Loop Back:           Pass\n" );
                }
                else
                {
                  fprintf(filePtr," Local Loop Back:           Fail\n" );
                }

                fprintf(filePtr,"Bit Error Rate:             %d\n", portLoopBackAnalogLocalRes->loopLocalRes.berErrorCnt);

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
            case TEST_ID_EIC_FRAMER_4:
              {
                sPortLoopResult *remoteLoopResult;
                remoteLoopResult = (sPortLoopResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"<Port:                      %d>\n", remoteLoopResult->portId);

                if(remoteLoopResult->loopBackRes.errCode == 0)
                {
                  fprintf(filePtr," Remote Loop Back:          Pass\n" );
                }
                else
                {
                  fprintf(filePtr," Remote Loop Back:          Fail\n" );
                }

                fprintf(filePtr,"Bit Error Rate:             Not Applicable\n");

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
            case TEST_ID_EIC_FRAMER_5:
              {
                sOverallPortLoopResult *overallLoopBackResult;
                overallLoopBackResult = (sOverallPortLoopResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"<Port:                                    %d>\n", overallLoopBackResult->portId);

                if(overallLoopBackResult->localLoopBackResult.errCode == 0)
                {
                  fprintf(filePtr," Internal Digital and  Analog  Loop Back: Pass\n" );
                }
                else
                {
                  fprintf(filePtr," Internal Digital and  Analog  Loop Back: Fail\n");
                }

                fprintf(filePtr,"Bit Error Rate:                           %d\n", overallLoopBackResult->localLoopBackResult.berErrorCnt);

                if(overallLoopBackResult->remoteLoopBackResult.errCode == 0)
                {
                  fprintf(filePtr," Remote Loop Back:                        Pass\n");
                }
                else
                {
                  fprintf(filePtr," Remote Loop Back:                        Fail\n");
                }

                fprintf(filePtr,"Bit Error Rate:                           Not Applicable\n");

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
            case TEST_ID_EIC_FRAMER_6:
              {
                sLoopBackResult *tdmConnectivityResult;
                tdmConnectivityResult = (sLoopBackResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"<Port:                      %d>\n", tdmConnectivityResult->portId);

                if(tdmConnectivityResult->loopBackResult.errCode == 0)
                {
                  fprintf(filePtr," TDM Connectivity Test:   Pass\n");
                }
                else
                {
                  fprintf(filePtr," TDM Connectivity Test:   Fail\n");
                }

                fprintf(filePtr,"Bit Error Rate:             %d\n", tdmConnectivityResult->loopBackResult.berErrorCnt);

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
		  LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for EIC FRAMER", 
			  ((sDiagnosticResult*)BpmRespPtr)->testID);
		  break;
	  }
        }
	break;
      case DIAGNOS_TCT_EIC_ETHERNET_CP:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_EIC_CP_ETH_ALL:
              {
                sEicCpPortAllResult *eicDiagCpPortAllRes;
                eicDiagCpPortAllRes = (sEicCpPortAllResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr," Ethernet PortId:           %d\n", eicDiagCpPortAllRes->eicCpPortStats.ethPortId);
                fprintf(filePtr," Ethernet Port Mac Address: %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    eicDiagCpPortAllRes->eicCpPortStats.macAddr[0], eicDiagCpPortAllRes->eicCpPortStats.macAddr[1],
                    eicDiagCpPortAllRes->eicCpPortStats.macAddr[2], eicDiagCpPortAllRes->eicCpPortStats.macAddr[3],
                    eicDiagCpPortAllRes->eicCpPortStats.macAddr[4], eicDiagCpPortAllRes->eicCpPortStats.macAddr[5]);

                fprintf(filePtr," IP address:                %d.%d.%d.%d\n", eicDiagCpPortAllRes->eicCpPortStats.ipAddr[0],
                    eicDiagCpPortAllRes->eicCpPortStats.ipAddr[1], eicDiagCpPortAllRes->eicCpPortStats.ipAddr[2],
                    eicDiagCpPortAllRes->eicCpPortStats.ipAddr[3]);


                fprintf(filePtr," Transmitted Packet:        %u\n", eicDiagCpPortAllRes->eicCpPortStats.txPkts);
                fprintf(filePtr," Received Packet:           %u\n", eicDiagCpPortAllRes->eicCpPortStats.rxPkts);
                fprintf(filePtr," Transmitted Byte:          %u\n", eicDiagCpPortAllRes->eicCpPortStats.txBytes);
                fprintf(filePtr," Received Byte:             %u\n", eicDiagCpPortAllRes->eicCpPortStats.rxBytes);
                fprintf(filePtr," Number of Collisions:      %u\n", eicDiagCpPortAllRes->eicCpPortStats.collisions);
                fprintf(filePtr," Transmitted Packet Dropped:%u\n", eicDiagCpPortAllRes->eicCpPortStats.txPktDrop);
                fprintf(filePtr," Received Packet  Dropped:  %u\n", eicDiagCpPortAllRes->eicCpPortStats.rxPktDrop);

                if(eicDiagCpPortAllRes->autoNegResult.diagRes.errCode == 0)
                {
                  fprintf(filePtr," Activate Auto-Negotiation Operation Test :   Pass\n");
                }
                else
                {
                  fprintf(filePtr," Activate Auto-Negotiation Operation Test :   Fail\n");
                }

                if(eicDiagCpPortAllRes->forcedNegResult.diagRes.errCode == 0)
                {
                  fprintf(filePtr," Forced Configuration Operation Test :   Pass\n");
                }
                else
                {
                  fprintf(filePtr," Forced Configuration Operation Test :   Fail\n");
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
            case TEST_ID_EIC_CP_ETH_1:
              {
                sEicEthPortStats *eicCpEthPortStats;
                eicCpEthPortStats = (sEicEthPortStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\nEthernet Port:              %d\n", eicCpEthPortStats->ethPortId);
                fprintf(filePtr," Ethernet Port Mac Address: %02x.%02x.%02x.%02x.%02x.%02x\n", 
                    eicCpEthPortStats->macAddr[0], eicCpEthPortStats->macAddr[1],
                    eicCpEthPortStats->macAddr[2], eicCpEthPortStats->macAddr[3],
                    eicCpEthPortStats->macAddr[4], eicCpEthPortStats->macAddr[5]);

                fprintf(filePtr," IP address:                %d.%d.%d.%d\n", eicCpEthPortStats->ipAddr[0],
                    eicCpEthPortStats->ipAddr[1], eicCpEthPortStats->ipAddr[2],
                    eicCpEthPortStats->ipAddr[3]);

                fprintf(filePtr," Transmitted Packet:        %u\n", eicCpEthPortStats->txPkts);
                fprintf(filePtr," Received Packet:           %u\n", eicCpEthPortStats->rxPkts);
                fprintf(filePtr," Transmitted Byte:          %u\n", eicCpEthPortStats->txBytes);
                fprintf(filePtr," Received Byte:             %u\n", eicCpEthPortStats->rxBytes);
                fprintf(filePtr," Number of Collisions:      %u\n", eicCpEthPortStats->collisions);
                fprintf(filePtr," Transmitted Packet Dropped:%u\n", eicCpEthPortStats->txPktDrop);
                fprintf(filePtr," Received Packet  Dropped:  %u\n", eicCpEthPortStats->rxPktDrop);

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
            case TEST_ID_EIC_CP_ETH_2:
              {
                sEicCpPortAutoNegRes *eicCpPortAutoNegRes;
                eicCpPortAutoNegRes = (sEicCpPortAutoNegRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\nEthernet Port:              %d\n", eicCpPortAutoNegRes->ethPortId);
                if(eicCpPortAutoNegRes->diagRes.errCode == 0)
                {
                  fprintf(filePtr," Activate Auto-Negotiation Operation Test :   Pass\n");
                }
                else
                {
                  fprintf(filePtr," Activate Auto-Negotiation Operation Test :   Fail\n");
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

            case TEST_ID_EIC_CP_ETH_3:
              {
                sEicCpPortForcedNegRes *eicCpPortForcedNegRes;
                eicCpPortForcedNegRes = (sEicCpPortForcedNegRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\nEthernet Port:              %d\n", eicCpPortForcedNegRes->ethPortId);

                if(eicCpPortForcedNegRes->diagRes.errCode == 0)
                {
                  fprintf(filePtr," Forced Configuration Operation Test :   Pass\n");
                }
                else
                {
                  fprintf(filePtr," Forced Configuration Operation Test :   Fail\n");
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
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for EIC ETH CP ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;

      case DIAGNOS_TCT_EIC_ETHERNET_SWITCH:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_EIC_SW_ETH_1:
              {
                sEicCpPortAutoNegRes *switchPortLoopRes;
                switchPortLoopRes = (sEicCpPortAutoNegRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

		for(i=0 ;i< MAX_ETH_SW_PORTS; i++)
		{
		    fprintf(filePtr,"\nEthernet Switch Port:   %d\n", switchPortLoopRes->ethPortId);
		    if(switchPortLoopRes->diagRes.errCode == 0)
		    {
			fprintf(filePtr," Loopback Test :    Pass\n");
		    }
		    else
		    {
			fprintf(filePtr," Loopback Test :    Fail\n");
		    }

		    switchPortLoopRes++;
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
            case TEST_ID_EIC_SW_ETH_2:
	      {
                sEicCpPortAutoNegRes *switchPortScanRes;
                switchPortScanRes = (sEicCpPortAutoNegRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

		for(i=0 ;i< MAX_ETH_SW_PORTS; i++)
		{
		    fprintf(filePtr,"\nEthernet Switch Port:   %d\n", switchPortScanRes->ethPortId);
		    if(switchPortScanRes->diagRes.errCode == 0)
		    {
			fprintf(filePtr," Scan Ethernet Switch Port Test :   Pass\n");
		    }
		    else
		    {
			fprintf(filePtr," Scan Ethernet Switch Port Test :   Fail\n");
		    }

		    switchPortScanRes++;
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
            case TEST_ID_EIC_SW_ETH_3:
	      {
                sEicSwEthPortStats *eicSwEthPortStats;
                eicSwEthPortStats = (sEicSwEthPortStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

		fprintf(filePtr,"\nEthernet Switch Port:                               %u\n", eicSwEthPortStats->portNum);
		fprintf(filePtr," Lower 32 bits of Good Octets Received:               %u\n",eicSwEthPortStats->ethPortInfo.nr_in_good_octets_low);
		fprintf(filePtr," Higher 32 bits of Good Octets Received:              %u\n",eicSwEthPortStats->ethPortInfo.nr_in_good_octets_hi);
		fprintf(filePtr," Bad Octets Received:                                 %u\n",eicSwEthPortStats->ethPortInfo.nr_in_bad_octets);
		fprintf(filePtr," Unicast Good Frames Received:                        %u\n",eicSwEthPortStats->ethPortInfo.nr_in_unicasts);
		fprintf(filePtr," Broadcast Good Frames Received:                      %u\n",eicSwEthPortStats->ethPortInfo.nr_in_broadcasts);
		fprintf(filePtr," Multicast Good Frames Received:                      %u\n",eicSwEthPortStats->ethPortInfo.nr_in_multicasts);
		fprintf(filePtr," Flow Controlled Good Frames Received:                %u\n",eicSwEthPortStats->ethPortInfo.nr_in_pause);
		fprintf(filePtr," Undersize Frames Received with Valid FCS:            %u\n",eicSwEthPortStats->ethPortInfo.nr_in_undersize);
		fprintf(filePtr," Undersize Frames Received with Invalid FCS:          %u\n",eicSwEthPortStats->ethPortInfo.nr_in_fragments);
		fprintf(filePtr," Oversize Frames Received with Valid FCS:             %u\n",eicSwEthPortStats->ethPortInfo.nr_in_oversize);
		fprintf(filePtr," Oversize Frames Received with Invalid FCS:           %u\n",eicSwEthPortStats->ethPortInfo.nr_in_jabber);
		fprintf(filePtr," Frames Received with RxErr:                          %u\n",eicSwEthPortStats->ethPortInfo.nr_in_rx_error);
		fprintf(filePtr," Frames Received with FCSErr:                         %u\n",eicSwEthPortStats->ethPortInfo.nr_in_fcs_error);
		fprintf(filePtr," Lower 32 bits of Good Octets Sent :                  %u\n",eicSwEthPortStats->ethPortInfo.nr_out_octets_low);
		fprintf(filePtr," Higher 32 bits of Good Octets Sent :                 %u\n",eicSwEthPortStats->ethPortInfo.nr_out_octets_hi);
		fprintf(filePtr," Unicast Good Frames Sent :                           %u\n",eicSwEthPortStats->ethPortInfo.nr_out_unicasts);
		fprintf(filePtr," Broadcast Good Frames Sent :                         %u\n",eicSwEthPortStats->ethPortInfo.nr_out_broadcasts);
		fprintf(filePtr," Multicast Good Frames Sent :                         %u\n",eicSwEthPortStats->ethPortInfo.nr_out_multicasts);
		fprintf(filePtr," Flow Controlled Good Frames Sent :                   %u\n",eicSwEthPortStats->ethPortInfo.nr_out_pause);
		fprintf(filePtr," Frames Sent and Delayed:                             %u\n",eicSwEthPortStats->ethPortInfo.nr_out_deferred);
		fprintf(filePtr," Collision Events in Sent Frames:                     %u\n",eicSwEthPortStats->ethPortInfo.nr_out_collisions);
		fprintf(filePtr," Successful Sent Frames with Single Collision:        %u\n",eicSwEthPortStats->ethPortInfo.nr_out_one_collision);
		fprintf(filePtr," Successful Sent Frames with Multiple Collision:      %u\n",eicSwEthPortStats->ethPortInfo.nr_out_many_collisions);
		fprintf(filePtr," Frames dropped due to Excessive Collision:           %u\n",eicSwEthPortStats->ethPortInfo.nr_out_excessive_collisions);
		fprintf(filePtr," Number of collision detected Later:                  %u\n",eicSwEthPortStats->ethPortInfo.nr_out_late);
		fprintf(filePtr," Frames Tx with FCS Error:                            %u\n",eicSwEthPortStats->ethPortInfo.nr_out_fcs_error);
		fprintf(filePtr," Frames Rx/Tx with length 64 octets:                  %u\n",eicSwEthPortStats->ethPortInfo.nr_octets64);
		fprintf(filePtr," Frames Rx/Tx with length between 65 and 127:         %u\n",eicSwEthPortStats->ethPortInfo.nr_octets127);
		fprintf(filePtr," Frames Rx/Tx with length between 128 and 255:        %u\n",eicSwEthPortStats->ethPortInfo.nr_octets255);
		fprintf(filePtr," Frames Rx/Tx with length between 256 and 511:        %u\n",eicSwEthPortStats->ethPortInfo.nr_octets511);
		fprintf(filePtr," Frames Rx/Tx with length between 512 and 1023:       %u\n",eicSwEthPortStats->ethPortInfo.nr_octets1023);
		fprintf(filePtr," Frames Rx/Tx with length between 1024 and MaxSize:   %u\n",eicSwEthPortStats->ethPortInfo.nr_octetsmax);

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
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for EIC ETH SWITCH ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;

      case DIAGNOS_TCT_EIC_DSP:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_EIC_DSP_ALL:
              {
                sEicDspAllTestRes *eicDspAllTestResult;
                eicDspAllTestResult = (sEicDspAllTestRes*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(eicDspAllTestResult->conRes.ppDspConCheckRes.errCode == 0)
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the Protocol Processor and  DSP : Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the Protocol Processor and  DSP : Fail\n");
                }

                if(eicDspAllTestResult->conRes.eicDspConCheckRes.diagRes.errCode == 0)
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the EIC PP and  DSP :             Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the EIC PP and  DSP :             Fail\n");
                }

                if(eicDspAllTestResult->ifRes.diagRes.errCode == 0)
                {
                  fprintf(filePtr,"\n DSI  connectivity between the Protocol Processor and  DSP:      Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n DSI  connectivity between the Protocol Processor and  DSP:      Fail\n");
                }

                if(eicDspAllTestResult->rdWrRes.diagRes.errCode == 0)
                {
                  fprintf(filePtr,"\n DSP internal Memory Read/Write Test  :                          Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n DSP internal Memory Read/Write Test  :                          Fail\n");
                }

                if(eicDspAllTestResult->loopRes.loopRes.errCode == 0)
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI:                Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI:                Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:                                                 %d\n", eicDspAllTestResult->loopRes.loopRes.berErrorCnt);

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
            case TEST_ID_EIC_DSP_1:
              {
                sEicPPDspConCheckResult *eicDspConCheckResult;
                eicDspConCheckResult = (sEicPPDspConCheckResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(eicDspConCheckResult->ppDspConCheckRes.errCode == 0)
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the ICC PP and  DSP : Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the ICC PP and  DSP : Fail\n");
                }

                if(eicDspConCheckResult->eicDspConCheckRes.diagRes.errCode == 0)
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the EIC PP and  DSP : Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n Ethernet connectivity between the EIC PP and  DSP : Fail\n");
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
            case TEST_ID_EIC_DSP_2:
              {
                sEicDspDsiIfResult *eicDspDsiIfResult;
                eicDspDsiIfResult = (sEicDspDsiIfResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(eicDspDsiIfResult->diagRes.errCode == 0)
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
            case TEST_ID_EIC_DSP_3:
              {
                sEicDspRdWrResult *eicDspRdWrResult;
                eicDspRdWrResult = (sEicDspRdWrResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                if(eicDspRdWrResult->diagRes.errCode == 0)
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
            case TEST_ID_EIC_DSP_4:
              {
                sEicDspLoopResult *eicDspLoopBackRes;
                eicDspLoopBackRes = (sEicDspLoopResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                fprintf(filePtr,"\n Dsp Id:                                            %d\n", eicDspLoopBackRes->dspId);
                if(eicDspLoopBackRes->loopRes.errCode == 0)
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI:   Pass\n");
                }
                else
                {
                  fprintf(filePtr,"\n TDM Stream BER testing between the DSP and  TSI:   Fail\n");
                }
                fprintf(filePtr,"\n Bit Error Rate:                                    %d\n", eicDspLoopBackRes->loopRes.berErrorCnt);

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
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for EIC DSP ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;

      case DIAGNOS_TCT_EIC_CPLD:
        {
          switch(((sDiagnosticResult*)BpmRespPtr)->testID)
          {
            case TEST_ID_EIC_CPLD_ALL:
              {
                sEicCpldAllTestResult *eicCpldAllTestResult;
                eicCpldAllTestResult = (sEicCpldAllTestResult*)(((sDiagnosticResult*)BpmRespPtr)->data);

                switch(eicCpldAllTestResult->eicCpldStats.selfCardState)
                {
                  case BPM_EIC_ENABLE:
                    fprintf(filePtr," Self Card State :                        Enable(1)\n");
                    break;

                  case BPM_EIC_DISABLE:
                    fprintf(filePtr," Self Card State :                        Disable(0)\n");
                    break;

		  default:
                    fprintf(filePtr," Self Card State :                        Invalid(%d)\n",eicCpldAllTestResult->eicCpldStats.selfCardState);
                    break;
                }

                switch(eicCpldAllTestResult->eicCpldStats.peerCardState)
                {
                  case BPM_EIC_ENABLE:
                    fprintf(filePtr," Peer Card State :                        Enable(1)\n");
                    break;

                  case BPM_EIC_DISABLE:
                    fprintf(filePtr," Peer Card State :                        Disable(0)\n");
                    break;

		  default:
                    fprintf(filePtr," Peer Card State :                        Invalid(%d)\n",eicCpldAllTestResult->eicCpldStats.peerCardState);
                    break;
                }

		switch(eicCpldAllTestResult->eicCpldStats.tdmLinkSelection)
		{
		    case 0:
			fprintf(filePtr," TDM Link Selection C0/C1 =               C0(0)\n");
			break;
		    case 1:
			fprintf(filePtr," TDM Link Selection C0/C1 =               C1(1)\n");
			break;
		    default:
			fprintf(filePtr," TDM Link Selection C0/C1 =               Invalid(%d)\n",eicCpldAllTestResult->eicCpldStats.tdmLinkSelection);
			break;
		}

		switch(eicCpldAllTestResult->eicCpldStats.clkStatus)
		{
		    case REFERENCE_MATE_CLK:
			fprintf(filePtr," Selected TDM CLK Internal/External =     Mate EIC Card(73)\n");
			break;
		    case REFERENCE_INTERNAL_CLK:
			fprintf(filePtr," Selected TDM CLK Internal/External =     Internal(74)\n");
			break;
		    case REFERENCE_EXTERNAL_CLK:
			fprintf(filePtr," Selected TDM CLK Internal/External =     External(75)\n");
			break;
		    default:
			fprintf(filePtr," Selected TDM CLK Internal/External =     Invalid(%d)\n",eicCpldAllTestResult->eicCpldStats.clkStatus);
			break;
		}

                fprintf(filePtr,"\n CPLD Verson :                            %d.%d.%d\n",
			((eicCpldAllTestResult->eicCpldReg.mjver & 0xF0) >> 4),
			(eicCpldAllTestResult->eicCpldReg.mjver & 0x0F),
			(eicCpldAllTestResult->eicCpldReg.mnver & 0x0F));
                fprintf(filePtr," Card Identification:                     0x%02x\n",eicCpldAllTestResult->eicCpldReg.cir);

		fprintf(filePtr,"\nSelf Status Register:\n");

		if(eicCpldAllTestResult->eicCpldReg.ssr & 0x80)
		{
		    fprintf(filePtr," Clock Status =                           Clock0 Normal(1)\n");
		}
		else
		{
		    fprintf(filePtr," Clock Status =                           Clock0 Failure(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.ssr & 0x40)
		{
		    fprintf(filePtr," Clock Status =                           Clock1 Normal(1)\n");
		}
		else
		{
		    fprintf(filePtr," Clock Status =                           Clock1 Failure(0)\n");
		}

                fprintf(filePtr,"\nWatch Dog Timer/DPLL Status Register: \n");

		if(eicCpldAllTestResult->eicCpldReg.wdr & 0x80)
		{
		    fprintf(filePtr," Watch Dog Timer Enable =                 Enable(1)\n");

		    if(eicCpldAllTestResult->eicCpldReg.wdr & 0x20)
		    {
			fprintf(filePtr," Watch Dog Timer Processor Status =       Running(1), Processor is Good\n");
		    }
		    else
		    {
			fprintf(filePtr," Watch Dog Timer Processor Status =       Timeout(0),Processor is Failed\n");
		    }
		}
		else
		{
		    fprintf(filePtr," Watch Dog Timer Enable =                 Disable(0)\n");
		}

                fprintf(filePtr,"\nClock Buffer Control Register: \n");
		if(eicCpldAllTestResult->eicCpldReg.cbcr & 0x01)
		{
		    fprintf(filePtr," TDM Clk to Card0 =                       Enabled(1)\n");
		}
		else
		{
		    fprintf(filePtr," TDM Clk to Card0 =                       Disabled(0)\n");
		}
		
		if(eicCpldAllTestResult->eicCpldReg.cbcr & 0x02)
		{
		    fprintf(filePtr," TDM Clk to Card1 =                       Enabled(1)\n");
		}
		else
		{
		    fprintf(filePtr," TDM Clk to Card1 =                       Disabled(0)\n");
		}
		
		if(eicCpldAllTestResult->eicCpldReg.cbcr & 0x04)
		{
		    fprintf(filePtr," TDM Clk to Card2 =                       Enabled(1)\n");
		}
		else
		{
		    fprintf(filePtr," TDM Clk to Card2 =                       Disabled(0)\n");
		}
		
		if(eicCpldAllTestResult->eicCpldReg.cbcr & 0x08)
		{
		    fprintf(filePtr," TDM Clk to Card3 =                       Enabled(1)\n");
		}
		else
		{
		    fprintf(filePtr," TDM Clk to Card3 =                       Disabled(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.cbcr & 0x10)
		{
		    fprintf(filePtr," TDM Clk to Card4 =                       Enabled(1)\n");
		}
		else
		{
		    fprintf(filePtr," TDM Clk to Card4 =                       Disabled(0)\n");
		}
		
		if(eicCpldAllTestResult->eicCpldReg.cbcr & 0x20)
		{
		    fprintf(filePtr," TDM Clk to Card5 =                       Enabled(1)\n");
		}
		else
		{
		    fprintf(filePtr," TDM Clk to Card5 =                       Disabled(0)\n");
		}
		
                fprintf(filePtr,"\nFrame Control Register: \n");
		if(eicCpldAllTestResult->eicCpldReg.fcr & 0x08)
		{
		    fprintf(filePtr," Transmit Enable for the Framer's LIU =   Enabled(1)\n");
		}
		else
		{
		    fprintf(filePtr," Transmit Enable for the Framer's LIU =   Disabled(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.fcr & 0x04)
		{
		    fprintf(filePtr," Framer REF_CLK_SEL to Backplane =        Framer1(1)\n");
		}
		else
		{
		    fprintf(filePtr," Framer REF_CLK_SEL to Backplane =        Framer0(0)\n");
		}
		
		switch(eicCpldAllTestResult->eicCpldReg.fcr & 0x03)
		{
		    case 0x00:
			fprintf(filePtr," LIU_REF_CLK_SEL Mode =                   E1 Mode(00)\n");
			break;
		    case 0x01:
			fprintf(filePtr," LIU_REF_CLK_SEL Mode =                   T1 Mode(01)\n");
			break;
		    default:
			break;
		}

                fprintf(filePtr,"\nTDM Bus/Clk Select Register: \n");

		if(eicCpldAllTestResult->eicCpldReg.tbcsr & 0x80)
		{
		    fprintf(filePtr," TDM Link Selection C0/C1 =               C1(1)\n");
		}
		else
		{
		    fprintf(filePtr," TDM Link Selection C0/C1 =               C0(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.tbcsr & 0x20)
		{
		    fprintf(filePtr," RFN Sync/No Sync =                       Sync(1)\n");
		}
		else
		{
		    fprintf(filePtr," RFN Sync/No Sync =                       No Sync(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.tbcsr & 0x02)
		{
		    fprintf(filePtr," Selected TDM CLK/FS C0/C1 =              C1(1)\n");
		}
		else
		{
		    fprintf(filePtr," Selected TDM CLK/FS C0/C1 =              C0(0)\n");
		}

                fprintf(filePtr,"\nExtracted Clock select register: \n");
		switch(eicCpldAllTestResult->eicCpldReg.ecsr & 0xF0)
		{
		    case 0x00:
			fprintf(filePtr," Ref1 Clk extracted from Framer0 (0000)\n");
			break;
		    case 0x10:
			fprintf(filePtr," Ref1 Clk extracted from Framer1 (0001)\n");
			break;
		    case 0x20:
			fprintf(filePtr," Ref1 Clk extracted from B0 (0010)\n");
			break;
		    case 0x30:
			fprintf(filePtr," Ref1 Clk extracted from B1 (0011)\n");
			break;
		    case 0x40:
			fprintf(filePtr," Ref1 Clk extracted from E0 (0100)\n");
			break;
		    case 0x50:
			fprintf(filePtr," Ref1 Clk extracted from E1 (0101)\n");
			break;
		    case 0x60:
			fprintf(filePtr," Ref1 Clk extracted from External (0110)\n");
			break;
		    case 0x70:
			fprintf(filePtr," Ref1 Clk extracted from EIC Framer (0111)\n");
			break;
		    case 0x80:
			fprintf(filePtr," Ref1 8KHz derived from 26MHz Clk (1000)\n");
			break;
		    default:
			fprintf(filePtr," Ref1 Disable\n");
			break;
		}
		switch(eicCpldAllTestResult->eicCpldReg.ecsr & 0x0F)
		{
		    case 0x00:
			fprintf(filePtr," Ref0 Clk extracted from Framer0 (0000)\n");
			break;
		    case 0x10:
			fprintf(filePtr," Ref0 Clk extracted from Framer1 (0001)\n");
			break;
		    case 0x20:
			fprintf(filePtr," Ref0 Clk extracted from B0 (0010)\n");
			break;
		    case 0x30:
			fprintf(filePtr," Ref0 Clk extracted from B1 (0011)\n");
			break;
		    case 0x40:
			fprintf(filePtr," Ref0 Clk extracted from E0 (0100)\n");
			break;
		    case 0x50:
			fprintf(filePtr," Ref0 Clk extracted from E1 (0101)\n");
			break;
		    case 0x60:
			fprintf(filePtr," Ref0 Clk extracted from External (0110)\n");
			break;
		    case 0x70:
			fprintf(filePtr," Ref0 Clk extracted from EIC Framer (0111)\n");
			break;
		    case 0x80:
			fprintf(filePtr," Ref0 8KHz derived from 26MHz Clk (1000)\n");
			break;
		    default:
			fprintf(filePtr," Ref0 Disable\n");
			break;
		}

                fprintf(filePtr,"\nTDM Link/Clock Selection Register: \n");
		if(eicCpldAllTestResult->eicCpldReg.tlcsr & 0x80)
		{
		    fprintf(filePtr," DPLL monitor Disable/Enable =            Disable(1)\n");
		}
		else
		{
		    fprintf(filePtr," DPLL monitor Disable/Enable =            Enable(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.tlcsr & 0x40)
		{
		    fprintf(filePtr," copy1 Clock monitor Disable/Enable =     Disable(1)\n");
		}
		else
		{
		    fprintf(filePtr," copy1 Clock monitor Disable/Enable =     Enable(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.tlcsr & 0x20)
		{
		    fprintf(filePtr," copy0 Clock monitor Disable/Enable =     Disable(1)\n");
		}
		else
		{
		    fprintf(filePtr," copy0 Clock monitor Disable/Enable =     Enable(0)\n");
		}

		switch(eicCpldAllTestResult->eicCpldReg.tlcsr & 0x0C)
		{
		    case 0x00:
			fprintf(filePtr," TDM Link Selection Mode =            Copy0 (00)\n");
			break;
		    case 0x01:
			fprintf(filePtr," TDM Link Selection Mode =            Copy1 (01)\n");
			break;
		    case 0x02:
			fprintf(filePtr," TDM Link Selection Mode =            Auto-Mode (10)\n");
			break;
		    case 0x03:
			fprintf(filePtr," TDM Link Selection Mode =            Previous State (11)\n");
			break;
		}

		switch(eicCpldAllTestResult->eicCpldReg.tlcsr & 0x03)
		{
		    case 0x00:
			fprintf(filePtr," TDM Clock Selection Mode =               Copy0 (00)\n");
			break;
		    case 0x01:
			fprintf(filePtr," TDM Clock Selection Mode =               Copy1 (01)\n");
			break;
		    case 0x02:
			fprintf(filePtr," TDM Clock Selection Mode =               Auto-Mode (10)\n");
			break;
		    case 0x03:
			fprintf(filePtr," TDM Clock Selection Mode =               Previous State (11)\n");
			break;
		}

		fprintf(filePtr,"\nDPLL Reference input clock status Register:\n");
		if(eicCpldAllTestResult->eicCpldReg.wdr & 0x04)
		{
		    fprintf(filePtr," Ref clock from Mate card =               Absent(1)\n");
		}
		else
		{
		    fprintf(filePtr," Ref clock from Mate card =               Present(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.refclksts & 0x20)
		{
		    fprintf(filePtr," Ref clock from ICC-E1 card =             Present(1)\n");
		}
		else
		{
		    fprintf(filePtr," Ref clock from ICC-E1 card =             Absent(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.refclksts & 0x10)
		{
		    fprintf(filePtr," Ref clock from ICC-E0 card =             Present(1)\n");
		}
		else
		{
		    fprintf(filePtr," Ref clock from ICC-E0 card =             Absent(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.refclksts & 0x08)
		{
		    fprintf(filePtr," Ref clock from ICC-B1 card =             Present(1)\n");
		}
		else
		{
		    fprintf(filePtr," Ref clock from ICC-B1 card =             Absent(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.refclksts & 0x04)
		{
		    fprintf(filePtr," Ref clock from ICC-B0 card =             Present(1)\n");
		}
		else
		{
		    fprintf(filePtr," Ref clock from ICC-B0 card =             Absent(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.refclksts & 0x02)
		{
		    fprintf(filePtr," Ref clock from onboard Framer1 =         Present(1)\n");
		}
		else
		{
		    fprintf(filePtr," Ref clock from onboard Framer1 =         Absent(0)\n");
		}

		if(eicCpldAllTestResult->eicCpldReg.refclksts & 0x01)
		{
		    fprintf(filePtr," Ref clock from onboard Framer0 =         Present(1)\n");
		}
		else
		{
		    fprintf(filePtr," Ref clock from onboard Framer0 =         Absent(0)\n");
		}

                fprintf(filePtr,"\nCPLD Reg Dump :- \n");
                fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
                    eicCpldAllTestResult->eicCpldReg.mjver,
                    eicCpldAllTestResult->eicCpldReg.cir, eicCpldAllTestResult->eicCpldReg.dcr,
                    eicCpldAllTestResult->eicCpldReg.scr, eicCpldAllTestResult->eicCpldReg.ssr,
                    eicCpldAllTestResult->eicCpldReg.wdr, eicCpldAllTestResult->eicCpldReg.cbcr,
                    eicCpldAllTestResult->eicCpldReg.rccb3, eicCpldAllTestResult->eicCpldReg.rccb2,
                    eicCpldAllTestResult->eicCpldReg.rccb1, eicCpldAllTestResult->eicCpldReg.wlb1,
                    eicCpldAllTestResult->eicCpldReg.wlb2, eicCpldAllTestResult->eicCpldReg.fcr,
                    eicCpldAllTestResult->eicCpldReg.tbcsr, eicCpldAllTestResult->eicCpldReg.apr);
                fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
                    eicCpldAllTestResult->eicCpldReg.spr, eicCpldAllTestResult->eicCpldReg.swpr,
                    eicCpldAllTestResult->eicCpldReg.lrpr1, eicCpldAllTestResult->eicCpldReg.daclsb,
                    eicCpldAllTestResult->eicCpldReg.dacmsb, eicCpldAllTestResult->eicCpldReg.ecsr,
                    eicCpldAllTestResult->eicCpldReg.mnver, eicCpldAllTestResult->eicCpldReg.isr,
                    eicCpldAllTestResult->eicCpldReg.wlb3, eicCpldAllTestResult->eicCpldReg.wlb4,
                    eicCpldAllTestResult->eicCpldReg.tlcsr, eicCpldAllTestResult->eicCpldReg.esr1,
                    eicCpldAllTestResult->eicCpldReg.esr2, eicCpldAllTestResult->eicCpldReg.esr3,
		    eicCpldAllTestResult->eicCpldReg.esr4);
                fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
                    eicCpldAllTestResult->eicCpldReg.msr,
                    eicCpldAllTestResult->eicCpldReg.lrpr2, eicCpldAllTestResult->eicCpldReg.csid,
                    eicCpldAllTestResult->eicCpldReg.cpsnt, eicCpldAllTestResult->eicCpldReg.tlmen,
                    eicCpldAllTestResult->eicCpldReg.refclksts, eicCpldAllTestResult->eicCpldReg.dsp32bit,
                    eicCpldAllTestResult->eicCpldReg.e1los, eicCpldAllTestResult->eicCpldReg.tdmclkreg,
                    eicCpldAllTestResult->eicCpldReg.losstat);


		fprintf(filePtr, "\nDPLL Status Register: \n");
		fprintf(filePtr, "DPLL Configuration: \n");

		switch(eicCpldAllTestResult->eicDpllRegs.dpllConf.mode)
		{
		    case 0:
			fprintf(filePtr," DPLL Mode Select =                       Normal Mode(0)\n");
			break;
		    case 1:
			fprintf(filePtr," DPLL Mode Select =                       Holdover Mode(1)\n");
			break;
		    case 2:
			fprintf(filePtr," DPLL Mode Select =                       Free run Mode(2)\n");
			break;
		    case 3:
			fprintf(filePtr," DPLL Mode Select =                       Automatic Mode(3)\n");
			break;
		    default:
			fprintf(filePtr," DPLL Mode Select =                       Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllConf.mode);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllConf.refsel)
		{
		    case 0:
			fprintf(filePtr," DPLL Reference Clock Select =            REF0(00)\n");
			break;
		    case 1:
			fprintf(filePtr," DPLL Reference Clock Select =            REF1(01)\n");
			break;
		    case 2:
		    case 3:
			fprintf(filePtr," DPLL Reference Clock Select =            REF2(1x)\n");
			break;
		    default:
			fprintf(filePtr," DPLL Reference Clock Select =            Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllConf.refsel);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllConf.tie)
		{
		    case 0:
			fprintf(filePtr," TIE Reset =                              Reset(0)\n");
			break;
		    case 1:
			fprintf(filePtr," TIE Reset =                              No Action(1)\n");
			break;
		    default:
			fprintf(filePtr," TIE Reset =                              Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllConf.tie);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllConf.primary)
		{
		    case 0:
			fprintf(filePtr," Primary/Secondary Operation =            Primary(0)\n");
			break;
		    case 1:
			fprintf(filePtr," Primary/Secondary Operation =            Secondary(1)\n");
			break;
		    default:
			fprintf(filePtr," Primary/Secondary Operation =            Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllConf.primary);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllConf.hitless)
		{
		    case 0:
			fprintf(filePtr," Hitless Mode Select =                    Disable(0)\n");
			break;
		    case 1:
			fprintf(filePtr," Hitless Mode Select =                    Enable(1)\n");
			break;
		    default:
			fprintf(filePtr," Hitless Mode Select =                    Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllConf.hitless);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllConf.fastlock)
		{
		    case 0:
			fprintf(filePtr," DPLL Fast Lock =                         Normal(0)\n");
			break;
		    case 1:
			fprintf(filePtr," DPLL Fast Lock =                         Lock(1)\n");
			break;
		    default:
			fprintf(filePtr," DPLL Fast Lock =                         Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllConf.fastlock);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllConf.dpllMon)
		{
		    case 0:
			fprintf(filePtr," DPLL Monitor =                           Enable(0)\n");
			break;
		    case 1:
			fprintf(filePtr," DPLL Monitor =                           Disble(1)\n");
			break;
		    default:
			fprintf(filePtr," Monitor =                                Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllConf.dpllMon);
			break;
		}

		fprintf(filePtr, "\nDPLL Statistics: \n");
		switch(eicCpldAllTestResult->eicDpllRegs.dpllStat.ref0Fail)
		{
		    case 0:
			fprintf(filePtr," Ref0 Clk Status =                        Good(0)\n");
			break;
		    case 1:
			fprintf(filePtr," Ref0 Clk Status =                        Failed(1)\n");
			break;
		    default:
			fprintf(filePtr," Ref0 Clk Status =                        Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllStat.ref0Fail);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllStat.ref1Fail)
		{
		    case 0:
			fprintf(filePtr," Ref1 Clk Status =                        Good(0)\n");
			break;
		    case 1:
			fprintf(filePtr," Ref1 Clk Status =                        Failed(1)\n");
			break;
		    default:
			fprintf(filePtr," Ref1 Clk Status =                        Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllStat.ref1Fail);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllStat.ref2Fail)
		{
		    case 0:
			fprintf(filePtr," Ref2 Clk Status =                        Good(0)\n");
			break;
		    case 1:
			fprintf(filePtr," Ref2 Clk Status =                        Failed(1)\n");
			break;
		    default:
			fprintf(filePtr," Ref2 Clk Status =                        Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllStat.ref2Fail);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllStat.locked)
		{
		    case 0:
			fprintf(filePtr," PLL Freq Locked/Unlocked =               Unlocked(0)\n");
			break;
		    case 1:
			fprintf(filePtr," PLL Freq Locked/Unlocked =               Locked(1)\n");
			break;
		    default:
			fprintf(filePtr," PLL Freq Locked/Unlocked =               Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllStat.locked);
			break;
		}

		switch(eicCpldAllTestResult->eicDpllRegs.dpllStat.holdover)
		{
		    case 0:
			fprintf(filePtr," Holdover Mode =                          Disable(0)\n");
			break;
		    case 1:
			fprintf(filePtr," Holdover Mode =                          Enable(1)\n");
			break;
		    default:
			fprintf(filePtr," Holdover Mode =                          Invalid(%d)\n",eicCpldAllTestResult->eicDpllRegs.dpllStat.holdover);
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
            case TEST_ID_EIC_CPLD_1:
	      {
		  sEicCpldStats *eicCpldStats;
		  eicCpldStats = (sEicCpldStats*)(((sDiagnosticResult*)BpmRespPtr)->data);

		  switch(eicCpldStats->selfCardState)
		  {
		      case BPM_EIC_ENABLE:
			  fprintf(filePtr," Self Card State :                    Enable(1)\n");
			  break;

		      case BPM_EIC_DISABLE:
			  fprintf(filePtr," Self Card State :                    Disable(0)\n");
			  break;

		      default:
			  fprintf(filePtr," Self Card State :                    Invalid(%d)\n",eicCpldStats->selfCardState);
			  break;
		  }

		  switch(eicCpldStats->peerCardState)
		  {
		      case BPM_EIC_ENABLE:
			  fprintf(filePtr," Peer Card State :                    Enable(1)\n");
			  break;

		      case BPM_EIC_DISABLE:
			  fprintf(filePtr," Peer Card State :                    Disable(0)\n");
			  break;

		      default:
			  fprintf(filePtr," Peer Card State :                    Invalid(%d)\n",eicCpldStats->peerCardState);
			  break;
		  }

		  switch(eicCpldStats->tdmLinkSelection)
		  {
		      case 0:
			  fprintf(filePtr," TDM Link Selection C0/C1 =           C0(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," TDM Link Selection C0/C1 =           C1(1)\n");
			  break;
		      default:
			  fprintf(filePtr," TDM Link Selection C0/C1 =           Invalid(%d)\n",eicCpldStats->tdmLinkSelection);
			  break;
		  }

		  switch(eicCpldStats->clkStatus)
		  {
		    case REFERENCE_MATE_CLK:
		      fprintf(filePtr," Selected TDM CLK Internal/External = Mate EIC Card(73)\n");
		      break;
		    case REFERENCE_INTERNAL_CLK:
		      fprintf(filePtr," Selected TDM CLK Internal/External = Internal(74)\n");
		      break;
		    case REFERENCE_EXTERNAL_CLK:
		      fprintf(filePtr," Selected TDM CLK Internal/External = External(75)\n");
		      break;
		    default:
		      fprintf(filePtr," Selected TDM CLK Internal/External = Invalid(%d)\n",eicCpldStats->clkStatus);
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
            case TEST_ID_EIC_CPLD_2:
	      {
		  sEicCpldReg *eicCpldReg;
		  eicCpldReg = (sEicCpldReg*)(((sDiagnosticResult*)BpmRespPtr)->data);

		  fprintf(filePtr,"\n CPLD Verson :                          %d.%d.%d\n",
			  ((eicCpldReg->mjver & 0xF0) >> 4),
			  (eicCpldReg->mjver & 0x0F),
			  (eicCpldReg->mnver & 0x0F));
		  fprintf(filePtr," Card Identification:                   0x%02x\n",eicCpldReg->cir);

		  fprintf(filePtr,"\nSelf Status Register:\n");

		  if(eicCpldReg->ssr & 0x80)
		  {
		      fprintf(filePtr," Clock Status =                         Clock0 Normal(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Clock Status =                         Clock0 Failure(0)\n");
		  }

		  if(eicCpldReg->ssr & 0x40)
		  {
		      fprintf(filePtr," Clock Status =                         Clock1 Normal(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Clock Status =                         Clock1 Failure(0)\n");
		  }

		  fprintf(filePtr,"\nWatch Dog Timer/DPLL Status Register: \n");

		  if(eicCpldReg->wdr & 0x80)
		  {
		      fprintf(filePtr," Watch Dog Timer Enable =               Enable(1)\n");
		      if(eicCpldReg->wdr & 0x20)
		      {
			  fprintf(filePtr," Watch Dog Timer Processor Status =     Running(1),Processor is Good\n");
		      }
		      else
		      {
			  fprintf(filePtr," Watch Dog Timer Processor Status =     Timeout(0),Processor is Failed\n");
		      }
		  }
		  else
		  {
		      fprintf(filePtr," Watch Dog Timer Enable =               Disable(0)\n");
		  }

		  fprintf(filePtr,"\nClock Buffer Control Register: \n");
		  if(eicCpldReg->cbcr & 0x01)
		  {
		      fprintf(filePtr," TDM Clk to Card0 =                     Enabled(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," TDM Clk to Card0 =                     Disabled(0)\n");
		  }

		  if(eicCpldReg->cbcr & 0x02)
		  {
		      fprintf(filePtr," TDM Clk to Card1 =                     Enabled(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," TDM Clk to Card1 =                     Disabled(0)\n");
		  }

		  if(eicCpldReg->cbcr & 0x04)
		  {
		      fprintf(filePtr," TDM Clk to Card2 =                     Enabled(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," TDM Clk to Card2 =                     Disabled(0)\n");
		  }

		  if(eicCpldReg->cbcr & 0x08)
		  {
		      fprintf(filePtr," TDM Clk to Card3 =                     Enabled(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," TDM Clk to Card3 =                     Disabled(0)\n");
		  }

		  if(eicCpldReg->cbcr & 0x10)
		  {
		      fprintf(filePtr," TDM Clk to Card4 =                     Enabled(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," TDM Clk to Card4 =                     Disabled(0)\n");
		  }

		  if(eicCpldReg->cbcr & 0x20)
		  {
		      fprintf(filePtr," TDM Clk to Card5 =                     Enabled(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," TDM Clk to Card5 =                     Disabled(0)\n");
		  }

		  fprintf(filePtr,"\nFrame Control Register: \n");
		  if(eicCpldReg->fcr & 0x08)
		  {
		      fprintf(filePtr," Transmit Enable for the Framer's LIU = Enabled(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Transmit Enable for the Framer's LIU = Disabled(0)\n");
		  }

		  if(eicCpldReg->fcr & 0x04)
		  {
		      fprintf(filePtr," Framer REF_CLK_SEL to Backplane =      Framer1(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Framer REF_CLK_SEL to Backplane =      Framer0(0)\n");
		  }

		  switch(eicCpldReg->fcr & 0x03)
		  {
		      case 0x00:
			  fprintf(filePtr," LIU_REF_CLK_SEL Mode =                 E1 Mode(00)\n");
			  break;
		      case 0x01:
			  fprintf(filePtr," LIU_REF_CLK_SEL Mode =                 T1 Mode(01)\n");
			  break;
		      default:
			  break;
		  }

		  fprintf(filePtr,"\nTDM Bus/Clk Select Register: \n");

		  if(eicCpldReg->tbcsr & 0x80)
		  {
		      fprintf(filePtr," TDM Link Selection C0/C1 =             C1(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," TDM Link Selection C0/C1 =             C0(0)\n");
		  }

		  if(eicCpldReg->tbcsr & 0x20)
		  {
		      fprintf(filePtr," RFN Sync/No Sync =                     Sync(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," RFN Sync/No Sync =                     No Sync(0)\n");
		  }

		  if(eicCpldReg->tbcsr & 0x02)
		  {
		      fprintf(filePtr," Selected TDM CLK/FS C0/C1 =            C1(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Selected TDM CLK/FS C0/C1 =            C0(0)\n");
		  }

		  fprintf(filePtr,"\nExtracted Clock select register: \n");
		  switch(eicCpldReg->ecsr & 0xF0)
		  {
		      case 0x00:
			  fprintf(filePtr," Ref1 Clk extracted from Framer0 (0000)\n");
			  break;
		      case 0x10:
			  fprintf(filePtr," Ref1 Clk extracted from Framer1 (0001)\n");
			  break;
		      case 0x20:
			  fprintf(filePtr," Ref1 Clk extracted from B0 (0010)\n");
			  break;
		      case 0x30:
			  fprintf(filePtr," Ref1 Clk extracted from B1 (0011)\n");
			  break;
		      case 0x40:
			  fprintf(filePtr," Ref1 Clk extracted from E0 (0100)\n");
			  break;
		      case 0x50:
			  fprintf(filePtr," Ref1 Clk extracted from E1 (0101)\n");
			  break;
		      case 0x60:
			  fprintf(filePtr," Ref1 Clk extracted from External (0110)\n");
			  break;
		      case 0x70:
			  fprintf(filePtr," Ref1 Clk extracted from EIC Framer (0111)\n");
			  break;
		      case 0x80:
			  fprintf(filePtr," Ref1 8KHz derived from 26MHz Clk (1000)\n");
			  break;
		      default:
			  fprintf(filePtr," Ref1 Disable\n");
			  break;
		  }
		  switch(eicCpldReg->ecsr & 0x0F)
		  {
		      case 0x00:
			  fprintf(filePtr," Ref0 Clk extracted from Framer0 (0000)\n");
			  break;
		      case 0x10:
			  fprintf(filePtr," Ref0 Clk extracted from Framer1 (0001)\n");
			  break;
		      case 0x20:
			  fprintf(filePtr," Ref0 Clk extracted from B0 (0010)\n");
			  break;
		      case 0x30:
			  fprintf(filePtr," Ref0 Clk extracted from B1 (0011)\n");
			  break;
		      case 0x40:
			  fprintf(filePtr," Ref0 Clk extracted from E0 (0100)\n");
			  break;
		      case 0x50:
			  fprintf(filePtr," Ref0 Clk extracted from E1 (0101)\n");
			  break;
		      case 0x60:
			  fprintf(filePtr," Ref0 Clk extracted from External (0110)\n");
			  break;
		      case 0x70:
			  fprintf(filePtr," Ref0 Clk extracted from EIC Framer (0111)\n");
			  break;
		      case 0x80:
			  fprintf(filePtr," Ref0 8KHz derived from 26MHz Clk (1000)\n");
			  break;
		      default:
			  fprintf(filePtr," Ref0 Disable\n");
			  break;
		  }

		  fprintf(filePtr,"\nTDM Link/Clock Selection Register: \n");
		  if(eicCpldReg->tlcsr & 0x80)
		  {
		      fprintf(filePtr," DPLL monitor Disable/Enable =          Disable(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," DPLL monitor Disable/Enable =          Enable(0)\n");
		  }

		  if(eicCpldReg->tlcsr & 0x40)
		  {
		      fprintf(filePtr," copy1 Clock monitor Disable/Enable =   Disable(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," copy1 Clock monitor Disable/Enable =   Enable(0)\n");
		  }

		  if(eicCpldReg->tlcsr & 0x20)
		  {
		      fprintf(filePtr," copy0 Clock monitor Disable/Enable =   Disable(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," copy0 Clock monitor Disable/Enable =   Enable(0)\n");
		  }

		  switch(eicCpldReg->tlcsr & 0x0C)
		  {
		      case 0x00:
			  fprintf(filePtr," TDM Link Selection Mode =          Copy0 (00)\n");
			  break;
		      case 0x01:
			  fprintf(filePtr," TDM Link Selection Mode =          Copy1 (01)\n");
			  break;
		      case 0x02:
			  fprintf(filePtr," TDM Link Selection Mode =          Auto-Mode (10)\n");
			  break;
		      case 0x03:
			  fprintf(filePtr," TDM Link Selection Mode =          Previous State (11)\n");
			  break;
		  }

		  switch(eicCpldReg->tlcsr & 0x03)
		  {
		      case 0x00:
			  fprintf(filePtr," TDM Clock Selection Mode =             Copy0 (00)\n");
			  break;
		      case 0x01:
			  fprintf(filePtr," TDM Clock Selection Mode =             Copy1 (01)\n");
			  break;
		      case 0x02:
			  fprintf(filePtr," TDM Clock Selection Mode =             Auto-Mode (10)\n");
			  break;
		      case 0x03:
			  fprintf(filePtr," TDM Clock Selection Mode =             Previous State (11)\n");
			  break;
		  }

		  fprintf(filePtr,"\nDPLL Reference input clock status Register:\n");
		  if(eicCpldReg->wdr & 0x04)
		  {
		      fprintf(filePtr," Ref clock from Mate card =             Present(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Ref clock from Mate card =             Absent(0)\n");
		  }

		  if(eicCpldReg->refclksts & 0x20)
		  {
		      fprintf(filePtr," Ref clock from ICC-E1 card =           Present(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Ref clock from ICC-E1 card =           Absent(0)\n");
		  }

		  if(eicCpldReg->refclksts & 0x10)
		  {
		      fprintf(filePtr," Ref clock from ICC-E0 card =           Present(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Ref clock from ICC-E0 card =           Absent(0)\n");
		  }

		  if(eicCpldReg->refclksts & 0x08)
		  {
		      fprintf(filePtr," Ref clock from ICC-B1 card =           Present(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Ref clock from ICC-B1 card =           Absent(0)\n");
		  }

		  if(eicCpldReg->refclksts & 0x04)
		  {
		      fprintf(filePtr," Ref clock from ICC-B0 card =           Present(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Ref clock from ICC-B0 card =           Absent(0)\n");
		  }

		  if(eicCpldReg->refclksts & 0x02)
		  {
		      fprintf(filePtr," Ref clock from onboard Framer1 =       Present(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Ref clock from onboard Framer1 =       Absent(0)\n");
		  }

		  if(eicCpldReg->refclksts & 0x01)
		  {
		      fprintf(filePtr," Ref clock from onboard Framer0 =       Present(1)\n");
		  }
		  else
		  {
		      fprintf(filePtr," Ref clock from onboard Framer0 =       Absent(0)\n");
		  }

		  fprintf(filePtr,"\nCPLD Reg Dump :- \n");
		  fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
			  eicCpldReg->mjver,
			  eicCpldReg->cir, eicCpldReg->dcr,
			  eicCpldReg->scr, eicCpldReg->ssr,
			  eicCpldReg->wdr, eicCpldReg->cbcr,
			  eicCpldReg->rccb3, eicCpldReg->rccb2,
			  eicCpldReg->rccb1, eicCpldReg->wlb1,
			  eicCpldReg->wlb2, eicCpldReg->fcr,
			  eicCpldReg->tbcsr, eicCpldReg->apr);
		  fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
			  eicCpldReg->spr, eicCpldReg->swpr,
			  eicCpldReg->lrpr1, eicCpldReg->daclsb,
			  eicCpldReg->dacmsb, eicCpldReg->ecsr,
			  eicCpldReg->mnver, eicCpldReg->isr,
			  eicCpldReg->wlb3, eicCpldReg->wlb4,
			  eicCpldReg->tlcsr, eicCpldReg->esr1,
			  eicCpldReg->esr2, eicCpldReg->esr3,
			  eicCpldReg->esr4);
		  fprintf(filePtr,"0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\n",
			  eicCpldReg->msr,
			  eicCpldReg->lrpr2, eicCpldReg->csid,
			  eicCpldReg->cpsnt, eicCpldReg->tlmen,
			  eicCpldReg->refclksts, eicCpldReg->dsp32bit,
			  eicCpldReg->e1los, eicCpldReg->tdmclkreg,
			  eicCpldReg->losstat);

		  fflush(filePtr);

		  if(libGlobalParam.fileAction == DIAG_FILE_CLOSE)
		  {
		      if(libGlobalParam.errCode != 0) 
		      {
			  fprintf(filePtr, "\nResolution :                     Replace the Card\n");
			  fflush(filePtr);
		      }
		      else
		      {
			  fprintf(filePtr, "\nResolution :                     None\n");
			  fflush(filePtr);
		      }
		  }  
	      }
              break; 
            case TEST_ID_EIC_CPLD_3:
	      {
		  sEicDpllRegs *eicDpllRegs;
		  eicDpllRegs= (sEicDpllRegs*)(((sDiagnosticResult*)BpmRespPtr)->data);

		  fprintf(filePtr, "\nDPLL Status Register: \n");
		  fprintf(filePtr, "DPLL Configuration: \n");

		  switch(eicDpllRegs->dpllConf.mode)
		  {
		      case 0:
			  fprintf(filePtr," DPLL Mode Select =                 Normal Mode(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," DPLL Mode Select =                 Holdover Mode(1)\n");
			  break;
		      case 2:
			  fprintf(filePtr," DPLL Mode Select =                 Free run Mode(2)\n");
			  break;
		      case 3:
			  fprintf(filePtr," DPLL Mode Select =                 Automatic Mode(3)\n");
			  break;
		      default:
			  fprintf(filePtr," DPLL Mode Select =                 Invalid(%d)\n",eicDpllRegs->dpllConf.mode);
			  break;
		  }

		  switch(eicDpllRegs->dpllConf.refsel)
		  {
		      case 0:
			  fprintf(filePtr," DPLL Reference Clock Select =      REF0(00)\n");
			  break;
		      case 1:
			  fprintf(filePtr," DPLL Reference Clock Select =      REF1(01)\n");
			  break;
		      case 2:
		      case 3:
			  fprintf(filePtr," DPLL Reference Clock Select =      REF2(1x)\n");
			  break;
		      default:
			  fprintf(filePtr," DPLL Reference Clock Select =      Invalid(%d)\n",eicDpllRegs->dpllConf.refsel);
			  break;
		  }

		  switch(eicDpllRegs->dpllConf.tie)
		  {
		      case 0:
			  fprintf(filePtr," TIE Reset =                        Reset(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," TIE Reset =                        No Action(1)\n");
			  break;
		      default:
			  fprintf(filePtr," TIE Reset =                        Invalid(%d)\n",eicDpllRegs->dpllConf.tie);
			  break;
		  }

		  switch(eicDpllRegs->dpllConf.primary)
		  {
		      case 0:
			  fprintf(filePtr," Primary/Secondary Operation =      Primary(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," Primary/Secondary Operation =      Secondary(1)\n");
			  break;
		      default:
			  fprintf(filePtr," Primary/Secondary Operation =      Invalid(%d)\n",eicDpllRegs->dpllConf.primary);
			  break;
		  }

		  switch(eicDpllRegs->dpllConf.hitless)
		  {
		      case 0:
			  fprintf(filePtr," Hitless Mode Select =              Disable(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," Hitless Mode Select =              Enable(1)\n");
			  break;
		      default:
			  fprintf(filePtr," Hitless Mode Select =              Invalid(%d)\n",eicDpllRegs->dpllConf.hitless);
			  break;
		  }

		  switch(eicDpllRegs->dpllConf.fastlock)
		  {
		      case 0:
			  fprintf(filePtr," DPLL Fast Lock =                   Normal(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," DPLL Fast Lock =                   Lock(1)\n");
			  break;
		      default:
			  fprintf(filePtr," DPLL Fast Lock =                   Invalid(%d)\n",eicDpllRegs->dpllConf.fastlock);
			  break;
		  }

		  switch(eicDpllRegs->dpllConf.dpllMon)
		  {
		      case 0:
			  fprintf(filePtr," DPLL Monitor =                     Enable(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," DPLL Monitor =                     Disble(1)\n");
			  break;
		      default:
			  fprintf(filePtr," Monitor =                          Invalid(%d)\n",eicDpllRegs->dpllConf.dpllMon);
			  break;
		  }

		  fprintf(filePtr, "\nDPLL Statistics: \n");
		  switch(eicDpllRegs->dpllStat.ref0Fail)
		  {
		      case 0:
			  fprintf(filePtr," Ref0 Clk Status =                  Good(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," Ref0 Clk Status =                  Failed(1)\n");
			  break;
		      default:
			  fprintf(filePtr," Ref0 Clk Status =                  Invalid(%d)\n",eicDpllRegs->dpllStat.ref0Fail);
			  break;
		  }

		  switch(eicDpllRegs->dpllStat.ref1Fail)
		  {
		      case 0:
			  fprintf(filePtr," Ref1 Clk Status =                  Good(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," Ref1 Clk Status =                  Failed(1)\n");
			  break;
		      default:
			  fprintf(filePtr," Ref1 Clk Status =                  Invalid(%d)\n",eicDpllRegs->dpllStat.ref1Fail);
			  break;
		  }

		  switch(eicDpllRegs->dpllStat.ref2Fail)
		  {
		      case 0:
			  fprintf(filePtr," Ref2 Clk Status =                  Good(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," Ref2 Clk Status =                  Failed(1)\n");
			  break;
		      default:
			  fprintf(filePtr," Ref2 Clk Status =                  Invalid(%d)\n",eicDpllRegs->dpllStat.ref2Fail);
			  break;
		  }

		  switch(eicDpllRegs->dpllStat.locked)
		  {
		      case 0:
			  fprintf(filePtr," PLL Freq Locked/Unlocked =         Unlocked(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," PLL Freq Locked/Unlocked =         Locked(1)\n");
			  break;
		      default:
			  fprintf(filePtr," PLL Freq Locked/Unlocked =         Invalid(%d)\n",eicDpllRegs->dpllStat.locked);
			  break;
		  }

		  switch(eicDpllRegs->dpllStat.holdover)
		  {
		      case 0:
			  fprintf(filePtr," Holdover Mode =                    Disable(0)\n");
			  break;
		      case 1:
			  fprintf(filePtr," Holdover Mode =                    Enable(1)\n");
			  break;
		      default:
			  fprintf(filePtr," Holdover Mode =                    Invalid(%d)\n",eicDpllRegs->dpllStat.holdover);
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
              LOG_PRINT(CRITICAL,"DiagLib: TESTID '%d' not defined for EIC CPLD ", 
                  ((sDiagnosticResult*)BpmRespPtr)->testID);
              break;
          }    
        }
	break;

      default:
        LOG_PRINT(CRITICAL,"DiagLib: TEST TYPE '%d' not defined for EIC", 
            ((sDiagnosticResult*)BpmRespPtr)->testType);
        break;
    }
  }
}
