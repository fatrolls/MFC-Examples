// browsevw.cpp : implementation file
//

#include "stdafx.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserView

IMPLEMENT_DYNCREATE(CBrowserView, CView)

CBrowserView::CBrowserView()
{
}

CBrowserView::~CBrowserView()
{
	m_pWebBrowser2->Release();
}


BEGIN_MESSAGE_MAP(CBrowserView, CView)
	//{{AFX_MSG_MAP(CBrowserView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserView drawing

void CBrowserView::OnDraw(CDC* pDC)
{
	//just overload to avoid compilation errors
	//We don't require it

}

/////////////////////////////////////////////////////////////////////////////
// CBrowserView diagnostics

#ifdef _DEBUG
void CBrowserView::AssertValid() const
{
	CView::AssertValid();
}

void CBrowserView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserView message handlers

int CBrowserView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//Create the Browser Control
	if (!m_wndWebBrowser.CreateControl(CLSID_WebBrowser, NULL,WS_CHILD|WS_VISIBLE|WS_GROUP|WS_TABSTOP, CRect(0,0,0,0), this, 1))
		return -1;

	//Get IUnknown Interface pointer
	LPUNKNOWN pUnk = m_wndWebBrowser.GetControlUnknown();
	HRESULT hr = pUnk->QueryInterface(IID_IWebBrowser2, (LPVOID*)&m_pWebBrowser2);
	
	if (!SUCCEEDED(hr))
		return -1;
	

	return 0;
}

void CBrowserView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_wndWebBrowser.MoveWindow(0, 0, cx, cy);	
}

BOOL CBrowserView::LoadForm(CHTMLForm * pForm)
{
	m_pForm = pForm;
	m_bNewForm = TRUE;

	HRESULT hr = m_pWebBrowser2->Navigate(m_pForm->m_strURL.AllocSysString(), NULL, NULL, NULL, NULL);

	if (!SUCCEEDED(hr))
		return FALSE;

	return TRUE;
}

BEGIN_EVENTSINK_MAP(CBrowserView, CView)
    //{{AFX_EVENTSINK_MAP(CBrowserView)
	ON_EVENT(CBrowserView, IDC_EXPLORER, 104 /* DownloadComplete */, OnDownloadComplete, VTS_NONE)
	ON_EVENT(CBrowserView, IDC_EXPLORER, 259 /* DocumentComplete */, OnDocumentComplete, VTS_DISPATCH VTS_PVARIANT)
	ON_EVENT(CBrowserView, IDC_EXPLORER, 250 /* BeforeNavigate2 */, OnBeforeNavigate2, VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CBrowserView::OnDownloadComplete() 
{
	// TODO: Add your control notification handler code here
//	m_bNewForm = FALSE;
}

void CBrowserView::OnDocumentComplete(LPDISPATCH pDisp, VARIANT FAR* URL) 
{

	//Document is fully loaded now initialize any variables
	CWaitCursor wc;

	if (!m_bNewForm)
		return;
	
	HRESULT hr;
	LPDISPATCH pDisp1;
	IHTMLDocument2* pHTMLDocument = NULL;
	IHTMLElementCollection* pCollection = NULL;
	

	hr = m_pWebBrowser2->get_Document(&pDisp1);
	//if (!SUCCEEDED(hr))
	//	throw Exception

	hr = pDisp1->QueryInterface(IID_IHTMLDocument2, (void**)&pHTMLDocument);
	//if (!SUCCEEDED(hr))
	//	throw Exception

	hr = pHTMLDocument->get_all(&pCollection);
	//if (!SUCCEEDED(hr))
	//	throw Exception
	ICustomDoc* pCustomDoc;

	hr = pDisp1->QueryInterface(IID_ICustomDoc, (LPVOID*)&pCustomDoc);
	//if (!SUCCEEDED(hr))
	//	throw Exception
	

	CDocHostUIHandler* pDHUIH = new CDocHostUIHandler();
	
	pDHUIH->m_pBrowserView = this;

	pCustomDoc->SetUIHandler((IDocHostUIHandler*)pDHUIH);
	
	pCustomDoc->Release();
	
	m_pForm->OnLoad(pCollection);
	//It is responsiblity of the form to realease pCollection
	

	pDisp1->Release();
	pHTMLDocument->Release();
	
	m_bNewForm = FALSE;

}

void CBrowserView::OnBeforeNavigate2(LPDISPATCH pDisp, VARIANT FAR* URL, VARIANT FAR* Flags, VARIANT FAR* TargetFrameName, VARIANT FAR* PostData, VARIANT FAR* Headers, BOOL FAR* Cancel) 
{
	//Get the command 
	//Parse the URL
	if (m_bNewForm)
	{
		*Cancel = FALSE;
		return;
	}

	
	CWaitCursor wc;

	CString strCmd = URL->bstrVal;
	strCmd = strCmd.Right(strCmd.GetLength() - 6);
	m_pForm->ExecuteCmd(strCmd);
	*Cancel = TRUE;
}

void CBrowserView::OnContextMenu(POINT pt)
{
	//The application needs to overload this to display it's menu
}
