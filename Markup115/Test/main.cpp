#include "MarkupTest.h"

int main()
{
	CMarkupTest test;
	test.RunTest();
#if defined(MARKUP_WCHAR)
	wprintf( MCD_T("%ls"), MCD_2PCSZ(test.m_strResult) );
#else
	printf( MCD_T("%s"), MCD_2PCSZ(test.m_strResult) );
#endif
	return 0;
}
