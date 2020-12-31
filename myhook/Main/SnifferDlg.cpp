// SnifferDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "SnifferDlg.h"
#include <winsock2.h>
#include <MsTcpIP.h>
#include "Helper.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnifferDlg dialog
IMPLEMENT_DYNCREATE(CSnifferDlg, CRootDlg)

CSnifferDlg::CSnifferDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CSnifferDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSnifferDlg)
	m_iInterface = -1;
	//}}AFX_DATA_INIT
	m_pThread = NULL;
}


void CSnifferDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnifferDlg)
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BTN_START_SNIFFER, m_btnStart);
	DDX_Control(pDX, IDC_TREE_DATA, m_treeData);
	DDX_Control(pDX, IDC_COMBO_INTERFACE, m_cmbInterface);
	DDX_CBIndex(pDX, IDC_COMBO_INTERFACE, m_iInterface);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSnifferDlg, CRootDlg)
	//{{AFX_MSG_MAP(CSnifferDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_START_SNIFFER, OnBtnStartSniffer)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnifferDlg message handlers

BOOL CSnifferDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	CStringArray aInterface;

	GetInterface(aInterface);

	for(int i=0; i<aInterface.GetSize(); i++)
		m_cmbInterface.AddString(aInterface[i]);
	m_cmbInterface.SetCurSel(0);
	m_iInterface = 0;
	
	m_imgList.Create(16, 16, ILC_COLOR32|ILC_MASK, 0, 1);
	m_imgList.Add( LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_COMP2COMP ) ) );
	m_imgList.Add( LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_IPHeader ) ) );
	m_imgList.Add( LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_TCPHEADER ) ) );

	m_treeData.SetImageList(&m_imgList, TVSIL_NORMAL);

	LOGFONT logfont;
	RtlZeroMemory(&logfont, sizeof(logfont));
	_tcscpy(logfont.lfFaceName, _T("Arial new"));
	logfont.lfHeight = 12;
	m_Font.CreateFontIndirect(&logfont);

	m_treeData.SetFont(&m_Font);
	return TRUE;  
}

void CSnifferDlg::GetInterface(CStringArray &aInterface)
{
    char szHost[MAX_PATH] = { 0 };
	gethostname(szHost, MAX_PATH);
	hostent* pHost = gethostbyname(szHost);
	if (pHost == NULL)
		return;
	int i = 0;
	in_addr addr;
	while(pHost->h_addr_list[i])
	{
		memcpy(&addr.S_un.S_addr, pHost->h_addr_list[i], pHost->h_length);
        aInterface.Add(inet_ntoa(addr));
		i ++;
	}
}

void CSnifferDlg::OnDestroy() 
{
	if (m_pThread != NULL)
		OnBtnStop();
	CRootDlg::OnDestroy();
    m_Font.DeleteObject();
	m_imgList.DeleteImageList();
}

void CSnifferDlg::OnBtnStartSniffer() 
{
	UpdateData();

	CString strCaption;
	m_btnStart.GetWindowText(strCaption);

	if(strCaption == "开始嗅探")
	{
		if (m_pThread == NULL)
		{
			m_treeData.DeleteAllItems();
			m_bThreadExit = false;
			m_btnStart.SetWindowText("暂停");
			m_btnStop.EnableWindow(TRUE);
			m_pThread = AfxBeginThread(AFX_THREADPROC(DoSniffer), this);
		}
		else
		{
			m_pThread->ResumeThread();
			m_btnStop.EnableWindow(TRUE);
			m_btnStart.SetWindowText("暂停");
		}
	}
	else if (strCaption == "暂停")
	{
		m_btnStart.SetWindowText("开始嗅探");
		m_btnStop.EnableWindow(FALSE);
		m_pThread->SuspendThread();
	}
}

void CSnifferDlg::OnBtnStop() 
{
	if (m_pThread == NULL)
		return;
	m_bThreadExit = true;
	m_event.SetEvent();
	WaitForSingleObject(m_pThread->m_hThread, INFINITE);
	m_btnStart.SetWindowText("开始嗅探");
	m_btnStop.EnableWindow(FALSE);
	m_pThread = NULL;
}

