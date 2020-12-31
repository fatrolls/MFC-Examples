// ComboTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComboTree.h"
#include "ComboTreeDlg.h"
#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CComboTreeDlg dialog

CComboTreeDlg::CComboTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComboTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComboTreeDlg)
	m_nOXTreeHeight = 0;
	m_nOXTreeWidth = 0;
	m_nShellHeight = 0;
	m_nShellWidth = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CComboTreeDlg::~CComboTreeDlg()
{
}
void CComboTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComboTreeDlg)
	DDX_Text(pDX, IDC_EDIT_OXTREEHEIGHT, m_nOXTreeHeight);
	DDV_MinMaxUInt(pDX, m_nOXTreeHeight, 0, 300);
	DDX_Text(pDX, IDC_EDIT_OXTREEWIDTH, m_nOXTreeWidth);
	DDV_MinMaxUInt(pDX, m_nOXTreeWidth, 0, 300);
	DDX_Text(pDX, IDC_EDIT_SHELLTREEHEIGHT, m_nShellHeight);
	DDV_MinMaxUInt(pDX, m_nShellHeight, 0, 300);
	DDX_Text(pDX, IDC_EDIT_SHELLTREEWIDTH, m_nShellWidth);
	DDV_MinMaxUInt(pDX, m_nShellWidth, 0, 300);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CComboTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CComboTreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboTreeDlg message handlers

