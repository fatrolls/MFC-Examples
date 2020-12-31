// XMsgBoxTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMsgBoxTest.h"
#include "XMsgBoxTestDlg.h"
#include "about.h"
#include "XTrace.h"
#include "gallery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable : 4996)		// disable bogus deprecation warning

BEGIN_MESSAGE_MAP(CXMsgBoxTestDlg, CDialog)
	//{{AFX_MSG_MAP(CXMsgBoxTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST_WINDOWS_MSGBOX, OnWindowsMessageBox)
	ON_BN_CLICKED(IDC_TEST_XMSGBOX, OnXMessageBox)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_ONLINE_HELP, OnOnlineHelp)
	ON_BN_CLICKED(IDC_GALLERY, OnGallery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// CXMsgBoxTestDlg ctor

CXMsgBoxTestDlg::CXMsgBoxTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXMsgBoxTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMsgBoxTestDlg)
	m_nDefButton = -1;
	m_nIcon = -1;
	m_nString = -1;
	m_nButton = -1;
	m_nDontAsk = -1;
	m_nLanguage = -1;
	m_nTimeout = 0;
	m_nDisabled = 0;
	m_strHelpContextId = _T("0");
	m_bVistaStyle = FALSE;
	m_bNarrow = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_lpReportFunc = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

///////////////////////////////////////////////////////////////////////////////
// DoDataExchange 
void CXMsgBoxTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMsgBoxTestDlg)
	DDX_Control(pDX, IDC_LANGUAGE1,        m_radLanguage);
	DDX_Control(pDX, IDC_NO_SOUND,         m_chkNoSound);
	DDX_Control(pDX, IDC_RIGHT_JUSTIFY,    m_chkRightJustify);
	DDX_Control(pDX, IDC_CUSTOM_BUTTONS,   m_chkCustomButtons);
	DDX_Control(pDX, IDC_CUSTOM_ICON,      m_chkCustomIcon);
	DDX_Control(pDX, IDC_INCLUDE_REPORT,   m_chkReport);
	DDX_Control(pDX, IDC_INCLUDE_YESTOALL, m_chkYesToAll);
	DDX_Control(pDX, IDC_INCLUDE_NOTOALL,  m_chkNoToAll);
	DDX_Control(pDX, IDC_INCLUDE_HELP,     m_chkHelp);
	DDX_Control(pDX, IDC_DONTASK1,         m_radDontAsk);
	DDX_Control(pDX, IDC_BUTTON1,          m_radButton);
	DDX_Control(pDX, IDC_RESULT,           m_stcResult);
	DDX_Control(pDX, IDC_STRING1,          m_radString);
	DDX_Control(pDX, IDC_ICON1,            m_radIcon);
	DDX_Control(pDX, IDC_DEFBUTTON1,       m_radDefButton);
	DDX_Radio(pDX,   IDC_DEFBUTTON1,       m_nDefButton);
	DDX_Radio(pDX,   IDC_ICON1,            m_nIcon);
	DDX_Radio(pDX,   IDC_STRING1,          m_nString);
	DDX_Radio(pDX,   IDC_BUTTON1,          m_nButton);
	DDX_Radio(pDX,   IDC_DONTASK1,         m_nDontAsk);
	DDX_Radio(pDX,   IDC_LANGUAGE1,        m_nLanguage);
	DDX_Text(pDX,    IDC_TIMEOUT_EDIT,     m_nTimeout);
	DDV_MinMaxInt(pDX, m_nTimeout, 0, 999);
	DDX_Text(pDX,    IDC_DISABLED_EDIT,    m_nDisabled);
	DDV_MinMaxInt(pDX, m_nDisabled, 0, 999);
	DDX_Text(pDX,    IDC_HELP_CONTEXT_ID,  m_strHelpContextId);
	DDX_Check(pDX,   IDC_VISTA,            m_bVistaStyle);
	DDX_Check(pDX, IDC_NARROW,             m_bNarrow);
	//}}AFX_DATA_MAP
}

