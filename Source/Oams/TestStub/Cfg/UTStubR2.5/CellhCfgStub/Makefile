include  ../../../../../Csapp/Util/make.opt
HDR = -I$(BSC_BASE)/Source/Oams/Src/Cfg/Inc/ -I$(BSC_BASE)/Source/Oams/Inc/ \
		  -I$(BSC_BASE)/Source/Oam/Inc	-I$(BSC_BASE)/Source/Oams/TestStub/Cfg/SwUpgrade/Inc/ \
                        -I$(BSC_BASE)/Inc/Sks/SCM/ \
			-I$(BSC_BASE)/Source/Oams/Src/Swverparser/Inc
TARGET = CELLH_STUB
BIN_NAME= CELLH_STUB
########################################################################
## Define local c/cpp file(s)
########################################################################
COBJECTS = \
cellh_cfg_stub.o 

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
               
