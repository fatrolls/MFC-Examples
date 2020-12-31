#include "stdafx.h"
#include "CCtl.h"
#include "CCtlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BMP_SIZE_X		16
#define BMP_SIZE_Y		15

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
	DDX_Control(pDX, IDC_TREE, m_treeCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCCtlDlg, CDialog)
	//{{AFX_MSG_MAP(CCCtlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCCtlDlg::OnInitDialog()
{
	TV_INSERTSTRUCT tvInsertStruct;
	CBitmap bmp;
	HTREEITEM hTreeItem;
	CImageList *pilCtrl;

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
	
	pilCtrl=new CImageList();
	pilCtrl->Create(BMP_SIZE_X, BMP_SIZE_Y, ILC_MASK, 5, 0);
	
	bmp.LoadBitmap(IDB_BITMAP_ROOT);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();
	
	bmp.LoadBitmap(IDB_BITMAP_DOC);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP_CLOSEDFOLDER);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP_OPENFOLDER);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_BITMAP_LEAF);
	pilCtrl->Add(&bmp, RGB(255, 255, 255));
	bmp.DeleteObject();

	pilCtrl->SetBkColor(RGB(255, 255, 255));
	m_treeCtrl.SetImageList(pilCtrl, TVSIL_NORMAL);

	tvInsertStruct.hParent=NULL;
	tvInsertStruct.hInsertAfter=TVI_LAST;
	tvInsertStruct.item.iImage=0;
	tvInsertStruct.item.iSelectedImage=0;
	tvInsertStruct.item.pszText="Root";
	tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;

	hTreeItem=m_treeCtrl.InsertItem(&tvInsertStruct);
	ASSERT(hTreeItem);

	tvInsertStruct.hParent=hTreeItem;
	tvInsertStruct.hInsertAfter=TVI_LAST;
	tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE| TVIF_TEXT;
	tvInsertStruct.item.iImage=1;
	tvInsertStruct.item.iSelectedImage=1;
	tvInsertStruct.item.pszText="Doc";

	hTreeItem=m_treeCtrl.InsertItem(&tvInsertStruct);
	ASSERT(hTreeItem);

	tvInsertStruct.hParent=hTreeItem;
	tvInsertStruct.hInsertAfter=TVI_LAST;
	tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE| TVIF_TEXT;
	tvInsertStruct.item.iImage=2;
	tvInsertStruct.item.iSelectedImage=2;
	tvInsertStruct.item.pszText="Folder";

	hTreeItem=m_treeCtrl.InsertItem(&tvInsertStruct);
	ASSERT(hTreeItem);

	tvInsertStruct.hParent=hTreeItem;
	tvInsertStruct.hInsertAfter=TVI_LAST;
	tvInsertStruct.item.mask=TVIF_IMAGE | TVIF_SELECTEDIMAGE| TVIF_TEXT;
	tvInsertStruct.item.iImage=4;
	tvInsertStruct.item.iSelectedImage=4;
	tvInsertStruct.item.pszText="Leaf 1";

	m_treeCtrl.InsertItem(&tvInsertStruct);
	tvInsertStruct.item.pszText="Leaf 2";
	m_treeCtrl.InsertItem(&tvInsertStruct);
	tvInsertStruct.item.pszText="Leaf 3";
	m_treeCtrl.InsertItem(&tvInsertStruct);
	tvInsertStruct.item.pszText="Leaf 4";
	m_treeCtrl.InsertItem(&tvInsertStruct);
	tvInsertStruct.item.pszText="Leaf 5";

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

void CCCtlDlg::OnDestroy() 
{
	CImageList *pilCtrl;

	pilCtrl=m_treeCtrl.GetImageList(TVSIL_NORMAL);
	pilCtrl->DeleteImageList();
	delete pilCtrl;
	m_treeCtrl.DeleteAllItems();

	CDialog::OnDestroy();
}
