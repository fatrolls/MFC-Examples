#include "stdafx.h"
#include "Ctl.h"
#include "CtlDlg.h"

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

CCtlDlg::CCtlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCtlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCtlDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCtlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCtlDlg)
	DDX_Control(pDX, IDC_LIST_DIR, m_listDir);
	DDX_Control(pDX, IDC_LIST_MULCOL, m_listMCBox);
	DDX_Control(pDX, IDC_LIST, m_listBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCtlDlg, CDialog)
	//{{AFX_MSG_MAP(CCtlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCtlDlg::OnInitDialog()
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
	
	m_listBox.AddString("List box item 1");
	m_listBox.AddString("List box item 2");
	m_listBox.AddString("List box item 3");
	m_listBox.AddString("List box item 4");

	m_listMCBox.AddString("Item 1");
	m_listMCBox.AddString("Item 2");
	m_listMCBox.AddString("Item 3");
	m_listMCBox.AddString("Item 4");
	m_listMCBox.AddString("Item 5");
	m_listMCBox.AddString("Item 6");
	m_listMCBox.AddString("Item 7");
	m_listMCBox.AddString("Item 8");
	m_listMCBox.AddString("Item 9");
	m_listMCBox.AddString("Item 10");
	m_listMCBox.AddString("Item 11");
	m_listMCBox.AddString("Item 12");
	m_listMCBox.AddString("Item 13");
	m_listMCBox.AddString("Item 14");
	m_listMCBox.AddString("Item 15");
	m_listMCBox.AddString("Item 16");
	m_listMCBox.AddString("Item 17");
	m_listMCBox.AddString("Item 18");
	m_listMCBox.AddString("Item 19");
	m_listMCBox.AddString("Item 20");

	m_listMCBox.SetColumnWidth(50);

	m_listDir.Dir(0x10, "*.*");

	return TRUE;
}

void CCtlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCtlDlg::OnPaint() 
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

HCURSOR CCtlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
