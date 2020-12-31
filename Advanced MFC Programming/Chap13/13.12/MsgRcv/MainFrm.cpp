#include "stdafx.h"
#include "MsgRcv.h"
#include "RcvDoc.h"
#include "RcvView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT g_uMsgSendStr=0;
UINT g_uMsgReceived=0;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(g_uMsgSendStr, OnSendStr)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	g_uMsgSendStr=::RegisterWindowMessage(MSG_SENDSTRING);
	g_uMsgReceived=::RegisterWindowMessage(MSG_RECEIVED);

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT &cs)
{
	cs.lpszClass=CLASS_NAME_RECIEVER;
	return CFrameWnd::PreCreateWindow(cs);
}

LONG CMainFrame::OnSendStr(UINT wParam, LONG lParam)
{
	CWnd *pWnd;
	CString szText;
	HANDLE hMapFile;
	LPSTR lpMapAddress;

	pWnd=CWnd::FromHandle((HWND)wParam);
	ASSERT(pWnd != NULL);
	pWnd->PostMessage(g_uMsgReceived);

	hMapFile=::OpenFileMapping
	(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		MAPPING_PROJECT
	);
 
	if(hMapFile != NULL)
	{ 
		lpMapAddress=(LPSTR)MapViewOfFile
		(
			hMapFile,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			0
		);
		if(lpMapAddress != NULL)
		{
			szText=lpMapAddress;
		}
		CEdit &editCtrl=((CEditView *)GetActiveView())->GetEditCtrl();
		editCtrl.SetSel(0, -1);
		editCtrl.ReplaceSel(szText);
	}
	return (LONG)TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif
