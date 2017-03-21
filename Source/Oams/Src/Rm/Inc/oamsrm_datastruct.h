/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oamscellh_datastruct.h
 PURPOSE           :  Contains Cell Handler Data struct
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/
#ifndef __OAMSRM_DATASTRUCT_H
#define __OAMSRM_DATASTRUCT_H

typedef struct
{
       SysHdr  sHdr;
       I_U32 srcE1;
       I_U32 srcTs;
       I_U32 destE1;
       I_U32 destTs;
}OamsRmCpifPeerSwitchConnect;
typedef OamsRmCpifPeerSwitchConnect TcpCpifRmPeerSwitchConnect;

typedef struct
{
       SysHdr  sHdr;
       I_U32 srcE1;
       I_U32 srcTs;
}OamsRmCpifPeerSwitchConnectAck;
typedef OamsRmCpifPeerSwitchConnectAck TcpCpifRmPeerSwitchConnectAck;

typedef struct
{
       SysHdr  sHdr;
       I_U32 srcE1;
       I_U32 srcTs;
       OamsCause cause;
}OamsRmCpifPeerSwitchConnectNack;
typedef OamsRmCpifPeerSwitchConnectNack TcpCpifRmPeerSwitchConnectNack;

typedef struct
{
   SysHdr sHdr;
}OamsRmCpifSlotReq;

typedef OamsRmCpifSlotReq TcpCpifRmSlotReq;

typedef struct
{
   SysHdr sHdr;
   I_U8 mySlotId;
   I_U8 peerSlotId;
}OamsRmCpifSlotResp;
typedef OamsRmCpifSlotResp TcpCpifRmSlotResp;

typedef struct
{
       SysHdr  sHdr;
}OamsRmCellhAIPReq;

typedef OamsRmCellhAIPReq OamsRmTrxhAIPReq;
typedef OamsRmCellhAIPReq OamsRmGrhmAIPReq;
typedef OamsRmCellhAIPReq OamsRmBichAIPReq;

typedef struct
{
       SysHdr  sHdr;
}OamsRmCellhActiveReq;

typedef OamsRmCellhActiveReq OamsRmTrxhActiveReq;
typedef OamsRmCellhActiveReq OamsRmGrhmActiveReq;
typedef OamsRmCellhActiveReq OamsRmBichActiveReq;
//void SendBpmNotification(I_S8 );
//I_U32 rmSendMessage(void*, I_U32 , I_S32 ,I_S32 ,I_U16 , I_U8 );
#endif /* __OAMSCELLH_DATASTRUCT_H */
