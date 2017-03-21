/*****************************************************************************
#  Date :07 Feb 07
#  Owner:Ashutosh Singh
#                     Copy right permission to IMR Pvt Ltd
#                                 2007-08
#
#   This product and related documentation is protected by copyright and
#   distributed under licenses restricting its use, copying, distribution
#   and decompilation.  No part of this product or related documentation
#   may be reproduced in any form by any means without prior written
#   authorization ofIMR Pvt Ltd and its licensors, if any.
#
#
# ...  Devloping started from 07 Feb 07
# ...  Finalized testing on 
#   changes related to             Date                by
#
#     1.
#
#     2.
#
******************************************************************************/


#include <stdio.h>

#include "GTT_Implem.h"
#include "trace.h"
#define MAX_TRAVERSE 10

ITS_OCTET IMRGT_Indicator[MAX_IND]={IMR_GTI_1,IMR_GTI_2,IMR_GTI_3,IMR_GTI_4};

ITS_OCTET IMRGT_OpreationCode[MAX_OPCODE]={0,1,2,3};

/*Patch:Itika:15-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
ITS_OCTET IMRGT_TranslationType[MAX_TT]= {
                                           IMR_TT0,IMR_TT0,IMR_TT0,
                                           IMR_TT0,IMR_TT1,IMR_TT1,
                                           IMR_TT2,IMR_TT2,IMR_TT2,
                                           IMR_TT3,IMR_TT3,IMR_TT17,
                                           IMR_TT17,IMR_TT40,IMR_TT40
                                         };

ITS_OCTET IMRGT_EncodeScheme[MAX_EN_SH]= {
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,
                                           IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_3,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,
                                           IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2
                                        };

ITS_OCTET IMRGT_NumeberingPlan[MAX_NP]=  {
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_7,
                                           IMR_NUMPLAN_7,IMR_NUMPLAN_0,IMR_NUMPLAN_0,
                                           IMR_NUMPLAN_2,IMR_NUMPLAN_2,IMR_NUMPLAN_2,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_1,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6
                                         };

ITS_OCTET IMRGT_NatureAddInd[MAX_NAI]=   {
                                           IMR_NAI_4,IMR_NAI_4,IMR_NAI_4,
                                           IMR_NAI_4,IMR_NAI_4,IMR_NAI_4,
                                           IMR_NAI_4,IMR_NAI_4,IMR_NAI_4,
                                           IMR_NAI_4,IMR_NAI_4,IMR_NAI_4,
                                           IMR_NAI_4,IMR_NAI_4,IMR_NAI_4
                                        };

ITS_OCTET IMRGT_MaxDigits[MAX_MAXD]=    {
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_4,IMR_MAXDIGT_4,
                                          IMR_MAXDIGT_6,IMR_MAXDIGT_6,IMR_MAXDIGT_6,
                                          IMR_MAXDIGT_4,IMR_MAXDIGT_4,IMR_MAXDIGT_4,
                                          IMR_MAXDIGT_4,IMR_MAXDIGT_6,IMR_MAXDIGT_6
                                        };

ITS_OCTET IMRGT_MinDigits[MIN_MAXD]=    {
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5
                                        };

ITS_OCTET IMRGT_SkipDigits[SKIP_DGT]=   {
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT
                                        };

#endif

#ifdef ANSI
ITS_OCTET IMRGT_TranslationType[MAX_TT]= {
                                           IMR_TT1,IMR_TT1,IMR_TT1,IMR_TT1,
                                           IMR_TT2,IMR_TT2,IMR_TT2,IMR_TT2,
                                           IMR_TT3,IMR_TT3,IMR_TT3,IMR_TT3,
                                           IMR_TT4,IMR_TT4,IMR_TT4,IMR_TT4,
                                           IMR_TT5,IMR_TT5,IMR_TT5,IMR_TT5,
                                           IMR_TT6,IMR_TT6,IMR_TT6,IMR_TT6,
                                           IMR_TT7,IMR_TT7,IMR_TT7,IMR_TT7,
                                           IMR_TT8,IMR_TT8,IMR_TT8,IMR_TT8,
                                           IMR_TT9,IMR_TT9,IMR_TT9,IMR_TT9,
                                           IMR_TT10,IMR_TT10,IMR_TT10,IMR_TT10,
                                           IMR_TT11,IMR_TT11,IMR_TT11,IMR_TT11,
                                           IMR_TT12,IMR_TT12,IMR_TT12,IMR_TT12,
                                           IMR_TT13,IMR_TT13,IMR_TT13,IMR_TT13,
                                           IMR_TT14,IMR_TT14,IMR_TT14,IMR_TT14,
                                           IMR_TT15,IMR_TT15,IMR_TT15,IMR_TT15,
                                           IMR_TT16,IMR_TT16,IMR_TT16,IMR_TT16,
                                           IMR_TT17,IMR_TT17,IMR_TT17,IMR_TT17,
                                           IMR_TT28,IMR_TT28,IMR_TT28,IMR_TT28,
                                           IMR_TT29,IMR_TT29,IMR_TT29,IMR_TT29,
                                           IMR_TT30,IMR_TT30,IMR_TT30,IMR_TT30,
                                           IMR_TT31,IMR_TT31,IMR_TT31,IMR_TT31,
                                           IMR_TT251,IMR_TT251,IMR_TT251,IMR_TT251,
                                           IMR_TT253,IMR_TT253,IMR_TT253,IMR_TT253
                                         };


ITS_OCTET IMRGT_EncodeScheme[MAX_EN_SH]= {
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                           IMR_ENCODSCH_1,IMR_ENCODSCH_2,IMR_ENCODSCH_1,IMR_ENCODSCH_2,
                                        };

ITS_OCTET IMRGT_NumeberingPlan[MAX_NP]=  {
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                           IMR_NUMPLAN_1,IMR_NUMPLAN_1,IMR_NUMPLAN_6,IMR_NUMPLAN_6,
                                         };


ITS_OCTET IMRGT_MaxDigits[MAX_MAXD]=    {
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                          IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,IMR_MAXDIGT_8,
                                        };

ITS_OCTET IMRGT_MinDigits[MIN_MAXD]=    {
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                          IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,IMR_MINDIGT_5,
                                        };

ITS_OCTET IMRGT_SkipDigits[SKIP_DGT]=   {
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                          IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,IMR_SKIPDGT,
                                        };
#endif
/*End:Updated for ANSI SCCP-CL*/
extern ISIL_GTT_LIST *gtt_list;

