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
 *  ID: $Id: readRLLM.c,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
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
 *  Revision 1.1.2.4  2005/09/27 12:22:25  mkrishna
 *  Modification done for Error cases - hakshata & raghavendrasm
 *
 *  Revision 1.1.2.3  2005/09/23 07:11:54  mkrishna
 *  Enhancements for Bugs raised - hakshata & sriraghavendrasm
 *
 *  Revision 1.1.2.2  2005/09/15 08:39:46  mkrishna
 *  Read elemnt modified
 *
 *  Revision 1.1.2.1  2005/08/29 08:59:40  mkrishna
 *  Added codec simulator - hakshata & sriraghavendrasm
 *
 *
 ****************************************************************************/

#include <abis_traffic_management.h>
                                                                                                                             
extern FILE *fp;
                                                                                                                             
                                                                                                                            
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
HandleDataReq(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0;
    ITS_OCTET buffer[300];

    /* Read the values from the file */
    ReadDataReq(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
    	printf("****************** ENCODED DATA ****************************\n");
        printf("Encoding Data Request Success  ret :: %d\n\n", ret);
	printEncComRllm(buffer,len);
        printf("\n\n");
    }
                                                                                                                             
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
	printf("****************** DECODED DATA ****************************\n");
	printf("Decoding Data Request Success  ret :: %d\n", ret);
	printDecComRllm(msg);
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the data inidcation information elements from the file,
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
HandleDataInd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadDataInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {	
    	printf("********************ENCODED DATA****************************\n");
        printf("Encoding Data Indication Success  ret :: %d\n\n", ret);
        printEncComRllm(buffer,len);                                                                                                 printf("\n\n");
    }                                                                                                                            
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Data Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        
        printf("****************** DECODED DATA ***************************\n");
	printf("Decoding Data Indication Success  ret :: %d\n", ret);
        printDecComRllm(msg);                                                                                                                     
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Error indication information elements from 
        the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
        buffer - input message while decoding function is being called
                                                                                                                             
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
HandleErrInd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadErrInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Error Indication Failed  ret :: %d\n", ret);
        return ret;  
    }
    else
                                                                                                                             
    printf("******************* ENCODED DATA *****************************\n");
    {
        printf("Encoding Error Indication Success  ret :: %d\n\n", ret);
        /* display buffer */
        printEncComRllm(buffer,len);
        printf("\n\n");
    }
                                                                                                                             
    printf("******************** DECODED DATA ****************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Error Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Error Indication Success  ret :: %d\n", ret);
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printDecOthComRllm(msg);
        
        printf("lengthIden      :   0x%02x\n", msg.u.rllmMsg.u.errorInd.rlmLen);
        printf("causeValue      :   0x%02x\n",msg.u.rllmMsg.u.errorInd.causeVal);
    }
 
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Establish Request information elements from 
        the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
                                                                                                                             
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
*	prints the encoded and decoded values
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
HandleEstReq(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadEstReq(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Establish Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("******************* ENCODED DATA  *******************************\n");
    {
        printf("Encoding Establish Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        printEncComRllm(buffer,len);
        printf("\n\n");
    }
                                                                                                                             
    printf("******************** DECODED DATA *******************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Establish Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Data Request Success  ret :: %d\n", ret);
        printDecOthComRllm(msg);                                                                                                                            
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Establish Configuration information elements from 
        the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called                                                       * INPUT/OUTPUT:
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
HandleEstConf(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadEstConf(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Establish Confirm Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("****************** ENCODED DATA ********************************\n");
    {
        printf("Encoding Establish Confirm  Success  ret :: %d\n\n", ret);
        /* display buffer */
        printEncComRllm(buffer,len);
        printf("\n\n");
    }
                                                                                                                             
    printf("******************  DECODED DATA ******************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Esatblish Confirm Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Esatblish Confirm Success  ret :: %d\n", ret);
        printDecOthComRllm(msg);                                                                                                                            
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the Establish Indication information elements from 
        the file, encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called                                                       *	     prints the encoded and decoded values                                                                     
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
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
HandleEstInd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    int ret_elem = 0;
    ret_elem = ReadEstInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Establish Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {	
    	printf("******************** ENCODED DATA ****************************\n");
        printf("Encoding Establish Indication Success  ret :: %d\n\n", ret);
        printEncComRllm(buffer,len);                                     
        printf("\n\n");
    }
                                                                                                                             
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Establish Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        
        printf("********************* DECODED DATA   ************************\n");
        printf("Decoding Esatblish Indication Success  ret :: %d\n", ret);
        printDecOthComRllm(msg);
        if (ret_elem == 11)
        {
            printf("lengthInd:   0x%02x\n", msg.u.rllmMsg.u.estInd.l3Info.lengthInd);
            printf("LLSDU    :   0x%02x\n", msg.u.rllmMsg.u.estInd.l3Info.LLSDU[0]);
        }
                                                                                                                     
    }
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Handles reading the data inidcation information elements from the file,
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
HandleRelReq(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadRelReq(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Release Request Failed  ret :: %d\n", ret);
        return ret;  
    }
    else
                                                                                                                             
    printf("********************** ENCODED DATA *******************************\n");
    {
        printf("Encoding Release Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        printEncComRllm(buffer,len);                                                                                                 printf("\n\n");
    }
                                                                                                                             
    printf("*********************** DECODED DATA ****************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Release Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Release Request Success  ret :: %d\n", ret);
        printDecOthComRllm(msg);
	printf("Mode bit        :   0x%02x\n", msg.u.rllmMsg.u.relReq.modeBit);
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Release Confirmation information elements from 
*       the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
*       buffer - input message while decoding function is being called
                                                                                                                             
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
*       msg - values to be filled in the msg after parsing
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
HandleRelConf(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadRelConf(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("************************* ENCODED DATA *********************************\n");
    {
        printf("Encoding Data Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        printEncComRllm(buffer,len);                                                                                         
        printf("\n\n");
    }
                                                                                                                             
    printf("************************** DECODED DATA  ********************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Data Request Success  ret :: %d\n", ret);
        printDecOthComRllm(msg);
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the data request information elements from the file, 
        encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
        buffer - input message while decoding function is being called
                                                                                                                             
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
        msg - values to be filled in the msg after parsing
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
HandleRelInd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadRelInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Release Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
                                                                                                                             
    printf("*********************** ENCODED DATA ******************************\n");
    {
        printf("Encoding Release Indication Success  ret :: %d\n\n", ret);
        /* display buffer */
        printEncComRllm(buffer,len);
        printf("\n\n");
    }
                                                                                                                             
    printf("*********************** DECODED DATA ***************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Release Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Release Indication Success  ret :: %d\n", ret);
	printDecOthComRllm(msg);
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Unit Data Request information elements from the file, 
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
HandleUnitDatReq(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadUnitDatReq(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Unit  Data Request Failed  ret :: %d\n", ret);
         return ret;
    }
    else
                                                                                                                             
    printf("******************* * ENCODED DATA **********************\n");
    {
        printf("Encoding Unit Data Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        printEncComRllm(buffer,len);
        printf("\n\n");
    }
                                                                                                                             
    printf("******************** DECODED DATA ***********************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Unit  Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Unit Data Request Success  ret :: %d\n", ret);
        printDecComRllm(msg);
    }
    return ITS_SUCCESS;
}
/*implementation:internal
*
* PURPOSE:
*       Handles reading the Unit Data Indication information elements from 
        the file,encoding and then decoding
* INPUT:
*       msg - input message to be encoded while encoding function called
        buffer - input message while decoding function is being called
                                                                                                                             
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed after calling the encode function
*       size - size of filled buffer
        msg - values to be filled in the msg after parsing
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
HandleUnitDatInd(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[300];
    ReadUnitDatInd(&msg,fp);
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Unit Data Indaication Failed  ret :: %d\n", ret);
         return ret;
    }
    else
                                                                                                                             
    printf("************************* ENCODED DATA ***************************\n");
    {
        printf("Encoding Unit Data Indication Request Success  ret :: %d\n\n", ret);
        /* display buffer */
       printEncComRllm(buffer,len);
       printf("\n\n");
    }
                                                                                                                             
    printf("************************** DECODED DATA *************************\n");
    ret = ABIS_TMM_Decode(&msg,sizeof(buffer),buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Data Request Failed  ret :: %d\n", ret);
          return ret;
    }
    else
    {
        printf("Decoding Data Request Success  ret :: %d\n", ret);
        printDecComRllm(msg);
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
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/
                                                                                                                      
ITS_INT
ReadDataReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=11;
    int linecount=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                                 printf("                        \n");
    printf("Message Name: DATA REQUEST\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while (strcmp(fgets(line,sizeof(line),fp),"DATREQ END\n")!=0)
    {
        if (strcmp(line,"DATREQ START")!=0)
        {
                  printf("%s",line);
                  for ( i=0;i<300;i++)
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
                          /* Do Nothing */
                      }
                      else
                      {
                          printf("Enter tab space after the param at %d\n",linecount);
                          exit(1);
                      }
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
        exit(1);
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: DATA REQUEST\n");
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
             printf("msgDesc      :   0x%02x\n", 
                                            msg->genElemnts.msgDesc.msgGruop);
        }
                                                                                                                             
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T)   :   0x%02x\n",
                                          msg->genElemnts.msgDesc.trasparent);
        }
                                                                                                                             
        if (k==2)
        {
                                                                                                                             
             msg->genElemnts.msgType=temp[k];
             printf("msgType      :   0x%02x\n",msg->genElemnts.msgType);
        }
                                                                                                                             
        if (k==3)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits     :   0x%02x\n",
                            msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum  :   0x%02x\n",
                        msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
                                                                                                                             
        if (k==5)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits     :   0x%02x\n",
                             msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
                                                                                                                             
        if (k==6)
        {
                                                                                                                             
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA            :   0x%02x\n",
                                   msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority      :   0x%02x\n",
                             msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI          :   0x%02x\n",
                                 msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.rllmMsg.u.dataReq.l3Info.lengthInd=temp[k];
            printf("lengthIden    :   0x%02x\n",
                                  msg->u.rllmMsg.u.dataReq.l3Info.lengthInd);
        }
                                                                                                                             
        if (k==10)
        {
            printf("LLSDU         :   0x%02x\n",temp[k]);
            for(l3count=0;l3count<msg->u.rllmMsg.u.dataReq.l3Info.lengthInd;l3count++)
            {
               msg->u.rllmMsg.u.dataReq.l3Info.LLSDU[l3count] = temp[k];
            }
                                                                                                                             
                                                                                                                             
        }
                                                                                                                             
     }
    fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       This function reads the data indication information elements from the
        file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS: none
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
ReadDataInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300], *bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=11;
    int linecount=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;                                                                                                                            
    printf("                        \n");
    printf("Message Name: DATA INDICATION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"DATIND START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"DATIND END\n")!=0)
            {
                printf("%s",line);
                for ( i=0;i<300;i++)
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
                         /* Do Nothing */
                    }
                    else
                    {
                         printf("tab space after the parameter at %d\n",linecount);
                         exit(1);
                    }
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
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: DATA INDICATION\n");
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
                                                                                                                             
        if ( bufspace[k][2]>='a' && bufspace[k][2]<='f' ||  bufspace[k][2]>='0'
             && bufspace[k][2]<='9' && bufspace[k][3]>='a' && bufspace[k][3]<='f' 
             || bufspace[k][3]>='0' && bufspace[k][3]<='9' )
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
             printf("msgDesc   :   0x%02x\n", msg->genElemnts.msgDesc.msgGruop);
        }
                                                                                                                             
        if (k==1)
        {
             msg->genElemnts.msgDesc.trasparent=temp[k];
             printf("msgdesc(T):   0x%02x\n",msg->genElemnts.msgDesc.trasparent);
        }
                                                                                                                             
        if (k==2)
        {
             msg->genElemnts.msgType=temp[k];
             printf("msgType   :   0x%02x\n",msg->genElemnts.msgType);
        }
                                                                                                                             
        if (k==3)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];
             printf("chanBits  :   0x%02x\n",
                              msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        }
                                                                                                                             
        if (k==4)
        {
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum=temp[k];
             printf("timeSlotNum:   0x%02x\n",
                              msg->u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        }
                                                                                                                             
        if (k==5)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits  :   0x%02x\n",
                                  msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
                                                                                                                             
        if (k==6)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA         :   0x%02x\n",
                                  msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority   :   0x%02x\n",
                                 msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI       :   0x%02x\n",
                                    msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.rllmMsg.u.dataReq.l3Info.lengthInd=temp[k];
            printf("lengthIden      :   0x%02x\n",
                                     msg->u.rllmMsg.u.dataReq.l3Info.lengthInd);
        }
                                                                                                                             
        if (k==10)
        {
            printf("LLSDU           :   0x%02x\n",temp[k]);
            for(l3count=0;l3count<msg->u.rllmMsg.u.dataReq.l3Info.lengthInd;l3count++)
            {
               msg->u.rllmMsg.u.dataReq.l3Info.LLSDU[l3count] = temp[k];
            }
                                                                                                                             
                                                                                                                             
        }
                                                                                                                             
     }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       This function reads the Error Indication information elements from the
        file
* INPUT:
*       msg - pointer to the traffic management srtucture to stor the values 
        read from file
        fp - Pointer to the file from where the information elements are read
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:none
* COMMENTS:
*       none
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  26-08-2005
*
*
*/

ITS_INT
ReadErrInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300], *bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=11;
    int linecount=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: ERROR INDICATION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"ERRIND START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"ERRIND END\n")!=0)
            {
                printf("%s",line);
                for ( i=0;i<300;i++)
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
                         /* Do Nothing */
                    }
                    else
                    {
                         printf("tab space needed after the parameter at %d\n",linecount);
                         exit(1);
                    }
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
    if (kcount == no_params)
    {
                                                                                                                             
    }
    else
    {
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: ERROR INDICATION\n");
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
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits       :   0x%02x\n",
                                        msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
                                                                                                                             
        if (k==6)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA              :   0x%02x\n",
                                        msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority        :   0x%02x\n",
                                        msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI            :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.rllmMsg.u.errorInd.rlmLen = temp[k];
            printf("lengthIden      :   0x%02x\n", msg->u.rllmMsg.u.errorInd.rlmLen); 
        }
                                                                                                                             
        if (k==10)
        {
             
            l[k]=strtol(bufspace[k],NULL,16);
            temp[k]=(ITS_USHORT)l[k];
            msg->u.rllmMsg.u.errorInd.causeVal = temp[k];
            printf("causeValue           :   0x%02x\n",msg->u.rllmMsg.u.errorInd.causeVal);
            //<<Added 
            /*if (msg->u.rllmMsg.u.errorInd.causeVal == 0xff || msg->u.rllmMsg.u.errorInd.causeVal == 0x80)        
            {
                printf("The other octet is 0x%02x\n",temp[11]);
                 
                msg->u.rllmMsg.u.errorInd.causeVal = temp[11];
               
            }*/
    
        }
     }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       This function reads the Establish Request information elements from the
