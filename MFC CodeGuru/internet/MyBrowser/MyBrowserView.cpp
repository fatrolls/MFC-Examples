// MyBrowserView.cpp : implementation of the CMyBrowserView class
//

#include "stdafx.h"
#include "MyBrowser.h"

#include "MyBrowserDoc.h"
#include "MyBrowserView.h"
#include "UrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserView

IMPLEMENT_DYNCREATE(CMyBrowserView, CView)

BEGIN_MESSAGE_MAP(CMyBrowserView, CView)
	//{{AFX_MSG_MAP(CMyBrowserView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_RELOAD, OnReload)
	ON_COMMAND(IDC_FORWARD, OnForward)
	ON_COMMAND(ID_BACK, OnBack)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_URL, OnUrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyBrowserView construction/destruction

CMyBrowserView::CMyBrowserView()
{
	// TODO: add construction code here

}

CMyBrowserView::~CMyBrowserView()
{
}

BOOL CMyBrowserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserView drawing

void CMyBrowserView::OnDraw(CDC* pDC)
{
	CMyBrowserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserView diagnostics

#ifdef _DEBUG
void CMyBrowserView::AssertValid() const
{
	CView::AssertValid();
}

void CMyBrowserView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyBrowserDoc* CMyBrowserView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyBrowserDoc)));
	return (CMyBrowserDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyBrowserView message handlers

int CMyBrowserView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if ( ! m_Browser.Create( NULL, WS_CHILD | WS_VISIBLE, CRect(), this,
		 IDX_BROWSER ) )
		return -1;
	
	COleVariant varEmpty; // Default is VT_EMPTY

	char Buffer[ 200 ];

	GetCurrentDirectory( 199, Buffer );
	strcat( Buffer, "\\a.htm" );

	m_Browser.Navigate( Buffer, &varEmpty, &varEmpty,
						&varEmpty, &varEmpty );

	return 0;
}

void CMyBrowserView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_Browser.MoveWindow( 0, 0, cx, cy );
	m_Browser.UpdateWindow();	
}


void CMyBrowserView::OnReload() 
{
	// TODO: Add your command handler code here
	m_Browser.Refresh();
}

void CMyBrowserView::OnForward() 
{
	// TODO: Add your command handler code here
	m_Browser.GoForward();
}

void CMyBrowserView::OnBack() 
{
	// TODO: Add your command handler code here
	m_Browser.GoBack();	
}

void CMyBrowserView::OnStop() 
{
	// TODO: Add your command handler code here
	m_Browser.Stop();
}

void CMyBrowserView::OnUrl() 
{
	// TODO: Add your command handler code here
	COleVariant varEmpty; // Default is VT_EMPTY
	
	UrlDlg *Dlg = new UrlDlg( this );
	if( Dlg->DoModal() == IDOK )
		m_Browser.Navigate( Dlg->m_Edit, &varEmpty, &varEmpty,
						&varEmpty, &varEmpty );
	delete Dlg;
}