/*****************************************************************************
 *  Purpose:
 *      This function Set the GTT translation rule per translation func .
 *
 *  Input Parameters:
 *      IMR_OCTET gti.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *

*****************************************************************************/
int
IMR_GTT_SetTransRulePerFunc()
{
int i,j,k;
ISIL_initTree();

 for (k=0; k<MAX_GTI ;k++)
 {
   Set_GTI.Gti=IMRGT_Indicator[k];
   switch(IMRGT_Indicator[k])
   {
     case IMR_GTI_1:
/*Patch:Itika:15-june-10:Updated for ANSI SCCP-CL*/
#ifdef ANSI
         for (i=0;i<MAX_TRANSFUNC;i++)
         {
           Set_GTI.TransFunc[i].TransType=IMRGT_TranslationType[i] ;
           Set_GTI.TransFunc[i].Encod_scheme=IMRGT_EncodeScheme[i] ;
           Set_GTI.TransFunc[i].Num_Plan=IMRGT_NumeberingPlan[i] ;

           for (j=0;j<MAX_TRANSRULE;j++)
           {
             Set_GTI.TransFunc[i].TransRule[j].MinDigits=IMRGT_MinDigits[i] ;
             Set_GTI.TransFunc[i].TransRule[j].Oper_code=IMRGT_OpreationCode[j] ;
           }
         }
#endif
/*End:Updated for ANSI SCCP-CL*/

     break ;
     case IMR_GTI_2:
         for (i=0;i<MAX_TRANSFUNC;i++)
         {
           Set_GTI.TransFunc[i].TransType=IMRGT_TranslationType[i] ;
         
           for (j=0;j<MAX_TRANSRULE;j++)
           {
             Set_GTI.TransFunc[i].TransRule[j].MinDigits=IMRGT_MinDigits[i] ;
             Set_GTI.TransFunc[i].TransRule[j].Oper_code=IMRGT_OpreationCode[j] ;
           }
         }
     continue;
     case IMR_GTI_3:
     break;
     case IMR_GTI_4:
/*Patch:Itika:15-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
         Set_GTI.Gti=IMRGT_Indicator[k];
         for (i=0;i<MAX_TRANSFUNC;i++)
         {
           Set_GTI.TransFunc[i].TransType=IMRGT_TranslationType[i] ;
           Set_GTI.TransFunc[i].Encod_scheme=IMRGT_EncodeScheme[i] ;
           Set_GTI.TransFunc[i].Num_Plan=IMRGT_NumeberingPlan[i] ;
           Set_GTI.TransFunc[i].NAI=IMRGT_NatureAddInd[i] ;

           for (j=0;j<MAX_TRANSRULE;j++)
           {
             Set_GTI.TransFunc[i].TransRule[j].MinDigits=IMRGT_MinDigits[i] ;
             Set_GTI.TransFunc[i].TransRule[j].Oper_code=IMRGT_OpreationCode[j] ;
           }
         }
#endif
/*End:Updated for ANSI SCCP-CL*/
   break;

  }/*end of switch*/
 }/*end of for*/
  
}/*end of func SetTransRuleperFunc*/



