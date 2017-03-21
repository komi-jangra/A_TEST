/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oamsdsph_hashdefs.h
 PURPOSE           :  Contains Dsph Hashdefs
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  R2-BSC Team
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSDSPH_HASHDEFS_H
#define __OAMSDSPH_HASHDEFS_H

#define MAX_DSP_IN_SYSTEM          6

#define DSPH_HANDLER               1

#define ZERO                       0
#define ONE                        1
#define FOUR                       4

#define PARENT_LOCKED              0
#define PARENT_UNLOCKED            1

#define DSP_DOWN                   2
#define DSP_UP                     3

#define PRESENT                    1
#define NOT_PRESENT                0

#define DSPH_SUCCESS               DSP_TEST_PASS
#define DSPH_FAILURE               DSP_TEST_FAIL

#define DSP_ON_SLOT3               0
#define DSP_ON_SLOT4               1

#define ACTIVE_ICC_CARD                 1
#define STANDBY_ICC_CARD                2

#define ICC_CARD_SLOT3                  3
#define ICC_CARD_SLOT4                  4

/* R2.9 changes starts*/
#define DSP_STATE_UNLOCKED_ENABLED      1
#define DSP_STATE_UNLOCKED_DISABLED     2
#define DSP_STATE_LOCKED_DISABLED       3
/* R2.9 changes ends */

#define DSP_INIT_SIZE                    (sizeof(DTrauMgsDspInitReq)-(sizeof(SysHdr)+sizeof(tHdr)))
#define DSP_TRIGGER_SIZE                 (sizeof(DTrauMgsDspTriggerReq)-(sizeof(SysHdr)+sizeof(tHdr)))
#define DSP_TRAUSTART_SIZE               (sizeof(DTrauMgsTrauStartReq)-(sizeof(SysHdr)+sizeof(tHdr)))
#define DSP_TRAU_CONF_DECONF_RESP_SIZE   (sizeof(OamsDsphGrhmTrauChanConfResp)-(sizeof(SysHdr)+sizeof(tHdr)))
#define DSP_TRAU_CONF_REQ_SIZE           (sizeof(CsappGrhmDsphTrauChanConfReq)-(sizeof(SysHdr)+sizeof(tHdr)))
#define DSP_TRAU_DECONF_REQ_SIZE         (sizeof(CsappGrhmDsphTrauChanDeconfReq)-(sizeof(SysHdr)+sizeof(tHdr)))
/* Added for RTP specific messages */
#define DSP_RTP_TRAU_CONF_REQ_SIZE       (sizeof(CsappGrhmDsphRtpTrauChanConfReq)-(sizeof(SysHdr)+sizeof(tHdr)))
#define DSP_RTP_TRAU_CONF_DECONF_RESP_SIZE   (sizeof(OamsDsphGrhmRtpTrauChanConfResp)-(sizeof(SysHdr)+sizeof(tHdr)))
#define DSP_RTP_TRAU_DECONF_REQ_SIZE         (sizeof(CsappGrhmDsphRtpTrauChanDeconfReq)-(sizeof(SysHdr)+sizeof(tHdr)))
#define DSP_RTP_INIT_SIZE                    (sizeof(DTrauMgsRtpDspInitReq)-(sizeof(SysHdr)+sizeof(tHdr)))
/* Added for RTP specific messages */



#define DSP_TRAU_CONF_REQ_SIZE           (sizeof(CsappGrhmDsphTrauChanConfReq)-(sizeof(SysHdr)+sizeof(tHdr)))

#define DSP_OPRSTATE_DISABLED         DISABLED
#define DSP_OPRSTATE_ENABLED          ENABLED

#define DEFAULT_TIMERVAL               20
#define DEFAULT_MAX_RETRY              10

#define FAIL                           0xff
#define INVALID                        0xff

#define SW_ACT_IN_PROGRESS            CM_ERR_SW_DSP_ACT_IN_PROGRESS
#define SW_DWNLD_OR_ACT_IN_PROGRESS   CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS /*Added For Mantis 16805*/

/* R2.4 Changes : Starts */
#define MAX_CORE                   4
#define MAX_DSP_TRAU_INDEX        32

#define OAMS_SUCCESS              1
#define OAMS_FAILURE              0


#define TIMER_STOPED              0
#define TIMER_STARTED             1

/* R2.4 Changes : Starts */

// mantis 11095

#define DSP_LOCKED              4
#define DSP_UNLOCKED            5

/* Possible DSP Types */
#define DSP_TYPE_TDM            1
#define DSP_TYPE_RTP            2



#endif  /*__OAMSDSPH_HASHDEFS_H */
