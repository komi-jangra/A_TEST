/***********************************File Header ***************************
       File Name        : oamscfg_clk_object_handler.h
       Purpose          : This file contains function prototype for CFG
                          Clk Source object Handler  methods.
       Project          : BSC OAM
       Subsystem        : Oams
       Author           : Bikram Bhatt (BB)
       CSCI ID          :
       Version          :
************************************* End **********************************/
#ifndef OAMCFG_CLK_OBJHANDLER_H
#define OAMCFG_CLK_OBJHANDLER_H

#define updMaxClkConfig(maxClkCfg) (gclkSrcCfgData.clkSrcCfg.maxClkConfig = maxClkCfg)
#define updDbIndex(Idx) (gclkSrcCfgData.dbIndex = Idx)
#define readDbIndex() (gclkSrcCfgData.dbIndex)
#define readMaxClkConfig() (gclkSrcCfgData.clkSrcCfg.maxClkConfig )

/*updClkSrcNrslt -> sets the clock source as provided paramter and result to default */
#define updClkSrcNrslt(Idx,frameID,slotID,trunkPId,pri) do {\
          gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].frameId     = frameID;\
          gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].slotId      = slotID;\
          gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].trunkPortId = trunkPId;\
          gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].priority    = pri;\
          gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].result      = CM_SUCCESS;\
        } while (0)

#define readClkSrc(Idx,frameID,slotID,trunkPId,pri) do {\
          frameID  = gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].frameId;\
          slotID   = gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].slotId;\
          trunkPId = gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].trunkPortId;\
          pri      = gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].priority;\
        } while (0)

/*BSC R2.0 Changes Starts*/
#define readClkSrcSts(Idx,frameID,slotID,trunkPId,sts) do {\
          frameID  = gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].frameId;\
          slotID   = gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].slotId;\
          trunkPId = gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].trunkPortId;\
          sts      = APPLIED;\
        } while (0)
/*BSC R2.0 Changes Ends*/

#define readClkSrcTrunkPortIdAtIdx(Idx) (gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].trunkPortId )

#define updClkSrcLvlResult(Idx,rslt) do {\
          gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].result      = rslt;\
        } while (0)

#define readClkSrcLvlResult(Idx) (gclkSrcCfgData.clkSrcCfg.clkSrcPriorityResult[Idx].result)

#define OAM_BPM_CONFIG_FRAMER_RESULT_BASE OAM_BPM_CONFIG_CLOCK_RESULT_BASE 

#define isClkSrcResultNOKFromOil(rslt)  ((rslt) != OPERATION_SUCCESS)

#define isClkSrcResultOK(rslt)  ( CM_SUCCESS == (rslt) )
                                        
#define updClkTopLvlResutl(rslt) (gclkSrcCfgData.clkSrcCfg.result = rslt)

#define isClkSrcProcOngoing()  ((gclkSrcCfgData.enumClkSrcProcState) == (clkSrcCfgOngoing))

#define setClkSrcProcState(ProState) (gclkSrcCfgData.enumClkSrcProcState = ProState)

#define MAX_CFG_CLK_COUNT      5
#define INVALID_CLK_SRC_IDX    0xFF
#define INVALID_CLK_SRC        0x00

#define CLK_SRC_OK_EVENT_STRING  "Clk Config On FrameId[%d],SlotId[%d],PortId [%d] Success"
#define CLK_SRC_NOK_EVENT_STRING  "Clk Config On FrameId[%d],SlotId[%d],PortId [%d] Failed"

/* Function Prototypes */
I_Void setOilClkSrcRespHldr(I_Void);
I_Void setClkSrcTblHdlr(I_Void);
I_Bool sendClockSourceConfigReq();
I_Bool checkClockSourceResp();
I_Void sendClkSourceConfigFailAlarm(I_U8 frameId, I_U8 slotId, I_U16 trunkPortId , I_U32 priority);
I_Bool IsTrunkPortConfiguredAsClkSrc(I_U16 TrunkPortID);
I_Void sendClkSourceAppliedAlarm(I_U8 frameId, I_U8 slotId, I_U16 trunkPortId , I_U32 priority);
I_Void sendClkSourcePendingAlarm(I_U8 frameId, I_U8 slotId, I_U16 trunkPortId , I_U32 priority);

/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS4.0                   BB             Created 

************************************** End *********************************/

#endif /*OAMCFG_CLK_OBJHANDLER_H */