*       file
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
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
ReadEstReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300], *bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=9;
    int linecount=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: ESTABLISH REQUEST\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");

    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"ESTREQ START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"ESTREQ END\n")!=0)
            {
                printf("%s",line);
                for ( i=0;i<300;i++)
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
                         /* Do Nothing */
                    }
                    else
                    {
                         printf("tab space needed after the parameter at %d\n",linecount);
                         exit(1);
                    }
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
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: ESTABLISH REQUEST\n");
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
             printf("msgDesc         :   0x%02x\n", 
                                         msg->genElemnts.msgDesc.msgGruop) ;
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
             printf("msgType         :   0x%02x\n",
                                                  msg->genElemnts.msgType);
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
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits       :   0x%02x\n",
                             msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
                                                                                                                             
        if (k==6)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA              :   0x%02x\n",
                                    msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority        :   0x%02x\n",
                                    msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI            :   0x%02x\n",
                                        msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                             
    }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       This function reads the establish configuration information elements 
*       from the file
* INPUT:
*       msg - input message to be encoded
*       fp - file pointer where the values for the elems are fed
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
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
ReadEstConf(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=9;
    int linecount=0;
   
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                             
                                                                                                                             
    printf("                        \n");
    printf("Message Name: ESTABLISH CONFIRM\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"ESTCONF START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"ESTCONF END\n")!=0)
            {
                printf("%s",line);
                 for ( i=0;i<300;i++)
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
                         /* Do Nothing */
                    }
                    else
                    {
                         printf("tab space after the parameter at %d\n",linecount);
                         exit(1);
                    }
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
    if (kcount == no_params)
    {
                                                                                                                             
    }
    else
    {
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: ESTABLISH CONFIRM\n");
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
             printf("msgDesc         :   0x%02x\n", 
                                             msg->genElemnts.msgDesc.msgGruop) ;
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
             printf("msgType         :     0x%02x\n",msg->genElemnts.msgType);
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
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits       :   0x%02x\n",
                              msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
         
        if (k==6)
        {
                                                                                                                             
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA              :   0x%02x\n",
                                 msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority        :   0x%02x\n",
                                msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI            :   0x%02x\n",
                                msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                             
    }
    fclose(fp);
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
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/

ITS_INT
ReadEstInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params = 0;
    int linecount = 0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                             
                                                                                                                             
    printf("                        \n");
    printf("Message Name: ESTABLISH INDICATION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"ESTAIND START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"ESTAIND END\n")!=0)
            {
                printf("%s",line);
                for (i=0;i<300;i++)
                {
                    if (line[i] == '\n');
                    {
                        linecount++;
                    }
                }
                if (line[0] == 'M' || line[0] == 'O')
                {
                    if (line[1] == '\t')
                    {
                    
                    }
                    else
                    {
                        printf("tab space after parameter at %d\n",linecount);
                        exit(1);
                    }
                } 
                  
                if (line[0] == 'O' && line[1] == '\t' && line[2] == '0')
                {
                    no_params=11;
                }
                else
                { 
                    no_params=9;
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
    icount=i;
    kcount=k;
    if (kcount==no_params)
    {
                                                                                                                             
    }
    else
    {
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME:ESTABLISH INDICATION\n");
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
             printf("msgDesc         :   0x%02x\n", 
                                         msg->genElemnts.msgDesc.msgGruop) ;
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
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits       :   0x%02x\n",
                           msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
                                                                                                                             
        if (k==6)
        {
                                                                                                                             
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA              :   0x%02x\n",
                                 msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority        :   0x%02x\n",
                                msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
                                                                                                                             
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI            :   0x%02x\n",
                                 msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                             
        if (k==9)
        {   
            CLEAR_TM_RLLM_EI_OPTIONAL_BIT_MAP((msg));
            SET_TM_RLLM_EI_L3_INFO((msg));
            msg->u.rllmMsg.u.estInd.l3Info.lengthInd=temp[k];
            printf("lengthIden      :   0x%02x\n",
                                    msg->u.rllmMsg.u.estInd.l3Info.lengthInd);
        }
                                                                                                                             
        if (k==10)
        {
            printf("LLSDU           :   0x%02x\n",temp[k]);
            for(l3count=0;l3count<msg->u.rllmMsg.u.estInd.l3Info.lengthInd;l3count++)
            {
               msg->u.rllmMsg.u.estInd.l3Info.LLSDU[l3count] = temp[k];
            }
                                                                                                                             
                                                                                                                             
        }
                                                                                                                             
     }
    fclose(fp);
    return no_params;
}


/*implementation:internal
*
* PURPOSE:
*       This function reads the Release Request information elements from the
        file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
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
ReadRelReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=11;
    int linecount=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: RELEASE REQUEST\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"RELREQ START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"RELREQ END\n")!=0)
            {
                printf("%s",line);
                for (i=0;i<300;i++)
                {
                    if (line[i] == '\n');
                    {
                        linecount++;
                    }
                }
                if (line[0] == 'M' || line[0] == 'O')
                {
                    if (line[1] == '\t')
                    {
                                                                                                                             
                    }
                    else
                    {
                        printf("tab space needed after parameter at %d\n",linecount);
                        exit(1);
                    }
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
    if (kcount == no_params)
    {
                                                                                                                             
    }
    else
    {
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: RELEASE REQUEST\n");
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
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits       :   0x%02x\n",
                                    msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
         
                                                                                                  
        if (k==6)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA              :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority        :   0x%02x\n",
                                             msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI            :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
        if (k==9)
        {
           msg->u.rllmMsg.u.relReq.modeBit=temp[k];
           printf("Mode bit        :   0x%02x\n",msg->u.rllmMsg.u.relReq.modeBit);
        }                                                                                                                        }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       This function reads the release confirm information elements from the
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
*/
ITS_INT
ReadRelConf(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=9;
    int linecount=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: RELEASE CONFIRM\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"RELCONF START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"RELCONF END\n")!=0)
            {
                printf("%s",line);
                for (i=0;i<300;i++)
                {
                    if (line[i] == '\n');
                    {
                        linecount++;
                    }
                }
                if (line[0] == 'M' || line[0] == 'O')
                {
                    if (line[1] == '\t')
                    {
                                                                                                                             
                    }
                    else
                    {
                        printf("tab space needed after parameter at %d\n",linecount);
                        exit(1);
                    }
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
    if (kcount == no_params)
    {
                                                                                                                             
    }
    else
    {
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: RELEASE CONFIRM\n");
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
                                                                                                                             
             msg->u.rllmMsg.rllmGenElements.chanlNum.chanlBits=temp[k];                                                                   printf("chanBits        :   0x%02x\n",
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
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits       :   0x%02x\n",
                                         msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
                                                                                                                             
        if (k==6)
        {
                                                                                                                             
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA              :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority        :   0x%02x\n",
                                        msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI            :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                                 }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       This function reads the Release Indication information elements from the
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
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/
ITS_INT
ReadRelInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=9;
    int linecount=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                             
    printf("                        \n");
    printf("Message Name: RELEASE INDICATION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"RELIND START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"RELIND END\n")!=0)
            {
                printf("%s",line);
                for (i=0;i<300;i++)
                {
                    if (line[i] == '\n');
                    {
                        linecount++;
                    }
                }
                if (line[0] == 'M' || line[0] == 'O')
                {
                    if (line[1] == '\t')
                    {
                                                                                                                             
                    }
                    else
                    {
                        printf("tab space needed after parameter at %d\n",linecount);
                        exit(1);
                    }
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
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME: RELEASE INDICATION\n");
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
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits       :   0x%02x\n",
                                        msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
                                                                                                                             
        if (k==6)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA              :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority        :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI            :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                             
                                                                                                                               
     }
    fclose(fp);
}

/*implementation:internal
*
* PURPOSE:
*       This function reads the Unit Data Request information elements from the
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
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Akshata  24-08-2005
*
*
*/
ITS_INT
ReadUnitDatReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=11;
    int linecount=0;
    
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                             
    printf("                        \n");
    printf("Message Name:UNIT DATA REQUEST\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"UNITDATREQ START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"UNITDATREQ END\n")!=0)
            {
                printf("%s",line);
                for (i=0;i<300;i++)
                {
                    if (line[i] == '\n');
                    {
                        linecount++;
                    }
                }
                if (line[0] == 'M' || line[0] == 'O')
                {
                    if (line[1] == '\t')
                    {
                                                                                                                             
                    }
                    else
                    {
                        printf("tab space needed after parameter at %d\n",linecount);
                        exit(1);
                    }
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
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME:UNIT DATA REQUEST\n");
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
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits       :   0x%02x\n",
                                          msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
                                                                                                                             
        if (k==6)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA              :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority        :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI            :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.rllmMsg.u.dataReq.l3Info.lengthInd=temp[k];
            printf("lengthIden      :   0x%02x\n",msg->u.rllmMsg.u.dataReq.l3Info.lengthInd);
        }
                                                                                                                             
        if (k==10)
        {
            printf("LLSDU           :   0x%02x\n",temp[k]);
            for(l3count=0;l3count<msg->u.rllmMsg.u.dataReq.l3Info.lengthInd;l3count++)
            {
               msg->u.rllmMsg.u.dataReq.l3Info.LLSDU[l3count] = temp[k];
            }
                                                                                                                             
                                                                                                                             
        }
                                                                                                                             
     }
    fclose(fp);
}
/*implementation:internal
*
* PURPOSE:
*       This function reads the Unit Data Indication information elements from the
        file
* INPUT:
*       msg - input message to be encoded
        fp - file pointer where the values for the elems are fed
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       The values of the information elements are printed onto the std
*       output
* RETURNS:
*       none
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
ReadUnitDatInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg,FILE *fp)
{
    char line[1024];
    char *tokentab,*tokenspace;
    char *buftab[300],*bufspace[300];
    int i=0,icount;
    int k=0,kcount;
    int no_params=11;
    int linecount=0;
    unsigned char buffer[300];
    unsigned char temp[300];
    long l[300];
    int l3count;
                                                                                                                             
    printf("                        \n");
    printf("Message Name:UNIT DATA INDICATION\n");
    printf("                        \n");
    printf("Reading from file...\n");
    printf("                        \n");
    while(feof)
    {
        fgets(line,sizeof(line),fp);
        if(strcmp(line,"UNITDATIND START\n")==0)
        {
            while (strcmp(fgets(line,sizeof(line),fp),"UNITDATIND END\n")!=0)
            {
                printf("%s",line);
                  for (i=0;i<300;i++)
                {
                    if (line[i] == '\n');
                    {
                        linecount++;
                    }
                }
                if (line[0] == 'M' || line[0] == 'O')
                {
                    if (line[1] == '\t')
                    {
                                                                                                                             
                    }
                    else
                    {
                        printf("tab space needed after parameter at %d\n",linecount);
                        exit(1);
                    }
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
        printf("Encoded string missing\n");
    }
    printf("VALUES OF INFORMATION ELEMENTS READ FROM FILE ARE AS FOLLOWS...\n");
    printf("MESSAGE NAME:UNIT DATA INDICATION\n");
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

        l[k] = strtol(bufspace[k],NULL,16);
        temp[k] = (unsigned char)l[k];                                                                                                                                                                                                                            if (k==0)
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
            msg->u.rllmMsg.rllmGenElements.linkId.chanlBits=temp[k];
            printf("chanlBits   :   0x%02x\n",
                                  msg->u.rllmMsg.rllmGenElements.linkId.chanlBits);
        }
                                                                                                                             
        if (k==6)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.NA=temp[k];
            printf("NA          :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.NA);
        }
                                                                                                                             
        if (k==7)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.priority=temp[k];
            printf("priority    :   0x%02x\n",
                                  msg->u.rllmMsg.rllmGenElements.linkId.priority);
        }
                                                                                                                             
        if (k==8)
        {
            msg->u.rllmMsg.rllmGenElements.linkId.SAPI=temp[k];
            printf("SAPI        :   0x%02x\n",msg->u.rllmMsg.rllmGenElements.linkId.SAPI);
        }
                                                                                                                             
        if (k==9)
        {
            msg->u.rllmMsg.u.dataReq.l3Info.lengthInd=temp[k];
            printf("lengthIden  :   0x%02x\n",msg->u.rllmMsg.u.dataReq.l3Info.lengthInd);
        }
                                                                                                                             
        if (k==10)
        {
            printf("LLSDU       :   0x%02x\n",temp[k]);
            for(l3count=0;l3count<msg->u.rllmMsg.u.dataReq.l3Info.lengthInd;l3count++)
            {
               msg->u.rllmMsg.u.dataReq.l3Info.LLSDU[l3count] = temp[k];
            }
                                                                                                                             
                                                                                                                             
        }
                                                                                                                             
     }
    fclose(fp);
}

ITS_INT
printEncComRllm(ITS_OCTET *buffer,ITS_INT len)
{
    int i=0;
    for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
    return;
}
                                                                                                                             
ITS_INT
printDecComRllm(ABIS_TRAFFIC_MANAGEMENT_MSG msg)
{
    printf("PARAMETER NAMES\t   VALUES\n");
    printf("---------------\t   ------\n");
    printf("msgDesc     :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
    printf("msgDesc(T)  :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
    printf("msgType     :   0x%02x\n", msg.genElemnts.msgType);
    printf("chanlBits   :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
    printf("timeSlotNum :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
    printf("chanlBits   :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.linkId.chanlBits);
    printf("NA          :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.linkId.NA);
    printf("priority    :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.linkId.priority);
    printf("SAPI        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.linkId.SAPI);
    printf("lengthInd   :   0x%02x\n", msg.u.rllmMsg.u.dataReq.l3Info.lengthInd);
    printf("LLSDU       :   0x%02x\n", msg.u.rllmMsg.u.dataReq.l3Info.LLSDU[0]);
    return;
}

ITS_INT
printDecOthComRllm(ABIS_TRAFFIC_MANAGEMENT_MSG msg)
{
        printf("PARAMETER NAMES\t   VALUES\n");
        printf("---------------\t   ------\n");
        printf("msgDesc     :   0x%02x\n", msg.genElemnts.msgDesc.msgGruop) ;
        printf("msgDesc(T)  :   0x%02x\n", msg.genElemnts.msgDesc.trasparent) ;
        printf("msgType     :   0x%02x\n", msg.genElemnts.msgType);
        printf("chanlBits   :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.chanlBits);
        printf("timeSlotNu  :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.chanlNum.timeSlotNum);
        printf("chanlBits   :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.linkId.chanlBits);
        printf("NA          :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.linkId.NA);
        printf("priority    :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.linkId.priority);
        printf("SAPI        :   0x%02x\n", msg.u.rllmMsg.rllmGenElements.linkId.SAPI);
}






ITS_INT (*testTrafficMsg_RLLM[42])(int) = {
					      HandleDataReq,
                                              HandleDataReq,
				              HandleDataInd,
                                              HandleErrInd,
					      HandleEstReq,
					      HandleEstConf,
					      HandleEstInd,         
					      HandleRelReq,
					      HandleRelConf,
					      HandleRelInd,
					      HandleUnitDatReq,
					      HandleUnitDatInd
				          };  
                                                                                                                         

