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
 *  ID: $Id: its_mtp2_intern.h,v 1.3 2008-06-05 04:49:55 bsccs2 Exp $
 *  
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.2  2008/02/13 02:02:09  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:12:12  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:21:59  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.2  2007/05/11 06:12:52  ashutosh.singh
 * LOG: change for logger lib integeration
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.3  2006/07/22 07:46:11  sjaddu
 * LOG: modified device file as mcc instead of mtp2
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/14 17:17:52  gdevanand
 * LOG: Commiting after mtp2 testing.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:18:40  lbana
 * LOG: Vframe structure and mtp2 specifics.
 * LOG:
 * LOG:
 *  
 ****************************************************************************/

#ifndef ITS_MTP2_INTERN_H
#define ITS_MTP2_INTERN_H
 
#ident "$Id: its_mtp2_intern.h,v 1.3 2008-06-05 04:49:55 bsccs2 Exp $"

#include <its.h>
#include <its_trace.h>
#include <itu/mtp2.h>

#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#endif

#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif

/* #define MAX_MTP2_RXTX_DATA 260 */
//#define MAX_MTP2_RXTX_DATA 272
#define MAX_MTP2_RXTX_DATA (273 + 3)/*SIF+SIO+LS+LN+PRTTYPE*//*mantis 4118*/
#define MAX_LINK_CODES     16     /* 16 links in a linkset */
#define MAX_MTP2_LINK_SETS 80 

#define MAX_DEV_NAME_LEN   80
#define MTP2_DEV_NAME      "/dev/mtp2/%d"

#define MTP2_SIG_GET_CTS_SIZE     3  /* write size of get config/trace/stats */
#define MTP2_SIG_SET_CONFIG_SIZE  (1+sizeof(MTP2_ConfigData)) /* write size for set */
#define MTP2_SIG_SET_TRACE_SIZE   (1+MTP2_MAX_TRACE_LEVELS)
#define MTP2_SIG_RESET_STAT_SIZE  (1+sizeof(MTP2_StatsData))
//#define MTP2_L2_L3_IND_SIZE       3 /* MTP2_SIG_GET_CTS_SIZE */
#define MTP2_L2_L3_IND_SIZE       4 /* MTP2_SIG_GET_CTS_SIZE */
#define MTP2_L2_L3_MIN_DATA_LEN   MTP2_L2_L3_IND_SIZE 

#if defined(__cplusplus)
extern "C"
{
#endif

typedef enum
{
    MTP2_SIGNAL_UNKNOWN,
    MTP2_SIGNAL_DATA,
    MTP2_SIGNAL_CONFIG,
    MTP2_SIGNAL_PEGS,
    MTP2_SIGNAL_TRACE
}
MTP2_SIGNAL_TYPE;

#define MTP2_RX_SIGNAL_TYPE(d) ((((ITS_OCTET)d >= L2_L3_IN_SERVICE) &&  \
             ((ITS_OCTET)d <= L2_L3_CONGESTION_ABATES)) ? MTP2_SIGNAL_DATA : \
             ((ITS_OCTET)d == L2_L3_CURRENT_TRACE) ? MTP2_SIGNAL_TRACE :     \
             ((ITS_OCTET)d == L2_L3_CURRENT_CONFIG) ? MTP2_SIGNAL_CONFIG :   \
             ((ITS_OCTET)d == L2_L3_CURRENT_PEGS) ? MTP2_SIGNAL_PEGS :     \
               MTP2_SIGNAL_UNKNOWN)

#define MTP2_TX_SIGNAL_TYPE(d) (((ITS_OCTET)d >= L3_L2_START) &&   \
          ((ITS_OCTET)d <= L3_L2_LOCAL_PROCESSOR_OUT) ? MTP2_SIGNAL_DATA : \
          ((ITS_OCTET)d >= L3_L2_GET_TRACE &&                              \
          (ITS_OCTET)d <= L3_L2_SET_TRACE) ? MTP2_SIGNAL_TRACE :           \
          ((ITS_OCTET)d >= L3_L2_GET_CONFIG &&                             \
          (ITS_OCTET)d <= L3_L2_SET_CONFIG) ? MTP2_SIGNAL_CONFIG :        \
          ((ITS_OCTET)d >= L3_L2_GET_PEGS &&                              \
          (ITS_OCTET)d <= L3_L2_RESET_PEGS) ? MTP2_SIGNAL_PEGS :         \
          MTP2_SIGNAL_UNKNOWN)

