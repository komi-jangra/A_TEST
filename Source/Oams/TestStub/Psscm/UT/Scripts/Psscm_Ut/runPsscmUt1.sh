
########################## EXPORT VARIABLES ####################################
################################################################################
# Export Variables
export T_WAIT=1
export j=40;
export k=40;
export BGCOLOR=LAVENDER
################################################################################

############################ FUNCTIONS #########################################
################################################################################
# Function to Start Binary
startExe() {
  exe=$1;
  j=$(($j + 20));
  k=$(($k + 20));
  xterm -geometry 80x05+$k+$j -fg black -bg $BGCOLOR -e "$exe" &
  pid=$!
  sleep $T_WAIT;
  ps --no-heading -p $pid || echo "$exe: CRASHED"
}
################################################################################

################################################################################
# Function to Start PSSCM Without DB Data
startPsscm1() {
   # Starting PSSCM Module
   startExe "$EXE_PATH/$PSSCM_BIN_NAME"

   # Starting BPM Stub to send state transitions INSERVICE, ACTIVEINPROGRESS, ACTIVE
   startExe $C_PATH/runBpmStub.sh

   # Kill Bpm Stub
   sleep 1
   source $C_PATH/killProcess.sh $BPM_STUB_BIN_NAME
}
################################################################################

################################################################################
# Function to Start PSSCM With DB Data
startPsscm2() {
   # Adding Data In DB
   source $C_PATH/addInstCount.sh
   source $C_PATH/addGbInterfaceTable.sh

   # Starting PSSCM Module
   startExe "$EXE_PATH/$PSSCM_BIN_NAME"

   # Starting BPM Stub to send state transitions INSERVICE, ACTIVEINPROGRESS, ACTIVE
   startExe $C_PATH/runBpmStub.sh
}
################################################################################

################################################################################
PsscmIdle_to_WaitForProvNseiCnf()
{
$TESTSTUBS_PATH/$UTENV_STUB_BIN_NAME1 << %%
1
1
0
0
%%
}

WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf()
{
$TESTSTUBS_PATH/$UTENV_STUB_BIN_NAME2 << %%
1
4
0
0
%%
}



######################### Test Env #############################################
  	startPsscm2
	
   source $C_PATH/deleteGbInterfaceTable.sh
   source $C_PATH/runUtEnvTC.sh 1 2
   source $C_PATH/takeLogs.sh 2
   source $C_PATH/clearLogs.sh
   source $C_PATH/addGbInterfaceTable.sh
   source $C_PATH/runUtEnvTC.sh 1 1
   source $C_PATH/takeLogs.sh 1
   source $C_PATH/runUtEnvTC.sh 2 6
   source $C_PATH/takeLogs.sh 29
   source $C_PATH/clearLogs.sh
	PsscmIdle_to_WaitForProvNseiCnf 
   source $C_PATH/runUtEnvTC.sh 2 3
   source $C_PATH/takeLogs.sh 26
   source $C_PATH/runUtEnvTC.sh 2 5
   source $C_PATH/takeLogs.sh 28
   source $C_PATH/runUtEnvTC.sh 4 61
   source $C_PATH/takeLogs.sh 87
   source $C_PATH/clearLogs.sh

################################################################################
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/takeLogs.sh 27
   source $C_PATH/runUtEnvTC.sh 3 10
   source $C_PATH/takeLogs.sh 33
   source $C_PATH/runUtEnvTC.sh 4 62
   source $C_PATH/takeLogs.sh 88
   source $C_PATH/clearLogs.sh
################################################################################


################################################################################

       PsscmIdle_to_WaitForProvNseiCnf
   source $C_PATH/runUtEnvTC.sh 2 3
   source $C_PATH/runUtEnvTC.sh 2 7
   source $C_PATH/takeLogs.sh 30
   source $C_PATH/clearLogs.sh

################################################################################

################################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/takeLogs.sh 31
   source $C_PATH/runUtEnvTC.sh 3 18
   source $C_PATH/takeLogs.sh 42
   source $C_PATH/runUtEnvTC.sh 4 59 
   source $C_PATH/takeLogs.sh 85 
   source $C_PATH/runUtEnvTC.sh 4 62
   source $C_PATH/clearLogs.sh

#################################################################################

################################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 11
   source $C_PATH/takeLogs.sh 34
   source $C_PATH/runUtEnvTC.sh 3 9
   source $C_PATH/takeLogs.sh 32
   source $C_PATH/runUtEnvTC.sh 4 59 
   source $C_PATH/runUtEnvTC.sh 4 61
   source $C_PATH/clearLogs.sh

###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 12
   source $C_PATH/takeLogs.sh 35 
   source $C_PATH/runUtEnvTC.sh 3 17
   source $C_PATH/takeLogs.sh 40  
   source $C_PATH/takeLogs.sh 41  
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/takeLogs.sh 83   
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh


###############################################################################

###############################################################################


   source $C_PATH/addLepInfoTable.sh
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/takeLogs.sh 36   
   source $C_PATH/runUtEnvTC.sh 3 24
   source $C_PATH/takeLogs.sh 48   
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 62 
   source $C_PATH/clearLogs.sh


