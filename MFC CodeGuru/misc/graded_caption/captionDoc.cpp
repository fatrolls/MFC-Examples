// captionDoc.cpp : implementation of the CCaptionDoc class
//

#include "stdafx.h"
#include "caption.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "captionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptionDoc

IMPLEMENT_DYNCREATE(CCaptionDoc, CDocument)

BEGIN_MESSAGE_MAP(CCaptionDoc, CDocument)
	//{{AFX_MSG_MAP(CCaptionDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptionDoc construction/destruction

CCaptionDoc::CCaptionDoc()
{
	// TODO: add one-time construction code here

}

CCaptionDoc::~CCaptionDoc()
{
}

BOOL CCaptionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCaptionDoc serialization

void CCaptionDoc::Serialize(CArchive& ar)
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
// CCaptionDoc diagnostics

#ifdef _DEBUG
void CCaptionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCaptionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCaptionDoc commands

void CCaptionDoc::SetModifiedFlag(BOOL flag)
{
  CDocument::SetModifiedFlag(flag);
  ((CMainFrame *)AfxGetMainWnd())->RedrawCaption();
  POSITION pos = GetFirstViewPosition();
  CView *pView;
  CChildFrame *pChild;
  while(pos!=NULL){
    pView = GetNextView(pos);
    if(pView){
      pChild = (CChildFrame *)pView->GetParent();
      if(pChild)pChild->OnUpdateFrameTitle(TRUE);
    }
  }
}
