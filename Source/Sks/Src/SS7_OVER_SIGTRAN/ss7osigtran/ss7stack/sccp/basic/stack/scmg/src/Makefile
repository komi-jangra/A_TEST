##############################################################################
#
#       Makefile:
#                       Makefile for HSS test target development
#                       environment.
#
#      DATE       NAME           REFERENCE       REASON
#      -----------------------------------------------------
#      28Jan'98   Sriganesh Kini                 Original
#
#  Copyright (C) 1998, Hughes Software Systems
##############################################################################

include ${sccp_project_path}/sc_macro.mk

UNIT= scmg

INCLUDES= \
	$(STACK_COMMON_INCLUDE_DIR) \
	-I$(SCCP_STACK_ROOT)/$(UNIT)/h

OBJS=   sc_spmg.o \
        sc_ssmg.o \
	sc_cong.o \
	sc_bcast.o \
	sc_mgprs.o \
	sc_mgbld.o \
	sc_msgh.o \
	sc_sstc.o \
	sc_reg.o

all:	$(OBJS)

clean:
	$(RM) $(OBJS)

.c.o:
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $<
