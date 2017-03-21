#include "dbs_includes.h"
#define ALLOCATION_ALLOWED 1
/***************************************************************************/

/*
	***************************************************************
		Insertion Of Dump For Various Tables
	***************************************************************
*/

I_Void insertDump()
{
   // insertLtrxDump();
   // insertDataPtrx();
//    insertDataPtrxPreconfig();
    insertDataCellTable();
    insertDataChannelUsageTable();
    insertDataChnGrp();
    insertDataTimeSlot();
    insertDataE1Table();
    insertDataCsNeighbourCell();
    insertPsNeighCell();
    insertDataSiPreconfig();
    insertDataBssPsPreConfig();
    insertDataPsCell();  
    insertDataCsExternalCell();
    insertDataRadioTimeslot();
    insertDataAllocationAllowedTable();
    insertDataObjectStateTable();
    insertDataBssCsPreConfTable();
    insertDataBssTable();
    insertDataPcuTable();
    insertDataChannelParamTable();
    insertDataLapdTimerTable();
    insertDataPpResourceTable ();
    insertDataTrauChannelUsageTable ();
   // insertDataMccTsUsageTable ();
    insertRadioClockTableApi();
   // insertDataRaTable();
    insertDataArfcnTable();
    insertDataAInterfaceTable();
    testDBE1StreamMap();
    testDBDspTrauResourcePreconfigured(); 
    testDBNailup(); 
    insertTrxTeiTrxTsTeiTabl();
    insertTrxTabl();
    insertDataBicTable();
    insertBicTeiMapTable();
    insertBicTrxTsTabl();
}

void insertBicTrxTsTabl()
{
       BicTrxTsTableApi inData;
       I_S32 errCode;
       I_U32 i;
       for(i=1;i<=4 ;i++)
       {
	 inData.trxPos  = i ;
         inData.startTs = i*3 ;
         errCode = insertBicTrxTsTable(&inData);
         if (errCode != CLIB_SUCCESS)
         {             fprintf(stdout, "Insertion failed: err = %s",clib_strerror(errCode));
            return;
         }

       } 
}
void insertDataBicTable()
{
       BicTableApi inData;
       I_S32 errCode;
       I_U32 i;
        for(i=0;i<12;i++)
        {
            inData.bicId = (I_U16)1+i;
            inData.numTrx = (I_U32)2;
            if(i<3)
            {
                inData.e1Id = (I_U8)1;
            }
            else if(i>=3 && i<=5)
            {
                inData.e1Id = (I_U8)2;
	    }
            else if(i>=6 && i<=8)
            {
                inData.e1Id = (I_U8)3;
	    }
	    else
            {
                inData.e1Id = (I_U8)4;
	    }
            errCode = insertBicTable(&inData);
         }
         if (errCode != CLIB_SUCCESS)
         {             fprintf(stdout, "Insertion failed: err = %s",clib_strerror(errCode));
            return;
         }
}



I_Void insertBicTeiMapTable()
{
       BicE1TeiMapTableApi inData;
       I_S32 errCode;
       I_U32 i;
       for(i=0;i<4;i++)
       {
           inData.bicTei = (I_U32)1 + i;
           inData. e1Id =  (I_U8)1 + i;
           errCode = insertBicE1TeiMapTable(&inData);
       }
       if (errCode != CLIB_SUCCESS)
       {
          fprintf(stdout, "InsertBicE1TeiMapTable failed: err = %s",clib_strerror(errCode));
          return;
       }
}


I_Void insertTrxTeiTrxTsTeiTabl()
{
   I_U32    counter;
   I_S32    errCode;
   TrxTsTeiTableApi inData;

   for(counter = 1 ; counter <= 24 ; counter++)
   {
      inData.ptrxId         = counter;
      inData.trxTei         = counter;
      if(counter <=6)
      {
          inData.e1Id           = 1;
      }
      else if(counter>=7 && counter<=12)
      { 
          inData.e1Id           = 2;
      }
      else if(counter>=13 && counter<=18)
      { 
          inData.e1Id           = 3;
      }
      else
      {
          inData.e1Id           = 4;
      }
      inData.startTsTraffic = (counter * 2) + (counter - 1);
      inData.lapdTs         =  (counter * 4) + (counter - 1);
      errCode = insertTrxTsTeiTable(&inData);
      if (errCode != CLIB_SUCCESS)
        printf("Insertion in trxTsTable failed\n");

   }
}

I_Void insertTrxTabl()
{
   I_U32    counter;
   I_S32    errCode;
   TrxTableApi  inData;

   for(counter = 1 ; counter <= 24 ; counter++)
   {
      inData.ptrxId         = counter;
      inData.adminState     = 0;
      inData.trxLocation    = 2;
      if(counter <= 2)
      {
          inData.bicId          = 1;
          inData.trxPos         = 1;
      }
      else if(counter >=3 && counter <=4)
      {      
          inData.bicId          = 2;
          inData.trxPos         = 2;
      }
      else if(counter >=5 && counter <=6)
      {      
          inData.bicId          = 3;
          inData.trxPos         = 3;
      }
      else if(counter >=7 && counter <=8)
      {      
          inData.bicId          = 4;
          inData.trxPos         = 1;
      }
      else if(counter >=9 && counter <=10)
      {      
          inData.bicId          = 5;
          inData.trxPos         = 2;
      }
      else if(counter >=11 && counter <=12)
      {      
          inData.bicId          = 6;
          inData.trxPos         = 3;
      }
      else if(counter >=13 && counter <=14)
      {      
          inData.bicId          = 7;
          inData.trxPos         = 4;
      }
      else if(counter >=15 && counter <=16)
      {      
          inData.bicId          = 8;
          inData.trxPos         = 3;
      }
      else if(counter >=17 && counter <=18)
      {      
          inData.bicId          = 9;
          inData.trxPos         = 2;
      }
      else if(counter >=19 && counter <=20)
      {      
          inData.bicId          = 10;
          inData.trxPos         = 4;
      }
      else if(counter >=21 && counter <=22)
      {      
          inData.bicId          = 11;
          inData.trxPos         = 3;
      }
      else
      {      
          inData.bicId          = 12;
          inData.trxPos         = 2;
      }
      inData.antennaID      = 5;
      inData.rfPathGain     = 2 ;      
      errCode = insertTrxTable(&inData);
      if (errCode != CLIB_SUCCESS)
        printf("Insertion in trxTable failed\n");

   }

}           
I_S32 insertRadioClockTableApi()
{
    RadioClockTableApi *inData ;
    inData=(RadioClockTableApi *)malloc(sizeof(RadioClockTableApi));
    inData->radioClockId= 0;
    inData->oprStatus =(I_U32)1 ;
    insertRadioClockTable(inData);
}
  
  
I_Void insertLtrxDump()
{
   I_S32 errCode;
   I_U32 counter;
   I_U32 random;
   I_U32 i;

   LtrxTableApi ltrxInData;
 
   /*  ******************* Ltrx Table *************************/
    for(counter = 0 ; counter <= 4 ; counter++)
    {
       random = rand()%10;
       if(counter%2 ==0)
        { 
            i = 0;
        }
        else
        {
            i=1;
        }
       ltrxInData.ltrxId	= (I_U32)counter+10;
       ltrxInData.cellId	= (I_U32)14+i;
       ltrxInData.lac		= (I_U32)20;
       ltrxInData.chnGrpId	= (I_U32)0;
       ltrxInData.ptrxId	= (I_U32)counter;
       ltrxInData.ltrxPriority	= (I_U32)random;
       ltrxInData.mappingStatus	= (I_U32)1;
       ltrxInData.maio		= (I_U32)0;
       ltrxInData.availabilityStatus= (I_U32)0;
       ltrxInData.channelTypeTs0= (I_U32)0;
       ltrxInData.channelTypeTs1= (I_U32)0;
       ltrxInData.channelTypeTs2= (I_U32)0;
       ltrxInData.channelTypeTs3= (I_U32)0;
       ltrxInData.channelTypeTs4= (I_U32)0;
       ltrxInData.channelTypeTs5= (I_U32)0;
       ltrxInData.channelTypeTs6= (I_U32)0;
       ltrxInData.channelTypeTs7= (I_U32)0;

  //     ltrxIndices.ltrxId	= (I_U32)counter+10;

/*      errCode = deleteLtrxTable(&ltrxIndices);
      if (errCode != CLIB_SUCCESS)
 	printf("Deletion in ltrx table failed\n");
*/
      errCode = insertLtrxTable(&ltrxInData);
      if (errCode != CLIB_SUCCESS)
 	printf("Insertion in ltrx table failed\n");

  /*    errCode = updateLtrxTable(&ltrxInData);
      if (errCode != CLIB_SUCCESS)
 	printf("Updationtion in ltrx table failed\n");
*/
    }

}

