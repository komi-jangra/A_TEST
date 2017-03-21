
/***********************************File Header ***************************
File Name        : oams_sig_handler.h
Purpose          : This file contains functions definitions for Signal Handling  
initialization methods.
Project          : BSC
Subsystem        : OAMS
Author           : VNL
Version          :
 ************************************* End **********************************/
#define BACK_TRACE_DEPTH   100
#define  REGISTER_CONTEXT(a,b,c) registerContext(a,b,c); 
#define  REGISTER_SIGNAL_HANDLER() registerSigHandler(); 

#ifdef BPM_PRESENT
#include <signal.h>
#include <string.h> //strsignal
#include <execinfo.h> //backtrace,backtrace_symbols
#include <ucontext.h> //ucontext_t
//Commented for cloud compile 16-Nov-16
#if 0
void printPpcContext(ucontext_t *uc)
{
  I_U32 i = 0;
  for (i=0; i < 32; i++) {
 	  LOG_PRINT(LOG_CRITICAL,"R%d [0x%x] [%u]",i,uc->uc_mcontext.regs->gpr[i],uc->uc_mcontext.regs->gpr[i]);
  }
 	LOG_PRINT(LOG_CRITICAL,"NIP       [0x%x] [%u]",uc->uc_mcontext.regs->nip,uc->uc_mcontext.regs->nip);
 	LOG_PRINT(CRITICAL,"MSR       [0x%x] [%u]",uc->uc_mcontext.regs->msr,uc->uc_mcontext.regs->msr);
 	LOG_PRINT(CRITICAL,"ORIG_GPR3 [0x%x] [%u]",uc->uc_mcontext.regs->orig_gpr3,uc->uc_mcontext.regs->orig_gpr3);
 	LOG_PRINT(CRITICAL,"CTR       [0x%x] [%u]",uc->uc_mcontext.regs->ctr,uc->uc_mcontext.regs->ctr);
 	LOG_PRINT(CRITICAL,"LINK      [0x%x] [%u]",uc->uc_mcontext.regs->link,uc->uc_mcontext.regs->link);
 	LOG_PRINT(CRITICAL,"XER       [0x%x] [%u]",uc->uc_mcontext.regs->xer,uc->uc_mcontext.regs->xer);
 	LOG_PRINT(CRITICAL,"CCR       [0x%x] [%u]",uc->uc_mcontext.regs->ccr,uc->uc_mcontext.regs->ccr);
 	LOG_PRINT(CRITICAL,"MQ        [0x%x] [%u]",uc->uc_mcontext.regs->mq,uc->uc_mcontext.regs->mq);
}
#endif

#else 
#define __USE_GNU
#include <signal.h>
#include <string.h> //strsignal
#include <execinfo.h> //backtrace,backtrace_symbols
#include <ucontext.h> //ucontext_t
void printIntelContext(ucontext_t *uc)
{
  LOG_PRINT(CRITICAL,"REG_GS  [0x%x] [%u]",uc->uc_mcontext.gregs[REG_GS],uc->uc_mcontext.gregs[REG_GS]);
 	LOG_PRINT(CRITICAL,"REG_FS  [0x%x] [%u]",uc->uc_mcontext.gregs[REG_FS],uc->uc_mcontext.gregs[REG_FS]);
 	LOG_PRINT(CRITICAL,"REG_ES  [0x%x] [%u]",uc->uc_mcontext.gregs[REG_ES],uc->uc_mcontext.gregs[REG_ES]);
 	LOG_PRINT(CRITICAL,"REG_DS  [0x%x] [%u]",uc->uc_mcontext.gregs[REG_DS],uc->uc_mcontext.gregs[REG_DS]);
 	LOG_PRINT(CRITICAL,"REG_CS  [0x%x] [%u]",uc->uc_mcontext.gregs[REG_CS],uc->uc_mcontext.gregs[REG_CS]);
 	LOG_PRINT(CRITICAL,"REG_SS  [0x%x] [%u]",uc->uc_mcontext.gregs[REG_SS],uc->uc_mcontext.gregs[REG_SS]);  
 	LOG_PRINT(CRITICAL,"REG_EDI [0x%x] [%u]",uc->uc_mcontext.gregs[REG_EDI],uc->uc_mcontext.gregs[REG_EDI]);
 	LOG_PRINT(CRITICAL,"REG_ESI [0x%x] [%u]",uc->uc_mcontext.gregs[REG_ESI],uc->uc_mcontext.gregs[REG_ESI]);
 	LOG_PRINT(CRITICAL,"REG_EBP [0x%x] [%u]",uc->uc_mcontext.gregs[REG_EBP],uc->uc_mcontext.gregs[REG_EBP]);
 	LOG_PRINT(CRITICAL,"REG_ESP [0x%x] [%u]",uc->uc_mcontext.gregs[REG_ESP],uc->uc_mcontext.gregs[REG_ESP]);
 	LOG_PRINT(CRITICAL,"REG_EBX [0x%x] [%u]",uc->uc_mcontext.gregs[REG_EBX],uc->uc_mcontext.gregs[REG_EBX]);
 	LOG_PRINT(CRITICAL,"REG_EDX [0x%x] [%u]",uc->uc_mcontext.gregs[REG_EDX],uc->uc_mcontext.gregs[REG_EDX]);
 	LOG_PRINT(CRITICAL,"REG_ECX [0x%x] [%u]",uc->uc_mcontext.gregs[REG_ECX],uc->uc_mcontext.gregs[REG_ECX]);
 	LOG_PRINT(CRITICAL,"REG_EAX [0x%x] [%u]",uc->uc_mcontext.gregs[REG_EAX],uc->uc_mcontext.gregs[REG_EAX]);
 	LOG_PRINT(CRITICAL,"REG_EIP [0x%x] [%u]",uc->uc_mcontext.gregs[REG_EIP],uc->uc_mcontext.gregs[REG_EIP]);
}
#endif

