/*
 * The Spread Toolkit.
 *     
 * The contents of this file are subject to the Spread Open-Source
 * License, Version 1.0 (the ``License''); you may not use
 * this file except in compliance with the License.  You may obtain a
 * copy of the License at:
 *
 * http://www.spread.org/license/
 *
 * or in the file ``license.txt'' found in this distribution.
 *
 * Software distributed under the License is distributed on an AS IS basis, 
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License 
 * for the specific language governing rights and limitations under the 
 * License.
 *
 * The Creators of Spread are:
 *  Yair Amir, Michal Miskin-Amir, Jonathan Stanton, John Schultz.
 *
 *  Copyright (C) 1993-2006 Spread Concepts LLC <info@spreadconcepts.com>
 *
 *  All Rights Reserved.
 *
 * Major Contributor(s):
 * ---------------
 *    Ryan Caudy           rcaudy@gmail.com - contributions to process groups.
 *    Claudiu Danilov      claudiu@acm.org - scalable wide area support.
 *    Cristina Nita-Rotaru crisn@cs.purdue.edu - group communication security.
 *    Theo Schlossnagle    jesus@omniti.com - Perl, autoconf, old skiplist.
 *    Dan Schoenblum       dansch@cnds.jhu.edu - Java interface.
 *
 */




#include <string.h>
#include <signal.h>
#include "arch.h"
#include "spread_params.h"
#include "session.h"
#include "configuration.h"
#include "sp_events.h"
#include "status.h"
#include "log.h"
#include "alarm.h"

#ifndef ARCH_PC_WIN95
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#endif

#ifdef	ARCH_PC_WIN95

#include	<winsock.h>

WSADATA		WSAData;

#endif	/* ARCH_PC_WIN95 */
 #ifdef PLATFORM_IMR
 #include <bpmxxx_commonDef.h>
 #include <bpmxxx_OAM_commonDef.h>
 #include <bpmxxx_platformLib.h>
 #include <stdlib.h>
 #endif
#ifdef LOGGER_IMR
 #include <sysxxx_hashdefs.h>
 #include <sysxxx_typedef.h>
 #include <sysxxx_msgstruct.h>
 #include <sysxxx_proc.h>
 #include <sysxxx_prcr.h>
 #include <ipcfrm_syslog.h>
 SysAddr slfAddr;
#endif
extern  unsigned int  LEAVE_EVENT_SEND;
static	char		*My_name;
static	char		My_name_buf[80];
static	char		Config_file[80];
static	int		Log;
static  const char            Spread_build_date[] = SPREAD_BUILD_DATE;

static	void	Invalid_privilege_decrease(char *user, char *group);
static	void	Usage(int argc, char *argv[]);
extern  void Gcsutil_Invoke();
extern  void PEER_Leave();
extern  void SendNetworkChangeLeaveMsg();
/* auth-null.c: */
void null_init(void);
/* auth-ip.c: */
void ip_init(void);
/* acp-permit.c: */
void permit_init(void);
/* HLD: added break/exit handler (to allow profiling). */
#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
{
    exit(0);

    return 1; /* Not reached. */
}
#else /* !defined(WIN32) */
static void exitHandler(int sig)
{
    exit(0);
}
#endif /* defined(WIN32) */

