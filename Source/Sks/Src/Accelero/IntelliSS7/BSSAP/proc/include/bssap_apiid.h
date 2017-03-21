#ifndef  _BSSAP_APPID_H_
#define  _BSSAP_APPID_H_

#include <BSSAP++.h>
#include <bssap_common.h>

using namespace std;
using namespace its;

/*
* PURPOSE:
*       Maintains complete call object information
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0170
*/
class BSSAP_AppId
{
public:

     BSSAP_AppId()
     {
        slr = dlr = 0; 
     }

     ITS_CTXT GetSLR() 
     { 
         return slr;
     }

     void SetSLR(ITS_CTXT sl)
     { 
         slr = sl;
     }

     ITS_CTXT GetDLR() 
     { 
         return dlr;
     }

     void SetDLR(ITS_CTXT dl)
     { 
         dlr = dl;
     }

     ITS_UINT GetAppId()
     { 
         return appId; 
     }

     void SetAppId(ITS_UINT ai)
     { 
         appId = ai;
     }

private:
     ITS_CTXT dlr;
     ITS_CTXT slr;
     ITS_UINT appId;
};

#endif

