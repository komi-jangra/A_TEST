////////////////////////////////////////////////////////////////////////////////
//
// Finite State Machines unit tester - how to use example.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

// Advice: first understand well Test1 before trying to understand Test2.

#if defined(HPUX)
#include <iostream/iostream.h>
#else
#include <iostream>
#endif
#if defined(WIN32)
#include <conio.h>
#elif defined(unix)
#include <unistd.h>
#endif

#include <its_exception.h>
#include <its_fsm.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif    // defined(ITS_NAMESPACE)


// Forward declarations.
void Test1();
void Test2();


int main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;

    try
    {

        cout << endl << "==== Test1 =====" << endl << endl;

        Test1();

        cout << endl << "==== Test2 =====" << endl << endl;

        Test2();
    }
    catch (ITS_GenericException& exp)
    {
        cout << exp.GetDescription() << endl;
    }
    catch (exception& exp)
    {
        cout << exp.what() << endl;  
    }

    cout << "End of test..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Test1 function and previous related definitions.

// Simple State Machine with three states (A, B, C).

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class EventABC : public ITS_BasicEvent
{
public:

    EventABC(unsigned long idParam) : ITS_BasicEvent(idParam)
    {};
};


// Forward declaration.
class FsmABC;

void TransitionFunctionCToA(
                    ITS_BasicFunctionalTransition<FsmABC>& transition,
                    FsmABC& finiteStateMachine,
                    ITS_BasicState<FsmABC>& stateOrig,
                    ITS_BasicState<FsmABC>& stateDest,
                    ITS_BasicEvent& event)
{
    cout << "Inside transition function (C to A)..." << endl;
}


class FsmABC : public ITS_FiniteStateMachine<ITS_BasicEvent>
{
public:

    FsmABC()
    {
        stateA = new StateA(*this);
        stateB = new StateB(*this);
        stateC = new StateC(*this);

        SetInitialState(
            reinterpret_cast<
                ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                    ITS_BasicEvent>&>
                        (*stateA));

        transitionAToB = 
            new ITS_BasicTransition<FsmABC>(
                                        *this,
                                        *stateA,
                                        *stateB);

        transitionBToC = 
            new ITS_BasicTransition<FsmABC>(
                                        *this,
                                        *stateB,
                                        *stateC);

        transitionCToA =  
            new ITS_BasicFunctionalTransition<FsmABC>(
                                                    *this,
                                                    *stateC,
                                                    *stateA);

        transitionCToA->SetFunction(TransitionFunctionCToA);

        stateA->DefineTransition(*transitionAToB, 1);
        stateB->DefineTransition(*transitionBToC, 2);
        stateC->DefineTransition(*transitionCToA, 3);
    }

    virtual ~FsmABC()
    {
        delete stateA;
        delete stateB;
        delete stateC;

        delete transitionAToB;
        delete transitionBToC;
        delete transitionCToA;
    }

    class StateA : public ITS_BasicState<FsmABC> 
    {
    public:
        StateA(FsmABC& fsmParam) : ITS_BasicState<FsmABC>(fsmParam)
        {};

        virtual ~StateA()
        {};

        void ExecuteIn(ITS_BasicEvent& event)
        { cout << "Go in state A..." << endl; }

        void ExecuteOut(ITS_BasicEvent& event)
        { cout << "Go out of state A..." << endl; }
    };

    class StateB : public ITS_BasicState<FsmABC> 
    {
    public:
        StateB(FsmABC& fsmParam) : ITS_BasicState<FsmABC>(fsmParam)
        {};

        virtual ~StateB()
        {};

        void ExecuteIn(ITS_BasicEvent& event)
        { cout << "Go in state B..." << endl; }

        void ExecuteOut(ITS_BasicEvent& event)
        { cout << "Go out of state B..." << endl; }
    };

    class StateC : public ITS_BasicState<FsmABC> 
    {
    public:
        StateC(FsmABC& fsmParam) : ITS_BasicState<FsmABC>(fsmParam)
        {};

        virtual ~StateC()
        {};

        void ExecuteIn(ITS_BasicEvent& event)
        { cout << "Go in state C..." << endl; }

        void ExecuteOut(ITS_BasicEvent& event)
        { cout << "Go out of state C..." << endl; }
    };

    StateA* stateA;
    StateB* stateB;
    StateC* stateC;

