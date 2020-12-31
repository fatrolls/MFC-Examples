// Gallery.cpp : implementation file
//

#include "stdafx.h"
#include "xmsgboxtest.h"
#include "Gallery.h"
#include "XMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable : 4996)		// disable bogus deprecation warning


//=============================================================================
BEGIN_MESSAGE_MAP(CGallery, CDialog)
//=============================================================================
	//{{AFX_MSG_MAP(CGallery)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//=============================================================================
CGallery::CGallery(CWnd* pParent /*=NULL*/)
	: CDialog(CGallery::IDD, pParent)
//=============================================================================
{
	//{{AFX_DATA_INIT(CGallery)
	//}}AFX_DATA_INIT
}

//=============================================================================
CGallery::~CGallery()
//=============================================================================
{
	if (m_font.GetSafeHandle())
		m_font.DeleteObject();
}

//=============================================================================
void CGallery::DoDataExchange(CDataExchange* pDX)
//=============================================================================
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGallery)
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}

//=============================================================================
BOOL CGallery::OnInitDialog() 
//=============================================================================
{
	CDialog::OnInitDialog();
	
	CFont *pFont = m_Edit.GetFont();
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	_tcscpy(lf.lfFaceName, _T("Courier New"));
	m_font.CreateFontIndirect(&lf);
	m_Edit.SetFont(&m_font, FALSE);
	m_Edit.SetMargins(5, 5);
	m_Edit.SetTabStops(10);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//=============================================================================
void CGallery::OnButton1() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMSGBOXPARAMS xmb;\r\n")
		_T("	_tcscpy(xmb.szCustomButtons, _T(\"Copy Log to Clipboard\\nOK\")); \r\n")
		_T("	int rc = XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"Captain! We have been hit! Shields are at 10%.\"),\r\n")
		_T("		_T(\"Example 1\"), \r\n")
		_T("		MB_DEFBUTTON2, &xmb);\r\n")
		_T("\r\n")
		_T("	if ((rc & 0xFF) == IDCUSTOM1) \r\n")
		_T("	{ \r\n")
		_T("		TRACE(_T(\"Copy Log to Clipboard\\n\")); \r\n")
		_T("	} \r\n")
		_T("	                                                                                                                                         \r\n")
	);

	XMSGBOXPARAMS xmb;
	_tcscpy(xmb.szCustomButtons, _T("Copy Log to Clipboard\nOK"));
	int rc = XMessageBox(m_hWnd, 
		_T("Captain! We have been hit! Shields are at 10%."),
		_T("Example 1"), 
		MB_DEFBUTTON2, &xmb);

	if ((rc & 0xFF) == IDCUSTOM1)
	{
		TRACE(_T("Copy Log to Clipboard\n"));
	}
}

//=============================================================================
void CGallery::OnButton2() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMSGBOXPARAMS xmb;\r\n")
		_T("	xmb.nIdIcon = IDI_BOB;\r\n")
		_T("	xmb.crBackground = RGB(255,153,0);\r\n")
		_T("	xmb.crText = RGB(0,102,0);\r\n")
		_T("	XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"The truth is out there.\"),\r\n")
		_T("		_T(\"Example 2\"), \r\n")
		_T("		MB_OK, &xmb); \r\n")
	);

	XMSGBOXPARAMS xmb;
	xmb.nIdIcon = IDI_BOB;
	xmb.crBackground = RGB(255,153,0);
	xmb.crText = RGB(0,102,0);
	XMessageBox(m_hWnd, 
#if 0  // -----------------------------------------------------------
		_T("It can't be bargained with. ")
		_T("It can't be reasoned with. ")
		_T("It can't be reasoned with. ")
		_T("It can't be reasoned with. ")
		_T("It can't be reasoned with. ")
		_T("It can't be reasoned with. ")
		_T("It can't be reasoned with. ")
		_T("It doesn't feel pity, or remorse, or fear. "),
#endif // -----------------------------------------------------------
		_T("The truth is out there."),
		_T("Example 2"),
		MB_OK, &xmb);
}

//=============================================================================
void CGallery::OnButton3() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"The program has encountered an error.\"),\r\n")
		_T("		_T(\"Example 3\"), \r\n")
		_T("		MB_ICONSTOP | MB_HELP | MB_NORESOURCE | MB_OK); \r\n")
	);

	XMessageBox(m_hWnd, 
		_T("The program has encountered an error."),
		_T("Example 3"),
		MB_ICONSTOP | MB_HELP | MB_NORESOURCE | MB_OK);
}

