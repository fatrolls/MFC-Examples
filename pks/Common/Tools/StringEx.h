#ifndef __STRINGEX_H

#define __STRINGEX_H


//////////////////////////////////////////////////////////////////////
// Splits a string into array elements WRT the separater character
//////////////////////////////////////////////////////////////////////

void SplitStringEx(LPTSTR lpszInputString, 
				   LPCTSTR lpszDelimiters, 
				   CStringArray *csElementArray);

void TrimStringEx(CString &csInputString, 
				  LPCTSTR lpszLeftTarget=" ", 
				  LPCTSTR lpszRightTarget=" ", 
				  UINT nFlags=0);

BOOL IsEqualStringEx(LPCTSTR lpszInputString,
			   LPCTSTR lpszComparisonString);

BOOL IsEqualStringEx(char cInputChar,
					 LPCTSTR lpszComparisonString);

#endif
