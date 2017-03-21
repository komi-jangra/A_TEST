/***********************************File Header ***************************
       File Name        : oam_sysinfo_encoder.h
       Purpose          : header file to declare the methods,
                          structures used for system information message encoding
       Project          : IMR OAM - BSC
       Subsystem        : bsc
       Author           : Aricent 
       CSCI ID          :
       Version          :
************************************* End **********************************/


#ifndef SYSINFOENCODER_HPP_
#define SYSINFOENCODER_HPP_

/*#include <sysxxx_typedef.h>
#include "sysinfodefs.h" */



typedef struct
{
        I_U8 protocolDiscriminator;
        I_U8 skipIndicator;
        I_U8 messageType;

        /*I_U8 cellChannelDescription;*/
        I_U8 formatIndicator[22];
        I_U8 ARFCN[124];    /* bitmap 0 format */
        I_U8 f0;

        I_U16 origARFCN;
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
        I_U8 w17;
        I_U8 w18;
        I_U8 w19;
        I_U8 w20;
        I_U8 w21;
        I_U8 w22;
        I_U8 w23;
        I_U8 w24;
        I_U8 w25;
        I_U8 w26;
        I_U8 w27;
        I_U8 w28;

        I_S16 f1;
        I_S16 f2;
        I_S16 f3;
        I_S16 f4;
        I_S16 f5;
        I_S16 f6;
        I_S16 f7;
        I_S16 f8;
        I_S16 f9;
        I_S16 f10;
        I_S16 f11;
        I_S16 f12;
        I_S16 f13;
        I_S16 f14;
        I_S16 f15;
        I_S16 f16;
        I_S16 f17;
        I_S16 f18;
        I_S16 f19;
        I_S16 f20;
        I_S16 f21;
        I_S16 f22;
        I_S16 f23;
        I_S16 f24;
        I_S16 f25;
        I_S16 f26;
        I_S16 f27;
        I_S16 f28;

        /*I_U8 rachDescription[2];*/
         I_U8 re;
         I_U8 cellBarAccess;
         I_U8 txInteger;
         I_U8 maxRetans;
         /*byte 2-3 */
         I_U8 ec;
         I_U8 acClass[16];
        /*Rest Octet */
         I_U8 NCHPosition;
         I_U8 BandIndicator;  
         I_U8 NCH;

} SystemInfo1;

typedef struct
{
        I_U8 protocolDiscriminator;
        I_U8 skipIndicator;
        I_U8 messageType;

        /*I_U8 cellChannelDescription;*/
        I_U8 formatIndicator[22];
        I_U8 ba_ind;
        I_U8 ext_ind;
        I_U8 ARFCN[124];    /* bitmap 0 format */
        I_U8 f0;

        I_U16 origARFCN;
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
        I_U8 w17;
        I_U8 w18;
        I_U8 w19;
        I_U8 w20;
        I_U8 w21;
        I_U8 w22;
        I_U8 w23;
        I_U8 w24;
        I_U8 w25;
        I_U8 w26;
        I_U8 w27;
        I_U8 w28;

        I_S16 f1;
        I_S16 f2;
        I_S16 f3;
        I_S16 f4;
        I_S16 f5;
        I_S16 f6;
        I_S16 f7;
        I_S16 f8;
        I_S16 f9;
        I_S16 f10;
        I_S16 f11;
        I_S16 f12;
        I_S16 f13;
        I_S16 f14;
        I_S16 f15;
        I_S16 f16;
        I_S16 f17;
        I_S16 f18;
        I_S16 f19;
        I_S16 f20;
        I_S16 f21;
        I_S16 f22;
        I_S16 f23;
        I_S16 f24;
        I_S16 f25;
        I_S16 f26;
        I_S16 f27;
        I_S16 f28;


        /*NCC description*/
        I_U8 NCC[8];

        /*I_U8 rachDescription[2];*/
         I_U8 re;
         I_U8 cellBarAccess;
         I_U8 txInteger;
         I_U8 maxRetans;
         /*byte 2-3 */
         I_U8 ec;
         I_U8 acClass[16];

} SystemInfo2;

