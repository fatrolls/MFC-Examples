// XMessageBox.cpp  Version 1.5
//
// Author: Hans Dietrich
//         hdietrich@gmail.com
//
// Description:
//     XMessageBox.cpp implements XMessageBox(), a drop-in replacement for 
//     MessageBox() that includes custom checkboxes, custom buttons, custom
//     icon, and more.  For more information see
//         http://www.codeproject.com/dialog/xmessagebox.asp
//
// History
//     Version 1.5 - 2006 August 21
//     - Fixed bugs reported by kingworm, TMS_73, Curtis Faith, ladislav Hruska,
//       Tim Hodgson, DrJohnAir
//     - Incorporated Uwe Keim's changes for dynamic button captions
//
//     Version 1.4 - 2003 December 10
//     - Implemented MB_DONOTSHOWAGAIN
//     - Implemented MB_TOPMOST
//     - Implemented MB_SETFOREGROUND
//     - Added MB_SKIPSKIPALLCANCEL and MB_IGNOREIGNOREALLCANCEL, suggested
//       by Shane L
//     - Added HINSTANCE parameter for loading strings from extra-exe resource
//     - Added "report function" parameter for optional report function
//     - Added custom button parameter to allow definition of custom buttons,
//       thanks to Obliterator for comments and review
//     - Added timeout parameter to automatically select default button
//       after timeout expires, thanks to Obliterator for suggestion
//     - Added disabled time parameter, that will disable all buttons on the
//       messagebox for n seconds (for nag dialogs).
//     - Added custom icon parameter
//     - The XMessageBox dialog will now be centered even in non-MFC apps,
//       thanks to Tom Wright for suggestion
//     - The message text and caption text can now be passed as either a string
//       or a resource ID (using MAKEINTRESOURCE)
//     - The initial x,y screen coordinates can now be specified.
//     - The buttons can now be centered (default) or right-justified, as
//       in XP Explorer.
//     - Response to "Do Not Ask/Tell" checkboxes will be saved automatically
//       to ini file, if lpszModule member is non-NULL
//     - Gathered all optional parameters into one optional XMSGBOXPARAMS struct.
//     - Added assert if default button is set to Help or Report button
//     - Removed statics and rearranged code into classes, thanks to code from
//       Anne Jan Beeks
//
//     Version 1.3 - 2001 July 31
//     - Miscellaneous improvements and bug fixes
//
//     Version 1.2 - 2001 July 13
//     - Initial public release
//
// Some parts of this software are from information in the Microsoft SDK.
//
// This software is released into the public domain.  You are free to use it
// in any way you like, except that you may not sell this source code.
//
// This software is provided "as is" with no expressed or implied warranty.
// I accept no liability for any damage or loss of business that this software
// may cause.
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// include the following two lines if compiling an MFC app
#include "stdafx.h"
#pragma message("    compiling for MFC")
///////////////////////////////////////////////////////////////////////////////


#ifndef _MFC_VER
#include <windows.h>
#include <stdio.h>
#include <crtdbg.h>
#include <tchar.h>
#pragma message("    compiling for Win32")
#endif

#include "XMessageBox.h"

#pragma warning(disable : 4127)	// conditional expression is constant
#pragma warning(disable : 4996)	// disable bogus deprecation warning

#define countof(array) (sizeof(array)/sizeof(array[0]))


///////////////////////////////////////////////////////////////////////////////
//
// If you do not want TRACE output from XMessageBox.cpp you can
// uncomment the following lines:
//
//#undef  TRACE
//#define TRACE ((void)0)
//


///////////////////////////////////////////////////////////////////////////////
//
// If you want to save the state of "Do Not Ask/Tell" checkbox to profile (ini)
// file instead of registry, uncomment the following line:
//
//#define XMESSAGEBOX_USE_PROFILE_FILE


///////////////////////////////////////////////////////////////////////////////
//
// If you do not want automatic saving of "Do Not Ask/Tell" checkbox, 
// uncomment the following line:
//
//#define XMESSAGEBOX_DO_NOT_SAVE_CHECKBOX


///////////////////////////////////////////////////////////////////////////////
//
// If you have chosen to automatically save "Do Not Ask/Tell" checkbox to ini:
//
// Normally the lpszModule and nLine data are encoded, since it might not be
// desirable to allow users to be able to see the path and module name of
// your source file.  If you do not want encoding of "Do Not Ask/Tell" module
// info in the registry (or ini file), uncomment the following line:
//
//#define XMESSAGEBOX_DO_NOT_ENCODE


///////////////////////////////////////////////////////////////////////////////
//
// This identifier specifies the format of the text displayed for the timeout 
// key, which by default is "%s = %d".  You may change this to anything you 
// wish, as long as 1) there is both a %s and a %d;  and 2) the %s precedes 
// the %d.
//
#define XMESSAGEBOX_TIMEOUT_TEXT_FORMAT	_T("%s = %d")


///////////////////////////////////////////////////////////////////////////////
//
// This identifier specifies the name of the ini file, which by default 
// is "XMessageBox.ini".
//
#define XMESSAGEBOX_INI_FILE			_T("XMessageBox.ini")


///////////////////////////////////////////////////////////////////////////////
//
// This identifier specifies the registry key used to store checkbox values.  
// By default it is "XMessageBox".
//
#define XMESSAGEBOX_REGISTRY_KEY		_T("XMessageBox")



#ifndef XMESSAGEBOX_USE_PROFILE_FILE
static void WriteRegistry(LPCTSTR lpszCompanyName, LPCTSTR lpszKey, DWORD dwData);
static DWORD ReadRegistry(LPCTSTR lpszCompanyName, LPCTSTR lpszKey);
#endif


///////////////////////////////////////////////////////////////////////////////
//
// CXRect - replacement for CRect
//
class CXRect : public tagRECT
{
public:
// Constructors
	// uninitialized rectangle
	CXRect() {}

// Attributes (in addition to RECT members)

	// retrieves the width
	int Width() const	{ return right - left; }

	// returns the height
	int Height() const	{ return bottom - top; }

// Operations

	// set rectangle from left, top, right, and bottom
	void SetRect(int x1, int y1, int x2, int y2)
	{
		::SetRect(this, x1, y1, x2, y2);
	}
};


///////////////////////////////////////////////////////////////////////////////
//
// CXDialogItem
//
class CXDialogTemplate;

class CXDialogItem
{
public:
	DLGITEMTEMPLATE m_dlgItemTemplate;
	enum Econtroltype { ICON = 0x7F, BUTTON, EDITCONTROL, STATICTEXT, CHECKBOX };
	Econtroltype m_controltype;
	TCHAR * m_pszCaption;	//+++1.5

public:
	CXDialogItem(Econtroltype cType);	// default constructor will fill in default values
	CXDialogItem() {};					// default constructor, not to be called directly
	virtual ~CXDialogItem();			//+++1.5

	void AddItem(CXDialogTemplate& dialog, 
				 Econtroltype cType,
				 UINT nID,
				 CXRect* prect = NULL,
				 LPCTSTR pszCaption = NULL);
};


///////////////////////////////////////////////////////////////////////////////
//
// CXDialogTemplate
//
class CXDialogTemplate
{
// Constructors
public:
	CXDialogTemplate(HWND hWnd,
					 LPCTSTR lpszMessage,
					 LPCTSTR lpszCaption,
					 UINT nStyle,
					 XMSGBOXPARAMS *pXMB);

	virtual ~CXDialogTemplate();

// Attributes
public:
	LPCTSTR	GetMessageText() const				{ return m_lpszMessage; }
	int&	GetButtonCount()					{ return m_nButton; }
	UINT	GetDefaultButtonId() const			{ return m_nDefId; }
	void	SetDefaultButtonId(UINT nDefId)		{ m_nDefId = nDefId; }
	int		GetDefaultButton() const			{ return m_nDefButton; }

// Operations
public:
	int		Display();
	void	AddItem(CXDialogItem::Econtroltype cType,
					UINT nID,
					CXRect* prect = NULL,
					LPCTSTR pszCaption = NULL);
	void	AddCheckBox(HDC hdc, 
						int& x, 
						int& y, 
						CXRect& rect, 
						CXRect& mbrect, 
						CXRect& buttonrow, 
						CXRect& checkboxrect, 
						LPCTSTR lpszButtonCaption);

// Implementation
protected:
	enum { FirstControlId = 1001};
	enum { MaxButtonStringSize = 100};
	enum
	{
		//ButtonWidth         = 90,
		ButtonWidth         = 78,		//+++1.5
		ButtonTimeoutWidth  = 100,
		//ButtonHeight        = 26,
		ButtonHeight        = 23,		//+++1.5
		ButtonSpacing       = 6,
		BottomMargin        = 12,
		DoNotAskAgainHeight = 16,

		IdDoNotAskAgian     = 5555,
		IdExHelp            = 300,
		IdExReport          = 301,

		// if you change the value for MaxItems, make sure that the code
		// in CXDialogTemplate remains consistent with your changes.
		MaxItems            = 20,	// max no. of items in the dialog
		MaxCustomButtons    = 4,
		MinimalHeight       = 70,
		SpacingSize         = 8,
		MessageSize         = 64*1024,
		SpacingBetweenMessageAndButtons = 10,
	};

	CXDialogItem* m_pDlgItemArray[MaxItems];
	XMESSAGEBOX_REPORT_FUNCTION m_lpReportFunc;
	DWORD		m_dwReportUserData;
	int			m_Options;
	int			m_nButton;			// current button no.
	int			m_nDefButton;		// Default button
	int			m_nTimeoutSeconds;	// timeout in seconds (before default button selected)
	int			m_nDisabledSeconds;	// disabled time in seconds (before buttons are enabled)
	int			m_X, m_Y;			// initial x,y screen coordinates
	UINT		m_nMaxID;			// max control id (one more)
	UINT		m_nDefId;			// button number of default button
	UINT		m_nHelpId;			// help context id
	UINT		m_nStyle;			// message box style
	BOOL		m_bRightJustifyButtons;	// TRUE = right justify buttons
	LPCTSTR		m_lpszModule;		// module name (for saving DoNotAsk state)
	int			m_nLine;			// line number (for saving DoNotAsk state)

