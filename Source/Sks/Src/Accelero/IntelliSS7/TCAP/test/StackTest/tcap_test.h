#ifndef _ITU_TCAP_TEST_H
#define _ITU_TCAP_TEST_H

#include <itu/tcap.h>

#define USE_ITS_INST_NB     1
#define MTP3_INST_NB        2

/* type of SCCP address */
#define SCCP_ADDR_CGPA       0
#define SCCP_ADDR_CDPA       1

/* Transaction Type */
#define TC_BEGIN    1
#define TC_CONTINUE 2     
#define TC_END      3
#define TC_ABORT    4
#define TC_UNI      5

/* Component Type */
#define TC_INVOKE           1
#define TC_ERROR            2
#define TC_RESULT_L         3
#define TC_RESULT_NL        4
#define TC_REJECT           5
#define TC_CANCEL           6
#define TC_TIMER_RESET      7

/* TCAP msg Tags */
#define UNI_TAG         1
#define BEGIN_TAG       2
#define END_TAG         4
#define CONTINUE_TAG    5
#define ABORT_TAG       7
#define UNK_TAG         6

#define CPT_INVOKE_TAG      1
#define CPT_R_RESULT_TAG    2
#define CPT_R_ERROR_TAG     3
#define CPT_UNK_TAG         4

/* TCAP IE Tags */
#define OTID_TAG            0x48
#define DTID_TAG            0x49
#define CPT_PORTION_TAG     0x6C
#define P_ABORT_CAUSE_TAG   0x4A
#define UNK_IE_TAG          0x6D
#define TCAP_MSG_UNK_TAG    0x66

#define PARAMETER_SET_TAG   (0x30U)
#define SEQUENCE_TAG        0x30         

/*
 * Notice Return Cause
 */
static char *notice_returnCause[] = {
    "No Translation for an Address of Such Nature",
    "No Translation for this Specific Address",
    "Subsystem Congestion",
    "Subsystem Failure",
    "Unequipped User",
    "MTP Failure",
    "Network Congestion",
    "Error in Message Transport (XUDTS msg)",
    "Error in Local Processing (XUDTS msg)",
    "Destination Cannot Perform Reassembly (XUDTS msg)",
    "SCCP Failure",
};


static ITS_OCTET user_Info[12] = {
    /* External Tag, Then Len */
    0x28,
    0x0A,
    /* OID Tag, Len the OID */
    0x06,
    0x03,
    0x81,
    0x34,
    0x03,
    /* Signle ASN.1 type Tag, Len  */
    0xA0,
    0x03,
    /* User Data */
    0x01,
    0x02,
    0x03,
};


/*
 * This macro will return a text represensation of the qos when present
 */
#define getText_qosInd(qosInd)                                                 \
    ((qosInd & (QOSI_RET_OPT|QOSI_SEQ_CTRL) == (QOSI_RET_OPT|QOSI_SEQ_CTRL)) ? \
     "Return Option and Sequence Control" :                                    \
    ((qosInd & QOSI_RET_OPT) ? "Return Option" : "Sequence Control")) 


/*
 * Macro used to set the qos for
 * a TCAP transaction.
 * qos of 1 = Not Seq, Not Return,  qos of 2 = Not Seq, Return. 
 * qos of 3 = Seq, Not Return, qos of 4 = Seq, Return. 
 */
#define set_qos(transaction, qos) \
    switch(qos) \
    {   \
        case 1: \
            transaction.qos.indicator = 0; \
            break;  \
        case 2: \
            transaction.qos.indicator = QOSI_RET_OPT;\
            break;  \
        case 3: \
            transaction.qos.indicator = QOSI_SEQ_CTRL; \
            break;  \
        case 4: \
            transaction.qos.indicator = \
                (QOSI_SEQ_CTRL | QOSI_RET_OPT);\
            break;  \
    }            \

/*
 * Macro to copy some bytes into User Info array
 * for and ITU transaction
 */
#define setUserInfo(userinfo) (userinfo.len = 12)
    
