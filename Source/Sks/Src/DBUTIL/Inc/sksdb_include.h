#ifndef __SKSDB_INCLUDE_H
#define __SKSDB_INCLUDE_H 
/*se ts=2************************************File Header*****
File Name		:		skdb_include.h 
Purpose			:		hash defines used by Application and 
                     DBUTIL Library
Project			:		GSM
Subsystem		:	  SKS / DBUTIL	
Author			:		
CSCI id			:
Version			:		V0.1
*************************************************************/

/*******************************************Change History***
S.No.   Release        Patch        Author        Description
1.      Rel0.0         None         xxxxx         Creation
*************************************************************/
#ifdef BSC
//#define clib_dump(D_ID,M_ID,rS,rC) scm_clib_dump(D_ID,M_ID,rS,rC);
//#define clib_get(D_ID,M_ID,Ix,sIx,Buf,rS,rC) scm_clib_get(D_ID,M_ID,Ix,sIx,Buf,rS,rC);
#endif

#include <stdio.h>
#include "../../SCM/Inc/scm_encaps.h"
//#include <sysinst_hashdefs.h>
//#include <sysxxx_typedef.h>
//#include <syscmn_hashdefs.h>
//#include <sysxxx_hashdefs.h>
#include <dbsxxx_tabledef.h>
#include <dbsxxx_persistent_table.h>
//#include <dbsxxx_transient_table.h>

//#include <oamxxx_alarmtypedefs.h>
//#include <scm_msgdef.h>
//#include <scm_hashdefs.h>
//#include <scm_preconfig_msgdef.h>
#include <DBLIBError.h>


#define DB_SUCCESS  DBLIB_SUCCESS

#endif // __SKSDB_INCLUDE_H 