#define MAX_MTP2_SIG_REQ (MTP2_SIGNAL_TRACE +1)   /* Config, trace, and stats requests from user */

typedef struct
{
    ITS_INT     fd;
    ITS_INT     linkCode;
    ITS_INT     channelNum;
    char        *configData[MAX_MTP2_SIG_REQ];
    ITS_BOOLEAN active; /* Inactive doesn't mean the physical channel is inactive
                         * its merely to know link state
                         */
}
DLink;

typedef struct _its_ss7_context
{
    ITS_USHORT              trid;
    ITS_OCTET               numLinks;
    ITS_OCTET               linkSet;
    ITS_UINT                idxMap; /* Set bit position for the index */
    DLink                   dlink[MAX_LINK_CODES];
    ITS_UINT                mtp2State;
    struct _its_ss7_context *next;
    struct _its_ss7_context *prev;
}
ITS_SS7_CONTEXT;

#define ITS_SS7_CTXT_DLINK(x)       (((ITS_SS7_CONTEXT *)x)->dlink)
#define ITS_SS7_CTXT_LINKSET(x)     (((ITS_SS7_CONTEXT *)x)->linkSet)
#define ITS_SS7_CTXT_NUMLINKS(x)    (((ITS_SS7_CONTEXT *)x)->numLinks)
#define ITS_SS7_CTXT_MTP2STATE(x)   (((ITS_SS7_CONTEXT *)x)->mtp2State)
#define ITS_SS7_CTXT_IDXMAP(x)      (((ITS_SS7_CONTEXT *)x)->idxMap)
#define ITS_SS7_CTXT_L2REQ_STATE(x) (((ITS_SS7_CONTEXT *)x)->l2ReqState)

typedef struct
{
    ITS_SS7_CONTEXT *context[MAX_MTP2_LINK_SETS]; /* LinkSet contexts */
    ITS_INT          configFD;
    ITS_INT          maxOpen;                     /* Max opened files */
    ITS_INT          numLinkSets;                 /* Total num of Link Sets */
    ITS_INT          waitTime;                    /* Wait perior for select in secs */
    /* TODO: Add read write lock */
    ITS_SS7_CONTEXT  *head;                       /* The list is for reader where as sender */
    ITS_SS7_CONTEXT  *tail;                       /* can directly lookup the context */ 
}
SS7CONTEXT_Manager;

#define SS7CONTEXT_HEAD(m)  m.head
#define SS7CONTEXT_TAIL(m)  m.tail

#define SS7CONTEXT_ADD_HEAD(m, e) do {                                   \
                                      if (m.head == NULL) {              \
                                          m.head = e;                    \
                                          m.tail = e;                    \
                                      }                                  \
                                      else {                             \
                                          e->next = m.head;              \
                                          m.head->prev = e;              \
                                          m.head = e;                    \
                                      }                                  \
                                  } while (0)

#define SS7CONTEXT_ADD_TAIL(m, e) do {                                   \
                                      if (m.tail == NULL) {              \
                                          SS7CONTEXT_ADD_HEAD(m , e);    \
                                      }                                  \
                                      else {                             \
                                          m.tail->next = e;              \
                                          e->prev = m.tail;              \
                                          m.tail  = e;                   \
                                      }                                  \
                                   } while (0)

#define SS7CONTEXT_DEL_ELEMENT(m, e) do {                               \
                                         if (e->prev) {                 \
                                             e->prev->next = e->next;   \
                                         }                              \
                                         if (e->next) {                 \
                                             e->next->prev = e->prev;   \
                                         }                              \
                                         if (m.head == e)               \
                                             m.head = e->next;          \
                                         }                              \
                                         if (m.tail == e)               \
                                             m.tail = e->prev;          \
                                         }                              \
                                      } while (0)

int
IMTP2_Send_CCITT(ITS_SS7_HANDLE handle, ITS_OCTET *data, ITS_USHORT dlen);

int
IMTP2_Initialize_CCITT(ITS_SS7_HANDLE handle);
int
IMTP2_Terminate_CCITT(ITS_SS7_HANDLE handle);

