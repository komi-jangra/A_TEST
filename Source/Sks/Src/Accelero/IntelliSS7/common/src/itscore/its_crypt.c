/****************************************************************************
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:51:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/08/15 19:02:50  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.2  2002/07/08 22:34:52  mmiers
 * LOG: Add AES for EAP
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:02  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/07/27 19:59:16  mmiers
 * LOG:
 * LOG: Move things around so we can publish the license API.
 * LOG:
 * LOG: Revision 2.7  2000/07/17 15:24:19  mmiers
 * LOG:
 * LOG:
 * LOG: Small API changes, mostly typing.
 * LOG:
 * LOG: Revision 2.6  2000/07/03 22:40:15  mmiers
 * LOG:
 * LOG:
 * LOG: Add message digest
 * LOG:
 * LOG: Revision 2.5  2000/07/03 22:06:07  mmiers
 * LOG:
 * LOG:
 * LOG: Add secure hash.
 * LOG:
 * LOG: Revision 2.4  2000/03/18 21:03:49  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.3  2000/02/14 19:17:39  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.2  2000/02/01 23:41:51  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more feature initialization.
 * LOG:
 * LOG: Revision 2.1  2000/02/01 23:09:13  mmiers
 * LOG:
 * LOG:
 * LOG: Auto start the license system.  Can do away with standalone *now*.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:21  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/11/02 21:45:15  labuser
 * LOG:
 * LOG:
 * LOG: Make clock reversal sensing configurable.
 * LOG:
 * LOG: Revision 1.4  1999/07/29 00:08:39  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.3  1999/03/24 22:45:27  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a number of bugs with the new infrastructure.  Provide an
 * LOG: example for the new format INI files.  Add duration to licensing
 * LOG: scheme.  Fix memory leak in timer subsystem.  Fix initialization
 * LOG: bug in thread lib.
 * LOG:
 * LOG: Revision 1.2  1999/03/24 17:38:12  mmiers
 * LOG:
 * LOG:
 * LOG: Formatting.
 * LOG:
 * LOG: Revision 1.1  1999/03/12 18:20:11  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.9  1999/03/12 00:06:13  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.8  1999/02/04 22:57:41  mmiers
 * LOG:
 * LOG:
 * LOG: Some tweaks, detail improvement.
 * LOG:
 * LOG: Revision 1.7  1999/02/04 22:26:38  mmiers
 * LOG:
 * LOG:
 * LOG: Fool around with this thing a bit.
 * LOG:
 * LOG: Revision 1.6  1998/11/19 21:13:00  mmiers
 * LOG: Build on Solaris.
 * LOG:
 * LOG: Revision 1.5  1998/11/19 15:39:47  mmiers
 * LOG: Fix NT build.
 * LOG:
 * LOG: Revision 1.4  1998/11/19 00:36:25  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.3  1998/09/22 17:28:29  mmiers
 * LOG: More work adding C-trace into the library.
 * LOG:
 * LOG: Revision 1.2  1998/05/14 20:45:59  mmiers
 * LOG: Remove references to non-associated projects.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 19:00:13  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 * LOG: Revision 1.1  1998/01/24 21:51:14  mmiers
 * LOG: Move these around a bit.
 * LOG:
 * LOG: Revision 1.2  1998/01/24 21:49:05  mmiers
 * LOG: license.c: Encrypt/decrypt the license file.
 * LOG: crlicense.c: create a license.
 * LOG: mklicense.c: convert a plaintext license to encrypted form.
 * LOG: readlicense.c: read a license file.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_crypt.h>
#include <its_assertion.h>

#ident "$Id: its_crypt.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      swap two bytes in place
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
swap_byte(ITS_OCTET *a, ITS_OCTET *b)
{
    ITS_OCTET swapByte; 
     
    swapByte = *a; 
    *a = *b;      
    *b = swapByte;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      initialize the key structure.  The encryption algorithm used is RC4.
 *      RC4 is a symmetric stream cipher; see "Applied Cryptography" (Schneier)
 *      for details.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
CRYPT_InitKey(ITS_Key *key, ITS_OCTET *keydat, ITS_UINT keylen)
{
    ITS_OCTET index1;
    ITS_OCTET index2;
    ITS_OCTET *state;
    short counter;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(keydat != NULL);

    state = &key->state[0];
    for (counter = 0; counter < 256; counter++)
    {
        state[counter] = (ITS_OCTET)counter;
    }

    key->x = 0;
    key->y = 0;
    index1 = 0;
    index2 = 0;

    for (counter = 0; counter < 256; counter++)
    {

        index2 = (ITS_OCTET)((keydat[index1] + state[counter] + index2) % 256);
        swap_byte(&state[counter], &state[index2]);

        index1 = (ITS_OCTET)((index1 + 1) % keylen);
    }
}
 
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      encrypt and decrypt are the same function (RC4 is symmetric), but
 *      nobody else needs to know that.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
CRYPT_Encrypt(ITS_Key *key, ITS_OCTET *buf, ITS_UINT blen)
{ 
    ITS_OCTET x;
    ITS_OCTET y;
    ITS_OCTET *state;
    ITS_OCTET xorIndex;
    ITS_UINT counter;              

    ITS_C_REQUIRE(key != NULL);
    /* buf can be NULL but only if blen is zero */
    ITS_C_REQUIRE(buf != NULL || blen == 0);

    x = key->x;     
    y = key->y;     
     
    state = &key->state[0];         
    for(counter = 0; counter < blen; counter ++)
    {

        x = (ITS_OCTET)((x + 1) % 256);
        y = (ITS_OCTET)((state[x] + y) % 256);

        swap_byte(&state[x], &state[y]);

        xorIndex = (ITS_OCTET)(state[x] + (state[y]) % 256);

        buf[counter] ^= state[xorIndex];         
    }               

    key->x = x;     
    key->y = y;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      encrypt and decrypt are the same function (RC4 is symmetric), but
 *      nobody else needs to know that.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
CRYPT_Decrypt(ITS_Key *key, ITS_OCTET *buf, ITS_UINT blen)
{ 
    ITS_OCTET x;
    ITS_OCTET y;
    ITS_OCTET *state;
    ITS_OCTET xorIndex;
    ITS_UINT counter;              
     
    ITS_C_REQUIRE(key != NULL);
    /* buf can be NULL but only if blen is zero */
    ITS_C_REQUIRE(buf != NULL || blen == 0);

    x = key->x;     
    y = key->y;     

    state = &key->state[0];         
    for(counter = 0; counter < blen; counter ++)
    {

        x = (ITS_OCTET)((x + 1) % 256);
        y = (ITS_OCTET)((state[x] + y) % 256);

        swap_byte(&state[x], &state[y]);

        xorIndex = (ITS_OCTET)(state[x] + (state[y]) % 256);

        buf[counter] ^= state[xorIndex];         
    }               

    key->x = x;     
    key->y = y;
}

