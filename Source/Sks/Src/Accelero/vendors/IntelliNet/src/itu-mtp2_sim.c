/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:19:33  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1  2007/01/05 08:40:07  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:12  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.4  2006/07/18 15:21:33  sjaddu
 * LOG: MTP2 : 2 link alignment changes
 * LOG:
 * LOG: Revision 1.1.2.3  2006/07/04 12:13:06  gdevanand
 * LOG: Combined driver for MTP and LAPD (Badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/12 06:36:39  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ident "$Id: itu-mtp2_sim.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"


#define  MTP2SIM     /* defined for  MTP2SIM  on the  host   */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <its.h>
#include <its_mtp2_intern.h>
#include <its_mcc_user.h>

#include <its_tq_trans.h>
#include <its_timers.h>
#include <its_link.h>

#if defined(INCLUDE_MTP2)

#ifdef  MTP2SIM
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

unsigned int  server_flag =0;
unsigned int  udp_base_port =0;
unsigned int  tcp_server_port =0;
unsigned char *serv_ipstr ={"127.0.0.1"};

unsigned connected_flag[16];
unsigned int  local_port[16];
unsigned int  remote_port[16];
char remoteIpAddr[16][16];
char localIpAddr[16];
int   sockfd=-1;

#endif  /* MTP2SIM */ 


#define MTP2_RXTX_DATA(x) (((MTP2_Signal *)x)->data)


#define NOT_USING_UTIL 0

static TRACE_OutputInitializer fileCritTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};
 
static TRACE_OutputInitializer fileErrTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};
 
static TRACE_OutputInitializer fileWarnTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};
 