void gcsBpmAisCallbackFunc(struct sAisParam* param);
/* HLD: end. */
#ifdef PLATFORM_IMR
void gcsBpmAisCallbackFunc(struct sAisParam* param)
{

        switch(param->messageId)
        {
                case BPM_HEALTHCHECK_MESSAGE:
                       {
                        bpmRespondToAis (param->invocation,OK);
                        }
                        break;

                case BPM_SELFCARD_STATE_CHANGE:
                         if(param->cardState == CARDSTATE_RECOVERY)
                         {
                           LOG_PRINT(INFO," **** SELF CARDSTATE_RECOVERY  so ABORTING %d ***\n ",param->cardState);
                           bpmRespondToAis (param->invocation,OK);
                           abort();
                         }
                         else
                         {
                           bpmRespondToAis (param->invocation,OK);
                         }
                        break;

                case BPM_PEERCARD_STATE_CHANGE:
                             LOG_PRINT(INFO," **** CARDSTATE_PEER UPDATE  %d ***\n ",param->cardState);
                         if((param->cardState == CARDSTATE_ABSENT) || (param->cardState == CARDSTATE_FAIL) || (param->cardState == CARDSTATE_RECOVERY))
                         {
                            
                             LOG_PRINT(INFO," **** CARDSTATE_ABSENT  ***\n ");
                             LOG_PRINT(INFO," PEER_LEAVE called :Before PEER_LEAVE  LEAVE_EVENT_SEND[%d] ***\n ",LEAVE_EVENT_SEND);
                             if(LEAVE_EVENT_SEND == 0)
                             {
                               PEER_Leave();
                               LEAVE_EVENT_SEND = 1;
                             LOG_PRINT(INFO," PEER_LEAVE called :Setting LEAVE_EVENT_SEND[%d] ***\n ",LEAVE_EVENT_SEND);
                             }
                             else
                             {
                             LOG_PRINT(INFO," **** PEER_LEAVE ALREADY CALLED:LEAVE_EVENT_SEND[%d] ***\n ",LEAVE_EVENT_SEND);
                             }
                               
                         }
                        bpmRespondToAis (param->invocation,OK);
                        break;

                case BPM_MSG_ACK_CONFIGURE:
                        break;

                case BPM_SHUTDOWN:
                     LOG_PRINT(INFO," **** SHUT DOWN  ***\n ");
                     abort();
 
                      break;
                default:
                        break;
        }
}

#endif
void handle_sig()
{
LOG_PRINT(INFO,"handler function caught");
  exit(1);
}

int main(int argc, char *argv[])
{
My_name = 0; /* NULL */
char *env = NULL;
signal(SIGINT,handle_sig);
#ifdef	ARCH_PC_WIN95
	int	ret;
#endif

#ifndef ARCH_PC_WIN95
	struct group  *grp;
	struct passwd *pwd;
#endif
/* HLD: added break/exit handler (to allow profiling). */
#if defined(WIN32)
SetConsoleCtrlHandler(breakHandler, TRUE);
#else /* !defined(WIN32) */
signal(SIGINT, exitHandler);
#endif /* defined(WIN32) */
 /* HLD: end. */
  #ifdef LOGGER_IMR
     slfAddr.prcr = 0;
     slfAddr.entity = 105;
     slfAddr.clsId = 0;
     slfAddr.rfu = 0;
     slfAddr.inst = 0;
     if(InitLoggingUtility(slfAddr) == 0)
      {
       LOG_PRINT(INFO," GCS GET REGISTERED  with LOGGER Utility   ");
      }
     else
      {
       LOG_PRINT(INFO," GCS couldnot  REGISTERED  with LOGGER Utility   ");
      }

#endif

	Alarm_set_types( CONF ); 
        Alarm_set_priority( SPLOG_INFO );


      /*chage for node Id*/
     env = getenv((const char *)"CardId");

     memcpy( My_name_buf,env,strlen(env));
     My_name = My_name_buf;
     LOG_PRINT(INFO,"Node Id=%s\n",My_name);
   /*end */
//      Usage( argc, argv );
 #ifdef PLATFORM_IMR
     /*  Application will  register with application  */
    bpmGetComponentRegister(gcsBpmAisCallbackFunc,(unsigned short)ENT_SKS_GCS);
    bpmComponentConfigure();
 #endif

//	Usage( argc, argv );
  Gcsutil_Invoke();
  while(1)
  {
     LOG_PRINT(CRITICAL," Return From Gcsutil_Invoke function\n");
     LOG_PRINT(CRITICAL," Return From Gcsutil_Invoke function\n");
     LOG_PRINT(CRITICAL," Return From Gcsutil_Invoke function\n");
     exit(0);
     sleep(5);
  }
#if 0

#ifdef	ARCH_PC_WIN95

	ret = WSAStartup( MAKEWORD(1,1), &WSAData );
	if( ret != 0 )
            Alarmp( SPLOG_FATAL, NETWORK, "Spread: winsock initialization error %d\n", ret );

#endif	/* ARCH_PC_WIN95 */

        /* initialize each valid authentication protocol */
        null_init();
        ip_init();
#ifdef  ENABLE_PASSWORD
        pword_init();
#endif
        permit_init();

        /* Initialize Access Control & Authentication */
        Acm_init();

	Conf_init(Config_file, My_name );

	E_init();

	Sess_init();

	Stat_init(); 
	if( Log ) Log_init();

#ifndef	ARCH_PC_WIN95
	/* Yupp, we're paranoid */
/* HLD: commented out. */
#if 0 
	if (geteuid() != (uid_t) 0) {
            Alarmp( SPLOG_WARNING, SECURITY, "Spread: not running as root, won't chroot\n" );
	}
	else if ( (grp = getgrnam(Conf_get_group())) == NULL || (pwd = getpwnam(Conf_get_user())) == NULL ) {
            Invalid_privilege_decrease(Conf_get_user(), Conf_get_group());
	}
	else if (chdir(Conf_get_runtime_dir()) < 0 || chroot(Conf_get_runtime_dir()) < 0 ) {
            Alarmp( SPLOG_FATAL, SECURITY, "Spread: FAILED chroot to '%s'\n", Conf_get_runtime_dir() );
	}
	else if ( setgroups(1, &grp->gr_gid) < 0 || setgid(grp->gr_gid) < 0 || setuid(pwd->pw_uid) < 0) {
            Invalid_privilege_decrease(Conf_get_user(), Conf_get_group());
	} else {
            Alarmp( SPLOG_INFO, SECURITY, "Spread: setugid and chroot successeful\n" );
	}
#endif
#endif	/* ARCH_PC_WIN95 */

    //   LOG_PRINT(INFO," GCS UTIL GET REGISTERED     ");
  //Gcsutil_Invoke();
      // LOG_PRINT(INFO," GCS UTIL GET REGISTERED   ");
	E_handle_events();

#endif

	return 0;
}

