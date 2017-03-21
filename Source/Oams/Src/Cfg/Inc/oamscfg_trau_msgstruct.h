typedef struct
{
#ifndef TSM_MOD
     SysHdr         sysHdr;
#endif
     tHdr           hdr;
     message_hdr_t  trauHdr;
     I_U8           response;
     I_U8           max_num_tone;
     I_U8           max_num_ann;
     I_U8           max_num_DTMF_sender;
     I_U8           max_num_DTMF_receiver;
     I_U8           max_num_conference;
     I_U8           max_num_trau;
     I_U8           active_Channels0;
     I_U8           active_Channels1;
     I_U8           boot_test_res;
} __attribute__((packed)) DSmmMgsBootMsg;


typedef struct
{
#ifndef TSM_MOD
         SysHdr         sysHdr;
#endif
         tHdr           hdr;
         message_hdr_t  trauHdr;
         I_U8           law;
         I_U8           hbDuration;
} __attribute__((packed)) DSmmDspInitReqMsg;

typedef struct
{
#ifndef TSM_MOD
        SysHdr         sysHdr;
#endif
        tHdr           hdr;
        message_hdr_t trauHdr;
        I_U8           response;
} __attribute__((packed)) DSmmDspInitResMsg;

typedef struct
{
#ifndef TSM_MOD
        SysHdr         sysHdr;
#endif
        tHdr           hdr;
        message_hdr_t  trauHdr;
} __attribute__((packed)) DSmmTrauStartReqMsg;

typedef struct
{
#ifndef TSM_MOD
        SysHdr         sysHdr;
#endif
        tHdr           hdr;
        message_hdr_t  trauHdr;
        I_U8           response;
} __attribute__((packed)) DSmmTrauStartResMsg;






