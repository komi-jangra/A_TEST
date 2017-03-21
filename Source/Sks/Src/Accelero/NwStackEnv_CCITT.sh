#
#umask 022
#
# General Path settings.
# DONT MESS WITH THE ORDER OF DIRECTORIES HERE!
#
#if [[ -n $PS1 ]]; then
#   stty erase
#fi
ENV=.kshrc
export ENV
#rel=Accelero-
#compiler=MTP2
#buildDir=${rel}${compiler}
buildDir=Accelero
export  buildDir
export CONFIG_VAR=$PWD/vendors
#HOME=$SKS_ROOT
#export HOME

#PATH=.:$HOME/bin
PATH=$PATH:/usr/local/bin
PATH=$PATH:/bin
PATH=$PATH:/usr/bin
PATH=$PATH:/usr/sbin
#PATH=$PATH:$HOME/bin
PATH=$PATH:$ITS_ROOT/common/bin
PATH=$PATH:/opt/nms/bin
PATH=$PATH:/sbin
PATH=$PATH:/opt/nmstx/bin:/opt/montavista/cge/devkit/ppc/85xx/bin

#
# Man path settings.
#
MANPATH=/usr/man
MANPATH=$MANPATH:/usr/share/man
MANPATH=$MANPATH:/usr/local/man
MANPATH=$MANPATH:/usr/openwin/man
MANPATH=$MANPATH:/usr/openwin/share/man

#
# LD_LIBRARY_PATH settings.
#
LD_LIBRARY_PATH=/usr/dt/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKS_ROOT/${buildDir}/IntelliSS7/common/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKS_ROOT/${buildDir}/IntelliSS7/BSSAP/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKS_ROOT/${buildDir}/IntelliSS7/BSSAP/proc/test/bssap
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKS_ROOT/${buildDir}/vendors/IntelliNet/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKS_ROOT/${buildDir}/vendors/nms/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKS_ROOT/${buildDir}/IntelliSS7/MTP3/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKS_ROOT/${buildDir}/IntelliSS7/SCCP/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKS_ROOT/${buildDir}/IntelliSS7/TCAP/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SKS_ROOT/${buildDir}/IntelliSS7/IS41/lib
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.


export PATH
export MANPATH
export LD_LIBRARY_PATH

#
# CVS Configuration
#
export CVSUMASK=002
export ITS_ROOT=$SKS_ROOT/${buildDir}/IntelliSS7
export ASNCPATH=$ITS_ROOT/common/include/asn-c
export VENDOR_ROOT=$SKS_ROOT/${buildDir}/vendors
export VENDOR=IntelliNet
#export PLATFORM=mvlppc

if [ $OS = "montavista" ]
then
export PLATFORM=mvlppc
else
export PLATFORM=$OS
fi

export PROTOCOL=CCITT
export STACK=INTELLINET
export SCCP_PROT=CCITT
export BUILD_TYPE=INTEGRATED
export DEBUG_BUILD=yes
export PATH

