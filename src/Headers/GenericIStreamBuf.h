#ifndef GENERICISTREAMBUF_H
#define GENERICISTREAMBUF_H

#include <streambuf>

namespace GenericIOStreamTest
{
    class GenericIStreamBuf : public std::basic_streambuf<char>
    {
    // Public structures
    public:
        struct DataRetrieveCallback_base
        {
        // Public member functions
        public:
            virtual void Invoke(char* const Buffer, const size_t MaxLen)
            {
                
            }
        };
        
        template<class T>
        struct DataRetrieveCallback_member : public DataRetrieveCallback_base
        {
        // Public construction
        public:
            DataRetrieveCallback_member(T* Ref, size_t (T::* Func)(char* const, const size_t)) :
                MemRef(Ref),
                MemFunc(Func)
            {
                
            }
            
        // Public member functions
        public:
            virtual void Invoke(char* const Buffer, const size_t MaxLen)
            {
                (MemRef->*MemFunc)(Buffer, MaxLen);
            }
            
        // Private member variables
        private:
            T* MemRef;
            size_t (T::* MemFunc)(char* const Buffer, const size_t MaxLen);
        };
        
        struct DataRetrieveCallback_plain : public DataRetrieveCallback_base
        {
        // Public construction
        public:
            DataRetrieveCallback_plain(size_t (*FuncRef)(char* const, const size_t)) :
                Func(FuncRef)
            {
                
            }
            
        // Public member functions
        public:
            virtual void Invoke(char* const Buffer, const size_t MaxLen)
            {
                (*Func)(Buffer, MaxLen);
            }
            
        // Private member variables
        private:
            size_t (*Func)(char* const, const size_t);
        };
        
    // Public construction/destruction
    public:
        GenericIStreamBuf(const size_t BufferSize);
        ~GenericIStreamBuf();
        
    // Public member functions
    public:
        void RegisterOnDataRetrieveCallback(DataRetrieveCallback_base* const DataRetCB);
        
    // Protected member functions
    protected:
        virtual std::basic_streambuf<char>::int_type underflow();
        
    // Private member variables
    private:
        const size_t MemLength;
        char* InternalMem;
        DataRetrieveCallback_base* DataRetrieveCB;
    };
}

#endif // GENERICISTREAMBUF_H
