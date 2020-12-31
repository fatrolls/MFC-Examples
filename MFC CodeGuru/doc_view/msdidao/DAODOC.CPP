// DaoDoc.cpp : implementation of the CMSDIDaoDoc class
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoBmp.h"
#include "DaoSet.h"
#include "CategSet.h"
#include "CustSet.h"

#include "DaoDoc.h"

#include "TblView.h"
#include "CategTbl.h"
#include "CustTbl.h"

#include "CategVw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// helpers

static BOOL FileExist(LPCSTR lpszFileName)
{
  OFSTRUCT OpenBuffer;
  OpenFile(lpszFileName, &OpenBuffer, OF_EXIST);
  return (OpenBuffer.nErrCode == 0x0000) ? TRUE: FALSE;
}

int DaoMessageBox(CDaoException* e, UINT nType, UINT nIDHelp)
{
  return AfxMessageBox(e->m_pErrorInfo->m_strDescription, nType|MB_ICONEXCLAMATION, nIDHelp);
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoDoc

IMPLEMENT_DYNCREATE(CMSDIDaoDoc, CDocument)

BEGIN_MESSAGE_MAP(CMSDIDaoDoc, CDocument)
	//{{AFX_MSG_MAP(CMSDIDaoDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_TABLE_CATEG, OnTableCategories)
	ON_COMMAND(ID_TABLE_CUSTOM, OnTableCustomers)
	ON_COMMAND(ID_FORM_CATEG, OnFormCateg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoDoc construction/destruction

CMSDIDaoDoc::CMSDIDaoDoc()
{
	m_pCategoriesSet = NULL;
	m_pCustomersSet = NULL;
	// ... ADDALL
}

CMSDIDaoDoc::~CMSDIDaoDoc()
{
}

BOOL CMSDIDaoDoc::OnNewDocument()
{
	ASSERT(!m_db.IsOpen());

	if (!CDocument::OnNewDocument())
		return FALSE;

	// MSDIDAO: prompt for a file name to create a new document
	return DoSave(NULL);
}

void CMSDIDaoDoc::OnCloseDocument() 
{
	// database is closed in the DeleteContents
	CDocument::OnCloseDocument();
}

BOOL CMSDIDaoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// MSDIDAO: OnOpenNewDocument()
	try
	{
		m_db.Open(lpszPathName);
	}
	catch (CDaoException* e)
	{
		DaoMessageBox(e);
		e->Delete();
		return FALSE;
	}
	DeleteContents();
	SetModifiedFlag(FALSE); // start with unmodified
	return TRUE;
}

BOOL CMSDIDaoDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// MSDIDAO: OnSaveDocument()
	CString strPathName = GetPathName();

	// if pathname is empty, create à new document
	if (strPathName.IsEmpty())
	  return CreateNewDatabase(lpszPathName);

	// if new file name, create a new document with the old
	if (CString(lpszPathName) != strPathName)
	{
          ASSERT(m_db.IsOpen());
	  try
	  {
	    CWaitCursor cursorWait;
	    m_db.Close();
	    if (FileExist(lpszPathName))
	      CFile::Remove(lpszPathName);
	    CDaoWorkspace WorkSpace;
	    WorkSpace.Open();
	    WorkSpace.CompactDatabase(GetPathName(), lpszPathName);
	    WorkSpace.Close();
	    m_db.Open(lpszPathName);
	  }
	  catch (CDaoException* e)
	  {
	    DaoMessageBox(e);
	    e->Delete();
	    return FALSE;
	  }
	}
	return TRUE;
}

void CMSDIDaoDoc::DeleteContents() 
{
	// MSDIDAO: DeleteContents()
	CDocument::DeleteContents();
	CloseDataBase();
}

BOOL CMSDIDaoDoc::CreateNewDatabase(LPCTSTR lpszPathName)
{
	// MSDIDAO: CreateNewDatabase()

	// close database if opened
	ASSERT(!m_db.IsOpen());
	if (m_db.IsOpen()) m_db.Close();

	// remove the old file berfore creating the new one
	if (FileExist(lpszPathName))
	  CFile::Remove(lpszPathName);

	try
	{
	  m_db.Create(lpszPathName, dbLangGeneral);
	}
	catch (CDaoException* e)
	{
	  DaoMessageBox(e);
	  e->Delete();
	  return FALSE;
	}
	return TRUE;
}

