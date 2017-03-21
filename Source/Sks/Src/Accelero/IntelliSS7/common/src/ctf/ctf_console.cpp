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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:14  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:03  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.3  2005/05/06 09:38:03  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1731) Fix.
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:35:45  mmanikandan
 * LOG: Validation Bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:06  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:08  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.7  2005/03/01 11:28:43  mmanikandan
 * LOG: Printing ANSI CODEC changes.
 * LOG:
 * LOG: Revision 1.1.2.6  2005/02/24 11:59:33  mmanikandan
 * LOG: Validation Bug fixing.
 * LOG:
 * LOG: Revision 1.1.2.5  2005/02/01 06:16:32  mmanikandan
 * LOG: Compiler Warnings are removed.
 * LOG:
 * LOG: Revision 1.1.2.4  2005/01/31 11:29:08  mmanikandan
 * LOG: Windows compilation errors are resolved.
 * LOG:
 * LOG: Revision 1.1.2.3  2005/01/28 11:56:27  mmanikandan
 * LOG: Codec Integration and combining real time/offline mode.
 * LOG:
 * LOG: Revision 1.1.2.2  2005/01/17 12:11:09  mmanikandan
 * LOG: Filter option is added and hybrid stack support.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/01/04 13:10:25  mmanikandan
 * LOG: CTF Initial commit.
 * LOG:
 *
 ****************************************************************************/
#include <math.h>
#include <sys/stat.h>
#include <iostream>

#if defined(WIN32)

//
//  Template getlinefixed.
//
//  The VC++ getline template has a bug: it reads one extra character at the
//  end. This is a copy of that macro with the bug fixed.
//
//  See file [ ...\DevStudio\VC\include\STRING ] for original version.
//

namespace std {

template<class _E, class _TYPE, class _A> inline
	basic_istream<_E, _TYPE>& getlinefixed(basic_istream<_E, _TYPE>& _I,
		basic_string<_E, _TYPE, _A>& _X, const _E _D)
	{ios_base::iostate _St = ios_base::goodbit;
	bool _Chg = false;
	_X.erase();
	const basic_istream<_E, _TYPE>::sentry _Ok(_I, true);
	if (_Ok)
		{_TRY_IO_BEGIN
		_TYPE::int_type _C = _I.rdbuf()->sgetc();
		for (; ; _C = _I.rdbuf()->snextc())
			if (_TYPE::eq_int_type(_TYPE::eof(), _C))
				{_St |= ios_base::eofbit;
				break; }
			else if (_TYPE::eq(_C, _D))
				{_Chg = true;
                _I.rdbuf()->sbumpc();   // Bug was here: used to call snextc(). 
				break; }
			else if (_X.max_size() <= _X.size())
				{_St |= ios_base::failbit;
				break; }
			else
				_X += _TYPE::to_char_type(_C), _Chg = true;
		_CATCH_IO_(_I); }
	if (!_Chg)
		_St |= ios_base::failbit;
	_I.setstate(_St);
	return (_I); }

}   // Namespace std.

#endif // defined(WIN32)

#include <its++.h>
#include <engine++.h>
#include <its_pprint.h>
#include <its_dsm.h>
#include <its_sockets.h>



#if defined (WIN32)
#define CTFDLLAPI __declspec(dllexport)
#else
#define CTFDLLAPI
#endif

#define EVT_TRACE  ".itsEvent"

extern ITS_INT ParseFilterFile (char* filtFile);
extern void ClearFilterList();

FILE* fpbin = NULL;
FILE* fpInput = NULL;
FILE* fpOutput = NULL;
FILE* fpFilter = NULL;

char inputFile[255];
char filterFile[255];
char outputFile[255];
char tempBuf[255];
char command[255];
std::string realCodec_ = "";
std::string offCodec_ = "";
ITS_BOOLEAN isRealCodec_ = ITS_FALSE;
ITS_BOOLEAN isOffCodec_ = ITS_FALSE;

ITS_BOOLEAN isFilter = ITS_FALSE;
/*
 * ring buffer
 */
RINGBUF_Manager *buffer = NULL;
RINGBUF_Manager *buffer_stdout = NULL;
ITS_OCTET mtp3Bytes[1024];
ITS_USHORT mtp3Len;
int ieCount;

DLSYM_Manager* offmgr = NULL;
DLSYM_Manager* realmgr = NULL;

ITS_DLSYM offsym = NULL;
ITS_DLSYM realsym = NULL;

ITS_BOOLEAN stdoutDisplay = ITS_FALSE;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Resolve the codec library and returns the dlsym manager reference
 *
 *  Input Parameters:
 *      std::string codec - Application codec needs to be resolved. 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      DLSYM_Manager*
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

static DLSYM_Manager* GetCodecMgr (std::string codec)
{
    DLSYM_Manager* dm = NULL;

    if (codec == "INAP-CS2")
    {
        dm = DLSYM_Create("libINAPPrintD.so");
    }
    else if (codec == "MAP-V7")
    {
        dm = DLSYM_Create("libMAPPrintD.so");
    }
    else if (codec == "CAP-V4")
    {
        dm = DLSYM_Create("libCAMELPrintD.so");
    }
    else if (codec == "AIN-02")
    {
        dm = DLSYM_Create("libAIN-02PrintD.so");
    }
    else if (codec == "JSTD36")
    {
        dm = DLSYM_Create("libJSTD36PrintD.so");
    }
    else if (codec == "IS-41")
    {
        dm = DLSYM_Create("libIS-41PrintD.so");
    }
    else if (codec == "WIN")
    {
        dm = DLSYM_Create("libWINPrintD.so");
    }

    return dm; 
}

#undef CCITT
#undef ANSI
#define ANSI

#include <tcap_sn.h>

#undef CCITT
#undef ANSI
#define CCITT


#include <itu/mtp3.h>
#include <itu/sccp.h>
#include <itu/tcap.h>
#include <vframe.h>

extern ITS_BOOLEAN IsMTP3EventTobeFiltered (ITS_UINT opc, ITS_UINT dpc, ITS_UINT sio);
extern ITS_BOOLEAN IsSCCPEventTobeFiltered (ITS_OCTET family, SCCP_ADDR* clp, SCCP_ADDR* cdp);
extern ITS_BOOLEAN IsTCAPEventTobeFiltered (ITS_OCTET nat, ITS_OCTET opfam, ITS_USHORT op);

static ITS_SCCP_IE ies[32];

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Returns the operation code for the given ccitt tcap message stream.
 *
 *  Input Parameters:
 *      ITS_OCTET* tmp - Tcap encoded bytes.
 *      ITS_UINT tmpLen - Length of tcap encoded bytes.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      NONE
 *
 *  Return Value:
 *      Operation code.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

extern "C" ITS_INT 
GetCCITTOpCode(ITS_OCTET* tmp, ITS_UINT tmpLen)
{
    ITS_INT op = 0;

    ITS_OCTET *tp, *dp, *cp, *pdu;
    ITS_UINT clen = 0, cTag = 0;

    int ret = TCAP_FindParts_CCITT(tmp, tmpLen, &tp, &dp, &cp); 

    if (ret != PC_PARSE_OK)
        return op;

    if (cp && *cp == CSEQ_IDENT)
    {
        pdu = cp;
        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, tmp + tmpLen, ITS_TRUE);

        pdu += TCAP_GetTag(pdu, &cTag, tmp + tmpLen);
        pdu += TCAP_GetLength(pdu, &clen, tmp + tmpLen, ITS_TRUE);

        TCAP_CPT cpt;

        ret = TCAP_CvtDataToCPT_CCITT(&cpt, pdu, cTag, clen); 

        if (ret != ITS_SUCCESS)
            return op;


        switch (cpt.ptype)
        {
            case TCAP_PT_TC_INVOKE_CCITT:
            { 
                int oplen = cpt.u.invoke.operation.len;
                if (oplen >= 3)
                {
                    op = cpt.u.invoke.operation.data[2];
                    for (int i = 3; i < oplen; i++)
                        op = (op << 8) | cpt.u.invoke.operation.data[i];
                }
                break;
            }
            case TCAP_PT_TC_RESULT_L_CCITT:
            { 
                int oplen = cpt.u.result.operation.len;
                if (oplen >= 3)
                {
                    op = cpt.u.result.operation.data[2];
                    for (int i = 3; i < oplen; i++)
                        op = (op << 8) | cpt.u.result.operation.data[i];
                }
                break;
            }
        }
    }

    return op;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the decoded TCAP message in the given ring buffer.
 *
 *  Input Parameters:
 *      RINGBUF_Manager *ringBuf - The ring buffer where the output to write
 *      ITS_OCTET *bytes - Encoded CCITT Tcap message bytes.
 *      ITS_USHORT len - Length of the encoded message.
 *      ITS_USHORT src - The source encoded the bytes stream.
 *      ITS_CHAR* appbuffer - Character buffer to write before the 
 *                            decoded info in the ring buffer
 *      ITS_DLSYM sym - PPrint symbol for the codec library.
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

