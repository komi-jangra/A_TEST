
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
 ****************************************************************************/

#include <abis_network_management.h>
extern FILE *fp;
extern char filename[20];

/***************************************************************************
implementation:internal
*
* PURPOSE:
*       This is the common function called while reading the common Information
*       elements from the file i.e Message Discriminator,Placement Indicator,
*       Sequence number,mesage type,object class,object instance.
* INPUT:
*       msg - input message to be encoded while encoding function called
*       line - Each line being read from the file.                                                                          
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      It returns an integer value after successful scanning of the file     
* COMMENTS:
*       none
*****************************************************************************/


ITS_INT
ReadCommonElems(char line[1024],ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
  char str[10],str_one[10],str_two[10];
  char c;
  unsigned char temp[100];
  long l[100];
  int i = 0;
  if (line[0] == 'M' && line[1] == '\t' &&  strstr(line,"Message Discriminator"))
  {
      sscanf(line,"%c %s",&c,&str);
      l[0]=strtol(str,NULL,16);
      temp[0]=(unsigned char)l[0];
      msg->u.formMsg.formGenElemnts.msgDesc = temp[0];
                                                                                                                             
  }
  
  if (line[0] == 'M' && line[1] == '\t' &&  strstr(line,"Placement Indicator"))
  {
      sscanf(line,"%c %s",&c,&str);
      l[0]=strtol(str,NULL,16);
      temp[0]=(unsigned char)l[0];
      msg->u.formMsg.formGenElemnts.placeInd = temp[0];
                                                                                                                             
  }
  
  if (line[0] == 'M' && line[1] == '\t' &&  strstr(line,"Sequence Number"))
  {
      sscanf(line,"%c %s",&c,&str);
      l[0]=strtol(str,NULL,16);
      temp[0]=(unsigned char)l[0];
      msg->u.formMsg.formGenElemnts.seqNum = temp[0];
                                                                                                                             
  }

  if (line[0] == 'M' && line[1] == '\t' &&  strstr(line,"Message Type"))
  {
      sscanf(line,"%c %s",&c,&str);
      l[0]=strtol(str,NULL,16);
      temp[0]=(unsigned char)l[0];
      msg->u.formMsg.formGenElemnts.msgType = temp[0];

  }
  if (line[0] == 'M' && line[1] == '\t' &&  strstr(line,"Object Class"))
  {
      sscanf(line,"%c %s",&c,&str);
      l[0]=strtol(str,NULL,16);
      temp[0]=(unsigned char)l[0];
      msg->u.formMsg.formGenElemnts.objClass = temp[0];

  }
   
  if (line[0] == 'M' && line[1] == '\t' &&  strstr(line,"Object Instance"))
  {
      sscanf(line,"%c %s %s %s",&c,&str,&str_one,&str_two);
      for (i=0;i<6;i++)
      {
          if (i==0)
          {
              l[i]=strtol(str,NULL,16);
              temp[i]=(unsigned char)l[i];
              msg->u.formMsg.formGenElemnts.objInst.btsNum = temp[i];
          }
          
          if (i==1)
          {    
              l[i]=strtol(str_one,NULL,16);
              temp[i]=(unsigned char)l[i];
              msg->u.formMsg.formGenElemnts.objInst.baseBandNum = temp[i];
          }

          if (i==2)
          {
              l[i]=strtol(str_two,NULL,16);
              temp[i]=(unsigned char)l[i];
              msg->u.formMsg.formGenElemnts.objInst.timeSlotNum = temp[i];
          }

      } 
      
  }
  return;
}

/***************************************************************************
This function is called to print the common elements of all the message types
after the decode function.
****************************************************************************/

ITS_INT
printDecCommonElems(ABIS_NETWORK_MANAGEMENT_MSG msg)
{   
    printf("PARAMETER NAMES : VALUES\n");
    printf("------------------------\n");
    printf("msgDesc     :  0x%02x\n",msg.u.formMsg.formGenElemnts.msgDesc);
    printf("placeInd    :  0x%02x\n",msg.u.formMsg.formGenElemnts.placeInd);
    printf("seqNum      :  0x%02x\n",msg.u.formMsg.formGenElemnts.seqNum);
    printf("msgType     :  0x%02x\n",msg.u.formMsg.formGenElemnts.msgType);
    printf("objClass    :  0x%02x\n",msg.u.formMsg.formGenElemnts.objClass);
    printf("btsNum      :  0x%02x\n",msg.u.formMsg.formGenElemnts.objInst.btsNum);
    printf("BaseBandNum :  0x%02x\n",msg.u.formMsg.formGenElemnts.objInst.baseBandNum);
    printf("timeSlotNum :  0x%02x\n",msg.u.formMsg.formGenElemnts.objInst.timeSlotNum);
    return;
}

/***************************************************************************
This function is called to print the common elements of all the message types
after scanning the elements from the file.
****************************************************************************/

ITS_INT
printComFileElems(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    printf("msgDesc   :   0x%02x\n",
                                msg->u.formMsg.formGenElemnts.msgDesc);
    printf("placeInd  :   0x%02x\n",
                                msg->u.formMsg.formGenElemnts.placeInd);
    printf("seqNum    :   0x%02x\n",
                                msg->u.formMsg.formGenElemnts.seqNum);
    printf("msgType   :   0x%02x\n",
                                msg->u.formMsg.formGenElemnts.msgType);
    printf("objClass  :   0x%02x\n",
                               msg->u.formMsg.formGenElemnts.objClass); 
    printf("btsNum    :   0x%02x\n",
                         msg->u.formMsg.formGenElemnts.objInst.btsNum);
    printf("BaseBandN :   0x%02x\n",
                    msg->u.formMsg.formGenElemnts.objInst.baseBandNum);
    printf("timeSlotN :   0x%02x\n",
                    msg->u.formMsg.formGenElemnts.objInst.timeSlotNum);
    return;
}

/****************************************************************************
*implementation:internal
*
* PURPOSE:
*       Handles reading the Load data inidcation,Load data Indication Ack,
*	and Load Data Indication Nack information elements 
*       from the file,encoding and then decoding
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
*****************************************************************************/

static ITS_INT
HandleLoadDataInit(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadLoadDataInit(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding  Failed  ret :: %d\n", ret);
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
        printf("Decoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding  Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        printf("fileIdLen   :  0x%02x\n",
                         msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileIdLen);
        printf("fileId      :  0x%02x\n",
                         msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileId[0]);
        printf("fileVerLen  :  0x%02x\n",
                        msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVerLen);
        printf("fileVer     :  0x%02x\n",
                        msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVer[0]);
        printf("winSize     :  0x%02x\n",
                                   msg.u.formMsg.u.swdmMsg.u.loadInit.winSize);
        if (choice == 3)
        {
            printf("nackCause   :  0x%02x\n",
                                 msg.u.formMsg.u.swdmMsg.u.loadInit.nackCuase);
        }
        
    }
                                                                                                                            
    return ITS_SUCCESS;
}

/***************************************************************************
implementation:internal
*
* PURPOSE:
*       This function reads the Load Data Inidcation,Ack,Nack
*       information elements from the file.
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*
*************************************************************************/

