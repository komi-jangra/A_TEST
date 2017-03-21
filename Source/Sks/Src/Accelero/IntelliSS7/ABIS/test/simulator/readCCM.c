/***************************************************************************
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
 *  ID: $Id: readCCM.c,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $ 
 *
 *  $Log: not supported by cvs2svn $
 *  Revision 1.1.1.1  2007/10/04 13:23:39  bsccs2
 *  init tree
 *
 *  Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 *  BscCs2
 *
 *  Revision 1.1.1.1  2007/03/08 15:12:53  cvsadmin
 *  BSC project
 *
 *  Revision 1.1.2.3  2005/09/27 12:22:25  mkrishna
 *  Modification done for Error cases - hakshata & raghavendrasm
 *
 *  Revision 1.1.2.2  2005/09/23 07:11:54  mkrishna
 *  Enhancements for Bugs raised - hakshata & sriraghavendrasm
 *
 *  Revision 1.1.2.1  2005/08/29 08:59:39  mkrishna
 *  Added codec simulator - hakshata & sriraghavendrasm
 *
 *
 ****************************************************************************/

#include <abis_traffic_management.h>

extern FILE *fp;
extern char filename[20];

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Bcch information elements from the file,
        encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name            Date           Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
HandleBcchInfo(int choice)
{  
    FILE *fp;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fptr;
    char line[1024]; 
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    ReadBcchInfo(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding BcchInfo Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    printf("*********** ENCODED DATA  *************************\n");  
    {
        printf("Encoding BcchInfo Success  ret :: %d\n\n", ret);
        // display buffer 
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("******************* DECODED DATA **************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding BcchInfo Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding BcchInfo Success  ret :: %d\n", ret);
        // display buffer 
                                                    
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n", 
                                    msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanlBits       :   0x%02x\n", 
                            msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                           msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);
        printf("sysInfoField    :   0x%02x\n", 
                                      msg.u.ccmMsg.u.bcchInfo.sysInfoType);
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"BCCHINF START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "BCCHINF END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("fullBcch        :   0x%02x\n", 
                                      msg.u.ccmMsg.u.bcchInfo.fullBcch.length);
                        printf("msg[0]          :   0x%02x\n", 
                                      msg.u.ccmMsg.u.bcchInfo.fullBcch.msg[0]);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-2"))
                    {
                        printf("startingtime    :   0x%02x\n", 
                                         msg.u.ccmMsg.u.bcchInfo.startingTime);
                    }
                }
                break;
            }
        }    
        fclose(fptr); 
   } 
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Bcch information elements from the file and assigning these
	values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name            Date           Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
