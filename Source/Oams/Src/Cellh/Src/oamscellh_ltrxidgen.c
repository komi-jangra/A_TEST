#include <sysxxx_typedef.h>
#include <pthread.h>
#include <oamscellh_ltrxidgen.h>

pthread_mutex_t mutex;
static I_U32 ltrxId =0;
I_U32 retVal1 =0;

I_U32 GenerateLtrxId()
    {
     pthread_mutex_lock(&mutex);
		 findHighestLtrxId(&retVal1);
        if(retVal1 > ltrxId) 
				{				
				ltrxId = retVal1 + 1;
				}
				else
      	{
				ltrxId = ltrxId + 1;
				}
				
     pthread_mutex_unlock(&mutex);
     return(ltrxId);
    }

