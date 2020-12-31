// ExtendedTreeControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExtendedTreeControl.h"
#include "ExtendedTreeControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendedTreeControlDlg dialog

CExtendedTreeControlDlg::CExtendedTreeControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExtendedTreeControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExtendedTreeControlDlg)
	m_bMultiSel=FALSE;
	m_bHasButtons=FALSE;
	m_bHasLines=FALSE;
	m_bHasLinesAtRoot=FALSE;
	m_bShowSelAlways=FALSE;
	m_bHasGrid=FALSE;
	m_bRowSel=FALSE;
	m_bItemTips=FALSE;
	m_bNoSortHeader=FALSE;
	//}}AFX_DATA_INIT
	m_pDragImage=NULL;
	m_bDragging=FALSE;
	m_hDropItem=NULL;

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CExtendedTreeControlDlg::~CExtendedTreeControlDlg()
{
	if (m_pDragImage)
		delete m_pDragImage;
}

void CExtendedTreeControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExtendedTreeControlDlg)
	DDX_Control(pDX, IDC_STATIC_EXTENDED_STYLES, m_sepExtendedStyle);
	DDX_Control(pDX, IDC_STATIC_BASIC_STYLES, m_sepBasicStyles);
	DDX_Control(pDX, IDC_EXTENDED_TREE, m_xlc);
	DDX_Check(pDX, IDC_TVOXS_MULTISEL, m_bMultiSel);
	DDX_Check(pDX, IDC_TVS_HASBUTTONS, m_bHasButtons);
	DDX_Check(pDX, IDC_TVS_HASLINES, m_bHasLines);
	DDX_Check(pDX, IDC_TVS_HASLINESATROOT, m_bHasLinesAtRoot);
	DDX_Check(pDX, IDC_TVS_SHOWSELALWAYS, m_bShowSelAlways);
	DDX_Check(pDX, IDC_TVOXS_GRID, m_bHasGrid);
	DDX_Check(pDX, IDC_TVOXS_ROWSEL, m_bRowSel);
	DDX_Check(pDX, IDC_TVOXS_ITEMTIPS, m_bItemTips);
	DDX_Check(pDX, IDC_TVOXS_NOSORTHEADER, m_bNoSortHeader);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExtendedTreeControlDlg, CDialog)
	//{{AFX_MSG_MAP(CExtendedTreeControlDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TVOXS_MULTISEL, OnTvoxsMultisel)
	ON_BN_CLICKED(IDC_TVS_HASBUTTONS, OnTvsHasbuttons)
	ON_BN_CLICKED(IDC_TVS_HASLINES, OnTvsHaslines)
	ON_BN_CLICKED(IDC_TVS_HASLINESATROOT, OnTvsHaslinesatroot)
	ON_BN_CLICKED(IDC_TVS_SHOWSELALWAYS, OnTvsShowselalways)
	ON_BN_CLICKED(IDC_HIDE, OnHide)
	ON_BN_CLICKED(IDC_UNHIDE_ALL, OnUnhideAll)
	ON_BN_CLICKED(IDC_SET_FONT, OnSetFontToSel)
	ON_BN_CLICKED(IDC_TOGGLE_DISABLE, OnToggleDisable)
	ON_BN_CLICKED(IDC_TVOXS_GRID, OnGrid)
	ON_BN_CLICKED(IDC_TVOXS_ROWSEL, OnRowSel)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_EXTENDED_TREE, OnBegindragExtendedTree)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_TVOXS_ITEMTIPS, OnTvoxsItemtips)
	ON_BN_CLICKED(IDC_TVOXS_NOSORTHEADER, OnTvoxsNosortheader)
	ON_WM_DESTROY()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON1, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendedTreeControlDlg message handlers

