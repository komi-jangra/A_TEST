/****************************************************************************
 *                                                                          *
 *     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: tcap_clientimpl.c
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/08 11:12:27  bsccs2
 * Init Code
 *
 * Revision 1.1.1.1  2007/10/04 13:25:04  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
 * BscCs2
 *
 * Revision 1.6  2007/04/17 08:35:44  ashutosh.singh
 * Logger Lib related changes
 *
 * Revision 1.5  2007/03/20 04:49:37  ashutosh.singh
 * Trace and DTAP Messages handling  related changes
 *
 * Revision 1.4  2007/03/06 08:04:02  cvsadmin
 * Added  the Traces
 *
 * Revision 1.3  2007/02/16 05:06:38  cvsadmin
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/17 04:31:46  ashutosh.singh
 * *** empty log message ***
 *
 * Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * Initialising sources in CVS
 *
 * Revision 1.1  2003/10/07 12:46:08  sswami
 * TCAP multiple App binding Client Implementation
 *
 *
 ****************************************************************************/
#include <tcap_clientimpl.h>
#include <its_hash.h>
#include <its_mutex.h>
#include <stdlib.h>
#include <its_transports.h>
#include <its_ss7_trans.h>
#include "trace.h"
extern ITS_MUTEX CL_WriteMutexLock;
extern ITS_MUTEX CL_ReadMutexLock;
extern ITS_MUTEX SCMCL_WriteMutexLock;
extern void  ISIL_TRACE(int trace ,const char *ftstring, ...);

static char* sync_data = "ISS7SSI";
static int   sd_len = 7;

ITS_USHORT did = 0;

SS7TRAN_Manager* ISS7_ANSI_Stack;
#define ISS7_Stack         ISS7_ANSI_Stack
#define ISIL_TRACE_DEBUG   0x01
#define ISIL_TRACE_ERROR   0x02
#define ISIL_TRACE_WARNING 0x03


