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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:23  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:02  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2002/01/09 23:28:35  mmiers
 * LOG: Switch FindTransport to a reference counting mechanism to
 * LOG: avoid race problems.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.4  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2001/01/09 23:54:55  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_transports.h>
#include <its_factory.h>
#include <its_transport_factory.h>
#include <its_ss7_trans.h>
#include <its_ip_trans.h>
#include <its_fifo_trans.h>
#include <its_gfifo_trans.h>
#include <its_tq_trans.h>
#include <its_assertion.h>

#ident "$Id: its_transport_factory.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creates an instance of an object controlled by this
 *      factory.
 *
 *  Input Parameters:
 *      factoryClass - the factory object class.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, this function returns a pointer to the initialized
 *          instance.
 *      On failure, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_Object
CreateInstance(FACTORY_Class factoryClass, va_list alist)
{
    TRANSPORT_Control *transport = NULL;
    char *name;
    ITS_USHORT instance;
    ITS_UINT mask;

    name = va_arg(alist, char *);
    instance = va_arg(alist, ITS_UINT);
    mask = va_arg(alist, ITS_UINT);

    switch (ITS_GET_TRANSPORT_TYPE(mask))
    {
    case ITS_TRANSPORT_SS7:
        transport =
            (TRANSPORT_Control *)SS7TRAN_CreateTransport(name,
                                                         instance,
                                                         mask);
        break;

    case ITS_TRANSPORT_FIFO:
        transport =
            (TRANSPORT_Control *)FIFOTRAN_CreateTransport(name,
                                                          instance,
                                                          mask);
        break;

    case ITS_TRANSPORT_GFIFO:
        transport =
            (TRANSPORT_Control *) GFIFOTRAN_CreateTransport(name,
                                                            instance,
                                                            mask);
        break;

    case ITS_TRANSPORT_CSOCKET:
        transport =
            (TRANSPORT_Control *)SOCKTRAN_CreateClientTransport(name,
                                                                instance,
                                                                mask);
        break;

    case ITS_TRANSPORT_SSOCKET:
        if (ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SSOCKET_DYN)
        {
            transport =
                (TRANSPORT_Control *)TRANSPORT_FindTransport(instance);
        }
        else
        {
            transport =
                (TRANSPORT_Control *)SOCKTRAN_CreateServerTransport(name,
                                                                    instance,
                                                                    mask);
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        transport =
            (TRANSPORT_Control *)TQUEUETRAN_CreateTransport(name,
                                                            instance,
                                                            mask);
        break;

    case ITS_TRANSPORT_DATAGRAM:
        transport =
            (TRANSPORT_Control *)SOCKTRAN_CreateEndPointTransport(name,
                                                                  instance,
                                                                  mask);
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }

    return ((ITS_Object)transport);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function deletes an instance of an object controlled by this
 *      factory.
 *
 *  Input Parameters:
 *      factoryClass - the factory object class.
 *      obj - the instance to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
DeleteInstance(FACTORY_Class factoryClass, ITS_Object obj)
{
    TRANSPORT_Control *transport = (TRANSPORT_Control *)obj;

    if (transport)
    {
        switch (ITS_GET_TRANSPORT_TYPE(TRANSPORT_MASK(transport)))
        {
        case ITS_TRANSPORT_SS7:
            SS7TRAN_DeleteTransport((SS7TRAN_Manager *)transport);
            break;

        case ITS_TRANSPORT_FIFO:
            FIFOTRAN_DeleteTransport((FIFOTRAN_Manager *)transport);
            break;

        case ITS_TRANSPORT_GFIFO:
            GFIFOTRAN_DeleteTransport((GFIFOTRAN_Manager *)transport);
            break;

        case ITS_TRANSPORT_CSOCKET:
            SOCKTRAN_DeleteClientTransport((SOCKTRAN_Manager *)transport);
            break;

        case ITS_TRANSPORT_SSOCKET:
            if (ITS_GET_TRANSPORT_FLAGS(TRANSPORT_MASK(transport)) &
                ITS_TRANSPORT_SSOCKET_DYN)
            {
                TRANSPORT_UnfindTransport(transport);
            }
            SOCKTRAN_DeleteServerTransport((SOCKTRAN_Manager *)transport);
            break;

        case ITS_TRANSPORT_TQUEUE:
            TQUEUETRAN_DeleteTransport((TQUEUETRAN_Manager *)transport);
            break;

        case ITS_TRANSPORT_DATAGRAM:
            SOCKTRAN_DeleteEndPointTransport((SOCKTRAN_Manager *)transport);
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
    }
}

/*
 * the lockable class record
 */
ITSDLLAPI FACTORY_ClassRec itsTRANSPORT_FACTORY_ClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsCORE_ClassRec,/* superclass */
        0,                          /* no meaningful instance size */
        ITS_FALSE,                  /* not initted */
        0,                          /* initial refCount */
        TRANSPORT_FACTORY_CLASS_NAME,/* class name */
        ITS_CLASS_NO_INIT,          /* class initialize */
        ITS_CLASS_NO_DEST,          /* class destroy */
        ITS_CLASS_PART_NO_INIT,     /* class initialize part */
        ITS_CLASS_PART_NO_DEST,     /* class destroy part */
        ITS_INST_NO_CONST,          /* can't instantiate from here */
        ITS_INST_NO_DEST,           /* can't destruct anything */
        ITS_INST_CLONE_INHERIT,     /* inherit clone */
        ITS_INST_PRINT_INHERIT,     /* inherit print */
        ITS_INST_SERIAL_INHERIT,    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,    /* inherit equals */
        ITS_INST_HASH_INHERIT,      /* inherit equals */
        NULL                        /* no extension of interest */
    },
    /* factory part */
    {
        CreateInstance,
        DeleteInstance
    }
};

ITSDLLAPI ITS_Class itsTRANSPORT_FACTORY_Class =
    (ITS_Class)&itsTRANSPORT_FACTORY_ClassRec;
