/*  *********************************************************************
    File: testio.c

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: testio.c     I/O callbacks for sslsampl


    ****************************************************************** */

#include "ssl.h"

#ifdef WIN32
#include <winsock.h>
#include <time.h>
#else
#include <unistd.h>
#endif

SSLErr SocketRead(SSLBuffer buffer, uint32 *processed, void *state);
SSLErr SocketWrite(SSLBuffer buffer, uint32 *processed, void *state);

SSLErr
SocketRead(SSLBuffer buffer, uint32 *processed, void *state)
{
#ifdef WIN32
    SOCKET      sock = *(SOCKET*)state;
    int         length;
    uint32      done;
    
    *processed = done = 0;

    do
    {   length = recv(sock, (char*)buffer.data + done, buffer.length - done, 0);
    } while   ( (length > 0) && ((done += length) < buffer.length) );

    *processed = done;
    
    if (*processed != buffer.length)
        return SSLIOErr;
    
#else
    int         sock = *(int*)state, length;
    uint32      done;
    
    *processed = done = 0;

    do
        length = read(sock, (char*)buffer.data + done, buffer.length - done);
    while (length > 0 && ((done += length) < buffer.length));
    
    *processed = done;
    
    if (*processed != buffer.length)
        return SSLIOErr;
#endif
    
    return SSLNoErr;
}

SSLErr
SocketWrite(SSLBuffer buffer, uint32 *processed, void *state)
{   
#ifdef WIN32
    SOCKET  sock = *(SOCKET*)state;
#else
    int     sock = *(int*)state;
#endif
    int     length;
    uint32  done;
    
    *processed = done = 0;
#ifdef WIN32
    do
        length = send(sock, (char*)buffer.data + done, buffer.length - done, 0);
    while ((length > 0) && ((done += length) < buffer.length));
#else
    do
        length = write(sock, (char*)buffer.data + done, buffer.length - done);
    while (length > 0 && ((done += length) < buffer.length));
#endif
    
    *processed = done;
    
    if (*processed != buffer.length)
        return SSLIOErr;
    
    return SSLNoErr;
}
