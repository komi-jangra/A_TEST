/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: ConfigTest.c,v 1.1.1.1 2007-10-08 11:12:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:57  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:15  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:06  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:18  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:40  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.2  2002/02/05 20:19:53  ssharma
 * LOG: IntelliNet ISUP stack test directory.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/29 20:27:21  ssharma
 * LOG: INI file parse test.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/23 18:04:03  ssharma
 * LOG: ISUP specific ini file parse test.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:14  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 16:46:41  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/08/27 02:25:44  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for DEC build
 * LOG:
 * LOG: Revision 1.3  1999/08/20 20:40:41  mmiers
 * LOG:
 * LOG:
 * LOG: Make sure I got this right.
 * LOG:
 * LOG: Revision 1.2  1999/08/20 20:09:59  mmiers
 * LOG:
 * LOG:
 * LOG: Resfile test.
 * LOG:
 * LOG: Revision 1.1  1999/08/20 00:10:39  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a free twice bug in the resource manager.
 * LOG:
 *
 ****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(unix)
#include <unistd.h>
#include <signal.h>
#endif

#include <its.h>
#include <its_app.h>
#include <its_iniparse.h>
#include <isup_parse.h>

int
main(int argc, char **argv)
{
    char key[ITS_PATH_MAX << 2], val[ITS_PATH_MAX << 2];
    const char *section;
    int ret = ITS_SUCCESS;

    static ITS_BOOLEAN localpcFound = ITS_FALSE;
    static ITS_BOOLEAN remotepcFound = ITS_FALSE;
    static ITS_BOOLEAN variantFound = ITS_FALSE;
    static ITS_BOOLEAN timerIDFound = ITS_FALSE;
    static ITS_BOOLEAN timeoutHndlFound = ITS_FALSE;
    static ITS_BOOLEAN startCicFound = ITS_FALSE;
    static ITS_BOOLEAN numCicsFound = ITS_FALSE;
    static ITS_BOOLEAN cicRuleFound = ITS_FALSE;

    static char localpc[32];
    static char remotepc[32];
    static ITS_OCTET timer_id = 0;
    static ISUP_OPC_DPC_INFO *odInfo = NULL;
    static ISUP_CKGP_INFO ckgp_info;
    static ITS_USHORT startCic = 0;
    static ITS_USHORT cic_index = 0;
    static ITS_USHORT number_cics = 0;
    static ITS_USHORT gpid = 0;

    ITS_UINT local = 0;
    ITS_UINT remote = 0;
    ITS_OCTET varType = 0;
    ITS_OCTET opcid = 0;
    ITS_OCTET dpcid = 0;
    ITS_USHORT opcdpc = 0;
    ISUP_PC_INFO *opcInfo = NULL;
    ISUP_PC_INFO *dpcInfo = NULL;
    ISUP_TMR_HNDL timeoutHndl;
    ISUP_CKGP_CTRL cicRule;

#if 0
    ITS_BOOLEAN localpcFound = ITS_FALSE;
    ITS_BOOLEAN remotepcFound = ITS_FALSE;
    ITS_BOOLEAN variantFound = ITS_FALSE;
    ITS_BOOLEAN timerIDFound = ITS_FALSE;
    ITS_BOOLEAN timeoutHndlFound = ITS_FALSE;
    ITS_BOOLEAN startCICFound = ITS_FALSE;
    ITS_BOOLEAN numCICsFound = ITS_FALSE;
    ITS_BOOLEAN CICRuleFound = ITS_FALSE;

    char localpc[32];
    char remotepc[32];

    ITS_UINT local = 0;
    ITS_UINT remote = 0;
    ITS_OCTET varType = 0;
    ITS_OCTET opcid = 0;
    ITS_OCTET dpcid = 0;
    ITS_USHORT opcdpc = 0;
    ISUP_PC_INFO *opcInfo = NULL;
    ISUP_PC_INFO *dpcInfo = NULL;
    ISUP_OPC_DPC_INFO *odInfo = NULL;
    ISUP_TMR_HNDL timeoutHndl;
    static ITS_OCTET timer_id = 0;
#endif

    RESFILE_Manager *res;

    APPL_SetConfigFileName("ISUP.ini");

    RESFILE_SetAltCommentChar('!');

    if (ITS_GlobalStart(0) != ITS_SUCCESS)
    {
        exit(0);
    }

    if ((res = RESFILE_CreateResourceManager((char *)APPL_GetConfigFileName()))
                                                                == NULL)
    {
        exit(0);
    }

    RESFILE_Lock(res);

    RESFILE_Rewind(res, NULL);

    section = NULL;
    while ((section = RESFILE_GetNextSectionName(res, section)) != NULL)
    {
        RESFILE_Rewind(res, section);

        printf("SECTION '%s':\n", section);

        if (strcmp(ITU_ISUP_CLASS_NAME, section) == 0)
        {
           __ISUP_Init_HashTables();

           while (RESFILE_GetKeyName(res, section, key, ITS_PATH_MAX)
                                                          == ITS_SUCCESS &&
                  RESFILE_GetKeyValue(res, section, val, ITS_PATH_MAX)
                                                          == ITS_SUCCESS)
           {
               // printf("  KEY: '%s' VALUE: '%s'\n", key, val);

               if (strcmp(ISUP_LOCAL_PC_STR, key) == 0)
               {
                   printf("  localPc: '%s' \n", val);
                   strncpy(localpc, val, strlen(val) + 1);
                   localpcFound = ITS_TRUE;                            

                   if (odInfo != NULL)
                   {
                       free (odInfo); 
                       odInfo = NULL;
                   }

                   odInfo =
                     (ISUP_OPC_DPC_INFO*) calloc(1, sizeof(ISUP_OPC_DPC_INFO));
                   assert (odInfo != NULL);
               }
               else if (strcmp(ISUP_REMOTE_PC_STR, key) == 0)
               {
                   printf("  remotePc: '%s' \n", val);
                   strncpy(remotepc, val, strlen(val) + 1);
                   remotepcFound = ITS_TRUE;                                 
               }
               else if (strcmp(ISUP_VARIANT_STR, key) == 0)
               {
                   printf("  variant: '%s' \n", val);
                   variantFound = ITS_TRUE;

                   varType = ISUP_VarType(val);

                   if (varType == ISUP_UNKNOWN)
                   {
                       printf("\n\n Invalid Variant (%s) \n\n", val);
                       //break;
                   }

                   if (ISUP_VarANSI(val))
                   {
                       local = ISUP_PCStrToNum_ANSI(localpc);
                       remote = ISUP_PCStrToNum_ANSI(remotepc);
                   }
                   else if (ISUP_VarITU(val))
                   {
                       local = ISUP_PCStrToNum_ITU(localpc);
                       remote = ISUP_PCStrToNum_ITU(remotepc);
                   } 

                   printf("  localPC: %d. remotePC: %d. \n", local, remote);

                   opcInfo = ISUP_FindOpc(local);
                   dpcInfo = ISUP_FindDpc(remote);

                   printf("\n opcInfo %x. dpcInfo %x", opcInfo, dpcInfo);
                   if (opcInfo == NULL)
                   {
                        opcid = ISUP_NextOpcId();
                        printf("\n opcid %d", opcid);

                        ret = ISUP_AllocOpcOpcId(local, opcid);
                        assert(ret == ITS_SUCCESS);
                   }
                   else
                   {
                        opcid = opcInfo->pc_id;
                   }
                   ISUP_PrintAllOpcOpcId();                        
                                               
                   if (dpcInfo == NULL)
                   {
                        dpcid = ISUP_NextDpcId();

                        ret = ISUP_AllocDpcDpcId(remote, dpcid);
                        assert(ret == ITS_SUCCESS);
                   }
                   else
                   {
                        dpcid = dpcInfo->pc_id;
                   }

                   opcdpc |= (opcid << 8) | dpcid;
#if 0
                   odInfo =
                     (ISUP_OPC_DPC_INFO*) calloc(1, sizeof(ISUP_OPC_DPC_INFO));
                   assert (odInfo != NULL);
#endif
                   ISUP_InitOpcDpc(odInfo, opcdpc, varType);
               }
               else if (strcmp(ISUP_TIMER_STR, key) == 0)
               {
                   timer_id = ISUP_Tmr(val);

                   if ((timer_id < 0) || (timer_id >= ISUP_MAX_TMRS))
                   {
                       printf("\n TimerId incorrect: %s", timer_id);
                   }
                   else
                   {
                        timerIDFound = ITS_TRUE;
                   }
               }
               else if (strcmp(ISUP_TIMER_VAL_STR, key) == 0)
               {
                   assert (timerIDFound == ITS_TRUE);

                   if (strcmp(val, "DEF") == 0)
                   {
                       // use the default which is already set
                   }
                   else if (strcmp(val, "OFF") == 0)
                   {
                       // set it to 0
                       odInfo->tmr_hndl_info[timer_id].tmr_value = 0;
                   }
                   else
                   {
                       // set it to the value specified
                       odInfo->tmr_hndl_info[timer_id].tmr_value = atoi(val);
                   }

                   printf("\n TimerId %d. TimerValue %d",
                          timer_id, odInfo->tmr_hndl_info[timer_id].tmr_value);
               } 
               else if (strcmp(ISUP_TIMER_HNDL_STR, key) == 0)
               {
                   timeoutHndlFound = ITS_TRUE;

                   timeoutHndl = ISUP_TmrHndl(val);

                   assert (timeoutHndl != ISUP_TMR_HNDL_INVALID);

                   odInfo->tmr_hndl_info[timer_id].tmr_hndl_layer = timeoutHndl;

                   printf(" TimeoutHandler %s ",
                    ISUP_TmrHndlString
                         (odInfo->tmr_hndl_info[timer_id].tmr_hndl_layer)); 
               }   
               else if (strcmp(ISUP_CIC_RULE_STR, key) == 0)
               {
                  // Check: Mandatory params. OPC / DPC / Variant should be set by now

                  if (!localpcFound || !remotepcFound || !variantFound)
                  {
                      printf("\n Incomplete Configuration Info. ");
                      printf("Check LocalPC / RemotePC / Variant \n \n");
                  }

#if 0
                  if (startCicFound)
                  {
                      ckgp_info.ckgp_id = gpid;
                      ISUP_InsertCkgpInfo(odInfo, &ckgp_info);
                      ISUP_PrintAllCkgps(odInfo);
                  }
#endif
                  // Fresh Circuit Group data.
                  ISUP_InitCkgp(&ckgp_info, 0xFFFF);
                  startCicFound = ITS_FALSE;

                  cicRuleFound = ITS_TRUE;  
              }   
              else if (strcmp(ISUP_START_CIC_STR, key) == 0)
              {
                  assert (cicRuleFound == ITS_TRUE);
#if 0
                  if (number_cics != 0)
                  {
                      ckgp_info.ckgp_id = gpid;
                      ISUP_AddUsableCics(&ckgp_info, cic_index, number_cics);
                  }
#endif
                  startCic = atoi(val);
                  printf("\n start cic : %d", startCic);

                  VAR_GetCkgpFromCIC(odInfo->isup_var_class, startCic,
                           &cic_index, &gpid, &number_cics);

                  startCicFound = ITS_TRUE;
              }   
              else if (strcmp(ISUP_NUM_CICS_STR, key) == 0)
              {
                  number_cics = atoi(val);
                  printf("\n number of cics : %d", number_cics);

                  if (number_cics != 0)
                  {
                      printf("\n going to insert ckgp info: gpid %d.", gpid);
                      ckgp_info.ckgp_id = gpid;
                      ISUP_AddUsableCics(&ckgp_info, cic_index, number_cics);

                      if (ISUP_CkgpExists(odInfo, ckgp_info.ckgp_id))
                      {
                          printf("\n Record exists: gpid %d", ckgp_info.ckgp_id);
                          ISUP_UpdateCkgpInfo(odInfo, ckgp_info.ckgp_id,
                                                                 &ckgp_info);
                          ISUP_PrintAllCkgps(odInfo);
                      }
                      else
                      {
                          ISUP_InsertCkgpInfo(odInfo, &ckgp_info);
                          ISUP_PrintAllCkgps(odInfo);
                      }
                  }                                                                      
               }   

           } // while key-value pair found

        }
        else
        {
            // nothing to do: just skip ahead
        }
    }

    RESFILE_Unlock(res);

    ITS_GlobalStop();

    return (0);
}


