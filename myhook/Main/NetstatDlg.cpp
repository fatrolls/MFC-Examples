// NetstatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include "NetstatDlg.h"

#pragma comment(lib, "iphlpapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetstatDlg dialog
IMPLEMENT_DYNCREATE(CNetstatDlg, CRootDlg)

CNetstatDlg::CNetstatDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CNetstatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetstatDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hDll = LoadLibrary("iphlpapi.dll");
	m_pGetTcpTable = NULL;
	m_pGetUdpTable = NULL;
	if (m_hDll != NULL)
	{
		m_pGetTcpTable = (PFAllocateAndGetTcpExTableFromStack)GetProcAddress(m_hDll, "AllocateAndGetTcpExTableFromStack");
        m_pGetUdpTable = (PFNAllocateAndGetUdpExTableFromStack)GetProcAddress(m_hDll, "AllocateAndGetUdpExTableFromStack");
	}
}


void CNetstatDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetstatDlg)
	DDX_Control(pDX, IDC_LIST_UDP_TABLE, m_lstUdpTable);
	DDX_Control(pDX, IDC_LIST_TCP_TABLE, m_lstTcpTable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetstatDlg, CRootDlg)
	//{{AFX_MSG_MAP(CNetstatDlg)
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDR_REFRESH, OnRefresh)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetstatDlg message handlers

BOOL CNetstatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    m_lstTcpTable.InsertColumn(0, "Local IP", LVCFMT_LEFT, 85);
	m_lstTcpTable.InsertColumn(1, "Local Port", LVCFMT_LEFT, 70);
	m_lstTcpTable.InsertColumn(2, "Remote IP", LVCFMT_LEFT, 85);
	m_lstTcpTable.InsertColumn(3, "Remote Port", LVCFMT_LEFT, 70);
	m_lstTcpTable.InsertColumn(4, "Exe", LVCFMT_LEFT, 80);
	m_lstTcpTable.InsertColumn(5, "ID", LVCFMT_LEFT, 50);
	m_lstTcpTable.InsertColumn(6, "State", LVCFMT_LEFT, 50);
	GetTcpTable();
	m_lstUdpTable.InsertColumn(0, "Local IP", LVCFMT_LEFT, 85);
	m_lstUdpTable.InsertColumn(1, "Local Port", LVCFMT_LEFT, 70);
	m_lstUdpTable.InsertColumn(2, "Remote IP", LVCFMT_LEFT, 85);
	m_lstUdpTable.InsertColumn(3, "Remote Port", LVCFMT_LEFT, 70);
	m_lstUdpTable.InsertColumn(4, "Exe", LVCFMT_LEFT, 80);
	m_lstUdpTable.InsertColumn(5, "ID", LVCFMT_LEFT, 50);
	GetUdpTable();
	return TRUE; 
}

void CNetstatDlg::OnDestroy() 
{
	CRootDlg::OnDestroy();
    if (m_hDll != NULL)
		FreeLibrary(m_hDll);
}

void CNetstatDlg::GetTcpTable()
{
	PMIB_TCPEXTABLE pTcpTable;

	if (m_pGetTcpTable == NULL)
		return;
	if (m_pGetTcpTable(&pTcpTable, TRUE, GetProcessHeap(), 2, 2) != 0)
		return;
	// 给系统内的所有进程拍一个快照
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE)
	{
		LocalFree(pTcpTable);
		return;
	}

	m_lstTcpTable.DeleteAllItems();
    
	CString strState;
	CString strLocalIP;
	CString strLocalPort;
	CString strRemoteIP;
	CString strRemotePort;
	CString strProcessName;
	CString strProcessID;

	for(int i=0; i<pTcpTable->dwNumEntries; i++)
	{
		PMIB_TCPEXROW pRow = &pTcpTable->table[i];
        switch(pRow->dwState)
		{
        case MIB_TCP_STATE_CLOSED:
			strState = "CLOSED";
			break;
		case MIB_TCP_STATE_TIME_WAIT:
			strState = "TIME_WAIT";
			break;
		case MIB_TCP_STATE_LAST_ACK:
			strState = "LAST_ACK";
			break;
		case MIB_TCP_STATE_CLOSING:
			strState = "CLOSING";
			break;
		case MIB_TCP_STATE_CLOSE_WAIT:
			strState = "CLOSE_WAIT";
			break;
		case MIB_TCP_STATE_FIN_WAIT1:
			strState = "FIN_WAIT1";
			break;
		case MIB_TCP_STATE_ESTAB:
			strState = "ESTAB";
			break;
		case MIB_TCP_STATE_SYN_RCVD:
			strState = "SYN_RCVD";
			break;
		case MIB_TCP_STATE_SYN_SENT:
			strState = "SYN_SENT";
			break;
		case MIB_TCP_STATE_LISTEN:
			strState = "LISTEN";
			break;
		case MIB_TCP_STATE_DELETE_TCB:
			strState = "DELETE";
			break;
		default:
			strState = "状态未知";
			break;
		}
		strLocalIP = inet_ntoa(*((in_addr*)(&pRow->dwLocalAddr)));
		strLocalPort.Format("%d", ntohs(pRow->dwLocalPort));
		strRemoteIP = inet_ntoa(*((in_addr*)(&pRow->dwRemoteAddr)));
		strRemotePort.Format("%d", strState != "LISTEN" ? ntohs(pRow->dwRemotePort) : 0);
		strProcessName = ProcessPidToName(hSnap, pRow->dwProcessId);
		strProcessID.Format("%d", pRow->dwProcessId);
		m_lstTcpTable.InsertItem(i, strLocalIP);
		m_lstTcpTable.SetItemText(i, 1, strLocalPort);
		m_lstTcpTable.SetItemText(i, 2, strRemoteIP);
		m_lstTcpTable.SetItemText(i, 3, strRemotePort);
		m_lstTcpTable.SetItemText(i, 4, strProcessName);
		m_lstTcpTable.SetItemText(i, 5, strProcessID);
		m_lstTcpTable.SetItemText(i, 6, strState);
	}
	
	CloseHandle(hSnap);
	LocalFree(pTcpTable);
}

