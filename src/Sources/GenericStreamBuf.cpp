#include "GenericStreamBuf.h"
#include "stdafx.h"

// Public construction/destruction
GenericIOStreamTest::GenericStreamBuf::GenericStreamBuf(const size_t BufferSize) :
    MemLength(BufferSize),
    InternalMem(new char[BufferSize]),
    PCAdvance(true)
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
void GenericIOStreamTest::GenericStreamBuf::PrintStatus()
{
    std::cout << "GenericStreamBuf[PrintStatus]: PutBegin = " << pbase() - InternalMem << std::endl;
    std::cout << "GenericStreamBuf[PrintStatus]: PutEnd = " << epptr() - InternalMem << std::endl;
    std::cout << "GenericStreamBuf[PrintStatus]: PutCurrent = " << pptr() - InternalMem << std::endl;
    std::cout << "GenericStreamBuf[PrintStatus]: GetBegin = " << eback() - InternalMem << std::endl;
    std::cout << "GenericStreamBuf[PrintStatus]: GetEnd = " << egptr() - InternalMem << std::endl;
    std::cout << "GenericStreamBuf[PrintStatus]: GetCurrent = " << gptr() - InternalMem << std::endl;
    std::cout << "GenericStreamBuf[PrintStatus]: PCAdvance = " << PCAdvance << std::endl;
}


// Protected member functions
std::basic_streambuf<char>::int_type GenericIOStreamTest::GenericStreamBuf::overflow(std::basic_streambuf<char>::int_type ch)
{
    std::cout << "GenericStreamBuf[overflow]: Overflow" << std::endl;
    
    std::basic_streambuf<char>::int_type Result;
    
    //std::basic_streambuf<char>::char_type* PutBegin = pbase();
    std::basic_streambuf<char>::char_type* PutEnd = epptr();
    //std::basic_streambuf<char>::char_type* PutCurrent = pptr();
    
    //std::basic_streambuf<char>::char_type* GetBegin = eback();
    std::basic_streambuf<char>::char_type* GetEnd = egptr();
    std::basic_streambuf<char>::char_type* GetCurrent = gptr();
    
    if(PutEnd > GetEnd)
    {
        if(PutEnd < InternalMem + MemLength)
        {
            setp(PutEnd, PutEnd, InternalMem + MemLength);
        }
        else //if(GetCurrent != InternalMem)
        {
            setp(InternalMem, InternalMem, GetCurrent);
        }
    }
    else if(PutEnd < GetEnd) //&& PutEnd != GetCurrent)
    {
        setp(PutEnd, PutEnd, GetCurrent);
    }
    else if(!PCAdvance)
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
	
    PCAdvance = true;
    //PrintStatus();
    if(epptr() - pptr() > 0)
    {
        std::cout << "GenericStreamBuf[overflow]: Write space available" << std::endl;
        Result = sputc(ch);
    }
    else
    {
        std::cout << "GenericStreamBuf[overflow]: Write space unavailable" << std::endl;
        Result = std::basic_streambuf<char>::overflow(ch);
    }
    
    return Result;
}
std::basic_streambuf<char>::int_type GenericIOStreamTest::GenericStreamBuf::underflow()
{
    std::cout << "GenericStreamBuf[underflow]: Underflow" << std::endl;
    
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
        else //if(PutCurrent != InternalMem)
        {
            setg(InternalMem, InternalMem, PutCurrent);
        }
    }
    else if(GetEnd < PutEnd) //&& GetEnd != PutCurrent)
    {
        setg(GetEnd, GetEnd, PutCurrent);
    }
    else if(PCAdvance)
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
    
    PCAdvance = PutEnd != egptr();
    //PrintStatus();
    if(egptr() - gptr() > 0)
    {
        std::cout << "GenericStreamBuf[underflow]: Read space available" << std::endl;
        Result = sgetc();
    }
    else
    {
        std::cout << "GenericStreamBuf[underflow]: Read space unavailable" << std::endl;
        Result = std::basic_streambuf<char>::underflow();
    }
    return Result;
}
std::streamsize GenericIOStreamTest::GenericStreamBuf::showmanyc()
{
    return std::basic_streambuf<char>::showmanyc();
}
