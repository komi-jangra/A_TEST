/*  *********************************************************************
    File: ssltrspt.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: ssltrspt.h   SSL Transport Layer

    A single fabulous prototype for the single function in ssltrspt.h
    which isn't in ssl.h. You have found the SSLRef easter egg (such as
    it is). SSLRef by Tim Dierks, with help from Eric Gundrum, Chris
    Allen, Jonathan Zamick, and Michael Rutman. Thanks also to Jim
    CastroLang, Clare Burmeister, and Tony Hughes. Also, thanks to our
    friends at Netscape: Tom Weinstein, Jeff Weinstein, Phil Karlton, and
    Eric Greenberg.

    ****************************************************************** */

#ifndef _SSLTRSPT_H_
#define _SSLTRSPT_H_ 1

#ifndef _SSL_H_
#include "ssl.h"
#endif

#ifndef _SSLREC_H_
#include "sslrec.h"
#endif

SSLErr QueueMessage(SSLRecord rec, SSLContext *ctx);

#endif
