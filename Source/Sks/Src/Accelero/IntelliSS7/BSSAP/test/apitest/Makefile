#
# get the vars
#
include $(ITS_ROOT)/config.vars

OBJS=    test1.o

CFLAGS := $(CFLAGS) -I../../include \
          -I$(ITS_ROOT)/tools/include
CXXFLAGS := $(CXXFLAGS) -I../include \
          -I$(ITS_ROOT)/tools/include

all: test1

clean:
	$(RM) $(OBJS) .depend

test1: $(OBJS)
	$(CXX) $(CXXFLAGS) -o test1 $(OBJS) -L../../lib \
          -L$(ITS_ROOT)/tools/lib \
          -L$(ITS_ROOT)/common/lib \
          -lBSSAP++D -lSUPPORTD -lCORED -lUNITTESTD 

#
# get the rules
#
include $(ITS_ROOT)/config.rules