void insertDataPtrx()
{
       PtrxTableApi *inData = (PtrxTableApi*)malloc(sizeof(PtrxTableApi));
       I_S32 errCode;
       I_U32 i;  
    	for(i=1;i<=5;i++)
	{
	    inData->ptrxId = (I_U32)i;
	    inData->ltrxId = i+10;
	    inData->oprState = (I_U32)233;
	    inData->mappingStatus = (I_U32)0;
	    inData->mapAllowed = (I_U8)15+i;
	    strcpy(inData->trxSwVersionId,"10");
	    strcpy(inData->trxHwVersionId,"11");	
	    inData->bandCapability = (I_U32)12;	
	    inData->pwrCapability = (I_U32)13;	
            inData->hoppingSupport = 20;
	    errCode = insertPtrxTable(inData);
	    if (errCode == CLIB_SUCCESS)
	    {
		fprintf(stdout, "Insertion successfull\n");
		
	    }
	    else
	    {
		fprintf(stdout, "Insertion failed: err = %s",clib_strerror(errCode));
	    }
	}
	free(inData);
}    
/*
void insertDataPtrxPreconfig()
{
       PhysicalTrxPreconfiguredTableApi *inData = (PhysicalTrxPreconfiguredTableApi*)malloc(sizeof(PhysicalTrxPreconfiguredTableApi));
       I_S32 errCode;
       I_U32 i;
       // I_U32 outCount;
      // I_U16 outSize; 
    	for(i=0;i<=2;i++)
	{
	    inData->ptrxId = (I_U32)i+1;
	    inData->tei = (I_U32)15+i;
	    inData->antennaId = (I_U32)5;
	    inData->adminState = (I_U32)0;
	    inData->e1Id = (I_U8)15;
	    inData->startE1Timeslot = (I_U32)((i*8)+1);	
	    inData->rackId = (I_U32)13;	
	    inData->slotId = (I_U32)13;	
	    errCode = insertPhysicalTrxPreconfiguredTable(inData);
	    if (errCode == CLIB_SUCCESS)
	    {
		fprintf(stdout, "Insertion successfull\n");
		
	    }
	    else
	    {
		fprintf(stdout, "Insertion failed: err = %s",clib_strerror(errCode));
	    }
	}
	free(inData);
        //errCode =  getallPhysicalTrxPreconfiguredTable(&outData , &outCount, &outSize);
}    
 
*/

I_Void insertDataCellTable()
{
    I_U32 counter; 
    I_S32 errCode;

    CellTableIndices cellIndices;
    CellTableApi cellInData;

    LaTableApi	laTableInData;

    /***********	For Cell Table	***************/
    for(counter = 0 ; counter < 1 ; counter++)
    {
        cellInData.cellId 	= (I_U32)counter+14; 
	cellInData.lac 		= (I_U32)counter+24;

        laTableInData.lac       = (I_U32)counter+24;

	cellInData.adminState 	= (I_U32)0; 
	cellInData.oprState	= (I_U32)0;
	cellInData.antennaId    =(I_U32)(5*counter)+5;  
	cellInData.bcchArfcn	= (I_U16)160; 
	cellInData.ccchConf     = (I_U8)10;
        cellInData.freqBandBcch	= (I_U32)4; 
	cellInData.bcc 		= (I_U32)7; 
	cellInData.bcchPwr      = (I_U32)10;
	//cellInData.txPwrMaxRed	= (I_U32)0; 
	cellInData.msTxPwrMax	= (I_U32)10; 
	cellInData.msTxPowerMaxCch = (I_U32)5; 
	cellInData.fnOffset	 = (I_U32)59; 
	cellInData.csStatus 	 = (I_U32)89; 
	cellInData.pageStatus 	 = (I_U32)99; 
	cellInData.psStatus	 = (I_U32)0; 
	cellInData.cellBarAccess = (I_U32)0; 
//	cellInData.cellBarredAinterf = (I_U32)0;
	cellInData.accessCtrlClass = (I_U16)409; 
	cellInData.bsAgBlksRes 	 = (I_U32)1; 
	cellInData.bsPaMfrms	 = (I_U32)609; 
	cellInData.cellReselectHysteresis = (I_U32)709; 
	cellInData.rxLevAccessMin  = (I_U32)809; 
	cellInData.powerOffset 	   = (I_U32)909; 
	cellInData.bcchChangeMark  = (I_U32)12; 
	cellInData.siChangeField   = (I_U32)3; 
	cellInData.antennaLocation = (I_U32)4; 
	cellInData.lobeAxis 	   = (I_U32)6; 
	cellInData.lobeWidth       = (I_U32)88; 
	cellInData.ulAntennaSystemGain = (I_U32)9; 
	cellInData.dLAntennaSystemGain = (I_U32)3; 
	//cellInData.msTxPowerMax	 = (I_U32)0; 
	cellInData.cbq 		 = (I_U32)1; 
	cellInData.cellReselectOffset = (I_U32)5; 
	cellInData.tempOffset	 = (I_U32)7; 
	cellInData.penalityTime	 = (I_U32)8; 

	cellIndices.cellId 	= (I_U32)14+counter; 
	cellIndices.lac 	= (I_U32)24+counter;
/*	errCode = deleteCellTable(&cellIndices);
	if (errCode != CLIB_SUCCESS)
		printf("Deletion in cell table failed\n");*/

	errCode = insertCellTable(&cellInData);
	if (errCode != CLIB_SUCCESS)
		printf("Insertion in cell table failed\n");
	errCode = insertLaTable(&laTableInData);
        if (errCode != CLIB_SUCCESS)
  		printf("Insertion in Lac table failed\n");

/*	errCode = updateCellTable(&cellInData);
	if (errCode != CLIB_SUCCESS)
		printf("Insertion in cell table failed\n");
*/
    }
}