static  void    Print_help(void)
{
    Alarmp( SPLOG_FATAL, SYSTEM, "Usage: spread\n%s\n%s\n%s\n",
           "\t[-l y/n]          : print log",
           "\t[-n <proc name>]  : force computer name",
           "\t[-c <file name>]  : specify configuration file" );
}


static	void	Invalid_privilege_decrease(char *user, char *group)
{
    Alarmp( SPLOG_FATAL, SECURITY, "Spread: FAILED privilege drop to user/group "
           "'%s/%s' (defined in spread.conf or spread_params.h)\n",
           user, group );
}

static	void	Usage(int argc, char *argv[])
{
  char *path, *absPath;

     absPath=(char*)malloc(sizeof(char)*100);
     path = getenv ((const char *) "CONFIG");
     strcpy(absPath, path);
     strcat(absPath,"gcs_daemon.ini");
	//My_name = 0; /* NULL */ /* changes by anand for config file parsing */
	Log	= 1;//changed by sandeep as previous version having this valiue 
//	strcpy( Config_file, "../config/gcs_daemon.ini" );
	strcpy( Config_file, absPath );
#if 0 //changed by sandeep as this need not to be there 
	while( --argc > 0 )
	{
		argv++;

		if( !strncmp( *argv, "-n", 2 ) )
		{
                        if (argc < 2) Print_help();
			if( strlen( argv[1] ) > MAX_PROC_NAME-1 ) /* -1 for the null */
                              Alarmp( SPLOG_FATAL, SYSTEM, "Usage: proc name %s too long\n",
					argv[1] );

			memcpy( My_name_buf, argv[1], strlen( argv[1] ) );
			My_name = My_name_buf;

			argc--; argv++;

		}else if( !strncmp( *argv, "-c", 2 ) ){
                        if (argc < 2) Print_help();
			strcpy( Config_file, argv[1] );

			argc--; argv++;

		}else if( !strncmp( *argv, "-l", 2 ) ){
                        if (argc < 2) Print_help();
			if( !strcmp( argv[1], "y" ) )
				Log = 1;
			else if( !strcmp( argv[1], "n" ) )
				Log = 0;
			else Print_help();

			argc--; argv++;

		}else{
                        Print_help();
		}
	}
#endif
}