extern "C" void 
PrintCCITT_TCAP(RINGBUF_Manager *ringBuf, ITS_OCTET *bytes, ITS_USHORT len, 
                ITS_USHORT src, ITS_CHAR* appbuffer, ITS_DLSYM sym)
{
    ITS_UINT byteCount = 1;
    ITS_OCTET* tmp = NULL;
    ITS_UINT tmpLen = 0;
    ITS_OCTET mType;

    if (src == ITS_SCCP_CCITT_SRC)
    {
        ITS_OCTET tmpChar = bytes[7];
        bytes[7] = bytes[0];
        SCCP_DecodeMTP3_CCITT(&bytes[7], len - 7, &mType, ies, &ieCount,
            &SCCP_UDT_Desc_CCITT);
        bytes[7] = tmpChar;
    }
    else if (src == ITS_SCCP_ANSI_SRC)
    {
        ITS_OCTET tmpChar = bytes[10];
        bytes[10] = bytes[0];
        SCCP_DecodeMTP3_ANSI(&bytes[10], len - 10, &mType, ies, &ieCount,
            &SCCP_UDT_Desc_ANSI);
        bytes[10] = tmpChar;
    }
    else
    {
        tmp = bytes;
        tmpLen = len;
    }

    if (!tmp)
    {
        for (int i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_DATA)
            {
                tmp = ies[i].param_data.userData.data;
                tmpLen = ies[i].param_length;
            }
        }
    }
    
    if (tmp)
    {
        int op = 0;
         
        op = GetCCITTOpCode(tmp, tmpLen);

        if (!isFilter || IsTCAPEventTobeFiltered(0,0, op))
        {
            if (appbuffer)
            { 
                if (fpOutput)
                {
                    fprintf(fpOutput,"%s",appbuffer);
                }
                else
                {
                    printf("%s",appbuffer);
                }
            }
            PPrint(ringBuf, "%CT", &byteCount, tmp, tmpLen, sym);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the decoded SCCP message in the given ring buffer.
 *
 *  Input Parameters:
 *      RINGBUF_Manager *ringBuf - The ring buffer where the output to write
 *      ITS_OCTET *bytes - Encoded CCITT SCCP message bytes.
 *      ITS_USHORT len - Length of the encoded message.
 *      ITS_USHORT src - The source encoded the bytes stream.
 *      ITS_CHAR* appbuffer - Character buffer to write before the
 *                            decoded info in the ring buffer
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

extern "C" void 
PrintCCITT_SCCP(RINGBUF_Manager *ringBuf, ITS_OCTET *bytes, ITS_USHORT len, 
                ITS_USHORT src, ITS_CHAR* appbuffer)
{
    ITS_EVENT ev;
    ITS_UINT byteCount = 1;
    ITS_OCTET mType;
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET data[MTP3_MAX_SIF_LENGTH];
    ITS_USHORT mlen;

    if (src == ITS_MTP3_ANSI_SRC)
    {
        MTP3_HEADER_ANSI hdr3;
        ev.data = bytes;
        ev.len = len;
        if (MTP3_Decode_ANSI(&ev, &mType, &hdr3, data, &mlen) == ITS_SUCCESS)
        {
            if (mType == MTP3_MSG_USER_DATA)
            {
                ev.data = data;
                ev.len = mlen;
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else if (src == ITS_MTP3_CCITT_SRC)
    {
        MTP3_HEADER_CCITT hdr3;
        ev.data = bytes;
        ev.len = len;
        if (MTP3_Decode_CCITT(&ev, &mType, &hdr3, data, &mlen) == ITS_SUCCESS)
        {
            if (mType == MTP3_MSG_USER_DATA)
            {
                ev.data = data;
                ev.len = mlen;
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        ev.data = bytes + 7;
        ev.data[0] = bytes[0];
        ev.len = len - 7;
    }

    
    switch (ev.data[0])
    {
    case SCCP_MSG_CR:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_CR_Desc_CCITT);
        break;
        
    case SCCP_MSG_CC:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_CC_Desc_CCITT);
        break;
        
    case SCCP_MSG_CREF:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_CREF_Desc_CCITT);
        break;
        
    case SCCP_MSG_RLSD:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_RLSD_Desc_CCITT);
        break;
        
    case SCCP_MSG_RLC:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_RLC_Desc_CCITT);
        break;
        
    case SCCP_MSG_DT1:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_DT1_Desc_CCITT);
        break;
        
    case SCCP_MSG_DT2:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_DT2_Desc_CCITT);
        break;
        
    case SCCP_MSG_AK:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_AK_Desc_CCITT);
        break;
        
    case SCCP_MSG_UDT:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_UDT_Desc_CCITT);
        break;
        
    case SCCP_MSG_XUDT:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_XUDT_Desc_CCITT);
        break;
        
    case SCCP_MSG_UDTS:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_UDTS_Desc_CCITT);
        break;
        
    case SCCP_MSG_XUDTS:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_XUDTS_Desc_CCITT);
        break;
        
    case SCCP_MSG_ED:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_ED_Desc_CCITT);
        break;
        
    case SCCP_MSG_EA:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_EA_Desc_CCITT);
        break;
        
    case SCCP_MSG_RSR:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_RSR_Desc_CCITT);
        break;
        
    case SCCP_MSG_RSC:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_RSC_Desc_CCITT);
        break;
        
    case SCCP_MSG_ERR:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_ERR_Desc_CCITT);
        break;
        
    case SCCP_MSG_IT:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_IT_Desc_CCITT);
        break;
        
    case SCCP_MSG_LUDT:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_LUDT_Desc_CCITT);
        break;
        
    case SCCP_MSG_LUDTS:
        ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_LUDTS_Desc_CCITT);
        break;
        
    case SCCP_MSG_NOTICE:
    default:
        ret = ITS_ENOTFOUND;
        break;
    }

    SCCP_ADDR *cdp = NULL, *clp = NULL;

    for (int i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            clp = &ies[i].param_data.callingPartyAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &ies[i].param_data.calledPartyAddr;
        }
    }

    if (!isFilter || IsSCCPEventTobeFiltered(1, clp, cdp))
    {
        if (appbuffer)
        {
            if (fpOutput)
            {
                fprintf(fpOutput,"%s",appbuffer);
            }
            else
            {
                printf("%s",appbuffer);
            }
        } 

        PPrint(ringBuf, "%CS", &byteCount, mType, ies, ieCount, ITS_FALSE);
    }

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the decoded MTP3 message in the given ring buffer.
 *
 *  Input Parameters:
 *      RINGBUF_Manager *ringBuf - The ring buffer where the output to write
 *      ITS_OCTET *bytes - Encoded MTP3 Tcap message bytes.
 *      ITS_USHORT len - Length of the encoded message.
 *      ITS_USHORT src - The source encoded the bytes stream.
 *      ITS_CHAR* appbuffer - Character buffer to write before the
 *                            decoded info in the ring buffer
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   06-04-2005    Bug ID : 1671     MTP3Len is initialized to avoid 
 *                                             junk data printing
 *  Mani   05-05-2005    Bug ID : 1731
 * 
 ****************************************************************************/

