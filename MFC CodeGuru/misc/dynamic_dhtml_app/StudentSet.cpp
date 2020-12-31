// StudentSet.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "StudentSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudentSet

IMPLEMENT_DYNAMIC(CStudentSet, CRecordset)

CStudentSet::CStudentSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CStudentSet)
	m_StudentID = 0;
	m_Name = _T("");
	m_GradYear = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CStudentSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Student Registration");
}

CString CStudentSet::GetDefaultSQL()
{
	return _T("[Student]");
}

void CStudentSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CStudentSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[StudentID]"), m_StudentID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Int(pFX, _T("[GradYear]"), m_GradYear);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CStudentSet diagnostics

#ifdef _DEBUG
void CStudentSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStudentSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
