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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:00  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:43  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/06/21 22:49:09  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.4  2002/05/06 21:15:31  hdivoux
 * LOG: Cleanup after FT/HA integration.
 * LOG:
 * LOG: Revision 6.3  2002/04/16 21:20:30  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.2  2002/03/12 16:50:24  mmiers
 * LOG: Add user data.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:04  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.13  2002/02/13 23:26:54  mmiers
 * LOG: Typo fix.
 * LOG:
 * LOG: Revision 5.12  2002/02/12 23:30:08  mmiers
 * LOG: ISUP parser in place
 * LOG:
 * LOG: Revision 5.11  2001/12/18 22:49:44  mmiers
 * LOG: Add level names
 * LOG:
 * LOG: Revision 5.10  2001/11/08 16:16:11  mmiers
 * LOG: Make sure things compile without its_bc.h.  Fix MutexGuard.
 * LOG:
 * LOG: Revision 5.9  2001/10/19 22:45:12  mmiers
 * LOG: Use strings for variant names.
 * LOG:
 * LOG: Revision 5.8  2001/10/18 21:33:40  mmiers
 * LOG: Update engine to use destinations.
 * LOG:
 * LOG: Revision 5.7  2001/10/17 00:56:57  mmiers
 * LOG: Remove SLS stuff from engine.
 * LOG:
 * LOG: Revision 5.6  2001/10/02 21:44:25  mmiers
 * LOG: dead route style removal
 * LOG:
 * LOG: Revision 5.5  2001/09/24 21:37:37  mmiers
 * LOG: ENGINE link, linkSet, C++ API.
 * LOG:
 * LOG: Revision 5.4  2001/09/21 16:22:44  hdivoux
 * LOG: Update for comments and const parameters.
 * LOG:
 * LOG: Revision 5.3  2001/08/20 23:28:54  mmiers
 * LOG: Finish route work.
 * LOG:
 * LOG: Revision 5.2  2001/08/20 22:57:21  mmiers
 * LOG: Change to new routing scheme
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.10  2001/07/26 19:04:14  mmiers
 * LOG: Add engine thread pool type for pattern matcher.
 * LOG:
 * LOG: Revision 4.9  2001/07/25 23:41:26  mmiers
 * LOG: Diff's about done.
 * LOG:
 * LOG: Revision 4.8  2001/07/05 22:48:00  mmiers
 * LOG: Update for DMA.  Need to finish timers.
 * LOG:
 * LOG: Revision 4.7  2001/06/22 21:01:06  mmiers
 * LOG: Finish integrating DSM and RM.  Need to add PeerDead notification
 * LOG: to complete.
 * LOG:
 * LOG: Revision 4.6  2001/06/21 15:18:37  mmiers
 * LOG: Add HMI and Alarm.
 * LOG:
 * LOG: Revision 4.5  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.4  2001/06/15 00:21:43  mmiers
 * LOG: Add class for engine worker.
 * LOG:
 * LOG: Revision 4.3  2001/05/10 16:41:12  mmiers
 * LOG: The rest of the requests.
 * LOG:
 * LOG: Revision 4.2  2001/05/09 23:20:17  mmiers
 * LOG: Name change by request.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/04/25 20:11:48  mmiers
 * LOG: Avoid member hiding.
 * LOG:
 * LOG: Revision 3.6  2001/04/11 01:04:22  mmiers
 * LOG: Rename it for consistency.
 * LOG:
 * LOG: Revision 3.5  2001/04/11 00:48:58  mmiers
 * LOG: Add a little documentation.
 * LOG:
 * LOG: Revision 3.4  2001/04/11 00:45:11  mmiers
 * LOG: Move the EngineWorker class so that users can see it.
 * LOG:
 * LOG: Revision 3.3  2001/04/06 21:10:38  mmiers
 * LOG: Finish the CPP API.
 * LOG:
 * LOG: Revision 3.2  2001/04/06 17:48:58  mmiers
 * LOG: Updates.
 * LOG:
 * LOG: Revision 3.1  2001/04/05 23:07:00  mmiers
 * LOG: Debugging C++ API.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_ENGINE_PP_H_)
#define _ENGINE_PP_H_

#include <its++.h>
#include <engine.h>

#ident "$Id: engine++.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#include <string>
#include <vector>

#if defined(ITS_NAMESPACE)
namespace engine
{
#endif

/*
 * CPP objects to wrapper the C objects.
 *
 * The discerning user will note that the C objects are not destroyed.
 * This is intentional behavior (the engine will free them as needed).
 *
 * The same thing applies to any locally allocated memory.
 */

/*
 * Application class
 */
class Application
{
public:
    /* constructor */
    Application(bool isService, bool cppBinding, ITS_UINT gsMask,
                const char *libName,
                const char *ss7Select, const char *appSelect,
                const char *hmi, const char *alarm,
                const char *preFunc, const char *postFunc)
    {
        Initialize(isService, cppBinding, gsMask, libName,
                   ss7Select, appSelect, hmi, alarm,
                   preFunc, postFunc);
    }
    
    /* constructor */
    Application(bool isService, bool cppBinding, ITS_UINT gsMask,
                const std::string& libName,
                const std::string& ss7Select, const std::string& appSelect,
                const std::string& hmi, const std::string& alarm,
                const std::string& preFunc, const std::string& postFunc)
    {
        Initialize(isService, cppBinding, gsMask, libName.c_str(),
                   ss7Select.c_str(), appSelect.c_str(),
                   hmi.c_str(), alarm.c_str(),
                   preFunc.c_str(), postFunc.c_str());
    }

    ENGINE_Application&
    GetApplication()
    {
        return app;
    }

    ITS_Object&
    GetAppTrance()
    {
        return ENGINE_APP_TRACE_LEVELS(app);
    }
    ITS_Object&
    GetSupportTrace()
    {
        return ENGINE_APP_SUPPORT_LEVELS(app);
    }

    void
    SetOptions(const char **options, int numOptions)
    {
        char **localOpts;

        localOpts = (char **)malloc(sizeof(char *) * numOptions);
        ITS_THROW_ASSERT(localOpts != NULL);

        for (int i = 0; i < numOptions; i++)
        {
            localOpts[i] = strdup(options[i]);

            ITS_THROW_ASSERT(localOpts[i] != NULL);
        }

        ENGINE_APP_OPTIONS(app) = localOpts;
        ENGINE_APP_NUM_OPTIONS(app) = numOptions;
    }
    void
    SetOptions(const std::vector<std::string>& options)
    {
        char **localOpts;

        localOpts = (char **)malloc(sizeof(char *) * options.size());
        ITS_THROW_ASSERT(localOpts != NULL);

        for (unsigned i = 0; i < options.size(); i++)
        {
            localOpts[i] = strdup(options[i].c_str());

            ITS_THROW_ASSERT(localOpts[i] != NULL);
        }

        ENGINE_APP_OPTIONS(app) = localOpts;
        ENGINE_APP_NUM_OPTIONS(app) = options.size();
    }


private:
    void
    Initialize(bool isService, bool cppBinding, ITS_UINT gsMask,
               const char *libName,
               const char *ss7Select, const char *appSelect,
               const char *hmi, const char *alarm,
               const char *preFunc, const char *postFunc)
    {
        app = (ENGINE_Application)
            ITS_ConstructObject(itsENGINE_ApplicationClass,
                                isService ? ITS_TRUE : ITS_FALSE,
                                cppBinding ? ITS_TRUE : ITS_FALSE,
                                gsMask, libName,
                                ss7Select, appSelect,
                                hmi, alarm,
                                preFunc, postFunc);

        ITS_THROW_ASSERT(app != NULL);
    }

