/************************************************************************
 * PegCounters.c
 *
 ************************************************************************/
#undef ANSI
#undef CCITT
#define CCITT 1

#include <PegCounters.h>

    int init_sw = 0;
    int maxCounters_CCITT = 0;
    int maxMiscCounters_CCITT = 0;
    int maxCounters_ANSI = 0;
    int maxMiscCounters_ANSI = 0;


    ITS_MUTEX    pegLock;
    /* Pointers to Counter Structures */
    theCOUNTERS *ptheCnt_CCITT = NULL, *ptheCnt_ANSI = NULL;
    miscCOUNTERS *pmiscCnt_CCITT = NULL, *pmiscCnt_ANSI = NULL;

    /* Indirect Group Index for Counters  -- I.E. COUNTERtbl[grpIndex[msg_id]] */
    unsigned char msgIndex_CCITT[256];
    unsigned char scmgIndex_CCITT[256];
    unsigned char cptIndex_CCITT[256];
    unsigned char reasonUABTIndex_CCITT[256]; 
    unsigned char reasonPABTIndex_CCITT[256];  
    unsigned char rejCodeResIndex_CCITT[256];
    unsigned char rejCodeGenIndex_CCITT[256];  
    unsigned char rejCodeInvIndex_CCITT[256];  
    unsigned char rejCodeErrIndex_CCITT[256]; 
    unsigned char miscIndex_CCITT[256]; 

    unsigned char msgIndex_ANSI[256];
    unsigned char scmgIndex_ANSI[256];
    unsigned char cptIndex_ANSI[256];
    unsigned char reasonABTIndex_ANSI[256]; 
    unsigned char rejCodeResIndex_ANSI[256];
    unsigned char rejCodeGenIndex_ANSI[256];  
    unsigned char rejCodeInvIndex_ANSI[256];  
    unsigned char rejCodeErrIndex_ANSI[256]; 
    unsigned char rejCodeTranIndex_ANSI[256]; 
    unsigned char rejCodeTransIndex_ANSI[256]; 
    unsigned char miscIndex_ANSI[256]; 


    unsigned char msgList_CCITT[] = 
    {
        PEG_TOTAL_TCAP_MSGS,            /*   Total All TCAP Messages */
        PEG_TOTAL_SCCP_MSGS,            /*   Total All SCCP Messages */
        PEG_TCAP_UNKNOWN_MSG,            /*   Unknown TCAP Message */
        PEG_SCCP_UNKNOWN_MSG,            /*   Unknown SCCP Message */

        TCAP_PT_TC_UNI_CCITT,            /*  (0x61U)  TC-Uni  */
        TCAP_PT_TC_BEGIN_CCITT,            /*  (0x62U)  TC-Begin  */
        TCAP_PT_TC_END_CCITT,            /*  (0x64U)  TC-End */
        TCAP_PT_TC_CONTINUE_CCITT,        /*  (0x65U)  TC-Continue */
        TCAP_PT_TC_P_ABORT_CCITT,        /*  (0x67U)  TC-P-Abort */
        TCAP_PT_TC_U_ABORT_CCITT,        /*  (0x68U)  TC-U-Abort */ 
        TCAP_PT_TC_NOTICE_CCITT,        /*  (0x69U)  TC-Notice */ 

        SCCP_MSG_CR,        /*  (0x01U)  "Connection Request" */
        SCCP_MSG_CC,        /*  (0x02U)  "Conection Confirm" */
        SCCP_MSG_CREF,        /*  (0x03U)  "Connection REFused" */
        SCCP_MSG_RLSD,        /*  (0x04U)  "ReLeaSed" */
        SCCP_MSG_RLC,        /*  (0x05U)  "ReLease Complete" */
        SCCP_MSG_DT1,        /*  (0x06U)  "DaTa form 1" */
        SCCP_MSG_DT2,        /*  (0x07U)  "DaTa form 2" */
        SCCP_MSG_AK,        /*  (0x08U)  "AcKnowledgement" */
        SCCP_MSG_UDT,        /*  (0x09U)  "Unit DaTa" */
        SCCP_MSG_UDTS,        /*  (0x0AU)  "Unit DaTa Service" */
        SCCP_MSG_ED,        /*  (0x0BU)  "Expedited Data" */
        SCCP_MSG_EA,        /*  (0x0CU)  "Expedited data Acknowledgement" */
        SCCP_MSG_RSR,        /*  (0x0DU)  "ReSet Request" */
        SCCP_MSG_RSC,        /*  (0x0EU)  "ReSet Confirmation" */
        SCCP_MSG_ERR,        /*  (0x0FU)  "ERRor" */
        SCCP_MSG_IT,        /*  (0x10U)  "Inactivity Test" */
        SCCP_MSG_XUDT,        /*  (0x11U)  "eXtended Unit DaTa" */
        SCCP_MSG_XUDTS,        /*  (0x12U)  "eXtended Unit DaTa Service" */
        SCCP_MSG_LUDT,        /*  (0x13U)  "Long Unitdata message" */
        SCCP_MSG_LUDTS,        /*  (0x14U)  "Long Unitdata Service Msg" */
        SCCP_MSG_NOTICE,    /*  (0xFFU)  "Notice from MTP3/to user" */
        0X00,                /*    End of table */
    };



    unsigned char msgList_ANSI[] = 
    {
        PEG_TOTAL_TCAP_MSGS,            /*   Total All TCAP Messages */
        PEG_TOTAL_SCCP_MSGS,            /*   Total All SCCP Messages */
        PEG_TCAP_UNKNOWN_MSG,            /*   Unknown TCAP Message */
        PEG_SCCP_UNKNOWN_MSG,            /*   Unknown SCCP Message */

        TCAP_PT_TC_UNI_ANSI,            /*  (0xE1U)  TC-Uni       */
        TCAP_PT_TC_QUERY_W_PERM_ANSI,   /*  (0xE2U)  TC-Query-WIP   */
        TCAP_PT_TC_QUERY_WO_PERM_ANSI,  /*  (0xE3U)  TC-Query-WOP  */
        TCAP_PT_TC_RESP_ANSI,            /*  (0xE4U)  TC-Resp       */
        TCAP_PT_TC_CONV_W_PERM_ANSI,    /*  (0xE5U)  TC-Conv-WIP  */
        TCAP_PT_TC_CONV_WO_PERM_ANSI,    /*  (0xE6U)  TC-Conv-WOP    */
        TCAP_PT_TC_ABORT_ANSI,            /*  (0xE6U)  TC-Conv-WOP  */
        TCAP_PT_TC_NOTICE_ANSI,            /*  (0xE8U)  TC-Notice     */


        SCCP_MSG_CR,        /*  (0x01U)  "Connection Request" */
        SCCP_MSG_CC,        /*  (0x02U)  "Conection Confirm" */
        SCCP_MSG_CREF,        /*  (0x03U)  "Connection REFused" */
        SCCP_MSG_RLSD,        /*  (0x04U)  "ReLeaSed" */
        SCCP_MSG_RLC,        /*  (0x05U)  "ReLease Complete" */
        SCCP_MSG_DT1,        /*  (0x06U)  "DaTa form 1" */
        SCCP_MSG_DT2,        /*  (0x07U)  "DaTa form 2" */
        SCCP_MSG_AK,        /*  (0x08U)  "AcKnowledgement" */
        SCCP_MSG_UDT,        /*  (0x09U)  "Unit DaTa" */
        SCCP_MSG_UDTS,        /*  (0x0AU)  "Unit DaTa Service" */
        SCCP_MSG_ED,        /*  (0x0BU)  "Expedited Data" */
        SCCP_MSG_EA,        /*  (0x0CU)  "Expedited data Acknowledgement" */
        SCCP_MSG_RSR,        /*  (0x0DU)  "ReSet Request" */
        SCCP_MSG_RSC,        /*  (0x0EU)  "ReSet Confirmation" */
        SCCP_MSG_ERR,        /*  (0x0FU)  "ERRor" */
        SCCP_MSG_IT,        /*  (0x10U)  "Inactivity Test" */
        SCCP_MSG_XUDT,        /*  (0x11U)  "eXtended Unit DaTa" */
        SCCP_MSG_XUDTS,        /*  (0x12U)  "eXtended Unit DaTa Service" */
/*        SCCP_MSG_LUDT,        //  (0x13U)  "Long Unitdata message" */
/*        SCCP_MSG_LUDTS,        //  (0x14U)  "Long Unitdata Service Msg" */
        SCCP_MSG_NOTICE,    /*  (0xFFU)  "Notice from MTP3/to user" */
        0X00,                /*    End of table */
    };

 
    unsigned char scmgList_CCITT[] = 
    {
        PEG_TOTAL_SCMG_MSGS,            /*    Total all SCMG Messages */
        PEG_SCMG_UNKNOWN_MSG,            /*  Unknown SCMG Message */
        SCCP_SCMG_SS_ALLOWED,            /*  (0x01U)  "SubSystem Allowed" */
        SCCP_SCMG_SS_PROHIBIT,            /*  (0x02U)  "SubSystem Prohibited" */
        SCCP_SCMG_SS_STATUS_TEST,        /*  (0x03U)  "SubSystem Status Test" */
        SCCP_SCMG_SS_OOS_REQ,            /*  (0x04U)  "SubSystem Out Of Service Request" */
        SCCP_SCMG_SS_OOS_GRANT,            /*  (0x05U)  "SubSystem Out Of Service Grant" */
        SCCP_SCMG_SS_BACKUP_ROUTE,        /*  (0xFDU)  "SubSystem Backup Routing" */
        SCCP_SCMG_SS_NORMAL_ROUTE,        /*  (0xFEU)  "SubSystem  Normal Routing" */
        SCCP_SCMG_SS_ROUTE_STATUS,        /*  (0xFFU)  "SubSystem Route Status"   */
        SCCP_SCMG_SS_UIS,                /*    (0xF0U)      User In Service     */
        SCCP_SCMG_SS_UOS,                /*    (0xF1U)   User Out of Service */
        SCCP_SCMG_SS_CONG,                /*    (0xF2U)      User Congested */
        0X00,                            /*    End of table */
    };

 
    unsigned char scmgList_ANSI[] = 
    {
        PEG_TOTAL_SCMG_MSGS,            /*    Total all SCMG Messages */
        PEG_SCMG_UNKNOWN_MSG,            /*  Unknown SCMG Message */
        SCCP_SCMG_SS_ALLOWED,            /*  (0x01U)  "SubSystem Allowed" */
        SCCP_SCMG_SS_PROHIBIT,            /*  (0x02U)  "SubSystem Prohibited" */
        SCCP_SCMG_SS_STATUS_TEST,        /*  (0x03U)  "SubSystem Status Test" */
        SCCP_SCMG_SS_OOS_REQ,            /*  (0x04U)  "SubSystem Out Of Service Request" */
        SCCP_SCMG_SS_OOS_GRANT,            /*  (0x05U)  "SubSystem Out Of Service Grant" */
        SCCP_SCMG_SS_BACKUP_ROUTE,        /*  (0xFDU)  "SubSystem Backup Routing" */
        SCCP_SCMG_SS_NORMAL_ROUTE,        /*  (0xFEU)  "SubSystem  Normal Routing" */
        SCCP_SCMG_SS_ROUTE_STATUS,        /*  (0xFFU)  "SubSystem Route Status"   */
        SCCP_SCMG_SS_UIS,                /*    (0xF0U)      User In Service     */
        SCCP_SCMG_SS_UOS,                /*    (0xF1U)   User Out of Service */
        SCCP_SCMG_SS_CONG,                /*    (0xF2U)      User Congested */
        0X00,                            /*    End of table */
    };




    /* Group Counter identifiers -- used as index to counter Index */
    unsigned char cptList_CCITT[] = 
    {
        PEG_TOTAL_CMPS,    /*    "Total All Components"    // place keeper for Total Components */

        TCAP_PT_TC_INVOKE_CCITT,       /* (0xA1U)  TC-Invoke  */
        TCAP_PT_TC_RESULT_L_CCITT,     /* (0xA2U)  TC-Result-L  */
        TCAP_PT_TC_U_ERROR_CCITT,      /* (0xA3U)  TC-U-Error  */
        TCAP_PT_TC_R_REJECT_CCITT,     /* (0xA4U)  TC-R-Reject  */
        TCAP_PT_TC_RESULT_NL_CCITT,    /* (0xA7U)  TC-Result-NL  */
        TCAP_PT_TC_L_CANCEL_CCITT,     /* (0xA8U)  TC-L-Cancel  */
        TCAP_PT_TC_U_CANCEL_CCITT,     /* (0xA9U)  TC-U-Cancel  */
        TCAP_PT_TC_L_REJECT_CCITT,     /* (0xAAU)  TC-L-Reject  */
        TCAP_PT_TC_U_REJECT_CCITT,     /* (0xABU)  TC-U-Reject  */
        TCAP_PT_TC_TIMER_RESET_CCITT,  /* (0xACU)  TC-Timer-Reset  */
        0X00,                           /*    End of table */
    };



    /* Group Counter identifiers -- used as index to counter Index */
    unsigned char cptList_ANSI[] = 
    {
        PEG_TOTAL_CMPS,    /*    "Total All Components"    // place keeper for Total Components */

        TCAP_PT_TC_INVOKE_ANSI,            /*  (0xE9U)  TC-Invoke-L    */
        TCAP_PT_TC_RESULT_L_ANSI,        /*  (0xEAU)  TC-Result-L   */
        TCAP_PT_TC_ERROR_ANSI,            /*  (0xEBU)  TC-Error      */
        TCAP_PT_TC_REJECT_ANSI,            /*  (0xECU)  TC-Reject      */
        TCAP_PT_TC_INVOKE_NL_ANSI,        /*  (0xEDU)  TC-Invoke-NL  */
        TCAP_PT_TC_RESULT_NL_ANSI,        /*  (0xEEU)  TC-Result-NL  */
        TCAP_PT_TC_CANCEL_ANSI,            /*  (0xEFU) this doesn't exist but several vendors use it */
        0X00,                            /*    End of table */
    };