extern "C" void
PrintCCITT_MTP3(RINGBUF_Manager *ringBuf, ITS_OCTET *bytes, ITS_USHORT len, 
                ITS_USHORT src, ITS_CHAR* appbuffer)
{
    MTP3_HEADER_CCITT* mtp3;
    ITS_UINT byteCount = 1;
    ITS_OCTET sio = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET* temp = NULL;
    ITS_INT mtp3Len = 0;
    
    if (len < 3) return;

    if (!isFilter)
    {
        PPrint(ringBuf,"-------------- MTP2 ----------------\n");
        switch(bytes[0])
        {
        case L2_L3_IN_SERVICE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 IN Service\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_REMOTE_PROCESSOR_OUT:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Remote Processor Out\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_OUT_OF_SERVICE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 OUT Of Service\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_REMOTE_PROCESSOR_REC:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Remote Processor Recover\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_DATA:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Data\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_BSNT:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Backward Sequence Number Transmitted (BSNT)\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_BSNT_NOT_RETRIEVABLE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Backward Sequence Number Transmitted (BSNT) Not Retrievable\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RETRIEVED_MSG:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Retrieved Message\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RETRIEVAL_COMPLETE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Retrieval Complete\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RETRIEVAL_NOT_POSSIBLE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Retrieval Not Possible\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RB_CLEARED:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Retrieval Buffer Cleared\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RTB_CLEARED:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 ReTransmission Buffer Cleared\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_CONGESTION_ONSET:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Congestion OnSet\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_CONGESTION_ABATES:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Congestion Abates\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_START:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Start\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_STOP:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Stop\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_RESUME:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Resume\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_CLEAR_BUFFERS:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Clear Buffers\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_CLEAR_RTB:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Clear ReTransmission Buffer\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_EMERGENCY:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Emergency\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_EMERGENCY_CEASE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Emergency Cease\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_DATA:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Data\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_RETRIEVE_BSNT:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Retrieve Backward Sequence Number Transmitted (BSNT)\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_RETRIEVE_MSGS:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Retrieve Messages\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_FLOW_CONTROL_START:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Flow Control Start\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_FLOW_CONTROL_STOP:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Flow Control Stop\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_LOCAL_PROCESSOR_OUT:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Local Processor Out\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_LOCAL_PROCESSOR_REC:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Local Processor Recovered\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        default:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - Unknown\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        }
    
        byteCount++;
        
        PPrint(ringBuf," %3d.  %02x   %08b  LinkSet = %d\n",
            byteCount, bytes[1], bytes[1], bytes[1]);
        
        byteCount++;
        
        PPrint(ringBuf," %3d.  %02x   %08b  LinkCode = %d\n\n",
            byteCount, bytes[2], bytes[2], bytes[2]);
        
        byteCount++;
    }

    if (len == 3) return;


    if ((src == ITS_SCCP_CCITT_SRC) || (src == ITS_SCCP_ANSI_SRC))
    {
        mtp3 = (MTP3_HEADER_CCITT *)&bytes[4];
    }
    else
    {
        mtp3 = (MTP3_HEADER_CCITT *)&bytes[3];
    }

    sio = MTP3_HDR_GET_SIO(*mtp3);

    MTP3_POINT_CODE_CCITT dpc, opc;
    MTP3_RL_GET_DPC_CCITT(mtp3->label,dpc);
    MTP3_RL_GET_OPC_CCITT(mtp3->label,opc);

    if (!isFilter || IsMTP3EventTobeFiltered(MTP3_PC_GET_VALUE_CCITT(opc), 
        MTP3_PC_GET_VALUE_CCITT(dpc), sio))
    {
        if (appbuffer)
        {
            if (fpOutput)
            {
                fprintf(fpOutput,"%s",appbuffer);
            }
            else
            {
                printf("%s",appbuffer);
            }
        }
        PPrint(ringBuf, "%CN", &byteCount, mtp3);
    }
    else
    {
        return;
    }

    if ((src == ITS_SCCP_CCITT_SRC) || (src == ITS_SCCP_ANSI_SRC))
    {
        temp = (ITS_OCTET *)&bytes[sizeof(MTP3_HEADER_CCITT) + 4];
    }
    else
    {
        temp = (ITS_OCTET *)&bytes[sizeof(MTP3_HEADER_CCITT) + 3];
    }

    switch (sio & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    {
        PPrint(ringBuf," %3d.  %02x   %08b  SNMM Message\n", 
                byteCount, sio, sio);
        byteCount++;

        switch(*temp)
        {
        case 0x11:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Change Over Order\n", 
                byteCount, *temp, *temp);
            break;
        case 0x12:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Emergency Change Over Order\n", 
                byteCount, *temp, *temp);
            break;
        case 0x13:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Signalling Route Set Congestion Test\n", 
                byteCount, *temp, *temp);
            break;
        case 0x14:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Transfer Prohibited\n", 
                byteCount, *temp, *temp);
            break;
        case 0x15:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Signalling Route Set Test\n", 
                byteCount, *temp, *temp);
            break;
        case 0x16:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Link Inhibit\n", 
                byteCount, *temp, *temp);
            break;
        case 0x17:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Traffic Restart Allowed\n", 
                byteCount, *temp, *temp);
            break;
        case 0x18:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Signalling Data Link Connection Order\n", 
                byteCount, *temp, *temp);
            break;
        case 0x1A:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : User Part Unavailable\n", 
                byteCount, *temp, *temp);
            break;
        case 0x21:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Change Over Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x22:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Emergency Change Over Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x23:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Transfer Controlled\n", 
                byteCount, *temp, *temp);
            break;
        case 0x25:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Signalling Route Set Test Restricted National\n", 
                byteCount, *temp, *temp);
            break;
        case 0x26:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LUN) Link Uninhibited\n", 
                byteCount, *temp, *temp);
            break;
        case 0x28:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CSS) Connection Successful\n", 
                byteCount, *temp, *temp);
            break;
        case 0x31:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (XCO) Extended Change Over Order\n", 
                byteCount, *temp, *temp);
            break;
        case 0x34:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (TFR) Transfer Restricted\n", 
                byteCount, *temp, *temp);
            break;
        case 0x36:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LIA) Link inhibit Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x38:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CNS) Connection Not Successful\n", 
                byteCount, *temp, *temp);
            break;
        case 0x41:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (XCA) Extended Change Over Order Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x46:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LUA) Link Uninhibit Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x48:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CNP) Connection Not Possible\n", 
                byteCount, *temp, *temp);
            break;
        case 0x51:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CBD) Change Back Declaration\n", 
                byteCount, *temp, *temp);
            break;
        case 0x54:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (TFA) Transfer Allowed\n", 
                byteCount, *temp, *temp);
            break;
        case 0x56:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LID) Link Inhibit Denied\n", 
                byteCount, *temp, *temp);
            break;
        case 0x61:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CBA) Change Back Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x66:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LFU) Link Forced Uninhibit\n", 
                byteCount, *temp, *temp);
            break;
        case 0x76:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LLT) Link Local Inhibit Test\n", 
                byteCount, *temp, *temp);
            break;
        case 0x86:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LLT) Link Remote Inhibit Test\n", 
                byteCount, *temp, *temp);
            break;
        }
        break;
    }
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    {
        if (*temp == 0x11)
        {
            PPrint(ringBuf," %3d.  %02x   %08b  Message Type : SLTM\n", 
               byteCount, sio, sio);
        }
        else if (*temp == 0x21)
        {
            PPrint(ringBuf," %3d.  %02x   %08b  Message Type : SLTA\n", 
               byteCount, sio, sio);
        }

        temp++;
        byteCount++;

        int len = ((*temp) & 0xf0) >> 4;
        PPrint(ringBuf," %3d.  %02x   %08b  Test Data Length - %d\n", 
               byteCount, *temp, *temp, len);
        byteCount++;
        
        for (int i = 0; i < len; i++)
        {
            temp++;

            PPrint(ringBuf," %3d.  %02x   %08b  Test Data [%d] = %d\n", 
               byteCount, *temp, *temp, i, *temp);
            byteCount++;
        }

        break;
    }
    default:
    {
        PPrint(ringBuf," %3d.  %02x   %08b  Message Type - Applicaton Message\n", 
               byteCount, sio, sio);
        byteCount++;

        int tmpLen = len - (sizeof(MTP3_HEADER) + sizeof(ITS_OCTET) + 2);

        PPrint(ringBuf," %3d.               Applicaton Message Length : %d\n", 
               byteCount, sio, sio);
        byteCount++;

        for (int i = 0; i < tmpLen; i++)
        {
            PPrint(ringBuf," %3d.  %02x   %08b  Applicaton Data [%d] = %d\n", 
               byteCount, *temp, *temp, i, *temp);
            temp++;
            byteCount++;
        }
    }
    }
}

#undef CCITT
#undef ANSI
#define ANSI

#include <ansi/mtp3.h>
#include <ansi/sccp.h>
#include <ansi/tcap.h>
#include <vframe.h>

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Returns the operation code for the given ansi tcap message stream.
 *
 *  Input Parameters:
 *      ITS_OCTET* tmp - Tcap encoded bytes.
 *      ITS_UINT tmpLen - Length of tcap encoded bytes.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_OCTET* nat - National indicator 
 *      ITS_OCTET* opfam - operation family
 *
 *  Return Value:
 *      Operation code.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

extern "C" ITS_INT
GetANSIOpCode(ITS_OCTET* tmp, ITS_UINT tmpLen, ITS_OCTET* nat, ITS_OCTET* opfam)
{
    ITS_INT op = 0;

    ITS_OCTET *tp, *dp, *cp, *pdu;
    ITS_UINT clen = 0, cTag = 0;;

    int ret = TCAP_FindParts_ANSI(tmp, tmpLen, &tp, &dp, &cp);

    if (ret != ITS_SUCCESS)
        return op;

    if (cp && *cp == CSEQ_IDENT)
    {
        pdu = cp;
        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, tmp + tmpLen, ITS_TRUE);

        pdu += TCAP_GetTag(pdu, &cTag, tmp + tmpLen);
        pdu += TCAP_GetLength(pdu, &clen, tmp + tmpLen, ITS_TRUE);

        TCAP_CPT cpt;

        ret = TCAP_CvtDataToCPT_ANSI(&cpt, pdu, cTag, clen);

        if (ret != ITS_SUCCESS)
            return op;

        switch (cpt.ptype)
        {
            case TCAP_PT_TC_INVOKE_ANSI:
            {
                if (cpt.u.invoke.operation.len >= 3)
                {
                    *nat = (cpt.u.invoke.operation.data[0] == TCPPN_OCI_NATIONAL_TCAP)?1:0;
                    *opfam = cpt.u.invoke.operation.data[2];
                    op = cpt.u.invoke.operation.data[3];
                }
                break;
            }
        }
    }
    return op;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the decoded TCAP message in the given ring buffer.
 *
 *  Input Parameters:
 *      RINGBUF_Manager *ringBuf - The ring buffer where the output to write
 *      ITS_OCTET *bytes - Encoded ANSI Tcap message bytes.
 *      ITS_USHORT len - Length of the encoded message.
 *      ITS_USHORT src - The source encoded the bytes stream.
 *      ITS_CHAR* appbuffer - Character buffer to write before the
 *                            decoded info in the ring buffer
 *      ITS_DLSYM sym - PPrint symbol for the codec library.
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

