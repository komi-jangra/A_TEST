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
 *                                                                        
 * CONTRACT: INTERNAL                                           
 *                                                                       
 ****************************************************************************
 *  ID: $Id: server.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 ****************************************************************************
 *
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
 *  LOG: Revision 1.1.2.1  2005/12/22 16:33:37  adutta
 *  LOG: Initial checkin
 *  LOG:
 ***************************************************************************/

#ifndef GW_PDESIMULATOR_H
#define GW_PDESIMULATOR_H



// Number of pending connections queue will hold 

#include <pthread.h>

#define PENDING_CONNECTIONS 10
#define MAX_BUF_SIZE 1000


class Server
{
public:
    Server();
    void Createsocket(unsigned short);
    void ListenAccept();
    void ReadWrite();
    int Write(unsigned char* buf, unsigned int size);
    
    void ProcessMessage(unsigned char* buf, 
                        unsigned char* outputbuf, 
                        unsigned int &size);


private:
    int sockfd;
    int new_fd;
};

extern "C" void* PrintMenu(void*);


#endif
