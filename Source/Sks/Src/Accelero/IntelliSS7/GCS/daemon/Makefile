.SUFFIXES: .lo .to .tlo
include $(CONFIG_VAR)/config.vars

prefix=/usr/local
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
sbindir=${exec_prefix}/sbin
libdir=${exec_prefix}/lib
includedir=${prefix}/include
mandir=${prefix}/man
mansubdir=man
sysconfdir=${prefix}/etc
piddir=/var/run
srcdir=.
top_srcdir=..
buildtoolsdir=$(top_srcdir)/buildtools
host=i686-pc-linux-gnu

DESTDIR=

SPREAD_PROGRAM=${exec_prefix}/sbin/spread
SP_MAJOR_VERSION=4
SP_MINOR_VERSION=0
SP_PATCH_VERSION=0
VERSION=4.0.0

PATHS= 
####added by sandeep #######
ifeq ($(FEATURE),bpm-enable)
DEFINES:=$(DEFINES) -DPLATFORM_IMR -DAPP_MULTITHREADS -D__i386__
else
DEFINES:=$(DEFINES) -UPLATFORM_IMR -DAPP_MULTITHREADS -D__i386__
endif
ifeq ($(OS),linux)
CFLAGS := $(CFLAGS) -static -g -pg -I. -I${BPM_INC}/../Sys    -I${BPM_INC}/../Ipc
SYSLIBS := $(SYSLIBS) -L$(SYSEXE_ROOT)/Host/CommonLib/CP
CC=gcc -D__C_APPL
LD=gcc
 
else
CFLAGS := $(CFLAGS) -static -g -pg -I.  -I${BPM_INC}/../Sys    -I${BPM_INC}/../Ipc  -I${BPM_INC} 
SYSLIBS := $(SYSLIBS) -L$(SYSEXE_ROOT)/Target/CommonLib/CP -lplatformLib
CC=ppc_85xx-gcc -D__C_APPL -DAPP_MULTITHREADS -D__i386__
LD=ppc_85xx-gcc
endif
####added by sandeep #######
#CFLAGS=-g -O2 -Wall
CPPFLAGS=-I. -I$(srcdir) -I$(top_srcdir)/include -I../stdutil/src -I$(top_srcdir)/stdutil/src  $(PATHS) -DHAVE_CONFIG_H -DAPP_MULTITHREADS -D__i386__
#LDFLAGS= 
LIBS=-lm -lnsl  
THLDFLAGS=
THLIBS=-lpthread 
LEX=/usr/bin/flex
INSTALL=/usr/bin/install -c
SOFTLINK=ln -s
PERL=/usr/bin/perl
ENT=@ENT@
EXEEXT=

TARGETS=spread$(EXEEXT) spmonitor$(EXEEXT)

SPREADOBJS= main.o spread.o protocol.o session.o groups.o alarm.o events.o memory.o membership.o data_link.o network.o status.o log.o flow_control.o message.o lex.yy.o y.tab.o configuration.o acm.o acp-permit.o auth-null.o auth-ip.o

MONITOR_OBJS= monitor.o  alarm.o events.o memory.o data_link.o lex.yy.o y.tab.o configuration.o acm.o

TMONITOR_OBJS= monitor.to  alarm.to events.to memory.to data_link.to lex.yy.to y.tab.to configuration.to acm.to

all: $(TARGETS)

$(SPREADOBJS): config.h
$(MONITOR_OBJS): config.h
$(TMONITOR_OBJS): config.h

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

.c.to:
	$(CC) $(LDFLAGS) $(CFLAGS) $(CPPFLAGS)  -D_REENTRANT -c $< -o $*.to

parser:
	$(YACC) -d $(srcdir)/config_parse.y
	$(LEX) $(srcdir)/config_gram.l

#Disabled now because of timestamp errors causing extra regeneration
#To build parser run "make parser" after ./configure is run.
#lex.yy.c:       config_gram.l y.tab.c
#	$(LEX) config_gram.l

#y.tab.c:        config_parse.y
#	$(YACC) -d config_parse.y

ifeq ($(OS),linux)
spread$(EXEEXT): $(SPREADOBJS) ../stdutil/lib/libstdutil-threaded-release.a	
	$(LD) -o $@ $(SPREADOBJS) -L$(SYSEXE_ROOT)/Host/CommonLib/CP -llog -lfrm -lpthread ../stdutil/lib/libstdutil-threaded-release.a  $(LDFLAGS) $(LIBS) 
else
spread$(EXEEXT): $(SPREADOBJS) ../stdutil/lib/libstdutil-threaded-release.a	
	$(LD) -o $@ $(SPREADOBJS) -L$(SYSEXE_ROOT)/Target/CommonLib/CP -lplatformLib  -llog -lfrm -lpthread ../stdutil/lib/libstdutil-threaded-release.a $(LDFLAGS) $(LIBS)
endif
spmonitor$(EXEEXT): $(MONITOR_OBJS)
	$(LD) -o $@ $(MONITOR_OBJS) $(LDFLAGS) $(LIBS) $(THLIBS) 

sptmonitor$(EXEEXT): $(TMONITOR_OBJS)
	$(LD) $(THLDFLAGS) -o $@ $(TMONITOR_OBJS) $(LDFLAGS) $(LIBS) $(THLIBS) 

testprog: spsend$(EXEEXT) sprecv$(EXEEXT)

spsend$(EXEEXT): s.o alarm.o data_link.o events.o memory.o
	$(LD) -o $@ s.o alarm.o data_link.o events.o memory.o $(LDFLAGS) $(LIBS)

sprecv$(EXEEXT): r.o alarm.o data_link.o
	$(LD) -o $@ r.o alarm.o data_link.o $(LDFLAGS) $(LIBS)

clean:
	rm -f *.lo *.tlo *.to *.o *.a *.dylib $(TARGETS) spsimple_user
	rm -f config.cache config.log docs/*.out core
	rm -rf autom4te.cache
	rm -rf ../bin/$(host)

distclean: clean
	rm -f Makefile config.h config.status *~

binrelease: $(TARGETS)
	$(buildtoolsdir)/mkinstalldirs ../bin/$(host)
	$(INSTALL) -m 0755 -s spmonitor$(EXEEXT) ../bin/$(host)/spmonitor$(EXEEXT)
	$(INSTALL) -m 0755 -s spread$(EXEEXT) ../bin/$(host)/spread$(EXEEXT)

install: $(TARGETS) install-files 

install-files:
	$(buildtoolsdir)/mkinstalldirs $(DESTDIR)$(bindir)
	$(buildtoolsdir)/mkinstalldirs $(DESTDIR)$(sbindir)
	$(buildtoolsdir)/mkinstalldirs $(DESTDIR)$(includedir)
	$(INSTALL) -m 0755 -s spmonitor$(EXEEXT) $(DESTDIR)$(bindir)/spmonitor$(EXEEXT)
	$(INSTALL) -m 0755 -s spread$(EXEEXT) $(DESTDIR)$(sbindir)/spread$(EXEEXT)

uninstallall:	uninstall
	-rmdir $(DESTDIR)$(bindir)
	-rmdir $(DESTDIR)$(sbindir)

uninstall: 
	-rm -f $(DESTDIR)$(bindir)/spmonitor$(EXEEXT)
	-rm -f $(DESTDIR)$(sbindir)/spread$(EXEEXT)
