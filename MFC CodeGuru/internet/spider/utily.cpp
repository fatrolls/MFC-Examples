
// Utily.cpp : implementation 
//
/****************************************************************
Pre-emptive Multithreading Web Spider
Copyright (c) 1998 by Sim Ayers.
**************************************************************/

#include "stdafx.h"
#include "Spider.h"
#include <string.h>
#include "utily.h"


BOOL FindHref(LPCTSTR lpszFind,LPCTSTR lpszString,CString& lpszResult,UINT nLen)
{
	// start the search at nStart
	LPCTSTR lpsz = lpszFind;

		// single-byte string search
		UINT nCompare = nLen;
	int k=0;
	int nLenFind = lstrlen(lpszString);
	lpszResult ="";
		while (nCompare > 0)
		{

			LPSTR lpch = (LPSTR)(lpsz + nLenFind);
			char chSave = *lpch;
			*lpch = '\0';
			int nResult = lstrcmpi(lpsz, lpszString);
			*lpch = chSave;
			if (nResult == 0)
			{
				while(*lpsz != '\0')
				{
					if(*lpsz =='"')
					{
						lpsz++;	
						k++;
						int j=0;
						while(*lpsz != '"')
						{
							lpszResult += lpszFind[k+j];
							lpsz++;	
							j++;

						}
				

						return TRUE;

					}
					lpsz++;	
					k++;
				}

				return TRUE;
			}

			// restore character at end of search
			*lpch = chSave;

			// move on to next substring
			nCompare--;
			lpsz ++;
			k++;
		}

	return FALSE;
}



BOOL GetHref(LPCSTR szBuffer,LPCSTR szfind, CStringList& list)

{			
	BOOL InTag=FALSE;
	CStringList RList;
	int i = 0,j=0;
	POSITION pos = NULL;
	int nLen = strlen(szBuffer);
	LPCTSTR lpsz = szBuffer;
	if( nLen <= 0) return FALSE;

	CString str,hString;
	str="";
	while (nLen)
	{
		if( *lpsz == '<')	InTag=TRUE;
	
		if(InTag==TRUE)		str += szBuffer[j];
		
		if( *lpsz == '>')  
		{
			RList.AddTail(str);
			str ="";
			InTag=FALSE;
		}
	
		++lpsz;
		j++;
		nLen--;
		
	}

	int count = RList.GetCount();
	char* pdest;

	for(i=0; i<count; i++)
	{
		if( ( pos = RList.FindIndex( i)) != NULL )
		{
			str = RList.GetAt( pos );
			
			pdest = strstr( str, _T("NOINDEX")); //for robot exclusion
			if( pdest != NULL )	return FALSE;

			pdest = strstr( str, _T("noindex"));
			if( pdest != NULL )	return FALSE;

			if(FindHref((LPCTSTR) str,szfind,hString,str.GetLength()))
			{
			pdest = strstr( hString, _T("mailto:"));
			if( pdest == NULL )	list.AddTail(hString);
			}
			else
			{
				if(FindHref((LPCTSTR) str,_T("option"),hString,str.GetLength()))
				{
				pdest = strstr( hString, _T("http"));
				if( pdest != NULL )	list.AddTail(hString);
				}
			}

		}
	}

	count = list.GetCount();
	if(count>0) return TRUE;

	return FALSE;
}

BOOL GetEmail(LPCSTR szBuffer,LPCSTR szfind, CStringList& list)

{			
	BOOL InTag=FALSE;
	CStringList RList;
	int i = 0,j=0;
	POSITION pos = NULL;
	int nLen = strlen(szBuffer);
	LPCTSTR lpsz = szBuffer;
	if( nLen <= 0) return FALSE;

	CString str,hString;
	str="";
	while (nLen)
	{
		if( *lpsz == '<')	InTag=TRUE;
	
		if(InTag==TRUE)		str += szBuffer[j];
		
		if( *lpsz == '>')  
		{
			RList.AddTail(str);
			str ="";
			InTag=FALSE;
		}
	
		++lpsz;
		j++;
		nLen--;
		
	}

	int count = RList.GetCount();
	char* pdest;
	int p;
	for(i=0; i<count; i++)
	{
		if( ( pos = RList.FindIndex( i)) != NULL )
		{
			str = RList.GetAt( pos );
			
			pdest = strstr( str, _T("NOINDEX")); //for robot exclusion
			if( pdest != NULL )	return FALSE;

			pdest = strstr( str, _T("noindex"));
			if( pdest != NULL )	return FALSE;

			if(FindHref((LPCTSTR) str,szfind,hString,str.GetLength()))
			{
				pdest = strstr( hString, _T("mailto:"));
				if( pdest != NULL )
				{
					p = hString.Find("mailto:");
					if(p >= 0)
					{
						str = hString.Mid(p+7);
						list.AddTail(str);
					}
				}
			}


		}
	}

	count = list.GetCount();
	if(count>0) return TRUE;

	return FALSE;
}

BOOL GetHTMLTags(LPCSTR szBuffer, CStringList& list)

{			
	BOOL InTag=FALSE;
	int j=0;
	int nLen = strlen(szBuffer);
	LPCTSTR lpsz = szBuffer;
	if( nLen <= 0) return FALSE;

	CString str;
	str="";
	while (nLen)
	{
		if( *lpsz == '<')	InTag=TRUE;
	
		if(InTag==TRUE  )	str += szBuffer[j];
		
		if( *lpsz == '>')  
		{
			list.AddTail(str);
			str ="";
			InTag=FALSE;
		}
	
		++lpsz;
		j++;
		nLen--;
		
	}


	int count = list.GetCount();
	if(count>0) return TRUE;

	return FALSE;
}

BOOL GetHTMLText(LPCSTR szBuffer, CStringList& list)

{			
	BOOL InTag=FALSE;
	int j=0;
	int nLen = strlen(szBuffer);
	LPCTSTR lpsz = szBuffer;
	if( nLen <= 0) return FALSE;

	CString str;
	str="";
	while (nLen)
	{
		if( *lpsz == '<')	InTag=FALSE;
	
		if(InTag==TRUE  && *lpsz != '>')		str += szBuffer[j];
		
		if( *lpsz == '>')  
		{
			list.AddTail(str);
			str ="";

			InTag=TRUE;
		}
	
		++lpsz;
		j++;
		nLen--;
		
	}


	int count = list.GetCount();
	if(count>0) return TRUE;

	return FALSE;

}

