////////////////////////////////////////////////////////////////////////////////
//
// Quick unit tester.
//
////////////////////////////////////////////////////////////////////////////////

#include <its++.h>

#if !defined(HPUX)
#include <iostream>
#else
#include <iostream/iostream.h>
#endif
#if defined(WIN32)
#include <conio.h>
#include <crtdbg.h>
#elif defined(unix)
#include <unistd.h>
#endif

#include <stdio.h>

#include <its_event_log.h>
#include <its_exception_log.h>
#include <its_exception.h>

#include <Asn.h>
#include <Octets.h>
#include <Tag.h>
#include <Length.h>
#include <AsnDescObject.h>
#include <AsnInteger.h>
#include <AsnDescInteger.h>
#include <AsnBoolean.h>
#include <AsnDescBoolean.h>
#include <AsnSet.h>
#include <AsnDescSet.h>
#include <AsnChoice.h>
#include <AsnDescChoice.h>
#include <AsnSequenceOf.h>
#include <AsnDescSequenceOf.h>
#include <AsnOctetString.h>
#include <AsnDescOctetString.h>
#include <AsnSequence.h>
#include <AsnDescSequence.h>
#include <AsnException.h>



// Windows NT only (use CRTDBG to check memory leaks).
// The following macros set and clear, respectively, given bits
// of the C runtime library debug flag, as specified by a bitmask.

#if defined(WIN32)

#ifdef   _DEBUG
#define  SET_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  CLEAR_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else
#define  SET_CRT_DEBUG_FIELD(a)   ((void) 0)
#define  CLEAR_CRT_DEBUG_FIELD(a) ((void) 0)
#endif  // _DEBUG

#endif  // defined(WIN32)



#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif    // defined(ITS_NAMESPACE)

static void Test1();
static void Test2();
static void Test3(); 
static void Test4();
static void Test5();
static void Test6();
static void Test7();
static void Test8();
static void Test8();
static void Test9();
static void Test10();
static void Test11();

static void TestMemory();

static void TestExceptions();

static bool testPrint = true;

int main(int argc, char* argv[])
{

#if defined(WIN32)

// Send all reports to stdout.

_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
_CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
_CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
_CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );

#endif  // defined(WIN32)

    cout << "Begin test..." << endl;

    try
    {
        Test1();

        Test2();

        Test3();

        Test4();

        Test5();

        Test6();

        Test7();

        Test8();

        Test9();

        Test10();

        Test11();

        TestExceptions();
        
        TestMemory();

    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;
    }

    cout << "End of test..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";
#if defined(WIN32)
    char c = getch();
#elif defined(unix)
    char c = getchar();
#endif

#if defined(WIN32)

   // Set the debug-heap flag so that memory leaks are reported when
   // the process terminates. Then, exit.

   SET_CRT_DEBUG_FIELD( _CRTDBG_LEAK_CHECK_DF );

#endif  // defined(WIN32)

    return 0;
}

void TestMemory()
{
    testPrint = false;

    for (long i = 0; i < 10000l; i++)
    {
        Test1();

        Test2();

        Test3();

        Test4();

        Test5();

        Test6();

        Test7();

        Test8();

        Test9();

        Test10();

        //
        // Small leak (?) in std::ostrstream (only if one exception is thrown).
        // std::ostrstream is used by AsnObject::GetDecodeExtendedErrorText.
        //

        // Test11();
    }

    testPrint = true;
}


void TestExceptions()
{
    cout << "Test with exception (source is ASN RUNTIME)..." << endl;

    // Exception Log settings...

    ITS_NtEventLog::RegistryRemoveSource("ASN RUNTIME");

    ITS_NtEventLog::RegistryCreateSource("ASN RUNTIME", "ItsMsgFile.dll");

    static ITS_NtExceptionLog exceptionLog("ASN RUNTIME");

    ITS_GenericException::SetExceptionLog(exceptionLog);

    Octets* octets = NULL;

    try
    {
        // Test to throw one encode exception...

        byte array1[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                         0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                         0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                         0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                         0x01, 0x02, 0x03, 0x04, 0x05,
                         0x06, 0x07, 0x08 };

        vector<byte> vector1(array1, array1 + 28);

        AsnDescOctetString* descOctetString1 = new AsnDescOctetString();

        descOctetString1->SetClauseSize();
        descOctetString1->SetMinSize(22);
        descOctetString1->SetMaxSize(22);

        AsnOctetString* octetString1 = new AsnOctetString(descOctetString1, vector1);

        // Next should throw ASN.1 encode exception.

        Octets* octets = octetString1->Encode();
    }
    catch (ITS_GenericException& exp)
    {
        cout << exp.GetDescription() << endl;

        exp.Log();
    }
    catch (exception& exp)
    {
        cout << exp.what() << endl;  
    }

    if (octets != NULL)
    {
        delete octets;

        octets = NULL;
    }

    try
    {
        // Test to throw one decode exception...

        byte array1[1024];

        for (int j = 0; j < 1024; j++)
        {
            array1[j] = (byte)(j % 256);
        }

        vector<byte> vector1(array1, array1 + 1024);

        AsnDescOctetString* descOctetString1 = new AsnDescOctetString();

        descOctetString1->SetClauseSize();
        descOctetString1->SetMinSize(1024);
        descOctetString1->SetMaxSize(1024);

        Tag* tag1 = new Tag(Tag::CLASS_APPLICATION, Tag::PRIMITIVE, Tag::OCTET_STRING);

        descOctetString1->TagAddLevel(tag1);

        AsnOctetString* octetString1 = new AsnOctetString(descOctetString1, vector1);

        Octets* octets = octetString1->Encode();

        AsnDescOctetString* descOctetString1After = new AsnDescOctetString();

        descOctetString1After->SetClauseSize();
        descOctetString1After->SetMinSize(999);
        descOctetString1After->SetMaxSize(999);

        AsnOctetString* octetString1After = new AsnOctetString(descOctetString1After);

        // Next should throw ASN.1 decode exception.

        octetString1After->Decode(*octets);
    }
    catch (ITS_GenericException& exp)
    {
        cout << exp.GetDescription() << endl;

        exp.Log();
    }
    catch (exception& exp)
    {
        cout << exp.what() << endl;  
    }

    if (octets != NULL)
    {
        delete octets;

        octets = NULL;
    }

    cout << endl;

    cout << "End test with exceptions..." << endl;
}


