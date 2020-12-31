// =============================================================================
// 							Class Implementation : COXWebView
// =============================================================================
//
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
//
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "OXWebView.h"
#include "OXMainRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#ifndef CSC_NAVIGATEBACK
	#define CSC_NAVIGATEBACK		2
#endif

#ifndef CSC_NAVIGATEFORWARD
	#define CSC_NAVIGATEFORWARD		1
#endif

// Edit control that adds item to combobox upon pressing enter.

const int ECA_NO_DUPLICATES		= 0x1;
const int ECA_DEFAULT = ECA_NO_DUPLICATES;

class OX_CLASS_DECL CEditComboboxAdder : public CEdit 
{
public:
	CEditComboboxAdder(CWnd* pCB, int nFlags = ECA_DEFAULT, int nMaxEntries = 20);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void PostNcDestroy()
		{ 
		delete this; 
		}
private:
	// Note:	The control ID for the edit control of a combobox
	//			is 1001. It seems quite unlikely that Microsoft
	//			would ever change this, but if it happens, the
	//			following anonymous enumeration will need updating.

	enum { IDC_COMBOBOX_EDIT = 1001 };

	CComboBox* m_pCB;
	int m_nMaxEntries;
	int m_nFlags;
};

CEditComboboxAdder::CEditComboboxAdder(CWnd* pCB, int nFlags, int nMaxEntries) 
	:
	m_nFlags(nFlags),
	m_nMaxEntries(nMaxEntries)
	{
	UINT uiEdit = IDC_COMBOBOX_EDIT;
	m_pCB = (CComboBox*)pCB;
	ASSERT_VALID(pCB);
	VERIFY(SubclassDlgItem(uiEdit, pCB));
	}

BOOL CEditComboboxAdder::PreTranslateMessage(MSG* pMsg)
	{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{
		CString s;
		GetWindowText(s);

		// If we are supposed to prevent duplicates, and the 
		// given item exists, delete it.

		int nDupe;
		if ((m_nFlags & ECA_NO_DUPLICATES) &&
			((nDupe = m_pCB->FindStringExact(-1, s)) != CB_ERR))
			{
			m_pCB->DeleteString(nDupe);
			}

		// Add the item to the top and select it.

		m_pCB->InsertString(0, s);
		m_pCB->SetCurSel(0);

		// If we have more than the maximum, trim the list.

		for (int n = m_pCB->GetCount(); n > m_nMaxEntries; n--)
			m_pCB->DeleteString(n - 1);

		// Fake the selection change notifcation.

		CWnd* pwndParent = m_pCB->GetParent();
		if (pwndParent != NULL)
			{
			WPARAM w = MAKEWPARAM(m_pCB->GetDlgCtrlID(), CBN_SELCHANGE);
			LPARAM l = (LPARAM)m_pCB->GetSafeHwnd();
			pwndParent->PostMessage(WM_COMMAND, w, l);
			}

		return TRUE;
		}

	return FALSE;
	}

/////////////////////////////////////////////////////////////////////////////
// COXWebView

/////////////////////////////////////////////////////////////////////////////
// Definition of static members

// Data members -------------------------------------------------------------
// private:
	
CFont* COXWebView::m_pfontToolbarURL;
int COXWebView::m_nNumInstantiated;

IMPLEMENT_DYNCREATE(COXWebView, CView)

BEGIN_MESSAGE_MAP(COXWebView, CView)
	//{{AFX_MSG_MAP(COXWebView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_OX_WEBVIEW_BACK, OnWebviewBack)
	ON_COMMAND(ID_OX_WEBVIEW_FORWARD, OnWebviewForward)
	ON_UPDATE_COMMAND_UI(ID_OX_WEBVIEW_BACK, OnUpdateWebviewBack)
	ON_UPDATE_COMMAND_UI(ID_OX_WEBVIEW_FORWARD, OnUpdateWebviewForward)
	ON_COMMAND(ID_OX_WEBVIEW_HOME, OnWebviewHome)
	ON_COMMAND(ID_OX_WEBVIEW_SEARCH, OnWebviewSearch)
	ON_UPDATE_COMMAND_UI(ID_OX_WEBVIEW_STOP, OnUpdateWebviewStop)
	ON_COMMAND(ID_OX_WEBVIEW_STOP, OnWebviewStop)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_OX_WEBVIEW_REFRESH, OnUpdateWebviewRefresh)
	ON_COMMAND(ID_OX_WEBVIEW_REFRESH, OnWebviewRefresh)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

	ON_CBN_SELCHANGE(IDC_TOOLBAR_URL, OnToolbarURLChange)
	ON_NOTIFY_EX(TTN_NEEDTEXTA, 0, OnTooltipNeedText)
	ON_NOTIFY_EX(TTN_NEEDTEXTW, 0, OnTooltipNeedText)
	//ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT, 0, 0xFFFFFFFF, OnTooltipNeedText)

