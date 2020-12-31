// MyListCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyListCtrl.h"
#include "MyListCtrlDlg.h"
#include "ListColorDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
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
		// No message handlers
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrlDlg dialog

CMyListCtrlDlg::CMyListCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyListCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyListCtrlDlg)
	m_fullrow = TRUE;
	m_image1 = FALSE;
	m_image2 = FALSE;
	m_image3 = FALSE;
	m_check1 = FALSE;
	m_check2 = TRUE;
	m_check3 = FALSE;
	m_progress = TRUE;
	m_winColors = FALSE;
	m_normalStyle = FALSE;
	m_noImgSel = TRUE;
	m_noCheckSel = TRUE;
	m_noSel1 = FALSE;
	m_noSel2 = FALSE;
	m_noSel3 = FALSE;
	m_progBorder = 0;
	m_grid = FALSE;
	m_columnNavigation = TRUE;
	m_editonenter = TRUE;
	m_editonf2 = TRUE;
	m_editondblclick = TRUE;
	m_editonwriting = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DragImage = NULL;

	/*m_progress = FALSE;
	m_winColors = TRUE;
	m_normalStyle = TRUE;
	m_check2 = FALSE;*/
}

void CMyListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyListCtrlDlg)
	DDX_Control(pDX, IDC_COMBO_KEYFIND, m_keyFind);
	DDX_Control(pDX, IDC_COMBO_IMAGELIST, m_selImgList);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Check(pDX, IDC_CHECK_FULLROW, m_fullrow);
	DDX_Check(pDX, IDC_CHECK_IMAGE1, m_image1);
	DDX_Check(pDX, IDC_CHECK_IMAGE2, m_image2);
	DDX_Check(pDX, IDC_CHECK_IMAGE3, m_image3);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	DDX_Check(pDX, IDC_CHECK3, m_check3);
	DDX_Check(pDX, IDC_CHECK_PROGRESS, m_progress);
	DDX_Check(pDX, IDC_CHECK_WINCOLORS, m_winColors);
	DDX_Check(pDX, IDC_CHECK_NOSTYLECHANGE, m_normalStyle);
	DDX_Check(pDX, IDC_CHECK_NOIMAGESEL, m_noImgSel);
	DDX_Check(pDX, IDC_CHECK_NOCHECKSELECTIOn, m_noCheckSel);
	DDX_Check(pDX, IDC_CHECK_NOSEL1, m_noSel1);
	DDX_Check(pDX, IDC_CHECK_NOSEL2, m_noSel2);
	DDX_Check(pDX, IDC_CHECK_NOSEL3, m_noSel3);
	DDX_CBIndex(pDX, IDC_COMBO_PROGBORDER, m_progBorder);
	DDX_Check(pDX, IDC_CHECK_GRID, m_grid);
	DDX_Check(pDX, IDC_CHECK_COLUMNNAVIGATION, m_columnNavigation);
	DDX_Check(pDX, IDC_CHECK_EDITONENTER, m_editonenter);
	DDX_Check(pDX, IDC_CHECK_EDITONF2, m_editonf2);
	DDX_Check(pDX, IDC_CHECK_EDITONDBLCLICK, m_editondblclick);
	DDX_Check(pDX, IDC_CHECK_EDITONWRITING, m_editonwriting);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyListCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CMyListCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_FULLROW, OnCheckFullrow)
	ON_BN_CLICKED(IDC_BUTTON_ADDTEN, OnButtonAddten)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_CBN_SELCHANGE(IDC_COMBO_IMAGELIST, OnSelchangeComboImagelist)
	ON_CBN_SELCHANGE(IDC_COMBO_KEYFIND, OnSelchangeComboKeyfind)
	ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST, OnOdfinditemList)
	ON_BN_CLICKED(IDC_BUTTON_COLORS, OnButtonColors)
	ON_CBN_SELCHANGE(IDC_COMBO_PROGBORDER, OnSelchangeComboProgborder)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_GRID, OnCheckGrid)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
	ON_BN_CLICKED(IDC_CHECK_COLUMNNAVIGATION, OnCheckColumnnavigation)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST, OnBeginlabeleditList)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST, OnBegindragList)
	ON_NOTIFY(NM_RCLICK, IDC_LIST, OnRclickList)
	ON_WM_LBUTTONUP()
	ON_NOTIFY(NM_RDBLCLK, IDC_LIST, OnRdblclkList)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_CHECK_EDITONENTER, OnCheckEditonenter)
	ON_BN_CLICKED(IDC_CHECK_EDITONF2, OnCheckEditonf2)
	ON_BN_CLICKED(IDC_CHECK_EDITONDBLCLICK, OnCheckEditondblclick)
	ON_BN_CLICKED(IDC_BUTTON_FULLREDRAW, OnButtonFullredraw)
	ON_COMMAND(ID_HEADERMENU_COLUMN1, OnHeadermenuColumn1)
	ON_COMMAND(ID_HEADERMENU_COLUMN2, OnHeadermenuColumn2)
	ON_COMMAND(ID_HEADERMENU_COLUMN3, OnHeadermenuColumn3)
	ON_BN_CLICKED(IDC_CHECK_EDITONWRITING, OnCheckEditonwriting)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECK_FULLROW, IDC_CHECK_NOSEL3, OnSomeCheckbox)

	ON_MESSAGE(WM_QUICKLIST_GETLISTITEMDATA, OnGetListItem) 
	ON_MESSAGE(WM_QUICKLIST_NAVIGATIONTEST, OnNavigationTest) 
	ON_MESSAGE(WM_QUICKLIST_CLICK, OnListClick) 
	ON_MESSAGE(WM_QUICKLIST_HEADERRIGHTCLICK, OnHeaderRightClick)

	#ifdef USEXPTHEMES
		//WM_THEMECHANGED = 0x031A (WM_THEMECHANGED may not be avalible)
		ON_MESSAGE(0x031A, OnThemeChanged)	
	#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrlDlg message handlers