void Test1()
{
    Length* length1 = new Length(12345);

    Octets* octets = length1->Encode();

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of Octets...";
        cout <<endl;
        cout << *octets;
        cout << endl;
    }

    Length* length2 = new Length(*octets);

    long l = length2->GetLength();

    delete length1;
    delete length2;

    delete octets;

    length1 = new Length(12);

    octets = length1->Encode();

    length2 = new Length(*octets);

    l = length2->GetLength();

    delete length1;
    delete length2;

    delete octets;

    length1 = new Length(0);

    octets = length1->Encode();

    length2 = new Length(*octets);

    l = length2->GetLength();

    delete length1;
    delete length2;

    delete octets;

    length1 = new Length(1234567890);

    octets = length1->Encode();

    length2 = new Length(*octets);

    l = length2->GetLength();

    delete length1;
    delete length2;

    delete octets;
}

void Test2()
{
    long array[] = {12345, -12345, -1, 0, -10, 10, 987654321, -987654321};

    AsnInteger* integer1 = NULL;
    AsnInteger* integer2 = NULL;
    Octets* octets = NULL;

    long valueBefore = 0;
    long valueAfter = 0;

    for (int i = 0; i < 8; i++)
    {
        valueBefore = array[i];

        integer1 = new AsnInteger(valueBefore);

        octets = integer1->Encode();

        integer2 = new AsnInteger(*octets);

        valueAfter = integer2->GetValue();

        delete integer1;
        delete integer2;
        delete octets;
    }

    integer1 = new AsnInteger(1999l);
    integer2 = new AsnInteger(*integer1);

    AsnInteger* integer3 = new AsnInteger(2001l);

    *integer3 = *integer1;

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of AsnInteger...";
        cout << endl;
        cout << *integer1;
        cout << *integer2;
        cout << *integer3;
        cout << endl;
    }

    delete integer1;
    delete integer2;
    delete integer3;

}

void Test3()
{
    long array[] = {2, 4, 10, 2333, 334567, 4567897};

    Tag* tag1 = NULL;
    Tag* tag2 = NULL;
    Octets* octets = NULL;
    long numberBefore = 0;
    long numberAfter = 0;

    for (int i = 0; i < 6; i++)
    {
        numberBefore = array[i];
        
        tag1 = new Tag(Tag::CLASS_APPLICATION, Tag::PRIMITIVE, numberBefore);

        octets = tag1->Encode();

        tag2 = new Tag(*octets);

        numberAfter = tag2->GetNumber();

        delete tag1;
        delete tag2;
        delete octets;

     }
}


void Test4()
{
    bool array[] = {false, true};

    AsnBoolean* boolean1 = NULL;
    AsnBoolean* boolean2 = NULL;
    Octets* octets = NULL;

    bool valueBefore = false;
    bool valueAfter = false;

    for (int i = 0; i < 2; i++)
    {
        valueBefore = array[i];

        boolean1 = new AsnBoolean(valueBefore);

        octets = boolean1->Encode();

        boolean2 = new AsnBoolean(*octets);

        valueAfter = boolean2->GetValue();

        delete boolean1;
        delete boolean2;
        delete octets;
    }

    boolean1 = new AsnBoolean(true);
    boolean2 = new AsnBoolean(*boolean1);

    AsnBoolean* boolean3 = new AsnBoolean(false);

    *boolean3 = *boolean1;

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of AsnBoolean...";
        cout << endl;
        cout << *boolean1;
        cout << *boolean2;
        cout << *boolean3;
        cout << endl;
    }

    delete boolean1;
    delete boolean2;
    delete boolean3;
}

void Test5()
{
    AsnObject* asnObject1 = NULL;
    AsnObject* asnObject2 = NULL;
    AsnObject* asnObject3 = NULL;

    asnObject1 = new AsnInteger(10l);

    asnObject2 = asnObject1->Clone();

    AsnInteger* asnInteger1 = static_cast<AsnInteger*> (asnObject2);

    asnObject3 = asnObject1->GetPolymorphDescription().Factory();

    AsnInteger* asnInteger2 = static_cast<AsnInteger*> (asnObject3);

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of AsnInteger...";
        cout << endl;
        cout << *asnInteger1;
        cout << *asnInteger2;
        cout << endl;
    }

    delete asnObject1;
    delete asnObject2;
    delete asnObject3;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//
