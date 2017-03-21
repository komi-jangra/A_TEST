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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.3  2002/09/20 15:44:08  mmiers
 * LOG: Fix the licensing binaries
 * LOG:
 * LOG: Revision 7.2  2002/09/19 21:08:29  mmiers
 * LOG: Add a print for debugging
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2002/02/14 19:43:22  mmiers
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/04/24 23:13:38  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 3.5  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:03  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.8  2000/07/27 22:03:23  mmiers
 * LOG: Last of the core changes for PR3.  Removed last stubs, stack
 * LOG: binding is now dynamic.
 * LOG:
 * LOG: Revision 2.7  2000/03/18 21:03:49  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.6  2000/02/15 20:34:44  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 2.5  2000/02/15 16:37:19  mmiers
 * LOG:
 * LOG: Good enough for a working version.  I have some ideas about cleaning
 * LOG: up the leaks (use ITS_RegisterFeature for the ClassInit).
 * LOG:
 * LOG: Revision 2.4  2000/02/02 17:05:56  mmiers
 * LOG:
 * LOG:
 * LOG: Debug feature work.
 * LOG:
 * LOG: Revision 2.3  2000/02/01 23:01:05  mmiers
 * LOG:
 * LOG:
 * LOG: Add AddFeature() function.
 * LOG:
 * LOG: Revision 2.2  2000/02/01 21:29:24  mmiers
 * LOG:
 * LOG:
 * LOG: Some updates for specific features.
 * LOG:
 * LOG: Revision 2.1  2000/01/26 18:12:57  mmiers
 * LOG:
 * LOG:
 * LOG: Add feature processing.
 * LOG:
 * LOG: Revision 1.5  2000/01/26 18:01:23  mmiers
 * LOG:
 * LOG:
 * LOG: Start the feature processing function.
 * LOG:
 * LOG: Revision 1.4  2000/01/26 17:36:31  mmiers
 * LOG:
 * LOG:
 * LOG: Fix feature processing.
 * LOG:
 * LOG: Revision 1.3  2000/01/26 03:04:09  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 1.2  1999/12/18 00:35:38  mmiers
 * LOG: Continued tweaks.
 * LOG:
 * LOG: Revision 1.1  1999/12/17 21:50:48  mmiers
 * LOG:
 * LOG:
 * LOG: Rearrange, trying to get this right.
 * LOG:
 * LOG: Revision 2.1  1999/12/17 16:44:18  mmiers
 * LOG:
 * LOG:
 * LOG: New files.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_object.h>
#include <its_mutex.h>

#ident "$Id: its_features.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

extern ITS_Feature   ITS_FeatureListHead, ITS_FeatureListTail;

static ITS_Feature  staticListTail = NULL;

static ITS_MUTEX    featureMutex;
static ITS_BOOLEAN  singleThreaded = ITS_TRUE;

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This function allows thread safe feature manipulation.
 *
 *  Input Parameters:
 *      None.
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
 ************************************************************************/
