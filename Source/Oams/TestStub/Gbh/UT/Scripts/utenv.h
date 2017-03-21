
/* Include this file at the end of your module compiltation step */ 
/* Use the flag __UT_FLAG in your Makefile also */ 

#ifndef __UTENV_H_ 
#define __UTENV_H_ 

 #ifdef __UT_TEST

  #ifdef ENT_OAMS_CFG
     #undef ENT_OAMS_CFG
     #define ENT_OAMS_CFG 200
  #endif

  #ifdef ENT_PSSTK_GSAL
     #undef ENT_PSSTK_GSAL 
     #define ENT_PSSTK_GSAL 200
  #endif

  #ifdef ENT_OAMS_PSCH
     #undef ENT_OAMS_PSCH 
     #define ENT_OAMS_PSCH 200
  #endif

 #endif /* __UT_TEST */ 

#endif
