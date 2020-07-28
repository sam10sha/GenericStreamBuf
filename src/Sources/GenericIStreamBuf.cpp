#include "GenericIStreamBuf.h"
#include "stdafx.h"

// Public construction/destruction
GenericIOStreamTest::GenericIStreamBuf::GenericIStreamBuf(const size_t BufferSize) :
    MemLength(BufferSize),
    InternalMem(new char[BufferSize]),
    DataRetrieveCB(nullptr)
{
    std::memset(InternalMem, 0, BufferSize);
    setp(InternalMem, InternalMem, InternalMem + BufferSize);
    setg(InternalMem, InternalMem, InternalMem);
}
GenericIOStreamTest::GenericIStreamBuf::~GenericIStreamBuf()
{
    if(InternalMem)
    {
        delete[] InternalMem;
        InternalMem = nullptr;
    }
}

// Public member functions
void GenericIOStreamTest::GenericIStreamBuf::RegisterOnDataRetrieveCallback(DataRetrieveCallback_base* const DataRetCB)
{
    DataRetrieveCB = DataRetCB;
}

// Protected member functions
std::basic_streambuf<char>::int_type GenericIOStreamTest::GenericIStreamBuf::underflow()
{
    //std::basic_streambuf<char>::char_type* PutBegin = pbase();
    std::basic_streambuf<char>::char_type* PutEnd = epptr();
    std::basic_streambuf<char>::char_type* PutCurrent = pptr();
    if(DataRetrieveCB)
    {
        DataRetrieveCB->Invoke(PutCurrent, PutEnd - PutCurrent);
    }
    return std::basic_streambuf<char>::underflow();
}
