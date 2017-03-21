
#ifndef __OAMS_GBH_DATASTRUCT_H
#define __OAMS_GBH_DATASTRUCT_H
 /* Changes for HotStb start here     */
typedef struct 
{
  I_U16 gbIfIndex;
  I_U16 nsvcEnabled;
  I_U32 sigBvcResetFromSgsn;
  I_U32 cblNegotiated;
  I_U8 isCblChanged;
}GbhRedCtxt;
 /* Changes for HotStb end here     */

#endif 