//  Useful types to test SET and SEQUENCE.
//

////////////////////////////////////////
//
//  Integer1.
//

class Integer1 : public AsnInteger
{
public:

    Integer1(bool initialize = true);

    Integer1(long valueParam, bool initialize = true);

    Integer1(Octets& octets, bool initialize = true);

    Integer1(const Integer1& rhs);

    Integer1(AsnDescObject* descriptionParam);

    Integer1(AsnDescObject* descriptionParam, long valueParam);

protected:

    void Initialize();

public:

    static AsnDescObject* GetStaticDescription();

public:

    virtual ~Integer1();

    virtual AsnObject* Clone() const;

    virtual std::string GetName() const
    { return "Integer1"; }

};

Integer1::Integer1(bool initialize) : AsnInteger(false)
{
    if (initialize)
    {
        Initialize();
    }
}

Integer1::Integer1(long valueParam, bool initialize) : AsnInteger(valueParam, false)
{
    if (initialize)
    {
        Initialize();
    }
}

Integer1::Integer1(Octets& octets, bool initialize) : AsnInteger(false)
{
    if (initialize)
    {
        Initialize();
    }

    Decode(octets);
}

Integer1::Integer1(const Integer1& rhs) : AsnInteger(rhs)
{
    // Nothing to do.
}

Integer1::Integer1(AsnDescObject* descriptionParam) : AsnInteger(descriptionParam)
{
    // Nothing to do.
}

Integer1::Integer1(AsnDescObject* descriptionParam, long valueParam) : AsnInteger(descriptionParam, valueParam)
{
    // Nothing to do.
}

void Integer1::Initialize()
{
    ITS_ASSERT(description == NULL);

    description = GetStaticDescription();
    description->IncRef();
}

AsnDescObject* Integer1::GetStaticDescription()
{
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

    if (result == NULL)
    {
        // To deny the reference counting mechanism.
        // (staticDesc is static.)
        staticDesc.IncRef();

        staticDesc.SetCloneForFactory(new Integer1(&staticDesc));

        // One circular reference to remove.
        // (cloneForFactory is an attribute of staticDesc.)
        staticDesc.DecRef();

        staticDesc.TagAddLevel(new Tag(Tag::CLASS_CONTEXT_SPECIFIC, Tag::PRIMITIVE, 1));

        result = &staticDesc;
    }

    return result;
}

Integer1::~Integer1()
{
    // Nothing to do.
}

AsnObject* Integer1::Clone() const
{
    return new Integer1(*this);
}


////////////////////////////////////////
//
//  Integer2.
//

class Integer2 : public AsnInteger
{
public:

    Integer2(bool initialize = true);

    Integer2(long valueParam, bool initialize = true);

    Integer2(Octets& octets, bool initialize = true);

    Integer2(const Integer2& rhs);

    Integer2(AsnDescObject* descriptionParam);

    Integer2(AsnDescObject* descriptionParam, long valueParam);

protected:

    void Initialize();

public:

    static AsnDescObject* GetStaticDescription();

public:

    virtual ~Integer2();

    virtual AsnObject* Clone() const;

    virtual std::string GetName() const
    { return "Integer2"; }

};

Integer2::Integer2(bool initialize) : AsnInteger(false)
{
    if (initialize)
    {
        Initialize();
    }
}

Integer2::Integer2(long valueParam, bool initialize) : AsnInteger(valueParam, false)
{
    if (initialize)
    {
        Initialize();
    }
}

Integer2::Integer2(Octets& octets, bool initialize) : AsnInteger(false)
{
    if (initialize)
    {
        Initialize();
    }

    Decode(octets);
}

Integer2::Integer2(const Integer2& rhs) : AsnInteger(rhs)
{
    // Nothing to do.
}

Integer2::Integer2(AsnDescObject* descriptionParam) : AsnInteger(descriptionParam)
{
    // Nothing to do.
}

Integer2::Integer2(AsnDescObject* descriptionParam, long valueParam) : AsnInteger(descriptionParam, valueParam)
{
    // Nothing to do.
}

void Integer2::Initialize()
{
    ITS_ASSERT(description == NULL);

    description = GetStaticDescription();
    description->IncRef();
}

AsnDescObject* Integer2::GetStaticDescription()
{
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

    if (result == NULL)
    {
        // To deny the reference counting mechanism.
        // (staticDesc is static.)
        staticDesc.IncRef();

        staticDesc.SetCloneForFactory(new Integer2(&staticDesc));

        // One circular reference to remove.
        // (cloneForFactory is an attribute of staticDesc.)
        staticDesc.DecRef();

        staticDesc.TagAddLevel(new Tag(Tag::CLASS_CONTEXT_SPECIFIC, Tag::PRIMITIVE, 2));

        result = &staticDesc;
    }

    return result;
}

Integer2::~Integer2()
{
    // Nothing to do.
}

