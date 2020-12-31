#include "stdafx.h"
#include "DB.h"
#include "BarDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT indicators[] =
{
	AFX_IDS_IDLEMESSAGE,
	IDS_MESSAGE
};

CBarDialog::CBarDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBarDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBarDialog)
	//}}AFX_DATA_INIT
}


void CBarDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBarDialog)
	//}}AFX_DATA_MAP
}

IMPLEMENT_DYNAMIC(CBarDialog, CDialog)

BEGIN_MESSAGE_MAP(CBarDialog, CDialog)
	//{{AFX_MSG_MAP(CBarDialog)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
	ON_MESSAGE(WM_POPMESSAGESTRING, OnPopMessageString)
END_MESSAGE_MAP()

BOOL CBarDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRect rectOld;
	CRect rectNew;
	CRect rect;	
	CPoint ptOffset;
	CWnd *pWndCtrl;

	CDialog::OnInitDialog();
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

BOOL CBarDialog::OnToolTipText(UINT, NMHDR *pNMHDR, LRESULT *pResult)
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

LRESULT CBarDialog::OnSetMessageString(WPARAM wParam, LPARAM lParam)
{
	UINT nIDMsg=(UINT)wParam;
	CString strMsg;

	if(nIDMsg)
	{
		if(strMsg.LoadString(nIDMsg) != 0)m_wndStatusBar.SetPaneText(0, strMsg);
	}   
	
	return nIDMsg;  
}

LRESULT CBarDialog::OnPopMessageString(WPARAM wParam, LPARAM lParam)
{
	if(m_nFlags & WF_NOPOPMSG)return 0;
	return SendMessage(WM_SETMESSAGESTRING, wParam, lParam);
}
