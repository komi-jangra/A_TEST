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
 *  ID: $Id: measurement_management_msg.c,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
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
 *  Revision 1.1.2.2  2005/09/27 12:22:25  mkrishna
 *  Modification done for Error cases - hakshata & raghavendrasm
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
*       Handles reading the MeasurementResultReuest ,Stop Measurement and
*       Start Measurement elements from the file,encoding and then decoding. 
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
HandleMeasureReq(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadMeasureReq(&msg,fp,choice);
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
        printf("Encoding Success ret :: %d\n\n", ret);
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
        printf("Measrement Id   :  0x%02x\n",
                msg.u.formMsg.u.measMsg.measId );
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the MeasurementResultRequest ,Stop Measurement and Start
*       Measurement information elements from the file and assigning these 
*       values to the structure element
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
ReadMeasureReq(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0;
    int k = 0, kcount;
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
    printf("MESSAGE NAME: MEASUREMENT MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"MEASUREREQ START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"MEASUREREQ END\n")!=0)
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
                      if(line[1] == '\t')
                      {
                         /*Do Nothing */
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
                   && choice == 3 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }

               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 4 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }

               tokentab=(char *)strtok(line,"\t");
               while (tokentab)
               {
                   buftab[i]=(char*)calloc(strlen(tokentab)+1,sizeof(char));
                   strcpy(*(buftab+i), tokentab);
                   i++;
                   tokentab=(char *)strtok(NULL,"\t");
                   tokenspace=(char *)strtok(tokentab," ");
                   while (tokenspace)
                   {
                       bufspace[k] = (char*)calloc(strlen(tokenspace)+1,
                                       sizeof(char));
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
    kcount = k;
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    if (choice == 1)
    {
        printf("MESSAGE NAME: MEASUREMENT RESULT REQUEST \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x8A)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 3)
    {
        printf("MESSAGE NAME: START MEASUREMENT \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x8C)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 4)
    {
        printf("MESSAGE NAME: STOP MEASUREMENT \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x8D)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k = 0; k < kcount; k++)
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
            printf("placeInd       :   0x%02x\n",
                             msg->u.formMsg.formGenElemnts.msgType );
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
            msg->u.formMsg.u.measMsg.measId = temp[k];
            printf("Measurement Id :   0x%02x\n",
                      msg->u.formMsg.u.measMsg.measId);
        }
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Measurement Result Response elements from the file,
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
*      none 
*/
ITS_INT
HandleMeasureResponse(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadMeasureResponse(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Measure Management Message Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding Measure Management Message Success ret:: %d\n\n",ret);
        for(i = 0; i < len; i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Measurement Management Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Measure Result Request Success  ret :: %d\n", ret);
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
        printf("Measrement Id   :  0x%02x\n",
                                      msg.u.formMsg.u.measMsg.measId );
        printf("Length          :  0x%02x\n",
                                  msg.u.formMsg.u.measMsg.u.measResp.length);
        printf("Result[0]       :  0x%02x\n" ,
                           msg.u.formMsg.u.measMsg.u.measResp.measResult[0]);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the Measurment Result Response information elements from the
*       file and assigning these values to the structure element 
*INPUT:
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
ReadMeasureResponse(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0;
    int k = 0, kcount;
    int param = 11;
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
    printf("Message Name: Measurement Management Message\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"MEASURERESPONSE START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),
                   "MEASURERESPONSE END\n") != 0)
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
                      if(line[1] == '\t')
                      {
                         /* Do Nothing */    
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
    printf("MESSAGE NAME: MEASUREMENT RESULT RESPONSE\n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k = 0; k < kcount; k++)
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
            msg->u.formMsg.u.measMsg.measId = temp[k];
            printf("Measurement Id :   0x%02x\n",
                      msg->u.formMsg.u.measMsg.measId);
        }
        if (k == 9)
        {
            msg->u.formMsg.u.measMsg.u.measResp.length = temp[k];
            printf("length         :   0x%02x\n",
                      msg->u.formMsg.u.measMsg.u.measResp.length);
        }
        if (k == 10)
        {
            printf("measResult     :   0x%02x\n", temp[k]);
            for (i = 0; i <  msg->u.formMsg.u.measMsg.u.measResp.length; i++ )
            {
               msg->u.formMsg.u.measMsg.u.measResp.measResult[i] = temp[k];
            }
        }
    }
    fclose(fp);
}

ITS_INT ( *testNetworkMsg_MMM[5])(int) = 
{
    NULL,
    HandleMeasureReq,
    HandleMeasureResponse,
    HandleMeasureReq,
    HandleMeasureReq,
}; 
                                                                                                                             


