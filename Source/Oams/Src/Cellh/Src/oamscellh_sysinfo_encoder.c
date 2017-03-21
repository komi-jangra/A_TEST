/************************ File Header *****************************************
   File Name      : SysInfoEncoder.c                                          *
   Purpose        : Encoding System information messages                      *
   Project        : GSM                                                       *
   Subsystem      : BSC OAM Cell Handler                                      *
   Author         : VNL BSC TEAM  & Aricent                                   *
   Created        : 07/13/2007 12:26:47 AM IST                                *
   CSCI id        :                                                           *
   Version        : 1.0                                                       *
************************** End ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysxxx_typedef.h>
#include <CLIB.h>
#include <DBLIBError.h>
#include <sysxxx_hashdefs.h>
#include <sysxxx_msgstruct.h>
#include <dbsxxx_commondefs.h>
#include <dbsxxx_cellh_dbwrapper.h>
#include <dbsxxx_commonwrappers.h>
#include <ipcfrm_syslog.h>
#include <ipcfrm_extern.h>
#include <oamscellh_sysinfo_hashdefs.h>
#include <oamscellh_sysinfo_encoder.h>
#include <oamscellh_hashdefs.h>
/*#include "its_types.h"
#include "oam_trace.h"*/

// ********************************************************************************
//CODE ADDED BY PGOYAL....................

typedef struct bufInfo
{
   I_U8     octPos;
   I_U8     bitPos;
   I_U8     *buf;
} BufEncInfo, BufDecInfo;


/* MACRO: Put bit 0 into the buffer */
#define STUFF0(dest)             \
{    \
    (dest)->buf[(dest)->octPos] &= ~((I_U8) 1 << (7-((dest)->bitPos)));          \
    (dest)->bitPos += 1;               \
    (dest)->octPos += (dest)->bitPos >> 3;       \
    (dest)->bitPos &= 7;          \
}

/* MACRO: Put bit 1 into the buffer */
#define STUFF1(dest)             \
{                   \
    (dest)->buf[(dest)->octPos] |= ((I_U8) 1 << (7-((dest)->bitPos)));        \
    (dest)->bitPos += 1;               \
    (dest)->octPos += (dest)->bitPos >> 3;       \
    (dest)->bitPos &= 7;       \
}

/* MACRO: Put Value less than 32 bits*/
#define STUFFVAL(dest, numBits, srcVal)   \
{                                  \
    I_U8 aL[4]={0x00, 0x00, 0x00, 0x00};               \
    I_U32 vL = (I_U32)srcVal; \
    aL[0] = (vL >> 24)& 0xff; \
    aL[1] = (vL >> 16)& 0xff; \
    aL[2] = (vL >> 8)& 0xff; \
    aL[3] = vL & 0xff; \
    copyBits(&aL[(3-((numBits-1)>>3))], ((numBits&7)?(numBits&7):8), \
            &(dest)->buf[(dest)->octPos], (8-(dest)->bitPos), numBits);        \
    (dest)->bitPos += numBits;               \
    (dest)->octPos += (dest)->bitPos >> 3;       \
    (dest)->bitPos &= 7;          \
}

/* MACRO: Put to pack any number of bits from a 64 bit buffer */
#define STUFFARR(dest, numBits, srcPtr)       \
{                                  \
    copyBits(&srcPtr[(7-((numBits-1)>>3))], ((numBits&7)?(numBits&7):8), \
            &(dest)->buf[(dest)->octPos], (8-((dest)->bitPos)), numBits);         \
    (dest)->bitPos += numBits;               \
    (dest)->octPos += (dest)->bitPos >> 3;       \
    (dest)->bitPos &= 7;         \
}

/* MACRO: Extract 1 bit*/
#define XTRACT1(src, destVal)    \
{                         \
    destVal = 0;                          \
    destVal= ( ((src)->buf[(src)->octPos]) >> ( ((I_U8)(8-((src)->bitPos))) - 1) ) & 0x1; \
    (src)->bitPos += 1;               \
    (src)->octPos += (src)->bitPos >> 3;       \
    (src)->bitPos &= 7;          \
}

/* MACRO: to fetch less than 32 bits*/
#define XTRACTVAL(src, numBits, destVal)   \
{                                  \
    I_U8 aL[4]={0x00, 0x00, 0x00, 0x00};               \
    copyBits( &(src)->buf[(src)->octPos], (8-((src)->bitPos)), \
              &aL[(3-(I_U8)((numBits-1)>>3))], ((numBits&7)?(numBits&7):8), numBits);\
    destVal = (((I_U32)aL[0]) << 24) | (((I_U32)aL[1]) << 16)  | \
              (((I_U32)aL[2]) << 8)  | ((I_U32)aL[3]);\
    (src)->bitPos += numBits;               \
    (src)->octPos += (src)->bitPos >> 3;       \
    (src)->bitPos &= 7;          \
}

/* MACRO: Extract any number of bits into a 64 bit buffer, with the lsb at 
   the rightmost bit*/
#define XTRACTARR(src, numBits, destPtr)        \
{                   \
    copyBits(&(src)->buf[(src)->octPos], (8-((src)->bitPos)), &destPtr[(7-((I_U8)(numBits-1)>>3))],\
               ((numBits&7)?(numBits&7):8), numBits); \
    (src)->bitPos += numBits;               \
    (src)->octPos += (src)->bitPos >> 3;       \
    (src)->bitPos &= 7;      \
}



/********************************************************************************
 *
 *     Function:   copyBits
 *
 *     Descr:  This routine copies numBits number of bits from srcBitPos 
 *        position in  current octet from 'srcBuff buffer to   destBitPos 
 *        position in destBuff buffer.
 *
 *
*********************************************************************************/
void copyBits 
( 
 I_U8   *srcBuff,    /* Pointer to the source buffer */
 I_U32  srcBitPos,  /* Bit number in source buffer */
 I_U8   *destBuff,     /* Pointer to the destination buffer */
 I_U32  destBitPos, /* Bit number in destination buffer */
 I_U32  numBits     /* Number of bits to copy */
 )
{
    I_U32  numBytes = 0;

    /*For Stuffing: If we have less than 8 bits to copy, i.e. numbits < 8
      For Xtraction:If we have numBits less than the number of bits required 
           to reach the src to nearest octet boundary*/ 
    if( (srcBitPos < 8 ) && (numBits <= srcBitPos) )
    {
        if( numBits <= destBitPos)
        {
            *destBuff |= ( (*srcBuff >> (srcBitPos - numBits)) & 
                        ~(~0 << numBits)) << (destBitPos - numBits);
        }
        else
        {
            *destBuff |= ( (*srcBuff >> (srcBitPos - destBitPos)) & 
                        ~(~0 << destBitPos));
            destBuff++;
            *destBuff |= ((*srcBuff >> (srcBitPos - numBits )) & 
                         ~(~0 << (numBits-destBitPos))) << 
                                 (8 - numBits + destBitPos );
        }
        return;  
    }

    /*For Stuffing: if numBits are not multiple of 8 then, copy the essential 
       bits from the starting so that only multiples of octets left to be copied
      For Xtraction: copy the essential number of bits so Source '
       curbitpos/srcBitPos reaches the octet boundary*/
    if( srcBitPos != 8 )
    {
        if( srcBitPos <= destBitPos)
        {
            *destBuff |= ( (*srcBuff ) & ~(~0 << srcBitPos)) << 
                     (destBitPos - srcBitPos);
            destBitPos -= srcBitPos; 
        }
        else
        {
            *destBuff |= ( (*srcBuff >> (srcBitPos - destBitPos)) & 
                        ~(~0 << destBitPos));
            destBuff++;
            *destBuff |= ((*srcBuff ) & ~(~0 << (srcBitPos-destBitPos))) << 
                        (8 - srcBitPos + destBitPos );
             destBitPos += (8 - srcBitPos);
        }
    
        numBits -= srcBitPos; 
        srcBuff++;
    }


    /*For Stuffing: copy the rest (which would be left from the previous block. 
          (here numbits would be multiple of 8 only)
      For Xtraction: extract the maximum number of octets directly*/
    if( (numBytes = (numBits >> 3)) > 0 )
    {
        /* Here we copy numBytes from srcBuff buffer which are aligned 
          at octet boundaries to destBuff buffer from 'destBitPos' position. */
        numBits -= (numBytes << 3);
        while( numBytes-- )
        {
            *destBuff++ |= (*srcBuff >> (8 - destBitPos));
            if( destBitPos != 8)
            {
                *destBuff = *srcBuff << destBitPos; 
            }
            srcBuff++;
        }
    }

    /*For Stuffing: The following block will not be executed( Condition will always be false)*/
    /*For Xtraction: copy the rest bits left*/
    if( numBits > 0 )
    {
        if( numBits <= destBitPos)
        {
            *destBuff |= ( (*srcBuff >> (8 - numBits)) & ~(~0 << numBits)) << 
                        (destBitPos - numBits);
        }
        else
        {
            *destBuff |= ( (*srcBuff >> (8 - destBitPos)) & 
                        ~(~0 << destBitPos));
            destBuff++;
            *destBuff |= ((*srcBuff >> (8 - numBits )) & 
                        ~(~0 << (numBits-destBitPos))) << 
                             (8- numBits + destBitPos );
        }
    }

    return;
}


/***********************************************************************
 *
 *     Function   :  fillPadding
 *     Description: Function to add padding to control blocks
 *
***********************************************************************/
void fillPadding
(
BufEncInfo *enc,
I_U8 len
)
{
   I_U8  mask = 0x2b; 
   I_U8  octPos = enc->octPos;
   I_U8  bitPos = enc->bitPos;

   /* if message is full, no padding */
   if (octPos >= len) 
    return; 

   /* assume the buffer is zero'ed initially (i.e. next bit is zero to start
      the padding)*/
   bitPos++;
   enc->buf[octPos++] |= ((~(~0 <<(8 - bitPos))) & mask);

   while (octPos < len)
   {
    enc->buf[octPos++] = mask; 
   }

   return; 
} /*End of Function*/


//CODE ADDED BY PGOYAL....................
// ********************************************************************************


I_U8 nextIndex = 0;
I_U8 msInfoIndex = 0;
static I_S32 Encode_san(I_S32 index, I_S32 *set, I_S32 len, I_S32 range, I_S32 *nW);
static I_S32  Encode(I_S32 index, I_S32 *set, I_S32 len, I_S32 range, I_S32 *nW);
/* Commented by Aricent
SysInfoEncoder::SysInfoEncoder()
{
	
} */
/***********************************************************************************
*  Function Name   : PrepareSysInformation1
*
*  Args            : 1. cell id  
*                    2. lac 
*                    3. bsc id
*                    4. buff
*                    5. bufLen
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will FILL the SystemInfo1  structure 
***********************************************************************************/

I_S32 PrepareSysInformation1(I_U32 cellId, I_U32 lac, I_U32 bscId, I_U8 * buff , I_U16 * bufLen)
{
   I_U16 tvar1 = 0;
   I_S32 index;
   I_S32 range;
   I_U32 i = 0;
   I_U32 setLen = 0;
   I_S32 nW[NW_LEN];
   I_S32 set[ARFCN_LEN]; 
   I_S32 errCode = 1;
   I_U16 arfcn[ARFCN_LEN];/* the maximum number of arfcn can be 18 */
   I_S32 temp = 0;
   I_U32 oprStateAInterface = 0;
   I_U32 outRows = 0;
   I_U16 outSize = 0;  
   CellTableApi * cellTableOutData ;
   BssTableApi * bssTableOutData;
   SiPreconfigTableApi * siPreconfigTableOutData;
   CellTableIndices  cellTableInData;
   BssTableIndices  bssTableInData;
   SystemInfo1 *sysInfo = (SystemInfo1 *)AlocOrdBuf(sizeof(SystemInfo1));   

   /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo1));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo1 structure");
      return errCode;
   }

 
  /* initializing arfcn array to zero */ 
   memset(arfcn,0,sizeof(I_U16)*ARFCN_LEN); 
   memset(set,0,sizeof(I_S32)*ARFCN_LEN); 
   

  /* Get the data needed from the Db */
   cellTableInData.cellId = cellId;
   cellTableInData.lac = lac;
   errCode = getCellTable(&cellTableInData, &cellTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI1: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }
  
   bssTableInData.bscId = bscId;
   errCode = getBssTable(&bssTableInData, &bssTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from BSS Table for SI1: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      return errCode;
   }

   errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
   if ((errCode != CLIB_SUCCESS)||(outRows < 1))
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI1: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      return errCode;
   }

   /*  value of ARFCNs  from hopping channel groups*/
   errCode = getchnGrpArfcn(cellTableOutData->cellId,cellTableOutData->lac,arfcn,&setLen);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Channel Group Table for SI1: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      free(siPreconfigTableOutData);
      return errCode;
   }
   errCode = getAInterfaceOprState(&oprStateAInterface);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from AInterface Table for SI1:err=%s",clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      free(siPreconfigTableOutData);
      return errCode;
   }
    
   for(i=0 ; i < setLen ; i++)
      set[i] = arfcn[i]; 
  
  
   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG;
   LOG_PRINT(DEBUG,"sysInfo1->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);
   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR;
   LOG_PRINT(DEBUG,"sysInfo1->skipIndicator = %d",sysInfo->skipIndicator);
   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_01;
   LOG_PRINT(DEBUG,"sysInfo1->messageType = %d",sysInfo->messageType);
   /* fill in formatIndicator */
   if ( (cellTableOutData->freqBandBcch == GSM850
      || cellTableOutData->freqBandBcch == GSM1800
      || cellTableOutData->freqBandBcch == GSM1900))
   {	 
      strcpy((char *)sysInfo->formatIndicator,"range512format");
      LOG_PRINT(DEBUG,"sysInfo1->formatIndicator = %s",sysInfo->formatIndicator);
      if(setLen > 0)
      {
         for(i=0; i< NW_LEN; i++)
            nW[i] = 0;
      
         index = BITMAP_512_INDEX;
         range = BITMAP_512_RANGE;  
         sysInfo->origARFCN = set[0]; /* original ARFCN */
         LOG_PRINT(DEBUG,"sysInfo1->origARFCN = %d",sysInfo->origARFCN);
         for(i = 1 ; i< setLen ; i++)
            set[i-1] = set[i]-( sysInfo->origARFCN + 1); 
         Encode_san(index, set, setLen - 1, range, nW);
         sysInfo->w1 = nW[0];
         sysInfo->w2 = nW[1];
         sysInfo->w3 = nW[2];
         sysInfo->w4 = nW[3];
         sysInfo->w5 = nW[4];
         sysInfo->w6 = nW[5];
         sysInfo->w7 = nW[6];
         sysInfo->w8 = nW[7];
         sysInfo->w9 = nW[8];
         sysInfo->w10 = nW[9];
         sysInfo->w11 = nW[10];
         sysInfo->w12 = nW[11];
         sysInfo->w13 = nW[12];
         sysInfo->w14 = nW[13];
         sysInfo->w15 = nW[14];
         sysInfo->w16 = nW[15];
         sysInfo->w17 = nW[16];
         LOG_PRINT(DEBUG,"sysInfo1->w1 = %d",sysInfo->w1);
         LOG_PRINT(DEBUG,"sysInfo1->w2 = %d",sysInfo->w2);
         LOG_PRINT(DEBUG,"sysInfo1->w3 = %d",sysInfo->w3);
         LOG_PRINT(DEBUG,"sysInfo1->w4 = %d",sysInfo->w4);
         LOG_PRINT(DEBUG,"sysInfo1->w5 = %d",sysInfo->w5);
         LOG_PRINT(DEBUG,"sysInfo1->w6 = %d",sysInfo->w6);
         LOG_PRINT(DEBUG,"sysInfo1->w7 = %d",sysInfo->w7);
         LOG_PRINT(DEBUG,"sysInfo1->w8 = %d",sysInfo->w8);
         LOG_PRINT(DEBUG,"sysInfo1->w9 = %d",sysInfo->w9);
         LOG_PRINT(DEBUG,"sysInfo1->w10 = %d",sysInfo->w10);
         LOG_PRINT(DEBUG,"sysInfo1->w11 = %d",sysInfo->w11);
         LOG_PRINT(DEBUG,"sysInfo1->w12 = %d",sysInfo->w12);
         LOG_PRINT(DEBUG,"sysInfo1->w13 = %d",sysInfo->w13);
         LOG_PRINT(DEBUG,"sysInfo1->w14 = %d",sysInfo->w14);
         LOG_PRINT(DEBUG,"sysInfo1->w15 = %d",sysInfo->w15);
         LOG_PRINT(DEBUG,"sysInfo1->w16 = %d",sysInfo->w16);
         LOG_PRINT(DEBUG,"sysInfo1->w17 = %d",sysInfo->w17);
      }
   }
   /* making list of frequencies for Bitmap 0 format*/
   else if (cellTableOutData->freqBandBcch == GSM900)
   {
			if((cellTableOutData->bcchArfcn >= 975) && (cellTableOutData->bcchArfcn <= 1023))
			{
      	LOG_PRINT(DEBUG,"Inside range1024format"); 
      	strcpy((char *)sysInfo->formatIndicator,"range1024format");
         if(arfcn[0]>0) sysInfo->f1 = arfcn[0]; else sysInfo->f1 = -1;
         if(arfcn[1]>0) sysInfo->f2 = arfcn[1]; else sysInfo->f2 = -1;
         if(arfcn[2]>0) sysInfo->f3 = arfcn[2]; else sysInfo->f3 = -1;
         if(arfcn[3]>0) sysInfo->f4 = arfcn[3]; else sysInfo->f4 = -1;
         if(arfcn[4]>0) sysInfo->f5 = arfcn[4]; else sysInfo->f5 = -1;
         if(arfcn[5]>0) sysInfo->f6 = arfcn[5]; else sysInfo->f6 = -1;
         if(arfcn[6]>0) sysInfo->f7 = arfcn[6]; else sysInfo->f7 = -1;
         if(arfcn[7]>0) sysInfo->f8 = arfcn[7]; else sysInfo->f8 = -1;
         if(arfcn[8]>0) sysInfo->f9 = arfcn[8]; else sysInfo->f9 = -1;
         if(arfcn[9]>0) sysInfo->f10 = arfcn[9]; else sysInfo->f10 = -1;
         if(arfcn[10]>0) sysInfo->f11 = arfcn[10]; else sysInfo->f11 = -1;
         if(arfcn[11]>0) sysInfo->f12 = arfcn[11]; else sysInfo->f12 = -1;
         if(arfcn[12]>0) sysInfo->f13 = arfcn[12]; else sysInfo->f13 = -1;
         if(arfcn[13]>0) sysInfo->f14 = arfcn[13]; else sysInfo->f14 = -1;
         if(arfcn[14]>0) sysInfo->f15 = arfcn[14]; else sysInfo->f15 = -1;
         if(arfcn[15]>0) sysInfo->f16 = arfcn[15]; else sysInfo->f16 = -1;
			}
			else
			{
      strcpy((char *)sysInfo->formatIndicator,"bitmap0format");
      LOG_PRINT(DEBUG,"sysInfo1->formatIndicator = %s",sysInfo->formatIndicator); 
      for(i=0 ; i < BITMAP_ZERO_LEN ; i++)
         sysInfo->ARFCN[i] = 0;
      
      for(i = 0 ; i < setLen ; i++)
      {
         if(arfcn[i]> 0 && arfcn[i]<= BITMAP_ZERO_LEN)
         {
            temp = arfcn[i];
      	    sysInfo->ARFCN[temp - 1] = 1;
            LOG_PRINT(DEBUG,"sysInfo1->ARFCN[%d] = %d",temp - 1,sysInfo->ARFCN[temp - 1]);
         }
      } 
			}
   }
   else if (cellTableOutData->freqBandBcch != GSM850
           && cellTableOutData->freqBandBcch != GSM900
           && cellTableOutData->freqBandBcch != GSM1800
           && cellTableOutData->freqBandBcch != GSM1900)
   {
       LOG_PRINT(CRITICAL,"Invalid Band : %d",cellTableOutData->freqBandBcch);
       DalocOrdBuf(sysInfo);
       free(cellTableOutData);
       free(bssTableOutData);
       free(siPreconfigTableOutData);
       errCode = 1;  
       return errCode;
   }
   /** #####no need to fill W1 .....Wn for other formats##### (Only bitmap 0 and bitmap512 format are supported)*/
   /* fill in re */
   sysInfo->re = (I_U8)bssTableOutData->callReestablishmentInd;
   LOG_PRINT(DEBUG,"sysInfo1->re = %d",sysInfo->re);  
  /* fill in cell bar access */
   if(cellTableOutData->cellBarAccess == I_FALSE &&
      oprStateAInterface == ENABLED)
      sysInfo->cellBarAccess = (I_U8)I_FALSE;
   else
      sysInfo->cellBarAccess = (I_U8)I_TRUE;
   LOG_PRINT(DEBUG,"sysInfo1->cellBarAccess = %d",sysInfo->cellBarAccess);
  /* fill in tx integer */
   sysInfo->txInteger = (I_U8)bssTableOutData->txInteger;
      LOG_PRINT(DEBUG,"sysInfo1->txInteger = %d",sysInfo->txInteger);
  /* fill in max retrans */
   sysInfo->maxRetans = (I_U8)bssTableOutData->maxRetrans;
   LOG_PRINT(DEBUG,"sysInfo1->maxRetans = %d",sysInfo->maxRetans);
  /* fill in ec */
   sysInfo->ec = (I_U8)siPreconfigTableOutData->ec;
   LOG_PRINT(DEBUG,"sysInfo1->ec = %d",sysInfo->ec);
  /* fill in access class */
   tvar1 = cellTableOutData->accessCtrlClass;
   
   for(i = 0 ; i < ACCESS_CLASS_LEN ; i++)
   {
      sysInfo->acClass[i] = tvar1 & 0x01;
      tvar1 = tvar1>>1;
      LOG_PRINT(DEBUG,"sysInfo1->acClass[%d] = %d",i , sysInfo->acClass[i]);

   }	  

 /* no need to fill in nch position,NCH */
 /* fill Band Indicator */
   if(cellTableOutData->freqBandBcch == GSM1900)
      sysInfo->BandIndicator = (I_U8)GSM1900;
    
   else
      sysInfo->BandIndicator = (I_U8)GSM1800;
   LOG_PRINT(DEBUG,"sysInfo1->BandIndicator = %d",sysInfo->BandIndicator);
   EncodeSysInformation1(sysInfo,buff,bufLen); 
   LOG_PRINT(DEBUG,"Printing Encoded System Information 1 message buffer");
   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));    
 /* free memory allocated */
   free(cellTableOutData);
   free(bssTableOutData);   
   free(siPreconfigTableOutData);
   DalocOrdBuf(sysInfo);
   return errCode;/* will be success */
}

/***********************************************************************************
*  Function Name   : PrepareSysInformation2
*
*  Args            : 1. cell id
*                    2. lac
*                    3. bsc id
*                    4. buff
*                    5. bufLen
*                    6. arfcn
*                    7. length
*                    8. aInd
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will FILL the SystemInfo2 structure 
***********************************************************************************/

I_S32 PrepareSysInformation2 (I_U32 cellId, I_U32 lac, I_U32 bscId,
                              I_U8 * buff, I_U16 * bufLen,
                              I_U16 arfcn[], I_U32 setLen, I_U8 baInd )
{
   I_U16 tvar1 = 0;
   I_U32 tvar2 = 0;
   I_S32 index;
   I_S32 range;
   I_U32 i = 0; 
   I_S32 nW[NW_LEN];
   I_S32 set[ARFCN_LEN];
   I_S32 temp = 0;
   I_U32 oprStateAInterface = 0;

   I_U32 outRows = 0;
   I_U16 outSize = 0;
   I_S32 errCode = 1;

   CellTableIndices         cellTableInData;
   CellTableApi            *cellTableOutData = NULL;
   BssTableIndices          bssTableInData;
   BssTableApi             *bssTableOutData = NULL;
   SiPreconfigTableApi     *siPreconfigTableOutData = NULL;

   SystemInfo2 *sysInfo = (SystemInfo2 *)AlocOrdBuf(sizeof(SystemInfo2));

    /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo2));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo2 structure");
      return errCode;
   }

   /* initializing arfcn array to zero */ 
   memset(set,0,sizeof(I_S32)*ARFCN_LEN);
   
   /* Value From Cell Table */
   cellTableInData.cellId = cellId;
   cellTableInData.lac = lac;
   errCode = getCellTable(&cellTableInData, &cellTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI2: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }

   /* Value From Bss Table */  
   bssTableInData.bscId = bscId;
   errCode = getBssTable(&bssTableInData, &bssTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from BSS Table for SI2: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      return errCode;
   }

   /* Value From SiPreconfig Table */
   errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
   if ((errCode != CLIB_SUCCESS)||(outRows < 1))
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI2: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      return errCode;
   }

   errCode = getAInterfaceOprState(&oprStateAInterface);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from AInterface Table for SI2:err=%s",clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      free(siPreconfigTableOutData);
      return errCode;
   }

   /*  value of ARFCNs  from  Neighbour Cell*/ 
   for ( i = 0; i < setLen; i++ )
      set[i]= arfcn[i]; 
  
   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG; 
   LOG_PRINT(DEBUG,"sysInfo2->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);   

   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR; 
   LOG_PRINT(DEBUG,"sysInfo2->skipIndicator = %d",sysInfo->skipIndicator); 

   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_02;
   LOG_PRINT(DEBUG,"sysInfo2->messageType = %d",sysInfo->messageType);

   /* fill in formatIndicator */
   if (( cellTableOutData->freqBandBcch == GSM850
      || cellTableOutData->freqBandBcch == GSM1800
      || cellTableOutData->freqBandBcch == GSM1900))
   {	 
      strcpy((char *)sysInfo->formatIndicator,"range512format");
      LOG_PRINT(DEBUG,"sysInfo2->formatIndicator = %s",sysInfo->formatIndicator);
      if(setLen > 0)
      {
         memset(nW, 0, sizeof(I_S32)*NW_LEN); 
      
         index = BITMAP_512_INDEX;
         range = BITMAP_512_RANGE;  
         sysInfo->origARFCN = set[0]; /* original ARFCN */
         LOG_PRINT(DEBUG,"sysInfo2->origARFCN = %d",sysInfo->origARFCN);
         for(i = 1 ; i< setLen ; i++)
            set[i-1] = set[i]-( sysInfo->origARFCN + 1); 
         Encode_san(index, set, setLen - 1, range, nW);
         sysInfo->w1 = nW[0];
         sysInfo->w2 = nW[1];
         sysInfo->w3 = nW[2];
         sysInfo->w4 = nW[3];
         sysInfo->w5 = nW[4];
         sysInfo->w6 = nW[5];
         sysInfo->w7 = nW[6];
         sysInfo->w8 = nW[7];
         sysInfo->w9 = nW[8];
         sysInfo->w10 = nW[9];
         sysInfo->w11 = nW[10];
         sysInfo->w12 = nW[11];
         sysInfo->w13 = nW[12];
         sysInfo->w14 = nW[13];
         sysInfo->w15 = nW[14];
         sysInfo->w16 = nW[15];
         sysInfo->w17 = nW[16];
         LOG_PRINT(DEBUG,"sysInfo2->w1 = %d",sysInfo->w1);
         LOG_PRINT(DEBUG,"sysInfo2->w2 = %d",sysInfo->w2);
         LOG_PRINT(DEBUG,"sysInfo2->w3 = %d",sysInfo->w3);
         LOG_PRINT(DEBUG,"sysInfo2->w4 = %d",sysInfo->w4);
         LOG_PRINT(DEBUG,"sysInfo2->w5 = %d",sysInfo->w5);
         LOG_PRINT(DEBUG,"sysInfo2->w6 = %d",sysInfo->w6);
         LOG_PRINT(DEBUG,"sysInfo2->w7 = %d",sysInfo->w7);
         LOG_PRINT(DEBUG,"sysInfo2->w8 = %d",sysInfo->w8);
         LOG_PRINT(DEBUG,"sysInfo2->w9 = %d",sysInfo->w9);
         LOG_PRINT(DEBUG,"sysInfo2->w10 = %d",sysInfo->w10);
         LOG_PRINT(DEBUG,"sysInfo2->w11 = %d",sysInfo->w11);
         LOG_PRINT(DEBUG,"sysInfo2->w12 = %d",sysInfo->w12);
         LOG_PRINT(DEBUG,"sysInfo2->w13 = %d",sysInfo->w13);
         LOG_PRINT(DEBUG,"sysInfo2->w14 = %d",sysInfo->w14);
         LOG_PRINT(DEBUG,"sysInfo2->w15 = %d",sysInfo->w15);
         LOG_PRINT(DEBUG,"sysInfo2->w16 = %d",sysInfo->w16);
         LOG_PRINT(DEBUG,"sysInfo2->w17 = %d",sysInfo->w17);
      } 
   }

   /* making list of frequencies for Bitmap 0 format*/
   else if (cellTableOutData->freqBandBcch == GSM900)
   {
			if(((arfcn[0] >= 975) && (arfcn[0] <= 1023))) 
				/* &&((cellTableOutData->bcchArfcn >= 975) && (cellTableOutData->bcchArfcn <= 1023)))*/
			{
      	LOG_PRINT(DEBUG,"Inside range1024format"); 
      	strcpy((char *)sysInfo->formatIndicator,"range1024format");
         if(arfcn[0]>0) sysInfo->f1 = arfcn[0]; else sysInfo->f1 = -1;
         if(arfcn[1]>0) sysInfo->f2 = arfcn[1]; else sysInfo->f2 = -1;
         if(arfcn[2]>0) sysInfo->f3 = arfcn[2]; else sysInfo->f3 = -1;
         if(arfcn[3]>0) sysInfo->f4 = arfcn[3]; else sysInfo->f4 = -1;
         if(arfcn[4]>0) sysInfo->f5 = arfcn[4]; else sysInfo->f5 = -1;
         if(arfcn[5]>0) sysInfo->f6 = arfcn[5]; else sysInfo->f6 = -1;
         if(arfcn[6]>0) sysInfo->f7 = arfcn[6]; else sysInfo->f7 = -1;
         if(arfcn[7]>0) sysInfo->f8 = arfcn[7]; else sysInfo->f8 = -1;
         if(arfcn[8]>0) sysInfo->f9 = arfcn[8]; else sysInfo->f9 = -1;
         if(arfcn[9]>0) sysInfo->f10 = arfcn[9]; else sysInfo->f10 = -1;
         if(arfcn[10]>0) sysInfo->f11 = arfcn[10]; else sysInfo->f11 = -1;
         if(arfcn[11]>0) sysInfo->f12 = arfcn[11]; else sysInfo->f12 = -1;
         if(arfcn[12]>0) sysInfo->f13 = arfcn[12]; else sysInfo->f13 = -1;
         if(arfcn[13]>0) sysInfo->f14 = arfcn[13]; else sysInfo->f14 = -1;
         if(arfcn[14]>0) sysInfo->f15 = arfcn[14]; else sysInfo->f15 = -1;
         if(arfcn[15]>0) sysInfo->f16 = arfcn[15]; else sysInfo->f16 = -1;
			}
			else
			{
      strcpy((char *)sysInfo->formatIndicator,"bitmap0format");
      LOG_PRINT(DEBUG,"sysInfo2->formatIndicator = %s",sysInfo->formatIndicator); 
      for(i=0 ; i < BITMAP_ZERO_LEN ; i++)
         sysInfo->ARFCN[i] = 0;
      
      for(i = 0 ; i < setLen ; i++)
      {
         if(arfcn[i]> 0 && arfcn[i]<= BITMAP_ZERO_LEN)
         {
            temp = arfcn[i];
      	    sysInfo->ARFCN[temp - 1] = 1;
            LOG_PRINT(DEBUG,"sysInfo2->ARFCN[%d]= %d",temp - 1, sysInfo->ARFCN[temp - 1]);
         }
         
      } 
			}
   }
   else if(cellTableOutData->freqBandBcch != GSM850
          && cellTableOutData->freqBandBcch != GSM1800 
          && cellTableOutData->freqBandBcch != GSM1900 
          && cellTableOutData->freqBandBcch != GSM900)  
   {
      LOG_PRINT(CRITICAL,"Invalid Band : %d" ,cellTableOutData->freqBandBcch);
      DalocOrdBuf(sysInfo); 
      free(cellTableOutData);
      free(bssTableOutData);
      free(siPreconfigTableOutData);
      errCode = 1;
      return errCode;

   }

   /* fill in ba_ind */
   sysInfo->ba_ind = baInd;
   LOG_PRINT(DEBUG,"sysInfo2->ba_ind = %d",sysInfo->ba_ind); 

   /* fill in ext ind */
   sysInfo->ext_ind = COMPLETE_BA;
   LOG_PRINT(DEBUG,"sysInfo2->ext_ind = %d",sysInfo->ext_ind);

   /* fill in NCC */
   tvar2 = (I_U8)bssTableOutData->nccPermitted;
	  
   for(i = 0 ; i < NCC_LEN ; i++)
   {
      sysInfo->NCC[i] = tvar2 & 0x01;
      tvar2 = tvar2>>1;
      LOG_PRINT(DEBUG,"sysInfo2->NCC[%d] = %d", i, sysInfo->NCC[i]);
   }
     
   /* fill in re */
   sysInfo->re = (I_U8)bssTableOutData->callReestablishmentInd;
   LOG_PRINT(DEBUG,"sysInfo2->re = %d",sysInfo->re);
	 
   /* fill in cell bar access */
   if(cellTableOutData->cellBarAccess == I_FALSE &&
      oprStateAInterface == ENABLED)
      sysInfo->cellBarAccess = (I_U8)I_FALSE;
   else
      sysInfo->cellBarAccess = (I_U8)I_TRUE;
   LOG_PRINT(DEBUG,"sysInfo2->cellBarAccess = %d",sysInfo->cellBarAccess);

   /* fill in tx integer */
   sysInfo->txInteger = (I_U8)bssTableOutData->txInteger;
   LOG_PRINT(DEBUG,"sysInfo2->txInteger = %d",sysInfo->txInteger);

   /* fill in max retrans */
   sysInfo->maxRetans = (I_U8)bssTableOutData->maxRetrans;
   LOG_PRINT(DEBUG,"sysInfo2->maxRetans = %d",sysInfo->maxRetans);

   /* fill in ec */
   sysInfo->ec = (I_U8)siPreconfigTableOutData->ec;
   LOG_PRINT(DEBUG,"sysInfo2->ec = %d",sysInfo->ec);

   /* fill in access class */
   tvar1 = cellTableOutData->accessCtrlClass;
   for(i = 0 ; i < ACCESS_CLASS_LEN ; i++)
   {
      sysInfo->acClass[i] = tvar1 & 0x01;
      tvar1 = tvar1>>1;
      LOG_PRINT(DEBUG,"sysInfo2->acClass[%d] = %d",i,sysInfo->acClass[i]);
   }	  

   EncodeSysInformation2(sysInfo,buff,bufLen);
   LOG_PRINT(DEBUG,"Printing Encoded System Information 2 message buffer");
   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));
   /* free memory allocated */
   free(cellTableOutData);
   free(bssTableOutData);   
   free(siPreconfigTableOutData);
   DalocOrdBuf(sysInfo);   
   return errCode;/* will be success */
}

/***********************************************************************************
*  Function Name   : PrepareSysInformation2ter
*
*  Args            : 1. cell id
*                    2. lac
*                    3. buff
*                    4. bufLen
*                    5. arfcn
*                    6. length
*                    7. baInd
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will FILL the SystemInfo2ter structure 
***********************************************************************************/

I_S32 PrepareSysInformation2ter ( I_U32 cellId , I_U32 lac, 
                                  I_U8 * buff , I_U16 * bufLen,
                                  I_U16 arfcn[], I_U32 setLen, I_U8 baInd )
{
   I_S32 index,range;
   I_U32 i =0; 
   I_S32 errCode = 1;
   I_S32 nW[NW_LEN];
   I_S32 set[ARFCN_LEN];
   I_S32 temp = 0;
   I_U32 band, freqBandBcch; 
   I_U8 mulbandReporting;

   SystemInfo2ter *sysInfo = (SystemInfo2ter *)AlocOrdBuf(sizeof(SystemInfo2ter));

    /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo2ter));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo2ter structure");
      return errCode;
   }


   /* initializing arfcn array to zero */
   memset(set,0,sizeof(I_S32)*ARFCN_LEN);
  
   /* Get the data needed from the Db */
   errCode = getFrequencyBandFromCellTable(cellId, lac, &freqBandBcch);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI2ter: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }
   
   switch(freqBandBcch)
   {
      case GSM900 : band = GSM1800;
      break;

      case GSM1800 : band = GSM900;
      break;
   
      case GSM850 : band = GSM1900;
      break;

      case GSM1900 : band = GSM850;
      break;
   
      default: LOG_PRINT(CRITICAL,"Invalid value of Band : %d",freqBandBcch);
      DalocOrdBuf(sysInfo); 
      errCode = 1;
      return errCode;
   } 

  /* Get the value of multiband reporting */
   errCode = getMultibandReportingFromHoCtrlTable(cellId, lac, &mulbandReporting);
   if ( errCode != CLIB_SUCCESS )
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from HoCtrl Table for SI2ter: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }

   /*  value of ARFCNs  from  Neighbour Cell*/
   for ( i = 0; i < setLen; i++ )
      set[i] = arfcn[i];
  
   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG; 
   LOG_PRINT(DEBUG,"sysInfo2ter->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);

   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR; 
   LOG_PRINT(DEBUG,"sysInfo2ter->skipIndicator = %d",sysInfo->skipIndicator); 

   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_02ter;
   LOG_PRINT(DEBUG,"sysInfo2ter->messageType = %d",sysInfo->messageType);

   /* fill in formatIndicator */
   if (( band == GSM850
      || band == GSM1800
      || band == GSM1900))
   {	 
      strcpy((char *)sysInfo->formatIndicator,"range512format");
      LOG_PRINT(DEBUG,"sysInfo2ter->formatIndicator = %s",sysInfo->formatIndicator);
      if(setLen > 0)
      {
         memset(nW, 0, sizeof(I_S32)*NW_LEN);

         index = BITMAP_512_INDEX;
         range = BITMAP_512_RANGE;  
         sysInfo->origARFCN = set[0]; /* original ARFCN */
         LOG_PRINT(DEBUG,"sysInfo2ter->origARFCN = %d",sysInfo->origARFCN);
         for(i = 1 ; i< setLen ; i++)
            set[i-1] = set[i]-(sysInfo->origARFCN + 1); 
         Encode_san(index, set, setLen - 1, range, nW);
         sysInfo->w1 = nW[0];
         sysInfo->w2 = nW[1];
         sysInfo->w3 = nW[2];
         sysInfo->w4 = nW[3];
         sysInfo->w5 = nW[4];
         sysInfo->w6 = nW[5];
         sysInfo->w7 = nW[6];
         sysInfo->w8 = nW[7];
         sysInfo->w9 = nW[8];
         sysInfo->w10 = nW[9];
         sysInfo->w11 = nW[10];
         sysInfo->w12 = nW[11];
         sysInfo->w13 = nW[12];
         sysInfo->w14 = nW[13];
         sysInfo->w15 = nW[14];
         sysInfo->w16 = nW[15];
         sysInfo->w17 = nW[16];
         LOG_PRINT(DEBUG,"sysInfo2ter->w1 = %d",sysInfo->w1);
         LOG_PRINT(DEBUG,"sysInfo2ter->w2 = %d",sysInfo->w2);
         LOG_PRINT(DEBUG,"sysInfo2ter->w3 = %d",sysInfo->w3);
         LOG_PRINT(DEBUG,"sysInfo2ter->w4 = %d",sysInfo->w4);
         LOG_PRINT(DEBUG,"sysInfo2ter->w5 = %d",sysInfo->w5);
         LOG_PRINT(DEBUG,"sysInfo2ter->w6 = %d",sysInfo->w6);
         LOG_PRINT(DEBUG,"sysInfo2ter->w7 = %d",sysInfo->w7);
         LOG_PRINT(DEBUG,"sysInfo2ter->w8 = %d",sysInfo->w8);
         LOG_PRINT(DEBUG,"sysInfo2ter->w9 = %d",sysInfo->w9);
         LOG_PRINT(DEBUG,"sysInfo2ter->w10 = %d",sysInfo->w10);
         LOG_PRINT(DEBUG,"sysInfo2ter->w11 = %d",sysInfo->w11);
         LOG_PRINT(DEBUG,"sysInfo2ter->w12 = %d",sysInfo->w12);
         LOG_PRINT(DEBUG,"sysInfo2ter->w13 = %d",sysInfo->w13);
         LOG_PRINT(DEBUG,"sysInfo2ter->w14 = %d",sysInfo->w14);
         LOG_PRINT(DEBUG,"sysInfo2ter->w15 = %d",sysInfo->w15);
         LOG_PRINT(DEBUG,"sysInfo2ter->w16 = %d",sysInfo->w16);
         LOG_PRINT(DEBUG,"sysInfo2ter->w17 = %d",sysInfo->w17);
      }    
   }
   /* making list of frequencies for Bitmap 0 format*/
   else if (band == GSM900)
   {
			if(((arfcn[0] >= 975) && (arfcn[0] <= 1023))) 
				/* &&((cellTableOutData->bcchArfcn >= 975) && (cellTableOutData->bcchArfcn <= 1023)))*/
			{
      	LOG_PRINT(DEBUG,"Inside range1024format"); 
      	strcpy((char *)sysInfo->formatIndicator,"range1024format");
         if(arfcn[0]>0) sysInfo->f1 = arfcn[0]; else sysInfo->f1 = -1;
         if(arfcn[1]>0) sysInfo->f2 = arfcn[1]; else sysInfo->f2 = -1;
         if(arfcn[2]>0) sysInfo->f3 = arfcn[2]; else sysInfo->f3 = -1;
         if(arfcn[3]>0) sysInfo->f4 = arfcn[3]; else sysInfo->f4 = -1;
         if(arfcn[4]>0) sysInfo->f5 = arfcn[4]; else sysInfo->f5 = -1;
         if(arfcn[5]>0) sysInfo->f6 = arfcn[5]; else sysInfo->f6 = -1;
         if(arfcn[6]>0) sysInfo->f7 = arfcn[6]; else sysInfo->f7 = -1;
         if(arfcn[7]>0) sysInfo->f8 = arfcn[7]; else sysInfo->f8 = -1;
         if(arfcn[8]>0) sysInfo->f9 = arfcn[8]; else sysInfo->f9 = -1;
         if(arfcn[9]>0) sysInfo->f10 = arfcn[9]; else sysInfo->f10 = -1;
         if(arfcn[10]>0) sysInfo->f11 = arfcn[10]; else sysInfo->f11 = -1;
         if(arfcn[11]>0) sysInfo->f12 = arfcn[11]; else sysInfo->f12 = -1;
         if(arfcn[12]>0) sysInfo->f13 = arfcn[12]; else sysInfo->f13 = -1;
         if(arfcn[13]>0) sysInfo->f14 = arfcn[13]; else sysInfo->f14 = -1;
         if(arfcn[14]>0) sysInfo->f15 = arfcn[14]; else sysInfo->f15 = -1;
         if(arfcn[15]>0) sysInfo->f16 = arfcn[15]; else sysInfo->f16 = -1;
			}
			else
			{
      strcpy((char *)sysInfo->formatIndicator,"bitmap0format");
      LOG_PRINT(DEBUG,"sysInfo2ter->formatIndicator = %s",sysInfo->formatIndicator);
 
      for(i=0 ; i < BITMAP_ZERO_LEN ; i++)
         sysInfo->ARFCN[i] = 0;
      
      for(i = 0 ; i < setLen ; i++)
      {
         if(arfcn[i]> 0 && arfcn[i]<= BITMAP_ZERO_LEN)
         {
            temp = arfcn[i];
      	    sysInfo->ARFCN[temp - 1] = 1;
            LOG_PRINT(DEBUG,"sysInfo2ter->ARFCN[%d] = %d", temp -1 ,sysInfo->ARFCN[temp - 1]);
         }
         
      } 
			}
   }
   else
   {
      LOG_PRINT(CRITICAL,"Invalid Band : %d" ,band);
      DalocOrdBuf(sysInfo); 
      errCode = ONE;
      return errCode;
   }
 
   /* fill in ba_ind */
   sysInfo->baInd = baInd; 
   LOG_PRINT(DEBUG,"sysInfo2ter->baInd = %d",sysInfo->baInd);	   

  /* ####fill in multiband reporting(here it is normal reporting)##### */
   sysInfo->multibandReporting = mulbandReporting;
   LOG_PRINT(DEBUG,"sysInfo2ter->multibandReporting = %d",sysInfo->multibandReporting);
		   
   /** #####no need to fill W1 .....Wn for other formats##### 
        (Only bitmap 0 and bitmap512 format are supported)*/

   /* SI2ter rest octet are not required to be filled(coded as L) */
   /* free memory allocated */  
   EncodeSysInformation2ter(sysInfo,buff,bufLen);
   LOG_PRINT(DEBUG,"Printing Encoded System Information 2ter message buffer");
   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));

   DalocOrdBuf(sysInfo);
   return errCode;/* will be success */
}

/***********************************************************************************
*  Function Name   : PrepareSysInformation3
*
*  Args            : 1. sysInfo2terInd 
                     2. sysInfo2quatInd 
*                    3. cell id
*                    4. lac
*                    5. bsc id
*                    6. cchConf
*                    7. buff
*                    8. bufLen
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will FILL the SystemInfo3 structure 
***********************************************************************************/

I_S32 PrepareSysInformation3(I_U8 sysInfo2terInd,I_U8 sysInfo2quatInd, I_U32 cellId, I_U32 lac, I_U32 bscId, I_U8 ccchConf, I_U8 * buff , I_U16 * bufLen)
{
   I_U32 i = 0;
   I_U16 tvar1   = 0;
   I_S32 errCode = 0;
   I_U32 outRows = 0;
   I_U16 outSize = 0;
   I_U32 oprStateAInterface = 0;

   BssTableIndices      bssTableInData;
   CellTableIndices     cellTableInData;
   PsCellTableIndices   psCellTableInData;
   BssTableApi          *bssTableOutData = NULL;
   CellTableApi         *cellTableOutData = NULL;
   PsCellTableApi       *psCellTableOutData = NULL;
   SiPreconfigTableApi  *siPreconfigTableOutData = NULL;

   SystemInfo3 *sysInfo = (SystemInfo3 *)AlocOrdBuf(sizeof(SystemInfo3)); 
    /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo3));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo3 structure");
      return errCode;
   }

   /* Get the data needed from the Db */
   cellTableInData.cellId = cellId;
   cellTableInData.lac = lac;
   errCode = getCellTable(&cellTableInData, &cellTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI3: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }
  
   bssTableInData.bscId = bscId;
   errCode = getBssTable(&bssTableInData, &bssTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from BSS Table for SI3: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      return errCode;
   }

   errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
   if ((errCode != CLIB_SUCCESS)||(outRows < 1))
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI3: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      return errCode;
   }
  
   errCode = getAInterfaceOprState(&oprStateAInterface);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from AInterface Table for SI3:err=%s",clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      free(siPreconfigTableOutData);
      return errCode;
   }

   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG; 
   LOG_PRINT(DEBUG,"sysInfo3->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);

   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR;
   LOG_PRINT(DEBUG,"sysInfo3->skipIndicator = %d",sysInfo->skipIndicator); 

   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_03;
   LOG_PRINT(DEBUG,"sysInfo3->messageType = %d",sysInfo->messageType);

   /* fill in cell identity */
   sysInfo->cellIdentity = cellTableOutData->cellId;
   LOG_PRINT(DEBUG,"sysInfo3->cellIdentity = %d",sysInfo->cellIdentity);
        
   /* fill in mobileCC */
   sysInfo->mobileCC = bssTableOutData->mcc;
   LOG_PRINT(DEBUG,"sysInfo3->mobileCC = %d",sysInfo->mobileCC);

   /* fill in mobileNC */
   sysInfo->mobileNC = bssTableOutData->mnc;
   LOG_PRINT(DEBUG,"sysInfo3->mobileNC = %d",sysInfo->mobileNC);

   /* fill in locationAreaCode */
   sysInfo->locationAreaCode = cellTableOutData->lac;
   LOG_PRINT(DEBUG,"sysInfo3->locationAreaCode = %d",sysInfo->locationAreaCode);
	
   /* fill in ccch_conf  */
   sysInfo->ccch_conf = ccchConf;
   LOG_PRINT(DEBUG,"sysInfo3->ccch_conf = %d",sysInfo->ccch_conf);

   errCode = updateCcchConf(cellId,lac,sysInfo->ccch_conf);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Updation failed for ccch conf for SI3: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      free(siPreconfigTableOutData);
      return errCode;
   }

   /* fill in bs_ag_blks_res */
   sysInfo->bs_ag_blks_res = (I_U8)cellTableOutData->bsAgBlksRes;
   LOG_PRINT(DEBUG,"sysInfo3->bs_ag_blks_res = %d",sysInfo->bs_ag_blks_res);

   /* fill in att */
   sysInfo->att = (I_U8)bssTableOutData->attInd;
   LOG_PRINT(DEBUG,"sysInfo3->att = %d",sysInfo->att);

   /* fill in mscr */
   sysInfo->mscr = (I_U8)siPreconfigTableOutData->mscr;
   LOG_PRINT(DEBUG,"sysInfo3->mscr = %d",sysInfo->mscr);

   /* fill in bs_pa_mfrms */
   sysInfo->bs_pa_mfrms = (I_U8)cellTableOutData->bsPaMfrms;
   LOG_PRINT(DEBUG,"sysInfo3->bs_pa_mfrms = %d",sysInfo->bs_pa_mfrms);

   /* fill in cbq3 */
   sysInfo->cbq3 = (I_U8)siPreconfigTableOutData->cbq3;
   LOG_PRINT(DEBUG,"sysInfo3->cbq3 = %d",sysInfo->cbq3);

   /* fill in timer3212value */
   sysInfo->timer3212value = (I_U8)bssTableOutData->t3212;
   LOG_PRINT(DEBUG,"sysInfo3->timer3212value = %d",sysInfo->timer3212value);

   /* fill in radio_link_timeout */
   sysInfo->radio_link_timeout = (I_U8)bssTableOutData->radioLinkTimeout;
   LOG_PRINT(DEBUG,"sysInfo3->radio_link_timeout = %d",sysInfo->radio_link_timeout);

   /* fill in dtx */
   sysInfo->dtx = (I_U8)bssTableOutData->dtxUpLinkInd;
   LOG_PRINT(DEBUG,"sysInfo3->dtx = %d",sysInfo->dtx);

   /* fill in pwrc */
   sysInfo->pwrc = (I_U8)siPreconfigTableOutData->pwrc;
   LOG_PRINT(DEBUG,"sysInfo3->pwrc = %d",sysInfo->pwrc);

   /* fill in dn_ind */
   sysInfo->dn_ind = (I_U8)siPreconfigTableOutData->dnInd;
   LOG_PRINT(DEBUG,"sysInfo3->dn_ind = %d",sysInfo->dn_ind);

   /* fill in ms txpwr max cch */
   sysInfo->ms_txpwr_max_cch = (I_U8)cellTableOutData->msTxPowerMaxCch;
   LOG_PRINT(DEBUG,"sysInfo3->ms_txpwr_max_cch = %d",sysInfo->ms_txpwr_max_cch);

   /* fill in cell reselect hystersis */
   sysInfo->cell_reselect_hystersis = (I_U8)cellTableOutData->cellReselectHysteresis;
   LOG_PRINT(DEBUG,"sysInfo3->cell_reselect_hystersis = %d",sysInfo->cell_reselect_hystersis);

   /* fill in rxlev access min */
   sysInfo->rxlev_access_min = (I_U8)cellTableOutData->rxLevAccessMin;
   LOG_PRINT(DEBUG,"sysInfo3->rxlev_access_min = %d",sysInfo->rxlev_access_min);

   /* fill in neci */
   sysInfo->neci = (I_U8)siPreconfigTableOutData->neci;
   LOG_PRINT(DEBUG,"sysInfo3->neci = %d",sysInfo->neci);

   /* fill in acs */
   sysInfo->acs = (I_U8)siPreconfigTableOutData->acs;
   LOG_PRINT(DEBUG,"sysInfo3->acs = %d",sysInfo->acs);

   /* fill in re */
   sysInfo->re = (I_U8)bssTableOutData->callReestablishmentInd;
   LOG_PRINT(DEBUG,"sysInfo3->re = %d",sysInfo->re);	 

   /* fill in cell bar access */
   if(cellTableOutData->cellBarAccess == I_FALSE &&
      oprStateAInterface == ENABLED)
      sysInfo->cellBarAccess = (I_U8)I_FALSE;
   else
      sysInfo->cellBarAccess = (I_U8)I_TRUE;
   LOG_PRINT(DEBUG,"sysInfo3->cellBarAccess = %d",sysInfo->cellBarAccess);

   /* fill in tx integer */
   sysInfo->txInteger = (I_U8)bssTableOutData->txInteger;
   LOG_PRINT(DEBUG,"sysInfo3->txInteger = %d",sysInfo->txInteger);

   /* fill in max retrans */
   sysInfo->maxRetans = (I_U8)bssTableOutData->maxRetrans;
   LOG_PRINT(DEBUG,"sysInfo3->maxRetans = %d",sysInfo->maxRetans);

   /* fill in ec */
   sysInfo->ec = (I_U8)siPreconfigTableOutData->ec;
   LOG_PRINT(DEBUG,"sysInfo3->ec = %d",sysInfo->ec);

   /* fill in access class */
   tvar1 = cellTableOutData->accessCtrlClass;
   for(i = 0; i < ACCESS_CLASS_LEN; i++)
   {
      sysInfo->acClass[i] = tvar1 & 0x01;
      tvar1 = tvar1>>1;
      LOG_PRINT(DEBUG,"sysInfo3->acClass[%d] = %d", i, sysInfo->acClass[i]);
   }	  

   /* Set OptionalSelectionparam Option */ 
   sysInfo->OptionalSelectionParameters = PRESENT;
   LOG_PRINT(DEBUG,"sysInfo3->OptionalSelectionParameters  = %d",sysInfo->OptionalSelectionParameters);
   if ( sysInfo->OptionalSelectionParameters == PRESENT )
   {
      /* fill in CBQ */
     //Changes for CBQ on CELLBARRED
      if(oprStateAInterface == ENABLED)
        sysInfo->CBQ = (I_U8)cellTableOutData->cbq; 
      else
        sysInfo->CBQ = ZERO; 
      LOG_PRINT(DEBUG,"sysInfo3->CBQ                  = %d", sysInfo->CBQ);

      /* fill in CELL RESELECT OFFSET */
      sysInfo->CELL_RESELECT_OFFSET = (I_U8)cellTableOutData->cellReselectOffset;
      LOG_PRINT(DEBUG,"sysInfo3->CELL_RESELECT_OFFSET = %d",sysInfo->CELL_RESELECT_OFFSET);

      /* fill in Temporaray Offset */
      sysInfo->TEMPORARY_OFFSET = (I_U8)cellTableOutData->tempOffset;
      LOG_PRINT(DEBUG,"sysInfo3->TEMPORARY_OFFSET     = %d",sysInfo->TEMPORARY_OFFSET);
      
      /* fill in PENALTY TIME */
      sysInfo->PENALTY_TIME = (I_U8)cellTableOutData->penalityTime; 
      LOG_PRINT(DEBUG,"sysInfo3->PENALTY_TIME         = %d",sysInfo->PENALTY_TIME);
   }

   /* Set PowerOffsetSelection Option */ 
   sysInfo->PowerOffsetSelection = PRESENT;
   LOG_PRINT(DEBUG,"sysInfo3->PowerOffsetSelection         = %d",sysInfo->PowerOffsetSelection);

   if ( sysInfo->PowerOffsetSelection == PRESENT )
   {
      /* fill in PowerOffset */
      sysInfo->PowerOffset = (I_U8)cellTableOutData->powerOffset;
      LOG_PRINT(DEBUG,"sysInfo3->PowerOffset         = %d",sysInfo->PowerOffset);
   }

   /* Set Sysinfo2terIndication (to be given by cell handler) */
   sysInfo->Sysinfo2terIndication = sysInfo2terInd;
   LOG_PRINT(DEBUG,"sysInfo3->Sysinfo2terIndication        = %d",sysInfo->Sysinfo2terIndication);
   
   /* fill in Early Classmark Sending Control */
   sysInfo->EarlyClassmarkSendingControl = siPreconfigTableOutData->earlyClassmarkSendingControl;
   LOG_PRINT(DEBUG,"sysInfo3->EarlyClassmarkSendingControl = %d",sysInfo->EarlyClassmarkSendingControl);

   /* Set SchedulingIfWhereoption (Coded as L) */
   sysInfo->SchedulingIfWhereOption = NOT_PRESENT;
   LOG_PRINT(DEBUG,"sysInfo3->SchedulingIfWhereOption      = %d",sysInfo->SchedulingIfWhereOption);

   /* #####fill in SchedulingIfWhere##### */
   sysInfo->SchedulingIfWhere = NOT_PRESENT;
   LOG_PRINT(DEBUG,"sysInfo3->SchedulingIfWhere   = %d",sysInfo->SchedulingIfWhere);

   /* Set GPRSIndicator Option*/ 
      /* Changes for PCU R2.5 : Start*/
   /*
   if(cellTableOutData->psStatus == 1) 
      sysInfo->GPRSIndicator = PRESENT;
   else
   */  
   
   sysInfo->GPRSIndicator = NOT_PRESENT;
      /* Changes for PCU R2.5 : End*/
   LOG_PRINT(DEBUG,"sysInfo3->GPRSIndicator                = %d",sysInfo->GPRSIndicator);	
/* Mantis 13890 changes start */
#if 0
   if(sysInfo->GPRSIndicator == PRESENT)
   {

      psCellTableInData.cellId = cellId;
      psCellTableInData.lac = lac;
      errCode = getPsCellTable(&psCellTableInData, &psCellTableOutData);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL,"Retrieval failed from PS Cell Table for SI3: err = %s", clib_strerror(errCode));
         DalocOrdBuf(sysInfo);
         free(cellTableOutData);
         free(bssTableOutData);
         free(siPreconfigTableOutData);
         return errCode;
      }	   
      /* fill in RA_COLOUR */
      sysInfo->RA_COLOUR = psCellTableOutData->raColour;
      LOG_PRINT(DEBUG,"sysInfo3->RA_COLOUR        = %d",sysInfo->RA_COLOUR);

      /* fill in SI13Position */
      sysInfo->SI13Position = siPreconfigTableOutData->si13Position;
      LOG_PRINT(DEBUG,"sysInfo3->SI13Position     = %d",sysInfo->SI13Position);
      free(psCellTableOutData);
   }
#endif
/* Mantis 13890 changes ends */

   /* fill in G3EarlyCMSendingrestriction */
   sysInfo->G3EarlyCMSendingRestriction = siPreconfigTableOutData->g3EarlyCmSendingRestriction;
   LOG_PRINT(DEBUG,"sysInfo3->G3EarlyCMSendingRestriction  = %d",sysInfo->G3EarlyCMSendingRestriction);

   /* 2G - 3G Handover */
   /* fill in SI2quaterPosition */
   sysInfo->SI2quaterPosition = sysInfo2quatInd;
   //sysInfo->SI2quaterPosition = 0;
   LOG_PRINT(DEBUG,"sysInfo3->SI2quaterPosition            = %d",sysInfo->SI2quaterPosition);

   /* #####fill in IuIndicator (it is not needed in CS2)#####
   sysInfo->iuIndicator = siPreconfigTableOutData->iuIndicator;*/

   /* free memory allocated */
   EncodeSysInformation3(sysInfo,buff,bufLen);

   LOG_PRINT(DEBUG,"Printing Encoded System Information 3 message buffer");
   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));

   free(cellTableOutData);
   free(bssTableOutData);   
   free(siPreconfigTableOutData);
   DalocOrdBuf(sysInfo);   
   return errCode;/* will be success */
}

/***********************************************************************************
*  Function Name   : PrepareSysInformation4
*
*  Args            : 1. cell id
*                    2. lac
*                    3. bsc id
*                    4. buff
*                    5. bufLen
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will FILL the SystemInfo4 structure 
***********************************************************************************/
I_S32 PrepareSysInformation4(I_U32 cellId, I_U32 lac, I_U32 bscId, I_U8 * buff , I_U16 * bufLen)
{
   I_U32 i = 0;
   I_U16 tvar1 = 0;
   I_U32 outRows = 0;
   I_U16 outSize = 0;
   I_S32 errCode = 0;
   I_U32 oprStateAInterface = 0;

   CellTableIndices    cellTableInData;
   BssTableIndices     bssTableInData;
   PsCellTableIndices  psCellTableInData;
   BssTableApi         *bssTableOutData = NULL;
   CellTableApi        *cellTableOutData = NULL;
   PsCellTableApi      *psCellTableOutData = NULL;
   SiPreconfigTableApi *siPreconfigTableOutData = NULL;

   SystemInfo4 *sysInfo = (SystemInfo4 *)AlocOrdBuf(sizeof(SystemInfo4));
    /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo4));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo4 structure");
      return errCode;
   }

   /* Get the data needed from the Db */
   cellTableInData.cellId = cellId;
   cellTableInData.lac = lac;
   errCode = getCellTable(&cellTableInData, &cellTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI4: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }
  
   bssTableInData.bscId = bscId;
   errCode = getBssTable(&bssTableInData, &bssTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from BSS Table for SI4: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      return errCode;
   }

   errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
   if ((errCode != CLIB_SUCCESS)||(outRows < 1))
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI4: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);   
      return errCode;
   }

   errCode = getAInterfaceOprState(&oprStateAInterface);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from AInterface Table for SI4:err=%s",clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);   
      free(siPreconfigTableOutData);
      return errCode;
   }

   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG; 
   LOG_PRINT(DEBUG,"sysInfo4->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);
   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR;
   LOG_PRINT(DEBUG,"sysInfo4->skipIndicator = %d",sysInfo->skipIndicator); 

   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_04;
   LOG_PRINT(DEBUG,"sysInfo4->messageType = %d",sysInfo->messageType);

   /* fill in cell identity */
   sysInfo->cellIdentity = cellTableOutData->cellId;
   LOG_PRINT(DEBUG,"sysInfo4->cellIdentity = %d",sysInfo->cellIdentity);
        
   /* fill in mobileCC */
   sysInfo->mobileCC = bssTableOutData->mcc;
   LOG_PRINT(DEBUG,"sysInfo4->mobileCC = %d",sysInfo->mobileCC);
	
   /* fill in mobileNC */
   sysInfo->mobileNC = bssTableOutData->mnc;
   LOG_PRINT(DEBUG,"sysInfo4->mobileNC = %d",sysInfo->mobileNC);

   /* fill in locationAreaCode */
   sysInfo->locationAreaCode = cellTableOutData->lac;
   LOG_PRINT(DEBUG,"sysInfo4->locationAreaCode = %d",sysInfo->locationAreaCode);

   /* fill in ms txpwr max cch */
   sysInfo->ms_txpwr_max_cch = (I_U8)cellTableOutData->msTxPowerMaxCch;
   LOG_PRINT(DEBUG,"sysInfo4->ms_txpwr_max_cch = %d",sysInfo->ms_txpwr_max_cch);

   /* fill in cell reselect hystersis */
   sysInfo->cell_reselect_hystersis = (I_U8)cellTableOutData->cellReselectHysteresis;
   LOG_PRINT(DEBUG,"sysInfo4->cell_reselect_hystersis = %d",sysInfo->cell_reselect_hystersis);

   /* fill in rxlev access min */
   sysInfo->rxlev_access_min = (I_U8)cellTableOutData->rxLevAccessMin;
   LOG_PRINT(DEBUG,"sysInfo4->rxlev_access_min = %d",sysInfo->rxlev_access_min);

   /* fill in neci */
   sysInfo->neci = (I_U8)siPreconfigTableOutData->neci;
   LOG_PRINT(DEBUG,"sysInfo4->neci = %d",sysInfo->neci);

   /* fill in acs */
   sysInfo->acs = (I_U8)siPreconfigTableOutData->acs;
   LOG_PRINT(DEBUG,"sysInfo4->acs = %d",sysInfo->acs);

   /* fill in re */
   sysInfo->re = (I_U8)bssTableOutData->callReestablishmentInd;
   LOG_PRINT(DEBUG,"sysInfo4->re = %d",sysInfo->re);
	 
   /* fill in cell bar access */
   if(cellTableOutData->cellBarAccess == I_FALSE &&
      oprStateAInterface == ENABLED)
      sysInfo->cellBarAccess = (I_U8)I_FALSE;
   else
      sysInfo->cellBarAccess = (I_U8)I_TRUE;
   LOG_PRINT(DEBUG,"sysInfo4->cellBarAccess = %d",sysInfo->cellBarAccess);

   /* fill in tx integer */
   sysInfo->txInteger = (I_U8)bssTableOutData->txInteger;
   LOG_PRINT(DEBUG,"sysInfo4->txInteger = %d",sysInfo->txInteger);

   /* fill in max retrans */
   sysInfo->maxRetans = (I_U8)bssTableOutData->maxRetrans;
   LOG_PRINT(DEBUG,"sysInfo4->maxRetans = %d",sysInfo->maxRetans);

   /* fill in ec */
   sysInfo->ec = (I_U8)siPreconfigTableOutData->ec;
   LOG_PRINT(DEBUG,"sysInfo4->ec = %d",sysInfo->ec);

   /* fill in access class */
   tvar1 = cellTableOutData->accessCtrlClass;
   for(i = 0 ; i < ACCESS_CLASS_LEN ; i++)
   {
      sysInfo->acClass[i] = tvar1 & 0x01;
      tvar1 = tvar1>>1;
      LOG_PRINT(DEBUG,"sysInfo4->acClass[%d] = %d", i, sysInfo->acClass[i]);
   }	  

   /* fill in OptionalSelectionparam */ 
   sysInfo->OptionalSelectionParameters = PRESENT;
   LOG_PRINT(DEBUG,"sysInfo4->OptionalSelectionParameters = %d",sysInfo->OptionalSelectionParameters);

   if ( sysInfo->OptionalSelectionParameters == PRESENT )
   {
      /* fill in CBQ */
     //Changes for CBQ on CELLBARRED
      if(oprStateAInterface == ENABLED)
        sysInfo->CBQ = (I_U8)cellTableOutData->cbq;
      else
        sysInfo->CBQ = 0; 
      LOG_PRINT(DEBUG,"sysInfo4->CBQ                  = %d", sysInfo->CBQ);

      /* fill in CELL RESELECT OFFSET */
      sysInfo->CELL_RESELECT_OFFSET = (I_U8)cellTableOutData->cellReselectOffset;
      LOG_PRINT(DEBUG,"sysInfo4->CELL_RESELECT_OFFSET = %d",sysInfo->CELL_RESELECT_OFFSET);

      /* fill in Temporaray Offset */
      sysInfo->TEMPORARY_OFFSET = (I_U8)cellTableOutData->tempOffset;
      LOG_PRINT(DEBUG,"sysInfo4->TEMPORARY_OFFSET     = %d",sysInfo->TEMPORARY_OFFSET);

      /* fill in PENALTY TIME */
      sysInfo->PENALTY_TIME = (I_U8)cellTableOutData->penalityTime;
      LOG_PRINT(DEBUG,"sysInfo4->PENALTY_TIME         = %d",sysInfo->PENALTY_TIME);
   }

   /* Set PowerOffsetSelection Option */
   sysInfo->PowerOffsetSelection = PRESENT;
   LOG_PRINT(DEBUG,"sysInfo4->PowerOffsetSelection         = %d",sysInfo->PowerOffsetSelection);

   if ( sysInfo->PowerOffsetSelection == PRESENT )
   {
      /* fill in PowerOffset */
      sysInfo->PowerOffset = (I_U8)cellTableOutData->powerOffset;
      LOG_PRINT(DEBUG,"sysInfo4->PowerOffset         = %d",sysInfo->PowerOffset);
   }

   /* fill in GPRSIndicator */

      /* Changes for PCU R2.5 : Starts*/
   /*
   if(cellTableOutData->psStatus == 1)
      sysInfo->GPRSIndicator = PRESENT;

   else
   */

   sysInfo->GPRSIndicator = NOT_PRESENT;
      /* Changes for PCU R2.5 : End*/
   LOG_PRINT(DEBUG,"sysInfo4->GPRSIndicator = %d",sysInfo->GPRSIndicator);

/*changes for Mantis 13890 start */
#if 0	 
   if(sysInfo->GPRSIndicator == PRESENT)
   {
      psCellTableInData.cellId = cellId;
      psCellTableInData.lac = lac;
      errCode = getPsCellTable(&psCellTableInData, &psCellTableOutData);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from PS Cell Table For SI4 : err = %s", clib_strerror(errCode));
         DalocOrdBuf(sysInfo);
         free(cellTableOutData);
         free(bssTableOutData);   
         free(siPreconfigTableOutData);
         return errCode;
      }	   
      /* fill in RA_COLOUR */
      sysInfo->RA_COLOUR = (I_U8)psCellTableOutData->raColour;
      LOG_PRINT(DEBUG,"sysInfo4->RA_COLOUR = %d",sysInfo->RA_COLOUR);
      /* fill in SI13Position */
      sysInfo->SI13Position = (I_U8)siPreconfigTableOutData->si13Position;
      LOG_PRINT(DEBUG,"sysInfo4->SI13Position = %d",sysInfo->SI13Position);
      free(psCellTableOutData);
   }
#endif
/*changes for Mantis 13890 ends */

   /* fill in BreakIndicator */
   sysInfo->BreakIndicator = (I_U8)siPreconfigTableOutData->breakIndicator;
   LOG_PRINT(DEBUG,"sysInfo4->BreakIndicator = %d",sysInfo->BreakIndicator);
   EncodeSysInformation4(sysInfo,buff,bufLen);
   LOG_PRINT(DEBUG,"Printing Encoded System Information 4 message buffer");
   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));
   /* free memory allocated */
   free(cellTableOutData);
   free(bssTableOutData);   
   free(siPreconfigTableOutData);
   DalocOrdBuf(sysInfo);
   return errCode;/* will be success */

}


I_S32 PrepareSysInformation4_Cbsh(I_U32 cellId, I_U32 lac, I_U32 bscId, I_U8 * buff , I_U16 * bufLen)
{

   I_U32 i = 0;
   I_U16 tvar1 = 0;
   I_U32 outRows = 0;
   I_U16 outSize = 0;
   I_S32 errCode = 0;
   I_U32 outCount = 0;
   I_U16 index = 0;

   I_U32 oprStateAInterface = 0;


   CellTableIndices    cellTableInData;
   BssTableIndices     bssTableInData;
   PsCellTableIndices  psCellTableInData;
   BssTableApi         *bssTableOutData = NULL;
   CellTableApi        *cellTableOutData = NULL;
   PsCellTableApi      *psCellTableOutData = NULL;
   SiPreconfigTableApi *siPreconfigTableOutData = NULL;
   ChnGrpTableApi      *chnGrpData =NULL;
   ChnGrpTableApi      *tempChnGrpPtr =NULL;
   

   SystemInfo4 *sysInfo = (SystemInfo4 *)AlocOrdBuf(sizeof(SystemInfo4));
    /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo4));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo4 structure");
      return errCode;
   }

   /* Get the data needed from the Db */
   cellTableInData.cellId = cellId;
   cellTableInData.lac = lac;
   errCode = getCellTable(&cellTableInData, &cellTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI4: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }
  
   bssTableInData.bscId = bscId;
   errCode = getBssTable(&bssTableInData, &bssTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from BSS Table for SI4: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      return errCode;
   }

   errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
   if ((errCode != CLIB_SUCCESS)||(outRows < 1))
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI4: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);   
      return errCode;
   }

   errCode = getAInterfaceOprState(&oprStateAInterface);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from AInterface Table for SI4:err=%s",clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);   
      free(siPreconfigTableOutData);
      return errCode;
   }
/* CBCH changes start */
 errCode = getTerChnGrpTable( TRUE, &tempChnGrpPtr, &outCount, &outSize);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from ChnGrp Table for SI4:err=%s",clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      free(siPreconfigTableOutData);
      return errCode;
   }
   errCode = CLIBERROR_DBLIB_ERROR;
   for( index=0; index<outCount; index++ )
   {	
      chnGrpData = (ChnGrpTableApi*)((I_U8*)(tempChnGrpPtr) + (index * outSize));  	    	     
      if ( (chnGrpData->cellId == cellId)  && (chnGrpData->lac == lac))
      {
          errCode = CLIB_SUCCESS;
          break;
      }
      
   }
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from ChnGrp Table for SI4:err=%s",clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);
      free(siPreconfigTableOutData);
      free(tempChnGrpPtr);
      return errCode;
   }

   sysInfo->tsc = chnGrpData->tsc;
   sysInfo->cbchArfcn = chnGrpData->arfcn1;
   sysInfo->hoppingChannel =  chnGrpData->hsn;
   if (chnGrpData->bcchCcchSdcch4 == 1)
         {
           sysInfo->channelType = BCCH_CCCH_SDCCH4_SI4_CBCH;
           sysInfo->timeslotNumber = 0;
         }
    else
        {
          sysInfo->channelType = SDCCH8_SI4_CBCH;
          sysInfo->timeslotNumber = 1;
        }
   sysInfo->cbchChannelDesIe = CBCH_CHANNEL_DESCRIPTION;

   free(tempChnGrpPtr);
/* CBCH changes end */

   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG; 
   LOG_PRINT(DEBUG,"sysInfo4->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);
   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR;
   LOG_PRINT(DEBUG,"sysInfo4->skipIndicator = %d",sysInfo->skipIndicator); 

   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_04;
   LOG_PRINT(DEBUG,"sysInfo4->messageType = %d",sysInfo->messageType);

   /* fill in cell identity */
   sysInfo->cellIdentity = cellTableOutData->cellId;
   LOG_PRINT(DEBUG,"sysInfo4->cellIdentity = %d",sysInfo->cellIdentity);
        
   /* fill in mobileCC */
   sysInfo->mobileCC = bssTableOutData->mcc;
   LOG_PRINT(DEBUG,"sysInfo4->mobileCC = %d",sysInfo->mobileCC);
	
   /* fill in mobileNC */
   sysInfo->mobileNC = bssTableOutData->mnc;
   LOG_PRINT(DEBUG,"sysInfo4->mobileNC = %d",sysInfo->mobileNC);

   /* fill in locationAreaCode */
   sysInfo->locationAreaCode = cellTableOutData->lac;
   LOG_PRINT(DEBUG,"sysInfo4->locationAreaCode = %d",sysInfo->locationAreaCode);

   /* fill in ms txpwr max cch */
   sysInfo->ms_txpwr_max_cch = (I_U8)cellTableOutData->msTxPowerMaxCch;
   LOG_PRINT(DEBUG,"sysInfo4->ms_txpwr_max_cch = %d",sysInfo->ms_txpwr_max_cch);

   /* fill in cell reselect hystersis */
   sysInfo->cell_reselect_hystersis = (I_U8)cellTableOutData->cellReselectHysteresis;
   LOG_PRINT(DEBUG,"sysInfo4->cell_reselect_hystersis = %d",sysInfo->cell_reselect_hystersis);

   /* fill in rxlev access min */
   sysInfo->rxlev_access_min = (I_U8)cellTableOutData->rxLevAccessMin;
   LOG_PRINT(DEBUG,"sysInfo4->rxlev_access_min = %d",sysInfo->rxlev_access_min);

   /* fill in neci */
   sysInfo->neci = (I_U8)siPreconfigTableOutData->neci;
   LOG_PRINT(DEBUG,"sysInfo4->neci = %d",sysInfo->neci);

   /* fill in acs */
   sysInfo->acs = (I_U8)siPreconfigTableOutData->acs;
   LOG_PRINT(DEBUG,"sysInfo4->acs = %d",sysInfo->acs);

   /* fill in re */
   sysInfo->re = (I_U8)bssTableOutData->callReestablishmentInd;
   LOG_PRINT(DEBUG,"sysInfo4->re = %d",sysInfo->re);
	 
   /* fill in cell bar access */
   if(cellTableOutData->cellBarAccess == I_FALSE &&
      oprStateAInterface == ENABLED)
      sysInfo->cellBarAccess = (I_U8)I_FALSE;
   else
      sysInfo->cellBarAccess = (I_U8)I_TRUE;
   LOG_PRINT(DEBUG,"sysInfo4->cellBarAccess = %d",sysInfo->cellBarAccess);

   /* fill in tx integer */
   sysInfo->txInteger = (I_U8)bssTableOutData->txInteger;
   LOG_PRINT(DEBUG,"sysInfo4->txInteger = %d",sysInfo->txInteger);

   /* fill in max retrans */
   sysInfo->maxRetans = (I_U8)bssTableOutData->maxRetrans;
   LOG_PRINT(DEBUG,"sysInfo4->maxRetans = %d",sysInfo->maxRetans);

   /* fill in ec */
   sysInfo->ec = (I_U8)siPreconfigTableOutData->ec;
   LOG_PRINT(DEBUG,"sysInfo4->ec = %d",sysInfo->ec);

   /* fill in access class */
   tvar1 = cellTableOutData->accessCtrlClass;
   for(i = 0 ; i < ACCESS_CLASS_LEN ; i++)
   {
      sysInfo->acClass[i] = tvar1 & 0x01;
      tvar1 = tvar1>>1;
      LOG_PRINT(DEBUG,"sysInfo4->acClass[%d] = %d", i, sysInfo->acClass[i]);
   }	  

   /* fill in OptionalSelectionparam */ 
   sysInfo->OptionalSelectionParameters = PRESENT;
   LOG_PRINT(DEBUG,"sysInfo4->OptionalSelectionParameters = %d",sysInfo->OptionalSelectionParameters);

   if ( sysInfo->OptionalSelectionParameters == PRESENT )
   {
      /* fill in CBQ */
     //Changes for CBQ on CELLBARRED
      if(oprStateAInterface == ENABLED)
        sysInfo->CBQ = (I_U8)cellTableOutData->cbq;
      else
        sysInfo->CBQ = 0; 
      LOG_PRINT(DEBUG,"sysInfo4->CBQ                  = %d", sysInfo->CBQ);

      /* fill in CELL RESELECT OFFSET */
      sysInfo->CELL_RESELECT_OFFSET = (I_U8)cellTableOutData->cellReselectOffset;
      LOG_PRINT(DEBUG,"sysInfo4->CELL_RESELECT_OFFSET = %d",sysInfo->CELL_RESELECT_OFFSET);

      /* fill in Temporaray Offset */
      sysInfo->TEMPORARY_OFFSET = (I_U8)cellTableOutData->tempOffset;
      LOG_PRINT(DEBUG,"sysInfo4->TEMPORARY_OFFSET     = %d",sysInfo->TEMPORARY_OFFSET);

      /* fill in PENALTY TIME */
      sysInfo->PENALTY_TIME = (I_U8)cellTableOutData->penalityTime;
      LOG_PRINT(DEBUG,"sysInfo4->PENALTY_TIME         = %d",sysInfo->PENALTY_TIME);
   }

   /* Set PowerOffsetSelection Option */
   sysInfo->PowerOffsetSelection = PRESENT;
   LOG_PRINT(DEBUG,"sysInfo4->PowerOffsetSelection         = %d",sysInfo->PowerOffsetSelection);

   if ( sysInfo->PowerOffsetSelection == PRESENT )
   {
      /* fill in PowerOffset */
      sysInfo->PowerOffset = (I_U8)cellTableOutData->powerOffset;
      LOG_PRINT(DEBUG,"sysInfo4->PowerOffset         = %d",sysInfo->PowerOffset);
   }

   /* fill in GPRSIndicator */

      /* Changes for PCU R2.5 : Starts*/
   /*
   if(cellTableOutData->psStatus == 1)
      sysInfo->GPRSIndicator = PRESENT;

   else
   */

   sysInfo->GPRSIndicator = NOT_PRESENT;
      /* Changes for PCU R2.5 : End*/
   LOG_PRINT(DEBUG,"sysInfo4->GPRSIndicator = %d",sysInfo->GPRSIndicator);
   /* Mantis 13890 changes start */
#if 0
   if(sysInfo->GPRSIndicator == PRESENT)
   {
      psCellTableInData.cellId = cellId;
      psCellTableInData.lac = lac;
      errCode = getPsCellTable(&psCellTableInData, &psCellTableOutData);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from PS Cell Table For SI4 : err = %s", clib_strerror(errCode));
         DalocOrdBuf(sysInfo);
         free(cellTableOutData);
         free(bssTableOutData);   
         free(siPreconfigTableOutData);
         return errCode;
      }	   
      /* fill in RA_COLOUR */
      sysInfo->RA_COLOUR = (I_U8)psCellTableOutData->raColour;
      LOG_PRINT(DEBUG,"sysInfo4->RA_COLOUR = %d",sysInfo->RA_COLOUR);
      /* fill in SI13Position */
      sysInfo->SI13Position = (I_U8)siPreconfigTableOutData->si13Position;
      LOG_PRINT(DEBUG,"sysInfo4->SI13Position = %d",sysInfo->SI13Position);
      free(psCellTableOutData);
   }
#endif
   /* Mantis 13890 changes ends */

   /* fill in BreakIndicator */
   sysInfo->BreakIndicator = (I_U8)siPreconfigTableOutData->breakIndicator;
   LOG_PRINT(DEBUG,"sysInfo4->BreakIndicator = %d",sysInfo->BreakIndicator);
   EncodeSysInformation4_cbch(sysInfo,buff,bufLen);
   LOG_PRINT(DEBUG,"Printing Encoded System Information 4 message buffer");
   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));
   /* free memory allocated */
   free(cellTableOutData);
   free(bssTableOutData);   
   free(siPreconfigTableOutData);
   DalocOrdBuf(sysInfo);
   return errCode;/* will be success */

}

/***********************************************************************************
*  Function Name   : PrepareSysInformation5
*
*  Args            : 1. cell id
*                    2. lac
*		     3. buff
*                    4. bufLen
*                    5. arfcn
*                    6. length 
*                    7. baInd
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will FILL the SystemInfo5 structure 
***********************************************************************************/
I_S32 PrepareSysInformation5 ( I_U32 cellId , I_U32 lac,
                               I_U8 * buff , I_U16 * bufLen,
                               I_U16 arfcn[], I_U32 setLen, I_U8 baInd )
{
   I_U32 i       = 0; 
   I_U32 temp    = 0;	/* To Store Temporarily Value Of ARFCN */
   I_U32 band    = 0;	/* Invalid Value Provided */
   I_S32 index   = 0;
   I_S32 range   = 0;
   I_S32 errCode = 0;
   I_S32 nW[NW_LEN];
   I_S32 set[ARFCN_LEN];

   SystemInfo5 *sysInfo = (SystemInfo5 *)AlocOrdBuf(sizeof(SystemInfo5));

    /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo5));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo5 structure");
      return errCode;
   }

   /* initializing arfcn array to zero */
   memset(set, 0, sizeof(I_S32)*ARFCN_LEN);

   /* Get the frequency band of serving cell */
   errCode = getFrequencyBandFromCellTable(cellId, lac, &band);
   if ( errCode != CLIB_SUCCESS )
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from cell Table for SI5: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }

   /*  value of ARFCNs  from  Neighbour Cell*/
   for ( i = 0; i < setLen; i++)
      set[i] = arfcn[i]; 
  
   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG; 
   LOG_PRINT(DEBUG,"sysInfo5->protocolDiscriminator = %d",sysInfo->protocolDiscriminator); 

   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR;
   LOG_PRINT(DEBUG,"sysInfo5->skipIndicator         = %d",sysInfo->skipIndicator); 
  
   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_05;
   LOG_PRINT(DEBUG,"sysInfo5->messageType           = %d",sysInfo->messageType); 
   
   /* fill in formatIndicator */
   if (( band == GSM850) || (band == GSM1800) || (band == GSM1900))   
   {	 
      strcpy((char *)sysInfo->formatIndicator,"range512format");
      LOG_PRINT(DEBUG,"sysInfo5->formatIndicator       = %s",sysInfo->formatIndicator);
      if (setLen > 0)
      { 
         memset(nW, 0, sizeof(I_S32)*NW_LEN);  
  
         index = BITMAP_512_INDEX;
         range = BITMAP_512_RANGE;  
         sysInfo->origARFCN = set[0]; /* original ARFCN */

         LOG_PRINT(DEBUG,"sysInfo5->origARFCN = %d",sysInfo->origARFCN);

         for ( i = 1 ; i < setLen ; i++)
            set[i-1] = set[i] - ( sysInfo->origARFCN + 1); 

         Encode_san(index, set, setLen - 1, range, nW);

         sysInfo->w1 = nW[0];
         sysInfo->w2 = nW[1];
         sysInfo->w3 = nW[2];
         sysInfo->w4 = nW[3];
         sysInfo->w5 = nW[4];
         sysInfo->w6 = nW[5];
         sysInfo->w7 = nW[6];
         sysInfo->w8 = nW[7];
         sysInfo->w9 = nW[8];
         sysInfo->w10 = nW[9];
         sysInfo->w11 = nW[10];
         sysInfo->w12 = nW[11];
         sysInfo->w13 = nW[12];
         sysInfo->w14 = nW[13];
         sysInfo->w15 = nW[14];
         sysInfo->w16 = nW[15];
         sysInfo->w17 = nW[16];

         LOG_PRINT(DEBUG,"sysInfo5->w1  = %d",sysInfo->w1);
         LOG_PRINT(DEBUG,"sysInfo5->w2  = %d",sysInfo->w2);
         LOG_PRINT(DEBUG,"sysInfo5->w3  = %d",sysInfo->w3);
         LOG_PRINT(DEBUG,"sysInfo5->w4  = %d",sysInfo->w4);
         LOG_PRINT(DEBUG,"sysInfo5->w5  = %d",sysInfo->w5);
         LOG_PRINT(DEBUG,"sysInfo5->w6  = %d",sysInfo->w6);
         LOG_PRINT(DEBUG,"sysInfo5->w7  = %d",sysInfo->w7);
         LOG_PRINT(DEBUG,"sysInfo5->w8  = %d",sysInfo->w8);
         LOG_PRINT(DEBUG,"sysInfo5->w9  = %d",sysInfo->w9);
         LOG_PRINT(DEBUG,"sysInfo5->w10 = %d",sysInfo->w10);
         LOG_PRINT(DEBUG,"sysInfo5->w11 = %d",sysInfo->w11);
         LOG_PRINT(DEBUG,"sysInfo5->w12 = %d",sysInfo->w12);
         LOG_PRINT(DEBUG,"sysInfo5->w13 = %d",sysInfo->w13);
         LOG_PRINT(DEBUG,"sysInfo5->w14 = %d",sysInfo->w14);
         LOG_PRINT(DEBUG,"sysInfo5->w15 = %d",sysInfo->w15);
         LOG_PRINT(DEBUG,"sysInfo5->w16 = %d",sysInfo->w16);
         LOG_PRINT(DEBUG,"sysInfo5->w17 = %d",sysInfo->w17);
      } 
   }
   /* making list of frequencies for Bitmap 0 format*/
   else if ( band == GSM900)
   {
			if(((arfcn[0] >= 975) && (arfcn[0] <= 1023))) 
				/* &&((cellTableOutData->bcchArfcn >= 975) && (cellTableOutData->bcchArfcn <= 1023)))*/
			{
      	LOG_PRINT(DEBUG,"Inside range1024format"); 
      	strcpy((char *)sysInfo->formatIndicator,"range1024format");
         if(arfcn[0]>0) sysInfo->f1 = arfcn[0]; else sysInfo->f1 = -1;
         if(arfcn[1]>0) sysInfo->f2 = arfcn[1]; else sysInfo->f2 = -1;
         if(arfcn[2]>0) sysInfo->f3 = arfcn[2]; else sysInfo->f3 = -1;
         if(arfcn[3]>0) sysInfo->f4 = arfcn[3]; else sysInfo->f4 = -1;
         if(arfcn[4]>0) sysInfo->f5 = arfcn[4]; else sysInfo->f5 = -1;
         if(arfcn[5]>0) sysInfo->f6 = arfcn[5]; else sysInfo->f6 = -1;
         if(arfcn[6]>0) sysInfo->f7 = arfcn[6]; else sysInfo->f7 = -1;
         if(arfcn[7]>0) sysInfo->f8 = arfcn[7]; else sysInfo->f8 = -1;
         if(arfcn[8]>0) sysInfo->f9 = arfcn[8]; else sysInfo->f9 = -1;
         if(arfcn[9]>0) sysInfo->f10 = arfcn[9]; else sysInfo->f10 = -1;
         if(arfcn[10]>0) sysInfo->f11 = arfcn[10]; else sysInfo->f11 = -1;
         if(arfcn[11]>0) sysInfo->f12 = arfcn[11]; else sysInfo->f12 = -1;
         if(arfcn[12]>0) sysInfo->f13 = arfcn[12]; else sysInfo->f13 = -1;
         if(arfcn[13]>0) sysInfo->f14 = arfcn[13]; else sysInfo->f14 = -1;
         if(arfcn[14]>0) sysInfo->f15 = arfcn[14]; else sysInfo->f15 = -1;
         if(arfcn[15]>0) sysInfo->f16 = arfcn[15]; else sysInfo->f16 = -1;
			}
			else
			{
      strcpy((char *)sysInfo->formatIndicator,"bitmap0format");
      LOG_PRINT(DEBUG,"sysInfo5->formatIndicator       = %s",sysInfo->formatIndicator); 
     
      memset(sysInfo->ARFCN, 0, sizeof(I_U8)*BITMAP_ZERO_LEN);
 
      for (i = 0 ; i < setLen ; i++)
      {
         if ((arfcn[i] > 0) && (arfcn[i] <= BITMAP_ZERO_LEN))
         {
            temp = arfcn[i];
      	    sysInfo->ARFCN[temp - 1] = ONE;
            LOG_PRINT(DEBUG,"sysInfo5->ARFCN[%d] = %d",temp - 1, sysInfo->ARFCN[temp - 1]);
         }
      } 
      } 
   }
   else if (( band != GSM850) && (band != GSM1800) && (band != GSM1900) && (band != GSM900))
   {
      LOG_PRINT(CRITICAL,"Invalid Band : %d" ,band);
      DalocOrdBuf(sysInfo); 
      errCode = ONE;
      return errCode;
   }
  
   /* fill in ba_ind (fixed to zero)*/
   sysInfo->ba_ind = baInd;
   LOG_PRINT(DEBUG,"sysInfo5->ba_ind = %d",sysInfo->ba_ind);

   /* fill in ext ind (fixed to zero)*/
   sysInfo->ext_ind = COMPLETE_BA;
   LOG_PRINT(DEBUG,"sysInfo5->ext_ind = %d",sysInfo->ext_ind);

   EncodeSysInformation5(sysInfo,buff,bufLen);

   LOG_PRINT(DEBUG,"Printing Encoded System Information 5 message buffer");

   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));
   /* free memory allocated */
   DalocOrdBuf(sysInfo);
   return errCode;/* will be success */
}

/***********************************************************************************
*  Function Name   : PrepareSysInformation5ter
*
*  Args            : 1. cell id
*                    2. lac
*                    3. buff
*                    4. bufLen
*                    5. arfcn
*                    6. length
*                    7. baInd
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will FILL the SystemInfo5ter structure 
***********************************************************************************/

I_S32 PrepareSysInformation5ter ( I_U32 cellId, I_U32 lac,
                                  I_U8 * buff, I_U16 * bufLen,
                                  I_U16 arfcn[], I_U32 setLen, I_U8 baInd )
{
   I_U32 i       = 0; 
   I_U32 temp    = 0;	/* To Store Temporarily Value Of ARFCN */
   I_U32 band    = 0;	/* Invalid Value Provided */
   I_S32 index   = 0;
   I_S32 range   = 0;
   I_S32 errCode = 0;
   I_U8 mulbandReporting;
   I_S32 nW[NW_LEN];
   I_S32 set[ARFCN_LEN];

   SystemInfo5ter *sysInfo = (SystemInfo5ter *)AlocOrdBuf(sizeof(SystemInfo5ter));

   /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo5ter));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo5ter structure");
      return errCode;
   }

   /* initializing arfcn array to zero */
   memset(set,0,sizeof(I_S32)*ARFCN_LEN);
  
   /* Get the frequency band of serving cell */
   errCode = getFrequencyBandFromCellTable(cellId, lac, &band);
   if ( errCode != CLIB_SUCCESS )
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI5ter: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }
   
   switch(band)
   {
      case GSM900 : band = GSM1800;
      break;

      case GSM1800 : band = GSM900;
      break;
   
      case GSM850 : band = GSM1900;
      break;

      case GSM1900 : band = GSM850;
      break;
   
      default: LOG_PRINT(CRITICAL,"Invalid value of Band : %d",band);
      DalocOrdBuf(sysInfo); 
      errCode = ONE;
      return errCode;
   } 

   /* Get the value of multiband reporting */
   errCode = getMultibandReportingFromHoCtrlTable(cellId, lac, &mulbandReporting);
   if ( errCode != CLIB_SUCCESS )
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from HoCtrl Table for SI5ter: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      return errCode;
   }

   /* Get the ARFCN's list */
   for ( i = 0 ; i < setLen ; i++)
      set[i] = arfcn[i];
  
   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG; 
   LOG_PRINT(DEBUG,"sysInfo5ter->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);

   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR; 
   LOG_PRINT(DEBUG,"sysInfo5ter->skipIndicator         = %d",sysInfo->skipIndicator); 

   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_05ter;
   LOG_PRINT(DEBUG,"sysInfo5ter->messageType           = %d",sysInfo->messageType);

   /* fill in formatIndicator */
   if (( band == GSM850) || (band == GSM1800) || (band == GSM1900))
   {	 
      strcpy((char *)sysInfo->formatIndicator,"range512format");
      LOG_PRINT(DEBUG,"sysInfo5ter->formatIndicator    = %s",sysInfo->formatIndicator);
      if (setLen > 0)
      {
         memset(nW, 0, sizeof(I_S32)*NW_LEN);

         index = BITMAP_512_INDEX;
         range = BITMAP_512_RANGE;  

         sysInfo->origARFCN = set[0]; /* original ARFCN */
         LOG_PRINT(DEBUG,"sysInfo5ter->origARFCN = %d",sysInfo->origARFCN);

         for(i = 1 ; i< setLen ; i++)
            set[i-1] = set[i] - (sysInfo->origARFCN + 1); 

         Encode_san(index, set, setLen - 1, range, nW);

         sysInfo->w1 = nW[0];
         sysInfo->w2 = nW[1];
         sysInfo->w3 = nW[2];
         sysInfo->w4 = nW[3];
         sysInfo->w5 = nW[4];
         sysInfo->w6 = nW[5];
         sysInfo->w7 = nW[6];
         sysInfo->w8 = nW[7];
         sysInfo->w9 = nW[8];
         sysInfo->w10 = nW[9];
         sysInfo->w11 = nW[10];
         sysInfo->w12 = nW[11];
         sysInfo->w13 = nW[12];
         sysInfo->w14 = nW[13];
         sysInfo->w15 = nW[14];
         sysInfo->w16 = nW[15];
         sysInfo->w17 = nW[16];

         LOG_PRINT(DEBUG,"sysInfo5ter->w1  = %d",sysInfo->w1);
         LOG_PRINT(DEBUG,"sysInfo5ter->w2  = %d",sysInfo->w2);
         LOG_PRINT(DEBUG,"sysInfo5ter->w3  = %d",sysInfo->w3);
         LOG_PRINT(DEBUG,"sysInfo5ter->w4  = %d",sysInfo->w4);
         LOG_PRINT(DEBUG,"sysInfo5ter->w5  = %d",sysInfo->w5);
         LOG_PRINT(DEBUG,"sysInfo5ter->w6  = %d",sysInfo->w6);
         LOG_PRINT(DEBUG,"sysInfo5ter->w7  = %d",sysInfo->w7);
         LOG_PRINT(DEBUG,"sysInfo5ter->w8  = %d",sysInfo->w8);
         LOG_PRINT(DEBUG,"sysInfo5ter->w9  = %d",sysInfo->w9);
         LOG_PRINT(DEBUG,"sysInfo5ter->w10 = %d",sysInfo->w10);
         LOG_PRINT(DEBUG,"sysInfo5ter->w11 = %d",sysInfo->w11);
         LOG_PRINT(DEBUG,"sysInfo5ter->w12 = %d",sysInfo->w12);
         LOG_PRINT(DEBUG,"sysInfo5ter->w13 = %d",sysInfo->w13);
         LOG_PRINT(DEBUG,"sysInfo5ter->w14 = %d",sysInfo->w14);
         LOG_PRINT(DEBUG,"sysInfo5ter->w15 = %d",sysInfo->w15);
         LOG_PRINT(DEBUG,"sysInfo5ter->w16 = %d",sysInfo->w16);
         LOG_PRINT(DEBUG,"sysInfo5ter->w17 = %d",sysInfo->w17);
      }    
   }
   /* making list of frequencies for Bitmap 0 format*/
   else if (band == GSM900)
   {
			if(((arfcn[0] >= 975) && (arfcn[0] <= 1023))) 
				/* &&((cellTableOutData->bcchArfcn >= 975) && (cellTableOutData->bcchArfcn <= 1023)))*/
			{
      	LOG_PRINT(DEBUG,"Inside range1024format"); 
      	strcpy((char *)sysInfo->formatIndicator,"range1024format");
         if(arfcn[0]>0) sysInfo->f1 = arfcn[0]; else sysInfo->f1 = -1;
         if(arfcn[1]>0) sysInfo->f2 = arfcn[1]; else sysInfo->f2 = -1;
         if(arfcn[2]>0) sysInfo->f3 = arfcn[2]; else sysInfo->f3 = -1;
         if(arfcn[3]>0) sysInfo->f4 = arfcn[3]; else sysInfo->f4 = -1;
         if(arfcn[4]>0) sysInfo->f5 = arfcn[4]; else sysInfo->f5 = -1;
         if(arfcn[5]>0) sysInfo->f6 = arfcn[5]; else sysInfo->f6 = -1;
         if(arfcn[6]>0) sysInfo->f7 = arfcn[6]; else sysInfo->f7 = -1;
         if(arfcn[7]>0) sysInfo->f8 = arfcn[7]; else sysInfo->f8 = -1;
         if(arfcn[8]>0) sysInfo->f9 = arfcn[8]; else sysInfo->f9 = -1;
         if(arfcn[9]>0) sysInfo->f10 = arfcn[9]; else sysInfo->f10 = -1;
         if(arfcn[10]>0) sysInfo->f11 = arfcn[10]; else sysInfo->f11 = -1;
         if(arfcn[11]>0) sysInfo->f12 = arfcn[11]; else sysInfo->f12 = -1;
         if(arfcn[12]>0) sysInfo->f13 = arfcn[12]; else sysInfo->f13 = -1;
         if(arfcn[13]>0) sysInfo->f14 = arfcn[13]; else sysInfo->f14 = -1;
         if(arfcn[14]>0) sysInfo->f15 = arfcn[14]; else sysInfo->f15 = -1;
         if(arfcn[15]>0) sysInfo->f16 = arfcn[15]; else sysInfo->f16 = -1;
			}
			else
			{
      strcpy((char *)sysInfo->formatIndicator,"bitmap0format");
      LOG_PRINT(DEBUG,"sysInfo5ter->formatIndicator    = %s",sysInfo->formatIndicator);
 
      memset(sysInfo->ARFCN, 0, sizeof(I_U8)*BITMAP_ZERO_LEN);
      
      for (i = 0 ; i < setLen ; i++)
      {
         if (( arfcn[i] > 0) && (arfcn[i] <= BITMAP_ZERO_LEN))
         {
            temp = arfcn[i];
      	    sysInfo->ARFCN[temp - 1] = 1;
            LOG_PRINT(DEBUG,"sysInfo5ter->ARFCN[%d] = %d", temp -1 ,sysInfo->ARFCN[temp - 1]);
         }
      }
			} 
   }
   else
   {
      LOG_PRINT(CRITICAL,"Invalid Band : %d" ,band);
      DalocOrdBuf(sysInfo); 
      errCode = ONE;
      return errCode;
   }

   /* fill in ba_ind (fixed to zero)*/
   sysInfo->baInd = baInd;
   LOG_PRINT(DEBUG,"sysInfo5ter->baInd              = %d",sysInfo->baInd);
	   
   /* fill in multiband reporting */
   sysInfo->multibandReporting = mulbandReporting;
   LOG_PRINT(DEBUG,"sysInfo5ter->multibandReporting = %d",sysInfo->multibandReporting);

   EncodeSysInformation5ter(sysInfo,buff,bufLen);

   LOG_PRINT(DEBUG,"Printing Encoded System Information 5ter message buffer");

   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));

   /* free memory allocated */
   DalocOrdBuf(sysInfo);
   return errCode;/* will be success */
}

/***********************************************************************************
*  Function Name   : PrepareSysInformation6
*
*  Args            : 1. cell id
*                    2. lac
*                    3. bsc id
*                    4. buff
*                    5. bufLen
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will FILL the SystemInfo6 structure 
***********************************************************************************/
I_S32 PrepareSysInformation6(I_U32 cellId, I_U32 lac, I_U32 bscId, I_U8 * buff , I_U16 * bufLen)
{
       
   I_U32 tvar2 = 0; 
   I_U32 i = 0; 
   I_S32 errCode = 1;
   I_U32 outRows = 0;
   I_U16 outSize = 0;
   CellTableApi * cellTableOutData ;
   BssTableApi * bssTableOutData;
   SiPreconfigTableApi * siPreconfigTableOutData;
   CellTableIndices  cellTableInData;
   BssTableIndices  bssTableInData;
   SystemInfo6 *sysInfo = (SystemInfo6 *)AlocOrdBuf(sizeof(SystemInfo6));
    /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo6));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo6 structure");
      return errCode;
   }

   /* Get the data needed from the Db */
   cellTableInData.cellId = cellId;
   cellTableInData.lac = lac;
   errCode = getCellTable(&cellTableInData, &cellTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI6: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo); 
      return errCode;
   }
  
   bssTableInData.bscId = bscId;
   errCode = getBssTable(&bssTableInData, &bssTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from BSS Table for SI6: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      return errCode;
   }

   errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
   if ((errCode != CLIB_SUCCESS)||(outRows < 1))
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI6: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);   
      return errCode;
   }

   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG; 
   LOG_PRINT(DEBUG,"sysInfo6->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);
   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR; 
   LOG_PRINT(DEBUG,"sysInfo6->skipIndicator = %d",sysInfo->skipIndicator);

   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_06;
   LOG_PRINT(DEBUG,"sysInfo6->messageType = %d",sysInfo->messageType);

   /* fill in cell identity */
   sysInfo->cellIdentity = cellTableOutData->cellId;
   LOG_PRINT(DEBUG,"sysInfo6->cellIdentity = %d",sysInfo->cellIdentity);
        
   /* fill in mobileCC */
   sysInfo->mobileCC = bssTableOutData->mcc;
   LOG_PRINT(DEBUG,"sysInfo6->mobileCC = %d",sysInfo->mobileCC);
	
   /* fill in mobileNC */
   sysInfo->mobileNC = bssTableOutData->mnc;
   LOG_PRINT(DEBUG,"sysInfo6->mobileNC = %d",sysInfo->mobileNC);

   /* fill in locationAreaCode */
   sysInfo->locationAreaCode = cellTableOutData->lac;
   LOG_PRINT(DEBUG,"sysInfo6->locationAreaCode = %d",sysInfo->locationAreaCode);
	
   /* fill in radio_link_timeout */
   sysInfo->radio_link_timeout = (I_U8)bssTableOutData->radioLinkTimeout;
   LOG_PRINT(DEBUG,"sysInfo6->radio_link_timeout = %d",sysInfo->radio_link_timeout);

   /* fill in dtx */
   sysInfo->dtx = (I_U8)bssTableOutData->dtxUpLinkInd;
   LOG_PRINT(DEBUG,"sysInfo6->dtx = %d",sysInfo->dtx);

   /* fill in pwrc (its value should be zero as BCCH is not part of hopping system)*/
   sysInfo->pwrc = (I_U8)siPreconfigTableOutData->pwrc;
   LOG_PRINT(DEBUG,"sysInfo6->pwrc = %d",sysInfo->pwrc);

   /* ##### not present in cell options SAACH #####
   sysInfo->dnInd = (I_U8)siPreconfigTableOutData->dnInd;
   LOG_PRINT(DEBUG,"sysInfo6->dnInd = %d",sysInfo->dnInd); */

   /* fill in NCC */
   tvar2 = bssTableOutData->nccPermitted;
    
   for(i = 0 ; i < NCC_LEN ; i++)
   {
      sysInfo->NCC[i] = tvar2 & 0x01;
      tvar2 = tvar2>>1;
      LOG_PRINT(DEBUG,"sysInfo6->NCC[%d] = %d",i,sysInfo->NCC[i]);
   }

   /* #####No Need to fill in in PCh NCh Info(needs to be encoded as L in CS2)##### */
   /*sysInfo->pchAndNchInfo = (I_U8)siPreconfigTableOutData->pchAndNchInfo;*/ 
		
   LOG_PRINT(DEBUG,"PCH NCH is encoded as L"); 
   /* fill in vbs/vgcs options(needs to be encoded as L in CS2) */
   /*sysInfo->vbsVgcsOptions = (I_U8)siPreconfigTableOutData->vbsVgcsOptions;*/
   LOG_PRINT(DEBUG,"VBS VGCS OPTIONS is encoded as L"); 
   /*fill in dtm support(DTM support is encoded as L) 
   sysInfo->DTM_Support = (I_U8)siPreconfigTableOutData->dtmSupport;
   LOG_PRINT(DEBUG,"sysInfo6->DTM_Support = %d",sysInfo->DTM_Support); */
   LOG_PRINT(DEBUG,"DTM_Support is encoded as L"); 

   /* fill in RAC */
   /*sysInfo->RAC = (I_U8)psCellTableOutData->rac;
   LOG_PRINT(DEBUG,"sysInfo6->RAC = %d",sysInfo->RAC);
   */
   /*fill in maxLapdm*/
   /*sysInfo->MAX_LAPDm = (I_U8)siPreconfigTableOutData->maxLapdm;
   LOG_PRINT(DEBUG,"sysInfo6->MAX_LAPDm = %d",sysInfo->MAX_LAPDm);
   */
   /* fill in band indicator */
   sysInfo->Band_Indicator = (I_U8)cellTableOutData->freqBandBcch;
   LOG_PRINT(DEBUG,"sysInfo6->Band_Indicator = %d",sysInfo->Band_Indicator);
	
   /* fill in gprsMsTxpwrMaxCch(is not present so should be encoded as L)*/
   /* sysInfo->GPRS_MS_TXPWR_MAX_CCCH = (I_U8)siPreconfigTableOutData->gprsMsTxpwrMaxCch;
   LOG_PRINT(DEBUG,"sysInfo6->GPRS_MS_TXPWR_MAX_CCCH = %d",sysInfo->GPRS_MS_TXPWR_MAX_CCCH);*/
   LOG_PRINT(DEBUG,"GPRS_MS_TXPWR_MAX_CCCH is encoded as L");

   EncodeSysInformation6(sysInfo,buff,bufLen);
   LOG_PRINT(DEBUG,"Printing Encoded System Information 6 message buffer");
   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));
/* free memory allocated */
   free(cellTableOutData);
   free(bssTableOutData);   
   free(siPreconfigTableOutData);
   DalocOrdBuf(sysInfo);
   return errCode;/* will be success */
}
/***********************************************************************************
*  Function Name   : PrepareSysInformation13
*
*  Args            : 1. cell id
*                    2. lac
*                    3. bsc id
*                    4. buff
*                    5. buffLen
*                    6. pbcchPres
*                    7. egprsPresent 
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will FILL the SystemInfo13 structure 
***********************************************************************************/

I_S32 PrepareSysInformation13 ( I_U32 cellId, I_U32 lac, I_U32 bscId,
                                I_U8 * buff, I_U16 * bufLen,
                                I_U8 pbcchPres, I_U8 tsc, I_U8 tn, I_U16 arfcn,I_U8 egprsPresent)
{
   I_S32 errCode = 1;
   I_U32 outRows = 0;
   I_U16 outSize = 0;

   CellTableApi * cellTableOutData ;
   PsCellTableApi * psCellTableOutData ;
   BssTableApi * bssTableOutData;
   SiPreconfigTableApi * siPreconfigTableOutData;
   BssPsPreConfigTableApi * bssPsPreConfigTableOutData;
   CellTableIndices  cellTableInData;
   PsCellTableIndices  psCellTableInData;
   BssTableIndices  bssTableInData;
   BssPsTableApi  *bssPsTableOutData;
   SystemInfo13 *sysInfo = (SystemInfo13 *)AlocOrdBuf(sizeof(SystemInfo13));
    /* Initialize to zero*/
   if(sysInfo != NULL)
      memset(sysInfo,0,sizeof(SystemInfo13));
   else
   {
      LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo13 structure");
      return errCode;
   }
 
   /* Get the data needed from the Db */
   cellTableInData.cellId = cellId;
   cellTableInData.lac = lac;
   errCode = getCellTable(&cellTableInData, &cellTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI13: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo); 
      return errCode;
   }
  
   bssTableInData.bscId = bscId;
   errCode = getBssTable(&bssTableInData, &bssTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from BSS Table for SI13: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      return errCode;
   }

   errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
   if ((errCode != CLIB_SUCCESS)||(outRows < 1))
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI13: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);   
      return errCode;
   }

   outRows = 0;
   errCode = getallBssPsPreConfigTable(&bssPsPreConfigTableOutData, &outRows , &outSize);
   if ((errCode != CLIB_SUCCESS)||(outRows < 1))
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from BSS PS Preconfig Table for SI13: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);   
      free(siPreconfigTableOutData);
      return errCode;
   } 

   psCellTableInData.cellId = cellId;
   psCellTableInData.lac = lac;
   errCode = getPsCellTable(&psCellTableInData, &psCellTableOutData);
   if (errCode != CLIB_SUCCESS)
   {
      LOG_PRINT(CRITICAL, "Retrieval failed from PS Cell Table for SI13: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);   
      free(siPreconfigTableOutData);
      free(bssPsPreConfigTableOutData);
      return errCode;
   }

/*Changes for PCU R2.5 : Starts*/
   outRows = 0;
   errCode = getallBssPsTable(&bssPsTableOutData, &outRows , &outSize);
   if ((errCode != CLIB_SUCCESS)||(outRows > 1))
   {
      LOG_PRINT(CRITICAL, "Retrieval failed BssPsTable for SI13: err = %s", clib_strerror(errCode));
      DalocOrdBuf(sysInfo);
      free(cellTableOutData);
      free(bssTableOutData);   
      free(siPreconfigTableOutData);
      free(bssPsPreConfigTableOutData);
      free(psCellTableOutData);
      return errCode;
   }
/*Changes for PCU R2.5 : End*/

   /* fill protocol discriminator */
   sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG;
   LOG_PRINT(DEBUG,"sysInfo13->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);
   
   /* fill protocol discriminator */
   sysInfo->skipIndicator = SKIP_INDICATOR;
   LOG_PRINT(DEBUG,"sysInfo13->skipIndicator = %d",sysInfo->skipIndicator); 
   
   /* fill protocol discriminator*/
   sysInfo->messageType = MSG_SYS_INFO_13;
   LOG_PRINT(DEBUG,"sysInfo13->messageType = %d",sysInfo->messageType); 
   
   /* #####fill in BCCH CHANGE MARK#####(not required in CS2 )*/ 
   /*sysInfo->bcchChangeMark = (I_U8)cellTableOutData->bcchChangeMark;*/
   sysInfo->bcchChangeMark = (I_U8)BCCH_CHANGE_MARK_ZERO;
   LOG_PRINT(DEBUG,"sysInfo13->bcchChangeMark = %d",sysInfo->bcchChangeMark);
 
   /*#####fill in SI change field(not required in CS2 )#####*/
   /*sysInfo->siChangeField = (I_U8)cellTableOutData->siChangeField;*/
   sysInfo->siChangeField = (I_U8)SI_CHANGE_FIELD_ZERO;
   LOG_PRINT(DEBUG,"sysInfo13->siChangeField = %d",sysInfo->siChangeField); 
   
   /* #####  GPRS Mobile Allocation function is not present as PBCCH is not hopping in CS2.....(L) ##### */
   sysInfo->gprsMobileAllocation = NOT_PRESENT;
   LOG_PRINT(DEBUG,"sysInfo13->gprsMobileAllocation = %d",sysInfo->gprsMobileAllocation);
   
   /*if(psCellTableOutData->pbcchPres && hoppingAllowed)
      sysInfo->gprsMobileAllocation = 1;
   else
      sysInfo->gprsMobileAllocation = 0;
*/
  /* if(gprsMobileAllocation != 0)
   {
      sysInfo->si13ChangeMark = (I_U8)psCellTableOutData->si13ChangeMark;
      
      sysInfo->hsn = (I_U8)radioTimeslotTableOutData->hsn;
     */ 
      /* #####rflList is not used#####*/
      
      /* #####  maLength and maBitmap not used ##### */
   /*}*/
  
   if(!pbcchPres)
   {
      sysInfo->rac = psCellTableOutData->rac; /* changed to PSCellTable from RATable*/
      LOG_PRINT(DEBUG,"sysInfo13->rac = %d",sysInfo->rac); 
      sysInfo->spgcCcchSup = SPGC_CCCH_SUP;/*Changed for PCU R2.5*/
      LOG_PRINT(DEBUG,"sysInfo13->spgcCcchSup = %d",sysInfo->spgcCcchSup);
      sysInfo->priorityAccessThr = (I_U8)psCellTableOutData->priorityAccessThr;
      LOG_PRINT(DEBUG,"sysInfo13->priorityAccessThr = %d",sysInfo->priorityAccessThr); 
      sysInfo->networkControlOrder = NETWORK_CONTROL_ORDER;/*Changed for PCU R2.5*/
      LOG_PRINT(DEBUG,"sysInfo13->networkControlOrder = %d",sysInfo->networkControlOrder); 
      /* GPRS Cell Options */
      sysInfo->nmo = (I_U8)bssPsTableOutData->nmo;/*Changed for PCU R2.5*/
      LOG_PRINT(DEBUG,"sysInfo13->nmo = %d",sysInfo->nmo);
      sysInfo->t3168 = (I_U8)bssPsPreConfigTableOutData->t3168;
      LOG_PRINT(DEBUG,"sysInfo13->t3168 = %d",sysInfo->t3168);
      sysInfo->t3192 = (I_U8)bssPsPreConfigTableOutData->t3192;
      LOG_PRINT(DEBUG,"sysInfo13->t3192 = %d",sysInfo->t3192);
      sysInfo->drxTimerMax = (I_U8)bssPsPreConfigTableOutData->drxTimerMax;
      LOG_PRINT(DEBUG,"sysInfo13->drxTimerMax = %d",sysInfo->drxTimerMax);
      sysInfo->accessBurstType = ACCESS_BURST_TYPE;/*Changed for PCU R2.5*/
      LOG_PRINT(DEBUG,"sysInfo13->accessBurstType = %d",sysInfo->accessBurstType);
      sysInfo->controlAckType =  CONTROL_ACK_TYPE;/*Changed for PCU R2.5*/
      LOG_PRINT(DEBUG,"sysInfo13->controlAckType = %d",sysInfo->controlAckType); 
      sysInfo->bsCvMax =   (I_U8)bssPsPreConfigTableOutData->bsCvMax;
      LOG_PRINT(DEBUG,"sysInfo13->bsCvMax = %d",sysInfo->bsCvMax);
      /* Changes for PCU R2.5 : Start*/
      sysInfo->panDec = (I_U8)bssPsPreConfigTableOutData->panDec;/*this param was previously in pscelltable */
      LOG_PRINT(DEBUG,"sysInfo13->panDec = %d",sysInfo->panDec);
      sysInfo->panInc = (I_U8)bssPsPreConfigTableOutData->panInc;
      LOG_PRINT(DEBUG,"sysInfo13->panInc  = %d",sysInfo->panInc);
      sysInfo->panMax = (I_U8)bssPsPreConfigTableOutData->panMax;
      LOG_PRINT(DEBUG,"sysInfo13->panMax = %d",sysInfo->panMax);
      /* Changes for PCU R2.5 : End*/

      /* EGPRS Changes Starts*/
      /* Extension information */
      /* egprsPacketChannelRequest is supported */
      LOG_PRINT(DEBUG,"sysInfo13->egprsPacketChannelRequest = %d",bssPsPreConfigTableOutData->egprsPacketChannelRequest);
      sysInfo->egprsPacketChannelRequest = (I_U8)bssPsPreConfigTableOutData->egprsPacketChannelRequest;
      LOG_PRINT(DEBUG,"sysInfo13->egprsPacketChannelRequest = %d",sysInfo->egprsPacketChannelRequest);
      /* #####need to check bep period##### */
      sysInfo->bepPeriod = (I_U8)bssPsPreConfigTableOutData->bepPeriod;
      LOG_PRINT(DEBUG,"sysInfo13->bepPeriod = %d",sysInfo->bepPeriod);
      /* EGPRS Changes Ends */


      /* Commented in PCU R2.5*/
      /*
      sysInfo->pfcFeatureMode = (I_U8)bssPsPreConfigTableOutData->pfcFeatureMode;
      LOG_PRINT(DEBUG,"sysInfo13->pfcFeatureMode = %d",sysInfo->pfcFeatureMode);
      */
      /* #####need to check dtm support##### */
      sysInfo->dtmSupport = (I_U8)siPreconfigTableOutData->dtmSupport;
      LOG_PRINT(DEBUG,"sysInfo13->dtmSupport = %d",sysInfo->dtmSupport);
      /* Commented in PCU R2.5*/
      /*
      sysInfo->ccnActive = (I_U8)bssPsPreConfigTableOutData->ccnActive;
      LOG_PRINT(DEBUG,"sysInfo13->ccnActive = %d",sysInfo->ccnActive);
      sysInfo->nwExtUtbf = (I_U8)bssPsPreConfigTableOutData->nwExtUtbf;
      LOG_PRINT(DEBUG,"sysInfo13->nwExtUtbf = %d",sysInfo->nwExtUtbf);
      */
      /* #####need to check on bssPaging Coordination##### */
      /* Commented in PCU R2.5*/
      /*
      sysInfo->bssPagingCoordination = (I_U8)bssPsPreConfigTableOutData->bssPagingCoordination;
      LOG_PRINT(DEBUG,"sysInfo13->bssPagingCoordination  = %d",sysInfo->bssPagingCoordination); 
      */
      /* GPRS Power Control Parameter */
      /*Changes for PCU R2.5 : Start*/
      sysInfo->alpha = (I_U8)bssPsPreConfigTableOutData->alpha;
      LOG_PRINT(DEBUG,"sysInfo13->alpha = %d",sysInfo->alpha);
      sysInfo->tAvgW = (I_U8)bssPsTableOutData->tAvgW;
      LOG_PRINT(DEBUG,"sysInfo13->tAvgW = %d",sysInfo->tAvgW);
      sysInfo->tAvgT = (I_U8)bssPsTableOutData->tAvgT;
      LOG_PRINT(DEBUG,"sysInfo13->tAvgT  = %d",sysInfo->tAvgT);
      sysInfo->pcMeasChan = (I_U8)bssPsPreConfigTableOutData->pcMeasChan;
      LOG_PRINT(DEBUG,"sysInfo13->pcMeasChan = %d",sysInfo->pcMeasChan);
      sysInfo->nAvgI = (I_U8)bssPsTableOutData->nAvgI;
      LOG_PRINT(DEBUG,"sysInfo13->nAvgI = %d",sysInfo->nAvgI);
      /*Changes for PCU R2.5 : End*/
   }
 
   else if(pbcchPres) 
   {
      /*Changed for PCU R2.5 : Starts(Code is Commented as Pbcch is not supported)*/
      /*
      sysInfo->psi1RepeatPeriod = (I_U8)psCellTableOutData->psi1RepeatPeriod;  
      LOG_PRINT(DEBUG,"sysInfo13->psi1RepeatPeriod = %d",sysInfo->psi1RepeatPeriod);
      sysInfo->pb = (I_U8)psCellTableOutData->pb;
      LOG_PRINT(DEBUG,"sysInfo13->pb = %d",sysInfo->pb);
      */
      /*Changed for PCU R2.5 : End*/
      sysInfo->tsc = tsc;
      LOG_PRINT(DEBUG,"sysInfo13->tsc  = %d",sysInfo->tsc );
      sysInfo->tn = tn;
      LOG_PRINT(DEBUG,"sysInfo13->tn = %d",sysInfo->tn);
      /* since PBCCH is not hopping, arfcn is present and not maio */
      sysInfo->arfcn = arfcn;
      LOG_PRINT(DEBUG,"sysInfo13->arfcn = %d",sysInfo->arfcn);
//      free(radioTimeslotTableOutData);
   }     
   
   //sysInfo->sgsnr = (I_U8)siPreconfigTableOutData->sgsnRelNum;
   sysInfo->sgsnr = (I_U8)bssPsTableOutData->sgsnr;
   LOG_PRINT(DEBUG,"sysInfo13->sgsnr = %d",sysInfo->sgsnr);
   sysInfo->siStatusInd =PSI_STATUS_IND; /*Changed for PCU R2.5*/
   LOG_PRINT(DEBUG,"sysInfo13->siStatusInd = %d",sysInfo->siStatusInd);
   EncodeSysInformation13(sysInfo,buff,bufLen,pbcchPres,egprsPresent);
   LOG_PRINT(DEBUG,"Printing Encoded System Information 13 message buffer");
   PRINT_HEX_DUMP(DEBUG,buff,(*bufLen));
   /* free memory allocated */
   free(psCellTableOutData);
   free(cellTableOutData);
   free(bssTableOutData);   
   free(siPreconfigTableOutData);
   free(bssPsPreConfigTableOutData);
   free(bssPsTableOutData);      /* PCU R2.5 */
   DalocOrdBuf(sysInfo);
   return errCode;/* will be success */	
}
/* 2G - 3G Handover */
/***********************************************************************************
  *  Function Name   : PrepareSysInformation2quat
  *
  *  Args            : 1. cell id
  *                    2. lac
  *                    3. bsc id
  *                    4. buff
  *                    5. bufLen
  *
  *  Returns         : SUCCESS or  FAILURE.
  *
  *  Task            : This method will FILL the SystemInfo2quat  structure
  ***********************************************************************************/

I_S32 PrepareSysInformation2quat ( I_U32 cellId , I_U32 lac,
                                   I_U8 * buff , I_U16 * bufLen,
                                   I_U16 arfcn[], I_U32 setLen,I_U16 fddInfo[][16], I_U8 innerLength[],
                                   I_U8 baInd , I_U8 baInd3g)
{
  I_S32 index,range;
  I_U32 i =0,n =0,j =0, position =0, k=0;
  I_S32 errCode = 1;
  I_S32 nW[NW_LEN];
  I_S32 set[ARFCN_LEN];
  I_S32 newSet[ARFCN_LEN];
  I_S32 temp = 0;
  I_U32 band;
  I_U16 singleBufLen = 0;
  I_U8 newInnerLen = 0;
  I_U8 zeroPresent = I_FALSE;
  
  HoCtrlTableIndices hoCtrlTableInData;
  HoCtrlTableApi     *hoCtrlTableOutData = NULL;

  LOG_PRINT(DEBUG, "GOYAL: %s : %d : buff=%x, bufLen=%d, setLen=%d", __FILE__, __LINE__, buff, *bufLen, setLen);


  SystemInfo2quat *sysInfo = (SystemInfo2quat *)AlocOrdBuf(sizeof(SystemInfo2quat));

  /* Initialize to zero*/
  if(sysInfo != NULL)
    memset(sysInfo,0,sizeof(SystemInfo2quat));
  else
  {
    LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo2quat structure");
    return errCode;
  }




  /* Get the data needed from the Db */
  hoCtrlTableInData.cellId = cellId;
  hoCtrlTableInData.lac = lac;
  errCode = getHoCtrlTable(&hoCtrlTableInData, &hoCtrlTableOutData);
  if (errCode != CLIB_SUCCESS)
  {
    LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI 2Quat: err = %s", clib_strerror(errCode));
    DalocOrdBuf(sysInfo);
    return errCode;
  }

  /* fill protocol discriminator */
  sysInfo->protocolDiscriminator = RADIO_RESOURCE_MANAGEMENT_MSG;
  LOG_PRINT(DEBUG,"sysInfo2quat->protocolDiscriminator = %d",sysInfo->protocolDiscriminator);

  /* fill protocol discriminator */
  sysInfo->skipIndicator = SKIP_INDICATOR;
  LOG_PRINT(DEBUG,"sysInfo2quat->skipIndicator = %d",sysInfo->skipIndicator);

  /* fill protocol discriminator*/
  sysInfo->messageType = MSG_SYS_INFO_02quat;
  LOG_PRINT(DEBUG,"sysInfo2quat->messageType = %d",sysInfo->messageType);
  /* fill in ba_ind */
  sysInfo->baInd = baInd;
  LOG_PRINT(DEBUG,"sysInfo2quat->baInd = %d",sysInfo->baInd);

  /* fill in ba_ind_3g */
  //sysInfo->baInd3g = baInd3g;
  sysInfo->baInd3g = 1;
  LOG_PRINT(DEBUG,"sysInfo2quat->baInd3g = %d",sysInfo->baInd3g);

  /* fill in mp_change_mark */
  sysInfo->mpChangeMark = MP_CHANGE_MARK;
  LOG_PRINT(DEBUG,"sysInfo2quat->mpChangeMark = %d",sysInfo->mpChangeMark);

  /* fill in q_Search_I */
  sysInfo->qSearch_I = hoCtrlTableOutData->qSearch_I;
  LOG_PRINT(DEBUG,"sysInfo2quat->qSearch_I = %d",sysInfo->qSearch_I);

  /* fill in q_Search_C_Initial */
  sysInfo->qSearch_C_Initial = hoCtrlTableOutData->qSearch_C_Initial;
  LOG_PRINT(DEBUG,"sysInfo2quat->qSearch_C_Initial = %d",sysInfo->qSearch_C_Initial);

  /* fill in fdd_Q_Offset */
  sysInfo->fdd_Qoffset = hoCtrlTableOutData->fddQoffset;
  LOG_PRINT(DEBUG,"sysInfo2quat->fdd_Qoffset = %d",sysInfo->fdd_Qoffset);

  /* fill in fdd_Rep_Quant */
  sysInfo->fdd_Rep_Quant = FDD_REPQUANT;
  LOG_PRINT(DEBUG,"sysInfo2quat->fdd_Rep_Quant = %d",sysInfo->fdd_Rep_Quant);

  /* fill in fdd_Multirat_Report */
  sysInfo->fdd_Multirat_Report = hoCtrlTableOutData->fddMultiRatReporting;
  LOG_PRINT(DEBUG,"sysInfo2quat->fdd_Multirat_Report = %d",sysInfo->fdd_Multirat_Report);

  /* fill in fdd_Qmin */
  sysInfo->fdd_Qmin = hoCtrlTableOutData->fddQmin;
  LOG_PRINT(DEBUG,"sysInfo2quat->fdd_Qmin = %d",sysInfo->fdd_Qmin);

  /* fill in fdd_Qmin_Offset */
  sysInfo->fdd_Qmin_Offset = hoCtrlTableOutData->fddQminOffset;
  LOG_PRINT(DEBUG,"sysInfo2quat->fdd_Qmin_Offset = %d",sysInfo->fdd_Qmin_Offset);

  /* fill in fdd_Rscpmin */
  sysInfo->fdd_Rscpmin = hoCtrlTableOutData->fddRSCPmin;
  LOG_PRINT(DEBUG,"sysInfo2quat->fdd_Rscpmin = %d",sysInfo->fdd_Rscpmin);
  
  /* fill in WcdmaSearchPrio */
  sysInfo->wcdmaSearchPrio = hoCtrlTableOutData->WcdmaSearchPrio;
  LOG_PRINT(DEBUG,"sysInfo2quat->wcdmaSearchPrio = %d",sysInfo->wcdmaSearchPrio);
  
  
  /* fill in fdd_reporting_Threashold_2 */
  sysInfo->fdd_reporting_Threashold_2 = hoCtrlTableOutData->fddReportingThreshold2; //to be read from  hoCtrlTableOutData
  LOG_PRINT(DEBUG,"sysInfo2quat->fdd_reporting_Threashold_2 = %d",sysInfo->fdd_reporting_Threashold_2);
  LOG_PRINT(DEBUG,"setLen %d",setLen);

  sysInfo->si2QuatCount = 0;
  sysInfo->si2QuatIndex = 0;

  for( j=0; j<setLen; j++)
  {
    if(innerLength[j]>8)
    {
      sysInfo->si2QuatCount++;
    }
    else if(innerLength[j]==8 && (j == setLen - 1))
    {
      sysInfo->si2QuatCount++;
    }
    sysInfo->si2QuatCount++;
  }        

  LOG_PRINT(DEBUG,"sysInfo->si2QuatCount= %d",sysInfo->si2QuatCount);

  for( j=0; j<setLen; j++) /* Loop Over Number of FDD Arfcns */
  {
    n = 0;
    newInnerLen = 0;
    sysInfo->fddDesc[j].fddArfcn = arfcn[j];

    LOG_PRINT(DEBUG,"FDD ARFCN  %d",sysInfo->fddDesc[j].fddArfcn);

    /* initializing arfcn array to zero */
    memset(set,0,sizeof(I_S32)*ARFCN_LEN);
    memset(newSet,0,sizeof(I_S32)*ARFCN_LEN);
    memset(nW,0,sizeof(I_S32)*NW_LEN);


    for(i=0; i<innerLength[j]; i++) /* Number of Scrambling Codes per Arfcn */
    {
      set[i] = fddInfo[j][i];
      LOG_PRINT(DEBUG, "set[%d]: %d" , i,set[i]) ;
    }    


    for(i = 0; i<innerLength[j]; i++) /* Finding a 0 in the list of Scram Codes */
    {
      if(set[i]  == 0)
      {
        position=i;
        n = 1;
        break;
      }
    }

    if(n == 0)
    {
      for(i= 0; i<innerLength[j]; i++)
        set[i] = set[i] -1 ;

      index = 1;
      range = 1023;
      sysInfo->fddDesc[j].fddIndices0 = 0;

      LOG_PRINT(DEBUG, "case n= 0") ;
    }
    else
    {
      if(position==(innerLength[j]-1)); /* 0 is present at the last position of array */
      else
      {
        for(i=position;i<innerLength[j];i++)
          set[i]=set[i+1];
      }

      for(i= 0; i<innerLength[j]; i++)
        set[i] = set[i] - 1;

      index = 1;
      range = 1023;

      
      if (position >= 8)
        sysInfo->fddDesc[j].fddIndices0 = 0  ;
      else
        sysInfo->fddDesc[j].fddIndices0 = 1  ;

        innerLength[j] = innerLength[j] - 1;
    }


    if(innerLength[j]>8)
      Encode_san(index, set, 8 , range, nW); 
    
    /*When Last Index has 8 or 8 non-zero along with a 0 scrambling code 
      then encoding 7 non-zero scrambling code*/
    else if((innerLength[j]==8) && ((j == setLen - 1) || (n == 1)))
    {
      Encode_san(index, set, 7 , range, nW); 
      zeroPresent = I_TRUE; 
    }
    else  
      Encode_san(index, set, innerLength[j] , range, nW); 

     
    sysInfo->fddDesc[j].noOfFddCells = innerLength[j];
   
   for(k=0;k<16;k++)
   {
      sysInfo->fddDesc[j].w[k] = nW[k];
      LOG_PRINT(DEBUG,"\n %d, j=%d, sysInfo2Quat->w[%d]  = %d\t",__LINE__, j, k, sysInfo->fddDesc[j].w[k]);
   }

    EncodeSysInformation2quat(sysInfo,buff+singleBufLen,bufLen,j,zeroPresent);
    LOG_PRINT(DEBUG,"GOYAL: Printing Encoded System Information 2quat message buffer");
    PRINT_HEX_DUMP(DEBUG,buff+singleBufLen,(23));

    if(nextIndex == 16)
    {
      LOG_PRINT(DEBUG,"No more SI 2 Quats can be encoded");
      break;
    }
    if(nextIndex!=0) 
    { 
      if(sysInfo->fddDesc[j].noOfFddCells > 8){
        sysInfo->indexStart3G = sysInfo->indexStart3G + 8 ;
        LOG_PRINT(DEBUG,"In cond 1 sysInfo->indexStart3G = %d",sysInfo->indexStart3G);
      }
      else if((sysInfo->fddDesc[j].noOfFddCells == 8) && 
             (((j == (setLen - 1))) || (n == 1)))
      {
        sysInfo->indexStart3G = sysInfo->indexStart3G + 7 ;
        LOG_PRINT(DEBUG,"In cond 1 sysInfo->indexStart3G = %d",sysInfo->indexStart3G);
      }
      else{
        sysInfo->indexStart3G = sysInfo->indexStart3G + sysInfo->fddDesc[j].noOfFddCells ;
        LOG_PRINT(DEBUG,"In cond 2 sysInfo->indexStart3G = %d",sysInfo->indexStart3G);
      }
    }
    singleBufLen+=23;

    if( (sysInfo->fddDesc[j].noOfFddCells > 8) || ((sysInfo->fddDesc[j].noOfFddCells == 8) &&  
          ((j == (setLen - 1)) || (n == 1))))
    {

       if (position >= 8)   
        sysInfo->fddDesc[j].fddIndices0 = 1  ;


      if(sysInfo->fddDesc[j].noOfFddCells > 8 ){
        sysInfo->fddDesc[j].noOfFddCells = innerLength[j] - 8;
        newInnerLen = innerLength[j] - 8;
        for(i = 0; i < newInnerLen; i++)
        {
          newSet[i] = set[i+8];
          LOG_PRINT(DEBUG, "newset[%d]: %d" , i,newSet[i]) ;
        }
      }
      else if( (sysInfo->fddDesc[j].noOfFddCells == 8) &&  
             ((j == (setLen - 1)) || (n == 1)) )
      {
        sysInfo->fddDesc[j].noOfFddCells = innerLength[j] - 7;
        newInnerLen = innerLength[j] - 7;
       for(i = 0; i < newInnerLen; i++)
       {
         newSet[i] = set[i+7];
         LOG_PRINT(DEBUG, "newset[%d]: %d" , i,newSet[i]) ;
       }
      }
   /*  for(i = 0 ; i < newInnerLen; i++){
        newSet[i] = set[i+8];
        LOG_PRINT(DEBUG, "newset[%d]: %d" , i,newSet[i]) ;
      }*/


      memset(nW,0,sizeof(I_S32)*NW_LEN);
      Encode_san(index, newSet, newInnerLen , range, nW); 
      i=0;
      for(k=0;k<newInnerLen; k++)
      {
        sysInfo->fddDesc[j].w[i] = nW[k];
        LOG_PRINT(DEBUG,"\n %d, j=%d, sysInfo2Quat->w[%d]  = %d\t",__LINE__, j, i, sysInfo->fddDesc[j].w[i]);
        i++;
      }

      EncodeSysInformation2quat(sysInfo,buff+singleBufLen,bufLen,j,zeroPresent);
      LOG_PRINT(DEBUG, "GOYAL: %s : %d : After EncodeSysInformation2quat buff=%x, bufLen=%d, setLen=%d", __FILE__, __LINE__, buff, *bufLen, setLen);

      if(nextIndex == 16)
      {
        LOG_PRINT(DEBUG,"No more SI 2 Quats can be encoded");
        break;
      }  
      if(nextIndex!=0) 
      { 
        if(sysInfo->fddDesc[j].noOfFddCells > 8){
          sysInfo->indexStart3G = sysInfo->indexStart3G + 8 ;
          LOG_PRINT(DEBUG,"In cond 1 sysInfo->indexStart3G = %d",sysInfo->indexStart3G);
        }
        else if((sysInfo->fddDesc[j].noOfFddCells == 8) && ((j == (setLen - 1))||(n == 1)) ){
          sysInfo->indexStart3G = sysInfo->indexStart3G + 7 ;
          LOG_PRINT(DEBUG,"In cond 1 sysInfo->indexStart3G = %d",sysInfo->indexStart3G);
        }
        else{
          sysInfo->indexStart3G = sysInfo->indexStart3G + sysInfo->fddDesc[j].noOfFddCells ;
          LOG_PRINT(DEBUG,"In cond 2 sysInfo->indexStart3G = %d",sysInfo->indexStart3G);
        }
      }

      LOG_PRINT(DEBUG,"Printing Encoded System Information 2quat message buffer");
      PRINT_HEX_DUMP(DEBUG,buff+singleBufLen,(23));
      singleBufLen+=23;
    }
    //check on n = 1 then do this else nothing to be done   
    if (n == 1)
      innerLength[j] = innerLength[j] + 1;
  } 

  LOG_PRINT(DEBUG,"%d",*(bufLen));  
  PRINT_HEX_DUMP(DEBUG,buff,*(bufLen));
  free(hoCtrlTableOutData);
  nextIndex = 0;
  DalocOrdBuf(sysInfo);
  return errCode;/* will be success */
}


/***********************************************************************************
  *  Function Name   : PrepareMeasInfo
  *
  *  Args            : 1. cell id
  *                    2. lac
  *                    3. bsc id
  *                    4. buff
  *                    5. bufLen
  *
  *  Returns         : SUCCESS or  FAILURE.
  *
  *  Task            : This method will FILL the Meas Information  structure
  ***********************************************************************************/

I_S32 PrepareMeasInfo ( I_U32 cellId , I_U32 lac,
                                   I_U8 * buff , I_U16 * bufLen,
                                   I_U16 arfcn[], I_U32 setLen,I_U16 fddInfo[][16], I_U8 innerLength[],
                                   I_U8 baInd , I_U8 baInd3g)
{
  I_S32 index,range;
  I_U32 i =0,n =0,j =0, position =0, k=0;
  I_S32 errCode = 1;
  I_S32 nW[NW_LEN];
  I_S32 set[ARFCN_LEN];
  I_S32 newSet[ARFCN_LEN];
  I_S32 temp = 0;
  I_U32 band;
  I_U16 singleBufLen = 0;
  I_U8 newInnerLen = 0;
  I_U8 zeroPresent = I_FALSE;
  HoCtrlTableIndices hoCtrlTableInData;
  HoCtrlTableApi     *hoCtrlTableOutData = NULL;


  MeasInfo *measInfo = (MeasInfo *)AlocOrdBuf(sizeof(MeasInfo));

  /* Initialize to zero*/
  if(measInfo != NULL)
    memset(measInfo,0,sizeof(MeasInfo));
  else
  {
    LOG_PRINT(CRITICAL, "Unable to allocate memory to SysInfo2quat structure");
    return errCode;
  }




  /* Get the data needed from the Db */
  hoCtrlTableInData.cellId = cellId;
  hoCtrlTableInData.lac = lac;
  errCode = getHoCtrlTable(&hoCtrlTableInData, &hoCtrlTableOutData);
  if (errCode != CLIB_SUCCESS)
  {
    LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI 2Quat: err = %s", clib_strerror(errCode));
    DalocOrdBuf(measInfo);
    return errCode;
  }

  /* fill protocol discriminator */
  measInfo->protocolDiscriminator = 0;
  LOG_PRINT(DEBUG,"measInfo->protocolDiscriminator = %d",measInfo->protocolDiscriminator);

  /* fill protocol discriminator*/
  measInfo->messageType = MSG_MEAS_INFO;
  LOG_PRINT(DEBUG,"measInfo->messageType = %d",measInfo->messageType);
  
  measInfo->shortL2Header = 0;
  LOG_PRINT(DEBUG,"meas->shortL2Header = %d",measInfo->shortL2Header);
  
  /* fill in ba_ind */
  measInfo->baInd = baInd;
  LOG_PRINT(DEBUG,"meas->baInd = %d",measInfo->baInd);

  /* fill in ba_ind_3g */
    //sysInfo->baInd3g = baInd3g;
    measInfo->baInd3g = 1;
  LOG_PRINT(DEBUG,"measInfo->baInd3g = %d",measInfo->baInd3g);

  /* fill in mp_change_mark */
  measInfo->mpChangeMark = MP_CHANGE_MARK;
  LOG_PRINT(DEBUG,"measInfo->mpChangeMark = %d",measInfo->mpChangeMark);

  measInfo->pwrc = 0;
  LOG_PRINT(DEBUG,"measInfo->pwrc = %d",measInfo->pwrc);
  
  
  measInfo->report_type = 1;
  LOG_PRINT(DEBUG,"measInfo->report_type = %d",measInfo->report_type);
  
  
  measInfo->reporting_rate = 0;
  LOG_PRINT(DEBUG,"measInfo->reporting_rate = %d",measInfo->reporting_rate);
  
  
  measInfo->invalidBsic = 1;
  LOG_PRINT(DEBUG,"measInfo->invalidBsic = %d",measInfo->invalidBsic);
  
  /* fill in q_Search_I */
  measInfo->qSearch_I = hoCtrlTableOutData->qSearch_I;
  LOG_PRINT(DEBUG,"measInfo->qSearch_I = %d",measInfo->qSearch_I);

  /* fill in q_Search_C */
  measInfo->qSearch_C = hoCtrlTableOutData->qSearch_C;
  LOG_PRINT(DEBUG,"measInfo->qSearch_C = %d",measInfo->qSearch_C);


  /* fill in fdd_Q_Offset */
  measInfo->fdd_Qoffset = hoCtrlTableOutData->fddQoffset;
  LOG_PRINT(DEBUG,"measInfo->fdd_Qoffset = %d",measInfo->fdd_Qoffset);

  /* fill in fdd_Rep_Quant */
  measInfo->fdd_Rep_Quant = FDD_REPQUANT;
  LOG_PRINT(DEBUG,"measInfo->fdd_Rep_Quant = %d",measInfo->fdd_Rep_Quant);

  /* fill in fdd_Multirat_Report */
  measInfo->fdd_Multirat_Report = hoCtrlTableOutData->fddMultiRatReporting;
  LOG_PRINT(DEBUG,"measInfo->fdd_Multirat_Report = %d",measInfo->fdd_Multirat_Report);

  /* fill in fdd_Qmin */
  measInfo->fdd_Qmin = hoCtrlTableOutData->fddQmin;
  LOG_PRINT(DEBUG,"measInfo->fdd_Qmin = %d",measInfo->fdd_Qmin);
  /* fill in WcdmaSearchPrio */
  measInfo->wcdmaSearchPrio = hoCtrlTableOutData->WcdmaSearchPrio;
  LOG_PRINT(DEBUG,"measInfo->wcdmaSearchPrio = %d",measInfo->wcdmaSearchPrio);

  /* fill in fdd_reporting_Threashold_2 */
  measInfo->fdd_reporting_Threashold_2 = hoCtrlTableOutData->fddReportingThreshold2; 
  LOG_PRINT(DEBUG,"measInfo->fdd_reporting_Threashold_2 = %d",measInfo->fdd_reporting_Threashold_2);
  
  LOG_PRINT(DEBUG,"setLen %d",setLen);
  
  measInfo->miCount = 0;
  measInfo->miIndex = 0;

  for( j=0; j<setLen; j++)
  {
     if(innerLength[j]>8)
     {
        measInfo->miCount++;
     }
     else if(innerLength[j]==8 && (j == setLen - 1))
     {
        measInfo->miCount++;
     }
     measInfo->miCount++;
  }

  LOG_PRINT(DEBUG,"measInfo->miCount= %d",measInfo->miCount);
 
  
  for( j=0; j<setLen; j++) /* Loop Over Number of FDD Arfcns */
  {
    n = 0;
    newInnerLen = 0;
    measInfo->fddDesc[j].fddArfcn = arfcn[j];

    LOG_PRINT(DEBUG,"FDD ARFCN  %d",measInfo->fddDesc[j].fddArfcn);
  
    /* initializing arfcn array to zero */
    memset(set,0,sizeof(I_S32)*ARFCN_LEN);
    memset(newSet,0,sizeof(I_S32)*ARFCN_LEN);
    memset(nW,0,sizeof(I_S32)*NW_LEN);

    
    for(i=0; i<innerLength[j]; i++) /* Number of Scrambling Codes per Arfcn */
    {
      set[i] = fddInfo[j][i];
      LOG_PRINT(DEBUG, "set[%d]: %d" , i,set[i]) ;
    }
 
    for(i = 0; i<innerLength[j]; i++) /* Finding a 0 in the list of Scram Codes */
    {
      if(set[i]  == 0)
      {
        position=i;
        n=1; 
        break;
      }
    }
   
    
    if(n == 0)
    {
      for(i= 0; i<innerLength[j]; i++)
        set[i] = set[i] -1 ;

      index = 1;
      range = 1023;
      measInfo->fddDesc[j].fddIndices0 = 0  ;
    }
    else
    {
      if(position==(innerLength[j]-1)); /* 0 is present at the last position of array */
      else
      {
        for(i=position;i<innerLength[j];i++)
          set[i]=set[i+1];
      }

      for(i= 0; i<innerLength[j]; i++)
        set[i] = set[i] - 1;

      index = 1;
      range = 1023;

      if (position >= 8)
        measInfo->fddDesc[j].fddIndices0 = 0  ;
      else
        measInfo->fddDesc[j].fddIndices0 = 1  ;

        innerLength[j] = innerLength[j] - 1;
    }

    
    if(innerLength[j]>8)
       Encode_san(index, set, 8 , range, nW); // first mi can have not more than 9 
    else if((innerLength[j]==8) && ((j == setLen - 1) || (n == 1))){
       Encode_san(index, set, 7 , range, nW); //first mi can not have more than 7 
       zeroPresent = I_TRUE;
    }
    else  
       Encode_san(index, set, innerLength[j] , range, nW); // only one mi 
    
   
   measInfo->fddDesc[j].noOfFddCells = innerLength[j];
   
   for(k=0;k<16;k++)
    {
      measInfo->fddDesc[j].w[k] = nW[k];
      LOG_PRINT(DEBUG,"\n measInfo->w[%d]  = %d\t", k, measInfo->fddDesc[j].w[k]);
    }

    EncodeMeasInfo(measInfo,buff+singleBufLen,bufLen,j,zeroPresent);
    LOG_PRINT(DEBUG,"Printing Encoded Measurement Information message buffer");
    PRINT_HEX_DUMP(DEBUG,buff+singleBufLen,(19));

    if(msInfoIndex == 16)
    {
      LOG_PRINT(DEBUG,"No more Measurement Information can be encoded");
      break;
    }
      if(msInfoIndex!=0) 
      { 
        if(measInfo->fddDesc[j].noOfFddCells > 8){
          measInfo->indexStart3G = measInfo->indexStart3G + 8 ;
          LOG_PRINT(DEBUG,"In cond 1 measInfo->indexStart3G = %d",measInfo->indexStart3G);
        }
        else if((measInfo->fddDesc[j].noOfFddCells == 8) &&  
                ((j == (setLen - 1)) || (n == 1))){
          measInfo->indexStart3G = measInfo->indexStart3G + 7 ;
          LOG_PRINT(DEBUG,"In cond 1 measInfo->indexStart3G = %d",measInfo->indexStart3G);
        }
        else{
          measInfo->indexStart3G = measInfo->indexStart3G + measInfo->fddDesc[j].noOfFddCells ;
          LOG_PRINT(DEBUG,"In cond 2 measInfo->indexStart3G = %d",measInfo->indexStart3G);
        }
      }

    singleBufLen+=19;

    if(measInfo->fddDesc[j].noOfFddCells>8 || ((measInfo->fddDesc[j].noOfFddCells == 8) &&  (j == (setLen - 1)       || (n == 1))))
    {
      if (position >= 8)   
        measInfo->fddDesc[j].fddIndices0 = 1  ;


       if(measInfo->fddDesc[j].noOfFddCells > 8 ){
          measInfo->fddDesc[j].noOfFddCells = innerLength[j] - 8;
          newInnerLen = innerLength[j] - 8;
          for(i = 0 ; i < newInnerLen; i++)
            newSet[i] = set[i+8];
       }
        else if((measInfo->fddDesc[j].noOfFddCells == 8) &&  (j == (setLen - 1)||(n == 1))){
          measInfo->fddDesc[j].noOfFddCells = innerLength[j] - 7;
          newInnerLen = innerLength[j] - 7;
          for(i = 0 ; i < newInnerLen; i++)
            newSet[i] = set[i+7];
        }

  /*   for(i = 0 ; i < newInnerLen; i++)
        newSet[i] = set[i+8];*/
      
      memset(nW,0,sizeof(I_S32)*NW_LEN);
      
      LOG_PRINT(DEBUG,"Sending Next Measurement Information for same ARFCN");
      
      Encode_san(index, newSet, newInnerLen, range, nW); 
      i=0;
      for(k=0;k<newInnerLen;k++)
      {
        measInfo->fddDesc[j].w[i] = nW[k];
        LOG_PRINT(DEBUG,"\n k---%d,measInfo->w[%d]  = %d\t",k, i, measInfo->fddDesc[j].w[i]);
        i++;
      }

      EncodeMeasInfo(measInfo,buff+singleBufLen,bufLen,j,zeroPresent);

      if(msInfoIndex == 16)
      {
        LOG_PRINT(DEBUG,"No more Measurement Information can be encoded");
        break;
      }  
      if(msInfoIndex!=0) 
      { 
        if(measInfo->fddDesc[j].noOfFddCells > 8){
          measInfo->indexStart3G = measInfo->indexStart3G + 8 ;
          LOG_PRINT(DEBUG,"In cond 1 measInfo->indexStart3G = %d",measInfo->indexStart3G);
        }
        else if((measInfo->fddDesc[j].noOfFddCells == 8) &&  (j == (setLen - 1)||(n == 1))){
          measInfo->indexStart3G = measInfo->indexStart3G + 7 ;
          LOG_PRINT(DEBUG,"In cond 1 measInfo->indexStart3G = %d",measInfo->indexStart3G);
        }
        else{
          measInfo->indexStart3G = measInfo->indexStart3G + measInfo->fddDesc[j].noOfFddCells ;
          LOG_PRINT(DEBUG,"In cond 2 measInfo->indexStart3G = %d",measInfo->indexStart3G);
        }
      }

      LOG_PRINT(DEBUG,"Printing Encoded Measurement Information  message buffer");
      PRINT_HEX_DUMP(DEBUG,buff+singleBufLen,(20));
      singleBufLen+=19;
    }
   if(n == 1)
    innerLength[j]= innerLength[j] + 1;
  }  

  
  LOG_PRINT(DEBUG,"%d",*(bufLen));  
  PRINT_HEX_DUMP(DEBUG,buff,*(bufLen));
  msInfoIndex = 0;
  free(hoCtrlTableOutData);
  DalocOrdBuf(measInfo);
  return errCode;/* will be success */
}




/***********************************************************************************
*  Function Name   : EncodeSysInformation1 
*
*  Args            : 1. SystemInfo1 structure pointer 
*                    2. pointer to buff 
*                    3. length of buffer 
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 1 message buffer 
***********************************************************************************/
	
/*I_S32  SysInfoEncoder::EncodeSysInformation1( SystemInfo1 *sysInfo, I_U8 *buff, I_U16 *len )
*/I_S32  EncodeSysInformation1( SystemInfo1 *sysInfo, I_U8 *buff, I_U16 *len )
{

 I_U8 tvar1 = 0;
 I_U8 tvar2 = 0;
 I_U8 tvar3 = 0;
 I_U8 tvar4 = 0;
 I_U8 tvar5 = 0;
 I_U8 tvar6 = 0;

 I_U16 tvar7 = 0;
 I_U16 tvar8 = 0;
 I_U16 tvar9 = 0;

 I_U8 format1[22] = "bitmap0format";
 I_U8 format2[22] = "range1024format";
 I_U8 format3[22] = "range512format";
 I_U8 format4[22] = "range256format";
 I_U8 format5[22] = "range128format";
 I_U8 format6[22] = "variablebitmapformat";
 I_U8 firstByte;
 I_U8 bitstring[30];
 I_U8 l2PseudoLength;
 I_U8 S_ARFCN = 119;
 I_U8 E_ARFCN = 113; 
 I_U8 i;

 /* Added By Aricent */
 memset(bitstring, 0, sizeof(bitstring));
 /* End of Adding */

 tvar1 = sysInfo->skipIndicator<<4 ;
 firstByte = tvar1|sysInfo->protocolDiscriminator;

 bitstring[0] = firstByte;
 bitstring[1] = sysInfo->messageType;


/*cellChannelDescription */

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format1);


if(tvar6==0)       /* bitmap 0 format */
{

        tvar1 = sysInfo->ARFCN[123]<<3;
        tvar2 = tvar1 | sysInfo->ARFCN[122]<<2;
        tvar1 = tvar2 | sysInfo->ARFCN[121]<<1;
        tvar2 = tvar1 | sysInfo->ARFCN[120];
        tvar1 = tvar2 &  15;
        bitstring[2] = tvar1;

        for(i= 3; i<=17; i++)
        {
            tvar4 = 6;
            tvar1 = sysInfo->ARFCN[S_ARFCN]<<7;
            for(tvar3 = S_ARFCN - 1; tvar3>=E_ARFCN; tvar3--)
            {
                tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                tvar1 = tvar2;
                tvar4--;
            }
            tvar2 = tvar1 | sysInfo->ARFCN[E_ARFCN -1];
            bitstring[i] = tvar2;
            tvar1= 0;
            tvar2= 0;
            tvar3 =0;
            S_ARFCN = S_ARFCN -8;
            E_ARFCN = E_ARFCN -8;
        }//for

}/*end of bitmap0 format*/

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format2);

if(tvar6 ==0)       /*range 1024 format */
{
LOG_PRINT(DEBUG,"RRRR: Inside range 1024 format");
        
        I_S32   index = 0; /* initialized to 0 by Aricent */
        I_S32   len = 0 , i =0;
        I_S32   n = 0 ;
        I_S32   range = 1024;
        I_S32   nW[28];
        /* I_S32   set[16]; *//*Changed by Aricent*/
        I_S32 set[16]; 
        for(i=0; i<28; i++)
        {
         nW[i] = 0;
         
        }
       
        for(i=0; i<16; i++)
        {
         set[i] = 0;
         
        }
LOG_PRINT(DEBUG,"RRRR: f1 %d f2 %d f3 %d f4 %d",sysInfo->f1,sysInfo->f2,sysInfo->f3,sysInfo->f4);
             
        if(sysInfo->f1 != -1)
        {
          set[0]=   sysInfo->f1;
          len++;
        }
        if(sysInfo->f2 != -1)
        {
          set[1]=   sysInfo->f2;
          len++;
        }

        if(sysInfo->f3 != -1)
        {
          set[2]=   sysInfo->f3;
          len++;
        }
        if(sysInfo->f4 != -1)
        {
          set[3]=   sysInfo->f4;
          len++;
        }
        if(sysInfo->f5 != -1)
        {
          set[4]=   sysInfo->f5;
          len++;
        }
        if(sysInfo->f6 != -1)
        {
          set[5]=   sysInfo->f6;
          len++;
        }
        if(sysInfo->f7 != -1)
        {
          set[6]=   sysInfo->f7;
          len++;
        }
        if(sysInfo->f8 != -1)
        {
          set[7]=   sysInfo->f8;
          len++;
        }
        if(sysInfo->f9 != -1)
        {
          set[8]=   sysInfo->f9;
          len++;
        }
        if(sysInfo->f10 != -1)
        {
          set[9]=   sysInfo->f10;
          len++;
        }
        if(sysInfo->f11 != -1)
        {
          set[10]=   sysInfo->f11;
          len++;
        }
        if(sysInfo->f12 != -1)
        {
          set[11]=   sysInfo->f12;
          len++;
        }
        if(sysInfo->f13 != -1)
        {
          set[12]=   sysInfo->f13;
          len++;
        }
        if(sysInfo->f14 != -1)
        {
          set[13]=   sysInfo->f14;
          len++;
        }
        if(sysInfo->f15 != -1)
        {
          set[14]=   sysInfo->f15;
          len++;
        }
        if(sysInfo->f16 != -1)
        {
          set[15]=   sysInfo->f16;
          len++;
        }

LOG_PRINT(DEBUG,"RRRR: After reading f1-f16 len: %d",len);
        //int set[] = {13, 71, 122, 191, 251, 321, 402, 476, 521, 575, 635, 701, 765, 831, 906, 981};
        for(i = 0; i<len; i++)
        {
           if(set[i]  == 0)
           {
               n++;
           }
        }
LOG_PRINT(DEBUG,"RRRR: After checking set n: %d",n);
        if(n == 0)
        {
LOG_PRINT(DEBUG,"RRRR: Inside n==0");
           for(i= 0; i<len; i++)
           {
              set[i] = set[i] -1;
              index = 1;
              range = 1023;
              sysInfo->f0 =0  ;
           }
        }
        else
        {
LOG_PRINT(DEBUG,"RRRR: Inside else n==0");
            for(i= 0; i<len; i++)
            {
               set[i] = set[i++];
               index = 1;
               range = 1024 ;
               sysInfo->f0 = 1 ;
            }
        }
       
LOG_PRINT(DEBUG,"RRRR: Before Encode_san nW");
PRINT_HEX_DUMP(DEBUG, set, 16);
        Encode_san(index, set, len, range, nW);
LOG_PRINT(DEBUG,"RRRR: After Encode_san nW");
PRINT_HEX_DUMP(DEBUG, nW, 16);
        
        sysInfo->w1 = nW[0];
        sysInfo->w2 = nW[1];
        sysInfo->w3 = nW[2];
        sysInfo->w4 = nW[3];
        sysInfo->w5 = nW[4];
        sysInfo->w6 = nW[5];
        sysInfo->w7 = nW[6];
        sysInfo->w8 = nW[7];
        sysInfo->w9 = nW[8];
        sysInfo->w10 = nW[9];
        sysInfo->w11 = nW[10];
        sysInfo->w12 = nW[11];
        sysInfo->w13 = nW[12];
        sysInfo->w14 = nW[13];
        sysInfo->w15 = nW[14];
        sysInfo->w16 = nW[15];

        tvar3 = sysInfo->f0<<2;

        tvar7 = sysInfo->w1 >> 8;     /*High part of w1*/
        tvar8 = sysInfo->w1 & 255;     /*Low part of w1*/

        tvar4 = tvar3 | (I_U8) tvar7;
        tvar5 = tvar4 |128;
        tvar4 = tvar5 & 183;

        bitstring[2] = tvar4;

        bitstring[3] = (I_U8) tvar8;

        tvar7 = sysInfo->w2  >> 1;     /*High part of w2*/
        bitstring[4] = (I_U8) tvar7;

        tvar7 = sysInfo->w2 & 1;       /*Low part of w2*/

        tvar9 = sysInfo->w3 >> 2;     /*High part of w3*/
        bitstring[5] = (I_U8) tvar7<<7 | tvar9;

        tvar7 = sysInfo->w3 & 7;        /*Low part of w3*/

        tvar3 = sysInfo->w4 >> 2;     /*High part of w4*/
        bitstring[6] = (I_U8) tvar7<<6 | tvar3;
        tvar4 = sysInfo->w4 & 3;        /*Low part of w4*/


        tvar1 = sysInfo->w5 >> 2;     /*High part of w5*/
        bitstring[7] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w5 & 3;        /*Low part of w5*/

        tvar3 = sysInfo->w6 >> 2;     /*High part of w6*/
        bitstring[8] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w6 & 3;        /*Low part of w6*/

        tvar1 = sysInfo->w7 >> 2;     /*High part of w7*/
        bitstring[9] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w7& 3;       /*Low part of w7*/

        tvar3 = sysInfo->w8 >> 1;     /*High part of w8*/
        bitstring[10] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w8 & 1;       /*Low part of w8*/

        tvar1 = tvar4 << 7 | sysInfo->w9;
        bitstring[11] = tvar1;

        tvar2 = sysInfo->w10;

        tvar3 = sysInfo->w11 >> 6;     /*High part of w11*/
        bitstring[12] = tvar2<<1 | tvar3;
        tvar4 = sysInfo->w11& 63;       /*Low part of w11*/

        tvar1 = sysInfo->w12 >> 5;     /*High part of w12*/
        bitstring[13] = tvar4<<2 | tvar1;
        tvar2 = sysInfo->w12& 31;       /*Low part of w12*/


        tvar3 = sysInfo->w13 >> 4;     /*High part of w13*/
        bitstring[14] = tvar2<<3 | tvar3;
        tvar4 = sysInfo->w13& 15;       /*Low part of w13*/

        tvar1 = sysInfo->w14 >> 3;     /*High part of w14*/
        bitstring[15] = tvar4<<4 | tvar1;
        tvar2 = sysInfo->w14& 7;        /*Low part of w14*/

        tvar3 = sysInfo->w15 >> 2;     /*High part of w15*/
        bitstring[16] = tvar2<<5 | tvar3;
        tvar4 = sysInfo->w15& 7;        /*Low part of w15*/

        tvar1 = sysInfo->w16 ;
        bitstring[17] = tvar4<<6 | tvar1;

}/*end of 1024 format */

tvar6 = strcmp((const char*)sysInfo->formatIndicator,(const char*) format3);

if ( tvar6 == 0 )       /*range 512 format */
{


        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCN512 */
        tvar4 = (I_U8) tvar7 |136;

       /*tvar3 = tvar4 & 185; 
        bitstring[2] = tvar3; */
        bitstring[2] = tvar4; 

        tvar7 = sysInfo->origARFCN >> 1;   /*middle part of origARFCN512 */
        tvar4 = (I_U8) tvar7 & 255;
        bitstring[3] = tvar4;

        /*tvar7 = sysInfo->origARFCN >> 9;*/   /*low part of origARFCN512 */
        tvar7 = sysInfo->origARFCN & 1; 
        /*tvar4 = (I_U8) tvar3 & 511; */
        tvar4 = (I_U8)tvar7;

        tvar8 = sysInfo->w1>> 2;  /*High part of w1*/
        tvar9 = sysInfo->w1 & 3 ; /*low part of w1*/
        tvar3 = tvar4 << 7 | (I_U16) tvar8;
        bitstring[4] = tvar3; 

        tvar3 = sysInfo->w2>> 2;  /*High part of w2*/
        bitstring[5] = (I_U16) tvar9 <<6 | tvar3;
        tvar4 = sysInfo->w2 & 3 ; /*low part of w2*/

        tvar1 = sysInfo->w3>> 2;  /*High part of w3*/
        bitstring[6] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w3 & 3 ; /*low part of w3*/

        tvar3 = sysInfo->w4>> 1;  /*High part of w4*/
        bitstring[7] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w4 & 1 ; /*low part of w4*/

        tvar1 = sysInfo->w5;
        tvar2 = tvar4 << 7 | sysInfo->w5;
        bitstring[8] = tvar2;

        tvar1 = sysInfo->w6;

        tvar3 = sysInfo->w7>> 6;  /*High part of w7*/
        /*bitstring[9] = tvar1<<1 | tvar1;*/
        bitstring[9] = tvar1<<1 | tvar3;
        tvar4 = sysInfo->w7 & 63 ; /*low part of w7*/

        tvar1 = sysInfo->w8>> 4;  /*High part of w8*/
        /*bitstring[10] = tvar4<<2 | tvar4;*/
        bitstring[10] = tvar4<<2 | tvar1;
        tvar2 = sysInfo->w8 & 15 ; /*low part of w8*/

        tvar3 = sysInfo->w9>> 2;  /*High part of w9*/
        /*bitstring[11] = tvar2<<4 | tvar2;*/
        bitstring[11] = tvar2<<4 | tvar3;
        tvar4 = sysInfo->w9 & 3 ; /*low part of w9*/

        tvar1 = sysInfo->w10;
        tvar2 = tvar4<<6 | tvar1;
        bitstring[12] = tvar2;

        tvar3 = sysInfo->w11 ;

        tvar1 = sysInfo->w12 >> 4;  /*High part of w12*/
        bitstring[13] = tvar3<<2 | tvar1;
        tvar2 = sysInfo->w12 & 15 ; /*low part of w12*/

        tvar3 = sysInfo->w13 >> 2;  /*High part of w13*/
        /*bitstring[14] = tvar3<<4 | tvar3;*/
        bitstring[14] = tvar2<<4 | tvar3;
        tvar4 = sysInfo->w13 & 3 ; /*low part of w13*/

        tvar1 = sysInfo->w14;
        tvar2 = tvar4<<6 |tvar1 ;
        bitstring[15] = tvar2;
        tvar3 = sysInfo->w15;

        /*tvar1 = sysInfo->w16 >> 4;*/  /*High part of w16*/
        tvar1 = sysInfo->w16 >> 3;  /*High part of w16*/
        bitstring[16] = tvar3<<2 | tvar1;
        /*tvar2 = sysInfo->w16 & 15*/ ; /*low part of w16*/
        tvar2 = sysInfo->w16 & 7 ; /*low part of w16*/

        tvar3 = sysInfo->w17;
        tvar4 = tvar2 << 5 | tvar3;
        bitstring[17] =  tvar4;
       

}  /*end of range512w format */


tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format4);

if(tvar6==0)       /*range 256 format */
{


        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCN512 */
        tvar4 = (I_U8) tvar7 |138;
        tvar1 = tvar4 & 187 ;

        bitstring[2] = tvar1;

        tvar8 = sysInfo->origARFCN >> 1;   /*middle part of origARFCN512 */
        tvar4 = (I_U8) tvar8 & 255;
        bitstring[3] = tvar4;

        tvar9 = sysInfo->origARFCN >> 9;   /*low part of origARFCN512 */
        tvar4 = (I_U8) tvar9 & 511;

        tvar1 = sysInfo->w1 >> 1;  /*high part of w1 */
        tvar2 = sysInfo->w1 & 1;  /*low part of w1 */

        tvar3 = sysInfo->w2;
        tvar4 = tvar2<<7 |tvar3;
        bitstring[4] =  tvar4;

        tvar1 = sysInfo->w3;

        tvar3 = sysInfo->w4 >> 4;  /*high part of w4 */
        bitstring[5] = tvar1 << 1 | tvar3;
        tvar4 = sysInfo->w4 & 15;  /*low part of w4 */

        tvar1 = sysInfo->w5 >> 3;  /*high part of w5 */
        bitstring[6] = tvar4 << 3 | tvar1;
        tvar2 = sysInfo->w5 & 7;  /*low part of w5 */

        tvar3 = sysInfo->w6 >> 5;  /*high part of w6 */
        bitstring[7] = tvar2 << 5 | tvar3;
        tvar4 = sysInfo->w6 & 1;  /*low part of w6 */

        tvar1 = sysInfo->w7<<1;
        tvar5 = tvar4<< 7 | tvar1;

        tvar2 = sysInfo->w8 >> 4;  /*high part of w8 */
        bitstring[8] = tvar5 | tvar2;
        tvar3 = sysInfo->w8 & 15;  /*low part of w8 */

        tvar1 = sysInfo->w9 >> 4;  /*high part of w9 */
        bitstring[9] = tvar3<<4 | tvar1;
        tvar4 = sysInfo->w9 & 1;  /*low part of w9 */

        tvar1 = sysInfo->w10<<2;
        tvar5 = tvar4<<7  | tvar1 ;

        tvar2 = sysInfo->w11 >> 3;  /*high part of w11 */
        bitstring[10] = tvar5 | tvar2;
        tvar3 = sysInfo->w11 & 7;  /*low part of w11 */

        tvar1 = sysInfo->w12;
        bitstring[11] = tvar3<<4  | tvar1;
    
        tvar1 = sysInfo->w13;
        tvar2 = sysInfo->w14 >> 2; /*high part of w14*/
        tvar3 = sysInfo->w14 & 3; /*low part of w14 */

        bitstring[12] =  tvar1 << 3 |tvar2 ;

        tvar1 = sysInfo->w15;
        tvar2 = sysInfo->w16 >> 3; /*high part of w16*/
        tvar4 = sysInfo->w16 & 7; /*low part of w16 */

        tvar5 = tvar3<<5 | tvar1;
        bitstring[13] = tvar3 << 5 | tvar1 <<1 |tvar2;

        tvar1 = sysInfo->w17;
        tvar2 = sysInfo->w18 >> 3; /*high part of w18*/
        tvar3 = sysInfo->w18 & 7; /*low part of w18 */

        bitstring[14] = tvar4 << 5 | tvar1 <<1 |tvar2;

        tvar1 = sysInfo->w19;
        tvar2 = sysInfo->w20 >> 3; /*high part of w20*/
        tvar4 = sysInfo->w20 & 7; /*low part of w20 */

        bitstring[15] = tvar3 << 5 | tvar1 <<1 |tvar2;

        tvar1 = sysInfo->w21;
        bitstring[16] = tvar4 << 5 | tvar1<<1;
}/* end of 256 format*/

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format5);

if(tvar6 ==0)       /*range 128 format */
{

        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCN128 */
        tvar3 = (I_U8) tvar7 |140;
        tvar4 = tvar3 & 189;
 
        bitstring[2] = tvar4;
        
        tvar8 = sysInfo->origARFCN >> 1;   /*middle part of origARFCN128 */
        tvar4 = (I_U8) tvar8 & 255;
        bitstring[3] = tvar4;

        tvar9 = sysInfo->origARFCN >> 9;   /*low part of origARFCN128 */
        tvar4 = (I_U8) tvar9 & 511;

        tvar1 = sysInfo->w1;
        bitstring[4] = tvar4 << 1 | tvar1;

        tvar2 = sysInfo->w2;
        tvar3 = sysInfo->w3 >>4 ; /*high part of w3 */
        tvar4 = sysInfo->w3 & 15 ; /*low part of w3*/

        bitstring[5] = tvar2 << 2 |tvar3;

        tvar1 = sysInfo->w4 >>1 ; /*high part of w4 */
        tvar2 = sysInfo->w4 & 1 ; /*low part of w4 */

        bitstring[6] = tvar4 << 4 |tvar1;

        tvar1 = sysInfo->w5;

        tvar3 = sysInfo->w6 >>2 ; /*high part of w6 */
        tvar4 = sysInfo->w6 & 7 ; /*low part of w6 */

        bitstring[7] = tvar2 <<7 | tvar1 <<2 |tvar3;

        bitstring[8] = tvar4 <<5 | sysInfo->w7;

        bitstring[9] = sysInfo->w8 <<4 |  sysInfo->w9;

        bitstring[10] = sysInfo->w10 <<4 |  sysInfo->w11;

        bitstring[11] = sysInfo->w12 <<4 |  sysInfo->w13;

        bitstring[12] = sysInfo->w14 <<4 |  sysInfo->w15;

        tvar1 = sysInfo->w16;
        tvar2 = sysInfo->w17;

        tvar3 = sysInfo->w18 >>1 ; /*high part of w18 */
        tvar4 = sysInfo->w18 & 1 ; /*low part of w18 */

        bitstring[13] = tvar1 << 5 | tvar2<<2 |tvar3;

        tvar1 = sysInfo->w19;
        tvar2 = sysInfo->w20;

        tvar3 = sysInfo->w21 >>2 ; /*high part of w21 */
        tvar5 = sysInfo->w21 & 3 ; /*low part of w21 */

        bitstring[14] = tvar4 <<7 | tvar1 <<4 | tvar2 <<1 |tvar3;

        tvar1 = sysInfo->w22;
        tvar2 = sysInfo->w23;

        bitstring[15] = tvar5<<6 | tvar1 <<3 | tvar2;

        tvar1 = sysInfo->w26 >>1 ; /*high part of w26 */
        tvar2 = sysInfo->w26 & 1 ; /*low part of w26 */

        tvar3 = sysInfo->w24;
        tvar4 = sysInfo->w25;

        bitstring[16] =  tvar3 <<4 |tvar4 <<2 |tvar1;

        tvar1 = sysInfo->w27;
        tvar2 = sysInfo->w28;

        bitstring[17]= tvar4<<7 |tvar1<<4 |tvar2<<1;
}/*end of 128 format */

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format6);

if(tvar6 ==0)       /*variable bitmap format */
{

        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCNv */
        tvar4 = (I_U8) tvar7 |142;
        tvar3 = tvar4 & 191;
        
        bitstring[2] = tvar3;

        tvar8 = sysInfo->origARFCN >> 1; /*middle part of origARFCNv */
        tvar4 = (I_U8) tvar8 & 255;
        bitstring[3] = tvar4;

        tvar9 = sysInfo->origARFCN >> 9;   /*low part of origARFCNv */
        tvar4 = (I_U8) tvar9 & 511;

        tvar1 = sysInfo->ARFCN[1]<<6;
        tvar2 = tvar1 | sysInfo->ARFCN[2]<<5;
        tvar1 = tvar2 | sysInfo->ARFCN[3]<<4;
        tvar2 = tvar1 | sysInfo->ARFCN[4]<<3;
        tvar1 = tvar2 | sysInfo->ARFCN[5]<<2;
        tvar2 = tvar1 | sysInfo->ARFCN[6]<<1;
        tvar1 = tvar2 | sysInfo->ARFCN[7];

        bitstring[4] = tvar4 << 7 | tvar1;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[8]<<7;
        for(tvar3 = 9; tvar3<=14; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
             }
        tvar2 = tvar1 | sysInfo->ARFCN[15];
        bitstring[5] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[16]<<7;
        for(tvar3 = 17; tvar3<=22; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[23];
        bitstring[6] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[24]<<7;
        for(tvar3 = 25; tvar3<=30; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[21];
        bitstring[7] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[32]<<7;
        for(tvar3 = 33; tvar3<=38; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[39];
        bitstring[8] = tvar2;
        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[40]<<7;
        for(tvar3 = 41; tvar3<=46; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[47];
        bitstring[9] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[48]<<7;
        for(tvar3 = 49; tvar3<=54; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[55];
        bitstring[10] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[56]<<7;
        for(tvar3 = 57; tvar3<=62; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[63];
        bitstring[11] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[64]<<7;
        for(tvar3 = 65; tvar3<=70; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
            tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[71];
        bitstring[12] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[72]<<7;
        for(tvar3 = 73; tvar3<=78; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[79];
        bitstring[13] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[80]<<7;
        for(tvar3 = 81; tvar3<=86; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[87];
        bitstring[14] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[88]<<7;
        for(tvar3 = 89; tvar3<=84; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[95];
        bitstring[15] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[96]<<7;
        for(tvar3 = 97; tvar3<=102; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[103];
        bitstring[16] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[104]<<7;
        for(tvar3 = 105; tvar3<=110; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[111];
        bitstring[17] = tvar2;

} /*end of variable bitmap format */

/*rachdescription */
tvar1 = sysInfo->maxRetans<<6;
tvar2 = tvar1 | sysInfo->txInteger<<2;
tvar1 = tvar2 | sysInfo->cellBarAccess<<1;
tvar2 = tvar1 | sysInfo->re;
bitstring[18] = tvar2;

tvar1 = sysInfo->acClass[15]<<7;
tvar2 = tvar1 | sysInfo->acClass[14]<<6;
tvar1 = tvar2 | sysInfo->acClass[13]<<5;
tvar2 = tvar1 | sysInfo->acClass[12]<<4;
tvar1 = tvar2 | sysInfo->acClass[11]<<3;
tvar2 = tvar1 | sysInfo->ec<<2;
tvar1 = tvar2 | sysInfo->acClass[9]<<1;
tvar2 = tvar1 | sysInfo->acClass[8];
bitstring[19] = tvar2;

tvar4 = 6;
tvar1 = sysInfo->acClass[7]<<7;
for(tvar3 = 6; tvar3>=1; tvar3--)
    {
         tvar2 = tvar1 | sysInfo->acClass[tvar3]<<tvar4;
         tvar1 = tvar2;
         tvar4--;
     }
tvar2 = tvar1 | sysInfo->acClass[0];
bitstring[20] = tvar2;

// bitstring[21] = 0;  /*Reset octet for SysInfo 1 */

bitstring[21] = 43;

/* have uncommented this piece of code - Aricent*/
if(sysInfo->NCH != 0)
{
    tvar1 = 128;
    tvar2 = sysInfo->NCHPosition<<2;
    tvar2 = tvar2 | tvar1;
    tvar1 = sysInfo->BandIndicator<<1;
    /* Added by Aricent (spare padding)*/
    tvar3 = tvar2 | tvar1| 1;
    bitstring[21] = tvar3;

}
else
{
    tvar1 = sysInfo->BandIndicator<<6 ;
   /* Added spare padding by aricent */
    bitstring[21] = tvar1 |SI_SPARE;
}


 l2PseudoLength =21;
 l2PseudoLength = l2PseudoLength << 2 | 1;
 *len = 23;
 buff[0] = l2PseudoLength;
 memcpy(buff+1, bitstring, 22);


 return 0; /* Added by Aricent */
}
/***********************************************************************************
*  Function Name   : EncodeSysInformation2 
*  Args            : 1. SystemInfo2 structure pointer
*                    2. pointer to buff
*                    3. length of buffer
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 2 message buffer
***********************************************************************************/

/*I_S32  SysInfoEncoder::EncodeSysInformation2( SystemInfo2 *sysInfo, I_U8 *buff, I_U16 *len)
*/I_S32  EncodeSysInformation2( SystemInfo2 *sysInfo, I_U8 *buff, I_U16 *len)
{

 I_U8 tvar1 = 0;
 I_U8 tvar2 = 0;
 I_U8 tvar3 = 0;
 I_U8 tvar4 = 0;
 I_U8 tvar5 = 0;
 I_U8 tvar6 = 0;

 I_U16 tvar7 = 0;
 I_U16 tvar8 = 0;
 I_U16 tvar9 = 0;

 I_U8 format1[22] = "bitmap0format";
 I_U8 format2[22] = "range1024format";
 I_U8 format3[22] = "range512format";
 I_U8 format4[22] = "range256format";
 I_U8 format5[22] = "range128format";
 I_U8 format6[22] = "variablebitmapformat";
 I_U8 firstByte;
 I_U8 bitstring[22];  /* modified the value of bitstring length by Aricent */
 I_U8 l2PseudoLength;
 I_U8 S_ARFCN = 119;
 I_U8 E_ARFCN = 113;
 I_U8 i;

 /* Added By Aricent */
 memset(bitstring, 0, sizeof(bitstring));
 /* End of Adding */

 tvar1 = sysInfo->skipIndicator<<4 ;
 firstByte = tvar1|sysInfo->protocolDiscriminator;

 bitstring[0] = firstByte;
 bitstring[1] = sysInfo->messageType;


/*cellChannelDescription */

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format1);


if(tvar6==0)       /* bitmap 0 format */
{

        tvar3 = sysInfo->ext_ind<<5;
        tvar4 = tvar3 | sysInfo->ba_ind<<4;
        tvar1 = tvar4 | sysInfo->ARFCN[123]<<3;
        tvar2 = tvar1 | sysInfo->ARFCN[122]<<2;
        tvar1 = tvar2 | sysInfo->ARFCN[121]<<1;
        tvar2 = tvar1 | sysInfo->ARFCN[120];
        tvar1 = tvar2 &  63;
        bitstring[2] = tvar1;
        
        for(i= 3; i<=17; i++)
        {
            tvar4 = 6;
            tvar1 = sysInfo->ARFCN[S_ARFCN]<<7;
            for(tvar3 = S_ARFCN - 1; tvar3>=E_ARFCN; tvar3--)
            {
                tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                tvar1 = tvar2;
                tvar4--;
            }
            tvar2 = tvar1 | sysInfo->ARFCN[E_ARFCN -1];
            bitstring[i] = tvar2;
            tvar1= 0;
            tvar2= 0;
            tvar3 =0;
            S_ARFCN = S_ARFCN -8;
            E_ARFCN = E_ARFCN -8;
        }//for




}/*end of bitmap0 format*/

tvar6 = strcmp((const char*)sysInfo->formatIndicator,(const char*) format2);

if(tvar6 ==0)       /*range 1024 format */
{
        
        I_S32   index = 0; /* initialized to 0 by Aricent */
        I_S32   len = 0 , i =0;
        I_S32   n = 0 ;
        I_S32   range = 1024;
        I_S32   nW[28];
        /*I_S32   set[16]; Changed by Aricent */
        I_S32  set[16]; 

        for(i=0; i<28; i++)
        {
         nW[i] = 0;

        }

        for(i=0; i<16; i++)
        {
         set[i] = 0;

        }

        if(sysInfo->f1 != -1)
        {
          set[0]=   sysInfo->f1;
          len++;
        }
        if(sysInfo->f2 != -1)
        {
          set[1]=   sysInfo->f2;
          len++;
        }

        if(sysInfo->f3 != -1)
        {
          set[2]=   sysInfo->f3;
          len++;
        }
        if(sysInfo->f4 != -1)
        {
          set[3]=   sysInfo->f4;
          len++;
        }
        if(sysInfo->f5 != -1)
        {
          set[4]=   sysInfo->f5;
          len++;
        }
        if(sysInfo->f6 != -1)
        {
          set[5]=   sysInfo->f6;
          len++;
        }
        if(sysInfo->f7 != -1)
        {
          set[6]=   sysInfo->f7;
          len++;
        }
        if(sysInfo->f8 != -1)
        {
          set[7]=   sysInfo->f8;
          len++;
        }
        if(sysInfo->f9 != -1)
        {
          set[8]=   sysInfo->f9;
          len++;
        }
        if(sysInfo->f10 != -1)
        {
          set[9]=   sysInfo->f10;
          len++;
        }
        if(sysInfo->f11 != -1)
        {
          set[10]=   sysInfo->f11;
          len++;
        }
        if(sysInfo->f12 != -1)
        {
          set[11]=   sysInfo->f12;
          len++;
        }
        if(sysInfo->f13 != -1)
        {
          set[12]=   sysInfo->f13;
          len++;
        }
        if(sysInfo->f14 != -1)
        {
          set[13]=   sysInfo->f14;
          len++;
        }
        if(sysInfo->f15 != -1)
        {
          set[14]=   sysInfo->f15;
          len++;
        }
        if(sysInfo->f16 != -1)
        {
          set[15]=   sysInfo->f16;
          len++;
        }

        for(i = 0; i<len; i++)
        {
           if(set[i]  == 0)
           {
               n++;
           }
        }
        if(n == 0)
        {
           for(i= 0; i<len; i++)
           {
              set[i] = set[i] -1;
              index = 1;
              range = 1023;
              sysInfo->f0 =0  ;
           }
        }
        else
        {
            for(i= 0; i<len; i++)
            {
               set[i] = set[i++] ;
               index = 1;
               range = 1024 ;
               sysInfo->f0 = 1 ;
            }
        }

        Encode_san(index, set, len, range, nW);

        sysInfo->w1 = nW[0];
        sysInfo->w2 = nW[1];
        sysInfo->w3 = nW[2];
        sysInfo->w4 = nW[3];
        sysInfo->w5 = nW[4];
        sysInfo->w6 = nW[5];
        sysInfo->w7 = nW[6];
        sysInfo->w8 = nW[7];
        sysInfo->w9 = nW[8];
        sysInfo->w10 = nW[9];
        sysInfo->w11 = nW[10];
        sysInfo->w12 = nW[11];
        sysInfo->w13 = nW[12];
        sysInfo->w14 = nW[13];
        sysInfo->w15 = nW[14];
        sysInfo->w16 = nW[15];
         
        tvar1 = sysInfo->ext_ind<<5;
        tvar2 = tvar1 | sysInfo->ba_ind<<4;

        tvar3 = tvar2 | sysInfo->f0<<2;

        tvar7 = sysInfo->w1 >> 8;     /*High part of w1*/
        tvar8 = sysInfo->w1 & 255;     /*Low part of w1*/

        tvar4 = tvar3 | (I_U8) tvar7;
        tvar5 = tvar4 |128;
        tvar4 = tvar5 & 191;

        bitstring[2] = tvar4;
        bitstring[3] = (I_U8) tvar8;

        tvar7 = sysInfo->w2  >> 1;     /*High part of w2*/
        bitstring[4] = (I_U8) tvar7;

        tvar7 = sysInfo->w2 & 1;       /*Low part of w2*/

        tvar9 = sysInfo->w3 >> 2;     /*High part of w3*/
        bitstring[5] = (I_U8) tvar7<<7 | tvar9;

        tvar7 = sysInfo->w3 & 7;        /*Low part of w3*/

        tvar3 = sysInfo->w4 >> 2;     /*High part of w4*/
        bitstring[6] = (I_U8) tvar7<<6 | tvar3;
        tvar4 = sysInfo->w4 & 3;        /*Low part of w4*/

        tvar1 = sysInfo->w5 >> 2;     /*High part of w5*/
        bitstring[7] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w5 & 3;        /*Low part of w5*/

        tvar3 = sysInfo->w6 >> 2;     /*High part of w6*/
        bitstring[8] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w6 & 3;        /*Low part of w6*/

        tvar1 = sysInfo->w7 >> 2;     /*High part of w7*/
        bitstring[9] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w7& 3;       /*Low part of w7*/

        tvar3 = sysInfo->w8 >> 1;     /*High part of w8*/
        bitstring[10] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w8 & 1;       /*Low part of w8*/

        tvar1 = tvar4 << 7 | sysInfo->w9;
        bitstring[11] = tvar1;

        tvar2 = sysInfo->w10;

        tvar3 = sysInfo->w11 >> 6;     /*High part of w11*/
        bitstring[12] = tvar2<<1 | tvar3;
        tvar4 = sysInfo->w11& 63;       /*Low part of w11*/

        tvar1 = sysInfo->w12 >> 5;     /*High part of w12*/
        bitstring[13] = tvar4<<2 | tvar1;
        tvar2 = sysInfo->w12& 31;       /*Low part of w12*/

        tvar3 = sysInfo->w13 >> 4;     /*High part of w13*/
        bitstring[14] = tvar2<<3 | tvar3;
        tvar4 = sysInfo->w13& 15;       /*Low part of w13*/

        tvar1 = sysInfo->w14 >> 3;     /*High part of w14*/
        bitstring[15] = tvar4<<4 | tvar1;
        tvar2 = sysInfo->w14& 7;        /*Low part of w14*/

        tvar3 = sysInfo->w15 >> 2;     /*High part of w15*/
        bitstring[16] = tvar2<<5 | tvar3;
        tvar4 = sysInfo->w15& 7;        /*Low part of w15*/

        tvar1 = sysInfo->w16 ;
        bitstring[17] = tvar4<<6 | tvar1;

}/*end of 1024 format */

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format3);


if ( (tvar6 == 0) && (sysInfo->origARFCN != 0) )      /*range 512 format */
{
    
        tvar1 = sysInfo->ext_ind<<5;
        tvar2 = tvar2 | sysInfo->ba_ind<<4;

        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCN512 */
        tvar4 = (I_U8) tvar7 |136;
      /*   tvar4 = tvar4 & 207; */
         
        tvar4 = tvar4 | tvar2;

        /*tvar3 = tvar4 & 185;
        bitstring[2] = tvar3; */
        bitstring[2] = tvar4;

        tvar7 = sysInfo->origARFCN >> 1;   /*middle part of origARFCN512 */
        tvar4 = (I_U8) tvar7 & 255;
        bitstring[3] = tvar4;
    
         /*tvar7 = sysInfo->origARFCN >> 9;*/   /*low part of origARFCN512 */
        tvar7 = sysInfo->origARFCN & 1;
        /*tvar4 = (I_U8) tvar3 & 511; */
        tvar4 = (I_U8)tvar7;

        tvar8 = sysInfo->w1>> 2;  /*High part of w1*/
        tvar9 = sysInfo->w1 & 3 ; /*low part of w1*/
        tvar3 = tvar4 << 7 | (I_U16) tvar8;
        bitstring[4] = tvar3;

        tvar3 = sysInfo->w2>> 2;  /*High part of w2*/
        bitstring[5] = (I_U16) tvar9 <<6 | tvar3;
        tvar4 = sysInfo->w2 & 3 ; /*low part of w2*/

        tvar1 = sysInfo->w3>> 2;  /*High part of w3*/
        bitstring[6] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w3 & 3 ; /*low part of w3*/

        tvar3 = sysInfo->w4>> 1;  /*High part of w4*/
        bitstring[7] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w4 & 1 ; /*low part of w4*/

        tvar1 = sysInfo->w5;
        tvar2 = tvar4 << 7 | sysInfo->w5;
        bitstring[8] = tvar2;

        tvar1 = sysInfo->w6;

        tvar3 = sysInfo->w7>> 6;  /*High part of w7*/
        /*bitstring[9] = tvar1<<1 | tvar1;*/
        bitstring[9] = tvar1<<1 | tvar3;
        tvar4 = sysInfo->w7 & 63 ; /*low part of w7*/

        tvar1 = sysInfo->w8>> 4;  /*High part of w8*/
        /*bitstring[10] = tvar4<<2 | tvar4;*/
        bitstring[10] = tvar4<<2 | tvar1;
        tvar2 = sysInfo->w8 & 15 ; /*low part of w8*/

        tvar3 = sysInfo->w9>> 2;  /*High part of w9*/
        /*bitstring[11] = tvar2<<4 | tvar2;*/
        bitstring[11] = tvar2<<4 | tvar3;
        tvar4 = sysInfo->w9 & 3 ; /*low part of w9*/

        tvar1 = sysInfo->w10;
        tvar2 = tvar4<<6 | tvar1;
        bitstring[12] = tvar2;

        tvar3 = sysInfo->w11 ;

        tvar1 = sysInfo->w12 >> 4;  /*High part of w12*/
        bitstring[13] = tvar3<<2 | tvar1;
        tvar2 = sysInfo->w12 & 15 ; /*low part of w12*/
        tvar3 = sysInfo->w13 >> 2;  /*High part of w13*/
        /*bitstring[14] = tvar3<<4 | tvar3;*/
        bitstring[14] = tvar2<<4 | tvar3;
        tvar4 = sysInfo->w13 & 3 ; /*low part of w13*/

        tvar1 = sysInfo->w14;
        tvar2 = tvar4<<6 |tvar1 ;
        bitstring[15] = tvar2;
        tvar3 = sysInfo->w15;

        /*tvar1 = sysInfo->w16 >> 4;*/  /*High part of w16*/
        tvar1 = sysInfo->w16 >> 3;  /*High part of w16*/
        bitstring[16] = tvar3<<2 | tvar1;
        /*tvar2 = sysInfo->w16 & 15*/ ; /*low part of w16*/
        tvar2 = sysInfo->w16 & 7 ; /*low part of w16*/

        tvar3 = sysInfo->w17;
        tvar4 = tvar2 << 5 | tvar3;
        bitstring[17] =  tvar4;

 
        #if 0
        tvar7 = sysInfo->origARFCN >> 9;   /*low part of origARFCN512 */
        tvar4 = (I_U8) tvar3 & 511;

        tvar8 = sysInfo->w1>> 2;  /*High part of w1*/
        tvar9 = sysInfo->w1 & 3 ; /*low part of w1*/
        tvar3 = tvar4 << 7 | (I_U16) tvar8;
        bitstring[4] = tvar3;

        tvar3 = sysInfo->w2>> 2;  /*High part of w2*/
        bitstring[5] = (I_U16) tvar9 <<6 | tvar3;
        tvar4 = sysInfo->w2 & 3 ; /*low part of w2*/

        tvar1 = sysInfo->w3>> 2;  /*High part of w3*/
        bitstring[6] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w3 & 3 ; /*low part of w3*/

        tvar3 = sysInfo->w4>> 1;  /*High part of w4*/
        bitstring[7] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w4 & 1 ; /*low part of w4*/

        tvar1 = sysInfo->w5;
        tvar2 = tvar4 << 7 | sysInfo->w5;
        bitstring[8] = tvar2;

        tvar1 = sysInfo->w6;

        tvar3 = sysInfo->w7>> 6;  /*High part of w7*/
        bitstring[9] = tvar1<<1 | tvar1;
        tvar4 = sysInfo->w7 & 63 ; /*low part of w7*/

        tvar1 = sysInfo->w8>> 4;  /*High part of w8*/
        bitstring[10] = tvar4<<2 | tvar4;
        tvar2 = sysInfo->w8 & 15 ; /*low part of w8*/

        tvar3 = sysInfo->w9>> 2;  /*High part of w9*/
        bitstring[11] = tvar2<<4 | tvar2;
        tvar4 = sysInfo->w9 & 3 ; /*low part of w9*/

        tvar1 = sysInfo->w10;
        tvar2 = tvar4<<6 | tvar1;
        bitstring[12] = tvar2;

        tvar3 = sysInfo->w11 ;

        tvar1 = sysInfo->w12 >> 4;  /*High part of w12*/
        bitstring[13] = tvar3<<2 | tvar1;
        tvar2 = sysInfo->w12 & 15 ; /*low part of w12*/

        tvar3 = sysInfo->w13 >> 2;  /*High part of w13*/
        bitstring[14] = tvar3<<4 | tvar3;
        tvar4 = sysInfo->w13 & 3 ; /*low part of w13*/

        tvar1 = sysInfo->w14;
        tvar2 = tvar4<<6 |tvar1 ;
        bitstring[15] = tvar2;
        tvar3 = sysInfo->w15;

        tvar1 = sysInfo->w16 >> 4;  /*High part of w16*/
        bitstring[16] = tvar3<<2 | tvar1;
        tvar2 = sysInfo->w16 & 15 ; /*low part of w16*/

        tvar3 = sysInfo->w17;
        tvar4 = tvar2 << 5 | tvar3;
        bitstring[17] =  tvar4;
       #endif

}  /*end of range512w format */


tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format4);

if(tvar6==0)       /*range 256 format */
{


        tvar3 = sysInfo->ext_ind<<5;
        tvar2 = tvar3 | sysInfo->ba_ind<<4;

        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCN512 */
        tvar4 = (I_U8) tvar7 |138;
        tvar4 = tvar4 | tvar2; 
        tvar1 = tvar4 & 187 ;
         
        bitstring[2] = tvar1;

        tvar8 = sysInfo->origARFCN >> 1;   /*middle part of origARFCN512 */
        tvar4 = (I_U8) tvar8 & 255;
        bitstring[3] = tvar4;

        tvar9 = sysInfo->origARFCN >> 9;   /*low part of origARFCN512 */
        tvar4 = (I_U8) tvar9 & 511;

        tvar1 = sysInfo->w1 >> 1;  /*high part of w1 */
        tvar2 = sysInfo->w1 & 1;  /*low part of w1 */

        tvar3 = sysInfo->w2;
        tvar4 = tvar2<<7 |tvar3;
        bitstring[4] =  tvar4;

        tvar1 = sysInfo->w3;

        tvar3 = sysInfo->w4 >> 4;  /*high part of w4 */
        bitstring[5] = tvar1 << 1 | tvar3;
        tvar4 = sysInfo->w4 & 15;  /*low part of w4 */

        tvar1 = sysInfo->w5 >> 3;  /*high part of w5 */
        bitstring[6] = tvar4 << 3 | tvar1;
        tvar2 = sysInfo->w5 & 7;  /*low part of w5 */

        tvar3 = sysInfo->w6 >> 5;  /*high part of w6 */
        bitstring[7] = tvar2 << 5 | tvar3;
        tvar4 = sysInfo->w6 & 1;  /*low part of w6 */

        tvar1 = sysInfo->w7<<1;
        tvar5 = tvar4<< 7 | tvar1;

        tvar2 = sysInfo->w8 >> 4;  /*high part of w8 */
        bitstring[8] = tvar5 | tvar2;
        tvar3 = sysInfo->w8 & 15;  /*low part of w8 */

        tvar1 = sysInfo->w9 >> 4;  /*high part of w9 */
        bitstring[9] = tvar3<<4 | tvar1;
        tvar4 = sysInfo->w9 & 1;  /*low part of w9 */

        tvar1 = sysInfo->w10<<2;
        tvar5 = tvar4<<7  | tvar1 ;

        tvar2 = sysInfo->w11 >> 3;  /*high part of w11 */
        bitstring[10] = tvar5 | tvar2;
        tvar3 = sysInfo->w11 & 7;  /*low part of w11 */

        tvar1 = sysInfo->w12;
        bitstring[11] = tvar3<<4  | tvar1;
    
        tvar1 = sysInfo->w13;
        tvar2 = sysInfo->w14 >> 2; /*high part of w14*/
        tvar3 = sysInfo->w14 & 3; /*low part of w14 */

        bitstring[12] =  tvar1 << 3 |tvar2 ;

        tvar1 = sysInfo->w15;
        tvar2 = sysInfo->w16 >> 3; /*high part of w16*/
        tvar4 = sysInfo->w16 & 7; /*low part of w16 */

        tvar5 = tvar3<<5 | tvar1;
        bitstring[13] = tvar3 << 5 | tvar1 <<1 |tvar2;

        tvar1 = sysInfo->w17;
        tvar2 = sysInfo->w18 >> 3; /*high part of w18*/
        tvar3 = sysInfo->w18 & 7; /*low part of w18 */

        bitstring[14] = tvar4 << 5 | tvar1 <<1 |tvar2;

        tvar1 = sysInfo->w19;
        tvar2 = sysInfo->w20 >> 3; /*high part of w20*/
        tvar4 = sysInfo->w20 & 7; /*low part of w20 */

        bitstring[15] = tvar3 << 5 | tvar1 <<1 |tvar2;

        tvar1 = sysInfo->w21;
        bitstring[16] = tvar4 << 5 | tvar1<<1;
}/* end of 256 format*/

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format5);

if(tvar6 ==0)       /*range 128 format */
{

        tvar1 = sysInfo->ext_ind<<5;
        tvar2 = tvar2 | sysInfo->ba_ind<<4;

        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCN128 */
        tvar3 = (I_U8) tvar7 |140;
        tvar3 = tvar3 | tvar2;  
        tvar4 = tvar3 & 189;
 
        bitstring[2] = tvar4;
        
        tvar8 = sysInfo->origARFCN >> 1;   /*middle part of origARFCN128 */
        tvar4 = (I_U8) tvar8 & 255;
        bitstring[3] = tvar4;

        tvar9 = sysInfo->origARFCN >> 9;   /*low part of origARFCN128 */
        tvar4 = (I_U8) tvar9 & 511;

        tvar1 = sysInfo->w1;
        bitstring[4] = tvar4 << 1 | tvar1;

        tvar2 = sysInfo->w2;
        tvar3 = sysInfo->w3 >>4 ; /*high part of w3 */
        tvar4 = sysInfo->w3 & 15 ; /*low part of w3*/

        bitstring[5] = tvar2 << 2 |tvar3;

        tvar1 = sysInfo->w4 >>1 ; /*high part of w4 */
        tvar2 = sysInfo->w4 & 1 ; /*low part of w4 */

        bitstring[6] = tvar4 << 4 |tvar1;

        tvar1 = sysInfo->w5;

        tvar3 = sysInfo->w6 >>2 ; /*high part of w6 */
        tvar4 = sysInfo->w6 & 7 ; /*low part of w6 */

        bitstring[7] = tvar2 <<7 | tvar1 <<2 |tvar3;

        bitstring[8] = tvar4 <<5 | sysInfo->w7;

        bitstring[9] = sysInfo->w8 <<4 |  sysInfo->w9;

        bitstring[10] = sysInfo->w10 <<4 |  sysInfo->w11;

        bitstring[11] = sysInfo->w12 <<4 |  sysInfo->w13;

       bitstring[12] = sysInfo->w14 <<4 |  sysInfo->w15;

        tvar1 = sysInfo->w16;
        tvar2 = sysInfo->w17;

        tvar3 = sysInfo->w18 >>1 ; /*high part of w18 */
        tvar4 = sysInfo->w18 & 1 ; /*low part of w18 */

        bitstring[13] = tvar1 << 5 | tvar2<<2 |tvar3;

        tvar1 = sysInfo->w19;
        tvar2 = sysInfo->w20;

        tvar3 = sysInfo->w21 >>2 ; /*high part of w21 */
        tvar5 = sysInfo->w21 & 3 ; /*low part of w21 */

        bitstring[14] = tvar4 <<7 | tvar1 <<4 | tvar2 <<1 |tvar3;

        tvar1 = sysInfo->w22;
        tvar2 = sysInfo->w23;

        bitstring[15] = tvar5<<6 | tvar1 <<3 | tvar2;

        tvar1 = sysInfo->w26 >>1 ; /*high part of w26 */
        tvar2 = sysInfo->w26 & 1 ; /*low part of w26 */

        tvar3 = sysInfo->w24;
        tvar4 = sysInfo->w25;

        bitstring[16] =  tvar3 <<4 |tvar4 <<2 |tvar1;

        tvar1 = sysInfo->w27;
        tvar2 = sysInfo->w28;

        bitstring[17]= tvar4<<7 |tvar1<<4 |tvar2<<1;
}/*end of 128 format */

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format6);

if(tvar6 ==0)       /*variable bitmap format */
{

        tvar1 = sysInfo->ext_ind<<5;
        tvar2 = tvar1 | sysInfo->ba_ind<<4;

        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCNv */
        tvar4 = (I_U8) tvar7 |142;
        tvar4 = tvar4 |tvar2;
        tvar3 = tvar4 & 191;
        
        bitstring[2] = tvar3;

        tvar8 = sysInfo->origARFCN >> 1; /*middle part of origARFCNv */
        tvar4 = (I_U8) tvar8 & 255;
        bitstring[3] = tvar4;

        tvar9 = sysInfo->origARFCN >> 9;   /*low part of origARFCNv */
        tvar4 = (I_U8) tvar9 & 511;

        tvar1 = sysInfo->ARFCN[1]<<6;
        tvar2 = tvar1 | sysInfo->ARFCN[2]<<5;
        tvar1 = tvar2 | sysInfo->ARFCN[3]<<4;
        tvar2 = tvar1 | sysInfo->ARFCN[4]<<3;
        tvar1 = tvar2 | sysInfo->ARFCN[5]<<2;
        tvar2 = tvar1 | sysInfo->ARFCN[6]<<1;
        tvar1 = tvar2 | sysInfo->ARFCN[7];

        bitstring[4] = tvar4 << 7 | tvar1;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[8]<<7;
        for(tvar3 = 9; tvar3<=14; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
             }
        tvar2 = tvar1 | sysInfo->ARFCN[15];
        bitstring[5] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[16]<<7;
        for(tvar3 = 17; tvar3<=22; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[23];
        bitstring[6] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[24]<<7;
        for(tvar3 = 25; tvar3<=30; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[21];
        bitstring[7] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[32]<<7;
        for(tvar3 = 33; tvar3<=38; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[39];
        bitstring[8] = tvar2;
        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[40]<<7;
        for(tvar3 = 41; tvar3<=46; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[47];
        bitstring[9] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[48]<<7;
        for(tvar3 = 49; tvar3<=54; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[55];
        bitstring[10] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[56]<<7;
        for(tvar3 = 57; tvar3<=62; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[63];
        bitstring[11] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[64]<<7;
        for(tvar3 = 65; tvar3<=70; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
            tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[71];
        bitstring[12] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[72]<<7;
        for(tvar3 = 73; tvar3<=78; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[79];
        bitstring[13] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[80]<<7;
        for(tvar3 = 81; tvar3<=86; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[87];
        bitstring[14] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[88]<<7;
        for(tvar3 = 89; tvar3<=84; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[95];
        bitstring[15] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[96]<<7;
        for(tvar3 = 97; tvar3<=102; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[103];
        bitstring[16] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[104]<<7;
        for(tvar3 = 105; tvar3<=110; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[111];
        bitstring[17] = tvar2;

} /*end of variable bitmap format */


/*NCC description */
tvar4 = 6;
tvar1 = sysInfo->NCC[7]<<7;
for(tvar3 = 6; tvar3>=1; tvar3--)
   {
        tvar2 = tvar1 | sysInfo->NCC[tvar3]<<tvar4;
        tvar1 = tvar2;
        tvar4--;
    }
tvar2 = tvar1 | sysInfo->NCC[0];
bitstring[18] = tvar2;


/*rachdescription */
  tvar1 = sysInfo->maxRetans<<6;
  tvar2 = tvar1 | sysInfo->txInteger<<2;
  tvar1 = tvar2 | sysInfo->cellBarAccess<<1;
  tvar2 = tvar1 | sysInfo->re;
  bitstring[19] = tvar2;

  tvar1 = sysInfo->acClass[15]<<7;
  tvar2 = tvar1 | sysInfo->acClass[14]<<6;
  tvar1 = tvar2 | sysInfo->acClass[13]<<5;
  tvar2 = tvar1 | sysInfo->acClass[12]<<4;
  tvar1 = tvar2 | sysInfo->acClass[11]<<3;
  tvar2 = tvar1 | sysInfo->ec<<2;
  tvar1 = tvar2 | sysInfo->acClass[9]<<1;
  tvar2 = tvar1 | sysInfo->acClass[8];
  bitstring[20] = tvar2;

  tvar4 = 6;
  tvar1 = sysInfo->acClass[7]<<7;
  for(tvar3 = 6; tvar3>=1; tvar3--)
    {
         tvar2 = tvar1 | sysInfo->acClass[tvar3]<<tvar4;
         tvar1 = tvar2;
         tvar4--;
     }
  tvar2 = tvar1 | sysInfo->acClass[0];
  bitstring[21] = tvar2;

  l2PseudoLength =22;
  l2PseudoLength = l2PseudoLength << 2 | 1;
  *len = 23;
  buff[0] = l2PseudoLength;
  memcpy(buff+1, bitstring, 22);


  return 0; /* Added by Aricent */

}
/***********************************************************************************
*  Function Name   : EncodeSysInformation2ter 
*  Args            : 1. SystemInfo2ter structure pointer
*                    2. pointer to buff
*                    3. length of buffer
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 2ter message buffer
***********************************************************************************/

I_S32  EncodeSysInformation2ter( SystemInfo2ter *sysInfo, I_U8 *buff, I_U16 *len)
{

   I_U8 tvar1 = 0;
   I_U8 tvar2 = 0;
   I_U8 tvar3 = 0;
   I_U8 tvar4 = 0;
   I_U8 tvar6 = 0;

   I_U16 tvar7 = 0;
   I_U16 tvar8 = 0;
   I_U16 tvar9 = 0;

   I_U8 format1[FORMAT_LEN] = "bitmap0format";
   I_U8 format2[FORMAT_LEN] = "range512format";
   I_U8 firstByte;
   I_U8 bitstring[BITSTRING_LEN]; 
   I_U8 l2PseudoLength;
   I_U8 S_ARFCN = 119;
   I_U8 E_ARFCN = 113;
   I_U8 i;

 /* Added By Aricent */
 memset(bitstring, 0, sizeof(bitstring));
 /* End of Adding */

   tvar1 = sysInfo->skipIndicator<<4 ;
   firstByte = tvar1|sysInfo->protocolDiscriminator;

   bitstring[0] = firstByte;
   bitstring[1] = sysInfo->messageType;


/*cellChannelDescription */

   tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format1);


   if(tvar6==0)       /* bitmap 0 format */
   {

      tvar3 = sysInfo->multibandReporting<<5;
      tvar4 = tvar3 | sysInfo->baInd<<4;
      tvar1 = tvar4 | sysInfo->ARFCN[123]<<3;
      tvar2 = tvar1 | sysInfo->ARFCN[122]<<2;
      tvar1 = tvar2 | sysInfo->ARFCN[121]<<1;
      tvar2 = tvar1 | sysInfo->ARFCN[120];
//    tvar1 = tvar2 &  63;	Mantis 4715
      bitstring[2] = tvar1;
        
      for(i= 3; i<=17; i++)
      {
         tvar4 = 6;
         tvar1 = sysInfo->ARFCN[S_ARFCN]<<7;
         for(tvar3 = S_ARFCN - 1; tvar3>=E_ARFCN; tvar3--)
         {
            tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
            tvar1 = tvar2;
            tvar4--;
         }
         tvar2 = tvar1 | sysInfo->ARFCN[E_ARFCN -1];
         bitstring[i] = tvar2;
         tvar1= 0;
         tvar2= 0;
         tvar3 =0;
         S_ARFCN = S_ARFCN -8;
         E_ARFCN = E_ARFCN -8;
      }//for

   }/*end of bitmap0 format*/


   tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format2);

   if ( (tvar6 == 0) && (sysInfo->origARFCN != 0) )       /*range 512 format */
   {
    
      //tvar1 = sysInfo->ext_ind<<5;
      tvar1 = sysInfo->multibandReporting<<5;
      tvar2 = tvar2 | sysInfo->baInd<<4;

       /* Commented By Aricent 
      tvar7 = sysInfo->origARFCN >>9; *//*high part of origARCN512 */
      tvar7 = sysInfo->origARFCN & 1023;
      tvar6 = (I_U8)(tvar7>>9);

      tvar4 = tvar1|tvar2|tvar6|136;
      /* commented By Aricent 
      tvar4 = tvar4 & 207;
         
      tvar4 = tvar4 | tvar2;

      tvar3 = tvar4 & 185; */
      bitstring[2] = tvar4;

      tvar8 = sysInfo->origARFCN >> 1;   /*middle part of origARFCN512 */
      tvar4 = (I_U8) tvar8 & 255;
      bitstring[3] = tvar4;


       /*tvar7 = sysInfo->origARFCN >> 9;*/   /*low part of origARFCN512 */
        tvar7 = sysInfo->origARFCN & 1;
        /*tvar4 = (I_U8) tvar3 & 511; */
        tvar4 = (I_U8)tvar7;

        tvar8 = sysInfo->w1>> 2;  /*High part of w1*/
        tvar9 = sysInfo->w1 & 3 ; /*low part of w1*/
        tvar3 = tvar4 << 7 | (I_U16) tvar8;
        bitstring[4] = tvar3;

        tvar3 = sysInfo->w2>> 2;  /*High part of w2*/
        bitstring[5] = (I_U16) tvar9 <<6 | tvar3;
        tvar4 = sysInfo->w2 & 3 ; /*low part of w2*/

        tvar1 = sysInfo->w3>> 2;  /*High part of w3*/
        bitstring[6] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w3 & 3 ; /*low part of w3*/

        tvar3 = sysInfo->w4>> 1;  /*High part of w4*/
        bitstring[7] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w4 & 1 ; /*low part of w4*/

        tvar1 = sysInfo->w5;
        tvar2 = tvar4 << 7 | sysInfo->w5;
        bitstring[8] = tvar2;

        tvar1 = sysInfo->w6;

        tvar3 = sysInfo->w7>> 6;  /*High part of w7*/
        /*bitstring[9] = tvar1<<1 | tvar1;*/
        bitstring[9] = tvar1<<1 | tvar3;
        tvar4 = sysInfo->w7 & 63 ; /*low part of w7*/

        tvar1 = sysInfo->w8>> 4;  /*High part of w8*/
        /*bitstring[10] = tvar4<<2 | tvar4;*/
        bitstring[10] = tvar4<<2 | tvar1;
        tvar2 = sysInfo->w8 & 15 ; /*low part of w8*/

        tvar3 = sysInfo->w9>> 2;  /*High part of w9*/
        /*bitstring[11] = tvar2<<4 | tvar2;*/
        bitstring[11] = tvar2<<4 | tvar3;
        tvar4 = sysInfo->w9 & 3 ; /*low part of w9*/

        tvar1 = sysInfo->w10;
        tvar2 = tvar4<<6 | tvar1;
        bitstring[12] = tvar2;

        tvar3 = sysInfo->w11 ;

        tvar1 = sysInfo->w12 >> 4;  /*High part of w12*/
        bitstring[13] = tvar3<<2 | tvar1;
        tvar2 = sysInfo->w12 & 15 ; /*low part of w12*/
        tvar3 = sysInfo->w13 >> 2;  /*High part of w13*/
        /*bitstring[14] = tvar3<<4 | tvar3;*/
        bitstring[14] = tvar2<<4 | tvar3;
        tvar4 = sysInfo->w13 & 3 ; /*low part of w13*/

        tvar1 = sysInfo->w14;
        tvar2 = tvar4<<6 |tvar1 ;
        bitstring[15] = tvar2;
        tvar3 = sysInfo->w15;

        /*tvar1 = sysInfo->w16 >> 4;*/  /*High part of w16*/
        tvar1 = sysInfo->w16 >> 3;  /*High part of w16*/
        bitstring[16] = tvar3<<2 | tvar1;
        /*tvar2 = sysInfo->w16 & 15*/ ; /*low part of w16*/
        tvar2 = sysInfo->w16 & 7 ; /*low part of w16*/

        tvar3 = sysInfo->w17;
        tvar4 = tvar2 << 5 | tvar3;
        bitstring[17] =  tvar4;

     #if 0
      tvar6 = (I_U8)(tvar7 & 1);   /*low part of origARFCN512 */
      /*tvar4 = (I_U8) tvar3 & 511; */

      tvar8 = sysInfo->w1>> 2;  /*High part of w1*/
      tvar9 = sysInfo->w1 & 3 ; /*low part of w1*/
      /*tvar3 = tvar4 << 7 | (I_U16) tvar8; */
      tvar3 = tvar6 | (I_U8) tvar8;
      bitstring[4] = tvar3;

      tvar3 = sysInfo->w2>> 2;  /*High part of w2*/
      bitstring[5] = (I_U16) tvar9 <<6 | tvar3;
      tvar4 = sysInfo->w2 & 3 ; /*low part of w2*/

      tvar1 = sysInfo->w3>> 2;  /*High part of w3*/
      bitstring[6] = tvar4<<6 | tvar1;
      tvar2 = sysInfo->w3 & 3 ; /*low part of w3*/

      tvar3 = sysInfo->w4>> 1;  /*High part of w4*/
      bitstring[7] = tvar2<<6 | tvar3;
      tvar4 = sysInfo->w4 & 1 ; /*low part of w4*/

      tvar1 = sysInfo->w5;
      tvar2 = tvar4 << 7 | sysInfo->w5;
      bitstring[8] = tvar2;

      tvar1 = sysInfo->w6;

      tvar3 = sysInfo->w7>> 6;  /*High part of w7*/
      bitstring[9] = tvar1<<1 | tvar1;
      tvar4 = sysInfo->w7 & 63 ; /*low part of w7*/

      tvar1 = sysInfo->w8>> 4;  /*High part of w8*/
      bitstring[10] = tvar4<<2 | tvar4;
      tvar2 = sysInfo->w8 & 15 ; /*low part of w8*/

      tvar3 = sysInfo->w9>> 2;  /*High part of w9*/
      bitstring[11] = tvar2<<4 | tvar2;
      tvar4 = sysInfo->w9 & 3 ; /*low part of w9*/

      tvar1 = sysInfo->w10;
      tvar2 = tvar4<<6 | tvar1;
      bitstring[12] = tvar2;

      tvar3 = sysInfo->w11 ;

      tvar1 = sysInfo->w12 >> 4;  /*High part of w12*/
      bitstring[13] = tvar3<<2 | tvar1;
      tvar2 = sysInfo->w12 & 15 ; /*low part of w12*/

      tvar3 = sysInfo->w13 >> 2;  /*High part of w13*/
      bitstring[14] = tvar3<<4 | tvar3;
      tvar4 = sysInfo->w13 & 3 ; /*low part of w13*/

      tvar1 = sysInfo->w14;
      tvar2 = tvar4<<6 |tvar1 ;
      bitstring[15] = tvar2;
      tvar3 = sysInfo->w15;

      tvar1 = sysInfo->w16 >> 4;  /*High part of w16*/
      bitstring[16] = tvar3<<2 | tvar1;
      tvar2 = sysInfo->w16 & 15 ; /*low part of w16*/

      tvar3 = sysInfo->w17;
      tvar4 = tvar2 << 5 | tvar3;
      bitstring[17] =  tvar4;

     #endif 

   }  /*end of range512w format */

 /* NCCPermitted needs to be encoded */

   bitstring[18] = SI_SPARE;
   bitstring[19] = SI_SPARE;
   bitstring[20] = SI_SPARE;
   bitstring[21] = SI_SPARE;


   l2PseudoLength =18;
   l2PseudoLength = l2PseudoLength << 2 | 1;
   *len = 23;
   buff[0] = l2PseudoLength;
   memcpy(buff+1, bitstring, 22);
   return 0; 
 
}

/***********************************************************************************
*  Function Name   : EncodeSysInformation3 
*  Args            : 1. SystemInfo3 structure pointer
*                    2. pointer to buff
*                    3. length of buffer
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 3 message buffer
***********************************************************************************/

/*I_S32  SysInfoEncoder::EncodeSysInformation3( SystemInfo3 *sysInfo, I_U8 *buff, I_U16 *len)
*/I_S32  EncodeSysInformation3( SystemInfo3 *sysInfo, I_U8 *buff, I_U16 *len)
{

 I_U8 tvar1 = 0;
 I_U8 tvar2 = 0;
 I_U8 tvar3 = 0;
 I_U8 tvar4 = 0;
 I_U8 tvar5 = 0;
 I_U8 tvar6 = 0;

 I_U16 tvar7 = 0;
/* Commented by Aricent
 I_U16 tvar7 = 0;
 I_U16 tvar8 = 0;
 I_U16 tvar9 = 0; */

 I_U8 firstByte;
 I_U8 bitstring[22]; /* modified the value of bitstring length by Aricent */
 I_U8 l2PseudoLength;

 /* Added By Aricent */
 memset(bitstring, 0, sizeof(bitstring));
 /* End of Adding */

tvar1 = sysInfo->skipIndicator<<4 ;
firstByte = tvar1|sysInfo->protocolDiscriminator;
bitstring[0] = firstByte;
bitstring[1] = sysInfo->messageType;

bitstring[2] = sysInfo->cellIdentity >> 8 & 255;
bitstring[3] = sysInfo->cellIdentity & 255;

/* Commented by Aricent 
tvar3 = sysInfo->mobileCC/100;*/  /* first digit of MCC */
/*tvar2 = sysInfo->mobileCC % 100 ;
tvar2 = tvar2/10;  */    /* second digit of MCC */
tvar7 = sysInfo->mobileCC & 0x0F00;
tvar3 = (I_U8)(tvar7 >> 8); /* first digit of MCC */
tvar7 = sysInfo->mobileCC & 0x00F0;
tvar2 = (I_U8)(tvar7 >>4); /* second digit of MCC */
bitstring[4] = tvar2<<4 | tvar3;
/*Commented By Aricent 
tvar2 = sysInfo->mobileCC % 10; */ /* third digit of MCC */
tvar7 = sysInfo->mobileCC & 0x000F;
tvar2 = (I_U8)tvar7; /* Third digit of MCC */
tvar7 =  sysInfo->mobileNC & 0x000F;
tvar3 = (I_U8)tvar7; /*Third digit of MNC */
if (tvar3 == 0x0F)
{
   bitstring[5] = 0xf0 | tvar2; //Added by LN.
}
else
   bitstring[5] = tvar3<<4 | tvar2; /*Added by Aricent */
/*Commented By Aricent 
tvar1 = sysInfo->mobileNC/10; */  /* first digit of NCC. now MNC 2 digit only*/
                               //Added by LN.
/*Commented By Aricent
tvar2 = sysInfo->mobileNC % 10; */
     /* second digit of NCC */
tvar7 = sysInfo->mobileNC & 0x0F00;
tvar1 = (I_U8)(tvar7 >> 8); /* First digit of MNC */
tvar7 = sysInfo->mobileNC & 0x00F0;
tvar2 = (I_U8)(tvar7 >>4); /* Second digit of MNC*/
bitstring[6] = tvar2<<4 | tvar1;


bitstring[7] = sysInfo->locationAreaCode >> 8 & 255;
bitstring[8] = sysInfo->locationAreaCode & 255;

tvar1 = sysInfo->mscr<<7;
tvar2 = tvar1 | sysInfo->att<<6;
tvar1 = tvar2 | sysInfo->bs_ag_blks_res<<3;
tvar2 = tvar1 |sysInfo->ccch_conf;
bitstring[9] = tvar2;

tvar1 = sysInfo->cbq3<<5;
tvar2 = tvar1 |sysInfo->bs_pa_mfrms;
bitstring[10] = tvar2;

bitstring[11] = sysInfo->timer3212value;

tvar1 = sysInfo->dn_ind<<7;
tvar2 = tvar1 | sysInfo->pwrc<<6;
tvar1 = tvar2 | sysInfo->dtx<<4 ;
tvar2 = tvar1 | sysInfo->radio_link_timeout;
bitstring[12] = tvar2;

tvar1 = sysInfo->cell_reselect_hystersis<<5;
tvar2 = tvar1 | sysInfo->ms_txpwr_max_cch;
bitstring[13] = tvar2;

tvar1 = sysInfo->acs<<7;
tvar2 = tvar1 | sysInfo->neci<<6;
tvar1 = tvar2 | sysInfo->rxlev_access_min;
bitstring[14] = tvar1;

tvar1 = sysInfo->maxRetans<<6;
tvar2 = tvar1 | sysInfo->txInteger<<2;
tvar1 = tvar2 | sysInfo->cellBarAccess<<1;
tvar2 = tvar1 | sysInfo->re;
bitstring[15] = tvar2;

tvar1 = sysInfo->acClass[15]<<7;
tvar2 = tvar1 | sysInfo->acClass[14]<<6;
tvar1 = tvar2 | sysInfo->acClass[13]<<5;
tvar2 = tvar1 | sysInfo->acClass[12]<<4;
tvar1 = tvar2 | sysInfo->acClass[11]<<3;
tvar2 = tvar1 | sysInfo->ec<<2;
tvar1 = tvar2 | sysInfo->acClass[9]<<1;
tvar2 = tvar1 | sysInfo->acClass[8];
bitstring[16] = tvar2;


tvar4 = 6;
tvar1 = sysInfo->acClass[7]<<7;
for(tvar3 = 6; tvar3>=1; tvar3--)
    {
         tvar2 = tvar1 | sysInfo->acClass[tvar3]<<tvar4;
         tvar1 = tvar2;
         tvar4--;
     }
tvar2 = tvar1 | sysInfo->acClass[0];
bitstring[17] = tvar2;
   bitstring[18] = 0;  /*Reset octet for SysInfo 3 */
   bitstring[19] = 0;  /*Reset octet for SysInfo 3 */
   bitstring[20] = 0;  /*Reset octet for SysInfo 3 */
   bitstring[21] = 0;  /*Reset octet for SysInfo 3 */

if(sysInfo->OptionalSelectionParameters != 0)
{
  tvar1 = 128;
  tvar2 = tvar1 | sysInfo->CBQ<<6;
  tvar2 = tvar2 | sysInfo->CELL_RESELECT_OFFSET;
  bitstring[18] = tvar2;

  tvar1 = sysInfo->TEMPORARY_OFFSET;
  tvar2 = tvar1<<5 | sysInfo->PENALTY_TIME;
  bitstring[19] = tvar2;
  if(sysInfo->PowerOffsetSelection != 0)
  {
    /* Commented by Aricent  
       tvar1 = 64;
       tvar2 = tvar1 | sysInfo->PowerOffset<<4;*/
    /* Added by Aricent */
    tvar1 = 128;
    tvar2 = sysInfo->PowerOffset<<5;
    if (sysInfo->Sysinfo2terIndication!=0)
      tvar3 = 16;
    else
      tvar3 = 0;
    if (sysInfo->EarlyClassmarkSendingControl!=0)
      tvar4 = 0;
    else
      tvar4 = 8;
    /* scheduling if and where is coded as L */
    if(sysInfo->GPRSIndicator!=0)
    {
      tvar5 = tvar1|tvar2|tvar3|tvar4|0|sysInfo->RA_COLOUR>>2;
      bitstring[20]= tvar5;
      tvar1 = sysInfo->RA_COLOUR<<6 |sysInfo->SI13Position<<5;
      if(sysInfo->G3EarlyCMSendingRestriction != 0)
        tvar2 = 16;
      else
        tvar2 = 0;
      // if(sysInfo->SI2quaterPosition!= 0)
      /*Changes for PCU R2.5 : Start*/

      //tvar3 = 3 |(1 & sysInfo->SI2quaterPosition)<<2;
        tvar3 = 0;
        tvar3 = 11|sysInfo->SI2quaterPosition<<3;

      /*PCU Rel 2.5 Changes : Ends*/
      //  else
      // tvar3 = 11; /* padding spare bits as 2B*/
      tvar4 = tvar1|tvar2|tvar3;
      bitstring[21]= tvar4;
    }
    else
    {
      /* GPRS Indiactor encoded as L*/
      if (sysInfo->G3EarlyCMSendingRestriction != 0)
        tvar5 = 2;
      else
        tvar5 = 3;
      tvar6 = tvar1|tvar2|tvar3|tvar4|0|tvar5;
      bitstring[20]= tvar6;

      if(sysInfo->SI2quaterPosition!= 0)
       //tvar1 = 171|sysInfo->SI2quaterPosition<<6;
       tvar1 = 171;
       else
       tvar1 = SI_SPARE; /* spare padding as 2B */

      bitstring[21]= tvar1;
    }   
    /* End Of Added by Aricent */
    /*Commented By Aricent   	 
      bitstring[20] = tvar2;
      bitstring[21] = 43;*/
  }
  else
  {
    /* Added By Aricent*/	    
    if (sysInfo->Sysinfo2terIndication!=0)
      //        tvar1 = 128;
      tvar1 = 64;
    else
      tvar1 = 0;
    if (sysInfo->EarlyClassmarkSendingControl!=0)
      //        tvar2 = 64;
      tvar2 = 0;
    else
      //        tvar2 = 0;
      tvar2 = 32;	    
    /* scheduling if and where is coded as L */
    if(sysInfo->GPRSIndicator!=0)
    {
      /*Commeted By Aricent
        tvar3 = sysInfo->RA_COLOUR<<1;
        tvar4 = sysInfo->SI13Position;
        tvar5 = tvar1|tvar2|48|tvar3|tvar4;
        bitstring[20]= tvar5;
        if(sysInfo->G3EarlyCMSendingRestriction != 0)
        tvar1 = 128;
        else
        tvar1 = 0;
        if(sysInfo->SI2quaterPosition!= 0)
        tvar2 = 107|sysInfo->SI2quaterPosition<<5;
        else
        tvar2 = SI_SPARE; 
        tvar3 = tvar1|tvar2;
        bitstring[21]= tvar3 */

      /* Added By Aricent */
      tvar3 = sysInfo->RA_COLOUR; 
      tvar5 = tvar1|tvar2|0|tvar3;
      bitstring[20]= tvar5;

      tvar4 = sysInfo->SI13Position<<7; 
      if(sysInfo->G3EarlyCMSendingRestriction != 0)
        tvar1 = 64; 
      else
        tvar1 = 0;
      //  if(sysInfo->SI2quaterPosition!= 0)
      tvar2 = 11|sysInfo->SI2quaterPosition<<4;
      // else
      //   tvar2 = SI_SPARE;  // spare padding by 2B
      tvar3 = tvar4|tvar1|tvar2;
      bitstring[21]= tvar3;
      /* End Of Added by Aricent */
    }
    else
    {
      /* GPRS Indiactor encoded as L*/

      /*Commeted By Aricent
        if (sysInfo->G3EarlyCMSendingRestriction != 0)
        tvar3 = 0;
        else
        tvar3 = 8;
        if(sysInfo->SI2quaterPosition!= 0)
        tvar4 = 5|sysInfo->SI2quaterPosition<<1;
        else
        tvar4 = 1;
        tvar5 = tvar1|tvar2|32|tvar3|tvar4;*/

      /* Added By Aricent */
      if (sysInfo->G3EarlyCMSendingRestriction != 0)
        tvar3 = 4;
      else
        tvar3 = 0;
      //  if(sysInfo->SI2quaterPosition!= 0)
      tvar4 = 0|sysInfo->SI2quaterPosition;
      //      else
      //       tvar4 = 3;/* spare padding inc */
      tvar5 = tvar1|tvar2|8|tvar3|tvar4;
      /* End Of Added by Aricent */
      bitstring[20]= tvar5;
      bitstring[21]= SI_SPARE;
    }   	    
    /* End of Added By Aricent */
    /* Commented by Aricent 	    
       bitstring[20] = 43;
       bitstring[21] = 43;*/
  }
}//OptionalSelectionParameters
else /* when optional selection parameters is not present */
{
    if(sysInfo->PowerOffsetSelection != 0)
    {
	 /* Added by Aricent*/   
	 tvar1 = 64;
	 tvar2 = sysInfo->PowerOffset<<4;
	 if (sysInfo->Sysinfo2terIndication!=0)
	    tvar3 = 0;
         else
	    tvar3 = 8;
         if (sysInfo->EarlyClassmarkSendingControl!=0)
	    tvar4 = 4;
         else
	    tvar4 = 0;
         /* scheduling if and where is coded as L */
         if(sysInfo->GPRSIndicator!=0)
	 {
	     tvar5 = tvar1|tvar2|tvar3|tvar4|0|sysInfo->RA_COLOUR>>2;
	     bitstring[18]= tvar5;
             tvar1 = sysInfo->RA_COLOUR<<6 |sysInfo->SI13Position<<5;
             if(sysInfo->G3EarlyCMSendingRestriction != 0)
	        tvar2 = 16;
	     else
                tvar2 = 0;
        //     if(sysInfo->SI2quaterPosition!= 0)
	        tvar3 = 3|sysInfo->SI2quaterPosition<<2;
          //   else
	       // tvar3 = 11; /* spare padding inc*/
             tvar4 = tvar1|tvar2|tvar3;
             bitstring[19]= tvar4;
          }
         else
	 {
             /* GPRS Indiactor encoded as L*/
              if (sysInfo->G3EarlyCMSendingRestriction != 0)
	        tvar5 = 128;
	     else
                tvar5 = 0;
             /*tvar6 = tvar1|tvar2|tvar3|tvar4|0|tvar5; */
             tvar6 = tvar1|tvar2|tvar3|tvar4|3; 
             bitstring[18]= tvar6;
	     
           //   if(sysInfo->SI2quaterPosition!= 0)
	        tvar1 = 64|sysInfo->SI2quaterPosition<<5;
            // else
	       // tvar1 = SI_SPARE; /* spare padding inc*/
             	    
	     bitstring[19]= tvar5|tvar1;
	 }      
	 /* End of Added By Aricent*/
	 /* commented by Aricent   
         tvar1 = 64;
         tvar2 = tvar1 | sysInfo->PowerOffset<<4;
         bitstring[18] = tvar2;
         bitstring[19] = 43;*/
         bitstring[20] = 43;
         bitstring[21] = 43;
    }
    else
    {
       /* Added By Aricent*/	    
       if (sysInfo->Sysinfo2terIndication!=0)
          tvar1 = 128;
       else
          tvar1 = 0;
       if (sysInfo->EarlyClassmarkSendingControl!=0)
          tvar2 = 64;
       else
          tvar2 = 0;	    
       /* scheduling if and where is coded as L */
       if(sysInfo->GPRSIndicator!=0)
       {
	  tvar3 = sysInfo->RA_COLOUR<<1;
          tvar4 = sysInfo->SI13Position;	  
          tvar5 = tvar1|tvar2|48|tvar3|tvar4;
          bitstring[18]= tvar5;
          if(sysInfo->G3EarlyCMSendingRestriction != 0)
             tvar1 = 128; 
          else
             tvar1 = 0;
         // if(sysInfo->SI2quaterPosition!= 0)
             tvar2 = 75|sysInfo->SI2quaterPosition<<5;
         // else
           //  tvar2 = SI_SPARE;/* spare padding inc */
          tvar3 = tvar1|tvar2;
          bitstring[19]= tvar3;
       }
       else
       {
         /* GPRS Indicator encoded as L*/
          if (sysInfo->G3EarlyCMSendingRestriction != 0)
             tvar3 = 0;
	  else
             tvar3 = 8;
	 // if(sysInfo->SI2quaterPosition!= 0)
	     tvar4 = 5|sysInfo->SI2quaterPosition<<1;
     //     else
       //      tvar4 = 1; /* spare padding inc */
          tvar5 = tvar1|tvar2|32|tvar3|tvar4;
          bitstring[18]= tvar5;
          bitstring[19]= SI_SPARE;
        }   	    
      /* End of Added by Aricent*/
      /* Commented by Aricent 
      bitstring[18] = 43;
      bitstring[19] = 43;*/
      bitstring[20] = 43;
      bitstring[21] = 43;
    }
}//End Rest Octet


  l2PseudoLength =18;
  l2PseudoLength = l2PseudoLength << 2 | 1;
  *len = 23;
  buff[0] = l2PseudoLength;
  memcpy(buff+1, bitstring,22);


  return 0; /* Added by Aricent */

}

/***********************************************************************************
*  Function Name   : EncodeSysInformation4 
*  Args            : 1. SystemInfo4 structure pointer
*                    2. pointer to buff
*                    3. length of buffer
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 4 message buffer
***********************************************************************************/

/*I_S32  SysInfoEncoder::EncodeSysInformation4( SystemInfo4 *sysInfo, I_U8 *buff, I_U16 *len)
*/I_S32 EncodeSysInformation4( SystemInfo4 *sysInfo, I_U8 *buff, I_U16 *len)
{

 I_U8 tvar1 = 0;
 I_U8 tvar2 = 0;
 I_U8 tvar3 = 0;
 I_U8 tvar4 = 0;
/* Commented by Aricent 
 I_U8 tvar5 = 0;
 I_U8 tvar6 = 0;
*/
 I_U16 tvar7 = 0;
/* I_U16 tvar8 = 0;
 I_U16 tvar9 = 0; */

 I_U8 firstByte;
 I_U8 bitstring[22]; /* modified the value of bitstring length by Aricent */
 I_U8 l2PseudoLength;
 
 /* Added By Aricent */
 memset(bitstring, 0, sizeof(bitstring));
 /* End of Adding */

tvar1 = sysInfo->skipIndicator<<4 ;
firstByte = tvar1|sysInfo->protocolDiscriminator;
bitstring[0] = firstByte;
bitstring[1] = sysInfo->messageType;

/*Commented by Aricent 
tvar3 = sysInfo->mobileCC/100; */  /* first digit of MCC */
/*tvar2 = sysInfo->mobileCC % 100 ;
tvar2 = tvar2/10;  */   /* second digit of MCC */
tvar7 = sysInfo->mobileCC & 0x0F00;
tvar3 = (I_U8)(tvar7 >> 8); /* first digit of MCC */
tvar7 = sysInfo->mobileCC & 0x00F0;
tvar2 = (I_U8)(tvar7 >>4); /* second digit of MCC */
bitstring[2] = tvar2<<4 | tvar3;

/*Commented By Aricent 
tvar2 = sysInfo->mobileCC % 10; *//* third digit of MCC */
/*bitstring[3] =  0xf0 | tvar2; */
tvar7 = sysInfo->mobileCC & 0x000F;
tvar2 = (I_U8)tvar7; /* Third digit of MCC */
tvar7 =  sysInfo->mobileNC & 0x000F;
tvar3 = (I_U8)tvar7; /*Third digit of MNC */
if (tvar3 == 0x0F)
{
   bitstring[3] = 0xf0 | tvar2; 
}
else
   bitstring[3] = tvar3<<4 | tvar2; /*Added by Aricent */

/*Commented By Aricent 
tvar1 = sysInfo->mobileNC/10; */  /* first digit of NCC */
/*tvar2 = sysInfo->mobileNC % 10 ; */
tvar7 = sysInfo->mobileNC & 0x0F00;
tvar1 = (I_U8)(tvar7 >> 8); /* First digit of MNC */
tvar7 = sysInfo->mobileNC & 0x00F0;
tvar2 = (I_U8)(tvar7 >>4); /* Second digit of MNC*/
bitstring[4] =  tvar2<<4 | tvar1;

bitstring[5] = sysInfo->locationAreaCode >> 8 & 255;
bitstring[6] = sysInfo->locationAreaCode & 255;


tvar1 = sysInfo->cell_reselect_hystersis<<5;
tvar2 = tvar1 | sysInfo->ms_txpwr_max_cch;
bitstring[7] = tvar2;

tvar1 = sysInfo->acs<<7;
tvar2 = tvar1 | sysInfo->neci<<6;
tvar1 = tvar2 | sysInfo->rxlev_access_min;
bitstring[8] = tvar1;

tvar1 = sysInfo->maxRetans<<6;
tvar2 = tvar1 | sysInfo->txInteger<<2;
tvar1 = tvar2 | sysInfo->cellBarAccess<<1;
tvar2 = tvar1 | sysInfo->re;
bitstring[9] = tvar2;

tvar1 = sysInfo->acClass[15]<<7;
tvar2 = tvar1 | sysInfo->acClass[14]<<6;
tvar1 = tvar2 | sysInfo->acClass[13]<<5;
tvar2 = tvar1 | sysInfo->acClass[12]<<4;
tvar1 = tvar2 | sysInfo->acClass[11]<<3;
tvar2 = tvar1 | sysInfo->ec<<2;
tvar1 = tvar2 | sysInfo->acClass[9]<<1;
tvar2 = tvar1 | sysInfo->acClass[8];
bitstring[10] = tvar2;


tvar4 = 6;
tvar1 = sysInfo->acClass[7]<<7;
for(tvar3 = 6; tvar3>=1; tvar3--)
    {
         tvar2 = tvar1 | sysInfo->acClass[tvar3]<<tvar4;
         tvar1 = tvar2;
         tvar4--;
     }
tvar2 = tvar1 | sysInfo->acClass[0];
bitstring[11] = tvar2;

if(sysInfo->OptionalSelectionParameters != 0)
{
    tvar1 = 128;
    tvar2 = tvar1 | sysInfo->CBQ<<6;
    tvar2 = tvar2 | sysInfo->CELL_RESELECT_OFFSET;
    bitstring[12] = tvar2;
    
    tvar1 = sysInfo->TEMPORARY_OFFSET;
    tvar2 = tvar1<<5 | sysInfo->PENALTY_TIME;
    bitstring[13] = tvar2;
   
    if(sysInfo->PowerOffsetSelection != 0)
    {
        /* Added by Aricent */	
	 tvar1 = 128;
         tvar2 = tvar1|sysInfo->PowerOffset<<5;
         if(sysInfo->GPRSIndicator !=0)
	 {
	    tvar3 = 16 |sysInfo->RA_COLOUR<<1;
            tvar4 = tvar2|tvar3|sysInfo->SI13Position;
            bitstring[14] = tvar4;
         }
         else
	 {
        /* here, 
           GPRS Ind Encoded As L
           Break Indicator encoded as LL */	 

	/* Commented By Aricent
	   tvar3 = 8;
           tvar4 = tvar2|tvar3;	   
	   bitstring[14] = tvar4; */

            tvar3 = 11;
            bitstring[14] = tvar2|0|tvar3; 
	 }

	/* End of Added by Aricent */ 
	 /* commented by Aricent    
         tvar1 = 64;
         tvar2 = tvar1 | sysInfo->PowerOffset<<4;
         bitstring[14] = tvar2;*/
	 /* here , Break Indicator encoded as LL */

         bitstring[15] = 43;
         bitstring[16] = 43;
         bitstring[17] = 43;
         bitstring[18] = 43;
         bitstring[19] = 43;
         bitstring[20] = 43;
         bitstring[21] = 43;
    }
    else
    {
      /* Added by Aricent */
      /* here break indicator encoded as LL(2)*/ 	    
       if (sysInfo->GPRSIndicator !=0)
       {
       	 /* commented by Aricent
         tvar1 = 128;
         tvar2 = sysInfo->RA_COLOUR<<4;
         tvar3 = sysInfo->SI13Position<<3|2;
         tvar4 = tvar1|tvar2|tvar3;
         bitstring [14] = tvar4; */
         
         tvar1 = 64;
         tvar2 = sysInfo->RA_COLOUR << 3;
         tvar3 = sysInfo->SI13Position << 2;
         tvar4 = tvar1|tvar2|tvar3|2; 
         bitstring [14] = tvar4;
       }
       else
       /* End of Added by Aricent */	       
          bitstring[14] = 43;
       bitstring[15] = 43;
       bitstring[16] = 43;
       bitstring[17] = 43;
       bitstring[18] = 43;
       bitstring[19] = 43;
       bitstring[20] = 43;
       bitstring[21] = 43;
    }
    
}//OptionalSelectionParameters
else /* if optional selection params is L */
{
    if(sysInfo->PowerOffsetSelection != 0)
    {
	  /* Added by Aricent */	
	 tvar1 = 64;
         tvar2 = tvar1|sysInfo->PowerOffset<<4;
         if(sysInfo->GPRSIndicator !=0)
	 {
	    /* Commented By Aricent
	    tvar3 = 16 |sysInfo->RA_COLOUR<<1;
            tvar4 = tvar2|tvar3|sysInfo->SI13Position;
            bitstring[12] = tvar4;
	    */
	    tvar3 = 0|sysInfo->RA_COLOUR;
            bitstring[12] = tvar2|tvar3;
            
            tvar4 = sysInfo->SI13Position << 7|27;
            bitstring[13] = tvar4;
         }
         else
	 {
          /* GPRS Indicator is encoded as L */ 
          /* here, Break Indicator is encoded as LL */
  
	  /* commented by Aricent
	   tvar3 = 10; 
           tvar4 = tvar2|tvar3|1; */

           tvar4 = tvar2|9;   	   
	   bitstring[12] = tvar4;
           bitstring[13] = 43;  /* spare padding */
	  }
	/* End of Added by Aricent */ 
         /* Commented By Aricent 	 
         tvar1 = 64;
         tvar2 = tvar1 | sysInfo->PowerOffset<<4;
         bitstring[12] = tvar2;*/
	 /* here, break indicator encoded as LL*/
//         bitstring[13] = 43;
         bitstring[14] = 43;
         bitstring[15] = 43;
         bitstring[16] = 43;
         bitstring[17] = 43;
         bitstring[18] = 43;
         bitstring[19] = 43;
         bitstring[20] = 43;
         bitstring[21] = 43;
    }
    else
    {
      /* Added by Aricent */	    
       if (sysInfo->GPRSIndicator !=0)
       {
	 /* here, break indicator encoded as LL(2)*/
         /* commented by Aricent
         tvar1 = 128;
         tvar2 = sysInfo->RA_COLOUR<<4;
         tvar3 = sysInfo->SI13Position<<3|2;
         tvar4 = tvar1|tvar2|tvar3;
         bitstring [12] = tvar4;*/

         tvar1 = 0|sysInfo->RA_COLOUR << 2 ;
         tvar4 = tvar1|sysInfo->SI13Position << 1|1;
         bitstring [12] = tvar4;
       }
       else
       /* End of Added by Aricent */
           bitstring[12] = 0x23;
        bitstring[13] = 43;
        bitstring[14] = 43;
        bitstring[15] = 43;
        bitstring[16] = 43;
        bitstring[17] = 43;
        bitstring[18] = 43;
        bitstring[19] = 43;
        bitstring[20] = 43;
        bitstring[21] = 43;

    }
}//End Rest Octet
  
  l2PseudoLength =12;
  l2PseudoLength = l2PseudoLength << 2 | 1;
  *len = 23;
  buff[0] = l2PseudoLength;
  memcpy(buff+1, bitstring,22);
  return 0; /* Added by Aricent */
}


/***********************************************************************************
*  Function Name   : EncodeSysInformation4_cbch 
*  Args            : 1. SystemInfo4_cbch structure pointer
*                    2. pointer to buff
*                    3. length of buffer
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 4 message buffer
***********************************************************************************/

I_S32 EncodeSysInformation4_cbch( SystemInfo4 *sysInfo, I_U8 *buff, I_U16 *len)
{

 I_U8 tvar1 = 0;
 I_U8 tvar2 = 0;
 I_U8 tvar3 = 0;
 I_U8 tvar4 = 0;
 I_U8 tvar5 = 0;
 I_U8 tvar6 = 0;
 I_U16 tvar7 = 0;
 I_U16  tvar8 = 0;
/* I_U16 tvar8 = 0;
 I_U16 tvar9 = 0; */

 I_U8 firstByte;
 I_U8 bitstring[26]; /* modified the value of bitstring length by Aricent */
 I_U8 l2PseudoLength;
 
 /* Added By Aricent */
 memset(bitstring, 0, sizeof(bitstring));
 /* End of Adding */

tvar1 = sysInfo->skipIndicator<<4 ;
firstByte = tvar1|sysInfo->protocolDiscriminator;
bitstring[0] = firstByte;
bitstring[1] = sysInfo->messageType;

/*Commented by Aricent 
tvar3 = sysInfo->mobileCC/100; */  /* first digit of MCC */
/*tvar2 = sysInfo->mobileCC % 100 ;
tvar2 = tvar2/10;  */   /* second digit of MCC */
tvar7 = sysInfo->mobileCC & 0x0F00;
tvar3 = (I_U8)(tvar7 >> 8); /* first digit of MCC */
tvar7 = sysInfo->mobileCC & 0x00F0;
tvar2 = (I_U8)(tvar7 >>4); /* second digit of MCC */
bitstring[2] = tvar2<<4 | tvar3;

/*Commented By Aricent 
tvar2 = sysInfo->mobileCC % 10; *//* third digit of MCC */
/*bitstring[3] =  0xf0 | tvar2; */
tvar7 = sysInfo->mobileCC & 0x000F;
tvar2 = (I_U8)tvar7; /* Third digit of MCC */
tvar7 =  sysInfo->mobileNC & 0x000F;
tvar3 = (I_U8)tvar7; /*Third digit of MNC */
if (tvar3 == 0x0F)
{
   bitstring[3] = 0xf0 | tvar2; 
}
else
   bitstring[3] = tvar3<<4 | tvar2; /*Added by Aricent */

/*Commented By Aricent 
tvar1 = sysInfo->mobileNC/10; */  /* first digit of NCC */
/*tvar2 = sysInfo->mobileNC % 10 ; */
tvar7 = sysInfo->mobileNC & 0x0F00;
tvar1 = (I_U8)(tvar7 >> 8); /* First digit of MNC */
tvar7 = sysInfo->mobileNC & 0x00F0;
tvar2 = (I_U8)(tvar7 >>4); /* Second digit of MNC*/
bitstring[4] =  tvar2<<4 | tvar1;

bitstring[5] = sysInfo->locationAreaCode >> 8 & 255;
bitstring[6] = sysInfo->locationAreaCode & 255;


tvar1 = sysInfo->cell_reselect_hystersis<<5;
tvar2 = tvar1 | sysInfo->ms_txpwr_max_cch;
bitstring[7] = tvar2;

tvar1 = sysInfo->acs<<7;
tvar2 = tvar1 | sysInfo->neci<<6;
tvar1 = tvar2 | sysInfo->rxlev_access_min;
bitstring[8] = tvar1;

tvar1 = sysInfo->maxRetans<<6;
tvar2 = tvar1 | sysInfo->txInteger<<2;
tvar1 = tvar2 | sysInfo->cellBarAccess<<1;
tvar2 = tvar1 | sysInfo->re;
bitstring[9] = tvar2;

tvar1 = sysInfo->acClass[15]<<7;
tvar2 = tvar1 | sysInfo->acClass[14]<<6;
tvar1 = tvar2 | sysInfo->acClass[13]<<5;
tvar2 = tvar1 | sysInfo->acClass[12]<<4;
tvar1 = tvar2 | sysInfo->acClass[11]<<3;
tvar2 = tvar1 | sysInfo->ec<<2;
tvar1 = tvar2 | sysInfo->acClass[9]<<1;
tvar2 = tvar1 | sysInfo->acClass[8];
bitstring[10] = tvar2;

tvar4 = 6;
tvar1 = sysInfo->acClass[7]<<7;
for(tvar3 = 6; tvar3>=1; tvar3--)
    {
         tvar2 = tvar1 | sysInfo->acClass[tvar3]<<tvar4;
         tvar1 = tvar2;
         tvar4--;
     }
tvar2 = tvar1 | sysInfo->acClass[0];
bitstring[11] = tvar2;

/* CBCH changes */
bitstring[12] = sysInfo->cbchChannelDesIe;

  tvar2 = sysInfo->channelType;      /* channel type*/
  tvar3 = sysInfo->timeslotNumber;   /*Timeslot number */
  LOG_PRINT(DEBUG,"value of channel type is %d\n", tvar2);
  LOG_PRINT(DEBUG,"value of timeslot number is %d\n", tvar3);

  tvar2 = tvar2<<3;
  tvar3 = tvar3 & 7;
  tvar4 = tvar2 | tvar3;
  LOG_PRINT(DEBUG,"value of channel type and timeslot after forming second byte of CBCH is %d\n", tvar4);

bitstring[13] = tvar4;

  tvar1 = sysInfo->tsc;              /*hard-coded value is used for TSC */
  tvar2 = sysInfo->hoppingChannel;   /* Hopping Channnel is hard-coded for CBCH */
  tvar8 = sysInfo->cbchArfcn;        /* cbch ARFCN */
  LOG_PRINT(DEBUG,"value of TSC is %d\n", tvar1);
  LOG_PRINT(DEBUG,"value of Hopping Channel is %d\n", tvar2);
  LOG_PRINT(DEBUG,"value of ARFCN is %d\n", tvar8);

  tvar1 = tvar1<<5;
  tvar2 = tvar2<<4;
  //tvar5 = tvar4 & 3;
  tvar5 = (tvar8 & 768) >> 8;
  tvar5 = tvar1 | tvar2 | tvar5;
  LOG_PRINT(DEBUG,"value of TSC Hopping Channel and ARFCN high part after forming third byte of CBCH is %d\n", tvar5);

bitstring[14] = tvar5;
  
 // tvar4= tvar4>>2;
  //tvar4 =tvar4 & 0xFF;
  tvar4 =tvar8 & 0xFF;
  printf("value of ARFCN low part after forming fourth byte of CBCH %d\n", tvar4);
  LOG_PRINT(DEBUG,"value of ARFCN low part after forming fourth byte of CBCH %d\n", tvar4);

bitstring[15] = tvar4;

if(sysInfo->OptionalSelectionParameters != 0)
{
    tvar1 = 128;
    tvar2 = tvar1 | sysInfo->CBQ<<6;
    tvar2 = tvar2 | sysInfo->CELL_RESELECT_OFFSET;
    bitstring[16] = tvar2;
    
    tvar1 = sysInfo->TEMPORARY_OFFSET;
    tvar2 = tvar1<<5 | sysInfo->PENALTY_TIME;
    bitstring[17] = tvar2;
   
    if(sysInfo->PowerOffsetSelection != 0)
    {
        /* Added by Aricent */	
	 tvar1 = 128;
         tvar2 = tvar1|sysInfo->PowerOffset<<5;
         if(sysInfo->GPRSIndicator !=0)
	 {
	    tvar3 = 16 |sysInfo->RA_COLOUR<<1;
            tvar4 = tvar2|tvar3|sysInfo->SI13Position;
            bitstring[18] = tvar4;
         }
         else
	 {
        /* here, 
           GPRS Ind Encoded As L
           Break Indicator encoded as LL */	 

	/* Commented By Aricent
	   tvar3 = 8;
           tvar4 = tvar2|tvar3;	   
	   bitstring[18] = tvar4; */

            tvar3 = 11;
            bitstring[18] = tvar2|0|tvar3; 
	 }

	/* End of Added by Aricent */ 
	 /* commented by Aricent    
         tvar1 = 64;
         tvar2 = tvar1 | sysInfo->PowerOffset<<4;
         bitstring[18] = tvar2;*/
	 /* here , Break Indicator encoded as LL */

         bitstring[19] = 43;
         bitstring[20] = 43;
         bitstring[21] = 43;
         bitstring[22] = 43;
         bitstring[23] = 43;
         bitstring[24] = 43;
         bitstring[25] = 43;
    }
    else
    {
      /* Added by Aricent */
      /* here break indicator encoded as LL(2)*/ 	    
       if (sysInfo->GPRSIndicator !=0)
       {
       	 /* commented by Aricent
         tvar1 = 128;
         tvar2 = sysInfo->RA_COLOUR<<4;
         tvar3 = sysInfo->SI13Position<<3|2;
         tvar4 = tvar1|tvar2|tvar3;
         bitstring [18] = tvar4; */
         
         tvar1 = 64;
         tvar2 = sysInfo->RA_COLOUR << 3;
         tvar3 = sysInfo->SI13Position << 2;
         tvar4 = tvar1|tvar2|tvar3|2; 
         bitstring [18] = tvar4;
       }
       else
       /* End of Added by Aricent */	       
          bitstring[18] = 43;
       bitstring[19] = 43;
       bitstring[20] = 43;
       bitstring[21] = 43;
       bitstring[22] = 43;
       bitstring[23] = 43;
       bitstring[24] = 43;
       bitstring[25] = 43;
    }
    
}//OptionalSelectionParameters
else /* if optional selection params is L */
{
    if(sysInfo->PowerOffsetSelection != 0)
    {
	  /* Added by Aricent */	
	 tvar1 = 64;
         tvar2 = tvar1|sysInfo->PowerOffset<<4;
         if(sysInfo->GPRSIndicator !=0)
	 {
	    /* Commented By Aricent
	    tvar3 = 16 |sysInfo->RA_COLOUR<<1;
            tvar4 = tvar2|tvar3|sysInfo->SI13Position;
            bitstring[16] = tvar4;
	    */
	    tvar3 = 0|sysInfo->RA_COLOUR;
            bitstring[16] = tvar2|tvar3;
            
            tvar4 = sysInfo->SI13Position << 7|27;
            bitstring[17] = tvar4;
         }
         else
	 {
          /* GPRS Indicator is encoded as L */ 
          /* here, Break Indicator is encoded as LL */
  
	  /* commented by Aricent
	   tvar3 = 10; 
           tvar4 = tvar2|tvar3|1; */

           tvar4 = tvar2|9;   	   
	   bitstring[16] = tvar4;
           bitstring[17] = 43;  /* spare padding */
	  }
	/* End of Added by Aricent */ 
         /* Commented By Aricent 	 
         tvar1 = 64;
         tvar2 = tvar1 | sysInfo->PowerOffset<<4;
         bitstring[16] = tvar2;*/
	 /* here, break indicator encoded as LL*/
//         bitstring[17] = 43;
         bitstring[18] = 43;
         bitstring[19] = 43;
         bitstring[20] = 43;
         bitstring[21] = 43;
         bitstring[22] = 43;
         bitstring[23] = 43;
         bitstring[24] = 43;
         bitstring[25] = 43;
    }
    else
    {
      /* Added by Aricent */	    
       if (sysInfo->GPRSIndicator !=0)
       {
	 /* here, break indicator encoded as LL(2)*/
         /* commented by Aricent
         tvar1 = 128;
         tvar2 = sysInfo->RA_COLOUR<<4;
         tvar3 = sysInfo->SI13Position<<3|2;
         tvar4 = tvar1|tvar2|tvar3;
         bitstring [16] = tvar4;*/

         tvar1 = 0|sysInfo->RA_COLOUR << 2 ;
         tvar4 = tvar1|sysInfo->SI13Position << 1|1;
         bitstring [16] = tvar4;
       }
       else
       /* End of Added by Aricent */
        bitstring[16] = 0x23;
        bitstring[17] = 43;
        bitstring[18] = 43;
        bitstring[19] = 43;
        bitstring[20] = 43;
        bitstring[21] = 43;
        bitstring[22] = 43;
        bitstring[23] = 43;
        bitstring[24] = 43;
        bitstring[25] = 43;

    }
}//End Rest Octet
  
  l2PseudoLength =16;
  l2PseudoLength = l2PseudoLength << 2 | 1;
  *len = 23;
  buff[0] = l2PseudoLength;
  memcpy(buff+1, bitstring,23);
  return 0; /* Added by Aricent */
}


/***********************************************************************************
*  Function Name   : EncodeSysInformation5 
*  Args            : 1. SystemInfo5 structure pointer
*                    2. pointer to buff
*                    3. length of buffer
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 5 message buffer
***********************************************************************************/

/*I_S32  SysInfoEncoder::EncodeSysInformation5( SystemInfo5 *sysInfo, I_U8 *buff, I_U16 *len)*/
I_S32  EncodeSysInformation5( SystemInfo5 *sysInfo, I_U8 *buff, I_U16 *len)
{
 I_U8 tvar1 = 0;
 I_U8 tvar2 = 0;
 I_U8 tvar3 = 0;
 I_U8 tvar4 = 0;
 I_U8 tvar5 = 0;
 I_U8 tvar6 = 0;

 I_U16 tvar7 = 0;
 I_U16 tvar8 = 0;
 I_U16 tvar9 = 0;

 I_U8 format1[22] = "bitmap0format";
 I_U8 format2[22] = "range1024format";
 I_U8 format3[22] = "range512format";
 I_U8 format4[22] = "range256format";
 I_U8 format5[22] = "range128format";
 I_U8 format6[22] = "variablebitmapformat";
 I_U8 firstByte;
 I_U8 bitstring[22];
 I_U8 l2PseudoLength;
 I_U8 S_ARFCN = 119;
 I_U8 E_ARFCN = 113;
 I_U8 i;

 /* Added By Aricent */
 memset(bitstring, 0, sizeof(bitstring));
 /* End of Adding */

 tvar1 = sysInfo->skipIndicator<<4 ;
 firstByte = tvar1|sysInfo->protocolDiscriminator;

bitstring[0] = firstByte;
bitstring[1] = sysInfo->messageType;

/*cellChannelDescription */

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format1);


if(tvar6==0)       /* bitmap 0 format */
{

        tvar3 = sysInfo->ext_ind<<5;
        tvar4 = tvar3 | sysInfo->ba_ind<<4;
        tvar1 = tvar4 | sysInfo->ARFCN[123]<<3;
        tvar2 = tvar1 | sysInfo->ARFCN[122]<<2;
        tvar1 = tvar2 | sysInfo->ARFCN[121]<<1;
        tvar2 = tvar1 | sysInfo->ARFCN[120];
        tvar1 = tvar2 &  63;
        bitstring[2] = tvar1;

        for(i= 3; i<=17; i++)
        {
            tvar4 = 6;
            tvar1 = sysInfo->ARFCN[S_ARFCN]<<7;
            for(tvar3 = S_ARFCN - 1; tvar3>=E_ARFCN; tvar3--)
            {
                tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                tvar1 = tvar2;
                tvar4--;
            }
            tvar2 = tvar1 | sysInfo->ARFCN[E_ARFCN -1];
            bitstring[i] = tvar2;
            tvar1= 0;
            tvar2= 0;
            tvar3 =0;
            S_ARFCN = S_ARFCN -8;
            E_ARFCN = E_ARFCN -8;
        }//for

}/*end of bitmap0 format*/

tvar6 = strcmp((const char*)sysInfo->formatIndicator,(const char*) format2);

if(tvar6 ==0)       /*range 1024 format */
{
        
        I_S32   index = 0;/* initialized to 0 by Aricent */
        I_S32   len =  0 , i = 0;
        I_S32   n = 0 ;
        I_S32   range = 1024;
        I_S32   nW[28];
        /* I_S32   set[16]; Changed by Aricent */
        I_S32 set[16]; 




        for(i=0; i<28; i++)
        {
         nW[i] = 0;

        }

        for(i=0; i<16; i++)
        {
         set[i] = 0;

        }

        if(sysInfo->f1 != -1)
        {
          set[0]=   sysInfo->f1;
          len++;
        }
        if(sysInfo->f2 != -1)
        {
          set[1]=   sysInfo->f2;
          len++;
        }

        if(sysInfo->f3 != -1)
        {
          set[2]=   sysInfo->f3;
          len++;
        }
        if(sysInfo->f4 != -1)
        {
          set[3]=   sysInfo->f4;
          len++;
        }
        if(sysInfo->f5 != -1)
        {
          set[4]=   sysInfo->f5;
          len++;
        }
        if(sysInfo->f6 != -1)
        {
          set[5]=   sysInfo->f6;
          len++;
        }
        if(sysInfo->f7 != -1)
        {
          set[6]=   sysInfo->f7;
          len++;
        }
        if(sysInfo->f8 != -1)
        {
          set[7]=   sysInfo->f8;
          len++;
        }
        if(sysInfo->f9 != -1)
        {
          set[8]=   sysInfo->f9;
          len++;
        }
        if(sysInfo->f10 != -1)
        {
          set[9]=   sysInfo->f10;
          len++;
        }
        if(sysInfo->f11 != -1)
        {
          set[10]=   sysInfo->f11;
          len++;
        }
        if(sysInfo->f12 != -1)
        {
          set[11]=   sysInfo->f12;
          len++;
        }
        if(sysInfo->f13 != -1)
        {
          set[12]=   sysInfo->f13;
          len++;
        }
        if(sysInfo->f14 != -1)
        {
          set[13]=   sysInfo->f14;
          len++;
        }
        if(sysInfo->f15 != -1)
        {
          set[14]=   sysInfo->f15;
          len++;
        }
        if(sysInfo->f16 != -1)
        {
          set[15]=   sysInfo->f16;
          len++;
        }

       for(i = 0; i<len; i++)
        {
           if(set[i]  == 0)
           {
               n++;
           }
        }
        if(n == 0)
        {
           for(i= 0; i<len; i++)
           {
              set[i] = set[i] -1;
              index = 1;
              range = 1023;
              sysInfo->f0 =0  ;
           }
        }
        else
        {
            for(i= 0; i<len; i++)
            {
               set[i] = set[i++] ;
               index = 1;
               range = 1024 ;
               sysInfo->f0 = 1 ;
            }
        }

        Encode_san(index, set, len, range, nW);



        sysInfo->w1 = nW[0];
        sysInfo->w2 = nW[1];
        sysInfo->w3 = nW[2];
        sysInfo->w4 = nW[3];
        sysInfo->w5 = nW[4];
        sysInfo->w6 = nW[5];
        sysInfo->w7 = nW[6];
        sysInfo->w8 = nW[7];
        sysInfo->w9 = nW[8];
        sysInfo->w10 = nW[9];
        sysInfo->w11 = nW[10];
        sysInfo->w12 = nW[11];
        sysInfo->w13 = nW[12];
        sysInfo->w14 = nW[13];
        sysInfo->w15 = nW[14];
        sysInfo->w16 = nW[15];

        tvar1 = sysInfo->ext_ind<<5;
        tvar2 = tvar1 | sysInfo->ba_ind<<4;

        tvar3 = tvar2 | sysInfo->f0<<2;

        tvar7 = sysInfo->w1 >> 8;     /*High part of w1*/
        tvar8 = sysInfo->w1 & 255;     /*Low part of w1*/

        tvar4 = tvar3 | (I_U8) tvar7;
        tvar5 = tvar4 |128;
        tvar4 = tvar5 & 191;

        bitstring[2] = tvar4;
        bitstring[3] = (I_U8) tvar8;

        tvar7 = sysInfo->w2  >> 1;     /*High part of w2*/
        bitstring[4] = (I_U8) tvar7;

        tvar7 = sysInfo->w2 & 1;       /*Low part of w2*/

        tvar9 = sysInfo->w3 >> 2;     /*High part of w3*/
        bitstring[5] = (I_U8) tvar7<<7 | tvar9;

        tvar7 = sysInfo->w3 & 7;        /*Low part of w3*/

        tvar3 = sysInfo->w4 >> 2;     /*High part of w4*/
        bitstring[6] = (I_U8) tvar7<<6 | tvar3;
        tvar4 = sysInfo->w4 & 3;        /*Low part of w4*/

        tvar1 = sysInfo->w5 >> 2;     /*High part of w5*/
        bitstring[7] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w5 & 3;        /*Low part of w5*/

        tvar3 = sysInfo->w6 >> 2;     /*High part of w6*/
        bitstring[8] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w6 & 3;        /*Low part of w6*/

        tvar1 = sysInfo->w7 >> 2;     /*High part of w7*/
        bitstring[9] = tvar4<<6 | tvar1;
        tvar2 = sysInfo->w7& 3;       /*Low part of w7*/

        tvar3 = sysInfo->w8 >> 1;     /*High part of w8*/
        bitstring[10] = tvar2<<6 | tvar3;
        tvar4 = sysInfo->w8 & 1;       /*Low part of w8*/

        tvar1 = tvar4 << 7 | sysInfo->w9;
        bitstring[11] = tvar1;

        tvar2 = sysInfo->w10;

        tvar3 = sysInfo->w11 >> 6;     /*High part of w11*/
        bitstring[12] = tvar2<<1 | tvar3;
        tvar4 = sysInfo->w11& 63;       /*Low part of w11*/

        tvar1 = sysInfo->w12 >> 5;     /*High part of w12*/
        bitstring[13] = tvar4<<2 | tvar1;
        tvar2 = sysInfo->w12& 31;       /*Low part of w12*/

        tvar3 = sysInfo->w13 >> 4;     /*High part of w13*/
        bitstring[14] = tvar2<<3 | tvar3;
        tvar4 = sysInfo->w13& 15;       /*Low part of w13*/

        tvar1 = sysInfo->w14 >> 3;     /*High part of w14*/
        bitstring[15] = tvar4<<4 | tvar1;
        tvar2 = sysInfo->w14& 7;        /*Low part of w14*/

        tvar3 = sysInfo->w15 >> 2;     /*High part of w15*/
        bitstring[16] = tvar2<<5 | tvar3;
        tvar4 = sysInfo->w15& 7;        /*Low part of w15*/

        tvar1 = sysInfo->w16 ;
        bitstring[17] = tvar4<<6 | tvar1;

}/*end of 1024 format */

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format3);

if ( (tvar6 == 0) && (sysInfo->origARFCN != 0) )       /*range 512 format */
{
        tvar1 = sysInfo->ext_ind<<5;
        tvar2 = tvar2 | sysInfo->ba_ind<<4;

        tvar7 = sysInfo->origARFCN >>9;	 	/*high part of origARFCN512 */
        tvar4 = (I_U8) tvar7 |136;
        tvar4 = tvar4 | tvar2;
        bitstring[2] = tvar4;

        tvar7 = sysInfo->origARFCN >> 1; 	/*middle part of origARFCN512 */
        tvar4 = (I_U8) tvar7 & 255;
        bitstring[3] = tvar4;
    
        tvar7 = sysInfo->origARFCN & 1;		/*low part of origARFCN512 */
        tvar4 = (I_U8)tvar7;
        tvar8 = sysInfo->w1>> 2;  		/*High part of w1*/
        tvar3 = tvar4 << 7 | (I_U16) tvar8;
        bitstring[4] = tvar3;

        tvar9 = sysInfo->w1 & 3 ; 		/*low part of w1*/
        tvar3 = sysInfo->w2>> 2;  		/*High part of w2*/
        bitstring[5] = (I_U16) tvar9 <<6 | tvar3;

        tvar4 = sysInfo->w2 & 3 ; 		/*low part of w2*/
        tvar1 = sysInfo->w3>> 2;  		/*High part of w3*/
        bitstring[6] = tvar4<<6 | tvar1;

        tvar2 = sysInfo->w3 & 3 ; 		/*low part of w3*/
        tvar3 = sysInfo->w4>> 1;  		/*High part of w4*/
        bitstring[7] = tvar2<<6 | tvar3;

        tvar4 = sysInfo->w4 & 1 ; 		/*low part of w4*/
        tvar1 = sysInfo->w5;
        tvar2 = tvar4 << 7 | sysInfo->w5;
        bitstring[8] = tvar2;

        tvar1 = sysInfo->w6;
        tvar3 = sysInfo->w7>> 6;  		/*High part of w7*/
        bitstring[9] = tvar1<<1 | tvar3;

        tvar4 = sysInfo->w7 & 63 ; 		/*low part of w7*/
        tvar1 = sysInfo->w8>> 4;  		/*High part of w8*/
        bitstring[10] = tvar4<<2 | tvar1;

        tvar2 = sysInfo->w8 & 15 ; 		/*low part of w8*/
        tvar3 = sysInfo->w9>> 2;  		/*High part of w9*/
        bitstring[11] = tvar2<<4 | tvar3;

        tvar4 = sysInfo->w9 & 3 ; 		/*low part of w9*/
        tvar1 = sysInfo->w10;
        tvar2 = tvar4<<6 | tvar1;
        bitstring[12] = tvar2;

        tvar3 = sysInfo->w11 ;
        tvar1 = sysInfo->w12 >> 4;  		/*High part of w12*/
        bitstring[13] = tvar3<<2 | tvar1;

        tvar2 = sysInfo->w12 & 15; 		/*low part of w12*/
        tvar3 = sysInfo->w13 >> 2;  		/*High part of w13*/
        bitstring[14] = tvar2<<4 | tvar3;

        tvar4 = sysInfo->w13 & 3 ; 		/*low part of w13*/
        tvar1 = sysInfo->w14;
        tvar2 = tvar4<<6 |tvar1 ;
        bitstring[15] = tvar2;

        tvar3 = sysInfo->w15;
        tvar1 = sysInfo->w16 >> 3;  		/*High part of w16*/
        bitstring[16] = tvar3<<2 | tvar1;

        tvar2 = sysInfo->w16 & 7; 		/*low part of w16*/
        tvar3 = sysInfo->w17;
        tvar4 = tvar2 << 5 | tvar3;
        bitstring[17] =  tvar4;

}  /*end of range512w format */


tvar6 = strcmp((const char*)sysInfo->formatIndicator,(const char*) format4);

if(tvar6==0)       /*range 256 format */
{


        tvar3 = sysInfo->ext_ind<<5;
        tvar2 = tvar3 | sysInfo->ba_ind<<4;

        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCN512 */
        tvar4 = (I_U8) tvar7 |138;
        tvar4 = tvar4 | tvar2; 
        tvar1 = tvar4 & 187 ;
         
        bitstring[2] = tvar1;

        tvar8 = sysInfo->origARFCN >> 1;   /*middle part of origARFCN512 */
        tvar4 = (I_U8) tvar8 & 255;
        bitstring[3] = tvar4;

        tvar9 = sysInfo->origARFCN >> 9;   /*low part of origARFCN512 */
        tvar4 = (I_U8) tvar9 & 511;

        tvar1 = sysInfo->w1 >> 1;  /*high part of w1 */
        tvar2 = sysInfo->w1 & 1;  /*low part of w1 */

        tvar3 = sysInfo->w2;
        tvar4 = tvar2<<7 |tvar3;
        bitstring[4] =  tvar4;

        tvar1 = sysInfo->w3;

        tvar3 = sysInfo->w4 >> 4;  /*high part of w4 */
        bitstring[5] = tvar1 << 1 | tvar3;
        tvar4 = sysInfo->w4 & 15;  /*low part of w4 */

        tvar1 = sysInfo->w5 >> 3;  /*high part of w5 */
        bitstring[6] = tvar4 << 3 | tvar1;
        tvar2 = sysInfo->w5 & 7;  /*low part of w5 */

        tvar3 = sysInfo->w6 >> 5;  /*high part of w6 */
        bitstring[7] = tvar2 << 5 | tvar3;
        tvar4 = sysInfo->w6 & 1;  /*low part of w6 */

        tvar1 = sysInfo->w7<<1;
        tvar5 = tvar4<< 7 | tvar1;

        tvar2 = sysInfo->w8 >> 4;  /*high part of w8 */
        bitstring[8] = tvar5 | tvar2;
        tvar3 = sysInfo->w8 & 15;  /*low part of w8 */

        tvar1 = sysInfo->w9 >> 4;  /*high part of w9 */
        bitstring[9] = tvar3<<4 | tvar1;
        tvar4 = sysInfo->w9 & 1;  /*low part of w9 */

        tvar1 = sysInfo->w10<<2;
        tvar5 = tvar4<<7  | tvar1 ;

        tvar2 = sysInfo->w11 >> 3;  /*high part of w11 */
        bitstring[10] = tvar5 | tvar2;
        tvar3 = sysInfo->w11 & 7;  /*low part of w11 */

        tvar1 = sysInfo->w12;
        bitstring[11] = tvar3<<4  | tvar1;
    
        tvar1 = sysInfo->w13;
        tvar2 = sysInfo->w14 >> 2; /*high part of w14*/
        tvar3 = sysInfo->w14 & 3; /*low part of w14 */

        bitstring[12] =  tvar1 << 3 |tvar2 ;

        tvar1 = sysInfo->w15;
        tvar2 = sysInfo->w16 >> 3; /*high part of w16*/
        tvar4 = sysInfo->w16 & 7; /*low part of w16 */

        tvar5 = tvar3<<5 | tvar1;
        bitstring[13] = tvar3 << 5 | tvar1 <<1 |tvar2;

        tvar1 = sysInfo->w17;
        tvar2 = sysInfo->w18 >> 3; /*high part of w18*/
        tvar3 = sysInfo->w18 & 7; /*low part of w18 */

        bitstring[14] = tvar4 << 5 | tvar1 <<1 |tvar2;

        tvar1 = sysInfo->w19;
        tvar2 = sysInfo->w20 >> 3; /*high part of w20*/
        tvar4 = sysInfo->w20 & 7; /*low part of w20 */

        bitstring[15] = tvar3 << 5 | tvar1 <<1 |tvar2;

        tvar1 = sysInfo->w21;
        bitstring[16] = tvar4 << 5 | tvar1<<1;
}/* end of 256 format*/

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format5);

if(tvar6 ==0)       /*range 128 format */
{

        tvar1 = sysInfo->ext_ind<<5;
        tvar2 = tvar2 | sysInfo->ba_ind<<4;

        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCN128 */
        tvar3 = (I_U8) tvar7 |140;
        tvar3 = tvar3 | tvar2;  
        tvar4 = tvar3 & 189;
 
        bitstring[2] = tvar4;
        
        tvar8 = sysInfo->origARFCN >> 1;   /*middle part of origARFCN128 */
        tvar4 = (I_U8) tvar8 & 255;
        bitstring[3] = tvar4;

        tvar9 = sysInfo->origARFCN >> 9;   /*low part of origARFCN128 */
        tvar4 = (I_U8) tvar9 & 511;

        tvar1 = sysInfo->w1;
        bitstring[4] = tvar4 << 1 | tvar1;

        tvar2 = sysInfo->w2;
        tvar3 = sysInfo->w3 >>4 ; /*high part of w3 */
        tvar4 = sysInfo->w3 & 15 ; /*low part of w3*/

        bitstring[5] = tvar2 << 2 |tvar3;

        tvar1 = sysInfo->w4 >>1 ; /*high part of w4 */
        tvar2 = sysInfo->w4 & 1 ; /*low part of w4 */

        bitstring[6] = tvar4 << 4 |tvar1;

        tvar1 = sysInfo->w5;

        tvar3 = sysInfo->w6 >>2 ; /*high part of w6 */
        tvar4 = sysInfo->w6 & 7 ; /*low part of w6 */

        bitstring[7] = tvar2 <<7 | tvar1 <<2 |tvar3;

        bitstring[8] = tvar4 <<5 | sysInfo->w7;

        bitstring[9] = sysInfo->w8 <<4 |  sysInfo->w9;

        bitstring[10] = sysInfo->w10 <<4 |  sysInfo->w11;

        bitstring[11] = sysInfo->w12 <<4 |  sysInfo->w13;

        bitstring[12] = sysInfo->w14 <<4 |  sysInfo->w15;

        tvar1 = sysInfo->w16;
        tvar2 = sysInfo->w17;

        tvar3 = sysInfo->w18 >>1 ; /*high part of w18 */
        tvar4 = sysInfo->w18 & 1 ; /*low part of w18 */

        bitstring[13] = tvar1 << 5 | tvar2<<2 |tvar3;

        tvar1 = sysInfo->w19;
        tvar2 = sysInfo->w20;

        tvar3 = sysInfo->w21 >>2 ; /*high part of w21 */
        tvar5 = sysInfo->w21 & 3 ; /*low part of w21 */

        bitstring[14] = tvar4 <<7 | tvar1 <<4 | tvar2 <<1 |tvar3;

        tvar1 = sysInfo->w22;
        tvar2 = sysInfo->w23;

        bitstring[15] = tvar5<<6 | tvar1 <<3 | tvar2;

        tvar1 = sysInfo->w26 >>1 ; /*high part of w26 */
        tvar2 = sysInfo->w26 & 1 ; /*low part of w26 */

        tvar3 = sysInfo->w24;
        tvar4 = sysInfo->w25;

        bitstring[16] =  tvar3 <<4 |tvar4 <<2 |tvar1;

        tvar1 = sysInfo->w27;
        tvar2 = sysInfo->w28;

        bitstring[17]= tvar4<<7 |tvar1<<4 |tvar2<<1;
}/*end of 128 format */

tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format6);

if(tvar6 ==0)       /*variable bitmap format */
{

        tvar1 = sysInfo->ext_ind<<5;
        tvar2 = tvar1 | sysInfo->ba_ind<<4;

        tvar7 = sysInfo->origARFCN >>9; /*high part of origARFCNv */
        tvar4 = (I_U8) tvar7 |142;
        tvar4 = tvar4 |tvar2;
        tvar3 = tvar4 & 191;
        
        bitstring[2] = tvar3;

        tvar8 = sysInfo->origARFCN >> 1; /*middle part of origARFCNv */
        tvar4 = (I_U8) tvar8 & 255;
        bitstring[3] = tvar4;

        tvar9 = sysInfo->origARFCN >> 9;   /*low part of origARFCNv */
        tvar4 = (I_U8) tvar9 & 511;

        tvar1 = sysInfo->ARFCN[1]<<6;
        tvar2 = tvar1 | sysInfo->ARFCN[2]<<5;
        tvar1 = tvar2 | sysInfo->ARFCN[3]<<4;
        tvar2 = tvar1 | sysInfo->ARFCN[4]<<3;
        tvar1 = tvar2 | sysInfo->ARFCN[5]<<2;
        tvar2 = tvar1 | sysInfo->ARFCN[6]<<1;
        tvar1 = tvar2 | sysInfo->ARFCN[7];

        bitstring[4] = tvar4 << 7 | tvar1;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[8]<<7;
        for(tvar3 = 9; tvar3<=14; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
             }
        tvar2 = tvar1 | sysInfo->ARFCN[15];
        bitstring[5] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[16]<<7;
        for(tvar3 = 17; tvar3<=22; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[23];
        bitstring[6] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[24]<<7;
        for(tvar3 = 25; tvar3<=30; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[21];
        bitstring[7] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[32]<<7;
        for(tvar3 = 33; tvar3<=38; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[39];
        bitstring[8] = tvar2;
        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[40]<<7;
        for(tvar3 = 41; tvar3<=46; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[47];
        bitstring[9] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[48]<<7;
        for(tvar3 = 49; tvar3<=54; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[55];
        bitstring[10] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[56]<<7;
        for(tvar3 = 57; tvar3<=62; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[63];
        bitstring[11] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[64]<<7;
        for(tvar3 = 65; tvar3<=70; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
            tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[71];
        bitstring[12] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[72]<<7;
        for(tvar3 = 73; tvar3<=78; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[79];
        bitstring[13] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[80]<<7;
        for(tvar3 = 81; tvar3<=86; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[87];
        bitstring[14] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[88]<<7;
        for(tvar3 = 89; tvar3<=84; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[95];
        bitstring[15] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[96]<<7;
        for(tvar3 = 97; tvar3<=102; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[103];
        bitstring[16] = tvar2;

        tvar4 = 6;
        tvar1 = sysInfo->ARFCN[104]<<7;
        for(tvar3 = 105; tvar3<=110; tvar3++)
                {
                        tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
                        tvar1 = tvar2;
                        tvar4--;
                }
        tvar2 = tvar1 | sysInfo->ARFCN[111];
        bitstring[17] = tvar2;


} /*end of variable bitmap format */
    l2PseudoLength =18;
    l2PseudoLength = l2PseudoLength << 2 | 1;
    *len = 19;
    buff[0] = l2PseudoLength;
    memcpy(buff+1, bitstring,18);
    return 0; /* Added by Aricent */
}

/***********************************************************************************
*  Function Name   : EncodeSysInformation5ter 
*  Args            : 1. SystemInfo5ter structure pointer
*                    2. pointer to buff
*                    3. length of buffer
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 5ter message buffer
***********************************************************************************/

I_S32  EncodeSysInformation5ter( SystemInfo5ter *sysInfo, I_U8 *buff, I_U16 *len)
{

   I_U8 tvar1 = 0;
   I_U8 tvar2 = 0;
   I_U8 tvar3 = 0;
   I_U8 tvar4 = 0;
   I_U8 tvar6 = 0;

   I_U16 tvar7 = 0;
   I_U16 tvar8 = 0;
   I_U16 tvar9 = 0;

   I_U8 format1[FORMAT_LEN] = "bitmap0format";
   I_U8 format2[FORMAT_LEN] = "range512format";
   I_U8 firstByte;
   I_U8 bitstring[BITSTRING_LEN]; 
   I_U8 l2PseudoLength;
   I_U8 S_ARFCN = 119;
   I_U8 E_ARFCN = 113;
   I_U8 i;

   /* Added By Aricent */
   memset(bitstring, 0, sizeof(bitstring));
   /* End of Adding */

   tvar1 = sysInfo->skipIndicator<<4 ;
   firstByte = tvar1|sysInfo->protocolDiscriminator;

   bitstring[0] = firstByte;
   bitstring[1] = sysInfo->messageType;


  /*cellChannelDescription */
   tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format1);


   if(tvar6==0)       /* bitmap 0 format */
   {

      tvar3 = sysInfo->multibandReporting<<5;
      tvar4 = tvar3 | sysInfo->baInd<<4;
      tvar1 = tvar4 | sysInfo->ARFCN[123]<<3;
      tvar2 = tvar1 | sysInfo->ARFCN[122]<<2;
      tvar1 = tvar2 | sysInfo->ARFCN[121]<<1;
      tvar2 = tvar1 | sysInfo->ARFCN[120];
//    tvar1 = tvar2 &  63;	Mantis 4715
      bitstring[2] = tvar1;
        
      for(i= 3; i<=17; i++)
      {
         tvar4 = 6;
         tvar1 = sysInfo->ARFCN[S_ARFCN]<<7;
         for(tvar3 = S_ARFCN - 1; tvar3>=E_ARFCN; tvar3--)
         {
            tvar2 = tvar1 | sysInfo->ARFCN[tvar3]<<tvar4;
            tvar1 = tvar2;
            tvar4--;
         }
         tvar2 = tvar1 | sysInfo->ARFCN[E_ARFCN -1];
         bitstring[i] = tvar2;
         tvar1= 0;
         tvar2= 0;
         tvar3 =0;
         S_ARFCN = S_ARFCN -8;
         E_ARFCN = E_ARFCN -8;
      }//for

   }/*end of bitmap0 format*/


   tvar6 = strcmp((const char*)sysInfo->formatIndicator, (const char*)format2);

   if ( (tvar6 == 0) && (sysInfo->origARFCN != 0) )       /*range 512 format */
   {
      tvar1 = sysInfo->multibandReporting<<5;
      tvar2 = tvar2 | sysInfo->baInd<<4;

      tvar7 = sysInfo->origARFCN & 1023;	/*high part of origARFCN512 */
      tvar6 = (I_U8)(tvar7>>9);
      tvar4 = tvar1|tvar2|tvar6|136;
      bitstring[2] = tvar4;

      tvar8 = sysInfo->origARFCN >> 1;   	/*middle part of origARFCN512 */
      tvar4 = (I_U8) tvar8 & 255;
      bitstring[3] = tvar4;

      tvar7 = sysInfo->origARFCN & 1;
      tvar4 = (I_U8)tvar7;

      tvar8 = sysInfo->w1>> 2;  		/*High part of w1*/
      tvar3 = tvar4 << 7 | (I_U16) tvar8;
      bitstring[4] = tvar3;

      tvar9 = sysInfo->w1 & 3 ; 		/*low part of w1*/
      tvar3 = sysInfo->w2>> 2;  		/*High part of w2*/
      bitstring[5] = (I_U16) tvar9 <<6 | tvar3;

      tvar4 = sysInfo->w2 & 3 ; /*low part of w2*/
      tvar1 = sysInfo->w3>> 2;  /*High part of w3*/
      bitstring[6] = tvar4<<6 | tvar1;

      tvar2 = sysInfo->w3 & 3 ; /*low part of w3*/
      tvar3 = sysInfo->w4>> 1;  /*High part of w4*/
      bitstring[7] = tvar2<<6 | tvar3;

      tvar4 = sysInfo->w4 & 1 ; /*low part of w4*/
      tvar1 = sysInfo->w5;
      tvar2 = tvar4 << 7 | sysInfo->w5;
      bitstring[8] = tvar2;

      tvar1 = sysInfo->w6;
      tvar3 = sysInfo->w7>> 6;  /*High part of w7*/
      bitstring[9] = tvar1<<1 | tvar3;

      tvar4 = sysInfo->w7 & 63 ; /*low part of w7*/
      tvar1 = sysInfo->w8>> 4;  /*High part of w8*/
      bitstring[10] = tvar4<<2 | tvar1;

      tvar2 = sysInfo->w8 & 15 ; /*low part of w8*/
      tvar3 = sysInfo->w9>> 2;  /*High part of w9*/
      bitstring[11] = tvar2<<4 | tvar3;

      tvar4 = sysInfo->w9 & 3 ; /*low part of w9*/
      tvar1 = sysInfo->w10;
      tvar2 = tvar4<<6 | tvar1;
      bitstring[12] = tvar2;

      tvar3 = sysInfo->w11 ;
      tvar1 = sysInfo->w12 >> 4;  /*High part of w12*/
      bitstring[13] = tvar3<<2 | tvar1;

      tvar2 = sysInfo->w12 & 15 ; /*low part of w12*/
      tvar3 = sysInfo->w13 >> 2;  /*High part of w13*/
      bitstring[14] = tvar2<<4 | tvar3;

      tvar4 = sysInfo->w13 & 3 ; /*low part of w13*/
      tvar1 = sysInfo->w14;
      tvar2 = tvar4<<6 |tvar1 ;
      bitstring[15] = tvar2;

      tvar3 = sysInfo->w15;
      tvar1 = sysInfo->w16 >> 3;  /*High part of w16*/
      bitstring[16] = tvar3<<2 | tvar1;

      tvar2 = sysInfo->w16 & 7 ; /*low part of w16*/
      tvar3 = sysInfo->w17;
      tvar4 = tvar2 << 5 | tvar3;
      bitstring[17] =  tvar4;

     #if 0
      tvar6 = (I_U8)(tvar7 & 1);   /*low part of origARFCN512 */
      /*tvar4 = (I_U8) tvar3 & 511; */

      tvar8 = sysInfo->w1>> 2;  /*High part of w1*/
      tvar9 = sysInfo->w1 & 3 ; /*low part of w1*/
      /*tvar3 = tvar4 << 7 | (I_U16) tvar8; */
      tvar3 = tvar6 | (I_U8) tvar8;
      bitstring[4] = tvar3;

      tvar3 = sysInfo->w2>> 2;  /*High part of w2*/
      bitstring[5] = (I_U16) tvar9 <<6 | tvar3;
      tvar4 = sysInfo->w2 & 3 ; /*low part of w2*/

      tvar1 = sysInfo->w3>> 2;  /*High part of w3*/
      bitstring[6] = tvar4<<6 | tvar1;
      tvar2 = sysInfo->w3 & 3 ; /*low part of w3*/

      tvar3 = sysInfo->w4>> 1;  /*High part of w4*/
      bitstring[7] = tvar2<<6 | tvar3;
      tvar4 = sysInfo->w4 & 1 ; /*low part of w4*/

      tvar1 = sysInfo->w5;
      tvar2 = tvar4 << 7 | sysInfo->w5;
      bitstring[8] = tvar2;

      tvar1 = sysInfo->w6;

      tvar3 = sysInfo->w7>> 6;  /*High part of w7*/
      bitstring[9] = tvar1<<1 | tvar1;
      tvar4 = sysInfo->w7 & 63 ; /*low part of w7*/

      tvar1 = sysInfo->w8>> 4;  /*High part of w8*/
      bitstring[10] = tvar4<<2 | tvar4;
      tvar2 = sysInfo->w8 & 15 ; /*low part of w8*/

      tvar3 = sysInfo->w9>> 2;  /*High part of w9*/
      bitstring[11] = tvar2<<4 | tvar2;
      tvar4 = sysInfo->w9 & 3 ; /*low part of w9*/

      tvar1 = sysInfo->w10;
      tvar2 = tvar4<<6 | tvar1;
      bitstring[12] = tvar2;

      tvar3 = sysInfo->w11 ;

      tvar1 = sysInfo->w12 >> 4;  /*High part of w12*/
      bitstring[13] = tvar3<<2 | tvar1;
      tvar2 = sysInfo->w12 & 15 ; /*low part of w12*/

      tvar3 = sysInfo->w13 >> 2;  /*High part of w13*/
      bitstring[14] = tvar3<<4 | tvar3;
      tvar4 = sysInfo->w13 & 3 ; /*low part of w13*/

      tvar1 = sysInfo->w14;
      tvar2 = tvar4<<6 |tvar1 ;
      bitstring[15] = tvar2;
      tvar3 = sysInfo->w15;

      tvar1 = sysInfo->w16 >> 4;  /*High part of w16*/
      bitstring[16] = tvar3<<2 | tvar1;
      tvar2 = sysInfo->w16 & 15 ; /*low part of w16*/

      tvar3 = sysInfo->w17;
      tvar4 = tvar2 << 5 | tvar3;
      bitstring[17] =  tvar4;

     #endif 

   }  /*end of range512w format */

 /* NCCPermitted needs to be encoded */

/*   bitstring[18] = SI_SPARE;
   bitstring[19] = SI_SPARE;
   bitstring[20] = SI_SPARE;
   bitstring[21] = SI_SPARE;*/


   l2PseudoLength =18;
   l2PseudoLength = l2PseudoLength << 2 | 1;
   *len = 19;
   buff[0] = l2PseudoLength;
   memcpy(buff+1, bitstring, 18);
   return 0; 
}

/***********************************************************************************
*  Function Name   : Encode
*  Args            : 1. index
*                    2. set of arfcns 
*                    3. length 
*                    4. range
*                    5. encoded arfcns
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the arfcns according to the format applied 
***********************************************************************************/

I_S32  Encode(I_S32 index, I_S32 *set, I_S32 len, I_S32 range, I_S32 *nW)
{
    I_S32 i=0, j=0, temp = 2; 
   /* Added by Aricent 
    I_S32 i=0, j=0 */
    I_S32  pvotIndex = 0;
    
    //test for leaf condition
    if (len == 0) { return 1;} 
      /* Added by Aricent   
    {
      nW[index - 1] = 0; 
      return 1;
    }  end of Added by Aricent */
       	       
    if (len == 1)
    {
        //wSet[index] = set[0] +1 ;
        if (set[0] < 0)  /* Aricent - is this check needed ? */  
        {
           nW[index -1] =set[0] + 1 + 2*(range ) -1;
        } 
        else
        { 
            nW[index -1] = set[0] + 1;
        } 
        return 2;
    }

 //find the pivot value
    for (i = 0; i < len ; i++)
    {
       I_S32 nElem = 0;

       for (j = 0; j < len; j++)
       {
          if ((set[j] - set[i]) < 0) /*Aricent - is this check required ? */
                continue; 
          if ( ((set[j] - set[i])%range) <= (range-1)/2)
          {
                nElem++;
          }
       } /* end of j loop */

       if ( (nElem-1) == (len -1)/2 )
       {
          pvotIndex = i;
          if (set[i] < 0) /* Aricent - is this check required ? */ 
          {
              nW[index -1] =  set[i] + 1 + 2*(range) -1;
          } 
          else
          { 
               nW[index -1] =  set[i] + 1 ;
          } 
          for (i = 0 ; i < len ; i++)
          {
          }
          break;
        }/* end of if */
    }/* end of i loop */

    //wSet[index] =  set[pvotIndex] + 1;
    //Left hand side node
    {
        //Calculate subsets
        I_S32 subSet[len/2]; 
        I_S32 subSetInd = 0 , i ;
        I_S32 orgVal = 0;
        memset(subSet,0,len/2);
        orgVal = (set[pvotIndex] + (range-1)/2 + 1)%range;

        for (i =0; i < len; i++)
        {
            if (((set[i] - orgVal)%range ) < 0) /*why is this check required */
            {
                if (set[pvotIndex] > set[i])
                {
                }
                else
                {
                    continue;
                }
            }


            
                  
            /*if (((set[i] - orgVal)%range ) < 0) continue;  */
            if ((((set[i] - orgVal)%range ) < range/2))
            {
                subSet[subSetInd] = (set[i] - orgVal)%range;
                //if (set[pvotIndex] > set[i])
                //{
                 //   subSet[subSetInd] = (subSet[subSetInd] + range - 1);
                //}
                subSetInd++;
            }
        }

        
        temp = 1;
        if(index > 17 ) /* Changed by Aricent from 16 to 17) */ 
        {
            index = 1;
        }

        for(i = 1; i< index; i++ )
        {
                temp = temp*2;
        }
        if(index == 7 && range == 127 )
        {
            index = index + 4;
        }
        else

        if(index == 3  || index == 7)
        {
            index = index + 2;
        }
        else
        if(index == 4 ||  index == 5 || index == 6)
        {
            index = index + 4;
        }
        else
        if(index == 8)
        {
            index = index + 8;
        }
        else
        if(index != 1)
        {
           index = index + temp;
        }
        else
        {
             index++;
        }

        range = range + 1;   
	/*Added by Aricent    
        power = 1;
        do
        {

           power = 2 * power;
        }while(power < index);

       if (power >index)
          index = index + (power/2);
       else
          index = index + power;
       index = index % 18;

         
 
        End of Added by Aricent */
	

        Encode(index, subSet, subSetInd, range/2, nW);
    }
    //Right hand side node
    {
         if(index > 17) /* Changed by Aricent from  16 to 17 */
        {
           index = 1;
        }  
        //Calculate subsets
         I_S32 subSet[(len-1)/2];
        I_S32 subSetInd = 0 , i ;
        I_S32 orgVal = 0;
        memset(subSet,0,len/2);
        orgVal = (set[pvotIndex] + 1)%range;


        for (i =0; i < len; i++)
        {
            if (((set[i] - orgVal)%range ) < 0)
            { 
               /* Added by Aricent */ 
               if(set[pvotIndex] < set[i])
               {

                /*subSet[subSetInd] = (set[i] - (orgVal ))%range;
                subSetInd++;
                continue; */ 

               }
               else  /*End of Added by Aricent */
                   continue; 
            }

            if ((((set[i] - orgVal)%range ) < range/2))
            {
                subSet[subSetInd] = (set[i] - orgVal)%range;
                subSetInd++;
            }
        }
       
       	
        temp =1;

        if(index == 2 || index == 1)
        {
           index = index + 1;
        }
        else
        if(index == 8 || index == 9 || index == 10 || index == 11)
        {
           index = index + 4;
        }
        else
        if(index == 4 || index == 5)
        {
           index = index + 2;
        }
        else
        {
               index = index + temp;
        } 

	 /*Added by Aricent  
	  
	power = 1;
        do 
	{

	   power = 2 * power;
	}while(power < index);
         	  
       if (power >index)
          index = index +power;
       else
          index = index + 2* power;

	index = index % 18;       
        End of Added by Aricent */	   

	
        range = range - 1;
       return( Encode(index, subSet, subSetInd, range/2, nW));
    }

}

/***********************************************************************************
*  Function Name   : EncodeSysInformation6 
*  Args            : 1. SystemInfo6 structure pointer
*                    2. pointer to buff
*                    3. length of buffer
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 6 message buffer
***********************************************************************************/


/*I_S32  SysInfoEncoder::EncodeSysInformation6( SystemInfo6 *sysInfo, I_U8 *buff, I_U16 *len)
*/I_S32 EncodeSysInformation6( SystemInfo6 *sysInfo, I_U8 *buff, I_U16 *len)
{

	I_U8 tvar1 = 0;
 	I_U8 tvar2 = 0;
	I_U8 tvar3 = 0;
 	I_U8 tvar4 = 0;
       /* Commented by Aricent 
 	I_U8 tvar5 = 0;
 	I_U8 tvar6 = 0; */
        I_U16 tvar7 = 0;
 	I_U8 firstByte;
 	I_U8 bitstring[22];
 	I_U8 l2PseudoLength;

   /* Added By Aricent */
   memset(bitstring, 0, sizeof(bitstring));
   /* End of Adding */

	tvar1 = sysInfo->skipIndicator<<4 ;
	firstByte = tvar1|sysInfo->protocolDiscriminator;
	bitstring[0] = firstByte;
	bitstring[1] = sysInfo->messageType;

	bitstring[2] = sysInfo->cellIdentity >> 8 & 255;
	bitstring[3] = sysInfo->cellIdentity & 255;

        /* Commented By Aricent 
	tvar3 = sysInfo->mobileCC/100;  
	tvar2 = sysInfo->mobileCC % 100 ;
	tvar2 = tvar2/10;    */
        tvar7 = sysInfo->mobileCC & 0x0F00;
        tvar3 = (I_U8)(tvar7 >> 8); /* first digit of MCC */
        tvar7 = sysInfo->mobileCC & 0x00F0;
        tvar2 = (I_U8)(tvar7 >>4); /* second digit of MCC */
	bitstring[4] = tvar2<<4 | tvar3;
      
        tvar7 = sysInfo->mobileCC & 0x000F;
        tvar2 = (I_U8)tvar7; /* Third digit of MCC */
        tvar7 =  sysInfo->mobileNC & 0x000F;
        tvar3 = (I_U8)tvar7; /*Third digit of MNC */
        if (tvar3 == 0x0F)
        {
           bitstring[5] = 0xf0 | tvar2;
        }
        else
           bitstring[5] = tvar3<<4 | tvar2; /*Added by Aricent */
 
        /* Commented by Aricent 
	tvar2 = sysInfo->mobileCC % 10; 
	bitstring[5] = 0xf0 | tvar2; 
	tvar1 = sysInfo->mobileNC/10;  
                               
	tvar2 = sysInfo->mobileNC % 10 ; */
        tvar7 = sysInfo->mobileNC & 0x0F00;
        tvar1 = (I_U8)(tvar7 >> 8); /* First digit of MNC */
        tvar7 = sysInfo->mobileNC & 0x00F0;
        tvar2 = (I_U8)(tvar7 >>4); /* Second digit of MNC*/
        bitstring[6] = tvar2<<4 | tvar1;

	bitstring[7] = sysInfo->locationAreaCode >> 8 & 255;
	bitstring[8] = sysInfo->locationAreaCode & 255;

	tvar1 = 0;
	tvar2 = 0;
	/* Commented by Aricent
    if(sysInfo->dtx < 4)
	{
		tvar2 = tvar1 | sysInfo->pwrc<<6;
		tvar1 = tvar2 | sysInfo->dtx<<4 ;
		tvar2 = tvar1 | sysInfo->radio_link_timeout;
		bitstring[9] = tvar2;
	}
	else
	{
		tvar1 = 128;
		tvar3 = sysInfo->dtx & 3 ;
		tvar2 = tvar1 | sysInfo->pwrc<<6;
        tvar1 = tvar2 | tvar3<<4 ;
        tvar2 = tvar1 | sysInfo->radio_link_timeout;
        bitstring[9] = tvar2;

	}*/
	
        /* Added by Aricent */
        tvar4 = (sysInfo->dtx>>2) & 1; 
        tvar1 = tvar4<<7|sysInfo->pwrc<<6;
        tvar4 = sysInfo->dtx & 3; 
        tvar2 = tvar4<<4|sysInfo->radio_link_timeout;
        tvar3 = tvar1|tvar2;
        bitstring[9] = tvar3;
        /* End of Added by Aricent */
	
	tvar4 = 6;
	tvar1 = sysInfo->NCC[7]<<7;
	for(tvar3 = 6; tvar3>=1; tvar3--)
   	{
        	tvar2 = tvar1 | sysInfo->NCC[tvar3]<<tvar4;
        	tvar1 = tvar2;
        	tvar4--;
    }
	tvar2 = tvar1 | sysInfo->NCC[0];
	bitstring[10] = tvar2;

	/* Added by Aricent*/
	/* SI6 Rest Octets */
	/* PCH and NCH info is encoded as L */
	/* VBS/VGCS Options is encoded as L*/
	/* DTM support fixed to L */
        tvar1 = SI_SPARE;
        /* Commented by Aricent 
        if(sysInfo->Band_Indicator == GSM1800)
	   tvar2 = 0;
	else
	   tvar2 = 16; */
        /* Added by Aricent */
        if(sysInfo->Band_Indicator == GSM1900)
	   tvar2 = 16;
	else
	   tvar2 = 0; 
        /*End of Added by Aricent*/
        /*gprs_mx_txpwr_max_cch is not present*/
        tvar3 = tvar1|tvar2;
        bitstring[11] = tvar3;
        /*
	if(sysInfo->DTM_Support!= 0)
	   tvar1 = 0;
	else
	   tvar1 = 32;
	tvar2 = sysInfo->RAC>>3 & 31;
	tvar3 = tvar1|tvar2;
	bitstring[11] = tvar3;

	tvar1 = sysInfo->RAC<<5 & 224;
	tvar2 = (sysInfo->MAX_LAPDm<<2);
	if(sysInfo->Band_Indicator == GSM1800)
	   tvar3 = 3;
	else
	   tvar3 = 1;*//* inc spare padding as gprs_mx_txpwr_max_cch is not present*/
	/*tvar4 = tvar1|tvar2|tvar3;
	bitstring[12] = tvar4; */
	/* End of Added by Aricent */
	/* Commented by Aricent
	bitstring[11] = 43; */  
   	bitstring[12] = 43;  
   	bitstring[13] = 43;  
  	bitstring[14] = 43;
	bitstring[15] = 43;
	bitstring[16] = 43;
	bitstring[17] = 43;  

    l2PseudoLength =11;
    l2PseudoLength = l2PseudoLength << 2 | 1;
    *len = 19; 
    buff[0] = l2PseudoLength;
    memcpy(buff+1, bitstring,18); 

    return 0; /* Added by Aricent */
}
/***********************************************************************************
*  Function Name   : EncodeSysInformation13 
*  Args            : 1. SystemInfo13 structure pointer
*                    2. pointer to buff
*                    3. length of buffer
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will encode the system information 13 message buffer
***********************************************************************************/

I_S32  EncodeSysInformation13( SystemInfo13 *sysInfo, I_U8 *buff, I_U16 *len, I_U8 pbcchPres,I_U8 egprsPresent)
{

   I_U8 tvar1 = 0;
   I_U8 tvar2 = 0;
   I_U8 tvar3 = 0;
   I_U8 tvar4 = 0;
   I_U8 tvar5 = 0;
   I_U8 tvar6 = 0;
   I_U8 tvar7 = 0;

   I_U8 firstByte;
   I_U8 bitstring[BITSTRING_LEN_23];
   I_U8 l2PseudoLength;

   /* Added By Aricent */
   memset(bitstring, 0, sizeof(bitstring));
   /* End of Adding */
   tvar1 = sysInfo->skipIndicator<<4 ;
   firstByte = tvar1|sysInfo->protocolDiscriminator;
   bitstring[0] = firstByte;
   bitstring[1] = sysInfo->messageType;
        /* First Rest Octet */
   tvar1 = 128;
   tvar1 = tvar1 | (sysInfo->bcchChangeMark<<4);
   tvar2 = tvar1 | sysInfo->siChangeField;
   bitstring[2]= tvar2;
        /* Second Rest octet */
   if(pbcchPres == 0)
   {	
      tvar1 = (I_U8)(sysInfo->rac & 255);
      tvar2 = tvar1>>2;
      bitstring[3] = tvar2;

      tvar1 = tvar1<<6;
      tvar2 = sysInfo->spgcCcchSup<<5;
      tvar3 = sysInfo->priorityAccessThr<<2;
      tvar4 = tvar1|tvar2|tvar3|sysInfo->networkControlOrder;
      bitstring[4] = tvar4;

      /* GPRS Cell Options */
      tvar1 = sysInfo->nmo<<6;
      tvar2 = (I_U8)(sysInfo->t3168<<3);
      tvar3 = (I_U8)(sysInfo->t3192);
      tvar4 = tvar1|tvar2|tvar3;
      bitstring[5] = tvar4;

      tvar1 = sysInfo->drxTimerMax<<5;
      tvar2 = sysInfo->accessBurstType<<4;
      tvar3 = sysInfo->controlAckType<<3;
      tvar4 = sysInfo->bsCvMax>>1;
      tvar5 = tvar1|tvar2|tvar3|tvar4;
      bitstring[6] = tvar5;

      tvar1 = sysInfo->bsCvMax<<7;
      tvar2 = sysInfo->panDec<<3;
      tvar3 = sysInfo->panInc;
      tvar4 = tvar1|64|tvar2|tvar3;
      bitstring[7] = tvar4;

      tvar1 = sysInfo->panMax<<5;
      

      if(egprsPresent == I_FALSE)
      {
      /*Changed in PCU R2.5 : Starts*/
     // tvar2 = 5;/* extension length */
     // tvar3 = tvar2>>2;
     // tvar4 = tvar1|tvar3;
     // bitstring[8] = tvar4;
     /* Since EGPRS is not supported by the cell */
     /* hence no need to fill egprsPacketChannelRequest and bepPeriod
      tvar1 = sysInfo->egprsPacketChannelRequest<<7;
      tvar2 = sysInfo->bepPeriod<<3; */
     // tvar1 = tvar2<<6;/* last 2 bits of extension length */
     // tvar3 = sysInfo->pfcFeatureMode<<4;
     // tvar4 = sysInfo->dtmSupport<<3;
     // tvar5 = sysInfo->bssPagingCoordination<<2;
     // tvar6 = sysInfo->ccnActive<<1;
     // tvar7 = sysInfo->nwExtUtbf;  
     // tvar7 = tvar1|0|tvar3|tvar4|tvar5|tvar6|tvar7;
     // bitstring[9] = tvar7;

   /* GPRS power Control parameters */
      tvar1 = tvar1 | 0 | (sysInfo->alpha & 15);
      bitstring[8] = tvar1;

      tvar1 = (sysInfo->tAvgW << 3) & 248;
      //tvar3 = tvar1|tvar2;
      //bitstring[10] = tvar3;
      //tvar1 = sysInfo->tAvgW<<7;
      tvar2 = (sysInfo->tAvgT >> 2) & 7;
      bitstring[9] = tvar1 | tvar2;
  
      //tvar2 = sysInfo->tAvgT<<2;
      //tvar3 = sysInfo->pcMeasChan<<1;
      //tvar4 = sysInfo->nAvgI>>3; 
      //tvar5 = tvar1|tvar2|tvar3|tvar4;  
      //bitstring[11] = tvar5;
      tvar1 = (sysInfo->tAvgT << 6 ) & 192;
      tvar2 = (sysInfo->pcMeasChan & 1);
      tvar3 = (sysInfo->nAvgI & 15);
      bitstring[10] = tvar1 | (tvar2 << 5) | (tvar3 << 1) | 0;
       
     // tvar1 = sysInfo->nAvgI<<5;
     // tvar2 = sysInfo->sgsnr<<3;
     // tvar3 = sysInfo->siStatusInd<<1;
     // tvar4 = tvar1|21|tvar2|tvar3; 
     // bitstring[12] = tvar4;
      bitstring[11] = (sysInfo->sgsnr << 7) | 64 | (sysInfo->siStatusInd << 5) | 11;

      bitstring[12] = SI_SPARE;
      /*Changed in PCU R2.5 : End*/
      bitstring[13] = SI_SPARE;
      bitstring[14] = SI_SPARE;
      bitstring[15] = SI_SPARE;
      bitstring[16] = SI_SPARE;
      bitstring[17] = SI_SPARE;
      bitstring[18] = SI_SPARE;
      bitstring[19] = SI_SPARE;
      bitstring[20] = SI_SPARE;
      bitstring[21] = SI_SPARE;
      }
#if 0
      if(egprsPresent == I_TRUE)
      {
        /*Changed in PCU R2.5 : Starts*/
      tvar2 = 5;/* extension length */
      tvar3 = tvar2>>2;
      tvar4 = tvar1|16|tvar3;
      bitstring[8] = tvar4;
      tvar1 = tvar2<<6;/* last 2 bits of extension length */
      /* Since EGPRS is supported by the cell */
      /* hence need to fill egprsPacketChannelRequest and bepPeriod */
      tvar2 = sysInfo->egprsPacketChannelRequest<<4;
      tvar3 = sysInfo->bepPeriod;
      tvar7 = tvar1|32|tvar2|tvar3;
      bitstring[9] = tvar7;

      /* GPRS power Control parameters */
      tvar1 = sysInfo->alpha<<4 ;
      tvar2 = sysInfo->tAvgW>>1;
      bitstring[10] = tvar1 | tvar2;

      tvar1 = (sysInfo->tAvgW) & 1;
      tvar2 = (sysInfo->tAvgW<<7);
      tvar3 = (sysInfo->tAvgT<<2);
      tvar4 = (sysInfo->pcMeasChan<<1);
      tvar5=  (sysInfo->nAvgI>>3);
      bitstring[11] = tvar2 | tvar3 | tvar4 | tvar5;
      tvar1 = (sysInfo->nAvgI & 7);
      tvar2 = sysInfo->nAvgI<<5;
      tvar3 = (sysInfo->sgsnr << 3);
      tvar4 = (sysInfo->siStatusInd << 1);
      bitstring[12] = tvar2 | 16 | tvar3 | 4 | tvar4 | 1;

      bitstring[13] = SI_SPARE;
      bitstring[14] = SI_SPARE;
      bitstring[15] = SI_SPARE;
      bitstring[16] = SI_SPARE;
      bitstring[17] = SI_SPARE;
      bitstring[18] = SI_SPARE;
      bitstring[19] = SI_SPARE;
      bitstring[20] = SI_SPARE;
      bitstring[21] = SI_SPARE;
      }
#endif
      if(egprsPresent == I_TRUE)
      {
        /*Changed in PCU R2.5 : Starts*/
      //tvar2 = 8;/* extension length */
      //tvar3 = tvar2>>2;
      //tvar4 = tvar1|16|tvar3;
		tvar4 = tvar1|16|3;//3 puts 11 in first two bits for length = 15
      	bitstring[8] = tvar4;
      //tvar1 = tvar2<<6;/* last 2 bits of extension length */
      /* Since EGPRS is supported by the cell */
      /* hence need to fill egprsPacketChannelRequest and bepPeriod */
      tvar2 = sysInfo->egprsPacketChannelRequest<<4;
      tvar3 = sysInfo->bepPeriod;
      //tvar7 = tvar1|32|tvar2|tvar3;
     tvar7 = 0xC0|32|tvar2|tvar3;//CO puts 11 in last two bits for length = 15
	  bitstring[9] = tvar7;
      tvar1 = 0;
      /* GPRS power Control parameters */
#if 0
 	  tvar1 = sysInfo->alpha<<1 ;
      tvar2 = sysInfo->tAvgW>>4;
      bitstring[10] = tvar1 | tvar2;

      tvar3 = (sysInfo->tAvgW) & 0x0f;
      tvar4 = (tvar3<<4);
      tvar5 = (sysInfo->tAvgT>>1);
      bitstring[11] = tvar4 | tvar5;
     

      tvar4 = (sysInfo->tAvgT) & 1;
      tvar5 = tvar4<<7; 
      tvar6 = (sysInfo->pcMeasChan<<6);
      tvar7 = (sysInfo->nAvgI<<2);
      tvar1 = sysInfo->sgsnr ;
      bitstring[12] = tvar5 | tvar6 | tvar7 | tvar1;
      tvar2 = (sysInfo->siStatusInd << 6);
      bitstring[13] = 128 | tvar2 | 0x2b;

      bitstring[14] = SI_SPARE;
#endif
	  bitstring[10] = 0x02;
      bitstring[11] = 0x29;
      bitstring[12] = 0x80;
      bitstring[13] = 0x86;

	  bitstring[14] = SI_SPARE;
	  bitstring[15] = SI_SPARE;
      bitstring[16] = SI_SPARE;
      bitstring[17] = SI_SPARE;
      bitstring[18] = SI_SPARE;
      bitstring[19] = SI_SPARE;
      bitstring[20] = SI_SPARE;
      bitstring[21] = SI_SPARE;
      }

   } 
   else if (pbcchPres != 0)
   {
      /*Changed for PCU R2.5 (Pbcch not supported)*/
      /*
      tvar1 = 64;
      tvar2 = sysInfo->psi1RepeatPeriod<<2;
      tvar3 = sysInfo->pb>>2;
      tvar4 = tvar1 | tvar2 | tvar3;
      bitstring[3] = tvar4;

      tvar1 = sysInfo->pb<<6;
      tvar2 = sysInfo->tsc<<3;
      tvar3 = sysInfo->tn;
      tvar4 = tvar1|tvar2|tvar3;
      bitstring[4] = tvar4;
      
      tvar2 = ((I_U16)sysInfo->arfcn )>>4;
      tvar3 =  64;
      bitstring[5] = tvar3|tvar2;
      tvar2 = ((I_U16)sysInfo->arfcn) & 0xf;
      tvar2 = tvar2<<4;  
      tvar3 = sysInfo->sgsnr<<2;
      tvar4 = sysInfo->siStatusInd;
      bitstring[6] = tvar2|tvar3|tvar4|0;
      
      bitstring[7] = SI_SPARE;
      bitstring[8] = SI_SPARE;
      bitstring[9] = SI_SPARE;
      bitstring[10] = SI_SPARE;
      bitstring[11] = SI_SPARE;
      bitstring[12] = SI_SPARE;
      bitstring[13] = SI_SPARE;
      bitstring[14] = SI_SPARE;
      bitstring[15] = SI_SPARE;
      bitstring[16] = SI_SPARE;
      bitstring[17] = SI_SPARE;
      bitstring[18] = SI_SPARE;
      bitstring[19] = SI_SPARE;
      bitstring[20] = SI_SPARE;
      bitstring[21] = SI_SPARE;
      */
   } 
#if 0
      bitstring[0] = 0x06;
      bitstring[1] = 0x00;
      bitstring[2] = 0x80;
      bitstring[3] = 0x00;
      bitstring[4] = 0x58;
      bitstring[5] = 0x40;
      bitstring[6] = 0x63;
      bitstring[7] = 0x4A;
      bitstring[8] = 0x32;
      bitstring[9] = 0x2A;
      bitstring[10] = 0x14;
      bitstring[11] = 0xC0;
      bitstring[12] = 0x41;
      bitstring[13] = SI_SPARE;
      bitstring[14] = SI_SPARE;
      bitstring[15] = SI_SPARE;
      bitstring[16] = SI_SPARE;
      bitstring[17] = SI_SPARE;
      bitstring[18] = SI_SPARE;
      bitstring[19] = SI_SPARE;
      bitstring[20] = SI_SPARE;
      bitstring[21] = SI_SPARE;
#endif
   l2PseudoLength =0;
   l2PseudoLength = l2PseudoLength << 2 | 1;
   *len = 23; 
   buff[0] = l2PseudoLength;
   memcpy(buff+1, bitstring,22); 

   return 0; 
}

/* 2G - 3G Handover */
/***********************************************************************************
  *  Function Name   : EncodeSysInformation2quat
  *  Args            : 1. SystemInfo2quat structure pointer
  *                    2. pointer to buff
  *                    3. length of buffer
  *
  *  Returns         : SUCCESS or  FAILURE.
  *
  *  Task            : This method will encode the system information 6 message buffer
  ***********************************************************************************/


/*I_S32  SysInfoEncoder::EncodeSysInformation2quat( SystemInfo2quat *sysInfo, I_U8 *buff, I_U16 *len,I_U8 index)*/
#if 0
I_S32 EncodeSysInformation2quat( SystemInfo2quat *sysInfo, I_U8 *buff, I_U16 *len,I_U8 index)
{

  I_U8 tvar1 = 0;
  I_U8 tvar2 = 0;
  I_U8 tvar3 = 0;
  I_U8 tvar4 = 0;
  I_U8 tvar5 = 0;
  I_U8 tvar6 = 0; 
  I_U8 tvar7 = 0;
  I_U8 tvar8 = 0;
  I_U8 tvar9 = 0;
  I_U8 tvar10 = 0;
  I_U8 tvar11 = 0;
  I_U8 tvar12 = 0;
  I_U8 tvar13 = 0;
  I_U8 tvar14 = 0;
  I_U8 tvar15 = 0;
  I_U8 tvar16 = 0;
  I_U8 tvar17 = 0;
  I_U8 tvar18 = 0;
  I_U8 tvar19 = 0;
  I_U8 tvar20 = 0;
  I_U8 tvar21 = 0;
  I_U8 tvar22 = 0;
  I_U8 tvar23 = 0;
  I_U8 tvar24 = 0;
  I_U8 tvar25 = 0;
  I_U8 tvar26 = 0;
  I_U8 tvar27 = 0;
  I_U8 tvar28 = 0;
  I_U8 tvar29 = 0;
  I_U8 tvar30 = 0;
  I_U8 tvar31 = 0;
  I_U8 tvar32 = 0;
  I_U8 tvar33 = 0;
  I_U8 tvar34 = 0;
  I_U8 tvar35 = 0;
  I_U8 tvar36 = 0;
  I_U8 firstByte;
  I_U8 bitCount = 0;
  I_U8 noOfBytes = 0;
  I_U8 noOfBits = 0;
  I_U8 loop = 0;
  I_U8 restOctet[20];
  I_U8 bitstring[2];
  I_U8 l2PseudoLength;
  I_U8 bitsUsedTillCellInfo = 0;


  I_U8 svar1 = 0;
  I_U8 svar2 = 0;
  I_U8 svar3 = 0;
  I_U8 svar4 = 0;
  I_U8 svar5 = 0;
  I_U8 svar6 = 0; 
  I_U8 svar7 = 0;
  I_U8 svar8 = 0;
  I_U8 svar9 = 0;
  I_U8 svar10 = 0;
  I_U8 svar11 = 0;
  I_U8 svar12 = 0;
  I_U8 svar13 = 0;
  I_U8 svar14 = 0;
  I_U8 svar15 = 0;
  I_U8 svar16 = 0;
  I_U8 svar17 = 0;
  I_U8 svar18 = 0;
  I_U8 svar19 = 0;
  I_U8 svar20 = 0;
  I_U8 svar21 = 0;
  I_U8 svar22 = 0;
  I_U8 svar23 = 0;
  I_U8 svar24 = 0;
  I_U8 svar25 = 0;
  I_U8 svar26 = 0;
  I_U8 svar27 = 0;
  I_U8 svar28 = 0;
  I_U8 svar29 = 0;
  I_U8 svar30 = 0;
  I_U8 svar31 = 0;
  I_U8 svar32 = 0;
  I_U8 svar33 = 0;
  I_U8 svar34 = 0;
  I_U8 svar35 = 0;
  I_U8 svar36 = 0;
  I_U8 svar37 = 0;

  I_U8 rvar1 = 0;
  I_U8 rvar2 = 0;
  I_U8 rvar3 = 0;
  I_U8 rvar4 = 0;
  I_U8 noOfCells = 0;

  I_U8 fillByte = 0 , i = 0;

  I_U8 PBIT[17] = {0,10,19,28,36,44,52,60,67,74,81,88,95,102,109,116,122};

  memset(bitstring, 0, sizeof(bitstring));
  memset(restOctet, 0, sizeof(restOctet));

  tvar1 = sysInfo->skipIndicator<<4 ;
  firstByte = tvar1|sysInfo->protocolDiscriminator;

  bitstring[0] = firstByte;
  bitstring[1] = sysInfo->messageType;

  LOG_PRINT(DEBUG," First two Bytes %d  %d",bitstring[0],bitstring[1]);
  sysInfo->si2QuatIndex = nextIndex;

  tvar3 = sysInfo->baInd<<7;
  tvar4 = sysInfo->baInd3g<<6;
  tvar5 = sysInfo->mpChangeMark<<5;
  tvar6 = sysInfo->si2QuatIndex<<1;
  tvar7 = sysInfo->si2QuatCount>>3;
    
  restOctet[0] = tvar3 | tvar4 | tvar5 | tvar6 | tvar7;
  
  tvar33 = sysInfo->si2QuatCount & 7;
  tvar8 = tvar33<<5;

  restOctet[1] = tvar8;

  restOctet[2] = 37 ;

  
  tvar9 =  sysInfo->fddDesc[index].fddArfcn>>7;

  restOctet[3] = tvar9;

  tvar10 = (sysInfo->fddDesc[index].fddArfcn) & (127);
  tvar11 = tvar10<<1;
  tvar12 = sysInfo->fddDesc[index].fddIndices0;

  restOctet[4] = tvar11 | tvar12;
  
  if(sysInfo->si2QuatIndex==0) 
    {
      if(sysInfo->fddDesc[index].noOfFddCells>10)
        noOfCells = 10;
      else
        noOfCells = sysInfo->fddDesc[index].noOfFddCells;
    }  
  else if(sysInfo->si2QuatIndex!=0) 
      { 
        if (sysInfo->fddDesc[index].noOfFddCells>14)
          noOfCells = 14;
        else
          noOfCells = sysInfo->fddDesc[index].noOfFddCells;
      }
  
  LOG_PRINT(DEBUG," No Of Cells =  %d",noOfCells);

  tvar12 = noOfCells<<3;
  svar1 = sysInfo->fddDesc[index].w[0]>>7;

  restOctet[5] = tvar12 | svar1;


  bitCount = PBIT[sysInfo->fddDesc[index].noOfFddCells];

  if((sysInfo->fddDesc[index].noOfFddCells>10) &&(sysInfo->si2QuatIndex == 0))
      bitCount = PBIT[10];
  
  else if(sysInfo->fddDesc[index].noOfFddCells>14)
      bitCount = PBIT[14];
    

  svar2 = (sysInfo->fddDesc[index].w[0]) & (127) ;
  svar3 = svar2<<1;
  svar4 = sysInfo->fddDesc[index].w[1]>>8;

  restOctet[6] = svar3 | svar4;

  svar5 = (sysInfo->fddDesc[index].w[1]) & (255);

  restOctet[7] = svar5 ;

  svar6 = sysInfo->fddDesc[index].w[2]>>1;

  restOctet[8] = svar6 ;

  svar7 = (sysInfo->fddDesc[index].w[2]) & (1);
  svar8 = svar7<<7;
  svar9 = sysInfo->fddDesc[index].w[3]>>1;

  restOctet[9] = svar8 | svar9;

  svar10 = (sysInfo->fddDesc[index].w[3]) & (1);
  svar11 = svar10<<7;
  svar12 = sysInfo->fddDesc[index].w[4]>>1;

  restOctet[10] = svar11 | svar12;

  svar13 = (sysInfo->fddDesc[index].w[4]) & (1);
  svar14 = svar13<<7;
  svar15 = sysInfo->fddDesc[index].w[5]>>1;

  restOctet[11] = svar14 | svar15;

  svar16 = (sysInfo->fddDesc[index].w[5]) & (1);
  svar17 = svar16<<7;
  svar18 = sysInfo->fddDesc[index].w[6]>>1;

  restOctet[12] = svar17 | svar18;

  svar19 = (sysInfo->fddDesc[index].w[6]) & (1);
  svar20 = svar19<<7;
  svar21 = sysInfo->fddDesc[index].w[7];

  restOctet[13] = svar20 | svar21;

  svar22 = sysInfo->fddDesc[index].w[8]<<1;
  svar23 = sysInfo->fddDesc[index].w[9]>>7;

  restOctet[14] = svar22 | svar23;

  svar24 = (sysInfo->fddDesc[index].w[9]) & (63);
  svar25 = svar24<<2;
  svar26 = sysInfo->fddDesc[index].w[10]>>5;

  restOctet[15] = svar25 | svar26;

  svar27= (sysInfo->fddDesc[index].w[10]) & (31);
  svar28 = svar27<<3;
  svar29 = sysInfo->fddDesc[index].w[11]>>4;

  restOctet[16] = svar28 | svar29;

  svar30 = (sysInfo->fddDesc[index].w[11]) & (15);
  svar31 = svar30<<4;
  svar32 = sysInfo->fddDesc[index].w[12]>>3;

  restOctet[17] = svar31 | svar32;

  svar33 = (sysInfo->fddDesc[index].w[12]) & (7);
  svar34 = svar33<<5;
  svar35 = sysInfo->fddDesc[index].w[13]>>2;

  restOctet[18] = svar34 | svar35;

  svar36 = (sysInfo->fddDesc[index].w[13]) & (3);
  svar37 = svar36<<6;

  
  restOctet[19] = svar37 ;


  /* Encoding of fields present after FDD CELL INFORMATION PARAMTERS */

  bitsUsedTillCellInfo = 45+bitCount+3; //( 3 bits for 001 fixed for optional and mandatory)
  noOfBytes = bitsUsedTillCellInfo/8;
  noOfBits = 8-(bitsUsedTillCellInfo%8);
  loop = noOfBytes;
  fillByte = loop;

  LOG_PRINT(DEBUG," Bytes= %d Bits= %d Loop =%d ",noOfBytes,noOfBits,loop);

  if( sysInfo->si2QuatIndex == 0)
  {
    switch(noOfBits)
    {
      case 8:
        {
          LOG_PRINT(DEBUG," 1st restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar1 = 0<<2;
          rvar2 = 0<<1;
          rvar3 = 1;
          restOctet[loop-1] = restOctet[loop-1] | rvar1 | rvar2 | rvar3; 
          LOG_PRINT(DEBUG," 2nd restOctet[loop-1]=  %d",restOctet[loop-1]);
          tvar16 = sysInfo->qSearch_I<<4;
          tvar17 = sysInfo->qSearch_C_Initial<<3;
          tvar18 = 1<<2;
          tvar19 = sysInfo->fdd_Qoffset>>2;
          restOctet[loop] = tvar16 | tvar17 | tvar18 | tvar19;
          LOG_PRINT(DEBUG," restOctet[loop]=  %d",restOctet[loop]);
          tvar20 = sysInfo->fdd_Qoffset & 3;
          tvar21 = tvar20<<6;
          tvar22 = sysInfo->fdd_Rep_Quant<<5;
          tvar23 = sysInfo->fdd_Multirat_Report<<3;
          tvar24 = sysInfo->fdd_Qmin;
          restOctet[loop+1] = tvar21 | tvar22 | tvar23 | tvar24 ;
          LOG_PRINT(DEBUG," restOctet[loop+1]=  %d",restOctet[loop+1]);
          tvar24 = 0<<7;
          tvar25 = 0<<6;
          tvar26 = 1<<5;
          tvar27 = sysInfo->fdd_Qmin_Offset<<2;
          tvar28 = sysInfo->fdd_Rscpmin>>2;
          restOctet[loop+2] = tvar24 | tvar25 |tvar26 | tvar27 | tvar28;
          LOG_PRINT(DEBUG," restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar29 = sysInfo->fdd_Rscpmin & 3;
          tvar30 = sysInfo->fdd_Rscpmin<<6;
          restOctet[loop+3] = tvar30;
          LOG_PRINT(DEBUG," restOctet[loop+3]=  %d",restOctet[loop+3]);
          fillByte = loop+4;
        }
        break;
      
      
      
      
      case 1:
        {
          rvar1 = 0<<3;
          rvar2 = 0<<2;
          rvar3 = 1<<1;
          tvar15 = sysInfo->qSearch_I>>3;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 ;
          tvar16 = sysInfo->qSearch_I & 7;
          tvar17 = tvar16<<5;
          tvar18 = sysInfo->qSearch_C_Initial<<4;
          tvar19 = 1<<3;
          tvar20 = sysInfo->fdd_Qoffset>>1;
          restOctet[loop+1] = tvar17 | tvar18 | tvar19 | tvar20 ;
          tvar21 = sysInfo->fdd_Qoffset & 7;
          tvar22 = tvar21<<5;
          tvar23 = sysInfo->fdd_Rep_Quant<<4;
          tvar24 = sysInfo->fdd_Multirat_Report<<2; 
          tvar25 = sysInfo->fdd_Qmin<<1;
          restOctet[loop+2] = tvar21 | tvar22 | tvar23 | tvar24 | tvar25 ;
          tvar26 = sysInfo->fdd_Qmin & 3;
          tvar27 = tvar26<<6;
          tvar28 = 0<<5;
          tvar29 = 0<<4;
          tvar30 = 1<<3;
          tvar31 = sysInfo->fdd_Qmin_Offset;
          restOctet[loop+3] = tvar27 | tvar28 | tvar29 | tvar30 | tvar31;
          tvar32  = sysInfo->fdd_Rscpmin<<4;
          restOctet[loop+4] = tvar32;
          fillByte = loop+5;

        }
        break;




      case 2:
        {
          rvar1 = 0<<4;
          rvar2 = 0<<3;
          rvar3 = 1<<2;
          tvar15 = sysInfo->qSearch_I>>2;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 ;
          tvar16 = sysInfo->qSearch_I & 3;
          tvar17 = tvar16<<6;
          tvar18 = sysInfo->qSearch_C_Initial<<5;
          tvar19 = 1<<4;
          tvar20 = sysInfo->fdd_Qoffset;
          restOctet[loop+1] = tvar17 | tvar18 | tvar19 | tvar20 ;
          tvar21 = sysInfo->fdd_Rep_Quant<<7;
          tvar22 = sysInfo->fdd_Multirat_Report<<5; ;
          tvar23 = sysInfo->fdd_Qmin<<2;
          tvar24 = 0<<1;
          tvar25 = 0;
          restOctet[loop+2] = tvar21 | tvar22 | tvar23 | tvar24 | tvar25 ;
          tvar26 = 1<<7;
          tvar27 = sysInfo->fdd_Qmin_Offset<<4;
          tvar28  = sysInfo->fdd_Rscpmin;
          restOctet[loop+3] = tvar26 | tvar27 | tvar28;
          fillByte = loop+4;

        }
        break;


      case 3:
        {
          rvar1 = 0<<5;
          rvar2 = 0<<4;
          rvar3 = 1<<3;
          tvar15 = sysInfo->qSearch_I>>1;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 ;
          tvar16 = sysInfo->qSearch_I & 1;
          tvar17 = tvar16<<7;
          tvar18 = sysInfo->qSearch_C_Initial<<6;
          tvar19 = 1<<5;
          tvar20 = sysInfo->fdd_Qoffset<<1;
          tvar21 = sysInfo->fdd_Rep_Quant;
          restOctet[loop+1] = tvar17 | tvar18 | tvar19 | tvar20 | tvar21;
          tvar22 = sysInfo->fdd_Multirat_Report<<6; ;
          tvar23 = sysInfo->fdd_Qmin<<3;
          tvar24 = 0<<2;
          tvar25 = 0<<1;
          tvar26 = 1;
          restOctet[loop+2] = tvar22 | tvar23 | tvar24 | tvar25 | tvar26 ;
          tvar28 = sysInfo->fdd_Qmin_Offset<<5;
          tvar29  = sysInfo->fdd_Rscpmin<<1;
          restOctet[loop+3] = tvar28 | tvar29;
          fillByte = loop+4;

        }
        break;


      case 4:
        {

          rvar1 = 0<<6;
          rvar2 = 0<<5;
          rvar3 = 1<<4;
          tvar15 = sysInfo->qSearch_I;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 ;
          tvar16 = sysInfo->qSearch_C_Initial<<7;
          tvar17 = 1<<6;
          tvar18 = sysInfo->fdd_Qoffset<<2;
          tvar19 = sysInfo->fdd_Rep_Quant<<1;
          tvar20 = sysInfo->fdd_Multirat_Report>>1;
          restOctet[loop+1] = tvar16 | tvar17 | tvar18 | tvar19 | tvar20;
          tvar21 = sysInfo->fdd_Multirat_Report & 1;
          tvar22 = tvar21<<7;
          tvar23 = sysInfo->fdd_Qmin<<4;
          tvar24 = 0<<3;
          tvar25 = 0<<2;
          tvar26 = 1<<1;
          tvar27 = sysInfo->fdd_Qmin_Offset>>2;
          restOctet[loop+2] = tvar22 | tvar23 | tvar24 | tvar25 | tvar26 | tvar27;
          tvar28 = sysInfo->fdd_Qmin_Offset & (3);
          tvar29 = tvar28<<6;
          tvar30  = sysInfo->fdd_Rscpmin<<2;
          restOctet[loop+3] = tvar29 | tvar30;
          fillByte = loop+4;

        }
        break;


      case 5:
        {
          rvar1 = 0<<7;
          rvar2 = 0<<6;
          rvar3 = 1<<5;
          tvar15 = sysInfo->qSearch_I<<1;
          tvar16 = sysInfo->qSearch_C_Initial;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          tvar17 = 1<<7;
          tvar18 = sysInfo->fdd_Qoffset<<3;
          tvar19 = sysInfo->fdd_Rep_Quant<<2;
          tvar20 = sysInfo->fdd_Multirat_Report;
          restOctet[loop+1] = tvar17 | tvar18 | tvar19 | tvar20;
          tvar21 = sysInfo->fdd_Qmin<<5;
          tvar22 = 0<<4;
          tvar23 = 0<<3;
          tvar24 = 1<<2;
          tvar25 = sysInfo->fdd_Qmin_Offset>>1;
          restOctet[loop+2] = tvar21 | tvar22 | tvar23 | tvar24 | tvar25;
          tvar26 = sysInfo->fdd_Qmin_Offset & (1);
          tvar27 = tvar26<<7;
          tvar28  = sysInfo->fdd_Rscpmin<<3;
          restOctet[loop+3] = tvar27 | tvar28;
          fillByte = loop+4;
        }
        break;

      case 6:
        {
          LOG_PRINT(DEBUG,"1st restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar1 = 0;
          restOctet[loop-1] = restOctet[loop-1]| rvar1 ;
          LOG_PRINT(DEBUG," 2nd restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar2 = 0<<7;
          rvar3 = 1<<6;
          tvar15 = sysInfo->qSearch_I<<2;
          tvar16 = sysInfo->qSearch_C_Initial<<1;
          tvar17 = 1;
          restOctet[loop] = rvar2 | rvar3 | tvar15 | tvar16 | tvar17;
          LOG_PRINT(DEBUG,"  restOctet[loop]=  %d",restOctet[loop]);
          tvar18 = sysInfo->fdd_Qoffset<<4;
          tvar19 = sysInfo->fdd_Rep_Quant<<3;
          tvar20 = sysInfo->fdd_Multirat_Report<<1;
          tvar21 = sysInfo->fdd_Qmin>>2;
          restOctet[loop+1] = tvar18 | tvar19 | tvar20 | tvar21;
          LOG_PRINT(DEBUG,"  restOctet[loop+1]=  %d",restOctet[loop+1]);
          tvar22 = sysInfo->fdd_Qmin & 3;
          tvar23 = tvar22<<6;
          tvar24 = 0<<5;
          tvar25 = 1<<4;
          restOctet[loop+2] = tvar23 | tvar24 | tvar25 | 7 ;
          LOG_PRINT(DEBUG,"  restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar26 = 1<<7;
          tvar27 = 0<<6;
          tvar28 = 0<<5;
          tvar29 = 0<<4;
          tvar30 = 0<<3;
          tvar31 = 1<<2;
//          tvar31 = 0<<2;
          tvar32 = 1<<1;
          tvar33 = sysInfo->fdd_Qmin_Offset>>2;
          //restOctet[loop+3] = tvar26 | tvar27 | tvar28 | tvar29 | tvar30 | tvar31 | tvar32 | 1;
          restOctet[loop+3] = tvar26 | tvar27 | tvar28 | tvar29 | tvar30 | tvar31 | tvar32 | tvar33;
          LOG_PRINT(DEBUG," 1st restOctet[loop+3]=  %d",restOctet[loop+3]);
          tvar34 = sysInfo->fdd_Qmin_Offset & 3;
          tvar35 = tvar34<<6;
          tvar36 = sysInfo->fdd_Rscpmin<<2;
          restOctet[loop+4] = tvar35 | tvar36 | 3;
          LOG_PRINT(DEBUG," 1st restOctet[loop+4]=  %d",restOctet[loop+4]);

          restOctet[loop+5] = 0x07;
          LOG_PRINT(DEBUG," 1st restOctet[loop+5]=  %d",restOctet[loop+5]);
           
          /*tvar25 = 0<<4;
          tvar26 = 1<<3;
          tvar27 = sysInfo->fdd_Qmin_Offset;
          restOctet[loop+2] = tvar23 | tvar24 | tvar25 | tvar26 | tvar26 | tvar27;
          LOG_PRINT(DEBUG,"  restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar28 = sysInfo->fdd_Rscpmin<<4 ;
          restOctet[loop+3] = tvar28;
          LOG_PRINT(DEBUG," 1st restOctet[loop+3]=  %d",restOctet[loop+3]);*/
          fillByte = loop+6;
        }
        break;


      case 7:
        {
          LOG_PRINT(DEBUG,"1st restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar1 = 0<<1;
          rvar2 = 0;
          restOctet[loop-1] = restOctet[loop-1]| rvar1 | rvar2 ;
          LOG_PRINT(DEBUG," 2nd restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar3 = 1<<7;
          tvar15 = sysInfo->qSearch_I<<3;
          tvar16 = sysInfo->qSearch_C_Initial<<2;
          tvar17 = 1<<1;
          tvar18 = sysInfo->fdd_Qoffset>>3;
          restOctet[loop] = rvar3 | tvar15 | tvar16 | tvar17 | tvar18;
          LOG_PRINT(DEBUG,"  restOctet[loop]=  %d",restOctet[loop]);
          tvar19 = sysInfo->fdd_Qoffset & 7;
          tvar20 = tvar19<<5;
          tvar21 = sysInfo->fdd_Rep_Quant<<4;
          tvar22 = sysInfo->fdd_Multirat_Report<<2;
          tvar23 = sysInfo->fdd_Qmin>>1;
          restOctet[loop+1] = tvar20 | tvar21 | tvar22 | tvar23;
          LOG_PRINT(DEBUG,"  restOctet[loop+1]=  %d",restOctet[loop+1]);
          tvar22 = sysInfo->fdd_Qmin & 1;
          tvar23 = tvar22<<7;
          tvar24 = 0<<6;
          tvar25 = 0<<5;
          tvar26 = 1<<4;
          /*Testing Code
             tvar27 = 1<<3;
          tvar28 = sysInfo->fdd_Qmin_Offset;
          restOctet[loop+2] = tvar23 | tvar24 | tvar25 | tvar26 | tvar26 | tvar27 | tvar28;
          LOG_PRINT(DEBUG,"  restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar29 = sysInfo->fdd_Rscpmin<<4;
          restOctet[loop+3] = tvar29;
          LOG_PRINT(DEBUG," 1st restOctet[loop+3]=  %d",restOctet[loop+3]);
          fillByte = loop+4;*/
          tvar27 = sysInfo->fdd_Qmin_Offset<<1;
          tvar28 = sysInfo->fdd_Rscpmin>>1;
          restOctet[loop+2] = tvar23 | tvar24 | tvar25 | tvar26 | tvar26 | tvar27 | tvar28;
          LOG_PRINT(DEBUG,"  restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar29 = sysInfo->fdd_Rscpmin & 7 ;
          tvar30 = sysInfo->fdd_Rscpmin<<5;
          restOctet[loop+3] = tvar30;
          LOG_PRINT(DEBUG," 1st restOctet[loop+3]=  %d",restOctet[loop+3]);
          fillByte = loop+4;


        }
        break;

      default:
        break;

    }
  }    

  else if( sysInfo->si2QuatIndex != 0)
  {
    switch(noOfBits)
    {
      case 8:
        {
          rvar1 = 0<<2;
          rvar2 = 0<<1;
          rvar3 = 0;
          restOctet[loop-1] = restOctet[loop-1] | rvar1 | rvar2 | rvar3; 
          tvar16 = 0<<7;
          tvar17 = 0<<6;
          restOctet[loop] = tvar16 | tvar17 ;
          fillByte = loop+1;
        }
        break;
      
      
      
      
      case 1:
        {
          rvar1 = 0<<3;
          rvar2 = 0<<2;
          rvar3 = 0<<1;
          tvar15 = 0;          
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15; 
          tvar16 = 0<<7;
          restOctet[loop+1] = tvar16 ;
          fillByte = loop+2;
        }
        break;




      case 2:
        {
          rvar1 = 0<<4;
          rvar2 = 0<<3;
          rvar3 = 0<<2;
          tvar15 = 0<<1;
          tvar16 = 0;          
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;


      case 3:
        {
          rvar1 = 0<<5;
          rvar2 = 0<<4;
          rvar3 = 0<<3;
          tvar15 = 0<<2;          
          tvar16 = 0<<1;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;


      case 4:
        {
          rvar1 = 0<<6;
          rvar2 = 0<<5;
          rvar3 = 0<<4;
          tvar15 = 0<<3;          
          tvar16 = 0<<2;          
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;


      case 5:
        {
          rvar1 = 0<<7;
          rvar2 = 0<<6;
          rvar3 = 0<<5;
          tvar15 = 0<<4;
          tvar16 = 0<<3;
          restOctet[loop] = rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;

      case 6:
        {
          rvar1 = 0;
          restOctet[loop-1] =  restOctet[loop-1] |rvar1 ;
          rvar3 = 0<<7;
          rvar4 = 0<<6;
          tvar15 = 0<<5;
          tvar16 = 0<<4;
          restOctet[loop] =  rvar3 | rvar4 | tvar15 | tvar16 ;
          fillByte = loop+1;
        }
        break;


      case 7:
        {
          rvar1 = 0;
          rvar2 = 0<<1;
          restOctet[loop-1] = restOctet[loop-1] | rvar1 | rvar2 ;
          rvar4 = 0<<7;
          tvar15 = 0<<6;
          tvar16 = 0<<5;
          restOctet[loop] =  rvar4 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;

      default:
        break;

    }
  }


  LOG_PRINT(DEBUG," fillByte=  %d",fillByte);
  if(fillByte<20)
  {
    for(i=fillByte;i<20;i++)
    {
      restOctet[i] = SI_SPARE;
    }
  } 


  nextIndex++;


  l2PseudoLength = 1;
  l2PseudoLength = l2PseudoLength << 2 | 1;
  *len = *len + 23;
  buff[0] = l2PseudoLength;
  memcpy(buff+1, bitstring, 2);
  memcpy(buff+3, restOctet, 20);

  return 0;

}
#else
I_S32 EncodeSysInformation2quat( SystemInfo2quat *sysInfo, I_U8 *buff, I_U16 *len,I_U8 index,I_U8 zeroPresent)
{
  BufEncInfo t;
  BufEncInfo *b = &t;
  I_U8 k=0;
  I_U8 l2PseudoLength;
  I_U8 noOfCells = 0;
  I_U8 Index_Start_3G_Val=0;

  I_U8 PBIT[17] = {0,10,19,28,36,44,52,60,67,74,81,88,95,102,109,116,122};
  I_U8 PBIT_r[17] = {10, 9, 9, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6 };

  for(k=0;k<noOfCells;k++)
  {
    LOG_PRINT(DEBUG," index=%d, w[%d] =  %d",index, k, sysInfo->fddDesc[index].w[k]);
  }
  
    LOG_PRINT(DEBUG," b->buf   %d", b->buf);
  b->buf = buff;
  b->octPos = 0;
  b->bitPos = 0;

  l2PseudoLength = 1;
  l2PseudoLength = l2PseudoLength << 2 | 1;

  STUFFVAL(b, 8, l2PseudoLength);
  STUFFVAL(b, 4, sysInfo->skipIndicator);
  STUFFVAL(b, 4, sysInfo->protocolDiscriminator);
  STUFFVAL(b, 8, sysInfo->messageType);

  sysInfo->si2QuatIndex = nextIndex;

  STUFFVAL(b, 1, sysInfo->baInd);
  STUFFVAL(b, 1, sysInfo->baInd3g);
  STUFFVAL(b, 1, sysInfo->mpChangeMark);
  STUFFVAL(b, 4, sysInfo->si2QuatIndex);
  STUFFVAL(b, 4, sysInfo->si2QuatCount - 1);


  STUFF0(b); // For Meareument Parameters Description
  STUFF0(b); // For GPRS_Real Time Difference Description
  STUFF0(b); // For GPRS_BSIC Description
  STUFF0(b); // For GPRS_REPORT Priority Description
  STUFF0(b); // For GPRS_MEASUREMENT_Parameters Description
  STUFF0(b); // For NC Measurements Parameters
  STUFF0(b); // For Extension Length

  STUFF1(b); // For 3G Neighbour Cell Description

  if(sysInfo->si2QuatIndex== 0)
  {
    //STUFF0(b);  // Index_Start_3G (not present)
    STUFF1(b);  // Index_Start_3G (present)
    STUFFVAL(b, 7, sysInfo->si2QuatIndex*8);
  }
  else if(sysInfo->si2QuatIndex!=0) 
  { 
    STUFF1(b);  // Index_Start_3G (present)
    STUFFVAL(b, 7, sysInfo->indexStart3G);
  }

  STUFF0(b); // Absoluete_index_start_EMR
  STUFF1(b); // UTRAN FDD Description

  STUFF0(b); // BANDWIDTH_FDD
  STUFF1(b); // Repeated UTRAN FDD Neighbour Cells

  STUFF0(b);
  STUFFVAL(b, 14, sysInfo->fddDesc[index].fddArfcn); // FDD-ARFCN
  STUFFVAL(b, 1, sysInfo->fddDesc[index].fddIndices0); // FDD_Indic0 
  
  if(sysInfo->fddDesc[index].noOfFddCells>8)
    noOfCells = 8;
  else if((sysInfo->fddDesc[index].noOfFddCells==8) && (zeroPresent == I_TRUE))
    noOfCells = 7;
  else if((sysInfo->fddDesc[index].noOfFddCells==8))
    noOfCells = 8;
  else
   noOfCells = sysInfo->fddDesc[index].noOfFddCells;
  
  LOG_PRINT(DEBUG," 2quat No Of Cells =  %d",noOfCells);
  STUFFVAL(b, 5, noOfCells);

  for(k=0;k<noOfCells;k++)
  {
    STUFFVAL(b, PBIT_r[k], sysInfo->fddDesc[index].w[k]);
    LOG_PRINT(DEBUG," index=%d, w[%d] =  %d",index, k, sysInfo->fddDesc[index].w[k]);
  }

  STUFF0(b); // For ending Repeated UTRAN FDD Neighbour Cells 
  STUFF0(b); // For UTRAN TDD Description 

  //Lets send 3g Measurement parameters description only on the first SI2Qaut index
  if(sysInfo->si2QuatIndex == 0)
  {
    LOG_PRINT(DEBUG,"b->octPos=%d", b->octPos);
    STUFF1(b);
/* NOte  
     qSearch_I = 7 (from vodafone logs)
     fdd_Multirat_Report = 1 (from vodafone logs)
     qmin =7
     */
    //sysInfo->qSearch_I = 7;
    //sysInfo->fdd_Multirat_Report=1;
    //sysInfo->fdd_Qmin = 7;

    STUFFVAL(b, 4, sysInfo->qSearch_I);
    STUFFVAL(b, 1, sysInfo->qSearch_C_Initial);

    STUFF1(b); // for FDD Information

    STUFFVAL(b, 4, sysInfo->fdd_Qoffset);
    STUFFVAL(b, 1, sysInfo->fdd_Rep_Quant);

    STUFFVAL(b, 2, sysInfo->fdd_Multirat_Report);
    STUFFVAL(b, 3, sysInfo->fdd_Qmin);
    STUFF0(b); // TDD Information
  }
  else
  {
    STUFF0(b);
  }

#if 0
  STUFF0(b); // For GPRS_3G_MEAUSUREMENT Parameters Description
#else
  STUFF1(b); // For GPRS_3G_MEAUSUREMENT Parameters Description
  STUFFVAL(b, 4, 7);  // Lets put Qsearch_P=7, (from vodafone logs)
  STUFFVAL(b, 1, sysInfo->wcdmaSearchPrio); // For 3G_Search_Prio 
  STUFF0(b); //FDD parameter  
  STUFF0(b);
  STUFF0(b); // TDD Parameters
  STUFF0(b);

#endif


  if(nextIndex == (sysInfo->si2QuatCount - 1)){
    // Following code is to STUFF 'H' for adding additional 3g parameters
    if( b->bitPos == 0 ||
        b->bitPos == 1 ||
        b->bitPos == 3 ||
        b->bitPos == 5 )
    {
      STUFF1(b);
    }
    else
    {
      STUFF0(b);
    }

    STUFF1(b); // For 3G Additional Measurement Parameteres Description
    STUFFVAL(b, 3, sysInfo->fdd_Qmin_Offset);
    STUFFVAL(b, 4, sysInfo->fdd_Rscpmin);
    STUFF1(b); //3G Additional Measurement(2) Parameters Description
    // Following code is to STUFF 'L' for adding additional 3g parameters
# if 0 
    if( b->bitPos == 0 ||
        b->bitPos == 1 ||
        b->bitPos == 3 ||
        b->bitPos == 5 )
    {
      STUFF0(b);
    }
    else
    {
      STUFF1(b);
    }
#endif
      STUFF1(b);//for adding additional 3g parameters Threshold _2 
    STUFFVAL(b, 6, sysInfo->fdd_reporting_Threashold_2);
  }
  else {
    // Following code is to STUFF 'L' for adding additional 3g parameters
    if( b->bitPos == 0 ||
        b->bitPos == 1 ||
        b->bitPos == 3 ||
        b->bitPos == 5 )
    {
      STUFF0(b);
    }
    else
    {
      STUFF1(b);
    }
  }  
  LOG_PRINT(DEBUG,"b->octPos=%d, b->bitPos=%d", b->octPos, b->bitPos);
  fillPadding(b, 23);
  *len = *len + 23;

  nextIndex++;
  return 0;
}
#endif

/***********************************************************************************
  *  Function Name   : EncodeMeasInfo
  *  Args            : 1. SystemInfo2quat structure pointer
  *                    2. pointer to buff
  *                    3. length of buffer
  *
  *  Returns         : SUCCESS or  FAILURE.
  *
  *  Task            : This method will encode the system information 6 message buffer
  ***********************************************************************************/

#if 0

I_S32 EncodeMeasInfo( MeasInfo *measInfo, I_U8 *buff, I_U16 *len,I_U8 index)
{

  I_U8 tvar1 = 0;
  I_U8 tvar2 = 0;
  I_U8 tvar3 = 0;
  I_U8 tvar4 = 0;
  I_U8 tvar5 = 0;
  I_U8 tvar6 = 0; 
  I_U8 tvar7 = 0;
  I_U8 tvar8 = 0;
  I_U8 tvar9 = 0;
  I_U8 tvar10 = 0;
  I_U8 tvar11 = 0;
  I_U8 tvar12 = 0;
  I_U8 tvar13 = 0;
  I_U8 tvar14 = 0;
  I_U8 tvar15 = 0;
  I_U8 tvar16 = 0;
  I_U8 tvar17 = 0;
  I_U8 tvar18 = 0;
  I_U8 tvar19 = 0;
  I_U8 tvar20 = 0;
  I_U8 tvar21 = 0;
  I_U8 tvar22 = 0;
  I_U8 tvar23 = 0;
  I_U8 tvar24 = 0;
  I_U8 tvar25 = 0;
  I_U8 tvar26 = 0;
  I_U8 tvar27 = 0;
  I_U8 tvar28 = 0;
  I_U8 tvar29 = 0;
  I_U8 tvar30 = 0;
  I_U8 tvar31 = 0;
  I_U8 tvar32 = 0;
  I_U8 tvar33 = 0;
  I_U8 tvar34 = 0;
  I_U8 tvar35 = 0;
  I_U8 tvar36 = 0;
  I_U8 firstByte;
  I_U8 bitCount = 0;
  I_U8 noOfBytes = 0;
  I_U8 noOfBits = 0;
  I_U8 loop = 0;
  I_U8 restOctet[20];
  I_U8 bitstring[2];
  I_U8 l2PseudoLength;
  I_U8 bitsUsedTillCellInfo = 0;


  I_U8 svar1 = 0;
  I_U8 svar2 = 0;
  I_U8 svar3 = 0;
  I_U8 svar4 = 0;
  I_U8 svar5 = 0;
  I_U8 svar6 = 0; 
  I_U8 svar7 = 0;
  I_U8 svar8 = 0;
  I_U8 svar9 = 0;
  I_U8 svar10 = 0;
  I_U8 svar11 = 0;
  I_U8 svar12 = 0;
  I_U8 svar13 = 0;
  I_U8 svar14 = 0;
  I_U8 svar15 = 0;
  I_U8 svar16 = 0;
  I_U8 svar17 = 0;
  I_U8 svar18 = 0;
  I_U8 svar19 = 0;
  I_U8 svar20 = 0;
  I_U8 svar21 = 0;
  I_U8 svar22 = 0;
  I_U8 svar23 = 0;
  I_U8 svar24 = 0;
  I_U8 svar25 = 0;
  I_U8 svar26 = 0;
  I_U8 svar27 = 0;
  I_U8 svar28 = 0;
  I_U8 svar29 = 0;
  I_U8 svar30 = 0;
  I_U8 svar31 = 0;
  I_U8 svar32 = 0;
  I_U8 svar33 = 0;
  I_U8 svar34 = 0;
  I_U8 svar35 = 0;
  I_U8 svar36 = 0;
  I_U8 svar37 = 0;

  I_U8 rvar1 = 0;
  I_U8 rvar2 = 0;
  I_U8 rvar3 = 0;
  I_U8 rvar4 = 0;
  I_U8 noOfCells = 0;

  I_U8 fillByte = 0 , i = 0;

  I_U8 PBIT[17] = {0,10,19,28,36,44,52,60,67,74,81,88,95,102,109,116,122};

  memset(restOctet, 0, sizeof(restOctet));

  tvar1 = measInfo->protocolDiscriminator<<7 ;
  tvar2 = measInfo->messageType<<2;
  tvar3 = measInfo->shortL2Header;

  buff[0] = tvar1 | tvar2 | tvar3;


  LOG_PRINT(DEBUG," First two Bytes %d ",buff[0]);
  measInfo->miIndex = msInfoIndex;

  tvar4 = measInfo->baInd<<7;
  tvar5 = measInfo->baInd3g<<6;
  tvar6 = measInfo->mpChangeMark<<5;
  tvar7 = measInfo->miIndex<<1;
  tvar8 = measInfo->miCount>>3;
    
  restOctet[0] =  tvar4 | tvar5 | tvar6 | tvar7 | tvar8;
  
  tvar9 = measInfo->miCount & 7;
  tvar10 = tvar9<<5;
  tvar11 = measInfo->pwrc<<4;
  tvar12 = measInfo->report_type<<3;
  tvar13 = measInfo->reporting_rate<<2;
  tvar14 = measInfo->invalidBsic<<1;

  restOctet[1] = tvar10 | tvar11 | tvar12 | tvar13 | tvar14 ;

  /*tvar15 = 0<<7;
  tvar16 = 0<<6;
  tvar17 = 0<<5;
  tvar18 = 0<<4;
  tvar19 = 1<<3;*/

  restOctet[2] = 10 ;

  
//  tvar9 =  sysInfo->fddDesc[index].fddArfcn>>7;

  restOctet[3] = 1;
   
  tvar15 = 1<<6;
  tvar16 = measInfo->fddDesc[index].fddArfcn>>9;

  restOctet[4] = tvar15 | tvar16;
  
  tvar17 = (measInfo->fddDesc[index].fddArfcn>>1) ;
  tvar18 = tvar17 & (255);
  
  restOctet[5] = tvar18;

  
  tvar19 = (measInfo->fddDesc[index].fddArfcn) & 1  ;
  tvar20 = tvar19<<7;
  tvar21 = measInfo->fddDesc[index].fddIndices0<<6;

  
  if(measInfo->miIndex==0) 
    {
      if(measInfo->fddDesc[index].noOfFddCells>10)
        noOfCells = 10;
      else
        noOfCells = measInfo->fddDesc[index].noOfFddCells;
    }  
  else if(measInfo->miIndex!=0) 
      { 
        if (measInfo->fddDesc[index].noOfFddCells>14)
          noOfCells = 14;
        else
          noOfCells = measInfo->fddDesc[index].noOfFddCells;
      }
  
  LOG_PRINT(DEBUG," No Of Cells =  %d",noOfCells);

  tvar22 = noOfCells<<1;
  svar1 = measInfo->fddDesc[index].w1>>9;

  
  restOctet[6] = tvar20 | tvar21 |tvar22 | svar1;


  bitCount = PBIT[measInfo->fddDesc[index].noOfFddCells];

  if((measInfo->fddDesc[index].noOfFddCells>10) &&(measInfo->miIndex == 0))
      bitCount = PBIT[10];
  
  else if(measInfo->fddDesc[index].noOfFddCells>14)
      bitCount = PBIT[14];
    

  svar2 = (measInfo->fddDesc[index].w1)>>1 ;
  svar3 = svar2 & 255;

  restOctet[7] = svar3;

  svar4 = (measInfo->fddDesc[index].w1) & 1;
  svar5 = svar4<<7;
  
/*  svar4 = sysInfo->fddDesc[index].w2>>8;

  restOctet[7] = svar3 | svar4;

  svar5 = (sysInfo->fddDesc[index].w2) & (255);

  restOctet[7] = svar5 ;

  svar6 = sysInfo->fddDesc[index].w3>>1;

  restOctet[8] = svar6 ;

  svar7 = (sysInfo->fddDesc[index].w3) & (1);
  svar8 = svar7<<7;
  svar9 = sysInfo->fddDesc[index].w4>>1;

  restOctet[9] = svar8 | svar9;

  svar10 = (sysInfo->fddDesc[index].w4) & (1);
  svar11 = svar10<<7;
  svar12 = sysInfo->fddDesc[index].w5>>1;

  restOctet[10] = svar11 | svar12;

  svar13 = (sysInfo->fddDesc[index].w5) & (1);
  svar14 = svar13<<7;
  svar15 = sysInfo->fddDesc[index].w6>>1;

  restOctet[11] = svar14 | svar15;

  svar16 = (sysInfo->fddDesc[index].w6) & (1);
  svar17 = svar16<<7;
  svar18 = sysInfo->fddDesc[index].w7>>1;

  restOctet[12] = svar17 | svar18;

  svar19 = (sysInfo->fddDesc[index].w7) & (1);
  svar20 = svar19<<7;
  svar21 = sysInfo->fddDesc[index].w8;

  restOctet[13] = svar20 | svar21;

  svar22 = sysInfo->fddDesc[index].w9<<1;
  svar23 = sysInfo->fddDesc[index].w10>>7;

  restOctet[14] = svar22 | svar23;

  svar24 = (sysInfo->fddDesc[index].w10) & (63);
  svar25 = svar24<<2;
  svar26 = sysInfo->fddDesc[index].w11>>5;

  restOctet[15] = svar25 | svar26;

  svar27= (sysInfo->fddDesc[index].w11) & (31);
  svar28 = svar27<<3;
  svar29 = sysInfo->fddDesc[index].w12>>4;

  restOctet[16] = svar28 | svar29;

  svar30 = (sysInfo->fddDesc[index].w12) & (15);
  svar31 = svar30<<4;
  svar32 = sysInfo->fddDesc[index].w13>>3;

  restOctet[17] = svar31 | svar32;

  svar33 = (sysInfo->fddDesc[index].w13) & (7);
  svar34 = svar33<<5;
  svar35 = sysInfo->fddDesc[index].w14>>2;

  restOctet[18] = svar34 | svar35;

  svar36 = (sysInfo->fddDesc[index].w14) & (3);
  svar37 = svar36<<6;

  
  restOctet[19] = svar37 ;*/


  /* Encoding of fields present after FDD CELL INFORMATION PARAMTERS */

  bitsUsedTillCellInfo = 63+bitCount+4; //( 3 bits for 001 fixed for optional and mandatory)
  noOfBytes = bitsUsedTillCellInfo/8;
  noOfBits = 8-(bitsUsedTillCellInfo%8);
  loop = noOfBytes;
  fillByte = loop;

  LOG_PRINT(DEBUG," Bytes= %d Bits= %d Loop =%d ",noOfBytes,noOfBits,loop);

  if( measInfo->miIndex == 0)
  {
    switch(noOfBits)
    {
      /*
      case 8:
        {
          LOG_PRINT(DEBUG," 1st restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar1 = 0<<2;
          rvar2 = 0<<1;
          rvar3 = 1;
          restOctet[loop-1] = restOctet[loop-1] | rvar1 | rvar2 | rvar3; 
          LOG_PRINT(DEBUG," 2nd restOctet[loop-1]=  %d",restOctet[loop-1]);
          tvar16 = measInfo->qSearch_I<<4;
          tvar17 = measInfo->qSearch_C_Initial<<3;
          tvar18 = 1<<2;
          tvar19 = measInfo->fdd_Qoffset>>2;
          restOctet[loop] = tvar16 | tvar17 | tvar18 | tvar19;
          LOG_PRINT(DEBUG," restOctet[loop]=  %d",restOctet[loop]);
          tvar20 = measInfo->fdd_Qoffset & 3;
          tvar21 = tvar20<<6;
          tvar22 = measInfo->fdd_Rep_Quant<<5;
          tvar23 = measInfo->fdd_Multirat_Report<<3;
          tvar24 = measInfo->fdd_Qmin;
          restOctet[loop+1] = tvar21 | tvar22 | tvar23 | tvar24 ;
          LOG_PRINT(DEBUG," restOctet[loop+1]=  %d",restOctet[loop+1]);
          tvar24 = 0<<7;
          tvar25 = 0<<6;
          tvar26 = 1<<5;
          tvar27 = measInfo->fdd_Qmin_Offset<<2;
          tvar28 = measInfo->fdd_Rscpmin>>2;
          restOctet[loop+2] = tvar24 | tvar25 |tvar26 | tvar27 | tvar28;
          LOG_PRINT(DEBUG," restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar29 = measInfo->fdd_Rscpmin & 3;
          tvar30 = measInfo->fdd_Rscpmin<<6;
          restOctet[loop+3] = tvar30;
          LOG_PRINT(DEBUG," restOctet[loop+3]=  %d",restOctet[loop+3]);
          fillByte = loop+4;
        }
        break;
      
      
      
      
      case 1:
        {
          rvar1 = 0<<3;
          rvar2 = 0<<2;
          rvar3 = 1<<1;
          tvar15 = sysInfo->qSearch_I>>3;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 ;
          tvar16 = sysInfo->qSearch_I & 7;
          tvar17 = tvar16<<5;
          tvar18 = sysInfo->qSearch_C_Initial<<4;
          tvar19 = 1<<3;
          tvar20 = sysInfo->fdd_Qoffset>>1;
          restOctet[loop+1] = tvar17 | tvar18 | tvar19 | tvar20 ;
          tvar21 = sysInfo->fdd_Qoffset & 7;
          tvar22 = tvar21<<5;
          tvar23 = sysInfo->fdd_Rep_Quant<<4;
          tvar24 = sysInfo->fdd_Multirat_Report<<2; 
          tvar25 = sysInfo->fdd_Qmin<<1;
          restOctet[loop+2] = tvar21 | tvar22 | tvar23 | tvar24 | tvar25 ;
          tvar26 = sysInfo->fdd_Qmin & 3;
          tvar27 = tvar26<<6;
          tvar28 = 0<<5;
          tvar29 = 0<<4;
          tvar30 = 1<<3;
          tvar31 = sysInfo->fdd_Qmin_Offset;
          restOctet[loop+3] = tvar27 | tvar28 | tvar29 | tvar30 | tvar31;
          tvar32  = sysInfo->fdd_Rscpmin<<4;
          restOctet[loop+4] = tvar32;
          fillByte = loop+5;

        }
        break;




      case 2:
        {
          rvar1 = 0<<4;
          rvar2 = 0<<3;
          rvar3 = 1<<2;
          tvar15 = sysInfo->qSearch_I>>2;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 ;
          tvar16 = sysInfo->qSearch_I & 3;
          tvar17 = tvar16<<6;
          tvar18 = sysInfo->qSearch_C_Initial<<5;
          tvar19 = 1<<4;
          tvar20 = sysInfo->fdd_Qoffset;
          restOctet[loop+1] = tvar17 | tvar18 | tvar19 | tvar20 ;
          tvar21 = sysInfo->fdd_Rep_Quant<<7;
          tvar22 = sysInfo->fdd_Multirat_Report<<5; ;
          tvar23 = sysInfo->fdd_Qmin<<2;
          tvar24 = 0<<1;
          tvar25 = 0;
          restOctet[loop+2] = tvar21 | tvar22 | tvar23 | tvar24 | tvar25 ;
          tvar26 = 1<<7;
          tvar27 = sysInfo->fdd_Qmin_Offset<<4;
          tvar28  = sysInfo->fdd_Rscpmin;
          restOctet[loop+3] = tvar26 | tvar27 | tvar28;
          fillByte = loop+4;

        }
        break;


      case 3:
        {
          rvar1 = 0<<5;
          rvar2 = 0<<4;
          rvar3 = 1<<3;
          tvar15 = sysInfo->qSearch_I>>1;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 ;
          tvar16 = sysInfo->qSearch_I & 1;
          tvar17 = tvar16<<7;
          tvar18 = sysInfo->qSearch_C_Initial<<6;
          tvar19 = 1<<5;
          tvar20 = sysInfo->fdd_Qoffset<<1;
          tvar21 = sysInfo->fdd_Rep_Quant;
          restOctet[loop+1] = tvar17 | tvar18 | tvar19 | tvar20 | tvar21;
          tvar22 = sysInfo->fdd_Multirat_Report<<6; ;
          tvar23 = sysInfo->fdd_Qmin<<3;
          tvar24 = 0<<2;
          tvar25 = 0<<1;
          tvar26 = 1;
          restOctet[loop+2] = tvar22 | tvar23 | tvar24 | tvar25 | tvar26 ;
          tvar28 = sysInfo->fdd_Qmin_Offset<<5;
          tvar29  = sysInfo->fdd_Rscpmin<<1;
          restOctet[loop+3] = tvar28 | tvar29;
          fillByte = loop+4;

        }
        break;
*/

      case 3:
        {
          rvar1 = 0<<6;
          rvar2 = 0<<5;
          rvar3 = 0<<4;
          rvar4 = 1<<3;
          tvar15 = 7;//qseachp
          restOctet[loop-1] = restOctet[loop-1] | rvar1 | rvar2 | rvar3 | rvar4 |(tvar15 >>1) ;
          /*tvar16 = 1<<7;
          tvar17 = 1<<6;
          tvar18 = 1<<5;
          tvar18 = sysInfo->fdd_Qoffset<<2;
          tvar19 = sysInfo->fdd_Rep_Quant<<1;
          tvar20 = sysInfo->fdd_Multirat_Report>>1;*/
          //restOctet[loop] =236;
          restOctet[loop] =0xF6;
/*          tvar21 = sysInfo->fdd_Multirat_Report & 1;
          tvar22 = tvar21<<7;
          tvar23 = sysInfo->fdd_Qmin<<4;
          tvar24 = 0<<3;
          tvar25 = 0<<2;
          tvar26 = 1<<1;
          tvar27 = sysInfo->fdd_Qmin_Offset>>2;*/
          restOctet[loop+1] = 0;
          restOctet[loop+2] = 0x2B;
/*          tvar28 = sysInfo->fdd_Qmin_Offset & (3);
          tvar29 = tvar28<<6;
          tvar30  = sysInfo->fdd_Rscpmin<<2;
          restOctet[loop+3] = tvar29 | tvar30;*/
          fillByte = loop+3;

        }
        break;
/*

      case 5:
        {
          rvar1 = 0<<7;
          rvar2 = 0<<6;
          rvar3 = 1<<5;
          tvar15 = sysInfo->qSearch_I<<1;
          tvar16 = sysInfo->qSearch_C_Initial;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          tvar17 = 1<<7;
          tvar18 = sysInfo->fdd_Qoffset<<3;
          tvar19 = sysInfo->fdd_Rep_Quant<<2;
          tvar20 = sysInfo->fdd_Multirat_Report;
          restOctet[loop+1] = tvar17 | tvar18 | tvar19 | tvar20;
          tvar21 = sysInfo->fdd_Qmin<<5;
          tvar22 = 0<<4;
          tvar23 = 0<<3;
          tvar24 = 1<<2;
          tvar25 = sysInfo->fdd_Qmin_Offset>>1;
          restOctet[loop+2] = tvar21 | tvar22 | tvar23 | tvar24 | tvar25;
          tvar26 = sysInfo->fdd_Qmin_Offset & (1);
          tvar27 = tvar26<<7;
          tvar28  = sysInfo->fdd_Rscpmin<<3;
          restOctet[loop+3] = tvar27 | tvar28;
          fillByte = loop+4;
        }
        break;

      case 6:
        {
          LOG_PRINT(DEBUG,"1st restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar1 = 0;
          restOctet[loop-1] = restOctet[loop-1]| rvar1 ;
          LOG_PRINT(DEBUG," 2nd restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar2 = 0<<7;
          rvar3 = 1<<6;
          tvar15 = sysInfo->qSearch_I<<2;
          tvar16 = sysInfo->qSearch_C_Initial<<1;
          tvar17 = 1;
          restOctet[loop] = rvar2 | rvar3 | tvar15 | tvar16 | tvar17;
          LOG_PRINT(DEBUG,"  restOctet[loop]=  %d",restOctet[loop]);
          tvar18 = sysInfo->fdd_Qoffset<<4;
          tvar19 = sysInfo->fdd_Rep_Quant<<3;
          tvar20 = sysInfo->fdd_Multirat_Report<<1;
          tvar21 = sysInfo->fdd_Qmin>>2;
          restOctet[loop+1] = tvar18 | tvar19 | tvar20 | tvar21;
          LOG_PRINT(DEBUG,"  restOctet[loop+1]=  %d",restOctet[loop+1]);
          tvar22 = sysInfo->fdd_Qmin & 3;
          tvar23 = tvar22<<6;
          tvar24 = 0<<5;
          tvar25 = 1<<4;
          restOctet[loop+2] = tvar23 | tvar24 | tvar25 | 14 ;
          LOG_PRINT(DEBUG,"  restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar26 = 1<<7;
          tvar27 = 0<<6;
          tvar28 = 0<<5;
          tvar29 = 0<<4;
          tvar30 = 0<<3;
//          tvar31 = 1<<2;
          tvar31 = 0<<2;
          tvar32 = 1<<1;
//          tvar33 = sysInfo->fdd_Qmin_Offset>>2;
          restOctet[loop+3] = tvar26 | tvar27 | tvar28 | tvar29 | tvar30 | tvar31 | tvar32 | 1;
          LOG_PRINT(DEBUG," 1st restOctet[loop+3]=  %d",restOctet[loop+3]);
//          tvar34 = sysInfo->fdd_Qmin_Offset & 3;
//          tvar35 = tvar34<<6;
//          tvar36 = sysInfo->fdd_Rscpmin<<2;
//          restOctet[loop+4] = tvar35 | tvar36 | 3;
//          LOG_PRINT(DEBUG," 1st restOctet[loop+4]=  %d",restOctet[loop+4]);

           
          //tvar25 = 0<<4;
          tvar26 = 1<<3;
          tvar27 = sysInfo->fdd_Qmin_Offset;
          restOctet[loop+2] = tvar23 | tvar24 | tvar25 | tvar26 | tvar26 | tvar27;
          LOG_PRINT(DEBUG,"  restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar28 = sysInfo->fdd_Rscpmin<<4 ;
          restOctet[loop+3] = tvar28;
          LOG_PRINT(DEBUG," 1st restOctet[loop+3]=  %d",restOctet[loop+3]);
          fillByte = loop+4;
        }
    
        break;


      case 7:
        {
          LOG_PRINT(DEBUG,"1st restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar1 = 0<<1;
          rvar2 = 0;
          restOctet[loop-1] = restOctet[loop-1]| rvar1 | rvar2 ;
          LOG_PRINT(DEBUG," 2nd restOctet[loop-1]=  %d",restOctet[loop-1]);
          rvar3 = 1<<7;
          tvar15 = sysInfo->qSearch_I<<3;
          tvar16 = sysInfo->qSearch_C_Initial<<2;
          tvar17 = 1<<1;
          tvar18 = sysInfo->fdd_Qoffset>>3;
          restOctet[loop] = rvar3 | tvar15 | tvar16 | tvar17 | tvar18;
          LOG_PRINT(DEBUG,"  restOctet[loop]=  %d",restOctet[loop]);
          tvar19 = sysInfo->fdd_Qoffset & 7;
          tvar20 = tvar19<<5;
          tvar21 = sysInfo->fdd_Rep_Quant<<4;
          tvar22 = sysInfo->fdd_Multirat_Report<<2;
          tvar23 = sysInfo->fdd_Qmin>>1;
          restOctet[loop+1] = tvar20 | tvar21 | tvar22 | tvar23;
          LOG_PRINT(DEBUG,"  restOctet[loop+1]=  %d",restOctet[loop+1]);
          tvar22 = sysInfo->fdd_Qmin & 1;
          tvar23 = tvar22<<7;
          tvar24 = 0<<6;
          tvar25 = 0<<5;
          tvar26 = 1<<4;
          Testing Code
             tvar27 = 1<<3;
          tvar28 = sysInfo->fdd_Qmin_Offset;
          restOctet[loop+2] = tvar23 | tvar24 | tvar25 | tvar26 | tvar26 | tvar27 | tvar28;
          LOG_PRINT(DEBUG,"  restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar29 = sysInfo->fdd_Rscpmin<<4;
          restOctet[loop+3] = tvar29;
          LOG_PRINT(DEBUG," 1st restOctet[loop+3]=  %d",restOctet[loop+3]);
          fillByte = loop+4;
          tvar27 = sysInfo->fdd_Qmin_Offset<<1;
          tvar28 = sysInfo->fdd_Rscpmin>>1;
          restOctet[loop+2] = tvar23 | tvar24 | tvar25 | tvar26 | tvar26 | tvar27 | tvar28;
          LOG_PRINT(DEBUG,"  restOctet[loop+2]=  %d",restOctet[loop+2]);
          tvar29 = sysInfo->fdd_Rscpmin & 7 ;
          tvar30 = sysInfo->fdd_Rscpmin<<5;
          restOctet[loop+3] = tvar30;
          LOG_PRINT(DEBUG," 1st restOctet[loop+3]=  %d",restOctet[loop+3]);
          fillByte = loop+4;


        }
        break;
        */

      default:
        break;

    }
  }    
#if 0
  else if( measInfo->miIndex != 0)
  {
    switch(noOfBits)
    {
      case 8:
        {
          rvar1 = 0<<2;
          rvar2 = 0<<1;
          rvar3 = 0;
          restOctet[loop-1] = restOctet[loop-1] | rvar1 | rvar2 | rvar3; 
          tvar16 = 0<<7;
          tvar17 = 0<<6;
          restOctet[loop] = tvar16 | tvar17 ;
          fillByte = loop+1;
        }
        break;
      
      
      
      
      case 1:
        {
          rvar1 = 0<<3;
          rvar2 = 0<<2;
          rvar3 = 0<<1;
          tvar15 = 0;          
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15; 
          tvar16 = 0<<7;
          restOctet[loop+1] = tvar16 ;
          fillByte = loop+2;
        }
        break;




      case 2:
        {
          rvar1 = 0<<4;
          rvar2 = 0<<3;
          rvar3 = 0<<2;
          tvar15 = 0<<1;
          tvar16 = 0;          
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;


      case 3:
        {
          rvar1 = 0<<5;
          rvar2 = 0<<4;
          rvar3 = 0<<3;
          tvar15 = 0<<2;          
          tvar16 = 0<<1;
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;


      case 4:
        {
          rvar1 = 0<<6;
          rvar2 = 0<<5;
          rvar3 = 0<<4;
          tvar15 = 0<<3;          
          tvar16 = 0<<2;          
          restOctet[loop] = restOctet[loop] | rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;


      case 5:
        {
          rvar1 = 0<<7;
          rvar2 = 0<<6;
          rvar3 = 0<<5;
          tvar15 = 0<<4;
          tvar16 = 0<<3;
          restOctet[loop] = rvar1 | rvar2 | rvar3 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;

      case 6:
        {
          rvar1 = 0;
          restOctet[loop-1] =  restOctet[loop-1] |rvar1 ;
          rvar3 = 0<<7;
          rvar4 = 0<<6;
          tvar15 = 0<<5;
          tvar16 = 0<<4;
          restOctet[loop] =  rvar3 | rvar4 | tvar15 | tvar16 ;
          fillByte = loop+1;
        }
        break;


      case 7:
        {
          rvar1 = 0;
          rvar2 = 0<<1;
          restOctet[loop-1] = restOctet[loop-1] | rvar1 | rvar2 ;
          rvar4 = 0<<7;
          tvar15 = 0<<6;
          tvar16 = 0<<5;
          restOctet[loop] =  rvar4 | tvar15 | tvar16;
          fillByte = loop+1;
        }
        break;

      default:
        break;

    }
  }
#endif

  LOG_PRINT(DEBUG," fillByte=  %d",fillByte);
  if(fillByte<18)
  {
    for(i=fillByte;i<18;i++)
    {
      restOctet[i] = SI_SPARE;
    }
  } 


  msInfoIndex++;


  /*l2PseudoLength = 1;
  l2PseudoLength = l2PseudoLength << 2 | 1;
  *len = *len + 23;*/
   *len = *len + 19; 
  memcpy(buff+1, restOctet, 20);

  return 0;

}
#else
/*
typedef struct
{
  I_U8 protocolDiscriminator;
  I_U8 messageType;
  I_U8 shortL2Header;

 // SI 2quat Rest Octects
  I_U8 baInd;
  I_U8 baInd3g;
  I_U8 mpChangeMark;
  I_U8 miIndex;
  I_U8 miCount;
  I_U8 pwrc;
  I_U8 report_type;
  I_U8 reporting_rate;
  I_U8 invalidBsic;

 //  3G Measurement Parameters Description 
  I_U8 qSearch_I;
  I_U8 qSearch_C;
  I_U8 fdd_Qoffset;
  I_U8 fdd_Rep_Quant;
  I_U8 fdd_Multirat_Report;
  I_U8 fdd_Qmin;

  // UTRAN FDD Description 
  FddDesc fddDesc[18];
} MeasInfo;

typedef struct
{
 //UTRAN FDD Desvription
  I_U16 fddArfcn;
  I_U8 fddIndices0;
  I_U8 noOfFddCells;
  I_U16 w1;
  I_U16 w2;
  I_U16 w3;
  I_U8 w4;
  I_U8 w5;
  I_U8 w6;
  I_U8 w7;
  I_U8 w8;
  I_U8 w9;
  I_U8 w10;
  I_U8 w11;
  I_U8 w12;
  I_U8 w13;
  I_U8 w14;
  I_U8 w15;
  I_U8 w16;
} FddDesc;  

*/

I_S32 EncodeMeasInfo( MeasInfo *measInfo, I_U8 *buff, I_U16 *len,I_U8 index,I_U8 zeroPresent)
{
  BufEncInfo t;
  BufEncInfo *b = &t;
  I_U8 noOfCells = 0;
  I_U8 k=0;

  I_U8 PBIT[17] = {0,10,19,28,36,44,52,60,67,74,81,88,95,102,109,116,122};
  I_U8 PBIT_r[17] = {10, 9, 9, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6 };
  
  b->buf = buff;
  b->octPos = 0;
  b->bitPos = 0;

  STUFFVAL(b, 1, measInfo->protocolDiscriminator);
  STUFFVAL(b, 5, measInfo->messageType);
  STUFFVAL(b, 2, measInfo->shortL2Header);
  
  STUFFVAL(b, 1, measInfo->baInd);
  STUFFVAL(b, 1, measInfo->baInd3g);
  STUFFVAL(b, 1, measInfo->mpChangeMark);

  measInfo->miIndex = msInfoIndex;
  STUFFVAL(b, 4, measInfo->miIndex);

  STUFFVAL(b, 4, measInfo->miCount - 1);
  STUFFVAL(b, 1, measInfo->pwrc);
  STUFFVAL(b, 1, measInfo->report_type);
  STUFFVAL(b, 1, measInfo->reporting_rate);
  STUFFVAL(b, 1, measInfo->invalidBsic);


  STUFF0(b); // For Real Time Difference Description (not Present)
  STUFF0(b); // For BSIC description (not Present)
  STUFF0(b); // For REPORT PRIORITY Description (not Present)
  STUFF0(b); // For MEASUREMENT Parameters Description ( not Present)
  STUFF0(b); // For extension Length (not Present)

  STUFF1(b); // For 3G Neighbour Cell Description

  STUFF0(b); // 3G_Wait 

  if(measInfo->miIndex == 0)
  {
    //STUFF0(b);  // Index_Start_3G (not present)
    STUFF1(b);  // Index_Start_3G (present)
    STUFFVAL(b, 7, measInfo->miIndex*8);
  }
  else if(measInfo->miIndex!=0) 
  { 
    STUFF1(b);  // Index_Start_3G (present)
    STUFFVAL(b, 7, measInfo->indexStart3G);
  }

  STUFF0(b);  // Absolute_Index_Start_EMR

  STUFF1(b);  // UTRAN FDD Description

  STUFF0(b); // Bandwidth_FDD
  STUFF1(b); // Repeated UTRAN FDD Neighbour Cells

  STUFF0(b);
  STUFFVAL(b, 14, measInfo->fddDesc[index].fddArfcn);

  STUFFVAL(b, 1, measInfo->fddDesc[index].fddIndices0);

  if(measInfo->fddDesc[index].noOfFddCells>8)
    noOfCells = 8;
  else if((measInfo->fddDesc[index].noOfFddCells==8) && (zeroPresent == I_TRUE))
    noOfCells = 7;
  else if(measInfo->fddDesc[index].noOfFddCells==8)
    noOfCells = 8;
  else
    noOfCells = measInfo->fddDesc[index].noOfFddCells;
  
    LOG_PRINT(DEBUG, "measInfo->indexStart3G =  %d  measInfo->fddDesc[j].noOfFddCells = %d",measInfo->indexStart3G ,noOfCells);
  LOG_PRINT(DEBUG," No Of Cells =  %d",noOfCells);

  STUFFVAL(b, 5, noOfCells);

  for(k=0;k<noOfCells;k++)
  {
    STUFFVAL(b, PBIT_r[ k], measInfo->fddDesc[index].w[k]);
    LOG_PRINT(DEBUG," w[%d] =  %d",k, measInfo->fddDesc[index].w[k+ measInfo->miIndex*8]);
  }

  //Lets encode only one scrambling code for now.
  //STUFFVAL(b, 10, measInfo->fddDesc[index].w1);

  STUFF0(b); // For ending Repeated UTRAN FDD Neighbour Cells 
  STUFF0(b); // For UTRAN TDD Description 
  STUFF0(b); // For Cdma2000 Description.

  STUFF1(b); // For 3G MEASUREMENT Parameters Description

  LOG_PRINT(DEBUG,"qSearch_C=%d, fdd_Rep_Quant=%d, fdd_Multirat_Report=%d, fdd_Qoffset=%d, fdd_Qmin=%d",
              measInfo->qSearch_C, measInfo->fdd_Rep_Quant, measInfo->fdd_Multirat_Report, measInfo->fdd_Qoffset, measInfo->fdd_Qmin);


  /*values from vodafone*/
  //measInfo->qSearch_C = 7;
  //measInfo->fdd_Rep_Quant =1;
  //measInfo->fdd_Multirat_Report =1;
  
  STUFFVAL(b, 4, measInfo->qSearch_C);
  STUFFVAL(b, 1, measInfo->wcdmaSearchPrio);// For 3G Search PRIO
  STUFFVAL(b, 1, measInfo->fdd_Rep_Quant);
  STUFF1(b);
  STUFFVAL(b, 2, measInfo->fdd_Multirat_Report);
  //STUFF1(b); // For FDD Multirat parameters
  //STUFFVAL(b,3, measInfo->fdd_Qoffset); // Lets fill FDD_REPORTING_OFFSET as zero
 // STUFFVAL(b,3, measInfo->fdd_Qmin); // Lets not fill FDD_REPORTING_THRESHOLD as zero
  STUFF0(b); //For FDD Multirat parameters not present

  STUFF0(b); //For TDD measurement description (not present)
  STUFF0(b); 
  STUFF0(b); //For cdma2000 measurement description(not present)
  STUFF0(b); 
  if(msInfoIndex == (measInfo->miCount - 1)){
    // Following code is to STUFF 'H' for adding additional 3g parameters
    if( b->bitPos == 0 ||
        b->bitPos == 1 ||
        b->bitPos == 3 ||
        b->bitPos == 5 )
    {
      STUFF1(b);
    }
    else
    {
      STUFF0(b);
    }
    STUFF1(b);
    STUFF1(b);
    STUFFVAL(b,6, measInfo->fdd_reporting_Threashold_2); // Lets not fill FDD_REPORTING_THRESHOLD_2 as zero
    //STUFFVAL(b,6, 11); // Lets not fill FDD_REPORTING_THRESHOLD_2 as zero
  }
  else{
    // Following code is to STUFF 'L' for adding additional 3g parameters
    if( b->bitPos == 0 ||
        b->bitPos == 1 ||
        b->bitPos == 3 ||
        b->bitPos == 5 )
    {
      STUFF0(b);
    }
    else
    {
      STUFF1(b);
    }
  } 
    
  fillPadding(b, 19);
  *len = *len + 19;

  msInfoIndex++;
  return 0;

}
#endif
/****************************************************************************************************
                                         Added by Aricent
****************************************************************************************************/
/***********************************************************************************
*  Function Name   : findmod
*  Args            : 1. val
*                    2. range
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will the mod of the input value
*                    with respect to input range
***********************************************************************************/
I_S32 findmod( int val, int range)
{
   I_S32 p=0;
   if(val < 0)
   {
      p= (val + range);
      return p;
   }
   else
   {
      p = (val % range);
      return p;
   }
}


/***********************************************************************************
*  Function Name   : power 
*  Args            : 1. base 
*                    2. pow 
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will the result of base^pow for base >=0
*                    pow >= 0   
***********************************************************************************/
I_S32 power(I_S32 base,I_S32 pow)
{
   I_S32 result=1;
   I_S32 count;
   if(base == 0 || pow < 0)
      return 0 ;
   if(pow == 0)
      return 1 ;

   for(count=0 ; count < pow ; count++)
   {
      result = result * base ;
   }
   return result ;
}

/***********************************************************************************
*  Function Name   : gt_pow_2 
*  Args            : 1. index 
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will find the greatest power of 2 less  
*                    than or equal to index 
***********************************************************************************/
I_S32 gt_pow_2(int index)
{
   I_S32 n=0;
   I_S32 no=2;
   while( (power(no,n))<= index)
   {
      n++;
   }
   return (I_S32) (power(no, n-1));
}


/***********************************************************************************
*  Function Name   : Encode_san 
*  Args            : 1.index 
*                    2.set of Arfcns
*                    3.length of set array
*                    4.range 
*                    
*
*  Returns         : SUCCESS or  FAILURE and an array of encoded Arfcns
*
*  Task            : This method will encode the input set of Arfcns   
*                     according to the bitmap format specified(i.e.range) 
***********************************************************************************/

I_S32 Encode_san(I_S32 index, I_S32 *set, I_S32 len, I_S32 range, I_S32 *nW)
{
   I_S32 i=0, j=0, nElem=0, pvotIndex=0;
   I_S32 subSet_left[len];
   I_S32 subSetInd_left=0;
   I_S32 orgVal_left=0;
   I_S32 index_left=0;

   I_S32 subSet_right[len];
   I_S32 subSetInd_right=0;
   I_S32 orgVal_right=0;
   I_S32 index_right=0;
   I_S32 errCode = 1;

   memset(subSet_left,0, sizeof(subSet_left));
   memset(subSet_right,0, sizeof(subSet_right));
   if (len <= 0)
   {
      return errCode;
   }
   else if (len == 1)
   {
      nW[index -1] = set[0] + 1;
      return errCode;
   }
   /* calculate pivot index */
   for (i = 0; i < len ; i++)
   {
      nElem = 0;
      for (j = 0; j < len; j++)
      {
         if( findmod( (set[j] - set[i]), range) <= (range-1)/2 )
            nElem++;
      }
      if ( (nElem-1) == (len -1)/2 )
      {
         pvotIndex = i;
         nW[index -1] =  set[pvotIndex] + 1 ;
         break;
      }
   }
   index_left=index;
   index_right=index;
   /* left subset */
   orgVal_left = findmod( (set[pvotIndex] + (range-1)/2 + 1),range);
   subSetInd_left=0;
   for (i =0; i < len; i++)
   {
      if ( findmod( (set[i] - orgVal_left),range ) < range/2 )
      {
         subSet_left[subSetInd_left] = findmod( (set[i] - orgVal_left),range);
         subSetInd_left++;
      }
   }
   index_left=index_left+ gt_pow_2(index);
   Encode_san( index_left, subSet_left, subSetInd_left, range/2, nW);

   /* right subset */

   orgVal_right = findmod( (set[pvotIndex] + 1),range);
   subSetInd_right=0;
   for (i =0; i < len; i++)
   {
      if ( findmod( (set[i] - orgVal_right),range ) < range/2 )
      {
         subSet_right[subSetInd_right] = findmod( (set[i] - orgVal_right),range);
         subSetInd_right++;
      }
   }
   index_right=index_right+ 2*gt_pow_2(index);
   Encode_san( index_right, subSet_right, subSetInd_right, (range-1)/2, nW);
}


/* Added By ARICENT For On The Fly Changes */
/*******************************************************************************
*  Function Name   : updateSysInformation1
*
*  Args            : 1. cell id  
*                    2. lac 
*                    3. buff
*                    4. bufLen
*                    5. ieInd
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will update the SystemInfo1  
*******************************************************************************/
I_S32 updateSysInformation1(I_U32 cellId, I_U32 lac, I_U8 *buff, I_U16 bufLen, I_U8 ieInd)
{
   I_U8  tvar = 0;
   I_S32 errCode = 1;
   I_U32 cellBarStatus = 0;
   I_U32 oprStateAInterface = 0;

   /* Check Length Of Encoded Buffer */
   if ( bufLen != 23 || buff == NULL )
   {
      LOG_PRINT(CRITICAL, "Wrong Buffer Size To Be Updated For SI1: err=%s",clib_strerror(errCode));
      return errCode;
   }

   switch ( ieInd )
   {
   case CELL_BAR_ACCESS: 
      /* Get A Interface Operational State */
      errCode = getAInterfaceOprState(&oprStateAInterface);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from AInterface Table for SI1:err=%s",clib_strerror(errCode));
         return errCode;
      }
 
      /* Get "cellBarAccess" From Cell Table */
      errCode = cellHGetCellBarred(cellId, lac, &cellBarStatus);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI1:err=%s",clib_strerror(errCode));
         return errCode;
      } 
  
      if ( cellBarStatus == I_FALSE && oprStateAInterface == ENABLED )
      {
         /* To Disable cellBarStatus Bit*/
         tvar = 0;
      }
      else
      {
         /* To Enable  cellBarStatus Bit */
         tvar = 2;
      }
      buff[19] = buff[19] & 253;
      buff[19] = buff[19] | tvar;

      LOG_PRINT(DEBUG,"Printing Updated System Information 1 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      break;

   default:
      LOG_PRINT(DEBUG,"Wrong IE Provided To Update System Information 1");
      errCode = 1;	
      return errCode; 
   }
   return errCode;
}

/*******************************************************************************
*  Function Name   : updateSysInformation2
*
*  Args            : 1. cell id  
*                    2. lac 
*                    3. buff
*                    4. bufLen
*                    5. ieInd
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will update the SystemInfo2  
*******************************************************************************/
I_S32 updateSysInformation2(I_U32 cellId, I_U32 lac, I_U8 * buff, I_U16 bufLen, I_U8 ieInd)
{
   I_U8  tvar = 0;
   I_S32 errCode = 1;
   I_U32 cellBarStatus = 0;
   I_U32 oprStateAInterface = 0;

   /* Check Length Of Encoded Buffer */
   if ( bufLen != 23 || buff == NULL )
   {
      LOG_PRINT(CRITICAL, "Wrong Buffer Size To Be Updated For SI1: err=%s",clib_strerror(errCode));
      return errCode;
   }

   switch ( ieInd )
   {
   case CELL_BAR_ACCESS:
      /* Get A Interface Operational State */
      errCode = getAInterfaceOprState(&oprStateAInterface);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from AInterface Table for SI1:err=%s",clib_strerror(errCode));
         return errCode;
      }
 
      /* Get "cellBarAccess" From Cell Table */
      errCode = cellHGetCellBarred(cellId, lac, &cellBarStatus);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI 2:err=%s",clib_strerror(errCode));
         return errCode;
      }

      if ( cellBarStatus == I_FALSE && oprStateAInterface == ENABLED )
      {
         /* To Disable cellBarStatus Bit*/
         tvar = 0;
      }
      else
      {
         /* To Enable  cellBarStatus Bit */
         tvar = 2;
      }
      buff[20] = buff[20] & 253;
      buff[20] = buff[20] | tvar;

      LOG_PRINT(DEBUG,"Printing Updated System Information 2 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      break;

   default:
      LOG_PRINT(DEBUG,"Wrong IE Provided To Update System Information 2");
      errCode = 1;
      return errCode;
   }

   return errCode;
}

/*******************************************************************************
*  Function Name   : updateSysInformation3
*
*  Args            : 1. cell id  
*                    2. lac 
*                    3. buff
*                    4. bufLen
*                    5. ieInd
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will update the SystemInfo3  
*******************************************************************************/
I_S32 updateSysInformation3(I_U32 cellId, I_U32 lac, I_U8 * buff , I_U16 bufLen, I_U8 ieInd, I_U8 si2quaterPosition)
{
   I_U8  tvar = 0;
   I_U8  tvar1 = 0;
   I_U8  tvar2 = 0;
   I_U8  tvar3 = 0;
   I_U8  tvar4 = 0;
   I_U8  raColour;
   I_U8  si13Position;
   I_U32 outRows = 0;
   I_U16 outSize = 0;  
   I_S32 errCode = 1;
   I_U32 cellBarStatus = 0;
   I_U32 oprStateAInterface = 0;
   //I_U8  si2quaterPosition= 0;
   PsCellTableIndices   psCellTableInData;
   PsCellTableApi       *psCellTableOutData = NULL;
   SiPreconfigTableApi  *siPreconfigTableOutData = NULL;
   /* Check Length Of Encoded Buffer */
   if ( bufLen != 23 || buff == NULL )
   {
      LOG_PRINT(CRITICAL, "Wrong Buffer Size To Be Updated For SI3: err=%s",clib_strerror(errCode));
      return errCode;
   }

   switch ( ieInd )
   {
   case SI_2TER_IND_NOT_PRESENT:

      LOG_PRINT(DEBUG,"Sysinfo2terIndication Not Present");
      /* To Disable Sysinfo2terIndication Bit*/
      buff[21] = buff[21] & 239;   
      buff[21] = buff[21] | 0;
      LOG_PRINT(DEBUG,"Printing Updated System Information 3 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      errCode = 0;
      break;

   case SI_2TER_IND_PRESENT: 

      LOG_PRINT(DEBUG,"Sysinfo2terIndication Present");
      /* To Enable Sysinfo2terIndication Bit*/
      buff[21] = buff[21] & 239;   
      buff[21] = buff[21] | 16;
      LOG_PRINT(DEBUG,"Printing Updated System Information 3 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      errCode = 0;
      break;

   case CELL_BAR_ACCESS:
      /* Get A Interface Operational State */
      errCode = getAInterfaceOprState(&oprStateAInterface);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from AInterface Table for SI1:err=%s",clib_strerror(errCode));
         return errCode;
      }
 
      /* Get "cellBarAccess" From Cell Table */
      errCode = cellHGetCellBarred(cellId, lac, &cellBarStatus);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI 3:err=%s",clib_strerror(errCode));
         return errCode;
      }

      if ( cellBarStatus == I_FALSE && oprStateAInterface == ENABLED )
      {
         /* To Disable cellBarStatus Bit*/
         tvar = 0;
      }
      else
      {
         /* To Enable  cellBarStatus Bit */
         tvar = 2;
      } 
      buff[16] = buff[16] & 253;
      buff[16] = buff[16] | tvar;
      LOG_PRINT(DEBUG,"Printing Updated System Information 3 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      break;

      /* Changes for PCU R2.5 : Starts*/
   case GPRS_PRESENT: 

      LOG_PRINT(DEBUG,"GPRS Present");
      /* To Enable gprsIndicator Bit*/
      psCellTableInData.cellId = cellId;
      psCellTableInData.lac = lac;
      errCode = getPsCellTable(&psCellTableInData, &psCellTableOutData);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL,"Retrieval failed from PS Cell Table for SI3: err = %s", clib_strerror(errCode));
         return errCode;
      }	   
      raColour = psCellTableOutData->raColour;
      raColour = raColour & 7;/* mask upper 5 bits */
      LOG_PRINT(DEBUG,"RA_COLOUR        = %d",raColour);

      errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
      if ((errCode != CLIB_SUCCESS)||(outRows < 1))
      {
          LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI3: err = %s", clib_strerror(errCode));
          free(psCellTableOutData);
          return errCode;
      } 
      si13Position = siPreconfigTableOutData->si13Position;
      si13Position = si13Position & 1;/* mask upper 7 bits */
      LOG_PRINT(DEBUG,"SI13Position     = %d",si13Position);
      //si2quaterPosition= siPreconfigTableOutData->si2QuaterIndicator;
      LOG_PRINT(DEBUG,"si2quaterPosition     = %d",si2quaterPosition);
      tvar=raColour>>2;
      tvar= tvar & 1;/* mask all upper 7 bits */
      buff[21]=buff[21] & 252;
      buff[21]=buff[21] | tvar;
      
      tvar1 = raColour<<6 | si13Position<<5;
      if(siPreconfigTableOutData->g3EarlyCmSendingRestriction != 0)
         tvar2 = 16;
      else
         tvar2 = 0;
      
      
      if(si2quaterPosition!= 0)
        tvar3 = 3 ;
      else
         tvar3 = 11; /* padding spare bits as 2B*/
      tvar4 = tvar1|tvar2|tvar3;
      buff[22]= tvar4;

      free(psCellTableOutData);
      free(siPreconfigTableOutData);
      
      LOG_PRINT(DEBUG,"Printing Updated System Information 3 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      break;
   
   case GPRS_NOT_PRESENT: 

      LOG_PRINT(DEBUG,"GPRS Not Present");
      /* To Disable gprsIndicator Bit*/
      SiPreconfigTableApi  *siPreconfigTableOutData = NULL;
      errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
      if ((errCode != CLIB_SUCCESS)||(outRows < 1))
      {
          LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI3: err = %s", clib_strerror(errCode));
          return errCode;
      } 
      /* 7th bit encoded as 1 to mark GPRS_IND not present */
      if (siPreconfigTableOutData->g3EarlyCmSendingRestriction !=0)
         tvar = 2;
      else
         tvar = 3;
      buff[21]=buff[21] & 252;
      buff[21]=buff[21] | tvar;
      
      si2quaterPosition= siPreconfigTableOutData->si2QuaterIndicator;
      
      if(si2quaterPosition != 0)
         tvar1 = 171 | si2quaterPosition<<6;
      else
         tvar1 = SI_SPARE; /* spare padding as 2B */
      
      buff[22]= tvar1;

      free(siPreconfigTableOutData);
      LOG_PRINT(DEBUG,"Printing Updated System Information 3 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      break;

      /* Changes for PCU R2.5 : End*/
   default:
      LOG_PRINT(DEBUG,"Wrong IE Provided To Update System Information 3");
      errCode = 1;
      return errCode;
   }

   return errCode;
}

/*******************************************************************************
*  Function Name   : updateSysInformation4
*
*  Args            : 1. cell id  
*                    2. lac 
*                    3. buff
*                    4. bufLen
*                    5. ieInd
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will update the SystemInfo4  
*******************************************************************************/
I_S32 updateSysInformation4(I_U32 cellId, I_U32 lac, I_U8 * buff, I_U16 bufLen, I_U8 ieInd, I_U8 isCbchActive)
{
   I_U8  tvar = 0;
   I_U8  raColour;
   I_U8  si13Position;
   I_U32 outRows = 0;
   I_U16 outSize = 0;  
   I_S32 errCode = 1;
   I_U32 cellBarStatus = 0;
   I_U32 oprStateAInterface = 0;
   PsCellTableIndices   psCellTableInData;
   PsCellTableApi       *psCellTableOutData = NULL;
   SiPreconfigTableApi  *siPreconfigTableOutData = NULL;

   /* Check Length Of Encoded Buffer */
   if ( bufLen != 23 || buff == NULL )
   {
      LOG_PRINT(CRITICAL, "Wrong Buffer Size To Be Updated For SI4: err=%s",clib_strerror(errCode));
      return errCode;
   }

   switch ( ieInd )
   {
   case CELL_BAR_ACCESS:
      /* Get A Interface Operational State */
      errCode = getAInterfaceOprState(&oprStateAInterface);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from AInterface Table for SI4 err=%s",clib_strerror(errCode));
         return errCode;
      }
 
      /* Get "cellBarAccess" From Cell Table */
      errCode = cellHGetCellBarred(cellId, lac, &cellBarStatus);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL, "Retrieval failed from Cell Table for SI 4:err=%s",clib_strerror(errCode));
         return errCode;
      }

      if ( cellBarStatus == I_FALSE && oprStateAInterface == ENABLED )
      {
         /* To Disable cellBarStatus Bit*/
         tvar = 0;
      }
      else
      {
         /* To Enable  cellBarStatus Bit */
         tvar = 2;
      }
      buff[10] = buff[10] & 253;
      buff[10] = buff[10] | tvar;

      LOG_PRINT(DEBUG,"Printing Updated System Information 4 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen)
      break;

      /* Changes for PCU R2.5 : Starts*/
   case GPRS_PRESENT: 
      LOG_PRINT(DEBUG,"GPRS Present");
      /* To Enable gprsIndicator Bit*/
      psCellTableInData.cellId = cellId;
      psCellTableInData.lac = lac;
      errCode = getPsCellTable(&psCellTableInData, &psCellTableOutData);
      if (errCode != CLIB_SUCCESS)
      {
         LOG_PRINT(CRITICAL,"Retrieval failed from PS Cell Table for SI4: err = %s", clib_strerror(errCode));
         return errCode;
      }	   
      raColour = psCellTableOutData->raColour;
      raColour = raColour & 7;/* mask upper 5 bits*/
      LOG_PRINT(DEBUG,"RA_COLOUR        = %d",raColour);

      errCode = getallSiPreconfigTable(&siPreconfigTableOutData , &outRows , &outSize);
      if ((errCode != CLIB_SUCCESS)||(outRows < 1))
      {
          LOG_PRINT(CRITICAL, "Retrieval failed from SI Preconfig Table for SI4: err = %s", clib_strerror(errCode));
          free(psCellTableOutData);
          return errCode;
      } 
      si13Position = siPreconfigTableOutData->si13Position;
      si13Position = si13Position & 1; /* mask upper 7 bits */
      LOG_PRINT(DEBUG,"SI13Position     = %d",si13Position);
      
      if(I_TRUE == isCbchActive){
         buff[19]=buff[19] & 224;
         buff[19]=buff[19] | 16 | raColour<<1 | si13Position;
      }else {
         buff[15]=buff[15] & 224;
         buff[15]=buff[15] | 16 | raColour<<1 | si13Position;
      }    
      free(psCellTableOutData);
      free(siPreconfigTableOutData);
      
      LOG_PRINT(DEBUG,"Printing Updated System Information 4 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      break;
   
   case GPRS_NOT_PRESENT: 

      LOG_PRINT(DEBUG,"GPRS Not present");
      /* To Disable gprsIndicator Bit*/
      if(I_TRUE == isCbchActive){
         buff[19]=buff[19] & 224;
         buff[19]=buff[19] | 11;
      }else {
         buff[15]=buff[15] & 224;
         buff[15]=buff[15] | 11;
      }    
      errCode= CLIB_SUCCESS;
      LOG_PRINT(DEBUG,"Printing Updated System Information 4 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      break;

      /* Changes for PCU R2.5 : End*/
   default:
      LOG_PRINT(DEBUG,"Wrong IE Provided To Update System Information 4");
      errCode = 1;
      return errCode;
   }

   return errCode;
}
      /* Changes for PCU R2.5 : Starts*/
/*******************************************************************************
*  Function Name   : updateSysInformation13
*
*  Args            : 1. cell id  
*                    2. lac 
*                    3. buff
*                    4. bufLen
*                    5. ieInd
*
*  Returns         : SUCCESS or  FAILURE.
*
*  Task            : This method will update the SystemInfo13  
*******************************************************************************/
I_S32 updateSysInformation13(I_U32 cellId, I_U32 lac, I_U8 * buff, I_U16 bufLen, I_U8 ieInd)
{
   I_U8  tvar1 = 0;
   I_S32 errCode = 1;
   
   /* Check Length Of Encoded Buffer */
   if ( bufLen != 23 || buff == NULL )
   {
      LOG_PRINT(CRITICAL, "Wrong Buffer Size To Be Updated For SI13: err=%s",clib_strerror(errCode));
      return errCode;
   }

   switch ( ieInd )
   {
   case N_CELL_CHANGE:
      tvar1 = buff[3] & 112;
      tvar1 = tvar1 >> 4;
      tvar1 = (tvar1 + 1) % 8;
      buff[3] = 128 | (tvar1 << 4) | 2;

      errCode = updateBccHChgMarkAndSiChgField(cellId,lac,tvar1,TWO);
      if(CLIB_SUCCESS != errCode)
      {
          LOG_PRINT(CRITICAL,"Error in updateBccHChgMarkAndSiChgField() DB API");
          return errCode;
      }

      LOG_PRINT(DEBUG,"BcchChangeMark=%u",tvar1);
      LOG_PRINT(DEBUG,"Printing Updated System Information 13 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      break;

   case GPRS_NOT_PRESENT:
      buff[3] = buff[3] & 128;

      errCode = updateBccHChgMarkAndSiChgField(cellId,lac,ZERO,ZERO);
      if(CLIB_SUCCESS != errCode)
      {
          LOG_PRINT(CRITICAL,"Error in updateBccHChgMarkAndSiChgField() DB API");
          return errCode;
      }
      LOG_PRINT(DEBUG,"Printing Updated System Information 13 message buffer");
      PRINT_HEX_DUMP(DEBUG, buff, bufLen);
      break;

   default:
      LOG_PRINT(DEBUG,"Wrong IE Provided To Update System Information 13");
      errCode = 1;
      return errCode;
   }

   return errCode;
}
      /* Changes for PCU R2.5 : End*/
 
 /* End of Added by Aricent */
/*
SysInfoEncoder::~SysInfoEncoder()
{
} */
