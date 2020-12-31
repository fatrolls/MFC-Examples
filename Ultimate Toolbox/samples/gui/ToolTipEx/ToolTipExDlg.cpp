// ToolTipExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolTipExDlg.h"

#include "UTSampleAbout.h"
#include "UTBStrOp.h"
#include "UTB64Bit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipExDlg dialog

CToolTipExDlg::CToolTipExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolTipExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolTipExDlg)
	m_bBoldTips = FALSE;
	m_bSetMaxWidth = FALSE;
	m_nMaxWidth = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolTipExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolTipExDlg)
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_SEPARATOR_SAMPLES, m_sepSamples);
	DDX_Control(pDX, IDC_SEPARATOR_CUSTOMIZE, m_sepCustomize);
	DDX_Control(pDX, IDC_BUTTON_COLOR_BACKGROUND, m_btnBkColor);
	DDX_Control(pDX, IDC_BUTTON_TEXT_FONT_COLOR, m_btnTextFontColor);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Check(pDX, IDC_CHECK1, m_bBoldTips);
	DDX_Check(pDX, IDC_CHECK_SET_MAX_WIDTH, m_bSetMaxWidth);
	DDX_Text(pDX, IDC_EDIT_MAX_WIDTH, m_nMaxWidth);
	//}}AFX_DATA_MAP
	DDX_ColorPicker(pDX, IDC_BUTTON_COLOR_BACKGROUND, m_clrBackground);
	DDX_FontPickerFont(pDX, IDC_BUTTON_TEXT_FONT_COLOR, &m_font);
	DDX_FontPickerColor(pDX, IDC_BUTTON_TEXT_FONT_COLOR, m_clrText);
}

BEGIN_MESSAGE_MAP(CToolTipExDlg, CDialog)
	//{{AFX_MSG_MAP(CToolTipExDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_COLOR_BACKGROUND, OnButtonColorBackground)
	ON_BN_CLICKED(IDC_BUTTON_TEXT_FONT_COLOR, OnButtonTextFontColor)
	ON_BN_CLICKED(IDC_CHECK_SET_MAX_WIDTH, OnCheckSetMaxWidth)
	ON_EN_CHANGE(IDC_EDIT_MAX_WIDTH, OnChangeEditMaxWidth)
	//}}AFX_MSG_MAP
    ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipExDlg message handlers

BOOL CToolTipExDlg::OnToolTipNotify(UINT /*id*/, NMHDR* pNMHDR, LRESULT* /*pResult*/)
{    
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;    
    UINT nID = PtrToUint(pNMHDR->idFrom);

    if (nID == IDCANCEL)    // Get text from string resource
    {
        pTTT->lpszText = MAKEINTRESOURCE(nID);
        pTTT->hinst    = AfxGetResourceHandle();            
        return TRUE;
    }
    if (nID == IDC_RADIO1) // Supply a pointer to some text
    {
        pTTT->lpszText = _T("Radio Button Control");
        return TRUE;
    }
    if (nID == IDC_CHECK1) // Fill in the text buffer
    {
		UTBStr::tcscpy(pTTT->szText, 80, _T("Check Box Control\rCheck this if you want\ntooltips to be bold"));
        return TRUE;
    }

    return FALSE;
}