AsnObject* Integer2::Clone() const
{
    return new Integer2(*this);
}


////////////////////////////////////////
//
//  Boolean1.
//

class Boolean1 : public AsnBoolean
{
public:

    Boolean1(bool valueParam = false, bool initialize = true);

    Boolean1(Octets& octets, bool initialize = true);

    Boolean1(const Boolean1& rhs);

    Boolean1(AsnDescObject* descriptionParam);

    Boolean1(AsnDescObject* descriptionParam, bool valueParam);

protected:

    void Initialize();

public:

    static AsnDescObject* GetStaticDescription();

public:

    virtual ~Boolean1();

    virtual AsnObject* Clone() const;

    virtual std::string GetName() const
    { return "Boolean1"; }

};


Boolean1::Boolean1(bool valueParam, bool initialize) : AsnBoolean(valueParam, false)
{
    if (initialize)
    {
        Initialize();
    }
}

Boolean1::Boolean1(Octets& octets, bool initialize) : AsnBoolean(false, false)
{
    if (initialize)
    {
        Initialize();
    }

    Decode(octets);
}

Boolean1::Boolean1(const Boolean1& rhs) : AsnBoolean(rhs)
{
    // Nothing to do.
}

Boolean1::Boolean1(AsnDescObject* descriptionParam) : AsnBoolean(descriptionParam)
{
    // Nothing to do.
}

Boolean1::Boolean1(AsnDescObject* descriptionParam, bool valueParam) : AsnBoolean(descriptionParam, valueParam)
{
    // Nothing to do.
}

void Boolean1::Initialize()
{
    ITS_ASSERT(description == NULL);

    description = GetStaticDescription();
    description->IncRef();
}

AsnDescObject* Boolean1::GetStaticDescription()
{
    static AsnDescObject* result = NULL;
    static AsnDescBoolean staticDesc;

    if (result == NULL)
    {
        // To deny the reference counting mechanism.
        // (staticDesc is static.)
        staticDesc.IncRef();

        staticDesc.SetCloneForFactory(new Boolean1(&staticDesc));

        // One circular reference to remove.
        // (cloneForFactory is an attribute of staticDesc.)
        staticDesc.DecRef();

        staticDesc.TagAddLevel(new Tag(Tag::CLASS_CONTEXT_SPECIFIC, Tag::PRIMITIVE, 3));

        result = &staticDesc;
    }

    return result;
}

Boolean1::~Boolean1()
{
    // Nothing to do.
}

AsnObject* Boolean1::Clone() const
{
    return new Boolean1(*this);
}



////////////////////////////////////////
//
//  Boolean2.
//

class Boolean2 : public AsnBoolean
{
public:

    Boolean2(bool valueParam = false, bool initialize = true);

    Boolean2(Octets& octets, bool initialize = true);

    Boolean2(const Boolean2& rhs);

    Boolean2(AsnDescObject* descriptionParam);

    Boolean2(AsnDescObject* descriptionParam, bool valueParam);

protected:

    void Initialize();

public:

    static AsnDescObject* GetStaticDescription();

public:

    virtual ~Boolean2();

    virtual AsnObject* Clone() const;

    virtual std::string GetName() const
    { return "Boolean2"; }

};


Boolean2::Boolean2(bool valueParam, bool initialize) : AsnBoolean(valueParam, false)
{
    if (initialize)
    {
        Initialize();
    }
}

Boolean2::Boolean2(Octets& octets, bool initialize) : AsnBoolean(false, false)
{
    if (initialize)
    {
        Initialize();
    }

    Decode(octets);
}

Boolean2::Boolean2(const Boolean2& rhs) : AsnBoolean(rhs)
{
    // Nothing to do.
}

Boolean2::Boolean2(AsnDescObject* descriptionParam) : AsnBoolean(descriptionParam)
{
    // Nothing to do.
}

Boolean2::Boolean2(AsnDescObject* descriptionParam, bool valueParam) : AsnBoolean(descriptionParam, valueParam)
{
    // Nothing to do.
}

void Boolean2::Initialize()
{
    ITS_ASSERT(description == NULL);

    description = GetStaticDescription();
    description->IncRef();
}

AsnDescObject* Boolean2::GetStaticDescription()
{
    static AsnDescObject* result = NULL;
    static AsnDescBoolean staticDesc;

    if (result == NULL)
    {
        // To deny the reference counting mechanism.
        // (staticDesc is static.)
        staticDesc.IncRef();

        staticDesc.SetCloneForFactory(new Boolean2(&staticDesc));

        // One circular reference to remove.
        // (cloneForFactory is an attribute of staticDesc.)
        staticDesc.DecRef();

        staticDesc.TagAddLevel(new Tag(Tag::CLASS_CONTEXT_SPECIFIC, Tag::PRIMITIVE, 4));

        result = &staticDesc;
    }

    return result;
}

Boolean2::~Boolean2()
{
    // Nothing to do.
}

