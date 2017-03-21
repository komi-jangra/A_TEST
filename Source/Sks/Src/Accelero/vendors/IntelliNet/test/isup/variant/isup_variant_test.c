/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: isup_variant_test.c,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:22  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:22  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:36  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/15 16:11:12  hbalimid
 * LOG: test program to test multiple variants
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>

#include <its.h>
#include <its_assertion.h>
#include <its_ss7_trans.h>

#include <isup_variants.h>
#include <isup_intern.h>
#include <itu/isup_97.h>
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
#endif


#if 0
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
                                                                               
    const char* className = ISUP_VariantToString(ISUP_ITU_97);
    ITS_Class varClass;
    ITS_USHORT i = 0;

    ITS_C_ASSERT(className != NULL);

    printf("Var Enum = %d\n", ISUP_StringToVariant(className));

    signal(SIGINT, exitHandler);

    ITS_AddFeature(itsSS7STACK_ClassCCITT);
    ITS_AddFeature(itsINTELLISS7_ClassCCITT);
    if (ITS_AddFeature(isupITU97_Class) != ITS_SUCCESS)
    {
        printf("AddFeature for %s failed\n", className); 
    }

    printf("Class Name = %s\n", className);
    varClass = ITS_FindFeature(className);
    ITS_C_ASSERT ( varClass != NULL );

    VAR_PrintRecord(varClass);


    /*********************** Variant specific functions ****************/

    if (VAR_IsMsgCompInfoSupported(varClass))
    {
        printf(" \n Msg Comp Info Param Supported by Variant...\n");
    }
    else
    {
        printf(" Msg Comp Info Param NOT Supported by Variant...\n");
    }

    if (VAR_IsParamCompInfoSupported(varClass))
    {
        printf(" Param Comp Info Param Supported by Variant...\n");
    }
    else
    {
        printf(" Param Comp Info Param NOT Supported by Variant...\n");
    }

    if ((Timer = VAR_GetTimerInfo(varClass)) == NULL)
    {
        printf("\n No Timer Info in Record. "); 
    }
    else
    {
        printf("\n TimerInfo: %x", Timer);
        for( i = 0; i < ISUP_NB_TIMERS; i++)
        {
            printf("\n timer %d: val. %d, handler %d",
                           i,  Timer[i].tmr_value, Timer[i].tmr_hndl_layer); 
            switch(Timer[i].tmr_hndl_layer)
            {
                case ISUP_TMR_HNDL_STACK:
                    printf("handled by STACK\n");
                    break;

                case ISUP_TMR_HNDL_APP:
                    printf("handled by APP\n");
                    break;

                case ISUP_TMR_HNDL_INVALID:
                    printf("handled by INVALID\n");
                    break;

                default:
                    printf("*** DEFAULT***\n");
                    break;
            }

        }

    }

    printf("\n Enter any CIC" );
    printf("\n ->> " );
    scanf("%d", &cic);
    
    printf("\n No. of Cics/Ckgp: %d, FirstCic in Ckgp: %d",
               VAR_GetNumCICs_Ckgp(varClass),
               VAR_GetFirstCIC_Ckgp(varClass));

    VAR_GetCkgpFromCIC(varClass, cic, &index, &ckgp, &numCics);
    printf("\n CIC: %d, index %d, Ckgp: %d, CicsRemaining: %d", 
               VAR_GetCICFromCkgp(varClass, ckgp, index), 
               index, ckgp, numCics);

    cic = VAR_GetCICFromCkgp(varClass, ckgp, index); 
    printf("\n cic = %d\tckgp = %d\n", cic, ckgp);

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
             if (VAR_IsMsgSupported(varClass, (ITS_OCTET)msg))
             {
                 printf(" Message %02x (hex), Supported \n", msg );
             }
             else
             {
                 printf(" Message %02x (hex), Not Supported \n", msg);
             }

             // Get the msg descriptor
             msg_desc = VAR_GetMsgDescription(varClass, (ITS_OCTET)msg);

             if (msg_desc != NULL)
             {
        
             }
             else
             {

             }
 
             if ((Func = VAR_GetMsgProc(varClass, msg, state)) == NULL)
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
             //Variant_HandleUnrecMsg(varClass);

        } // end of switch

    } // end of while keepGoing

}