/*****************************************************************************
 *  Purpose:
 *      This function Get the GTT translation  .
 *
 *  Input Parameters:
 *   IMR_GTT_IN 
 *   IMR_GTT_GTI  
 *
 *  Input/Output Parameters:
 *      IMR_GTT_TransRule
 *
 *  Output Parameters:
 *
 *  Return Value:
 *

*****************************************************************************/
int
IMR_GTT_GetTransFunc(IMR_GTT_IN Gtt_in, IMR_GTT_TransRule *Rule)
{
 int i=0;
 int ret=-1;
  switch(Gtt_in.gti)
   {
     case IMR_GTI_1:
           ISIL_DEBUG_TRACE(("IMR_GTT_GetTransFunc: Case IMR_GTI_1\n"));            
/*Patch:Itika:15-june-10:Updated for ANSI SCCP-CL*/
#ifdef ANSI
        for(i=0 ;i<MAX_TRANSFUNC;i++)
         {

          if (Set_GTI.TransFunc[i].TransType==Gtt_in.TF_in.TransType &&
                Set_GTI.TransFunc[i].Encod_scheme==Gtt_in.TF_in.Encod_scheme &&
                           Set_GTI.TransFunc[i].Num_Plan==Gtt_in.TF_in.Num_Plan) 
           {
           ISIL_DEBUG_TRACE(("IMR_GTT_GetTransFunc: GetTransRule for  i = %d\n",i));            
              IMR_GTT_GetTransRule_ANSI(Set_GTI.TransFunc[i],Rule);
              ret=0;
           }
         }/*end of for loop for trans Fucn*/
#endif
/*End:Updated for ANSI SCCP-CL*/
     break;
     case IMR_GTI_2:
           ISIL_DEBUG_TRACE(("IMR_GTT_GetTransFunc: Case IMR_GTI_2\n"));            
        for(i=0 ;i<MAX_TRANSFUNC;i++)
         {
          if (Set_GTI.TransFunc[i].TransType==Gtt_in.TF_in.TransType )
          {
/*Patch:Itika:15-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
              IMR_GTT_GetTransRule(Set_GTI.TransFunc[i],Rule);
#endif
#ifdef ANSI
              IMR_GTT_GetTransRule_ANSI(Set_GTI.TransFunc[i],Rule);
#endif
/*End:Updated for ANSI SCCP-CL*/
              ret=0;
          }
         }
     break ;
     case IMR_GTI_3:
           ISIL_DEBUG_TRACE(("IMR_GTT_GetTransFunc: Case IMR_GTI_3\n"));            
     break ;
     case IMR_GTI_4:
           ISIL_DEBUG_TRACE(("IMR_GTT_GetTransFunc: Case IMR_GTI_4\n"));            
/*Patch:Itika:15-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
        for(i=0 ;i<MAX_TRANSFUNC;i++)
         {
          if (Set_GTI.TransFunc[i].TransType==Gtt_in.TF_in.TransType &&
                Set_GTI.TransFunc[i].Encod_scheme==Gtt_in.TF_in.Encod_scheme &&
                           Set_GTI.TransFunc[i].Num_Plan==Gtt_in.TF_in.Num_Plan &&
                                          Set_GTI.TransFunc[i].NAI==Gtt_in.TF_in.NAI )
           {
              IMR_GTT_GetTransRule(Set_GTI.TransFunc[i],Rule);
              ret=0;
           }
         }/*end of for loop for trans Fucn*/
#endif
/*End:Updated for ANSI SCCP-CL*/
  break;
   }
 return ret;
}/*end of func GTT_Grt_TransFunc*/


