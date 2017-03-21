/*se ts=3************************************File Header********************************
File Name               :             swversion_parser.h
Purpose                 :             contains various hash defines used in different function 
Project                 :             BSC3.0
Subsystem               :             
Author                  :             
CSCI id                 :
Version                 :              
 *****************************************************************************************/

#ifndef __SWVERSION_PARSER_H
#define __SWVERSION_PARSER_H
#include "sysxxx_typedef.h"

#define SW_VER_SUCCESS 0
#define SW_VER_FAILURE -1
#define TOKENS_IN_STRING 3
#define MAX_DIGITS 3

I_S32 convertInputStringToNumber(I_U8 *inputString, I_U32 *numberOfTokens, I_U32 token[], I_U32 *errCause);
I_S32 convertInputNumberToString(I_U8 *swVersionBuffer, I_U8 swVersionLen, I_S8 *swVersionString);

#endif
