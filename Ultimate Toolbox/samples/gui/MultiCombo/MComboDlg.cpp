// MComboDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UTSampleAbout.h"
#include "mcombo.h"
#include "MComboDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMComboDlg dialog

CMComboDlg::CMComboDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMComboDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMComboDlg)
	m_MasterColumn = 0;
	m_ColumnWidth = 0;
	m_ColWidth_ColNum = 0;
	m_ColCount = 0;
	m_AddList = _T("");
	m_InsertAt_ColNum = 0;
	m_LBText = _T("");
	m_LBText_ColNum = 0;
	m_LBText_RowNum = 0;
	m_SelectColNum = 0;
	m_SelectStartAfter = 0;
	m_SelectString = _T("");
	m_dwItemData = 0;
	m_nItemDataIndex = 0;
	m_bFitToSize = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMComboDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMComboDlg)
	DDX_Control(pDX, IDC_COMBO1, m_MCombo);
	DDX_Control(pDX, IDC_EDIT_SELECT_STARTAFTER_SPIN, m_wndSelectStartAfterSpin);
	DDX_Control(pDX, IDC_EDIT_SELECT_COLUMNNUMBER_SPIN, m_wndSelectColNumSpin);
	DDX_Control(pDX, IDC_EDIT_MASTERCOLUMNNUMBER_SPIN, m_wndMasterColumnSpin);
	DDX_Control(pDX, IDC_EDIT_LBTEXT_ROWNUM_SPIN, m_wndLBTextRowNumSpin);
	DDX_Control(pDX, IDC_EDIT_ITEMDATAINDEX_SPIN, m_wndItemDataIndexSpin);
	DDX_Control(pDX, IDC_EDIT_ITEMDATA_SPIN, m_wndItemDataSpin);
	DDX_Control(pDX, IDC_EDIT_INSERTAT_SPIN, m_wndInsertAtColNumSpin);
	DDX_Control(pDX, IDC_EDIT_GETLBTEXT_COLUMNNUMBER_SPIN, m_wndLBTextColNumSpin);
	DDX_Control(pDX, IDC_EDIT_COLUMNWIDTH_SPIN, m_wndColWidthSpin);
	DDX_Control(pDX, IDC_EDIT_COLCOUNT_SPIN, m_wndColCountSpin);
	DDX_Control(pDX, IDC_EDIT_COLUMNWIDTH_COLUMNNUMBER_SPIN, m_wndColWidthColSpin);
	DDX_Text(pDX, IDC_EDIT_MASTERCOLUMNNUMBER, m_MasterColumn);
	DDX_Text(pDX, IDC_EDIT_COLUMNWIDTH, m_ColumnWidth);
	DDX_Text(pDX, IDC_EDIT_COLUMNWIDTH_COLUMNNUMBER, m_ColWidth_ColNum);
	DDX_Text(pDX, IDC_EDIT_COLCOUNT, m_ColCount);
	DDX_Text(pDX, IDC_EDIT_ADD, m_AddList);
	DDV_MaxChars(pDX, m_AddList, 100000);
	DDX_Text(pDX, IDC_EDIT_INSERTAT, m_InsertAt_ColNum);
	DDX_Text(pDX, IDC_EDIT_GETLBTEXT, m_LBText);
	DDX_Text(pDX, IDC_EDIT_GETLBTEXT_COLUMNNUMBER, m_LBText_ColNum);
	DDX_Text(pDX, IDC_EDIT_LBTEXT_ROWNUM, m_LBText_RowNum);
	DDX_Text(pDX, IDC_EDIT_SELECT_COLUMNNUMBER, m_SelectColNum);
	DDX_Text(pDX, IDC_EDIT_SELECT_STARTAFTER, m_SelectStartAfter);
	DDX_Text(pDX, IDC_EDIT_SELECT_STRING, m_SelectString);
	DDX_Text(pDX, IDC_EDIT_ITEMDATA, m_dwItemData);
	DDX_Text(pDX, IDC_EDIT_ITEMDATAINDEX, m_nItemDataIndex);
	DDX_Check(pDX, IDC_CHECK_FITTOSIZE, m_bFitToSize);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMComboDlg, CDialog)
	//{{AFX_MSG_MAP(CMComboDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SETMASTERCOLUMN, OnButtonSetmastercolumn)
	ON_BN_CLICKED(IDC_BUTTON_SETCOLUMNWIDTH, OnButtonSetcolumnwidth)
	ON_BN_CLICKED(IDC_BUTTON_SETCOLCOUNT, OnButtonSetcolcount)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_INSERTAT, OnButtonInsertat)
	ON_BN_CLICKED(IDC_BUTTON_GETLBTEXT, OnButtonGetlbtext)
	ON_BN_CLICKED(IDC_BUTTON_SELECTSTRING, OnButtonSelectstring)
	ON_BN_CLICKED(IDC_BUTTON_SETITEMDATA, OnButtonSetitemdata)
	ON_BN_CLICKED(IDC_BUTTON_GETITEMDATA, OnButtonGetitemdata)
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_CBN_EDITUPDATE(IDC_COMBO1, OnEditupdateCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CHECK_FITTOSIZE, OnCheckFittosize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMComboDlg message handlers

BOOL CMComboDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

		// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);

	if (!strAboutMenu.IsEmpty())
		{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_MCombo.SetColumnCount(3);
	m_MCombo.SetColumnWidth(0,100);
	m_MCombo.SetColumnWidth(1,120);
	m_MCombo.SetColumnWidth(2,20);
	LPTSTR str1[] = {_T("David"), _T("Cunningham"), _T("1")};
	LPTSTR str2[] = {_T("Troy") , _T("Marchand"), _T("2")};
	LPTSTR str3[] = {_T("Andrei"), _T("Zenkovitch"), _T("3")};
	LPTSTR str4[] = {_T("Ghazi"), _T("Wadi"), _T("4")};

	m_MCombo.AddString((LPCTSTR*)str1,3);
	m_MCombo.AddString((LPCTSTR*)str2,3);
	m_MCombo.AddString((LPCTSTR*)str3,3);
	m_MCombo.AddString((LPCTSTR*)str4,3);

	m_wndSelectStartAfterSpin.SetRange(-1, 100);
	m_wndSelectColNumSpin.SetRange(0, 100);
	m_wndMasterColumnSpin.SetRange(0, 100);
	m_wndLBTextRowNumSpin.SetRange(0, 100);
	m_wndItemDataIndexSpin.SetRange(0, 100);
	m_wndItemDataSpin.SetRange(0, 100);
	m_wndInsertAtColNumSpin.SetRange(0, 100);
	m_wndLBTextColNumSpin.SetRange(0, 100);
	m_wndColWidthSpin.SetRange(0, 100);
	m_wndColCountSpin.SetRange(0, 100);
	m_wndColWidthColSpin.SetRange(0, 100);

	m_bFitToSize=m_MCombo.GetFitToSize();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMComboDlg::OnPaint() 
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
HCURSOR CMComboDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void  CMComboDlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		{
		CUTSampleAboutDlg dlgAbout(IDR_MAINRFAME,ID_DESCRIPTION_FILE);
		dlgAbout.DoModal();
		}
	else
		{
		CDialog::OnSysCommand(nID, lParam);
		}
	}


void CMComboDlg::PostNcDestroy() 
{
	m_MCombo.Detach();
	CDialog::PostNcDestroy();
}

void CMComboDlg::OnButtonSetmastercolumn() 
{
	UpdateData(TRUE);
	if(!m_MCombo.SetMasterColumn(m_MasterColumn))
		AfxMessageBox(_T("Invalid Master Column"));
}

void CMComboDlg::OnButtonSetcolumnwidth() 
{
	UpdateData(TRUE);
	if(!m_MCombo.SetColumnWidth(m_ColWidth_ColNum,m_ColumnWidth))
		AfxMessageBox(_T("Invalid Column"));
}

void CMComboDlg::OnButtonSetcolcount() 
{
	UpdateData(TRUE);
	if(!m_MCombo.SetColumnCount(m_ColCount))
		AfxMessageBox(_T("Invalid Column Count"));
}

void CMComboDlg::OnButtonAdd() 
{
	UpdateData(TRUE);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_ADD); 
	int nLineCount = pEdit->GetLineCount();
	TCHAR* PtrArray[50];
	int nNumChar;
	int nIndex=0;
	for(nIndex=0; nIndex < nLineCount; nIndex++)
	{
		PtrArray[nIndex] = new TCHAR[200];
		nNumChar = pEdit->GetLine(nIndex,PtrArray[nIndex],199);
		(PtrArray[nIndex])[nNumChar] = '\0';
	}
	if(m_MCombo.AddString((LPCTSTR*)PtrArray,nLineCount)==CB_ERR)
		AfxMessageBox(_T("Add is not successfull"));
	for(nIndex=0; nIndex < nLineCount; nIndex++)
		delete PtrArray[nIndex];
}