ITS_MUTEX CL_Mtp3ReadMutexLock;
ITS_MUTEX CL_SccpReadMutexLock;
ITS_MUTEX CL_TcapReadMutexLock;
int CL_WriteEventIsup(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_WriteEventMtp3(ITS_HANDLE handle, ITS_EVENT *evt);

int CL_WriteEventSccp(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_WriteEventTcap(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_WriteEventMM(ITS_HANDLE handle, ITS_EVENT *evt);

int CL_ReadEventMM(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_ReadEventMtp3(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_ReadEventIsup(ITS_HANDLE handle, ITS_EVENT *evt);

int CL_ReadEventSccp(ITS_HANDLE handle, ITS_EVENT *evt);
int CL_ReadEventTcap(ITS_HANDLE handle, ITS_EVENT *evt);





/*******************************************************************/


int CL_WriteEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nrite,i;
    ITS_USHORT tmp =0;

    if (CL_SockInfo == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* today I don't have to use handle, may be in future 
     * we might have to use
     */

    MUTEX_AcquireMutex(&CL_WriteMutexLock);

    nrite = SOCK_Write(CL_SockInfo, sync_data, sd_len); 
    if (nrite != sd_len)
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Write(CL_SockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->len);

    nrite = SOCK_Write(CL_SockInfo, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(CL_SockInfo, (char *)evt->data, evt->len);
           for( i = 0; i < evt->len; i++)
   {
       printf("%x ", evt->data[i]);
   }

        if (nrite != (int)evt->len)
        {
            MUTEX_ReleaseMutex(&CL_WriteMutexLock);
            return (ITS_ESENDFAIL);
        }
    }

 
    /* Free the event*/
    if (evt->data)
    {
        ITS_Free(evt->data);
        evt->data =0;
    }
    MUTEX_ReleaseMutex(&CL_WriteMutexLock);
    return ITS_SUCCESS;
}
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method Reads the data from server
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt    -  event 
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *      evt - type ITS_EVENT *.
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 * 
 *  See Also:
 *
 ****************************************************************************/
int CL_ReadEvent(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nread = 0, ret =0,j;
    char buf;
    ITS_USHORT tmp =0;
    ITS_BOOLEAN firstTime = ITS_TRUE;
    unsigned i, dosCount;
 /*       for( j = 0; j < evt->len; i++)
                {
                        printf("%x ", evt->data[j]);
                }
*/
    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    MUTEX_AcquireMutex(&CL_ReadMutexLock);

    /* synchronize the stream */
    for (i = 0, dosCount = 0;
         i < (unsigned)sd_len && dosCount < ITS_MAX_EVENT_SIZE;
         i++, dosCount++)
    {
        /*
         * this should be the blocking point
         */
         
            firstTime = ITS_FALSE; //ANAND
        if (firstTime)
        {
            ITS_SockPollInfo info;

repeat:
            memset(&info, 0, sizeof(info));

            info.lookFor = SOCK_POLL_READ;
            info.sinfo = CL_SockInfo;

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * 1000);
            if (ret < ITS_SUCCESS)
            {
                MUTEX_ReleaseMutex(&CL_ReadMutexLock);
                return (ITS_ERCVFAIL);
            }

            if (ret == 0)
            {
                goto repeat;
            }

            firstTime = ITS_FALSE;
        }

   //  ret = SOCK_Read(CL_SockInfo, &buf, sizeof(char));
       //ANAND
        ret = SOCK_Read(handle, &buf, sizeof(char));

        if (ret != sizeof(char))
        {
            MUTEX_ReleaseMutex(&CL_ReadMutexLock);
            return (ITS_ERCVFAIL);
        }

        if (buf != sync_data[i])
        {
            i = ~0U;
            continue;
        }
    }

    /* Here we are so successfully received ISS7SSI*/ 

    /* read the source */
   // nread = SOCK_Read(CL_SockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    nread = SOCK_Read(handle, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ERCVFAIL);
    }

    evt->src = SOCK_NToHS(tmp);

    /* read the length */
   nread = SOCK_Read(handle, (char *)&tmp, sizeof(ITS_USHORT));
  // nread = SOCK_Read(CL_SockInfo, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ERCVFAIL);
    }

    evt->len = SOCK_NToHS(tmp);

    evt->data = (ITS_OCTET *)ITS_Malloc(evt->len);
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ENOMEM);
    }

    /* read the data */
    if (evt->len)
    {
    //    nread = SOCK_Read(CL_SockInfo, (char *)evt->data, evt->len);
       nread = SOCK_Read(handle, (char *)evt->data, evt->len);

        if (nread != evt->len)
        {
            ITS_Free(evt->data);
            evt->data = NULL;

            MUTEX_ReleaseMutex(&CL_ReadMutexLock);
            return (ITS_ERCVFAIL);
        }
    }
    MUTEX_ReleaseMutex(&CL_ReadMutexLock);
    return ITS_SUCCESS;
}





int CL_WriteEventIsup(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nrite=0,i;
    ITS_SocketInfo * CL_Sock = NULL;
    CL_Sock = (ITS_SocketInfo *)handle;
      ITS_INT count;
    ITS_OCTET *buff;
    ITS_OCTET TempBuffer[10];
 
    if (CL_Sock == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    MUTEX_AcquireMutex(&CL_WriteMutexLock);
    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(CL_Sock, (char *)evt->data, evt->len);

        if (nrite != (int)evt->len)
        {
            MUTEX_ReleaseMutex(&CL_WriteMutexLock);
            return (ITS_ESENDFAIL);
        }
    }
     buff = (ITS_OCTET*)calloc(evt->len*6+1, sizeof(ITS_OCTET));

       for (count = 0; count < evt->len; count++)
         {
             sprintf((char *)TempBuffer, "0x%02x ",evt->data[count]);
             strcat((char*)buff,(const char *)TempBuffer);
             if (!(count % 15))
               {
                 strcat((char *)buff,"\n");
               }
           }

          ISIL_DEBUG_TRACE(("\nData send to ISUP:-\n\n%s\n\n",buff));
          free(buff);

     /* ISIL_DEBUG_TRACE(("Data send to ISUP :-\n"));
     for( i = 0; i < evt->len; i++)
     {
       printf("%02x ", evt->data[i]);
     }
    printf("\n");
   */
    /* Free the event*/
    if (evt->data)
    {
        ITS_Free(evt->data);
        evt->data =0;
    }
       
    MUTEX_ReleaseMutex(&CL_WriteMutexLock);
    return ITS_SUCCESS;
}


