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

MODULES= \
	dbg

OBJS=	\
	dbg/src/dbg.o

all:	SHARED_MODULES
	$(LD) $(LDFLAGS) $(OBJS) -o sc_shrd.o

SHARED_MODULES:
	for i in $(MODULES); \
	do \
		(cd $$i/src; \
			echo $$i/src; \
			$(MAKE) all \
		); \
	done

clean:
	$(RM) -f *.o tca.*; \
	for i in $(MODULES); \
	do \
		(cd $$i/src; \
			echo $$i/src; \
			$(MAKE) clean \
		); \
	done