///////////////////////////////////////////////////////////////////////////////
// OnInitDialog
BOOL CXMsgBoxTestDlg::OnInitDialog()
{
	TRACE(_T("in CXMsgBoxTestDlg::OnInitDialog\n"));

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

	m_radDefButton.SetCheck(1);
	m_radIcon.SetCheck(1);
	m_radString.SetCheck(1);
	m_radButton.SetCheck(1);
	m_radDontAsk.SetCheck(1);
	m_radLanguage.SetCheck(1);
	m_chkYesToAll.SetCheck(0);
	m_chkNoToAll.SetCheck(0);
	m_chkHelp.SetCheck(0);
	m_chkNoSound.SetCheck(0);
	m_chkReport.SetCheck(0);
	m_chkCustomButtons.SetCheck(0);
	m_chkCustomIcon.SetCheck(0);
	m_chkRightJustify.SetCheck(0);

	m_nIcon = 0;
	m_nString = 0;

	CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_TIMEOUT_SPIN);
	ASSERT(pSpin);
	pSpin->SetRange(0, 999);

	CEdit* pEdit = (CEdit*) GetDlgItem(IDC_TIMEOUT_EDIT);
	ASSERT(pEdit);
	pEdit->LimitText(3);

	pSpin = (CSpinButtonCtrl*) GetDlgItem(IDC_DISABLED_SPIN);
	ASSERT(pSpin);
	pSpin->SetRange(0, 999);

	pEdit = (CEdit*) GetDlgItem(IDC_DISABLED_EDIT);
	ASSERT(pEdit);
	pEdit->LimitText(3);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

///////////////////////////////////////////////////////////////////////////////
// OnSysCommand 
void CXMsgBoxTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlg;
		dlg.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

///////////////////////////////////////////////////////////////////////////////
// OnPaint 
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CXMsgBoxTestDlg::OnPaint() 
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

///////////////////////////////////////////////////////////////////////////////
// OnQueryDragIcon 
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXMsgBoxTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

///////////////////////////////////////////////////////////////////////////////
// DisplayResult 
void CXMsgBoxTestDlg::DisplayResult(int nResult, BOOL bReadFromRegistry)
{
	CString str = _T("");

	int rc = nResult & 0xFF;

	switch (rc)
	{
		case IDABORT:		str = _T("IDABORT"); break;
		case IDCANCEL:		str = _T("IDCANCEL"); break;
		case IDCONTINUE:	str = _T("IDCONTINUE"); break;
		case IDCUSTOM1:		str = _T("IDCUSTOM1"); break;
		case IDCUSTOM2:		str = _T("IDCUSTOM2"); break;
		case IDCUSTOM3:		str = _T("IDCUSTOM3"); break;
		case IDCUSTOM4:		str = _T("IDCUSTOM4"); break;
		case IDIGNORE:		str = _T("IDIGNORE"); break;
		case IDIGNOREALL:	str = _T("IDIGNOREALL"); break;
		case IDNO:			str = _T("IDNO"); break;
		case IDNOTOALL:		str = _T("IDNOTOALL"); break;
		case IDOK:			str = _T("IDOK"); break;
		case IDRETRY:		str = _T("IDRETRY"); break;
		case IDSKIP:		str = _T("IDSKIP"); break;
		case IDSKIPALL:		str = _T("IDSKIPALL"); break;
		case IDTRYAGAIN:	str = _T("IDTRYAGAIN"); break;
		case IDYES:			str = _T("IDYES"); break;
		case IDYESTOALL:	str = _T("IDYESTOALL"); break;
		default:			str.Format(_T("Unknown result:  %d"), nResult); break;
	}

	if (nResult & MB_DONOTASKAGAIN)
		str += _T(" + MB_DONOTASKAGAIN");

	if (nResult & MB_DONOTSHOWAGAIN)
		str += _T(" + MB_DONOTSHOWAGAIN");

	if (nResult & MB_DONOTTELLAGAIN)
		str += _T(" + MB_DONOTTELLAGAIN");

	if (nResult & MB_TIMEOUT)
		str += _T(" + MB_TIMEOUT");

	if (bReadFromRegistry)
		str += _T("  (read from registry)");

	CString s = _T(" ");
	s += str;
	m_stcResult.SetWindowText(s);
}

