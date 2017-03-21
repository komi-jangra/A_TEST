////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.2  2007/09/13 03:12:30  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.2  2007/07/25 07:49:13  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:07  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 9.1.8.3  2005/11/28 13:11:10  adutta
// LOG: Return for ExcuteNotDefined function
// LOG:
// LOG: Revision 9.1.8.2  2005/11/17 06:36:12  adutta
// LOG: ProcessEvent returning success/fail
// LOG:
// LOG: Revision 9.1.8.1  2005/08/29 09:25:00  adutta
// LOG: Handling of undefined events
// LOG:
// LOG: Revision 9.2  2005/07/11 04:46:41  adutta
// LOG: Handling of erroneous events
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:46  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.6  2001/03/15 01:27:10  mmiers
// LOG: Updates for portability (fsm).  I think these were required anyway,
// LOG: but VC doesn't complain if they aren't there.  The rest is thinking
// LOG: about the thread pools.  I think I have a handle on this if I can
// LOG: remember it tomorrow.  The comments should help.
// LOG:
// LOG: Revision 3.5  2001/03/06 23:54:43  mmiers
// LOG: Shrink comment blocks for readability.
// LOG:
// LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
// LOG: Convert RCSID to ident.
// LOG:
// LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
// LOG: Move log back (more complaints than applause).
// LOG: Make C service take event log.
// LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
// LOG: bindings).
// LOG:
// LOG: Revision 3.2  2001/01/30 18:11:33  mmiers
// LOG: Demo log at bottom of file.
// LOG:
// LOG: Revision 3.1  2000/08/16 00:03:13  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.1  2000/06/13 19:15:53  mmiers
// LOG:
// LOG: C++ assertion no longer throws exception by default.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:25:35  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.5  1999/07/07 18:28:51  mmiers
// LOG:
// LOG:
// LOG: Formatting, possible collision with template type names on Unix.
// LOG:
// LOG: Revision 1.4  1998/06/05 01:51:17  hdivoux
// LOG: Added documentation.
// LOG:
// LOG: Revision 1.3  1998/05/08 22:50:48  hdivoux
// LOG: Added prefix ITS_.
// LOG:
// LOG: Revision 1.2  1998/05/06 15:17:45  hdivoux
// LOG: Corrections after review.
// LOG:
// LOG: Revision 1.1  1998/05/05 23:15:11  hdivoux
// LOG: Creation.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////

//
//
//   Interfaces of the Finite State Machine classes.
//
//


#if !defined(_ITS_FSM_H_)
#define _ITS_FSM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif    // defined(WIN32)

#include <map>
#include <functional>

#include <its++.h>    // For ITS_NAMESPACE.
#include <its_exception.h>

#ident "$Id: its_fsm.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)


// Forward declarations.
class BasicEvent;

template <class _F_, class _E_>
class State;

template <class _F_, class _E_>
class Transition;

template <class _F_>
class BasicState;



