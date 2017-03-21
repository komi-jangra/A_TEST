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

echo "Executing get_bpm_binaries.sh"
source get_bpm_binaries.sh $HW_VER $REL_VER
echo "Executing get_dsp_interfaces.sh"
source get_dsp_interfaces.sh
echo "Done"