int CL_WriteEventMtp3(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nrite,i;
    ITS_USHORT tmp =0;
    ITS_SocketInfo * CL_Sock = NULL;
    CL_Sock = (ITS_SocketInfo *)handle; 
    

    if (CL_Sock == NULL)
    {
        return ITS_EINVALIDARGS;

    }

    /* today I don't have to use handle, may be in future 
     * we might have to use
     */

    MUTEX_AcquireMutex(&CL_WriteMutexLock);

    nrite = SOCK_Write(CL_Sock, sync_data, sd_len); 
    if (nrite != sd_len)
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Write(CL_Sock, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->len);

    nrite = SOCK_Write(CL_Sock, (char *)&tmp, sizeof(ITS_USHORT)); 
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }
    printf("MSG GOING FOR MTP3\n");
    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(CL_Sock, (char *)evt->data, evt->len);
           for( i = 0; i < evt->len; i++)
   {
       printf("%x ", evt->data[i]);
    } 

         printf("\n/************************************************/\n");
         printf("/*******************MSG FOR MTP3********************/\n");
         printf("/**************************************************/\n");

        if (nrite != (int)evt->len)
        {
            MUTEX_ReleaseMutex(&CL_WriteMutexLock);
            return (ITS_ESENDFAIL);
        }
    }

 
    /* Free the event*/
    if (evt->data)
    {
        ITS_Free(evt->data);
        evt->data =0;
    }
    MUTEX_ReleaseMutex(&CL_WriteMutexLock);
    return ITS_SUCCESS;
}

int CL_WriteEventTcap(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nrite=0,i;
    ITS_SocketInfo * CL_Sock = NULL;
    CL_Sock = (ITS_SocketInfo *)handle;
    ITS_INT count;
    ITS_OCTET *buff;
    ITS_OCTET TempBuffer[10];


    if (CL_Sock == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    MUTEX_AcquireMutex(&CL_WriteMutexLock);
    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(CL_Sock, (char *)evt->data, evt->len);

        if (nrite != (int)evt->len)
        {
            MUTEX_ReleaseMutex(&CL_WriteMutexLock);
            return (ITS_ESENDFAIL);
        }
    }
#if 0    
     buff = (ITS_OCTET*)calloc(evt->len*6+1, sizeof(ITS_OCTET));

       for (count = 0; count < evt->len; count++)
         {
             sprintf((char *)TempBuffer, "0x%02x ",evt->data[count]);
             strcat((char*)buff,(const char *)TempBuffer);
             if (!(count % 15))
               {
                 strcat((char *)buff,"\n");
               }
           }

          ISIL_DEBUG_TRACE(("Data send to TCAP:-\n\n%s\n\n",buff));
          free(buff);
#endif	  

 /*     ISIL_DEBUG_TRACE(("Data send to TCAP :-\n"));
   
     for( i = 0; i < evt->len; i++)
     {
       printf("%02x ", evt->data[i]);
     }
     printf("\n");*/

    /* Free the event*/
    if (evt->data)
    {
        free(evt->data);
        evt->data =0;
    }

    MUTEX_ReleaseMutex(&CL_WriteMutexLock);
    return ITS_SUCCESS;
}


