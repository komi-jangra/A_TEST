////////////////////////////////////////////////////////////////////////////////
//
// Test2.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)
#pragma warning(disable:4786) 
#endif // defined(WIN32)

#include <iostream>
#include <conio.h>

#include <its++.h>
#include <its_ss7_stubs.h>

#include <test2_feature_request_rrl.h>


#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
#endif // defined(ITS_NAMESPACE)


static void Test();
static void TestSpeedAndMemory();

static bool testPrint = true;

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

        Test();

        //TestSpeedAndMemory();

        ITS_GlobalStop();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        ITS_GlobalStop();
    }

    cout << "End of test..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();

    return 0;
}


void Test()
{
    FeatureRequestRRL*
        featureRequestRRL = 
            new FeatureRequestRRL();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                FeatureResult 
                    FeatureResult;

    FeatureResult* featureResult = new FeatureResult();

    featureResult->SetSuccessful();

    featureRequestRRL->SetFeatureResult(featureResult);

    // Local scope typedef.
    typedef FeatureRequestRRL::
                GroupInformation
                    GroupInformation;
        
    byte array1[] = { 0xAAU, 0xBBU, 0xCCU, 0xDDU };

    vector<byte> v1(array1, array1 + 4);

    GroupInformation* groupInformation = new GroupInformation(v1);

    featureRequestRRL->SetGroupInformation(groupInformation);

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList
                    TerminationList;

    TerminationList* terminationList = new TerminationList();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE
                        CHOICE;
                
    CHOICE* choice1 = new CHOICE();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        LocalTermination
                            LocalTermination;

    LocalTermination* localTermination = new LocalTermination();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        LocalTermination::
                            ElectronicSerialNumber
                                ElectronicSerialNumber;

    byte array2[] = { 0x01U, 0x02U, 0x03U, 0x04U };

    vector<byte> v2(array2, array2 + 4);

    ElectronicSerialNumber* electronicSerialNumber = 
        new ElectronicSerialNumber(v2);

    localTermination->
        SetElectronicSerialNumber(
            electronicSerialNumber);

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        LocalTermination::
                            AlertCode
                                AlertCode;

    byte array3[] = { 0xF1U, 0xF2U };

    vector<byte> v3(array3, array3 + 2);

    AlertCode* alertCode = new AlertCode(v3);

    localTermination->
        SetAlertCode(
            alertCode);

    choice1->SetChoiceLocalTermination(localTermination);

    terminationList->AddElement(choice1);

    CHOICE* choice2 = new CHOICE();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        PSTNTermination
                            PSTNTermination;

    PSTNTermination* pSTNTermination = new PSTNTermination();

    // Local scope typedef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        PSTNTermination::
                            DestinationDigits
                                DestinationDigits;

    byte array4[] = { 0x10U, 0x20U, 0x30U, 0x40U, 0x50U };

    vector<byte> v4(array4, array4 + 5);

    DestinationDigits* destinationDigits = new DestinationDigits(v4);
    
    pSTNTermination->SetDestinationDigits(destinationDigits);

    // Local scope typdef.
    typedef FeatureRequestRRL::
                TerminationList::
                    CHOICE::
                        PSTNTermination::
                            CarrierDigits
                                CarrierDigits;

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

void TestSpeedAndMemory()
{
    testPrint = false;

    for (long i = 0; i < 10000l; i++)
    {
       Test();
    }

    testPrint = true;
}

