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
	ui \
	sm

all:	CLIENT_MODULES

CLIENT_MODULES:
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