extern "C" void 
PrintANSI_TCAP(RINGBUF_Manager *ringBuf, ITS_OCTET *bytes, ITS_USHORT len, 
               ITS_USHORT src, ITS_CHAR* appbuffer, ITS_DLSYM sym)
{
    ITS_UINT byteCount = 1;
    ITS_OCTET* tmp = NULL;
    ITS_UINT tmpLen = 0;
    ITS_OCTET mType;

    if (src == ITS_SCCP_CCITT_SRC)
    {
        ITS_OCTET tmpChar = bytes[7];
        bytes[7] = bytes[0];
        SCCP_DecodeMTP3_CCITT(&bytes[7], len - 7, &mType, ies, &ieCount,
            &SCCP_UDT_Desc_CCITT);
        bytes[7] = tmpChar;
    }
    else if (src == ITS_SCCP_ANSI_SRC)
    {
        ITS_OCTET tmpChar = bytes[10];
        bytes[10] = bytes[0];
        SCCP_DecodeMTP3_ANSI(&bytes[10], len - 10, &mType, ies, &ieCount,
            &SCCP_UDT_Desc_ANSI);
        bytes[10] = tmpChar;
    }
    else
    {
        tmp = bytes;
        tmpLen = len;
    }

    if (!tmp)
    {
        for (int i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_DATA)
            {
                tmp = ies[i].param_data.userData.data;
                tmpLen = ies[i].param_length;
            }
        }
    }

    if (tmp)
    {
        int op = 0;
        ITS_OCTET nat = 0;
        ITS_OCTET opfam = 0;

        if (isFilter)
             op = GetANSIOpCode(tmp, tmpLen, &nat, &opfam);

        if (!isFilter || IsTCAPEventTobeFiltered(nat, opfam, op))
        {
            if (appbuffer)
            {
                if (fpOutput)
                {
                    fprintf(fpOutput,"%s",appbuffer);
                }
                else
                {
                    printf("%s",appbuffer);
                }
            }
            PPrint(ringBuf, "%AT", &byteCount, tmp, tmpLen, sym);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the decoded SCCP message in the given ring buffer.
 *
 *  Input Parameters:
 *      RINGBUF_Manager *ringBuf - The ring buffer where the output to write
 *      ITS_OCTET *bytes - Encoded ANSI SCCP message bytes.
 *      ITS_USHORT len - Length of the encoded message.
 *      ITS_USHORT src - The source encoded the bytes stream.
 *      ITS_CHAR* appbuffer - Character buffer to write before the
 *                            decoded info in the ring buffer
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

extern "C" void 
PrintANSI_SCCP(RINGBUF_Manager *ringBuf, ITS_OCTET *bytes, ITS_USHORT len, 
               ITS_USHORT src, ITS_CHAR* appbuffer)
{
    ITS_EVENT ev;
    ITS_UINT byteCount = 1;
    ITS_OCTET mType;
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET data[MTP3_MAX_SIF_LENGTH];
    ITS_USHORT mlen;

    
    if (src == ITS_MTP3_ANSI_SRC)
    {
        MTP3_HEADER_ANSI hdr3;
        ev.data = bytes;
        ev.len = len;
        if (MTP3_Decode_ANSI(&ev, &mType, &hdr3, data, &mlen) == ITS_SUCCESS)
        {
            if (mType == MTP3_MSG_USER_DATA)
            {
                ev.data = data;
                ev.len = mlen;
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else if (src == ITS_MTP3_CCITT_SRC)
    {
        MTP3_HEADER_CCITT hdr3;
        ev.data = bytes;
        ev.len = len;
        if (MTP3_Decode_CCITT(&ev, &mType, &hdr3, data, &mlen) == ITS_SUCCESS)
        {
            if (mType == MTP3_MSG_USER_DATA)
            {
                ev.data = data;
                ev.len = mlen;
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        ev.data = bytes + 10;
        ev.len = len - 10;
        ev.data[0] = bytes[0];
    }
    

    switch (ev.data[0])
    {
    case SCCP_MSG_CR:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_CR_Desc_ANSI);
        break;
        
    case SCCP_MSG_CC:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_CC_Desc_ANSI);
        break;
        
    case SCCP_MSG_CREF:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_CREF_Desc_ANSI);
        break;
        
    case SCCP_MSG_RLSD:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_RLSD_Desc_ANSI);
        break;
        
    case SCCP_MSG_RLC:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_RLC_Desc_ANSI);
        break;
        
    case SCCP_MSG_DT1:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_DT1_Desc_ANSI);
        break;
        
    case SCCP_MSG_DT2:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_DT2_Desc_ANSI);
        break;
        
    case SCCP_MSG_AK:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_AK_Desc_ANSI);
        break;
        
    case SCCP_MSG_UDT:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_UDT_Desc_ANSI);
        break;
        
    case SCCP_MSG_XUDT:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_XUDT_Desc_ANSI);
        break;
        
    case SCCP_MSG_UDTS:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_UDTS_Desc_ANSI);
        break;
        
    case SCCP_MSG_XUDTS:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_XUDTS_Desc_ANSI);
        break;
        
    case SCCP_MSG_ED:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_ED_Desc_ANSI);
        break;
        
    case SCCP_MSG_EA:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_EA_Desc_ANSI);
        break;
        
    case SCCP_MSG_RSR:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_RSR_Desc_ANSI);
        break;
        
    case SCCP_MSG_RSC:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_RSC_Desc_ANSI);
        break;
        
    case SCCP_MSG_ERR:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_ERR_Desc_ANSI);
        break;
        
    case SCCP_MSG_IT:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_IT_Desc_ANSI);
        break;
        
    case SCCP_MSG_LUDT:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_LUDT_Desc_ANSI);
        break;
        
    case SCCP_MSG_LUDTS:
        ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
            &mType, ies, &ieCount,
            &SCCP_LUDTS_Desc_ANSI);
        break;
        
    case SCCP_MSG_NOTICE:
    default:
        ret = ITS_ENOTFOUND;
        break;
    }

    SCCP_ADDR* clp = NULL;
    SCCP_ADDR* cdp = NULL;

    for (int i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            clp = &ies[i].param_data.callingPartyAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &ies[i].param_data.calledPartyAddr;
        }
    }

    if (!isFilter || IsSCCPEventTobeFiltered(2, clp, cdp))
    {
        if (appbuffer)
        {
            if (fpOutput)
            {
                fprintf(fpOutput,"%s",appbuffer);
            }
            else
            {
                printf("%s",appbuffer);
            }
        }
        PPrint(ringBuf, "%AS", &byteCount, mType, ies, ieCount, ITS_FALSE);
    } 
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the decoded MTP3 message in the given ring buffer.
 *
 *  Input Parameters:
 *      RINGBUF_Manager *ringBuf - The ring buffer where the output to write
 *      ITS_OCTET *bytes - Encoded ANSI MTP3 message bytes.
 *      ITS_USHORT len - Length of the encoded message.
 *      ITS_USHORT src - The source encoded the bytes stream.
 *      ITS_CHAR* appbuffer - Character buffer to write before the
 *                            decoded info in the ring buffer
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   06-04-2005    Bug ID : 1671     MTP3Len is initialized to avoid
 *                                             junk data printing
 *  Mani   05-05-2005    Bug ID : 1731
 *
 ****************************************************************************/

