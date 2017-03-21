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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: readTRXM_LCS.c,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $ 
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
 *  Revision 1.1.2.3  2005/09/27 12:22:25  mkrishna
 *  Modification done for Error cases - hakshata & raghavendrasm
 *
 *  Revision 1.1.2.2  2005/09/23 07:11:54  mkrishna
 *  Enhancements for Bugs raised - hakshata & sriraghavendrasm
 *
 *  Revision 1.1.2.1  2005/08/29 08:59:40  mkrishna
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
*       Handles reading the RF Resource Indication elements from the file,
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
HandleRfrscInd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadRfrscInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding RF Resource Indicaton failure ret :: %d\n", ret);
        return !ITS_SUCCESS;
    }
    else
    printf("***************** ENCODED DATA ***************************\n");    
    {
        printf("Encoding RF Resource Indication Success ret :: %d\n\n", ret);
        for(i=0;i<len;i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }


    printf("***************** DECODED DATA **************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding RF Resource Indication Failed ret:: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding RF Resource Indication Success ret :: %d\n", ret);

        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                       msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                     msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n",msg.genElemnts.msgType);
        printf("length          :   0x%02x\n",
                                     msg.u.trxmMsg.u.rfResInd.length);
        printf("chanlBits[0]    :   0x%02x\n",
                    msg.u.trxmMsg.u.rfResInd.info[0].chanlNum.chanlBits);
        printf("timeSlotNum[0]  :   0x%02x\n",
                   msg.u.trxmMsg.u.rfResInd.info[0].chanlNum.timeSlotNum);
        printf("interband[0]    :   0x%02x\n", 
                            msg.u.trxmMsg.u.rfResInd.info[0].interfBand);
        printf("chanlBits[1]    :   0x%02x\n",
                     msg.u.trxmMsg.u.rfResInd.info[1].chanlNum.chanlBits);
        printf("timeSlotNum[1]  :   0x%02x\n",
                   msg.u.trxmMsg.u.rfResInd.info[1].chanlNum.timeSlotNum);
        printf("interband[1]    :   0x%02x\n",
                            msg.u.trxmMsg.u.rfResInd.info[1].interfBand);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the RF Resource Indication elements from the file and assigning
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
*  Name            Date           Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*
*/

ITS_INT
ReadRfrscInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
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
    fp_ch = fopen(filename,"r");
    if (!fp_ch)
    {
        printf("Error opening the file\n");
        exit(1);
    }
    printf("                        \n");
    printf("Message Name: RF RESOURCE INDICATION \n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while ((c = fgetc(fp_ch)) != EOF)
    {
        if (c == '\n')
        linecount++;
        if(c == 'M')
        {
            d_tab = fgetc(fp_ch);
            if(d_tab == '\t')
            {
                /* printf("mandatory field ocuurred\n");*/
            }
            else if(d_tab == ' ')
            {
                printf("Tab space needed after the mandatory"
                "parameter at line %d\n",linecount);
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
                if (e_opt == '0')
                no_params = 10;   
                else
                no_params = 9;
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
        if ( strcmp(line,"RFRESIND START\n") == 0)
        {
            while ( strcmp(fgets(line,sizeof(line),fp),"RFRESIND END\n") != 0)
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
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS\n");
    printf("MESSAGE NAME: RF RESOURCE INDICATION\n");
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

        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f'||
        bufspace[k][2]>='0' && bufspace[k][2] <= '9' &&
        bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f'||
        bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
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
            msg->u.trxmMsg.u.rfResInd.length = temp;
            printf("length          :   0x%02x\n", 
                                       msg->u.trxmMsg.u.rfResInd.length);
        }

        if (k == 4)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.trxmMsg.u.rfResInd.info[0].chanlNum.chanlBits = temp;
            printf("chanlBit[0]     :   0x%02x\n",
                    msg->u.trxmMsg.u.rfResInd.info[0].chanlNum.chanlBits);
        }

        if (k == 5)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.trxmMsg.u.rfResInd.info[0].chanlNum.timeSlotNum = temp;
            printf("timeSlotNum     :   0x%02x\n",
                    msg->u.trxmMsg.u.rfResInd.info[0].chanlNum.timeSlotNum);
        }

        if (k == 6)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.trxmMsg.u.rfResInd.info[0].interfBand =  temp;
            printf("interfBand[0]   :   0x%02x\n",
                           msg->u.trxmMsg.u.rfResInd.info[0].interfBand);
        }

        if (k == 7)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.trxmMsg.u.rfResInd.info[1].chanlNum.chanlBits = temp;
            printf("chanlBit[1]     :   0x%02x\n",
                   msg->u.trxmMsg.u.rfResInd.info[1].chanlNum.chanlBits);
        }

        if (k == 8)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.trxmMsg.u.rfResInd.info[1].chanlNum.timeSlotNum = temp;
            printf("timeSlotNum[1]  :   0x%02x\n",
                   msg->u.trxmMsg.u.rfResInd.info[1].chanlNum.timeSlotNum);
        }

        if (k == 9)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.trxmMsg.u.rfResInd.info[1].interfBand =  temp;
            printf("interfBand[1]   :   0x%02x\n",
                          msg->u.trxmMsg.u.rfResInd.info[1].interfBand);
        }


    }
    fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Saach Filling elements from the file,
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
HandleSaachFill(int choice)
{  
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;	
    FILE *fptr; 
    char line[1024];
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    ReadSaachFill(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        	printf("Encoding SAACH FILLING  failure ret :: %d\n", ret);
               return ret;
     }
    else
 
    printf("******************** ENCODED DATA ************************\n");    
	 {
        	printf("Encoding SAACH FILLING Success  ret :: %d\n\n", ret);
       // display buffer 
                                                         

       for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }


    printf("*************** DECODED DATA ****************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SAACH FILLING Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding SAACH FILLING Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("sysInfoType     :   0x%02x\n", msg.u.trxmMsg.u.sacchFill.sysInfoType);
       fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"SAACHFILL START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "SAACHFILL END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("lengthInd       :   0x%02x\n",
                                   msg.u.trxmMsg.u.sacchFill.l3Info.lengthInd);
                        printf("LSDU[0]         :   0x%02x\n",
                                   msg.u.trxmMsg.u.sacchFill.l3Info.LLSDU[0]);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-2"))
                    {
                        printf("startingtime    :   0x%02x\n",
                                      msg.u.trxmMsg.u.sacchFill.startingTime);
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
*       Reading the Saach Filling elements from the file and assigning these
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
*
*/
ITS_INT
ReadSaachFill(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
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
    printf("MESSAGE CATEGORY:TRX MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        CLEAR_TM_TRXM_SF_OPTIONAL_BIT_MAP(msg);
        if (strcmp(line,"SAACHFILL START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "SAACHFILL END\n") != 0)
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
                    SET_TM_TRXM_SF_L3_INFO(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.sacchFill.l3Info.lengthInd = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0;
        j < msg->u.trxmMsg.u.sacchFill.l3Info.lengthInd ; j++ )
                            {
                   msg->u.trxmMsg.u.sacchFill.l3Info.LLSDU[j] = temp[i];
                             }
                        }


                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-2"))
                {
                    optional[2] = 2;
                    SET_TM_TRXM_SF_STARTING_TIME(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.sacchFill.startingTime = temp[i];
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
             msg->u.trxmMsg.u.sacchFill.sysInfoType = temp[k];
             printf("sysInfoType     :   0x%02x\n",msg->u.trxmMsg.u.sacchFill.sysInfoType); 
        }
}
 
    if (optional[1] == 1)
    {
        printf("lengthInd       :   0x%02x\n", 
                                    msg->u.trxmMsg.u.sacchFill.l3Info.lengthInd);
        printf("LLSDU[0]        :   0x%02x\n",
                                     msg->u.trxmMsg.u.sacchFill.l3Info.LLSDU[0]);
    }
    if (optional[2] == 2)
    {
        printf("startingtime    :   0x%02x\n",
                                      msg->u.trxmMsg.u.sacchFill.startingTime);
    
    } 
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the OverLoad elements from the file,
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
HandleOverLoad(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;    
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadOverLoad(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding OverLoad failure ret :: %d\n", ret);
        return ret;
    }
    else

    printf("****************** ENCODED DATA *************************\n");    
    {
        printf("Encoding OverLoad Success  ret :: %d\n\n", ret);
        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    printf("******************* DECODED DATA *************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding OverLoad Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding OverLoad Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                      msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                    msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("length          :   0x%02x\n",
                                      msg.u.trxmMsg.u.overload.length);
        printf("diagnostic[0]   :   0x%02x\n",
                               msg.u.trxmMsg.u.overload.diagnostics[0]);
        printf("causeVal        :   0x%02x\n",
                                     msg.u.trxmMsg.u.overload.causeVal);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the OverLoad elements from the file and assigning these
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
* -------------------------------------------------------------------------
*  Name            Date           Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*
*/

ITS_INT
ReadOverLoad(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE * fp)
{
    FILE *fp_ch;
    char line[1024];
    char *tokentab;
    char *tokenspace;
    char *buftab[300];
    char *bufspace[300];
    int i = 0, icount;
    int k = 0, kcount;
    int no_params = 7;
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
    printf("Message Name: OVERLOAD \n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while ((c = fgetc(fp_ch)) != EOF)
    {
        if (c == '\n')
        linecount++;
        if (c == 'M')
        {
            d_tab = fgetc(fp_ch);
            if (d_tab == '\t')
            {
                /* printf("mandatory field ocuurred\n");*/
            }
            else if(d_tab==' ')
            {
                printf("Tab space needed after the mandatory"
                                    "parameter at line %d\n",linecount);
                exit(1);
            }
        }
        if (c == 'O')
        {
            d_tab = fgetc(fp_ch);
            if (d_tab == '\t')
            {
                /* printf("optional field ocuurred\n");*/
                e_opt = fgetc(fp_ch);
                if (e_opt == '0')
                no_params = 7;
                else
                no_params = 6;
            }
            else if (d_tab == ' ')
            {
                printf("Tab space needed after the optional" 
                                        "parameter at line %d\n",linecount);
                exit(1);
            }
        }
    }
    fclose(fp_ch);
    fp = fopen(filename,"r");
    while ( feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"OVERLOAD START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"OVERLOAD END\n")!=0)
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
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS\n");
    printf("MESSAGE NAME: OVERLOAD\n");
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
            msg->u.trxmMsg.u.overload.length = temp;
            printf("length          :   0x%02x\n",
                                        msg->u.trxmMsg.u.overload.length);
        }

        if (k == 4)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            for(i = 0; i < msg->u.trxmMsg.u.overload.length; i++)
            {
                msg->u.trxmMsg.u.overload.diagnostics[i] = temp;
            }  
            printf("diagnostics[0]  :   0x%02x\n",
                                   msg->u.trxmMsg.u.overload.diagnostics[0]);
        }

        if (k == 5)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            msg->u.trxmMsg.u.overload.causeVal = temp;
            printf("causeVal        :   0x%02x\n",
                                        msg->u.trxmMsg.u.overload.causeVal);
        }

    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Error Report elements from the file,
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
HandleErrReport(int choice)
{
    FILE *fp;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];
    int ret_elem =0  ;
    FILE *fptr;
    char line[1024];
    ReadErrReport(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("****************** ENCODED DATA *************************\n");
        printf("Encoding Success  ret :: %d\n\n", ret);
       /* display buffer */
        printf("\n\n\n length :: %d\n\n\n", len);
        for(i = 0; i < len; i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    printf("********************** DECODED DATA ************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("Decoding Result Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        
        printf("msgDesc         :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)      :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("length          :   0x%02x\n", 
                                msg.u.trxmMsg.u.errorReport.cause.length);  
        printf("diagnostics[0]  :   0x%02x\n", 
                           msg.u.trxmMsg.u.errorReport.cause.diagnostics[0]);
        printf("causeValue      :   0x%02x\n", 
                                 msg.u.trxmMsg.u.errorReport.cause.causeVal); 
        fptr = fopen(filename,"r");
        while(feof)
        {
            fgets(line,sizeof(line),fptr);
            if(strcmp(line,"ERRRPT START\n") == 0)
            {
                while (strcmp(fgets(line,sizeof(line),fptr),
                         "ERRRPT END\n") != 0)
                {
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-1"))
                    {
                        printf("msgId           :   0x%02x\n", 
                                            msg.u.trxmMsg.u.errorReport.msgId);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-2"))
                    {
                        printf("chanlBits       :   0x%02x\n", 
                                msg.u.trxmMsg.u.errorReport.chanlNum.chanlBits);
                        printf("timeSlotNum     :   0x%02x\n", 
                             msg.u.trxmMsg.u.errorReport.chanlNum.timeSlotNum);
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0' 
                    && strstr(line,"Optional-3"))
                    {
                        printf("chanlBits       :   0x%02x\n", 
                                 msg.u.trxmMsg.u.errorReport.linkId.chanlBits);
                        printf("NA              :   0x%02x\n", 
                                        msg.u.trxmMsg.u.errorReport.linkId.NA);  
                        printf("Priority        :   0x%02x\n", 
                                  msg.u.trxmMsg.u.errorReport.linkId.priority);
                        printf("SAPI            :   0x%02x\n", 
                                      msg.u.trxmMsg.u.errorReport.linkId.SAPI);
      
                    }
                    if (line[0] == 'O' && line[1] == '\t' && line[2] == '0'
                    && strstr(line,"Optional-4"))
                    {
                        printf("errMsglength    :   0x%02x\n", 
                                   msg.u.trxmMsg.u.errorReport.errMsg.length);
                        printf("recvdMsg[0]     :   0x%02x\n", 
                               msg.u.trxmMsg.u.errorReport.errMsg.recvdMsg[0]);
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
*       Reading the Error Report elements from the file and assigning these
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
*
*/
ITS_INT
ReadErrReport(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
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
    printf("MESSAGE CATEGORY:TRX MANAGEMENT MESSAGES\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    memset(optional,NULL,0);
    fp = fopen(filename,"r");
    CLEAR_TM_TRXM_ER_OPTIONAL_BIT_MAP(msg); 
    while (feof)
    {
        fgets(line,sizeof(line),fp);
        if (strcmp(line,"ERRRPT START\n") == 0)
        {  
            while (strcmp(fgets(line,sizeof(line),fp),
                                        "ERRRPT END\n") != 0)
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
                    SET_TM_TRXM_ER_MESSAGE_IDENTIFIER(msg);
                    sscanf(line,"%c %s",&c,&str);
                    for (i = 0; i < 2; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.errorReport.msgId = temp[i]; 
                        }

                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-2"))
                {
                    optional[2] = 2;
                    SET_TM_TRXM_ER_CHANNEL_NUMBER(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.errorReport.chanlNum.chanlBits = 
                                                                      temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.errorReport.chanlNum.timeSlotNum =
                                                                        temp[i];
                        }

                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-3"))
                {
                    optional[3] = 3;
                    SET_TM_TRXM_ER_LINK_IDENTIFIER(msg);
                    sscanf(line,"%c %s %s %s %s",&c,&str,&str1,&str2,&str3);
                    for (i = 0; i < 4; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.errorReport.linkId.chanlBits = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.errorReport.linkId.NA = temp[i];  
                        }
                        if (i == 2)
                        {
                            l[i] = strtol(str2,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.errorReport.linkId.priority = temp[i];
                        }
                        if (i == 3)
                        {
                            l[i] = strtol(str3,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.errorReport.linkId.SAPI = temp[i];
                        }
                    
    
                    }
                }
                if (line[0]=='O' && line[1] == '\t' && line[2] =='0'
                     && strstr(line,"Optional-4"))
                {
                    optional[4] = 4;
                    SET_TM_TRXM_ER_ERRONEOUS_MSG(msg);
                    sscanf(line,"%c %s %s",&c,&str,&str1);
                    for (i = 0; i < 3; i++)
                    {
                        if (i == 0)
                        {
                            l[i] = strtol(str,NULL,16);
                            temp[i] = (unsigned char)l[i];
                            msg->u.trxmMsg.u.errorReport.errMsg.length = temp[i];
                        }
                        if (i == 1)
                        {
                            l[i] = strtol(str1,NULL,16);
                            temp[i] = (unsigned char)l[i];
                       for(j = 0; 
        j <  msg->u.trxmMsg.u.errorReport.errMsg.length ; j++ )
                            {
                   msg->u.trxmMsg.u.errorReport.errMsg.recvdMsg[j] = temp[i];
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
	     msg->u.trxmMsg.u.errorReport.cause.length = temp[k];
             printf("length          :   0x%02x\n",msg->u.trxmMsg.u.errorReport.cause.length);
        }
	if (k == 4)
        {
             for(i=0; i < msg->u.trxmMsg.u.errorReport.cause.length;i++  )
             { 
	     msg->u.trxmMsg.u.errorReport.cause.diagnostics[i] = temp[k];
             }
             printf("diagnostics[0]  :   0x%02x\n", temp[k]);
        }
        if (k == 5)
        {
             msg->u.trxmMsg.u.overload.causeVal = temp[k];
            printf("causeVal        :   0x%02x\n",msg->u.trxmMsg.u.overload.causeVal);	    
        }
    }

    if (optional[1] == 1)
    {
        printf("msgId           :   0x%02x\n", msg->u.trxmMsg.u.errorReport.msgId);
    }
    if (optional[2] == 2)
    {

        printf("chanlBits       :   0x%02x\n",
                                 msg->u.trxmMsg.u.errorReport.chanlNum.chanlBits);
        printf("timeSlotNum     :   0x%02x\n",
                                msg->u.trxmMsg.u.errorReport.chanlNum.timeSlotNum);
    
    } 
    if (optional[3] == 3)
    {
        printf("chanlBits       :   0x%02x\n", 
                           msg->u.trxmMsg.u.errorReport.linkId.chanlBits);
        printf("NA              :   0x%02x\n",
                                  msg->u.trxmMsg.u.errorReport.linkId.NA);
        printf("priority        :   0x%02x\n",
                                 msg->u.trxmMsg.u.errorReport.linkId.priority);
        printf("SAPI            :   0x%02x\n", 
                                     msg->u.trxmMsg.u.errorReport.linkId.SAPI);

    }
    if (optional[4] == 4)
    {
        printf("msglength       :   0x%02x\n", 
                                  msg->u.trxmMsg.u.errorReport.errMsg.length);
        printf("recievdMsg[0]   :   0x%02x\n",
                            msg->u.trxmMsg.u.errorReport.errMsg.recvdMsg[0]);
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Location Informaton elements from the file,
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
HandleLocInfo(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    FILE *fp;    
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadLocInfo(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Location Information failure ret :: %d\n", ret);
        return ret;
    }
    else
    printf("******************** ENCODED DATA ************************\n");
    {
        printf("Encoding Location Informaton Success ret :: %d\n\n", ret);

        for(i=0; i<len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    printf("********************* DECODED DATA ***********************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Location Information Failed ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Location Information Success ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc         :   0x%02x\n",
                                          msg.genElemnts.msgDesc.msgGruop);
        printf("msgDesc(T)      :   0x%02x\n",
                                         msg.genElemnts.msgDesc.trasparent);
        printf("msgType         :   0x%02x\n", msg.genElemnts.msgType);
        printf("length          :   0x%02x\n",
                                      msg.u.lcsMsg.u.lcsLocInfo.length);
        printf("facIEI[0]       :   0x%02x\n",
                                     msg.u.lcsMsg.u.lcsLocInfo.facIEI[0]);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Reading the Location information elements from the file and assigning
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
*  Name            Date           Reference                  Description
* -------------------------------------------------------------------------
* Sriraghavendra   25-08-2005
*
*
*
*/
ITS_INT
ReadLocInfo(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE * fp)
{
    FILE *fp_ch;
    char line[1024];
    char *tokentab;
    char *tokenspace;
    char *buftab[300];
    char *bufspace[300];
    int i = 0,icount;
    int k = 0,kcount;
    int no_params = 7;
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
    printf("Message Name: LOCATION INFORMATION \n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while((c = fgetc(fp_ch)) != EOF)
    {
        if (c == '\n')
        linecount++;
        if(c == 'M')
        {
            d_tab = fgetc(fp_ch);
            if (d_tab == '\t')
            {

            }
            else if (d_tab == ' ')
            {
                printf("Tab space needed after the mandatory"
                               "parameter at line %d\n",linecount);
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
                no_params = 7; 
                else
                no_params = 6;
            }
            else if(d_tab==' ')
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
        if ( strcmp(line,"LCINF START\n") == 0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"LCINF END\n") != 0)
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
    printf("MESSAGE NAME: LOCATION INFORMATION\n");
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

        if ( bufspace[k][2] >= 'a' && bufspace[k][2] <= 'f'||
        bufspace[k][2] >= '0' && bufspace[k][2] <= '9'&&
        bufspace[k][3] >= 'a' && bufspace[k][3] <= 'f'||
        bufspace[k][3] >= '0' && bufspace[k][3] <= '9')
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
            msg->u.lcsMsg.u.lcsLocInfo.length = temp;
            printf("length          :   0x%02x\n",
                                        msg->u.lcsMsg.u.lcsLocInfo.length);
        }

        if (k == 4)
        {
            l = strtol(bufspace[k],NULL,16);
            temp = (unsigned char)l;
            printf("facIEI[0]       :   0x%02x\n", temp);
            for(i = 0; i < msg->u.lcsMsg.u.lcsLocInfo.length; i++ )
            {
                 msg->u.lcsMsg.u.lcsLocInfo.facIEI[i] = temp;
            }
        }
    }
    fclose(fp);
}


ITS_INT (*testTrafficMsg_TRXM[6])(int) = 
{
    HandleRfrscInd,
    HandleRfrscInd,
    HandleSaachFill,
    HandleOverLoad,
    HandleErrReport,
}
;

ITS_INT (*testTrafficMsg_LCS[2])(int) = 
{
    NULL,
    HandleLocInfo,
}
;















