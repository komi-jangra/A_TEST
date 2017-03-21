include $(ccm_project_path)/ss7stack/lib/macros.mk

CPPFLAGS += -I$(ccm_project_path)/ss7stack/sccp/basic/shared/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/shared/dbg/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/client/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/client/ui/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/stack/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/stack/scmg/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/stack/sclc/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/stack/db/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/stack/errp/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/stack/stat/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/stack/redn/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/stack/scoc/h \
	-I$(ccm_project_path)/ss7stack/sccp/basic/stack/disp/h \
	-I$(ccm_project_path)/ss7stack/sccp/port/h \
    -DSCCP -DSCCP_TRACE_ENABLED -DSCCP_REDN_ENABLED -DLOGGER_IMR -DSCCP_RM_IF -DSCCP_STATS_ENABLED -DSCCP_ERROR_ENABLED \
	-DSCCP_INCLUDE_CO_SERVICE -DSCCP_INCLUDE_CO_CLASS3_SERVICE -UBACK_UP_SSN \
    -DSCCP_ITU -DSCCP_ETSI -DSCCP_ANSI -DSCCP_BCGR -DSCCP_CHINESE -DSCCP_JAPANESE \
	-DSCCP_CONNECTION_ID_CHANGES -DSST_AFTER_RESUME -DSCCP_GTT_CALLED_PARTY_ADDRESS_CHANGE -DMARK_SS_PROHIBITED_ON_RESUME

ifdef SST_AFTER_RESUME
	CPPFLAGS += -DMARK_SS_PROHIBITED_ON_RESUME
endif