###############################################################################

###############################################################################


   source $C_PATH/deleteLepInfoTable.sh
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 14
   source $C_PATH/takeLogs.sh 37   
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


   source $C_PATH/updateTransportType.sh 2
   source $C_PATH/addLepInfoTable.sh
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 15
   source $C_PATH/takeLogs.sh 38   
   source $C_PATH/runUtEnvTC.sh 3 24
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 62 
   source $C_PATH/clearLogs.sh


###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/deleteLepInfoTable.sh
   source $C_PATH/runUtEnvTC.sh 3 16
   source $C_PATH/takeLogs.sh 39   

###############################################################################

###############################################################################


   source $C_PATH/updateTransportType.sh 3
       PsscmIdle_to_WaitForProvNseiCnf
      WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 19
   source $C_PATH/takeLogs.sh 43  
   source $C_PATH/runUtEnvTC.sh 4 65
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


   source $C_PATH/updateTransportType.sh 1
   source $C_PATH/addLepInfoTable.sh
   source $C_PATH/addRepInfoTable.sh
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/takeLogs.sh 44   
   source $C_PATH/runUtEnvTC.sh 3 31
   source $C_PATH/takeLogs.sh 55   
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/takeLogs.sh 77   
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 62 
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


   source $C_PATH/updateTransportType.sh 1
   source $C_PATH/deleteRepInfoTable.sh
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 21
   source $C_PATH/takeLogs.sh 45   
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


   source $C_PATH/addRepInfoTable.sh
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 25
   source $C_PATH/takeLogs.sh 49   
   source $C_PATH/runUtEnvTC.sh 3 22
   source $C_PATH/takeLogs.sh 46   
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 26
   source $C_PATH/takeLogs.sh 50   
   source $C_PATH/runUtEnvTC.sh 3 29
   source $C_PATH/takeLogs.sh 53   
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/takeLogs.sh 79   
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh




###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 27
   source $C_PATH/takeLogs.sh 51   
   source $C_PATH/runUtEnvTC.sh 4 44
   source $C_PATH/takeLogs.sh 68   
   source $C_PATH/runUtEnvTC.sh 4 63
   source $C_PATH/takeLogs.sh 3   
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


   source $C_PATH/updateTransportType.sh 2
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 28
   source $C_PATH/takeLogs.sh 52   
   source $C_PATH/runUtEnvTC.sh 4 34
   source $C_PATH/takeLogs.sh 58   
   source $C_PATH/runUtEnvTC.sh 4 64
   source $C_PATH/takeLogs.sh 4   
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 26
   source $C_PATH/deleteRepInfoTable.sh
   source $C_PATH/runUtEnvTC.sh 3 30
   source $C_PATH/takeLogs.sh 54  
   source $C_PATH/clearLogs.sh

 
###############################################################################

###############################################################################


   source $C_PATH/addRepInfoTable.sh
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 28
   source $C_PATH/runUtEnvTC.sh 4 42
   source $C_PATH/takeLogs.sh 66   
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 28
   source $C_PATH/runUtEnvTC.sh 4 37
   source $C_PATH/takeLogs.sh 61   
   source $C_PATH/runUtEnvTC.sh 4 42
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61
   source $C_PATH/clearLogs.sh





###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 28
   source $C_PATH/runUtEnvTC.sh 4 37
   source $C_PATH/runUtEnvTC.sh 4 41
   source $C_PATH/takeLogs.sh 65   
   source $C_PATH/runUtEnvTC.sh 4 40
   source $C_PATH/takeLogs.sh 64   
   source $C_PATH/runUtEnvTC.sh 4 34
   source $C_PATH/runUtEnvTC.sh 4 64
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61
   source $C_PATH/clearLogs.sh


###############################################################################

###############################################################################


   source $C_PATH/updateTransportType.sh 1
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 27
   source $C_PATH/runUtEnvTC.sh 4 43
   source $C_PATH/takeLogs.sh 67   
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 27
   source $C_PATH/runUtEnvTC.sh 4 49
   source $C_PATH/takeLogs.sh 73   
   source $C_PATH/runUtEnvTC.sh 4 43
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61
   source $C_PATH/clearLogs.sh


###############################################################################

###############################################################################


   source $C_PATH/addRepInfoTable.sh
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 27
   source $C_PATH/runUtEnvTC.sh 4 49
   source $C_PATH/runUtEnvTC.sh 4 51
   source $C_PATH/takeLogs.sh 75   
   source $C_PATH/runUtEnvTC.sh 4 50
   source $C_PATH/takeLogs.sh 74   
   source $C_PATH/runUtEnvTC.sh 4 44
   source $C_PATH/runUtEnvTC.sh 4 63
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh


###############################################################################

###############################################################################


   source $C_PATH/updateTransportType.sh 2
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 28
   source $C_PATH/runUtEnvTC.sh 4 34
   source $C_PATH/runUtEnvTC.sh 4 64
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 86
   source $C_PATH/takeLogs.sh 76   
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20
   source $C_PATH/runUtEnvTC.sh 3 28
   source $C_PATH/runUtEnvTC.sh 4 34
   source $C_PATH/runUtEnvTC.sh 4 64
   source $C_PATH/runUtEnvTC.sh 4 52
   source $C_PATH/takeLogs.sh 78   
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 24
   source $C_PATH/runUtEnvTC.sh 4 56
   source $C_PATH/takeLogs.sh 82   
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh




