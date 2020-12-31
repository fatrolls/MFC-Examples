#include "stdafx.h"
#include "DDESrv.h"
#include "MainFrm.h"
#include "DDEDoc.h"
#include "DDEView.h"
#include "Advise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TCHAR CMainFrame::m_szService[]=TEXT("Server");
TCHAR CMainFrame::m_szTopic[]=TEXT("Topic");
TCHAR CMainFrame::m_szTimeItem[]=TEXT("Time");
TCHAR CMainFrame::m_szTextItem[]=TEXT("Text");
HSZ CMainFrame::m_hszServiceName=0;
HSZ CMainFrame::m_hszTopicName=0;
HSZ CMainFrame::m_hszTimeItem=0;
HSZ CMainFrame::m_hszTextItem=0;
BOOL CMainFrame::m_bAdvise=FALSE;
HCONV CMainFrame::m_hConvServer=0;
DWORD CMainFrame::m_dwInst=0;
CString CMainFrame::m_szText;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CLOSE()
	ON_COMMAND(ID_DDE_DISCONNECT, OnDdeDisconnect)
	ON_UPDATE_COMMAND_UI(ID_DDE_DISCONNECT, OnUpdateDdeDisconnect)
	ON_COMMAND(ID_DDE_ADVISE, OnDdeAdvise)
	ON_UPDATE_COMMAND_UI(ID_DDE_ADVISE, OnUpdateDdeAdvise)
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
	HSZ hszItemName,
	HDDEDATA hData,
	DWORD lData1,
	DWORD lData2
)
{
	switch(wType)
	{
	    case XTYP_REGISTER: 
        case XTYP_UNREGISTER:
		{
			return (HDDEDATA)FALSE;
		}
		case XTYP_REQUEST:
		{
			if
			(
				!::DdeCmpStringHandles(hszTopic, m_hszTopicName) && 
				!::DdeCmpStringHandles(hszItemName, m_hszTimeItem) &&
				wFormat == CF_TEXT
			)
			{
				CTime time;
				CString szTime;
				HDDEDATA hData;

				time=CTime::GetCurrentTime();
				szTime=time.Format("%H:%M:%S");
				hData=::DdeCreateDataHandle
				(
					m_dwInst,
					(LPBYTE)(LPCSTR)szTime,
					szTime.GetLength(),
					0,
					m_hszTimeItem,
					CF_TEXT,
					0
				);

				Printf("Responded to client's request for time item\r\n");
				return hData;
			}
			else
			{
				Printf("Do not support this itme!\r\n");
				return (HDDEDATA)FALSE;
			}
		}
		case XTYP_ADVSTART:
		{
			if
			(
				!::DdeCmpStringHandles(hszTopic, m_hszTopicName) && 
				!::DdeCmpStringHandles(hszItemName, m_hszTextItem) &&
				wFormat == CF_TEXT
			)
			{
				((CMainFrame *)(AfxGetApp()->m_pMainWnd))->m_bAdvise=TRUE;
				Printf("Responded to client's request for advise  on time item\r\n");
				return (HDDEDATA)TRUE;
			}
			else
			{
				Printf("Do not support advise on this item!\r\n");
				return (HDDEDATA)FALSE;
			}
		}
		case XTYP_ADVDATA:
		{
			return (HDDEDATA)FALSE;
		}
		case XTYP_ADVREQ:
		{
			if
			(
				!::DdeCmpStringHandles(hszTopic, m_hszTopicName) && 
				!::DdeCmpStringHandles(hszItemName, m_hszTextItem) &&
				wFormat == CF_TEXT
			)
			{
				CString szText;
				HDDEDATA hData;

				szText=((CMainFrame *)(AfxGetApp()->m_pMainWnd))->m_szText;
				hData=::DdeCreateDataHandle
				(
					m_dwInst,
					(LPBYTE)(LPCSTR)szText,
					szText.GetLength(),
					0,
					m_hszTextItem,
					CF_TEXT,
					0
				);

				Printf("Advized on text item\r\n");
				return hData;
			}
			else
			{
				Printf("Do not support advise on this item!\r\n");
				return (HDDEDATA)FALSE;
			}
		}
		case XTYP_ADVSTOP:
		{
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->m_bAdvise=FALSE;
			Printf("Advise stopped\r\n");
			return (HDDEDATA)FALSE;
		}
        case XTYP_XACT_COMPLETE: 
		{
			return (HDDEDATA)FALSE;
		}
		case XTYP_CONNECT:
		{
			if
			(
				!::DdeCmpStringHandles(hszTopic, m_hszTopicName) && 
				!::DdeCmpStringHandles(hszItemName, m_hszServiceName)
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
	m_hszTimeItem=::DdeCreateStringHandle(m_dwInst, m_szTimeItem, NULL);
	Printf("Supported item name: %s\r\n", m_szTimeItem);
	m_hszTextItem=::DdeCreateStringHandle(m_dwInst, m_szTextItem, NULL);
	Printf("Supported item name: %s\r\n", m_szTextItem);
}

void CMainFrame::UnHszize()
{
	::DdeFreeStringHandle(m_dwInst, m_hszServiceName);
	::DdeFreeStringHandle(m_dwInst, m_hszTopicName);
	::DdeFreeStringHandle(m_dwInst, m_hszTimeItem);
	::DdeFreeStringHandle(m_dwInst, m_hszTextItem);
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

void CMainFrame::OnDdeAdvise() 
{
	CAdviseDialog dlg;
	
	if(dlg.DoModal() == IDOK && m_bAdvise == TRUE)
	{
		m_szText.Empty();
		m_szText=dlg.m_szText;
		m_szText+='\0';
		::DdePostAdvise(m_dwInst, m_hszTopicName, m_hszTextItem);
	}
}

void CMainFrame::OnUpdateDdeAdvise(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bAdvise);	
}
