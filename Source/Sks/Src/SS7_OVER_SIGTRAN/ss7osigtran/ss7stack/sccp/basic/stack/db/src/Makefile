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

UNIT= db

INCLUDES= \
	$(STACK_COMMON_INCLUDE_DIR) \
	-I$(SCCP_STACK_ROOT)/$(UNIT)/h

OBJS=   sc_dbadd.o \
	sc_dbdel.o \
	sc_dbini.o \
	sc_dbloc.o \
	sc_dbhsh.o \
	sc_dbmsc.o

all:	$(OBJS)

clean:
	$(RM) $(OBJS) 

.c.o:
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $<



