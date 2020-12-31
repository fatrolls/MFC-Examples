// $$root$$.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "$$root$$.h"

#include "$$frame_hfile$$.h"
$$IF(MDICHILD)
#include "$$child_frame_hfile$$.h"
$$ENDIF //MDICHILD
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
#include "$$ipframe_hfile$$.h"
$$ENDIF
$$IF(CRecordView || CDaoRecordView)
#include "$$recset_hfile$$.h"
$$ENDIF
#include "$$doc_hfile$$.h"
#include "$$view_hfile$$.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$APP_CLASS$$

BEGIN_MESSAGE_MAP($$APP_CLASS$$, $$APP_BASE_CLASS$$)
	//{{AFX_MSG_MAP($$APP_CLASS$$)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
$$ENDIF
	//}}AFX_MSG_MAP
$$IF(!DB_NO_FILE)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, $$APP_BASE_CLASS$$::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, $$APP_BASE_CLASS$$::OnFileOpen)
$$ENDIF //!DB_NO_FILE
$$IF(PRINT)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, $$APP_BASE_CLASS$$::OnFilePrintSetup)
$$ENDIF //PRINT
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// $$APP_CLASS$$ construction

$$APP_CLASS$$::$$APP_CLASS$$()
{
$$IF(VERBOSE)
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
$$ENDIF
}

/////////////////////////////////////////////////////////////////////////////
// The one and only $$APP_CLASS$$ object

$$APP_CLASS$$ theApp;
$$IF(FULL_SERVER || MINI_SERVER || CONTAINER_SERVER || AUTOMATION)

$$IF(VERBOSE)
// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {$$APP_CLSID_REG$$}
$$ENDIF
static const CLSID clsid =
$$APP_CLSID$$;
$$ENDIF

/////////////////////////////////////////////////////////////////////////////
// $$APP_CLASS$$ initialization

BOOL $$APP_CLASS$$::InitInstance()
{
$$IF(SOCKETS)
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

$$ENDIF //SOCKETS
$$IF(CONTAINER || CONTAINER_SERVER || MINI_SERVER || FULL_SERVER || AUTOMATION)
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

$$ENDIF //CONTAINER || CONTAINER_SERVER || MINI_SERVER || FULL_SERVER || AUTOMATION
$$IF(OLECTL)
	AfxEnableControlContainer();

$$ENDIF //OLECTL
	// Standard initialization
$$IF(VERBOSE)
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
$$ENDIF
$$IF(3D)

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
$$ENDIF //3D

	// Change the registry key under which our settings are stored.
$$IF(VERBOSE)
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
$$ENDIF
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings($$SIZE_MRU$$);  // Load standard INI file options (including MRU)

$$IF(VERBOSE)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
$$ELSE
	// Register document templates
$$ENDIF
$$IF(PROJTYPE_MDI)

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_$$DOC$$TYPE,
$$ELSE

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
$$ENDIF
		RUNTIME_CLASS($$DOC_CLASS$$),
$$IF(PROJTYPE_MDI)
$$IF(MDICHILD)
		RUNTIME_CLASS($$CHILD_FRAME_CLASS$$), // custom MDI child frame
$$ELSE //!MDICHILD
		RUNTIME_CLASS(CMDIChildWnd),          // standard MDI child frame
$$ENDIF //MDICHILD
$$ELSE //!MDI
		RUNTIME_CLASS($$FRAME_CLASS$$),       // main SDI frame window
$$ENDIF
		RUNTIME_CLASS($$VIEW_CLASS$$));
$$IF(CONTAINER || CONTAINER_SERVER)
$$IF(PROJTYPE_MDI)
	pDocTemplate->SetContainerInfo(IDR_$$DOC$$TYPE_CNTR_IP);
$$ELSE
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
$$ENDIF
$$ENDIF
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
	pDocTemplate->SetServerInfo(
$$IF(PROJTYPE_MDI)
		IDR_$$DOC$$TYPE_SRVR_EMB, IDR_$$DOC$$TYPE_SRVR_IP,
$$ELSE
		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
$$ENDIF
		RUNTIME_CLASS($$IPFRAME_CLASS$$));
