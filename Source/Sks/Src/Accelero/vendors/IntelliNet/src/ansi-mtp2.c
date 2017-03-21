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
 * LOG: Revision 1.3  2008/02/13 03:02:21  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2008/02/13 02:06:26  bsccs2
 * LOG: Changed by Ashutosh
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:12:15  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:33  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.6  2007/08/01 10:42:57  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.5  2007/07/20 10:53:30  ashutosh.singh
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2007/07/20 06:05:59  ashutosh.singh
 * LOG: change for run time configuration at mtp2
 * LOG:
 * LOG: Revision 1.3  2007/05/11 06:13:38  ashutosh.singh
 * LOG: change for logger lib integeration
 * LOG:
 * LOG: Revision 1.2  2007/01/06 06:54:57  cvsadmin
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

#ident "$Id: itu-mtp2.c,v 1.4 2008-05-14 08:26:32 bsccs2 Exp $"

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
#include <mtp2_cmn.h>
#include <sysxxx_typedef.h>
#include <nwstkscm_hashdefs.h>
#include <nwstkscm_msgdef.h>
#define ITS_DEFAULT_SRC 0xEEEE
#define ITS_ISUP_SRC  ITS_ISUP_ANSI_SRC
#if defined(INCLUDE_MTP2)

ITS_SEMAPHORE scm_sema;
ITS_SEMAPHORE mtp2_sema;
/*change due to inform the ln_add or ln_del commamd to mtp2*/

#define ln_add_cmd  0x1a
#define ln_del_cmd  0x1b
ITS_OCTET ENTRYDONE;
ITS_OCTET ENTRYDELETE;
ITS_OCTET TIMERCONFIG;
ITS_OCTET PEGCONFIG;
ITS_OCTET LINKSET;
ITS_OCTET LINKCODE;

/*end */

#define MTP2_RXTX_DATA(x) (((MTP2_Signal *)x)->data)


#define NOT_USING_UTIL 0

