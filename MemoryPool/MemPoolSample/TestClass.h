
#ifndef __TESTCLASS_H__
#define __TESTCLASS_H__


class CTestClass
{
public:
	//*
	void *operator new(unsigned int uiSize);	//Must overload the function. It`s static function.
	void  operator delete(void *p);				//Must overload the function. It`s static function.
	//*/
	
private:
	char m_chBuf[1000];
};

#endif //__TESTCLASS_H__