ReadBcchInfo(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0,icount, k =0, kcount,j ;
    char c, str[10], str1[10], str2[10], str3[10],str4[10], str5[10];
    char str6[10] ,str7[10], str8[10],str9[10];
    unsigned char buffer[100];
    unsigned char temp[100],temp1;
    long l[100], l1;
    int optional[10];
    int tot_elem = 0;
    int param = 0;
    printf("                        \n");
    printf("MESSAGE CATEGORY:CHANNEL MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        CLEAR_TM_CCM_BI_OPTIONAL_BIT_MAP(msg);
        if (strcmp(line,"BCCHINF START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "BCCHINF END\n") != 0)
            {
                if ( line[0] == 'M' || line[0] == 'O')
                {
                    if(line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }


                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_TM_CCM_BI_FULL_BCCH_INFO(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.bcchInfo.fullBcch.length = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for(j = 0;
                                j < msg->u.ccmMsg.u.bcchInfo.fullBcch.length ; 
                                j++ )
                            {
                                msg->u.ccmMsg.u.bcchInfo.fullBcch.msg[j] = 
                                                                   temp[i];
                            }
                        }
                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-2"))
                {
                    optional[2] = 2;
                    SET_TM_CCM_BI_STARTING_TIME(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.bcchInfo.startingTime = temp[i];
                        }

                    }
                }
                printf("%s",line);
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
    		    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab = (char *)strtok(NULL,"\t");
                    tokenspace = (char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                         bufspace[k] = 
                         (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                         strcpy(*(bufspace+k),tokenspace);
                         k++;
                         tokenspace = (char *)strtok(NULL," ");
                    }
                }
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    printf("kcount is %d\n",kcount);
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||  
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
        {
        }
        else
        {
            printf("input not in correct format\n");
        }

        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k==0)
        {

             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc         :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
        
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)      :   0x%02x\n",
                          msg->genElemnts.msgDesc.trasparent);
        }
        if (k==2)
        {
             msg->genElemnts.msgType=temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k==3)
        {
             msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",
                           msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        }
        if (k==4)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum=temp[k];
            printf("timeSlotNum     :   0x%02x\n", 
                            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
        }
        if (k==5)
        {
             msg->u.trxmMsg.u.sacchFill.sysInfoType = temp[k];
             printf("sysInfoType     :   0x%02x\n",
                                    msg->u.trxmMsg.u.sacchFill.sysInfoType); 
        }
}
 
    if (optional[1] == 1)
    {
        printf("length          :   0x%02x\n", 
                                   msg->u.ccmMsg.u.bcchInfo.fullBcch.length);
        printf("msg[0]          :   0x%02x\n", 
                                   msg->u.ccmMsg.u.bcchInfo.fullBcch.msg[0]);
    }
    if (optional[2] == 2)
    {
        printf("startingtime    :   0x%02x\n",
                                     msg->u.ccmMsg.u.bcchInfo.startingTime); 
    } 
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Ccch Load Indication information elements from the
        file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
*       fp - file pointer where the values for the elems are fed

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
HandleCcchLdInd(int choice)
{   
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;
    FILE *fptr;
    char line[1024];
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    ReadCcchLdInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding CcchLoadIndication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("***************** ENCODED DATA *******************\n");     
        printf("Encoding CcchLoadIndication Success  ret :: %d\n\n", ret);
        // display buffer 
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("***************** DECODED DATA *************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding CcchLoadIndication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding CcchLoadIndication Success  ret :: %d\n", ret);
        // display buffer 
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", 
                                         msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", 
                                       msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
	printf("chanlBits       :   0x%02x\n", 
                               msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                             msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"CCCHLDIND START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "CCCHLDIND END\n") != 0)
                {
                    if (line[0] == 'C' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Conditional-1"))
                    {
                        printf("length          :   0x%02x\n", 
                                       msg.u.ccmMsg.u.ccchLoadInd.rach.length);
                        printf("info[0]        :   0x%02x\n", 
                                     msg.u.ccmMsg.u.ccchLoadInd.rach.info[0]);

                        printf("slotCount       :   0x%02x\n", 
                                   msg.u.ccmMsg.u.ccchLoadInd.rach.slotCount);
                        printf("bysyCount       :   0x%02x\n", 
                                    msg.u.ccmMsg.u.ccchLoadInd.rach.busyCount);
                        printf("accessCount     :   0x%02x\n", 
                                  msg.u.ccmMsg.u.ccchLoadInd.rach.accessCount);
                     }

                    

                    if (line[0] == 'C' && line[1] == '\t' && line[2] == '0'
                    && strstr(line,"Conditional-2"))
                    {
                        printf("pagBufSpace     :   0x%02x\n", 
                                       msg.u.ccmMsg.u.ccchLoadInd.pagBufSpace);
                    } 

                }
                break;
            }
        }    
        fclose(fptr); 
    } 
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Ccch Load Indication elements from the file and assigning
        these values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
ReadCcchLdInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0,icount, k =0, kcount,j ;
    char c, str[10], str1[10], str2[10], str3[10],str4[10], str5[10];
    char str6[10] ,str7[10], str8[10],str9[10];
    unsigned char buffer[100];
    unsigned char temp[100],temp1;
    long l[100], l1;
    int conditional[10];
    int tot_elem = 0;
    int param = 0;
    printf("                        \n");
    printf("MESSAGE CATEGORY:COMMON CHANNEL MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(conditional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"CCCHLDIND START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "CCCHLDIND END\n") != 0)
            {
                if ( line[0] == 'M' || line[0] == 'O')
                {
                    if(line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }


                /***CONDITIIONAL BITS  ******/  
                if (line[0]=='C' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"Conditional-1"))
                {
                    conditional[1] = 1;
                    sscanf(line,"%c %s %s %s %s %s",
                       &c,&str,&str1,&str2,&str3,&str4);
                    for (i = 0; i < 10; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.ccchLoadInd.rach.length = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0;
        j <  msg->u.ccmMsg.u.ccchLoadInd.rach.length ; j++ )
                            {
                   msg->u.ccmMsg.u.ccchLoadInd.rach.info[j] = temp[i];
                             }
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.ccchLoadInd.rach.slotCount=temp[i]; 
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.ccchLoadInd.rach.busyCount=temp[i]; 
                        }
                        if (i == 4)
                        {
                            l[i] = strtol(str4,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.ccchLoadInd.rach.accessCount = 
                                                                   temp[i]; 
                        }
                    }
                    
                }
                if (line[0]=='C' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Conditional-2"))
                {
                    {
                        conditional[2] = 2;
                        sscanf(line,"%c %s",&c,&str);
                        for (i = 0; i < 2; i++)
                        {
                            if (i == 0)
                            {
                                l[i] = strtol(str,NULL,16);
                                temp[i] = (unsigned char)l[i];
                                msg->u.ccmMsg.u.ccchLoadInd.pagBufSpace = 
                                                                  temp[i];  
                            }
                        }
                    }
                }
                printf("%s",line);
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
    		    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab = (char *)strtok(NULL,"\t");
                    tokenspace = (char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                         bufspace[k] = 
                         (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                         strcpy(*(bufspace+k),tokenspace);
                         k++;
                         tokenspace = (char *)strtok(NULL," ");
                    }
                }
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    printf("kcount is %d\n",kcount);
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||  
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
        {
        }
        else
        {
            printf("input not in correct format\n");
        }

        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k==0)
        {

             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc         :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
        
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)      :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
        if (k==2)
        {
             msg->genElemnts.msgType=temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k==3)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits        :   0x%02x\n",
                            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        }
        if (k==4)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum    :   0x%02x\n", 
                         msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
        }

}
        printf("length         :   0x%02x\n", 
                                   msg->u.ccmMsg.u.ccchLoadInd.rach.length);
        printf("info[0]        :   0x%02x\n", 
                                   msg->u.ccmMsg.u.ccchLoadInd.rach.info[0]);
        printf("slotCount      :   0x%02x\n",
                                 msg->u.ccmMsg.u.ccchLoadInd.rach.slotCount);
        printf("busyCount      :   0x%02x\n", 
                                 msg->u.ccmMsg.u.ccchLoadInd.rach.busyCount);
        printf("accessCount    :   0x%02x\n",
                               msg->u.ccmMsg.u.ccchLoadInd.rach.accessCount);
        printf("pagBufSpace    :   0x%02x\n", 
                                    msg->u.ccmMsg.u.ccchLoadInd.pagBufSpace);  
        fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Channel Required information elements from the
        file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
*       fp - file pointer where the values for the elems are fed

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
HandleChanlRqd(int choice)
{  
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;
    FILE *fptr;
    char line[1024];
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    ReadChanlRqd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Channel Required Failed  ret :: %d\n", ret);
        return ret;
    }
    else

    printf("************** ENCODED DATA ******************************\n");

    {
        printf("Encoding Channel Required Success  ret :: %d\n\n", ret);
        // display buffer 
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    printf("********************* DECODED DATA *********************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Channel Requred Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Channel Required Success  ret :: %d\n", ret);

// display buffer 
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc           :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)        :   0x%02x\n", 
                                        msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType           :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanlBits         :   0x%02x\n", 
                                msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum       :   0x%02x\n", 
                              msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);
        printf("RA(Random Access) :   0x%02x\n", msg.u.ccmMsg.u.chanRqd.RA);
        printf("reqRefNum         :   0x%02x\n", msg.u.ccmMsg.u.chanRqd.reqRefNum);
        printf("accessDelay       :   0x%02x\n", msg.u.ccmMsg.u.chanRqd.accessDelay);

        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"CHANRQD START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "CHANRQD END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("length            :   0x%02x\n", 
                                      msg.u.ccmMsg.u.chanRqd.phyContext.length);
                        printf("content[0]      :   0x%02x\n",
                              msg.u.ccmMsg.u.chanRqd.phyContext.content[0]);
                    }

                }
                break;
            }
        }    
        fclose(fptr); 
   } 
    return ITS_SUCCESS;
}


