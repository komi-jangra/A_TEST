#!/bin/bash

#########################
if [ $# -ne 3 ]; then
	echo "Usage: $0 <H/W Version> <RELEASEVERSION> <SA/INTG>"
	echo ""
	echo "Example: $0 M1 2.5.1 SA"
	echo "Example: $0 M2 2.0.7 INTG"
	echo "SA - Split Architecture"
	echo "INTG - Integration or Non-Split Architecture"
	exit 1
fi
HW_VER=$1
REL_VER=$2
ARCH=$3
# old structure
#DSPROOT=http://192.168.1.7/shared/VNL-Shared/trunk/DSP-Binaries/current/BSC
rm -rf DSP_BINARIES
# new structure as per PFS release
DSPROOT=http://10.100.211.65/shared/VNL-Shared/trunk/PFS3.0/DSP/DSP-Binaries
svn export --username arun.rg $DSPROOT DSP_BINARIES
DEST=../
dsp_arch=""

case "${ARCH}" in
	SA) dsp_arch="_sa";;
	INTG) dsp_arch="";;
	*) echo "Please Enter SA/INTG for Split or Non-Split/INTG Arch";
	   exit 1;; 
esac
DSP_OS_BIN=trau_8122${dsp_arch}.s
DSP_INIT_BIN=dspinit.bin

echo "Copying DSP OS, Init Binaries"
cp DSP_BINARIES/BSC/${DSP_OS_BIN} $DEST/Bin/Target/Exec/PP/DSP_OS-${REL_VER}
chmod 775  $DEST/Bin/Target/Exec/PP/DSP_OS-${REL_VER}
#cp DSP_BINARIES/COMMON/${HW_VER}/${DSP_INIT_BIN} $DEST/Bin/Target/Exec/PP/.
echo "Done"