//.interface:FiniteStateMachine
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      FiniteStateMachine
//
//  Purpose:
//      Finite state machine base class. Abstraction of a finite state machine.
//
//  Usage:
//      To be Used in association with the other finite state machine related
//      classes. These others classes represent the following abstractions:
//
//      o State.
//      o Transition.
//      o Event.
//      o Sub finite state machine (a special state).
//
//      The object-oriented model used is one of the most complete to implement
//      the concept of finite state machines with an object-oriented language
//      like C++. Everything is represented by an object, especially each 
//      transition is an object. Another possible model (simpler but less
//      powerful) do not consider transitions to be objects.
//
//      The relationships between the objects of the model (at runtime) are the
//      following:
//
//      o A state machine contains one or more states ("has a" relationship).
//
//      o A state machine contains one or more possible transitions ("has a"
//        relationship). Each transition is usually defined between two states.
//        Usually, because it is also possible to define a transition with one
//        originating state and two potential destination states (binary
//        transition versus ternary transition).
//              
//          -----------             -----------
//          | state A |  -------->  | state B |
//          -----------             -----------
//           
//                 - binary transition -
//
//
//          -----------             -----------
//          | state A |  -------->  | state B |
//          -----------      |      -----------
//                           |
//                           |      -----------
//                            --->  | state C |
//                                  -----------
//
//                 - ternary transition -
//
//        In the case of a ternary transition, the actual return state is chosen
//        during the transition itself. See the class TernaryTransition for
//        more information.
//
//      o A state contains the association between each relevant transition (for
//        this state) and an event identifier (an event identifier is
//        implemented as an ITS_UINT and is considered to be unique).
//        
//
//      Simple description of the algorithm used:
//      -----------------------------------------
//
//      A state machine is event driven. A state machine is always in a defined
//      state named current state. When a state machine process an incoming
//      event, it simply asks the current state to actually process the event.
//      From the incoming event, the current state retrieves the event 
//      identifier and then searches for the associated transition. When the
//      associated transition is found the next state can be figured out. The
//      state machine current state is then updated with the new state.
//      
//      Design principles:
//      ------------------
//
//      ----[1]----
//
//      C++ genericity (i.e. C++ templates) is used to parameterize with an
//      event type the classes representing the following abstractions:
//
//      o State machine.
//      o State.
//      o Transition.
//      o Sub finite state machine.
//
//      The only assumption done is that it must be possible to get a unique 
//      event identifier (ITS_UINT) from an event object. The event type
//      generic parameter is named _E_ (see class definitions that include
//      <..., class _E_, ...>).
//      
//      A class named BasicEvent is also proposed. BasicEvent includes
//      only an attribute representing an event identifier and the associated
//      get/set member functions. Typical use is to inherit from BasicEvent.
//      All the classes named Basic... implement BasicEvent as the event
//      type generic parameter. These classes are direct instances of more
//      generic classes. 
//
//      ----[2]---- 
//
//      C++ genericity is also used to provide to classes that represent state
//      and transition abstractions a direct view on their associated state
//      machine. For instance this can give all the states of a particular 
//      finite state machine the ability to share common data (stored in the
//      state machine itself). The finite state machine generic parameter is
//      named _F_ (see class definitions that include: <..., class _F_,...>).
//
//      The same mechanism is used to provide to a binary transition abstraction
//      a direct view to its originating state and destination state. The
//      corresponding generic parameters are named SOrig and SDest (see class
//      definitions that include: <..., class SOrig, class SDest, ...>).
//
//      ----[3]---- 
//
//      Specific processing can be added to a transition (or to each transition).
//      There are two different ways to do it:
//
//      o To inherit from a class transition and redefine the virtual member
//        function named Execute (this function take the incoming event as an
//        argument). This could imply to create a lot of classes by inheritance.
//
//      o To use a special transition class that allows to set a pointer to a
//        function to be executed during the transition (see the class named
//        BasicFunctionalTransition).
//        
//      ----[4]----
//
//      Specific processing can be added to a state (or to each state):
//      
//      o Each time the associated finite state machine go in a state.
//
//      o Each time the associated finite state machine go out of a state.
//
//      Note that if specific transition processing is also executed, the order
//      of the executions is the following:
//
//          -----------   transition A to B    -----------
//          | state A |  ------------------->  | state B |
//          -----------                        -----------
//
//      o transistion A to B specific processing.
//
//      o go out of state A specific processing.
//
//      o go in state B specific processing.
//
//      Beware that transition A to B specific processing is done before go out
//      of state A specific processing.
//      
//      The usual way to add specific processing to a state is to inherit from a
//      state class and redefine the virtual member functions named ExecuteIn 
//      and ExecuteOut.
//
//      ----[5]----
//
//      A sub finite state machine abstraction is also proposed. A sub finite 
//      state machine inherits conceptually from the state and finite state
//      machine abstractions. Inheritance is conceptual, because in practice C++
//      multiple inheritance is not used to simplify the task of the C++
//      compiler. Consequently the code is simply duplicated. 
//
//      When an incoming event is processed by a state that is also a sub finite
//      state machine then the algorithm retrieves the event identifier and
//      starts searching for an associated transition. If the associated 
//      transition is found within the sub finite state machine then the current
//      state of the sub finite state machine is updated with a new state. If
//      the transition is not found within the sub finite state machine, then 
//      the algorithm starts searching for an associated transition in the
//      parent finite state machine. If the associated transition is found, then
//      the parent finite state machine current state is updated with a new
//      state.
//
//      How to use example 1:
//      ---------------------
//
//      The classes parameterized by BasicEvent are used. 
//
//      Simple finite state machine with three states (A, B, C) and three 
//      transitions:
//        
//            -----------   transition A to B    -----------
//            | state A |  ------------------->  | state B |
//            -----------                        -----------   
//                 ^                                   |
//                 |                                   |
//                 |                                   |
//                 |                                   |
//                 |                                   |
//                 |           -----------             |
//                  ---------- | state C | <-----------
//         transition C to A   -----------   transition B to C
//         
//            
//      Code to define the different classes:
//
//
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Begin code ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      
//      class EventABC : public BasicEvent
//      {
//      public:
//      
//          EventABC(ITS_UINT idParam) : BasicEvent(idParam)
//          {};
//      };
//      
//      
//      // Forward declaration.
//      class FsmABC;
//      
//      void TransitionFunctionCToA(
//                          BasicFunctionalTransition<FsmABC>& transition,
//                          FsmABC& finiteStateMachine,
//                          BasicState<FsmABC>& stateOrig,
//                          BasicState<FsmABC>& stateDest,
//                          BasicEvent& event)
//      {
//          cout << "Inside transition function (C to A)..." << endl;
//      }
//      
//      
//      class FsmABC : public FiniteStateMachine<BasicEvent>
//      {
//      public:
//      
//          FsmABC()
//          {
//              stateA = new StateA(*this);
//              stateB = new StateB(*this);
//              stateC = new StateC(*this);
//      
//              SetInitialState(
//                  reinterpret_cast<
//                      State<FiniteStateMachine<BasicEvent>,
//                          BasicEvent>&>
//                              (*stateA));
//      
//              transitionAToB = 
//                  new BasicTransition<FsmABC>(
//                                              *this,
//                                              *stateA,
//                                              *stateB);
//      
//              transitionBToC = 
//                  new BasicTransition<FsmABC>(
//                                              *this,
//                                              *stateB,
//                                              *stateC);
//      
//              transitionCToA =  
//                  new BasicFunctionalTransition<FsmABC>(
//                                                          *this,
//                                                          *stateC,
//                                                          *stateA);
//      
//              transitionCToA->SetFunction(TransitionFunctionCToA);
//      
//              stateA->DefineTransition(*transitionAToB, 1);
//              stateB->DefineTransition(*transitionBToC, 2);
//              stateC->DefineTransition(*transitionCToA, 3);
//          }
//      
//          virtual ~FsmABC()
//          {
//              delete stateA;
//              delete stateB;
//              delete stateC;
//      
//              delete transitionAToB;
//              delete transitionBToC;
//              delete transitionCToA;
//          }
//      
//          class StateA : public BasicState<FsmABC> 
//          {
//          public:
//              StateA(FsmABC& fsmParam) : BasicState<FsmABC>(fsmParam)
//              {};
//      
//              virtual ~StateA()
//              {};
//      
//              void ExecuteIn(BasicEvent& event)
//              { cout << "Go in state A..." << endl; }
//      
//              void ExecuteOut(BasicEvent& event)
//              { cout << "Go out of state A..." << endl; }
//          };
//      
//          class StateB : public BasicState<FsmABC> 
//          {
//          public:
//              StateB(FsmABC& fsmParam) : BasicState<FsmABC>(fsmParam)
//              {};
//      
//              virtual ~StateB()
//              {};
//      
//              void ExecuteIn(BasicEvent& event)
//              { cout << "Go in state B..." << endl; }
//      
//              void ExecuteOut(BasicEvent& event)
//              { cout << "Go out of state B..." << endl; }
//          };
//      
//          class StateC : public BasicState<FsmABC> 
//          {
//          public:
//              StateC(FsmABC& fsmParam) : BasicState<FsmABC>(fsmParam)
//              {};
//      
//              virtual ~StateC()
//              {};
//      
//              void ExecuteIn(BasicEvent& event)
//              { cout << "Go in state C..." << endl; }
//      
//              void ExecuteOut(BasicEvent& event)
//              { cout << "Go out of state C..." << endl; }
//          };
//      
//          StateA* stateA;
//          StateB* stateB;
//          StateC* stateC;
//      
//          BasicTransition<FsmABC>* transitionAToB;
//          BasicTransition<FsmABC>* transitionBToC;
//          BasicFunctionalTransition<FsmABC>* transitionCToA;
//      };
//
//
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ End of code ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
//
//      A simple function to use the previous code is:
//
//
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Begin code ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
//      void Test1()
//      {
//          EventABC event1(1);
//          EventABC event2(2);
//          EventABC event3(3);
//      
//          FsmABC fsmABC;
//      
//          fsmABC.ProcessEvent(event1);
//          fsmABC.ProcessEvent(event2);
//          fsmABC.ProcessEvent(event3);
//      }
//
//
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ End of code ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
//
//      When executed, the function Test1 should produce the following
//      outputs:
//
//      Go out of state A...
//      Go in state B...
//      Go out of state B...
//      Go in state C...
//      Inside transition function (C to A)...
//      Go out of state C...
//      Go in state A...
//
//
//      How to use example 2:
//      ---------------------
//
//      The classes parameterized by BasicEvent are used. 
//
//      Simple finite state machine with three states (X, Y, Z). State Y 
//      is a sub finite state machine with also three states (R, S, T).
//        
//            -----------   transition X to Y    -----------
//            | state X |  ------------------->  | state Y |
//            -----------                        -----------   
//                 ^                                   |
//                 |                                   |
//                 |                                   |
//                 |                                   |
//                 |                                   |
//                 |           -----------             |
//                  ---------- | state Z | <-----------
//         transition Z to Y   -----------   transition Y to Z
//
//
//         State Y is a sub finite state machine:
//       ----------------------------------------------------------
//       |                                                        |
//       |     -----------   transition R to S    -----------     |
//       |     | state R |  ------------------->  | state S |     |
//       |     -----------                        -----------     |
//       |          ^                                   |         |
//       |          |                                   |         |
//       |          |                                   |         |
//       |          |                                   |         |
//       |          |                                   |         |
//       |          |           -----------             |         |
//       |           ---------- | state T | <-----------          |
//       |  transition T to R   -----------   transition S to T   |
//       |                                                        |
//       ----------------------------------------------------------
//        
//            
//      Code to define the different classes:
//
//
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Begin code ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
//      class EventXYZ : public BasicEvent
//      {
//      public:
//      
//          EventXYZ(ITS_UINT idParam) : BasicEvent(idParam)
//          {};
//      };
//      
//      
//      // Forward declaration.
//      
//      class FsmXYZ;
//      
//      void TransitionFunctionZToX(
//                          BasicFunctionalTransition<FsmXYZ>& transition,
//                          FsmXYZ& finiteStateMachine,
//                          BasicState<FsmXYZ>& stateOrig,
//                          BasicState<FsmXYZ>& stateDest,
//                          BasicEvent& event)
//      {
//          cout << "Inside transition function (Z to X)..." << endl;
//      }
//      
//      
//      class FsmXYZ : public FiniteStateMachine<BasicEvent>
//      {
//      public:
//      
//          FsmXYZ()
//          {
//              stateX = new StateX(*this);
//              stateY = new StateY(*this);
//              stateZ = new StateZ(*this);
//      
//              SetInitialState(
//                  reinterpret_cast<
//                      State<FiniteStateMachine<BasicEvent>,
//                          BasicEvent>&>
//                              (*stateX));
//      
//              transitionXToY = 
//                  new BasicTransition<FsmXYZ>(
//                                              *this,
//                                              *stateX,
//                                              *stateY);
//      
//              transitionYToZ = 
//                  new BasicTransition<FsmXYZ>(
//                                              *this,
//                                              *stateY,
//                                              *stateZ);
//      
//              transitionZToX = 
//                  new BasicFunctionalTransition<FsmXYZ>(
//                                                          *this,
//                                                          *stateZ,
//                                                          *stateX);
//      
//              transitionZToX->SetFunction(TransitionFunctionZToX);
//      
//              stateX->DefineTransition(*transitionXToY, 1);
//              stateY->DefineTransition(*transitionYToZ, 2);
//              stateZ->DefineTransition(*transitionZToX, 3);
//          }
//      
//          virtual ~FsmXYZ()
//          {
//              delete stateX;
//              delete stateY;
//              delete stateZ;
//      
//              delete transitionXToY;
//              delete transitionYToZ;
//              delete transitionZToX;
//          }
//      
//          // Forward declaration.
//      
//          class StateY;
//      
//          static void TransitionFunctionTToR(
//                          BasicFunctionalTransition<StateY>& transition,
//                          StateY& finiteStateMachine,
//                          BasicState<StateY>& stateOrig,
//                          BasicState<StateY>& stateDest,
//                          BasicEvent& event)
//          {
//              cout << "Inside transition function (T to R)..." << endl;
//          }
//      
//          class StateX : public BasicState<FsmXYZ> 
//          {
//          public:
//              StateX(FsmXYZ& fsmParam) : BasicState<FsmXYZ>(fsmParam)
//              {};
//      
//              virtual ~StateX()
//              {};
//      
//              void ExecuteIn(BasicEvent& event)
//              { cout << "Go in state X..." << endl; }
//      
//              void ExecuteOut(BasicEvent& event)
//              { cout << "Go out of state X..." << endl; }
//          };
//      
//      
//          class StateY : public BasicSubFiniteStateMachine<FsmXYZ> 
//          {
//          public:
//              StateY(FsmXYZ& fsmParam)
//              :    BasicSubFiniteStateMachine<FsmXYZ>(fsmParam)
//              {
//                  stateR = new StateR(*this);
//                  stateS = new StateS(*this);
//                  stateT = new StateT(*this);
//      
//                  SetInitialState(
//                      reinterpret_cast<
//                          BasicState<
//                              BasicSubFiniteStateMachine<FsmXYZ>
//                                  >&>(*stateR));
//      
//                  transitionRToS = 
//                      new BasicTransition<StateY>(
//                                                  *this,
//                                                  *stateR,
//                                                  *stateS);
//      
//                  transitionSToT = 
//                      new BasicTransition<StateY>(
//                                                  *this,
//                                                  *stateS,
//                                                  *stateT);
//      
//                  transitionTToR = 
//                      new BasicFunctionalTransition<StateY>(
//                                                              *this,
//                                                              *stateT,
//                                                              *stateR);
//      
//                  transitionTToR->SetFunction(TransitionFunctionTToR);
//      
//                  stateR->DefineTransition(*transitionRToS, 4);
//                  stateS->DefineTransition(*transitionSToT, 5);
//                  stateT->DefineTransition(*transitionTToR, 6);
//              }
//              
//              virtual ~StateY()
//              {
//                  delete stateR;
//                  delete stateS;
//                  delete stateT;
//      
//                  delete transitionRToS;
//                  delete transitionSToT;
//                  delete transitionTToR;
//              };
//      
//              void ExecuteIn(BasicEvent& event)
//              { cout << "Go in state Y..." << endl; }
//      
//              void ExecuteOut(BasicEvent& event)
//              { cout << "Go out of state Y..." << endl; }
//      
//              class StateR : public BasicState<StateY>
//              {
//              public:
//                  StateR(StateY& fsmParam) : BasicState<StateY>(fsmParam)
//                  {};
//      
//                  virtual ~StateR()
//                  {};
//      
//                  void ExecuteIn(BasicEvent& event)
//                  { cout << "Go in state R..." << endl; }
//      
//                  void ExecuteOut(BasicEvent& event)
//                  { cout << "Go out of state R..." << endl; }
//              };
//      
//              class StateS : public BasicState<StateY>
//              {
//              public:
//                  StateS(StateY& fsmParam) : BasicState<StateY>(fsmParam)
//                  {};
//      
//                  virtual ~StateS()
//                  {};
//      
//                  void ExecuteIn(BasicEvent& event)
//                  { cout << "Go in state S..." << endl; }
//      
//                  void ExecuteOut(BasicEvent& event)
//                  { cout << "Go out of state S..." << endl; }
//              };
//      
//              class StateT : public BasicState<StateY>
//              {
//              public:
//                  StateT(StateY& fsmParam) : BasicState<StateY>(fsmParam)
//                  {};
//      
//                  virtual ~StateT()
//                  {};
//      
//                  void ExecuteIn(BasicEvent& event)
//                  { cout << "Go in state T..." << endl; }
//      
//                  void ExecuteOut(BasicEvent& event)
//                  { cout << "Go out of state T..." << endl; }
//              };
//      
//              StateR* stateR;
//              StateS* stateS;
//              StateT* stateT;
//      
//              BasicTransition<StateY>* transitionRToS;
//              BasicTransition<StateY>* transitionSToT;
//              BasicFunctionalTransition<StateY>* transitionTToR;
//          };
//      
//          class StateZ : public BasicState<FsmXYZ> 
//          {
//          public:
//              StateZ(FsmXYZ& fsmParam) : BasicState<FsmXYZ>(fsmParam)
//              {};
//      
//              virtual ~StateZ()
//              {};
//      
//              void ExecuteIn(BasicEvent& event)
//              { cout << "Go in state Z..." << endl; }
//      
//              void ExecuteOut(BasicEvent& event)
//              { cout << "Go out of state Z..." << endl; }
//          };
//      
//          StateX* stateX;
//          StateY* stateY;
//          StateZ* stateZ;
//      
//          BasicTransition<FsmXYZ>* transitionXToY;
//          BasicTransition<FsmXYZ>* transitionYToZ;
//          BasicFunctionalTransition<FsmXYZ>* transitionZToX;
//      };
//
//
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ End of code ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
//
//      A simple function to use the previous code is:
//
//
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Begin code ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
//      void Test2()
//      {
//          EventXYZ event1(1);
//          EventXYZ event2(2);
//          EventXYZ event3(3);
//          EventXYZ event4(4);
//          EventXYZ event5(5);
//          EventXYZ event6(6);
//      
//          FsmXYZ fsmXYZ;
//      
//          cout << endl << "Going to process event 1..." << endl << endl;
//          fsmXYZ.ProcessEvent(event1);
//      
//          cout << endl << "Going to process event 4..." << endl << endl;
//          fsmXYZ.ProcessEvent(event4);
//      
//          cout << endl << "Going to process event 5..." << endl << endl;
//          fsmXYZ.ProcessEvent(event5);
//      
//          cout << endl << "Going to process event 6..." << endl << endl;
//          fsmXYZ.ProcessEvent(event6);
//      
//          cout << endl << "Going to process event 2..." << endl << endl;
//          fsmXYZ.ProcessEvent(event2);
//      
//          cout << endl << "Going to process event 3..." << endl << endl;
//          fsmXYZ.ProcessEvent(event3);
//      }
//
//
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ End of code ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//
//
//      When executed, the function Test2 should produce the following
//      outputs:
//
//      Going to process event 1...
//      
//      Go out of state X...
//      Go in state Y...
//      Go in state R...
//      
//      Going to process event 4...
//      
//      Go out of state R...
//      Go in state S...
//      
//      Going to process event 5...
//      
//      Go out of state S...
//      Go in state T...
//      
//      Going to process event 6...
//      
//      Inside transition function (T to R)...
//      Go out of state T...
//      Go in state R...
//      
//      Going to process event 2...
//      
//      Go out of state R...
//      Go out of state Y...
//      Go in state Z...
//      
//      Going to process event 3...
//      
//      Inside transition function (Z to X)...
//      Go out of state Z...
//      Go in state X...
//
//       
//
////////////////////////////////////////////////////////////////////////////////

