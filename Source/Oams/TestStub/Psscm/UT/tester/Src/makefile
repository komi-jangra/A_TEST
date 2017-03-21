#Export path of BSC-DEVELOPMENT and CHECK

include ../../../../../../Csapp/Util/make.opt

CHECK = ../../../../../../..

INCLUDES =  -I$(CHECK)/Tools/check-0.9.6/src/

INC = -I../Inc/

INC_IPC = -I../../../../../../../Inc/Ipc

INC_OAMS = -I../../../../Inc/

INC_TOP = -I../../../../../../../Inc/

USER_FLAG = -D__UT_TEST

CFLAGS := -g $(CFLAGS) $(INCLUDES) $(INC) $(INC_OAMS) $(INC_TOP) $(INC_IPC) $(USER_FLAG)

LFLAGS += -L$(CHECK)/Tools/check-0.9.6/src/.libs

LIBS += -lcheck

.PHONY: all clean install tsmstub_nack check

EXEC= UT \
     
all: $(EXEC)

UT: ut.o adap.o testCase1.o testCase2.o testCase3.o testCase4.o testCase5.o
	$(CC) -o utenv1 $(LFLAGS) ut.o adap.o testCase1.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv1"
	$(CC) -o utenv2 $(LFLAGS) ut.o adap.o testCase2.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv2 "
	$(CC) -o utenv3 $(LFLAGS) ut.o adap.o testCase3.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv3 "
	$(CC) -o utenv4 $(LFLAGS) ut.o adap.o testCase4.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv4 "
	$(CC) -o utenv5 $(LFLAGS) ut.o adap.o testCase5.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv5 "
	
adap.o: adap.c
	$(CC) -c $(CFLAGS) adap.c
	
ut.o: ut.c 
	$(CC) -c $(CFLAGS) ut.c

testCase1.o: testCase1.c
	$(CC) -c $(CFLAGS) testCase1.c

testCase2.o: testCase2.c
	$(CC) -c $(CFLAGS) testCase2.c

testCase3.o: testCase3.c
	$(CC) -c $(CFLAGS) testCase3.c

testCase4.o: testCase4.c
	$(CC) -c $(CFLAGS) testCase4.c

testCase5.o: testCase5.c
	$(CC) -c $(CFLAGS) testCase5.c

clean:  
	rm -rf *.o core*.*
	rm -rf utenv*
	rm -rf *.log
	rm -rf test_result.xml      

check:
	splint $(INC) $(INCLUDES) -nof -preproc -imptype -showscan -showsummary -warnposix -warnflags -weak +ignoresigns -varuse +matchanyintegral\
	ut.c adap.c testCase1.c testCase2.c testCase3.c testCase4.c testCase5.c>splint.log 2>&1
	@echo "Splint output file generated: splint.log"
