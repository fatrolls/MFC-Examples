// ShortcutBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShortcutBar.h"
#include "ShortcutBarDlg.h"
#include "SHBPropertiesDlg.h"

#include "UTSampleAbout.h"
#include "UTBStrOp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarDlg dialog

CShortcutBarDlg::CShortcutBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShortcutBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShortcutBarDlg)
	m_bAutoScroll = FALSE;
	m_bBoldExpandedGroup = FALSE;
	m_sDescription = _T("");
	m_bDisableDragDropHeader = FALSE;
	m_bEditHeaders = FALSE;
	m_bEditItems = FALSE;
	m_bHandleNotifications = TRUE;
	m_bInfoTip = FALSE;
	m_nSorting = 0;
	m_bNoScroll = FALSE;
	m_bShowActiveAlways = FALSE;
	m_bUnderlineHotItem = FALSE;
	m_bAnimateExpand = FALSE;
	m_bAutoExpand = FALSE;
	m_bDrawHeaderDragImage = FALSE;
	m_bDrawItemDragImage = FALSE;
	m_bDisableDragItem = FALSE;
	m_bDisableDropItem = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bItemDroped=FALSE;
}

void CShortcutBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShortcutBarDlg)
	DDX_Check(pDX, IDC_AUTOSCROLL, m_bAutoScroll);
	DDX_Check(pDX, IDC_BOLDEXPANDEDGROUP, m_bBoldExpandedGroup);
	DDX_Text(pDX, IDC_DESCRIPTION, m_sDescription);
	DDX_Check(pDX, IDC_DISABLEDDRAGDROPHEADER, m_bDisableDragDropHeader);
	DDX_Check(pDX, IDC_EDITHEADERS, m_bEditHeaders);
	DDX_Check(pDX, IDC_EDITITEMS, m_bEditItems);
	DDX_Check(pDX, IDC_HANDLENOTIFICATIONS, m_bHandleNotifications);
	DDX_Check(pDX, IDC_INFOTIP, m_bInfoTip);
	DDX_Radio(pDX, IDC_NO_SORT, m_nSorting);
	DDX_Check(pDX, IDC_NOSCROLL, m_bNoScroll);
	DDX_Check(pDX, IDC_SHOWACTIVEALWAYS, m_bShowActiveAlways);
	DDX_Check(pDX, IDC_UNDERLINEHOTITEM, m_bUnderlineHotItem);
	DDX_Check(pDX, IDC_ANIMATEEXPAND, m_bAnimateExpand);
	DDX_Check(pDX, IDC_AUTOEXPAND, m_bAutoExpand);
	DDX_Check(pDX, IDC_DRAWHEADERDRAGIMAGE, m_bDrawHeaderDragImage);
	DDX_Check(pDX, IDC_DRAWITEMDRAGIMAGE, m_bDrawItemDragImage);
	DDX_Check(pDX, IDC_DISABLEDRAGITEM, m_bDisableDragItem);
	DDX_Check(pDX, IDC_DISABLEDROPITEM, m_bDisableDropItem);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShortcutBarDlg, CDialog)
	//{{AFX_MSG_MAP(CShortcutBarDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ASCENDING, OnAscending)
	ON_BN_CLICKED(IDC_AUTOSCROLL, OnAutoscroll)
	ON_BN_CLICKED(IDC_BOLDEXPANDEDGROUP, OnBoldexpandedgroup)
	ON_BN_CLICKED(IDC_DESCENDING, OnDescending)
	ON_BN_CLICKED(IDC_DISABLEDDRAGDROPHEADER, OnDisableddragdropheader)
	ON_BN_CLICKED(IDC_EDITHEADERS, OnEditheaders)
	ON_BN_CLICKED(IDC_EDITITEMS, OnEdititems)
	ON_BN_CLICKED(IDC_HANDLENOTIFICATIONS, OnHandlenotifications)
	ON_BN_CLICKED(IDC_INFOTIP, OnInfotip)
	ON_BN_CLICKED(IDC_NO_SORT, OnNoSort)
	ON_BN_CLICKED(IDC_NOSCROLL, OnNoscroll)
	ON_BN_CLICKED(IDC_SHOWACTIVEALWAYS, OnShowactivealways)
	ON_BN_CLICKED(IDC_UNDERLINEHOTITEM, OnUnderlinehotitem)
	ON_BN_CLICKED(IDC_AUTOEXPAND, OnAutoexpand)
	ON_BN_CLICKED(IDC_ANIMATEEXPAND, OnAnimateexpand)
	ON_BN_CLICKED(IDC_DRAWITEMDRAGIMAGE, OnDrawitemdragimage)
	ON_BN_CLICKED(IDC_DRAWHEADERDRAGIMAGE, OnDrawheaderdragimage)
	ON_BN_CLICKED(IDC_DISABLEDRAGITEM, OnDisabledragitem)
	ON_BN_CLICKED(IDC_DISABLEDROPITEM, OnDisabledropitem)
	//}}AFX_MSG_MAP

	ON_NOTIFY(SHBN_BEGINDRAGHEADER,IDC_SHORTCUT_BAR,OnBeginDragHeader)
	ON_NOTIFY(SHBN_BEGINHEADEREDIT,IDC_SHORTCUT_BAR,OnBeginHeaderEdit)
	ON_NOTIFY(SHBN_DELETEGROUP,IDC_SHORTCUT_BAR,OnDeleteGroup)
	ON_NOTIFY(SHBN_ENDHEADEREDIT,IDC_SHORTCUT_BAR,OnEndHeaderEdit)
	ON_NOTIFY(SHBN_GETHEADERINFOTIP,IDC_SHORTCUT_BAR,OnGetHeaderInfoTip)
	ON_NOTIFY(SHBN_GROUPEXPANDED,IDC_SHORTCUT_BAR,OnGroupExpanded)
	ON_NOTIFY(SHBN_GROUPEXPANDING,IDC_SHORTCUT_BAR,OnGroupExpanding)
	ON_NOTIFY(SHBN_DRAWHEADER,IDC_SHORTCUT_BAR,OnDrawHeader)
	ON_NOTIFY(SHBN_DROPGROUP,IDC_SHORTCUT_BAR,OnDropGroup)

	ON_NOTIFY(SHBN_BEGINDRAGITEM,IDC_SHORTCUT_BAR,OnBeginDragItem)
	ON_NOTIFY(SHBN_BEGINITEMEDIT,IDC_SHORTCUT_BAR,OnBeginItemEdit)
	ON_NOTIFY(SHBN_DELETEITEM,IDC_SHORTCUT_BAR,OnDeleteItem)
	ON_NOTIFY(SHBN_DELETEALLITEMS,IDC_SHORTCUT_BAR,OnDeleteAllItems)
	ON_NOTIFY(SHBN_ENDITEMEDIT,IDC_SHORTCUT_BAR,OnEndItemEdit)
	ON_NOTIFY(SHBN_GETITEMINFOTIP,IDC_SHORTCUT_BAR,OnGetItemInfoTip)
	ON_NOTIFY(SHBN_INSERTITEM,IDC_SHORTCUT_BAR,OnInsertItem)
	ON_NOTIFY(SHBN_SELECTITEM,IDC_SHORTCUT_BAR,OnSelectItem)
	ON_NOTIFY(SHBN_ACTIVATEITEM,IDC_SHORTCUT_BAR,OnActivateItem)
	ON_NOTIFY(SHBN_HOTITEM,IDC_SHORTCUT_BAR,OnHotItem)
	ON_NOTIFY(SHBN_DRAWITEM,IDC_SHORTCUT_BAR,OnDrawItem)
	ON_NOTIFY(SHBN_DROP,IDC_SHORTCUT_BAR,OnDropItem)
	ON_NOTIFY(SHBN_ENDDRAGDROPITEM,IDC_SHORTCUT_BAR,OnEndDragDropItem)
	
	ON_NOTIFY(SHBN_CONTEXTMENU,IDC_SHORTCUT_BAR,OnSHBContextMenu)

	ON_COMMAND(SHB_IDMPROPERTIES, OnSHBProperties)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarDlg message handlers