AsnObject* Boolean2::Clone() const
{
    return new Boolean2(*this);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Test6()
{
    Integer1* integer1 = new Integer1(1999l);
    Integer2* integer2 = new Integer2(2010l);
    Boolean1* boolean1 = new Boolean1(false);
    Boolean2* boolean2 = new Boolean2(true);

    AsnSet* set1 = new AsnSet(4);

    static AsnDescSet* staticDescPtr1 = NULL;

    if (staticDescPtr1 == NULL)
    {
        static AsnDescSet staticDesc1(4);

        staticDesc1.IncRef();
        staticDesc1.SetCloneForFactory(new AsnSet(4, &staticDesc1));
        staticDesc1.DecRef();
        staticDesc1.TagAddLevel(AsnSet::GetUniversalTag());

        staticDescPtr1 = &staticDesc1;
    }

    set1->SetDescription(staticDescPtr1);

    ((AsnDescSet&)set1->GetDescription()).AddElement(0, (AsnDescObject*)&integer1->GetDescription());
    ((AsnDescSet&)set1->GetDescription()).AddElement(1, (AsnDescObject*)&integer2->GetDescription());
    ((AsnDescSet&)set1->GetDescription()).AddElement(2, (AsnDescObject*)&boolean1->GetDescription());
    ((AsnDescSet&)set1->GetDescription()).AddElement(3, (AsnDescObject*)&boolean2->GetDescription());

    set1->AddElement(0, integer1);
    set1->AddElement(1, integer2);
    set1->AddElement(2, boolean1);
    set1->AddElement(3, boolean2);

    Octets* octets = set1->Encode();

    AsnSet* set2 = new AsnSet(4);

    static AsnDescSet* staticDescPtr2 = NULL;

    if (staticDescPtr2 == NULL)
    {
        static AsnDescSet staticDesc2(4);

        staticDesc2.IncRef();
        staticDesc2.SetCloneForFactory(new AsnSet(4, &staticDesc2));
        staticDesc2.DecRef();
        staticDesc2.TagAddLevel(AsnSet::GetUniversalTag());

        staticDescPtr2 = &staticDesc2;
    }

    set2->SetDescription(staticDescPtr2);

    ((AsnDescSet&)set2->GetDescription()).AddElement(0, (AsnDescObject*)&integer1->GetDescription());
    ((AsnDescSet&)set2->GetDescription()).AddElement(1, (AsnDescObject*)&integer2->GetDescription());
    ((AsnDescSet&)set2->GetDescription()).AddElement(2, (AsnDescObject*)&boolean1->GetDescription());
    ((AsnDescSet&)set2->GetDescription()).AddElement(3, (AsnDescObject*)&boolean2->GetDescription());

    set2->Decode(*octets);

    const AsnInteger& integer1After = (const AsnInteger&)set2->ElementAt(0);
    const AsnInteger& integer2After = (const AsnInteger&)set2->ElementAt(1);
    const AsnBoolean& boolean1After = (const AsnBoolean&)set2->ElementAt(2);
    const AsnBoolean& boolean2After = (const AsnBoolean&)set2->ElementAt(3);

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of AsnSet...";
        cout << endl;
        cout << *set2;
        cout << endl;
    }

    delete set2;
    delete set1;
    delete octets;
}

void Test7()
{
    Integer1* integer1 = new Integer1(1999l);
    Integer2* integer2 = new Integer2(2010l);
    Boolean1* boolean1 = new Boolean1(false);
    Boolean2* boolean2 = new Boolean2(true);

    AsnSet* set1 = new AsnSet(4);

    static AsnDescSet* staticDescPtr1 = NULL;

    if (staticDescPtr1 == NULL)
    {
        static AsnDescSet staticDesc1(4);

        staticDesc1.IncRef();
        staticDesc1.SetCloneForFactory(new AsnSet(4, &staticDesc1));
        staticDesc1.DecRef();
        staticDesc1.TagAddLevel(AsnSet::GetUniversalTag());

        staticDescPtr1 = &staticDesc1;
    }

    set1->SetDescription(staticDescPtr1);

    ((AsnDescSet&)set1->GetDescription()).AddElement(0, (AsnDescObject*)&integer1->GetDescription());
    ((AsnDescSet&)set1->GetDescription()).AddElement(1, (AsnDescObject*)&integer2->GetDescription());
    ((AsnDescSet&)set1->GetDescription()).AddElement(2, (AsnDescObject*)&boolean1->GetDescription());
    ((AsnDescSet&)set1->GetDescription()).AddElement(3, (AsnDescObject*)&boolean2->GetDescription());

    set1->AddElement(0, integer1);
    set1->AddElement(1, integer2);
    set1->AddElement(2, boolean1);
    set1->AddElement(3, boolean2);

    Octets* octets = set1->Encode();

    AsnSet* set2 = new AsnSet(4);

    static AsnDescSet* staticDescPtr2 = NULL;

    if (staticDescPtr2 == NULL)
    {
        static AsnDescSet staticDesc2(4);

        staticDesc2.IncRef();
        staticDesc2.SetCloneForFactory(new AsnSet(4, &staticDesc2));
        staticDesc2.DecRef();
        staticDesc2.TagAddLevel(AsnSet::GetUniversalTag());

        staticDescPtr2 = &staticDesc2;
    }

    set2->SetDescription(staticDescPtr2);

    ((AsnDescSet&)set2->GetDescription()).AddElement(0, (AsnDescObject*)&integer1->GetDescription());
    ((AsnDescSet&)set2->GetDescription()).AddElement(1, (AsnDescObject*)&integer2->GetDescription());
    ((AsnDescSet&)set2->GetDescription()).AddElement(2, (AsnDescObject*)&boolean1->GetDescription());
    ((AsnDescSet&)set2->GetDescription()).AddElement(3, (AsnDescObject*)&boolean2->GetDescription());

    set2->Decode(*octets);

    const AsnInteger& integer1After = (const AsnInteger&)set2->ElementAt(0);
    const AsnInteger& integer2After = (const AsnInteger&)set2->ElementAt(1);
    const AsnBoolean& boolean1After = (const AsnBoolean&)set2->ElementAt(2);
    const AsnBoolean& boolean2After = (const AsnBoolean&)set2->ElementAt(3);

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of AsnSet...";
        cout << endl;
        cout << *set2;
        cout << endl;
    }

    delete set2;
    delete set1;
    delete octets;
}

