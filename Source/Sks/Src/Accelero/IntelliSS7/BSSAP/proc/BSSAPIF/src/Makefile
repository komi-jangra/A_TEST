include $(ITS_ROOT)/config.vars

ifeq ($(TARGET),NATIVE)
DEFINES := $(DEFINES) -DNATIVE
endif

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/SCCP/include \
       	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include 

CXXFLAGS := $(CXXFLAGS) -I ../include -I../../include  \
          -I$(ITS_ROOT)/BSSAP/proc/include \
          -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include \
	  -I$(ITS_ROOT)/BSSAP/include

LIBS=-L$(ITS_ROOT)/common/lib  \
     -L$(VENDOR_ROOT)/IntelliNet/lib \
     -L$(ITS_ROOT)/BSSAP/lib \
	-lDRIVER++D -lDISPATCH++D -lDRIVERD \
        -lENGINED -lVFrameD -lCCITT-VENDORD \
        -lBSSAPStackD -lrt

OBJS := MscMain.o

LIBOBJS := bssap_ifcallbacks.o bssapif_dispatcher.o bssapif_socket.o \
           bssapif_trace.o bssapif_transport.o

all: libBSSAPIntf.so MSim 

MSim: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o MSim $(OBJS) -L. -lBSSAPIntf \
 	$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) $(LIBS)

libBSSAPIntf.so: $(LIBOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) libBSSAPIntf.so $(LIBOBJS) $(LIBS)

clean:
	$(RM) libBSSAPIntf.so MSim *.o

# get the rules
#
include $(ITS_ROOT)/config.rules
