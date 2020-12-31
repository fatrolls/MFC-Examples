// InstructorSet.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "InstructorSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstructorSet

IMPLEMENT_DYNAMIC(CInstructorSet, CRecordset)

CInstructorSet::CInstructorSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CInstructorSet)
	m_InstructorID = _T("");
	m_Name = _T("");
	m_RoomNo = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CInstructorSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Student Registration");
}

CString CInstructorSet::GetDefaultSQL()
{
	return _T("[Instructor]");
}

void CInstructorSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CInstructorSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[InstructorID]"), m_InstructorID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[RoomNo]"), m_RoomNo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CInstructorSet diagnostics

#ifdef _DEBUG
void CInstructorSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CInstructorSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