//.interface:BasicEvent
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      BasicEvent
//
//  Purpose:
//      Finite state machine basic event abstraction. Base class of all
//      basic events. Used as the event type generic parameter for all the
//      classes named Basic...
//
//  Usage:
//      Directly or by inheritance to define a hierarchy of class events. See
//      interface FiniteStateMachine for more informations.
//
////////////////////////////////////////////////////////////////////////////////
class BasicEvent
{
public:

    //.implementation:public,inline,BasicEvent
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      idParam - event identifier.
    //
    //  Notes:
    //      Within a finite state machine (or more precisely within a state), an
    //      event identifier must be unique.
    //
    ////////////////////////////////////////////////////////////////////////////
    BasicEvent(ITS_UINT idParam)
        : id(idParam)
    {}
    //.implementation:public,inline,BasicEvent
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
  virtual ~BasicEvent()
    {}

    //.implementation:public,inline,BasicEvent
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To get the event identifier.
    //
    //  Return Value:
    //      ITS_UINT - event identifier.
    //
    ////////////////////////////////////////////////////////////////////////////
    ITS_UINT
    GetId()
    { return id; }

    //.implementation:public,inline,BasicEvent
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the event identifier.
    //
    //  Input Parameters:
    //      idParam - event identifier.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetId(ITS_UINT idParam)
    { id = idParam; }

protected:
    ITS_UINT id;
};




