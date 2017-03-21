
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

  #ifdef ENT_OAMS_PSSCM
     #undef ENT_OAMS_PSSCM
     #define ENT_OAMS_PSSCM 200
  #endif

  #ifdef ENT_PSAPP_PSMSH
     #undef ENT_PSAPP_PSMSH
     #define ENT_PSAPP_PSMSH 200
  #endif

  #ifdef ENT_OAMS_TRXH
     #undef ENT_OAMS_TRXH
     #define ENT_OAMS_TRXH 200
  #endif

  #ifdef ENT_CSAPP_GRHM
     #undef ENT_CSAPP_GRHM
     #define ENT_CSAPP_GRHM 200
  #endif

  #ifdef ENT_OAMS_CELLH
     #undef ENT_OAMS_CELLH
     #define ENT_OAMS_CELLH 200
  #endif

  #ifdef ENT_OAMS_GBH
     #undef ENT_OAMS_GBH
     #define ENT_OAMS_GBH 200
  #endif

 #endif /* __UT_TEST */ 

#endif
