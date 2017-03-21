/**************************************************************************************** 
 *                                                                                      *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.                *
 *             Manufactured in the United States of America.                            *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.                   *
 *                                                                                      *
 *   This product and related documentation is protected by copyright and               *
 *   distributed under licenses restricting its use, copying, distribution              *
 *   and decompilation.  No part of this product or related documentation               *
 *   may be reproduced in any form by any means without prior written                   *
 *   authorization of IntelliNet Technologies and its licensors, if any.                *
 *                                                                                      *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the                  *
 *   government is subject to restrictions as set forth in subparagraph                 *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software                   *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                                    *
 *                                                                                      *
 **************************************************************************************** 
 *
 * ID: $Id: Main.cpp,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:34  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:26  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:10  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.1  2005/02/08 11:38:53  kannanp
 * LOG: WorkItem Initial - Hari Priya.
 * LOG:
 * LOG:
 ****************************************************************************************
 *
 * Description: The WorkItem Sample Application illustrates the creation and 
 *              usage of the WorkItem and WorkItemPool and the related 
 *              functions.

 * Usage:       The WorkItemPool is created using the C Function  
 *              
 *              WORKITEMPOOL *tmpinst = WORKITEMPOOL_InitPool( void *data,
 *                                      50001, 4, 0, WORKITEMPOOL_Dispatch)
 *
 *              This function creates a WorkItemPool, that internally creates
 *              a WorkItem Queue with instance 50001.
 *
 *              The desired number of WorkItems can be created and added to the 
 *              Pool using the function
 *               
 *              WORKITEM_Instance *item = WORKITEM_Create( 12, false, App_func)     
 *               
 *              This function would create a WorkItem with size 12, nonpersistent 
 *              and points to the func App_func. If the WorkItem is made persistent,
 *              the event would return to the queue. This function returns a 
 *              pointer to the allocated WorkItem.
 *              Once the WorkItem has been created, the event to be placed in the 
 *              Queue has to be assigned to the object pointed to by the Instance
 *              returned by WorkItem.
 *               .....
 *              item->object = evt;
 *
 *              Now the WorkItem (i.e, the event) has to be added to the Pool and 
 *              thus placed on the Queue created by the Pool. The WorkItemPool gets
 *              the event from the queue and dispatches that the event to one of the 
 *              available threads in the Pool. 
 *            
 *              WORKITEM_PutWorkItem(TRANSPORT_INSTANCE(WORKITEMPOOL_QUEUE(tmpinst)),
 *                                                                             item)
 *              The arguments for this function is the Instance of the Queue created 
 *              by the Pool and the pointer to the WorkItem.
 *                
 ****************************************************************************************/
 #ident "$Id: Main.cpp,v 1.1.1.1 2007-10-08 11:12:01 bsccs2 Exp $"

#include <engine.h>

int main(int argc, const char **argv)
{
    /* Set the application name */
    APPL_SetName("SampleApp_WorkItem");

    /* Set the application extension */
    APPL_SetConfigFileExtension("xml");

    //DBC_SetDoCommand(ExecuteCommand);

    ENGINE_Initialize(argc, argv, NULL, 0);

    return(ENGINE_Run(argc, argv));
}