END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(COXWebView, CView)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x64, BeforeNavigate, VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PVARIANT)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x65, NavigateComplete, VTS_BSTR)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x66, StatusTextChange, VTS_BSTR)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x67, Quit, VTS_PVARIANT)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x6a, DownloadBegin, VTS_NONE)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x6b, NewWindow, VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PVARIANT)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x6c, ProgressChange, VTS_I4 VTS_I4)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x68, DownloadComplete, VTS_NONE)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x69, CommandStateChange, VTS_I4 VTS_BOOL)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x70, PropertyChange, VTS_BSTR)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0x71, TitleChange, VTS_BSTR)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0xc8, FrameBeforeNavigate, VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PVARIANT)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0xc9, FrameNavigateComplete, VTS_BSTR)
	ON_EVENT(COXWebView, IDC_WEB_CTRL, 0xcc, FrameNewWindow, VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PVARIANT)
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// COXWebView construction/destruction

COXWebView::COXWebView() 
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Contructor of object
	//				It will initialize the internal state
	:
	m_bCanGoBack(FALSE),
	m_bCanGoForward(FALSE),
	m_bCanRefresh(FALSE)
	{
	if (m_nNumInstantiated++ == 0)
		{
		CDC DC;
		DC.CreateCompatibleDC(NULL);
		LOGFONT lf;
		memset(&lf, 0, sizeof(lf));
		_tcscpy(lf.lfFaceName, _T("MS Sans Serif"));
		const int POINTS_PER_INCH = 72;
		const int PPLIY = DC.GetDeviceCaps(LOGPIXELSY);
		lf.lfHeight = -MulDiv(8, PPLIY, POINTS_PER_INCH);
		m_pfontToolbarURL = new CFont;
		m_pfontToolbarURL->CreateFontIndirect(&lf);
		}
	}

COXWebView::~COXWebView()
	{
	if (--m_nNumInstantiated == 0)
		{
		delete m_pfontToolbarURL;
		m_pfontToolbarURL = NULL;
		}
	}

/////////////////////////////////////////////////////////////////////////////
// COXWebView drawing

void COXWebView::OnDraw(CDC* /* pDC */)
	{
	// no implementation
	}

/////////////////////////////////////////////////////////////////////////////
// COXWebView printing

BOOL COXWebView::OnPreparePrinting(CPrintInfo* pInfo)
	{
	// default preparation
	return DoPreparePrinting(pInfo);
	}

void COXWebView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
	// TODO: add extra initialization before printing
	}

void COXWebView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
	// TODO: add cleanup after printing
	}

/////////////////////////////////////////////////////////////////////////////
// COXWebView diagnostics

#ifdef _DEBUG
void COXWebView::AssertValid() const
	{
	CView::AssertValid();
	}

void COXWebView::Dump(CDumpContext& dc) const
	{
	CView::Dump(dc);
	}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COXWebView message handlers

int COXWebView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
	{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Fail if we cannot create the web control.

	if (!m_WebCtrl.Create(_T(""), WS_VISIBLE|WS_CHILD,
						  CRect(0, 0, 0, 0), this, IDC_WEB_CTRL))
		{
		TRACE0("COXWebView::OnCreate could not create web control\n");
		return -1;
		}

	// The control ID specified in the create function does
	// not actually get used for the container ID; instead,
	// zero is used. Unfortunately, the RepositionBars method
	// will not actually resize the web control if the container
	// ID is zero. Thus, we set it to something else here. Also,
	// FYI, this cannot be done with SetDlgCtrlID--it sneakily
	// checks to see if the window in question is a client site
	// and changes the ID of the ActiveX control instead. The
	// more MFC does, the more it frustrates customizations.

	SetWindowLong(m_WebCtrl.GetSafeHwnd(), GWL_ID, 1);

#ifdef _DEBUG
	// (Make sure OXWebViev.rc is included in your resource file)
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDR_OX_WEBVIEW_BAR), RT_TOOLBAR);
	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(IDR_OX_WEBVIEW_BAR), RT_TOOLBAR);
	ASSERT(hRsrc != NULL);
