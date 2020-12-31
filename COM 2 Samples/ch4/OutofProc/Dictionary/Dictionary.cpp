// Dictionary.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
#include "objbase.h"
#include "olectl.h"

#include "Dictionary.h"
#include "factory.h"
#include "registry.h"

ULONG    g_LockNumber = 0;
ULONG    g_DictionaryNumber = 0;
DWORD	 dwMainThreadID;

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

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// Initialize the COM Library.
	HRESULT hr = CoInitialize(NULL) ;
	if (FAILED(hr))
	{
		return 0 ;
	}
   
	int retVal = 0;
	// If TRUE, don't loop.
	BOOL bExit = FALSE ;

	// Read the command line.
	char szTokens[] = "-/" ;
	dwMainThreadID = ::GetCurrentThreadId() ;

	char* szToken = strtok(lpCmdLine, szTokens) ; 
	while (szToken != NULL)
	{
		if (_stricmp(szToken, "RegServer") == 0)
		{
			char szModule[1024];
			DWORD dwResult = ::GetModuleFileName((HMODULE)hInstance, szModule, 1024);
			if (dwResult == 0)
				retVal = SELFREG_E_CLASS;
			retVal = RegisterServer(CLSID_Dictionary,
								  szModule, 
								  "Dictionary.Object",
								  "Dictionary Component",
								  NULL);
			// We are done, so exit.
			bExit = TRUE ;
		}
		else if (_stricmp(szToken, "UnregServer") == 0)
		{
			retVal = UnregisterServer(CLSID_Dictionary,
	                        "Dictionary.Object",NULL);
			// We are done, so exit.
			bExit = TRUE ;
		}
		else if (_stricmp(szToken, "Embedding") == 0)
		{
			bExit = FALSE;
			break ;
		}
		szToken = strtok(NULL, szTokens) ;
	}

	if (!bExit)
	{
		// Register all of the class factory.
		CDictionaryFactory::RegisterFactory();

		// Wait for shutdown.
		MSG msg ;
		while (::GetMessage(&msg, 0, 0, 0))
		{
			::DispatchMessage(&msg);
		}

		// Unregister the class factory.
		CDictionaryFactory::UnregisterFactory() ;
	}

	// Uninitialize the COM Library.
	CoUninitialize() ;
	return 0 ;
}

// class CDictionary implementation

CDictionary::CDictionary()
{
	m_Ref = 0;
	m_nWordNumber = 0;
	m_nStructNumber = 0;
	m_pData = NULL;
	g_DictionaryNumber ++ ;
}

CDictionary::~CDictionary()
{
	if (m_pData != NULL) 
	{
		delete [] m_pData;
	}
	if (CDictionaryFactory::CanUnloadNow()) {
		::PostThreadMessage(dwMainThreadID, WM_QUIT, 0, 0) ;
	}
}

HRESULT  CDictionary::QueryInterface(const IID& iid, void **ppv)
{
	if ( iid == IID_IUnknown )
	{
		*ppv = (IDictionary *) this ;
				((IDictionary *)(*ppv))->AddRef() ;
	} else if ( iid == IID_Dictionary ) 
	{
		*ppv = (IDictionary *) this ;
				((IDictionary *)(*ppv))->AddRef() ;
	} else if ( iid == IID_SpellCheck ) 
	{
		*ppv = (ISpellCheck *) this ;
				((ISpellCheck *)(*ppv))->AddRef() ;
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE ;
	}
	return S_OK;
}

ULONG	  CDictionary::AddRef()
{
	m_Ref ++;
	return  (ULONG) m_Ref;
}

ULONG	  CDictionary::Release()
{
	m_Ref --;
	if (m_Ref == 0 ) {
		g_DictionaryNumber -- ;
		delete this;
		return 0;
	}
	return  (ULONG) m_Ref;
}

HRESULT CDictionary::Initialize()
{
	m_nWordNumber = 0;
	m_nStructNumber = 0;
	if (m_pData != NULL) 
	{
		delete [] m_pData;
	}
	m_pData = NULL;
	return S_OK;
}

HRESULT CDictionary::LoadLibrary(String filename)
{
	char *pFileName = new char[256];
	wcstombs(pFileName, filename, 256) ;

	FILE *fp;
	if( (fp = fopen( pFileName, "rt" )) == NULL ) {
		delete pFileName;
		return E_FAIL;
	}
	char LineBuffer[128];
	if (feof(fp)) {
		fclose(fp);
		delete pFileName;
		return E_FAIL+1;
	}
	if (fgets(LineBuffer, 128, fp) == NULL) {
		fclose(fp);
		delete pFileName;
		return E_FAIL+2;
	}
	
	int nTotalNumber = 0;
	sscanf(LineBuffer, "%d", &nTotalNumber);
	if ( (nTotalNumber < 1) && (nTotalNumber > 5000) ) {
		fclose(fp);
		delete pFileName;
		return E_FAIL+3;
	}

	Initialize();
	m_nStructNumber = nTotalNumber+100;
	m_pData = new DictWord[m_nStructNumber];
	m_nWordNumber = 0;
	
	while(!feof(fp)) {
		if (fgets(LineBuffer, MaxWordLength, fp) == NULL) {
			break;
		}
		sscanf(LineBuffer, "%s", m_pData[m_nWordNumber].wordForLang1);
		if (fgets(LineBuffer, MaxWordLength, fp) == NULL) {
			break;
		}
		sscanf(LineBuffer, "%s", m_pData[m_nWordNumber].wordForLang2);
		m_nWordNumber ++;
		if (m_nWordNumber == nTotalNumber)
			break;
		if (m_nWordNumber > m_nStructNumber)
			break;
	}	
	
	fclose(fp);
	delete pFileName;
	return S_OK;
}

