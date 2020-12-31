// CompCtrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "windows.h"
#include <stdio.h>
#include <comutil.h>

#include "SomeIFace.h"
#include "OtherIFace.h"

// {16DCB982-BEEB-11d2-B362-00104B08CC22}
extern "C" const GUID IID_SomeInterface = 
		{ 0x16dcb982, 0xbeeb, 0x11d2, 
		{ 0xb3, 0x62, 0x0, 0x10, 0x4b, 0x8, 0xcc, 0x22 } };

// {39C07942-BFCC-11d2-A100-00A0C9A6F472}
extern "C" const GUID IID_OtherInterface = 
		{ 0x39c07942, 0xbfcc, 0x11d2, 
		{ 0xa1, 0x0, 0x0, 0xa0, 0xc9, 0xa6, 0xf4, 0x72 } };


int main(int argc, char* argv[])
{
	IUnknown *pUnknown;
	ISomeInterface *pSomeInterface;
	IOtherInterface *pOtherInterface;
	HRESULT hResult;

	if (CoInitialize(NULL) != S_OK) {
		printf("Initialize COM library failed!\n");
		return -1;
	}

	GUID compBCLSID;
	hResult = ::CLSIDFromProgID(L"CompB.Object", &compBCLSID);
	if (FAILED(hResult)) 
	{
		printf("Can't find the CompB CLSID!\n");
		CoUninitialize();
		return -2;
	}
	
	hResult = CoCreateInstance(compBCLSID, NULL, 
		CLSCTX_INPROC_SERVER, IID_IUnknown, (void **)&pUnknown);
	if (FAILED(hResult)) 
	{
		printf("Create object failed!\n");
		CoUninitialize();
		return -2;
	}

	hResult = pUnknown->QueryInterface(IID_SomeInterface, (void **)&pSomeInterface);
	pUnknown->Release();
	if (FAILED(hResult)) 
	{
		printf("QueryInterface ISomeInterface failed!\n");
		CoUninitialize();
		return -3;
	}

	pSomeInterface->SomeFunction();
	
	hResult = pSomeInterface->QueryInterface(IID_OtherInterface, (void **)&pOtherInterface);
	pSomeInterface->Release();
	if (FAILED(hResult)) 
	{
		printf("QueryInterface IOtherInterface failed!\n");
		CoUninitialize();
		return -4;
	}

	pOtherInterface->OtherFunction();

	pOtherInterface->Release();
	CoUninitialize();
	return 0;
}
