/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oamsswmh_datasruct.h
 PURPOSE           :  Contains SWMH Data struct
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSSWMH_DATASTRUCT_H
#define __OAMSSWMH_DATASTRUCT_H

typedef struct
{
   NodeType                       nodeType;
   NodeIdentity                   nodeId;
   ApplTei                        applTei;
   I_S8                           swVersion[MAX_SW_VERSION_LENGTH];
   I_S8                           binaryPath[OAMS_CMD_PARAM_MAX_SIZE];
}OamsSwmhContext;


#endif   /* __OAMSSWMH_DATASTRUCT_H  */ 