#ifdef USEXPTHEMES
LRESULT CMyListCtrlDlg::OnThemeChanged(WPARAM, LPARAM)
{
	// This feature requires Windows XP or greater.
	// The symbol _WIN32_WINNT must be >= 0x0501.
	// TODO: Add your message handler code here and/or call default

	m_themeManager.ThemeChanged(m_hWnd);

	return 1;
}
#endif

BOOL CMyListCtrlDlg::OnInitDialog()
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
	
	ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_SUBITEMIMAGES , LVS_EX_SUBITEMIMAGES );
	//ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_TRACKSELECT, LVS_EX_TRACKSELECT );
	ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES );
	ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_HEADERDRAGDROP, LVS_EX_HEADERDRAGDROP);


#ifdef USEXPTHEMES
	m_themeManager.Init(m_hWnd);
	m_list.SetThemeManager(&m_themeManager);
#endif

	m_imgList.Create(IDB_BITMAP1, 16, ILC_COLOR4, RGB(255, 255, 255));
	m_imgLargeList.Create(IDB_BITMAP2, 32, ILC_COLOR4, RGB(255, 255, 255));

	//m_list.SetBackgroundColor(RGB(255,255,255));

#ifndef QUICKLIST_NOIMAGE
//	m_list.SetImageList(&m_imgLargeList, LVSIL_SMALL);
#endif
	m_selImgList.SetCurSel(2);

	m_list.InsertColumn(0, _T("Person"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(1, _T("Slogan"), LVCFMT_LEFT, 225);
	m_list.InsertColumn(2, _T("Result"), LVCFMT_CENTER, 75);
	
	m_keyFind.SetCurSel(1);
	OnSelchangeComboKeyfind();

#ifndef QUICKLIST_NOEMPTYMESSAGE	
	m_list.SetEmptyMessage(IDS_EMPTYMESS);
#endif

	//Note: There are problems with tool tips. See article
	m_list.EnableToolTips(TRUE);
	

	OnButtonAddten();
	OnButtonAddten();
	OnButtonAddten();

	SetTimer(0, 10, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyListCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyListCtrlDlg::OnPaint() 
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
HCURSOR CMyListCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//Test if it's ok to change navigation column
LRESULT CMyListCtrlDlg::OnNavigationTest(WPARAM wParam, LPARAM lParam)
{
#ifndef QUICKLIST_NONAVIGATION
	//Make sure message comes from list box
	ASSERT( (HWND)wParam == m_list.GetSafeHwnd() );

	CQuickList::CNavigationTest* test = (CQuickList::CNavigationTest*) lParam;

	//Don't allow navigation to progress column
	if(test->m_newColumn == 2)
		test->m_allowChange = false;

#endif

	return 0;
}

//User clicked on list. Toggle checkbox/image if hit
LRESULT CMyListCtrlDlg::OnListClick(WPARAM wParam, LPARAM lParam)
{
	//Make sure message comes from list box
	ASSERT( (HWND)wParam == m_list.GetSafeHwnd() );

	CQuickList::CListHitInfo *hit= (CQuickList::CListHitInfo*) lParam;

	TRACE(_T("User hit item %d, subitem %d "), hit->m_item, hit->m_subitem);

	if(hit->m_onButton)
	{
		TRACE(_T("On check box. "));
		m_data[hit->m_item].m_check[hit->m_subitem] = !m_data[hit->m_item].m_check[hit->m_subitem];

		m_list.RedrawCheckBoxs(hit->m_item, hit->m_item, hit->m_subitem);
	}
	else
	if(hit->m_onImage)
	{
		TRACE(_T("On image. "));
		m_data[hit->m_item].m_image[hit->m_subitem] = (m_data[hit->m_item].m_image[hit->m_subitem]+1)%IMAGECOUNT;

		m_list.RedrawImages(hit->m_item, hit->m_item, hit->m_subitem);
	}


	TRACE(_T("\n"));

	return 0;
}

//Get item data
LRESULT CMyListCtrlDlg::OnGetListItem(WPARAM wParam, LPARAM lParam)
{
	//wParam is a handler to the list
	//Make sure message comes from list box
	ASSERT( (HWND)wParam == m_list.GetSafeHwnd() );

	//lParam is a pointer to the data that is needed for the element
	CQuickList::CListItemData* data = (CQuickList::CListItemData*) lParam;

	//Get which item and subitem that is asked for.
	int item = data->GetItem();
	int subItem = data->GetSubItem();


	CSampleData& sampledata = m_data[item];
	

	UpdateData();
	BOOL noSel[3] = { m_noSel1, m_noSel2, m_noSel3 };

	data->m_noSelection = (noSel[subItem] != 0);

#ifndef QUICKLIST_NOEDIT
	if(subItem < 2)
	{
		//Only column one is editable if not full row select
		if(m_fullrow || subItem == 0)
			data->m_allowEdit = true;
	}
#endif

#ifndef QUICKLIST_NOCOLORS
	if(m_winColors==0)
	{
		if(data->GetItem()%2 == 0)
		{
			data->m_colors.m_textColor =			RGB( 10, 5, 20);
			data->m_colors.m_backColor =			RGB( 180, 180, 255);
			#ifndef QUICKLIST_NONAVIGATION
			data->m_colors.m_navigatedTextColor =	RGB( 200, 220, 230);
			data->m_colors.m_navigatedBackColor =	RGB( 140, 60, 70);
			#endif

			data->m_colors.m_hotTextColor =			RGB( 170, 10, 150);
			
			data->m_colors.m_selectedBackColorNoFocus = RGB( 20, 20, 120);
			data->m_colors.m_selectedBackColor =	RGB( 30, 0, 96);
			data->m_colors.m_selectedTextColor =	RGB( 240, 200, 128);
		}
		else
		{
			data->m_colors.m_textColor =			RGB( 40, 10, 40);
			data->m_colors.m_backColor =			RGB( 220, 220, 255);
			#ifndef QUICKLIST_NONAVIGATION
			data->m_colors.m_navigatedTextColor =	RGB( 200, 200, 230);
			data->m_colors.m_navigatedBackColor =	RGB( 160, 70, 70);
			#endif

			data->m_colors.m_hotTextColor =			RGB( 170, 10, 150);
			
			data->m_colors.m_selectedBackColorNoFocus = RGB( 20, 60, 120);
			data->m_colors.m_selectedBackColor =	RGB( 30, 50, 96);
			data->m_colors.m_selectedTextColor =	RGB( 240, 250, 128);
		}

	}
#endif

#ifndef QUICKLIST_NOTEXTSTYLE 
	if(m_normalStyle==0)
	{
		data->m_textStyle.m_bold = sampledata.m_bold[subItem];
		data->m_textStyle.m_italic = sampledata.m_italic[subItem];
	}
#endif

#ifndef QUICKLIST_NOIMAGE	
	BOOL drawImage[3] = { m_image1, m_image2, m_image3};
	
	if(drawImage[subItem] )
	{
		//data->m_image.m_imageList = &m_imgList;
		data->m_image.m_imageID	  = sampledata.m_image[subItem];

		if(subItem==1)
			data->m_image.m_imageList = &m_imgList;
		if(subItem==2)
			data->m_image.m_imageList = &m_imgLargeList;
		
		data->m_image.m_noSelection = (m_noImgSel!=0);
	}
#endif

#ifndef QUICKLIST_NOBUTTON
	BOOL drawCheck[3] = { m_check1, m_check2, m_check3 };

	if(drawCheck[subItem])
	{
		int style[] = {DFCS_BUTTONRADIO, DFCS_BUTTONCHECK, DFCS_BUTTONPUSH};

		data->m_button.m_draw = true;
		data->m_button.m_noSelection = (m_noCheckSel != 0);
		data->m_button.m_style = style[subItem];
		
		if(	sampledata.m_check[subItem] )
			data->m_button.m_style |= DFCS_CHECKED;
	}
#endif

	if(data->GetSubItem() == 0)
	{
		data->m_text.Format(_T("%d %s"), item+1, sampledata.m_name);
	}
	else if(data->GetSubItem() == 1)
	{
		data->m_text = sampledata.m_slogan;
	}
	else
	{
		data->m_text.Format(_T("%d%%"), sampledata.m_result);
	}


#ifndef QUICKLIST_NOTOOLTIP
	//Tool tip text
	data->m_tooltip = CString(_T("Tooltip: ")) + data->m_text;
#endif


#ifndef QUICKLIST_NOPROGRESSBAR
	if(subItem == 2 && m_progress)
	{
		UINT edgestyle[] = {EDGE_BUMP, EDGE_ETCHED, EDGE_RAISED, EDGE_SUNKEN};

		data->m_progressBar.m_maxvalue = 100;;
		data->m_progressBar.m_value    = sampledata.m_result;
		if(m_progBorder != 0)
			data->m_progressBar.m_edge	   = edgestyle[m_progBorder-1];
		else
			data->m_progressBar.m_edge	   = 0;

		if(m_winColors==0)
			data->m_progressBar.m_fillColor = RGB(   40, 
													 60-30*(data->GetItem()%3), 
													 30 );
	}
#endif



	return 0;
}




void CMyListCtrlDlg::OnCheckFullrow() 
{
	UpdateData();

	if(m_fullrow)
		ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	else
		ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_FULLROWSELECT, 0);
	
	UpdateList();
}


void CMyListCtrlDlg::OnCheckGrid() 
{
	UpdateData();

	if(m_grid)
		ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);
	else
		ListView_SetExtendedListViewStyleEx(m_list.m_hWnd, LVS_EX_GRIDLINES, 0);
	
	UpdateList();	
}

void CMyListCtrlDlg::OnButtonAddten() 
{
	for(int i=0; i<10; i++)
		m_data.push_back( CSampleData() );

	UpdateList();
}

void CMyListCtrlDlg::OnButtonClear() 
{
	m_data.clear();

	UpdateList();
}

void CMyListCtrlDlg::UpdateList()
{
	m_list.LockWindowUpdate();
	m_list.SetItemCount( (int) m_data.size() );
	m_list.UnlockWindowUpdate();
	m_list.RedrawItems(
			m_list.GetTopIndex(),
			m_list.GetTopIndex()+m_list.GetCountPerPage());
}


void CMyListCtrlDlg::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int item=-1, subitem=-1;
	bool oncheck=false;
	bool onimage=false;

	if(m_list.HitTest(pNMListView->ptAction, item, subitem, &oncheck, &onimage))
	{
		TRACE(_T("User right hit item %d, subitem %d \n"), item, subitem);

		if(!oncheck && !onimage)
		{
			//Hit on text. Toggle bold/italic
			int temp =  (m_data[item].m_bold[subitem] ? 1: 0) + 
						(m_data[item].m_italic[subitem] ? 2: 0);

			temp =(temp+1)%4;

			bool a=((temp&0x01) != 0);
			m_data[item].m_bold[subitem] =  ( (temp&0x01) != 0);
			a=((temp&0x02) != 0);
			m_data[item].m_italic[subitem] = ( (temp&0x02) != 0);
			
			m_list.RedrawSubitems(item, item, subitem);
		}
	}
	
	*pResult = 0;
}


