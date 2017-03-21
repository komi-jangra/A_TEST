include $(ccm_project_path)/lib/macros.mk
include $(ccm_project_path)/sigtran/m3ua/build/$(ARCH)/makefile.m3ua

SHELL=/bin/sh

SIGTRAN_DIR=$(ccm_project_path)/sigtran
SCTP_BASE_DIR=$(ccm_project_path)/sigtran/sctp

CSPL_DIR=$(ccm_project_path)/port/cspl

ifeq ($(ARCH), linux)
		CPU=linux
		PORT=linux
endif

ifeq ($(ARCH), sparc)
	CPU=sparc
	PORT=solaris
endif

ifeq ($(ARCH), ARM)
export		CPU=ARM
export 		PORT=ARM
endif

subdir = m3ua sctp


M3UA_DIR      = $(SIGTRAN_DIR)/m3ua
LIB_DIR       = $(M3UA_DIR)/lib
OBJ_DIR       = $(M3UA_DIR)/obj/$(CPU)


LIBS          = $(LIB_DIR)/libdb.so \
                $(LIB_DIR)/libsu.so \
                $(LIB_DIR)/libsm.so \
                $(LIB_DIR)/libmain.so \
                $(LIB_DIR)/libinit.so \
                $(LIB_DIR)/libmh.so \
                $(LIB_DIR)/libtl.so \
                $(LIB_DIR)/libfs.so \
                $(LIB_DIR)/libstats.so \
                $(LIB_DIR)/liberr.so \
                $(LIB_DIR)/libcommon.so \
                $(LIB_DIR)/libdbg.so \
                $(LIB_DIR)/libos.so \
                $(LIB_DIR)/libred.so \
                $(LIB_DIR)/libgenlib.so

 
MODULES       = $(M3UA_DIR)/basic/shared \
		$(M3UA_DIR)/basic/stack/err  \
                $(M3UA_DIR)/basic/shared/dbg \
                $(M3UA_DIR)/basic/stack/fsm \
                $(M3UA_DIR)/basic/stack/init \
                $(M3UA_DIR)/basic/stack/main \
                $(M3UA_DIR)/basic/stack/mh \
                $(M3UA_DIR)/basic/stack/red \
                $(M3UA_DIR)/basic/stack/sm \
                $(M3UA_DIR)/basic/stack/stat \
                $(M3UA_DIR)/basic/stack/su \
                $(M3UA_DIR)/basic/stack/tli \
                $(M3UA_DIR)/basic/stack/db \
		$(M3UA_DIR)/../common/port/make/$(PORT)\
		$(M3UA_DIR)/../common/gw/make/$(PORT) 




#Modules that are to be ported by customer - err/dbg
CSTPRT_MODULES=	$(M3UA_DIR)/basic/stack/err/port \
                $(M3UA_DIR)/basic/shared/dbg/port

SHAREDCLIMODULES    = $(M3UA_DIR)/basic/shared \
		$(M3UA_DIR)/../common/port/make/$(PORT)

CLIMODULES    = $(M3UA_DIR)/basic/client \
                $(M3UA_DIR)/basic/client/su \
                $(M3UA_DIR)/basic/client/sm

MIBMODULE     = $(M3UA_DIR)/basic/mib

PORTMODULES   = $(M3UA_DIR)/port

CSTPRTOBJFILES= $(OBJ_DIR)/m3erport.o \
                $(OBJ_DIR)/m3dbgprt.o