/****************************************************************************
 * rijndael-alg-ref.c   v2.0   August '99
 * Reference ANSI C code
 * authors: Paulo Barreto
 *          Vincent Rijmen
 *                       ------------------------------
 *                       Rijndael ANSI C Reference Code
 *                       ------------------------------
 *
 *                                October 24, 2000
 *
 *                                  Disclaimer
 *
 *
 * This software package was submitted to the National Institute of
 * Standards and Technology (NIST) during the Advanced Encryption
 * Standard (AES) development effort by Joan Daemen and Vincent Rijmen,
 * the developers of the Rijndael algorithm.
 *
 * This software is distributed in compliance with export regulations
 * (see below), and it is intended for non-commercial use, only.   NIST
 * does not support this software and does not provide any guarantees or
 * warranties as to its performance, fitness for any particular application,
 * or validation under the Cryptographic Module Validation Program (CMVP)
 * <http://csrc.nist.gov/cryptval/>.  NIST does not accept any liability
 * associated with its use or misuse.  This software is provided as-is. 
 * By accepting this software the user agrees to the terms stated herein.
 *
 *                            -----------------------
 *
 *                              Export Restrictions
 *
 *
 * Implementations of cryptography are subject to United States Federal
 * Government export controls.  Export controls on commercial encryption
 * products are administered by the Bureau of Export Administration (BXA) 
 * <http://www.bxa.doc.gov/Encryption/> in the U.S. Department of Commerce. 
 * Regulations governing exports of encryption are found in the Export 
 * Administration Regulations (EAR), 15 C.F.R. Parts 730-774.
 */

#include <its.h>
#include <its_crypt.h>

static ITS_OCTET Logtable[256] =
{
      0,   0,  25,   1,  50,   2,  26, 198,  75, 199,  27, 104,  51, 238, 223,   3, 
    100,   4, 224,  14,  52, 141, 129, 239,  76, 113,   8, 200, 248, 105,  28, 193, 
    125, 194,  29, 181, 249, 185,  39, 106,  77, 228, 166, 114, 154, 201,   9, 120, 
    101,  47, 138,   5,  33,  15, 225,  36,  18, 240, 130,  69,  53, 147, 218, 142, 
    150, 143, 219, 189,  54, 208, 206, 148,  19,  92, 210, 241,  64,  70, 131,  56, 
    102, 221, 253,  48, 191,   6, 139,  98, 179,  37, 226, 152,  34, 136, 145,  16, 
    126, 110,  72, 195, 163, 182,  30,  66,  58, 107,  40,  84, 250, 133,  61, 186, 
     43, 121,  10,  21, 155, 159,  94, 202,  78, 212, 172, 229, 243, 115, 167,  87, 
    175,  88, 168,  80, 244, 234, 214, 116,  79, 174, 233, 213, 231, 230, 173, 232, 
     44, 215, 117, 122, 235,  22,  11, 245,  89, 203,  95, 176, 156, 169,  81, 160, 
    127,  12, 246, 111,  23, 196,  73, 236, 216,  67,  31,  45, 164, 118, 123, 183, 
    204, 187,  62,  90, 251,  96, 177, 134,  59,  82, 161, 108, 170,  85,  41, 157, 
    151, 178, 135, 144,  97, 190, 220, 252, 188, 149, 207, 205,  55,  63,  91, 209, 
     83,  57, 132,  60,  65, 162, 109,  71,  20,  42, 158,  93,  86, 242, 211, 171, 
     68,  17, 146, 217,  35,  32,  46, 137, 180, 124, 184,  38, 119, 153, 227, 165, 
    103,  74, 237, 222, 197,  49, 254,  24,  13,  99, 140, 128, 192, 247, 112,   7, 
};

static ITS_OCTET Alogtable[256] =
{
      1,   3,   5,  15,  17,  51,  85, 255,  26,  46, 114, 150, 161, 248,  19,  53, 
     95, 225,  56,  72, 216, 115, 149, 164, 247,   2,   6,  10,  30,  34, 102, 170, 
    229,  52,  92, 228,  55,  89, 235,  38, 106, 190, 217, 112, 144, 171, 230,  49, 
     83, 245,   4,  12,  20,  60,  68, 204,  79, 209, 104, 184, 211, 110, 178, 205, 
     76, 212, 103, 169, 224,  59,  77, 215,  98, 166, 241,   8,  24,  40, 120, 136, 
    131, 158, 185, 208, 107, 189, 220, 127, 129, 152, 179, 206,  73, 219, 118, 154, 
    181, 196,  87, 249,  16,  48,  80, 240,  11,  29,  39, 105, 187, 214,  97, 163, 
    254,  25,  43, 125, 135, 146, 173, 236,  47, 113, 147, 174, 233,  32,  96, 160, 
    251,  22,  58,  78, 210, 109, 183, 194,  93, 231,  50,  86, 250,  21,  63,  65, 
    195,  94, 226,  61,  71, 201,  64, 192,  91, 237,  44, 116, 156, 191, 218, 117, 
    159, 186, 213, 100, 172, 239,  42, 126, 130, 157, 188, 223, 122, 142, 137, 128, 
    155, 182, 193,  88, 232,  35, 101, 175, 234,  37, 111, 177, 200,  67, 197,  84, 
    252,  31,  33,  99, 165, 244,   7,   9,  27,  45, 119, 153, 176, 203,  70, 202, 
     69, 207,  74, 222, 121, 139, 134, 145, 168, 227,  62,  66, 198,  81, 243,  14, 
     18,  54,  90, 238,  41, 123, 141, 140, 143, 138, 133, 148, 167, 242,  13,  23, 
     57,  75, 221, 124, 132, 151, 162, 253,  28,  36, 108, 180, 199,  82, 246,   1, 
};

