export ARCH=ARM
export PORT=ARM
export CPU=ARM
cd ss7osigtran
export ccm_project_path=$PWD
cd build
make ARCH=ARM NATIVELINUX=yes PERL=perl clean
make ARCH=ARM NATIVELINUX=yes PERL=perl all 2>err_arm
cd $ccm_project_path/src
make ARCH=ARM NATIVELINUX=yes PERL=perl clean
make ARCH=ARM NATIVELINUX=yes PERL=perl all 2>err_arm
cp -v $ccm_project_path/src/SS7_OVER_SIGTRAN ../../../../Bin/Target/Exec/SS7_OVER_SIGTRAN-${BASE}.${MAJOR}.${MINOR}
 
