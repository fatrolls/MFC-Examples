// DictCtrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <stdio.h>
#include <comutil.h>

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
	String stringResult;
	BOOL bResult;
	HRESULT hResult;

	if (CoInitialize(NULL) != S_OK) {
		printf("Initialize COM library failed!\n");
		return -1;
	}

	GUID dictionaryCLSID;
	hResult = ::CLSIDFromProgID(L"Dictionary.Object", &dictionaryCLSID);
	if (hResult != S_OK) 
	{
		printf("Can't find the dictionary CLSID!\n");
		return -2;
	}
	
	hResult = CoCreateInstance(dictionaryCLSID, NULL, 
		CLSCTX_INPROC_SERVER, IID_IUnknown, (void **)&pUnknown);
	if (hResult != S_OK) 
	{
		printf("Create object failed!\n");
		return -2;
	}

	hResult = pUnknown->QueryInterface(IID_Dictionary, (void **)&pDictionary);
	if (hResult != S_OK) {
		pUnknown->Release();
		printf("QueryInterface IDictionary failed!\n");
		return -3;
	}
	bResult = pDictionary->LoadLibrary(L"animal.dict");
	if (bResult) {
		String stringResult;
		bResult = pDictionary->LookupWord(L"tiger", &stringResult);
		
		if (bResult) {
			char *pTiger = _com_util::ConvertBSTRToString(stringResult);
			printf("find the word \"tiger\" -- %s\n", pTiger);
			delete pTiger;
		}

		pDictionary->InsertWord(L"elephant", L"Ïó");
		bResult = pDictionary->LookupWord(L"elephant", &stringResult);
		if (bResult) {

			pDictionary->RestoreLibrary(L"animal1.dict");
		}
	} else {
		printf("Load Library \"animal.dict\"\n");
	}
	
	hResult = pDictionary->QueryInterface(IID_SpellCheck, (void **)&pSpellCheck);
	pDictionary->Release();
	if (hResult != S_OK) {
		pUnknown->Release();
		printf("QueryInterface IDictionary failed!\n");
		return -4;
	}

	bResult = pSpellCheck->CheckWord(L"lion", &stringResult);
	if (bResult) {
		printf("Word \"lion\" spelling right.\n");
	} else {
		char *pLion = _com_util::ConvertBSTRToString(stringResult);
		printf("Word \"lion\" spelling is wrong. Maybe it is %s.\n", pLion);
		delete pLion;
	}
	bResult = pSpellCheck->CheckWord(L"dot", &stringResult);
	if (bResult) {
		printf("Word \"dot\" spelling right.\n");
	} else {
		char *pDot = _com_util::ConvertBSTRToString(stringResult);
		printf("Word \"dot\" spelling is wrong. Maybe it is %s.\n", pDot);
		delete pDot;
	}

	pSpellCheck->Release();
	if (pUnknown->Release()== 0) 
		printf("The reference count of dictionary object is zero.");

	CoUninitialize();
	return 0;
}
