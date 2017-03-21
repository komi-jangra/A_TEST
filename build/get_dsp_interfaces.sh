#!/bin/bash

#########################
if [ $# -ne 1 ]; then
	echo "Usage: $0 <DSP-Version>"
	echo ""
	echo "Example: $0 <DSP-BSC-4.1.0.001>"
	exit 1;
fi
DSP_VER=$1

rm -rf DSP_INTERFACES
# new structure as per PFS release
export DSPROOT=http://10.100.211.65/system/dsp/dsp-support/ra/DSP-ReleaseArea/current/DSP-BSC/${DSP_VER}/${DSP_VER}
svn export $DSPROOT/Inc DSP_INTERFACES/
DEST=..

echo "Copying Interfaces"
platforms="M4 "
for hw_platform in $platforms;
do
	echo "hw $hw_platform"
	cp -pf DSP_INTERFACES/*.h $DEST/Bin/Target/Pfs4.0
done
echo "Done"