typedef struct
{
   I_U8 protocolDiscriminator;
   I_U8 skipIndicator;
   I_U8 messageType;

   /*I_U8 cellChannelDescription;*/
   I_U8 formatIndicator[22];
   I_U8 baInd;
   I_U8 multibandReporting;
   I_U8 ARFCN[124];    /* bitmap 0 format */
   I_U8 f0;

   I_U16 origARFCN;
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
   I_U8 w17;
/*Temp added for E-GSM PERWEZ 8-02-2017*/
   I_S16 f1;
   I_S16 f2;
   I_S16 f3;
   I_S16 f4;
   I_S16 f5;
   I_S16 f6;
   I_S16 f7;
   I_S16 f8;
   I_S16 f9;
   I_S16 f10;
   I_S16 f11;
   I_S16 f12;
   I_S16 f13;
   I_S16 f14;
   I_S16 f15;
   I_S16 f16;
   I_S16 f17;
   I_S16 f18;
   I_S16 f19;
   I_S16 f20;
   I_S16 f21;
   I_S16 f22;
   I_S16 f23;
   I_S16 f24;
   I_S16 f25;
   I_S16 f26;
   I_S16 f27;
   I_S16 f28;
/*Temp added for E-GSM 8-02-217*/
   /* Rest octects for 2ter are coded as L*/

} SystemInfo2ter;

typedef struct
{
        I_U8 protocolDiscriminator;
        I_U8 skipIndicator;
        I_U8 messageType;
        I_U32  cellIdentity;

        /*I_U8 locationAreaIdentity[4];*/
        I_U16  mobileCC; /* Changed from I_U32 to I_U16*/
        I_U16  mobileNC; /*Changed from I_U32 to I_U16 */
          
        /*byte 3 */
        I_U32 locationAreaCode;


        /*I_U8 controlChannelDescription[2];*/

        I_U8 ccch_conf;
        I_U8 bs_ag_blks_res;
        I_U8 att;
        I_U8 mscr;
        /*byte2 */
        I_U8 bs_pa_mfrms;
        I_U8 cbq3;
        /* byte3  */
        I_U8 timer3212value;


       /*I_U8 cellOptions */
        I_U8 radio_link_timeout;
        I_U8 dtx;
        I_U8 pwrc;
        I_U8 dn_ind;

        /*I_U8 cellSelectionParameters[1] ;*/
        I_U8 ms_txpwr_max_cch;
        I_U8 cell_reselect_hystersis;
        /*byte 2  */
        I_U8 rxlev_access_min;
        I_U8 neci;
        I_U8 acs;

        /*I_U8 rachDescription[2];*/
         I_U8 re;
         I_U8 cellBarAccess;
         I_U8 txInteger;
         I_U8 maxRetans;
         /*byte 2-3 */
         I_U8 ec;
         I_U8 acClass[16];

        /*Rest Octet */
         I_U8 OptionalSelectionParameters;
         I_U8 CBQ;  
         I_U8 CELL_RESELECT_OFFSET;
         I_U8 TEMPORARY_OFFSET; 
         I_U8 PENALTY_TIME; 
         I_U8 PowerOffsetSelection;
         I_U8 PowerOffset;
         I_U8 Sysinfo2terIndication;
         I_U8 EarlyClassmarkSendingControl;
         I_U8 SchedulingIfWhereOption;
         I_U8 SchedulingIfWhere;
         I_U8 GPRSIndicator;
         I_U8 RA_COLOUR;
         I_U8 SI13Position;
         I_U8 G3EarlyCMSendingRestriction;
         I_U8 SI2quaterPosition;


} SystemInfo3;

