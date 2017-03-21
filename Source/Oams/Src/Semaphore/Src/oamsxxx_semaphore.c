#include<oamsxxx_semaphore.h>
#include "sysxxx_typedef.h"
#include "sysxxx_hashdefs.h"
#include "sysxxx_msgstruct.h"
#include "sysxxx_proc.h"
#include "sysinst_hashdefs.h"
#include "sysxxx_macro.h"

#include "ipcfrm_extern.h"
#include "ipcfrm_msgqueue.h"
#include "ipcfrm_msgdef.h"
#include "ipcfrm_syslog.h"

/*sem_t* semaphoreOpen(char* semName)
{
	sem_t* semHandler;
	sem_unlink (semName);
  	if ((semHandler = sem_open (semName, SEM_FLG|O_CREAT|O_EXCL, S_IWUSR|S_IRUSR, 1))==SEM_FAILED)
   {
			
		LOG_PRINT(INFO, "Semaphore init failed :: %s",strerror(errno));
      sem_close (semHandler);
      sem_unlink (semName);
		semHandler =  NULL;
		
   }
	return semHandler; 
}*/


int semaphoreInit(sem_t* semHandler)
{
	int retVal;
	
	retVal = sem_init (semHandler, 0, 1);
  	if (retVal == -1)
   {
			
		LOG_PRINT(INFO, "Semaphore init failed :: %s",strerror(errno));
      sem_destroy (semHandler);
     // sem_unlink (semName);
		
   }
	return retVal;
}


int semaphoreWait(sem_t* semHandler)
{
	int retVal;
	retVal = sem_wait(semHandler);
	return retVal;
}	

int semaphorePost(sem_t* semHandler)
{
	int retVal;
	retVal = sem_post(semHandler);
	return retVal;
}	

int semaphoreTimedWait(sem_t* semHandler)
{
	int retVal = 1;
	int errCode;
   struct timespec abs_timeout;
//   fprintf(stderr, "\nWaiting for signal ");
//   fflush(stdout);
   LOG_PRINT(INFO, "semTimedFunc called with semandler:: %d", semHandler);


   clock_gettime(CLOCK_REALTIME, &abs_timeout);
   abs_timeout.tv_sec += SEMAPHORE_TIMEOUT;
	errCode = sem_timedwait(semHandler, &abs_timeout);	
	if(errCode != 0)
   {
   	LOG_PRINT(INFO, "semaphore not got within 4 secs", semHandler);
      retVal = 0;
   }
   return retVal;
}