template <class _E_> 
class FiniteStateMachine
{
public:

    //.implementation:public,inline,FiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Notes:
    //      The initial state is not set by the constructor. Therefore the
    //      member function SetInitialState must be called (for instance within
    //      the constructor of a heir of this class).
    //
    ////////////////////////////////////////////////////////////////////////////
    FiniteStateMachine()
        : currentState(NULL)
    {}


    //.implementation:public,inline,FiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~FiniteStateMachine()
    {}

    //.implementation:public,inline,FiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      According to the event, changes the current state to a new state and
    //      excutes the specific processing associated with the transition (the 
    //      finite state machine is event driven).
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    //  Notes:
    //      Success is assumed or an exception is thrown.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual int
    ProcessEvent(_E_& event)
    {
        ITS_INT ret = ITS_SUCCESS;

        State<FiniteStateMachine<_E_>, _E_>* previousState =
            currentState;

       
        currentState = currentState->StateProcessEvent(event);
        if (!currentState)
        {
            currentState = previousState;
            ret = previousState->ExecuteEventNotDefined(event);
            return (ret);
        }

        if (currentState != previousState)
        {
            previousState->HiddenExecuteOut(event);
            previousState->ExecuteOut(event);

            currentState->ExecuteIn(event);
            currentState->HiddenExecuteIn(event);
        }

        return (ret);
    }

    //.implementation:public,inline,FiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the initial state of the state machine. Must be called.
    //
    //  Input Parameters:
    //      initialState - initial state.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetInitialState(State<FiniteStateMachine<_E_>, _E_>& initialState)
    { currentState = &initialState; }

protected:
    State<FiniteStateMachine<_E_>, _E_>* currentState;
};


//.interface:State
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      State
//
//  Purpose:
//      Finite state machine state abstraction. Abstract base class of all
//      states.
//
//  Usage:
//      By inheritance to define one or more states of a specific  finite state
//      machine. See interface FiniteStateMachine for more informations.
//
//      Generic parameter class _F_ -> a finite state machine.
//      Generic parameter class _E_ -> an event type.
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_, class _E_>
class State
{
public:

    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      fsmParam - finite state machine to which the current state belongs.
    //
    ////////////////////////////////////////////////////////////////////////////
    State(_F_& fsmParam) 
        : finiteStateMachine(fsmParam)
    {}


    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~State()
    {}


