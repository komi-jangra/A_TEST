/*****************************************************************************
 *                                                                           *
 *     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *             Manufactured in the United States of America.                 *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                           *
 *   This product and related documentation is protected by copyright and    *
 *   distributed under licenses restricting its use, copying, distribution   *
 *   and decompilation.  No part of this product or related documentation    *
 *   may be reproduced in any form by any means without prior written        *
 *   authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                           *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *   government is subject to restrictions as set forth in subparagraph      *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                           *
 *****************************************************************************
 *                                                                           *
 * CONTRACT: INTERNAL                                                        *
 *                                                                           *
 *****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:24  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:14  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:43  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/04/17 14:29:33  hdivoux
 * LOG: Added system include files for Unix.
 * LOG:
 * LOG: Revision 6.4  2002/04/15 15:09:25  hdivoux
 * LOG: Added preconditions for timeout member values (poll function).
 * LOG:
 * LOG: Revision 6.3  2002/04/15 14:52:55  hdivoux
 * LOG: Use true timeval structure.
 * LOG:
 * LOG: Revision 6.2  2002/03/26 21:22:51  hdivoux
 * LOG: Add mailbox poll function.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 1.2  2001/06/29 16:46:50  hdivoux
 * LOG: Add GCS event related functions.
 * LOG:
 * LOG: Revision 1.1  2001/06/26 21:41:20  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/

#include <gcs_client.h>

#include <its_assertion.h>
#include <its_trace.h>

#include <sp.h>

#if !defined(ARCH_PC_WIN95)
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#endif /* !defined(ARCH_PC_WIN95) */

#undef mailbox
#undef service


#ident "$Id: gcs_client.c,v 1.1.1.1 2007-10-08 11:11:53 bsccs2 Exp $"



/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Retrieve GCS client library version.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      majorVersion - major version.
 *      minorVersion - minor version.
 *      patchVersion - patch version.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_Version(
        ITS_INT* majorVersion, 
        ITS_INT* minorVersion, 
        ITS_INT* patchVersion)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_Version:\n"));

    ITS_C_REQUIRE(majorVersion != NULL);
    ITS_C_REQUIRE(minorVersion != NULL);
    ITS_C_REQUIRE(patchVersion != NULL);

    ret = SP_version(
                (int*)majorVersion, 
                (int*)minorVersion, 
                (int*)patchVersion);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Initial call an application must make to establish a connection with
 *      a GCS deamon. All other GCS calls must refer to a valid mailbox 
 *      returned by this function.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_Connect( 
        const char* gcsName,
        const char* privateName,
        ITS_INT priority,
        ITS_INT groupMembership,
        GCS_MAILBOX* mailboxParam,
        char* privateGroup)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_Connect:\n"));

    ITS_C_REQUIRE(gcsName != NULL);
    ITS_C_REQUIRE(privateName != NULL);
    ITS_C_REQUIRE(mailboxParam != NULL);
    ITS_C_REQUIRE(privateGroup != NULL);

    ret = SP_connect(
                gcsName,
                privateName,
                priority,
                groupMembership,
                mailboxParam,
                privateGroup);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Initial call an application must make to establish a connection with
 *      a GCS deamon. All other GCS calls must refer to a valid mailbox 
 *      returned by this function.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCSStub_ConnectTimeout(
        const char* gcsName, 
        const char* privateName,
        ITS_INT priority, 
        ITS_INT groupMembership, 
        GCS_MAILBOX* mailboxParam,
        char* privateGroup,
        GCS_TIME timeout)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCSStub_ConnectTimeout:\n"));

    ITS_C_REQUIRE(gcsName != NULL);
    ITS_C_REQUIRE(privateName != NULL);
    ITS_C_REQUIRE(mailboxParam != NULL);
    ITS_C_REQUIRE(privateGroup != NULL);

    ITS_C_ASSERT(sizeof(GCS_TIME) == sizeof(sp_time));

    ret = SP_connect(
                gcsName,
                privateName,
                priority,
                groupMembership,
                mailboxParam,
                privateGroup);

