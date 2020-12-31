// TaceRouteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"

#include "TaceRouteDlg.h"
//#include "Ws2tcpip.h"
#include "ProtocolTypes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaceRouteDlg dialog
IMPLEMENT_DYNCREATE(CTaceRouteDlg, CRootDlg)

CTaceRouteDlg::CTaceRouteDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CTaceRouteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTaceRouteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTaceRouteDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTaceRouteDlg)
	DDX_Control(pDX, IDC_STATIC_INFO, m_wndPlace);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IpAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTaceRouteDlg, CRootDlg)
	//{{AFX_MSG_MAP(CTaceRouteDlg)
	ON_BN_CLICKED(IDC_BTN_TRACE, OnBtnTrace)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TRACE_END, OnTraceEnd)
	ON_MESSAGE(WM_TRACE_ADD_GROUD, OnTraceAddGroup)
	ON_MESSAGE(WM_TRACE_Add_CHILD, OnTraceAddChild)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaceRouteDlg message handlers

void CTaceRouteDlg::OnDestroy() 
{
	m_wndPropList.DestroyWindow();
	CRootDlg::OnDestroy();
}

BOOL CTaceRouteDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	CRect rectDummy;
	m_wndPlace.GetWindowRect(rectDummy);
	ScreenToClient(&rectDummy);
	rectDummy.DeflateRect(3, 3);
	rectDummy.top += 3;
	m_wndPropList.Create (WS_VISIBLE | WS_CHILD, rectDummy, this, 2);
	m_wndPropList.EnableHeaderCtrl (FALSE);
    m_wndPropList.SetVSDotNetLook ();
		
	return TRUE;  
}

CBCGPProp* CTaceRouteDlg::AddGroupProp(CString strName, CBCGPProp* pParent)
{
	CBCGPProp* pProp = new CBCGPProp(_T(strName));
	if (pParent == NULL)
		m_wndPropList.AddProperty(pProp);
	else
		pParent->AddSubItem(pProp);
	return pProp;
}

void CTaceRouteDlg::AddChildProp(CString strName, CString strValue, CBCGPProp* pParent)
{
    CBCGPProp* pProp = new CBCGPProp(_T(strName), (_variant_t)(_bstr_t)strValue, "");
	if (pParent == NULL)
		m_wndPropList.AddProperty(pProp);
	else
		pParent->AddSubItem(pProp);
}

void CTaceRouteDlg::OnBtnTrace() 
{
	DWORD dwIP;
	m_IpAddress.GetAddress(dwIP);

	m_wndPropList.RemoveAll();
	if (dwIP == 0)
	{
		AddChildProp("错误", "请输入有效的IP地址");
		return;
	}
    GetDlgItem(IDC_BTN_TRACE)->EnableWindow(FALSE);
	CTraceRouteThread* pThread = (CTraceRouteThread*)AfxBeginThread(RUNTIME_CLASS(CTraceRouteThread));
	pThread->StartTrace(this, htonl(dwIP));
}

LRESULT CTaceRouteDlg::OnTraceEnd(WPARAM, LPARAM)
{
    GetDlgItem(IDC_BTN_TRACE)->EnableWindow(TRUE);
	return 0;
}

LRESULT CTaceRouteDlg::OnTraceAddGroup(WPARAM wParam, LPARAM lParam)
{
     CBCGPProp* pParent = (CBCGPProp*)wParam;
	 char* szBuf = (char*)lParam;
     CBCGPProp* pProp = AddGroupProp(szBuf, pParent);
	 delete [] szBuf;
	 return (LRESULT)pProp;
}	

LRESULT CTaceRouteDlg::OnTraceAddChild(WPARAM wParam, LPARAM lParam)
{
     CBCGPProp* pParent = (CBCGPProp*)wParam;
	 ChildProp* pChild = (ChildProp*)lParam;
	 AddChildProp(pChild->strName, pChild->strValue, pParent);
	 delete pChild;
	 return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CTraceRouteThread

IMPLEMENT_DYNCREATE(CTraceRouteThread, CWinThread)

CTraceRouteThread::CTraceRouteThread()
{
}

CTraceRouteThread::~CTraceRouteThread()
{
}

BOOL CTraceRouteThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CTraceRouteThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CTraceRouteThread, CWinThread)
	//{{AFX_MSG_MAP(CTraceRouteThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTraceRouteThread message handlers