I_Void insertDataChnGrp()
{
    I_S32 errCode;
    I_U32 counter;
    I_U16 *temp;
    I_U32 count;

    ChnGrpTableIndices chnGrpIndices;
    ChnGrpTableApi chnGrpInData;

/******************** ChnGrp Table ************************************/
   for(counter = 0 ; counter < 1 ; counter++)
   {
      memset(&chnGrpInData , 0 , sizeof(ChnGrpTableApi));  
      chnGrpInData.chnGrpId	= (I_U32) counter+20;
     // chnGrpInData.cellId	= (I_U32) 30;
     // chnGrpInData.lac		= (I_U32) 40;
if(counter == 0)
{
        chnGrpInData.cellId       = (I_U32) 14;
	chnGrpInData.lac          = (I_U32) 24;
        chnGrpInData.bcchCcchSdcch4     = (I_U32) 1;
        chnGrpInData.bcchCcch           = (I_U32) 0;
        chnGrpInData.sdcch8             = (I_U32) 1;
        chnGrpInData.tch                = (I_U32) 6;
        chnGrpInData.pdch               = (I_U32) 0;
	
	chnGrpIndices.cellId      = (I_U32) 14;
        chnGrpIndices.lac         = (I_U32) 24;
	chnGrpInData.validArfcns  = (I_U8)  3;
	chnGrpInData.arfcn1       = (I_U8)  10;
	chnGrpInData.arfcn2       = (I_U8)  20;
	chnGrpInData.arfcn3       = (I_U8)  30;
}
 if(counter == 1)
       {
	chnGrpInData.cellId       = (I_U32) 14;
	chnGrpInData.lac          = (I_U32) 24;
        chnGrpInData.bcchCcchSdcch4     = (I_U32) 1;
        chnGrpInData.bcchCcch           = (I_U32) 0;
        chnGrpInData.sdcch8             = (I_U32) 0;
        chnGrpInData.tch                = (I_U32) 0;
        chnGrpInData.pdch               = (I_U32) 7;

	chnGrpIndices.cellId      = (I_U32) 14;
        chnGrpIndices.lac         = (I_U32) 24;
	chnGrpInData.validArfcns  = (I_U8)  1;
	chnGrpInData.arfcn1       = (I_U8)  160;
       }
if(counter == 2)
       {
        chnGrpInData.cellId       = (I_U32) 15;
        chnGrpInData.lac          = (I_U32) 25;
        chnGrpInData.bcchCcchSdcch4     = (I_U32) 0;
        chnGrpInData.bcchCcch           = (I_U32) 1;
        chnGrpInData.sdcch8             = (I_U32) 0;
        chnGrpInData.tch                = (I_U32) 0;
        chnGrpInData.pdch               = (I_U32) 7;

        chnGrpIndices.cellId      = (I_U32) 15;
        chnGrpIndices.lac         = (I_U32) 25;
	chnGrpInData.validArfcns  = (I_U8)  4;
	chnGrpInData.arfcn1       = (I_U8)  70;
	chnGrpInData.arfcn2       = (I_U8)  80;
	chnGrpInData.arfcn3       = (I_U8)  90;
	chnGrpInData.arfcn4       = (I_U8)  100;
       }
if(counter == 3)
       {
        chnGrpInData.cellId       = (I_U32) 15;
        chnGrpInData.lac          = (I_U32) 25;
        chnGrpInData.bcchCcchSdcch4     = (I_U32) 0;
        chnGrpInData.bcchCcch           = (I_U32) 0;
        chnGrpInData.sdcch8             = (I_U32) 0;
        chnGrpInData.tch                = (I_U32) 6;
        chnGrpInData.pdch               = (I_U32) 2;

        chnGrpIndices.cellId      = (I_U32) 15;
        chnGrpIndices.lac         = (I_U32) 25;
	chnGrpInData.validArfcns  = (I_U8)  4;
	chnGrpInData.arfcn1       = (I_U8)  110;
	chnGrpInData.arfcn2       = (I_U8)  120;
	chnGrpInData.arfcn3       = (I_U8)  130;
	chnGrpInData.arfcn4      = (I_U8)  140;

       }
/*
      chnGrpInData.bcchCcchSdcch4	= (I_U32) 0;
      chnGrpInData.bcchCcch		= (I_U32) 0;
      chnGrpInData.sdcch8	= (I_U32) 0;
      chnGrpInData.tch		= (I_U32) 0;
      chnGrpInData.pdch		= (I_U32) 0;
*/
      chnGrpInData.hsn		= (I_U32) 0;
      chnGrpInData.maxTxPwr	= (I_U32) 10;
      chnGrpInData.chnGrpStaticOffset  = (I_U32)0;
      chnGrpInData.chnGrpDynamicOffset = (I_U32)0;
      chnGrpInData.tsc		= (I_U32) 0;
      chnGrpInData.loadFraction = (I_U32) 0;
      chnGrpInData.band         = (I_U32) 6;
     // chnGrpInData.validArfcns  = (I_U8)  rand()%19;
//      temp = &chnGrpInData.arfcn1;

      /* For Loop To Store Arfcns On the Basis Of ValidArfcns Counter */
  //    for(count = 0 ; (count < chnGrpInData.validArfcns) && (chnGrpInData.validArfcns >1) ; count++)
    //  { 
      //   *(temp+count) = (I_U16)rand()%17;;
     // }/* Ending For Loop */

      chnGrpIndices.chnGrpId	= (I_U32) counter+20;
     // chnGrpIndices.cellId	= (I_U32) 30;
     // chnGrpIndices.lac		= (I_U32) 40;      

     errCode = deleteChnGrpTable(&chnGrpIndices);
      if (errCode != CLIB_SUCCESS)
 	printf("Deletion in chnGrp table failed\n");

      errCode = insertChnGrpTable(&chnGrpInData);
      if (errCode != CLIB_SUCCESS)
 	printf("Insertion in chnGrp table failed\n");

      errCode = updateChnGrpTable(&chnGrpInData);
      if (errCode != CLIB_SUCCESS)
 	printf("Updationtion in chnGrp table failed\n");

  }

}

