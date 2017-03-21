/*----------------------------------------------------------------------------*
 *                                                                            *
 *      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *              Manufactured in the United States of America.                 *
 *        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                            *
 *    This product and related documentation is protected by copyright and    *
 *    distributed under licenses restricting its use, copying, distribution   *
 *    and decompilation.  No part of this product or related documentation    *
 *    may be reproduced in any form by any means without prior written        *
 *    authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                            *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *    government is subject to restrictions as set forth in subparagraph      *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *
 *  ID: $Id: asn_assertion.c,v 1.1.1.1 2007-10-08 11:11:39 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#include <string.h>

#include <asn_assertion.h>



const char*
AsnStripPath(const char* str)
{
    char* result = NULL;


    if ((result = strrchr(str, '/')) == NULL)
    {
        result = strrchr(str, '\\');

        if (result)
        {
            result++;
        }
    }
    else
    {
        result++;
    }

    if (!result)
    {
        result = (char *)str;
    }

    return result;
}
      

 

 