void CTraceRouteThread::StartTrace(CTaceRouteDlg *pDlg, DWORD dwIP)
{
    m_pDlg = pDlg;
	m_dwIP = dwIP;
	m_event.SetEvent();
}

int CTraceRouteThread::Run() 
{
	SOCKET sSend = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    SOCKET sRaw = ::socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	while(true)
	{
        int nRet = WaitForSingleObject(m_event.m_hObject, 3000);
		if (nRet == WAIT_TIMEOUT)
			continue;
        MySockaddr_In addr(0);

		nRet = bind(sRaw, (LPSOCKADDR)&addr, sizeof(addr));
        if (nRet == SOCKET_ERROR)
		{
			ChildProp* pMsg = new ChildProp;
			pMsg->strName = "错误";
			pMsg->strValue = "不能绑定原始套接字到端口";
			m_pDlg->SendMessage(WM_TRACE_Add_CHILD, 0, (LPARAM)pMsg);
			break;
		}
		int nTimeout = 5000;
		setsockopt(sRaw, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeout, sizeof(int));
		MySockaddr_In destAddr(22, ntohl(m_dwIP));
		sockaddr_in rcvAddr;
        int nTTL = 0;
		DWORD dwTick;
		char rcvBuf[1024];
		ICMPHeader* pIcmpHeader;

		do{
            setsockopt(sSend, IPPROTO_IP, IP_TTL, (char*)&nTTL, sizeof(int));
			dwTick = GetTickCount();
            nRet = sendto(sSend, "Hello", 6, 0, (LPSOCKADDR)&destAddr, sizeof(destAddr));
			if (nRet == SOCKET_ERROR)
			{
				if (nTTL++ <= 20)
					continue;
				else
					break;
			}
			int nLen = sizeof(rcvAddr);
			nRet = ::recvfrom(sRaw, rcvBuf, 1024, 0, (sockaddr*)&rcvAddr, &nLen);
			if(nRet == SOCKET_ERROR)
			{
				if(::WSAGetLastError() == WSAETIMEDOUT)
				{
					ChildProp* pMsg = new ChildProp;
					pMsg->strName = "错误";
					pMsg->strValue = "Time out";
					m_pDlg->SendMessage(WM_TRACE_Add_CHILD, 0, (LPARAM)pMsg);
				}
				break;
			}
			
			// 解析接收到的ICMP数据
			pIcmpHeader = (ICMPHeader*)&rcvBuf[20]; // sizeof(IPHeader)
			
			if(pIcmpHeader->Type != 11 && pIcmpHeader->Type != 3 && pIcmpHeader->Code != 3)
			{
				CString str;
				str.Format(" Unexpected Type: %d , code: %d \n", pIcmpHeader->Type, pIcmpHeader->Code); 
				ChildProp* pMsg = new ChildProp;
				pMsg->strName = "错误";
				pMsg->strValue = str;
				m_pDlg->SendMessage(WM_TRACE_Add_CHILD, 0, (LPARAM)pMsg);
			}
			else
			{
				char *szIP = ::inet_ntoa(rcvAddr.sin_addr);
				CString* str = new CString;
				str->Format("第%d个路由器", nTTL);
                CBCGPProp* pProp = (CBCGPProp*)m_pDlg->SendMessage(WM_TRACE_ADD_GROUD, 0, (LPARAM)str);
				ChildProp* pMsg = new ChildProp;
				pMsg->strName = "IP";
				pMsg->strValue = szIP;
				m_pDlg->SendMessage(WM_TRACE_Add_CHILD, (WPARAM)pProp, (LPARAM)pMsg);
				pMsg = new ChildProp;
				pMsg->strName = "用时";
				pMsg->strValue.Format("%d毫秒", GetTickCount() - dwTick);
				m_pDlg->SendMessage(WM_TRACE_Add_CHILD, (WPARAM)pProp, (LPARAM)pMsg);
			}
			
			if(destAddr.sin_addr.S_un.S_addr == rcvAddr.sin_addr.S_un.S_addr)
			{	
				ChildProp* pMsg = new ChildProp;
				pMsg->strName = "目标机器可达到性";
				pMsg->strValue = "目标可达";
				m_pDlg->SendMessage(WM_TRACE_Add_CHILD, 0, (LPARAM)pMsg);
				break;
			}
		}while(nTTL++ <= 20);
		
		break;
	}

	closesocket(sRaw);
	closesocket(sSend);
	m_pDlg->SendMessage(WM_TRACE_END, 0, 0);
	return CWinThread::Run();
}
