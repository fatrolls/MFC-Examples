// StuDoc.cpp : implementation of the CStudentDoc class
//

#include "stdafx.h"
#include "ex15b.h"

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc construction/destruction

CStudentDoc::CStudentDoc()
{
	TRACE("Entering CStudentDoc constructor\n");
#ifdef _DEBUG
	afxDump.SetDepth(1); // Ensure dump of list elements
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
#ifdef _DEBUG
	Dump(afxDump);
#endif
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
