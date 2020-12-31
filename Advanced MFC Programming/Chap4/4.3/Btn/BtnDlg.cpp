#include "stdafx.h"
#include "Btn.h"
#include "BtnDlg.h"

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

CBtnDlg::CBtnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBtnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBtnDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBtnDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBtnDlg, CDialog)
	//{{AFX_MSG_MAP(CBtnDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_BN_CLICKED(IDC_RADIO_A, OnRadioA)
	ON_BN_CLICKED(IDC_RADIO_B, OnRadioB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBtnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	m_btnPlay.SubclassDlgItem(IDC_PLAY, this);
	m_btnPlay.LoadBitmaps
	(
		"PLAYU",
		"PLAYD",
		NULL,
		NULL
	);
	m_btnPlay.SizeToContent();
	m_bmpCheck.LoadBitmap(IDB_BITMAP_CHECK);
	m_bmpUnCheck.LoadBitmap(IDB_BITMAP_UNCHECK);
	((CButton *)GetDlgItem(IDC_CHECK))->SetBitmap
	(
		(HBITMAP)m_bmpUnCheck.GetSafeHandle()
	);
	((CButton *)GetDlgItem(IDC_RADIO_A))->SetBitmap
	(
		(HBITMAP)m_bmpUnCheck.GetSafeHandle()
	);
	((CButton *)GetDlgItem(IDC_RADIO_B))->SetBitmap
	(
		(HBITMAP)m_bmpUnCheck.GetSafeHandle()
	);
	
	return TRUE;
}

void CBtnDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBtnDlg::OnPaint() 
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

HCURSOR CBtnDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBtnDlg::OnCheck() 
{
	SetCheckBitmap(IDC_CHECK);
}

void CBtnDlg::OnRadioA() 
{
	SetCheckBitmap(IDC_RADIO_A);
	SetCheckBitmap(IDC_RADIO_B);
}

void CBtnDlg::OnRadioB() 
{
	SetCheckBitmap(IDC_RADIO_B);
	SetCheckBitmap(IDC_RADIO_A);
}

void CBtnDlg::SetCheckBitmap(UINT nID)
{
	BOOL bCheck;

	bCheck=((CButton *)GetDlgItem(nID))->GetCheck();
	((CButton *)GetDlgItem(nID))->SetBitmap
	(
		bCheck ? (HBITMAP)m_bmpCheck.GetSafeHandle():
				 (HBITMAP)m_bmpUnCheck.GetSafeHandle()
	);
	Invalidate(FALSE);
}
