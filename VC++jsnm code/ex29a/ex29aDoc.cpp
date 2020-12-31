// ex29adoc.cpp : implementation of the CEx29aDoc class
//

#include "stdafx.h"
#include "ex29a.h"

#include "ex29adoc.h"
#include "MainFrm.h"
#include "tablesel.h"
#include "IsamSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// global helper function to display an error message
void DaoErrorMsg(CDaoException* e)
{
    char errorMsg[301];
   	wsprintf(errorMsg, "DAO error %d, SOURCE = %s, DESCR = %s",
        e->m_pErrorInfo->m_lErrorCode,
        (const char*) e->m_pErrorInfo->m_strSource,
        (const char*) e->m_pErrorInfo->m_strDescription);
   	AfxMessageBox(errorMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CEx29aDoc

IMPLEMENT_DYNCREATE(CEx29aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx29aDoc, CDocument)
    //{{AFX_MSG_MAP(CEx29aDoc)
    ON_COMMAND(IDC_REQUERY, OnRequery)
    ON_UPDATE_COMMAND_UI(IDC_REQUERY, OnUpdateRequery)
    ON_COMMAND(ID_FILE_DAOOPEN_MDB, OnFileDaoOpenMdb)
    ON_COMMAND(ID_FILE_DAOOPEN_ODBC, OnFileDaoOpenOdbc)
    ON_UPDATE_COMMAND_UI(ID_FILE_DAOOPEN_MDB, OnUpdateFileDaoOpen)
	ON_COMMAND(ID_FILE_DAOOPEN_ISAM, OnFileDaoOpenIsam)
    ON_UPDATE_COMMAND_UI(ID_FILE_DAOOPEN_ODBC, OnUpdateFileDaoOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSave)
    ON_UPDATE_COMMAND_UI(ID_FILE_DAOOPEN_ISAM, OnUpdateFileDaoOpen)
	ON_COMMAND(ID_FILE_DAODISCONNECT, OnFileDaoDisconnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_DAODISCONNECT, OnUpdateFileDaoDisconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx29aDoc construction/destruction

CEx29aDoc::CEx29aDoc()
{
    m_bConnected = FALSE;
    m_pRecordset = NULL;
    m_nFields = 0;
    m_nRowCount = 0;
	m_nDatabaseType = UNK;
}

CEx29aDoc::~CEx29aDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
void CEx29aDoc::DeleteContents()
{
}       

/////////////////////////////////////////////////////////////////////////////
BOOL CEx29aDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;
    m_strDatabase.Empty(); // in case we're SDI
    m_strConnect.Empty();
    m_strQuery.Empty();
    return TRUE;
}


BOOL CEx29aDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
    if (!CDocument::OnOpenDocument(lpszPathName))
        return FALSE;
    PutQuery();
	switch (m_nDatabaseType) {
	case UNK:
		break;
	case MDB:
		DaoOpenMdb();
		break;
	case ISAM:
		DaoOpenIsam();
		break;
	case ODBC:
		DaoOpenOdbc();
		break;
	}
	return TRUE;
}

void CEx29aDoc::OnCloseDocument() 
{
    m_strQuery.Empty();
    PutQuery();
    if (m_bConnected) {
      delete m_pRecordset; // Destructor calls Close
      m_database.Close();
      m_bConnected = FALSE;
      m_pRecordset = NULL;
	  m_nRowCount = 0;
    }
    CDocument::OnCloseDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CEx29aDoc serialization

void CEx29aDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
     	ar << (int) m_nDatabaseType << m_strDatabase << m_strConnect << m_strQuery;
    }
    else {
    	ar >> (int&) m_nDatabaseType >> m_strDatabase >> m_strConnect >> m_strQuery;
    }
}


/////////////////////////////////////////////////////////////////////////////
// CEx29aDoc diagnostics

#ifdef _DEBUG
void CEx29aDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CEx29aDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
void CEx29aDoc::GetQuery()
{    // get SQL string from dialog bar
	char text[201];   
    CDialogBar& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndQueryBar;
    rBar.GetDlgItemText(IDC_QUERY, text, 200);
    m_strQuery = text;
}

void CEx29aDoc::PutQuery()
{    // write SQL string to dialog bar
    CDialogBar& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndQueryBar;
    rBar.SetDlgItemText(IDC_QUERY, m_strQuery);
}

void CEx29aDoc::GetFieldSpecs()
{
	m_nFields = (int) m_pRecordset->GetFieldCount();
	m_arrayFieldName.SetSize(m_nFields);
	m_arrayFieldSize.SetSize(m_nFields);
	CDaoFieldInfo fi;
	for(int i = 0; i < m_nFields; i++) {
		m_pRecordset->GetFieldInfo(i, fi);
		m_arrayFieldName[i] = fi.m_strName;
		m_arrayFieldSize[i] = (short) max(min(fi.m_lSize, 50),
								fi.m_strName.GetLength());
		TRACE("field name = %s\n", fi.m_strName);
	}
}