void CExtendedTreeControlDlg::InsertItems()
{
		CStringArray arrCity;
	arrCity.Add(_T("Amsterdam"));
	arrCity.Add(_T("Berlin"));
	arrCity.Add(_T("Edingburg"));
	arrCity.Add(_T("Madrid"));
	arrCity.Add(_T("Mexico City"));
	arrCity.Add(_T("Moscow"));
	arrCity.Add(_T("Niece"));
	arrCity.Add(_T("New York"));
	arrCity.Add(_T("Rome"));
	arrCity.Add(_T("Toronto"));
	arrCity.Add(_T("Zurich"));

	CStringArray arrPosition;
	arrPosition.Add(_T("CEO"));
	arrPosition.Add(_T("Computer Programmer"));
	arrPosition.Add(_T("Consultant"));
	arrPosition.Add(_T("Engineer"));
	arrPosition.Add(_T("Head Chef"));
	arrPosition.Add(_T("Professional Athlete"));
	arrPosition.Add(_T("Shipper"));
	arrPosition.Add(_T("Singer"));

	CStringArray arrDate;
	arrDate.Add(_T("01/01/1998"));
	arrDate.Add(_T("31/12/2001"));

	TCHAR szItems[][50]={
		_T("Bob Jackson"),_T("Niece"),_T("Computer Programmer"), _T("(213)-456-7689"),_T("bobj@comp.net"),_T("09.12.1998"),
		_T("Elizabeth Sizeberg"),_T("Berlin"),_T("Shipper"), _T("(343)-534-2653"),_T("elsize@berco.com"),_T("11.03.1998"),
		_T("Janna Stevens"),_T("Zurich"),_T("Consultant"), _T("(312)-232-4467 ext. 2098"),_T("stevensj@hotmail.com"),_T("10.22.1998"),
		_T("John McDonald"),_T("Toronto"),_T("CEO"), _T("(416)-568-3379"),_T("john.mcdonald@echo.com"),_T("07.30.1998"),
		_T("Margaret Atwal"),_T("Madrid"),_T("Singer"), _T("(568)-803-3149"),_T("margo@jinglebells.com"),_T("09.02.1998"),
		_T("Markus Brody"),_T("Mexico City"),_T("Engineer"), _T("(476)-671-0951"),_T("brody@techdome.net"),_T("03.21.1998"),
		_T("Martha Lenton"),_T("Rome"),_T("Professional Athlete"), _T("(805)-609-9087"),_T("martha@sportnet.com"),_T("06.29.1998"),
		_T("Mary Bolten"),_T("New York"),_T("Head Chef"), _T("(502)-403-0261"),_T("mlenton@cook.net"),_T("05.09.1998")
	};

	for(int nIndex=0; nIndex<8; nIndex++)
	{
		// Name
		HTREEITEM hItem=m_xlc.InsertItem(szItems[nIndex*6]);
		ASSERT(hItem!=NULL);
		m_xlc.SetItemImage(hItem,0,0,0);
		m_xlc.SetItemColor(hItem,RGB(0,0,255));
		// City
		m_xlc.SetSubItem(hItem,1,OX_SUBITEM_TEXT,szItems[nIndex*6+1]);
		m_xlc.SetEditMode(hItem,OXET_COMBO,arrCity,1);
		m_xlc.SetItemColor(hItem,RGB(0,128,0),1);
		// Position
		m_xlc.SetSubItem(hItem,2,OX_SUBITEM_TEXT,szItems[nIndex*6+2]);
		m_xlc.SetEditMode(hItem,OXET_COMBO,arrPosition,2);
		m_xlc.SetItemColor(hItem,RGB(128,0,0),2);

		// Phone
		HTREEITEM hSubItem=m_xlc.InsertItem(_T("Telephone:"),hItem);
		ASSERT(hSubItem!=NULL);
		m_xlc.SetItemImage(hSubItem,1,1,0);
		m_xlc.SetSubItem(hSubItem,1,OX_SUBITEM_TEXT,szItems[nIndex*6+3]);
		m_xlc.SetItemColor(hSubItem,RGB(0,128,0),1);

		// E-mail
		hSubItem=m_xlc.InsertItem(_T("E-mail:"),hItem);
		ASSERT(hSubItem!=NULL);
		m_xlc.SetItemImage(hSubItem,2,2,0);
		m_xlc.SetSubItem(hSubItem,1,OX_SUBITEM_TEXT,szItems[nIndex*6+4]);
		m_xlc.SetItemColor(hSubItem,RGB(0,128,0),1);

		// Last contact
		hSubItem=m_xlc.InsertItem(_T("Last contact:"),hItem);
		ASSERT(hSubItem!=NULL);
		m_xlc.SetItemImage(hSubItem,3,3,0);
		m_xlc.SetSubItem(hSubItem,1,OX_SUBITEM_TEXT,szItems[nIndex*6+5]);
		m_xlc.SetEditMode(hSubItem,OXET_CALENDAR,arrDate,1);
		m_xlc.SetItemColor(hSubItem,RGB(0,128,0),1);
	}
}

