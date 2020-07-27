#include "GenericStreamBuf.h"
#include "stdafx.h"

// Public construction/destruction
GenericIOStreamTest::GenericStreamBuf::GenericStreamBuf(const size_t BufferSize) :
    MemLength(BufferSize),
    InternalMem(new char[BufferSize])
{
    std::memset(InternalMem, 0, BufferSize);
    setp(InternalMem, InternalMem, InternalMem + BufferSize);
    setg(InternalMem, InternalMem, InternalMem);
}

GenericIOStreamTest::GenericStreamBuf::~GenericStreamBuf()
{
    if(InternalMem)
    {
        delete[] InternalMem;
        InternalMem = nullptr;
    }
}
	

// Public member functions
void GenericIOStreamTest::GenericStreamBuf::PrintStreamBuf()
{
    std::cout << "GenericStreamBuf[PrintStreamBuf]: " << InternalMem << std::endl;
}


// Protected member functions
std::basic_streambuf<char>::int_type GenericIOStreamTest::GenericStreamBuf::overflow(std::basic_streambuf<char>::int_type ch)
{
    std::basic_streambuf<char>::int_type Result;
    
    //std::basic_streambuf<char>::char_type* PutBegin = pbase();
    std::basic_streambuf<char>::char_type* PutEnd = epptr();
    //std::basic_streambuf<char>::char_type* PutCurrent = pptr();
    
    //std::basic_streambuf<char>::char_type* GetBegin = eback();
    std::basic_streambuf<char>::char_type* GetEnd = egptr();
    std::basic_streambuf<char>::char_type* GetCurrent = gptr();
    
    if(PutEnd >= GetEnd)
    {
        if(PutEnd < InternalMem + MemLength)
        {
            setp(PutEnd, PutEnd, InternalMem + MemLength);
        }
        else
        {
            setp(InternalMem, InternalMem, GetCurrent);
        }
    }
    else
    {
        setp(PutEnd, PutEnd, GetCurrent);
    }
    
    if(epptr() - pptr() > 0)
    {
        Result = sputc(ch);
    }
    else
    {
        Result = std::basic_streambuf<char>::overflow(ch);
    }
    
    return Result;
}
std::basic_streambuf<char>::int_type GenericIOStreamTest::GenericStreamBuf::underflow()
{
    std::basic_streambuf<char>::int_type Result;
    
    //std::basic_streambuf<char>::char_type* PutBegin = pbase();
    std::basic_streambuf<char>::char_type* PutEnd = epptr();
    std::basic_streambuf<char>::char_type* PutCurrent = pptr();
    
    //std::basic_streambuf<char>::char_type* GetBegin = eback();
    std::basic_streambuf<char>::char_type* GetEnd = egptr();
    //std::basic_streambuf<char>::char_type* GetCurrent = gptr();
    
    if(GetEnd > PutEnd)
    {
        if(GetEnd < InternalMem + MemLength)
        {
            setg(GetEnd, GetEnd, InternalMem + MemLength);
        }
        else
        {
            setg(InternalMem, InternalMem, PutCurrent);
        }
    }
    else if(GetEnd < PutEnd)
    {
        setg(GetEnd, GetEnd, PutCurrent);
    }
    else
    {
        if(GetEnd < InternalMem + MemLength)
        {
            setg(GetEnd, GetEnd, PutCurrent);
        }
        else
        {
            setg(InternalMem, InternalMem, PutCurrent);
        }
    }
    
    if(egptr() - gptr() > 0)
    {
        Result = sgetc();
    }
    else
    {
        Result = std::basic_streambuf<char>::underflow();
    }
    return Result;
}
std::streamsize GenericIOStreamTest::GenericStreamBuf::showmanyc()
{
    return std::basic_streambuf<char>::showmanyc();
}
