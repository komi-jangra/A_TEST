#include <stdio.h>
#include <itu/sccp.h>
#include <its.h>
#include <its_object.h>
#include <its_ss7_trans.h>
#include <its_app.h>
#include <sua.h>


int ISUP_SetVariant_CCITT() { return 0; }
int CCITT_CallTable;
int CCITT_ISUP_Variant() { return 0; }
int ISUP_TlvEventToL3Message_CCITT() { return 0; }
int ISUP_L3MessageToTlvEvent_CCITT() { return 0; }
int ComputeMSize() {return 0;}
int SCTPTRAN_RegisterCodec() {return 0;}
int SCTPTRAN_DeregisterCodec() {return 0;}

#define BUILD_UDT             1
#define BUILD_XUDT            2
#define BUILD_UDTS            3
#define BUILD_XUDTS           4
#define BUILD_SSA             5
#define BUILD_CR              6
#define BUILD_CC              7
#define BUILD_CREF            8
#define BUILD_DT1             9
#define BUILD_RSLD           10
#define BUILD_RLC            11
#define BUILD_LUDT           12
#define BUILD_LUDTS          13
#define BUILD_CLDT           14
#define BUILD_ASPUP          15
#define BUILD_ASPDN          16
#define TEST_EXIT            99

#define VALID_CHOICE(x)     ( x >= 1 && x <= 16 || x == 99 )

#define OPC         1
#define DPC         2
#define SSN         5

static unsigned char GT_Digits[5] = {0x01, 0x23, 0x45, 0x67, 0x89};
static unsigned char DATA[10] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                 0x08, 0x09};
static unsigned char DST_LOCAL_REF[3] = {0x00, 0x00, 0x01};
static unsigned char SRC_LOCAL_REF[3] = {0x00, 0x00, 0x02};
static unsigned char SSA[5] = {0x01, 0x05, 0x0A, 0x0B, 0x00};
static unsigned char SSP[5] = {0x02, 0x05, 0x0A, 0x0B, 0x00};
static unsigned char SST[5] = {0x03, 0x05, 0x0A, 0x0B, 0x00};
static unsigned char ALI[3] = {0x0A, 0x0B, 0x0C};
static unsigned char INFO_STR[5] = {0x01, 0x02, 0x03, 0x04, 0x05};

static int 
TEST_PrintCommand()
{
    printf("\n\n\t**** IntelliNet Technologies, Inc. ****\n");
    printf("\t\tBasic SUA Test program\n\n");

    printf("To build a message from the following list, \n");
    printf("\ttype in the corresponding number:-\n\n");

    printf("    %d) Build SCCP UDT message. \n", BUILD_UDT);
    printf("    %d) Build SCCP XUDT message. \n", BUILD_XUDT);
    printf("    %d) Build SCCP UDTS message. \n", BUILD_UDTS);
    printf("    %d) Build SCCP XUDTS message.\n", BUILD_XUDTS);
    printf("    %d) Build SCMG SSA message.\n", BUILD_SSA);
    printf("    %d) Build SCCP CR message .\n", BUILD_CR);
    printf("    %d) Build SCCP CC message.\n", BUILD_CC);
    printf("    %d) Build SCCP CREF message \n", BUILD_CREF);
    printf("    %d) Build SCCP DT1 message.\n", BUILD_DT1);
    printf("    %d) Build SCCP RSLD message.\n", BUILD_RSLD);
    printf("    %d) Build SCCP RLC message.\n", BUILD_RLC);
    printf("    %d) Build SCCP LUDT message.\n", BUILD_LUDT);
    printf("    %d) Build SCCP LUDTS message.\n", BUILD_LUDTS);
    printf("    %d) Build SUA CLDT message.\n", BUILD_CLDT);
    printf("    %d) Build SUA ASPUP message.\n", BUILD_ASPUP);
    printf("    %d) Build SUA ASPDN message.\n", BUILD_ASPDN);   
    printf("\n    %d) Quit program.\n", TEST_EXIT);

    printf("\n  -> ");

    return 1;
}


