#include <oamcfg_includes.h>
extern I_U32 gTestCaseCompleted;

void insertMtp3LinksetStsTableApi()
{
   Mtp3LinksetStsTableApi Mtp3LinksetStsTableApiBuff;
   Mtp3LinksetStsTableApiBuff.MTP3LinksetlinksetID =1;
   Mtp3LinksetStsTableApiBuff.oprState=1;
   insertMtp3LinksetStsTable(&Mtp3LinksetStsTableApiBuff);
}
void cfgCmDbHndlr44()
{
   static int testInitiation =1;
   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinksetTableApi mtp3LinksetTblApiBuff= {0};   
   Mtp3LinksetTableIndices Mtp3LinksetTableIndicesBuff;      
   I_S32 errCode = 0;
   I_S32 count = 0;   

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr44: Mtp3LinksetTable Update Request - with MTP3LinksetlinksetID not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinksetTableIndicesBuff.MTP3LinksetlinksetID= 1;
      deleteMtp3LinksetTable(&Mtp3LinksetTableIndicesBuff);

      /* Send Mtp3LinksetTable Update Request - with MTP3LinksetlinksetID not in DB */
      mtp3LinksetTblApiBuff.MTP3LinksetlinksetID= 1;
      mtp3LinksetTblApiBuff.mtp3Linksetlpc = 2;
      mtp3LinksetTblApiBuff.mtp3Linksetapc = 2;
      mtp3LinksetTblApiBuff.mtp3Linksetni = 10;

      printf("\n cfgCmDbHndlr44: Mtp3LinksetTable Insert Request - with MTP3LinksetlinksetID not in DB, sending");
      cfgStubSendCmMessage(&mtp3LinksetTblApiBuff, sizeof(Mtp3LinksetTableApi),BSC_API_SET_MTP3LINKSETTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3LINKSETTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3LINKSETTABLE,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr44: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr44: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr44: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr44 */

void cfgCmDbHndlr45()
{
   static int testInitiation =1;
   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinksetTableApi mtp3LinksetTblApiBuff= {0};   
   Mtp3LinksetTableIndices Mtp3LinksetTableIndicesBuff;      
   I_S32 errCode = 0;
   I_S32 count = 0;   

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr45: Mtp3LinksetTable Testing Parameter Modification");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinksetTableIndicesBuff.MTP3LinksetlinksetID= 1;
      deleteMtp3LinksetTable(&Mtp3LinksetTableIndicesBuff);

      /* Send Mtp3LinksetTable Update Request - with MTP3LinksetlinksetID not in DB */
      mtp3LinksetTblApiBuff.MTP3LinksetlinksetID= 1;
      mtp3LinksetTblApiBuff.mtp3Linksetlpc = 1;
      mtp3LinksetTblApiBuff.mtp3Linksetapc = 2;
      mtp3LinksetTblApiBuff.mtp3Linksetni = 10;
      insertMtp3LinksetTable(&mtp3LinksetTblApiBuff);

      mtp3LinksetTblApiBuff.MTP3LinksetlinksetID= 2;
      mtp3LinksetTblApiBuff.mtp3Linksetlpc = 2;
      mtp3LinksetTblApiBuff.mtp3Linksetapc = 2;
      mtp3LinksetTblApiBuff.mtp3Linksetni = 10;

      printf("\n cfgCmDbHndlr45: Mtp3LinksetTable parameter modification");
      cfgStubSendCmMessage(&mtp3LinksetTblApiBuff, sizeof(Mtp3LinksetTableApi),BSC_API_SET_MTP3LINKSETTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3LINKSETTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3LINKSETTABLE,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr45: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr45: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr45: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr45 */

void cfgCmDbHndlr46()
{
   static int testInitiation =1;
   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinksetTableApi mtp3LinksetTblApiBuff= {0};   
   Mtp3LinksetTableIndices Mtp3LinksetTableIndicesBuff;      
   I_S32 errCode = 0;
   I_S32 count = 0;   

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr46: Testing timeout for Set Mtp3LinksetTable to OIL");
      printf("\n cfgCmDbHndlr46: Mtp3LinksetTable Inserting new row - with MTP3LinksetlinksetID not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinksetTableIndicesBuff.MTP3LinksetlinksetID= 1;
      deleteMtp3LinksetTable(&Mtp3LinksetTableIndicesBuff);

      /* Send Mtp3LinksetTable Update Request - with MTP3LinksetlinksetID not in DB */
      mtp3LinksetTblApiBuff.MTP3LinksetlinksetID= 1;
      mtp3LinksetTblApiBuff.mtp3Linksetlpc = 2;
      mtp3LinksetTblApiBuff.mtp3Linksetapc = 2;
      mtp3LinksetTblApiBuff.mtp3Linksetni = 10;

      printf("\n cfgCmDbHndlr46: Mtp3LinksetTable Inserting new row - with MTP3LinksetlinksetID not in DB, sending");
      cfgStubSendCmMessage(&mtp3LinksetTblApiBuff, sizeof(Mtp3LinksetTableApi),BSC_API_SET_MTP3LINKSETTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3LINKSETTABLE :
            {
               printf(" Received BSC_API_SET_MTP3LINKSETTABLE , but not repsonding \n");
               /* 
                  cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3LINKSETTABLE,CM_SUCCESS);
                */
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr46: CM_ERR_END\n");
                  printf("\n cfgCmDbHndlr46: TestCase Passed\n");
               }
               else
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr46: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr46: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr46 */

void cfgCmDbHndlr47()
{
   static int testInitiation =1;
   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinksetTableApi mtp3LinksetTblApiBuff= {0};
   Mtp3LinksetTableApi *mtp3LinksetTblApiPtr= NULL;
   Mtp3LinksetTableIndices  Mtp3LinksetTableIndicesBuff = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr47: Mtp3LinksetTable Update Request - Same parameter values as in DB- Initiation");      

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinksetTableIndicesBuff.MTP3LinksetlinksetID= 1;
      deleteMtp3LinksetTable(&Mtp3LinksetTableIndicesBuff);

      /* Send Mtp3LinksetTable Update Request - with MTP3LinksetlinksetID not in DB */
      mtp3LinksetTblApiBuff.MTP3LinksetlinksetID= 1;
      mtp3LinksetTblApiBuff.mtp3Linksetlpc = 2;
      mtp3LinksetTblApiBuff.mtp3Linksetapc = 2;
      mtp3LinksetTblApiBuff.mtp3Linksetni = 10;
      insertMtp3LinksetTable(&mtp3LinksetTblApiBuff);


      printf("\n cfgCmDbHndlr47: Mtp3LinksetTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&mtp3LinksetTblApiBuff, sizeof(Mtp3LinksetTableApi),BSC_API_SET_MTP3LINKSETTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr47: FAILURE: Successfully handled");
               }
               else
               {
                  printf("\n cfgCmDbHndlr47: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr47: Msg Discarded ");
            }
      } /* end of Switch */

      printf("In cfgCmDbHndlr47: Success\n");
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr47 */


void cfgCmDbHndlr48()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3RouteTableApi mtp3RouteTblApiBuff = {0};
   Mtp3RouteTableIndices Mtp3RouteTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr48: Mtp3RouteTable Update Request - with mtp3RouterouteID not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3RouteTableIndicesBuff.mtp3RouterouteID = 1;
      deleteMtp3RouteTable(&Mtp3RouteTableIndicesBuff);
      /* Send Mtp3RouteTable Update Request - with mtp3RouterouteID not in DB */
      mtp3RouteTblApiBuff.mtp3RouterouteID = 1;
      mtp3RouteTblApiBuff.mtp3Routedirection = 2;
      mtp3RouteTblApiBuff.mtp3RoutelinksetID = 1;
      mtp3RouteTblApiBuff.mtp3Routestyle = DPC_SIO;
      mtp3RouteTblApiBuff.mtp3Routedpc = 22;
      mtp3RouteTblApiBuff.mtp3Routesio = 20;
      mtp3RouteTblApiBuff.mtp3Routessn = 7;
      mtp3RouteTblApiBuff.mtp3Routeni = 10;
      mtp3RouteTblApiBuff.mtp3Routeopc =  23;
      mtp3RouteTblApiBuff.mtp3Routerange = 16;
      mtp3RouteTblApiBuff.mtp3Routecic = 9;      

      printf("\n cfgCmDbHndlr48: Mtp3RouteTable Update Request - with mtp3RouterouteID not in DB, sending");
      cfgStubSendCmMessage(&mtp3RouteTblApiBuff, sizeof(Mtp3RouteTableApi),BSC_API_SET_MTP3ROUTETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3ROUTETABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3ROUTETABLE,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr48: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr48: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr48: Msg Discarded ");
            }

      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr48 */



void cfgCmDbHndlr49()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3RouteTableApi mtp3RouteTblApiBuff = {0};
   Mtp3RouteTableIndices Mtp3RouteTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr49: Mtp3RouteTable Parameter Modification");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3RouteTableIndicesBuff.mtp3RouterouteID = 1;
      deleteMtp3RouteTable(&Mtp3RouteTableIndicesBuff);
      /* Send Mtp3RouteTable Update Request - with mtp3RouterouteID not in DB */

      mtp3RouteTblApiBuff.mtp3RouterouteID = 1;
      mtp3RouteTblApiBuff.mtp3Routedirection = 2;
      mtp3RouteTblApiBuff.mtp3RoutelinksetID = 1;
      mtp3RouteTblApiBuff.mtp3Routestyle = DPC_SIO;
      mtp3RouteTblApiBuff.mtp3Routedpc = 22;
      mtp3RouteTblApiBuff.mtp3Routesio = 20;
      mtp3RouteTblApiBuff.mtp3Routessn = 7;
      mtp3RouteTblApiBuff.mtp3Routeni = 10;
      mtp3RouteTblApiBuff.mtp3Routeopc =  23;
      mtp3RouteTblApiBuff.mtp3Routerange = 16;
      mtp3RouteTblApiBuff.mtp3Routecic = 9;      

      if (insertMtp3RouteTable(&mtp3RouteTblApiBuff) != CLIB_SUCCESS)
         updateMtp3RouteTable(&mtp3RouteTblApiBuff);

      /* Modify one of the parameter */
      mtp3RouteTblApiBuff.mtp3Routecic = 1;      

      printf("\n cfgCmDbHndlr49: Sending Mtp3RouteTable Parameter Modification");
      cfgStubSendCmMessage(&mtp3RouteTblApiBuff, sizeof(Mtp3RouteTableApi),BSC_API_SET_MTP3ROUTETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3ROUTETABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3ROUTETABLE,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr49: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr49: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr49: Msg Discarded ");
            }

      } /* end of Switch */

   }/* end of Else-Execution Part*/
}



void cfgCmDbHndlr50()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3RouteTableApi mtp3RouteTblApiBuff = {0};
   Mtp3RouteTableIndices Mtp3RouteTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr50: Mtp3RouteTable Update Request - with mtp3RouterouteID not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3RouteTableIndicesBuff.mtp3RouterouteID = 1;
      deleteMtp3RouteTable(&Mtp3RouteTableIndicesBuff);
      /* Send Mtp3RouteTable Update Request - with mtp3RouterouteID not in DB */
      mtp3RouteTblApiBuff.mtp3RouterouteID = 1;
      mtp3RouteTblApiBuff.mtp3Routedirection = 2;
      mtp3RouteTblApiBuff.mtp3RoutelinksetID = 1;
      mtp3RouteTblApiBuff.mtp3Routestyle = DPC_SIO;
      mtp3RouteTblApiBuff.mtp3Routedpc = 22;
      mtp3RouteTblApiBuff.mtp3Routesio = 20;
      mtp3RouteTblApiBuff.mtp3Routessn = 7;
      mtp3RouteTblApiBuff.mtp3Routeni = 10;
      mtp3RouteTblApiBuff.mtp3Routeopc =  23;
      mtp3RouteTblApiBuff.mtp3Routerange = 16;
      mtp3RouteTblApiBuff.mtp3Routecic = 9;      

      printf("\n cfgCmDbHndlr50: Mtp3RouteTable Update Request - with mtp3RouterouteID not in DB, sending");
      cfgStubSendCmMessage(&mtp3RouteTblApiBuff, sizeof(Mtp3RouteTableApi),BSC_API_SET_MTP3ROUTETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3ROUTETABLE :
            {
               printf(" Received BSC_API_SET_MTP3ROUTETABLE ,Don't send Response \n");
               /*cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3ROUTETABLE,CM_SUCCESS); */
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr50: CM_ERR_END , Timeout Case \n");
                  printf("\n cfgCmDbHndlr50:  Test Case Passed \n");
               }
               else
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr50: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr50: Msg Discarded ");
            }

      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr50 */



void cfgCmDbHndlr51()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3RouteTableApi mtp3RouteTblApiBuff = {0};
   Mtp3RouteTableIndices Mtp3RouteTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr51: Mtp3RouteTable Update Request for idenitical row");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3RouteTableIndicesBuff.mtp3RouterouteID = 1;
      deleteMtp3RouteTable(&Mtp3RouteTableIndicesBuff);
      /* Send Mtp3RouteTable Update Request - with mtp3RouterouteID not in DB */

      mtp3RouteTblApiBuff.mtp3RouterouteID = 1;
      mtp3RouteTblApiBuff.mtp3Routedirection = 2;
      mtp3RouteTblApiBuff.mtp3RoutelinksetID = 1;
      mtp3RouteTblApiBuff.mtp3Routestyle = DPC_SIO;
      mtp3RouteTblApiBuff.mtp3Routedpc = 22;
      mtp3RouteTblApiBuff.mtp3Routesio = 20;
      mtp3RouteTblApiBuff.mtp3Routessn = 7;
      mtp3RouteTblApiBuff.mtp3Routeni = 10;
      mtp3RouteTblApiBuff.mtp3Routeopc =  23;
      mtp3RouteTblApiBuff.mtp3Routerange = 16;
      mtp3RouteTblApiBuff.mtp3Routecic = 9;      

      if (insertMtp3RouteTable(&mtp3RouteTblApiBuff) != CLIB_SUCCESS)
         updateMtp3RouteTable(&mtp3RouteTblApiBuff);

      /* Send the same Buffer */

      printf("\n cfgCmDbHndlr51: Sending Set Mtp3RouteTable with the same parameters as in DB");
      cfgStubSendCmMessage(&mtp3RouteTblApiBuff, sizeof(Mtp3RouteTableApi),BSC_API_SET_MTP3ROUTETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr51: received CM_ERR_END \n");
                  printf("\n cfgCmDbHndlr51: Test Case Passed \n");
               }
               else
               {
                  gTestCaseCompleted = 1;
                  printf("\n cfgCmDbHndlr51: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr51: Msg Discarded ");
            }

      } /* end of Switch */

   }/* end of Else-Execution Part*/
}

