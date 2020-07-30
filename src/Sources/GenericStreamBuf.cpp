#include "GenericStreamBuf.h"
#include "stdafx.h"

// Public construction/destruction
GenericIOStreamTest::GenericStreamBuf::GenericStreamBuf(const size_t BufferSize) :
    MemLength(BufferSize),
    InternalMem(new char[BufferSize]),
    PCAdvance(false)
{
    std::memset(InternalMem, 0, BufferSize);
    setp(InternalMem, InternalMem);
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
void GenericIOStreamTest::GenericStreamBuf::PrintStreamBuf() const
{
    std::cout << "GenericStreamBuf[PrintStreamBuf]: " << InternalMem << std::endl;
}
void GenericIOStreamTest::GenericStreamBuf::PrintStatus() const
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
            setp(PutEnd, InternalMem + MemLength);
        }
        else
        {
            setp(InternalMem, GetCurrent);
        }
    }
    else if(PutEnd < GetEnd)
    {
        setp(PutEnd, GetCurrent);
    }
    else if(!PCAdvance)
    {
        if(PutEnd < InternalMem + MemLength)
        {
            setp(PutEnd, InternalMem + MemLength);
        }
        else
        {
            setp(InternalMem, GetCurrent);
        }
    }
	
    PCAdvance = true;
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
std::basic_streambuf<char>::pos_type GenericIOStreamTest::GenericStreamBuf::seekoff(std::basic_streambuf<char>::off_type off, std::ios_base::seekdir dir,
                            std::ios_base::openmode which)
{
    std::basic_streambuf<char>::pos_type ResultPos;
    switch(which)
    {
        case std::ios_base::in:
            ResultPos = seekoff_in(off, dir);
            break;
        case std::ios_base::out:
            ResultPos = seekoff_out(off, dir);
            break;
        default:
            ResultPos = std::basic_streambuf<char>::seekoff(off, dir, which);
            break;
    }
    return ResultPos;
}
std::basic_streambuf<char>::pos_type GenericIOStreamTest::GenericStreamBuf::seekpos(std::basic_streambuf<char>::pos_type pos,
                            std::ios_base::openmode which)
{
    return std::basic_streambuf<char>::seekpos(pos, which);
}
std::streamsize GenericIOStreamTest::GenericStreamBuf::showmanyc()
{
    std::streamsize NumChars = 0;
    //std::basic_streambuf<char>::char_type* PutBegin = pbase();
    std::basic_streambuf<char>::char_type* PutEnd = epptr();
    std::basic_streambuf<char>::char_type* PutCurrent = pptr();
    
    //std::basic_streambuf<char>::char_type* GetBegin = eback();
    std::basic_streambuf<char>::char_type* GetEnd = egptr();
    std::basic_streambuf<char>::char_type* GetCurrent = gptr();
    
    if(GetEnd > PutEnd)
    {
        // ((InternalMem + MemLength) - GetCurrent) + (PutCurrent - InternalMem)
        NumChars = PutCurrent + MemLength - GetCurrent;
    }
    else if(GetEnd < PutEnd)
    {
        NumChars = PutCurrent - GetCurrent;
    }
    else if(PCAdvance)
    {
        // ((InternalMem + MemLength) - GetCurrent) + (PutCurrent - InternalMem)
        NumChars = PutCurrent + MemLength - GetCurrent;
    }
    
    return NumChars;
}

// Private member functions
std::basic_streambuf<char>::pos_type GenericIOStreamTest::GenericStreamBuf::seekoff_in(const std::basic_streambuf<char>::off_type off,
                            const std::ios_base::seekdir dir)
{
    std::basic_streambuf<char>::pos_type ResultPos;
    std::basic_streambuf<char>::char_type* LimitPtr;
    long MaxPtrDiff;
    switch(dir)
    {
        case std::ios_base::beg:
            LimitPtr = gptr();
            MaxPtrDiff = LimitPtr - eback();
            setg(eback() + ((MaxPtrDiff >= off) ? off : MaxPtrDiff), LimitPtr, epptr());
            ResultPos = std::basic_streambuf<char>::pos_type(eback() - InternalMem);
            break;
        case std::ios_base::cur:
            LimitPtr = egptr();
            MaxPtrDiff = LimitPtr - gptr();
            gbump((MaxPtrDiff >= off) ? off : MaxPtrDiff);
            ResultPos = std::basic_streambuf<char>::pos_type(gptr() - InternalMem);
            break;
        case std::ios_base::end:
            LimitPtr = InternalMem + MemLength;
            MaxPtrDiff = LimitPtr - egptr();
            setg(pbase(), LimitPtr, egptr() + ((MaxPtrDiff >= off) ? off : MaxPtrDiff));
            ResultPos = std::basic_streambuf<char>::pos_type(egptr() - InternalMem);
            break;
        default:
            ResultPos = std::basic_streambuf<char>::pos_type(0);
            break;
    }
    return ResultPos;
}
std::basic_streambuf<char>::pos_type GenericIOStreamTest::GenericStreamBuf::seekoff_out(const std::basic_streambuf<char>::off_type off,
                            const std::ios_base::seekdir dir)
{
    std::basic_streambuf<char>::pos_type ResultPos;
    std::basic_streambuf<char>::char_type* LimitPtr;
    long MaxPtrDiff;
    switch(dir)
    {
        case std::ios_base::beg:
            LimitPtr = pptr();
            MaxPtrDiff = LimitPtr - pbase();
            setp(pbase() + ((MaxPtrDiff >= off) ? off : MaxPtrDiff), epptr());
            pbump(LimitPtr - pbase());
            ResultPos = std::basic_streambuf<char>::pos_type(pbase() - InternalMem);
            break;
        case std::ios_base::cur:
            MaxPtrDiff = epptr() - pptr();
            pbump((MaxPtrDiff >= off) ? off : MaxPtrDiff);
            ResultPos = std::basic_streambuf<char>::pos_type(pptr() - InternalMem);
            break;
        case std::ios_base::end:
            LimitPtr = pptr();
            MaxPtrDiff = InternalMem + MemLength - epptr();
            setp(pbase(), epptr() + ((MaxPtrDiff >= off) ? off : MaxPtrDiff));
            pbump(LimitPtr - pbase());
            ResultPos = std::basic_streambuf<char>::pos_type(epptr() - InternalMem);
            break;
        default:
            ResultPos = std::basic_streambuf<char>::pos_type(0);
            break;
    }
    return ResultPos;
}

