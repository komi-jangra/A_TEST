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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:15  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/16 19:08:31  mmiers
 * LOG: Warning removal, Borland update.
 * LOG:
 * LOG: Revision 7.1  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.2  2002/12/05 15:59:51  omayor
 * LOG: Add modification to CRC32C according to RFC 3309.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2002/02/13 22:22:57  mmiers
 * LOG: Commented code had bugs.
 * LOG:
 * LOG: Revision 5.3  2002/01/18 22:31:23  mmiers
 * LOG: A couple of warnings pointed out by the sun compiler.
 * LOG:
 * LOG: Revision 5.2  2002/01/15 23:04:57  mmiers
 * LOG: Add CRC32C.  Update M2PA as far as I can without SCTP support.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:10  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/07/03 21:16:22  mmiers
 * LOG: Move RM and DSM.
 * LOG:
 * LOG: Revision 4.2  2001/07/03 20:32:49  mmiers
 * LOG: Add CRC-32
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.10  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.9  2001/03/06 02:50:16  mmiers
 * LOG: Fixups for DLLs, make
 * LOG:
 * LOG: Revision 3.8  2001/03/05 23:54:56  mmiers
 * LOG: Prep for dynamic linking.
 * LOG:
 * LOG: Revision 3.7  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.6  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:55:49  mmiers
 * LOG: A few typos.
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.2  2000/10/03 21:17:09  mmiers
 * LOG: Today's installment.  Getting real close now.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:22  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/08/09 01:13:44  mmiers
 * LOG: Platform corrections.
 * LOG:
 * LOG: Revision 2.1  2000/05/22 17:00:24  mmiers
 * LOG:
 * LOG:
 * LOG: Add Adler32 generation
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_chksum.h>
#include <its_assertion.h>

#ident "$Id: its_chksum.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Compute the checksum of an IP header.
 *
 *  Input Parameters:
 *      buf - header buffer
 *      size - header size
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      updated checksum value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
IP_Chksum16(ITS_OCTET *buf, ITS_UINT size)
{
    ITS_USHORT *psh;
    ITS_UINT sum, i;

    ITS_C_REQUIRE(buf != NULL || size == 0);

    sum = 0;
    psh = (ITS_USHORT *)buf;

    if (size & 1)
    {
        buf[size] = 0;
        size++;
    }

    size >>= 1;

    for (i = 0; i < size; i++)
    {
        sum += *psh;
        psh++;
    }

    sum = (sum >> 16) + (sum & 0x0000FFFFU);
    sum += (sum >> 16);

    return ((ITS_USHORT)(~sum & 0x0000FFFFU));
}

/*
 * largest prime smaller than 65536
 */