void CMComboDlg::OnButtonInsertat() 
{
	UpdateData(TRUE);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_ADD); 
	int nLineCount = pEdit->GetLineCount();
	TCHAR* PtrArray[50];
	int nNumChar;
	int nIndex=0;
	for(nIndex=0; nIndex < nLineCount; nIndex++)
	{
		PtrArray[nIndex] = new TCHAR[200];
		nNumChar = pEdit->GetLine(nIndex,(LPTSTR)PtrArray[nIndex],200);
		(PtrArray[nIndex])[nNumChar] = '\0';
	}
	if(m_MCombo.InsertString(m_InsertAt_ColNum,(LPCTSTR*)PtrArray,nLineCount)==CB_ERR)
		AfxMessageBox(_T("insert is not successfull"));
	for(nIndex=0; nIndex < nLineCount; nIndex++)
		delete PtrArray[nIndex];

}

void CMComboDlg::OnButtonGetlbtext() 
{
	UpdateData(TRUE);
	m_MCombo.GetLBText(m_LBText_RowNum,m_LBText_ColNum,m_LBText);
	UpdateData(FALSE);
}


void CMComboDlg::OnButtonSelectstring() 
{
	UpdateData(TRUE);
	if(m_MCombo.SelectString(m_SelectStartAfter,m_SelectColNum,m_SelectString.GetBuffer(0)) == CB_ERR)
		AfxMessageBox(_T("select is not successfull"));
}

