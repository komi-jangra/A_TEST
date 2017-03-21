#
# Makefile for SIGTRAN stack
#
SHELL=/bin/sh
include $(ccm_project_path)/sigtran/m3ua/build/$(ARCH)/makefile.m3ua

SIGTRAN_DIR=$(ccm_project_path)/sigtran
SCTP_BASE_DIR=$(ccm_project_path)/sigtran/sctp

CSPL_DIR=$(ccm_project_path)/port/cspl
OUT_DIR=$(PWD)

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
export		PORT=ARM
endif


subdir = m3ua sctp

all clean:
	for dir in $(subdir); do \
	    if cd $$dir && $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT)  $@ && cd ..; then \
		true; \
	    else \
		exit 1; \
	    fi; \
	done
m3uaclean:
	cd m3ua/$(ARCH) && \rm  -f m3ua_task.o libm3ua.a m3ua_bssapp.o  m3ua_config.o  m3ua_port.o && cd ../..;

#for SGSN sigtran Port
SL_FLAG= -I$(ccm_project_path)/port \
	 -I$(ccm_project_path)/sdt_kernel/h \
	 -I$(ccm_project_path)/ss7stack/h \
	 -I$(ccm_project_path)/ss7stack/mtp3/basic/shared/h\
	 -I$(ccm_project_path)/h \
	 -I$(ccm_project_path)/common/c-src/h \
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
	 -I$(ccm_project_path)/sigtran/sctp/basic/client/su/h \
	 -I$(ccm_project_path)/sigtran/sctp/basic/stack/port/cspl/h \
	 -I$(ccm_project_path)/sigtran/m3ua/port/h \
	 -I$(ccm_project_path)/build/bssapp/$(ARCH) \
	 -I$(ccm_project_path)/build/gmm/$(ARCH) 

VPATH=$(ccm_project_path)/sigtran/m3ua/port/src

# Amaresh       $(ccm_project_path)/sigtran/m3ua/obj/$(PORT)/m3tlind.o 

sigtran_obj += \
        $(ccm_project_path)/sigtran/m3ua/obj/$(PORT)/m3ua.o \
        $(ccm_project_path)/sigtran/m3ua/obj/$(PORT)/m3uac.o \
        $(ccm_project_path)/sigtran/m3ua/obj/$(PORT)/m3uacli.o \
        $(ccm_project_path)/sigtran/m3ua/obj/$(PORT)/port_cli.o \
        $(ccm_project_path)/sigtran/m3ua/obj/$(PORT)/m3ua_cstprt.o \
        $(ccm_project_path)/sigtran/m3ua/obj/$(PORT)/port_es.o  \
        $(ccm_project_path)/sigtran/sctp/basic/stack/obj/sctp.o \
        $(ccm_project_path)/sigtran/common/port/obj/$(PORT)/sig_os.o \
        $(ccm_project_path)/sigtran/common/port/obj/$(PORT)/sig_hash.o \
	$(ccm_project_path)/sigtran/common/gw/obj/$(PORT)/*.o

gl_library_path = $(ccm_project_path)/sigtran/common/gw/lib/$(PORT)

port_src =  m3ua_task.c m3ua_config.c 

obj = $(port_src:%.c=m3ua/$(ARCH)/%.o) $(sigtran_obj)

sgsn_sig_lib = m3ua/$(ARCH)/libm3ua.a

m3uabuild : $(sgsn_sig_lib) 

$(sgsn_sig_lib): $(obj) $(sigtran_obj)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

m3ua/$(ARCH)/%.o: %.c
	$(CC) $(SL_FLAG) -DSCTP_STATS_ENABLED -DANSI_PROTO  $< -o $@