I_Void insertDataTimeSlot()
{
    I_S32 errCode;
    I_U32 counter;
    I_U32 i;

    TimeSlotTableIndices timeSlotIndices;
    TimeSlotTableApi timeSlotInData;

   /*  ******************* Timeslot Table *************************/
   timeSlotInData.e1Num      = (I_U32) 8;
   timeSlotInData.tsNum      = (I_U32) 9;
   timeSlotInData.adminState = (I_U32) 1;
   timeSlotInData.oprState   = (I_U32) 1;
   timeSlotInData.usageType  = (I_U32) SYS_TS_USAGE_CIC;
   timeSlotInData.usingEntity= (I_U32) 0x10001;
   errCode = insertTimeSlotTable(&timeSlotInData);

   if (errCode != CLIB_SUCCESS)
 	printf("Insertion in TimeSlot table failed\n");
/*
   for(counter = 0 ; counter <= 3 ; counter++)
   {
      if(counter%2 == 0)
             i=1;
      else
             i=0;
      timeSlotInData.e1Num      = (I_U32) counter+20;
      timeSlotInData.tsNum      = (I_U32) counter+30;
      timeSlotInData.adminState = (I_U32) counter%2;
      timeSlotInData.oprState   = (I_U32) !(counter%2);
      timeSlotInData.usageType  = (I_U32) 12+i;
      timeSlotInData.usingEntity= (I_U32) 34+i;

      timeSlotIndices.e1Num      = (I_U32) counter+20;
      timeSlotIndices.tsNum      = (I_U32) counter+30;*/
  /*    errCode = deleteTimeSlotTable(&timeSlotIndices);
      if (errCode != CLIB_SUCCESS)
 	printf("Deletion in TimeSlot table failed\n");
*/
/*
      errCode = insertTimeSlotTable(&timeSlotInData);
      if (errCode != CLIB_SUCCESS)
 	printf("Insertion in TimeSlot table failed\n");
*/
  /*    errCode = updateTimeSlotTable(&timeSlotInData);
      if (errCode != CLIB_SUCCESS)
 	printf("Updationtion in TimeSlot table failed\n");
*/
  // }

}

I_Void insertDataE1Table()
{
    I_S32 errCode;
    I_U32 counter;
    
    E1TableIndices e1Indices;
    E1TableApi e1InData;
    
   /*  ******************* E1Num Table *************************/
   for(counter = 0 ; counter <4 ; counter++)
   {
      e1InData.e1Num 	  = (I_U32) counter+1;
      e1InData.adminState = (I_U32) counter%2;
      e1InData.oprState   = (I_U32) !(counter%2);
      e1InData.usingEntity= (I_U32) 0;
      e1InData.usageType  = (I_U32) 8;

      e1Indices.e1Num 	  = (I_U32) counter+20;
  /*    errCode = deleteE1Table(&e1Indices);
      if (errCode != CLIB_SUCCESS)
 	printf("Deletion in E1 table failed\n");
*/

      errCode = insertE1Table(&e1InData);
      if (errCode != CLIB_SUCCESS)
 	printf("Insertion in E1 table failed\n");

  /*    errCode = updateE1Table(&e1InData);
      if (errCode != CLIB_SUCCESS)
 	printf("Updationtion in E1 table failed\n");
*/
   }

}

I_Void insertDataCsNeighbourCell()
{
    I_S32 errCode;
    I_U32 counter;

    CsNeighCellsTableIndices csNeighCellIndices;
    CsNeighCellsTableApi csNeighCellInData;
    
    
   /***********	For CsNeighbourCell Table	***************/
   for(counter = 0 ; counter <4  ; counter++)
   {	
      csNeighCellInData.cellId = (I_U32)14;
      csNeighCellInData.lac = (I_U32)24;
  if(counter > 2 )
        {
        csNeighCellInData.cellType = (I_U32)1;
        }
        else
        {
        csNeighCellInData.cellType = (I_U32)0;
        }

      //csNeighCellInData.cellType = (I_U32)counter%2;
      csNeighCellInData.neighborCellId = (I_U32)counter+15;
      csNeighCellInData.neighborLac = (I_U32)counter+25;
      csNeighCellInData.neighborMnc = (I_U32)33;
      csNeighCellInData.neighborMcc = (I_U32)43;
	if(counter > 2)
        {
       csNeighCellInData.relationType = (I_U32)2;
        }
        else
        {
        csNeighCellInData.relationType = (I_U32)1;
        }

      //csNeighCellInData.relationType = (I_U32)!(counter%2);

      csNeighCellIndices.cellId = (I_U32)14;
     csNeighCellIndices.lac = (I_U32)24;
        if(counter > 2 )
        {
        csNeighCellIndices.cellType = (I_U32)1;
        }
        else
        {
        csNeighCellIndices.cellType = (I_U32)0;
        }


     // csNeighCellIndices.cellType = (I_U32)counter%2;
      csNeighCellIndices.neighborCellId = (I_U32)counter+15;

  /*    errCode = deleteCsNeighCellsTable(&csNeighCellIndices);
      if (errCode != CLIB_SUCCESS)
         printf("Deletion in csNeighcell table failed\n");
*/

      errCode = insertCsNeighCellsTable(&csNeighCellInData);
      if (errCode != CLIB_SUCCESS)
         printf("Insertion in csNeighcell table failed\n");

  /*    errCode = updateCsNeighCellsTable(&csNeighCellInData);
      if (errCode != CLIB_SUCCESS)
     	 printf("Updationtion in csNeighcell table failed\n");
*/
   } 
}

    
I_Void insertPsNeighCell()
{
    I_S32 errCode;
    I_U32 counter;

    PsNeighCellsTableIndices psNeighCellIndices;
    PsNeighCellsTableApi psNeighCellInData;

     
   /***********	For PsNeighbourCell Table	***************/
   for(counter = 0 ; counter <= 4 ; counter++)
   {	
      psNeighCellInData.psCellId = (I_U32)14+counter;
      psNeighCellInData.lac = (I_U32)24+counter;
      psNeighCellInData.cellType = (I_U32)counter%2;
      psNeighCellInData.psNeighborCellId = (I_U32)counter+15;
      psNeighCellInData.psNeighborLac = (I_U32)counter+25;
      psNeighCellInData.psNeighborMnc = (I_U32)33;
      psNeighCellInData.psNeighborMcc = (I_U32)43;
      psNeighCellInData.relationType = (I_U32)!(counter%2);
       psNeighCellInData.psNeighborCellRac = (I_U32)6 +counter;	

      psNeighCellIndices.psCellId = (I_U32)12;
      psNeighCellIndices.lac = (I_U32)20; 
      
      psNeighCellIndices.cellType = (I_U32)counter%2;
      psNeighCellIndices.psNeighborCellId = (I_U32)counter+13;
      psNeighCellIndices.psNeighborLac = (I_U32)counter+23;

  /*    errCode = deletePsNeighCellsTable(&psNeighCellIndices);
      if (errCode != CLIB_SUCCESS)
         printf("Deletion in psNeighcell table failed\n");
*/

      errCode = insertPsNeighCellsTable(&psNeighCellInData);
      if (errCode != CLIB_SUCCESS)
         printf("Insertion in psNeighcell table failed\n");

  /*    errCode = updatePsNeighCellsTable(&psNeighCellInData);
      if (errCode != CLIB_SUCCESS)
     	 printf("Updationtion in psNeighcell table failed\n");
*/
   }	
}


