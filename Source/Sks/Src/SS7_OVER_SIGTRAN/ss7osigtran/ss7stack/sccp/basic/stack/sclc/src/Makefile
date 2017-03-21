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

UNIT= sclc

INCLUDES= \
	$(STACK_COMMON_INCLUDE_DIR) \
	-I$(SCCP_STACK_ROOT)/$(UNIT)/h

OBJS=   sc_clprs.o \
        sc_clbld.o \
        sc_clc.o \
        sc_routf.o \
        sc_reas.o \
        sc_segm.o \
        sc_clmsc.o

all:	$(OBJS)

clean:
	$(RM) $(OBJS) 

.c.o:
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $<



