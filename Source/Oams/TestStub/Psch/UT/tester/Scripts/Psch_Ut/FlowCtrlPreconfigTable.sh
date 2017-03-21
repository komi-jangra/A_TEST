
# Add Data in PsFlowCtrPreConfig Table
Table_Num=150
psFlowCtrlPreconfigIndex=1
bMaxBvc=1
rBvc=1
bMaxMs=1
rMs=1
msBucketSizeLowerThreshold=1
msBucketSizeUpperThreshold=1
rMsReducedCs1=1
rMsReducedCs2=1
rMsReducedCs3=1
rMsReducedCs4=1
$EXE_PATH/DB_TOOL << %% > /dev/null
$Table_Num
4
n
$psFlowCtrlPreconfigIndex
$bMaxBvc
$rBvc
$bMaxMs
$rMs
$msBucketSizeLowerThreshold
$msBucketSizeUpperThreshold
$rMsReducedCs1
$rMsReducedCs2
$rMsReducedCs3
$rMsReducedCs4
n
999
%%