/* Commented temporaryly for Testing of JOIN msg
    ret = SPStub_connect_timeout(
                gcsName,
                privateName,
                priority,
                groupMembership,
                mailboxParam,
                privateGroup,
                *((sp_time*)&timeout));*/

    return ret;
}
GCSDLLAPI int 
GCS_ConnectTimeout(
        const char* gcsName, 
        const char* privateName,
        ITS_INT priority, 
        ITS_INT groupMembership, 
        GCS_MAILBOX* mailboxParam,
        char* privateGroup,
        GCS_TIME timeout)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_ConnectTimeout:\n"));

    ITS_C_REQUIRE(gcsName != NULL);
    ITS_C_REQUIRE(privateName != NULL);
    ITS_C_REQUIRE(mailboxParam != NULL);
    ITS_C_REQUIRE(privateGroup != NULL);

    ITS_C_ASSERT(sizeof(GCS_TIME) == sizeof(sp_time));

    ret = SP_connect_timeout(
                gcsName,
                privateName,
                priority,
                groupMembership,
                mailboxParam,
                privateGroup,
                *((sp_time*)&timeout));

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Should be called when the application is finished with a connection to
 *      the GCS daemon.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_Disconnect(GCS_MAILBOX mailboxParam)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_Disconnect:\n"));

    ret = SP_disconnect(mailboxParam);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      To join a group.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_Join(GCS_MAILBOX mailboxParam, const char* group)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_Join:\n"));

    ITS_C_REQUIRE(group != NULL);

    ret = SP_join(mailboxParam, group);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      To leave a group.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.s
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_Leave(GCS_MAILBOX mailboxParam, const char* group)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_Leave:\n"));

    ITS_C_REQUIRE(group != NULL);

    ret = SP_leave(mailboxParam, group);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Multicast a message to a group.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_Multicast(
        GCS_MAILBOX mailboxParam, 
        GCS_SERVICE serviceParam, 
        const char* group,
        ITS_SHORT msgType, 
        ITS_INT msgLen, 
        const char* msg)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_Multicast:\n"));

    ITS_C_REQUIRE(group != NULL);
    ITS_C_REQUIRE(msgLen >= 0);
    ITS_C_REQUIRE(msg != NULL);

    ret = SP_multicast(
                mailboxParam,
                serviceParam,
                group,
                msgType,
                msgLen,
                msg);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Multicast a message to a group.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_ScatMulticast( 
        GCS_MAILBOX mailboxParam, 
        GCS_SERVICE serviceParam,
        const char* group,
        ITS_SHORT msgType, 
        const GCS_SCATTER* scatterParam)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_ScatMulticast:\n"));

    ITS_C_REQUIRE(group != NULL);
    ITS_C_REQUIRE(scatterParam != NULL);

    ITS_C_ASSERT(sizeof(GCS_SCATTER) == sizeof(scatter));

    ret = SP_scat_multicast(
                mailboxParam,
                serviceParam,
                group,
                msgType,
                (const scatter*)&scatterParam);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Multicast a message to a collection of groups.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_MultigroupMulticast(
        GCS_MAILBOX mailboxParam, 
        GCS_SERVICE serviceParam,
        ITS_INT numGroups,
        const char groups[][GCS_MAX_GROUP_NAME],
        ITS_SHORT msgType, 
        ITS_INT msgLen,
        const char* msg)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_MultigroupMulticast:\n"));

    ITS_C_REQUIRE(numGroups > 0);
    ITS_C_REQUIRE(groups != NULL);
    ITS_C_REQUIRE(msgLen > 0);
    ITS_C_REQUIRE(msg != NULL);

    ret = SP_multigroup_multicast(
                mailboxParam,
                serviceParam,
                numGroups,
                groups,
                msgType,
                msgLen,
                msg);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Multicast a message to a collection of groups.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_MultigroupScatMulticast( 
        GCS_MAILBOX mailboxParam, 
        GCS_SERVICE serviceParam,
        ITS_INT numGroups,
        const char groups[][GCS_MAX_GROUP_NAME],
        ITS_SHORT msgType,
        const GCS_SCATTER* scatterParam)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_MultigroupScatMulticast:\n"));

    ITS_C_REQUIRE(numGroups > 0);
    ITS_C_REQUIRE(groups != NULL);
    ITS_C_REQUIRE(scatterParam != NULL);

    ITS_C_ASSERT(sizeof(GCS_SCATTER) == sizeof(scatter));

    ret = SP_multigroup_scat_multicast(
                mailboxParam,
                serviceParam,
                numGroups,
                groups,
                msgType,
                (const scatter*)scatterParam);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Receive data and membership messages.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_Receive( 
        GCS_MAILBOX mailboxParam, 
        GCS_SERVICE* serviceParam,
        char sender[GCS_MAX_GROUP_NAME], 
        ITS_INT maxGroups,
        ITS_INT* numGroups, 
        char groups[][GCS_MAX_GROUP_NAME],
        ITS_SHORT* msgType, 
        ITS_INT* endianMismatch,
        ITS_INT maxMsgLen, 
        char* msg)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_Receive:\n"));

    ITS_C_REQUIRE(serviceParam != NULL);
    ITS_C_REQUIRE(sender != NULL);
    ITS_C_REQUIRE(maxGroups > 0);
    ITS_C_REQUIRE(numGroups != NULL);
    ITS_C_REQUIRE(groups != NULL);
    ITS_C_REQUIRE(msgType != NULL);
    ITS_C_REQUIRE(endianMismatch != NULL);
    ITS_C_REQUIRE(maxMsgLen > 0);
    ITS_C_REQUIRE(msg != NULL);

    ret = SP_receive(
                mailboxParam,
                serviceParam,
                sender,
                maxGroups,
                numGroups,
                groups,
                msgType,
                endianMismatch,
                maxMsgLen,
                msg);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Receive data and membership messages.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_ScatReceive( 
        GCS_MAILBOX mailboxParam, 
        GCS_SERVICE* serviceParam,
        char sender[GCS_MAX_GROUP_NAME], 
        ITS_INT maxGroups,
        ITS_INT* numGroups, 
        char groups[][GCS_MAX_GROUP_NAME],
        ITS_SHORT* msgType, 
        ITS_INT* endianMismatch,
        GCS_SCATTER* scatterParam)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_ScatReceive:\n"));

    ITS_C_REQUIRE(serviceParam != NULL);
    ITS_C_REQUIRE(sender != NULL);
    ITS_C_REQUIRE(maxGroups > 0);
    ITS_C_REQUIRE(numGroups != NULL);
    ITS_C_REQUIRE(groups != NULL);
    ITS_C_REQUIRE(msgType != NULL);
    ITS_C_REQUIRE(endianMismatch != NULL);
    ITS_C_REQUIRE(scatterParam != NULL);

    ITS_C_REQUIRE(sizeof(GCS_SCATTER) == sizeof(scatter));

    ret = SP_scat_receive(
                mailboxParam,
                serviceParam,
                sender,
                maxGroups,
                numGroups,
                groups,
                msgType,
                endianMismatch,
                (scatter*)scatterParam);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Poll to see if message(s) available in mailbox.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_Poll(GCS_MAILBOX mailboxParam)
{
    int ret = GCS_SUCCESS;

    ITS_TRACE_DEBUG(("GCS_Poll:\n"));

    ret = SP_poll(mailboxParam);

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Test equality of two group ids (group id is an opaque type).
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      0 - not equal.
 *      1 - equal.
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI int 
GCS_EqualGroupIds(GCS_GROUP_ID groupId1, GCS_GROUP_ID groupId2)
{
    int ret = 0;

    ITS_TRACE_DEBUG(("GCS_EqualGroupIds:\n"));

    ITS_C_ASSERT(sizeof(GCS_GROUP_ID) == sizeof(group_id));

    ret = SP_equal_group_ids(*((group_id*)&groupId1), *((group_id*)&groupId2));

    return ret;
}


/*.implementation:extern
 *****************************************************************************
 *  Purpose:
 *      Report a GCS error with meaningfull text.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *      GCS associated documentation for more details.
 *
 *****************************************************************************/

GCSDLLAPI void 
GCS_ReportError(int error)
{
    ITS_TRACE_DEBUG(("GCS_ReportError:\n"));

    SP_error(error);
}



/******************************************************************************
 ******************************************************************************
 *
 *  Mailbox poll related.
 */

GCSDLLAPI int 
GCS_MailboxPoll(
        GCS_MAILBOX_POLL_INFO* mailboxPollInfos,
        ITS_UINT numMailboxPollInfos,
        GCS_TIME* timeout)
{
    fd_set readfds, writefds, errorfds;
    struct timeval tv;
    int i, max;
    int ret;

    ITS_C_REQUIRE(mailboxPollInfos != NULL);
    ITS_C_REQUIRE(numMailboxPollInfos >= 1);
    ITS_C_REQUIRE(timeout->sec >= 0);
    ITS_C_REQUIRE(timeout->sec <= 100000000);
    ITS_C_REQUIRE(timeout->usec >= 0);
    ITS_C_REQUIRE(timeout->usec < 1000000);

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&errorfds);

    max = 0;

    for (i = 0; i < (int)numMailboxPollInfos; i++)
    {
        mailboxPollInfos[i].wasSet = 0;

        if ((int)mailboxPollInfos[i].mailbox > max)
        {
            max = mailboxPollInfos[i].mailbox;
        }

        if (mailboxPollInfos[i].lookFor & GCS_POLL_READ)
        {
            FD_SET(mailboxPollInfos[i].mailbox, &readfds);
        }

        if (mailboxPollInfos[i].lookFor & GCS_POLL_WRITE)
        {
            FD_SET(mailboxPollInfos[i].mailbox, &writefds);
        }

        if (mailboxPollInfos[i].lookFor & GCS_POLL_ERROR)
        {
            FD_SET(mailboxPollInfos[i].mailbox, &errorfds);
        }
    }

    if (max > 0)
    {
        max++;
    }

    tv.tv_sec = timeout->sec;
    tv.tv_usec = timeout->usec;

    ret = select(
                max, 
                &readfds, 
                &writefds, 
                &errorfds, 
                &tv);
    if (ret < 0)
    {
        return ret;
    }
    else if (ret == 0)
    {
        return ret;
    }
    else
    {
        for (i = 0; i < (int)numMailboxPollInfos; i++)
        {
            if (FD_ISSET(mailboxPollInfos[i].mailbox, &readfds))
            {
                mailboxPollInfos[i].wasSet |= GCS_POLL_READ;
            }

            if (FD_ISSET(mailboxPollInfos[i].mailbox, &writefds))
            {
                mailboxPollInfos[i].wasSet |= GCS_POLL_WRITE;
            }

            if (FD_ISSET(mailboxPollInfos[i].mailbox, &errorfds))
            {
                mailboxPollInfos[i].wasSet |= GCS_POLL_ERROR;
            }
        }

        return ret;
    }
}


