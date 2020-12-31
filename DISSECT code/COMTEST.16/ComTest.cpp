// ComTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ComTest.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "ComTestDoc.h"
#include "ComTestView.h"
#include "Splash.h"
#include <dos.h>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComTestApp

BEGIN_MESSAGE_MAP(CComTestApp, CWinApp)
	ON_COMMAND(CG_IDS_TIPOFTHEDAY, ShowTipOfTheDay)
        //{{AFX_MSG_MAP(CComTestApp)
        ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
                // NOTE - the ClassWizard will add and remove mapping macros here.
                //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
        // Standard file based document commands
        ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
        ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
        // Standard print setup command
        ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComTestApp construction

CComTestApp::CComTestApp()
{
        // TODO: add construction code here,
        // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CComTestApp object

CComTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CComTestApp initialization

BOOL CComTestApp::InitInstance()
{
        // CG: The following block was added by the Splash Screen component.
\
 {
\
            CCommandLineInfo cmdInfo;
\
            ParseCommandLine(cmdInfo);
\

\
                CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
       }
        AfxEnableControlContainer();

        // Standard initialization
        // If you are not using these features and wish to reduce the size
        //  of your final executable, you should remove from the following
        //  the specific initialization routines you do not need.

#ifdef _AFXDLL
        Enable3dControls();                     // Call this when using MFC in a shared DLL
#else
        Enable3dControlsStatic();       // Call this when linking to MFC statically
#endif

        // Change the registry key under which our settings are stored.
        // You should modify this string to be something appropriate
        // such as the name of your company or organization.
        SetRegistryKey(_T("Local AppWizard-Generated Applications"));

        LoadStdProfileSettings();  // Load standard INI file options (including MRU)

        // Register the application's document templates.  Document templates
        //  serve as the connection between documents, frame windows and views.

        CMultiDocTemplate* pDocTemplate;
        pDocTemplate = new CMultiDocTemplate(
                IDR_COMTESTYPE,
                RUNTIME_CLASS(CComTestDoc),
                RUNTIME_CLASS(CChildFrame), // custom MDI child frame
                RUNTIME_CLASS(CComTestView));
        AddDocTemplate(pDocTemplate);

        // create main MDI Frame window
        CMainFrame* pMainFrame = new CMainFrame;
        if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
                return FALSE;
        m_pMainWnd = pMainFrame;

        // Parse command line for standard shell commands, DDE, file open
        CCommandLineInfo cmdInfo;
        ParseCommandLine(cmdInfo);

        // Dispatch commands specified on the command line
        if (!ProcessShellCommand(cmdInfo))
                return FALSE;

        // The main window has been initialized, so show and update it.
        pMainFrame->ShowWindow(m_nCmdShow);
        pMainFrame->UpdateWindow();

	// CG: This line inserted by 'Tip of the Day' component.
	ShowTipAtStartup();

        return TRUE;
}

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
        virtual BOOL OnInitDialog();
        //{{AFX_MSG(CAboutDlg)
                // No message handlers
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

// App command to run the dialog
void CComTestApp::OnAppAbout()
{
        CAboutDlg aboutDlg;
        aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CComTestApp commands

BOOL CComTestApp::PreTranslateMessage(MSG* pMsg)
{
        // CG: The following lines were added by the Splash Screen component.
  if (CSplashWnd::PreTranslateAppMessage(pMsg))
          return TRUE;

  return CWinApp::PreTranslateMessage(pMsg);
}

BOOL CAboutDlg::OnInitDialog()
{
        CDialog::OnInitDialog();        // CG:  This was added by System Info Component.

        // CG: Following block was added by System Info Component.
        {
                CString strFreeDiskSpace;
                CString strFreeMemory;
                CString strFmt;

                // Fill available memory
                MEMORYSTATUS MemStat;
                MemStat.dwLength = sizeof(MEMORYSTATUS);
                GlobalMemoryStatus(&MemStat);
                strFmt.LoadString(CG_IDS_PHYSICAL_MEM);
                strFreeMemory.Format(strFmt, MemStat.dwTotalPhys / 1024L);

                //TODO: Add a static control to your About Box to receive the memory
                //      information.  Initialize the control with code like this:
                SetDlgItemText(IDC_PHYSICAL_MEM, strFreeMemory);

                // Fill disk free information
                struct _diskfree_t diskfree;
                int nDrive = _getdrive(); // use current default drive
                if (_getdiskfree(nDrive, &diskfree) == 0)
                {
                        strFmt.LoadString(CG_IDS_DISK_SPACE);
                        strFreeDiskSpace.Format(strFmt,
                                (DWORD)diskfree.avail_clusters *
                                (DWORD)diskfree.sectors_per_cluster *
                                (DWORD)diskfree.bytes_per_sector / (DWORD)1024L,
                                nDrive-1 + _T('A'));
                }
                else
                        strFreeDiskSpace.LoadString(CG_IDS_DISK_SPACE_UNAVAIL);

                //TODO: Add a static control to your About Box to receive the memory
                //      information.  Initialize the control with code like this:
                SetDlgItemText(IDC_DISK_SPACE, strFreeDiskSpace);
        }

        return TRUE;    // CG:  This was added by System Info Component.

}

void CComTestApp::ShowTipAtStartup(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_bShowSplash)
	{
		CTipDlg dlg;
		if (dlg.m_bStartup)
			dlg.DoModal();
	}

}

void CComTestApp::ShowTipOfTheDay(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CTipDlg dlg;
	dlg.DoModal();

}
