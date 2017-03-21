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
 *  ID: $ $
 ****************************************************************************
 * LOG: $ $
 * LOG:
 ****************************************************************************/

#include <iostream>

#include <its++.h>

#include <AppCodec.h>

#if defined(ITS_STD_NAMESPACE)

using namespace std;
using namespace its;

#endif 

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function will be used if this application works as codec only.
 *      It will encode the given message and then it will decodes it. 
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

void EncodeDecode()
{
    ITS_OCTET encOctets[1024];
    int len;
    int choice, op; 

    while (1)
    {
        BuildMsg(encOctets, &len);
        InterpretMsg(encOctets, len);
    }
}
