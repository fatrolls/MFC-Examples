// ScreenGrabber.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ScreenGrabber.h"

#include "PropertySheetCapture.h"
#include "PropertyPageActivation.h"
#include "PropertyPageSource.h"
#include "PropertyPageDestination.h"
#include "PropertyPageImage.h"
#include "PropertyPageFile.h"
#include "PropertyPagePreferences.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenGrabberApp

BEGIN_MESSAGE_MAP(CScreenGrabberApp, CWinApp)
	//{{AFX_MSG_MAP(CScreenGrabberApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScreenGrabberApp construction

CScreenGrabberApp::CScreenGrabberApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CScreenGrabberApp object

CScreenGrabberApp theApp;
static HINSTANCE g_hRichEdDLL=NULL;

/////////////////////////////////////////////////////////////////////////////
// CScreenGrabberApp initialization

BOOL CScreenGrabberApp::InitInstance()
{
	// Initialize RichEdit control
	// for About Dialog
	if(g_hRichEdDLL==NULL)
	{
		g_hRichEdDLL=::LoadLibrary(_T("RICHED32.DLL"));
		if(g_hRichEdDLL==NULL)
			TRACE(_T("Cannot load library to display RichEditTextControl"));
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif


	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Ultimate Toolbox Samples"));

	// initialize application variables using values from Registry
	IniAppVars();

	if(!m_wndInvisible.CreateEx(0, AfxRegisterWndClass(0), _T(""), 0, 0, 0, 0, 0, NULL, 0))
	{
		TRACE(_T("CScreenGrabberApp::InitInstance: failed to create invisible window"));
		return FALSE;
	}

	CPropertySheetCapture dlgPropertySheet(AFX_IDS_APP_TITLE,&m_wndInvisible);

	// change property sheet properties
	// to show icon and remove Apply Now button
	HICON hIcon=LoadIcon(IDR_MAINFRAME);
	dlgPropertySheet.m_psh.dwFlags|=PSH_NOAPPLYNOW;
	dlgPropertySheet.m_psh.dwFlags|=PSH_USEHICON;
	dlgPropertySheet.m_psh.hIcon=hIcon;

	CPropertyPageActivation pageActivation;
	CPropertyPageSource pageSource;
	CPropertyPageDestination pageDestination;
	CPropertyPageImage pageImage;
	CPropertyPageFile pageFile;
	CPropertyPagePreferences pagePreferences;

	dlgPropertySheet.AddPage(&pageActivation);
	dlgPropertySheet.AddPage(&pageSource);
	dlgPropertySheet.AddPage(&pageDestination);
	dlgPropertySheet.AddPage(&pageImage);
	dlgPropertySheet.AddPage(&pageFile);
	dlgPropertySheet.AddPage(&pagePreferences);

	m_pMainWnd = &dlgPropertySheet;


	// Initialize vars
	pageActivation.m_sHotKey=m_sHotKey;
	pageActivation.m_nInitialDelay=m_nInitialDelay;
	pageActivation.m_bInitialDelay=m_bInitialDelay;

	pageSource.m_nRadioCapturedArea=m_nRadioCapturedArea;

	pageDestination.m_bClipboard=m_bClipboard;
	pageDestination.m_bFile=m_bFile;

	pageImage.m_bMaintainRatio=m_bMaintainRatio;
	pageImage.m_bResize=m_bResize;
	pageImage.m_nHeight=m_nHeight;
	pageImage.m_nWidth=m_nWidth;

	pageFile.m_bAutomaticNaming=m_bAutomaticNaming;
	pageFile.m_sFileName=m_sFileName;
	pageFile.m_sFileType=m_sFileType;
	pageFile.m_sCaptureDir=m_sCaptureDir;

	pagePreferences.m_bHideIcon=m_bHideIcon;
	pagePreferences.m_bNotifyEnd=m_bNotifyEnd;

	switch(dlgPropertySheet.DoModal())
	{
	case IDOK:
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
		break;
	case IDCANCEL:
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
		break;
	}

	// Copy vars
	m_sHotKey=pageActivation.m_sHotKey;
	m_nInitialDelay=pageActivation.m_nInitialDelay;
	m_bInitialDelay=pageActivation.m_bInitialDelay;

	m_nRadioCapturedArea=pageSource.m_nRadioCapturedArea;

	m_bClipboard=pageDestination.m_bClipboard;
	m_bFile=pageDestination.m_bFile;

	m_bMaintainRatio=pageImage.m_bMaintainRatio;
	m_bResize=pageImage.m_bResize;
	m_nHeight=pageImage.m_nHeight;
	m_nWidth=pageImage.m_nWidth;

	m_bAutomaticNaming=pageFile.m_bAutomaticNaming;
	m_sFileName=pageFile.m_sFileName;
	m_sFileType=pageFile.m_sFileType;
	m_sCaptureDir=pageFile.m_sCaptureDir;

	m_bHideIcon=pagePreferences.m_bHideIcon;
	m_bNotifyEnd=pagePreferences.m_bNotifyEnd;

	// save application variables to Registry
	SaveAppVars();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CScreenGrabberApp::IniAppVars() 
{
	m_sHotKey=GetProfileString(_T("Activation"),_T("HotKey"),_T("F7"));
	m_nInitialDelay=GetProfileInt(_T("Activation"),_T("InitialDelay"),5);
	m_bInitialDelay=GetProfileInt(_T("Activation"),
		_T("SetInitialDelay"),TRUE);

	m_nRadioCapturedArea=GetProfileInt(_T("Source"),_T("CapturedArea"),0);

	m_bClipboard=GetProfileInt(_T("Destination"),_T("Clipboard"),FALSE);
	m_bFile=GetProfileInt(_T("Destination"),_T("File"),TRUE);

	m_bMaintainRatio=GetProfileInt(_T("Image"),_T("MaintainRatio"),TRUE);
	m_bResize=GetProfileInt(_T("Image"),_T("Resize"),FALSE);
	m_nHeight=GetProfileInt(_T("Image"),_T("Height"),
		::GetSystemMetrics(SM_CYSCREEN));
	m_nWidth=GetProfileInt(_T("Image"),_T("Width"),
		::GetSystemMetrics(SM_CXSCREEN));

	m_bAutomaticNaming=GetProfileInt(_T("File"),_T("AutomaticNaming"),FALSE);
	m_sFileName=GetProfileString(_T("File"),_T("FileName"),_T("ScreenShot"));
	m_sFileType=GetProfileString(_T("File"),_T("FileType"),_T("Windows Bitmap (*.bmp)"));
	/// set as default directory the current one
	CString sCurDir;
	LPTSTR sBuffer=sCurDir.GetBuffer(_MAX_PATH);
	GetCurrentDirectory(_MAX_PATH,sBuffer);
	sCurDir.ReleaseBuffer();
	///
	m_sCaptureDir=GetProfileString(_T("File"),_T("CaptureDir"),sCurDir);

	m_bHideIcon=GetProfileInt(_T("Prefences"),_T("HideIcon"),FALSE);
	m_bNotifyEnd=GetProfileInt(_T("Prefences"),_T("NotifyEnd"),TRUE);
}

void CScreenGrabberApp::SaveAppVars() 
{
	WriteProfileString(_T("Activation"),_T("HotKey"),m_sHotKey);
	WriteProfileInt(_T("Activation"),_T("InitialDelay"),m_nInitialDelay);
	WriteProfileInt(_T("Activation"),_T("SetInitialDelay"),
		m_bInitialDelay);

	WriteProfileInt(_T("Source"),_T("CapturedArea"),m_nRadioCapturedArea);

	WriteProfileInt(_T("Destination"),_T("Clipboard"),m_bClipboard);
	WriteProfileInt(_T("Destination"),_T("File"),m_bFile);

	WriteProfileInt(_T("Image"),_T("MaintainRatio"),m_bMaintainRatio);
	WriteProfileInt(_T("Image"),_T("Resize"),m_bResize);
	WriteProfileInt(_T("Image"),_T("Height"),m_nHeight);
	WriteProfileInt(_T("Image"),_T("Width"),m_nWidth);

	WriteProfileInt(_T("File"),_T("AutomaticNaming"),m_bAutomaticNaming);
	WriteProfileString(_T("File"),_T("FileName"),m_sFileName);
	WriteProfileString(_T("File"),_T("FileType"),m_sFileType);
	WriteProfileString(_T("File"),_T("CaptureDir"),m_sCaptureDir);

	WriteProfileInt(_T("Prefences"),_T("HideIcon"),m_bHideIcon);
	WriteProfileInt(_T("Prefences"),_T("NotifyEnd"),m_bNotifyEnd);
}


int CScreenGrabberApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);

	return CWinApp::ExitInstance();
}
