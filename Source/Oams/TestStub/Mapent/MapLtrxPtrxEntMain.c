#include "MapLtrxPtrxEntInc.h"
#include "DBLIBError.h"
#include "oams_include.h"

I_Void Test_PtrxDown_Resp();
I_Void Test_CellLock_Resp();
I_Void Test_MapEnt_Trxh_Cre_Map_Failed();
I_Void Test_InitMap_PtrxDown();


int main ()
{
   I_U32    ptrxId;   
   I_S32    errCode;
   I_U8     choice;

   printf("\n::::In function Test Stub Main::::\n");
   errCode = dbConnect();

   if( errCode == 0)
   {
     printf("::::Db Connection Status::::Success\n");
   }
   else
   {
      printf("Db could not be connected errcode is %d ", errCode);
      return I_FALSE;
   }

 while(1)
 {
    fprintf(stderr,"\n --------- Enter your choice "); 
   
    fprintf(stderr,"\n ---------OAMS_MAPENT_TRXH_CRE_LTRX_PTRX_MAPPING_FAILED ");

    fprintf(stderr,"\n ---------OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP ");
   
    fprintf(stderr,"\n --------- Invoke the main Map entity loop");

    fprintf(stderr,"\n --------- OAMS_MAPENT_CELLH_DEL_MAP_RESP");
   
    scanf("%d",&choice);

    switch ( choice )
    {
       case 1:        
 
          /* Test OAMS_MAPENT_TRXH_CRE_LTRX_PTRX_MAPPING_FAILED */
           Test_MapEnt_Trxh_Cre_Map_Failed();
           break; 
       case 2:                    
           Test_PtrxDown_Resp();
           break;

      case 3:           
           Test_InitMap_PtrxDown();
           break;
       
      case 4:               
          Test_CellLock_Resp();
          break;

     default:         
           Test_InitMap_PtrxDown();
           break;
    }
 }


   dbDestroy();
   return I_TRUE;
}


I_Void Test_PtrxDown_Resp()
{
    I_U32   sndMsgSize;
   I_PVoid dataPtr = NULL; 
   OamsTrxhMapentDelLtrxPtrxMappingResp *msgPtr  = NULL;
   OamsMapentCellhDelMapResp *rcvdMsgPtr = NULL;
 
    LtrxTableIndices ltrxIdIndice;
    LtrxTableApi     *ltrxIdRowData;
  
    PtrxTableIndices ptrxIdIndice;
    PtrxTableApi     *ptrxIdRowData;
    I_S32            errCode;

   I_U16 invMode = OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP; 
   

   sndMsgSize = sizeof(OamsTrxhMapentDelLtrxPtrxMappingResp);
   dataPtr     = AlocMsgBuf(sndMsgSize);
   msgPtr  = (OamsTrxhMapentDelLtrxPtrxMappingResp*)dataPtr;

   FILL_SYS_HDR(msgPtr,OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP,MSG_SUB_TYPE, PRCR_CP,
               ENT_OAMS_TRXH ,ZERO , PRCR_CP,ENT_OAMS_CELLH, ZERO);

   msgPtr->ptrxId = 21;
   msgPtr->ltrxId = 11;
   msgPtr->cellId = 1;
   msgPtr->lac    = 2;
   
   MappingLtrxPtrxEntity(invMode, dataPtr);

   rcvdMsgPtr = (OamsMapentCellhDelMapResp*)(dataPtr);

   /* Print the data ptr filled and received from Map entity.
    * The data received will be of type OamsMapentCellhDelMapResp
   
   */
   printf("\n::::CreateMsgMapentCellhDelMapResp in case of PTRX Going down::::\n");
   printf("\nCell Id is %d ",rcvdMsgPtr->cellId);
   printf("\nlac is %d ", rcvdMsgPtr->lac);    

   /* Fill the ltrx id for which the record has to be retreived */
    ltrxIdIndice.ltrxId = 11;

    /* Get the Ltrx record for the specified Ltrx Id */
    errCode =  getLtrxTable (&ltrxIdIndice, &ltrxIdRowData );
    if ( errCode != CLIB_SUCCESS )
    {
      printf("Failed to retreive from Ltrx table in Test_MapEnt_Trxh_Cre_Map_Failed");
      return;
    }

    printf("\nMapping Status in Ltrx Table is:: %d ",ltrxIdRowData->mappingStatus);


   /* Fill the ptrx id for which the record has to be retreived */
     ptrxIdIndice.ptrxId = 21;

    /* Get the Ltrx record for the specified Ltrx Id */
    getPtrxTable (&ptrxIdIndice, &ptrxIdRowData );
    printf("\nMapping Status in Ptrx table is  %d ",ptrxIdRowData->mappingStatus);
   
   printf("\n::::CreateMsgMapentCellhDelMapResp in case of Cell lock::::\n");
   msgPtr->ptrxId = 12;
   msgPtr->ltrxId = 10;
   
   MappingLtrxPtrxEntity(invMode, dataPtr);

   rcvdMsgPtr = (OamsMapentCellhDelMapResp*)(dataPtr);
      
   printf("\nCell Id is %d ",rcvdMsgPtr->cellId);
   printf("\nlac is %d \n", rcvdMsgPtr->lac);    
   DalocMsgBuf(dataPtr);
  
}