int
TEST_BuildSCCPMsg(int cmdInput)
{
    SCCP_ADDR origAddr;
    SCCP_ADDR destAddr;
    ITS_SCCP_IE sccpIES[32];
    ITS_SUA_IE suaIES[32];
    int ret = ITS_SUCCESS;
    ITS_EVENT sccpEvt, suaEvt;
    ITS_HDR   hdr;
    int suaIeCnt = 0, i;
    int sccpIeCnt = 0;
    ITS_OCTET sls;
    ITS_BOOLEAN isMgmt;

    ITS_EVENT_INIT (&sccpEvt, 0, 256);
    ITS_EVENT_INIT(&suaEvt, 0, 256);

    hdr.context.ssn = SSN;
    if (cmdInput >= 5 && cmdInput <= 7)
    {
        SCCP_EncodeAddr(&destAddr,
                        SCCP_CPA_ROUTE_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN,
                        DPC, 1, NULL, 0);
    }
    else
    {
        SCCP_EncodeAddr(&destAddr,
                        SCCP_CPA_ROUTE_GTTI|SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN,
                        DPC, SSN, GT_Digits, 5);
    }

    SCCP_EncodeAddr(&origAddr,
                    SCCP_CPA_ROUTE_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN,
                    OPC, SSN, NULL, 0);


    switch(cmdInput)
    {
/*********************************************
 **            ASPUP TEST
 *********************************************/
    case BUILD_ASPUP:

        suaIES[0].param_id = SUA_PRM_MSG_HDR;
        suaIES[0].param_length =  sizeof(SUA_MSG_HDR);
        suaIES[0].param_data.msgHeader.suaMsgClass = 
                                             SUA_ASP_STATE_MAINT_MSG;
        suaIES[0].param_data.msgHeader.suaMsgType = SUA_MSG_ASPUP;
        suaIES[0].param_data.msgHeader.version = SUA_PROT_VER1;

        suaIES[1].param_id = SUA_PRM_ASP_CAP;
        suaIES[1].param_length =  sizeof(SUA_ASP_CAPAB);
        SUA_SET_VARIANT(suaIES[1].param_data.aspCapability, SCCP_ITU_I);
        suaIES[1].param_data.aspCapability.protClass = SUA_PROT_CLASS_0;
        suaIES[1].param_data.aspCapability.interworking = 
                                                     SUA_ITW_IP_SIG_ENDP; 

        suaIES[2].param_id = SUA_PRM_ALI;
        suaIES[2].param_length =  sizeof(SUA_ALI);
        memcpy(suaIES[2].param_data.ali.adaptLayerIdent, ALI, 3);


        suaIES[3].param_id = SUA_PRM_INFO_STR;
        suaIES[3].param_length =  5;
        memcpy(suaIES[3].param_data.infoStr.infoStr, INFO_STR, 5);  

        ret = SUA_EncodeMsg(suaIES, 4, &suaEvt, &SUA_ASPUP_Desc);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }      
        
        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);

        }
        printf("\n");

        break;



/*********************************************
 **            ASPDN TEST
 *********************************************/
    case BUILD_ASPDN:

        suaIES[0].param_id = SUA_PRM_MSG_HDR;
        suaIES[0].param_length =  sizeof(SUA_MSG_HDR);
        suaIES[0].param_data.msgHeader.suaMsgClass = 
                                             SUA_ASP_STATE_MAINT_MSG;
        suaIES[0].param_data.msgHeader.suaMsgType = SUA_MSG_ASPUP;
        suaIES[0].param_data.msgHeader.version = SUA_PROT_VER1;

        suaIES[1].param_id = SUA_PRM_UNAV_CAUSE;
        suaIES[1].param_length =  sizeof(SUA_UNAV_CAUSE);
        suaIES[1].param_data.unavCause.unavCause[3] = SUA_CAUSE_PROC_OUTAGE;
 
/*
        suaIES[1].param_id = SUA_PRM_ALI;
        suaIES[1].param_length =  sizeof(SUA_ALI);
        memcpy(suaIES[1].param_data.ali.adaptLayerIdent, ALI, 3);

*/
        suaIES[2].param_id = SUA_PRM_INFO_STR;
        suaIES[2].param_length =  5;
        memcpy(suaIES[2].param_data.infoStr.infoStr, INFO_STR, 5);

        ret = SUA_EncodeMsg(suaIES, 3, &suaEvt, &SUA_ASPDN_Desc);
        if (ret != ITS_SUCCESS)
        {
            printf("error encoding message \n");
            return ret;
        }      
        
        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);

        }
        printf("\n");

        break;



