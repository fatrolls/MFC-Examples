// NewControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewControl.h"
#include "NewControlDlg.h"

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
// CNewControlDlg dialog

CNewControlDlg::CNewControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewControlDlg)
	m_bCheckBoxes = FALSE;
	m_bGridLines = FALSE;
	m_bShowImages = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNewControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewControlDlg)
	DDX_Check(pDX, IDC_CHECK_CHECKBOXES, m_bCheckBoxes);
	DDX_Check(pDX, IDC_CHECK_GRIDLINES, m_bGridLines);
	DDX_Check(pDX, IDC_CHECK_IMAGES, m_bShowImages);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNewControlDlg, CDialog)
	//{{AFX_MSG_MAP(CNewControlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHECK_CHECKBOXES, OnCheckCheckboxes)
	ON_BN_CLICKED(IDC_CHECK_GRIDLINES, OnCheckGridlines)
	ON_BN_CLICKED(IDC_CHECK_IMAGES, OnCheckImages)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_NOTIFY(HTMLLIST_SELECTIONCHANGED,123,OnHTMLList_SelectionChanged)
	ON_NOTIFY(HTMLLIST_LBUTTONDOWN,123,OnHTMLList_LButtonDown)
	ON_NOTIFY(HTMLLIST_LBUTTONDBLCLICK,123,OnHTMLList_LButtonDBLClick)
	ON_NOTIFY(HTMLLIST_RBUTTONDOWN,123,OnHTMLList_RButtonDown)
	ON_NOTIFY(HTMLLIST_ITEMCHECKED,123,OnHTMLList_CheckStateChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewControlDlg message handlers

BOOL CNewControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ImageList.Create(16,16,ILC_COLOR24|ILC_MASK,4,4);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_TEST));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	m_list.Create(this,CRect(10,10,465,350),123);

	m_list.SetImageList(&m_ImageList);

	m_bCheckBoxes = TRUE;
	m_bGridLines = TRUE;
	m_bShowImages = TRUE;
	m_list.SetExtendedStyle(HTMLLIST_STYLE_GRIDLINES|HTMLLIST_STYLE_CHECKBOX|HTMLLIST_STYLE_IMAGES);

	m_list.InsertItem("This is a test string, Height is AUTO (according to text)",0,NORMAL_TEXT);

	m_list.InsertItem("This is a test string, Single Line style and Specified Height(40px)",0,SINGLE_LINE_TEXT,40);

	m_list.InsertItem("This string is too long and will not be wraped, instead it will end in ellipses, This is a test string, ",0,SINGLE_LINE_TEXT,30);

	for(int i = 0;i < 10;i++)
	{
		CString str;
		str.Format("<font color=#ff0000>This is Red Text</font>, <b>This is Bold Text</b>, \
This harmless looking string will actually <u><b>wrap</b></u> to the next line , <br>A BR tag was used to move this line to the next line (%d)",i);
		m_list.InsertItem(str,0,HTML_TEXT);//NORMAL_TEXT);
	}
	
	m_list.InsertItem("This is a test",1,NORMAL_TEXT);
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
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNewControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNewControlDlg::OnPaint() 
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
HCURSOR CNewControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CNewControlDlg::OnEraseBkgnd(CDC* pDC) 
{
		
	return CDialog::OnEraseBkgnd(pDC);
}

void CNewControlDlg::OnHTMLList_SelectionChanged(NMHDR* pNMHDR, LRESULT*)
{
	NM_HTMLLISTCTRL *pListNMHDr = (NM_HTMLLISTCTRL*) pNMHDR;


	if(pListNMHDr->nItemNo != NONE_SELECTED)
	{
		//MessageBox(pListNMHDr->sItemText);
	}
	
}

void CNewControlDlg::OnOK()
{
	CDialog::OnOK();
}

void CNewControlDlg::OnCheckCheckboxes() 
{
	UpdateData();
	if(m_bCheckBoxes)
	{
		m_list.SetExtendedStyle(m_list.GetExtendedStyle() | HTMLLIST_STYLE_CHECKBOX);
	}
	else
	{
		m_list.SetExtendedStyle(m_list.GetExtendedStyle() & ~HTMLLIST_STYLE_CHECKBOX);
	}
}

void CNewControlDlg::OnCheckGridlines() 
{
	UpdateData();
	if(m_bGridLines)
	{
		m_list.SetExtendedStyle(m_list.GetExtendedStyle() | HTMLLIST_STYLE_GRIDLINES);
	}
	else
	{
		m_list.SetExtendedStyle(m_list.GetExtendedStyle() & ~HTMLLIST_STYLE_GRIDLINES);
	}
}

void CNewControlDlg::OnCheckImages() 
{
	UpdateData();
	if(m_bShowImages)
	{
		m_list.SetExtendedStyle(m_list.GetExtendedStyle() | HTMLLIST_STYLE_IMAGES);
	}
	else
	{
		m_list.SetExtendedStyle(m_list.GetExtendedStyle() & ~HTMLLIST_STYLE_IMAGES);
	}	
}

void CNewControlDlg::OnHTMLList_LButtonDown(NMHDR* pNMHDR, LRESULT*)
{
	//MessageBox("LButtonDown");
}

void CNewControlDlg::OnHTMLList_LButtonDBLClick(NMHDR* pNMHDR, LRESULT*)
{
	MessageBox("Double Clicked");
}

void CNewControlDlg::OnHTMLList_RButtonDown(NMHDR* pNMHDR, LRESULT*)
{
	MessageBox("Right Button Clicked");
}
void CNewControlDlg::OnHTMLList_CheckStateChanged(NMHDR* pNMHDR, LRESULT*)
{
	NM_HTMLLISTCTRL *pListNMHDr = (NM_HTMLLISTCTRL*) pNMHDR;


	if(pListNMHDr->nItemNo != NONE_SELECTED)
	{
		if(pListNMHDr->bChecked)
		{
			//MessageBox("Checked");
		}
		else
		{
			//MessageBox("UnChecked");
		}
	}
}

void CNewControlDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CNewControlDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	//was only testing the resizing
	/*if(IsWindow(m_list.GetSafeHwnd()))
	{
		CRect rc;
		m_list.GetClientRect(&rc);
		rc.right = cx;
		rc.bottom = cy;
		m_list.MoveWindow(&rc);
	}*/
}
