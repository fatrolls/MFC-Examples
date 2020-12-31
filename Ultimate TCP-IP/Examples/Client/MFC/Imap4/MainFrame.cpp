// MainFrame.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "IMAPClient.h"
#include "MainFrame.h"
#include "MessageFolderView.h"
#include "MessageListView.h"
#include "ConnectDlg.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_FILE_CONNECT, OnFileConnect)
	ON_UPDATE_COMMAND_UI(IDM_FILE_CONNECT, OnUpdateFileConnect)
	ON_COMMAND(IDM_FILE_DISCONNECT, OnFileDisconnect)
	ON_UPDATE_COMMAND_UI(IDM_FILE_DISCONNECT, OnUpdateFileDisconnect)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: m_bConnected(FALSE)
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /* lpcs */, CCreateContext* pContext) 
{
	// Setup splitters
	m_wndSplitter.CreateStatic(this, 1, 2);
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMessageFolderView), CSize(0, 0), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMessageListView), CSize(0, 0), pContext);
	m_wndSplitter.SetColumnInfo(0, 150, 0);

    m_imapClient.m_ptrListView = GetMessageListView();
	return TRUE;
}

void CMainFrame::OnFileConnect() 
{
	CConnectDlg dlg;

	dlg.m_sServer = _T("???????");
	dlg.m_sLogin = _T("???????");
	dlg.m_sPassword = _T(" ");
	
	if (dlg.DoModal() == IDOK) {

		int nResult = m_imapClient.IMAP4Connect(dlg.m_sServer, dlg.m_sLogin, dlg.m_sPassword);

		if (nResult == UTE_SUCCESS) {
			m_bConnected = TRUE;

			// fire the retrieve event
			CMessageFolderView* pView = GetMessageFolderView();
			pView->BuildFolderList();
		}
		else {

			CString sErrorMessage = CUT_ERR::GetErrorString(nResult);
			AfxMessageBox(sErrorMessage, MB_OK | MB_ICONSTOP);
		}
	}	
}

void CMainFrame::OnUpdateFileConnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bConnected);
}

void CMainFrame::OnFileDisconnect() 
{
	m_imapClient.IMAP4Close();
	m_bConnected = FALSE;
}

void CMainFrame::OnUpdateFileDisconnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bConnected);
}

void CMainFrame::OnClose() 
{
	if (m_bConnected)
		m_imapClient.IMAP4Close();

	CFrameWnd::OnClose();
}

/////////////////////////////////////////////////////////////////////////////
// 
// CMyIMAP4Class implementation

void CMyIMAP4Class::OnAlertMessage(LPCSTR lpszAlertMsg)
{
	CString s;
	s.Format(_T("An alert message was recieved from the IMAP server:\n\n%s"), lpszAlertMsg);
	AfxMessageBox(s, MB_OK | MB_ICONINFORMATION);
}

void CMyIMAP4Class::OnExpunge(long /* nMsgNumber */)
{
	// The message specified by `nMsgNumber' was expunged from the remote
	// database. 
	//
	// NOTE: nMsgNumber specifies the zero-based sequence index of the message
	//       in the selected folder.


}

BOOL CMyIMAP4Class::OnFetch(CUT_MsgData & /* data */)
{
	return FALSE;
}

void CMyIMAP4Class::OnExists(long /* nMsgNumber */)
{
}

void CMyIMAP4Class::OnRecent(long nMsgNumber)
{
    if(nMsgNumber > 0) {
        _TCHAR    szSet[25];

        _stprintf(szSet, _T("%d:*"), m_lMailBoxMsgNumber - nMsgNumber + 1);
        if(MessageFetch(szSet, MSG_BODY_HEADER) == UTE_SUCCESS) {
            CUT_MsgData    *ptrMsgData;
            for (int i = 0; i < GetMsgDataListSize(); i++) {
                if(GetMsgDataListItem(i, ptrMsgData) != UTE_SUCCESS)
                    break;

                m_ptrListView->AddMessageEntry(ptrMsgData);
                }
            }
        }
}


#pragma warning ( pop )