// DictCtrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <stdio.h>

#include "IDictionary.h"
#include "ISpellCheck.h"

// {54BF6567-1007-11D1-B0AA-444553540000}
extern "C" const GUID CLSID_Dictionary = 
		{ 0x54bf6567, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;

extern "C" const GUID IID_Dictionary = 
		{ 0x54bf6568, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;

extern "C" const GUID IID_SpellCheck = 
		{ 0x54bf6569, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;


int main(int argc, char* argv[])
{
	IUnknown *pUnknown;
	IDictionary *pDictionary;
	ISpellCheck *pSpellCheck;
	WCHAR  stringResult[32];
	HRESULT hResult;

	if (CoInitialize(NULL) != S_OK) {
		printf("Initialize COM library failed!\n");
		CoUninitialize();
		return -1;
	}

	GUID dictionaryCLSID;
	hResult = ::CLSIDFromProgID(L"Dictionary.Object", &dictionaryCLSID);
	if (FAILED(hResult)) 
	{
		printf("Can't find the dictionary CLSID!\n");
		CoUninitialize();
		return -2;
	}
	
	hResult = CoCreateInstance(dictionaryCLSID, NULL, 
		CLSCTX_LOCAL_SERVER, IID_IUnknown, (void **)&pUnknown);
	if (FAILED(hResult)) 
	{
		printf("Create object failed!\n");
		CoUninitialize();
		return -2;
	}

	hResult = pUnknown->QueryInterface(IID_Dictionary, (void **)&pDictionary);
	if (FAILED(hResult)) {
		pUnknown->Release();
		printf("QueryInterface IDictionary failed!\n");
		CoUninitialize();
		return -3;
	}
	
	char strDirectory[256];
	::GetCurrentDirectory(200, strDirectory);
	strcat(strDirectory, "\\animal.dict");
	WCHAR pLibFileName[256];
	mbstowcs(pLibFileName, strDirectory, 256);
	hResult = pDictionary->LoadLibrary(pLibFileName);

	if (SUCCEEDED(hResult)) {
		hResult = pDictionary->LookupWord(L"tiger", stringResult);
		
		if (SUCCEEDED(hResult)) {
			char *pTiger = new char[32];
			wcstombs(pTiger, stringResult, 32) ;
			printf("find the word \"tiger\" -- %s\n", pTiger);
			delete pTiger;
		}

		pDictionary->InsertWord(L"elephant", L"Ïó");
		hResult = pDictionary->LookupWord(L"elephant", stringResult);
		if (SUCCEEDED(hResult)) {
			pDictionary->RestoreLibrary(L"animal1.dict");
		}
	} else {
		printf("Load Library \"%s\" Failed!\n", strDirectory);
		pDictionary->Release();
		pUnknown->Release();
		CoUninitialize();
		return -4;
	}
	
	hResult = pDictionary->QueryInterface(IID_SpellCheck, (void **)&pSpellCheck);
	pDictionary->Release();
	if (FAILED(hResult)) {
		pUnknown->Release();
		printf("QueryInterface IDictionary failed!\n");
		CoUninitialize();
		return -5;
	}

	hResult = pSpellCheck->CheckWord(L"lion", stringResult);
	if (SUCCEEDED(hResult)) {
		printf("Word \"lion\" spelling right.\n");
	} else {
		char *pLion = new char[32];
		wcstombs(pLion, stringResult, 32) ;
		printf("Word \"lion\" spelling is wrong. Maybe it is %s.\n", pLion);
		delete pLion;
	}
	hResult = pSpellCheck->CheckWord(L"dot", stringResult);
	if (SUCCEEDED(hResult)) {
		printf("Word \"dot\" spelling right.\n");
	} else {
		char *pDot = new char[32];
		wcstombs(pDot, stringResult, 32) ;
		printf("Word \"dot\" spelling is wrong. Maybe it is %s.\n", pDot);
		delete pDot;
	}

	pSpellCheck->Release();
	if (pUnknown->Release()== 0) 
		printf("The reference count of dictionary object is zero.");

	CoUninitialize();
	return 0;
}