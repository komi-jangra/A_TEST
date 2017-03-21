
rm -rf $TESTSTUBS_PATH/PRC_LOG/DUMPER.txt
cp -rf $TESTSTUBS_PATH/DUMPER.txt $TESTSTUBS_PATH/PRC_LOG/ 

cd $C_PATH

DATE=`date +%F%H%M`
DATE1=`date +%F`

mkdir ./$DATE1

cd $TESTSTUBS_PATH
cp -R PRC_LOG LOG_GBH_UT_TC_$1_$2

tar -cvzf LOG_GBH_UT_TC_$1_$2.tgz LOG_GBH_UT_TC_$1_$2

rm -fr LOG_GBH_UT_TC_$1_$2

mv LOG_GBH_UT_TC_$1_$2.tgz $C_PATH/$DATE1/

cd $C_PATH

cat result.txt >> Verdict.txt
