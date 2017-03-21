
# Add Data in GbInterface Table
Table_Num=22
gbIfIndex=1
nsei=1
maxNumNsvcsOverFr=1
maxNumNsvcsOverIp=1
maxNumLeps=1
maxNumReps=1
transportType=1
tFcC=200
tFcTh=200
tFcSup=200000
nMaxFcRep=3
$EXE_PATH/DB_TOOL << %% > /dev/null
$Table_Num
4
n
$gbIfIndex
$nsei
$maxNumNsvcsOverFr
$maxNumNsvcsOverIp
$maxNumLeps
$maxNumReps
$transportType
$tFcC
$tFcTh
$tFcSup
$nMaxFcRep
n
999
%%
