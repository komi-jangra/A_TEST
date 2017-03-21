#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#define __USE_GNU
#include <string.h> //strsignal
#include <execinfo.h> //backtrace,backtrace_symbols
#include <ucontext.h> //ucontext_t
#include <oamsbich_includes.h>
#define BACK_TRACE_DEPTH   100
//#define LOG_PRINT(x,y,args...) printf("\n");printf(y, ##args)

#ifdef BPM_PRESENT
void reg_sig_hndlr();

void print_ppc_context(ucontext_t *uc)
{
#if 0
  unsigned int i = 0;
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
#endif
}
#else 
void print_intel_context(ucontext_t *uc)
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

  LOG_PRINT(CRITICAL,"[bt] Execution path:");
  
  for (i=2; i < BackTraceSize; ++i) {
  	LOG_PRINT(CRITICAL,"[bt]#[%u]->%s",i-2,messages[i]);
  }  
}

void bsc_sighandler(int signum, siginfo_t *sig_info, void *secret) 
{
  ucontext_t *uc = (ucontext_t *)secret;


  LOG_PRINT(CRITICAL,"Got Signal [%d] [%s]",signum,strsignal(signum));
  
  if (signum == SIGSEGV) {
  	LOG_PRINT(CRITICAL,"SIGSEGV Faulty Address is [%p]",sig_info->si_addr);
  }
#ifdef BPM_PRESENT        
  print_ppc_context(uc);
#else 
  print_intel_context(uc);
#endif 
  printBackTrace(uc);
  printf("\n");

  signal(signum,SIG_DFL);

  kill(getpid(),signum); 

  return ;

}

void reg_sig_hndlr()
{
  /* Install our signal handler */
  struct sigaction sa;

  sa.sa_sigaction = (void *)bsc_sighandler;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_RESTART | SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGFPE , &sa, NULL);
  /* ... add any other signal here */
  
  return ;
}