BOOL CExtendedTreeControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	VERIFY(m_il.Create(IDB_IL_TREE,16,1,RGB(255,0,255)));
	m_xlc.SetImageList(&m_il,TVSIL_NORMAL);

	// Setup columns
	m_xlc.DeleteColumn(0);
	m_xlc.InsertColumn(0,_T("Name"),LVCFMT_LEFT,150);
	m_xlc.InsertColumn(1,_T("City"),LVCFMT_LEFT,100);
	m_xlc.InsertColumn(2,_T("Title"),LVCFMT_LEFT,120);
	//////////////////////////
	

	InsertItems();

	m_xlc.ModifyExStyle(0,TVOXS_COLUMNHDR);
	m_xlc.ModifyExStyle(0,TVOXS_MULTISEL);
	m_xlc.ModifyStyle(0,TVS_EDITLABELS);
	m_xlc.ModifyStyle(0,TVS_HASBUTTONS);
	m_xlc.ModifyStyle(0,TVS_HASLINES);
	m_xlc.ModifyStyle(0,TVS_LINESATROOT);
	m_xlc.ModifyStyle(0,TVS_SHOWSELALWAYS);
	m_xlc.ModifyExStyle(TVOXS_VGRID,0);
	m_xlc.ModifyExStyle(TVOXS_HGRID,0);
	m_xlc.ModifyExStyle(0,TVOXS_FLGRID);
	m_xlc.ModifyExStyle(0,TVOXS_ROWSEL);
	m_xlc.ModifyExStyle(0,TVOXS_PICKANYWHERE);
	m_xlc.ModifyExStyle(0,TVOXS_ITEMTIPS);

	m_bHasLines=m_xlc.HasLines();
	m_bHasButtons=m_xlc.HasButtons();
	m_bHasLinesAtRoot=m_xlc.HasLinesAtRoot();
	m_bShowSelAlways=m_xlc.GetShowSelAlways();
	DWORD dwStyleEx=m_xlc.GetExStyle();
	m_bMultiSel=(dwStyleEx & TVOXS_MULTISEL)!=0;
	m_bHasGrid=((dwStyleEx & TVOXS_HGRID)!=0 && (dwStyleEx & TVOXS_VGRID)!=0);
	m_bRowSel=(dwStyleEx & TVOXS_ROWSEL)!=0;
	m_bItemTips=(dwStyleEx & TVOXS_ITEMTIPS)!=0;
	m_bNoSortHeader=(dwStyleEx & TVOXS_NOSORTHEADER)!=0;
/*
	// separators
	COLORREF clr=::GetSysColor(COLOR_WINDOW);
	m_sepBasicStyles.SetTextColor(clr);
	m_sepExtendedStyle.SetTextColor(clr);
*/
	// layout
	//
	m_LayoutManager.Attach(this);
	m_LayoutManager.TieChild(&m_xlc,
		OX_LMS_LEFT|OX_LMS_RIGHT|OX_LMS_TOP|OX_LMS_BOTTOM,OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_SET_FONT,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_HIDE,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_UNHIDE_ALL,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TOGGLE_DISABLE,OX_LMS_RIGHT,OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_STATIC_BASIC_STYLES,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_STATIC_EXTENDED_STYLES,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TVS_HASLINES,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TVS_HASBUTTONS,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TVS_HASLINESATROOT,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TVS_SHOWSELALWAYS,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TVOXS_MULTISEL,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TVOXS_NOSORTHEADER,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TVOXS_GRID,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TVOXS_ROWSEL,OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_TVOXS_ITEMTIPS,OX_LMS_BOTTOM,OX_LMT_SAME);	

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExtendedTreeControlDlg::OnPaint() 
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
HCURSOR CExtendedTreeControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExtendedTreeControlDlg::OnTvoxsMultisel() 
{
	UpdateData();
	if(m_bMultiSel)
	{
		m_xlc.ModifyExStyle(0,TVOXS_MULTISEL);
	}
	else
	{
		m_xlc.ModifyExStyle(TVOXS_MULTISEL,0);
	}
}

void CExtendedTreeControlDlg::OnTvsHasbuttons() 
{
	UpdateData();
	if(m_bHasButtons)
	{
		m_xlc.ModifyStyle(0,TVS_HASBUTTONS);
	}
	else
	{
		m_xlc.ModifyStyle(TVS_HASBUTTONS,0);
	}
	
}

void CExtendedTreeControlDlg::OnTvsHaslines() 
{
	UpdateData();
	if(m_bHasLines)
	{
		m_xlc.ModifyStyle(0,TVS_HASLINES);
	}
	else
	{
		m_xlc.ModifyStyle(TVS_HASLINES,0);
	}
	
}

