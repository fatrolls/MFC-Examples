// ExtTreeDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExtTreeDemo.h"
#include "ExtTreeDemoDlg.h"

#include "UTSampleAbout.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtTreeDemoDlg dialog

CExtTreeDemoDlg::CExtTreeDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExtTreeDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExtTreeDemoDlg)
	m_bShowColumnHdr = FALSE;
	m_bMultiSel = FALSE;
	m_bEditLabels = FALSE;
	m_bHasButtons = FALSE;
	m_bHasLines = FALSE;
	m_bHasLinesAtRoot = FALSE;
	m_bShowSelAlways = FALSE;
	m_bHasHGrid = FALSE;
	m_bHasVGrid = FALSE;
	m_bRowSel = FALSE;
	m_bFullLength = FALSE;
	m_bPickAnywhere = FALSE;
	m_bItemTips = FALSE;
	m_bNoSortHeader = FALSE;
	m_bNoScroll = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDragImage=NULL;
	m_bDragging=FALSE;
	m_hDropItem = NULL;
}

CExtTreeDemoDlg::~CExtTreeDemoDlg()
{
	if(m_pDragImage)
	{
		delete m_pDragImage;
	}
}

void CExtTreeDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtTreeDemoDlg)
	DDX_Control(pDX, IDC_LIST2, m_xlc);
	DDX_Check(pDX, IDC_TVOXS_COLUMNHDR, m_bShowColumnHdr);
	DDX_Check(pDX, IDC_TVOXS_MULTISEL, m_bMultiSel);
	DDX_Check(pDX, IDC_TVS_EDITLABELS, m_bEditLabels);
	DDX_Check(pDX, IDC_TVS_HASBUTTONS, m_bHasButtons);
	DDX_Check(pDX, IDC_TVS_HASLINES, m_bHasLines);
	DDX_Check(pDX, IDC_TVS_HASLINESATROOT, m_bHasLinesAtRoot);
	DDX_Check(pDX, IDC_TVS_SHOWSELALWAYS, m_bShowSelAlways);
	DDX_Check(pDX, IDC_TVOXS_HGRID, m_bHasHGrid);
	DDX_Check(pDX, IDC_TVOXS_VGRID, m_bHasVGrid);
	DDX_Check(pDX, IDC_TVOXS_ROWSEL, m_bRowSel);
	DDX_Check(pDX, IDC_TVOXS_FLGRID, m_bFullLength);
	DDX_Check(pDX, IDC_TVOXS_PICKANYWHERE, m_bPickAnywhere);
	DDX_Check(pDX, IDC_TVOXS_ITEMTIPS, m_bItemTips);
	DDX_Check(pDX, IDC_TVOXS_NOSORTHEADER, m_bNoSortHeader);
	DDX_Check(pDX, IDC_TVOXS_NOSCROLL, m_bNoScroll);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExtTreeDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CExtTreeDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_GETDISPINFO, IDC_LIST2, OnGetdispinfoTree1)
	ON_BN_CLICKED(IDC_TVOXS_COLUMNHDR, OnTvoxsColumnhdr)
	ON_BN_CLICKED(IDC_TVOXS_MULTISEL, OnTvoxsMultisel)
	ON_BN_CLICKED(IDC_TVS_EDITLABELS, OnTvsEditlabels)
	ON_BN_CLICKED(IDC_TVS_HASBUTTONS, OnTvsHasbuttons)
	ON_BN_CLICKED(IDC_TVS_HASLINES, OnTvsHaslines)
	ON_BN_CLICKED(IDC_TVS_HASLINESATROOT, OnTvsHaslinesatroot)
	ON_BN_CLICKED(IDC_TVS_SHOWSELALWAYS, OnTvsShowselalways)
	ON_BN_CLICKED(IDC_HIDE, OnHide)
	ON_BN_CLICKED(IDC_UNHIDE_ALL, OnUnhideAll)
	ON_BN_CLICKED(IDC_ADD_TO_FOCUS, OnAddToFocus)
	ON_BN_CLICKED(IDC_SET_FONT, OnSetFontToSel)
	ON_BN_CLICKED(IDC_TOGGLE_DISABLE, OnToggleDisable)
	ON_BN_CLICKED(IDC_TVOXS_VGRID, OnVgrid)
	ON_BN_CLICKED(IDC_TVOXS_HGRID, OnHgrid)
	ON_BN_CLICKED(IDC_TVOXS_ROWSEL, OnRowSel)
	ON_BN_CLICKED(IDC_TVOXS_FLGRID, OnFullLength)
	ON_BN_CLICKED(IDC_TVOXS_PICKANYWHERE, OnPickAnywhere)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST2, OnBegindragList2)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST2, OnItemclickList2)
	ON_BN_CLICKED(IDC_TVOXS_ITEMTIPS, OnTvoxsItemtips)
	ON_BN_CLICKED(IDC_TVOXS_NOSCROLL, OnTvoxsNoscroll)
	ON_BN_CLICKED(IDC_TVOXS_NOSORTHEADER, OnTvoxsNosortheader)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickList2)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_LIST2, OnItemExpandingTree1)
	ON_BN_CLICKED(IDC_DELETE_SELECTED, OnDeleteSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtTreeDemoDlg message handlers

BOOL CExtTreeDemoDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here



	m_il.Create(IDB_BITMAP1,16,1,RGB(255,255,255));
	m_il1.Create(IDB_BITMAP1,16,1,RGB(255,255,255));
	m_ils.Create(IDB_BITMAP2,13,1,RGB(255,255,255));
	
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

	LV_COLUMN lvc;
	memset(&lvc,0,sizeof(lvc));
	lvc.fmt = LVCFMT_LEFT;
	lvc.cx = 100;
	lvc.pszText = _T("Column");
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	m_xlc.SetColumn(0,&lvc);
	m_xlc.InsertColumn(1,_T("ComboBox"),LVCFMT_CENTER,100,1);
	m_xlc.InsertColumn(2,_T("Dates"),LVCFMT_RIGHT,100,2);
	m_xlc.SetImageList(&m_il1,TVSIL_NORMAL);
	m_xlc.SetImageList(&m_ils,TVSIL_STATE);
	for(i=0;i<10;i++)
	{
		CString sItem;
		sItem.Format(_T("Item %d"),i);
		HTREEITEM hti = m_xlc.InsertItem(sItem);
		sItem.Format(_T("Column2 Item %d"),i);
		m_xlc.SetSubItem(hti,1,OX_SUBITEM_TEXT|OX_SUBITEM_IMAGE,sItem,1);
		m_xlc.SetItemColor(hti,RGB(255 - 10*i,0,0));
		m_xlc.SetItemColor(hti,RGB(0,255 - 10*i,0),1);
		m_xlc.SetEditMode(hti,OXET_COMBO,saComboStr,1);

		m_xlc.SetSubItem(hti,2,OX_SUBITEM_TEXT,_T("None"));
		m_xlc.SetEditMode(hti,OXET_CALENDAR,saDates,2);
		TV_ITEM tvi;
		memset(&tvi,0,sizeof(tvi));
		tvi.cChildren=1;
		tvi.mask=TVIF_CHILDREN | TVIF_HANDLE;
		tvi.hItem = hti;
		if(!i)
		{
			tvi.mask |= TVIF_TEXT;
			tvi.pszText = LPSTR_TEXTCALLBACK;
			m_xlc.SetItem(&tvi);
		}
		else if(i == 1)
		{
			tvi.mask |= TVIF_STATE;
			tvi.stateMask = TVIS_STATEIMAGEMASK;
			tvi.state = INDEXTOSTATEIMAGEMASK(2);
			m_xlc.SetItem(&tvi);
		}
		else if(i == 2)
		{
			LOGFONT lf;
			CFont f,*pF = GetFont();
			if(pF->GetLogFont(&lf))
			{
				lf.lfItalic = TRUE;
				f.CreateFontIndirect(&lf);
				m_xlc.SetItemFont(hti,&f);
			}
			m_xlc.SetItem(&tvi);
		}
		else
			m_xlc.SetItem(&tvi);

		m_xlc.SetItemImage(hti,0,1);

	}

	m_xlc.ModifyExStyle(0,TVOXS_COLUMNHDR);
	m_xlc.ModifyExStyle(0,TVOXS_MULTISEL);
	m_xlc.ModifyStyle(0,TVS_EDITLABELS);
	m_xlc.ModifyStyle(0,TVS_HASBUTTONS);
	m_xlc.ModifyStyle(0,TVS_HASLINES);
	m_xlc.ModifyStyle(0,TVS_LINESATROOT);
	m_xlc.ModifyStyle(0,TVS_SHOWSELALWAYS);
	m_xlc.ModifyExStyle(0,TVOXS_VGRID);
	m_xlc.ModifyExStyle(0,TVOXS_HGRID);
	m_xlc.ModifyExStyle(0,TVOXS_FLGRID);
	m_xlc.ModifyExStyle(0,TVOXS_ROWSEL);
	m_xlc.ModifyExStyle(0,TVOXS_PICKANYWHERE);
	m_xlc.ModifyExStyle(0,TVOXS_ITEMTIPS);

	m_bHasLines = m_xlc.HasLines() > 0 ? TRUE : FALSE;
	m_bHasButtons = m_xlc.HasButtons() > 0 ? TRUE : FALSE;
	m_bHasLinesAtRoot = m_xlc.HasLinesAtRoot() > 0 ? TRUE : FALSE;
	DWORD dwStyle = m_xlc.GetStyle();
	m_bEditLabels = (dwStyle & TVS_EDITLABELS) > 0 ? TRUE : FALSE;
	m_bShowSelAlways = (dwStyle & TVS_SHOWSELALWAYS) > 0 ? TRUE : FALSE;
	DWORD dwStyleEx = m_xlc.GetExStyle();
	m_bShowColumnHdr = (dwStyleEx & TVOXS_COLUMNHDR) > 0 ? TRUE : FALSE;
	m_bMultiSel = 	(dwStyleEx & TVOXS_MULTISEL) > 0 ? TRUE : FALSE;
	m_bHasHGrid = 	(dwStyleEx & TVOXS_HGRID) > 0 ? TRUE : FALSE;
	m_bHasVGrid = 	(dwStyleEx & TVOXS_VGRID) > 0 ? TRUE : FALSE;
	m_bFullLength = 	(dwStyleEx & TVOXS_FLGRID) > 0 ? TRUE : FALSE;
	m_bRowSel =  	(dwStyleEx & TVOXS_ROWSEL) > 0 ? TRUE : FALSE;
	m_bPickAnywhere =  	(dwStyleEx & TVOXS_PICKANYWHERE) > 0 ? TRUE : FALSE;
	m_bItemTips = (dwStyleEx & TVOXS_ITEMTIPS) > 0 ? TRUE : FALSE;	
	m_bNoScroll = (dwStyleEx & TVOXS_NOSCROLL) > 0 ? TRUE : FALSE;	
	m_bNoSortHeader = (dwStyleEx & TVOXS_NOSORTHEADER) > 0 ? TRUE : FALSE;	

	m_xlc.ShowWindow(SW_SHOW);

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExtTreeDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME, ID_DESCRIPTION_FILE);
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

