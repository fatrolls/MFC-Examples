// ColorEditView.cpp : implementation of the Colorize class
//

#include "stdafx.h"
#include "Colorize.h"


#define COMMENT_COLOR RGB(0,200,0)
#define KEYWORD_COLOR RGB(0,40,250)
#define USER_COLOR RGB(220,0,40)
#define NORMAL_COLOR RGB(0,0,0)



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BOOL AUTO_TAB = TRUE;


Colorize::Colorize(CString &keywordsFile, BOOL caseSensitive)
{
	cCaseSensitive = caseSensitive;
	LoadKeyWords(keywordsFile);
}

Colorize::~Colorize()
{
}


void Colorize::SetLineColors(CString &pString, 
	CTypedPtrArray<CPtrArray, void*> &pColors) 
{
	CString word;
	long i,j,k,l,s,e;
	BOOL remline;

	//test for a remark line
	word = pString;
	word.TrimLeft();
	word.TrimRight();
	word = word.Left(3);
	if(word.CompareNoCase("REM") == 0)
	{
		//set the line to all comment color
		for(i=0; i<pString.GetLength(); i++)
		{
			pColors.SetAtGrow(i, (void*)(COMMENT_COLOR));
		}
		//make sure "REM" is all caps
		for(i=0; i<pString.GetLength(); i++)
		{
			if((pString.GetAt(i) == 'r')
				|| (pString.GetAt(i) == 'R'))
			{
				pString.SetAt(i,'R');
				pString.SetAt(i+1,'E');
				pString.SetAt(i+2,'M');
				break;
			}
		}
		j = pString.GetLength();
	}
	else
	{
		//set the line to all black
		k = 0;
		j = pString.GetLength();
		for(i=0; i<j; i++)
		{
			pColors.SetAtGrow(i,(void*)(NORMAL_COLOR));
		}
		while(k<j)
		{
			word.Empty();
			while((k<j) && (IsWhiteSpace(pString.GetAt(k))))
			{
				k++;
			}
			s = k;
			while((k<j) && (!IsWhiteSpace(pString.GetAt(k))))
			{
				word = word + pString.GetAt(k);
				k++;
			}
			e = k;
			word.TrimLeft();
			word.TrimRight();
			if(IsKeyWord(word))
			{
				l = 0;
				for(i=s; i<e; i++)
				{
					pString.SetAt(i,word.GetAt(l));
					l++;
					pColors[i] = (void*)(KEYWORD_COLOR);
				}
			}
			else if(IsSmartWord(word))
			{
				l = 0;
				for(i=s; i<e; i++)
				{
					pString.SetAt(i,word.GetAt(l));
					l++;
					pColors[i] = (void*)(USER_COLOR);
				}
			}
		}
	}

	//count up the number of single quote characters to see if
	//the tail end of the line is a comment line
	remline = FALSE;
	for(i=0; i<j; i++)
	{
		if(pString.GetAt(i) == 39)
		{
			remline = !remline;
			l = i;
		}
	}
	if(remline)
	{
		for(i=l; i<j; i++)
		{
			pColors.SetAtGrow(i,(void*)(COMMENT_COLOR));
		}
	}
}

BOOL Colorize::IsWhiteSpace(char pTest)
{
	if(pTest < 65) return TRUE;
	return FALSE;
}

BOOL Colorize::IsKeyWord(CString & pTest)
{
	POSITION p;
	CString key;
	p = KeyWords.GetHeadPosition();
	while(p)
	{
		key = KeyWords.GetNext(p);
		if(cCaseSensitive)
		{
			if(pTest.Compare(key) == 0)
			{
				pTest = key;
				return TRUE;
			}
		}
		else
		{
			if(pTest.CompareNoCase(key) == 0)
			{
				pTest = key;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL Colorize::IsSmartWord(CString & pTest)
{
	POSITION p;
	CString key;
	p = SmartWords.GetHeadPosition();
	while(p)
	{
		key = SmartWords.GetNext(p);
		if(cCaseSensitive)
		{
			if(pTest.Compare(key) == 0)
			{
				pTest = key;
				return TRUE;
			}
		}
		else
		{
			if(pTest.CompareNoCase(key) == 0)
			{
				pTest = key;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL Colorize::IsTabPlusWord(CString & pTest)
{
	POSITION p;
	CString key;
	p = TabPlusWords.GetHeadPosition();
	while(p)
	{
		key = TabPlusWords.GetNext(p);
		if(cCaseSensitive)
		{
			if(pTest.Compare(key) == 0)
			{
				pTest = key;
				return TRUE;
			}
		}
		else
		{
			if(pTest.CompareNoCase(key) == 0)
			{
				pTest = key;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL Colorize::IsTabMinusWord(CString & pTest)
{
	POSITION p;
	CString key;
	p = TabMinusWords.GetHeadPosition();
	while(p)
	{
		key = TabMinusWords.GetNext(p);
		if(cCaseSensitive)
		{
			if(pTest.Compare(key) == 0)
			{
				pTest = key;
				return TRUE;
			}
		}
		else
		{
			if(pTest.CompareNoCase(key) == 0)
			{
				pTest = key;
				return TRUE;
			}
		}
	}
	return FALSE;
}

void Colorize::LoadKeyWords(CString &keywordsFile)
{
	FILE * infile;
	char buffer[512];
	CString inifile = keywordsFile;
	if(infile = fopen(inifile,"rb"))
	{
		while(!feof(infile))
		{
			fscanf(infile,"%s",buffer);
			if(buffer[0] == '+') //tab plus keyword
			{
				TabPlusWords.AddTail(buffer+1);
			}
			else if(buffer[0] == '-') //tab minus keyword
			{
				TabMinusWords.AddTail(buffer+1);
			}
			else if(buffer[0] == '&') //smartedit keyword
			{
				SmartWords.AddTail(buffer+1);
			}
			else //visual basic keyword
			{
				KeyWords.AddTail(buffer);
			}
		}
		fclose(infile);
	}
}

