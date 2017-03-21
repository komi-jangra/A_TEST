////////////////////////////////////////////////////////////////////////////////
//
// Test6 (GSMMAP V4).
//
////////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)
#pragma warning(disable:4786) 
#endif // defined(WIN32)

#include <iostream>
#include <conio.h>

#include <its++.h>


#include <AsnException.h>

#include <map_v4_insert_subscriber_data_arg.h>


using namespace std;
using namespace its;
using namespace map_v4;


static void Test();
static void TestSpeedAndMemory();
static void TestXml();

static bool testPrint = true;



int
main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;

    try
    {
        //int res = ITS_GlobalStart(0);

        //if (res != ITS_SUCCESS)
        //{
        //    throw ITS_Error(res, __FILE__, __LINE__);
        //}

        TestXml();

        //TestSpeedAndMemory();

        //ITS_GlobalStop();
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        //ITS_GlobalStop();
    }

    cout << "End of test..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();

    return 0;
}


//
// Macro to get size (count of items) of a statically dimensioned array.
//

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))


// Function template to convert arrays to vectors.

template <typename T> inline std::vector<T> ArrayToVector(T array[], size_t size)
{ return std::vector<T>(array, array + size); }


// Helper operator<< to print content of vector of bytes.

static string 
ByteToHexString(byte b)
{
    char strBuf[3];

    sprintf(strBuf, "%02X", b);

    return strBuf;
}

ostream& 
operator<< (ostream& os, const vector<byte>& vect)
{
    os << "{ ";

    for (int i = 0; i < vect.size(); i++)
    {
        os << "0x" << ByteToHexString(vect[i]).c_str();
        
        if (i != vect.size() - 1)
        {
            os << ",";
        }

        os << " ";
    }

    os << "}";

    return os;
}