static ITS_OCTET S[256] =
{
     99, 124, 119, 123, 242, 107, 111, 197,  48,   1, 103,  43, 254, 215, 171, 118, 
    202, 130, 201, 125, 250,  89,  71, 240, 173, 212, 162, 175, 156, 164, 114, 192, 
    183, 253, 147,  38,  54,  63, 247, 204,  52, 165, 229, 241, 113, 216,  49,  21, 
      4, 199,  35, 195,  24, 150,   5, 154,   7,  18, 128, 226, 235,  39, 178, 117, 
      9, 131,  44,  26,  27, 110,  90, 160,  82,  59, 214, 179,  41, 227,  47, 132, 
     83, 209,   0, 237,  32, 252, 177,  91, 106, 203, 190,  57,  74,  76,  88, 207, 
    208, 239, 170, 251,  67,  77,  51, 133,  69, 249,   2, 127,  80,  60, 159, 168, 
     81, 163,  64, 143, 146, 157,  56, 245, 188, 182, 218,  33,  16, 255, 243, 210, 
    205,  12,  19, 236,  95, 151,  68,  23, 196, 167, 126,  61, 100,  93,  25, 115, 
     96, 129,  79, 220,  34,  42, 144, 136,  70, 238, 184,  20, 222,  94,  11, 219, 
    224,  50,  58,  10,  73,   6,  36,  92, 194, 211, 172,  98, 145, 149, 228, 121, 
    231, 200,  55, 109, 141, 213,  78, 169, 108,  86, 244, 234, 101, 122, 174,   8, 
    186, 120,  37,  46,  28, 166, 180, 198, 232, 221, 116,  31,  75, 189, 139, 138, 
    112,  62, 181, 102,  72,   3, 246,  14,  97,  53,  87, 185, 134, 193,  29, 158, 
    225, 248, 152,  17, 105, 217, 142, 148, 155,  30, 135, 233, 206,  85,  40, 223, 
    140, 161, 137,  13, 191, 230,  66, 104,  65, 153,  45,  15, 176,  84, 187,  22, 
};

static ITS_OCTET Si[256] =
{
     82,   9, 106, 213,  48,  54, 165,  56, 191,  64, 163, 158, 129, 243, 215, 251, 
    124, 227,  57, 130, 155,  47, 255, 135,  52, 142,  67,  68, 196, 222, 233, 203, 
     84, 123, 148,  50, 166, 194,  35,  61, 238,  76, 149,  11,  66, 250, 195,  78, 
      8,  46, 161, 102,  40, 217,  36, 178, 118,  91, 162,  73, 109, 139, 209,  37, 
    114, 248, 246, 100, 134, 104, 152,  22, 212, 164,  92, 204,  93, 101, 182, 146, 
    108, 112,  72,  80, 253, 237, 185, 218,  94,  21,  70,  87, 167, 141, 157, 132, 
    144, 216, 171,   0, 140, 188, 211,  10, 247, 228,  88,   5, 184, 179,  69,   6, 
    208,  44,  30, 143, 202,  63,  15,   2, 193, 175, 189,   3,   1,  19, 138, 107, 
     58, 145,  17,  65,  79, 103, 220, 234, 151, 242, 207, 206, 240, 180, 230, 115, 
    150, 172, 116,  34, 231, 173,  53, 133, 226, 249,  55, 232,  28, 117, 223, 110, 
     71, 241,  26, 113,  29,  41, 197, 137, 111, 183,  98,  14, 170,  24, 190,  27, 
    252,  86,  62,  75, 198, 210, 121,  32, 154, 219, 192, 254, 120, 205,  90, 244, 
     31, 221, 168,  51, 136,   7, 199,  49, 177,  18,  16,  89,  39, 128, 236,  95, 
     96,  81, 127, 169,  25, 181,  74,  13,  45, 229, 122, 159, 147, 201, 156, 239, 
    160, 224,  59,  77, 174,  42, 245, 176, 200, 235, 187,  60, 131,  83, 153,  97, 
     23,  43,   4, 126, 186, 119, 214,  38, 225, 105,  20,  99,  85,  33,  12, 125, 
};

static ITS_UINT rcon[30] =
{ 
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc,
    0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4,
    0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91
};

static ITS_OCTET shifts[3][4][2] =
{
    {
        { 0, 0 },
        { 1, 3 },
        { 2, 2 },
        { 3, 1 }
    },
    {   
        { 0, 0 },
        { 1, 5 },
        { 2, 4 },
        { 3, 3 }
    },
    {
        { 0, 0 },
        { 1, 7 },
        { 3, 5 },
        { 4, 4 }
    }
}; 

/*
 * shorthand used in the algo
 */
#define SC	((BC - 4) >> 1)

/*
 * multiply two elements of GF(2^m)
 * needed for MixColumn and InvMixColumn
 */
static ITS_OCTET
mul(ITS_OCTET a, ITS_OCTET b)
{
    if (a && b)
    {
        return (Alogtable[(Logtable[a] + Logtable[b]) % 255]);
    }
    else
    {
        return 0;
    }
}

/*
 * XOR corresponding text input and round key input bytes
 */
static void
KeyAddition(ITS_OCTET a[4][MAXBC], ITS_OCTET rk[4][MAXBC],
            ITS_OCTET BC)
{
    int i, j;
    
    for (i = 0; i < 4; i++)
    {
       for (j = 0; j < BC; j++)
       {
           a[i][j] ^= rk[i][j];
       }
    }
}

/* Row 0 remains unchanged
 * The other three rows are shifted a variable amount
 */
static void
ShiftRow(ITS_OCTET a[4][MAXBC], ITS_OCTET d, ITS_OCTET BC)
{
    ITS_OCTET tmp[MAXBC];
    int i, j;
    
    for (i = 1; i < 4; i++)
    {
        for (j = 0; j < BC; j++)
        {
            tmp[j] = a[i][(j + shifts[SC][i][d]) % BC];
        }
        for (j = 0; j < BC; j++)
        {
            a[i][j] = tmp[j];
        }
    }
}

/*
 * Replace every byte of the input by the byte at that place
 * in the nonlinear S-box
 */
static void
Substitution(ITS_OCTET a[4][MAXBC], ITS_OCTET box[256],
             ITS_OCTET BC)
{
    int i, j;
    
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < BC; j++)
        {
            a[i][j] = box[a[i][j]];
        }
    }
}
   
/*
 * Mix the four bytes of every column in a linear way
 */
static void
MixColumn(ITS_OCTET a[4][MAXBC], ITS_OCTET BC)
{
    ITS_OCTET b[4][MAXBC];
    int i, j;
	    
    for (j = 0; j < BC; j++)
    {
        for (i = 0; i < 4; i++)
        {
            b[i][j] = (ITS_OCTET)(mul(2,a[i][j])
                                  ^ mul(3,a[(i + 1) % 4][j])
                                  ^ a[(i + 2) % 4][j]
                                  ^ a[(i + 3) % 4][j]);
        }
    }

    for (i = 0; i < 4; i++)
    {
        for(j = 0; j < BC; j++)
        {
            a[i][j] = b[i][j];
        }
    }
}

