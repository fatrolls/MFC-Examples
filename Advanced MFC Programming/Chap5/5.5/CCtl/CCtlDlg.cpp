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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCCtlDlg, CDialog)
	//{{AFX_MSG_MAP(CCCtlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCCtlDlg::OnInitDialog()
{
	int i;

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
	
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER_AUTOTICK))->SetRange(0, 10);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER_AUTOTICK))->SetTicFreq(2);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER_TICK))->SetRange(0, 50);
	for(i=0; i<=50; i+=i)
	{
		((CSliderCtrl *)GetDlgItem(IDC_SLIDER_TICK))->SetTic(i);
		if(i == 0)i=2;
	}
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER_SEL))->SetRange(50, 100);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER_SEL))->SetPageSize(40);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER_SEL))->SetLineSize(10);
	((CSliderCtrl *)GetDlgItem(IDC_SLIDER_SEL))->SetSelection(60, 90);

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


void CCCtlDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CString szStr;
	int nSliderPos=0;

	switch(pScrollBar->GetDlgCtrlID())
	{
		case IDC_SLIDER_AUTOTICK:
		{
			szStr="IDC_SLIDER_AUTOTICK";
			nSliderPos=((CSliderCtrl *)pScrollBar)->GetPos();
			break;
		}
		case IDC_SLIDER_TICK:
		{
			szStr="IDC_SLIDER_TICK";
			nSliderPos=((CSliderCtrl *)pScrollBar)->GetPos();
			break;
		}
		case IDC_SLIDER_SEL:
		{
			szStr="IDC_SLIDER_SEL";
			nSliderPos=((CSliderCtrl *)pScrollBar)->GetPos();
			break;
		}
		default:
		{
			szStr="None";
		}
	}
	TRACE("Slider %s, Current Pos=%d\n", (LPCSTR)szStr, nSliderPos);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