void CExtTreeDemoDlg::OnPaint() 
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
HCURSOR CExtTreeDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CExtTreeDemoDlg::OnGetdispinfoTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDI = (TV_DISPINFO*)pNMHDR;
	TV_ITEM *tvi = &(pTVDI->item);
	static int hit=0;
	if(tvi->mask & TVIF_TEXT)
	{
		TCHAR t[20];
		UTBStr::stprintf(t, 20, _T("Hit %d"),hit++);
		ASSERT(tvi->pszText);
		ASSERT(tvi->pszText != LPSTR_TEXTCALLBACK);

		UTBStr::tcsncpy(tvi->pszText, tvi->cchTextMax, t,tvi->cchTextMax);
	}
	
	*pResult = 1;
}

void CExtTreeDemoDlg::OnTvoxsColumnhdr() 
{
	UpdateData();
	if(m_bShowColumnHdr)
		m_xlc.ModifyExStyle(0,TVOXS_COLUMNHDR,SWP_DRAWFRAME);
	else
		m_xlc.ModifyExStyle(TVOXS_COLUMNHDR,0,SWP_DRAWFRAME);

}

void CExtTreeDemoDlg::OnTvoxsMultisel() 
{
	UpdateData();
	if(m_bMultiSel)
		m_xlc.ModifyExStyle(0,TVOXS_MULTISEL);
	else
		m_xlc.ModifyExStyle(TVOXS_MULTISEL,0);
}