I_Void insertDataSiPreconfig()
{
    I_S32 errCode;
    I_U32 counter;

    SiPreconfigTableIndices siPreconfigIndices;
    SiPreconfigTableApi siPreconfigInData;   

/***********	For SI Preconfig Table	***************/
		
    for(counter = 1 ; counter < 2 ; counter++)
    {
        siPreconfigInData.dummyIndex	= (I_U16)counter; 
	siPreconfigInData.ec	= (I_U32)counter; 
	siPreconfigInData.nchPosition 	= (I_U32)0; 
	siPreconfigInData.baIndicator = (I_U32)0; 
	siPreconfigInData.mscr	= (I_U32)1; 
	siPreconfigInData.cbq3	= (I_U32)0; 
	siPreconfigInData.pwrc	= (I_U32)1; 
	siPreconfigInData.dnInd	= (I_U32)0; 
	siPreconfigInData.neci	= (I_U32)0; 
	siPreconfigInData.acs = (I_U32)0; 
	siPreconfigInData.earlyClassmarkSendingControl	 = (I_U32)1; 
	siPreconfigInData.si13Position 	 = (I_U32)0; 
	siPreconfigInData.g3EarlyCmSendingRestriction = (I_U32)0; 
	siPreconfigInData.si2QuaterIndicator = (I_U32)0; 
	siPreconfigInData.iuIndicator = (I_U32)0; 
	siPreconfigInData.breakIndicator = (I_U32)0; 
	siPreconfigInData.pchAndNchInfo	 = (I_U32)0; 
	siPreconfigInData.vbsVgcsOptions = (I_U32)0; 
	siPreconfigInData.dtmSupport = (I_U32)0; 
	siPreconfigInData.maxLapdm  = (I_U32)5; 
	siPreconfigInData.gprsMsTxpwrMaxCch   = (I_U32)0; 
	siPreconfigInData.sgsnRelNum  = (I_U32)1; 

	siPreconfigIndices.dummyIndex 	= (I_U16)counter; 
/*	errCode = deleteSiPreconfigTable(&siPreconfigIndices);
	if (errCode != CLIB_SUCCESS)
		printf("Deletion in SI Preconfig table failed\n");
*/

	errCode = insertSiPreconfigTable(&siPreconfigInData);
	if (errCode != CLIB_SUCCESS)
		printf("Insertion in SI Preconfig failed\n");

/*	errCode = updateSiPreconfigTable(&siPreconfigInData);
	if (errCode != CLIB_SUCCESS)
		printf("Insertion in SI Preconfig table failed\n");
*/

    }
}

I_Void insertDataBssPsPreConfig()
{
    I_S32 errCode;
    I_U32 counter;

    BssPsPreConfigTableIndices bssPsPreConfigIndices;
    BssPsPreConfigTableApi bssPsPreConfigInData;

    /***********	For Bss Ps Preconfig Table	***************/
		
    for(counter = 1 ; counter < 2 ; counter++)
    {
        bssPsPreConfigInData.dummyIndex      	= (I_U16)counter; 
	bssPsPreConfigInData.pageMode   	= (I_U8)1; 
	bssPsPreConfigInData.nmo        	= (I_U8)2; 
	bssPsPreConfigInData.t3168      	= (I_U32)5; 
	bssPsPreConfigInData.t3192      	= (I_U32)5; 
	bssPsPreConfigInData.drxTimerMax        = (I_U8)3; 
	bssPsPreConfigInData.accessBurstType    = (I_U8)1; 
	bssPsPreConfigInData.controlAckType     = (I_U8)1; 
	bssPsPreConfigInData.bsCvMax    	= (I_U32)6; 
	bssPsPreConfigInData.psiStatusInd       = (I_U8)1; 
	bssPsPreConfigInData.extensionBits      = (I_U32)2; 
	bssPsPreConfigInData.measurementOrder   = (I_U8)1; 
	bssPsPreConfigInData.bssPagingCoordination  = (I_U32)0; 
	bssPsPreConfigInData.spgcCcchSup        = (I_U8)1; 
	bssPsPreConfigInData.t3169              = (I_U8)5; 
	bssPsPreConfigInData.nwExtUtbf          = (I_U8)0; 
	bssPsPreConfigInData.pfcFeatureMode     = (I_U8)1; 
	bssPsPreConfigInData.ccnActive	        = (I_U8)1; 
	bssPsPreConfigInData.networkControlOrder = (I_U8)2; 

	bssPsPreConfigIndices.dummyIndex 	= (I_U16)counter; 
	
  /*      errCode = deleteBssPsPreConfigTable(&bssPsPreConfigIndices);
	if (errCode != CLIB_SUCCESS)
		printf("Deletion in BSS PS Preconfig table failed\n");
*/

	errCode = insertBssPsPreConfigTable(&bssPsPreConfigInData);
	if (errCode != CLIB_SUCCESS)
		printf("Insertion in BSS PS Preconfig table failed\n");

/*	errCode = updateBssPsPreConfigTable(&bssPsPreConfigInData);
	if (errCode != CLIB_SUCCESS)
		printf("Insertion in BSS PS Preconfig table failed\n");
*/

    }
}

