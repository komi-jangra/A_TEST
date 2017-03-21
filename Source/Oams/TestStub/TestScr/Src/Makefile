include  ../../../../Csapp/Util/make.opt
HDR = -I$(BSC_BASE)/Source/Oams/Src/Cfg/Inc/ -I$(BSC_BASE)/Source/Oams/Inc/ \
      -I$(BSC_BASE)/Source/Oams/Src/Swverparser/Inc/ \
      -I$(BSC_BASE)/Source/Oams/Src/Mutex/Inc/ -I$(BSC_BASE)/Source/Oam/Inc/\
      -I$(BSC_BASE)/Inc/Sks/SCM/ \
      -I$(BSC_BASE)/Source/Csapp/Src/CbshCodec_asn/Inc/\
      -I$(BSC_BASE)/Source/Oams/Src/DiagLib/Inc/
TARGET = CellStatusUtility
BIN_NAME= CellStatusUtility
GCOV= -fprofile-arcs -ftest-coverage
########################################################################
## Define local c/cpp file(s)
########################################################################
COBJECTS = \
newScr.o

#######################################################################
## Define possible compiler flags
#######################################################################
#CC1 := $(CC) -g -DEIC_6670 -D__C_APPL -DCFG_UT $(GCOV) $(INC) $(HDR) $(COMPILEROPT)
CC1 := $(CC) -g -DEIC_6670 -D__C_APPL $(INC) $(HDR) $(COMPILEROPT)
#######################################################################
## Define make targets
#######################################################################
RM = rm
RM1 = rm -rf
.PHONY: all
all : compile install
compile: $(COBJECTS)
	$(CC1) $(LFLAGS)  -o $(TARGET) $(COBJECTS) $(LIBS) -lpthread 
%.o: %.c
	$(CC1) -c $< -o $@
install:
	cp -f $(TARGET) $(REL_BIN)/Exec/CP/$(BIN_NAME)-${VERSION}
clean: 
	rm -f $(TARGET) $(REL_BIN)/Exec/CP/$(BIN_NAME)-${VERSION} *.o *.gcno *.gcda *.bb *.bbg
               