void CMComboDlg::OnButtonSetitemdata() 
{
	UpdateData(TRUE);
	if(m_MCombo.SetItemData(m_nItemDataIndex,m_dwItemData)==CB_ERR)
	{
		AfxMessageBox(_T("SetItemData is not successfull"));
		return;
	}
	UpdateData(FALSE);
}

void CMComboDlg::OnButtonGetitemdata() 
{
	UpdateData(TRUE);
	if((m_dwItemData = m_MCombo.GetItemData(m_nItemDataIndex))==CB_ERR)
	{
		AfxMessageBox(_T("GetItemDatais not successfull"));
		return;
	}
	UpdateData(FALSE);
	
}

void CMComboDlg::OnEditchangeCombo1() 
{
	// TODO: Add your control notification handler code here

	CString sText;
	m_MCombo.GetLBText(m_MCombo.GetCurSel(),1,sText);
}

void CMComboDlg::OnEditupdateCombo1() 
{
	// TODO: Add your control notification handler code here
	
	CString sText;
	m_MCombo.GetLBText(m_MCombo.GetCurSel(),1,sText);
}

void CMComboDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	
	CString sText;
	m_MCombo.GetLBText(m_MCombo.GetCurSel(),1,sText);
}

void CMComboDlg::OnCheckFittosize() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_MCombo.SetFitToSize(m_bFitToSize);
}
