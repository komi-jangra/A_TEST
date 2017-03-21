
ifeq ($(BSC_FLAG),1)
	RELEASEFLAG=DBSC
endif
ifeq ($(MSC_FLAG),1)
	RELEASEFLAG=DMSC
endif
	ifeq ($a,1)
		AR= ar
		CC= gcc
		DEFINES= -Dread_config_file -DMTP3_EVENT_REPORTING  -DSCCP_INCLUDE_CO_SERVICE \
                        -DITU_STACK             -DANSI_PROTO              \
                        -DLINUX                 -DPLATFORM_IMR            \
                        -DLOGGER_IMR            -D__C_APPL	\
                        -DCSSF_SMS              -$(RELEASEFLAG) 
	endif
	ifeq ($a,2)
		AR= ar
		CC= gcc
		DEFINES=-Dread_config_file -DMTP3_EVENT_REPORTING  -DSCCP_INCLUDE_CO_SERVICE   -DHLRSCM \
                        -DITU_STACK             -DANSI_PROTO              \
                        -DLINUX                 -UPLATFORM_IMR            \
                        -DLOGGER_IMR            -D__C_APPL\
                        -DCSSF_SMS              -$(RELEASEFLAG) 
	endif
	ifeq ($a,0)
		AR= ppc_85xx-ar  -rdynamic
		CC= ppc_85xx-gcc -rdynamic
		DEFINES= -Dread_config_file -DMTP3_EVENT_REPORTING  -DSCCP_INCLUDE_CO_SERVICE \
                        -DITU_STACK             -DANSI_PROTO              \
                        -DLINUX                 -DPLATFORM_IMR            \
                        -DLOGGER_IMR            -D__C_APPL\
                        -DCSSF_SMS              -$(RELEASEFLAG)           \
                        -DTARGET_SETUP          -DLAPD_HA         
                         
	endif
ifeq ($(MSC_FLAG),1)
	CAP_PATH=${REL_PATH}/MSC-Development/Source/SKS/Src/GSMSSF
endif

	RM=rm -f
	MAKE=make
	CFLAGS= -Wall -g
	ARFLAGS=-r


ifeq ($(MSC_FLAG),1)
INCLUDES= \
        -I${SCM_ROOT}/Inc \
        -I${BPM_INC} \
        -I${BPM_INC}/../SYS \
        -I${BPM_INC}/../DBS \
        -I${BPM_INC}/../IPC \
        -I${BPM_INC}/../OAM \
        -I${BPM_INC}/../HLS \
        -I${BPM_INC}/../../Source/SKS/Inc \
	-I${BPM_INC}/../SKS/CAP \
        -I${SCM_INC} 
endif
ifeq ($(BSC_FLAG),1)
INCLUDES= \
        -I${SCM_ROOT}/Inc \
        -I${SCM_ROOT}/Inc/Sys \
        -I${BPM_INC} \
        -I${BPM_INC}/../Sys \
        -I${BPM_INC}/../Sks/SCM \
        -I${BPM_INC}/../Dbs \
        -I${BPM_INC}/../Ipc \
        -I${BPM_INC}/../Oam \
        -I${BPM_INC}/../../Source/Sks/Inc 
endif
