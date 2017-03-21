##############################################################################
#
#       Makefile:
#                       Makefile for HSS test target development
#                       environment.
#
#      DATE       NAME           REFERENCE       REASON
#      -----------------------------------------------------
#      28Aug'2001   Pawanish Modi                 Original
#
#  Copyright (C) 2001, Hughes Software Systems
##############################################################################

include ${sccp_project_path}/sc_macro.mk

UNIT=dsccp

INCLUDES= \
	$(STACK_COMMON_INCLUDE_DIR) \
	-I$(SCCP_STACK_ROOT)/$(UNIT)/h \
	-I$(SCCP_STACK_ROOT)/scmg/h \
	-I$(SCCP_STACK_ROOT)/h \
	-I$(SCCP_STACK_ROOT)/stat/h \
	-I$(SCCP_STACK_ROOT)/sclc/h 

OBJS=   dsccp_main.o \
        dsccp_conf.o \
        dsccp_hm.o \
        dsccp_scoc.o \
        dsccp_scmg.o \
        dsccp_stats.o \
        dsccp_sclc.o 

all:	$(OBJS)

clean:
	$(RM) $(OBJS)

.c.o:
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $<