void CExtTreeDemoDlg::OnTvsEditlabels() 
{
	UpdateData();
	if(m_bEditLabels)
		m_xlc.ModifyStyle(0,TVS_EDITLABELS);
	else
		m_xlc.ModifyStyle(TVS_EDITLABELS,0);
	
}

void CExtTreeDemoDlg::OnTvsHasbuttons() 
{
	UpdateData();
	if(m_bHasButtons)
		m_xlc.ModifyStyle(0,TVS_HASBUTTONS);
	else
		m_xlc.ModifyStyle(TVS_HASBUTTONS,0);
	
}

void CExtTreeDemoDlg::OnTvsHaslines() 
{
	UpdateData();
	if(m_bHasLines)
		m_xlc.ModifyStyle(0,TVS_HASLINES);
	else
		m_xlc.ModifyStyle(TVS_HASLINES,0);
	
}

void CExtTreeDemoDlg::OnTvsHaslinesatroot() 
{
	UpdateData();
	if(m_bHasLinesAtRoot)
		m_xlc.ModifyStyle(0,TVS_LINESATROOT);
	else
		m_xlc.ModifyStyle(TVS_LINESATROOT,0);
	
}

void CExtTreeDemoDlg::OnTvsShowselalways() 
{
	UpdateData();
	if(m_bShowSelAlways)
		m_xlc.ModifyStyle(0,TVS_SHOWSELALWAYS);
	else
		m_xlc.ModifyStyle(TVS_SHOWSELALWAYS,0);
	
}

