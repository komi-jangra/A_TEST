/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
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
 *
 *  ID: $Id: isup_cmn.c,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:06  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:02  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:49:58  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.1  2003/05/07 09:22:27  ssingh
 * LOG: ANSI/ITU latest changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 8.2  2003/04/25 13:27:51  sjaddu
 * LOG: Cic Rules is changed to ITS_OCTET.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:43:24  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.3  2003/01/06 22:39:34  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2002/12/31 09:00:14  akumar
 * LOG: Added new functions to support configuration of exchange_type and
 * LOG: segmentation_supported variables
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/01 15:48:13  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 6.3.2.1  2002/07/01 22:19:18  hbalimid
 * LOG: Updated with ISUP ANSI 92 & 95.
 * LOG:
 * LOG: Revision 6.3  2002/06/10 14:50:55  sjaddu
 * LOG: Typo fixes.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 15:31:34  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2.2.2  2002/05/13 22:38:49  hbalimid
 * LOG: Updated with the ITU 97 variant
 * LOG:
 * LOG: Revision 5.2.2.1  2002/03/22 19:17:43  ssharma
 * LOG: Fix timer handling.
 * LOG:
 * LOG: Revision 5.2  2002/02/26 16:49:49  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.1  2002/02/08 21:49:43  mmiers
 * LOG: Reorg is complete.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

/*
 * ugly, but it works
 */
#if defined(TANDEM)
#include <strings.h>
#endif

#include <its.h>
#include <its_license.h>
#include <its_trace.h>

#ident "$Id: isup_cmn.c,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $"

#include <isup_sn.h>
#include <isup_cmn.h>

#include <ansi/isup.h>
#include <itu/isup.h>

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function does a caseless compare of two strings.
 *
 *  Input Parameters:
 *      s1, s2 - strings to be compared.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      difference between the strings, 0 if not different.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