int CL_WriteEventSccp(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nrite,i;
    ITS_USHORT tmp =0;
    ITS_SocketInfo * CL_Sock = NULL;
    CL_Sock = (ITS_SocketInfo *)handle;
    ITS_EVENT *event;

    if (CL_Sock == NULL)
    {
        return ITS_EINVALIDARGS;

    }

    /* today I don't have to use handle, may be in future 
     * we might have to use
*/
    MUTEX_AcquireMutex(&CL_WriteMutexLock);

    nrite = SOCK_Write(CL_Sock, sync_data, sd_len);
    if (nrite != sd_len)
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->src);

    nrite = SOCK_Write(CL_Sock, (char *)&tmp, sizeof(ITS_USHORT));
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }

    tmp = SOCK_HToNS(evt->len);

    nrite = SOCK_Write(CL_Sock, (char *)&tmp, sizeof(ITS_USHORT));
    if (nrite != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_WriteMutexLock);
        return ITS_ESENDFAIL;
    }  
    printf("\n\n");
    printf("\n MSG GOING FOR SCCP\n");

    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(CL_Sock, (char *)evt->data, evt->len);
           for( i = 0; i < evt->len; i++)
   {
       printf("%x ", evt->data[i]);
   }

   printf("\n/*****************************************************/\n");
   printf("/*******************MSG FOR SCCP ************************/\n");
   printf("/*********************************************************/\n");
        if (nrite != (int)evt->len)
        {
             printf("******#######********");
            MUTEX_ReleaseMutex(&CL_WriteMutexLock);
            return (ITS_ESENDFAIL);
        }
    }

    /* Free the event*/
    if (evt->data)
    {
        free(evt->data);
        evt->data =0;
    }
    MUTEX_ReleaseMutex(&CL_WriteMutexLock);
    return ITS_SUCCESS;

}

                                                       
/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method Reads the data from server
 *
 *  Input Parameters:
 *      handle - ITS_HANDLE
 *      evt    -  event 
 *
 *  Output Parameters:
 *      None.
 *  In/Out Parm:
 *      evt - type ITS_EVENT *.
 *
 *  Return Value:
 *      returns ITS_SUCCES on success.
 *
 *  Notes:
 * 
 *  See Also:
 *
 ****************************************************************************/


int CL_ReadEventIsup(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nread = 0, ret =0;
    unsigned short len;
    unsigned char  buffer[5];

    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

        evt->len =0;
    MUTEX_AcquireMutex(&CL_ReadMutexLock);

/*    printf("Data: \n\n  ");*/
    ret = SOCK_NonBlockingRead(handle,buffer,5,5);
    if (ret != 5)
     {
         MUTEX_ReleaseMutex(&CL_ReadMutexLock);
         return ITS_SUCCESS;
     }

   printf("\n\n\nISIL_TRACE:MSG PARMETER FORM ISUP :-\n\n");
    printf(" api_id=%d\t", buffer[0]);
    printf(" api.ver=%d\t",  buffer[1]);
    printf(" element=%d\t",  buffer[2]);
    len  =  buffer[3] | buffer[4] << 8;
    printf(" len =%d\t", (len));  

    /* read the data */

/*    if (len==0 || len<1000)
    {*/

     evt->data = (ITS_OCTET *)ITS_Malloc(len );
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ENOMEM);
    }
        evt->len= len ;
        memcpy(evt->data ,(char *)buffer  ,5);
        nread = SOCK_NonBlockingRead(handle, (char *)(evt->data + 5), len-5 ,5);
        if (nread != len-5)
        {
            ITS_Free(evt->data);
            evt->data = NULL;
            MUTEX_ReleaseMutex(&CL_ReadMutexLock);
            return (ITS_ERCVFAIL);
        }
   /* }*/
    MUTEX_ReleaseMutex(&CL_ReadMutexLock);
    return ITS_SUCCESS;
}



