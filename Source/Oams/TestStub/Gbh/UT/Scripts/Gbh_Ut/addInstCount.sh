
#  Add GBH Instance

MAINOPTION=0
SETCNTOPTION=21
ENTITY=167       #GBH Entity Id
GBHCLSID=1     #GBH Class Id
INSTCNTGBH=5  #GBH Instance Count
INSTEXIT=27

$TESTSTUBS_PATH/INSTLIB_DB_STUB << %%
$MAINOPTION
$ENTITY
$GBHCLSID
$SETCNTOPTION
$INSTCNTGBH
$INSTEXIT
%%