/*Patch:Itika:15-june-10:Updated for ANSI SCCP-CL*/
#ifdef CCITT
/*****************************************************************************
 *  Purpose:
 *      This function Get the GTT translation rule per translation func .
 *
 *  Input Parameters:
 *    IMR_GTT_TransFunc
 *
 *  Input/Output Parameters:
 *    IMR_GTT_TransRule
 *
 *  Output Parameters:
 *
 *  Return Value:
 *

*****************************************************************************/

int
IMR_GTT_GetTransRule(IMR_GTT_TransFunc TransFunc ,
                          IMR_GTT_TransRule *Rule)
{
int i=0;

 switch(TransFunc.TransType)
 { 
  case IMR_TT0 :
  case IMR_TT1 :
  case IMR_TT2 :
  case IMR_TT3 :
  case IMR_TT17 :
  case IMR_TT40 :/*cannot be idendified about SSN*/  
      for ( i=0;i<MAX_TRANSRULE;i++)
       {
        if ((TransFunc.TransRule[i].Oper_code==IMR_GTT_GET_DPC_SSN_TABLE))
        {
           ISIL_DEBUG_TRACE(("GT Searching in DPC_SSN Table\n"));            
           Rule->MinDigits=TransFunc.TransRule[i].MinDigits;
           break;

        }/*end of if*/
    
      }/*end of For translation rule*/ 

  break;
    default:
          ISIL_DEBUG_TRACE(("Translation type unavailable for GT Searching \n"));            
 }

}/*end of func GetTransRule*/
#endif

#ifdef ANSI
/*****************************************************************************
 *  Purpose:
 *      This function Get the GTT translation rule per translation func .
 *
 *  Input Parameters:
 *    IMR_GTT_TransFunc
 *
 *  Input/Output Parameters:
 *    IMR_GTT_TransRule
 *
 *  Output Parameters:
 *
 *  Return Value:
 *

*****************************************************************************/

int
IMR_GTT_GetTransRule_ANSI(IMR_GTT_TransFunc TransFunc ,
                          IMR_GTT_TransRule *Rule)
{
int i=0;
           ISIL_DEBUG_TRACE(("IMR_GTT_GetTransRule_ANSI: TransFunc.TransType :%d\n",TransFunc.TransType));            

 switch(TransFunc.TransType)
 { 
  case IMR_TT1 :
  case IMR_TT2 :
  case IMR_TT3 :
  case IMR_TT4 :
  case IMR_TT5 :
  case IMR_TT6 :
  case IMR_TT7 :
  case IMR_TT8 :
  case IMR_TT9 :
  case IMR_TT10 :
  case IMR_TT11 :
  case IMR_TT12 :
  case IMR_TT13 :
  case IMR_TT14 :
  case IMR_TT15 :
  case IMR_TT16 :
  case IMR_TT17 :
  case IMR_TT28 :  
  case IMR_TT29 :  
  case IMR_TT30 :  
  case IMR_TT31 :  
  case IMR_TT251 :  
  case IMR_TT253 :  
      for ( i=0;i<MAX_TRANSRULE;i++)
       {
        if ((TransFunc.TransRule[i].Oper_code==IMR_GTT_GET_DPC_SSN_TABLE))
        {
           ISIL_DEBUG_TRACE(("GT Searching in DPC_SSN Table\n"));            
           Rule->MinDigits=TransFunc.TransRule[i].MinDigits;
           break;

        }/*end of if*/
    
      }/*end of For translation rule*/ 

  break;
    default:
          ISIL_DEBUG_TRACE(("Translation type unavailable for GT Searching \n"));            
 }

}/*end of func GetTransRule*/

#endif
/*End:Updated for ANSI SCCP-CL*/
 



