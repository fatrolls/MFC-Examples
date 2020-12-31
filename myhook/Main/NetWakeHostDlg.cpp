// NetWakeHostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "NetWakeHostDlg.h"
#include <winsock2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetWakeHostDlg dialog
IMPLEMENT_DYNCREATE(CNetWakeHostDlg, CRootDlg)

CNetWakeHostDlg::CNetWakeHostDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CNetWakeHostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetWakeHostDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNetWakeHostDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetWakeHostDlg)
	DDX_Control(pDX, IDC_LIST_IP, m_lstIP);
	DDX_Control(pDX, IDC_LIST_MAC, m_lstMac);
	DDX_Control(pDX, IDC_LIST_HOST, m_lstHost);
	DDX_Control(pDX, IDC_BTN_WAKE, m_btnWake);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetWakeHostDlg, CRootDlg)
	//{{AFX_MSG_MAP(CNetWakeHostDlg)
	ON_LBN_SELCHANGE(IDC_LIST_HOST, OnSelchangeListHost)
	ON_LBN_SELCHANGE(IDC_LIST_MAC, OnSelchangeListMac)
	ON_LBN_SELCHANGE(IDC_LIST_IP, OnSelchangeListIp)
	ON_BN_CLICKED(IDC_BTN_WAKE, OnBtnWake)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetWakeHostDlg message handlers

BOOL CNetWakeHostDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	InitializeControls();
	return TRUE;  
}

void CNetWakeHostDlg::InitializeControls()
{
    CMainApp* pApp = (CMainApp*)AfxGetApp();
	int iCount = pApp->GetProfileInt("Macs", "Count", 0);
	CString strKey, strHost, strMac, strIP;
	for(int i=0; i<iCount; i++)
	{
        strKey.Format("Host#%d", i);
		strHost = pApp->GetProfileString("Macs", strKey, "");
		strKey.Format("Mac#%d", i);
		strMac = pApp->GetProfileString("Macs", strKey, "");
		strKey.Format("IP#%d", i);
		strIP = pApp->GetProfileString("Macs", strKey, "");
		if (strHost != "" && strMac != ""  && strIP != "")
		{
			m_lstHost.AddString(strHost);
			m_lstMac.AddString(strMac);
			m_lstIP.AddString(strIP);
		}
	}

	if (m_lstHost.GetCount() > 0)
		m_lstHost.SetCurSel(0);
    if (m_lstMac.GetCount() > 0)
		m_lstMac.SetCurSel(0);
     if (m_lstIP.GetCount() > 0)
		m_lstIP.SetCurSel(0);
}

void CNetWakeHostDlg::OnSelchangeListHost() 
{
	int index = m_lstHost.GetCurSel();
	if (index != LB_ERR)
	{
		m_lstMac.SetCurSel(index);
		m_lstIP.SetCurSel(index);
	}
}

void CNetWakeHostDlg::OnSelchangeListMac() 
{
	int index = m_lstMac.GetCurSel();
	if (index != LB_ERR)
	{
		m_lstHost.SetCurSel(index);
	    m_lstIP.SetCurSel(index);
	}
}

void CNetWakeHostDlg::OnSelchangeListIp() 
{
	int index = m_lstIP.GetCurSel();
	if (index != LB_ERR)
	{
		m_lstHost.SetCurSel(index);
	    m_lstMac.SetCurSel(index);
	}
}

void CNetWakeHostDlg::OnBtnWake() 
{
	int index = m_lstHost.GetCurSel();
	if (index == -1)
		return;
	CString strIP, strMac;
	m_lstIP.GetText(index, strIP);
	m_lstMac.GetText(index, strMac);
	unsigned char mac[6];
	StringToMac(strMac, mac);
	char szBuf[6];
	memset(szBuf, 0xff, 6);
	char pData[102];
	memcpy(pData, szBuf, 6);
	for(int i=0; i<16; i++)
		memcpy(pData + (i + 1)* 6, mac, 6);

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(strIP);
	for( i=1025; i<65535; i++)
	{
        addr.sin_port = htons(i);
		if (SOCKET_ERROR == sendto(s, pData, 102, 0, (LPSOCKADDR)&addr, sizeof(addr)))
		{
			AfxMessageBox("Bad");
		}
	}
	closesocket(s);
}

void CNetWakeHostDlg::StringToMac(CString strMac, unsigned char mac[6])
{
    CString str1, str2, str3, str4, str5, str6;
	CString str;
	int index = strMac.Find("-");
	str1 = strMac.Left(index);
	str = strMac.Right(strMac.GetLength()-1-index);
    index = str.Find("-");
	str2 = str.Left(index);
	str = str.Right(str.GetLength()-1-index);
	index = str.Find("-");
	str3 = str.Left(index);
	str = str.Right(str.GetLength()-1-index);
	index = str.Find("-");
	str4 = str.Left(index);
	str = str.Right(str.GetLength()-1-index);
	index = str.Find("-");
	str5 = str.Left(index);
	str6 = str.Right(str.GetLength()-1-index);
	mac[0] = strtol(str1, NULL, 16);
	mac[1] = strtol(str2, NULL, 16);
	mac[2] = strtol(str3, NULL, 16);
	mac[3] = strtol(str4, NULL, 16);
	mac[4] = strtol(str5, NULL, 16);
	mac[5] = strtol(str6, NULL, 16);
}
