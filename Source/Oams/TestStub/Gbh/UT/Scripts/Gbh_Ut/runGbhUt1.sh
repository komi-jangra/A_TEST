
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
# Function to Start GBH Without DB Data
startGbh1() {
   # Starting GBH Module
   startExe "$EXE_PATH/$GBH_BIN_NAME"

   # Starting BPM Stub to send state transitions INSERVICE, ACTIVEINPROGRESS, ACTIVE
   startExe $C_PATH/runBpmStub.sh

   # Kill Bpm Stub
   sleep 1
   source $C_PATH/killProcess.sh $BPM_STUB_BIN_NAME
}
################################################################################

################################################################################
# Function to Start GBH With DB Data
startGbh2() {
   # Adding Data In DB
   #source $C_PATH/addInstCount.sh
   source $C_PATH/addGbInterfaceTable.sh

   # Starting GBH Module
   startExe "$EXE_PATH/$GBH_BIN_NAME"

   # Starting BPM Stub to send state transitions INSERVICE, ACTIVEINPROGRESS, ACTIVE
   startExe $C_PATH/runBpmStub.sh
}
################################################################################

################################################################################
execute_test_case_1()
{
   source $C_PATH/updateGbIfStatusTable.sh 1 1
$TESTSTUBS_PATH/$UTENV_STUB_BIN_NAME1 << %%
1
1
0
0
%%
}

######################### Test Env #############################################
  	startGbh2
#	execute_test_case_1 

   source $C_PATH/updateGbIfStatusTable.sh 1 1
   source $C_PATH/runUtEnvTC.sh 1 1
   source $C_PATH/takeLogs.sh TC_1
   source $C_PATH/updateGbIfStatusTable.sh 1 0
   source $C_PATH/runUtEnvTC.sh 1 2
   source $C_PATH/takeLogs.sh TC_2
   source $C_PATH/updateGbIfStatusTable.sh 1 0
   source $C_PATH/runUtEnvTC.sh 1 3
   source $C_PATH/takeLogs.sh TC_3
   source $C_PATH/updateGbIfStatusTable.sh 1 1
   source $C_PATH/runUtEnvTC.sh 1 4
   source $C_PATH/takeLogs.sh TC_4
   source $C_PATH/updateGbIfStatusTable.sh 1 1
   source $C_PATH/runUtEnvTC.sh 1 5
   source $C_PATH/takeLogs.sh TC_5
   source $C_PATH/updateGbIfStatusTable.sh 1 0
   source $C_PATH/runUtEnvTC.sh 1 6
   source $C_PATH/takeLogs.sh TC_6
   source $C_PATH/updateGbIfStatusTable.sh 1 1
   source $C_PATH/runUtEnvTC.sh 1 7
   source $C_PATH/takeLogs.sh TC_7
   source $C_PATH/updateGbIfStatusTable.sh 1 0
   source $C_PATH/runUtEnvTC.sh 1 8
   source $C_PATH/takeLogs.sh TC_8
   source $C_PATH/updateGbIfStatusTable.sh 1 0
   source $C_PATH/runUtEnvTC.sh 1 9
   source $C_PATH/takeLogs.sh TC_9
   source $C_PATH/updateGbIfStatusTable.sh 1 1
   source $C_PATH/runUtEnvTC.sh 1 10
   source $C_PATH/takeLogs.sh TC_10
   source $C_PATH/updateGbIfStatusTable.sh 1 1
   source $C_PATH/runUtEnvTC.sh 1 11
   source $C_PATH/takeLogs.sh TC_11
   source $C_PATH/updateGbIfStatusTable.sh 1 0
   source $C_PATH/runUtEnvTC.sh 1 12
   source $C_PATH/takeLogs.sh TC_12
   source $C_PATH/clearLogs.sh
   source $C_PATH/runUtEnvTC.sh 2 1
   source $C_PATH/takeLogs.sh TC_13
   source $C_PATH/clearLogs.sh
   source $C_PATH/updateGbIfStatusTable.sh 0 0
   source $C_PATH/runUtEnvTC.sh 3 1
   source $C_PATH/takeLogs.sh TC_14
   source $C_PATH/runUtEnvTC.sh 4 1
   source $C_PATH/takeLogs.sh TC_20
   source $C_PATH/updateGbIfStatusTable.sh 1 1
   source $C_PATH/runUtEnvTC.sh 3 4
   source $C_PATH/takeLogs.sh TC_15
   source $C_PATH/runUtEnvTC.sh 4 2
   source $C_PATH/takeLogs.sh TC_21
   source $C_PATH/updateGbIfStatusTable.sh 0 0
   source $C_PATH/runUtEnvTC.sh 4 3
   source $C_PATH/takeLogs.sh TC_22
   source $C_PATH/deleteGbIfStatusTable.sh
   source $C_PATH/deleteGbInterfaceTable.sh
   source $C_PATH/runUtEnvTC.sh 4 4
   source $C_PATH/takeLogs.sh TC_23
   source $C_PATH/updateGbIfStatusTable.sh 0 0
   source $C_PATH/runUtEnvTC.sh 4 5
   source $C_PATH/takeLogs.sh TC_24 
   source $C_PATH/deleteGbIfStatusTable.sh
   source $C_PATH/runUtEnvTC.sh 3 6
   source $C_PATH/takeLogs.sh TC_17
   source $C_PATH/runUtEnvTC.sh 3 7
   source $C_PATH/takeLogs.sh TC_18

   
################################################################################
