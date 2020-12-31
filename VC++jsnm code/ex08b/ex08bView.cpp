// ex08bView.cpp : implementation of the CEx08bView class
//

#include "stdafx.h"
#include "ex08b.h"

#include "ex08bDoc.h"
#include "ex08bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx08bView

const char CEx08bView::s_engineAltavista[] =
	"http://altavista.digital.com/";

IMPLEMENT_DYNCREATE(CEx08bView, CView)

BEGIN_MESSAGE_MAP(CEx08bView, CView)
	//{{AFX_MSG_MAP(CEx08bView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx08bView construction/destruction

CEx08bView::CEx08bView()
{
	// TODO: add construction code here

}

CEx08bView::~CEx08bView()
{
}

BOOL CEx08bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx08bView drawing

void CEx08bView::OnDraw(CDC* pDC)
{
	CEx08bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx08bView diagnostics

#ifdef _DEBUG
void CEx08bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx08bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx08bDoc* CEx08bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx08bDoc)));
	return (CEx08bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx08bView message handlers

int CEx08bView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DWORD dwStyle = WS_VISIBLE | WS_CHILD;	
	if (m_search.Create(NULL, dwStyle, CRect(0, 0, 100, 100),
	                    this, ID_BROWSER_SEARCH) == 0) {
		AfxMessageBox("Unable to create search control!\n");
		return -1;
	}
	m_search.Navigate(s_engineAltavista, NULL, NULL, NULL, NULL);

	if (m_target.Create(NULL, dwStyle, CRect(0, 0, 100, 100),
	                    this, ID_BROWSER_TARGET) == 0) {
		AfxMessageBox("Unable to create target control!\n");
		return -1;
	}
	m_target.GoHome(); // as defined in IE3 options

	return 0;
}

void CEx08bView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	CRect rectClient;
	GetClientRect(rectClient);
	CRect rectBrowse(rectClient);
	rectBrowse.right = rectClient.right / 2;
	CRect rectSearch(rectClient);
	rectSearch.left = rectClient.right / 2;

	m_target.SetWidth(rectBrowse.right - rectBrowse.left);
	m_target.SetHeight(rectBrowse.bottom - rectBrowse.top);
	m_target.UpdateWindow();

	m_search.SetLeft(rectSearch.left);
	m_search.SetWidth(rectSearch.right - rectSearch.left);
	m_search.SetHeight(rectSearch.bottom - rectSearch.top);
	m_search.UpdateWindow();
}

BEGIN_EVENTSINK_MAP(CEx08bView, CView)
	ON_EVENT(CEx08bView, ID_BROWSER_SEARCH, 100, OnBeforeNavigateExplorer1, VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PBOOL)
	ON_EVENT(CEx08bView, ID_BROWSER_TARGET, 113, OnTitleChangeExplorer2, VTS_BSTR)
END_EVENTSINK_MAP()

void CEx08bView::OnBeforeNavigateExplorer1(LPCTSTR URL,
	long Flags, LPCTSTR TargetFrameName,
	VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Cancel)
{
	TRACE("CEx08bView::OnBeforeNavigateExplorer1 -- URL = %s\n", URL);

	if (!strnicmp(URL, s_engineAltavista, strlen(s_engineAltavista))) {
		return;
	}
	m_target.Navigate(URL, NULL, NULL, PostData, NULL);
	*Cancel = TRUE;
}

void CEx08bView::OnTitleChangeExplorer2(LPCTSTR Text)
{
	// Careful!  Event could fire before we're ready.
	CWnd* pWnd = AfxGetApp()->m_pMainWnd;
	if (pWnd != NULL) {
		if (::IsWindow(pWnd->m_hWnd)) {
			pWnd->SetWindowText(Text);
		}
	}
}
