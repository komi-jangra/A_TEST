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
 *  ID: $Id: equipment_management_msg.c,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
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
 *  Revision 1.1.2.1  2005/09/05 12:34:25  mkrishna
 *  Added network mangement simulator - akshata & sriraghavendrasm
 *
 *
 ****************************************************************************/

#include<abis_network_management.h>
extern FILE *fp;
extern char filename[20]; 

/*implementation:internal
*
* PURPOSE:
*       Handles reading the ChangeOver elements from the file,
*       encoding and then decoding. The Same function takes care of 
*       ChangeOver Ack and Change Over Nack
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
        none
*/
ITS_INT
HandleChangeOver(ITS_INT choice)
{
    FILE *fp;
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadChangeOver(&msg,fp,choice);
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
        for(i=0;i<len;i++)
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
        printf("Source length   :  0x%02x\n",
                            msg.u.formMsg.u.equipMsg.u.changeOver.src.length);
        printf("Src Value[0]    :  0x%02x\n",
                           msg.u.formMsg.u.equipMsg.u.changeOver.src.value[0]);
        printf("Destn Length    :  0x%02x\n",
                           msg.u.formMsg.u.equipMsg.u.changeOver.dest.length);
        printf("Dstn Value[0]   :  0x%02x\n",
                         msg.u.formMsg.u.equipMsg.u.changeOver.dest.value[0]);
        printf("nackCuase       :  0x%02x\n",
                            msg.u.formMsg.u.equipMsg.u.changeOver.nackCuase);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the Change Over information elements from the file and 
*       assigning these values to the structure element and depending on the 
*       choices corresponding values are assigned to the structure elements
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
ReadChangeOver(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i = 0;
    int k = 0,kcount;
    int param = 0;
    int linecount=0;
    unsigned char buffer[100];
    unsigned char temp[100];
    long l[100];
    int l3count;
    char c;
    char str[10];
    long l1,l2,l3;
    unsigned char temp1,temp2,temp3;
    printf("                        \n");
    printf("MESSAGE CATEGORY : EQUIPMENT MANAGEMENT MESSAGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"CHNGOVER START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"CHNGOVER END\n")!=0)
           {
               printf("%s",line);
               for ( i=0;i<100;i++)
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

               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 3 && strstr(line,"Message Type"))
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
        printf("MESSAGE NAME: CHANGE OVER \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x71)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 2)
    {
        printf("MESSAGE NAME: CHANGE OVER ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x72)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 3)
    {
        printf("MESSAGE NAME: CHANGE OVER NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x73)
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
            printf("seqNum         :   0x%02x\n",
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
            msg->u.formMsg.u.equipMsg.u.changeOver.src.length = temp[k];
            printf("Source length  :   0x%02x\n",
                      msg->u.formMsg.u.equipMsg.u.changeOver.src.length);
        }
        if (k == 9)
        {
            printf("Source Value   :   0x%02x\n",temp[k]);
            for(i = 0; i < msg->u.formMsg.u.equipMsg.u.changeOver.src.length ;
                i++)
            {
                msg->u.formMsg.u.equipMsg.u.changeOver.src.value[i] = temp[k];
            }
        }
        if (k == 10)
        {
            msg->u.formMsg.u.equipMsg.u.changeOver.dest.length = temp[k];
            printf("Dstn length    :   0x%02x\n",
                        msg->u.formMsg.u.equipMsg.u.changeOver.dest.length );
        }
        if (k == 11)
        {
            printf("Destn Value    :   0x%02x\n",temp[k]) ;
            for(i = 0; i < msg->u.formMsg.u.equipMsg.u.changeOver.dest.length ;
                i++)
            {
                msg->u.formMsg.u.equipMsg.u.changeOver.dest.value[i] = temp[k];
            }
        }
        if (k == 12)
        {
            msg->u.formMsg.u.equipMsg.u.changeOver.nackCuase = temp[k];
            printf("nackCuase      :   0x%02x\n",
                      msg->u.formMsg.u.equipMsg.u.changeOver.nackCuase);
        }
    }
    fclose(fp);
}

/****************************************************************************/
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Opstart elements from the file,encoding and 
*       then decoding. The Same function takes care of Opstart Ack and 
*       Opstart Nack
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
HandleOpstart(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadOpstart(&msg,fp,choice);
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
        printf("nackCuase       :  0x%02x\n",
                            msg.u.formMsg.u.equipMsg.u.opStart.nackCuase);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the Opstart information elements from the file and 
*       assigning these values to the structure element and depending on the 
*       choices corresponding values are assigned to the structure elements
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
ReadOpstart(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    printf("MESSAGE CATEGORY: EQUIPMENT MANAGEMENT MESSAGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"OPSTAT START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"OPSTAT END\n")!=0)
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
                         /*  Do Nothing */    
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
                   && choice == 4 && strstr(line,"Message Type"))
                {
                    sscanf(line,"%c %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
                    msg->u.formMsg.formGenElemnts.msgType = temp1;
                }
                    
                if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 5 && strstr(line,"Message Type"))
                {
                    sscanf(line,"%c %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
                    msg->u.formMsg.formGenElemnts.msgType = temp1;
                }

                if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 6 && strstr(line,"Message Type"))
                {
                    sscanf(line,"%c %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
                    msg->u.formMsg.formGenElemnts.msgType = temp1;
                }
                tokentab = (char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i]=(char*)calloc(strlen(tokentab)+1,sizeof(char));
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
    kcount = k;
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    if (choice == 4)
    {
        printf("MESSAGE NAME: OPSTART \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x74)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 5)
    {
        printf("MESSAGE NAME: OPSTART ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x75)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 6)
    {
        printf("MESSAGE NAME: OPSTART NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x76)
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
            msg->u.formMsg.u.equipMsg.u.opStart.nackCuase = temp[k];
            printf("nackCuase      :   0x%02x\n",
                      msg->u.formMsg.u.equipMsg.u.opStart.nackCuase);
        } 
    }
    fclose(fp);
}

/****************************************************************************/
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Setsite elements and Chage H/W Config elements
*       from the file, encoding and then decoding. The Same function takes care
*       of Setsite Ack, Setsite Nack, Change H/w Config Ack and Change H/w 
*       Config Nack
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
HandleSetsite(ITS_INT choice)
{
    FILE *fp;
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadSetsite(&msg,fp,choice);
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
        for(i=0;i<len;i++)
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
      	printf("SiteO/P length  :   0x%02x\n", 
                           msg.u.formMsg.u.equipMsg.u.siteOutput.length ); 
	printf("Output[0]       :   0x%02x\n", 
                        msg.u.formMsg.u.equipMsg.u.siteOutput.output[0]);
 
        printf("nackCuase       :  0x%02x\n",
                         msg.u.formMsg.u.equipMsg.u.siteOutput.nackCuase);
    }
    return ITS_SUCCESS;
}
 
/*implementation:internal
*
* PURPOSE:
*       Reading the Setsite and Change H/W Configuration information elements
*       from the file and assigning these values to the structure element and
*       depending on the choices corresponding values are assigned to the 
*       structure elements
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
ReadSetsite(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i=0;
    int k=0,kcount;
    int param = 0;
    int linecount=0;
    unsigned char buffer[100];
    unsigned char temp[100];
    long l[100];
    int l3count;
    char c;
    char str[10];
    long l1,l2,l3;
    unsigned char temp1,temp2,temp3;
    printf("                        \n");
    printf("MESSAGE CATEGORY : EQUIPMENT MANAGEMENT MESSAGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"SETSITE START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"SETSITE END\n")!=0)
           {
               printf("%s",line);
               for ( i=0;i<100;i++)
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
                   && choice == 10 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
                    
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 11 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }

               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 12 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 13 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 14 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 15 && strstr(line,"Message Type"))
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
    if (choice == 10)
    {
        printf("MESSAGE NAME: SETSITE OUTPUT \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x77)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 11)
    {
        printf("MESSAGE NAME: SETSITE OUTPUT ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x78)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 12)
    {
        printf("MESSAGE NAME: SETSITE OUTPUT NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x79)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 13)
    {
        printf("MESSAGE NAME: CHANGE H/W CONFIG \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x90)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  
    if (choice == 14)
    {
        printf("MESSAGE NAME: CHANGE H/W CONFIG ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x91)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  
    if (choice == 15)
    {
        printf("MESSAGE NAME: CHANGE H/W CONFIG NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x92)
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
            printf("msgDesc         :   0x%02x\n",
                               msg->u.formMsg.formGenElemnts.msgDesc) ;
        }
        if (k == 1)
        {
            msg->u.formMsg.formGenElemnts.placeInd = temp[k];            
            printf("placeInd        :   0x%02x\n",
                               msg->u.formMsg.formGenElemnts.placeInd) ;
        }
        if (k == 2)
        {
            msg->u.formMsg.formGenElemnts.seqNum = temp[k];            
            printf("seqNum          :   0x%02x\n",
                               msg->u.formMsg.formGenElemnts.seqNum ) ;
        }
        if (k == 3)
        {
            msg->u.formMsg.formGenElemnts.msgType = temp[k];            
            printf("msgType         :   0x%02x\n",
                               msg->u.formMsg.formGenElemnts.msgType);
        }
        if (k == 4)
        {
            msg->u.formMsg.formGenElemnts.objClass = temp[k];
            printf("objClass        :   0x%02x\n",
                             msg->u.formMsg.formGenElemnts.objClass);
        }
        if (k == 5)
        {
            msg->u.formMsg.formGenElemnts.objInst.btsNum = temp[k];             
            printf("BTSNum          :   0x%02x\n",
                         msg->u.formMsg.formGenElemnts.objInst.btsNum);
        }
        if (k == 6)
        {
            msg->u.formMsg.formGenElemnts.objInst.baseBandNum = temp[k];
            printf("baseBandNum     :   0x%02x\n",
                     msg->u.formMsg.formGenElemnts.objInst.baseBandNum);
        }
        if (k == 7)
        {
            msg->u.formMsg.formGenElemnts.objInst.timeSlotNum = temp[k];
            printf("timeSlotNum     :   0x%02x\n",
                      msg->u.formMsg.formGenElemnts.objInst.timeSlotNum);
        }
	if (k == 8)
        {
            msg->u.formMsg.u.equipMsg.u.siteOutput.length = temp[k];
            printf("SiteO/P length  :   0x%02x\n",
                     msg->u.formMsg.u.equipMsg.u.siteOutput.length );
        }
	if (k == 9)
        {
            printf("Site o/p value  :   0x%02x\n",temp[k]);
            for(i = 0; i < msg->u.formMsg.u.equipMsg.u.siteOutput.length ;
                i++)
            {
                msg->u.formMsg.u.equipMsg.u.siteOutput.output[i] = temp[k];
            }
        }

        if (k == 10)
        {
            msg->u.formMsg.u.equipMsg.u.siteOutput.nackCuase = temp[k];
            printf("nackCuase      :   0x%02x\n",
                      msg->u.formMsg.u.equipMsg.u.siteOutput.nackCuase);
        } 
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Reinitialize elements from the file,
*       encoding and then decoding. The Same function takes care of 
*       Reinitialize Ack and Reinitialize Nack
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
HandleReinitialize(int choice)
{
    FILE *fp;
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    int ret_elem =0  ;
    FILE *fptr;
    char line[1024];
    ReadReinitialize(&msg,fp,choice);
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
        printf("nackCuase        :  0x%02x\n",
                         msg.u.formMsg.u.equipMsg.u.reInit.nackCuase);
    
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"REINITIALIZE START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "REINITIALIZE END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional"))
                    {
                        printf("equipIdlen   :  0x%02x\n", 
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.equipIdLen);
                        printf("equipId[0]   :  0x%02x\n", 
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.equipId[0]);
                        printf("euipTypelen  :  0x%02x\n", 
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.equipTypeLen);
                        printf("equipTyptId  :  0x%02x\n",
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.equipType[0]);
                        printf("equipVerLen  :  0x%02x\n", 
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.equipVerLen);
                        printf("equipVer[0]  :  0x%02x\n",
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.equipVer[0]);
                        printf("LocLength    :  0x%02x\n", 
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.locLen);
                        printf("locLen[0]    :  0x%02x\n",
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.location[0]);
                        printf("InfoLength   :  0x%02x\n", 
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.infoLen);
                        printf("equipId[0]   :  0x%02x\n",
                        msg.u.formMsg.u.equipMsg.u.reInit.hwDesc.info[0]);
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
*       Reading the Reinitialize information elements from the file and 
*       assigning these values to the structure element and depending on the 
*       choices corresponding values are assigned to the structure elements
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
ReadReinitialize(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp, int choice)
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
    printf("MESSAGE CATEGORY:EQUIPMENT MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        CLEAR_NM_EM_REIN_OPTIONAL_BIT_MAP(msg);
        if (strcmp(line,"REINITIALIZE START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "REINITIALIZE END\n") != 0)
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

               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 7 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 8 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }
               if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 9 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
               }

                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional"))
                {
                    optional[0] = 1;
                    SET_NM_EM_REIN_HW_DESCRIPTION(msg);
                    sscanf(line,"%c %s %s %s %s %s %s %s %s %s %s",
                 &c,&str,&str1,&str2,&str3,&str4,&str5,&str6,&str7,&str8,&str9);
                    for (i=0; i<10; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                 msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipIdLen = 
                                                           temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                      j < msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipIdLen;
                       j++ )
                            {
 
                         msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipId[j] = 
                                                                  temp[i];
                             }
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                 msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipTypeLen = 
                                                           temp[i];
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                    j < msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipTypeLen;
                       j++ )
                            {
 
                     msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipType[j] = 
                                                                  temp[i];
                             }
                        }
                        if (i == 4)
                        {
                            l[i] = strtol(str4,NULL,16);
                            temp[i] = (unsigned char)l[i];
                 msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipVerLen = 
                                                           temp[i];
                        }
                        if (i == 5)
                        {
                            l[i] = strtol(str5,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                     j < msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipVerLen;
                       j++ )
                            {
 
                   msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipVer[j] = 
                                                                  temp[i];
                             }
                        }
                        if (i == 6)
                        {
                            l[i] = strtol(str6,NULL,16);
                            temp[i] = (unsigned char)l[i];
                 msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.locLen = 
                                                           temp[i];
                        }
                        if (i == 7)
                        {
                            l[i] = strtol(str7,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                      j < msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.locLen;
                       j++ )
                            {
 
                    msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.location[j] = 
                                                                  temp[i];
                             }
                        }
                        if (i == 8)
                        {
                            l[i] = strtol(str8,NULL,16);
                            temp[i] = (unsigned char)l[i];
                 msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.infoLen = 
                                                           temp[i];
                        }
                        if (i == 9)
                        {
                            l[i] = strtol(str9,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                      j < msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.infoLen ;
                       j++ )
                            {
 
                    msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.info[j] = 
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
    if (kcount == 9 || kcount > 9)
    {
    }
    else
    {
	printf("Information element missing\n");
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    if (choice == 7)
    {
        printf("MESSAGE NAME: REINITIALIZE \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x87)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 8)
    {
        printf("MESSAGE NAME: REINITIALIZE ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x88)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 9)
    {
        printf("MESSAGE NAME: REINITIALIZE NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x89)
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
             msg->u.formMsg.u.equipMsg.u.reInit.nackCuase = temp[k];
             printf("nackCuase      :   0x%02x\n",
                          msg->u.formMsg.u.equipMsg.u.reInit.nackCuase);
        }
    }
    if (optional[0] == 1)
    {
        printf("Length               :  0x%02x\n", 
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipIdLen);
        printf("equipId[0]           :  0x%02x\n",
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipId[0]);
        printf("euipTypelen          :  0x%02x\n", 
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipTypeLen);
        printf("equipTyptId          :  0x%02x\n",
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipType[0]);
        printf("equipVerLen          :  0x%02x\n", 
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipVerLen);
        printf("equipVer[0]          :  0x%02x\n",
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.equipVer[0]);
        printf("LocLength            :  0x%02x\n", 
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.locLen);
        printf("locLen[0]            :  0x%02x\n",
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.location[0]);
        printf("InfoLength           : 0x%02x\n", 
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.infoLen);
        printf("equipId[0]           :0x%02x\n",
                        msg->u.formMsg.u.equipMsg.u.reInit.hwDesc.info[0]);


    }
  
    fclose(fp);
}

ITS_INT (*testNetworkMsg_EMM[36])(int) = 
{
    NULL,
    HandleChangeOver,
    HandleChangeOver,
    HandleChangeOver,
    HandleOpstart,
    HandleOpstart,
    HandleOpstart,
    HandleReinitialize,
    HandleReinitialize,
    HandleReinitialize,
    HandleSetsite,
    HandleSetsite,
    HandleSetsite,
    HandleSetsite,
    HandleSetsite,
    HandleSetsite,
};

