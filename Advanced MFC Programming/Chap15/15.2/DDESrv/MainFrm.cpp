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
TCHAR CMainFrame::m_szTopic[]=TEXT("Topic");
HSZ CMainFrame::m_hszServiceName=0;
HSZ CMainFrame::m_hszTopicName=0;
HCONV CMainFrame::m_hConvServer=0;
DWORD CMainFrame::m_dwInst=0;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CLOSE()
	ON_COMMAND(ID_DDE_DISCONNECT, OnDdeDisconnect)
	ON_UPDATE_COMMAND_UI(ID_DDE_DISCONNECT, OnUpdateDdeDisconnect)
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
	HSZ hszAppName,
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
		{
			return (HDDEDATA)FALSE;
		}
		case XTYP_CONNECT:
		{
			if
			(
				!::DdeCmpStringHandles(hszTopic, m_hszTopicName) && 
				!::DdeCmpStringHandles(hszAppName, m_hszServiceName)
			)
			{
				Printf("Connect!\r\n");
				return (HDDEDATA)TRUE;
			}
			else
			{
				Printf("Connection refused, do not support this topic!\r\n");
				return (HDDEDATA)FALSE;
			}
		}
        case XTYP_DISCONNECT:
		{
			if(m_hConvServer == hConv)
			{
				m_hConvServer=0;
				Printf("Disconnected by the client.\r\n");
			}
			return (HDDEDATA)FALSE;
		}
		case XTYP_CONNECT_CONFIRM:
		{
			m_hConvServer=hConv;
			Printf("Handle saved for conversation!\r\n");
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
	m_hszTopicName=::DdeCreateStringHandle(m_dwInst, m_szTopic, NULL);
	Printf("Supported topic name: %s\r\n", m_szTopic);
}

void CMainFrame::UnHszize()
{
	::DdeFreeStringHandle(m_dwInst, m_hszServiceName);
	::DdeFreeStringHandle(m_dwInst, m_hszTopicName);
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


void CMainFrame::OnDdeDisconnect() 
{
	if(m_hConvServer != 0)
	{
		::DdeDisconnect(m_hConvServer);
		m_hConvServer=0;
		Printf("Disconnected by the server.\r\n");
	}
}

void CMainFrame::OnUpdateDdeDisconnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((int)m_hConvServer);
}