/*********************************************
 **            UDT TEST
 *********************************************/
    case BUILD_UDT:

        sccpIES[0].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        sccpIES[0].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[0].param_data.calledPartyAddr, &destAddr,
               sizeof(SCCP_ADDR));

        sccpIES[1].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        sccpIES[1].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[1].param_data.callingPartyAddr, &origAddr,
               sizeof(SCCP_ADDR));
        
        sccpIES[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        sccpIES[2].param_length = sizeof (SCCP_PROT_CLASS);
        sccpIES[2].param_data.protocolClass.pclass = 0x82;

        sccpIES[3].param_id = SCCP_PRM_DATA;
        sccpIES[3].param_length = 10;
        memcpy(sccpIES[3].param_data.userData.data, DATA, 10);

        ret = SCCP_Encode(sccpIES, 4, SCCP_MSG_UDT,&sccpEvt, &hdr, 
                          &SCCP_UDT_Desc);

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SCCPEvtToSUAEvt(&sccpEvt , ITS_TRUE, &hdr, &sls);

        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SUAEvtToSCCPEvt(&sccpEvt , ITS_TRUE, &hdr, &isMgmt);

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


/*      ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_UDT_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
        }

        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_CLDT_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
        }

        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);

        }
        printf("\n");

        ret = SUA_DecodeMsg(suaIES, &suaIeCnt, &suaEvt, &SUA_CLDT_Desc);
        if (ret != ITS_SUCCESS)
        {
            printf("SUA_DecodeMsg returned %d \n", ret);
        }
        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_CLDT_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, sccpMsgType,
                          &sccpEvt, &hdr, &SCCP_UDT_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
        }

        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
*/       
        break;


/*********************************************
 **            XUDT TEST
 *********************************************/
    case BUILD_XUDT:

        sccpIES[0].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        sccpIES[0].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[0].param_data.calledPartyAddr, &destAddr,
               sizeof(SCCP_ADDR));

        sccpIES[1].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        sccpIES[1].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[1].param_data.callingPartyAddr, &origAddr,
               sizeof(SCCP_ADDR));
        
        sccpIES[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        sccpIES[2].param_length = sizeof (SCCP_PROT_CLASS);
        sccpIES[2].param_data.protocolClass.pclass = SCCP_PCLASS_1;

        sccpIES[3].param_id = SCCP_PRM_DATA;
        sccpIES[3].param_length = 10;
        memcpy(sccpIES[3].param_data.userData.data, DATA, 10);

        sccpIES[4].param_id = SCCP_PRM_HOP_COUNTER;
        sccpIES[4].param_length = sizeof(SCCP_HOP_COUNT);
        sccpIES[4].param_data.hopCount.count = 0x0B;

        /* optional parameter */
        sccpIES[5].param_id = SCCP_PRM_SEGMENTATION;
        sccpIES[5].param_length = sizeof(SCCP_SEGMENTATION);
        sccpIES[5].param_data.segmentation.flags = 0xC3;
        memcpy(sccpIES[5].param_data.segmentation.localRef.refno, SRC_LOCAL_REF,
               3);

        sccpIES[6].param_id = SCCP_PRM_IMPORTANCE;
        sccpIES[6].param_length = sizeof(SCCP_IMPORTANCE);
        sccpIES[6].param_data.impotance.importance = 0x03;
        
        ret = SCCP_Encode(sccpIES, 7, SCCP_MSG_XUDT, &sccpEvt, &hdr, 
                          &SCCP_XUDT_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d\n", ret);
            return -1;
        }

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SUA_SCCPEvtToSUAEvt(&sccpEvt , ITS_TRUE, &hdr, &sls);

        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SUAEvtToSCCPEvt(&sccpEvt , ITS_TRUE, &hdr, &isMgmt);

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
/*
        ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_XUDT_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
        }

        printf("Number of SUA IES : %d\n", suaIeCnt);
        printf("The message was converted to SUA type: %04x\n", suaMsgType);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_CLDT_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
        }

        printf("SUA CLDT message : \n");
        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);

        }
        printf("\n");

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_CLDT_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, SCCP_MSG_XUDT,
                          &sccpEvt, &hdr, &SCCP_XUDT_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
        }

        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
       
*/
        break;


/*********************************************
 **            UDTS TEST
 *********************************************/
    case BUILD_UDTS:

        sccpIES[0].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        sccpIES[0].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[0].param_data.calledPartyAddr, &destAddr,
               sizeof(SCCP_ADDR));

        sccpIES[1].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        sccpIES[1].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[1].param_data.callingPartyAddr, &origAddr,
               sizeof(SCCP_ADDR));
        
        sccpIES[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        sccpIES[2].param_length = sizeof (SCCP_PROT_CLASS);
        sccpIES[2].param_data.protocolClass.pclass = SCCP_PCLASS_0;

        sccpIES[3].param_id = SCCP_PRM_DATA;
        sccpIES[3].param_length = 10;
        memcpy(sccpIES[3].param_data.userData.data, DATA, 10);

        sccpIES[4].param_id = SCCP_PRM_RETURN_CAUSE;
        sccpIES[4].param_length = sizeof(SCCP_RET_CAUSE);
        sccpIES[4].param_data.returnCause.cause = 0xBB;

        ret = SCCP_Encode(sccpIES, 5, SCCP_MSG_UDTS, &sccpEvt, &hdr, 
                          &SCCP_UDTS_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
            return -1;
        }

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SUA_SCCPEvtToSUAEvt(&sccpEvt , ITS_TRUE, &hdr, &sls);

        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SUAEvtToSCCPEvt(&sccpEvt , ITS_TRUE, &hdr, &isMgmt);

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

/*
        ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_UDTS_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
            return -1;
        }

        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_CLDA_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
            return -1;
        }

        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);

        }
        printf("\n");


        ret = SUA_DecodeMsg(suaIES, &suaIeCnt, &suaEvt, &SUA_CLDA_Desc);
        if (ret != ITS_SUCCESS)
        {
            printf("SUA_DecodeMsg returned %d \n", ret);
        }
        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_CLDA_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
            return -1;
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, sccpMsgType,
                          &sccpEvt, &hdr, &SCCP_UDTS_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
            return -1;
        }

        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
*/     
        break;


/*********************************************
 **            XUDTS TEST
 *********************************************/
    case BUILD_XUDTS:

        sccpIES[0].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        sccpIES[0].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[0].param_data.calledPartyAddr, &destAddr,
               sizeof(SCCP_ADDR));

        sccpIES[1].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        sccpIES[1].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[1].param_data.callingPartyAddr, &origAddr,
               sizeof(SCCP_ADDR));
        
        sccpIES[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        sccpIES[2].param_length = sizeof (SCCP_PROT_CLASS);
        sccpIES[2].param_data.protocolClass.pclass = SCCP_PCLASS_0;

        sccpIES[3].param_id = SCCP_PRM_DATA;
        sccpIES[3].param_length = 10;
        memcpy(sccpIES[3].param_data.userData.data, DATA, 10);

        sccpIES[4].param_id = SCCP_PRM_RETURN_CAUSE;
        sccpIES[4].param_length = sizeof(SCCP_RET_CAUSE);
        sccpIES[4].param_data.returnCause.cause = 0xBB;

        sccpIES[5].param_id = SCCP_PRM_HOP_COUNTER;
        sccpIES[5].param_length = sizeof(SCCP_HOP_COUNT);
        sccpIES[5].param_data.hopCount.count = 0x0B;

        /* optional parameter */
        sccpIES[6].param_id = SCCP_PRM_SEGMENTATION;
        sccpIES[6].param_length = sizeof(SCCP_SEGMENTATION);
        sccpIES[6].param_data.segmentation.flags = 0xC3;
        memcpy(sccpIES[6].param_data.segmentation.localRef.refno, SRC_LOCAL_REF,
               3);

        ret = SCCP_Encode(sccpIES, 7, SCCP_MSG_XUDTS, &sccpEvt, &hdr, 
                          &SCCP_XUDTS_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
            return -1;
        }

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SUA_SCCPEvtToSUAEvt(&sccpEvt , ITS_TRUE, &hdr, &sls);

        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SUAEvtToSCCPEvt(&sccpEvt , ITS_TRUE, &hdr, &isMgmt);

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
/*
        ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_XUDTS_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
            return -1;
        }

        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_CLDA_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
            return -1;
        }

        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);

        }
        printf("\n");

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_CLDA_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
            return -1;
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, SCCP_MSG_XUDTS,
                          &sccpEvt, &hdr, &SCCP_XUDTS_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
            return -1;
        }

        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
*/
        break;


/*********************************************
 **            SSA TEST
 *********************************************/
    case BUILD_SSA:

        sccpIES[0].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        sccpIES[0].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[0].param_data.calledPartyAddr, &destAddr,
               sizeof(SCCP_ADDR));

        sccpIES[1].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        sccpIES[1].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[1].param_data.callingPartyAddr, &origAddr,
               sizeof(SCCP_ADDR));
        
        sccpIES[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        sccpIES[2].param_length = sizeof (SCCP_PROT_CLASS);
        sccpIES[2].param_data.protocolClass.pclass = 0x82;

        sccpIES[3].param_id = SCCP_PRM_DATA;
        sccpIES[3].param_length = sizeof(SCCP_SCMG);
        memcpy(sccpIES[3].param_data.userData.data, SSA, sizeof(SCCP_SCMG));

        ret = SCCP_Encode(sccpIES, 4, SCCP_MSG_UDT,&sccpEvt, &hdr, 
                          &SCCP_UDT_Desc);

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SUA_SCCPEvtToSUAEvt(&sccpEvt , ITS_TRUE, &hdr, &sls);

        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SUAEvtToSCCPEvt(&sccpEvt , ITS_TRUE, &hdr, &isMgmt);

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
/*
        ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_UDT_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
        }

        printf("SCCP message converted to SUA %04x.\n", suaMsgType);
        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_DAVA_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
        }

        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);

        }
        printf("\n");

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_DAVA_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, sccpMsgType,
                          &sccpEvt, &hdr, &SCCP_UDT_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
        }

        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

*/
        break;



/*********************************************
 **            CR TEST
 *********************************************/
    case BUILD_CR:

        /* CDPA */
        sccpIES[0].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        sccpIES[0].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[0].param_data.calledPartyAddr, &destAddr,
               sizeof(SCCP_ADDR));
        /* CLPA */
        sccpIES[1].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        sccpIES[1].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[1].param_data.callingPartyAddr, &origAddr,
               sizeof(SCCP_ADDR));
        
        /* Protocol Class */
        sccpIES[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        sccpIES[2].param_length = sizeof (SCCP_PROT_CLASS);
        sccpIES[2].param_data.protocolClass.pclass = 0x82;

        /* Source Local reference */
        sccpIES[3].param_id = SCCP_PRM_SRC_LOCAL_REF;
        sccpIES[3].param_length = sizeof(SCCP_REF_NUM);
        memcpy(sccpIES[3].param_data.sourceLocalReference.refno,
               SRC_LOCAL_REF, sizeof(SCCP_REF_NUM));

        /* Data is an optional parameter for SCCP & SUA*/
        sccpIES[4].param_id = SCCP_PRM_DATA;
        sccpIES[4].param_length = 10;
        memcpy(sccpIES[4].param_data.userData.data, DATA, 10);

        /* Hop Counter is an optional for SCCP */
        sccpIES[5].param_id = SCCP_PRM_HOP_COUNTER;
        sccpIES[5].param_length = sizeof(SCCP_HOP_COUNT);
        sccpIES[5].param_data.hopCount.count = 0x0B;

        sccpIES[6].param_id = SCCP_PRM_CREDIT;
        sccpIES[6].param_length = sizeof(SCCP_CREDIT);
        sccpIES[6].param_data.hopCount.count = 0xAA;

        ret = SCCP_Encode(sccpIES, 7, SCCP_MSG_CR, &sccpEvt, &hdr, 
                          &SCCP_CR_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d\n", ret);
            return -1;
        }
        
        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SUA_SCCPEvtToSUAEvt(&sccpEvt , ITS_TRUE, &hdr, &sls);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPEvtToSUAEvt returned %d\n", ret);
            return -1;
        }

        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SUAEvtToSCCPEvt(&sccpEvt , ITS_TRUE, &hdr, &isMgmt);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUAEvtToSCCPEvt returned %d\n", ret);
            return -1;
        }

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
/*
        ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_CR_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
            return -1;
        }

        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        printf("SCCP Message Conv To SUA %04x \n", suaMsgType);

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_CORE_Desc);

        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
            return -1;
        }

        printf("SUA Event:\n");
        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);

        }
        printf("\n");

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_CORE_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, sccpMsgType,
                          &sccpEvt, &hdr, &SCCP_CR_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
        }

        printf("SCCP Event \n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
*/
        break;