//=============================================================================
void CGallery::OnButton4() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMSGBOXPARAMS xmb;\r\n")
		_T("	_tcscpy(xmb.szCustomButtons, _T(\"OK\\nHelp\"));\r\n")
		_T("	int rc = XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"The program has encountered an error.\"),\r\n")
		_T("		_T(\"Example 4\"), MB_ICONSTOP, &xmb); \r\n")
		_T("\r\n")
		_T("	if ((rc & 0xFF) == IDCUSTOM1) \r\n")
		_T("	{ \r\n")
		_T("		TRACE(_T(\"OK button\\n\")); \r\n")
		_T("	} \r\n")
		_T("	if ((rc & 0xFF) == IDCUSTOM2) \r\n")
		_T("	{ \r\n")
		_T("		TRACE(_T(\"Help button\\n\")); \r\n")
		_T("	} \r\n")
	);

	XMSGBOXPARAMS xmb;
	_tcscpy(xmb.szCustomButtons, _T("OK\nHelp"));
	int rc = XMessageBox(m_hWnd, 
		_T("The program has encountered an error."),
		_T("Example 4"), MB_ICONSTOP, &xmb);

	if ((rc & 0xFF) == IDCUSTOM1)
	{
		TRACE(_T("OK button\n"));
	}
	if ((rc & 0xFF) == IDCUSTOM2)
	{
		TRACE(_T("Help button\n"));
	}
}

//=============================================================================
void CGallery::OnButton5() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	int rc = XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"Captain! We have been hit! Shields are at 10%.\"),\r\n")
		_T("		_T(\"Example 5\"), \r\n")
		_T("		MB_OK | MB_DONOTTELLAGAIN | MB_ICONINFORMATION | MB_NORESOURCE); \r\n")
		_T("\r\n")
		_T("	if (rc & MB_DONOTTELLAGAIN) \r\n")
		_T("	{ \r\n")
		_T("		TRACE(_T(\"MB_DONOTTELLAGAIN\\n\")); \r\n")
		_T("	} \r\n")
		_T("	                                                                                                                                         \r\n")
	);

	int rc = XMessageBox(m_hWnd, 
		_T("Captain! We have been hit! Shields are at 10%."),
		_T("Example 5"), 
		MB_OK | MB_DONOTTELLAGAIN | MB_ICONINFORMATION | MB_NORESOURCE);

	if (rc & MB_DONOTTELLAGAIN)
	{
		TRACE(_T("MB_DONOTTELLAGAIN\n"));
	}
}

static void ReportFunc(LPCTSTR lpszMessage, DWORD dwUserData)
{
	TRACE(_T("in ReportFunc\n"));

	CString str;
	str.Format(_T("This message is being reported:\r\n'%s'\r\nUser data = %d"),
			   lpszMessage, dwUserData);
	::MessageBox(NULL, str, _T("ReportFunc"), MB_OK);
}

//=============================================================================
void CGallery::OnButton6() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMSGBOXPARAMS xmb;\r\n")
		_T("	xmb.lpReportFunc = ReportFunc; \r\n")
		_T("	xmb.dwReportUserData = 1234; \r\n")
		_T("	_tcscpy(xmb.szReportButtonCaption, _T(\"Report Problem\")); \r\n")
		_T("	XMessageBox(m_hWnd, \r\n")
		_T("		MAKEINTRESOURCE(IDS_PROBLEM),\r\n")
		_T("		_T(\"Example 6\"), MB_OK | MB_ICONEXCLAMATION, &xmb); \r\n")
	);

	XMSGBOXPARAMS xmb;
	xmb.lpReportFunc = ReportFunc;
	xmb.dwReportUserData = 1234;
	_tcscpy(xmb.szReportButtonCaption, _T("Report Problem"));
	XMessageBox(m_hWnd, 
		MAKEINTRESOURCE(IDS_PROBLEM),
		_T("Example 6"), MB_OK | MB_ICONEXCLAMATION, &xmb);
}

//=============================================================================
void CGallery::OnButton7() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMSGBOXPARAMS xmb;\r\n")
		_T("	xmb.nTimeoutSeconds = 5; \r\n")
		_T("	XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"15 shopping days left!\"),\r\n")
		_T("		_T(\"Example 7\"), MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION | MB_NORESOURCE, &xmb); \r\n")
		_T("	                                                                                                                                         \r\n")
	);

	XMSGBOXPARAMS xmb;
	xmb.nTimeoutSeconds = 5;
	XMessageBox(m_hWnd, 
		_T("15 shopping days left!"),
		_T("Example 7"), MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION | MB_NORESOURCE, &xmb);
}

//=============================================================================
void CGallery::OnButton8() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMSGBOXPARAMS xmb;\r\n")
		_T("	xmb.nIdIcon = IDI_UAC_SHIELD;\r\n")
		_T("	_tcscpy(xmb.szCustomButtons, _T(\"OK\\nSelf Destruct\"));\r\n")
		_T("	xmb.nTimeoutSeconds = 10; \r\n")
		_T("	xmb.crBackground = RGB(255,255,255); \r\n")
		_T("	xmb.crText = RGB(255,0,0); \r\n")
		_T("	int rc = XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"Captain! Shields are down! The Borg are boarding!\"),\r\n")
		_T("		_T(\"Example 8\"), \r\n")
		_T("		MB_DEFBUTTON2, // causes timeout to display on 2nd button \r\n")
		_T("		&xmb);\r\n")
		_T("\r\n")
		_T("	if ((rc & 0xFF) == IDCUSTOM2) \r\n")
		_T("	{ \r\n")
		_T("		TRACE(_T(\"Self Destruct\\n\")); \r\n")
		_T("	} \r\n")
		_T("	                                                                                                                                         \r\n")
	);

	XMSGBOXPARAMS xmb;
	xmb.nIdIcon = IDI_UAC_SHIELD;
	_tcscpy(xmb.szCustomButtons, _T("OK\nSelf Destruct"));
	xmb.nTimeoutSeconds = 10;
	xmb.crBackground = RGB(255,255,255);
	xmb.crText = RGB(255,0,0);
	int rc = XMessageBox(m_hWnd, 
		_T("Captain! Shields are down! The Borg are boarding!"),
		_T("Example 8"), 
		MB_DEFBUTTON2, // causes timeout to display on 2nd button
		&xmb);	

	if ((rc & 0xFF) == IDCUSTOM2)
	{
		TRACE(_T("Self Destruct\n"));
	}
}

