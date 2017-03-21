/***************************************************************************
**  FUNCTION:
** 	Contains version definitions for SCCP     
**
****************************************************************************
**
**  FILE NAME:
**      sc_ver.h
**
**  DESCRIPTION:
**      This file contains definitions of the major and minor versions,
**	and the different standard versions for the SCCP module
**
**  DATE          NAME              REF#   REASON
**  -------       --------------    -----  --------------------------------
**  02Sept'99 	  Sudipta Pattar    -----  Original
**
**  Copyright 1999, Hughes Software Systems
***************************************************************************/

#ifndef _SC_VER_H_
#define _SC_VER_H_

/* Module version number */
#define SCCP_MAJOR_VERSION_NO	0x06    /* Major release number */
#define SCCP_MINOR_VERSION_NO   0x00	/* Minor release number */

/* Standard versions */

#define SCCP_ITU_1996		0x00
#define SCCP_ETSI_1997		0x01
#define SCCP_ANSI_1996		0x02
#define SCCP_BCGR_1997		0x03

#define SCCP_STANDARD_ITU_VERSION	SCCP_ITU_1996
#define SCCP_STANDARD_ETSI_VERSION	SCCP_ETSI_1997
#define SCCP_STANDARD_ANSI_VERSION	SCCP_ANSI_1996
#define SCCP_STANDARD_BCGR_VERSION 	SCCP_BCGR_1997

#endif