I_Void insertDataPsCell()
{
    I_S32 errCode;
    I_U32 counter;

    PsCellTableIndices psCellIndices;
    PsCellTableApi psCellInData;

  /***********	For PS Cell Table	***************/
	
    memset(&psCellInData,0,sizeof(PsCellTableApi));	
    for(counter = 0 ; counter <= 3 ; counter++)
    {
        psCellInData.cellId 	        = (I_U32)counter+14; 
	psCellInData.lac 		= (I_U32)counter+24; 
	psCellInData.pbcchPres  	= (I_U32)1; 
	psCellInData.rac        	= (I_U32)6; 
	psCellInData.raColour   	= (I_U32)5; 
	psCellInData.alpha      	= (I_U8)1; 
	psCellInData.tAvgW 		= (I_U8)2; 
	psCellInData.tAvgT       	= (I_U8)3; 
	psCellInData.pb         	= (I_U8)7; 
	psCellInData.pcMeasChan         = (I_U8)1; 
	psCellInData.panInc	        = (I_U8)1; 
	psCellInData.panDec 	        = (I_U8)1; 
	psCellInData.panMax 	        = (I_U8)2; 
	psCellInData.bepPeriod	        = (I_U8)1; 
	psCellInData.priorityAccessThr  = (I_U8)6; 
	psCellInData.nAvgI              = (I_U8)2; 
	psCellInData.psi1RepeatPeriod   = (I_U8)2; 
//	psCellInData.si13ChangeMark     = (I_U8)1; 

	psCellIndices.cellId 	= (I_U32)14+counter; 
	psCellIndices.lac 	= (I_U32)24+counter;
/*	errCode = deletePsCellTable(&psCellIndices);
	if (errCode != CLIB_SUCCESS)
		printf("Deletion in PS cell table failed\n");
*/

	errCode = insertPsCellTable(&psCellInData);
	if (errCode != CLIB_SUCCESS)
		printf("Insertion in PS cell table failed\n");

/*	errCode = updatePsCellTable(&psCellInData);
	if (errCode != CLIB_SUCCESS)
		printf("Insertion in PS cell table failed\n");
*/

   }
}
I_Void insertDataCsExternalCell()
{
    I_S32 errCode;
    I_U32 counter;

    CsExternalCellTableIndices csExtCellIndices;
    CsExternalCellTableApi csExtCellInData;

/***********	For CsExternalCell Table	***************/

    for(counter = 0 ; counter <= 2 ; counter++)
    {
	csExtCellInData.csExtCellId = (I_U32)counter+18;
	csExtCellInData.lac = (I_U32)counter+28;
	csExtCellInData.mnc = (I_U32)33;
	csExtCellInData.mcc = (I_U32)43;
	csExtCellInData.bcc = (I_U32)0;
	csExtCellInData.ncc = (I_U32)0;
	csExtCellInData.bcchArfcn = (I_U32)counter+23;
	csExtCellInData.freqBandBcch = (I_U32)1;

	csExtCellIndices.csExtCellId = (I_U32)counter+18;
	csExtCellIndices.lac = (I_U32)counter+28;
	csExtCellIndices.mnc = (I_U32)33;
	csExtCellIndices.mcc = (I_U32)43;

/*	errCode = deleteCsExternalCellTable(&csExtCellIndices);
	if (errCode != CLIB_SUCCESS)
		printf("Deletionon in csExtcell table failed\n");
*/

	errCode = insertCsExternalCellTable(&csExtCellInData);
	if (errCode != CLIB_SUCCESS)
		printf("Insertion in csExtcell table failed\n");

/*	errCode = updateCsExternalCellTable(&csExtCellInData);
	if (errCode != CLIB_SUCCESS)
		printf("Updation in csExtcell table failed\n");
*/

    }
}
I_Void insertDataRadioTimeslot()
{
    I_S32 errCode;
    I_U32 counter;
    
      
    RadioTimeslotTableIndices radioTimeslotIndices;
    RadioTimeslotTableApi radioTimeslotInData;

  
/*  ******************* Radio Time Slot Table *************************/
    for(counter = 0 ; counter <= 5 ; counter++)
    {
       radioTimeslotInData.ptrxId = (I_U32)counter+12;
       radioTimeslotInData.radioTs= (I_U32)counter+20;
       radioTimeslotInData.channelCombination= (I_U32)33;
       radioTimeslotInData.tsc = (I_U32)counter+30;
       radioTimeslotInData.hsn = (I_U32)counter+40;
       radioTimeslotInData.maio= (I_U32)counter+50;
       radioTimeslotInData.validArfcns=(I_U8)1;
       radioTimeslotInData.arfcn1 = (I_U16)3;
       radioTimeslotInData.arfcn2 = (I_U16)0;
       radioTimeslotInData.arfcn3 = (I_U16)0;
       radioTimeslotInData.arfcn4 = (I_U16)0;
       radioTimeslotInData.arfcn5 = (I_U16)0;
       radioTimeslotInData.arfcn6 = (I_U16)0;
       radioTimeslotInData.arfcn7 = (I_U16)0;
       radioTimeslotInData.arfcn8 = (I_U16)0;
       radioTimeslotInData.arfcn9 = (I_U16)0;
       radioTimeslotInData.arfcn10= (I_U16)0;
       radioTimeslotInData.arfcn11= (I_U16)0;
       radioTimeslotInData.arfcn12= (I_U16)0;
       radioTimeslotInData.arfcn13= (I_U16)0;
       radioTimeslotInData.arfcn14= (I_U16)0;
       radioTimeslotInData.arfcn15= (I_U16)0;
       radioTimeslotInData.arfcn16= (I_U16)0;
       radioTimeslotInData.arfcn17= (I_U16)0;
       radioTimeslotInData.arfcn18= (I_U16)0;
       radioTimeslotInData.abisE1Id=(I_U32)0;
       radioTimeslotInData.abisE1Tst=(I_U32)0;

      radioTimeslotIndices.ptrxId	= (I_U32) counter+12;
      radioTimeslotIndices.radioTs	= (I_U32) counter+20;

  /*    errCode = deleteRadioTimeslotTable(&radioTimeslotIndices);
      if (errCode != CLIB_SUCCESS)
 	printf("Deletion in radioTimeslot table failed\n");
*/

      errCode = insertRadioTimeslotTable(&radioTimeslotInData);
      if (errCode != CLIB_SUCCESS)
 	printf("Insertion in radioTimeslot table failed\n");

  /*    errCode = updateRadioTimeslotTable(&radioTimeslotInData);
      if (errCode != CLIB_SUCCESS)
 	printf("Updationtion in radioTimeslot table failed\n");
*/
   }

}

I_Void insertDataAllocationAllowedTable()
{
    I_S32 errCode;
    I_U32 index;
    AllocationAllowedTableApi alloactionIpData;
    
    for (index =0; index < 3; index++)
    {
        alloactionIpData.lac = 24;
        alloactionIpData.cellId = 14;
	if(index == 0)
	{
          alloactionIpData.channelName = PDCH_PBCCH;
	  alloactionIpData.allocStatus = 1;
	}
	if(index == 1)
	{
          alloactionIpData.channelName = PDCH_PDTCH;
	  alloactionIpData.allocStatus = 1;
	}

	if(index == 2)
	{
          alloactionIpData.channelName = TCH;
	  alloactionIpData.allocStatus = 1;
	}

        //alloactionIpData.allocStatus = ALLOCATION_ALLOWED;
        errCode = insertAllocationAllowedTable(&alloactionIpData);
    }

    //printf(" i am in allocation allowed errCode =%d",errCode);
}

I_Void insertDataObjectStateTable()
{
    I_S32 errCode;
    I_U32 random;
    I_U32 index;
    ObjectStateTableApi *objectStateIpData = (ObjectStateTableApi*)malloc(sizeof(ObjectStateTableApi));
    
    for (index =0; index < 3; index++)
    {
        random = rand()%50;
        printf("Random no. generated %d", random);

        objectStateIpData->objectType = 20+index;
        objectStateIpData->objectId = 21+index;
        objectStateIpData->ongoingProcedure = random;
        objectStateIpData->localState = 21;
        objectStateIpData->remoteState = 24;
        errCode = insertObjectStateTable(objectStateIpData);
    }
    free(objectStateIpData);
}