/*********************************************
 **            CC TEST
 *********************************************/
    case BUILD_CC:

        /* Destination local reference */
        sccpIES[0].param_id = SCCP_PRM_DEST_LOCAL_REF;
        sccpIES[0].param_length = sizeof(SCCP_REF_NUM);
        memcpy(&sccpIES[0].param_data.destinationLocalReference.refno, 
               DST_LOCAL_REF, sizeof(SCCP_REF_NUM));

        /* Source local reference */
        sccpIES[1].param_id = SCCP_PRM_SRC_LOCAL_REF;
        sccpIES[1].param_length = sizeof(SCCP_REF_NUM);
        memcpy(&sccpIES[1].param_data.sourceLocalReference.refno,
               SRC_LOCAL_REF, sizeof(SCCP_REF_NUM));
        
        /* Protocol Class */
        sccpIES[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        sccpIES[2].param_length = sizeof (SCCP_PROT_CLASS);
        sccpIES[2].param_data.protocolClass.pclass = 0x82;

        /* Data is an optional parameter for SCCP & SUA */
/*      sccpIES[4].param_id = SCCP_PRM_DATA;
        sccpIES[4].param_length = 10;
        memcpy(sccpIES[4].param_data.userData.data, DATA, 10); */

        ret = SCCP_Encode(sccpIES, 3, SCCP_MSG_CC, &sccpEvt, &hdr, 
                          &SCCP_CC_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d\n", ret);
            return -1;
        }
        
        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SUA_SCCPEvtToSUAEvt(&sccpEvt , ITS_TRUE, &hdr, &sls);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPEvtToSUAEvt returned %d\n", ret);
            return -1;
        }

        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SUAEvtToSCCPEvt(&sccpEvt , ITS_TRUE, &hdr, &isMgmt);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUAEvtToSCCPEvt returned %d\n", ret);
            return -1;
        }

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
/*
        ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_CC_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
            return -1;
        }

        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        printf("SCCP Message Conv To SUA %04x \n", suaMsgType);

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_COAK_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
            return -1;
        }

        printf("SUA Event:\n");
        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);
        }
        printf("\n");

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_COAK_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, sccpMsgType,
                          &sccpEvt, &hdr, &SCCP_CC_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
        }

        printf("SCCP Event \n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
*/
        break;


