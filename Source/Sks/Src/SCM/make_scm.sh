#Start to make SME 
VERSION_SCM=${BASE}.${MAJOR}.${MINOR}
OS=`uname -s`

if [ $# -ne 1 ]
then
echo ""
echo "Usage:    ./make_scm -[OS]"
echo "OS:       -linux or -montavista"
echo "Example:  ./make_scm -linux"
echo "          ./make_scm -montavista"
echo ""
fi

build_type=$1

# code addition begins
if [ "$build_type" = "montavista" ]
then
a=0
echo $a
echo "*************"
export a
make all
fi

if [ "$build_type" = "linux" ]
then
a=1
echo $a
echo "*************"
export a
make all
fi

if [ "$build_type" = "linux" ]
then
cp Bin/SCM-${VERSION_SCM}  ${EXE_ROOT}/Host/Exec
echo "Copied the executable to  bin  folder .... \n"
fi


if [ "$build_type" = "montavista" ]
then
cp Bin/SCM-${VERSION_SCM}  ${EXE_ROOT}/Target/Exec
echo "Copied the executable to  bin  folder .... \n"
fi

export build_type



# code addition ends