$$ENDIF
	AddDocTemplate(pDocTemplate);
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER || AUTOMATION)
$$IF(VERBOSE)

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
$$ENDIF
$$IF(PROJTYPE_MDI)
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

$$IF(VERBOSE)
	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
$$ENDIF
	COleTemplateServer::RegisterAll();
$$IF(VERBOSE)
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.
$$ENDIF
$$ELSE //!MDI
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);
$$IF(VERBOSE)
		// Note: SDI applications register server objects only if /Embedding
		//   or /Automation is present on the command line.
$$ENDIF
$$ENDIF
$$ENDIF

$$IF(PROJTYPE_MDI)
	// create main MDI Frame window
	$$FRAME_CLASS$$* pMainFrame = new $$FRAME_CLASS$$;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

$$IF(!MINI_SERVER)
$$// call DragAcceptFiles only if compiling for Mac, or if there's a suffix.
$$//  In an MDI app, this should occur immediately after setting m_pMainWnd
$$IF(HAS_SUFFIX)
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

$$ELIF(INSTALLED_MAC)
#ifdef _MAC
	// Enable drag/drop open.  We don't call this in Win32, since a
	//  document file extension wasn't chosen while running AppWizard.
	m_pMainWnd->DragAcceptFiles();
#endif

$$ENDIF //SUFFIX/INSTALLED_MAC
$$ENDIF //!MINI_SERVER
$$ENDIF //MDI
$$IF(!MINI_SERVER)
$$IF(HAS_SUFFIX)
	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

$$ENDIF //SUFFIX
$$ENDIF //!MINI_SERVER
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER || AUTOMATION)
$$IF(VERBOSE)
	// Check to see if launched as OLE server
$$ENDIF
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
$$IF(!PROJTYPE_MDI)
$$IF(VERBOSE)
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
$$ENDIF //VERBOSE
		COleTemplateServer::RegisterAll();

$$ENDIF //!MDI
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

$$IF(VERBOSE)
	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
$$ENDIF
$$IF(MINI_SERVER || FULL_SERVER || CONTAINER_SERVER)
$$IF(ACTIVE_DOC_SERVER)
	m_server.UpdateRegistry(OAT_DOC_OBJECT_SERVER);
$$ELSE
	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
$$ENDIF	// ACTIVE_DOC_SERVER
$$ELIF(AUTOMATION)
	m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
$$ENDIF
$$IF(AUTOMATION)
	COleObjectFactory::UpdateRegistryAll();
$$ENDIF

$$ENDIF //MINI_SERVER || FULL_SERVER || CONTAINER_SERVER || AUTOMATION
$$IF(MINI_SERVER)
$$IF(VERBOSE)
	// When a mini-server is run stand-alone the registry is updated and the
	//  user is instructed to use the Insert Object dialog in a container
	//  to use the server.  Mini-servers do not have stand-alone user interfaces.
$$ENDIF //VERBOSE
	AfxMessageBox(IDP_USE_INSERT_OBJECT);
	return FALSE;
$$ELSE //!MINI_SERVER
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
$$IF(PROJTYPE_MDI)
$$IF(VERBOSE)

	// The main window has been initialized, so show and update it.
$$ENDIF
	pMainFrame->ShowWindow($$SW_ARG$$);
	pMainFrame->UpdateWindow();
$$ELIF(PROJTYPE_SDI)
$$IF(VERBOSE)

	// The one and only window has been initialized, so show and update it.
$$ENDIF
	m_pMainWnd->ShowWindow($$SW_ARG$$);
	m_pMainWnd->UpdateWindow();
$$// call DragAcceptFiles only if compiling for Mac, or if there's a suffix.
$$//  In an SDI app, this should occur after ProcessShellCommand
$$IF(HAS_SUFFIX)

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
$$ELIF(INSTALLED_MAC)

#ifdef _MAC
	// Enable drag/drop open.  We don't call this in Win32, since a
	//  document file extension wasn't chosen while running AppWizard.
	m_pMainWnd->DragAcceptFiles();
#endif
$$ENDIF //SUFFIX/INSTALLED_MAC
$$ENDIF //MDI/SDI

	return TRUE;
$$ENDIF //!MINI_SERVER
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
void $$APP_CLASS$$::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// $$APP_CLASS$$ commands
