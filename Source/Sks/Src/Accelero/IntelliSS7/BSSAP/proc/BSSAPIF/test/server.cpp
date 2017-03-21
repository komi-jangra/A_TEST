/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 2004 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: server.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $                                                             
 ***************************************************************************                                       
 *  LOG: $Log: not supported by cvs2svn $
 *  LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 *  LOG: init tree
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 *  LOG: BscCs2
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 *  LOG: BSC project
 *  LOG:
 *  LOG: Revision 1.1.2.1  2005/12/22 16:32:16  adutta
 *  LOG: Initial check in
 *  LOG:
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#include <server.h>

Server* server;

pthread_mutex_t mutex_ = PTHREAD_MUTEX_INITIALIZER;

/*.Implementation:
 *****************************************************************************
 * Purpose :
 *     This function displays the Menu options
 *
 * Input/Output Parameters:
 *    None
 *
 * Output Parameters:
 *     None.
 *
 * Return Value:
 *    None.
 *
 *****************************************************************************/

extern "C" void*
PrintMenu (void*)
{
    return NULL;
}

/*.Implementation:
 *****************************************************************************
 * Purpose :
 *     This function initializes the Mutex
 *
 * Input/Output Parameters:
 *    None
 *
 * Output Parameters:
 *     None.
 *
 * Return Value:
 *    None.
 *
 *****************************************************************************/
Server::Server()
{
}


/*.Implementation:
 *****************************************************************************
 * Purpose :
 *     This function will process the incoming message from GW
 *
 * Input/Output Parameters:
 *    buf - 
 *    outputbuf -  
 *
 * Output Parameters:
 *     size - size of the buf.
 *
 * Return Value:
 *    None.
 *
 *****************************************************************************/
void
Server::ProcessMessage(unsigned char* buf, 
                             unsigned char* outputbuf,
                             unsigned int &size)
{

}

/*.Implementation:public
 *****************************************************************************
 *  Purpose : 
 *      This function creates a Server Socket, and waits forever 
 *      to get message from SS7 Gateway and sends response back to gateway.
 * 
 *  Input Parameters:
 *      port  : Port number.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value: 
 *     None.
 *
 ****************************************************************************/
void
Server::Createsocket(unsigned short port)
{
    struct sockaddr_in my_addr;  

    printf("Server:CreateSocket\n");

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;    
    my_addr.sin_port = htons(port); 
    my_addr.sin_addr.s_addr = INADDR_ANY; 

    if (bind(sockfd, (struct sockaddr *)&my_addr,
                          sizeof(struct sockaddr))== -1)
    {
        perror("bind");
        exit(1);
    }
}

/*.Implementation:
 *****************************************************************************
 * Purpose :
 *     Socket is in listen mode and ready to accept the data
 *
 * Input/Output Parameters:
 *    None
 *
 * Output Parameters:
 *     None.
 *
 * Return Value:
 *    None.
 *
 *****************************************************************************/

void
Server::ListenAccept()
{
    struct sockaddr_in their_addr;

    printf("Server:ListenAccept\n");

    if (listen(sockfd, PENDING_CONNECTIONS) == -1)
    {
        perror("listen");
        exit(1);
    }

    socklen_t sin_size = sizeof(struct sockaddr_in);
    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr,
                                      &sin_size)) == -1)
    {
        perror("accept");
        return;
    }
    printf("CreateSocket:Server connected to client\n");
}


/*.Implementation:
 *****************************************************************************
 * Purpose :
 *     This function does the basic rear/write functionalities
 *
 * Input/Output Parameters:
 *    None
 *
 * Output Parameters:
 *     None.
 *
 * Return Value:
 *    None.
 *
 *****************************************************************************/

void
Server::ReadWrite()
{
    unsigned char buf[MAX_BUF_SIZE];
    unsigned char outputbuf[MAX_BUF_SIZE];
    unsigned int size = MAX_BUF_SIZE;

    printf("Server::ReadWrite\n");

    while(1) 
    {
        while (1)
        {
            if ((size = recv(new_fd, buf, MAX_BUF_SIZE, 0)) == -1)
            {
                perror("recv");
                break;
            }

            printf("------------- Received Buffer ---------------------\n");
            for (int i = 0 ; i < size ; i ++)
            printf("%02x ", buf[i]);
            printf("\n---------------------------------------------------");
            printf("\n\n\n");
    
            //ProcessMessage(buf, outputbuf, size);
        }
        ListenAccept();
    }
}

/*.Implementation:
 *****************************************************************************
 * Purpose :
 *     This function sends  response back to GW
 *
 * Input Parameters:
 *    buf - Input msg buffer
 *    size - size of buffer
 *
 * Output Parameters:
 *     None.
 *
 * Return Value:
 *    None.
 *
 *****************************************************************************/

int
Server::Write(unsigned char* buf, unsigned int size)
{
    if (size > 0)
    {
        pthread_mutex_lock(&mutex_);
        if ((size = send (new_fd, buf, size, 0)) == -1)
        {
            pthread_mutex_unlock(&mutex_);
            perror("send");
            return 1;
        }
        pthread_mutex_unlock(&mutex_);
        printf("------------- Sending Buffer -----------------------\n");
        for (int i = 0 ; i < size ; i ++)
        printf("%c", buf[i]);
        printf("\n");
        printf("---------------------------------------------------");
        printf("\n\n\n");
    }
    return 0;
}



/*.Implementation:
 *****************************************************************************
 * Purpose : 
 *     None          
 *
 * Input/Output Parameters:
 *    None
 *
 * Output Parameters:
 *     None.
 *
 * Return Value:
 *    None.
 *
 *****************************************************************************/
int 
main(int argc, char* argv[])
{
    int sockfd, numbytes;
    unsigned short port;
    unsigned char buf[MAX_BUF_SIZE];
    unsigned int size;
    struct hostent *he;
    struct sockaddr_in their_addr; 
    int Choice, ret = 0;
    pthread_t hbThread;
    
    if (argc != 2)
    {
        fprintf(stderr,"usage: bserver <port>\n");
        exit(1);
    }

    port = atoi(argv[1]);

    // Span a new thread to process the HeartBeat Message  
    
    ret = pthread_create(&hbThread, NULL, PrintMenu, NULL);

    if (ret !=0)
    {
        perror("pthread_create");
    }

    server = new Server;
    server->Createsocket(port);
    server->ListenAccept();
    server->ReadWrite();

    return 0;
}


