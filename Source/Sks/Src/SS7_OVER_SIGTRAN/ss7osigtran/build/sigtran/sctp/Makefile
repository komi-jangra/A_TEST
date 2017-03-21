SHELL=/bin/sh
include $(ccm_project_path)/lib/macros.mk

include $(ccm_project_path)/sigtran/sctp/build/$(ARCH)/sctp_mac.mk
SIGTRAN_DIR=$(ccm_project_path)/sigtran
SCTP_BASE_DIR=$(ccm_project_path)/sigtran/sctp

CSPL_DIR=$(ccm_project_path)/port/cspl

ifeq ($(ARCH), linux)
		CPU=linux
		PORT=linux
		CC = gcc -O2 -c -g -pg -D__C_APPL
		LDEXEC = -O2 -c -g -pg
		LD = ld -r
		RTOS = .rt
endif
ifeq ($(ARCH), sparc)
	CPU=sparc
	PORT=solaris
endif

ifeq ($(ARCH), ARM)
		CPU=ARM
		PORT=ARM
		AR=$(VNL_COM_PREFIX)ar
    CC=$(VNL_COM_PREFIX)gcc -D__C_APPL
		LDEXEC = -O2 -c -g -pg
		LD = $(VNL_COM_PREFIX)ld -r
		RTOS = .rt
endif

OBJS=	
SUBDIRS=	${SIGTRAN_DIR}/sctp/basic
ARCHDEFINES = 
LIBS = -lpthread -lsocket -lnsl
COMMONMODULES = $(SIGTRAN_COMMON_DIR)/port/make/$(PORT)

all:		build common
install:	install_objs
touch:		touch_all
clean:		clean_all common_clean

build:	$(SUBDIRS)
	@-for i in $(SUBDIRS);\
	do\
		echo "Building in $$i" ; \
		(cd $$i ; \
		 $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) \
		) ; \
	done
common:
	@for i in $(COMMONMODULES); \
	do \
	echo "-----> Making $$i: $(MAKE) all"; \
	cd $$i; $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) OS_ALL OS_CLI CFLAGS_GCC='$(SIG_COMMON_FLAGS)'; \
	echo "-----> Finished Making $i <-----"; \
	done

install_objs:
	@-for i in $(SUBDIRS);\
	do\
		echo "Copying objects from $$i" ; \
		(cd $$i ; \
	 	 $(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) install INSTALL_DIR=$(INSTALL_DIR) \
		) ; \
	done

touch_all:
	@-for i in $(SUBDIRS);\
	do\
		(cd $$i ; \
			$(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) touch \
		) ; \
	done

clean_all:
	@-for i in $(SUBDIRS);\
	do\
		(cd $$i ; \
			$(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) clean \
		) ; \
	done
common_clean:
	for i in $(COMMONMODULES); \
	do \
	echo "Cleaning $$i:$(MAKE) clean"; echo ;\
	cd $$i; \
	$(MAKE) SIGTRAN_DIR=$(SIGTRAN_DIR) SCTP_BASE_DIR=$(SCTP_BASE_DIR) CSPL_DIR=$(CSPL_DIR) CPU=$(CPU) PORT=$(PORT) clean ; \
	done
