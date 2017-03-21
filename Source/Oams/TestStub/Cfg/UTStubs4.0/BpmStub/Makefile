include  ../../../../../Csapp/Util/make.opt
HDR = -I$(BSC_BASE)/Source/Oams/Src/Cfg/Inc/ -I$(BSC_BASE)/Source/Oams/Inc/ -I$(BSC_BASE)/Source/Oams/Src/Mutex/Inc\
			-I$(BSC_BASE)/Source/Oams/TestStub/Cfg/UTStubs4.0/Inc/ \
			-I$(BSC_BASE)/Source/Oams/Src/Swverparser/Inc \
			-I$(BSC_BASE)/Inc/Sks/SCM
TARGET = BPM_STUB
BIN_NAME= BPM_STUB
########################################################################
## Define local c/cpp file(s)
########################################################################
COBJECTS = \
bpmStub.o 

#######################################################################
## Define possible compiler flags
#######################################################################
CC1 := $(CC) -D__C_APPL $(INC) $(HDR) $(COMPILEROPT)
#######################################################################
## Define make targets
#######################################################################
RM = rm
RM1 = rm -rf
.PHONY: all
all : compile install
compile: $(COBJECTS)
	$(CC1) $(LFLAGS) $(LIBS) -o $(TARGET) $(COBJECTS)
%.o: %.c
	$(CC1) -c $< -o $@
install:
#	cp -f $(TARGET) $(REL_BIN)/Exec/CP/$(BIN_NAME)-${VERSION}
clean: 
	rm -f $(TARGET) *.o *~
               
