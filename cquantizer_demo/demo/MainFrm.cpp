// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "demo.h"

#include "MainFrm.h"
#include "demodoc.h"
#include "DlgCapture.h"

#include "ximage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**************************************/
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_FILE_SELECTSOURCE, OnFileSelectsource)
	ON_COMMAND(ID_FILE_ACQUIRE, OnFileAcquire)
	ON_WM_CLOSE()
	ON_COMMAND(ID_FILE_CAPTURE, OnFileCapture)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR1,
	ID_INDICATOR2,
	ID_INDICATOR3,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/**************************************/
// CMainFrame construction/destruction
CMainFrame::CMainFrame()
{ }
CMainFrame::~CMainFrame()
{ }
/**************************************/
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndProgressBar.Create(WS_CHILD,CRect(200,2,262,18),&m_wndStatusBar,ID_INDICATOR1))
	{
		TRACE0("Failed to create progress bar\n");
		return -1;      // fail to create
	}
	m_wndProgressBar.ShowWindow(SW_SHOW);
	m_wndProgressBar.SetRange(0,100);

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// <<<TWAIN>>>
	InitTwain(m_hWnd);
//	if(!IsValidDriver()) AfxMessageBox("Unable to load Twain Driver.");

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/**************************************/
// CMainFrame diagnostics
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG

/**************************************/
// CMainFrame message handlers
void CMainFrame::OnEditPaste() 
{
	CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 

	if (NewDoc)	{
		HANDLE hBitmap=NULL;
		CBitmap bmpClip;
		if (OpenClipboard()) hBitmap=GetClipboardData(CF_DIB);
		if (hBitmap){
			CxImage *newima = new CxImage(hBitmap);
			NewDoc->image = newima;
		}
		CloseClipboard();

		CString s;
		s.Format("Clipboard Image %d",((CDemoApp*)AfxGetApp())->m_nDocCount++);
		NewDoc->SetTitle(s);
		NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
		NewDoc->UpdateStatusBar();
	}
}
/**************************************/
void CMainFrame::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	if(!IsClipboardFormatAvailable(CF_DIB)) pCmdUI->Enable(FALSE);
}
/**************************************/
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (CMDIFrameWnd::OnCreateClient(lpcs, pContext)){  
		// Subclass the MDIClient to print the logo in the 
		// bottom right corner....See CLogoMdi in logomdi.cpp
        m_LogoMdiClientWnd.SubclassWindow(m_hWndMDIClient) ; 
        return TRUE ;
	} else {
        return FALSE ;
	}
}
/**************************************/
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if (CTwain::SourceEnabled()) //<<<TWAIN>>>
		return CTwain::ProcessMessage(*pMsg);			//process twain
	else
		return CMDIFrameWnd::PreTranslateMessage(pMsg);	//other message
}
/**************************************/
void CMainFrame::OnFileSelectsource() 
{
	CTwain::SelectSource(); //<<<TWAIN>>>
}
/**************************************/
void CMainFrame::OnFileAcquire() 
{
	CTwain::Acquire(TWCPP_ANYCOUNT); //<<<TWAIN>>>
}
/**************************************/
void CMainFrame::OnClose() 
{
	CTwain::ReleaseTwain(); //<<<TWAIN>>>
	CMDIFrameWnd::OnClose();
}
/**************************************/
void CMainFrame::SetImage(HANDLE hBitmap,TW_IMAGEINFO& info)
{ //<<<TWAIN>>>
	CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
	if (NewDoc)	{
		if (hBitmap){
			CxImage *newima = new CxImage(hBitmap);
			NewDoc->image = newima;
		}
		CString s;
		s.Format("Acquired Image %d",((CDemoApp*)AfxGetApp())->m_nDocCount++);
		NewDoc->SetTitle(s);
		NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
		NewDoc->UpdateStatusBar();
	}
}
/**************************************/
void CMainFrame::OnFileCapture() 
{
	DlgCapture dlg;
	if (dlg.DoModal()==IDOK){
		// get the desired window from dialog box
		HWND hwnd=dlg.m_SelectedWnd;
		// get window size
		CRect r;
		::GetWindowRect(hwnd,&r);
		CSize sz(r.Width(), r.Height());

		// bring the window at the top most level
		::SetWindowPos(hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

		// prepare the DCs
		HDC dstDC = ::GetDC(NULL);
        HDC srcDC = ::GetWindowDC(hwnd); //full window (::GetDC(hwnd); = clientarea)
		HDC memDC = ::CreateCompatibleDC(dstDC);
		
		// copy the screen to the bitmap
		HBITMAP bm =::CreateCompatibleBitmap(dstDC, sz.cx, sz.cy);
		HBITMAP oldbm = (HBITMAP)::SelectObject(memDC,bm);
		::BitBlt(memDC, 0, 0, sz.cx, sz.cy, srcDC, 0, 0, SRCCOPY);
	
		// restore the position
		::SetWindowPos(hwnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		::SetWindowPos(m_hWnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

		// prepare the new document
		CDemoDoc *NewDoc=(CDemoDoc*)((CDemoApp*)AfxGetApp())->demoTemplate->OpenDocumentFile(NULL); 
		if (NewDoc)	{
			CxImage *newima = new CxImage(bm);
			NewDoc->image = newima;
			CString s;
			s.Format("Captured Image %d",((CDemoApp*)AfxGetApp())->m_nDocCount++);
			NewDoc->SetTitle(s);
			NewDoc->UpdateAllViews(0,WM_USER_NEWIMAGE);
			NewDoc->UpdateStatusBar();
		}

		// free objects
		SelectObject(memDC,oldbm);    
		DeleteObject(memDC);
	}
}
/**************************************/
void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIFrameWnd::OnSize(nType, cx, cy);
	
	m_wndProgressBar.SetWindowPos(0,max(200,cx-370),2,0,0,SWP_NOZORDER|SWP_NOSIZE);
}
/**************************************/
