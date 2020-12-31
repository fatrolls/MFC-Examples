// MaskedEditTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MaskedEditTest.h"     // CMaskedEditTestApp
#include "MaskedEditTestDlg.h"  // CMaskedEditTestDlg
#include "OXMaskedEdit.h"       // COXMaskedEdit

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__ ;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditTestDlg dialog

CMaskedEditTestDlg::CMaskedEditTestDlg(CWnd* pParent /*=NULL*/) : CDialog(CMaskedEditTestDlg::IDD, pParent)/*, 
	m_editMasked()*/
	{
	//{{AFX_DATA_INIT(CMaskedEditTestDlg)
	m_csPromptChar = _T("");
	m_bAutoTab = FALSE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon ( IDR_MAINFRAME ) ;
	}

void CMaskedEditTestDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX) ;
	//{{AFX_DATA_MAP(CMaskedEditTestDlg)
	DDX_Control (pDX, IDC_EDIT_TEST  , m_editMasked  ) ;
	DDX_Control (pDX, IDC_COMBO_MASKS, m_comboMasks  ) ;
	DDX_Text    (pDX, IDC_EDIT_PROMPT, m_csPromptChar) ;
	DDV_MaxChars(pDX, m_csPromptChar, 1) ;
	DDX_Check(pDX, IDC_CHECK_AUTOTAB, m_bAutoTab);
	//}}AFX_DATA_MAP
	}

BEGIN_MESSAGE_MAP(CMaskedEditTestDlg, CDialog)
	//{{AFX_MSG_MAP(CMaskedEditTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELENDOK  (IDC_COMBO_MASKS, OnSelendokMasks  )
	ON_CBN_EDITCHANGE(IDC_COMBO_MASKS, OnEditchangeMasks)
	ON_EN_CHANGE(IDC_EDIT_PROMPT, OnChangeEditPrompt)
	ON_BN_CLICKED(IDC_BUTTON_EMPTY, OnButtonEmpty)
	ON_BN_CLICKED(IDC_CHECK_AUTOTAB, OnCheckAutotab)
	//}}AFX_MSG_MAP
	ON_NOTIFY(OXMEN_VALIDATE,IDC_EDIT_TEST,OnValidateEditTest)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditTestDlg message handlers

BOOL CMaskedEditTestDlg::OnInitDialog()
	{
	m_csPromptChar = m_editMasked.GetPromptSymbol() ;
	m_bAutoTab=m_editMasked.GetAutoTab();
	
	CDialog::OnInitDialog() ;
	
	// Add "About..." menu item to system menu.

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

	m_comboMasks.AddString ( _T("Digit Test: ###-####") ) ;
	m_comboMasks.AddString ( _T("Decimal Test: ###.###.###.###") ) ;
	m_comboMasks.AddString ( _T("Thousands Test: ##,###.##") ) ;
	m_comboMasks.AddString ( _T("Time Test: ##:##") ) ;
	m_comboMasks.AddString ( _T("Date Test: ##/##/####") ) ;
	// Since the "C" programming language also uses the '\' as an escape character, 
	// you must use two in sequence to equal one switch for masking purposes. 
	m_comboMasks.AddString ( _T("\\Alphanumeric Test: AAAAAAAAAA\\, AAAAAAAA") ) ;
	m_comboMasks.AddString ( _T("\\Alphabetic Test: ????????????????") ) ;
	m_comboMasks.AddString ( _T("Uppercase Test: >>>>>>> ????????") ) ;
	m_comboMasks.AddString ( _T("Lowercase Test: <<<<<<< ????????") ) ;
	m_comboMasks.AddString ( _T("Phone:(###)###-#### Ext:####") ) ;
	m_comboMasks.AddString ( _T("AAA-#######")                  ) ;
	m_comboMasks.AddString ( _T("&####-##-## ##\\:##\\:##")     ) ;
	m_comboMasks.SetCurSel ( 0 ) ;
	OnSelendokMasks() ;
	return TRUE ;
	}

void CMaskedEditTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMaskedEditTestDlg::OnPaint() 
	{
	if ( IsIconic() )
		{
		CPaintDC dc ( this ) ;  // device context for painting
		
		SendMessage ( WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0 ) ;
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics ( SM_CXICON ) ;
		int cyIcon = GetSystemMetrics ( SM_CYICON ) ;
		
		CRect rect ;
		GetClientRect ( &rect ) ;
		int x = (rect.Width () - cxIcon + 1) / 2 ;
		int y = (rect.Height() - cyIcon + 1) / 2 ;
		
		// Draw the icon
		dc.DrawIcon ( x, y, m_hIcon ) ;
		}
	else
		{
		CDialog::OnPaint() ;
		}
	}

HCURSOR CMaskedEditTestDlg::OnQueryDragIcon()
	{
	return (HCURSOR) m_hIcon ;
	}

void CMaskedEditTestDlg::OnSelendokMasks()
	{
	TRACE(_T("CMaskedEditTestDlg::OnSelendokMasks()\n"));

	int nSelected = m_comboMasks.GetCurSel() ;
	if ( nSelected >= 0 )
		{
		CString csNewMask ;
		m_comboMasks.GetLBText ( nSelected, csNewMask ) ;
		m_editMasked.SetMask   ( csNewMask ) ;
		}
	}

void CMaskedEditTestDlg::OnEditchangeMasks() 
	{
	TRACE(_T("CMaskedEditTestDlg::OnEditchangeMasks()\n"));
	
	CString csNewMask ;
	m_comboMasks.GetWindowText ( csNewMask ) ;
	m_editMasked.SetMask       ( csNewMask ) ;
	}

void CMaskedEditTestDlg::OnChangeEditPrompt() 
	{
	TRACE(_T("CMaskedEditTestDlg::OnChangeEditPrompt()\n"));
	
	UpdateData ( TRUE ) ;
	if ( m_csPromptChar.GetLength() == 1 )
		m_editMasked.SetPromptSymbol ( m_csPromptChar[0] ) ;
	}

void CMaskedEditTestDlg::OnButtonEmpty() 
{
	// TODO: Add your control notification handler code here
	m_editMasked.EmptyData(TRUE);
	UpdateData ( FALSE ) ;
}

void CMaskedEditTestDlg::OnCheckAutotab() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_editMasked.SetAutoTab(m_bAutoTab);
}

void CMaskedEditTestDlg::OnValidateEditTest(NMHDR * pNotifyStruct, LRESULT * result)
{
	LPMENMHDR pMENotifyStruct = (LPMENMHDR)pNotifyStruct;

	UpdateData();

	CString sText=m_editMasked.GetInputData();

	// just as an example: if user typed "345" then typed information is invalid,
	// cursor will be set before first found "345" symbol
	int nPos=sText.Find(_T("345"));
	if(nPos!=-1)
	{
		pMENotifyStruct->bValid=FALSE;
		pMENotifyStruct->nPosition=m_editMasked.LPtoRP(nPos);
	}
	else
	{
		pMENotifyStruct->bValid=TRUE;
		pMENotifyStruct->bDefaultValidation=TRUE;
	}

	*result=0;
}

