////////////////////////////////////////////////////////////////////////////////
//
// Test15 (test default values, based on INAP CS1 and CS2 simplified types).
//
////////////////////////////////////////////////////////////////////////////////


#include <its++.h>

#if defined(WIN32)
#include <conio.h>
#endif // defined(WIN32)

#include <iostream>

#include <AsnException.h>

#include <test15_event_report_bcsm_arg.h>
#include <test15_prompt_and_collect_user_information_arg.h>

#if !defined(ITS_NAMESPACE)
#error ANSI C++ compiler required.
#endif // !defined(ITS_NAMESPACE)

using namespace std;
using namespace its;
using namespace test15;

static void TestEventReportBCSMArg();
static void TestPromptAndCollectUserInformationArg();

static void TestXmlEventReportBCSMArg();
static void TestXmlPromptAndCollectUserInformationArg();

static bool testPrint = true;


int main(int argc, char* argv[])
{
    cout << "Begin test..." << endl;

    try
    {
        TestEventReportBCSMArg();

        cout << endl << endl << endl;

        TestXmlEventReportBCSMArg();

        cout << endl << endl << endl;

        TestPromptAndCollectUserInformationArg();

        cout << endl << endl << endl;

        TestPromptAndCollectUserInformationArg();

        cout << endl << endl << endl;
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;
    }

    cout << "End of test..." << endl;
    
#if defined(WIN32)    
    
    // To stop here in console application.
    cout << "Type any key to quit...";
    char c = getch();
    
#endif // defined(WIN32)

    return 0;
}


static void 
TestEventReportBCSMArg()
{
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // EventReportBCSMArg Encode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    EventReportBCSMArg*
        eventReportBCSMArg = 
            new EventReportBCSMArg();

    EventTypeBCSM*
        eventTypeBCSM =
            new EventTypeBCSM(1l);

    eventReportBCSMArg->SetEventTypeBCSM(eventTypeBCSM);

    ////////////////////////////////////////////////////////
    // Print ASN.1 value before encoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value before encoding..." << endl;
        cout << endl;
        cout << *eventReportBCSMArg;
        cout << endl;
    }

    ////////////////////////////////////////////////////////
    // Encode using ASN.1 BER.
    ////////////////////////////////////////////////////////

    Octets* octets = NULL;

    try
    {
        octets = eventReportBCSMArg->Encode();
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

    delete eventReportBCSMArg;

    eventReportBCSMArg = NULL;


    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // EventReportBCSMArg Decode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    /////////////////////////////
    // Decoded => suffix "Dec".
    /////////////////////////////

    EventReportBCSMArg*
        eventReportBCSMArgDec = 
            new EventReportBCSMArg();

    ////////////////////////////////////////////////////////
    // Decoding using ASN.1 BER.
    ////////////////////////////////////////////////////////

    try
    {
        eventReportBCSMArgDec->Decode(*octets);
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
        cout << *eventReportBCSMArgDec;
        cout << endl;
    }

    // Release all allocated memory.

    delete eventReportBCSMArgDec;
    delete octets;
}


static void 
TestXmlEventReportBCSMArg()
{
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // EventReportBCSMArg Encode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    EventReportBCSMArg*
        eventReportBCSMArg = 
            new EventReportBCSMArg();

    EventTypeBCSM*
        eventTypeBCSM =
            new EventTypeBCSM(1l);

    eventReportBCSMArg->SetEventTypeBCSM(eventTypeBCSM);

    ////////////////////////////////////////////////////////
    // Print ASN.1 value before encoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value before encoding..." << endl;
        cout << endl;
        cout << *eventReportBCSMArg;
        cout << endl;
    }

    ////////////////////////////////////////////////////////
    // Encode using ASN.1 XER.
    ////////////////////////////////////////////////////////

    Characters* characters = NULL;

    try
    {
        characters = eventReportBCSMArg->EncodeToXml();
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

    delete eventReportBCSMArg;

    eventReportBCSMArg = NULL;


    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // EventReportBCSMArg Decode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    /////////////////////////////
    // Decoded => suffix "Dec".
    /////////////////////////////

    EventReportBCSMArg*
        eventReportBCSMArgDec = 
            new EventReportBCSMArg();

    ////////////////////////////////////////////////////////
    // Decoding using ASN.1 XER.
    ////////////////////////////////////////////////////////

    try
    {
        eventReportBCSMArgDec->DecodeFromXml(*characters);
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
        cout << *eventReportBCSMArgDec;
        cout << endl;
    }

    // Release all allocated memory.

    delete eventReportBCSMArgDec;
    delete characters;
}