/*
 * ANSI T1.114 abort causes
 */
    unsigned char reasonABTList_ANSI[] = 
    {
        TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI,            /* (0x00U) */
        TCAP_ABT_REASON_INCORRECT_TRANS_PORT_ANSI,        /* (0x01U) */
        TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI,    /* (0x02U) */
        TCAP_ABT_REASON_UNREC_TRANS_ID_ANSI,            /* (0x03U) */
        TCAP_ABT_REASON_PERM_TO_RELEASE_ANSI,            /* (0x04U) */
        TCAP_ABT_REASON_RES_UNAVAIL_ANSI,                /* (0x05U) */
        0XFF,                                /*    End of table */
    };


/*
 * TCAP_PN_ABORT_REASON values (White Book):
 */
    unsigned char reasonUABTList_CCITT[] = 
    {
        TCAP_UABT_AC_NOT_SUP_CCITT,      /* 1   /* Application context not supported */
        TCAP_UABT_DLG_REFUSED_CCITT,     /* 2   /* Dialogue refused */
        TCAP_UABT_USER_DEFINED_CCITT,    /* 3   /* User defined */
        0XFF,                                /*    End of table */
    };


/*
 * P-ABORT values
 */
    unsigned char reasonPABTList_CCITT[] = 
    {
        TCAP_ABT_REASON_UNREC_MSG_TYPE_CCITT,            /*(0x00U) */
        TCAP_ABT_REASON_UNREC_TRANS_ID_CCITT,            /*(0x01U) */
        TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_CCITT,   /*(0x02U) */
        TCAP_ABT_REASON_INCORRECT_TRANS_PORT_CCITT,      /*(0x03U) */
        TCAP_ABT_REASON_RES_UNAVAIL_CCITT,               /*(0x04U) */
        TCAP_PABT_ABNORMAL_DLG_CCITT,                    /* (126) */
        TCAP_PABT_NO_COMMON_DLG_CCITT,                    /* (127) */
        0XFF,                                            /*    End of table */
    };


/*
 * Q.773 reject types
 */
    unsigned char rejTypeList_CCITT[] = 
    {
        TCAP_PROB_GENERAL_CCITT,         /*(0x01U) */
        TCAP_PROB_INVOKE_CCITT,          /*(0x02U) */
        TCAP_PROB_RETURN_RES_CCITT,      /*(0x02U) */
        TCAP_PROB_RETURN_ERR_CCITT,      /*(0x03U) */
        0XFF,                            /*    End of table */
    };

    unsigned char rejTypeList_ANSI[] = 
    {
        TCAP_PROB_GENERAL_ANSI,          /*(0x00U) */
        TCAP_PROB_INVOKE_ANSI,           /*(0x01U) */
        TCAP_PROB_RETURN_RES_ANSI,       /*(0x03U) */
        TCAP_PROB_RETURN_ERR_ANSI,       /*(0x04U) */
        TCAP_PROB_TRANS_PORTION_ANSI,     /*(0x05U) */
        0XFF,                            /*    End of table */
    };


