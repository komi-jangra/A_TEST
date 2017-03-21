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
 * ID: $Id: isup_macros.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:43  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:06  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:01  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2002/02/01 20:05:56  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:35  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:05  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:25  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:26  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/11/10 19:57:19  fhasle
 * LOG:
 * LOG: Almost done fully ANSI and ITU compatible.
 * LOG:
 * LOG: Revision 1.2  1999/10/27 15:45:22  mmiers
 * LOG:
 * LOG:
 * LOG: Get the headers in here.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ISUP_MACROS_H
#define _ISUP_MACROS_H

#ident "$Id: isup_macros.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $"

/* ISUP Extention Indicator */
#define ISUP_EXT_INDICATOR  (0x80U)

#define SET_ISUP_EXT_INDICATOR(x) (*x |= ISUP_EXT_INDICATOR)

#define ISUP_EXT_INDICATOR_SET(x)                       \
    (((x & ISUP_EXT_INDICATOR) == ISUP_EXT_INDICATOR),  \
     ? ITS_TRUE : ITS_FALSE)


/* ISUP Layer 1,2,3 Identifier */
#define ISUP_LAYER_1_IDEN   0x01
#define ISUP_LAYER_2_IDEN   0x02
#define ISUP_LAYER_3_IDEN   0x03




/* Bit(s) masks */
#define BITS_21_MASK    (0x03U)
#define BITS_23_MASK    (0x06U)
#define BITS_43_MASK    (0xC0U)
#define BITS_65_MASK    (0x30U)
#define BITS_76_MASK    (0x60U)
#define BITS_87_MASK    (0xC0U)
#define BITS_86_MASK    (0xE0U)
#define BITS_31_MASK    (0x07U)        
#define BITS_75_MASK    (0x70U)
#define BITS_41_MASK    (0x0FU)
#define BITS_85_MASK    (0xF0U)
#define BITS_51_MASK    (0x1FU)
#define BITS_61_MASK    (0x3FU)
#define BITS_71_MASK    (0x7FU)


#define BIT_1_MASK    (0x01U)
#define BIT_2_MASK    (0x02U)
#define BIT_3_MASK    (0x04U)
#define BIT_4_MASK    (0x08U)
#define BIT_5_MASK    (0x10U)
#define BIT_6_MASK    (0x20U)
#define BIT_7_MASK    (0x40U)
#define BIT_8_MASK    (0x80U)


#if defined ANSI
/*
 * Business group:
 * 'x' should be a pointer to ISUP_BUSINESS_GROUP.
 * Macros only used if line privileges info indicator = 0.
 * 'x' should be a pointer to ISUP_BUSINESS_GROUP structure. 
 * 'y' should represent the value to set for the specific bits(s) (octet 1).
 * 'sel' should be the party selector. 
 * 'orig' should be the originating restrictions. 
 * 'term' should be the terminating restrictions. 
 */
#define SET_BUS_GRP_BIT_7(x,y)    \
    ((x)->party_selector &= 0xBF, \
     (x)->party_selector |= (((y)<<6) & BIT_7_MASK))

#define SET_BUS_GRP_BIT_6(x,y)    \
    ((x)->party_selector &= 0xDF, \
     (x)->party_selector |= (((y)<<5) & BIT_6_MASK))

#define SET_BUS_GRP_BIT_5(x,y)    \
    ((x)->party_selector &= 0xEF, \
     (x)->party_selector |= (((y)<<4) & BIT_5_MASK))

#define SET_BUS_GRP_PARTY_SEL(x,sel)    \
    ((x)->party_selector &= BITS_85_MASK, \
     (x)->party_selector |= ((sel) & BITS_41_MASK))

/* Macros only used if line privileges info indicator = 0. */
#define SET_BUS_GRP_LN_PRIVLG(x, orig, term)                \
    ((x)->line_privileges = 0x00,                           \
     (x)->line_privileges |= (((orig)<<4) & BIT_85_MASK),   \
     (x)->line_privileges |= ((term) & BIT_41_MASK))

#define SET_BUS_GRP_LN_PRIVLG_ORIG(x,orig)  \
    ((x)->line_privileges &= BIT_41_MASK,   \
     (x)->line_privileges |= (((orig)<<4) & BIT_85_MASK))
     