void CExtendedTreeControlDlg::OnTvsHaslinesatroot() 
{
	UpdateData();
	if(m_bHasLinesAtRoot)
	{
		m_xlc.ModifyStyle(0,TVS_LINESATROOT);
	}
	else
	{
		m_xlc.ModifyStyle(TVS_LINESATROOT,0);
	}
	
}

void CExtendedTreeControlDlg::OnTvsShowselalways() 
{
	UpdateData();
	if(m_bShowSelAlways)
	{
		m_xlc.ModifyStyle(0,TVS_SHOWSELALWAYS);
	}
	else
	{
		m_xlc.ModifyStyle(TVS_SHOWSELALWAYS,0);
	}
	
}

void CExtendedTreeControlDlg::OnHide() 
{
	HTREEITEM hItem=m_xlc.GetNextItem(TVI_ROOT,TVGN_FIRSTSELECTED);
	while(hItem)
	{
		HTREEITEM hItem1=hItem;
		hItem=m_xlc.GetNextItem(hItem,TVGN_NEXTSELECTED);
		m_xlc.HideItem(hItem1);
	}
}

void CExtendedTreeControlDlg::OnUnhideAll() 
{
	HTREEITEM hItem=m_xlc.GetFirstHiddenItem();
	while(hItem)
	{
		HTREEITEM hItem1=hItem;
		hItem=m_xlc.GetNextHiddenItem(hItem);
		m_xlc.HideItem(hItem1,FALSE);
	}
}

void CExtendedTreeControlDlg::OnSetFontToSel() 
{
	int nSelectedCount=m_xlc.GetSelectedCount();
	if(nSelectedCount==0)
	{
		return;
	}

	// Use font common dialog
	CFontDialog* pFontDlg;
	if(nSelectedCount==1)
	{
		HTREEITEM hSelectedItem=m_xlc.GetNextItem(TVI_ROOT,TVGN_FIRSTSELECTED);
		CFont* pFont=m_xlc.GetItemFont(hSelectedItem);
		if(pFont==NULL)
		{
			pFont=m_xlc.GetFont();
		}
		ASSERT(pFont!=NULL);
		LOGFONT lf;
		pFont->GetLogFont(&lf);
		pFontDlg=new CFontDialog(&lf);
		pFontDlg->m_cf.rgbColors=m_xlc.GetItemColor(hSelectedItem);
	}
	else
	{
		pFontDlg=new CFontDialog();
	}
	ASSERT(pFontDlg!=NULL);

	if(pFontDlg->DoModal()==IDOK)
	{
		LOGFONT lf;
		pFontDlg->GetCurrentFont(&lf);
		CFont font;
		VERIFY(font.CreateFontIndirect(&lf));
		HTREEITEM hItem=m_xlc.GetNextItem(TVI_ROOT,TVGN_FIRSTSELECTED);
		while(hItem)
		{
			m_xlc.SetItemFont(hItem,&font,0);
			m_xlc.SetItemFont(hItem,&font,1);
			m_xlc.SetItemFont(hItem,&font,2);
			m_xlc.SetItemColor(hItem,pFontDlg->m_cf.rgbColors);
			m_xlc.SetItemColor(hItem,pFontDlg->m_cf.rgbColors,1);
			m_xlc.SetItemColor(hItem,pFontDlg->m_cf.rgbColors,2);
			hItem=m_xlc.GetNextItem(hItem,TVGN_NEXTSELECTED);
		}

		UINT nHeight=m_xlc.GetItemHeight();
		lf.lfHeight=(lf.lfHeight>0 ? lf.lfHeight : -lf.lfHeight)+6;
		if(lf.lfHeight>(int)nHeight)
		{
			m_xlc.SetItemHeight(lf.lfHeight);
		}
	}

	delete pFontDlg;
}

void CExtendedTreeControlDlg::OnToggleDisable() 
{
	HTREEITEM hItem=m_xlc.GetNextItem(TVI_ROOT,TVGN_FIRSTSELECTED);
	while(hItem)
	{
		m_xlc.DisableItem(hItem,!m_xlc.IsItemDisabled(hItem));
		hItem=m_xlc.GetNextItem(hItem,TVGN_NEXTSELECTED);
	}
}

void CExtendedTreeControlDlg::OnGrid() 
{
	UpdateData();
	DWORD dwStyleAdd=m_bHasGrid ? TVOXS_VGRID|TVOXS_HGRID|TVOXS_FLGRID : 0;
	DWORD dwStyleRemove=m_bHasGrid ? 0 : TVOXS_VGRID|TVOXS_HGRID|TVOXS_FLGRID;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}

