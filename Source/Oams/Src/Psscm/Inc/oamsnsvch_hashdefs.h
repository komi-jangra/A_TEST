/*********************************************************** File Header **
 FILE NAME         :  oamsnsvch_hashdefs.h
 PURPOSE           :  Contains NSVCH Hashdefs
 PROJECT           :  BSC
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSNSVCH_HASHDEFS_H
#define __OAMSNSVCH_HASHDEFS_H

/* NSVCH hashdefs for the two classes */
#define NONE				0                      
#define LOCK_IN_PROGRESS		1
#define UNLOCK_IN_PROGRESS		2

#define DOWN				0                           
#define UP				1                             

#define OAMS_NSVC_BLOCKED		0
#define OAMS_NSVC_RESET			1
#define OAMS_FRCHANNEL_DOWN		2

/*Fix for mantis 0014667 starts*/

#define STOP_NOT_INITIATED		0
#define STOP_NOT_COMPLETED		1
#define STOP_COMPLETED			2

/*Fix for mantis 0014667 End*/ 

#endif