void CExtTreeDemoDlg::OnHide() 
{
	HTREEITEM hItem = m_xlc.GetNextItem(TVI_ROOT,TVGN_FIRSTSELECTED);
	while(hItem)
	{
		HTREEITEM hItem1 = hItem;
		hItem = m_xlc.GetNextItem(hItem,TVGN_NEXTSELECTED);
		m_xlc.HideItem(hItem1);
	}
}

void CExtTreeDemoDlg::OnUnhideAll() 
{
	HTREEITEM hItem = m_xlc.GetFirstHiddenItem();
	while(hItem)
	{
		HTREEITEM hItem1 = hItem;
		hItem = m_xlc.GetNextHiddenItem(hItem);
		m_xlc.HideItem(hItem1,FALSE);
	}
}

void CExtTreeDemoDlg::OnAddToFocus() 
{
	static int hit=0;
	HTREEITEM hItem = m_xlc.GetSelectedItem();
	hItem= hItem==NULL ? m_xlc.GetRootItem() : hItem;
	if(hItem)
	{
		CString s;
		s.Format(_T("New Item %d"),++hit);
		hItem=m_xlc.InsertItem(s,hItem,TVI_SORT);
		ASSERT(hItem!=NULL);
		m_xlc.SelectItem(hItem);
		m_xlc.EnsureVisible(hItem);
		m_xlc.EditLabel(hItem);
	}
}

void CExtTreeDemoDlg::OnSetFontToSel() 
{
	CFontDialog fnt_dlg;
	if(fnt_dlg.DoModal() != IDOK)
		return;
	LOGFONT lf;
	fnt_dlg.GetCurrentFont(&lf);
	CFont f;
	f.CreateFontIndirect(&lf);
	HTREEITEM hItem = m_xlc.GetNextItem(TVI_ROOT,TVGN_FIRSTSELECTED);
	while(hItem)
	{
		m_xlc.SetItemFont(hItem,&f,0);
		m_xlc.SetItemFont(hItem,&f,1);
		m_xlc.SetItemFont(hItem,&f,2);
		m_xlc.SetItemColor(hItem,fnt_dlg.m_cf.rgbColors);
		m_xlc.SetItemColor(hItem,fnt_dlg.m_cf.rgbColors,1);
		m_xlc.SetItemColor(hItem,fnt_dlg.m_cf.rgbColors,2);
		hItem = m_xlc.GetNextItem(hItem,TVGN_NEXTSELECTED);
	}

	UINT nHeight=m_xlc.GetItemHeight();
	lf.lfHeight=(lf.lfHeight>0 ? lf.lfHeight : -lf.lfHeight)+6;
	if(lf.lfHeight>(int)nHeight)
	{
		m_xlc.SetItemHeight(lf.lfHeight);
	}
}

void CExtTreeDemoDlg::OnToggleDisable() 
{
	HTREEITEM hItem = m_xlc.GetNextItem(TVI_ROOT,TVGN_FIRSTSELECTED);
	while(hItem)
	{
		m_xlc.DisableItem(hItem,!m_xlc.IsItemDisabled(hItem));
		hItem = m_xlc.GetNextItem(hItem,TVGN_NEXTSELECTED);
	}
}

void CExtTreeDemoDlg::OnVgrid() 
{
	UpdateData();
	DWORD dwStyleAdd = m_bHasVGrid ? TVOXS_VGRID : 0;
	DWORD dwStyleRemove = m_bHasVGrid ? 0 : TVOXS_VGRID;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}

