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
 *  ID: $Id: other_messages.c,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
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
 *  Revision 1.1.2.1  2005/09/05 12:34:26  mkrishna
 *  Added network mangement simulator - akshata & sriraghavendrasm
 *
 *
 ****************************************************************************/

#include<abis_network_management.h>

extern FILE *fp;
extern filename[20];

/*implementation:internal
*
* PURPOSE:
*       Handles reading the GetAttribute and GetAttribute Nack elements 
*       from the file,encoding and then decoding. The Same function takes care
*       of the above two
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
*       none
*/
ITS_INT
HandleGetAttribute(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadGetAttribute(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding Success  ret :: %d\n\n", ret);
        for(i = 0; i < len; i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printf("msgDesc         :  0x%02x\n",
                                   msg.u.formMsg.formGenElemnts.msgDesc);
        printf("placeInd        :  0x%02x\n",
                                  msg.u.formMsg.formGenElemnts.placeInd);
        printf("SeqNum          :  0x%02x\n",
                                 msg.u.formMsg.formGenElemnts.seqNum);
        printf("msgType         :  0x%02x\n",
                                 msg.u.formMsg.formGenElemnts.msgType);
        printf("objClass        :  0x%02x\n",
                                 msg.u.formMsg.formGenElemnts.objClass);
        printf("btsNum          :  0x%02x\n",
                                 msg.u.formMsg.formGenElemnts.objInst.btsNum);
        printf("BaseBandNum     :  0x%02x\n",
                             msg.u.formMsg.formGenElemnts.objInst.baseBandNum);
        printf("timeSlotNum     :  0x%02x\n",
                             msg.u.formMsg.formGenElemnts.objInst.timeSlotNum);
        printf("Attr Length     :  0x%02x\n",
                             msg.u.formMsg.u.miscMsg.u.getAttr.length);         
        printf("Attr Id         :  0x%02x\n",
                             msg.u.formMsg.u.miscMsg.u.getAttr.atrrId[0]);
        printf("nackCuase       :  0x%02x\n",
                           msg.u.formMsg.u.miscMsg.u.getAttr.nackCuase );
    }
    return ITS_SUCCESS;
}
  
/*implementation:internal
*
* PURPOSE:
*       Reading the GetAttributes and GetAttrAtrributeNack information elements
        from the file and assigning these values to the structure elements. 
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
*       none 
*/
ITS_INT
ReadGetAttribute(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0;
    int k = 0,kcount;
    int param = 0;
    int linecount = 0;
    unsigned char buffer[100];
    unsigned char temp[100];
    long l[100];
    int l3count;
    char c;
    char str[10];
    long l1,l2,l3;
    unsigned char temp1,temp2,temp3;
    printf("                        \n");
    printf("MESSAGE CATEGORY: MISCELLANEOUS MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"GETATTR START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"GETATTR END\n")!=0)
           {
               printf("%s",line);
               for ( i = 0; i < 100; i++)
               {
                     if( line[i] == '\n')
                      {
                          linecount++;
                      }
               }
               if (line[0] == 'M')
               {
                      if(line[1]=='\t')
                      {
                         //  Do Nothing     
                      }
                      else
                      {
                          printf("Tab space after the param at %d\n",linecount);
                          exit(1);
                      }
               }
                
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }
               
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 1 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
                    
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 2 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
               tokentab = (char *)strtok(line,"\t");
               while (tokentab)
               {
                   buftab[i] = (char*)calloc(strlen(tokentab)+1,sizeof(char));
                   strcpy(*(buftab+i), tokentab);
                   i++;
                   tokentab = (char *)strtok(NULL,"\t");
                   tokenspace = (char *)strtok(tokentab," ");
                   while (tokenspace)
                   {
                       bufspace[k] = (char*)calloc(strlen(tokenspace)+1,
                                       sizeof(char));
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
    kcount = k;

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    if (choice == 1)
    {
        printf("MESSAGE NAME: GET ATTRIBUTE \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x81)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 2)
    {
        printf("MESSAGE NAME: GET ATTRIBUTE NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x83)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    
    for(k=0; k<kcount; k++)
    {
        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k == 0)
        {
            msg->u.formMsg.formGenElemnts.msgDesc = temp[k];
            printf("msgDesc        :   0x%02x\n",
                               msg->u.formMsg.formGenElemnts.msgDesc);
        }
        if (k == 1)
        {
            msg->u.formMsg.formGenElemnts.placeInd = temp[k];
            printf("placeInd       :   0x%02x\n",
                             msg->u.formMsg.formGenElemnts.placeInd );
        }
        if (k == 2)
        {
            msg->u.formMsg.formGenElemnts.seqNum = temp[k];
            printf("seqNum         :   0x%02x\n",
                                 msg->u.formMsg.formGenElemnts.seqNum);
        }
        if (k == 3)
        {
            msg->u.formMsg.formGenElemnts.msgType = temp[k];
            printf("msgType        :   0x%02x\n",
                                 msg->u.formMsg.formGenElemnts.msgType);
        }
        if (k == 4)
        {
             msg->u.formMsg.formGenElemnts.objClass = temp[k];
             printf("objClass       :   0x%02x\n",
                                  msg->u.formMsg.formGenElemnts.objClass);
        }
        if (k == 5)
        {
             msg->u.formMsg.formGenElemnts.objInst.btsNum = temp[k];
             printf("btsNum         :   0x%02x\n",
                             msg->u.formMsg.formGenElemnts.objInst.btsNum);
        }
        if (k == 6)
        {
             msg->u.formMsg.formGenElemnts.objInst.baseBandNum = temp[k];
             printf("BaseBandN      :   0x%02x\n",
                         msg->u.formMsg.formGenElemnts.objInst.baseBandNum);
        }

        if (k == 7)
        {
             msg->u.formMsg.formGenElemnts.objInst.timeSlotNum = temp[k];
             printf("timeSlotN      :   0x%02x\n",
                          msg->u.formMsg.formGenElemnts.objInst.timeSlotNum);
        }
        if (k == 8)
        {
            msg->u.formMsg.u.miscMsg.u.getAttr.length = temp[k];
            printf("Attr Length    :   0x%02x\n",
                              msg->u.formMsg.u.miscMsg.u.getAttr.length);
        }
        if (k == 9)
        {
            printf("attrId[0]      :   0x%02x\n", temp[k]);
            for(i = 0; i < msg->u.formMsg.u.miscMsg.u.getAttr.length; i++)
            {
                msg->u.formMsg.u.miscMsg.u.getAttr.atrrId[i] = temp[k];
            }
        }
        if (k == 10)
        {
            msg->u.formMsg.u.miscMsg.u.getAttr.nackCuase = temp[k];
            printf("nackCuase      :   0x%02x\n",
                              msg->u.formMsg.u.miscMsg.u.getAttr.nackCuase);
        }
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the GetAttribute Response elements from the file,
*       encoding and then decoding. 
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
*       none
*/
ITS_INT
HandleGetAttrResponse(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadGetAttrResponse(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding Success  ret :: %d\n\n", ret);
        for(i = 0; i < len; i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printf("msgDesc         :  0x%02x\n",
                                   msg.u.formMsg.formGenElemnts.msgDesc);
        printf("placeInd        :  0x%02x\n",
                                  msg.u.formMsg.formGenElemnts.placeInd);
        printf("SeqNum          :  0x%02x\n",
                                 msg.u.formMsg.formGenElemnts.seqNum);
        printf("msgType         :  0x%02x\n",
                                 msg.u.formMsg.formGenElemnts.msgType);
        printf("objClass        :  0x%02x\n",
                                 msg.u.formMsg.formGenElemnts.objClass);
        printf("btsNum          :  0x%02x\n",
                                 msg.u.formMsg.formGenElemnts.objInst.btsNum);
        printf("BaseBandNum     :  0x%02x\n",
                             msg.u.formMsg.formGenElemnts.objInst.baseBandNum);
        printf("timeSlotNum     :  0x%02x\n",
                             msg.u.formMsg.formGenElemnts.objInst.timeSlotNum);
        printf("AttrRespLength  :  0x%02x\n", 
                       msg.u.formMsg.u.miscMsg.u.getAttrResp.length );
        printf("notReport[0]    :  0x%02x\n",
                    msg.u.formMsg.u.miscMsg.u.getAttrResp.notRep[0]);
        printf("Reported[0]     :  0x%02x\n",
                    msg.u.formMsg.u.miscMsg.u.getAttrResp.reported[0]);
        printf("notRepCount     :  0x%02x\n",
                    msg.u.formMsg.u.miscMsg.u.getAttrResp.notRepCount);
    }
    return ITS_SUCCESS;
}
  
/*implementation:internal
*
* PURPOSE:
*       Reading the GetAtrribute Response information elements from the file 
*       and  assigning these values to the structure elements 
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
*       none
*/
ITS_INT
ReadGetAttrResponse(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0;
    int k = 0,kcount;
    int param = 0;
    int linecount = 0;
    unsigned char buffer[100];
    unsigned char temp[100];
    long l[100];
    int l3count;
    char c;
    char str[10];
    long l1,l2,l3;
    unsigned char temp1,temp2,temp3;
    printf("                        \n");
    printf("MESSAGE CATEGORY: MISCELLANEOUS MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"GETATTRRESPONSE START\n") == 0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),
                  "GETATTRRESPONSE END\n") != 0)
           {
               printf("%s",line);
               for ( i = 0; i < 100; i++)
               {
                     if( line[i] == '\n')
                      {
                          linecount++;
                      }
               }
               if (line[0] == 'M')
               {
                      if(line[1]=='\t')
                      {
                         //  Do Nothing     
                      }
                      else
                      {
                          printf("Tab space after the param at %d\n",linecount);
                          exit(1);
                      }
               }
               tokentab = (char *)strtok(line,"\t");
               while (tokentab)
               {
                   buftab[i] = (char*)calloc(strlen(tokentab)+1,sizeof(char));
                   strcpy(*(buftab+i), tokentab);
                   i++;
                   tokentab = (char *)strtok(NULL,"\t");
                   tokenspace = (char *)strtok(tokentab," ");
                   while (tokenspace)
                   {
                       bufspace[k] = (char*)calloc(strlen(tokenspace)+1,
                                       sizeof(char));
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
    kcount = k;
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printf("MESSAGE NAME: GET ATTRIBUTE RESPONE\n\n\n");
   
    for(k=0; k<kcount; k++)
    {
        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k == 0)
        {
            msg->u.formMsg.formGenElemnts.msgDesc = temp[k];
            printf("msgDesc        :   0x%02x\n",
                               msg->u.formMsg.formGenElemnts.msgDesc);
        }
        if (k == 1)
        {
            msg->u.formMsg.formGenElemnts.placeInd = temp[k];
            printf("placeInd       :   0x%02x\n",
                             msg->u.formMsg.formGenElemnts.placeInd );
        }
        if (k == 2)
        {
            msg->u.formMsg.formGenElemnts.seqNum = temp[k];
            printf("seqNum         :   0x%02x\n",
                                 msg->u.formMsg.formGenElemnts.seqNum);
        }
        if (k == 3)
        {
            msg->u.formMsg.formGenElemnts.msgType = temp[k];
            printf("msgType        :   0x%02x\n",
                                 msg->u.formMsg.formGenElemnts.msgType);
        }
        if (k == 4)
        {
             msg->u.formMsg.formGenElemnts.objClass = temp[k];
             printf("objClass       :   0x%02x\n",
                                  msg->u.formMsg.formGenElemnts.objClass);
        }
        if (k == 5)
        {
             msg->u.formMsg.formGenElemnts.objInst.btsNum = temp[k];
             printf("btsNum         :   0x%02x\n",
                             msg->u.formMsg.formGenElemnts.objInst.btsNum);
        }
        if (k == 6)
        {
             msg->u.formMsg.formGenElemnts.objInst.baseBandNum = temp[k];
             printf("BaseBandN      :   0x%02x\n",
                         msg->u.formMsg.formGenElemnts.objInst.baseBandNum);
        }

        if (k == 7)
        {
             msg->u.formMsg.formGenElemnts.objInst.timeSlotNum = temp[k];
             printf("timeSlotN      :   0x%02x\n",
                          msg->u.formMsg.formGenElemnts.objInst.timeSlotNum);
        }
        if (k == 8)
        {
            msg->u.formMsg.u.miscMsg.u.getAttrResp.length = temp[k];
            printf("AttrRespLength :   0x%02x\n",
                              msg->u.formMsg.u.miscMsg.u.getAttrResp.length);
        }
        if (k == 9)
        {
            printf("notReported[0] :   0x%02x\n", temp[k]);
            for(i = 0; i < msg->u.formMsg.u.miscMsg.u.getAttrResp.length; i++)
            {
                msg->u.formMsg.u.miscMsg.u.getAttrResp.notRep[i] = temp[k];
            }
        }
        if (k == 10)
        {
            printf("Reported[0]    :   0x%02x\n", temp[k]);
            for(i = 0; i < msg->u.formMsg.u.miscMsg.u.getAttrResp.length; i++)
            {
                msg->u.formMsg.u.miscMsg.u.getAttrResp.reported[i] = temp[k];
            }
        }
        if (k == 11)
        {
            msg->u.formMsg.u.miscMsg.u.getAttrResp.notRepCount = temp[k];
            printf("Attr Length    :   0x%02x\n",
                         msg->u.formMsg.u.miscMsg.u.getAttrResp.notRepCount);
        }
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the SetAlarm elements from the file,
*       encoding and then decoding. The Same function takes care of 
*       SetAlarm Ack and SetAlarm Nack
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
*      none
*/
ITS_INT
HandleSetAlarm(int choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    int ret_elem =0  ;
    FILE *fptr;
    char line[1024];
    ReadSetAlarm(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    printf("******************* ENCODED DATA *************************\n");
    {
        printf("Encoding Success  ret :: %d\n\n", ret);
       /* display buffer */
        for(i = 0; i < len; i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("********************** DECODED DATA ************************\n");
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Failed  ret :: %d\n", ret);
         return ret;
    }
    else
    {
    	printf("Decoding Result Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("msgDesc          :  0x%02x\n",
                      msg.u.formMsg.formGenElemnts.msgDesc);
        printf("placeInd         :  0x%02x\n",
                     msg.u.formMsg.formGenElemnts.placeInd);
        printf("SeqNum           :  0x%02x\n",
                        msg.u.formMsg.formGenElemnts.seqNum);
        printf("msgType          :  0x%02x\n",
                       msg.u.formMsg.formGenElemnts.msgType);
        printf("objClass         :  0x%02x\n",
                      msg.u.formMsg.formGenElemnts.objClass);
        printf("btsNum           :  0x%02x\n",
                   msg.u.formMsg.formGenElemnts.objInst.btsNum);
        printf("BaseBandNum      :  0x%02x\n",
                 msg.u.formMsg.formGenElemnts.objInst.baseBandNum);
        printf("timeSlotNum      :  0x%02x\n",
                    msg.u.formMsg.formGenElemnts.objInst.timeSlotNum);
        printf("probCauseType    :  0x%02x\n",  
             msg.u.formMsg.u.miscMsg.u.alarmThresh.probCause.type);
        printf("probCauseValue   :  0x%02x\n",  
             msg.u.formMsg.u.miscMsg.u.alarmThresh.probCause.value);
        printf("nackCuase        :  0x%02x\n",
                    msg.u.formMsg.u.miscMsg.u.alarmThresh.nackCuase);    
    
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"SETALARM START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "SETALARM END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("pwr o/p Fault:  0x%02x\n", 
                       msg.u.formMsg.u.miscMsg.u.alarmThresh.powerOutput.fault);
                        printf("reduced      :  0x%02x\n",
                    msg.u.formMsg.u.miscMsg.u.alarmThresh.powerOutput.reduced); 
                        printf("excessive    :  0x%02x\n", 
                   msg.u.formMsg.u.miscMsg.u.alarmThresh.powerOutput.excessive);

                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-2"))
                    {
                        printf("Faulty       :  0x%02x\n",
                        msg.u.formMsg.u.miscMsg.u.alarmThresh.vswr.faulty); 
                        printf("notAdjusted  :  0x%02x\n",
                   msg.u.formMsg.u.miscMsg.u.alarmThresh.vswr.notAdjusted);

                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-3"))
                    {
                        printf("ThreshLen    :  0x%02x\n",
                       msg.u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh.length); 
                        printf("reduced      :  0x%02x\n",
              msg.u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh.mfdDependnt[0]); 

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
*       Reading the SetAlarm Threshold ,Set Alarm Threshold Ack and SetAlarm 
*       Threshold Nack information elements from the file and assigning these 
*       values to the structure element and depending on the choices 
*       corresponding values are assigned to the structure elements
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
*       none
*/
ITS_INT
ReadSetAlarm(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp, int choice)
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
    printf("MESSAGE CATEGORY:MISCELLANEOUS MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        CLEAR_NM_EM_REIN_OPTIONAL_BIT_MAP(msg);
        if (strcmp(line,"SETALARM START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "SETALARM END\n") != 0)
            {
                if ( line[0] == 'M' || line[0] == 'O')
                {
                    if(line[1] == '\t')
                    {
                        /* Do Nothing */
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

               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 4 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 5 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 6 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }

                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_NM_MM_SAT_POWER_OUTPUT_THRESHOLD(msg);
                    sscanf(line,"%c %s %s %s",&c,&str,&str1,&str2);
                    for (i = 0; i < 5; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
          msg->u.formMsg.u.miscMsg.u.alarmThresh.powerOutput.fault = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            {
 msg->u.formMsg.u.miscMsg.u.alarmThresh.powerOutput.reduced = temp[i];
                             }
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
       msg->u.formMsg.u.miscMsg.u.alarmThresh.powerOutput.excessive = temp[i];
                        }

                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-2"))
                {
                    optional[2] = 2;
                    SET_NM_MM_SAT_VSWR_THRESHOLDS(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                           msg->u.formMsg.u.miscMsg.u.alarmThresh.vswr.faulty = 
                                                                  temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            {
                   msg->u.formMsg.u.miscMsg.u.alarmThresh.vswr.notAdjusted =
                                                                   temp[i];
                             }
                        }

                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-3"))
                {
                    optional[3] = 3;
                    SET_NM_MM_SAT_MFD_DEPENDENT_THRESHOLDS(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 4; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
              msg->u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh.length = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
        j < msg->u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh.length ;
                       j++ )
                            {
 msg->u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh.mfdDependnt[j] = temp[i];
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
    if (kcount == 11 || kcount > 11)
    {
    }
    else
    {
	printf("Information element missing\n");
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    if (choice == 4)
    {
        printf("MESSAGE NAME: SET ALARM THRESHOLD \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x84)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 5)
    {
        printf("MESSAGE NAME: SET ALARM THRESHOLD ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x85)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 6)
    {
        printf("MESSAGE NAME: SET ALARM THRESHOLD NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x86)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
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
            msg->u.formMsg.formGenElemnts.msgDesc = temp[k];
            printf("msgDesc        :   0x%02x\n",
                               msg->u.formMsg.formGenElemnts.msgDesc);
        }
        if (k == 1)
        {
            msg->u.formMsg.formGenElemnts.placeInd = temp[k];
            printf("placeInd       :   0x%02x\n",
                             msg->u.formMsg.formGenElemnts.placeInd);
        }
        if (k == 2)
        {
            msg->u.formMsg.formGenElemnts.seqNum = temp[k];
            printf("seqNum         :   0x%02x\n",
                                 msg->u.formMsg.formGenElemnts.seqNum);
        }
        if (k == 3)
        {  
             msg->u.formMsg.formGenElemnts.msgType = temp[k];
             printf("msgType        :   0x%02x\n",
                          msg->u.formMsg.formGenElemnts.msgType);
        }
        if (k == 4)
        {
             msg->u.formMsg.formGenElemnts.objClass = temp[k];
             printf("objClass       :   0x%02x\n",
                                  msg->u.formMsg.formGenElemnts.objClass);
        }
        if (k == 5)
        {
             msg->u.formMsg.formGenElemnts.objInst.btsNum = temp[k];
             printf("btsNum         :   0x%02x\n",
                             msg->u.formMsg.formGenElemnts.objInst.btsNum);
        }
        if (k == 6)
        {
             msg->u.formMsg.formGenElemnts.objInst.baseBandNum = temp[k];
             printf("BaseBandNum    :   0x%02x\n",
                         msg->u.formMsg.formGenElemnts.objInst.baseBandNum);
        }
        if (k == 7)
        {
             msg->u.formMsg.formGenElemnts.objInst.timeSlotNum = temp[k];
             printf("timeSlotNum    :   0x%02x\n",
                          msg->u.formMsg.formGenElemnts.objInst.timeSlotNum);
        }
        if (k == 8)
        {
             msg->u.formMsg.u.miscMsg.u.alarmThresh.probCause.type = temp[k];
             printf("probCauseType  :   0x%02x\n",
             msg->u.formMsg.u.miscMsg.u.alarmThresh.probCause.type);
        }
        if (k == 9)
        {
             msg->u.formMsg.u.miscMsg.u.alarmThresh.probCause.value = temp[k];
             printf("probCuaseValur :   0x%02x\n",
                 msg->u.formMsg.u.miscMsg.u.alarmThresh.probCause.value);
        }
        if (k == 10)
        {
             msg->u.formMsg.u.miscMsg.u.alarmThresh.nackCuase = temp[k];
             printf("nackCuase      :   0x%02x\n",
                     msg->u.formMsg.u.miscMsg.u.alarmThresh.nackCuase);
        }
    }
    if (optional[1] == 1)
    {
        printf("pwr o/p Fault:  0x%02x\n", 
                     msg->u.formMsg.u.miscMsg.u.alarmThresh.powerOutput.fault);
        printf("reduced      :  0x%02x\n",
                  msg->u.formMsg.u.miscMsg.u.alarmThresh.powerOutput.reduced); 
        printf("excessive    :  0x%02x\n", 
                msg->u.formMsg.u.miscMsg.u.alarmThresh.powerOutput.excessive);

    }
    if (optional[2] == 2)
    {
        printf("Faulty       :  0x%02x\n",
              msg->u.formMsg.u.miscMsg.u.alarmThresh.vswr.faulty);
        printf("notAdjusted  :  0x%02x\n",
               msg->u.formMsg.u.miscMsg.u.alarmThresh.vswr.notAdjusted);
     
    
    } 
    if (optional[3] == 3)
    {
        printf("ThreshLen    :  0x%02x\n",
                       msg->u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh.length);
        printf("reduced      :  0x%02x\n",
              msg->u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh.mfdDependnt[0]);

    }
    fclose(fp);
  
}

ITS_INT ( *testNetworkMsg_OMM[7])(int) = 
{
    NULL,
    HandleGetAttribute,
    HandleGetAttribute,
    HandleGetAttrResponse,
    HandleSetAlarm,
    HandleSetAlarm,
    HandleSetAlarm,
    
}; 