UINT CSnifferDlg::DoSniffer(LPVOID pParam)
{
	CSnifferDlg* pDlg = (CSnifferDlg*)pParam;
    SOCKET s = WSASocket(AF_INET, SOCK_RAW, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
	CString strInterface;
	pDlg->m_cmbInterface.GetLBText(pDlg->m_iInterface, strInterface);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(strInterface);
	addr.sin_port = 0;
	bind(s, (LPSOCKADDR)&addr, sizeof(addr));
    unsigned int optval = 1;
	DWORD dwBytesRet = 0;
	if (SOCKET_ERROR == WSAIoctl(s, SIO_RCVALL, &optval, sizeof(optval), NULL, 0, &dwBytesRet, NULL, NULL))
	{
		AfxMessageBox("不能该设置网卡的混杂模式");
		closesocket(s);
		return 0;
	}
    WSAOVERLAPPED overlap = { 0 };
	overlap.hEvent = pDlg->m_event.m_hObject;
	WSABUF buf;
	char bufT[4096];
    buf.buf = bufT;;
	buf.len = 4096;
    DWORD dwRet;
	DWORD dwFlag;
	int nRet;
	while(!pDlg->m_bThreadExit)
	{
		dwRet = dwFlag = 0;
        if (SOCKET_ERROR == WSARecv(s, &buf, 1, &dwRet, &dwFlag, &overlap, NULL))
		{
			DWORD dwError = WSAGetLastError();
			CString strError;
			GetErrorMessage(dwError, strError);
			if (dwError != WSA_IO_PENDING)
				continue;
			nRet = WaitForSingleObject(pDlg->m_event.m_hObject, 3000);
			if (nRet == WAIT_TIMEOUT)
				continue;
			if (!GetOverlappedResult((HANDLE)s, &overlap, &dwRet, FALSE) || dwRet <= 0)
				continue;
		}
		bufT[dwRet] = 0;
		pDlg->DecodePacket(bufT, dwRet);
	}

	closesocket(s);
	//pDlg->m_pThread = NULL;
	pDlg->m_bThreadExit = true;
    return 0;
}

void CSnifferDlg::DecodePacket(char *bufT, DWORD dwRet)
{
    if (dwRet < sizeof(IPHeader))
		return;
	PIPHeader pIpHeader = (PIPHeader)bufT;

	if (pIpHeader->ipProtocol == IPPROTO_TCP)
	{
        if (dwRet < sizeof(IPHeader) + sizeof(TCPHeader))
			return;
		PTCPHeader pTcpHeader = (PTCPHeader)(bufT + sizeof(IPHeader));
		char* pBuf = bufT + sizeof(IPHeader) + sizeof(TCPHeader);
		DWORD dwSize = dwRet - sizeof(IPHeader) + sizeof(TCPHeader);
		InsertData data(pIpHeader, pTcpHeader, pBuf, dwSize);
		data.Output(m_treeData);
	}
	else if (pIpHeader->ipProtocol == IPPROTO_UDP)
	{
        if (dwRet < sizeof(IPHeader) + sizeof(UDPHeader))
			return;
		PUDPHeader pUdpHeader = (PUDPHeader)(bufT + sizeof(IPHeader));
		char* pBuf = bufT + sizeof(IPHeader) + sizeof(UDPHeader);
		DWORD dwSize = dwRet - sizeof(IPHeader) + sizeof(UDPHeader);
		InsertData data(pIpHeader, pUdpHeader, pBuf, dwSize);
		data.Output(m_treeData);
	}
    //else if (pIpHeader->ipProtocol == IPPROTO_ARP)
	//{

	//}
}

CSnifferDlg::InsertData::InsertData(PIPHeader pIpHeader, PTCPHeader pTcpHeader, char *pData, DWORD dwDataSize)
{
    m_iType = TCP_TYPE;
	Data.tcp = new TCP;
	strDestIP = inet_ntoa(*(in_addr*)&pIpHeader->ipDestionation);
    strSrcIP = inet_ntoa(*(in_addr*)&pIpHeader->ipSource);
	Data.tcp->strDestPort.Format("%d", ntohs(pTcpHeader->destinationPort));
    Data.tcp->strSrcPort.Format("%d", ntohs(pTcpHeader->sourcePort));
	Data.tcp->strSequence.Format("%ul", ntohs(pTcpHeader->sequenceNumber));
	if (((pTcpHeader->flags >> 5) & 1) == 1)
		Data.tcp->strFlags += "URG,";
    if (((pTcpHeader->flags >> 4) & 1) == 1)
		Data.tcp->strFlags += "ACK,";
	if (((pTcpHeader->flags >> 3) & 1) == 1)
		Data.tcp->strFlags += "PUSH,";
	if (((pTcpHeader->flags >> 2) & 1) == 1)
		Data.tcp->strFlags += "RST,";
	if (((pTcpHeader->flags >> 1) & 1) == 1)
		Data.tcp->strFlags += "SYN,";
	if (((pTcpHeader->flags) & 1) == 1)
		Data.tcp->strFlags += "FIN,";
	Data.tcp->strFlags = Data.tcp->strFlags.Left(Data.tcp->strFlags.GetLength()-1);
    Data.tcp->strWindowSize.Format("%ul", pTcpHeader->windows);
	if (pData != NULL && dwDataSize > 0)
	{
		strData = GetData(pData, dwDataSize);
		if (Data.tcp->strDestPort == "21")
			GetFtpData(pData, dwDataSize);
	}
}

CSnifferDlg::InsertData::InsertData(PIPHeader pIpHeader, PUDPHeader pUdpHeader, char *pData, DWORD dwDataSize)
{
    m_iType = UDP_TYPE;
	Data.udp = new UDP;
	strDestIP = inet_ntoa(*(in_addr*)&pIpHeader->ipDestionation);
    strSrcIP = inet_ntoa(*(in_addr*)&pIpHeader->ipSource);
	Data.udp->strDestPort.Format("%d", ntohs(pUdpHeader->destinationPort));
    Data.udp->strSrcPort.Format("%d", ntohs(pUdpHeader->sourcePort));
	if (pData != NULL && dwDataSize > 0)
		strData = GetData(pData, dwDataSize);
}

CSnifferDlg::InsertData::InsertData(PIPHeader pIpHeader, PARPHeader pArpHeader, char *pData, DWORD dwDataSize)
{
   m_iType = ARP_TYPE;
   Data.arp = new ARP;
   strDestIP = inet_ntoa(*(in_addr*)&pIpHeader->ipDestionation);
   strSrcIP = inet_ntoa(*(in_addr*)&pIpHeader->ipSource);
   Data.arp->strSrcMac.Format("%02x-%02x-%02x-%02x-%02x-%02x", pArpHeader->sourcemac[0], 
	   pArpHeader->sourcemac[1], pArpHeader->sourcemac[2], pArpHeader->sourcemac[3],
	   pArpHeader->sourcemac[4], pArpHeader->sourcemac[5]);
   Data.arp->strDestMac.Format("%02x-%02x-%02x-%02x-%02x-%02x", pArpHeader->destmac[0], 
	   pArpHeader->destmac[1], pArpHeader->destmac[2], pArpHeader->destmac[3],
	   pArpHeader->destmac[4], pArpHeader->destmac[5]);
   if (pData != NULL && dwDataSize > 0)
		strData = GetData(pData, dwDataSize);
}

CString CSnifferDlg::InsertData::GetData(char *pData, DWORD dwSize)
{
	CString str;
	CString str2;
    for(int i=0; i<dwSize; i++)
	{
      char ch = pData[i];
	  str2.Format("%02x ", ch);  
      str += str2;
	}
    return str;
}

void CSnifferDlg::InsertData::Output(CTreeCtrl &tree)
{
	CString strKey = strSrcIP + "--->" + strDestIP;
	HTREEITEM hItem = tree.InsertItem(strKey, 0, 0);
	HTREEITEM hIpItem = tree.InsertItem(_T("IPHeader"), hItem, 0);
	tree.InsertItem("Source IP: " + strSrcIP, hIpItem, 0);
    tree.InsertItem("Dest IP: " + strDestIP, hIpItem, 0);
	HTREEITEM hDataItem = NULL;

	if (m_iType == TCP_TYPE)
	{
		hDataItem =  tree.InsertItem("TCPHeader", hItem, 0);
		tree.InsertItem("Source Port: " + Data.tcp->strSrcPort, hDataItem, 0);
        tree.InsertItem("Dest IP: " + Data.tcp->strDestPort, hDataItem, 0);
		tree.InsertItem("Sequence: " + Data.tcp->strSequence, hDataItem, 0);
        tree.InsertItem("Window size: " + Data.tcp->strWindowSize, hDataItem, 0);
		tree.InsertItem("Flags: " + Data.tcp->strFlags, hDataItem, 0);
		if (Data.tcp->strUserName != "")
			tree.InsertItem("Flags: " + Data.tcp->strUserName, hDataItem, 0);
		if (Data.tcp->strPassword != "")
		   tree.InsertItem("Flags: " + Data.tcp->strPassword, hDataItem, 0);
	}
	else if (m_iType == UDP_TYPE)
	{
		hDataItem =  tree.InsertItem("UDPHeader", hItem, 0);
		tree.InsertItem("Source Port: " + Data.udp->strSrcPort, hDataItem, 0);
        tree.InsertItem("Dest Port: " + Data.udp->strDestPort, hDataItem, 0);
	}
	else if (m_iType == ARP_TYPE)
	{
		hDataItem = tree.InsertItem("ARPHeader", hItem, 0);
        tree.InsertItem("源MAC地址: " + Data.arp->strSrcMac, hDataItem, 0);
        tree.InsertItem("目的MAC地址: " + Data.arp->strDestMac, hDataItem, 0);
	}

	if (hDataItem != NULL && strData != "")
	    tree.InsertItem("Data: " + strData, hDataItem, 0); 
}

void CSnifferDlg::InsertData::GetFtpData(char *pData, DWORD dwSize)
{
	char szUserName[100] = "";
	char szPassword[100] = "";

	if(strnicmp(pData, "USER ", 5) == 0)
		sscanf(pData + 4, "%*[ ]%s", szUserName);	
	else if(strnicmp(pData, "PASS ", 5) == 0)
		sscanf(pData + 4, "%*[ ]%s", szPassword);
    if (strcmp(szUserName, "") != 0)
		Data.tcp->strUserName = szUserName;
    if (strcmp(szPassword, "") != 0)
		Data.tcp->strPassword = szUserName;
}