int CL_ReadEventMtp3(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nread = 0, ret =0,j;
    char buf;
    ITS_USHORT tmp =0;
    ITS_BOOLEAN firstTime = ITS_TRUE;
    unsigned i, dosCount;
    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    MUTEX_AcquireMutex(&CL_Mtp3ReadMutexLock);

    /* synchronize the stream */
    for (i = 0, dosCount = 0;
         i < (unsigned)sd_len && dosCount < ITS_MAX_EVENT_SIZE;
         i++, dosCount++)
    {
        /*
         * this should be the blocking point
         */
         
            firstTime = ITS_FALSE; //ANAND
        if (firstTime)
        {
            ITS_SockPollInfo info;

    repeat:
            memset(&info, 0, sizeof(info));

            info.lookFor = SOCK_POLL_READ;
            info.sinfo = handle;

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * 1000);
            if (ret < ITS_SUCCESS)
            {
                MUTEX_ReleaseMutex(&CL_Mtp3ReadMutexLock);
                return (ITS_ERCVFAIL);
            }

            if (ret == 0)
            {
                goto repeat;
            }

            firstTime = ITS_FALSE;
        }

        ret = SOCK_Read(handle, &buf, sizeof(char));

        if (ret != sizeof(char))
        {
            MUTEX_ReleaseMutex(&CL_Mtp3ReadMutexLock);
            return (ITS_ERCVFAIL);
        }

        if (buf != sync_data[i])
        {
            i = ~0U;
            continue;
        }
    }

    /* Here we are so successfully received ISS7SSI*/ 

    /* read the source */
    nread = SOCK_Read(handle, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_Mtp3ReadMutexLock);
        return (ITS_ERCVFAIL);
    }

    evt->src = SOCK_NToHS(tmp);

    /* read the length */
   nread = SOCK_Read(handle, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_Mtp3ReadMutexLock);
        return (ITS_ERCVFAIL);
    }

    evt->len = SOCK_NToHS(tmp);

    evt->data = (ITS_OCTET *)ITS_Malloc(evt->len);
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&CL_Mtp3ReadMutexLock);
        return (ITS_ENOMEM);
    }

    /* read the data */
    if (evt->len)
    {
       nread = SOCK_Read(handle, (char *)evt->data, evt->len);

        if (nread != evt->len)
        {
            ITS_Free(evt->data);
            evt->data = NULL;

            MUTEX_ReleaseMutex(&CL_Mtp3ReadMutexLock);
            return (ITS_ERCVFAIL);
        }
    }
    MUTEX_ReleaseMutex(&CL_Mtp3ReadMutexLock);
    return ITS_SUCCESS;
}


int CL_ReadEventSccp(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nread = 0, ret =0,j;
    char buf;
    ITS_USHORT tmp =0;
    ITS_BOOLEAN firstTime = ITS_TRUE;
    unsigned i, dosCount;
    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    MUTEX_AcquireMutex(&CL_SccpReadMutexLock);

    /* synchronize the stream */
    for (i = 0, dosCount = 0;
         i < (unsigned)sd_len && dosCount < ITS_MAX_EVENT_SIZE;
         i++, dosCount++)
    {
        /*
         * this should be the blocking point
         */

            firstTime = ITS_FALSE; //ANAND
        if (firstTime)
        {
            ITS_SockPollInfo info;

repeat:
            memset(&info, 0, sizeof(info));

            info.lookFor = SOCK_POLL_READ;
            info.sinfo = handle;

            ret = SOCK_Poll(&info, 1,
                            HMI_GetTimeOutInterval() * 1000);
            if (ret < ITS_SUCCESS)
            {
                MUTEX_ReleaseMutex(&CL_SccpReadMutexLock);
                return (ITS_ERCVFAIL);
            }

            if (ret == 0)
            {
                goto repeat;
            }

            firstTime = ITS_FALSE;
        }
                                                               ret = SOCK_Read(handle, &buf, sizeof(char));

        if (ret != sizeof(char))
        {
            MUTEX_ReleaseMutex(&CL_SccpReadMutexLock);
            return (ITS_ERCVFAIL);
        }

        if (buf != sync_data[i])
        {
            i = ~0U;
            continue;
        }
    }

    /* Here we are so successfully received ISS7SSI*/

    /* read the source */
    nread = SOCK_Read(handle, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_SccpReadMutexLock);
        return (ITS_ERCVFAIL);
    }

    evt->src = SOCK_NToHS(tmp);

    /* read the length */
   nread = SOCK_Read(handle, (char *)&tmp, sizeof(ITS_USHORT));
    if (nread != sizeof(ITS_USHORT))
    {
        MUTEX_ReleaseMutex(&CL_SccpReadMutexLock);
        return (ITS_ERCVFAIL);
    }

    evt->len = SOCK_NToHS(tmp);

    evt->data = (ITS_OCTET *)malloc(evt->len);
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&CL_SccpReadMutexLock);
        return (ITS_ENOMEM);
    }

    /* read the data */
    if (evt->len)
    {
       nread = SOCK_Read(handle, (char *)evt->data, evt->len);

        if (nread != evt->len)
{
 free(evt->data);
            evt->data = NULL;

            MUTEX_ReleaseMutex(&CL_SccpReadMutexLock);
            return (ITS_ERCVFAIL);
        }
    }
    MUTEX_ReleaseMutex(&CL_SccpReadMutexLock);
    return ITS_SUCCESS;
}



