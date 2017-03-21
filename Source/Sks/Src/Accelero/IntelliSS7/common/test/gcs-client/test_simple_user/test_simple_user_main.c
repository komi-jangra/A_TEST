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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:37  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:17  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:31  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:00  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:08  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:16  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 1.1  2001/06/26 22:00:02  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/

/* 
 * Simple test for GCS client library (GCS daemon MUST be running).
 * 
 */

#include <its.h>

#include <stdio.h>

#include <gcs_client.h>


static  char user[80];
static  char gcsName[80];
static  char privateGroup[GCS_MAX_GROUP_NAME];

static  GCS_MAILBOX mailbox;

static int  ReadMessage();
static void Usage(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int ret;
    int msgLen;
    char msg[200];


    Usage(argc, argv);

    /* 
     * Connecting to GCS daemon, requesting group information.
     */

    ret = GCS_Connect(gcsName, user, 0, 1, &mailbox, privateGroup);

    if ( ret < 0 ) 
    {
        GCS_ReportError(ret);
        exit(0);
    }


    /* 
     * Join group named "simple_group".
     */

    ret = GCS_Join(mailbox, "simple_group");

    if ( ret < 0 ) 
    {
        GCS_ReportError(ret);
        exit(0);
    }


    printf("Enter message: ");

    ret = (int) fgets(msg, 200, stdin);

    if( ret==0 ) exit(0);

    msgLen = strlen(msg);


    /* 
     * Multicast a message to "simple_group".
     */

    ret = GCS_Multicast(
                mailbox, 
                GCS_AGREED_MSG, 
                "simple_group", 
                1, 
                msgLen, 
                msg);

    if ( ret < 0 ) 
    {
        GCS_ReportError(ret);
        exit(0);
    }

    /* 
     * Reading a message.
     * Note that the first message may be a membership caused by the join (if
     * group information was requested at connect time). If this is the case,
     * then read another message.
     */

    do
    {
        ret = ReadMessage();
    } 
    while (!GCS_IsRegularMsg(ret));

    return 0;
}


static int 
ReadMessage()
{
    static char     msg[102400];
    char            sender[GCS_MAX_GROUP_NAME];
    char            targetGroups[100][GCS_MAX_GROUP_NAME];
    GCS_GROUP_ID*   groupId;
    ITS_INT         numGroups;
    ITS_INT         numBytes;
    ITS_INT         service;
    ITS_SHORT       msgType;
    ITS_INT         endianMismatch;
    int             i;
    int             ret;

    printf("\n============================\n");

    ret = GCS_Receive(
                mailbox, 
                &service, 
                sender, 
                100, 
                &numGroups, 
                targetGroups, 
                &msgType, 
                &endianMismatch, 
                sizeof(msg), 
                msg);

    if ( ret < 0 ) 
    {
        GCS_ReportError(ret);
        exit(0);
    }

    if (GCS_IsRegularMsg(service))
    {
        /* 
         * A regular message, sent by one of the processes.
         */

        msg[ret] = 0;

        if (GCS_IsUnreliableMsg(service)) 
        {
            printf("Received UNRELIABLE ");
        }
        else if (GCS_IsReliableMsg(service)) 
        {
            printf("Received RELIABLE ");
        }
        else if (GCS_IsFifoMsg(service)) 
        {
            printf("Received FIFO ");
        }
        else if (GCS_IsCausalMsg(service))
        {
            printf("Received CAUSAL ");
        }
        else if (GCS_IsAgreedMsg(service)) 
        {
            printf("received AGREED ");
        }
        else if (GCS_IsSafeMsg(service))
        {
            printf("received SAFE ");
        }

        printf(
            "message from %s of type %d (endian %d), "
            "to %d groups \n(%d bytes): %s.\n",
             sender, 
             msgType, 
             endianMismatch, 
             numGroups, 
             ret, 
             msg);

    }
    else if (GCS_IsMembershipMsg(service))
    {
        /* 
         * A membership notification.
         */

        if (GCS_IsRegMembMsg(service))
        {
            numBytes = 0;
            groupId = (GCS_GROUP_ID*)&msg[numBytes];
            numBytes += sizeof(GCS_GROUP_ID);
            printf("Received REGULAR membership ");
            if (GCS_IsCausedJoinMsg(service)) 
            {
                printf("caused by JOIN ");
            }
            if (GCS_IsCausedLeaveMsg(service))
            {
                printf("caused by LEAVE ");
            }
            if (GCS_IsCausedDisconnectMsg(service))
            {
                printf("caused by DISCONNECT ");
            }
            printf("for group %s with %d members:\n", sender, numGroups);

            for (i = 0; i < numGroups; i++)
            {
                printf("\t%s\n", &targetGroups[i][0]);
            }

            printf(
                "grp id is %d %d %d\n",
                groupId->id[0], 
                groupId->id[1], 
                groupId->id[2] );

        }
        else if (GCS_IsTransitionMsg(service)) 
        {
            printf(
                "received TRANSITIONAL membership for group %s\n", 
                sender);
        }
        else if (GCS_IsCausedLeaveMsg(service))
        {
            printf(
                "received membership message that left group %s\n", 
                sender);
        }
        else 
        {
            printf(
                "received incorrect membership message of type %d\n", 
                service);
        }
    } 
    else 
    {
        printf(
            "received message of unknown message type %d with %d bytes\n", 
            service,
            ret);
    }

    return(service);
}

static void 
Usage(int argc, char *argv[])
{

    /* Setting defaults */
    sprintf(user, "simple");

#if defined(WIN32)

    sprintf(gcsName, "4803@localhost");

#else /* !defined(WIN32) */

    sprintf(gcsName, "4803");

#endif /* defined(WIN32) */

    while (--argc > 0)
    {
        argv++;

        if (!strncmp( *argv, "-u", 2))
        {
            strcpy(user, argv[1]);
            argc--; 
            argv++;
        } 
        else if (!strncmp(*argv, "-s", 2))
        {
            strcpy(gcsName, argv[1]);
            argc--; 
            argv++;
        }else{
            printf("Usage: user\n%s\n%s\n",
                "\t[-u <user name>]  : unique (in this machine) user name",
                "\t[-s <address>]    : either port or port@machine");
            exit(1);
         }
    }
}