/*
 * Q.773 reject codes
 */
    unsigned char rejCodeGenList_CCITT[] = 
    {
        TCAP_PROB_SPEC_GEN_UNREC_COMP_CCITT,                /* (0x00U)  */
        TCAP_PROB_SPEC_GEN_MISTYPED_COMP_CCITT,             /* (0x01U) */
        TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_CCITT,         /* (0x02U) */
        0XFF,                                                /*    End of table */
    };
    
    unsigned char rejCodeGenList_ANSI[] = 
    {
        TCAP_PROB_SPEC_GEN_UNREC_COMP_ANSI,                 /* (0x01U)  */
        TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI,             /* (0x02U) */
        TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_ANSI,          /* (0x03U) */
        0XFF,                                                /* End of table */
    }; 

    unsigned char rejCodeInvList_CCITT[] = 
    {
        TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_CCITT,          /* (0x00U) */
        TCAP_PROB_SPEC_INV_UNREC_OP_CODE_CCITT,             /* (0x01U) */
        TCAP_PROB_SPEC_INV_MISTYPED_PARAM_CCITT,            /* (0x02U) */
        TCAP_PROB_SPEC_INV_RESOURCE_LIMIT_CCITT,            /* (0x03U) */
        TCAP_PROB_SPEC_INV_INITIATE_RELEASE_CCITT,          /* (0x04U) */
        TCAP_PROB_SPEC_INV_UNREC_LINKED_ID_CCITT,           /* (0x05U) */
        TCAP_PROB_SPEC_INV_UNEXPECTED_LINK_RESP_CCITT,      /* (0x06U) */
        TCAP_PROB_SPEC_INV_UNEXPECTED_LINKED_OP_CCITT,      /* (0x07U)*/
        0XFF,                                                /* End of table*/
    };


    unsigned char rejCodeInvList_ANSI[] = 
    {
        TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_ANSI,         /* (0x01U) */
        TCAP_PROB_SPEC_INV_UNREC_OP_CODE_ANSI,            /* (0x02U) */
        TCAP_PROB_SPEC_INV_INCORRECT_PARAM_ANSI,          /* (0x03U) */
        TCAP_PROB_SPEC_INV_INCORRECT_PARAM_ANSI,          /* (0x04U) */
        0XFF,                                             /* End of table*/
    };



    unsigned char rejCodeResList_CCITT[] = 
    {
        TCAP_PROB_SPEC_RES_UNREC_INVOKE_ID_CCITT,           /* (0x00U) */
        TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_CCITT,        /* (0x01U) */
        TCAP_PROB_SPEC_RES_MISTYPED_PARAM_CCITT,            /* (0x02U)*/
        0XFF,                                                /* End of table*/
    };



    unsigned char rejCodeResList_ANSI[] = 
    {
        TCAP_PROB_SPEC_RES_UNREC_COREL_ID_ANSI,             /* (0x01U) */
        TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_ANSI,         /* (0x02U) */
        TCAP_PROB_SPEC_RES_INCORRECT_PARAM_ANSI,            /* (0x03U)*/
        0XFF,                                                /* End of table*/
    };



    unsigned char rejCodeErrList_CCITT[] = 
    {
        TCAP_PROB_SPEC_ERR_UNREC_INVOKE_ID_CCITT,           /* (0x00U) */
        TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_CCITT,      /* (0x01U) */
        TCAP_PROB_SPEC_ERR_UNREC_ERROR_CCITT,               /* (0x02U) */
        TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_CCITT,          /* (0x03U) */
        TCAP_PROB_SPEC_ERR_MISTYPED_PARAM_CCITT,            /* (0x04U) */
        0XFF,                                                /* End of table*/
    };


    unsigned char rejCodeErrList_ANSI[] = 
    {
        TCAP_PROB_SPEC_ERR_UNREC_COREL_ID_ANSI,             /* (0x01U) */
        TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_ANSI,       /* (0x02U) */
        TCAP_PROB_SPEC_ERR_UNREC_ERROR_ANSI,                /* (0x03U) */
        TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_ANSI,           /* (0x04U) */
        TCAP_PROB_SPEC_ERR_INCORRECT_PARAM_ANSI,            /* (0x05U) */
        0XFF,                                                /* End of table*/
    };


    unsigned char rejCodeTransList_ANSI[] = 
    {
        TCAP_PROB_SPEC_TRANS_UNREC_PACK_TYPE_ANSI,          /* (0x01U) */
        TCAP_PROB_SPEC_TRANS_INCORRECT_TRANS_PORT_ANSI,     /* (0x02U) */
        TCAP_PROB_SPEC_TRANS_BADLY_STRUCT_TRANS_PORT_ANSI,  /* (0x03U) */
        TCAP_PROB_SPEC_TRANS_UNREC_TRANS_ID_ANSI,           /* (0x04U) */
        TCAP_PROB_SPEC_TRANS_PERM_TO_RELEASE_ANSI,          /* (0x05U) */
        TCAP_PROB_SPEC_TRANS_RES_UNAVAIL_ANSI,              /* (0x06U) */
        0XFF,                                                /* End of table*/
    };

    unsigned char miscList_CCITT[] = 
    {
        PEG_TCAP_ACTIVE_DIALOGUE,
        PEG_TCAP_ACTIVATED_DIALOGUE,
        PEG_TCAP_ACTIVE_TRANSACTIONS,
        PEG_TCAP_ACTIVATED_TRANSACTIONS,
        PEG_TCAP_INV_CLASS_1_SENT,
        PEG_TCAP_INV_CLASS_2_SENT,
        PEG_TCAP_INV_CLASS_3_SENT,
        PEG_TCAP_INV_CLASS_4_SENT,
        PEG_TCAP_INV_CONTEXT,
        PEG_TCAP_INV_CONTEXT_ACTIVE,
        PEG_TCAP_SEND_DIALOGUE,
        PEG_TCAP_RECEIVE_DIALOGUE,
        PEG_TCAP_CMP_SENT_FROM_APP, 
        PEG_TCAP_RECEIVE_COMPONENT,
        PEG_TCAP_RECEIVE_UDT,
        PEG_TCAP_RECEIVE_XUDT,
        PEG_TCAP_RECEIVE_UDTS,
        PEG_TCAP_RECEIVE_XUDTS,
        PEG_TCAP_RECEIVE_LUDT,
        PEG_TCAP_RECEIVE_LUDTS,
        PEG_TCAP_RECEIVE_INVALID_SCCP,
        PEG_TCAP_SEND_UDT,
        PEG_TCAP_SEND_XUDT,
        PEG_TCAP_SEND_UDTS,
        PEG_TCAP_SEND_XUDTS,
        PEG_TCAP_SEND_LUDT,
        PEG_TCAP_SEND_LUDTS,
        PEG_TCAP_PREARRANGED_END,
/*        PEG_TCAP_SCCP_CLASS_0_SENT, */
        PEG_TCAP_SCCP_CLASS_1_SENT,
        PEG_TCAP_SCCP_CLASS_0_RECEIVED,
        PEG_TCAP_SCCP_CLASS_1_RECEIVED,
        PEG_TCAP_SCCP_RET_ON_ERR_SENT,
        PEG_MTP3_MSG_PAUSE,
        PEG_MTP3_MSG_RESUME,
        PEG_MTP3_MSG_STATUS,
        PEG_SCCP_ACTIVE_CONNECTION,        
        PEG_SCCP_ACTIVATED_CONNECTION,    
        PEG_SCCP_MSG_FOR_PROHIBITED_SSN,                        
        PEG_SCCP_USER_INTERVENTION,        
        PEG_SCCP_USER_SEND_EVENT,        
        PEG_SCCP_USER_RECEIVE_EVENT,        
        PEG_SCCP_SEND_USER_OUT_OF_SERVICE,    
        PEG_SCCP_SEND_USER_IN_SERVICE,    
        PEG_SCCP_SEND_USER_CONGESTED,    
        PEG_SCCP_ROUTING_FAILURE,        
        PEG_SCCP_LBC_SS_IN_SERVICE,        
        PEG_SCCP_LBC_SS_OUT_OF_SERVICE,    
        PEG_SCCP_LBC_SS_CONGESTED,        
        PEG_SCCP_LBC_SS_ALLOWED,            
        PEG_SCCP_LBC_SS_PROHIBITED,        
        PEG_SCCP_LBC_USER_IN_SERVICE,    
        PEG_SCCP_LBC_USER_OUT_OF_SERVICE,    
        PEG_SCCP_GTT_REQUEST,
        PEG_SCCP_GTT_SUCCESS,
        PEG_SCCP_GTT_FAILURE,
        PEG_SCCP_PCLASS_0_SENT,
        PEG_SCCP_PCLASS_1_SENT,
        PEG_SCCP_PCLASS_2_SENT,
        PEG_SCCP_PCLASS_3_SENT,
        PEG_SCCP_PCLASS_0_RECEIVED,
        PEG_SCCP_PCLASS_1_RECEIVED,
        PEG_SCCP_PCLASS_2_RECEIVED,
        PEG_SCCP_PCLASS_3_RECEIVED,
        PEG_SCCP_RET_ON_ERR_SENT,
        PEG_SCCP_RET_ON_ERR_RECEIVED,
        PEG_MISC_UNUSED,
        0,                                /* End of table*/
    };


    unsigned char miscList_ANSI[] = 
    {
        PEG_TCAP_ACTIVE_DIALOGUE,
        PEG_TCAP_ACTIVATED_DIALOGUE,
        PEG_TCAP_ACTIVE_TRANSACTIONS,
        PEG_TCAP_ACTIVATED_TRANSACTIONS,
        PEG_TCAP_INV_CLASS_1_SENT,
        PEG_TCAP_INV_CLASS_2_SENT,
        PEG_TCAP_INV_CLASS_3_SENT,
        PEG_TCAP_INV_CLASS_4_SENT,
        PEG_TCAP_INV_CONTEXT,
        PEG_TCAP_INV_CONTEXT_ACTIVE,
        PEG_TCAP_SEND_DIALOGUE,
        PEG_TCAP_RECEIVE_DIALOGUE,
        PEG_TCAP_CMP_SENT_FROM_APP, 
        PEG_TCAP_RECEIVE_COMPONENT,
        PEG_TCAP_RECEIVE_UDT,
        PEG_TCAP_RECEIVE_XUDT,
        PEG_TCAP_RECEIVE_UDTS,
        PEG_TCAP_RECEIVE_XUDTS,
        PEG_TCAP_RECEIVE_INVALID_SCCP,
        PEG_TCAP_SEND_UDT,
        PEG_TCAP_SEND_XUDT,
        PEG_TCAP_SEND_UDTS,
        PEG_TCAP_SEND_XUDTS,
/*        PEG_TCAP_PREARRANGED_END,*/
/*        PEG_TCAP_SCCP_CLASS_0_SENT,*/
/*        PEG_TCAP_SCCP_CLASS_1_SENT,*/
/*        PEG_TCAP_SCCP_CLASS_0_RECEIVED,*/
/*        PEG_TCAP_SCCP_CLASS_1_RECEIVED,*/
/*        PEG_TCAP_SCCP_RET_ON_ERR_SENT,*/
        PEG_MTP3_MSG_PAUSE,
        PEG_MTP3_MSG_RESUME,
        PEG_MTP3_MSG_STATUS,
        PEG_SCCP_ACTIVE_CONNECTION,        
        PEG_SCCP_ACTIVATED_CONNECTION,    
        PEG_SCCP_MSG_FOR_PROHIBITED_SSN,                        
        PEG_SCCP_USER_INTERVENTION,        
        PEG_SCCP_USER_SEND_EVENT,        
        PEG_SCCP_USER_RECEIVE_EVENT,        
        PEG_SCCP_SEND_USER_OUT_OF_SERVICE,    
        PEG_SCCP_SEND_USER_IN_SERVICE,    
        PEG_SCCP_SEND_USER_CONGESTED,    
        PEG_SCCP_ROUTING_FAILURE,        
        PEG_SCCP_LBC_SS_IN_SERVICE,        
        PEG_SCCP_LBC_SS_OUT_OF_SERVICE,    
        PEG_SCCP_LBC_SS_CONGESTED,        
        PEG_SCCP_LBC_SS_ALLOWED,            
        PEG_SCCP_LBC_SS_PROHIBITED,        
        PEG_SCCP_LBC_USER_IN_SERVICE,    
        PEG_SCCP_LBC_USER_OUT_OF_SERVICE,    
        PEG_SCCP_GTT_REQUEST,
        PEG_SCCP_GTT_SUCCESS,
        PEG_SCCP_GTT_FAILURE,
        PEG_SCCP_PCLASS_0_SENT,
        PEG_SCCP_PCLASS_1_SENT,
        PEG_SCCP_PCLASS_2_SENT,
        PEG_SCCP_PCLASS_3_SENT,
        PEG_SCCP_PCLASS_0_RECEIVED,
        PEG_SCCP_PCLASS_1_RECEIVED,
        PEG_SCCP_PCLASS_2_RECEIVED,
        PEG_SCCP_PCLASS_3_RECEIVED,
        PEG_SCCP_RET_ON_ERR_SENT,
        PEG_SCCP_RET_ON_ERR_RECEIVED,
        PEG_MISC_UNUSED,
        0,                                /* End of table*/
    };



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int  
PegCountInit()
{

    int i, i2;
    /* If First Time*/
    if (init_sw == 0)
    {
        /* Start off with Clean Slate */
        maxCounters_CCITT = 0;
        maxMiscCounters_CCITT = 0;
        ptheCnt_CCITT = NULL;
        pmiscCnt_CCITT = NULL;

        maxCounters_ANSI = 0;
        maxMiscCounters_ANSI = 0;
        ptheCnt_ANSI = NULL;
        pmiscCnt_ANSI = NULL;

        if ((PegCreateLock()) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        } /* if */

        
        for (i=0; i<256; i++) 
        {
            /* Set msgIndexes into theCOUNTERS to zero*/
            msgIndex_CCITT[i] = 0;
            msgIndex_ANSI[i] = 0;

            /* Set scmgIndexes into theCOUNTERS to zero*/
            scmgIndex_CCITT[i] = 0;
            scmgIndex_ANSI[i] = 0;

            /* Set cptIndexes into theCOUNTERS to zero*/
            cptIndex_CCITT[i] = 0;
            cptIndex_ANSI[i] = 0;

            /* Set reasonABTIndex into theCOUNTERS to hi-values*/
            reasonABTIndex_ANSI[i] = 0xFF;

            /* Set reasonUABTIndex into theCOUNTERS to hi-values*/
            reasonUABTIndex_CCITT[i] = 0xFF;

            /* Set reasonPABTIndex into theCOUNTERS to hi-values*/
            reasonPABTIndex_CCITT[i] = 0xFF;

            /* Set rejCodeResIndex into theCOUNTERS to hi-values*/
            rejCodeResIndex_CCITT[i] = 0xFF;
            rejCodeResIndex_ANSI[i] = 0xFF;

            /* Set rejCodeGenIndex into theCOUNTERS to hi-values*/
            rejCodeGenIndex_CCITT[i] = 0xFF;
            rejCodeGenIndex_ANSI[i] = 0xFF;

            /* Set rejCodeInvIndex into theCOUNTERS to hi-values*/
            rejCodeInvIndex_CCITT[i] = 0xFF;
            rejCodeInvIndex_ANSI[i] = 0xFF;

            /* Set rejCodeErrIndex into theCOUNTERS to hi-values*/
            rejCodeErrIndex_CCITT[i] = 0xFF;
            rejCodeErrIndex_ANSI[i] = 0xFF;

            /* Set rejCodeTransIndex into theCOUNTERS to hi-values*/
            rejCodeTransIndex_ANSI[i] = 0xFF;
            
            /* Set miscIndex into miscCOUNTERS to zero*/
            miscIndex_CCITT[i] = 0;
            miscIndex_ANSI[i] = 0;
        } /* for */

        /* Loop through msgListS */
        for (i=0, i2=1; i < sizeof(msgList_CCITT); i++) 
        {
            /* If valid msgType then use as msgIndex to msgIndex & sequentially set the*/
            /* msgIndex to theCOUNTERS  -- Later we use msgType to find the associated*/
            /* theCOUNTERS struct and its counters*/
            msgIndex_CCITT[msgList_CCITT[i]] = i2++;
        } /* for */
        
        /* Loop through msgList*/
        for (i=0, i2=1; i < sizeof(msgList_ANSI); i++) 
        {
            /* If valid msgType then use as msgIndex to msgIndex & sequentially set the*/
            /* msgIndex to theCOUNTERS  -- Later we use msgType to find the associated*/
            /* theCOUNTERS struct and its counters*/
            msgIndex_ANSI[msgList_ANSI[i]] = i2++;
        } /* for */
        

        /* Loop through scmgList*/
        for (i=0; i < sizeof(scmgList_CCITT); i++) 
        {
            /* If valid scmgType then use as scmgIndex to scmgIndex & sequentially set the*/
            /* scmgIndex to theCOUNTERS  -- Later we use scmgType to find the associated*/
            /* theCOUNTERS struct and its counters*/
            scmgIndex_CCITT[scmgList_CCITT[i]] = i2++;
        } /* for */


        /* Loop through scmgList*/
        for (i=0; i < sizeof(scmgList_ANSI); i++) 
        {
            /* If valid scmgType then use as scmgIndex to scmgIndex & sequentially set the*/
            /* scmgIndex to theCOUNTERS  -- Later we use scmgType to find the associated */
            /* theCOUNTERS struct and its counters*/
            scmgIndex_ANSI[scmgList_ANSI[i]] = i2++;
        } /* for */


        /* Loop through cptList*/
        for (i=0; i < sizeof(cptList_CCITT); i++) 
        {
            /* If valid cptType then use as cptIndex to cptIndex & sequentially set the*/
            /* cptIndex to theCOUNTERS  -- Later we use cptType to find the associated*/
            /* theCOUNTERS struct and its counters*/
            cptIndex_CCITT[cptList_CCITT[i]] = i2++;
        } /* for */


        /* Loop through cptList*/
        for (i=0; i < sizeof(cptList_ANSI); i++) 
        {
            /* If valid cptType then use as cptIndex to cptIndex & sequentially set the*/
            /* cptIndex to theCOUNTERS  -- Later we use cptType to find the associated*/
            /* theCOUNTERS struct and its counters*/
            cptIndex_ANSI[cptList_ANSI[i]] = i2++;
        } /* for */

        /* Loop through reasonABTList*/
        for (i=0; i < sizeof(reasonABTList_ANSI); i++) 
        {
            /* If valid reasonABTType then use as reasonABTIndex to reasonABTIndex & */
            /* sequentially set the reasonABTIndex to theCOUNTERS  -- Later we */
            /*  use reason to find the associated theCOUNTERS struct */
            /*  and its counters*/
            reasonABTIndex_ANSI[reasonABTList_ANSI[i]] = i2++;
        } /* for */
        maxCounters_ANSI = i2 - 1;

        /* Loop through reasonUABTList*/
        for (i=0; i < sizeof(reasonUABTList_CCITT); i++) 
        {
            /* If valid reasonUABTType then use as reasonUABTIndex to reasonUABTIndex & */
            /* sequentially set the reasonUABTIndex to theCOUNTERS  -- Later we */
            /*  use reason to find the associated theCOUNTERS struct */
            /*  and its counters*/
            reasonUABTIndex_CCITT[reasonUABTList_CCITT[i]] = i2++;
        } /* for */


        /* Loop through reasonPABTList*/
        for (i=0; i < sizeof(reasonPABTList_CCITT); i++) 
        {
            /* If valid reasonPABTType then use as reasonPABTIndex to reasonPABTIndex & */
            /* sequentially set the reasonPABTIndex to theCOUNTERS  -- Later we */
            /* use reason to find the associated theCOUNTERS struct */
            /* and its counters*/
            reasonPABTIndex_CCITT[reasonPABTList_CCITT[i]] = i2++;
        } /* for */

        /* Loop through rejCodeGenList*/
        for (i=0; i < sizeof(rejCodeGenList_CCITT); i++) 
        {
            /* If valid rejCodeGenList then use as rejCodeGenIndex to rejCodeGenIndex & */
            /*  sequentially set the rejCodeGenIndex to theCOUNTERS  -- Later we */
            /*  use type & code to find the associated theCOUNTERS struct */
            /*  and its counters*/
            rejCodeGenIndex_CCITT[rejCodeGenList_CCITT[i]] = i2++;
        } /* for */



        /* Loop through rejCodeResList*/
        for (i=0; i < sizeof(rejCodeResList_CCITT); i++) 
        {
            /* If valid rejCodeResList then use as rejCodeResIndex to rejCodeResIndex & */
            /* sequentially set the rejCodeResIndex to theCOUNTERS  -- Later we */
            /* use type & code to find the associated theCOUNTERS struct */
            /* and its counters if (rejCodeResList[i] != 0xFF) */
            rejCodeResIndex_CCITT[rejCodeResList_CCITT[i]] = i2++;
        } /* for */


        /* Loop through rejCodeInvList*/
        for (i=0; i < sizeof(rejCodeInvList_CCITT); i++) 
        {
            /* If valid rejCodeInvList then use as rejCodeInvIndex to rejCodeInvIndex & */
            /* sequentially set the rejCodeInvIndex to theCOUNTERS  -- Later we */
            /* use type & code to find the associated theCOUNTERS struct */
            /* and its counters if (rejCodeInvList[i] != 0xFF) */
            rejCodeInvIndex_CCITT[rejCodeInvList_CCITT[i]] = i2++;
        } /* for */


        /* Loop through rejCodeErrList
        for (i=0; i < sizeof(rejCodeErrList_CCITT); i++) */
        {
            /* If valid rejCodeErrList then use as rejCodeErrIndex to rejCodeErrIndex & */
            /* sequentially set the rejCodeErrIndex to theCOUNTERS  -- Later we */
            /* use type & code to find the associated theCOUNTERS struct */
            /* and its counters if (rejCodeErrList[i] != 0xFF) */
            rejCodeErrIndex_CCITT[rejCodeErrList_CCITT[i]] = i2++;
        } /* for */
        maxCounters_CCITT = i2 - 1;


        /* Loop through miscList*/
        for (i=0, i2=1; i < sizeof(miscList_CCITT); i++) 
        {
            /* If valid miscList then use as miscIndex to miscIndex & sequentially set the*/
            /* miscIndex to miscCOUNTERS  -- Later we use miscType to find the associated*/
            /* miscCOUNTERS struct and its counters*/
            miscIndex_CCITT[miscList_CCITT[i]] = i2++;
        } /* for */
        maxMiscCounters_CCITT = i2 - 1;


        /* Loop through miscList*/
        for (i=0, i2=1; i < sizeof(miscList_ANSI); i++) 
        {
            /* If valid miscList then use as miscIndex to miscIndex & sequentially set the*/
            /* miscIndex to miscCOUNTERS  -- Later we use miscType to find the associated*/
            /* miscCOUNTERS struct and its counters*/
            miscIndex_ANSI[miscList_ANSI[i]] = i2++;
        } /* for */
        maxMiscCounters_ANSI = i2 - 1;



        /* ooh-no we need to break the table up into two tables*/
        ITS_C_ASSERT(maxCounters_CCITT <= 256);
        ITS_C_ASSERT(maxCounters_ANSI <= 256);

        /* Get memory for counter struct*/
        ptheCnt_CCITT = (theCOUNTERS *) ITS_Calloc(maxCounters_CCITT+1,sizeof(theCOUNTERS));
        ptheCnt_ANSI = (theCOUNTERS *) ITS_Calloc(maxCounters_ANSI+1,sizeof(theCOUNTERS));

        /* ooh-no we need to break the table up into two tables*/
        ITS_C_ASSERT(maxMiscCounters_CCITT <= 256);
        ITS_C_ASSERT(maxMiscCounters_ANSI <= 256);

        /* Get memory for counter struct*/
        pmiscCnt_CCITT = (miscCOUNTERS *) ITS_Calloc(maxMiscCounters_CCITT+1,sizeof(miscCOUNTERS));
        pmiscCnt_ANSI = (miscCOUNTERS *) ITS_Calloc(maxMiscCounters_ANSI+1,sizeof(miscCOUNTERS));

        /* Set switch so we won't do this again*/
        init_sw = 1;

    } /* if */

    return (ITS_SUCCESS);
} /* PegCountInit */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void 
PegCountTerm()
{
    if (init_sw = 0) 
    {
        return;
    } /* if */
    ITS_Free (ptheCnt_CCITT);        /* free up the memory obtained for the counters*/
    ITS_Free (ptheCnt_ANSI);        /* free up the memory obtained for the counters*/

    ITS_Free (pmiscCnt_CCITT);    /* free up the memory obtained for misc counters*/
    ITS_Free (pmiscCnt_ANSI);    /* free up the memory obtained for misc counters*/

    PegDeleteLock();

    init_sw = 0;            /* reset switch*/

} /* PegCountTerm */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int 
PegAddTCAPMsgEvent(ITS_EVENT *pev, ITS_OCTET cntIndex, ITS_INT protocol)
{
    TCAP_DLG *pdlg = 0;
    ITS_OCTET msgType = 0;
    ITS_USHORT tmp = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        /* Event data has TCAP_DLG embedded -- on odd boundry -- so avoid pointer*/
        /* don't do pdlg = (TCAP_DLG *) &pev->data[3]; msgType = (ITS_OCTET) pev-pType;*/
        /* do the following*/
        memcpy(&tmp, &pev->data[1 + sizeof(ITS_CTXT)], sizeof(ITS_USHORT));
        if (protocol == PEG_CCITT)
        {
            msgType = (ITS_OCTET) tmp;            /* TCAP Message Type*/
            i = msgIndex_CCITT[msgType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */
    
            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_CCITT+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            i = msgIndex_CCITT[PEG_TOTAL_TCAP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            msgType = (ITS_OCTET) tmp;            /* TCAP Message Type*/
            i = msgIndex_ANSI[msgType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */
    
            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_ANSI+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            i = msgIndex_ANSI[PEG_TOTAL_TCAP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* else - ANSI */
    } /* else */
    return(ITS_SUCCESS);                    

}    /* PegAddTCAPMsgEvent */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int 
PegAddTCAPMsgDlg(TCAP_DLG *pdlg, ITS_OCTET cntIndex, ITS_INT protocol)
{
    ITS_OCTET msgType = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        msgType = (ITS_OCTET) pdlg->ptype;    /* TCAP message Type*/
        if (protocol == PEG_CCITT)
        {
            i = msgIndex_CCITT[msgType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_CCITT+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            i = msgIndex_CCITT[PEG_TOTAL_TCAP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            i = msgIndex_ANSI[msgType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_ANSI+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            i = msgIndex_ANSI[PEG_TOTAL_TCAP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* else - ANSI */
    } /* else */
    return(ITS_SUCCESS);
}    /* PegAddTCAPMsgDlg */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int 
PegAddTCAPMsgType(ITS_OCTET msgType, ITS_OCTET cntIndex, ITS_INT protocol)
{

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        if (protocol == PEG_CCITT)
        {
            i = msgIndex_CCITT[msgType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/
            (ptheCnt_CCITT+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr msg counter*/

            i = msgIndex_CCITT[PEG_TOTAL_TCAP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/
            PegReleaseLock();                    /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            i = msgIndex_ANSI[msgType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/
            (ptheCnt_ANSI+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr msg counter*/

            i = msgIndex_ANSI[PEG_TOTAL_TCAP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/
            PegReleaseLock();                    /* Always Release the lock*/
        } /* else - ANSI */

    } /* else */
    return(ITS_SUCCESS);

}    /* PegAddTCAPMsgType */


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int 
PegAddSCMGType(ITS_OCTET scmgType, ITS_OCTET cntIndex, ITS_INT protocol)
{

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        if (protocol == PEG_CCITT)
        {
            i = scmgIndex_CCITT[scmgType];            /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if scmgIndex 0 then no scmg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_CCITT+i)->cntName = scmgType;    /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr scmg counter*/

            i = scmgIndex_CCITT[PEG_TOTAL_SCMG_MSGS];    /* Simple indirect Index*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/
    
            PegReleaseLock();                    /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            i = scmgIndex_ANSI[scmgType];            /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if scmgIndex 0 then no scmg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_ANSI+i)->cntName = scmgType;    /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr scmg counter*/

            i = scmgIndex_ANSI[PEG_TOTAL_SCMG_MSGS];    /* Simple indirect Index*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/
    
            PegReleaseLock();                    /* Always Release the lock*/
        } /* else - ANSI */
    } /* else */
    return(ITS_SUCCESS);

}    /* PegAddSCMGType */


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int 
PegAddSCCPMsgEvent(ITS_EVENT *pev, ITS_OCTET cntIndex, ITS_INT protocol)
{
    ITS_OCTET msgType = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        msgType = SCCP_MSG_TYPE(pev);        /* SCCP Message Type*/
        if (protocol == PEG_CCITT)
        {
            i = msgIndex_CCITT[msgType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_CCITT+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr msg counter*/

            i = msgIndex_CCITT[PEG_TOTAL_SCCP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            i = msgIndex_ANSI[msgType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_ANSI+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr msg counter*/

            i = msgIndex_ANSI[PEG_TOTAL_SCCP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* else - ANSI */
    } /* else */
    return(ITS_SUCCESS);                

}    /* PegAddSCCPMsgEvent */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int 
PegAddSCCPMsgType(ITS_OCTET msgType, ITS_OCTET cntIndex, ITS_INT protocol)
{

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        if (protocol == PEG_CCITT)
        {
            i = msgIndex_CCITT[msgType];                /* Simple indirect Index*/
            if (i == 0)
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_CCITT+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr msg counter*/

            i = msgIndex_CCITT[PEG_TOTAL_SCCP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            i = msgIndex_ANSI[msgType];                /* Simple indirect Index*/
            if (i == 0)
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_ANSI+i)->cntName = msgType;        /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr msg counter*/

            i = msgIndex_ANSI[PEG_TOTAL_SCCP_MSGS];    /* Simple indirect Index*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* Total count all Messages*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* else - ANSI */
    } /* else */
    return(ITS_SUCCESS);

}    /* PegAddSCCPMsgType */


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

int 
PegAddTCAPAbortReasonEvent(ITS_EVENT *pev, ITS_OCTET cntIndex, ITS_INT protocol)

{
    TCAP_DLG dlg, *pdlg = &dlg;
    ITS_OCTET reason = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;

        /* Event data has TCAP_DLG embedded -- on odd boundry -- so avoid pointer*/
        /* don't do pdlg = (TCAP_DLG *) &pev->data[3]; */
        /* do the following*/
        memcpy(&dlg, &pev->data[3], sizeof(dlg));
        reason = (ITS_OCTET) pdlg->u.abort.abort_reason; /* Get Reason for Abort*/
        if (protocol == PEG_CCITT)
        {
            if (dlg.ptype == TCAP_PT_TC_U_ABORT_CCITT)
            {
                i = reasonUABTIndex_CCITT[reason];        /* Simple indirect Index*/
            } /* if */
            else
            {
                i = reasonPABTIndex_CCITT[reason];        /* Simple indirect Index*/
            } /* else */

            if (i == 0xFF) 
            {
                return(ITS_EINVALIDARGS);        /* if Index 0xFF then no reason of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_CCITT+i)->cntName = reason;        /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            i = reasonABTIndex_ANSI[reason];        /* Simple indirect Index*/

            if (i == 0xFF) 
            {
                return(ITS_EINVALIDARGS);        /* if Index 0xFF then no reason of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_ANSI+i)->cntName = reason;        /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* else - ANSI */
    } /* else */
    return(ITS_SUCCESS);

}    /* PegAddTCAPAbortReasonEvent */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

int 
PegAddTCAPAbortReasonDlg(TCAP_DLG *pdlg, ITS_OCTET cntIndex)

{

    ITS_OCTET reason = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        reason = (ITS_OCTET) pdlg->u.abort.abort_reason; /* Get Reason for Abort*/
        i = reasonABTIndex_ANSI[reason];        /* Simple indirect Index*/
        if (i == 0xFF) 
        {
            return(ITS_EINVALIDARGS);        /* if Index 0xFF then no reason of that type*/
        } /* if */
    
        PegGetLock();                        /* Lock table -- could lock each counter*/

        (ptheCnt_ANSI+i)->cntName = reason;        /* Set type -- only really need do once*/
        (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

        PegReleaseLock();                    /* Always Release the lock*/
    } /* else */
    return(ITS_SUCCESS);                    

}    /* PegAddTCAPAbortReasonDlg */




/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

int 
PegAddTCAPUAbortReasonEvent(ITS_EVENT *pev, ITS_OCTET cntIndex)

{
    TCAP_DLG dlg, *pdlg = &dlg;
    ITS_OCTET reason = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;

        /* Event data has TCAP_DLG embedded -- on odd boundry -- so avoid pointer*/
        /* don't do pdlg = (TCAP_DLG *) &pev->data[3]; */
        /* do the following*/
        memcpy(&dlg, &pev->data[3], sizeof(dlg));
        reason = (ITS_OCTET) pdlg->u.abort.abort_reason; /* Get Reason for Abort*/
        i = reasonUABTIndex_CCITT[reason];        /* Simple indirect Index*/
        if (i == 0xFF) 
        {
            return(ITS_EINVALIDARGS);        /* if Index 0xFF then no reason of that type*/
        } /* if */

        PegGetLock();                        /* Lock table -- could lock each counter*/

        (ptheCnt_CCITT+i)->cntName = reason;        /* Set type -- only really need do once*/
        (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

        PegReleaseLock();                    /* Always Release the lock*/
    } /* else */
    return(ITS_SUCCESS);

}    /* PegAddTCAPUAbortReasonEvent */


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

int 
PegAddTCAPUAbortReasonDlg(TCAP_DLG *pdlg, ITS_OCTET cntIndex)

{

    ITS_OCTET reason = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        reason = (ITS_OCTET) pdlg->u.abort.abort_reason; /* Get Reason for Abort*/
        i = reasonUABTIndex_CCITT[reason];        /* Simple indirect Index*/
        if (i == 0xFF) 
        {
            return(ITS_EINVALIDARGS);        /* if Index 0xFF then no reason of that type*/
        } /* if */

        PegGetLock();                        /* Lock table -- could lock each counter*/

        (ptheCnt_CCITT+i)->cntName = reason;        /* Set type -- only really need do once*/
        (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

        PegReleaseLock();                    /* Always Release the lock*/
    } /* else */
    return(ITS_SUCCESS);                    

}    /* PegAddTCAPUAbortReasonDlg */


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

int 
PegAddTCAPPAbortReasonEvent(ITS_EVENT *pev, ITS_OCTET cntIndex)

{
    TCAP_DLG dlg, *pdlg = &dlg;
    ITS_OCTET reason = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready */
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        /* Event data has TCAP_DLG embedded -- on odd boundry -- so avoid pointer*/
        /* don't do pdlg = (TCAP_DLG *) &pev->data[3]; */
        /* do the following*/
        memcpy(&dlg, &pev->data[3], sizeof(dlg));
        reason = (ITS_OCTET) pdlg->u.abort.abort_reason; /* Get Reason for Abort*/
        i = reasonPABTIndex_CCITT[reason];        /* Simple indirect Index*/
        if (i == 0xFF) 
        {
            return(ITS_EINVALIDARGS);        /* if Index 0xFF then no reason of that type*/
        } /* if */

        PegGetLock();                        /* Lock table -- could lock each counter*/

        (ptheCnt_CCITT+i)->cntName = reason;        /* Set type -- only really need do once*/
        (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

        PegReleaseLock();                    /* Always Release the lock*/
    } /* else */
    return(ITS_SUCCESS);                    

}    /* PegAddTCAPPAbortReasonEvent */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

int 
PegAddTCAPPAbortReasonDlg(TCAP_DLG *pdlg, ITS_OCTET cntIndex)
{
    ITS_OCTET reason = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        reason = (ITS_OCTET) pdlg->u.abort.abort_reason; /* Get Reason for Abort*/
        i = reasonPABTIndex_CCITT[reason];        /* Simple indirect Index*/
        if (i == 0xFF) 
        {
            return(ITS_EINVALIDARGS);        /* if Index 0xFF then no reason of that type*/
        } /* if */

        PegGetLock();                        /* Lock table -- could lock each counter*/

        (ptheCnt_CCITT+i)->cntName = reason;        /* Set type -- only really need do once*/
        (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

        PegReleaseLock();                    /* Always Release the lock*/
    } /* else */
    return(ITS_SUCCESS);                    

}    /* PegAddTCAPPAbortReasonDlg */




/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

int
PegAddTCAPRejectProblemCpt(TCAP_CPT *pcpt, ITS_OCTET cntIndex, ITS_INT protocol)
{
    ITS_OCTET type = 0;
    ITS_OCTET code = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                    /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        type = (!LOCAL_REJECT_MARKER) & pcpt->u.reject.problem.data[0];    /* Prob Type*/
        code = pcpt->u.reject.problem.data[2];    /* Get Error Code*/
        if (protocol == PEG_CCITT)
        {
            switch (type)
            {
                case (TCAP_PROB_GENERAL_CCITT):
                    i = rejCodeGenIndex_CCITT[code];            /* Simple indirect Index*/
                    break;
                case (TCAP_PROB_INVOKE_CCITT):
                    i = rejCodeInvIndex_CCITT[code];            /* Simple indirect Index*/
                    break;
                case (TCAP_PROB_RETURN_RES_CCITT):
                    i = rejCodeResIndex_CCITT[code];            /* Simple indirect Index*/
                    break;
                case (TCAP_PROB_RETURN_ERR_CCITT):
                    i = rejCodeErrIndex_CCITT[code];            /* Simple indirect Index*/
                    break;
                default:
                    return(ITS_EINVALIDARGS);    
            }; /* switch */

            if (i == 0xFF) 
            {
                return(ITS_EINVALIDARGS);        /* if Index 0xFF then no code of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_CCITT+i)->cntName = code;        /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            switch (type)
            {
                case (TCAP_PROB_GENERAL_ANSI):
                    i = rejCodeGenIndex_ANSI[code];            /* Simple indirect Index*/
                    break;
                case (TCAP_PROB_INVOKE_ANSI):
                    i = rejCodeInvIndex_ANSI[code];            /* Simple indirect Index*/
                    break;
                case (TCAP_PROB_RETURN_RES_ANSI):
                    i = rejCodeResIndex_ANSI[code];            /* Simple indirect Index*/
                    break;
                case (TCAP_PROB_RETURN_ERR_ANSI):
                    i = rejCodeErrIndex_ANSI[code];            /* Simple indirect Index*/
                    break;
                case (TCAP_PROB_TRANS_PORTION_ANSI):
                    i = rejCodeTransIndex_ANSI[code];            /* Simple indirect Index*/
                    break;
                default:
                    return(ITS_EINVALIDARGS);    
            }; /* switch */

            if (i == 0xFF) 
            {
                return(ITS_EINVALIDARGS);        /* if Index 0xFF then no code of that type*/
            } /* if */

            PegGetLock();                        /* Lock table -- could lock each counter*/

            (ptheCnt_ANSI+i)->cntName = code;        /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            PegReleaseLock();                    /* Always Release the lock*/
        } /* else - ANSI */
    } /* else */
    return(ITS_SUCCESS);                    


} /* PegAddTCAPRejectProblemCpt */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
PegAddTCAPCptEvent(ITS_EVENT *pev, ITS_OCTET cntIndex, ITS_INT protocol)
{
    TCAP_CPT cpt, *pcpt = &cpt;
    ITS_OCTET cptType = 0;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );
        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        /* Event data has TCAP_CPT embedded -- on odd boundry -- so avoid pointer*/
        /* don't do pcpt = (TCAP_CPT *) &pev->data[3]; */
        /* do the following*/
        memcpy(&cpt, &pev->data[3], sizeof(cpt));
        cptType = (ITS_OCTET) pcpt->ptype;
        if (protocol == PEG_CCITT)
        {
            i = cptIndex_CCITT[cptType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */
            PegGetLock();                        /* Lock table -- could lock each counter*/
            (ptheCnt_CCITT+i)->cntName = cptType;        /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            i = cptIndex_CCITT[PEG_TOTAL_CMPS];        /* Simple indirect Index*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;        /* Total count all Components*/
            PegReleaseLock();                    /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            i = cptIndex_ANSI[cptType];                /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);        /* if msgIndex 0 then no msg of that type*/
            } /* if */
            PegGetLock();                        /* Lock table -- could lock each counter*/
            (ptheCnt_ANSI+i)->cntName = cptType;        /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* incr the counter*/

            i = cptIndex_ANSI[PEG_TOTAL_CMPS];        /* Simple indirect Index*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;        /* Total count all Components*/
            PegReleaseLock();                    /* Always Release the lock*/
        } /* else - ANSI */
    } /* else */
    return(ITS_SUCCESS);

}    /* PegAddTCAPCptEvent */


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int 
PegAddTCAPCptType(ITS_OCTET cptType, ITS_OCTET cntIndex, ITS_INT protocol)
{

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);            /* PegCounters Not Ready*/
    } /* if */

    /* Insure counter name valid for Messages counters*/
    if (cntIndex > (ITS_OCTET) 2 ) 
    {
        /* Invalid Counter Name (Really it is an Index)*/
        ITS_C_ASSERT(cntIndex > (ITS_OCTET) 2 );

        return (ITS_EINVALIDARGS);
    } /* if */
    else
    {
        int i;
        if (protocol == PEG_CCITT)
        {
            i = cptIndex_CCITT[cptType];            /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
            } /* if */
            PegGetLock();                    /* Lock table -- could lock each counter*/
            (ptheCnt_CCITT+i)->cntName = cptType;    /* Set type -- only really need do once*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;    /* incr the counter*/

            i = cptIndex_CCITT[PEG_TOTAL_CMPS];    /* Simple indirect Index*/
            (ptheCnt_CCITT+i)->u.s.cnts[cntIndex]++;    /* Total count all Components*/
            PegReleaseLock();                /* Always Release the lock*/
        } /* if - CCITT */
        else
        {
            i = cptIndex_ANSI[cptType];            /* Simple indirect Index*/
            if (i == 0) 
            {
                return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
            } /* if */
            PegGetLock();                    /* Lock table -- could lock each counter*/
            (ptheCnt_ANSI+i)->cntName = cptType;    /* Set type -- only really need do once*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;    /* incr the counter*/

            i = cptIndex_ANSI[PEG_TOTAL_CMPS];    /* Simple indirect Index*/
            (ptheCnt_ANSI+i)->u.s.cnts[cntIndex]++;    /* Total count all Components*/
            PegReleaseLock();                /* Always Release the lock*/
        } /* else - ANSI */
    } /* else */
    return(ITS_SUCCESS);

}    /* PegAddTCAPCptType */


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
    
int 
PegAddMiscType(ITS_OCTET miscType, ITS_INT protocol)
{
    int i;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);            /* PegCounters Not Ready*/
    } /* if */

    if (protocol == PEG_CCITT)
    {
        i = miscIndex_CCITT[miscType];                /* Simple indirect Index*/
        if (i == 0) 
        {
            return(ITS_EINVALIDARGS);        /* if miscIndex 0 then no msg of that type*/
        } /* if */

        PegGetLock();                        /* Lock table -- could lock each counter*/

        (pmiscCnt_CCITT+i)->cntName = miscType;    /* Set type -- only really need do once*/
        (pmiscCnt_CCITT+i)->cnt++;            /* increment byte counter*/

        PegReleaseLock();                    /* Always Release the lock*/
    } /* if - CCITT */
    else
    {
        i = miscIndex_ANSI[miscType];                /* Simple indirect Index*/
        if (i == 0) 
        {
            return(ITS_EINVALIDARGS);        /* if miscIndex 0 then no msg of that type*/
        } /* if */

        PegGetLock();                        /* Lock table -- could lock each counter*/

        (pmiscCnt_ANSI+i)->cntName = miscType;    /* Set type -- only really need do once*/
        (pmiscCnt_ANSI+i)->cnt++;            /* increment byte counter*/

        PegReleaseLock();                    /* Always Release the lock*/
    } /* else - ANSI */

    return(ITS_SUCCESS);

} /* PegAddMiscType */
    



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
    
int 
PegSubMiscType(ITS_OCTET miscType, ITS_INT protocol)
{
    int i;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);            /* PegCounters Not Ready*/
    } /* if */

    if (protocol == PEG_CCITT)
    {
        i = miscIndex_CCITT[miscType];                /* Simple indirect Index*/
        if (i == 0) 
        {
            return(ITS_EINVALIDARGS);        /* if miscIndex 0 then no msg of that type*/
        } /* if */

        PegGetLock();                        /* Lock table -- could lock each counter*/

        /* This should not happen, but lets not look bad if it does*/
        /* Actually it could on overflow -- or if locks not used on counters*/
        if ((pmiscCnt_CCITT+i)->cnt != 0)
        {
            (pmiscCnt_CCITT+i)->cnt--;            /* decrement byte counter*/
        } /* if */

        PegReleaseLock();                    /* Always Release the lock*/
    } /* if - CCITT */
    else
    {
        i = miscIndex_ANSI[miscType];                /* Simple indirect Index*/
        if (i == 0) 
        {
            return(ITS_EINVALIDARGS);        /* if miscIndex 0 then no msg of that type*/
        } /* if */

        PegGetLock();                        /* Lock table -- could lock each counter*/

        /* This should not happen, but lets not look bad if it does*/
        /* Actually it could on overflow -- or if locks not used on counters*/
        if ((pmiscCnt_ANSI+i)->cnt != 0)
        {
            (pmiscCnt_ANSI+i)->cnt--;            /* decrement byte counter*/
        } /* if */

        PegReleaseLock();                    /* Always Release the lock*/
    } /* else - ANSI */

    return(ITS_SUCCESS);

} /* PegSubMiscType */
    


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI int    
PegGetCounter(ITS_OCTET group, ITS_OCTET code, void *pCOUNTERS, ITS_INT protocol)
{
    int i;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);                /* PegCounters Not Ready*/
    } /* if */

    if (protocol == PEG_CCITT)
    {
        switch (group)
        {
            case (msgGroup):
                i = msgIndex_CCITT[code];                /* Simple indirect Index*/
                if (i == 0) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (scmgGroup):
                i = scmgIndex_CCITT[code];            /* Simple indirect Index*/
                if (i == 0) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (cptGroup):
                i = cptIndex_CCITT[code];                /* Simple indirect Index*/
                if (i == 0) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (reasonUABTGroup):
                i = reasonUABTIndex_CCITT[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (reasonPABTGroup):
                i = reasonPABTIndex_CCITT[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (rejCodeResGroup):
                i = rejCodeResIndex_CCITT[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (rejCodeGenGroup):
                i = rejCodeGenIndex_CCITT[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (rejCodeInvGroup):
                i = rejCodeInvIndex_CCITT[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (rejCodeErrGroup):
                i = rejCodeErrIndex_CCITT[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (miscGroup):
                i = miscIndex_CCITT[code];            /* Simple indirect Index*/
                if (i == 0) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */

                /* Copy counters to user area*/
                memcpy(pCOUNTERS, (pmiscCnt_CCITT+i), sizeof(miscCOUNTERS));
    
                /* has counter ever been incremented?*/
                if ((pmiscCnt_CCITT+i)->cntName == (unsigned char) 0)
                {
                    /* If not add counter name to struct returned*/
                    ((miscCOUNTERS *)pCOUNTERS)->cntName = code;
                } /* if */

                if ((((miscCOUNTERS *)pCOUNTERS))->cntName == PEG_TCAP_RECEIVE_COMPONENT)
                {
                    /* Tcap_Receive_Component Routine is entered twice per component */
                    /*  distorting the count so divide by 2*/
                    (((miscCOUNTERS *)pCOUNTERS))->cnt = (((miscCOUNTERS *)pCOUNTERS))->cnt /2;
                } /* if */

                return(ITS_SUCCESS);    /* Return Successful*/
        
                break;
            default:
                return(ITS_EINVALIDARGS);    
        }; /* switch */

        /* Copy counters to user area*/
        memcpy(pCOUNTERS, (ptheCnt_CCITT+i), sizeof(theCOUNTERS));


        /* has counter ever been incremented?*/
        if ((ptheCnt_CCITT+i)->cntName == (unsigned char) 0)
        {
            /* If not add counter name to struct returned*/
            (((theCOUNTERS *)pCOUNTERS))->cntName = code;
        } /* if */
    } /* if - CCITT */
    else
    {
        switch (group)
        {
            case (msgGroup):
                i = msgIndex_ANSI[code];                /* Simple indirect Index*/
                if (i == 0) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (scmgGroup):
                i = scmgIndex_ANSI[code];            /* Simple indirect Index*/
                if (i == 0) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (cptGroup):
                i = cptIndex_ANSI[code];                /* Simple indirect Index*/
                if (i == 0) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (reasonUABTGroup):
                i = reasonABTIndex_ANSI[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (rejCodeResGroup):
                i = rejCodeResIndex_ANSI[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (rejCodeGenGroup):
                i = rejCodeGenIndex_ANSI[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (rejCodeInvGroup):
                i = rejCodeInvIndex_ANSI[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (rejCodeErrGroup):
                i = rejCodeErrIndex_ANSI[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (rejCodeTransGroup):
                i = rejCodeTransIndex_ANSI[code];        /* Simple indirect Index*/
                if (i == 0xFF) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */
                break;
            case (miscGroup):
                i = miscIndex_ANSI[code];            /* Simple indirect Index*/
                if (i == 0) 
                {
                    return(ITS_EINVALIDARGS);    /* if msgIndex 0 then no msg of that type*/
                } /* if */

                /* Copy counters to user area*/
                memcpy(pCOUNTERS, (pmiscCnt_ANSI+i), sizeof(miscCOUNTERS));
    
                /* has counter ever been incremented?*/
                if ((pmiscCnt_ANSI+i)->cntName == (unsigned char) 0)
                {
                    /* If not add counter name to struct returned*/
                    ((miscCOUNTERS *)pCOUNTERS)->cntName = code;
                } /* if */

                if ((((miscCOUNTERS *)pCOUNTERS))->cntName == PEG_TCAP_RECEIVE_COMPONENT)
                {
                    /* Tcap_Receive_Component Routine is entered twice per component */
                    /*  distorting the count so divide by 2*/
                    (((miscCOUNTERS *)pCOUNTERS))->cnt = (((miscCOUNTERS *)pCOUNTERS))->cnt /2;
                } /* if */

                return(ITS_SUCCESS);    /* Return Successful*/
        
                break;
            default:
                return(ITS_EINVALIDARGS);    
        }; /* switch */

        /* Copy counters to user area*/
        memcpy(pCOUNTERS, (ptheCnt_ANSI+i), sizeof(theCOUNTERS));


        /* has counter ever been incremented?*/
        if ((ptheCnt_ANSI+i)->cntName == (unsigned char) 0)
        {
            /* If not add counter name to struct returned*/
            (((theCOUNTERS *)pCOUNTERS))->cntName = code;
        } /* if */
    } /* else - ANSI */

    return(ITS_SUCCESS);    /* Return Successful*/

} /* PegGetCounter */


    
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Returns the Next counter in the Group containing data
 *
 *  Input Parameters:
 *      Group ID, Index starting with 0 & updated to next by this function,
 *            and a pointer to memory to copy the Counter or Counter set
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      Counter or Counter set
 *
 *  Return Value:
 *      ITS_EINVALIDARGS return if error -- Index is set to PEG_EOF if EOF
 *        Output counters valid only when return == Success & Index != EOF
 ****************************************************************************/
ITSDLLAPI int    
PegGetNextCounter(ITS_OCTET group, int *pIndex, void *pCOUNTERS, ITS_INT protocol)
{
    int i, mi;

    if (init_sw = 0) 
    {
        return(ITS_EBADSTATE);            /* PegCounters Not Ready*/
    } /* if */

    if (protocol == PEG_CCITT)
    {
        for (;;)
        {
            if (*pIndex < 0 || *pIndex >255) 
            {
                if (*pIndex == 256)
                {
                    *pIndex = PEG_EOF;        
                    return(ITS_SUCCESS);
                } /* if */
                return (ITS_EINVALIDARGS);
            } /* if */

            /* Each group index (I.E. msgIndex) has a default value of either Low-Values (0)*/
            /*    or Hi-Values (0xFF).  The default value is used in places where there is no*/
            /*    corresponding counter.  Each valid counter id is itself an index into the group*/
            /*    index.  The value contained at that location is in turn an index into the */
            /*    table of counters.  In the case of msgIndex the message tag is use as an index*/
            /*    to msgIndex. For the cptIndex the component tab is use....*/
            switch (group)
            {
                case (msgGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; msgIndex_CCITT[i] == 0; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */ 
                    } /* for */
                    mi = msgIndex_CCITT[i];
                    break;
                case (scmgGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; scmgIndex_CCITT[i] == 0; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = scmgIndex_CCITT[i];
                    break;

                case (cptGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; cptIndex_CCITT[i] == 0; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = cptIndex_CCITT[i];
                    break;
                case (reasonABTGroup):
                    *pIndex = PEG_EOF;        
                    return(ITS_SUCCESS);
                    break;
                case (reasonUABTGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; reasonUABTIndex_CCITT[i] == 0xFF; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = reasonUABTIndex_CCITT[i];
                    break;
                case (reasonPABTGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; reasonPABTIndex_CCITT[i] == 0xFF; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = reasonPABTIndex_CCITT[i];
                    break;
                case (rejCodeResGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; rejCodeResIndex_CCITT[i] == 0xFF; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = rejCodeResIndex_CCITT[i];
                    break;
                case (rejCodeGenGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; rejCodeGenIndex_CCITT[i] == 0xFF; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = rejCodeGenIndex_CCITT[i];
                    break;
                case (rejCodeInvGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; rejCodeInvIndex_CCITT[i] == 0xFF; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = rejCodeInvIndex_CCITT[i];
                    break;
                case (rejCodeErrGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; rejCodeErrIndex_CCITT[i] == 0xFF ; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = rejCodeErrIndex_CCITT[i];
                    break;
                case (rejCodeTransGroup):
                    *pIndex = PEG_EOF;        
                    return(ITS_SUCCESS);
                    break;
                case (miscGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; miscIndex_CCITT[i] == 0 ; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = miscIndex_CCITT[i];
                    break;
            default:
                return(ITS_EINVALIDARGS);    
            }; /* switch */

        
            if (group == miscGroup)
            {
                /* has counter ever been incremented?*/
                if ((pmiscCnt_CCITT+mi)->cntName != (unsigned char) 0)
                {
                    break;
                } /* if */
            } /* if */
            else
            {
                /* has counter ever been incremented?*/
                if ((ptheCnt_CCITT+mi)->cntName != (unsigned char) 0)
                {
                    break;
                } /* if */
            } /* else */
    
            /* this is not the one we want so start over again with next one*/
            (*pIndex) = i + 1;    /* incr the Index*/
        }; /* for ever */



        if (group == miscGroup)
        {
            /* Copy counters to user area*/
            memcpy(pCOUNTERS, (pmiscCnt_CCITT+mi), sizeof(miscCOUNTERS));

            if ((((miscCOUNTERS *)pCOUNTERS))->cntName == PEG_TCAP_RECEIVE_COMPONENT)
            {
                /* Tcap_Receive_Component Routine is entered twice per component  */
                /*  distorting the count so divide by 2*/
                (((miscCOUNTERS *)pCOUNTERS))->cnt = (((miscCOUNTERS *)pCOUNTERS))->cnt  /2;
            } /* if */
    
        } /* if */
        else
        {
            /* Copy counters to user area*/
            memcpy(pCOUNTERS, (ptheCnt_CCITT+mi), sizeof(theCOUNTERS));
        } /* else */
    } /* if - CCITT */
    else
    {
        for (;;)
        {
            if (*pIndex < 0 || *pIndex >255) 
            {
                if (*pIndex == 256)
                {
                    *pIndex = PEG_EOF;        
                    return(ITS_SUCCESS);
                } /* if */
                return (ITS_EINVALIDARGS);
            } /* if */

            /* Each group index (I.E. msgIndex) has a default value of either Low-Values (0)*/
            /*    or Hi-Values (0xFF).  The default value is used in places where there is no*/
            /*    corresponding counter.  Each valid counter id is itself an index into the group*/
            /*    index.  The value contained at that location is in turn an index into the */
            /*    table of counters.  In the case of msgIndex the message tag is use as an index*/
            /*    to msgIndex. For the cptIndex the component tab is use....*/
            switch (group)
            {
                case (msgGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; msgIndex_ANSI[i] == 0; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */ 
                    } /* for */
                    mi = msgIndex_ANSI[i];
                    break;
                case (scmgGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; scmgIndex_ANSI[i] == 0; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = scmgIndex_ANSI[i];
                    break;

                case (cptGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; cptIndex_ANSI[i] == 0; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = cptIndex_ANSI[i];
                    break;
                case (reasonABTGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; reasonABTIndex_ANSI[i] == 0xFF; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = reasonABTIndex_ANSI[i];
                    break;
                case (reasonUABTGroup):
                    *pIndex = PEG_EOF;        
                    return(ITS_SUCCESS);
                    break;
                case (reasonPABTGroup):
                    *pIndex = PEG_EOF;        
                    return(ITS_SUCCESS);
                    break;
                case (rejCodeResGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; rejCodeResIndex_ANSI[i] == 0xFF; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = rejCodeResIndex_ANSI[i];
                    break;
                case (rejCodeGenGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; rejCodeGenIndex_ANSI[i] == 0xFF; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = rejCodeGenIndex_ANSI[i];
                    break;
                case (rejCodeInvGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; rejCodeInvIndex_ANSI[i] == 0xFF; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = rejCodeInvIndex_ANSI[i];
                    break;
                case (rejCodeErrGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; rejCodeErrIndex_ANSI[i] == 0xFF ; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = rejCodeErrIndex_ANSI[i];
                    break;
                case (rejCodeTransGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; rejCodeTransIndex_ANSI[i] == 0xFF ; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = rejCodeTransIndex_ANSI[i];
                    break;
                case (miscGroup):
                    /* Look for a real counter in this group*/
                    for (i = *pIndex; miscIndex_ANSI[i] == 0 ; i++)
                    {
                        if (i >= 255) 
                        {
                            *pIndex = PEG_EOF;        
                            return(ITS_SUCCESS);
                        } /* if */
                    } /* for */
                    mi = miscIndex_ANSI[i];
                    break;
            default:
                return(ITS_EINVALIDARGS);    
            }; /* switch */

        
            if (group == miscGroup)
            {
                /* has counter ever been incremented?*/
                if ((pmiscCnt_ANSI+mi)->cntName != (unsigned char) 0)
                {
                    break;
                } /* if */
            } /* if */
            else
            {
                /* has counter ever been incremented?*/
                if ((ptheCnt_ANSI+mi)->cntName != (unsigned char) 0)
                {
                    break;
                } /* if */
            } /* else */
    
            /* this is not the one we want so start over again with next one*/
            (*pIndex) = i + 1;    /* incr the Index*/
        }; /* for ever */



        if (group == miscGroup)
        {
            /* Copy counters to user area*/
            memcpy(pCOUNTERS, (pmiscCnt_ANSI+mi), sizeof(miscCOUNTERS));

            if ((((miscCOUNTERS *)pCOUNTERS))->cntName == PEG_TCAP_RECEIVE_COMPONENT)
            {
                /* Tcap_Receive_Component Routine is entered twice per component  */
                /*  distorting the count so divide by 2*/
                (((miscCOUNTERS *)pCOUNTERS))->cnt = (((miscCOUNTERS *)pCOUNTERS))->cnt  /2;
            } /* if */
    
        } /* if */
        else
        {
            /* Copy counters to user area */
            memcpy(pCOUNTERS, (ptheCnt_ANSI+mi), sizeof(theCOUNTERS));
        } /* else */
    } /* else - ANSI */
    
    (*pIndex) = i + 1;                /* incr the Index*/

    return(ITS_SUCCESS);            /* Return Successful*/

} /* PegGetNextCounter */





/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void 
PegCountersReset()
{
    int i, i2;

    if (init_sw = 0) 
    {
        return;                            /* PegCounters Not Ready*/
    } /* if */

        PegGetLock();                    /* Lock counters while we reset them*/

    /* Loop through the theCOUNTERS struct*/
    for(i = 0; i < (maxCounters_CCITT+1); i++) 
    {
        (ptheCnt_CCITT+i)->cntName = 0;        /* Set Name to zero*/
        /* Loop through indivdual counters*/
        for (i2 = 0; i2 < 3; i2++) 
        {
            (ptheCnt_CCITT+i)->u.s.cnts[i2] = 0;    /* Set those counters to zero*/
        } /* for - counters with in struct */
    } /* for - counter structures */


    /* Loop through the theCOUNTERS struct */
    for(i = 0; i < (maxCounters_ANSI+1); i++) 
    {
        (ptheCnt_ANSI+i)->cntName = 0;        /* Set Name to zero*/
        /* Loop through indivdual counters*/
        for (i2 = 0; i2 < 3; i2++) 
        {
            (ptheCnt_ANSI+i)->u.s.cnts[i2] = 0;    /* Set those counters to zero*/
        } /* for - counters with in struct */
    } /* for - counter structures */


    /* Loop through the miscCOUNTERS struct*/
    for(i = 0; i < (maxMiscCounters_CCITT+1); i++) 
    {
        (pmiscCnt_CCITT+i)->cntName = 0;        /* Set Name to zero*/
        (pmiscCnt_CCITT+i)->cnt = 0;            /* Set counter to zero*/
    } /* for */

    /* Loop through the miscCOUNTERS struct*/
    for(i = 0; i < (maxMiscCounters_ANSI+1); i++) 
    {
        (pmiscCnt_ANSI+i)->cntName = 0;        /* Set Name to zero*/
        (pmiscCnt_ANSI+i)->cnt = 0;            /* Set counter to zero*/
    } /* for */


    PegReleaseLock();                /* Always Release Lock */
}    /* PegCountersReset */








