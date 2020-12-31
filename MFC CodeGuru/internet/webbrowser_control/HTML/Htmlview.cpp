// HtmlView.cpp : implementation of the CHtmlView class
//

#include "stdafx.h"
#include "Html.h"

#include "HtmlDoc.h"
#include "HtmlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/* EAB22AC1-30C1-11CF-A7EB-0000C05BAE0B */
IID const IID_IWebBrowser={0xEAB22AC1, 0x30C1, 0x11CF, 0xA7, 0xEB,
		0x00, 0x00, 0xC0, 0x5B, 0xAE, 0x0B};

/* 8856F961-340A-11D0-A96B-00C04FD705A2 */
CLSID const CLSID_WebBrowser={0x8856F961, 0x340A, 0x11D0, 0xA9, 0x6B,
		0x00, 0xC0, 0x4F, 0xD7, 0x05, 0xA2};

/////////////////////////////////////////////////////////////////////////////
// CHtmlView

IMPLEMENT_DYNCREATE(CHtmlView, CView)

BEGIN_MESSAGE_MAP(CHtmlView, CView)
	//{{AFX_MSG_MAP(CHtmlView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlView construction/destruction

CHtmlView::CHtmlView()
{
}

CHtmlView::~CHtmlView()
{
}

BOOL CHtmlView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlView drawing

void CHtmlView::OnDraw(CDC* pDC)
{
	CHtmlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlView printing

BOOL CHtmlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHtmlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CHtmlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlView diagnostics

#ifdef _DEBUG
void CHtmlView::AssertValid() const
{
	CView::AssertValid();
}

void CHtmlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHtmlDoc* CHtmlView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHtmlDoc)));
	return (CHtmlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHtmlView message handlers

BOOL CHtmlView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	if (!CView::Create(lpszClassName, lpszWindowName, dwStyle, 
								rect, pParentWnd, nID, pContext))
	{
		TRACE("Can't create view.\n");
		return FALSE;
	}
	
	CRect client;
	GetClientRect(&client);
	if (!m_wndBrowser.CreateControl(CLSID_WebBrowser, lpszWindowName, 
				WS_VISIBLE|WS_CHILD, rect, this, AFX_IDW_PANE_FIRST))
	{
		TRACE("Can't create Web Browser control window.\n");
		return FALSE;
	}

	IUnknown *pUnk=m_wndBrowser.GetControlUnknown();
	ASSERT(pUnk);
	IWebBrowser *pBrowser;
	HRESULT hr=pUnk->QueryInterface(IID_IWebBrowser, (void **)&pBrowser);
	if (!SUCCEEDED(hr))
	{
		TRACE("WebBrowser interface not supported.\n");
		return FALSE;
	}

	CString url("http://www.microsoft.com/");
	BSTR bUrl=url.AllocSysString();
	hr=pBrowser->Navigate(bUrl, &COleVariant((long)0, VT_I4),
		&COleVariant((LPCTSTR)NULL, VT_BSTR), NULL, &COleVariant((LPCTSTR)NULL, VT_BSTR));
	if (!SUCCEEDED(hr))
	{
		AfxMessageBox("can't browse!!");
		return FALSE;
	}
	return TRUE;
}

void CHtmlView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if (::IsWindow(m_wndBrowser.m_hWnd))
	{
		CRect client;
		GetClientRect(&client);
		m_wndBrowser.SetWindowPos(NULL, 0, 0, client.right, client.bottom, 
			SWP_NOACTIVATE|SWP_NOZORDER);
	}
}

void CHtmlView::OnPaint() 
{
	Default();
}