int CL_ReadEventTcap(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nread = 0, ret =0;
    unsigned short len;
    
    unsigned char  buffer[5];
    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

        evt->len =0;
    MUTEX_AcquireMutex(&CL_ReadMutexLock);

   ret = SOCK_NonBlockingRead(handle,buffer,5,5);
    if (ret != 5)
     {
         MUTEX_ReleaseMutex(&CL_ReadMutexLock);
         return ITS_SUCCESS;
     }

    printf("\n/*********************************************************/\n");
    printf("/*************START MSG FROM TCAP****************************/\n");
    printf("/************************************************************/\n");
    printf(" api_id=%d\t", buffer[0]);
     printf(" ver=%d\t",  buffer[1]);
    printf(" no of elemnt=%d\t", buffer[2]);
    len  =  buffer[3] | buffer[4] << 8;
    
    printf(" len %d\t", len);

    if (len==0 || len<1000)
    {

     evt->data = (ITS_OCTET *)malloc(len );
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ENOMEM);
    }
        evt->len= len ;
         memcpy(evt->data ,(char *)buffer  ,5);
 nread = SOCK_NonBlockingRead(handle, (char *)(evt->data + 5), len-5 ,5);
        if (nread != len-5)
        {
            free(evt->data);
            evt->data = NULL;
            MUTEX_ReleaseMutex(&CL_ReadMutexLock);
            return (ITS_ERCVFAIL);
        }
    }
    MUTEX_ReleaseMutex(&CL_ReadMutexLock);
    return ITS_SUCCESS;
}


















int CL_WriteEventMM(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nrite=0,i;
    ITS_SocketInfo * CL_Sock = NULL;
    CL_Sock = (ITS_SocketInfo *)handle;
      ITS_INT count;
    ITS_OCTET *buff;
    ITS_OCTET TempBuffer[10];

    if (CL_Sock == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    MUTEX_AcquireMutex(&CL_WriteMutexLock);
    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(CL_Sock, (char *)evt->data, evt->len);

        if (nrite != (int)evt->len)
        {
            MUTEX_ReleaseMutex(&CL_WriteMutexLock);
            return (ITS_ESENDFAIL);
        }
    }
     buff = (ITS_OCTET*)calloc(evt->len*6+1, sizeof(ITS_OCTET));

       for (count = 0; count < evt->len; count++)
         {
             sprintf((char *)TempBuffer, "0x%02x ",evt->data[count]);
             strcat((char*)buff,(const char *)TempBuffer);
             if (!(count % 15))
               {
                 strcat((char *)buff,"\n");
               }
           }

          ISIL_DEBUG_TRACE(("\nData send to MM:-\n\n%s\n\n",buff));
          free(buff);
/*
    ISIL_DEBUG_TRACE(("Data send to MM :-\n"));
    for(i = 0; i < evt->len; i++)
   {
       printf("%02x ", evt->data[i]);
   }
     printf("\n");
  */
   // printf("\n\n\n");
    /* Free the event*/
    if (evt->data)
    {
        ITS_Free(evt->data);
        evt->data =0;
    }

    MUTEX_ReleaseMutex(&CL_WriteMutexLock);
    return ITS_SUCCESS;
}


