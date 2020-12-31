
#include "TestClass.h"
#include "MemPool.h"

extern CMemPool g_MemPool;
	
//*
void *CTestClass::operator new(unsigned int uiSize)
{
	return g_MemPool.Alloc(uiSize);
}


void  CTestClass::operator delete(void *p)
{
	g_MemPool.Free(p);
}
//*/