	HWND		m_hWnd;				// handle of owner window
	HINSTANCE	m_hInstanceStrings;	// handle to instance used for loading strings
	HINSTANCE	m_hInstanceIcon;	// handle to instance used for loading icon

	LPTSTR		m_lpszMessage;		// message buffer
	LPTSTR		m_lpszCaption;		// caption buffer
	TCHAR		m_szCustomButtons[MAX_PATH];	// custom buttons - strings 
												// separated by \n
	TCHAR		m_szCompanyName[MAX_PATH];		// used when saving checkbox state in registry
	HICON		m_hIcon;			// Handle of icon
	HANDLE		m_hFont;			// handle to font for the message box

	DLGTEMPLATE m_dlgTempl;			// message box dialog template

	TCHAR		m_szDefaultButton	[MaxButtonStringSize];	// used for original default 
															// button text, in case of
															// countdown timer

	TCHAR		szAbort				[MaxButtonStringSize];
	TCHAR		szCancel			[MaxButtonStringSize];
	TCHAR		szContinue			[MaxButtonStringSize];
	TCHAR		szDoNotAskAgain		[MaxButtonStringSize];
	TCHAR		szDoNotTellAgain	[MaxButtonStringSize];
	TCHAR		szDoNotShowAgain	[MaxButtonStringSize];
	TCHAR		szHelp				[MaxButtonStringSize];
	TCHAR		szIgnore			[MaxButtonStringSize];
	TCHAR		szIgnoreAll			[MaxButtonStringSize];
	TCHAR		szNo				[MaxButtonStringSize];
	TCHAR		szNoToAll			[MaxButtonStringSize];
	TCHAR		szOK				[MaxButtonStringSize];
	TCHAR		szReport			[MaxButtonStringSize];
	TCHAR		szRetry				[MaxButtonStringSize];
	TCHAR		szSkip				[MaxButtonStringSize];
	TCHAR		szSkipAll			[MaxButtonStringSize];
	TCHAR		szTryAgain			[MaxButtonStringSize];
	TCHAR		szYes				[MaxButtonStringSize];
	TCHAR		szYesToAll			[MaxButtonStringSize];

	enum EOptions
	{
		DoNotAskAgain    = 0x01,		// include Do Not Ask checkbox
		DoNotTellAgain   = 0x02,		// include Do Not Tell checkbox
		DoNotShowAgain   = 0x04,		// include Do Not Show checkbox
		CancelButton     = 0x08,		// include Cancel button
		OkButton         = 0x10,		// MB_OK used
		CancelOrOkButton = CancelButton | OkButton,
		EDefault         = 0x00
	};

	static BOOL CALLBACK MsgBoxDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM me);

	void	Unset(EOptions id)			{ m_Options &= ~id;};
	void	Set(EOptions id)			{ m_Options |= id;};
	int		Option(EOptions id) const	{ return m_Options & id; }
	void	LoadButtonStrings();
	void	LoadButtonStringsFromResources(HINSTANCE hInstance);

	//-[UK
	void LoadUserDefinedButtonStrings( 
		const XMSGBOXPARAMS::CUserDefinedButtonCaptions& udcs );
	//-]UK
};

#ifndef XMESSAGEBOX_DO_NOT_SAVE_CHECKBOX
///////////////////////////////////////////////////////////////////////////////
//
// encode()
//
// Purpose:     Disguise string with simple encoding.  Note that there is
//              no requirement to decode string.
//
// Parameters:  str - pointer null-terminated string to encode
//
// Returns:     LPTSTR - pointer to str
//

#ifndef XMESSAGEBOX_DO_NOT_ENCODE

// folowing string MUST be at least 64 TCHARs
static TCHAR *szAlphabet = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
						   _T("0123456789")
						   _T("abcdefghijklmnopqrstuvwxyz")
						   _T("98");
#endif

static LPTSTR encode(LPTSTR str)
{
#ifndef XMESSAGEBOX_DO_NOT_ENCODE
	for (UINT i = 0; i < _tcslen(str); i++)
	{
		UINT n = (UINT) str[i];
		str[i] = szAlphabet[(n + (5*i)) % 64];
	}
#endif

	return str;
}
#endif

///////////////////////////////////////////////////////////////////////////////
//
// XMessageBox()
//
// The XMessageBox function creates, displays, and operates a message box.
// The message box contains an application-defined message and title, plus
// any combination of predefined icons, push buttons, and checkboxes.
//
// For more information see
//     http://www.codeproject.com/dialog/xmessagebox.asp
//
// int XMessageBox(HWND hwnd,                 // handle of owner window
//                 LPCTSTR lpszMessage,       // address of text in message box
//                 LPCTSTR lpszCaption,       // address of title of message box
//                 UINT nStyle,               // style of message box
//                 XMSGBOXPARAMS * pXMB)      // optional parameters
//
// PARAMETERS
//
//     hwnd              - Identifies the owner window of the message box to be
//                         created. If this parameter is NULL, the message box
//                         has no owner window.
//
//     lpszMessage       - Pointer to a null-terminated string containing the
//                         message to be displayed.
//
//     lpszCaption       - Pointer to a null-terminated string used for the
//                         dialog box title. If this parameter is NULL, the
//                         default title Error is used.
//
//     nStyle            - Specifies a set of bit flags that determine the
//                         contents and  behavior of the dialog box. This
//                         parameter can be a combination of flags from the
//                         following groups of flags.
//
//     pXMB              - Pointer to optional parameters.  The parameters
//                         struct XMSGBOXPARAMS is defined in XMessageBox.h.
//
///////////////////////////////////////////////////////////////////////////////