#define SET_BUS_GRP_LN_PRIVLG_TERM(x,term)  \
    ((x)->line_privileges &= BIT_85_MASK,   \
     (x)->line_privileges |= ((term) & BIT_41_MASK))

/* 'x' should be a ISUP_BUSINESS_GROUP structure. */
#define GET_BUS_GRP_ATTENDANT_STAT(x) (((x).party_selector & BIT_7_MASK)>>6)
#define GET_BUS_GRP_BGID_STAT(x)      (((x).party_selector & BIT_6_MASK)>>5)
#define GET_BUS_GRP_LINE_INFO(x)      (((x).party_selector & BIT_5_MASK)>>4)
#define GET_BUS_GRP_PARTY_SEL(x)      ((x).party_selector & BITS_41_MASK)
#define GET_BUS_GRP_LN_PRIVLG_ORIG(x) (((x).line_privileges & BIT_85_MASK)>>4)
#define GET_BUS_GRP_LN_PRIVLG_TERM(x) ((x).line_privileges & BIT_41_MASK)

#endif /* ANSI */
/* End: Business group. */

/* Call reference and Connection Request:
 * 'x' should be a pointer to ISUP_CALL_REFERENCE or
 * ISUP_CONNECTION_REQUEST.
 * 'id' should represent the call identity.
 * 'pc' should represent the point code.
 */
#define SET_CR_CALL_IDENT(x,id)                 \
    ((x)->call_ident[0] &= 0xFFU,               \
     (x)->call_ident[0] |= ((id) & 0xFFU),      \
     (x)->call_ident[1] &= 0xFFU,               \
     (x)->call_ident[1] |= (((id)>>8) & 0xFFU), \
     (x)->call_ident[2] &= 0xFFU,               \
     (x)->call_ident[2] |= (((id)>>16) & 0xFFU))

#if defined CCITT
#define SET_CR_POINT_CODE(x,pc)             \
    ((x)->point_code[0] &= 0xFFU,           \
     (x)->point_code[0] |= ((pc) & 0xFFU),  \
     (x)->point_code[1] &= 0xFFU,           \
     (x)->point_code[1] |= (((pc)>>8) & BITS_61_MASK))
#elif defined ANSI
#define SET_CR_POINT_CODE(x,pc)             \
    ((x)->point_code[0] &= 0xFFU,           \
     (x)->point_code[0] |= ((pc) & 0xFFU),  \
     (x)->point_code[1] &= 0xFFU,           \
     (x)->point_code[1] |= (((pc)>>8) & 0xFFU), \
     (x)->point_code[2] &= 0xFFU,               \
     (x)->point_code[2] |= (((pc)>>16) & 0xFFU))
#endif

/* x should be a ISUP_CALL_REFERENCE or ISUP_CONNECTION_REQUEST struct. */
#define GET_CR_CALL_IDENT(x)                \
    ((((x).call_ident[2] & 0xFFU) << 16) |  \
     (((x).call_ident[1] & 0xFFU) << 8) |   \
     ((x).call_ident[0] & 0xFFU))

#if defined CCITT
#define GET_CR_POINT_CODE(x)                        \
    ((((x).point_code[1] & BITS_61_MASK) << 8) |    \
     ((x).point_code[0] & 0xFFU))
#elif defined ANSI
#define GET_CR_POINT_CODE(x)                \
    ((((x).point_code[2] & 0xFFU) << 16) |  \
     (((x).point_code[1] & 0xFFU) << 8) |   \
     ((x).point_code[0] & 0xFFU))
#endif
/* End: Call reference. */

/* 
 * Called party number:
 * 'x' should be a pointer to ISUP_CALLED_PARTY_NUM.
 * 'odd' should represent the odd/even indicator.
 * 'nat' should represent the nature of address.
 * 'inn' should represent the internal network number (CCITT only).
 * 'num' should represent the numbering plan.
 */
#define SET_CPN_ODD_EVEN_BIT(x,odd) \
    ((x)->addr_ind &= BITS_71_MASK, \
     (x)->addr_ind |= (((odd)<<7) & BIT_8_MASK))

#define SET_CPN_ADDR_IND(x,nat)     \
    ((x)->addr_ind &= BIT_8_MASK,   \
     (x)->addr_ind |= ((nat) & BITS_71_MASK))

