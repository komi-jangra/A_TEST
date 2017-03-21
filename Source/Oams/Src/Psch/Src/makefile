# Makefile for PSCH
export TAU_VERSION :=TAU_4.3
include ../../../../Csapp/Util/make.opt

BASE_NAME     = SystemClassPsch
MAKEFILE_NAME = Makefile.SystemClassPsch 
# BIN_NAME is the name with which binary is to be installed and used.
BIN_NAME      = OAMS_PSCH

all: generate compile install

generate:
ifeq ($(PLATFORM),Host)
	$(TAUBATCH) --project ../Model/PSCH.ttp --config Default -G
endif
ifeq ($(PLATFORM),Target)
	$(TAUBATCH) --project ../Model/PSCH.ttp --config Target -G
endif
compile:
	make -f $(MAKEFILE_NAME) sctdir=$(KERNEL_DIR) $(USERARGS) $(USERDEFAULT)

install:
	cp -f $(BASE_NAME)_ap*.sct $(REL_BIN)/Exec/PP/$(BIN_NAME)-${VERSION}

clean:
	make -f $(MAKEFILE_NAME) sctdir=$(KERNEL_DIR) $(USERARGS) clean
	-rm -f $(BASE_NAME)_ap*.sct

uninstall:
	rm -f $(REL_BIN)/Exec/CP/$(BIN_NAME)-${VERSION}
