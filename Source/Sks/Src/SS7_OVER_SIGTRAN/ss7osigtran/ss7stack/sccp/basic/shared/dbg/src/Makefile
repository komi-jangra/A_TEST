##############################################################################
#
#       Makefile:
#                       Makefile for HSS test target development
#                       environment.
#
#      DATE       NAME           REFERENCE       REASON
#      -----------------------------------------------------
#
#      28Jan'98   Sriganesh Kini               Original
#
#  Copyright (C) 1998, Hughes Software Systems
##############################################################################

include ${SS7_ROOT}/sccp/sc_macro.mk

UNIT= dbg

INCLUDES=   -I$(SCCP_SHARED_ROOT)/dbg/h \
            -I$(SCCP_SHARED_ROOT)/h \
            -I$(SCCP_STACK_ROOT)/errp/h \
            -I${SS7_ROOT}/tcap/h \
	    -I $(SS7_ROOT)/h

OBJS=       sc_debug.o

all:    $(UNIT).o

$(UNIT).o:	$(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(UNIT).o

clean:
	$(RM) *.o *.tca

.c.o:
	$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $<