/******************************************************************************
 ******************************************************************************
 *
 *  Time related (see GCS code for more details).
 */

GCSDLLAPI GCS_TIME  
GCS_GetTime()
{
    sp_time result;

    ITS_TRACE_DEBUG(("GCS_GetTime:\n"));

    result = E_get_time();

    ITS_C_ASSERT(sizeof(GCS_TIME) == sizeof(sp_time));

    return *((GCS_TIME*)&result);
}

GCSDLLAPI GCS_TIME  
GCS_SubTime(GCS_TIME t, GCS_TIME delta)
{
    sp_time result;

    ITS_TRACE_DEBUG(("GCS_SubTime:\n"));

    result = E_sub_time(*((sp_time*)&t), *((sp_time*)&delta));

    ITS_C_ASSERT(sizeof(GCS_TIME) == sizeof(sp_time));

    return *((GCS_TIME*)&result);
}

GCSDLLAPI GCS_TIME  
GCS_AddTime(GCS_TIME t, GCS_TIME delta)
{
    sp_time result;

    ITS_TRACE_DEBUG(("GCS_AddTime:\n"));

    result = E_add_time(*((sp_time*)&t), *((sp_time*)&delta));

    ITS_C_ASSERT(sizeof(GCS_TIME) == sizeof(sp_time));

    return *((GCS_TIME*)&result);
}