int XMessageBox(HWND hwnd,
				LPCTSTR lpszMessage,
				LPCTSTR lpszCaption /*= NULL*/,
				UINT nStyle /*= MB_OK | MB_ICONEXCLAMATION*/,
				XMSGBOXPARAMS * pXMB /*= NULL*/)
{
	_ASSERTE(lpszMessage);

	if (hwnd == NULL)
	{
		hwnd = ::GetActiveWindow() ;
		if (hwnd != NULL)
		{
			hwnd = ::GetLastActivePopup(hwnd) ;
		}
	};

	if ((nStyle & MB_ICONHAND) && (nStyle & MB_SYSTEMMODAL))
	{
		// NOTE: When an application calls MessageBox and specifies the
		// MB_ICONHAND and MB_SYSTEMMODAL flags for the nStyle parameter,
		// the system displays the resulting message box regardless of
		// available memory.

		return ::MessageBox(hwnd, lpszMessage, lpszCaption, nStyle);
	}


	if (lpszCaption == NULL || lpszCaption[0] == 0)
		lpszCaption = _T("Error");

	XMSGBOXPARAMS xmb;
	if (pXMB)
		xmb = *pXMB;


#ifndef XMESSAGEBOX_DO_NOT_SAVE_CHECKBOX

	// are Do Not Ask styles specified?
	if ((nStyle & MB_DONOTASKAGAIN) || 
		(nStyle & MB_DONOTTELLAGAIN) ||
		(nStyle & MB_DONOTSHOWAGAIN))
	{
		// is module name supplied?
		if (xmb.lpszModule && (xmb.lpszModule[0] != _T('\0')))
		{
			// caller specified Do No Ask style and a module name -
			// check if answer previously saved in ini file

			// get full path to ini file
			TCHAR szPathName[MAX_PATH*2];
			szPathName[0] = _T('\0');
			::GetModuleFileName(NULL, szPathName, countof(szPathName)-1);

			TCHAR *cp = _tcsrchr(szPathName, _T('\\'));
			if (cp != NULL)
				*(cp+1) = _T('\0');
			_tcscat(szPathName, XMESSAGEBOX_INI_FILE);

			// key is module name and line
			TCHAR szKey[MAX_PATH*2];
			_tcscpy(szKey, xmb.lpszModule);
			TRACE(_T("szKey=<%s>\n"), szKey);

			encode(szKey);		// simple encoding to obscure module name

			TCHAR szLine[100];
			szLine[0] = _T('\0');
			_tcscat(szKey, _itot(xmb.nLine, szLine, 10));
			TRACE(_T("szKey=<%s>\n"), szKey);

			TCHAR szBuf[100];
			szBuf[0] = _T('\0');

			DWORD dwData = 0;

#ifndef XMESSAGEBOX_USE_PROFILE_FILE

			// read from registry 

			dwData = ReadRegistry(xmb.szCompanyName, szKey);
			TRACE(_T("dwData=0x%08X\n"), dwData);

#else
			// read from ini file

			// data string is hex value of XMessageBox return code
			::GetPrivateProfileString(_T("DoNotAsk"),	// section name
									  szKey,			// key name
									  _T(""),			// default string
									  szBuf,			// destination buffer
									  countof(szBuf)-1,	// size of destination buffer
									  szPathName);		// initialization file name

			dwData = _tcstoul(szBuf, NULL, 16);
			TRACE(_T("szBuf=<%s>  dwData=0x%08X\n"), szBuf, dwData);

#endif	// XMESSAGEBOX_USE_PROFILE_FILE

			// Note:  dwData will be 0 if either ReadRegistry or 
			// GetPrivateProfileString fail to find key

			if ((dwData & MB_DONOTASKAGAIN) || 
				(dwData & MB_DONOTTELLAGAIN) ||
				(dwData & MB_DONOTSHOWAGAIN))
			{
				TRACE(_T("saved DoNotAsk found, returning 0x%08X\n"), dwData);
				return (int)dwData;
			}
		}
	}

#endif	// #ifndef XMESSAGEBOX_DO_NOT_SAVE_CHECKBOX

	// should be seconds, not milliseconds
	_ASSERTE(xmb.nTimeoutSeconds < 1000);
	if (xmb.nTimeoutSeconds >= 1000)
		xmb.nTimeoutSeconds = 10;

	// should be seconds, not milliseconds
	_ASSERTE(xmb.nDisabledSeconds < 1000);
	if (xmb.nDisabledSeconds >= 1000)
		xmb.nDisabledSeconds = 10;

	// cannot have both disabled and timeout seconds
	_ASSERTE(xmb.nDisabledSeconds == 0 || xmb.nTimeoutSeconds == 0);

	CXDialogTemplate dlg(hwnd,
						 lpszMessage,
						 lpszCaption,
						 nStyle,
						 &xmb);

	if ((nStyle & MB_NOSOUND) == 0)
		::MessageBeep(nStyle & MB_ICONMASK);

	int rc = dlg.Display();

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
// IconProc
LONG CALLBACK IconProc(HWND hwnd, UINT message, WPARAM, LPARAM)
{
	if (message == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		::DrawIcon(hdc, 0, 0, (HICON)(UINT_PTR)(::GetWindowLong(hwnd, GWL_USERDATA)));
		EndPaint(hwnd, &ps);
	}

	return FALSE;
}



///////////////////////////////////////////////////////////////////////////////
// CXDialogTemplate class

///////////////////////////////////////////////////////////////////////////////
// CXDialogTemplate ctor
CXDialogTemplate::CXDialogTemplate(HWND hWnd,
								   LPCTSTR lpszMessage,
								   LPCTSTR lpszCaption,
								   UINT nStyle,
								   XMSGBOXPARAMS *pXMB) :
	m_hWnd(hWnd),
	m_lpszMessage(NULL),
	m_lpszCaption(NULL),
	m_nStyle(nStyle),
	m_nHelpId(pXMB->nIdHelp),
	m_hInstanceStrings(pXMB->hInstanceStrings),
	m_hInstanceIcon(pXMB->hInstanceIcon),
	m_lpReportFunc(pXMB->lpReportFunc),
	m_dwReportUserData(pXMB->dwReportUserData),
	m_nTimeoutSeconds(pXMB->nTimeoutSeconds),
	m_nDisabledSeconds(pXMB->nDisabledSeconds),
	m_Options(EDefault),
	m_hIcon(NULL),
	m_hFont(NULL),
	m_nButton(0),				// current button no.
	m_nDefId(1),				// button number of default button
	m_nMaxID(FirstControlId),	// control id
	m_X(pXMB->x),
	m_Y(pXMB->y),
	m_lpszModule(pXMB->lpszModule),
	m_nLine(pXMB->nLine),
	m_bRightJustifyButtons(pXMB->dwOptions & XMSGBOXPARAMS::RightJustifyButtons)
{
	// store company name to use for saving checkbox state in registry
	memset(m_szCompanyName, 0, sizeof(m_szCompanyName));
	_tcscpy(m_szCompanyName, pXMB->szCompanyName);
		
	// m_szDefaultButton is used to save text for timeout option
	memset(m_szDefaultButton, 0, sizeof(m_szDefaultButton));

	///////////////////////////////////////////////////////////////////////////
	// allocate buffers for message and caption - buffers must be allocated
	// (instead of just using pointers) because we may need to load the strings
	// from resources
	m_lpszMessage = new TCHAR [MessageSize];
	if (m_lpszMessage)
		m_lpszMessage[0] = _T('\0');
	memset(m_lpszMessage, 0, MessageSize);

	m_lpszCaption = new TCHAR [MessageSize];
	if (m_lpszCaption)
		m_lpszCaption[0] = _T('\0');
	memset(m_lpszCaption, 0, MessageSize);

	///////////////////////////////////////////////////////////////////////////
	// set instance handle for strings
	HINSTANCE hInstanceStrings = m_hInstanceStrings;
	if (!hInstanceStrings)
		hInstanceStrings = ::GetModuleHandle(NULL);

	///////////////////////////////////////////////////////////////////////////
	// load message text from resource or string
	if (lpszMessage)
	{
		if (HIWORD(lpszMessage) == NULL)
		{
			// looks like a resource id
			if (::LoadString(hInstanceStrings,
							 LOWORD((UINT_PTR)lpszMessage),
							 m_lpszMessage,
							 MessageSize-1) == 0)
				m_lpszMessage[0] = _T('\0');
		}
		else
		{
			// looks like a string pointer
			_tcsncpy(m_lpszMessage, lpszMessage, MessageSize-1);
		}
		m_lpszMessage[MessageSize-1] = _T('\0');
	}

	///////////////////////////////////////////////////////////////////////////
	// load caption from resource or string
	if (lpszCaption)
	{
		if (HIWORD(lpszCaption) == NULL)
		{
			// looks like a resource id
			if (::LoadString(hInstanceStrings,
							 LOWORD((UINT_PTR)lpszCaption),
							 m_lpszCaption,
							 MessageSize-1) == 0)
				m_lpszCaption[0] = _T('\0');
		}
		else
		{
			// looks like a string pointer
			_tcsncpy(m_lpszCaption, lpszCaption, MessageSize-1);
		}
		m_lpszCaption[MessageSize-1] = _T('\0');
	}

	///////////////////////////////////////////////////////////////////////////
	// load custom buttons from resource or string
	memset(m_szCustomButtons, 0, sizeof(m_szCustomButtons));

	if (pXMB->nIdCustomButtons)
	{
		// load from resource id
		if (::LoadString(hInstanceStrings,
						 pXMB->nIdCustomButtons,
						 m_szCustomButtons,
						 countof(m_szCustomButtons)-1) == 0)
			m_szCustomButtons[0] = _T('\0');
	}

	if ((m_szCustomButtons[0] == _T('\0')) && (pXMB->szCustomButtons[0] != _T('\0')))
	{
		// load from string
		_tcsncpy(m_szCustomButtons, pXMB->szCustomButtons, countof(m_szCustomButtons)-1);
	}
	m_szCustomButtons[countof(m_szCustomButtons)-1] = _T('\0');

	///////////////////////////////////////////////////////////////////////////
	// load report button caption from resource or string
	memset(szReport, 0, sizeof(szReport));

	if (pXMB->nIdReportButtonCaption)
	{
		// load from resource id
		if (::LoadString(hInstanceStrings,
						 pXMB->nIdReportButtonCaption,
						 szReport,
						 MaxButtonStringSize-1) == 0)
			szReport[0] = _T('\0');
	}

	if ((szReport[0] == _T('\0')) && (pXMB->szReportButtonCaption[0] != _T('\0')))
	{
		_tcsncpy(szReport, pXMB->szReportButtonCaption, MaxButtonStringSize-1);
	}
	szReport[MaxButtonStringSize-1] = _T('\0');

	///////////////////////////////////////////////////////////////////////////
	// load  button captions from resource or use default strings

	//-[UK
	if ( pXMB->bUseUserDefinedButtonCaptions )
	{
		LoadUserDefinedButtonStrings( pXMB->UserDefinedButtonCaptions );
	}
	else
	{
	//-]UK
		if (nStyle & MB_NORESOURCE)
			LoadButtonStrings();				// use English strings
		else
			LoadButtonStringsFromResources(hInstanceStrings);	// try to load from resource strings
	//-[UK
	}
	//-]UK

	///////////////////////////////////////////////////////////////////////////
	// get dc for drawing
	HDC hdc = ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	_ASSERTE(hdc);

	///////////////////////////////////////////////////////////////////////////
	// get message font
	NONCLIENTMETRICS ncm;
	memset(&ncm, 0, sizeof(ncm));
	ncm.cbSize = sizeof(ncm);
	::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0);
	m_hFont = ::CreateFontIndirect(&ncm.lfMessageFont);

	HFONT hOldFont = (HFONT)::SelectObject(hdc, m_hFont);

	int nMaxWidth = (::GetSystemMetrics(SM_CXSCREEN) / 2) + 80;	//+++1.5
	if (nStyle & MB_ICONMASK)
		nMaxWidth -= GetSystemMetrics(SM_CXICON) + 2*SpacingSize;

	CXRect msgrect;
	SetRect(&msgrect, 0, 0, nMaxWidth, nMaxWidth);

	///////////////////////////////////////////////////////////////////////////
	// get output size of message text
	::DrawText(hdc, GetMessageText(), -1, &msgrect, DT_LEFT | DT_NOPREFIX |
		DT_WORDBREAK | DT_CALCRECT | DT_EXPANDTABS);	//+++1.5

	msgrect.right  += 12;
	msgrect.bottom += 5;

	msgrect.left    = 2 * SpacingSize;
	msgrect.top     = 2 * SpacingSize;
	msgrect.right  += 2 * SpacingSize;
	msgrect.bottom += 2 * SpacingSize;

	// client rect
	CXRect mbrect;
	SetRect(&mbrect, 0, 0,
		msgrect.Width() + (2 * SpacingSize),
		msgrect.Height() + (2 * SpacingSize));

	if (mbrect.Height() < MinimalHeight)
		mbrect.bottom = MinimalHeight;

	///////////////////////////////////////////////////////////////////////////
	// initialize the DLGTEMPLATE structure
	m_dlgTempl.x = 0;
	m_dlgTempl.y = 0;

	m_dlgTempl.cdit = 0;

	m_dlgTempl.style = WS_CAPTION | WS_VISIBLE | WS_SYSMENU |
		WS_POPUP | DS_MODALFRAME | DS_CENTER;

	m_dlgTempl.dwExtendedStyle = 0;

	if (nStyle & MB_SYSTEMMODAL)
		m_dlgTempl.style |= DS_SYSMODAL;

	for (int j = 0; j < MaxItems; j++)
		m_pDlgItemArray[j] = NULL;

	int x, y;

	CXRect iconrect;
	SetRect(&iconrect, 0, 0, 0, 0);
	CXRect rect;

	HINSTANCE hInstanceIcon = m_hInstanceIcon;
	if (!hInstanceIcon)
		hInstanceIcon = ::GetModuleHandle(NULL);

	///////////////////////////////////////////////////////////////////////////
	// load icon by id or by name
	if (pXMB->nIdIcon)
	{
		m_hIcon = ::LoadIcon(hInstanceIcon, MAKEINTRESOURCE(pXMB->nIdIcon));

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		int icon_x = SpacingSize;
		int icon_y = SpacingSize;

		msgrect.left += cxIcon + icon_x;
		msgrect.right += cxIcon + icon_x;

		mbrect.right = msgrect.right + SpacingSize;

		SetRect(&iconrect, icon_x, icon_y, icon_x + cxIcon + 2, icon_y + cyIcon + 2);
		AddItem(CXDialogItem::STATICTEXT, 1000, &iconrect, _T(""));
	}
	else if (pXMB->szIcon[0] != _T('\0'))
	{
		m_hIcon = ::LoadIcon(hInstanceIcon, pXMB->szIcon);
	}
	else if (nStyle & MB_ICONMASK)
	{
		LPTSTR lpIcon = (LPTSTR)IDI_EXCLAMATION;

		switch (nStyle & MB_ICONMASK)
		{
			case MB_ICONEXCLAMATION: lpIcon = (LPTSTR)IDI_EXCLAMATION; break;
			case MB_ICONHAND:        lpIcon = (LPTSTR)IDI_HAND;        break;
			case MB_ICONQUESTION:    lpIcon = (LPTSTR)IDI_QUESTION;    break;
			case MB_ICONASTERISK:    lpIcon = (LPTSTR)IDI_ASTERISK;    break;
		}

		if (lpIcon)
		{
			m_hIcon = ::LoadIcon(NULL, lpIcon);

			int cxIcon = GetSystemMetrics(SM_CXICON);
			int cyIcon = GetSystemMetrics(SM_CYICON);

			int icon_x = SpacingSize;
			int icon_y = SpacingSize;

			msgrect.left += cxIcon + icon_x;
			msgrect.right += cxIcon + icon_x;

			mbrect.right = msgrect.right + SpacingSize;

			SetRect(&iconrect, icon_x, icon_y, icon_x + cxIcon + 2, icon_y + cyIcon + 2);
			AddItem(CXDialogItem::STATICTEXT, 1000, &iconrect, _T(""));
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// add message text
	AddItem(CXDialogItem::STATICTEXT, m_nMaxID++, &msgrect, GetMessageText());

	int cItems = 0;

	if (m_szCustomButtons[0] == _T('\0'))
	{
		// process standard buttons

		switch (nStyle & MB_TYPEMASK)
		{
			case MB_ABORTRETRYIGNORE      : cItems = 3; break;
			case MB_CANCELTRYCONTINUE     : cItems = 3; break;
			case MB_CONTINUEABORT         : cItems = 2; break;
			case MB_IGNOREIGNOREALLCANCEL : cItems = 3; break;
			case MB_OK                    : cItems = 1; break;
			case MB_OKCANCEL              : cItems = 2; break;
			case MB_RETRYCANCEL           : cItems = 2; break;
			case MB_SKIPSKIPALLCANCEL     : cItems = 3; break;
			case MB_YESNO                 : cItems = 2; break;
			case MB_YESNOCANCEL           : cItems = 3; break;
		}

		if (nStyle & MB_YESTOALL)
		{
			_ASSERTE((nStyle & MB_YESNO) || (nStyle & MB_YESNOCANCEL));
			if ((nStyle & MB_YESNO) || (nStyle & MB_YESNOCANCEL))
				cItems++;
		}

		if (nStyle & MB_NOTOALL)
		{
			_ASSERTE((nStyle & MB_YESNO) || (nStyle & MB_YESNOCANCEL));
			if ((nStyle & MB_YESNO) || (nStyle & MB_YESNOCANCEL))
				cItems++;
		}
	}
	else
	{
		// process custom buttons

		TCHAR szCustomButtons[MAX_PATH];
		_tcscpy(szCustomButtons, m_szCustomButtons);

		int i = 0;
		TCHAR * cp = _tcstok(szCustomButtons, _T("\n"));
		while (cp != NULL)
		{
			if (i >= MaxCustomButtons)
				break;

			cp = _tcstok(NULL, _T("\n"));
			i++;
		}

		cItems += i;
	}

	int nHelpButton = 0;
	if (nStyle & MB_HELP)
	{
		cItems++;
		nHelpButton = cItems;
	}

	int nReportButton = 0;
	if (m_lpReportFunc)
	{
		cItems++;
		nReportButton = cItems;
	}

	if (nStyle & MB_DONOTASKAGAIN)
		Set(DoNotAskAgain);
	else if (nStyle & MB_DONOTTELLAGAIN)
		Set(DoNotTellAgain);
	else if (nStyle & MB_DONOTSHOWAGAIN)
		Set(DoNotShowAgain);

	_ASSERTE(cItems > 0);

	CXRect buttonrow;
	y = (msgrect.bottom > iconrect.bottom) ? msgrect.bottom : iconrect.bottom;
	y += SpacingBetweenMessageAndButtons;

	// allow for wider buttons if timeout specified
	int button_width = m_nTimeoutSeconds ? ButtonTimeoutWidth : ButtonWidth;

	int w = button_width * cItems + (ButtonSpacing * (cItems - 1));

	SetRect(&buttonrow,0, y, w, y + ButtonHeight);

	switch (nStyle & MB_DEFMASK)
	{
		case MB_DEFBUTTON1 : m_nDefButton = 1; break;
		case MB_DEFBUTTON2 : m_nDefButton = 2; break;
		case MB_DEFBUTTON3 : m_nDefButton = 3; break;
		case MB_DEFBUTTON4 : m_nDefButton = 4; break;
		case MB_DEFBUTTON5 : m_nDefButton = 5; break;
		case MB_DEFBUTTON6 : m_nDefButton = 6; break;
		default:             m_nDefButton = 1; break;
	}

	if (m_nDefButton > cItems)
		m_nDefButton = 1;

	if (nHelpButton == m_nDefButton)
	{
		TRACE(_T("ERROR:  Help button cannot be default button\n"));
		_ASSERTE(FALSE);
	}

	if (nReportButton == m_nDefButton)
	{
		TRACE(_T("ERROR:  Report button cannot be default button\n"));
		_ASSERTE(FALSE);
	}

	///////////////////////////////////////////////////////////////////////////
	// add buttons

	mbrect.bottom = buttonrow.bottom + BottomMargin;

	int bw = buttonrow.Width();
	int bleft = 2 * SpacingSize;
	int bright = bleft + bw;

	if (mbrect.right <= (bright + (2 * SpacingSize)))
		mbrect.right = bright + (2 * SpacingSize);

	x = (mbrect.Width() - bw) / 2;
	y = buttonrow.top;

	if (m_bRightJustifyButtons)
	{
		x = mbrect.right - ButtonSpacing - cItems * (ButtonSpacing + button_width);
	}

	if (m_szCustomButtons[0] == _T('\0'))
	{
		// no custom buttons

		switch (nStyle & MB_TYPEMASK)
		{
			case MB_OK:
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDOK, &rect, szOK);
				Set(OkButton);
				break;

			case MB_OKCANCEL:
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDOK, &rect, szOK);

				x += button_width + ButtonSpacing;
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDCANCEL, &rect, szCancel);
				Set(CancelButton);
				break;

			case MB_YESNO:
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDYES, &rect, szYes);

				if (nStyle & MB_YESTOALL)
				{
					x += button_width + ButtonSpacing;
					SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
					AddItem(CXDialogItem::BUTTON, IDYESTOALL, &rect, szYesToAll);
				}

				x += button_width + ButtonSpacing;
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDNO, &rect, szNo);

				if (nStyle & MB_NOTOALL)
				{
					x += button_width + ButtonSpacing;
					SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
					AddItem(CXDialogItem::BUTTON, IDNOTOALL, &rect, szNoToAll);
				}
				break;

			case MB_YESNOCANCEL:
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDYES, &rect, szYes);

				if (nStyle & MB_YESTOALL)
				{
					x += button_width + ButtonSpacing;
					SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
					AddItem(CXDialogItem::BUTTON, IDYESTOALL, &rect, szYesToAll);
				}

				x += button_width + ButtonSpacing;
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDNO, &rect, szNo);

				if (nStyle & MB_NOTOALL)
				{
					x += button_width + ButtonSpacing;
					SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
					AddItem(CXDialogItem::BUTTON, IDNOTOALL, &rect, szNoToAll);
				}

				x += button_width + ButtonSpacing;
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDCANCEL, &rect, szCancel);
				Set(CancelButton);
				break;

			case MB_ABORTRETRYIGNORE:
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDABORT, &rect, szAbort);

				x += button_width + ButtonSpacing;
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDRETRY, &rect, szRetry);

				x += button_width + ButtonSpacing;
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDIGNORE, &rect, szIgnore);
				break;

			case MB_RETRYCANCEL:
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDRETRY, &rect, szRetry);

				x += button_width + ButtonSpacing;
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDCANCEL, &rect, szCancel);
				Set(CancelButton);
				break;

			case MB_CONTINUEABORT:
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDCONTINUE, &rect, szContinue);

				x += button_width + ButtonSpacing;
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDABORT, &rect, szAbort);
				break;

			case MB_CANCELTRYCONTINUE:
				rect.SetRect(x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDCANCEL, &rect, szCancel);

				x += button_width + ButtonSpacing;
				rect.SetRect(x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDTRYAGAIN, &rect, szTryAgain);

				x += button_width + ButtonSpacing;
				rect.SetRect(x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDCONTINUE, &rect, szContinue);
				Set(CancelButton);
				break;

			case MB_SKIPSKIPALLCANCEL:
				rect.SetRect(x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDSKIP, &rect, szSkip);

				x += button_width + ButtonSpacing;
				rect.SetRect(x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDSKIPALL, &rect, szSkipAll);

				x += button_width + ButtonSpacing;
				rect.SetRect(x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDCANCEL, &rect, szCancel);
				Set(CancelButton);
				break;

			case MB_IGNOREIGNOREALLCANCEL:
				rect.SetRect(x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDIGNORE, &rect, szIgnore);

				x += button_width + ButtonSpacing;
				rect.SetRect(x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDIGNOREALL, &rect, szIgnoreAll);

				x += button_width + ButtonSpacing;
				rect.SetRect(x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDCANCEL, &rect, szCancel);
				Set(CancelButton);
				break;

			default:
				SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
				AddItem(CXDialogItem::BUTTON, IDOK, &rect, szOK);
				break;
		}
	}
	else
	{
		// process custom buttons

		TCHAR szCustomButtons[MAX_PATH];
		_tcscpy(szCustomButtons, m_szCustomButtons);

		int i = 0;
		TCHAR * cp = _tcstok(szCustomButtons, _T("\n"));
		while (cp != NULL)
		{
			if (i >= MaxCustomButtons)
				break;

			if (i > 0)
				x += button_width + ButtonSpacing;

			rect.SetRect(x, y, x + button_width, y + ButtonHeight);
			AddItem(CXDialogItem::BUTTON, IDCUSTOM1 + i, &rect, cp);
			cp = _tcstok(NULL, _T("\n"));
			i++;
		}
	}

	if (nStyle & MB_HELP)
	{
		x += button_width + ButtonSpacing;
		SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
		AddItem(CXDialogItem::BUTTON, IdExHelp, &rect, szHelp);
	}

	if (m_lpReportFunc)
	{
		x += button_width + ButtonSpacing;
		SetRect(&rect,x, y, x + button_width, y + ButtonHeight);
		AddItem(CXDialogItem::BUTTON, IdExReport, &rect, szReport);
	}

	///////////////////////////////////////////////////////////////////////////
	// add checkbox

	nMaxWidth = ::GetSystemMetrics(SM_CXSCREEN) / 3;

	CXRect checkboxrect;
	SetRect(&checkboxrect,0, 0, nMaxWidth, DoNotAskAgainHeight);

	if (nStyle & MB_DONOTASKAGAIN)
		AddCheckBox(hdc, x, y, rect, mbrect, buttonrow, checkboxrect, szDoNotAskAgain);
	else if (nStyle & MB_DONOTTELLAGAIN)
		AddCheckBox(hdc, x, y, rect, mbrect, buttonrow, checkboxrect, szDoNotTellAgain);
	else if (nStyle & MB_DONOTSHOWAGAIN)
		AddCheckBox(hdc, x, y, rect, mbrect, buttonrow, checkboxrect, szDoNotShowAgain);

	if (buttonrow.bottom >= mbrect.bottom)
		mbrect.bottom = buttonrow.bottom + (2 * SpacingSize);

	if (mbrect.right < (buttonrow.right + (2 * SpacingSize)))
		mbrect.right = buttonrow.right + (2 * SpacingSize);

	short hidbu = HIWORD(GetDialogBaseUnits());
	short lodbu = LOWORD(GetDialogBaseUnits());

	m_dlgTempl.x = 0;
	m_dlgTempl.y = 0;
	m_dlgTempl.cx = (short)((mbrect.Width() * 4) / lodbu);
	m_dlgTempl.cy = (short)((mbrect.Height() * 8) / hidbu);

	::SelectObject(hdc, hOldFont);
	::DeleteDC(hdc);
}

