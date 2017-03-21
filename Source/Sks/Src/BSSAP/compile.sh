export ARCH=linux
export PORT=linux
export CPU=linux
cd bssapStack
export ccm_project_path=$PWD
cd build
make ARCH=linux NATIVELINUX=yes PERL=perl clean
make ARCH=linux NATIVELINUX=yes PERL=perl all 2>err_lnx
cd $ccm_project_path/BsStk/bssap/src
make ARCH=linux NATIVELINUX=yes PERL=perl clean
make ARCH=linux NATIVELINUX=yes PERL=perl all 2>err_lnx
cp -v $ccm_project_path/BsStk/bssap/src/BSSAP ../../../../../../Bin/Target/Exec/BSSAP-${BASE}.${MAJOR}.${MINOR} 
cp -v $ccm_project_path/BsStk/bssap/src/BSSAP $REL_PATH/Bin/Target/Exec/CP/BSSAP-${BASE}.${MAJOR}.${MINOR}

#cp -v $ccm_project_path/BsStk/bssap/src/BSSAP $REL_PATH/Development/Bin/Target/Exec/CP/BSSAP-${BASE}.${MAJOR}.${MINOR} 
