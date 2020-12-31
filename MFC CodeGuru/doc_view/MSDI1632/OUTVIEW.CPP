// outview.cpp : implementation of the COutView class
//

#include "stdafx.h"

#include "mainfrm.h"
#include "outview.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutView

IMPLEMENT_DYNCREATE(COutView, CEditView)

BEGIN_MESSAGE_MAP(COutView, CEditView)
  //{{AFX_MSG_MAP(COutView)
  ON_WM_DESTROY()
  //}}AFX_MSG_MAP
  // outside the ADX_MSG_MAP for #if #endif
#ifdef WIN32
  ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
#else
  ON_LBN_SELCHANGE(EN_CHANGE, OnChange)
#endif
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutView construction/destruction

COutView::COutView()
{
}

COutView::~COutView()
{
}

void COutView::OnInitialUpdate()
{
  GetEditCtrl().SetReadOnly(TRUE);
  WriteTTY("Hello world\r\n");
}

/////////////////////////////////////////////////////////////////////////////
// COutView Implementation

void COutView::WriteTTY(LPCSTR lpszString)
{
  CEdit& Edit = GetEditCtrl();
  Edit.SetSel(-1, -1, NULL);
  Edit.ReplaceSel(lpszString);
}

void COutView::ClearTTY()
{
  GetEditCtrl().SetWindowText(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// COutView printing

BOOL COutView::OnPreparePrinting(CPrintInfo* pInfo)
{
  return CEditView::OnPreparePrinting(pInfo);
}

void COutView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
  CEditView::OnBeginPrinting(pDC, pInfo);
}

void COutView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
  CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// COutView message handlers

void COutView::OnDestroy()
{
  CEditView::OnDestroy();
  // call the mainframe to destroy the pointer
  CMSDIWinApp* pApp = (CMSDIWinApp*)AfxGetApp();
  CMainFrame* pMainFrame = (CMainFrame*)pApp->m_pMainWnd;
  pMainFrame->OnDestroyView(this);
}

void COutView::OnChange()
{
  // make this override to not call pDoc->SetModifiedFlag()
  // the document pointer of this view is NULL
  ASSERT(GetDocument() == NULL);
}