#if defined CCITT
#define SET_CPN_INN_BIT(x,in)       \
    ((x)->num_plan &= BITS_71_MASK, \
     (x)->num_plan |= (((in)<<7) & BIT_8_MASK))
#endif

#define SET_CPN_NUM_PLAN(x,num)     \
    ((x)->num_plan &= BIT_8_MASK,   \
     (x)->num_plan |= (((num))<<4) & BITS_75_MASK))

/* x should be a ISUP_CALLED_PARTY_NUM struct. */
#define GET_CPN_ODD_EVEN_BIT(x) (((x).addr_ind & BIT_8_MASK)>>7)
#define GET_CPN_ODD_ADDR_IND(x) ((x).addr_ind & BITS_71_MASK)

#if defined CCITT
#define GET_CPN_ODD_INN_BIT(x)  (((x).num_plan & BIT_8_MASK)>>7)
#endif

#define GET_CPN_ODD_NUM_PLAN(x) (((x).num_plan & BITS_75_MASK)>>4)
/* End: Called party number. */

/* 
 * Calling party number:
 * Note: some macros from the Called party number can be used.
 * 'x' should be a pointer to ISUP_CALLING_PARTY_NUM.
 * 'num' should represent the numbering plan (way to set it is different).
 * 'pres' should represent the address representation restricted ind.
 * 'scren' should represent the screening indicator.
 */
#define SET_CPGN_NUM_PLAN(x,num) \
    ((x)->addr_ind &= 0x8FU,    \
     (x)->addr_ind |= (((num))<<4) & BITS_75_MASK))

#define SET_CPGN_PRES_IND(x,pres)   \
    ((x)->subfields4 &= 0xF3U,      \
     (x)->subfields4 |= (((pres)<<2) & BITS_43_MASK))

#define SET_CPGN_SCRN_IND(x,scren)  \
    ((x)->subfields4 &= 0xFCU,      \
     (x)->subfields4 |= ((scren) & BITS_21_MASK))

/* x should be a ISUP_CALLING_PARTY_NUM struct. */
#define GET_CPGN_PRES_IND(x) (((x)->subfields4 & BITS_43_MASK)>>2)
#define GET_CPGN_SCRN_IND(x) ((x)->subfields4 & BITS_21_MASK)
/* End: Calling party number. */


#if defined ANSI
/*
 * Carrier Identification.
 * 'x' should be a pointer to ISUP_CARRIER_IDENTIFICATION.
 * 'typ' should represent the type of netwrok id.
 * 'plan' should represent the network id plan.
 * 'd1' should represent digit 1 or 3.
 * 'd2' should represent digit 2 or 4 (set to 0 if plan is 3-digit).
 */
#define SET_CARRIER_ID_NTWRK(x, typ, plan)          \
    ((x)->network = 0x00,                           \
     (x)->network |= (((typ)<<4) & BITS_75_MASK),   \
     (x)->network |= ((plan) & BITS_41_MASK))

#define SET_CARRIER_ID_DIGIT_21(x, d1, d2)          \
    ((x)->digit2and1 = 0x00,                        \
     (x)->digit2and1 |= (((d2)<<4) & BITS_85_MASK), \
     (x)->digit2and1 |= ((d1) & BITS_41_MASK))

#define SET_CARRIER_ID_DIGIT_43(x, d1, d2)          \
    ((x)->digit4and3 = 0x00,                        \
     (x)->digit4and3 |= (((d2)<<4) & BITS_85_MASK), \
     (x)->digit4and3 |= ((d1) & BITS_41_MASK))

/* x should be a ISUP_CARRIER_IDENTIFICATION struct. */
#define GET_CARRIER_ID_NTWRK_TYPE(x) (((x).network & BITS_75_MASK)>>4)
#define GET_CARRIER_ID_NTWRK_PLAN(x) ((x).network & BITS_41_MASK)
#define GET_CARRIER_ID_DIGIT_1(x)    (((x).digit2and1 & BITS_85_MASK)>>4)
#define GET_CARRIER_ID_DIGIT_2(x)    ((x).digit2and1 & BITS_41_MASK)
#define GET_CARRIER_ID_DIGIT_3(x)    (((x).digit4and3 & BITS_85_MASK)>>4)
#define GET_CARRIER_ID_DIGIT_4(x)    ((x).digit4and3 & BITS_41_MASK))
#endif
/* End: Carrier Identification. */

