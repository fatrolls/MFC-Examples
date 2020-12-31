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
	DDX_Control(pDX, IDC_LIST, m_lbBmp);
	DDX_Control(pDX, IDC_COMBO, m_cbBmp);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCCtlDlg, CDialog)
	//{{AFX_MSG_MAP(CCCtlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCCtlDlg::OnInitDialog()
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
	
	m_cbBmp.AddString((LPCTSTR)COMBO_BUTTON);
	m_cbBmp.AddString((LPCTSTR)COMBO_BIGSMILE);
	m_cbBmp.AddString((LPCTSTR)COMBO_BUTTON);

	m_lbBmp.AddString((LPCTSTR)LIST_SMILE_1);
	m_lbBmp.AddString((LPCTSTR)LIST_SMILE_2);
	m_lbBmp.AddString((LPCTSTR)LIST_SMILE_3);
	m_lbBmp.AddString((LPCTSTR)LIST_SMILE_4);

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

void CCCtlDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	CDC *ptrDC;
	CDC dcMemory;
	CRect rect;
	BITMAP bm;

	if(nIDCtl == IDC_LIST)
	{
		switch(lpDrawItemStruct->itemData)
		{
			case LIST_SMILE_1:
			{
				bmp.LoadBitmap(IDB_BITMAP_SMILE_1);
				break;
			}
			case LIST_SMILE_2:
			{
				bmp.LoadBitmap(IDB_BITMAP_SMILE_2);
				break;
			}
			case LIST_SMILE_3:
			{
				bmp.LoadBitmap(IDB_BITMAP_SMILE_3);
				break;
			}
			case LIST_SMILE_4:
			{
				bmp.LoadBitmap(IDB_BITMAP_SMILE_4);
				break;
			}
		}
	}
	if(nIDCtl == IDC_COMBO)
	{
		switch(lpDrawItemStruct->itemData)
		{
			case COMBO_BUTTON:
			{
				if(lpDrawItemStruct->itemState & ODS_SELECTED)
				{
					bmp.LoadBitmap(IDB_BITMAP_BUTTON_SEL);
				}
				else
				{
					bmp.LoadBitmap(IDB_BITMAP_BUTTON_UNSEL);
				}
				break;
			}
			case COMBO_BIGSMILE:
			{
				if(lpDrawItemStruct->itemState & ODS_SELECTED)
				{
					bmp.LoadBitmap(IDB_BITMAP_BIG_SMILE_1);
				}
				else
				{
					bmp.LoadBitmap(IDB_BITMAP_BIG_SMILE_2);
				}
				break;
			}
		}
	}
	if((nIDCtl == IDC_COMBO || nIDCtl == IDC_LIST) && bmp.GetSafeHandle())
	{
		bmp.GetBitmap(&bm);
		ptrDC=CDC::FromHandle(lpDrawItemStruct->hDC);
		dcMemory.CreateCompatibleDC(ptrDC);
		rect=lpDrawItemStruct->rcItem;
		ptrBmpOld=dcMemory.SelectObject(&bmp);
		ptrDC->BitBlt
		(
			rect.left,
			rect.top,
			rect.Width(),
			rect.Height(),
			&dcMemory,
			0,
			0,
			SRCCOPY
		);
		if((lpDrawItemStruct->itemState & ODS_SELECTED) && nIDCtl == IDC_LIST)
		{
			ptrDC->BitBlt
			(
				rect.left,
				rect.top,
				bm.bmWidth,
				bm.bmHeight,
				NULL,
				0,
				0,
				DSTINVERT
			);
		}
		dcMemory.SelectObject(ptrBmpOld);
	}
}

void CCCtlDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	BITMAP bm;
	CBitmap bmp;

	switch(nIDCtl)
	{
		case IDC_LIST:
		{
			bmp.LoadBitmap(IDB_BITMAP_SMILE_1);
			bmp.GetBitmap(&bm);
			lpMeasureItemStruct->itemWidth=bm.bmWidth;
			lpMeasureItemStruct->itemHeight=bm.bmHeight;
			break;
		}
		case IDC_COMBO:
		{
			switch(lpMeasureItemStruct->itemData)
			{
				case COMBO_BUTTON:
				{
					bmp.LoadBitmap(IDB_BITMAP_BUTTON_SEL);
					bmp.GetBitmap(&bm);
					lpMeasureItemStruct->itemWidth=bm.bmWidth;
					lpMeasureItemStruct->itemHeight=bm.bmHeight;
					break;
				}
				case COMBO_BIGSMILE:
				{
					bmp.LoadBitmap(IDB_BITMAP_BIG_SMILE_1);
					bmp.GetBitmap(&bm);
					lpMeasureItemStruct->itemWidth=bm.bmWidth;
					lpMeasureItemStruct->itemHeight=bm.bmHeight;
					break;
				}
			}
			break;
		}
	}
}