GCSDLLAPI int       
GCS_CompareTime(GCS_TIME t1, GCS_TIME t2)
{
    ITS_TRACE_DEBUG(("GCS_CompareTime:\n"));

    return E_compare_time(*((sp_time*)&t1), *((sp_time*)&t2));
}



/******************************************************************************
 ******************************************************************************
 *
 *  Event related (see GCS code for more details).
 */


GCSDLLAPI int   
GCS_EventInitialize()
{
    ITS_TRACE_DEBUG(("GCS_EventInitialize:\n"));

    return E_init();
}

GCSDLLAPI int   
GCS_EventQueue(
            void (*function)(int code, void* data), 
            int code, 
            void* data,
            GCS_TIME deltaTime)
{
    ITS_TRACE_DEBUG(("GCS_EventQueue:\n"));

    ITS_C_ASSERT(sizeof(GCS_TIME) == sizeof(sp_time));

    return E_queue(function, code, data, *((sp_time*)&deltaTime));
}

GCSDLLAPI int   
GCS_EventDequeue( 
            void (*function)(int code, void* data), 
            int code,
            void* data)
{
    ITS_TRACE_DEBUG(("GCS_EventDequeue:\n"));

    return E_dequeue(function, code, data);
}

GCSDLLAPI void  
GCS_EventDelay(GCS_TIME t)
{
    ITS_TRACE_DEBUG(("GCS_EventDelay:\n"));

    ITS_C_ASSERT(sizeof(GCS_TIME) == sizeof(sp_time));

    E_delay(*((sp_time*)&t));
}