static void ReportFunc(LPCTSTR lpszMessage, DWORD dwUserData)
{
	CString str;
	str.Format(_T("This message is being reported:\r\n'%s'\r\nUser data = %d")
			   _T("\r\n\r\nIdea:  Your implementation of the ReportFunc could") 
			   _T("\r\nemail the message to the IT department."), 
			   lpszMessage, dwUserData);
	::MessageBox(NULL, str, _T("ReportFunc"), MB_OK);
}


///////////////////////////////////////////////////////////////////////////////
// GetOptions 
BOOL CXMsgBoxTestDlg::GetOptions(CString& strText,
								 UINT *pnButton,
								 UINT *pnDefButton,
								 UINT *pnIconType,
								 UINT *pnDontAsk,
								 UINT *pnHelpId,
								 CString& strCustomButtons,
								 int  *pnTimeout,
								 int  *pnDisabled,
								 UINT * pnIdIcon)
{
	UpdateData(TRUE);

	strCustomButtons = _T("");

	if (pnHelpId)
		*pnHelpId = _ttoi(m_strHelpContextId);

	if (m_chkCustomButtons.GetCheck())
	{
		// the maximum no. of custom buttons is 4
		strCustomButtons = _T("Custom 1\nCustom 2\nCustom 3\nCustom 4\nCustom5");
		*pnButton = 0;
	}
	else
	{
		switch (m_nButton)
		{
			case 0:		*pnButton = MB_OK; break;
			case 1:		*pnButton = MB_OKCANCEL; break;
			case 2:		*pnButton = MB_YESNO; break;
			case 3:		*pnButton = MB_YESNOCANCEL; break;
			case 4:		*pnButton = MB_ABORTRETRYIGNORE; break;
			case 5:		*pnButton = MB_RETRYCANCEL; break;
			case 6:		*pnButton = MB_CANCELTRYCONTINUE; break;
			case 7:		*pnButton = MB_CONTINUEABORT; break;
			case 8:		*pnButton = MB_SKIPSKIPALLCANCEL; break;
			case 9:		*pnButton = MB_IGNOREIGNOREALLCANCEL; break;
			default:	ASSERT(FALSE); return FALSE;
		}

		if (m_chkYesToAll.GetCheck())
			*pnButton |= MB_YESTOALL;

		if (m_chkNoToAll.GetCheck())
			*pnButton |= MB_NOTOALL;
	}

	switch (m_nLanguage)
	{
		case 0:		*pnButton |= MB_NORESOURCE; break;	// English
		case 1:		break;								// French
		default:	ASSERT(FALSE); return FALSE;
	}

	if (m_chkHelp.GetCheck())
		*pnButton |= MB_HELP;

	if (m_chkNoSound.GetCheck())
		*pnButton |= MB_NOSOUND;

	m_lpReportFunc = NULL;
	if (m_chkReport.GetCheck())
		m_lpReportFunc = ReportFunc;

	m_bRightJustify = m_chkRightJustify.GetCheck();

	*pnIconType = 0;
	*pnIdIcon = 0;

	if (m_chkCustomIcon.GetCheck())
	{
		//*pnIdIcon = IDR_MAINFRAME;
		*pnIdIcon = IDI_BOB;	//+++1.5
	}

	switch (m_nIcon)
	{
		case 0:		*pnIconType = 0; break;
		case 1:		*pnIconType = MB_ICONEXCLAMATION; break;
		case 2:		*pnIconType = MB_ICONINFORMATION; break;
		case 3:		*pnIconType = MB_ICONQUESTION; break;
		case 4:		*pnIconType = MB_ICONSTOP; break;
		default:	ASSERT(FALSE); return FALSE;
	}

	switch (m_nDefButton)
	{
		case 0:		*pnDefButton = 0; break;
		case 1:		*pnDefButton = MB_DEFBUTTON1; break;
		case 2:		*pnDefButton = MB_DEFBUTTON2; break;
		case 3:		*pnDefButton = MB_DEFBUTTON3; break;
		case 4:		*pnDefButton = MB_DEFBUTTON4; break;
		case 5:		*pnDefButton = MB_DEFBUTTON5; break;
		case 6:		*pnDefButton = MB_DEFBUTTON6; break;
		default:	ASSERT(FALSE); return FALSE;
	}

	switch (m_nDontAsk)
	{
		case 0:		*pnDontAsk = 0; break;
		case 1:		*pnDontAsk = MB_DONOTASKAGAIN; break;
		case 2:		*pnDontAsk = MB_DONOTTELLAGAIN; break;
		case 3:		*pnDontAsk = MB_DONOTSHOWAGAIN; break;
		default:	ASSERT(FALSE); return FALSE;
	}

	switch (m_nString)
	{
		case 0:		strText = _T("Resistance is futile"); break;
		case 1:		strText = _T("I know what you're thinking. ")
							  _T("Did he fire six shots or only five?"); break;
		case 2:		strText = _T("It can't be bargained with. ")
							  _T("It can't be reasoned with. ")
							  _T("It doesn't feel pity, or remorse, or fear. "); break;
		case 3:		strText = _T("It can't be bargained with. ")
							  _T("It can't be reasoned with. ")
							  _T("It doesn't feel pity, or remorse, or fear. ")
							  _T("And it absolutely will not stop, ever, until you are dead."); break;
		case 4:		strText = _T("Whose woods these are I think I know.\n")
							  _T("His house is in the village though;\n")
							  _T("He will not see me stopping here\n")
							  _T("To watch his woods fill up with snow.\n\n")
							  _T("My little horse must think it queer\n")
							  _T("To stop without a farmhouse near\n")
							  _T("Between the woods and frozen lake\n")
							  _T("The darkest evening of the year.\n\n")
							  _T("He gives his harness bells a shake\n")
							  _T("To ask if there is some mistake.\n")
							  _T("The only other sound's the sweep\n")
							  _T("Of easy wind and downy flake.\n\n")
							  _T("The woods are lovely, dark and deep,\n")
							  _T("But I have promises to keep,\n")
							  _T("And miles to go before I sleep,\n")
							  _T("And miles to go before I sleep."); break;
		default:	ASSERT(FALSE); return FALSE;
	}

	CString strTimeout;
	GetDlgItem(IDC_TIMEOUT_EDIT)->GetWindowText(strTimeout);
	*pnTimeout = _ttoi(strTimeout);

	CString strDisabled;
	GetDlgItem(IDC_DISABLED_EDIT)->GetWindowText(strDisabled);
	*pnDisabled = _ttoi(strDisabled);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// OnWindowsMessageBox 
void CXMsgBoxTestDlg::OnWindowsMessageBox() 
{
	m_stcResult.SetWindowText(_T(""));

	CString strText, strCustomButtons;
	strText.Empty();
	UINT nButton, nDefButton, nIconType, nDontAsk;
	int nTimeout = 0;
	int nDisabled = 0;
	UINT nIdIcon = 0;

	GetOptions(strText, &nButton, &nDefButton, &nIconType, &nDontAsk, NULL, 
		strCustomButtons, &nTimeout, &nDisabled, &nIdIcon);

	if ((nButton & MB_TYPEMASK) == MB_CONTINUEABORT)
	{
		AfxMessageBox(_T("MB_CONTINUEABORT is not supported by the Windows\n")
					  _T("MessageBox API.  Please make another selection"));
		return;
	}

	if ((nButton & MB_TYPEMASK) == MB_SKIPSKIPALLCANCEL)
	{
		AfxMessageBox(_T("MB_SKIPSKIPALLCANCEL is not supported by the Windows\n")
					  _T("MessageBox API.  Please make another selection"));
		return;
	}

	if ((nButton & MB_TYPEMASK) == MB_IGNOREIGNOREALLCANCEL)
	{
		AfxMessageBox(_T("MB_IGNOREIGNOREALLCANCEL is not supported by the Windows\n")
					  _T("MessageBox API.  Please make another selection"));
		return;
	}

	int rc = ::MessageBox(m_hWnd, strText, _T("MessageBox"), 
					nDefButton | nButton | nIconType);

	DisplayResult(rc, FALSE);
}


///////////////////////////////////////////////////////////////////////////////
// OnXMessageBox 
void CXMsgBoxTestDlg::OnXMessageBox()
{
	m_stcResult.SetWindowText(_T(""));

	CString strText, strCustomButtons;
	strText.Empty();
	UINT nButton, nDefButton, nIconType, nDontAsk, nHelpContextId;
	int nTimeout = 0;
	int nDisabled = 0;
	UINT nIdIcon = 0;

	GetOptions(strText, &nButton, &nDefButton, &nIconType, &nDontAsk, 
		&nHelpContextId, strCustomButtons, &nTimeout, &nDisabled, &nIdIcon);

	if ((nButton & MB_NOTOALL) || (nButton & MB_YESTOALL))
	{
		if (((nButton & MB_TYPEMASK) != MB_YESNO) && ((nButton & MB_TYPEMASK) != MB_YESNOCANCEL))
		{
			AfxMessageBox(_T("MB_YESTOALL and MB_NOTOALL can only be\n")
						  _T("used with MB_YESNO or MB_YESNOCANCEL"));
			return;
		}
	}

	int rc = 0;

	XMSGBOXPARAMS xmb;
	xmb.nTimeoutSeconds  = nTimeout;
	xmb.nDisabledSeconds = nDisabled;
	xmb.nIdIcon          = nIdIcon;
	xmb.dwReportUserData = 1234;
	xmb.nIdHelp          = nHelpContextId;
	xmb.lpReportFunc     = m_lpReportFunc;
	xmb.lpszModule       = _T(__FILE__);
	xmb.nLine            = 12345;
	_tcscpy(xmb.szCompanyName, _T("CodeProject"));

	_tcscpy(xmb.szReportButtonCaption, _T("Notify IT"));
	if (!strCustomButtons.IsEmpty())
		_tcscpy(xmb.szCustomButtons, strCustomButtons);

	///////////////////////////////////////////////////////////////////////////
	//
	// uncomment following two lines to display XMessageBox at (50, 20):
	//
	//xmb.x = 50;
	//xmb.y = 20;

	if (m_bRightJustify)
		xmb.dwOptions |= XMSGBOXPARAMS::RightJustifyButtons;
	if (m_bVistaStyle)
		xmb.dwOptions |= XMSGBOXPARAMS::VistaStyle;
	if (m_bNarrow)
		xmb.dwOptions |= XMSGBOXPARAMS::Narrow;

	// note that message box will always be displayed *unless* one of 
	// the checkboxes is specified, *and* value is in registry
	BOOL bReadFromRegistry = (BOOL) XMessageBoxGetCheckBox(xmb) && nDontAsk;

	//rc = ::XMessageBox(m_hWnd, strText, MAKEINTRESOURCE(IDS_CAPTION),
	rc = ::XMessageBox(m_hWnd, strText, _T("XMessageBox"), 
					nDefButton | nButton | nIconType | nDontAsk, &xmb);

	DisplayResult(rc, bReadFromRegistry);
}

///////////////////////////////////////////////////////////////////////////////
// OnCtlColor 
HBRUSH CXMsgBoxTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	DWORD dwStyle;
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		dwStyle = ::GetWindowLong(pWnd->m_hWnd, GWL_STYLE);
		if (((dwStyle & 0x00001FFF) == SS_CENTER) ||
			((dwStyle & 0x00001FFF) == BS_GROUPBOX))
			pDC->SetTextColor(RGB(0, 0, 255));
	}
	return hbr;
}

///////////////////////////////////////////////////////////////////////////////
// OnOnlineHelp 
void CXMsgBoxTestDlg::OnOnlineHelp() 
{
	CString strHelp = _T("");
	VERIFY(strHelp.LoadString(IDS_ONLINE_HELP));
	CXHyperLink::GotoURL(strHelp, SW_SHOW, TRUE);	
}

///////////////////////////////////////////////////////////////////////////////
// OnGallery 
void CXMsgBoxTestDlg::OnGallery() 
{
	CGallery dlg;
	dlg.DoModal();
}
