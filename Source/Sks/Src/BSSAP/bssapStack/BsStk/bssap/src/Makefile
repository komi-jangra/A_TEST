#*******************************************************************************
##      FILE NAME:
##          Makefile
##
##      DESCRIPTION:
##              This file Compiles the Source Code of Bssap Stack.
##
##
##      DATE            NAME                          REFERENCE        REASON
##      ----            ----                          ---------        ------
##      21th Feb 2014   Amaresh Prasad Grahacharya
##
##      Copyright 2005, Vihaan Network Ltd.
##
##*****************************************************************************

include $(ccm_project_path)/lib/macros.mk 


SHELL = /bin/sh
CPPFLAGS += $(LIS_INC)
ifeq ($(ARCH), linux)
	CC=gcc -g -D__C_APPL
endif

ifeq ($(ARCH), ARM)
	CC=$(VNL_COM_PREFIX)gcc -g -D__C_APPL
endif

SIGTRAN_LB_PATH=-L${EXE_ROOT}/Target/CommonLib\
		  -L$(SYSEXE_ROOT)/Target/CommonLib/CP
SIGTRAN_LOG   = -llog -lfrm -lpthread -lplatformLib
#SIGTRAN_LOG   =  -llog -lpthread

CPPFLAGS +=-I $(ccm_project_path)/port/cspl/h \
	 -I $(ccm_project_path)/ss7stack/bssap/h \
   -DSCCP_CONNECTION_ID_CHANGES \
   -DLCLS_PARAM_DECODE \
   -DSCCP_ITU \
   -DCOMPARE_ITU \
  -DSIGTRAN_SCCP_IF \
  -DSCCP_TRACE_ENABLED \
  -DSCCP_INCLUDE_CO_SERVICE \
  -I$(BPM_INC)/../Sks/SCM \
  -I$(BPM_INC)/../Oam \
  -I../../../../../../Inc \
  -I$(BPM_INC) \
  -I$(BPM_INC)/../Sys \
  -I$(BPM_INC)/../Ipc -DBSSAP_HA -DPLATFORM_IMR -DAPP_MULTITHREADS -DSCM_CHG 


#		 ${EXE_ROOT}/Target/CommonLib/liblog.so
#for SIGtran and porting 
LDFLAGS:= $(LDFLAGS) $(ccm_project_path)/build/cspl/$(ARCH)/libcspl.a \
	   	     $(ccm_project_path)/build/cspl/$(ARCH)/libcpset.a \
		     $(ccm_project_path)/build/cspl/$(ARCH)/libmpset.a \
		     $(ccm_project_path)/build/cspl/$(ARCH)/libporting.a \
     		     $(ccm_project_path)/build/ss7stack/common/$(ARCH)/libscommon.a \
 
LDFLAGS := $(LDFLAGS) 
local_obj = bs_main.o bs_sys.o bs_apphdl.o bs_map.o bs_bdy5.o bs_bdy7.o bs_clc.o bs_mptop.o bs_msg.o bs_sccphdl.o bssap_task.o bssap_port.o cm_hash.o bs_hashFunc.o

exe = BSSAP


ifeq ($(dep), )
	LDFLAGS := $(LDFLAGS) -Wl,-Bdynamic 
else
	LDFLAGS := $(LDFLAGS) -Wl,-Bdynamic 
endif


#
# dependencies and rules
#
#ifndef LINUXCOMMON
#LIBC=/usr/lib/i386-redhat-linux7/lib/libc.a
#endif 

obj = $(local_obj) $(module_obj)

all: $(exe)


#$(gsn_logger_exe):
#	$(CC) -o $@ -g $(ccm_project_path)/src/$(gsn_logger_src)

$(exe): $(obj) $(dep)
	$(CC) -o $@ $(obj) $(LIBC) $(SIGTRAN_LB_PATH) $(SIGTRAN_LOG) $(LDFLAGS)
default: $(exe)

clean:
	$(RM)  *.o $(exe) 