void Test8()
{
    AsnInteger* integer1 = new AsnInteger(1999l);
    AsnInteger* integer2 = new AsnInteger(2001l);
    AsnInteger* integer3 = new AsnInteger(2010l);
    AsnInteger* integer4 = new AsnInteger(2064l);

    AsnBoolean* boolean1 = new AsnBoolean(true);

    AsnSequenceOf* sequenceOf1 = new AsnSequenceOf();

    static bool sequenceOf1DescToBeSet = true;

    if (sequenceOf1DescToBeSet) // If not done -> memory leak (everything must use once design pattern).
    {
        sequenceOf1DescToBeSet = false;

        ((AsnDescSequenceOf&)sequenceOf1->GetDescription()).SetElement((AsnDescObject*)&integer1->GetDescription());
    }

    AsnChoice* choice1 = new AsnChoice();

    static bool choice1DescToBeSet = true;

    if (choice1DescToBeSet) // If not done -> memory leak (everything must use once design pattern).
    {
        choice1DescToBeSet = false;

        ((AsnDescChoice&)choice1->GetDescription()).AddChoice((AsnDescObject*)&sequenceOf1->GetDescription());
        ((AsnDescChoice&)choice1->GetDescription()).AddChoice((AsnDescObject*)&boolean1->GetDescription());
    }

    sequenceOf1->AddElement(integer1);
    sequenceOf1->AddElement(integer2);
    sequenceOf1->AddElement(integer3);
    sequenceOf1->AddElement(integer4);

    choice1->SetChoice(sequenceOf1);

    AsnChoice* choice2 = new AsnChoice();

    static bool choice2DescToBeSet = true;

    if (choice2DescToBeSet) // If not done -> memory leak (everything must use once design pattern).
    {
        choice2DescToBeSet = false;

        ((AsnDescChoice&)choice2->GetDescription()).AddChoice((AsnDescObject*)&sequenceOf1->GetDescription());
        ((AsnDescChoice&)choice2->GetDescription()).AddChoice((AsnDescObject*)&boolean1->GetDescription());
    }

    choice2->SetChoice(boolean1);

    Octets* octets = choice1->Encode();

    AsnChoice* choice1After = new AsnChoice();

    static bool choice1AfterDescToBeSet = true;

    if (choice1AfterDescToBeSet) // If not done -> memory leak (everything must use once design pattern).
    {
        choice1AfterDescToBeSet = false;

        ((AsnDescChoice&)choice1After->GetDescription()).AddChoice((AsnDescObject*)&sequenceOf1->GetDescription());
        ((AsnDescChoice&)choice1After->GetDescription()).AddChoice((AsnDescObject*)&boolean1->GetDescription());
    }

    choice1After->Decode(*octets);

    const AsnSequenceOf& sequenceOf1After = (const AsnSequenceOf&)choice1After->GetChoice();

    const AsnInteger& integer1After = (const AsnInteger&)sequenceOf1After.ElementAt(0);
    const AsnInteger& integer2After = (const AsnInteger&)sequenceOf1After.ElementAt(1);
    const AsnInteger& integer3After = (const AsnInteger&)sequenceOf1After.ElementAt(2);
    const AsnInteger& integer4After = (const AsnInteger&)sequenceOf1After.ElementAt(3);

    delete octets;

    octets = choice2->Encode();

    AsnChoice* choice2After = new AsnChoice();

    static bool choice2AfterDescToBeSet = true;

    if (choice2AfterDescToBeSet) // If not done -> memory leak (everything must use once design pattern).
    {
        choice2AfterDescToBeSet = false;

        ((AsnDescChoice&)choice2After->GetDescription()).AddChoice((AsnDescObject*)&sequenceOf1->GetDescription());
        ((AsnDescChoice&)choice2After->GetDescription()).AddChoice((AsnDescObject*)&boolean1->GetDescription());
    }

    choice2After->Decode(*octets);

    const AsnBoolean& boolean1After = (const AsnBoolean&)choice2After->GetChoice();

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of AsnChoice...";
        cout << endl;
        cout << *choice1After;
        cout << endl;
        cout << *choice2After;
        cout << endl;
    }

    delete choice1After;
    delete choice2After;
    delete choice1;
    delete choice2;

    delete octets;
}

