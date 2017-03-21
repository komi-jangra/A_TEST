#ifndef  _BSSAP_APPIDDB_H_
#define  _BSSAP_APPIDDB_H_

#include <bssap_apiid.h>
#include <its_hash.h>
#include <its_singleton.h>

#define BS_APPID_INFO  2

/*implementation:internal
*
* PURPOSE:
*       Maintains CALL CTXT table in DSM. it provides Add, Fetch, Remove
*       function to manipulate/remove call object properties
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
*                        ID :: D0180
*/
class BSSAP_AppidDB :
     public its::ITS_SingletonMultithreaded<BSSAP_AppidDB>
    
{
public:
    
    BSSAP_AppidDB() :
               its:: ITS_SingletonMultithreaded<BSSAP_AppidDB>()
    {
        _BS_Appid_info = HASH_CreateTable();
    }

    ~BSSAP_AppidDB();
    
    static ITS_INT Initialize();

    ITS_INT Add(BSSAP_AppId* appid);
    BSSAP_AppId* Fetch(ITS_CTXT appid);
    ITS_INT Remove(ITS_CTXT appid);
/*Modification Start by Amaresh as on dated 26-08-14 */   
    ITS_INT AddAppidLocal(BSSAP_AppId* appid);
    ITS_INT RemoveAppidLocal(ITS_CTXT appid);
/*Modification Stop by Amaresh as on dated 26-08-14 */
private:

    HASH_Table _BS_Appid_info;   

};

#endif

