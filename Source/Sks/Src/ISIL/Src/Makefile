#include $(ITS_ROOT)/config/config.vaddrs

include $(ITS_ROOT)/config.vars

VERSION_ISIL=${BASE}.${MAJOR}.${MINOR}

ifeq ($(TARGET),NATIVE)
DEFINES := $(DEFINES) -DNATIVE
endif

DEFINES := $(DEFINES)  -DDEBUG_TRACE

ifeq ($(TYPE),MTP2SIM)
DEFINES := $(DEFINES)  -DMTP2SIM

ifeq ($(PLATFORM),mvlppc)
LIBS :=  $(LIBS)  -L$(SYSEXE_ROOT)/Target/CommonLib/CP  -lCCITT-MTP2SIMD 
else

LIBS :=  $(LIBS)  -L$(SYSEXE_ROOT)/Host/CommonLib/CP  -lCCITT-MTP2SIMD 
endif

endif

ifeq ($(TYPE),ADAX)

DEFINES := $(DEFINES)  #-DADAX
 
LIBS :=  $(LIBS) -L$(SYSEXE_ROOT)/Host/CommonLib/CP -lANSI-VENDORD -l$(PROTOCOL)-ADAXVendorD -lLiS 

endif

ifeq ($(TYPE),MCC)

DEFINES := $(DEFINES)  -DTMCC

ifeq ($(PROTOCOL),ANSI)
LIBS :=  $(LIBS) -L$(SYSEXE_ROOT)/Target/CommonLib/CP  -lANSI-VENDORD
else
LIBS :=  $(LIBS) -L$(SYSEXE_ROOT)/Target/CommonLib/CP  -lCCITT-VENDORD
endif


endif

ifeq ($(PLATFORM),mvlppc)

ifeq ($(FEATURE),bpm-enable)
DEFINES := $(DEFINES)  -DPLATFORM_IMR -DLAPD_HA
else
DEFINES := $(DEFINES)  -UPLATFORM_IMR -DLAPD_HA 
endif

endif 

CFLAGS := $(CFLAGS)  -I$(ITS_ROOT)/common/include  \
			-I$(ITS_ROOT)/common/include/ADAX \
			-I$(VENDOR_ROOT)/IntelliNet/include  \
			-I$(ITS_ROOT)/TCAP/include \
			-I$(ITS_ROOT)/SCCP/include \
			-I$(ITS_ROOT)/BSSAP/proc/include \
			-I$(ITS_ROOT)/ISUP/include \
      -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
      -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include \
      -I${BPM_INC}  \
      -I${BPM_INC}/../Sys  \
      -I${BPM_INC}/../Ipc  \
      -I${BPM_INC}/../../Source/Sks/Inc\
      -I$(SKS_ROOT)/ISIL/Inc 

CXXFLAGS := $(CXXFLAGS)  -I ../Inc   \
		-I$(ITS_ROOT)/BSSAP/proc/include \
	  -I$(ITS_ROOT)/common/include \
		-I$(ITS_ROOT)/common/include/ADAX \
		-I$(ITS_ROOT)/SCCP/include \
		-I$(ITS_ROOT)/ISUP/include \
		-I$(VENDOR_ROOT)/IntelliNet/include  \
    -I$(ITS_ROOT)/TCAP/include -I$(ITS_ROOT)/SCCP/include \
    -I$(ITS_ROOT)/MTP3/include -I$(ITS_ROOT)/MTP2/include \
	  -I$(ITS_ROOT)/BSSAP/include \
    -I${BPM_INC}  \
    -I${BPM_INC}/../Sys  \
    -I${BPM_INC}/../Ipc  \
    -I${BPM_INC}/../../Source/Sks/Inc\
	  -I$(SKS_ROOT)/ISIL/Inc 


ifeq ($(PROTOCOL),ANSI)
LIBS :=$(LIBS)	-L$(ITS_ROOT)/BSSAP/lib \
	-L$(ITS_ROOT)/common/lib  \
	-L$(ITS_ROOT)/common/lib/ADAX  \
     	-L$(VENDOR_ROOT)/IntelliNet/lib \
	-L$(SKS_ROOT)/ISIL/Lib \
	-lANSI-VENDORD -lANSI-DRIVER++D -lANSI-DISPATCH++D -lANSI-DRIVERD \
        -lANSI-ENGINED  -lANSI-VFrameD -lANSI-ITS-REDUNDANCYD -lANSI-DSM-GCSD\
        -lANSI-BSSAPStackD  -lANSI-GCS-CLIENTD \
        -llog \
	-lrt 
else
LIBS :=$(LIBS)	-L$(ITS_ROOT)/BSSAP/lib \
	-L$(ITS_ROOT)/common/lib  \
	-L$(ITS_ROOT)/common/lib/ADAX  \
     	-L$(VENDOR_ROOT)/IntelliNet/lib \
	-L$(SKS_ROOT)/ISIL/Lib \
	-lCCITT-VENDORD -lCCITT-DRIVER++D -lCCITT-DISPATCH++D -lCCITT-DRIVERD \
        -lCCITT-ENGINED  -lCCITT-VFrameD -lCCITT-ITS-REDUNDANCYD -lCCITT-DSM-GCSD\
        -lCCITT-BSSAPStackD  -lCCITT-GCS-CLIENTD \
        -llog \
	-lrt 
endif




ifeq ($(PLATFORM),mvlppc)

BPMLIBS= 	-L${SYSEXE_ROOT}/Target/CommonLib/PP \
		-lplatformLib
endif 