HRESULT CDictionary::InsertWord(String word1, String word2)
{
	if (m_nWordNumber < m_nStructNumber) {
		char *pWord1 = new char[256];
		wcstombs(pWord1, word1, 256) ;
		char *pWord2 = new char[256];
		wcstombs(pWord2, word2, 256) ;
		
		if (strlen(pWord1) > MaxWordLength)
			*(pWord1+MaxWordLength-1) = '\0';
		if (strlen(pWord2) > MaxWordLength)
			*(pWord2+MaxWordLength-1) = '\0';
		strcpy(m_pData[m_nWordNumber].wordForLang1, pWord1);
		strcpy(m_pData[m_nWordNumber].wordForLang2, pWord2);
		m_nWordNumber ++ ;
		delete pWord1;
		delete pWord2;
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CDictionary::DeleteWord(String word)
{
	char *pWord = new char[256];
	wcstombs(pWord, word, 256) ;

	char *pUpperWord = strupr(pWord);
	for (int i = 0; i < m_nWordNumber; i++)
	{
		char *tmpWord = strupr(m_pData[i].wordForLang1);
		if (strcmp(tmpWord, pWord) == 0) {
			for(int j = i + 1; j < m_nWordNumber; j++) {
				strcpy( m_pData[j].wordForLang1, m_pData[j + 1].wordForLang1);
				strcpy( m_pData[j].wordForLang2, m_pData[j + 1].wordForLang2);
			}
			m_nWordNumber ++ ;
			break;
		}
	}
	delete pWord;
	return S_OK;
}

HRESULT CDictionary::LookupWord(String word, String resultWord)
{
	char *pWord = new char[32];
	wcstombs(pWord, word, 32) ;

	char *pUpperWord = strupr(pWord);
	for (int i = 0; i < m_nWordNumber; i++)
	{
		char *tmpWord = strupr(m_pData[i].wordForLang1);
		if (strcmp(tmpWord, pWord) == 0) {
			WCHAR *tmpWord = new WCHAR[32];
			mbstowcs(tmpWord, m_pData[i].wordForLang2, 32) ;
			wcscpy(resultWord, tmpWord);
			delete tmpWord;

			delete pWord;
			return S_OK;
		}
	}
	*resultWord = NULL;
	delete pWord;
	return E_FAIL;
}

HRESULT CDictionary::RestoreLibrary(String filename)
{
	char *pFileName = new char[32];
	wcstombs(pFileName, filename, 32) ;

	FILE *fp;
	if( (fp = fopen( pFileName, "wt" )) == NULL ) {
		printf("Open dictionary file : %s failed.\n", pFileName);
		delete pFileName;
		return E_FAIL;
	}
	char LineBuffer[128];
	sprintf(LineBuffer, "%d\n", m_nWordNumber);
	if (fputs(LineBuffer, fp) == EOF) {
		printf("Write TotalNumber failed!\n");
		fclose(fp);
		delete pFileName;
		return E_FAIL;
	}
	
	for(int i = 0; i < m_nWordNumber; i ++ ) {
		if (fputs(m_pData[i].wordForLang1, fp) == EOF) {
			printf("Write the first string failed!\n");
			fclose(fp);
			delete pFileName;
			return E_FAIL;
		}
		fputs("\n", fp);
		if (fputs(m_pData[i].wordForLang2, fp) == EOF) {
			printf("Write the first string failed!\n");
			fclose(fp);
			delete pFileName;
			return E_FAIL;
		}
		fputs("\n", fp);
	}
	
	fclose(fp);
	delete pFileName;
	return S_OK;
}

HRESULT CDictionary::FreeLibrary()
{
	Initialize();
	return S_OK;
}

	
HRESULT CDictionary::CheckWord (String word, String resultWord)
{
	char *pWord = new char[32];
	wcstombs(pWord, word, 32) ;

	char *pUpperWord = strupr(pWord);
	char *pMinMaxWord, *pMaxMinWord;
	int	 nMinIndex = -1, nMaxIndex = -1;
	pMinMaxWord = pMaxMinWord = NULL;
	for (int i = 0; i < m_nWordNumber; i++)
	{
		char *tmpWord = strupr(m_pData[i].wordForLang1);
		if (strcmp(tmpWord, pWord) == 0) {
			delete pWord;
			return S_OK;
		} else if (strcmp(tmpWord, pWord) < 0) {
			if ((pMinMaxWord == NULL) || (strcmp(tmpWord, pMinMaxWord) > 0)) 
			{
				pMinMaxWord = tmpWord;
				nMinIndex = i;
			}
		} else {
			if ((pMaxMinWord == NULL) || (strcmp(tmpWord, pMaxMinWord) < 0)) 
			{
				pMaxMinWord = tmpWord;
				nMaxIndex = i;
			}
		}
	}
	
	if (nMinIndex != -1) {
		WCHAR *tmpWord = new WCHAR[32];
		mbstowcs(tmpWord, m_pData[nMinIndex].wordForLang1, 32) ;
		wcscpy(resultWord, tmpWord);
		delete tmpWord;
	} else if (nMaxIndex != -1) {
		WCHAR *tmpWord = new WCHAR[32];
		mbstowcs(tmpWord, m_pData[nMaxIndex].wordForLang1, 32) ;
		wcscpy(resultWord, tmpWord);
		delete tmpWord;
	}
	delete pWord;
	return E_FAIL;
}