static TRACE_OutputInitializer fileCritTrace = {
  MTP2_FILE_STRING,
  ITS_TRUE,
  MTP2_TRACE_CRITICAL_FILE,
  TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace = {
  MTP2_FILE_STRING,
  ITS_TRUE,
  MTP2_TRACE_ERROR_FILE,
  TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace = {
  MTP2_FILE_STRING,
  ITS_TRUE,
  MTP2_TRACE_WARNING_FILE,
  TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace = {
  MTP2_FILE_STRING,
  ITS_TRUE,
  MTP2_TRACE_DEBUG_FILE,
  TRACE_TO_FILE
};

static TRACE_OutputInitializer fileEventTrace = {
  MTP2_FILE_STRING,
  ITS_TRUE,
  MTP2_TRACE_EVENT_FILE,
  TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace = {
  MTP2_STDOUT_STRING,
  ITS_TRUE,
  NULL,
  TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace = {
  MTP2_SYSLOG_STRING,
  ITS_TRUE,
  NULL,
#if defined(WIN32)
  TRACE_TO_NT_EVENT_LOG
#else
  TRACE_TO_SYSLOG
#endif
};

#ifdef CCITT

#define IMTP2_Initialize IMTP2_Initialize_CCITT
#define IMTP2_Retrieve IMTP2_Retrieve_CCITT
#define IMTP2_Terminate IMTP2_Terminate_CCITT
#define ITS_MTP3_SRC ITS_MTP3_CCITT_SRC
#define ITS_MTP2_SRC ITS_MTP2_CCITT_SRC
#else
#define IMTP2_Initialize IMTP2_Initialize_ANSI
#define IMTP2_Retrieve IMTP2_Retrieve_ANSI
#define IMTP2_Terminate IMTP2_Terminate_ANSI
#define ITS_MTP3_SRC ITS_MTP3_ANSI_SRC
#define ITS_MTP2_SRC ITS_MTP2_ANSI_SRC
#endif

static TRACE_LevelInitializer MTP2_TraceMap[] = {
  {MTP2_CRITICAL_STRING, ITS_TRUE, 3,
   {&stdoutTrace, &fileCritTrace, &syslogTrace}},
  {MTP2_ERROR_STRING, ITS_TRUE, 3,
   {&stdoutTrace, &fileErrTrace, &syslogTrace}},
  {MTP2_WARNING_STRING, ITS_TRUE, 3,
   {&stdoutTrace, &fileWarnTrace, &syslogTrace}},
  {MTP2_DEBUG_STRING, ITS_FALSE, 3,
   {&stdoutTrace, &fileDebugTrace, &syslogTrace}},
  {MTP2_EVENT_STRING, ITS_FALSE, 3,
   {&stdoutTrace, &fileEventTrace, &syslogTrace}}
};

TRACE_Data *MTP2_CCITT_TraceData = NULL;
TQUEUETRAN_Manager *__MTP2_CCITT_RcvQueue;
static ITS_THREAD mtp2SendThread;
static ITS_THREAD mtp2RcvThread;
static ITS_BOOLEAN isSetExitMTP2 = ITS_FALSE;
static ITS_BOOLEAN mtp2Inited = ITS_FALSE;
static SS7CONTEXT_Manager manager;

THREAD_RET_TYPE CCITT_MTP2_SendThread (void *arg);

THREAD_RET_TYPE CCITT_MTP2_RcvThread (void *arg);

static ITS_INT SendDataToDev (ITS_INT tofd, char *data, ITS_INT len);

static int
Build_MTP2Event (ITS_SS7_CONTEXT * ctxt, ITS_INT dli, ITS_OCTET * data,
		 ITS_INT dlen)
{
  MTP2_Signal *rxdata = (MTP2_Signal *) (data);
  ITS_EVENT event;
  ITS_INT soffset = 3;		/* leave room for signal, LS and LC */
  ITS_BOOLEAN sigValid = ITS_TRUE;
  ITS_INT ret;
  ITS_INT count;
  ITS_OCTET *buff = NULL;
  ITS_OCTET TempBuffer[10];

  if (rxdata == NULL || dlen == 0)
    {
      /* shouldn't have come here */
      return ITS_ENOMEM;
    }

/*    ITS_EVENT_INIT(&event, ITS_MTP2_SRC, dlen + soffset); */
  /*  Three  Extra  Byte removal  Patch  */
  ITS_EVENT_INIT (&event, ITS_MTP2_SRC, dlen);

  if (event.data == NULL)
    {
      return ITS_ENOMEM;
    }

  if (/*(rxdata->signal != L2_L3_DATA && dlen > MTP2_L2_L3_IND_SIZE) ||*/
      (rxdata->signal == L2_L3_DATA && dlen < MTP2_L2_L3_MIN_DATA_LEN))
    {
      MTP2_WARNING (("Build_MTP2Event: Invalid length indicator from read.\n"));

      return ITS_ENOMEM;
    }

  switch (rxdata->signal)
    {
    case L2_L3_IN_SERVICE:
      MTP2_ERROR (("IN_SERVICE:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_REMOTE_PROCESSOR_OUT:
      MTP2_DEBUG (("RPO:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_OUT_OF_SERVICE:
      MTP2_ERROR (("OUT_OF_SERVICE:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_REMOTE_PROCESSOR_REC:
      MTP2_DEBUG (("RPR:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_DATA:
      MTP2_DEBUG (("DATA:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_BSNT:
      MTP2_DEBUG (("BSNT:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_BSNT_NOT_RETRIEVABLE:
      MTP2_DEBUG (("BSNT_NOT_RETRIEVABLE:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_RETRIEVED_MSG:
      MTP2_DEBUG (("RETRIEVED_MSG:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_RETRIEVAL_COMPLETE:
      MTP2_DEBUG (("RETRIEVAL_COMP:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_RETRIEVAL_NOT_POSSIBLE:
      MTP2_DEBUG (("RETRIEVAL_NOT_POSSIBLE:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_RB_CLEARED:
      MTP2_DEBUG (("RB_CLR:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_RTB_CLEARED:
      MTP2_DEBUG (("RTB_CLR:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_CONGESTION_ONSET:
      MTP2_DEBUG (("CONGESTION_ONSET:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    case L2_L3_CONGESTION_ABATES:
      MTP2_DEBUG (("CONGESTION_ABATES:Rx::LS=%d:LC=%d\n",
		   ctxt->linkSet, ctxt->dlink[dli].linkCode));
      break;

    default:
      MTP2_WARNING (("Build_MTP2Event: Received invalid signal "
		     "from device FD(%d).\n", ctxt->dlink[dli].fd));
      sigValid = ITS_FALSE;
      break;
    }

  fflush (stdout);

  if (sigValid)
    {
      int i = 0;

      L2_MSG_TYPE (&event) = rxdata->signal;
      L2_LINK_SET (&event) = ctxt->linkSet;
      L2_LINK_CODE (&event) = ctxt->dlink[dli].linkCode;

      if (rxdata->signal == L2_L3_DATA || rxdata->signal == L2_L3_BSNT || rxdata->signal == L2_L3_RETRIEVED_MSG)
	{
	  /*          memcpy(L2_LINK_DATA(&event), rxdata->data.sif, dlen); */
	  memcpy (L2_LINK_DATA (&event), rxdata->data.sif, (dlen - 3));
	}
      else
	{
	  event.len = 3;
	}

      /*  MTP2_DEBUG(("MTP2 Send for MTP3:\n"));
         for (i = 0; i < event.len; i++)
         {
         printf("0x%02x ", event.data[i]);
         if (i && i %16 == 0)
         {
         printf("\n");
         }
         } */
#ifdef TRACE_DUMP
      buff = (ITS_OCTET *) calloc (event.len * 6 + 1, sizeof (ITS_OCTET));

      for (count = 0; count < event.len; count++)
	{
	  sprintf ((char *) TempBuffer, "0x%02x ", event.data[count]);
	  strcat ((char *) buff, (const char *) TempBuffer);

	  if (!(count % 15) && (count != 0))
	    {
	      strcat ((char *) buff, "\n");
	    }
	}
      MTP2_DEBUG (("MTP2 Send for MTP3::-\n\n%02x\n\n", buff));
      free (buff);
#endif
      /* TODO: Enqueue the event in Vendor queue if it is border trans. */
      ret = TRANSPORT_PutEvent (ITS_MTP3_ANSI_SRC, &event);
    }
  else
    {
      ret = ITS_ENOMSG;
      ITS_EVENT_TERM (&event);	/* This shouldn't happen all the time */
    }

  fflush (stdout);
  return ret;
}

static void
SetLinkDesc (ITS_SS7_CONTEXT * ctxt, fd_set * rfds, ITS_INT * maxFd)
{
  int i = 0;

//  for (i = 0; ctxt && i < ctxt->numLinks; i++)
  for (i = 0; ((ctxt) && ( i < MAX_LINK_CODES)); i++)
    {
  //    MTP2_DEBUG (("linkCode = %d active %d\n", ctxt->dlink[i].linkCode,ctxt->dlink[i].active));
      
      if (!ctxt->dlink[i].active)
	{
    //     MTP2_DEBUG (("Con linkCode = %d ", ctxt->dlink[i].linkCode));
	  continue;
	}
      MTP2_DEBUG ((" Set FD = %d \n", ITS_SS7_CTXT_DLINK (ctxt)[i].fd));

      FD_SET (ITS_SS7_CTXT_DLINK (ctxt)[i].fd, rfds);

      if (*maxFd < ctxt->dlink[i].fd)
	{
	  *maxFd = ctxt->dlink[i].fd;
	}
    }

  MTP2_DEBUG (("maxFD = %d \n", *maxFd));
  return;
}

static ITS_INT
WaitForIndication (ITS_SS7_CONTEXT * ctxt, int *indic_flag, int milliSecs,
		   ITS_BOOLEAN fromVend)
{
  fd_set allfds;
  struct timeval tv;
  ITS_INT ret = ITS_SUCCESS;
  ITS_INT maxFd = 0;
  ITS_INT i = 0;

  FD_ZERO (&allfds);

  if (fromVend)
    {
      /* We get here only if we have Border transports */
      SetLinkDesc (ctxt, &allfds, &maxFd);
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
	  SetLinkDesc (ctxt, &allfds, &maxFd);

	  ctxt = ctxt->next;
	}
    }

  tv.tv_sec = milliSecs / MILLISEC_PER_SEC;
  tv.tv_usec = 0;

  ret = select (maxFd + 1, &allfds, NULL, NULL, &tv);

  if (ret < 0)
    {
      MTP2_ERROR (("WaitForIndication: select returned error=%d.\n", errno));

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
      //MTP2_DEBUG (("WaitForIndication: Check which FD has data.\n"));

      if (fromVend)
	{
//	  for (i = 0; i < ITS_SS7_CTXT_NUMLINKS (ctxt); i++)
	  for (i = 0; i < MAX_LINK_CODES; i++)
	    {
              if(ITS_SS7_CTXT_DLINK (ctxt)[i].fd<=0)
              {
               continue;
              }  
	      if (FD_ISSET (ITS_SS7_CTXT_DLINK (ctxt)[i].fd, &allfds))
		{
		 // MTP2_DEBUG (("WaitForIndication: FD = %d \n", ITS_SS7_CTXT_DLINK (ctxt)[i].fd));

		  ITS_SS7_CTXT_IDXMAP (ctxt) |= (1 << i);
		}
	    }
	}
      else
	{
	  ctxt = manager.head;

	  while (ctxt)
	    {
	  //    for (i = 0; i < ITS_SS7_CTXT_NUMLINKS (ctxt); i++)
	     for (i = 0; i < MAX_LINK_CODES; i++)
	      {
                if(ITS_SS7_CTXT_DLINK (ctxt)[i].fd<=0)
                {
                 continue;
                }   
		  if (FD_ISSET (ITS_SS7_CTXT_DLINK (ctxt)[i].fd, &allfds))
		    {
		     // MTP2_DEBUG (("WaitForIndication: FD = %d \n", ITS_SS7_CTXT_DLINK (ctxt)[i].fd));
		      ITS_SS7_CTXT_IDXMAP (ctxt) |= (1 << i);
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
Record_MTP2ConfigData (ITS_SS7_CONTEXT * ctxt, ITS_INT idx,
		       MTP2_SIGNAL_TYPE sig, char *data, ITS_INT len)
{
  ITS_INT ret = ITS_SUCCESS;
  char *ptr;
  ITS_EVENT ev;
  NwstkScmMtp2PegResponse Mtp2PegResponse;
  MTP2_PerfData *PegResp = (MTP2_PerfData *)&data[3];

 if(sig==MTP2_SIGNAL_PEGS)
 {
  MTP2_DEBUG(("Record_MTP2ConfigData::L2_L3_CURRENT_PEGS linSet %d linkCode %d",ITS_SS7_CTXT_LINKSET (ctxt),ctxt->dlink[idx].linkCode)); 

  Mtp2PegResponse.linkId= ctxt->dlink[idx].linkCode;
  Mtp2PegResponse.linkSetId=ITS_SS7_CTXT_LINKSET (ctxt);

  MTP2_DEBUG(("From MTP2::"));
  MTP2_DEBUG(("Pegs:SLFail_abnormBSNR %d",PegResp->SLFail_abnormBSNR));
  MTP2_DEBUG(("Pegs:SLFail_abnormFIBR %d",PegResp->SLFail_abnormFIBR));
  MTP2_DEBUG(("Pegs:SLFail_T7 %d",PegResp->SLFail_T7));
  MTP2_DEBUG(("Pegs:SLFail_suerm %d",PegResp->SLFail_suerm));
  MTP2_DEBUG(("Pegs:SLFail_cong %d",PegResp->SLFail_cong));
  MTP2_DEBUG(("Pegs:ALFail_T2T3 %d",PegResp->ALFail_T2T3));
  MTP2_DEBUG(("Pegs:ALFail_aerm %d",PegResp->ALFail_aerm));
  MTP2_DEBUG(("Pegs:numNegAck %d",PegResp->numNegAck));
  MTP2_DEBUG(("Pegs:numErrSu %d",PegResp->numErrSu));
  MTP2_DEBUG(("Pegs:SIBtx %d",PegResp->SIBtx));
  MTP2_DEBUG(("Pegs:SIBrx %d",PegResp->SIBrx));
  MTP2_DEBUG(("Pegs:N1rtx %d",PegResp->N1rtx));
  MTP2_DEBUG(("Pegs:N2rtx %d",PegResp->N2rtx));
  MTP2_DEBUG(("Pegs:MSUrtx %d",PegResp->MSUrtx));
  MTP2_DEBUG(("Pegs:MSUrtx_octets %d",PegResp->MSUrtx_octets));
  MTP2_DEBUG(("Pegs:MSUhsrx %d",PegResp->MSUhsrx));
  MTP2_DEBUG(("Pegs:MSUhstx %d",PegResp->MSUhstx));
  MTP2_DEBUG(("Pegs:MSUrx %d",PegResp->MSUrx));
  MTP2_DEBUG(("Pegs:MSUtx %d",PegResp->MSUtx));
  MTP2_DEBUG(("Pegs:MSUtx_octets %d",PegResp->MSUtx_octets));
  MTP2_DEBUG(("Pegs:MSUrx_octets %d",PegResp->MSUrx_octets));
  MTP2_DEBUG(("Pegs:RQThresCross %d",PegResp->RQThresCross));
  MTP2_DEBUG(("Pegs:TQThresCross %d",PegResp->TQThresCross));
  MTP2_DEBUG(("Pegs:TBThresCross %d",PegResp->TBThresCross));

  memcpy(&(Mtp2PegResponse.mtp2PegsLinkFailAbnBSNR),PegResp,sizeof(MTP2_PerfData));

  MTP2_DEBUG(("TO SCM:"));
  MTP2_DEBUG(("Pegs:SLFail_abnormBSNR %d",Mtp2PegResponse.mtp2PegsLinkFailAbnBSNR));
  MTP2_DEBUG(("Pegs:SLFail_abnormFIBR %d",Mtp2PegResponse.mtp2PegsLinkFailAbnFIBR));
  MTP2_DEBUG(("Pegs:SLFail_T7 %d",Mtp2PegResponse.mtp2PegsLinkFailT7Exp));
  MTP2_DEBUG(("Pegs:SLFail_suerm %d",Mtp2PegResponse.mtp2PegsLinkFailSUERM));
  MTP2_DEBUG(("Pegs:SLFail_cong %d",Mtp2PegResponse.mtp2PegsLinkFailCongetion));
  MTP2_DEBUG(("Pegs:ALFail_T2T3 %d",Mtp2PegResponse.mtp2PegsLinkAlgnmntFailT2T3));
  MTP2_DEBUG(("Pegs:ALFail_aerm %d",Mtp2PegResponse.mtp2PegsLinkAlgnmntFailAERM));
  MTP2_DEBUG(("Pegs:numNegAck %d",Mtp2PegResponse.mtp2PegsNumOfNegativeAck));
  MTP2_DEBUG(("Pegs:numErrSu %d",Mtp2PegResponse.mtp2PegsNumOfSUsErr));
  MTP2_DEBUG(("Pegs:SIBtx %d",Mtp2PegResponse.mtp2PegsSIBTx));
  MTP2_DEBUG(("Pegs:SIBrx %d",Mtp2PegResponse.mtp2PegsSIBRx));
  MTP2_DEBUG(("Pegs:N1rtx %d",Mtp2PegResponse.mtp2PegsN1RetransTx));
  MTP2_DEBUG(("Pegs:N2rtx %d",Mtp2PegResponse.mtp2PegsN2RetransTx));
  MTP2_DEBUG(("Pegs:MSUrtx %d",Mtp2PegResponse.mtp2PegsMSURetransTx));
  MTP2_DEBUG(("Pegs:MSUrtx_octets %d",Mtp2PegResponse.mtp2PegsMSURetransOctTx));
  MTP2_DEBUG(("Pegs:MSUhsrx %d",Mtp2PegResponse.mtp2PegsNoOfMSURxFromMtp3));
  MTP2_DEBUG(("Pegs:MSUhstx %d",Mtp2PegResponse.mtp2PegsNoOfMSUTxToMtp3));
  MTP2_DEBUG(("Pegs:MSUrx %d",Mtp2PegResponse.mtp2PegsNoOfMSURxFromMCC));
  MTP2_DEBUG(("Pegs:MSUtx %d",Mtp2PegResponse.mtp2PegsNoOfMSUTxToMCC));
  MTP2_DEBUG(("Pegs:MSUtx_octets %d",Mtp2PegResponse.mtp2PegsNoOfMSUOctTxToMCC));
  MTP2_DEBUG(("Pegs:MSUrx_octets %d",Mtp2PegResponse.mtp2PegsRQThresCross));
  MTP2_DEBUG(("Pegs:RQThresCross %d",Mtp2PegResponse.mtp2PegsTQThresCross));
  MTP2_DEBUG(("Pegs:TQThresCross %d",Mtp2PegResponse.mtp2PegsTBThresCross));
  MTP2_DEBUG(("Pegs:TBThresCross %d",Mtp2PegResponse.mtp2PegsRTBThresCross));


  ITS_EVENT_INIT(&ev,ITS_MTP2_SRC,sizeof(NwstkScmMtp2PegResponse));
  memcpy(&ev.data[0],&Mtp2PegResponse,sizeof(NwstkScmMtp2PegResponse));
  ret=TRANSPORT_PutEvent(ITS_ISUP_SRC,&ev);
  if(ret!=ITS_SUCCESS)
  {
    MTP2_ERROR(("PegResponse :: TRANSPORT_PutEvent Fail"));
  }
 }
 else
 {
  ptr = ITS_SS7_CTXT_DLINK (ctxt)[idx].configData[sig];
  if (ptr == NULL)
    {
      ptr = calloc (1, sizeof (MTP2_Signal));

      ITS_SS7_CTXT_DLINK (ctxt)[idx].configData[sig] = ptr;

      if (!ptr)
	{
	  ret = ITS_ENOMEM;
	}
    }

  if (ptr && len <= sizeof (MTP2_Signal))
    {
      memcpy (ptr, data, len);
    }

 }
  return ret;
}

static ITS_INT
ReadDataFromDev (ITS_SS7_CONTEXT * ctxt, ITS_INT idx, ITS_BOOLEAN fromVend)
{
  ITS_OCTET data[MAX_MTP2_RXTX_DATA];
  const ITS_UINT dlen = MAX_MTP2_RXTX_DATA;
  ITS_INT ret;
  MTP2_SIGNAL_TYPE sig;
  int i = 0, j = 0;
//  char buff[1024 + 40];
#ifdef TRACE_DUMP
  ITS_OCTET *buff = NULL;
  ITS_OCTET TempBuffer[10];
  ITS_INT count = 0;
#endif 
  int len = 0;
  char buff[1024 + 40];;
  ITS_INT k = 0, l = 0;


  ret = read (ctxt->dlink[idx].fd, (char *) data, dlen);

  if ((ret > 0) && (ret <= MAX_MTP2_RXTX_DATA))
    {
      MTP2_DEBUG (("ReadDataFromDev: fd = %d len = %d \n",
		   ctxt->dlink[idx].fd, ret));

/* No use
   if (ret >= 30)
	{
	  len = 30;
	}
  else
	{
	  len = ret;
	}
*/
/***************** To Print the Data Received on MTP2 Channel****/
  MTP2_DEBUG (("*****ReadDataFromDev**** %d \n", ret));
   len=ret;
  if (len < 100)
    {
      for (k = 0; k < len; k++)
	{
	  l += sprintf (&buff[l], "0x%02x ", data[k]);
	  if (k && k % 16 == 0)
	    {
	      l += sprintf (&buff[l], "\n");
	    }
	}
    }
  else
    {
      MTP2_DEBUG (("***** ReadDataFromDev len is  >100********** %d \n", len));
      for (k = 0; k < 100; k++)
	{
	  l += sprintf (&buff[l], "0x%02x ", data[k]);
	  if (k && k % 16 == 0)
	    {
	      l += sprintf (&buff[l], "\n");
	    }
	}
    }

  MTP2_DEBUG (("ReadDataFromDev: %s\n", buff));

/***************** To Print the Data Received on MTP2 Channel****/
#ifdef TRACE_DUMP
      buff = (ITS_OCTET *) calloc (len * 6 + 1, sizeof (ITS_OCTET));

  for (count = 0; count < len; count++)	/*only 100 bytes will print */
	{
	  sprintf ((char *) TempBuffer, "0x%02x ", data[count]);
	  strcat ((char *) buff, (const char *) TempBuffer);

	  if (!(count % 15) && (count != 0))
	    {
	      strcat ((char *) buff, "\n");
	    }
	}

      MTP2_DEBUG (("%02s", buff));
      free (buff);
#endif

/*      for (i = 0; i < ret; i++)
	{
	  j += sprintf (&buff[j], "0x%02x ", data[i]);

	  if (i && i % 16 == 0)
	    {
	      j += sprintf (&buff[j++], "\n");
	    }
	}

      MTP2_DEBUG (("%s \n", buff));*/

      /* The data could be any of the following.
       * 1. MTP2 DATA Signals.
       * 2. Configuration.
       * 3. Statistics.
       * 4. Trace configuration.
       */
      sig = MTP2_RX_SIGNAL_TYPE (data[0]);
  
      
      switch (sig)
	{
	case MTP2_SIGNAL_DATA:
	  ret = Build_MTP2Event (ctxt, idx, data, ret);
	  break;

	case MTP2_SIGNAL_TRACE:
	case MTP2_SIGNAL_CONFIG:
	case MTP2_SIGNAL_PEGS:
       MTP2_DEBUG(("PEGS RESPONSE signal %x %x \n",sig, MTP2_SIGNAL_PEGS)); 
	  ret = Record_MTP2ConfigData (ctxt, idx, sig, data, ret);
	  break;

	default:
	  ret = ITS_ENOMEM;
	  break;
	}
    }
  else
    {
      MTP2_ERROR (("Read return fd = %d error = %d \n", ctxt->dlink[idx].fd,
		   errno));
      ret = ITS_ENOMEM;
    }

  return ret;
}

ITS_INT
IMTP2_WaitForIndication (ITS_SS7_HANDLE handle, int *indic_flag, int millSecs)
{
  /* TODO: Implement for border Transport */

  return ITS_SUCCESS;
}

THREAD_RET_TYPE
CCITT_MTP2_RcvThread (void *args)
{
  ITS_INT ret = ITS_SUCCESS;
  ITS_INT i = 0;
  ITS_UINT indic_flag;
  ITS_SS7_CONTEXT *ctxt = NULL;
  ITS_INT millSecs = 10000;

  while (!isSetExitMTP2)
    {
      ret = WaitForIndication (NULL, &indic_flag, millSecs, ITS_FALSE);

      switch (ret)
	{
	case ITS_ETIMEOUT:
	  MTP2_DEBUG (("CCITT_MTP2_RcvThread: Select timedout no data "
		       "from dev.\n"));
	  continue;
	  break;

	case ITS_SUCCESS:
	  break;

	default:
	  MTP2_DEBUG (("@@@@@@@@ EXITING Loop @@@@@@@@@@@@@@\n"));
	  /* Fault has happend */
	  /* isSetExitMTP2 = ITS_TRUE; */
	  continue;
	  break;
	}

      ctxt = manager.head;

      while (ctxt)
	{
//	  while (ITS_SS7_CTXT_IDXMAP (ctxt)
//		 && i < ITS_SS7_CTXT_NUMLINKS (ctxt))
	    while (ITS_SS7_CTXT_IDXMAP (ctxt)  && (i < MAX_LINK_CODES))
	    {
	      if (ITS_SS7_CTXT_IDXMAP (ctxt) & (1 << i))
		{
		  ret = ReadDataFromDev (ctxt, i, ITS_FALSE);

		  if (ret != ITS_SUCCESS)
		    {
		      MTP2_ERROR (("CCITT_MTP2_RcvThread: Read error occured. error = %d\n", errno));
/*
                        MTP2_ERROR(("CCITT_MTP2_RcvThread: Read error occured."
                                    " Set Rcv/Send thread to Exit state.\n"));
*/
		      /* isSetExitMTP2 = ITS_TRUE; */
		    }
		  ITS_SS7_CTXT_IDXMAP (ctxt) &= ~(1 << i);
		}

	      i++;
	    }

	  ctxt = ctxt->next;
	  i = 0;
	}

    }

  MTP2_ERROR (("CCITT_MTP2_RcvThread: Exit loop.\n"));

  THREAD_NORMAL_EXIT;
}



int
mtp2_modify(ITS_EVENT *ev)
{
  NwStkHdr *hdr=(NwStkHdr*)ev->data;
  MTP2_ConfigData mtp2Config; 
  MTP2_Signal txdata ;
  ITS_SS7_CONTEXT *context;
  ITS_UINT tofd,dlen,ret,Ret;
  ScmNwstkMtp2PegGet *Mtp2PegGet;
 
  memset(&mtp2Config,0,sizeof(MTP2_ConfigData));
  memset(&txdata,0,sizeof(MTP2_Signal));

 
  switch(hdr->opcode)
  {
  case SCM_NWSTK_LINK_ADMIN_STATE_MODIFY:
      {
        ScmNwstkLinkAdminStateModify *mtp2timerevt =(ScmNwstkLinkAdminStateModify *)ev->data;
        ScmNwstkMtp2TimerModify *mtp2timer = &(mtp2timerevt->scmNwstkMtp2TimerModify);

        MTP2_DEBUG(("mtp2_modify::Timer\n"));
        MTP2_DEBUG(("mtp2timer mtp2TimerT1 %d",mtp2timer->mtp2TimerT1));
        MTP2_DEBUG(("mtp2timer mtp2TimerT2 %d",mtp2timer->mtp2TimerT2));
        MTP2_DEBUG(("mtp2timer mtp2TimerT3 %d",mtp2timer->mtp2TimerT3));
        MTP2_DEBUG(("mtp2timer mtp2TimerT4 %d",mtp2timer->mtp2TimerT4));
        MTP2_DEBUG(("mtp2timer mtp2TimerT5 %d",mtp2timer->mtp2TimerT5));
        MTP2_DEBUG(("mtp2timer mtp2TimerT6 %d",mtp2timer->mtp2TimerT6));
        MTP2_DEBUG(("mtp2timer mtp2TimerT7 %d",mtp2timer->mtp2TimerT7));
        MTP2_DEBUG(("mtp2timer mtp2EmrgncyProvngPriod  %d",mtp2timer->mtp2EmrgncyProvngPriod));
        MTP2_DEBUG(("mtp2timer mtp2NormalProvngPriod   %d",mtp2timer->mtp2NormalProvngPriod));
        MTP2_DEBUG(("mtp2timer mtp2PCRFlag  %d",mtp2timer->mtp2PCRFlag));
        MTP2_DEBUG(("mtp2timer mtp2RcvOnset %d",mtp2timer->mtp2RcvOnset));
        MTP2_DEBUG(("mtp2timer mtp2RcvAbates %d",mtp2timer->mtp2RcvAbates));
        MTP2_DEBUG(("mtp2timer mtp2TxOnset1 %d",mtp2timer->mtp2TxOnset1));
        MTP2_DEBUG(("mtp2timer mtp2TxOnset2 %d",mtp2timer->mtp2TxOnset2));
        MTP2_DEBUG(("mtp2timer mtp2TxOnset3  %d",mtp2timer->mtp2TxOnset3));
        MTP2_DEBUG(("mtp2timer mtp2TxAbetes1 %d",mtp2timer->mtp2TxAbetes1));
        MTP2_DEBUG(("mtp2timer mtp2TxAbetes2 %d",mtp2timer->mtp2TxAbetes2));
        MTP2_DEBUG(("mtp2timer mtp2TxAbetes3 %d",mtp2timer->mtp2TxAbetes3));
        mtp2Config.T1  =mtp2timer->mtp2TimerT1;
        mtp2Config.T2  =mtp2timer->mtp2TimerT2;
        mtp2Config.T3  =mtp2timer->mtp2TimerT3;
        mtp2Config.T4  =mtp2timer->mtp2TimerT4;
        mtp2Config.T5  =mtp2timer->mtp2TimerT5;
        mtp2Config.T6  =mtp2timer->mtp2TimerT6;
        mtp2Config.T7  =mtp2timer->mtp2TimerT7;
        mtp2Config.Pn  =mtp2timer->mtp2EmrgncyProvngPriod;
        mtp2Config.Pe  =mtp2timer->mtp2NormalProvngPriod;
        mtp2Config.PCR =mtp2timer->mtp2PCRFlag;
        mtp2Config.rcOnset   =mtp2timer->mtp2RcvOnset;
        mtp2Config.rcAbates  =mtp2timer->mtp2RcvAbates;
        mtp2Config.txOnset1   =mtp2timer->mtp2TxOnset1;
        mtp2Config.txOnset2   =mtp2timer->mtp2TxOnset2;
        mtp2Config.txOnset3   =mtp2timer->mtp2TxOnset3;
        mtp2Config.txAbates1  =mtp2timer->mtp2TxAbetes1;
        mtp2Config.txAbates2  =mtp2timer->mtp2TxAbetes2;
        mtp2Config.txAbates3  =mtp2timer->mtp2TxAbetes3;
        #define PRINTTMR(A,C) \
        MTP2_DEBUG((A,mtp2Config.C));

        PRINTTMR("mtp2Config T1 :  %d",T1);
        PRINTTMR("mtp2Config T2 :  %d",T2);
        PRINTTMR("mtp2Config T3 :  %d",T3);
        PRINTTMR("mtp2Config T4 :  %d",T4);
        PRINTTMR("mtp2Config T5 :  %d",T5);
        PRINTTMR("mtp2Config T6 :  %d",T6);
        PRINTTMR("mtp2Config T7 :  %d",T7);
        PRINTTMR("mtp2Config Pn :  %d",Pn);
        PRINTTMR("mtp2Config Pe :  %d",Pe);
        PRINTTMR("mtp2Config PCR :  %d",PCR);
        PRINTTMR("mtp2Config rcOnset :  %d",rcOnset);
        PRINTTMR("mtp2Config rcAbates :  %d",rcAbates);
        PRINTTMR("mtp2Config txOnset1 :  %d",txOnset1);
        PRINTTMR("mtp2Config txOnset2 :  %d",txOnset2);
        PRINTTMR("mtp2Config txOnset3 :  %d",txOnset3);
        PRINTTMR("mtp2Config txAbates1 :  %d",txAbates1);
        PRINTTMR("mtp2Config txAbates2 :  %d",txAbates2);
        PRINTTMR("mtp2Config txAbates3 :  %d",txAbates3);


         txdata.signal=L3_L2_SET_CONFIG_NEW;
         txdata.linkSet=mtp2timerevt->linkSetId;
         txdata.linkCode=mtp2timerevt->linkId;
         memcpy(txdata.data.sif,&mtp2Config,sizeof(MTP2_ConfigData)); 
         
         context = manager.context[mtp2timerevt->linkSetId];         
         if(context==NULL)
         {
           MTP2_ERROR(("mtp2_modify:LinkSet not Found"));
           MTP2_DEBUG (("mtp2_modify: Post Sema Enrty"));
           TIMERCONFIG=0;
           Ret=SEMA_PostSemaphore(&mtp2_sema);
           if(Ret!=ITS_SUCCESS)
             {
                MTP2_ERROR (("mtp2_modify: Entry not Added"));
             }
           else
             { 
               MTP2_DEBUG (("mtp2_modify: Post Sema Success"));
             }
           break;
        }   
         tofd = context->dlink[mtp2timerevt->linkId].fd;
         MTP2_DEBUG(("mtp2_modify::fd %d linkSet %d linkCode %d \n",tofd,mtp2timerevt->linkSetId,mtp2timerevt->linkId));
         if(tofd > 0) 
         { 
              dlen=sizeof(MTP2_ConfigData) + 3 *sizeof(ITS_OCTET); 
              ret = SendDataToDev (tofd, (char *) &txdata,dlen);
              if (ret != dlen)
               {
                MTP2_WARNING (("IMTP2_Send_CCITT: Device could not send"
                              " specified len (%d) of data\n", dlen));
   
               }
              else
               {
                TIMERCONFIG=1; 
               } 
         }
        else
         {
            MTP2_DEBUG(("mtp2_modify::Timer Fd Invalid \n"));

         }
           MTP2_DEBUG (("mtp2_modify: Post Sema Enrty"));
           Ret=SEMA_PostSemaphore(&mtp2_sema);
           if(Ret!=ITS_SUCCESS)
           {
             MTP2_ERROR (("mtp2_modify: Entry not Added"));
           }
          else
           { 
             MTP2_DEBUG (("mtp2_modify: Post Sema Success"));
           }
            
     }
   break;
   case SCM_NWSTK_MTP2_PEG_GET:
     {  
          Mtp2PegGet = (ScmNwstkMtp2PegGet *)ev->data;

           MTP2_DEBUG(("mtp2_modify::peg %d\n",Mtp2PegGet->pegResetFlag));
          if(Mtp2PegGet->pegResetFlag)
          {
             txdata.signal=L3_L2_RESET_PEGS_NEW;
             txdata.linkSet=Mtp2PegGet->linkSetId;
             txdata.linkCode=Mtp2PegGet->linkId;
              

          }
         else
          {
             txdata.signal=L3_L2_GET_PEGS_NEW;
             txdata.linkSet=Mtp2PegGet->linkSetId;
             txdata.linkCode=Mtp2PegGet->linkId;


          }
         context = manager.context[Mtp2PegGet->linkSetId];        
         if(context==NULL)
         {
           MTP2_ERROR(("mtp2_modify:LinkSet not Found"));
           MTP2_DEBUG (("mtp2_modify: Post Sema Enrty"));
           PEGCONFIG=1; 
           Ret=SEMA_PostSemaphore(&mtp2_sema);
           if(Ret!=ITS_SUCCESS)
             {
                MTP2_ERROR (("mtp2_modify: Entry not Added"));
             }
           else
             { 
               MTP2_DEBUG (("mtp2_modify: Post Sema Success"));
             }
           break;
        }   
         tofd = context->dlink[Mtp2PegGet->linkId].fd;
         MTP2_DEBUG(("mtp2_modify::fd %d linkSet %d linkCode %d \n",tofd,Mtp2PegGet->linkSetId,Mtp2PegGet->linkId));
         if(tofd > 0) 
         { 
              dlen=3 *sizeof(ITS_OCTET); 
              ret = SendDataToDev (tofd, (char *) &txdata,dlen);
              if (ret != dlen)
               {
                MTP2_WARNING (("IMTP2_Send_CCITT: Device could not send"
                              " specified len (%d) of data\n", dlen));
   
               }
              else
               {
                PEGCONFIG=1; 
               } 
           MTP2_DEBUG (("mtp2_modify: Post Sema Enrty"));
           Ret=SEMA_PostSemaphore(&mtp2_sema);
           if(Ret!=ITS_SUCCESS)
           {
             MTP2_ERROR (("mtp2_modify: Entry not Added"));
           }
          else
           { 
             MTP2_DEBUG (("mtp2_modify: Post Sema Success"));
           }
         }
      }
     break;
     
      default:
          MTP2_ERROR(("Unknown Signal\n"));
     }

}








THREAD_RET_TYPE
CCITT_MTP2_SendThread (void *args)
{
  ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *) (args);
  ITS_EVENT mtp2Event;
  ITS_INT ret;

  ITS_EVENT_INIT (&mtp2Event, 0, 0);

  while (!isSetExitMTP2 &&
	 TRANSPORT_CLASS_GET_NEXT_EVENT (ITS_OBJ_CLASS
					 (__MTP2_CCITT_RcvQueue))
	 (__MTP2_CCITT_RcvQueue, &mtp2Event) == ITS_SUCCESS)
    {
      switch (mtp2Event.src)
	{
	case ITS_MTP3_SRC:

	  MTP2_DEBUG (("CCITT_MTP2_SendThread Got data from MTP3.\n"));

	  if ((mtp2Event.data[0] == ln_add_cmd)
	      || (mtp2Event.data[0] == ln_del_cmd))
	    {
	      ret = ln_config (mtp2Event);
	      if (ret != ITS_SUCCESS)
		{
		  MTP2_DEBUG (("ln_config:addition or deletion fail\n"));
		}
		  MTP2_DEBUG (("ln_config:\n"));
	    }
	  else
	    {
	      context = manager.context[L2_LINK_SET (&mtp2Event)];

	      if (context == NULL)
		{
		  MTP2_ERROR (("CCITT_MTP2_SendThread: Could not find LinkSet(%d)"
			       " context.\n", L2_LINK_SET (&mtp2Event)));
		}
	      else
		{
		  ret =
		    IMTP2_Send_CCITT (context, mtp2Event.data, mtp2Event.len);
		}
	    }
	  break;

  case ITS_DEFAULT_SRC:
        MTP2_ERROR(("CCITT_MTP2_SendThread::MTP2 Config"));
        mtp2_modify(&mtp2Event);

  break; 
	case ITS_MTP2_SRC:
	  MTP2_ERROR (("CCITT_MTP2_SendThread: Exiting MTP2 loop...\n"));
	  /* isSetExitMTP2 = ITS_TRUE; */
	  break;
   

	default:
	  break;
	}
     ITS_EVENT_TERM(&mtp2Event);
    }

  MTP2_ERROR (("CCITT_MTP2_SendThread: Exit loop.\n"));

  THREAD_NORMAL_EXIT;
}

static void
InitTraceData ()
{
  RESFILE_Manager *res = TRANSPORT_RES (__MTP2_CCITT_RcvQueue);;
  char value[ITS_PATH_MAX];
  char *name = TRANSPORT_NAME (__MTP2_CCITT_RcvQueue);


  if (res != NULL)
    {
      /* critical */
      if (RESFILE_GetKeyValueOf (res, name, MTP2_TRACE_CRITICAL_STRING,
				 value, ITS_PATH_MAX) == ITS_SUCCESS)
	{
	  ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

	  if (strstr (value, MTP2_STDOUT_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_CRITICAL_STRING,
					  MTP2_STDOUT_STRING, ITS_TRUE);
	      std = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_CRITICAL_STRING,
					  MTP2_STDOUT_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_FILE_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_CRITICAL_STRING,
					  MTP2_FILE_STRING, ITS_TRUE);
	      fil = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_CRITICAL_STRING,
					  MTP2_FILE_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_SYSLOG_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_CRITICAL_STRING,
					  MTP2_SYSLOG_STRING, ITS_TRUE);
	      sys = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_CRITICAL_STRING,
					  MTP2_SYSLOG_STRING, ITS_FALSE);
	    }

	  if (std || fil || sys)
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_CRITICAL_STRING, ITS_TRUE);
	    }
	  else
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_CRITICAL_STRING, ITS_FALSE);
	    }
	}

      /* error */
      if (RESFILE_GetKeyValueOf (res, name, MTP2_TRACE_ERROR_STRING,
				 value, ITS_PATH_MAX) == ITS_SUCCESS)
	{
	  ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

	  if (strstr (value, MTP2_STDOUT_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_ERROR_STRING,
					  MTP2_STDOUT_STRING, ITS_TRUE);
	      std = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_ERROR_STRING,
					  MTP2_STDOUT_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_FILE_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_ERROR_STRING,
					  MTP2_FILE_STRING, ITS_TRUE);
	      fil = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_ERROR_STRING,
					  MTP2_FILE_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_SYSLOG_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_ERROR_STRING,
					  MTP2_SYSLOG_STRING, ITS_TRUE);
	      sys = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_ERROR_STRING,
					  MTP2_SYSLOG_STRING, ITS_FALSE);
	    }

	  if (std || fil || sys)
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_ERROR_STRING, ITS_TRUE);
	    }
	  else
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_ERROR_STRING, ITS_FALSE);
	    }
	}

      /* warning */
      if (RESFILE_GetKeyValueOf (res, name, MTP2_TRACE_WARNING_STRING,
				 value, ITS_PATH_MAX) == ITS_SUCCESS)
	{
	  ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

	  if (strstr (value, MTP2_STDOUT_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_WARNING_STRING,
					  MTP2_STDOUT_STRING, ITS_TRUE);
	      std = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_WARNING_STRING,
					  MTP2_STDOUT_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_FILE_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_WARNING_STRING,
					  MTP2_FILE_STRING, ITS_TRUE);
	      fil = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_WARNING_STRING,
					  MTP2_FILE_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_SYSLOG_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_WARNING_STRING,
					  MTP2_SYSLOG_STRING, ITS_TRUE);
	      sys = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_WARNING_STRING,
					  MTP2_SYSLOG_STRING, ITS_FALSE);
	    }

	  if (std || fil || sys)
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_WARNING_STRING, ITS_TRUE);
	    }
	  else
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_WARNING_STRING, ITS_FALSE);
	    }
	}

      /* debug */
      if (RESFILE_GetKeyValueOf (res, name, MTP2_TRACE_DEBUG_STRING,
				 value, ITS_PATH_MAX) == ITS_SUCCESS)
	{
	  ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

	  if (strstr (value, MTP2_STDOUT_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_DEBUG_STRING,
					  MTP2_STDOUT_STRING, ITS_TRUE);
	      std = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_DEBUG_STRING,
					  MTP2_STDOUT_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_FILE_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_DEBUG_STRING,
					  MTP2_FILE_STRING, ITS_TRUE);
	      fil = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_DEBUG_STRING,
					  MTP2_FILE_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_SYSLOG_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_DEBUG_STRING,
					  MTP2_SYSLOG_STRING, ITS_TRUE);
	      sys = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_DEBUG_STRING,
					  MTP2_SYSLOG_STRING, ITS_FALSE);
	    }

	  if (std || fil || sys)
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_DEBUG_STRING, ITS_TRUE);
	    }
	  else
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_DEBUG_STRING, ITS_FALSE);
	    }
	}

      /* Event */
      if (RESFILE_GetKeyValueOf (res, name, MTP2_TRACE_EVENT_STRING,
				 value, ITS_PATH_MAX) == ITS_SUCCESS)
	{
	  ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

	  if (strstr (value, MTP2_STDOUT_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_EVENT_STRING,
					  MTP2_STDOUT_STRING, ITS_TRUE);
	      std = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_EVENT_STRING,
					  MTP2_STDOUT_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_FILE_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_EVENT_STRING,
					  MTP2_FILE_STRING, ITS_TRUE);

	      fil = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_EVENT_STRING,
					  MTP2_FILE_STRING, ITS_FALSE);
	    }
	  if (strstr (value, MTP2_SYSLOG_STRING) != NULL)
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_EVENT_STRING,
					  MTP2_SYSLOG_STRING, ITS_TRUE);
	      sys = ITS_TRUE;
	    }
	  else
	    {
	      TRACE_SetOutputOnOffByName (MTP2_CCITT_TraceData,
					  MTP2_EVENT_STRING,
					  MTP2_SYSLOG_STRING, ITS_FALSE);
	    }

	  if (std || fil || sys)
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_EVENT_STRING, ITS_TRUE);
	    }
	  else
	    {
	      TRACE_SetLevelOnOffByName (MTP2_CCITT_TraceData,
					 MTP2_EVENT_STRING, ITS_FALSE);
	    }
	}

    }
  return;
}

static ITS_INT
MTP2Bind (ITS_SS7_CONTEXT * ctxt)
{
  char devName[MAX_DEV_NAME_LEN];
  struct mtp2_cfg mtp2Cfg;
  ITS_INT i = 0;
  ITS_OCTET NONE_ENTRY = 0;
  for (; i < MAX_LINK_CODES ; i++)
   {
      if (!mtp2Inited)
	    {
	       LINKCODE = ITS_SS7_CTXT_DLINK (ctxt)[i].linkCode;
	     /* MTP2_DEBUG (("MTP2Bind at Init:linkcode %d,linkcode %d \n",
		       ITS_SS7_CTXT_DLINK (ctxt)[i].linkCode, LINKCODE));*/
	    }
        /*   MTP2_DEBUG (("MTP2Bind :linkcode %d,linkcode %d \n",
		   ITS_SS7_CTXT_DLINK (ctxt)[i].linkCode, LINKCODE));*/
      if (ITS_SS7_CTXT_DLINK (ctxt)[i].linkCode == LINKCODE)
	{
	  snprintf (devName, MAX_DEV_NAME_LEN, MTP2_DEV_NAME,
		    ITS_SS7_CTXT_DLINK (ctxt)[i].channelNum );

#if NOT_USING_UTIL

	  MT2_DEBUG (("***** MTP2Bind IN  NOT_USING_UTIL **********\n"));
	  mtp2Cfg.num_chan = 1;
	  mtp2Cfg.channels[0].chan = ITS_SS7_CTXT_DLINK (ctxt)[i].channelNum;
	  mtp2Cfg.channels[0].mode = MCC_TYPE_SS7;
	  mtp2Cfg.channels[0].loop = 0;	/* 0: no loopback */
	  if (ioctl (manager.configFD, MCC_IOCSCONFIG, &mtp2Cfg) < 0)
	    {
	      MTP2_DEBUG (("MTP2Bind: Could not Configure the Device "));
	    }

	  /* Enable control device */
	  if (ioctl (manager.configFD, MCC_IOCENABLE, NULL) < 0)
	    {
	      MTP2_DEBUG (("MTP2Bind: Could not Enable the Device "));
	    }

	  close (manager.configFD);	/* Now I see why I should build the
					 * mtp2 ctrl utility for channel configuration
					 */
	  manager.configFD = -1;	/* set to invalid data */
#endif

	  ITS_SS7_CTXT_DLINK (ctxt)[i].fd = open (devName, O_RDWR);

	  MTP2_DEBUG (("MTP2 Bind: To Device %s | %s:%d\n", devName, __FILE__,
		       __LINE__));

	  if (ITS_SS7_CTXT_DLINK (ctxt)[i].fd < 0)
	    {
	      MTP2_ERROR (("MTP2Bind: Could not bind to the Device (%s) "
			   "error (%d)\n", devName, errno));

	      return ITS_ENOMEM;
	    }


	  MTP2_DEBUG (("MTP2Bind OPen file descriptor = %d \n",
		       ITS_SS7_CTXT_DLINK (ctxt)[i].fd));
	  ITS_SS7_CTXT_DLINK (ctxt)[i].active = ITS_TRUE;
	  NONE_ENTRY = 1;
	}
 }
  if (NONE_ENTRY == 0)
    {
      return -1;
    }
  return ITS_SUCCESS;

}

static ITS_INT
MTP2BindAllDev ()
{
  ITS_INT ret = ITS_SUCCESS;
  ITS_SS7_CONTEXT *ctxt = manager.head;

  for (; ctxt; ctxt = ctxt->next)
    {
      if (!mtp2Inited)
	{
	  LINKSET = ITS_SS7_CTXT_LINKSET (ctxt);
	  MTP2_DEBUG (("MTP2Bind at Init:linkset %d,linkset %d \n",
		       ITS_SS7_CTXT_LINKSET (ctxt), LINKSET));
	}

      MTP2_DEBUG (("MTP2Bind :linkset %d,linkset %d \n",
		   ITS_SS7_CTXT_LINKSET (ctxt), LINKSET));
      if (ITS_SS7_CTXT_LINKSET (ctxt) == LINKSET)
	{
	  ret = MTP2Bind (ctxt);

	  if (ret != ITS_SUCCESS)
	    {
	      return ret;
	    }
	}
    }

  return ITS_SUCCESS;
}

static void
RequestMTP2ConfigData ()
{
  ITS_INT i = 0, j = 0;
  ITS_SS7_CONTEXT *ctxt = manager.head;
  MTP2_Signal sig;
  ITS_INT tofd;
  ITS_INT ret;
  ITS_OCTET type[] = { L3_L2_GET_CONFIG,
    L3_L2_GET_TRACE,
    L3_L2_GET_PEGS
  };
  MTP2_DEBUG (("RequestMTP2ConfigData: \n"));

  memset (&sig, 0, sizeof (MTP2_Signal));

  for (; ctxt; ctxt = ctxt->next)
    {
      //for (i = 0; i < ITS_SS7_CTXT_NUMLINKS (ctxt); i++)
      for (i = 0; i < MAX_LINK_CODES; i++)
	{
	  tofd = ITS_SS7_CTXT_DLINK (ctxt)[i].fd;
          if(tofd <=0)
          {
           continue;
          } 

	  do
	    {
	      sig.signal = type[j++];
	      ret =
		SendDataToDev (tofd, (char *) &sig, MTP2_SIG_GET_CTS_SIZE);

	      if (ret != MTP2_SIG_GET_CTS_SIZE)
		{
		  MTP2_DEBUG (("RequestMTP2ConfigData: Error while write to"
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
IMTP2_Initialize (ITS_SS7_HANDLE handle)
{
  ITS_EVENT event;
  SS7_LinkPtr ln;
  ITS_SS7_CONTEXT *context;
  ITS_BOOLEAN isBorderConfig = ITS_FALSE;
  ITS_INT ret = 0, k = 0;
  ITS_INT idx;

  MTP2_DEBUG (("*******MTP2 Initialize %s:%d ********\n", __FILE__,
	       __LINE__));
  if (!mtp2Inited)
    {
      /* Static members initialization. Protecting from multiple invokes in 
       * case user prefers to use border transport
       */

      if ((MTP2_CCITT_TraceData = TRACE_Constructor ("ANSI-MTP2",
						     MTP2_TraceMap,
						     5)) == NULL)
	{
	  MTP2_DEBUG (("IMTP2_Initialize: Could not create trace Data.\n"));
	  return ITS_ENOMEM;
	}

      MTP2_DEBUG (("*** Creating MTP2 transport ***** %s:%d \n", __FILE__,
		   __LINE__));
      if ((__MTP2_CCITT_RcvQueue =
	   TQUEUETRAN_CreateTransport ("ANSI-MTP2", ITS_MTP2_ANSI_SRC,
				       ITS_MTP2_ANSI)) == NULL)
	{
	  MTP2_CRITICAL (("IMTP2_Initialize_CCITT:could not create transport.\n"));

	  /* Delete MTP2 specifics */
	  TRACE_Destructor (MTP2_CCITT_TraceData);

	  return ITS_ENOMEM;
	}

      /* Initialize MTP2 specifics here */
      InitTraceData ();

      memset (&manager, 0, sizeof (SS7CONTEXT_Manager));
#if NOT_USING_UTIL
      MTP2_DEBUG (("***** IMTP2_Initialize_CCITT IN  NOT_USING_UTIL **********\n"));
      manager.configFD = open (MCC_CTL_DEVICE_NAME, O_WRONLY);

      if (manager.configFD < 0)
	{
	  MTP2_ERROR (("IMTP2_Initialize_CCITT: failed to open CTL dev error%d\n", errno));

	  return ITS_ENOMEM;
	}
      MTP2_DEBUG (("IMTP2_Initialize_CCITT: opened CTL dev successfully\n"));

      /* Reset MCC controller */
      if (ioctl (manager.configFD, MCC_IOCRESET, NULL) < 0)
	{
	  MTP2_ERROR (("IMTP2_Initialize_CCITT: failed to reset MCC error%d\n", errno));

	  return ITS_ENOMEM;
	}
      MTP2_DEBUG (("IMTP2_Initialize_CCITT: Reset CTL dev successfully\n"));

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

  ln = TRANSPORT_SS7_INFO (__MTP2_CCITT_RcvQueue).linkInfo;

  if (!ln)
    {
      isBorderConfig = ITS_TRUE;

      /* TODO: 1. Lookup for the context using Transport ID.
       *       2. If not found Allocate context and add to the list.
       *       3. Bind to the Dev.
       */
      ret = MTP2Bind (context);
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
	  MTP2_WARNING (("IMTP2_Initialize: No linkSet for this link"
			 " (%d)...!\n", ln->linkCode));
	  continue;
	}

      if (manager.context[ln->linkSet->linkSet])
	{
	  context = manager.context[ln->linkSet->linkSet];
	}
      else
	{
	  context = (ITS_SS7_CONTEXT *) calloc (1, sizeof (ITS_SS7_CONTEXT));
	  manager.context[ln->linkSet->linkSet] = context;

	  ITS_SS7_CTXT_LINKSET (context) = ln->linkSet->linkSet;
          for (k = 0; k < MAX_LINK_CODES; k++)
          {
	     ITS_SS7_CTXT_DLINK (context)[k].linkCode = -1;
	     ITS_SS7_CTXT_DLINK (context)[k].active = ITS_FALSE;
	 }		/*linkCode zero may be valid */

	  SS7CONTEXT_ADD_HEAD (manager, context);
	}

      if (context == NULL)
	{
	  MTP2_CRITICAL (("IMTP2_Initialize_CCITT: Could not allocate context.\n"));

	  return ITS_ENOMEM;
	}

      idx = ITS_SS7_CTXT_NUMLINKS (context);

      ITS_SS7_CTXT_DLINK (context)[idx].linkCode = ln->linkCode;
      ITS_SS7_CTXT_DLINK (context)[idx].channelNum = ln->dataLink;
      ITS_SS7_CTXT_DLINK (context)[idx].active = ITS_FALSE;
      ITS_SS7_CTXT_NUMLINKS (context)++;

      /*  LINKSET=ln->linkSet->linkSet;
         LINKCODE=ln->linkCode; */
    }

  if (!isBorderConfig && !mtp2Inited)
    {
      ret = MTP2BindAllDev ();

      if (ret != ITS_SUCCESS)
	{
	  /* TODO: Close opened fd's and destroy all objects */
	}
      else
	{
	  /* Send request to the dev for config/trace/stats */
//	  RequestMTP2ConfigData ();
	}

      if (THREAD_CreateThread (&mtp2SendThread, 0, CCITT_MTP2_SendThread,
			       NULL, ITS_TRUE) != ITS_SUCCESS)
	{
	  MTP2_CRITICAL (("IMTP2_Initialize_CCITT:Could not create "
			  "ccitt-mtp2 thread.\n"));

	  TQUEUETRAN_DeleteTransport (__MTP2_CCITT_RcvQueue);

	  /* Delete mtp2 specifics */
	  TRACE_Destructor (MTP2_CCITT_TraceData);

	  return ITS_ENOMEM;
	}

      if (THREAD_CreateThread (&mtp2RcvThread, 0, CCITT_MTP2_RcvThread,
			       NULL, ITS_TRUE) != ITS_SUCCESS)
	{
	  MTP2_CRITICAL (("IMTP2_Initialize_CCITT:Could not create"
			  " ccitt-mtp2 thread.\n"));

	  ITS_EVENT_INIT (&event, ITS_MTP2_ANSI_SRC, 0);

	  /* to exit the send thread */
	  TRANSPORT_PutEvent (ITS_MTP2_ANSI_SRC, &event);

	  TQUEUETRAN_DeleteTransport (__MTP2_CCITT_RcvQueue);

	  /* Delete mtp2 specifics */
	  TRACE_Destructor (MTP2_CCITT_TraceData);

	  return ITS_ENOMEM;
	}
    }

  mtp2Inited = ITS_TRUE;

  MTP2_DEBUG (("******* ITS_MTP2 Initialization sucess *******\n"));
  fflush (stdout);
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
IMTP2_Terminate (ITS_SS7_HANDLE handle)
{
  ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *) handle;

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
IMTP2_Retrieve (ITS_SS7_HANDLE handl)
{
  ITS_SS7_CONTEXT *ctxt = (ITS_SS7_CONTEXT *) handl;
  ITS_INT i = 0;
  ITS_INT ret;

  while (ITS_SS7_CTXT_IDXMAP (ctxt) && i < ITS_SS7_CTXT_NUMLINKS (ctxt))
    {
      if (ITS_SS7_CTXT_IDXMAP (ctxt) & (1 << i))
	{
	  ret = ReadDataFromDev (ctxt, i, ITS_TRUE);
	}
      i++;
    }

  return ret;
}

static ITS_INT
SendDataToDev (ITS_INT tofd, char *data, ITS_INT len)
{
  ITS_INT ret;

  ret = write (tofd, data, len);

  MTP2_DEBUG ((" SendDataToDev: write() ret = %d on fd = %d \n", ret, tofd));
  if (ret < 0)
    {
      MTP2_ERROR (("SendDataToDev: Write to Device failed for fd(%d) errno=%d.\n", tofd, errno));
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
IMTP2_Send_CCITT (ITS_SS7_HANDLE handle, ITS_OCTET * data, ITS_USHORT dlen)
{
  ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *) handle;
  ITS_OCTET linkSet, linkCode;
  ITS_INT tofd = -1;		/* set fd to send data */
  ITS_BOOLEAN found = ITS_FALSE;
  ITS_BOOLEAN sigValid = ITS_TRUE;
  MTP2_Signal rxdata;
  ITS_EVENT evt;
  ITS_EVENT       event;
  ITS_INT ret = ITS_SUCCESS;
  ITS_INT i = 0;
  char buff[1024 + 40];;
  ITS_INT k = 0, l = 0;
  evt.data = data;
  evt.len = dlen;

  MTP2_DEBUG (("***** IMTP2_Send_CCITT ********** %d \n", dlen));
  if (dlen < 100)
    {
      for (k = 0; k < dlen; k++)
	{
	  l += sprintf (&buff[l], "0x%02x ", data[k]);
	  if (k && k % 16 == 0)
	    {
	      l += sprintf (&buff[l], "\n");
	    }
	}
    }
  else
    {
      MTP2_DEBUG (("***** IMTP2_Send_CCITT len is  >100********** %d \n",
		   dlen));
      for (k = 0; k < 100; k++)
	{
	  l += sprintf (&buff[l], "0x%02x ", data[k]);
	  if (k && k % 16 == 0)
	    {
	      l += sprintf (&buff[l], "\n");
	    }
	}

    }

  MTP2_DEBUG (("IMTP2_Send_CCITT: %s\n", buff));

  linkSet = L2_LINK_SET (&evt);
  linkCode = L2_LINK_CODE (&evt);

 /* for (i = 0; (context->linkSet == linkSet &&
	       i < MAX_LINK_CODES && !found); i++)
    {
      if (context->dlink[i].linkCode == linkCode)
	{
	  tofd = context->dlink[i].fd;
	  found = ITS_TRUE;
    break;
	}
    }*/
  if((context->linkSet == linkSet) && (!found))
  {
      if (context->dlink[linkCode].linkCode == linkCode)
      {
        tofd = context->dlink[linkCode].fd;
        found = ITS_TRUE;
      }
  }

  MTP2_DEBUG (("SendData:LS=%d LC=%d tofd = %d \n", linkSet, linkCode, tofd));
  if (found)
    {
#if 0
      MTP2_RXTX_SIGNAL (&rxdata) = L2_MSG_TYPE (&evt);

      if (L2_MSG_TYPE (&evt) == L3_L2_DATA)
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
	  rxdata.signal = L2_MSG_TYPE (&evt);
	  memcpy (rxdata.data.sif, L2_LINK_DATA (&evt) + 1,
		  dlen - (MTP2_FIXED_HDR_SIZE + 1));
#endif
	  memcpy (&rxdata, evt.data, dlen);

	  rxdata.linkSet = linkSet;
	  rxdata.linkCode = linkCode;
#if 0
	}
#endif
      switch (rxdata.signal)
	{
	case L3_L2_CONNECT:
	  MTP2_ERROR (("CONNECT:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_START:
	  MTP2_ERROR (("START:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_STOP:
	  MTP2_ERROR(("STOP:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_DISCONNECT:
	  MTP2_DEBUG (("DISCONNECT:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_RESUME:
	  MTP2_DEBUG (("RESUME:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_CLEAR_BUFFERS:
	  MTP2_DEBUG (("CLR_BUFFERS:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_CLEAR_RTB:
	  MTP2_DEBUG (("CLR_RTB:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_EMERGENCY:
	  MTP2_DEBUG (("EMERGENCY:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_EMERGENCY_CEASE:
	  MTP2_DEBUG (("EMERGENCY_CEASE:TX:LS=%d:LC=%d\n",
		       linkSet, linkCode));
	  break;

	case L3_L2_DATA:
	  memcpy (rxdata.data.sif, L2_LINK_DATA (&evt) + 1,
		  dlen - (MTP2_FIXED_HDR_SIZE + 1));
	  dlen = dlen - 1;	/*(MTP2_FIXED_HDR_SIZE + 1); */
	  MTP2_DEBUG (("DATA:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_RETRIEVE_BSNT:
 /* Sandeep jeevan to generate ECO for MTP3 ValidationStarts here
       ITS_EVENT_INIT(&event, ITS_MTP2_SRC, 3);
      event.data[0]=L2_L3_BSNT_NOT_RETRIEVABLE;
      event.data[1]=linkSet;
      event.data[2]=linkCode;
      ret= TRANSPORT_PutEvent(ITS_MTP3_ANSI_SRC, &event);
      return ret;
	    MTP2_DEBUG (("Temperoary chaged for fake ECO\n"));
 Sandeep jeevan to generate ECO for MTP3 Validation ENDS  here*/

	  MTP2_DEBUG (("RETIEVE_BSNT:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_RETRIEVE_MSGS:
	  {
	    ITS_UINT bsnt;

	    memcpy (&bsnt, L2_LINK_DATA (&evt), sizeof (ITS_UINT));

	    MTP2_SIGNAL_BSNT (&rxdata) = (ITS_OCTET) (bsnt & 0x000000FF);

	    MTP2_DEBUG (("RETRIEVE_MSGS:TX:LS=%d:LC=%d\n",
			 linkSet, linkCode));
	    break;
	  }
	case L3_L2_FLOW_CONTROL_START:
	  MTP2_DEBUG (("FLOW_CTRL_START:TX:LS=%d:LC=%d\n",
		       linkSet, linkCode));
	  break;

	case L3_L2_FLOW_CONTROL_STOP:
	  MTP2_DEBUG (("FLOW_CTRL_STOP:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_LOCAL_PROCESSOR_OUT:
	  MTP2_DEBUG (("LPO:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_LOCAL_PROCESSOR_REC:
	  MTP2_DEBUG (("LPR:TX:LS=%d:LC=%d\n", linkSet, linkCode));
	  break;

	case L3_L2_GET_TRACE:
	  MTP2_DEBUG (("L3_L2_GET_TRACE:LS=%d:LC=%d\n", linkSet, linkCode));
	  sigValid = ITS_FALSE;
	  break;
	case L3_L2_GET_CONFIG:
	  MTP2_DEBUG (("L3_L2_GET_CONFIG:LS=%d:LC=%d\n", linkSet, linkCode));
	  sigValid = ITS_FALSE;
	  break;
	case L3_L2_GET_PEGS:
	  MTP2_DEBUG (("L3_L2_GET_STATS:LS=%d:LC=%d\n", linkSet, linkCode));
	  sigValid = ITS_FALSE;
	  break;
	case L3_L2_SET_TRACE:
	  MTP2_DEBUG (("L3_L2_SET_TRACE:LS=%d:LC=%d\n", linkSet, linkCode));
	  sigValid = ITS_FALSE;
	  break;
	case L3_L2_SET_CONFIG:
	  MTP2_DEBUG (("L3_L2_SET_CONFIG:LS=%d:LC=%d\n", linkSet, linkCode));
	  sigValid = ITS_FALSE;
	  break;
	default:
	  /* MTP3 is requesting config data on recv func */
	  sigValid = ITS_FALSE;
	}

  if (sigValid)
	{
	  ret = SendDataToDev (tofd, (char *) &rxdata, dlen);

	  if (ret != dlen)
	    {
	      MTP2_WARNING (("IMTP2_Send_CCITT: Device could not send"
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
	  MTP2_ERROR (("IMTP2_Send_CCITT: Invalid signal.\n"));
	}
    }

  return ret;
}

ITS_INT
IMTP2_SetConfiguration (ITS_OCTET ls, ITS_OCTET lc, MTP2_Signal * data)
{
  ITS_SS7_CONTEXT *ctxt = NULL;
  ITS_INT ret = ITS_ENOMEM;
  MTP2_Signal getsig;
  ITS_OCTET sig;
  MTP2_SIGNAL_TYPE type = MTP2_TX_SIGNAL_TYPE (data->signal);
  ITS_INT len = 0;
  ITS_INT tofd = 0;

  ctxt = manager.context[ls];

  if (type == MTP2_SIGNAL_CONFIG)
    {
      len = MTP2_SIG_SET_CONFIG_SIZE;
      sig = L3_L2_GET_CONFIG;
    }
  else if (type == MTP2_SIGNAL_PEGS)
    {
      len = MTP2_SIG_RESET_STAT_SIZE;
      sig = L3_L2_GET_PEGS;
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
      ITS_INT i = 0;

    //  for (i = 0; i < ITS_SS7_CTXT_NUMLINKS (ctxt); i++)
      for (i = 0; i < MAX_LINK_CODES; i++)
	{
	  if (ITS_SS7_CTXT_DLINK (ctxt)[i].linkCode == lc)
	    {
	      tofd = ITS_SS7_CTXT_DLINK (ctxt)[i].fd;

	      ret = SendDataToDev (tofd, (char *) data, len);

	      if (ret != ITS_ESENDFAIL && ret == len)
		{
		  memset (&getsig, 0, sizeof (MTP2_Signal));

		  getsig.signal = sig;

		  /* Go ahead and get the modified data */
		  ret = SendDataToDev (tofd, (char *) &getsig,
				       MTP2_SIG_GET_CTS_SIZE);

		  if (ret != MTP2_SIG_GET_CTS_SIZE)
		    {
		      MTP2_DEBUG (("IMTP2_SetConfiguration: Could be partial write." " Error = %d len = %d\n", errno, ret));

		      ret = ITS_ESENDFAIL;
		    }
		  else
		    {
		      ret = ITS_SUCCESS;
		    }
		}
	      else
		{
		  MTP2_DEBUG (("IMTP2_SetConfiguration: Could be partial write." " Error = %d len = %d\n", errno, ret));
		}

	      break;
	    }
	}
    }

  return ret;
}

ITS_INT
IMTP2_GetConfiguration (ITS_OCTET ls, ITS_OCTET lc, MTP2_Signal * sig)
{
  ITS_SS7_CONTEXT *ctxt;
  ITS_INT ret;
  ITS_INT i = 0;
  ITS_INT type = sig->signal;

  if (ls >= MAX_MTP2_LINK_SETS || sig == NULL)
    {
      return ITS_ENOMEM;
    }

  ctxt = manager.context[ls];

  if (ctxt)
    {
     // for (i = 0; i < ITS_SS7_CTXT_NUMLINKS (ctxt); i++)
      for (i = 0; i < MAX_LINK_CODES; i++)
	{
	  if (ITS_SS7_CTXT_DLINK (ctxt)[i].linkCode == lc)
	    {
	      memcpy (sig, ITS_SS7_CTXT_DLINK (ctxt)[i].configData[type],
		      sizeof (MTP2_Signal));

	      return ret;
	    }
	}
    }

  return ret;
}


int
ln_config (ITS_EVENT evt)
{
  SS7_LinkPtr ln =NULL;
  ITS_SS7_CONTEXT *context=NULL;
  ITS_INT ret = 0, i = 0;
  ITS_INT idx = 0, cnt = 0,Ret=0;
  ITS_OCTET EXISTLINK = 0, k = 0, DELFLAG = 0;

  ln = TRANSPORT_SS7_INFO (__MTP2_CCITT_RcvQueue).linkInfo;

  switch (evt.data[0])
    {
    case ln_add_cmd:
      LINKSET = evt.data[1];
      LINKCODE = evt.data[2];


      MTP2_DEBUG (("SetConfiguration: ln_add command for linkset %d,linkcode %d", evt.data[1], evt.data[2]));
      for (; ln; ln = ln->next)
     	{
	     if (ln == NULL)
	    {
	      MTP2_DEBUG (("SetConfiguration: No Database"));
	      break;
	    }
	    if (!ln->linkSet)
	     {
	      MTP2_WARNING (("IMTP2_Initialize: No linkSet for this link"
			     " (%d)...!\n", ln->linkCode));
	      continue;
	    }
	  if (manager.context[ln->linkSet->linkSet])
	    {
	      context = manager.context[ln->linkSet->linkSet];
	    }
	  else
	    {
	      context =
		(ITS_SS7_CONTEXT *) calloc (1, sizeof (ITS_SS7_CONTEXT));
              if(context == NULL)
              {
	      MTP2_CRITICAL (("IMTP2_Initialize_CCITT: Could not allocate context.\n"));
                break;  
              }
	      manager.context[ln->linkSet->linkSet] = context;
	      ITS_SS7_CTXT_LINKSET (context) = ln->linkSet->linkSet;

	  for (k = 0; k < MAX_LINK_CODES; k++)
		{
		  ITS_SS7_CTXT_DLINK (context)[k].linkCode = -1;
		  ITS_SS7_CTXT_DLINK (context)[k].active = ITS_FALSE;
		}		/*linkCode zero may be valid */

	      SS7CONTEXT_ADD_HEAD (manager, context);
	    }

	  if (context == NULL)
	    {
	      MTP2_CRITICAL (("IMTP2_Initialize_CCITT: Could not allocate context.\n"));
	      return ITS_ENOMEM;
	    }

	  idx = ITS_SS7_CTXT_NUMLINKS (context);
	  MTP2_DEBUG (("SetConfiguration: No of Links=%d", idx));

          if (ITS_SS7_CTXT_DLINK (context)[ln->linkCode].linkCode == ln->linkCode)
             {
                  MTP2_CRITICAL (("IMTP2_Initialize_CCITT:Try for Next Entry find.\n"));
                  EXISTLINK = 1;
              }
           else
              {
                  EXISTLINK = 0;

              }
	  MTP2_DEBUG (("SetConfiguration: Link Set=%d", ITS_SS7_CTXT_LINKSET (context)));
	  if (ITS_SS7_CTXT_LINKSET (context) == LINKSET && EXISTLINK == 0)
	    {
		      MTP2_DEBUG (("SetConfiguration: idx=%d,context=%x", ln->linkCode,
				   context));
		      ITS_SS7_CTXT_DLINK (context)[ln->linkCode].linkCode = ln->linkCode;
		      ITS_SS7_CTXT_DLINK (context)[ln->linkCode].channelNum =ln->dataLink;
//		      ITS_SS7_CTXT_DLINK (context)[ln->linkCode].active = 1;

			  for (k = 0; k < MAX_MTP2_SIG_REQ; k++)
			  {
		  		MTP2_DEBUG (("Configuration:Traces "));
	  			ITS_SS7_CTXT_DLINK (context)[ln->linkCode].configData[k] = NULL;
			  }               /*for config trace zero may be valid */
		      ITS_SS7_CTXT_NUMLINKS (context)++;

		   if (ITS_SS7_CTXT_DLINK (context)[ln->linkCode].channelNum % 2 != 0)
			   {
			      MTP2_DEBUG (("SetConfiguration: Entry not Added"));
			      ENTRYDONE = 0;
			  }
		   else
		   	{
			     MTP2_DEBUG (("SetConfiguration: Entry Added"));
			     ENTRYDONE = 1;
			   }
		     break;
       }

	}			/*end of for loop */

  if (EXISTLINK == 0 && ENTRYDONE == 1)
	{
	  ret = MTP2BindAllDev ();
	  if (ret != ITS_SUCCESS)
	    {
	         ENTRYDONE = -1;
	      /* TODO: Close opened fd's and destroy all objects */
	      return -1;
	    }
	  else
	    {
           MTP2_DEBUG (("SetConfiguration: Post Sema Enrty"));
          Ret=SEMA_PostSemaphore(&scm_sema);
           if(Ret!=ITS_SUCCESS)
           {
             MTP2_ERROR (("SetConfiguration: Entry not Added"));
           }
          else
           { 
             MTP2_DEBUG (("SetConfiguration: Post Sema Success"));
           }
	      /* Send request to the dev for config/trace/stats */
	     // RequestMTP2ConfigData ();
	      return ITS_SUCCESS;
	    }
	}
      else
        {
          return !ITS_SUCCESS;
        }
      break;
    case ln_del_cmd:


      MTP2_DEBUG (("SetConfiguration: ln_del command for linkset %d,linkcode %d", evt.data[1], evt.data[2]));
      if (manager.context[evt.data[1]])
	    {
	         context = manager.context[evt.data[1]];
	    }

      if (context == NULL)
	    {
	          MTP2_CRITICAL (("IMTP2_Initialize_CCITT: Could not allocate context.\n"));
	          return ITS_ENOMEM;
	    }


      idx = ITS_SS7_CTXT_NUMLINKS (context);
      MTP2_DEBUG (("SetConfiguration:Total Links=%d ", idx));

      
     if (ITS_SS7_CTXT_DLINK (context)[evt.data[2]].linkCode == evt.data[2])
     {
	  ITS_SS7_CTXT_DLINK (context)[evt.data[2]].active = ITS_FALSE;
	  ITS_SS7_CTXT_DLINK (context)[evt.data[2]].linkCode = -1;
	  ITS_SS7_CTXT_NUMLINKS (context)--;
	  if (ITS_SS7_CTXT_DLINK (context)[evt.data[2]].fd >= 0)
	    {
	            ENTRYDELETE = 1;
              MTP2_DEBUG (("SetConfiguration: Post Sema Enrty"));
              Ret=SEMA_PostSemaphore(&scm_sema);
              if(Ret!=ITS_SUCCESS)
               {
                   MTP2_ERROR (("SetConfiguration: Entry not Added"));
               }
              else
               { 
                   MTP2_DEBUG (("SetConfiguration: Post Sema Success"));
               }
	      close (ITS_SS7_CTXT_DLINK (context)[evt.data[2]].fd);
	    }
	  ITS_SS7_CTXT_DLINK (context)[evt.data[2]].fd = -1;
	  return ITS_SUCCESS;
	 }
      else
	{
	  return !ITS_SUCCESS;
	}



      break;
    default:
      return (-1);
      break;

    }

}






#endif /* INCLUDE_MTP2 */