#define BASE 65521

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Update a running Adler-32 checksum with the bytes buf[0..len-1]
 *      and return the updated checksum. The Adler-32 checksum should be
 *      initialized to 1.
 *
 *  Input Parameters:
 *      adler - the last computed chksum
 *      buf - new data to compute running chksum for
 *      len - length of new data buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      updated checksum value
 *
 *  Notes:
 *      Use something like:
 *
 *      unsigned long adler = 1L;
 *
 *      while (read_buffer(buffer, length) != EOF)
 *      {
 *          adler = update_adler32(adler, buffer, length);
 *      }
 *
 *      if (adler != original_adler)
 *      {
 *          error();
 *      }
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
ADLER_UpdateChksum32(ITS_UINT adler, ITS_OCTET *buf, ITS_UINT len)
{
    ITS_UINT s1 = adler & 0xffff;
    ITS_UINT s2 = (adler >> 16) & 0xffff;
    ITS_UINT n;

    for (n = 0; n < len; n++)
    {
        s1 = (s1 + buf[n]) % BASE;
        s2 = (s2 + s1)     % BASE;
    }

    return (s2 << 16) + s1;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return the CRC32 of the bytes buf[0..len-1]
 *
 *  Input Parameters:
 *      buf - new data to compute running chksum for
 *      len - length of new data buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      checksum value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
ADLER_Chksum32(ITS_OCTET *buf, ITS_UINT len)
{
    ITS_C_REQUIRE(buf != NULL || len == 0);

    return ADLER_UpdateChksum32(1, buf, len);
}

static unsigned int crc32_tab[] =
{
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
    0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
    0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
    0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
    0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
    0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
    0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
    0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
    0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
    0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
    0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
    0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
    0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
    0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
    0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
    0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
    0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
    0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
    0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
    0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
    0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
    0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
    0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
    0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
    0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
    0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
    0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
    0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
    0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
    0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
    0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
    0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
    0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
    0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
    0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
    0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
    0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
    0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
    0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
    0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
    0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
    0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
    0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
    0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
    0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
    0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
    0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
    0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
    0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
    0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
    0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
    0x2d02ef8dL
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return the CRC-32 of the bytes buf[0..len-1]
 *
 *  Input Parameters:
 *      buf - new data to compute chksum for
 *      len - length of new data buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      checksum value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
CRC_Chksum32(const ITS_OCTET *buf, ITS_UINT len)
{
    ITS_UINT i;
    ITS_UINT crc32val = 0;

    for (i = 0;  i < len;  i ++)
    {
        crc32val = crc32_tab[(crc32val ^ buf[i]) & 0xff] ^ (crc32val >> 8);
    }

    return (crc32val);
}

/*
 * How to build the CRC tables
 * Example of table build routine
 */
#if defined(GENERATE_TABLES)

#define OUTPUT_FILE   "crc32cr.h"
#define CRC32C_POLY    0x1EDC6F41L
#define CRC_TYPE                                                            \
    "/* Castagnoli93                                                  */\n" \
    "/* x^32+x^28+x^27+x^26+x^25+x^23+x^22+x^20+x^19+x^18+x^14+x^13+  */\n" \
    "/* x^11+x^10+x^9+x^8+x^6+x^0                                     */\n" \
    "/* Guy Castagnoli Stefan Braeuer and Martin Herrman              */\n" \
    "/* 'Optimization of Cyclic Redundancy-Check Codes                */\n" \
    "/* with 24 and 32 Parity Bits',                                  */\n" \
    "/* IEEE Transactions on Communications, Vol.41, No.6, June 1993  */\n"

FILE *tf;

ITS_UINT
reflect_32(ITS_UINT b)
{
    int i;
    ITS_UINT rw = 0L;

    for (i = 0; i < 32; i++)
    {
        if (b & 1)
        {
            rw |= 1 << (31 - i);
        }

        b >>= 1;
    }

    return(rw);
}

ITS_UINT
build_crc_table (int index)
{
    int i;
    ITS_UINT rb;

    rb = reflect_32(index);

    for (i = 0; i < 8; i++)
    {
        if (rb & 0x80000000L)
        {
            rb = (rb << 1) ^ CRC32C_POLY;
        }
        else
        {
            rb <<= 1;
        }
    }

    return (reflect_32 (rb));
}

int
main(int argc, char **argv)
{
    int i;

    printf("\nGenerating CRC-32c table file <%s>\n", OUTPUT_FILE);
    if ((tf = fopen(OUTPUT_FILE, "w")) == NULL)
    {
        printf("Unable to open %s\n", OUTPUT_FILE);
        exit(1);
    }

    /* fprintf(tf, "#ifndef __crc32cr_table_h__\n"); */
    /* fprintf(tf, "#define __crc32cr_table_h__\n\n"); */
    fprintf(tf, "#define CRC32C_POLY   0x%08lX\n", CRC32C_POLY);
    fprintf(tf, "#define CRC32C(c,d)   (c = (c >> 8) ^ crc_c[(c ^ (d)) & 0xFF])\n");
    fprintf(tf, "/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */\n");
    fprintf(tf, "/* Copyright 2001, D. Otis.  Use this program, code or tables    */\n");
    fprintf(tf, "/* extracted from it, as desired without restriction.            */\n");
    fprintf(tf, "/*                                                               */\n");
    fprintf(tf, "/* 32 Bit Reflected CRC table generation for SCTP.               */\n");
    fprintf(tf, "/* To accommodate serial byte data being shifted out least       */\n");
    fprintf(tf, "/* significant bit first, the table's 32 bit words are reflected */\n");
    fprintf(tf, "/* which flips both byte and bit MS and LS positions.  The CRC   */\n");
    fprintf(tf, "/* is calculated MS bits first from the perspective of the serial*/\n");
    fprintf(tf, "/* stream.  The x^32 term is implied and the x^0 term may also   */\n");
    fprintf(tf, "/* be shown as +1.  The polynomial code used is 0x%08lX.      */\n%s",
            CRC32C_POLY, CRC_TYPE);
    fprintf(tf, "/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */\n");

    fprintf(tf, "\nITS_UINT  crc_c[256] =\n{\n");

    for (i = 0; i < 256; i++)
    {
        fprintf(tf, "0x%08lXL, ", build_crc_table (i));
        if ((i & 3) == 3)
        {
            fprintf (tf, "\n");
        }
    }

    fprintf (tf, "};\n\n#endif\n");

    if (fclose (tf) != 0)
    {
        printf ("Unable to close <%s>." OUTPUT_FILE);
    }
    else
    {
        printf("\nThe CRC-32c table has been written to <%s>.\n",
               OUTPUT_FILE);
    }

    return (0);
}

#endif /* defined(GENERATE_TABLES) */

#define CRC32C_POLY     0x1EDC6F41
#define CRC32C(c,d)     (c = (c >> 8) ^ crc_c[(c ^ (d)) & 0xFF])

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* Copyright 2001, D. Otis.  Use this program, code or tables    */
/* extracted from it, as desired without restriction.            */
/*                                                               */
/* 32 Bit Reflected CRC table generation for SCTP.               */
/* To accommodate serial byte data being shifted out least       */
/* significant bit first, the table's 32 bit words are reflected */
/* which flips both byte and bit MS and LS positions.  The CRC   */
/* is calculated MS bits first from the perspective of the serial*/
/* stream.  The x^32 term is implied and the x^0 term may also   */
/* be shown as +1.  The polynomial code used is 0x1EDC6F41.      */
/* Castagnoli93                                                  */
/* x^32+x^28+x^27+x^26+x^25+x^23+x^22+x^20+x^19+x^18+x^14+x^13+  */
/* x^11+x^10+x^9+x^8+x^6+x^0                                     */
/* Guy Castagnoli Stefan Braeuer and Martin Herrman              */
/* "Optimization of Cyclic Redundancy-Check Codes                */
/* with 24 and 32 Parity Bits",                                  */
/* IEEE Transactions on Communications, Vol.41, No.6, June 1993  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

ITS_UINT crc_c[256] =
{
    0x00000000L, 0xF26B8303L, 0xE13B70F7L, 0x1350F3F4L,
    0xC79A971FL, 0x35F1141CL, 0x26A1E7E8L, 0xD4CA64EBL,
    0x8AD958CFL, 0x78B2DBCCL, 0x6BE22838L, 0x9989AB3BL,
    0x4D43CFD0L, 0xBF284CD3L, 0xAC78BF27L, 0x5E133C24L,
    0x105EC76FL, 0xE235446CL, 0xF165B798L, 0x030E349BL,
    0xD7C45070L, 0x25AFD373L, 0x36FF2087L, 0xC494A384L,
    0x9A879FA0L, 0x68EC1CA3L, 0x7BBCEF57L, 0x89D76C54L,
    0x5D1D08BFL, 0xAF768BBCL, 0xBC267848L, 0x4E4DFB4BL,
    0x20BD8EDEL, 0xD2D60DDDL, 0xC186FE29L, 0x33ED7D2AL,
    0xE72719C1L, 0x154C9AC2L, 0x061C6936L, 0xF477EA35L,
    0xAA64D611L, 0x580F5512L, 0x4B5FA6E6L, 0xB93425E5L,
    0x6DFE410EL, 0x9F95C20DL, 0x8CC531F9L, 0x7EAEB2FAL,
    0x30E349B1L, 0xC288CAB2L, 0xD1D83946L, 0x23B3BA45L,
    0xF779DEAEL, 0x05125DADL, 0x1642AE59L, 0xE4292D5AL,
    0xBA3A117EL, 0x4851927DL, 0x5B016189L, 0xA96AE28AL,
    0x7DA08661L, 0x8FCB0562L, 0x9C9BF696L, 0x6EF07595L,
    0x417B1DBCL, 0xB3109EBFL, 0xA0406D4BL, 0x522BEE48L,
    0x86E18AA3L, 0x748A09A0L, 0x67DAFA54L, 0x95B17957L,
    0xCBA24573L, 0x39C9C670L, 0x2A993584L, 0xD8F2B687L,
    0x0C38D26CL, 0xFE53516FL, 0xED03A29BL, 0x1F682198L,
    0x5125DAD3L, 0xA34E59D0L, 0xB01EAA24L, 0x42752927L,
    0x96BF4DCCL, 0x64D4CECFL, 0x77843D3BL, 0x85EFBE38L,
    0xDBFC821CL, 0x2997011FL, 0x3AC7F2EBL, 0xC8AC71E8L,
    0x1C661503L, 0xEE0D9600L, 0xFD5D65F4L, 0x0F36E6F7L,
    0x61C69362L, 0x93AD1061L, 0x80FDE395L, 0x72966096L,
    0xA65C047DL, 0x5437877EL, 0x4767748AL, 0xB50CF789L,
    0xEB1FCBADL, 0x197448AEL, 0x0A24BB5AL, 0xF84F3859L,
    0x2C855CB2L, 0xDEEEDFB1L, 0xCDBE2C45L, 0x3FD5AF46L,
    0x7198540DL, 0x83F3D70EL, 0x90A324FAL, 0x62C8A7F9L,
    0xB602C312L, 0x44694011L, 0x5739B3E5L, 0xA55230E6L,
    0xFB410CC2L, 0x092A8FC1L, 0x1A7A7C35L, 0xE811FF36L,
    0x3CDB9BDDL, 0xCEB018DEL, 0xDDE0EB2AL, 0x2F8B6829L,
    0x82F63B78L, 0x709DB87BL, 0x63CD4B8FL, 0x91A6C88CL,
    0x456CAC67L, 0xB7072F64L, 0xA457DC90L, 0x563C5F93L,
    0x082F63B7L, 0xFA44E0B4L, 0xE9141340L, 0x1B7F9043L,
    0xCFB5F4A8L, 0x3DDE77ABL, 0x2E8E845FL, 0xDCE5075CL,
    0x92A8FC17L, 0x60C37F14L, 0x73938CE0L, 0x81F80FE3L,
    0x55326B08L, 0xA759E80BL, 0xB4091BFFL, 0x466298FCL,
    0x1871A4D8L, 0xEA1A27DBL, 0xF94AD42FL, 0x0B21572CL,
    0xDFEB33C7L, 0x2D80B0C4L, 0x3ED04330L, 0xCCBBC033L,
    0xA24BB5A6L, 0x502036A5L, 0x4370C551L, 0xB11B4652L,
    0x65D122B9L, 0x97BAA1BAL, 0x84EA524EL, 0x7681D14DL,
    0x2892ED69L, 0xDAF96E6AL, 0xC9A99D9EL, 0x3BC21E9DL,
    0xEF087A76L, 0x1D63F975L, 0x0E330A81L, 0xFC588982L,
    0xB21572C9L, 0x407EF1CAL, 0x532E023EL, 0xA145813DL,
    0x758FE5D6L, 0x87E466D5L, 0x94B49521L, 0x66DF1622L,
    0x38CC2A06L, 0xCAA7A905L, 0xD9F75AF1L, 0x2B9CD9F2L,
    0xFF56BD19L, 0x0D3D3E1AL, 0x1E6DCDEEL, 0xEC064EEDL,
    0xC38D26C4L, 0x31E6A5C7L, 0x22B65633L, 0xD0DDD530L,
    0x0417B1DBL, 0xF67C32D8L, 0xE52CC12CL, 0x1747422FL,
    0x49547E0BL, 0xBB3FFD08L, 0xA86F0EFCL, 0x5A048DFFL,
    0x8ECEE914L, 0x7CA56A17L, 0x6FF599E3L, 0x9D9E1AE0L,
    0xD3D3E1ABL, 0x21B862A8L, 0x32E8915CL, 0xC083125FL,
    0x144976B4L, 0xE622F5B7L, 0xF5720643L, 0x07198540L,
    0x590AB964L, 0xAB613A67L, 0xB831C993L, 0x4A5A4A90L,
    0x9E902E7BL, 0x6CFBAD78L, 0x7FAB5E8CL, 0x8DC0DD8FL,
    0xE330A81AL, 0x115B2B19L, 0x020BD8EDL, 0xF0605BEEL,
    0x24AA3F05L, 0xD6C1BC06L, 0xC5914FF2L, 0x37FACCF1L,
    0x69E9F0D5L, 0x9B8273D6L, 0x88D28022L, 0x7AB90321L,
    0xAE7367CAL, 0x5C18E4C9L, 0x4F48173DL, 0xBD23943EL,
    0xF36E6F75L, 0x0105EC76L, 0x12551F82L, 0xE03E9C81L,
    0x34F4F86AL, 0xC69F7B69L, 0xD5CF889DL, 0x27A40B9EL,
    0x79B737BAL, 0x8BDCB4B9L, 0x988C474DL, 0x6AE7C44EL,
    0xBE2DA0A5L, 0x4C4623A6L, 0x5F16D052L, 0xAD7D5351L,
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return the CRC32C of the bytes buf[0..len-1]
 *
 *  Input Parameters:
 *      buf - new data to compute running chksum for
 *      len - length of new data buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      checksum value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
CRC_Chksum32C(const ITS_OCTET *buffer, ITS_UINT length)
{
    ITS_UINT i;
    ITS_UINT crc32 = ~0;
    ITS_UINT result;
    ITS_OCTET byte0, byte1, byte2, byte3;

    for (i = 0; i < length; i++)
    {
        CRC32C(crc32, buffer[i]);
    }

    result = ~crc32;
 
    /*  result  now holds the negated polynomial remainder;
     *  since the table and algorithm is "reflected" [williams95].
     *  That is,  result has the same value as if we mapped the message
     *  to a polynomial, computed the host-bit-order polynomial
     *  remainder, performed final negation, then did an end-for-end
     *  bit-reversal.
     *  Note that a 32-bit bit-reversal is identical to four inplace
     *  8-bit reversals followed by an end-for-end byteswap.
     *  In other words, the bytes of each bit are in the right order,
     *  but the bytes have been byteswapped.  So we now do an explicit
     *  byteswap.  On a little-endian machine, this byteswap and
     *  the final ntohl cancel out and could be elided.
     */
 
 
    byte0 = (ITS_OCTET)(result & 0xffU);
    byte1 = (ITS_OCTET)((result>>8U) & 0xffU);
    byte2 = (ITS_OCTET)((result>>16U) & 0xffU);
    byte3 = (ITS_OCTET)((result>>24U) & 0xffU);

    crc32 = ((byte0 << 24U) |
             (byte1 << 16U) |
             (byte2 << 8U)  |
              byte3);

    /* and insert it into the message */
    return(crc32);
}