void CMyListCtrlDlg::OnRdblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int item=-1, subitem=-1;

	if(m_list.HitTest(pNMListView->ptAction, item, subitem))
	{
		m_list.SetHotItem(item);
	}
	
	*pResult = 0;
}



void CMyListCtrlDlg::OnSomeCheckbox(UINT)
{
	UpdateList();
}

void CMyListCtrlDlg::OnSelchangeComboImagelist() 
{
	if(m_selImgList.GetCurSel() == 0)
	{
		m_list.SetImageList(&m_imgLargeList, LVSIL_SMALL);
	}
	else if (m_selImgList.GetCurSel() == 1)
	{
		m_list.SetImageList(&m_imgList, LVSIL_SMALL);
	}
	else
		m_list.SetImageList(NULL, LVSIL_SMALL);
}


void CMyListCtrlDlg::OnSelchangeComboKeyfind() 
{
	m_list.SetKeyfindColumn( m_keyFind.GetCurSel()-2 );	
}

void CMyListCtrlDlg::OnOdfinditemList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLVFINDITEM* pFindInfo = (NMLVFINDITEM*)pNMHDR;
	// TODO: Add your control notification handler code here
	TRACE(_T("LVN_ODFINDITEM send to parent.\n"));
	
	*pResult = 0;
}

