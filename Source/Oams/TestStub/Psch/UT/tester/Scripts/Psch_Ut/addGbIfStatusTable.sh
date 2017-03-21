
# Add Data in GbIfStatus Table
Table_Num=141
gbIfIndex=1
oprState=1
cblNegotiated=1
$EXE_PATH/DB_TOOL << %% > /dev/null
$Table_Num
4
n
$gbIfIndex
$oprState
$cblNegotiated
n
999
%%
