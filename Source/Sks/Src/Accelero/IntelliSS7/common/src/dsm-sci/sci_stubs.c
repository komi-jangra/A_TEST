/*********************************-*-C-*-************************************
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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:23  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:24  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:40  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 1.4  2001/07/05 14:44:48  mmiers
 * LOG: Back to static libraries.
 * LOG:
 * LOG: Revision 1.3  2001/07/03 21:16:22  mmiers
 * LOG: Move RM and DSM.
 * LOG:
 * LOG: Revision 1.2  2001/06/28 20:32:42  mmiers
 * LOG: Add fast remote down detection.  A little concerned about the
 * LOG: overhead for this.
 * LOG:
 * LOG: Revision 1.1  2001/06/22 18:26:52  mmiers
 * LOG: Move to ENGINE.
 * LOG:
 * LOG: Revision 1.1  2001/06/20 19:55:41  mmiers
 * LOG: Split DSM out into a separate library.
 * LOG:
 * LOG: Revision 1.2  2001/05/16 00:14:14  mmiers
 * LOG: Get PR5 built.
 * LOG:
 * LOG: Revision 1.1  2001/05/10 00:45:28  mmiers
 * LOG: Add stubs for when DSM isn't present.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#define _REENTRANT
#endif

#include <its.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <its_timers.h>

#include "dsm_impl.h"
#include <its_dsm.h>

#ident "$Id: sci_stubs.c,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"

#if !defined(USE_DSM)

const unsigned int SCI_FLAG_FIXED_MAP_ADDR = 0;
const unsigned int SCI_Q_ADAPTER_NODEID = 0;
const unsigned int SCI_Q_ADAPTER = 0;
const unsigned int SCI_FLAG_DMA_WAIT = 0;
const unsigned int SCI_FLAG_DMA_POST = 0;
const unsigned int SCI_FLAG_USE_CALLBACK = 0;

void
SCIInitialize(unsigned int flags,
              sci_error_t *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCITerminate(void)
{
}

void
SCIOpen(sci_desc_t   *sd,
        unsigned int flags,
        sci_error_t  *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIClose(sci_desc_t sd,
         unsigned int flags,
         sci_error_t *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIConnectSegment(sci_desc_t              sd,
                  sci_remote_segment_t    *segment,
                  unsigned int            nodeId,
                  unsigned int            segmentId,
                  unsigned int            localAdapterNo,
                  sci_cb_remote_segment_t callback, 
                  void                    *callbackArg,
                  unsigned int            timeout,
                  unsigned int            flags,
                  sci_error_t             *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIDisconnectSegment(sci_remote_segment_t segment,
                     unsigned int         flags,
                     sci_error_t          *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

unsigned int
SCIGetRemoteSegmentSize(sci_remote_segment_t segment)
{
    return (0);
}

sci_segment_cb_reason_t
SCIWaitForRemoteSegmentEvent(sci_remote_segment_t segment,
                             sci_error_t          *status,
                             unsigned int         timeout,
                             unsigned int         flags,
                             sci_error_t          *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (SCI_CB_LOST);
}

volatile void *
SCIMapRemoteSegment(sci_remote_segment_t segment,
                    sci_map_t            *map,
                    unsigned int         offset,
                    unsigned int         size,
                    void                *addr,
                    unsigned int         flags,
                    sci_error_t          *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (NULL);
}

void *
SCIMapLocalSegment(sci_local_segment_t segment,
                   sci_map_t           *map,
                   unsigned int        offset,
                   unsigned int        size,
                   void                *addr,
                   unsigned int        flags,
                   sci_error_t         *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (NULL);
}

void
SCIUnmapSegment(sci_map_t    map,
                unsigned int flags,
                sci_error_t  *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCICreateSegment(sci_desc_t             sd,
                 sci_local_segment_t    *segment,
                 unsigned int           segmentId,
                 unsigned int           size,
                 sci_cb_local_segment_t callback,
                 void                   *callbackArg, 
                 unsigned int           flags,
                 sci_error_t            *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

sci_segment_cb_reason_t
SCIWaitForLocalSegmentEvent(sci_local_segment_t segment,     
                            unsigned int *sourcenodeId,
                            unsigned int *localAdapterNo,
                            unsigned int timeout,
                            unsigned int flags,
                            sci_error_t  *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (SCI_CB_LOST);
}

void
SCIPrepareSegment(sci_local_segment_t segment,
                  unsigned int        localAdapterNo,
                  unsigned int        flags,
                  sci_error_t         *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIRemoveSegment(sci_local_segment_t segment,
                 unsigned int        flags, 
                 sci_error_t         *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCISetSegmentAvailable(sci_local_segment_t segment,
                       unsigned int        localAdapterNo,
                       unsigned int        flags,
                       sci_error_t         *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCISetSegmentUnavailable(sci_local_segment_t segment,
                         unsigned int        localAdapterNo,
                         unsigned int        flags,
                         sci_error_t         *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCICreateMapSequence(sci_map_t   map, 
                     sci_sequence_t *sequence, 
                     unsigned int   flags, 
                     sci_error_t    *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIRemoveSequence(sci_sequence_t sequence, 
                  unsigned int   flags, 
                  sci_error_t    *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

sci_sequence_status_t
SCIStartSequence(sci_sequence_t sequence,
                 unsigned int   flags,
                 sci_error_t    *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (SCI_SEQ_NOT_RETRIABLE);
}

sci_sequence_status_t
SCICheckSequence(sci_sequence_t sequence,
                 unsigned int   flags,
                 sci_error_t    *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (SCI_SEQ_NOT_RETRIABLE);
}

void
SCIStoreBarrier(sci_sequence_t sequence,
                unsigned int   flags)
{
}

void
SCIFlushReadBuffers(sci_sequence_t sequence)
{
}

int
SCIProbeNode(sci_desc_t   sd,
             unsigned int localAdapterNo,
             unsigned int nodeId,
             unsigned int flags,
             sci_error_t  *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (0);
}

unsigned int
SCIGetCSRRegister(sci_desc_t   sd,
                  unsigned int localAdapterNo,
                  unsigned int SCINodeId,
                  unsigned int CSROffset,
                  unsigned int flags,
                  sci_error_t  *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (0);
}

void
SCISetCSRRegister(sci_desc_t   sd,
                  unsigned int localAdapterNo,
                  unsigned int SCINodeId,
                  unsigned int CSROffset,
                  unsigned int CSRValue,
                  unsigned int flags,
                  sci_error_t  *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

unsigned int
SCIGetLocalCSR(sci_desc_t   sd,
               unsigned int localAdapterNo,
               unsigned int CSROffset,
               unsigned int flags,
               sci_error_t  *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (0);
}

void
SCISetLocalCSR(sci_desc_t        sd,
               unsigned int      localAdapterNo,
               unsigned int      CSROffset,
               unsigned int      CSRValue,
               unsigned int      flags,
               sci_error_t       *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIQuery(unsigned int command,
         void         *data,
         unsigned int flags,
         sci_error_t  *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCICreateDMAQueue(sci_desc_t      sd,
                  sci_dma_queue_t *dq,
                  unsigned int    localAdapterNo,
                  unsigned int    maxEntries,
                  unsigned int    flags,
                  sci_error_t     *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIRemoveDMAQueue(sci_dma_queue_t dq,
                  unsigned int    flags,
                  sci_error_t     *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

sci_dma_queue_state_t
SCIEnqueueDMATransfer(sci_dma_queue_t      dq,
                      sci_local_segment_t  localSegment,
                      sci_remote_segment_t remoteSegment,
                      unsigned int         localOffset,
                      unsigned int         remoteOffset,
                      unsigned int         size,
                      unsigned int         flags,
                      sci_error_t          *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (SCI_DMAQUEUE_ERROR);
}

void
SCIPostDMAQueue(sci_dma_queue_t dq, 
                sci_cb_dma_t    callback, 
                void            *callbackArg,
                unsigned int    flags,
                sci_error_t     *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIAbortDMAQueue(sci_dma_queue_t dq,
                 unsigned int    flags,
                 sci_error_t     *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIResetDMAQueue(sci_dma_queue_t dq,
                 unsigned int    flags,
                 sci_error_t     *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

sci_dma_queue_state_t
SCIDMAQueueState(sci_dma_queue_t dq)
{
    return (SCI_DMAQUEUE_ERROR);
}

sci_dma_queue_state_t
SCIWaitForDMAQueue(sci_dma_queue_t dq,
                   unsigned int    timeout,
                   unsigned int    flags,
                   sci_error_t     *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;

    return (SCI_DMAQUEUE_ERROR);
}

void
SCICreateInterrupt(sci_desc_t            sd,
                   sci_local_interrupt_t *interrupt,
                   unsigned int          localAdapterNo,
                   unsigned int          *interruptNo,
                   sci_cb_interrupt_t    callback,
                   void                  *callbackArg,
                   unsigned int          flags,
                   sci_error_t           *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIRemoveInterrupt(sci_local_interrupt_t interrupt,
                   unsigned int          flags,
                   sci_error_t           *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIWaitForInterrupt(sci_local_interrupt_t interrupt, 
                    unsigned int          timeout,
                    unsigned int          flags, 
                    sci_error_t           *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIConnectInterrupt(sci_desc_t             sd,
                    sci_remote_interrupt_t *interrupt,
                    unsigned int           nodeId,
                    unsigned int           localAdapterNo,
                    unsigned int           interruptNo,
                    unsigned int           timeout,
                    unsigned int           flags,
                    sci_error_t            *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIDisconnectInterrupt(sci_remote_interrupt_t interrupt,
                       unsigned int           flags,
                       sci_error_t            *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCITriggerInterrupt(sci_remote_interrupt_t interrupt,
                    unsigned int           flags,
                    sci_error_t            *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIRegisterInterruptFlag(unsigned int           localAdapterNo,
                         sci_local_interrupt_t *interrupt,
                         sci_local_segment_t    segment,
                         unsigned int           offset,
                         sci_cb_interrupt_t     callback,
                         void                  *callbackArg,
                         unsigned int           flags,
                         sci_error_t           *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIEnableConditionalInterrupt(sci_local_interrupt_t interrupt,
                              unsigned int          flags,
                              sci_error_t           *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIDisableConditionalInterrupt(sci_local_interrupt_t interrupt,
                               unsigned int          flags,
                               sci_error_t           *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIGetConditionalInterruptTrigCounter(sci_local_interrupt_t interrupt,
                                      unsigned int          *interruptTrigCounter,
                                      unsigned int          flags,
                                      sci_error_t           *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCITransferBlock(sci_map_t    sourceMap,
                 unsigned int sourceOffset,
                 sci_map_t    destinationMap,
                 unsigned int destinationOffset,
                 unsigned int size,
                 unsigned int flags,
                 sci_error_t  *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCITransferBlockAsync(sci_map_t               sourceMap,
                      unsigned int            sourceOffset,
                      sci_map_t               destinationMap,
                      unsigned int            destinationOffset,
                      unsigned int            size,
                      sci_block_transfer_t    *block,
                      sci_cb_block_transfer_t callback,
                      void                    *callbackArg,
                      unsigned int            flags,
                      sci_error_t             *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIWaitForBlockTransfer(sci_block_transfer_t block,
                        unsigned int         timeout,
                        unsigned int         flags,
                        sci_error_t          *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIAbortBlockTransfer(sci_block_transfer_t block,
                      unsigned int         flags,
                      sci_error_t          *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

static void
SCIDummyCopy(void *memAddr, sci_map_t rm,
      unsigned int off, unsigned int size, unsigned int flags,
      sci_error_t *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void (*sciMemCopyFuncPtr)(void         *memAddr,
                          sci_map_t     remoteMap,
                          unsigned int  remoteOffset,
                          unsigned int  size,
                          unsigned int  flags,
                          sci_error_t  *error) = SCIDummyCopy;

#define SCIMemCopy(memAddr, remoteMap, remoteOffset, size, flags, error) \
    { (*sciMemCopyFuncPtr)(memAddr,remoteMap,remoteOffset,size,flags,error); }

void
SCIRegisterSegmentMemory(void                *address,
                         unsigned int        size,
                         sci_local_segment_t segment,
                         unsigned int        flags,
                         sci_error_t         *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

void
SCIConnectSCISpace(sci_desc_t           sd,
                   unsigned int         localAdapterNo,
                   sci_remote_segment_t *segment,
                   sci_address_t        address,
                   unsigned int         size,
                   unsigned int         flags,
                   sci_error_t          *error)
{
    *error = SCI_ERR_FLAG_NOT_IMPLEMENTED;
}

#endif