    //.implementation:public,abstract,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Pure virtual function to be defined in all concrete heirs. Returns
    //      the new state and executes the specific processing associated with
    //      the transition.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    //  Input/Output Parameters:
    //  Return Value:
    //      State<_F_, _E_>* - new state.
    //
    //  Notes:
    //      Success is assumed or an exception is thrown.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual State<_F_, _E_>*
    StateProcessEvent(_E_& event) = 0;


    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To be redefined if necessary in a descendant. Allows specifying some
    //      processing to be executed when entering the current state.
    //
    //  Input Parameters:
    //      event - event currently processed.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    ExecuteIn(_E_& event)
    {}


    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To be redefined if necessary in a descendant. Allows specifying some
    //      processing to be executed when leaving the current state.
    //
    //  Input Parameters:
    //      event - event currently processed.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    ExecuteOut(_E_& event)
    {}


    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To define a new association between a transition and an event
    //      identifier that is valid for (also meaning accepted by) the current
    //      state.
    //
    //  Input Parameters:
    //      transition - a transition.
    //      eventId    - an event identifier.
    //
    //  Notes:
    //      Success is assumed or an exception is thrown.
    //
    ////////////////////////////////////////////////////////////////////////////
    void 
    DefineTransition(Transition<_F_, _E_>& transition,
                     ITS_UINT eventId)
    {
        std::pair <EventTransitionAssociation::iterator, bool> insertRes = 
            eventTransitionAssociation.
                insert(EventTransitionAssociation::
                    value_type(eventId, &transition));

        // Ensure that the insertion is okay (attribute
        // second of insertRes must be okay).

        ITS_ENSURE(insertRes.second);
    }


    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To get the finite state machine to which the current state belongs.
    //
    //  Return Value:
    //      _F_& - finite state machine.
    //
    ////////////////////////////////////////////////////////////////////////////
    _F_&
    GetFsm()
    { return finiteStateMachine; }


    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the finite state machine to which the current state belongs.
    //
    //  Input Parameters:
    //      fsmParam - finite state machine.
    //
    //  See Also:
    //      Constructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetFsm(_F_& fsmParam)
    { finiteStateMachine = fsmParam; }


    typedef std::map<ITS_UINT, void*> EventTransitionAssociation;

    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To get the container (STL map) of all the event identifier and
    //      transition associations of the current state.
    //
    //  Return Value:
    //      const EventTransitionAssociation& - container (STL map).
    //
    //  Notes:
    //      EventTransitionAssociation is defined by:
    //
    //      typedef map<ITS_UINT, void*> EventTransitionAssociation;
    //      
    //      It should be map<ITS_UINT, Transition<_F_, _E_>*> to ensure type
    //      safety. In practice, void* is used to help the C++ compiler.
    //
    ////////////////////////////////////////////////////////////////////////////
    const EventTransitionAssociation&
    GetEventTransitionAssociation()
    { return eventTransitionAssociation; }


    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To be redefined if necessary in a descendant. Allows specifying some
    //      hidden processing to be executed when entering the current state.
    //
    //  Input Parameters:
    //      event - event currently processed.
    //
    //  Notes:
    //      Should be a protected member function, but a C++ type system 
    //      deficiency leaves no real choice.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    HiddenExecuteIn(_E_& event)
    {}


    //.implementation:public,inline,State
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To be redefined if necessary in a descendant. Allows specifying some
    //      hidden processing to be executed when leaving the current state.
    //
    //  Input Parameters:
    //      event - event currently processed.
    //
    //  Notes:
    //      Should be a protected member function, but a C++ type system 
    //      deficiency leaves no real choice.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    HiddenExecuteOut(_E_& event)
    {}

    virtual int 
    ExecuteEventNotDefined(_E_& event)
    {}


protected:
    EventTransitionAssociation eventTransitionAssociation;

    _F_& finiteStateMachine;
};


//.interface:SubFiniteStateMachine
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      SubFiniteStateMachine
//
//  Purpose:
//      Finite state machine sub finite state machine abstraction. Base class
//      of all the sub finite state machines. This class should also inherit 
//      from FiniteStateMachine. Code duplication is done to help the C++ 
//      compiler.
//
//  Usage:
//      Usually by inheritance to define one or more sub finite state machines
//      of a specific finite state machine. See interface FiniteStateMachine
//      for more informations.
//
//      Generic parameter class _F_ -> a finite state machine.
//      Generic parameter class _E_ -> an event type.
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_, class _E_>
class SubFiniteStateMachine : public State<_F_, _E_>
{
public:

    //.implementation:public,inline,SubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      fsmParam - finite state machine to which the current sub finite 
    //      state belongs.
    //
    //  Notes:
    //      The initial state is not set by the constructor. Therefore the
    //      member function SetInitialState must be called (for instance within
    //      the constructor of a heir of this class).
    //
    ////////////////////////////////////////////////////////////////////////////
    SubFiniteStateMachine(_F_& fsmParam)
        :    State<_F_, _E_>(fsmParam),
             currentState(NULL),
             initialStateSave(NULL)
    {}


    //.implementation:public,inline,SubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~SubFiniteStateMachine()
    {}


    //.implementation:public,abstract,SubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Pure virtual function to be defined in all concrete heirs. Returns
    //      the new state and executes the specific processing associated with
    //      the transition.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    //  Return Value:
    //      State<_F_, _E_>* - new state.
    //
    //  Notes:
    //      Success is assumed or an exception is thrown.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual State<_F_, _E_>*
    StateProcessEvent(_E_& event) = 0;

    //.implementation:public,inline,SubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the initial state of the sub finite state machine. Must be
    //      called.
    //
    //  Input Parameters:
    //      initialState - initial state.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetInitialState(State<SubFiniteStateMachine<_F_, _E_>, _E_>& initialState)
    { currentState = initialStateSave = &initialState; }

protected:

    //.implementation:public,inline,SubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      According to the event, changes the current state to a new state and
    //      excutes the specific processing associated with the transition (the 
    //      sub finite state machine is event driven).
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    //  Notes:
    //      Success is assumed or an exception is thrown.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    ProcessEvent(BasicEvent& event)
    {
        State<SubFiniteStateMachine<_F_, _E_>, _E_>* previousState = 
            currentState;

        currentState->ExecuteOut(event);

        currentState = currentState->StateProcessEvent(event);

        if (currentState != previousState)
        {
            previousState->HiddenExecuteOut(event);
            previousState->ExecuteOut(event);

            currentState->ExecuteIn(event);
            currentState->HiddenExecuteIn(event);
        }
    }

    State<SubFiniteStateMachine<_F_, _E_>, _E_>* currentState;
    State<SubFiniteStateMachine<_F_, _E_>, _E_>* initialStateSave;
};


//.interface:BasicState
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      BasicState
//
//  Purpose:
//      Finite state machine basic state abstraction. Base class of all
//      basic states. Class State specialized with the event type 
//      BasicEvent.
//
//  Usage:
//      Usually by inheritance to define one or more states of a specific 
//      finite state machine. See interface FiniteStateMachine for more 
//      informations.
//
//      Generic parameter class _F_ -> a finite state machine.
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_>
class BasicState : public State<_F_, BasicEvent>
{
public:
     using State<_F_, BasicEvent>::eventTransitionAssociation;
    //.implementation:public,inline,BasicState
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      fsmParam - finite state machine to which the current state belongs.
    //
    ////////////////////////////////////////////////////////////////////////////
    BasicState(_F_& fsmParam) : State<_F_, BasicEvent>(fsmParam)
    {}


    //.implementation:public,inline,BasicState
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~BasicState()
    {}


    //.implementation:public,inline,BasicState
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To return the new state and to execute the specific processing
    //      associated with the transition.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    //  Return Value:
    //      State<_F_, BasicEvent>* - new state.
    //
    //  Notes:
    //      Success is assumed or an exception is thrown.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual State<_F_, BasicEvent>*
    StateProcessEvent(BasicEvent& event)
    {
 typename State<_F_, BasicEvent>::EventTransitionAssociation::iterator iter;
//        EventTransitionAssociation::iterator iter;

        iter = eventTransitionAssociation.find(event.GetId());

        if (iter != eventTransitionAssociation.end())
        {
            Transition<_F_, BasicEvent>* transition = 
                static_cast<Transition<_F_, BasicEvent>* >
                    ((*iter).second);

            return &transition->ProcessEvent(event);
        }
        else
        {
            bool event_id_must_be_found = false;

            return NULL;    // Not reached.
        }
    }
};


