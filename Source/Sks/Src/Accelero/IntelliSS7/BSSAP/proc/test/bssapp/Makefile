include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/SCCP/include \
       	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include 

CXXFLAGS := $(CXXFLAGS) -I../../include  -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include \
	  -I$(ITS_ROOT)/BSSAP/include

LIBS=-L$(ITS_ROOT)/common/lib  \
     -L$(VENDOR_ROOT)/IntelliNet/lib \
     -L../../../lib \
	-lDRIVER++D -lDISPATCH++D -lDRIVERD -lENGINED -lVFrameD -lCCITT-VENDORD \
        -lBSSAPStackD -lrt

OBJS := BssMain.o

ifeq ($(TARGET),BSS)

LIBOBJS := BssCallbacks.o BssMessage.o

all: libBSS.so BSim 

BSim: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o BSim $(OBJS) -L. -lBSS \
 	$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

libBSS.so: $(LIBOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) libBSS.so $(LIBOBJS) $(LIBS)

else

LIBOBJS := MscCallbacks.o BssMessage.o

all: libMSC.so MSim 

MSim: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o MSim $(OBJS) -L. -lMSC \
 	$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS) $(LIBS)

libMSC.so: $(LIBOBJS)
	$(CXX) $(CXXSHAREDARFLAGS) libMSC.so $(LIBOBJS) $(LIBS)

endif

clean:
	$(RM) libBSS.so libMSC.so BSim MSim *.o

# get the rules
#
include $(ITS_ROOT)/config.rules
