/*************************************************************
Generated for Telelogic Tau 3.0.0.0.2032 at Sat Dec 23 07:58:10 CET 2006
Copyright Telesoft Europe AB 1990-1991.
Copyright Telelogic Malmoe AB 1991-1994.
(c) 1994 - 2006 Copyright Telelogic AB.

This Program, supplied in source code, is owned by Telelogic 
and is protected by national copyright laws and international 
copyright treaties. Telelogic grants you the right to use this 
Program according to the terms and conditions in the Software License.

Under this License you may modify the Program for the purpose
of adapting it to your computer environment. You must reproduce 
and include any copyright and trademark notices on all copies of the 
source code.

Telelogic does not warrant that the Program will meet your
requirements or that the operation of the Program will be
uninterrupted and error free. You are solely responsible that the
selection of the Program and modifications of the source code
will achieve your intended results and that the results are actually
obtained.

Any modifications to the source code are done at your own risk 
and will void any support obligations or commitments made by Telelogic.
*************************************************************/


/* 
Filename: sctenv.c

     1.   The primary purpose of this file is to be a template for
          the standard signal I/O interface for an SDL system generated
          by SDL Suite.
     2.   The secondary purpose is to serve as a "dummy" for the
          user supplied environment module during early system
          testing.
     3.   Also included in this file are a set of rudimentary
          functions that can be used for signal and process
          logging in a target (or host) environment.

          All the C-functions in this file are intended to be 
          modified according to actual user requirements.
          Therefore, a good strategy is to leave an unmodified
          copy of this file in its original directory, and to 
          make any modifications in copies placed in other
          directories. The reason for this is that the standard
          Makefile which is supplied with the Master Library
          assumes that a compilable copy of this file resides
          in the $sdtdir/INCLUDE directory for the purpose
          in paragraph 2.

FILE INDEX
00   Include Files
01   Global Variables
02   Environment routines
03   Signal and Process logging
*/


/****+***************************************************************
00   Include Files
********************************************************************/

#include "scttypes.h"

/*
   Here is where you may include signal and process definitons from
   your SDL system.
   Prerequisite: either you have turned on the 'generate env header'
   option in the SDL Analyzer Generate Option menu or, you have a
   manually produced header file with SDL system definitions.
   Usage: replace MySDLSystemName with your SDL system name and
   remove the comment characters surrounding the include statment
   below. */
/*
#include "MySDLSystemName.ifc"
*/

#ifdef XENV
/****+***************************************************************
01   Global Variables
********************************************************************/
#ifndef XREADANDWRITEF
#ifdef XSIGLOG
#include <stdio.h>
#endif
#endif


/****+***************************************************************
02   Environment routines
********************************************************************/

/*---+---------------------------------------------------------------
     xGlobalNodeNumber
-------------------------------------------------------------------*/
int xGlobalNodeNumber(void)
{
/*
   Assign a unique global system Id to each SDL system in a cluster of
   systems.
*/
  return 1;
}

/*---+---------------------------------------------------------------
     xInitEnv
-------------------------------------------------------------------*/
void xInitEnv(void)
{
/*
   Code to initialize your SDL-system environment may be inserted here.
*/

#ifdef XTRACE
  xPrintString("xInitEnv: Called but did nothing!\n");
#endif
}

/*---+---------------------------------------------------------------
     xCloseEnv
-------------------------------------------------------------------*/
void xCloseEnv(void)
{
/*
   Code to bring down the environment in a controlled manner
   may be inserted here.
*/

#ifdef XTRACE
  xPrintString("xCloseEnv: Called but did nothing!\n");
#endif
}

/*---+---------------------------------------------------------------
     xOutEnv
-------------------------------------------------------------------*/
void xOutEnv( xSignalNode  *S ) 
{

/*
   Below is a template for a xOutEnv implementation.
*/

/*
  if ( ((*S)->NameNode) == Actual_SDL_SignalName ) {
    
   --   Insert the proper code here in order to perform the necessary
   --   actions due to the signal sent from the SDL system. The code
   --   below gives an example of how to retrieve the SDL signal
   --   parameters.
   --   MyVar_x must be visible in this function and of the same
   --   types as the corresponding signal parameters, unless you
   --   use an extra cast operator in the assignment statements
   --   for type conversion.
    
   MyVar_1 = ( (yPDP_Actual_SDL_SignalName)(*S) )->Param1;
   MyVar_2 = ( (yPDP_Actual_SDL_SignalName)(*S) )->Param2;
   .
   .
   MyVar_i = ( (yPDP_Actual_SDL_SignalName)(*S) )->Parami;

   --   Release ( deallocate ) the SDL-signal. 
   xReleaseSignal( S );
   return;
  }
   
  --   Repeat the above "if"-statement for each SDL signal sent to
  --   the system environment.
*/

/*
   The code below, controlled by the XTRACE macro, is an option for
   limited host debugging of the environment module.
*/
#ifdef XTRACE
#ifdef XIDNAMES
  char  Temp[100];
  sprintf(Temp, "xOutEnv:  %s has been received by Env:1\n",
          (*S)->NameNode->Name );
  xPrintString(Temp);
#else
  xPrintString("xOutEnv:  One signal has been received by Env:1\n");
#endif
#endif


  /* discard all unimplemented signals */
  xReleaseSignal( S );
}

