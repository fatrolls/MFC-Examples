#include "countobj.hpp"
template<class BeingCounted>
Counted<BeingCounted>::Counted()
{
    init();
}
template<class BeingCounted>
Counted<BeingCounted>::Counted(const Counted<BeingCounted>&)
{
    init();
}
template<class BeingCounted>
void Counted<BeingCounted>::init()
{
    if (numObjects >= maxObjects) throw TooManyObjects();
    ++numObjects;
}
 

////////////other file//////////////////
template<class BeingCounted>                  
int Counted<BeingCounted>::numObjects;       
const size_t Counted<Printer>::maxObjects = 10;


//////////////////maxobject///////////////////////

// Obligatory definitions of class statics
size_t MPrinter::numObjects = 0;
//const size_t MPrinter::maxObjects;//??
MPrinter::MPrinter()
{
    if (numObjects >= maxObjects) {
        throw TooManyObjects();
    }
    ////...
}
MPrinter::MPrinter(const MPrinter& rhs)
{
    if (numObjects >= maxObjects) {
        throw TooManyObjects();
    }
    ////...
}
MPrinter * MPrinter::makePrinter()
{
    return new MPrinter;
}
MPrinter * MPrinter::makePrinter(const MPrinter& rhs)
{
    return new MPrinter(rhs);
}


//////////////////maxobject///////////////////////
