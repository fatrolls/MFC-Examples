// ex08cView.cpp : implementation of the CEx08cView class
//

#include "stdafx.h"
#include <docobj.h> // for printing
#include "ex08c.h"

#include "ex08cDoc.h"
#include "ex08cView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx08cView

IMPLEMENT_DYNCREATE(CEx08cView, CView)

BEGIN_MESSAGE_MAP(CEx08cView, CView)
	//{{AFX_MSG_MAP(CEx08cView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_COMMAND_EX(ID_ENGINE_ALTAVISTA, OnEngine)
	ON_COMMAND_EX(ID_ENGINE_MAGELLAN, OnEngine)
	ON_COMMAND_EX(ID_ENGINE_MICROSOFT, OnEngine)
	ON_COMMAND_EX(ID_ENGINE_YAHOO, OnEngine)
	ON_COMMAND(ID_VIEW_REFRESHBROWSE, OnViewRefreshbrowse)
	ON_COMMAND(ID_VIEW_UPDATEBROWSE, OnViewUpdatebrowse)
	ON_COMMAND(ID_VIEW_REFRESHSEARCH, OnViewRefreshsearch)
	ON_COMMAND(ID_VIEW_BACKSEARCH, OnViewBacksearch)
	ON_COMMAND(ID_VIEW_FORWARDSEARCH, OnViewForwardsearch)
	ON_COMMAND(ID_VIEW_BACKBROWSE, OnViewBackbrowse)
	ON_COMMAND(ID_VIEW_FORWARDBROWSE, OnViewForwardbrowse)
	ON_COMMAND(ID_FILE_PRINTBROWSE, OnFilePrintbrowse)
	ON_COMMAND(ID_FILE_PRINTSEARCH, OnFilePrintsearch)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_BUSY, OnUpdateIndicatorBusy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CEx08cView, CView)
    //{{AFX_EVENTSINK_MAP(CEx08bView)
	ON_EVENT(CEx08cView, 2001, 100 /* BeforeNavigate */, OnBeforeNavigateExplorer1, VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PBOOL)
	ON_EVENT(CEx08cView, 2001, 102 /* StatusTextChange */, OnStatusTextChangeExplorer1, VTS_BSTR)
	ON_EVENT(CEx08cView, 2002, 100 /* BeforeNavigate */, OnBeforeNavigateExplorer2, VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PBOOL)
	ON_EVENT(CEx08cView, 2002, 113 /* TitleChange */, OnTitleChangeExplorer2, VTS_BSTR)
	ON_EVENT(CEx08cView, 2002, 102 /* StatusTextChange */, OnStatusTextChangeExplorer2, VTS_BSTR)
	ON_EVENT(CEx08cView, 2002, 107 /* NewWindow */, OnNewWindowExplorer2, VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PBOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx08cView construction/destruction

CEx08cView::CEx08cView()
{
}

CEx08cView::~CEx08cView()
{
}

BOOL CEx08cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx08cView drawing

void CEx08cView::OnDraw(CDC* pDC)
{
	CEx08cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx08cView printing

BOOL CEx08cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx08cView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx08cView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx08cView diagnostics

#ifdef _DEBUG
void CEx08cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx08cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx08cDoc* CEx08cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx08cDoc)));
	return (CEx08cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx08cView message handlers

int CEx08cView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	TRACE("CEx08cView::OnCreate\n");
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CEx08cDoc* pDoc = GetDocument();
	int nPane = GetDlgCtrlID();
	TRACE("CEx08cView::OnCreate -- ID = %x\n", nPane);
	DWORD dwStyle = WS_VISIBLE | WS_CHILD;
	if(nPane == AFX_IDW_PANE_FIRST) {
		if(pDoc->m_browse.Create(NULL, dwStyle, CRect(0,0,100,100), this, 2002) == 0) {
			AfxMessageBox("Unable to create browser control!\n");
			return -1;
		}
		pDoc->m_strURLBrowse = AfxGetApp()->GetProfileString(CEx08cDoc::s_profileInternet,
				CEx08cDoc::s_profileURLBrowse, "");
		if(pDoc->m_strURLBrowse == "") {
			pDoc->m_browse.GoHome();
		}
		else {
			pDoc->m_browse.Navigate(pDoc->m_strURLBrowse);
		}
	}
	else {
		if(pDoc->m_search.Create(NULL, dwStyle, CRect(0,0,100,100), this, 2001) == 0) {
			AfxMessageBox("Unable to create search control!\n");
			return -1;
		}
		pDoc->m_strURLSearch = AfxGetApp()->GetProfileString(CEx08cDoc::s_profileInternet,
                        CEx08cDoc::s_profileURLSearch, CEx08cDoc::s_engineAltavista);
		pDoc->m_search.Navigate(pDoc->m_strURLSearch);
	}
	return 0;
}