###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 18
   source $C_PATH/runUtEnvTC.sh 4 58
   source $C_PATH/takeLogs.sh 84   
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 10
   source $C_PATH/runUtEnvTC.sh 4 60
   source $C_PATH/takeLogs.sh 86   
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/runUtEnvTC.sh 2 3 
   source $C_PATH/takeLogs.sh 89   
   source $C_PATH/clearLogs.sh



###############################################################################

###############################################################################


   source $C_PATH/updateTransportType.sh 3
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 19
   source $C_PATH/runUtEnvTC.sh 4 65 
   source $C_PATH/takeLogs.sh 5   
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh


###############################################################################

###############################################################################


   source $C_PATH/updateTransportType.sh 1
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20 
   source $C_PATH/runUtEnvTC.sh 3 27
   source $C_PATH/runUtEnvTC.sh 4 44
   source $C_PATH/deleteRepInfoTable.sh
   source $C_PATH/runUtEnvTC.sh 4 66 
   source $C_PATH/takeLogs.sh 6   
   



   source $C_PATH/addRepInfoTable.sh
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20 
   source $C_PATH/runUtEnvTC.sh 3 27
   source $C_PATH/runUtEnvTC.sh 4 44
   source $C_PATH/runUtEnvTC.sh 4 70 
   source $C_PATH/takeLogs.sh 10   
   source $C_PATH/runUtEnvTC.sh 4 68
   source $C_PATH/takeLogs.sh 8   
   source $C_PATH/runUtEnvTC.sh 4 44 
   source $C_PATH/runUtEnvTC.sh 4 63
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh


###############################################################################

###############################################################################


   source $C_PATH/addRepInfoTable.sh
   source $C_PATH/updateTransportType.sh 2
       PsscmIdle_to_WaitForProvNseiCnf
       WaitForProvNseiCnf_to_WaitForNsProvSigBvcCnf
   source $C_PATH/runUtEnvTC.sh 3 8
   source $C_PATH/runUtEnvTC.sh 3 13
   source $C_PATH/runUtEnvTC.sh 3 20 
   source $C_PATH/runUtEnvTC.sh 3 28
   source $C_PATH/runUtEnvTC.sh 4 34
   source $C_PATH/clearLogs.sh


   source $C_PATH/addBvciRaiMappingTable.sh
   source $C_PATH/runUtEnvTC.sh 4 72 
   source $C_PATH/takeLogs.sh 12   
   source $C_PATH/runUtEnvTC.sh 4 73 
   source $C_PATH/takeLogs.sh 13   
   source $C_PATH/runUtEnvTC.sh 4 76 
   source $C_PATH/takeLogs.sh 16   
   source $C_PATH/runUtEnvTC.sh 4 71 
   source $C_PATH/takeLogs.sh 11   
   source $C_PATH/runUtEnvTC.sh 4 78 
   source $C_PATH/takeLogs.sh 18   
   source $C_PATH/runUtEnvTC.sh 4 79 
   source $C_PATH/takeLogs.sh 19   

   source $C_PATH/clearLogs.sh



   source $C_PATH/deleteBvciRaiMappingTable.sh
   source $C_PATH/runUtEnvTC.sh 4 72 
   source $C_PATH/runUtEnvTC.sh 4 74 
   source $C_PATH/takeLogs.sh 14   
   source $C_PATH/clearLogs.sh
   source $C_PATH/runUtEnvTC.sh 4 72 
   source $C_PATH/runUtEnvTC.sh 4 75 
   source $C_PATH/takeLogs.sh 15   
   source $C_PATH/clearLogs.sh
   source $C_PATH/runUtEnvTC.sh 4 77 
   source $C_PATH/takeLogs.sh 17   
   source $C_PATH/runUtEnvTC.sh 4 80 
   source $C_PATH/takeLogs.sh 20   
   source $C_PATH/clearLogs.sh
   source $C_PATH/runUtEnvTC.sh 5 85 
   source $C_PATH/takeLogs.sh 25   
   source $C_PATH/runUtEnvTC.sh 4 69 
   source $C_PATH/takeLogs.sh 9   
   source $C_PATH/runUtEnvTC.sh 4 67 
   source $C_PATH/takeLogs.sh 7   
   source $C_PATH/runUtEnvTC.sh 4 34 
   source $C_PATH/clearLogs.sh
   
   source $C_PATH/runUtEnvTC.sh 4 64
   source $C_PATH/runUtEnvTC.sh 4 52
   source $C_PATH/runUtEnvTC.sh 4 53
   source $C_PATH/runUtEnvTC.sh 5 87
   source $C_PATH/runUtEnvTC.sh 5 57
   source $C_PATH/runUtEnvTC.sh 5 59
   source $C_PATH/runUtEnvTC.sh 4 61 
   source $C_PATH/clearLogs.sh
###############################################################################

###############################################################################