/*
 * Mix the four bytes of every column in a linear way
 * This is the opposite operation of Mixcolumn
 */
static void
InvMixColumn(ITS_OCTET a[4][MAXBC], ITS_OCTET BC)
{
    ITS_OCTET b[4][MAXBC];
    int i, j;
    
    for (j = 0; j < BC; j++)
    {
        for (i = 0; i < 4; i++)
        {
            b[i][j] = (ITS_OCTET)(mul(0xe,a[i][j])
                                  ^ mul(0xb,a[(i + 1) % 4][j])
                                  ^ mul(0xd,a[(i + 2) % 4][j])
                                  ^ mul(0x9,a[(i + 3) % 4][j]));
        }
    }

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < BC; j++)
        {
            a[i][j] = b[i][j];
        }
    }
}

/*
 * Calculate the necessary round keys
 * The number of calculations depends on keyBits and blockBits
 */
static int
rijndaelKeySched(ITS_OCTET k[4][MAXKC],
                 int keyBits, int blockBits,
                 ITS_OCTET W[MAXROUNDS+1][4][MAXBC])
{
    int KC, BC, ROUNDS;
    int i, j, t, rconpointer = 0;
    ITS_OCTET tk[4][MAXKC];   

    switch (keyBits)
    {
    case 128:
        KC = 4;
        break;
    case 192:
        KC = 6;
        break;
    case 256:
        KC = 8;
        break;
    default:
        return (ITS_EINVALIDARGS);
    }

    switch (blockBits)
    {
    case 128:
        BC = 4;
        break;
    case 192:
        BC = 6;
        break;
    case 256:
        BC = 8;
        break;
    default:
        return (ITS_EINVALIDARGS);
    }

    switch (keyBits >= blockBits ? keyBits : blockBits)
    {
    case 128:
        ROUNDS = 10;
        break;
    case 192:
        ROUNDS = 12;
        break;
    case 256:
        ROUNDS = 14;
        break;
    default:
        return (ITS_EINVALIDARGS); /* this cannot happen */
    }

    for (j = 0; j < KC; j++)
    {
        for (i = 0; i < 4; i++)
        {
            tk[i][j] = k[i][j];
        }
    }

    t = 0;

    /* copy values into round key array */
    for (j = 0; (j < KC) && (t < (ROUNDS+1)*BC); j++, t++)
    {
        for(i = 0; i < 4; i++)
        {
            W[t / BC][i][t % BC] = tk[i][j];
        }
    }
	    
    /* while not enough round key material calculated */
    while (t < (ROUNDS+1) * BC)
    {
	/* calculate new values */
        for(i = 0; i < 4; i++)
        {
            tk[i][0] ^= S[tk[(i+1)%4][KC-1]];
        }

        tk[0][0] ^= rcon[rconpointer++];

        if (KC != 8)
        {
            for (j = 1; j < KC; j++)
            {
                for (i = 0; i < 4; i++)
                {
                    tk[i][j] ^= tk[i][j-1];
                }
            }
        }
        else
        {
            for(j = 1; j < KC/2; j++)
            {
                for(i = 0; i < 4; i++)
                {
                    tk[i][j] ^= tk[i][j-1];
                }
            }

            for(i = 0; i < 4; i++)
            {
                tk[i][KC/2] ^= S[tk[i][KC/2 - 1]];
            }

            for(j = KC/2 + 1; j < KC; j++)
            {
                for(i = 0; i < 4; i++)
                {
                    tk[i][j] ^= tk[i][j-1];
                }
            }
        }

        /* copy values into round key array */
        for (j = 0; (j < KC) && (t < (ROUNDS+1)*BC); j++, t++)
        {
            for (i = 0; i < 4; i++)
            {
                W[t / BC][i][t % BC] = tk[i][j];
            }
        }
    }		

    return (ITS_SUCCESS);
}
      
/*
 * Encryption of one block. 
 */
static int
rijndaelEncrypt(ITS_OCTET a[4][MAXBC],
                int keyBits, int blockBits,
                ITS_OCTET rk[MAXROUNDS+1][4][MAXBC])
{
    int r, ROUNDS;
    ITS_OCTET BC;

    switch (blockBits)
    {
    case 128:
        BC = 4;
        break;
    case 192:
        BC = 6;
        break;
    case 256:
        BC = 8;
        break;
    default:
        return (ITS_EINVALIDARGS);
    }

    switch (keyBits >= blockBits ? keyBits : blockBits)
    {
    case 128:
        ROUNDS = 10;
        break;
    case 192:
        ROUNDS = 12;
        break;
    case 256:
        ROUNDS = 14;
        break;
    default:
        return (ITS_EINVALIDARGS); /* this cannot happen */
    }

    /* begin with a key addition */
    KeyAddition(a, rk[0], BC); 

    /* ROUNDS-1 ordinary rounds */
    for (r = 1; r < ROUNDS; r++)
    {
        Substitution(a, S, BC);
        ShiftRow(a, 0, BC);
        MixColumn(a, BC);
        KeyAddition(a, rk[r], BC);
    }
    
    /* Last round is special: there is no MixColumn */
    Substitution(a, S, BC);
    ShiftRow(a, 0, BC);
    KeyAddition(a, rk[ROUNDS], BC);

    return (ITS_SUCCESS);
}   



/*
 * Encrypt only a certain number of rounds.
 * Only used in the Intermediate Value Known Answer Test.
 */
static int
rijndaelEncryptRound(ITS_OCTET a[4][MAXBC],
                     int keyBits, int blockBits, 
                     ITS_OCTET rk[MAXROUNDS+1][4][MAXBC],
                     int rounds)
{
    int r, ROUNDS;
    ITS_OCTET BC;

    switch (blockBits)
    {
    case 128:
        BC = 4;
        break;
    case 192:
        BC = 6;
        break;
    case 256:
        BC = 8;
        break;
    default:
        return (ITS_EINVALIDARGS);
    }

    switch (keyBits >= blockBits ? keyBits : blockBits)
    {
    case 128:
        ROUNDS = 10;
        break;
    case 192:
        ROUNDS = 12;
        break;
    case 256:
        ROUNDS = 14;
        break;
    default:
        return (ITS_EINVALIDARGS); /* this cannot happen */
    }

    /* make number of rounds sane */
    if (rounds > ROUNDS)
    {
        rounds = ROUNDS;
    }

    /* begin with a key addition */
    KeyAddition(a, rk[0], BC);
    
    /* at most ROUNDS-1 ordinary rounds */
    for (r = 1; (r <= rounds) && (r < ROUNDS); r++)
    {
        Substitution(a, S, BC);
        ShiftRow(a, 0, BC);
        MixColumn(a, BC);
        KeyAddition(a, rk[r], BC);
    }
    
    /* if necessary, do the last, special, round: */
    if (rounds == ROUNDS)
    {
        Substitution(a, S, BC);
        ShiftRow(a, 0, BC);
        KeyAddition(a, rk[ROUNDS], BC);
    }

    return (ITS_SUCCESS);
}


