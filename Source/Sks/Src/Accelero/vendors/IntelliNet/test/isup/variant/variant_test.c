#include <stdio.h>

#include <its.h>
#include <isup_variants.h>
#include <isup_intern.h>
#include <itu/isup_93.h>
#include <itu/isup_china.h>
#include <its_trace.h>

ITS_Class itsINTELLISS7_Class;
//#define ISUP_MSGS  2
//__ISUP_MsgHandlerProc ACMProcFunc;

void
exitHandler()
{
    exit(0);
}

void
DisplayStateMenu(int* state)
{
    printf("\n enter one of the states:");
    printf("\n  0. IDLE (Default)    ");           
    printf("\n  1. WAIT_INCOMING_ACM ");
    printf("\n  2. WAIT_INCOMING_ANM ");
    printf("\n  3. RCVD_INCOMING_ANM ");
    printf("\n  4. WAIT_INCOMING_RLC ");
    printf("\n  5. WAIT_INCOMING_RES ");
    printf("\n  6. WAIT_OUTGOING_ACM ");
    printf("\n  7. WAIT_OUTGOING_ANM ");
    printf("\n  8. SENT_OUTGOING_ANM ");
    printf("\n  9. WAIT_OUTGOING_RLC ");
    printf("\n 10. WAIT_OUTGOING_RES ");
    printf("\n 11. WAIT_OUTGOING_REL ");
    printf("\n ->> " );
    scanf("%x", state);

    if (*state < 0 || *state > 11)
    {
        *state = 0;
    }
}


void
DisplayMsgMenu(int* msg)
{
    // Initialise msg. to default 0: in case of wrong input, this should go
    *msg = 0;

    printf("\n enter one of the ISUP msg.Types in hex. (press 0 to quit):");
    printf("\n ISUP_MSG_ACM    0x06");    /* Address Complete  */
    printf("\n ISUP_MSG_ANM    0x09");    /* Answer  */
    printf("\n ISUP_MSG_CPG    0x2C");    /* Call Progress */
    printf("\n ISUP_MSG_IAM    0x01");    /* Initial Address */ 
    printf("\n ISUP_MSG_PAM    0x28");    /* Pass Along */
    printf("\n ISUP_MSG_REL    0x0C");    /* Release */
    printf("\n ISUP_MSG_RLC    0x10");    /* Release Complete */
    printf("\n ISUP_MSG_RSC    0x12");    /* Reset Circuit Message */
    printf("\n ->> " );
    scanf("%x", msg);
}

#if 0
void
TestVariant_ITU93()
{
    int var = 0x00U;
    int msg = 0x00U;
    int state = 0x00U;
    ITS_USHORT key = 0;
    ITS_BOOLEAN keepGoing = ITS_TRUE;
    ISUP_MSG_DESC* msg_desc = NULL;
    CHINA_VARIANT_Class chinaVariant = NULL;
    ITU93_VARIANT_Class itu93Variant = NULL;
    ITS_EVENT* ev = NULL;
    ITS_HDR* hdr = NULL;
    ITS_ISUP_IE* ie = NULL;
    ITS_OCTET o1, o2;
    ISUP_VariantInfo* var_info = NULL;
    __ISUP_MsgHandlerProc Func = NULL;

    /******************** Class Initialization functions ***************/ 

    itu93Variant = ITU93_CreateClass();
    if (itu93Variant != NULL)
    {
        printf("\n Successfully created ITU93 VariantClass\n");
        var_info = ISUP_CLASS_INFO(itu93Variant);
    }
    else
    {
	printf("\n ITU93 Variant Class creat fail: exiting...\n");
        return ;
    }

    /*********************** Variant specific functions ****************/

    if (ITU93_IsMsgCompInfoSupported((ITS_Class)itu93Variant))
    {
	printf(" Msg Comp Info Param Supported by Variant...\n");
    }
    else
    {
	printf(" Msg Comp Info Param NOT Supported by Variant...\n");
    }

    if (ITU93_IsParamCompInfoSupported((ITS_Class)itu93Variant))
    {
	printf(" Param Comp Info Param Supported by Variant...\n");
    }
    else
    {
	printf(" Param Comp Info Param NOT Supported by Variant...\n");
    }


    /************************** Message specific functions ****************/

    while (keepGoing)
    {
        DisplayMsgMenu(&msg);

        switch (msg)
        {
        case  0:
             keepGoing = ITS_FALSE;
             break;

        case ISUP_MSG_ACM:    /* Address Complete  */
        case ISUP_MSG_ANM:    /* Answer  */
        case ISUP_MSG_CPG:    /* Call Progress */
        case ISUP_MSG_IAM:    /* Initial Address */ 
        case ISUP_MSG_PAM:    /* Pass Along */
        case ISUP_MSG_REL:    /* Release */
        case ISUP_MSG_RLC:    /* Release Complete */
        case ISUP_MSG_RSC:    /* Reset Circuit Message */

             DisplayStateMenu(&state);

             // Check if msg is supported
             if (ITU93_IsMsgSupported((ITS_Class)itu93Variant, (ITS_OCTET)msg))
             {
	         printf(" Message %02x (hex), Supported \n", msg );
             }
             else
             {
	         printf(" Message %02x (hex), Not Supported \n", msg);
             }

             // Get the msg descriptor 
             ITU93_GetMsgDescription((ITS_Class)itu93Variant, (ITS_OCTET)msg);

             if ((Func = ITU93_GetMsgProc((ITS_Class)itu93Variant, msg, state))
                                                                 == NULL)
             {
	         printf(" No func. entry in HashTable: msg %x, state %x \n",
                                                           msg, state);
             }
             else
             {
	         printf(" msg %x, state %x, address %x \n", msg, state, Func);
             }

             break;
                                                        
        default:
            // Call unrec. param handling procedure
             ITU93_HandleUnrecMsg((ITS_Class)itu93Variant, ev);

        } // end of switch

    } // end of while keepGoing

}                                                                               


