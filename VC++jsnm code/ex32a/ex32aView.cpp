// ex32aView.cpp : implementation of the CEx32aView class
//

#include "stdafx.h"
#include "ex32a.h"

#include "ex32aDoc.h"
#include "CntrItem.h"
#include "ex32aView.h"
#include "UrlThread.h"
#include "MainFrm.h"
#include "IpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx32aView

IMPLEMENT_DYNCREATE(CEx32aView, CRichEditView)

BEGIN_MESSAGE_MAP(CEx32aView, CRichEditView)
	//{{AFX_MSG_MAP(CEx32aView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_COMMAND(IDC_START, OnStart)
	ON_UPDATE_COMMAND_UI(IDC_START, OnUpdateStart)
	ON_COMMAND(IDC_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(IDC_STOP, OnUpdateStop)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx32aView construction/destruction

CEx32aView::CEx32aView()
{
	// TODO: add construction code here

}

CEx32aView::~CEx32aView()
{
}

BOOL CEx32aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CEx32aView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CEx32aView printing

BOOL CEx32aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CEx32aView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CEx32aView diagnostics

#ifdef _DEBUG
void CEx32aView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CEx32aView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CEx32aDoc* CEx32aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx32aDoc)));
	return (CEx32aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx32aView message handlers

void CEx32aView::OnEditClearAll() 
{
	SetWindowText("");
}

void CEx32aView::OnStart() 
{
	CWnd* pFrm = GetParent(); // SDI only
	CWnd* pBar;
	if(pFrm->IsKindOf(RUNTIME_CLASS(CMainFrame))) {
		pBar = &((CMainFrame*) pFrm)->m_wndDialogBar;
	}
	else {
		pBar = &((CInPlaceFrame*) pFrm)->m_wndDialogBar;
	}
	// g_strURL: thread sync?
	pBar->GetDlgItemText(IDC_URL, g_strURL);
	TRACE("CEx32aView::OnRequest -- URL = %s\n", g_strURL);
	AfxBeginThread(UrlThreadProc, GetSafeHwnd(), THREAD_PRIORITY_NORMAL);
}

void CEx32aView::OnStop() 
{
	g_eKill.SetEvent();
}

void CEx32aView::OnUpdateStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(g_bThreadStarted);
}

void CEx32aView::OnUpdateStart(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!g_bThreadStarted);
}