void CMSDIDaoDoc::CloseDataBase()
{
  // to close all recordset
  while (m_pCategoriesSet) CloseCategories();
  while (m_pCustomersSet) CloseCustomers();
  // ... ADDALL
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoDoc serialization

void CMSDIDaoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoDoc diagnostics

#ifdef _DEBUG
void CMSDIDaoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMSDIDaoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoDoc Create tables

static void CreateKeys(CDaoTableDef* pDaoTableDef, TABLEKEY* pKeyInfo)
{
  CDaoIndexInfo IdxInfo;
  // Defaults values
  IdxInfo.m_bClustered = FALSE;
  IdxInfo.m_bIgnoreNulls = FALSE;
  IdxInfo.m_bForeign = FALSE;

  for (int i = 0; pKeyInfo[i].nFields; i++)
  {
    CDaoIndexFieldInfo* pFieldInfo = new CDaoIndexFieldInfo[pKeyInfo[i].nFields];
    IdxInfo.m_pFieldInfos = pFieldInfo;
    IdxInfo.m_nFields = pKeyInfo[i].nFields;
    for (int j = 0; j < IdxInfo.m_nFields; j++)
    {
      pFieldInfo[j].m_strName = pKeyInfo[i].FieldInfoName[j];
      pFieldInfo[j].m_bDescending = FALSE;
    }
    IdxInfo.m_strName = pKeyInfo[i].strName;
    IdxInfo.m_bPrimary = pKeyInfo[i].bPrimary;
    IdxInfo.m_bUnique = pKeyInfo[i].bUnique;
    IdxInfo.m_bRequired = pKeyInfo[i].bRequired;
    pDaoTableDef->CreateIndex(IdxInfo);
    delete [] pFieldInfo;
  }
}

void CreateFieldInfo(CDaoTableDef* pDaoTableDef, LPCTSTR lpszName, short nType,
  long lSize, BOOL bRequired, BOOL bAllowZero, long lAttributes = 0)
{
  CDaoFieldInfo fieldinfo;

  // Initialize everything so only correct properties will be set
  fieldinfo.m_strName = lpszName;
  fieldinfo.m_nType = nType;
  fieldinfo.m_lSize = lSize;
  fieldinfo.m_lAttributes = lAttributes;
  fieldinfo.m_nOrdinalPosition = 0;
  fieldinfo.m_bRequired = bRequired;
  fieldinfo.m_bAllowZeroLength = bAllowZero;
  fieldinfo.m_lCollatingOrder = 0;
  pDaoTableDef->CreateField(fieldinfo);
}

static void CreateTableDef(CDaoTableDef* pDaoTableDef, LPCSTR lpcsTableName, TABLEFIELD* pFieldInfo)
{
  pDaoTableDef->Create(lpcsTableName);
  for (int i = 0; pFieldInfo[i].FieldID; i++)
    CreateFieldInfo(pDaoTableDef, pFieldInfo[i].FieldID,
      pFieldInfo[i].Type, pFieldInfo[i].Len, 
	pFieldInfo[i].bRequired, pFieldInfo[i].bAllowZero);
}

void CMSDIDaoDoc::CreateTable(LPCSTR lpcsTableName, TABLEFIELD* pFieldInfo, TABLEKEY* pKeyInfo)
{
  ASSERT(m_db.IsOpen());
  CDaoTableDef DaoTableDef(&m_db);
  try
  {
    // Create the table
    CWaitCursor waitCursor;
    DaoTableDef.Create(lpcsTableName);
    CreateTableDef(&DaoTableDef, lpcsTableName, pFieldInfo);
    CreateKeys(&DaoTableDef, pKeyInfo);
    DaoTableDef.Append();
    DaoTableDef.Close();
  }
  catch (CDaoException* e)
  {
    DaoMessageBox(e);
    e->Delete();
  }
}

BOOL CMSDIDaoDoc::TableExist(LPCSTR lpcsTableName)
{
	CDaoTableDef TableDef(&m_db);
	try
	{
	  TableDef.Open(lpcsTableName);
	  TableDef.Close();
	}
	catch (CDaoException* e)
	{
	  e->Delete();
	  return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoDoc Open/Close tables

CCategoriesSet* CMSDIDaoDoc::OpenCategories()
{
  // create table if not exist
  if (!TableExist(CategoriesTable.lpcsTableName))
    CreateTable(CategoriesTable.lpcsTableName, CategoriesTable.pFieldInfo, CategoriesTable.pKeyInfo);

  // create record set if not exist
  if (m_pCategoriesSet == NULL)
    m_pCategoriesSet = new CCategoriesSet(&m_db);

  // open table
  for (;;)
  {
    try
    {
      m_pCategoriesSet->Open();
      break;
    }
    catch (CDaoException* e)
    {
      DaoMessageBox(e);
      e->Delete();
      if (AfxMessageBox(IDS_ERROR_OPEN_TABLE, MB_YESNO) == IDNO)
      {
	delete m_pCategoriesSet;
	m_pCategoriesSet = NULL;
	break;
      }
    }
    if (m_pCategoriesSet->IsOpen()) m_pCategoriesSet->Close();
    m_db.DeleteTableDef(CategoriesTable.lpcsTableName);
    CreateTable(CategoriesTable.lpcsTableName, CategoriesTable.pFieldInfo, CategoriesTable.pKeyInfo);
  }
  return m_pCategoriesSet;
}

void CMSDIDaoDoc::CloseCategories()
{
  if (m_pCategoriesSet != NULL)
  {
    m_pCategoriesSet->Close();
    if (m_pCategoriesSet->m_OpenCount == 0)
    {
      delete m_pCategoriesSet;
      m_pCategoriesSet = NULL;
    }
  }
}

CCustomersSet* CMSDIDaoDoc::OpenCustomers()
{
  // create table if not exist
  if (!TableExist(CustomersTable.lpcsTableName))
    CreateTable(CustomersTable.lpcsTableName, CustomersTable.pFieldInfo, CustomersTable.pKeyInfo);

  // create record set if not exist
  if (m_pCustomersSet == NULL)
    m_pCustomersSet = new CCustomersSet(&m_db);

  // open table
  for (;;)
  {
    try
    {
      m_pCustomersSet->Open();
      break;
    }
    catch (CDaoException* e)
    {
      DaoMessageBox(e);
      e->Delete();
      if (AfxMessageBox(IDS_ERROR_OPEN_TABLE, MB_YESNO) == IDNO)
      {
	delete m_pCustomersSet;
	m_pCustomersSet = NULL;
	break;
      }
    }
    if (m_pCustomersSet->IsOpen()) m_pCustomersSet->Close();
    m_db.DeleteTableDef(CustomersTable.lpcsTableName);
    CreateTable(CustomersTable.lpcsTableName, CustomersTable.pFieldInfo, CustomersTable.pKeyInfo);
  }
  return m_pCustomersSet;
}

void CMSDIDaoDoc::CloseCustomers()
{
  if (m_pCustomersSet != NULL)
  {
    m_pCustomersSet->Close();
    if (m_pCustomersSet->m_OpenCount == 0)
    {
      delete m_pCustomersSet;
      m_pCustomersSet = NULL;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoDoc commands

void CMSDIDaoDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// save only the current table, not the document
	pCmdUI->Enable(FALSE);
}

void CMSDIDaoDoc::OnTableCategories() 
{
	theApp.CreateOrActivateFrame(RUNTIME_CLASS(CCategoriesTable), this);
}

void CMSDIDaoDoc::OnTableCustomers() 
{
	theApp.CreateOrActivateFrame(RUNTIME_CLASS(CCustomersTable), this);
}

void CMSDIDaoDoc::OnFormCateg() 
{
	theApp.CreateOrActivateFrame(RUNTIME_CLASS(CCategoriesView), this);
}