/*---+---------------------------------------------------------------
     xInEnv
-------------------------------------------------------------------*/
#ifndef XTENV
void xInEnv (SDL_Time Time_for_next_event)
#else
SDL_Duration xInEnv (SDL_Time Time_for_next_event)
#endif
{
  xSignalNode S; /* declare a variable that points to a SDL-signal */
 
#ifdef XTRACE
/* This section is only for textual trace and may be removed */
  xPrintString( "xInEnv: Called!\n");
#endif

/*
   Below is a template for a xInEnv implementation.
   Time_for_next_event may be used to break the polling loop
   in a time critical system.
*/

/*
      -- AnyInputActive must be redefined by the user, possibly
      -- implemented as a C-function
*/

#define AnyInputActive 1

  while( AnyInputActive ){

/*    -- Poll all your possible inputs in this while loop 
 
  if ( Input_1_Active ){
      --  the Input_1_Active function or expression
      --  must be supplied by the user

      -- Create an SDL_Signal and specify receiver and sender
     S = xGetSignal( ActualSDL_SignalName,  xNotDefPId,   xEnv );
      --                                         ^          ^
      --                                         |          |
      --                                     Receiver ,  Sender

      --  copy your data (if any ) into the appropriate signal
      --  parameters.

      --  Load 1st parameter
     ((yPDP_ActualSDL_SignalName)S)->Param1 = MyData_1;
     .
     .
      -- Load n-th parameter
     ((yPDP_ActualSDL_SignalName)S)->Paramn = MyData_n;

      -- Send the signal to the SDL system
  SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
  } --end of "Input_1_Active"

  if ( Input_2_Active ){ ......
  }
  .
  .
  if ( Input_n_Active ){ ......
  }
*/

/*
   If you have time critical regions in your SDL application, 
   you may use a construct similar to the one below
   to service that critical event (timer). The effect is 
   that you make an immediate return to the SDL-system
   when the test below is TRUE.
*/
  if ( xLE_SDL_Time( Time_for_next_event, SDL_Now()) ) break;

  } /* end of while loop */

#ifdef XTENV
 return SDL_Time_Lit((xint32)0,(xint32)0);
#endif
}
#endif


/****+***************************************************************
03   Signal and Process logging
********************************************************************/

#ifdef XSIGLOG
/*
   Replace "(void)putchar(P)" with your function that sends
   one character to the appropriate log device.
   XPOST_MORTEM_TRACE writes the trace on a ring buffer
   instead of to some output port ( default sdtout ).
*/
#ifndef XPOST_MORTEM_TRACE

#define xPut( P )   (void)putchar( P )

#else
/*
   This section writes the last trace messages on to a ring
   buffer for 'post-mortem' analysis. The last written entry
   as suffixed by a '*'. To output this buffer to the appropriate
   port you may use a function like the one below, activated by
   some unused interrupt.
   void _interrupt_n coredump()
    {
     int i;
     for (i = 0; i < PMBUFF ; *Port_n = xPostMortemBuffer[i++]);
    }
*/
#define xPut( P )   xPostMortemPutchar( P )

#ifndef PMBUFF
#define PMBUFF 0x100
#endif
char   xPostMortemBuffer[PMBUFF];

static void xPostMortemPutchar( char C )
{
  static char *xPostMortemPrintAt = xPostMortemBuffer ;
  *xPostMortemPrintAt = xPostMortemBuffer ;

  if ( xPostMortemPrintAt >= (xPostMortemBuffer + PMBUFF) )
    xPostMortemPrintAt = xPostMortemBuffer;
  *xPostMortemPrintAt++ = C;
  *xPostMortemPrintAt = '*';
}
#endif

/*---+---------------------------------------------------------------
     xPutString
-------------------------------------------------------------------*/
static void xPutString ( char * StrPtr )
{
  while( *StrPtr != '\0' ) { xPut( *StrPtr++ ); }
}

/*---+---------------------------------------------------------------
     xSignalLog
-------------------------------------------------------------------*/
void xSignalLog  (
  xSignalNode Signal,
  int         NrOfReceivers,
  xIdNode    *Path,
  int         PathIndex )
{
  /* Note that if XOPTCHAN is defined, the parameters Path and
     PathIndex will not contain any information */

  if (Signal->NameNode->EC == xStartUpSignalEC) {
    xPutString( "CREATE " );
    xPutString( Signal->Receiver.LocalPId->PrsP->NameNode->Name );
    xPutString("\n");
  } else {
    if (NrOfReceivers != 1)
      xPutString( "ERROR in " );
    else if (Signal->NameNode->EC == xTimerEC)
      xPutString( "TIMER " );
    xPutString( "OUTPUT ");
    xPutString( Signal->NameNode->Name );
    if (!xEq_SDL_PId_NULL(Signal->Receiver))
      if (Signal->Receiver.LocalPId->PrsP->NameNode != (xPrsIdNode)0){
        xPutString( " TO " );
        xPutString( Signal->Receiver.LocalPId->PrsP->NameNode->Name );
      }
    xPutString("\n");
  }
}

/*---+---------------------------------------------------------------
     xProcessLog
-------------------------------------------------------------------*/
void xProcessLog (xPrsNode P)
{
  xPutString("\n");
  if (P->Signal->NameNode->EC == xStartUpSignalEC) {
    xPutString( "START TRANSITION BY " );
    xPutString( P->NameNode->Name );
    xPutString("\n");
  } else {
    xPutString( "INPUT " );
    xPutString( P->Signal->NameNode->Name );
    xPutString( " BY PROCESS " );
    xPutString( P->NameNode->Name );
    xPutString( " IN STATE " );
    xPutString( P->NameNode->StateList[P->State]->Name );
    xPutString("\n");
    if (P->ActivePrd != (xPrdNode)0) {
      xPutString( "            IN PROCEDURE " );
      xPutString( P->ActivePrd->NameNode->Name );
      xPutString( " IN STATE " );
      xPutString( P->ActivePrd->NameNode->StateList
                    [P->ActivePrd->State]->Name );
      xPutString("\n");
    }
  }
}

#endif
       /* XSIGLOG */
