#include "stdafx.h"
#include "DB.h"
#include "DBDlg.h"

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

CDBDlg::CDBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDBDlg, CDialog)
	//{{AFX_MSG_MAP(CDBDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDBDlg::OnInitDialog()
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

HBRUSH CDBDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor) 
{
	HBRUSH brush;

	switch(nCtlColor)
	{
		case CTLCOLOR_BTN:
		case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			brush=(HBRUSH)::GetStockObject(NULL_BRUSH);
			break;
		}
		case CTLCOLOR_EDIT:
		{
			pDC->SetBkMode(TRANSPARENT);
			brush=(HBRUSH)::GetStockObject(LTGRAY_BRUSH);
			break;
		}
		case CTLCOLOR_LISTBOX:
		{
			pDC->SetBkMode(TRANSPARENT);
			brush=(HBRUSH)::GetStockObject(GRAY_BRUSH);
			break;
		}
		case CTLCOLOR_MSGBOX:
		{
			brush=(HBRUSH)::GetStockObject(LTGRAY_BRUSH);
			break;
		}
		case CTLCOLOR_SCROLLBAR:
		{
			brush=(HBRUSH)::GetStockObject(GRAY_BRUSH);
			break;
		}
		default: brush=CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	return brush;
}

BOOL CDBDlg::OnEraseBkgnd(CDC *pDC) 
{
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	CDC dcMemory;
	BITMAP bm;
	CRect rect;
	int i, j;
	int nHor, nVer;

	bmp.LoadBitmap(IDB_BITMAP_DLGBGD);
	bmp.GetBitmap(&bm);
	GetClientRect(rect);
	nHor=rect.Width()/bm.bmWidth+1;
	nVer=rect.Height()/bm.bmHeight+1;
	dcMemory.CreateCompatibleDC(pDC);
	ptrBmpOld=dcMemory.SelectObject(&bmp);
	for(i=0; i<nHor; i++)
	{
		for(j=0; j<nVer; j++)
		{
			pDC->BitBlt
			(
				i*bm.bmWidth,
				j*bm.bmHeight,
				bm.bmWidth,
				bm.bmHeight,
				&dcMemory,
				0,
				0,
				SRCCOPY
			);
		}
	}
	dcMemory.SelectObject(ptrBmpOld);
	
	return TRUE;
}
