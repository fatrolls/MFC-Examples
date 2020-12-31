// ex28cSet.cpp : implementation of the CEx28cSet class
//

#include "stdafx.h"
#include "ex28c.h"
#include "ex28cSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28cSet implementation

IMPLEMENT_DYNAMIC(CEx28cSet, CRecordset)

CEx28cSet::CEx28cSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEx28cSet)
	m_InstructorID = _T("");
	m_Name = _T("");
	m_RoomNo = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CEx28cSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Student Registration");
}

CString CEx28cSet::GetDefaultSQL()
{
	return _T("[Instructor]");
}

void CEx28cSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEx28cSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[InstructorID]"), m_InstructorID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[RoomNo]"), m_RoomNo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEx28cSet diagnostics

#ifdef _DEBUG
void CEx28cSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEx28cSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
