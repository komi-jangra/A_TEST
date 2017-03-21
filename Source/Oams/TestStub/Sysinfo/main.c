#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sysxxx_typedef.h>
#include <sysxxx_hashdefs.h>
#include <CLIB.h>
#include <DBLIBError.h>
//#include <DBLIBConstants.h>
#include <dbsxxx_commondefs.h>
#include <dbsxxx_commonwrappers.h>
#include <dbsxxx_cellh_dbwrapper.h>
#include <oamscellh_sysinfo_hashdefs.h>
#include <oamscellh_sysinfo_encoder.h>
#include <ipcfrm_extern.h>
#include <sysxxx_proc.h>
#define BUF_LEN 50

void printBuff(I_U8 * buff , I_U16 len)
{
      int i = 0;
      for(i = 0 ; i < len ; i++)
         printf("%x\t" , buff[i]);
      printf("\n \n");
}

int main()
{
/* ---------------------------- Variable Dealaration ------------------------- */

   /* Db initialization With Default Values */
   I_S32    errCode =  0;
   I_U32    bscId   =  1;
   I_U32    cellId  = 14;
   I_U32    lac     = 24;

   /* To Be Fetched After DB Connect */
   I_U16    arfcn[ARFCN_LEN];
   I_U32    setLen         = 0;
   I_U32    band           = 0;  
   I_U32    freqBandBcch   = 0;
   I_U8     sysInfo2terind = 0;
   
   /* As & When Required Provide With Values */
   I_U8     tn        = 0;
   I_U8     tsc       = 0; 
   I_U8     baInd     = 0; 
   I_U8     ccchConf  = 0;
   I_U8     pbcchPres = 0;
   I_U16    tarfcn    = 0;

   /* Buffer To Fill SysInfo As L3 Info */
   I_U8    *buff  = NULL;
   I_U8    *buff1 = NULL;
   I_U8    *buff2 = NULL;
   I_U8    *buff3 = NULL;
   I_U8    *buff4 = NULL;  

   /* To Retrieve Length Of Encoded Buffer */
   I_U16    len   = 0;
   I_U16    len1  = 0;
   I_U16    len2  = 0;
   I_U16    len3  = 0;
   I_U16    len4  = 0;

   /* To Update SysInfo */
   I_U8     choice;

/*------------------------------------------------------------------------------*/
 
   /* To Register itself with IPC FrameWork */
   if (RegisterWithIpcFrmwrk(ENT_OAMS_CELLH, (I_S8 *)"ENT_OAMS_CELLH") < 0)
   {
      printf("\t Unable To Register Itself With IPC FrameWork : Exiting");
      exit(0) ;
   }

   /* To Connect itself with DB Server */
   errCode= dbConnect();
   if(errCode != CLIB_SUCCESS)
     {
      printf("\t Unable To Connect Itself With DB Server : Exiting");
      exit(0);   
    }

   /* Get the data needed from the Db */
   errCode = getFrequencyBandFromCellTable(cellId, lac, &freqBandBcch);
   if (errCode != CLIB_SUCCESS)
   {
      printf("\t Retrieval Failed From Cell Table For SI: err = %s", clib_strerror(errCode));
      exit(0);
   }

   /* Allocation Of Memory To Fetch Encoded Buffer Of Sys Info */  
   buff    =   (I_U8*)malloc(BUF_LEN); 
   buff1   =   (I_U8*)malloc(BUF_LEN);   
   buff2   =   (I_U8*)malloc(BUF_LEN);
   buff3   =   (I_U8*)malloc(BUF_LEN);
   buff4   =   (I_U8*)malloc(BUF_LEN);

   /* Assigning Null to Avoid Junk Values */
   memset(buff,  0, BUF_LEN);
   memset(buff1, 0, BUF_LEN);
   memset(buff2, 0, BUF_LEN);
   memset(buff3, 0, BUF_LEN);
   memset(buff4, 0, BUF_LEN);

   /* To Fill SysInfo 1 */ 
   if (PrepareSysInformation1 (cellId, lac, bscId, buff1, &len1 ) == CLIB_SUCCESS)
   {
      printf("\n \t Printing  SysInfo 1 \n");
      printBuff(buff1, len1);
   }
   else
      printf("\n Failure To Fill SysInfo 1");

   memset(arfcn, 0, sizeof(I_U16)*ARFCN_LEN);   
   /* Get The ARFCN's List Of Neighbour Cells */
   errCode = getNeighCellArfcn( cellId, lac, arfcn, &setLen, freqBandBcch );
   if ( (errCode != CLIB_SUCCESS) && 
        (errCode != DBLIBERR_BASEDAO_NO_INDEX_DEFINED )&&
        (errCode != DBLIBERR_BASEDAO_NO_INDEX_ENTRY ) )  
   {
      printf("\t Retrieval Failed From NeighbourCell Table for SI: err = %s", clib_strerror(errCode));
      exit(0);
   }

   /* To Fill SysInfo 2 */
   if ( PrepareSysInformation2( cellId, lac, bscId, buff2, &len2, arfcn, setLen, baInd )== 0)
   {
      printf("\n \t Printing  SysInfo 2 \n");
      printBuff(buff2, len2);
   }
   else
      printf("\n Failure To Fill SysInfo 2");

   /* To Fill SysInfo 5 */
   if ( PrepareSysInformation5( cellId, lac, buff, &len, arfcn, setLen, baInd ) == 0)
   {
      printf("\n \t Printing  SysInfo 5 \n");
      printBuff(buff, len);
      memset(buff,0,BUF_LEN);
   }
   else
      printf("\n Failure to fill SysInfo 5");

   /* To Get Complementary Band Of Serving Cell */
   switch(freqBandBcch)
   {
      case GSM900  : band = GSM1800;
      break;

      case GSM1800 : band = GSM900;
      break;
   
      default: printf("Invalid Value Of Band : %d",freqBandBcch);
      exit(0); 
   }

   sysInfo2terind = isNeighCellArfcnPresent( cellId, lac, band );
   if ( sysInfo2terind == I_TRUE )
   {
      /* Get the ARFCN's list of neighbour cells of complementary band */
      memset(arfcn, 0, sizeof(I_U16)*ARFCN_LEN);
      errCode = getNeighCellArfcn( cellId, lac, arfcn, &setLen, band );
      if (errCode != CLIB_SUCCESS )  
      {
         printf("\n Failure To Retrieve neighbour cells of complementary band ");
      } 
      else
      {  
         /* To Fill SysInfo 2 ter */ 
         if ( PrepareSysInformation2ter( cellId, lac, buff, &len, arfcn, setLen, baInd )== 0)
         {
            printf("\n \t Printing  SysInfo 2ter \n");
            printBuff(buff, len);
            memset(buff, 0, BUF_LEN);
         }
         else
            printf("\n Failure to fill SysInfo 2ter");

         /* To Fill SysInfo 5 ter */
         if ( PrepareSysInformation5ter( cellId, lac, buff, &len, arfcn, setLen, baInd )== 0)
         {
            printf("\n \t Printing  SysInfo 5ter \n");
            printBuff(buff, len);
            memset(buff, 0, BUF_LEN);
         }
         else
            printf("\n Failure to fill SysInfo 5ter");
      }
   }
   else
         printf("\n No Neighbour exist to broadcast SysInfo 2ter & 5ter");

   /* To Fill SysInfo 3 */
   if ( PrepareSysInformation3( sysInfo2terind, cellId, lac, bscId, ccchConf, buff3, &len3 ) == 0)
   {
      printf("\n \t Printing  SysInfo 3 \n");
      printBuff(buff3, len3);
   }
   else
      printf("\n Failure to fill SysInfo 3");

   /* To Fill SysInfo 4 */
   if ( PrepareSysInformation4( cellId, lac, bscId, buff4, &len4 ) == 0 )
   {
      printf("\n \t Printing  SysInfo 4 \n");
      printBuff(buff4, len4);
   }
   else
      printf("\n Failure to fill SysInfo 4");

   /* To Fill SysInfo 6 */
   if ( PrepareSysInformation6( cellId, lac, bscId, buff, &len )== 0)
   {
      printf("\n \t Printing  SysInfo 6 \n");
      printBuff(buff, len);
      memset(buff, 0, BUF_LEN);
   }
   else
      printf("\n Failure to fill SysInfo 6");
   
   /* To Fill SysInfo 13 */
   if ( PrepareSysInformation13( cellId, lac, bscId, buff, &len, pbcchPres, tsc, tn, tarfcn ) == 0)
   {
      printf("\n \t Printing  SysInfo 13 \n");
      printBuff(buff,len);
      memset(buff, 0, BUF_LEN);
   }
   else
      printf("\n Failure to fill SysInfo 13");

   printf(" \n \t -------------------------------------------------");
   printf(" \n \t Want To Update System Information y/n............. ");
   choice = getchar();
   
   if ( choice == 'y' || choice == 'Y' )
   {
      if ( updateSysInformation1( cellId, lac, buff1, len1, CELL_BAR_ACCESS) == 0)
      {
         printf("\n \t Printing  SysInfo 1 \n");
         printBuff(buff1, len1);
      }
      else
         printf("\n Failure To Fill SysInfo 1");

      if ( updateSysInformation2( cellId, lac, buff2, len2, CELL_BAR_ACCESS) == 0)
      {
         printf("\n \t Printing  SysInfo 2 \n");
         printBuff(buff2, len2);
      }
      else
         printf("\n Failure To Fill SysInfo 2");

      if ( updateSysInformation3( cellId, lac, buff3, len3, CELL_BAR_ACCESS) == 0)
      {
         printf("\n \t Printing  SysInfo 3 \n");
         printBuff(buff3, len3);
      }
      else
         printf("\n Failure To Fill SysInfo 3");

      if ( updateSysInformation4( cellId, lac, buff4, len4, CELL_BAR_ACCESS) == 0)
      {
         printf("\n \t Printing  SysInfo 4 \n");
         printBuff(buff4, len4);
      }
      else
         printf("\n Failure To Fill SysInfo 4");
   }

   printf(" \n \t -------------------------------------------------");
   printf(" \n \t Neighbours Entry Updated For System Information y/n ............. ");
   fflush(stdin);
   getchar();
   choice = getchar();
   if ( choice == 'y' || choice == 'Y' )
   {
      sysInfo2terind = isNeighCellArfcnPresent( cellId, lac, band );
      if ( sysInfo2terind == I_TRUE )
      {
         if ( updateSysInformation3( cellId, lac, buff3, len3, SI_2TER_IND_PRESENT ) == 0)
         {
            printf("\n \t Printing  SysInfo 3 \n");
            printBuff(buff3, len3);
         }
         else
            printf("\n Failure To Fill SysInfo 3");
      }
      else
      {
         if ( updateSysInformation3( cellId, lac, buff3, len3, SI_2TER_IND_NOT_PRESENT ) == 0)
         {
            printf("\n \t Printing  SysInfo 3 \n");
            printBuff(buff3, len3);
         }
         else
            printf("\n Failure To Fill SysInfo 3");
      }
   }
   free(buff);
   free(buff1);
   free(buff2);
   free(buff3);
   free(buff4);
   
   dbDestroy();
   return 0;
}  
  