void CExtendedTreeControlDlg::OnRowSel() 
{
	UpdateData();
	DWORD dwStyleAdd=m_bRowSel ? TVOXS_ROWSEL : 0;
	DWORD dwStyleRemove=m_bRowSel ? 0 : TVOXS_ROWSEL;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}


void CExtendedTreeControlDlg::OnBegindragExtendedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(m_pDragImage)
	{
		delete m_pDragImage;
	}

	HTREEITEM hDragItem=m_xlc.GetSelectedItem();
	ASSERT (hDragItem);
	m_pDragImage=m_xlc.CreateDragImage (hDragItem);
	ASSERT (m_pDragImage);

	// changes the cursor to the drag image (DragMove() is still required in 
	// OnMouseMove())
	VERIFY (m_pDragImage->BeginDrag (0, CPoint (8, 8)));
	VERIFY (m_pDragImage->DragEnter (GetDesktopWindow (), pNMListView->ptAction));

	IMAGEINFO pImageInfo;
	VERIFY(m_pDragImage->GetImageInfo(0,&pImageInfo));

	// set dragging flag
	m_bDragging=TRUE;
	m_hDropItem=NULL;

	// capture all mouse messages
	SetCapture();

	*pResult=0;
}

void CExtendedTreeControlDlg::OnMouseMove(UINT nFlags, CPoint point) 
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
		CWnd* pDropWnd=WindowFromPoint (pt);
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
				m_hDropItem=NULL;
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
				m_hDropItem=m_xlc.GetItemFromIndex(nIndex);
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

void CExtendedTreeControlDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_bDragging)
	{
		// end dragging
		VERIFY (m_pDragImage->DragLeave (GetDesktopWindow ())); 
		m_pDragImage->EndDrag ();
		// stop intercepting all mouse messages
		VERIFY (::ReleaseCapture ());
		m_bDragging=FALSE;

		CPoint pt (point);
		ClientToScreen (&pt);
		// m_dropPoint=pt;

		// get the CWnd pointer of the window that is under the	mouse cursor
		CWnd* pDropWnd=WindowFromPoint (pt);
		ASSERT (pDropWnd);

		// if window is CTreeCtrl
		if (pDropWnd == &m_xlc)
		{
			HTREEITEM htiDropTarget=m_xlc.GetDropHilightItem();
			ASSERT(m_hDropItem==htiDropTarget);
			m_xlc.SelectDropTarget(NULL);
			// move only if we selected only one item 
			if(htiDropTarget!=NULL)
			{
				if(m_xlc.GetSelectedCount()<2)
				{
					// the last selected item is the dragged one
					HTREEITEM hDragItem=m_xlc.GetSelectedItem();
					ASSERT (hDragItem);

					HTREEITEM htiParent=m_xlc.GetParentItem(htiDropTarget);
					if (::GetKeyState(VK_CONTROL) & 0x8000)
						m_xlc.CopyItem(hDragItem,htiDropTarget);
					else
						m_xlc.MoveItem(hDragItem,htiParent,htiDropTarget);
				}
				else
				{
					if (::GetKeyState(VK_CONTROL) & 0x8000)
						AfxMessageBox("Cannot copy more than 1 item at once!");
					else
						AfxMessageBox("Cannot move more than 1 item at once!");
				}
			}

			m_hDropItem=NULL;
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}


void CExtendedTreeControlDlg::OnTvoxsItemtips() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	DWORD dwStyleAdd=m_bItemTips ? TVOXS_ITEMTIPS : 0;
	DWORD dwStyleRemove=m_bItemTips ? 0 : TVOXS_ITEMTIPS;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}



void CExtendedTreeControlDlg::OnTvoxsNosortheader() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	DWORD dwStyleAdd=m_bNoSortHeader ? TVOXS_NOSORTHEADER : 0;
	DWORD dwStyleRemove=m_bNoSortHeader ? 0 : TVOXS_NOSORTHEADER;
	m_xlc.ModifyExStyle(dwStyleRemove,dwStyleAdd);
}


void CExtendedTreeControlDlg::OnDestroy() 
{
	if (m_LayoutManager.IsAttached())
		m_LayoutManager.Detach();

	CDialog::OnDestroy();
}

void CExtendedTreeControlDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	lpMMI->ptMinTrackSize.x = 500;
	lpMMI->ptMinTrackSize.y = 300;
	
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CExtendedTreeControlDlg::OnDelete()
{
	m_xlc.DeleteAllItems();
	InsertItems();
//	m_xlc.DeleteItem(m_xlc.GetSelectedItem());
}