void Test9()
{
    byte array1[] = {0x01, 0x02, 0x03, 0x04, 0x05 };

    vector<byte> vector1(array1, array1 + 5);


    byte array2[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                     0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                     0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                     0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                     0x01, 0x02, 0x03, 0x04, 0x05,
                     0x06, 0x07, 0x08 };

    vector<byte> vector2(array2, array2 + 28);


    byte array3[] = {0x01, 0x02, 0x03, 0x04, 0x05,
                     0x06, 0x07, 0x08, 0x09, 0x0A };

    vector<byte> vector3(array3, array3 + 10);


    byte array4[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                     0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                     0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                     0xFF, 0xFE, 0xFD, 0xFC, 0xFB,
                     0x01, 0x02, 0x03, 0x04, 0x05,
                     0x06, 0x07, 0x08, 0x09, 0x0A };

    vector<byte> vector4(array4, array4 + 30);


    AsnOctetString* octetString1 = new AsnOctetString(vector1);
    AsnOctetString* octetString2 = new AsnOctetString(vector2);
    AsnOctetString* octetString3 = new AsnOctetString(vector3);
    AsnOctetString* octetString4 = new AsnOctetString(vector4);

    Octets* octets = octetString1->Encode();

    AsnOctetString* octetString1After = new AsnOctetString(*octets);

    delete octets;

    octets = octetString2->Encode();

    AsnOctetString* octetString2After = new AsnOctetString(*octets);

    delete octets;

    octets = octetString3->Encode();

    AsnOctetString* octetString3After = new AsnOctetString(*octets);

    delete octets;

    octets = octetString4->Encode();

    AsnOctetString* octetString4After = new AsnOctetString(*octets);

    delete octets;

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of AsnOctetString...";
        cout << endl;
        cout << *octetString1After;
        cout << endl;
        cout << *octetString2After;
        cout << endl;
        cout << *octetString3After;
        cout << endl;
        cout << *octetString4After;
        cout << endl;
    }

    delete octetString1;
    delete octetString2;
    delete octetString3;
    delete octetString4;
    delete octetString1After;
    delete octetString2After;
    delete octetString3After;
    delete octetString4After;
}


void Test10()
{
    Integer1* integer1 = new Integer1(1999l);
    Integer2* integer2 = new Integer2(2010l);
    Boolean1* boolean1 = new Boolean1(false);
    Boolean2* boolean2 = new Boolean2(true);

    AsnSequence* sequence1 = new AsnSequence(4);

    static AsnDescSequence* staticDescPtr1 = NULL;

    if (staticDescPtr1 == NULL)
    {
        static AsnDescSequence staticDesc1(4);

        staticDesc1.IncRef();
        staticDesc1.SetCloneForFactory(new AsnSequence(4, &staticDesc1));
        staticDesc1.DecRef();
        staticDesc1.TagAddLevel(AsnSequence::GetUniversalTag());

        staticDescPtr1 = &staticDesc1;
    }

    sequence1->SetDescription(staticDescPtr1);

    ((AsnDescSequence&)sequence1->GetDescription()).AddElement(0, (AsnDescObject*)&integer1->GetDescription());
    ((AsnDescSequence&)sequence1->GetDescription()).AddElement(1, (AsnDescObject*)&integer2->GetDescription());
    ((AsnDescSequence&)sequence1->GetDescription()).AddElement(2, (AsnDescObject*)&boolean1->GetDescription());
    ((AsnDescSequence&)sequence1->GetDescription()).AddElement(3, (AsnDescObject*)&boolean2->GetDescription());

    sequence1->AddElement(0, integer1);
    sequence1->AddElement(1, integer2);
    sequence1->AddElement(2, boolean1);
    sequence1->AddElement(3, boolean2);

    Octets* octets = sequence1->Encode();

    AsnSequence* sequence2 = new AsnSequence(4);

    static AsnDescSequence* staticDescPtr2 = NULL;

    if (staticDescPtr2 == NULL)
    {
        static AsnDescSequence staticDesc2(4);

        staticDesc2.IncRef();
        staticDesc2.SetCloneForFactory(new AsnSequence(4, &staticDesc2));
        staticDesc2.DecRef();
        staticDesc2.TagAddLevel(AsnSequence::GetUniversalTag());

        staticDescPtr2 = &staticDesc2;
    }

    sequence2->SetDescription(staticDescPtr2);

    ((AsnDescSequence&)sequence2->GetDescription()).AddElement(0, (AsnDescObject*)&integer1->GetDescription());
    ((AsnDescSequence&)sequence2->GetDescription()).AddElement(1, (AsnDescObject*)&integer2->GetDescription());
    ((AsnDescSequence&)sequence2->GetDescription()).AddElement(2, (AsnDescObject*)&boolean1->GetDescription());
    ((AsnDescSequence&)sequence2->GetDescription()).AddElement(3, (AsnDescObject*)&boolean2->GetDescription());

    sequence2->Decode(*octets);

    const AsnInteger& integer1After = (const AsnInteger&)sequence2->ElementAt(0);
    const AsnInteger& integer2After = (const AsnInteger&)sequence2->ElementAt(1);
    const AsnBoolean& boolean1After = (const AsnBoolean&)sequence2->ElementAt(2);
    const AsnBoolean& boolean2After = (const AsnBoolean&)sequence2->ElementAt(3);

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of AsnSequence...";
        cout << endl;
        cout << *sequence2;
        cout << endl;
    }

    delete sequence2;
    delete sequence1;

    delete octets;
}

