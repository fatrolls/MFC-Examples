// SlowSet.cpp : implementation file
//

#include "stdafx.h"
#include "FastTest.h"
#include "SlowSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlowSet

IMPLEMENT_DYNAMIC(CSlowSet, CRecordset)

CSlowSet::CSlowSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSlowSet)
	m_CODE = _T("");
	m_NAME = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSlowSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=FASTDB");
}

CString CSlowSet::GetDefaultSQL()
{
	return _T("[LOCATIONS]");
}

void CSlowSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSlowSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[CODE]"), m_CODE);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSlowSet diagnostics

#ifdef _DEBUG
void CSlowSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSlowSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