void 
Test()
{
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // InsertSubscriberDataArg Encode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    InsertSubscriberDataArg* 
        insertSubscriberDataArg =
            new InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////
    // Set imsi.

    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    IMSI* imsi = new IMSI(ArrayToVector(array1, ARRAY_SIZE(array1)));

    insertSubscriberDataArg->SetImsi(imsi);


    ////////////////////////////////////////////////////////
    // Set msisdn.

    byte array2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

    ISDN_AddressString* iSDN_AddressString = 
        new ISDN_AddressString(ArrayToVector(array2, ARRAY_SIZE(array2)));

    insertSubscriberDataArg->SetMsisdn(iSDN_AddressString);


    ////////////////////////////////////////////////////////
    // Set category.

    byte array3[] = { 0x66U };

    Category* category = 
        new Category(ArrayToVector(array3, ARRAY_SIZE(array3)));

    insertSubscriberDataArg->SetCategory(category);


    ////////////////////////////////////////////////////////
    // Set subscriberStatus.

    SubscriberStatus* subscriberStatus = new SubscriberStatus();

    subscriberStatus->SetServiceGranted();

    insertSubscriberDataArg->SetSubscriberStatus(subscriberStatus);


    ////////////////////////////////////////////////////////
    // Set bearerServiceList.

    BearerServiceList* bearerServiceList = new BearerServiceList();

    // Insert 2 elements (Type BearerServiceCode).

    byte array4[] = { 0xAAU };

    BearerServiceCode* bearerServiceCode1 = 
        new BearerServiceCode(ArrayToVector(array4, ARRAY_SIZE(array4)));

    bearerServiceList->AddElement(bearerServiceCode1);

    byte array5[] = { 0xBBU };

    BearerServiceCode* bearerServiceCode2 = 
        new BearerServiceCode(ArrayToVector(array5, ARRAY_SIZE(array5)));

    bearerServiceList->AddElement(bearerServiceCode2);

    insertSubscriberDataArg->SetBearerServiceList(bearerServiceList);

    ////////////////////////////////////////////////////////
    // Set teleserviceList.

    TeleserviceList* teleserviceList = new TeleserviceList();

    // Insert 3 elements (type TeleserviceCode).

    byte array6[] = { 0xCCU };

    TeleserviceCode* teleserviceCode1 = 
        new TeleserviceCode(ArrayToVector(array6, ARRAY_SIZE(array6)));

    teleserviceList->AddElement(teleserviceCode1);

    byte array7[] = { 0xDDU };

    TeleserviceCode* teleserviceCode2 = 
        new TeleserviceCode(ArrayToVector(array7, ARRAY_SIZE(array7)));

    teleserviceList->AddElement(teleserviceCode2);

    byte array8[] = { 0xEEU };

    TeleserviceCode* teleserviceCode3 = 
        new TeleserviceCode(ArrayToVector(array8, ARRAY_SIZE(array8)));

    teleserviceList->AddElement(teleserviceCode3);

    insertSubscriberDataArg->SetTeleserviceList(teleserviceList);

    ////////////////////////////////////////////////////////
    // Set provisionedSS (type SS_InfoList).

    SS_InfoList* sS_InfoList = new SS_InfoList();

    // Insert 3 elements (type SS_Info).

    // First element.

    SS_Info* sS_Info1 = new SS_Info();

    // First element choice is forwardingInfo.

    ForwardingInfo* forwardingInfo = new ForwardingInfo();

    byte array9[] = { 0x33U };

    SS_Code* sS_Code = new SS_Code(ArrayToVector(array9, ARRAY_SIZE(array9)));

    forwardingInfo->SetSs_Code(sS_Code);

    ForwardingFeatureList* forwardingFeatureList = 
        new ForwardingFeatureList();

    // Insert 1 element (type ForwardingFeature).

    ForwardingFeature* forwardingFeature = new ForwardingFeature();

    BasicServiceCode* basicServiceCode = new BasicServiceCode();

    byte array10[] = { 0x44U };

    BearerServiceCode* bearerServiceCode = 
        new BearerServiceCode(ArrayToVector(array10, ARRAY_SIZE(array10)));

    basicServiceCode->SetChoiceBearerService(bearerServiceCode);

    forwardingFeature->SetBasicService(basicServiceCode);

    byte array11[] = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };

    ISDN_SubaddressString* iSDN_SubaddressString = 
        new ISDN_SubaddressString(ArrayToVector(array11, ARRAY_SIZE(array11)));

    forwardingFeature->SetForwardedToSubaddress(iSDN_SubaddressString);

    forwardingFeatureList->AddElement(forwardingFeature);

    forwardingInfo->SetForwardingFeatureList(forwardingFeatureList);

    sS_Info1->SetChoiceForwardingInfo(forwardingInfo);

    sS_InfoList->AddElement(sS_Info1);

    // Second element.

    SS_Info* sS_Info2 = new SS_Info();

    // Second element choice is cug-Info.

    CUG_Info* cUG_Info = new CUG_Info();

    CUG_SubscriptionList* cUG_SubscriptionList = new CUG_SubscriptionList();

    // Insert 2 elements (type CUG_Subscription).

    CUG_Subscription* cUG_Subscription1 = new CUG_Subscription();

    CUG_Index* cUG_Index1 = new CUG_Index(1999l);

    cUG_Subscription1->SetCug_Index(cUG_Index1);

    byte array12[] = { 0x11U, 0x22U, 0x33U, 0x44U };

    CUG_Interlock* cUG_Interlock1 = 
        new CUG_Interlock(ArrayToVector(array12, ARRAY_SIZE(array12)));

    cUG_Subscription1->SetCug_Interlock(cUG_Interlock1);

    IntraCUG_Options* intraCUG_Options1 = new IntraCUG_Options();

    intraCUG_Options1->SetNoCUG_Restrictions();

    cUG_Subscription1->SetIntraCUG_Options(intraCUG_Options1);

    cUG_SubscriptionList->AddElement(cUG_Subscription1);

    CUG_Subscription* cUG_Subscription2 = new CUG_Subscription();

    CUG_Index* cUG_Index2 = new CUG_Index(2001l);

    cUG_Subscription2->SetCug_Index(cUG_Index2);

    byte array13[] = { 0x44U, 0x33U, 0x22U, 0x11U };

    CUG_Interlock* cUG_Interlock2 = 
        new CUG_Interlock(ArrayToVector(array13, ARRAY_SIZE(array13)));

    cUG_Subscription2->SetCug_Interlock(cUG_Interlock2);

    IntraCUG_Options* intraCUG_Options2 = new IntraCUG_Options();

    intraCUG_Options2->SetNoCUG_Restrictions();

    cUG_Subscription2->SetIntraCUG_Options(intraCUG_Options2);

    cUG_SubscriptionList->AddElement(cUG_Subscription2);

    cUG_Info->SetCug_SubscriptionList(cUG_SubscriptionList);

    sS_Info2->SetChoiceCug_Info(cUG_Info);

    sS_InfoList->AddElement(sS_Info2);

    // Third element.

    SS_Info* sS_Info3 = new SS_Info();

    // Third element choice is ss-Data.

    SS_Data* sS_Data = new SS_Data();

    SS_SubscriptionOption* sS_SubscriptionOption = new SS_SubscriptionOption();

    CliRestrictionOption* cliRestrictionOption = new CliRestrictionOption();

    cliRestrictionOption->SetTemporaryDefaultRestricted();

    sS_SubscriptionOption->SetChoiceCliRestrictionOption(cliRestrictionOption);

    sS_Data->SetSs_SubscriptionOption(sS_SubscriptionOption);

    sS_Info3->SetChoiceSs_Data(sS_Data);

    sS_InfoList->AddElement(sS_Info3);

    insertSubscriberDataArg->SetProvisionedSS(sS_InfoList);

    ////////////////////////////////////////////////////////
    // Set odb-Data.

    ODB_Data* oDB_Data = new ODB_Data();

    bool array14[] = { true, false, true, false, true, false };

    ODB_GeneralData* oDB_GeneralData = 
        new ODB_GeneralData(ArrayToVector(array14, ARRAY_SIZE(array14)));

    oDB_Data->SetOdb_GeneralData(oDB_GeneralData);

    bool array15[] = { false, true, false, true };

    ODB_HPLMN_Data* oDB_HPLMN_Data = 
        new ODB_HPLMN_Data(ArrayToVector(array15, ARRAY_SIZE(array15)));

    oDB_Data->SetOdb_HPLMN_Data(oDB_HPLMN_Data);

    insertSubscriberDataArg->SetOdb_Data(oDB_Data);


    ////////////////////////////////////////////////////////
    // Print ASN.1 value before encoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value before encoding..." << endl;
        cout << endl;
        cout << *insertSubscriberDataArg;
        cout << endl;
    }

    ////////////////////////////////////////////////////////
    // Encode using ASN.1 BER.
    ////////////////////////////////////////////////////////

    Octets* octets = NULL;

    try
    {
        octets = insertSubscriberDataArg->Encode();
    }
    catch (AsnEncodeError& exc)
    {
        if (testPrint)
        {
            cout << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Exception during encoding phase..." << endl;
            cout << exc.GetDescription() << endl;
            cout << "Exit test..." << endl;

            exit(EXIT_FAILURE);
        }
    }

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << endl;
        cout << *octets;
        cout << endl;
    }

    // Release all allocated memory till current point.

    delete insertSubscriberDataArg;

    insertSubscriberDataArg = NULL;


    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // InsertSubscriberDataArg Decode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    /////////////////////////////
    // Decoded => suffix "Dec".
    /////////////////////////////

    // For all optionals we should check that they are present with the
    // OptionXXXXXX() member functions.

    InsertSubscriberDataArg*
        insertSubscriberDataArgDec = 
            new InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////
    // Decoding using ASN.1 BER.
    ////////////////////////////////////////////////////////

    try
    {
        insertSubscriberDataArgDec->Decode(*octets);
    }
    catch (AsnDecodeError& exc)
    {
        if (testPrint)
        {
            cout << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Exception during decoding phase..." << endl;
            cout << exc.GetDescription() << endl;
            cout << "Exit test..." << endl;

            exit(EXIT_FAILURE);
        }
    }

    ////////////////////////////////////////////////////////
    // Print ASN.1 value after decoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value after decoding..." << endl;
        cout << endl;
        cout << *insertSubscriberDataArgDec;
        cout << endl;
    }


    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Access ASN.1 value content after decoding..." << endl;
        cout << endl;
    }

    if (insertSubscriberDataArgDec->OptionImsi())
    {
        const IMSI& imsiDec = insertSubscriberDataArgDec->GetImsi();

        if (testPrint)
        {
            cout << endl;
            cout << imsiDec;
            cout << endl;
        }

        const vector<byte>& arrayDec = imsiDec.GetArray();

        if (testPrint)
        {
            cout << endl;
            cout << "IMSI raw content: " << arrayDec;
            cout << endl;
        }
    }

    if (insertSubscriberDataArgDec->OptionBearerServiceList())
    {
        const BearerServiceList& bearerServiceListDec =
            insertSubscriberDataArgDec->GetBearerServiceList();

        if (testPrint)
        {
            cout << endl;
            cout << "BearerServiceList has <";
            cout << bearerServiceListDec.Size();
            cout << "> element(s).";
            cout << endl;
        }

        // Get first element (size of SEQUENCE OF is >= 1).

        const BearerServiceCode& bearerServiceCodeDec = 
            bearerServiceListDec.ElementAt(0);

        if (testPrint)
        {
            cout << endl;
            cout << bearerServiceCodeDec;
            cout << endl;
        }

        const vector<byte>& arrayDec = bearerServiceCodeDec.GetArray();

        if (testPrint)
        {
            cout << endl;
            cout << "BearerServiceCode raw content: " << arrayDec;
            cout << endl;
        }
    }

    if (insertSubscriberDataArgDec->OptionProvisionedSS())
    {
        const SS_InfoList& sS_InfoListDec = 
            insertSubscriberDataArgDec->GetProvisionedSS();

        if (testPrint)
        {
            cout << endl;
            cout << "SS_InfoList has <";
            cout << sS_InfoListDec.Size();
            cout << "> element(s).";
            cout << endl;
        }

        // Get first element (size of SEQUENCE OF is >= 1).

        const SS_Info& sS_InfoDec =
            sS_InfoListDec.ElementAt(0);

        if (sS_InfoDec.ChoiceForwardingInfo())
        {
            const ForwardingInfo& forwardingInfoDec = 
                sS_InfoDec.GetChoiceForwardingInfo();

            const ForwardingFeatureList& forwardingFeatureListDec =
                forwardingInfoDec.GetForwardingFeatureList();

            if (testPrint)
            {
                cout << endl;
                cout << "ForwardingFeatureList has <";
                cout << forwardingFeatureListDec.Size();
                cout << "> element(s).";
                cout << endl;
            }

            // Get first element (size of SEQUENCE OF is >= 1).

            const ForwardingFeature& forwardingFeatureDec =
                forwardingFeatureListDec.ElementAt(0);

            if (testPrint)
            {
                cout << endl;
                cout << forwardingFeatureDec;
                cout << endl;
            }

            if (forwardingFeatureDec.OptionForwardedToSubaddress())
            {
                const ISDN_SubaddressString& iSDN_SubaddressStringDec =
                    forwardingFeatureDec.GetForwardedToSubaddress();

                if (testPrint)
                {
                    cout << endl;
                    cout << iSDN_SubaddressStringDec;
                    cout << endl;
                }

                const vector<byte>& arrayDec = 
                        iSDN_SubaddressStringDec.GetArray();

                if (testPrint)
                {
                    cout << endl;
                    cout << "ForwardedToSubaddress raw content: " << endl;
                    cout << arrayDec;
                    cout << endl;
                }
            }
        }
    }

    // To be continued...

    // Release all allocated memory.

    delete insertSubscriberDataArgDec;
    delete octets;
}

