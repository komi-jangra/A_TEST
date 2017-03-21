#!/bin/ksh
############################################################################
#                                                                          #
#     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    #
#             Manufactured in the United States of America.                #
#       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       #
#                                                                          #
#   This product and related documentation is protected by copyright and   #
#   distributed under licenses restricting its use, copying, distribution  #
#   and decompilation.  No part of this product or related documentation   #
#   may be reproduced in any form by any means without prior written       #
#   authorization of IntelliNet Technologies and its licensors, if any.    #
#                                                                          #
#   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      #
#   government is subject to restrictions as set forth in subparagraph     #
#   (c)(1)(ii) of the Rights in Technical Data and Computer Software       #
#   clause at DFARS 252.227-7013 and FAR 52.227-19.                        #
#                                                                          #
############################################################################
#                                                                          #
# CONTRACT: INTERNAL                                                       #
#                                                                          #
############################################################################


prog="${0##*/}"
if (( $# != 2 )); then
   echo "USAGE:./$prog logName1 logName2"
   echo "USAGE: where logName1 is the cvs login to be replaced in the Root file"
   echo "USAGE: where logName2 is the new cvs login"
   echo "eg: ./$prog jchui sjohn"
   exit 1
fi

outputOfFind=$HOME/outputOfFind
logNameToReplace=$1
newLogName=$2
curDir=$(pwd)
rootDir=$curDir/.
directoryToSearch=CVS
fileToSearch=Root
grep="/usr/xpg4/bin/grep"
tmpFile=${fileToSearch}.new
#  Start search

find $rootDir -name $directoryToSearch -print > $outputOfFind

cat $outputOfFind | while read line
do
    echo $line
    cd $line
    pwd
    eval $grep  -q ${logNameToReplace}.*wall.internal.net:/export/home/.32901cvsroot $fileToSearch
    rc=$?
    if (( rc != 0 )); then
       echo "$logNameToReplace not found"
    else
       cp $fileToSearch ${fileToSearch}.orig
       echo "replacing $logNameToReplace with $newLogName"
       eval sed -e 's/${logNameToReplace}/${newLogName}/g' $fileToSearch > ${tmpFile}
       mv $tmpFile $fileToSearch
    fi
    cd $curDir
done
find . -name buildFlagFile exec \rm {} 2> /dev/null ';'
find . -name out1 exec \rm {} 2> /dev/null ';'
\rm $outputOfFind
