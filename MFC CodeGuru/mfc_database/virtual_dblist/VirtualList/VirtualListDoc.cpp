// VirtualListDoc.cpp : implementation of the CVirtualListDoc class
//

#include "stdafx.h"
#include "VirtualList.h"

#include "VirtualListDoc.h"
#include "PickTableDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVirtualListDoc

IMPLEMENT_DYNCREATE(CVirtualListDoc, CDocument)

BEGIN_MESSAGE_MAP(CVirtualListDoc, CDocument)
	//{{AFX_MSG_MAP(CVirtualListDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtualListDoc construction/destruction

CVirtualListDoc::CVirtualListDoc()
{
	m_pDataBase = NULL;
	m_pRecordSet = NULL;
}

CVirtualListDoc::~CVirtualListDoc()
{
}


/////////////////////////////////////////////////////////////////////////////
// CVirtualListDoc diagnostics

#ifdef _DEBUG
void CVirtualListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVirtualListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVirtualListDoc commands

BOOL CVirtualListDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	m_pDataBase = new CDaoDatabase;
	try
	{
		m_pDataBase->Open(lpszPathName);
	}
	catch(CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription, 
				MB_ICONEXCLAMATION );
		delete m_pDataBase;
		e->Delete();
		return FALSE;
	}
	CPickTableDlg  pickDlg(m_pDataBase);
	if(pickDlg.DoModal() == IDCANCEL)
		return FALSE;
	CString TableName;
	pickDlg.GetTableName(TableName);
	m_pRecordSet = new CDaoRecordset(m_pDataBase);
	CString strSQL = "SELECT * FROM " + TableName;//Set up SQL statement	
	try
	{
		m_pRecordSet->Open(dbOpenDynaset, strSQL);//Open recordset using SQL statement
	}
	catch(CDaoException* e)
	{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription, 
				MB_ICONEXCLAMATION );
		delete m_pRecordSet;
		m_pDataBase->Close();
		delete m_pDataBase;
		e->Delete();
		return FALSE;
	}

	m_pRecordSet->MoveLast();//you have to access the records in the dynaset to get GCDaoRecordSet::SetRecordCount() to work	return TRUE;
	return TRUE;
}

void CVirtualListDoc::OnCloseDocument() 
{
	POSITION pos = GetFirstViewPosition();
	while(pos != NULL)
	{
		CListView* pCurrentView = (CListView*)GetNextView(pos);
		CImageList* pImageList = pCurrentView->GetListCtrl().SetImageList(NULL, LVSIL_SMALL);
		delete pImageList;
	}
	
	if(m_pRecordSet != NULL)
	{
		ASSERT_VALID(m_pRecordSet);
		if(m_pRecordSet->IsOpen())
			m_pRecordSet->Close();
		delete m_pRecordSet;
		m_pRecordSet = NULL;
	}

	if(m_pDataBase != NULL)
	{
		ASSERT_VALID(m_pDataBase);
		if(m_pDataBase->IsOpen())
			m_pDataBase->Close();
		delete m_pDataBase;
		m_pDataBase = NULL;
	}
	CDocument::OnCloseDocument();
}

BOOL CVirtualListDoc::OnNewDocument() 
{
	return CDocument::OnNewDocument();

}

void CVirtualListDoc::DeleteContents() 
{
	POSITION pos = GetFirstViewPosition();
	while(pos != NULL)
	{
		CListView* pCurrentView = (CListView*)GetNextView(pos);
		int NumCols = 0;
		LV_COLUMN lvColumn;
		memset(&lvColumn, 0, sizeof(LV_COLUMN));
		lvColumn.mask = LVCF_FMT;
		while(pCurrentView->GetListCtrl().GetColumn(NumCols, &lvColumn))
			NumCols++;
		pCurrentView->GetListCtrl().SendMessage(LVM_SETITEMCOUNT, (WPARAM)0, (LPARAM)LVSICF_NOINVALIDATEALL);
		while(NumCols > 0)
		{
			pCurrentView->GetListCtrl().DeleteColumn(NumCols - 1);
			NumCols--;
		}
		CImageList* pImageList = pCurrentView->GetListCtrl().SetImageList(NULL, LVSIL_SMALL);
		delete pImageList;
	}
	
	if(m_pRecordSet != NULL)
	{
		ASSERT_VALID(m_pRecordSet);
		if(m_pRecordSet->IsOpen())
			m_pRecordSet->Close();
		delete m_pRecordSet;
		m_pRecordSet = NULL;
	}

	if(m_pDataBase != NULL)
	{
		ASSERT_VALID(m_pDataBase);
		if(m_pDataBase->IsOpen())
			m_pDataBase->Close();
		delete m_pDataBase;
		m_pDataBase = NULL;
	}
	CDocument::DeleteContents();
}
