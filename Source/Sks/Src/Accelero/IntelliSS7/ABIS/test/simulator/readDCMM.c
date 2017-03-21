
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
 *  ID: $Id: readDCMM.c,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
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

FILE *fp;
extern char filename[20];

/*implementation:internal
*
* PURPOSE:
*       Handles reading the data request information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
HandleChanActv(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    FILE *fptr;
    char line[1024];
    /* Read from the file */
    ReadChanActv(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
     
    msg.genElemnts.msgDesc.msgGruop = 0x78; 
    msg.genElemnts.msgDesc.trasparent= 0x00;
    msg.genElemnts.msgType = 0x21;
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Channel Activation Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("****************** ENCODED DATA ***************************\n");
        printf("Encoding Channel Activation Success  ret :: %d\n\n", ret);
        printEncComDcmm(buffer,len);                                                                                             }
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Channel Activation Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("****************** DECODED DATA **************************\n");
        printf("Decoding Channel Activation Success  ret :: %d\n", ret);
        //printDecChanActv(msg,ret_elem);
        /* display buffer */
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        //printf("msgDesc      :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop);
        //printf("msgDesc(T)   :   0x%02x\n", msg.genElemnts.msgDesc.trasparent);
       // printf("msgType      :   0x%02x\n", msg.genElemnts.msgType);
        printf("msgDesc      :   0x78\n");
        printf("msgDesc(T)   :   0x00\n");
        printf("msgType      :   0x21\n");
        printf("chanBits     :   0x%02x\n",
                             msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum  :   0x%02x\n",
                             msg.u.dcmMsg.dcmGenElements.chanlNum.timeSlotNum);
        printf("ActivationTyp:   0x%02x\n",
                                             msg.u.dcmMsg.u.chanActiv.actType);
        printf("procedure    :   0x%02x\n",
                                           msg.u.dcmMsg.u.chanActiv.procedure);
         
        printf("length :   0x%02x\n",
                                       msg.u.dcmMsg.u.chanActiv.chnlMode.length);
        printf("chnlmodedtxu :   0x%02x\n",
                                       msg.u.dcmMsg.u.chanActiv.chnlMode.dtxu);
        printf("chnlmodedtxd :   0x%02x\n",
                                       msg.u.dcmMsg.u.chanActiv.chnlMode.dtxd);
        printf("indicator    :   0x%02x\n",
                                  msg.u.dcmMsg.u.chanActiv.chnlMode.indicator);
        printf("rateandtype  :   0x%02x\n",
                                msg.u.dcmMsg.u.chanActiv.chnlMode.rateAndType);
	printf("coding algo  :   0x%02x\n",
                                  msg.u.dcmMsg.u.chanActiv.chnlMode.codingAlg);
        if (msg.u.dcmMsg.u.chanActiv.chnlMode.indicator == TM_CM_DATA)
        {
            printf("rate          : %02x\n", msg.u.dcmMsg.u.chanActiv.chnlMode.rate);
            printf("service       : %02x\n", msg.u.dcmMsg.u.chanActiv.chnlMode.service);
        }
 
        fptr=fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"CHANACT START\n")==0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),"CHANACT END\n")!=0)
                {   
                    /* Channel identifier */
                    if (line[0]=='O' && line[1]=='\t' && line[2]=='0' 
                       && strstr(line,"opt1")) 
                    {
                        printf("CI Length   :   0x%02x\n",
                                        msg.u.dcmMsg.u.chanActiv.chnlId.length);
                        printf("desclen     :   0x%02x\n",
                                       msg.u.dcmMsg.u.chanActiv.chnlId.descLen);
                        printf("chnlDesc    :   0x%02x\n",
                                  msg.u.dcmMsg.u.chanActiv.chnlId.chanlDesc[0]);
                        printf("alloclen    :   0x%02x\n",
                                      msg.u.dcmMsg.u.chanActiv.chnlId.allocLen);
                        printf("mobAlloc    :   0x%02x\n",
                                   msg.u.dcmMsg.u.chanActiv.chnlId.mobAlloc[0]);
                    }

                    /* Encrytion Command */
                    if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                        strstr(line,"opt2"))
                    {
                        printf("EI length   :   0x%02x\n", 
                                    msg.u.dcmMsg.u.chanActiv.encryption.length);
                        printf("algorithmId :   0x%02x\n", 
                               msg.u.dcmMsg.u.chanActiv.encryption.algorithmId);
                        printf("key         :   0x%02x\n", 
                                    msg.u.dcmMsg.u.chanActiv.encryption.key[0]);
                     }   

                    /* handover reference */
                    if (line[0]=='C' && line[1]=='\t' && line[2]=='0' 
                       && strstr(line,"opt3")) 
                    {
                        printf("HandRef     :   0x%02x\n", 
                                              msg.u.dcmMsg.u.chanActiv.handRef);   
                    }
                    /* BS Power */
                    if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                       strstr(line,"opt4"))
                    {
                        printf(" PowLevel   : 0x%02x\n", 
                                   msg.u.dcmMsg.u.chanActiv.bsPower.powerLevel);
                        printf("FPC         : 0x%02x\n", 
                                          msg.u.dcmMsg.u.chanActiv.bsPower.FPC);
                    }
                    /* MS Power */
                    if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                       strstr(line,"opt5"))
                    {
                        printf("MsPowLevel  : 0x%02x\n", 
                                   msg.u.dcmMsg.u.chanActiv.msPower.powerLevel);
                        printf("FPC         : 0x%02x\n", 
                                          msg.u.dcmMsg.u.chanActiv.msPower.FPC);
                    }

                    /* Conditional Parameter-Timing Advance */
                    if (line[0]=='C' && line[1]=='\t' && line[2]=='0' && 
                       strstr(line,"opt6"))
                    {
                         printf("timingAdv   : 0x%02x\n", 
                                            msg.u.dcmMsg.u.chanActiv.timingAdv);
                    }

                    /* BS Power Parameters */
                   if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                      strstr(line,"opt7"))
                   {
                        printf("BsParamsLen : 0x%02x\n", 
                                      msg.u.dcmMsg.u.chanActiv.bsParams.length);
                        printf("powerControl: 0x%02x\n", 
                            msg.u.dcmMsg.u.chanActiv.bsParams.powerControl[0]); 
                   } 

                   /* MS Power Parameters */
                   if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                      strstr(line,"opt8"))
                   {
                       printf("MS Params   : 0x%02x\n",
                                      msg.u.dcmMsg.u.chanActiv.msParams.length);
                       printf("PowerControl: 0x%02x\n",
                             msg.u.dcmMsg.u.chanActiv.msParams.powerControl[0]);
                   }

                   /* Physical Context */
                   if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                      strstr(line,"opt9"))
                   {
                       printf("Length      : 0x%02x\n",
                                    msg.u.dcmMsg.u.chanActiv.phyContext.length);
                       printf("Content     : 0x%02x\n",
                                msg.u.dcmMsg.u.chanActiv.phyContext.content[0]);
                   }

                   /* SACCH INFO */
                   if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                      strstr(line,"opt-10"))
                   {
                       printf("sacch length: 0x%02x\n",
                                     msg.u.dcmMsg.u.chanActiv.sacchInfo.length);
                       printf("numOfMsgs   : 0x%02x\n",
                                  msg.u.dcmMsg.u.chanActiv.sacchInfo.numOfMsgs);
                       msg.u.dcmMsg.u.chanActiv.sacchInfo.msgInfo =
                       (TM_SACCH_MSG_INFO  *)
                       calloc(msg.u.dcmMsg.u.chanActiv.sacchInfo.msgInfo, 
                                                  sizeof(TM_SACCH_MSG_INFO));
                                                                                                                             
                       /*printf("Type of Msg : 0x%02x\n",
                       msg.u.dcmMsg.u.chanActiv.sacchInfo.msgInfo[0].typeOfMsg);
                       printf("msgInf Leng : 0x%02x\n",
                          msg.u.dcmMsg.u.chanActiv.sacchInfo.msgInfo[0].length);
                       printf("msgInf msg  : 0x%02x\n",
                          msg.u.dcmMsg.u.chanActiv.sacchInfo.msgInfo[0].msg[0]);*/
                   }

                   /* UIC Length */
                   if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                       strstr(line,"opt-11"))
                   {
                       printf("uicLen      : 0x%02x\n",
                                           msg.u.dcmMsg.u.chanActiv.uicLen);
                       printf("uicInfo     : 0x%02x\n",
                                           msg.u.dcmMsg.u.chanActiv.uicInfo);
                   }
                   /* Main Channel Reference */
                   if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                       strstr(line,"opt-12"))
                   {
                       printf("MainChnRef  : 0x%02x\n",
                                      msg.u.dcmMsg.u.chanActiv.mainChnlRefTn);
                   }                                                          
                     
                   /* Multirate Configuration */
                   if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                      strstr(line,"opt-13"))
                   {
                       printf("mrConf lengt: 0x%02x\n",
                                    msg.u.dcmMsg.u.chanActiv.mrConfig.length);
                       printf("Content     : 0x%02x\n",
                                msg.u.dcmMsg.u.chanActiv.mrConfig.content[0]);
                   }

                  /* Multirate Control */
                  if (line[0]=='O' && line[1]=='\t' && line[2]=='0'
                   && strstr(line,"opt-14"))
                  {
                      printf("TFO         : 0x%02x\n", 
                                     msg.u.dcmMsg.u.chanActiv.mrControl.TFO);
                      printf("PRE         : 0x%02x\n", 
                                      msg.u.dcmMsg.u.chanActiv.mrControl.PRE);
                      printf("RAE         : 0x%02x\n",                               
                                      msg.u.dcmMsg.u.chanActiv.mrControl.RAE);
                  }                                                                    

                  /* Supported Codec types */
                  if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                                                 strstr(line,"opt-15"))
                  {
                       printf("CodecTypLen : 0x%02x\n", 
                                   msg.u.dcmMsg.u.chanActiv.codecTypes.length);
                       printf("sysId       : 0x%02x\n", 
                                    msg.u.dcmMsg.u.chanActiv.codecTypes.sysId);
                       printf("codecList   : 0x%02x\n", 
                                msg.u.dcmMsg.u.chanActiv.codecTypes.codecList);
                       if (msg.u.dcmMsg.u.chanActiv.codecTypes.codecList > 0x07)
                       {
                       printf("MACS        : 0x%02x\n", 
                                  msg.u.dcmMsg.u.chanActiv.codecTypes.MACS[0]);
                       printf("TFO_VER     : 0x%02x\n", 
                              msg.u.dcmMsg.u.chanActiv.codecTypes.TFO_VER[0]);
                       printf("MACS[1]     : 0x%02x\n", 
                                  msg.u.dcmMsg.u.chanActiv.codecTypes.MACS[1]);
                       printf("TFO_VER[1]  : 0x%02x\n", 
                               msg.u.dcmMsg.u.chanActiv.codecTypes.TFO_VER[1]);
                       printf("SCS[0]      : 0x%02x\n", 
                                      msg.u.dcmMsg.u.chanActiv.codecTypes.SCS[0]);
                       printf("SCS[1]      : 0x%02x\n", 
                                      msg.u.dcmMsg.u.chanActiv.codecTypes.SCS[1]);
                       printf("prefCodecTyp: 0x%02x\n", 
                            msg.u.dcmMsg.u.chanActiv.codecTypes.prefCodecType);
                     }
 
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
*       Reading the Channel Activation information elements from the file and 
        assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
                                                                                                                             
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
ITS_INT
ReadChanActv(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char c;
    char line[1024];
    char str[10],str1[10],str2[10],str3[10],str4[10];
    char str5[10],str6[10],str7[10],str8[10],str9[10];
    int i=0,icount,k=0,kcount;
    int count;
    int j;
    int tot_elem = 0;
    int mand_elem = 15;
    int optional[20] , conditional[10];
    int linecount = 0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    long l1;
    unsigned char temp1;
    int l3count;
    printf("                        \n");
    printf("Message Name: CHANNEL ACTIVATION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,0,NULL);
     
    CLEAR_TM_DCM_CA_OPTIONAL_BIT_MAP(msg); 
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"CHANACT START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"CHANACT END\n")!=0)
            {
                for(i=0;i<300;i++)
                {
                    if(line[i]=='\n')
                    {
                        linecount++;
                        
                    }
                }
		if(line[0]=='M' || line[0]=='O')
                {
		    if(line[1]=='\t')
                    {
			/* Do Nothing */
 		    }
		    else
		    {
		        printf("Enter tab after the param at %d\n",linecount);
			exit(1);
		    }
                }
                if (line[0] == 'M' && strstr(line,"Message Type"))
                {
                    sscanf(line,"%c %s %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
                    msg->genElemnts.msgType =temp1;
                }        
                
                if (line[0] == 'M' && strstr(line,"Message discriminator"))
                {
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    //printf("%s\n",str);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
 	                    temp[i] = (unsigned char)l[i];
                            msg->genElemnts.msgDesc.msgGruop=temp[i];
                            printf("msggrp is %02x\n", msg->genElemnts.msgDesc.msgGruop); 
                        }
                                                                                                                             
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->genElemnts.msgDesc.trasparent=temp[i];
                        }
                                                                                                                             
                    }
 
                }
                if (line[0] == 'M' && strstr(line,"Channel Number"))
                {
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = 
                                                                    temp[i];

                        }
                                                                                                                             
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum =
                                                                     temp[i];
                        }
                                                                                                                             
                    }
                                                                                                                             
                }
                
                if (line[0] == 'M' && strstr(line,"Activation Type"))
                {
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
			    msg->u.dcmMsg.u.chanActiv.actType=temp[i];  
                        }
                                                                                                                             
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.procedure=temp[i];

                        }                                                                                                         
                    }
                                                                                                                             
                }
                if (line[0] == 'M' && strstr(line,"Channel Mode"))
                {
                    sscanf(line,"%c %s %s %s %s %s %s %s %s",&c,&str,&str1,
                           &str2,&str3,&str4,&str5,&str6,&str7);
                                                                                                                             
                    for(i=0;i<10;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.chnlMode.length = 
                                                                temp[i]; 
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];			   	
                             msg->u.dcmMsg.u.chanActiv.chnlMode.dtxd = temp[i]; 
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.chnlMode.dtxu = temp[i];  
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.chnlMode.indicator = 
                                                                    temp[i];
                        }
                        if (i == 4)
                        {
                            l[i] = strtol(str4,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.chnlMode.rateAndType = 
                                                              temp[i];       
                        }
                        if (i == 5)
                        {
                            l[i] = strtol(str5,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.chnlMode.codingAlg = 
                                                                      temp[i];
                        }
                       if (msg->u.dcmMsg.u.chanActiv.chnlMode.indicator == 0x02)
                       { 
                                                                                                                                                      
                        if (i == 6)
                        {
                            l[i] = strtol(str6,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.chnlMode.rate = 
                                                                      temp[i];
                        }
                         
                        if (i == 7)
                        {
                            l[i] = strtol(str7,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.chnlMode.service = 
                                                                      temp[i];
                        }
                     }

                    } 
                }

               /* Channel identifier */

                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt1")) 
                {
                    SET_TM_DCM_CA_CHANNEL_ID(msg);
                    sscanf(line,"%c %s %s %s %s %s",&c,&str,&str1,
                                                      &str2,&str3,&str4); 
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        { 
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
		            msg->u.dcmMsg.u.chanActiv.chnlId.length = temp[i];
                        }
                        if (i == 1)
                        { 
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.chnlId.descLen = temp[i];
                        }
                        if (i == 2)
                        {  
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for(k = 0; 
                               k < msg->u.dcmMsg.u.chanActiv.chnlId.descLen;k++)
            		    {

                                msg->u.dcmMsg.u.chanActiv.chnlId.chanlDesc[k] = 
                                                                       temp[i];
                            }
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.chnlId.allocLen = temp[i];
                        }
                        if (i == 4)
                        { 
                            l[i] = strtol(str4,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for(k = 0 ; 
                            k < msg->u.dcmMsg.u.chanActiv.chnlId.allocLen ;
                            k++)
                            {
                                msg->u.dcmMsg.u.chanActiv.chnlId.mobAlloc[k] =
                                                                      temp[i];
                            }
	                }
                    }
                    optional[1] = 1;      
                }
               /* Encryption Command */ 

                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' &&
                                                        strstr(line,"opt2"))
                {
                    SET_TM_DCM_CA_ENCRYPT_INFO(msg);
                    optional[2] = 2;
                    sscanf(line,"%c %s %s %s",&c,&str,&str1,&str2);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        { 
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.encryption.length = 
                                                                  temp[i];
                        }
                        if (i == 1)
                        { 
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.encryption.algorithmId =
                                                                     temp[i];
                        }
                        if (i == 2)
                        { 
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
               	            for( k=0; 
                            k< msg -> u.dcmMsg.u.chanActiv.encryption.length;
                            k++)
                            {
                               msg->u.dcmMsg.u.chanActiv.encryption.key[k] = 
                                                                     temp[i];
                            }
                        }
		    }
                }
                /**** Conditional Parameter-Handover refrence ***/
                if (line[0]=='C' && line[1]=='\t' && line[2]=='0' &&
                                                 strstr(line,"opt3"))

                {
                    conditional[1] = 1;
                    sscanf(line,"%c %s",&c,&str);
                    if (  msg->u.dcmMsg.u.chanActiv.actType == 0x02 || 
                         msg->u.dcmMsg.u.chanActiv.actType == 0x03)
                    {
                        l1 = strtol(str,NULL,16);
                        temp1 = (unsigned char)l1;
                        msg->u.dcmMsg.u.chanActiv.handRef = temp1;
                    }
                    else
                    {
                   
                    } 
		}
                /**** BS Power  ****/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt4"))
                {
                    optional[4] = 4;
                    SET_TM_DCM_CA_BS_POWER(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0; i<6; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.bsPower.FPC = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];   
                            msg->u.dcmMsg.u.chanActiv.bsPower.powerLevel = 
                                                                  temp[i];
                        }
                    }
		}
                /**** MS power  ****/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt5"))
                {

                    optional[5] = 5; 
                    SET_TM_DCM_CA_MS_POWER(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.msPower.FPC = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.msPower.powerLevel = 
                                                                  temp[i];
                        }
                    }
		}
                /*****Conditional Parameter-Timing Advance ******/
                if (line[0]=='C' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt6"))
                {
                    conditional[2] = 2; 
                    sscanf(line,"%c %s",&c,&str);
                    if ( msg->u.dcmMsg.u.chanActiv.actType == 0x00 || 
                         msg->u.dcmMsg.u.chanActiv.actType == 0x01)
                    {
                        l1 = strtol(str,NULL,16);
                        temp1 = (unsigned char)l1;
                        msg->u.dcmMsg.u.chanActiv.handRef = temp1;
                    }
                    else
                    {
                    }
		}
                /*****BS Power Parameters ****/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt7"))
                {

		    optional[7] = 7;	                   
                    SET_TM_DCM_CA_BS_POWER_PARAM(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.bsParams.length = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for (k=0; 
                            k<msg->u.dcmMsg.u.chanActiv.bsParams.length;k++)
                            { 
                                msg->u.dcmMsg.u.chanActiv.bsParams.\
                                        powerControl[k] = temp[i];
                            }
                        }
                    }
		}
                /***** MS Power Parameters ****/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt8"))
                {
		    optional[8] = 8;
                    SET_TM_DCM_CA_MS_POWER_PARAM(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.msParams.length = temp[i];
                        }
                       if (i == 1)
                       {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for (k=0; 
                            k<msg->u.dcmMsg.u.chanActiv.bsParams.length;k++)
                            {
                                msg->u.dcmMsg.u.chanActiv.msParams.\
                                             powerControl[k] = temp[i];
                            }
                        }
                    }
                }
                /******* Physical Context *******/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt9"))
                {
                    optional[9]=9;   
                    SET_TM_DCM_CA_PHYSICAL_CONTEXT(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.phyContext.length = 
                                                                 temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for (k=0; 
                            k<msg->u.dcmMsg.u.chanActiv.phyContext.length;k++)
                            {
                                msg->u.dcmMsg.u.chanActiv.phyContext.\
                                           content[k] = temp[i];
                            }
                        }
                    }                   
		}
                /**** SACCH INFO ******/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt-10"))
                {
                    optional[10] = 10;
                    SET_TM_DCM_CA_SAACH_INFO(msg);
                    sscanf(line,"%c %s %s %s %s %s %s",&c,&str,&str1,
                                                      &str2,&str3,&str4);
                    for(i=0;i<6;i++)
                    {
                        if (i==0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.sacchInfo.length = 
                                                                 temp[i];
                        }
                        if (i==1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.sacchInfo.numOfMsgs = 
                                                                    temp[i];
                        }
                        if (i==2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                           //free(msg);
                           /*msg->u.dcmMsg.u.chanActiv.sacchInfo.msgInfo =
                           (TM_SACCH_MSG_INFO  *)
                           calloc(msg->u.dcmMsg.u.chanActiv.sacchInfo.msgInfo, sizeof(TM_SACCH_MSG_INFO)); */
	                    for ( k = 0; 
                            k < msg->u.dcmMsg.u.chanActiv.sacchInfo.numOfMsgs ; 
                            k++)
                            {
                                msg->u.dcmMsg.u.chanActiv.sacchInfo.msgInfo[k].\
                                                         typeOfMsg = temp[i];
                            }
                            free(msg);
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for ( k = 0; 
                            k < msg->u.dcmMsg.u.chanActiv.sacchInfo.numOfMsgs ; 
                            k++)
            	            {
                               msg->u.dcmMsg.u.chanActiv.sacchInfo.msgInfo[k].\
                                                             length= temp[i];
                            }
                        }
                        if (i==4)
                        {
                            l[i] = strtol(str4,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for (k = 0; 
                            k < msg->u.dcmMsg.u.chanActiv.sacchInfo.numOfMsgs ;
                            k++)
                            {
                                for(j=0; 
                                j < msg->u.dcmMsg.u.chanActiv.sacchInfo.\
                                msgInfo[k].length; j++)
                                {
                                    msg->u.dcmMsg.u.chanActiv.sacchInfo.\
                                              msgInfo[k].msg[j]=temp[i];
                                }
                            }
			}                                                                                                                            
       		    }	            
		}
                /****UIC Length*****/

                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                                                 strstr(line,"opt-11"))
                {
                    optional[11] = 11;
                    SET_TM_DCM_CA_UIC(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.uicLen = temp[i];
                        }     
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.uicInfo = temp[i];    
                        }
                    }
                }
                /****Main Channel Reference ****/ 
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt-12"))
                {
		    optional[12] =12;
		    SET_TM_DCM_CA_MAIN_CHANNEL_REF(msg);
                    sscanf(line,"%c %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
		    msg->u.dcmMsg.u.chanActiv.mainChnlRefTn = temp1; 
                }

                /****Multirate Configuration ****/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt-13"))
                {
                    optional[13] = 13;
                    SET_TM_DCM_CA_MULTI_RATE_CONFIG(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.mrConfig.length = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for (k=0; 
                             k<msg->u.dcmMsg.u.chanActiv.mrConfig.length;k++)
                            {
		                msg->u.dcmMsg.u.chanActiv.mrConfig.content[k] = 
                                                                       temp[i];
                            }
                       }
                    }
                }

                /****Multirate Control *****/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' 
                    && strstr(line,"opt-14"))
                {

                    optional[14] = 14;
                    SET_TM_DCM_CA_MULTI_RATE_CONTROL(msg);
                    sscanf(line,"%c %s %s %s",&c,&str,&str1,&str2);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.mrControl.TFO = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.mrControl.PRE =temp[i];
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.mrControl.RAE =temp[i];
                        }
                    }
		}
                /**** Supported Codec types ****/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt-15"))
                {
                    optional[15] = 15;
                    SET_TM_DCM_CA_SUPPORTED_CODEC_TYPES(msg);
                    sscanf(line,"%c %s %s %s %s %s %s %s %s %s %s",&c,
                            &str,&str1,&str2,&str3,&str4,&str5,&str6,&str7,&str8,&str9);
                    for(i=0;i<10;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
               		    msg->u.dcmMsg.u.chanActiv.codecTypes.length = 
                                                                       temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.codecTypes.sysId =
                                                                     temp[i];
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.codecTypes.codecList = 
                                                                        temp[i];
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
              		    msg->u.dcmMsg.u.chanActiv.codecTypes.MACS[0] = 
                                                                       temp[i];
                        }
                        if (i == 4)
                        {
                            l[i] = strtol(str4,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.codecTypes.TFO_VER[0] = 
                                                                       temp[i];
                        }
                        if (i == 5)
                        {
                            l[i] = strtol(str5,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            if ( msg->u.dcmMsg.u.chanActiv.codecTypes.codecList == 0x18)
                            { 
                              msg->u.dcmMsg.u.chanActiv.codecTypes.MACS[1] = 
                                                                    temp[i];
                            } 
                        }
                        if (i == 6)
                        {
                            l[i] = strtol(str6,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            if ( msg->u.dcmMsg.u.chanActiv.codecTypes.codecList == 0x18)
                            { 
                              msg->u.dcmMsg.u.chanActiv.codecTypes.TFO_VER[1] = 
                                                                    temp[i];
                            } 
                        }
                        if (i == 7)
                        {
                            l[i] = strtol(str7,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.codecTypes.SCS[0] = 
                                                                    temp[i];
                        }
                         
                        if (i == 8)
                        {   
                            l[i] = strtol(str7,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            if ( msg->u.dcmMsg.u.chanActiv.codecTypes.codecList == 0x18)
                            { 
                             msg->u.dcmMsg.u.chanActiv.codecTypes.SCS[1] = 
                                                                    temp[i];
                            }
                        }
                        if (i == 9)
                        {
                            l[i] = strtol(str8,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.chanActiv.codecTypes.prefCodecType =
                                                                        temp[i];
                        }
                    }
                }
		printf("%s",line);
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
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: CHANNEL ACTIVATION\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
     
   // printf("msggrp is %02x\n", msg->genElemnts.msgDesc.msgGruop); 
   // printf("msgDesc         :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
   // printf("msgdesc(T)      :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
    printf("msgDesc         :   0x78\n");
    printf("msgDesc(T)      :   0x00\n");
    printf("msgType         :   0x21\n");
    printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
    printf("chanBits        :   0x%02x\n",
                            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
    printf("timeSlotNum     :   0x%02x\n",
                          msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
    printf("ActivationTyp   :   0x%02x\n",msg->u.dcmMsg.u.chanActiv.actType);
    printf("procedure       :   0x%02x\n",msg->u.dcmMsg.u.chanActiv.procedure);
    printf("chnlmodelen     :   0x%02x\n",
                                    msg->u.dcmMsg.u.chanActiv.chnlMode.length);
    printf("chnlmodedtxd    :   0x%02x\n",
                                     msg->u.dcmMsg.u.chanActiv.chnlMode.dtxd);
    printf("chnl dtxu       :   0x%02x\n",
                                     msg->u.dcmMsg.u.chanActiv.chnlMode.dtxu); 
    printf("indicator       :   0x%02x\n",
                                msg->u.dcmMsg.u.chanActiv.chnlMode.indicator);
    printf("rateandtype     :   0x%02x\n",
                                msg->u.dcmMsg.u.chanActiv.chnlMode.rateAndType);
    printf("coding algo     :   0x%02x\n",
                                  msg->u.dcmMsg.u.chanActiv.chnlMode.codingAlg);
 
    if ( msg->u.dcmMsg.u.chanActiv.chnlMode.indicator == TM_CM_DATA)
    {
        printf("rate          : %02x\n", msg->u.dcmMsg.u.chanActiv.chnlMode.rate);
        printf("service       : %02x\n", msg->u.dcmMsg.u.chanActiv.chnlMode.service);
    }
 
    if (optional[1] == 1)
    {
        printf("length      :  0x%02x\n",
                                    msg->u.dcmMsg.u.chanActiv.chnlId.length);
        printf("descLen     :  0x%02x\n",
                                    msg->u.dcmMsg.u.chanActiv.chnlId.descLen);
        printf("ChanlDesc   :  0x%02x\n",
                                msg->u.dcmMsg.u.chanActiv.chnlId.chanlDesc[0]);
        printf("allocLen    :  0x%02x\n",
                                   msg->u.dcmMsg.u.chanActiv.chnlId.allocLen);
        printf("mobAlloc    :  0x%02x\n",
                                 msg->u.dcmMsg.u.chanActiv.chnlId.mobAlloc[0]);
    }     
    if (optional[2] == 2)
    {
        printf("Enc Len     :  0x%02x\n",
                                 msg->u.dcmMsg.u.chanActiv.encryption.length);
        printf("service     :  0x%02x\n",
                             msg->u.dcmMsg.u.chanActiv.encryption.algorithmId);
        printf("key         :  0x%02x\n",
                               msg->u.dcmMsg.u.chanActiv.encryption.key[0]);
    }
    
    if (optional[3] == 3)
    {
         printf("handref    : 0x%02x\n",msg->u.dcmMsg.u.chanActiv.handRef);
    }  
    
    if (optional[4] == 4)
    {
        printf("FPC         : 0x%02x\n",msg->u.dcmMsg.u.chanActiv.bsPower.FPC);
        printf("service     : 0x%02x\n",
                                 msg->u.dcmMsg.u.chanActiv.bsPower.powerLevel);
    }    
    if (optional[5] == 5)
    {
        printf("FPC         : 0x%02x\n",msg->u.dcmMsg.u.chanActiv.msPower.FPC);
        printf("service     : 0x%02x\n",
                                 msg->u.dcmMsg.u.chanActiv.msPower.powerLevel);
    }         
    if (optional[6] == 6)
    {
       printf("timingAdvance : 0x%02x\n",msg->u.dcmMsg.u.chanActiv.timingAdv);
    }
    if (optional[7] == 7)
    {
        printf("bsParamslen  : 0x%02x\n",
                                    msg->u.dcmMsg.u.chanActiv.bsParams.length);
        printf("powerControl : 0x%02x\n",
                           msg->u.dcmMsg.u.chanActiv.bsParams.powerControl[0]);
    }
    if (optional[8] == 8)
    {
        printf("msParamslen  : 0x%02x\n",
                                    msg->u.dcmMsg.u.chanActiv.msParams.length);
        printf("powerControl : 0x%02x\n",
                          msg->u.dcmMsg.u.chanActiv.msParams.powerControl[0]);
    }
      
    if (optional[9] == 9)
    {
        printf("Phylength    : 0x%02x\n",
                                  msg->u.dcmMsg.u.chanActiv.phyContext.length); 
        printf("Phy content  : 0x%02x\n", 
                             msg->u.dcmMsg.u.chanActiv.phyContext.content[0]);      
    }   
    if (optional[10] == 10)
    {
        printf("sacchInflen : 0x%02x\n",
                                    msg->u.dcmMsg.u.chanActiv.sacchInfo.length);
        printf("numOfMsgs   : 0x%02x\n",
                                 msg->u.dcmMsg.u.chanActiv.sacchInfo.numOfMsgs);
        printf("msg typOfMsg: 0x%02x\n",
                      msg->u.dcmMsg.u.chanActiv.sacchInfo.msgInfo[0].typeOfMsg);
        printf("msg length  : 0x%02x\n",
                        msg->u.dcmMsg.u.chanActiv.sacchInfo.msgInfo[0].length);
        printf("msgI ength  : 0x%02x\n",
                        msg->u.dcmMsg.u.chanActiv.sacchInfo.msgInfo[0].msg[0]);
    }
    if (optional[11] == 11)
    {
         printf("UIC leng   :   0x%02x\n",msg->u.dcmMsg.u.chanActiv.uicLen);
         printf("UIC Info   :   0x%02x\n",msg->u.dcmMsg.u.chanActiv.uicInfo);
    }
    if (optional[12] == 12)
    {
         printf("mainCnlRe  : 0x%02x\n",
                                     msg->u.dcmMsg.u.chanActiv.mainChnlRefTn);
    }                             
    if (optional[13] == 13)
    {
        printf("mrconfleng  :   0x%02x\n",
                                     msg->u.dcmMsg.u.chanActiv.mrConfig.length);
        printf("mrconfleng  :   0x%02x\n",
                                 msg->u.dcmMsg.u.chanActiv.mrConfig.content[0]);
    }
    if (optional[14] == 14)
    {
        printf("mrCtrl TFO : 0x%02x\n",msg->u.dcmMsg.u.chanActiv.mrControl.TFO);
        printf("mrCtrl PRE : 0x%02x\n",msg->u.dcmMsg.u.chanActiv.mrControl.PRE);
        printf("mrCtrl RAE : 0x%02x\n",msg->u.dcmMsg.u.chanActiv.mrControl.RAE);
    }
    if (optional[15] == 15)
    {
         printf("length    :   0x%02x\n",
                                  msg->u.dcmMsg.u.chanActiv.codecTypes.length);
         printf("sysId     :   0x%02x\n",
                                  msg->u.dcmMsg.u.chanActiv.codecTypes.sysId);
         printf("codecList :   0x%02x\n",
                              msg->u.dcmMsg.u.chanActiv.codecTypes.codecList);
         if (msg->u.dcmMsg.u.chanActiv.codecTypes.codecList > 0x07)
         {
         printf("MACS[0]   :   0x%02x\n",
                                 msg->u.dcmMsg.u.chanActiv.codecTypes.MACS[0]);
         printf("TFO_VER[0 :   0x%02x\n",
                              msg->u.dcmMsg.u.chanActiv.codecTypes.TFO_VER[0]);
          
         printf("SCS       :   0x%02x\n",
                                    msg->u.dcmMsg.u.chanActiv.codecTypes.SCS[0]);
             printf("MACS[1]   :   0x%02x\n",
                              msg->u.dcmMsg.u.chanActiv.codecTypes.MACS[1]);
             printf("TFO_VER[1]:   0x%02x\n",
                              msg->u.dcmMsg.u.chanActiv.codecTypes.TFO_VER[1]);
              
             printf("SCS[1]    :   0x%02x\n",
                                   msg->u.dcmMsg.u.chanActiv.codecTypes.SCS[1]);
        }
         printf("prfCdecTy :   0x%02x\n",
                          msg->u.dcmMsg.u.chanActiv.codecTypes.prefCodecType);
    }
    fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Channel Activation Acknowledge information elements 
        from the file,encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
HandleChanActvAck(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadChanActvAck(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Channel Activation Acknowledge Failed ret::%d\n",ret);
        return ret;
    }
    else
                                                                                                                            
    {
	printf(" ********************** ENCODED DATA **********************\n");
        printf("Encoding Channel Activation Ack Success ret::%d\n\n",ret);
	printEncComDcmm(buffer,len);      
        printf("\n\n");
    }
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Channel Activation Ack Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
	printf("************************ DECODED DATA *********************\n");
    	printf("Decoding Channel Activation Ack Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printDecComDcmm(msg);
        printf("Frame Number    :   0x%04x\n",
                                         msg.u.dcmMsg.u.chanActivAck.frameNum);
    }
    return ITS_SUCCESS;
}
   /*implementation:internal
*
* PURPOSE:
*       Handles reading the Channel Activation Acknowledge  
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
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/                                                                                                                  
ITS_INT
ReadChanActvAck(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int k=0,kcount;
    int i=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int no_params = 6;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: CHANNEL ACTIVATION ACKNOWLEDGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"CHANACT_ACK START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"CHANACT_ACK END\n")!= 0)
            {
                if(line[0]=='M')
                {
                    if(line[1]=='\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
                tokentab=(char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = (char*)calloc(strlen(tokentab)+1,sizeof(char));
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
    if (kcount == no_params)
    {
     
    }
    else
    {
        printf("encoded string is missing\n");
    }    

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: CHANNEL ACTIVATION ACKNOWLEDGE\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    ComFunc (msg,temp,bufspace,kcount);
    for(k=0; k<kcount; k++)
    {
	l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];
        if (k == 5)
        {
            msg->u.dcmMsg.u.chanActivAck.frameNum = temp[k];
            printf("Frame Number    :   0x%02x\n",
                                       msg->u.dcmMsg.u.chanActivAck.frameNum);
        }
    }
    fclose(fp);
}

ITS_INT
ComFunc ( ABIS_TRAFFIC_MANAGEMENT_MSG *msg,unsigned char temp[300],
         char *bufspace[300],int kcount)
{
    int k = 0; 
    unsigned char l[300];
    
    for(k = 0; k < kcount; k++)
    {	
        if(bufspace[k][0] != '0' && bufspace[k][1] != 'x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9' )
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
             printf("msgDesc         :   0x%02x\n", 
                                      msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
             msg->genElemnts.msgDesc.trasparent = temp[k];
             printf("msgdesc(T)      :   0x%02x\n",
                                     msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {  
            msg->genElemnts.msgType = temp[k];
            printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k]; 
             printf("chanBits        :   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                     msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
    }
    return;
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Channel Activation Negative Acknowledge  information
*       elements from the file,
*       encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
HandleChanNActvAck(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadChanNActvAck(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Channel Activation Negative Acknowledge Failed"
                 "ret :: %d\n", ret);
        return ret;
    }
    else
    {
       printf("********************** ENCODED DATA ************************\n");
       printf("Encoding Channel Activation Negative Acknowledge "
               " Success  ret :: %d\n\n",ret);
       printEncComDcmm(buffer,len);
       printf("\n\n");
    }
                                                                                                                             
    printf("********************** DECODED DATA ***************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Channel Activation Negative "
                "Acknowledge Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding Channel Activation Negative "
                "Acknowledge Success  ret :: %d\n", ret);
        printDecComDcmm(msg);
        printf("length          :   0x%02x\n", 
                                msg.u.dcmMsg.u.chanActivNack.length);
	printf("Cause Value     :   0x%02x\n", 
                                msg.u.dcmMsg.u.chanActivNack.causeVal);
	printf("Diagnostics     :   0x%02x\n", 
                                msg.u.dcmMsg.u.chanActivNack.diagnostics[0]);
    }
    return ITS_SUCCESS;
}
 /*implementation:internal
*
* PURPOSE:
*       Handles reading the Channel Activation Negative Acknowledge  
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
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*/                                                                                                                    
ITS_INT
ReadChanNActvAck(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_params=8;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int diagcount;

    printf("                        \n");
    printf("Message Name: CHANNEL ACTIVATION NEGATIVE ACKNOWLEDGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"CHANACT_NEG_ACK START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),
                    "CHANACT_NEG_ACK END\n")!=0)
            {
                if(line[0]=='M')
                {
                    if(line[1]=='\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: CHANNEL ACTIVATION NEGATIVE ACKNOWLEDGE\n");
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
        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||
             bufspace[k][2] >= '0' && bufspace[k][2] <= '9' && 
             bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f' ||
             bufspace[k][3] >= '0' && bufspace[k][3] <= '9' )
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
             printf("msgDesc         :   0x%02x\n",
                                      msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
             msg->genElemnts.msgDesc.trasparent = temp[k];
             printf("msgdesc(T)      :   0x%02x\n",
                                     msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
             msg->genElemnts.msgType = temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k==3)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
             printf("chanBits        :   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                      msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
	if (k == 5)
        {
            msg->u.dcmMsg.u.chanActivNack.length = temp[k];
            printf("Frame Number    :   0x%04x\n",
                                    msg->u.dcmMsg.u.chanActivNack.length);
        }
	if (k == 6)
        {
            msg->u.dcmMsg.u.chanActivNack.causeVal = temp[k];
            printf("Frame Number    :   0x%04x\n",
                                   msg->u.dcmMsg.u.chanActivNack.causeVal);
        }
        if(k == 7)
        {
	   printf("diagnostics     :   0x%02x\n",temp[k]);	   
           for (diagcount=0;
                diagcount<msg->u.dcmMsg.u.chanActivNack.length;diagcount++)
            {
               msg->u.dcmMsg.u.chanActivNack.diagnostics[diagcount] = temp[k];
            }
        }
    }
    fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Connection Failure Indication information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/
ITS_INT
HandleConFLInd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadConFLInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Connection Failure Indication "
                "Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    printf("******************** ENCODED DATA **************************\n");
    {
        printf("Encoding Connection failure Indication "
               "Success  ret :: %d\n\n", ret);
        /* display buffer */
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
        printf("Decoding Connection Failure Indication Failed " 
                " ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Connection Failure Indication "
                "Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                 msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                            msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                          msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("length          :   0x%02x\n", 
                                         msg.u.dcmMsg.u.chanActivNack.length);
	printf("Cause Value     :   0x%02x\n",
                                       msg.u.dcmMsg.u.chanActivNack.causeVal);
	printf("Diagnostics     :   0x%02x\n", 
                                 msg.u.dcmMsg.u.chanActivNack.diagnostics[0]);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the Connection Failure Neg Ack information elements from the
*        file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
ITS_INT
ReadConFLInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_params = 8;
    unsigned char buffer[300];
    unsigned char temp;
    long l;
    int diagcount;
    printf("                        \n");
    printf("Message Name: CONNECTION FAILURE INDICATION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"CON_FL_IND START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"CON_FL_IND END\n") != 0)
            {
                if(line[0] == 'M')
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
                printf("%s",line);
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: CONNECTION FAILURE INDICATION\n");
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
        l = strtol(bufspace[k],NULL,16);
        temp = (unsigned char)l;
        if (k == 0)
        {
             msg->genElemnts.msgDesc.msgGruop = temp;
             printf("msgDesc     :   0x%02x\n", 
                                         msg->genElemnts.msgDesc.msgGruop) ;
        }
        if (k == 1)
        {
             msg->genElemnts.msgDesc.trasparent = temp;
             printf("msgdesc(T)  :   0x%02x\n",
                                        msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
             msg->genElemnts.msgType = temp;
             printf("msgType     :   0x%02x\n", msg->genElemnts.msgType);
        }
        if (k == 3)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp;
             printf(" chanBits   :   0x%02x\n",
                      msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp;
             printf("timeSlotNum :   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
	if (k == 5)
        {
            msg->u.dcmMsg.u.chanActivNack.length = temp;
            printf("length      :   0x%02x\n",
                                    msg->u.dcmMsg.u.chanActivNack.length);
        }
	if (k == 6)
        {
            msg->u.dcmMsg.u.chanActivNack.causeVal = temp;
            printf("causeVal    :   0x%02x\n",
                                    msg->u.dcmMsg.u.chanActivNack.causeVal);
        }       
        if(k == 7)
        {
	   printf("diagnostics     :   0x%02x\n",temp);	   
           for (diagcount=0; 
                diagcount<msg->u.dcmMsg.u.chanActivNack.length;diagcount++)
            {
               msg->u.dcmMsg.u.chanActivNack.diagnostics[diagcount] = temp;
            }

        }
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the deactivate sacch information elements from the file,
*       encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
HandleDeActSacch(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadDeActSacch(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    printf("************************* ENCODED DATA *********************\n");
    {
        printf("Encoding Data Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        for (i = 0; i < len; i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("******************** DECODED DATA ***************************\n");
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
        printf("msgDesc         :   0x%02x\n",msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n", 
                                     msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                          msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                        msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
    }
    return ITS_SUCCESS;
}
 /*implementation:internal
*
* PURPOSE:
*       Reading the Deactivate Sacch information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                                                                                                                    
ITS_INT
ReadDeActSacch(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_params = 5;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: DEACTIVATE SACCH\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"DEACT_SACCH START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"DEACT_SACCH END\n") != 0)
            {
                if(line[0] == 'M')
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
                printf("%s",line);
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: DEACTIVATE SACCH\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if(bufspace[k][0] != '0' && bufspace[k][1] != 'x')
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
             printf("msgDesc         :   0x%02x\n", 
                                         msg->genElemnts.msgDesc.msgGruop) ;
        }
        if (k == 1)
        {
             msg->genElemnts.msgDesc.trasparent = temp[k];
             printf("msgdesc(T)      :   0x%02x\n",
                                         msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
             msg->genElemnts.msgType = temp[k];
             printf("msgType         :   0x%02x\n",
                                         msg->genElemnts.msgType);
        }
        if (k == 3)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
             printf("chanBits        :   0x%02x\n",
                       msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                      msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
    }
    fclose(fp);
}   
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Encrytion Command information elements from the file,
*       encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/
ITS_INT            
HandleEncCom(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadEncCom(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding encryption command Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Encoding encryption command  success  ret :: %d\n\n", ret);
       //  display buffer 
        printf("*********************** ENCODED DATA ********************\n");
        for(i = 0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("************************ DECODED DATA ***********************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding encryption command Acknowledge "
                " Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Decoding encryption command Success  ret :: %d\n", ret);
      
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                    msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
	printf("chanBits        :   0x%02x\n", 
                      msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                    msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
	printf("Encrytion length:   0x%02x\n", 
                             msg.u.dcmMsg.u.encrCmd.encryption.length);
	printf("Algorithm Id    :   0x%02x\n", 
                        msg.u.dcmMsg.u.encrCmd.encryption.algorithmId);
	printf("Encryption Key  :   0x%02x\n", 
                            msg.u.dcmMsg.u.encrCmd.encryption.key[0]); 
	printf("chanBits        :   0x%02x\n", 
                             msg.u.dcmMsg.u.encrCmd.linkId.chanlBits);
        printf("NA              :   0x%02x\n", 
                                    msg.u.dcmMsg.u.encrCmd.linkId.NA);
        printf("priority        :   0x%02x\n", 
                              msg.u.dcmMsg.u.encrCmd.linkId.priority);
	printf("SAPI            :   0x%02x\n",
                                   msg.u.dcmMsg.u.encrCmd.linkId.SAPI);
	printf("length		:   0x%02x\n", 
                              msg.u.dcmMsg.u.encrCmd.l3Info.lengthInd);
	printf("LLSDU           :   0x%02x\n", 
                               msg.u.dcmMsg.u.encrCmd.l3Info.LLSDU[0]);	                                 
    }
    return ITS_SUCCESS;
}
 /*implementation:internal
*
* PURPOSE:
*       Reading the Encrytion Command information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                                                                                                                    
ITS_INT
ReadEncCom(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_params = 14;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: ENCRYPTION COMMAND\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"ENCCOM START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"ENCCOM END\n") != 0)
            {
                if(line[0] == 'M')
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
                printf("%s",line);
                tokentab=(char *)strtok(line,"\t");
                while (tokentab)
                {
                    buftab[i] = (char*)calloc(strlen(tokentab)+1,sizeof(char));
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: MODE MODIFY ACKNOWLEDGE\n");
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
            printf("msgDesc         :   0x%02x\n", 
                                         msg->genElemnts.msgDesc.msgGruop) ;
        }
        if (k == 1)
        {
            msg->genElemnts.msgDesc.trasparent = temp[k];
            printf("msgdesc(T)      :   0x%02x\n",
                                       msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
            msg->genElemnts.msgType = temp[k];
            printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k]; 
            printf("chanBits        :   0x%02x\n",
                       msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum     :   0x%02x\n",
                     msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
        if (k == 5)
        {
            msg->u.dcmMsg.u.encrCmd.encryption.length = temp[k];
            printf("Encryp length   :   0x%02x\n",
                              msg->u.dcmMsg.u.encrCmd.encryption.length);
        }
	if (k == 6)
        {
            msg->u.dcmMsg.u.encrCmd.encryption.algorithmId = temp[k];
            printf("Algorithm id    :   0x%02x\n",
                         msg->u.dcmMsg.u.encrCmd.encryption.algorithmId);
        }
	if (k == 7)
        {
	    printf("Encryption key  :   0x%02x\n",temp[k]);
 	    for(i=0; i<msg->u.dcmMsg.u.encrCmd.encryption.length; i++)
	    {
                msg->u.dcmMsg.u.encrCmd.encryption.key[i] = temp[k];
            }
        }
	if (k == 8)
        {
	    msg->u.dcmMsg.u.encrCmd.linkId.chanlBits = temp[k];       
	    printf("Chanl Bits     :   0x%02x\n",
                              msg->u.dcmMsg.u.encrCmd.linkId.chanlBits);
        }
	if (k == 9)
        {
	    msg->u.dcmMsg.u.encrCmd.linkId.NA = temp[k];
	    printf("NA             :   0x%02x\n",
                                     msg->u.dcmMsg.u.encrCmd.linkId.NA);
        }
	if (k == 10)
        {
            msg->u.dcmMsg.u.encrCmd.linkId.priority = temp[k];
	    printf("priority        :   0x%02x\n", 
                                  msg->u.dcmMsg.u.encrCmd.linkId.priority);
        }
	if (k == 11)
        {
            msg->u.dcmMsg.u.encrCmd.linkId.SAPI=temp[k];
            printf("SAPI            :   0x%02x\n",
                                    msg->u.dcmMsg.u.encrCmd.linkId.SAPI);
        }
	if (k == 12)
        {
            msg->u.dcmMsg.u.encrCmd.l3Info.lengthInd = temp[k];
            printf("L3 lengInd       :   0x%02x\n",
                                  msg->u.dcmMsg.u.encrCmd.l3Info.lengthInd);
        }
  	if (k == 13)
        {
            printf("LLSDU             :   0x%02x\n",temp[k]);
	    for(i=0; i<msg->u.dcmMsg.u.encrCmd.l3Info.lengthInd; i++)
	    {
                msg->u.dcmMsg.u.encrCmd.l3Info.LLSDU[i] = temp[k];
            }

        }
    }
    fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Measurement Result information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/

ITS_INT
HandleMeasRes(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem =0 ;
    FILE *fptr;
    char line[1024];
    ret_elem = ReadMeasRes(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    msg.genElemnts.msgDesc.msgGruop = 0x78; 
    msg.genElemnts.msgDesc.trasparent= 0x00;
    msg.genElemnts.msgType = 0x28;
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Measuement Result Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("******************* ENCODED DATA *************************\n");
        printf("Encoding Measurement Result Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("********************** DECODED DATA ************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Measurement Result Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding Measurement Result Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                         msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                         msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                       msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf(" measresnum     :   0x%02x\n", 
                                      msg.u.dcmMsg.u.measRes.measResultNum);
        printf("uplinkmeaslenmsg:   0x%02x\n", 
                                   msg.u.dcmMsg.u.measRes.uplinkMeas.length);
         
        printf("rfu             :   0x%02x\n", 
                                     msg.u.dcmMsg.u.measRes.uplinkMeas.rfu);
        printf("dtxd            :   0x%02x\n",
                                     msg.u.dcmMsg.u.measRes.uplinkMeas.dtxd);
        printf("rxlevfull ip    :   0x%02x\n", 
                             msg.u.dcmMsg.u.measRes.uplinkMeas.rxlevFullUp);
        printf("rxlev Subup     :   0x%02x\n", 
                               msg.u.dcmMsg.u.measRes.uplinkMeas.rxlevSubUp);
        printf("rxqualfulup     :   0x%02x\n", 
                             msg.u.dcmMsg.u.measRes.uplinkMeas.rxqualFullUp);
        printf("rxqual subup    :   0x%02x\n", 
                              msg.u.dcmMsg.u.measRes.uplinkMeas.rxqualSubUp);
         printf("lengthInd             : 0x%02x\n",
                                  msg.u.dcmMsg.u.measRes.l3Info.lengthInd);
        printf("LLSDU                 : 0x%02x\n",
                                     msg.u.dcmMsg.u.measRes.l3Info.LLSDU[0]);
                     
        printf("timingOffset        : 0x%02x\n",
                                       msg.u.dcmMsg.u.measRes.timingOffset);

        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"MEASURE_RSLT START\n")==0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "MEASURE_RSLT END\n")!=0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"L1Info"))
                    {
                        printf("l1Infopower :0x%02x\n", 
                                     msg.u.dcmMsg.u.measRes.l1Info.powerLevel);
                        printf("l1Infotiming:0x%02x\n", 
                                    msg.u.dcmMsg.u.measRes.l1Info.timingAdvns);
                        printf("l1InfoFPC   :0x%02x\n",
                                            msg.u.dcmMsg.u.measRes.l1Info.FPC);
                    }

 
                    if (line[0]=='O' && line[1]=='\t' && line[2]=='0' 
                        && strstr(line,"opt2"))
                    {
                        printf("l3Infolen: 0x%02x\n",
                                     msg.u.dcmMsg.u.measRes.l3Info.lengthInd);
                        printf("LLSDU   :  0x%02x\n",
                                     msg.u.dcmMsg.u.measRes.l3Info.LLSDU[0]);
                    }                 
                    
                    if (line[0]=='O' && line[1]=='\t' && line[2]=='0' 
                    && strstr(line,"TimingOffset"))
                    {
                        printf("TimimgOff: 0x%02x\n",
                                          msg.u.dcmMsg.u.measRes.timingOffset);
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
*       Reading the Measurement Result information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                             
ITS_INT
ReadMeasRes(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0,icount, k =0, kcount;
    char c, str[10], str1[10], str2[10], str3[10];
    unsigned char buffer[300];
    unsigned char temp[300],temp1;
    long l[300], l1;
    int optional[20];
    int tot_elem = 0;
    printf("                        \n");
    printf("Message Name: Measurement Result\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
     
    CLEAR_TM_DCM_MR_OPTIONAL_BIT_MAP(msg);

    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"MEASURE_RSLT START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "MEASURE_RSLT END\n")!=0)
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
                /**** OPTIONAL BITS ****/     

                /**L1 Information **/
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"L1Info"))
                {
                    optional[1] = 1;
                    SET_TM_DCM_MR_L1_INFO(msg);
                    sscanf(line,"%c %s %s %s ",&c,&str,&str1,&str2);
                    for (i=0; i<10; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.measRes.l1Info.powerLevel = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.measRes.l1Info.timingAdvns = 
                                                                      temp[i];
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.measRes.l1Info.FPC = temp[i];
                        }
                                                                                                                             
                    }
                }
               /** L3 Information **/
#if 0
                if (line[0] == 'O' && line[1] == '\t' && line[2] =='0'
                    && strstr(line,"L3Info"))
                {
                    optional[2] = 2;
                    SET_TM_DCM_MR_L3_INFO(msg);
                    sscanf(line,"%c %s %s ",&c,&str,&str1);
                    for (i=0; i<3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.measRes.l3Info.lengthInd = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for (k=0; 
                            k<msg->u.dcmMsg.u.measRes.l3Info.lengthInd;k++)
                            {
                                msg->u.dcmMsg.u.measRes.l3Info.LLSDU[k] = 
                                                                   temp[i];
                            }
                        }
                    }
                }
                /** Timimng Offset **/
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                    && strstr(line,"TimingOffset"))
                {
                    optional[3] = 3;
                    SET_TM_DCM_MR_MS_TIMING_OFFSET(msg);
                    sscanf(line,"%c %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
                    msg->u.dcmMsg.u.measRes.timingOffset = temp1;
                }    
#endif
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
    if (kcount == 16 || kcount > 16)
    {
    }
    else
    {
	printf("Information element missing\n");
//      exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: MEASUREMENT RESULT\n");
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
             printf("msgDesc         :   0x%02x\n", 
                                     msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
             msg->genElemnts.msgDesc.trasparent = temp[k];
             printf("msgdesc(T)      :   0x%02x\n",
                                     msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
             msg->genElemnts.msgType = temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
             printf("chanBits        :   0x%02x\n",
                         msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                       msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
	if (k == 5)
        {
            msg->u.dcmMsg.u.measRes.measResultNum = temp[k];
	    printf("Meas Res Num     :   0x%02x\n", 
                                     msg->u.dcmMsg.u.measRes.measResultNum);
        }
	if (k == 6)
        {
            msg->u.dcmMsg.u.measRes.uplinkMeas.length = temp[k];
	    printf("Uplink meas len  :   0x%02x\n", 
                                   msg->u.dcmMsg.u.measRes.uplinkMeas.length);
        }
	if (k == 7)
        {
            msg->u.dcmMsg.u.measRes.uplinkMeas.rfu = temp[k];
	    printf("rfu              :   0x%02x\n", 
                                      msg->u.dcmMsg.u.measRes.uplinkMeas.rfu);
        }
	if (k == 8)
        {
            msg->u.dcmMsg.u.measRes.uplinkMeas.dtxd = temp[k];
	    printf("DTXd             :   0x%02x\n",
                                     msg->u.dcmMsg.u.measRes.uplinkMeas.dtxd);
        }
	if (k == 9)
        {
            msg->u.dcmMsg.u.measRes.uplinkMeas.rxlevFullUp = temp[k];
	    printf("Rxlev full up    :   0x%02x\n", 
                              msg->u.dcmMsg.u.measRes.uplinkMeas.rxlevFullUp);
        }
	if (k == 10)
        {
            msg->u.dcmMsg.u.measRes.uplinkMeas.rxlevSubUp = temp[k];
	    printf("Rxlev Subup      :   0x%02x\n", 
                               msg->u.dcmMsg.u.measRes.uplinkMeas.rxlevSubUp);
        }
	if (k == 11)
        {
            msg->u.dcmMsg.u.measRes.uplinkMeas.rxqualFullUp = temp[k];
	    printf("rxqual full up   :   0x%02x\n", 
                            msg->u.dcmMsg.u.measRes.uplinkMeas.rxqualFullUp);
        }
	if (k == 12)
        {
            msg->u.dcmMsg.u.measRes.uplinkMeas.rxqualSubUp = temp[k];
	    printf("rxqual full up   :   0x%02x\n", 
                             msg->u.dcmMsg.u.measRes.uplinkMeas.rxqualSubUp);
        }
        if (k == 13)
        {
	    printf("SMI              :   0x%02x\n",temp[k]);	   
            for(i=0; i<msg->u.dcmMsg.u.measRes.uplinkMeas.length; i++)
            {
                msg->u.dcmMsg.u.measRes.uplinkMeas.SMI[i] = temp[k];
            }
        }
        if (k == 14)
        {  
            msg->u.dcmMsg.u.measRes.bsPower.FPC = temp[k];  
            printf("FPC(BSPOW)       :   0x%02x\n", msg->u.dcmMsg.u.measRes.bsPower.FPC);
        }
        if (k == 15)
        {  
            msg->u.dcmMsg.u.measRes.bsPower.powerLevel = temp[k];                           
            printf("powerLevel(BSPOW):   0x%02x\n", 
                                   msg->u.dcmMsg.u.measRes.bsPower.powerLevel);
        }
          
        if (k == 19)
        { 
            SET_TM_DCM_MR_L3_INFO(msg); 
            msg->u.dcmMsg.u.measRes.l3Info.lengthInd = temp[k];                           
            printf("L3Inf(len        :   0x%02x\n", 
                                   msg->u.dcmMsg.u.measRes.l3Info.lengthInd);
        }
         
        if (k == 20)
        {  
            printf("LLSDU            :   0x%02x\n", 
                                            temp[k]);
            for(i=0; i<msg->u.dcmMsg.u.measRes.l3Info.lengthInd;i++)
            {
                msg->u.dcmMsg.u.measRes.l3Info.LLSDU[i] = temp[k];
            }
       
        }
         
        if (k == 21)
        {  
            SET_TM_DCM_MR_MS_TIMING_OFFSET(msg);
            msg->u.dcmMsg.u.measRes.timingOffset = temp[k];                           
            printf("TimimgOffset      :   0x%02x\n", 
                                    msg->u.dcmMsg.u.measRes.timingOffset);
        }
    }
    if (optional[1] == 1)
    {
        printf("l1InfopowerLevel     : 0x%02x\n", 
                                  msg->u.dcmMsg.u.measRes.l1Info.powerLevel);
        printf("l1Infotiming         : 0x%02x\n",
                                 msg->u.dcmMsg.u.measRes.l1Info.timingAdvns);
        printf("l1InfoFPC            : 0x%02x\n", msg->u.dcmMsg.u.measRes.l1Info.FPC);
    }
    if (optional[2] == 2)
    {
       printf("lengthInd             : 0x%02x\n", 
                                   msg->u.dcmMsg.u.measRes.l3Info.lengthInd);
       printf("LLSDU                 : 0x%02x\n",
                                     msg->u.dcmMsg.u.measRes.l3Info.LLSDU[0]);
    }
    if (optional[3] == 3)
    {
         printf("timingOffset        : 0x%02x\n", 
                                       msg->u.dcmMsg.u.measRes.timingOffset);    
    }
    fclose(fp);
    return tot_elem;
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Mode Modify information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/

ITS_INT
HandleModeModify(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem =0 ;
    FILE *fptr;
    char line[1024];
    ret_elem = ReadModeModify(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    /*msg.genElemnts.msgDesc.msgGruop = 0x78;
    msg.genElemnts.msgDesc.trasparent = 0x01;
    msg.genElemnts.msgType = 0x29;*/
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Mode Modify Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    printf("******************** ENCODED DATA *************************\n");
    {
        printf("Encoding Mode Modify Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("********************** DECODED DATA ************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Mode Modify Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding Mode Modify Success  ret :: %d\n", ret);
        /* display buffer */
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                            msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", 
                                           msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n",msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                             msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                           msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("chnlmod len     :   0x%02x\n", 
                                 msg.u.dcmMsg.u.modeModifyReq.chnlMode.length);
        printf("dtxd            :   0x%02x\n", 
                                   msg.u.dcmMsg.u.modeModifyReq.chnlMode.dtxd);
        printf("dtx             :   0x%02x\n", 
                                   msg.u.dcmMsg.u.modeModifyReq.chnlMode.dtxu);
 	printf("indicator       :   0x%02x\n", 
                              msg.u.dcmMsg.u.modeModifyReq.chnlMode.indicator);
        printf("rateAndType     :   0x%02x\n",
                            msg.u.dcmMsg.u.modeModifyReq.chnlMode.rateAndType);
        printf("codingAlg       :   0x%02x\n",
                             msg.u.dcmMsg.u.modeModifyReq.chnlMode.codingAlg);
       /* printf("rate            :   0x%02x\n",
                                 msg.u.dcmMsg.u.modeModifyReq.chnlMode.rate);
        printf("service         :   0x%02x\n",
                               msg.u.dcmMsg.u.modeModifyReq.chnlMode.service);*/
        /* optional bits */
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if (strcmp(line,"MOD_MODIFY START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                       "MOD_MODIFY END\n")!=0)
                {
                    /* Channel identifier */
                    if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                    strstr(line,"opt1"))
                    {
                        printf("length: 0x%02x\n",
                               msg.u.dcmMsg.u.modeModifyReq.encryption.length);
                        printf("algid : 0x%02x\n",
                          msg.u.dcmMsg.u.modeModifyReq.encryption.algorithmId);
                        printf("key   : 0x%02x\n",
                               msg.u.dcmMsg.u.modeModifyReq.encryption.key[0]);
                    }
                    /* Main Channel Reference */
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' && 
                       strstr(line,"opt2")) 
                    {                                                                          
                        printf("chnlre: 0x%02x\n",
                                  msg.u.dcmMsg.u.modeModifyReq.mainChnlRefTn);        
                    }
                    /*MR Configuration */
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' && 
                        strstr(line,"opt3"))
                    {
                        printf("mconlen:0x%02x\n",
                                 msg.u.dcmMsg.u.modeModifyReq.mrConfig.length); 
                        printf("cont   :0x%02x\n", 
                             msg.u.dcmMsg.u.modeModifyReq.mrConfig.content[0]); 
                    }
                    /* MR Control */
                    if (line[0]=='O' && line[1]=='\t' && line[2]=='0' && 
                        strstr(line,"opt4"))
                    {
                        printf("TFO    :0x%02x\n", 
                                 msg.u.dcmMsg.u.modeModifyReq.mrControl.TFO);
                        printf("PRE    :0x%02x\n",
                                 msg.u.dcmMsg.u.modeModifyReq.mrControl.PRE);
                        printf("RAE    :0x%02x\n", 
                                 msg.u.dcmMsg.u.modeModifyReq.mrControl.RAE);
                    }
                    /* Supported Codec Types */
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' &&
                    strstr(line,"opt5"))
                    {
                        printf("length :0x%02x\n", 
                              msg.u.dcmMsg.u.modeModifyReq.codecTypes.length);
                        printf("sysId  :0x%02x\n", 
                               msg.u.dcmMsg.u.modeModifyReq.codecTypes.sysId);
                        printf("cdecLst:0x%02x\n",
                           msg.u.dcmMsg.u.modeModifyReq.codecTypes.codecList);
                        printf("MACS   :0x%02x\n", 
                            msg.u.dcmMsg.u.modeModifyReq.codecTypes.MACS[0]);
                        printf("TFO_VER:0x%02x\n",
                          msg.u.dcmMsg.u.modeModifyReq.codecTypes.TFO_VER[0]);
                        printf("MACS[1]:0x%02x\n", 
                             msg.u.dcmMsg.u.modeModifyReq.codecTypes.MACS[1]);
                        printf("TFO_VER:0x%02x\n",
                          msg.u.dcmMsg.u.modeModifyReq.codecTypes.TFO_VER[1]);
                        printf("SCS[0] :0x%02x\n",
                                 msg.u.dcmMsg.u.modeModifyReq.codecTypes.SCS[0]);
                        printf("SCS[1] :0x%02x\n",
                                 msg.u.dcmMsg.u.modeModifyReq.codecTypes.SCS[1]);
                        printf("prfCdec:0x%02x\n", 
                        msg.u.dcmMsg.u.modeModifyReq.codecTypes.prefCodecType);
                    }
                }
                break;
            }       
        }         
    }          
    return ITS_SUCCESS;
}         
/*implementation:internal
*
* PURPOSE:
*       Reading the Mode Modify information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                         
ITS_INT
ReadModeModify(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int tot_elem = 0;
    int opt_elem = 0;
    int mand_elem = 14;
    unsigned char buffer[300];
    unsigned char temp[300],temp1;
    long l[300],l1;
    char str[10],str1[10],str2[10],str3[10],str4[10];
    char str5[10],str6[10],str7[10],str8[10],str9[10];
    int optional[20];
    char c;
    printf("                        \n");
    printf("Message Name: Mode Modify\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
     
    CLEAR_TM_DCM_MM_OPTIONAL_BIT_MAP(msg);
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"MOD_MODIFY START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"MOD_MODIFY END\n") != 0)
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
                 
                if (line[0] == 'M' && strstr(line,"Message Type"))
                {
                    sscanf(line,"%c %s %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
                    msg->genElemnts.msgType =temp1;
                }        
                
                if (line[0] == 'M' && strstr(line,"Message discriminator"))
                {
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    //printf("%s\n",str);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
 	                    temp[i] = (unsigned char)l[i];
                            msg->genElemnts.msgDesc.msgGruop=temp[i];
                            printf("msggrp is %02x\n", msg->genElemnts.msgDesc.msgGruop); 
                        }
                                                                                                                             
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->genElemnts.msgDesc.trasparent=temp[i];
                        }
                                                                                                                             
                    }
                }
                  if (line[0] == 'M' && strstr(line,"Channel Number"))
                {
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0;i<6;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits =
                                                                    temp[i];
                                                                                                                             
                        }
                                                                                                                             
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum =
                                                                     temp[i];
                        }
                                                                                                                             
                    }
                                                                                                                             
                }
                  if (line[0] == 'M' && strstr(line,"Channel Mode"))
                {
                    sscanf(line,"%c %s %s %s %s %s %s",&c,&str,&str1,
                           &str2,&str3,&str4,&str5);
                                                                                                                             
                    for(i=0;i<10;i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                             msg->u.dcmMsg.u.modeModifyReq.chnlMode.length = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                             msg->u.dcmMsg.u.modeModifyReq.chnlMode.dtxd = temp[i];
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.chnlMode.dtxu = temp[i];
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.chnlMode.indicator =
                                                                    temp[i];
                        }
                          if (i == 4)
                        {
                            l[i] = strtol(str4,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.chnlMode.rateAndType =
                                                              temp[i];
                        }
                        if (i == 5)
                        {
                            l[i] = strtol(str5,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.chnlMode.codingAlg =
                                                                      temp[i];
                        }
                                                                                                                             
                    }
                }

               /** OPTIONAL PARAMETERS STARTS-ENCRYTION COMMAND **/
                if (line[0]== 'O' && line[1]== '\t' && line[2]=='0' 
                   && strstr(line,"opt1"))
                {
                    SET_TM_DCM_MM_ENCRYPT_INFO(msg);
                    sscanf("%c %s %s %s",&c,&str,&str1,&str2);
                    optional[1] = 1;
                    for(i=0; i<6; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.encryption.length = 
                                                                     temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.encryption.\
                                                algorithmId = temp[i];
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for( k=0; 
                          k< msg -> u.dcmMsg.u.modeModifyReq.encryption.length; 
                          k++)
                            {
                                msg->u.dcmMsg.u.modeModifyReq.encryption.\
                                key[k] = temp[i];
                            }
                        }
                    }

                }
               /** MAIN CHANNEL REFERENCE **/
                if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' && 
                   strstr(line,"opt2"))
                {
                    optional[2] = 2;
                    SET_TM_DCM_MM_MAIN_CHANNEL_REF(msg);
                    sscanf(line,"%c %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;                    
                    msg->u.dcmMsg.u.modeModifyReq.mainChnlRefTn = temp1;
                }
                /** MULTIRATE CONFIGURATION **/
                if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                && strstr(line,"opt3"))
                {
                    optional[3] = 3;
                    SET_TM_DCM_MM_MULTI_RATE_CONFIG(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for(i=0; i<6; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.mrConfig.length =
                                                                    temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for (k=0; 
                             k < msg->u.dcmMsg.u.modeModifyReq.mrConfig.length;
                             k++)
                            {
                                msg->u.dcmMsg.u.modeModifyReq.mrConfig.\
                                content[k]=temp[i];
                            }
                        }
                    }
                }
                /** MULTIRATE CONTROL **/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0'
                    && strstr(line,"opt4"))
                {
                    optional[4] = 4;
                    SET_TM_DCM_MM_MULTI_RATE_CONTROL(msg);
                    sscanf(line,"%c %s %s %s",&c,&str,&str1,&str2);
                    for(i=0; i<6; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.mrControl.TFO =
                                                                  temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.mrControl.PRE = 
                                                                  temp[i];
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.mrControl.RAE = 
                                                                  temp[i];
                        }
                    }
                }
                /**** Supported Codec types ****/
                if (line[0]=='O' && line[1]=='\t' && line[2]=='0' 
                    && strstr(line,"opt5"))
                {
                    optional[5] = 5;
                    SET_TM_DCM_MM_SUPPORTED_CODEC_TYPES(msg);
                    sscanf(line,"%c %s %s %s %s %s %s %s %s %s",&c,
                    &str,&str1,&str2,&str3,&str4,&str5,&str6,&str7,&str8,&str9);
                    for(i=0; i<10; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.length = 
                                                                     temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.sysId = 
                                                                     temp[i];
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.codecList =
                                                                        temp[i];
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.MACS[0] =
                                                                      temp[i];
                        }
                        if (i == 4)
                        {
                            l[i] = strtol(str4,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.\
                                                 TFO_VER[0] = temp[i];
                        }
                        if (i == 5)
                        {
                            l[i] = strtol(str5,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.\
                                                    MACS[1] = temp[i];
                        }
                        if (i == 6)
                        {
                            l[i] = strtol(str6,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.\
                                                        TFO_VER[1] = temp[i];
                        }
                        if (i == 7)
                        {
                            l[i] = strtol(str7,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.SCS[0] =
                                                                     temp[i];
                        }
                         
                        if (i == 8)
                        {
                            l[i] = strtol(str7,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.SCS[1] =
                                                                     temp[i];
                        }
                        if (i == 9)
                        {
                            l[i] = strtol(str8,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.\
                                                   prefCodecType = temp[i];
                        }
                   }
                }
                printf("%s",line);
            }
            break;
        }
    }
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount = i;
    kcount = k;
    if (kcount == 13 || kcount > 13)
    {
    }
    else
    {
	printf("Information element missing\n");
        //exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: MODE MODIFY\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
      
       printf("msgDesc :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop);
       printf("msgdesc(T) :   0x%02x\n",
                                          msg->genElemnts.msgDesc.trasparent);
       
       printf("msgType    :   0x%02x\n",msg->genElemnts.msgType);
       
       printf("chanBits   :   0x%02x\n", 
                          msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
         
       printf("timeSlotNum :   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        
        printf("length :   0x%02x\n",
                                       msg->u.dcmMsg.u.modeModifyReq.chnlMode.length);
        printf("chnlmodedtxu :   0x%02x\n",
                                       msg->u.dcmMsg.u.modeModifyReq.chnlMode.dtxu);
        printf("chnlmodedtxd :   0x%02x\n",
                                       msg->u.dcmMsg.u.modeModifyReq.chnlMode.dtxd);
        printf("indicator    :   0x%02x\n",
                                  msg->u.dcmMsg.u.modeModifyReq.chnlMode.indicator);
        printf("rateandtype  :   0x%02x\n",
                                msg->u.dcmMsg.u.modeModifyReq.chnlMode.rateAndType);
	printf("coding algo  :   0x%02x\n",
                                  msg->u.dcmMsg.u.modeModifyReq.chnlMode.codingAlg);

    if (optional[1] == 1)
    {
        printf("Enc Len     :  0x%02x\n",
                          msg->u.dcmMsg.u.modeModifyReq.encryption.length);
        printf("service     :  0x%02x\n",
                     msg->u.dcmMsg.u.modeModifyReq.encryption.algorithmId);
        printf("key         :  0x%02x\n",
                          msg->u.dcmMsg.u.modeModifyReq.encryption.key[0]);
    }
    if (optional[2] == 2)
    {
         printf("mainCnlRe  : 0x%02x\n",
                              msg->u.dcmMsg.u.modeModifyReq.mainChnlRefTn);
    }
    if (optional[3] == 3)
    {
        printf("mrconfleng  :   0x%02x\n",
                             msg->u.dcmMsg.u.modeModifyReq.mrConfig.length);
        printf("mrconfcont  :   0x%02x\n",
                         msg->u.dcmMsg.u.modeModifyReq.mrConfig.content[0]);
    }
    if (optional[4] == 4)
    {
        printf("mrCtrl TFO : 0x%02x\n", 
                               msg->u.dcmMsg.u.modeModifyReq.mrControl.TFO);
        printf("mrCtrl PRE : 0x%02x\n",
                                msg->u.dcmMsg.u.modeModifyReq.mrControl.PRE);
        printf("mrCtrl RAE : 0x%02x\n",
                                msg->u.dcmMsg.u.modeModifyReq.mrControl.RAE);
    }
    if (optional[5] == 5)
    {
        printf("length    :   0x%02x\n",
                           msg->u.dcmMsg.u.modeModifyReq.codecTypes.length);
        printf("sysId     :   0x%02x\n",
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.sysId);
        printf("codecList :   0x%02x\n",
                        msg->u.dcmMsg.u.modeModifyReq.codecTypes.codecList);
        printf("MACS[0]   :   0x%02x\n",
                           msg->u.dcmMsg.u.modeModifyReq.codecTypes.MACS[0]);
        printf("TFO_VER[0 :   0x%02x\n",
                         msg->u.dcmMsg.u.modeModifyReq.codecTypes.TFO_VER[0]);
        printf("MACS[1]   :   0x%02x\n",
                            msg->u.dcmMsg.u.modeModifyReq.codecTypes.MACS[1]);
        printf("TFO_VER[1]:   0x%02x\n",
                         msg->u.dcmMsg.u.modeModifyReq.codecTypes.TFO_VER[1]);
        printf("SCS[0]       :   0x%02x\n",
                             msg->u.dcmMsg.u.modeModifyReq.codecTypes.SCS[0]);
        printf("SCS[1]       :   0x%02x\n",
                             msg->u.dcmMsg.u.modeModifyReq.codecTypes.SCS[1]);
        printf("prfCdecTy :   0x%02x\n",
                      msg->u.dcmMsg.u.modeModifyReq.codecTypes.prefCodecType);
    }
    fclose(fp);
    return tot_elem;
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Mod Modify Ack information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
HandleModModifyAck(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    int ret1 = 0;
    ITS_OCTET buffer[300];
    ReadModModifyAck(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Mode Modify Acknowledge Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        // display buffer 
        printf("******************** ENCODED DATA ***********************\n");
        printf("Encoding Mode Modify Acknowledge Success  ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("********************** DECODED DATA **************************\n");
    ret1 = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret1 != ITS_SUCCESS)
    {
        printf("Decoding Mode Modify Acknowledge Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding Mode Modify Acknowledge Success  ret :: %d\n", ret);
         //display buffer 
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                           msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                         msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                          msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n",
                        msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
    }
    return ITS_SUCCESS;
}
 /*implementation:internal
*
* PURPOSE:
*       Reading the ModeModify Acknowledge information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                              
ITS_INT
ReadModModifyAck(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_params = 5;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: MODE MODIFY ACKNOWLEDGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"MOD_MODIFY_ACK START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),
                                                 "MOD_MODIFY_ACK END\n")!=0)
            {
                if(line[0]=='M')
                {
                    if(line[1]=='\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: MODE MODIFY ACK\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if (bufspace[k][0]!='0' && bufspace[k][1]!='x')
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
             printf("msgDesc         :   0x%02x\n", 
                                        msg->genElemnts.msgDesc.msgGruop) ;
        }
        if (k == 1)
        {
             msg->genElemnts.msgDesc.trasparent = temp[k];
             printf("msgdesc(T)      :   0x%02x\n",
                                       msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
             msg->genElemnts.msgType = temp[k];
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
             printf("chanBits        :   0x%02x\n",
                         msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }                                                                          
    }
    fclose(fp);
}   
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Mod Modify Neg Ack information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/
ITS_INT
HandleModModifyNack(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadModModifyNack(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Mode Modify Negative Acknowledge "
                "Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Encoding Mode Modify Negative Acknowledge "
                "Success  ret :: %d\n\n", ret);
        /* display buffer */
        printf("******************** ENCODED DATA ***********************\n");
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("********************* DECODED DATA **************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Mode Modify Negative Acknowledge " 
                "Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding Mode Modify Negative Acknowledge "
                "Success  ret :: %d\n", ret);
        /* display buffer */
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", 
                                      msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                    msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                     msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                    msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("length          :   0x%02x\n", 
                                   msg.u.dcmMsg.u.chanActivNack.length);
	printf("Cause Value     :   0x%02x\n", 
                                 msg.u.dcmMsg.u.chanActivNack.causeVal);
	printf("Diagnostics     :   0x%02x\n", 
                            msg.u.dcmMsg.u.chanActivNack.diagnostics[0]);
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the ModeModify Neg Ack information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
ITS_INT
ReadModModifyNack(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_params = 8;
    unsigned char buffer[300];
    unsigned char temp;
    long l;
    int diagcount;
    printf("                        \n");
    printf("Message Name: MODE MODIFY NEGATIVE ACKNOWLEDGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"MOD_MODIFY_NACK START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),
                                      "MOD_MODIFY_NACK END\n") != 0)
            {
                if (line[0] == 'M')
                {
                    if (line[1] == '\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: MODE MODIFY NEGATIVE ACKNOWLEDGE\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if (bufspace[k][0] != '0' && bufspace[k][1] != 'x')
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
        l = strtol(bufspace[k],NULL,16);
        temp = (unsigned char)l;
        if (k == 0)
        {
             msg->genElemnts.msgDesc.msgGruop = temp;
             printf("msgDesc         :   0x%02x\n",
                                         msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
             msg->genElemnts.msgDesc.trasparent = temp;
             printf("msgdesc(T)      :   0x%02x\n",
                                      msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
             msg->genElemnts.msgType = temp;
             printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp;
             printf("chanBits        :   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp;
             printf("timeSlotNum     :   0x%02x\n",
                      msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
	if (k == 5)
        {
            msg->u.dcmMsg.u.chanActivNack.length = temp;
            printf("length          :   0x%02x\n",
                                     msg->u.dcmMsg.u.chanActivNack.length);
        }
	if (k == 6)
        {
            msg->u.dcmMsg.u.chanActivNack.causeVal = temp;
            printf("causeVal        :   0x%02x\n",
                                    msg->u.dcmMsg.u.chanActivNack.causeVal);
        }
        if (k == 7)
        {
	    printf("diagnostics     :   0x%02x\n",temp);	   
            for(diagcount=0;
                diagcount<msg->u.dcmMsg.u.chanActivNack.length;diagcount++)
            {
                msg->u.dcmMsg.u.chanActivNack.diagnostics[diagcount] = temp;
            }
        }
    }
    fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Physical Context Request elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/

ITS_INT
HandlePhyConReq(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadPhyConReq(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Physical Context Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("******************* ENCODED DATA ***********************\n");
        printf("Encoding Physical Context Request "
                "Success  ret :: %d\n\n", ret);
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("*********************** DECODED DATA *************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Physical Context Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Decoding Physical Context Request Success  ret :: %d\n", ret);
         //display buffer 
         printf("PARAMETER NAMES\t   VALUES\n");
         printf("---------------\t   ------\n");
         printf("msgDesc         :   0x%02x\n", 
                                             msg.genElemnts.msgDesc.msgGruop);
         printf("msgDesc(T)      :   0x%02x\n",
                                           msg.genElemnts.msgDesc.trasparent);
         printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
         printf("chanBits        :   0x%02x\n", 
                            msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
         printf("timeSlotNum     :   0x%02x\n", 
                          msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Physical Context Confirm information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                             
ITS_INT
ReadPhyConReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_params = 5;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: PHYSICAL CONTEXT REQUEST\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"PHY_CONTEXT_REQ START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),
                   "PHY_CONTEXT_REQ END\n")!=0)
            {
                if (line[0] == 'M')
                {
                    if (line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: PHYSICAL CONTEXT REQUEST\n");
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
             printf("msgDesc     :   0x%02x\n", 
                                         msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
             msg->genElemnts.msgDesc.trasparent = temp[k];
             printf("msgdesc(T)  :   0x%02x\n",
                                       msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
             msg->genElemnts.msgType = temp[k];
             printf("msgType     :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
             printf("chanBits    :   0x%02x\n",
                         msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
             printf("timeSlotNum  :   0x%02x\n",
                       msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }  
    }
    fclose(fp);
}  
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Physical Context Confirm information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/


ITS_INT
HandlePhyConConf(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem = 0;
    ret_elem = ReadPhyConConf(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Physical Context Confirm Control "
               "Failed  ret :: %d\n", ret);
         return ret;
    }
    else
    printf("******************** ENCODED DATA **************************\n");
    {
        printf("Encoding Physical Context Confirm "
                "Success  ret :: %d\n\n", ret);
        /* display buffer */
        for (i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("********************* DECODED DATA *************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Physical Context Confirm Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding Physical Context Confirm Success  ret :: %d\n", ret);
        /* display buffer */
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", 
                                          msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                        msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n",msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n",
                           msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                       msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("BSFPC           :   0x%02x\n",
                                msg.u.dcmMsg.u.phyContextConf.bsPower.FPC);
        printf("BSpowerLev      :   0x%02x\n",
                                msg.u.dcmMsg.u.phyContextConf.bsPower.powerLevel);
         
        printf("MSFPC           :   0x%02x\n",
                                msg.u.dcmMsg.u.phyContextConf.msPower.FPC);
        printf("MSpowerLev      :   0x%02x\n",
                                msg.u.dcmMsg.u.phyContextConf.msPower.powerLevel);
         
        printf("Timing Advance   :   0x%02x\n",
                                  msg.u.dcmMsg.u.phyContextConf.timingAdv);   
        if (ret_elem == 8)
        {
            printf("length      :   0x%02x\n", 
                             msg.u.dcmMsg.u.mspowerControl.msParams.length);
            printf("content     :   0x%02x\n",
                     msg.u.dcmMsg.u.phyContextConf.phyContext.content[0]); 
                  
        }
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Physical Context Confirm information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                                                                                                                  
ITS_INT
ReadPhyConConf(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_elem = 0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: PHYSICAL CONTEXT CONFIRM\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"PHY_CONTEXT_CONFIRM START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),
                    "PHY_CONTEXT_CONFIRM END\n")!=0)
            {
                if (line[0] == 'M' || line[0] == 'O')
                {
                    if (line[1] == '\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                if (line[0] == 'O' || line[1] == '\t' || line[2] == '0')
                {
                    no_elem = 8;
                    
                }
                else
                {
                    no_elem = 10;
                }
                printf("%s",line);
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
    if (kcount == no_elem)
    {
    }
    else
    {
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: MS Power Control\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    for(k=0;k<kcount;k++)
    {
        if (bufspace[k][0] != '0' && bufspace[k][1] != 'x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if (bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' ||  
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
            printf("msgDesc    :   0x%02x\n", 
                                          msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
            msg->genElemnts.msgDesc.trasparent = temp[k];
            printf("msgdesc(T) :   0x%02x\n",
                                        msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
            msg->genElemnts.msgType = temp[k];
            printf("msgType    :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits   :   0x%02x\n",
                          msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum:   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
        if (k == 5)
        {
            msg->u.dcmMsg.u.phyContextConf.bsPower.FPC = temp[k]; 
            printf("BSFPC      :   0x%02x\n",
                                msg->u.dcmMsg.u.phyContextConf.bsPower.FPC);
        }
        if (k == 6)
        {
             msg->u.dcmMsg.u.phyContextConf.bsPower.powerLevel = temp[k];
             printf("BS PowLev    :   0x%02x\n",
                        msg->u.dcmMsg.u.phyContextConf.bsPower.powerLevel);
        }
        if (k == 7)         
        {
            msg->u.dcmMsg.u.phyContextConf.msPower.FPC =temp[k]; 
            printf("MS-FPC     :   0x%02x\n", 
                               msg->u.dcmMsg.u.phyContextConf.msPower.FPC);   
        }
        if (k == 8)
        {     
            msg->u.dcmMsg.u.phyContextConf.msPower.powerLevel = temp[k]; 
            printf("MS PowLev  :   0x%02x\n", 
                          msg->u.dcmMsg.u.phyContextConf.msPower.powerLevel);   
        }  
        if (k == 9)
        {     
            msg->u.dcmMsg.u.phyContextConf.timingAdv = temp[k]; 
            printf("Timing Advance   :   0x%02x\n",
                                  msg->u.dcmMsg.u.phyContextConf.timingAdv);   
        }  
        if (k == 10)
        {     
            CLEAR_TM_DCM_PCC_OPTIONAL_BIT_MAP(msg);
            SET_TM_DCM_PCC_PHYSICAL_CONTEXT(msg);
            msg->u.dcmMsg.u.phyContextConf.phyContext.length =temp[k]; 
            printf("PhyCon length  :   0x%02x\n", 
                            msg->u.dcmMsg.u.phyContextConf.phyContext.length); 
        } 
        if (k == 11)
        {   
            printf("content        :   0x%02x\n",temp[k]);  
            for( i = 0;
                 i < msg->u.dcmMsg.u.phyContextConf.phyContext.length;i++)
            {
                msg->u.dcmMsg.u.phyContextConf.phyContext.content[i] = temp[k]; 
            }   
        }     
    }
    fclose(fp);
    return no_elem;
}  
/*implementation:internal
*
* PURPOSE:
*       Handles reading the PreProcess Configure information elements from the file,
*       encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/
 
ITS_INT
HandlePreProConf(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadPreProConf(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Preprocess Configure Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
     // display buffer 
        printf("****************** ENCODED DATA *************************\n");
        printf("Encoding Preprocess Configure  :: %d\n\n", ret);
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("********************** DECODED DATA ************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Preprocess Configure Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding Preprocess Configure Success  ret :: %d\n", ret);
         //display buffer 
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                         msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                       msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                          msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                        msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
	printf("procedure       :   0x%02x\n",
                                    msg.u.dcmMsg.u.preprocConfig.procedure);    	
        printf("preproConf leng :   0x%02x\n", 
                                       msg.u.dcmMsg.u.preprocConfig.length);
	printf("procparams      :   0x%02x\n", 
                                msg.u.dcmMsg.u.preprocConfig.processParam[0]);
    }
    return ITS_SUCCESS;
}
 /*implementation:internal
*
* PURPOSE:
*       Reading the PreProcessed Configure information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                              
ITS_INT
ReadPreProConf(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_params = 6;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: PREPROCESS CONFIGURE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"PREPROCESS_CONF START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),
                              "PREPROCESS_CONF END\n") != 0)
            {
                if (line[0] == 'M')
                {
                    if (line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: Preprocess Configure\n");
    printf("                                \n");
    printf("PARAMETER NAMES\t   VALUES      \n");
    printf("---------------\t   ------------\n");
    for (k=0; k<kcount; k++)
    {
        if (bufspace[k][0] != '0' && bufspace[k][1] != 'x')
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
            printf("msgDesc     :   0x%02x\n", 
                                        msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
            msg->genElemnts.msgDesc.trasparent = temp[k];
            printf("msgdesc(T)  :   0x%02x\n",
                                       msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
            msg->genElemnts.msgType = temp[k];
            printf("msgType     :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits    :   0x%02x\n",
                      msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
             printf("timeSlotNum :   0x%02x\n",
                      msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
        if (k == 5)
        {
	    msg->u.dcmMsg.u.preprocConfig.length = temp[k];
            printf("Prepro length:   0x%02x\n",
                                     msg->u.dcmMsg.u.preprocConfig.length);
        }
        if (k == 6)
        {    	     
            printf("process params  :   0x%02x\n",temp[k]);
            for(i=0; i<msg->u.dcmMsg.u.preprocConfig.length; i++)
            {
	        msg->u.dcmMsg.u.preprocConfig.processParam[i]=temp[k];
            }
        }
	if (k == 7)
        {
	    msg->u.dcmMsg.u.preprocConfig.procedure = temp[k];
            printf("procedure  :   0x%02x\n",
                                 msg->u.dcmMsg.u.preprocConfig.procedure);
        }
    }
    fclose(fp);
}   
/*implementation:internal
*
* PURPOSE:
*       Handles reading the PreProcess Measurement Result information elements 
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
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/
ITS_INT
HandlePreProMeasRes(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadPreProMeasRes(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Preprocess Measurement result Failed"
                "ret :: %d\n", ret);
        return ret;
    }
    else
    {
     // display buffer 
        printf("******************** ENCODED DATA **********************\n");
        printf("Encoding Preprocess Measurement result  :: %d\n\n", ret);
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("*********************** DECODED DATA ************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Preprocess Measurement Result "
                "Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding Preprocess Measurement Result "
                "Success  ret :: %d\n", ret);
         //display buffer 
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                         msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                       msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                       msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n",
                      msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
	printf("MeasRes Length  :   0x%02x\n",
                                     msg.u.dcmMsg.u.prepocMeasRes.length);
        printf("processMeas     :   0x%02x\n",
                             msg.u.dcmMsg.u.prepocMeasRes.processMeas[0]);
    }
    return ITS_SUCCESS;
}
 /*implementation:internal
*
* PURPOSE:
*       Reading the Preprocessed Measurement result information elements 
*       from the file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                              
ITS_INT
ReadPreProMeasRes(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0,icount, k = 0, kcount;
    int no_params = 6;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: PREPROCESS MEASUREMENT RESULT\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"PREPROCESS_MEASURE START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),
                                "PREPROCESS_MEASURE END\n")!=0)
            {
                if (line[0] == 'M')
                {
                    if (line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: PREPROCESS MEASUREMENT RESULT\n");
    printf("                                \n");
    printf("PARAMETER NAMES\t   VALUES      \n");
    printf("---------------\t   ------------\n");
    for(k=0; k<kcount; k++)
    {
        if (bufspace[k][0] != '0' && bufspace[k][1] != 'x')
        {
            printf("The input is not in correct format\n");
            exit(1);
        }
        if (bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f' || 
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
            printf("msgDesc         :   0x%02x\n", 
                                          msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
            msg->genElemnts.msgDesc.trasparent = temp[k];
            printf("msgdesc(T)      :   0x%02x\n",
                                         msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
            msg->genElemnts.msgType = temp[k];
            printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits        :   0x%02x\n",
                       msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k == 4)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum     :   0x%02x\n",
                       msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
        if (k == 5)
        {
	     msg->u.dcmMsg.u.prepocMeasRes.length = temp[k];
             printf("MeasRes Length  :   0x%02x\n",
                                     msg->u.dcmMsg.u.prepocMeasRes.length);
        }
        if (k == 6)
        {    	     
            printf("process meas     :   0x%02x\n",temp[k]);
            for(i = 0 ; i < msg->u.dcmMsg.u.prepocMeasRes.length ; i++)
            {
                msg->u.dcmMsg.u.prepocMeasRes.processMeas[i] = temp[k];
            }
        }
   }
   fclose(fp);
}   
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Handover Detection  information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
HandleHandDet(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int params = 0;
    params = ReadHandDet(&msg,fp);
    printf("The no of params is %d\n",params);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Handover Detection Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("**********************ENCODED DATA **********************\n");
        printf("Encoding Handover Detection Success :: %d\n\n", ret);
        printEncComDcmm(buffer,len);  
    }
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Handover Detection Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("******************** DECODED DATA ***********************\n");
    	printf("Decoding Handover Detection Success  ret :: %d\n", ret);
        printDecComDcmm(msg,params);  
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the HandOver detection information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                            
ITS_INT
ReadHandDet(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_params;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: HANDOVER DETECTION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"HNDOVR_DET START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"HNDOVR_DET END\n") != 0)
            {
                if (line[0] == 'M' || line[0] == 'O')
                {
                    if (line[1] == '\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
	        if (line[0] == 'O' && line[1] == '\t' && line[2] == '0')
                {
	            no_params = 6;
                }
                else
	        {
	            no_params = 5;
                }        
                printf("%s",line);
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
    printf("no_params count is %d\n",no_params);
    if (kcount == no_params)
    {
    }
    else
    {
	printf("Information element missing\n");
	exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: HANDOVER DETECTION\n");
    printf("                                \n");
    printf("PARAMETER NAMES\t   VALUES      \n");
    printf("---------------\t   ------------\n");
    for (k=0; k<kcount; k++)
    {
        if (bufspace[k][0] != '0' && bufspace[k][1] != 'x')
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
            printf("msgDesc    :   0x%02x\n", 
                                       msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
            msg->genElemnts.msgDesc.trasparent=temp[k];
            printf("msgdesc(T) :   0x%02x\n",
                                       msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
            msg->genElemnts.msgType = temp[k];
            printf("msgType    :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits   :   0x%02x\n",
                       msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum:   0x%02x\n",
                      msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
        if (k == 5)
        {    
            CLEAR_TM_DCM_HD_OPTIONAL_BIT_MAP(msg);
            SET_TM_DCM_HD_ACCESS_DELAY(msg);
	    msg->u.dcmMsg.u.handoDet.accessDelay = temp[k];
            printf("Access Delay   :   0x%02x\n",
                                     msg->u.dcmMsg.u.handoDet.accessDelay);
        }
    }   
    fclose(fp);
    return no_params;
}   
/*implementation:internal
*
* PURPOSE:
*       Handles reading the RF Channel Release information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/

ITS_INT
HandleRFChanRel(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadRFChanRel(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding RF Channel Release Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    printf("********************* ENCODED DATA *************************\n");
    {
        printf("Encoding RF Channel Release Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("********************** DECODED DATA *************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding RF Channel Release Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding RF Channel Release Success  ret :: %d\n", ret);
        /* display buffer */
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", 
                                          msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n", 
                                         msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                          msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                        msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the RF Channel Release information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                                                                                                                     
ITS_INT
ReadRFChanRel(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_params = 5;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: RF CHANNEL RELEASE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"RF_CHAN_REL START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"RF_CHAN_REL END\n") != 0)
            {
                if (line[0] == 'M')
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
                printf("%s",line);
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
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: RF CHANNEL RELEASE\n");
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
            printf("msgDesc     :   0x%02x\n",
                                       msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
            msg->genElemnts.msgDesc.trasparent = temp[k];
            printf("msgdesc(T)  :   0x%02x\n",
                                      msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
            msg->genElemnts.msgType = temp[k];
            printf("msgType     :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits    :   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }     
        if (k==4)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum :   0x%02x\n",
                       msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
    }
    fclose(fp);
}  
/*implementation:internal
*
* PURPOSE:
*       Handles reading the RF Channel Release information elements from the file,
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
*/
ITS_INT
HandleMSPowctrl(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem = 0;
    ret_elem = ReadMSPowctrl(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding MS Power Control Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    printf("******************** ENCODED DATA ************************\n");
    {
        printf("Encoding MS Power Control Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("************************ DECODED DATA ***********************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding MS Power Control Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding MS Power Control Success  ret :: %d\n", ret);
        /* display buffer */
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                            msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                          msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n",
                           msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                         msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("FPC     :   0x%02x\n",
                                   msg.u.dcmMsg.u.mspowerControl.msPower.FPC);
        printf("timeSlotNum     :   0x%02x\n", 
                            msg.u.dcmMsg.u.mspowerControl.msPower.powerLevel);
        if (ret_elem == 9)
        {
            printf("length          :   0x%02x\n", 
                              msg.u.dcmMsg.u.mspowerControl.msParams.length);
            printf("content         :   0x%02x\n",
                     msg.u.dcmMsg.u.mspowerControl.msParams.powerControl[0]);
        }
    }
    return ITS_SUCCESS;
}
 /*implementation:internal
*
* PURPOSE:
*       Reading the RF Channel Release information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/                                                                                                                    
ITS_INT
ReadMSPowctrl(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i = 0, icount, k = 0, kcount;
    int no_elem = 0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    printf("                        \n");
    printf("Message Name: MS Power Control\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"MS_POW_CTRL START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"MS_POW_CTRL END\n") != 0)
            {
                if (line[0] == 'M' || line[0] == 'O')
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
                if (line[0] == 'O' || line[1] == '\t' || line[2] == '0')
                {
                    no_elem = 9;
                }
                else
                {
                    no_elem = 7;
                }
                printf("%s",line);
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
    if (kcount == no_elem)
    {
    }
    else
    {
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("MESSAGE NAME: MS Power Control\n");
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
            printf("msgDesc         :   0x%02x\n",
                                       msg->genElemnts.msgDesc.msgGruop);
        }
        if (k == 1)
        {
            msg->genElemnts.msgDesc.trasparent = temp[k];
            printf("msgdesc(T)      :   0x%02x\n",
                                      msg->genElemnts.msgDesc.trasparent);
        }
        if (k == 2)
        {
            msg->genElemnts.msgType = temp[k];
            printf("msgType         :   0x%02x\n",msg->genElemnts.msgType);
        }
        if (k == 3)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits = temp[k];
            printf("chanBits        :   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
        if (k == 4)
        {
            msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum = temp[k];
            printf("timeSlotNum     :   0x%02x\n",
                     msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
        if (k == 5)
        {
            msg->u.dcmMsg.u.mspowerControl.msPower.FPC = temp[k];
            printf("timeSlotNum     :   0x%02x\n",
                               msg->u.dcmMsg.u.mspowerControl.msPower.FPC);
        }
        if (k == 6)
        {
            msg->u.dcmMsg.u.mspowerControl.msPower.powerLevel = temp[k];
            printf("timeSlotNum     :   0x%02x\n",
                        msg->u.dcmMsg.u.mspowerControl.msPower.powerLevel);
        }
        if (k == 7)         
        {
            CLEAR_TM_DCM_MPC_OPTIONAL_BIT_MAP(msg);
            SET_TM_DCM_MPC_MS_POWER_PARAMS(msg);
            printf("length     :   0x%02x\n",temp[k]);
            msg->u.dcmMsg.u.mspowerControl.msParams.length = temp[k];
        }
        if (k == 8)         
        {
            printf("timeSlotNum     :   0x%02x\n",temp[k]);
            for(i=0;i< msg->u.dcmMsg.u.mspowerControl.msParams.length;i++)
            {
                msg->u.dcmMsg.u.mspowerControl.msParams.powerControl[i] = temp[k];
            }
        }   
    }
    fclose(fp);
    return no_elem;
}  
ITS_INT
HandleBSPowctrl(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem = 0;
    ret_elem = ReadBSPowctrl(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Request Failed  ret :: %d\n", ret);
         return ret;
    }
    else
                                                                                                                             
    printf("********************************** ENCODED DATA **********************************\n");
    {
        printf("Encoding BS Power ctrl Success  ret :: %d\n\n", ret);
        /* display buffer */
                                                                                                                             
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("********************************** DECODED DATA **********************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding BS Power ctrl Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Decoding BS Power ctrl Success  ret :: %d\n", ret);
        /* display buffer */
         printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("FPC     :   0x%02x\n", msg.u.dcmMsg.u.bspowerControl.bsPower.FPC);
        printf("timeSlotNum     :   0x%02x\n", msg.u.dcmMsg.u.bspowerControl.bsPower.powerLevel);
        if (ret_elem == 9)
        {
            printf("length          :   0x%02x\n", msg.u.dcmMsg.u.bspowerControl.bsParams.length);
            printf("content         :   0x%02x\n", msg.u.dcmMsg.u.bspowerControl.bsParams.powerControl[0]);
        }
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the BS Power Control information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
ITS_INT
ReadBSPowctrl(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_elem=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];

    printf("                        \n");
    printf("Message Name: BS POWER CONTROL\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"BS_POW_CTRL START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"BS_POW_CTRL END\n")!=0)
            {
                if(line[0]=='M' || line[0]=='O')
                {
                    if(line[1]=='\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                if (line[0]== 'O' || line[1]== '\t' || line[2]=='0')
               {
                    no_elem = 9;
                    
               }
                                                                                                                             
               else
               {
                   no_elem = 7;
               }
                printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    if (kcount==no_elem)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: BS POWER CONTROL\n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
                                                                                                                                     
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
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
         if (k==5)
        {
             msg->u.dcmMsg.u.bspowerControl.bsPower.FPC=temp[k];
             printf("timeSlotNum     :   0x%02x\n",msg->u.dcmMsg.u.bspowerControl.bsPower.FPC);
        }
                                                                                                                    
         if (k==6)
        {
             msg->u.dcmMsg.u.bspowerControl.bsPower.powerLevel=temp[k];
             printf("timeSlotNum     :   0x%02x\n",msg->u.dcmMsg.u.bspowerControl.bsPower.powerLevel);
        }
         if (k==7)         
         {
             CLEAR_TM_DCM_MPC_OPTIONAL_BIT_MAP(msg);
             SET_TM_DCM_MPC_MS_POWER_PARAMS(msg);
             printf("length     :   0x%02x\n",temp[k]);
             msg->u.dcmMsg.u.bspowerControl.bsParams.length = temp[k];

        }
        
          if (k==9)         
         {
             printf("powerContrl    :   0x%02x\n",temp[k]);
             for(i=0;i< msg->u.dcmMsg.u.bspowerControl.bsParams.length;i++)
             {
                msg->u.dcmMsg.u.bspowerControl.bsParams.powerControl[i]=temp[k];
             }

        }                
                                                                                                                     	
      
    }
    
	fclose(fp);
        return no_elem;
}  
/*implementation:internal
*
* PURPOSE:
*       Handles reading the RF Channel Release Ack information elements from the file,
*       encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
HandleRFChanRelAck(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadRFChanRel(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("************************** ENCODED DATA *****************************\n");
    {
        printf("Encoding RF Channel Release Acknowledge Success  ret :: %d\n\n", ret);
        /* display buffer */
                                                                                                                             
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("************************* DECODED DATA *******************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("RF Channel Release Acknowledge Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("RF Channel Release Acknowledge Success  ret :: %d\n", ret);
        /* display buffer */
         printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                                msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                              msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
    
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the RF Channel Release Ack information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
                                                                                                                             
                                                                                                                     
ITS_INT
ReadRFChanRelAck(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_params=6;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];

    printf("                        \n");
    printf("Message Name: RF CHANNEL RELEASE ACKNOWLEDGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"RF_CHAN_REL_ACK START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"RF_CHAN_REL_ACK END\n")!=0)
            {
                if(line[0]=='M')
                {
                    if(line[1]=='\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    if (kcount==no_params)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: RF CHANNEL RELEASE ACKNOWLEDGE\n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
                                                                                                                                     l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
                                                                                                                             
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
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",
                                   msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                                msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
                                                                                                                          
    }
    	
     fclose(fp);
} 

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Sacch Information elements from the file,encoding 
        and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/
                                                                                                                             
ITS_INT
HandleSacchInfoMod(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem = 0;
    ret_elem=ReadSacchInfoMod(&msg,fp);
    printf("returned elem is %d\n",ret_elem);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding SACCH Info Modify failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("***************************** ENCODED DATA  *******************************\n");
    {
        printf("Encoding SACCH Info Modify Success  ret :: %d\n\n", ret);
        /* display buffer */
                                                                                                                             
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                           
    printf("***************************** DECODED DATA ******************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("SACCH Info Modify Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Sacch Info Modify Success  ret :: %d\n", ret);
        /* display buffer */
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", 
                                msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", 
                              msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("SysInfo type    :   0x%02x\n", 
                                         msg.u.dcmMsg.u.sacchInfoMod.sysInfoType);
        if(ret_elem == 8 || ret_elem == 9)
        {
	    printf("Lengthiden  :   0x%02x\n", 
                                    msg.u.dcmMsg.u.sacchInfoMod.l3Info.lengthInd);
	    printf("LLSDU       :   0x%02x\n", 
                                     msg.u.dcmMsg.u.sacchInfoMod.l3Info.LLSDU[0]);
        }
        
        if(ret_elem==7 || ret_elem==9)
        {
            printf("StartingTime:   0x%02x\n", msg.u.dcmMsg.u.sacchInfoMod.startingTime);
        }
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Sacch Information Modification request information elements 
*        from the file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/

ITS_INT
ReadSacchInfoMod(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int mand_elem=6;
    int tot_elem=0;
    int opt_elem[2]= { 2,1 };
    int opt_ocur_elem[2] = {0,0};
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    

    printf("                        \n");
    printf("Message Name: SACCH INFO MODIFY\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    CLEAR_TM_DCM_SIM_OPTIONAL_BIT_MAP(msg);
    //SET_TM_DCM_SIM_L3_INFO(msg);
    //SET_TM_DCM_SIM_STARTING_TIME(msg); 
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"SACCH_INFO_MOD START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"SACCH_INFO_MOD END\n")!=0)
            {
                if(line[0]=='M' || line[0]=='O')
                {
                    if(line[1]=='\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                
               if (line[0]== 'O' && line[1]== '\t' && line[2]=='0' && strstr(line,"opt1"))
               {
                    opt_ocur_elem[0]=opt_elem[0];
                     //opt_elem++;
                    //tot_elem = opt_elem + mand_elem;                 
               }
		
               /*else
               {
                   tot_elem = mand_elem;
               }*/
               
               if (line[0]== 'O' && line[1]== '\t' && line[2]=='0' && strstr(line,"opt2"))
               {
                   opt_ocur_elem[1]=opt_elem[1];
               }
               printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
                         strcpy(*(bufspace+k),tokenspace);
                         k++;
                         tokenspace=(char *)strtok(NULL," ");
                    }
                }
            }
           break;
        }
    }
    tot_elem =  mand_elem + opt_ocur_elem[0] + opt_ocur_elem[1];
    printf("                        \n");
    printf("Reading from file ends...\n");
    printf("                        \n");
    icount=i;
    kcount=k;
    printf("total elem is %d\n",tot_elem);
    printf("kcount is %d\n",kcount);
    if (kcount==tot_elem)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
    }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: SACCH INFO MODIFY\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
                                                                                                                             
                                                                                                                           
        for(k=0;k<kcount;k++)
        {
	   
             l[k]=strtol(bufspace[k],NULL,16);
             temp[k]=(unsigned char)l[k];
                                                                                                                                         if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
            {
                printf("The input is not in correct format\n");
                exit(1);
            }
                                                                                                                             
           if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
          {
                                                                                                                             
          }
          else
          {
              printf("input not in correct format\n");
          }
                                                                                                                             
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
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",
                              msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {  
                                                                                                                                          msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }    
        
        if (k==5)
        {                                                                                                                                
             msg->u.dcmMsg.u.sacchInfoMod.sysInfoType=temp[k];
             printf("SysInfo type    :   0x%02x\n", 
                                        msg->u.dcmMsg.u.sacchInfoMod.sysInfoType);
        }    
        
	if (k==6)
        {
           
           SET_TM_DCM_SIM_L3_INFO(msg);
            msg->u.dcmMsg.u.sacchInfoMod.l3Info.lengthInd=temp[k];
           printf("Length identifier    :   0x%02x\n", 
                                 msg->u.dcmMsg.u.sacchInfoMod.l3Info.lengthInd);
        }
	    
        if (k==7)
        {  
	
             printf("LLSDU           :   0x%02x\n", temp[k]);
             for(i=0;i<msg->u.dcmMsg.u.sacchInfoMod.l3Info.lengthInd;i++)
             {
	         msg->u.dcmMsg.u.sacchInfoMod.l3Info.LLSDU[i]=temp[k];
             }
	}    
        if (k==8)
        {     
              
            SET_TM_DCM_SIM_STARTING_TIME(msg);                                                                                                                           
             msg->u.dcmMsg.u.sacchInfoMod.startingTime=temp[k];
             printf("Starting time    :   0x%02x\n", 
                                     msg->u.dcmMsg.u.sacchInfoMod.startingTime);
        }    
    }

   	fclose(fp);
         
        return tot_elem; 
}
/*implementation:internal
* PURPOSE:
*       Handles reading the Talker Detection information elements from
*      the file,encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*/
 
ITS_INT
HandleTalkDet(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem = 0;
    ret_elem = ReadTalkDet(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Talker Detection Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("************************* ENCODED DATA ******************************\n");
        printf("Encoding Talker Detection  :: %d\n\n", ret);      
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("***************************** DECODED DATA ******************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Talker Detection Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Decoding Talker Detection Success  ret :: %d\n", ret);
         printf("PARAMETER NAMES\t   VALUES\n");
         printf("---------------\t   ------\n");
         printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
         printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
         printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
         printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
         printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
         if(ret_elem==6)
         {
             printf("Access Delay    :   0x%02x\n",  msg.u.dcmMsg.u.handoDet.accessDelay);
         }
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Talker Detection information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
                                                                                                                             
ITS_INT
ReadTalkDet(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_elem;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];

    printf("                        \n");
    printf("Message Name: TALKER DETECTION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"TLK_DET START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"TLK_DET END\n")!=0)
            {
                if(line[0]=='M' || line[0]=='O')
                {
                    if(line[1]=='\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
	     
	       if (line[0]=='O' && line[1]=='\t' && line[2]=='0')
               {
	           no_elem=6;
               }
               else
	       {
	           no_elem=5;
               }        
               printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    printf("kcount is %d\n",kcount);
    printf("no_params count is %d\n",no_elem);
    if (kcount==no_elem)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
	exit(1);
    }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: TALKER DETECTION\n");
    printf("                                \n");
    printf("PARAMETER NAMES\t   VALUES      \n");
    printf("---------------\t   ------------\n");
                                                                                                                             
                                                                                                                           
    for(k=0;k<kcount;k++)
    {
                                                                                                                             
       if(bufspace[k][0]!='0' && bufspace[k][1]!='x')
       {
            printf("The input is not in correct format\n");
            exit(1);
        }
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
                                                                                                                             
	l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
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
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",
                                  msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                                 msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
	
        if (k==5)
        {    
             CLEAR_TM_DCM_HD_OPTIONAL_BIT_MAP(msg);
             SET_TM_DCM_HD_ACCESS_DELAY(msg);
	     msg->u.dcmMsg.u.handoDet.accessDelay=temp[k];
             printf("Access Delay   :   0x%02x\n",msg->u.dcmMsg.u.handoDet.accessDelay);
        }
                                                                                                                  	
   }   
	fclose(fp);
	return no_elem;
}
   
/*implementation:internal
* PURPOSE:
*       Handles reading the Handle Listener Detection information elements from
*      the file,encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*/
ITS_INT
HandleListDet(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem = 0;
    ret_elem = ReadListDet(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Listener Detection Failed  ret :: %d\n", ret);
         return ret;
    }
    else
    {
        printf("************************ ENCODED DATA ******************************\n");
        printf("Encoding Listener Detection Success  :: %d\n\n", ret);       
        //printEncComDcmm(buffer,len);  
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("**************************** DECODED DATA *******************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Listener Detection Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Decoding Listener Detection Success  ret :: %d\n", ret);
         printf("PARAMETER NAMES\t   VALUES\n");
         printf("---------------\t   ------\n");
         printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
         printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
         printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
         printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
         printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
         if(ret_elem==6)
         {
             printf("Access Delay    :   0x%02x\n",  msg.u.dcmMsg.u.handoDet.accessDelay);
         }
         
        // printDecComDcmm(msg,ret_elem); 
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Listener Detection information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
                                                                                                                             
                               
ITS_INT
ReadListDet(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_elem;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];

    printf("                        \n");
    printf("Message Name: LISTENER DETECTION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"TLK_DET START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"TLK_DET END\n")!=0)
            {
                if(line[0]=='M' || line[0]=='O')
                {
                    if(line[1]=='\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
	     
	       if (line[0]=='O' && line[1]=='\t' && line[2]=='0')
               {
	           no_elem=6;
               }
               else
	       {
	           no_elem=5;
               }        
               printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    printf("kcount is %d\n",kcount);
    printf("no_params count is %d\n",no_elem);
    if (kcount==no_elem)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
	exit(1);
    }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: LISTENER DETECTION\n");
    printf("                                \n");
    printf("PARAMETER NAMES\t   VALUES      \n");
    printf("---------------\t   ------------\n");
    for(k=0;k<kcount;k++)
    {
           
            l[k]=strtol(bufspace[k],NULL,16);
            temp[k]=(unsigned char)l[k];
	if (k==0)
        {

             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc      :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
                                                                                                                             
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)  :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
                                                                                                                             
        if (k==2)
        {
                                                                                                                             
             msg->genElemnts.msgType=temp[k];
             printf("msgType     :   0x%02x\n",msg->genElemnts.msgType);
        }
                                                                                                                             
        if (k==3)
        {
                                                                                                                             
        msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
        printf("chanBits        :   0x%02x\n",
                             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum:  0x%02x\n",
                         msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
        if(k==5)
        {    
             CLEAR_TM_DCM_HD_OPTIONAL_BIT_MAP(msg);
             SET_TM_DCM_HD_ACCESS_DELAY(msg);
	     msg->u.dcmMsg.u.handoDet.accessDelay=temp[k];
             printf("Access Delay:   0x%02x\n",
                                      msg->u.dcmMsg.u.handoDet.accessDelay);
        }
                                                                                                                  	
   }   
	fclose(fp);
	return no_elem;
}

/*implementation:internal
* PURPOSE:
*       Handles reading the Round Trip Delay Repor t information elements from 
*      the file,encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*/
                                                                                                                             
ITS_INT
HandleRndTrip(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int diagcount;
    ReadRndTrip(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Round trip Report Failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("*************************** ENCODED DATA ******************************\n");
    {
        printf("Encoding Round Trip Delay success  ret :: %d\n\n", ret);
        /* display buffer */
                                                                                                                             
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("*************************** DECODED DATA *******************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Round Trip Delay failed   ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Encoding Round Trip delay Success  ret :: %d\n", ret);
        /* display buffer */
         printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("RTD             :   0x%02x\n", msg.u.dcmMsg.u.rtdRep.RTD);
        printf("Delay             :   0x%02x\n", msg.u.dcmMsg.u.rtdRep.delay);
                                                                                                                                                                                                                                                              }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Round Trip Report information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
                                                                                                                             
                                                                                                                     
ITS_INT
ReadRndTrip (ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_params=6;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int diagcount;

    printf("                        \n");
    printf("Message Name: ROUND TRIP DELAY REPORT\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"RNDTRIP_DEL_REP START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"RNDTRIP_DEL_REP END\n")!=0)
            {
                if(line[0]=='M')
                {
                    if(line[1]=='\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    if (kcount==no_params)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: ROUND TRIP DELAY REPORT \n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
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
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",
                               msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                            msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
                                                                                                                             
	if (k==5)
        {
              msg->u.dcmMsg.u.rtdRep.RTD = temp[k];
              printf("RTD        :   0x%02x\n",msg->u.dcmMsg.u.rtdRep.RTD);      
        }
                                                                                                                             
	if (k==6)
        {
                msg->u.dcmMsg.u.rtdRep.delay = temp[k];
		printf("delay        :   0x%02x\n",msg->u.dcmMsg.u.rtdRep.delay);
        }
        
      }
    
    
	fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Pre Handover Notification information elements 
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
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/
                                                                                                                             
ITS_INT
HandlePreHndNot(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int diagcount;
    ReadPreHndNot(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding PreHandover Notification Failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("***************************** ENCODED DATA ******************************\n");
    {
        printf("Encoding PreHandover Notification success  ret :: %d\n\n", ret);
        /* display buffer */
                                                                                                                             
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("***************************** DECODED DATA ******************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding PreHandover Notification failed   ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Encoding PreHandover Notification Success  ret :: %d\n", ret);
        /* display buffer */
         printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc    :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T) :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType    :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits   :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum:   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("TFO        :  0x%02x\n", msg.u.dcmMsg.u.preHandoNotif.mrControl.TFO);  
        printf("PRE        :  0x%02x\n", msg.u.dcmMsg.u.preHandoNotif.mrControl.PRE);
        printf("RAE        :  0x%02x\n", msg.u.dcmMsg.u.preHandoNotif.mrControl.RAE);
        printf("length     :  0x%02x\n", msg.u.dcmMsg.u.preHandoNotif.config.length);
        printf("codecType  :  0x%02x\n", msg.u.dcmMsg.u.preHandoNotif.config.codecType);
        printf("ICM        :  0x%02x\n", msg.u.dcmMsg.u.preHandoNotif.config.ICM);
        printf("codecSet   :  0x%02x\n", msg.u.dcmMsg.u.preHandoNotif.config.codecSet);
}
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Deactivate Sacch information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
                                                                                                                     
ITS_INT
ReadPreHndNot (ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_params=6;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int diagcount;

    printf("                        \n");
    printf("Message Name: PRE HANDOVER NOTIFICATION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"PREHNDOVR_NOT START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"PREHNDOVR_NOT END\n")!=0)
            {
                if(line[0]=='M')
                {
                    if(line[1]=='\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    if (kcount==no_params)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: PRE HANDOVER NOTIFICATION \n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
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
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",
                                     msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum :   0x%02x\n", 
                                  msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
                                                                                                                             
	if (k==5)
        {
            msg->u.dcmMsg.u.preHandoNotif.mrControl.TFO =  temp[k];     
            printf("TFO         :  0x%02x\n", msg->u.dcmMsg.u.preHandoNotif.mrControl.TFO);
        }
                                                                                                                             
	if (k==6)
        {
            msg->u.dcmMsg.u.preHandoNotif.mrControl.PRE = temp[k];
            printf("PRE         :  0x%02x\n", msg->u.dcmMsg.u.preHandoNotif.mrControl.PRE);
        }
	if (k==7)
        {
            msg->u.dcmMsg.u.preHandoNotif.mrControl.RAE = temp[k];
            printf("RAE         :  0x%02x\n", msg->u.dcmMsg.u.preHandoNotif.mrControl.RAE);
        }
	if (k==8)
        {
            msg->u.dcmMsg.u.preHandoNotif.config.length =temp[k];
            printf("length      :  0x%02x\n", msg->u.dcmMsg.u.preHandoNotif.config.length);
        }
	if (k==9)
        {
            msg->u.dcmMsg.u.preHandoNotif.config.codecType =temp[k];
            printf("codecType   :  0x%02x\n", msg->u.dcmMsg.u.preHandoNotif.config.codecType);
        }
	if (k==10)
        {
             msg->u.dcmMsg.u.preHandoNotif.config.ICM = temp[k];
             printf("ICM        :  0x%02x\n", msg->u.dcmMsg.u.preHandoNotif.config.ICM);
        }
	if (k==11)
        {
             msg->u.dcmMsg.u.preHandoNotif.config.codecSet = temp[k];
             printf("codecSet   :  0x%02x\n", msg->u.dcmMsg.u.preHandoNotif.config.codecSet);
        }
        
      }
    
    
	fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Multirate Codec Modfn Req information elements from the file,
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
*/

   
ITS_INT
HandleMCodecModReq(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem = 0;
    ret_elem = ReadMCodecModReq(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Multirate Codec Modification request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("************************* ENCODED DATA ******************************\n");
        printf("Encoding Multirate Codec Modification Request Success  :: %d\n\n", ret);       
        printEncComDcmm(buffer,len);  
    }
                                                                                                                             
    printf("***************************** DECODED DATA*********************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Multirate Codec Modification Request  Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Decoding Multirate Codec Modification Request Success  ret :: %d\n", ret);
         printf("PARAMETER NAMES\t   VALUES\n");
         printDecComDcmm(msg,ret_elem); 
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Multirate Codec Mod Req information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
                               
ITS_INT
ReadMCodecModReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_elem;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];

    printf("                        \n");
    printf("Message Name: MULTIRATE CODEC MODIFICATION REQUEST\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"MUL_CODEC_MODREQ START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"MUL_CODEC_MODREQ END\n")!=0)
            {
                if(line[0]=='M' || line[0]=='O')
                {
                    if(line[1]=='\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
	     
	       if (line[0]=='O' && line[1]=='\t' && line[2]=='0')
               {
	           no_elem=6;
               }
               else
	       {
	           no_elem=5;
               }        
               printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    printf("kcount is %d\n",kcount);
    printf("no_params count is %d\n",no_elem);
    if (kcount==no_elem)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
	exit(1);
    }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: MULTIRATE MODIFICATION REQUEST\n");
    printf("                                \n");
    printf("PARAMETER NAMES\t   VALUES      \n");
    printf("---------------\t   ------------\n");
    for(k=0;k<kcount;k++)
    {
           
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
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
                                                                                                                             
        msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
        printf("chanBits        :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
        if(k==5)
        {    
             CLEAR_TM_DCM_HD_OPTIONAL_BIT_MAP(msg);
             SET_TM_DCM_HD_ACCESS_DELAY(msg);
	     msg->u.dcmMsg.u.handoDet.accessDelay=temp[k];
             printf("Access Delay   :   0x%02x\n",msg->u.dcmMsg.u.handoDet.accessDelay);
        }
                                                                                                                  	
   }   
	fclose(fp);
	return no_elem;
}   

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Multi Codec Modfn Ack information elements from the file,
*       encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/
 
ITS_INT
HandleMCodecModAck(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem = 0;
    ret_elem = ReadMCodecModReq(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Multirate Codec Modification Acknowledge Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("****************************** ENCODED DATA **********************************\n");
        printf("Encoding Multirate Codec Modification Acknowledge Success  :: %d\n\n", ret);       
        printEncComDcmm(buffer,len);  
    }
                                                                                                                             
    printf("********************************** DECODED DATA **********************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Multirate Codec Modification Acknowledge  Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Decoding Multirate Codec Modification Acknowledge Success  ret :: %d\n", ret);
         printf("PARAMETER NAMES\t   VALUES\n");
         printDecComDcmm(msg,ret_elem); 
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Multirate Codec Mod Ack information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
                               
ITS_INT
ReadMCodecModAck(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_elem;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];

    printf("                        \n");
    printf("Message Name: MULTIRATE CODEC MODIFICATION ACKNOWLEDGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"MUL_CODEC_MODREQ START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"MUL_CODEC_MODREQ END\n")!=0)
            {
                if(line[0]=='M' || line[0]=='O')
                {
                    if(line[1]=='\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
	     
	       if (line[0]=='O' && line[1]=='\t' && line[2]=='0')
               {
	           no_elem=6;
               }
               else
	       {
	           no_elem=5;
               }        
               printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    printf("kcount is %d\n",kcount);
    printf("no_params count is %d\n",no_elem);
    if (kcount==no_elem)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
	exit(1);
    }

    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: MULTIRATE MODIFICATION ACKNOWLEDGE\n");
    printf("                                \n");
    printf("PARAMETER NAMES\t   VALUES      \n");
    printf("---------------\t   ------------\n");
    for(k=0;k<kcount;k++)
    {
           
            l[k]=strtol(bufspace[k],NULL,16);
            temp[k]=(unsigned char)l[k];
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
                                                                                                                             
        msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
        printf("chanBits        :   0x%02x\n",
                                    msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                                  msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
        if(k==5)
        {    
             CLEAR_TM_DCM_HD_OPTIONAL_BIT_MAP(msg);
             SET_TM_DCM_HD_ACCESS_DELAY(msg);
	     msg->u.dcmMsg.u.handoDet.accessDelay=temp[k];
             printf("Access Delay   :   0x%02x\n",msg->u.dcmMsg.u.handoDet.accessDelay);
        }
                                                                                                                  	
   }   
	fclose(fp);
	return no_elem;
}  
/*implementation:internal
*
* PURPOSE:
*       Handles reading the data request information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/
  
ITS_INT
HandleMCodecModNack(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int diagcount;
    ReadConFLInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("************************* ENCODED DATA **************************\n");
    {
        printf("Encoding Multirate Codec Modification Neg Ack success  ret :: %d\n\n", ret);
        /* display buffer */
                                                                                                                             
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("**************************** DECODED DATA ***************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Multirate Codec Modification Neg Ack failed   ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Encoding Multirate Codec Modification Neg Ack Success  ret :: %d\n", ret);
        /* display buffer */
         printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("length          :   0x%02x\n", msg.u.dcmMsg.u.chanActivNack.length);
	printf("Cause Value     :   0x%02x\n", msg.u.dcmMsg.u.chanActivNack.causeVal);
	printf("Diagnostics     :   0x%02x\n", msg.u.dcmMsg.u.chanActivNack.diagnostics[0]);
    
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the Multirate Codec Modification Neg Ack information elements 
*        from the file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
ITS_INT
ReadMulCodecModNack (ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_params=6;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int diagcount;

    printf("                        \n");
    printf("Message Name: MULTIRATE CODEC MODIFICATION NEGATIVE ACKNOWLEDGE\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"MUL_CODEC_MOD_NACK START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"MUL_CODEC_MOD_NACK END\n")!=0)
            {
                if(line[0]=='M')
                {
                    if(line[1]=='\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    if (kcount==no_params)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: MULTIRATE CODEC MODIFICATION NEGATIVE ACKNOWLEDGE \n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
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
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
                                                                                                                             
	if (k==5)
        {
            msg->u.dcmMsg.u.chanActivNack.length=temp[k];
            printf("length          :   0x%02x\n",msg->u.dcmMsg.u.chanActivNack.length);
        }
                                                                                                                             
	if (k==6)
        {
            msg->u.dcmMsg.u.chanActivNack.causeVal=temp[k];
            printf("causeVal        :   0x%02x\n",msg->u.dcmMsg.u.chanActivNack.causeVal);
        }
        
       if(k==7)
       {

	   printf("diagnostics     :   0x%02x\n",temp);	   
           for(diagcount=0;diagcount<msg->u.dcmMsg.u.chanActivNack.length;diagcount++)
            {
               msg->u.dcmMsg.u.chanActivNack.diagnostics[diagcount]=temp[k];
            }

      }
    }
    
	fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Multi Rate Codec Modification Request
        information elements from the file, encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
HandleMCodecModPer(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadMCodecModPer(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Multirate Codec Modification Performed Failed  ret :: %d\n", ret);
         return ret;
    }
    else
                                                                                                                             
    printf("********************************** ENCODED DATA **********************************\n");
    {
        printf("Encoding Multirate Codec Modification Performed success  ret :: %d\n\n", ret);
        /* display buffer */
                                                                                                                             
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("********************************** DECODED DATA **********************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Multirate Codec Modification Performed failed   ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Encoding Multirate Codec Modification Performed Success  ret :: %d\n", ret);
        /* display buffer */
         printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("length          :   0x%02x\n", msg.u.dcmMsg.u.mrCodecModReq.mrConfig.length);
	printf("Content         :   0x%02x\n", msg.u.dcmMsg.u.mrCodecModReq.mrConfig.content[0]);
    
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the MCodec Modification Performed information elements from 
*       the file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
ITS_INT
ReadMCodecModPer(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_params=6;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int diagcount;

    printf("                        \n");
    printf("Message Name: MULTIRATE CODEC MODIFICATION PERFORMED\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"MUL_CODEC_MOD_NACK START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"MUL_CODEC_MOD_NACK END\n")!=0)
            {
                if(line[0]=='M')
                {
                    if(line[1]=='\t')
                    {
                        /* Do Nothing */
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    if (kcount==no_params)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: MULTIRATE CODEC MODIFICATION PERFORMED\n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
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
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
                                                                                                                             
	if (k==5)
        {
            msg->u.dcmMsg.u.mrCodecModReq.mrConfig.length=temp[k];
            printf("length          :   0x%02x\n",msg->u.dcmMsg.u.mrCodecModReq.mrConfig.length);
        }
                                                                                                                             
        
       if(k==6)
       {

	   printf("Content         :   0x%02x\n",temp[k]);	   
           for(i=0;i<msg->u.dcmMsg.u.mrCodecModReq.mrConfig.length;i++)
            {
               msg->u.dcmMsg.u.mrCodecModReq.mrConfig.content[i]=temp[k];
            }

      }
    }
    
	fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the TFO Report information elements from the file,
*       encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/


ITS_INT
HandleTFORep(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    int ret1 = 0;
    ITS_OCTET buffer[300];
    ReadTFORep(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding TFO Report failed  ret :: %d\n", ret);
        return ret;
    }
    else                                                                                                                         {
     
     printf("********************************** ENCODED DATA **********************************\n");
     printf("Encoding TFO Report success  ret :: %d\n\n", ret);
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("********************************** DECODED DATA **********************************\n");
    ret1 = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret1 != ITS_SUCCESS)
    {
        printf("Decoding TFO Report Failed  ret :: %d\n", ret1);
        return ret1;
        
    }
    else
    {
    	 printf("Decoding TFO Report Success  ret :: %d\n", ret);
         //display buffer 
         printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("TFO Status      :   0x%02x\n",msg.u.dcmMsg.u.tfoRep.tfoStatus);
       
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the TFO Report information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/

ITS_INT
ReadTFORep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_elem=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];

    printf("                        \n");
    printf("Message Name: TFO REPORT \n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("TFO REPORT\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"TFO_REP START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"TFO_REP END\n")!=0)
            {
                if(line[0]=='M' || line[0]=='O')
                {
                    if(line[1]=='\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
		
		                    
                printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: TFO REPORT\n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
                                                                                                                             
	l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
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
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits        :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {                                                                                                                                 msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :  0x%02x\n",msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }

        if (k==5)
        {                                                                                                                                 msg->u.dcmMsg.u.tfoRep.tfoStatus     = temp[k];
             printf("timeSlotNum     :   0x%02x\n",msg->u.dcmMsg.u.tfoRep.tfoStatus);
        }
     }
      fclose(fp);
 }
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Remote Codec Modification Request information elements 
        from the file,encoding and then decoding
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
HandleRemCodecModRep(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int diagcount;
    ReadRemCodecModRep(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding remote codec modification Report Failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("********************************** ENCODED DATA **********************************\n");
    {
        printf("Encoding remote codec modification report success  ret :: %d\n\n", ret);
        // display buffer 
                                                                                                                             
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("********************************** DECODED DATA **********************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("decoding remote codec modification report failed   ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Encoding Remote Codec Modification Report Success  ret :: %d\n", ret);
       
         printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("length          :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.config.length);
        printf("codecType       :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.config.codecType);
        printf("ICM             :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.config.ICM);
        printf("codecset        :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.config.codecSet);
        printf("length          :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.length);             
        printf("sysId           :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.sysId);        
        printf("codecList       :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.codecList);   
      /*  printf("MACS[0]         :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.MACS[0]);                 
        printf("TFO_VER[0]      :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.TFO_VER[0]);     
        printf("MACS[1]         :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.MACS[1]);            
        printf("TFO_VER[1]      :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.TFO_VER[1]); 
        printf("SCS[0]          :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.SCS[0]);            
        printf("SCS[1]          :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.SCS[1]);*/            
        printf("prefCodecTyp    :   0x%02x\n", msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes.prefCodecType);
                                                                                                                                                                                                                                                              }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the MultiRate Mcodec Modn Report information elements 
*       from the file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
                                                                                                                     
ITS_INT
ReadRemCodecModRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_params=6;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int diagcount;

    printf("                        \n");
    printf("Message Name: REMOTE CODEC MODIFICATION REPORT\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"REM_COD_CONF_REP START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"REM_COD_CONF_REP END\n")!=0)
            {
                if(line[0]=='M')
                {
                    if(line[1]=='\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
                printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
    if (kcount==no_params)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: REMOTE CODEC MODIFICATION REPORT \n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
                                                                                                                             
        l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        if (k==0)
        {
             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc     :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
                                                                                                                             
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)  :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
                                                                                                                             
        if (k==2)
        {
                                                                                                                             
             msg->genElemnts.msgType=temp[k];
             printf("msgType     :   0x%02x\n",msg->genElemnts.msgType);
        }
                                                                                                                             
        if (k==3)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits    :   0x%02x\n",
                                msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum :   0x%02x\n",
                               msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
                                                                                                                             
	if (k==5)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.config.length =temp[k];
            printf("length       :  0x%02x\n", 
                               msg->u.dcmMsg.u.remoteCodecConfRep.config.length);
   
        }
                                                                                                                             
	if (k==6)
        {
                 
            msg->u.dcmMsg.u.remoteCodecConfRep.config.codecType =temp[k];
            printf("codecType      :  0x%02x\n", 
                              msg->u.dcmMsg.u.remoteCodecConfRep.config.codecType);

        }
	if (k==7)
        { 
            msg->u.dcmMsg.u.remoteCodecConfRep.config.ICM =temp[k];
            printf("ICM           :  0x%02x\n", 
                                       msg->u.dcmMsg.u.remoteCodecConfRep.config.ICM);

        }
	if (k==8)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.config.codecSet =temp[k];
            printf("codecset      :  0x%02x\n", 
                                   msg->u.dcmMsg.u.remoteCodecConfRep.config.codecSet);
        }
	if (k==9)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.length = temp[k];                 
            printf("length        :  0x%02x\n", 
                                  msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.length);                 
        }
	if (k==10)
        { 
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.sysId = temp[k];                 
            printf("sysId         :  0x%02x\n",
                                   msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.sysId);                 

        }
	if (k==11)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.codecList = temp[k];                 
            printf("codecList    :  0x%02x\n",
                               msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.codecList);                 

        }
/*	if (k==12)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.MACS[0] = temp[k];                 
            printf("MACS[0]       :  0x%02x\n", 
                               msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.MACS[0]);                 

        }
	if (k==13)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.TFO_VER[0] = temp[k];                 
            printf("TFO_VER[0]    :  0x%02x\n",
                             msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.TFO_VER[0]);                 
        }
	if (k==14)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.MACS[1] = temp[k];                 
            printf("MACS[1]    :  0x%02x\n",
                            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.MACS[1]);                 
        }
	if (k==15)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.TFO_VER[1] = temp[k];                 
            printf("TFO_VER[1] :  0x%02x\n",
                       msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.TFO_VER[1]);                 
        }
	if (k==16)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.SCS[0] = temp[k];                 
            printf("SCS[0]    :  0x%02x\n",
                           msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.SCS[0]);                 
        }

	if (k==17)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.SCS[1] = temp[k];                 
            printf("SCS[1]    :  0x%02x\n",
                           msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.SCS[1]);                 
        } */
 
	if (k==12)
        {
            msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.prefCodecType = temp[k];                 
            printf("prefCod   :  0x%02x\n",
                   msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes.prefCodecType);                 
        }
     }
     fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the data request information elements from the file,
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  25-08-2005
*
*
*/

ITS_INT
HandleTFOModReq(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    int ret1 = 0;
    ITS_OCTET buffer[300];
    ReadTFOModReq(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding TFO Modification Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else                                                                                                                         {
        // display buffer 
     printf("************************** ENCODED DATA *******************************\n");
     printf("Encoding TFO Modification Request Success  ret :: %d\n\n", ret);
       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    printf("*************************** DECODED DATA **************************\n");
    ret1 = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret1 != ITS_SUCCESS)
    {
        printf("Decoding TFO Modification Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	 printf("Decoding TFO Modification Request Success  ret :: %d\n", ret);
         //display buffer 
         printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("TFO             :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.mrControl.TFO);
        printf("PRE             :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.mrControl.PRE);
        printf("RAE             :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.mrControl.RAE);
        printf("length          :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.length);
        printf("SysId           :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.sysId);
        printf("CodecList       :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.codecList);
        printf("MACS[0]         :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.MACS[0]);
        printf("TFO_VER[0]      :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.TFO_VER[0]);
        printf("MACS[1]         :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.MACS[0]);
        printf("TFO_VER[1]      :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.TFO_VER[0]);
        printf("SCS[0]          :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.SCS[0]);
        printf("SCS[1]          :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.SCS[1]);
        printf("prefCodecType   :   0x%02x\n", msg.u.dcmMsg.u.tfoModReq.codecTypes.prefCodecType);
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Reading the TFO Modify Req information elements from the
*       file and assigning these values to the structure element
* INPUT:
*       File Pointer - Pointer to the file wherein values are read.
*       msg-pointer to the traffic management structure to store data read
*       from the file.
* INPUT/OUTPUT:
*       None
* OUTPUT:
        Values of the message structure are printed on the standard output
* RETURNS:
        none
* COMMENTS:
*       none
*/
ITS_INT
ReadTFOModReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount,k=0,kcount;
    int no_elem=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];

    printf("                        \n");
    printf("Message Name: TFO \n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("TFO MODIFICATION REQUEST\n");
    printf("                        \n");
    fp=fopen(filename,"r");
    CLEAR_TM_DCM_TMR_OPTIONAL_BIT_MAP(msg);
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"TFO_MODREQ START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"TFO_MODREQ END\n")!=0)
            {
                if(line[0]=='M' || line[0]=='O')
                {
                    if(line[1]=='\t')
                    {
                        // Do Nothing 
                    }
                    else
                    {
                        printf("tab space needed after the parameter\n");
                        exit(1);
                    }
                }
		
		if (line[0]=='O' && line[1]=='\t' && line[2]=='0')
                {
                    no_elem=17;
                }
                else
		{
                    no_elem=8;
                }                                    
                printf("%s",line);
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
                         bufspace[k]=(char*)calloc(strlen(tokenspace)+1,sizeof(char));
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
    icount=i;
    kcount=k;
  /*  if (kcount==no_elem)
    {
                                                                                                                             
    }
    else
    {
	printf("Information element missing\n");
        exit(1);
    }*/
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: TFO MODIFICATION REQUEST\n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0' &&
           bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' ||
           bufspace[k][3]>='0' && bufspace[k][3]<='9' )
        {
                                                                                                                             
        }
        else
        {
            printf("input not in correct format\n");
        }
                                                                                                                             
	l[k]=strtol(bufspace[k],NULL,16);
        temp[k]=(unsigned char)l[k];
        if (k==0)
        {

             msg->genElemnts.msgDesc.msgGruop=temp[k];
             printf("msgDesc   :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop) ;
        }
                                                                                                                             
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T) :   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
                                                                                                                             
        if (k==2)
        {
             msg->genElemnts.msgType=temp[k];
             printf("msgType    :   0x%02x\n",msg->genElemnts.msgType);
        }
                                                                                                                             
        if (k==3)
        {
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits   :   0x%02x\n",
                              msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {                                                                                                                                 msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum     :   0x%02x\n",
                           msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
                                                                                                                  	
        if (k==5)
        {                                                                                                                                 msg->u.dcmMsg.u.tfoModReq.mrControl.TFO=temp[k];
             printf("mr control TFO       :   0x%02x\n",msg->u.dcmMsg.u.tfoModReq.mrControl.TFO);
        }                                                                                                                  	
        if (k==6)
        {                                                                                                                                 msg->u.dcmMsg.u.tfoModReq.mrControl.PRE=temp[k];
             printf("mr control PRE       :   0x%02x\n",msg->u.dcmMsg.u.tfoModReq.mrControl.PRE);
        }                                                                                                                  	
        if (k==7)
        {                                                                                                                                 msg->u.dcmMsg.u.tfoModReq.mrControl.RAE=temp[k];
             printf("mr control RAE       :   0x%02x\n",msg->u.dcmMsg.u.tfoModReq.mrControl.RAE);
        }                                                                                                                  	
        if (k==8)
        {    

             SET_TM_DCM_TMR_SUPPORTED_CODEC_TYPE(msg);                                       
             msg->u.dcmMsg.u.tfoModReq.codecTypes.length=temp[k];
             printf("length        :   0x%02x\n",msg->u.dcmMsg.u.tfoModReq.codecTypes.length);
        }                                                                                                                  	
        if (k==9)
        {
             msg->u.dcmMsg.u.tfoModReq.codecTypes.sysId=temp[k];
             printf("sysId         :   0x%02x\n",msg->u.dcmMsg.u.tfoModReq.codecTypes.sysId);
        }                                                                                                                  	
        if (k==10)
        {                                                                                                                                                                                                                                                                              
             msg->u.dcmMsg.u.tfoModReq.codecTypes.codecList=temp[k];
             printf("codecList     :   0x%02x\n",msg->u.dcmMsg.u.tfoModReq.codecTypes.codecList);
        }                                                                                                                  	
        if (k==11)
        { 
             msg->u.dcmMsg.u.tfoModReq.codecTypes.MACS[0]=temp[k];
             printf("MACS[0]       :   0x%02x\n",msg->u.dcmMsg.u.tfoModReq.codecTypes.MACS[0]);
        }
        
                                                                                                                  	           if (k==12)

        {                                                                                                                                 
             msg->u.dcmMsg.u.tfoModReq.codecTypes.TFO_VER[0]=temp[k];
             printf("TFO_VER[0]   :   0x%02x\n",
                                         msg->u.dcmMsg.u.tfoModReq.codecTypes.TFO_VER[0]);
        }                                                                                                                  	
        if (k==13)
        {                                                                                                                                                                                                                                                                     
             msg->u.dcmMsg.u.tfoModReq.codecTypes.MACS[1]=temp[k];
             printf("MACS[1]      :   0x%02x\n",
                                       msg->u.dcmMsg.u.tfoModReq.codecTypes.MACS[1]);
        }
        if (k==14)
        {                                                                                                                                                                                                                                                               
             msg->u.dcmMsg.u.tfoModReq.codecTypes.TFO_VER[1]=temp[k];
             printf("TFO VER[1]  :   0x%02x\n",
                                   msg->u.dcmMsg.u.tfoModReq.codecTypes.TFO_VER[1]);
        }
        if (k==15)
        {                                                                                                                                                                                                                                                             
             msg->u.dcmMsg.u.tfoModReq.codecTypes.SCS[0]=temp[k];
             printf("SCS[0]      :   0x%02x\n",
                                       msg->u.dcmMsg.u.tfoModReq.codecTypes.SCS[0]);
        }
        
        if (k==16)
        {                                                                                                                                                                                                                                                             
             msg->u.dcmMsg.u.tfoModReq.codecTypes.SCS[1]=temp[k];
             printf("SCS[1]      :   0x%02x\n",
                                       msg->u.dcmMsg.u.tfoModReq.codecTypes.SCS[1]);
        }
        if (k==17)
        {    
                                                                                                                                           
            msg->u.dcmMsg.u.tfoModReq.codecTypes.prefCodecType=temp[k];
             printf("prefCodTyp :   0x%02x\n",
                                msg->u.dcmMsg.u.tfoModReq.codecTypes.prefCodecType);
        }
 
	fclose(fp);
     }
}   

ITS_INT
printEncComDcmm(ITS_OCTET *buffer, int len)
{
    int i = 0;
    for(i=0;i<len;i++)
    {
        printf("%02x ", buffer[i]);
    }
    printf("\n\n");
    return;
}
                                                                                                                             
ITS_INT
printDecComDcmm(ABIS_TRAFFIC_MANAGEMENT_MSG msg,int params)
{
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
    printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
    printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
    printf("chanBits        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
    printf("timeSlotNum     :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
    if(params==6)
    {
        printf("Access Delay    :   0x%02x\n",  msg.u.dcmMsg.u.handoDet.accessDelay);
    }
    return;
}

ITS_INT (*testTrafficMsg_DCMM[35])(int) = {
                                             HandleChanActv,
                                             HandleChanActv,
                                             HandleChanActvAck,
                                             HandleChanNActvAck,
					     HandleConFLInd,
                                             HandleDeActSacch,
                                             HandleEncCom,
                                             HandleHandDet,
                                             HandleMeasRes,
                                             HandleModeModify,
                                             HandleModModifyAck,
					     HandleModModifyNack,
					     HandlePhyConReq,
					     HandlePhyConConf,
					     HandleRFChanRel,
					     HandleMSPowctrl,
					     HandleBSPowctrl,
					     HandlePreProConf,
					     HandlePreProMeasRes,
					     HandleRFChanRelAck,
					     HandleSacchInfoMod,
					     HandleTalkDet,
					     HandleListDet,
					     HandleRemCodecModRep,
					     HandleRndTrip,
					     HandlePreHndNot,
					     HandleMCodecModReq,
					     HandleMCodecModAck,
					     HandleMCodecModNack,
					     HandleMCodecModPer,
					     HandleTFORep,
					     HandleTFOModReq 
					    }; 

