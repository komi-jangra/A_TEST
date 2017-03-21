# Makefile for Gbh 
export TAU_VERSION :=TAU_4.3
include ../../../../Csapp/Util/make.opt

BASE_NAME     = Gbh
MAKEFILE_NAME = Makefile.Gbh
# BIN_NAME is the name with which binary is to be installed and used.
BIN_NAME      = OAMS_GBH
#ifeq ($(LOCATION),Aricent)
#     export TAUBATCH :=$(TAU4.3BATCH)
#     export PATH := /usr/kerberos/bin:/usr/local/bin:/bin:/usr/bin:/usr/X11R6/bin:$(TAU_4.3_DIR)/bin:$(MVL_BIN_DIR):
#     else
#      export PATH := /usr/kerberos/bin:/usr/local/bin:/bin:/usr/bin:/usr/X11R6/bin:$(TAU_DIR)/bin:$(MVL_BIN_DIR):
#endif

all: generate compile install

generate:
ifeq ($(PLATFORM),Host)
	$(TAUBATCH) --project ../Model/Gbh.ttp --config Default -G
endif
ifeq ($(PLATFORM),Target)
	$(TAUBATCH) --project ../Model/Gbh.ttp --config Target -G
endif
compile:
	make -f $(MAKEFILE_NAME) sctdir=$(KERNEL_DIR) $(USERARGS) $(USERDEFAULT)

install:
	cp -f $(BASE_NAME)_ap*.sct $(REL_BIN)/Exec/PP/$(BIN_NAME)-${VERSION}

clean:
	make -f $(MAKEFILE_NAME) sctdir=$(KERNEL_DIR) $(USERARGS) clean
	-rm -f $(BASE_NAME)_ap*.sct

uninstall:
	rm -f $(REL_BIN)/Exec/PP/$(BIN_NAME)-${VERSION}
