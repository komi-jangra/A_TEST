export ARCH=linux
export PORT=linux
export CPU=linux
export NIB=CLIENT
cd ss7osigtran
export ccm_project_path=$PWD
cd build
make ARCH=linux NATIVELINUX=yes PERL=perl clean
make ARCH=linux NATIVELINUX=yes PERL=perl all 2>err_lnx
cd $ccm_project_path/src
make ARCH=linux NATIVELINUX=yes PERL=perl clean
make ARCH=linux NATIVELINUX=yes PERL=perl all 2>err_lnx
cp -v $ccm_project_path/src/SS7_OVER_SIGTRAN_CLIENT ../../../../Bin/Target/Exec/SS7_OVER_SIGTRAN_CLIENT-${BASE}.${MAJOR}.${MINOR}
cp -v $ccm_project_path/src/SS7_OVER_SIGTRAN_CLIENT $REL_PATH/Bin/Target/Exec/CP/SS7_OVER_SIGTRAN_CLIENT-${BASE}.${MAJOR}.${MINOR} 