I_Void *contextData[10];
I_U16 dataSize[10];
I_U8 noOfContextReg;
void printBackTrace(ucontext_t *uc)
{
  void *BackTrace[BACK_TRACE_DEPTH];  
  char **messages = (char **)NULL;
  int i, BackTraceSize = 0;

  BackTraceSize = backtrace(BackTrace, BACK_TRACE_DEPTH);

  /* overwrite sigaction with caller's address */
  if (uc)  {
#ifdef BPM_PRESENT
#if 0
    BackTrace[2] = (void * )uc->uc_mcontext.regs->nip;
    BackTrace[3] = (void * )uc->uc_mcontext.regs->link;
#endif
#else
    BackTrace[2] = (void *)uc->uc_mcontext.gregs[REG_EIP];
#endif 
  }

  messages = backtrace_symbols(BackTrace, BackTraceSize);
  /* skip first stack frame (points here) */

  LOG_PRINT(LOG_CRITICAL,"[bt] Execution path:");

  for (i=2; i < BackTraceSize; ++i) {
    LOG_PRINT(CRITICAL,"[bt]#[%u]->%s",i-2,messages[i]);
  }  
}
void printContextDump()
{
  int i=0;
  for(i=0;i<noOfContextReg;i++){
    LOG_PRINT(LOG_INFO,"dumping context");
    PRINT_HEX_DUMP(LOG_INFO,contextData[i],dataSize[i]);
  }
}
void sigHandler(int signum, siginfo_t *sig_info, void *secret) 
{
  ucontext_t *uc = (ucontext_t *)secret;
  LOG_PRINT(CRITICAL,"%s Signal Recieved [%d  [%s]",__FUNCTION__,signum,strsignal(signum));

  if (signum == SIGSEGV) {
    LOG_PRINT(CRITICAL,"SIGSEGV Faulty Address is [%p]",sig_info->si_addr);
  }
  printContextDump();
#ifdef BPM_PRESENT        
#if 0        
  printPpcContext(uc);
#endif
#else 
  printIntelContext(uc);
#endif 
  printBackTrace(uc);

  signal(signum,SIG_DFL);
  kill(getpid(),signum); 
  return ;
}
void registerSigHandler()
{
   LOG_PRINT(LOG_INFO,"Entering function %s",__FUNCTION__);
  /* Install our signal handler */
  struct sigaction sa;

  sa.sa_sigaction = (void *)sigHandler;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_RESTART | SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGFPE , &sa, NULL);
  sigaction(SIGINT , &sa, NULL);
  sigaction(SIGQUIT , &sa, NULL);
  sigaction(SIGTERM , &sa, NULL);
  sigaction(SIGALRM , &sa, NULL);
  sigaction(SIGILL , &sa, NULL);
  /* ... add any other signal here */
  LOG_PRINT(LOG_INFO,"Exiting function %s",__FUNCTION__);
  return ;
}
registerContext(void *data, I_U16 size, I_U8 nth)
{
  if(nth > 10){
    return -1;
  }
  contextData[nth-1] = data;  
  dataSize[nth-1] = size;
}


