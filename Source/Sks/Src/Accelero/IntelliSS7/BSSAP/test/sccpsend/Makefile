include $(ITS_ROOT)/config.vars

CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/SCCP/include \
       	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include 

CXXFLAGS := $(CXXFLAGS) -I$(ITS_ROOT)/SCCP/include \
	  -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include \
	  -I$(ITS_ROOT)/BSSAP/include

all: libAPP.so test

clean:
	$(RM) test libAPP.so app.o

LIBS=-L$(ITS_ROOT)/common/lib  \
     -L$(ITS_ROOT)/BSSAP/lib  -lBSSAP++D \
	-lDRIVER++D -lDISPATCH++D -lENGINED \
       -lmtmalloc \
        -lrt


test: test.cpp libAPP.so
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o test test.cpp -L. -lAPP $(LIBS) \
 	$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)

libAPP.so: app.o
	$(CXX) $(CXXSHAREDARFLAGS) libAPP.so app.o -L$(ITS_ROOT)/BSSAP/lib -lBSSAP++D



# get the rules
#
include $(ITS_ROOT)/config.rules