/*
 * Macro to copy some bytes into AC Name array
 * for and ITU transaction
 */
#define set_proposed_ACName(acName)         \
    ((acName.len) = 5,                      \
     (acName.data)[0] = (ITS_OCTET)(0x06U), \
     (acName.data)[1] = (ITS_OCTET)(0x03U), \
     (acName.data)[2] = (ITS_OCTET)(0x81U), \
     (acName.data)[3] = (ITS_OCTET)(0x34U), \
     (acName.data)[4] = (ITS_OCTET)(0x03U))

#define set_alternative_ACName(acName)      \
    ((acName.len) = 5,                      \
     (acName.data)[0] = (ITS_OCTET)(0x06U), \
     (acName.data)[1] = (ITS_OCTET)(0x03U), \
     (acName.data)[2] = (ITS_OCTET)(0x81U), \
     (acName.data)[3] = (ITS_OCTET)(0x02U), \
     (acName.data)[4] = (ITS_OCTET)(0x05U))

/*
 * Macro to copy some bytes into parameters
 * for Invoke Component.
 */
#define setParameterSet(param)             \
    ((param.len) = 5,                      \
     (param.data)[0] = PARAMETER_SET_TAG, \
     (param.data)[1] = (ITS_OCTET)(0x03U), \
     (param.data)[2] = (ITS_OCTET)(0x0AU), \
     (param.data)[3] = (ITS_OCTET)(0x01U), \
     (param.data)[4] = (ITS_OCTET)(0x81U))


int setSCCPAddr(SCCP_ADDR *addr);

void setTC_Begin(TCAP_DLG* TC_Begin, SCCP_ADDR CdPA, SCCP_ADDR CgPA,
                 ITS_BOOLEAN* newDid);
void setTC_End(TCAP_DLG* TC_End, ITS_BOOLEAN* newDid);
void setTC_Continue(TCAP_DLG* TC_Continue, SCCP_ADDR CgPA,
                    ITS_BOOLEAN confirmTC_Begin, ITS_BOOLEAN* newDid);
void setTC_U_Abort(TCAP_DLG* TC_U_Abort, ITS_BOOLEAN* newDid);
void setTC_Uni(TCAP_DLG* TC_Uni, SCCP_ADDR CdPA, SCCP_ADDR CgPA,
               ITS_BOOLEAN* newDid);

void setTC_Invoke(TCAP_CPT* TC_Comp);
void setTC_U_Error(TCAP_CPT* TC_Comp);
void setTC_Result(TCAP_CPT* TC_Comp, ITS_BOOLEAN last);
void setTC_U_Reject(TCAP_CPT* TC_Comp);
void setTC_U_Cancel(TCAP_CPT* TC_Comp);
void setTC_U_TimerReset(TCAP_CPT* TC_Comp);

int sendNStateInd(ITS_HANDLE handle, SCCP_ADDR CgPA, ITS_BOOLEAN allowed);
int endTransaction(ITS_HANDLE handle);

void receiveComponent(ITS_HANDLE handle);

void displayTransaction(ITS_HDR header, TCAP_DLG* transaction,
                        ITS_BOOLEAN indication);
void displayComponent(ITS_HDR header, TCAP_CPT* component,
                      ITS_BOOLEAN indication);

ITS_BOOLEAN ComponentPresent(TCAP_DLG transaction);


/* functions used for MTP3 TCAP */
void setProtocolClass(ITS_OCTET* protocolClass);
int setMTP3Header(MTP3_HEADER *mtp3_header , SCCP_ADDR cgpa, SCCP_ADDR cdpa);
void setTransactionID(ITS_BOOLEAN originating, ITS_OCTET* data, int *len);
void setDialoguePortion(ITS_OCTET* data, int *len);
void setComponentPortion(ITS_OCTET* data, int *len);
void setP_Abort(ITS_OCTET* data, int *len);
ITS_BOOLEAN setUnknownElementTag(ITS_OCTET* data, int *len);
ITS_BOOLEAN setOption();

#endif