#endif

	// Fail if we cannot create the toolbar.
	if (!m_Toolbar.Create(this) ||
		!m_Toolbar.LoadToolBar(IDR_OX_WEBVIEW_BAR))
		{
		TRACE0("COXWebView::OnCreate could not create toolbar\n");
		return -1;
		}

	// Create the combobox on the toolbar.

	CRect rc;
	const int HEIGHT = 150;
	const int WIDTH = 200;
	CToolBarCtrl& t = m_Toolbar.GetToolBarCtrl();
	int nNum = t.GetButtonCount();
	t.GetItemRect(nNum - 1, &rc);
	CSize sizeOfs(rc.Width() / 2, rc.top);
	rc.top = sizeOfs.cy;
	rc.bottom = rc.top + HEIGHT;
	rc.left = rc.right + sizeOfs.cx;
	rc.right = rc.left + WIDTH;

	if (!m_cbxToolbarURL.Create(CBS_DROPDOWN|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL,
								rc, &t, IDC_TOOLBAR_URL))
		{
		TRACE0("COXWebView::OnCreate could not create toolbar URL combo-box\n");
		return -1;
		}
	m_cbxToolbarURL.SetFont(m_pfontToolbarURL, FALSE);

	// Add combobox edit control handling for entering URLs.

	CEditComboboxAdder* pCbxEdit;
	pCbxEdit = new CEditComboboxAdder(&m_cbxToolbarURL);
	ASSERT(pCbxEdit != NULL);

	// Load up the tooltips for the toolbar.

	VERIFY(m_Tooltips.Create(&m_Toolbar));
	for (int n = 0; n < nNum; n++)
		{
		TBBUTTON btn;
		t.GetButton(n, &btn);
		t.GetItemRect(n, &rc);
		m_Tooltips.AddTool(&t, LPSTR_TEXTCALLBACK, rc, btn.idCommand);
		}
	t.SetToolTips(&m_Tooltips);

	return 0;
	}

void COXWebView::OnSize(UINT nType, int cx, int cy) 
	{
	// First, make sure that the view window has finished
	// its own sizing.

	CView::OnSize(nType, cx, cy);
	UpdateWindow();

	// Now, force an update of the toolbar, and resize the
	// combobox to take advantage of all available room.

	CRect rcTB, rc, rcLast;
	RepositionBars(AFX_IDW_TOOLBAR, AFX_IDW_TOOLBAR, 1);
	CToolBarCtrl& t = m_Toolbar.GetToolBarCtrl();
	int nNum = t.GetButtonCount();
	t.GetClientRect(&rcTB);
	m_cbxToolbarURL.GetWindowRect(&rc);
	t.ScreenToClient(&rc);
	t.GetItemRect(nNum - 1, &rcLast);
	const int HOFS = rcLast.Width() / 2;
	rc.left = rcLast.right + HOFS;
	rc.right = rcTB.right;

	// Make sure the combobox is at least four buttons wide.

	if (rc.Width() < HOFS * 8)
		rc.right = rc.left + HOFS * 8;

	m_cbxToolbarURL.MoveWindow(rc);
	}

void COXWebView::OnUpdateWebviewBack(CCmdUI* pCmdUI) 
	{
	pCmdUI->Enable(m_bCanGoBack);
	}

void COXWebView::OnWebviewBack() 
	{
	m_WebCtrl.GoBack();
	}

void COXWebView::OnUpdateWebviewForward(CCmdUI* pCmdUI) 
	{
	pCmdUI->Enable(m_bCanGoForward);
	}

void COXWebView::OnWebviewForward() 
	{
	m_WebCtrl.GoForward();
	}

void COXWebView::OnWebviewHome() 
	{
	m_WebCtrl.GoHome();
	}

void COXWebView::OnWebviewSearch() 
	{
	m_WebCtrl.GoSearch();
	}

void COXWebView::OnUpdateWebviewStop(CCmdUI* pCmdUI) 
	{
	pCmdUI->Enable(m_WebCtrl.GetBusy());
	}

void COXWebView::OnWebviewStop() 
	{
	m_WebCtrl.Stop();
	}

