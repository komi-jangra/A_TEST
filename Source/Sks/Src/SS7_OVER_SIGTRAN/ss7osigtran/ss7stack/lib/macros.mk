#
# Make macros for SS7 stack
#
include $(ccm_project_path)/lib/macros.mk
ifdef MTP3
	MTP3_SUPPORT = 1
endif
ifdef HLR_MTP3
	MTP3_SUPPORT = 1
endif

CPPFLAGS += -I$(ccm_project_path)/ss7stack/h \
            -DSCCP -DANSI_PROTO  \
            -DSCCP_STATS_ENABLED \
            -DSCCP_ERROR_ENABLED \
            -DSCCP_TRACE_ENABLED

ifdef MTP3_SUPPORT  
CPPFLAGS += -DMTP3
endif
