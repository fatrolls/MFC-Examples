#include "stdafx.h"
#include "DDESrv.h"
#include "MainFrm.h"
#include "DDEDoc.h"
#include "DDEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TCHAR CMainFrame::m_szService[]=TEXT("Server");
HSZ CMainFrame::m_hszServiceName=0;
DWORD CMainFrame::m_dwInst=0;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFrameWnd::PreCreateWindow(cs);
}

HDDEDATA CALLBACK CMainFrame::DdeCallback
(
	UINT wType,
	UINT wFormat,
	HCONV hConv,
	HSZ hszTopic,
	HSZ hszItem,
	HDDEDATA hData,
	DWORD lData1,
	DWORD lData2
)
{
	switch(wType)
	{
	    case XTYP_REGISTER: 
        case XTYP_UNREGISTER:
		case XTYP_ADVSTART:
		case XTYP_ADVDATA:
		case XTYP_ADVREQ:
		case XTYP_ADVSTOP:
        case XTYP_XACT_COMPLETE: 
		case XTYP_CONNECT:
        case XTYP_DISCONNECT:
		case XTYP_CONNECT_CONFIRM:
		{
			return (HDDEDATA)NULL; 
		}
        default:
		{
			return (HDDEDATA)NULL; 
		}
	}
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif

void CMainFrame::InitializeDDE()
{
	UINT uDdeInit;
	CString szRlt;

	uDdeInit=::DdeInitialize
	(
		&m_dwInst,
		(PFNCALLBACK)DdeCallback,
		APPCMD_FILTERINITS, 
		0L
	);

	switch(uDdeInit)
	{
		case DMLERR_NO_ERROR:
		{
			Hszize();
			if(::DdeNameService(m_dwInst, m_hszServiceName, NULL, DNS_REGISTER))
			{
				szRlt="DDE initialized successfully!";
			}
			else szRlt="Fail to initialize DDE: Fail to register name service!";
			break;
		}
		case DMLERR_DLL_USAGE:
		{
			szRlt="Fail to initialize DDE: Dll usage error!";
			break;
		}
		case DMLERR_INVALIDPARAMETER:
		{
			szRlt="Fail to initialize DDE: Invalid parameter!";
			break;
		}
		case DMLERR_SYS_ERROR:
		{
			szRlt="Fail to initialize DDE: System error!";
			break;
		}
	}
	
	Printf((LPCSTR)szRlt);
	Printf("\r\n");
}

void CMainFrame::Hszize()
{
    m_hszServiceName=::DdeCreateStringHandle(m_dwInst, m_szService, NULL);
	Printf("Service name: %s\r\n", m_szService);
}

void CMainFrame::UnHszize()
{
	::DdeFreeStringHandle(m_dwInst, m_hszServiceName);
}

void CMainFrame::OnClose() 
{
	::DdeNameService(m_dwInst, NULL, NULL, DNS_UNREGISTER);
	UnHszize();
	::DdeUninitialize(m_dwInst);
	
	CFrameWnd::OnClose();
}

void CMainFrame::Printf(const char *fmt, ...)
{
	char buff[1024];

	va_list argp;
	va_start(argp, fmt);
	vsprintf(buff, fmt, argp);
	va_end(argp);
	GetCDDESrvView()->GetEditCtrl().ReplaceSel(buff);
	((CFrameWnd *)(AfxGetApp()->m_pMainWnd))->GetActiveDocument()->SetModifiedFlag(FALSE);
}

CDDESrvView *CMainFrame::GetCDDESrvView()
{
	CView *pView=((CFrameWnd *)(AfxGetApp()->m_pMainWnd))->GetActiveView();
	if(!pView)return NULL;
	if(!pView->IsKindOf(RUNTIME_CLASS(CDDESrvView)))return NULL;
	return (CDDESrvView *)pView;
}
