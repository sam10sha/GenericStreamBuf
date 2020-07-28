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
    
    cout << "Starting 1" << endl;
    OStream << "Hello";
    //OStream << "world";
    StreamBuf.PrintStatus();
    StreamBuf.PrintStreamBuf();
    std::memset(Bytes, 0, 0x40);
    IStream.read(Bytes, 5);
    StreamBuf.PrintStatus();
    cout << Bytes << endl;
    
    /* OStream << "world";
    StreamBuf.PrintStreamBuf();
    std::memset(Bytes, 0, 0x40);
    IStream.read(Bytes, 5);
    cout << Bytes << endl; */
    
    cout << "Starting 2" << endl;
    OStream << "Hi";
    /* OStream << "Hello";
    OStream << "world";
    OStream << "this";
    OStream << "is";
    OStream << "Saumil";
    StreamBuf.sputc('h'); */
    cout << "Done outputting data" << endl;
    StreamBuf.PrintStatus();
    StreamBuf.PrintStreamBuf();
    std::memset(Bytes, 0, 0x40);
    cout << Bytes << endl;
    IStream.read(Bytes, 5);
    StreamBuf.PrintStatus();
    cout << Bytes << endl;
    
    
    //cout << IStream.rdbuf();
    //StreamBuf.PrintStreamBuf();
    
    return 0;
}