OBJFILES      = $(OBJ_DIR)/m3dbconf.o \
                $(OBJ_DIR)/m3dbinit.o \
                $(OBJ_DIR)/m3dbnw.o \
                $(OBJ_DIR)/m3dbrt.o \
                $(OBJ_DIR)/m3dbred.o \
                $(OBJ_DIR)/m3dbrou.o \
                $(OBJ_DIR)/m3dbspmc.o \
                $(OBJ_DIR)/m3dbhash.o \
		$(OBJ_DIR)/m3dbrtip.o \
		$(OBJ_DIR)/m3dbroui.o \
		$(OBJ_DIR)/m3dbcfgi.o \
                $(OBJ_DIR)/m3dbuser.o \
                $(OBJ_DIR)/m3erp.o \
                $(OBJ_DIR)/m3fsinit.o \
                $(OBJ_DIR)/m3fsmapg.o \
                $(OBJ_DIR)/m3fsipsp.o \
                $(OBJ_DIR)/m3fsmapp.o \
                $(OBJ_DIR)/m3fsmasg.o \
                $(OBJ_DIR)/m3fsmisc.o \
                $(OBJ_DIR)/m3mhbld.o \
                $(OBJ_DIR)/m3mhpars.o \
                $(OBJ_DIR)/m3mhproc.o \
                $(OBJ_DIR)/m3mhinit.o \
                $(OBJ_DIR)/m3red.o \
                $(OBJ_DIR)/m3smapi.o \
                $(OBJ_DIR)/m3sminit.o \
                $(OBJ_DIR)/m3smind.o \
                $(OBJ_DIR)/m3smindq.o \
                $(OBJ_DIR)/m3smmisc.o \
                $(OBJ_DIR)/m3stats.o \
                $(OBJ_DIR)/m3suapi.o \
                $(OBJ_DIR)/m3suinit.o \
                $(OBJ_DIR)/m3suind.o \
                $(OBJ_DIR)/m3suindq.o \
                $(OBJ_DIR)/m3sumisc.o \
                $(OBJ_DIR)/m3tlind.o \
                $(OBJ_DIR)/m3tlsock.o \
                $(OBJ_DIR)/m3ua_tl.o \
                $(OBJ_DIR)/m3tlbfdb.o \
                $(OBJ_DIR)/m3tlbftl.o \
                $(OBJ_DIR)/m3tlbfin.o \
                $(OBJ_DIR)/m3tlutil.o \
                $(OBJ_DIR)/m3uainit.o \
                $(OBJ_DIR)/m3uamain.o 

COMOBJFILES   = $(OBJ_DIR)/m3apibuf.o \
                $(OBJ_DIR)/m3uautil.o \
                $(OBJ_DIR)/m3ua_ind_q.o \
                $(OBJ_DIR)/m3ua_dbg.o \
                $(OBJ_DIR)/m3ua_cspl_handlr.o \
                $(OBJ_DIR)/m3ua_cspl_init.o 

CLIENTCOMOBJS = $(OBJ_DIR)/m3apibuf.o \
                $(OBJ_DIR)/m3uautil.o 

M3UA_CL_OBJS  = $(OBJ_DIR)/m3smbuf.o \
                $(OBJ_DIR)/m3smcsb.o \
                $(OBJ_DIR)/m3sucsb.o \
                $(OBJ_DIR)/m3smresp.o \
                $(OBJ_DIR)/m3subuf.o \
                $(OBJ_DIR)/m3suresp.o

CLI_OBJS      = $(OBJ_DIR)/m3smcli.o \
                $(OBJ_DIR)/m3smcpk.o \
                $(OBJ_DIR)/m3smcup.o \
                $(OBJ_DIR)/m3sucli.o \
                $(OBJ_DIR)/m3sucpk.o \
                $(OBJ_DIR)/m3sucup.o \
                $(OBJ_DIR)/m3ua_cli.o

MIB_OBJS      = $(OBJ_DIR)/m3uamib.o

PORT_CLI_OBJS = $(OBJ_DIR)/cli_port.o \
                $(OBJ_DIR)/cli_es.o 

PORT_ES_OBJS  = $(OBJ_DIR)/m3ua_es.o \
                $(OBJ_DIR)/m3uaport.o \
                $(OBJ_DIR)/m3ua_es_cspl_init.o \
                $(OBJ_DIR)/m3ua_es_cspl_fnc_handlr.o 

CSPL_PRT_OBJS  = $(OBJ_DIR)/m3ua_es_cspl_init.o \
                $(OBJ_DIR)/m3ua_es_cspl_fnc_handlr.o 

