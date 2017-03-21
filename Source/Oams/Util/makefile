# Makefile for Oams
include ../../Csapp/Util/make.opt

ifeq ($(LOCATION),VNL)
  DIRS := ../../Csapp/Src/CbshCodec ../../Csapp/Src/CbshCodec_asn ../TestStub/TestScr Mutex Semaphore Swverparser Trxh Cellh Cfg Bich SWMH Rm CCUH Psch Psscm Gbh Dsph
else
  DIRS := Trxh Cellh Cfg Bich Psch Psscm Gbh
endif

info:
	echo "rules: all clean install uninstall"

all clean install uninstall:
ifeq ($(BPM_ENABLE),0)
		make -C $(BSC_BASE)/Source/Oams/Src/BpmStub/Src $@ || exit $?
else
		make -C $(BSC_BASE)/Source/Oams/Src/DiagLib/Src/ $@ || exit $?
endif	
	for name in $(DIRS); do\
		make -C $(BSC_BASE)/Source/Oams/Src/$$name/Src $@ || exit $?; done