//.interface:ITS_BasicSubFiniteStateMachine
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      BasicSubFiniteStateMachine
//
//  Purpose:
//      Finite state machine basic sub finite state machine abstraction. Base
//      class of all the basic sub finite state machines. This class should
//      also inherit from SubFiniteStateMachine. Code duplication is done
//      to help the C++ compiler. Class SubFiniteStateMachine specialized
//      with the event type BasicEvent.
//
//  Usage:
//      Usually by inheritance to define one or more sub finite state machines
//      of a specific finite state machine. See interface FiniteStateMachine
//      for more informations.
//
//      Generic parameter class _F_ -> a finite state machine.
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_>
class BasicSubFiniteStateMachine : public BasicState<_F_>
{
public:

     using BasicState<_F_>::eventTransitionAssociation;
    //.implementation:public,inline,BasicSubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      fsmParam - finite state machine to which the current sub finite 
    //      state belongs.
    //
    //  Notes:
    //      The initial state is not set by the constructor. Therefore the
    //      member function SetInitialState must be called (for instance within
    //      the constructor of a heir of this class).
    //
    ////////////////////////////////////////////////////////////////////////////
    BasicSubFiniteStateMachine(_F_& fsmParam)
        : BasicState<_F_>(fsmParam),
          currentState(NULL),
          initialStateSave(NULL)
    {}


    //.implementation:public,inline,BasicSubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~BasicSubFiniteStateMachine()
    {}


    //.implementation:public,inline,BasicSubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To return the new state and to execute the specific processing
    //      associated with the transition.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    //  Notes:
    //      Success is assumed or an exception is thrown.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual State<_F_, BasicEvent>* 
    StateProcessEvent(BasicEvent& event)
    {
        // [1] try to process the event at the finite state machine level.

        typename BasicState<_F_>::EventTransitionAssociation::iterator iter;
        iter =  currentState->GetEventTransitionAssociation().find(event.GetId());

        if (iter != currentState->GetEventTransitionAssociation().end())
        {
            ProcessEvent(event);

            return this;
        }
        else // [2] try to process the event at the state level.
        {
            iter = eventTransitionAssociation.find(event.GetId());

            if (iter != eventTransitionAssociation.end())
            {    
                Transition<_F_, BasicEvent>* transition = 
                    static_cast<Transition<_F_, BasicEvent>* >
                        ((*iter).second);

                return &transition->ProcessEvent(event);
            }
            else // [3] eventId not found => error.
            {
                bool event_id_must_be_found = false;

                ITS_THROW_ASSERT(event_id_must_be_found);

                return this;    // Not reached.
            }
        }
    }


    //.implementation:public,inline,BasicSubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the initial state of the sub finite state machine. Must be
    //      called.
    //
    //  Input Parameters:
    //      initialState - initial state.
    //
    ////////////////////////////////////////////////////////////////////////////
    void 
    SetInitialState(State<BasicSubFiniteStateMachine<_F_>,
                    BasicEvent>& initialState)
    { currentState = initialStateSave = &initialState; }


    //.implementation:public,inline,BasicSubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Hidden processing to be executed when entering the current sub
    //      finite state machine.
    //
    //  Input Parameters:
    //      event - event currently processed.
    //
    //  Notes:
    //      Should be a protected member function, but a C++ type system 
    //      deficiency leaves no real choice.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    HiddenExecuteIn(BasicEvent& event)
    {
        currentState->ExecuteIn(event);
    }


    //.implementation:public,inline,BasicSubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Hidden processing to be executed when leaving the current sub finite
    //      state machine.
    //
    //  Input Parameters:
    //      event - event currently processed.
    //
    //  Notes:
    //      Should be a protected member function, but a C++ type system 
    //      deficiency leaves no real choice.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    HiddenExecuteOut(BasicEvent& event)
    {
        currentState->ExecuteOut(event);

        currentState = initialStateSave;
    }

protected:

    //.implementation:public,inline,BasicSubFiniteStateMachine
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      According to the event, changes the current state to a new state and
    //      excutes the specific processing associated with the transition (the 
    //      sub finite state machine is event driven).
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    //  Notes:
    //      Success is assumed or an exception is thrown.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    ProcessEvent(BasicEvent& event)
    {
        State<BasicSubFiniteStateMachine<_F_>, BasicEvent>*
            previousState = currentState;

        currentState = currentState->StateProcessEvent(event);

        if (currentState != previousState)
        {
            previousState->HiddenExecuteOut(event);
            previousState->ExecuteOut(event);

            currentState->ExecuteIn(event);
            currentState->HiddenExecuteIn(event);
        }
    }
        
    State<BasicSubFiniteStateMachine<_F_>, BasicEvent>*
        currentState;

    State<BasicSubFiniteStateMachine<_F_>, BasicEvent>*
        initialStateSave;
};



//.interface:Transition
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      Transition
//
//  Purpose:
//      Finite state machine transition abstraction. Abstract base class of all
//      transitions.
//
//  Usage:
//      By inheritance to define one or more transitions of a specific finite
//      state machine. See interface FiniteStateMachine for more 
//      informations.
//
//      Generic parameter class _F_ -> a finite state machine.
//      Generic parameter class _E_ -> an event type.
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_, class _E_>
class Transition
{
public:

    //.implementation:public,inline,Transition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      fsmParam - finite state machine to which the current transition
    //                 belongs.
    //
    ////////////////////////////////////////////////////////////////////////////
    Transition(_F_& fsmParam)
        : finiteStateMachine(fsmParam)
    {}


    //.implementation:public,inline,Transition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~Transition()
    {}


    //.implementation:public,abstract,Transition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Pure virtual function to be defined in all concrete heirs. Allows 
    //      to execute some specific processing associated with the current
    //      transition.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    Execute(_E_& event) = 0;


    //.implementation:public,abstract,Transition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Pure virtual function to be defined in all concrete heirs. Returns
    //      the new state and executes the specific processing associated with
    //      the current transition.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    //  Return Value:
    //      State<_F_, _E_>& - new state.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual State<_F_, _E_>&
    ProcessEvent(_E_& event) = 0;


    //.implementation:public,inline,Transition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To get the finite state machine to which the current transition
    //      belongs.
    //
    //  Return Value:
    //      _F_& - finite state machine.
    //
    ////////////////////////////////////////////////////////////////////////////
    _F_&
    GetFsm()
    { return finiteStateMachine; }


    //.implementation:public,inline,Transition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the finite state machine to which the current transition
    //      belongs.
    //
    //  Input Parameters:
    //      fsmParam - finite state machine.
    //
    //  See Also:
    //      Constructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetFsm(_F_& finiteStateMachineParam)
    { finiteStateMachine = finiteStateMachineParam; }

protected:
    _F_& finiteStateMachine;
};


