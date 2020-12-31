// CustomDB.cpp: implementation of the CCustomDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomDB.h"
#include "StringEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CCustomDB::CCustomDB()
{
	m_csErrorMessage = "Success";
}

CCustomDB::~CCustomDB()
{
	if (m_pConnection != 0 && m_pConnection->State != adStateClosed)
	{
		m_pConnection->Close();	
	}

	CoUninitialize();
}

BOOL CCustomDB::CreateConnection(LPCTSTR lpszProvider, LPCTSTR lpszDataSource, LPCTSTR lpszUserName, LPCTSTR lpszPasswd)
{
	TCHAR szBuf[1024];
	HRESULT hResult;
	
	if(FAILED(CoInitialize(NULL)))
	{
		m_csErrorMessage = "Error in COM Initialization";
		return FALSE;
	}

	hResult = m_pConnection.CreateInstance(__uuidof(Connection)); 

	if(FAILED(hResult))
	{
		 m_csErrorMessage = "Error in Connection creation";
		 return FALSE;
	}

	wsprintf(szBuf,"%s%s%s%s%s","Provider =",lpszProvider,";Data Source =",lpszDataSource,";Persist Security Info=false;");
	
	_bstr_t bstrConnectionStr(szBuf);

	hResult = m_pConnection->Open(bstrConnectionStr,_bstr_t(lpszUserName),_bstr_t(lpszPasswd),adConnectUnspecified); 

	if(FAILED(hResult))
	{
		m_csErrorMessage = "Error in Opening Database Connection";
		return FALSE;
	}

	return TRUE;
}

LPCTSTR CCustomDB::GetErrorMessage()
{
	return (LPCTSTR)m_csErrorMessage; 
}

BOOL CCustomDB::Insert(LPCTSTR lpszTableName, LPCTSTR lpszFields, LPCTSTR lpszValues)
{
	TCHAR szBuf[1024];
	_variant_t vRecsAffected(0L);

	wsprintf(szBuf,"%s %s %s %s %s %s %s %s","INSERT INTO ",lpszTableName," (",lpszFields,")"," VALUES (",lpszValues,")");

	TRACE("SQL Statement: %s \n",szBuf);

	_bstr_t bstrCommand(szBuf);

	try
	{
		m_pConnection->Execute(bstrCommand,&vRecsAffected,adCmdText|adExecuteNoRecords); 
	}
	catch(_com_error &Error)
	{
		wsprintf(szBuf,"%s%s  %s%s  %s%s","Source :",(LPCTSTR)Error.Source(),"ErrorMessage :",(LPCTSTR)Error.ErrorMessage(),"Description :",(LPCTSTR)Error.Description());   
		m_csErrorMessage = szBuf; 
		return FALSE;
	}

	return TRUE;
}

BOOL CCustomDB::Delete(LPCTSTR lpszTableName, LPCTSTR lpszCondition)
{
	TCHAR szBuf[1024];
	_variant_t	vRecsAffected(0L);
	
	CString csCheck(lpszCondition);

	if (lpszCondition != NULL)
	{
		if(csCheck.Left(5).CollateNoCase("WHERE") == 0)
		{
			wsprintf(szBuf,"%s %s %s","DELETE * FROM ",lpszTableName,lpszCondition);
		}
		else
		{
			wsprintf(szBuf,"%s %s %s %s","DELETE * FROM ",lpszTableName," WHERE ",lpszCondition);
		}
	}
	else
	{
		wsprintf(szBuf,"%s %s","DELETE * FROM ",lpszTableName);
	}

	TRACE("SQL Statement: %s \n",szBuf);

	_bstr_t bstrCommand(szBuf);

	try
	{
		m_pConnection->Execute(bstrCommand,&vRecsAffected,adCmdText|adExecuteNoRecords); 
	}
	catch(_com_error &Error)
	{
		wsprintf(szBuf,"%s%s  %s%s  %s%s","Source :",(LPCTSTR)Error.Source(),"ErrorMessage :",(LPCTSTR)Error.ErrorMessage(),"Description :",(LPCTSTR)Error.Description());   
		m_csErrorMessage = szBuf; 
		return FALSE;
	}

	return TRUE;
}

