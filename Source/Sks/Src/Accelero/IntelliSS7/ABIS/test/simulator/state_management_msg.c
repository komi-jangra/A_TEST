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
 *  ID: $Id: state_management_msg.c,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
 *
 *  $Log: not supported by cvs2svn $
 *  Revision 1.1.1.1  2007/10/04 13:23:39  bsccs2
 *  init tree
 *
 *  Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 *  BscCs2
 *
 *  Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
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
*       Handles reading the StateChangeEventReport elements from the file,
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
HandleStateChangeEventReport(int choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    int ret_elem =0  ;
    FILE *fptr;
    char line[1024];
    ReadStateChangeEventReport(&msg,fp,choice);
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
    
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"STATECHANGEEVENT START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "STATECHANGEEVENT END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("operanStat       :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.changeEv.operanStat);

                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-2"))
                    {
                        printf("availStatLen     :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.changeEv.availStat.length);
                        printf("Status[0]        :  0x%02x\n",
                      msg.u.formMsg.u.stateMsg.u.changeEv.availStat.status[0]);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-3"))
                    {
                       printf("mfdDepen         :  0x%02x\n",
                             msg.u.formMsg.u.stateMsg.u.changeEv.mfdDepen);
                       
                    }

                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-4"))
                    { 
                        printf("siteInputlength  :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.changeEv.siteInputs.length);
                        printf("attr[0].state    :  0x%02x\n",
                msg.u.formMsg.u.stateMsg.u.changeEv.siteInputs.attr[0].state);
                        printf("attr[0].input    :  0x%02x\n",
                msg.u.formMsg.u.stateMsg.u.changeEv.siteInputs.attr[0].input);
                       
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
*       Reading the StateChangeEventReport information elements from the file
*       and assigning these values to the structure element
*       
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
ReadStateChangeEventReport(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp, int choice)
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
    printf("MESSAGE CATEGORY:STATE MANAGEMENT AND EVENT REPORT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"STATECHANGEEVENT START\n") == 0)
        {  
            CLEAR_NM_SM_SCER_OPTIONAL_BIT_MAP(msg);
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "STATECHANGEEVENT END\n") != 0)
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

                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_NM_SM_SCER_OPERATIONAL_STATE(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                           msg->u.formMsg.u.stateMsg.u.changeEv.operanStat = 
                                                                      temp[i];
                        }
                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-2"))
                {
                    optional[2] = 2;
                    SET_NM_SM_SCER_AVAILABILITY_STATE(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                        msg->u.formMsg.u.stateMsg.u.changeEv.availStat.length = 
                                                                      temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for(j = 0;
                j < msg->u.formMsg.u.stateMsg.u.changeEv.availStat.length ;
                       j++ )
                            {
                     msg->u.formMsg.u.stateMsg.u.changeEv.availStat.status[j] = 
                                                                      temp[i];
                             }
                        }

                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-3"))
                {
                    optional[3] = 3;
                    SET_NM_SM_SCER_MAN_DEP_STATE(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.formMsg.u.stateMsg.u.changeEv.mfdDepen = 
                                                                      temp[i];
                        }
                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-4"))
                {
                    optional[4] = 4;
                    SET_NM_SM_SCER_SITE_INPUTS(msg);
                    sscanf(line,"%c %s %s %s",&c,&str,&str1,&str2);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs.length = 
                                                                      temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0;
                  j < msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs.length ;
                      j++ )
                            {

               msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs.attr[j].state =
                                                                  temp[i];
                            }
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0;
                  j < msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs.length ;
                      j++ )
                            {

               msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs.attr[j].input =
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
    printf("MESSAGE NAME: STATE CHANGED EVENT REPORT\n");
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
             msg->u.formMsg.u.stateMsg.u.stopEv.nackCuase = temp[k];
             printf("nackCuase      :   0x%02x\n",
                         msg->u.formMsg.u.stateMsg.u.stopEv.nackCuase);
        }

    }
    if (optional[1] == 1)
    {
        printf("operanStat       :  0x%02x\n",
                         msg->u.formMsg.u.stateMsg.u.changeEv.operanStat);

    }
    if (optional[2] == 2)
    {
        printf("availStatLen     :  0x%02x\n",
                    msg->u.formMsg.u.stateMsg.u.changeEv.availStat.length);
        printf("Status[0]        :  0x%02x\n",
                  msg->u.formMsg.u.stateMsg.u.changeEv.availStat.status[0]);
    } 
    if (optional[3] == 3)
    {
        printf("mfdDepen         :  0x%02x\n",
                             msg->u.formMsg.u.stateMsg.u.changeEv.mfdDepen);
    }
    if (optional[4] == 4)
    {
        printf("stateInputlen    :  0x%02x\n",
                       msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs.length);
        printf("attr[0].state    :  0x%02x\n",
         msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs.attr[0].state);
        printf("attr[0].input    :  0x%02x\n",
         msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs.attr[0].input);

    }
    fclose(fp);
  
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Failure Event Report elements from the file,
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
HandleFailureEventReport(int choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    int ret_elem =0  ;
    FILE *fptr;
    char line[1024];
    ReadFailureEventReport(&msg,fp);
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
        printf("EventType        :  0x%02x\n",
                         msg.u.formMsg.u.stateMsg.u.failEv.evtType );    
        printf("percvdSeverity   :  0x%02x\n",
                         msg.u.formMsg.u.stateMsg.u.failEv.percvdSever);    
        printf("probCuaseType    :  0x%02x\n",
                         msg.u.formMsg.u.stateMsg.u.failEv.probCause.type );    
        printf("probCuaseVal     :  0x%02x\n",
                         msg.u.formMsg.u.stateMsg.u.failEv.probCause.value );    
    
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"FAILUREEVENTREPORT START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "FAILUREEVENTREPORT END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("specProbs        :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.specProbs);

                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-2"))
                    {
                        printf("equipIdLen       :  0x%02x\n",
                       msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.equipIdLen );
                        printf("equipId[0]       :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.equipId[0]);
                        printf("equipTypeLen     :  0x%02x\n",
                       msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.equipTypeLen );
                        printf("equipType[0]     :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.equipType[0]);
                        printf("equipVerLen      :  0x%02x\n",
                       msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.equipVerLen);
                        printf("equipVer[0]      :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.equipVer[0]);
                        printf("Loclen           :  0x%02x\n",
                       msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.locLen);
                        printf("location[0]      :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.location[0]);
                        printf("Infolen          :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.infoLen);
                        printf("info[0]          :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.hwDescr.info[0]);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-3"))
                    {
                       printf("fileIdLen        :  0x%02x\n",
                       msg.u.formMsg.u.stateMsg.u.failEv.swDescr.fileIdLen);
                       printf("file[0]          :  0x%02x\n",
                       msg.u.formMsg.u.stateMsg.u.failEv.swDescr.fileId[0]);
                       printf("fileVerLen       :  0x%02x\n",
                       msg.u.formMsg.u.stateMsg.u.failEv.swDescr.fileVerLen);
                       printf("fileVer[0]       :  0x%02x\n",
                       msg.u.formMsg.u.stateMsg.u.failEv.swDescr.fileVer[0]);
                       
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-4"))
                    { 
                        printf("AddTextLen       :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.addText.length);
                        printf("AddTextvalu[0]   :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.addText.value[0]);
                       
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-5"))
                    {
                        printf("addInfoLen       :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.addInfo.length);
                        printf("addInfovalue[0]  :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.addInfo.value[0]);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-6"))
                    {
                        printf("alarmSeq         :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.failEv.alarmSeq);
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
*       Reading the FailureEventReport information elements from the file and 
*       assigning these values to the structure elements
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
ReadFailureEventReport(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp)
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
    printf("MESSAGE CATEGORY:STATE MANAGEMENT AND EVENT REPORT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"FAILUREEVENTREPORT START\n") == 0)
        { 
            CLEAR_NM_SM_FER_OPTIONAL_BIT_MAP(msg);
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "FAILUREEVENTREPORT END\n") != 0)
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
                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_NM_SM_FER_SPECIFIC_PROBLEMS(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.formMsg.u.stateMsg.u.failEv.specProbs = 
                                                                temp[i];
                        }
                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-2"))
                {
                    optional[2] = 2;
                    SET_NM_SM_FER_HW_DESCRIPTION(msg);
                   sscanf(line,"%c %s %s %s %s %s %s %s %s %s %s",
                 &c,&str,&str1,&str2,&str3,&str4,&str5,&str6,&str7,&str8,&str9);
                    for (i = 0; i < 10; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                 msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipIdLen = 
                                                           temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                      j < msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipIdLen;
                       j++ )
                            {
 
                        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipId[j] = 
                                                                  temp[i];
                             }
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                      msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipTypeLen = 
                                                           temp[i];
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                    j < msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipTypeLen;
                       j++ )
                            {
 
                     msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipType[j] = 
                                                                  temp[i];
                             }
                        }
                        if (i == 4)
                        {
                            l[i] = strtol(str4,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipVerLen = 
                                                           temp[i];
                        }
                        if (i == 5)
                        {
                            l[i] = strtol(str5,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                     j < msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipVerLen;
                       j++ )
                            {
 
                   msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipVer[j] = 
                                                                  temp[i];
                             }
                        }
                        if (i == 6)
                        {
                            l[i] = strtol(str6,NULL,16);
                            temp[i] = (unsigned char)l[i];
                 msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.locLen = 
                                                           temp[i];
                        }
                        if (i == 7)
                        {
                            l[i] = strtol(str7,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                      j < msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.locLen;
                       j++ )
                            {
 
                    msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.location[j] = 
                                                                  temp[i];
                             }
                        }


                        if (i == 8)
                        {
                            l[i] = strtol(str8,NULL,16);
                            temp[i] = (unsigned char)l[i];
                 msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.infoLen = 
                                                           temp[i];
                        }
                        if (i == 9)
                        {
                            l[i] = strtol(str9,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                      j < msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.infoLen ;
                       j++ )
                            {
 
                    msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.info[j] = 
                                                                  temp[i];
                             }
                        }
                    }
 
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-3"))
                {
                    optional[3] = 3;
                    SET_NM_SM_FER_SW_DESCRIPTION(msg);
                    sscanf(line,"%c %s %s %s %s",&c,&str,&str1,&str2,&str3);
                    for (i = 0; i < 5; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                         msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileIdLen = 
                                                                        temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                      j < msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileIdLen;
                       j++ )
                            {
 
                         msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileId[j] = 
                                                                       temp[i];
                             }
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                      msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileVerLen = 
                                                                     temp[i];
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
                      j < msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileVerLen;
                       j++ )
                            {
 
                        msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileVer[j] = 
                                                                       temp[i];
                             }
                        }
                    }  
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-4"))
                {
                    optional[4] = 4;
                    SET_NM_SM_FER_ADDITIONAL_TEXT(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.formMsg.u.stateMsg.u.failEv.addText.length =
                                                                        temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0;
                     j < msg->u.formMsg.u.stateMsg.u.failEv.addText.length;
                       j++ )
                            {

                        msg->u.formMsg.u.stateMsg.u.failEv.addText.value[j] =
                                                                       temp[i];
                             }
                        }

                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-5"))
                {
                    optional[5] = 5;
                    SET_NM_SM_FER_ADDITIONAL_INFO(msg);
                    sscanf(line,"%c %s",&c,&str,str1);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.formMsg.u.stateMsg.u.failEv.addInfo.length =
                                                                        temp[i];                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0;
                     j < msg->u.formMsg.u.stateMsg.u.failEv.addInfo.length;
                       j++ )
                            {

                        msg->u.formMsg.u.stateMsg.u.failEv.addInfo.value[j] =
                                                                       temp[i];
                             }
                        }

                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-6"))
                {
                    optional[6] = 6;
                    SET_NM_SM_FER_OUTSTANDING_ALARM_SEQ(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.formMsg.u.stateMsg.u.failEv.alarmSeq =
                                                                temp[i];
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
    if (kcount == 12 || kcount > 12)
    {
    }
    else
    {
	printf("Information element missing\n");
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS.\n");
    printf("                          \n");
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("MESSAGE NAME: FAILURE EVENT REPORT\n");
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
             msg->u.formMsg.u.stateMsg.u.failEv.evtType = temp[k];
             printf("EventType        :  0x%02x\n",
                         msg->u.formMsg.u.stateMsg.u.failEv.evtType );    
        }
        if (k == 9)
        {
             msg->u.formMsg.u.stateMsg.u.failEv.percvdSever = temp[k];
             printf("percvdSeverity   :  0x%02x\n",
                         msg->u.formMsg.u.stateMsg.u.failEv.percvdSever);    
        }
        if (k == 10)
        {
             msg->u.formMsg.u.stateMsg.u.failEv.probCause.type = temp[k];
             printf("probCuaseType    :  0x%02x\n",
                         msg->u.formMsg.u.stateMsg.u.failEv.probCause.type );    
        }
        if (k == 11)
        {
             msg->u.formMsg.u.stateMsg.u.failEv.probCause.value = temp[k];
             printf("probCuaseVal     :  0x%02x\n",
                      msg->u.formMsg.u.stateMsg.u.failEv.probCause.value);    
        }

    }
    if (optional[1] == 1)
    {
        printf("specProbs        :  0x%02x\n",
                        msg->u.formMsg.u.stateMsg.u.failEv.specProbs);

    }
    if (optional[2] == 2)
    {
        printf("equipIdLen       :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipIdLen );
        printf("equipId[0]       :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipId[0]);
        printf("equipTypeLen     :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipTypeLen );
        printf("equipType[0]     :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipType[0]);
        printf("equipVerLen      :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipVerLen);
        printf("equipVer[0]      :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.equipVer[0]);
        printf("Loclen           :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.locLen);
        printf("location[0]      :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.location[0]);
        printf("Infolen          :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.infoLen);
        printf("info[0]          :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.hwDescr.info[0]);
    } 
    if (optional[3] == 3)
    {
        printf("fileIdLen        :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileIdLen);
        printf("file[0]          :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileId[0]);
        printf("fileVerLen       :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileVerLen);
        printf("fileVer[0]       :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.swDescr.fileVer[0]);
    }
    if (optional[4] == 4)
    {
        printf("AddTextLen       :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.addText.length);
        printf("AddTextvalu[0]   :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.addText.value[0]);

    }
    if (optional[5] == 5)
    {
        printf("addInfoLen       :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.addInfo.length);
        printf("addInfovalue[0]  :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.addInfo.value[0]);

    }
    if (optional[6] == 6)
    {
        printf("alarmSeq         :  0x%02x\n",
        msg->u.formMsg.u.stateMsg.u.failEv.alarmSeq);

    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the ChangeAdm State and ChangeAdmState Request elements
*       from the file,encoding and then decoding. The Same function takes care
*       of ChangeAdmState Ack,ChangeAdmState Nack,ChangeAdmState Request Ack 
*       and ChangeAdmState Request Nack
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
HandleChangeAdm(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadChangeAdm(&msg,fp,choice);
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
        printf("Admn State      :  0x%02x\n",
                               msg.u.formMsg.u.stateMsg.u.state.adminStat);
        printf("nackCuase       :  0x%02x\n",
                           msg.u.formMsg.u.stateMsg.u.state.nackCuase );
    }
    return ITS_SUCCESS;
}
 
/*implementation:internal
*
* PURPOSE:
*       Reading the ChangeAdmState and ChangeAdmStateRequest information 
*       elements from the file and assigning these values to the structure 
*       element and depending on the choices corresponding values are assigned 
*       to the structure elements
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
ReadChangeAdm(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    printf("MESSAGE CATEGORY: STATE MANAGEMENT AND EVENT REPORT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"CHANGEADMIN START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),"CHANGEADMIN END\n")!=0)
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
                   && choice == 9 && strstr(line,"Message Type"))
               {
                   sscanf(line,"%c %s",&c,&str);
                   l1=strtol(str,NULL,16);
                   temp1=(unsigned char)l1;
                   msg->u.formMsg.formGenElemnts.msgType = temp1;
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
    if (choice == 9)
    {
        printf("MESSAGE NAME: CHANGE ADMIN \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x69)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 10)
    {
        printf("MESSAGE NAME: CHANGE ADMIN ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x6A)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 11)
    {
        printf("MESSAGE NAME: CHANGE ADMIN NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x6B)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 12)
    {
        printf("MESSAGE NAME: CHANGE ADMIN STATE REQUEST \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x6C)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 13)
    {
        printf("MESSAGE NAME: CHANGE ADMIN STATE REQUEST ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x6D)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 14)
    {
        printf("MESSAGE NAME: CHANGE ADMIN STATE REQUEST NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x6E)
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
            msg->u.formMsg.u.stateMsg.u.state.adminStat = temp[k];
            printf("Admin Stat     :   0x%02x\n",
                      msg->u.formMsg.u.stateMsg.u.state.adminStat);
        }
        if (k == 9)
        {
            msg->u.formMsg.u.stateMsg.u.state.nackCuase = temp[k];
            printf("nackCuase      :   0x%02x\n",
                      msg->u.formMsg.u.stateMsg.u.state.nackCuase);
        }
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the ReportOutstand Alarm elements from the file,
*       encoding and then decoding. The Same function takes care of 
*       Report Outstand Alarm Ack and Report Outstand Alarm Nack
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
HandleReportOutstandAlarm(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    ReadReportOutstandAlarm(&msg,fp,choice);
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
                           msg.u.formMsg.u.stateMsg.u.repAlarm.nackCuase);
    }
    return ITS_SUCCESS;
}
  
/*implementation:internal
*
* PURPOSE:
*       Reading the ReportOutstandAlarm information elements from the file and 
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
ReadReportOutstandAlarm(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp,int choice)
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
    printf("MESSAGE CATEGORY: STATE MANAGEMENT AND EVENT REPORT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"REPORTOUTSTANDALRM START\n")==0)
        {
           while (strcmp(fgets(line,sizeof(line),fp),
                   "REPORTOUTSTANDALRM END\n")!=0)
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
                   && choice == 15 && strstr(line,"Message Type"))
                {
                    sscanf(line,"%c %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
                    msg->u.formMsg.formGenElemnts.msgType = temp1;
                }
                if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 16 && strstr(line,"Message Type"))
                {
                    sscanf(line,"%c %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
                    msg->u.formMsg.formGenElemnts.msgType = temp1;
                }
                if (line[0] == 'M' && line[1] == '\t' && line[2] == '0'
                   && choice == 17 && strstr(line,"Message Type"))
                {
                    sscanf(line,"%c %s",&c,&str);
                    l1 = strtol(str,NULL,16);
                    temp1 = (unsigned char)l1;
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
    if (choice == 15)
    {
        printf("MESSAGE NAME: REPORT OUSTANDING ALARM\n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x93)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 16)
    {
        printf("MESSAGE NAME: REPORT OUTSTANDING ALARM ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x94)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 17)
    {
        printf("MESSAGE NAME: REPORT OUSTANDING ALARM NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x95)
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
            msg->u.formMsg.u.stateMsg.u.repAlarm.nackCuase = temp[k];
            printf("nackCuase      :   0x%02x\n",
                      msg->u.formMsg.u.stateMsg.u.repAlarm.nackCuase) ;
        }
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the StopSendEvent and Restart Sending Event Report
*       elements from the file, encoding and then decoding. The Same function
*       takes care of StopSendEvent Ack ,StopSendEvent Nack, Restart Sending 
*       Event Ack and Restart Sending Event Nack
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
HandleStopSendEvent(int choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    int ret_elem =0  ;
    FILE *fptr;
    char line[1024];
    ReadStopSendEvent(&msg,fp,choice);
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
        printf("nackCuase        :  0x%02x\n",
                          msg.u.formMsg.u.stateMsg.u.stopEv.nackCuase);    
    
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"STOPSENDEVENT START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "STOPSENDEVENT END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("operanStat       :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.stopEv.operanStat);

                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-2"))
                    {
                        printf("availStatLen     :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.stopEv.availStat.length);
                        printf("Status[0]        :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.stopEv.availStat.status[0]);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-3"))
                    {
                       printf("mfdDepen         :  0x%02x\n",
                             msg.u.formMsg.u.stateMsg.u.stopEv.mfdDepen);
                       
                    }

                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-4"))
                    { 
                        printf("probCauseType    :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.stopEv.probCause.type);
                        printf("probCauseValue   :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.stopEv.probCause.value);
                       
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-5"))
                    {
                        printf("specificProb     :  0x%02x\n",
                        msg.u.formMsg.u.stateMsg.u.stopEv.specProbs);
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
*       Reading the StopSendEventReportand RestartSendEventReport information
*       elements from the file and assigning these values to the structure 
*       element and depending on the choices corresponding values are assigned 
*       to the structure elements
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
*      none
*/
ITS_INT
ReadStopSendEvent(ABIS_NETWORK_MANAGEMENT_MSG *msg,FILE *fp, int choice)
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
    printf("MESSAGE CATEGORY:STATE MANAGEMENT AND EVENT REPORT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"STOPSENDEVENT START\n") == 0)
        {  
            CLEAR_NM_SM_SSER_OPTIONAL_BIT_MAP(msg);
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "STOPSENDEVENT END\n") != 0)
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

                /***OPTIONAL BITS  ******/  
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-1"))
                {
                    optional[1] = 1;
                    SET_NM_SM_SSER_OPERATIONAL_STATE(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.formMsg.u.stateMsg.u.stopEv.operanStat = 
                                                                      temp[i];
                        }
                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-2"))
                {
                    optional[2] = 2;
                    SET_NM_SM_SSER_AVAILABILTY_STATE(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                          msg->u.formMsg.u.stateMsg.u.stopEv.availStat.length = 
                                                                      temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            for(j = 0;
                j < msg->u.formMsg.u.stateMsg.u.stopEv.availStat.length ;
                       j++ )
                            {
                      msg->u.formMsg.u.stateMsg.u.stopEv.availStat.status[j] = 
                                                                      temp[i];
                             }
                        }

                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-3"))
                {
                    optional[3] = 3;
                    SET_NM_SM_SSER_MFD_DEP_STATE(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.formMsg.u.stateMsg.u.stopEv.mfdDepen = 
                                                                      temp[i];
                        }
                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-4"))
                {
                    optional[4] = 4;
                    SET_NM_SM_SSER_PROBABLE_CAUSE(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.formMsg.u.stateMsg.u.stopEv.probCause.type = 
                                                                      temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                           msg->u.formMsg.u.stateMsg.u.stopEv.probCause.value = 
                                                                      temp[i];
                        }
                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-5"))
                {
                    optional[5] = 5;
                    SET_NM_SM_SSER_SPECIFIC_PROBLEMS(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.formMsg.u.stateMsg.u.stopEv.specProbs = 
                                                                  temp[i];
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
    if (choice == 3)
    {
        printf("MESSAGE NAME: STOP SENDING EVENT REPORTS \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x63)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 4)
    {
        printf("MESSAGE NAME: STOP SENDING EVENT REPORTS ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x64)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 5)
    {
        printf("MESSAGE NAME: STOP SENDING EVENT REPORTS NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x65)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 6)
    {
        printf("MESSAGE NAME: RESTART SENDING EVENT REPORTS \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x66)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 7)
    {
        printf("MESSAGE NAME: RESTART SENDING EVENT REPORTS ACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x67)
        {
            printf("Enter the correct message type\n");
            exit(1);
        }
    }
    if (choice == 8)
    {
        printf("MESSAGE NAME: RESTART SENDING EVENT REPORTS NACK \n");
        if ( msg->u.formMsg.formGenElemnts.msgType != 0x68)
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
             msg->u.formMsg.u.stateMsg.u.stopEv.nackCuase = temp[k];
             printf("nackCuase      :   0x%02x\n",
                         msg->u.formMsg.u.stateMsg.u.stopEv.nackCuase);
        }

    }
    if (optional[1] == 1)
    {
        printf("operanStat       :  0x%02x\n",
                         msg->u.formMsg.u.stateMsg.u.stopEv.operanStat);

    }
    if (optional[2] == 2)
    {
        printf("availStatLen     :  0x%02x\n",
                    msg->u.formMsg.u.stateMsg.u.stopEv.availStat.length);
        printf("Status[0]        :  0x%02x\n",
                  msg->u.formMsg.u.stateMsg.u.stopEv.availStat.status[0]);
    } 
    if (optional[3] == 3)
    {
        printf("mfdDepen         :  0x%02x\n",
                             msg->u.formMsg.u.stateMsg.u.stopEv.mfdDepen);
    }
    if (optional[4] == 4)
    {
        printf("probCauseType    :  0x%02x\n",
                       msg->u.formMsg.u.stateMsg.u.stopEv.probCause.type);
        printf("probCauseValue   :  0x%02x\n",
                     msg->u.formMsg.u.stateMsg.u.stopEv.probCause.value);
    }
    if (optional[5] == 5)
    {
        printf("specificProb     :  0x%02x\n",
                           msg->u.formMsg.u.stateMsg.u.stopEv.specProbs);
    }
    fclose(fp);
}

ITS_INT ( *testNetworkMsg_SMM[19])(int) = 
{
    NULL,
    HandleStateChangeEventReport,
    HandleFailureEventReport,
    HandleStopSendEvent, 
    HandleStopSendEvent, 
    HandleStopSendEvent, 
    HandleStopSendEvent, 
    HandleStopSendEvent, 
    HandleStopSendEvent, 
    HandleChangeAdm,
    HandleChangeAdm,
    HandleChangeAdm,
    HandleChangeAdm,
    HandleChangeAdm,
    HandleChangeAdm,
    HandleReportOutstandAlarm,
    HandleReportOutstandAlarm,
    HandleReportOutstandAlarm,
}; 

