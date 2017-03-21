#
# standard macros
#
SHELL = /bin/sh

ifeq ($(ARCH), linux)
    ifndef NATIVELINUX
      ifndef CROSSDEV
          CROSSDEV = /user/trimode/crossdev
      endif
      ifndef KERNELVERSION
          KERNELVERSION=2.2.14
      endif
      CPP = $(CROSSDEV)/i486-linux/bin/gcc -B $(CROSSDEV)/lib/gcc-lib/i486-linux/2.7.2.3/ -I $(CROSSDEV)/i486-linux/include -L $(CROSSDEV)/i486-linux/lib -E
      CC = $(CROSSDEV)/i486-linux/bin/gcc -B $(CROSSDEV)/lib/gcc-lib/i486-linux/2.7.2.3/ -I $(CROSSDEV)/i486-linux/include -L $(CROSSDEV)/i486-linux/lib
      KERNEL_CC = $(CROSSDEV)/i486-linux/bin/gcc -B $(CROSSDEV)/lib/gcc-lib/i486-linux/2.7.2.3/ 
      KERNEL_INCLUDES=-I$(CROSSDEV)/i486-linux/kernel-$(KERNELVERSION)/include
      KERNEL_VERSION=$(shell echo $(KERNELVERSION) | perl -e '@s=split(/\./,<STDIN>);print($$s[0],"_",$$s[1])')
      AR = $(CROSSDEV)/i486-linux/bin/ar
      LD = $(CROSSDEV)/i486-linux/bin/ld
      RANLIB = $(CROSSDEV)/i486-linux/bin/ranlib
      STRIP = $(CROSSDEV)/i486-linux/bin/strip
      COMMONLIB=
      SAFELIB=
      TCL_LIB= -L$(CROSSDEV)/i486-linux/lib -ltix -ltk -ltcl -ldl
      TCL_INC= -I $(CROSSDEV)/i486-linux/include
      X_LIB= -L$(CROSSDEV)/i486-linux/lib-X11 -lX11
      X_INC= -I$(CROSSDEV)/i486-linux/include
      LDFLAGS = -L $(CROSSDEV)/i486-linux/lib
    else
      CPP = gcc -E -D__C_APPL
      CC = gcc -D__C_APPL
      KERNEL_CC = gcc -D__C_APPL
	  ifndef kernel_src_path
	      KERNEL_INCLUDES=-I/usr/src/linux-$(shell uname -r)/include
	  else
	      KERNEL_INCLUDES=-I$(kernel_src_path)/include
	  endif
      KERNEL_VERSION=$(shell uname -r |  perl -e '@s=split(/\./,<STDIN>);print($$s[0],"_",$$s[1])')
      AR = ar
      LD = ld
      RANLIB = ranlib
      STRIP = strip
      COMMONLIB=
      SAFELIB=
      X_LIB= -L/usr/X11R6/lib -lX11 
      X_INC= -I/usr/include
	  LDFLAGS = -L /usr/lib -L /usr/lib/i386-linux-gnu/
     endif
    endif

ifeq ($(ARCH), i386)
    ARCH = sparc
    CPP = gcc -E
    CC = gcc
    AR = ar
    LD = ld
    RANLIB = ranlib
    STRIP = strip
    SAFELIB=-lsocket -lnsl
    COMMONLIB=-lposix4 -lsocket -lnsl
    TCL_LIB= -L/user/trimode/native.sun/lib -ltix4.1.8.0 -ltk8.0 -ltcl8.0
    TCL_INC= -I/user/trimode/native.sun/include
    X_LIB= -L/usr/openwin/lib -lX11
    X_INC= -I/usr/openwin/include
	LDFLAGS = -L /usr/lib
endif

ARFLAGS = rv

CPPFLAGS = \
	-I$(ccm_project_path)/h \
	-I$(ccm_project_path)/port \
	-I$(ccm_project_path)/port/cspl/h \
	-I../h \
	-D_REENTRANT \
	-DANSI_PROTO \
	-DSINGLE_THREAD \
	-D_LARGEFILE64_SOURCE -D_FILE_OFFSET=64 \
	-USTACK_PRINT=ss7_over_sigtran_log_print \
    -Ulogprintf=ss7_over_sigtran_log_print \
    -UDtraceprintf=ss7_over_sigtran_log_print \
    -DSYSLOG_SUPPORT \
    -DNS_AUTO_UNBLOCK_AFTER_RESET \
	-DPURIFY_FIXES_4_4_1 \
	-DLOGGER_IMR

ifdef M3UA
CPPFLAGS += -DM3UA
endif

ifdef EXPERIMENTAL
CPPFLAGS += -DEXPERIMENTAL
endif

ifndef NOERROR
CPPFLAGS += -DGSN_ERROR_LOGGING
endif

ifndef NOTRACE
CPPFLAGS += -DGSN_FIELD_TRACE
endif

#CFLAGS = -g -pedantic -Wall -W -Wcast-align -Wstrict-prototypes
CFLAGS = -Wall -Wcast-align -Wstrict-prototypes -Wno-unused

ifndef PRODUCTION
CFLAGS += -g 
endif

ifdef OPTIMIZE
CFLAGS += -O3
endif

ifdef PROFILE
CFLAGS += -pg
endif

ifdef PERFORMANCE
CPPFLAGS += -DPERFORMANCE_STATS
endif

CPPFLAGS += -DCDR_FTP

MKDEP = gcc -M $(CPPFLAGS)