BOOL CShortcutBarDlg::OnInitDialog()
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
	InitShortcutBar();

	GetVars();

	m_LayoutManager.Attach(this);

	CRect rect;
	GetClientRect(rect);
	CRect rectBar;
	m_ctlShortcutBar.GetWindowRect(rectBar);
	ScreenToClient(rectBar);
	m_LayoutManager.SetConstraint(IDC_SHORTCUT_BAR, OX_LMS_LEFT, OX_LMT_SAME, 
		rectBar.left-rect.left);
	m_LayoutManager.SetConstraint(IDC_SHORTCUT_BAR, OX_LMS_TOP, OX_LMT_SAME, 
		rectBar.top-rect.top);
	m_LayoutManager.SetConstraint(IDC_SHORTCUT_BAR, OX_LMS_RIGHT, OX_LMT_SAME, 
		rectBar.right-rect.right);
	m_LayoutManager.SetConstraint(IDC_SHORTCUT_BAR, OX_LMS_BOTTOM, OX_LMT_SAME, 
		rectBar.bottom-rect.bottom);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShortcutBarDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShortcutBarDlg::OnPaint() 
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
HCURSOR CShortcutBarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShortcutBarDlg::OnAscending() 
{
	// TODO: Add your control notification handler code here

	m_nSorting=1;
	m_ctlShortcutBar.SortGroups(1);
	m_ctlShortcutBar.RedrawBar();

	UpdateData(FALSE);
}