/*
 * To decrypt: apply the inverse operations of the encrypt routine,
 *             in opposite order
 * 
 * (KeyAddition is an involution: it 's equal to its inverse)
 * (the inverse of Substitution with table S is Substitution with the inverse table of S)
 * (the inverse of Shiftrow is Shiftrow over a suitable distance)
 */
static int
rijndaelDecrypt(ITS_OCTET a[4][MAXBC],
                int keyBits, int blockBits,
                ITS_OCTET rk[MAXROUNDS+1][4][MAXBC])
{
    int r, ROUNDS;
    ITS_OCTET BC;
    
    switch (blockBits)
    {
    case 128:
        BC = 4;
        break;
    case 192:
        BC = 6;
        break;
    case 256:
        BC = 8;
        break;
    default:
        return (ITS_EINVALIDARGS);
    }

    switch (keyBits >= blockBits ? keyBits : blockBits)
    {
    case 128:
        ROUNDS = 10;
        break;
    case 192:
        ROUNDS = 12;
        break;
    case 256:
        ROUNDS = 14;
        break;
    default:
        return (ITS_EINVALIDARGS); /* this cannot happen */
    }

    /*
     * First the special round:
     *   without InvMixColumn
     *   with extra KeyAddition
     */
    KeyAddition(a, rk[ROUNDS], BC);
    Substitution(a, Si, BC);
    ShiftRow(a, 1, BC);              
    
    /* ROUNDS-1 ordinary rounds */
    for (r = ROUNDS-1; r > 0; r--)
    {
        KeyAddition(a, rk[r], BC);
        InvMixColumn(a, BC);      
        Substitution(a, Si, BC);
        ShiftRow(a, 1, BC);                
    }
    
    /* End with the extra key addition */
    KeyAddition(a, rk[0], BC);

    return (ITS_SUCCESS);
}

/*
 * Decrypt only a certain number of rounds.
 * Only used in the Intermediate Value Known Answer Test.
 * Operations rearranged such that the intermediate values
 * of decryption correspond with the intermediate values
 * of encryption.
 */
