/*************************************************************** File Header ***
  File Name      : oamcfg_signal_handler.c
Purpose        :
Project        : BSC
Subsystem    : OAM - CFG
Author         : Aricent, B'lore
CSCI id        :
Version        : 1.2
 *********************************************************************** End ***/

#include "oamscfg_includes.h"

/* Signal handling of SIGALRM */
void *cfgSigalrmHandler()
{
   LOG_PRINT(LOG_CRITICAL,"CFG: Recieved signal Alarm");

} /* End of function cfgSigalrmHandler() */

/* Signal handling of SIGINT */
void *cfgSigintHandler(int signum)
{
   signal(signum, SIG_DFL);
   signal(SIGSEGV, cfgSigsegvHandler);
   LOG_PRINT(LOG_CRITICAL,"CFG: Recieved signal SIGINT %d", signum);
   LOG_PRINT(LOG_INFO,"CFG: Exiting.......");
   exit(0);
}

/* Signal handling of SIGQUIT */
void *cfgSigquitHandler(int signum)
{
   signal(signum, SIG_DFL);
   LOG_PRINT(LOG_CRITICAL,"CFG: Recieved signal SIGQUIT");
   LOG_PRINT(LOG_INFO,"CFG: Exiting.......");
   exit(0);
}

/* Signal handling of SIGSTOP */
void *cfgSigstopHandler(int signum)
{
   signal(signum, SIG_DFL);
   LOG_PRINT(LOG_CRITICAL,"CFG: Recieved signal SIGSTOP");
   LOG_PRINT(LOG_INFO,"CFG: Exiting.......");
   exit(0);
}
/* Signal handling of SIGSEGV */
void *cfgSigsegvHandler(int signum)
{
//   LOG_PRINT(LOG_CRITICAL,"CFG: Recieved signal SIGSEGV");
//   LOG_PRINT(LOG_INFO,"CFG: Exiting.......");

/* LOG SIGSEGV rxd
    * Update CPLD card state reg *
    * Set SIGSEGV to default *
    * Resend SIGSEGV to process from the handler *
    */
//   savelog(signum);
//   signal(signum, SIG_DFL);
//   kill(signum, getpid());
   exit(0);
}

/* Signal handling of SIGBUS */
void *cfgSigbusHandler()
{
   LOG_PRINT(LOG_CRITICAL,"CFG: Recieved signal SIGBUS");
   LOG_PRINT(LOG_INFO,"CFG: Exiting.......");
   exit(0);
}

/* Signal handling of SIGILL */
void *cfgSigillHandler()
{
   LOG_PRINT(LOG_CRITICAL,"CFG: Recieved signal SIGILL");
   LOG_PRINT(LOG_INFO,"CFG: Exiting.......");
   exit(0);
}

/* Signal handling of SIGFPEV */
void *cfgSigfpeHandler()
{
   LOG_PRINT(LOG_CRITICAL,"CFG: Recieved signal SIGFPE");
   LOG_PRINT(LOG_INFO,"CFG: Exiting.......");
   exit(0);
}

/********************************* Change History ***************************
  Release     Patch       Author         Description

 ************************************** End *********************************/