ITS_INT
ReadLoadDataInit(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    char c;
    char str[10];
    long l1;
    unsigned char temp1;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: LOAD DATA INITIATE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"LOAD_DATA_INITIATE START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"LOAD_DATA_INITIATE END\n")!=0)
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
               ReadCommonElems(line,msg);              
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
    kcount =k;
    if (param != 9) /* Checks for the no of Info elem */
    {
        printf("Enter the data correctly\n");
        exit(1);                                                                                                                 }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    if (choice == 1)
    {
        printf("MESSAGE NAME: LOAD DATA INITIATE \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x01)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 2)
    {
        printf("MESSAGE NAME: LOAD DATA INITIATE ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x02)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 3)
    {
        printf("MESSAGE NAME: LOAD DATA INITIATE NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x03)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        
        if (k==8)
        {
            
           l[8]=strtol(bufspace[8],NULL,16);
	    msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileIdLen = (ITS_USHORT)l[8];
            printf("fileIdLen :   0x%04x\n",
                    msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileIdLen);
        }
                                                                                                                             
        if (k==9)
        {
            printf("fileId    :   0x%02x\n",temp[k]);
            for(i=0;i<msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileIdLen;i++)
            {
               msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileId[i] = temp[k];
            }
        }
                                                                                                                             
        if (k==10)
        {   
             
           l[10]=strtol(bufspace[10],NULL,16);
            msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVerLen= (ITS_USHORT)l[10];
            printf("fileVerLen:   0x%04x\n",
                    msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVerLen);
        }
                                                                                                                             
        if (k==11)
        {
            printf("fileVer   :   0x%02x\n",temp[k]);
            for(i=0;i<msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVerLen;i++)
            {
               msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVer[i] = temp[k];
            }

        }
                                                                                                                             
        if (k==12)
        {
            msg->u.formMsg.u.swdmMsg.u.loadInit.winSize = temp[k];
            printf("winSize   :   0x%02x\n",
                               msg->u.formMsg.u.swdmMsg.u.loadInit.winSize);

        }
                                                                                                                             
        if (k==13)
        {   
            if (choice == 3)
            {
                msg->u.formMsg.u.swdmMsg.u.loadInit.nackCuase = temp[k];
                printf("nackCuase :   0x%02x\n",
                             msg->u.formMsg.u.swdmMsg.u.loadInit.nackCuase);
            }
        }
                                                                                                                             
     }
    fclose(fp);
}

/****************************************************************************
implementation:internal
*
* PURPOSE:
*       Handles reading the Load Data Segment,Load Data Segment Ack 
*       information elements from the file,encoding and then decoding
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
****************************************************************************/

static ITS_INT
HandleLoadDataSeg(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadLoadDataSeg(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
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
        printf("Decoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        printf("Length      :  0x%02x\n",msg.u.formMsg.u.swdmMsg.u.loadSeg.length);
        printf("Data        :  0x%02x\n",msg.u.formMsg.u.swdmMsg.u.loadSeg.data[0]);
    }
                                                                                                                            
    return ITS_SUCCESS;
}
  
/************************************************************************
*implementation:internal
*
* PURPOSE:
*       This function reads the Load Data Segment, Load Data Segment Ack
*        information elements from the file
* INPUT:
*       msg - input message to be encoded
*       fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*************************************************************************/

ITS_INT
ReadLoadDataSeg(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    char c;
    char str[10];
    long l1;
    unsigned char temp1;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: LOAD DATA SEGMENT\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"LOAD_DATA_SEG START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"LOAD_DATA_SEG END\n")!=0)
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
               ReadCommonElems(line,msg);              
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
    kcount=k;

    if (param != 7) /* Checks for the no of Info elem */
    {
        printf("Enter the data correctly\n");
        exit(1);                                                                                                                 }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    if (choice == 4)
    {
        printf("MESSAGE NAME: LOAD DATA SEGMENT \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x04)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 5)
    {
        printf("MESSAGE NAME: LOAD DATA SEGMENT ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x05)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
                                                                                                                             
        if (k==8)
        {
            msg->u.formMsg.u.swdmMsg.u.loadSeg.length = temp[k];
            printf("Length    :   0x%02x\n",
                       msg->u.formMsg.u.swdmMsg.u.loadSeg.length);
        }
                                                                                                                             
        if (k==9)
        {
            printf("Data      :   0x%02x\n",temp[k]);
            for(i=0;i<msg->u.formMsg.u.swdmMsg.u.loadSeg.length;i++)
            {
               msg->u.formMsg.u.swdmMsg.u.loadSeg.data[i] = temp[k];
            }
        }
    }
    fclose(fp);
}   

/*************************************************************************
*implementation:internal
*
* PURPOSE:
*       Handles reading the Load Data Abort information elements from the file,
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
**************************************************************************/

static ITS_INT
HandleLoadDataAbort(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadLoadDataAbort(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Load Data Abort Failed  ret :: %d\n", ret);
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding Load Data Abort Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Load Data Initiate Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Load Data Initiate Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
    }
                                                                                                                            
    return ITS_SUCCESS;
}

/***********************************************************************
*implementation:internal
*
* PURPOSE:
*       This function reads the Load Data Abort information elements from the 
        file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*************************************************************************/

ITS_INT
ReadLoadDataAbort(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    int i=0;
    int param = 0;
    int linecount=0;
    char c;
    char str[10];
    long l;
    unsigned char temp;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: LOAD DATA ABORT\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"LOAD_DATA_ABORT START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"LOAD_DATA_ABORT END\n")!=0)
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
               if(strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l=strtol(str,NULL,16);
                   temp=(unsigned char)l;
                   msg->u.formMsg.formGenElemnts.msgType = temp;
               } 
               ReadCommonElems(line,msg);             
          }
          break;
      }
    } 
    
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");

    if (param != 6) /* Checks for the no of Info elem */
    {
        printf("Enter the data correctly\n");
        exit(1);                                                                                                                 }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);         
    fclose(fp);
}       

/****************************************************************************
*implementation:internal
*
* PURPOSE:
*       Handles reading the Load Data End,Ack,Nack information elements from the 
*        file,encoding and then decoding
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
**************************************************************************/

static ITS_INT
HandleLoadDataEnd(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadLoadDataEnd(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding  Failed  ret :: %d\n", ret);
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
        printf("Decoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        printf("fileIdLen   :  0x%02x\n",
                         msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileIdLen);
        printf("fileId      :  0x%02x\n",
                         msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileId[0]);
        printf("fileVerLen  :  0x%02x\n",
                        msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVerLen);
        printf("fileVer     :  0x%02x\n",
                        msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVer[0]);
        
    }
                                                                                                                            
    return ITS_SUCCESS;
}
 
/*************************************************************************
*implementation:internal
*
* PURPOSE:
*       This function reads the Load Data End,Ack,Nack information elements 
*       from the file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*************************************************************************/
 
ITS_INT
ReadLoadDataEnd(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    char c;
    char str[10];
    long l1;
    unsigned char temp1;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: LOAD DATA END\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"LOAD_DATA_END START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"LOAD_DATA_END END\n")!=0)
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
               ReadCommonElems(line,msg);              
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
    kcount =k;
    if (param != 8) /* Checks for the no of Info elem */
    {
        printf("Enter the data correctly\n");
        exit(1);                                                                                                                 }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    if (choice == 7)
    {
        printf("MESSAGE NAME: LOAD DATA END \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x07)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 8)
    {
        printf("MESSAGE NAME: LOAD DATA END ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x08)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 9)
    {
        printf("MESSAGE NAME: LOAD DATA END NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x09)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);         
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
                                                                                                                             
        if (k==7)
        {
            msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileIdLen = temp[k];
            printf("fileIdLen :   0x%02x\n",
                    msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileIdLen);
        }
                                                                                                                             
        if (k==8)
        {
            printf("fileId    :   0x%02x\n",temp[k]);
            for(i=0;i<msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileIdLen;i++)
            {
               msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileId[i] = temp[k];
            }
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVerLen = temp[k];
            printf("fileVerLen:   0x%02x\n",
                    msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVerLen);
        }
                                                                                                                             
        if (k==10)
        {
            printf("fileVer   :   0x%02x\n",temp[k]);
            for(i=0;i<msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVerLen;i++)
            {
               msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr.fileVer[i] = temp[k];
            }

        }
                                                                                                                             
     }
    fclose(fp);
}

/**************************************************************************
*implementation:internal
*
* PURPOSE:
*       Handles reading the Software Activation Request,Ack,Nack Information 
*       elements from the file,encoding and then decoding
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
****************************************************************************/

static ITS_INT
HandleSWActReq(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadSWActReq(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding SW Activate Acknowledge Failed  ret :: %d\n", ret);
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding SW Activate Acknowledge Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SW Activate Acknowledge  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding SW Activate Acknowledge Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        printf("hwConfLen   :   0x%02x\n",
                         msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.length);
        printf("equipIdLen  :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].equipIdLen);
        printf("equipId     :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].equipId[0]); 
        printf("equipTypeLen:   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].equipTypeLen); 
        printf("equipType   :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].equipType[0]);
        printf("equipVerLen :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].equipVerLen);
        printf("equipVer    :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].equipVer[0]);
        printf("LocLen      :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].locLen);          
        printf("Location    :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].location[0]); 
        printf("InfoLen     :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].infoLen);
        printf("Info        :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[0].info[0]); 
        printf("SWConfLen   :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.swConfig.length);
        printf("fileIdLen   :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[0].fileIdLen);
        printf("fileId      :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[0].fileId[0]);
        printf("fileVerLen  :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[0].fileVerLen);
        printf("fileVer     :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[0].fileVer[0]);
        if (choice == 12)
        {
            printf("nackCuase   :   0x%02x\n",msg.u.formMsg.u.swdmMsg.u.loadInit.nackCuase);
        }

    }
                                                                                                                            
    return ITS_SUCCESS;
}
  
/*************************************************************************
*implementation:internal
*
* PURPOSE:
*       This function reads the Software Activation Request,Ack, Nack 
*       information elements from the file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
************************************************************************/

ITS_INT
ReadSWActReq(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    char c;
    char str[10];
    long l1;
    unsigned char temp1;
    int j =0;                                                                                                                         
    printf("                        \n");
    printf("Message Name: SOFTWARE ACTIVATE ACK\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"SW_ACT_REQ START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"SW_ACT_REQ END\n")!=0)
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
               ReadCommonElems(line,msg);              
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
    kcount =k;
    printf("param is %d\n",param);
    if (param != 9) /* Checks for the no of Info elem */
    {
        printf("Enter the data correctly\n");
        exit(1);                                                                                                                 }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    if (choice == 10)
    {
        printf("MESSAGE NAME: SOFTWARE ACTIVATE REQUEST \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x0a)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 11)
    {
        printf("MESSAGE NAME: SOFTWARE ACTIVATE REQUEST ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x0b)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 12)
    {
        printf("MESSAGE NAME: SOFTWARE ACTIVATE REQUEST NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x0c)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);         
   
    /* Allocate Memory for hardware description */
    msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc =
    (HW_DESCRIPTION *)calloc(msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length, sizeof(HW_DESCRIPTION));

    /* Allocate Memory for software description */
    msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc =
    (SW_DESCRIPTION *)calloc(msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length, sizeof(SW_DESCRIPTION));

    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
                                                                                                                             
        if (k==8)
        {
            msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length = temp[k];
            printf("hwConfLen :   0x%02x\n",
                         msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length);
        }
        if (k==9)
        {
            printf("equipIdLen:   0x%02x\n",temp[k]);
            for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
            {
                 msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].equipIdLen = temp[k];
            }
        }
        if (k==10)
        {
            printf("equipId   :   0x%02x\n",temp[k]);
            for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
            {
                for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].equipIdLen; j++)
                {
                     msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].equipId[j] = temp[k];
                } 

            }

        }
        if (k==11)
        {
            printf("equpTpeLen:   0x%02x\n",temp[k]);
            for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
            {
                 msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].equipTypeLen = temp[k];
            }

        }
        if (k==12)
        {
            printf("equipType :   0x%02x\n",temp[k]);
            for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
            {
                for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].equipTypeLen; j++)
                {
                     msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].equipType[j] = temp[k];
                } 

            }

       }
       
       if (k==13)
       {
           printf("equipVerLen:   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
           {
               msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].equipVerLen = temp[k];
           }

       }
       if (k==14)
       {
           printf("equipVer   :   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
           {
               for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].equipVerLen; j++)
               {
                   msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].equipVer[j] = temp[k];
               } 

           }

       }
       if (k==15)
       {
           printf("LocLen     :   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
           {
               msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].locLen = temp[k];
           }

       }
       if (k==16)
       {
           printf("Location   :   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
           {
               for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].locLen; j++)
               {
                   msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].location[j] = temp[k];
               } 

           }

       }
       if (k==17)
       {
           printf("InfoLen    :   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
           {
               msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].infoLen = temp[k];
           }

       }
       if (k==18)
       {
           printf("Info       :   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length;i++)
           {
               for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].infoLen; j++)
               {
                   msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[i].info[j] = temp[k];
               } 

           }

       }
       if (k==19)
       {
           msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length = temp[k];
           printf("SWConfLen  :   0x%02x\n",
                         msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length);
       }
        
       if (k==20)
       {
           printf("fileIdLen  :   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length;i++)
           {
               msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[i].fileIdLen = temp[k];
           }
                                                                                                                             
       }
       if (k==21)
       {
           printf("fileId     :   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length;i++)
           {
               for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[i].fileIdLen; j++)
               {
                   msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[i].fileId[j] = temp[k];
               }
                                                                                                                             
           }
                                                                                                                             
       }

       if (k==22)
       {
           printf("fileVerLen :   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length;i++)
           {
               msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[i].fileVerLen = temp[k];
           }
                                                                                                                             
       }

       if (k==23)
       {
           printf("fileVer    :   0x%02x\n",temp[k]);
           for(i=0;i<msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length;i++)
           {
               for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[i].fileVerLen; j++)
               {
                   msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[i].fileVer[j] = temp[k];
               }
                                                                                                                             
           }
                                                                                                                             
       }
       if (k==24)
       {   
           if (choice == 12)
           {
               msg->u.formMsg.u.swdmMsg.u.loadInit.nackCuase = temp[k];
               printf("nackCuase  :   0x%02x\n",
                             msg->u.formMsg.u.swdmMsg.u.loadInit.nackCuase);
           }
       }
    }
    fclose(fp);
}

/*****************************************************************************
*implementation:internal
* PURPOSE:
*       Handles reading the Activate Software information elements from the file,
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
****************************************************************************/

HandleActSW(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    int no_elem = 0;
    no_elem = ReadActSW(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
     
    printf("*****Before encode,after reading fileVerLen:   0x%04x\n",
                    msg.u.formMsg.u.swdmMsg.u.actSw.swDescr.fileVerLen);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Activate Software Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding Activate Software Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);
                                                                                                                             
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Activate Software Initiate Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Activate Software Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        if (no_elem == 7)
        {
            printf("fileIdLen   :  0x%02x\n",
                        msg.u.formMsg.u.swdmMsg.u.actSw.swDescr.fileIdLen);
            printf("fileId      :  0x%02x\n",
                         msg.u.formMsg.u.swdmMsg.u.actSw.swDescr.fileId[0]);
            printf("fileVerLen  :  0x%02x\n",
                        msg.u.formMsg.u.swdmMsg.u.actSw.swDescr.fileVerLen);
            printf("fileVer     :  0x%02x\n",
                        msg.u.formMsg.u.swdmMsg.u.actSw.swDescr.fileVer[0]);
        }

        if (choice == 15)
        {
           printf("nackCause   :  0x%02x\n",
                               msg.u.formMsg.u.swdmMsg.u.actSw.nackCuase);
        }    
    }
                                                                                                                             
    return ITS_SUCCESS;
}

/*************************************************************************
*implementation:internal
*
* PURPOSE:
*       This function reads the Activate Software information elements from the 
        file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
************************************************************************/
                                                                                                                           
ITS_INT
ReadActSW(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    int i=0;
    int param = 0;
    int linecount=0;
    int j = 0;
    char c;
    char str[10],str1[10],str2[10],str3[10];
    long l[100];
    unsigned char temp[100];
    long l1;
    unsigned char temp1; 
    int k;                                                                                                                         
    printf("                        \n");
    printf("Message Name: ACTIVATE SOFTWARE \n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    CLEAR_NM_SWDM_AS_OPTIONAL_BIT_MAP(msg);

    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"ACT_SW START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"ACT_SW END\n")!=0)
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
               ReadCommonElems(line,msg);
               if (line[0] == 'M' || line[0]=='O' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }
               /* Check for NACK */
               if (choice == 15)
               {
                  if (strstr(line,"Nack Cause"))
                  {
                      sscanf(line,"%c %s",&c,&str);
                      l1=strtol(str,NULL,16);
                      temp1=(unsigned char)l1;
                      msg->u.formMsg.u.swdmMsg.u.actSw.nackCuase = temp1;
                  }
              }
              /* Check for Optional Parameter */     
              if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"opt1"))
              {  
                  SET_NM_SWDM_AS_SW_DESCRIPTION(msg);
                  sscanf(line,"%c %s %s %s %s ",&c,&str,&str1,&str2,&str3);
                  for (i=0;i<10;i++)
                  {
                      if (i==0)
                      { 
                          l[i]=strtol(str,NULL,16);
                          //temp[i]=(unsigned char)l[i];
                          msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileIdLen = (ITS_USHORT)l[i];  
                      }
 
                     if (i==1)
                      {
                          l[i]=strtol(str,NULL,16);
                          temp[i]=(unsigned char)l[i];
                          for(j=0;j<msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileIdLen;j++)
                          {
                              msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileId[j] = temp[i];
                          }

                      }
                      if (i==2)
                      { 
                          l[i]=strtol(str,NULL,16);
                          temp[i]=(unsigned char)l[i];
                          msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileVerLen = (ITS_USHORT)l[i];  
                      }
                      
                      if (i==3)
                      {
                          l[i]=strtol(str,NULL,16);
                          temp[i]=(unsigned char)l[i];
                          for(j=0;j<msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileVerLen;j++)
                          {
                              msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileVer[j] = temp[i];
                          }

                      }

                  }
                           
              }
          }
          break;
      }
    }
                                                                                                                             
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    printf("%d\n",param);
    if (param == 8 || param == 7) /* Checks for the no of Info elem */
    {
    }
    else
    {
        printf("enter data\n");
        exit(1);
    } 
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    if (choice == 13)
    {
        printf("MESSAGE NAME: ACTIVATE SW \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x0d)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 14)
    {
        printf("MESSAGE NAME: ACTIVATE SW ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x0e)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 15)
    {
        printf("MESSAGE NAME: ACTIVATE SW NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x0f)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
         printf("fileIdLen :   0x%04x\n",
                    msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileIdLen);
         printf("fileId    :   0x%02x\n",msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileId[0]);
         printf("fileVerLen:   0x%04x\n",
                    msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileVerLen);
         printf("fileVer   :   0x%02x\n",msg->u.formMsg.u.swdmMsg.u.actSw.swDescr.fileVer[0]);
    if (choice == 15)
    {
        printf("nackCuase :   0x%02x\n",
                             msg->u.formMsg.u.swdmMsg.u.actSw.nackCuase);
    } 
    fclose(fp);
    return param;
}

/*****************************************************************************
*implementation:internal
* PURPOSE:
*       Handles reading the Software Activation Report,Ack,Nack information elements 
*       from the file,encoding and then decoding
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
****************************************************************************/

static ITS_INT
HandleSWActRep(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadSWActRep(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding SW Activated Report Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding SW Activated Report Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);
                                                                                                                             
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SW Activated Report Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding SW Activated Report Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
    }
                                                                                                                             
    return ITS_SUCCESS;
}

/*************************************************************************
*implementation:internal
*
* PURPOSE:
*       This function reads the Software Activation Report,Ack,Nack information 
*       elements from the file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
**************************************************************************/

ITS_INT
ReadSWActRep(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    int i=0;
    int param = 0;
    int linecount=0;
    char c;
    char str[10];
    long l;
    unsigned char temp;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: SOFTWARE ACTIVATED REPORT\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"SW_ACT_REP START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"SW_ACT_REP END\n")!=0)
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
               if(strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l=strtol(str,NULL,16);
                   temp=(unsigned char)l;
                   msg->u.formMsg.formGenElemnts.msgType = temp;
               }
               ReadCommonElems(line,msg);
          }
          break;
      }
    }
                                                                                                                             
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
                                                                                                                             
    if (param != 6) /* Checks for the no of Info elem */
    {
        printf("Enter the data correctly\n");
        exit(1);     
    }
                                                                                                                             
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    fclose(fp);
}

/***************************************************************************
*implementation:internal
*
* PURPOSE:
*       Handles reading the Establish TEI information elements from the file,
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
****************************************************************************/

static ITS_INT
HandleEstablishTEI(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadEstablishTEI(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Establish TEI Failed  ret :: %d\n", ret);
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding Establish TEI Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Establish TEI Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Establish TEI  Success  ret :: %d\n", ret);
        printDecCommonElems(msg);

        printf("teiVal      :   0x%02x\n",
                               msg.u.formMsg.u.abisMsg.u.estaTei.teiVal);
        printf("btsPort     :   0x%02x\n",
                              msg.u.formMsg.u.abisMsg.abisChanl.btsPortNum);
        printf("timeSlot    :   0x%02x\n",
                              msg.u.formMsg.u.abisMsg.abisChanl.timeSlotNum);
        printf("subSlotN    :   0x%02x\n",
                              msg.u.formMsg.u.abisMsg.abisChanl.subSlotNum);
        if (choice == 3)
        {
            printf("nack    :   0x%02x\n",
                               msg.u.formMsg.u.abisMsg.u.estaTei.nackCuase);
        }
    }
                                                                                                                            
    return ITS_SUCCESS;
}
 
/************************************************************************
*implementation:internal
*
* PURPOSE:
*       This function reads the Establish TEI,Ack,Nack information elements 
*       from the file
* INPUT:
*       msg - input message to be encoded
*       fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
**********************************************************************/
 
ITS_INT
ReadEstablishTEI(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    char c;
    char str[10];
    long l1;
    unsigned char temp1;
                                                                                                                             
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"EST_TEI START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"EST_TEI END\n")!=0)
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
                   

               ReadCommonElems(line,msg);              
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
    kcount =k;
    if (param != 9) /* Checks for the no of Info elem */
    {
        printf("Enter the data correctly\n");
        exit(1);                                                                                                                 }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    
    if (choice == 1)
    {
        printf("Message Name: ESTABLISH TEI\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x21 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  
    if (choice == 2)
    {
        printf("Message Name: ESTABLISH TEI ACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x22 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  
    if (choice == 3)
    {
        printf("Message Name: ESTABLISH TEI NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x23)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        
        if (k==8)
        {
            msg->u.formMsg.u.abisMsg.u.estaTei.teiVal = temp[k];
            printf("teiVal   :   0x%02x\n",
                               msg->u.formMsg.u.abisMsg.u.estaTei.teiVal);
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.formMsg.u.abisMsg.abisChanl.btsPortNum = temp[k];
            printf("btsPort  :   0x%02x\n",
                              msg->u.formMsg.u.abisMsg.abisChanl.btsPortNum);
        }
                                                                                                                             
        if (k==10)
        {
            msg->u.formMsg.u.abisMsg.abisChanl.timeSlotNum = temp[k];
            printf("timeSlot :   0x%02x\n",
                              msg->u.formMsg.u.abisMsg.abisChanl.timeSlotNum);
        }
                                                                                                                             
        if (k==11)
        {
            msg->u.formMsg.u.abisMsg.abisChanl.subSlotNum = temp[k];
            printf("subSlotN :   0x%02x\n",
                              msg->u.formMsg.u.abisMsg.abisChanl.subSlotNum);
        }
                                                                                                                             
       if (k==12)
       {
            if (choice == 3)
            {
                 msg->u.formMsg.u.abisMsg.u.estaTei.nackCuase = temp[k];
                 printf("Nack:   0x%02x\n",
                               msg->u.formMsg.u.abisMsg.u.estaTei.nackCuase);

            }

       }
                                                                                                                             
     }
    fclose(fp);
}
/*****************************************************************************
*implementation:internal
*
* PURPOSE:
*       Handles reading the Connection Terrestrial Signalling,Ack,Nack information 
*       elements from the file,encoding and then decoding
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
*****************************************************************************/

static ITS_INT
HandleConTerSig(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadConTerSig(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding  Failed  ret :: %d\n", ret);
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
        printf("Decoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        printf("btsPort     :   0x%02x\n",
                              msg.u.formMsg.u.abisMsg.abisChanl.btsPortNum);
        printf("timeSlot    :   0x%02x\n",
                              msg.u.formMsg.u.abisMsg.abisChanl.timeSlotNum);
        printf("subSlotN    :   0x%02x\n",
                              msg.u.formMsg.u.abisMsg.abisChanl.subSlotNum);
        if (choice == 6)
        {
            printf("nack    :   0x%02x\n",
                                  msg.u.formMsg.u.abisMsg.u.connTerr.nackCuase); 
        }
    }
                                                                                                                            
    return ITS_SUCCESS;
}

/*************************************************************************
*implementation:internal
*
* PURPOSE:
*       This function reads the Connect/Disconnect Terrestrial Signalling,Ack,Nack
*         information elements from the file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
************************************************************************/

ITS_INT
ReadConTerSig(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    char c;
    char str[10];
    long l1;
    unsigned char temp1;
                                                                                                                             
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"TERRESTRIAL_SIGNALLING START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"TERRESTRIAL_SIGNALLING END\n")!=0)
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
                   

               ReadCommonElems(line,msg);              
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
    kcount =k;
    if (param != 8) /* Checks for the no of Info elem */
    {
        printf("Enter the data correctly\n");
        exit(1);                                                                                                                 }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    
    if (choice == 4)
    {
        printf("Message Name: CONNECT TERRESTRIAL SIGNALLING\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x24 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
   }
    if (choice == 5)
    {
        printf("Message Name: CONNECT TERRESTRIAL SIGNALLING ACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x25 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
   }

    if (choice == 6)
    {
        printf("Message Name: CONNECT TERRESTRIAL SIGNALLING NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x26 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 7)
    {
        printf("Message Name: DISCONNECT TERRESTRIAL SIGNALLING \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x27 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 8)
    {
       printf("Message Name: DISCONNECT TERRESTRIAL SIGNALLING ACK\n");
       if ( msg->u.formMsg.formGenElemnts.msgType != 0x28 )
       {
            printf("Enter the correct message type\n");
            exit(1);
       }
    }
    if (choice == 9)
    {
        printf("Message Name: DISCONNECT TERRESTRIAL SIGNALLING NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x29 )
        {
            printf("Enter the correct message type\n");
            exit(1);
       }
    }
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        
        if (k==8)
        {
            msg->u.formMsg.u.abisMsg.abisChanl.btsPortNum = temp[k];
            printf("btsPort  :   0x%02x\n",
                              msg->u.formMsg.u.abisMsg.abisChanl.btsPortNum);
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.formMsg.u.abisMsg.abisChanl.timeSlotNum = temp[k];
            printf("timeSlot :   0x%02x\n",
                              msg->u.formMsg.u.abisMsg.abisChanl.timeSlotNum);
        }
                                                                                                                             
        if (k==10)
        {
            msg->u.formMsg.u.abisMsg.abisChanl.subSlotNum = temp[k];
            printf("subSlotN :   0x%02x\n",
                              msg->u.formMsg.u.abisMsg.abisChanl.subSlotNum);
        }
                                                                                                                             
       if (k==11)
       {
            if (choice == 6 || choice == 9 )
            {
                 msg->u.formMsg.u.abisMsg.u.connTerr.nackCuase  = temp[k];
                 printf("Nack:   0x%02x\n",
                               msg->u.formMsg.u.abisMsg.u.connTerr.nackCuase);

            }

       }
                                                                                                                             
     }
    fclose(fp);
}
/*****************************************************************************
*implementation:internal
* PURPOSE:
*       Handles reading the Connect/Disconnect Terrestrial Traffic,Ack,Nack 
*       information elements from the file,encoding and then decoding
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
*****************************************************************************/
static ITS_INT
HandleConTerTrff(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    int no_elem = 0;
    no_elem = ReadConTerTrff(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding  Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        printf("btsPort     :   0x%02x\n",
                              msg.u.formMsg.u.abisMsg.abisChanl.btsPortNum);
        printf("timeSlot    :   0x%02x\n",
                              msg.u.formMsg.u.abisMsg.abisChanl.timeSlotNum);
        printf("subSlotN    :   0x%02x\n",
                              msg.u.formMsg.u.abisMsg.abisChanl.subSlotNum);
        if (choice == 12 || choice == 15)
        {
            printf("nack    :   0x%02x\n",
                                  msg.u.formMsg.u.abisMsg.u.connTraf.nackCuase); 
        }
        
        if (no_elem == 9)
        {
            printf("RadioSubChan :   0x%02x\n",msg.u.formMsg.u.abisMsg.u.connTraf.radioSubChanl);
        }
    }
                                                                                                                            
    return ITS_SUCCESS;
}
 
/*implementation:internal
*
* PURPOSE:
*       This function reads the data request information elements from the 
        file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*
*/

ITS_INT
ReadConTerTrff(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    char c;
    char str[10];
    int true = 0;
                                                                                                                             
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    CLEAR_NM_AM_CTT_OPTIONAL_BIT_MAP((msg));
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"TERRESTRIAL_TRAFFIC START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"TERRESTRIAL_TRAFFIC END\n")!=0)
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
                
               if (line[0] == 'M' || line [0] == 'O' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }
               
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"RadioSubChannel"))
               {
                    true = 1;
                    SET_NM_AM_CTT_RADIO_SUB_CHANNEL ((msg));
                    sscanf(line,"%c %s",&c,&str);
                    l[0]=strtol(str,NULL,16);
                    temp[0]=(unsigned char)l[0];
                    msg->u.formMsg.u.abisMsg.u.connTraf.radioSubChanl = temp[0];
               }

               ReadCommonElems(line,msg);              
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
    
    if (choice == 10)
    {
        printf("Message Name: CONNECT TERRESTRIAL TRAFFIC\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x2a )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
   }
     
    if (choice == 11)
    {
        printf("Message Name: CONNECT TERRESTRIAL TRAFFIC ACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x2b )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
   }


    if (choice == 12)
    {
        printf("Message Name: CONNECT TERRESTRIAL TRAFFIC NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x2c )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
   }
    if (choice == 13)
    {
        printf("Message Name: DISCONNECT TERRESTRIAL TRAFFIC \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x2d )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
   }
    if (choice == 14)
    {
        printf("Message Name: DISCONNECT TERRESTRIAL TRAFFIC ACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x2e )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 15)
    {
        printf("Message Name: DISCONNECT TERRESTRIAL TRAFFIC NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x2f )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    kcount =k;
    printf("PARAM is %d\n",param);
    if (param == 8 || param==9) /* Checks for the no of Info elem */
    {

    }
    else
    {     
        printf("Enter the data correctly\n");
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        
        if (k==8)
        {
            msg->u.formMsg.u.abisMsg.abisChanl.btsPortNum = temp[k];
            printf("btsPort  :   0x%02x\n",
                              msg->u.formMsg.u.abisMsg.abisChanl.btsPortNum);
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.formMsg.u.abisMsg.abisChanl.timeSlotNum = temp[k];
            printf("timeSlot :   0x%02x\n",
                              msg->u.formMsg.u.abisMsg.abisChanl.timeSlotNum);
        }
                                                                                                                             
        if (k==10)
        {
            msg->u.formMsg.u.abisMsg.abisChanl.subSlotNum = temp[k];
            printf("subSlotN :   0x%02x\n",
                              msg->u.formMsg.u.abisMsg.abisChanl.subSlotNum);
        }
                                                                                                                             
       if (k==11)
       {
            if (choice == 12 || choice == 15)
            {
                 msg->u.formMsg.u.abisMsg.u.connTerr.nackCuase  = temp[k];
                 printf("Nack     :   0x%02x\n",
                               msg->u.formMsg.u.abisMsg.u.connTraf.nackCuase);

            }

       }
                                                                                                                             
     }
    
    if (true == 1)
    {
        printf("Radio SubCh :   0x%02x\n",msg->u.formMsg.u.abisMsg.u.connTraf.radioSubChanl);
    }
    return param; 
    fclose(fp);
}
/********************************************************************************
*implementation:internal
*
* PURPOSE:
*       Handles reading the Connect/Discoonect Multi Drop Link,Ack,Nack information 
*       elements from the file,encoding and then decoding
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
******************************************************************************/
static ITS_INT
HandleMulDropLink(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadMulDropLink(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
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
        printf("Decoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        printf("BSC-BtsPrtNo  :   0x%02x\n",
                      msg.u.formMsg.u.transMsg.u.conLink.bscLink.btsPortNum);
        printf("BSC-timeSlotNo:   0x%02x\n",
                         msg.u.formMsg.u.transMsg.u.conLink.bscLink.timeSlotNum);
        printf("BTS-BtsPrtNo  :   0x%02x\n",
                         msg.u.formMsg.u.transMsg.u.conLink.btsLink.btsPortNum);
        printf("BTS-timeSlotNo:   0x%02x\n",
                         msg.u.formMsg.u.transMsg.u.conLink.btsLink.timeSlotNum);

        if (choice == 3 || choice == 6)
        {
            printf("nack    :   0x%02x\n",
                                msg.u.formMsg.u.transMsg.u.conLink.nackCuase);
        }
    }
                                                                                                                            
    return ITS_SUCCESS;
}

/*************************************************************************
*implementation:internal
*
* PURPOSE:
*       This function reads the Connect/Disconnect Multi drop Link,Ack 
*       Nack information elements from the file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
**************************************************************************/
  
ITS_INT
ReadMulDropLink(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    char c;
    char str[10];
    long l1;
    unsigned char temp1;
                                                                                                                             
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"MULTI_DROP_LINK START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"MULTI_DROP_LINK END\n")!=0)
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
                   

               ReadCommonElems(line,msg);              
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
    kcount =k;
    if (param != 9) /* Checks for the no of Info elem */
    {
        printf("Enter the data correctly\n");
        exit(1);                                                                                                                 }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    
    if (choice == 1)
    {
        printf("Message Name: CONNECT MULTI DROP LINK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x31 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  
    if (choice == 2)
    {
        printf("Message Name: CONNECT MULTI DROP LINK ACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x32 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  
    if (choice == 3)
    {
        printf("Message Name: CONNECT MULTIDROP LINK NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x33)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  
     
    if (choice == 4)
    {
        printf("Message Name: DISCONNECT MULTI DROP LINK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x34)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  

    if (choice == 5 )
    {
        printf("Message Name: DISCONNECT MULTI DROP LINK ACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x35)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 6)
    {
        printf("Message Name: DISCONNECT MULTI DROP LINK NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x36)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }  
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        
        if (k==8)
        {
            msg->u.formMsg.u.transMsg.u.conLink.bscLink.btsPortNum = temp[k];
            printf("BSC-BtsPortNo :   0x%02x\n",
                         msg->u.formMsg.u.transMsg.u.conLink.bscLink.btsPortNum);
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.formMsg.u.transMsg.u.conLink.bscLink.timeSlotNum = temp[k];
            printf("BSC-timeSlotNo:   0x%02x\n",
                         msg->u.formMsg.u.transMsg.u.conLink.bscLink.timeSlotNum);
        }
                                                                                                                             
        if (k==10)
        {
            msg->u.formMsg.u.transMsg.u.conLink.btsLink.btsPortNum = temp[k];
            printf("BTS-BtsPrtNo :   0x%02x\n",
                              msg->u.formMsg.u.transMsg.u.conLink.btsLink.btsPortNum);
        }
                                                                                                                             
        if (k==11)
        {
            msg->u.formMsg.u.transMsg.u.conLink.btsLink.timeSlotNum = temp[k];
            printf("BTS-timeSlot :   0x%02x\n",
                              msg->u.formMsg.u.transMsg.u.conLink.btsLink.timeSlotNum);
        }
                                                                                                                             
       if (k==12)
       {
            if (choice == 3 || choice == 6)
            {
                 msg->u.formMsg.u.abisMsg.u.estaTei.nackCuase = temp[k];
                 printf("Nack:   0x%02x\n",
                                 msg->u.formMsg.u.transMsg.u.conLink.nackCuase);
            }

       }
                                                                                                                             
     }
    fclose(fp);
}

/**************** AIR INTERFACE MANAGEMENT MESSAGES  **************************/

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Set Bts Attributes, Ack, Nack information elements 
*        from the file,encoding and then decoding
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
*
*/

static ITS_INT
HandleSetBtsAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[300];
    ITS_UINT ret = 0, i, len;
    FILE *fptr;
    char line[1024];
    memset(&msg, 0,sizeof(ABIS_NETWORK_MANAGEMENT_MSG));
    ReadSetBtsAttr(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    printf("\n\n\n\n Value : %d\n\n\n\n", msg.u.formMsg.u.airMsg.u.btsAttr.conFail.length); 
    printf("\n\n\n\n Value : %d\n\n\n\n", msg.u.formMsg.u.airMsg.u.btsAttr.overldPeriod.length); 
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    printf("\n\n\n\n length : %d\n\n\n\n", len); 
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
    memset(&msg,0,sizeof(ABIS_NETWORK_MANAGEMENT_MSG));
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        if (choice == 3)
        {
             printf("Nack:   0x%02x\n",
                                 msg.u.formMsg.u.airMsg.u.btsAttr.nackCuase);
        }
        fptr = fopen(filename,"r");
        while (feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"SET_BTS_ATTR START\n")==0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),"SET_BTS_ATTR END\n")!=0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                    && strstr(line,"InterferenceLevelBoundaries"))
                    {
                        printf("interfBound0 : 0x%02x\n",
                        msg.u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound0);
                        printf("interfBound1 : 0x%02x\n",
                        msg.u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound1);
                        printf("interfBound2 : 0x%02x\n",
                        msg.u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound2);
                        printf("interfBound3 : 0x%02x\n",
                        msg.u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound3);
                        printf("interfBound4 : 0x%02x\n",
                        msg.u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound4);
                        printf("interfBound5 : 0x%02x\n",
                        msg.u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound5);
                     }
 
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"Intave Parameter"))
                     {
                         printf("intaveParam : 0x%02x\n",
                                   msg.u.formMsg.u.airMsg.u.btsAttr.intaveParam);
                     }
 
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"ConnectionFailureCriterion"))
                     {
                         printf("length       : 0x%02x\n",
                                msg.u.formMsg.u.airMsg.u.btsAttr.conFail.length);
                         printf("failCrit     : 0x%02x\n",
                              msg.u.formMsg.u.airMsg.u.btsAttr.conFail.failCrit);
                         printf("critVal[0]   : 0x%02x\n",
                             msg.u.formMsg.u.airMsg.u.btsAttr.conFail.critVal[0]);
                     }

                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"T200"))
                     {
                         printf("sdcch        : 0x%02x\n", 
                                      msg.u.formMsg.u.airMsg.u.btsAttr.t200.sdcch);
                         printf("facchFull    : 0x%02x\n", 
                                  msg.u.formMsg.u.airMsg.u.btsAttr.t200.facchFull);
                         printf("facchHalf    : 0x%02x\n", 
                                  msg.u.formMsg.u.airMsg.u.btsAttr.t200.facchHalf);
                         printf("sacchSap10   : 0x%02x\n", 
                                 msg.u.formMsg.u.airMsg.u.btsAttr.t200.sacchSap10);
                         printf("sacchSdcch   : 0x%02x\n", 
                                 msg.u.formMsg.u.airMsg.u.btsAttr.t200.sacchSdcch);
                         printf("sdcchSap13   : 0x%02x\n", 
                                 msg.u.formMsg.u.airMsg.u.btsAttr.t200.sdcchSap13);
                         printf("sacchSap13   : 0x%02x\n", 
                                 msg.u.formMsg.u.airMsg.u.btsAttr.t200.sacchSap13);
                      }
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"MaxTimingAdvance"))
                     {
                          printf("maxTimeAdv   : 0x%02x\n", 
                                     msg.u.formMsg.u.airMsg.u.btsAttr.maxTimeAdv);
                     }
 
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"Overload Period"))
                     {
                         printf("overldPeriod : 0x%02x\n",
                                msg.u.formMsg.u.airMsg.u.btsAttr.overldPeriod.length);
                         printf("period       : 0x%02x\n",
                             msg.u.formMsg.u.airMsg.u.btsAttr.overldPeriod.period[0]);
                     }

                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"CCCH Load Threshold"))
                     {
                         printf("threshold    : 0x%02x\n",
                                 msg.u.formMsg.u.airMsg.u.btsAttr.threshold);  
                     }
                     
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"CCCHLoadIndicationPeriod"))
                     {
                         printf("initPeriod   : 0x%02x\n",  
                                           msg.u.formMsg.u.airMsg.u.btsAttr.initPeriod);
                     } 
 
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"RACH Busy Threshold"))
                     {
                         printf("busyThreshold: 0x%02x\n",
                                       msg.u.formMsg.u.airMsg.u.btsAttr.busyThreshold);
                     }
                     
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"RACHLoadAveragingSlots"))
                     {
                         printf("avgSlots     : 0x%02x\n", 
                                           msg.u.formMsg.u.airMsg.u.btsAttr.avgSlots);
                     }

                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"BTS Air Timer"))
                     {
                          printf("airT3105     : 0x%02x\n", 
                                           msg.u.formMsg.u.airMsg.u.btsAttr.airT3105);
                     } 
                    
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"NY1"))
                     {
                           printf("ny1          : 0x%02x\n",
                                                msg.u.formMsg.u.airMsg.u.btsAttr.ny1);   
                     }
                     
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"BCCH ARFCN"))
                     {
                         printf("arfcn        : 0x%02x\n",
                                              msg.u.formMsg.u.airMsg.u.btsAttr.arfcn);
                     }

                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"BSIC"))
                     {
                           printf("bsic         : 0x%02x\n",
                                            msg.u.formMsg.u.airMsg.u.btsAttr.bsic);
                     }

                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"Starting Time"))
                     {
                          printf("FrameNo      : 0x%02x\n",
                                   msg.u.formMsg.u.airMsg.u.btsAttr.startCurFrameNo);
                     } 
                 }
              break;
            }
          
        } 

    }
    fclose(fptr);                                                                                                                        
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       This function reads the Set Bts Attributes,Ack,Nack information elements 
*       from the file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*/
 
ITS_INT
ReadSetBtsAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    char c;
    char str[10],str1[10],str2[10],str3[10],str4[10],str5[10];
    char str6[10];
    long l1;
    unsigned char temp1;
    int optional[20];
    int j = 0;
                                                                                                                             
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    CLEAR_NM_AIM_SBA_OPTIONAL_BIT_MAP(msg);
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"SET_BTS_ATTR START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"SET_BTS_ATTR END\n")!=0)
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
               ReadCommonElems(line,msg);
             
               /* OPTIONAL PARAMETERS */ 

               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"InterferenceLevelBoundaries"))
               {
                   optional[1] = 1;
                   SET_NM_AIM_SBA_INTER_LEVEL_BOUNDARIES(msg);
                   sscanf(line,"%c %s %s %s %s %s %s",&c,&str,&str1,&str2,&str3,str4,&str5);
                   for (i=0;i<10;i++)
                   {
                       if (i==0)
                       {
                           l[i]=strtol(str,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound0 = temp[i];  
                       }    
                        
                       if (i==1)
                       {
                           l[i]=strtol(str1,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound1 = temp[i];  
                       }    
                        
                       if (i==2)
                       {
                           l[i]=strtol(str2,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound2 = temp[i];  
                       }    
                        
                       if (i==3)
                       {
                           l[i]=strtol(str3,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound3 = temp[i];  
                       }    
                        
                       if (i==4)
                       {
                           l[i]=strtol(str4,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound4 = temp[i];  
                       }    

                       if (i==5)
                       {
                           l[i]=strtol(str5,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound5 = temp[i];  
                       }    
                   }
               }

               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"Intave Parameter"))
               {
                   optional[2] = 2;
                   SET_NM_AIM_SBA_INTAVE_PARAMETER(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.intaveParam=temp1;
               }

               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"ConnectionFailureCriterion"))
               {
                   optional[3] = 3;
                   SET_NM_AIM_SBA_CONN_FAILURE_CRITERION(msg);
                   sscanf(line,"%c %s %s %s",&c,&str,&str1,&str2);
                   for (i=0;i<10;i++)
                   {
                       if (i==0)
                       {
                           l[i]=strtol(str,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.conFail.length = temp[i];
                       }
                                                                                                                             
                       if (i==1)
                       {
                           l[i]=strtol(str1,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.conFail.failCrit = temp[i];
                       }
                                                                                                                             
                       if (i==2)
                       {
                           l[i]=strtol(str2,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           for (j=0;j<msg->u.formMsg.u.airMsg.u.btsAttr.conFail.length;j++)
                           {
                               msg->u.formMsg.u.airMsg.u.btsAttr.conFail.critVal[j] = temp[i];
                            }
                       }
                     }
                 }

               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"T200"))
               {
                   optional[4] = 4;
                   SET_NM_AIM_SBA_T200(msg);
                   sscanf(line,"%c %s %s %s %s %s %s %s",&c,
                          &str,&str1,&str2,&str3,&str4,&str5,&str6);
                   for (i=0;i<10;i++)
                   {
                       if (i==0)
                       {
                           l[i]=strtol(str,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.t200.sdcch = temp[i];
                       }
                                                                                                                             
                       if (i==1)
                       {
                           l[i]=strtol(str1,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.t200.facchFull = temp[i];
                       }
                                                                                                                             
                       if (i==2)
                       {
                           l[i]=strtol(str2,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.t200.facchHalf = temp[i];
                       }
                       if (i==3)
                       {
                           l[i]=strtol(str3,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.t200.sacchSap10 = temp[i];
                       }

                        if (i==4)
                       {
                           l[i]=strtol(str4,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.t200.sacchSdcch = temp[i];
                       }
 
                       if (i==5)
                       {
                           l[i]=strtol(str5,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.t200.sdcchSap13 = temp[i];
                       }

                       if (i==6)
                       {
                           l[i]=strtol(str6,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.t200.sacchSap13 = temp[i];
                       }

       
                     }
                 }
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"MaxTimingAdvance"))
               {
                   optional[5] = 5;
                   SET_NM_AIM_SBA_MAX_TIMING_ADVANCE(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.maxTimeAdv = temp1;
               }

                if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"Overload Period"))
                {
                   optional[6] = 6;
                   SET_NM_AIM_SBA_OVERLOAD_PERIOD(msg);
                   sscanf(line,"%c %s %s",&c,&str,&str1);
                   for (i=0;i<3;i++)
                   {
                       if (i==0)
                       {
                           l[i]=strtol(str,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           msg->u.formMsg.u.airMsg.u.btsAttr.overldPeriod.length = temp[i];
                       }
                                                                                                                             
                       if (i==1)
                       {
                           l[i]=strtol(str1,NULL,16);
                           temp[i]=(unsigned char)l[i];
                           for (j=0;j< msg->u.formMsg.u.airMsg.u.btsAttr.overldPeriod.length;j++)
                           {
                                msg->u.formMsg.u.airMsg.u.btsAttr.overldPeriod.period[j] = temp[i];
                           }  
                       }
                    }
                 } 

               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"CCCH Load Threshold"))
               {
                   optional[7] = 7;
                   SET_NM_AIM_SBA_CCCH_LOAD_THRESHOLD(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.threshold = temp1;
               }
                 
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"CCCHLoadIndicationPeriod"))
               {
                   optional[8] = 8;
                   SET_NM_AIM_SBA_CCCH_LOAD_IND_PERIOD(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.initPeriod = temp1;
               }
                  
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"RACH Busy Threshold"))
               {
                   optional[9] = 9;
                   SET_NM_AIM_SBA_RACH_BUSY_THRESHOLD(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.busyThreshold = temp1;
               }
                
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"RACHLoadAveragingSlots"))
               {
                   optional[10] = 10;
                   SET_NM_AIM_SBA_RACH_LOAD_AVG_SLOTS(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.avgSlots = temp1;
               }
                
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"BTS Air Timer"))
               {
                   optional[11] = 11;
                   SET_NM_AIM_SBA_BTS_AIR_TIMER(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.airT3105.tch = temp1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.airT3105.sdcch = temp1;
		   //Added By LN
               }
                
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"NY1"))
               {
                   optional[12] = 12;
                   SET_NM_AIM_SBA_NY1(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.ny1.tch = temp1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.ny1.sdcch = temp1;
		   //Added By LN
               }

                
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"BCCH ARFCN"))
               {
                   optional[13] = 13;
                   SET_NM_AIM_SBA_BCCH_ARFCN(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.arfcn = temp1;
               }
                
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"BSIC"))
               {
                   optional[14] = 14;
                   SET_NM_AIM_SBA_BSIC(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.bsic = temp1;
               }
                
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                  && strstr(line,"Starting Time"))
               {
                   optional[15] = 15;
                   SET_NM_AIM_SBA_STARTING_TIME(msg);
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.u.airMsg.u.btsAttr.startCurFrameNo = temp1;
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
    kcount =k;
    if (param == 7 || param == 6) /* Checks for the no of Info elem */
    {

    }
    else
    {
        printf("Enter the data correctly\n");
        exit(1);                                                                                                                 }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    if (choice == 1)
    {
        printf("MESSAGE NAME : SET BTS ATTRIBUTES\n");
        if (msg->u.formMsg.formGenElemnts.msgType != 0x41)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
     
    if (choice == 2)
    {
        printf("MESSAGE NAME : SET BTS ATTRIBUTES ACK\n");
        if (msg->u.formMsg.formGenElemnts.msgType != 0x42)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
     
    if (choice == 3)
    {
        printf("MESSAGE NAME : SET BTS ATTRIBUTES NACK\n");
        if (msg->u.formMsg.formGenElemnts.msgType != 0x43)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        if (k==8)
        {
            if (choice == 3 )
            {
                 msg->u.formMsg.u.airMsg.u.btsAttr.nackCuase = temp[k];
                 printf("Nack:   0x%02x\n",
                                 msg->u.formMsg.u.airMsg.u.btsAttr.nackCuase);
            }
        }
                                                                                                                             
                                                                                                                             
    }
    if (optional[1] == 1)
    {
        printf("interfBound0 : 0x%02x\n", 
                        msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound0); 
        printf("interfBound1 : 0x%02x\n", 
                        msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound1); 
        printf("interfBound2 : 0x%02x\n", 
                        msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound2); 
        printf("interfBound3 : 0x%02x\n", 
                        msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound3); 
        printf("interfBound4 : 0x%02x\n", 
                        msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound4); 
        printf("interfBound5 : 0x%02x\n", 
                        msg->u.formMsg.u.airMsg.u.btsAttr.interLevel.interfBound5);
    } 
    if (optional[2] == 2)
    {
        printf("intaveParam  : 0x%02x\n",msg->u.formMsg.u.airMsg.u.btsAttr.intaveParam);
    }

    if (optional[3] == 3)
    {
        printf("length       : 0x%02x\n",
                                msg->u.formMsg.u.airMsg.u.btsAttr.conFail.length);
        printf("failCrit     : 0x%02x\n",
                              msg->u.formMsg.u.airMsg.u.btsAttr.conFail.failCrit);
        printf("critVal[0]   : 0x%02x\n",msg->u.formMsg.u.airMsg.u.btsAttr.conFail.critVal[0]);

    }
 
    if (optional[4] == 4)
    {
        printf("sdcch        : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.t200.sdcch);
        printf("facchFull    : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.t200.facchFull);
        printf("facchHalf    : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.t200.facchHalf);
        printf("sacchSap10   : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.t200.sacchSap10);
        printf("sacchSdcch   : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.t200.sacchSdcch);
        printf("sdcchSap13   : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.t200.sdcchSap13);
        printf("sacchSap13   : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.t200.sacchSap13);
    }

    if (optional[5] == 5)
    {
        printf("maxTimeAdv   : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.maxTimeAdv);
    }

    if (optional[6] == 6)
    {
        printf("overldPeriod : 0x%02x\n", 
                                msg->u.formMsg.u.airMsg.u.btsAttr.overldPeriod.length);
        printf("period       : 0x%02x\n", 
                             msg->u.formMsg.u.airMsg.u.btsAttr.overldPeriod.period[0]);
    }
  
    if (optional[7] == 7)
    {
        printf("threshold    : 0x%02x\n",msg->u.formMsg.u.airMsg.u.btsAttr.threshold); 
    }
     
    if (optional[8] == 8)
    {
        printf("initPeriod   : 0x%02x\n",  msg->u.formMsg.u.airMsg.u.btsAttr.initPeriod);
    }
     
    if (optional[9] == 9)
    {
       printf("busyThreshold: 0x%02x\n",msg->u.formMsg.u.airMsg.u.btsAttr.busyThreshold);
    }
     
    if (optional[10] == 10)
    {
        printf("avgSlots     : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.avgSlots);
    }
        
    if (optional[11] == 11)
    {
         printf("airT3105     : 0x%02x\n", msg->u.formMsg.u.airMsg.u.btsAttr.airT3105);     
    }
     
    if (optional[12] == 12)
    {
        printf("ny1          : 0x%02x\n",msg->u.formMsg.u.airMsg.u.btsAttr.ny1);
    }
     
    if (optional[13] == 13)
    {
        printf("arfcn        : 0x%02x\n",msg->u.formMsg.u.airMsg.u.btsAttr.arfcn);
    }
        
    if (optional[14] == 14)
    {
        printf("bsic         : 0x%02x\n",msg->u.formMsg.u.airMsg.u.btsAttr.bsic );
    }
        
    if (optional[15] == 15)
    {
        printf("FrameNo      : 0x%02x\n",msg->u.formMsg.u.airMsg.u.btsAttr.startCurFrameNo);
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Set Radio Attributes,Ack,Nack information elements 
*       from the file,encoding and then decoding
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
*/
static ITS_INT
HandleSetRadioCarAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    int no_elem = 0;
    no_elem = ReadSetRadioCarAttr(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding  Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        
        if (choice == 6)     
        {
            printf("nack    :   0x%02x\n",
                                  msg.u.formMsg.u.abisMsg.u.connTraf.nackCuase); 
        }
        if (no_elem == 10 || no_elem == 12)
        {
           printf("powerRed :   0x%02x\n", msg.u.formMsg.u.airMsg.u.radioAttr.powerRedu);
        }
        if (no_elem == 11 || no_elem == 12)
        {
            printf("length  :   0x%02x\n", msg.u.formMsg.u.airMsg.u.radioAttr.arfcnList.length); 
            printf("arfcn   :   0x%02x\n", msg.u.formMsg.u.airMsg.u.radioAttr.arfcnList.arfcn[0]); 
        }
  
    }
    return ITS_SUCCESS;
}
 
/*implementation:internal
*
* PURPOSE:
*       This function reads the Set Radio carrier Attributes,Ack,Nack information 
*       elements from the file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*
*/
 
ITS_INT
ReadSetRadioCarAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i= 0;
    int j = 0;
    int k=0,kcount;
    int linecount=0;
    unsigned char buffer[100];
    unsigned char temp[100];
    long l[100];
    char c;
    char str[10],str1[10];
    int true = 0;
    int true_opt =0 ;
                                                                                                                             
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    CLEAR_NM_AM_CTT_OPTIONAL_BIT_MAP((msg));
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"SET_RADIO_CAR_ATTR START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"SET_RADIO_CAR_ATTR END\n")!=0)
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
               
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"RFMaxPowerReduction"))
               {
                    true = 1;
                    SET_NM_AIM_SRCA_RF_MAX_POWER_REDUCTION((msg));
                    sscanf(line,"%c %s",&c,&str);
                    l[0]=strtol(str,NULL,16);
                    temp[0]=(unsigned char)l[0];
                    msg->u.formMsg.u.airMsg.u.radioAttr.powerRedu = temp[0];
               }
                
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"ARFCN"))
               {
                    true_opt = 1;
                    SET_NM_AIM_SRCA_ARFCN_LIST((msg));
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i=0;i<3;i++)
                    {
                        if (i==0)
                        {
                            l[i]=strtol(str,NULL,16);
                            temp[i]=(unsigned char)l[i];
                            msg->u.formMsg.u.airMsg.u.radioAttr.arfcnList.length = temp[i];
                        }
                         
                        if (i==1)
                        {
                            l[i]=strtol(str,NULL,16);
                            temp[i]=(unsigned char)l[i];
                            for (j=0;j < msg->u.formMsg.u.airMsg.u.radioAttr.arfcnList.length;j++)
                            {
                                 msg->u.formMsg.u.airMsg.u.radioAttr.arfcnList.arfcn[j] = temp[i]; 
                            }
                        }
                    }
               }
               ReadCommonElems(line,msg);              
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
    
    if (choice == 4)
    {
        printf("Message Name: SET RADIO CARRIER ATTRIBUTES \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x44 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
   }
    if (choice == 5)
    {
        printf("Message Name: SET RADIO CARRIER ATTRIBUTES ACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x45 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 6)
    {
        printf("Message Name: SET RADIO CARRIER ATTRIBUTES NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x46 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    kcount = k;
    if (kcount >= 9) /* Checks for the no of Info elem */
    {

    }
    else
    {     
        printf("Enter the data correctly\n");
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        
        if (k==8)
        {
            if (choice == 6)
            {
                msg->u.formMsg.u.airMsg.u.radioAttr.nackCuase  = temp[k];
                printf("Nack     :   0x%02x\n",
                               msg->u.formMsg.u.airMsg.u.radioAttr.nackCuase);

            }

        }
                                                                                                                             
    }
    if (true == 1)
    {
        printf("powerRed :   0x%02x\n", msg->u.formMsg.u.airMsg.u.radioAttr.powerRedu); 
    }
      
    if (true_opt == 1)
    {
        printf("length  :   0x%02x\n", msg->u.formMsg.u.airMsg.u.radioAttr.arfcnList.length); 
        printf("arfcn   :   0x%02x\n", msg->u.formMsg.u.airMsg.u.radioAttr.arfcnList.arfcn[0]); 
    }
    return kcount; 
    fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Set Channel Attributes,Ack,Nack information elements from the file,
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
*
*/
static ITS_INT
HandleSetChanAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    int no_elem = 0;
    FILE *fptr;
    char line[1024];
    no_elem = ReadSetChanAttr(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding  Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        
        if (choice == 9)
        {
            printf("nack    :   0x%02x\n",
                                msg.u.formMsg.u.airMsg.u.chanlAttr.nackCuase); 
        }
        
        fptr = fopen(filename,"r");
        while (feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"SET_CHANNEL_ATTR START\n")==0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),"SET_CHANNEL_ATTR END\n")!=0)
                {
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"Channel Combination"))
                     { 
                         printf("chanlComb :   0x%02x\n", msg.u.formMsg.u.airMsg.u.chanlAttr.chanlComb );
                     }
                                                                                                                             
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"HSN"))
                     {
                         printf("HSN       :   0x%02x\n",msg.u.formMsg.u.airMsg.u.chanlAttr.hsn);
                     }
                     if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                     && strstr(line,"MAIO"))
                     {
			 msg.u.formMsg.u.airMsg.u.chanlAttr.maioList.len = 1;
			 //Added By LN -- Keep it as  Fixed
                         printf("MAIO len     :   0x%02x\n", msg.u.formMsg.u.airMsg.u.chanlAttr.maioList.len);
			 printf("MAIO 0x%02x\n", msg.u.formMsg.u.airMsg.u.chanlAttr.maioList.maio[0]);
			 
                     }
 
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                    && strstr(line,"ARFCN"))
                    {
                        printf("Length    :   0x%02x\n", 
                                          msg.u.formMsg.u.airMsg.u.chanlAttr.arfcnList.length);
                        printf("ARFCN     :   0x%02x\n", 
                                        msg.u.formMsg.u.airMsg.u.chanlAttr.arfcnList.arfcn[0]);
 
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                    && strstr(line,"StartingTime"))
                    {
                        printf("StrtingTim:   0x%02x\n", 
                                          msg.u.formMsg.u.airMsg.u.chanlAttr.startCurFrameNo);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                    && strstr(line,"TSC"))
                    {
                         printf("TSC       :   0x%02x\n",  
                                           msg.u.formMsg.u.airMsg.u.chanlAttr.tscSeqCode);   
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
*       This function reads the Set Channel Attributes,Ack,Nack information elements 
*       from the file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*
*/

ITS_INT
ReadSetChanAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i= 0;
    int j = 0;
    int k=0,kcount;
    int param = 0;
    int linecount=0;
    unsigned char buffer[100];
    unsigned char temp[100];
    long l[100];
    char c;
    char str[10],str1[10];
    int optional[10];
    
    memset(optional,NULL,0);                                                                                                                         
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    CLEAR_NM_AIM_SCA_OPTIONAL_BIT_MAP((msg));
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"SET_CHANNEL_ATTR START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"SET_CHANNEL_ATTR END\n")!=0)
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
                
               if (line[0] == 'M' || line [0] == 'O' && line[1] == '\t' && line[2] == '0')
               {
                   param++;
               }

               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"Channel Combination"))
               {
                    optional[1] = 1;
                    SET_NM_AIM_SCA_CHANNEL_COMBINATION((msg));
                    sscanf(line,"%c %s",&c,&str);
                    l[0]=strtol(str,NULL,16);
                    temp[0]=(unsigned char)l[0];
                    msg->u.formMsg.u.airMsg.u.chanlAttr.chanlComb = temp[0];
               }
              
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"HSN"))
               {
                    optional[2] = 2;
                    SET_NM_AIM_SCA_HSN((msg));
                    sscanf(line,"%c %s",&c,&str);
                    l[0]=strtol(str,NULL,16);
                    temp[0]=(unsigned char)l[0];
                    msg->u.formMsg.u.airMsg.u.chanlAttr.hsn = temp[0];
               }

               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"MAIO"))
               {
                    optional[3] = 3;
                    SET_NM_AIM_SCA_MAIO((msg));
                    sscanf(line,"%c %s",&c,&str);
                    l[0]=strtol(str,NULL,16);
                    temp[0]=(unsigned char)l[0];

		    msg->u.formMsg.u.airMsg.u.chanlAttr.maioList.len = 1;

		    printf("Taken fixed maio length as 1 here in App..\n");

                    msg->u.formMsg.u.airMsg.u.chanlAttr.maioList.maio[0] = temp[0];
               }

  
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"ARFCN"))
               {
                    optional[4] = 4;
                    SET_NM_AIM_SCA_ARFCN_LIST((msg));
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i=0;i<3;i++)
                    {
                        if (i==0)
                        {
                            l[i]=strtol(str,NULL,16);
                            temp[i]=(unsigned char)l[i];
                            msg->u.formMsg.u.airMsg.u.chanlAttr.arfcnList.length = temp[i];
                        }
                         
                        if (i==1)
                        {
                            l[i]=strtol(str,NULL,16);
                            temp[i]=(unsigned char)l[i];
                            for (j=0;j < msg->u.formMsg.u.airMsg.u.chanlAttr.arfcnList.length;j++)
                            {
                                 msg->u.formMsg.u.airMsg.u.chanlAttr.arfcnList.arfcn[j] = temp[i]; 
                            }
                        }
                    }
               }

                if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"StartingTime"))
               {
                    optional[5] = 5;
                    SET_NM_AIM_SCA_STARTING_TIME((msg));
                    sscanf(line,"%c %s",&c,&str);
                    l[0]=strtol(str,NULL,16);
                    temp[0]=(unsigned char)l[0];
                    msg->u.formMsg.u.airMsg.u.chanlAttr.startCurFrameNo = temp[0];
               }

               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"TSC"))
               {
                    optional[6] = 6;
                    SET_NM_AIM_SCA_TSC((msg));
                    sscanf(line,"%c %s",&c,&str);
                    l[0]=strtol(str,NULL,16);
                    temp[0]=(unsigned char)l[0];
                    msg->u.formMsg.u.airMsg.u.chanlAttr.tscSeqCode = temp[0];
               }
               ReadCommonElems(line,msg);              
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
    
    if (choice == 7)
    {
        printf("Message Name: SET CHANNEL ATTRIBUTES \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x47 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
   }
    if (choice == 8)
    {
        printf("Message Name: SET CHANNEL ATTRIBUTES ACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x48 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 9)
    {
        printf("Message Name: SET CHANNEL ATTRIBUTES NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x49 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    kcount = k;
    if (kcount >= 9) /* Checks for the no of Info elem */
    {

    }
    else
    {     
        printf("Enter the data correctly\n");
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        
        if (k==8)
        {
            if (choice == 9)
            {
                msg->u.formMsg.u.airMsg.u.chanlAttr.nackCuase  = temp[k];
                printf("Nack     :   0x%02x\n",
                                   msg->u.formMsg.u.airMsg.u.chanlAttr.nackCuase);
            }

        }
                                                                                                                             
    }
    if (optional[1] == 1)
    {
        printf("chanlComb :   0x%02x\n", msg->u.formMsg.u.airMsg.u.chanlAttr.chanlComb ); 
    }
      
    if (optional[2] == 2 )
    {
        printf("HSN       :   0x%02x\n",msg->u.formMsg.u.airMsg.u.chanlAttr.hsn); 

    }
        
    if (optional[3] == 3 )
    {
        printf("MAIO Len fixed taken as 1\n");

        printf("MAIO[0]      :   0x%02x\n", msg->u.formMsg.u.airMsg.u.chanlAttr.maioList.maio[0]); 
    }
    
    if (optional[4] == 4)
    {
        printf("Length    :   0x%02x\n", msg->u.formMsg.u.airMsg.u.chanlAttr.arfcnList.length);
        printf("ARFCN     :   0x%02x\n", msg->u.formMsg.u.airMsg.u.chanlAttr.arfcnList.arfcn[0]);
    }     
 
    if (optional[5] == 5)
    {
        printf("StrtingTim:   0x%02x\n", msg->u.formMsg.u.airMsg.u.chanlAttr.startCurFrameNo); 
    }

    if (optional[6] == 6)
    {
        printf("TSC       :   0x%02x\n",  msg->u.formMsg.u.airMsg.u.chanlAttr.tscSeqCode); 
    }
    return kcount; 
    fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Perform Test,Ack,Nack information elements from the file,
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
*
*/

HandlePerfTest(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    int no_elem = 0;
    no_elem = ReadPerfTest(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding  Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        if (choice == 3)     
        {
            printf("nack    :   0x%02x\n",
                                       msg.u.formMsg.u.testMsg.u.perfTest.nackCuase);
        }
        printf("testNum     :   0x%02x\n",
                               msg.u.formMsg.u.testMsg.testNum);
        printf("autorep     :   0x%02x\n",
                               msg.u.formMsg.u.testMsg.u.perfTest.autoRep);

        if (no_elem == 12 || no_elem == 14)
        {
           printf("testDur  :   0x%02x\n", msg.u.formMsg.u.testMsg.u.perfTest.testDura);
        }
        if (no_elem == 13 || no_elem == 14)
        {
            printf("length  :   0x%02x\n",msg.u.formMsg.u.testMsg.u.perfTest.phyContext.length); 
            printf("testConf:   0x%02x\n",msg.u.formMsg.u.testMsg.u.perfTest.phyContext.testConfig[0]); 
        }
  
    }
    return ITS_SUCCESS;
}
  
/*implementation:internal
*
* PURPOSE:
*       This function reads the Perform Test,Ack,Nack information elements from the 
        file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*/


ITS_INT
ReadPerfTest(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i= 0;
    int j = 0;
    int k=0,kcount;
    int linecount=0;
    unsigned char buffer[100];
    unsigned char temp[100];
    long l[100];
    char c;
    char str[10],str1[10];
    int true = 0;
    int true_opt =0 ;
                                                                                                                             
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    CLEAR_NM_TM_PT_OPTIONAL_BIT_MAP((msg));
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"PERFORM_TEST START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"PERFORM_TEST END\n")!=0)
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
               
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"Test Duration"))
               {
                    true = 1;
                    SET_NM_TM_PT_TEST_DURATION((msg));
                    sscanf(line,"%c %s",&c,&str);
                    l[0]=strtol(str,NULL,16);
                    temp[0]=(unsigned char)l[0];
                    msg->u.formMsg.u.testMsg.u.perfTest.testDura = temp[0];
               }
                
               if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                   && strstr(line,"Physical Configuration"))
               {
                    true_opt = 1;
                    SET_NM_TM_PT_PHYSICAL_CONFIGURATION((msg));
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i=0;i<3;i++)
                    {
                        if (i==0)
                        {
                            l[i]=strtol(str,NULL,16);
                            temp[i]=(unsigned char)l[i];
                            msg->u.formMsg.u.testMsg.u.perfTest.phyContext.length = temp[i];
                        }
                         
                        if (i==1)
                        {
                            l[i]=strtol(str,NULL,16);
                            temp[i]=(unsigned char)l[i];
                            for (j=0;j < msg->u.formMsg.u.testMsg.u.perfTest.phyContext.length;j++)
                            {
                                 msg->u.formMsg.u.testMsg.u.perfTest.phyContext.testConfig[j] = temp[i]; 
                            }
                        }
                    }
               }
               ReadCommonElems(line,msg);              
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
    
    if (choice == 1)
    {
        printf("Message Name: PERFORM TEST \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x51 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
   }
    if (choice == 2)
    {
        printf("Message Name: PERFORM TEST ACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x52 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 3)
    {
        printf("Message Name: PERFORM TEST NACK\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x53 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    kcount = k;
    if (kcount >= 11) /* Checks for the no of Info elem */
    {

    }
    else
    {     
        printf("Enter the data correctly\n");
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        
        if (k==8)
        {
            if (choice == 3)
            {
                msg->u.formMsg.u.testMsg.u.perfTest.nackCuase  = temp[k];
                printf("Nack      :   0x%02x\n",
                               msg->u.formMsg.u.testMsg.u.perfTest.nackCuase);

            }

        }

        if (k==9)
        {
                msg->u.formMsg.u.testMsg.testNum = temp[k];
                printf("testNum   :   0x%02x\n",
                               msg->u.formMsg.u.testMsg.testNum);
                                                                                                                             
        }
          
        if (k==10)
        {
                msg->u.formMsg.u.testMsg.u.perfTest.autoRep = temp[k];
                printf("autorep   :   0x%02x\n",
                               msg->u.formMsg.u.testMsg.u.perfTest.autoRep);
                                                                                                                             
        }
                                                                                                                             
    }
    if (true == 1)
    {
        printf("Test Dur    :   0x%02x\n",  msg->u.formMsg.u.testMsg.u.perfTest.testDura); 
    }
      
    if (true_opt == 1)
    {
        printf("length    :   0x%02x\n", msg->u.formMsg.u.testMsg.u.perfTest.phyContext.length); 
        printf("PhyConf   :   0x%02x\n", msg->u.formMsg.u.testMsg.u.perfTest.phyContext.testConfig[0]); 
    }

    return kcount; 
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Test Report information elements from the file,
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
*
*/

HandleTestRep(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    int no_elem = 0;
    ReadTestRep(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Test Report Failed  ret :: %d\n", ret);
    }
    else
    {   
        printf("**************** ENCODED DATA *************************\n");
        printf("Encoding Test Report  Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    ret = ABIS_NMM_Decode(&msg,sizeof(buffer),buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Test Report  Failed  ret :: %d\n", ret);

    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Test Report Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        printf("testNum   :   0x%02x\n", msg.u.formMsg.u.testMsg.testNum);
        printf("length    :   0x%02x\n",
                              msg.u.formMsg.u.testMsg.u.testRep.length);
        printf("resultInf :   0x%02x\n",
                              msg.u.formMsg.u.testMsg.u.testRep.resultInfo[0]);      
    }
    return ITS_SUCCESS;
}
  
/*implementation:internal
*
* PURPOSE:
*       This function reads the Perform Test,Ack,Nack information elements from the 
        file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*/
ITS_INT
ReadTestRep(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i= 0;
    int j = 0;
    int k=0,kcount;
    int linecount=0;
    unsigned char buffer[100];
    unsigned char temp[100];
    long l[100];
    char c;
    char str[10],str1[10];
    int true = 0;
    int true_opt =0 ;
                                                                                                                             
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"TEST_REPORT START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"TEST_REPORT END\n")!=0)
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
               ReadCommonElems(line,msg);              
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
    printf("Message Name: TEST REPORT\n");
    kcount = k;
    if (kcount == 11) /* Checks for the no of Info elem */
    {

    }
    else
    {     
        printf("Enter the data correctly\n");
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        if (k==8)
        {
                msg->u.formMsg.u.testMsg.testNum = temp[k];
                printf("testNum   :   0x%02x\n",
                               msg->u.formMsg.u.testMsg.testNum);
                                                                                                                             
        }
          
        if (k==9)
        {
                msg->u.formMsg.u.testMsg.u.testRep.length = temp[k];
                printf("length    :   0x%02x\n",
                               msg->u.formMsg.u.testMsg.u.testRep.length);
        }
                                                                                                                             
        if (k==10)
        {
            printf("ResultInfo:   0x%02x\n", temp[k]);
            for (i=0;i<msg->u.formMsg.u.testMsg.u.testRep.length;i++)
            {
                msg->u.formMsg.u.testMsg.u.testRep.resultInfo[i] = temp[k];
            }
                
        }
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Send/Stop Test Report,Ack,Nack information elements 
*       from the file,encoding and then decoding
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
*
*/

HandleSendTestRep(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    int no_elem = 0;
    ReadSendTestRep(&msg,fp,choice);
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
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
    ret = ABIS_NMM_Decode(&msg, len, buffer);

    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Failed  ret :: %d\n", ret);

    }
    else
    {
        printf("**************** DECODED DATA *************************\n");
        printf("Decoding Success  ret :: %d\n", ret);
        printDecCommonElems(msg);
        printf("testNum   :   0x%02x\n", msg.u.formMsg.u.testMsg.testNum);
        if (choice == 7 || choice == 10)
        {
            printf("Nack      :   0x%02x\n", msg.u.formMsg.u.testMsg.u.sendRep.nackCuase);
        }
                                                    
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       This function reads the Send/Stop Test Report,Ack,Nack information 
*        elements from the file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
*
*/
  
ITS_INT
ReadSendTestRep(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[100],*bufspace[100];
    int i= 0;
    int j = 0;
    int k=0,kcount;
    int linecount=0;
    unsigned char buffer[100];
    unsigned char temp[100];
    long l[100];
    char c;
    char str[10],str1[10];
    int true = 0;
    int true_opt =0 ;
                                                                                                                             
    printf("                        \n");

     
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"SENDSTOP_TEST START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"SENDSTOP_TEST END\n")!=0)
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
               ReadCommonElems(line,msg);              
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
    if (choice == 5)
    {
        printf("Message Name: SEND TEST REPORT \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x55 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    
    if (choice == 6)
    {
        printf("Message Name: SEND TEST REPORT ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x56 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }

    if (choice == 7)
    {
        printf("Message Name: SEND TEST REPORT NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x57 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
     
    if (choice == 8)
    {
        printf("Message Name: SEND TEST \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x58 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
     
    if (choice == 9)
    {
        printf("Message Name: STOP TEST ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x59 )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
     
    if (choice == 10)
    {
        printf("Message Name: STOP TEST NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x5a )
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }

    kcount = k;
    if (kcount == 10) /* Checks for the no of Info elem */
    {

    }
    else
    {     
        printf("Enter the data correctly\n");
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE ...\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printComFileElems(msg);
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
           
        if (k==8)
        {
            if(choice == 7 || choice == 10)
            {       
                msg->u.formMsg.u.testMsg.u.sendRep.nackCuase = temp[k];
                printf("testNum   :   0x%02x\n",
                               msg->u.formMsg.u.testMsg.u.sendRep.nackCuase);
            }
                                                                                                                             
        }

        if (k==9)
        {
                msg->u.formMsg.u.testMsg.testNum = temp[k];
                printf("testNum   :   0x%02x\n",
                               msg->u.formMsg.u.testMsg.testNum);
                                                                                                                             
        }
    }

    return kcount; 
    fclose(fp);
}



ITS_INT (*testNetworkMsg_AIMM[20])(int) = {
					      NULL,
					      HandleEstablishTEI,
					      HandleEstablishTEI,
					      HandleEstablishTEI,
	                                      HandleConTerSig,
	                                      HandleConTerSig,
	                                      HandleConTerSig,
	                                      HandleConTerSig,
	                                      HandleConTerSig,
	                                      HandleConTerSig,
	                                      HandleConTerTrff,
	                                      HandleConTerTrff,
	                                      HandleConTerTrff,
	                                      HandleConTerTrff,
	                                      HandleConTerTrff,
	                                      HandleConTerTrff
                                          };	

ITS_INT (*testNetworkMsg_TMM[10])(int) = {
					      NULL,
					      HandleMulDropLink,
					      HandleMulDropLink,
					      HandleMulDropLink,
					      HandleMulDropLink,
					      HandleMulDropLink,
					      HandleMulDropLink
                                          };


ITS_INT (*testNetworkMsg_AIM[15])(int) = {
					      NULL,
					      HandleSetBtsAttr,
					      HandleSetBtsAttr,
					      HandleSetBtsAttr,
					      HandleSetRadioCarAttr,
					      HandleSetRadioCarAttr,
					      HandleSetRadioCarAttr,
                                              HandleSetChanAttr,
                                              HandleSetChanAttr,
                                              HandleSetChanAttr
                                         };


ITS_INT (*testNetworkMsg_TESTMM[15])(int) = {
					      NULL,
					      HandlePerfTest,
					      HandlePerfTest,
					      HandlePerfTest,
                                              HandleTestRep,
 					      HandleSendTestRep,
 					      HandleSendTestRep,
 					      HandleSendTestRep,
 					      HandleSendTestRep,
 					      HandleSendTestRep,
 					      HandleSendTestRep
                                           };

                                              
ITS_INT (*testNetworkMsg_SWDM[20])(int) = {
                                              NULL,
                                              HandleLoadDataInit,
                                              HandleLoadDataInit,
                                              HandleLoadDataInit,
                                              HandleLoadDataSeg,
                                              HandleLoadDataSeg,
                                              HandleLoadDataAbort,
                                              HandleLoadDataEnd,
                                              HandleLoadDataEnd,
                                              HandleLoadDataEnd,
                                              HandleSWActReq,
                                              HandleSWActReq,
                                              HandleSWActReq,
                                              HandleActSW,
                                              HandleActSW,
                                              HandleActSW,
                                              HandleSWActRep 
                                          };


