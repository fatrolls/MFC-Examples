// CategSet.cpp : implementation file
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoBmp.h"
#include "DaoSet.h"
#include "CategSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Tables informations

static TABLEFIELD CategoriesField[] =
{
  { "CategoryID",   dbLong,       0, FALSE, FALSE },
  { "CategoryName", dbText,      15, TRUE,  FALSE },
  { "Description",  dbMemo,       0, FALSE, FALSE },
  { "Picture",      dbLongBinary, 0, FALSE, FALSE },
  { 0 },
};

static const char* CategoriesKey1[] = { "CategoryID" };
static const char* CategoriesKey2[] = { "CategoryName" };

static TABLEKEY CategoriesKey[] =
{
  { 1, CategoriesKey1, lpcsPrimaryKey, TRUE, TRUE, TRUE },
  { 1, CategoriesKey2, "CategoryName", FALSE, TRUE, FALSE },
  { 0 },
};

TABLESET CategoriesTable = { "Categories", CategoriesField, CategoriesKey };
  
/////////////////////////////////////////////////////////////////////////////
// CCategoriesSet

IMPLEMENT_DYNAMIC(CCategoriesSet, CDAORecordset)

CCategoriesSet::CCategoriesSet(CDaoDatabase* pdb)
	: CDAORecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCategoriesSet)
	m_CategoryID = 0;
	m_CategoryName = _T("");
	m_Description = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;
}

CString CCategoriesSet::GetDefaultDBName()
{
	// we must define a database
	ASSERT(FALSE);
	return _T("");
}

CString CCategoriesSet::GetDefaultSQL()
{
	return _T("[Categories]");
}

void CCategoriesSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCategoriesSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Long(pFX, _T("[CategoryID]"), m_CategoryID);
	DFX_Text(pFX, _T("[CategoryName]"), m_CategoryName);
	DFX_Text(pFX, _T("[Description]"), m_Description);
	DFX_LongBinary(pFX, _T("[Picture]"), m_Picture);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCategoriesSet diagnostics

#ifdef _DEBUG
void CCategoriesSet::AssertValid() const
{
	CDAORecordset::AssertValid();
}

void CCategoriesSet::Dump(CDumpContext& dc) const
{
	CDAORecordset::Dump(dc);
}
#endif //_DEBUG
