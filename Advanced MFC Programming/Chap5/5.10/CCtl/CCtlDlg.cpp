#include "stdafx.h"
#include "CCtl.h"
#include "CCtlDlg.h"

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

CCCtlDlg::CCCtlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCCtlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCCtlDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCCtlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCCtlDlg)
	DDX_Control(pDX, IDC_COMBO_SIMPLE, m_cbSimple);
	DDX_Control(pDX, IDC_COMBO_DROPLIST, m_cbDropList);
	DDX_Control(pDX, IDC_COMBO_DROPDOWN, m_cbDropDown);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCCtlDlg, CDialog)
	//{{AFX_MSG_MAP(CCCtlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_CLOSEUP(IDC_COMBO_DROPDOWN, OnCloseupComboDropdown)
	ON_CBN_CLOSEUP(IDC_COMBO_DROPLIST, OnCloseupComboDroplist)
	ON_CBN_SELCHANGE(IDC_COMBO_SIMPLE, OnSelchangeComboSimple)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_COMBO_RETURN, OnComboReturn)
END_MESSAGE_MAP()

BOOL CCCtlDlg::OnInitDialog()
{
	CEdit *ptrEdit;
	HWND hwndEdit;
	char szClassName[256];

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
	
	ptrEdit=(CEdit *)m_cbDropDown.GetWindow(GW_CHILD);
	hwndEdit=ptrEdit->GetSafeHwnd();
	::GetClassName(hwndEdit, szClassName, 256);
	if(memcmp(szClassName, "Edit", sizeof("Edit")))
	{
		ptrEdit=(CEdit *)ptrEdit->GetWindow(GW_HWNDNEXT);
		hwndEdit=ptrEdit->GetSafeHwnd();
	}
	m_editChar.SubclassWindow(hwndEdit);
	ptrEdit=(CEdit *)m_cbSimple.GetWindow(GW_CHILD);
	hwndEdit=ptrEdit->GetSafeHwnd();
	::GetClassName(hwndEdit, szClassName, 256);
	if(memcmp(szClassName, "Edit", sizeof("Edit")))
	{
		ptrEdit=(CEdit *)ptrEdit->GetWindow(GW_HWNDNEXT);
		hwndEdit=ptrEdit->GetSafeHwnd();
	}
	m_editNum.SubclassWindow(hwndEdit);
	m_cbDropDown.AddString("Item 1");
	m_cbDropDown.AddString("Item 2");
	m_cbDropDown.AddString("Item 3");
	m_cbDropDown.AddString("Item 4");
	
	return TRUE;
}

void CCCtlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCCtlDlg::OnPaint() 
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

HCURSOR CCCtlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LONG CCCtlDlg::OnComboReturn(UINT wParam, LONG lParam)
{
	CComboBox *ptrCombo;
	CEdit *ptrEdit;
	HWND hwndEdit;
	CString szStr;
	CString szStrLB;
	char szClassName[256];
	int nSize;
	int i;
	BOOL bHit;

	ptrCombo=(CComboBox *)GetDlgItem(wParam);
	ptrEdit=(CEdit *)ptrCombo->GetWindow(GW_CHILD);
	hwndEdit=ptrEdit->GetSafeHwnd();
	::GetClassName(hwndEdit, szClassName, 256);
	if(memcmp(szClassName, "Edit", sizeof("Edit")))
	{
		ptrEdit=(CEdit *)ptrEdit->GetWindow(GW_HWNDNEXT);
		hwndEdit=ptrEdit->GetSafeHwnd();
	}
	ptrEdit->GetWindowText(szStr);
	if(!szStr.IsEmpty())
	{
		ptrEdit->SetSel(0, -1);
		nSize=ptrCombo->GetCount();
		bHit=FALSE;
		for(i=0; i<nSize; i++)
		{
			ptrCombo->GetLBText(i, szStrLB);
			if(szStrLB == szStr)
			{
				bHit=TRUE;
				break;
			}
		}
	}
	if(bHit == FALSE)
	{
		ptrCombo->AddString(szStr);
		if(wParam == IDC_COMBO_DROPDOWN)
		{
			GetDlgItem(IDC_STATIC_DROPDOWN)->SetWindowText(szStr);
		}
		if(wParam == IDC_COMBO_SIMPLE)
		{
			GetDlgItem(IDC_STATIC_SIMPLE)->SetWindowText(szStr);
		}
	}
	return (LRESULT)TRUE;
}

BOOL CCCtlDlg::PreTranslateMessage(MSG *pMsg) 
{
	CString str;
	HWND hwndFocus;
	HWND hwndEdit;
	CEdit *ptrEdit;
	int nVirtKey;
	char szClassName[256];

	if(pMsg->message == WM_KEYDOWN)
	{
		nVirtKey=(int)pMsg->wParam;
		if(nVirtKey == VK_RETURN)
		{
			hwndFocus=GetFocus()->GetSafeHwnd();
			if(hwndFocus == NULL)return CDialog::PreTranslateMessage(pMsg);
			ptrEdit=(CEdit *)m_cbDropDown.GetWindow(GW_CHILD);
			hwndEdit=ptrEdit->GetSafeHwnd();
			::GetClassName(hwndEdit, szClassName, 256);
			if(memcmp(szClassName, "Edit", sizeof("Edit")))
			{
				ptrEdit=(CEdit *)ptrEdit->GetWindow(GW_HWNDNEXT);
				hwndEdit=ptrEdit->GetSafeHwnd();
			}
			if(hwndFocus == hwndEdit)
			{
				PostMessage(WM_COMBO_RETURN, (WPARAM)IDC_COMBO_DROPDOWN, (LPARAM)0);
				return TRUE;
			}
			ptrEdit=(CEdit *)m_cbSimple.GetWindow(GW_CHILD);
			hwndEdit=ptrEdit->GetSafeHwnd();
			::GetClassName(hwndEdit, szClassName, 256);
			if(memcmp(szClassName, "Edit", sizeof("Edit")))
			{
				ptrEdit=(CEdit *)ptrEdit->GetWindow(GW_HWNDNEXT);
				hwndEdit=ptrEdit->GetSafeHwnd();
			}
			if(hwndFocus == hwndEdit)
			{
				PostMessage(WM_COMBO_RETURN, (WPARAM)IDC_COMBO_SIMPLE, (LPARAM)0);
				return TRUE;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CCCtlDlg::OnCloseupComboDropdown() 
{
	CString szStr;
	int nSel;

	nSel=m_cbDropDown.GetCurSel();
	if(nSel != CB_ERR)
	{
		m_cbDropDown.GetLBText(nSel, szStr);
	}
	GetDlgItem(IDC_STATIC_DROPDOWN)->SetWindowText(szStr);
}

void CCCtlDlg::OnCloseupComboDroplist() 
{
	CString szStr;
	int nSel;

	nSel=m_cbDropList.GetCurSel();
	if(nSel != CB_ERR)
	{
		m_cbDropList.GetLBText(nSel, szStr);
	}
	GetDlgItem(IDC_STATIC_DROPLIST)->SetWindowText(szStr);
}

void CCCtlDlg::OnSelchangeComboSimple() 
{
	CString szStr;
	int nSel;

	nSel=m_cbSimple.GetCurSel();
	if(nSel != CB_ERR)
	{
		m_cbSimple.GetLBText(nSel, szStr);
	}
	GetDlgItem(IDC_STATIC_SIMPLE)->SetWindowText(szStr);
}
