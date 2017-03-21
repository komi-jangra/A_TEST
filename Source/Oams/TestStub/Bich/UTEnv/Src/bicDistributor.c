#include <includes.h>
unsigned char tcResult = 1;
I_PU8 msgRcvP ;
I_PVoid sndMsgP ;
I_U32 gTei, gBtsId;
I_U32 gLapdLinkStatus;
I_U32 gOprState;
I_U32 gTrxId;
I_U32 gE1Id;
I_U32 gTsVal;
I_U32 gBtsType;
I_U32 gAdminState;
I_U32 gTrxOpr;
I_Void RcvMsg(I_PVoid msgPtr);
I_PVoid SndMsg( I_U32 msgOpCode, I_U32 srcEntId)
{
   LOG_PRINT(INFO,"%s:",__func__);
  
   switch(srcEntId)
   {
     case  ENT_OAMS_CFG:
     {
      SendCfgMsg(msgOpCode);
      break;
     }
     case ENT_CSAPP_ABIHM:
      {
       SendAbihmMsg(msgOpCode);
       break;
      }
   case ENT_OAMS_TRXH :
      {
       SendTrxhMsg(msgOpCode);
       break;
      }
   }
}
I_Void RcvMsg(I_PVoid msgPtr)
{
  LOG_PRINT(INFO,"%s:",__func__);
  I_U32 msgOpCode;
  msgRcvP = msgPtr;
  switch (READ_MSG_TYPE()) { 
    case OAMS_BICH_CFG_ADD_BIC_RESP: 
      LOG_PRINT(INFO, "Msg Rcvd OAMS_BICH_CFG_ADD_BIC_RESP" );
      if (((OamsBichCfgAddBicResp *) RCVD_MSG_PTR)->result != OAMS_RSLT_SUCCESS) {
        tcResult=FAIL;
      }
      return;
    case OAMS_BICH_CFG_LOCK_RESP: 
      LOG_PRINT(INFO, "Msg Rcvd OAMS_BICH_CFG_LOCK_RESP" );
      if (((OamsBichCfgLockResp *) RCVD_MSG_PTR)->result != OAMS_RSLT_SUCCESS) {
        tcResult=FAIL;
      }
      return;
    case OAMS_BICH_CFG_UNLOCK_RESP: 
      LOG_PRINT(INFO, "Msg Rcvd OAMS_BICH_CFG_UNLOCK_RESP" );
      if (((OamsBichCfgLockResp *) RCVD_MSG_PTR)->result != OAMS_RSLT_SUCCESS) {
        tcResult=FAIL;
      }
      return;
    default :;
  }
  return ;
}

I_Void checkBicStatusTable(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  BicStatusTableApi *dbData;
  BicStatusTableIndices   indices;

  indices.bicId = gBtsId;
  if ( (getBicStatusTable(&indices, &dbData)) != CLIB_SUCCESS )
  {
     tcResult=FAIL;
  }
  else
  {
     if (dbData->bicId == gBtsId && dbData->lapdLinkStatus == gLapdLinkStatus && dbData->oprState ==  gOprState )
     {
     }
     else
     {
         tcResult=FAIL;
     }
     free ( dbData );
  }   

  return ;
}