///////////////////////////////////////////////////////////////////////////////
// CXDialogTemplate dtor
CXDialogTemplate::~CXDialogTemplate()
{
	if (m_hIcon)
		DestroyIcon(m_hIcon);

	if (m_hFont)
		::DeleteObject(m_hFont);

	for (int i = 0; i < MaxItems; i++)
	{
		if (m_pDlgItemArray[i])
		{
			delete m_pDlgItemArray[i];
			m_pDlgItemArray[i] = NULL;
		}
	}

	if (m_lpszMessage)
		delete [] m_lpszMessage;
	m_lpszMessage = NULL;

	if (m_lpszCaption)
		delete [] m_lpszCaption;
	m_lpszCaption = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// AddCheckBox
void CXDialogTemplate::AddCheckBox(HDC hdc, 
								   int& x, 
								   int& y, 
								   CXRect& rect, 
								   CXRect& mbrect, 
								   CXRect& buttonrow, 
								   CXRect& checkboxrect, 
								   LPCTSTR lpszButtonCaption)
{
	x = 2 * ButtonSpacing + 5;
	y += ButtonHeight + (2 * ButtonSpacing);

	::DrawText(hdc, lpszButtonCaption, -1, &checkboxrect,
		DT_LEFT | DT_NOPREFIX | DT_CALCRECT | DT_SINGLELINE);

	int w = checkboxrect.Width();
	w += w/3;

	SetRect(&rect, x, y, x + w, y + DoNotAskAgainHeight);
	AddItem(CXDialogItem::CHECKBOX, IdDoNotAskAgian, &rect, lpszButtonCaption);
	buttonrow.bottom = y + DoNotAskAgainHeight;
	mbrect.bottom = buttonrow.bottom + SpacingSize;
	if (mbrect.Width() < (x + w))
		mbrect.right = mbrect.left + x + w;
}

//-[UK
void CXDialogTemplate::LoadUserDefinedButtonStrings( 
	const XMSGBOXPARAMS::CUserDefinedButtonCaptions& udcs )
{
	TRACE(_T("in CXDialogTemplate::LoadUserDefinedButtonStrings\n"));

	_tcscpy(szAbort,          udcs.szAbort          );
	_tcscpy(szCancel,         udcs.szCancel         );
	_tcscpy(szContinue,       udcs.szContinue       );
	_tcscpy(szDoNotAskAgain,  udcs.szDoNotAskAgain  );
	_tcscpy(szDoNotTellAgain, udcs.szDoNotTellAgain );
	_tcscpy(szDoNotShowAgain, udcs.szDoNotShowAgain );
	_tcscpy(szHelp,           udcs.szHelp           );
	_tcscpy(szIgnore,         udcs.szIgnore         );
	_tcscpy(szIgnoreAll,      udcs.szIgnoreAll      );
	_tcscpy(szNo,             udcs.szNo             );
	_tcscpy(szNoToAll,        udcs.szNoToAll        );
	_tcscpy(szOK,             udcs.szOK             );
	if (szReport[0] == _T('\0'))
		_tcscpy(szReport,     udcs.szReport			);
	_tcscpy(szRetry,          udcs.szRetry          );
	_tcscpy(szSkip,           udcs.szSkip           );
	_tcscpy(szSkipAll,        udcs.szSkipAll        );
	_tcscpy(szTryAgain,       udcs.szTryAgain       );
	_tcscpy(szYes,            udcs.szYes            );
	_tcscpy(szYesToAll,       udcs.szYesToAll       );
}
//-]UK

///////////////////////////////////////////////////////////////////////////////
// LoadButtonStrings
void CXDialogTemplate::LoadButtonStrings()
{
	TRACE(_T("in CXDialogTemplate::LoadButtonStrings\n"));
	_tcscpy(szAbort,          _T("&Abort"));
	_tcscpy(szCancel,         _T("Cancel"));
	_tcscpy(szContinue,       _T("&Continue"));
	_tcscpy(szDoNotAskAgain,  _T("Don't ask me again"));
	_tcscpy(szDoNotTellAgain, _T("Don't tell me again"));
	_tcscpy(szDoNotShowAgain, _T("Don't show again"));
	_tcscpy(szHelp,           _T("&Help"));
	_tcscpy(szIgnore,         _T("&Ignore"));
	_tcscpy(szIgnoreAll,      _T("I&gnore All"));
	_tcscpy(szNo,             _T("&No"));
	_tcscpy(szNoToAll,        _T("N&o to All"));
	_tcscpy(szOK,             _T("OK"));
	if (szReport[0] == _T('\0'))
		_tcscpy(szReport,     _T("Re&port"));
	_tcscpy(szRetry,          _T("&Retry"));
	_tcscpy(szSkip,           _T("&Skip"));
	_tcscpy(szSkipAll,        _T("S&kip All"));
	_tcscpy(szTryAgain,       _T("&Try Again"));
	_tcscpy(szYes,            _T("&Yes"));
	_tcscpy(szYesToAll,       _T("Y&es to All"));
}

///////////////////////////////////////////////////////////////////////////////
// LoadButtonStringsFromResources
void CXDialogTemplate::LoadButtonStringsFromResources(HINSTANCE hInstance)
{
	TRACE(_T("in CXDialogTemplate::LoadButtonStringsFromResources\n"));

	_ASSERTE(hInstance);

	LoadButtonStrings();	// initialize all strings in case LoadString fails

	if (::LoadString(hInstance, IDS_ABORT, szAbort, MaxButtonStringSize) == 0)
		_tcscpy(szAbort, _T("&Abort"));
	szAbort[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_CANCEL, szCancel, MaxButtonStringSize) == 0)
		_tcscpy(szCancel, _T("Cancel"));
	szCancel[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_CONTINUE, szContinue, MaxButtonStringSize) == 0)
		_tcscpy(szContinue, _T("&Continue"));
	szContinue[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_DONOTASKAGAIN, szDoNotAskAgain, MaxButtonStringSize) == 0)
		_tcscpy(szDoNotAskAgain, _T("Don't ask me again"));
	szDoNotAskAgain[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_DONOTTELLAGAIN, szDoNotTellAgain, MaxButtonStringSize) == 0)
		_tcscpy(szDoNotTellAgain, _T("Don't tell me again"));
	szDoNotTellAgain[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_DONOTSHOWAGAIN, szDoNotShowAgain, MaxButtonStringSize) == 0)
		_tcscpy(szDoNotShowAgain, _T("Don't show again"));
	szDoNotShowAgain[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_HELP, szHelp, MaxButtonStringSize) == 0)
		_tcscpy(szHelp, _T("&Help"));
	szHelp[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_IGNORE, szIgnore, MaxButtonStringSize) == 0)
		_tcscpy(szIgnore, _T("&Ignore"));
	szIgnore[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_IGNOREALL, szIgnoreAll, MaxButtonStringSize) == 0)
		_tcscpy(szIgnoreAll, _T("I&gnore All"));
	szIgnoreAll[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_NO, szNo, MaxButtonStringSize) == 0)
		_tcscpy(szNo, _T("&No"));
	szNo[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_NOTOALL, szNoToAll, MaxButtonStringSize) == 0)
		_tcscpy(szNoToAll, _T("N&o to All"));
	szNoToAll[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_OK, szOK, MaxButtonStringSize) == 0)
		_tcscpy(szOK, _T("OK"));
	szOK[MaxButtonStringSize-1] = _T('\0');

	if (szReport[0] == _T('\0'))
		if (::LoadString(hInstance, IDS_REPORT, szReport, MaxButtonStringSize) == 0)
			_tcscpy(szReport, _T("Re&port"));
	szReport[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_RETRY, szRetry, MaxButtonStringSize) == 0)
		_tcscpy(szRetry, _T("&Retry"));
	szRetry[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_SKIP, szSkip, MaxButtonStringSize) == 0)
		_tcscpy(szSkip, _T("&Skip"));
	szSkip[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_SKIPALL, szSkipAll, MaxButtonStringSize) == 0)
		_tcscpy(szSkipAll, _T("S&kip All"));
	szSkipAll[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_TRYAGAIN, szTryAgain, MaxButtonStringSize) == 0)
		_tcscpy(szTryAgain, _T("&Try Again"));
	szTryAgain[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_YES, szYes, MaxButtonStringSize) == 0)
		_tcscpy(szYes, _T("&Yes"));
	szYes[MaxButtonStringSize-1] = _T('\0');

	if (::LoadString(hInstance, IDS_YESTOALL, szYesToAll, MaxButtonStringSize) == 0)
		_tcscpy(szYesToAll, _T("Y&es to All"));
	szYesToAll[MaxButtonStringSize-1] = _T('\0');
}


