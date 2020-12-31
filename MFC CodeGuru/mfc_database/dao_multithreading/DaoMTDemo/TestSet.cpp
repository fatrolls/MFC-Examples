// TestSet.cpp : implementation file
//

#include "stdafx.h"
#include "DaoMTDemo.h"
#include "TestSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestSet

IMPLEMENT_DYNAMIC(CTestSet, CDaoRecordset)

CTestSet::CTestSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTestSet)
	m_test_number = 0;
	m_test_string = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CTestSet::GetDefaultDBName()
{
	return _T("test.mdb");
}

CString CTestSet::GetDefaultSQL()
{
	return _T("[test_table]");
}

void CTestSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTestSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Short(pFX, _T("[test_number]"), m_test_number);
	DFX_Text(pFX, _T("[test_string]"), m_test_string);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTestSet diagnostics

#ifdef _DEBUG
void CTestSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CTestSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
