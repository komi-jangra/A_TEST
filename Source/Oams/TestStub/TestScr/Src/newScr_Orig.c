#include<oamscfg_includes.h>


I_U8 getPingableIp (char *serverip)
{
		char pingstr[200];
		//char ip[25];
		int len;
		char *tmp;
		I_U8 flag = 0; 
      char *s = (char *)malloc ( sizeof ( char ) * 200 );
		//fprintf(stderr,"serverip is %s\n",serverip);

		

			bzero(pingstr,200);
			bzero(s,200);
    	sprintf(pingstr,"ping %s -c 1 -W 1 | grep \"0 received\" ",serverip);
    	FILE *cmd1 = popen ( pingstr, "r" );

    	while ( !feof(cmd1) )
    	{
            fgets ( s, sizeof ( char )*200, cmd1 );
            if ( strstr( s, "received" ) != 0 )
						{
						 flag = 0;
						}
						else
						{
						 //LOG_PRINT(INFO,"ping is  successful, go to next entry");
             flag = 1;
						}
            break;
    	}
    	pclose ( cmd1 );


    return flag;

}/* getPingableIp */


main()
{
I_S32           result = ZERO;
I_U8 sts;
I_U16 noOfUnLockedCells=0, noOfLockedCells=0;
result = dbConnect();
      if ( result != DBLIB_SUCCESS )
      {
         //LOG_PRINT(CRITICAL,"CELLHandler: Unable to Register itself with DBServer:Exiting");
         fprintf(stderr,"Unable to register");
         return;
      }

  I_S32         outRows=0,tmpCnt,tmpCnt1,tmpCnt2,outRows2;
  I_S16         outSize,outSize2;
  I_S32         dbSts=DBLIB_SUCCESS,i;
  I_Void        *outData,*tmpData1,*tmpData2,*tmpData3,*tmpData4,*tmpData5,*tmpData6,*tmpData7,*tmpData8,*tmpData9,*tmpData10;
  BicTableApi *tmpData;
  I_CHAR        tmpStr[20];
  I_U32         tmpAntId=0,tmpTrxId1=0,tmpTrxId2=0;
  PtrxTableIndices       tmpPtrxIdKey;
  TrxTableIndices       tmpTrxIdKey;
  CellNonPerTableIndices tmpCellNonPerTableKey;
  BicTableApi * tmpBicTable;
  CellPerTableApi *tmpCellTable;
  TrxTableApi *tmpTrxTable;
  struct        in_addr in; 
  BicStatusTableIndices bicStatus;
	AInterfaceTableApi *tmpAifTable;
	LinkTableApi *tmpLinkTable;
	LinkStatusTableIndices inLinkSts;
	CellPerTableApi *tmpCellPerTable;
	GbIfStatusTableApi *tmpGbIfTable;
	 	time_t now;
 	 	time(&now);
tmpCnt1=0;
 fprintf(stderr,"------------------------------------------------------------------------------------------------------------\n");
 				fprintf(stderr,"%69s",ctime(&now));
				dbSts = getallAInterfaceTable((AInterfaceTableApi **)&tmpData6, &outRows, &outSize);
        if(dbSts == DBLIB_SUCCESS)
        {
					tmpAifTable=NULL;
					tmpAifTable = (AInterfaceTableApi *)((I_U8*)tmpData6 + (tmpCnt1 *outSize));
					if(tmpAifTable->oprState == 1)
					fprintf(stderr,"%18s","AIF-STATUS: UP");
					else
					fprintf(stderr,"%18s","AIF-STATUS: DOWN");
					free(tmpData6);
				}
        else
					fprintf(stderr,"%18s","AIF-STATUS: DB-Fail");

				dbSts = getallLinkTable((LinkTableApi **)&tmpData7, &outRows, &outSize);
        if(dbSts == DBLIB_SUCCESS)
        {
					for(tmpCnt1=0; tmpCnt1<outRows; ++tmpCnt1)
      		{
					tmpLinkTable=NULL;
					tmpLinkTable = (LinkTableApi *)((I_U8*)tmpData7 + (tmpCnt1 *outSize));
				
					inLinkSts.linksetID = tmpLinkTable->linksetID;
					inLinkSts.linkId = tmpLinkTable->linkId;
				  dbSts = getLinkStatusTable(&(inLinkSts), (LinkStatusTableApi **)&tmpData10);	
					if(dbSts == CLIB_SUCCESS)
					{
					if(tmpLinkTable->cardNum == 3)
					{
				   if(((((LinkStatusTableApi *) tmpData10)[0]).oprState == 1) && (tmpLinkTable->adminState == 1)) 
						fprintf(stderr,"%23s","LINK3-AS: UENB");
   				else if(((((LinkStatusTableApi *) tmpData10)[0]).oprState == 1) && (tmpLinkTable->adminState == 0))
						fprintf(stderr,"%23s","LINK3-AS: LENB");
   				else if(((((LinkStatusTableApi *) tmpData10)[0]).oprState == 0) && (tmpLinkTable->adminState == 0)) 
						fprintf(stderr,"%23s","LINK3-AS: LDIS");
          else
          fprintf(stderr,"%23s","LINK3-AS: UDIS");

					}
					else
					{
   					if(((((LinkStatusTableApi *) tmpData10)[0]).oprState == 1) && (tmpLinkTable->adminState == 1))
						fprintf(stderr,"%28s","LINK4-AS: UENB");
   					else if(((((LinkStatusTableApi *) tmpData10)[0]).oprState == 1) && (tmpLinkTable->adminState == 0))
						fprintf(stderr,"%28s","LINK4-AS: LENB");
   					else if(((((LinkStatusTableApi *) tmpData10)[0]).oprState == 0) && (tmpLinkTable->adminState == 0))
						fprintf(stderr,"%28s","LINK4-AS: LDIS");
          else
          fprintf(stderr,"%28s","LINK4-AS: UDIS");
					}
					free(tmpData10);
				 }
				 	}
					free(tmpData7);
				}
        else
					fprintf(stderr,"%28s","LINK-AS: DB-Fail");

				dbSts = getallGbIfStatusTable((GbIfStatusTableApi **)&tmpData8, &outRows, &outSize);
        if(dbSts == DBLIB_SUCCESS)
        {
          tmpCnt1=0;
					tmpGbIfTable=NULL;
					tmpGbIfTable = (GbIfStatusTableApi *)((I_U8*)tmpData8 + (tmpCnt1 *outSize));
					if(tmpGbIfTable->oprState == 1)
					fprintf(stderr,"%33s\n","GBIF-STATUS: UP");
					else
					fprintf(stderr,"%33s\n","GBIF-STATUS: DOWN");
					free(tmpData8);
				}
        else
					fprintf(stderr,"%33s\n","GBIF-STATUS: DB-Fail");

/*
				dbSts = getallCellPerTable((CellPerTableApi **)&tmpData9, &outRows, &outSize);
        if(dbSts == DBLIB_SUCCESS)
        {
          fprintf(stderr,"%16s","Total Cells: "); 
          fprintf(stderr,"%d",outRows); 
					
					for(tmpCnt1=0; tmpCnt1<outRows; ++tmpCnt1)
      		{
					tmpCellPerTable=NULL;
					tmpCellPerTable = (CellPerTableApi *)((I_U8*)tmpData9 + (tmpCnt1 *outSize));
					
					if(tmpCellPerTable->adminState == 1)
					{
						noOfUnLockedCells++;
					}
					else
					{

						noOfLockedCells++;
					}
				 	}
          fprintf(stderr,"%23s","Locked Cells: "); 
          fprintf(stderr,"%d",noOfLockedCells); 
          fprintf(stderr,"%29s","UnLocked Cells: "); 
          fprintf(stderr,"%d\n",noOfUnLockedCells); 
					free(tmpData9);
				}
*/
        fprintf(stderr,"%19s%9s%6s%6s%16s%7s%s%7s%8s%7s%8s%s%8s%s\n","BtsName","BtsId","AbisS","BtsS","IpAddr","CellId","(Band)","AntId","BArfcn","CellS","BTrxS",":PId","NBTrxS",":Pid");
 fprintf(stderr,"------------------------------------------------------------------------------------------------------------\n");
  
       
    dbSts = getallBicTable((BicTableApi **)&tmpData, &outRows, &outSize);

    if(dbSts == DBLIB_SUCCESS && outRows > 0)
    {

      for(tmpCnt1=0; tmpCnt1<outRows; ++tmpCnt1)
      {
        tmpBicTable=NULL;
        tmpBicTable = (BicTableApi *)((I_U8*)tmpData + (tmpCnt1 *outSize));
        //fprintf(stderr,"%s",(((BicTableApi *) tmpData)[tmpCnt1]).btsName); 
        //fprintf(stderr," \t%d",(((BicTableApi *) tmpData)[tmpCnt1]).bicId); 
        //fprintf(stderr,"%8d",time(NULL));
        fprintf(stderr,"%19s",tmpBicTable->btsName); 
        fprintf(stderr,"%9d",tmpBicTable->bicId); 
        dbSts = getBicStatusTable(&(tmpBicTable->bicId), (BicStatusTableApi **)&tmpData1);
        if(dbSts == DBLIB_SUCCESS)
        {
          //fprintf(stderr," \t%d",(((BicStatusTableApi *) tmpData1)[0]).btsIpLinkStatus); 
          //fprintf(stderr," \t%d",(((BicStatusTableApi *) tmpData1)[0]).btsIpLinkStatus); 
          if((((BicStatusTableApi *) tmpData1)[0]).btsIpLinkStatus == 1) /*1=UP 0=DOWN*/
          fprintf(stderr,"%6s","UP"); 
          else
          fprintf(stderr,"%6s","DWN"); 
         
            //scrBscConfigPtr[tmpCnt1].oprState = 0x01;

          if(((((BicStatusTableApi *) tmpData1)[0]).oprState == 1) && (tmpBicTable->adminState == 1)) /*1=ENABLED 0=DISABLED*/
          fprintf(stderr,"%6s","UENB"); 
					else if(((((BicStatusTableApi *) tmpData1)[0]).oprState == 1) && (tmpBicTable->adminState == 0)) /*1=ENABLED 0=DISABLED*/ 
          fprintf(stderr,"%6s","LENB"); 
					else if(((((BicStatusTableApi *) tmpData1)[0]).oprState == 0) && (tmpBicTable->adminState == 0)) /*1=ENABLED 0=DISABLED*/ 
          fprintf(stderr,"%6s","LDIS"); 
          else
          fprintf(stderr,"%6s","UDIS"); 
          //  scrBscConfigPtr[tBandmpCnt1].oprState |= 0x02;

          i = inet_addr((((BicStatusTableApi *)tmpData1)[0]).btsIpAddr);
          in.s_addr = htonl(i);
           
          //strcpy(scrBscConfigPtr[tmpCnt1].btsIpAddr, inet_ntoa(in));
          fprintf(stderr,"%16s",inet_ntoa(in));

/*          if( (strcmp(inet_ntoa(in),"255.255.255.255")==0) ||(strcmp(inet_ntoa(in),"0.0.0.0")==0) )  
          {
          fprintf(stderr,"%7s","NA");
					}
*/
#if 0   
       else
          {
          sts = getPingableIp((char *)inet_ntoa(in));
          if(sts == 1)
          fprintf(stderr,"%7s","SUCC");
          else
          fprintf(stderr,"%7s","FAIL");
          }
#endif
          free(tmpData1);
          dbSts = getallTrxTable((TrxTableApi **)&tmpData2, &outRows2, &outSize2);
          if(dbSts == DBLIB_SUCCESS && outRows2 > 0)
          {
            tmpTrxId1=0; tmpTrxId2=0;
            for(tmpCnt2=0; tmpCnt2<outRows2; ++tmpCnt2)
            {
              tmpTrxTable = (TrxTableApi *)((I_U8*)tmpData2 + (tmpCnt2 *outSize2));
              if(tmpTrxTable->bicId == tmpBicTable->bicId)
              {
                tmpAntId = tmpTrxTable->antennaID;
                if(tmpTrxId1 == 0)
                  tmpTrxId1 = tmpTrxTable->ptrxId;
                else
                  tmpTrxId2 = tmpTrxTable->ptrxId;
                //break;
              }
            }/*for*/
            free(tmpData2);
          } 
          dbSts = getallCellPerTable((CellPerTableApi **)&tmpData2, &outRows2, &outSize2);
          if(dbSts == DBLIB_SUCCESS && outRows2 > 0)
          {
            for(tmpCnt2=0; tmpCnt2<outRows2; ++tmpCnt2)
            {
            tmpCellTable = (CellPerTableApi *)((I_U8*)tmpData2 + (tmpCnt2 *outSize2));
              if(tmpAntId == tmpCellTable->antennaId)
              {
                if((tmpCellTable->freqBandBcch == 1)||(tmpCellTable->freqBandBcch == 2))
                fprintf(stderr,"%7d",tmpCellTable->cellId); 
                else
                fprintf(stderr,"%7d",tmpCellTable->cellId); 
									


                if(tmpCellTable->freqBandBcch ==  4)
                fprintf(stderr,"(%s)","1800");
                else if(tmpCellTable->freqBandBcch ==  2)
                fprintf(stderr,"(%4s)","900");
                else if(tmpCellTable->freqBandBcch ==  1)
                fprintf(stderr,"(%4s)","850");
                else if(tmpCellTable->freqBandBcch ==  5)
                fprintf(stderr,"(%s)","1900");
                else
                fprintf(stderr,"(%s)","INVL");
                fprintf(stderr,"%7d",tmpCellTable->antennaId); 
                fprintf(stderr,"%8d",tmpCellTable->bcchArfcn); 

                tmpCellNonPerTableKey.lac    =tmpCellTable->lac;
                tmpCellNonPerTableKey.cellId =tmpCellTable->cellId;
                dbSts = getCellNonPerTable(&tmpCellNonPerTableKey,(CellNonPerTableApi **)&tmpData3);
                if(dbSts == DBLIB_SUCCESS) 
                {
                  if(((CellNonPerTableApi *) tmpData3)[0].oprState == 1)  /*1=ENABLED 0=DISABLED*/
                  {
										if(tmpCellTable->adminState == 1)
                    fprintf(stderr,"%7s","UENB"); 
 										else
                    fprintf(stderr,"%7s","LENB"); 

                    tmpPtrxIdKey.ptrxId = ((CellNonPerTableApi *)tmpData3)[0].bcchPtrxId;

                    dbSts = getPtrxTable(&tmpPtrxIdKey,(PtrxTableApi **)&tmpData4);
                    if(dbSts == DBLIB_SUCCESS) 
                    {
											tmpTrxIdKey.ptrxId=tmpPtrxIdKey.ptrxId;
					             dbSts = getTrxTable(&tmpTrxIdKey,(TrxTableApi **)&tmpData5);

                      if(((PtrxTableApi *)tmpData4)[0].oprState == 1)
											{
													if(((TrxTableApi *)tmpData5)[0].adminState == 1)
                        	{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","UENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","UENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
                        	}
													else
													{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","LENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","LENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
													}
                      }
											else
                      {
													if(((TrxTableApi *)tmpData5)[0].adminState == 1)
                        	{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","UDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","UDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
                        	}
													else
													{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","LDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","LDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
													}
                      }
											free(tmpData4);
											free(tmpData5);
                    }/*if*/

                    if(tmpPtrxIdKey.ptrxId == tmpTrxId1)
                      tmpPtrxIdKey.ptrxId = tmpTrxId2;
                    else if(tmpPtrxIdKey.ptrxId == tmpTrxId2)
                      tmpPtrxIdKey.ptrxId = tmpTrxId1;

                    dbSts = getPtrxTable(&tmpPtrxIdKey,(PtrxTableApi **)&tmpData4);
                    if(dbSts == DBLIB_SUCCESS) 
                    {
											 tmpTrxIdKey.ptrxId=tmpPtrxIdKey.ptrxId;
					             dbSts = getTrxTable(&tmpTrxIdKey,(TrxTableApi **)&tmpData5);
	
                      //if((((PtrxTableApi *)tmpData4)[0].oprState == 1) && (((TrxTableApi *)tmpData5)[0].adminState == 1))
                      //fprintf(stderr,"%9s:%d","UENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
                      //else
                      //fprintf(stderr,"%9s:%d","LDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 

//New

                      if(((PtrxTableApi *)tmpData4)[0].oprState == 1)
											{
													
													if(((TrxTableApi *)tmpData5)[0].adminState == 1)
                        	{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","UENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","UENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
                        	}
													else
													{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","LENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","LENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
													}
                      }
											else
                      {
													if(((TrxTableApi *)tmpData5)[0].adminState == 1)
                        	{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","UDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","UDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
                        	}
													else
													{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","LDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","LDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
													}
                      }

//New Ends

                      free(tmpData4);
                      free(tmpData5);
                    }/*if*/
                  }/*if*/
                  else
                  {
										if(tmpCellTable->adminState == 1)
                    fprintf(stderr,"%7s","UDIS"); //CellStatus
										else
                    fprintf(stderr,"%7s","LDIS"); //CellStatus

                    tmpPtrxIdKey.ptrxId = tmpTrxId1;

                    dbSts = getPtrxTable(&tmpPtrxIdKey,(PtrxTableApi **)&tmpData4);
                    if(dbSts == DBLIB_SUCCESS) 
                    {
											 tmpTrxIdKey.ptrxId=tmpPtrxIdKey.ptrxId;
					             dbSts = getTrxTable(&tmpTrxIdKey,(TrxTableApi **)&tmpData5);
                      if(((PtrxTableApi *)tmpData4)[0].oprState == 1)
											{
													
													if(((TrxTableApi *)tmpData5)[0].adminState == 1)
                        	{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","UENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","UENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
                        	}
													else
													{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","LENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","LENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
													}
                      }
											else
                      {
													if(((TrxTableApi *)tmpData5)[0].adminState == 1)
                        	{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","UDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","UDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
                        	}
													else
													{
														if(((PtrxTableApi *)tmpData4)[0].ptrxId <= 9)
                      			fprintf(stderr,"%9s:%2d","LDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
														else
                      			fprintf(stderr,"%9s:%d","LDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
													}
                      }
                      free(tmpData4);
                      free(tmpData5);
                    }/*if*/

                    if(tmpPtrxIdKey.ptrxId == tmpTrxId1)
                      tmpPtrxIdKey.ptrxId = tmpTrxId2;
                    else if(tmpPtrxIdKey.ptrxId == tmpTrxId2)
                      tmpPtrxIdKey.ptrxId = tmpTrxId1;

                    dbSts = getPtrxTable(&tmpPtrxIdKey,(PtrxTableApi **)&tmpData4);
                    if(dbSts == DBLIB_SUCCESS) 
                    {
											 tmpTrxIdKey.ptrxId=tmpPtrxIdKey.ptrxId;
					             dbSts = getTrxTable(&tmpTrxIdKey,(TrxTableApi **)&tmpData5);
                      if((((PtrxTableApi *)tmpData4)[0].oprState == 1) && (((TrxTableApi *)tmpData5)[0].adminState == 1))
                      fprintf(stderr,"%9s:%2d","UENB",((PtrxTableApi *)tmpData4)[0].ptrxId); 
                      else
                      fprintf(stderr,"%9s:%2d","LDIS",((PtrxTableApi *)tmpData4)[0].ptrxId); 
                       free(tmpData4);
                       free(tmpData5);
                    }/*if*/
										//cell status
                    
                  //  fprintf(stderr,"%7s","DIS"); 
                  //  fprintf(stderr,"%8s","DIS");//trx1 
                  //  fprintf(stderr,"%8s","DIS");//trx2 
									}
                  free(tmpData3);
                }/*if*/
                break;
              }/*if*/
            }/*for*/
            free(tmpData2);
          }/*if*/
    }/*if*/
 fprintf(stderr,"\n");
 }
      free(tmpData);
}
    if(dbSts != DBLIB_SUCCESS)
    {
      printf(DEBUG,"Bic Table dbSts(%d)",dbSts);
      //free(scrBscConfigPtr);
    }/*if*/

}

