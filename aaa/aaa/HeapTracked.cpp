#include <list>
#include <algorithm>
using namespace std;
typedef const void* RawAddress;
class HeapTracked                    
{
public:                               
    class MissingAddress{};           
    virtual ~HeapTracked() = 0;
    static void *operator new(size_t size);
    static void operator delete(void *ptr);
    bool isOnHeap() const;
private:
    
    static list<RawAddress> addresses;
};
// mandatory definition of static class member
list<RawAddress> HeapTracked::addresses; 
HeapTracked::~HeapTracked() {}
void * HeapTracked::operator new(size_t size)
{
    void *memPtr = ::operator new(size);   
    addresses.push_front(memPtr);         
    return memPtr;
}
void HeapTracked::operator delete(void *ptr)
{
 
    list<RawAddress>::iterator it =
        find(addresses.begin(), addresses.end(), ptr);
    if (it != addresses.end()) {        
        addresses.erase(it);            
        ::operator delete(ptr);         
    } else {                           
        throw MissingAddress();           
    }                                
}
bool HeapTracked::isOnHeap() const
{
 

    const void *rawAddress = dynamic_cast<const void*>(this);
 
    list<RawAddress>::iterator it =
        find(addresses.begin(), addresses.end(), rawAddress);
    return it != addresses.end();       
}

class UPNumber
{
public:
    UPNumber(){}
    UPNumber(int initValue){}
    UPNumber(double initValue){}
    UPNumber(const UPNumber& rhs);
 
    void destroy() const {
        delete this;
    }
    //////...
protected:        //private
    ~UPNumber(){}
};

class NonNegativeUPNumber : public UPNumber
{
    //////...
};

class Asset : public HeapTracked
{
public:
    Asset(int initValue);
    ~Asset();
    ////...
private:
    UPNumber *value; //UPNumber value;
};
Asset::Asset(int initValue) : value(new UPNumber(initValue))
{
    //////...
}
Asset::~Asset()
{
    value->destroy();
}

void inventoryAsset(const Asset *ap)
{
    if (ap->isOnHeap()) {
        //ap is a heap-based asset  . inventory it as such;
    } else {
        //ap is a non-heap-based asset . record it that way;
    }
}

class UPNumber2
{
private:
    static void *operator new(size_t size);
    static void operator delete(void *ptr);
    //////...
};
class NonNegativeUPNumber2:         
            public UPNumber2                 
{
    //////...
};

class Asset2
{
public:
    Asset2(int initValue);
    //////...
private:
    UPNumber2 value;
};
Asset *pa = new Asset(100);