void CEx08cView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	CEx08cDoc* pDoc = GetDocument();
	CRect rectClient;
	GetClientRect(rectClient);
	int nPane = GetDlgCtrlID();

	if(nPane == AFX_IDW_PANE_FIRST) {
		pDoc->m_browse.SetWidth(rectClient.right - rectClient.left);
		pDoc->m_browse.SetHeight(rectClient.bottom - rectClient.top);
		pDoc->m_browse.UpdateWindow();
	}
	else {
		pDoc->m_search.SetWidth(rectClient.right - rectClient.left);
		pDoc->m_search.SetHeight(rectClient.bottom - rectClient.top);
		pDoc->m_search.UpdateWindow();
	}
	
}

// event handlers
void CEx08cView::OnBeforeNavigateExplorer1(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Cancel) 
{
	CEx08cDoc* pDoc = GetDocument();
	TRACE("CEx08bView::OnBeforeNavigateExplorer1 -- URL = %s\n", URL);
	TRACE(" strURLSearch = %s\n", pDoc->m_strURLSearch);
	if(pDoc->m_bSearchBackForward || KeepSearching(URL)) {
		pDoc->m_strURLSearch = URL;
		pDoc->m_bSearchBackForward = FALSE;
		pDoc->m_bSearchBusy = TRUE;
		return;
	}
	// actual post data starts at PostData->bstrVal + 24 -- single byte characters
	pDoc->m_browse.Navigate(URL, NULL, NULL, PostData, NULL);
	pDoc->m_strURLBrowse = URL;
	UpdateStatusBar();
	*Cancel = TRUE;
}

BOOL CEx08cView::KeepSearching(LPCTSTR URL)
{
	CEx08cDoc* pDoc = GetDocument();
	char URLUpper[400];
	strcpy(URLUpper, pDoc->m_strURLSearch);
	_strupr(URLUpper);
	if(strstr(URLUpper, "ALTAVISTA")) {
		return (strnicmp(URL, pDoc->m_strURLSearch, 28) == 0);
	}
	if(strstr(URLUpper, "MAGELLAN")) {
		return (strnicmp(URL, pDoc->m_strURLSearch, 28) == 0);
	}
	if(strstr(URLUpper, "MICROSOFT")) {
		if(strstr(URL, "search")) return TRUE;
		return (strnicmp(URL, pDoc->m_strURLSearch, 31) == 0);
	}
	if(strstr(URLUpper, "YAHOO")) {
		return (strnicmp(URL, pDoc->m_strURLSearch, 20) == 0);
	}
	return FALSE;
}

void CEx08cView::OnStatusTextChangeExplorer1(LPCTSTR Text) 
{
//	TRACE("CEx08cView::OnStatusTextChangeExplorer1 -- Text = %s\n", Text);
	CEx08cDoc* pDoc = GetDocument();
	if(!stricmp(Text, "Done")) {
		pDoc->m_bSearchBusy = FALSE;
	}
}

void CEx08cView::OnBeforeNavigateExplorer2(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Cancel) 
{
	TRACE("CEx08bView::OnBeforeNavigateExplorer2 -- URL = %s, TargetFrameName = %s\n", URL, TargetFrameName);
	CEx08cDoc* pDoc = GetDocument();
	pDoc->m_strURLBrowse = URL;
	UpdateStatusBar();
}

void CEx08cView::OnTitleChangeExplorer2(LPCTSTR Text) 
{
	// careful!  event could fire before we're ready
	CWnd* pWnd = AfxGetApp()->m_pMainWnd;
	if(pWnd != NULL) {
		if(::IsWindow(pWnd->m_hWnd)) {
			pWnd->SetWindowText(Text);
		}
	}
}

void CEx08cView::OnStatusTextChangeExplorer2(LPCTSTR Text) 
{
//	TRACE("CEx08cView::OnStatusTextChangeExplorer2 -- Text = %s\n", Text);
	CMainFrame* pFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	if(pFrm != NULL) {
		if(::IsWindow(pFrm->m_hWnd)) {
			CStatusBar& rBar = pFrm->m_wndStatusBar;
			rBar.SetPaneText(0, Text);
		}
	}
}

void CEx08cView::OnNewWindowExplorer2(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Processed) 
{
	// disallow opening a new window in response to TARGET attribute
	TRACE("CEx08cView::OnNewWindowExplorer2 TargetFrameName = %s\n", TargetFrameName);
	CEx08cDoc* pDoc = GetDocument();
	pDoc->m_strURLBrowse = URL;
	// Navigate doesn't always work here, so we must post a message
	CWnd* pWnd = AfxGetApp()->m_pMainWnd;
	if(pWnd != NULL) {
		if(::IsWindow(pWnd->m_hWnd)) {
			pWnd->PostMessage(WM_COMMAND, ID_VIEW_UPDATEBROWSE);
		}
	}
	UpdateStatusBar();
	*Processed = TRUE;
}

