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

#ifndef __STOREDPROC_H__
#define __STOREDPROC_H__

//////////////////////////////////////////////////////////////////////////////
// CStoredProcResult - the result of a SQL stored procedure that doesn't return records

class CStoredProcResult : private CRecordset
{
	DECLARE_DYNAMIC(CStoredProcResult)

// Constructor
public:
	CStoredProcResult(CDatabase* pDatabase = NULL);

public:
	virtual ~CStoredProcResult();
	virtual BOOL Open(LPCTSTR lpszSQL = NULL);

// Attributes
public:
	CRecordset::m_hstmt;      // Source statement for this resultset
	CRecordset::m_pDatabase;  // Source database for this resultset

	CRecordset::GetSQL;       // SQL executed for this stored procedure
	CRecordset::IsOpen;       // Stored procedure already executed?

// Operations
public:
	CRecordset::SetParamNull;

	// Stored procedure operations
	virtual BOOL Requery();        // Re-execute the stored procedure based on new params

	// Cancel asynchronous operation
	CRecordset::Cancel;

// Overridables
public:
	// Get default connect string
	CRecordset::GetDefaultConnect;

	// Get SQL to execute
	CRecordset::GetDefaultSQL;

	// for stored procedure param exchange
	CRecordset::DoFieldExchange;

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif //_DEBUG

	CRecordset::Check; // general error check

	CRecordset::PreBindFields;   // called before data fields are bound
	CRecordset::m_nParams;       // number of RFX params
	CRecordset::m_bRebindParams; // date or UNICODE text parameter existence flag
	CRecordset::m_mapParamIndex; // Map of member address to field index

	// RFX Operations on params of CStoredProcResult
	CRecordset::BindParams;
	CRecordset::RebindParams;

	// RFX operation helper functions
	CRecordset::ThrowDBException;

	CRecordset::GetBoundParamIndex;

	CRecordset::AllocStatusArrays;
	CRecordset::GetFieldLengthBuffer;   // for params only

	CRecordset::IsParamStatusNull;
	CRecordset::SetNullParamStatus;
	CRecordset::ClearNullParamStatus;

	CRecordset::m_pvParamProxy;
	CRecordset::m_nProxyParams;

protected:
	CRecordset::m_lOpen;
	CRecordset::m_bRecordsetDb;
	CRecordset::m_strSQL;       // SQL statement for recordset
	CRecordset::m_pbParamFlags;
	CRecordset::m_plParamLength;

protected:
	CRecordset::m_strRequerySQL;    // archive SQL string

	CRecordset::AllocHstmt;
	CRecordset::BuildSQL;
	CRecordset::PrepareAndExecute;

	friend class CFieldExchange;

// members inherited from CObject 
public:

	// Object model (types, destruction, allocation)
	CRecordset::GetRuntimeClass;

	// Diagnostic allocations
	CRecordset::operator new;
	CRecordset::operator delete;

	// Serialization
	CRecordset::Serialize;

// Attributes
public:
	CRecordset::IsSerializable;
	CRecordset::IsKindOf;

// Implementation
public:
	CRecordset::classCObject;
#ifdef _AFXDLL
	CRecordset::_GetBaseClass;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// Standard Field Exchange routines.
// In CStoredProcResult derived classes RFX_String must be used in place of
// RFX_Text for output parameters, otherwise you will get exceptions.

// text data
void AFXAPI RFX_String(CFieldExchange* pFX, LPCTSTR szName, CString& value,
	// Default max length for char and varchar, default datasource type
	int nMaxLength = 255, int nColumnType = SQL_VARCHAR, short nScale = 0);

// date and time
void AFXAPI RFX_Date(CFieldExchange* pFX, LPCTSTR szName, COleDateTime& value);

#endif //__STOREDPROC_H__

