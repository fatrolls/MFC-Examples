// ClientsRecordset.cpp : implementation file
//

#include "stdafx.h"
#include "Pizza.h"
#include "ClientsRecordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientsRecordset

IMPLEMENT_DYNAMIC(CClientsRecordset, CDaoRecordset)

CClientsRecordset::CClientsRecordset(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CClientsRecordset)
	m_id = 0;
	m_SurName = _T("");
	m_SecondName = _T("");
	m_Address = _T("");
	m_AddrNo = _T("");
	m_Phone = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
	m_strSort = "SurName, SecondName, Address, AddrNo, Phone";
}


CString CClientsRecordset::GetDefaultDBName()
{
	return _T("Clients.mdb");
}

CString CClientsRecordset::GetDefaultSQL()
{
	return _T("[Clients]");
}

void CClientsRecordset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CClientsRecordset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[id]"), m_id);
	DFX_Text(pFX, _T("[SurName]"), m_SurName);
	DFX_Text(pFX, _T("[SecondName]"), m_SecondName);
	DFX_Text(pFX, _T("[Address]"), m_Address);
	DFX_Text(pFX, _T("[AddrNo]"), m_AddrNo);
	DFX_Text(pFX, _T("[Phone]"), m_Phone);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CClientsRecordset diagnostics

#ifdef _DEBUG
void CClientsRecordset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CClientsRecordset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
