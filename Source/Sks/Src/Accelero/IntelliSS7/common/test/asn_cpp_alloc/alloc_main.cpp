////////////////////////////////////////////////////////////////////////////////
//
//  Quick test for memory allocation improvements for ASN.1.
//


#if defined(WIN32)
#pragma warning(disable:4786) 
#endif // defined(WIN32)


#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <new>

#if defined(WIN32)
#include <crtdbg.h>
#else // !defined(WIN32)

#define _ASSERTE(expression)

#endif // defined(WIN32)

typedef unsigned char byte;

using namespace std;



////////////////////////////////////////////////////////////////////////////////
//
//  AsnInnerAbstractAllocator.
//

class AsnInnerAbstractAllocator
{
public:
 
    virtual void* allocate(size_t size, const void* hintPtr = NULL) = 0;

    virtual void deallocate(void* ptr, size_t size) = 0;
};



////////////////////////////////////////////////////////////////////////////////
//
//  AsnInnerDefaultAllocator.
//

class AsnInnerDefaultAllocator : public AsnInnerAbstractAllocator
{
public:

    AsnInnerDefaultAllocator()
    {
        // Nothing to do.
    }

    // Default copy constructor not ok.

    // Default assignment operator not ok.

    virtual ~AsnInnerDefaultAllocator()
    {
        // Nothing to do.
    }

    virtual void* 
    allocate(size_t size, const void* hintPtr = NULL)
    { return ::operator new(size); }

    virtual void 
    deallocate(void* ptr, size_t size)
    { ::operator delete(ptr); }

private:

    AsnInnerDefaultAllocator(const AsnInnerDefaultAllocator&) {}

    AsnInnerDefaultAllocator& 
    operator=(const AsnInnerDefaultAllocator&) { return *this; }
};



////////////////////////////////////////////////////////////////////////////////
//
//  AsnInnerBufferAllocator.
//

class AsnInnerBufferAllocator : public AsnInnerAbstractAllocator
{
public:

    AsnInnerBufferAllocator(byte* bufferPtrParam, size_t bufferSizeParam)
    :   bufferPtr(bufferPtrParam),
        bufferVarPtr(bufferPtrParam),
        bufferSize(bufferSizeParam)
    {
        // Nothing to do.
    }

    // Default copy constructor not ok.

    // Default assignment operator not ok.

    virtual ~AsnInnerBufferAllocator()
    {
        // Nothing to do.
    }

    virtual void* 
    allocate(size_t size, const void* hintPtr = 0)
    {
        void* result = (void*)bufferVarPtr;

        bufferVarPtr += size;

        // Detect out of buffer memory condition. Should throw an AsnBadAlloc
        // exception.

        _ASSERTE((size_t)(bufferVarPtr - bufferPtr) <= bufferSize);

        return result;
    }

    virtual void 
    deallocate(void* ptr, size_t size)
    { 
        // Nothing to do.
    }

protected:

    byte* bufferPtr;

    byte* bufferVarPtr;

    size_t bufferSize;

private:

    AsnInnerBufferAllocator(const AsnInnerBufferAllocator&) {}

    AsnInnerBufferAllocator& 
    operator=(const AsnInnerBufferAllocator&) { return *this; }
};




////////////////////////////////////////////////////////////////////////////////
//
// AsnAllocatorTp (Tp for Template).
//

template<class _T_>
class AsnAllocatorTp 
{
public:

    //
    // Type definitions.
    //

    typedef size_t      size_type; 
    typedef ptrdiff_t   difference_type;
    typedef _T_*        pointer;
    typedef const _T_*  const_pointer;
    typedef _T_&        reference;
    typedef const _T_&  const_reference;
    typedef _T_         value_type;


    //
    // Rebind allocator to type U.
    //
    
#if defined(__GNUC__)

    template <class U>

        struct rebind {
            typedef AsnAllocatorTp<U> other;
    };
    
#endif // defined(__GNUC__)


    //
    //  Return address of values.
    //

    pointer 
    address(reference value) const
    {return &value; }

    const_pointer 
    address(const_reference value) const
    {return &value; }


    //
    //  Constructors.
    //

    AsnAllocatorTp()
    :   innerAllocator(NULL)
    {
        // Nothing else to do.
    }

    AsnAllocatorTp(AsnInnerAbstractAllocator& innerAllocatorParam)
    :   innerAllocator(&innerAllocatorParam)
    {
        // Nothing else to do.
    }

