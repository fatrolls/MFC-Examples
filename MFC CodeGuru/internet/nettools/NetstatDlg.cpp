// NetstatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nettools.h"
#include "inetthreadparms.h"
#include "NetstatDlg.h"
//#include "Worker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetstatDlg dialog


CNetstatDlg::CNetstatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetstatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetstatDlg)
	m_connections = FALSE;
	m_icmpstats = FALSE;
	m_ifstats = FALSE;
	m_ipstats = FALSE;
	m_routes = FALSE;
	m_tcpstats = FALSE;
	m_udpstats = FALSE;
	m_all = FALSE;
	m_resolve = FALSE;
	//}}AFX_DATA_INIT
}


void CNetstatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetstatDlg)
	DDX_Check(pDX, IDC_NETSTAT_OPT_CONNS, m_connections);
	DDX_Check(pDX, IDC_NETSTAT_OPT_ICMPSTATS, m_icmpstats);
	DDX_Check(pDX, IDC_NETSTAT_OPT_IFSTATS, m_ifstats);
	DDX_Check(pDX, IDC_NETSTAT_OPT_IPSTATS, m_ipstats);
	DDX_Check(pDX, IDC_NETSTAT_OPT_ROUTES, m_routes);
	DDX_Check(pDX, IDC_NETSTAT_OPT_TCPSTATS, m_tcpstats);
	DDX_Check(pDX, IDC_NETSTAT_OPT_UDPSTATS, m_udpstats);
	DDX_Check(pDX, IDC_NETSTAT_OPT_ALL, m_all);
	DDX_Check(pDX, IDC_NETSTAT_OPT_RESOLVE, m_resolve);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetstatDlg, CDialog)
	//{{AFX_MSG_MAP(CNetstatDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetstatDlg message handlers

void CNetstatDlg::OnOK() 
{
	if (!UpdateData(TRUE))  // retrieve and validate data
		return;				// validate failed

	m_lpInetParms->connections = m_connections;
	m_lpInetParms->icmpstats = m_icmpstats;
	m_lpInetParms->ifstats = m_ifstats;
	m_lpInetParms->ipstats = m_ipstats;
	m_lpInetParms->routtable = m_routes;
	m_lpInetParms->tcpstats = m_tcpstats;
	m_lpInetParms->udpstats = m_udpstats;
	m_lpInetParms->allopts =  m_all;
	m_lpInetParms->resolveaddrs = m_resolve;
	
	CDialog::OnOK();
}