void CShortcutBarDlg::OnAutoscroll() 
{
	// TODO: Add your control notification handler code here

	if(!UpdateData())
		return;

	if(m_bAutoScroll)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_AUTOSCROLL);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_AUTOSCROLL);
}

void CShortcutBarDlg::OnBoldexpandedgroup() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bBoldExpandedGroup)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_BOLDEXPANDEDGROUP);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_BOLDEXPANDEDGROUP);
	m_ctlShortcutBar.RedrawBar();
}

void CShortcutBarDlg::OnDescending() 
{
	// TODO: Add your control notification handler code here
	
	m_nSorting=2;
	m_ctlShortcutBar.SortGroups(-1);
	m_ctlShortcutBar.RedrawBar();

	UpdateData(FALSE);
}

void CShortcutBarDlg::OnDisableddragdropheader() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bDisableDragDropHeader)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_DISABLEDRAGDROPHEADER);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_DISABLEDRAGDROPHEADER);
}

void CShortcutBarDlg::OnDisabledragitem() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bDisableDragItem)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|
			SHBS_DISABLEDRAGITEM);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&
			~SHBS_DISABLEDRAGITEM);
}

void CShortcutBarDlg::OnDisabledropitem() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bDisableDropItem)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|
			SHBS_DISABLEDROPITEM);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&
			~SHBS_DISABLEDROPITEM);
}

void CShortcutBarDlg::OnEditheaders() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bEditHeaders)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_EDITHEADERS);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_EDITHEADERS);
}

void CShortcutBarDlg::OnEdititems() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bEditItems)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_EDITITEMS);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_EDITITEMS);
}

void CShortcutBarDlg::OnHandlenotifications() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
}

void CShortcutBarDlg::OnInfotip() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bInfoTip)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_INFOTIP);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_INFOTIP);
}

void CShortcutBarDlg::OnNoSort() 
{
	// TODO: Add your control notification handler code here
	
	m_nSorting=0;
	m_ctlShortcutBar.SortGroups(0);
	m_ctlShortcutBar.RedrawBar();

	UpdateData(FALSE);
}

void CShortcutBarDlg::OnNoscroll() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bNoScroll)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_NOSCROLL);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_NOSCROLL);
	m_ctlShortcutBar.RedrawBar();
}