///////////////////////////////////////////////////////////////////////////////
// MsgBoxDlgProc
BOOL CALLBACK CXDialogTemplate::MsgBoxDlgProc(HWND hwnd,
											  UINT message,
											  WPARAM wParam,
											  LPARAM lParam)
{
	CXDialogTemplate* Me = (CXDialogTemplate*) (UINT_PTR)::GetWindowLong(hwnd, GWL_USERDATA);
	HWND hwndChild;

	switch (message)
	{
		case WM_INITDIALOG:
		{
			::SetWindowLong(hwnd, GWL_USERDATA, (LONG)lParam);	// save it for the others
			Me = (CXDialogTemplate*) lParam;
			_ASSERTE(Me);

			HDC hdc = ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
			_ASSERTE(hdc);

			::SelectObject(hdc, Me->m_hFont);
			::DeleteDC(hdc);
			UINT nID;

			for (nID = FirstControlId; nID < Me->m_nMaxID; nID++)
			{
				hwndChild = ::GetDlgItem(hwnd, nID);
				if (::IsWindow(hwndChild))
					::SendMessage(hwndChild, WM_SETFONT, (WPARAM)Me->m_hFont, 0);
				else
					break;
			}
			for (nID = 1; nID <= ID_XMESSAGEBOX_LAST_ID; nID++)
			{
				hwndChild = ::GetDlgItem(hwnd, nID);
				if (hwndChild && ::IsWindow(hwndChild))
				{
					::SendMessage(hwndChild, WM_SETFONT, (WPARAM)Me->m_hFont, 0);

					// disbale all buttons if disabled seconds specified
					if (Me->m_nDisabledSeconds)
					{
						TCHAR szClassName[MAX_PATH];
						::GetClassName(hwndChild, szClassName, countof(szClassName)-2);
						if (_tcsicmp(szClassName, _T("Button")) == 0)
						{
							LONG nStyle = ::GetWindowLong(hwndChild, GWL_STYLE);
							nStyle |= WS_DISABLED;
							::SetWindowLong(hwndChild, GWL_STYLE, nStyle);
						}
						::EnableMenuItem(GetSystemMenu(hwnd, FALSE), SC_CLOSE, MF_GRAYED);
					}
				}
			}

			hwndChild = ::GetDlgItem(hwnd, IdExHelp);
			if (hwndChild && ::IsWindow(hwndChild))
				::SendMessage(hwndChild, WM_SETFONT, (WPARAM)Me->m_hFont, 0);

			hwndChild = ::GetDlgItem(hwnd, IdDoNotAskAgian);
			if (hwndChild && ::IsWindow(hwndChild))
			{
				::SendMessage(hwndChild, WM_SETFONT, (WPARAM)Me->m_hFont, 0);
				CheckDlgButton(hwnd, IdDoNotAskAgian, 0);
			}

			hwndChild = ::GetDlgItem(hwnd, IdExReport);
			if (hwndChild && ::IsWindow(hwndChild))
				::SendMessage(hwndChild, WM_SETFONT, (WPARAM)Me->m_hFont, 0);

			hwndChild = ::GetDlgItem(hwnd, Me->m_nDefId);
			if (hwndChild && ::IsWindow(hwndChild))
				::SetFocus(hwndChild);

			// disable close button just like real MessageBox
			if (!Me->Option(CancelOrOkButton))
				::EnableMenuItem(GetSystemMenu(hwnd, FALSE), SC_CLOSE, MF_GRAYED);

			if (Me->m_hIcon)
			{
				HWND hwndIcon;

				hwndIcon = ::GetDlgItem(hwnd, 1000);
				::SetWindowLong(hwndIcon, GWL_WNDPROC, (LONG)(UINT_PTR) IconProc);
				::SetWindowLong(hwndIcon, GWL_USERDATA, (LONG)(UINT_PTR) Me->m_hIcon);
			}

			if (Me->m_nStyle & MB_TOPMOST)
				::SetWindowPos(hwnd, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE);

			if (Me->m_nStyle & MB_SETFOREGROUND)
				::SetForegroundWindow(hwnd);

			if (Me->m_X || Me->m_Y)
			{
				// caller has specified screen coordinates
				CXRect dlgRect;
				::GetWindowRect(hwnd, &dlgRect);
				::MoveWindow(hwnd, Me->m_X, Me->m_Y, dlgRect.Width(), dlgRect.Height(), TRUE);
			}
			else if (GetParent(hwnd) != NULL)
			{
				// code to center dialog (necessary if not called by MFC app)
				// [suggested by Tom Wright]
				CXRect mainRect, dlgRect;
				::GetWindowRect(::GetParent(hwnd), &mainRect);
				::GetWindowRect(hwnd, &dlgRect);
				int x = (mainRect.right  + mainRect.left)/2 - dlgRect.Width()/2;
				int y =	(mainRect.bottom + mainRect.top) /2 - dlgRect.Height()/2;
				::MoveWindow(hwnd, x, y, dlgRect.Width(), dlgRect.Height(), TRUE);
			}

			// display seconds countdown if timeout specified
			if (Me->m_nTimeoutSeconds > 0)
				::SetTimer(hwnd, 1, 1000, NULL);

			if (Me->m_nDisabledSeconds > 0)
				::SetTimer(hwnd, 2, Me->m_nDisabledSeconds*1000, NULL);

			return FALSE;
		}

		case WM_COMMAND:
		{
			// user clicked on something - stop the timer
			::KillTimer(hwnd, 1);

			if (Me->GetDefaultButtonId())
			{
				HWND hwndDefButton = ::GetDlgItem(hwnd, Me->GetDefaultButtonId());
				if (hwndDefButton && ::IsWindow(hwndDefButton))
				{
					if (Me->m_szDefaultButton[0] != _T('\0'))
					{
						::SetWindowText(hwndDefButton, Me->m_szDefaultButton);
					}
				}
			}

			switch(wParam)
			{
				case IDCLOSE:
					return TRUE;

				case IDCANCEL:
					if (Me->Option(CancelButton))
						::EndDialog(hwnd, IDCANCEL);
					else if (Me->Option(OkButton))
						::EndDialog(hwnd, IDOK);
					return TRUE;

				case IdExHelp:
				{
					TCHAR szBuf[_MAX_PATH*2];
					memset(szBuf, 0, sizeof(szBuf));
					::GetModuleFileName(NULL, szBuf, countof(szBuf) - 1);
					if (_tcslen(szBuf) > 0)
					{
						TCHAR *cp = _tcsrchr(szBuf, _T('.'));
						if (cp)
						{
							_tcscpy(cp, _T(".hlp"));
							::WinHelp(hwnd, szBuf,
								(Me->m_nHelpId == 0) ? HELP_PARTIALKEY : HELP_CONTEXT,
								Me->m_nHelpId);
						}
					}
					return FALSE;
				}

				case IdExReport:
				{
					if (Me->m_lpReportFunc)
						Me->m_lpReportFunc(Me->m_lpszMessage, Me->m_dwReportUserData);
					return FALSE;
				}

				case IdDoNotAskAgian: //IdDoNotAskAgian & DoNotTellAgain share the same id!!
					return FALSE;

				default:
					hwndChild = ::GetDlgItem(hwnd, IdDoNotAskAgian);
					BOOL bFlag = FALSE;

					if (hwndChild && ::IsWindow(hwndChild))
						bFlag = (BOOL)::SendMessage(hwndChild, BM_GETCHECK, 0, 0);

					if (Me->Option(DoNotAskAgain))
						wParam |= bFlag ? MB_DONOTASKAGAIN : 0;
					else if (Me->Option(DoNotTellAgain))
						wParam |= bFlag ? MB_DONOTTELLAGAIN : 0;
					else if (Me->Option(DoNotShowAgain))
						wParam |= bFlag ? MB_DONOTSHOWAGAIN : 0;

#ifndef XMESSAGEBOX_DO_NOT_SAVE_CHECKBOX

					// save return code in ini file if Do Not Ask style and
					// module name were specified

					if (bFlag && Me->m_lpszModule &&
						(Me->m_lpszModule[0] != _T('\0')))
					{
						TCHAR szPathName[MAX_PATH*2];

						// get full path to ini file
						szPathName[0] = _T('\0');
						::GetModuleFileName(NULL, szPathName, countof(szPathName)-1);

						TCHAR *cp = _tcsrchr(szPathName, _T('\\'));
						if (cp != NULL)
							*(cp+1) = _T('\0');
						_tcscat(szPathName, XMESSAGEBOX_INI_FILE);

						// key is module name and line
						TCHAR szKey[MAX_PATH*2];
						_tcscpy(szKey, Me->m_lpszModule);
						TRACE(_T("szKey=<%s>\n"), szKey);

						encode(szKey);		// simple encoding to obscure module name

						TCHAR szLine[100];
						szLine[0] = _T('\0');
						_tcscat(szKey, _itot(Me->m_nLine, szLine, 10));

						TRACE(_T("szKey=<%s>\n"), szKey);

#ifndef XMESSAGEBOX_USE_PROFILE_FILE

						WriteRegistry(Me->m_szCompanyName, szKey, (DWORD)wParam);

#else

						// data string is hex value of XMessageBox return code
						TCHAR szData[100];
						_stprintf(szData, _T("%08X"), wParam);


						::WritePrivateProfileString(_T("DoNotAsk"),		// section name
													szKey,				// key name
													szData,				// string to add
													szPathName);		// initialization file
#endif	// XMESSAGEBOX_USE_PROFILE_FILE



#ifdef _DEBUG
						// verify that we can read data

						DWORD dwData = 0;

#ifndef XMESSAGEBOX_USE_PROFILE_FILE

						// read from registry 

						dwData = ReadRegistry(Me->m_szCompanyName, szKey);
						TRACE(_T("dwData=0x%08X\n"), dwData);

#else
						// read from ini file

						TCHAR szBuf[100];
						::GetPrivateProfileString(_T("DoNotAsk"),	// section name
												  szKey,			// key name
												  _T(""),			// default string
												  szBuf,			// destination buffer
												  countof(szBuf)-1,	// size of destination buffer
												  szPathName);		// initialization file name

						dwData = _tcstoul(szBuf, NULL, 16);
						TRACE(_T("szBuf=<%s>  dwData=0x%08X\n"), szBuf, dwData);

#endif	// XMESSAGEBOX_USE_PROFILE_FILE

						_ASSERTE(dwData == (DWORD) wParam);

#endif	// _DEBUG
					}
#endif	// #ifndef XMESSAGEBOX_DO_NOT_SAVE_CHECKBOX

					::EndDialog(hwnd, wParam);

					return FALSE;
			}
		}

		case WM_LBUTTONDOWN:
		case WM_NCLBUTTONDOWN:
		{
			// user clicked on dialog or titlebar - stop the timer
			::KillTimer(hwnd, 1);

			if (Me->GetDefaultButtonId())
			{
				HWND hwndDefButton = ::GetDlgItem(hwnd, Me->GetDefaultButtonId());
				if (hwndDefButton && ::IsWindow(hwndDefButton))
				{
					if (Me->m_szDefaultButton[0] != _T('\0'))
					{
						::SetWindowText(hwndDefButton, Me->m_szDefaultButton);
					}
				}
			}

			return FALSE;
		}

		case WM_TIMER:		// used for timeout
		{
			TRACE(_T("in WM_TIMER\n"));

			if (wParam == 1)			// timeout timer
			{
				if (Me->m_nTimeoutSeconds <= 0)
				{
					::KillTimer(hwnd, wParam);

					// time's up, select default button
					::SendMessage(hwnd, WM_COMMAND, Me->GetDefaultButtonId() | MB_TIMEOUT, 0);

					return FALSE;
				}

				if (Me->GetDefaultButtonId() == 0)
					return FALSE;

				HWND hwndDefButton = ::GetDlgItem(hwnd, Me->GetDefaultButtonId());
				if (hwndDefButton == NULL || !::IsWindow(hwndDefButton))
					return FALSE;

				if (Me->m_szDefaultButton[0] == _T('\0'))
				{
					// first time - get text of default button
					::GetWindowText(hwndDefButton, Me->m_szDefaultButton, 
						MaxButtonStringSize);
				}

				TCHAR szButtonText[MaxButtonStringSize*2];
				_stprintf(szButtonText, XMESSAGEBOX_TIMEOUT_TEXT_FORMAT, 
					Me->m_szDefaultButton, Me->m_nTimeoutSeconds);

				::SetWindowText(hwndDefButton, szButtonText);

				Me->m_nTimeoutSeconds--;
			}
			else if (wParam == 2)		// disabled timer
			{
				::KillTimer(hwnd, wParam);

				for (UINT nID = 1; nID <= ID_XMESSAGEBOX_LAST_ID; nID++)
				{
					hwndChild = ::GetDlgItem(hwnd, nID);
					if (hwndChild && ::IsWindow(hwndChild))
					{
						// enable all buttons
						TCHAR szClassName[MAX_PATH];
						::GetClassName(hwndChild, szClassName, countof(szClassName)-2);
						if (_tcsicmp(szClassName, _T("Button")) == 0)
						{
							LONG nStyle = ::GetWindowLong(hwndChild, GWL_STYLE);
							nStyle &= ~WS_DISABLED;
							::SetWindowLong(hwndChild, GWL_STYLE, nStyle);
						}
					}
				} // for

				if (Me->Option(CancelOrOkButton))
					::EnableMenuItem(GetSystemMenu(hwnd, FALSE), SC_CLOSE, MF_ENABLED);

				::RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW);
			}
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// CXDialogTemplate::AddItem
void CXDialogTemplate::AddItem(CXDialogItem::Econtroltype cType,
							   UINT nID,
							   CXRect* prect,
							   LPCTSTR pszCaption)
{
	_ASSERTE(m_pDlgItemArray[m_dlgTempl.cdit] == NULL);

	CXDialogItem::Econtroltype ct = cType;

	if (ct == CXDialogItem::CHECKBOX)
		ct = CXDialogItem::BUTTON;

	m_pDlgItemArray[m_dlgTempl.cdit] = new CXDialogItem(ct);
	_ASSERTE(m_pDlgItemArray[m_dlgTempl.cdit]);

	m_pDlgItemArray[m_dlgTempl.cdit]->AddItem(*this, cType, nID, prect, pszCaption);

	m_dlgTempl.cdit++;
	_ASSERTE(m_dlgTempl.cdit < MaxItems);
}

///////////////////////////////////////////////////////////////////////////////
// CXDialogTemplate::Display
int CXDialogTemplate::Display()
{
	// The first step is to allocate memory to define the dialog. The information to be
	// stored in the allocated buffer is the following:
	//
	// 1. DLGTEMPLATE structure
	//    typedef struct
	//    {
	//       DWORD style;
	//       DWORD dwExtendedStyle;
	//       WORD cdit;
	//       short x;
	//       short y;
	//       short cx;
	//       short cy;
	//    } DLGTEMPLATE;
	// 2. 0x0000 (Word) indicating the dialog has no menu
	// 3. 0x0000 (Word) Let windows assign default class to the dialog
	// 4. (Caption) Null terminated unicode string
	// 5. 0x000B (size of the font to be used)
	// 6. "MS Sans Serif" (name of the typeface to be used)
	// 7. DLGITEMTEMPLATE structure for the button (HAS TO BE DWORD ALIGNED)
	//    typedef struct
	//    {
	//       DWORD style;
	//       DWORD dwExtendedStyle;
	//       short x;
	//       short y;
	//       short cx;
	//       short cy;
	//       WORD id;
	//    } DLGITEMTEMPLATE;
	// 8. 0x0080 to indicate the control is a button
	// 9. (Title). Unicode null terminated string with the caption
	// 10. 0x0000 0 extra bytes of data for this control
	// 11. DLGITEMTEMPLATE structure for the Static Text (HAS TO BE DWORD ALIGNED)
	// 12. 0x0081 to indicate the control is static text
	// 13. (Title). Unicode null terminated string with the text
	// 14. 0x0000. 0 extra bytes of data for this control


	int rc = IDCANCEL;

	TCHAR szTitle[1024];
	_tcsncpy(szTitle, m_lpszCaption, countof(szTitle)-1);
	szTitle[countof(szTitle)-1] = _T('\0');
	size_t nTitleLen = _tcslen(szTitle);

	int i = 0;

	size_t nBufferSize = sizeof(DLGTEMPLATE) +
		(2 * sizeof(WORD)) + // menu and class
		((nTitleLen + 1) * sizeof(WCHAR));

	// NOTE - font is set in MsgBoxDlgProc

	nBufferSize = (nBufferSize + 3) & ~3; // adjust size to make
	// first control DWORD aligned

	// loop to calculate size of buffer we need -
	// add size of each control:
	// sizeof(DLGITEMTEMPLATE) +
	// sizeof(WORD) + // atom value flag 0xFFFF
	// sizeof(WORD) + // ordinal value of control's class
	// sizeof(WORD) + // no. of bytes in creation data array
	// sizeof title in WCHARs
	for (i = 0; i < m_dlgTempl.cdit; i++)
	{
		size_t nItemLength = sizeof(DLGITEMTEMPLATE) + 3 * sizeof(WORD);

#ifdef _UNICODE
		size_t nActualChars = _tcslen(m_pDlgItemArray[i]->m_pszCaption) + 1;	//+++1.5;
#else
		int nActualChars = MultiByteToWideChar(CP_ACP, 0,
								(LPCSTR)m_pDlgItemArray[i]->m_pszCaption, 
								-1, NULL, 0);	//+++1.5
#endif

		ASSERT(nActualChars > 0);
		nItemLength += nActualChars * sizeof(WCHAR);

		if (i != m_dlgTempl.cdit - 1) // the last control does not need extra bytes
		{
			nItemLength = (nItemLength + 3) & ~3; // take into account gap
		} // so next control is DWORD aligned

		nBufferSize += nItemLength;
	}

	HLOCAL hLocal = LocalAlloc(LHND, nBufferSize);
	_ASSERTE(hLocal);
	if (hLocal == NULL)
		return IDCANCEL;

	BYTE* pBuffer = (BYTE*)LocalLock(hLocal);
	_ASSERTE(pBuffer);
	if (pBuffer == NULL)
	{
		LocalFree(hLocal);
		return IDCANCEL;
	}

	BYTE* pdest = pBuffer;

	// transfer DLGTEMPLATE structure to the buffer
	memcpy(pdest, &m_dlgTempl, sizeof(DLGTEMPLATE));
	pdest += sizeof(DLGTEMPLATE);

	*(WORD*)pdest = 0;		// no menu
	pdest += sizeof(WORD);	//+++1.5
	*(WORD*)pdest = 0;		// use default window class		//+++1.5
	pdest += sizeof(WORD);	//+++1.5

	// transfer title
	WCHAR * pchCaption = new WCHAR[nTitleLen + 100];
	memset(pchCaption, 0, nTitleLen*2 + 2);

#ifdef _UNICODE
	memcpy(pchCaption, szTitle, nTitleLen * sizeof(TCHAR));
	size_t nActualChars = nTitleLen + 1;
#else
	size_t nActualChars = MultiByteToWideChar(CP_ACP, 0,
			(LPCSTR)szTitle, -1, pchCaption, nTitleLen + 1);
#endif

	_ASSERTE(nActualChars > 0);
	memcpy(pdest, pchCaption, nActualChars * sizeof(WCHAR));
	pdest += nActualChars * sizeof(WCHAR);
	delete [] pchCaption;		//+++1.5

	// will now transfer the information for each one of the item templates
	for (i = 0; i < m_dlgTempl.cdit; i++)
	{
		pdest = (BYTE*)(((UINT_PTR)pdest + 3) & ~3);	// make the pointer DWORD aligned
		memcpy(pdest, (void *)&m_pDlgItemArray[i]->m_dlgItemTemplate,
			sizeof(DLGITEMTEMPLATE));
		pdest += sizeof(DLGITEMTEMPLATE);
		*(WORD*)pdest = 0xFFFF;						// indicating atom value
		pdest += sizeof(WORD);
		*(WORD*)pdest = (WORD)m_pDlgItemArray[i]->m_controltype;	// atom value for the control
		pdest += sizeof(WORD);

		// transfer the caption even when it is an empty string

		size_t nChars = _tcslen(m_pDlgItemArray[i]->m_pszCaption) + 1;	//+++1.5

		WCHAR * pchCaption = new WCHAR[nChars+100];

#ifdef _UNICODE
		memset(pchCaption, 0, nChars*sizeof(TCHAR) + 2);
		memcpy(pchCaption, m_pDlgItemArray[i]->m_pszCaption, nChars * sizeof(TCHAR));	//+++1.5
		size_t nActualChars = nChars;
#else
		size_t nActualChars = MultiByteToWideChar(CP_ACP, 0,
			(LPCSTR)m_pDlgItemArray[i]->m_pszCaption, -1, pchCaption, nChars);	//+++1.5
#endif

		_ASSERTE(nActualChars > 0);
		memcpy(pdest, pchCaption, nActualChars * sizeof(WCHAR));
		pdest += nActualChars * sizeof(WCHAR);
		delete [] pchCaption;	//+++1.5

		*(WORD*)pdest = 0; // How many bytes in data for control
		pdest += sizeof(WORD);
	}

	_ASSERTE((size_t)(pdest - pBuffer) <= nBufferSize); //+++1.5 // just make sure we did not overrun the heap
	HINSTANCE hInstance = GetModuleHandle(NULL);

	rc = ::DialogBoxIndirectParam(hInstance, (LPCDLGTEMPLATE) pBuffer, m_hWnd, 
				MsgBoxDlgProc, (LPARAM)this);

	LocalUnlock(hLocal);
	LocalFree(hLocal);

	return rc;
}


///////////////////////////////////////////////////////////////////////////////
// CXDialogItem class

///////////////////////////////////////////////////////////////////////////////
// CXDialogItem ctor
CXDialogItem::CXDialogItem(CXDialogItem::Econtroltype ctrlType) :
	m_controltype(ctrlType),
	m_pszCaption(NULL)		//+++1.5
{
}

///////////////////////////////////////////////////////////////////////////////
// CXDialogItem dtor
CXDialogItem::~CXDialogItem()
{
	if (m_pszCaption)
		delete [] m_pszCaption;
}

///////////////////////////////////////////////////////////////////////////////
// CXDialogItem::AddItem
void CXDialogItem::AddItem(CXDialogTemplate& dialog,
						   Econtroltype ctrltype,
						   UINT nID,
						   CXRect* prect,
						   LPCTSTR lpszCaption)
{
	short hidbu = HIWORD(GetDialogBaseUnits());
	short lodbu = LOWORD(GetDialogBaseUnits());

	// first fill in the type, location and size of the control
	m_controltype = ctrltype;

	if (m_controltype == CHECKBOX)
		m_controltype = BUTTON;

	if (prect != NULL)
	{
		m_dlgItemTemplate.x = (short)((prect->left * 4) / lodbu);
		m_dlgItemTemplate.y = (short)((prect->top * 8) / hidbu);
		m_dlgItemTemplate.cx = (short)((prect->Width() * 4) / lodbu);
		m_dlgItemTemplate.cy = (short)((prect->Height() * 8) / hidbu);
	}
	else
	{
		m_dlgItemTemplate.x = 0;
		m_dlgItemTemplate.y = 0;
		m_dlgItemTemplate.cx = 10; // some useless default
		m_dlgItemTemplate.cy = 10;
	}

	m_dlgItemTemplate.dwExtendedStyle = 0;
	m_dlgItemTemplate.id = (WORD)nID;

	switch (ctrltype)
	{
		case ICON:
			m_dlgItemTemplate.style = WS_CHILD | SS_ICON | WS_VISIBLE;
			break;

		case BUTTON:
			dialog.GetButtonCount()++;
			m_dlgItemTemplate.style = WS_VISIBLE | WS_CHILD | WS_TABSTOP;
			if (dialog.GetButtonCount() == dialog.GetDefaultButton())
			{
				m_dlgItemTemplate.style |= BS_DEFPUSHBUTTON;
				dialog.SetDefaultButtonId(nID);
			}
			else
			{
				m_dlgItemTemplate.style |= BS_PUSHBUTTON;
			}
			break;

		case CHECKBOX:
			m_dlgItemTemplate.style = WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTOCHECKBOX;
			break;

		case EDITCONTROL:
			m_dlgItemTemplate.style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_MULTILINE | ES_LEFT;
			break;

		case STATICTEXT:
			m_dlgItemTemplate.style = WS_CHILD | WS_VISIBLE | SS_LEFT;
			break;

		default:
			_ASSERTE(FALSE); // should never get here
	}

	//_tcsncpy(m_szCaption, lpszCaption ? lpszCaption : _T(""), countof(m_szCaption)- 1);
	//m_szCaption[countof(m_szCaption)-1] = _T('\0');

	size_t stringLength = lpszCaption ? _tcslen(lpszCaption) : 0;	//+++1.5
	m_pszCaption = new TCHAR [stringLength + 1];				//+++1.5
	_tcscpy(m_pszCaption, lpszCaption ? lpszCaption : _T(""));	//+++1.5
}

#ifndef XMESSAGEBOX_DO_NOT_SAVE_CHECKBOX
#ifndef XMESSAGEBOX_USE_PROFILE_FILE

static DWORD ReadRegistry(LPCTSTR lpszCompanyName, LPCTSTR lpszKey)
{
	_ASSERTE((lpszKey != NULL) && (lpszKey[0] != _T('\0')));
	if (!lpszKey || lpszKey[0] == _T('\0'))
		return 0;

	TCHAR * szRegPath = _T("Software\\");

	TCHAR szKey[_MAX_PATH*2];
	memset(szKey, 0, _MAX_PATH*2*sizeof(TCHAR));
	_tcscpy(szKey, szRegPath);

	if (lpszCompanyName && lpszCompanyName[0] != _T('\0'))
	{
		_tcscat(szKey, lpszCompanyName);
		_tcscat(szKey, _T("\\"));
	}

	TCHAR szPathName[_MAX_PATH*2];
	memset(szPathName, 0, _MAX_PATH*2*sizeof(TCHAR));
	::GetModuleFileName(NULL, szPathName, MAX_PATH*2-2);

	TCHAR *cp = _tcsrchr(szPathName, _T('\\'));
	if (cp == NULL)
		cp = szPathName;
	else
		cp++;

	_tcscat(szKey, cp);

	_tcscat(szKey, _T("\\"));
	_tcscat(szKey, XMESSAGEBOX_REGISTRY_KEY);

	TRACE(_T("szKey=<%s>\n"), szKey);

	// open the registry event source key
	DWORD dwData = 0;
	HKEY hKey = NULL;
	TRACE(_T("trying to open key\n"));
	LONG lRet = ::RegOpenKeyEx(HKEY_CURRENT_USER, szKey, 0, KEY_READ, &hKey);

	if (lRet == ERROR_SUCCESS)
	{
		// registry key was opened or created -
		TRACE(_T("key opened ok\n"));

		// === write EventMessageFile key ===
		DWORD dwType = 0;
		DWORD dwSize = sizeof(DWORD);
		lRet = ::RegQueryValueEx(hKey, lpszKey, 0, &dwType, (LPBYTE) &dwData, &dwSize);

		::RegCloseKey(hKey);

		if (lRet != ERROR_SUCCESS)
			dwData = 0;
	}
	else
	{
		dwData = 0;
	}

	return dwData;
}

static void WriteRegistry(LPCTSTR lpszCompanyName, LPCTSTR lpszKey, DWORD dwData)
{
	_ASSERTE((lpszKey != NULL) && (lpszKey[0] != _T('\0')));
	if (!lpszKey || lpszKey[0] == _T('\0'))
		return;

	TCHAR * szRegPath = _T("Software\\");

	TCHAR szKey[_MAX_PATH*2];
	memset(szKey, 0, _MAX_PATH*2*sizeof(TCHAR));
	_tcscpy(szKey, szRegPath);

	if (lpszCompanyName && lpszCompanyName[0] != _T('\0'))
	{
		_tcscat(szKey, lpszCompanyName);
		_tcscat(szKey, _T("\\"));
	}

	TCHAR szPathName[_MAX_PATH*2];
	memset(szPathName, 0, _MAX_PATH*2*sizeof(TCHAR));
	::GetModuleFileName(NULL, szPathName, MAX_PATH*2-2);

	TCHAR *cp = _tcsrchr(szPathName, _T('\\'));
	if (cp == NULL)
		cp = szPathName;
	else
		cp++;

	_tcscat(szKey, cp);

	_tcscat(szKey, _T("\\"));
	_tcscat(szKey, XMESSAGEBOX_REGISTRY_KEY);

	TRACE(_T("szKey=<%s>\n"), szKey);

	// open the registry key
	DWORD dwResult = 0;
	HKEY hKey = NULL;
	LONG lRet = ::RegCreateKeyEx(HKEY_CURRENT_USER, szKey, 0, NULL,
					REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwResult);

	if (lRet == ERROR_SUCCESS)
	{
		// registry key was opened or created -

		::RegSetValueEx(hKey, lpszKey, 0, REG_DWORD,
			(const BYTE *) &dwData, sizeof(DWORD));

		::RegCloseKey(hKey);
	}

	return;
}

#endif	// XMESSAGEBOX_USE_PROFILE_FILE
#endif	// XMESSAGEBOX_DO_NOT_SAVE_CHECKBOX

