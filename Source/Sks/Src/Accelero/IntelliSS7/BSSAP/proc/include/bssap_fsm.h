/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: bssap_fsm.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.12  2005/09/29 07:43:48  adutta
 * LOG: Trace changes
 * LOG:
 * LOG: Revision 1.1.2.11  2005/09/28 06:38:02  adutta
 * LOG: Proceed msg changed to Progress
 * LOG:
 * LOG: Revision 1.1.2.10  2005/09/28 06:12:47  adutta
 * LOG: Added state transitions to handle rel/rel compl/disc ind
 * LOG:
 * LOG: Revision 1.1.2.9  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.8  2005/08/28 19:03:50  adutta
 * LOG: Handover addition
 * LOG:
 * LOG: Revision 1.1.2.7  2005/08/26 20:20:16  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.6  2005/08/26 06:54:14  adutta
 * LOG: Fsm changes - for redundancy
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/21 15:45:20  adutta
 * LOG: Changes for MO calls
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/20 18:15:25  adutta
 * LOG: Few more traces added
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/19 06:39:44  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/17 05:32:45  adutta
 * LOG: Traces added
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_FSM_H_
#define  _BSSAP_FSM_H_

#include <iostream.h>

#include <its_exception.h>
#include <its_fsm.h>

#include <BSSAP.h>
#include <bssap_timer.h>
#include <bssap_call.h>
#include <bssap_sccphandler.h>
#include <bssap_interface.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif    // defined(ITS_NAMESPACE)


#define   BSSAP_CC_MSG_DISCONNECT_IND             50
#define   BSSAP_CC_MSG_RELEASE_IND                51


/*.interface:BSSAPEvent
 *****************************************************************************
 *  Interface:
 *      BSSAPEvent
 *
 *  Purpose:
 *      This is a derived class from BasicEvent. In general state transition 
 *      occurs through event triggers. The BasicEvent is a class wrapping this 
 *      events, In this case events are BSSAP message type. The derived 
 *      class adds properties like call reference identifier and call object.
 *
 *
 *
 *
 *  Usage:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                          Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/2005   IMR-DESP-BSSAP-01-V1.1 ID::D0300
 *****************************************************************************/
class BSSAPEvent : public ITS_BasicEvent
{
    public:
        BSSAPEvent(ITS_UINT eventID) :  ITS_BasicEvent(eventID)
        {};

        void SetCallRefId(ITS_USHORT Id)
        {
            callrefId = Id;
        }

        ITS_USHORT GetCallRefId()
        {
            return callrefId;
        }

        void SetCallObject(BSSAP_Call* c)
        {
            call = c;
        }

        BSSAP_Call* GetCallObject()
        {
            return call;
        }

    private:
        ITS_USHORT callrefId;
        BSSAP_Call* call;
};



/*.interface:Fsm
 *****************************************************************************
 *  Interface:
 *      Fsm
 *
 *  Purpose:
 *      Forms the BSSAP state engine base class. This is inherited from 
 *      Accelero FSM template.       
 *
 *
 *
 *
 *  Usage:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                          Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/2005   IMR-DESP-BSSAP-01-V1.1 ID::D0280
 *                                               ID::D0290
 *                                               ID::D0310
 *****************************************************************************/
class Fsm : public ITS_FiniteStateMachine<ITS_BasicEvent>
{

public:
    virtual ~Fsm(){}

    virtual void SetState(ITS_OCTET evt)
    {}

    friend ITS_INT HandleAbnormalEvents(BSSAP_Call* call)
    {
        ITS_OCTET ev = 0;
        ITS_INT ret = ITS_SUCCESS;
        BSSAP_Interface intface;

        ev = call->GetCurrentEvent();


        if ((ev == BSSAP_CC_MSG_DISCONNECT_IND)  ||
           (ev == BSSAP_CC_MSG_RELEASE_COMPLETE) ||
           (ev == BSSAP_CC_MSG_RELEASE_IND)      ||
           (ev == BSSAP_CC_MSG_PROGRESS))
        {
            BSSAP_WARNING(("Fsm: Call clearing Event %s\n", DTAP_STR(ev))) ; 

            ret = intface.DispatchDtapToApp(call);

            return (ret);
        }

        BSSAP_WARNING(("Fsm: Abnormal Event %s\n", DTAP_STR(ev))) ; 

        call->SetCurrentEvent(call->GetPrevEvent());

        return (!ret);
    }
};


/*.interface:FsmMT
 *****************************************************************************
 *  Interface:
 *      FsmMT
 *
 *  Purpose:
 *     Derived from Fsm base class this handles all the states related to 
 *     mobile terminated calls.
 *
 *
 *
 *
 *  Usage:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                          Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/2005   IMR-DESP-BSSAP-01-V1.1 ID::D0280
 *                                               ID::D0290
 *                                               ID::D0310

 *****************************************************************************/
