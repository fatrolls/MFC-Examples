// IpHlpMiscDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include "IpHlpMiscDlg.h"
#include "Helper.h"
#include "RawUdp.h"

#pragma comment(lib, "iphlpapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CIpHlpMiscDlg dialog
IMPLEMENT_DYNCREATE(CIpHlpMiscDlg, CRootDlg)

CIpHlpMiscDlg::CIpHlpMiscDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CIpHlpMiscDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIpHlpMiscDlg)
	m_strFirstInterfaceDesc = _T("");
	m_strAdapterName = _T("");
	m_strAdapterIndex = _T("");
	m_strAdapterNum = _T("");
	m_strMac = _T("");
	//}}AFX_DATA_INIT
}


void CIpHlpMiscDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIpHlpMiscDlg)
	DDX_Control(pDX, IDC_IPADDRESS2, m_IPHost);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPGateWay);
	DDX_Text(pDX, IDC_EDIT_FIRST_INTERFACE_DESC, m_strFirstInterfaceDesc);
	DDX_Text(pDX, IDC_STATIC_ADAPT_NAME, m_strAdapterName);
	DDX_Text(pDX, IDC_STATIC_ADAPTER_INDEX, m_strAdapterIndex);
	DDX_Text(pDX, IDC_STATIC_ADAPTER_NUM, m_strAdapterNum);
	DDX_Text(pDX, IDC_STATIC_MAC_ADDRESS, m_strMac);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIpHlpMiscDlg, CRootDlg)
	//{{AFX_MSG_MAP(CIpHlpMiscDlg)
	ON_BN_CLICKED(IDC_BTN_CHANGE_DEFAULT_GATEWAY, OnBtnChangeDefaultGateway)
	ON_BN_CLICKED(IDC_BTN_GET_MAC, OnBtnGetMac)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIpHlpMiscDlg message handlers

PMIB_IPFORWARDTABLE CIpHlpMiscDlg::GetIpForwardTable()
{
	PMIB_IPFORWARDTABLE pTable = NULL;
	DWORD dwSize = 0;

	VERIFY(ERROR_INSUFFICIENT_BUFFER == ::GetIpForwardTable(pTable, &dwSize, TRUE));
	pTable = (PMIB_IPFORWARDTABLE)(new char[dwSize]);
    VERIFY(NO_ERROR == ::GetIpForwardTable(pTable, &dwSize, TRUE));
    return pTable;
}


BOOL CIpHlpMiscDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	PMIB_IPFORWARDTABLE pTable = GetIpForwardTable();
	PMIB_IPFORWARDROW pRow;
	DWORD dwGateway = 0;
	for(int i=0; i<pTable->dwNumEntries; i++)
	{
		pRow = &pTable->table[i];
		if (pRow->dwForwardDest == 0)
		{
			dwGateway = pRow->dwForwardNextHop;
			break;
		}
	}
	delete [] ((char*)pTable);

	if (dwGateway != 0)
	{
		m_IPGateWay.SetAddress(ntohl(dwGateway));
	}

	GetFirstInterfaceDescription();
	GetAdapterInfo();
	return TRUE;  
}

void CIpHlpMiscDlg::OnBtnChangeDefaultGateway() 
{
	PMIB_IPFORWARDTABLE pTable = GetIpForwardTable();
	PMIB_IPFORWARDROW pRow;
	MIB_IPFORWARDROW  row;
	DWORD dwNewGateway;
    m_IPGateWay.GetAddress(dwNewGateway);

	if (dwNewGateway == 0)
	{
		AfxMessageBox("请设置新默认网关");
		return;
	}
	for(int i=0; i<pTable->dwNumEntries; i++)
	{
		pRow = &pTable->table[i];
		if (pRow->dwForwardDest == 0)
		{
			memcpy(&row, pRow, sizeof(MIB_IPFORWARDROW));
			DeleteIpForwardEntry(pRow);
			row.dwForwardNextHop = htonl(dwNewGateway);
			SetIpForwardEntry(&row);
			AfxMessageBox("设置默认网关成功");
			break;
		}
	}
	delete [] ((char*)pTable);

}

void CIpHlpMiscDlg::GetFirstInterfaceDescription()
{
    PMIB_IFTABLE pTable = NULL;
	MIB_IFROW row;
	DWORD dwSize = 0;

	VERIFY(ERROR_INSUFFICIENT_BUFFER == GetIfTable(pTable, &dwSize, FALSE));
	pTable = (PMIB_IFTABLE)(new char[dwSize]);
    if (NO_ERROR != GetIfTable(pTable, &dwSize, FALSE) || pTable->dwNumEntries <= 0)
	{
		delete [] ((char*)pTable);
		return;
	}
    delete [] ((char*)pTable);
	row.dwIndex = 1;
	VERIFY(NO_ERROR == GetIfEntry(&row));
	m_strFirstInterfaceDesc = (char*)row.bDescr;
	UpdateData(FALSE);
}