int CL_WriteEventSCM(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nrite=0,i;
    ITS_SocketInfo * CL_Sock = NULL;
    CL_Sock = (ITS_SocketInfo *)handle;
    ITS_INT count;
    ITS_INT ret=ITS_SUCCESS;
    ITS_OCTET *buff;
    ITS_OCTET TempBuffer[10];

    if (CL_Sock == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    MUTEX_AcquireMutex(&SCMCL_WriteMutexLock);
    if (ret != ITS_SUCCESS)
     {
        ISIL_DEBUG_TRACE(("CL_WriteEvent:Mutex Acquire Fail\n"));
        return NULL;
     }
    /* Write the data */
    if (evt->len)
    {
        nrite = SOCK_Write(CL_Sock, (char *)evt->data, evt->len);

        if (nrite != (int)evt->len)
        {
            MUTEX_ReleaseMutex(&SCMCL_WriteMutexLock);
            return (ITS_ESENDFAIL);
        }
    }
     buff = (ITS_OCTET*)calloc(evt->len*6+1, sizeof(ITS_OCTET));

       for (count = 0; count < evt->len; count++)
         {
             sprintf((char *)TempBuffer, "0x%02x ",evt->data[count]);
             strcat((char*)buff,(const char *)TempBuffer);
             if (!(count % 15))
               {
                 strcat((char *)buff,"\n");
               }
           }

          ISIL_DEBUG_TRACE(("\nData send to SCM:-\n\n%s\n\n",buff));
          free(buff);
/*
    ISIL_DEBUG_TRACE(("Data send to MM :-\n"));
    for(i = 0; i < evt->len; i++)
   {
       printf("%02x ", evt->data[i]);
   }
     printf("\n");
  */
   // printf("\n\n\n");
    /* Free the event*/
    if (evt->data)
    {
        ITS_Free(evt->data);
        evt->data =0;
    }

    MUTEX_ReleaseMutex(&SCMCL_WriteMutexLock);
    return ITS_SUCCESS;
}

int CL_ReadEventMM(ITS_HANDLE handle, ITS_EVENT *evt)
{
    int nread = 0, ret =0,i;
    unsigned short len;

    unsigned char  buffer[5];
    if (evt == NULL)
    {
        return ITS_EINVALIDARGS;
    }

        evt->len =0;
    MUTEX_AcquireMutex(&CL_ReadMutexLock);

   ret = SOCK_NonBlockingRead(handle,buffer,5,5);
    if (ret != 5)
     {
         MUTEX_ReleaseMutex(&CL_ReadMutexLock);
         return ITS_SUCCESS;
     }

    len  =  buffer[3] | buffer[4] << 8;

    printf(" len %d\n", len);

    if (len==0 || len<1000)
    {

     evt->data = (ITS_OCTET *)malloc(len );
    if (evt->data == NULL)
    {
        MUTEX_ReleaseMutex(&CL_ReadMutexLock);
        return (ITS_ENOMEM);
    }
        evt->len= len ;
        memcpy(evt->data ,(char *)buffer  ,5);
        nread = SOCK_NonBlockingRead(handle, (char *)(evt->data + 5), len-5 ,5);
       for(i=0; i <(evt->len); i++)
       {
        printf("\n%x", evt->data[i]);
       }
       printf("\n");

    
        if (nread != len-5)
        {
            free(evt->data);
            evt->data = NULL;
            MUTEX_ReleaseMutex(&CL_ReadMutexLock);
            return (ITS_ERCVFAIL);
        }
 }
    MUTEX_ReleaseMutex(&CL_ReadMutexLock);
    return ITS_SUCCESS;
}