void
ISUP_InitNodeConfig(char *key, char *val)
{
    //char key[ITS_PATH_MAX << 2], val[ITS_PATH_MAX << 2];
    const char *section;
    int ret = ITS_SUCCESS;

    static ITS_BOOLEAN localpcFound = ITS_FALSE;
    static ITS_BOOLEAN remotepcFound = ITS_FALSE;
    static ITS_BOOLEAN variantFound = ITS_FALSE;
    static ITS_BOOLEAN timerIDFound = ITS_FALSE;
    static ITS_BOOLEAN timeoutHndlFound = ITS_FALSE;
    static ITS_BOOLEAN startCicFound = ITS_FALSE;
    static ITS_BOOLEAN numCicsFound = ITS_FALSE;
    static ITS_BOOLEAN cicRuleFound = ITS_FALSE;

    static char localpc[32];
    static char remotepc[32];
    static ITS_OCTET timer_id = 0;
    static ISUP_OPC_DPC_INFO *odInfo = NULL;
    static ISUP_CKGP_INFO ckgp_info;
    static ITS_USHORT startCic = 0;
    static ITS_USHORT cic_index = 0;
    static ITS_USHORT number_cics = 0;
    static ITS_USHORT gpid = 0;

    ITS_UINT local = 0;
    ITS_UINT remote = 0;
    ITS_OCTET varType = 0;
    ITS_OCTET opcid = 0;
    ITS_OCTET dpcid = 0;
    ITS_USHORT opcdpc = 0;
    ISUP_PC_INFO *opcInfo = NULL;
    ISUP_PC_INFO *dpcInfo = NULL;
    ISUP_TMR_HNDL timeoutHndl;
    ISUP_CKGP_CTRL cicRule;

    if (strcmp(ISUP_LOCAL_PC_STR, key) == 0)
    {
        printf("  localPc: '%s' \n", val);
        strncpy(localpc, val, strlen(val) + 1);
        localpcFound = ITS_TRUE;
    } 
    else if (strcmp(ISUP_REMOTE_PC_STR, key) == 0)
    {
        printf("  remotePc: '%s' \n", val);
        strncpy(remotepc, val, strlen(val) + 1);
        remotepcFound = ITS_TRUE;
    }
    else if (strcmp(ISUP_VARIANT_STR, key) == 0)
    {
        printf("  variant: '%s' \n", val);
        variantFound = ITS_TRUE;

        varType = ISUP_VarType(val);

        if (varType == ISUP_UNKNOWN)
        {
            printf("\n\n Invalid Variant (%s) \n\n", val);
            //break;
        }

        if (ISUP_VarANSI(val))
        {
            local = ISUP_PCStrToNum_ANSI(localpc);
            remote = ISUP_PCStrToNum_ANSI(remotepc);
        }
        else if (ISUP_VarITU(val))
        {
            local = ISUP_PCStrToNum_ITU(localpc);
            remote = ISUP_PCStrToNum_ITU(remotepc);
        } 

        printf("  localPC: %d. remotePC: %d. \n", local, remote);

        opcInfo = ISUP_FindOpc(local);
        dpcInfo = ISUP_FindDpc(remote);

        if (opcInfo == NULL)
        {
             opcid = ISUP_NextOpcId();

             ret = ISUP_AllocOpcOpcId(local, opcid);
             assert(ret == ITS_SUCCESS);
        }
        else
        {
             opcid = opcInfo->pc_id;
        }

        if (dpcInfo == NULL)
        {
             dpcid = ISUP_NextDpcId();

             ret = ISUP_AllocDpcDpcId(remote, dpcid);
             assert(ret == ITS_SUCCESS);
        }
        else
        {
             dpcid = dpcInfo->pc_id;
        }

        opcdpc |= (opcid << 8) | dpcid;
               
        odInfo = (ISUP_OPC_DPC_INFO*) calloc(1, sizeof(ISUP_OPC_DPC_INFO));
        assert (odInfo != NULL);

        ISUP_InitOpcDpc(odInfo, opcdpc, varType); 


#if 0
                   ISUP_UpdateOpcDpc(odInfo); 
                   ISUP_PrintOpcDpc(odInfo);
#endif
    }
    else if (strcmp(ISUP_TIMER_STR, key) == 0)
    {
         timer_id = ISUP_Tmr(val);
     
         if ((timer_id < 0) || (timer_id >= ISUP_MAX_TMRS))
         {
              printf("\n TimerId incorrect: %s", timer_id);
         }
         else
         {
              timerIDFound = ITS_TRUE;
         }
    }
    else if (strcmp(ISUP_TIMER_VAL_STR, key) == 0)
    {
         assert (timerIDFound == ITS_TRUE);

         if (strcmp(val, "DEF") == 0)
         {
             // use the default which is already set
         } 
         else if (strcmp(val, "OFF") == 0)
         {
             // set it to 0
             odInfo->tmr_hndl_info[timer_id].tmr_value = 0; 
         } 
         else 
         {
             // set it to the value specified 
             odInfo->tmr_hndl_info[timer_id].tmr_value = atoi(val); 
         } 

         printf("\n TimerId %d. TimerValue %d",
                    timer_id, odInfo->tmr_hndl_info[timer_id].tmr_value);

    } 
    else if (strcmp(ISUP_TIMER_HNDL_STR, key) == 0)
    {
         timeoutHndlFound = ITS_TRUE;
                  
         timeoutHndl = ISUP_TmrHndl(val);
                  
         assert (timeoutHndl != ISUP_TMR_HNDL_INVALID);
                 
         odInfo->tmr_hndl_info[timer_id].tmr_hndl_layer = timeoutHndl; 

         printf(" TimeoutHandler %s ",
          ISUP_TmrHndlString(odInfo->tmr_hndl_info[timer_id].tmr_hndl_layer));
    } 
    else if (strcmp(ISUP_CIC_RULE_STR, key) == 0)
    {
        // Check: Mandatory params. OPC / DPC / Variant should be set by now

        if (!localpcFound || !remotepcFound || !variantFound)
        {
            printf("\n Incomplete Configuration Info. ");
            printf("Check LocalPC / RemotePC / Variant \n \n");
        }

#if 0
        if (startCicFound)
        {
            ckgp_info.ckgp_id = gpid;
            ISUP_InsertCkgpInfo(odInfo, &ckgp_info);
            ISUP_PrintAllCkgps(odInfo);
        }
#endif
        // Fresh Circuit Group data.
        ISUP_InitCkgp(&ckgp_info, 0xFFFF);
        startCicFound = ITS_FALSE;

        cicRuleFound = ITS_TRUE;
        cicRule = ISUP_CkgpCtrl(val);
        number_cics = 0;

        if (cicRule == ISUP_CKGP_CTRL_INV)
        {
            printf("\n CIC rule Incorrect: %s", val);
        }
        else
        {
            printf("\n cic rule: %s", val); 
        }

        ckgp_info.ckgp_control = cicRule; 
    }
    else if (strcmp(ISUP_START_CIC_STR, key) == 0)
    {
        assert (cicRuleFound == ITS_TRUE);
#if 0
        if (number_cics != 0)
        {
            ckgp_info.ckgp_id = gpid;
            ISUP_AddUsableCics(&ckgp_info, cic_index, number_cics);
        }
#endif
        startCic = atoi(val);
        printf("\n start cic : %d", startCic); 

        VAR_GetCkgpFromCIC(odInfo->isup_var_class, startCic,
                           &cic_index, &gpid, &number_cics);

        startCicFound = ITS_TRUE;
    }
    else if (strcmp(ISUP_NUM_CICS_STR, key) == 0)
    {
        number_cics = atoi(val);
        printf("\n number of cics : %d", number_cics); 
        
        if (number_cics != 0)
        {
            printf("\n going to insert ckgp info: gpid %d.", gpid);
            ckgp_info.ckgp_id = gpid;
            ISUP_AddUsableCics(&ckgp_info, cic_index, number_cics);
        
            if (ISUP_CkgpExists(odInfo, ckgp_info.ckgp_id))
            {
                printf("\n Record exists for group %d", ckgp_info.ckgp_id);
                ISUP_UpdateCkgpInfo(odInfo, ckgp_info.ckgp_id, &ckgp_info);
                ISUP_PrintAllCkgps(odInfo);
            }
            else
            {    
                ISUP_InsertCkgpInfo(odInfo, &ckgp_info);
                ISUP_PrintAllCkgps(odInfo);
            }
        }
    }

}