void CEx08cView::UpdateStatusBar()
{
	CEx08cDoc* pDoc = GetDocument();
	CMainFrame* pFrm = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	if(pFrm != NULL) {
		if(::IsWindow(pFrm->m_hWnd)) {
			CStatusBar& rBar = pFrm->m_wndStatusBar;
			rBar.SetPaneText(1, pDoc->m_strURLBrowse);
		}
	}
}

void CEx08cView::OnDestroy() 
{
	CEx08cDoc* pDoc = GetDocument();
	CView::OnDestroy();
    AfxGetApp()->WriteProfileString(CEx08cDoc::s_profileInternet,
                         CEx08cDoc::s_profileURLBrowse, pDoc->m_strURLBrowse);
    AfxGetApp()->WriteProfileString(CEx08cDoc::s_profileInternet,
                         CEx08cDoc::s_profileURLSearch, pDoc->m_strURLSearch);
}

BOOL CEx08cView::OnEngine(UINT nCommand) 
{
	CEx08cDoc* pDoc = GetDocument();
	switch(nCommand) {
	case ID_ENGINE_ALTAVISTA:
		pDoc->m_strURLSearch = CEx08cDoc::s_engineAltavista;
		break;
	case ID_ENGINE_MAGELLAN:
		pDoc->m_strURLSearch = CEx08cDoc::s_engineMagellan;
		break;
	case ID_ENGINE_MICROSOFT:
		pDoc->m_strURLSearch = CEx08cDoc::s_engineMicrosoft;
		break;
	case ID_ENGINE_YAHOO:
		pDoc->m_strURLSearch = CEx08cDoc::s_engineYahoo;
		break;
	default:
		ASSERT(FALSE);
	}
	pDoc->m_search.Navigate(pDoc->m_strURLSearch);
	return TRUE;
}

void CEx08cView::OnViewRefreshbrowse() 
{
	CEx08cDoc* pDoc = GetDocument();
	pDoc->m_browse.Refresh();
}

void CEx08cView::OnViewUpdatebrowse() 
{
	// message sent if user or html tries to open a new window
	CEx08cDoc* pDoc = GetDocument();
	pDoc->m_browse.Navigate(pDoc->m_strURLBrowse);
}

void CEx08cView::OnViewRefreshsearch() 
{
	CEx08cDoc* pDoc = GetDocument();
	pDoc->m_search.Refresh();
}

void CEx08cView::OnViewBacksearch() 
{
	CEx08cDoc* pDoc = GetDocument();
	try {
		pDoc->m_bSearchBackForward = TRUE;
		pDoc->m_search.GoBack();
	}
	catch (COleDispatchException* pe) {
		AfxMessageBox("Can't go back");
		pe->Delete();
	}
}

void CEx08cView::OnViewForwardsearch() 
{
	CEx08cDoc* pDoc = GetDocument();
	try {
		pDoc->m_bSearchBackForward = TRUE;
		pDoc->m_search.GoForward();
	}
	catch (COleDispatchException* pe) {
		AfxMessageBox("Can't go forward");
		pe->Delete();
	}
}

void CEx08cView::OnViewBackbrowse() 
{
	CEx08cDoc* pDoc = GetDocument();
	try {
		pDoc->m_browse.GoBack();
	}
	catch (COleDispatchException* pe) {
		AfxMessageBox("Can't go back");
		pe->Delete();
	}
}

void CEx08cView::OnViewForwardbrowse() 
{
	CEx08cDoc* pDoc = GetDocument();
	try {
		pDoc->m_browse.GoForward();
	}
	catch (COleDispatchException* pe) {
		AfxMessageBox("Can't go forward");
		pe->Delete();
	}
}

void CEx08cView::OnFilePrintbrowse() 
{
	CEx08cDoc* pDoc = GetDocument();
	LPOLECOMMANDTARGET pOCT;
	LPDISPATCH pDisp = pDoc->m_browse.GetDocument();
	ASSERT(pDisp != NULL);
	VERIFY(pDisp->QueryInterface(IID_IOleCommandTarget, (void**) &pOCT) == S_OK);
	VERIFY(pOCT->Exec(NULL,OLECMDID_PRINT, OLECMDEXECOPT_DONTPROMPTUSER, NULL,NULL) == S_OK);
}

void CEx08cView::OnFilePrintsearch() 
{
	CEx08cDoc* pDoc = GetDocument();
	LPOLECOMMANDTARGET pOCT;
	LPDISPATCH pDisp = pDoc->m_search.GetDocument();
	ASSERT(pDisp != NULL);
	VERIFY(pDisp->QueryInterface(IID_IOleCommandTarget, (void**) &pOCT) == S_OK);
	VERIFY(pOCT->Exec(NULL,OLECMDID_PRINT, OLECMDEXECOPT_DONTPROMPTUSER, NULL,NULL) == S_OK);
}

void CEx08cView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	UpdateStatusBar();
}

void CEx08cView::OnUpdateIndicatorBusy(CCmdUI* pCmdUI) 
{
	CEx08cDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->m_bSearchBusy);
}