// helper used by OnFileDaoOpenMdb, OnFileDaoOpenIsam, and OnFileDaoOpenOdbc
void CEx29aDoc::OpenRecordset()
{
    GetQuery();
    if (m_strQuery.IsEmpty()) {
      CTableSelect tableDlg(&m_database);
      if (tableDlg.DoModal() != IDOK) {
        m_database.Close();  // escape route
        return;
      }
      
	  m_strQuery.Format("select * from [%s]", tableDlg.m_strSelection);
      PutQuery();
    }

    m_pRecordset = new CDaoRecordset(&m_database);
    try {	
      m_pRecordset->Open(dbOpenDynaset, m_strQuery, dbReadOnly);
    }
    catch (CDaoException* e) {
      ::DaoErrorMsg(e);
      UpdateAllViews(NULL);
      m_bConnected = FALSE;
      e->Delete();
      return;
    }
    if (!m_pRecordset->IsBOF()) {
	  // might be expensive for a really big table
	  // View adjusts its m_nRowCount if you supply a big value here
      m_pRecordset->MoveLast(); // to validate record count
    }
    m_nRowCount = m_pRecordset->GetAbsolutePosition() + 2;
    TRACE("m_nRowCount = %d\n", m_nRowCount);
    GetFieldSpecs();
    UpdateAllViews(NULL);
    m_bConnected = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx29aDoc commands

/////////////////////////////////////////////////////////////////////////////
void CEx29aDoc::OnRequery()
{ 
    GetQuery();
    // Requery won't work because we're changing the SQL statement
    BeginWaitCursor();
	if(m_pRecordset->IsOpen()) {
		m_pRecordset->Close();
	}
    try {	
      m_pRecordset->Open(dbOpenDynaset, m_strQuery, dbReadOnly);
    }
    catch (CDaoException* e) {
      ::DaoErrorMsg(e);
	  m_nRowCount = 0;
      UpdateAllViews(NULL);
      EndWaitCursor();
      e->Delete();
      return;
    }
    if (!m_pRecordset->IsBOF()) {
      m_pRecordset->MoveLast(); // to validate record count
    }
    m_nRowCount = m_pRecordset->GetAbsolutePosition() + 2;
    TRACE("m_nRowCount = %d\n", m_nRowCount);
    GetFieldSpecs();
    UpdateAllViews(NULL); 
    EndWaitCursor();
}

/////////////////////////////////////////////////////////////////////////////
void CEx29aDoc::OnUpdateRequery(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_bConnected);
}

void CEx29aDoc::OnFileDaoOpenMdb()
{
	m_strDatabase.Empty();
    m_strQuery.Empty();
	DaoOpenMdb();
}

void CEx29aDoc::DaoOpenMdb()
{
    if (m_strDatabase.IsEmpty()) {
      CFileDialog dlg(TRUE, ".mdb", "*.mdb");
      if (dlg.DoModal() == IDCANCEL) return;
      m_strDatabase = dlg.GetPathName();
    }
    BeginWaitCursor();
    try {
      // nonexclusive, read-only
      m_database.Open(m_strDatabase, FALSE, TRUE);
    }
    catch (CDaoException* e) {
      ::DaoErrorMsg(e);
      EndWaitCursor();
      e->Delete();
      return;
    }
    m_strDatabase = m_database.GetName();
    TRACE("database name = %s, connect = %s\n",
         (const char*) m_strDatabase, (const char*) m_strConnect);
    OpenRecordset();
	m_nDatabaseType = MDB;
    EndWaitCursor();
}

void CEx29aDoc::OnFileDaoOpenOdbc()
{
	m_strConnect.Empty();
    m_strQuery.Empty();
	DaoOpenOdbc();
}

void CEx29aDoc::DaoOpenOdbc()
{
    // can't open ODBC using Access driver
    if (m_strConnect.IsEmpty()) {
      m_strConnect = "ODBC;";
    }
    BeginWaitCursor();
    try {
      // nonexclusive, read-only
      m_database.Open("", FALSE, TRUE, m_strConnect);
    }
    catch (CDaoException* e) {
      ::DaoErrorMsg(e);
      EndWaitCursor();
      e->Delete();
      return;
    }
    m_strConnect = m_database.GetConnect();
    TRACE("database name = %s, connect = %s\n",
        (const char*) m_strDatabase,
        (const char*) m_strConnect);
    OpenRecordset();
	m_nDatabaseType = ODBC;
    EndWaitCursor();
}

void CEx29aDoc::OnFileDaoOpenIsam() 
{
	m_strConnect.Empty();
    m_strQuery.Empty();
	DaoOpenIsam();
}

void CEx29aDoc::DaoOpenIsam() 
{
    BeginWaitCursor();
    if (m_strConnect.IsEmpty()) {
      CIsamSelect isamDlg;
      if (isamDlg.DoModal() != IDOK) {
        return;
      }
      m_strConnect = isamDlg.m_strIsam + ";DATABASE=" +
          isamDlg.m_strDirectory;
      TRACE("m_strConnect = %s\n", (const char*) m_strConnect);
    }
    try {
      // nonexclusive, read-only
      m_database.Open("", FALSE, TRUE, m_strConnect);
    }
    catch(CDaoException* e) {
      ::DaoErrorMsg(e);
      EndWaitCursor();
      e->Delete();
      return;
    }
    m_strConnect = m_database.GetConnect();
    TRACE("database name = %s, connect = %s\n",
         (const char*) m_strDatabase, (const char*) m_strConnect);
    OpenRecordset();
	m_nDatabaseType = ISAM;
    EndWaitCursor();
}

void CEx29aDoc::OnUpdateFileDaoOpen(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_bConnected);
}

void CEx29aDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_bConnected);
}

void CEx29aDoc::OnFileDaoDisconnect() 
{
    if (m_bConnected) {
      delete m_pRecordset; // Destructor calls Close
      m_database.Close();
      m_bConnected = FALSE;
      m_pRecordset = NULL;
	  m_nRowCount = 0;
	  UpdateAllViews(NULL);
    }
}

void CEx29aDoc::OnUpdateFileDaoDisconnect(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_bConnected);
}
