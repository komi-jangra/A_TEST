/** ts=3 ********************************************************File Header ** 
 FILE NAME         :  oamsswmh_swmhlib.h
 PURPOSE           :  Contains SWMH Data struct

 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/
#ifndef __OAMSSWMH_SWMHLIB_H
#define __OAMSSWMH_SWMHLIB_H

//#include <stdio.h>
#include <sysxxx_typedef.h>


//void getSoftwareVersionFileSize(char *binaryPath, I_U32 *fileSize ) ;

I_S8 getSoftwareVersionFileSize(I_S8 *path, I_U32 *filesize);
#endif   /* __OAMSSWMH_DATASTRUCT_H  */