BOOL CCustomDB::Update(LPCTSTR lpszTableName, LPTSTR lpszFields, LPTSTR lpszValues, LPCTSTR lpszCondition, int nMode, LPCTSTR lpszQueryEx)
{
	TCHAR szBuf[1024];
	_variant_t vRecsAffected(0L);

	CString csSetValues;

	if (nMode == QUERY_MODE_NORMAL)
	{
		CStringArray csFieldArray;
		CStringArray csValueArray;

		SplitStringEx(lpszFields,LPCTSTR(","),&csFieldArray);
		SplitStringEx(lpszValues,LPCTSTR(","),&csValueArray);

		for(int nLoop=0; nLoop<csFieldArray.GetSize(); nLoop++)
		{
			csSetValues += csFieldArray.GetAt(nLoop);
			csSetValues += " = ";
			csSetValues += csValueArray.GetAt(nLoop);

			if(nLoop < csFieldArray.GetSize()-1)
			{
				csSetValues += " , ";
			}
		}
	}
	else
	{
		csSetValues = lpszQueryEx;
	}
	
	CString csCheck(lpszCondition);
	
	if(csCheck.Left(5).CollateNoCase("WHERE") == 0)
	{
		wsprintf(szBuf,"%s %s %s %s %s","UPDATE ",lpszTableName," SET ",csSetValues,lpszCondition);
	}
	else
	{
		wsprintf(szBuf,"%s %s %s %s %s %s","UPDATE ",lpszTableName," SET ",csSetValues," WHERE ",lpszCondition);
	}

	TRACE("SQL Statement: %s \n",szBuf);

	_bstr_t bstrCommand(szBuf);

	try
	{
		m_pConnection->Execute(bstrCommand,&vRecsAffected,adCmdText|adExecuteNoRecords); 
	}
	catch(_com_error &Error)
	{
		wsprintf(szBuf,"%s%s  %s%s  %s%s","Source :",(LPCTSTR)Error.Source(),"ErrorMessage :",(LPCTSTR)Error.ErrorMessage(),"Description :",(LPCTSTR)Error.Description());   
		m_csErrorMessage = szBuf; 
		return FALSE;
	}

	return TRUE;
}

BOOL CCustomDB::Select(LPCTSTR lpszTableName,CStringArray *pcsValueArray,int nFieldCount,LPTSTR lpszFields,LPCTSTR lpszCondition,int nMode,LPCTSTR lpszQueryEx)
{
	TCHAR szBuf[1024];
	_variant_t	vRecsAffected(0L);
	_RecordsetPtr pRecordset(__uuidof(Recordset));
	
	if (nMode == QUERY_MODE_NORMAL)
	{
		wsprintf(szBuf,"%s %s %s %s %s","SELECT",lpszFields,"FROM",lpszTableName,lpszCondition);
	}
	else
	{
		wsprintf(szBuf,"%s %s %s %s %s","SELECT",lpszQueryEx,"FROM",lpszTableName,lpszCondition);
	}

	TRACE("SQL Statement: %s \n",szBuf);

	_bstr_t bstrCommand(szBuf);

	_variant_t *pvFields;
	pvFields = new _variant_t[nFieldCount];

	CStringArray csFieldArray;
	SplitStringEx(lpszFields,LPCTSTR(","),&csFieldArray);

	for(int i=0; i < csFieldArray.GetSize(); i++)
	{
		CString szTempFieldName;
		szTempFieldName = csFieldArray.GetAt(i);
		szTempFieldName.MakeUpper();
		int nIndex = szTempFieldName.Find(" AS ");

		if(nIndex != -1)
		{
			szTempFieldName = szTempFieldName.Mid(nIndex +  3);
			szTempFieldName.TrimLeft();
			szTempFieldName.TrimRight();
			csFieldArray.SetAt(i,szTempFieldName);
		}
	}

	try
	{
		pRecordset = m_pConnection->Execute(bstrCommand,&vRecsAffected,adCmdText); 

		if(!pRecordset->GetadoEOF())
		{
			while(!pRecordset->GetadoEOF())
			{
				for(int nLoop=0; nLoop<nFieldCount; nLoop++)
				{
					pvFields[nLoop] = pRecordset->GetCollect((_variant_t)(_bstr_t)csFieldArray.GetAt(nLoop)); 
					if(pvFields[nLoop].vt != VT_NULL)
					{
						pcsValueArray[nLoop].Add((LPCTSTR)(_bstr_t)pvFields[nLoop]);
					}
					else
					{
						pcsValueArray[nLoop].Add("");
					}
				}
				pRecordset->MoveNext();
			}
		}
		pRecordset->Close(); 
	}
	catch(_com_error &Error)
	{
		wsprintf(szBuf,"%s%s  %s%s  %s%s","Source :",(LPCTSTR)Error.Source(),"ErrorMessage :",(LPCTSTR)Error.ErrorMessage(),"Description :",(LPCTSTR)Error.Description());   
		
		m_csErrorMessage = szBuf; 

		delete []pvFields;
		return FALSE;
	}
	
	delete []pvFields;
	return TRUE;
}