/* 
 * Forward call indicators:
 * x should be a pointer to ISUP_FORWARD_CALL_INDICATORS struct.
 * y should represent the value to set for the specific bits(s).
 */

#define SET_FWD_CI_A_BIT(x,y)   \
    ((x)->fwd_ci[0] &= 0xFEU,   \
     (x)->fwd_ci[0] |= ((y) & BIT_1_MASK))

#define SET_FWD_CI_CB_BITS(x,y) \
    ((x)->fwd_ci[0] &= 0xF9U,   \
     (x)->fwd_ci[0] |= (((y)<<1) & BITS_23_MASK))

#define SET_FWD_CI_D_BIT(x,y)   \
     ((x)->fwd_ci[0] &= 0xF7U,  \
     (x)->fwd_ci[0] |= (((y)<<3) & BIT_4_MASK)

#define SET_FWD_CI_E_BIT(x,y)   \
    ((x)->fwd_ci[0] &= 0xEFU,   \
     (x)->fwd_ci[0] |= (((y)<<4) & BIT_5_MASK))

#define SET_FWD_CI_F_BIT(x,y)   \
    ((x)->fwd_ci[0] &= 0xDFU,   \
     (x)->fwd_ci[0] |= (((y)<<5) & BIT_6_MASK))

#define SET_FWD_CI_HG_BITS(x,y) \
    ((x)->fwd_ci[0] &= 0x3FU,   \
     (x)->fwd_ci[0] |= (((y)<<6) & BITS_87_MASK))

#define SET_FWD_CI_I_BIT(x,y)   \
    ((x)->fwd_ci[1] &= 0xFEU,   \
     (x)->fwd_ci[1] |= ((y) & BIT_1_MASK))

#define SET_FWD_CI_KJ_BITS(x,y) \
    ((x)->fwd_ci[1] &= 0xF9U,   \
     (x)->fwd_ci[1] |= (((y)<<1) & BITS_23_MASK))

/* x should be a ISUP_FORWARD_CALL_INDICATORS struct. */
#define GET_FWD_CI_A_BIT(x)     ((x).fwd_ci[0] & BIT_1_MASK)
#define GET_FWD_CI_CB_BITS(x)   (((x).fwd_ci[0] & & BITS_23_MASK)>>1)
#define GET_FWD_CI_D_BIT(x)     (((x).fwd_ci[0] & BIT_4_MASK)>>3)
#define GET_FWD_CI_E_BIT(x)     (((x).fwd_ci[0] & BIT_5_MASK)>>4)
#define GET_FWD_CI_F_BIT(x)     (((x).fwd_ci[0] & BIT_6_MASK)>>5)
#define GET_FWD_CI_HG_BITS(x)   (((x).fwd_ci[0] & & BITS_87_MASK)>>6)
#define GET_FWD_CI_I_BIT(x)     ((x).fwd_ci[1] & BIT_1_MASK)
#define GET_FWD_CI_KJ_BITS(x)   (((x).fwd_ci[1] & & BITS_23_MASK)>>1)
/* End: Forward call indicators. */

/*
 * Generic Digits
 * 'x' should be a pointer to ISUP_GENERIC_DIGITS struct.
 * 'typ' should be the type of digits.
 * 'sch' should be the scheme.
 */
#define SET_GEN_DIGITS_TYPE(x,typ)      \
    ((x)->type_scheme &= BITS_86_MASK,  \
     (x)->type_scheme |= ((typ) & BITS_51_MASK))

#define SET_GEN_DIGITS_SCHEME(x,sch)    \
    ((x)->type_scheme &= BITS_51_MASK,  \
     (x)->type_scheme |= (((sch)<<5) & BITS_86_MASK))

/* 'x' should be a ISUP_GENERIC_DIGITS struct. */
#define GET_GEN_DIGITS_TYPE(x)      ((x).type_scheme & BITS_51_MASK)
#define GET_GEN_DIGITS_SCHEME(x)    (((x).type_scheme & BITS_86_MASK)>>5)
/* End: Generic Digits. */

/*
 * Information Request Indicators
 * 'x' should be a pointer to ISUP_INFORMATION_REQUEST_INDICATORS struct.
 */
#define SET_INFO_REQ_BIT_A(x)   \
    ((x)->indics[0] &= 0xFE,    \
     (x)->indics[0] |= BIT_1_MASK);

#define SET_INFO_REQ_BIT_B(x)   \
    ((x)->indics[0] &= 0xFD,    \
     (x)->indics[0] |= BIT_2_MASK);

#define SET_INFO_REQ_BIT_D(x)   \
    ((x)->indics[0] &= 0xF7,    \
     (x)->indics[0] |= BIT_4_MASK);

#define SET_INFO_REQ_BIT_E(x)   \
    ((x)->indics[0] &= 0xDF,    \
     (x)->indics[0] |= BIT_5_MASK);

#define SET_INFO_REQ_BIT_H(x)   \
    ((x)->indics[0] &= 0x7F,    \
     (x)->indics[0] |= BIT_8_MASK);

#if defined ANSI
#define SET_INFO_REQ_BIT_P(x)   \
    ((x)->indics[1] &= 0x7F,    \
     (x)->indics[1] |= BIT_8_MASK);
#endif

/* 'x' should be a ISUP_INFORMATION_REQUEST_INDICATORS struct. */
#define GET_INFO_REQ_BIT_A(x)   ((x).indics[0] & BIT_1_MASK)
#define GET_INFO_REQ_BIT_B(x)   (((x).indics[0] & BIT_2_MASK)>>1)
#define GET_INFO_REQ_BIT_D(x)   (((x).indics[0] & BIT_4_MASK)>>3)
#define GET_INFO_REQ_BIT_E(x)   (((x).indics[0] & BIT_5_MASK)>>4)
#define GET_INFO_REQ_BIT_H(x)   (((x).indics[0] & BIT_8_MASK)>>7)

#if defined ANSI
#define GET_INFO_REQ_BIT_P(x)   (((x).indics[1] & BIT_8_MASK)>>7)
#endif
 /* End: Information Request Indicators. */

/*
 * Nature of connection indicators:
 * x should be a pointer to ISUP_CONNECTION_INDICATORS struct.
 * sat should be the satellite indicator (bits BA).
 * cont should be the continuity check indicator (bits DC).
 * eco should be the echo control device indicator (bit E).
 */
#define SET_CONN_IND(x,sat,cont,eco)    \
    ((x)->subfields4 &= 0xFFU,                          \
     (x)->subfields4 |= ((sat) & BITS_21_MASK),         \
     (x)->subfields4 |= (((cont)<<2) & BITS_43_MASK),   \
     (x)->subfields4 |= (((eco)<<4) & BIT_5_MASK))

#define SET_CONN_IND_BA_BITS(x,sat) \
    ((x)->subfields4 &= 0xFCU,      \
     (x)->subfields4 |= ((sat) & BITS_21_MASK))

#define SET_CONN_IND_DC_BITS(x,cont)    \
    ((x)->subfields4 &= 0xF3U,          \
     (x)->subfields4 |= (((cont)<<2) & BITS_43_MASK))

#define SET_CONN_IND_E_BIT(x,eco)   \
    ((x)->subfields4 &= 0xDFU,      \
     (x)->subfields4 |= (((eco)<<4) & BIT_5_MASK))

/* x should be a ISUP_CONNECTION_INDICATORS struct. */
#define GET_CONN_IND_BA_BITS(x) ((x).subfields4 & BITS_21_MASK)
#define GET_CONN_IND_DC_BITS(x) (((x).subfields4 & BITS_43_MASK)>>2)
#define GET_CONN_IND_E_BIT(x)   (((x).subfields4 & BITS_5_MASK)>>4)
/* End: Nature of connection indicators. */

/*
 * Redirection Information.
 * 'x' should be a pointer to ISUP_REDIRECTION_INFO structure. 
 * 'in'  should be the redirecting Indicator. 
 * 'orn'  should be the original redirecting reason. 
 * 'cnt' should be the redirection counter. 
 * 'rn'  should be the redirecting reason. 
 */
 
#define SET_RINFO_INDICATOR(x,in)   \
    ((x)->red_info[0] &= 0xF8U,     \
     (x)->red_info[0] |= ((in) & BITS_31_MASK))

#define SET_RINFO_OR_REASON(x,orn)  \
    ((x)->red_info[0] &= 0x0FU,     \
     (x)->red_info[0] |= (((orn)<<4) & BITS_85_MASK))

#if defined CCITT
#define SET_RINFO_COUNTER(x,cnt)    \
    ((x)->red_info[1] &= 0xF8U,     \
     (x)->red_info[1] |= ((cnt) & BITS_31_MASK))
#elif defined ANSI
#define SET_RINFO_COUNTER(x,cnt)    \
    ((x)->red_info[1] &= 0xF0U,     \
     (x)->red_info[1] |= ((cnt) & BITS_41_MASK))
#endif

#define SET_RINFO_REASON(x,rn)  \
    ((x)->red_info[1] &= 0x0FU, \
     (x)->red_info[1] |= (((orn)<<4) & BITS_85_MASK))

/* 'x' should be a pointer to ISUP_REDIRECTION_INFO structure. */
#define GET_RINFO_INDICATOR(x) ((x).red_info[0] & BITS_31_MASK)
#define GET_RINFO_OR_REASON(x) (((x).red_info[0] & BITS_85_MASK)>>4)
#define GET_RINFO_COUNTER(x)   ((x).red_info[1] & BITS_31_MASK)
#define GET_RINFO_REASON(x)    (((x).red_info[1] & BITS_85_MASK)>>4)
/* End: Redirection Information. */


/*
 * User Service Information:
 * 'x' should be a pointer to ISUP_USER_SERVICE_INFO structure. 
 * 'cod' should be the coding standard (octet 1). 
 * 'cap' should be the information transfer capability (octet 1). 
 * 'mod' should be the transfer mode (octet 2). 
 * 'rate' should be the information transfer rate (octet 2 and 2b). 
 * 'struc' should be the structure (octet 2a). 
 * 'conf' should be the configuration (octet 2a).  
 * 'est' should be the Establishment (octet 2a).
 * 'sym' should be the symmetry.
 * 'multi' should be the rate multiplier (octet 2.1 ANSI only). 
 * 'l1' should be the User info Layer 1 Protocol (octet 3). 
 * 'l2' should be the User info Layer 2 Protocol (octet 4).
 * 'l3' should be the User info Layer 3 Protocol (octet 5).
 */
#define SET_USI_OCTET1(x,std,cap)                   \
    ((x)->coding = (0x00),                          \
     (x)->coding |= ISUP_EXT_INDICATOR,             \
     (x)->coding |= (((std)<<5) & BITS_76_MASK),    \
     (x)->coding |= ((cap) & BITS_51_MASK))

#define SET_USI_OCTET1_STD(x,std)       \
    ((x)->coding &= (0x1F),             \
     (x)->coding |= ISUP_EXT_INDICATOR, \
     (x)->coding |= (((cod)<<5) & BITS_76_MASK))
     
#define SET_USI_OCTET1_CAP(x,cap)       \
    ((x)->coding &= (BITS_51_MASK),     \
     (x)->coding |= ISUP_EXT_INDICATOR, \
     (x)->coding |= ((cap) & BITS_51_MASK))

#define SET_USI_OCTET2(x,mod,rate)                      \
    ((x)->trans_mode = (0x00),                          \
     (x)->trans_mode |= (((mod)<<5) & BITS_76_MASK),    \
     (x)->trans_mode |= ((rate) & BITS_51_MASK))

#define SET_USI_OCTET2_MODE(x,std)  \
    ((x)->trans_mode &= (0x9F),     \
     (x)->trans_mode |= (((mod)<<5) & BITS_76_MASK))
     
#define SET_USI_OCTET2_RATE(x,rate) \
    ((x)->trans_mode &= (0xE0),     \
     (x)->trans_mode |= ((rate) & BITS_51_MASK))

#define SET_USI_OCTET2A(x,struc, conf,est)          \
    ((x)->config &= (0x80),                         \
     (x)->config |= (((struc)<<4) & BITS_75_MASK),  \
     (x)->config |= (((conf)<<2) & BITS_43_MASK),   \
     (x)->config |= ((est) & BITS_21_MASK))

#define SET_USI_OCTET2A_STRUCT(x,struc) \
    ((x)->config &= (0x8F),             \
     (x)->config |= (((struc)<<4) & BITS_75_MASK))

#define SET_USI_OCTET2A_CONF(x,conf)    \
    ((x)->config &= (0xF3),             \
     (x)->config |= (((conf)<<2) & BITS_43_MASK))

#define SET_USI_OCTET2A_EST(x,est)  \
    ((x)->config &= (0xFC),         \
     (x)->config |= ((est) & BITS_21_MASK))

#define SET_USI_OCTET2B_SYM(x,sym)          \
    ((x)->symmetry &= (0x9F),               \
     (x)->symmetry |= ISUP_EXT_INDICATOR,   \
     (x)->symmetry |= (((sym)<<5) & BITS_76_MASK))

#define SET_USI_OCTET2B_RATE(x,rate)        \
    ((x)->symmetry &= (0xE0),               \
     (x)->symmetry |= ISUP_EXT_INDICATOR,   \
     (x)->symmetry |= ((rate) & BITS_51_MASK))

#define SET_USI_OCTET2B(x,sym,rate)                 \
    ((x)->symmetry = (0x00),                        \
     (x)->symmetry |= ISUP_EXT_INDICATOR,           \
     (x)->symmetry |= (((sym)<<5) & BITS_76_MASK),  \
     (x)->symmetry |= ((rate) & BITS_51_MASK))

#if defined ANSI
#define SET_USI_OCTET2_1(x,multi)                   \
    ((x)->rate_multiplier = (0x00),                 \
     (x)->rate_multiplier |= ISUP_EXT_INDICATOR,    \
     (x)->rate_multiplier |= ((multi) & BITS_71_MASK))
#endif

#define SET_USI_OCTET3_L1_PROT(x,l1)                            \
    ((x)->layer1 &= ISUP_EXT_INDICATOR,                         \
     (x)->layer1 |= ((ISUP_LAYER_1_IDEN<< 5) && BITS_76_MASK),  \
     (x)->layer1 |= (l1 & BITS_51_MASK))

#define SET_USI_OCTET4_L2_PROT(x,l2)                            \
    ((x)->layer2 &= ISUP_EXT_INDICATOR,                         \
     (x)->layer2 |= ((ISUP_LAYER_2_IDEN<< 5) && BITS_76_MASK),  \
     (x)->layer2 |= (l2 & BITS_51_MASK))

#define SET_USI_OCTET5_L3_PROT(x,l3)                            \
    ((x)->layer3 &= ISUP_EXT_INDICATOR,                         \
     (x)->layer3 |= ((ISUP_LAYER_3_IDEN<< 5) && BITS_76_MASK),  \
     (x)->layer3 |= (l3 & BITS_51_MASK))

/* 'x' should be a ISUP_USER_SERVICE_INFO structure. */
#define GET_USI_OCTET1_STD(x)       (((x).coding & BITS_76_MASK) >> 5)
#define GET_USI_OCTET1_CAP(x)       ((x).coding & BITS_51_MASK)
#define GET_USI_OCTET2_M0DE(x)      (((x).trans_mode & BITS_76_MASK) >> 5)
#define GET_USI_OCTET2_RATE(x)      ((x).trans_mode & BITS_51_MASK)
#define GET_USI_OCTET2A_STRUCT(x)   (((x).config & BITS_75_MASK) >> 4)
#define GET_USI_OCTET2A_CONF(x)     (((x).config & BITS_43_MASK) >> 2)
#define GET_USI_OCTET2A_EST(x)      ((x).config & BITS_21_MASK)
#define GET_USI_OCTET2B_SYMM(x)     (((x).symmetry & BITS_76_MASK) >> 5)
#define GET_USI_OCTET2B_RATE(x)     ((x).symmetry & BITS_51_MASK)

#if defined ANSI
#define GET_USI_OCTET2_1_MULTI(x)   ((x).rate_multiplier & BITS_71_MASK)
#endif

#define GET_USI_OCTET3_L1_PROT(x)   ((x).layer1 & BITS_51_MASK)
#define GET_USI_OCTET4_L2_PROT(x)   ((x).layer2 & BITS_51_MASK)
#define GET_USI_OCTET5_L3_PROT(x)   ((x).layer3 & BITS_51_MASK)
/* End: User Service Information. */


#ifdef CCITT

/*
 * Parameter compatibility Information.
 * nb_param should be the number of upgraded parameters. 
 * len should be param_length of the ITS_ISUP_IE structure. 
 */
#define GET_PARAM_COMPAT_LEN(nb_param) (nb_param * (sizeof(ITS_OCTET) * 3))
#define GET_PARAM_COMPAT_NB_PARAMS(len) (len / (sizeof(ITS_OCTET) * 3))

#endif




#endif