void 
TestSpeedAndMemory()
{
    testPrint = false;

    for (long i = 0; i < 10000l; i++)
    {
       Test();
    }

    testPrint = true;
}

void 
TestXml()
{
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // InsertSubscriberDataArg Encode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    InsertSubscriberDataArg* 
        insertSubscriberDataArg =
            new InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////
    // Set imsi.

    byte array1[] = { 0x01U, 0x02U, 0x03U, 0x04U }; 

    IMSI* imsi = new IMSI(ArrayToVector(array1, ARRAY_SIZE(array1)));

    insertSubscriberDataArg->SetImsi(imsi);


    ////////////////////////////////////////////////////////
    // Set msisdn.

    byte array2[] = { 0x11U, 0x22U, 0x33U, 0x44U, 0x55U };

    ISDN_AddressString* iSDN_AddressString = 
        new ISDN_AddressString(ArrayToVector(array2, ARRAY_SIZE(array2)));

    insertSubscriberDataArg->SetMsisdn(iSDN_AddressString);


    ////////////////////////////////////////////////////////
    // Set category.

    byte array3[] = { 0x66U };

    Category* category = 
        new Category(ArrayToVector(array3, ARRAY_SIZE(array3)));

    insertSubscriberDataArg->SetCategory(category);


    ////////////////////////////////////////////////////////
    // Set subscriberStatus.

    SubscriberStatus* subscriberStatus = new SubscriberStatus();

    subscriberStatus->SetServiceGranted();

    insertSubscriberDataArg->SetSubscriberStatus(subscriberStatus);


    ////////////////////////////////////////////////////////
    // Set bearerServiceList.

    BearerServiceList* bearerServiceList = new BearerServiceList();

    // Insert 2 elements (Type BearerServiceCode).

    byte array4[] = { 0xAAU };

    BearerServiceCode* bearerServiceCode1 = 
        new BearerServiceCode(ArrayToVector(array4, ARRAY_SIZE(array4)));

    bearerServiceList->AddElement(bearerServiceCode1);

    byte array5[] = { 0xBBU };

    BearerServiceCode* bearerServiceCode2 = 
        new BearerServiceCode(ArrayToVector(array5, ARRAY_SIZE(array5)));

    bearerServiceList->AddElement(bearerServiceCode2);

    insertSubscriberDataArg->SetBearerServiceList(bearerServiceList);

    ////////////////////////////////////////////////////////
    // Set teleserviceList.

    TeleserviceList* teleserviceList = new TeleserviceList();

    // Insert 3 elements (type TeleserviceCode).

    byte array6[] = { 0xCCU };

    TeleserviceCode* teleserviceCode1 = 
        new TeleserviceCode(ArrayToVector(array6, ARRAY_SIZE(array6)));

    teleserviceList->AddElement(teleserviceCode1);

    byte array7[] = { 0xDDU };

    TeleserviceCode* teleserviceCode2 = 
        new TeleserviceCode(ArrayToVector(array7, ARRAY_SIZE(array7)));

    teleserviceList->AddElement(teleserviceCode2);

    byte array8[] = { 0xEEU };

    TeleserviceCode* teleserviceCode3 = 
        new TeleserviceCode(ArrayToVector(array8, ARRAY_SIZE(array8)));

    teleserviceList->AddElement(teleserviceCode3);

    insertSubscriberDataArg->SetTeleserviceList(teleserviceList);

    ////////////////////////////////////////////////////////
    // Set provisionedSS (type SS_InfoList).

    SS_InfoList* sS_InfoList = new SS_InfoList();

    // Insert 3 elements (type SS_Info).

    // First element.

    SS_Info* sS_Info1 = new SS_Info();

    // First element choice is forwardingInfo.

    ForwardingInfo* forwardingInfo = new ForwardingInfo();

    byte array9[] = { 0x33U };

    SS_Code* sS_Code = new SS_Code(ArrayToVector(array9, ARRAY_SIZE(array9)));

    forwardingInfo->SetSs_Code(sS_Code);

    ForwardingFeatureList* forwardingFeatureList = 
        new ForwardingFeatureList();

    // Insert 1 element (type ForwardingFeature).

    ForwardingFeature* forwardingFeature = new ForwardingFeature();

    BasicServiceCode* basicServiceCode = new BasicServiceCode();

    byte array10[] = { 0x44U };

    BearerServiceCode* bearerServiceCode = 
        new BearerServiceCode(ArrayToVector(array10, ARRAY_SIZE(array10)));

    basicServiceCode->SetChoiceBearerService(bearerServiceCode);

    forwardingFeature->SetBasicService(basicServiceCode);

    byte array11[] = { 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U };

    ISDN_SubaddressString* iSDN_SubaddressString = 
        new ISDN_SubaddressString(ArrayToVector(array11, ARRAY_SIZE(array11)));

    forwardingFeature->SetForwardedToSubaddress(iSDN_SubaddressString);

    forwardingFeatureList->AddElement(forwardingFeature);

    forwardingInfo->SetForwardingFeatureList(forwardingFeatureList);

    sS_Info1->SetChoiceForwardingInfo(forwardingInfo);

    sS_InfoList->AddElement(sS_Info1);

    // Second element.

    SS_Info* sS_Info2 = new SS_Info();

    // Second element choice is cug-Info.

    CUG_Info* cUG_Info = new CUG_Info();

    CUG_SubscriptionList* cUG_SubscriptionList = new CUG_SubscriptionList();

    // Insert 2 elements (type CUG_Subscription).

    CUG_Subscription* cUG_Subscription1 = new CUG_Subscription();

    CUG_Index* cUG_Index1 = new CUG_Index(1999l);

    cUG_Subscription1->SetCug_Index(cUG_Index1);

    byte array12[] = { 0x11U, 0x22U, 0x33U, 0x44U };

    CUG_Interlock* cUG_Interlock1 = 
        new CUG_Interlock(ArrayToVector(array12, ARRAY_SIZE(array12)));

    cUG_Subscription1->SetCug_Interlock(cUG_Interlock1);

    IntraCUG_Options* intraCUG_Options1 = new IntraCUG_Options();

    intraCUG_Options1->SetNoCUG_Restrictions();

    cUG_Subscription1->SetIntraCUG_Options(intraCUG_Options1);

    cUG_SubscriptionList->AddElement(cUG_Subscription1);

    CUG_Subscription* cUG_Subscription2 = new CUG_Subscription();

    CUG_Index* cUG_Index2 = new CUG_Index(2001l);

    cUG_Subscription2->SetCug_Index(cUG_Index2);

    byte array13[] = { 0x44U, 0x33U, 0x22U, 0x11U };

    CUG_Interlock* cUG_Interlock2 = 
        new CUG_Interlock(ArrayToVector(array13, ARRAY_SIZE(array13)));

    cUG_Subscription2->SetCug_Interlock(cUG_Interlock2);

    IntraCUG_Options* intraCUG_Options2 = new IntraCUG_Options();

    intraCUG_Options2->SetNoCUG_Restrictions();

    cUG_Subscription2->SetIntraCUG_Options(intraCUG_Options2);

    cUG_SubscriptionList->AddElement(cUG_Subscription2);

    cUG_Info->SetCug_SubscriptionList(cUG_SubscriptionList);

    sS_Info2->SetChoiceCug_Info(cUG_Info);

    sS_InfoList->AddElement(sS_Info2);

    // Third element.

    SS_Info* sS_Info3 = new SS_Info();

    // Third element choice is ss-Data.

    SS_Data* sS_Data = new SS_Data();

    SS_SubscriptionOption* sS_SubscriptionOption = new SS_SubscriptionOption();

    CliRestrictionOption* cliRestrictionOption = new CliRestrictionOption();

    cliRestrictionOption->SetTemporaryDefaultRestricted();

    sS_SubscriptionOption->SetChoiceCliRestrictionOption(cliRestrictionOption);

    sS_Data->SetSs_SubscriptionOption(sS_SubscriptionOption);

    sS_Info3->SetChoiceSs_Data(sS_Data);

    sS_InfoList->AddElement(sS_Info3);

    insertSubscriberDataArg->SetProvisionedSS(sS_InfoList);

    ////////////////////////////////////////////////////////
    // Set odb-Data.

    ODB_Data* oDB_Data = new ODB_Data();

    bool array14[] = { true, false, true, false, true, false };

    ODB_GeneralData* oDB_GeneralData = 
        new ODB_GeneralData(ArrayToVector(array14, ARRAY_SIZE(array14)));

    oDB_Data->SetOdb_GeneralData(oDB_GeneralData);

    bool array15[] = { false, true, false, true };

    ODB_HPLMN_Data* oDB_HPLMN_Data = 
        new ODB_HPLMN_Data(ArrayToVector(array15, ARRAY_SIZE(array15)));

    oDB_Data->SetOdb_HPLMN_Data(oDB_HPLMN_Data);

    insertSubscriberDataArg->SetOdb_Data(oDB_Data);


    ////////////////////////////////////////////////////////
    // Print ASN.1 value before encoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value before encoding..." << endl;
        cout << endl;
        cout << *insertSubscriberDataArg;
        cout << endl;
    }

    ////////////////////////////////////////////////////////
    // Encode using ASN.1 XER.
    ////////////////////////////////////////////////////////

    Characters* characters = NULL;

    try
    {
        characters = insertSubscriberDataArg->EncodeToXml();
    }
    catch (AsnEncodeError& exc)
    {
        if (testPrint)
        {
            cout << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Exception during encoding phase..." << endl;
            cout << exc.GetDescription() << endl;
            cout << "Exit test..." << endl;

            exit(EXIT_FAILURE);
        }
    }

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 encoded value..." << endl;
        cout << endl;
        cout << *characters;
        cout << endl;
    }

    // Release all allocated memory till current point.

    delete insertSubscriberDataArg;

    insertSubscriberDataArg = NULL;

    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // InsertSubscriberDataArg Decode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    /////////////////////////////
    // Decoded => suffix "Dec".
    /////////////////////////////

    // For all optionals we should check that they are present with the
    // OptionXXXXXX() member functions.

    InsertSubscriberDataArg*
        insertSubscriberDataArgDec = 
            new InsertSubscriberDataArg();

    ////////////////////////////////////////////////////////
    // Decoding using ASN.1 BER.
    ////////////////////////////////////////////////////////

    try
    {
        insertSubscriberDataArgDec->DecodeFromXml(*characters);
    }
    catch (AsnCharactersDecodeError& exc)
    {
        if (testPrint)
        {
            cout << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Exception during decoding phase..." << endl;
            cout << exc.GetDescription() << endl;
            cout << "Exit test..." << endl;

            exit(EXIT_FAILURE);
        }
    }

    ////////////////////////////////////////////////////////
    // Print ASN.1 value after decoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value after decoding..." << endl;
        cout << endl;
        cout << *insertSubscriberDataArgDec;
        cout << endl;
    }


    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Access ASN.1 value content after decoding..." << endl;
        cout << endl;
    }

    if (insertSubscriberDataArgDec->OptionImsi())
    {
        const IMSI& imsiDec = insertSubscriberDataArgDec->GetImsi();

        if (testPrint)
        {
            cout << endl;
            cout << imsiDec;
            cout << endl;
        }

        const vector<byte>& arrayDec = imsiDec.GetArray();

        if (testPrint)
        {
            cout << endl;
            cout << "IMSI raw content: " << arrayDec;
            cout << endl;
        }
    }

    if (insertSubscriberDataArgDec->OptionBearerServiceList())
    {
        const BearerServiceList& bearerServiceListDec =
            insertSubscriberDataArgDec->GetBearerServiceList();

        if (testPrint)
        {
            cout << endl;
            cout << "BearerServiceList has <";
            cout << bearerServiceListDec.Size();
            cout << "> element(s).";
            cout << endl;
        }

        // Get first element (size of SEQUENCE OF is >= 1).

        const BearerServiceCode& bearerServiceCodeDec = 
            bearerServiceListDec.ElementAt(0);

        if (testPrint)
        {
            cout << endl;
            cout << bearerServiceCodeDec;
            cout << endl;
        }

        const vector<byte>& arrayDec = bearerServiceCodeDec.GetArray();

        if (testPrint)
        {
            cout << endl;
            cout << "BearerServiceCode raw content: " << arrayDec;
            cout << endl;
        }
    }

    if (insertSubscriberDataArgDec->OptionProvisionedSS())
    {
        const SS_InfoList& sS_InfoListDec = 
            insertSubscriberDataArgDec->GetProvisionedSS();

        if (testPrint)
        {
            cout << endl;
            cout << "SS_InfoList has <";
            cout << sS_InfoListDec.Size();
            cout << "> element(s).";
            cout << endl;
        }

        // Get first element (size of SEQUENCE OF is >= 1).

        const SS_Info& sS_InfoDec =
            sS_InfoListDec.ElementAt(0);

        if (sS_InfoDec.ChoiceForwardingInfo())
        {
            const ForwardingInfo& forwardingInfoDec = 
                sS_InfoDec.GetChoiceForwardingInfo();

            const ForwardingFeatureList& forwardingFeatureListDec =
                forwardingInfoDec.GetForwardingFeatureList();

            if (testPrint)
            {
                cout << endl;
                cout << "ForwardingFeatureList has <";
                cout << forwardingFeatureListDec.Size();
                cout << "> element(s).";
                cout << endl;
            }

            // Get first element (size of SEQUENCE OF is >= 1).

            const ForwardingFeature& forwardingFeatureDec =
                forwardingFeatureListDec.ElementAt(0);

            if (testPrint)
            {
                cout << endl;
                cout << forwardingFeatureDec;
                cout << endl;
            }

            if (forwardingFeatureDec.OptionForwardedToSubaddress())
            {
                const ISDN_SubaddressString& iSDN_SubaddressStringDec =
                    forwardingFeatureDec.GetForwardedToSubaddress();

                if (testPrint)
                {
                    cout << endl;
                    cout << iSDN_SubaddressStringDec;
                    cout << endl;
                }

                const vector<byte>& arrayDec = 
                        iSDN_SubaddressStringDec.GetArray();

                if (testPrint)
                {
                    cout << endl;
                    cout << "ForwardedToSubaddress raw content: " << endl;
                    cout << arrayDec;
                    cout << endl;
                }
            }
        }
    }

    // To be continued...

    // Release all allocated memory.

    delete insertSubscriberDataArgDec;
    delete characters;
}

