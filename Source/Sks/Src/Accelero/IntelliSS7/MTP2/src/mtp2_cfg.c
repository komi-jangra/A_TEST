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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:45  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.2  2006/07/05 14:48:40  gdevanand
 * LOG: Changes for combined MTP2 and LAPD (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 17:25:56  lbana
 * LOG: MTP2 configuration utility.
 * LOG:
 * LOG:
 ***************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <engine.h>

#define INTELLI_MTP2

#include <mtp2_cmn.h>

#ident "$Id: mtp2_cfg.c,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $"

/**************************************************************
 * INI Configuartion example.
 *
 *   ;; User MUST configure even numbered slots. For SS7 the 
 *   ;; ODD numbered slots are NOT used in MPC8560.
 *   ;;
 *   ;; Note: at present mcc_port names are not used but the
 *   ;; the slot configuration should be under mcc_ports.
 *   ;; MCC1 channel range 0-127
 *   ;; MCC2 channel range 128-255
 *   ;; MCC1 Ports: PA=1, PB=2, PC=3, PD=4
 *   ;; MCC2 Ports: PA=5, PB=6, PC=7, PD=8
 *   ;;
 *   [mcc_port1]
 *   timeSlots = 0,2,4,6
 *
 **************************************************************/

#define MTP2_CONFIG_APP_NAME  "mtp2"
#define MCC_PORT_STRING       "mcc_port%d"
#define MCC_TS_SEP_STRING     " ,:"
#define MCC_TIMESLOTS_STRING  "timeSlots"
#define MCC_OPER_MODE_STRING  "loopBack"
#define MCC_LOOPBACK_YES      "yes"
#define MCC_LOOPBACK_NO       "no"
#define MTP2_CTL_DEV_NAME     "/dev/mcc_ctl"

static ITS_INT
RetrieveConfigInfo(RESFILE_Manager *res);

static void
ConfigureMTP2(const char *dev);

static void
AddDummyDSMCfg(RESFILE_Manager *res);

static void
Usage(const char *exe)
{
    printf("%s [-app %s] [-f %s]\n", exe, "mtp2", "mtp2.ini");
    return;
}

/* 
 * Only even numbered are used for MPC8560
 */
#define MTP2_MAX_SS7 128

typedef enum
{
    MCC1_PORTA,
    MCC1_PORTB,
    MCC1_PORTC,
    MCC1_PORTD,
    MCC2_PORTA,
    MCC2_PORTB,
    MCC2_PORTC,
    MCC2_PORTD
}
TDMA_PORTS;

struct MTP2Cfg
{
    int port;
    int link;
} 
DLinks[MTP2_MAX_SS7];

int 
main(int argc, const char **argv)
{
    int i = 1; /* skip exe name */
    ITS_BOOLEAN isExistApp = ITS_FALSE;
    RESFILE_Manager *res = NULL;
    char  filename[ITS_PATH_MAX];
    int ret = 0;

    memset(&DLinks, 0xFF, sizeof(DLinks));

    while (i < argc)
    {
        if (strcmp(argv[i], "-app") == 0)
        {
            i++;
            APPL_SetName(argv[i]);
            sprintf(filename, "%s.ini", argv[i]);

            isExistApp = ITS_TRUE;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            /* TODO: Parse the file name */
            i++;
        }
        else
        {
            Usage(argv[0]);

            return -1;
        }

        i++;
    }

    if (!isExistApp)
    {
        APPL_SetName(MTP2_CONFIG_APP_NAME);
        sprintf(filename, "%s.ini", MTP2_CONFIG_APP_NAME);
        printf("Application Name = %s \n", filename);
    }

    res = RESFILE_CreateResourceManager(filename);

    if (res != NULL)
    {
        AddDummyDSMCfg(res);

        ret = ITS_AddFeature(itsDSM_StubImplClass);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = ITS_GlobalStart(0);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ret = RetrieveConfigInfo(res);

        ITS_C_ASSERT(ret == ITS_SUCCESS);

        ConfigureMTP2(MTP2_CTL_DEV_NAME);

        ITS_GlobalStop(0);
    }

    return 0; 
}

static int
RetrieveConfigInfo(RESFILE_Manager *res)
{
    const char  *nextSect = NULL;
    char        var[ITS_PATH_MAX];
    char        val[ITS_PATH_MAX];
    ITS_INT     port;
    char        *timeslots;
    int         link;
    int         counter = 0;

    memset(var, 0, sizeof(char) * ITS_PATH_MAX);
    memset(val, 0, sizeof(char) * ITS_PATH_MAX);

    RESFILE_Lock(res);

    RESFILE_Rewind(res, nextSect); /* start from global */

    /* Any globals do it here...? */
 
    nextSect = RESFILE_GetNextSectionName(res, nextSect);

    while (nextSect)
    {
        sscanf(nextSect, MCC_PORT_STRING, &port);

        while (RESFILE_GetKeyName(res, nextSect, 
                                  var, sizeof(var)) == ITS_SUCCESS &&
               RESFILE_GetKeyValue(res, nextSect,
                                   val, sizeof(val)) == ITS_SUCCESS)
        {
            if (strcmp(var, MCC_TIMESLOTS_STRING) == 0)
            {
                timeslots = val;
                timeslots = strtok(val, MCC_TS_SEP_STRING);

                while (timeslots)
                {
                    link = RESFILE_ParseNum(timeslots);

                    if (link % 2 != 0 && link < MTP2_MAX_SS7)
                    {
                        /* Configured odd numbered slots */
                        printf("Odd numbered: TimeSlot=%d\n", link);
                        RESFILE_Unlock(res);

                        return ITS_EINVALIDARGS;
                    }

                    DLinks[counter].port = port;
                    DLinks[counter++].link = link;

                    timeslots = strtok(NULL, MCC_TS_SEP_STRING);
                }
            }
            else if (strcmp(var, MCC_OPER_MODE_STRING) == 0)
            {
            }
        }
        nextSect = RESFILE_GetNextSectionName(res, nextSect);
    }

    RESFILE_Unlock(res);

    return ITS_SUCCESS;
}

static void
ConfigureMTP2(const char *devname)
{
    int             i = 0;
    int             ctlFd = -1;
    struct mtp2_cfg cfg;

    memset(&cfg, 0, sizeof(cfg));

    /* Open MTP2 control device. */
    ctlFd = open(devname, O_WRONLY);

    if (ctlFd < 0)
    {
        printf("Could not open MTP2 control device: err=%d\n",
                errno);
        return;
    }

    ioctl(ctlFd, MTP2_IOCRESET, 0); 

    for (i = 0; i < MTP2_MAX_SS7; i++)
    {
        if (DLinks[i].link>= 0 && DLinks[i].link <= 255)
        {
            ++cfg.num_chan;
            cfg.channels[i].chan = DLinks[i].link;
            cfg.channels[i].loop = 0; /* 0: Normal mode.
                                       * 1: Loopback mode.
                                       */

            ioctl(ctlFd, MTP2_IOCSCONFIG, &cfg);
        }
        else
        {
            break; /* no more to configure */
        }
    }

    ioctl(ctlFd, MTP2_IOCENABLE);

    close(ctlFd);

    return;
}

#define DSM_FT_GROUP_0 "DsmFtGroup0"

/* 
 * Dummy DSM configuration FT/HA is needed to enjoy the RESFILE features.
 * It reduces the configuration burden on User.
 * Idea is to KIS for mtp2.ini
 *
 * Any Attributes/Elements that are not directly required for MTP2 
 * configuration should be added to the RESFILE.
 *
 */
static void
AddDummyDSMCfg(RESFILE_Manager *res)
{
    int ret = 0;

    ret = RESFILE_AddSection(res, DSM_FAULT_TOLERANCE_STRING);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FAULT_TOLERANCE_STRING, 
                              DSM_MAX_NUM_FT_GROUPS_STRING, "1");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FAULT_TOLERANCE_STRING, 
                              DSM_MAX_NUM_PROCESSES_STRING, "1");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FAULT_TOLERANCE_STRING, 
                              DSM_MAX_NUM_NODES_STRING, "1");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FAULT_TOLERANCE_STRING, 
                              DSM_NODE_ID_STRING, "0");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FAULT_TOLERANCE_STRING, 
                              DSM_PROCESS_ID_STRING, "0");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddSection(res, DSM_FT_GROUP_0);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_FT_GROUP_ID_STRING, "0");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_FT_GROUP_ID_STRING, "1");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_SIZE_STRING, "1048576");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_BASE_ADDRESS_STRING, "0x80000000");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_MAX_NUM_TABLES_STRING, "255");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_TYPE_STRING, "STUB");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_NUM_FT_GROUP_MEMBERS_STRING, "1");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_FT_GROUP_MEMBER_NODE_ID_STRING, "0");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_FT_GROUP_MEMBER_PROCESS_ID_STRING, "0");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(res, DSM_FT_GROUP_0, 
                              DSM_NUM_MASTER_FT_GROUP_MEMBERS_STRING, "0");
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    return;
}

