####################################################################
# 
#  Makefile file for SCCP_Test program using engine.
#                  README 
#
####################################################################

include $(ITS_ROOT)/config.vars

MAIN_OBJ = AppMain.o

CODEC_OBJ= ./codec/AppCodec.o

CFLAGS := -I../include/codec $(CFLAGS) \
          -D$(PROTOCOL) -DUSE_INTELLINET_STACK \
          -I../include/sendrecv \
          -I../include/codec \
          -I$(ITS_ROOT)/common/include \
          -I$(ITS_ROOT)/MTP3/include \
          -I$(ITS_ROOT)/SCCP/include \
          -I$(ITS_ROOT)/TCAP/include \
          -I$(ITS_ROOT)/SLTM/include \
          -I$(ITS_ROOT)/MTP2/include \
          -I$(ITS_ROOT)/ISUP/include \
          -I$(ITS_ROOT)/SNMM/include \
          -I$(ITS_ROOT)/ENGINE/include \
          -I$(ITS_ROOT)/IOSCDMA/include \
          -I$(VENDOR_ROOT)/IntelliNet/include

CODEC_OBJ := $(CODEC_OBJ) ./codec/bssap_codec/bssap-codec.o
ITS_LIBS := $(ITS_LIBS) -L$(ITS_ROOT)/BSSAP/lib -lBSSAP++$(DBGSUFFIX)
CFLAGS := $(CFLAGS) -I$(ITS_ROOT)/BSSAP/include/

ifeq ($(TARGET),MSC)

EXENAME := BSim
SENDRECV : ../bin/libSampleApp$(DBGSUFFIX).so ../bin/$(EXENAME)

else

EXENAME := MSim
SENDRECV : ../bin/libSampleApp$(DBGSUFFIX).so ../bin/$(EXENAME)

endif


CXXFLAGS := $(CXXFLAGS) -I../include -I$(ITS_ROOT)/common/include \
        -I$(ITS_ROOT)/SCCP/include \
        -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include

SENDRECV_OBJS := $(CODEC_OBJ) \
                ./sendrecv/AppUtils.o \
                ./sendrecv/AppTrace.o \
                ./sendrecv/AppSendRecv.o \
                ./sendrecv/AppDsm.o \
                ./sendrecv/AppDbc.o \
                ./sendrecv/AppMesg.o \
                ./sendrecv/AppCallbacks.o 

CPP_OBJS := $(MAIN_OBJ) $(SENDRECV_OBJS)

SYSLIBS := -lrt $(SYSLIBS)

ifeq ($(APP_TYPE),CODEC)

CFLAGS := $(CFLAGS) -DCODEC_ONLY
CXXFLAGS := $(CXXFLAGS) -DCODEC_ONLY
CPP_OBJS = $(MAIN_OBJ) $(CODEC_OBJ)
ITS_LIBS := $(ITS_LIBS) -L$(ITS_ROOT)/common/lib \
            -lCORE$(DBGSUFFIX)
all : CODEC

else

ITS_LIBS := $(ITS_LIBS) -L$(ITS_ROOT)/common/lib \
            -L$(VENDOR_ROOT)/IntelliNet/lib \
            -lENGINE$(DBGSUFFIX) \
            -lDISPATCH++$(DBGSUFFIX) \
            -lDRIVER++$(DBGSUFFIX) \
            -lVFrame$(DBGSUFFIX) \
            -lGCS-CLIENT$(DBGSUFFIX) \
            -l$(PROTOCOL)-VENDOR$(DBGSUFFIX) 

endif

CODEC : ../bin/$(TARGET)Codec$(DBGSUFFIX)


../bin/$(TARGET)Codec$(DBGSUFFIX) : $(CPP_OBJS)
		$(CXX) $(CXXFLAGS) $(LD_FLAGS) -o $@ $(CPP_OBJS) \
		$(ITS_LIBS) $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS)

../bin/libSampleApp$(DBGSUFFIX).so : $(SENDRECV_OBJS)
	$(SHAREDAR) $(SHAREDARFLAGS) \
        ../bin/libSampleApp$(DBGSUFFIX).so \
        $(SENDRECV_OBJS)

../bin/$(EXENAME) : $(CPP_OBJS)
		$(CXX) $(CXXFLAGS) $(LD_FLAGS) -o $@ $(CPP_OBJS) \
		$(ITS_LIBS) $(SYSLIBS) $(SOCKLIBS) $(THREADLIBS) \
                -L../bin -lSampleApp$(DBGSUFFIX)

%.o : %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $<

clean :
	$(RM) $(CPP_OBJS)  \
        ../bin/$(TARGET)Codec$(DBGSUFFIX) \
        ../bin/MSim \
        ../bin/BSim \
        ../bin/libSampleApp$(DBGSUFFIX).so 

