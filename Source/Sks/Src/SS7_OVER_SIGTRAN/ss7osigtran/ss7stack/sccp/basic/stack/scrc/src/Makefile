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

UNIT= scrc

INCLUDES= \
	$(STACK_COMMON_INCLUDE_DIR) \
	-I$(SCCP_STACK_ROOT)/$(UNIT)/h \
	-I$(SCCP_ADV_ROOT)/mtlib/h

OBJS=   sc_rcprs.o \
        sc_rout.o \
        sc_rcbld.o \
	sc_rcmsc.o

all:	$(OBJS)

clean:
	$(RM) $(OBJS) 

.c.o:
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $<



