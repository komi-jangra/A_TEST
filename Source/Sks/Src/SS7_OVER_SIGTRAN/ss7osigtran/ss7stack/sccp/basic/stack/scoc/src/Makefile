##############################################################################
#
#       Makefile:
#                       Makefile for HSS test target development
#                       environment.
#
#      DATE         NAME           REFERENCE       REASON
#      -----------------------------------------------------
#      01August'98  Praneet Khare                Original
#
#  Copyright (C) 1998, Hughes Software Systems
##############################################################################
include ${sccp_project_path}/sc_macro.mk

UNIT= scoc

INCLUDES= \
		$(STACK_COMMON_INCLUDE_DIR) \
		-I$(SCCP_STACK_ROOT)/$(UNIT)/h -I$(SCCP_STACK_ROOT)/scmg/h \
		-I$(SCCP_ADV_ROOT)/mtlib/h

OBJS=	sc_clsd.o \
		sc_clsg.o \
		sc_cobld.o \
		sc_coc.o \
		sc_coini.o \
		sc_coprs.o \
		sc_coutl.o \
		sc_estab.o \
		sc_idle.o \
		sc_reset.o \
		sc_start.o

all:$(OBJS)


clean:
		$(RM) $(OBJS) 

.c.o:
		$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $<
