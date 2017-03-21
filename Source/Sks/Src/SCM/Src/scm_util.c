#include "scm_localhashdef.h"
#include <scm_encaps.h>

void scm_signal()
{
  sem_signal.sem_num =  0;
  sem_signal.sem_op  =  1;
  sem_signal.sem_flg =  0;
  semop(g_parameter.semID, &sem_signal, 1);
  SCM_printf(SCM_DEBUG,"CONFIG SEMAPHORE SIGNAL");
  return;
} 
void scm_wait()
{
  sem_signal.sem_num =  0;
  sem_signal.sem_op  =  -1;
  sem_signal.sem_flg =  0;
  semop(g_parameter.semID, &sem_signal, 1);
  SCM_printf(SCM_DEBUG,"WAITING FOR SEMAPHORE SIGNAL");
  return;
}



void SCM_DUMP(int A, int C, unsigned char* ptr, int Y)
{
     #ifndef LOGGER_IMR
     int i;
     int M = 0;
     SCM_printf (SCM_DEBUG,"\n\t");
     for (i = A; i < C; i++)
     {
                 SCM_printf (SCM_DEBUG,"%03d ", ptr [i]);
                 if (M < Y)
                     M = M + 1;
                 else
                 {
                     SCM_printf (SCM_DEBUG,"\n\t");
                     M = 0;
                 }
     }
     SCM_printf (SCM_DEBUG,"\n");
     #else
     PRINT_HEX_DUMP(DEBUG,ptr,C);
     #endif
}





void STRING_DUMP(int A, int LEN, U8 *p_buf, int P)
{
     #ifndef LOGGER_IMR
     int M = 0;
     int i;
     int align;
     #else
     U8 temp_string[1000];
     int i = 0, j;
     for ( j = 0; j < LEN; j++ )
     {
           if ( p_buf[j] != '\n' )
           {
                temp_string[i] = p_buf[j];
                i = i + 1;
           }
           else
           {
                temp_string [i] = '\0';
                if ( i > 1 )
                {
                   SCM_printf(SCM_DEBUG,"%s",temp_string);
                }
                i = 0;
           }
     }
     #endif
     SCM_printf (SCM_DEBUG, "SCM MIS : DONE SCM_DUMP\n");
}


/* Signal handling of SIGINT */
void scmSigintHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGINT\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}

/* Signal handling of SIGQUIT */
void scmSigquitHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGQUIT\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}

/* Signal handling of SIGSTOP */
void scmSigstopHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGSTOP\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}
/* Signal handling of SIGSEGV */
void scmSigsegvHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGSEGV\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}

/* Signal handling of SIGBUS */
void scmSigbusHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGBUS\n");
   SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
   exit(0);
}

/* Signal handling of SIGILL */
void scmSigillHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGILL\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}

/* Signal handling of SIGFPEV */
void scmSigfpeHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGFPE\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}

void scmSigchldHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGCHLD\n");
   //   //exit(0);
}

/* Signal handling of SIGUSR1 */
void scmSiguser1Handler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGUSR1\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}

/* Signal handling of SIGUSR2 */
void scmSiguser2Handler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGUSR2\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}


/* Signal handling of SIGTERM */
void scmSigtermHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGFPE\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}
/* Signal handling of SIGTERM */
void scmSigpipeHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGPIPE\n");
   SCM_printf (SCM_CRITICAL, "\nENTITY OAM IS MARKED DOWN\n");
   close(xxx_client_sockfd [ENT_OAM]);
   FD_CLR(xxx_client_sockfd [ENT_OAM], &client_fd);
   g_parameter.config_cmd_resp = 0;
   xxx_client_sockfd [ENT_OAM] = -1;
     // exit(0);
}
/* Signal handling of SIGTERM */
void scmSigcontHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGCONT\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}

void scmSigabrtHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGABRT\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}
void scmSigtrapHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGTRAP\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}
void scmSigtstpHandler()
{
   SCM_printf(SCM_INFO,"\nscm: Recieved signal SIGTSTP\n");
      SCM_printf(SCM_INFO,"\nscm: Exiting.......\n");
      exit(0);
}

void scmSigInit()
{
 /* Ignore the signals */
 //signal(SIGHUP, SIG_IGN);
 signal(SIGINT, scmSigintHandler);
 signal(SIGQUIT, scmSigquitHandler);
 signal(SIGSTOP, scmSigstopHandler);
 signal(SIGUSR1, scmSiguser1Handler);
 signal(SIGUSR2, scmSiguser2Handler);

 //signal(SIGUSR3, SIG_IGN);
 //signal(SIGUSR4, SIG_IGN);
 signal(SIGTERM, scmSigtermHandler);
// signal(SIGALRM, scmSigalrmHandler);

 //signal(SIGSEGV, scmSigsegvHandler);
 signal(SIGBUS, scmSigbusHandler);
 signal(SIGILL, scmSigillHandler);
 signal(SIGFPE, scmSigfpeHandler);
 signal(SIGCHLD, scmSigchldHandler);
 signal(SIGPIPE, scmSigpipeHandler);
 signal(SIGCONT, scmSigcontHandler);
 signal(SIGABRT, scmSigabrtHandler);
 signal(SIGTRAP, scmSigtrapHandler);
 signal(SIGTSTP, scmSigtstpHandler);
}