void COXWebView::OnUpdateWebviewRefresh(CCmdUI* pCmdUI) 
	{
	pCmdUI->Enable(m_bCanRefresh);
	}

void COXWebView::OnWebviewRefresh() 
	{
	m_WebCtrl.Refresh();
	}

void COXWebView::OnToolbarURLChange()
	{
	int nSel = m_cbxToolbarURL.GetCurSel();
	if (nSel != CB_ERR)
		{
		CString s;
		m_cbxToolbarURL.GetLBText(nSel, s);
		m_WebCtrl.Navigate(s, NULL, NULL, NULL, NULL);
		}
	}

BOOL COXWebView::OnTooltipNeedText(UINT /* id */, NMHDR* pNMHDR, LRESULT* pResult)
	{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	CString strTipText;
	UINT nID = pNMHDR->idFrom;
	if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
		pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
		{
		// idFrom is actually the HWND of the tool
		nID = ((UINT)(WORD)::GetDlgCtrlID((HWND)nID));
		}

	if (nID != 0) // will be zero on a separator
		{
		strTipText.LoadString(nID);
		int nNewLine = strTipText.Find('\n');
		if (nNewLine != -1)
			strTipText = strTipText.Mid(nNewLine + 1);
		}
#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText,
            (sizeof(pTTTA->szText)/sizeof(pTTTA->szText[0])));
	else
		_mbstowcsz(pTTTW->szText, strTipText,
            (sizeof(pTTTW->szText)/sizeof(pTTTW->szText[0])));
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText,
            (sizeof(pTTTA->szText)/sizeof(pTTTA->szText[0])));
	else
		lstrcpyn(pTTTW->szText, strTipText,
            (sizeof(pTTTW->szText)/sizeof(pTTTW->szText[0])));
#endif
	*pResult = 0;

	// bring the tooltip window above other popup windows
	::SetWindowPos(pNMHDR->hwndFrom, HWND_TOP, 0, 0, 0, 0,
		SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOMOVE);

	return TRUE;    // message was handled
	}

void COXWebView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
	{
	pCmdUI->Enable(FALSE);	
	}

void COXWebView::OnFilePrint() 
	{
	m_WebCtrl.Print();	
	}

/////////////////////////////////////////////////////////////////////////////
// Web control notification handlers.

void COXWebView::BeforeNavigate(LPCTSTR /* pcszURL */, long /* lFlags */, LPCTSTR /* pcszTargetFrameName */, VARIANT* /* PostData */, LPCTSTR /* pcszHeaders */, VARIANT_BOOL* /* pbCancel */)
	// --- In  : pcszURL : The URL to which the view is about to navigate.
	//			 lFlags : (reserved for Microsoft's future use)
	//			 pcszTargetFrameName : String that contains the name of
	//								   the frame in which to display the
	//								   resource, or NULL if no named frame 
	//								   is targeted for the resource.
	//			 PostData : Address of data to send to the server if the 
	//						HTTP POST transaction is being used. 
	//			 pcszHeaders : Additional HTTP headers to send to the server 
	//						   (HTTP URLs only). The headers can specify 
	//						   such things as the action required of the 
	//						   server, the type of data being passed to the 
	//						   server, or a status code. 
	// --- Out : pbCancel : Address of cancel flag. An application can set 
	//						this parameter to TRUE to cancel the navigation 
	//						operation, or FALSE to allow it to proceed. 
	// --- Returns :
	// --- Effect : This method is called prior to a navigation operation.
	{
	//TRACE1("COXWebView::BeforeNavigate %s\n", pcszURL);
	}

void COXWebView::NavigateComplete(LPCTSTR /* pcszURL */)
	// --- In  : pcszURL : The URL to which the view is now positioned.
	// --- Out : 
	// --- Returns :
	// --- Effect : This method is called after a navigation operation 
	//				is completed.
	{
	m_bCanRefresh = TRUE;
	CString s = m_WebCtrl.GetLocationURL();
	m_cbxToolbarURL.SetWindowText(s);

	//TRACE1("COXWebView::NavigateComplete %s\n", pcszURL);
	}

void COXWebView::StatusTextChange(LPCTSTR /* pcszText */)
	// --- In  : pcszText : The message describing an event that 
	//						has occurred.
	// --- Out : 
	// --- Returns :
	// --- Effect : This method is called when something has happened of 
	//				which the application might want to inform the user.
	{
	//TRACE1("COXWebView::StatusTextChange %s\n", pcszText);
	}