void CIpHlpMiscDlg::GetAdapterInfo()
{
    PIP_INTERFACE_INFO pInfo = NULL;
	DWORD dwSize = 0;

	VERIFY(ERROR_INSUFFICIENT_BUFFER == ::GetInterfaceInfo(pInfo, &dwSize));
	pInfo = (PIP_INTERFACE_INFO)(new char[dwSize]);
    if (NO_ERROR != ::GetInterfaceInfo(pInfo, &dwSize))
	{
		delete [] ((char*)pInfo);
		return;
	}
	char buf[100] = {0};
	sprintf(buf, "适配器名称: %ws", pInfo->Adapter[0].Name);
    m_strAdapterName = buf;
	m_strAdapterIndex.Format("适配器Index: %d", pInfo->Adapter[0].Index);
	m_strAdapterNum.Format("适配器数目: %d", pInfo->NumAdapters);
	UpdateData(FALSE);
	delete [] ((char*)pInfo);
}

void CIpHlpMiscDlg::OnBtnGetMac() 
{
	DWORD dwAddr;
	m_strMac = "";
	UpdateData(FALSE);
	m_IPHost.GetAddress(dwAddr);
	if (dwAddr == 0)
	{
		AfxMessageBox("请输入要获取MAC地址的主机IP");
		return;
	}
	UCHAR mac[6];
	memset(mac, 0xff, 6);
	ULONG ulen = 6;
	DWORD dw = htonl(dwAddr);
	if (NO_ERROR != SendARP(htonl(dwAddr), 0, (ULONG*)mac, &ulen))
	{
		CString str;
		DWORD dw = htonl(dwAddr);
		str.Format("获取主机%s的MAC地址失败, 可能主机没有开， 没有联网， 或不存在", inet_ntoa(*((in_addr*)&dw)));
		AfxMessageBox(str);
		return;
	}
	m_strMac.Format("%02X-%02X-%02X-%02X-%02X-%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	UpdateData(FALSE);
}
/////////////////////////////////////////////////////////////////////////////
// CIpHlpMiscDlg2 dialog
IMPLEMENT_DYNCREATE(CIpHlpMiscDlg2, CRootDlg)

CIpHlpMiscDlg2::CIpHlpMiscDlg2(CWnd* pParent /*=NULL*/)
	: CRootDlg(CIpHlpMiscDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIpHlpMiscDlg2)
	m_strIndex = _T("");
	m_strIpAddr = _T("");
	//}}AFX_DATA_INIT
}


void CIpHlpMiscDlg2::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIpHlpMiscDlg2)
	DDX_Control(pDX, IDC_IPADDRESS, m_IPAddress);
	DDX_Control(pDX, IDC_COMBO_IPADDR, m_CmbIpAddr);
	DDX_Control(pDX, IDC_COMBO_INDEX, m_CombIndex);
	DDX_Control(pDX, IDC_BUTTON1, m_btnArpFunc);
	DDX_CBString(pDX, IDC_COMBO_INDEX, m_strIndex);
	DDX_CBString(pDX, IDC_COMBO_IPADDR, m_strIpAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIpHlpMiscDlg2, CRootDlg)
	//{{AFX_MSG_MAP(CIpHlpMiscDlg2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_INDEX, OnSelchangeComboIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIpHlpMiscDlg2 message handlers

BOOL CIpHlpMiscDlg2::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	menu.LoadMenu (IDR_MENU4);
	m_btnArpFunc.m_hMenu = menu.GetSubMenu (0)->GetSafeHmenu ();
	m_btnArpFunc.SizeToContent ();
	RefreshArpTable();
	return TRUE;
}

void CIpHlpMiscDlg2::OnButton1() 
{
	UpdateData();
    switch (m_btnArpFunc.m_nMenuResult)
	{
	case IDM_REFRESH_ARP_TABLE:
		RefreshArpTable();
		break;
	case IDM_ADD_ARP_ENTRY:
        AddARPEntry();
		break;
	case IDM_DEL_ARP_ENTRY:
        DeleteArpEntry();
		break;
	case IDR_SEND_RAW_UDP_PACKET:
		SendRawUdpPacket();
		break;
	default:
		return;
	}
}

bool CIpHlpMiscDlg2::RefreshArpTable()
{
    PMIB_IPNETTABLE pTable = NULL;
	DWORD dwSize = 0;
	VERIFY(ERROR_INSUFFICIENT_BUFFER == ::GetIpNetTable(pTable, &dwSize, FALSE));
    pTable = (PMIB_IPNETTABLE)new char[dwSize];
    if (NO_ERROR != ::GetIpNetTable(pTable, &dwSize, FALSE))
	{
        delete [] (char*)pTable;
		return false;
	}
    m_aArpTable.clear();
	for(int i=0; i<pTable->dwNumEntries; i++)
	{
		PMIB_IPNETROW pRow = &pTable->table[i];
		int index = pRow->dwIndex;
		CString strIP = inet_ntoa(*((in_addr*)&pRow->dwAddr));
		map<int, vector<CString> >::iterator it = m_aArpTable.find(index);
		if (it == m_aArpTable.end())
		{
			vector<CString> aIp;
			aIp.push_back(strIP);
			m_aArpTable.insert(make_pair(index, aIp));
		}
		else
		{
			vector<CString>& aIp = it->second;
            aIp.push_back(strIP);
		}
	}
	delete [] (char*)pTable;

	RefreshArpControl();
	return true;
}