/*****************************************************************************
 *  Purpose:
 *      This function Get the GTT translation digits form local GT database.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *

*****************************************************************************/
ISIL_DPC_SSN *
//IMR_GTDigts_Translation(ITS_USHORT *dpc,ITS_OCTET *ssn,IMR_GTT_TransRule *Rule,ITS_OCTET *gti_string)
IMR_GTDigts_Translation(IMR_GTT_TransRule *Rule,ITS_OCTET *gti_string)
{
char cnt =0;
ISIL_DPC_SSN *dpc_ssn=NULL;
char lineartraverse=0;
ISIL_GTT_LIST *searchgtt=NULL;
ISIL_GTT_LIST *tmp=NULL;
int ret=-1;
//ISIL_DPC_SSN *dpc_ssn; 

 searchgtt=&gtt_list[gti_string[cnt]];
// ISIL_DEBUG_TRACE(("GTT next Ptr :%x gti_string[%d] %d \n",searchgtt,cnt,gti_string[cnt]));
 cnt++;

  while(searchgtt)
  {
 
//   ISIL_DEBUG_TRACE(("next->next %x for string %d",searchgtt->next[gti_string[cnt]],gti_string[cnt]));

  if(gti_string[cnt] == 0x0A)
  {
   ISIL_DEBUG_TRACE(("IMR_GTDigts_Translation : Value are 0")); 
   if(gti_string[cnt]=='\0'|| searchgtt->next[0]==NULL)
    {
       ISIL_DEBUG_TRACE(("cnt  %d for Mindigits %d",(cnt+1),Rule->MinDigits));

       if((cnt+1) <= Rule->MinDigits)
       {
           ISIL_DEBUG_TRACE(("GTT Entry is not Found\n"));
           break;
       }

      if(searchgtt->Entry == NULL)
      {
         while(searchgtt)
         {
            while(lineartraverse < MAX_TRAVERSE)
             {
                if(searchgtt->next[lineartraverse]==NULL)
                 {
                     lineartraverse++;
                 }
                else
                 {
                    break;
                 }
             }
            tmp=searchgtt;

            if(lineartraverse == MAX_TRAVERSE )
             {
                 ISIL_DEBUG_TRACE(("End of Searched Stord String:: \n"));
                 break;
             } 

            searchgtt=searchgtt->next[lineartraverse];
  //          ISIL_DEBUG_TRACE(("GTT next Ptr :%x stored gti_string %d \n",searchgtt,lineartraverse));
            lineartraverse=0;
        }
        dpc_ssn = (ISIL_DPC_SSN *)(tmp->Entry);   
        if(dpc_ssn == NULL)
        {
           ISIL_DEBUG_TRACE(("After GTT Value are not found:: \n"));
           return NULL;
        }
 
        ISIL_DEBUG_TRACE(("After GTT Values are :: \n"));
      /*  ISIL_DEBUG_TRACE(("primary dpc=%d \n",dpc_ssn->primarydpc));
        ISIL_DEBUG_TRACE(("Secondary dpc=%d \n",dpc_ssn->secondarydpc));
        ISIL_DEBUG_TRACE(("SSN=%d \n",dpc_ssn->ssn));
        ISIL_DEBUG_TRACE(("RoutingFlag=%d \n",dpc_ssn->routeflag));
        ISIL_DEBUG_TRACE(("PrimarySSNFlag=%d \n",dpc_ssn->primaryssnflag));
        ISIL_DEBUG_TRACE(("SecondarySSNFlag=%d \n",dpc_ssn->secondaryssnflag));*/
        ISIL_WARNING_TRACE(("dpc1=%d dpc2=%d,ssn=%d \n",dpc_ssn->primarydpc,dpc_ssn->secondarydpc,dpc_ssn->ssn));



     // break;
        ret=0;
        return dpc_ssn;
     }
    else
     {
        dpc_ssn = (ISIL_DPC_SSN *)(searchgtt->Entry);   
        if(dpc_ssn == NULL)
        {
            ISIL_DEBUG_TRACE(("After GTT Value are not found:: \n"));
            return NULL;
        } 
      // ISIL_DEBUG_TRACE(("After GTT Values are :: \n"));
      // ISIL_DEBUG_TRACE(("primary dpc=%d \n",dpc_ssn->primarydpc));
      // ISIL_DEBUG_TRACE(("Secondary dpc=%d \n",dpc_ssn->secondarydpc));
      // ISIL_DEBUG_TRACE(("SSN=%d \n",dpc_ssn->ssn));
      // ISIL_DEBUG_TRACE(("RoutingFlag=%d \n",dpc_ssn->routeflag));
      // ISIL_DEBUG_TRACE(("PrimarySSNFlag=%d \n",dpc_ssn->primaryssnflag));
      // ISIL_DEBUG_TRACE(("SecondarySSNFlag=%d \n",dpc_ssn->secondaryssnflag));
        ISIL_WARNING_TRACE(("dpc1=%d dpc2=%d,ssn=%d \n",dpc_ssn->primarydpc,dpc_ssn->secondarydpc,dpc_ssn->ssn));
       // break;
       ret=0;
       return dpc_ssn;
    }
   }
  }
 else  
  { 
   if(gti_string[cnt]=='\0'|| searchgtt->next[gti_string[cnt]]==NULL)
    {
       ISIL_DEBUG_TRACE(("cnt  %d for Mindigits %d",(cnt+1),Rule->MinDigits));

       if((cnt+1) <= Rule->MinDigits)
       {
           ISIL_DEBUG_TRACE(("GTT Entry is not Found\n"));
           break;
       }

      if(searchgtt->Entry == NULL)
      {
         while(searchgtt)
         {
            while(lineartraverse < MAX_TRAVERSE)
             {
                if(searchgtt->next[lineartraverse]==NULL)
                 {
                     lineartraverse++;
                 }
                else
                 {
                    break;
                 }
             }
            tmp=searchgtt;

            if(lineartraverse == MAX_TRAVERSE )
             {
                 ISIL_DEBUG_TRACE(("End of Searched Stord String:: \n"));
                 break;
             } 

            searchgtt=searchgtt->next[lineartraverse];
  //          ISIL_DEBUG_TRACE(("GTT next Ptr :%x stored gti_string %d \n",searchgtt,lineartraverse));
            lineartraverse=0;
        }
        dpc_ssn = (ISIL_DPC_SSN *)(tmp->Entry);   
        if(dpc_ssn == NULL)
        {
           ISIL_DEBUG_TRACE(("After GTT Value are not found:: \n"));
           return NULL;
        }
 
        ISIL_DEBUG_TRACE(("After GTT Values are :: \n"));
      /*  ISIL_DEBUG_TRACE(("primary dpc=%d \n",dpc_ssn->primarydpc));
        ISIL_DEBUG_TRACE(("Secondary dpc=%d \n",dpc_ssn->secondarydpc));
        ISIL_DEBUG_TRACE(("SSN=%d \n",dpc_ssn->ssn));
        ISIL_DEBUG_TRACE(("RoutingFlag=%d \n",dpc_ssn->routeflag));
        ISIL_DEBUG_TRACE(("PrimarySSNFlag=%d \n",dpc_ssn->primaryssnflag));
        ISIL_DEBUG_TRACE(("SecondarySSNFlag=%d \n",dpc_ssn->secondaryssnflag));*/
        ISIL_WARNING_TRACE(("dpc1=%d dpc2=%d,ssn=%d \n",dpc_ssn->primarydpc,dpc_ssn->secondarydpc,dpc_ssn->ssn));



     // break;
        ret=0;
        return dpc_ssn;
     }
    else
     {
        dpc_ssn = (ISIL_DPC_SSN *)(searchgtt->Entry);   
        if(dpc_ssn == NULL)
        {
            ISIL_DEBUG_TRACE(("After GTT Value are not found:: \n"));
            return NULL;
        } 
      // ISIL_DEBUG_TRACE(("After GTT Values are :: \n"));
      // ISIL_DEBUG_TRACE(("primary dpc=%d \n",dpc_ssn->primarydpc));
      // ISIL_DEBUG_TRACE(("Secondary dpc=%d \n",dpc_ssn->secondarydpc));
      // ISIL_DEBUG_TRACE(("SSN=%d \n",dpc_ssn->ssn));
      // ISIL_DEBUG_TRACE(("RoutingFlag=%d \n",dpc_ssn->routeflag));
      // ISIL_DEBUG_TRACE(("PrimarySSNFlag=%d \n",dpc_ssn->primaryssnflag));
      // ISIL_DEBUG_TRACE(("SecondarySSNFlag=%d \n",dpc_ssn->secondaryssnflag));
        ISIL_WARNING_TRACE(("dpc1=%d dpc2=%d,ssn=%d \n",dpc_ssn->primarydpc,dpc_ssn->secondarydpc,dpc_ssn->ssn));
       // break;
       ret=0;
       return dpc_ssn;
    }

   }
  }

    if(gti_string[cnt] == 0x0A)
     {
       ISIL_DEBUG_TRACE(("IMR_GTDigts_Translation::Value are 0:: \n"));
       searchgtt=searchgtt->next[0];
     }
    else
     {
       searchgtt=searchgtt->next[gti_string[cnt]];
     } 
  // ISIL_DEBUG_TRACE(("GTT next Ptr :%x gti_string[%d] %d \n",searchgtt,cnt,gti_string[cnt]));
   cnt++;
  }
       return dpc_ssn;


}


/*****************************************************************************
 *  Purpose:
 *      This function Search the match in the dpc ssn table  for the dialed digits 
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
****************************************************************************/
