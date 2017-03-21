####################################################################
# 
#  Makefile For PDE Simulator  
#                  README 
#
####################################################################


DEFINES := $(DEFINES) -DPDE_DEBUG_PRINT

TEST_OBJS = server.o

CFLAGS := $(CFLAGS) -I.

ITS_LIBS =  \
           -lPOLGW++$(DBGSUFFIX) \
           -lASN++$(DBGSUFFIX) \
           -lCORE$(DBGSUFFIX) \
           -lSUPPORT$(DBGSUFFIX)

LINK_FLAG = -L$(ITS_ROOT)/common/lib \
            -L$(HOME)/cvsroot/polaris/codec/lib

CXXFLAGS := $(CXXFLAGS) -I.


all:bserver

bserver: $(TEST_OBJS) 
	g++ $(CFLAGS) \
        -o bserver $(TEST_OBJS)  \
        $(SOCKLIBS) $(THREADLIBS) -lrt

clean :
	$(RM) $(TEST_OBJS) bserver

# get the rules
#
include $(ITS_ROOT)/config.rules



