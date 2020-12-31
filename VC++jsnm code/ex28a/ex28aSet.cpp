// ex28aSet.cpp : implementation file
//

#include "stdafx.h"
#include "ex28a.h"
#include "ex28aset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28aSet

IMPLEMENT_DYNAMIC(CEx28aSet, CRecordset)

CEx28aSet::CEx28aSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEx28aSet)
	m_StudentID = 0;
	m_Name = _T("");
	m_GradYear = 0;
	m_CourseID = _T("");
	m_Grade = _T("");
	m_SectionNo = _T("");
	m_StudentID2 = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CEx28aSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Student Registration");
}

CString CEx28aSet::GetDefaultSQL()
{
	return _T("[Student],[Enrollment]");
}

void CEx28aSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEx28aSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Student].[StudentID]"), m_StudentID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Int(pFX, _T("[GradYear]"), m_GradYear);
	RFX_Text(pFX, _T("[CourseID]"), m_CourseID);
	RFX_Text(pFX, _T("[Grade]"), m_Grade);
	RFX_Text(pFX, _T("[SectionNo]"), m_SectionNo);
	RFX_Long(pFX, _T("[StudentID]"), m_StudentID2);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEx28aSet diagnostics

#ifdef _DEBUG
void CEx28aSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEx28aSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
