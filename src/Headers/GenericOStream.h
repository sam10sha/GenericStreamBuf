#ifndef GENERICOSTREAM_H
#define GENERICOSTREAM_H

#include <iostream>

namespace GenericIOStreamTest
{
    class GenericOStream : public std::ostream
    {
    // Public construction
    public:
        GenericOStream(std::streambuf* const IntBuf);
        
    // Private member variables
    private:
        std::streambuf* InternalBuffer;
    };
}

#endif // GENERICOSTREAM_H
