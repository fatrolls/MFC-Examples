// ex28dDoc.cpp : implementation of the CEx28dDoc class
//

#include "stdafx.h"
#include "ex28d.h"

#include "ex28dDoc.h"
#include "MainFrm.h"
#include "TableSel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28dDoc

IMPLEMENT_DYNCREATE(CEx28dDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx28dDoc, CDocument)
	//{{AFX_MSG_MAP(CEx28dDoc)
    ON_COMMAND(IDC_REQUERY, OnRequery)
    ON_UPDATE_COMMAND_UI(IDC_REQUERY, OnUpdateRequery)
	ON_COMMAND(ID_FILE_ODBCCONNECT, OnFileOdbcConnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_ODBCCONNECT, OnUpdateFileOdbcConnect)
	ON_COMMAND(ID_FILE_ODBCDISCONNECT, OnFileOdbcDisconnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_ODBCDISCONNECT, OnUpdateFileOdbcDisconnect)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx28dDoc construction/destruction

CEx28dDoc::CEx28dDoc()
{
    m_bConnected = FALSE;
    m_pRecordset = NULL;
    m_nFields = 0;
    m_nRowCount = 0;
}

CEx28dDoc::~CEx28dDoc()
{
}

BOOL CEx28dDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
    m_strConnect.Empty(); // in case we're SDI
    m_strQuery.Empty();
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEx28dDoc serialization

void CEx28dDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
     	ar << m_strConnect << m_strQuery;
    }
    else {
    	ar >> m_strConnect >> m_strQuery;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CEx28dDoc diagnostics

#ifdef _DEBUG
void CEx28dDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx28dDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28dDoc commands

BOOL CEx28dDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
    PutQuery();
	OpenOdbc();
	return TRUE;
}

void CEx28dDoc::OnCloseDocument() 
{
    m_strQuery.Empty();
    PutQuery();
    if (m_bConnected) {
      delete m_pRecordset; // destructor calls Close
      m_database.Close();
      m_bConnected = FALSE;
      m_pRecordset = NULL;
	  m_nRowCount = 0;
    }
	CDocument::OnCloseDocument();
}

void CEx28dDoc::GetQuery()
{    // get SQL string from dialog bar
	char text[201];   
    CDialogBar& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndQueryBar;
    rBar.GetDlgItemText(IDC_QUERY, text, 200);
	TRACE("GetQuery - text = %s\n", text);
    m_strQuery = text;
}

void CEx28dDoc::PutQuery()
{    // write SQL string to dialog bar
    CDialogBar& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndQueryBar;
    rBar.SetDlgItemText(IDC_QUERY, m_strQuery);
}

void CEx28dDoc::GetFieldSpecs()
{
	m_nFields = (int) m_pRecordset->GetODBCFieldCount();
	m_arrayFieldName.SetSize(m_nFields);
	m_arrayFieldSize.SetSize(m_nFields);
	CODBCFieldInfo fi;
	for(int i = 0; i < m_nFields; i++) {
		m_pRecordset->GetODBCFieldInfo(i, fi);
		m_arrayFieldName[i] = fi.m_strName;
		if(fi.m_nSQLType == SQL_DATE) {
			m_arrayFieldSize[i] = 15;
		}
		else {
			m_arrayFieldSize[i] = (short) max(min((short) fi.m_nPrecision, 50),
								fi.m_strName.GetLength());
		}
		TRACE("field name = %s, type = %d, precision = %d, scale = %d\n",
			fi.m_strName, fi.m_nSQLType, fi.m_nPrecision, fi.m_nScale);
	}
}

void CEx28dDoc::OnRequery()
{ 
    GetQuery();
    // Requery won't work because we're changing the SQL statement
    BeginWaitCursor();
	if(m_pRecordset->IsOpen()) {
		m_pRecordset->Close();
	}
    try {	
      m_pRecordset->Open(CRecordset::dynaset, m_strQuery, CRecordset::readOnly);
    }
    catch (CDBException* pe) {
	  AfxMessageBox(pe->m_strError);
	  m_nRowCount = 0;
      UpdateAllViews(NULL);
      EndWaitCursor();
      pe->Delete();
      return;
    }
    if (!m_pRecordset->IsBOF()) {
		while(!m_pRecordset->IsEOF()) {
			m_pRecordset->MoveNext(); // to validate record count
		}
    }	
    m_nRowCount = m_pRecordset->GetRecordCount() + 1;
    TRACE("m_nRowCount = %d\n", m_nRowCount);
    GetFieldSpecs();
    UpdateAllViews(NULL); 
    EndWaitCursor();
}

/////////////////////////////////////////////////////////////////////////////
void CEx28dDoc::OnUpdateRequery(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_bConnected);
}

void CEx28dDoc::OnFileOdbcConnect()
{
	m_strConnect.Empty();
    m_strQuery.Empty();
	OpenOdbc();
}

void CEx28dDoc::OpenOdbc()
{
    // can't open ODBC via Access driver
    if (m_strConnect.IsEmpty()) {
      m_strConnect = "ODBC;";
    }
    BeginWaitCursor();
	BOOL bRet;
    try {
      // non-exclusive, read-only, no cursor library (dynaset)
        bRet = m_database.Open("", FALSE, TRUE, m_strConnect, FALSE);
//		bRet = m_database.OpenEx(m_strConnect, CDatabase::openReadOnly);
   }
    catch (CDBException* pe) {
	  AfxMessageBox(pe->m_strError);
      EndWaitCursor();
      pe->Delete();
      return;
    }
	if(bRet) {
		m_strConnect = m_database.GetConnect();
		TRACE("connect = %s\n", m_strConnect);
		OpenRecordset();
	}
    EndWaitCursor();
}

// helper used by OnFileOdbcConnect
void CEx28dDoc::OpenRecordset()
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

    m_pRecordset = new CRecordset(&m_database);
    try {	
      m_pRecordset->Open(CRecordset::dynaset, m_strQuery, CRecordset::readOnly);
    }
    catch (CDBException* pe) {
	  AfxMessageBox(pe->m_strError);
      UpdateAllViews(NULL);
      m_bConnected = FALSE;
      pe->Delete();
      return;
    }
	if (!m_pRecordset->IsBOF()) {
		while(!m_pRecordset->IsEOF()) {
			m_pRecordset->MoveNext(); // to validate record count
		}
	}
	m_nRowCount = m_pRecordset->GetRecordCount() + 1;
    TRACE("m_nRowCount = %d\n", m_nRowCount);
    GetFieldSpecs();
    UpdateAllViews(NULL);
    m_bConnected = TRUE;
}

void CEx28dDoc::OnUpdateFileOdbcConnect(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_bConnected);
}

void CEx28dDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_bConnected);
}

 
void CEx28dDoc::OnFileOdbcDisconnect() 
{
   if (m_bConnected) {
      delete m_pRecordset; // destructor calls Close
      m_database.Close();
      m_bConnected = FALSE; 
      m_pRecordset = NULL;
	  m_nRowCount = 0;
	  UpdateAllViews(NULL);
    }
}

void CEx28dDoc::OnUpdateFileOdbcDisconnect(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_bConnected);
}
