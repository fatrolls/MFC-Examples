

#include <windows.h>
#include <iostream.h>

char buf[4100];

class CTestClass
{
	char m_chBuf[4096];
public:	
	//*	If you don`t want to use memory pool, please mark two following function!
	void *operator new(unsigned int uiSize)
	{
		return (void *)buf;
	}
	void  operator delete(void *p)
	{
	}
	//*/
};


int main()
{	
	DWORD count = GetTickCount();
	
	for(unsigned int i=0; i<0x5fffff; i++)
	{
		CTestClass *p = new CTestClass;
		delete p;
	}
	
	cout << "Interval = " << GetTickCount()-count << " ms" << endl;

	
	return 0;
}

