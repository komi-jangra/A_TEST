###############################################################################
USER_ROOT=/export/home/users/****
ITS_ROOT=$USER_ROOT/cvsroot/IntelliSS7
VENDOR_ROOT=$USER_ROOT/cvsroot/vendors
###############################################################################

export DLL_LIBS=$ITS_ROOT/common/lib:$ITS_ROOT/MTP3/lib:$VENDOR_ROOT/IntelliNet/lib

export LD_LIBRARY_PATH=/usr/local/lib:/usr/local/reloc/lib:/usr/lib:$LD_LIBRARY_PATH:$DLL_LIBS:$USER_ROOT/cvsroot/TestTools/TcapTest_PR6.ANSI.IMAL/src

#<exe> -appName <xml file> <route style>
$VENDOR_ROOT/IntelliNet/bin/run_TCAP -appName Server.ASP opc-dpc-sio

exit 0
