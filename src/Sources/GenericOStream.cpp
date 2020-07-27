#include "GenericOStream.h"

// Public construction/destruction
GenericIOStreamTest::GenericOStream::GenericOStream(std::streambuf* const IntBuf) :
    std::ostream(IntBuf),
    InternalBuffer(IntBuf)
{
    
}