void CMyListCtrlDlg::OnButtonColors() 
{
	CListColorDialog dlg;
	dlg.DoModal();
}

void CMyListCtrlDlg::OnSelchangeComboProgborder() 
{
	UpdateList();	
}

void CMyListCtrlDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_data.size() > 0)
	{
		m_data[0].m_result = (m_data[0].m_result+1)%100;
		m_list.RedrawText(0, 0, 2);
	}
	
	CDialog::OnTimer(nIDEvent);
}


//Editing stopped
void CMyListCtrlDlg::OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	// TODO: Add your control notification handler code here
	if(pDispInfo->item.pszText != NULL)
	{
		if(pDispInfo->item.iSubItem == 1)
			m_data[pDispInfo->item.iItem].m_slogan = pDispInfo->item.pszText;
		else if(pDispInfo->item.iSubItem == 0)
			m_data[pDispInfo->item.iItem].m_name = pDispInfo->item.pszText;

		//Select next item?
		if(m_list.GetLastEndEditKey() == VK_RETURN)
		{
			//If column 0, select in next column
			if(pDispInfo->item.iSubItem == 0)
			{
				m_list.EditSubItem(pDispInfo->item.iItem, 1);
			}
			else
			{
				//Select next item if possible
				if(pDispInfo->item.iItem+1 < m_list.GetItemCount())
					m_list.EditSubItem(pDispInfo->item.iItem+1, 0);
			}

		}
	}
	
	*pResult = 0;
}


