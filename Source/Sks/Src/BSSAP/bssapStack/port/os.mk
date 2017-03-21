
ifndef CSPL_FLAGS
	CSPL_FLAGS = -g -pedantic -Wall -W -Waggregate-return -Wstrict-prototypes -Wno-unused -DSYSLOG_SUPPORT -I ${ccm_project_path}/h
endif

ifndef CSPL_COMPILE
	CSPL_COMPILE = gcc
 ifeq ($(ARCH), ARM) 
	CSPL_COMPILE = $(VNL_COM_PREFIX)gcc
 endif 
endif

ifndef CSPL_LINKOBJ
	CSPL_LINKOBJ = ld -r
 ifeq ($(ARCH), ARM) 
	CSPL_LINKOBJ = $(VNL_COM_PREFIX)ld -r
 endif 
endif

ifndef CSPL_LINKEXE
	CSPL_LINKEXE = $(CSPL_COMPILE)
endif

ifndef CSPL_AR
	CSPL_AR = ar rv
 ifeq ($(ARCH), ARM) 
	CSPL_AR = $(VNL_COM_PREFIX)ar rv
 endif 
endif

ifndef CSPL_RANLIB
	CSPL_RANLIB = ranlib
ifeq ($(ARCH), ARM)
CSPL_RANLIB = $(VNL_COM_PREFIX)ranlib
endif
endif

ifndef CSPL_LIBRARIES
	CSPL_LIBRARIES = 
endif