void CExtTreeDemoDlg::OnHgrid() 
{
	UpdateData();
	DWORD dwStyleAdd = m_bHasHGrid ? TVOXS_HGRID : 0;
	DWORD dwStyleRemove = m_bHasHGrid ? 0 : TVOXS_HGRID;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}

void CExtTreeDemoDlg::OnFullLength() 
{
	UpdateData();
	DWORD dwStyleAdd = m_bFullLength ? TVOXS_FLGRID : 0;
	DWORD dwStyleRemove = m_bFullLength ? 0 : TVOXS_FLGRID;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}


void CExtTreeDemoDlg::OnRowSel() 
{
	UpdateData();
	DWORD dwStyleAdd = m_bRowSel ? TVOXS_ROWSEL : 0;
	DWORD dwStyleRemove = m_bRowSel ? 0 : TVOXS_ROWSEL;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}


void CExtTreeDemoDlg::OnPickAnywhere() 
{
	UpdateData();
	DWORD dwStyleAdd = m_bPickAnywhere ? TVOXS_PICKANYWHERE : 0;
	DWORD dwStyleRemove = m_bPickAnywhere ? 0 : TVOXS_PICKANYWHERE;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}

void CExtTreeDemoDlg::OnBegindragList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(m_pDragImage)
	{
		delete m_pDragImage;
	}

	HTREEITEM hDragItem = m_xlc.GetSelectedItem();
	ASSERT (hDragItem);
	m_pDragImage = m_xlc.CreateDragImage (hDragItem);
	ASSERT (m_pDragImage);

	// changes the cursor to the drag image (DragMove() is still required in 
	// OnMouseMove())
	VERIFY (m_pDragImage->BeginDrag (0, CPoint (8, 8)));
	VERIFY (m_pDragImage->DragEnter (GetDesktopWindow (), pNMListView->ptAction));

	// set dragging flag
	m_bDragging = TRUE;
	m_hDropItem = NULL;

	// capture all mouse messages
	SetCapture ();

	*pResult = 0;
}

void CExtTreeDemoDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_bDragging)
	{
		CPoint pt (point);
		ClientToScreen (&pt);

		// move the drag image
		VERIFY (m_pDragImage->DragMove (pt));

		BOOL bDraw=FALSE;

		// get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT (pDropWnd);
		// if we drag outside current window
		if (pDropWnd != &m_xlc)
		{
			// turn off drag hilite for tree control
			if (m_hDropItem)
			{
				if(!bDraw)
				{
					// unlock window updates
					VERIFY (m_pDragImage->DragShowNolock(FALSE));
					bDraw=TRUE;
				}
				m_xlc.SelectDropTarget (NULL);
				m_hDropItem = NULL;
			}
		}

		// convert from screen coordinates to drop target client coordinates
		pDropWnd->ScreenToClient (&pt);

		// if window is CTreeCtrl
		if (pDropWnd == &m_xlc)
		{ 
			UINT uFlags;
			// get the item that is below cursor
			int nIndex=m_xlc.HitTest(pt, &uFlags);
			if(nIndex>=0)
			{
				m_hDropItem = m_xlc.GetItemFromIndex(nIndex);
				HTREEITEM hOldDropItem=m_xlc.GetNextItem(m_xlc.GetRootItem(),
					TVGN_DROPHILITE);
				if(hOldDropItem!=m_hDropItem)
				{
					if(!bDraw)
					{
						// unlock window updates
						VERIFY (m_pDragImage->DragShowNolock(FALSE));
						bDraw=TRUE;
					}
					// highlight it
					m_xlc.SelectDropTarget(m_hDropItem);
				}
			}
		}

		if(bDraw)
		{
			// lock window updates
			VERIFY (m_pDragImage->DragShowNolock (TRUE));
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CExtTreeDemoDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_bDragging)
	{
		// end dragging
		VERIFY (m_pDragImage->DragLeave (GetDesktopWindow ())); 
		m_pDragImage->EndDrag ();
		// stop intercepting all mouse messages
		VERIFY (::ReleaseCapture ());
		m_bDragging = FALSE;

		CPoint pt (point);
		ClientToScreen (&pt);
		// m_dropPoint = pt;

		// get the CWnd pointer of the window that is under the	mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		ASSERT (pDropWnd);

		// if window is CTreeCtrl
		if (pDropWnd == &m_xlc)
		{
			HTREEITEM htiDropTarget=m_xlc.GetDropHilightItem();
			ASSERT(m_hDropItem==htiDropTarget);
			m_xlc.SelectDropTarget(NULL);
			
			// move selected items
			if(htiDropTarget!=NULL && m_xlc.GetSelectedCount() >= 1)
			{
				HTREEITEM htiParent=m_xlc.GetParentItem(htiDropTarget);

				HTREEITEM hDragItem = m_xlc.GetNextItem(TVI_ROOT, TVGN_FIRSTSELECTED);
				HTREEITEM hNextDragItem = m_xlc.GetNextItem(hDragItem, TVGN_NEXTSELECTED);
				while(hDragItem)
				{
					if (::GetKeyState(VK_CONTROL) & 0x8000)
					{
						m_xlc.CopyItem(hDragItem,htiDropTarget);
						htiDropTarget = hDragItem;
					}
					else
					{
						m_xlc.MoveItem(hDragItem,htiParent,htiDropTarget);
						htiDropTarget = hDragItem;
					}

					hDragItem = hNextDragItem;
					hNextDragItem = m_xlc.GetNextItem(hNextDragItem, TVGN_NEXTSELECTED);
				}

			}

			m_hDropItem = NULL;
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CExtTreeDemoDlg::OnItemclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	int nCol=phdn->iItem;
	m_xlc.SortChildren(NULL,nCol);
	*pResult = 0;
}

void CExtTreeDemoDlg::OnTvoxsItemtips() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	DWORD dwStyleAdd = m_bItemTips ? TVOXS_ITEMTIPS : 0;
	DWORD dwStyleRemove = m_bItemTips ? 0 : TVOXS_ITEMTIPS;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}



void CExtTreeDemoDlg::OnTvoxsNoscroll() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	DWORD dwStyleAdd = m_bNoScroll ? TVOXS_NOSCROLL : 0;
	DWORD dwStyleRemove = m_bNoScroll ? 0 : TVOXS_NOSCROLL;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd,SWP_DRAWFRAME);
}