StringCaseCompare(const char *s1, const char *s2)
{
#if defined(unix) || defined(TANDEM)
    return strcasecmp(s1, s2);
#elif defined(WIN32)
    return _stricmp(s1, s2);
#else
#error "You need to see if one of the two above works or write your own."
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns a string corresponding to a variant type.
 *
 *  Input Parameters:
 *      variant - variant type (enumeration).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      valid variant string for valid variant type
 *      "UNKNOWN" for invalid variant type
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI const char *
ISUP_VariantToString(ISUP_VAR_TYPE variant)
{
    switch (variant)
    {
    case ISUP_ANSI_BELL:
        return "ANSI_BELL";
    
    case ISUP_ANSI_BELLCORE_96:
        return "ANSI_BELLCORE_96";
    
    case ISUP_ANSI_ERICSSON:
        return "ANSI_ERICSSON";
    
    case ISUP_ANSI_GENERIC_88:
        return"ANSI_GENERIC_88";
    
    case ISUP_ANSI_GENERIC_92:
        return "ANSI_GENERIC_92";
    
    case ISUP_ANSI_95:
        return "ANSI_ISUP_95";
    
    case ISUP_ANSI_JAMAICA:
        return "ANSI_JAMAICA";
    
    case ISUP_ANSI_MCI:
        return "ANSI_MCI";
    
    case ISUP_ANSI_PUERTO_RICO:
        return "ANSI_PUERTO_RICO";

    case ISUP_ITU_GENERIC_88:
        return "ITU_GENERIC_88";

    case ISUP_ITU_GENERIC_93:
        return "ITU_GENERIC_93";
    
    case ISUP_ITU_97:
        return "ITU_ISUP_97";
    
    case ISUP_ITU_ARGENTINA:
        return "ITU_ARGENTINA";
    
    case ISUP_ITU_AUSTRALIA_NIIF_97:
        return "ITU_AUSTRALIA_NIIF_97";

    case ISUP_ITU_AUSTRALIA_OPTUS_AUG_94:
        return "ITU_AUSTRALIA_OPTUS_AUG_94";

    case ISUP_ITU_BRAZIL:
        return "ITU_BRAZIL";
    
    case ISUP_ITU_BELGIUM:
        return "ITU_BELGIUM";
    
    case ISUP_ITU_BRUNEI:
        return "ITU_BRUNEI";
    
    case ISUP_ITU_CHILE:
        return "ITU_CHILE";

    case ISUP_ITU_CHINA24:
        return "ITU_CHINA24";

    case ISUP_ITU_COLUMBIA:
        return "ITU_COLUMBIA";
    
    case ISUP_ITU_CZECH_SLOVAK:
        return "ITU_CZECH_SLOVAK";
    
    case ISUP_ITU_ERICSSON_BB_CME20R5:
        return "ITU_ERICSSON_BB_CME20R5";
    
    case ISUP_ITU_ERICSSON_PBMS:
        return "ITU_ERICSSON_PBMS";

    case ISUP_ITU_ERICSSON_REL3_SWEDEN:
        return "ITU_ERICSSON_REL3_SWEDEN";
    
    case ISUP_ITU_ERICSSON_WB_CME20R6:
        return "ITU_ERICSSON_WB_CME20R6";
    
    case ISUP_ITU_ETSI_V1_92:
        return "ITU_ETSI_V1_92";
    
    case ISUP_ITU_ETSI_V2_95:
        return "ITU_ETSI_V2_95";
    
    case ISUP_ITU_ETSI_V3_98:
        return "ITU_ETSI_V3_98";

    case ISUP_ITU_FINLAND:
        return "ITU_FINLAND";
    
    case ISUP_ITU_FRANCE_SPIROU:
        return "ITU_FRANCE_SPIROU"  ;
    
    case ISUP_ITU_FRANCE_SSUTR2:
        return "ITU_FRANCE_SSUTR2";
    
    case ISUP_ITU_FRANCE_SSUR:
        return "ITU_FRANCE_SSUR";
    
    case ISUP_ITU_FRANCE_TS_ED2:
        return "ITU_FRANCE_TS_ED2";

    case ISUP_ITU_GERMANY:
        return "ITU_GERMANY";

    case ISUP_ITU_GREECE:
        return "ITU_GREECE";
    
    case ISUP_ITU_HONGKONG:
        return "ITU_HONGKONG";
    
    case ISUP_ITU_HUNGARY_NETCOM_CCS_0421:
        return "ITU_HUNGARY_NETCOM_CCS_0421";
    
    case ISUP_ITU_INDIA_V1:
        return "ITU_INDIA_V1";

    case  ISUP_ITU_INDIA_V2:
        return "ITU_INDIA_V2";
    
    case ISUP_ITU_INDONESIA:
        return "ITU_INDONESIA";
    
    case ISUP_ITU_IRELAND:
        return "ITU_IRELAND";
    
    case ISUP_ITU_ISRAEL_PELEPHONE:
        return "ITU_ISRAEL_PELEPHONE";
    
    case ISUP_ITU_ITALY_OMNITEL_VMS:
        return "ITU_ITALY_OMNITEL_VMS"  ;

    case ISUP_ITU_ITALY_SIP_NOKIA:
        return "ITU_ITALY_SIP_NOKIA";
    
    case ISUP_ITU_JAPAN_CTM:
        return "ITU_JAPAN_CTM";
    
    case ISUP_ITU_JAPAN_NTT:
        return "ITU_JAPAN_NTT";
    
    case ISUP_ITU_JAPAN_TTC2:
        return "ITU_JAPAN_TTC2";
    
    case ISUP_ITU_JAPAN_TTC3:
        return "ITU_JAPAN_TTC3"  ;

    case ISUP_ITU_KOREA:
        return "ITU_KOREA";
    
    case ISUP_ITU_MALAYSIA:
        return "ITU_MALAYSIA";
    
    case ISUP_ITU_MEXICO:
        return "ITU_MEXICO";
    
    case ISUP_ITU_NETHERLANDS:
        return "ITU_NETHERLANDS";
    
    case ISUP_ITU_NEWZEALAND:
        return "ITU_NEWZEALAND";

    case  ISUP_ITU_NORWAY:
        return "ITU_NORWAY";
    
    case ISUP_ITU_PERU_ARGEN_CHILE:
        return "ITU_PERU_ARGEN_CHILE";
    
    case ISUP_ITU_PHILIPPINES:
        return "ITU_PHILIPPINES";
    
    case ISUP_ITU_POLAND:
        return "ITU_POLAND";
    
    case ISUP_ITU_PORTUGAL_LUXEM_SEIMENS_EWSD:
        return "ITU_PORTUGAL_LUXEM_SEIMENS_EWSD"  ;

    case ISUP_ITU_Q767:
        return "ITU_Q767";
    
    case ISUP_ITU_RUSSIA:
        return "ITU_RUSSIA";
    
    case ISUP_ITU_SINGAPORE:
        return "ITU_SINGAPORE";
    
    case ISUP_ITU_SOUTH_AFRICA_TELKOM_ISSUE4:
        return "ITU_SOUTH_AFRICA_TELKOM_ISSUE4";
    
    case ISUP_ITU_SPAIN_EG_S3_C03:
        return "ITU_SPAIN_EG_S3_C03"  ;

    case ISUP_ITU_SWITZERLAND:
        return "ITU_SWITZERLAND";
    
    case ISUP_ITU_SWEDEN_V1_8211_A335:
        return "ITU_SWEDEN_V1_8211_A335";
    
    case ISUP_ITU_SWEDEN_V2_TELIA:
        return "ITU_SWEDEN_V2_TELIA";
    
    case ISUP_ITU_TAIWAN:
        return "ITU_TAIWAN";
    
    case ISUP_ITU_THAILAND_AIS_17_ANT:
        return "ITU_THAILAND_AIS_17_ANT";

    case ISUP_ITU_THAILAND_TOT_93:
        return "ITU_THAILAND_TOT_93";
    
    case ISUP_ITU_TURKEY:
        return "ITU_TURKEY";

    case ISUP_ITU_UAE:
        return "ITU_UAE";
 
    case ISUP_ITU_VENEZUELA:
        return "ITU_VENEZUELA";
    
    case ISUP_ITU_VIETNAM:
        return "ITU_VIETNAM";

    default:
        return "UNKNOWN";
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the variant type corresponding to a variant
 *      string.
 *
 *  Input Parameters:
 *      variant - variant string.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      valid variant enumeration for valid variant string
 *      ISUP_UNKNOWN for invalid variant string
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ISUP_VAR_TYPE 
ISUP_StringToVariant(const char *variant)
{
    ISUP_VAR_TYPE ret;

    assert(variant != NULL);

    if (StringCaseCompare(variant, "ANSI_BELL") == 0)
    {
        ret = ISUP_ANSI_BELL;
    }    
    else if (StringCaseCompare(variant, "ANSI_BELLCORE_96") == 0)
    {
        ret =  ISUP_ANSI_BELLCORE_96;
    }
    else if (StringCaseCompare(variant, "ANSI_ERICSSON") == 0)
    {
        ret =  ISUP_ANSI_ERICSSON;
    }
    else if (StringCaseCompare(variant, "ANSI_GENERIC_88") == 0)
    {
        ret =  ISUP_ANSI_GENERIC_88;
    }
    else if (StringCaseCompare(variant, "ANSI_GENERIC_92") == 0)
    {
        ret =  ISUP_ANSI_GENERIC_92;
    }
    else if (StringCaseCompare(variant, "ANSI_ISUP_95") == 0)
    {
        ret =  ISUP_ANSI_95;
    }
    else if (StringCaseCompare(variant, "ANSI_JAMAICA") == 0)
    {
        ret =  ISUP_ANSI_JAMAICA;
    }
    else if (StringCaseCompare(variant, "ANSI_MCI") == 0)
    {
        ret =  ISUP_ANSI_MCI;
    }
    else if (StringCaseCompare(variant, "ANSI_PUERTO_RICO") == 0)
    {
        ret =  ISUP_ANSI_PUERTO_RICO;
    }
    else if (StringCaseCompare(variant, "ITU_GENERIC_88") == 0)
    {
        ret =  ISUP_ITU_GENERIC_88;
    }
    else if (StringCaseCompare(variant, "ITU_GENERIC_93") == 0)
    {
        ret =  ISUP_ITU_GENERIC_93;    
    }
    else if (StringCaseCompare(variant, "ITU_ISUP_97") == 0)
    {
        ret =  ISUP_ITU_97;
    }
    else if (StringCaseCompare(variant, "ITU_ARGENTINA") == 0)
    {
        ret =  ISUP_ITU_ARGENTINA;
    }
    else if (StringCaseCompare(variant, "ITU_AUSTRALIA_NIIF_97") == 0)
    {
        ret =  ISUP_ITU_AUSTRALIA_NIIF_97;
    }
    else if (StringCaseCompare(variant, "ITU_AUSTRALIA_OPTUS_AUG_94") == 0)
    {
        ret =  ISUP_ITU_AUSTRALIA_OPTUS_AUG_94;
    }
    else if (StringCaseCompare(variant, "ITU_BRAZIL") == 0)
    {
        ret =  ISUP_ITU_BRAZIL;
    }
    else if (StringCaseCompare(variant, "ITU_BELGIUM") == 0)
    {
        ret =  ISUP_ITU_BELGIUM;
    }
    else if (StringCaseCompare(variant, "ITU_BRUNEI") == 0)
    {
        ret =  ISUP_ITU_BRUNEI;
    }
    else if (StringCaseCompare(variant, "ITU_CHILE") == 0)
    {
        ret =  ISUP_ITU_CHILE;
    }
    else if (StringCaseCompare(variant, "ITU_CHINA24") == 0)
    {
        ret =  ISUP_ITU_CHINA24;
    }
    else if (StringCaseCompare(variant, "ITU_COLUMBIA") == 0)
    {
        ret =  ISUP_ITU_COLUMBIA;
    }
    else if (StringCaseCompare(variant, "ITU_CZECH_SLOVAK") == 0)
    {
        ret =  ISUP_ITU_CZECH_SLOVAK;
    }
    else if (StringCaseCompare(variant, "ITU_ERICSSON_BB_CME20R5") == 0)
    {
        ret =  ISUP_ITU_ERICSSON_BB_CME20R5;
    }
    else if (StringCaseCompare(variant, "ITU_ERICSSON_PBMS") == 0)
    {
        ret =  ISUP_ITU_ERICSSON_PBMS;
    }
    else if (StringCaseCompare(variant, "ITU_ERICSSON_REL3_SWEDEN") == 0)
    {
        ret =  ISUP_ITU_ERICSSON_REL3_SWEDEN;
    }
    else if (StringCaseCompare(variant, "ITU_ERICSSON_WB_CME20R6") == 0)
    {
        ret =  ISUP_ITU_ERICSSON_WB_CME20R6;
    }
    else if (StringCaseCompare(variant, "ITU_ETSI_V1_92") == 0)
    {
        ret =  ISUP_ITU_ETSI_V1_92;
    }
    else if (StringCaseCompare(variant, "ITU_ETSI_V2_95") == 0)
    {
        ret =  ISUP_ITU_ETSI_V2_95;
    }
    else if (StringCaseCompare(variant, "ITU_ETSI_V3_98") == 0)
    {
        ret =  ISUP_ITU_ETSI_V3_98;
    }
    else if (StringCaseCompare(variant, "ITU_FINLAND") == 0)
    {
        ret =  ISUP_ITU_FINLAND;
    }
    else if (StringCaseCompare(variant, "ITU_FRANCE_SPIROU") == 0)
    {
        ret =  ISUP_ITU_FRANCE_SPIROU;
    }
    else if (StringCaseCompare(variant, "ITU_FRANCE_SSUTR2") == 0)
    {
        ret =  ISUP_ITU_FRANCE_SSUTR2;
    }
    else if (StringCaseCompare(variant, "ITU_FRANCE_SSUR") == 0)
    {
        ret =  ISUP_ITU_FRANCE_SSUR;
    }
    else if (StringCaseCompare(variant, "ITU_FRANCE_TS_ED2") == 0)
    {
        ret =  ISUP_ITU_FRANCE_TS_ED2;
    }
    else if (StringCaseCompare(variant, "ITU_GERMANY") == 0)
    {
        ret =  ISUP_ITU_GERMANY;
    }
    else if (StringCaseCompare(variant, "ITU_GREECE") == 0)
    {
        ret =  ISUP_ITU_GREECE;
    }
    else if (StringCaseCompare(variant, "ITU_HONGKONG") == 0)
    {
        ret =  ISUP_ITU_HONGKONG;
    }
    else if (StringCaseCompare(variant, "ITU_HUNGARY_NETCOM_CCS_0421") == 0)
    {
        ret =  ISUP_ITU_HUNGARY_NETCOM_CCS_0421;
    }
    else if (StringCaseCompare(variant, "ITU_INDIA_V1") == 0)
    {
        ret =  ISUP_ITU_INDIA_V1;
    }
    else if (StringCaseCompare(variant, "ITU_INDIA_V2") == 0)
    {
        ret =  ISUP_ITU_INDIA_V2;
    }
    else if (StringCaseCompare(variant, "ITU_INDONESIA") == 0)
    {
        ret =  ISUP_ITU_INDONESIA;
    }
    else if (StringCaseCompare(variant, "ITU_IRELAND") == 0)
    {
        ret =  ISUP_ITU_IRELAND;
    }
    else if (StringCaseCompare(variant, "ITU_ISRAEL_PELEPHONE") == 0)
    {
        ret =  ISUP_ITU_ISRAEL_PELEPHONE;
    }
    else if (StringCaseCompare(variant, "ITU_ITALY_OMNITEL_VMS") == 0)
    {
        ret =  ISUP_ITU_ITALY_OMNITEL_VMS;
    }
    else if (StringCaseCompare(variant, "ITU_ITALY_SIP_NOKIA") == 0)
    {
        ret =  ISUP_ITU_ITALY_SIP_NOKIA;
    }
    else if (StringCaseCompare(variant, "ITU_JAPAN_CTM") == 0)
    {
        ret =  ISUP_ITU_JAPAN_CTM;
    }
    else if (StringCaseCompare(variant, "ITU_JAPAN_NTT") == 0)
    {
        ret =  ISUP_ITU_JAPAN_NTT;
    }
    else if (StringCaseCompare(variant, "ITU_JAPAN_TTC2") == 0)
    {
        ret =  ISUP_ITU_JAPAN_TTC2;
    }
    else if (StringCaseCompare(variant, "ITU_JAPAN_TTC3") == 0)
    {
        ret =  ISUP_ITU_JAPAN_TTC3;
    }
    else if (StringCaseCompare(variant, "ITU_KOREA") == 0)
    {
        ret =  ISUP_ITU_KOREA;
    }
    else if (StringCaseCompare(variant, "ITU_MALAYSIA") == 0)
    {
        ret =  ISUP_ITU_MALAYSIA;
    }
    else if (StringCaseCompare(variant, "ITU_MEXICO") == 0)
    {
        ret =  ISUP_ITU_MEXICO;
    }
    else if (StringCaseCompare(variant, "ITU_NETHERLANDS") == 0)
    {
        ret =  ISUP_ITU_NETHERLANDS;
    }
    else if (StringCaseCompare(variant, "ITU_NEWZEALAND") == 0)
    {
        ret =  ISUP_ITU_NEWZEALAND;
    }
    else if (StringCaseCompare(variant, "ITU_NORWAY") == 0)
    {
        ret =  ISUP_ITU_NORWAY;
    }
    else if (StringCaseCompare(variant, "ITU_PERU_ARGEN_CHILE") == 0)
    {
        ret =  ISUP_ITU_PERU_ARGEN_CHILE;
    }
    else if (StringCaseCompare(variant, "ITU_PHILIPPINES") == 0)
    {
        ret =  ISUP_ITU_PHILIPPINES;
    }
    else if (StringCaseCompare(variant, "ITU_POLAND") == 0)
    {
        ret =  ISUP_ITU_POLAND;
    }
    else if (StringCaseCompare(variant, "ITU_PORTUGAL_LUXEM_SEIMENS_EWSD") == 0)
    {
        ret =  ISUP_ITU_PORTUGAL_LUXEM_SEIMENS_EWSD;
    }
    else if (StringCaseCompare(variant, "ITU_Q767") == 0)
    {
        ret =  ISUP_ITU_Q767;
    }
    else if (StringCaseCompare(variant, "ITU_RUSSIA") == 0)
    {
        ret =  ISUP_ITU_RUSSIA;
    }
    else if (StringCaseCompare(variant, "ITU_SINGAPORE") == 0)
    {
        ret =  ISUP_ITU_SINGAPORE;
    }
    else if (StringCaseCompare(variant, "ITU_SOUTH_AFRICA_TELKOM_ISSUE4") == 0)
    {
        ret =  ISUP_ITU_SOUTH_AFRICA_TELKOM_ISSUE4;
    }
    else if (StringCaseCompare(variant, "ITU_SPAIN_EG_S3_C03") == 0)
    {
        ret =  ISUP_ITU_SPAIN_EG_S3_C03;
    }
    else if (StringCaseCompare(variant, "ITU_SWITZERLAND") == 0)
    {
        ret =  ISUP_ITU_SWITZERLAND;
    }
    else if (StringCaseCompare(variant, "ITU_SWEDEN_V1_8211_A335") == 0)
    {
        ret =  ISUP_ITU_SWEDEN_V1_8211_A335;
    }
    else if (StringCaseCompare(variant, "ITU_SWEDEN_V2_TELIA") == 0)
    {
        ret =  ISUP_ITU_SWEDEN_V2_TELIA;
    }
    else if (StringCaseCompare(variant, "ITU_TAIWAN") == 0)
    {
        ret =  ISUP_ITU_TAIWAN;
    }
    else if (StringCaseCompare(variant, "ITU_THAILAND_AIS_17_ANT") == 0)
    {
        ret =  ISUP_ITU_THAILAND_AIS_17_ANT;
    }
    else if (StringCaseCompare(variant, "ITU_THAILAND_TOT_93") == 0)
    {
        ret =  ISUP_ITU_THAILAND_TOT_93;
    }
    else if (StringCaseCompare(variant, "ITU_TURKEY") == 0)
    {
        ret =  ISUP_ITU_TURKEY;
    }
    else if (StringCaseCompare(variant, "ITU_UAE") == 0)
    {
        ret =  ISUP_ITU_UAE;
    }
    else if (StringCaseCompare(variant, "ITU_VENEZUELA") == 0)
    {
        ret =  ISUP_ITU_VENEZUELA;
    }
    else if (StringCaseCompare(variant, "ITU_VIETNAM") == 0)
    {
        ret =  ISUP_ITU_VIETNAM;
    }
    else
    {
        ret =  ISUP_UNKNOWN;
    }

    return(ret);
}

/*.implementation:extern
 ***************************************************************************
 *  Purpose:
 *      This function checks if the given variant is ANSI.
 *  Input Parameters:
 *      variant - variant string.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE or ITS_FALSE
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_BOOLEAN 
ISUP_VariantIsANSI(ISUP_VAR_TYPE var)
{
    if ((var > ISUP_ANSI_MIN) && (var <  ISUP_ANSI_MAX))
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function checks if the given variant is ITU.
 *
 *  Input Parameters:
 *      variant - variant string.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE or ITS_FALSE
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_BOOLEAN 
ISUP_VariantIsCCITT(ISUP_VAR_TYPE var)
{
    if ((var > ISUP_ITU_MIN) && (var <  ISUP_ITU_MAX))
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns a string corresponding to a variant type.
 *
 *  Input Parameters:
 *      variant - variant type (enumeration).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      valid variant string for valid variant type
 *      "UNKNOWN" for invalid variant type
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI const char *
ISUP_TimerToString(ITS_OCTET tmr_id)
{
    switch (tmr_id)
    {
    case ITS_ISUP_TIMER_T1:
        return "T1";
    
    case ITS_ISUP_TIMER_T2:
        return "T2";
    
    case ITS_ISUP_TIMER_T3:
        return "T3";

    case ITS_ISUP_TIMER_T4:
        return "T4";

    case ITS_ISUP_TIMER_T5:
        return "T5";

    case ITS_ISUP_TIMER_T6:
        return "T6";

    case ITS_ISUP_TIMER_T7:
        return "T7";

    case ITS_ISUP_TIMER_T8:
        return "T8";

    case ITS_ISUP_TIMER_T9:
        return "T9";

    case ITS_ISUP_TIMER_T10:
        return "T10";

    case ITS_ISUP_TIMER_T11:
        return "T11";

    case ITS_ISUP_TIMER_T12:
        return "T12";

    case ITS_ISUP_TIMER_T13:
        return "T13";

    case ITS_ISUP_TIMER_T14:
        return "T14";

    case ITS_ISUP_TIMER_T15:
        return "T15";

    case ITS_ISUP_TIMER_T16:
        return "T16";

    case ITS_ISUP_TIMER_T17:
        return "T17";

    case ITS_ISUP_TIMER_T18:
        return "T18";

    case ITS_ISUP_TIMER_T19:
        return "T19";

    case ITS_ISUP_TIMER_T20:
        return "T20";

    case ITS_ISUP_TIMER_T21:
        return "T21";

    case ITS_ISUP_TIMER_T22:
        return "T22";

    case ITS_ISUP_TIMER_T23:
        return "T23";

    case ITS_ISUP_TIMER_T24:
        return "T24";

    case ITS_ISUP_TIMER_T25:
        return "T25";

    case ITS_ISUP_TIMER_T26:
        return "T26";

    case ITS_ISUP_TIMER_T27:
        return "T27";

    case ITS_ISUP_TIMER_T28:
        return "T28";

    case ITS_ISUP_TIMER_T29:
        return "T29";

    case ITS_ISUP_TIMER_T30:
        return "T30";

    case ITS_ISUP_TIMER_T31:
        return "T31";

    case ITS_ISUP_TIMER_T32:
        return "T32";

    case ITS_ISUP_TIMER_T33:
        return "T33";

    case ITS_ISUP_TIMER_T34:
        return "T34";

    case ITS_ISUP_TIMER_T35:
        return "T35";

    case ITS_ISUP_TIMER_T36:
        return "T36";

    case ITS_ISUP_TIMER_T37:
        return "T37";

    case ITS_ISUP_TIMER_T38:
        return "T38";

    case ITS_ISUP_TIMER_T39:
        return "T39";

    /* Additional ANSI timers */
    case ITS_ISUP_TIMER_TACCR:
        return "TACCR";

    case ITS_ISUP_TIMER_TCCR:
        return "TCCR";

    case ITS_ISUP_TIMER_TCCRR:
        return "TCCRR";

    case ITS_ISUP_TIMER_TCGB:
        return "TCGB";

    case ITS_ISUP_TIMER_TCRA:
        return "TCRA";

    case ITS_ISUP_TIMER_TCRM:
        return "TCRM";

    case ITS_ISUP_TIMER_TCVT:
        return "TCVT";

    case ITS_ISUP_TIMER_TEXMD:
        return "TEXMD";

    case ITS_ISUP_TIMER_TGRS:
        return "TGRS";

    case ITS_ISUP_TIMER_THGA:
        return "THGA";

    case ITS_ISUP_TIMER_TSCGA:
        return "TSCGA";

    case ITS_ISUP_TIMER_TSCGAD:
        return "TSCGAD";

    default:
        return "INVALID";
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns a string corresponding to a variant type.
 *
 *  Input Parameters:
 *      variant - variant type (enumeration).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      valid variant string for valid variant type
 *      "UNKNOWN" for invalid variant type
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_OCTET
ISUP_StringToTimer(const char *tmr)
{
    ITS_OCTET ret;

    assert(tmr != NULL);

    if (StringCaseCompare(tmr, "T1") == 0)
    {
        ret = ITS_ISUP_TIMER_T1;
    }
    else if (StringCaseCompare(tmr, "T2") == 0)
    {
        ret =  ITS_ISUP_TIMER_T2;
    }
    else if (StringCaseCompare(tmr, "T3") == 0)
    {
        ret =  ITS_ISUP_TIMER_T3;
    }
    else if (StringCaseCompare(tmr, "T4") == 0)
    {
        ret =  ITS_ISUP_TIMER_T4;
    }
    else if (StringCaseCompare(tmr, "T5") == 0)
    {
        ret =  ITS_ISUP_TIMER_T5;
    }
    else if (StringCaseCompare(tmr, "T6") == 0)
    {
        ret =  ITS_ISUP_TIMER_T6;
    }
    else if (StringCaseCompare(tmr, "T7") == 0)
    {
        ret =  ITS_ISUP_TIMER_T7;
    }
    else if (StringCaseCompare(tmr, "T8") == 0)
    {
        ret =  ITS_ISUP_TIMER_T8;
    }
    else if (StringCaseCompare(tmr, "T9") == 0)
    {
        ret =  ITS_ISUP_TIMER_T9;
    }
    else if (StringCaseCompare(tmr, "T10") == 0)
    {
        ret =  ITS_ISUP_TIMER_T10;
    }
    else if (StringCaseCompare(tmr, "T11") == 0)
    {
        ret =  ITS_ISUP_TIMER_T11;
    }
    else if (StringCaseCompare(tmr, "T12") == 0)
    {
        ret =  ITS_ISUP_TIMER_T12;
    }
    else if (StringCaseCompare(tmr, "T13") == 0)
    {
        ret =  ITS_ISUP_TIMER_T13;
    }
    else if (StringCaseCompare(tmr, "T14") == 0)
    {
        ret =  ITS_ISUP_TIMER_T14;
    }
    else if (StringCaseCompare(tmr, "T15") == 0)
    {
        ret =  ITS_ISUP_TIMER_T15;
    }
    else if (StringCaseCompare(tmr, "T16") == 0)
    {
        ret =  ITS_ISUP_TIMER_T16;
    }
    else if (StringCaseCompare(tmr, "T17") == 0)
    {
        ret =  ITS_ISUP_TIMER_T17;
    }
    else if (StringCaseCompare(tmr, "T18") == 0)
    {
        ret =  ITS_ISUP_TIMER_T18;
    }
    else if (StringCaseCompare(tmr, "T19") == 0)
    {
        ret =  ITS_ISUP_TIMER_T19;
    }
    else if (StringCaseCompare(tmr, "T20") == 0)
    {
        ret =  ITS_ISUP_TIMER_T20;
    }
    else if (StringCaseCompare(tmr, "T21") == 0)
    {
        ret =  ITS_ISUP_TIMER_T21;
    }
    else if (StringCaseCompare(tmr, "T22") == 0)
    {
        ret =  ITS_ISUP_TIMER_T22;
    }
    else if (StringCaseCompare(tmr, "T23") == 0)
    {
        ret =  ITS_ISUP_TIMER_T23;
    }
    else if (StringCaseCompare(tmr, "T24") == 0)
    {
        ret =  ITS_ISUP_TIMER_T24;
    }
    else if (StringCaseCompare(tmr, "T25") == 0)
    {
        ret =  ITS_ISUP_TIMER_T25;
    }
    else if (StringCaseCompare(tmr, "T26") == 0)
    {
        ret =  ITS_ISUP_TIMER_T26;
    }
    else if (StringCaseCompare(tmr, "T27") == 0)
    {
        ret =  ITS_ISUP_TIMER_T27;
    }
    else if (StringCaseCompare(tmr, "T28") == 0)
    {
        ret =  ITS_ISUP_TIMER_T28;
    }
    else if (StringCaseCompare(tmr, "T29") == 0)
    {
        ret =  ITS_ISUP_TIMER_T29;
    }
    else if (StringCaseCompare(tmr, "T30") == 0)
    {
        ret =  ITS_ISUP_TIMER_T30;
    }
    else if (StringCaseCompare(tmr, "T31") == 0)
    {
        ret =  ITS_ISUP_TIMER_T31;
    }
    else if (StringCaseCompare(tmr, "T32") == 0)
    {
        ret =  ITS_ISUP_TIMER_T32;
    }
    else if (StringCaseCompare(tmr, "T33") == 0)
    {
        ret =  ITS_ISUP_TIMER_T33;
    }
    else if (StringCaseCompare(tmr, "T34") == 0)
    {
        ret =  ITS_ISUP_TIMER_T34;
    }
    else if (StringCaseCompare(tmr, "T35") == 0)
    {
        ret =  ITS_ISUP_TIMER_T35;
    }
    else if (StringCaseCompare(tmr, "T36") == 0)
    {
        ret =  ITS_ISUP_TIMER_T36;
    }
    else if (StringCaseCompare(tmr, "T37") == 0)
    {
        ret =  ITS_ISUP_TIMER_T37;
    }
    else if (StringCaseCompare(tmr, "T38") == 0)
    {
        ret =  ITS_ISUP_TIMER_T37;
    }
    else if (StringCaseCompare(tmr, "T39") == 0)
    {
        ret =  ITS_ISUP_TIMER_T37;
    }
    else if (StringCaseCompare(tmr, "TACCr") == 0)
    {
        ret =  ITS_ISUP_TIMER_TACCR;
    }
    else if (StringCaseCompare(tmr, "TCCR") == 0)
    {
        ret =  ITS_ISUP_TIMER_TCCR;
    }
    else if (StringCaseCompare(tmr, "TCCRr") == 0)
    {
        ret =  ITS_ISUP_TIMER_TCCRR;
    }
    else if (StringCaseCompare(tmr, "TCGB") == 0)
    {
        ret =  ITS_ISUP_TIMER_TCGB;
    }
    else if (StringCaseCompare(tmr, "TCRA") == 0)
    {
        ret =  ITS_ISUP_TIMER_TCRA;
    }
    else if (StringCaseCompare(tmr, "TCRM") == 0)
    {
        ret =  ITS_ISUP_TIMER_TCRM;
    }
    else if (StringCaseCompare(tmr, "TCVT") == 0)
    {
        ret =  ITS_ISUP_TIMER_TCVT;
    }
    else if (StringCaseCompare(tmr, "TEXMd") == 0)
    {
        ret =  ITS_ISUP_TIMER_TEXMD;
    }
    else if (StringCaseCompare(tmr, "TGRS") == 0)
    {
        ret =  ITS_ISUP_TIMER_TGRS;
    }
    else if (StringCaseCompare(tmr, "THGA") == 0)
    {
        ret =  ITS_ISUP_TIMER_THGA;
    }
    else if (StringCaseCompare(tmr, "TSCGA") == 0)
    {
        ret =  ITS_ISUP_TIMER_TSCGA;
    }
    else if (StringCaseCompare(tmr, "TSCGAd") == 0)
    {
        ret =  ITS_ISUP_TIMER_TSCGAD;
    }
    else
    {
        ret =  ISUP_TMR_HNDL_INVALID;
    }

    return(ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns a string corresponding to a variant type.
 *
 *  Input Parameters:
 *      variant - variant type (enumeration).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      valid variant string for valid variant type
 *      "UNKNOWN" for invalid variant type
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI const char *
ISUP_TimerHandlerToString(ISUP_TMR_HNDL tmr_hndl)
{
    switch (tmr_hndl)
    {
    case ISUP_TMR_HNDL_STACK:
        return "STACK";
    
    case ISUP_TMR_HNDL_APP:
        return "APP";

    default:
        return "INVALID";
    }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the variant type corresponding to a variant
 *      string.
 *
 *  Input Parameters:
 *      variant - variant string.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      valid variant enumeration for valid variant string
 *      ISUP_UNKNOWN for invalid variant string
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ISUP_TMR_HNDL
ISUP_StringToTimerHandler(const char *tmr_hndl)
{
    ISUP_TMR_HNDL ret;

    assert(tmr_hndl != NULL);

    if (StringCaseCompare(tmr_hndl, "STACK") == 0)
    {
        ret = ISUP_TMR_HNDL_STACK;
    }
    else if (StringCaseCompare(tmr_hndl, "APP") == 0)
    {
        ret = ISUP_TMR_HNDL_APP;
    }
    else if (StringCaseCompare(tmr_hndl, "DEF") == 0)
    {
        ret = ISUP_TMR_HNDL_STACK;
    }
    else if (StringCaseCompare(tmr_hndl, "") == 0)
    {
        ret = ISUP_TMR_HNDL_STACK;
    }
    else
    {
        ret = ISUP_TMR_HNDL_INVALID;
    }

    return (ret);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns a string corresponding to a variant type.
 *
 *  Input Parameters:
 *      variant - variant type (enumeration).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      valid variant string for valid variant type
 *      "UNKNOWN" for invalid variant type
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI const char *
ISUP_CkgpCtrlToString(ITS_OCTET ckgp_ctrl)
{
    switch (ckgp_ctrl)
    {
    case ISUP_CKGP_CTRL_NONE:
        return "NONE";
    
    case ISUP_CKGP_CTRL_EVEN:
        return "EVEN";

    case ISUP_CKGP_CTRL_ODD:
        return "ODD";
    
    case ISUP_CKGP_CTRL_ALL:
        return "ALL";

    case ISUP_CKGP_CTRL_DEF:
        return "DEF";

    default:
        return "INVALID";
    }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns the variant type corresponding to a variant
 *      string.
 *
 *  Input Parameters:
 *      variant - variant string.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      valid variant enumeration for valid variant string
 *      ISUP_UNKNOWN for invalid variant string
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI ITS_OCTET 
ISUP_StringToCkgpCtrl(const char *ckgp_ctrl)
{
    ITS_OCTET ret;

    assert(ckgp_ctrl != NULL);

    if (StringCaseCompare(ckgp_ctrl, "NONE") == 0)
    {
        ret = ISUP_CKGP_CTRL_NONE;
    }
    else if (StringCaseCompare(ckgp_ctrl, "EVEN") == 0)
    {
        ret = ISUP_CKGP_CTRL_EVEN;
    }
    else if (StringCaseCompare(ckgp_ctrl, "ODD") == 0)
    {
        ret = ISUP_CKGP_CTRL_ODD;
    }
    else if (StringCaseCompare(ckgp_ctrl, "ALL") == 0)
    {
        ret = ISUP_CKGP_CTRL_ALL;
    }
    else if (StringCaseCompare(ckgp_ctrl, "DEF") == 0)
    {
        ret = ISUP_CKGP_CTRL_DEF;
    }
    else
    {
        ret = ISUP_CKGP_CTRL_INV;
    }

    return(ret);
}

SS7DLLAPI ISUP_XCHANGE_TYPE
ISUP_StringToXchangeType(const char *xchange_type)
{
    ISUP_XCHANGE_TYPE ret;

    assert(xchange_type != NULL);

    if (StringCaseCompare(xchange_type, "TYPE_A") == 0)
    {
        ret = ISUP_XCHANGE_TYPE_A;
    }
    else if (StringCaseCompare(xchange_type, "TYPE_B") == 0)
    {
        ret = ISUP_XCHANGE_TYPE_B;
    }
    else
    {
        ret = ISUP_XCHANGE_TYPE_INV;
    }

    return(ret);
}

SS7DLLAPI ITS_BOOLEAN
ISUP_StringToSegSupport(const char *seg_supported)
{
    ITS_BOOLEAN ret;

    assert(seg_supported != NULL);

    if (StringCaseCompare(seg_supported, "no") == 0)
    {
        ret = ITS_FALSE;
    }
    else if (StringCaseCompare(seg_supported, "yes") == 0)
    {
        ret = ITS_TRUE;
    }
    else
    {
        ret = ITS_FALSE;
    }

    return(ret);
}