    AsnAllocatorTp(const AsnAllocatorTp& rhs)
    :   innerAllocator(rhs.innerAllocator)
    {
        // Nothing else to do.
    }


    //
    //  Assignment operator.
    //

    AsnAllocatorTp& 
    operator=(const AsnAllocatorTp& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            innerAllocator = rhs.innerAllocator;
        }
    }


    //
    //  Destructor.
    //

    virtual ~AsnAllocatorTp()
    { 
        // Nothing to do.
    }


    //
    //  Return maximum number of elements that can be allocated.
    //

    size_t 
    max_size(size_t dummy = 0) const 
    {
        size_t size = (size_t)(-1) / sizeof(_T_);
        return (0 < size ? size : 1); 
    }


    //
    //  Allocate (but do not initialize) size elements of type _T_.
    //

    pointer 
    allocate(size_type size, const void* ptr = NULL)
    { 
        if (innerAllocator == NULL)
        {
            return (pointer)::operator new (size * sizeof(_T_));
        }
        else
        {        
            return (pointer)innerAllocator->allocate(size * sizeof(_T_), ptr); 
        }
    }


    //
    //  Deallocate storage ptr of deleted elements.
    //

    void 
    deallocate(void* ptr, size_type size)
    { 
        if (innerAllocator == NULL)
        {
            ::operator delete(ptr);
        }
        else
        {
            innerAllocator->deallocate(ptr, size); 
        }
    }


    //
    //  Initialize elements of allocated storage ptr with value (call copy 
    //  constructor to a specific location using placement new operator).
    //

    void 
    construct(pointer ptr, const_reference value)
    { new((void*)ptr)_T_(value); }


    //
    //  Destroy elemetns of initialized storage ptr.
    //

    void 
    destroy(pointer ptr)
    { ptr->~_T_(); }


    //
    //  Allocate storage for size characters (specific to Visual C++ 6.0 only).
    //

    char* 
    _Charalloc(size_type size)
    { return innerAllocator->allocate(size); }



    //
    //  Todo: add the required member functions for ASN.1 runtime:
    //
    //  - AsnAllocatorTp<bool> GetBoolAllocator().
    //  - AsnAllocatorTp<long> GetLongAllocator().
    //  - AsnAllocatorTp<AsnObject*> GetAsnObjectPtrAllocator().
    //  - ...
    //

    AsnAllocatorTp<byte>
    GetByteAllocator() const
    { 
        if (innerAllocator == NULL)
        {
            AsnAllocatorTp<byte> result;

            return result;
        }
        else
        {
            AsnAllocatorTp<byte> result(*innerAllocator);

            return result;
        }
    }


protected:

    //
    //  Inner abstract allocator.
    //

    AsnInnerAbstractAllocator* innerAllocator;

};


////////////////////////////////////////////////////////////////////////////////
//
//  AsnAllocator. AsnAllocatorTp specialized for byte (sizeof is one).
//

typedef AsnAllocatorTp<byte> AsnAllocator; 



////////////////////////////////////////////////////////////////////////////////
//
//  AsnVectorToStdVector.
//
//  Convert a type [const vector<byte, AsnAllocatorTp<byte> >&] to a type 
//  [const vector<byte>&].
//
//  Not portable because of dependency on std::vector memory layout therefore
//  dependency on platform, C++ compiler and STL variant used.
//  
//  Following version is for:
//
//  [1] Windows NT/2000 - VC++ 6.0 - P.J. Plauger STL.
//
//  [2] Sun Solaris - SUN Pro CC 5.0 - Rogue Wave STL.
//
//  [3] Sun Solaris - g++ 2.95.2 - SGI STL.
//  
//  [4] Linux - g++ 2.95.2 - SGI STL.
//
//

const vector<byte>&
AsnVectorToStdVector(const vector<byte, AsnAllocatorTp<byte> >& asnVector)
{ 
   
#if (defined(WIN32) && (_MSC_VER >= 1200))

    // Windows NT/2000 - VC++ 6.0 - P.J. Plauger STL (assumed for VC++).
   
    return *((const vector<byte>*)((char*)(&asnVector) + sizeof(void*))); 

#elif (defined(solaris) && defined(__GNUC__))

    // Sun Solaris - g++ - SGI STL (assumed for g++).

    return *((const vector<byte>*)((char*)(&asnVector) + 2 * sizeof(void*)));

#elif (defined(solaris) && defined(__SUNPRO_CC))

    // Sun solaris - SUN Pro CC 5.0 - Rogue Wave STL (assumed for CC).

    return *((const vector<byte>*)((char*)(&asnVector)));

#elif (defined(linux) && defined(__GNUC__))

    // Linux - g++ - SGI STL (assumed for g++).

    return *((const vector<byte>*)((char*)(&asnVector) + 2 * sizeof(void*)));

#else

#error "(Platform / Compiler / STL variant) not defined."

#endif

}



