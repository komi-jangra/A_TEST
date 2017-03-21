/***********************************File Header ***************************
File Name        : oamscfg_clean_transient_table.h
Purpose          : This file contains object states defined for CFG
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef __OAMCFG_CLEANTRANSIENTTABLE_H_
#define __OAMCFG_CLEANTRANSIENTTABLE_H_

#define mkstr(x) #x
#define CALLCLEANDBTABLE(xxxTypeTable) clean##xxxTypeTable()
#define CLEANDBTABLEPROTO(xxxTypeTable) I_Void clean##xxxTypeTable(I_Void)
#define CLEANDBTABLEIMPLEMENTATION(xxxTypeTable) \
I_Void clean##xxxTypeTable (I_Void) \
{                                   \
    xxxTypeTable##Api *outData;     \
    I_U32 outRows;                  \
    I_U32 index;                    \
    I_U16 outSize;                  \
    if ( getall##xxxTypeTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {  \
       for (index=0;index<outRows;index++) {                                      \
          if ( delete##xxxTypeTable( (xxxTypeTable##Indices *)((I_U8 *)outData + (index*outSize)))  \
               != CLIB_SUCCESS) {                                                                   \
            LOG_PRINT(LOG_CRITICAL,"delete DB call Failed for "mkstr(xxxTypeTable));                \
          }                                                                                         \
       }                                                                                            \
       free(outData);                                                                               \
    }                                                                                               \
    LOG_PRINT(LOG_INFO,"Cleanup OK for "mkstr(xxxTypeTable));                                       \
}



CLEANDBTABLEPROTO(TrauOprStsTable);
CLEANDBTABLEPROTO(CellNonPerTable);
CLEANDBTABLEPROTO(E1NonPerTable);
CLEANDBTABLEPROTO(AbisTimeSlotNonPerTable);
CLEANDBTABLEPROTO(SwMNodeTable);
CLEANDBTABLEPROTO(SwMTable);
CLEANDBTABLEPROTO(LinksetStatusTable);
CLEANDBTABLEPROTO(LinkStatusTable);
CLEANDBTABLEPROTO(Ss7RouteStatusTable);
CLEANDBTABLEPROTO(LapdOperationalStatusTable);
CLEANDBTABLEPROTO(SystemTypeTable);
CLEANDBTABLEPROTO(ChasisFrameIdTable);
CLEANDBTABLEPROTO(IccCardInfoTable);
CLEANDBTABLEPROTO(EicCardInfoTable);
CLEANDBTABLEPROTO(DspInfoTable);
CLEANDBTABLEPROTO(SystemClkInfoTable);
CLEANDBTABLEPROTO(CardStateChangeTable);
CLEANDBTABLEPROTO(TrxTsTeiTable);
CLEANDBTABLEPROTO(BicE1TeiMapTable);
CLEANDBTABLEPROTO(SwMOfferTable);
CLEANDBTABLEPROTO(AInterfaceTable);
CLEANDBTABLEPROTO(MlpppChannelStatusTable);
CLEANDBTABLEPROTO(ClkSourceConfigStatusTable);
CLEANDBTABLEPROTO(TrunkPortStatusTable);
CLEANDBTABLEPROTO(DspStatusTable);

CLEANDBTABLEPROTO(PtrxTable);
CLEANDBTABLEPROTO(PowerSupplyInfoTable);
CLEANDBTABLEPROTO(BicStatusTable);
CLEANDBTABLEPROTO(RadioTimeslotTable);
CLEANDBTABLEPROTO(LtrxTable);
CLEANDBTABLEPROTO(DspTrauAbisResourceConfigTable);
CLEANDBTABLEPROTO(DspTrauPcmResourceConfigTable);
CLEANDBTABLEPROTO(DspTrauResourceMapTable);
CLEANDBTABLEPROTO(ChannelParamsTable);
CLEANDBTABLEPROTO(ChannelUsageTable);
CLEANDBTABLEPROTO(TrauChannelUsageTable);
CLEANDBTABLEPROTO(TrxHCreatedChnTable);
CLEANDBTABLEPROTO(E1StatusTable);
CLEANDBTABLEPROTO(CbsStatusTable);
CLEANDBTABLEPROTO(FanTrayInfoTable);
CLEANDBTABLEPROTO(FanInfoTable);
/*Changes PCU R2.5 Aricent -- START*/
CLEANDBTABLEPROTO(PsCellStatusTable);
CLEANDBTABLEPROTO(NsvcStatusTable);
CLEANDBTABLEPROTO(GbIfStatusTable);
CLEANDBTABLEPROTO(FrLinkStatusTable);
CLEANDBTABLEPROTO(FrLinkExtE1TsMccE1TsMapTable);

CLEANDBTABLEPROTO(PsAppCellPmTable);
CLEANDBTABLEPROTO(GbBssGpStackCellPmTable);
CLEANDBTABLEPROTO(GbBssGpStackPmTable);
CLEANDBTABLEPROTO(GbNsStackPmTable);
/*Changes PCU R2.5 Aricent -- END*/
#endif
