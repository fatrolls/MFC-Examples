// VBScriptEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CVBScriptEditDlg.h"
#include "VBScriptEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCVBScriptEditDlg dialog

CCVBScriptEditDlg::CCVBScriptEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCVBScriptEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCVBScriptEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCVBScriptEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCVBScriptEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCVBScriptEditDlg, CDialog)
	//{{AFX_MSG_MAP(CCVBScriptEditDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCVBScriptEditDlg message handlers

// TWSCRIPTEDIT	->
static LPCTSTR szKeywords = " Call Const Dim Do Loop Erase Exit For To Step Next "
"Each Function If Then Else On Error Resume Option Explicit Private Public Randomize "
"ReDim Rem Select Case Set Sub End While Wend "
"And Eqv Imp Is Mod Not Or Xor ";

static LPCTSTR szConstants = " Empty False True Nothing Null "
"vbBlack vbRed vbGreen vbYellow vbBlue vbMagenta vbCyan vbWhite "
"vbBinaryCompare vbTextCompare vbDatabaseCompare "
"vbGeneralDate vbLongDate vbShortDate vbLongTime vbShortTime "
"vbSunday vbMonday vbTuesday vbWednesday vbThursday vbFriday vbSaturday "
"vbFirstJan1 vbFirstFourDays vbFirstFullWeek vbUseSystem vbUseSystemDayOfWeek "
"vbObjectError vbOKOnly vbOKCancel vbAbortRetryIgnore vbYesNoCancel vbYesNo "
"vbRetryCancel vbCritical vbQuestion vbExclamation vbInformation "
"vbDefaultButton1 vbDefaultButton2 vbDefaultButton3 vbDefaultButton4 "
"vbApplicationModal vbSystemModal "
"vbCr vbCrLf vbFormFeed vbLf vbNewLine vbNullChar vbNullString vbTab vbVerticalTab "
"vbEmpty vbNull vbInteger vbLong vbSingle vbDouble vbCurrency vbDate vbString "
"vbObject vbError vbBoolean vbVariant vbDataObject vbDecimal vbByte vbArray ";
// <- TWSCRIPTEDIT	

BOOL CCVBScriptEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

// TWSCRIPTEDIT	->
	ModifyStyle(0, WS_CLIPCHILDREN);

	m_wndScriptEdit.SubclassDlgItem(IDC_RICHEDIT1, this);
	m_wndScriptEdit.Initialize();

	m_wndScriptEdit.SetCaseSensitive(FALSE);
	m_wndScriptEdit.SetStringQuotes(_T("\""));
	m_wndScriptEdit.SetSLComment(_T('\''));
	m_wndScriptEdit.SetSLComment(_T("rem"));

	m_wndScriptEdit.AddKeywords(szKeywords);
	m_wndScriptEdit.AddConstants(szConstants);
// <- TWSCRIPTEDIT	
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCVBScriptEditDlg::OnPaint() 
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
HCURSOR CCVBScriptEditDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
