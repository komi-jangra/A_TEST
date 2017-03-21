////////////////////////////////////////////////////////////////////////////////
//
// Test13 (test ASN.1 runtime in multithreaded conditions, based on ANSI41
// simplified types).
//
////////////////////////////////////////////////////////////////////////////////


#include <its++.h>

#if defined(WIN32)
#include <conio.h>
#endif // defined(WIN32)

#include <iostream>

#include <its_thread.h>
#include <its_timers.h>

#include <test13_feature_request_rrl.h>

#if !defined(ITS_NAMESPACE)
#error ANSI C++ compiler required.
#endif // !defined(ITS_NAMESPACE)

using namespace std;
using namespace its;
using namespace test13;

static void DoDecodeEncodeCycle();
static bool testPrint = false;






class WorkerThread : public ITS_Thread
{
public:
    WorkerThread(ITS_THREAD_FUNC function) 
    :    ITS_Thread(0, function)
    {
        // Nothing else to do.
    }


    virtual ~WorkerThread()
    {
        // Nothing to do.
    }

#if defined(WIN32)
    static unsigned __stdcall WorkerFunction(void *arg);
#else
    static void * WorkerFunction(void *arg);
#endif
};


#if defined(WIN32)
unsigned __stdcall
#else
void*
#endif
WorkerThread::WorkerFunction(void *arg)
{
    WorkerThread* worker = (WorkerThread *)arg;

    for (size_t i = 0; i < 10000000; i++)
    {
        DoDecodeEncodeCycle();
    }

    delete worker;

    WorkerThread::Exit(NULL);

    return 0;
}


int main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;

    try
    {
        int res = ITS_GlobalStart(0);

        if (res != ITS_SUCCESS)
        {
            throw ITS_Error(res, __FILE__, __LINE__);
        }

        for (int i = 0; i < 32; i++)
        {
            WorkerThread *workerThread = 
                new WorkerThread(WorkerThread::WorkerFunction);

            if (workerThread->Enter((void *)workerThread) != ITS_SUCCESS)
            {
                cout << endl;
                cout << "Failed to create thread number " << i << "...";
                cout << endl;
                cout << endl;
            }
        }


        // Wait for ever...

        while(true)
        {
            TIMERS_Sleep(10);
        }

        ITS_GlobalStop();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        ITS_GlobalStop();
    }

    cout << "End of test..." << endl;
    
#if defined(WIN32)    
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();
    
#endif // defined(WIN32)

    return 0;
}




void DoDecodeEncodeCycle()
{
    FeatureRequestRRL*
        featureRequestRRL = 
            new FeatureRequestRRL();

    FeatureResult* featureResult = new FeatureResult();

    featureResult->SetSuccessful();

    featureRequestRRL->SetFeatureResult(featureResult);
        
    byte array1[] = { 0xAAU, 0xBBU, 0xCCU, 0xDDU };

    vector<byte> v1(array1, array1 + 4);

    GroupInformation* groupInformation = new GroupInformation(v1);

    featureRequestRRL->SetGroupInformation(groupInformation);

    TerminationList* terminationList = new TerminationList();

    //
    // Local scope typedef still needed because CHOICE is not a Local Reference.
    // (And CHOICE is an anonymous type of SEQUENCE OF.)
    //

    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE
                        CHOICE;
                
    CHOICE* choice1 = new CHOICE();

    LocalTermination* localTermination = new LocalTermination();

    byte array2[] = { 0x01U, 0x02U, 0x03U, 0x04U };

    vector<byte> v2(array2, array2 + 4);

    ElectronicSerialNumber* electronicSerialNumber = 
        new ElectronicSerialNumber(v2);

    localTermination->
        SetElectronicSerialNumber(
            electronicSerialNumber);

    byte array3[] = { 0xF1U, 0xF2U };

    vector<byte> v3(array3, array3 + 2);

    AlertCode* alertCode = new AlertCode(v3);

    localTermination->
        SetAlertCode(
            alertCode);

    choice1->SetChoiceLocalTermination(localTermination);

    terminationList->AddElement(choice1);

    CHOICE* choice2 = new CHOICE();

    PSTNTermination* pSTNTermination = new PSTNTermination();

    byte array4[] = { 0x10U, 0x20U, 0x30U, 0x40U, 0x50U };

    vector<byte> v4(array4, array4 + 5);

    DestinationDigits* destinationDigits = new DestinationDigits(v4);
    
    pSTNTermination->SetDestinationDigits(destinationDigits);

    byte array5[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U, 0x66U, 0x77U };

    vector<byte> v5(array5, array5 + 7);

    CarrierDigits* carrierDigits = new CarrierDigits(v5);
    
    pSTNTermination->SetCarrierDigits(carrierDigits);

    choice2->SetChoicePSTNTermination(pSTNTermination);

    terminationList->AddElement(choice2);

    featureRequestRRL->SetTerminationList(terminationList);

    // Encode to ASN.1.

    Octets* octets = featureRequestRRL->Encode();

    if (testPrint)
    {
        cout << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << *octets;
        cout << endl;
    }

    // Decode from ASN.1 => suffix "After".
    // For all optionals we should check that they are present
    // with the OptionXXXXXXXX() member functions.

    FeatureRequestRRL*
        featureRequestRRLAfter = 
            new FeatureRequestRRL();

    featureRequestRRLAfter->Decode(*octets);

    const FeatureResult& featureResultAfter 
        = featureRequestRRLAfter->GetFeatureResult();

    const GroupInformation& groupInformationAfter
        = featureRequestRRLAfter->GetGroupInformation();

    const TerminationList& terminationListAfter
        = featureRequestRRLAfter->GetTerminationList();

    const CHOICE& choice1After = terminationListAfter.ElementAt(0);

    const CHOICE& choice2After = terminationListAfter.ElementAt(1);

    if (choice1After.ChoiceLocalTermination())
    {
        const LocalTermination& localTerminationAfter = 
            choice1After.GetChoiceLocalTermination();

        const ElectronicSerialNumber& electronicSerialNumberAfter =
            localTerminationAfter.GetElectronicSerialNumber();

        const AlertCode& alertCodeAfter = 
            localTerminationAfter.GetAlertCode();

    }

    if (choice2After.ChoicePSTNTermination())
    {
        const PSTNTermination& pSTNTerminationAfter = 
            choice2After.GetChoicePSTNTermination();

        const DestinationDigits& destinationDigitsAfter =
            pSTNTerminationAfter.GetDestinationDigits();

        const CarrierDigits& carrierDigitsAfter = 
            pSTNTerminationAfter.GetCarrierDigits();

    }

    if (testPrint)
    {
        cout << endl;
        cout << "Printing decoded featureRequestRRL..." << endl;
        cout << *featureRequestRRLAfter;
        cout << endl;
    }

    // Release all the memory.

    delete featureRequestRRLAfter;
    delete featureRequestRRL;
    delete octets;
}