void CShortcutBarDlg::OnShowactivealways() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bShowActiveAlways)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_SHOWACTIVEALWAYS);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_SHOWACTIVEALWAYS);
	m_ctlShortcutBar.RedrawBar();
}

void CShortcutBarDlg::OnUnderlinehotitem() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bUnderlineHotItem)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_UNDERLINEHOTITEM);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_UNDERLINEHOTITEM);
	m_ctlShortcutBar.RedrawBar();
}

void CShortcutBarDlg::InitShortcutBar()
{
	CWnd *pFrame=GetDlgItem(IDC_SHORTCUT_BAR);
	CRect rcWnd;
	pFrame->GetWindowRect(rcWnd);
	pFrame->DestroyWindow(); //pFrame was just a placeholder anyway.
	ScreenToClient(rcWnd);
	m_ctlShortcutBar.Create(this,rcWnd,SHBS_EDITHEADERS|SHBS_EDITITEMS|
		SHBS_DISABLEDRAGDROPITEM|SHBS_DISABLEDRAGDROPHEADER,IDC_SHORTCUT_BAR);

	// create tree control 
	m_tree.Create(TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_EDITLABELS,
		CRect(0,0,0,0),&m_ctlShortcutBar,IDC_TREE);

	TV_INSERTSTRUCT	tvstruct;
	TCHAR rgszItems[][20]={_T("Mail Box"),_T("Calendar"),_T("Deleted Items"), 
		_T("Inbox"),_T("Journal"),_T("Notes"),_T("Outbox"),_T("Sent Items")};
	VERIFY(m_ilTree.Create(IDB_TREE,16,8,RGB(255,0,255)));
	m_tree.SetImageList(&m_ilTree,TVSIL_NORMAL);

	HTREEITEM hParent=NULL;
	int nIndex=0;
	for(nIndex=0; nIndex<(sizeof(rgszItems)/sizeof(rgszItems[0])); nIndex++)
	{
		tvstruct.hParent=nIndex==0 ? NULL : hParent;
		tvstruct.hInsertAfter=TVI_LAST;
		tvstruct.item.iImage=nIndex;
		tvstruct.item.iSelectedImage=nIndex;
		tvstruct.item.pszText=rgszItems[nIndex];
		tvstruct.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
		HTREEITEM hItem=m_tree.InsertItem(&tvstruct);
		hParent=hParent==NULL ? hItem : hParent;
	}


	//	populate shortcut bar
	m_ctlShortcutBar.SetImageList(&m_ilTree);

	

	SHB_GROUPINFO shbGroup;
	CString sText;

	// create image lists
	VERIFY(m_ilLarge.Create(IDB_LARGE,32,11,RGB(128,128,128)));
	VERIFY(m_ilSmall.Create(IDB_SMALL,16,11,RGB(128,128,128)));

	// outlook group
	sText=_T("Outlook");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	m_ctlShortcutBar.InsertGroup(&shbGroup);

	// mail group
	sText=_T("Mail");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	m_ctlShortcutBar.InsertGroup(&shbGroup);	

	// group with tree control child window
	sText=_T("Other");
	shbGroup.nMask=SHBIF_TEXT|SHBIF_CHILDWND;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	shbGroup.pszText[sText.GetLength()] = 0;
	sText.ReleaseBuffer();
	shbGroup.hwndChild=m_tree.GetSafeHwnd();
	m_ctlShortcutBar.InsertGroup(&shbGroup);

	// fill standard list controls
	TCHAR shbszItems[][20]={_T("Inbox"),_T("Calendar"),_T("Contracts"), 
		_T("Tasks"),_T("Journal"),_T("Notes"),_T("Deleted Items"),_T("Inbox"),
		_T("Sent Items"),_T("Outbox"),_T("Deleted Items")};

	// find outlook group and populate it
	sText=_T("Outlook");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	HSHBGROUP hGroup=m_ctlShortcutBar.FindGroup(&shbGroup);
	ASSERT(hGroup);

	m_ctlShortcutBar.SetLCImageList(hGroup,&m_ilLarge,LVSIL_NORMAL);
	m_ctlShortcutBar.SetLCImageList(hGroup,&m_ilSmall,LVSIL_SMALL);

	for(int i=0 ; i<10; i++)
	for(nIndex=0; nIndex<7 ; nIndex++)
	{
		CString sText=shbszItems[nIndex];
		m_ctlShortcutBar.InsertLCItem(hGroup,nIndex+7*i,sText,nIndex);
	}
	m_ctlShortcutBar.ExpandGroup(hGroup);
	
	// find mail group and populate it
	sText=_T("Mail");
	shbGroup.nMask=SHBIF_TEXT;
	shbGroup.nTextMax=sText.GetLength();
	shbGroup.pszText=sText.GetBuffer(shbGroup.nTextMax);
	sText.ReleaseBuffer();
	hGroup=m_ctlShortcutBar.FindGroup(&shbGroup);
	ASSERT(hGroup);

	m_ctlShortcutBar.SetLCImageList(hGroup,&m_ilLarge,LVSIL_NORMAL);
	m_ctlShortcutBar.SetLCImageList(hGroup,&m_ilSmall,LVSIL_SMALL);

	for(nIndex=7; nIndex<(sizeof(shbszItems)/sizeof(shbszItems[0])); nIndex++)
	{
		CString sText=shbszItems[nIndex];
		LV_ITEM lvi;
		lvi.iItem=nIndex-7;
		lvi.iSubItem=0;
		lvi.mask=LVIF_TEXT|LVIF_IMAGE;
		lvi.iImage=nIndex;
		lvi.cchTextMax=sText.GetLength();
		lvi.pszText=sText.GetBuffer(lvi.cchTextMax);
		sText.ReleaseBuffer();
		m_ctlShortcutBar.InsertLCItem(hGroup,&lvi);
	}

	DWORD dwBarStyle=m_ctlShortcutBar.GetBarStyle();
	dwBarStyle&=~(SHBS_DISABLEDRAGDROPHEADER|SHBS_DISABLEDRAGDROPITEM);
	dwBarStyle|=SHBS_DRAWITEMDRAGIMAGE|SHBS_DRAWHEADERDRAGIMAGE|SHBS_INFOTIP|
		SHBS_AUTOEXPAND|SHBS_ANIMATEEXPAND;
	m_ctlShortcutBar.SetBarStyle(dwBarStyle);
}

