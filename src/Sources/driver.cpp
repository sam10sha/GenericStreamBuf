#include "stdafx.h"
#include "GenericStreamBuf.h"
#include "GenericIStream.h"
#include "GenericOStream.h"

using std::cout;
using std::endl;
using GenericIOStreamTest::GenericStreamBuf;
using GenericIOStreamTest::GenericIStream;
using GenericIOStreamTest::GenericOStream;

int main(int argc, char** argv)
{
    //GenericStreamBuf StreamBuf(0x100);
    GenericStreamBuf StreamBuf(0x5);
    GenericIStream IStream(&StreamBuf);
    GenericOStream OStream(&StreamBuf);
    char Bytes[0x40];
    std::memset(Bytes, 0, 0x40);
    
    OStream << "Hello";
    //IStream.read(Bytes, 6);
    IStream.read(Bytes, 5);
    cout << Bytes << endl;
    
    OStream << "world";
    //IStream.read(Bytes, 6);
    IStream.read(Bytes, 5);
    cout << Bytes << endl;
    
    OStream << "Hi";
    std::memset(Bytes, 0, 0x40);
    IStream.read(Bytes, 5);
    cout << Bytes << endl;
    
    
    //cout << IStream.rdbuf();
    //StreamBuf.PrintStreamBuf();
    
    return 0;
}
