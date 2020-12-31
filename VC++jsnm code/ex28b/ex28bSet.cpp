// ex28bSet.cpp : implementation of the CEx28bSet class
//

#include "stdafx.h"
#include "ex28b.h"
#include "ex28bSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28bSet implementation

IMPLEMENT_DYNAMIC(CEx28bSet, CRecordset)

CEx28bSet::CEx28bSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEx28bSet)
	m_InstructorID = _T("");
	m_Name = _T("");
	m_RoomNo = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CEx28bSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Student Registration");
}

CString CEx28bSet::GetDefaultSQL()
{
	return _T("[Instructor]");
}

void CEx28bSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEx28bSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[InstructorID]"), m_InstructorID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[RoomNo]"), m_RoomNo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEx28bSet diagnostics

#ifdef _DEBUG
void CEx28bSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEx28bSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
