// adHTMLHelp.cpp: implementation of the CadHTMLHelp class.
//
//////////////////////////////////////////////////////////////////////
//
// includes
//
#include "stdafx.h"

//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
//
// ckeck the window for valid
// Überprüft, ob das angegeben Fenster gültig ist
//
#ifndef ASSERT_WINDOW
	#ifdef _DEBUG
		#define ASSERT_WINDOW(hWnd) ASSERT(::IsWindow(hWnd))
	#else
		#define ASSERT_WINDOW(hWnd)
	#endif
#endif

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//
// capsulate the HTML-structures
// Strukturen für die HTML-Hilfe kapseln
//
//////////////////////////////////////////////////////////////////////
class	CHH_POPUP :public	HH_POPUP
{
public:
	CHH_POPUP(){
		ZeroMemory(this,sizeof(HH_POPUP));
		cbStruct = sizeof(HH_POPUP);
	}
	operator HH_POPUP() { return *this; }
	operator const HH_POPUP() { return (const HH_POPUP) *this; }
} ;

//////////////////////////////////////////////////////////////////////
class CHH_WINTYPE :public HH_WINTYPE
{
public:
	CHH_WINTYPE() {
		ZeroMemory(this,sizeof(HH_WINTYPE));
		cbStruct = sizeof(HH_WINTYPE);
#ifdef UNICODE
		fUniCodeString = true;
#endif
	}
	operator HH_WINTYPE() { return *this; }
	operator PHH_WINTYPE() { return this; }
} ;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//
// english:
// In this time, you can't work with HH_HELP_CONTEXT and must work with
// the filename in the packed html-archive. 
// Atention! If you work with relative paths in the cch-archive, you 
// must use this!
//
// german:
// HH_HELP_CONTEXT läßt sich zur Zeit nicht ansprechen. Deshalb muß
// der Aufruf des entsprechenden Files über den Namen erfolgen.
// dazu muß der relative Pfad innerhalb der gepacken cch-Datei mit
// angegeben werden!
//
void CDialogHelperHook::ShowHelp(CWnd* pWnd, const CString& strFile )
{
	ASSERT_VALID ( pWnd );
	ASSERT_WINDOW( pWnd->m_hWnd );

	CWaitCursor wait;

	CRect rect;
	pWnd->GetClientRect(rect);

	CHH_WINTYPE winType;		 
	winType.pszType=_T("alfXX");
	winType.fsValidMembers = 
		HHWIN_PARAM_STYLES|
		HHWIN_PARAM_RECT|
		HHWIN_PARAM_PROPERTIES|
		HHWIN_PARAM_TB_FLAGS;

	winType.dwStyles = WS_CHILD|WS_MAXIMIZE ;
	winType.fsWinProperties = 
		HHWIN_PROP_NOTITLEBAR|
		HHWIN_PROP_AUTO_SYNC|
		HHWIN_PROP_TRI_PANE;
	winType.fsToolBarFlags = 
		HHWIN_BUTTON_BACK|
		HHWIN_BUTTON_FORWARD|
		HHWIN_BUTTON_PRINT;

	winType.rcWindowPos = rect;

	CString strPath = GetHTMLHelpPath();

	HWND hWnd = HtmlHelp(
		 pWnd->GetSafeHwnd(),
		 strPath,
		 HH_SET_WIN_TYPE,
		 (DWORD)&winType );


	hWnd = HtmlHelp(
		 pWnd->GetSafeHwnd(),
		 strPath + _T(">alfXX"),
		 HH_DISPLAY_TOPIC,
		 (DWORD)(LPCTSTR) strFile );	

	if( hWnd == NULL ){
		//
		// error
		//
		// ... uv
		// make what you will!...
	}
}

//////////////////////////////////////////////////////////////////////
//
// The MFC get a file with *.hlp! We need *.chm and convert the name.
//
CString CDialogHelperHook::GetHTMLHelpPath()
{
	CWinApp* pApp = AfxGetApp();
	ASSERT_VALID( pApp );
	CString strPath = pApp->m_pszHelpFilePath;

	// Es wurde keine gültiger Name für die Hilfedatei gefunden!
	ASSERT( !strPath.IsEmpty());

	TCHAR szPathBuffer[_MAX_PATH];   
	TCHAR szDrive[_MAX_DRIVE];   
	TCHAR szDir[_MAX_DIR];
	TCHAR szFname[_MAX_FNAME];   
	TCHAR szExt[_MAX_EXT];		
	
	_splitpath( strPath, szDrive, szDir, szFname, szExt );

	_makepath( szPathBuffer,szDrive, szDir, szFname, _T("chm") );

	return szPathBuffer;
}
//////////////////////////////////////////////////////////////////////
#define DLG_STUFF 0x20000

UINT CDialogHelperHook::PareDlgIDForHelp(UINT nID)
{
	return nID + DLG_STUFF;
}
//////////////////////////////////////////////////////////////////////
HWND CDialogHelperHook::HtmlHelp(HWND hWndCaller,const CString& 
		strFile,UINT uCommand,DWORD dwData)

{
	//
	// load help file
	//
	HINSTANCE	
	m_h_instance = LoadLibrary (_T("HHCTRL.OCX"));

	ASSERT( m_h_instance );
	if (m_h_instance == NULL){
		//
		// can't find library!
		//
		return NULL;
	}


	//
	// get entry point
	//
	HWND (WINAPI *lpfn)(
		HWND hwndCaller,
		LPCTSTR pszFile,
		UINT uCommand,
		DWORD dwData);
	FARPROC m_entry_proc = NULL;

	if (m_h_instance != NULL) {

#ifdef UNICODE
		m_entry_proc = GetProcAddress(m_h_instance,_T("HtmlHelpW")); 
#else
		m_entry_proc = GetProcAddress(m_h_instance,_T("HtmlHelpA")); 
#endif

		ASSERT (m_entry_proc);
		if ( m_entry_proc == NULL ) {
			//
			// not found
			//
			return NULL;
		}
	}
	(FARPROC&)lpfn = m_entry_proc;

	//
	// call function
	//
	return lpfn(hWndCaller,strFile,uCommand,dwData);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//
//	CPageHelp
//
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CPageHelp, CPropertyPage)

CPageHelp::CPageHelp(UINT nHelpNameID) : 
	CPropertyPage(CPageHelp::IDD)
{
	m_nHelpNameID = nHelpNameID;
	pSheet = NULL;
}

CPageHelp::~CPageHelp()	{}

void CPageHelp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageHelp, CPropertyPage)
	//{{AFX_MSG_MAP(CPageHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPageHelp::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	//
	// Für den Zugriff muß im Konstruktor der Sheet-Klasse vor
	// dem Aufruf von AddPage das Feld pSheet in diesem Objekt
	// gesetzt werden!
	//
	ASSERT       ( pSheet );
	ASSERT_VALID ( pSheet );
	ASSERT       ( pSheet->GetPageCount() > 1 );
	
	//
	// calculate the size of the page
	//
	CRect rect;
	pSheet->GetPage(0)->GetClientRect( rect );
	SetWindowPos( (pSheet->GetPage(0) ),// -ad- 02.03.1998
		rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW );

	CString strHelpName;	strHelpName.LoadString( m_nHelpNameID );
	
	ShowHelp( this, strHelpName );

	return TRUE;  
}