void COXWebView::Quit(VARIANT_BOOL* /* pbCancel */)
	// --- In  : 
	// --- Out : pbCancel : Address of the cancel flag. An application 
	//						can set this parameter to TRUE to cancel the
	//						quit operation, or FALSE to allow it to 
	//						continue. 
	// --- Returns :
	// --- Effect : This method is called when the Internet Explorer 
	//				application is ready to quit.
	{
	//TRACE0("COXWebView::Quit\n");
	}

void COXWebView::DownloadBegin()
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Notifies an application that a navigation operation 
	//				is beginning. This event is fired shortly after the 
	//				BeforeNavigate event, unless the navigation is cancelled.
	{
	//TRACE0("COXWebView::DownloadBegin\n");
	}

void COXWebView::NewWindow(LPCTSTR /* pcszURL */, long /* lFlags */, LPCTSTR /* pcszTargetFrameName */, VARIANT* /* PostData */, LPCTSTR /* pcszHeaders */, VARIANT_BOOL* /* pbCancel */)
	// --- In  : pcszURL : The URL to which the view is about to navigate.
	//			 lFlags : (reserved for Microsoft's future use)
	//			 pcszTargetFrameName : String that contains the name of
	//								   the frame in which to display the
	//								   resource, or NULL if no named frame 
	//								   is targeted for the resource.
	//			 PostData : Address of data to send to the server if the 
	//						HTTP POST transaction is being used. 
	//			 pcszHeaders : Additional HTTP headers to send to the server 
	//						   (HTTP URLs only). The headers can specify 
	//						   such things as the action required of the 
	//						   server, the type of data being passed to the 
	//						   server, or a status code. 
	// --- Out : pbCancel : Address of cancel flag. An application can set 
	//						this parameter to TRUE to cancel the navigation 
	//						operation, or FALSE to allow it to proceed. 
	// --- Returns :
	// --- Effect : Notifies an application that a new window is to be 
	//				created for displaying a resource.
	{
	//TRACE1("COXWebView::NewWindow %s\n", pcszURL);
	}

void COXWebView::ProgressChange(long /* lProgress */, long /* lProgressMax */)
	// --- In  : lProgress : Amount of total progress to show, 
	//						 or -1 when progress is complete. 
	//			 lProgressMax : Maximum progress value. 
	// --- Out : 
	// --- Returns :
	// --- Effect : Notifies an application that the progress of a 
	//				download operation has been updated. 
	{
	//TRACE2("COXWebView::ProgressChange %i of %i\n", lProgress, lProgressMax);
	}

void COXWebView::DownloadComplete()
	// --- In  : 
	// --- Out : 
	// --- Returns :
	// --- Effect : Occurs when a navigation operation finished, was halted, 
	//				or failed. Unlike NavigateComplete which is only fired 
	//				when a URL is successfully navigated to, this event 
	//				is always fired after a navigation starts. Any animation 
	//				or "busy" indication that the container needs to display 
	//				should be connected to this event. 
	{
	//TRACE0("COXWebView::DownloadComplete\n");
	}

void COXWebView::CommandStateChange(long lCmdID, BOOL bEnabled)
	// --- In  : lCmdID : Identifier of the command whose enable state 
	//					  has changed. 
	//		     bEnabled : This parameter is TRUE if the command is 
	//						enabled, or FALSE if it is disabled.
	// --- Out : 
	// --- Returns :
	// --- Effect : Notifies an application that the enabled state of a Web 
	//				browser command has changed.
	{
	switch (lCmdID)
		{
		case CSC_NAVIGATEBACK:
			m_bCanGoBack = bEnabled;
			break;
		case CSC_NAVIGATEFORWARD:
			m_bCanGoForward = bEnabled;
			break;
		}

	// TRACE(_T("COXWebView::CommandStateChange 0x%X %i\n"), lCmdID, bEnabled);
	}

void COXWebView::PropertyChange(LPCTSTR /* pcszProperty */)
	// --- In  : pcszProperty : The name of the property that has changed.
	// --- Out : 
	// --- Returns :
	// --- Effect : Notifies an application that the IWebBrowser::PutProperty 
	//				function has changed the value of a property.
	{
	// TRACE1("COXWebView::PropertyChange %s\n", pcszProperty);
	}