void
TestVariant_CHINA()
{
    int var = 0x00U;
    int msg = 0x00U;
    int state = 0x00U;
    ITS_BOOLEAN keepGoing = ITS_TRUE;
    ISUP_MSG_DESC* msg_desc = NULL;
    CHINA_VARIANT_Class chinaVariant = NULL;
    ITU93_VARIANT_Class itu93Variant = NULL;
    ITS_EVENT* ev = NULL;
    ITS_HDR* hdr = NULL;
    ITS_ISUP_IE* ie = NULL;
    ITS_OCTET o1, o2;
    ISUP_VariantInfo* var_info = NULL;
    __ISUP_MsgHandlerProc Func = NULL;

    /******************** Class Initialization functions ***************/ 

    chinaVariant = CHINA_CreateClass();
    if (chinaVariant != NULL)
    {
        printf("\n Successfully created CHINA VariantClass\n");
    }
    else
    {
	printf("\nChina Variant Class creat problem: exiting...\n");
        return ;
    }
    /*********************** Variant specific functions ****************/

    if (CHINA_IsMsgCompInfoSupported(chinaVariant))
    {
	printf(" Msg Comp Info Param Supported by Variant...\n");
    }
    else
    {
	printf(" Msg Comp Info Param NOT Supported by Variant...\n");
    }

    if (CHINA_IsParamCompInfoSupported(chinaVariant))
    {
	printf(" Param Comp Info Param Supported by Variant...\n");
    }
    else
    {
	printf(" Param Comp Info Param NOT Supported by Variant...\n");
    }


    /************************** Message specific functions ****************/

    while (keepGoing)
    {
        DisplayMsgMenu(&msg);

        switch (msg)
        {
        case  0:
             keepGoing = ITS_FALSE;
             break;

        case ISUP_MSG_ACM:    /* Address Complete  */
        case ISUP_MSG_ANM:    /* Answer  */
        case ISUP_MSG_CPG:    /* Call Progress */
        case ISUP_MSG_IAM:    /* Initial Address */
        case ISUP_MSG_PAM:    /* Pass Along */
        case ISUP_MSG_REL:    /* Release */
        case ISUP_MSG_RLC:    /* Release Complete */
        case ISUP_MSG_RSC:    /* Reset Circuit Message */

             DisplayStateMenu(&state);                                         

             // Check if msg is supported
             if (CHINA_IsMsgSupported(chinaVariant, (ITS_OCTET)msg))
             {
	         printf(" Message %02x (hex), Supported \n", msg );
             }
             else
             {
	         printf(" Message %02x (hex), Not Supported \n", msg);
             }

             // Get the msg descriptor 
             CHINA_GetMsgDescription(chinaVariant, (ITS_OCTET)msg);

             // Call dummy Encode function
             // CHINA_EncodeMsg(chinaVariant, ie, msg, o1, o2, hdr, ev);

             // Call Variant specific function 
             // CHINA_VARIANT_SpecificMsg((ITS_Class)chinaVariant, ev);

             if ((Func = CHINA_GetMsgProc(chinaVariant, msg, state)) == NULL)
             {
                 printf(" No func. entry in HashTable: msg %x, state %x \n",
                                                           msg, state);
             }
             else
             {
                 printf("msg %x, state %x, address %x \n", msg, state, Func);
             }
             break;                                                          

        default:
            // Call unrec. param handling procedure
             CHINA_HandleUnrecMsg(chinaVariant, ev);

        } // end of while

    } // end of while KeepGoing

}                                                                               
#endif