typedef struct
{
        I_U8 protocolDiscriminator;
        I_U8 skipIndicator;
        I_U8 messageType;
        I_U32  cellIdentity;         
       
        /*locationAreaIdentity[4];*/
        I_U16  mobileCC; /* Changed from I_U32 to I_U16*/
        I_U16  mobileNC; /* Changed from I_U32 to I_U16 */
      
        I_U32 locationAreaCode;

        /*I_U8 cellSelectionParameters[1] ;*/
        I_U8 ms_txpwr_max_cch;
        I_U8 cell_reselect_hystersis;
        /*byte 2  */
        I_U8 rxlev_access_min;
        I_U8 neci;
        I_U8 acs;

        /*I_U8 rachDescription[2];*/
         I_U8 re;
         I_U8 cellBarAccess;
         I_U8 txInteger;
         I_U8 maxRetans;
         /*byte 2-3 */
         I_U8 ec;
         I_U8 acClass[16];
         
        /* CBCH Channel Description*/
         /*firstByte*/
          I_U8 cbchChannelDesIe;
        /*second  byte */
         I_U8  channelType;
         I_U8  timeslotNumber;
         /*third and fourth byte*/
         I_U8 tsc;
	 I_U8 hoppingChannel;
         I_U16 cbchArfcn;

       /*Rest Octet */
         I_U8 OptionalSelectionParameters;
         I_U8 CBQ;
         I_U8 CELL_RESELECT_OFFSET;
         I_U8 TEMPORARY_OFFSET;
         I_U8 PENALTY_TIME;
         I_U8 PowerOffsetSelection;
         I_U8 PowerOffset;
         I_U8 GPRSIndicator;
         I_U8 RA_COLOUR;
         I_U8 SI13Position;
         I_U8 BreakIndicator;
         I_U8 PRIO_THR;
         I_U8 LSA_OFFSET;
         I_U8 MCC;
         I_U8 MNC;
         I_U8 CellIdentity;
         I_U8 LSA_ID;
         I_U8 Short_LSA_ID;
         I_U8 CBQ3;
         I_U8 SI13altPosition;
         
} SystemInfo4;

typedef struct
{
        I_U8 protocolDiscriminator;
        I_U8 skipIndicator;
        I_U8 messageType;

        /*I_U8 cellChannelDescription;*/
        I_U8 formatIndicator[22];
        I_U8 ba_ind;
        I_U8 ext_ind;
        I_U8 ARFCN[124];    /* bitmap 0 format */
        I_U8 f0;

        I_U16 origARFCN;
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
        I_U8 w17;
        I_U8 w18;
        I_U8 w19;
        I_U8 w20;
        I_U8 w21;
        I_U8 w22;
        I_U8 w23;
        I_U8 w24;
        I_U8 w25;
        I_U8 w26;
        I_U8 w27;
        I_U8 w28;

        I_S16 f1;
        I_S16 f2;
        I_S16 f3;
        I_S16 f4;
        I_S16 f5;
        I_S16 f6;
        I_S16 f7;
        I_S16 f8;
        I_S16 f9;
        I_S16 f10;
        I_S16 f11;
        I_S16 f12;
        I_S16 f13;
        I_S16 f14;
        I_S16 f15;
        I_S16 f16;
        I_S16 f17;
        I_S16 f18;
        I_S16 f19;
        I_S16 f20;
        I_S16 f21;
        I_S16 f22;
        I_S16 f23;
        I_S16 f24;
        I_S16 f25;
        I_S16 f26;
        I_S16 f27;
        I_S16 f28;
} SystemInfo5;

typedef struct
{
   I_U8 protocolDiscriminator;
   I_U8 skipIndicator;
   I_U8 messageType;

   /*I_U8 cellChannelDescription;*/
   I_U8 formatIndicator[22];
   I_U8 baInd;
   I_U8 multibandReporting;
   I_U8 ARFCN[124];    /* bitmap 0 format */
   I_U8 f0;

   I_U16 origARFCN;
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
   I_U8 w17;
/*Temp added for E-GSM PERWEZ 8-02-2017*/
   I_S16 f1;
   I_S16 f2;
   I_S16 f3;
   I_S16 f4;
   I_S16 f5;
   I_S16 f6;
   I_S16 f7;
   I_S16 f8;
   I_S16 f9;
   I_S16 f10;
   I_S16 f11;
   I_S16 f12;
   I_S16 f13;
   I_S16 f14;
   I_S16 f15;
   I_S16 f16;
   I_S16 f17;
   I_S16 f18;
   I_S16 f19;
   I_S16 f20;
   I_S16 f21;
   I_S16 f22;
   I_S16 f23;
   I_S16 f24;
   I_S16 f25;
   I_S16 f26;
   I_S16 f27;
   I_S16 f28;
/*Temp added for E-GSM 8-02-217*/
} SystemInfo5ter;

