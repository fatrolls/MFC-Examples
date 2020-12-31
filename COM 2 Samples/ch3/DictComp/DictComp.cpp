// DictComp.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <comutil.h>
#include <stdio.h>
#include "objbase.h"
#include "olectl.h"

#include "DictComp.h"
#include "factory.h"
#include "registry.h"

ULONG    g_LockNumber = 0;
ULONG    g_DictionaryNumber = 0;
HANDLE	 g_hModule;

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



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    g_hModule = hModule;
	return TRUE;
}


extern "C" HRESULT __stdcall DllGetClassObject(const CLSID& clsid, const IID& iid, void **ppv)
{
	if (clsid == CLSID_Dictionary ) {
		
		CDictionaryFactory *pFactory = new CDictionaryFactory;
		
		if (pFactory == NULL) {
			return E_OUTOFMEMORY ;
		}
		
		HRESULT result = pFactory->QueryInterface(iid, ppv);

		return result;
	} else {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((g_DictionaryNumber == 0) && (g_LockNumber == 0))
		return S_OK;
	else
		return S_FALSE;
}

//
// Server registration
//
extern "C" HRESULT __stdcall DllRegisterServer()
{
	char szModule[1024];
	DWORD dwResult = ::GetModuleFileName((HMODULE)g_hModule, szModule, 1024);
	if (dwResult == 0)
		return SELFREG_E_CLASS;
	return RegisterServer(CLSID_Dictionary,
	                      szModule, 
						  "Dictionary.Object",
						  "Dictionary Component",
						  NULL);
}


//
// Server unregistration
//
extern "C" HRESULT __stdcall DllUnregisterServer()
{
	return UnregisterServer(CLSID_Dictionary,
	                        "Dictionary.Object",NULL);
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

BOOL CDictionary::Initialize()
{
	m_nWordNumber = 0;
	m_nStructNumber = 0;
	if (m_pData != NULL) 
	{
		delete [] m_pData;
	}
	m_pData = NULL;
	return TRUE;
}

BOOL CDictionary::LoadLibrary(String filename)
{
	char *pFileName = _com_util::ConvertBSTRToString(filename);
	FILE *fp;
	if( (fp = fopen( pFileName, "rt" )) == NULL ) {
		printf("Open dictionary file : %s failed.\n", pFileName);
		delete pFileName;
		return FALSE;
	}
	char LineBuffer[128];
	if (feof(fp)) {
		printf("It is a null file!\n");
		fclose(fp);
		delete pFileName;
		return FALSE; 
	}
	if (fgets(LineBuffer, 128, fp) == NULL) {
		printf("Read TotalNumber failed!\n");
		fclose(fp);
		delete pFileName;
		return FALSE; 
	}
	
	int nTotalNumber = 0;
	sscanf(LineBuffer, "%d", &nTotalNumber);
	if ( (nTotalNumber < 1) && (nTotalNumber > 5000) ) {
		printf("The Number of words is invalid!\n");
		fclose(fp);
		delete pFileName;
		return FALSE; 
	}

	Initialize();
	m_nStructNumber = nTotalNumber+100;
	m_pData = new DictWord[m_nStructNumber];
	m_nWordNumber = 0;
	
	while(!feof(fp)) {
		if (fgets(LineBuffer, MaxWordLength, fp) == NULL) {
			printf("Read the first string failed!\n");
			break;
		}
		sscanf(LineBuffer, "%s", m_pData[m_nWordNumber].wordForLang1);
		if (fgets(LineBuffer, MaxWordLength, fp) == NULL) {
			printf("Read the second string failed!\n");
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
	return TRUE;
}

BOOL CDictionary::InsertWord(String word1, String word2)
{
	char *pWord1, *pWord2;
	if (m_nWordNumber < m_nStructNumber) {
		pWord1 = _com_util::ConvertBSTRToString(word1);
		pWord2 = _com_util::ConvertBSTRToString(word2);

		if (strlen(pWord1) > MaxWordLength)
			*(pWord1+MaxWordLength-1) = '\0';
		if (strlen(pWord2) > MaxWordLength)
			*(pWord2+MaxWordLength-1) = '\0';
		strcpy(m_pData[m_nWordNumber].wordForLang1, pWord1);
		strcpy(m_pData[m_nWordNumber].wordForLang2, pWord2);
		m_nWordNumber ++ ;
		delete pWord1;
		delete pWord2;
		return TRUE;
	}
	return FALSE;
}

void CDictionary::DeleteWord(String word)
{
	char *pWord = _com_util::ConvertBSTRToString(word);
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
}

BOOL CDictionary::LookupWord(String word, String *resultWord)
{
	char *pWord = _com_util::ConvertBSTRToString(word);
	char *pUpperWord = strupr(pWord);
	for (int i = 0; i < m_nWordNumber; i++)
	{
		char *tmpWord = strupr(m_pData[i].wordForLang1);
		if (strcmp(tmpWord, pWord) == 0) {
			*resultWord = _com_util::ConvertStringToBSTR(m_pData[i].wordForLang2);
			delete pWord;
			return TRUE;
		}
	}
	*resultWord = NULL;
	delete pWord;
	return FALSE;
}

BOOL CDictionary::RestoreLibrary(String filename)
{
	char *pFileName = _com_util::ConvertBSTRToString(filename);
	FILE *fp;
	if( (fp = fopen( pFileName, "wt" )) == NULL ) {
		printf("Open dictionary file : %s failed.\n", pFileName);
		delete pFileName;
		return FALSE;
	}
	char LineBuffer[128];
	sprintf(LineBuffer, "%d\n", m_nWordNumber);
	if (fputs(LineBuffer, fp) == EOF) {
		printf("Write TotalNumber failed!\n");
		fclose(fp);
		delete pFileName;
		return FALSE; 
	}
	
	for(int i = 0; i < m_nWordNumber; i ++ ) {
		if (fputs(m_pData[i].wordForLang1, fp) == EOF) {
			printf("Write the first string failed!\n");
			fclose(fp);
			delete pFileName;
			return FALSE; 
		}
		fputs("\n", fp);
		if (fputs(m_pData[i].wordForLang2, fp) == EOF) {
			printf("Write the first string failed!\n");
			fclose(fp);
			delete pFileName;
			return FALSE; 
		}
		fputs("\n", fp);
	}
	
	fclose(fp);
	delete pFileName;
	return TRUE;
}

void CDictionary::FreeLibrary()
{
	Initialize();
}

	
BOOL CDictionary::CheckWord (String word, String *resultWord)
{
	char *pWord = _com_util::ConvertBSTRToString(word);
	char *pUpperWord = strupr(pWord);
	char *pMinMaxWord, *pMaxMinWord;
	int	 nMinIndex = -1, nMaxIndex = -1;
	pMinMaxWord = pMaxMinWord = NULL;
	for (int i = 0; i < m_nWordNumber; i++)
	{
		char *tmpWord = strupr(m_pData[i].wordForLang1);
		if (strcmp(tmpWord, pWord) == 0) {
			delete pWord;
			return TRUE;
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
	
	*resultWord = NULL;
	if (nMinIndex != -1)
		*resultWord = _com_util::ConvertStringToBSTR(m_pData[nMinIndex].wordForLang1);
	else if (nMaxIndex != -1)
		*resultWord = _com_util::ConvertStringToBSTR(m_pData[nMaxIndex].wordForLang1);
	delete pWord;
	return FALSE;
}