I_Void insertDataChannelUsageTable()
{
    I_S32 errCode;
    I_U32 index=0;
    I_U32 i=0;
    ChannelUsageTableApi *channelUsageIpData = (ChannelUsageTableApi*)malloc(sizeof(ChannelUsageTableApi));

        channelUsageIpData->channelId = 18;
        channelUsageIpData->channelName = 16;
        channelUsageIpData->lac = 0;
        channelUsageIpData->cellId = 1;
        channelUsageIpData->userType = 41;
        channelUsageIpData->userId = 61;
        channelUsageIpData->cic = 10;
        errCode = insertChannelUsageTable(channelUsageIpData);

    for (index =0; index < 6; index++)
    {
        if(index%2==0)
          i=0;
        else
          i=1;

        channelUsageIpData->channelId = 17+index;
        channelUsageIpData->channelName = 16+index;
        channelUsageIpData->lac = 18+index;
        channelUsageIpData->cellId = 19+index;
        channelUsageIpData->userType = 40+i;
        channelUsageIpData->userId = 6+i;
        channelUsageIpData->cic = 1+index;
        errCode = insertChannelUsageTable(channelUsageIpData);
    }
    free(channelUsageIpData);
}


I_Void insertDataBssCsPreConfTable()
{
    BssCsPreConfigTableApi *bssCsInData =(BssCsPreConfigTableApi*)malloc(sizeof(BssCsPreConfigTableApi));
    I_S32 errCode = 0;

    bssCsInData->dummyIndex = (I_U16)1;
    bssCsInData->tWaitLockComplete = 360;
    bssCsInData->tWaitUnlockComplete = 361;
    bssCsInData->tResetAckDelay = 362;
    bssCsInData->tResetCktAckDelay = 363;
    bssCsInData->t3101 = (I_U32)23;
    bssCsInData->t3107= (I_U32)24;
    bssCsInData->t3109 = (I_U32)25;
    bssCsInData->t3111 = (I_U32)1800;
    bssCsInData->t3122 = (I_U32)26;
    bssCsInData->tWaitClearCmd = (I_U8)255;
    bssCsInData->tWatchdogEstablish = (I_U16)65535;
    bssCsInData->tWatchdogRelease = (I_U16)20;
    bssCsInData->tWaitEstablishCnf = (I_U16)21;
    bssCsInData->tWaitChanActivation = (I_U16)28;
    bssCsInData->tRfChanRel = (I_U16)33;
    bssCsInData->clearReqRetryCount = (I_U16)13;
    bssCsInData->respSuperTimer = (I_U32)33;
    bssCsInData->maxNoRetransmission= (I_U32)3434523;
    bssCsInData->noOfRemoteTranscoderFailure = (I_U8)93;
    bssCsInData->cipheringAlgorithm = (I_U8)2;
    bssCsInData->loadSegTimer = (I_U32)223;
    bssCsInData->windowSize = (I_U32)213;
    bssCsInData->imageSegSize = (I_U32)2113;

    errCode = insertBssCsPreConfigTable(bssCsInData);
    if (errCode != CLIB_SUCCESS)
    {
       fprintf(stdout, " insertion failed: err = %s", clib_strerror(errCode));
    }
    free(bssCsInData);

}

I_Void insertDataBssTable()
{
    I_S32 errCode = 0;
    I_U32 i = 0;
    BssTableApi *bssTableIpData = (BssTableApi*)malloc(sizeof(BssTableApi));
    
    for ( i=0; i<=3; i++)
    {
        bssTableIpData->bscId = (I_U32)i+1;
        bssTableIpData->adminState = (I_U32)1;
        bssTableIpData->bssReset = (I_U32)12;
        bssTableIpData->callReestablishmentInd = (I_U32)23;
        bssTableIpData->attInd = (I_U32)435;
        bssTableIpData->t3212 = (I_U32)15;
        bssTableIpData->mcc = (I_U32) 43;
        bssTableIpData->mnc = (I_U32) 33;
        bssTableIpData->ncc = (I_U32)135;
        bssTableIpData->dtxDnLinkInd = (I_U32)111+i;
        bssTableIpData->dtxUpLinkInd = (I_U32)1223+i;
        bssTableIpData->maxRetrans = (I_U32)1;
        bssTableIpData->rxIncrStepSize = (I_U32)2;
        bssTableIpData->minChannelGap = (I_U32)3;
        bssTableIpData->gprsEnabled = (I_U32)0;
        errCode = insertBssTable(bssTableIpData);
        if (errCode != CLIB_SUCCESS)
        {
           fprintf(stdout, " insertion failed: err = %s", clib_strerror(errCode));
        }
    }
    free(bssTableIpData);
}

I_Void insertDataPcuTable()
{
   I_S32 errCode;

   PcuTableApi pcuInData;
   PcuTableIndices pcuIndex;
   
   pcuInData.dummyIndex		= (I_U16)1;
   //pcuInData.rrbpFlag		= (I_U8)0;
   pcuInData.tcVal		= (I_U32)4;
   //pcuInData.tFlowCtrlAck	= (I_U32)1;
   //pcuInData.pcuTimerRetries	= (I_U32)3;
   pcuInData.numContiguousPdch	= (I_U32)2;
   pcuInData.defaultChanCoding	= (I_U32)0;
   pcuInData.tlliBlkCoding	= (I_U32)0;
   pcuInData.maxUlAllocLength	= (I_U32)0;
   pcuInData.onePhSize		= (I_U8)2;
   pcuInData.globPwrCtrlFlag	= (I_U32)1;

   pcuIndex.dummyIndex = (I_U16)pcuInData.dummyIndex;

   errCode = deletePcuTable(&pcuIndex);
   if(errCode != CLIB_SUCCESS)
   {
      fprintf(stdout, " Deletion failed: err = %s", clib_strerror(errCode));
     // return;
   }
   
   errCode = insertPcuTable(&pcuInData);
   if(errCode != CLIB_SUCCESS)
   {
      fprintf(stdout, " Insertion failed: err = %s", clib_strerror(errCode));
      return;
   }
  
   errCode = updatePcuTable(&pcuInData);
   if(errCode != CLIB_SUCCESS)
   {
      fprintf(stdout, " Updation failed: err = %s", clib_strerror(errCode));
      return;
   }
}

