#include "GenericIStreamBuf.h"
#include "stdafx.h"

// Public construction/destruction
GenericIOStreamTest::GenericIStreamBuf::GenericIStreamBuf(const size_t BufferSize) :
    GenericStreamBuf(BufferSize),
    DataRetrieveCB(nullptr)
{
    
}

// Public member functions
void GenericIOStreamTest::GenericIStreamBuf::RegisterOnDataRetrieveCallback(DataRetrieveCallback_base* const DataRetCB)
{
    DataRetrieveCB = DataRetCB;
}

// Protected member functions
std::basic_streambuf<char>::int_type GenericIOStreamTest::GenericIStreamBuf::underflow()
{
    std::basic_streambuf<char>::int_type Result;
    Result = GenericStreamBuf::underflow();
    
    //if(!Result)
    if(std::char_traits<char>::eq_int_type(Result, std::char_traits<char>::eof()))
    {
        RetrieveData();
        Result = GenericStreamBuf::underflow();
    }
    return Result;
}

// Private member functions
void GenericIOStreamTest::GenericIStreamBuf::RetrieveData()
{
    size_t NumBytes = 0;
    //std::basic_streambuf<char>::char_type* PutBegin = pbase();
    std::basic_streambuf<char>::char_type* PutEnd = epptr();
    std::basic_streambuf<char>::char_type* PutCurrent = pptr();
    
    if(PutCurrent == PutEnd)
    {
        overflow('\0');
        seekoff(-1, std::ios_base::cur, std::ios_base::out);
        
        PutEnd = epptr();
        PutCurrent = pptr();
    }
    if(PutCurrent < PutEnd && DataRetrieveCB)
    {
        NumBytes = DataRetrieveCB->Invoke(PutCurrent, PutEnd - PutCurrent);
        seekoff((long)NumBytes, std::ios_base::cur, std::ios_base::out);
    }
    
    if(NumBytes)
    {
        RetrieveData();
    }
}