int
main()
{
    int var = 0x00U;
    ITS_Class class = NULL;
    int msg = 0x00U;
    int state = 0x00U;
    int cic = 0x00U;
    ITS_BOOLEAN keepGoing = ITS_TRUE;
    ISUP_MSG_DESC* msg_desc = NULL;
    ITS_EVENT* ev = NULL;
    ITS_HDR* hdr = NULL;
    ITS_ISUP_IE* ie = NULL;
    ITS_OCTET o1, o2;
    ITS_USHORT ckgp = 0;
    ITS_USHORT numCics = 0;
    ITS_USHORT index = 0;
    ISUP_VariantInfo* var_info = NULL;
    ISUP_TMR_HNDL_INFO* Timer = NULL;
    __ISUP_MsgHandlerProc Func = NULL;
                                                                               
    signal(SIGINT, exitHandler);

    ITS_AddFeature(itsINTELLISS7_Class);        

    printf("\n Which Variant do you want to test?" );
    printf("\n 1. ITU93 (Default)" );
    printf("\n 2. CHINA (Derived)\n" );
    printf("\n ->> " );
    scanf("%d", &var);

    if (var < 1 || var > 2)
    {
        var = 1;
    }

    if (var == 1)
    { 
        class = VAR_CreateClass(ISUP_ITU_GENERIC_93);
    } 
    else if (var == 2)
    { 
        class = VAR_CreateClass(ISUP_ITU_CHINA24);
    }

    /******************** Class Initialization functions ***************/
                                                                          
    if (class != NULL)
    {
        printf("\n Successfully created VariantClass\n");
        VAR_PrintRecord(class);
    }
    else
    {
        printf("\n Variant Class creat fail: exiting...\n");
        return ;
    }
        

    /*********************** Variant specific functions ****************/

    if (VAR_IsMsgCompInfoSupported(class))
    {
        printf(" \n Msg Comp Info Param Supported by Variant...\n");
    }
    else
    {
        printf(" Msg Comp Info Param NOT Supported by Variant...\n");
    }

    if (VAR_IsParamCompInfoSupported(class))
    {
        printf(" Param Comp Info Param Supported by Variant...\n");
    }
    else
    {
        printf(" Param Comp Info Param NOT Supported by Variant...\n");
    }

    if ((Timer = VAR_GetTimerInfo(class)) == NULL)
    {
        printf("\n No Timer Info in Record. "); 
    }
    else
    {
        printf("\n TimerInfo: %x", Timer);
        Timer++;
        printf("\n timer 1: val. %d, handler %d",
                            Timer->tmr_value, Timer->tmr_hndl_layer); 
    }

    printf("\n Enter any CIC" );
    printf("\n ->> " );
    scanf("%d", &cic);
    
    printf("\n No. of Cics/Ckgp: %d, FirstCic in Ckgp: %d",
               VAR_GetNumCICs_Ckgp(class),
               VAR_GetFirstCIC_Ckgp(class));

    VAR_GetCkgpFromCIC(class, cic, &index, &ckgp, &numCics);
    printf("\n CIC: %d, index %d, Ckgp: %d, CicsRemaining: %d", 
               VAR_GetCICFromCkgp(class, ckgp, index), 
               index, ckgp, numCics);

    cic = VAR_GetCICFromCkgp(class, ckgp, index); 
    if ((Timer = VAR_GetTimerInfo(class)) == NULL)
    {
        printf("\n No Timer Info in Record. "); 
    }
    else
    {
        printf("\n TimerInfo: %x", Timer);
        Timer++;
        printf("\n timer 1: val. %d, handler %d",
                            Timer->tmr_value, Timer->tmr_hndl_layer); 
    }
    /************************** Message specific functions ****************/

    while (keepGoing)
    {
        DisplayMsgMenu(&msg);

        switch (msg)
        {
        case  0:
             keepGoing = ITS_FALSE;
             break;

        case ISUP_MSG_ACM:    /* Address Complete  */
        case ISUP_MSG_ANM:    /* Answer  */
        case ISUP_MSG_CPG:    /* Call Progress */
        case ISUP_MSG_IAM:    /* Initial Address */
        case ISUP_MSG_PAM:    /* Pass Along */
        case ISUP_MSG_REL:    /* Release */
        case ISUP_MSG_RLC:    /* Release Complete */
        case ISUP_MSG_RSC:    /* Reset Circuit Message */

             DisplayStateMenu(&state);

             // Check if msg is supported
             if (VAR_IsMsgSupported(class, (ITS_OCTET)msg))
             {
                 printf(" Message %02x (hex), Supported \n", msg );
             }
             else
             {
                 printf(" Message %02x (hex), Not Supported \n", msg);
             }

             // Get the msg descriptor
             msg_desc = VAR_GetMsgDescription(class, (ITS_OCTET)msg);

             if (msg_desc != NULL)
             {
        
             }
             else
             {

             }
 
             if ((Func = VAR_GetMsgProc(class, msg, state)) == NULL)
             {
                 printf(" No func. entry in HashTable: msg %x, state %x \n",
                                                           msg, state);        
             }
             else
             {
                 printf(" msg %x, state %x, address %x \n", msg, state, Func);
             }
             break;

        default:
            // Call unrec. param handling procedure
             //Variant_HandleUnrecMsg(class);

        } // end of switch

    } // end of while keepGoing
                                                                               
}