void CShortcutBarDlg::GetVars()
{
	m_bAutoScroll=(m_ctlShortcutBar.GetBarStyle()&SHBS_AUTOSCROLL)!=0;
	m_bBoldExpandedGroup=(m_ctlShortcutBar.GetBarStyle()&SHBS_BOLDEXPANDEDGROUP)!=0;
	m_bDisableDragDropHeader=(m_ctlShortcutBar.GetBarStyle()&
		SHBS_DISABLEDRAGDROPHEADER)!=0;
	m_bDisableDragItem=(m_ctlShortcutBar.GetBarStyle()&
		SHBS_DISABLEDRAGITEM)!=0;
	m_bDisableDropItem=(m_ctlShortcutBar.GetBarStyle()&
		SHBS_DISABLEDROPITEM)!=0;
	m_bDrawItemDragImage=(m_ctlShortcutBar.GetBarStyle()&SHBS_DRAWITEMDRAGIMAGE)!=0;
	m_bDrawHeaderDragImage=(m_ctlShortcutBar.GetBarStyle()&SHBS_DRAWHEADERDRAGIMAGE)!=0;
	m_bEditHeaders=(m_ctlShortcutBar.GetBarStyle()&SHBS_EDITHEADERS)!=0;
	m_bEditItems=(m_ctlShortcutBar.GetBarStyle()&SHBS_EDITITEMS)!=0;
	m_bInfoTip=(m_ctlShortcutBar.GetBarStyle()&SHBS_INFOTIP)!=0;
	m_bNoScroll=(m_ctlShortcutBar.GetBarStyle()&SHBS_NOSCROLL)!=0;
	m_bShowActiveAlways=(m_ctlShortcutBar.GetBarStyle()&SHBS_SHOWACTIVEALWAYS)!=0;
	m_bUnderlineHotItem=(m_ctlShortcutBar.GetBarStyle()&SHBS_UNDERLINEHOTITEM)!=0;
	m_bAutoExpand=(m_ctlShortcutBar.GetBarStyle()&SHBS_AUTOEXPAND)!=0;
	m_bAnimateExpand=(m_ctlShortcutBar.GetBarStyle()&SHBS_ANIMATEEXPAND)!=0;

	HSHBGROUP hGroup=m_ctlShortcutBar.GetExpandedGroup();
	int nCount= PtrToInt(m_ctlShortcutBar.GetGroupCount());
	if(nCount==0)
		m_sDescription=_T("There is no groups in the shortcut bar");
	else
	{
		CString sGroupCount;
		if(nCount>1)
			sGroupCount.Format(_T("There are %d groups in the shortcut bar."),nCount);
		else
			sGroupCount.Format(_T("There is 1 group in the shortcut bar."));

		if(hGroup==NULL)
			m_sDescription.Format(_T("%s There is no any expanded group."),sGroupCount);
		else
			m_sDescription.Format(_T("%s Group %s is expanded, it's order is %d. Child window is %s and it is in %s view."),
				sGroupCount,m_ctlShortcutBar.GetGroupText(hGroup),
				m_ctlShortcutBar.GetGroupOrder(hGroup),
				((m_ctlShortcutBar.GetGroupChildWnd(hGroup)==NULL) ? 
				_T("standard list control") : _T("special defined window")),
				((m_ctlShortcutBar.GetGroupView(hGroup)==SHB_LARGEICON) ? 
				_T("Large Icons") : _T("Small Icons")));
	}

	UpdateData(FALSE);

	ShowControls();
}

