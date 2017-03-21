
#########################################################################
##
## Build Makefile for cfgstub.exe
##
##########################################################################
ROOT_PATH = $(BSC_BASE)/MSC-Development
BSC_BASE =  ../../../../../..
#BSC_BASE = ~/PCU

#ifeq ($(OS),linux)
 COMPILER = gcc -g -m32
 LINKER = gcc -g -m32
 BIN_PATH = .
 #BIN_PATH = $(BSC_BASE)/Source/Oams/Bin/Host/Exec
 LIB_PATH =$(BSC_BASE)/Bin/Host/CommonLib
 SYS_LIB_PATH = $(BSC_BASE)/Bin/Host/CommonLib/CP 
 export LD_LIBRARY_PATH=$SYS_LIB_PATH:$LD_LIBRARY_PATH
 COMP_FLAG = -DDEBUG -D__C_APPL -DCFG_UNIT_TEST
#endif

ifeq ($(OS),montavista)
 COMPILER = ppc_82xx-gcc -g
 LINKER = ppc_82xx-gcc -g
 BIN_PATH = ../../../Bin/Target/Exec
 LIB_PATH = ../../../Bin/Target/CommonLib/CP
 SYS_LIB_PATH = $(BSC_BASE)/Bin/Target/CommonLib/CP 
 COMP_FLAG = -DDEBUG -D__C_APPL
 ifeq ($(FEATURE),bpm-enable)
  COMP_FLAG := $(COMP_FLAG) -DPLATFORM_IMR
  LIBRARIES = -lplatformLib
  HDRFILES = -I $(BSC_BASE)/Inc/BPM/
 endif
endif

TARGET = $(BIN_PATH)/stub_cfg.exe
LIBRARY_PATH = -L $(SYS_LIB_PATH) -L $(LIB_PATH)
LIBRARIES := $(LIBRARIES) -lCLIB -ldbwrappers -lfrm -ltau -lrt -llog

HDRFILES := $(HDRFILES) -I $(BSC_BASE)/Inc/Sys/ \
-I $(BSC_BASE)/Inc/Bpm/ \
-I $(BSC_BASE)/Inc/Dsp/ \
-I $(BSC_BASE)/Inc/Ipc/ \
-I $(BSC_BASE)/Inc/Dbs/ \
-I $(BSC_BASE)/Inc/Oams/ \
-I $(BSC_BASE)/Inc/Oam/ \
-I $(BSC_BASE)/Inc/Mgs/ \
-I $(BSC_BASE)/Inc/Csapp/ \
-I $(BSC_BASE)/Source/Oams/Inc/ \
-I $(BSC_BASE)/Source/Oams/Src/Cfg/Inc/ \
-I $(BSC_BASE)/Source/Oams/TestStub/Cfg/UTStubR2.5/Inc/ 
########################################################################
## Define local c/cpp file(s)
########################################################################
COBJECTS = \
cfg_stub_range_check.o\
cfg_stub_main.o\
cfg_stub_cell_object_handler.o\
cfg_stub_nsvc_object_handler.o\
cfg_stub_e1_object_handler.o\
#cfg_stub_bss_object_handler.o\
cfg_stub_alarm_handler.o\
cfg_stub_e1_object_handler.o\
cfg_stub_csstack_dbhndlr.o\
cfg_stub_dbhndlr.o\
cfg_stub_db_del_operations.o\
cfg_stub_trau_init_handler.o
#######################################################################
## Define possible compiler flags
#######################################################################
CFLAGS = $(COMP_FLAG) $(HDRFILES)

#CC = $(COMPILER)  -fsigned-char $(HDRFILES) $(COMP_FLAG)
CC = $(COMPILER) $(HDRFILES) $(COMP_FLAG)
#######################################################################
## Define make targets
#######################################################################
RM = rm
RM1 = rm -rf
.PHONY: all
all: $(COBJECTS)
	$(CC) $(LIBRARY_PATH) $(LIBRARIES) -o $(TARGET) $(COBJECTS)

.PHONY: clean
clean:
	$(RM1) $(COBJECTS) $(TARGET)

.PHONY: debug
debug: $(COBJECTS)
	$(COMPILER) -o $(TARGET) $(COBJECTS)