/*implementation:internal
*
* PURPOSE:
*       Reading the Channel Request elements from the file and assigning
*       these values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
ReadChanlRqd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0,icount, k =0, kcount,j ;
    char c, str[10], str1[10], str2[10], str3[10],str4[10], str5[10];
    char str6[10] ,str7[10], str8[10],str9[10];
    unsigned char buffer[100];
    unsigned char temp[100],temp1;
    long l[100], l1;
    int optional[10];
    int tot_elem = 0;
    int param = 0;
    printf("                        \n");
    printf("MESSAGE CATEGORY:COMMON CHANNEL MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        CLEAR_TM_CCM_CR_OPTIONAL_BIT_MAP(msg);
        if (strcmp(line,"CHANRQD START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "CHANRQD END\n") != 0)
            {
                if ( line[0] == 'M' || line[0] == 'O')
                {
                    if(line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }


                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_TM_CCM_CR_PHYSICAL_CONTEXT(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                             msg->u.ccmMsg.u.chanRqd.phyContext.length = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0;
        j < msg->u.ccmMsg.u.chanRqd.phyContext.length ; j++ )
                            {
                    msg->u.ccmMsg.u.chanRqd.phyContext.content[j] = temp[i];
                             }
                        }                       
                            
                    }
                }

                printf("%s",line);
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
    		    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab = (char *)strtok(NULL,"\t");
                    tokenspace = (char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                         bufspace[k] = 
                         (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                         strcpy(*(bufspace+k),tokenspace);
                         k++;
                         tokenspace = (char *)strtok(NULL," ");
                    }
                }
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    printf("kcount is %d\n",kcount);
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||  
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
        {
        }
        else
        {
            printf("input not in correct format\n");
        }

        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k==0)
        {

             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc         :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
        
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)      :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
        if (k==2)
        {
             msg->genElemnts.msgType=temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k==3)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits        :   0x%02x\n",
                            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        }
        if (k==4)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum    :   0x%02x\n", 
                         msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
        }
        if (k==5)
	        {
        	     msg->u.ccmMsg.u.chanRqd.RA = temp[k];
	             printf("RA(RandomAccess) :   0x%02x\n",
                                         msg->u.ccmMsg.u.chanRqd.RA);
	        }

	if (k==6)
	        {
        	    msg->u.ccmMsg.u.chanRqd.reqRefNum = temp[k];
	            printf("reqRefNum        :   0x%02x\n",
                                     msg->u.ccmMsg.u.chanRqd.reqRefNum);
	        }
	 if (k==7)
	        {
        	    msg->u.ccmMsg.u.chanRqd.accessDelay = temp[k];
	            printf("accessDelay      :   0x%02x\n", 
                                        msg->u.ccmMsg.u.chanRqd.accessDelay);
	        }

}
    if (optional[1] == 1)
    {
        printf("length           :   0x%02x\n",
                            msg->u.ccmMsg.u.chanRqd.phyContext.length);
        printf("content[0]       :   0x%02x\n",
                            msg->u.ccmMsg.u.chanRqd.phyContext.content[0]);
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Delete Indication information elements from the
        file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
*       fp - file pointer where the values for the elems are fed

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/

ITS_INT
HandleDelInd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadDelInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    printf("****************** ENCODED DATA ************************\n");
    {
        printf("Encoding Data Request Success  ret :: %d\n\n", ret);
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }


    printf("****************** DECODED DATA ***************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Data Request Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", 
                                     msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                   msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n",msg.genElemnts.msgType);
        printf("chanlBits       :   0x%02x\n",
                       msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n",
                     msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);
        printf("length          :   0x%02x\n",
                                      msg.u.ccmMsg.u.deleteInd.length);
        printf("assignInfo[0]   :   0x%02x\n",
                               msg.u.ccmMsg.u.deleteInd.assignInfo[0]);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the Delete Indication elements from the file and assigning
*       these values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/

ITS_INT
ReadDelInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE * fp)
{
    FILE *fp_ch;
    char line[1024];
    char *tokentab;
    char *tokenspace;
    char *buftab[300];
    char *bufspace[300];
    int i = 0,icount;
    int k = 0,kcount;
    int no_params = 9;
    int linecount = 0;
    char c,d_tab,e_opt;
    unsigned char buffer[300];
    unsigned char temp;
    long l;
    int l3count;
    fp_ch = fopen(filename,"r");

    if (!fp_ch)
    {
        printf("Error opening the file\n");
        exit(1);
    }

    printf("                        \n");
    printf("Message Name: DELETE INDICATION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while((c = fgetc(fp_ch)) != EOF)
    {
        if (c == '\n')
        linecount++;
        if(c=='M')
        {
            d_tab = fgetc(fp_ch);
            if (d_tab == '\t')
            {

            }

            else if(d_tab == ' ')
            {
                printf("Tab space needed after the"
                        "mandatory parameter at line %d\n",linecount);
                exit(1);
            }
        }

        if (c == 'O')
        {
            d_tab = fgetc(fp_ch);
            if (d_tab == '\t')
            {
                e_opt = fgetc(fp_ch);
                if (e_opt == '0')
                no_params = 9;  
                else
                no_params = 8;
            }

            else if(d_tab == ' ')
            {
                printf("Tab space needed after the optional" 
                        "parameter at line %d\n",linecount);
                exit(1);
            }
        }
    }
    fclose(fp_ch);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"DELIND START\n") == 0)
        {

            while (strcmp(fgets(line,sizeof(line),fp),"DELIND END\n") != 0)
            {
                printf("%s",line);
                tokentab=(char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
                    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab=(char *)strtok(NULL,"\t");
                    tokenspace=(char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                        bufspace[k] = 
                        (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                        strcpy(*(bufspace+k),tokenspace);
                        k++;
                        tokenspace=(char *)strtok(NULL," ");
                    }
                }
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    if (kcount == no_params)
    {

    }
    else
    {
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");   
    printf("MESSAGE NAME: DELETE INDICATION\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0; k<kcount; k++)
    {
        if (bufspace[k][0] != '0' && bufspace[k][1] != 'x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' 
        ||  bufspace[k][2] >= '0' && bufspace[k][2] <= '9' 
        && bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' 
        || bufspace[k][3] >= '0' && bufspace[k][3] <= '9' )

        {

        }
        else
        {
            printf("input not in correct format\n");
        }

        if (k == 0)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->genElemnts.msgDesc.msgGruop = temp;
            printf("msgDesc         :   0x%02x\n",
                                     msg->genElemnts.msgDesc.msgGruop);
        }

        if (k == 1)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->genElemnts.msgDesc.trasparent = temp;
            printf("msgdesc(T)      :   0x%02x\n",
                                    msg->genElemnts.msgDesc.trasparent);
        }

        if (k == 2)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->genElemnts.msgType = temp;
            printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }

        if (k == 3)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits = temp;
            printf("chanBits        :   0x%02x\n",
                         msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        }

        if (k == 4)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum = temp;
            printf("timeSlotNum     :   0x%02x\n", 
                     msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
        }

        if (k == 5)						
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.u.deleteInd.length = temp;
            printf("length          :   0x%02x\n", 
                                        msg->u.ccmMsg.u.deleteInd.length);
        }

        if (k == 6)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            for(i = 0; i < msg->u.ccmMsg.u.deleteInd.length; i++ )
            {
                msg->u.ccmMsg.u.deleteInd.assignInfo[i] = temp;
            }
            printf("assignInfo[0]   :   0x%02x\n",
                                 msg->u.ccmMsg.u.deleteInd.assignInfo[0]);
        }
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Immidiate Assignment Command information elements
        from the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
*       fp - file pointer where the values for the elems are fed

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/

ITS_INT
HandleImmdAssgCmd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadImmdAssgCmd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {

        printf("Encoding Immidiate Assign Command  Failed ret :: %d\n", ret);
        return ret;
    }
    else
    printf("********************** ENCODED DATA ************************\n");
    {
        printf("Encoding Immidiate Assign Command Success ret::%d\n\n", ret);
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }


    printf("***************** DECODED DATA *************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Immidiate Assign Command Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Immidiate Assign Command Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                           msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                         msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanlBits       :   0x%02x\n", 
                            msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                          msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);
        printf("length          :   0x%02x\n",
                                      msg.u.ccmMsg.u.immdAssignCmd.length);
        printf("assignInfo[0]   :   0x%02x\n",
                                msg.u.ccmMsg.u.immdAssignCmd.assignInfo[0]);
        printf("assignInfo[1]   :   0x%02x\n", 
                                msg.u.ccmMsg.u.immdAssignCmd.assignInfo[1]);
        printf("assignInfo[2]   :   0x%02x\n",
                                msg.u.ccmMsg.u.immdAssignCmd.assignInfo[2]);
        printf("assignInfo[3]   :   0x%02x\n",
                                msg.u.ccmMsg.u.immdAssignCmd.assignInfo[3]);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the Immidiate Assign Command elements from the file and
*       assigning these values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
ReadImmdAssgCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE * fp)
{
    FILE *fp_ch;
    char line[1024];
    char *tokentab;
    char *tokenspace;
    char *buftab[300];
    char *bufspace[300];
    int i = 0,icount;
    int k = 0,kcount;
    int no_params = 10;
    int linecount = 0;
    char c,d_tab,e_opt;
    unsigned char buffer[300];
    unsigned char temp;
    long l;
    int l3count;
    fp_ch=fopen(filename,"r");

    if (!fp_ch)
    {
        printf("Error opening the file\n");
        exit(1);
    }


    printf("                        \n");
    printf("Message Name: Immidiate Assign Command \n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(( c = fgetc(fp_ch)) != EOF)
    {
        if (c == '\n')
        linecount++;
        if(c == 'M')
        {
            d_tab = fgetc(fp_ch);
            if (d_tab == '\t')
            {

                /* printf("mandatory field ocuurred\n");*/
            }

            else if (d_tab == ' ')
            {
                printf("Tab space needed after the "
                        "mandatory parameter at line %d\n",linecount);
                exit(1);
            }
        }

        if (c == 'O')
        {
            d_tab = fgetc(fp_ch);
            if (d_tab == '\t')
            {
                /* printf("optional field ocuurred\n"); */
                e_opt = fgetc(fp_ch);
                if(e_opt == '0')
                no_params = 10;
                else
                no_params = 9;
            }


            else if(d_tab == ' ')
            {
                printf("Tab space needed after the" 
                        "optional parameter at line %d\n",linecount);
                exit(1);
            }

        }
    }
    fclose(fp_ch);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"IMMASGCMD START\n") == 0)
        {

            while (strcmp(fgets(line,sizeof(line),fp),"IMMASGCMD END\n") != 0)
            {
                printf("%s",line);
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
                    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab = (char *)strtok(NULL,"\t");

                    tokenspace = (char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                        bufspace[k] = 
                        (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                        strcpy(*(bufspace+k),tokenspace);
                        k++;
                        tokenspace = (char *)strtok(NULL," ");
                    }

                }
            }
            break;
        }

    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    if (kcount == no_params)
    {


    }
    else
    {
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n"); 
    printf("MESSAGE NAME: IMMIDIATE ASSIGN COMMAND\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0; k<kcount; k++)
    {

        if(bufspace[k][0] != '0' && bufspace[k][1] != 'x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f'
        ||  bufspace[k][2] >= '0' && bufspace[k][2] <= '9'
        && bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f'
        || bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
        {


        }
        else
        {
            printf("input not in correct format\n");
        }


        if (k == 0)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->genElemnts.msgDesc.msgGruop = temp;
            printf("msgDesc         :   0x%02x\n",
                                 msg->genElemnts.msgDesc.msgGruop);

        }

        if (k == 1)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->genElemnts.msgDesc.trasparent = temp;
            printf("msgdesc(T)      :   0x%02x\n",
                                   msg->genElemnts.msgDesc.trasparent);
        }

        if (k == 2)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->genElemnts.msgType = temp;
            printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }

        if (k == 3)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits = temp;
            printf("chanBits        :   0x%02x\n",
                          msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        }

        if (k == 4)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum = temp;
            printf("timeSlotNum     :   0x%02x\n",
                       msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
        }

        if (k == 5)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.u.immdAssignCmd.length = temp;
            printf("length          :   0x%02x\n",
                                    msg->u.ccmMsg.u.immdAssignCmd.length);
        }

        if (k == 6)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.u.immdAssignCmd.assignInfo[0] = temp;
            printf("assignInfo[0]   :   0x%02x\n",
                              msg->u.ccmMsg.u.immdAssignCmd.assignInfo[0]);
        }

        if (k == 7)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.u.immdAssignCmd.assignInfo[1] = temp;
            printf("assignInfo[1]   :   0x%02x\n",
                                 msg->u.ccmMsg.u.immdAssignCmd.assignInfo[1]);
        }

        if (k == 8)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.u.immdAssignCmd.assignInfo[2] = temp;
            printf("assignInfo[2]   :   0x%02x\n",
                              msg->u.ccmMsg.u.immdAssignCmd.assignInfo[2]);
        }


        if (k == 9)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.ccmMsg.u.immdAssignCmd.assignInfo[3] = temp;
            printf("assignInfo[3]   :   0x%02x\n",
                            msg->u.ccmMsg.u.immdAssignCmd.assignInfo[3]);
        }
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Paging Command information elements
        from the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
