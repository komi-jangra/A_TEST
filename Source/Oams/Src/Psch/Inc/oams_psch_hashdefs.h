/*************************************************************** File Header ***
   File Name      : oams_psch_pschheaders.h                                   *
   Purpose        : Contains the heshdefs used in psch module                 *
   Project        : BSS                                                       *
   Subsystem      : OAMS                                                      *
   Author         : Aricent TEAM                                              *
   Created        :                                                           *
   CSCI id        :                                                           *
   Version        : 0.1                                                       *
*********************************************************************** End **/

# ifndef _OAMS_PSCH_PSCHHEADER_H

#define DOWN 0
#define UP 1
#define INVALID -1
#define SUPPORTED 1
#define PSCH_SUCCESS  0
#define PSCH_FAILURE  1
/* Bvc Reset Cause */
#define NETWORK_SERVICE_FAILURE 0x02
#define NETWORK_SERVICE_TRANSMISSION_MODIFIED 0x03
#define BVCI_UNKNOWN 0x05
#define BVCI_BLOCKED 0x09
/* BVC Pdu Types */
#define BVC_BLOCK            0x20
#define BVC_RESET            0x22
#define BVC_RESET_ACK        0x23
#define BVC_UNBLOCK          0x24
#define FLOW_CONTROL_BVC     0x26
/*macro for converting millisec to sec and millisec to nanosec*/
#define MILLISSEC_TO_SEC(millisec)  (millisec/1000)
#define REM_MILLISSEC_TO_NANOSEC(millisec) ((millisec%1000)*1000000)
#define ENABLED 1
#define WAITINGBVCUNPROVACK 2
#define GBDOWN 3
#define CELLIDLE 4
#define WAITBVCPROVACK 5
#define BLOCKED 6
#define WAITBVCUNBLOCKACK 7
#define WAITBVCRESETACK 8
#define WAITBVCBLOCKACK 9

/* nse feature */
#define NSE_UNLOCKED 1
#define NSE_LOCKED 0


#endif
