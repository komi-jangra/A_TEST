
# Add Data in PsAllocPreconfig Table
Table_Num=148
psAllocPreconfigIndex=1
ulOctetCntThreshold=1
dlQueueThreshold=1
dlCountdownValue=1
dlSpreadStepsize=1
ulSpreadStepsize=1
maxPdchAct=1
maxUlAlloc=1
maxDlAlloc=1
avgMsPdchDl=1
avgMsPdchUl=1
longMsWeight=1
$EXE_PATH/DB_TOOL << %% > /dev/null
$Table_Num
4
n
$psAllocPreconfigIndex
$ulOctetCntThreshold
$dlQueueThreshold
$dlCountdownValue
$dlSpreadStepsize
$ulSpreadStepsize
$maxPdchAct
$maxUlAlloc
$maxDlAlloc
$avgMsPdchDl
$avgMsPdchUl
$longMsWeight
n
999
%%