*       fp - file pointer where the values for the elems are fed

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/

ITS_INT
HandlePageCmd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;
    FILE *fptr;
    char line[1024];
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadPageCmd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Paging Command  Failed  ret :: %d\n", ret);
        return ret;
    }
    else

    printf("******************* ENCODED DATA ***********************\n");
    {
        printf("Encoding Paging Command  Success  ret :: %d\n\n", ret);
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }


    printf("**************** DECODED DATA ***************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Paging Command  Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Paging Command Success  ret :: %d\n", ret);

        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                       msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                     msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n",msg.genElemnts.msgType);

        printf("chanlBits       :   0x%02x\n",
                         msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);

        printf("timeSlotNum     :   0x%02x\n",
                       msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);

        printf("pagingGroup     :   0x%02x\n",
                                   msg.u.ccmMsg.u.pagingCmd.pagingGroup);

        printf("length          :   0x%02x\n",
                             msg.u.ccmMsg.u.pagingCmd.msIdentity.length);
        printf("identity[0]     :   0x%02x\n",
                         msg.u.ccmMsg.u.pagingCmd.msIdentity.identity[0]);
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"PAGCMD START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "PAGCMD END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("chanlNeed       :   0x%02x\n",
                                         msg.u.ccmMsg.u.pagingCmd.chanlNeed);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-2"))
                    {
                        printf("callPriority    :   0x%02x\n",
                                     msg.u.ccmMsg.u.pagingCmd.callPriority);
                    }

                }
                break;
            }
        }    
        fclose(fptr); 
   } 
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Paging Command elements from the file and assigning 
*       these values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
ReadPageCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0,icount, k =0, kcount,j ;
    char c, str[10], str1[10], str2[10], str3[10],str4[10], str5[10];
    char str6[10] ,str7[10], str8[10],str9[10];
    unsigned char buffer[100];
    unsigned char temp[100],temp1;
    long l[100], l1;
    int optional[10];
    int tot_elem = 0;
    int param = 0;
    printf("                        \n");
    printf("MESSAGE CATEGORY:CHANNEL MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        CLEAR_TM_CCM_PC_OPTIONAL_BIT_MAP(msg);
        if (strcmp(line,"PAGCMD START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "PAGCMD END\n") != 0)
            {
                if ( line[0] == 'M' || line[0] == 'O')
                {
                    if(line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }


                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_TM_CCM_PC_CHANNEL_NEEDED(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.pagingCmd.chanlNeed = temp[i];
                        }

                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-2"))
                {
                    optional[2] = 2;
                    SET_TM_CCM_PC_EMLPP_PRIORITY(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.pagingCmd.callPriority = temp[i];
                        }

                    }
                }
                printf("%s",line);
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
    		    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab = (char *)strtok(NULL,"\t");
                    tokenspace = (char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                         bufspace[k] = 
                         (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                         strcpy(*(bufspace+k),tokenspace);
                         k++;
                         tokenspace = (char *)strtok(NULL," ");
                    }
                }
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    printf("kcount is %d\n",kcount);
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||  
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
        {
        }
        else
        {
            printf("input not in correct format\n");
        }

        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k == 0)
        {

             msg->genElemnts.msgDesc.msgGruop = temp[k];
             printf("msgDesc         :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
        
        if (k == 1)
        {
             msg->genElemnts.msgDesc.trasparent = temp[k];
             printf("msgdesc(T)      :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
             msg->genElemnts.msgType = temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
	if (k == 3)
       	{
	    msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits=temp[k];
     	    printf("chanBits        :   0x%02x\n",
                          msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
	}
        if (k == 4)
      	{
	    msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum = temp[k];
      	    printf("timeSlotNum     :   0x%02x\n", 
                         msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
	}
	if (k == 5)
        {
	    msg->u.ccmMsg.u.pagingCmd.pagingGroup = temp[k]; 
       	    printf("pagingGroup     :   0x%02x\n",
                                    msg->u.ccmMsg.u.pagingCmd.pagingGroup);
	}
        if (k == 6)
        {
	    msg->u.ccmMsg.u.pagingCmd.msIdentity.length = temp[k];  
       	    printf("length          :   0x%02x\n", 
                              msg->u.ccmMsg.u.pagingCmd.msIdentity.length);
	}
        if (k==7)
        {
            printf("identity[0]     :   0x%02x\n",temp[k]);
            for( i = 0; i < msg->u.ccmMsg.u.pagingCmd.msIdentity.length; i++ )
            {
                msg->u.ccmMsg.u.pagingCmd.msIdentity.identity[i] = temp[k]; 
            }
        }
}
 
    if (optional[1] == 1)
    {
        printf("chanlNeed       :   0x%02x\n",
                                msg->u.ccmMsg.u.pagingCmd.chanlNeed);
    }
    if (optional[2] == 2)
    {
        printf("callPriority    :   0x%02x\n",
                                 msg->u.ccmMsg.u.pagingCmd.callPriority);
    } 
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the SMSBroadcast Request information elements
        from the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
*       fp - file pointer where the values for the elems are fed

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
HandleSmsBrdcastReq(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE * fp;
    FILE *fptr;
    char line[1024]; 
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadSmsBrdcastReq(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding SMS Broadcast Failed  ret :: %d\n", ret);
        return ret;
    }
    else

    printf("***************** ENCODED DATA *************************\n");
    {
        printf("Encoding SMS Broadcast  Success  ret :: %d\n\n", ret);
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("***************** DECODED DATA ***************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SMS Broadcast  Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding SMS Broadcast Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                         msg.genElemnts.msgDesc.msgGruop);  
        printf("msgDesc(T)      :   0x%02x\n",
                                       msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n",msg.genElemnts.msgType);
        printf("chanlBits       :   0x%02x\n",
                           msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n",
                         msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);
        printf("InfoLen         :   0x%02x\n",
                                      msg.u.ccmMsg.u.smsBcReq.smscbInfoLen);
        printf("smscbInfoLen[0] :   0x%02x\n",
                                     msg.u.ccmMsg.u.smsBcReq.smscbInfo[0]);
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"SMSBDREQ START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "SMSBDREQ END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                      printf("chanlInd        :   0x%02x\n",                                                                msg.u.ccmMsg.u.smsBcReq.chanlInd );
                    }

                }
                break;
            }
        }    
        fclose(fptr); 
   } 
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the SMSBroadcast request elements from the file and assigning
*       these values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
ReadSmsBrdcastReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE * fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0,icount, k =0, kcount,j ;
    char c, str[10], str1[10], str2[10], str3[10],str4[10], str5[10];
    char str6[10] ,str7[10], str8[10],str9[10];
    unsigned char buffer[100];
    unsigned char temp[100],temp1;
    long l[100], l1;
    int optional[10];
    int tot_elem = 0;
    int param = 0;
    printf("                        \n");
    printf("MESSAGE CATEGORY:COMMON CHANNEL MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    CLEAR_TM_CCM_SBR_OPTIONAL_BIT_MAP(msg);
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"SMSBDREQ START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "SMSBDREQ END\n") != 0)
            {
                if ( line[0] == 'M' || line[0] == 'O')
                {
                    if(line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }


                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_TM_CCM_SBR_SMSCB_CHANNEL_IND(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.smsBcReq.chanlInd = temp[i];
                        }
                    }
                }

                printf("%s",line);
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
    		    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab = (char *)strtok(NULL,"\t");
                    tokenspace = (char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                         bufspace[k] = 
                         (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                         strcpy(*(bufspace+k),tokenspace);
                         k++;
                         tokenspace = (char *)strtok(NULL," ");
                    }
                }
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    printf("kcount is %d\n",kcount);
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||  
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
        {
        }
        else
        {
            printf("input not in correct format\n");
        }

        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k==0)
        {

             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc         :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
        
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)      :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
        if (k==2)
        {
             msg->genElemnts.msgType=temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k==3)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits        :   0x%02x\n",
                            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        }
        if (k==4)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum    :   0x%02x\n", 
                         msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
        }
        if (k==5)
        {
            msg->u.ccmMsg.u.smsBcReq.smscbInfoLen = temp[k];
            printf("smsInfoLen      :   0x%02x\n",
                                     msg->u.ccmMsg.u.smsBcReq.smscbInfoLen);
        }

        if (k==6)
        {
            printf("Info[0]         :   0x%02x\n", temp[k]);
            for (i = 0; i < msg->u.ccmMsg.u.smsBcReq.smscbInfoLen ; i++  )
            {
                msg->u.ccmMsg.u.smsBcReq.smscbInfo[i] = temp[k];
            }

        }

}
    if (optional[1] == 1)
    {
        printf("chanInd        :   0x%02x\n",
                                     msg->u.ccmMsg.u.smsBcReq.chanlInd);
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the SMSBroadcast Command information elements
        from the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
*       fp - file pointer where the values for the elems are fed

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/

ITS_INT
HandleSmsBrdcastCmd(int choice)
{   
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;
    FILE *fptr;
    char line[1024];
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    ReadSmsBrdcastCmd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding SMS Broadcast Command Failed  ret :: %d\n", ret);
        return ret;
    }
    else

    printf("**************** ENCODED DATA ******************************\n");
    {
        printf("Encoding SMS Broadcast Command  Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("***************** DECODED DATA *****************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SMS Broadcast Command Failed  ret :: %d\n", ret);
         return ret;
    }
    else
    {
        printf("Decoding SMS Broadcast Command Success  ret :: %d\n", ret);
        // display buffer
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                    msg.genElemnts.msgDesc.msgGruop);   
        printf("msgDesc(T)      :   0x%02x\n",
                                    msg.genElemnts.msgDesc.trasparent);
	printf("msgType         :   0x%02x\n",msg.genElemnts.msgType);
        printf("chanlBits       :   0x%02x\n",
                                msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n",
                                msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);
        printf("command         :   0x%02x\n",
                                msg.u.ccmMsg.u.smsBcCmd.cmdType.command);
        printf("Broadcast       :   0x%02x\n",
                                msg.u.ccmMsg.u.smsBcCmd.cmdType.broadcast);
        printf("lastlock        :   0x%02x\n",
                                msg.u.ccmMsg.u.smsBcCmd.cmdType.lastlock);
        printf("length          :   0x%02x\n",
                                msg.u.ccmMsg.u.smsBcCmd.smscbMsg.length);
        printf("msg[0]          :   0x%02x\n",
                                msg.u.ccmMsg.u.smsBcCmd.smscbMsg.msg[0]);   
        
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"SMSBDCMD START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "SMSBDCMD END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                      printf("chanlInd        :   0x%02x\n",    
                                         msg.u.ccmMsg.u.smsBcCmd.chanlInd );
                    }

                }
                break;
            }
        }    
        fclose(fptr); 
   } 
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the SMSBroadcast Command elements from the file and assigning
*       these values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
ReadSmsBrdcastCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE * fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0,icount, k =0, kcount,j ;
    char c, str[10], str1[10], str2[10], str3[10],str4[10], str5[10];
    char str6[10] ,str7[10], str8[10],str9[10];
    unsigned char buffer[100];
    unsigned char temp[100],temp1;
    long l[100], l1;
    int optional[10];
    int tot_elem = 0;
    int param = 0;
    printf("                        \n");
    printf("MESSAGE CATEGORY:COMMON CHANNEL MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        CLEAR_TM_CCM_SBC_OPTIONAL_BIT_MAP(msg);
        if (strcmp(line,"SMSBDCMD START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "SMSBDCMD END\n") != 0)
            {
                if ( line[0] == 'M' || line[0] == 'O')
                {
                    if(line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }


                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_TM_CCM_SBC_SMSCB_CHANNEL_IND(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.smsBcCmd.chanlInd = temp[i];
                        }
                    }
                }

                printf("%s",line);
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
    		    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab = (char *)strtok(NULL,"\t");
                    tokenspace = (char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                         bufspace[k] = 
                         (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                         strcpy(*(bufspace+k),tokenspace);
                         k++;
                         tokenspace = (char *)strtok(NULL," ");
                    }
                }
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    printf("kcount is %d\n",kcount);
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||  
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
        {
        }
        else
        {
            printf("input not in correct format\n");
        }

        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k==0)
        {

             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc         :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
        
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)      :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
        if (k==2)
        {
             msg->genElemnts.msgType=temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k==3)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits        :   0x%02x\n",
                            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        }
        if (k==4)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum    :   0x%02x\n", 
                         msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
        }
        if (k==5)
        {
	    msg->u.ccmMsg.u.smsBcCmd.cmdType.command = temp[k];
            printf("command         :   0x%02x\n", 
                                   msg->u.ccmMsg.u.smsBcCmd.cmdType.command);
        }
	if (k==6)
        {
	    msg->u.ccmMsg.u.smsBcCmd.cmdType.broadcast = temp[k];
            printf("broadcast       :   0x%02x\n", 
                                  msg->u.ccmMsg.u.smsBcCmd.cmdType.broadcast);
        }
        if (k==7)
        {
            msg->u.ccmMsg.u.smsBcCmd.cmdType.lastlock = temp[k];
            printf("lastlock        :   0x%02x\n",
                                 msg->u.ccmMsg.u.smsBcCmd.cmdType.lastlock);
        }
        if (k==8)
        {
            msg->u.ccmMsg.u.smsBcCmd.smscbMsg.length = temp[k];
            printf("length          :   0x%02x\n",
                                 msg->u.ccmMsg.u.smsBcCmd.smscbMsg.length);
        }
        if (k==9)
        {
            printf("InfoLen[0]      :   0x%02x\n",temp[k] );
            for(i = 0; i <  msg->u.ccmMsg.u.smsBcCmd.smscbMsg.length; i++  )
            {
                msg->u.ccmMsg.u.smsBcCmd.smscbMsg.msg[i] = temp[k];
            } 
        }
    }
    if (optional[1] == 1)
    {
        printf("chanlInd        :   0x%02x\n",
                                      msg->u.ccmMsg.u.smsBcCmd.chanlInd);
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Cbch Load Indication information elements
        from the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
*       fp - file pointer where the values for the elems are fed

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/

ITS_INT
HandleCbchLdInd(int choice)
{   
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;
    FILE *fptr;
    char line[1024];
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    ReadCbchLdInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding CBCH LOAD INDICATOR Failed  ret :: %d\n", ret);
        return ret;
    }
    else

    printf("******************* ENCODED DATA *************************\n");
    {
        printf("Encoding CBCH LOAD INDICATOR  Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("***************** DECODED DATA ******************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding CBCH LOAD INDICATOR Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding CBCH LOAD INDICATOR Success  ret :: %d\n", ret);
        // display buffer
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",msg.genElemnts.msgDesc.msgGruop) ; 
        printf("msgDesc(T)      :   0x%02x\n",
                                     msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n",msg.genElemnts.msgType);
        printf("chanlBits       :   0x%02x\n",
                                 msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n",
                              msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);
        printf("Loadtype        :   0x%02x\n",msg.u.ccmMsg.u.cbchLoadInd.type);
        printf("Slotcount       :   0x%02x\n",
                                 msg.u.ccmMsg.u.cbchLoadInd.slotCount);
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"CBCHLDIND START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "CBCHLDIND END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                      printf("chanlInd        :   0x%02x\n",                                                                msg.u.ccmMsg.u.cbchLoadInd.chanlInd ) ;
                    }
                }
                break;
            }
        }    
        fclose(fptr); 
   } 
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Cbch Load Indication elements from the file and assigning
*       these values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*
*/
ITS_INT
ReadCbchLdInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0,icount, k =0, kcount,j ;
    char c, str[10], str1[10], str2[10], str3[10],str4[10], str5[10];
    char str6[10] ,str7[10], str8[10],str9[10];
    unsigned char buffer[100];
    unsigned char temp[100],temp1;
    long l[100], l1;
    int optional[10];
    int tot_elem = 0;
    int param = 0;
    printf("                        \n");
    printf("MESSAGE CATEGORY:COMMON CHANNEL MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        CLEAR_TM_CCM_CLI_OPTIONAL_BIT_MAP(msg);
        if (strcmp(line,"CBCHLDIND START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "CBCHLDIND END\n") != 0)
            {
                if ( line[0] == 'M' || line[0] == 'O')
                {
                    if(line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }


                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_TM_CCM_CLI_SMSCB_CHANNEL_IND(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.cbchLoadInd.chanlInd = temp[i];
                        }
                    }
                }

                printf("%s",line);
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
    		    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab = (char *)strtok(NULL,"\t");
                    tokenspace = (char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                         bufspace[k] = 
                         (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                         strcpy(*(bufspace+k),tokenspace);
                         k++;
                         tokenspace = (char *)strtok(NULL," ");
                    }
                }
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    printf("kcount is %d\n",kcount);
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||  
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
        {
        }
        else
        {
            printf("input not in correct format\n");
        }

        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k==0)
        {

             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc         :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
        
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)      :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
        if (k==2)
        {
             msg->genElemnts.msgType=temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k==3)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits        :   0x%02x\n",
                            msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        }
        if (k==4)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum    :   0x%02x\n", 
                         msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
        }
        if (k==5)
        {
            msg->u.ccmMsg.u.cbchLoadInd.type = temp[k];
            printf("Loadtype       :   0x%02x\n",
                                       msg->u.ccmMsg.u.cbchLoadInd.type);
        }
        if (k==6)
        {
            msg->u.ccmMsg.u.cbchLoadInd.slotCount = temp[k];
            printf("slotCount      :   0x%02x\n",
                                      msg->u.ccmMsg.u.cbchLoadInd.slotCount);
         }

}
    if (optional[1] == 1)
    {
        printf("chanInd        :   0x%02x\n",
                                     msg->u.ccmMsg.u.cbchLoadInd.chanlInd);
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Notify Command information elements from the
        file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
*       fp - file pointer where the values for the elems are fed

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*       prints the encoded and decoded values
* RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*/
ITS_INT
HandleNotifyCmd(int choice)
 {
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;
    FILE *fptr;
    char line[1024]; 
    int len = 0, ret = 0, i;
    int ret1 = 0;
    ITS_OCTET buffer[100];
    ReadNotifyCmd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);    
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Notify Command Failed  ret :: %d\n", ret);
        return ret;
    }
    else                                                 
    {
        // display buffer
        printf("****************** ENCODED DATA ************************\n");
        printf("Encoding Notify Command Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("**************** DECODED DATA **************************\n");
    ret1 = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret1 != ITS_SUCCESS)
    {
        printf("Decoding Notify Command Failed  ret :: %d\n", ret);
        return ret1;
    }
    else
    {
        printf("Decoding Notify Command Success  ret :: %d\n", ret);
         //display buffer
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", 
                                  msg.genElemnts.msgDesc.msgGruop) ;
	printf("msgDesc(T)      :   0x%02x\n", 
                                   msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanlBits       :   0x%02x\n",
                             msg.u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n",
                          msg.u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum);
        printf("length          :   0x%02x\n",
                                msg.u.ccmMsg.u.notCmd.cmdInd.length);
        printf("cmdVal          :   0x%02x\n",
                                  msg.u.ccmMsg.u.notCmd.cmdInd.cmdVal);
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"NTFYCMD START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "NTFYCMD END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("refLength       :   0x%02x\n",
                                      msg.u.ccmMsg.u.notCmd.callRef.length);
                        printf("descGroup[0]    :   0x%02x\n",
                                  msg.u.ccmMsg.u.notCmd.callRef.descGroup[0]);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-2"))
                    {
                        printf("descLength      :   0x%02x\n",
                                        msg.u.ccmMsg.u.notCmd.chanlDesc.length);
                        printf("chanlDesc[0]    :   0x%02x\n",
                                 msg.u.ccmMsg.u.notCmd.chanlDesc.chanlDesc[0]);

                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-3"))
                    {
                        printf("nchDrxLength    :   0x%02x\n",
                                         msg.u.ccmMsg.u.notCmd.nchDrx.length);
                        printf("NLNStatus       :   0x%02x\n",
                                        msg.u.ccmMsg.u.notCmd.nchDrx.status);
                        printf("eMLPP           :   0x%02x\n",
                                         msg.u.ccmMsg.u.notCmd.nchDrx.emlpp);
                        printf("NLN             :   0x%02x\n",
                                           msg.u.ccmMsg.u.notCmd.nchDrx.NLN);
                    }
                }
                break;
            }
        }    
        fclose(fptr); 
    } 
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Notify Command elements from the file and assigning
*       these values to the structure element
* INPUT:
*       File - input data is read from file

* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg structure elements after reading
        from file
* RETURNS:
        none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name               Date         Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*
*/
ITS_INT
ReadNotifyCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0,icount, k =0, kcount,j ;
    char c, str[10], str1[10], str2[10], str3[10],str4[10], str5[10];
    char str6[10] ,str7[10], str8[10],str9[10];
    unsigned char buffer[100];
    unsigned char temp[100],temp1;
    long l[100], l1;
    int optional[10];
    int tot_elem = 0;
    int param = 0;
    printf("                        \n");
    printf("MESSAGE CATEGORY:CHANNEL MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        CLEAR_TM_CCM_NC_OPTIONAL_BIT_MAP(msg);
        if (strcmp(line,"NTFYCMD START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "NTFYCMD END\n") != 0)
            {
                if ( line[0] == 'M' || line[0] == 'O')
                {
                    if(line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }
                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_TM_CCM_NC_GROUP_CALL_REFERENCE(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];

                            msg->u.ccmMsg.u.notCmd.callRef.length = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0;
        j < msg->u.ccmMsg.u.notCmd.callRef.length ; j++ )
                            {
                                msg->u.ccmMsg.u.notCmd.callRef.descGroup[j] = 
                                                                       temp[i];
                             }
                        }


                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-2"))
                {
                    optional[2] = 2;
                    SET_TM_CCM_NC_CHANNEL_DESCRIPTION(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.notCmd.chanlDesc.length = temp[i];  
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0;
        j < msg->u.ccmMsg.u.notCmd.chanlDesc.length ; j++ )
                            {
                                msg->u.ccmMsg.u.notCmd.chanlDesc.chanlDesc[j] =
                                                                       temp[i];
                             }
                        }

                    }
                }

                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-3"))
                {
                    optional[3] = 3;
                    SET_TM_CCM_NC_NCH_DRX_INFO(msg);
                    sscanf(line,"%c %s %s %s %s",&c,&str,&str1,&str2,&str3);
                    for (i = 0; i < 5; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.notCmd.nchDrx.length = temp[i];     
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.notCmd.nchDrx.status = temp[i];
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.notCmd.nchDrx.emlpp = temp[i];     
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.ccmMsg.u.notCmd.nchDrx.NLN = temp[i]; 
                        }
                    }
                }
                printf("%s",line);
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = 
                    (char*)calloc(strlen(tokentab)+1,sizeof(char));
    		    strcpy(*(buftab+i), tokentab);
                    i++;
                    tokentab = (char *)strtok(NULL,"\t");
                    tokenspace = (char *)strtok(tokentab," ");
                    while (tokenspace)
                    {
                         bufspace[k] = 
                         (char*)calloc(strlen(tokenspace)+1,sizeof(char));
                         strcpy(*(bufspace+k),tokenspace);
                         k++;
                         tokenspace = (char *)strtok(NULL," ");
                    }
                }
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    printf("kcount is %d\n",kcount);
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||  
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
        {
        }
        else
        {
            printf("input not in correct format\n");
        }

        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k==0)
        {

             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc         :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
        
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)      :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
        if (k==2)
        {
             msg->genElemnts.msgType=temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k==3)
        {
             msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",msg->u.ccmMsg.ccmGenElements.chanlNum.chanlBits);
        }

        if (k==4)
        {
            msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum=temp[k];
            printf("timeSlotNum     :   0x%02x\n", msg->u.ccmMsg.ccmGenElements.chanlNum.timeSlotNum );
        }
        if (k==5)
        {
            msg->u.ccmMsg.u.notCmd.cmdInd.length = temp[k];
            printf("length          :   0x%02x\n",
                                     msg->u.ccmMsg.u.notCmd.cmdInd.length);
        }
        if (k==6)
        {
            msg->u.ccmMsg.u.notCmd.cmdInd.cmdVal = temp[k]; 
            printf("cmdValue        :   0x%02x\n",
                                     msg->u.ccmMsg.u.notCmd.cmdInd.cmdVal);
        }

}
    if (optional[1] == 1)
    {
        printf("refLength       :   0x%02x\n",
                                 msg->u.ccmMsg.u.notCmd.callRef.length);
        printf("descGroup[0]    :   0x%02x\n",
                                msg->u.ccmMsg.u.notCmd.callRef.descGroup[0]);
    }
    if (optional[2] == 2)
    {
        printf("descLength      :   0x%02x\n",
                                msg->u.ccmMsg.u.notCmd.chanlDesc.length);
        printf("chanlDesc[0]    :   0x%02x\n",
                           msg->u.ccmMsg.u.notCmd.chanlDesc.chanlDesc[0]);
    } 
    if (optional[3] == 3)
    {
        printf("DrxLength       :   0x%02x\n",
                                  msg->u.ccmMsg.u.notCmd.nchDrx.length);
        printf("status          :   0x%02x\n",
                                   msg->u.ccmMsg.u.notCmd.nchDrx.status);
        printf("eMLPP           :   0x%02x\n",
                                    msg->u.ccmMsg.u.notCmd.nchDrx.emlpp);
        printf("NLN             :   0x%02x\n",
                                      msg->u.ccmMsg.u.notCmd.nchDrx.NLN);
    } 
    fclose(fp);
}

ITS_INT (*testTrafficMsg_CCM[11])(int) = 
{
    HandleBcchInfo,
    HandleBcchInfo,
    HandleCcchLdInd,
    HandleChanlRqd,
    HandleDelInd,
    HandlePageCmd,
    HandleImmdAssgCmd,
    HandleSmsBrdcastReq,
    HandleSmsBrdcastCmd,
    HandleCbchLdInd,
    HandleNotifyCmd,
};





















