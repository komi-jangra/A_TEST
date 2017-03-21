/*se ts=2************************************File Source*****
File Name		:	  sksdb_include.c 
Purpose			:		This file has utility function to retrive 
                     system configuraion values from DB.
Project			:		GSM
Subsystem		:	  Db	
Author			:		
CSCI id			:
Version			:		V0.1
*************************************************************/

/*******************************************Change History***
S.No.   Release        Patch        Author        Description
1.      Rel0.0         None         xxxxx         Creation
*************************************************************/


#include <sksdb_include.h>

/*************************************************************
Return Values : = 0 for Success
                <> 0  for failure 

Output        : I_U8 *mscId (Ascii Digit String Null Terminated) 
*************************************************************/
void  SksDbInit() 
{
   I_S32 retVal=0;
    /* REGISTRATION WITH DB */
    while((retVal = clib_init((char *)"../config/hlrdb.cfg")) != 0)
    {
           sleep (1);
    //       SCM_printf(SCM_INFO,"clib_init FAILED : CCM ERR = %d\n", retVal);
    }


}/*SksDbInit*/



/********************End Of File *******************************************/
