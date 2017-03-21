#!/bin/bash -x

## Script to get latest BPM binaries for this MSC Build ##

REL_VER=""
bpm_bin_dir=BPM_BINARIES
dest_msc_dir=..

if [ $# -ne 3 ]; then
	echo "Usage: $0 <Hardware M1/M2/M4/M2C> <RELEASEVERSION> <BPM-Release> "
	echo ""
	echo "Example: $0 M1 2.0.7 BPM-BSC-2.0.9.008"
	echo "Example: $0 M4 5.1.1 BPM-BSC-2.0.9.008"
	exit 1;
fi

hw_given=$1
REL_VER=$2
bpm_release_area=$3

base_ver=`echo ${REL_VER} | cut -d'.' -f1`
major_ver=`echo ${REL_VER} | cut -d'.' -f2`
shared_ver="${base_ver}.${major_ver}"
#shared_ver="4.0"
echo ""
echo "Given ${hw_given} for Release: ${REL_VER}"
sleep 2

BPM_BINARY_REPO=http://10.100.211.65/shared/VNL-Shared/trunk/PFS4.0/BPM/BPM-Binaries/${bpm_release_area}
rm -rf ${bpm_bin_dir}

svn co ${BPM_BINARY_REPO}  ${bpm_bin_dir}

## Copy the BPM Binaries to the MSC-Development dir "
echo "Begin BPM Binaries copy from ${bpm_bin_dir} ${dest_msc_dir}"
for target_hw in ${hw_given}
do
echo "Target ${target_hw}"

echo "CommonLib - libplatformLib.so for CP & PP"
cp ${bpm_bin_dir}/${target_hw}/CommonLib/CP/libplatformLib.so ${dest_msc_dir}/Bin/Target/CommonLib/CP/${target_hw}/libplatformLib.so
cp ${bpm_bin_dir}/${target_hw}/CommonLib/CP/libplatformLib.so ${dest_msc_dir}/Bin/Target/CommonLib/CP/libplatformLib.so
cp ${bpm_bin_dir}/${target_hw}/CommonLib/PP/libplatformLib.so ${dest_msc_dir}/Bin/Target/CommonLib/PP/${target_hw}/libplatformLib.so
cp ${bpm_bin_dir}/${target_hw}/CommonLib/PP/libplatformLib.so ${dest_msc_dir}/Bin/Target/CommonLib/PP/libplatformLib.so

# CP
echo "CP & PP Binaries for Exec"
for bpm_bin_file in HA INIT MPI PI PM RMON UA toggleHAmonitor TS-PI
do
if [ ${bpm_bin_file} == "INIT" ]
then
cp ${bpm_bin_dir}/${target_hw}/Exec/CP/${bpm_bin_file}* ${dest_msc_dir}/Bin/Target/Exec/CP/${target_hw}/${bpm_bin_file}
else
cp ${bpm_bin_dir}/${target_hw}/Exec/CP/${bpm_bin_file}* ${dest_msc_dir}/Bin/Target/Exec/CP/${target_hw}/${bpm_bin_file}-${REL_VER}
fi
done


# PP
for bpm_bin_file in HA INIT MPI PI PM RMON UA toggleHAmonitor TS-PI 
do
if [ ${bpm_bin_file} == "INIT" ]
then
cp ${bpm_bin_dir}/${target_hw}/Exec/PP/${bpm_bin_file}* ${dest_msc_dir}/Bin/Target/Exec/PP/${target_hw}/${bpm_bin_file}
else
cp ${bpm_bin_dir}/${target_hw}/Exec/PP/${bpm_bin_file}* ${dest_msc_dir}/Bin/Target/Exec/PP/${target_hw}/${bpm_bin_file}-${REL_VER}
fi
done

done

cp ${bpm_bin_dir}/${target_hw}/Exec/PP/DRA ${dest_msc_dir}/Bin/Target/Exec/PP/${target_hw}/DRA
