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
 *  ID:$Id: ss7_alarms.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:00  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:53:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.2.1.38.3  2005/01/24 10:42:40  snagesh
 * LOG: Moved MTP2_ALARM_START and MTP2_ALARM_END from mtp2_alarm.h
 * LOG:
 * LOG: Revision 7.8.2.1.38.2  2004/12/31 06:03:22  sbabu
 * LOG: TCAP and MTP3 OAM changes
 * LOG:
 * LOG: Revision 7.8.2.1.38.1  2004/12/06 14:04:18  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.8.2.1  2003/05/07 09:41:49  ssingh
 * LOG: ANSI Alarms max limit increased.
 * LOG:
 * LOG: Revision 7.8  2003/02/03 12:15:46  aganguly
 * LOG: Changes for SCCP alarms: clean up of unwanted alarms left for Release 6.4
 * LOG:
 * LOG: Revision 7.7  2003/01/30 12:24:14  ssingh
 * LOG: ISUP ansi alarms MAX value increased.
 * LOG:
 * LOG: Revision 7.6  2002/11/20 11:34:03  akumar
 * LOG: Modified the range for ANSI_ISUP_ALARMs
 * LOG:
 * LOG: Revision 7.5  2002/11/20 04:55:43  ttipatre
 * LOG: Modifying Log indentation.
 * LOG:
 * LOG: Revision 7.4  2002/11/20 04:48:01  ttipatre
 * LOG: Adding MTP3 ANSI Alarms
 * LOG:
 * LOG: Revision 7.3  2002/11/11 11:20:30  akumar
 * LOG: Code added for Automatic Congestion Control, ANSI ISUP Alarms and modified
 * LOG: the signature of __ISUP_IsExchangeControlling() func to include the new
 * LOG: argument.
 * LOG:
 * LOG: Revision 7.2  2002/10/10 11:16:03  sjaddu
 * LOG: ITU Alarm range is modified.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/06/13 20:30:11  ttipatre
 * LOG: Adding MTP3 Alarms
 * LOG:
 * LOG: Revision 6.4  2002/05/08 18:28:41  mmiers
 * LOG: Alarm level handling.  Start of OAM implementation
 * LOG:
 * LOG: Revision 6.3  2002/03/22 14:41:47  ngoel
 * LOG: add sccp alarm
 * LOG:
 * LOG: Revision 6.2  2002/03/22 14:27:39  ngoel
 * LOG: add ccitt sccp alarms
 * LOG:
 * LOG: Revision 6.1  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 * LOG: Revision 1.1.2.2  2001/12/20 21:26:16  pkelly
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.2.1  2001/12/20 19:13:25  pkelly
 * LOG: DSM - Alarms - PegCounters
 * LOG:
 ****************************************************************************/

#ifndef SS7_ALARMS_H
#define SS7_ALARMS_H

#include <its_alarm.h>

/*
 * ranges
 */
#define ANSI_SCCP_ALARM_START    401
#define ANSI_SCCP_ALARM_END      823 
#define CCITT_SCCP_ALARM_START   401
#define CCITT_SCCP_ALARM_END     823
#define ANSI_TCAP_ALARM_START    1001
#define ANSI_TCAP_ALARM_END      1059
#define CCITT_TCAP_ALARM_START   1401
#define CCITT_TCAP_ALARM_END     1455
#define ANSI_MTP3_ALARM_START    2401
#define ANSI_MTP3_ALARM_END      2801
//#define ANSI_MTP3_ALARM_END      2128
#define CCITT_MTP3_ALARM_START   2401
//#define CCITT_MTP3_ALARM_END     2528
#define CCITT_MTP3_ALARM_END     2801
#define ANSI_ISUP_ALARM_START    3001
#define ANSI_ISUP_ALARM_END      3305   /* Change this value in case more */
#define CCITT_ISUP_ALARM_START   3401
#define CCITT_ISUP_ALARM_END     3504 /* Change this value in case more */

#define MTP2_ALARM_START        12000
#define MTP2_ALARM_END          12027

/*
 * formats
 */
extern ALARM_Format *CCITT_MTP3_Alarms[];
extern ALARM_Format *ANSI_MTP3_Alarms[];
extern ALARM_Format *CCITT_ISUP_Alarms[];
extern ALARM_Format *ANSI_ISUP_Alarms[];
extern ALARM_Format *CCITT_SCCP_Alarms[];
extern ALARM_Format *ANSI_SCCP_Alarms[];
extern ALARM_Format *CCITT_TCAP_Alarms[];
extern ALARM_Format *ANSI_TCAP_Alarms[];

/*
 * levels
 */
extern ITS_UINT MTP3_AlarmLevel_ANSI;
extern ITS_UINT MTP3_AlarmLevel_CCITT;
extern ITS_UINT SCCP_AlarmLevel_ANSI;
extern ITS_UINT SCCP_AlarmLevel_CCITT;
extern ITS_UINT ISUP_AlarmLevel_ANSI;
extern ITS_UINT ISUP_AlarmLevel_CCITT;
extern ITS_UINT TCAP_AlarmLevel_ANSI;
extern ITS_UINT TCAP_AlarmLevel_CCITT;

/*
 * APIs
 */
void    MTP3_Alarm_ANSI(int which, const char *file, const int line,
                        char *format, ...);
void    MTP3_Alarm_CCITT(int which, const char *file, const int line,
                         char *format, ...);
ITSSS7DLLAPI void    ISUP_Alarm_ANSI(int which, const char *file, const int line,
                        char *format, ...);
ITSSS7DLLAPI void    ISUP_Alarm_CCITT(int which, const char *file, const int line,
                         char *format, ...);
void    SCCP_Alarm_ANSI(int which, const char *file, const int line,
                        char *format, ...);
void    SCCP_Alarm_CCITT(int which, const char *file, const int line,
                         char *format, ...);
void    TCAP_Alarm_ANSI(int which, const char *file, const int line,
                        char *format, ...);
void    TCAP_Alarm_CCITT(int which, const char *file, const int line,
                         char *format, ...);

#endif /* SS7_ALARM_H */