/*.interface:
 *
 * When a message of a certain severity is to be traced, the appropriate
 * macro as defined below shall be called. The arguments to the macros are
 * a "printf" style format string, and a variable list of args.
 *
 * Note that all the format string and the args should be surrounded by
 * parentheses. For example:
 *
 * MTP2_DEBUG(("Sample trace message: var1 = %d, var2 = %s.\n", var1, var2));
 *
 * trace possibilities:
 */
#define MTP2_TRACE_CRITICAL  0
#define MTP2_TRACE_ERROR     1
#define MTP2_TRACE_WARNING   2
#define MTP2_TRACE_DEBUG     3
#define MTP2_TRACE_EVENT     4

/*#if defined(ICCITT) */

#ifdef LOGGER_IMR
#define MTP2_CRITICAL(args) \
      LOG_PRINT_CRITICAL args;
#else
#define MTP2_CRITICAL(args) \
    TRACE(MTP2_CCITT_TraceData, MTP2_TRACE_CRITICAL, args)
#endif


#ifdef LOGGER_IMR
#define MTP2_ERROR(args) \
      LOG_PRINT_CRITICAL args;
#else
#define MTP2_ERROR(args) \
    TRACE(MTP2_CCITT_TraceData, MTP2_TRACE_ERROR, args)
#endif

#ifdef LOGGER_IMR
#define MTP2_WARNING(args) \
      LOG_PRINT_MAJOR args;
#else

#define MTP2_WARNING(args) \
    TRACE(MTP2_CCITT_TraceData, MTP2_TRACE_WARNING, args)
#endif


#ifdef LOGGER_IMR
#define MTP2_DEBUG(args) \
      LOG_PRINT_DEBUG args;
#else
#define MTP2_DEBUG(args) \
    TRACE(MTP2_CCITT_TraceData, MTP2_TRACE_DEBUG, args)
#endif
    

#define MTP2_EVENT(args) \
    TRACE(MTP2_CCITT_TraceData, MTP2_TRACE_EVENT, args)
/*
#else
#define MTP2_CRITICAL(args) printf args
#define MTP2_ERROR(args)    printf args
#define MTP2_WARNING(args)  printf args
#define MTP2_DEBUG(args)    printf args 
#endif 
*/
#if defined (__cplusplus)
}
#endif

/*
 * tracing strings
 */
#define MTP2_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define MTP2_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define MTP2_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define MTP2_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING
#define MTP2_TRACE_EVENT_STRING     ITS_TRACE_EVENT_STRING

#define MTP2_CRITICAL_STRING        ITS_CRITICAL_STRING
#define MTP2_ERROR_STRING           ITS_ERROR_STRING
#define MTP2_WARNING_STRING         ITS_WARNING_STRING
#define MTP2_DEBUG_STRING           ITS_DEBUG_STRING
#define MTP2_EVENT_STRING           ITS_EVENT_STRING

#define MTP2_STDOUT_STRING          ITS_STDOUT_STRING
#define MTP2_SYSLOG_STRING          ITS_SYSLOG_STRING
#define MTP2_FILE_STRING            ITS_FILE_STRING

#if defined(CCITT) 

#define MTP2_TRACE_CRITICAL_FILE    ".itu-mtp2-traceCritical"
#define MTP2_TRACE_ERROR_FILE       ".itu-mtp2-traceError"
#define MTP2_TRACE_WARNING_FILE     ".itu-mtp2-traceWarning"
#define MTP2_TRACE_DEBUG_FILE       ".itu-mtp2-traceDebug"
#define MTP2_TRACE_EVENT_FILE       ".itu-mtp2-traceEvent"
#else
#define MTP2_TRACE_CRITICAL_FILE    ".ansi-mtp2-traceCritical"
#define MTP2_TRACE_ERROR_FILE       ".ansi-mtp2-traceError"
#define MTP2_TRACE_WARNING_FILE     ".ansi-mtp2-traceWarning"
#define MTP2_TRACE_DEBUG_FILE       ".ansi-mtp2-traceDebug"
#define MTP2_TRACE_EVENT_FILE       ".ansi-mtp2-traceEvent"

#endif

#endif

