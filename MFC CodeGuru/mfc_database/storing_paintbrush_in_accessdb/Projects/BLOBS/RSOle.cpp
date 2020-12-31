// RSOle.cpp : implementation file
//

#include "stdafx.h"
#include "BLOBS.h"
#include "RSOle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RSOle

IMPLEMENT_DYNAMIC(RSOle, CDaoRecordset)

RSOle::RSOle(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(RSOle)
	m_ID = 0;
	m_SomeText = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString RSOle::GetDefaultDBName()
{
	return _T("E:\\Projects\\BLOBS\\BLOBS.mdb");
}

CString RSOle::GetDefaultSQL()
{
	return _T("[Table]");
}

void RSOle::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(RSOle)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[ID]"), m_ID);
	DFX_Text(pFX, _T("[SomeText]"), m_SomeText);
	DFX_Binary(pFX, _T("[Images]"), m_Images);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// RSOle diagnostics

#ifdef _DEBUG
void RSOle::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void RSOle::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