////////////////////////////////////////////////////////////////////////////////
//
//  Foo (test purpose).
//

class Foo
{
public:

    Foo(const AsnAllocator& asnAllocatorParam = AsnAllocator())
    :   asnAllocator(asnAllocatorParam), 
        data(asnAllocatorParam.GetByteAllocator())   
    {}

    virtual ~Foo() {}

    void 
    SetArray(const std::vector<byte, AsnAllocatorTp<byte> >& array)
    { data = array; }

    void 
    SetArray(const std::vector<byte>& array)
    { data.assign(array.begin(), array.end()); }

    const std::vector<byte>&
    GetArray() const
    { return AsnVectorToStdVector(data); }
    

protected:

    std::vector<byte, AsnAllocatorTp<byte> > data;

    AsnAllocator asnAllocator;

};



////////////////////////////////////////////////////////////////////////////////
//
//  Fn1: everything allocated in stack.
//

void Fn1()
{
    //
    //  Construct buffer asnAllocator (on stack but can also be static).
    //
    
    //
    //  Sun Pro CC 5.0 seems to perform weird optimizations for stack memory
    //  management in release build only.
    //

#if (defined(solaris) && defined(__SUNPRO_CC) && !defined(DEBUG))

    static byte buffer[1024];
    
#else // !(defined(solaris) && defined(__SUNPRO_CC) && !defined(DEBUG))
 
    byte buffer[1024];
    
#endif // defined(solaris) && defined(__SUNPRO_CC) && !defined(DEBUG)

    AsnInnerBufferAllocator innerBufferAllocator(buffer, 1024);

    AsnAllocator asnAllocator(innerBufferAllocator);


    vector<byte, AsnAllocatorTp<byte> > vect1(asnAllocator);

    // Note: we don't do vect1.reserve(5), so a lot of reallocations will occur.

    vect1.push_back(0x01U);
    vect1.push_back(0x02U);
    vect1.push_back(0x03U);
    vect1.push_back(0x04U);
    vect1.push_back(0x05U);
    
    cout << "vect1: ";
    cout << (int)vect1[0] << ", ";
    cout << (int)vect1[1] << ", ";
    cout << (int)vect1[2] << ", ";
    cout << (int)vect1[3] << ", ";
    cout << (int)vect1[4];
    cout << endl;


    Foo foo1(asnAllocator); // Use buffer asnAllocator.   

    foo1.SetArray(vect1); // Copy vect1 inside foo1 object.

    const vector<byte>& vect2 = foo1.GetArray();

    byte b1 = vect2[0];
    byte b2 = vect2[1];
    byte b3 = vect2[2];
    byte b4 = vect2[3];
    byte b5 = vect2[4];

    cout << "vect2: ";
    cout << (int)b1 << ", ";
    cout << (int)b2 << ", ";
    cout << (int)b3 << ", ";
    cout << (int)b4 << ", ";
    cout << (int)b5 << endl;

}



////////////////////////////////////////////////////////////////////////////////
//
//  Fn2: partially allocated in heap (contents of vectors).
//

void Fn2()
{
    vector<byte> vect1;

    // Note: we don't do vect1.reserve(5), so a lot of reallocations will occur.

    vect1.push_back(0x01U);
    vect1.push_back(0x02U);
    vect1.push_back(0x03U);
    vect1.push_back(0x04U);
    vect1.push_back(0x05U);

    Foo foo1;  // Use default asnAllocator.

    foo1.SetArray(vect1); // Copy vect1 inside foo1 object.

    const vector<byte>& vect2 = foo1.GetArray();

    byte b1 = vect2[0];
    byte b2 = vect2[1];
    byte b3 = vect2[2];
    byte b4 = vect2[3];
    byte b5 = vect2[4];

    cout << "vect2: ";
    cout << (int)b1 << ", ";
    cout << (int)b2 << ", ";
    cout << (int)b3 << ", ";
    cout << (int)b4 << ", ";
    cout << (int)b5 << endl;
}


int main()
{
    cout << "Begin asnAllocator test." << endl;

    Fn1();

    Fn2();

    cout << "End asnAllocator test." << endl;

    return EXIT_SUCCESS;
}