    ENGINE_Application  app;
};

/*
 * DLL cache records
 */
class LibCache
{
public:
    /* constructor */
    LibCache(Application *app, const char *libName)
    {
        Initialize(app->GetApplication(), libName);
    }

    /* constructor */
    LibCache(Application *app, const std::string& libName)
    {
        Initialize(app->GetApplication(), libName.c_str());
    }

private:
    void
    Initialize(ENGINE_Application app, const char *libName)
    {
        lc = (ENGINE_LibCache)
            ITS_ConstructObject(itsENGINE_LibCacheClass,
                                app, libName);

        ITS_THROW_ASSERT(lc != NULL);
    }

    ENGINE_LibCache lc;
};

/*
 * parser extension records
 */
class ParserExtension
{
public:
    ParserExtension(Application *app,
                    const char *libName, const char *elemName,
                    const char *startFunc, const char *stopFunc,
                    const char *xlateFunc)
    {
        ITS_Object ret;

        ret = ITS_ConstructObject(itsENGINE_ParserExtensionClass, app,
                                  libName, elemName,
                                  startFunc, stopFunc, xlateFunc);

        ITS_ASSERT(ret != NULL);
    }
    ParserExtension(Application *app,
                    const std::string& libName, const std::string& elemName,
                    const std::string& startFunc, const std::string& stopFunc,
                    const std::string& xlateFunc)
    {
        ITS_Object ret;

        ret = ITS_ConstructObject(itsENGINE_ParserExtensionClass, app,
                                  libName.c_str(), elemName.c_str(),
                                  startFunc.c_str(), stopFunc.c_str(),
                                  xlateFunc.c_str());

        ITS_ASSERT(ret != NULL);
    }
};

/*
 * feature records
 */
class Feature
{
public:
    /* constructor */
    Feature(Application *app,
            const char *featureName, const char *libName,
            const char *className,
            const char **options, unsigned numOptions)
    {
        const char **localOpts;

        localOpts = (const char **)malloc(sizeof(char *) * numOptions);
        ITS_THROW_ASSERT(localOpts != NULL);

        for (unsigned i = 0; i < numOptions; i++)
        {
            localOpts[i] = strdup(options[i]);

            ITS_THROW_ASSERT(localOpts[i] != NULL);
        }

        Initialize(app->GetApplication(), featureName, libName,
                   className, localOpts, numOptions);
    }

    /* constructor */
    Feature(Application *app,
            const std::string& featureName, const std::string& libName,
            const std::string& className, 
            const std::vector<std::string>& options)
    {
        const char **localOpts;

        localOpts = (const char **)malloc(sizeof(char *) * options.size());
        ITS_THROW_ASSERT(localOpts != NULL);

        unsigned i;
        for (i = 0; i < options.size(); i++)
        {
            localOpts[i] = strdup(options[i].c_str());

            ITS_THROW_ASSERT(localOpts[i] != NULL);
        }

        Initialize(app->GetApplication(),
                   featureName.c_str(), libName.c_str(),
                   className.c_str(), localOpts, i);
    }

private:
    void
    Initialize(ENGINE_Application app,
               const char *featureName, const char *libName,
               const char *className,
               const char **options, unsigned numOptions)
    {
        feat = (ENGINE_Feature)
            ITS_ConstructObject(itsENGINE_FeatureClass,
                                featureName, libName, className,
                                options, numOptions);

        ITS_THROW_ASSERT(feat != NULL);
    }

    ENGINE_Feature feat;
};

/*
 * trace levels
 */
class TraceLevel
{
public:
    /* constructor */
    TraceLevel(ITS_Object *list, const char *levelName, int levelMask)
    {
        Initialize(list, levelName, levelMask);
    }

    /* constructor */
    TraceLevel(ITS_Object *list, std::string levelName, int levelMask)
    {
        Initialize(list, levelName.c_str(), levelMask);
    }

private:
    void
    Initialize(ITS_Object *list, const char *levelName, int levelMask)
    {
        lev = (ENGINE_Trace)
            ITS_ConstructObject(itsENGINE_TraceClass, list,
                                levelName, levelMask);

        ITS_THROW_ASSERT(lev != NULL);
    }