#for SGSN sigtran Port
SL_FLAG= -I$(ccm_project_path)/port \
	 -I$(ccm_project_path)/sdt_kernel/h \
	 -I$(ccm_project_path)/ss7stack/h \
	 -I$(ccm_project_path)/ss7stack/mtp3/basic/shared/h\
	 -I$(ccm_project_path)/h \
	 -I$(ccm_project_path)/common/c-src/h \
	 -I$(ccm_project_path)/cap/SSF/basic/stack/common/h \
	 -I$(ccm_project_path)/cap/ports/common/solaris/h \
	 -I$(ccm_project_path)/cap/SSF/basic/stack/asn/wrapper/h \
	 -I$(ccm_project_path)/nm/server/h	\
	 -I$(ccm_project_path)/ss7stack/sccp/port/h \
	 -I$(ccm_project_path)/ss7stack/sccp/basic/stack/h \
	 -I$(ccm_project_path)/ss7stack/sccp/basic/stack/stat/h \
	 -I$(ccm_project_path)/ss7stack/sccp/basic/stack/errp/h \
	 -I$(ccm_project_path)/ss7stack/sccp/basic/stack/sclc/h \
	 -I$(ccm_project_path)/ss7stack/sccp/basic/stack/redn/h \
	 -I$(ccm_project_path)/ss7stack/sccp/basic/shared/h \
	 -I$(ccm_project_path)/ss7stack/sccp/basic/shared/dbg/h \
	 -I$(ccm_project_path)/sigtran/sctp/basic/stack/dbg/h \
	 -I$(ccm_project_path)/sigtran/sctp/basic/stack/co/h \
	 -I$(ccm_project_path)/sigtran/m3ua/port/h \
	 -I$(ccm_project_path)/build/bssapp/$(ARCH) \
	 -I$(ccm_project_path)/build/gmm/$(ARCH) 

VPATH=$(ccm_project_path)/sigtran/m3ua/port/src

port_src =  m3ua_task.c m3ua_config.c 

obj = $(port_src:%.c=$(ARCH)/%.o)

sgsn_sig_lib = $(ARCH)/libm3ua.a

all           : $(sgsn_sig_lib) setup  stack port cstprt client

$(sgsn_sig_lib): $(obj)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

$(ARCH)/%.o: %.c
	$(CC) $(SL_FLAG)  -DMTP3 -DSTACK_PRINT=ss7_over_sigtran_log_print -DCDR_FTP -DNS_OVER_FR -DSCTP_STATS_ENABLED -DSINGLE_THREAD -DANSI_PROTO $< -o $@


stack:		
		@for i in $(MODULES); \
                do \
			echo "-----> Making $$i: $(MAKE) all"; \
			cd $$i; $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) all ; \
			echo "-----> Finished Making $i <-----"; \
		done 
		cd $(SIGTRAN_DIR)/common/gw/make/$(PORT) ;\
		make SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) all_hash ;
		$(LD) -r $(OBJFILES) $(COMOBJFILES) -o $(OBJ_DIR)/m3ua.o
		$(LD) -r $(M3UA_CL_OBJS) -o $(OBJ_DIR)/m3uac.o

cstprt           :
		@for i in $(CSTPRT_MODULES); \
		do \
			echo "-----> Making $$i: $(MAKE) all"; \
			cd $$i; $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) all ; \
			echo "-----> Finished Making $i <-----"; \
		done 
		$(LD) -r $(CSTPRTOBJFILES) -o $(OBJ_DIR)/m3ua_cstprt.o

client        : 
		@for i in $(SHAREDCLIMODULES); \
                do \
			echo "-----> Making $$i: $(MAKE) all"; \
			cd $$i; $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) all ; \
			echo "-----> Finished Making $i <-----"; \
		done 
		@for i in $(CLIMODULES); \
                do \
			echo "-----> Making $$i: $(MAKE) all"; \
			cd $$i; $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) all ; \
			echo "-----> Finished Making $i <-----"; \
		done 
		$(LD) -r $(CLI_OBJS)  -o $(OBJ_DIR)/m3uacli.o