BOOL CToolTipExDlg::OnInitDialog()
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
	
	m_btnTextFontColor.SetBuddy(IDC_STATIC_TEXT_FONT_COLOR);

	GetDlgItem(IDC_EDIT_MAX_WIDTH)->EnableWindow(m_bSetMaxWidth);

	// initialize the tooltip
	m_toolTip.Create( this );

    // Use AddTool instead
	m_toolTip.AddTool( GetDlgItem(IDC_EDIT1),  
		_T("Edit Control\rThis is the extended\ntext for the edit control"));
	m_toolTip.AddTool( GetDlgItem(IDC_COMBO1), 
		_T("ComboBox Control\rComboBox Control\nData in the lists:\nData 1\nData 2\nData 2\nData 4"));
	m_toolTip.AddTool( GetDlgItem(IDC_TEXT1),  
		_T("Text Control - not extended"));
	m_toolTip.AddTool( GetDlgItem(IDC_LIST1), 
		IDC_LIST1); // _T("List Control\rYou can add strings here"));
	m_toolTip.AddTool( GetDlgItem(IDC_CHECK1),
		LPSTR_TEXTCALLBACK); // _T("Check Box Control\rCheck this if you want\ntooltips to be bold"));
	m_toolTip.AddTool( GetDlgItem(IDC_RADIO1), 
		LPSTR_TEXTCALLBACK); // _T("Radio Button Control"));
	m_toolTip.AddTool( GetDlgItem(IDCANCEL),  
		LPSTR_TEXTCALLBACK); // _T("Close Button Control"));

	m_toolTip.AddTool( GetDlgItem(IDC_TREE1), 
		_T("Tree Control\rHas only one root item"));
	
	m_toolTip.AddTool( GetDlgItem(IDC_BUTTON_TEXT_FONT_COLOR),
		_T("Change Font\rAllows you to change the\nfont and text color\nof the tooltips"));
	m_toolTip.AddTool( GetDlgItem(IDC_BUTTON_COLOR_BACKGROUND),
		_T("Change Tool Tip background color"));
	m_toolTip.AddTool( GetDlgItem(IDC_CHECK_SET_MAX_WIDTH),
		_T("Check the box in order\nto limit the width of the\ntool tip window.\nIf zero is specified then\nthere is no limit on the\nwindow width"));

    m_ListBox.AddString(_T("Sample"));
    m_ListBox.AddString(_T("Listbox"));
    m_ListBox.AddString(_T("Items"));
    m_ListBox.AddString(_T("tab\ttab\ttab"));

	HTREEITEM hRootItem=m_tree.InsertItem(_T("Root item"),-1,-1);
	ASSERT(hRootItem!=NULL);
	for(int nIndex=0; nIndex<20; nIndex++)
	{
		CString sItem;
		sItem.Format(_T("Item %d"),nIndex);
		VERIFY(m_tree.InsertItem(sItem,-1,-1,hRootItem)!=NULL);
	}

	m_btnBkColor.SetDefaultColor(::GetSysColor(COLOR_INFOBK));
	m_clrBackground=m_toolTip.GetTipBkColor();
	m_clrText=m_toolTip.GetTipTextColor();
	LOGFONT lf;
	CFont* pFont=m_toolTip.GetFont();
	ASSERT(pFont!=NULL);
	VERIFY(pFont->GetLogFont(&lf));
	VERIFY(m_font.CreateFontIndirect(&lf));

    // Change the color of one of the tooltips
    OXTOOLINFO ToolInfo;
    if (m_toolTip.GetToolInfo(ToolInfo, GetDlgItem(IDCANCEL)))
    {
        ToolInfo.clrBackColor = RGB(255, 255, 255);
        ToolInfo.clrTextColor = RGB(  0,   0, 255);
        m_toolTip.SetToolInfo(&ToolInfo);
    }

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CToolTipExDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CToolTipExDlg::OnPaint() 
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
HCURSOR CToolTipExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CToolTipExDlg::PreTranslateMessage( MSG *pMsg )
{
   	m_toolTip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}


void CToolTipExDlg::OnButtonColorBackground() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData(TRUE))
		return;

	m_toolTip.SetTipBkColor(m_clrBackground);
}

void CToolTipExDlg::OnButtonTextFontColor() 
{
	// TODO: Add your control notification handler code here
	
	if(!UpdateData(TRUE))
		return;

	m_toolTip.SetTipTextColor(m_clrText);
	m_toolTip.SetFont(&m_font);
}

void CToolTipExDlg::OnCheckSetMaxWidth() 
{
	// TODO: Add your control notification handler code here

	if(!UpdateData(TRUE))
		return;
	
	GetDlgItem(IDC_EDIT_MAX_WIDTH)->EnableWindow(m_bSetMaxWidth);
	if(!m_bSetMaxWidth)
		m_nMaxWidth=0;
	m_toolTip.SetMaxTipWidth(m_nMaxWidth);
}

void CToolTipExDlg::OnChangeEditMaxWidth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	if(!UpdateData(TRUE))
		return;
	
	m_toolTip.SetMaxTipWidth(m_nMaxWidth);
}