I_Void insertDataChannelParamTable()
{
   I_S32 errCode;
   I_U32 index;
   for( index=0; index<=2;index++)
   {
       ChannelParamsTableApi channelParamIpData;
       channelParamIpData.channelId=1+index;
       channelParamIpData.trxTei=2+index;
       channelParamIpData.channelName=3+index;
       channelParamIpData.timeSlotNum=4+index;
       channelParamIpData.chanlType=5+index;
       channelParamIpData.subChanNum=6;
       channelParamIpData.tsc=7;
       channelParamIpData.lac=8;
       channelParamIpData.cellId=9;
       channelParamIpData.isHsnPresent=10;
       channelParamIpData.hsn=11;
       channelParamIpData.isMaioPresent=1;
       channelParamIpData.maio=13+index;
       channelParamIpData.band=14;
       channelParamIpData.noOfArfcns=15;
       channelParamIpData.arfcn1=3;
       channelParamIpData.arfcn2=1;
       channelParamIpData.arfcn3=4;
       channelParamIpData.abisE1=19;
       channelParamIpData.abisTimeSlot=20;
       errCode = insertChannelParamsTable(&channelParamIpData);
    }
}
   
I_Void insertDataLapdTimerTable()
{
    I_S32 errCode = 0;
    LapdTimerTableApi *lapdIpData = (LapdTimerTableApi*)malloc(sizeof(LapdTimerTableApi));
    lapdIpData->lapdTimerT200 = 34;
    lapdIpData->lapdTimerT201 = 23;
    lapdIpData->lapdTimerT202 = 4;
    lapdIpData->lapdTimerT203 = 7;
    lapdIpData->lapdTimerDUMMYIndex = 8;
    errCode = insertLapdTimerTable( lapdIpData );
        
    if (errCode != CLIB_SUCCESS)
    {
        fprintf(stdout, " insertion failed: err = %s", clib_strerror(errCode));
    }
    free(lapdIpData);
}

I_Void insertDataPpResourceTable()
{
    I_S32 errCode = 0;
    I_U32 index;
    PpResourcePreconfiguredTableApi *ppResourceIpData = (PpResourcePreconfiguredTableApi*)malloc(sizeof(PpResourcePreconfiguredTableApi));
   for( index=0; index<1; index++)
   {
      ppResourceIpData->mccTs = 10; 
      ppResourceIpData->type = SYS_TS_USAGE_PDCH;
      ppResourceIpData->e1 = 16;
      ppResourceIpData->ts = 9;
      errCode = insertPpResourcePreconfiguredTable( ppResourceIpData );
   }    
   if (errCode != CLIB_SUCCESS)
   {
      fprintf(stdout, " insertion failed: err = %s", clib_strerror(errCode));
   }
   free(ppResourceIpData);
}

I_Void insertDataTrauChannelUsageTable()
{
    I_S32 errCode = 0;
    I_U32 index = 0;
    TrauChannelUsageTableApi *trauChannelOpData = (TrauChannelUsageTableApi*)malloc(sizeof(TrauChannelUsageTableApi));
   for( index=0; index<=2;index++)
   {
      trauChannelOpData->trauChNo = index+34; 
      //trauChannelOpData->isAllocated = index%2;
      errCode = insertTrauChannelUsageTable( trauChannelOpData );
   }     
   if (errCode != CLIB_SUCCESS)
   {
      fprintf(stdout, " insertion failed: err = %s", clib_strerror(errCode));
   }
   free(trauChannelOpData);
}

I_Void insertDataMccTsUsageTable()
{
    I_S32 errCode = 0;
    I_U32 index; 
    MccTsUsageTableApi *mccTsUsageOpData = (MccTsUsageTableApi*)malloc(sizeof(MccTsUsageTableApi));
   for( index=0; index<=2;index++)
   {
      mccTsUsageOpData->mccTs = index+34; 
      mccTsUsageOpData->isAllocated = index%2;
      errCode = insertMccTsUsageTable( mccTsUsageOpData );
   }     
   if (errCode != CLIB_SUCCESS)
   {
      fprintf(stdout, " insertion failed: err = %s", clib_strerror(errCode));
   }
   free(mccTsUsageOpData);
}
/*
I_Void insertDataRaTable()
{
    I_U32    counter;
    RaTableApi raTableApi;
    for (counter = 0; counter < 4; counter++)
	{
	raTableApi.lac = counter+24;
        raTableApi.rac = counter+6;
	
        if ( insertRaTable(&raTableApi) != CLIB_SUCCESS )
          {
                printf("Insert RATable Fail \n");
          }
	}
}
*/
I_Void insertDataArfcnTable()
{
	I_U32    counter;
        ArfcnListTableIndices arfcnListTableIndices;
        ArfcnListTableApi arfcnListTableApi;

	for(counter = 0; counter < 17; counter++)
	{
           arfcnListTableApi.band = 90;
           arfcnListTableApi.arfcn = (counter*10)+10;
           if ( insertArfcnListTable(&arfcnListTableApi) != CLIB_SUCCESS )
            {
                  printf("Insert Arfcn Table Fail \n");
            }

	}
}

I_Void insertDataAInterfaceTable()
{
   I_S32 errCode = 0;
   AInterfaceTableApi aInterfaceInData;
   
   aInterfaceInData.dummyIndex = 1;
   aInterfaceInData.oprState   = ENABLED;

   errCode = insertAInterfaceTable(&aInterfaceInData);
   if (errCode != CLIB_SUCCESS)
   {
      fprintf(stdout, " insertion failed: err = %s", clib_strerror(errCode));
   }
}

I_Void testDBNailup() 
{
   I_S32 errCode = 0;
   NailupTableApi  newData;

   newData.firste1Id = 52;
   newData.firste1Timeslot = 53;
   newData.seconde1Id = 54;
   newData.seconde1Timeslot = 55;

   errCode=insertNailupTable(&newData);

   if(errCode != CLIB_SUCCESS)
   {
      fprintf(stdout,"insertNailupTable Failed err = %s",clib_strerror(errCode));
   }
}


I_Void testDBDspTrauResourcePreconfigured() 
{
   I_S32 errCode = 0;
   DspTrauResourcePreconfiguredTableApi newData;

   newData.trauChannel = 1;
   newData.trauAbisE1 = 2;
   newData.trauAbisTs = 3;
   newData.trauAifE1 = 4;
   newData.trauAifTs = 5;

   errCode=insertDspTrauResourcePreconfiguredTable(&newData);

   if(errCode != CLIB_SUCCESS)
   {
      fprintf(stdout,"insertDspTrauResourcePreconfiguredTable Failed err = %s",clib_strerror(errCode));
   }
}



I_Void testDBE1StreamMap() 
{
   I_S32 errCode = 0;
   E1StreamMapTableApi newData;

  I_U32 i; 
for(i=0;i<3;i++)
{
   newData.e1Num =15+i;
   newData.e1Ts = (i*8)+1;
   newData.strmNum = 15;
   newData.strmTs = 15;

   errCode=insertE1StreamMapTable(&newData);

   if(errCode != CLIB_SUCCESS)
   {
      fprintf(stdout,"insertE1StreamMapTable Failed err = %s",clib_strerror(errCode));
   }
}
}


/***************************************************************************/