I_Void Test_CellLock_Resp()
{
  I_U32   sndMsgSize;
  I_PVoid dataPtr = NULL;
  I_PVoid tempBuf =NULL; 
  OamsCellhMapentDelMapReq *msgPtr  = NULL;
  OamsMapentCellhDelMapResp *rcvdMsgPtr = NULL;

  I_U16 invMode = OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP;

   sndMsgSize = sizeof(OamsCellhMapentDelMapReq);
   dataPtr     = AlocMsgBuf(sndMsgSize);
   msgPtr = (OamsCellhMapentDelMapReq *)dataPtr;

   FILL_SYS_HDR(msgPtr,OAMS_CELLH_MAPENT_DEL_MAP_REQ,MSG_SUB_TYPE, PRCR_CP,
               ENT_OAMS_TRXH ,ZERO , PRCR_CP,ENT_OAMS_CELLH, ZERO);

  
   msgPtr->cellId = 1;
   msgPtr->lac    = 2;
   

   MappingLtrxPtrxEntity(invMode, dataPtr);


    rcvdMsgPtr = (OamsMapentCellhDelMapResp*)(dataPtr);
   /* Print the data ptr filled and received from Map entity.
    * The data received will be of type OamsMapentCellhDelMapResp
   
   */
   printf("\n CreateMsgMapentCellhDelMapResp in case of Cell Lock\n");
   printf("\nCell Id is%d ", rcvdMsgPtr->cellId);
   printf("\nlac is%d ", rcvdMsgPtr->lac);      
   DalocMsgBuf(dataPtr);
}


I_Void Test_MapEnt_Trxh_Cre_Map_Failed()
{
   I_U32   sndMsgSize;
  I_PVoid dataPtr = NULL; 
  OamsTrxhMapentCreLtrxPtrxMappingFailed *msgPtr  = NULL;
  I_U16 invMode = OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED;
  I_S32 errCode;
  LtrxTableIndices ltrxIdIndice;
  LtrxTableApi     *ltrxIdRowData;
  PtrxTableIndices ptrxIdIndice;
  PtrxTableApi     *ptrxIdRowData;

  ltrxIdIndice.ltrxId = 11;
  ptrxIdIndice.ptrxId = 1;

  
  sndMsgSize = sizeof(OamsTrxhMapentCreLtrxPtrxMappingFailed);
  msgPtr  =(OamsTrxhMapentCreLtrxPtrxMappingFailed*) AlocMsgBuf(sndMsgSize);
  dataPtr  = (I_Void *)msgPtr;
  
  // dataPtr     = AlocMsgBuf(sndMsgSize);
  // msgPtr = (OamsCellhMapentDelMapReq *)dataPtr;
  FILL_SYS_HDR(msgPtr,OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED,MSG_SUB_TYPE, PRCR_CP, ENT_OAMS_TRXH ,ZERO , PRCR_CP,ENT_OAMS_CELLH, ZERO);

  
   msgPtr->ptrxId = 1;
   msgPtr->ltrxId = 11;
   
   MappingLtrxPtrxEntity(invMode, dataPtr);

   errCode = getLtrxTable(&ltrxIdIndice, &ltrxIdRowData);

   printf ("\n:::: OamsTrxhMapentCreLtrxPtrxMappingFailed in case of PTRX Going Down::::\n ");
   if (errCode != CLIB_SUCCESS)
   {
      printf("Failed to retreive from Ltrx table in Test_MapEnt_Trxh_Cre_Map_Failed");
      DalocMsgBuf(msgPtr);
      return;
   }

   else
   {
       printf( "\n Ltrx Mapping Status is %d \n", ltrxIdRowData->mappingStatus);
   }

   errCode = getPtrxTable(&ptrxIdIndice, &ptrxIdRowData);

   if (errCode != CLIB_SUCCESS)
   {
       printf("Failed to retreive from Ptrx table in Test_MapEnt_Trxh_Cre_Map_Failed");
       DalocMsgBuf(msgPtr);
       return;
   }
   else
   {
       printf( "\n Ptrx Mapping Status is %d \n", ptrxIdRowData->mappingStatus);
   }

  DalocMsgBuf(msgPtr);
}


I_Void Test_InitMap_PtrxDown()
{
  I_PVoid dataPtr = NULL;
  I_U16 invMode;
  MappingLtrxPtrxEntity(invMode, dataPtr);
}