//.interface:BinaryTransition
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      BinaryTransition
//
//  Purpose:
//      Finite state machine binary transition abstraction. Base class of all
//      binary transitions.
//
//  Usage:
//      Usually by inheritance to define one or more binary transitions of a
//      specific finite state machine. See interface FiniteStateMachine for
//      more informations.
//
//      Generic parameter class _F_     -> a finite state machine.
//      Generic parameter class _E_     -> an event type.
//      Generic parameter class SOrig -> a state (originating).
//      Generic parameter class SDest -> a state (destination).
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_, class SOrig, class SDest, class _E_>
class BinaryTransition : public Transition<_F_, _E_>
{
public:

    //.implementation:public,inline,BinaryTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      fsmParam       - finite state machine to which the current
    //                       transition belongs.
    //      stateOrigParam - originating state.
    //      stateDestParam - destination state.
    //
    ////////////////////////////////////////////////////////////////////////////
    BinaryTransition(_F_& fsmParam,
                     SOrig& stateOrigParam,
                     SDest& stateDestParam)
        :    Transition<_F_, _E_>(fsmParam),
             stateOrig(stateOrigParam),
             stateDest(stateDestParam)
    {}


    //.implementation:public,inline,BinaryTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~BinaryTransition()
    {}


    //.implementation:public,inline,BinaryTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Allows to execute some specific processing associated with the
    //      current transition when redefined in an heir.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    Execute(_E_& event)
    {}


    //.implementation:public,inline,BinaryTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To Return the new state and to execute the specific processing
    //      associated with the current transition. The new state is the 
    //      destination state.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    //  Return Value:
    //      State<_F_, _E_>& - new state.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual State<_F_, _E_>&
    ProcessEvent(_E_& event)
    {
        Execute(event);
    
        return stateDest;
    }


    //.implementation:public,inline,BinaryTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To get the originating state.
    //
    //  Return Value:
    //      SOrig& - originating state.
    //
    ////////////////////////////////////////////////////////////////////////////
    SOrig&
    GetStateOrig()
    { return stateOrig; }


    //.implementation:public,inline,BinarayTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the originating state.
    //
    //  Input Parameters:
    //      stateOrigParam - originating state.
    //
    //  See Also:
    //      Constructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetStateOrig(SOrig& stateOrigParam)
    { stateOrig = stateOrigParam; }


    //.implementation:public,inline,BinaryTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To get the destination state.
    //
    //  Return Value:
    //      SDest& - destination state.
    //
    ////////////////////////////////////////////////////////////////////////////
    SDest&
    GetStateDest()
    { return stateDest; }


    //.implementation:public,inline,BinarayTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the destination state.
    //
    //  Input Parameters:
    //      stateDestParam - destination state.
    //
    //  See Also:
    //      Constructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    void
    SetStateDest(SDest& stateDestParam)
    { stateDest = stateDestParam; }

protected:
    SOrig& stateOrig;

    SDest& stateDest;
};


//.interface:BasicTransition
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      BasicTransition
//
//  Purpose:
//      Finite state machine basic binary transition abstraction. Base class
//      of all basic binary transitions. Class BinaryTransition specialized
//      with the event type BasicEvent.
//
//  Usage:
//      Usually by inheritance to define one or more basic binary transitions
//      of a specific finite state machine. See interface FiniteStateMachine
//      for more informations.
//
//      Generic parameter class _F_ -> a finite state machine.
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_>
class BasicTransition : public BinaryTransition<_F_,
                                                BasicState<_F_>,
                                                BasicState<_F_>,
                                                BasicEvent>
{
public: 

    //.implementation:public,inline,BasicTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      fsmParam       - finite state machine to which the current
    //                       transition belongs.
    //      stateOrigParam - originating state.
    //      stateDestParam - destination state.
    //
    ////////////////////////////////////////////////////////////////////////////
    BasicTransition(_F_& fsmParam,
                    BasicState<_F_>& stateOrigParam,
                    BasicState<_F_>& stateDestParam)
        :    BinaryTransition<_F_, 
                              BasicState<_F_>,
                              BasicState<_F_>,
                              BasicEvent>
             (fsmParam, stateOrigParam, stateDestParam)
    {}


    //.implementation:public,inline,BasicTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~BasicTransition()
    {}


    //.implementation:public,inline,BasicTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Allows to execute some specific processing associated with the
    //      current transition when redefined in an heir.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    Execute(BasicEvent& event)
    {}
};


//.interface:BasicFunctionalTransition
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      BasicFunctionalTransition
//
//  Purpose:
//      Finite state machine basic binary functional transition abstraction.
//      Directly derived from BasicTransition. Avoids to define too many
//      classes inheriting from BasicTransition that only differ by the
//      specific processing to be executed during the transition. Allows to 
//      set a pointer to a function that is executed during the transition.
//
//  Usage:
//      Directly. See interface FiniteStateMachine for more informations.
//
//      Generic parameter class _F_ -> a finite state machine.
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_>
class BasicFunctionalTransition : public BasicTransition<_F_>
{
public:

    typedef void (*BasicTransitionFunction)
        (BasicFunctionalTransition& transition,
         _F_& finiteStateMachine,
         BasicState<_F_>& stateOrig,
         BasicState<_F_>& stateDest,
         BasicEvent& event);

    //.implementation:public,inline,BasicFunctionalTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      fsmParam       - finite state machine to which the current
    //                       transition belongs.
    //      stateOrigParam - originating state.
    //      stateDestParam - destination state.
    //
    //  Notes:
    //      The pointer function is not set by the constructor. Therefore the
    //      member function SetFunction must be called.
    //
    ////////////////////////////////////////////////////////////////////////////
    BasicFunctionalTransition(_F_& fsmParam,
                              BasicState<_F_>& stateOrigParam,
                              BasicState<_F_>& stateDestParam)
        :   BasicTransition<_F_>(fsmParam, stateOrigParam, stateDestParam),
            function(NULL) 
    {}


    //.implementation:public,inline,BasicFunctionalTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~BasicFunctionalTransition()
    {}


    //.implementation:public,inline,BasicFunctionalTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the pointer to the function that is executed during the
    //      transition. Must be called.
    //
    //  Input Parameters:
    //      functionParam - pointer to function.
    //
    //  Notes:
    //      The signature of the function must be:
    //
    //          typedef void (*BasicTransitionFunction)
    //              (BasicFunctionalTransition& transition,
    //              _F_& finiteStateMachine,
    //              BasicState<_F_>& stateOrig,
    //              BasicState<_F_>& stateDest,
    //              BasicEvent& event);
    //
    ////////////////////////////////////////////////////////////////////////////
    void 
    SetFunction(BasicTransitionFunction functionParam)
    { function = functionParam; }


    //.implementation:public,inline,BasicFunctionalTransition
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Execute the specific processing defined by the function during the
    //      transition.
    //
    //  Input Parameters:
    //      event - event to be processed. 
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual void
    Execute(BasicEvent& event)
    {
        ITS_REQUIRE(function != NULL);

//	using State<_F_, BasicEvent>::eventTransitionAssociation;

        function(*this,BasicTransition<_F_>::finiteStateMachine,BasicTransition<_F_>::stateOrig,BasicTransition<_F_>::stateDest, event);
    }

protected:

    BasicTransitionFunction function;
};


