/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Jorge Lodos
// All rights reserved
//
// Distribute and use freely, except:
// 1. Don't alter or remove this notice.
// 2. Mark the changes you made
//
// Send bug reports, bug fixes, enhancements, requests, etc. to:
//    lodos@cigb.edu.cu
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Standard Field Exchange routines. (Modified from dbrfx.cpp in mfc sources)
// In CStoredProcResult derived classes RFX_String must be used in place of
// RFX_Text, otherwise you will get exceptions.

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Note: CString.m_pchData must not be changed.  This address is registered
// with ODBC and must remain valid until the recordset is released.
void AFXAPI RFX_String(CFieldExchange* pFX, LPCTSTR szName,
	CString& value, int nMaxLength, int nColumnType, short nScale)
{
	ASSERT(AfxIsValidAddress(pFX, sizeof(CFieldExchange)));
	ASSERT(AfxIsValidString(szName));
	ASSERT(AfxIsValidAddress(&value, sizeof(CString)));

	RETCODE nRetCode;
	UINT nField;
	if (!pFX->IsFieldType(&nField))
		return;

	LONG* plLength = pFX->m_prs->GetFieldLengthBuffer(
		nField - 1, pFX->m_nFieldType);
	switch (pFX->m_nOperation)
	{
	default:
		pFX->Default(szName, value.GetBuffer(0), plLength,
			SQL_C_CHAR, value.GetLength(), nMaxLength);
		value.ReleaseBuffer();
		return;

	case CFieldExchange::BindParam:
		{
			// Preallocate to nMaxLength and setup binding address
			value.GetBufferSetLength(nMaxLength);
			void* pvParam = value.LockBuffer(); // will be overwritten if UNICODE

#ifdef _UNICODE
			// Must use proxy to translate unicode data into non-unicode param
			pFX->m_prs->m_bRebindParams = TRUE;

			// Allocate proxy array if necessary
			if (pFX->m_prs->m_pvParamProxy == NULL)
			{
				pFX->m_prs->m_pvParamProxy = new void*[pFX->m_prs->m_nParams];
				memset(pFX->m_prs->m_pvParamProxy, 0,
					pFX->m_prs->m_nParams*sizeof(void*));
				pFX->m_prs->m_nProxyParams = pFX->m_prs->m_nParams;
			}

			// Allocate non-unicode string to nMaxLength if necessary for SQLBindParameter
			if (pFX->m_prs->m_pvParamProxy[nField-1] == NULL)
			{
				pvParam = new CHAR[nMaxLength+1];
				pFX->m_prs->m_pvParamProxy[nField-1] = pvParam;
			}
			else
				pvParam = pFX->m_prs->m_pvParamProxy[nField-1];

			// Now fill in the data value
			USES_CONVERSION;
			lstrcpyA((char*)pvParam, T2A((LPCTSTR)value));
#endif // _UNICODE

			*plLength = pFX->m_prs->IsParamStatusNull(nField - 1) ?
				SQL_NULL_DATA : SQL_NTS;

			AFX_SQL_SYNC(::SQLBindParameter(pFX->m_hstmt, (UWORD)nField,
				 (SWORD)pFX->m_nFieldType, SQL_C_CHAR, (SWORD)nColumnType,
				 nMaxLength, nScale, pvParam, /*0 was here, not nMaxLength, Jorge Lodos 13/5/1998*/
				 nMaxLength, plLength));

			value.ReleaseBuffer();

			if (nRetCode != SQL_SUCCESS)
				pFX->m_prs->ThrowDBException(nRetCode, pFX->m_hstmt);

			// Add the member address to the param map
			pFX->m_prs->m_mapParamIndex.SetAt(&value, (void*)nField);
		}
		return;

#ifdef _UNICODE
	case CFieldExchange::RebindParam:
		*plLength = pFX->m_prs->IsParamStatusNull(nField - 1) ?
			SQL_NULL_DATA : SQL_NTS;
		if (pFX->m_prs->m_nProxyParams != 0)
		{
			// Fill buffer (expected by SQLBindParameter) with new param data
			USES_CONVERSION;
			LPSTR lpszParam = (LPSTR)pFX->m_prs->m_pvParamProxy[nField-1];
			lstrcpyA(lpszParam, T2A((LPCTSTR)value));
		}
		return;
#endif // _UNICODE

	case CFieldExchange::BindFieldToColumn:
		{
			// Assumes all bound fields BEFORE unbound fields
			CODBCFieldInfo* pODBCInfo =
				&pFX->m_prs->m_rgODBCFieldInfos[nField - 1];
			UINT cbColumn = pODBCInfo->m_nPrecision;

			switch (pODBCInfo->m_nSQLType)
			{
			default:
#ifdef _DEBUG
				// Warn of possible field schema mismatch
				if (afxTraceFlags & traceDatabase)
					TRACE1("Warning: CString converted from SQL type %ld.\n",
						pODBCInfo->m_nSQLType);
#endif // _DEBUG

				// Add room for extra information like sign, decimal point, etc.
				cbColumn += 10;
				break;

			case SQL_LONGVARCHAR:
			case SQL_CHAR:
			case SQL_VARCHAR:
				break;

			case SQL_FLOAT:
			case SQL_REAL:
			case SQL_DOUBLE:
				// Add room for sign, decimal point and " E +XXX"
				cbColumn += 10;
				break;

			case SQL_DECIMAL:
			case SQL_NUMERIC:
				// Add room for sign and decimal point
				cbColumn += 2;
				break;

			case SQL_TIMESTAMP:
			case SQL_DATE:
			case SQL_TIME:
				// May need extra space, i.e. "{TS mm/dd/yyyy hh:mm:ss}"
				cbColumn += 10;
				break;

			case SQL_TINYINT:
			case SQL_SMALLINT:
			case SQL_INTEGER:
			case SQL_BIGINT:
				// Add room for sign
				cbColumn += 1;
				break;
			}

			// Constrain to user specified max length, subject to 256 byte min
			if (cbColumn > (UINT)nMaxLength || cbColumn < 256)
				cbColumn = nMaxLength;

			// Set up binding addres
			void* pvData;
			value.GetBufferSetLength(cbColumn+1);
			pvData = value.LockBuffer();    // will be overwritten if UNICODE

#ifdef _UNICODE
			// Allocate proxy array if necessary
			if (pFX->m_prs->m_pvFieldProxy == NULL)
			{
				pFX->m_prs->m_pvFieldProxy = new void*[pFX->m_prs->m_nFields];
				memset(pFX->m_prs->m_pvFieldProxy, 0,
					pFX->m_prs->m_nFields*sizeof(void*));
				pFX->m_prs->m_nProxyFields = pFX->m_prs->m_nFields;
			}

			// Allocate non-unicode string for SQLBindCol (not necessary on Requery)
			if (pFX->m_prs->m_pvFieldProxy[nField-1] == NULL)
				pFX->m_prs->m_pvFieldProxy[nField-1] = new CHAR[cbColumn+2];

			pvData = pFX->m_prs->m_pvFieldProxy[nField-1];
#endif // _UNICODE

			AFX_SQL_SYNC(::SQLBindCol(pFX->m_prs->m_hstmt, (UWORD)nField,
				SQL_C_CHAR, pvData, cbColumn+1, plLength));
			value.ReleaseBuffer();
			if (!pFX->m_prs->Check(nRetCode))
				pFX->m_prs->ThrowDBException(nRetCode);

			// Add the member address to the field map
			pFX->m_prs->m_mapFieldIndex.SetAt(&value, (void*)nField);
		}
		return;

#ifdef _UNICODE
	case CFieldExchange::BindFieldForUpdate:
		if (pFX->m_prs->m_nProxyFields != 0)
		{
			// Fill buffer (expected by SQLSetPos) with new field data
			USES_CONVERSION;
			LPSTR lpszData = (LPSTR)pFX->m_prs->m_pvFieldProxy[nField-1];
			lstrcpyA(lpszData, T2A((LPCTSTR)value));

			pFX->Default(szName, (void *)lpszData, plLength, SQL_C_CHAR,
				value.GetLength(), nMaxLength);
		}
		return;
#endif // _UNICODE

	case CFieldExchange::Fixup:
		if (*plLength == SQL_NULL_DATA)
		{
			pFX->m_prs->SetNullFieldStatus(nField - 1);
			value.GetBufferSetLength(0);
			value.ReleaseBuffer();
		}
		else
		{
#ifdef _UNICODE
			// Copy value out of the proxy
			value = (LPSTR)pFX->m_prs->m_pvFieldProxy[nField-1];
#endif

			LPTSTR lpsz = value.GetBuffer(0);
			if (pFX->m_prs->m_pDatabase->m_bStripTrailingSpaces)
			{
				// find first trailing space
				LPTSTR lpszFirstTrailing = NULL;
				while (*lpsz != '\0')
				{
					if (*lpsz != ' ')
						lpszFirstTrailing = NULL;
					else
					{
						if (lpszFirstTrailing == NULL)
							lpszFirstTrailing = lpsz;
					}
					lpsz = _tcsinc(lpsz);
				}
				// truncate
				if (lpszFirstTrailing != NULL)
					*lpszFirstTrailing = '\0';

			}
			value.ReleaseBuffer();
			*plLength = value.GetLength();
		}
		return;

	case CFieldExchange::SetFieldNull:
		if ((pFX->m_pvField == NULL &&
			pFX->m_nFieldType == CFieldExchange::outputColumn) ||
			pFX->m_pvField == &value)
		{
			if (pFX->m_bField)
			{
				// Mark fields null
				pFX->m_prs->SetNullFieldStatus(nField - 1);
				// Set string 0 length
				value.GetBufferSetLength(0);
				value.ReleaseBuffer();
				*plLength = SQL_NULL_DATA;
			}
			else
			{
				pFX->m_prs->ClearNullFieldStatus(nField - 1);
				*plLength = SQL_NTS;
			}
#ifdef _DEBUG
			pFX->m_nFieldFound = nField;
#endif
		}
		return;


#ifdef _UNICODE
	case CFieldExchange::NameValue:
		if (pFX->m_prs->IsFieldStatusDirty(nField - 1))
		{
			*pFX->m_pstr += szName;
			*pFX->m_pstr += '=';
		}
		// Fall through

	case CFieldExchange::Value:
		if (pFX->m_prs->IsFieldStatusDirty(nField - 1))
		{
			// Get the field data
			CODBCFieldInfo* pODBCInfo =
					&pFX->m_prs->m_rgODBCFieldInfos[nField - 1];

			LPSTR lpszData = (LPSTR)pFX->m_prs->m_pvFieldProxy[nField-1];
			if (pFX->m_prs->IsFieldStatusNull(nField - 1))
			{
				*plLength = SQL_NULL_DATA;
			}
			else
			{
				USES_CONVERSION;
				lstrcpyA(lpszData, T2A((LPCTSTR)value));
				*plLength = value.GetLength();
			}

			// If optimizing for bulk add, only need lengths & proxy set correctly
			if(!(pFX->m_prs->m_dwOptions & CRecordset::optimizeBulkAdd))
			{
				*pFX->m_pstr += '?';
				*pFX->m_pstr += pFX->m_lpszSeparator;
				pFX->m_nParamFields++;
				AFX_SQL_SYNC(::SQLBindParameter(pFX->m_hstmt,
					(UWORD)pFX->m_nParamFields, SQL_PARAM_INPUT,
					SQL_C_CHAR, pODBCInfo->m_nSQLType, nMaxLength,
					pODBCInfo->m_nScale, lpszData, 0, plLength));
			}
		}
		return;
#endif // _UNICODE

	case CFieldExchange::MarkForAddNew:
		// can force writing of psuedo-null value (as a non-null) by setting field dirty
		if (!value.IsEmpty())
		{
			pFX->m_prs->SetDirtyFieldStatus(nField - 1);
			pFX->m_prs->ClearNullFieldStatus(nField - 1);
		}
		return;

	case CFieldExchange::MarkForUpdate:
		if (value.IsEmpty())
			pFX->m_prs->SetNullFieldStatus(nField - 1);
		else
			pFX->m_prs->ClearNullFieldStatus(nField - 1);
		pFX->Default(szName, &value, plLength,
			SQL_C_CHAR, value.GetLength(), nMaxLength);
		return;

	case CFieldExchange::LoadField:
		{
			// Get the field data
			CFieldInfo* pInfo = &pFX->m_prs->m_rgFieldInfos[nField - 1];
			CString* pStrCachedValue = (CString*)pInfo->m_pvDataCache;

			// Restore the status
			pFX->m_prs->SetFieldStatus(nField - 1, pInfo->m_bStatus);

			// If not NULL, restore the value and length
			if (!pFX->m_prs->IsFieldStatusNull(nField - 1))
			{
				value = *pStrCachedValue;
				*plLength = value.GetLength();

#ifdef _UNICODE
				// Must restore proxy for correct WHERE CURRENT OF operation
				USES_CONVERSION;
				LPSTR lpszData = (LPSTR)pFX->m_prs->m_pvFieldProxy[nField-1];
				lstrcpyA(lpszData, T2A((LPCTSTR)value));
#endif // _UNICODE
			}
			else
			{
				*plLength = SQL_NULL_DATA;
			}

#ifdef _DEBUG
			// Buffer address must not change - ODBC's SQLBindCol depends upon this
			void* pvBind;

	#ifdef _UNICODE
			pvBind = pFX->m_prs->m_pvFieldProxy[nField-1];
	#else // !_UNICODE
			pvBind = value.GetBuffer(0);
			value.ReleaseBuffer();
	#endif

			if (pvBind != pInfo->m_pvBindAddress)
			{
				TRACE1("Error: CString buffer (column %u) address has changed!\n",
					nField);
				ASSERT(FALSE);
			}
#endif // _DEBUG
		}
		return;

	case CFieldExchange::StoreField:
		AfxStoreField(*pFX->m_prs, nField, &value);
		return;

	case CFieldExchange::AllocCache:
		{
			CFieldInfo* pInfo = &pFX->m_prs->m_rgFieldInfos[nField - 1];
			pInfo->m_pvDataCache = new CString;
			pInfo->m_nDataType = AFX_RFX_TEXT;
		}
		return;

#ifdef _DEBUG
	case CFieldExchange::DumpField:
		*pFX->m_pdcDump << "\n" << szName << " = " << value;
		return;
#endif // _DEBUG

	}
}

