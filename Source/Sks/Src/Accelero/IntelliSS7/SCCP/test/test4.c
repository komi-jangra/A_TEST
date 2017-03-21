
#include <stdio.h>
#include <ansi/sccp.h>

void
setSCC_ConReq(ITS_SCCP_IE* ConReq, SCCP_ADDR CdPA, SCCP_ADDR CgPA,
            int* numComps, ITS_HDR *header)
{
    int qos = 0;
    int userInput = 0;
    int credit, i;

    printf("\n ** Info: Setting SCCP ConnReq\n");
        *numComps = 0;

    if ( SCCP_GetNextLocalRef(&header->context.conref) != ITS_SUCCESS)
        printf ("SCCP Get Next Local Reference failed\n");

    ConReq[0].param_id = SCCP_PRM_SRC_LOCAL_REF;
    ConReq[0].param_length = sizeof (SCCP_REF_NUM);
    RN_SET_REF_NUM(ConReq[0].param_data.sourceLocalReference, header->context.conref);
        (*numComps) = *numComps + 1;

    ConReq[1].param_id = SCCP_PRM_PROTOCOL_CLASS;
    ConReq[1].param_length = sizeof (SCCP_PROT_CLASS);
    ConReq[1].param_data.protocolClass.pclass = SCCP_PCLASS_2;
        *numComps = *numComps + 1;

    /* Setting calling and called party address */
    printf("\n Populating called party address (CdPA).");
    printf ("\n Called party len = %d\n", CdPA.len);

    for (i=0;i<CdPA.len;i++)
        printf ("\ndata = %x ", CdPA.data[i]);
    ConReq[2].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ConReq[2].param_length = sizeof (SCCP_ADDR);
    ConReq[2].param_data.calledPartyAddr.len = CdPA.len;
    memcpy(ConReq[2].param_data.calledPartyAddr.data, CdPA.data, CdPA.len);
        *numComps = *numComps + 1;
    printf ("What do you want the credit to be, has to be within 255\n");
    scanf ("%d", &credit);
    ConReq[3].param_id = SCCP_PRM_CREDIT;
    ConReq[3].param_length = sizeof (SCCP_CREDIT);
    ConReq[3].param_data.credit.win_size = credit;
        *numComps = *numComps + 1;

    printf("\n Populating calling party address (CgPA).\n");
    ConReq[4].param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    ConReq[4].param_length = sizeof (SCCP_ADDR);
    ConReq[4].param_data.callingPartyAddr.len = CgPA.len;
    memcpy(ConReq[4].param_data.callingPartyAddr.data, CgPA.data, CgPA.len);
        *numComps = *numComps + 1;

    ConReq[5].param_id = SCCP_PRM_DATA;
    ConReq[5].param_length = 5;
    ConReq[5].param_data.userData.data[0] = 0x03;
    ConReq[5].param_data.userData.data[1] = 0x06;
    ConReq[5].param_data.userData.data[2] = 0x89;
    ConReq[5].param_data.userData.data[3] = 0x98;
    ConReq[5].param_data.userData.data[4] = 0x34;
        *numComps = *numComps + 1;
    printf ("num comps in set is = %d\n", *numComps);

}

static ITS_SCCP_IE  SC_ConReq[10];
static ITS_SCCP_IE  SC_ConCon[10];
static ITS_SCCP_IE  SC_ConRef[10];
static ITS_SCCP_IE  SC_Data1[10];

static SCCP_ADDR cdpa, cgpa;

static int numOfConReqElements;

static ITS_HDR hdr;

static ITS_HANDLE sccp_handle;

void
setSCCPType()
{
    int transType = 0;
    int i, j;

    SCCP_EncodeAddr(&cdpa,
                    SCCP_CPA_ROUTE_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN,
                    5, 6, NULL, 0);
    SCCP_EncodeAddr(&cgpa,
                    SCCP_CPA_ROUTE_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN,
                    10, 7, NULL, 0);

    printf("\n Select SCCP Class 2 Type:\n");
    printf(" (%d) SCCP_ConnectionRequest \n", SCCP_MSG_CR);
    printf(" (%d) SCCP_ConnectionConfirm \n", SCCP_MSG_CC);
    printf(" (%d) SCCP_ConnectionRefused \n", SCCP_MSG_CREF);
    printf(" (%d) SCCP_Data form 1\n", SCCP_MSG_DT1);

    printf(" Enter SCCP Type: ");
    scanf("%d", &transType);

    switch (transType)
    {
    case SCCP_MSG_CR:
        for (i=0;i<10;i++)
                memset (&SC_ConReq[i], 0, sizeof(ITS_SCCP_IE));


        setSCC_ConReq(SC_ConReq, cdpa, cgpa, &numOfConReqElements, &hdr);
        printf ("num elements after set is = %d\n", numOfConReqElements);
        break;
    case SCCP_MSG_CC:
        for (i=0;i<10;i++)
                memset (&SC_ConCon[i], 0, sizeof(ITS_SCCP_IE));

        /* setSCC_ConCon(SC_ConCon, cdpa, cgpa, &numOfConConElements); */
        break;
    case SCCP_MSG_CREF:
        for (i=0;i<10;i++)
                memset (&SC_ConRef[i], 0, sizeof(ITS_SCCP_IE));

        /* setSCC_ConRef(SC_ConRef, cdpa, cgpa, &numOfConRefElements); */
        break;
    case SCCP_MSG_DT1:
        for (i=0;i<10;i++)
                memset (&SC_Data1[i], 0, sizeof(ITS_SCCP_IE));

        /* setSCC_Data1(SC_Data1, cdpa, cgpa, &numOfData1Elements); */
        break;

    default:
        printf("\n ** Warning: Invalid selection.\n");
        break;
    }
}

int
sendSCCPMsg()
{
    int result = 0;
    int transType = 0;
    int compType = 0;
    int userInput = 0;
    int i;

    printf("\n Select SCCP Class 2 Type:\n");
    printf(" (%d) SCCP_ConnectionRequest \n", SCCP_MSG_CR);
    printf(" (%d) SCCP_ConnectionConfirm \n", SCCP_MSG_CC);
    printf(" (%d) SCCP_ConnectionRefused \n", SCCP_MSG_CREF);
    printf(" (%d) SCCP_Data form 1\n", SCCP_MSG_DT1);
   
    printf(" Enter SCCP Type: ");
    scanf("%d", &transType);

    switch (transType)
    {
      case SCCP_MSG_CR:
        /* header.type = ITS_SCCP; */
        printf ("num of conn req elems = %d\n", numOfConReqElements);
        printf ("num elements before set is = %d\n", numOfConReqElements);
        for (i = 0; i < numOfConReqElements; i++)
        {
                printf ("%x ", SC_ConReq[i].param_id);
                printf ("%x ", SC_ConReq[i].param_length);
                printf ("%x ", SC_ConReq[i].param_data);
        }

        printf ("\n");

        /* displaySCCPMsg(hdr, SC_ConReq, numOfConReqElements, ITS_FALSE, SCCP_MSG_CR); */

        result = SCCP_SendConnectionRequest (sccp_handle, &hdr, SC_ConReq, numOfConReqElements);
        if (result != ITS_SUCCESS)
        {
            printf("\n ** Error : Failed to send SCCP message (%d).", result);
            return (result) ;
        }
        else
        {
            printf("\n ** Info : SCCP Connection Request Sent.");
            /* displaySCCPMsg(hdr, SC_ConReq, numOfConReqElements, ITS_FALSE, SCCP_MSG_CR); */
        }
        break;
    }
}