void CIpHlpMiscDlg2::RefreshArpControl()
{
	m_CmbIpAddr.ResetContent();
	m_CombIndex.ResetContent();
	map<int, vector<CString> >::iterator it;
	for(it = m_aArpTable.begin(); it!=m_aArpTable.end(); it++)
	{
        CString strIndex;
		strIndex.Format("%d", it->first);
		m_CombIndex.AddString(strIndex);

		if (it == m_aArpTable.begin())
		{
			vector<CString>& aIP = it->second;
			vector<CString>::iterator itIP;
			for(itIP=aIP.begin(); itIP!=aIP.end(); itIP++)
				m_CmbIpAddr.AddString(*itIP);
		}
	}
	m_CmbIpAddr.SetCurSel(0);
	m_CombIndex.SetCurSel(0);
}

void CIpHlpMiscDlg2::AddARPEntry()
{
	UpdateData();
    DWORD dwAddr;
	m_IPAddress.GetAddress(dwAddr);
	if (dwAddr == 0)
	{
		AfxMessageBox("请输入要添加的ARP条目IP地址");
		return;
	}
	MIB_IPNETROW row;
	int index = atoi(m_strIndex);
	PMIB_IPNETTABLE pTable = NULL;
	DWORD dwSize = 0;
	VERIFY(ERROR_INSUFFICIENT_BUFFER == ::GetIpNetTable(pTable, &dwSize, FALSE));
    pTable = (PMIB_IPNETTABLE)new char[dwSize];
    if (NO_ERROR != ::GetIpNetTable(pTable, &dwSize, FALSE))
	{
        delete [] (char*)pTable;
		CString strErr;
		GetErrorMessage(WSAGetLastError(), strErr);
		AfxMessageBox("添加ARP条目失败.失败原因: "+strErr);
		return;
	}
	for(int i=0; i<pTable->dwNumEntries; i++)
	{
		PMIB_IPNETROW pRow = &pTable->table[i];
		int index2 = pRow->dwIndex;
		if (index2 == index)
		{
			memcpy(&row, pRow, sizeof(row));
			break;
		}
	}
	delete [] (char*)pTable;
	row.dwIndex = index;
	row.dwAddr = htonl(dwAddr);
	if (NO_ERROR != SetIpNetEntry(&row))
	{
		CString strErr;
		GetErrorMessage(WSAGetLastError(), strErr);
		AfxMessageBox("添加ARP条目失败.失败原因: "+strErr);
		return;
	}
	AfxMessageBox("添加ARP条目成功");
	RefreshArpTable();
}

void CIpHlpMiscDlg2::DeleteArpEntry()
{
    UpdateData();
	int index = atoi(m_strIndex);
	DWORD dwAddr = inet_addr(m_strIpAddr);
	MIB_IPNETROW row;
	row.dwIndex = index;
	row.dwAddr = dwAddr;

	if (NO_ERROR != ::DeleteIpNetEntry(&row))
	{
        CString strErr;
		GetErrorMessage(WSAGetLastError(), strErr);
		AfxMessageBox("删除ARP条目失败.失败原因: "+strErr);
		return;
	}
	AfxMessageBox("删除ARP条目成功");
	RefreshArpTable();
}

void CIpHlpMiscDlg2::OnSelchangeComboIndex() 
{
	int i = m_CombIndex.GetCurSel();
	CString strIndex;
	m_CombIndex.GetLBText(i, strIndex);
	int index = atoi(strIndex);
	map<int, vector<CString> >::iterator it = m_aArpTable.find(index);
	if (it != m_aArpTable.end())
	{
		m_CmbIpAddr.ResetContent();
		for(vector<CString>::iterator it2=it->second.begin(); it2!=it->second.end(); it2++)
			m_CmbIpAddr.AddString(*it2);
	}
}

void CIpHlpMiscDlg2::SendRawUdpPacket()
{
    CString strMsg = "My Raw Udp Message";
	CString strSourceIP = "192.168.1.11";
	CString strDestIP = "192.168.1.19";
	USHORT uSourcePort = 80;
	USHORT uDestPort = 21;
	CSendRawUdpPacket temp;
	temp.SendPacket(strMsg.GetBuffer(0), strMsg.GetLength(), strSourceIP.GetBuffer(0), strDestIP.GetBuffer(0), uSourcePort, uDestPort);
}
