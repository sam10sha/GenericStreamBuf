#include "GenericIStream.h"

// Public construction/destruction
GenericIOStreamTest::GenericIStream::GenericIStream(std::streambuf* const IntBuf) :
    std::istream(IntBuf),
    InternalBuffer(IntBuf)
{
    
}