static int
rijndaelDecryptRound(ITS_OCTET a[4][MAXBC],
                     int keyBits, int blockBits, 
                     ITS_OCTET rk[MAXROUNDS+1][4][MAXBC],
                     int rounds)
{
    int r, ROUNDS;
    ITS_OCTET BC;
    
    switch (blockBits)
    {
    case 128:
        BC = 4;
        break;
    case 192:
        BC = 6;
        break;
    case 256:
        BC = 8;
        break;
    default:
        return (ITS_EINVALIDARGS);
    }

    switch (keyBits >= blockBits ? keyBits : blockBits)
    {
    case 128:
        ROUNDS = 10;
        break;
    case 192:
        ROUNDS = 12;
        break;
    case 256:
        ROUNDS = 14;
        break;
    default:
        return (ITS_EINVALIDARGS); /* this cannot happen */
    }

    /* make number of rounds sane */
    if (rounds > ROUNDS)
    {
        rounds = ROUNDS;
    }

    /*
     * First the special round:
     *   without InvMixColumn
     *   with extra KeyAddition
     */
    KeyAddition(a, rk[ROUNDS], BC);
    Substitution(a, Si, BC);
    ShiftRow(a, 1, BC);              
    
    /* ROUNDS-1 ordinary rounds */
    for (r = ROUNDS-1; r > rounds; r--)
    {
        KeyAddition(a, rk[r], BC);
        InvMixColumn(a, BC);
        Substitution(a, Si, BC);
        ShiftRow(a, 1, BC);
    }
    
    /* End with the extra key addition */	
    if (rounds == 0)
    {
        KeyAddition(a,rk[0],BC);
    }    

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize an AES key structure
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
AES_MakeKey(ITS_BlockKey *key, ITS_BlockDir direction,
            int keyLen, char *keyMaterial)
{
    ITS_OCTET k[4][MAXKC];
    int i, j, t;
    
    if (key == NULL)
    {
	return (ITS_EINVALIDARGS);
    }

    if ((direction == DIR_ENCRYPT) || (direction == DIR_DECRYPT))
    {
        key->direction = direction;
    }
    else
    {
        return (ITS_EINVALIDARGS);
    }

    if ((keyLen == 128) || (keyLen == 192) || (keyLen == 256))
    {
        key->keyLen = keyLen;
    }
    else
    {
        return (ITS_EINVALIDARGS);
    }

    if (keyMaterial)
    {
        strncpy(key->keyMaterial, keyMaterial, keyLen/4);
    }

    /* initialize key schedule: */ 
    for(i = 0; i < key->keyLen/8; i++)
    {
        t = key->keyMaterial[2*i];
        if ((t >= '0') && (t <= '9'))
        {
            j = (t - '0') << 4;
        }
        else if ((t >= 'a') && (t <= 'f'))
        {
            j = (t - 'a' + 10) << 4; 
        }
        else if ((t >= 'A') && (t <= 'F'))
        {
            j = (t - 'A' + 10) << 4; 
        }
        else
        {
            return (ITS_EINVALIDARGS);
        }
        
        t = key->keyMaterial[2*i+1];
        if ((t >= '0') && (t <= '9'))
        {
            j ^= (t - '0');
        }
        else if ((t >= 'a') && (t <= 'f'))
        {
            j ^= (t - 'a' + 10); 
        }
        else if ((t >= 'A') && (t <= 'F'))
        {
            j ^= (t - 'A' + 10); 
        }
        else
        {
            return (ITS_EINVALIDARGS);
        }
	
	k[i % 4][i / 4] = (ITS_OCTET) j; 
    }	
    
    rijndaelKeySched(k, key->keyLen, key->blockLen, key->keySched);
    
    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize an AES cipher structure
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
AES_CipherInit(ITS_BlockCipher *cipher, ITS_BlockMode mode, char *IV)
{
    int i, j, t;
    
    if ((mode == BLOCK_MODE_ECB) || (mode == BLOCK_MODE_CBC) ||
        (mode == BLOCK_MODE_CFB1))
    {
        cipher->mode = mode;
    }
    else
    {
        return (ITS_EINVALIDARGS);
    }
    
    if (IV != NULL)
    {
 	for(i = 0; i < cipher->blockLen/8; i++)
        {
            t = IV[2*i];
            if ((t >= '0') && (t <= '9'))
            {
                j = (t - '0') << 4;
            }
            else if ((t >= 'a') && (t <= 'f'))
            {
                j = (t - 'a' + 10) << 4; 
            }
            else if ((t >= 'A') && (t <= 'F'))
            {
                j = (t - 'A' + 10) << 4; 
            }
            else
            {
                return (ITS_EINVALIDARGS);
            }
    
            t = IV[2*i+1];
            if ((t >= '0') && (t <= '9'))
            {
                j ^= (t - '0');
            }
            else if ((t >= 'a') && (t <= 'f'))
            {
                j ^= (t - 'a' + 10); 
            }
            else if ((t >= 'A') && (t <= 'F'))
            {
                j ^= (t - 'A' + 10); 
            }
            else
            {
                return (ITS_EINVALIDARGS);
            }

            cipher->IV[i] = (ITS_OCTET)j;
	} 
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Encrypt a block using AES
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
AES_BlockEncrypt(ITS_BlockCipher *cipher, ITS_BlockKey *key,
                 ITS_OCTET *input, int inputLen,
                 ITS_OCTET *outBuffer)
{
    int i, j, t, numBlocks;
    ITS_OCTET block[4][MAXBC];

    /* check parameter consistency: */
    if (key == NULL ||
        key->direction != DIR_ENCRYPT ||
        (key->keyLen != 128 && key->keyLen != 192 && key->keyLen != 256))
    {
        return (ITS_EINVALIDARGS);
    }

    if (cipher == NULL ||
        (cipher->mode != BLOCK_MODE_ECB && cipher->mode != BLOCK_MODE_CBC &&
         cipher->mode != BLOCK_MODE_CFB1) ||
        (cipher->blockLen != 128 && cipher->blockLen != 192 &&
         cipher->blockLen != 256))
    {
        return (ITS_EINVALIDARGS);
    }


    numBlocks = inputLen/cipher->blockLen;
    
    switch (cipher->mode)
    {
    case BLOCK_MODE_ECB: 
        for (i = 0; i < numBlocks; i++)
        {
            for (j = 0; j < cipher->blockLen/32; j++)
            {
                for(t = 0; t < 4; t++)
                {
		            /* parse input stream into rectangular array */
                    block[t][j] = (ITS_OCTET)(input[4*j+t] & 0xFF);
                }
	    }

	    rijndaelEncrypt (block, key->keyLen, cipher->blockLen, key->keySched);

            for (j = 0; j < cipher->blockLen/32; j++)
            {
                /* parse rectangular array into output ciphertext bytes */
                for(t = 0; t < 4; t++)
                {
                    outBuffer[4*j+t] = (ITS_OCTET) block[t][j];
                }
            }
        }
        break;
	    
    case BLOCK_MODE_CBC:
        for (j = 0; j < cipher->blockLen/32; j++)
        {
            for(t = 0; t < 4; t++)
            {
                /* parse initial value into rectangular array */
                block[t][j] = (ITS_OCTET)(cipher->IV[t+4*j] & 0xFF);
            }
        }

        for (i = 0; i < numBlocks; i++)
        {
            for (j = 0; j < cipher->blockLen/32; j++)
            {
                for(t = 0; t < 4; t++)
                {
                    /* parse input stream into rectangular array and exor with 
                     * IV or the previous ciphertext */
                    block[t][j] ^= input[4*j+t] & 0xFF;
                }
            }

            rijndaelEncrypt(block, key->keyLen, cipher->blockLen, key->keySched);

            for (j = 0; j < cipher->blockLen/32; j++)
            {
                /* parse rectangular array into output ciphertext bytes */
                for (t = 0; t < 4; t++)
                {
                    outBuffer[4*j+t] = (ITS_OCTET) block[t][j];
                }
            }
	}
	break;
    
    default:
        return (ITS_EINVALIDARGS);
    }
    
    return (numBlocks * cipher->blockLen);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      do SHA transformation
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
AES_BlockDecrypt(ITS_BlockCipher *cipher, ITS_BlockKey *key,
                 ITS_OCTET *input, int inputLen,
                 ITS_OCTET *outBuffer)
{
    int i, j, t, numBlocks;
    ITS_OCTET block[4][MAXBC];

    if (cipher == NULL || key == NULL || key->direction == DIR_ENCRYPT ||
        cipher->blockLen != key->blockLen)
    {
        return (ITS_EINVALIDARGS);
    }

    /* check parameter consistency: */
    if (key == NULL ||
        key->direction != DIR_DECRYPT ||
        (key->keyLen != 128 && key->keyLen != 192 && key->keyLen != 256))
    {
        return (ITS_EINVALIDARGS);
    }

    if (cipher == NULL ||
        (cipher->mode != BLOCK_MODE_ECB && cipher->mode != BLOCK_MODE_CBC &&
         cipher->mode != BLOCK_MODE_CFB1) ||
        (cipher->blockLen != 128 && cipher->blockLen != 192 &&
         cipher->blockLen != 256))
    {
        return (ITS_EINVALIDARGS);
    }
    

    numBlocks = inputLen/cipher->blockLen;
    
    switch (cipher->mode)
    {
    case BLOCK_MODE_ECB: 
        for (i = 0; i < numBlocks; i++)
        {
            for (j = 0; j < cipher->blockLen/32; j++)
            {
                for(t = 0; t < 4; t++)
                {
                    /* parse input stream into rectangular array */
                    block[t][j] = (ITS_OCTET)(input[4*j+t] & 0xFF);
                }
            }

            rijndaelDecrypt (block, key->keyLen, cipher->blockLen, key->keySched);

            for (j = 0; j < cipher->blockLen/32; j++)
            {
                /* parse rectangular array into output ciphertext bytes */
                for(t = 0; t < 4; t++)
                {
                    outBuffer[4*j+t] = (ITS_OCTET) block[t][j];
                }
            }
        }
	break;
	    
    case BLOCK_MODE_CBC:
        /* first block */
        for (j = 0; j < cipher->blockLen/32; j++)
        {
            for(t = 0; t < 4; t++)
            {
               /* parse input stream into rectangular array */
                block[t][j] = (ITS_OCTET)(input[4*j+t] & 0xFF);
            }
        }

        rijndaelDecrypt(block, key->keyLen, cipher->blockLen, key->keySched);
    
        for (j = 0; j < cipher->blockLen/32; j++)
        {
            /* exor the IV and parse rectangular array into output ciphertext bytes */
            for(t = 0; t < 4; t++)
            {
                outBuffer[4*j+t] = (ITS_OCTET) (block[t][j] ^ cipher->IV[t+4*j]);
            }
        }
    
        /* next blocks */
        for (i = 1; i < numBlocks; i++)
        {
            for (j = 0; j < cipher->blockLen/32; j++)
            {
                for(t = 0; t < 4; t++)
                {
                    /* parse input stream into rectangular array */
                    block[t][j] = (ITS_OCTET)(input[cipher->blockLen/8+4*j+t] &
                                              0xFF);
                }
            }

            rijndaelDecrypt (block, key->keyLen, cipher->blockLen, key->keySched);
    
            for (j = 0; j < cipher->blockLen/32; j++)
            {
                /* exor previous ciphertext block and parse rectangular array 
	           into output ciphertext bytes */
                for(t = 0; t < 4; t++)
                {
                    outBuffer[cipher->blockLen/8+4*j+t] =
                        (ITS_OCTET) (block[t][j] ^ input[4*j+t-4*cipher->blockLen/32]);
                }
            }
        }
        break;
    
    default:
        return (ITS_EINVALIDARGS);
    }
    
    return (numBlocks * cipher->blockLen);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *	Encrypts/Decrypts exactly one full block a specified number of rounds.
 *	Only used in the Intermediate Value Known Answer Test.	
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
AES_CipherUpdateRounds(ITS_BlockCipher *cipher, ITS_BlockKey *key,
                       ITS_OCTET *input, int inputLen,
                       ITS_OCTET *outBuffer, int rounds)
{
    int j, t;
    ITS_OCTET block[4][MAXBC];

    if (cipher == NULL || key == NULL || cipher->blockLen != key->blockLen)
    {
        return (ITS_EINVALIDARGS);
    }

    for (j = 0; j < cipher->blockLen/32; j++)
    {
        for(t = 0; t < 4; t++)
        {
            /* parse input stream into rectangular array */
            block[t][j] = (ITS_OCTET)(input[4*j+t] & 0xFF);
        }
    }

    switch (key->direction)
    {
    case DIR_ENCRYPT:
        rijndaelEncryptRound(block, key->keyLen, cipher->blockLen, 
                             key->keySched, rounds);
        break;
	    
    case DIR_DECRYPT:
	rijndaelDecryptRound(block, key->keyLen, cipher->blockLen, 
                             key->keySched, rounds);
        break;
	    
    default:
        return (ITS_EINVALIDARGS);
    }

    for (j = 0; j < cipher->blockLen/32; j++)
    {
        /* parse rectangular array into output ciphertext bytes */
        for(t = 0; t < 4; t++)
        {
            outBuffer[4*j+t] = (ITS_OCTET) block[t][j];
        }
    }
    
    return (ITS_SUCCESS);
}
/*****************************************************************************/

/*
 * SHA f()-functions
 */
#define f1(x,y,z)   ((x & y) | (~x & z))
#define f2(x,y,z)   (x ^ y ^ z)
#define f3(x,y,z)   ((x & y) | (x & z) | (y & z))
#define f4(x,y,z)   (x ^ y ^ z)

/*
 * SHA constants
 */
#define CONST1      0x5a827999L
#define CONST2      0x6ed9eba1L
#define CONST3      0x8f1bbcdcL
#define CONST4      0xca62c1d6L

/*
 * 32-bit rotate
 */
#define ROT32(x,n)  ((x << n) | (x >> (32 - n)))

#define FUNC(n,i)                       \
    temp = ROT32(A,5) + f##n(B,C,D) + E + W[i] + CONST##n;  \
    E = D; D = C; C = ROT32(B,30); B = A; A = temp

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      do SHA transformation
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void 
sha_transform(ITS_SecHashInfo * sha_info)
{
    int i;
    ITS_UINT temp, A, B, C, D, E, W[80];

    for (i = 0; i < 16; ++i)
    {
        W[i] = sha_info->data[i];
    }
    for (i = 16; i < 80; ++i)
    {
        W[i] = W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16];
        W[i] = ROT32(W[i], 1);
    }

    A = sha_info->digest[0];
    B = sha_info->digest[1];
    C = sha_info->digest[2];
    D = sha_info->digest[3];
    E = sha_info->digest[4];

    FUNC(1, 0);
    FUNC(1, 1);
    FUNC(1, 2);
    FUNC(1, 3);
    FUNC(1, 4);
    FUNC(1, 5);
    FUNC(1, 6);
    FUNC(1, 7);
    FUNC(1, 8);
    FUNC(1, 9);
    FUNC(1, 10);
    FUNC(1, 11);
    FUNC(1, 12);
    FUNC(1, 13);
    FUNC(1, 14);
    FUNC(1, 15);
    FUNC(1, 16);
    FUNC(1, 17);
    FUNC(1, 18);
    FUNC(1, 19);

    FUNC(2, 20);
    FUNC(2, 21);
    FUNC(2, 22);
    FUNC(2, 23);
    FUNC(2, 24);
    FUNC(2, 25);
    FUNC(2, 26);
    FUNC(2, 27);
    FUNC(2, 28);
    FUNC(2, 29);
    FUNC(2, 30);
    FUNC(2, 31);
    FUNC(2, 32);
    FUNC(2, 33);
    FUNC(2, 34);
    FUNC(2, 35);
    FUNC(2, 36);
    FUNC(2, 37);
    FUNC(2, 38);
    FUNC(2, 39);

    FUNC(3, 40);
    FUNC(3, 41);
    FUNC(3, 42);
    FUNC(3, 43);
    FUNC(3, 44);
    FUNC(3, 45);
    FUNC(3, 46);
    FUNC(3, 47);
    FUNC(3, 48);
    FUNC(3, 49);
    FUNC(3, 50);
    FUNC(3, 51);
    FUNC(3, 52);
    FUNC(3, 53);
    FUNC(3, 54);
    FUNC(3, 55);
    FUNC(3, 56);
    FUNC(3, 57);
    FUNC(3, 58);
    FUNC(3, 59);

    FUNC(4, 60);
    FUNC(4, 61);
    FUNC(4, 62);
    FUNC(4, 63);
    FUNC(4, 64);
    FUNC(4, 65);
    FUNC(4, 66);
    FUNC(4, 67);
    FUNC(4, 68);
    FUNC(4, 69);
    FUNC(4, 70);
    FUNC(4, 71);
    FUNC(4, 72);
    FUNC(4, 73);
    FUNC(4, 74);
    FUNC(4, 75);
    FUNC(4, 76);
    FUNC(4, 77);
    FUNC(4, 78);
    FUNC(4, 79);

    sha_info->digest[0] += A;
    sha_info->digest[1] += B;
    sha_info->digest[2] += C;
    sha_info->digest[3] += D;
    sha_info->digest[4] += E;
}

#if __BYTE_ORDER == __LITTLE_ENDIAN

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      change endianness of data
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void 
byte_reverse(ITS_UINT *buffer, int count)
{
    int i;
    ITS_OCTET ct[4], *cp;

    count /= sizeof(ITS_UINT);
    cp = (ITS_OCTET *) buffer;

    for (i = 0; i < count; ++i)
    {
        ct[0] = cp[0];
        ct[1] = cp[1];
        ct[2] = cp[2];
        ct[3] = cp[3];
        cp[0] = ct[3];
        cp[1] = ct[2];
        cp[2] = ct[1];
        cp[3] = ct[0];
        cp += sizeof(ITS_UINT);
    }
}

#endif

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      initialize the SHA digest
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
SECHASH_Init(ITS_SecHashInfo * sha_info)
{
    ITS_C_REQUIRE(sha_info != NULL);

    sha_info->digest[0] = 0x67452301L;
    sha_info->digest[1] = 0xefcdab89L;
    sha_info->digest[2] = 0x98badcfeL;
    sha_info->digest[3] = 0x10325476L;
    sha_info->digest[4] = 0xc3d2e1f0L;

    sha_info->count_lo = 0L;
    sha_info->count_hi = 0L;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      update the SHA digest
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
SECHASH_Update(ITS_SecHashInfo * sha_info, ITS_OCTET * buffer, ITS_UINT count)
{
    ITS_C_REQUIRE(sha_info != NULL);
    ITS_C_REQUIRE(buffer != NULL || count == 0);

    if ((sha_info->count_lo + ((ITS_UINT) count << 3)) < sha_info->count_lo)
    {
        ++sha_info->count_hi;
    }

    sha_info->count_lo += (ITS_UINT) count << 3;
    sha_info->count_hi += (ITS_UINT) count >> 29;

    while (count >= ITS_SHASH_BLOCKSIZE)
    {
        memcpy(sha_info->data, buffer, ITS_SHASH_BLOCKSIZE);

#if __BYTE_ORDER == __LITTLE_ENDIAN
        byte_reverse(sha_info->data, ITS_SHASH_BLOCKSIZE);
#endif

        sha_transform(sha_info);
        buffer += ITS_SHASH_BLOCKSIZE;
        count -= ITS_SHASH_BLOCKSIZE;
    }

    memcpy(sha_info->data, buffer, count);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      finish computing the SHA digest
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void 
SECHASH_Final(ITS_SecHashInfo * sha_info)
{
    int count;
    ITS_UINT lo_bit_count, hi_bit_count;

    ITS_C_REQUIRE(sha_info != NULL);

    lo_bit_count = sha_info->count_lo;
    hi_bit_count = sha_info->count_hi;
    count = (int) ((lo_bit_count >> 3) & 0x3f);
    ((ITS_OCTET *) sha_info->data)[count++] = 0x80;

    if (count > 56)
    {
        memset((ITS_OCTET *) & sha_info->data + count, 0, 64 - count);

#if __BYTE_ORDER == __LITTLE_ENDIAN
        byte_reverse(sha_info->data, ITS_SHASH_BLOCKSIZE);
#endif

        sha_transform(sha_info);
        memset(&sha_info->data, 0, 56);
    }
    else
    {
        memset((ITS_OCTET *) & sha_info->data + count, 0, 56 - count);
    }

#if __BYTE_ORDER == __LITTLE_ENDIAN
    byte_reverse(sha_info->data, ITS_SHASH_BLOCKSIZE);
#endif

    sha_info->data[14] = hi_bit_count;
    sha_info->data[15] = lo_bit_count;
    sha_transform(sha_info);

#if __BYTE_ORDER == __LITTLE_ENDIAN
    byte_reverse(sha_info->digest, ITS_SHASH_DIGESTSIZE);
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      secure hash a message
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
HMAC_Hash(ITS_OCTET *text, ITS_UINT textLen,
          ITS_OCTET *key, ITS_UINT keyLen,
          ITS_OCTET *digest, ITS_UINT digestLen)
{
    ITS_SecHashInfo info;
    ITS_OCTET   ipad[ITS_SHASH_BLOCKSIZE+1];
    ITS_OCTET   opad[ITS_SHASH_BLOCKSIZE+1];
    ITS_OCTET   tk[ITS_SHASH_DIGESTSIZE];
    ITS_OCTET   td[ITS_SHASH_DIGESTSIZE];
    int i;

    if (keyLen > ITS_SHASH_BLOCKSIZE)
    {
        SECHASH_Init(&info);
        SECHASH_Update(&info, key, keyLen);
        SECHASH_Final(&info);

        memcpy(tk, info.digest, ITS_SHASH_DIGESTSIZE);
        key = tk;
        keyLen = ITS_SHASH_DIGESTSIZE;
    }

    /*
     * initialize the inner and outer vectors
     */
    memset(ipad, 0, sizeof(ipad));
    memset(opad, 0, sizeof(opad));
    memcpy(ipad, key, keyLen);
    memcpy(opad, key, keyLen);

    for (i = 0; i < ITS_SHASH_BLOCKSIZE; i++)
    {
        ipad[i] ^= 0x36;
        opad[i] ^= 0x5c;
    }

    /*
     * compute H(K XOR opad, H(K XOR IPAD, text))
     */
    SECHASH_Init(&info);
    SECHASH_Update(&info, ipad, ITS_SHASH_BLOCKSIZE);
    SECHASH_Update(&info, text, textLen);
    SECHASH_Final(&info);
    memcpy(td, info.digest, ITS_SHASH_DIGESTSIZE);

    SECHASH_Init(&info);
    SECHASH_Update(&info, opad, ITS_SHASH_BLOCKSIZE);
    SECHASH_Update(&info, td, ITS_SHASH_DIGESTSIZE);
    SECHASH_Final(&info);
    memcpy(digest, info.digest,
           (digestLen > ITS_SHASH_DIGESTSIZE)
                ? ITS_SHASH_DIGESTSIZE
                : digestLen);
}