void COXWebView::TitleChange(LPCTSTR /* pcszTitle */)
	// --- In  : pcszTitle : Caller allocated buffer that contains the 
	//						 new document title. 
	// --- Out : 
	// --- Returns :
	// --- Effect : Notifies an application that the title of a document 
	//				in the Web browser control becomes available or changes. 
	//				For HTML, the title may change; while HTML is still 
	//				downloading, the URL of the document is set as the title. 
	//				After the real title (if there is one) is parsed from the
	//				HTML, the title is changed to reflect the actual title. 
	{
	// TRACE1("COXWebView::TitleChange %s\n", pcszTitle);
	}

void COXWebView::FrameBeforeNavigate(LPCTSTR /* pcszURL */, long /* lFlags */, LPCTSTR /* pcszTargetFrameName */, VARIANT* /* PostData */, LPCTSTR /* pcszHeaders */, VARIANT_BOOL* /* pbCancel */)
	// --- In  : pcszURL : The URL to which the view is about to navigate.
	//			 lFlags : (reserved for Microsoft's future use)
	//			 pcszTargetFrameName : String that contains the name of
	//								   the frame in which to display the
	//								   resource, or NULL if no named frame 
	//								   is targeted for the resource.
	//			 PostData : Address of data to send to the server if the 
	//						HTTP POST transaction is being used. 
	//			 pcszHeaders : Additional HTTP headers to send to the server 
	//						   (HTTP URLs only). The headers can specify 
	//						   such things as the action required of the 
	//						   server, the type of data being passed to the 
	//						   server, or a status code. 
	// --- Out : pbCancel : Address of cancel flag. An application can set 
	//						this parameter to TRUE to cancel the navigation 
	//						operation, or FALSE to allow it to proceed. 
	// --- Returns :
	// --- Effect : Notifies an application that Web browser control is 
	//				about to navigate to a different URL, which may happen 
	//				as a result of external automation, internal automation 
	//				from a script, or the user clicking a link or typing in 
	//				the address bar. The container has an opportunity to 
	//				cancel the pending navigation. This event is fired for 
	//				navigations that occur inside an HTML frame. 
	{
	// TRACE1("COXWebView::FrameBeforeNavigate %s\n", pcszURL);
	}

void COXWebView::FrameNavigateComplete(LPCTSTR /* pcszURL */)
	// --- In  : pcszURL : URL to be navigated to. Note that this URL can be 
	//					   different from the URL that the browser was told 
	//					   to navigate to. 
	// --- Out : 
	// --- Returns :
	// --- Effect : Notifies an application that the browser has successfully 
	//				navigated to a new location. The document may still be 
	//				downloading (and in the case of HTML, images may still be 
	//				downloading), but at least part of the document has been 
	//				received from the server and the viewer for the document 
	//				has been created. This event is fired for navigations 
	//				that occur inside an HTML frame. 
	{
	// TRACE1("COXWebView::FrameNavigateComplete %s\n", pcszURL);
	}

void COXWebView::FrameNewWindow(LPCTSTR /* pcszURL */, long /* lFlags */, LPCTSTR /* pcszTargetFrameName */, VARIANT* /* PostData */, LPCTSTR /* pcszHeaders */, VARIANT_BOOL* /* pbCancel */)
	// --- In  : pcszURL : The URL to which the view is about to navigate.
	//			 lFlags : (reserved for Microsoft's future use)
	//			 pcszTargetFrameName : String that contains the name of
	//								   the frame in which to display the
	//								   resource, or NULL if no named frame 
	//								   is targeted for the resource.
	//			 PostData : Address of data to send to the server if the 
	//						HTTP POST transaction is being used. 
	//			 pcszHeaders : Additional HTTP headers to send to the server 
	//						   (HTTP URLs only). The headers can specify 
	//						   such things as the action required of the 
	//						   server, the type of data being passed to the 
	//						   server, or a status code. 
	// --- Out : pbCancel : Address of cancel flag. An application can set 
	//						this parameter to TRUE to cancel the navigation 
	//						operation, or FALSE to allow it to proceed. 
	// --- Returns :
	// --- Effect : Notifies an application that a new window is to be 
	//				created for displaying a resource. 
	{
	// TRACE1("COXWebView::FrameNewWindow %s\n", pcszURL);
	}