void CMyListCtrlDlg::OnOK() 
{
	// TODO: Add extra validation her

}

void CMyListCtrlDlg::OnCheckColumnnavigation() 
{
	UpdateData();
	m_list.EnableColumnNavigation(m_columnNavigation!=0);
	UpdateList();
}

void CMyListCtrlDlg::OnBeginlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	
	// Here can you change the text that should be edited.
	// In this case we don't want to edit the number in the first column
	if(pDispInfo->item.iSubItem == 0)
	{
		
		lstrcpyn(	pDispInfo->item.pszText, 
					m_data[pDispInfo->item.iItem].m_name, 
					pDispInfo->item.cchTextMax);

		
	}
	

	//Set to TRUE if you don't want to allo the user to change the label
	*pResult = 0;
}

void CMyListCtrlDlg::OnBegindragList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Currently this isn't working. Need to fix CQuickList::CreateDragImageEx().
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
/*
	POINT pt;
	pt.x = 8;
	pt.y = 8;
	// create a drag image

	// Added 7/29/96
	if(m_DragImage)
		delete m_DragImage;
	
	m_DragImage = m_list.CreateDragImage (pNMListView->iItem, &pt);
	ASSERT (m_DragImage);
	// changes the cursor to the drag image (DragMove() is still required in 
	// OnMouseMove())
	VERIFY (m_DragImage->BeginDrag (0, CPoint (0, 0)));
	VERIFY (m_DragImage->DragEnter (GetDesktopWindow (), pNMListView->ptAction));
	// set dragging flag
//	m_bDragging = TRUE;
//	m_nDropIndex = -1;
//	m_pDropWnd = &m_list;
	// capture all mouse messages
	SetCapture ();

	
	if(pNMListView->iItem != -1)
	{
		if(m_DragImage != NULL)
			delete m_DragImage;

		m_DragImage = m_list.CreateDragImageEx(0, 0); //pNMListView->iItem, &pNMListView->ptAction); //m_list.CreateDragImageEx(pNMListView->iItem, 0);//override this if you want another dragimage or none at all.
		if(m_DragImage)
		{
			TRACE(_T("Begin drag!\n"));
			VERIFY(m_DragImage->BeginDrag(0, CPoint(0,0)));
			//BOOL x =  ImageList_BeginDrag( m_DragImage->m_hImageList, 0, 0, 0 );	

			m_DragImage->DragEnter(this, pNMListView->ptAction);
			SetCapture();		
		}
	}*/
	
	*pResult = 0;
}

void CMyListCtrlDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_DragImage != NULL)
	{
		VERIFY (m_DragImage->DragLeave (GetDesktopWindow ()));
		m_DragImage->EndDrag ();

		delete m_DragImage;
		m_DragImage = NULL;
		ReleaseCapture();
		TRACE(_T("End drag!\n"));
	}
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CMyListCtrlDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_DragImage != NULL)
	{
		      CPoint pt (point);
			  ClientToScreen (&pt);
			  // move the drag image
			  VERIFY (m_DragImage->DragMove (pt));
			  // unlock window updates
			  VERIFY (m_DragImage->DragShowNolock (FALSE));
			  
			  // get the CWnd pointer of the window that is under the mouse
			  // cursor
			  CWnd* pDropWnd = WindowFromPoint (pt);
			  
			  /*ASSERT (pDropWnd);
			  // if we drag outside current window
			  if (pDropWnd != m_pDropWnd)
			  {
				  // turn off hilight for drop target in list control
				  if (m_nDropIndex != -1)
				  {
					  CListCtrl* pList = (CListCtrl*)m_pDropWnd;
					  VERIFY (pList->SetItemState (m_nDropIndex, 0,
						  LVIS_DROPHILITED));
					  // redraw item
					  VERIFY (pList->RedrawItems (m_nDropIndex, m_nDropIndex));
					  pList->UpdateWindow ();
					  m_nDropIndex = -1;
				  }
			  }*/
			  
			  // save current window pointer
			  //m_pDropWnd = pDropWnd;
			  
			  // convert from screen coordinates to drop target client
			  // coordinates
			  pDropWnd->ScreenToClient (&pt);
			  
/*			  if (pDropWnd->IsKindOf (RUNTIME_CLASS (CListCtrl)))
			  {   
				  UINT uFlags;
				  CListCtrl* pList = (CListCtrl*)pDropWnd;
				  
				  if (m_nDropIndex != -1) {
					  // turn off hilight for previous drop target
					  pList->SetItemState (m_nDropIndex, 0, LVIS_DROPHILITED);
					  // redraw previous item
					  pList->RedrawItems (m_nDropIndex, m_nDropIndex);
					  // we did the RedrawItems, we should update the window
					  fUpdateNeeded = TRUE;
				  }
				  
				  // get the item that is below cursor
				  m_nDropIndex = ((CListCtrl*)pDropWnd)->HitTest (pt, &uFlags);
				  if (m_nDropIndex != -1) 
				  {
					  //By PEK: This makes this thing scrolling
					  //Ensure it's visible
					  pList->EnsureVisible(m_nDropIndex, false);
					  //End PEK
					  
					  // highlight it
					  pList->SetItemState (m_nDropIndex, LVIS_DROPHILITED,
						  LVIS_DROPHILITED);
					  // redraw item
					  pList->RedrawItems (m_nDropIndex, m_nDropIndex);
					  // we did the RedrawItems, we should update the window
					  fUpdateNeeded = TRUE;
				  }
				  
				  // update the list control's window if we need to
				  if (fUpdateNeeded)
					  pList->UpdateWindow ();
				  
			  }*/
	}
			  
			  CDialog::OnMouseMove(nFlags, point);
	
}