GCSDLLAPI int   
GCS_EventAttachFd(
            int fd,
            int fdType,
            void (*function)(int fd, int code, void* data),
            int code,
            void* data, 
            int priority)
{
    ITS_TRACE_DEBUG(("GCS_EventAttachFd:\n"));

    return E_attach_fd(fd, fdType, function, code, data, priority);
}

GCSDLLAPI int   
GCS_EventDetachFd(int fd, int fdType)
{
    ITS_TRACE_DEBUG(("GCS_EventDetachFd:\n"));

    return E_detach_fd(fd, fdType);
}

GCSDLLAPI int   
GCS_EventSetActiveThreshold(int priority)
{
    ITS_TRACE_DEBUG(("GCS_EventSetActiveThreshold:\n"));

    return E_set_active_threshold(priority);
}

GCSDLLAPI int   
GCS_EventActivateFd(int fd, int fdType)
{
    ITS_TRACE_DEBUG(("GCS_EventActivateFd:\n"));

    return E_activate_fd(fd, fdType);
}

GCSDLLAPI int   
GCS_EventDeactivateFd(int fd, int fdType)
{
    ITS_TRACE_DEBUG(("GCS_EventDeactivateFd:\n"));

    return E_deactivate_fd(fd, fdType);

}

GCSDLLAPI int   
GCS_EventNumActive(int priority)
{
    ITS_TRACE_DEBUG(("GCS_EventNumActive:\n"));

    return E_num_active(priority);
}

GCSDLLAPI void  
GCS_EventHandleEvents()
{
    ITS_TRACE_DEBUG(("GCS_EventHandleEvents:\n"));

    E_handle_events();
}

GCSDLLAPI void  
GCS_EventExitEvents()
{
    ITS_TRACE_DEBUG(("GCS_EventExitEvents:\n"));

    E_exit_events();
}






