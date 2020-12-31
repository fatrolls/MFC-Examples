#ifndef _COLORIZE_
#define _COLORIZE_
#include "afxtempl.h"
class Colorize
{
public:
	BOOL cCaseSensitive;
	CStringList KeyWords;
	CStringList SmartWords;
	CStringList TabPlusWords;
	CStringList TabMinusWords;
	Colorize(CString &keywordsFile,BOOL caseSensitive);
	~Colorize();
	void SetLineColors(CString &pString, 
		CTypedPtrArray<CPtrArray, void*> &pColors); 
	BOOL IsWhiteSpace(char pTest);
	BOOL IsKeyWord(CString & pTest);
	BOOL IsSmartWord(CString & pTest);
	BOOL IsTabPlusWord(CString & pTest);
	BOOL IsTabMinusWord(CString & pTest);
	void LoadKeyWords(CString &keywordsFile);
};

#endif