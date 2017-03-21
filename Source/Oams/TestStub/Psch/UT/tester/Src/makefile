#Export path of BSC-DEVELOPMENT and CHECK

include ../../../../../../Csapp/Util/make.opt

CHECK = ../../../../../../..

INCLUDES =  -I$(CHECK)/Tools/check-0.9.6/src/

INC = -I../Inc/

INC_IPC = -I../../../../../../../Inc/Ipc

INC_OAMS = -I../../../../../Inc/

INC_TOP = -I../../../../../../../Inc/

USER_FLAG = -D__UT_TEST

CFLAGS := -g $(CFLAGS) $(INCLUDES) $(INC) $(INC_OAMS) $(INC_TOP) $(INC_IPC) $(USER_FLAG)

LFLAGS += -L$(CHECK)/Tools/check-0.9.6/src/.libs

LIBS += -lcheck

.PHONY: all clean install tsmstub_nack check

EXEC= UT \
     
all: $(EXEC)

UT: ut.o adap.o autotestCase.o
	$(CC) -o utenv $(LFLAGS) ut.o adap.o autotestCase.o \
	$(LIBS) 
	@echo "Compilation and build done for Tester "
	
adap.o: adap.c
	$(CC) -c $(CFLAGS) adap.c
	
ut.o: ut.c 
	$(CC) -c $(CFLAGS) ut.c

autotestCase.c: autotestCase.o
	$(CC) -c $(CFLAGS) autotestCase.c

clean:  
	rm -rf *.o core*.*
	rm -rf utenv
	rm -rf *.log
	rm -rf test_result.xml      

check:
	splint $(INC) $(INCLUDES) -nof -preproc -imptype -showscan -showsummary -warnposix -warnflags -weak +ignoresigns -varuse +matchanyintegral\
	ut.c adap.c autotestCase.c>splint.log 2>&1
	@echo "Splint output file generated: splint.log"
