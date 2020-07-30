#include "stdafx.h"
#include "GenericStreamBuf.h"
#include "GenericIStreamBuf.h"
#include "GenericIStream.h"
#include "GenericOStream.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using GenericIOStreamTest::GenericIStreamBuf;
using GenericIOStreamTest::GenericStreamBuf;
using GenericIOStreamTest::GenericIStream;
using GenericIOStreamTest::GenericOStream;

void TestGenericStreamBuf();
void TestGenericIStreamBuf();
size_t RetrieveData(void* const Buffer, const size_t MaxLen);

vector<string> Words;

int main(int argc, char** argv)
{
    //TestGenericStreamBuf();
    TestGenericIStreamBuf();
    return 0;
}

void TestGenericStreamBuf()
{
    //GenericStreamBuf StreamBuf(0x100);
    GenericStreamBuf StreamBuf(0x5);
    GenericIStream IStream(&StreamBuf);
    GenericOStream OStream(&StreamBuf);
    char Bytes[0x40];
    std::memset(Bytes, 0, 0x40);
    
    OStream << "Hello";
    std::memset(Bytes, 0, 0x40);
    IStream.read(Bytes, 5);
    cout << Bytes << endl;
    
    OStream << "world";
    std::memset(Bytes, 0, 0x40);
    IStream.read(Bytes, 5);
    cout << Bytes << endl;
    
    OStream << "Hi";
    std::memset(Bytes, 0, 0x40);
    IStream.read(Bytes, 2);
    cout << Bytes << endl;
    
    OStream << "Meera";
    StreamBuf.PrintStatus();
    StreamBuf.PrintStreamBuf();
    std::memset(Bytes, 0, 0x40);
    IStream.read(Bytes, 5);
    StreamBuf.PrintStatus();
    cout << Bytes << endl;
    
    
    //cout << IStream.rdbuf();
    //StreamBuf.PrintStreamBuf();
}

void TestGenericIStreamBuf()
{
    Words.push_back("a");
    Words.push_back("f");
    Words.push_back("t");
    Words.push_back("q");
    Words.push_back("hi");
    Words.push_back("of");
    Words.push_back("no");
    Words.push_back("if");
    Words.push_back("the");
    Words.push_back("can");
    Words.push_back("box");
    Words.push_back("dog");
    Words.push_back("soda");
    Words.push_back("lawn");
    Words.push_back("wall");
    Words.push_back("door");
    Words.push_back("chair");
    Words.push_back("phone");
    Words.push_back("plane");
    Words.push_back("table");
    Words.push_back("vision");
    Words.push_back("filter");
    Words.push_back("device");
    Words.push_back("fridge");
    GenericIStreamBuf::DataRetrieveCallback_plain DataRetrieveCB(&RetrieveData);
    GenericIStreamBuf IStreamBuf(0x10);
    GenericIStream IStream(&IStreamBuf);
    char Bytes[0x40];
    std::memset(Bytes, 0, 0x40);
    
    IStreamBuf.RegisterOnDataRetrieveCallback(&DataRetrieveCB);
    
    IStream.read(Bytes, 6);
    //IStreamBuf.PrintStreamBuf();
    cout << Bytes << endl;
}
size_t RetrieveData(void* const Buffer, const size_t MaxLen)
{
    int WordIndex;
    if(MaxLen >= 6)
    {
        WordIndex = 20 + (rand() % 4);
    }
    else
    {
        WordIndex = (MaxLen - 1) * 4 + (rand() % 4);
    }
    string& Word = Words.at(WordIndex);
    size_t WordLen = Word.size();
    std::strcpy((char*)Buffer, Word.c_str());
    return WordLen;
}
