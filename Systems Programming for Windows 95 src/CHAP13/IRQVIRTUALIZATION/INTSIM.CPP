///////////////////////////////////////////////////////////////////////////////
//
//    INTSIM.CPP -- Interrupt simulation applet
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "intsim.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntsimApp

BEGIN_MESSAGE_MAP(CIntsimApp, CWinApp)
	//{{AFX_MSG_MAP(CIntsimApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntsimApp construction

CIntsimApp::CIntsimApp()
{
}

CIntsimApp::~CIntsimApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIntsimApp object

CIntsimApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CIntsimApp implementation

#pragma warning(disable:4704)	// _asm precludes global optimization

BOOL CIntsimApp::InitInstance()
{
	CMainDlg dlg;
	char devname[] = "MYVXD   ";
	DWORD myvxd;
	
	_asm
		{						// locate device api
		mov	ax, 1684h			; fcn 1684: find api entry
		mov	bx, 0				; BX = unknown device id
		mov	di, ss				; ES:DI -> device name
		mov	es, di				;   ..
		lea	di, devname			;   ..
		int	2Fh					; look for device api entry
		mov	word ptr myvxd, di ; save address
		mov	word ptr myvxd+2, es ;   ..
		}						// locate device api
	if (!myvxd)
		{						// VxD not loaded
		MessageBox(GetFocus(), "MYVXD.VXD isn't loaded", "Error", MB_ICONHAND | MB_OK);
		return FALSE;
		}						// VxD not loaded
	dlg.myvxd = (void (FAR *)()) myvxd;
	dlg.DoModal();
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_BN_CLICKED(IDB_EXIT, OnExit)
	ON_BN_CLICKED(IDB_INTERRUPT, OnInterrupt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

void CMainDlg::OnExit()
{
	EndDialog(IDCANCEL);
}

void CMainDlg::OnInterrupt()
{
	myvxd();					// call MYVXD's API to simulate an IRQ
}