//.interface:TernaryTransition
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      TernaryTransition
//
//  Purpose:
//      Finite state machine ternary transition abstraction. Base class of all
//      ternary transitions.
//
//  Usage:
//      Usually by inheritance to define one or more ternary transitions of a
//      specific finite state machine. See interface FiniteStateMachine for
//      more informations.
//
//      Generic parameter class _F_        -> a finite state machine.
//      Generic parameter class _E_        -> an event type.
//      Generic parameter class SOrig    -> a state (originating).
//      Generic parameter class SDestOne -> a state (possible destination).
//      Generic parameter class SDestTwo -> a state (possible destination).
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_, class SOrig, class SDestOne, class SDestTwo, class _E_>
class TernaryTransition : public Transition<_F_, _E_>
{
public:

    TernaryTransition(_F_& fsmParam,
                      SOrig& stateOrigParam,
                      SDestOne& stateDestOneParam,
                      SDestTwo& stateDestTwoParam)
        :    Transition<_F_, _E_>(fsmParam),
             stateOrig(stateOrigParam),
             stateDestOne(stateDestOneParam),
             stateDestTwo(stateDestTwoParam),
             chosenStateDest(stateDestOneParam)
    {}

    virtual ~TernaryTransition()
    {}

    virtual void
    Execute(_E_& event) = 0;

    virtual State<_F_, _E_>&
    ProcessEvent(_E_& event)
    {
        Execute(event);

        return chosenStateDest;
    }

    SOrig&
    GetStateOrig()
    { return stateOrig; }

    void
    SetStateOrig(SOrig& stateOrigParam)
    { stateOrig = stateOrigParam; }

    SDestOne&
    GetStateDestOne()
    { return stateDestOne; }

    void
    SetStateDestOne(SDestOne& stateDestOneParam)
    { stateDestOne = stateDestOneParam; }

    SDestTwo& GetStateDestTwo()
    { return stateDestTwo; }

    void
    SetStateDestTwo(SDestTwo& stateDestTwoParam)
    { stateDestTwo = stateDestTwoParam; }

    void
    ChoseStateDestOne()
    { chosenStateDest = stateDestOne; }

    void
    ChoseStateDestTwo()
    { chosenStateDest = stateDestTwo; }


protected:
    SOrig& stateOrig;

    SDestOne& stateDestOne;
    SDestTwo& stateDestTwo;

    State<_F_, _E_>& chosenStateDest;
};


//.interface:QuaternaryTransition
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      QuaternaryTransition
//
//  Purpose:
//      Finite state machine quaternary transition abstraction. Base class of
//      all quaternary transitions.
//
//  Usage:
//      Usually by inheritance to define one or more quaternary transitions of
//      a specific finite state machine. See interface FiniteStateMachine
//      for more informations.
//
//      Generic parameter class _F_          -> a finite state machine.
//      Generic parameter class _E_          -> an event type.
//      Generic parameter class SOrig      -> a state (originating).
//      Generic parameter class SDestOne   -> a state (possible destination).
//      Generic parameter class SDestTwo   -> a state (possible destination).
//      Generic parameter class SDestThree -> a state (possible destination).
//
////////////////////////////////////////////////////////////////////////////////
template <class _F_, class SOrig, class SDestOne, class SDestTwo,
          class SDestThree, class _E_>
class QuaternaryTransition : public Transition<_F_, _E_>
{
public:

    QuaternaryTransition(_F_& fsmParam,
                         SOrig& stateOrigParam,
                         SDestOne& stateDestOneParam,
                         SDestTwo& stateDestTwoParam,
                         SDestThree& stateDestThreeParam)
        :    Transition<_F_, _E_>(fsmParam),
             stateOrig(stateOrigParam),
             stateDestOne(stateDestOneParam),
             stateDestTwo(stateDestTwoParam),
             stateDestThree(stateDestThreeParam),
             chosenStateDest(stateDestOneParam)
    {}

    virtual ~QuaternaryTransition()
    {}

    virtual void
    Execute(_E_& event) = 0;

    virtual State<_F_, _E_>&
    ProcessEvent(_E_& event)
    {
        Execute(event);

        return chosenStateDest;
    }

    SOrig&
    GetStateOrig()
    { return stateOrig; }

    void
    SetStateOrig(SOrig& stateOrigParam)
    { stateOrig = stateOrigParam; }

    SDestOne&
    GetStateDestOne()
    { return stateDestOne; }

    void
    SetStateDestOne(SDestOne& stateDestOneParam)
    { stateDestOne = stateDestOneParam; }

    SDestTwo&
    GetStateDestTwo()
    { return stateDestTwo; }

    void
    SetStateDestTwo(SDestTwo& stateDestTwoParam)
    { stateDestTwo = stateDestTwoParam; }

    SDestThree&
    GetStateDestThree()
    { return stateDestThree; }

    void
    SetStateDestThree(SDestThree& stateDestThreeParam)
    { stateDestThree = stateDestThreeParam; }

    void
    ChoseStateDestOne()
    { chosenStateDest = stateDestOne; }

    void
    ChoseStateDestTwo()
    { chosenStateDest = stateDestTwo; }

    void
    ChoseStateDestThree()
    { chosenStateDest = stateDestThree; }


protected:
    SOrig& stateOrig;

    SDestOne& stateDestOne;
    SDestTwo& stateDestTwo;
    SDestThree& stateDestThree; 

    State<_F_, _E_>& chosenStateDest;
};

#if 0
//.interface:BasicEvent
////////////////////////////////////////////////////////////////////////////////
//  Interface:
//      BasicEvent
//
//  Purpose:
//      Finite state machine basic event abstraction. Base class of all
//      basic events. Used as the event type generic parameter for all the
//      classes named Basic...
//
//  Usage:
//      Directly or by inheritance to define a hierarchy of class events. See
//      interface FiniteStateMachine for more informations.
//
////////////////////////////////////////////////////////////////////////////////
class BasicEvent
{
public:

    //.implementation:public,inline,BasicEvent
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Constructor.
    //
    //  Input Parameters:
    //      idParam - event identifier.
    //
    //  Notes:
    //      Within a finite state machine (or more precisely within a state), an
    //      event identifier must be unique.
    //
    ////////////////////////////////////////////////////////////////////////////
    BasicEvent(ITS_UINT idParam)
        : id(idParam)
    {}

    //.implementation:public,inline,BasicEvent
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      Destructor.
    //
    ////////////////////////////////////////////////////////////////////////////
    virtual ~BasicEvent()
    {}

    //.implementation:public,inline,BasicEvent
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To get the event identifier.
    //
    //  Return Value:
    //      ITS_UINT - event identifier.
    //
    ////////////////////////////////////////////////////////////////////////////
    ITS_UINT
    GetId()
    { return id; }

    //.implementation:public,inline,BasicEvent
    ////////////////////////////////////////////////////////////////////////////
    //
    //  Purpose:
    //      To set the event identifier.
    //
    //  Input Parameters:
    //      idParam - event identifier.
    //
    ////////////////////////////////////////////////////////////////////////////
    void 
    SetId(ITS_UINT idParam)
    { id = idParam; }

protected:
    ITS_UINT id;
};

#endif 

#if defined(ITS_NAMESPACE)
}
#endif    // defined(ITS_NAMESPACE)

#endif // !defined(_ITS_FSM_H_)