extern "C" void
PrintANSI_MTP3(RINGBUF_Manager *ringBuf, ITS_OCTET *bytes, ITS_USHORT len, 
               ITS_USHORT src, ITS_CHAR* appbuffer)
{
    MTP3_HEADER_ANSI* mtp3;
    ITS_UINT byteCount = 1;
    ITS_OCTET sio = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET* temp = NULL;
    ITS_INT mtp3Len = 0;
    
    if (len < 3) return;

    if (!isFilter)
    {
        PPrint(ringBuf,"-------------- MTP2 ----------------\n");
        switch(bytes[0])
        {
        case L2_L3_IN_SERVICE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 IN Service\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_REMOTE_PROCESSOR_OUT:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Remote Processor Out\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_OUT_OF_SERVICE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 OUT Of Service\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_REMOTE_PROCESSOR_REC:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Remote Processor Recover\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_DATA:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Data\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_BSNT:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Backward Sequence Number Transmitted (BSNT)\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_BSNT_NOT_RETRIEVABLE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Backward Sequence Number Transmitted (BSNT) Not Retrievable\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RETRIEVED_MSG:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Retrieved Message\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RETRIEVAL_COMPLETE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Retrieval Complete\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RETRIEVAL_NOT_POSSIBLE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Retrieval Not Possible\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RB_CLEARED:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Retrieval Buffer Cleared\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_RTB_CLEARED:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 ReTransmission Buffer Cleared\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_CONGESTION_ONSET:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Congestion OnSet\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L2_L3_CONGESTION_ABATES:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L2 L3 Congestion Abates\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_START:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Start\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_STOP:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Stop\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_RESUME:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Resume\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_CLEAR_BUFFERS:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Clear Buffers\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_CLEAR_RTB:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Clear ReTransmission Buffer\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_EMERGENCY:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Emergency\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_EMERGENCY_CEASE:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Emergency Cease\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_DATA:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Data\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_RETRIEVE_BSNT:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Retrieve Backward Sequence Number Transmitted (BSNT)\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_RETRIEVE_MSGS:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Retrieve Messages\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_FLOW_CONTROL_START:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Flow Control Start\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_FLOW_CONTROL_STOP:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Flow Control Stop\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_LOCAL_PROCESSOR_OUT:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Local Processor Out\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        case L3_L2_LOCAL_PROCESSOR_REC:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - L3 L2 Local Processor Recovered\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        default:
            {
                PPrint(ringBuf," %3d.  %02x   %08b  MTP2 Message - Unknown\n", 
                    byteCount, bytes[0], bytes[0]);
                break;
            }
        }
    
        byteCount++;
        
        PPrint(ringBuf," %3d.  %02x   %08b  LinkSet = %d\n",
            byteCount, bytes[1], bytes[1], bytes[1]);
        
        byteCount++;
        
        PPrint(ringBuf," %3d.  %02x   %08b  LinkCode = %d\n\n",
            byteCount, bytes[2], bytes[2], bytes[2]);
        
        byteCount++;
    }

    if (len == 3) return;


    if ((src == ITS_SCCP_CCITT_SRC) || (src == ITS_SCCP_ANSI_SRC))
    {
        mtp3 = (MTP3_HEADER_ANSI *)&bytes[4];
    }
    else
    {
        mtp3 = (MTP3_HEADER_ANSI *)&bytes[3];
    }

    sio = MTP3_HDR_GET_SIO(*mtp3);

    MTP3_POINT_CODE_ANSI dpc, opc;
    MTP3_RL_GET_DPC_ANSI(mtp3->label,dpc);
    MTP3_RL_GET_OPC_ANSI(mtp3->label,opc);

    if (!isFilter || IsMTP3EventTobeFiltered(MTP3_PC_GET_VALUE_ANSI(opc), 
        MTP3_PC_GET_VALUE_ANSI(dpc), sio))
    {
        if (appbuffer)
        {
            if (fpOutput)
            {
                fprintf(fpOutput,"%s",appbuffer);
            }
            else
            {
                printf("%s",appbuffer);
            }
        }
        PPrint(ringBuf, "%AN", &byteCount, mtp3);
    }
    else
    {
        return;
    }

    if ((src == ITS_SCCP_CCITT_SRC) || (src == ITS_SCCP_ANSI_SRC))
    {
        temp = (ITS_OCTET *)&bytes[sizeof(MTP3_HEADER_ANSI) + 4];
    }
    else
    {
        temp = (ITS_OCTET *)&bytes[sizeof(MTP3_HEADER_ANSI) + 3];
    }

    switch (sio & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    {
        PPrint(ringBuf," %3d.  %02x   %08b  SNMM Message\n", 
                byteCount, sio, sio);
        byteCount++;

        switch(*temp)
        {
        case 0x11:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Change Over Order\n", 
                byteCount, *temp, *temp);
            break;
        case 0x12:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Emergency Change Over Order\n", 
                byteCount, *temp, *temp);
            break;
        case 0x13:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Signalling Route Set Congestion Test\n", 
                byteCount, *temp, *temp);
            break;
        case 0x14:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Transfer Prohibited\n", 
                byteCount, *temp, *temp);
            break;
        case 0x15:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Signalling Route Set Test\n", 
                byteCount, *temp, *temp);
            break;
        case 0x16:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Link Inhibit\n", 
                byteCount, *temp, *temp);
            break;
        case 0x17:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Traffic Restart Allowed\n", 
                byteCount, *temp, *temp);
            break;
        case 0x18:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Signalling Data Link Connection Order\n", 
                byteCount, *temp, *temp);
            break;
        case 0x1A:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : User Part Unavailable\n", 
                byteCount, *temp, *temp);
            break;
        case 0x21:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Change Over Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x22:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Emergency Change Over Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x23:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Transfer Controlled\n", 
                byteCount, *temp, *temp);
            break;
        case 0x25:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : Signalling Route Set Test Restricted National\n", 
                byteCount, *temp, *temp);
            break;
        case 0x26:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LUN) Link Uninhibited\n", 
                byteCount, *temp, *temp);
            break;
        case 0x28:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CSS) Connection Successful\n", 
                byteCount, *temp, *temp);
            break;
        case 0x31:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (XCO) Extended Change Over Order\n", 
                byteCount, *temp, *temp);
            break;
        case 0x34:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (TFR) Transfer Restricted\n", 
                byteCount, *temp, *temp);
            break;
        case 0x36:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LIA) Link inhibit Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x38:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CNS) Connection Not Successful\n", 
                byteCount, *temp, *temp);
            break;
        case 0x41:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (XCA) Extended Change Over Order Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x46:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LUA) Link Uninhibit Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x48:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CNP) Connection Not Possible\n", 
                byteCount, *temp, *temp);
            break;
        case 0x51:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CBD) Change Back Declaration\n", 
                byteCount, *temp, *temp);
            break;
        case 0x54:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (TFA) Transfer Allowed\n", 
                byteCount, *temp, *temp);
            break;
        case 0x56:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LID) Link Inhibit Denied\n", 
                byteCount, *temp, *temp);
            break;
        case 0x61:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (CBA) Change Back Ack\n", 
                byteCount, *temp, *temp);
            break;
        case 0x66:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LFU) Link Forced Uninhibit\n", 
                byteCount, *temp, *temp);
            break;
        case 0x76:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LLT) Link Local Inhibit Test\n", 
                byteCount, *temp, *temp);
            break;
        case 0x86:
            PPrint(ringBuf," %3d.  %02x   %08b  MessageType : (LLT) Link Remote Inhibit Test\n", 
                byteCount, *temp, *temp);
            break;
        }
        break;
    }
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    {
        if (*temp == 0x11)
        {
            PPrint(ringBuf," %3d.  %02x   %08b  Message Type : SLTM\n", 
               byteCount, sio, sio);
        }
        else if (*temp == 0x21)
        {
            PPrint(ringBuf," %3d.  %02x   %08b  Message Type : SLTA\n", 
               byteCount, sio, sio);
        }

        temp++;
        byteCount++;

        int len = ((*temp) & 0xf0) >> 4;
        PPrint(ringBuf," %3d.  %02x   %08b  Test Data Length - %d\n", 
               byteCount, *temp, *temp, len);
        byteCount++;
        
        for (int i = 0; i < len; i++)
        {
            temp++;

            PPrint(ringBuf," %3d.  %02x   %08b  Test Data [%d] = %d\n", 
               byteCount, *temp, *temp, i, *temp);
            byteCount++;
        }

        break;
    }
    default:
    {
        PPrint(ringBuf," %3d.  %02x   %08b  Message Type - Applicaton Message\n", 
               byteCount, sio, sio);
        byteCount++;

        int tmpLen = len - (sizeof(MTP3_HEADER) + sizeof(ITS_OCTET) + 2);

        PPrint(ringBuf," %3d.               Applicaton Message Length : %d\n", 
               byteCount, sio, sio);
        byteCount++;

        for (int i = 0; i < tmpLen; i++)
        {
            PPrint(ringBuf," %3d.  %02x   %08b  Applicaton Data [%d] = %d\n", 
               byteCount, *temp, *temp, i, *temp);
            temp++;
            byteCount++;
        }
    }
    }

}

#undef CCITT
#undef ANSI

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Callback function for the ring buffer.
 *
 *  Input Parameters:
 *      RINGBUF_Manager *rb - reference to the ring buffer
 *      char *string - The character buffer to write
 *      ITS_UINT len - length of the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The bytes written.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

