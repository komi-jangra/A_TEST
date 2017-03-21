/*se ts=3************************************File Header********************************
   File Name               :             swversion_parser.c
Purpose                 :             contains the functions used to convert the version in the 
string to number and number to string format. 
Project                 :             BSC3.0
Subsystem               :             
Author                  :             
CSCI id                 :
Version                 :              
 *****************************************************************************************/

#include <stdio.h>
#include<string.h>
#include <swversion_parser.h>
#include <oamomc_errorcodes.h>
#include "sysxxx_typedef.h"
#include "sysxxx_hashdefs.h"
#include <sysxxx_msgstruct.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
/********************************************************************
 *
 * FUNCTION NAME : convertToDec
 *
 * DESCRIPTION : This function will convert the software version token to numbers.
 *
 *               digitsString : points to the token array which is to be converted to number.
 *               numDigits    : stores the number of digits in the token.
 *               number       : points to the token which is converted to number.
 * RETURNS : 
 *            
 *
 *********************************************************************/

void convertToDec(I_CHAR *digitsString, I_U32 numDigits, I_U32 *number)
{
   I_U32 i = 0;
   I_U32 j = 0;
   *number = 0;
   I_U32 multipicator;
      LOG_PRINT(INFO,"digitsString = %s , numDigits = %d ",digitsString,numDigits);

   while (*(digitsString + i) != '\0')
   {
      multipicator = 1;
      for (j=0; j < ( numDigits - 1 ); j++)
      {
         multipicator*=10; 
      }
      (*number) += ( ( *(digitsString + i)) - '0' ) * multipicator;
      numDigits--; i++;
   }   
  
}


/********************************************************************
 *
 * FUNCTION NAME : convertInputStringToNumber
 *
 * DESCRIPTION : This function will convert the software version given in String foramt to numbers.
 *
 *               inputString    : points to the software version given in string format.
 *               numberOfTokens : points to number of tokens in the given string.
 *               token          : points to the tokens stored in an array after convertion.
 *               errCause       : points to the error caused in the convertion.
 * RETURNS : SW_VER_FAILURE / SW_VER_SUCCESS
 *            
 *
 *********************************************************************/
I_S32 convertInputStringToNumber(I_U8 *inputString, I_U32 *numberOfTokens, I_U32 token[], I_U32 *errCause)
{
   I_U32 i = 0;
   I_U32 j = 0;
   I_U32 noOfTokenReqInString = 3;
   //   I_U32 result = SW_VER_FAILURE;

   I_CHAR digitsString[MAX_DIGITS + 1];

   I_CHAR isFirstCharacter;
   if(*numberOfTokens == 4){
     noOfTokenReqInString = *numberOfTokens;
   }
   *numberOfTokens = 0;
   *errCause = CM_SUCCESS;   

      LOG_PRINT(INFO,"noOfTokenReqInString = %d",noOfTokenReqInString);
   while (*(inputString + i) != '\0')
   {
      if (*numberOfTokens == noOfTokenReqInString)
      {
         *errCause = CM_ERR_SW_VERSION_EXCEEDS_MAX_TOKENS;
         return SW_VER_FAILURE;
      }

      j = 0;
      isFirstCharacter = I_TRUE;
      while ( (*(inputString + i) != '.') &&  (*(inputString + i) != '\0') )
      {
         if ( *(inputString + i) < '0' || *(inputString + i) > '9')
         {
            *errCause = CM_ERR_SW_VERSION_INVALID_FORMAT;
            return SW_VER_FAILURE;
         }

         /*if ( isFirstCharacter == I_TRUE )
         {
            isFirstCharacter = I_FALSE;
            if  ( ( *(inputString + i)  == '0' ) && ( ( *(inputString + i + 1)  != '.' ) 
                     && ( *(inputString + i + 1)  != '\0' ) ) )
            {
               *errCause = CM_ERR_SW_VERSION_LEADING_ZEROS;
               return SW_VER_FAILURE;
            }
         }*/

         digitsString[j] = *(inputString + i);


         i++; j++;

         if ( j > MAX_DIGITS )
         {
            *errCause = CM_ERR_SW_VERSION_EXCEEDS_MAX_DIGITS;
            return SW_VER_FAILURE;
         }


      }

      if ( ( *(inputString + i) == '.')  && (j == 0) ) 
      {
         *errCause = CM_ERR_SW_VERSION_INVALID_FORMAT;
         return SW_VER_FAILURE;
      }

      if ( j > 0 )
      {
         digitsString[j] = '\0';
         convertToDec(digitsString, j, (token+ (*numberOfTokens)));
         
      LOG_PRINT(INFO,"token[%d] = %d",*numberOfTokens,token[(*numberOfTokens)]);
         (*numberOfTokens)++;
      }
    
      if ( *(inputString + i) == '.')
      {
         i++;
      }
   }   

   if (*numberOfTokens == 0)
   {
      *errCause = CM_ERR_SW_VERSION_INVALID_FORMAT;
      return SW_VER_FAILURE;
   }   

   if (*numberOfTokens != noOfTokenReqInString)
   {
      *errCause = CM_ERR_SW_VERSION_LESS_TOKENS_IN_STRING;
      return SW_VER_FAILURE;
   }
   return SW_VER_SUCCESS;   
}



/********************************************************************
 *
 * FUNCTION NAME : convertInputNumberToString
 *
 * DESCRIPTION : This function will convert the software version given in numbers to String format.
 *
 *               swVersionBuffer  : points to the software version buffer containing sw version in numbers.
 *               swVersionLen     : length of the buffer containing sw version .
 *               swVersionString  : points to the software version converted to string format.
 * RETURNS : SW_VER_FAILURE / SW_VER_SUCCESS
 *            
 *
 *********************************************************************/
I_S32 convertInputNumberToString(I_U8 *swVersionBuffer, I_U8 swVersionLen, I_S8 *swVersionString)
{
   int counter = 0;
   I_S8 tempBuffer[swVersionLen + 1];
   /*Check the length of recieved buffer */
/*   if (swVersionLen != TOKENS_IN_STRING)
   {
      LOG_PRINT(MAJOR,"Length of the received buffer,for conversion to string, is Incorrect");
      return SW_VER_FAILURE;
   } */
   sprintf(swVersionString,"%u",swVersionBuffer[0]);   
   for( counter =1 ; counter < swVersionLen; counter++ )
   {
      sprintf(tempBuffer,".%u",swVersionBuffer[counter]);
      strcat(swVersionString,tempBuffer);
      LOG_PRINT(INFO,"swVersionString = %s",swVersionString);
   }
   return SW_VER_SUCCESS;
}