/*********************************************
 **            CREF TEST
 *********************************************/
    case BUILD_CREF:

        /* Destination local reference */
        sccpIES[0].param_id = SCCP_PRM_DEST_LOCAL_REF;
        sccpIES[0].param_length = sizeof(SCCP_REF_NUM);
        memcpy(&sccpIES[0].param_data.destinationLocalReference.refno, 
               DST_LOCAL_REF, sizeof(SCCP_REF_NUM));

        /* Refusal Cause */
        sccpIES[1].param_id = SCCP_PRM_REFUSAL_CAUSE;
        sccpIES[1].param_length = sizeof(SCCP_REF_CAUSE);
        sccpIES[1].param_data.refusalCause.cause = 0xAA;
        
        /* Data is an optional parameter for SCCP & SUA */
/*      sccpIES[2].param_id = SCCP_PRM_DATA;
        sccpIES[2].param_length = 10;
        memcpy(sccpIES[2].param_data.userData.data, DATA, 10); */

        ret = SCCP_Encode(sccpIES, 2, SCCP_MSG_CREF, &sccpEvt, &hdr, 
                          &SCCP_CREF_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d\n", ret);
            return -1;
        }
        
        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SUA_SCCPEvtToSUAEvt(&sccpEvt , ITS_TRUE, &hdr, &sls);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPEvtToSUAEvt returned %d\n", ret);
            return -1;
        }

        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SUAEvtToSCCPEvt(&sccpEvt , ITS_TRUE, &hdr, &isMgmt);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUAEvtToSCCPEvt returned %d\n", ret);
            return -1;
        }

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