typedef struct
{
        I_U8 protocolDiscriminator;
        I_U8 skipIndicator;
        I_U8 messageType;
        I_U32  cellIdentity;

        /*I_U8 locationAreaIdentity[4];*/
        I_U16  mobileCC; /* Changed from I_U32 to I_U16 */
        I_U16  mobileNC; /* Changed from I_U32 to I_U16 */
        /*byte 3 */
        I_U32 locationAreaCode;

        /*I_U8 cellOptions SACCH */
        I_U8 radio_link_timeout;
        I_U8 dtx;
        I_U8 pwrc;
	I_U8 dnInd;/* added by Aricent*/
        /*NCC description*/
        I_U8 NCC[8];
        /*Rest Octet */
        I_U8 NLN;
	I_U8 vbsVgcsOptions;/*added by Aricent */
        I_U8 DTM_Support;
        I_U8 RAC;
		I_U8 MAX_LAPDm;
		I_U8 Band_Indicator;
		I_U8 GPRS_MS_TXPWR_MAX_CCCH;

} SystemInfo6;

typedef struct
{
   I_U8 protocolDiscriminator;
   I_U8 skipIndicator;
   I_U8 messageType;
   /* SI13 Rest Octet */
   I_U8 bcchChangeMark;
   I_U8 siChangeField;
   I_U8 si13ChangeMark;
   /* GPRS Mobile Allocation*/
   I_U8 gprsMobileAllocation;
   I_U8 hsn;
   I_U8 rflNoList;
   I_U8 maLength;
   I_U32 maBitmap;
   /* ARFCN index list needs to be included */

   I_U8 rac;
   I_U8 spgcCcchSup;
   I_U8 priorityAccessThr;
   I_U8 networkControlOrder;
        
   /* GPRS Cell Options */
   I_U8 nmo;
   I_U8 t3168;
   I_U8 t3192;
   I_U8 drxTimerMax;
   I_U8 accessBurstType;
   I_U8 controlAckType;
   I_U8 bsCvMax;
   I_U8 panDec;
   I_U8 panInc;
   I_U8 panMax;

   /* Extension Information */
   I_U8 egprsPacketChannelRequest;
   I_U8 bepPeriod;
   I_U8 pfcFeatureMode;
   I_U8 dtmSupport;
   I_U8 ccnActive;
   I_U8 nwExtUtbf;
   I_U8 bssPagingCoordination;


   /* GPRS Power Control Parameter */
   I_U8 alpha;
   I_U8 tAvgW;
   I_U8 tAvgT;
   I_U8 pcMeasChan;
   I_U8 nAvgI;

   I_U8 psi1RepeatPeriod;
   /* PBCCH Description */
   I_U8 pb;
   I_U8 tsc;
   I_U8 tn;
   I_U8 maio;
   I_U8 sgsnr;
   I_U8 siStatusInd;
   I_U16 arfcn;
} SystemInfo13;

typedef struct
{
 /*UTRAN FDD Desvription*/
  I_U16 fddArfcn;
  I_U8 fddIndices0;
  I_U8 noOfFddCells;
  I_U16 w[16];
} FddDesc;  

/* 2G - 3G Handover */
typedef struct
{
  I_U8 protocolDiscriminator;
  I_U8 skipIndicator;
  I_U8 messageType;

  /*SI 2quat Rest Octects*/
  I_U8 baInd;
  I_U8 baInd3g;
  I_U8 mpChangeMark;
  I_U8 si2QuatIndex;
  I_U8 si2QuatCount;
  I_U8 indexStart3G;  

  /* 3G Measurement Parameters Description */
  I_U8 qSearch_I;
  I_U8 qSearch_C_Initial;
  I_U8 fdd_Qoffset;
  I_U8 fdd_Rep_Quant;
  I_U8 fdd_Multirat_Report;
  I_U8 fdd_Qmin;

  /* 3G Additional Measurement Parameters Description */
  I_U8 fdd_Qmin_Offset;
  I_U8 fdd_Rscpmin;
  I_U8 wcdmaSearchPrio;
  I_U8 fdd_reporting_Threashold_2;
  
  /* UTRAN FDD Description */
  FddDesc fddDesc[18];
} SystemInfo2quat;