class FsmMT : public Fsm,
                   public its::ITS_SingletonMultithreaded<FsmMT>
{
    public:
        FsmMT() : its:: ITS_SingletonMultithreaded<FsmMT>()
        {
            stateNull = new StateNull(*this);
            statePend = new StatePending(*this);
            stateInd = new StateIndication(*this);
            stateConf  =  new StateConfirm(*this);
            stateRecv = new StateReceived(*this);
            stateConReq = new StateConnectionRequest(*this);
            stateActv = new StateActive(*this);
            stateDiscReq = new StateDisconnectRequest(*this);
            stateDiscInd  = new StateDisconnectIndication(*this);
            stateRelReq  =  new StateReleaseRequest(*this);
            stateRelInd  =  new StateReleaseInd(*this);

            transition_null_to_pend =  
               new ITS_BasicTransition<FsmMT>( *this, *stateNull, *statePend);
            transition_pend_to_ind = 
               new ITS_BasicTransition<FsmMT>( *this, *statePend, *stateInd);
            transition_ind_to_conf  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateInd, *stateConf);
            transition_conf_to_recv  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateConf, *stateRecv);
            transition_recv_to_conreq  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateRecv, *stateConReq);
            transition_conreq_to_actv  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateConReq, *stateActv);
            transition_conf_to_conreq  =  
               new ITS_BasicTransition<FsmMT>( *this, *stateConf, *stateConReq);

            // Disconnect request from Applicaiton 
            transition_disreq_to_relInd =
              new ITS_BasicTransition<FsmMT>( *this,*stateDiscReq,*stateRelInd);
            transition_relInd_to_null =
              new ITS_BasicTransition<FsmMT>( *this, *stateRelInd, *stateNull);
            transition_ind_to_null  =  
              new ITS_BasicTransition<FsmMT>( *this, *stateInd, *stateNull);
            transition_actv_to_disreq =
              new ITS_BasicTransition<FsmMT>( *this, *stateActv, *stateDiscReq);
            transition_conf_to_disreq  =  
              new ITS_BasicTransition<FsmMT>( *this, *stateConf, *stateDiscReq);
            transition_recv_to_disreq  =  
              new ITS_BasicTransition<FsmMT>( *this, *stateRecv, *stateDiscReq);
            transition_ind_to_disreq  =  
              new ITS_BasicTransition<FsmMT>( *this, *stateInd, *stateDiscReq);


              
            // Disconnect request from remote 
            transition_actv_to_disind =
            new ITS_BasicTransition<FsmMT>( *this, *stateActv, *stateDiscInd);
            transition_disind_to_relreq  =  
            new ITS_BasicTransition<FsmMT>( *this, *stateDiscInd, *stateRelReq);
            transition_relreq_to_null  =  
            new ITS_BasicTransition<FsmMT>( *this, *stateRelReq, *stateNull);

            // Time out state transition
            transition_disreq_to_relreq =
            new ITS_BasicTransition<FsmMT>( *this, *stateDiscReq, *stateRelReq);
            transition_conreq_to_disreq =
            new ITS_BasicTransition<FsmMT>( *this, *stateConReq, *stateDiscReq);


               
            // Normal flow
            stateNull->DefineTransition(*transition_null_to_pend,
                                                BSSAP_MSG_PAGING_RESPONSE);
            statePend->DefineTransition(*transition_pend_to_ind, 
                                                BSSAP_CC_MSG_SETUP);
            stateInd->DefineTransition(*transition_ind_to_conf, 
                                                BSSAP_CC_MSG_CALL_CONFIRMED);
            stateConf->DefineTransition(*transition_conf_to_recv, 
                                                BSSAP_CC_MSG_ALERTING);
            stateRecv->DefineTransition(*transition_recv_to_conreq, 
                                                BSSAP_CC_MSG_CONNECT);
            stateConReq->DefineTransition(*transition_conreq_to_actv, 
                                              BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE);

            // Hops
            stateConf->DefineTransition(*transition_conf_to_conreq,
                                                BSSAP_CC_MSG_CONNECT);

            // Disconnects in between call setup
            stateConf->DefineTransition(*transition_conf_to_disreq,
                                                BSSAP_CC_MSG_DISCONNECT);
            stateRecv->DefineTransition(*transition_recv_to_disreq,
                                                BSSAP_CC_MSG_DISCONNECT);
            stateInd->DefineTransition(*transition_ind_to_disreq,
                                                BSSAP_CC_MSG_DISCONNECT);
            stateInd->DefineTransition(*transition_ind_to_null,
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);

            // Local Disconnect 
            stateActv->DefineTransition(*transition_actv_to_disreq, 
                                               BSSAP_CC_MSG_DISCONNECT);
            stateDiscReq->DefineTransition(*transition_disreq_to_relInd, 
                                                BSSAP_CC_MSG_RELEASE_IND);
            stateRelInd->DefineTransition(*transition_relInd_to_null, 
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);

            // Remote Disconnect
            stateActv->DefineTransition(*transition_actv_to_disind, 
                                                BSSAP_CC_MSG_DISCONNECT_IND);
            stateDiscInd->DefineTransition(*transition_disind_to_relreq, 
                                                BSSAP_CC_MSG_RELEASE);
            stateRelReq->DefineTransition(*transition_relreq_to_null, 
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);

            // Timeout 
            stateConReq->DefineTransition(*transition_conreq_to_disreq, 
                                                BSSAP_CC_MSG_DISCONNECT);
            stateDiscReq->DefineTransition(*transition_disreq_to_relreq, 
                                                BSSAP_CC_MSG_RELEASE);
        }               

        virtual ~FsmMT()
        {
            BSSAP_DEBUG(("FsmMT: State objects deleted\n"));

            delete stateNull;
            delete statePend;
            delete stateInd;
            delete stateConf;
            delete stateRecv;
            delete stateConReq;
            delete stateActv;
            delete stateDiscReq;
            delete stateDiscInd;
            delete stateRelReq;
            delete stateRelInd;

            BSSAP_DEBUG(("FsmMT: Transition objects deleted\n"));

            delete transition_null_to_pend;
            delete transition_pend_to_ind;
            delete transition_ind_to_conf;
            delete transition_conf_to_recv;
            delete transition_recv_to_conreq;
            delete transition_conreq_to_actv;


            delete transition_actv_to_disreq;
            delete transition_relreq_to_null;
            delete transition_disreq_to_relreq;
            delete transition_relInd_to_null;
            delete transition_actv_to_disind;
            delete transition_disind_to_relreq;
            delete transition_disreq_to_relInd;
            delete transition_conreq_to_disreq;
            delete transition_conf_to_conreq;
            delete transition_conf_to_disreq;
            delete transition_recv_to_disreq;
            delete transition_ind_to_disreq;
            delete transition_ind_to_null;
        }

        static ITS_INT Initialize()
        {
            ITS_INT ret = 0;

            ret = ITS_SingletonMultithreaded<FsmMT>::Initialize();

            if (ret == ITS_SUCCESS)
            {
                BSSAP_DEBUG(("FsmMT: MT state table initialized\n"));
            }

            return (ret);
        }


        void SetState(ITS_OCTET event)
        {
            switch (event)
            {
                case BSSAP_MSG_PAGING_RESPONSE:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*statePend));
                break;

                case BSSAP_CC_MSG_SETUP:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateInd));
                break;

                case BSSAP_CC_MSG_CALL_CONFIRMED:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateConf));
                break;

                case BSSAP_CC_MSG_ALERTING:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateRecv));
                break;

                case BSSAP_CC_MSG_CONNECT:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateConReq));
                break;

                case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateActv));
                break;

                case BSSAP_CC_MSG_DISCONNECT:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateDiscReq));
                break;

                case BSSAP_CC_MSG_RELEASE_IND:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateRelInd));
                break;

                case  BSSAP_CC_MSG_DISCONNECT_IND:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateDiscInd));
                break;

                case BSSAP_CC_MSG_RELEASE:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateRelReq));
                break;

                default:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateNull));
                break;

            }
        }
               
        /*.interface:StateNull
        ***********************************************************************
        *  Interface:
        *      StateNull
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateNull : public ITS_BasicState<FsmMT>
        {
             public:
                StateNull(FsmMT& fsmParam) : ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateNull()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { 
                    BSSAP_DEBUG(("FsmMT: CALL in  state NULL...\n"));
                }

                void ExecuteOut(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_SCCPHandler hndl;

                    BSSAP_DEBUG(("FsmMT: Leaving NULL state %s\n", 
                                                  DTAP_STR(event.GetId())));

                    hndl.SendCR(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };

        /*.interface:StatePending
        ************************************************************************
        *  Interface:
        *     StatePending
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/        class StatePending : public ITS_BasicState<FsmMT>
        {
            public:
                StatePending(FsmMT& fsmParam) : ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StatePending()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {}
                    

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAP_Interface intface;
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    BSSAP_DEBUG(("FsmMT: Leaving PEND state %s\n",
                                                  DTAP_STR(event.GetId())));
   
                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };

        /*.interface:StateIndication
        ************************************************************************
        *  Interface:
        *     StateIndication 
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        **********************************************************************/
        class StateIndication : public ITS_BasicState<FsmMT>
        {
            public:
                StateIndication(FsmMT& fsmParam) : 
                                           ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateIndication()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {} 

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAP_SCCPHandler hndl;
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    BSSAP_DEBUG(("FsmMT: Leaving IND state %s\n",
                                                  DTAP_STR(event.GetId())));

                    hndl.SendDT1(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };
   
        /*.interface:StateConfirm
        ***********************************************************************
        *  Interface:
        *     StateConfirm
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        **********************************************************************/
        class StateConfirm : public ITS_BasicState<FsmMT>
        {
            public:
                StateConfirm(FsmMT& fsmParam) : ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateConfirm()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {}

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAP_SCCPHandler hndl;
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    BSSAP_DEBUG(("FsmMT: Leaving CONF state %s\n",
                                                  DTAP_STR(event.GetId())));

                    hndl.SendDT1(ev->GetCallObject());
                }   


                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                {  
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };

              
        /*.interface:StateReceived
        ************************************************************************
        *  Interface:
        *     StateReceived
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        **********************************************************************/
        class StateReceived : public ITS_BasicState<FsmMT>
        {
            public:
                StateReceived(FsmMT& fsmParam) : ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateReceived()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {
                }

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAP_SCCPHandler hndl;
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    BSSAP_DEBUG(("FsmMT: Leaving RECV state %s\n",
                                                  DTAP_STR(event.GetId())));

                    hndl.SendDT1(ev->GetCallObject());

                }  

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };
  
         
        /*.interface:StateConnectionRequest
        ************************************************************************
        *  Interface:
        *     StateConnectionRequest
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateConnectionRequest: public ITS_BasicState<FsmMT>
        {
            public:
                StateConnectionRequest(FsmMT& fsmParam) : 
                                         ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateConnectionRequest()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {
                }

                void ExecuteOut(ITS_BasicEvent& event)
                {    
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    BSSAP_DEBUG(("FsmMT: Leaving CONN REQ state %s\n",
                                                  DTAP_STR(event.GetId())));
    
                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };

        /*.interface:StateActive
        ***********************************************************************
        *  Interface:
        *     StateActive
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        **********************************************************************/
        class StateActive: public ITS_BasicState<FsmMT>
        {
            public:
                StateActive(FsmMT& fsmParam) : ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateActive()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { 
                    BSSAP_DEBUG(("FsmMT: Call in state ACTIVE...\n")) ; 
                }

                void ExecuteOut(ITS_BasicEvent& event)
                { 
                    BSSAP_DEBUG(("FsmMT: Leaving  ACTIVE state %s\n", 
                                                     DTAP_STR(event.GetId())));
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        /*.interface:StateDisconnectRequest
        **********************************************************************
        *  Interface:
        *     StateDisconnectRequest
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateDisconnectRequest: public ITS_BasicState<FsmMT>
        {
            public:
                StateDisconnectRequest(FsmMT& fsmParam) : 
                                        ITS_BasicState<FsmMT>(fsmParam)
            {};

            virtual ~StateDisconnectRequest()
            {};

            void ExecuteIn(ITS_BasicEvent& event)
            {
                BSSAPEvent* ev = (BSSAPEvent*)&event;
                BSSAP_SCCPHandler hndl;

                BSSAP_DEBUG(("FsmMT: Sending  DISC REQ to MSC\n"));

                hndl.SendDT1(ev->GetCallObject());
            }

            void ExecuteOut(ITS_BasicEvent& event)
            {
                BSSAP_DEBUG(("FsmMT: Leaving  DISC REQ state %s\n",
                                                  DTAP_STR(event.GetId())));
            }

            void ExecuteEventNotDefined(ITS_BasicEvent& event)
            { 
                BSSAPEvent* ev = (BSSAPEvent*)&event;

                HandleAbnormalEvents(ev->GetCallObject());
            }
        };


        /*.interface:StateDisconnectIndication
        ***********************************************************************
        *  Interface:
        *     StateDisconnectIndication
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        **********************************************************************/
        class StateDisconnectIndication: public ITS_BasicState<FsmMT>
        {
            public:
                StateDisconnectIndication(FsmMT& fsmParam) : 
                                                ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateDisconnectIndication()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    BSSAP_DEBUG(("FsmMT: Sending DISCONNECT to App\n"));

                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteOut(ITS_BasicEvent& event)
                { 
                    BSSAP_DEBUG(("FsmMT: Leaving DISC IND state %s\n", 
                                                   DTAP_STR(event.GetId()))); 
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };

        /*.interface:StateReleaseRequest
        ***********************************************************************
        *  Interface:
        *     StateReleaseRequest
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateReleaseRequest: public ITS_BasicState<FsmMT>
        {
            public:
                StateReleaseRequest(FsmMT& fsmParam) : 
                                             ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateReleaseRequest()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_SCCPHandler hndl;

                    BSSAP_DEBUG(("FsmMT: Sending RELEASE to MSC\n"));

                    hndl.SendDT1(ev->GetCallObject());
                }

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    BSSAP_DEBUG(("FsmMT: Leaving REL REQ state %s\n",
                                                  DTAP_STR(event.GetId())));

                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                {  
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };

        /*.interface:StateReleaseInd
        ************************************************************************
        *  Interface:
        *     StateReleaseInd
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        *********************************************************************/
        class StateReleaseInd: public ITS_BasicState<FsmMT>
        {
            public:
                StateReleaseInd(FsmMT& fsmParam) :  
                                           ITS_BasicState<FsmMT>(fsmParam)
                {};

                virtual ~StateReleaseInd()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    BSSAP_DEBUG(("FsmMT: Sending REL to App\n"));

                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_SCCPHandler hndl;

                    BSSAP_DEBUG(("FsmMT: Leaving REL IND state %s\n",
                                                  DTAP_STR(event.GetId())));

                    hndl.SendDT1(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        StateNull* stateNull;
        StatePending* statePend;
        StateIndication* stateInd;
        StateConfirm* stateConf;
        StateReceived* stateRecv;
        StateConnectionRequest* stateConReq;
        StateActive* stateActv;
        StateDisconnectRequest* stateDiscReq;
        StateDisconnectIndication* stateDiscInd;
        StateReleaseRequest* stateRelReq;
        StateReleaseInd* stateRelInd;

        ITS_BasicTransition<FsmMT>* transition_null_to_pend;
        ITS_BasicTransition<FsmMT>* transition_pend_to_ind;
        ITS_BasicTransition<FsmMT>* transition_ind_to_conf;
        ITS_BasicTransition<FsmMT>* transition_conf_to_recv;
        ITS_BasicTransition<FsmMT>* transition_recv_to_conreq;
        ITS_BasicTransition<FsmMT>* transition_conreq_to_actv;
        ITS_BasicTransition<FsmMT>* transition_actv_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_disreq_to_relreq;

        ITS_BasicTransition<FsmMT>* transition_actv_to_disind;
        ITS_BasicTransition<FsmMT>* transition_disind_to_relreq;
        ITS_BasicTransition<FsmMT>* transition_relreq_to_null;
        ITS_BasicTransition<FsmMT>* transition_disreq_to_relInd;
        ITS_BasicTransition<FsmMT>* transition_relInd_to_null;
        ITS_BasicTransition<FsmMT>* transition_conreq_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_conf_to_conreq;
        ITS_BasicTransition<FsmMT>* transition_conf_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_recv_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_ind_to_disreq;
        ITS_BasicTransition<FsmMT>* transition_ind_to_null;

};




/*.interface:FsmMO
 *****************************************************************************
 *  Interface:
 *      FsmMO
 *
 *  Purpose:
 *     Derived from Fsm base class this handles all the states related to
 *     mobile orginated calls.
 *
 *
 *  Usage:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                          Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/2005   IMR-DESP-BSSAP-01-V1.1 ID::D0280
 *                                               ID::D0290
 *                                               ID::D0310
 *****************************************************************************/
class FsmMO : public Fsm,
                   public its::ITS_SingletonMultithreaded<FsmMO>
{
    public:
        FsmMO() : its:: ITS_SingletonMultithreaded<FsmMO>()
        {
            stateNull = new StateNull(*this);
            statePend = new StatePending(*this);
            stateInit  =  new StateInitiate(*this);
            stateProc = new StateProceed(*this);
            stateDelv = new StateDeliver(*this);
            stateConnInd = new StateConnInd(*this);
            stateActv = new StateActive(*this);
            stateDiscReq = new StateDisconnectRequest(*this);
            stateDiscInd  = new StateDisconnectIndication(*this);
            stateRelReq  =  new StateReleaseRequest(*this);
            stateRelInd  =  new StateReleaseInd(*this);

            // Normal call
            transition_null_to_pend =
               new ITS_BasicTransition<FsmMO>( *this, *stateNull, *statePend);
            transition_pend_to_init  =
               new ITS_BasicTransition<FsmMO>( *this, *statePend, *stateInit);
            transition_init_to_proc  =
               new ITS_BasicTransition<FsmMO>( *this, *stateInit, *stateProc);
            transition_proc_to_delv  =
               new ITS_BasicTransition<FsmMO>( *this, *stateProc, *stateDelv);
            transition_delv_to_conn =
              new ITS_BasicTransition<FsmMO>( *this, *stateDelv, *stateConnInd);
            transition_conn_to_actv =
              new ITS_BasicTransition<FsmMO>( *this, *stateConnInd, *stateActv);

            // Hop
            transition_init_to_delv  =
               new ITS_BasicTransition<FsmMO>( *this, *stateInit, *stateDelv);
            transition_init_to_conn  =
              new ITS_BasicTransition<FsmMO>( *this, *stateInit, *stateConnInd);
            transition_proc_to_conn  =
              new ITS_BasicTransition<FsmMO>( *this, *stateProc, *stateConnInd);


            // Local disconnect
            transition_actv_to_disreq =
              new ITS_BasicTransition<FsmMO>( *this, *stateActv, *stateDiscReq);
            transition_disreq_to_relInd =
            new ITS_BasicTransition<FsmMO>( *this, *stateDiscReq, *stateRelInd);
            transition_relInd_to_null =
            new ITS_BasicTransition<FsmMO>( *this, *stateRelInd, *stateNull);

            // Remote disconnect
            transition_actv_to_disind =
            new ITS_BasicTransition<FsmMO>( *this, *stateActv, *stateDiscInd);
            transition_disind_to_relreq  =
            new ITS_BasicTransition<FsmMO>( *this, *stateDiscInd, *stateRelReq);
            transition_relreq_to_null  =
            new ITS_BasicTransition<FsmMO>( *this, *stateRelReq, *stateNull);
            transition_proc_to_disreq =
            new ITS_BasicTransition<FsmMO>( *this, *stateProc, *stateDiscReq);
            transition_delv_to_disreq =
            new ITS_BasicTransition<FsmMO>( *this, *stateDelv, *stateDiscReq);

            // Timeout
            transition_disreq_to_relreq =
            new ITS_BasicTransition<FsmMO>( *this, *stateDiscReq, *stateRelReq);
            transition_init_to_disreq =
              new ITS_BasicTransition<FsmMO>( *this, *stateInit, *stateDiscReq);

            // Normal MO flow
            stateNull->DefineTransition(*transition_null_to_pend,
                                                BSSAP_MSG_CM_SERVICE_REQUEST);
            statePend->DefineTransition(*transition_pend_to_init,
                                                BSSAP_CC_MSG_SETUP);
            stateInit->DefineTransition(*transition_init_to_proc,
                                                BSSAP_CC_MSG_CALL_PROCEEDING);
            stateProc->DefineTransition(*transition_proc_to_delv,
                                                BSSAP_CC_MSG_ALERTING);
            stateDelv->DefineTransition(*transition_delv_to_conn,
                                                BSSAP_CC_MSG_CONNECT);
            stateConnInd->DefineTransition(*transition_conn_to_actv,
                                              BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE);
            // Hops
            stateInit->DefineTransition(*transition_init_to_conn,
                                                BSSAP_CC_MSG_CONNECT);
            stateInit->DefineTransition(*transition_init_to_delv,
                                                BSSAP_CC_MSG_ALERTING);
            stateProc->DefineTransition(*transition_proc_to_conn,
                                                BSSAP_CC_MSG_CONNECT);

            // Disconnects in between call setup
            stateInit->DefineTransition(*transition_init_to_disreq,
                                               BSSAP_CC_MSG_DISCONNECT); 
            stateProc->DefineTransition(*transition_proc_to_disreq,
                                                BSSAP_CC_MSG_DISCONNECT);
            stateDelv->DefineTransition(*transition_delv_to_disreq,
                                                BSSAP_CC_MSG_DISCONNECT);
 
            // Local Disconnect
            stateActv->DefineTransition(*transition_actv_to_disreq,
                                               BSSAP_CC_MSG_DISCONNECT);
            stateDiscReq->DefineTransition(*transition_disreq_to_relInd,
                                                BSSAP_CC_MSG_RELEASE_IND);
            stateRelInd->DefineTransition(*transition_relInd_to_null,
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);

            // Remote Disconnect
            stateActv->DefineTransition(*transition_actv_to_disind,
                                                BSSAP_CC_MSG_DISCONNECT_IND);
            stateDiscInd->DefineTransition(*transition_disind_to_relreq,
                                                BSSAP_CC_MSG_RELEASE);
            stateRelReq->DefineTransition(*transition_relreq_to_null,
                                                BSSAP_CC_MSG_RELEASE_COMPLETE);
            // Timeout
            stateDiscReq->DefineTransition(*transition_disreq_to_relreq,
                                                BSSAP_CC_MSG_RELEASE);
        }

        virtual ~FsmMO()
        {
            BSSAP_DEBUG(("FsmMO: State objects deleted\n"));

            delete stateNull;
            delete statePend;
            delete stateInit;
            delete stateProc;
            delete stateDelv;
            delete stateActv;
            delete stateDiscReq;
            delete stateDiscInd;
            delete stateRelReq;
            delete stateRelInd;
            delete stateConnInd;

            BSSAP_DEBUG(("FsmMO: transition objects deleted\n"));

            delete transition_null_to_pend;
            delete transition_pend_to_init;
            delete transition_init_to_proc;
            delete transition_init_to_delv;
            delete transition_proc_to_delv;
            delete transition_actv_to_disreq;
            delete transition_relreq_to_null;
            delete transition_disreq_to_relreq;
            delete transition_relInd_to_null;
            delete transition_actv_to_disind;
            delete transition_disind_to_relreq;
            delete transition_disreq_to_relInd;
            delete transition_init_to_disreq;
            delete transition_proc_to_disreq;
            delete transition_delv_to_conn;
            delete transition_conn_to_actv;
            delete transition_init_to_conn;
            delete transition_proc_to_conn;
            delete transition_delv_to_disreq;
        }

        static ITS_INT Initialize()
        {
            ITS_INT ret = 0;

            ret = ITS_SingletonMultithreaded<FsmMO>::Initialize();

            if (ret == ITS_SUCCESS)
            {
                BSSAP_DEBUG(("FsmMO: MO state table initialized\n"));
            }

            return (ret);
        }

        void SetState(ITS_OCTET event)
        {
            switch (event)
            {
                case BSSAP_MSG_CM_SERVICE_REQUEST:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*statePend));
                break;

                case BSSAP_CC_MSG_SETUP:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateInit));
                break;

                case BSSAP_CC_MSG_CALL_PROCEEDING:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateProc));
                break;

                case BSSAP_CC_MSG_ALERTING:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateDelv));
                break;

                case BSSAP_CC_MSG_CONNECT:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateConnInd));
                break;

                case  BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateActv));
                break;

                case BSSAP_CC_MSG_DISCONNECT:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateDiscReq));
                break;

                case BSSAP_CC_MSG_RELEASE_IND:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateRelInd));
                break;

                case  BSSAP_CC_MSG_DISCONNECT_IND:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateDiscInd));
                break;

                case BSSAP_CC_MSG_RELEASE:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateRelReq));
                break;

                default:
                    SetInitialState(
                        reinterpret_cast<
                            ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                                ITS_BasicEvent>&>
                                    (*stateNull));
                break;

            }
        }

        /*.interface:StateNull
        ***********************************************************************
        *  Interface:
        *     StateNull
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateNull : public ITS_BasicState<FsmMO>
        {
            public:
                StateNull(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateNull()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { 
                    BSSAP_DEBUG(("FsmMO: Call in NULL state\n"));
                }

                void ExecuteOut(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_SCCPHandler hndl;

                    BSSAP_DEBUG(("FsmMO: Leaving NULL state %s\n",
                                                  DTAP_STR(event.GetId())));

                    hndl.SendCR(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        /*.interface:StatePending
        ************************************************************************
        *  Interface:
        *     StatePending
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StatePending : public ITS_BasicState<FsmMO>
        {
            public:
                StatePending(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StatePending()

                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {}

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_SCCPHandler hndl;

                    BSSAP_DEBUG(("FsmMO: Leaving PENDING state %s\n",
                                                  DTAP_STR(event.GetId())));

                    hndl.SendDT1(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        /*.interface:StateInitiate
        ************************************************************************
        *  Interface:
        *     StateInitiate
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateInitiate : public ITS_BasicState<FsmMO>
        {
            public:
                StateInitiate(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateInitiate()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {
                }

                void ExecuteOut(ITS_BasicEvent& event)
                { 
                    BSSAP_DEBUG(("FsmMO: Leaving CALL INIT state %s\n",
                                                  DTAP_STR(event.GetId())));
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                {   
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        /*.interface:StateProceed
        ************************************************************************
        *  Interface:
        *     StateProceed
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateProceed : public ITS_BasicState<FsmMO>
        {
            public:
                StateProceed(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateProceed()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {   
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    intface.DispatchDtapToApp(ev->GetCallObject());
                }       
                     
                void ExecuteOut(ITS_BasicEvent& event)
                { 
                    BSSAP_DEBUG(("FsmMO: Leaving PROCEED state %s\n",
                                                  DTAP_STR(event.GetId())));
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        /*.interface:StateDeliver
        ************************************************************************
        *  Interface:
        *     StateDeliver
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateDeliver: public ITS_BasicState<FsmMO>
        {
            public:
                StateDeliver(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateDeliver()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    BSSAP_DEBUG(("FsmMO: Sending ALERT to App\n"));

                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAP_DEBUG(("FsmMO: Leaving DELIVER state %s\n",
                                                  DTAP_STR(event.GetId())));
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };

        /*.interface:StateConnInd
        ************************************************************************
        *  Interface:
        *     StateConnInd
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateConnInd: public ITS_BasicState<FsmMO>
        {
            public:
                StateConnInd(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateConnInd()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    BSSAP_DEBUG(("FsmMO: Sending CONNECT to App\n"));

                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAP_DEBUG(("FsmMO: Leaving CONN IND state %s\n",
                                                  DTAP_STR(event.GetId())));
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        /*.interface:StateActive
        ************************************************************************
        *  Interface:
        *     StateActive
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateActive: public ITS_BasicState<FsmMO>
        {
            public:
                StateActive(FsmMO& fsmParam) : ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateActive()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                {
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_SCCPHandler hndl;

                    BSSAP_DEBUG(("FsmMO: Sending CONN ACK to MSC\n"));

                    hndl.SendDT1(ev->GetCallObject());
 
                    BSSAP_DEBUG(("FsmMO: Call in ACTIVE state\n"));
                }

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAP_DEBUG(("FsmMO: Leaving ACTIVE state %s\n",
                                                  DTAP_STR(event.GetId())));
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        /*.interface:StateDisconnectRequest
        ************************************************************************
        *  Interface:
        *     StateDisconnectRequest
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        * 
        ***********************************************************************/
        class StateDisconnectRequest: public ITS_BasicState<FsmMO>
        {
            public:
                StateDisconnectRequest(FsmMO& fsmParam) :
                                        ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateDisconnectRequest()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_SCCPHandler hndl;

                    hndl.SendDT1(ev->GetCallObject());
                }

                void ExecuteOut(ITS_BasicEvent& event)
                { 
                    BSSAP_DEBUG(("FsmMO: Leaving DIS REQ state %s\n",
                                                  DTAP_STR(event.GetId())));
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        /*.interface:StateDisconnectIndication
        ************************************************************************
        *  Interface:
        *     StateDisconnectIndication
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateDisconnectIndication: public ITS_BasicState<FsmMO>
        {
            public:
                StateDisconnectIndication(FsmMO& fsmParam) :
                                                ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateDisconnectIndication()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    BSSAP_DEBUG(("FsmMO: Sending DISCONNECT to App\n"));

                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteOut(ITS_BasicEvent& event)
                {
                    BSSAP_DEBUG(("FsmMO: Leaving DIS IND state %s\n",
                                                  DTAP_STR(event.GetId())));
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };

        /*.interface:StateReleaseRequest
        ************************************************************************
        *  Interface:
        *     StateReleaseRequest
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateReleaseRequest: public ITS_BasicState<FsmMO>
        {
            public:
                StateReleaseRequest(FsmMO& fsmParam) :
                                             ITS_BasicState<FsmMO>(fsmParam)
                {};


                virtual ~StateReleaseRequest()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_SCCPHandler hndl;

                    BSSAP_DEBUG(("FsmMO: Sending RELEASE to MSC\n"));

                    hndl.SendDT1(ev->GetCallObject());
                }

                void ExecuteOut(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    BSSAP_DEBUG(("FsmMO: Leaving REL REQ state %s\n",
                                                  DTAP_STR(event.GetId())));

                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };

        /*.interface:StateReleaseInd
        ************************************************************************
        *  Interface:
        *     StateReleaseInd
        *
        *  Purpose:
        *
        *
        *
        *
        *
        *  Usage:
        *
        ***********************************************************************/
        class StateReleaseInd: public ITS_BasicState<FsmMO>
        {
            public:
                StateReleaseInd(FsmMO& fsmParam) :
                                           ITS_BasicState<FsmMO>(fsmParam)
                {};

                virtual ~StateReleaseInd()
                {};

                void ExecuteIn(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_Interface intface;

                    BSSAP_DEBUG(("FsmMO: Sending REL to App\n"));

                    intface.DispatchDtapToApp(ev->GetCallObject());
                }

                void ExecuteOut(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;
                    BSSAP_SCCPHandler hndl;

                    BSSAP_DEBUG(("FsmMO: Leaving REL IND state %s\n",
                                                  DTAP_STR(event.GetId())));

                    hndl.SendDT1(ev->GetCallObject());
                }

                void ExecuteEventNotDefined(ITS_BasicEvent& event)
                { 
                    BSSAPEvent* ev = (BSSAPEvent*)&event;

                    HandleAbnormalEvents(ev->GetCallObject());
                }
        };


        StateNull* stateNull;
        StatePending* statePend;
        StateInitiate* stateInit;
        StateProceed* stateProc;
        StateDeliver* stateDelv;
        StateActive* stateActv;
        StateDisconnectRequest* stateDiscReq;
        StateDisconnectIndication* stateDiscInd;
        StateReleaseRequest* stateRelReq;
        StateReleaseInd* stateRelInd; 
        StateConnInd* stateConnInd;

        ITS_BasicTransition<FsmMO>* transition_null_to_pend;
        ITS_BasicTransition<FsmMO>* transition_pend_to_init;
        ITS_BasicTransition<FsmMO>* transition_init_to_proc;
        ITS_BasicTransition<FsmMO>* transition_init_to_delv;
        ITS_BasicTransition<FsmMO>* transition_proc_to_delv;
        ITS_BasicTransition<FsmMO>* transition_actv_to_disreq;
        ITS_BasicTransition<FsmMO>* transition_disreq_to_relreq;

        ITS_BasicTransition<FsmMO>* transition_proc_to_conn;
        ITS_BasicTransition<FsmMO>* transition_init_to_conn;
        ITS_BasicTransition<FsmMO>* transition_conn_to_actv;
        ITS_BasicTransition<FsmMO>* transition_delv_to_conn;

        ITS_BasicTransition<FsmMO>* transition_actv_to_disind;
        ITS_BasicTransition<FsmMO>* transition_disind_to_relreq;
        ITS_BasicTransition<FsmMO>* transition_relreq_to_null;
        ITS_BasicTransition<FsmMO>* transition_disreq_to_relInd;
        ITS_BasicTransition<FsmMO>* transition_relInd_to_null;
        ITS_BasicTransition<FsmMO>* transition_init_to_disreq;
        ITS_BasicTransition<FsmMO>* transition_proc_to_disreq;
        ITS_BasicTransition<FsmMO>* transition_delv_to_disreq;

};


#endif
