// CustSet.cpp : implementation file
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoSet.h"
#include "CustSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Tables informations

static TABLEFIELD CustomersField[] =
{
  { "CustomerID",   dbText,  5, FALSE, FALSE },
  { "CompanyName",  dbText, 40, TRUE,  FALSE },
  { "ContactName",  dbText, 30, FALSE, FALSE },
  { "ContactTitle", dbText, 30, FALSE, FALSE },
  { "Address",      dbText, 60, FALSE, FALSE },
  { "City",         dbText, 15, FALSE, FALSE },
  { "Region",       dbText, 15, FALSE, FALSE },
  { "PostalCode",   dbText, 10, FALSE, FALSE },
  { "Country",      dbText, 15, FALSE, FALSE },
  { "Phone",        dbText, 24, FALSE, FALSE },
  { "Fax",          dbText, 24, FALSE, FALSE },
  { 0 },
};

static const char* CustomersKey1[] = { "CustomerID" };
static const char* CustomersKey2[] = { "CompanyName" };
static const char* CustomersKey3[] = { "City" };
static const char* CustomersKey4[] = { "Region" };
static const char* CustomersKey5[] = { "PostalCode" };

static TABLEKEY CustomersKey[] =
{
  { 1, CustomersKey1, lpcsPrimaryKey, TRUE,  TRUE, TRUE },
  { 1, CustomersKey2, "CompanyName",  FALSE, TRUE, FALSE },
  { 1, CustomersKey3, "City",         FALSE, TRUE, FALSE },
  { 1, CustomersKey4, "Region",       FALSE, TRUE, FALSE },
  { 1, CustomersKey5, "PostalCode",   FALSE, TRUE, FALSE },
  { 0 },
};

TABLESET CustomersTable = { "Customers", CustomersField, CustomersKey };

/////////////////////////////////////////////////////////////////////////////
// CCustomersSet

IMPLEMENT_DYNAMIC(CCustomersSet, CDAORecordset)

CCustomersSet::CCustomersSet(CDaoDatabase* pdb)
	: CDAORecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCustomersSet)
	m_CustomerID = _T("");
	m_CompanyName = _T("");
	m_ContactName = _T("");
	m_ContactTitle = _T("");
	m_Address = _T("");
	m_City = _T("");
	m_Region = _T("");
	m_PostalCode = _T("");
	m_Country = _T("");
	m_Phone = _T("");
	m_Fax = _T("");
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;
}


CString CCustomersSet::GetDefaultDBName()
{
	// we must define a database
	ASSERT(FALSE);
	return _T("");
}

CString CCustomersSet::GetDefaultSQL()
{
	return _T("[Customers]");
}

void CCustomersSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCustomersSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[CustomerID]"), m_CustomerID);
	DFX_Text(pFX, _T("[CompanyName]"), m_CompanyName);
	DFX_Text(pFX, _T("[ContactName]"), m_ContactName);
	DFX_Text(pFX, _T("[ContactTitle]"), m_ContactTitle);
	DFX_Text(pFX, _T("[Address]"), m_Address);
	DFX_Text(pFX, _T("[City]"), m_City);
	DFX_Text(pFX, _T("[Region]"), m_Region);
	DFX_Text(pFX, _T("[PostalCode]"), m_PostalCode);
	DFX_Text(pFX, _T("[Country]"), m_Country);
	DFX_Text(pFX, _T("[Phone]"), m_Phone);
	DFX_Text(pFX, _T("[Fax]"), m_Fax);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCustomersSet diagnostics

#ifdef _DEBUG
void CCustomersSet::AssertValid() const
{
	CDAORecordset::AssertValid();
}

void CCustomersSet::Dump(CDumpContext& dc) const
{
	CDAORecordset::Dump(dc);
}
#endif //_DEBUG
