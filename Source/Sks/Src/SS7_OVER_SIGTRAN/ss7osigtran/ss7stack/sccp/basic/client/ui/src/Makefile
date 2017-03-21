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

include ${SS7_ROOT}/sccp/sc_macro.mk

UNIT= ui

INCLUDES= \
	$(CLIENT_COMMON_INCLUDE_DIR) \
	-I$(SCCP_CLIENT_ROOT)/$(UNIT)/h

OBJS=   sc_uiprs.o \
        sc_uidfn.o

all:	$(UNIT).o

$(UNIT).o:	$(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(UNIT).o

clean:
	$(RM) *.o tca.*

.c.o:
	$(CC) $(DEFINES) $(CFLAGS) $(INCLUDES) -c $<



