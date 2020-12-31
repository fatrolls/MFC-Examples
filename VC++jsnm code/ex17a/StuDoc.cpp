// StuDoc.cpp : implementation of the CStudentDoc class
//

#include "stdafx.h"
#include "ex17a.h"

#include "StuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc

IMPLEMENT_DYNCREATE(CStudentDoc, CDocument)

BEGIN_MESSAGE_MAP(CStudentDoc, CDocument)
	//{{AFX_MSG_MAP(CStudentDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc construction/destruction

CStudentDoc::CStudentDoc()
{
	TRACE("Entering CStudentDoc constructor\n");
#ifdef _DEBUG
	afxDump.SetDepth(1); // ensure dump of list elements
#endif // _DEBUG
}

CStudentDoc::~CStudentDoc()
{
}

BOOL CStudentDoc::OnNewDocument()
{
	TRACE("Entering CStudentDoc::OnNewDocument\n");
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CStudentDoc serialization

void CStudentDoc::Serialize(CArchive& ar)
{
	TRACE("Entering CStudentDoc::Serialize\n");
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
	m_studentList.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc diagnostics

#ifdef _DEBUG
void CStudentDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStudentDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
	dc << "\n" << m_studentList << "\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc commands

void CStudentDoc::DeleteContents() 
{
	TRACE("Entering CStudentDoc::DeleteContents\n");
	while (m_studentList.GetHeadPosition()) {
		delete m_studentList.RemoveHead();
	}
}

void CStudentDoc::OnEditClearAll() 
{
	DeleteContents();
	UpdateAllViews(NULL);
}

void CStudentDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_studentList.IsEmpty());	
}

BOOL CStudentDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	TRACE("Entering CStudentDoc::OnOpenDocument\n");
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	return TRUE;
}

void CStudentDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// Disable disk toolbar button if file is not modified
	pCmdUI->Enable(IsModified());
}