    ITS_BasicTransition<FsmABC>* transitionAToB;
    ITS_BasicTransition<FsmABC>* transitionBToC;
    ITS_BasicFunctionalTransition<FsmABC>* transitionCToA;
};


void Test1()
{
    EventABC event1(1);
    EventABC event2(2);
    EventABC event3(3);

    FsmABC fsmABC;

    fsmABC.ProcessEvent(event1);
    fsmABC.ProcessEvent(event2);
    fsmABC.ProcessEvent(event3);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Test2 function and previous related definitions.

// State Machine with three states (X, Y, Z). State Y is
// a Sub State Machine with also three states (R, S, T).

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


class EventXYZ : public ITS_BasicEvent
{
public:

    EventXYZ(unsigned long idParam) : ITS_BasicEvent(idParam)
    {};
};


// Forward declaration.

class FsmXYZ;

void TransitionFunctionZToX(
                    ITS_BasicFunctionalTransition<FsmXYZ>& transition,
                    FsmXYZ& finiteStateMachine,
                    ITS_BasicState<FsmXYZ>& stateOrig,
                    ITS_BasicState<FsmXYZ>& stateDest,
                    ITS_BasicEvent& event)
{
    cout << "Inside transition function (Z to X)..." << endl;
}


class FsmXYZ : public ITS_FiniteStateMachine<ITS_BasicEvent>
{
public:

    FsmXYZ()
    {
        stateX = new StateX(*this);
        stateY = new StateY(*this);
        stateZ = new StateZ(*this);

        SetInitialState(
            reinterpret_cast<
                ITS_State<ITS_FiniteStateMachine<ITS_BasicEvent>,
                    ITS_BasicEvent>&>
                        (*stateX));

        transitionXToY = 
            new ITS_BasicTransition<FsmXYZ>(
                                        *this,
                                        *stateX,
                                        *stateY);

        transitionYToZ = 
            new ITS_BasicTransition<FsmXYZ>(
                                        *this,
                                        *stateY,
                                        *stateZ);

        transitionZToX = 
            new ITS_BasicFunctionalTransition<FsmXYZ>(
                                                    *this,
                                                    *stateZ,
                                                    *stateX);

        transitionZToX->SetFunction(TransitionFunctionZToX);

        stateX->DefineTransition(*transitionXToY, 1);
        stateY->DefineTransition(*transitionYToZ, 2);
        stateZ->DefineTransition(*transitionZToX, 3);
    }

    virtual ~FsmXYZ()
    {
        delete stateX;
        delete stateY;
        delete stateZ;

        delete transitionXToY;
        delete transitionYToZ;
        delete transitionZToX;
    }

    // Forward declaration.

    class StateY;

    static void TransitionFunctionTToR(
                    ITS_BasicFunctionalTransition<StateY>& transition,
                    StateY& finiteStateMachine,
                    ITS_BasicState<StateY>& stateOrig,
                    ITS_BasicState<StateY>& stateDest,
                    ITS_BasicEvent& event)
    {
        cout << "Inside transition function (T to R)..." << endl;
    }

    class StateX : public ITS_BasicState<FsmXYZ> 
    {
    public:
        StateX(FsmXYZ& fsmParam) : ITS_BasicState<FsmXYZ>(fsmParam)
        {};

        virtual ~StateX()
        {};

        void ExecuteIn(ITS_BasicEvent& event)
        { cout << "Go in state X..." << endl; }

        void ExecuteOut(ITS_BasicEvent& event)
        { cout << "Go out of state X..." << endl; }
    };


    class StateY : public ITS_BasicSubFiniteStateMachine<FsmXYZ> 
    {
    public:
        StateY(FsmXYZ& fsmParam)
        :    ITS_BasicSubFiniteStateMachine<FsmXYZ>(fsmParam)
        {
            stateR = new StateR(*this);
            stateS = new StateS(*this);
            stateT = new StateT(*this);

            SetInitialState(
                reinterpret_cast<
                    ITS_BasicState<
                        ITS_BasicSubFiniteStateMachine<FsmXYZ>
                            >&>(*stateR));

            transitionRToS = 
                new ITS_BasicTransition<StateY>(
                                            *this,
                                            *stateR,
                                            *stateS);

            transitionSToT = 
                new ITS_BasicTransition<StateY>(
                                            *this,
                                            *stateS,
                                            *stateT);

            transitionTToR = 
                new ITS_BasicFunctionalTransition<StateY>(
                                                        *this,
                                                        *stateT,
                                                        *stateR);

            transitionTToR->SetFunction(TransitionFunctionTToR);

            stateR->DefineTransition(*transitionRToS, 4);
            stateS->DefineTransition(*transitionSToT, 5);
            stateT->DefineTransition(*transitionTToR, 6);
        }
        
        virtual ~StateY()
        {
            delete stateR;
            delete stateS;
            delete stateT;

            delete transitionRToS;
            delete transitionSToT;
            delete transitionTToR;
        };

        void ExecuteIn(ITS_BasicEvent& event)
        { cout << "Go in state Y..." << endl; }

        void ExecuteOut(ITS_BasicEvent& event)
        { cout << "Go out of state Y..." << endl; }

        class StateR : public ITS_BasicState<StateY>
        {
        public:
            StateR(StateY& fsmParam) : ITS_BasicState<StateY>(fsmParam)
            {};

            virtual ~StateR()
            {};

            void ExecuteIn(ITS_BasicEvent& event)
            { cout << "Go in state R..." << endl; }

            void ExecuteOut(ITS_BasicEvent& event)
            { cout << "Go out of state R..." << endl; }
        };

        class StateS : public ITS_BasicState<StateY>
        {
        public:
            StateS(StateY& fsmParam) : ITS_BasicState<StateY>(fsmParam)
            {};

            virtual ~StateS()
            {};

            void ExecuteIn(ITS_BasicEvent& event)
            { cout << "Go in state S..." << endl; }

            void ExecuteOut(ITS_BasicEvent& event)
            { cout << "Go out of state S..." << endl; }
        };

        class StateT : public ITS_BasicState<StateY>
        {
        public:
            StateT(StateY& fsmParam) : ITS_BasicState<StateY>(fsmParam)
            {};

            virtual ~StateT()
            {};

            void ExecuteIn(ITS_BasicEvent& event)
            { cout << "Go in state T..." << endl; }

            void ExecuteOut(ITS_BasicEvent& event)
            { cout << "Go out of state T..." << endl; }
        };

        StateR* stateR;
        StateS* stateS;
        StateT* stateT;

        ITS_BasicTransition<StateY>* transitionRToS;
        ITS_BasicTransition<StateY>* transitionSToT;
        ITS_BasicFunctionalTransition<StateY>* transitionTToR;
    };

    class StateZ : public ITS_BasicState<FsmXYZ> 
    {
    public:
        StateZ(FsmXYZ& fsmParam) : ITS_BasicState<FsmXYZ>(fsmParam)
        {};

        virtual ~StateZ()
        {};

        void ExecuteIn(ITS_BasicEvent& event)
        { cout << "Go in state Z..." << endl; }

        void ExecuteOut(ITS_BasicEvent& event)
        { cout << "Go out of state Z..." << endl; }
    };

    StateX* stateX;
    StateY* stateY;
    StateZ* stateZ;

    ITS_BasicTransition<FsmXYZ>* transitionXToY;
    ITS_BasicTransition<FsmXYZ>* transitionYToZ;
    ITS_BasicFunctionalTransition<FsmXYZ>* transitionZToX;
};


void Test2()
{
    EventXYZ event1(1);
    EventXYZ event2(2);
    EventXYZ event3(3);
    EventXYZ event4(4);
    EventXYZ event5(5);
    EventXYZ event6(6);

    FsmXYZ fsmXYZ;

    cout << endl << "Going to process event 1..." << endl << endl;
    fsmXYZ.ProcessEvent(event1);

    cout << endl << "Going to process event 4..." << endl << endl;
    fsmXYZ.ProcessEvent(event4);

    cout << endl << "Going to process event 5..." << endl << endl;
    fsmXYZ.ProcessEvent(event5);

    cout << endl << "Going to process event 6..." << endl << endl;
    fsmXYZ.ProcessEvent(event6);

    cout << endl << "Going to process event 2..." << endl << endl;
    fsmXYZ.ProcessEvent(event2);

    cout << endl << "Going to process event 3..." << endl << endl;
    fsmXYZ.ProcessEvent(event3);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////