// DictCtrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <stdio.h>
#include <comutil.h>

#include "IMyUnknown.h"
#include "IDictionary.h"
#include "ISpellCheck.h"

// {54BF6567-1007-11D1-B0AA-444553540000}
extern "C" const GUID CLSID_Dictionary = 
		{ 0x54bf6567, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;
HMODULE hModual;

BOOL CreateObject(const CLSID& clsid, const IID& iid, void **ppv)
{

	hModual = LoadLibrary("DictComp.dll");
	if (hModual == NULL) return 0;
	
	typedef BOOL  (__stdcall*  MyFunctionType)(const CLSID& clsid, const IID& iid, void **ppv);
	MyFunctionType fnCreateObject;
	
	fnCreateObject = (MyFunctionType)GetProcAddress(hModual, "CreateObject");
	if (fnCreateObject == NULL) {
		FreeLibrary(hModual);
		return FALSE;
	}

	return fnCreateObject(clsid, iid, ppv);
}

int main(int argc, char* argv[])
{
	hModual = NULL;
	IMyUnknown *pMyUnknown;
	IDictionary *pDictionary;
	ISpellCheck *pSpellCheck;
	String stringResult;
	BOOL bResult;
	HRESULT hResult;

	bResult = CreateObject(CLSID_Dictionary, IID_IUnknown, (void **)&pMyUnknown);
	if (bResult == FALSE) 
	{
		printf("Create object failed!\n");
		return -1;
	}

	hResult = pMyUnknown->QueryInterface(IID_Dictionary, (void **)&pDictionary);
	if (hResult != S_OK) {
		pMyUnknown->Release();
		printf("QueryInterface IDictionary failed!\n");
		return -2;
	}
	bResult = pDictionary->LoadLibrary(L"animal.dict");
	if (bResult) {

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
		return -2;
	}
	
	hResult = pDictionary->QueryInterface(IID_SpellCheck, (void **)&pSpellCheck);
	pDictionary->Release();
	if (hResult != S_OK) {
		pMyUnknown->Release();
		printf("QueryInterface IDictionary failed!\n");
		return -2;
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
	if (pMyUnknown->Release()== 0) 
		FreeLibrary(hModual);
	return 0;
}
