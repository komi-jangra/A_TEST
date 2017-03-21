#include "oamsxxx_mutex.h"
#define MUTEX_TIMEOUT 8

void initMutex(pthread_mutex_t *mutexsum)
{
//   fprintf(stderr, "\nInitializing the Mutex ");
//   fflush(stdout);
   pthread_mutex_init(mutexsum, NULL);
}

void lockMutex(pthread_mutex_t *mutexsum)
{
//   fprintf(stderr,"\n Mutex is Locking ");
   pthread_mutex_lock (mutexsum);
}

int lockMutexAndWait(pthread_mutex_t *mutexsum)
{
   int errCode;
   int retval = 1;
   struct timespec abs_timeout;
//   fprintf(stderr, "\nWaiting for signal ");
//   fflush(stdout);
   
   clock_gettime(CLOCK_REALTIME, &abs_timeout); 
   abs_timeout.tv_sec += MUTEX_TIMEOUT;
   
//   fprintf(stderr,"\n WTMutex is Locked ");
   errCode = pthread_mutex_timedlock (mutexsum, &abs_timeout);
   if(errCode != 0)
   {
      printf("Errot Code %d" , errCode);
      retval = 0;
   }
   return retval;
}

void releaseMutex(pthread_mutex_t *mutexsum)
{
   
   /*fprintf(stderr,"\n Generating Signal ");
   fflush(stdout);
   fprintf(stderr,"\n Unlocking Mutex ");
   printf("Unlocking Error Code:: %d",pthread_mutex_unlock (mutexsum));
   fprintf(stderr,"\n Generated Signal ");
   fflush(stdout);*/
   
   pthread_mutex_unlock (mutexsum);
}