typedef struct
{
  I_U8 protocolDiscriminator;
  I_U8 messageType;
  I_U8 shortL2Header;

  /*SI 2quat Rest Octects*/
  I_U8 baInd;
  I_U8 baInd3g;
  I_U8 mpChangeMark;
  I_U8 miIndex;
  I_U8 miCount;
  I_U8 indexStart3G;  
  I_U8 pwrc;
  I_U8 report_type;
  I_U8 reporting_rate;
  I_U8 invalidBsic;

  /* 3G Measurement Parameters Description */
  I_U8 qSearch_I;
  I_U8 qSearch_C;
  I_U8 fdd_Qoffset;
  I_U8 fdd_Rep_Quant;
  I_U8 fdd_Multirat_Report;
  I_U8 fdd_Qmin;
  I_U8 wcdmaSearchPrio;
  //3G ADDITIONAL MEASUREMENT Parameters Description 2 struct
  I_U8 fdd_reporting_Threashold_2;
  /* UTRAN FDD Description */
  FddDesc fddDesc[18];
} MeasInfo;

    I_S32 PrepareSysInformation1(I_U32 cellId, 
			     I_U32 lac,
			     I_U32 bscId,
                             I_U8 * buff,
                             I_U16 * bufLen);
    I_S32 PrepareSysInformation2(I_U32 cellId, 
			     I_U32 lac, 
			     I_U32 bscId,
                             I_U8 * buff,
                             I_U16 * bufLen,
                             I_U16 arfcn[],
                             I_U32 setLen, 
			     I_U8  baInd );
    I_S32 PrepareSysInformation2ter(I_U32 cellId , 
				I_U32 lac,
                                I_U8 * buff,
                                I_U16 * bufLen,
                                I_U16 arfcn[],
                                I_U32 setLen,
                                I_U8  baInd );

    I_S32 PrepareSysInformation3(I_U8 sysInfo2terInd,I_U8 sysInfo2quatInd,
                              I_U32 cellId, I_U32 lac, I_U32 bscId,
                              I_U8 ccchConf, I_U8 * buff , I_U16 * bufLen);

    I_S32 PrepareSysInformation4(I_U32 cellId, 
			     I_U32 lac, 
			     I_U32 bscId,
                             I_U8 * buff,
                             I_U16 * bufLen);
   I_S32 PrepareSysInformation4_Cbsh(I_U32 cellId,
                             I_U32 lac,
                             I_U32 bscId,
                             I_U8 * buff,
                             I_U16 * bufLen);
    I_S32 PrepareSysInformation5(I_U32 cellId, 
			     I_U32 lac,
                             I_U8 * buff,
                             I_U16 * bufLen,
                             I_U16 arfcn[],
                             I_U32 setLen,
                             I_U8  baInd );
    I_S32 PrepareSysInformation5ter(I_U32 cellId , 
				I_U32 lac,
                                I_U8 * buff,
                                I_U16 * bufLen,
                                I_U16 arfcn[],
                                I_U32 setLen,
                                I_U8  baInd );
    I_S32 PrepareSysInformation6(I_U32 cellId, 
			     I_U32 lac, 
			     I_U32 bscId,
                             I_U8 * buff,
                             I_U16 * bufLen);
    I_S32 PrepareSysInformation13(I_U32 cellId, 
			      I_U32 lac, 
			      I_U32 bscId,
                              I_U8 * buff,
                              I_U16 * bufLen,
                              I_U8 pbcchPres,
                              I_U8 tsc, I_U8 tn, I_U16 arfcn, I_U8 egprsPresent);

    I_S32 PrepareSysInformation2quat(I_U32 cellId , I_U32 lac,
            I_U8 * buff , I_U16 * bufLen,
            I_U16 arfcn[], I_U32 setLen,I_U16 fddInfo[][16], I_U8 innerLength[],
            I_U8 baInd , I_U8 baInd3g);

    I_S32 PrepareMeasInfo(I_U32 cellId , I_U32 lac,
            I_U8 * buff , I_U16 * bufLen,
            I_U16 arfcn[], I_U32 setLen,I_U16 fddInfo[][16], I_U8 innerLength[],
            I_U8 baInd , I_U8 baInd3g);
   
    I_S32  EncodeSysInformation1(SystemInfo1 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len);
    I_S32  EncodeSysInformation2(SystemInfo2 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len);
    /* Added by Aricent - SI2ter*/  
    I_S32  EncodeSysInformation2ter(SystemInfo2ter *sysinfo, 
                                   I_U8 *buff, 
                                   I_U16 *len); 
    /* End of Added by Aricent */ 
    I_S32  EncodeSysInformation3(SystemInfo3 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len);
    I_S32  EncodeSysInformation4(SystemInfo4 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len);
    I_S32  EncodeSysInformation5(SystemInfo5 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len);
    /* Added by Aricent - SI5ter*/  
    I_S32  EncodeSysInformation5ter(SystemInfo5ter *sysinfo, 
                                   I_U8 *buff, 
                                   I_U16 *len);
    I_S32  EncodeSysInformation6(SystemInfo6 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len);
   /* Added by Aricent - SI13*/
    I_S32  EncodeSysInformation13(SystemInfo13 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len,
				I_U8 pbcchPres,I_U8 egprsPresent);
   /* End of Added by Aricent */
   
    I_S32 EncodeSysInformation2quat( SystemInfo2quat *sysInfo,
                                     I_U8 *buff, I_U16 *len, 
                                     I_U8 index,I_U8 zeroPresent);

    I_S32 EncodeMeasInfo( MeasInfo *measInfo,
                                     I_U8 *buff, I_U16 *len, 
                                     I_U8 index,I_U8 zeroPresent);

   /* Added By ARICENT For On The Fly Changes */
    I_S32 updateSysInformation1(I_U32 cellId, I_U32 lac, I_U8 *buff, I_U16 bufLen, I_U8 ieInd);
    I_S32 updateSysInformation2(I_U32 cellId, I_U32 lac, I_U8 *buff, I_U16 bufLen, I_U8 ieInd);
 /* I_S32 updateSysInformation3(I_U32 cellId, I_U32 lac, I_U8 *buff, I_U16 bufLen, I_U8 ieInd);  */  
    I_S32 updateSysInformation3(I_U32 cellId, I_U32 lac, I_U8 *buff, I_U16 bufLen, I_U8 ieInd, I_U8 ind2quater);
    I_S32 updateSysInformation4(I_U32 cellId, I_U32 lac, I_U8 * buff, I_U16 bufLen, I_U8 ieInd, I_U8 isCbchActive);
  /*  I_S32 updateSysInformation4(I_U32 cellId, I_U32 lac, I_U8 *buff , I_U16 bufLen, I_U8 ieInd);*/
   /* End of Added by Aricent */