static void 
TestPromptAndCollectUserInformationArg()
{
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // PromptAndCollectUserInformationArg Encode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    PromptAndCollectUserInformationArg*
        promptAndCollectUserInformationArg =
            new PromptAndCollectUserInformationArg();

    CollectedDigits*
        collectedDigits =
            new CollectedDigits();

    CollectedDigits::MaximumNbOfDigits*
        maximumNbOfDigits = 
            new CollectedDigits::MaximumNbOfDigits(16l);

    collectedDigits->SetMaximumNbOfDigits(maximumNbOfDigits);

    CollectedInfo*
        collectedInfo =
            new CollectedInfo();

    collectedInfo->SetChoiceCollectedDigits(collectedDigits);

    promptAndCollectUserInformationArg->SetCollectedInfo(collectedInfo);

    ////////////////////////////////////////////////////////
    // Print ASN.1 value before encoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value before encoding..." << endl;
        cout << endl;
        cout << *promptAndCollectUserInformationArg;
        cout << endl;
    }

    ////////////////////////////////////////////////////////
    // Encode using ASN.1 BER.
    ////////////////////////////////////////////////////////

    Octets* octets = NULL;

    try
    {
        octets = promptAndCollectUserInformationArg->Encode();
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

    delete promptAndCollectUserInformationArg;

    promptAndCollectUserInformationArg = NULL;

    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // PromptAndCollectUserInformationArg Decode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    /////////////////////////////
    // Decoded => suffix "Dec".
    /////////////////////////////

    PromptAndCollectUserInformationArg*
        promptAndCollectUserInformationArgDec = 
            new PromptAndCollectUserInformationArg();

    ////////////////////////////////////////////////////////
    // Decoding using ASN.1 BER.
    ////////////////////////////////////////////////////////

    try
    {
        promptAndCollectUserInformationArgDec->Decode(*octets);
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
        cout << *promptAndCollectUserInformationArgDec;
        cout << endl;
    }

    // Release all allocated memory.

    delete promptAndCollectUserInformationArgDec;
    delete octets;
}


static void 
TestXmlPromptAndCollectUserInformationArg()
{
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // PromptAndCollectUserInformationArg Encode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    PromptAndCollectUserInformationArg*
        promptAndCollectUserInformationArg =
            new PromptAndCollectUserInformationArg();

    CollectedDigits*
        collectedDigits =
            new CollectedDigits();

    CollectedDigits::MaximumNbOfDigits*
        maximumNbOfDigits = 
            new CollectedDigits::MaximumNbOfDigits(16l);

    collectedDigits->SetMaximumNbOfDigits(maximumNbOfDigits);

    CollectedInfo*
        collectedInfo =
            new CollectedInfo();

    collectedInfo->SetChoiceCollectedDigits(collectedDigits);

    promptAndCollectUserInformationArg->SetCollectedInfo(collectedInfo);

    ////////////////////////////////////////////////////////
    // Print ASN.1 value before encoding.
    ////////////////////////////////////////////////////////

    if (testPrint)
    {
        cout << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Printing ASN.1 value before encoding..." << endl;
        cout << endl;
        cout << *promptAndCollectUserInformationArg;
        cout << endl;
    }

    ////////////////////////////////////////////////////////
    // Encode using ASN.1 XER.
    ////////////////////////////////////////////////////////

    Characters* characters = NULL;

    try
    {
        characters = promptAndCollectUserInformationArg->EncodeToXml();
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

    delete promptAndCollectUserInformationArg;

    promptAndCollectUserInformationArg = NULL;

    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    // PromptAndCollectUserInformationArg Decode part.
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////

    /////////////////////////////
    // Decoded => suffix "Dec".
    /////////////////////////////

    PromptAndCollectUserInformationArg*
        promptAndCollectUserInformationArgDec = 
            new PromptAndCollectUserInformationArg();

    ////////////////////////////////////////////////////////
    // Decoding using ASN.1 XER.
    ////////////////////////////////////////////////////////

    try
    {
        promptAndCollectUserInformationArgDec->DecodeFromXml(*characters);
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
        cout << *promptAndCollectUserInformationArgDec;
        cout << endl;
    }

    // Release all allocated memory.

    delete promptAndCollectUserInformationArgDec;
    delete characters;
}

