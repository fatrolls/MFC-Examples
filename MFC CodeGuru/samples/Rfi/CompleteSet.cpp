// CompleteSet.cpp : implementation file
//

#include "stdafx.h"
#include "Rfi.h"
#include "CompleteSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompleteSet

IMPLEMENT_DYNAMIC(CCompleteSet, CDaoRecordset)

CCompleteSet::CCompleteSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCompleteSet)
	m_lID = 0;
	m_strCity = _T("");
	m_strState = _T("");
	m_strFrequency = _T("");
	m_strInput = _T("");
	m_strCallsign = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_strSort = "";
	m_strFilter = "";
}


CString CCompleteSet::GetDefaultDBName()
{
	return _T("rfi.mdb");
}

CString CCompleteSet::GetDefaultSQL()
{
	return _T("[Repeaters]");
}

void CCompleteSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCompleteSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_lID);
	DFX_Text(pFX, _T("[City]"), m_strCity);
	DFX_Text(pFX, _T("[State]"), m_strState);
	DFX_Text(pFX, _T("[Frequency]"), m_strFrequency);
	DFX_Text(pFX, _T("[Input]"), m_strInput);
	DFX_Text(pFX, _T("[Callsign]"), m_strCallsign);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCompleteSet diagnostics

#ifdef _DEBUG
void CCompleteSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CCompleteSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
