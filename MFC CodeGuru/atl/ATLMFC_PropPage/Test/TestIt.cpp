// Test.cpp
#include <windows.h>

#include <olectl.h>
#include "..\ATLMFC.h"

#include "..\ATLMFC_i.c"

int main()
{
	CoInitialize(NULL);

	// Only one page in this example

	ITest* pTest;
	CoCreateInstance(
		CLSID_Test,
		NULL,
		CLSCTX_SERVER,
		IID_ITest,
		(LPVOID*)&pTest
		);
	if (NULL==pTest)
		// Can't create object CLSID_Test!
		return 1;

	LPUNKNOWN pUnk=pTest;
	HRESULT hr=OleCreatePropertyFrame(
		NULL,
		100,
		100,
		L"My Test",
		1,
		&pUnk,
		1,
		(LPCLSID)&CLSID_PpgTest,
		0,
		0, NULL);

	pTest->Release();
	pTest=NULL;


	CoUninitialize();
	return 0;
}