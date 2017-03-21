include $(ccm_project_path)/ss7stack/lib/macros.mk

CFLAGS= -g -DANSI_PROTO -DSCCP -DSCCP_STATS_ENABLED -DSCCP_ITU  -DSCCP_ERROR_ENABLED -DSCCP_TRACE_ENABLED -DSIGTRAN_BSC_BSSAP_IF

VPATH = $(ccm_project_path)/ss7stack/src \
	$(ccm_project_path)/ss7stack/port/src

common_src = s7_sm.c s7_stdbg.c s7_sterr.c s7_stst.c
port_src = ss7_port.c

src = $(common_src) $(port_src)

obj = $(src:%.c=$(ARCH)/%.o)

lib = $(ARCH)/libscommon.a

all: $(lib)

$(lib): $(obj)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

$(ARCH)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(lib) $(obj)

#include $(ccm_project_path)/lib/rules.mk
