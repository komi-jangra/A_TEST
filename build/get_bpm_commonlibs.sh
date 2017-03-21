#!/bin/bash

############################

BPM_COMMON_LIB=http://10.100.211.65/shared/VNL-Shared/trunk/PFS3.0/CommonTargetLibs

rm -rf BPM_COMMON_LIB
svn export ${BPM_COMMON_LIB} BPM_COMMON_LIB

cp -rpf BPM_COMMON_LIB/M1 ../Bin/Target/.
cp -rpf BPM_COMMON_LIB/M2 ../Bin/Target/.
cp -rpf BPM_COMMON_LIB/M3 ../Bin/Target/.
cp -rpf BPM_COMMON_LIB/M2C ../Bin/Target/.

