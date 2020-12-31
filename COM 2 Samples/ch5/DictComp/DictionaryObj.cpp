// DictionaryObj.cpp : implementation file
//

#include "stdafx.h"
#include "DictComp.h"
#include <comutil.h>
#include "DictionaryObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDictionaryObj

IMPLEMENT_DYNCREATE(CDictionaryObj, CCmdTarget)

CDictionaryObj::CDictionaryObj()
{
	m_nWordNumber = 0;
	m_nStructNumber = 0;
	m_pData = NULL;
}

CDictionaryObj::~CDictionaryObj()
{
	if (m_pData != NULL) 
	{
		delete [] m_pData;
	}
}


BEGIN_MESSAGE_MAP(CDictionaryObj, CCmdTarget)
	//{{AFX_MSG_MAP(CDictionaryObj)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

extern "C" const IID IID_Dictionary = 
		{ 0x54bf6568, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;

extern "C" const IID IID_SpellCheck = 
		{ 0x54bf6569, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;

BEGIN_INTERFACE_MAP(CDictionaryObj, CCmdTarget)
	INTERFACE_PART(CDictionaryObj, IID_Dictionary, Dictionary)
	INTERFACE_PART(CDictionaryObj, IID_SpellCheck, SpellCheck)
END_INTERFACE_MAP()

// {54BF6567-1007-11D1-B0AA-444553540000}
IMPLEMENT_OLECREATE(CDictionaryObj, "Dictionary.Object", 
0x54bf6567, 0x1007, 0x11d1, 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00)

/////////////////////////////////////////////////////////////////////////////
// CDictionaryObj::XDictionary
STDMETHODIMP_(ULONG) CDictionaryObj::XDictionary::AddRef()
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, Dictionary)
	return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDictionaryObj::XDictionary::Release()
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, Dictionary)
	return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CDictionaryObj::XDictionary::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, Dictionary)
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(BOOL) CDictionaryObj::XDictionary::Initialize()
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, Dictionary)
	pThis->m_nWordNumber = 0;
	pThis->m_nStructNumber = 0;
	if (pThis->m_pData != NULL) 
	{
		delete [] pThis->m_pData;
	}
	pThis->m_pData = NULL;
	return TRUE;
}

STDMETHODIMP_(BOOL) CDictionaryObj::XDictionary::LoadLibrary(LPOLESTR filename)
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, Dictionary)

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
	pThis->m_nStructNumber = nTotalNumber+100;
	pThis->m_pData = new DictWord[pThis->m_nStructNumber];
	pThis->m_nWordNumber = 0;
	
	while(!feof(fp)) {
		if (fgets(LineBuffer, MaxWordLength, fp) == NULL) {
			printf("Read the first string failed!\n");
			break;
		}
		sscanf(LineBuffer, "%s", pThis->m_pData[pThis->m_nWordNumber].wordForLang1);
		if (fgets(LineBuffer, MaxWordLength, fp) == NULL) {
			printf("Read the second string failed!\n");
			break;
		}
		sscanf(LineBuffer, "%s", pThis->m_pData[pThis->m_nWordNumber].wordForLang2);
		pThis->m_nWordNumber ++;
		if (pThis->m_nWordNumber == nTotalNumber)
			break;
		if (pThis->m_nWordNumber > pThis->m_nStructNumber)
			break;
	}	
	
	fclose(fp);
	delete pFileName;
	return TRUE;
}

STDMETHODIMP_(BOOL) CDictionaryObj::XDictionary::InsertWord(LPOLESTR word1, LPOLESTR word2)
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, Dictionary)
	char *pWord1, *pWord2;
	if (pThis->m_nWordNumber < pThis->m_nStructNumber) {
		pWord1 = _com_util::ConvertBSTRToString(word1);
		pWord2 = _com_util::ConvertBSTRToString(word2);

		if (strlen(pWord1) > MaxWordLength)
			*(pWord1+MaxWordLength-1) = '\0';
		if (strlen(pWord2) > MaxWordLength)
			*(pWord2+MaxWordLength-1) = '\0';
		strcpy(pThis->m_pData[pThis->m_nWordNumber].wordForLang1, pWord1);
		strcpy(pThis->m_pData[pThis->m_nWordNumber].wordForLang2, pWord2);
		pThis->m_nWordNumber ++ ;
		delete pWord1;
		delete pWord2;
		return TRUE;
	}
	return FALSE;
}