void CShortcutBarDlg::ShowControls()
{
}

void CShortcutBarDlg::OnBeginDragHeader(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnBeginDragHeader - SHBN_BEGINDRAGHEADER\n"));

	*result=0;
}

void CShortcutBarDlg::OnBeginHeaderEdit(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnBeginHeaderEdit - SHBN_BEGINHEADEREDIT\n"));

	*result=0;
}

void CShortcutBarDlg::OnDeleteGroup(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnDeleteGroup - SHBN_DELETEGROUP\n"));

	GetVars();
	UpdateData();

	*result=0;
}

void CShortcutBarDlg::OnEndHeaderEdit(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnEndHeaderEdit - SHBN_ENDHEADEREDIT\n"));

	*result=0;
}

void CShortcutBarDlg::OnGetHeaderInfoTip(NMHDR* pNotifyStruct, LRESULT* result)
{
	if(m_bHandleNotifications)
		TRACE(_T("OnGetHeaderInfoTip - SHBN_GETHEADERINFOTIP\n"));

	LPNMSHORTCUTBAR pNMSHB=(LPNMSHORTCUTBAR)pNotifyStruct;
	ASSERT(pNMSHB!=NULL);

	HSHBGROUP hGroup=pNMSHB->hGroup;
	CString sText;
	sText.Format(_T("Tooltip for group '%s' which order is - %d"),
		m_ctlShortcutBar.GetGroupText(hGroup),m_ctlShortcutBar.GetGroupOrder(hGroup));

	LPSHBINFOTIP pSHBIT=(LPSHBINFOTIP)pNMSHB->lParam; 
	UTBStr::tcsncpy(pSHBIT->szText,countof(pSHBIT->szText),sText.GetBuffer(sText.GetLength()),countof(pSHBIT->szText));
	sText.ReleaseBuffer();

	*result=1;
}

