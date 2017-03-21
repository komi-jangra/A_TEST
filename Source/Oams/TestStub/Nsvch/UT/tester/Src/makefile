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

UT: ut.o adap.o testCase_till_unlockedEnabled.o testCase_block_lockDown.o testCase_statusInactive_in_IndDown.o testCase_indDown_unprov_states.o testCase_unlockedBlocked_db.o testCase_wrongDlci_conn_disc.o
	$(CC) -o utenv_till_unlockedEnabled $(LFLAGS) ut.o adap.o testCase_till_unlockedEnabled.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv_till_unlockedEnabled "
	
	$(CC) -o utenv_block_lockDown $(LFLAGS) ut.o adap.o testCase_block_lockDown.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv_block_lockDown "

	$(CC) -o utenv_statusInactive_in_IndDown $(LFLAGS) ut.o adap.o testCase_statusInactive_in_IndDown.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv_statusInactive_in_IndDown "

	$(CC) -o utenv_indDown_unprov_states $(LFLAGS) ut.o adap.o testCase_indDown_unprov_states.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv_indDown_unprov_states "

	$(CC) -o utenv_unlockedBlocked_db $(LFLAGS) ut.o adap.o testCase_unlockedBlocked_db.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv_unlockedBlocked_db "

	$(CC) -o utenv_wrongDlci_conn_disc $(LFLAGS) ut.o adap.o testCase_wrongDlci_conn_disc.o \
	$(LIBS) 
	@echo "Compilation and build done for utenv_wrongDlci_conn_disc "




	
adap.o: adap.c
	$(CC) -c $(CFLAGS) adap.c
	
ut.o: ut.c 
	$(CC) -c $(CFLAGS) ut.c

testCase_till_unlockedEnabled.o: testCase_till_unlockedEnabled.c
	$(CC) -c $(CFLAGS) testCase_till_unlockedEnabled.c

testCase_block_lockDown.o: testCase_block_lockDown.c
	$(CC) -c $(CFLAGS) testCase_block_lockDown.c

testCase_statusInactive_in_IndDown.o: testCase_statusInactive_in_IndDown.c
	$(CC) -c $(CFLAGS) testCase_statusInactive_in_IndDown.c

testCase_indDown_unprov_states.o: testCase_indDown_unprov_states.c
	$(CC) -c $(CFLAGS) testCase_indDown_unprov_states.c

testCase_unlockedBlocked_db.o: testCase_unlockedBlocked_db.c
	$(CC) -c $(CFLAGS) testCase_unlockedBlocked_db.c

testCase_wrongDlci_conn_disc.o: testCase_wrongDlci_conn_disc.c
	$(CC) -c $(CFLAGS) testCase_wrongDlci_conn_disc.c

clean:  
	rm -rf *.o core*.*
	rm -rf utenv_till_unlockedEnabled utenv_block_lockDown utenv_statusInactive_in_IndDown utenv_indDown_unprov_states utenv_unlockedBlocked_db utenv_wrongDlci_conn_disc
	rm -rf *.log

check:
	splint $(INC) $(INCLUDES) -nof -preproc -imptype -showscan -showsummary -warnposix -warnflags -weak +ignoresigns -varuse +matchanyintegral\
	ut.c adap.c testCase_till_unlockedEnabled.c testCase_block_lockDown.c testCase_statusInactive_in_IndDown.c testCase_indDown_unprov_states.c testCase_unlockedBlocked_db.c testCase_wrongDlci_conn_disc.c>splint.log 2>&1
	@echo "Splint output file generated: splint.log"