#	-l$(PROTOCOL)-ADAXVendorD \ 
#        -lplatformLib   \
#       -lais   \
#	-L/usr/lib -lLiS 

#OBJS := AMscMain.o
OBJS := BscMain.o
#LIBOBJS := Abssap_ifcallbacks.o Abssapif_dispatcher.o  bssapif_socket.o \
           bssapif_trace.o bssapif_transport.o tcap_clientapi.o util.o \
	   tcap_clientimpl.o Coder.o GTT_ReadInfor.o GTT_Implem.o Decoder.o


LIBOBJS := bssapif_callbacks.o bssapif_dispatcher.o  bssapif_socket.o \
           bssapif_trace.o bssapif_transport.o tcap_clientapi.o util.o \
           tcap_clientimpl.o Coder.o GTT_ReadInfor.o GTT_Implem.o Decoder.o \
	   lapd_adaptation_layer.o lapdif_handler.o lapdif_cfg.o lapdif_file_read.o \
	   ISIL_SCMInf.o  Target.o lapdConfigData.o


ifeq ($(PROTOCOL),ANSI)
all: libANSI-BSCISIL_$(TYPE).so ANSI-BSCNWSTK_$(TYPE)-${VERSION_ISIL}
else
all: libCCITT-BSCISIL_$(TYPE).so CCITT-BSCNWSTK_$(TYPE)-${VERSION_ISIL}
endif 


ifeq ($(PLATFORM),mvlppc)

ifeq ($(PROTOCOL),ANSI)
ANSI-BSCNWSTK_$(TYPE)-${VERSION_ISIL}: $(OBJS)
	$(CXX) $(CXXFLAGS)  $(LDFLAGS) -o ANSI-BSCNWSTK_$(TYPE)-${VERSION_ISIL} $(OBJS)  \
 	$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)  $(LIBS) $(BPMLIBS) -lANSI-BSCISIL_$(TYPE)
	mv  ANSI-BSCNWSTK_$(TYPE)-${VERSION_ISIL} $(EXE_ROOT)/Target/Exec
else
CCITT-BSCNWSTK_$(TYPE)-${VERSION_ISIL}: $(OBJS)
	$(CXX) $(CXXFLAGS)  $(LDFLAGS) -o CCITT-BSCNWSTK_$(TYPE)-${VERSION_ISIL} $(OBJS)  \
 	$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)  $(LIBS) $(BPMLIBS) -lCCITT-BSCISIL_$(TYPE)
	mv  CCITT-BSCNWSTK_$(TYPE)-${VERSION_ISIL} $(EXE_ROOT)/Target/Exec

endif

else
BSCNWSTK_$(TYPE)-${VERSION_ISIL}: $(OBJS)
	$(CXX) $(CXXFLAGS)  $(LDFLAGS) -o BSCNWSTK_$(TYPE)-${VERSION_ISIL} $(OBJS)  \
 	$(SOCKLIBS) $(THREADLIBS) $(SYSLIBS)  $(LIBS) $(BPMLIBS) -lBSCISIL_$(TYPE)
	mv  BSCNWSTK_$(TYPE)-${VERSION_ISIL} $(EXE_ROOT)/Host/Exec
endif


ifeq ($(PLATFORM),mvlppc)

ifeq ($(PROTOCOL),ANSI)
libANSI-BSCISIL_$(TYPE).so: $(LIBOBJS)
	$(CXX)  $(CXXSHAREDARFLAGS)  ../Lib/libANSI-BSCISIL_$(TYPE).so $(LIBOBJS) $(LIBS) $(CXXSHAREDARFLAGSEND) 
	cp  ../Lib/libANSI-BSCISIL_$(TYPE).so  $(EXE_ROOT)/Target/CommonLib/
else
libCCITT-BSCISIL_$(TYPE).so: $(LIBOBJS)
	$(CXX)  $(CXXSHAREDARFLAGS)  ../Lib/libCCITT-BSCISIL_$(TYPE).so $(LIBOBJS) $(LIBS) $(CXXSHAREDARFLAGSEND) 
	cp  ../Lib/libCCITT-BSCISIL_$(TYPE).so  $(EXE_ROOT)/Target/CommonLib/

endif

else
libBSCISIL_$(TYPE).so: $(LIBOBJS)
	$(CXX)  $(CXXSHAREDARFLAGS)  ../Lib/libBSCISIL_$(TYPE).so $(LIBOBJS)  $(CXXSHAREDARFLAGSEND)  $(SYSEXE_ROOT)/Host/CommonLib/PP/lapdlib.o  $(LIBS)
	cp  ../Lib/libBSCISIL_$(TYPE).so  $(EXE_ROOT)/Host/CommonLib/
endif


clean:

ifeq ($(PROTOCOL),ANSI)
	$(RM) ../Lib/libANSI-BSCISIL_$(TYPE).so  *.o
else
	$(RM) ../Lib/libCCITT-BSCISIL_$(TYPE).so  *.o
endif 

ifeq ($(PLATFORM),mvlppc)

ifeq ($(PROTOCOL),ANSI)
	$(RM)  $(EXE_ROOT)/Target/Exec/ANSI-BSCNWSTK_$(TYPE)-${VERSION_ISIL} 
else
	$(RM)  $(EXE_ROOT)/Target/Exec/CCITT-BSCNWSTK_$(TYPE)-${VERSION_ISIL} 
endif 

else
	$(RM)  $(EXE_ROOT)/Host/Exec/BSCNWSTACKS_$(TYPE)-${VERSION_ISIL}  
endif

# get the rules
#
include $(ITS_ROOT)/config.rules

#include $(ITS_ROOT)/config.rules
