#ifndef GENERICSTREAMBUF_H
#define GENERICSTREAMBUF_H

#include <boost/circular_buffer.hpp>
#include <iostream>

namespace GenericIOStreamTest
{
    class GenericStreamBuf : public std::basic_streambuf<char>
    {
    // Public construction/destruction
    public:
        GenericStreamBuf(const size_t BufferSize);
        ~GenericStreamBuf();
        
    // Public member functions
    public:
        void PrintStreamBuf();
        
    // Protected member functions
    protected:
        virtual std::basic_streambuf<char>::int_type overflow(std::basic_streambuf<char>::int_type ch);
        virtual std::basic_streambuf<char>::int_type underflow();
        virtual std::streamsize showmanyc();
        
    // Private member variables
    private:
        const size_t MemLength;
        char* InternalMem;
    };
}

#endif // GENERICSTREAMBUF_H