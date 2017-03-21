/*******************************************************************************
**      FILE NAME:
**          bs_cdef.h
**
**      DESCRIPTION:
**         This files defines the The standards (ITU-T/ETSI/ANSI) which the stack can work.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef _BS_CDEF_H_
#define _BS_CDEF_H_

/* Maximum number of Connections it could support in Class 2 and/or Class 3 */
#define MAX_SCCP_CO_CONNECTIONS    0xFFFF

/* Macros to include/exclude code depending on the standard which has
   been defined at compile time, and the run time configuration */

#if defined(SCCP_ETSI) || defined(SCCP_ANSI) || defined(SCCP_BCGR) || defined(SCCP_CHINESE) || defined(SCCP_JAPANESE)
#define COMPARE_ITU (sc_opt.standard == STACK_ITU)
#elif ( defined(SCCP_ITU) )
#define COMPARE_ITU (SS7_TRUE)
#endif

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ANSI) || defined(SCCP_BCGR) || defined(SCCP_CHINESE)
#define COMPARE_ETSI (sc_opt.standard == STACK_ETSI)
#elif defined (SCCP_ETSI)
#define COMPARE_ETSI (SS7_TRUE)
#endif

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined(SCCP_BCGR) || defined(SCCP_CHINESE)
#define COMPARE_ANSI (sc_opt.standard == STACK_ANSI) 
#elif defined (SCCP_ANSI)
#define COMPARE_ANSI (SS7_TRUE)
#endif

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined(SCCP_ANSI) || defined(SCCP_CHINESE)
#define COMPARE_BCGR (sc_opt.standard == STACK_BCGR)
#elif defined (SCCP_BCGR)
#define COMPARE_BCGR (SS7_TRUE)
#endif


#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined(SCCP_ANSI) || defined(SCCP_BCGR)
#define COMPARE_CHINESE (sc_opt.standard == STACK_CHINESE)
#elif defined (SCCP_CHINESE)
#define COMPARE_CHINESE (SS7_TRUE)
#endif

#if  defined(SCCP_ITU) || defined(SCCP_ETSI) || defined(SCCP_ANSI) || defined(SCCP_CHINESE) || defined(SCCP_BCGR)
#define COMPARE_JAPANESE (sc_opt.standard == STACK_JAPANESE)
#elif defined (SCCP_JAPANESE)
#define COMPARE_JAPANESE (SS7_TRUE)
#endif

#endif /* _BS_CDEF_H_ */

