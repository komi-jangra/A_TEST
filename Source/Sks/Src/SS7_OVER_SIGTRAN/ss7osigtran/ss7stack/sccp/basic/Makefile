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
	stack \
	shared \
        client

all:	SCCP_MODULES
	$(AR) -r $(SCCP_OBJ_DIR)/$(SCCP_STACK_LIB)  $(SCCP_STACK_ROOT)/sc_stack.o
	$(AR) -r $(SCCP_OBJ_DIR)/$(SCCP_SHRD_LIB)   $(SCCP_SHARED_ROOT)/sc_shrd.o
	$(AR) -r $(SCCP_OBJ_DIR)/$(SCCP_STACK_CLIENT_LIB) \
	       $(SCCP_CLIENT_ROOT)/ui/src/ui.o
	$(AR) -r $(SCCP_OBJ_DIR)/$(SCCP_SM_CLIENT_LIB) \
	       $(SCCP_CLIENT_ROOT)/sm/src/sm.o


SCCP_MODULES:
	for i in $(MODULES); \
	do \
		(cd $$i; \
			echo $$i; \
			$(MAKE) all \
		); \
	done

stack:
	cd $(SCCP_STACK_ROOT); $(MAKE) all

shared:
	cd $(SCCP_SHARED_ROOT); $(MAKE) all

client:
	cd $(SCCP_CLIENT_ROOT); $(MAKE) all

clean:
	$(RM) -f *.o tca.*; \
	for i in $(MODULES); \
	do \
		(cd $$i; \
			echo $$i; \
			$(MAKE) clean \
		); \
	done