void CShortcutBarDlg::OnGroupExpanded(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnGroupExpanded - SHBN_GROUPEXPANDED\n"));

	GetVars();
	UpdateData();

	*result=0;
}

void CShortcutBarDlg::OnGroupExpanding(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnGroupExpanding - SHBN_GROUPEXPANDING\n"));

	*result=0;
}

void CShortcutBarDlg::OnDrawHeader(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnDrawHeader - SHBN_DRAWHEADER\n"));

	*result=0;
}

	
void CShortcutBarDlg::OnBeginDragItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnBeginDragItem - SHBN_BEGINDRAGITEM\n"));

	*result=0;
}

void CShortcutBarDlg::OnDropGroup(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnDropGroup - SHBN_DROPGROUP\n"));

	*result=0;
}

void CShortcutBarDlg::OnBeginItemEdit(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnBeginItemEdit - SHBN_BEGINITEMEDIT\n"));

	*result=0;
}

void CShortcutBarDlg::OnDeleteItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnDeleteItem - SHBN_DELETEITEM\n"));

	*result=0;
}

void CShortcutBarDlg::OnDeleteAllItems(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnDeleteAllItems - SHBN_DELETEALLITEMS\n"));

	*result=0;
}

void CShortcutBarDlg::OnEndItemEdit(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnEndItemEdit - SHBN_ENDITEMEDIT\n"));

	*result=0;
}

void CShortcutBarDlg::OnGetItemInfoTip(NMHDR* pNotifyStruct, LRESULT* result)
{
	if(m_bHandleNotifications)
		TRACE(_T("OnGetItemInfoTip - SHBN_GETITEMINFOTIP\n"));

	LPNMSHORTCUTBAR pNMSHB=(LPNMSHORTCUTBAR)pNotifyStruct;
	ASSERT(pNMSHB!=NULL);

	int nItem=pNMSHB->nItem;
	CString sText;
	sText.Format(_T("Tooltip for item '%s'"),
		m_ctlShortcutBar.GetGroupListCtrl(pNMSHB->hGroup)->GetItemText(nItem,0));

	LPSHBINFOTIP pSHBIT=(LPSHBINFOTIP)pNMSHB->lParam; 
	UTBStr::tcsncpy(pSHBIT->szText,countof(pSHBIT->szText),sText.GetBuffer(sText.GetLength()),countof(pSHBIT->szText));
	sText.ReleaseBuffer();

	*result=0;
}

void CShortcutBarDlg::OnInsertItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	LPNMSHORTCUTBAR pNMSHB=(LPNMSHORTCUTBAR)pNotifyStruct;
	ASSERT(pNMSHB!=NULL);

	if(m_bHandleNotifications)
		TRACE(_T("OnInsertItem - SHBN_INSERTITEM\n"));

	static DWORD lParam=0;
	if(m_ctlShortcutBar.GetGroupListCtrl(pNMSHB->hGroup)->
		GetItemData(pNMSHB->nItem)==0)
	{
		lParam++;
		m_ctlShortcutBar.GetGroupListCtrl(pNMSHB->hGroup)->
			SetItemData(pNMSHB->nItem,lParam);
	}

	GetVars();
	UpdateData();

	if(m_bItemDroped)
		m_dwDropedItemData=m_ctlShortcutBar.GetGroupListCtrl(pNMSHB->hGroup)->
			GetItemData(pNMSHB->nItem);
	*result=0;
}

void CShortcutBarDlg::OnSelectItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	LPNMSHORTCUTBAR pNMSHB=(LPNMSHORTCUTBAR)pNotifyStruct;
	ASSERT(pNMSHB!=NULL);

	if(m_bHandleNotifications)
		TRACE(_T("OnSelectItem - SHBN_SELECTITEM\n"));

	if(pNMSHB->nItem!=-1)
		m_ctlShortcutBar.GetGroupListCtrl(pNMSHB->hGroup)->
			GetItemData(pNMSHB->nItem);

	*result=0;
}