void cfgCmDbHndlr52()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinksetStsTableApi mtp3LinkSetAdminStateTblApiBuff = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      Mtp3LinksetStsTableIndices Mtp3LinksetStsTableIndicesBuff;
      printf("\n cfgCmDbHndlr52: Mtp3LinksetStsTable Update Request - with linkId not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinksetStsTableIndicesBuff.MTP3LinksetlinksetID =1;
      deleteMtp3LinksetStsTable(&Mtp3LinksetStsTableIndicesBuff);
      /* Send Mtp3LinksetStsTable Update Request - with linkId not in DB */
      mtp3LinkSetAdminStateTblApiBuff.MTP3LinksetlinksetID = 1;
      mtp3LinkSetAdminStateTblApiBuff.oprState = ENABLED;

      printf("\n cfgCmDbHndlr52: Mtp3LinksetStsTable Update Request - with linkId not in DB, sending");
      cfgStubSendCmMessage(&mtp3LinkSetAdminStateTblApiBuff,
            sizeof(Mtp3LinksetStsTableApi),
            BSC_API_SET_MTP3LINKSETSTSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3LINKSETSTSTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3LINKSETSTSTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr52: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  printf("\n cfgCmDbHndlr52: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr52: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr52 */


void cfgCmDbHndlr53()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinksetStsTableApi mtp3LinkSetAdminStateTblApiBuff = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      Mtp3LinksetStsTableIndices Mtp3LinksetStsTableIndicesBuff;
      Mtp3LinksetStsTableApi* Mtp3LinksetStsTableApiPtr;
      printf("\n cfgCmDbHndlr53: Parameter modification in Mtp3LinksetStsTable");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinksetStsTableIndicesBuff.MTP3LinksetlinksetID =1;
      if (getMtp3LinksetStsTable(&Mtp3LinksetStsTableIndicesBuff,&Mtp3LinksetStsTableApiPtr) != CLIB_SUCCESS )
      {
         /* Send Mtp3LinksetStsTable Update Request - with linkId not in DB */
         mtp3LinkSetAdminStateTblApiBuff.MTP3LinksetlinksetID = 1;
         mtp3LinkSetAdminStateTblApiBuff.oprState = ENABLED;
         insertMtp3LinksetStsTable(&mtp3LinkSetAdminStateTblApiBuff);
      }
      else
      {
         memcpy(&mtp3LinkSetAdminStateTblApiBuff,Mtp3LinksetStsTableApiPtr,sizeof(Mtp3LinksetStsTableApi));
      }

      /* Modify one the parameter  */
      mtp3LinkSetAdminStateTblApiBuff.oprState = ~mtp3LinkSetAdminStateTblApiBuff.oprState;
      printf("\n cfgCmDbHndlr53: Sending parameter modification for Mtp3LinksetStsTable");
      cfgStubSendCmMessage(&mtp3LinkSetAdminStateTblApiBuff,
            sizeof(Mtp3LinksetStsTableApi),
            BSC_API_SET_MTP3LINKSETSTSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3LINKSETSTSTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3LINKSETSTSTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr53: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  printf("\n cfgCmDbHndlr53: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr53: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr53 */


void cfgCmDbHndlr54()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinksetStsTableApi mtp3LinkSetAdminStateTblApiBuff = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      Mtp3LinksetStsTableIndices Mtp3LinksetStsTableIndicesBuff;
      printf("\n cfgCmDbHndlr54: Mtp3LinksetStsTable Update Request - with linkId not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinksetStsTableIndicesBuff.MTP3LinksetlinksetID =1;
      deleteMtp3LinksetStsTable(&Mtp3LinksetStsTableIndicesBuff);
      /* Send Mtp3LinksetStsTable Update Request - with linkId not in DB */
      mtp3LinkSetAdminStateTblApiBuff.MTP3LinksetlinksetID = 1;
      mtp3LinkSetAdminStateTblApiBuff.oprState = ENABLED;

      printf("\n cfgCmDbHndlr54: Mtp3LinksetStsTable Update Request - with linkId not in DB, sending");
      cfgStubSendCmMessage(&mtp3LinkSetAdminStateTblApiBuff,
            sizeof(Mtp3LinksetStsTableApi),
            BSC_API_SET_MTP3LINKSETSTSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3LINKSETSTSTABLE :
            {
               printf("Received BSC_API_SET_MTP3LINKSETSTSTABLE , Don't Send Rsp\n");
               /*cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3LINKSETSTSTABLE,CM_SUCCESS); */
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr54: CM_ERR_END: Time out case \n");
                  printf("\n cfgCmDbHndlr54: Test case passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr54: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr54: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/
}



void cfgCmDbHndlr55()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinksetStsTableApi mtp3LinkSetAdminStateTblApiBuff = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      Mtp3LinksetStsTableIndices Mtp3LinksetStsTableIndicesBuff;
      Mtp3LinksetStsTableApi* Mtp3LinksetStsTableApiPtr;
      printf("\n cfgCmDbHndlr55: Mtp3LinksetStsTable Set Request - with same parameter value as in DB");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinksetStsTableIndicesBuff.MTP3LinksetlinksetID =1;
      if (getMtp3LinksetStsTable(&Mtp3LinksetStsTableIndicesBuff,&Mtp3LinksetStsTableApiPtr) != CLIB_SUCCESS )
      {
         /* Send Mtp3LinksetStsTable Update Request - with linkId not in DB */
         mtp3LinkSetAdminStateTblApiBuff.MTP3LinksetlinksetID = 1;
         mtp3LinkSetAdminStateTblApiBuff.oprState = ENABLED;
         insertMtp3LinksetStsTable(&mtp3LinkSetAdminStateTblApiBuff);
      }
      else
      {
         memcpy(&mtp3LinkSetAdminStateTblApiBuff,Mtp3LinksetStsTableApiPtr,sizeof(Mtp3LinksetStsTableApi));
      }

      /* Don't Modify the parameter  */
      printf("\n cfgCmDbHndlr55: Mtp3LinksetStsTable Set Request - with same parameter value as in DB");
      cfgStubSendCmMessage(&mtp3LinkSetAdminStateTblApiBuff,
            sizeof(Mtp3LinksetStsTableApi),
            BSC_API_SET_MTP3LINKSETSTSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr55: received CM_ERR_END\n");
                  printf("\n cfgCmDbHndlr55: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr55: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr55: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr55 */

void cfgCmDbHndlr56()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinkTableApi mtp3LinkTblApiBuff = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      Mtp3LinkTableIndices Mtp3LinkTableIndicesBuff;
      testInitiation =0;
      printf("\n cfgCmDbHndlr56: Mtp3LinkTable Update Request - with linkCode & setId not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinkTableIndicesBuff.mtp3LinklinkCode=1;
      Mtp3LinkTableIndicesBuff.mtp3LinklinksetID=1;
      deleteMtp3LinkTable(&Mtp3LinkTableIndicesBuff);
      /* Send Mtp3LinkTable Update Request - with linkCode & setId not in DB */
      mtp3LinkTblApiBuff.mtp3LinklinkCode = 1;
      mtp3LinkTblApiBuff.mtp3LinklinksetID = 1;

      mtp3LinkTblApiBuff.mtp3LinkcardId = 1;
      mtp3LinkTblApiBuff.mtp3LinkpeerMtp3 = 2;
      mtp3LinkTblApiBuff.mtp3LinkportNum = 31;
      mtp3LinkTblApiBuff.mtp3LinkchanNum = 6;           

      printf("\n cfgCmDbHndlr56: Mtp3LinkTable Update Request - with linkCode & setId not in DB, sending");
      cfgStubSendCmMessage(&mtp3LinkTblApiBuff, sizeof(Mtp3LinkTableApi),BSC_API_SET_MTP3LINKTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3LINKTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3LINKTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr56: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr56: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr56: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}



void cfgCmDbHndlr57()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinkTableApi mtp3LinkTblApiBuff = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      Mtp3LinkTableIndices Mtp3LinkTableIndicesBuff;
      testInitiation =0;
      printf("\n cfgCmDbHndlr57: Mtp3LinkTable Parameter Modification");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinkTableIndicesBuff.mtp3LinklinkCode=1;
      Mtp3LinkTableIndicesBuff.mtp3LinklinksetID=1;
      deleteMtp3LinkTable(&Mtp3LinkTableIndicesBuff);
      /* Send Mtp3LinkTable Update Request - with linkCode & setId not in DB */
      mtp3LinkTblApiBuff.mtp3LinklinkCode = 1;
      mtp3LinkTblApiBuff.mtp3LinklinksetID = 1;

      mtp3LinkTblApiBuff.mtp3LinkcardId = 1;
      mtp3LinkTblApiBuff.mtp3LinkpeerMtp3 = 2;
      mtp3LinkTblApiBuff.mtp3LinkportNum = 31;
      mtp3LinkTblApiBuff.mtp3LinkchanNum = 6;           

      insertMtp3LinkTable(&mtp3LinkTblApiBuff);

      /* Modify the parameter */
      mtp3LinkTblApiBuff.mtp3LinkchanNum = 7;           
      printf("\n cfgCmDbHndlr57: Sending Mtp3LinkTable Parameter Modification");
      cfgStubSendCmMessage(&mtp3LinkTblApiBuff, sizeof(Mtp3LinkTableApi),BSC_API_SET_MTP3LINKTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3LINKTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3LINKTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr57: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr57: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr57: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}



void cfgCmDbHndlr58()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinkTableApi mtp3LinkTblApiBuff = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      Mtp3LinkTableIndices Mtp3LinkTableIndicesBuff;
      testInitiation =0;
      printf("\n cfgCmDbHndlr58: Testing timeout for Set Mtp3LinkTable request");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinkTableIndicesBuff.mtp3LinklinkCode=1;
      Mtp3LinkTableIndicesBuff.mtp3LinklinksetID=1;
      deleteMtp3LinkTable(&Mtp3LinkTableIndicesBuff);
      /* Send Mtp3LinkTable Update Request - with linkCode & setId not in DB */
      mtp3LinkTblApiBuff.mtp3LinklinkCode = 1;
      mtp3LinkTblApiBuff.mtp3LinklinksetID = 1;

      mtp3LinkTblApiBuff.mtp3LinkcardId = 1;
      mtp3LinkTblApiBuff.mtp3LinkpeerMtp3 = 2;
      mtp3LinkTblApiBuff.mtp3LinkportNum = 31;
      mtp3LinkTblApiBuff.mtp3LinkchanNum = 6;           

      printf("\n cfgCmDbHndlr58: Testing timeout for Set Mtp3LinkTable request");
      cfgStubSendCmMessage(&mtp3LinkTblApiBuff, sizeof(Mtp3LinkTableApi),BSC_API_SET_MTP3LINKTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3LINKTABLE :
            {
               printf(" received BSC_API_SET_MTP3LINKTABLE, Dont send Rsp \n");
               /* cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3LINKTABLE,CM_SUCCESS); */
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr58: Received CM_ERR_END \n");
                  printf("\n cfgCmDbHndlr58: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr58: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr58: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}




void cfgCmDbHndlr59()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3LinkTableApi mtp3LinkTblApiBuff = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      Mtp3LinkTableIndices Mtp3LinkTableIndicesBuff;
      testInitiation =0;
      printf("\n cfgCmDbHndlr59: Mtp3LinkTable Set Request - with same parameter value as in DB");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      Mtp3LinkTableIndicesBuff.mtp3LinklinkCode=1;
      Mtp3LinkTableIndicesBuff.mtp3LinklinksetID=1;
      deleteMtp3LinkTable(&Mtp3LinkTableIndicesBuff);
      /* Send Mtp3LinkTable Update Request - with linkCode & setId not in DB */
      mtp3LinkTblApiBuff.mtp3LinklinkCode = 1;
      mtp3LinkTblApiBuff.mtp3LinklinksetID = 1;

      mtp3LinkTblApiBuff.mtp3LinkcardId = 1;
      mtp3LinkTblApiBuff.mtp3LinkpeerMtp3 = 2;
      mtp3LinkTblApiBuff.mtp3LinkportNum = 31;
      mtp3LinkTblApiBuff.mtp3LinkchanNum = 6;           

      insertMtp3LinkTable(&mtp3LinkTblApiBuff);

      /* Don't Modify the parameter */
      /* mtp3LinkTblApiBuff.mtp3LinkchanNum = 7;          */ 
      printf("\n cfgCmDbHndlr59: Sending Mtp3LinkTable Set Request - with same parameter value as in DB");
      cfgStubSendCmMessage(&mtp3LinkTblApiBuff, sizeof(Mtp3LinkTableApi),BSC_API_SET_MTP3LINKTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr59:CM_ERR_END: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr59: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr59: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr48 */


void cfgCmDbHndlr60()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   LinkAdminStateTableApi linkAdminStateTblApiBuff = {0};
   LinkAdminStateTableIndices LinkAdminStateTableIndicesBuf;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr60: LinkAdminStateTable Update Request - with linkId not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      LinkAdminStateTableIndicesBuf.linkAdminlinkCode =1;
      LinkAdminStateTableIndicesBuf.linkAdminlinksetID =1;
      deleteLinkAdminStateTable(&LinkAdminStateTableIndicesBuf);

      /* Send LinkAdminStateTable Update Request - with linkId not in DB */
      linkAdminStateTblApiBuff.linkAdminlinkCode = 1;
      linkAdminStateTblApiBuff.linkAdminlinksetID = 1;
      linkAdminStateTblApiBuff.linkAdminadminState = ENABLED;

      printf("\n cfgCmDbHndlr60: LinkAdminStateTable insertion Request - with linkId not in DB, sending");
      cfgStubSendCmMessage(&linkAdminStateTblApiBuff,
            sizeof(LinkAdminStateTableApi),
            BSC_API_SET_LINKADMINSTATETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_LINKADMINSTATETABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_LINKADMINSTATETABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr60: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  printf("\n cfgCmDbHndlr60: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr60: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr60 */


void cfgCmDbHndlr61()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   LinkAdminStateTableApi linkAdminStateTblApiBuff = {0};
   LinkAdminStateTableIndices LinkAdminStateTableIndicesBuf;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr61: LinkAdminStateTable Parameter Modification");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      LinkAdminStateTableIndicesBuf.linkAdminlinkCode =1;
      LinkAdminStateTableIndicesBuf.linkAdminlinksetID =1;
      deleteLinkAdminStateTable(&LinkAdminStateTableIndicesBuf);

      /* Send LinkAdminStateTable Update Request - with linkId not in DB */
      linkAdminStateTblApiBuff.linkAdminlinkCode = 1;
      linkAdminStateTblApiBuff.linkAdminlinksetID = 1;
      linkAdminStateTblApiBuff.linkAdminadminState = ENABLED;

      insertLinkAdminStateTable(&linkAdminStateTblApiBuff);

      /* Modify the table */

      linkAdminStateTblApiBuff.linkAdminadminState = ~ENABLED;

      printf("\n cfgCmDbHndlr61: LinkAdminStateTable update Request \n");
      cfgStubSendCmMessage(&linkAdminStateTblApiBuff,
            sizeof(LinkAdminStateTableApi),
            BSC_API_SET_LINKADMINSTATETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_LINKADMINSTATETABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_LINKADMINSTATETABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr61: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  printf("\n cfgCmDbHndlr61: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr61: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr61 */


void cfgCmDbHndlr62()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   LinkAdminStateTableApi linkAdminStateTblApiBuff = {0};
   LinkAdminStateTableIndices LinkAdminStateTableIndicesBuf;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr62: LinkAdminStateTable Set Request - Timeout");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      LinkAdminStateTableIndicesBuf.linkAdminlinkCode =1;
      LinkAdminStateTableIndicesBuf.linkAdminlinksetID =1;
      deleteLinkAdminStateTable(&LinkAdminStateTableIndicesBuf);

      /* Send LinkAdminStateTable Update Request - with linkId not in DB */
      linkAdminStateTblApiBuff.linkAdminlinkCode = 1;
      linkAdminStateTblApiBuff.linkAdminlinksetID = 1;
      linkAdminStateTblApiBuff.linkAdminadminState = ENABLED;

      printf("\n cfgCmDbHndlr62: LinkAdminStateTable insertion Request - with linkId not in DB, sending");
      cfgStubSendCmMessage(&linkAdminStateTblApiBuff,
            sizeof(LinkAdminStateTableApi),
            BSC_API_SET_LINKADMINSTATETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_LINKADMINSTATETABLE :
            {
               printf(" Received BSC_API_SET_LINKADMINSTATETABLE,Don't send Rsp\n");
               /* cfgStubSendCmMessageFromOil(BSC_API_SET_LINKADMINSTATETABLE,CM_SUCCESS);*/
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr62: CM_ERR_END ,TimeOut case");
                  printf("\n cfgCmDbHndlr62: Test case passed");
               }
               else
               {
                  printf("\n cfgCmDbHndlr62: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr62: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr62 */



void cfgCmDbHndlr63()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   LinkAdminStateTableApi linkAdminStateTblApiBuff = {0};
   LinkAdminStateTableIndices LinkAdminStateTableIndicesBuf;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr63: LinkAdminStateTable Update Request - with same parameters");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      LinkAdminStateTableIndicesBuf.linkAdminlinkCode =1;
      LinkAdminStateTableIndicesBuf.linkAdminlinksetID =1;
      deleteLinkAdminStateTable(&LinkAdminStateTableIndicesBuf);

      /* Send LinkAdminStateTable Update Request - with linkId not in DB */
      linkAdminStateTblApiBuff.linkAdminlinkCode = 1;
      linkAdminStateTblApiBuff.linkAdminlinksetID = 1;
      linkAdminStateTblApiBuff.linkAdminadminState = ENABLED;

      insertLinkAdminStateTable(&linkAdminStateTblApiBuff);

      /* Don't modify the table */


      printf("\n cfgCmDbHndlr63: LinkAdminStateTable update Request with same parameter as in DB \n");
      cfgStubSendCmMessage(&linkAdminStateTblApiBuff,
            sizeof(LinkAdminStateTableApi),
            BSC_API_SET_LINKADMINSTATETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr63: CM_ERR_END: Test Case 63 passed");
               }
               else
               {
                  printf("\n cfgCmDbHndlr63: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr63: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr63 */

void cfgCmDbHndlr64()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3RemotePointCodeStsTableApi mtp3RemotePtCdTblApiBuff = {0};
   Mtp3RemotePointCodeStsTableIndices Mtp3RemotePointCodeStsTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr64: Mtp3RemotePointCodeTable Update Request - with Coderpc+ni+linksetId not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      /* Send Mtp3RemotePointCodeTable Update Request - with Coderpc+ni+linksetId not in DB */

      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCoderpc =1 ;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodeni =1 ;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodelinksetID =1 ;
      deleteMtp3RemotePointCodeStsTable(& Mtp3RemotePointCodeStsTableIndicesBuff);

      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCoderpc = 1;
      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodeni = 1;
      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodelinksetID = 1;

      printf("\n cfgCmDbHndlr64: Mtp3RemotePointCodeTable Update Request - with Coderpc+ni+linksetId not in DB, sending");
      cfgStubSendCmMessage(&mtp3RemotePtCdTblApiBuff,
            sizeof(Mtp3RemotePointCodeStsTableApi),
            BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr64: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  printf("\n cfgCmDbHndlr64: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr64: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr64 */



void cfgCmDbHndlr65()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3RemotePointCodeStsTableApi mtp3RemotePtCdTblApiBuff = {0};
   Mtp3RemotePointCodeStsTableIndices Mtp3RemotePointCodeStsTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr65: Mtp3RemotePointCodeTable Set request for parameter modification");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      /* Send Mtp3RemotePointCodeTable Update Request - with Coderpc+ni+linksetId not in DB */

      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCoderpc =1 ;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodeni =1 ;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodelinksetID =1 ;
      deleteMtp3RemotePointCodeStsTable(& Mtp3RemotePointCodeStsTableIndicesBuff);

      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCoderpc = 1;
      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodeni = 1;
      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodelinksetID = 1;

      insertMtp3RemotePointCodeStsTable(&mtp3RemotePtCdTblApiBuff);
      /* modify the parameter */
      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodeni = 2;

      printf("\n cfgCmDbHndlr65: Sending Mtp3RemotePointCodeTable Set request for parameter modification");
      cfgStubSendCmMessage(&mtp3RemotePtCdTblApiBuff,
            sizeof(Mtp3RemotePointCodeStsTableApi),
            BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr65: CM_SUCCESS: Successfully handled- Row Updated");
                  printf("\n cfgCmDbHndlr65: Test case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr65: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr65: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr65 */



void cfgCmDbHndlr66()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3RemotePointCodeStsTableApi mtp3RemotePtCdTblApiBuff = {0};
   Mtp3RemotePointCodeStsTableIndices Mtp3RemotePointCodeStsTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr66: Mtp3RemotePointCodeTable Set Request - Timeout Case");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      /* Send Mtp3RemotePointCodeTable Update Request - with Coderpc+ni+linksetId not in DB */

      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCoderpc =1 ;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodeni =1 ;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodelinksetID =1 ;
      deleteMtp3RemotePointCodeStsTable(& Mtp3RemotePointCodeStsTableIndicesBuff);

      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCoderpc = 1;
      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodeni = 1;
      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodelinksetID = 1;

      printf("\n cfgCmDbHndlr66: Mtp3RemotePointCodeTable Update Request - with Coderpc+ni+linksetId not in DB, sending");
      cfgStubSendCmMessage(&mtp3RemotePtCdTblApiBuff,
            sizeof(Mtp3RemotePointCodeStsTableApi),
            BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE :
            {
               printf(" Received BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE ,Don't send Rsp\n");
               /*                cfgStubSendCmMessageFromOil(BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE,CM_SUCCESS); */
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr66: CM_ERR_END: Timeout Case \n");
                  printf("\n cfgCmDbHndlr66: Test case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr66: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr66: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr66 */


void cfgCmDbHndlr67()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   Mtp3RemotePointCodeStsTableApi mtp3RemotePtCdTblApiBuff = {0};
   Mtp3RemotePointCodeStsTableIndices Mtp3RemotePointCodeStsTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr67: Mtp3RemotePointCodeTable Update Request - with same parameters");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      /* Send Mtp3RemotePointCodeTable Update Request - with Coderpc+ni+linksetId not in DB */

      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCoderpc =1 ;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodeni =1 ;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodelinksetID =1 ;
      deleteMtp3RemotePointCodeStsTable(& Mtp3RemotePointCodeStsTableIndicesBuff);

      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCoderpc = 1;
      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodeni = 1;
      mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodelinksetID = 1;

      insertMtp3RemotePointCodeStsTable(&mtp3RemotePtCdTblApiBuff);
      /* Don't modify the parameter */
      /* mtp3RemotePtCdTblApiBuff.mtp3RemotePointCodestatus = ~ENABLED; */

      printf("\n cfgCmDbHndlr67: Sending Mtp3RemotePointCodeTable Update Request - with same parameters");
      cfgStubSendCmMessage(&mtp3RemotePtCdTblApiBuff,
            sizeof(Mtp3RemotePointCodeStsTableApi),
            BSC_API_SET_MTP3REMOTEPOINTCODESTSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr67: CM_ERR_END: \n");
                  printf("\n cfgCmDbHndlr67: Test case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr67: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr67: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr67 */


void cfgCmDbHndlr68()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   SccpSsnConfigTableApi sccpSsnConfigTblApiBuff = {0};
   SccpSsnConfigTableIndices SccpSsnConfigTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr68: SccpSsnConfigTable Update Request - no entry  in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      SccpSsnConfigTableIndicesBuff.sccpSsnConfigssn = 1;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigpc = 6;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigni = 1;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigisLocal = TRUE;
      deleteSccpSsnConfigTable(&SccpSsnConfigTableIndicesBuff);
      /* Send SccpSsnConfigTable Update Request - no entry  in DB */
      sccpSsnConfigTblApiBuff.sccpSsnConfigssn = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigpc = 6;
      sccpSsnConfigTblApiBuff.sccpSsnConfigni = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigisLocal = TRUE;
      sccpSsnConfigTblApiBuff.sccpSsnConfiglinksetID = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigsstTestOn = FALSE;

      printf("\n cfgCmDbHndlr68: SccpSsnConfigTable Update Request - no entry  in DB, sending");
      cfgStubSendCmMessage(&sccpSsnConfigTblApiBuff,
            sizeof(SccpSsnConfigTableApi),
            BSC_API_SET_SCCPSSNCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SCCPSSNCONFIGTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SCCPSSNCONFIGTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr68: CM_SUCCESS: Successfully handled- Row added");
                  printf("\n cfgCmDbHndlr68: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr68: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr68: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr68 */



void cfgCmDbHndlr69()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   SccpSsnConfigTableApi sccpSsnConfigTblApiBuff = {0};
   SccpSsnConfigTableIndices SccpSsnConfigTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr69: SccpSsnConfigTable Set request with parameter modification");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      SccpSsnConfigTableIndicesBuff.sccpSsnConfigssn = 1;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigpc = 6;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigni = 1;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigisLocal = TRUE;
      deleteSccpSsnConfigTable(&SccpSsnConfigTableIndicesBuff);
      /* Send SccpSsnConfigTable Update Request - no entry  in DB */
      sccpSsnConfigTblApiBuff.sccpSsnConfigssn = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigpc = 6;
      sccpSsnConfigTblApiBuff.sccpSsnConfigni = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigisLocal = TRUE;
      sccpSsnConfigTblApiBuff.sccpSsnConfiglinksetID = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigsstTestOn = FALSE;

      insertSccpSsnConfigTable(&sccpSsnConfigTblApiBuff);

      /* Modify the paramter */
      sccpSsnConfigTblApiBuff.sccpSsnConfigsstTestOn = TRUE;

      printf("\n cfgCmDbHndlr69: SccpSsnConfigTable Update Request Sending");
      cfgStubSendCmMessage(&sccpSsnConfigTblApiBuff,
            sizeof(SccpSsnConfigTableApi),
            BSC_API_SET_SCCPSSNCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SCCPSSNCONFIGTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SCCPSSNCONFIGTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr69: CM_SUCCESS: Successfully handled- Row added");
                  printf("\n cfgCmDbHndlr69: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr69: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr69: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr69 */


void cfgCmDbHndlr70()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   SccpSsnConfigTableApi sccpSsnConfigTblApiBuff = {0};
   SccpSsnConfigTableIndices SccpSsnConfigTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr70: SccpSsnConfigTable Update Request - Timeout Case");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      SccpSsnConfigTableIndicesBuff.sccpSsnConfigssn = 1;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigpc = 6;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigni = 1;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigisLocal = TRUE;
      deleteSccpSsnConfigTable(&SccpSsnConfigTableIndicesBuff);
      /* Send SccpSsnConfigTable Update Request - no entry  in DB */
      sccpSsnConfigTblApiBuff.sccpSsnConfigssn = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigpc = 6;
      sccpSsnConfigTblApiBuff.sccpSsnConfigni = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigisLocal = TRUE;
      sccpSsnConfigTblApiBuff.sccpSsnConfiglinksetID = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigsstTestOn = FALSE;

      printf("\n cfgCmDbHndlr70: SccpSsnConfigTable Update Request - no entry  in DB, sending");
      cfgStubSendCmMessage(&sccpSsnConfigTblApiBuff,
            sizeof(SccpSsnConfigTableApi),
            BSC_API_SET_SCCPSSNCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SCCPSSNCONFIGTABLE :
            {
               printf(" Received BSC_API_SET_SCCPSSNCONFIGTABLE, Don't Send the Rsp\n");
               /*cfgStubSendCmMessageFromOil(BSC_API_SET_SCCPSSNCONFIGTABLE,CM_SUCCESS);*/
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr70: CM_ERR_END,Timeout case \n");
                  printf("\n cfgCmDbHndlr70: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr70: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr70: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr70 */



void cfgCmDbHndlr71()
{
   static int testInitiation =1;

   BssTableApi* bssTableApiPtr = NULL;
   SccpSsnConfigTableApi sccpSsnConfigTblApiBuff = {0};
   SccpSsnConfigTableIndices SccpSsnConfigTableIndicesBuff;
   I_S32 errCode = 0;
   I_S32 count = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr71: SccpSsnConfigTable Set request with same parameter as in DB");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      SccpSsnConfigTableIndicesBuff.sccpSsnConfigssn = 1;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigpc = 6;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigni = 1;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigisLocal = TRUE;
      deleteSccpSsnConfigTable(&SccpSsnConfigTableIndicesBuff);
      /* Send SccpSsnConfigTable Update Request - no entry  in DB */
      sccpSsnConfigTblApiBuff.sccpSsnConfigssn = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigpc = 6;
      sccpSsnConfigTblApiBuff.sccpSsnConfigni = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigisLocal = TRUE;
      sccpSsnConfigTblApiBuff.sccpSsnConfiglinksetID = 1;
      sccpSsnConfigTblApiBuff.sccpSsnConfigsstTestOn = FALSE;

      insertSccpSsnConfigTable(&sccpSsnConfigTblApiBuff);

      /* Don't Modify the paramter */
      /* sccpSsnConfigTblApiBuff.sccpSsnConfigsstTestOn = TRUE; */

      printf("\n cfgCmDbHndlr71: SccpSsnConfigTable Update Request\n with same parameter Sending");
      cfgStubSendCmMessage(&sccpSsnConfigTblApiBuff,
            sizeof(SccpSsnConfigTableApi),
            BSC_API_SET_SCCPSSNCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr71: CM_ERR_END\n");
                  printf("\n cfgCmDbHndlr71: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr71: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr71: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr71 */





void cfgCmDbHndlr72()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   SccpCSSNConfigTableApi sccpCSSNConfigTblApiBuff = {0};
   SccpCSSNConfigTableIndices SccpCSSNConfigTableIndicesBuff;
   printf("\n cfgCmDbHndlr72 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr72: SccpCSSNConfigTable Update Request - with sccpCSsnConfigssn and sccpCSsnConfigpc not in DB, sending");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigssn =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigpc =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigni =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigcssn =1;
      deleteSccpCSSNConfigTable(&SccpCSSNConfigTableIndicesBuff);
      /* Send SccpCSSNConfigTable Update Request - with sccpCSsnConfigssn and sccpCSsnConfigpc not in DB */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigssn = 1; /* key */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigpc = 1; /* key */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigni= 1;
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcssn= 1;
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcpc= 1;



      cfgStubSendCmMessage(&sccpCSSNConfigTblApiBuff, sizeof(SccpCSSNConfigTableApi),BSC_API_SET_SCCPCSSNCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SCCPCSSNCONFIGTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SCCPCSSNCONFIGTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr72: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  printf("\n cfgCmDbHndlr72: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr72: Msg Discarded ");                     }
      } /* end of Switch */

   }/* end of Else-Execution Part*/
}
/* end of cfgCmDbHndlr72*/


void cfgCmDbHndlr73()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   SccpCSSNConfigTableApi sccpCSSNConfigTblApiBuff = {0};
   SccpCSSNConfigTableIndices SccpCSSNConfigTableIndicesBuff;
   printf("\n cfgCmDbHndlr73 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr73: SccpCSSNConfigTable Set request with parameter modification");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigssn =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigpc =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigni =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigcssn =1;
      deleteSccpCSSNConfigTable(&SccpCSSNConfigTableIndicesBuff);
      /* Send SccpCSSNConfigTable Update Request - with sccpCSsnConfigssn and sccpCSsnConfigpc not in DB */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigssn = 1; /* key */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigpc = 1; /* key */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigni= 1;
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcssn= 1;
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcpc= 1;

      insertSccpCSSNConfigTable(&sccpCSSNConfigTblApiBuff);
      /* Modify the parameter */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcpc= 2;


      printf("\n cfgCmDbHndlr73: Sending SccpCSSNConfigTable Set request with parameter modification");
      cfgStubSendCmMessage(&sccpCSSNConfigTblApiBuff, sizeof(SccpCSSNConfigTableApi),BSC_API_SET_SCCPCSSNCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SCCPCSSNCONFIGTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SCCPCSSNCONFIGTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr73: CM_SUCCESS: Successfully handled- Row Updated\n");
                  printf("\n cfgCmDbHndlr73: Test Case Passed\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr73: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr73: Msg Discarded ");                     }
      } /* end of Switch */

   }/* end of Else-Execution Part*/
}
/* start of cfgCmDbHndlr73 */
/* end of cfgCmDbHndlr73*/


void cfgCmDbHndlr74()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   SccpCSSNConfigTableApi sccpCSSNConfigTblApiBuff = {0};
   SccpCSSNConfigTableIndices SccpCSSNConfigTableIndicesBuff;
   printf("\n cfgCmDbHndlr74 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr74: SccpCSSNConfigTable Update Request - Timeout case");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigssn =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigpc =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigni =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigcssn =1;
      deleteSccpCSSNConfigTable(&SccpCSSNConfigTableIndicesBuff);
      /* Send SccpCSSNConfigTable Update Request - with sccpCSsnConfigssn and sccpCSsnConfigpc not in DB */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigssn = 1; /* key */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigpc = 1; /* key */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigni= 1;
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcssn= 1;
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcpc= 1;

      insertSccpCSSNConfigTable(&sccpCSSNConfigTblApiBuff);
      /* Modify the parameter */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcpc= 2;


      cfgStubSendCmMessage(&sccpCSSNConfigTblApiBuff, sizeof(SccpCSSNConfigTableApi),BSC_API_SET_SCCPCSSNCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SCCPCSSNCONFIGTABLE :
            {
               printf(" Received BSC_API_SET_SCCPCSSNCONFIGTABLE, Don't Send the response \n");
               /* cfgStubSendCmMessageFromOil(BSC_API_SET_SCCPCSSNCONFIGTABLE,CM_SUCCESS); */
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr74: CM_ERR_END: Time out case \n");
                  printf("\n cfgCmDbHndlr74: Test Case Passed\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr74: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr74: Msg Discarded ");                     }
      } /* end of Switch */

   }/* end of Else-Execution Part*/
}



void cfgCmDbHndlr76()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   SccpCSSNConfigTableApi sccpCSSNConfigTblApiBuff = {0};
   SccpCSSNConfigTableIndices SccpCSSNConfigTableIndicesBuff;
   printf("\n cfgCmDbHndlr76 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr76: SccpCSSNConfigTable Set request with same parameter value as in DB");

      /* First set the BSS - precondition */
      errCode = setDbForBss();


      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigssn =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigpc =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigni =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigcssn =1;
      deleteSccpCSSNConfigTable(&SccpCSSNConfigTableIndicesBuff);
      /* Send SccpCSSNConfigTable Update Request - with sccpCSsnConfigssn and sccpCSsnConfigpc not in DB */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigssn = 1; /* key */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigpc = 1; /* key */
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigni= 1;
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcssn= 1;
      sccpCSSNConfigTblApiBuff.sccpCSsnConfigcpc= 1;

      insertSccpCSSNConfigTable(&sccpCSSNConfigTblApiBuff);
      /* DOnt Modify the parameter */
      /* sccpCSSNConfigTblApiBuff.sccpCSsnConfigcpc= 2; */


      printf("\n cfgCmDbHndlr76: Sending SccpCSSNConfigTable Set request with same parameter value as in DB");
      cfgStubSendCmMessage(&sccpCSSNConfigTblApiBuff, sizeof(SccpCSSNConfigTableApi),BSC_API_SET_SCCPCSSNCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr76: CM_ERR_END: same parameter case \n");
                  printf("\n cfgCmDbHndlr76: Test Case Passed\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr76: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr76: Msg Discarded ");                     }
      } /* end of Switch */

   }/* end of Else-Execution Part*/
}

/* start of cfgCmDbHndlr105 */
void cfgCmDbHndlr105()
{
   static int testInitiation =1;    
   SksCommonTableApi sksCommonTblApiBuff = {0};
   SksCommonTableIndices SksCommonTableIndicesBuff;
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr105: SksCommonTable Update Request - with sksCommonopc and sksCommonfamily not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      /* Send SksCommonTable Update Request - with sksCommonopc and sksCommonfamily not in DB */
      SksCommonTableIndicesBuff.sksCommonopc=1;

      deleteSksCommonTable(&SksCommonTableIndicesBuff);

      sksCommonTblApiBuff.sksCommonopc = 1; /* key */     
      sksCommonTblApiBuff.sksCommonfamily = 1;

      printf("\n cfgCmDbHndlr105: SksCommonTable Update Request - with dlPktPollGap and ulPktAckGap not in DB, sending");
      cfgStubSendCmMessage(&sksCommonTblApiBuff, sizeof(SksCommonTableApi),BSC_API_SET_SKSCOMMONTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SKSCOMMONTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SKSCOMMONTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr105: CM_SUCCESS: Successfully handled- Row added");
                  printf("\n cfgCmDbHndlr105: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr105: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr105: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr105*/


/* start of cfgCmDbHndlr106 */ 
void cfgCmDbHndlr106()
{
   static int testInitiation =1;    
   SksCommonTableApi sksCommonTblApiBuff = {0};
   SksCommonTableIndices SksCommonTableIndicesBuff;
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr106: SksCommonTable Update Request -Parameter modification - Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      /* Send SksCommonTable Update Request - with sksCommonopc and sksCommonfamily not in DB */
      SksCommonTableIndicesBuff.sksCommonopc=1;
      deleteSksCommonTable(&SksCommonTableIndicesBuff);

      sksCommonTblApiBuff.sksCommonopc = 1; /* key */     
      sksCommonTblApiBuff.sksCommonfamily = 1;

      insertSksCommonTable(&sksCommonTblApiBuff);

      sksCommonTblApiBuff.sksCommonfamily = 2;

      printf("\n cfgCmDbHndlr106: SksCommonTable Update Request ...\n");
      cfgStubSendCmMessage(&sksCommonTblApiBuff, sizeof(SksCommonTableApi),BSC_API_SET_SKSCOMMONTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SKSCOMMONTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SKSCOMMONTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr106: CM_SUCCESS: Successfully handled");
                  printf("\n cfgCmDbHndlr106: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr106: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr106: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr106*/


/* start of cfgCmDbHndlr107 */
void cfgCmDbHndlr107()
{
   static int testInitiation =1;    
   SksCommonTableApi sksCommonTblApiBuff = {0};
   SksCommonTableIndices SksCommonTableIndicesBuff;
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr107: SksCommonTable Update Request -Timeout case- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      /* Send SksCommonTable Update Request - with sksCommonopc and sksCommonfamily not in DB */
      SksCommonTableIndicesBuff.sksCommonopc=1;

      deleteSksCommonTable(&SksCommonTableIndicesBuff);

      sksCommonTblApiBuff.sksCommonopc = 1; /* key */     
      sksCommonTblApiBuff.sksCommonfamily = 1;

      insertSksCommonTable(&sksCommonTblApiBuff);

      sksCommonTblApiBuff.sksCommonfamily = 2;

      printf("\n cfgCmDbHndlr107: SksCommonTable Update Request ...\n");
      cfgStubSendCmMessage(&sksCommonTblApiBuff, sizeof(SksCommonTableApi),BSC_API_SET_SKSCOMMONTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SKSCOMMONTABLE :
            {
               printf("Received BSC_API_SET_SKSCOMMONTABLE, Don't send RSP \n");
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr107:CM_ERR_END, TimeOut case \n");
                  printf("\n cfgCmDbHndlr107: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr107: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr107: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

} /* End 0f cfgCmDbHndlr107 */

/* start of cfgCmDbHndlr108 */ 
void cfgCmDbHndlr108()
{
   static int testInitiation =1;    
   SksCommonTableApi sksCommonTblApiBuff = {0};
   SksCommonTableIndices SksCommonTableIndicesBuff;
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr108: SksCommonTable Update Request - with Same Parameter values as in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      /* Send SksCommonTable Update Request - with sksCommonopc and sksCommonfamily not in DB */
      SksCommonTableIndicesBuff.sksCommonopc=1;

      deleteSksCommonTable(&SksCommonTableIndicesBuff);

      sksCommonTblApiBuff.sksCommonopc = 1; /* key */     
      sksCommonTblApiBuff.sksCommonfamily = 1;

      insertSksCommonTable(&sksCommonTblApiBuff);

      /* Don't Modify the parameter */
      printf("\n cfgCmDbHndlr108: SksCommonTable Same parameter updation ...\n");
      cfgStubSendCmMessage(&sksCommonTblApiBuff, sizeof(SksCommonTableApi),BSC_API_SET_SKSCOMMONTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr108:CM_ERR_END, \n");
                  printf("\n cfgCmDbHndlr108: Test Case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr108: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr108: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

} /* End of cfgCmDbHndlr108 */

/* start of cfgCmDbHndlr109 */
void cfgCmDbHndlr109()
{
   static int testInitiation =1;
   I_S32 errCode = 0;

   SksLinkstartTableApi sksLinkstartTblApiBuff = {0};
   SksLinkstartTableIndices SksLinkstartTableIndicesBuff = {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr109: SksLinkstartTable Update Request - with sksLinkStartLink not in DB- Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      SksLinkstartTableIndicesBuff.sksLinkStartLink =1;

      deleteSksLinkstartTable(&SksLinkstartTableIndicesBuff);

      /* Send SksLinkstartTable Update Request - with sksLinkStartLink not in DB */
      sksLinkstartTblApiBuff.sksLinkStartLink= 1; /*key*/

      printf("\n cfgCmDbHndlr109: SksLinkstartTable Update Request - with sksLinkStartLink not in DB, sending");
      cfgStubSendCmMessage(&sksLinkstartTblApiBuff, sizeof(SksLinkstartTableApi),BSC_API_SET_SKSLINKSTARTTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SKSLINKSTARTTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SKSLINKSTARTTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr109: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  printf("\n cfgCmDbHndlr109: problem in handling, chk code");
               }
               gTestCaseCompleted = 1;
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr109: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

} /* end of cfgCmDbHndlr109*/

void cfgCmDbHndlr110()
{
   static int testInitiation =1;
   I_S32 errCode = 0;

   SksLinkstartTableApi sksLinkstartTblApiBuff = {0};
   SksLinkstartTableIndices SksLinkstartTableIndicesBuff = {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr110: SksLinkstartTable Update Request - with sksLinkStartLink not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      SksLinkstartTableIndicesBuff.sksLinkStartLink =1;

      deleteSksLinkstartTable(&SksLinkstartTableIndicesBuff);

      /* Send SksLinkstartTable Update Request - with sksLinkStartLink not in DB */
      sksLinkstartTblApiBuff.sksLinkStartLink= 1; /*key*/

      insertSksLinkstartTable(&sksLinkstartTblApiBuff); 

      sksLinkstartTblApiBuff.sksLinkStartLink= 2; /*key*/
      printf("\n cfgCmDbHndlr110: SksLinkstartTable Update Request - with sksLinkStartLink not in DB, sending");
      cfgStubSendCmMessage(&sksLinkstartTblApiBuff, sizeof(SksLinkstartTableApi),BSC_API_SET_SKSLINKSTARTTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SKSLINKSTARTTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SKSLINKSTARTTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr110: CM_SUCCESS: Successfully handled- Row added");
               }
               else
               {
                  printf("\n cfgCmDbHndlr110: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr110: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

} /* End of cfgCmDbHndlr110 */


void cfgCmDbHndlr111()
{
   static int testInitiation =1;
   I_S32 errCode = 0;

   SksLinkstartTableApi sksLinkstartTblApiBuff = {0};
   SksLinkstartTableIndices SksLinkstartTableIndicesBuff = {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr111: SksLinkstartTable Update Request -Timeout Case- Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      SksLinkstartTableIndicesBuff.sksLinkStartLink =1;

      deleteSksLinkstartTable(&SksLinkstartTableIndicesBuff);

      /* Send SksLinkstartTable Update Request - with sksLinkStartLink not in DB */
      sksLinkstartTblApiBuff.sksLinkStartLink= 1; /*key*/

      printf("\n cfgCmDbHndlr111: SksLinkstartTable Update Request - with sksLinkStartLink not in DB, sending");
      cfgStubSendCmMessage(&sksLinkstartTblApiBuff, sizeof(SksLinkstartTableApi),BSC_API_SET_SKSLINKSTARTTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SKSLINKSTARTTABLE :
            {
               /* don't send any response */
               printf("Received BSC_API_SET_SKSLINKSTARTTABLE, don't Send Rsp\n");
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr111: CM_ERR_END\n");
                  printf("\n cfgCmDbHndlr111: Test Case Passed\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr111: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr111: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

} /* End of cfgCmDbHndlr111 */

/* Start of cfgCmDbHndlr112 */
void cfgCmDbHndlr112()
{
   static int testInitiation =1;
   I_S32 errCode = 0;

   SksLinkstartTableApi sksLinkstartTblApiBuff = {0};
   SksLinkstartTableIndices SksLinkstartTableIndicesBuff = {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr112: SksLinkstartTable Update Request - with same Parameter values as in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      SksLinkstartTableIndicesBuff.sksLinkStartLink =1;

      deleteSksLinkstartTable(&SksLinkstartTableIndicesBuff);

      /* Send SksLinkstartTable Update Request - with sksLinkStartLink not in DB */
      sksLinkstartTblApiBuff.sksLinkStartLink= 1; /*key*/

      insertSksLinkstartTable(&sksLinkstartTblApiBuff); 

      printf("\n cfgCmDbHndlr112: SksLinkstartTable Update Request - with same Parameter values as in DB-sending");
      cfgStubSendCmMessage(&sksLinkstartTblApiBuff, sizeof(SksLinkstartTableApi),BSC_API_SET_SKSLINKSTARTTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         /* case BSC_API_SET_SKSLINKSTARTTABLE :
            {
            cfgStubSendCmMessageFromOil(BSC_API_SET_SKSLINKSTARTTABLE,CM_SUCCESS);
            }
            break;*/
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr112: CM_SUCCESS: Successfully handled");
               }
               else
               {
                  printf("\n cfgCmDbHndlr112: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr112: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/
} /* End of cfgCmDbHndlr112 */


/* start of cfgCmDbHndlr113 */
void cfgCmDbHndlr113()
{
   static int testInitiation =1;
   I_S32 errCode = 0;

   SksGenCfgTableApi sksGenCfgTblApiBuff = {0};
   SksGenCfgTableIndices SksGenCfgTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr113: sksGenCfgTable Update Request - with sksGenCfgstackIndex not in DB- Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();


      /* Send sksGenCfgTable Update Request - with sksGenCfgstackIndex not in DB */
      sksGenCfgTblApiBuff.sksGenCfgstackIndex= 1; /* key */
      memset(&(sksGenCfgTblApiBuff.sksGenCfgdescript),1,20);
      sksGenCfgTblApiBuff.sksGenCfgalarmLevel= 1;
      sksGenCfgTblApiBuff.sksGenCfgtraceType= 1;
      //sksGenCfgTblApiBuff.sksGenCfgtraceOutput= 1;
      sksGenCfgTblApiBuff.sksGenCfgtraceOnOff= 1;

      SksGenCfgTableIndicesBuff.sksGenCfgstackIndex=1;
      deleteSksGenCfgTable(&SksGenCfgTableIndicesBuff);

      printf("\n cfgCmDbHndlr113: sksGenCfgTable INSERT, sending");
      cfgStubSendCmMessage(&sksGenCfgTblApiBuff, sizeof(SksGenCfgTableApi),BSC_API_SET_SKSGENCFGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SKSGENCFGTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SKSGENCFGTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr113: CM_SUCCESS: Successfully handled- Row added");
                  printf("\n cfgCmDbHndlr113: Test case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr113: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr113: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr113*/


void cfgCmDbHndlr114()
{
   static int testInitiation =1;
   I_S32 errCode = 0;

   SksGenCfgTableApi sksGenCfgTblApiBuff = {0};
   SksGenCfgTableIndices SksGenCfgTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr114: sksGenCfgTable Update Request -Parameter Modification- Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      /* Send sksGenCfgTable Update Request - with sksGenCfgstackIndex not in DB */
      sksGenCfgTblApiBuff.sksGenCfgstackIndex= 1; /* key */
      memset(&(sksGenCfgTblApiBuff.sksGenCfgdescript),1,20);
      sksGenCfgTblApiBuff.sksGenCfgalarmLevel= 1;
      sksGenCfgTblApiBuff.sksGenCfgtraceType= 1;
      //sksGenCfgTblApiBuff.sksGenCfgtraceOutput= 1;
      sksGenCfgTblApiBuff.sksGenCfgtraceOnOff= 1;

      SksGenCfgTableIndicesBuff.sksGenCfgstackIndex=1;

      deleteSksGenCfgTable(&SksGenCfgTableIndicesBuff);

      insertSksGenCfgTable(&sksGenCfgTblApiBuff);

      /* Modify the parameter */
      sksGenCfgTblApiBuff.sksGenCfgtraceOnOff= 2;

      printf("\n cfgCmDbHndlr114: sksGenCfgTable UPDATE, sending");
      cfgStubSendCmMessage(&sksGenCfgTblApiBuff, sizeof(SksGenCfgTableApi),BSC_API_SET_SKSGENCFGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SKSGENCFGTABLE :
            {
               cfgStubSendCmMessageFromOil(BSC_API_SET_SKSGENCFGTABLE,CM_SUCCESS);
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr114: CM_SUCCESS: Successfully handled");
                  printf("\n cfgCmDbHndlr114: Test case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr114: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr114: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

} /* end of cfgCmDbHndlr114*/


/* Start of cfgCmDbHndlr115*/
void cfgCmDbHndlr115()
{
   static int testInitiation =1;
   I_S32 errCode = 0;

   SksGenCfgTableApi sksGenCfgTblApiBuff = {0};
   SksGenCfgTableIndices SksGenCfgTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr115: sksGenCfgTable Update Request - Timeout case- Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      /* Send sksGenCfgTable Update Request - with sksGenCfgstackIndex not in DB */
      sksGenCfgTblApiBuff.sksGenCfgstackIndex= 1; /* key */
      memset(&(sksGenCfgTblApiBuff.sksGenCfgdescript),1,20);
      sksGenCfgTblApiBuff.sksGenCfgalarmLevel= 1;
      sksGenCfgTblApiBuff.sksGenCfgtraceType= 1;
      //sksGenCfgTblApiBuff.sksGenCfgtraceOutput= 1;
      sksGenCfgTblApiBuff.sksGenCfgtraceOnOff= 1;

      SksGenCfgTableIndicesBuff.sksGenCfgstackIndex=1;

      deleteSksGenCfgTable(&SksGenCfgTableIndicesBuff);

      insertSksGenCfgTable(&sksGenCfgTblApiBuff);

      /* Modify the parameter */
      sksGenCfgTblApiBuff.sksGenCfgtraceOnOff= 2;

      printf("\n cfgCmDbHndlr115: sksGenCfgTable UPDATE, sending");
      cfgStubSendCmMessage(&sksGenCfgTblApiBuff, sizeof(SksGenCfgTableApi),BSC_API_SET_SKSGENCFGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_SET_SKSGENCFGTABLE :
            {
               printf(" Received BSC_API_SET_SKSGENCFGTABLE, don't send Rsp \n");
            }
            break;
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr115: CM_ERR_END: Time out case ");
                  printf("\n cfgCmDbHndlr115: Test case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr115: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr115: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

} /* End of cfgCmDbHndlr115 */


/* Start of cfgCmDbHndlr116 */
void cfgCmDbHndlr116()
{
   static int testInitiation =1;
   I_S32 errCode = 0;

   SksGenCfgTableApi sksGenCfgTblApiBuff = {0};
   SksGenCfgTableIndices SksGenCfgTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr116: sksGenCfgTable Update Request - with same parameter values as in DB- Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      /* Send sksGenCfgTable Update Request - with sksGenCfgstackIndex not in DB */
      sksGenCfgTblApiBuff.sksGenCfgstackIndex= 1; /* key */
      memset(&(sksGenCfgTblApiBuff.sksGenCfgdescript),1,20);
      sksGenCfgTblApiBuff.sksGenCfgalarmLevel= 1;
      sksGenCfgTblApiBuff.sksGenCfgtraceType= 1;
      //sksGenCfgTblApiBuff.sksGenCfgtraceOutput= 1;
      sksGenCfgTblApiBuff.sksGenCfgtraceOnOff= 1;

      SksGenCfgTableIndicesBuff.sksGenCfgstackIndex=1;

      deleteSksGenCfgTable(&SksGenCfgTableIndicesBuff);

      insertSksGenCfgTable(&sksGenCfgTblApiBuff);

      /* Donot Modify the parameter */
      printf("\n cfgCmDbHndlr116: sksGenCfgTable UPDATE, sending");
      cfgStubSendCmMessage(&sksGenCfgTblApiBuff, sizeof(SksGenCfgTableApi),BSC_API_SET_SKSGENCFGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr116: CM_ERR_END: No parameter change\n ");
                  printf("\n cfgCmDbHndlr116: Test case Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr116: problem in handling, chk code");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr116: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

} /* End 0f cfgCmDbHndlr116 */

/* Start of cfgCmDbHndlr170 */
void cfgCmDbHndlr170()
{
   static int testInitiation =1;   
   SksGenCfgTableApi sksGenConfigTableApiBuff = {0};
   SksGenCfgTableIndices SksGenCfgTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr170 started -- ");             

      /* First set the BSS - precondition */
      setDbForBss();

      SksGenCfgTableIndicesBuff.sksGenCfgstackIndex=1;
      deleteSksGenCfgTable(&SksGenCfgTableIndicesBuff);

      sksGenConfigTableApiBuff.sksGenCfgstackIndex =1;

      printf("\nSending BSC_API_DEL_SKSGENCFGTABLE");
      cfgStubSendCmMessage(&sksGenConfigTableApiBuff,sizeof(SksGenCfgTableApi),BSC_API_DEL_SKSGENCFGTABLE );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr170: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr170: Success");
                  printf("In cfgCmDbHndlr170:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr170: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr170 */

/* Start of cfgCmDbHndlr169 */
void cfgCmDbHndlr169()
{
   static int testInitiation =1;   
   SksGenCfgTableApi sksGenConfigTableApiBuff = {0};
   SksGenCfgTableIndices SksGenCfgTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr169 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      SksGenCfgTableIndicesBuff.sksGenCfgstackIndex=1;
      deleteSksGenCfgTable(&SksGenCfgTableIndicesBuff);

      printf("\nSending BSC_API_DEL_SKSGENCFGTABLE");

      sksGenConfigTableApiBuff.sksGenCfgstackIndex =1;

      insertSksGenCfgTable(&sksGenConfigTableApiBuff);

      cfgStubSendCmMessage(&sksGenConfigTableApiBuff,sizeof(SksGenCfgTableApi),BSC_API_DEL_SKSGENCFGTABLE );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_SKSGENCFGTABLE  :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_SKSGENCFGTABLE ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr169: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr169: Failed");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr169: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr169 */

/* Start of cfgCmDbHndlr168 */
void cfgCmDbHndlr168()
{
   static int testInitiation =1;   
   SksLinkstartTableApi sksLinkStartTblApiBuff = {0};
   SksLinkstartTableIndices SksLinkstartTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr168 started -- ");             

      /* First set the BSS - precondition */
      setDbForBss();

      SksLinkstartTableIndicesBuff.sksLinkStartLink=1;
      deleteSksLinkstartTable(&SksLinkstartTableIndicesBuff);

      sksLinkStartTblApiBuff.sksLinkStartLink =1;
      printf("\nSending BSC_API_DEL_SKSLINKSTARTTABLE ");
      cfgStubSendCmMessage(&sksLinkStartTblApiBuff,sizeof(SksLinkstartTableApi),BSC_API_DEL_SKSLINKSTARTTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr168: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr168: Success");
                  printf("In cfgCmDbHndlr168:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr168: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr168 */

/* Start of cfgCmDbHndlr167 */
void cfgCmDbHndlr167()
{
   static int testInitiation =1;   
   SksLinkstartTableApi sksLinkStartTblApiBuff = {0};
   SksLinkstartTableIndices SksLinkstartTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr167 started -- ");             

      /* First set the BSS - precondition */
      setDbForBss();

      SksLinkstartTableIndicesBuff.sksLinkStartLink=1;
      deleteSksLinkstartTable(&SksLinkstartTableIndicesBuff);

      printf("\nSending BSC_API_DEL_SKSLINKSTARTTABLE ");
      sksLinkStartTblApiBuff.sksLinkStartLink =1;
      insertSksLinkstartTable(&sksLinkStartTblApiBuff);

      cfgStubSendCmMessage(&sksLinkStartTblApiBuff,sizeof(SksLinkstartTableApi),BSC_API_DEL_SKSLINKSTARTTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_SKSLINKSTARTTABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_SKSLINKSTARTTABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr167: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr167: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr167: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr167 */

/* Start of cfgCmDbHndlr166 */
void cfgCmDbHndlr166()
{
   static int testInitiation =1;   
   SksCommonTableApi sksCommonTblApiBuff = {0};
   SksCommonTableIndices SksCommonTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr166 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      SksCommonTableIndicesBuff.sksCommonopc=1;
      deleteSksCommonTable(&SksCommonTableIndicesBuff);

      sksCommonTblApiBuff.sksCommonopc =1;

      printf("\nSending BSC_API_DEL_SKSCOMMONTABLE ");
      cfgStubSendCmMessage(&sksCommonTblApiBuff,sizeof(SksCommonTableApi),BSC_API_DEL_SKSCOMMONTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr166: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr166: Success");
                  printf("In cfgCmDbHndlr166:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr166: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr166 */

/* Start of cfgCmDbHndlr165 */
void cfgCmDbHndlr165()
{
   static int testInitiation =1;   
   SksCommonTableApi sksCommonTblApiBuff = {0};
   SksCommonTableIndices SksCommonTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr165 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      SksCommonTableIndicesBuff.sksCommonopc=1;
      deleteSksCommonTable(&SksCommonTableIndicesBuff);

      printf("\nSending BSC_API_DEL_SKSCOMMONTABLE ");

      sksCommonTblApiBuff.sksCommonopc =1;
      insertSksCommonTable(&sksCommonTblApiBuff);

      cfgStubSendCmMessage(&sksCommonTblApiBuff,sizeof(SksCommonTableApi),BSC_API_DEL_SKSCOMMONTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_SKSCOMMONTABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_SKSCOMMONTABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr165: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr165: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr165: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr165 */

/* Start of cfgCmDbHndlr162 */
void cfgCmDbHndlr162()
{
   static int testInitiation =1;   
   SccpCSSNConfigTableApi SccpCssnConfigApiBuff = {0};
   SccpCSSNConfigTableIndices SccpCSSNConfigTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr162 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigssn =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigpc =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigni =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigcssn =1;
      deleteSccpCSSNConfigTable(&SccpCSSNConfigTableIndicesBuff);

      SccpCssnConfigApiBuff.sccpCSsnConfigssn =1;
      SccpCssnConfigApiBuff.sccpCSsnConfigpc =1;
      SccpCssnConfigApiBuff.sccpCSsnConfigni =1;
      SccpCssnConfigApiBuff.sccpCSsnConfigcssn =1;
      printf("\nSending BSC_API_DEL_SCCPCSSNCONFIGTABLE ");

      cfgStubSendCmMessage(&SccpCssnConfigApiBuff,sizeof(SccpCSSNConfigTableApi),BSC_API_DEL_SCCPCSSNCONFIGTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr162: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr162: Success");
                  printf("In cfgCmDbHndlr162:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr162: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr162 */

/* Start of cfgCmDbHndlr161 */
void cfgCmDbHndlr161()
{
   static int testInitiation =1;   
   SccpCSSNConfigTableApi SccpCssnConfigApiBuff = {0};
   SccpCSSNConfigTableIndices SccpCSSNConfigTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr161 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigssn =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigpc =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigni =1;
      SccpCSSNConfigTableIndicesBuff.sccpCSsnConfigcssn =1;
      deleteSccpCSSNConfigTable(&SccpCSSNConfigTableIndicesBuff);

      printf("\nSending BSC_API_DEL_SCCPCSSNCONFIGTABLE ");
      SccpCssnConfigApiBuff.sccpCSsnConfigssn =1;
      SccpCssnConfigApiBuff.sccpCSsnConfigpc =1;
      SccpCssnConfigApiBuff.sccpCSsnConfigni =1;
      SccpCssnConfigApiBuff.sccpCSsnConfigcssn =1;

      insertSccpCSSNConfigTable(&SccpCssnConfigApiBuff);

      cfgStubSendCmMessage(&SccpCssnConfigApiBuff,sizeof(SccpCSSNConfigTableApi),BSC_API_DEL_SCCPCSSNCONFIGTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_SCCPCSSNCONFIGTABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_SCCPCSSNCONFIGTABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr161: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr161: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr161: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr161 */

/* Start of cfgCmDbHndlr160 */
void cfgCmDbHndlr160()
{
   static int testInitiation =1;   
   SccpSsnConfigTableApi SccpSsnConfigApiBuff = {0};
   SccpSsnConfigTableIndices SccpSsnConfigTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr160 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigssn= (I_U16)1;//No Range Check
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigpc= (I_U32)2;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigni= (I_U16)3;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigisLocal= (I_U16)4;

      deleteSccpSsnConfigTable(&SccpSsnConfigTableIndicesBuff);

      SccpSsnConfigApiBuff.sccpSsnConfigssn= (I_U16)1;//No Range Check
      SccpSsnConfigApiBuff.sccpSsnConfigpc= (I_U32)2;
      SccpSsnConfigApiBuff.sccpSsnConfigni= (I_U16)3;
      SccpSsnConfigApiBuff.sccpSsnConfigisLocal= (I_U16)4;

      printf("\nSending BSC_API_DEL_SCCPSSNCONFIGTABLE ");
      cfgStubSendCmMessage(&SccpSsnConfigApiBuff,sizeof(SccpSsnConfigTableApi),BSC_API_DEL_SCCPSSNCONFIGTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr160: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr160: Success");
                  printf("In cfgCmDbHndlr160:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr160: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr160 */

/* Start of cfgCmDbHndlr159 */
void cfgCmDbHndlr159()
{
   static int testInitiation =1;   
   SccpSsnConfigTableApi SccpSsnConfigApiBuff = {0};
   SccpSsnConfigTableIndices SccpSsnConfigTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr159 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      SccpSsnConfigTableIndicesBuff.sccpSsnConfigssn= (I_U16)1;//No Range Check
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigpc= (I_U32)2;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigni= (I_U16)3;
      SccpSsnConfigTableIndicesBuff.sccpSsnConfigisLocal= (I_U16)4;

      deleteSccpSsnConfigTable(&SccpSsnConfigTableIndicesBuff);

      printf("\nSending BSC_API_DEL_SCCPSSNCONFIGTABLE ");

      SccpSsnConfigApiBuff.sccpSsnConfigssn= (I_U16)1;//No Range Check
      SccpSsnConfigApiBuff.sccpSsnConfigpc= (I_U32)2;
      SccpSsnConfigApiBuff.sccpSsnConfigni= (I_U16)3;
      SccpSsnConfigApiBuff.sccpSsnConfigisLocal= (I_U16)4;

      insertSccpSsnConfigTable(&SccpSsnConfigApiBuff);

      cfgStubSendCmMessage(&SccpSsnConfigApiBuff,sizeof(SccpSsnConfigTableApi),BSC_API_DEL_SCCPSSNCONFIGTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_SCCPSSNCONFIGTABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_SCCPSSNCONFIGTABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr159: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr159: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr159: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr159 */

/* Start of cfgCmDbHndlr151 */
void cfgCmDbHndlr151()
{
   static int testInitiation =1;   
   Mtp3RemotePointCodeStsTableApi Mtp3RemotePointCodeStsTableApiBuff = {0};
   Mtp3RemotePointCodeStsTableIndices Mtp3RemotePointCodeStsTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr151 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCoderpc = 19;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodeni = 20;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodelinksetID = 21;


      deleteMtp3RemotePointCodeStsTable(&Mtp3RemotePointCodeStsTableIndicesBuff);
      printf("\nSending BSC_API_DEL_MTP3REMOTEPOINTCODESTSTABLE ");
      Mtp3RemotePointCodeStsTableApiBuff.mtp3RemotePointCoderpc = 19;
      Mtp3RemotePointCodeStsTableApiBuff.mtp3RemotePointCodeni = 20;
      Mtp3RemotePointCodeStsTableApiBuff.mtp3RemotePointCodelinksetID = 21;

      printf("\nSending BSC_API_DEL_MTP3REMOTEPOINTCODESTSTABLE ");
      cfgStubSendCmMessage(&Mtp3RemotePointCodeStsTableApiBuff,sizeof(Mtp3RemotePointCodeStsTableApi),BSC_API_DEL_MTP3REMOTEPOINTCODESTSTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr151: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr151: Success");
                  printf("In cfgCmDbHndlr151:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr151: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr151 */

/* Start of cfgCmDbHndlr150 */
void cfgCmDbHndlr150()
{
   static int testInitiation =1;   
   Mtp3RemotePointCodeStsTableApi Mtp3RemotePointCodeStsTableApiBuff = {0};
   Mtp3RemotePointCodeStsTableIndices Mtp3RemotePointCodeStsTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr150 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCoderpc = 19;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodeni = 20;
      Mtp3RemotePointCodeStsTableIndicesBuff.mtp3RemotePointCodelinksetID = 21;

      deleteMtp3RemotePointCodeStsTable(&Mtp3RemotePointCodeStsTableIndicesBuff);
      printf("\nSending BSC_API_DEL_MTP3REMOTEPOINTCODESTSTABLE ");

      Mtp3RemotePointCodeStsTableApiBuff.mtp3RemotePointCoderpc = 19;
      Mtp3RemotePointCodeStsTableApiBuff.mtp3RemotePointCodeni = 20;
      Mtp3RemotePointCodeStsTableApiBuff.mtp3RemotePointCodelinksetID = 21;

      insertMtp3RemotePointCodeStsTable(&Mtp3RemotePointCodeStsTableApiBuff);

      cfgStubSendCmMessage(&Mtp3RemotePointCodeStsTableApiBuff,sizeof(Mtp3RemotePointCodeStsTableApi),BSC_API_DEL_MTP3REMOTEPOINTCODESTSTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_MTP3REMOTEPOINTCODESTSTABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_MTP3REMOTEPOINTCODESTSTABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr150: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr150: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr150: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr150 */

/* Start of cfgCmDbHndlr149 */
void cfgCmDbHndlr149()
{
   static int testInitiation =1;   
   LinkAdminStateTableApi LinkAdminStateTableApiBuff = {0};
   LinkAdminStateTableIndices LinkAdminStateTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr149 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      LinkAdminStateTableIndicesBuff.linkAdminlinkCode = 19;
      LinkAdminStateTableIndicesBuff.linkAdminlinksetID = 20;


      deleteLinkAdminStateTable(&LinkAdminStateTableIndicesBuff);

      LinkAdminStateTableApiBuff.linkAdminlinkCode = 19;
      LinkAdminStateTableApiBuff.linkAdminlinksetID = 20;

      printf("\nSending BSC_API_DEL_LINKADMINSTATETABLE ");
      cfgStubSendCmMessage(&LinkAdminStateTableApiBuff,sizeof(LinkAdminStateTableApi),BSC_API_DEL_LINKADMINSTATETABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr149: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr149: Success");
                  printf("In cfgCmDbHndlr149:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr149: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr149 */

/* Start of cfgCmDbHndlr148 */
void cfgCmDbHndlr148()
{
   static int testInitiation =1;   
   LinkAdminStateTableApi LinkAdminStateTableApiBuff = {0};
   LinkAdminStateTableIndices LinkAdminStateTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr148 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      LinkAdminStateTableIndicesBuff.linkAdminlinkCode = 19;
      LinkAdminStateTableIndicesBuff.linkAdminlinksetID = 20;

      deleteLinkAdminStateTable(&LinkAdminStateTableIndicesBuff);
      printf("\nSending BSC_API_DEL_LINKADMINSTATETABLE ");

      LinkAdminStateTableApiBuff.linkAdminlinkCode = 19;
      LinkAdminStateTableApiBuff.linkAdminlinksetID = 20;

      insertLinkAdminStateTable(&LinkAdminStateTableApiBuff);

      cfgStubSendCmMessage(&LinkAdminStateTableApiBuff,sizeof(LinkAdminStateTableApi),BSC_API_DEL_LINKADMINSTATETABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_LINKADMINSTATETABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_LINKADMINSTATETABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr148: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr148: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr148: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr148 */

/* Start of cfgCmDbHndlr147 */
void cfgCmDbHndlr147()
{
   static int testInitiation =1;   
   Mtp3LinkTableApi Mtp3LinkTableApiBuff = {0};
   Mtp3LinkTableIndices Mtp3LinkTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr147 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      Mtp3LinkTableIndicesBuff.mtp3LinklinkCode = 19;
      Mtp3LinkTableIndicesBuff.mtp3LinklinksetID = 20;

      deleteMtp3LinkTable(&Mtp3LinkTableIndicesBuff);

      Mtp3LinkTableApiBuff.mtp3LinklinkCode = 19;
      Mtp3LinkTableApiBuff.mtp3LinklinksetID = 20;


      printf("\nSending BSC_API_DEL_MTP3LINKTABLE ");
      cfgStubSendCmMessage(&Mtp3LinkTableApiBuff,sizeof(Mtp3LinkTableApi),BSC_API_DEL_MTP3LINKTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr147: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr147: Success");
                  printf("In cfgCmDbHndlr147:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr147: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr147 */

/* Start of cfgCmDbHndlr146 */
void cfgCmDbHndlr146()
{
   static int testInitiation =1;   
   Mtp3LinkTableApi Mtp3LinkTableApiBuff = {0};
   Mtp3LinkTableIndices Mtp3LinkTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr146 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      Mtp3LinkTableIndicesBuff.mtp3LinklinkCode = 19;
      Mtp3LinkTableIndicesBuff.mtp3LinklinksetID = 20;

      deleteMtp3LinkTable(&Mtp3LinkTableIndicesBuff);
      printf("\nSending BSC_API_DEL_MTP3LINKTABLE ");

      Mtp3LinkTableApiBuff.mtp3LinklinkCode = 19;
      Mtp3LinkTableApiBuff.mtp3LinklinksetID = 20;

      insertMtp3LinkTable(&Mtp3LinkTableApiBuff);

      cfgStubSendCmMessage(&Mtp3LinkTableApiBuff,sizeof(Mtp3LinkTableApi),BSC_API_DEL_MTP3LINKTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_MTP3LINKTABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_MTP3LINKTABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr146: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr146: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr146: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr146 */

/* Start of cfgCmDbHndlr145 */
void cfgCmDbHndlr145()
{
   static int testInitiation =1;   
   Mtp3LinksetStsTableApi Mtp3LinksetStsTableApiBuff = {0};
   Mtp3LinksetStsTableIndices Mtp3LinksetStsTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr145 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      Mtp3LinksetStsTableIndicesBuff.MTP3LinksetlinksetID = 19;


      deleteMtp3LinksetStsTable(&Mtp3LinksetStsTableIndicesBuff);

      Mtp3LinksetStsTableApiBuff.MTP3LinksetlinksetID = 19;


      printf("\nSending BSC_API_DEL_MTP3LINKSETSTSTABLE ");
      cfgStubSendCmMessage(&Mtp3LinksetStsTableApiBuff,sizeof(Mtp3LinksetStsTableApi),BSC_API_DEL_MTP3LINKSETSTSTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr145: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr145: Success");
                  printf("In cfgCmDbHndlr145:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr145: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr145 */

/* Start of cfgCmDbHndlr144 */
void cfgCmDbHndlr144()
{
   static int testInitiation =1;   
   Mtp3LinksetStsTableApi Mtp3LinksetStsTableApiBuff = {0};
   Mtp3LinksetStsTableIndices Mtp3LinksetStsTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr144 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      Mtp3LinksetStsTableIndicesBuff.MTP3LinksetlinksetID = 19;

      deleteMtp3LinksetStsTable(&Mtp3LinksetStsTableIndicesBuff);
      printf("\nSending BSC_API_DEL_MTP3LINKSETSTSTABLE ");

      Mtp3LinksetStsTableApiBuff.MTP3LinksetlinksetID = 19;

      insertMtp3LinksetStsTable(&Mtp3LinksetStsTableApiBuff);

      cfgStubSendCmMessage(&Mtp3LinksetStsTableApiBuff,sizeof(Mtp3LinksetStsTableApi),BSC_API_DEL_MTP3LINKSETSTSTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_MTP3LINKSETSTSTABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_MTP3LINKSETSTSTABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr144: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr144: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr144: Msg Discarded ");

      } /* end of Switch */


   }
} /* End 0f cfgCmDbHndlr144 */

/* Start of cfgCmDbHndlr143 */
void cfgCmDbHndlr143()
{
   static int testInitiation =1;   
   Mtp3RouteTableApi Mtp3RouteTableApiBuff = {0};
   Mtp3RouteTableIndices Mtp3RouteTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr143 started -- ");             
      /* First set the BSS - precondition */
      setDbForBss();

      Mtp3RouteTableIndicesBuff.mtp3RouterouteID = 19;

      deleteMtp3RouteTable(&Mtp3RouteTableIndicesBuff);

      Mtp3RouteTableApiBuff.mtp3RouterouteID = 19;

      printf("\nSending BSC_API_DEL_MTP3ROUTETABLE ");
      cfgStubSendCmMessage(&Mtp3RouteTableApiBuff,sizeof(Mtp3RouteTableApi),BSC_API_DEL_MTP3ROUTETABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr143: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr143: Success");
                  printf("In cfgCmDbHndlr143:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr143: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr143 */

/* Start of cfgCmDbHndlr142 */
void cfgCmDbHndlr142()
{
   static int testInitiation =1;   
   Mtp3RouteTableApi Mtp3RouteTableApiBuff = {0};
   Mtp3RouteTableIndices Mtp3RouteTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr142 started -- ");             

      /* First set the BSS - precondition */
      setDbForBss();

      Mtp3RouteTableIndicesBuff.mtp3RouterouteID = 19;

      deleteMtp3RouteTable(&Mtp3RouteTableIndicesBuff);
      printf("\nSending BSC_API_DEL_MTP3ROUTETABLE ");

      Mtp3RouteTableApiBuff.mtp3RouterouteID = 19;

      insertMtp3RouteTable(&Mtp3RouteTableApiBuff);

      cfgStubSendCmMessage(&Mtp3RouteTableApiBuff,sizeof(Mtp3RouteTableApi),BSC_API_DEL_MTP3ROUTETABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_MTP3ROUTETABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_MTP3ROUTETABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr142: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr142: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr142: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr142 */

/* Start of cfgCmDbHndlr141 */
void cfgCmDbHndlr141()
{
   static int testInitiation =1;   
   Mtp3LinksetTableApi Mtp3LinksetTableApiBuff = {0};
   Mtp3LinksetTableIndices Mtp3LinksetTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr141 started -- ");             

      /* First set the BSS - precondition */
      setDbForBss();

      Mtp3LinksetTableIndicesBuff.MTP3LinksetlinksetID = 19;

      deleteMtp3LinksetTable(&Mtp3LinksetTableIndicesBuff);

      Mtp3LinksetTableApiBuff.MTP3LinksetlinksetID = 19;

      printf("\nSending BSC_API_DEL_MTP3LINKSETTABLE ");
      cfgStubSendCmMessage(&Mtp3LinksetTableApiBuff,sizeof(Mtp3LinksetTableApi),BSC_API_DEL_MTP3LINKSETTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr141: Failure");
               }
               else
               {
                  printf("\n cfgCmDbHndlr141: Success");
                  printf("In cfgCmDbHndlr141:Completed Successfully\n");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr141: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr141 */

/* Start of cfgCmDbHndlr140 */
void cfgCmDbHndlr140()
{
   static int testInitiation =1;   
   Mtp3LinksetTableApi Mtp3LinksetTableApiBuff = {0};
   Mtp3LinksetTableIndices Mtp3LinksetTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n --cfgCmDbHndlr140 started -- ");             

      /* First set the BSS - precondition */
      setDbForBss();

      Mtp3LinksetTableIndicesBuff.MTP3LinksetlinksetID = 19;

      deleteMtp3LinksetTable(&Mtp3LinksetTableIndicesBuff);
      printf("\nSending BSC_API_DEL_MTP3LINKSETTABLE ");

      Mtp3LinksetTableApiBuff.MTP3LinksetlinksetID = 19;

      insertMtp3LinksetTable(&Mtp3LinksetTableApiBuff);

      cfgStubSendCmMessage(&Mtp3LinksetTableApiBuff,sizeof(Mtp3LinksetTableApi),BSC_API_DEL_MTP3LINKSETTABLE  );

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case BSC_API_DEL_MTP3LINKSETTABLE   :
            {
               cfgStubSendCmMessageFromOil(BSC_API_DEL_MTP3LINKSETTABLE  ,CM_SUCCESS);
            }
            break;

         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr140: Delete Table Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr140: Faild");
               }                    

            }break;     /* end of case CM_API_APP_RESPONSE */ 
         default:

            printf("\n In cfgCmDbHndlr140: Msg Discarded ");

      } /* end of Switch */
   }
} /* End 0f cfgCmDbHndlr140 */