/*
        ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_CREF_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
            return -1;
        }

        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        printf("SCCP Message Conv To SUA %04x \n", suaMsgType);

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_COAK_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
            return -1;
        }

        printf("SUA Event:\n");
        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);
        }
        printf("\n");

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_COAK_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, sccpMsgType,
                          &sccpEvt, &hdr, &SCCP_CREF_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
        }

        printf("SCCP Event \n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
*/
        break;


/*********************************************
 **            DT1 TEST
 *********************************************/
    case BUILD_DT1:

        /* Destination local reference */
        sccpIES[0].param_id = SCCP_PRM_DEST_LOCAL_REF;
        sccpIES[0].param_length = sizeof(SCCP_REF_NUM);
        memcpy(&sccpIES[0].param_data.destinationLocalReference.refno, 
               DST_LOCAL_REF, sizeof(SCCP_REF_NUM));

        /* Refusal Cause */
        sccpIES[1].param_id = SCCP_PRM_SEGMENT_REASSEM;
        sccpIES[1].param_length = sizeof(SCCP_SEG_RES);
        sccpIES[1].param_data.segmentingReassembly.seg_res = 0x01;
        
        /* Data is an optional parameter for SCCP & SUA */
        sccpIES[2].param_id = SCCP_PRM_DATA;
        sccpIES[2].param_length = 10;
        memcpy(sccpIES[2].param_data.userData.data, DATA, 10); 

        ret = SCCP_Encode(sccpIES, 3, SCCP_MSG_DT1, &sccpEvt, &hdr, 
                          &SCCP_DT1_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d\n", ret);
            return -1;
        }
        
        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SUA_SCCPEvtToSUAEvt(&sccpEvt , ITS_TRUE, &hdr, &sls);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPEvtToSUAEvt returned %d\n", ret);
            return -1;
        }

        printf("*---> Dump SUA Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");


        ret = SUA_SUAEvtToSCCPEvt(&sccpEvt , ITS_TRUE, &hdr, &isMgmt);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUAEvtToSCCPEvt returned %d\n", ret);
            return -1;
        }

        printf("*---> Dump SCCP Event <---*\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

/*
        ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_DT1_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
            return -1;
        }

        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        printf("SCCP Message Conv To SUA %04x \n", suaMsgType);

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_CODT_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
            return -1;
        }

        printf("SUA Event:\n");
        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);
        }
        printf("\n");

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_CODT_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, sccpMsgType,
                          &sccpEvt, &hdr, &SCCP_DT1_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
        }

        printf("SCCP Event \n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
*/
        break;

    case BUILD_RSLD:

        /* Destination local reference */
        sccpIES[0].param_id = SCCP_PRM_DEST_LOCAL_REF;
        sccpIES[0].param_length = sizeof(SCCP_REF_NUM);
        memcpy(&sccpIES[0].param_data.destinationLocalReference.refno, 
               DST_LOCAL_REF, sizeof(SCCP_REF_NUM));

        /* Source local reference */
        sccpIES[1].param_id = SCCP_PRM_SRC_LOCAL_REF;
        sccpIES[1].param_length = sizeof(SCCP_REF_NUM);
        memcpy(&sccpIES[1].param_data.sourceLocalReference.refno,
               SRC_LOCAL_REF, sizeof(SCCP_REF_NUM));

        /* Release cause parameter */
        sccpIES[2].param_id = SCCP_PRM_RELEASE_CAUSE;
        sccpIES[2].param_length = sizeof(SCCP_REL_CAUSE);
        sccpIES[2].param_data.releaseCause.cause = 0xAA;

        /* Data is an optional parameter for SCCP & SUA */
        sccpIES[3].param_id = SCCP_PRM_DATA;
        sccpIES[3].param_length = 10;
        memcpy(sccpIES[3].param_data.userData.data, DATA, 10); 

        ret = SCCP_Encode(sccpIES, 4, SCCP_MSG_RLSD, &sccpEvt, &hdr, 
                          &SCCP_RLSD_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d\n", ret);
            return -1;
        }
        
        printf("SCCP Event:\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");
/*
        ret = SUA_SCCPDecodeToSUA(suaIES, &suaIeCnt, &sccpEvt,
                                  &SCCP_RLSD_Desc, &suaMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SCCPDecodeToSUA returned %d.\n", ret);
            return -1;
        }

        printf("Number of SUA IES : %d\n", suaIeCnt);
        for (i = 0; i < suaIeCnt; i++)
        {
            SUA_PrintSUA_IES(suaIES + i);
        }

        printf("SCCP Message Conv To SUA %04x \n", suaMsgType);

        ret = SUA_EncodeMsg(suaIES, suaIeCnt, &suaEvt,
                            &SUA_RELRE_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_EncodeMsg returned %d.\n", ret);
            return -1;
        }

        printf("SUA Event:\n");
        for(i=0; i < suaEvt.len; i++)
        {
            printf("%02x ", suaEvt.data[i]);
        }
        printf("\n");

        memset(sccpEvt.data, 0, sccpEvt.len);

        ret = SUA_SUADecodeToSCCP(sccpIES, &sccpIeCnt, &suaEvt,
                                  &SUA_RELRE_Desc, &sccpMsgType);
        if(ret != ITS_SUCCESS)
        {
            printf("SUA_SUADecodeToSCCP returned %d.\n", ret);
        }

        ret = SCCP_Encode(sccpIES, sccpIeCnt, sccpMsgType,
                          &sccpEvt, &hdr, &SCCP_RLSD_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d.\n", ret);
        }

        printf("SCCP Event \n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

*/
        break;


/*********************************************
 **            LUDT TEST
 *********************************************/
    case BUILD_LUDT:
    {
        int ieCount;

        sccpIES[0].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        sccpIES[0].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[0].param_data.calledPartyAddr, &destAddr,
               sizeof(SCCP_ADDR));

        sccpIES[1].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        sccpIES[1].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[1].param_data.callingPartyAddr, &origAddr,
               sizeof(SCCP_ADDR));
        
        sccpIES[2].param_id = SCCP_PRM_PROTOCOL_CLASS;
        sccpIES[2].param_length = sizeof (SCCP_PROT_CLASS);
        sccpIES[2].param_data.protocolClass.pclass = SCCP_PCLASS_1;

        sccpIES[3].param_id = SCCP_PRM_LONG_DATA;
        sccpIES[3].param_data.longData.len = 10;
        memcpy(sccpIES[3].param_data.longData.data, DATA, 10);

        sccpIES[4].param_id = SCCP_PRM_HOP_COUNTER;
        sccpIES[4].param_length = sizeof(SCCP_HOP_COUNT);
        sccpIES[4].param_data.hopCount.count = 0x0B;

        /* optional parameter */
        sccpIES[5].param_id = SCCP_PRM_SEGMENTATION;
        sccpIES[5].param_length = sizeof(SCCP_SEGMENTATION);
        sccpIES[5].param_data.segmentation.flags = 0xC3;
        memcpy(sccpIES[5].param_data.segmentation.localRef.refno, SRC_LOCAL_REF,
               3);

        ret = SCCP_Encode(sccpIES, 6, SCCP_MSG_LUDT, &sccpEvt, &hdr, 
                          &SCCP_LUDT_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d\n", ret);
            return -1;
        }

        printf("SCCP LUDT Message :\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SCCP_Decode(sccpIES, &ieCount, &sccpEvt, &SCCP_LUDT_Desc);

        break;
    }

