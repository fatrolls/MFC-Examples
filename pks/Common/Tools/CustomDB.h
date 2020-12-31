// CustomDB.h: interface for the CCustomDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMDB_H__FD1B7D7B_250E_4D49_BF46_44C78AE27CA6__INCLUDED_)
#define AFX_CUSTOMDB_H__FD1B7D7B_250E_4D49_BF46_44C78AE27CA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#import <msado15.dll> no_namespace rename( "EOF", "adoEOF" )

#include <comdef.h>

#define QUERY_MODE_NORMAL			1
#define QUERY_MODE_ADVANCE			2

class CCustomDB  
{
	_ConnectionPtr m_pConnection;

	CString m_csErrorMessage;

public:

	BOOL Select(LPCTSTR lpszTableName,CStringArray *pcsaValues,int nFieldCount,LPTSTR lpszFields,LPCTSTR lpszCondition=NULL,int nMode = QUERY_MODE_NORMAL,LPCTSTR lpszQueryEx = NULL);
	BOOL Update(LPCTSTR lpszTableName,LPTSTR lpszFields,LPTSTR lpszValues,LPCTSTR lpszCondition =NULL,int nMode = QUERY_MODE_NORMAL,LPCTSTR lpszQueryEx = NULL);
	BOOL Delete(LPCTSTR lpszTableName,LPCTSTR lpszCondition =NULL);
	BOOL Insert(LPCTSTR lpszTableName,LPCTSTR lpszFields,LPCTSTR lpszValues);
	BOOL CreateConnection(LPCTSTR lpszProvider,LPCTSTR lpszDataSource,LPCTSTR lpszUserName=NULL,LPCTSTR lpszPasswd=NULL);
	LPCTSTR GetErrorMessage();
	CCustomDB();
	virtual ~CCustomDB();
};

#endif // !defined(AFX_CUSTOMDB_H__FD1B7D7B_250E_4D49_BF46_44C78AE27CA6__INCLUDED_)
