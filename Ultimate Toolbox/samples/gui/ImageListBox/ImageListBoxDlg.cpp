// ImageListBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageListBox.h"
#include "ImageListBoxDlg.h"

#include "utsampleabout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageListBoxDlg dialog

CImageListBoxDlg::CImageListBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageListBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageListBoxDlg)
	m_sIconSourceFile = _T("");
	m_nSourceType = -1;
	m_nSelectedImage = -1;
	m_bUseSmallIcons = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageListBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageListBoxDlg)
	DDX_Control(pDX, IDC_BUTTON_BK_COLOR, m_btnBkColor);
	DDX_Control(pDX, IDC_STATIC_OPERATIONS, m_sepOperations);
	DDX_Control(pDX, IDC_LIST_IMAGES, m_listImages);
	DDX_Control(pDX, IDC_COMBO_ICONSOURCE_FILENAME, m_comboIconSourceFile);
	DDX_CBString(pDX, IDC_COMBO_ICONSOURCE_FILENAME, m_sIconSourceFile);
	DDX_Radio(pDX, IDC_RADIO_DEFAULT, m_nSourceType);
	DDX_LBIndex(pDX, IDC_LIST_IMAGES, m_nSelectedImage);
	DDX_Check(pDX, IDC_CHECK_SMALL_ICONS, m_bUseSmallIcons);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_BK_COLOR, m_clrBackground);
}

BEGIN_MESSAGE_MAP(CImageListBoxDlg, CDialog)
	//{{AFX_MSG_MAP(CImageListBoxDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD_DEFAULT, OnButtonAddDefault)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_CBN_EDITCHANGE(IDC_COMBO_ICONSOURCE_FILENAME, OnEditchangeComboIconsourceFilename)
	ON_CBN_SELCHANGE(IDC_COMBO_ICONSOURCE_FILENAME, OnSelchangeComboIconsourceFilename)
	ON_LBN_SELCHANGE(IDC_LIST_IMAGES, OnSelchangeListImages)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, OnRadioCustom)
	ON_BN_CLICKED(IDC_RADIO_DEFAULT, OnRadioDefault)
	ON_BN_CLICKED(IDC_BUTTON_BK_COLOR, OnButtonBkColor)
	ON_BN_CLICKED(IDC_CHECK_SMALL_ICONS, OnCheckSmallIcons)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageListBoxDlg message handlers

BOOL CImageListBoxDlg::OnInitDialog()
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

	// create default image list
	VERIFY(m_ilDefault.Create(IDB_IL_DEFAULT,16,0,RGB(192,192,192)));

	m_nSourceType=0;
	// populate image list box with images
	m_listImages.SetImageList(&m_ilDefault);

	// setup history combo
	m_comboIconSourceFile.
		SetAutoPersistent(_T("CustomizeTrayIcon_IconSourceFileName"));
	for(int nIndex=4; nIndex<OX_HISTORY_COMBO_MAX_TOOLBUTTONS; nIndex++)
	{
		m_comboIconSourceFile.ShowButton(nIndex,FALSE);
	}
	CToolBar* pToolbar=m_comboIconSourceFile.GetToolBar();
	pToolbar->ModifyStyle(NULL,TBSTYLE_FLAT);
	m_comboIconSourceFile.RefreshToolbar();

	m_clrBackground=m_listImages.GetBkColor();
	m_btnBkColor.SetToolTip(TRUE);

	m_bUseSmallIcons=TRUE;

	UpdateData(FALSE);

	ShowControls();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageListBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CImageListBoxDlg::OnPaint() 
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
HCURSOR CImageListBoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CImageListBoxDlg::OnButtonAddDefault() 
{
	// TODO: Add your control notification handler code here
	m_listImages.AddImageList(&m_ilDefault);
}

void CImageListBoxDlg::OnButtonRemove() 
{
	// TODO: Add your control notification handler code here
	m_listImages.RemoveImage(m_nSelectedImage);
	m_listImages.SetCurSel(m_nSelectedImage);
}

void CImageListBoxDlg::OnEditchangeComboIconsourceFilename() 
{
	// TODO: Add your control notification handler code here
	ShowControls();
	LoadFromFile();
}

void CImageListBoxDlg::OnSelchangeComboIconsourceFilename() 
{
	// TODO: Add your control notification handler code here
	ShowControls();
	if(m_comboIconSourceFile.GetCurSel()!=CB_ERR)
	{
		m_comboIconSourceFile.GetLBText(m_comboIconSourceFile.GetCurSel(),
			m_sIconSourceFile);
		UpdateData(FALSE);
		ShowControls();
		LoadFromFile();
	}
}

void CImageListBoxDlg::OnSelchangeListImages() 
{
	// TODO: Add your control notification handler code here
	ShowControls();
}

void CImageListBoxDlg::OnRadioCustom() 
{
	// TODO: Add your control notification handler code here
	ShowControls();
	// populate with icons from the source file
	LoadFromFile();
}

void CImageListBoxDlg::OnRadioDefault() 
{
	// TODO: Add your control notification handler code here
	ShowControls();
	// populate image list box with images
	m_listImages.SetImageList(&m_ilDefault);
	m_listImages.SetCurSel(0);
}

void CImageListBoxDlg::OnButtonBkColor() 
{
	// TODO: Add your control notification handler code here
	ShowControls();
	m_listImages.SetBkColor(m_clrBackground);
}

void CImageListBoxDlg::OnCheckSmallIcons() 
{
	// TODO: Add your control notification handler code here
	ShowControls();
	LoadFromFile();
}

void CImageListBoxDlg::ShowControls()
{
	if(!UpdateData(TRUE))
		return;

	GetDlgItem(IDC_BUTTON_REMOVE)->EnableWindow(m_nSelectedImage!=-1);
	GetDlgItem(IDC_BUTTON_ADD_DEFAULT)->
		EnableWindow(m_nSourceType==1 && m_bUseSmallIcons && 
		!m_sIconSourceFile.IsEmpty());
	GetDlgItem(IDC_CHECK_SMALL_ICONS)->EnableWindow(m_nSourceType==1);
	m_comboIconSourceFile.EnableWindow(m_nSourceType==1);
}

void CImageListBoxDlg::LoadFromFile()
{
	if(!m_sIconSourceFile.IsEmpty())
	{
		m_listImages.LoadIconsFromFile(m_sIconSourceFile,m_bUseSmallIcons);
		m_listImages.SetCurSel(0);
	}
	else
	{	
		m_listImages.EmptyImageList();
	}	
}