static int
WriteStdout(RINGBUF_Manager *rb, char *string, ITS_UINT len)
{
    if (fpOutput)
    {
        return fprintf(fpOutput,"%*.*s", (ITS_INT)len, (ITS_INT)len, string);
    }
    else
    {
        return printf("%*.*s", (ITS_INT)len, (ITS_INT)len, string);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Callback function for the ring buffer.
 *
 *  Input Parameters:
 *      RINGBUF_Manager *rb - reference to the ring buffer
 *      char *string - The character buffer to write
 *      ITS_UINT len - length of the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The bytes written.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

static int
WriteStdoutOnly(RINGBUF_Manager *rb, char *string, ITS_UINT len)
{
    return printf("%*.*s", (ITS_INT)len, (ITS_INT)len, string);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Returns the Source string for the given source value.
 *
 *  Input Parameters:
 *      ITS_USHORT src - Source value
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Source String
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

static std::string GetSource (ITS_USHORT src)
{
    std::string source = "";
    switch(src)
    {
    case ITS_TIMER_SRC:
        source = "TIMER";
        break;
    case ITS_TCAP_ANSI_SRC:
        source = "ANSI TCAP";
        break;
    case ITS_TCAP_CCITT_SRC:
        source = "CCITT TCAP";
        break;
    case ITS_SCCP_ANSI_SRC:
        source = "ANSI SCCP";
        break;
    case ITS_SCCP_CCITT_SRC:
        source = "CCITT SCCP";
        break;
    case ITS_ISUP_ANSI_SRC:
        source = "ANSI ISUP";
        break;
    case ITS_ISUP_CCITT_SRC:
        source = "CCITT ISUP";
        break;
    case ITS_MTP3_ANSI_SRC:
        source = "ANSI MTP3";
        break;
    case ITS_MTP3_CCITT_SRC:
        source = "CCITT MTP3";
        break;
    case ITS_MTP2_ANSI_SRC:
        source = "ANSI MTP2";
        break;
    case ITS_MTP2_CCITT_SRC:
        source = "CCITT MTP2";
        break;
    case ITS_TCAP_PRC_SRC:
        source = "PRC TCAP";
        break;
    case ITS_SCCP_PRC_SRC:
        source = "PRC SCCP";
        break;
    case ITS_ISUP_PRC_SRC:
        source = "PRC ISUP";
        break;
    case ITS_MTP3_PRC_SRC:
        source = "PRC MTP3";
        break;
    case ITS_MTP2_PRC_SRC:
        source = "PRC MTP2";
        break;
    default:
        source = "Application";
        break;
    }
    
    return source;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the decoded information
 *
 *  Input Parameters:
 *      ITS_OCTET* buf - The bytes to be decode and print.
 *      ITS_UINT buflen - Length of the bytes stream.
 *      ITS_CHAR* localPBuf - The application buffer to be print before 
 *                             decoded info
 *      ITS_BOOLEAN pData - Boolean to print the Data Portion.
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

static void PrintBuffer (ITS_OCTET* buf, ITS_UINT buflen, 
                         ITS_CHAR* localPBuf, ITS_BOOLEAN pData)
{
    ITS_USHORT src = 0;
    ITS_USHORT dest = 0;
    ITS_UINT output = 0;
    ITS_CHAR priBuf[4096];
    ITS_CHAR tmp[5];

    src = (buf[0] << 8) | buf[1];
    dest = (buf[2] << 8) | buf[3];
    output = (buf[4] << 24) | (buf[5] << 16) | (buf[6] << 8) | buf[7];
    
    memset(priBuf, 0, 4096);
    strcpy(priBuf, localPBuf);
    for (ITS_UINT i = 8; i < buflen; i++)
    {
        sprintf(tmp,"%02x ", buf[i]);
        strcat(priBuf, tmp);
        
        if (((i-7) % 16) == 0)
            strcat(priBuf,"\n");
    }

    char localBuf[512];
    sprintf(localBuf,"\n\nSource Layer      : %s\nDestination Layer : %s\n\n",
            (char*)GetSource(src).c_str(), (char*)GetSource(dest).c_str());
    strcat(priBuf, localBuf);

    if (pData)
    {
        if (!buffer)
        {
            
            if ((buffer = RINGBUF_InitManager(4096, 90, WriteStdout, NULL)) == NULL)
            {
                fprintf(stderr, "Can't create ring buffer\n");
                
                return ;
            }
        }

        switch(dest)
        {
        case ITS_TCAP_CCITT_SRC:
            PrintCCITT_TCAP (buffer, &buf[8], buflen-8, src, priBuf,offsym); 
            break;
        case ITS_TCAP_ANSI_SRC:
            PrintANSI_TCAP (buffer, &buf[8], buflen-8, src, priBuf, offsym);
            break;
        case ITS_SCCP_CCITT_SRC:
            PrintCCITT_SCCP(buffer, &buf[8],buflen - 8, src, priBuf);
            break;
        case ITS_SCCP_ANSI_SRC:
            PrintANSI_SCCP(buffer, &buf[8],buflen - 8, src, priBuf);
            break;
        case ITS_MTP3_CCITT_SRC:
            PrintCCITT_MTP3(buffer, &buf[8], buflen-8, src, priBuf);
            break;
        case ITS_MTP3_ANSI_SRC:
            PrintANSI_MTP3(buffer, &buf[8], buflen-8, src, priBuf);
            break;
        }

        RINGBUF_Flush(buffer);
    }
}

static ITS_BOOLEAN borderStart = ITS_TRUE;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Callback function for the real time mode. It receives data from 
 *      the transport and prints the information.
 *
 *  Input Parameters:
 *      TPOOL_THREAD* thr - The instance which is receiving data from 
 *                          the transport
 *      ITS_EVENT* event - The event received from the transport 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Executed status of the function. ITS_SUCCESS on successful execution. 
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

static
ITS_INT CTF_PostNextEvent (TPOOL_THREAD* thr, ITS_EVENT* event)
{
    if ((fpbin != NULL) && !borderStart)
    {
        char lenbuf[11];

        memset(lenbuf, 0, 11);

        time_t tt = time(NULL);
        struct tm *t = localtime(&tt);

        lenbuf[0] = t->tm_mon & 0xff;
        lenbuf[1] = t->tm_mday & 0xff;
        lenbuf[2] = (t->tm_year & 0xff00) >> 8;
        lenbuf[3] = t->tm_year & 0xff;
        lenbuf[4] = t->tm_hour & 0xff;
        lenbuf[5] = t->tm_min & 0xff;
        lenbuf[6] = t->tm_sec & 0xff;
     
        sprintf(tempBuf,"%d/%d/%d  %d:%d:%d",t->tm_mon + 1,
                t->tm_mday, t->tm_year + 1900,t->tm_hour, 
                t->tm_min, t->tm_sec);

        lenbuf[7] = (event->len & 0xff000000) >> 24;
        lenbuf[8] = (event->len & 0x00ff0000) >> 16;
        lenbuf[9] = (event->len & 0x0000ff00) >> 8;
        lenbuf[10] = (event->len & 0x000000ff);

        ITS_INT output = (event->data[4] << 24) | (event->data[5] << 16) | 
                 (event->data[6] << 8) | event->data[7];

        if (output & 0x0002)
        {
            fwrite (lenbuf, 11,1, fpbin);
            fflush(fpbin);
            fwrite (event->data, event->len, 1, fpbin);
            fflush(fpbin);
        }
        if (output & 0x0001)
        {
            printf("\n----------------------------------------------\n");
            std::cout << "\nTimeStamp : " << tempBuf << std::endl << std::endl;

            ITS_USHORT src = (event->data[0] << 8) | event->data[1];
            ITS_USHORT dest = (event->data[2] << 8) | event->data[3];

            for (int i = 8; i < event->len; i++)
            {
                printf("%02x ", event->data[i]);

                if (((i-7) % 16) == 0)
                    printf("\n");
            }
            printf ("\n\n");

            std::cout << "Source Layer      : " << GetSource(src) << std::endl
                      << "Destination Layer : " << GetSource(dest) << std::endl 
                      << std::endl;
            
            if (stdoutDisplay)
            {
                if (!buffer_stdout)
                {
                    /* create the ring buffer */
                    if ((buffer_stdout = RINGBUF_InitManager(4096, 90, 
                                         WriteStdoutOnly, NULL)) == NULL)
                    {
                        fprintf(stderr, "Can't create ring buffer\n");

                        return (EXIT_FAILURE);
                    }
                }

                switch(dest)
                {
                    case ITS_TCAP_CCITT_SRC:
                        PrintCCITT_TCAP (buffer_stdout, event->data + 8, event->len-8, 
                                         src, NULL,realsym);
                        break;
                    case ITS_TCAP_ANSI_SRC:
                        PrintANSI_TCAP (buffer_stdout, event->data + 8,
                                         event->len-8, src, NULL, realsym);
                        break;
                    case ITS_SCCP_CCITT_SRC:
                        PrintCCITT_SCCP(buffer_stdout, event->data + 8,
                                         event->len-8, src, NULL);
                        break;
                    case ITS_SCCP_ANSI_SRC:
                        PrintANSI_SCCP(buffer_stdout, event->data + 8,
                                         event->len-8, src, NULL);
                        break;
                    case ITS_MTP3_CCITT_SRC:
                        PrintCCITT_MTP3(buffer_stdout, event->data + 8,
                                         event->len-8, src, NULL);
                        break;
                    case ITS_MTP3_ANSI_SRC:
                        PrintANSI_MTP3(buffer_stdout, event->data + 8,
                                         event->len-8, src, NULL);
                        break;
                }

                RINGBUF_Flush(buffer_stdout);
            }
        }
    }

    return ITS_SUCCESS;
}

static ITS_CHAR ipaddress_[25];
static ITS_USHORT port_ = 0;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      It will start the transport for real time capturing.
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
 *      Status of Thread exit.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   06-04-2005    Bug ID : 1669     Failure message for ctf connection
 *                                             failed is added. 
 *
 ****************************************************************************/

extern "C" THREAD_RET_TYPE 
StartBorderTransport (void * arg)
{
    if (borderStart)
    {

        its::ClientSocket cs (INET_DOMAIN, ipaddress_, port_);

        if (!cs.Connect())
        {
            borderStart = ITS_FALSE;
            printf ("Connection to the client Success\n");
            time_t tt = time(NULL);
            struct tm *t = localtime(&tt);

            sprintf(tempBuf,"%s%s_%d_%d_%d",APPL_GetTraceDir(),
                    EVT_TRACE,t->tm_mon + 1,t->tm_mday,
                    t->tm_year + 1900);
            printf("File : %s\n",tempBuf);
            fpbin = fopen(tempBuf,"ab+");

            ITS_USHORT isrc = 0;
            ITS_USHORT ilen = 0;
            char buf[10];
            while (!borderStart)
            {
                isrc = 0; ilen = 0;
                memset (buf, 0, 10);

                if (cs.Read(buf, 7) != 7)
                {
                    borderStart = ITS_TRUE;
                    break;
                }
                
                if (memcmp(buf,"ISS7SSI",7) != 0)
                {
                    printf ("Client is not connected to IntelliNet CTF Server\n");
                    borderStart = ITS_TRUE;
                    break;
                }

                ITS_EVENT evt;

                if (cs.Read((char*)(&isrc), 2) != 2)
                {
                    borderStart = ITS_TRUE;
                    break;
                }
                evt.src = SOCK_NToHS(isrc);

                if (cs.Read((char*)(&ilen), 2) != 2)
                {
                    borderStart = ITS_TRUE;
                    break;
                }

                evt.len = SOCK_NToHS(ilen);

                evt.data = (ITS_OCTET *)ITS_Malloc(evt.len);

                if (cs.Read((char*)evt.data, evt.len) != evt.len)
                {
                    borderStart = ITS_TRUE;
                    break;
                }

                CTF_PostNextEvent (NULL, &evt);
                ITS_EVENT_TERM(&evt);
            }
        }
        else
        {
            printf ("Connection to the client %s : %d Failed\n",
                ipaddress_, port_);
        }
    }
    else
    {
        printf ("Already the CTF Console is running in Real time mode\n");
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      It will parse the command line arguments.
 *
 *  Input Parameters:
 *      ITS_INT argc - argument count
 *      ITS_CHAR argv[][255] - argument strings
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Status of parsing arguments. ITS_SUCCESS on successful parsing
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

ITS_INT 
ParseArguments(ITS_INT argc, ITS_CHAR argv[][255])
{
    fpInput = NULL;
    fpOutput = NULL;
    ITS_INT ret = ITS_SUCCESS;
    isFilter = ITS_FALSE;
    isOffCodec_ = ITS_FALSE; 

    ClearFilterList();

    if (argc > 1)
    {
        for (int i = 0; i < argc; )
        {
            if (argv[i][0] == '-')
            {
                switch(argv[i][1])
                {
                case 'i':
                    if (argv[i][2] != '\0')
                    {
                        strcpy(inputFile, &argv[i][2]);
                        fpInput = fopen(inputFile,"rb");
                        i++;
                    }
                    else if (((i+1) < argc) && (argv[i+1][0] != '-'))
                    {
                        strcpy(inputFile, argv[i+1]);
                        fpInput = fopen(inputFile,"rb");
                        i+=2;
                    }
                    else
                    {
                        ret = -1;
                    }
                    break;
                case 'o':
                    if (argv[i][2] != '\0')
                    {
                        strcpy(outputFile, &argv[i][2]);
                        fpOutput = fopen(outputFile,"w");
                        i++;
                    }
                    else if (((i+1) < argc) && (argv[i+1][0] != '-'))
                    {
                        strcpy(outputFile, argv[i+1]);
                        fpOutput = fopen(outputFile,"w");
                        i+=2;
                    }
                    else
                    {
                        ret = -1;
                    }
                    break;
                case 'f':
                    if (argv[i][2] != '\0')
                    {
                        strcpy(filterFile, &argv[i][2]);
                        ParseFilterFile(filterFile);
                        isFilter = ITS_TRUE;
                        i++;
                    }
                    else if (((i+1) < argc) && (argv[i+1][0] != '-'))
                    {
                        strcpy(filterFile, argv[i+1]);
                        ParseFilterFile(filterFile);
                        isFilter = ITS_TRUE;
                        i+=2;
                    }
                    else
                    {
                        ret = -1;
                    }
                    break;
                case 's':
                    if (argv[i][2] != '\0')
                    {
                        strcpy(ipaddress_, &argv[i][2]);
                        i++;
                    }
                    else if (((i+1) < argc) && (argv[i+1][0] != '-'))
                    {
                        strcpy(ipaddress_, argv[i+1]);
                        i+=2;
                    }
                    else
                    {
                        ret = -1;
                    }
                    break;
                case 'p':
                    if (argv[i][2] != '\0')
                    {
                        port_ = atoi(&argv[i][2]);
                        i++;
                    }
                    else if (((i+1) < argc) && (argv[i+1][0] != '-'))
                    {
                        port_ = atoi(argv[i+1]);
                        i+=2;
                    }
                    else
                    {
                        ret = -1;
                    }
                    break;
                case 'c':
                    if (argv[i][2] != '\0')
                    {
                        if (strcmp (command,"ctf_trace") == 0)
                        { 
                            offCodec_ = &argv[i][2];
                            isOffCodec_ = ITS_TRUE;
                        } 
                        else if (strcmp (command,"ctf_connect") == 0)
                        {
                            realCodec_ = &argv[i][2];
                            isRealCodec_ = ITS_TRUE;
                        }
                        i++;
                    }
                    else if (((i+1) < argc) && (argv[i+1][0] != '-'))
                    {
                        if (strcmp (command,"ctf_trace") == 0)
                        {
                            offCodec_ = argv[i+1];
                            isOffCodec_ = ITS_TRUE;
                            
                        } 
                        else if (strcmp (command,"ctf_connect") == 0)
                        {
                            realCodec_ = argv[i+1];
                            isRealCodec_ = ITS_TRUE;
                        }
                        i+=2;
                    }
                    else
                    {
                        ret = -1;
                    }

                    if (ret != -1)
                    {
                        if (isOffCodec_)
                        {
                            offmgr = GetCodecMgr(offCodec_);
                            if (offmgr)
                                offsym = DLSYM_Resolve (offmgr, "ParamPrint");
                        }
                        else if (isRealCodec_)
                        {
                            realmgr = GetCodecMgr(realCodec_);
                            if (realmgr)
                                realsym = DLSYM_Resolve (realmgr, "ParamPrint");
                        }
                    }

                    break;
                default:
                    ret = -1;
                    break;
                }
            }
            else
            {
                ret = -1;
            }

            if (ret != ITS_SUCCESS)
            {
                break;
            }
        }
    }
    else
    {
        ret = -1;
    }

    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the help for CTF Console.
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

void PrintHelp()
{
    printf("S.No  Command          Description\n");
    printf("~~~~  ~~~~~~~          ~~~~~~~~~~~\n\n");
    printf("1.    help             To display this menu\n");
    printf("2.    help <command>   To display the help for the command\n");
    printf("3.    ctf_connect      To start the real time capturing\n");
    printf("4.    ctf_disconnect   To stop the real time capturing\n");
    printf("5.    ctf_display      To enable/disable the expanded view of raw bytes in stdout\n");
    printf("6.    ctf_trace        To trace and dump the given input file to the output file\n");
    printf("7.    exit             To exit this tool\n\n");
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the help for the given command.
 *
 *  Input Parameters:
 *      char* str - The command for which the help required
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

void PrintCtfHelp(char* str)
{
    if (strstr(str,"ctf_trace") != NULL)
    {
        printf("\nSYNOPSIS\n");
        printf("\tctf_trace -i <input file> [-o <output file> -f <filter file> -c <codec>]\n");
        printf("\nDESCRIPTION\n");
        printf("\tTo trace and dump the given input file to the output file\n");
        printf("\tThe codec will be - \n");
        printf("\tINAP-CS2, MAP-V7, CAP-V4, AIN-02, JSTD36, IS-41, WIN \n");
        printf("\nEXAMPLE\n");
        printf("\t>> ctf_trace -i .itsEvent_1_28_2005 -o output -f testFilter -c INAP-CS2\n\n");
    }
    else if (strstr(str,"ctf_connect") != NULL)
    {
        printf("\nSYNOPSIS\n");
        printf("\tctf_connect -s <ip address> -p <port> [-c codec]\n");
        printf("\nDESCRIPTION\n");
        printf("\tTo start the real time capturing\n");
        printf("\tThe codec will be - \n");
        printf("\tINAP-CS2, MAP-V7, CAP-V4, AIN-02, JSTD36, IS-41, WIN \n");
        printf("\nEXAMPLE\n");
        printf("\t>> ctf_connect -s 172.16.1.35 -p 2450\n\n");
    }
    else if (strstr(str,"ctf_disconnect") != NULL)
    {
        printf("\nSYNOPSIS\n");
        printf("\tctf_disconnect\n");
        printf("\nDESCRIPTION\n");
        printf("\tTo stop the real time capturing\n");
        printf("\nEXAMPLE\n");
        printf("\t>> ctf_disconnect\n\n");
    }
    else if (strstr(str,"ctf_display") != NULL)
    {
        printf("\nSYNOPSIS\n");
        printf("\tctf_display <on/off>\n"); 
        printf("\nDESCRIPTION\n");
        printf("\tTo enable/disable the expanded view of packets\n");
        printf("\nEXAMPLE\n");
        printf("\t>> ctf_display on\n\n"); 
    }
    else if (strstr(str, "help") != NULL)
    {
        printf("\nSYNOPSIS\n");
        printf("\thelp\n");
        printf("\nDESCRIPTION\n");
        printf("\tTo display the help menu\n");
        printf("\nEXAMPLE\n");
        printf("\t>> help\n\n");
    }
    else if (strstr(str, "exit") != NULL)
    {
        printf("\nSYNOPSIS\n");
        printf("\texit\n");
        printf("\nDESCRIPTION\n");
        printf("\tTo exit the tool\n");
        printf("\nEXAMPLE\n");
        printf("\t>> exit\n\n");
    }
    else
    {
        printf("\nUnknown Command\n\n");
        PrintHelp();
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse the command written in the ctf console.
 *
 *  Input Parameters:
 *      char* cmd - The command needs to be parsed.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Command parsing status. ITS_SUCCESS on successfull parsing.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

ITS_INT ParseCommand(char* cmd)
{
    ITS_INT ret = -2;
    char* temp = cmd;
    command[0] = '\0';

    while(*temp)
    {
        if (strcmp(cmd,"exit") == 0)
        {
            strcpy(command,"exit");
            ret = 1;
            break;
        }
        else if (strstr(cmd,"help") != NULL)
        {
            temp += 4;
            while (*temp == ' ') 
                temp++;

            if (*temp == '\0')
                PrintHelp();
            else
                PrintCtfHelp(temp);

            ret = 2;
            break;
        }
        else if ((temp = strstr(cmd,"ctf_disconnect")) != NULL)
        {
            borderStart = ITS_TRUE;
            isRealCodec_ = ITS_FALSE;
            strcpy (command, "ctf_disconnect");

            if (realmgr)
            {
                DLSYM_Destroy (realmgr);
                realmgr = NULL;
                realsym = NULL;
            }        

            printf("\nctf_disconnect success\n");
            ret = ITS_SUCCESS;
            break;
        }
        else if ((temp = strstr(cmd,"ctf_display")) != NULL)
        {
            stdoutDisplay = ITS_FALSE;

            while ((*temp != '\0') && (*temp != ' ')) temp++;

            if (*temp == ' ') 
            {
                temp++;
                if (strcmp(temp,"on") == 0)
                {
                    stdoutDisplay = ITS_TRUE;
                    printf("\nctf_display on success\n");
                } 
                else if (strcmp(temp,"off") == 0)
                {
                    printf("\nctf_display off success\n");
                }
                else
                {
                    printf("\n ctf_display %s - %s unknown", temp, temp);
                    printf("\n ctf_display is set to off mode\n");
                }
            } 

            strcpy (command, "ctf_display");
            ret = ITS_SUCCESS;
            break;
        }
        else if (((temp = strstr(cmd,"ctf_trace")) != NULL) ||
                 ((temp = strstr(cmd,"ctf_connect")) != NULL))
        {
            ITS_INT ArgCount = 0;
            ITS_CHAR Arg[25][255];
            char buf[255];
            buf[0] = '\0';
            ITS_INT bufCount = 0;

            if (strstr(cmd,"ctf_trace") != NULL)
            {
                strcpy(command,"ctf_trace");
                temp += 9; 
            }
            else
            {
                strcpy(command,"ctf_connect");
                temp += 11;
            }

            while (*temp)
            {
                if (*temp == ' ')
                {
                    if (buf[0] != '\0')
                    {
                        buf[bufCount] = '\0';
                        strcpy(Arg[ArgCount], buf);
                        ArgCount++;
                        bufCount = 0;
                        buf[0] = '\0';
                    }
                }
                else
                {
                    buf[bufCount] = *temp;
                    bufCount++;
                }
                temp++;
            }

            if (bufCount)
            {
                buf[bufCount] = '\0';
                strcpy(Arg[ArgCount], buf);
                ArgCount++;
            }

            ret = ParseArguments(ArgCount, Arg);

            if (ret != ITS_SUCCESS)
            {
                if (strstr(cmd,"ctf_trace") != NULL)
                    printf("ctf_trace -i <input file> [-o <output file>]\n");
                else
                    printf("ctf_connect -s <ip address> -p <port>\n"); 
            }
        }
        else
        {
            PrintHelp();
            ret = -2;
            break;
        }
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Shows the CTF Console prompt and collect the command to be executed. 
 *      It parse the command and executes the action for the command.
 *
 *  Input Parameters:
 *      ITS_INT argc - Command line argument count
 *      char* argv[] - Command line argument strings.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Status of execution of the function. ITS_SUCCESS on success.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

ITS_INT WorkAsOffLine (ITS_INT argc, char* argv[])
{
    ITS_INT len = 0;
    
    /* stub in */
    ITS_INT ret = ITS_AddFeature(itsDSM_StubImplClass);
    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Failed to add DSM stub class: %d\n", ret);
        
        exit(EXIT_FAILURE);
    }

    ret = ITS_AddFeature(itsSS7STACK_ClassCCITT);

    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Failed to add ITU stack class: %d\n", ret);

        exit(EXIT_FAILURE);
    }

    ret = ITS_AddFeature(itsSS7STACK_ClassANSI);

    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Failed to add ANSI stack class: %d\n", ret);

        exit(EXIT_FAILURE);
    }

    ret = ITS_GlobalStart(0);
    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Can't initialize IntelliSS7: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    /* create the ring buffer */
    if ((buffer = RINGBUF_InitManager(4096, 90, WriteStdout, NULL)) == NULL)
    {
        fprintf(stderr, "Can't create ring buffer\n");

        return (EXIT_FAILURE);
    }

    std::string commandLine;
    ITS_OCTET buf[1024];
    char tempBuf[255];

    std::cout << std::endl;
    std::cout << "IntelliSS7 Central Tracing Console (CTF) version 1.0."
         << std::endl;
    std::cout << "(C) 1999 IntelliNet Technologies." 
         << std::endl;
    std::cout << std::endl;

    while(true)
    {
        std::cout << ">> ";
        
        // Read command line.
        if (std::cin.eof())
        {
            break;
        }
        

        #if defined(WIN32)
            std::getlinefixed(std::cin, commandLine, '\n');
        #else
            std::getline(std::cin, commandLine, '\n');
        #endif

        ITS_INT ret = ParseCommand((char*)commandLine.c_str());

        if (ret == 1)
        {
            break;
        }
        else if (ret == ITS_SUCCESS)
        {
            if (strcmp(command,"ctf_trace") == 0)
            {
                if (fpInput)
                {
                    char localPBuf[1024];
                    fread(buf, 11, 1, fpInput);
                    while (!feof(fpInput))
                    {
                        strcpy(localPBuf, "\n----------------------------------------------\n");
                        sprintf(tempBuf,"\n%d/%d/%d  %d:%d:%d\n\n",buf[0] + 1,
                            buf[1], ((buf[2] << 8) | buf[3]) + 1900,buf[4], 
                            buf[5], buf[6]);
                        strcat(localPBuf, tempBuf);
                        
                        len = (buf[7] << 24) | (buf[8] << 16) | (buf[9] << 8) | buf[10];

                        if ((len > 0) && (len < 1000))
                        {
                            fread(buf, len, 1, fpInput);
                            
                            PrintBuffer(buf, len, localPBuf, ITS_TRUE);
                            RINGBUF_Flush(buffer);
                            
                            if (fpOutput)
                            {
                                fprintf(fpOutput,"\n\n");
                            }
                        }
                        else
                        {
                            printf("Problem with length : File Pos -> %d length->%d\n", 
                                    ftell(fpInput), len);
                        }
                        
                        fread(buf, 11, 1, fpInput);
                    }
                    
                    fclose(fpInput);

                    if (fpOutput)
                    {
                        fclose(fpOutput);
                        printf ("CTF Trace successfully completed\n");
                    }

                    if (offmgr)
                    {
                        DLSYM_Destroy (offmgr);
                        offmgr = NULL;
                        offsym = NULL;
                    }
                }
            }
            else if (strcmp(command,"ctf_connect") == 0)
            {
                if (borderStart)
                {
                    ITS_THREAD thr;
                    if (THREAD_CreateThread(&thr, 0, StartBorderTransport, 
                               (void *)&thr, ITS_TRUE) != ITS_SUCCESS)
                    {
                        printf ("Error in creating the border transport\n");
                    }
                }
#if defined (WIN32)
                Sleep (5);
#else
                sleep (5);
#endif
            }
        }
    }

    RINGBUF_FreeManager(buffer);

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Prints the usage of the CTF Console.
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

void
Usage()
{
    printf("CTFConsoleD -i <input file> [-o <output file>]\n");
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Main function for CTF Console.
 *
 *  Input Parameters:
 *      Command line arguments.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Status of CTF console execution
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

int 
main(ITS_INT argc, char* argv[])
{
    inputFile[0] = '\0';
    outputFile[0] = '\0';

    return WorkAsOffLine(argc, argv);
}




    
