
########################## EXPORT VARIABLES ####################################
################################################################################
# Export Variables
export T_WAIT=1
export j=40;
export k=40;
export BGCOLOR=LAVENDER
export PSCH_INST_COUNT=1
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
# Function to Start PSCH With DB Data
startPsch() {
   # Adding Data In DB
   source $C_PATH/addInstCount.sh
   source $C_PATH/addBssTable.sh 
   source $C_PATH/addCellPerTable.sh
   source $C_PATH/addPsCellTable.sh
   source $C_PATH/addPtrxTable.sh
   source $C_PATH/addGbInterfaceTable.sh
   source $C_PATH/addLtrxTable.sh 
   source $C_PATH/addAInterfaceTable.sh
   source $C_PATH/addPsCellStatusTable.sh
   source $C_PATH/addGbIfStatusTable.sh
   source $C_PATH/addPsAllocPreconfigTable.sh
   source $C_PATH/FlowCtrlPreconfigTable.sh

   # Starting PSCH Module
   startExe "$EXE_PATH/$PSCH_BIN_NAME"

}
################################################################################

################################################################################
startPsch
################################################################################
