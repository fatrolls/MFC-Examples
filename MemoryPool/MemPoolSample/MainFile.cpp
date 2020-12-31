
#include <windows.h>
#include <iostream.h>
#include "TestClass.h"
#include "TestClass2.h"
#include "MemPool.h"

#define LOOP_TIMES 100000*iTestCnt	

CMemPool g_MemPool(10);

int main()
{
	for(int iTestCnt=1; iTestCnt<=10; iTestCnt++)
	{
	
		unsigned int i;
		DWORD count = GetTickCount();
		
		for(i=0; i<LOOP_TIMES; i++)
		{
			//class CTestClass and class CTestClass2 are almost same!
			CTestClass *p = new CTestClass;	    //Using memory pool
			delete p;
		}
		
		cout << "[ Repeat " << LOOP_TIMES << " Times ]" << "Using memory pool! Interval 1 = " << GetTickCount()-count << " ms" << endl;
		
		//================================================================
		
		count = GetTickCount();
		
		for(i=0; i<LOOP_TIMES; i++)
		{
			CTestClass2 *p = new CTestClass2;	//No memory pool
			delete p;
		}
		
		cout << "[ Repeat " << LOOP_TIMES << " Times ]" << "No memory pool!    Interval 2 = " << GetTickCount()-count << " ms" << endl;
		
		//==============================================================

		cout << endl;
	}
	
	return 0;
}
