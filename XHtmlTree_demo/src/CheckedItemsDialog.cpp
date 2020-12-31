// CheckedItemsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CheckedItemsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT WM_CHECKEDITEMSDIALOG_CLOSING = ::RegisterWindowMessage(_T("WM_CHECKEDITEMSDIALOG_CLOSING"));
	CRect m_rect;

/////////////////////////////////////////////////////////////////////////////
// CCheckedItemsDialog dialog

BEGIN_MESSAGE_MAP(CCheckedItemsDialog, CDialog)
	//{{AFX_MSG_MAP(CCheckedItemsDialog)
	ON_WM_MOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCheckedItemsDialog::CCheckedItemsDialog(CWnd* pParent, CPoint point)
{
	//TRACEPOINT(point);
	//{{AFX_DATA_INIT(CCheckedItemsDialog)
	//}}AFX_DATA_INIT
	m_pParent = pParent;
	m_rect.left = point.x;
	m_rect.top  = point.y;
	//TRACERECT(m_rect);
	VERIFY(Create(CCheckedItemsDialog::IDD, pParent));
}

void CCheckedItemsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckedItemsDialog)
	DDX_Control(pDX, IDC_EDIT_INVISIBLE, m_edit);
	DDX_Control(pDX, IDC_CHECKED_ITEMS, m_checkeditems);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCheckedItemsDialog message handlers

BOOL CCheckedItemsDialog::OnInitDialog() 
{
	TRACE(_T("in CCheckedItemsDialog::OnInitDialog\n"));
	CDialog::OnInitDialog();

	m_edit.MoveWindow(10000, 10000, 10, 10, FALSE);
	m_checkeditems.SetMargins(5, 5);

	//TRACERECT(m_rect);
	if ((m_rect.left != 0) || (m_rect.top != 0))
	{
		CRect rect;
		GetWindowRect(&rect);
		m_rect.right  = m_rect.left + rect.Width();
		m_rect.bottom = m_rect.top + rect.Height();
		MoveWindow(&m_rect);
		//TRACERECT(m_rect);
	}
	else
	{
		GetWindowRect(&m_rect);
		//TRACERECT(m_rect);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCheckedItemsDialog::SetText(LPCTSTR lpszText) 
{
	m_strText = lpszText;
	m_checkeditems.SetWindowText(m_strText);
}

// must do this for modeless dialogs
void CCheckedItemsDialog::OnCancel()
{
	TRACE(_T("in CCheckedItemsDialog::OnCancel\n"));
	DestroyWindow();
}

// this assumes dialog is created via new
void CCheckedItemsDialog::PostNcDestroy() 
{
	TRACE(_T("in CCheckedItemsDialog::PostNcDestroy\n"));
	delete this;	
	CDialog::PostNcDestroy();
}

void CCheckedItemsDialog::OnMove(int x, int y) 
{
	TRACE(_T("in CCheckedItemsDialog::OnMove\n"));
	CDialog::OnMove(x, y);
	
	//GetWindowRect(&m_rect);

	//TRACERECT(m_rect);
}

void CCheckedItemsDialog::OnDestroy() 
{
	TRACE(_T("in CCheckedItemsDialog::OnDestroy\n"));

	if (m_pParent)
	{
		GetWindowRect(&m_rect);
		//TRACERECT(m_rect);
		WORD l = (WORD) (m_rect.left & 0xFFFF);
		WORD t = (WORD) (m_rect.top & 0xFFFF);
		LPARAM lParam = MAKELPARAM(l, t);
		m_pParent->PostMessage(WM_CHECKEDITEMSDIALOG_CLOSING, 0, lParam);
	}
	
	CDialog::OnDestroy();
}