STDMETHODIMP_(void) CDictionaryObj::XDictionary::DeleteWord(LPOLESTR word)
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, Dictionary)
	char *pWord = _com_util::ConvertBSTRToString(word);
	char *pUpperWord = strupr(pWord);
	for (int i = 0; i < pThis->m_nWordNumber; i++)
	{
		char *tmpWord = strupr(pThis->m_pData[i].wordForLang1);
		if (strcmp(tmpWord, pWord) == 0) {
			for(int j = i + 1; j < pThis->m_nWordNumber; j++) {
				strcpy( pThis->m_pData[j].wordForLang1, pThis->m_pData[j + 1].wordForLang1);
				strcpy( pThis->m_pData[j].wordForLang2, pThis->m_pData[j + 1].wordForLang2);
			}
			pThis->m_nWordNumber ++ ;
			break;
		}
	}
	delete pWord;
}

STDMETHODIMP_(BOOL) CDictionaryObj::XDictionary::LookupWord(LPOLESTR word, LPOLESTR *resultWord)
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, Dictionary)
	char *pWord = _com_util::ConvertBSTRToString(word);
	char *pUpperWord = strupr(pWord);
	for (int i = 0; i < pThis->m_nWordNumber; i++)
	{
		char *tmpWord = strupr(pThis->m_pData[i].wordForLang1);
		if (strcmp(tmpWord, pWord) == 0) {
			*resultWord = _com_util::ConvertStringToBSTR(pThis->m_pData[i].wordForLang2);
			delete pWord;
			return TRUE;
		}
	}
	*resultWord = NULL;
	delete pWord;
	return FALSE;
}

STDMETHODIMP_(BOOL) CDictionaryObj::XDictionary::RestoreLibrary(LPOLESTR filename)
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, Dictionary)
	char *pFileName = _com_util::ConvertBSTRToString(filename);
	FILE *fp;
	if( (fp = fopen( pFileName, "wt" )) == NULL ) {
		printf("Open dictionary file : %s failed.\n", pFileName);
		delete pFileName;
		return FALSE;
	}
	char LineBuffer[128];
	sprintf(LineBuffer, "%d\n", pThis->m_nWordNumber);
	if (fputs(LineBuffer, fp) == EOF) {
		printf("Write TotalNumber failed!\n");
		fclose(fp);
		delete pFileName;
		return FALSE; 
	}
	
	for(int i = 0; i < pThis->m_nWordNumber; i ++ ) {
		if (fputs(pThis->m_pData[i].wordForLang1, fp) == EOF) {
			printf("Write the first string failed!\n");
			fclose(fp);
			delete pFileName;
			return FALSE; 
		}
		fputs("\n", fp);
		if (fputs(pThis->m_pData[i].wordForLang2, fp) == EOF) {
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

STDMETHODIMP_(void) CDictionaryObj::XDictionary::FreeLibrary()
{
	Initialize();
}

	
/////////////////////////////////////////////////////////////////////////////
// CDictionaryObj::XSpellCheck
STDMETHODIMP_(ULONG) CDictionaryObj::XSpellCheck::AddRef()
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, SpellCheck)
	return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDictionaryObj::XSpellCheck::Release()
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, SpellCheck)
	return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CDictionaryObj::XSpellCheck::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, SpellCheck)
	return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(BOOL) CDictionaryObj::XSpellCheck::CheckWord (LPOLESTR word, LPOLESTR *resultWord)
{
	METHOD_PROLOGUE_EX_(CDictionaryObj, SpellCheck)
	char *pWord = _com_util::ConvertBSTRToString(word);
	char *pUpperWord = strupr(pWord);
	char *pMinMaxWord, *pMaxMinWord;
	int	 nMinIndex = -1, nMaxIndex = -1;
	pMinMaxWord = pMaxMinWord = NULL;
	for (int i = 0; i < pThis->m_nWordNumber; i++)
	{
		char *tmpWord = strupr(pThis->m_pData[i].wordForLang1);
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
		*resultWord = _com_util::ConvertStringToBSTR(pThis->m_pData[nMinIndex].wordForLang1);
	else if (nMaxIndex != -1)
		*resultWord = _com_util::ConvertStringToBSTR(pThis->m_pData[nMaxIndex].wordForLang1);
	delete pWord;
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CDictionaryObj message handlers
