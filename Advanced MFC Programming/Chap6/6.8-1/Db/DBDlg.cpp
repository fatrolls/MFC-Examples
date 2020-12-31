#include "stdafx.h"
#include "DB.h"
#include "DBDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	AFX_IDS_IDLEMESSAGE,
	IDS_MESSAGE
};

CDBDlg::CDBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBDlg)
	//}}AFX_DATA_INIT
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBDlg)
	//}}AFX_DATA_MAP
}

IMPLEMENT_DYNAMIC(CDBDlg, CDialog)

BEGIN_MESSAGE_MAP(CDBDlg, CDialog)
	//{{AFX_MSG_MAP(CDBDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
	ON_MESSAGE(WM_POPMESSAGESTRING, OnPopMessageString)
END_MESSAGE_MAP()

BOOL CDBDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	CRect rectOld;
	CRect rectNew;
	CRect rect;	
	CPoint ptOffset;
	CWnd *pWndCtrl;

	GetClientRect(rectOld);	

	if 
	(
		!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDD)
	)
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	if
	(
		!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators
		(
			indicators,
			sizeof(indicators)/sizeof(UINT)
		)
	)
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}
	m_wndStatusBar.SetPaneInfo
	(
		0,
		m_wndStatusBar.GetItemID(0),
		SBPS_STRETCH,
		NULL
	);

	m_wndToolBar.SetBarStyle
	(
		m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY
	);
	RepositionBars
	(
		AFX_IDW_CONTROLBAR_FIRST,
		AFX_IDW_CONTROLBAR_LAST, 
		0,
		CWnd::reposQuery,
		rectNew
	);
	
	ptOffset.x=rectNew.left-rectOld.left;
	ptOffset.y=rectNew.top-rectOld.top;
	
	pWndCtrl=GetWindow(GW_CHILD);
	while(pWndCtrl)
	{                               
		pWndCtrl->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.OffsetRect(ptOffset);
		pWndCtrl->MoveWindow(rect, FALSE);
		pWndCtrl=pWndCtrl->GetNextWindow();
	}
	GetWindowRect(rect);
	rect.right+=rectOld.Width()-rectNew.Width();
	rect.bottom+=rectOld.Height()-rectNew.Height();
	MoveWindow(rect);
	RepositionBars
	(
		AFX_IDW_CONTROLBAR_FIRST,
		AFX_IDW_CONTROLBAR_LAST,
		0
	);

	return TRUE;
}

void CDBDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CDBDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CDBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CDBDlg::OnToolTipText(UINT, NMHDR *pNMHDR, LRESULT *pResult)
{
	TOOLTIPTEXT* pTTT=(TOOLTIPTEXT*)pNMHDR;
	CString szTip;

	UINT nID=pNMHDR->idFrom;
	if(pNMHDR->code == TTN_NEEDTEXT && (pTTT->uFlags & TTF_IDISHWND))
	{
		nID=((UINT)(WORD)::GetDlgCtrlID((HWND)nID));
	}

	if(nID != 0)
	{
		szTip.LoadString(nID);
		szTip=szTip.Right(szTip.GetLength()-szTip.Find('\n')-1);
		lstrcpy(pTTT->szText, szTip);
		*pResult = 0;

		return TRUE;
	}
	*pResult=-1;
	return FALSE;
}

LRESULT CDBDlg::OnSetMessageString(WPARAM wParam, LPARAM lParam)
{
	UINT nIDMsg=(UINT)wParam;
	CString strMsg;

	if(nIDMsg)
	{
		if(strMsg.LoadString(nIDMsg) != 0)m_wndStatusBar.SetPaneText(0, strMsg);
	}   
	
	return nIDMsg;  
}

LRESULT CDBDlg::OnPopMessageString(WPARAM wParam, LPARAM lParam)
{
	if(m_nFlags & WF_NOPOPMSG)return 0;
	return SendMessage(WM_SETMESSAGESTRING, wParam, lParam);
}
