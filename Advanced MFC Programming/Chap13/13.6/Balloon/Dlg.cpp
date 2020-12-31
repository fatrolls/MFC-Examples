#include "stdafx.h"
#include "Balloon.h"
#include "Dlg.h"

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

CBalloonDlg::CBalloonDlg(CWnd* pParent /*=NULL*/) : CDialog(CBalloonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBalloonDlg)
	//}}AFX_DATA_INIT
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bCapture=FALSE;
}

void CBalloonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBalloonDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBalloonDlg, CDialog)
	//{{AFX_MSG_MAP(CBalloonDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBalloonDlg::OnInitDialog()
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

	return TRUE;
}

void CBalloonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBalloonDlg::OnPaint() 
{
	if(IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon=GetSystemMetrics(SM_CXICON);
		int cyIcon=GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x=(rect.Width()-cxIcon+1)/2;
		int y=(rect.Height()-cyIcon+1)/2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rect;
		CWindowDC dc(this);
		CBrush brush;
		CBrush *pBrOld;
		CPen *pPenOld;
		POINT pt[3];

		GetClientRect(rect);
		brush.CreateSolidBrush(RGB(255, 255, 0));
		pBrOld=dc.SelectObject(&brush);
		pPenOld=(CPen *)dc.SelectStockObject(NULL_PEN);
		dc.Ellipse(rect);
		pt[0].x=rect.left;
		pt[0].y=rect.bottom;
		pt[1].x=(rect.left+rect.right)/2;
		pt[1].y=(rect.top+rect.bottom)/2;
		pt[2].x=pt[1].x-rect.Width()/4;
		pt[2].y=pt[1].y;
		dc.Polygon(pt, 3);
		dc.SelectObject(pPenOld);
		dc.SelectObject(pBrOld);
	}
}

HCURSOR CBalloonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CBalloonDlg::OnEraseBkgnd(CDC *pDC) 
{
	return TRUE;
}

void CBalloonDlg::OnNcPaint() 
{
}

void CBalloonDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	POINT pt;

	CDialog::OnLButtonDown(nFlags, point);
	SetCapture();
	m_bCapture=TRUE;
	pt=point;
	ClientToScreen(&pt);
	m_ptMouse=pt;
}

void CBalloonDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rect;
	POINT pt;

	CDialog::OnLButtonUp(nFlags, point);
	if(m_bCapture == TRUE)
	{
		m_bCapture=FALSE;
		::ReleaseCapture();
		pt=point;
		ClientToScreen(&pt);
		GetWindowRect(rect);
		rect.OffsetRect(CPoint(pt)-m_ptMouse);
		MoveWindow(rect);
	}
}

void CBalloonDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rect;
	POINT pt;

	CDialog::OnMouseMove(nFlags, point);
	if((nFlags & MK_LBUTTON) && m_bCapture)
	{
		pt=point;
		ClientToScreen(&pt);
		GetWindowRect(rect);
		rect.OffsetRect(CPoint(pt)-m_ptMouse);
		m_ptMouse=pt;
		MoveWindow(rect);
	}
}