void Test11()
{
    Integer1* integer1 = new Integer1(1999l);
    Integer2* integer2 = new Integer2(2010l);
    Boolean1* boolean1 = new Boolean1(false);
    Boolean2* boolean2 = new Boolean2(true);

    AsnSet* set1 = new AsnSet(4);

    static AsnDescSet* staticDescPtr1 = NULL;

    if (staticDescPtr1 == NULL)
    {
        static AsnDescSet staticDesc1(4);

        staticDesc1.IncRef();
        staticDesc1.SetCloneForFactory(new AsnSet(4, &staticDesc1));
        staticDesc1.DecRef();
        staticDesc1.TagAddLevel(AsnSet::GetUniversalTag());

        staticDescPtr1 = &staticDesc1;
    }

    set1->SetDescription(staticDescPtr1);

    ((AsnDescSet&)set1->GetDescription()).AddElement(0, (AsnDescObject*)&integer1->GetDescription());
    ((AsnDescSet&)set1->GetDescription()).AddElement(1, (AsnDescObject*)&integer2->GetDescription());
    ((AsnDescSet&)set1->GetDescription()).AddElement(2, (AsnDescObject*)&boolean1->GetDescription());
    ((AsnDescSet&)set1->GetDescription()).AddElement(3, (AsnDescObject*)&boolean2->GetDescription());

    set1->AddElement(0, integer1);
    set1->AddElement(1, integer2);
    set1->AddElement(2, boolean1);
    set1->AddElement(3, boolean2);

    Octets* octets = set1->Encode();

    vector<byte> vectorSet1 = octets->GetArray();

    // Modification of octets to add an AsnOctetString (Unknown Element In Set Test).

    byte array[] = {0x01, 0x02, 0x03, 0x04, 0x05 };

    vector<byte> vectorOctetString(array, array + 5);

    AsnOctetString* octetString = new AsnOctetString(vectorOctetString);

    Octets* octetsToInsert = octetString->Encode();

    vector<byte> vectorToInsert = octetsToInsert->GetArray();

    delete octetString;
    delete octetsToInsert;

    // Insert the octet string two times:
    // - Between integer2 and boolean1.
    // - After boolean2.

    vectorSet1.insert(vectorSet1.begin() + 10, vectorToInsert.begin(), vectorToInsert.end());
    vectorSet1.insert(vectorSet1.end(), vectorToInsert.begin(), vectorToInsert.end());

    vectorSet1[1] = 0x1CU;  // Update the total length.

    AsnSet* set2 = new AsnSet(4);

    static AsnDescSet* staticDescPtr2 = NULL;

    if (staticDescPtr2 == NULL)
    {
        static AsnDescSet staticDesc2(4);

        staticDesc2.IncRef();
        staticDesc2.SetCloneForFactory(new AsnSet(4, &staticDesc2));
        staticDesc2.DecRef();
        staticDesc2.TagAddLevel(AsnSet::GetUniversalTag());

        staticDescPtr2 = &staticDesc2;
    }

    set2->SetDescription(staticDescPtr2);

    ((AsnDescSet&)set2->GetDescription()).AddElement(0, (AsnDescObject*)&integer1->GetDescription());
    ((AsnDescSet&)set2->GetDescription()).AddElement(1, (AsnDescObject*)&integer2->GetDescription());
    ((AsnDescSet&)set2->GetDescription()).AddElement(2, (AsnDescObject*)&boolean1->GetDescription());
    ((AsnDescSet&)set2->GetDescription()).AddElement(3, (AsnDescObject*)&boolean2->GetDescription());

    // Decode will fail with Unknown Element In Set.

    Octets octetsToDecode1(vectorSet1);

    AsnOptions::GlobalUnsetDecodeSkipUnknownElementInSet();

    try
    {
        set2->Decode(octetsToDecode1);
    }
    catch (AsnDecodeError& asnDecodeError)
    {
        if (testPrint)
        {
            cout << "The following exception is normal..." << endl;
            cout << asnDecodeError.GetDescription();
            cout << endl;
        }
    }

    // Decode will not fail with Unknown Element In Set.

    Octets octetsToDecode2(vectorSet1);

    AsnOptions::GlobalSetDecodeSkipUnknownElementInSet();

    set2->Decode(octetsToDecode2);

    // Set back the option.

    AsnOptions::GlobalUnsetDecodeSkipUnknownElementInSet();

    const AsnInteger& integer1After = (const AsnInteger&)set2->ElementAt(0);
    const AsnInteger& integer2After = (const AsnInteger&)set2->ElementAt(1);
    const AsnBoolean& boolean1After = (const AsnBoolean&)set2->ElementAt(2);
    const AsnBoolean& boolean2After = (const AsnBoolean&)set2->ElementAt(3);

    if (testPrint)
    {
        cout << endl;
        cout << "Test printing of AsnSet...";
        cout << endl;
        cout << *set2;
        cout << endl;
    }

    delete set2;
    delete set1;
    delete octets;
}
