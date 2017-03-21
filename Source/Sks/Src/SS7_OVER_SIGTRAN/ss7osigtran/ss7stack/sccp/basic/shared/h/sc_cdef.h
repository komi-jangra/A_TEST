/***************************************************************************
**  FILE NAME:
**      sc_cdef.h
**
****************************************************************************
**
**  FUNCTION:
**      Compile time definitions to build SCCP
**
**  DESCRIPTION:
**      Contains
**      1. The standards (ITU-T/ETSI/ANSI) which the stack can work as
**      2. Size of database (for signaling points, subsystems and concerned
**                           signaling points and concerned subsystems)
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  12May'98 Sriganesh. Kini   -----  Original
**	20Aug'98 Anil K,			----  Stack definitions removed.
**	06Mar'02 Sachin bhatia 		----  Chinese Macro Corrected.
**  24Jul'02 Salil Agrawal      ----  Fixed Spr 9341.
**  21Nov'03 knaveen            ----  Fixed Spr 13075.
**  25Feb'04 Hitesh Sharma      ----  Fixed Spr 13263
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_CDEF_H_
#define _SC_CDEF_H_

/* Fix for SPR No : 13263 start */ 
#if 0
/* define max values for the SCCP network configuration */
/* Start Spr 13075 Fix */
/* This hash define is commented and the MAX_SP will be init time parameter */
/* #define MAX_SP   20 */ /* Maximum number of signaling point in the SCCP network */
extern U32bit MAX_SP;
/* Stop Spr 13075 Fix */
#define MAX_SS   60  /* Maximum number of subsystem in the SCCP network */
/* Start Spr 13075 Fix */
/* This will be equal to the MAX_SP and is replaced by MAX_SP */
/* #define MAX_CSP  60  */ /* Maximum concerned signaling points */
/* Stop Spr 13075 Fix */
#define MAX_CSS  60  /* Maximum concerned subsystems */

#endif

#define SCCP_MAX_SS_VALUE    1024
#define SCCP_MAX_SP_VALUE    1024
#define SCCP_MAX_CSS_VALUE   1024
#define SCCP_MAX_CSP_VALUE   1024


extern U32bit MAX_SS ;
extern U32bit MAX_SP ;
extern U32bit MAX_CSS ;
extern U32bit MAX_CSP ;

/* Fix for SPR No : 13263 end */ 

/* Maximum number of Connections it could support in Class 2 and/or Class 3 */
#define MAX_SCCP_CO_CONNECTIONS   65535 /*1048576*/  /*0xFFFFFFFF*/

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

/* start spr #9341 */
#if 0
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined(SCCP_ANSI) || defined(SCCP_CHINESE)
#define COMPARE_CHINESE (sc_opt.standard == STACK_CHINESE)
#elif defined (SCCP_CHINESE)
#define COMPARE_CHINESE (SS7_TRUE)
#endif
#endif /* end of if 0 */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined(SCCP_ANSI) || defined(SCCP_BCGR)
#define COMPARE_CHINESE (sc_opt.standard == STACK_CHINESE)
#elif defined (SCCP_CHINESE)
#define COMPARE_CHINESE (SS7_TRUE)
#endif
/* end of spr # 9341 */

/* start spr # 9341 */
#if 0
/* We introduce COMPARE_JAPANESE FLAG HERE ... The Red DOT is missin :o) - Sachin */
#if  defined(SCCP_ITU) || defined(SCCP_ETSI) || defined(SCCP_ANSI) || defined(SCCP_CHINESE) || defined(SCCP_CHINESE)
#define COMPARE_JAPANESE (sc_opt.standard == STACK_JAPANESE)
#elif defined (SCCP_JAPANESE)
#define COMPARE_JAPANESE (SS7_TRUE)
#endif
#endif /* end of if 0 */

#if  defined(SCCP_ITU) || defined(SCCP_ETSI) || defined(SCCP_ANSI) || defined(SCCP_CHINESE) || defined(SCCP_BCGR)
#define COMPARE_JAPANESE (sc_opt.standard == STACK_JAPANESE)
#elif defined (SCCP_JAPANESE)
#define COMPARE_JAPANESE (SS7_TRUE)
#endif
/* end of spr # 9341 */

#endif /* _SC_CDEF_H_ */

