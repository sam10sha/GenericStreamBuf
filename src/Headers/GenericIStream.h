#ifndef GENERICISTREAM_H
#define GENERICISTREAM_H

#include <iostream>

namespace GenericIOStreamTest
{
    class GenericIStream : public std::istream
    {
    // Public construction
    public:
        GenericIStream(std::streambuf* const IntBuf);
        
    // Private member variables
    private:
        std::streambuf* InternalBuffer;
    };
}

#endif // GENERICISTREAM_H