int
ITS_FeatureStart()
{
    if (!singleThreaded)
    {
        return (ITS_SUCCESS);
    }

    if (MUTEX_CreateMutex(&featureMutex, 0) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    singleThreaded = ITS_FALSE;
    staticListTail = ITS_FeatureListTail;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This function terminates thread-safe feature manipulation
 *
 *  Input Parameters:
 *      None.
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
 ************************************************************************/
void
ITS_FeatureStop()
{
    if (singleThreaded)
    {
        return;
    }

    MUTEX_DeleteMutex(&featureMutex);

    singleThreaded = ITS_TRUE;
    staticListTail = NULL;
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This function initializes all registered IntelliSS7 features.
 *
 *  Input Parameters:
 *      None.
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
 ************************************************************************/
int
ITS_InitFeatures()
{
    ITS_Feature curFeature;
    int ret;

    for (curFeature = ITS_FeatureListHead;
         curFeature != NULL;
         curFeature = curFeature->next)
    {
        ITS_Class cl = curFeature->objClass;

        if (cl)
        {
            ret = ITS_InitializeClass(cl);

            if (ret != ITS_SUCCESS)
            {
                printf("feature '%s' failed to initialize: code %d\n",
                       ITS_CLASS_CLASSNAME(cl), ret);

                for (curFeature = curFeature->prev;
                     curFeature != NULL;
                     curFeature = curFeature->prev)
                {
                    if (cl)
                    {
                        ITS_DestroyClass(cl);
                    }
                }

                return (ret);
            }
        }

        if (curFeature == staticListTail)
        {
            break;
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This function destroys all IntelliSS7 features.
 *
 *  Input Parameters:
 *      None.
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
 ************************************************************************/
void
ITS_DestroyFeatures()
{
    ITS_Feature curFeature, tmp;

    for (curFeature = ITS_FeatureListTail;
         curFeature != NULL;
         curFeature = tmp)
    {
        ITS_Class cl = curFeature->objClass;

        tmp = curFeature->prev;

        if (cl)
        {
            ITS_DestroyClass(cl);
        }
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This function adds a new feature for GlobalStart() processing.
 *
 *  Input Parameters:
 *      newClass - the class feature to register
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
 ************************************************************************/
ITSDLLAPI int
ITS_AddFeature(ITS_Class newClass)
{
    ITS_Feature curFeature;

    if (!singleThreaded)
    {
        if (MUTEX_AcquireMutex(&featureMutex) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }
    }

    for (curFeature = ITS_FeatureListHead;
         curFeature != NULL;
         curFeature = curFeature->next)
    {
        if (curFeature->objClass &&
            curFeature->objClass->coreClass.className &&
            newClass &&
            newClass->coreClass.className &&
            strcmp(curFeature->objClass->coreClass.className,
                   newClass->coreClass.className) == 0)
        {
            if (!singleThreaded)
            {
                MUTEX_ReleaseMutex(&featureMutex);
            }

            return (ITS_EINUSE);
        }
    }

    if ((curFeature = (ITS_Feature)
                        calloc(1, sizeof(ITS_FeatureRec))) == NULL)
    {
        if (!singleThreaded)
        {
            MUTEX_ReleaseMutex(&featureMutex);
        }

        return (ITS_ENOMEM);
    }

    if (ITS_FeatureListHead == NULL)
    {
        ITS_FeatureListHead = curFeature;
    }

    curFeature->objClass = newClass;
    curFeature->prev = ITS_FeatureListTail;
    curFeature->next = NULL;

    if (ITS_FeatureListTail)
    {
        ITS_FeatureListTail->next = curFeature;
    }
    ITS_FeatureListTail = curFeature;

    if (!singleThreaded)
    {
        MUTEX_ReleaseMutex(&featureMutex);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This function adds a new feature for GlobalStart() processing.
 *
 *  Input Parameters:
 *      newClass - the class feature to register
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
 ************************************************************************/
ITSDLLAPI ITS_Class
ITS_FindFeature(const char *name)
{
    ITS_Feature curFeature;
    ITS_BOOLEAN match = ITS_FALSE;

    if (!singleThreaded)
    {
        if (MUTEX_AcquireMutex(&featureMutex) != ITS_SUCCESS)
        {
            return (NULL);
        }
    }

    for (curFeature = ITS_FeatureListHead;
         curFeature != NULL;
         curFeature = curFeature->next)
    {
        if (curFeature->objClass &&
            curFeature->objClass->coreClass.className &&
            strcmp(curFeature->objClass->coreClass.className, name) == 0)
        {
            match = ITS_TRUE;
            break;
        }
    }

    if (!singleThreaded)
    {
        MUTEX_ReleaseMutex(&featureMutex);
    }

    if (match)
    {
        return (curFeature->objClass);
    }

    return (NULL);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      This function removes a feature for GlobalStop() processing.
 *
 *  Input Parameters:
 *      newClass - the class feature to deregister
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
 ************************************************************************/
ITSDLLAPI void
ITS_RemFeature(ITS_Class newClass)
{
    ITS_Feature curFeature, tmp;

    if (!singleThreaded)
    {
        if (MUTEX_AcquireMutex(&featureMutex) != ITS_SUCCESS)
        {
            return;
        }
    }

    for (curFeature = ITS_FeatureListTail;
         curFeature != NULL;
         curFeature = tmp)
    {
        tmp = curFeature->prev;

        if (curFeature->objClass == newClass)
        {
            if (curFeature == ITS_FeatureListTail)
            {
                ITS_FeatureListTail = tmp;
            }

            if (curFeature->next)
            {
                curFeature->next->prev = curFeature->prev;
            }

            if (curFeature->prev)
            {
                curFeature->prev->next = curFeature->next;
            }

            free(curFeature);

            break;
        }
    }

    if (!singleThreaded)
    {
        MUTEX_ReleaseMutex(&featureMutex);
    }
}