//=============================================================================
void CGallery::OnButton9() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMSGBOXPARAMS xmb;\r\n")
		_T("	xmb.dwOptions |= XMSGBOXPARAMS::RightJustifyButtons; \r\n")
		_T("	XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"The sky is a lovely cerulean blue. Oh, and the button is right-justified.\"), \r\n")
		_T("		_T(\"Example 9\"), MB_OK | MB_NORESOURCE, &xmb); \r\n")
		_T("	                                                                                                                                         \r\n")
	);

	XMSGBOXPARAMS xmb;
	xmb.dwOptions |= XMSGBOXPARAMS::RightJustifyButtons;
	XMessageBox(m_hWnd, 
		_T("The sky is a lovely cerulean blue. Oh, and the button is right-justified."),
		_T("Example 9"), MB_OK | MB_NORESOURCE, &xmb);
}

//=============================================================================
void CGallery::OnButton10() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMSGBOXPARAMS xmb;\r\n")
		_T("	xmb.dwOptions |= XMSGBOXPARAMS::VistaStyle; \r\n")
		_T("	xmb.bUseUserDefinedButtonCaptions = TRUE; \r\n")
		_T("	_tcscpy(xmb.UserDefinedButtonCaptions.szYes, _T(\"Save\")); \r\n")
		_T("	_tcscpy(xmb.UserDefinedButtonCaptions.szNo, _T(\"Don't Save\")); \r\n")
		_T("	XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"Do you want to save changes to Untitled?\"), \r\n")
		_T("		_T(\"Example 10\"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_NORESOURCE, &xmb); \r\n")
		_T("	                                                                                                                                         \r\n")
	);

	XMSGBOXPARAMS xmb;
	xmb.dwOptions |= XMSGBOXPARAMS::VistaStyle;
	xmb.bUseUserDefinedButtonCaptions = TRUE;
	_tcscpy(xmb.UserDefinedButtonCaptions.szYes, _T("Save"));
	_tcscpy(xmb.UserDefinedButtonCaptions.szNo, _T("Don't Save"));
	XMessageBox(m_hWnd, 
		_T("Do you want to save changes to Untitled?"),
		_T("Example 10"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_NORESOURCE, &xmb);
}

//=============================================================================
void CGallery::OnButton11() 
//=============================================================================
{
	m_Edit.ModifyStyle(0, WS_HSCROLL);
	m_Edit.SetWindowText(
		_T("	XMSGBOXPARAMS xmb;\r\n")
		_T("	xmb.nDisabledSeconds = 5; \r\n")
		_T("	xmb.bUseUserDefinedButtonCaptions = TRUE; \r\n")
		_T("	_tcscpy(xmb.UserDefinedButtonCaptions.szOK, _T(\"Buy Now\")); \r\n")
		_T("	_tcscpy(xmb.UserDefinedButtonCaptions.szCancel, _T(\"Continue\")); \r\n")
		_T("	XMessageBox(m_hWnd, \r\n")
		_T("		_T(\"Your trial period has expired! \\r\\n\\r\\n\") \r\n")
		_T("		_T(\"Please visit www.bozosoft.com to order the registered\\r\\n\") \r\n")
		_T("		_T(\"product, or click the Buy Now button below.\"), \r\n")
		_T("		_T(\"Example 11\"), MB_OKCANCEL | MB_ICONEXCLAMATION | MB_NORESOURCE, &xmb); \r\n")
		_T("	                                                                                                                                         \r\n")
	);

	XMSGBOXPARAMS xmb;
	xmb.nDisabledSeconds = 5;
	xmb.bUseUserDefinedButtonCaptions = TRUE;
	_tcscpy(xmb.UserDefinedButtonCaptions.szOK, _T("Buy Now"));
	_tcscpy(xmb.UserDefinedButtonCaptions.szCancel, _T("Continue"));
	XMessageBox(m_hWnd, 
		_T("Your trial period has expired! \r\n\r\n")
		_T("Please visit www.bozosoft.com to order the registered\r\n")
		_T("product, or click the Buy Now button below."),
		_T("Example 11"), MB_OKCANCEL | MB_ICONEXCLAMATION | MB_NORESOURCE, &xmb);
	
}