void CNetstatDlg::GetUdpTable()
{
    PMIB_UDPEXTABLE pUdpTable;

	if (m_pGetUdpTable == NULL)
		return;
	if(m_pGetUdpTable(&pUdpTable, TRUE, GetProcessHeap(), 2, 2) != 0)
	    return;

	// 给系统内的所有进程拍一个快照
	HANDLE hSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnap == INVALID_HANDLE_VALUE)
	{
		LocalFree(pUdpTable);
		return;
	}

	m_lstUdpTable.DeleteAllItems();

	CString strLocalIP;
	CString strLocalPort;
	CString strRemoteIP = "*.*.*.*";
	CString strRemotePort = "*";
	CString strProcessName;
	CString strProcessID;
	for(int i = 0; i < pUdpTable->dwNumEntries; ++i)
	{
		PMIB_UDPEXROW pRow = &pUdpTable->table[i];
		strLocalIP = inet_ntoa(*((in_addr*)(&pRow->dwLocalAddr)));
		strLocalPort.Format("%d", ntohs(pRow->dwLocalPort));
		strProcessName = ProcessPidToName(hSnap, pRow->dwProcessId);
		strProcessID.Format("%d", pRow->dwProcessId);
        m_lstUdpTable.InsertItem(i, strLocalIP);
		m_lstUdpTable.SetItemText(i, 1, strLocalPort);
		m_lstUdpTable.SetItemText(i, 2, strRemoteIP);
		m_lstUdpTable.SetItemText(i, 3, strRemotePort);
		m_lstUdpTable.SetItemText(i, 4, strProcessName);
		m_lstUdpTable.SetItemText(i, 5, strProcessID);
	}
	LocalFree(pUdpTable);
	CloseHandle(hSnap);
}

CString CNetstatDlg::ProcessPidToName(HANDLE hSnap, DWORD dwProcessId)
{
	 PROCESSENTRY32 entry;
	 entry.dwSize = sizeof(entry);

	 if (!Process32First(hSnap, &entry))
		 return "???";
	 do 
	 {
		 if (entry.th32ProcessID == dwProcessId)
			 return entry.szExeFile;
	 } while(Process32Next(hSnap, &entry));
	 return "???";
}

void CNetstatDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CPoint pt;
	GetCursorPos(&pt);
	CRect rcTcp, rcUDP;
	m_lstTcpTable.GetWindowRect(rcTcp);
	m_lstUdpTable.GetWindowRect(rcUDP);
	if (rcTcp.PtInRect(pt) || rcUDP.PtInRect(pt))
	{
		if (rcTcp.PtInRect(pt))
			m_lstTcpTable.SetFocus();
		else
			m_lstUdpTable.SetFocus();
		CMenu menu;
		menu.LoadMenu(IDR_MENU2);
		CMenu* pMenu = menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this, NULL);
	}
}

void CNetstatDlg::OnRefresh() 
{
    CWnd* pWnd = GetFocus();
	if (pWnd->m_hWnd == m_lstTcpTable.m_hWnd)
		GetTcpTable();
	else if (pWnd->m_hWnd == m_lstUdpTable.m_hWnd)
		GetUdpTable();
}

void CNetstatDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CRootDlg::OnShowWindow(bShow, nStatus);
	CRect rcWindow;
	GetWindowRect(rcWindow);
	CRect rcTcpTable, rcUdpTable;
	m_lstTcpTable.GetWindowRect(rcTcpTable);
	m_lstUdpTable.GetWindowRect(rcUdpTable);
	rcTcpTable.right = rcWindow.right - 10;
	rcUdpTable.right = rcWindow.right - 10;
	ScreenToClient(&rcTcpTable);
	ScreenToClient(&rcUdpTable);
	m_lstTcpTable.MoveWindow(rcTcpTable);
	m_lstUdpTable.MoveWindow(rcUdpTable);
}
