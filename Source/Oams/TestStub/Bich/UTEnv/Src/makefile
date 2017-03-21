include  ../../../../../Csapp/Util/make.opt
HDR      = -I$(BSC_BASE)/Source/Oams/Inc/ \
           -I$(BSC_BASE)/Source/Oams/Src/Bich/Inc/ \
           -I$(BSC_BASE)/Source/Oams/TestStub/Bich/UTEnv/Inc/

TARGET   = UTE_CONTLR
BIN_NAME = UTE_CONTLR
########################################################################
## Define local c/cpp file(s)
########################################################################
COBJECTS = \
main_ut_controller.o\
addBich.o\
msgHdrEncDec.o\
testsuit.o 
#######################################################################
## Define possible compiler flags
#######################################################################
#CC1 := $(CC) -save-temps -D__C_APPL $(INC) $(HDR) $(COMPILEROPT)
CC1 := $(CC) -D__C_APPL $(INC) $(HDR) $(COMPILEROPT)
#######################################################################
## Define make targets
#######################################################################
.PHONY: all
all : clean compile install
gen: 
	./Script2GenMsgHelper
compile: $(COBJECTS)
	$(CC1) $(LFLAGS) $(LIBS) -o $(TARGET) $(COBJECTS)
%.o: %.c
	$(CC1) -c $< -o $@
install:
#	cp -f $(TARGET) /home/bikram/ut/targetBin/repos/r.4.0.0/telecom/OAMS_CFG
clean: 
	rm -f $(TARGET) *.o *.i *.s *~
               
