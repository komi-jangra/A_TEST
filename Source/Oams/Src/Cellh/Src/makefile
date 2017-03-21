# Makefile for Cellh 
include ../../../../Csapp/Util/make.opt

BASE_NAME     = System_CellHandler
MAKEFILE_NAME = Makefile.System_CellHandler
# BIN_NAME is the name with which binary is to be installed and used.
BIN_NAME      = OAMS_CELLHM

all: generate compile install

generate:
ifeq ($(PLATFORM),Host)
	$(TAUBATCH) --project ../Model/CELLH.ttp --config Default -G
endif
ifeq ($(PLATFORM),Target)
	$(TAUBATCH) --project ../Model/CELLH.ttp --config Target -G
endif

compile:
	make -f $(MAKEFILE_NAME) sctdir=$(KERNEL_DIR) $(USERARGS) $(USERDEFAULT)

install:
	cp -f $(BASE_NAME)_ap*.sct $(REL_BIN)/Exec/CP/$(BIN_NAME)-${VERSION}

clean:
	make -f $(MAKEFILE_NAME) sctdir=$(KERNEL_DIR) $(USERARGS) clean
	-rm -f $(BASE_NAME)_ap*.sct

uninstall:
	rm -f $(REL_BIN)/Exec/CP/$(BIN_NAME)-${VERSION}