BOOL CComboTreeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	InitializeControls();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CComboTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CComboTreeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CComboTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CComboTreeDlg::InitializeControls()
{
	//initializing shell tree
	VERIFY(m_pckShell.Create(WS_CHILD | WS_VISIBLE | CBS_OWNERDRAWFIXED | CBS_DROPDOWNLIST, 
		CRect(20,30,160,40),this,IDC_PICKER));
	VERIFY(m_cmbShell.Create(WS_CHILD | TVS_HASBUTTONS | TVS_TRACKSELECT | TVS_LINESATROOT | TVS_HASLINES,
		CRect(0,0,0,0),this,IDC_COMBO));

	m_cmbShell.SetOwnerCombo(&m_pckShell);
	m_pckShell.AttachDropDown(&m_cmbShell);
	m_pckShell.SetMaxDropdownHeight(200);
	m_cmbShell.InitializeTree();

	//initializing COXTreeCtrl combo
	VERIFY(m_pckOXTree.Create(WS_CHILD | WS_VISIBLE | CBS_OWNERDRAWFIXED | CBS_DROPDOWNLIST, 
		CRect(220,30,380,40),this,IDC_PICKER_OX));
	VERIFY(m_cmbOXTree.Create(WS_CHILD | TVS_HASBUTTONS | TVS_TRACKSELECT | TVS_LINESATROOT | TVS_HASLINES,
		CRect(0,0,0,0),this,IDC_COMBO_OX,NULL));

	m_cmbOXTree.SetOwnerCombo(&m_pckOXTree);





static CImageList	m_il; m_il.Create(IDB_BITMAP1,32,1,RGB(255,255,255));
static CImageList	m_il1; m_il1.Create(IDB_BITMAP1,32,1,RGB(255,255,255));
static CImageList	m_ils; m_ils.Create(IDB_BITMAP2,13,1,RGB(255,255,255));
	
	CStringArray saComboStr;
	CStringArray saDates;
	saDates.Add(_T("01/01/1998"));
	saDates.Add(_T("31/12/1998"));
	int i=0;
	for(i=0;i < 10;i++)
	{
		CString s;
		s.Format(_T("Option %d"),i+1);
		saComboStr.Add(s);
	}

	CString sItem;
	for (i = 1; i<=10; i++)
	{
		sItem.Format(_T("Item %d"),i);
		m_cmbOXTree.InsertItem(sItem);
	}

	LV_COLUMN lvc;
	memset(&lvc,0,sizeof(lvc));
	lvc.fmt = LVCFMT_LEFT;
	lvc.cx = 100;
	lvc.pszText = _T("Column");
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	m_cmbOXTree.SetColumn(0,&lvc);
	m_cmbOXTree.InsertColumn(1,_T("Dummy"),LVCFMT_LEFT,100,1);
	m_cmbOXTree.InsertColumn(2,_T("SuperDummy"),LVCFMT_LEFT,100,2);
	m_cmbOXTree.InsertColumn(3,_T("ComboBox"),LVCFMT_LEFT,100,3);
	m_cmbOXTree.InsertColumn(4,_T("Dates"),LVCFMT_RIGHT,100,4);
	m_cmbOXTree.SetImageList(&m_il1,TVSIL_NORMAL);
	m_cmbOXTree.SetImageList(&m_ils,TVSIL_STATE);
	for(i=0;i<1;i++)
	{
		CString sItem;
		sItem.Format(_T("Item %d"),i);
		HTREEITEM hti = m_cmbOXTree.InsertItem(sItem,TVI_ROOT);
		sItem.Format(_T("Column2 Item %d"),i);
		m_cmbOXTree.SetSubItem(hti,1,OX_SUBITEM_TEXT,sItem);
		m_cmbOXTree.SetSubItem(hti,2,OX_SUBITEM_TEXT,sItem);
		m_cmbOXTree.SetNoEditMode(hti,1);
		m_cmbOXTree.SetNoEditMode(hti,2);
		m_cmbOXTree.SetSubItem(hti,3,OX_SUBITEM_TEXT|OX_SUBITEM_IMAGE,sItem,1);
//		m_cmbOXTree.SetItemColor(hti,RGB(255 - 10*i,0,0));
//		m_cmbOXTree.SetItemColor(hti,RGB(0,255 - 10*i,0),1);
		m_cmbOXTree.SetEditMode(hti,OXET_COMBO,saComboStr,3);

		m_cmbOXTree.SetSubItem(hti,4,OX_SUBITEM_TEXT,_T("None"));
		m_cmbOXTree.SetEditMode(hti,OXET_CALENDAR,saDates,4);
		TV_ITEM tvi;
		memset(&tvi,0,sizeof(tvi));
		tvi.cChildren=1;
		tvi.mask=TVIF_CHILDREN | TVIF_HANDLE;
		tvi.hItem = hti;
		if(!i)
		{
			tvi.mask |= TVIF_TEXT;
			tvi.pszText = LPSTR_TEXTCALLBACK;
			m_cmbOXTree.SetItem(&tvi);
		}
		else if(i == 1)
		{
			tvi.mask |= TVIF_STATE;
			tvi.stateMask = TVIS_STATEIMAGEMASK;
			tvi.state = INDEXTOSTATEIMAGEMASK(2);
			m_cmbOXTree.SetItem(&tvi);
		}
		else if(i == 2)
		{
			LOGFONT lf;
			CFont f,*pF = GetFont();
			if(pF->GetLogFont(&lf))
			{
				lf.lfItalic = TRUE;
				f.CreateFontIndirect(&lf);
				m_cmbOXTree.SetItemFont(hti,&f);
			}
			m_cmbOXTree.SetItem(&tvi);
		}
		else
			m_cmbOXTree.SetItem(&tvi);

		m_cmbOXTree.SetItemImage(hti,0,1);

		for(int j=100;j >= 0;j--)
		{
			sItem.Format(_T("Item %d-%d"),i,j);
			HTREEITEM h =m_cmbOXTree.InsertItem(sItem,hti);
			if(!j)
			{
				CFont f;
				f.CreatePointFont(-80,_T("Arial"));
				m_cmbOXTree.SetItemFont(h,&f);
			}

			sItem.Format(_T("Option %d"),j);
			m_cmbOXTree.SetSubItem(h,1,OX_SUBITEM_TEXT,sItem);
			m_cmbOXTree.SetSubItem(h,2,OX_SUBITEM_TEXT,sItem);
			m_cmbOXTree.SetNoEditMode(h,1);
			m_cmbOXTree.SetNoEditMode(h,2);
			m_cmbOXTree.SetSubItem(h,3,OX_SUBITEM_TEXT,sItem);
			m_cmbOXTree.SetEditMode(h,OXET_COMBO,saComboStr,3);
			m_cmbOXTree.SetSubItem(h,4,OX_SUBITEM_TEXT,_T("None"));
			m_cmbOXTree.SetEditMode(h,OXET_CALENDAR,saDates,4);

			for(int k=0;k<10;k++)
			{
				sItem.Format(_T("Item %d-%d -%d"),i,j,k);
				HTREEITEM hSubitem=m_cmbOXTree.InsertItem(sItem,h);
				sItem.Format(_T("SubItem %d"),k);
				m_cmbOXTree.SetSubItem(hSubitem,1,OX_SUBITEM_TEXT,sItem);
				m_cmbOXTree.SetSubItem(hSubitem,2,OX_SUBITEM_TEXT,sItem);
				m_cmbOXTree.SetNoEditMode(hSubitem,1);
				m_cmbOXTree.SetNoEditMode(hSubitem,2);
				m_cmbOXTree.SetSubItem(hSubitem,3,OX_SUBITEM_TEXT|OX_SUBITEM_IMAGE,
					sItem,1);
				m_cmbOXTree.SetPlainEditMode(hSubitem,1);

				if(k == 1)
				{
					tvi.mask = TVIF_STATE | TVIF_HANDLE | TVIF_CHILDREN;
					tvi.cChildren=1;
					tvi.hItem = hSubitem;
					tvi.stateMask = TVIS_STATEIMAGEMASK;
					tvi.state = INDEXTOSTATEIMAGEMASK(2);
					m_cmbOXTree.SetItem(&tvi);
				}
			}
		}
	}

	m_cmbOXTree.ModifyExStyle(0,TVOXS_COLUMNHDR);
	m_cmbOXTree.ModifyExStyle(0,TVOXS_MULTISEL);
	m_cmbOXTree.ModifyStyle(0,TVS_EDITLABELS);
	m_cmbOXTree.ModifyStyle(0,TVS_HASBUTTONS);
	m_cmbOXTree.ModifyStyle(0,TVS_HASLINES);
	m_cmbOXTree.ModifyStyle(0,TVS_LINESATROOT);
	m_cmbOXTree.ModifyStyle(0,TVS_SHOWSELALWAYS);
	m_cmbOXTree.ModifyExStyle(0,TVOXS_VGRID);
	m_cmbOXTree.ModifyExStyle(0,TVOXS_HGRID);
	m_cmbOXTree.ModifyExStyle(0,TVOXS_FLGRID);
	m_cmbOXTree.ModifyExStyle(0,TVOXS_ROWSEL);
	m_cmbOXTree.ModifyExStyle(0,TVOXS_PICKANYWHERE);
	m_cmbOXTree.ModifyExStyle(0,TVOXS_ITEMTIPS);


	m_pckOXTree.AttachDropDown(&m_cmbOXTree);
	m_pckOXTree.SetMaxDropdownHeight(300);
	m_cmbOXTree.ShowWindow(SW_SHOW);

	m_cmbOXTree.SelectItem(m_cmbOXTree.GetNextItem(TVI_ROOT,TVGN_CHILD));

//	m_cmbOXTree.SelectItem(m_cmbOXTree.GetItemFromIndex(0));

	UpdateData(FALSE);


}

void CComboTreeDlg::OnApply() 
{
	UpdateData();

	m_cmbOXTree.SetMinWidthHeight(1,1);
	m_cmbOXTree.SetMaxWidthHeight(m_nOXTreeWidth?m_nOXTreeWidth:-1,
		m_nOXTreeHeight?m_nOXTreeHeight:-1);
	m_cmbShell.SetMinWidthHeight(1,1);
	m_cmbShell.SetMaxWidthHeight(m_nShellWidth?m_nShellWidth:-1,
		m_nShellHeight?m_nShellHeight:-1);
}