static TRACE_OutputInitializer fileDebugTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileEventTrace =
{
    MTP2_FILE_STRING,
    ITS_TRUE,
    MTP2_TRACE_EVENT_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    MTP2_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    MTP2_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer MTP2_TraceMap[] =
{
    {MTP2_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {MTP2_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {MTP2_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {MTP2_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } },
    {MTP2_EVENT_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileEventTrace, &syslogTrace } }
};

TRACE_Data                *MTP2_CCITT_TraceData = NULL;
TQUEUETRAN_Manager        *__MTP2_CCITT_RcvQueue;
static ITS_THREAD         mtp2SendThread;
static ITS_THREAD         mtp2RcvThread;
static ITS_BOOLEAN        isSetExitMTP2 = ITS_FALSE;
static ITS_BOOLEAN        mtp2Inited    = ITS_FALSE;
static SS7CONTEXT_Manager manager;

THREAD_RET_TYPE
CCITT_MTP2_SendThread(void *arg);

THREAD_RET_TYPE
CCITT_MTP2_RcvThread(void *arg);

static ITS_INT
SendDataToDev(ITS_INT tofd, char *data, ITS_INT len);

static int
Build_MTP2Event(ITS_SS7_CONTEXT *ctxt, ITS_INT dli, ITS_OCTET *data, 
                ITS_INT dlen)
{
    MTP2_Signal *rxdata = (MTP2_Signal *)(data);
    ITS_EVENT   event;
    ITS_INT     soffset = 3; /* leave room for signal, LS and LC */
    ITS_BOOLEAN sigValid = ITS_TRUE;
    ITS_INT     ret;

    if (rxdata == NULL || dlen == 0)
    {
        /* shouldn't have come here */
        return ITS_ENOMEM;
    }

    ITS_EVENT_INIT(&event, ITS_MTP2_SRC, dlen + soffset);

    if (event.data == NULL)
    {
        return ITS_ENOMEM;
    }

    if ((rxdata->signal != L2_L3_DATA && dlen > MTP2_L2_L3_IND_SIZE) ||
        (rxdata->signal == L2_L3_DATA && dlen < MTP2_L2_L3_MIN_DATA_LEN))
    {
        MTP2_WARNING(("Build_MTP2Event: Invalid length indicator from read.\n"));

        return ITS_ENOMEM;
    }

    switch (rxdata->signal)
    {
        case L2_L3_IN_SERVICE:
            MTP2_DEBUG(("IN_SERVICE:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_REMOTE_PROCESSOR_OUT:
            MTP2_DEBUG(("RPO:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_OUT_OF_SERVICE:
            MTP2_DEBUG(("OUT_OF_SERVICE:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_REMOTE_PROCESSOR_REC:
            MTP2_DEBUG(("RPR:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_DATA:
            MTP2_DEBUG(("DATA:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_BSNT:
            MTP2_DEBUG(("BSNT:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_BSNT_NOT_RETRIEVABLE:
            MTP2_DEBUG(("BSNT_NOT_RETRIEVABLE:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_RETRIEVED_MSG:
            MTP2_DEBUG(("RETRIEVED_MSG:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_RETRIEVAL_COMPLETE:
            MTP2_DEBUG(("RETRIEVAL_COMP:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_RETRIEVAL_NOT_POSSIBLE:
            MTP2_DEBUG(("RETRIEVAL_NOT_POSSIBLE:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_RB_CLEARED:
            MTP2_DEBUG(("RB_CLR:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_RTB_CLEARED:
            MTP2_DEBUG(("RTB_CLR:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_CONGESTION_ONSET:
            MTP2_DEBUG(("CONGESTION_ONSET:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        case L2_L3_CONGESTION_ABATES:
            MTP2_DEBUG(("CONGESTION_ABATES:Rx::LS=%d:LC=%d\n",
                        ctxt->linkSet, ctxt->dlink[dli].linkCode));
            break;

        default:
            MTP2_WARNING(("Build_MTP2Event: Received invalid signal "
                          "from device FD(%d).\n", ctxt->dlink[dli].fd));
            sigValid = ITS_FALSE;
            break; 
    }

    fflush(stdout);

    if (sigValid)
    {
        int i = 0;

        L2_MSG_TYPE(&event)  = rxdata->signal;
        L2_LINK_SET(&event)  = ctxt->linkSet;
        L2_LINK_CODE(&event) = ctxt->dlink[dli].linkCode;

        if (rxdata->signal == L2_L3_DATA)
        {
            memcpy(L2_LINK_DATA(&event), rxdata->data.sif, dlen);
        }
        else
        {
            event.len = 3;
        }

        printf("Send to MTP3:\n");
        for (i = 0; i < event.len; i++)
        {
            printf("0x%02x ", event.data[i]);
            if (i && i %16 == 0)
            {
                printf("\n");
            }
        }
        /* TODO: Enqueue the event in Vendor queue if it is border trans. */
        ret = TRANSPORT_PutEvent(ITS_MTP3_CCITT_SRC, &event);
    }
    else
    {
        ret = ITS_ENOMSG;
        ITS_EVENT_TERM(&event); /* This shouldn't happen all the time */
    }

    fflush(stdout);
    return ret;
}

static void 
SetLinkDesc(ITS_SS7_CONTEXT *ctxt, fd_set *rfds, ITS_INT *maxFd)
{
    int i = 0;

    for (i = 0; ctxt && i < ctxt->numLinks; i++)
    {
        if (!ctxt->dlink[i].active)
        {
            continue;
        }
MTP2_DEBUG(("*************** Set FD = %d \n", ITS_SS7_CTXT_DLINK(ctxt)[i].fd));
 
        FD_SET(ITS_SS7_CTXT_DLINK(ctxt)[i].fd, rfds);

        if (*maxFd < ctxt->dlink[i].fd)
        {
            *maxFd = ctxt->dlink[i].fd;
        }
    }

    MTP2_DEBUG(("***** maxFD = %d \n", *maxFd));
    return;
}

static ITS_INT 
WaitForIndication(ITS_SS7_CONTEXT *ctxt, int *indic_flag, int milliSecs, 
                  ITS_BOOLEAN fromVend)
{
    fd_set         allfds; 
    struct timeval tv;
    ITS_INT        ret = ITS_SUCCESS;
    ITS_INT        maxFd = 0;
    ITS_INT        i = 0;

    FD_ZERO(&allfds);

    if (fromVend)
    {
        /* We get here only if we have Border transports */
        SetLinkDesc(ctxt, &allfds, &maxFd);
    }
    else
    {
        /*
         * Stack is ours so why do you need a Border?
         * One thread receives all the traffic from the board
         * i.e MTP2 Recv thread.
         */
        ctxt = manager.head;

        while (ctxt)
        {
            SetLinkDesc(ctxt, &allfds, &maxFd);

            ctxt = ctxt->next;
        }
    }

    tv.tv_sec  = milliSecs / MILLISEC_PER_SEC;
    tv.tv_usec = 0;

    ret = select(maxFd + 1, &allfds, NULL, NULL, &tv);

    if (ret < 0)
    {
        MTP2_ERROR(("WaitForIndication: select returned error=%d.\n", errno));

        ret = ITS_ENOMEM;
    }
    else if (ret == 0)
    {
        /* Timeout: main loop might want to see timeout error */
        /* return a timeout error code */
        ret = ITS_ETIMEOUT;
    }
    else
    {
        MTP2_DEBUG(("WaitForIndication: Check which FD has data.\n"));

        if (fromVend)
        {
            for (i = 0; i < ITS_SS7_CTXT_NUMLINKS(ctxt); i++)
            {
                if (FD_ISSET(ITS_SS7_CTXT_DLINK(ctxt)[i].fd, &allfds))
                {
                   MTP2_DEBUG(("WaitForIndication: FD = %d \n",
                                ITS_SS7_CTXT_DLINK(ctxt)[i].fd));

                    ITS_SS7_CTXT_IDXMAP(ctxt) |= (1 << i);
                }
            }
        }
        else
        {
            ctxt = manager.head;

            while (ctxt)
            {
                for (i = 0; i < ITS_SS7_CTXT_NUMLINKS(ctxt); i++)
                {
                    if (FD_ISSET(ITS_SS7_CTXT_DLINK(ctxt)[i].fd, &allfds))
                    {
                        MTP2_DEBUG(("WaitForIndication: FD = %d \n",
                                     ITS_SS7_CTXT_DLINK(ctxt)[i].fd));
                        ITS_SS7_CTXT_IDXMAP(ctxt) |= (1 << i);
                    }
                }

                ctxt = ctxt->next;
                i = 0;
            }
        }

        ret = ITS_SUCCESS;
    }

    return ret;
}

static ITS_INT
Record_MTP2ConfigData(ITS_SS7_CONTEXT *ctxt, ITS_INT idx, MTP2_SIGNAL_TYPE sig, 
                      char *data, ITS_INT len)
{
    ITS_INT ret = ITS_SUCCESS;
    char    *ptr;

    ptr = ITS_SS7_CTXT_DLINK(ctxt)[idx].configData[sig];
    if (ptr == NULL)
    {
        ptr = calloc(1, sizeof(MTP2_Signal));

        ITS_SS7_CTXT_DLINK(ctxt)[idx].configData[sig] = ptr;

        if (!ptr)
        {
            ret = ITS_ENOMEM;
        }
    }

    if (ptr && len <= sizeof(MTP2_Signal))
    {
        memcpy(ptr, data, len);
    } 
  
    return ret;
}

static ITS_INT
ReadDataFromDev(ITS_SS7_CONTEXT *ctxt, ITS_INT idx, ITS_BOOLEAN fromVend)
{
    ITS_OCTET        data[MAX_MTP2_RXTX_DATA];
    const ITS_UINT   dlen = MAX_MTP2_RXTX_DATA;
    ITS_INT          ret;
    MTP2_SIGNAL_TYPE sig;
    int              i = 0, j = 0;
    unsigned char             buff[1024+40];
    static  count =0;

    
#ifdef  MTP2SIM   
  struct sockaddr_in cli;
  int cli_size;
  int retval;

  cli_size = sizeof(cli);
  ret = recvfrom(ctxt->dlink[idx].fd, (char *)&buff[0], dlen, 0,(struct sockaddr *) &cli, &cli_size);
 for (i=0;i<ret;i++)
{
 printf("\n Data byte  %x",buff[i]);
}
  /*  change first byte higer nibble  the  0x80 to  0x40 */
  switch(buff[0])
{
	case 0x94:
		ret =0;
          break;
	case 0x80:
		ret=0;
          break;
	case 0x81:
              data[0] =0x43;
              data[1] =0x00;
              data[2] =0x00;
              ret =0x03;
          break;
	case 0x87:
	data[0]=0x45;    /*L2_L3_DATA;*/
   	data[1]=0x81;
   	data[2]=ret-3;
   	memcpy(&data[3],&buff[3],ret-3);
	break;
	case 0x83:
              data[0] =0x41;
              data[1] =0x01;  /* link set */
	      if(idx ==0)
	      {	printf("link -0\n"); data[2] =0x00;}   /*  link id */
	      if(idx ==1)
	      {	printf("link -1\n"); data[2] =0x01;}
	      if(idx ==2)
	      {	printf("link -0\n"); data[2] =0x02;}
	
              ret =0x03;
            count++;
          break;
            
}
/*  data[0]= (data[0] & 0x0f);
  data[0]= data[0] | 0x40;*/
   printf("ReadDataFromDev:MTP2SIM   FD = %d len= %d \n",ctxt->dlink[idx].fd,ret); 

#else
   printf("ReadDataFromDev:MTP2SIM   FD = %d  \n",ctxt->dlink[idx].fd); 
   ret  =0;  /*  time being  block  th eread  */

#endif 
    
    if (ret > 0)
    {
        MTP2_DEBUG(("ReadDataFromDev: fd = %d len = %d \n", 
                     ctxt->dlink[idx].fd, ret));
        for (i=0; i < ret; i++)
        {
            j += sprintf(&buff[j], "0x%02x ", data[i]);

            if (i && i % 16 == 0)
            {
                j += sprintf(&buff[j++], "\n");
            }
        }

	    MTP2_DEBUG(("%s \n", buff)); 

        /* The data could be any of the following.
         * 1. MTP2 DATA Signals.
         * 2. Configuration.
         * 3. Statistics.
         * 4. Trace configuration.
         */
        sig = MTP2_RX_SIGNAL_TYPE(data[0]);

        switch (sig)
        {
            case MTP2_SIGNAL_DATA:
                ret = Build_MTP2Event(ctxt, idx, data, ret);
                break;

            case MTP2_SIGNAL_TRACE:
            case MTP2_SIGNAL_CONFIG:
            case MTP2_SIGNAL_STATS:
                ret = Record_MTP2ConfigData(ctxt, idx, sig, data, ret);
                break;

            default:
                ret = ITS_ENOMEM;
                break;
        }
    }
    else
    {
        MTP2_ERROR(("Read return fd = %d error = %d \n",ctxt->dlink[idx].fd, errno));
        ret = ITS_ENOMEM;
    }

    return ret;
}

ITS_INT
IMTP2_WaitForIndication(ITS_SS7_HANDLE handle, int *indic_flag, int millSecs)
{
    /* TODO: Implement for border Transport */

    return ITS_SUCCESS;
}

THREAD_RET_TYPE
CCITT_MTP2_RcvThread(void *args)
{
    ITS_INT         ret = ITS_SUCCESS;
    ITS_INT         i   = 0;
    ITS_UINT        indic_flag;
    ITS_SS7_CONTEXT *ctxt = NULL;
    ITS_INT         millSecs = 10000;

printf("********** CCITT_MTP2_RcvThread *************\n");
    while (!isSetExitMTP2)
    {
        ret = WaitForIndication(NULL, &indic_flag, millSecs, ITS_FALSE);

        switch (ret)
        {
            case ITS_ETIMEOUT:
                MTP2_DEBUG(("CCITT_MTP2_RcvThread: Select timedout no data "
                            "from dev.\n"));
                continue;
                break;

            case ITS_SUCCESS:
                break;

            default:
                printf("@@@@@@@@ EXITING Loop @@@@@@@@@@@@@@\n");
                /* Fault has happend */
                /* isSetExitMTP2 = ITS_TRUE; */
                continue;
                break;
        }

        ctxt = manager.head;

        while (ctxt)
        {
            while (ITS_SS7_CTXT_IDXMAP(ctxt) && i < ITS_SS7_CTXT_NUMLINKS(ctxt))
            {
                if (ITS_SS7_CTXT_IDXMAP(ctxt) & (1 << i))
                {
                    ret = ReadDataFromDev(ctxt, i, ITS_FALSE);
                
                    if (ret != ITS_SUCCESS)
                    {
                        MTP2_ERROR(("CCITT_MTP2_RcvThread: Read error occured. error = %d\n",
                                     errno));
/*
                        MTP2_ERROR(("CCITT_MTP2_RcvThread: Read error occured."
                                    " Set Rcv/Send thread to Exit state.\n"));
*/
                        /* isSetExitMTP2 = ITS_TRUE; */
                    }
                    ITS_SS7_CTXT_IDXMAP(ctxt) &= ~(1 << i);
                }

                i++;
            }

            ctxt = ctxt->next;
            i = 0;
        }

    }

    MTP2_ERROR(("CCITT_MTP2_RcvThread: Exit loop.\n"));

    THREAD_NORMAL_EXIT;
}

THREAD_RET_TYPE
CCITT_MTP2_SendThread(void *args)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)(args);
    ITS_EVENT       mtp2Event;
    ITS_INT         ret;

    ITS_EVENT_INIT(&mtp2Event, 0, 0);
printf("CCITT_MTP2_SendThread ***********\n");

    while (!isSetExitMTP2 &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__MTP2_CCITT_RcvQueue))
                                                        (__MTP2_CCITT_RcvQueue, 
                                                        &mtp2Event)
           == ITS_SUCCESS)
    {
        switch (mtp2Event.src)
        {
            case ITS_MTP3_CCITT_SRC:
                MTP2_DEBUG(("CCITT_MTP2Thread: Got data from MTP3.\n"));
                context = manager.context[L2_LINK_SET(&mtp2Event)];

                if (context == NULL)
                {
                    MTP2_ERROR(("CCITT_MTP2Thread: Could not find LinkSet(%d)"
                                " context.\n", L2_LINK_SET(&mtp2Event)));
                }
                else
                {
                    ret = IMTP2_Send_CCITT(context, mtp2Event.data, mtp2Event.len);
                }
                break;

            case ITS_MTP2_CCITT_SRC:
                MTP2_ERROR(("CCITT_MTP2Thread: Exiting MTP2 loop...\n"));
                /* isSetExitMTP2 = ITS_TRUE;*/
                break;

            default:
                break;
        }
    }

    MTP2_ERROR(("CCITT_MTP2_SendThread: Exit loop.\n"));

    THREAD_NORMAL_EXIT;
}

static void
InitTraceData()
{
    RESFILE_Manager *res = TRANSPORT_RES(__MTP2_CCITT_RcvQueue);;
    char            value[ITS_PATH_MAX];
    char            *name = TRANSPORT_NAME(__MTP2_CCITT_RcvQueue);

printf(" Res = %x Name = %s \n %s:%d\n", res, name, __FILE__, __LINE__);

    if (res != NULL)
    {
        /* critical */
        if (RESFILE_GetKeyValueOf(res, name, MTP2_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, MTP2_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_CRITICAL_STRING,
                                           MTP2_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_CRITICAL_STRING,
                                           MTP2_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_CRITICAL_STRING,
                                           MTP2_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_CRITICAL_STRING,
                                           MTP2_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_CRITICAL_STRING,
                                           MTP2_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_CRITICAL_STRING,
                                           MTP2_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_CRITICAL_STRING, ITS_FALSE);
            }
        }

        /* error */
        if (RESFILE_GetKeyValueOf(res, name, MTP2_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, MTP2_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_ERROR_STRING,
                                           MTP2_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_ERROR_STRING,
                                           MTP2_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_ERROR_STRING,
                                           MTP2_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_ERROR_STRING,
                                           MTP2_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_ERROR_STRING,
                                           MTP2_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_ERROR_STRING,
                                           MTP2_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_ERROR_STRING, ITS_FALSE);
            }
        }

        /* warning */
        if (RESFILE_GetKeyValueOf(res, name, MTP2_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, MTP2_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_WARNING_STRING,
                                           MTP2_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_WARNING_STRING,
                                           MTP2_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_WARNING_STRING,
                                           MTP2_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_WARNING_STRING,
                                           MTP2_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_WARNING_STRING,
                                           MTP2_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_WARNING_STRING,
                                           MTP2_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_WARNING_STRING, ITS_FALSE);
            }
        }

        /* debug */
        if (RESFILE_GetKeyValueOf(res, name, MTP2_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, MTP2_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_DEBUG_STRING,
                                           MTP2_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_DEBUG_STRING,
                                           MTP2_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_DEBUG_STRING,
                                           MTP2_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_DEBUG_STRING,
                                           MTP2_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_DEBUG_STRING,
                                           MTP2_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_DEBUG_STRING,
                                           MTP2_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_DEBUG_STRING, ITS_FALSE);
            }
        }

        /* Event */
        if (RESFILE_GetKeyValueOf(res, name, MTP2_TRACE_EVENT_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {   
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;
                                                          
            if (strstr(value, MTP2_STDOUT_STRING) != NULL)
            {   
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_EVENT_STRING,
                                           MTP2_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {   
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_EVENT_STRING,
                                           MTP2_STDOUT_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_FILE_STRING) != NULL)
            {   
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_EVENT_STRING,
                                           MTP2_FILE_STRING, ITS_TRUE);
            
                fil = ITS_TRUE;
            }
            else
            {                              
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_EVENT_STRING,
                                           MTP2_FILE_STRING, ITS_FALSE);
            }
            if (strstr(value, MTP2_SYSLOG_STRING) != NULL)
            {                              
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_EVENT_STRING,
                                           MTP2_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {                              
                TRACE_SetOutputOnOffByName(MTP2_CCITT_TraceData,
                                           MTP2_EVENT_STRING,
                                           MTP2_SYSLOG_STRING, ITS_FALSE);
            }
            
            if (std || fil || sys)
            {                             
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_EVENT_STRING, ITS_TRUE);
            }
            else
            {                             
                TRACE_SetLevelOnOffByName(MTP2_CCITT_TraceData,
                                          MTP2_EVENT_STRING, ITS_FALSE);
            }
        }

    }
printf("********** ENd trace **********\n");
    return;
}

static ITS_INT
MTP2Bind(ITS_SS7_CONTEXT *ctxt)
{
    char devName[MAX_DEV_NAME_LEN];
    struct mtp2_cfg mtp2Cfg;
    ITS_INT i = 0;



#ifdef  MTP2SIM
        long                    serv_ipaddr;
        long                    remote_ipaddr;
        struct sockaddr_in      saddr;
        struct sockaddr_in      me;

	memset(connected_flag, 0,16);

for (; i < ITS_SS7_CTXT_NUMLINKS(ctxt); i++)
{
	printf("\nMTP2BIND   link  %d\n\n",i);
	serv_ipaddr =0;
	remote_ipaddr =0; 

       if(connected_flag[i] ==0)
       {
            if ((serv_ipaddr = inet_addr (localIpAddr)) == -1)
             {
                printf ("Invalid IP address\n");
                exit (1);
              }

              if ((sockfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
              {
                return (-1);
              }

              me.sin_family = AF_INET;
              me.sin_port = htons(local_port[i]);
              me.sin_addr.s_addr = htonl(localIpAddr);
              memcpy ((char *)&me.sin_addr.s_addr, (char *)&serv_ipaddr, sizeof (long));

	     printf("localIpAddr= %s, local_port= %d\n",localIpAddr,local_port[i]); 	

	     printf("localIpAddr= %x, local_port= %x\n",me.sin_addr.s_addr, me.sin_port); 	

              if (bind( sockfd, (struct sockaddr *) &me, sizeof(me) ) < 0)
              {
              printf("Unable to Bind (client)");
              close(sockfd);
		connected_flag[i] =0;
		sockfd =-1;
              goto  Next;
              }


            if ((remote_ipaddr = inet_addr (remoteIpAddr[i])) == -1)
             {
                printf ("Invalid remote IP address\n");
                close(sockfd);
		connected_flag[i] =0;
		sockfd =-1;
                goto  Next;
              }
              saddr.sin_family = AF_INET;
              saddr.sin_port = htons (remote_port[i]);

              memcpy ((char *)&saddr.sin_addr.s_addr,
                (char *)&remote_ipaddr, sizeof (long));

	     printf("RemoteIpAddr= %s, Remote_port= %d\n",remoteIpAddr,remote_port[i]); 	

	     printf("RemoteIpAddr= %x, Remote_port= %x\n",saddr.sin_addr.s_addr, saddr.sin_port); 	

             if (connect (sockfd, (struct sockaddr *)&saddr,
                     sizeof (struct sockaddr_in)) < 0)
             {
                printf("\n Unable to connect to IP :[%s]::Port [%d] "
                                        "due to %s \n", remoteIpAddr,remote_port,strerror(errno));
                close (sockfd);
		connected_flag[i] =0;
		sockfd =-1;
              }



	      if(sockfd == -1)
	         connected_flag[i] =0;

        }
Next:	  	
	ITS_SS7_CTXT_DLINK(ctxt)[i].fd = sockfd;
	if (ITS_SS7_CTXT_DLINK(ctxt)[i].fd < 0)
        {
            MTP2_ERROR(("MTP2Bind: Could not bind to the Device (%s) "
                        "error (%d)\n", devName, errno));
	   continue;
        }
	

        printf("MTP2Bind Open file descriptor = %d \n", ITS_SS7_CTXT_DLINK(ctxt)[i].fd);
        ITS_SS7_CTXT_DLINK(ctxt)[i].active = ITS_TRUE;
}



   printf("******** MTP2SIM MTP2Bind end ******\n");
    return ITS_SUCCESS;

#endif  

#ifndef  MTP2SIM
    for (; i < ITS_SS7_CTXT_NUMLINKS(ctxt); i++)
    {
        snprintf(devName, MAX_DEV_NAME_LEN, MTP2_DEV_NAME, 
                 ITS_SS7_CTXT_DLINK(ctxt)[i].channelNum / 2);

#if NOT_USING_UTIL 
        
printf("***** MTP2Bind IN  NOT_USING_UTIL **********\n");
        mtp2Cfg.num_chan = 1;
        mtp2Cfg.channels[0].chan = ITS_SS7_CTXT_DLINK(ctxt)[i].channelNum;
        mtp2Cfg.channels[0].mode = MCC_TYPE_SS7;
        mtp2Cfg.channels[0].loop = 0; /* 0: no loopback */
        if (ioctl(manager.configFD, MCC_IOCSCONFIG, &mtp2Cfg) < 0)
        { 
            MTP2_DEBUG(("MTP2Bind: Could not Configure the Device "));
        } 

        /* Enable control device */
        if (ioctl(manager.configFD, MCC_IOCENABLE, NULL) < 0)
        { 
            MTP2_DEBUG(("MTP2Bind: Could not Enable the Device "));
        } 
 
        printf("MTP2 Bind: %s:%d\n", __FILE__, __LINE__);
        close(manager.configFD); /* Now I see why I should build the
                                  * mtp2 ctrl utility for channel configuration
                                  */
        manager.configFD = -1; /* set to invalid data */
#endif

        ITS_SS7_CTXT_DLINK(ctxt)[i].fd = open(devName, O_RDWR);

        printf("MTP2 Bind: To Device %s | %s:%d\n",devName, __FILE__, __LINE__);

        if (ITS_SS7_CTXT_DLINK(ctxt)[i].fd < 0)
        {
            MTP2_ERROR(("MTP2Bind: Could not bind to the Device (%s) "
                        "error (%d)\n", devName, errno));

            return ITS_ENOMEM;
        }


        printf("MTP2Bind OPen file descriptor = %d \n", ITS_SS7_CTXT_DLINK(ctxt)[i].fd);
        ITS_SS7_CTXT_DLINK(ctxt)[i].active = ITS_TRUE;
    }
printf("******** MTP2Bind end ******\n");
    return ITS_SUCCESS;

#endif  /*  MTP2SIM */
}

static ITS_INT
MTP2BindAllDev()
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_SS7_CONTEXT *ctxt = manager.head;

    for (; ctxt; ctxt = ctxt->next)
    {
        ret = MTP2Bind(ctxt);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }
    }

    return ITS_SUCCESS;
}

static void
RequestMTP2ConfigData()
{
    ITS_INT         i = 0, j = 0;
    ITS_SS7_CONTEXT *ctxt = manager.head;
    MTP2_Signal     sig;
    ITS_INT         tofd;
    ITS_INT         ret;
    ITS_OCTET       type[] = { L3_L2_GET_CONFIG, 
                               L3_L2_GET_TRACE, 
                               L3_L2_GET_STATS };
    MTP2_DEBUG(("RequestMTP2ConfigData: \n"));

    memset(&sig, 0, sizeof(MTP2_Signal));

    for (; ctxt; ctxt = ctxt->next)
    {
        for (i = 0; i < ITS_SS7_CTXT_NUMLINKS(ctxt); i++)
        {
            tofd = ITS_SS7_CTXT_DLINK(ctxt)[i].fd;

            do
            {
		
                sig.signal = type[j++]; 
#ifdef  MTP2SIM

		printf ( "\n\n.. open  UDP socket  interface with PEER for FD = %d ",tofd);
		ret =MTP2_SIG_GET_CTS_SIZE;
#endif

#ifndef MTP2SIM
                ret = SendDataToDev(tofd, (char *)&sig, MTP2_SIG_GET_CTS_SIZE);
#endif 

                if (ret != MTP2_SIG_GET_CTS_SIZE)
                {
                    MTP2_DEBUG(("RequestMTP2ConfigData: Error while write to"
                                " dev Error(%d) ret=(%d)\n", errno, ret));
                }
            }
            while (j < 3);
        }
    }

    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the MTP2 interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The SS7 context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
IMTP2_Initialize_CCITT(ITS_SS7_HANDLE handle)
{
    ITS_EVENT       event;
    SS7_LinkPtr      ln;
    ITS_SS7_CONTEXT *context;
    ITS_BOOLEAN     isBorderConfig = ITS_FALSE;
    ITS_INT         ret = 0;
    ITS_INT         idx;

printf("*******MTP2 Initialize %s:%d ********\n", __FILE__,__LINE__);
    if (!mtp2Inited)
    {
        /* Static members initialization. Protecting from multiple invokes in 
         * case user prefers to use border transport
         */

        if ( (MTP2_CCITT_TraceData = TRACE_Constructor("ITU-MTP2",
                                                  MTP2_TraceMap, 5)) == NULL)
        {
            printf("IMTP2_Initialize: Could not create trace Data.\n");
            return ITS_ENOMEM;
        }

printf("*** Creating MTP2 transport ***** %s:%d \n", __FILE__, __LINE__);
        if ( (__MTP2_CCITT_RcvQueue = TQUEUETRAN_CreateTransport("ITU-MTP2",
                                                       ITS_MTP2_CCITT_SRC,
                                                       ITS_MTP2_CCITT)) == NULL)
        {
            MTP2_CRITICAL(("IMTP2_Initialize_CCITT:could not create transport.\n"));

            /* Delete MTP2 specifics */
            TRACE_Destructor(MTP2_CCITT_TraceData);

            return ITS_ENOMEM;
        }

        /* Initialize MTP2 specifics here */
        InitTraceData();

        memset(&manager, 0, sizeof(SS7CONTEXT_Manager));
#if NOT_USING_UTIL
         printf("***** IMTP2_Initialize_CCITT IN  NOT_USING_UTIL **********\n");

#ifndef  MTP2SIM        
        manager.configFD = open (MCC_CTL_DEVICE_NAME, O_WRONLY);

        if (manager.configFD < 0)
        {
            MTP2_ERROR(("IMTP2_Initialize_CCITT: failed to open CTL dev error%d\n",
                        errno));

            return ITS_ENOMEM;
        }
        MTP2_DEBUG(("IMTP2_Initialize_CCITT: opened CTL dev successfully\n"));

        /* Reset MCC controller */
        if (ioctl(manager.configFD, MCC_IOCRESET, NULL) < 0)
        {
            MTP2_ERROR(("IMTP2_Initialize_CCITT: failed to reset MCC error%d\n",
                        errno));

            return ITS_ENOMEM;
        }
        MTP2_DEBUG(("IMTP2_Initialize_CCITT: Reset CTL dev successfully\n"));
#else

     
        MTP2_DEBUG(("IT is  MTP2SIM  , No  initalisation required\n"));

#endif         

#endif
    }

    /* TODO: Keep the context in global unlike in ADAX implementation. I am 
     * going to follow the IntelliNet stack implementation, of course that is 
     * what I intended to do but I am also inclined to do with border trans for 
     * the people who likes borders.
     * Allocate context for each linkset and put it in global varibale manager.
     * This part is done.
     *
     * We should know the transport if it is Border. Find when This initialize 
     * function is called. Got it Border initialization will call this.
     *
     * I may need to declare a section for LinkSets and Linkcode link in ADAX. 
     * This is only for backword compatibility with border trans.
     */ 
    /* Read link and linkSet information to build SS7CONTEXT_Manager */

    ln = TRANSPORT_SS7_INFO(__MTP2_CCITT_RcvQueue).linkInfo;

    if (!ln)
    {
        isBorderConfig = ITS_TRUE;

        /* TODO: 1. Lookup for the context using Transport ID.
         *       2. If not found Allocate context and add to the list.
         *       3. Bind to the Dev.
         */
        ret = MTP2Bind(context);
    }

    /* If Border Transports are configured then "for" loop won't be
     * executed. Here implementor needs to know the data link configuration
     * from XML i.e. LS, LC and TimeSlot....
     * TODO: Read data from XML for border transport config.
     */
    for (; ln; ln = ln->next)
    {
        if (!ln->linkSet)
        {
            MTP2_WARNING(("IMTP2_Initialize: No linkSet for this link"
                          " (%d)...!\n", ln->linkCode));
            continue;
        }

        if (manager.context[ln->linkSet->linkSet])
        {
            context = manager.context[ln->linkSet->linkSet];
	    }
        else
        { 
            context = (ITS_SS7_CONTEXT *)calloc(1, sizeof(ITS_SS7_CONTEXT));
            manager.context[ln->linkSet->linkSet] = context;

            ITS_SS7_CTXT_LINKSET(context) = ln->linkSet->linkSet;

            SS7CONTEXT_ADD_HEAD(manager, context);
        }

        if (context == NULL)
        {
            MTP2_CRITICAL(("IMTP2_Initialize_CCITT: Could not allocate context.\n"));

            return ITS_ENOMEM;
        }

        idx = ITS_SS7_CTXT_NUMLINKS(context);

        ITS_SS7_CTXT_DLINK(context)[idx].linkCode   = ln->linkCode;
        ITS_SS7_CTXT_DLINK(context)[idx].channelNum = ln->dataLink;
        ITS_SS7_CTXT_DLINK(context)[idx].active     = ITS_FALSE;
        ITS_SS7_CTXT_NUMLINKS(context)++;
    }

    if (!isBorderConfig && !mtp2Inited)
    {
        ret = MTP2BindAllDev();

        if (ret != ITS_SUCCESS)
        {
            /* TODO: Close opened fd's and destroy all objects */
        }
        else
        {
            /* Send request to the dev for config/trace/stats */
            RequestMTP2ConfigData();
        }

        if (THREAD_CreateThread(&mtp2SendThread, 0, CCITT_MTP2_SendThread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            MTP2_CRITICAL(("IMTP2_Initialize_CCITT:Could not create "
                           "ccitt-mtp2 thread.\n"));

            TQUEUETRAN_DeleteTransport(__MTP2_CCITT_RcvQueue);

            /* Delete mtp2 specifics */
            TRACE_Destructor(MTP2_CCITT_TraceData);

            return ITS_ENOMEM;
        }

        if (THREAD_CreateThread(&mtp2RcvThread, 0, CCITT_MTP2_RcvThread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            MTP2_CRITICAL(("IMTP2_Initialize_CCITT:Could not create"
                           " ccitt-mtp2 thread.\n"));

            ITS_EVENT_INIT(&event, ITS_MTP2_CCITT_SRC, 0);

            /* to exit the send thread */
            TRANSPORT_PutEvent(ITS_MTP2_CCITT_SRC, &event); 

            TQUEUETRAN_DeleteTransport(__MTP2_CCITT_RcvQueue);

            /* Delete mtp2 specifics */
            TRACE_Destructor(MTP2_CCITT_TraceData);

            return ITS_ENOMEM;
        }
    }
   
    mtp2Inited = ITS_TRUE;

    printf("******* ITS_MTP2 Initialization sucess *******\n"); 
fflush(stdout);
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Terminate the MTP2 interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The SS7 context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
IMTP2_Terminate_CCITT(ITS_SS7_HANDLE handle)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;

    /* TODO: 1. Close all opened files.
     *       2. Clean Context memory.
     *       3. Delete Transport.
     *       4. Delete Trace data.
     */

    mtp2Inited = ITS_FALSE;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Retrieve an MTP2 message
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
IMTP2_Retrieve_CCITT(ITS_SS7_HANDLE handl)
{
    ITS_SS7_CONTEXT *ctxt = (ITS_SS7_CONTEXT *)handl;
    ITS_INT         i = 0;
    ITS_INT         ret;

    while (ITS_SS7_CTXT_IDXMAP(ctxt) && i < ITS_SS7_CTXT_NUMLINKS(ctxt))
    {
        if (ITS_SS7_CTXT_IDXMAP(ctxt) & (1 << i))
        {
            ret = ReadDataFromDev(ctxt, i, ITS_TRUE);
        }
        i++;
    }

    return ret;
}

static ITS_INT
SendDataToDev(ITS_INT tofd, char *data, ITS_INT len)
{
    ITS_INT ret;
    ITS_INT loop;
   unsigned  char *ploop;
    	

#ifdef MTP2SIM
 int     nleft, nwritten;

printf("***** SendDataToDev ********** len = %d \n", len);
ploop  =data;
 for(loop =0; loop<len; loop++)
  {
        printf("%x,",ploop[loop]);

  }
  
        nleft = len;
        while (nleft > 0)
        {
                nwritten = write (tofd, data, nleft);
                if (nwritten < 0)
                 {
		   printf("error  in byte sending on socket\n\n  ");
		   break;	
		}		
			//        return nwritten;        /* error return < 0 */
		printf("left %d", nleft);
                nleft -= nwritten;
                data+= nwritten;
        }
        /*return (nbytes - nleft);*/

   	printf("***** MTP2SIM  SendDataToDev ********** sent len = %d >>\n", nleft);
	ret =len-nleft;
#else
    	ret =00;  /* time being  blocked */
	for (loop =0  ; loop<len;loop++)
	{
		printf("%d, ",data[loop]);

	}
    
#endif     
    
printf("***** SendDataToDev: write() ret = %d on fd = %d ****\n", ret, tofd);
    if (ret < 0)
    {
        MTP2_ERROR(("SendDataToDev: Write to Device failed for fd(%d) errno=%d.\n",
                    tofd, errno));
        ret = ITS_ESENDFAIL;
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an MTP2 message
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
IMTP2_Send_CCITT(ITS_SS7_HANDLE handle, ITS_OCTET *data, ITS_USHORT dlen)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    ITS_OCTET       linkSet, linkCode;
    ITS_INT         tofd     = -1; /* set fd to send data */
    ITS_BOOLEAN     found    = ITS_FALSE;
    ITS_BOOLEAN     sigValid = ITS_TRUE;
    MTP2_Signal     rxdata;
    ITS_EVENT       evt;
    ITS_INT         ret = ITS_SUCCESS;
    ITS_INT         i = 0;
    char            buff[1024+40];;
    ITS_INT         k = 0, l = 0;
    evt.data = data;
    evt.len  = dlen;

printf("***** IMTP2_Send_CCITT ********** %d \n", dlen);
    for (k = 0; k < dlen; k++)
    {
        l += sprintf(&buff[l], "0x%02x ", data[k]);
        if (k && k % 16 == 0)
        {
            l += sprintf(&buff[l], "\n");
        }
    }

    MTP2_DEBUG(("IMTP2_Send_CCITT: %s\n", buff));

    linkSet  = L2_LINK_SET(&evt);
    linkCode = L2_LINK_CODE(&evt);

    for (i =0; (context->linkSet == linkSet && 
                i < context->numLinks && !found); i++)
    {
        if (context->dlink[i].linkCode == linkCode)
        {
            tofd = context->dlink[i].fd;
            found = ITS_TRUE;
        }
    }

    MTP2_DEBUG(("SendData:LS=%d LC=%d tofd = %d \n",
                 linkSet, linkCode, tofd));
    if (found)
    {
#if 0
        MTP2_RXTX_SIGNAL(&rxdata) = L2_MSG_TYPE(&evt);

        if (L2_MSG_TYPE(&evt) == L3_L2_DATA)
        {
#endif
            /* TODO: Email from Mitch:
             * Lakshma, you're going to note if you read the MTP2 document that 
             * I changed the API slightly (the read/write size has changed for 
             * each signal).  Basically, I got into the implementation and realized 
             * I needed to reserve space for the MTP2 header.  The space I needed 
             * corresponded _exactly_ to the addition of linkSet/linkCode as defined 
             * for the MTP3<->MTP2 interface for the IntelliNet stack." So basically
             * Signal:LS:LC:SIF
             */
#if 0
            rxdata.signal = L2_MSG_TYPE(&evt);
            memcpy(rxdata.data.sif, L2_LINK_DATA(&evt) + 1, dlen - (MTP2_FIXED_HDR_SIZE + 1));
#endif
            memcpy(&rxdata, evt.data, dlen);

            rxdata.linkSet = linkSet;
            rxdata.linkCode = linkCode;
#if 0
        }
#endif
        switch (rxdata.signal)
        {
            case L3_L2_CONNECT:
                MTP2_DEBUG(("CONNECT:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_START:
                MTP2_DEBUG(("START:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_STOP:
                MTP2_DEBUG(("STOP:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_DISCONNECT:
                MTP2_DEBUG(("DISCONNECT:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_RESUME:
                MTP2_DEBUG(("RESUME:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_CLEAR_BUFFERS:
                MTP2_DEBUG(("CLR_BUFFERS:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_CLEAR_RTB:
                MTP2_DEBUG(("CLR_RTB:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_EMERGENCY:
                MTP2_DEBUG(("EMERGENCY:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_EMERGENCY_CEASE:
                MTP2_DEBUG(("EMERGENCY_CEASE:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_DATA:
                memcpy(rxdata.data.sif, L2_LINK_DATA(&evt) + 1,
                       dlen - (MTP2_FIXED_HDR_SIZE + 1));
                dlen = dlen - 1; /*(MTP2_FIXED_HDR_SIZE + 1);*/
                MTP2_DEBUG(("DATA:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_RETRIEVE_BSNT:
                MTP2_DEBUG(("RETIEVE_BSNT:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_RETRIEVE_MSGS:
            {
                ITS_UINT bsnt;

                memcpy(&bsnt, L2_LINK_DATA(&evt), sizeof(ITS_UINT));

                MTP2_SIGNAL_BSNT(&rxdata) = (ITS_OCTET)(bsnt & 0x000000FF);

                MTP2_DEBUG(("RETRIEVE_MSGS:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;
            }
            case L3_L2_FLOW_CONTROL_START:
                MTP2_DEBUG(("FLOW_CTRL_START:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_FLOW_CONTROL_STOP:
                MTP2_DEBUG(("FLOW_CTRL_STOP:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_LOCAL_PROCESSOR_OUT:
                MTP2_DEBUG(("LPO:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_LOCAL_PROCESSOR_REC:
                MTP2_DEBUG(("LPR:TX:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                break;

            case L3_L2_GET_TRACE:
                MTP2_DEBUG(("L3_L2_GET_TRACE:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                sigValid = ITS_FALSE;
                break;
            case L3_L2_GET_CONFIG:
                MTP2_DEBUG(("L3_L2_GET_CONFIG:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                sigValid = ITS_FALSE;
                break;
            case L3_L2_GET_STATS:
                MTP2_DEBUG(("L3_L2_GET_STATS:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                sigValid = ITS_FALSE;
                break;
            case L3_L2_SET_TRACE:
                MTP2_DEBUG(("L3_L2_SET_TRACE:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                sigValid = ITS_FALSE;
                break;
            case L3_L2_SET_CONFIG:
                MTP2_DEBUG(("L3_L2_SET_CONFIG:LS=%d:LC=%d\n",
                            linkSet, linkCode));
                sigValid = ITS_FALSE;
                break;
            default:
                /* MTP3 is requesting config data on recv func */
                sigValid = ITS_FALSE;
        }

        if (sigValid)
        {
            ret = SendDataToDev(tofd, (char *)&rxdata, dlen);

            if (ret != dlen)
            {
                MTP2_WARNING(("IMTP2_Send_CCITT: Device could not send"
                              " specified len (%d) of data\n", dlen));

                ret = ITS_ESENDFAIL;
            }
            else
            {
                ret = ITS_SUCCESS;
            }
        }
        else
        {
            MTP2_ERROR(("IMTP2_Send_CCITT: Invalid signal.\n"));
        }
    }

    return ret;
}

ITS_INT
IMTP2_SetConfiguration(ITS_OCTET ls, ITS_OCTET lc, MTP2_Signal *data)
{
    ITS_SS7_CONTEXT  *ctxt = NULL;
    ITS_INT          ret = ITS_ENOMEM;
    MTP2_Signal      getsig;
    ITS_OCTET        sig;
    MTP2_SIGNAL_TYPE type =  MTP2_TX_SIGNAL_TYPE(data->signal);
    ITS_INT          len  = 0;
    ITS_INT          tofd = 0;

    ctxt = manager.context[ls];

    if (type == MTP2_SIGNAL_CONFIG)
    {
        len = MTP2_SIG_SET_CONFIG_SIZE;
        sig = L3_L2_GET_CONFIG;
    }
    else if (type == MTP2_SIGNAL_STATS)
    {
        len = MTP2_SIG_RESET_STAT_SIZE;
        sig = L3_L2_GET_STATS;
    }
    else if (type == MTP2_SIGNAL_TRACE)
    {
        len = MTP2_SIG_SET_TRACE_SIZE;
        sig = L3_L2_GET_TRACE;
    }
    else
    {
        ret = ITS_EINVALIDARGS;
    }

    if (ctxt && ret != ITS_EINVALIDARGS)
    {
        ITS_INT i =0;

        for (i = 0; i < ITS_SS7_CTXT_NUMLINKS(ctxt); i++)
        {
            if (ITS_SS7_CTXT_DLINK(ctxt)[i].linkCode == lc)
            {
                tofd = ITS_SS7_CTXT_DLINK(ctxt)[i].fd;

                ret = SendDataToDev(tofd, (char *)data, len);

                if (ret != ITS_ESENDFAIL && ret == len)
                {
                    memset(&getsig, 0, sizeof(MTP2_Signal));

                    getsig.signal = sig;

                    /* Go ahead and get the modified data */
                    ret = SendDataToDev(tofd, (char *)&getsig, 
                                        MTP2_SIG_GET_CTS_SIZE);

                    if (ret != MTP2_SIG_GET_CTS_SIZE)
                    {
                        MTP2_DEBUG(("IMTP2_SetConfiguration: Could be partial write."
                                    " Error = %d len = %d\n", errno, ret));

                        ret = ITS_ESENDFAIL;
                    }
                    else
                    {
                        ret = ITS_SUCCESS;
                    }
                }
                else
                {
                    MTP2_DEBUG(("IMTP2_SetConfiguration: Could be partial write."
                                " Error = %d len = %d\n", errno, ret));
                }

                break;
            }
        }
    }

    return ret;
}

ITS_INT
IMTP2_GetConfiguration(ITS_OCTET ls, ITS_OCTET lc, MTP2_Signal *sig)
{
    ITS_SS7_CONTEXT *ctxt;
    ITS_INT         ret;
    ITS_INT         i = 0;
    ITS_INT         type = sig->signal;

    if (ls >= MAX_MTP2_LINK_SETS || sig == NULL)
    {
        return ITS_ENOMEM;
    }

    ctxt = manager.context[ls];

    if (ctxt)
    {
        for (i = 0; i < ITS_SS7_CTXT_NUMLINKS(ctxt); i++)
        {
            if (ITS_SS7_CTXT_DLINK(ctxt)[i].linkCode == lc)
            {
                memcpy(sig, ITS_SS7_CTXT_DLINK(ctxt)[i].configData[type], 
                       sizeof(MTP2_Signal));

                return ret;
            }
        }
    }

    return ret;
}

#endif /* INCLUDE_MTP2 */