void CShortcutBarDlg::OnActivateItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnActivateItem - SHBN_ACTIVATEITEM\n"));

	*result=0;
}

void CShortcutBarDlg::OnHotItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnHotItem - SHBN_HOTITEM\n"));

	*result=0;
}

void CShortcutBarDlg::OnDrawItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnDrawItem - SHBN_DRAWITEM\n"));

	*result=0;
}

void CShortcutBarDlg::OnDropItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	UNREFERENCED_PARAMETER(pNotifyStruct);

	if(m_bHandleNotifications)
		TRACE(_T("OnDropItem - SHBN_DROP\n"));

	m_bItemDroped=TRUE;

	*result=0;
}

void CShortcutBarDlg::OnEndDragDropItem(NMHDR* pNotifyStruct, LRESULT* result)
{
	LPNMSHORTCUTBAR pNMSHB=(LPNMSHORTCUTBAR)pNotifyStruct;
	ASSERT(pNMSHB!=NULL);

	if(m_bHandleNotifications)
		TRACE(_T("OnEndDragDropItem - SHBN_ENDDRAGDROPITEM\n"));

	if(m_bItemDroped && (DROPEFFECT)pNMSHB->lParam!=DROPEFFECT_NONE)
	{
		COXSHBListCtrl* pListCtrl=m_ctlShortcutBar.GetGroupListCtrl(pNMSHB->hGroup);
		ASSERT(pListCtrl);

		LV_FINDINFO lvfi;
		lvfi.flags=LVFI_PARAM;
		lvfi.lParam=m_dwDropedItemData;
		int nItem=pListCtrl->FindItem(&lvfi);
		ASSERT(nItem!=-1);

		if(pListCtrl->GetItemText(nItem,0).IsEmpty())
			pListCtrl->PostMessage(LVM_EDITLABEL,(WPARAM)nItem);
	}
	m_bItemDroped=FALSE;

	*result=0;
}


void CShortcutBarDlg::OnSHBContextMenu(NMHDR* pNotifyStruct, LRESULT* result)
{
	if(m_bHandleNotifications)
		TRACE(_T("OnSHBContextMenu - SHBN_CONTEXTMENU\n"));

	LPSHBCONTEXTMENU pSHBCM=
		(LPSHBCONTEXTMENU)((LPNMSHORTCUTBAR)pNotifyStruct)->lParam;
	if(pSHBCM->pShortcutBar==&m_ctlShortcutBar && 
		m_ctlShortcutBar.GetExpandedGroup()!=NULL)
	{
		CMenu* pMenu=pSHBCM->pMenu;
		if(pMenu->GetMenuItemCount()>0)
			pMenu->AppendMenu(MF_SEPARATOR);
		pMenu->AppendMenu(MF_STRING,SHB_IDMPROPERTIES,_T("Properties..."));
	}

	*result=0;
}

void CShortcutBarDlg::OnSHBProperties()
{
	CSHBPropertiesDlg propertiesDlg(&m_ctlShortcutBar);
	propertiesDlg.DoModal();
}

void CShortcutBarDlg::OnAutoexpand() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bAutoExpand)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_AUTOEXPAND);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_AUTOEXPAND);
}

void CShortcutBarDlg::OnAnimateexpand() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bAnimateExpand)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_ANIMATEEXPAND);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_ANIMATEEXPAND);
}

void CShortcutBarDlg::OnDrawitemdragimage() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bDrawItemDragImage)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_DRAWITEMDRAGIMAGE);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_DRAWITEMDRAGIMAGE);
}

void CShortcutBarDlg::OnDrawheaderdragimage() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData())
		return;

	if(m_bDrawHeaderDragImage)
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()|SHBS_DRAWHEADERDRAGIMAGE);
	else
		m_ctlShortcutBar.SetBarStyle(m_ctlShortcutBar.GetBarStyle()&~SHBS_DRAWHEADERDRAGIMAGE);
}

