
#ifndef __OAMS_PSCH_DATASTRUCT_H
#define __OAMS_PSCH_DATASTRUCT_H
 /* Changes for HotStb start here     */
typedef struct 
{
  I_U16 cellIndex;
  I_U16 bvcId;
  I_U16 finalState;
  I_U16 lac;
  I_U16 cellId; 
  I_U16 cellNumPsTrx;
  I_U8 bvcLockPending;
  I_U8 cellBarStatus;
  I_U8 oldAvailPs;
  I_U8 oldRelPs;
  I_U8 cellLockInProg;
  I_U16 gbIfStatus;
  I_U16 provResult;
  I_U8 isCblChanged;
  I_U8 cellShutdown;
  I_U8 egprsAllowed;
}PschRedCtxt;
 /* Changes for HotStb end here     */

#endif 