/* commented by Aricent */ 
/*class SysInfoEncoder 
{
public:
    SysInfoEncoder();
   
    */
    /*
   static I_S32  EncodeSysInformation1(SystemInfo1 *sysinfo, 
                                   I_U8 *buff, 
                                   I_U16 *len);
   static I_S32  EncodeSysInformation2(SystemInfo2 *sysinfo, 
                                   I_U8 *buff, 
                                   I_U16 *len);
    *//* Added by Aricent - SI2ter*/ /* 
   static I_S32  EncodeSysInformation2ter(SystemInfo2ter *sysinfo, 
                                   I_U8 *buff, 
                                   I_U16 *len); 
    *//* End of Added by Aricent */ /*
   static I_S32  EncodeSysInformation3(SystemInfo3 *sysinfo, 
                                    I_U8 *buff, 
                                    I_U16 *len);
   static I_S32  EncodeSysInformation4(SystemInfo4 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len);
   static I_S32  EncodeSysInformation5(SystemInfo5 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len);
   static I_S32  EncodeSysInformation6(SystemInfo6 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len);
   *//* Added by Aricent - SI13*//*
   static I_S32  EncodeSysInformation13(SystemInfo13 *sysinfo, 
                                I_U8 *buff, 
                                I_U16 *len,
				I_U8 pbcchPres);
  */ /* End of Added by Aricent */
   /*virtual ~SysInfoEncoder(); 
};*/ 

#endif /*SYSINFOENCODER_HPP_*/
