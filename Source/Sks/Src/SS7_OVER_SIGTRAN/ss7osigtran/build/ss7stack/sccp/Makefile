include $(ccm_project_path)/ss7stack/sccp/basic/lib/macros.mk


ifdef MTP3
  CPPFLAGS += -DMTP3 \
  			  -I$(ccm_project_path)/common/c-src/h
endif

VPATH = $(ccm_project_path)/ss7stack/sccp/basic/shared/dbg/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/db/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/disp/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/errp/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/init/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/redn/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/sclc/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/scmg/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/scoc/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/scrc/src \
	$(ccm_project_path)/ss7stack/sccp/basic/stack/stat/src \
	$(ccm_project_path)/ss7stack/sccp/port/src

# client_sm_src = sc_sysmc.c
client_sm_src =
client_ui_src = 
shared_dbg_src = sc_debug.c
stack_db_src = sc_dbadd.c sc_dbdel.c sc_dbhsh.c sc_dbini.c sc_dbloc.c \
	sc_dbmsc.c
stack_disp_src = sc_disp.c
stack_errp_src = sc_err.c
stack_init_src = sc_init.c sc_main.c sc_prov.c sc_sys.c sc_ctrl.c
stack_redn_src = sc_redn.c
stack_sclc_src = sc_clbld.c sc_clc.c sc_clmsc.c sc_clprs.c sc_reas.c \
	sc_routf.c sc_segm.c
stack_scmg_src = sc_bcast.c sc_cong.c sc_mgbld.c sc_mgprs.c sc_msgh.c \
	sc_reg.c sc_spmg.c sc_ssmg.c sc_sstc.c
stack_scoc_src = sc_clsd.c sc_clsg.c sc_cobld.c sc_coc.c sc_coini.c \
	sc_coprs.c sc_coutl.c sc_estab.c sc_idle.c sc_reset.c sc_start.c
stack_scrc_src = sc_rcbld.c sc_rcmsc.c sc_rcprs.c sc_rout.c
stack_stat_src = sc_stats.c
port_src = sccp_task.c sccp_port.c

src = $(client_sm_src) $(client_ui_src) $(shared_dbg_src) \
	$(stack_db_src) $(stack_disp_src) $(stack_errp_src) \
	$(stack_init_src) $(stack_redn_src) $(stack_sclc_src) \
	$(stack_scmg_src) $(stack_scoc_src) $(stack_scrc_src) \
	$(stack_stat_src) $(port_src)

obj = $(src:%.c=$(ARCH)/%.o)

lib = $(ARCH)/libsccp.a

all: $(lib)

$(lib): $(obj)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

$(ARCH)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(lib) $(obj)

#include $(ccm_project_path)/lib/rules.mk