void CMyListCtrlDlg::OnCheckEditonenter() 
{
	UpdateData();
	m_list.SetEditOnEnter(m_editonenter != 0);
}

void CMyListCtrlDlg::OnCheckEditonf2() 
{
	UpdateData();
	m_list.SetEditOnF2(m_editonf2 != 0);
}

void CMyListCtrlDlg::OnCheckEditonwriting() 
{
	UpdateData();
	m_list.SetEditOnWriting(m_editonwriting != 0);
}


void CMyListCtrlDlg::OnCheckEditondblclick() 
{
	UpdateData();
	m_list.SetEditOnDblclk(m_editondblclick != 0);
}

void CMyListCtrlDlg::OnButtonFullredraw() 
{
	clock_t   start = clock();

	for(int i=0; i<10; i++)
	{
		m_list.Invalidate();
		m_list.UpdateWindow();
	}

	TRACE(_T("Time to redraw: %f\n"),  (double)(clock() - start) / CLOCKS_PER_SEC);

	
}

//Right click on column header
LRESULT CMyListCtrlDlg::OnHeaderRightClick(WPARAM wParam, LPARAM lParam)
{
	//Make sure message comes from list box
	ASSERT( (HWND)wParam == m_list.GetSafeHwnd() );

	CQuickList::CHeaderRightClick *hit= 
		(CQuickList::CHeaderRightClick*) lParam;

	//Load menu
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_HEADERMENU));

	//Pop up sub menu 0
	CMenu* popup = menu.GetSubMenu(0);
	
	popup->TrackPopupMenu(	TPM_LEFTALIGN | TPM_RIGHTBUTTON,
							hit->m_mousePos.x, 
							hit->m_mousePos.y, 
							this); //AfxGetMainWnd());
	

	return 0;
}

void CMyListCtrlDlg::OnHeadermenuColumn1() 
{
	MessageBox( "If this was a real application, column 1 should "
				"now have disappeared." );
}

void CMyListCtrlDlg::OnHeadermenuColumn2() 
{
	MessageBox( "If this was a real application, column 2 should "
				"now have disappeared." );
}

void CMyListCtrlDlg::OnHeadermenuColumn3() 
{
	MessageBox( "If this was a real application, column 3 should "
				"now have disappeared." );
}