void CExtTreeDemoDlg::OnTvoxsNosortheader() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	DWORD dwStyleAdd = m_bNoSortHeader ? TVOXS_NOSORTHEADER : 0;
	DWORD dwStyleRemove = m_bNoSortHeader ? 0 : TVOXS_NOSORTHEADER;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd,SWP_DRAWFRAME);
}


void CExtTreeDemoDlg::OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UNREFERENCED_PARAMETER(pNMHDR);
	
	static int hit=0;
	HTREEITEM hItem = m_xlc.GetSelectedItem();
	if(hItem)
	{
		m_xlc.EditLabel(hItem);
	}

	*pResult = 0;
}

void CExtTreeDemoDlg::OnItemExpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	pNMTreeView->itemNew.stateMask=TVIS_EXPANDEDONCE;
	pNMTreeView->itemNew.mask=TVIF_STATE|TVIF_CHILDREN;
	m_xlc.GetItem(&pNMTreeView->itemNew);
	// If folder at least once was expanded then it was already populated 
	if((pNMTreeView->itemNew.state & TVIS_EXPANDEDONCE) || 
		pNMTreeView->itemNew.cChildren==0)
		return;

	CStringArray saComboStr;
	CStringArray saDates;
	saDates.Add(_T("01/01/1998"));
	saDates.Add(_T("31/12/1998"));
	for(int i=0; i<10; i++)
	{
		CString s;
		s.Format(_T("Option %d"),i+1);
		saComboStr.Add(s);
	}

	CString sParentItem=m_xlc.GetItemText(pNMTreeView->itemNew.hItem);
	for(int j=500;j >= 0;j--)
	{
		CString sItem;
		sItem.Format(_T("%s - Item %d"),sParentItem,j);
		HTREEITEM h =m_xlc.InsertItem(sItem,pNMTreeView->itemNew.hItem);
		if(!j)
		{
			CFont f;
			f.CreatePointFont(-80,_T("Arial"));
			m_xlc.SetItemFont(h,&f);
		}

		sItem.Format(_T("Option %d"),j);
		m_xlc.SetSubItem(h,1,OX_SUBITEM_TEXT,sItem);
		m_xlc.SetEditMode(h,OXET_COMBO,saComboStr,1);
		m_xlc.SetSubItem(h,2,OX_SUBITEM_TEXT,_T("None"));
		m_xlc.SetEditMode(h,OXET_CALENDAR,saDates,2);
	}

}

void CExtTreeDemoDlg::OnDeleteSelected() 
{
	HTREEITEM hSelected;
	while ((hSelected = m_xlc.GetSelectedItem()) != NULL)
		m_xlc.DeleteItem(hSelected);
}
