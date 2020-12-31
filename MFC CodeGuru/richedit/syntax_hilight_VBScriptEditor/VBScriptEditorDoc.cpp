// VBScriptEditorDoc.cpp : implementation of the CVBScriptEditorDoc class
//

#include "stdafx.h"
#include "VBScriptEditor.h"

#include "VBScriptEditorDoc.h"
#include "VBScriptEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorDoc

IMPLEMENT_DYNCREATE(CVBScriptEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CVBScriptEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CVBScriptEditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorDoc construction/destruction

CVBScriptEditorDoc::CVBScriptEditorDoc()
{
	// TODO: add one-time construction code here

}

CVBScriptEditorDoc::~CVBScriptEditorDoc()
{
}

BOOL CVBScriptEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CVBScriptEditorView*)m_viewList.GetHead())->SetWindowText(NULL);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorDoc serialization

void CVBScriptEditorDoc::Serialize(CArchive& ar)
{
	CVBScriptEditorView* pView = (CVBScriptEditorView*)m_viewList.GetHead();
	ASSERT_VALID(pView);
	ASSERT_KINDOF(CVBScriptEditorView, pView);

	CRichEditCtrl& wndRich = pView->GetRichEditCtrl();
	CString str;

	//Write/Read raw data from file to/from RichEditControl
	if (ar.IsStoring())	{
		wndRich.GetWindowText(str);
		ar.Write((LPVOID)(LPCTSTR)str, str.GetLength()*sizeof(TCHAR));
	} else {
		CFile* pFile = ar.GetFile();
		ASSERT(pFile->GetPosition() == 0);
		DWORD nFileSize = pFile->GetLength();
		ar.Read((LPVOID)str.GetBuffer(nFileSize), nFileSize/sizeof(TCHAR));
		wndRich.SetWindowText(str);
	}

	ASSERT_VALID(this);
}

/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorDoc diagnostics

#ifdef _DEBUG
void CVBScriptEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVBScriptEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVBScriptEditorDoc commands
