// NetStatisticsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include "NetStatisticsDlg.h"

#pragma comment(lib, "iphlpapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetStatisticsDlg dialog
IMPLEMENT_DYNCREATE(CNetStatisticsDlg, CRootDlg)

CNetStatisticsDlg::CNetStatisticsDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CNetStatisticsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNetStatisticsDlg)
	//}}AFX_DATA_INIT
}


void CNetStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetStatisticsDlg)
	DDX_Control(pDX, IDC_BTN_FUNCTION, m_btnFunction);
	DDX_Control(pDX, IDC_STATIC_TYPE, m_wndType);
	DDX_Control(pDX, IDC_STATIC_PLACE, m_wndPlace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNetStatisticsDlg, CRootDlg)
	//{{AFX_MSG_MAP(CNetStatisticsDlg)
	ON_BN_CLICKED(IDC_BTN_FUNCTION, OnBtnFunction)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetStatisticsDlg message handlers

BOOL CNetStatisticsDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	CRect rectDummy;
	m_wndPlace.GetWindowRect(rectDummy);
	ScreenToClient(&rectDummy);
	if (!m_wndPropList.Create (WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	    return FALSE;
	m_wndPropList.EnableHeaderCtrl (FALSE);
	//m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();

	menu.LoadMenu (IDR_MENU3);
	m_btnFunction.m_hMenu = menu.GetSubMenu (0)->GetSafeHmenu ();
	m_btnFunction.SizeToContent ();
	return TRUE;
}

void CNetStatisticsDlg::OnBtnFunction() 
{
	UpdateData();
    switch (m_btnFunction.m_nMenuResult)
	{
	case IDM_IP_STATS:
		GetIpStatistics();
		break;
	case IDM_ICMP_STATS:
        GetIcmpStatistics();	
		break;
	case IDM_TCP_STATS:
        GetTcpStatistics();		
		break;
	case IDM_UDP_STATS:
        GetUdpStatistics();		
		break;
	default:
		return;
	}
}

CBCGPProp* CNetStatisticsDlg::AddGroupProp(CString strName, CBCGPProp* pParent)
{
	CBCGPProp* pProp = new CBCGPProp(_T(strName));
	if (pParent == NULL)
		m_wndPropList.AddProperty(pProp);
	else
		pParent->AddSubItem(pProp);
	return pProp;
}

void CNetStatisticsDlg::AddChildProp(CString strName, CString strValue, CBCGPProp* pParent)
{
    CBCGPProp* pProp = new CBCGPProp(_T(strName), (_variant_t)(_bstr_t)strValue, "");
	if (pParent == NULL)
		m_wndPropList.AddProperty(pProp);
	else
		pParent->AddSubItem(pProp);
}

void CNetStatisticsDlg::OnDestroy() 
{
	CRootDlg::OnDestroy();
    m_wndPropList.DestroyWindow();
}


void CNetStatisticsDlg::GetIpStatistics()
{
	MIB_IPSTATS ipstats;

	m_wndType.SetWindowText("IP统计数据");
	m_wndPropList.RemoveAll();

	if (NO_ERROR != ::GetIpStatistics(&ipstats))
		return;
	
    CString dwForwarding;
	CString dwDefaultTTL;
	CString dwInReceives;
	CString dwInHdrErrors;
	CString dwInAddrErrors;
	CString dwForwDatagrams;
	CString dwInUnknownProtos;
	CString dwInDiscards;
	CString dwInDelivers;
	CString dwOutRequests;
	CString dwRoutingDiscards;
	CString dwOutDiscards;
	CString dwOutNoRoutes;
	CString dwReasmTimeout;
	CString dwReasmReqds;
	CString dwReasmOks;
	CString dwReasmFails;
	CString dwFragOks;
	CString dwFragFails;
	CString dwFragCreates;
	CString dwNumIf;
	CString dwNumAddr;
	CString dwNumRoutes;
    PMIB_IPSTATS pStats = &ipstats;

	dwForwarding.Format("%lu", pStats->dwForwarding);
    dwDefaultTTL.Format("%lu", pStats->dwDefaultTTL);
    dwInReceives.Format("%lu", pStats->dwInReceives);
    dwInHdrErrors.Format("%lu", pStats->dwInHdrErrors);
    dwInAddrErrors.Format("%lu", pStats->dwInAddrErrors);
    dwForwDatagrams.Format("%lu", pStats->dwForwDatagrams);
    dwInUnknownProtos.Format("%lu", pStats->dwInUnknownProtos);
    dwInDiscards.Format("%lu", pStats->dwInDiscards);
    dwInDelivers.Format("%lu", pStats->dwInDelivers);
    dwOutRequests.Format("%lu", pStats->dwOutRequests);
    dwRoutingDiscards.Format("%lu", pStats->dwRoutingDiscards);
    dwOutDiscards.Format("%lu", pStats->dwOutDiscards);
    dwOutNoRoutes.Format("%lu", pStats->dwOutNoRoutes);
    dwReasmTimeout.Format("%lu", pStats->dwReasmTimeout);
    dwReasmReqds.Format("%lu", pStats->dwReasmReqds);
    dwReasmOks.Format("%lu", pStats->dwReasmOks);
    dwReasmFails.Format("%lu", pStats->dwReasmFails);
    dwFragOks.Format("%lu", pStats->dwFragOks);
    dwFragFails.Format("%lu", pStats->dwFragFails);
    dwFragCreates.Format("%lu", pStats->dwFragCreates);
    dwNumIf.Format("%lu", pStats->dwNumIf);
    dwNumAddr.Format("%lu", pStats->dwNumAddr);
    dwNumRoutes.Format("%lu", pStats->dwNumRoutes);

	AddChildProp("dwForwarding", dwForwarding);
    AddChildProp("dwDefaultTTL", dwDefaultTTL);
	AddChildProp("dwInReceives", dwInReceives);
	AddChildProp("dwInHdrErrors", dwInHdrErrors);
	AddChildProp("dwInAddrErrors", dwInAddrErrors);
    AddChildProp("dwForwDatagrams", dwForwDatagrams);
	AddChildProp("dwInUnknownProtos", dwInUnknownProtos);
	AddChildProp("dwInDiscards", dwInDiscards);
	AddChildProp("dwInDelivers", dwInDelivers);
    AddChildProp("dwOutRequests", dwOutRequests);
	AddChildProp("dwOutRequests", dwOutRequests);
	AddChildProp("dwRoutingDiscards", dwRoutingDiscards);
	AddChildProp("dwOutDiscards", dwOutDiscards);
    AddChildProp("dwOutNoRoutes", dwOutNoRoutes);
	AddChildProp("dwReasmTimeout", dwReasmTimeout);
	AddChildProp("dwReasmReqds", dwReasmReqds);
	AddChildProp("dwReasmOks", dwReasmOks);
    AddChildProp("dwReasmFails", dwReasmFails);
	AddChildProp("dwFragOks", dwFragOks);
	AddChildProp("dwFragFails", dwFragFails);
	AddChildProp("dwFragCreates", dwFragCreates);
    AddChildProp("dwNumIf", dwNumIf);
	AddChildProp("dwNumAddr", dwNumAddr);
	AddChildProp("dwNumRoutes", dwNumRoutes);
}

void CNetStatisticsDlg::GetIcmpStatistics()
{
	m_wndType.SetWindowText("ICMP统计数据");
	m_wndPropList.RemoveAll();
	MIB_ICMP icmpstats;
	if (NO_ERROR != ::GetIcmpStatistics(&icmpstats))
		return;
	MIBICMPINFO* pStats = (MIBICMPINFO*)&icmpstats;
	CString dwInMsgs, dwOutMsg;
	dwInMsgs.Format("%lu", pStats->icmpInStats.dwMsgs);
	dwOutMsg.Format("%lu", pStats->icmpOutStats.dwMsgs);
    CString dwInErrors, dwOutErrors;
	dwInErrors.Format("%ld", pStats->icmpInStats.dwErrors);
	dwOutErrors.Format("%lu", pStats->icmpOutStats.dwErrors);
    CString dwInDestUnreachs, dwOutDestUnreachs;
	dwInDestUnreachs.Format("%lu", pStats->icmpInStats.dwDestUnreachs);
	dwOutDestUnreachs.Format("%lu", pStats->icmpOutStats.dwDestUnreachs);
    CString dwInTimeExcds, dwOutTimeExcds;
	dwInTimeExcds.Format("%lu", pStats->icmpInStats.dwTimeExcds);
	dwOutTimeExcds.Format("%lu", pStats->icmpOutStats.dwTimeExcds);
    CString dwInParmProbs, dwOutParmProbs;
	dwInParmProbs.Format("%lu", pStats->icmpInStats.dwParmProbs);
	dwOutParmProbs.Format("%lu", pStats->icmpOutStats.dwParmProbs);
    CString dwInSrcQuenchs, dwOutSrcQuenchs;
	dwInSrcQuenchs.Format("%lu", pStats->icmpInStats.dwSrcQuenchs);
	dwOutSrcQuenchs.Format("%lu", pStats->icmpOutStats.dwSrcQuenchs);
    CString dwInRedirects, dwOutRedirects;
	dwInRedirects.Format("%lu", pStats->icmpInStats.dwRedirects);
	dwOutRedirects.Format("%lu", pStats->icmpOutStats.dwRedirects);
    CString dwInEchos, dwOutEchos;
	dwInEchos.Format("%lu", pStats->icmpInStats.dwEchos);
	dwOutEchos.Format("%lu", pStats->icmpOutStats.dwEchos);
    CString dwInEchoReps, dwOutEchoReqs;
	dwInEchoReps.Format("%lu", pStats->icmpInStats.dwEchoReps);
	dwOutEchoReqs.Format("%lu", pStats->icmpOutStats.dwEchoReps);
    CString dwInTimestamps, dwOutTimestamps;
	dwInTimestamps.Format("%lu", pStats->icmpInStats.dwTimestamps);
	dwOutTimestamps.Format("%lu", pStats->icmpOutStats.dwTimestamps);
    CString dwInTimestampReps, dwOutTimestampReps;
	dwInTimestampReps.Format("%lu", pStats->icmpInStats.dwTimestampReps);
	dwOutTimestampReps.Format("%lu", pStats->icmpOutStats.dwTimestampReps);
    CString dwInAddrMasks, dwOutAddrMasks; 
	dwInAddrMasks.Format("%lu", pStats->icmpInStats.dwAddrMasks);
	dwOutAddrMasks.Format("%lu", pStats->icmpOutStats.dwAddrMasks);
    CString dwInAddrMaskReps, dwOutAddrMaskReps;
	dwInAddrMaskReps.Format("%lu", pStats->icmpInStats.dwAddrMaskReps);
	dwOutAddrMaskReps.Format("%lu", pStats->icmpOutStats.dwAddrMaskReps);

	AddChildProp("dwInMsgs", dwInMsgs);
    AddChildProp("dwOutMsg", dwOutMsg);
	AddChildProp("dwInErrors", dwInErrors);
	AddChildProp("dwOutErrors", dwOutErrors);
	AddChildProp("dwInDestUnreachs", dwInDestUnreachs);
    AddChildProp("dwOutDestUnreachs", dwOutDestUnreachs);
	AddChildProp("dwInTimeExcds", dwInTimeExcds);
	AddChildProp("dwOutTimeExcds", dwOutTimeExcds);
	AddChildProp("dwInParmProbs", dwInParmProbs);
    AddChildProp("dwOutParmProbs", dwOutParmProbs);
	AddChildProp("dwInSrcQuenchs", dwInSrcQuenchs);
	AddChildProp("dwOutSrcQuenchs", dwOutSrcQuenchs);
	AddChildProp("dwInRedirects", dwInRedirects);
    AddChildProp("dwOutRedirects", dwOutRedirects);
	AddChildProp("dwInEchos", dwInEchos);
	AddChildProp("dwOutEchos", dwOutEchos);
	AddChildProp("dwInEchoReps", dwInEchoReps);
    AddChildProp("dwOutEchoReqs", dwOutEchoReqs);
	AddChildProp("dwInTimestamps", dwInTimestamps);
	AddChildProp("dwOutTimestamps", dwOutTimestamps);
	AddChildProp("dwInTimestampReps", dwInTimestampReps);
    AddChildProp("dwOutTimestampReps", dwOutTimestampReps);
	AddChildProp("dwInAddrMasks", dwInAddrMasks);
	AddChildProp("dwOutAddrMasks", dwOutAddrMasks);
	AddChildProp("dwInAddrMaskReps", dwInAddrMaskReps);
	AddChildProp("dwOutAddrMaskReps", dwOutAddrMaskReps);
}

void CNetStatisticsDlg::GetTcpStatistics()
{
	m_wndType.SetWindowText("TCP统计数据");
	m_wndPropList.RemoveAll();
	MIB_TCPSTATS tcpstats;
	if (NO_ERROR != ::GetTcpStatistics(&tcpstats))
		return;
    PMIB_TCPSTATS pStats = &tcpstats;
	CString dwRtoAlgorithm;
	CString dwRtoMin;
	CString dwRtoMax;
	CString dwMaxConn;
	CString dwActiveOpens;
	CString dwPassiveOpens;
	CString dwAttemptFails;
	CString dwEstabResets;
	CString dwCurrEstab;
	CString dwInSegs;
	CString dwOutSegs;
	CString dwRetransSegs;
	CString dwInErrs;
	CString dwOutRsts;
	CString dwNumConns;

	dwRtoAlgorithm.Format("%lu", pStats->dwRtoAlgorithm);
	dwRtoMin.Format("%lu", pStats->dwRtoMin);
	dwRtoMax.Format("%lu", pStats->dwRtoMax);
	dwMaxConn.Format("%lu", pStats->dwMaxConn);
	dwActiveOpens.Format("%lu", pStats->dwActiveOpens);
	dwPassiveOpens.Format("%lu", pStats->dwPassiveOpens);
	dwAttemptFails.Format("%lu", pStats->dwAttemptFails);
	dwEstabResets.Format("%lu", pStats->dwEstabResets);
	dwCurrEstab.Format("%lu", pStats->dwCurrEstab);
	dwInSegs.Format("%lu", pStats->dwInSegs);
	dwOutSegs.Format("%lu", pStats->dwOutSegs);
	dwRetransSegs.Format("%lu", pStats->dwRetransSegs);
	dwInErrs.Format("%lu", pStats->dwInErrs);
	dwOutRsts.Format("%lu", pStats->dwOutRsts);
	dwNumConns.Format("%lu", pStats->dwNumConns);
		
	
	AddChildProp("dwRtoAlgorithm", dwRtoAlgorithm);
    AddChildProp("dwRtoMin", dwRtoMin);
	AddChildProp("dwRtoMax", dwRtoMax);
	AddChildProp("dwMaxConn", dwMaxConn);
	AddChildProp("dwActiveOpens", dwActiveOpens);
    AddChildProp("dwPassiveOpens", dwPassiveOpens);
	AddChildProp("dwAttemptFails", dwAttemptFails);
	AddChildProp("dwEstabResets", dwEstabResets);
	AddChildProp("dwCurrEstab", dwCurrEstab);
    AddChildProp("dwInSegs", dwInSegs);
	AddChildProp("dwOutSegs", dwOutSegs);
	AddChildProp("dwRetransSegs", dwRetransSegs);
	AddChildProp("dwInErrs", dwInErrs);
    AddChildProp("dwOutRsts", dwOutRsts);
	AddChildProp("dwNumConns", dwNumConns);
}

void CNetStatisticsDlg::GetUdpStatistics()
{
	m_wndType.SetWindowText("UDP统计数据");
	m_wndPropList.RemoveAll();

	MIB_UDPSTATS udpstats;
	if (NO_ERROR != ::GetUdpStatistics(&udpstats))
		return;
	PMIB_UDPSTATS pStats = &udpstats;
	CString dwInDatagrams;
	CString dwNoPorts;
	CString dwInErrors;
	CString dwOutDatagrams;
	CString dwNumAddrs;
	dwInDatagrams.Format("%lu", pStats->dwInDatagrams);
	dwNoPorts.Format("%lu", pStats->dwNoPorts);
	dwInErrors.Format("%lu", pStats->dwInErrors);
	dwOutDatagrams.Format("%lu", pStats->dwOutDatagrams);
	dwNumAddrs.Format("%lu", pStats->dwNumAddrs);
	AddChildProp("dwInDatagrams", dwInDatagrams);
	AddChildProp("dwNoPorts", dwNoPorts);
	AddChildProp("dwInErrors", dwInErrors);
    AddChildProp("dwOutDatagrams", dwOutDatagrams);
	AddChildProp("dwNumAddrs", dwNumAddrs);
}

