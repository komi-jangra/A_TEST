////////////////////////////////////////////////////////////////////////////////
//
// Test12 (test unknown elements in SET, based on ANSI41 simplified types).
//
////////////////////////////////////////////////////////////////////////////////


#include <its++.h>

#if defined(WIN32)
#include <conio.h>
#endif // defined(WIN32)

#include <iostream>

#include <test12_feature_request_rrl.h>

#if !defined(ITS_NAMESPACE)
#error ANSI C++ compiler required.
#endif // !defined(ITS_NAMESPACE)

using namespace std;
using namespace its;
using namespace test12;

static void TestDecodeEncodeWithUnknownElements();


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

        TestDecodeEncodeWithUnknownElements();

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




void TestDecodeEncodeWithUnknownElements()
{
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //
    // Initialization.
    //

    //
    // The following call MUST be done before any decoding of a SET that
    // contains unknown elements (or an exception 'unknown element in set' will
    // be thrown during the decoding). Obviously this call becomes optional if
    // the SET ASN.1 type is marked as extensible in the ASN.1 module (with the
    // ASN.1 extension marker '...'). In 'test12.asn' the simplified type
    // 'FeatureRequestRRL' is marked as extensible, so the following call is 
    // optional. In our ANSI41D ASN.1 module, the types are not yet market as
    // extensible so the following call is MANDATORY. The best is to do it at
    // the start-up of the application (i.e. just after the entry point).
    //

    AsnOptions::GlobalSetDecodeSkipUnknownElementInSet();

    //
    // Note that the previous call is valid only for the ASN.1 types based on
    // SET. There is also a static member function named
    // 'GlobalSetDecodeSkipUnknownElementInSequence' in the class AsnOptions.
    // 


    //  
    // The following calls MUST be done to process (i.e. retrieve after decoding
    // and taking into account for encoding) the unknown elements in an ASN.1 
    // SET based type. The best is to do those calls at the start-up of the
    // application (i.e. just after the entry point).
    //

    AsnOptions::GlobalSetDecodeProcessUnknownElements();

    AsnOptions::GlobalSetEncodeProcessUnknownElements();


    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //
    // The following ASN.1 encoded value is an encoded value of the (simplified)
    // ASN.1 type FeatureRequestRRL defined in 'test12.asn'. Two unknown
    // elements have been added at the end of the SET encoded value:
    // [210] OCTET STRING => [9F 81 52 05 A1 A2 A3 A4 A5]
    // [211] OCTET STRING => [9F 81 53 03 B1 B2 B3].
    //

    byte encodedValue[] = {
        0x31, 0x42, 0x9F, 0x81, 0x12, 0x01, 0x02, 0x9F, 0x81, 0x23,
        0x04, 0xAA, 0xBB, 0xCC, 0xDD, 0xBF, 0x78, 0x22, 0xBF, 0x5B,
        0x0B, 0x89, 0x04, 0x01, 0x02, 0x03, 0x04, 0x9F, 0x4B, 0x02,
        0xF1, 0xF2, 0xBF, 0x5F, 0x11, 0x84, 0x05, 0x10, 0x20, 0x30,
        0x40, 0x50, 0x9F, 0x56, 0x07, 0x11, 0x22, 0x33, 0x44, 0x55,
        0x66, 0x77,  
        0x9F, 0x81, 0x52, 0x05, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5,
        0x9F, 0x81, 0x53, 0x03, 0xB1, 0xB2, 0xB3
    };




    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    //
    // Decode FeatureRequestRRL ASN.1 (simplified) encoded value.
    //

    vector<byte> encodedValueVect(encodedValue, encodedValue + 68);

    Octets octetsForDecode(encodedValueVect);


    FeatureRequestRRL*
        featureRequestRRLForDecode = 
            new FeatureRequestRRL();

    featureRequestRRLForDecode->Decode(octetsForDecode);


    //
    // Pretty print of 'featureRequestRRLForDecode'. Note that the unknown
    // elements don't show up in the pretty print.
    //

    cout << endl;
    cout << endl;
    cout << "Printing decoded featureRequestRRL..." << endl;
    cout << *featureRequestRRLForDecode;
    cout << endl;
    cout << endl;


    //
    // Retrieve and store in a vector all the unknown elements (since by 
    // definition they are unknown, we cannot decode them). 
    //

    vector<Octets> unknownElementStorage;

    for (
        size_t i = 0; 
        i < featureRequestRRLForDecode->GetUnknownElementSize(); 
        i++)
    {
        unknownElementStorage.
            push_back(
                featureRequestRRLForDecode->UnknownElementAt(i));
    }


    //
    // Pretty print all the stored unknown elements.
    //

    for (
        size_t j = 0;
        j < unknownElementStorage.size();
        j++)
    {
        cout << endl;
        cout << endl;
        cout << "Printing encoded unknown element number ";
        cout << (j + 1) << "..." << endl;
        cout << unknownElementStorage[j];
        cout << endl;
        cout << endl;
    }


    //
    // Do whatever is application required with decoded 
    // featureRequestRRLForDecode. 
    //


    ////////////////////////////////////////////////////////////////////////////    
    //
    // Encode a FeatureRequestRRL ASN.1 value with the previously stored unknown
    // elements added (at the end).
    //


    FeatureRequestRRL*
        featureRequestRRLForEncode = 
            new FeatureRequestRRL();

    FeatureResult* featureResult = new FeatureResult();

    featureResult->SetSuccessful();

    featureRequestRRLForEncode->SetFeatureResult(featureResult);
        
    byte array1[] = { 0xAAU, 0xBBU, 0xCCU, 0xDDU };

    vector<byte> v1(array1, array1 + 4);

    GroupInformation* groupInformation = new GroupInformation(v1);

    featureRequestRRLForEncode->SetGroupInformation(groupInformation);

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

    featureRequestRRLForEncode->SetTerminationList(terminationList);


    //
    //  Add previously stored unknown elements.
    //

    for (
        size_t k = 0;
        k < unknownElementStorage.size();
        k++)
    {
        featureRequestRRLForEncode->AddUnknownElement(unknownElementStorage[k]);
    }



    // Encode to ASN.1.

    Octets* octetsForEncode = featureRequestRRLForEncode->Encode();

    cout << endl;
    cout << endl;
    cout << "Printing ASN.1 encoded value (should match initial ";
    cout << "encodedValue constant array in code)..." << endl;
    cout << *octetsForEncode;
    cout << endl;
    cout << endl;



    // Release all the memory.

    delete featureRequestRRLForDecode;
    delete featureRequestRRLForEncode;
    delete octetsForEncode;
}




