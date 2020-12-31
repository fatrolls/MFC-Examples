#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Splits a string into array elements WRT the separater character
//////////////////////////////////////////////////////////////////////

void SplitStringEx(LPTSTR lpszInputString, 
				   LPCTSTR lpszDelimiters, 
				   CStringArray *csElementArray)
{
	char* pcToken;
	LPTSTR lpszInput;

	lpszInput = new char[strlen(lpszInputString)+1];

	lstrcpy(lpszInput, lpszInputString);

	pcToken = strtok(lpszInput,lpszDelimiters);

	while(pcToken != NULL)
	{
		csElementArray->Add(pcToken);
		pcToken = strtok(NULL,lpszDelimiters);
	}

	delete lpszInput; 
}

void TrimStringEx(CString &csInputString, 
				  LPCTSTR lpszLeftTarget /*=" "*/, 
				  LPCTSTR lpszRightTarget /*=" "*/, 
				  UINT nFlags /*=0*/)
{
/*	switch(nFlags)
	{
	case TRIM_LEFT:
		csInputString.TrimLeft(lpszLeftTarget);
		break;
	case TRIM_RIGHT:
		csInputString.TrimRight(lpszRightTarget);
		break;
	case TRIM_BOTH:
	default:
		csInputString.TrimLeft(lpszLeftTarget);
		csInputString.TrimRight(lpszRightTarget);
		break;
	}*/
}

BOOL IsEqualStringEx(LPCTSTR lpszInputString,
					 LPCTSTR lpszComparisonString)
{
	BOOL bRet = FALSE;

	if(lstrcmp(lpszInputString,lpszComparisonString) == 0)
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL IsEqualStringEx(char cInputChar,
					 LPCTSTR lpszComparisonString)
{
	BOOL bRet = FALSE;
	CString csTemp = cInputChar;

	bRet = IsEqualStringEx((LPCTSTR)csTemp,lpszComparisonString);

	return bRet;
}