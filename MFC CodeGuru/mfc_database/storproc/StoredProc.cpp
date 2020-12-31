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

#include "stdafx.h"
#include "StoredProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
// CStoredProcResult

CStoredProcResult::CStoredProcResult(CDatabase* pDatabase) : CRecordset(pDatabase)
{
}

CStoredProcResult::~CStoredProcResult()
{
}

BOOL CStoredProcResult::Open(LPCTSTR lpszSQL)
{
	ASSERT(!IsOpen());
	ASSERT_VALID(this);
	ASSERT(lpszSQL == NULL || AfxIsValidString(lpszSQL));

	// Cache state info and allocate hstmt
	SetState(AFX_DB_USE_DEFAULT_TYPE, lpszSQL, none);
	if(!AllocHstmt())
		return FALSE;

	TRY
	{
		OnSetOptions(m_hstmt);

		// Allocate the field/param status arrays, if necessary
		BOOL bUnbound = FALSE;
		if (m_nFields > 0 || m_nParams > 0)
			AllocStatusArrays();
		else
			bUnbound = TRUE;

		// Build SQL and prep/execute or just execute direct
		BuildSQL(lpszSQL);
		PrepareAndExecute();

		// Cache some field info and prepare the rowset
		AllocAndCacheFieldInfo();
		AllocRowset();

		// If late binding, still need to allocate status arrays
		if (bUnbound && (m_nFields > 0 || m_nParams > 0))
			AllocStatusArrays();

		// Give derived classes a call before binding
		PreBindFields();

		// If EOF, then result set empty, so set BOF as well
		m_bBOF = m_bEOF = TRUE;
	}
	CATCH_ALL(e)
	{
		Close();
		THROW_LAST();
	}
	END_CATCH_ALL

	return TRUE;
}

BOOL CStoredProcResult::Requery()
{
	RETCODE nRetCode;

	ASSERT_VALID(this);
	ASSERT(IsOpen());

	TRY
	{
		// Shutdown current query, preserving buffers for performance
		AFX_SQL_SYNC(::SQLFreeStmt(m_hstmt, SQL_CLOSE));
		m_lOpen = AFX_RECORDSET_STATUS_CLOSED;

		// Rebind date/time parameters
		RebindParams(m_hstmt);

		// now attempt to re-execute the SQL Query
		::SQLExecute(m_hstmt);
		if (!Check(nRetCode))
		{
			TRACE0("Error: Requery attempt failed.\n");
			ThrowDBException(nRetCode);
		}

		m_lOpen = AFX_RECORDSET_STATUS_OPEN;

		// If EOF, then result set empty, so set BOF as well
		m_bBOF = m_bEOF = TRUE;
	}
	CATCH_ALL(e)
	{
		Close();
		THROW_LAST();
	}
	END_CATCH_ALL

	return TRUE;    // all set
}

//////////////////////////////////////////////////////////////////////////////
// CRecordset diagnostics

#ifdef _DEBUG
void CStoredProcResult::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStoredProcResult::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);

	dc << "\nm_strSQL = " << m_strSQL;
	dc << "\nm_hstmt = " << m_hstmt;
	dc << "\nm_bRecordsetDb = " << m_bRecordsetDb;

	dc << "\nm_lOpen = " << m_lOpen;

	dc << "\nm_nParams = " << m_nParams;

	if (dc.GetDepth() > 0)
	{
		if (m_pDatabase == NULL)
			dc << "with no database\n";
		else
			dc << "with database: " << m_pDatabase;
	}
}
#endif // _DEBUG

IMPLEMENT_DYNAMIC(CStoredProcResult, CRecordset)

/////////////////////////////////////////////////////////////////////////////