    ENGINE_Trace lev;
};

/*
 * routes and specializations (this may not work)
 */
class Route
{
public:
    /* constructor */
    Route(ITS_Object* listParam, ITS_UINT pointCodeParam,
          ROUTE_TYPE typeParam, SS7_Family familyParam,
          ITS_OCTET linkSetParam,
          ITS_OCTET priorityParam = ITS_SS7_DEFAULT_PRI)
        : list(listParam),
          pointCode(pointCodeParam),
          type(typeParam),
          family(familyParam),
          linkSet(linkSetParam),
          priority(priorityParam)
    {
    }

protected:
    ENGINE_Route rt;
    ITS_Object *list;
    ITS_UINT pointCode;
    ROUTE_TYPE type;
    SS7_Family family;
    ROUTE_CRITERIA style;
    ITS_OCTET linkSet;
    ITS_OCTET priority;
};

class RouteDPC_NI : public Route
{
public:
    /* constructor */
    RouteDPC_NI(ITS_Object *_list, ITS_UINT _pointCode,
                ROUTE_TYPE _type, SS7_Family _family, ITS_OCTET ni,
                ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_SIO, _family, ni,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_SIO : public Route
{
public:
    /* constructor */
    RouteDPC_SIO(ITS_Object *_list, ITS_UINT _pointCode,
                 ROUTE_TYPE _type, SS7_Family _family, ITS_OCTET sio,
                 ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_SIO, _family, sio,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_SIO_SSN : public Route
{
public:
    /* constructor */
    RouteDPC_SIO_SSN(ITS_Object *_list, ITS_UINT _pointCode,
                     ROUTE_TYPE _type, SS7_Family _family,
                     ITS_OCTET sio, ITS_OCTET ssn,
                     ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_SIO_SSN, _family, sio, ssn,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_SIO_CIC : public Route
{
public:
    /* constructor */
    RouteDPC_SIO_CIC(ITS_Object *_list, ITS_UINT _pointCode,
                     ROUTE_TYPE _type, SS7_Family _family,
                     ITS_OCTET sio, ITS_USHORT cic,
                     ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_SIO_CIC, _family, sio, cic,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_SIO_SSN_Range : public Route
{
public:
    /* constructor */
    RouteDPC_SIO_SSN_Range(ITS_Object *_list, ITS_UINT _pointCode,
                           ROUTE_TYPE _type, SS7_Family _family,
                           ITS_OCTET sio,
                           ITS_OCTET begin, ITS_OCTET end,
                           ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_SIO_SSN_RANGE, _family,
                                sio, begin, end,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_SIO_CIC_Range : public Route
{
public:
    /* constructor */
    RouteDPC_SIO_CIC_Range(ITS_Object *_list, ITS_UINT _pointCode,
                           ROUTE_TYPE _type, SS7_Family _family,
                           ITS_OCTET sio,
                           ITS_USHORT begin, ITS_USHORT end,
                           ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_SIO_SSN_RANGE, _family,
                                sio, begin, end,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_OPC_NI : public Route
{
public:
    /* constructor */
    RouteDPC_OPC_NI(ITS_Object *_list, ITS_UINT _pointCode,
                    ROUTE_TYPE _type, SS7_Family _family,
                    ITS_UINT opc, ITS_OCTET ni,
                    ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_OPC_NI, _family,
                                opc, ni,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_OPC_SIO : public Route
{
public:
    /* constructor */
    RouteDPC_OPC_SIO(ITS_Object *_list, ITS_UINT _pointCode,
                     ROUTE_TYPE _type, SS7_Family _family,
                     ITS_UINT opc, ITS_OCTET sio,
                     ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_OPC_SIO, _family,
                                opc, sio,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_OPC_SIO_SSN : public Route
{
public:
    /* constructor */
    RouteDPC_OPC_SIO_SSN(ITS_Object *_list, ITS_UINT _pointCode,
                         ROUTE_TYPE _type, SS7_Family _family,
                         ITS_UINT opc, ITS_OCTET sio,
                         ITS_OCTET ssn,
                         ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_OPC_SIO_SSN, _family,
                                opc, sio, ssn,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_OPC_SIO_CIC : public Route
{
public:
    /* constructor */
    RouteDPC_OPC_SIO_CIC(ITS_Object *_list, ITS_UINT _pointCode,
                         ROUTE_TYPE _type, SS7_Family _family, 
                         ITS_UINT opc, ITS_OCTET sio,
                         ITS_USHORT cic,
                         ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_OPC_SIO_CIC, _family,
                                opc, sio, cic,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_OPC_SIO_SSN_Range : public Route
{
public:
    /* constructor */
    RouteDPC_OPC_SIO_SSN_Range(ITS_Object *_list, ITS_UINT _pointCode,
                               ROUTE_TYPE _type, SS7_Family _family,
                               ITS_UINT opc, ITS_OCTET sio,
                               ITS_OCTET begin, ITS_OCTET end,
                               ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_OPC_SIO_SSN_RANGE, _family,
                                opc, sio,
                                begin, end,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

class RouteDPC_OPC_SIO_CIC_Range : public Route
{
public:
    /* constructor */
    RouteDPC_OPC_SIO_CIC_Range(ITS_Object *_list, ITS_UINT _pointCode,
                               ROUTE_TYPE _type, SS7_Family _family,
                               ITS_UINT opc, ITS_OCTET sio,
                               ITS_USHORT begin, ITS_USHORT end,
                               ITS_OCTET _linkSet, ITS_OCTET _priority)
        : Route(_list, _pointCode, _type, _family, _linkSet, _priority)
    {
        rt = (ENGINE_Route)
            ITS_ConstructObject(itsENGINE_RouteClass, _list, _pointCode,
                                _type, ROUTE_DPC_OPC_SIO_SSN_RANGE, opc, sio,
                                begin, end,
                                _linkSet, ITS_SS7_DEFAULT_LINK_CODE,
                                _priority, 0);

        ITS_THROW_ASSERT(rt != NULL);
    }
};

/*
 * destination class
 */
class Destination
{
public:
    Destination(Application *app, ITS_UINT pc,
                ITS_OCTET ni, SS7_Family _family,
                ITS_INT mtp3Var, ITS_INT isupVar,
                ITS_INT sccpVar, ITS_INT tcapVar,
                ITS_INT tupVar, ITS_INT dupVar)
    {
        ds = (ENGINE_Dest)
            ITS_ConstructObject(itsENGINE_DestClass, app,
                                pc, ni, _family,
                                mtp3Var, isupVar, sccpVar, tcapVar,
                                tupVar, dupVar);

        ITS_THROW_ASSERT(ds != NULL);
    }

private:
    ENGINE_Dest  ds;
};

/*
 * ISUP Attributes
 */
class ISUPAttributes
{
public:
    ISUPAttributes(Application *app, Destination *dest,
                   ITS_UINT localPC, ITS_OCTET sio,
                   const char *className, const char *library)
    {
        ia = (ENGINE_ISUPAttr)
            ITS_ConstructObject(itsENGINE_ISUPAttrClass,
                                app, dest, localPC, sio,
                                className, library);

        ITS_THROW_ASSERT(ia != NULL);
    }

private:
    ENGINE_ISUPAttr ia;
};

/*
 * Circuit group
 */
class CircuitGroup
{
public:
    CircuitGroup(ISUPAttributes *attr, const char *huntRule)
    {
        cg = (ENGINE_CircuitGroup)
            ITS_ConstructObject(itsENGINE_CircuitGroupClass,
                                attr, huntRule);

        ITS_THROW_ASSERT(cg != NULL);
    }

private:
    ENGINE_CircuitGroup cg;
};

/*
 * Circuit codes
 */
class CircuitCodes
{
public:
    CircuitCodes(CircuitGroup *group, ITS_UINT start, ITS_UINT count)
    {
        cc = (ENGINE_CICs)
            ITS_ConstructObject(itsENGINE_CICsClass,
                                group, start, count);

        ITS_THROW_ASSERT(cc != NULL);
    }

private:
    ENGINE_CICs cc;
};

/*
 * ISUP timer
 */
class ISUPTimer
{
public:
    ISUPTimer(ISUPAttributes *attr, const char *name,
              const char *value, const char *handler)
    {
        it = (ENGINE_ISUPTimer)
            ITS_ConstructObject(itsENGINE_ISUPTimerClass,
                                attr, name, value, handler);

        ITS_THROW_ASSERT(it != NULL);
    }

private:
    ENGINE_ISUPTimer it;
};

/*
 * link set class
 */
class LinkSet
{
public:
    LinkSet(Application *app, ITS_UINT adjacent, ITS_OCTET id,
            ITS_OCTET ni, ITS_UINT numToStart, bool adjacentSTP,
            bool isCLinkSet, bool is5Bit, SS7_Family _family)
    {
        ls = (ENGINE_LinkSet)
            ITS_ConstructObject(itsENGINE_LinkSetClass, app, adjacent,
                                 id, ni, numToStart,
                                 adjacentSTP ? ITS_TRUE : ITS_FALSE,
                                 isCLinkSet ? ITS_TRUE : ITS_FALSE,
                                 is5Bit ? ITS_TRUE : ITS_FALSE,
                                 _family);

        ITS_THROW_ASSERT(ls != NULL);
    }

private:
    ENGINE_LinkSet  ls;
};

/*
 * link class
 */
class Link
{
public:
    Link(ITS_Object *_list,
         ITS_OCTET linkSet, ITS_OCTET linkCode, ITS_OCTET linkPri,
         bool initActive, bool termFixed, bool linkFixed,
         ITS_USHORT terminal, ITS_USHORT circuit, bool isSAAL,
         bool isLocal, SS7_Family _family)
    {
        ln = (ENGINE_Link)
            ITS_ConstructObject(itsENGINE_LinkClass,
                                _list, linkSet, linkCode, linkPri,
                                initActive ? ITS_TRUE : ITS_FALSE,
                                termFixed ? ITS_TRUE : ITS_FALSE,
                                linkFixed ? ITS_TRUE : ITS_FALSE,
                                terminal, circuit,
                                isSAAL ? ITS_TRUE : ITS_FALSE,
                                isLocal ? ITS_TRUE : ITS_FALSE,
                                _family);

        ITS_THROW_ASSERT(ln != NULL);
    }

private:
    ENGINE_Link ln;
};

/*
 * thread pool class
 */
class ThreadPool
{
public:
    ThreadPool(Application *app, int stackSize, ENGINE_ThreadPoolType type)
    {
        tp = (ENGINE_ThreadPool)
            ITS_ConstructObject(itsENGINE_ThreadPoolClass,
                                app->GetApplication(),
                                stackSize, type);

        ITS_THROW_ASSERT(tp != NULL);
    }

    ENGINE_ThreadPool&
    GetThreadPool()
    {
        return tp;
    }

private:
    ENGINE_ThreadPool tp;
};

/*
 * transport callbacks
 */
class TransportCallbacks
{
public:
    /* constructor */
    TransportCallbacks(Application *app, const char *libName, bool isSS7,
                       DISP_HandlerType handlerType, DISP_Type blockType,
                       const char *preInit, const char *postInit,
                       const char *preNext, const char *nextFail,
                       const char *postNext,
                       const char *dispUser, const char *dispISUP,
                       const char *dispSCCP,
                       const char *onAccept,
                       const char *preTerm, const char *postTerm,
                       DISP_HandlerType acceptType)
    {
        tc = (ENGINE_TransportCallbacks)
            ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                libName, isSS7 ? ITS_TRUE : ITS_FALSE,
                                handlerType, blockType,
                                preInit, postInit,
                                preNext, nextFail, postNext,
                                dispUser, dispISUP, dispSCCP,
                                onAccept,
                                preTerm, postTerm,
                                acceptType);

        ITS_THROW_ASSERT(tc != NULL);
    }

    /* constructor */
    TransportCallbacks(Application *app, const std::string& libName, 
                       bool isSS7, DISP_HandlerType handlerType, 
                       DISP_Type blockType,
                       const std::string& preInit, 
                       const std::string& postInit,
                       const std::string& preNext, 
                       const std::string& nextFail,
                       const std::string& postNext,
                       const std::string& dispUser, 
                       const std::string& dispISUP,
                       const std::string& dispSCCP,
                       const std::string& onAccept,
                       const std::string& preTerm, 
                       const std::string& postTerm,
                       DISP_HandlerType acceptType)
    {
        tc = (ENGINE_TransportCallbacks)
            ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                libName.c_str(), isSS7 ? ITS_TRUE : ITS_FALSE,
                                handlerType, blockType,
                                preInit.c_str(), postInit.c_str(),
                                preNext.c_str(), nextFail.c_str(),
                                postNext.c_str(),
                                dispUser.c_str(), dispISUP.c_str(),
                                dispSCCP.c_str(),
                                onAccept.c_str(),
                                preTerm.c_str(), postTerm.c_str(),
                                acceptType);

        ITS_THROW_ASSERT(tc != NULL);
    }

    ENGINE_TransportCallbacks&
    GetCallbacks()
    {
        return tc;
    }

private:
    ENGINE_TransportCallbacks tc;
};

/*
 * transport specifics
 */
class TransportSpecifics
{
public:
    TransportSpecifics(ITS_UINT maskParam)
        : mask(maskParam),
          specs(NULL)
    {
    }

    ENGINE_TransportSpecifics&
    GetSpecs()
    {
        return specs;
    }

protected:
    ITS_UINT mask;
    ENGINE_TransportSpecifics specs;
};

class FIFOSpecs : public TransportSpecifics
{
public:
    /* constructor */
    FIFOSpecs(ITS_UINT _mask,
              const char *clientPath, const char *serverPath)
        : TransportSpecifics(_mask)
    {
        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, clientPath, serverPath);

        ITS_THROW_ASSERT(specs != NULL);
    }

    /* constructor */
    FIFOSpecs(ITS_UINT _mask,
              const std::string& clientPath, const std::string& serverPath)
        : TransportSpecifics(_mask)
    {
        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask,
                                clientPath.c_str(),
                                serverPath.c_str());

        ITS_THROW_ASSERT(specs != NULL);
    }
};

class SS7Specs : public TransportSpecifics
{
public:
    /* constructor */
    SS7Specs(ITS_UINT _mask,
             const char *vendorLib, const char *vendorClass)
        : TransportSpecifics(_mask)
    {
        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, vendorLib, vendorClass);

        ITS_THROW_ASSERT(specs != NULL);
    }

    /* constructor */
    SS7Specs(ITS_UINT _mask,
             const std::string& vendorLib, const std::string& vendorClass)
        : TransportSpecifics(_mask)
    {
        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask,
                                vendorLib.c_str(),
                                vendorClass.c_str());

        ITS_THROW_ASSERT(specs != NULL);
    }
};

class TCPSpecs : public TransportSpecifics
{
public:
    /* constructor */
    TCPSpecs(ITS_UINT _mask, ITS_SOCK_DOMAIN domain,
             const char *serverPath, ITS_USHORT serverPort,
             int retryDelay = DEFAULT_RETRY_DELAY,
             int retryCount = DEFAULT_RETRY_COUNT)
        : TransportSpecifics(_mask)
    {
        const char *d = domain == INET_DOMAIN
                            ? DOMAIN_INET_STRING
                            : DOMAIN_UNIX_STRING;
        char p[16], del[16], cnt[16];

        sprintf(p, "%d", serverPort);
        sprintf(del, "%d", retryDelay);
        sprintf(cnt, "%d", retryCount);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, d, serverPath, p, del, cnt);

        ITS_THROW_ASSERT(specs != NULL);
    }

    /* constructor */
    TCPSpecs(ITS_UINT _mask, ITS_SOCK_DOMAIN domain,
             const std::string& serverPath, ITS_USHORT serverPort,
             int retryDelay = DEFAULT_RETRY_DELAY,
             int retryCount = DEFAULT_RETRY_COUNT)
        : TransportSpecifics(_mask)
    {
        const char *d = domain == INET_DOMAIN
                            ? DOMAIN_INET_STRING
                            : DOMAIN_UNIX_STRING;
        char p[16], del[16], cnt[16];

        sprintf(p, "%d", serverPort);
        sprintf(del, "%d", retryDelay);
        sprintf(cnt, "%d", retryCount);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, d, serverPath.c_str(), p, del, cnt);

        ITS_THROW_ASSERT(specs != NULL);
    }
};

class UDPSpecs : public TransportSpecifics
{
public:
    /* constructor */
    UDPSpecs(ITS_UINT _mask,
             const char *localPath, ITS_USHORT localPort,
             const char **associates, int numAssociates)
        : TransportSpecifics(_mask)
    {
        char p[16];
        char **assoc;

        assoc = (char **)malloc(sizeof(char *) * numAssociates);
        ITS_THROW_ASSERT(assoc != NULL);

        for (int i = 0; i < numAssociates; i++)
        {
            assoc[i] = strdup(associates[i]);

            ITS_THROW_ASSERT(assoc[i] != NULL);
        }

        sprintf(p, "%d", localPort);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, localPath, p,
                                assoc, numAssociates);

        ITS_THROW_ASSERT(specs != NULL);
    }

    /* constructor */
    UDPSpecs(ITS_UINT _mask,
             const std::string& localPath, ITS_USHORT localPort,
             const std::vector<std::string>& associates)
        : TransportSpecifics(_mask)
    {
        char p[16];
        char **assoc;

        assoc = (char **)malloc(sizeof(char *) * associates.size());
        ITS_THROW_ASSERT(assoc != NULL);

        for (unsigned i = 0; i < associates.size(); i++)
        {
            assoc[i] = strdup(associates[i].c_str());

            ITS_THROW_ASSERT(assoc[i] != NULL);
        }

        sprintf(p, "%d", localPort);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, localPath.c_str(), p,
                                assoc, associates.size());

        ITS_THROW_ASSERT(specs != NULL);
    }
};

class GDISpecs : public TransportSpecifics
{
public:
    /* constructor */
    GDISpecs(ITS_UINT _mask, ITS_SOCK_DOMAIN domain,
             const char *serverPath, ITS_USHORT serverPort,
             ITS_UINT localPC, ITS_UINT remotePC, ITS_OCTET remoteSSN,
             int retryDelay = DEFAULT_RETRY_DELAY,
             int retryCount = DEFAULT_RETRY_COUNT)
        : TransportSpecifics(_mask)
    {
        const char *d = domain == INET_DOMAIN
                            ? DOMAIN_INET_STRING
                            : DOMAIN_UNIX_STRING;
        char p[16], del[16], cnt[16];
        char l[16], r[16], s[16];

        sprintf(p, "%d", serverPort);
        sprintf(del, "%d", retryDelay);
        sprintf(cnt, "%d", retryCount);
        sprintf(l, "0x%08x", localPC);
        sprintf(r, "0x%08x", remotePC);
        sprintf(s, "%d", remoteSSN);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, d, serverPath, p, del, cnt,
                                l, r, s);

        ITS_THROW_ASSERT(specs != NULL);
    }

    /* constructor */
    GDISpecs(ITS_UINT _mask, ITS_SOCK_DOMAIN domain,
             const std::string& serverPath, ITS_USHORT serverPort,
             ITS_UINT localPC, ITS_UINT remotePC, ITS_OCTET remoteSSN,
             int retryDelay = DEFAULT_RETRY_DELAY,
             int retryCount = DEFAULT_RETRY_COUNT)
        : TransportSpecifics(_mask)
    {
        const char *d = domain == INET_DOMAIN
                            ? DOMAIN_INET_STRING
                            : DOMAIN_UNIX_STRING;
        char p[16], del[16], cnt[16];
        char l[16], r[16], s[16];

        sprintf(p, "%d", serverPort);
        sprintf(del, "%d", retryDelay);
        sprintf(cnt, "%d", retryCount);
        sprintf(l, "0x%08x", localPC);
        sprintf(r, "0x%08x", remotePC);
        sprintf(s, "%d", remoteSSN);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, d, serverPath.c_str(), p, del, cnt,
                                l, r, s);

        ITS_THROW_ASSERT(specs != NULL);
    }
};

class IMALSpecs : public TransportSpecifics
{
public:
    /* constructor */
    IMALSpecs(ITS_UINT _mask, ITS_SOCK_DOMAIN domain,
             const char *serverPath, ITS_USHORT serverPort,
             ITS_UINT localPC, ITS_UINT adjPC, ITS_UINT timeOut,
             int retryDelay = DEFAULT_RETRY_DELAY,
             int retryCount = DEFAULT_RETRY_COUNT)
        : TransportSpecifics(_mask)
    {
        const char *d = domain == INET_DOMAIN
                            ? DOMAIN_INET_STRING
                            : DOMAIN_UNIX_STRING;
        char p[16], del[16], cnt[16];
        char l[16], r[16], s[16];

        sprintf(p, "%d", serverPort);
        sprintf(del, "%d", retryDelay);
        sprintf(cnt, "%d", retryCount);
        sprintf(l, "0x%08x", localPC);
        sprintf(r, "0x%08x", adjPC);
        sprintf(s, "%d", timeOut);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, d, serverPath, p, del, cnt,
                                l, r, s);

        ITS_THROW_ASSERT(specs != NULL);
    }

    /* constructor */
    IMALSpecs(ITS_UINT _mask, ITS_SOCK_DOMAIN domain,
              const std::string& serverPath, ITS_USHORT serverPort,
              ITS_UINT localPC, ITS_UINT adjPC, ITS_OCTET timeOut,
              int retryDelay = DEFAULT_RETRY_DELAY,
              int retryCount = DEFAULT_RETRY_COUNT)
        : TransportSpecifics(_mask)
    {
        const char *d = domain == INET_DOMAIN
                            ? DOMAIN_INET_STRING
                            : DOMAIN_UNIX_STRING;
        char p[16], del[16], cnt[16];
        char l[16], r[16], s[16];

        sprintf(p, "%d", serverPort);
        sprintf(del, "%d", retryDelay);
        sprintf(cnt, "%d", retryCount);
        sprintf(l, "0x%08x", localPC);
        sprintf(r, "0x%08x", adjPC);
        sprintf(s, "%d", timeOut);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, d, serverPath.c_str(), p, del, cnt,
                                l, r, s);

        ITS_THROW_ASSERT(specs != NULL);
    }
};

class TALISpecs : public TransportSpecifics
{
public:
    /* constructor */
    TALISpecs(ITS_UINT _mask, ITS_SOCK_DOMAIN domain,
              const char *serverPath, ITS_USHORT serverPort,
              ITS_UINT localPC, ITS_UINT adjPC,
              bool allowed, bool upper,
              int retryDelay = DEFAULT_RETRY_DELAY,
              int retryCount = DEFAULT_RETRY_COUNT)
        : TransportSpecifics(_mask)
    {
        const char *d = domain == INET_DOMAIN
                            ? DOMAIN_INET_STRING
                            : DOMAIN_UNIX_STRING;
        char p[16], del[16], cnt[16];
        char l[16], r[16], s[16], a[16];

        sprintf(p, "%d", serverPort);
        sprintf(del, "%d", retryDelay);
        sprintf(cnt, "%d", retryCount);
        sprintf(l, "0x%08x", localPC);
        sprintf(a, "0x%08x", adjPC);
        sprintf(r, "%s", allowed ? "yes" : "no");
        sprintf(s, "%s", upper ? "yes" : "no");

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, d, serverPath, p, del, cnt,
                                l, a, r, s);

        ITS_THROW_ASSERT(specs != NULL);
    }

    /* constructor */
    TALISpecs(ITS_UINT _mask, ITS_SOCK_DOMAIN domain,
              const std::string& serverPath, ITS_USHORT serverPort,
              ITS_UINT localPC, ITS_UINT adjPC,
              bool allowed, bool upper,
              int retryDelay = DEFAULT_RETRY_DELAY,
              int retryCount = DEFAULT_RETRY_COUNT)
        : TransportSpecifics(_mask)
    {
        const char *d = domain == INET_DOMAIN
                            ? DOMAIN_INET_STRING
                            : DOMAIN_UNIX_STRING;
        char p[16], del[16], cnt[16];
        char l[16], r[16], s[16], a[16];

        sprintf(p, "%d", serverPort);
        sprintf(del, "%d", retryDelay);
        sprintf(cnt, "%d", retryCount);
        sprintf(l, "0x%08x", localPC);
        sprintf(a, "0x%08x", adjPC);
        sprintf(r, "%s", allowed ? "yes" : "no");
        sprintf(s, "%s", upper ? "yes" : "no");

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, d, serverPath.c_str(), p, del, cnt,
                                l, a, r, s);

        ITS_THROW_ASSERT(specs != NULL);
    }
};

class SCTPSpecs : public TransportSpecifics
{
public:
    /* constructor */
    SCTPSpecs(ITS_UINT _mask,
              const char *localPath, ITS_USHORT localPort,
              const char **associates, int numAssociates,
              const char **extraHomes, int numExtraHomes,
              const char *payloadType,
              ITS_UINT maxInStreams = 256, ITS_UINT numOutStreams = 256,
              ITS_UINT maxAttempts = 5, ITS_UINT cookieLife = 5,
              bool hbOn = true, bool isClient = false,
              ITS_UINT initSecs = 3, ITS_UINT initUSecs = 0,
              ITS_UINT sendSecs = 3, ITS_UINT sendUSecs = 0,
              ITS_UINT recvSecs = 0, ITS_UINT recvUSecs = 200000,
              ITS_UINT hbSecs = 3, ITS_UINT hbUSecs = 0,
              ITS_UINT shutSecs = 0, ITS_UINT shutUSecs = 300000,
              ITS_UINT pmtuSecs = 600, ITS_UINT pmtuUSecs = 0)
        : TransportSpecifics(_mask)
    {
        char p[16];
        char **assoc, **homes;
        char out[16], in[16], at[16], cl[16], hb[16];
        char n[24], s[24], r[24], h[24], u[24], m[24];

        assoc = (char **)malloc(sizeof(char *) * numAssociates);
        ITS_THROW_ASSERT(assoc != NULL);

        int i;
        for (i = 0; i < numAssociates; i++)
        {
            assoc[i] = strdup(associates[i]);

            ITS_THROW_ASSERT(assoc[i] != NULL);
        }

        homes = (char **)malloc(sizeof(char *) * numExtraHomes);
        ITS_THROW_ASSERT(assoc != NULL);

        for (i = 0; i < numExtraHomes; i++)
        {
            assoc[i] = strdup(extraHomes[i]);

            ITS_THROW_ASSERT(homes[i] != NULL);
        }

        sprintf(p, "%d", localPort);
        sprintf(out, "%d", maxInStreams);
        sprintf(in, "%d", numOutStreams);
        sprintf(at, "%d", maxAttempts);
        sprintf(cl, "%d", cookieLife);
        sprintf(hb, "%d", hbOn);
        sprintf(n, "%d,%d", initSecs, initUSecs);
        sprintf(s, "%d,%d", sendSecs, sendUSecs);
        sprintf(r, "%d,%d", recvSecs, recvUSecs);
        sprintf(h, "%d,%d", hbSecs, hbUSecs);
        sprintf(u, "%d,%d", shutSecs, shutUSecs);
        sprintf(m, "%d,%d", pmtuSecs, pmtuUSecs);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, localPath, p,
                                assoc, numAssociates,
                                homes, numExtraHomes,
                                out, in, at, cl, hb,
                                i, s, r, h, u, m,
                                isClient ? "yes" : "no",
                                payloadType);

        ITS_THROW_ASSERT(specs != NULL);
    }

    /* constructor */
    SCTPSpecs(ITS_UINT _mask,
              const std::string& localPath, ITS_USHORT localPort,
              const std::vector<std::string>& associates,
              const std::vector<std::string>& extraHomes,
              const std::string& payloadType,
              ITS_UINT maxInStreams = 256, ITS_UINT numOutStreams = 256,
              ITS_UINT maxAttempts = 5, ITS_UINT cookieLife = 5,
              bool hbOn = true, bool isClient = false,
              ITS_UINT initSecs = 3, ITS_UINT initUSecs = 0,
              ITS_UINT sendSecs = 3, ITS_UINT sendUSecs = 0,
              ITS_UINT recvSecs = 0, ITS_UINT recvUSecs = 200000,
              ITS_UINT hbSecs = 3, ITS_UINT hbUSecs = 0,
              ITS_UINT shutSecs = 0, ITS_UINT shutUSecs = 300000,
              ITS_UINT pmtuSecs = 600, ITS_UINT pmtuUSecs = 0)
        : TransportSpecifics(_mask)
    {
        char p[16];
        char **assoc, **homes;
        char out[16], in[16], at[16], cl[16], hb[16];
        char n[24], s[24], r[24], h[24], u[24], m[24];

        assoc = (char **)malloc(sizeof(char *) * associates.size());
        ITS_THROW_ASSERT(assoc != NULL);

        unsigned i;
        for (i = 0; i < associates.size(); i++)
        {
            assoc[i] = strdup(associates[i].c_str());

            ITS_THROW_ASSERT(assoc[i] != NULL);
        }

        homes = (char **)malloc(sizeof(char *) * extraHomes.size());
        ITS_THROW_ASSERT(assoc != NULL);

        for (i = 0; i < extraHomes.size(); i++)
        {
            assoc[i] = strdup(extraHomes[i].c_str());

            ITS_THROW_ASSERT(homes[i] != NULL);
        }

        sprintf(p, "%d", localPort);
        sprintf(out, "%d", maxInStreams);
        sprintf(in, "%d", numOutStreams);
        sprintf(at, "%d", maxAttempts);
        sprintf(cl, "%d", cookieLife);
        sprintf(hb, "%d", hbOn);
        sprintf(n, "%d,%d", initSecs, initUSecs);
        sprintf(s, "%d,%d", sendSecs, sendUSecs);
        sprintf(r, "%d,%d", recvSecs, recvUSecs);
        sprintf(h, "%d,%d", hbSecs, hbUSecs);
        sprintf(u, "%d,%d", shutSecs, shutUSecs);
        sprintf(m, "%d,%d", pmtuSecs, pmtuUSecs);

        specs = (ENGINE_TransportSpecifics)
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                _mask, localPath.c_str(), p,
                                assoc, associates.size(),
                                homes, extraHomes.size(),
                                out, in, at, cl, hb,
                                i, s, r, h, u, m,
                                isClient ? "yes" : "no",
                                payloadType.c_str());

        ITS_THROW_ASSERT(specs != NULL);
    }
};

/*
 * transport class
 */
class Transport
{
public:
    /* constructor */
    Transport(ITS_Object *threadPool,
              const char *name, ITS_UINT _mask,
              ITS_Object specifics, TransportCallbacks *callbacks)
    {
        tr = (ENGINE_Transport)
            ITS_ConstructObject(itsENGINE_TransportClass,
                                threadPool, name, _mask,
                                specifics, callbacks->GetCallbacks(),
                                NULL, NULL);

        ITS_THROW_ASSERT(tr != NULL);
    }

    /* constructor */
    Transport(ITS_Object *threadPool,
              const std::string& name, ITS_UINT _mask,
              ITS_Object specifics, TransportCallbacks *callbacks)
    {
        tr = (ENGINE_Transport)
            ITS_ConstructObject(itsENGINE_TransportClass,
                                threadPool, name.c_str(), _mask,
                                specifics, callbacks->GetCallbacks(),
                                NULL, NULL);

        ITS_THROW_ASSERT(tr != NULL);
    }

    ITS_Object&
    GetLinks()
    {
        return ENGINE_TR_LINKS(tr);
    }

    ENGINE_Transport&
    GetTransport()
    {
        return tr;
    }

private:
    ENGINE_Transport tr;
};

/*
 * work item class
 */
class WorkItem
{
public:
    /* constructor */
    WorkItem(Transport *tr, bool persist, int repeat,
             const char *libName, const char *delegate)
    {
        wi = (ENGINE_WorkItem)
            ITS_ConstructObject(itsENGINE_WorkItemClass,
                                tr->GetTransport(),
                                persist ? ITS_TRUE : ITS_FALSE,
                                repeat, libName, delegate);

        ITS_THROW_ASSERT(wi != NULL);
    }

    /* constructor */
    WorkItem(Transport *tr, bool persist, int repeat,
             const std::string& libName, const std::string& delegate)
    {
        wi = (ENGINE_WorkItem)
            ITS_ConstructObject(itsENGINE_WorkItemClass,
                                tr->GetTransport(),
                                persist ? ITS_TRUE : ITS_FALSE,
                                repeat, libName.c_str(), delegate.c_str());

        ITS_THROW_ASSERT(wi != NULL);
    }

private:
    ENGINE_WorkItem wi;
};

/*
 * stack layer class (settings)
 */
class ISS7StackLayer
{
public:
    /* constructor */
    ISS7StackLayer(Application *app,
                   const char *name, int variant,
                   int numThreads = 1)
    {
        layer = (ENGINE_ISS7Stack)
            ITS_ConstructObject(itsENGINE_ISS7StackClass,
                                app->GetApplication(),
                                name, variant);

        ITS_THROW_ASSERT(layer != NULL);
    }
    /* constructor */
    ISS7StackLayer(Application *app,
                   const std::string& name, int variant,
                   int numThreads = 1)
    {
        layer = (ENGINE_ISS7Stack)
            ITS_ConstructObject(itsENGINE_ISS7StackClass,
                                app->GetApplication(),
                                name.c_str(), variant);

        ITS_THROW_ASSERT(layer != NULL);
    }

    ITS_Object&
    GetTrace()
    {
        return ENGINE_ISS7_TRACE(layer);
    }

    ITS_Object&
    GetLinks()
    {
        return ENGINE_ISS7_LINKS(layer);
    }

    void
    SetTimers(const char **options, int numOptions)
    {
        char **localOpts;

        localOpts = (char **)malloc(sizeof(char *) * numOptions);
        ITS_THROW_ASSERT(localOpts != NULL);

        for (int i = 0; i < numOptions; i++)
        {
            localOpts[i] = strdup(options[i]);

            ITS_THROW_ASSERT(localOpts[i] != NULL);
        }

        ENGINE_ISS7_TIMERS(layer) = localOpts;
        ENGINE_ISS7_NUM_TIMERS(layer) = numOptions;
    }
    void
    SetTimers(const std::vector<std::string>& options)
    {
        char **localOpts;

        localOpts = (char **)malloc(sizeof(char *) * options.size());
        ITS_THROW_ASSERT(localOpts != NULL);

        for (unsigned i = 0; i < options.size(); i++)
        {
            localOpts[i] = strdup(options[i].c_str());

            ITS_THROW_ASSERT(localOpts[i] != NULL);
        }

        ENGINE_ISS7_TIMERS(layer) = localOpts;
        ENGINE_ISS7_NUM_TIMERS(layer) = options.size();
    }

    void
    SetModifiers(const char **options, int numOptions)
    {
        char **localOpts;

        localOpts = (char **)malloc(sizeof(char *) * numOptions);
        ITS_THROW_ASSERT(localOpts != NULL);

        for (int i = 0; i < numOptions; i++)
        {
            localOpts[i] = strdup(options[i]);

            ITS_THROW_ASSERT(localOpts[i] != NULL);
        }

        ENGINE_ISS7_MODIFIERS(layer) = localOpts;
        ENGINE_ISS7_NUM_MODIFIERS(layer) = numOptions;
    }
    void
    SetModifiers(const std::vector<std::string>& options)
    {
        char **localOpts;

        localOpts = (char **)malloc(sizeof(char *) * options.size());
        ITS_THROW_ASSERT(localOpts != NULL);

        for (unsigned i = 0; i < options.size(); i++)
        {
            localOpts[i] = strdup(options[i].c_str());

            ITS_THROW_ASSERT(localOpts[i] != NULL);
        }

        ENGINE_ISS7_MODIFIERS(layer) = localOpts;
        ENGINE_ISS7_NUM_MODIFIERS(layer) = options.size();
    }

private:
    ENGINE_ISS7Stack layer;
};

/*
 * stack management class (callbacks)
 */
class SS7Callbacks
{
public:
    /* constructor */
    SS7Callbacks(Application *app, const char *libName,
                 const char *mtp3MgmtAnsi, const char *mtp3MgmtCcitt,
                 const char *isupMgmtAnsi, const char *isupMgmtCcitt,
                 const char *sccpMgmtAnsi, const char *sccpMgmtCcitt,
                 const char *sccpGTTAnsi, const char *sccpGTTCcitt,
                 const char *sccpSSNRouteAnsi, const char *sccpSSNRouteCcitt)
    {
        cbs = (ENGINE_SS7StackMgmt)
            ITS_ConstructObject(itsENGINE_SS7StackMgmtClass,
                                app->GetApplication(),
                                libName,
                                mtp3MgmtAnsi, mtp3MgmtCcitt,
                                isupMgmtAnsi, isupMgmtCcitt,
                                sccpMgmtAnsi, sccpMgmtCcitt,
                                sccpGTTAnsi, sccpGTTCcitt,
                                sccpSSNRouteAnsi, sccpSSNRouteCcitt);

        ITS_THROW_ASSERT(cbs != NULL);
    }

    /* constructor */
    SS7Callbacks(Application *app, const std::string& libName,
                 const std::string& mtp3MgmtAnsi, 
                 const std::string& mtp3MgmtCcitt,
                 const std::string& isupMgmtAnsi, 
                 const std::string& isupMgmtCcitt,
                 const std::string& sccpMgmtAnsi, 
                 const std::string& sccpMgmtCcitt,
                 const std::string& sccpGTTAnsi, 
                 const std::string& sccpGTTCcitt,
                 const std::string& sccpSSNRouteAnsi, 
                 const std::string& sccpSSNRouteCcitt)
    {
        cbs = (ENGINE_SS7StackMgmt)
            ITS_ConstructObject(itsENGINE_SS7StackMgmtClass,
                                app->GetApplication(),
                                libName.c_str(),
                                mtp3MgmtAnsi.c_str(), mtp3MgmtCcitt.c_str(),
                                isupMgmtAnsi.c_str(), isupMgmtCcitt.c_str(),
                                sccpMgmtAnsi.c_str(), sccpMgmtCcitt.c_str(),
                                sccpGTTAnsi.c_str(), sccpGTTCcitt.c_str(),
                                sccpSSNRouteAnsi.c_str(), 
                                sccpSSNRouteCcitt.c_str());

        ITS_THROW_ASSERT(cbs != NULL);
    }

private:
    ENGINE_SS7StackMgmt cbs;
};

/*
 * the reason for being
 */
class Engine
{
public:
    Engine(const char *applicationName,
           int argc, const char **argv,
           const char *xmlData)
    {
        its::Application::SetName(applicationName);

        ac = argc;
        av = argv;

        xd = strdup(xmlData);
    }

    Engine(const std::string& appName,
           int argc, const char **argv,
           const std::string& xmlData)
    {
        its::Application::SetName(appName.c_str());

        ac = argc;
        av = argv;

        xd = strdup(xmlData.c_str());
    }

    virtual void
    Initialize()
    {
        ENGINE_Initialize(ac, av, xd, strlen(xd) + 1);
    }

    virtual int
    Run()
    {
        return ENGINE_Run(ac, av);
    }

private:
    int ac;
    const char **av;
    char *xd;
};

/*
 * driver implementation class
 *
 * The recommended calling convention when dispatching application threads
 * is:
 *
 *   its::ThreadPoolThread *thr;
 *   engine::Worker *eng;
 *
 *   pool->GetFirstAvailThread(thr);
 *   eng = reinterpret_cast<engine::Worker *>(thr.GetThread());
 *   pool->DispatchOnThread(eng, DISP_Dispatch_USER_CPP,
 *                          (void *)eng->GetCallbackStruct());
 */
class Worker : public its::Worker
{
public:
    Worker(int stackSize, const char *name,
           ITS_USHORT instance, ITS_UINT mask)
        : its::Worker(stackSize, name, instance, mask),
          cbs(NULL),
          configRec(NULL),
          userData(NULL)
    {
    }

    virtual ~Worker()
    {
        if (cbs)
        {
            free(cbs);
        }
    }

    void
    SetUserData(void *data)
    {
        userData = data;
    }
    void *
    GetUserData(void)
    {
        return (userData);
    }

    // private methods for the engine.  Users should not invoke
    DISP_FuncsCPP*&
    GetCallbackStruct()
    {
        return cbs;
    }
    ITS_Object&
    GetConfigRec()
    {
        return configRec;
    }
private:
    DISP_FuncsCPP   *cbs;
    ITS_Object      configRec;
    void            *userData;
};

/*
 * driver implementation class.  The only override is the
 * MatchThread method.
 */
class EnginePool : public its::ThreadPool
{
public:
    EnginePool()
        : its::ThreadPool()
    {
    }

    virtual
    ~EnginePool()
    {
    }

    virtual bool MatchThread(its::ThreadPoolThread *thr,
                             void *userData);
};

/*
 * trace level strings
 */
#define APP_LEVEL_DEBUG     "APP_DEBUG_TRACE"
#define APP_LEVEL_WARNING   "APP_WARNING_TRACE"
#define APP_LEVEL_ERROR     "APP_ERROR_TRACE"
#define APP_LEVEL_CRITICAL  "APP_CRITICAL_TRACE"

/*
 * driver variables
 */
DRVDLLAPI extern its::TraceLevel    *AppDebugTrace;
DRVDLLAPI extern its::TraceLevel    *AppWarningTrace;
DRVDLLAPI extern its::TraceLevel    *AppErrorTrace;
DRVDLLAPI extern its::TraceLevel    *AppCriticalTrace;

DRVDLLAPI extern EnginePool         *borderPool;
DRVDLLAPI extern EnginePool         *workerPool;
DRVDLLAPI extern its::WorkItemPool  *workItemPool;

#if defined(ITS_NAMESPACE)
}
#endif

#endif  /* _ENGINE_PP_H_ */