#define AFX_RFX_OLEDATETIME_PSEUDO_NULL COleDateTime()

void AFXAPI RFX_Date(CFieldExchange* pFX, LPCTSTR szName, COleDateTime& value)
{
	ASSERT(AfxIsValidAddress(pFX, sizeof(CFieldExchange)));
	ASSERT(AfxIsValidString(szName));

	RETCODE nRetCode;
	UINT nField;
	if (!pFX->IsFieldType(&nField))
		return;

	LONG* plLength = pFX->m_prs->GetFieldLengthBuffer(nField - 1, pFX->m_nFieldType);
	switch (pFX->m_nOperation)
	{
	default:
		{
			pFX->Default(szName, &value, plLength, SQL_C_TIMESTAMP,
				sizeof(value), TIMESTAMP_PRECISION);
		}
		return;

	case CFieldExchange::BindParam:
		{
			TIMESTAMP_STRUCT* pts;
			pFX->m_prs->m_bRebindParams = TRUE;

			if (pFX->m_prs->IsParamStatusNull(nField - 1))
			{
				pts = NULL;
				*plLength = SQL_NULL_DATA;
			}
			else
			{
				// Allocate proxy array if necessary
				if (pFX->m_prs->m_pvParamProxy == NULL)
				{
					pFX->m_prs->m_pvParamProxy = new void*[pFX->m_prs->m_nParams];
					memset(pFX->m_prs->m_pvParamProxy, 0,
						pFX->m_prs->m_nParams*sizeof(void*));
					pFX->m_prs->m_nProxyParams = pFX->m_prs->m_nParams;
				}

				// Allocate TIMESTAMP_STRUCT if necessary for SQLBindParameter
				if (pFX->m_prs->m_pvParamProxy[nField-1] == NULL)
				{
					pts = new TIMESTAMP_STRUCT;
					pFX->m_prs->m_pvParamProxy[nField-1] = pts;
				}
				else
					pts = (TIMESTAMP_STRUCT *)pFX->m_prs->m_pvParamProxy[nField-1];

				pts->year = (SWORD)value.GetYear();
				pts->month = (UWORD)value.GetMonth();
				pts->day = (UWORD)value.GetDay();
				pts->hour = (UWORD)value.GetHour();
				pts->minute = (UWORD)value.GetMinute();
				pts->second = (UWORD)value.GetSecond();
				pts->fraction = 0;
				*plLength = sizeof(TIMESTAMP_STRUCT);
			}

			AFX_SQL_SYNC(::SQLBindParameter(pFX->m_hstmt, (UWORD)nField,
				(SWORD)pFX->m_nFieldType, SQL_C_TIMESTAMP, SQL_C_TIMESTAMP,
				TIMESTAMP_PRECISION, 0, pts, 0, plLength));
			if (nRetCode != SQL_SUCCESS)
				pFX->m_prs->ThrowDBException(nRetCode, pFX->m_hstmt);

			// Add the member address to the param map
			pFX->m_prs->m_mapParamIndex.SetAt(&value, (void*)nField);
		}
		return;

	case CFieldExchange::RebindParam:
		{
			*plLength = pFX->m_prs->IsParamStatusNull(nField - 1) ?
				SQL_NULL_DATA : sizeof(TIMESTAMP_STRUCT);
			if (pFX->m_prs->m_nProxyParams != 0)
			{
				// Fill buffer (expected by SQLBindParameter) with new param data
				TIMESTAMP_STRUCT* pts;
				pts = (TIMESTAMP_STRUCT *)pFX->m_prs->m_pvParamProxy[nField-1];
				pts->year = (SWORD)value.GetYear();
				pts->month = (UWORD)value.GetMonth();
				pts->day = (UWORD)value.GetDay();
				pts->hour = (UWORD)value.GetHour();
				pts->minute = (UWORD)value.GetMinute();
				pts->second = (UWORD)value.GetSecond();
				pts->fraction = 0;
			}
		}
		return;

	case CFieldExchange::BindFieldToColumn:
		{
#ifdef _DEBUG
			// Assumes all bound fields BEFORE unbound fields
			CODBCFieldInfo* pODBCInfo =
				&pFX->m_prs->m_rgODBCFieldInfos[nField - 1];

			if (pODBCInfo->m_nSQLType != SQL_DATE &&
				pODBCInfo->m_nSQLType != SQL_TIME &&
				pODBCInfo->m_nSQLType != SQL_TIMESTAMP)
			{
				// Warn of possible field schema mismatch
				if (afxTraceFlags & traceDatabase)
					TRACE1("Warning: COleDateTime converted from SQL type %ld.\n",
						pODBCInfo->m_nSQLType);
			}
#endif // _DEBUG

			// Allocate proxy array if necessary
			if (pFX->m_prs->m_pvFieldProxy == NULL)
			{
				pFX->m_prs->m_pvFieldProxy = new void*[pFX->m_prs->m_nFields];
				memset(pFX->m_prs->m_pvFieldProxy, 0,
					pFX->m_prs->m_nFields*sizeof(void*));
				pFX->m_prs->m_nProxyFields = pFX->m_prs->m_nFields;
			}

			// Allocate TIMESTAMP_STRUCT for SQLBindCol (not necessary on Requery)
			if (pFX->m_prs->m_pvFieldProxy[nField-1] == NULL)
				pFX->m_prs->m_pvFieldProxy[nField-1] = new TIMESTAMP_STRUCT;

			AFX_SQL_SYNC(::SQLBindCol(pFX->m_prs->m_hstmt, (UWORD)nField,
				SQL_C_TIMESTAMP, pFX->m_prs->m_pvFieldProxy[nField-1],
				sizeof(TIMESTAMP_STRUCT), plLength));
			if (!pFX->m_prs->Check(nRetCode))
				pFX->m_prs->ThrowDBException(nRetCode);

			// Add the member address to the field map
			pFX->m_prs->m_mapFieldIndex.SetAt(&value, (void*)nField);
		}
		return;

	case CFieldExchange::BindFieldForUpdate:
		if (pFX->m_prs->m_nProxyFields != 0)
		{
			// Fill buffer (expected by SQLSetPos) with new field data
			TIMESTAMP_STRUCT* pts;
			pts = (TIMESTAMP_STRUCT *)pFX->m_prs->m_pvFieldProxy[nField-1];
			pts->year = (SWORD)value.GetYear();
			pts->month = (UWORD)value.GetMonth();
			pts->day = (UWORD)value.GetDay();
			pts->hour = (UWORD)value.GetHour();
			pts->minute = (UWORD)value.GetMinute();
			pts->second = (UWORD)value.GetSecond();
			pts->fraction = 0;

			pFX->Default(szName, (void *)pts, plLength, SQL_C_TIMESTAMP,
				sizeof(TIMESTAMP_STRUCT), TIMESTAMP_PRECISION);
		}
		return;

	case CFieldExchange::Fixup:
		if (*plLength == SQL_NULL_DATA)
		{
			pFX->m_prs->SetNullFieldStatus(nField - 1);
			value = AFX_RFX_OLEDATETIME_PSEUDO_NULL;
		}
		else
		{
			TIMESTAMP_STRUCT* pts =
				(TIMESTAMP_STRUCT*)pFX->m_prs->m_pvFieldProxy[nField-1];
			if (pts->year < 100 || pts->year > 9999)
			{
				// Time value out of range, return NULL
#ifdef _DEBUG
				if (afxTraceFlags & traceDatabase)
					TRACE0("Warning: date value out of range, returning NULL value.\n");
#endif
				pFX->m_prs->SetNullFieldStatus(nField - 1);
				value = AFX_RFX_OLEDATETIME_PSEUDO_NULL;
			}
			else
			{
#ifdef _DEBUG
				if ((afxTraceFlags & traceDatabase) && pts->fraction != 0)
					TRACE0("Warning: ignoring milliseconds.\n");
#endif
				value = COleDateTime(pts->year, pts->month, pts->day,
					pts->hour, pts->minute, pts->second);
			}
		}
		return;

	case CFieldExchange::NameValue:
		if (pFX->m_prs->IsFieldStatusDirty(nField - 1))
		{
			*pFX->m_pstr += szName;
			*pFX->m_pstr += '=';
		}
		// Fall through

	case CFieldExchange::Value:
		if (pFX->m_prs->IsFieldStatusDirty(nField - 1))
		{
			TIMESTAMP_STRUCT* pts =
				(TIMESTAMP_STRUCT*)pFX->m_prs->m_pvFieldProxy[nField-1];
			if (pFX->m_prs->IsFieldStatusNull(nField - 1))
			{
				*plLength = SQL_NULL_DATA;
			}
			else
			{
				pts->year = (SWORD)value.GetYear();
				pts->month = (UWORD)value.GetMonth();
				pts->day = (UWORD)value.GetDay();
				pts->hour = (UWORD)value.GetHour();
				pts->minute = (UWORD)value.GetMinute();
				pts->second = (UWORD)value.GetSecond();
				pts->fraction = 0;
				*plLength = sizeof(TIMESTAMP_STRUCT);
			}

			// If optimizing for bulk add, only need lengths & proxy set correctly
			if(!(pFX->m_prs->m_dwOptions & CRecordset::optimizeBulkAdd))
			{
				*pFX->m_pstr += '?';
				*pFX->m_pstr += pFX->m_lpszSeparator;
				pFX->m_nParamFields++;

				// Assumes all bound fields BEFORE unbound fields
				CODBCFieldInfo* pODBCInfo =
					&pFX->m_prs->m_rgODBCFieldInfos[nField - 1];

				AFX_SQL_SYNC(::SQLBindParameter(pFX->m_hstmt,
					(UWORD)pFX->m_nParamFields, SQL_PARAM_INPUT,
					SQL_C_TIMESTAMP, pODBCInfo->m_nSQLType,
					TIMESTAMP_PRECISION, 0, pts, 0, plLength));
			}
		}
		return;

	case CFieldExchange::SetFieldNull:
		if ((pFX->m_pvField == NULL &&
			pFX->m_nFieldType == CFieldExchange::outputColumn) ||
			pFX->m_pvField == &value)
		{
			if (pFX->m_bField)
			{
				// Mark fields null
				pFX->m_prs->SetNullFieldStatus(nField - 1);
				value = AFX_RFX_OLEDATETIME_PSEUDO_NULL;
				*plLength = SQL_NULL_DATA;
			}
			else
			{
				pFX->m_prs->ClearNullFieldStatus(nField - 1);
				*plLength = sizeof(TIMESTAMP_STRUCT);
			}
#ifdef _DEBUG
			pFX->m_nFieldFound = nField;
#endif
		}
		return;

	case CFieldExchange::MarkForAddNew:
		{
			// can force writing of psuedo-null value (as a non-null) by setting field dirty
			COleDateTime timeNull = AFX_RFX_OLEDATETIME_PSEUDO_NULL;
			if (value != timeNull)
			{
				pFX->m_prs->SetDirtyFieldStatus(nField - 1);
				pFX->m_prs->ClearNullFieldStatus(nField - 1);
			}
		}
		return;

	case CFieldExchange::MarkForUpdate:
		{
			COleDateTime timeNull = AFX_RFX_OLEDATETIME_PSEUDO_NULL;
			if (value != timeNull)
			{
				pFX->m_prs->ClearNullFieldStatus(nField - 1);
			}
	
			void* pv = &value; 

			// Get the field data 
			CFieldInfo* pInfo = &pFX->m_prs->m_rgFieldInfos[nField - 1]; 

			// If user changed field value from previous value, mark field dirty 
			if ((pInfo->m_bStatus & AFX_SQL_FIELD_FLAG_NULL)) 
			{ 
				if (!pFX->m_prs->IsFieldStatusNull(nField - 1)) 
					pFX->m_prs->SetDirtyFieldStatus(nField - 1); 
			} 
			else 
			{ 
				// Saved field is not NULL. current field null, so field dirty 
				BOOL bDirty = pFX->m_prs->IsFieldStatusNull(nField - 1); 

				// If values differ, then field dirty 
				COleDateTime* pvDataCache = (COleDateTime*)pInfo->m_pvDataCache; 
				if (bDirty || !(value == *pvDataCache)) 
					pFX->m_prs->SetDirtyFieldStatus(nField - 1); 
			} 

#ifdef _DEBUG 
			// Field address must not change - ODBC's SQLBindCol depends upon this 
			if (pInfo->m_pvBindAddress != pFX->m_prs->m_pvFieldProxy[nField-1]) 
			{ 
				TRACE1("Error: field address (column %u) has changed!\n", nField); 
				ASSERT(FALSE); 
			} 
#endif // _DEBUG 

			if ((pFX->m_pvField == NULL || pFX->m_pvField == pv) && 
					 pFX->m_prs->IsFieldStatusDirty(nField - 1)) 
			{ 
				pFX->m_bField = TRUE; 
			} 
		} 
		return; 

	case CFieldExchange::StoreField: 
		{
			// Get the field data 
			CFieldInfo* pInfo = &pFX->m_prs->m_rgFieldInfos[nField - 1]; 

			// Cache the status 
			pInfo->m_bStatus = pFX->m_prs->GetFieldStatus(nField - 1); 

			// Save the data 
			if (!pFX->m_prs->IsFieldStatusNull(nField - 1)) 
				*(COleDateTime*)pInfo->m_pvDataCache = value; 

#ifdef _DEBUG 
			// Cache the bind address expected by ODBC 
			pInfo->m_pvBindAddress = pFX->m_prs->m_pvFieldProxy[nField-1]; 
#endif 
		}
		return; 

	case CFieldExchange::LoadField:
		{
			// Get the field data
			CFieldInfo* pInfo = &pFX->m_prs->m_rgFieldInfos[nField - 1];

			// Restore the status
			pFX->m_prs->SetFieldStatus(nField - 1, pInfo->m_bStatus);

			// If not NULL, restore the value, length and proxy
			if (!pFX->m_prs->IsFieldStatusNull(nField - 1))
			{
				*(COleDateTime*)pInfo->m_pvDataCache = value; 
				*plLength = sizeof(TIMESTAMP_STRUCT); 

				// Restore proxy for correct WHERE CURRENT OF operations
				TIMESTAMP_STRUCT* pts =
					(TIMESTAMP_STRUCT*)pFX->m_prs->m_pvFieldProxy[nField-1];

				pts->year = (SWORD)value.GetYear();
				pts->month = (UWORD)value.GetMonth();
				pts->day = (UWORD)value.GetDay();
				pts->hour = (UWORD)value.GetHour();
				pts->minute = (UWORD)value.GetMinute();
				pts->second = (UWORD)value.GetSecond();
				pts->fraction = 0;
			}
			else
				*plLength = SQL_NULL_DATA;

#ifdef _DEBUG
			// Buffer address must not change - ODBC's SQLBindCol depends upon this
			if (pInfo->m_pvBindAddress != pFX->m_prs->m_pvFieldProxy[nField-1])
			{
				TRACE1("Error: CString buffer (column %u) address has changed!\n",
					nField);
				ASSERT(FALSE);
			}
#endif // _DEBUG
		}
		return;

	case CFieldExchange::AllocCache:
		{
			CFieldInfo* pInfo = &pFX->m_prs->m_rgFieldInfos[nField - 1];
			pInfo->m_pvDataCache = new COleDateTime;
			pInfo->m_nDataType = AFX_RFX_DATE;
		}
		return;

#ifdef _DEBUG
	case CFieldExchange::DumpField:
		*pFX->m_pdcDump << "\n" << szName << " = " << value;
		return;
#endif // _DEBUG

	}
}