port          : 
		@for i in $(PORTMODULES); \
                do \
			echo "-----> Making $$i: $(MAKE) all"; \
			cd $$i; $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) all ; \
			echo "-----> Finished Making $i <-----"; \
		done 
		$(LD) -r $(PORT_CLI_OBJS) -o $(OBJ_DIR)/port_cli.o
		$(LD) -r $(PORT_ES_OBJS) -o $(OBJ_DIR)/port_es.o
		$(LD) -r $(CSPL_PRT_OBJS) -o $(OBJ_DIR)/port_cspl.o

mib           : setup
		@for i in $(MIBMODULE); \
                do \
			echo "-----> Making $$i: $(MAKE) all"; \
			cd $$i; $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) all ; \
			echo "-----> Finished Making $i <-----"; \
		done

setup         :
		if [ -d $(M3UA_DIR)/obj ] ; \
                then \
                    echo "Dir exists" ; \
                else \
                mkdir -p $(M3UA_DIR)/obj ; \
                fi
		if [ -d $(M3UA_DIR)/obj/$(CPU) ] ; \
                then \
                    echo "Dir exists" ; \
                else \
                    mkdir -p $(M3UA_DIR)/obj/$(CPU) ; \
                fi
		if [ -d $(M3UA_DIR)/lib ] ; \
                then \
                    echo "Dir exists" ; \
                else \
                    mkdir -p $(M3UA_DIR)/lib ; \
                fi
	
libs            :;\
		@for i in $(MODULES); \
                do \
                    echo "Make lib $$i:$(MAKE) lib"; echo ; \
                    cd $$i;\
                    $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) lib ;\
		done
		$(CC) -g -G -o $(M3UA_DIR)/lib/libm3ua.so $(LIBS) 

 ################CLEAN RULES######################

clean		: m3uaclean stackclean sharedclean cstprtclean portclean clientclean
	
m3uaclean:
	cd $(ARCH) && \rm  -f m3ua_task.o libm3ua.a m3ua_bssapp.o  m3ua_config.o  m3ua_port.o && cd ..;
	
stackclean           :;\
		for i in $(MODULES); \
		do \
			echo "Cleaning $$i:$(MAKE) clean"; echo ;\
			cd $$i; \
                        $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) clean ; \
		done
		\rm -f $(OBJ_DIR)/m3ua.o;
		\rm -f $(OBJ_DIR)/m3uac.o;
                

clientclean           :;\
		for i in $(CLIMODULES); \
		do \
			echo "Cleaning $$i:$(MAKE) clean"; echo ;\
			cd $$i; \
                        $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) clean ; \
		done
		\rm -f $(OBJ_DIR)/m3uacli.o;

cstprtclean		:;\
		for i in $(CSTPRT_MODULES); \
		do \
			echo "Cleaning $$i:$(MAKE) clean"; echo ;\
			cd $$i;	\
			$(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) clean ; \
		done
		\rm -f $(OBJ_DIR)/m3ua_cstprt.o;
		

portclean           :;\
		for i in $(PORTMODULES); \
		do \
			echo "Cleaning $$i:$(MAKE) clean"; echo ;\
			cd $$i; \
                        $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) clean ; \
		done
		\rm -f $(OBJ_DIR)/port_cli.o;
		\rm -f $(OBJ_DIR)/port_es.o;

mibclean           :;\
		for i in $(MIBMODULE); \
		do \
			echo "Cleaning $$i:$(MAKE) clean"; echo ;\
			cd $$i; \
			$(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) clean ; \
		done
		\rm -f $(OBJ_DIR)/m3uamib.o;


sharedclean           :;\
		for i in $(SHAREDCLIMODULES); \
		do \
			echo "Cleaning $$i:$(MAKE) clean"; echo ;\
			cd $$i; \
                        $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) clean ; \
		done

depend          :;\
		find . -name makefile.tm* -exec rm -f {} \;
		for i in $(MODULES) $(CLIMODULES) $(CSTPRT_MODULES) $(PORTMODULES); \
		do \
			echo "Make depend for $$i: $(MAKE) depend"; echo ;\
			cd $$i; \
			touch depend.$(CPU) ; \
			$(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) depend ; \
			echo "----> Finished Making $$i <----\n"; \
		done
	

