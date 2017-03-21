include  ../../../../Csapp/Util/make.opt
HDR = -I$(BSC_BASE)/Source/Oams/Src/Cfg/Inc/ -I$(BSC_BASE)/Source/Oams/Inc/ \
      -I$(BSC_BASE)/Source/Oams/Src/Swverparser/Inc/ \
      -I$(BSC_BASE)/Source/Oams/Src/Mutex/Inc/ -I$(BSC_BASE)/Source/Oam/Inc/\
      -I$(BSC_BASE)/Inc/Sks/SCM/ \
      -I$(BSC_BASE)/Source/Csapp/Src/CbshCodec_asn/Inc/\
      -I$(BSC_BASE)/Source/Oams/Src/DiagLib/Inc/
TARGET = OAMS_CFG
BIN_NAME= OAMS_CFG
GCOV= -fprofile-arcs -ftest-coverage
########################################################################
## Define local c/cpp file(s)
########################################################################
COBJECTS = \
oamscfg_main.o\
oamscfg_initialization.o\
oamscfg_msg_handlers.o\
oamscfg_bss_object_handler.o\
oamscfg_trx_object_handler.o\
oamscfg_e1_object_handler.o\
oamscfg_e1timeslot_object_handler.o\
oamscfg_signal_handler.o\
oamscfg_responses.o\
oamscfg_cell_object_handler.o\
oamscfg_alarm_handler.o\
oamscfg_range_check.o\
oamscfg_del_msg_handler.o\
oamscfg_set_msg_handler.o \
oamscfg_timer.o \
oamscfg_cell_object_consistancy_check.o \
oamscfg_consistency_check.o \
oamscfg_bic_object_handler.o \
oamscfg_bic_trx_ts_handler.o \
oamscfg_sw_upgrade_handler.o \
oamscfg_clk_object_handler.o \
oamscfg_eic_sw_upgrade_handler.o \
oamscfg_stack_object_handler.o \
oamscfg_mlppp_object_handler.o \
oamscfg_ccu_handler.o \
oamscfg_sig_handler.o \
oamscfg_dsp_object_handler.o \
oamscfg_dsp_sw_upgrade_handler.o \
oamscfg_nsvc_object_handler.o \
oamscfg_perf_counter_init.o \
oamscfg_mccfr_resource_handler.o \
oamscfg_cbs_handler.o\
oamscfg_diagnostics_handler.o\
oamscfg_diagnostics_validation.o \
oamscfg_tsgroup_object_handler.o \
oamscfg_externalport_handler.o\
oamscfg_cluster_handler.o\
oamscfg_ha_handler.o

#######################################################################
## Define possible compiler flags
#######################################################################
#CC1 := $(CC) -g -DEIC_6670 -D__C_APPL -DCFG_UT $(GCOV) $(INC) $(HDR) $(COMPILEROPT)
CC1 := $(CC) -g -DEIC_6670 -D__C_APPL $(GCOV) $(INC) $(HDR) $(COMPILEROPT)
#######################################################################
## Define make targets
#######################################################################
RM = rm
RM1 = rm -rf
.PHONY: all
all : compile install
compile: $(COBJECTS)
	$(CC1) $(LFLAGS)  -lmutex -lSwVerParser -linst-DB -lCbshCodecAsn -ldiagLibapi -o $(TARGET) $(COBJECTS) $(LIBS) 
%.o: %.c
	$(CC1) -c $< -o $@
install:
	cp -f $(TARGET) $(REL_BIN)/Exec/CP/$(BIN_NAME)-${VERSION}
clean: 
	rm -f $(TARGET) $(REL_BIN)/Exec/CP/$(BIN_NAME)-${VERSION} *.o *.gcno *.gcda *.bb *.bbg
               
