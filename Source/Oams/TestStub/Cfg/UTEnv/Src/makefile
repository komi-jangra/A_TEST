include  ../../../../../Csapp/Util/make.opt
HDR      = -I$(BSC_BASE)/Source/Oams/Inc/ \
           -I$(BSC_BASE)/Inc/Sks/SCM/ \
           -I$(BSC_BASE)/Source/Oams/Src/Cfg/Inc/ \
           -I$(BSC_BASE)/Source/Oams/Src/Swverparser/Inc \
           -I$(BSC_BASE)/Source/Oams/TestStub/Cfg/UTEnv/Inc/

TARGET   = UTE_CONTLR
BIN_NAME = UTE_CONTLR
########################################################################
## Define local c/cpp file(s)
########################################################################
COBJECTS = \
main_ut_controller.o\
testsuit.o \
ClkSrcTC1.o \
TpUsageTC.o \
TpAdmnStateTC.o \
StkSrcTC.o \
StkAddMTC.o \
CfgInit.o \
dbInit.o \
oil_stub.o \
grhm_stub.o \
bicLockUnlock.o
#######################################################################
## Define possible compiler flags
#######################################################################
#CC1 := $(CC) -save-temps -D__C_APPL $(INC) $(HDR) $(COMPILEROPT)
CC1 := $(CC) -D__C_APPL $(INC) $(HDR) $(COMPILEROPT)
#######################################################################
## Define make targets
#######################################################################
RM = rm
.PHONY: all
all : compile install
compile: $(COBJECTS)
	$(CC1) $(LFLAGS) $(LIBS) -o $(TARGET) $(COBJECTS)
%.o: %.c
	$(CC1) -c $< -o $@
install:
#	cp -f $(TARGET) /home/bikram/ut/targetBin/repos/r.4.0.0/telecom/OAMS_CFG
clean: 
	rm -f $(TARGET) *.o *.i *.s *~
               