/*********************************************
 **            LUDTS TEST
 *********************************************/
    case BUILD_LUDTS:
    {
        int ieCount;

        sccpIES[0].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        sccpIES[0].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[0].param_data.calledPartyAddr, &destAddr,
               sizeof(SCCP_ADDR));

        sccpIES[1].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
        sccpIES[1].param_length = sizeof(SCCP_ADDR);
        memcpy(&sccpIES[1].param_data.callingPartyAddr, &origAddr,
               sizeof(SCCP_ADDR));

        sccpIES[2].param_id = SCCP_PRM_RETURN_CAUSE;
        sccpIES[2].param_length = sizeof(SCCP_RET_CAUSE);
        sccpIES[2].param_data.returnCause.cause = 0xBB;
        

        sccpIES[3].param_id = SCCP_PRM_LONG_DATA;
        sccpIES[3].param_data.longData.len = 10;
        memcpy(sccpIES[3].param_data.longData.data, DATA, 10);

        sccpIES[4].param_id = SCCP_PRM_HOP_COUNTER;
        sccpIES[4].param_length = sizeof(SCCP_HOP_COUNT);
        sccpIES[4].param_data.hopCount.count = 0x0B;

        /* optional parameter */
        sccpIES[5].param_id = SCCP_PRM_SEGMENTATION;
        sccpIES[5].param_length = sizeof(SCCP_SEGMENTATION);
        sccpIES[5].param_data.segmentation.flags = 0xC3;
        memcpy(sccpIES[5].param_data.segmentation.localRef.refno, SRC_LOCAL_REF,
               3);

        ret = SCCP_Encode(sccpIES, 6, SCCP_MSG_LUDTS, &sccpEvt, &hdr, 
                          &SCCP_LUDTS_Desc);
        if(ret != ITS_SUCCESS)
        {
            printf("SCCP_Encode returned %d\n", ret);
            return -1;
        }

        printf("SCCP LUDT Message :\n");
        for(i=0; i < sccpEvt.len; i++)
        {
            printf("%02x ", sccpEvt.data[i]);

        }
        printf("\n");

        ret = SCCP_Decode(sccpIES, &ieCount, &sccpEvt, &SCCP_LUDTS_Desc);

        break;
    }
 
    default:
        return -1;
    }

    ITS_EVENT_TERM(&sccpEvt);
    ITS_EVENT_TERM(&suaEvt);

    return ret;
}


int
main()
{
    int cmdInput;
    int ret = ITS_SUCCESS;
    ITS_HANDLE handle;
    char appName[10] = "test";
    
    APPL_SetName(appName);

    ITS_AddFeature(itsINTELLISS7_Class);

    handle = (ITS_HANDLE)ITS_Initialize(ITS_SCCP |
                                        ITS_TRANSPORT_TQUEUE |
                                        ITS_TRANSPORT_SINGLE_USER, 1);
    if (handle == NULL)
    { 
        printf("\nCouldn't create ITS_HANDLE. Exiting...\n");
        exit(0);
    }

    for (;;)
    {
        TEST_PrintCommand();

        scanf("%d", &cmdInput);
        printf("\nYou input %d.\n", cmdInput);
        
        if (cmdInput == TEST_EXIT)
        {
            printf("Exiting SUA Test Program...\n");
      
            exit(1);
        }

        if (VALID_CHOICE(cmdInput))
        {    
            ret = TEST_BuildSCCPMsg(cmdInput); 
        }
        else
        {
            printf("Wrong Choice, Try again \n");
        }
    }


}