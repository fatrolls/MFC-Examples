// msdidoc.cpp : implementation of the CMsdiDoc class
//

#include "stdafx.h"
#include "msdi.h"

#include "msdidoc.h"
#include "grafview.h"
#include "outview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsdiDoc

IMPLEMENT_DYNCREATE(CMsdiDoc, CDocument)

BEGIN_MESSAGE_MAP(CMsdiDoc, CDocument)
  //{{AFX_MSG_MAP(CMsdiDoc)
  ON_COMMAND(ID_VIEW_VIEW2, OnViewView2)
  ON_UPDATE_COMMAND_UI(ID_VIEW_VIEW2, OnUpdateViewView2)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsdiDoc construction/destruction

CMsdiDoc::CMsdiDoc()
{
  // TODO: add one-time construction code here
}

CMsdiDoc::~CMsdiDoc()
{
}

BOOL CMsdiDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMsdiDoc serialization

void CMsdiDoc::Serialize(CArchive& ar)
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
// CMsdiDoc diagnostics

#ifdef _DEBUG
void CMsdiDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void CMsdiDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMsdiDoc commands

void CMsdiDoc::OnViewView2()
{
  CMSDIWinApp* pApp = (CMSDIWinApp*)AfxGetApp();
  pApp->CreateOrActivateFrame(RUNTIME_CLASS(CGrafView), this);
}

void CMsdiDoc::OnUpdateViewView2(CCmdUI* pCmdUI)
{
  // disable the command if the view2 exist
  CMSDIWinApp* pApp = (CMSDIWinApp*)AfxGetApp();
  CView* pView = pApp->GetView(RUNTIME_CLASS(CGrafView));
  pCmdUI->Enable(pView == NULL);
}
