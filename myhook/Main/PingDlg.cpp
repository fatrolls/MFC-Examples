// PingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "PingDlg.h"
#include <winsock2.h>
#include "Helper.h"
#include "ProtocolTypes.h"
#include "iphlpapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoComplete

CAutoComplete::CAutoComplete()
{
	m_bAutoComplete = TRUE;
}

CAutoComplete::~CAutoComplete()
{
}


BEGIN_MESSAGE_MAP(CAutoComplete, CComboBox)
	//{{AFX_MSG_MAP(CAutoComplete)
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, OnEditUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoComplete message handlers

BOOL CAutoComplete::PreTranslateMessage(MSG* pMsg)
{
	// Need to check for backspace/delete. These will modify the text in
	// the edit box, causing the auto complete to just add back the text
	// the user has just tried to delete. 

	if (pMsg->message == WM_KEYDOWN)
	{
		m_bAutoComplete = TRUE;

		int nVirtKey = (int) pMsg->wParam;
		if (nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
			m_bAutoComplete = FALSE;
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

void CAutoComplete::OnEditUpdate() 
{
  // if we are not to auto update the text, get outta here
  if (!m_bAutoComplete) 
      return;

  // Get the text in the edit box
  CString str;
  GetWindowText(str);
  int nLength = str.GetLength();
  
  // Currently selected range
  DWORD dwCurSel = GetEditSel();
  WORD dStart = LOWORD(dwCurSel);
  WORD dEnd   = HIWORD(dwCurSel);

  // Search for, and select in, and string in the combo box that is prefixed
  // by the text in the edit box
  if (SelectString(-1, str) == CB_ERR)
  {
      SetWindowText(str);		// No text selected, so restore what was there before
      if (dwCurSel != CB_ERR)
        SetEditSel(dStart, dEnd);	//restore cursor postion
  }

  // Set the text selection as the additional text that we have added
  if (dEnd < nLength && dwCurSel != CB_ERR)
      SetEditSel(dStart, dEnd);
  else
      SetEditSel(nLength, -1);
}


/////////////////////////////////////////////////////////////////////////////
// CPingDlg dialog
IMPLEMENT_DYNCREATE(CPingDlg, CRootDlg)

CPingDlg::CPingDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CPingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPingDlg)
	m_bCheckPing = FALSE;
	m_strEndIP = _T("");
	m_strStartIP = _T("");
	m_iPingTimes = 0;
	//}}AFX_DATA_INIT
	m_bDraw = false;
	m_nPos = -1;
	m_bIncrease = true;
}


void CPingDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPingDlg)
	DDX_Control(pDX, IDC_SPIN1, m_spin);
	DDX_Control(pDX, IDC_CHECK_PING, m_CheckPing);
	DDX_Control(pDX, IDC_STATIC_END_IP, m_wndEndIP);
	DDX_Control(pDX, IDC_PIC_TO, m_wndPicTo);
	DDX_Control(pDX, IDC_PIC_FROM, m_wndPicFrom);
	DDX_Control(pDX, IDC_LIST_INFO, m_lstInfo);
	DDX_Control(pDX, IDC_CMB_START_IP, m_cmbStartIP);
	DDX_Control(pDX, IDC_CMB_END_IP, m_cmbEndIP);
	DDX_Check(pDX, IDC_CHECK_PING, m_bCheckPing);
	DDX_CBString(pDX, IDC_CMB_END_IP, m_strEndIP);
	DDX_CBString(pDX, IDC_CMB_START_IP, m_strStartIP);
	DDX_Text(pDX, IDC_EDIT_PING_TIMES, m_iPingTimes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPingDlg, CRootDlg)
	//{{AFX_MSG_MAP(CPingDlg)
	ON_BN_CLICKED(IDC_CHECK_PING, OnCheckPing)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_START_PING, OnBtnStartPing)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG_STATUS, OnSetStatus)
	ON_MESSAGE(WM_PING_END, OnPingEnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPingDlg message handlers

void CPingDlg::OnCheckPing() 
{
	UpdateData();
	if (m_bCheckPing)
	{
		m_CheckPing.SetWindowText("Ping一个网段");
		m_wndEndIP.EnableWindow(TRUE);
		m_cmbEndIP.EnableWindow(TRUE);
	}
	else
	{
        m_CheckPing.SetWindowText("Ping一个主机");
		m_wndEndIP.EnableWindow(FALSE);
		m_cmbEndIP.EnableWindow(FALSE);
	}
}

BOOL CPingDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	InitializeControls();
	return TRUE;
}

void CPingDlg::OnDestroy() 
{
	CRootDlg::OnDestroy();
	CMainApp* pApp = (CMainApp*)AfxGetApp();
	CString strKey;
	CString strValue;
	
	pApp->WriteProfileInt("StartIP", "Count", m_cmbStartIP.GetCount());
	for(int i=0; i<m_cmbStartIP.GetCount(); i++)
	{
		strKey.Format("Host#%d", i);
		m_cmbStartIP.GetLBText(i, strValue);
		pApp->WriteProfileString("StartIP", strKey, strValue);
	}
	
	pApp->WriteProfileInt("EndIP", "Count", m_cmbEndIP.GetCount());
	for(i=0; i<m_cmbEndIP.GetCount(); i++)
	{
		strKey.Format("Host#%d", i);
		m_cmbEndIP.GetLBText(i, strValue);
		pApp->WriteProfileString("EndIP", strKey, strValue);
	}
	m_imglst.DeleteImageList();
}

void CPingDlg::InitializeControls()
{
    CMainApp* pApp = (CMainApp*)AfxGetApp();
	CString strKey;
	CString strValue;
	int iCount;

	iCount = pApp->GetProfileInt("StartIP", "Count", 0);
	for(int i=0; i<iCount; i++)
	{
		strKey.Format("Host#%d", i);
		strValue = pApp->GetProfileString("StartIP", strKey, "");
		if (strValue != "")
			m_cmbStartIP.AddString(strValue);
	}

	iCount = pApp->GetProfileInt("EndIP", "Count", 0);
	for(i=0; i<iCount; i++)
	{
		strKey.Format("Host#%d", i);
		strValue = pApp->GetProfileString("EndIP", strKey, "");
		if (strValue != "")
			m_cmbEndIP.AddString(strValue);
	}

	m_spin.SetRange(1, 10);
	m_spin.SetPos(4);

	m_imglst.Create(IDB_LOG,16,1,RGB(255,0,255));
	m_lstInfo.SetImageList(&m_imglst, LVSIL_SMALL);
	m_lstInfo.InsertColumn(0,"状态",LVCFMT_LEFT,800);
	CRect rc;
	m_lstInfo.GetClientRect(rc);
	m_lstInfo.SetColumnWidth(0,rc.Width());

	CRect rcFrom, rcTo;
	m_wndPicFrom.GetWindowRect(rcFrom);
	m_wndPicTo.GetWindowRect(rcTo);
	ScreenToClient(&rcFrom);
	ScreenToClient(&rcTo);
	CPoint ptFrom = rcFrom.CenterPoint();
	CPoint ptTo = rcTo.CenterPoint();
	ptFrom.x = rcFrom.right;
	ptTo.x = rcTo.left;
	m_rcInvalidate = CRect(ptFrom.x-5, ptFrom.y -5, ptTo.x+5, ptTo.y + 5);
}

void CPingDlg::OnBtnStartPing() 
{
	UpdateData();
	if (!CheckError())
		return;
	int index = m_cmbStartIP.FindStringExact(-1, m_strStartIP);
	if (index == CB_ERR && m_strStartIP != "")
		m_cmbStartIP.AddString(m_strStartIP);
	index = m_cmbEndIP.FindStringExact(-1, m_strEndIP);
	if (index == CB_ERR && m_strEndIP != "")
		m_cmbEndIP.AddString(m_strEndIP);

	m_lstInfo.DeleteAllItems();
	m_bDraw = true;
	m_nPos = -1;
	m_bIncrease = true;
	SetTimer(1, 10, NULL);
	GetDlgItem(IDC_BTN_START_PING)->EnableWindow(FALSE);
	CPingThread* pThread = (CPingThread*)AfxBeginThread(RUNTIME_CLASS(CPingThread));
	pThread->StartPing(this);
}

bool CPingDlg::CheckError()
{
    ULONG ipFrom = inet_addr(m_strStartIP);
	if (ipFrom == INADDR_NONE)
	{
		AfxMessageBox("起始IP错误");
		m_cmbStartIP.SetFocus();
		return false;
	}
	int iDotCount1 = 0;
	CString key1, key2, key3, key4;
	int index;

	index = m_strStartIP.Find(".");
	if (index == -1)
	{
        AfxMessageBox("起始IP错误");
		m_cmbStartIP.SetFocus();
		return false;
	}
	iDotCount1 ++;
    key1 = m_strStartIP.Left(index);
	key2 = m_strStartIP.Right(m_strStartIP.GetLength()-index-1);

	index = key2.Find(".");
	if (index == -1)
	{
        AfxMessageBox("起始IP错误");
		m_cmbStartIP.SetFocus();
		return false;
	}
	iDotCount1 ++;
	key3 = key2.Right(key2.GetLength()-index-1);
    key2 = key2.Left(index);

	index = key3.Find(".");
	if (index == -1)
	{
        AfxMessageBox("起始IP错误");
		m_cmbStartIP.SetFocus();
		return false;
	}
	iDotCount1 ++;
	key4 = key3.Right(key3.GetLength()-index-1);
    key3 = key3.Left(index);
	

	index = key4.Find(".");
	if (index != -1)
	{
        AfxMessageBox("起始IP错误");
		m_cmbStartIP.SetFocus();
		return false;
	}

	int iStart = atoi(key4);

	if (m_bCheckPing)
	{
        ULONG ipTo = inet_addr(m_strEndIP);
		if (ipTo == INADDR_NONE)
		{
			AfxMessageBox("终止IP错误");
			m_cmbEndIP.SetFocus();
			return false;
		}
		
		int iDotCount2 = 0;
		CString key11, key21, key31, key41;
		int index;
		
		index = m_strEndIP.Find(".");
		if (index == -1)
		{
			AfxMessageBox("终止IP错误");
			m_cmbEndIP.SetFocus();
			return false;
		}
		iDotCount2 ++;
		key11 = m_strEndIP.Left(index);
		key21 = m_strEndIP.Right(m_strEndIP.GetLength()-index-1);
		
		index = key21.Find(".");
		if (index == -1)
		{
			AfxMessageBox("终止IP错误");
			m_cmbEndIP.SetFocus();
			return false;
		}
		iDotCount2 ++;
		key31 = key21.Right(key21.GetLength()-index-1);
		key21 = key21.Left(index);
		
		
		index = key31.Find(".");
		if (index == -1)
		{
			AfxMessageBox("终止IP错误");
			m_cmbEndIP.SetFocus();
			return false;
		}
		iDotCount2 ++;
		key41 = key31.Right(key31.GetLength()-index-1);
		key31 = key31.Left(index);
		
		
		index = key41.Find(".");
		if (index != -1)
		{
			AfxMessageBox("终止IP错误");
			m_cmbEndIP.SetFocus();
			return false;
		}

		if (key1 != key11 || key2 != key21 || key3 != key31)
		{
            AfxMessageBox("起始IP和终止IP不在一个网段内");
			return false;
		}

		int iEnd = atoi(key41);

		if (iStart > iEnd)
		{
			AfxMessageBox("起始IP地址大于终止IP地址");
			return false;
		}
	}
	return true;
}

void CPingDlg::DrawAnimation(CPaintDC& dc)
{
	dc.FillSolidRect(m_rcInvalidate, GetSysColor(COLOR_BTNFACE));
    if (!m_bDraw)
		return;
	CRect rcFrom, rcTo;
	m_wndPicFrom.GetWindowRect(rcFrom);
	m_wndPicTo.GetWindowRect(rcTo);
	ScreenToClient(&rcFrom);
	ScreenToClient(&rcTo);
	CPoint ptFrom = rcFrom.CenterPoint();
	CPoint ptTo = rcTo.CenterPoint();
	ptFrom.x = rcFrom.right;
	ptTo.x = rcTo.left;
	
	CRect rc(ptFrom.x, ptFrom.y -3, ptTo.x, ptTo.y + 3);
	dc.FillSolidRect(rc, RGB(0, 0, 255));
	CPoint ptCur = CountPos(ptFrom, ptTo);
	CRect rcCur(ptCur.x-5, ptCur.y-5, ptCur.x+5, ptCur.y+5);
    dc.FillSolidRect(rcCur, RGB( 255, 0, 0));
}

void CPingDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	DrawAnimation(dc);
}

CPoint CPingDlg::CountPos(CPoint ptFrom, CPoint ptTo)
{
	int len = ptTo.x - ptFrom.x;
    if (m_nPos <= 5 && !m_bIncrease)
	{
		m_nPos = 5;
		m_bIncrease = true;
	}
	else if (m_nPos >= len-5 && m_bIncrease)
	{
		m_nPos = len - 5;
		m_bIncrease = false;
	}
	else
	{
		if (m_bIncrease)
			m_nPos += 10;
		else
			m_nPos -= 10;
	}

	//dwTick = dwCur;
	return CPoint(ptFrom.x + m_nPos, ptFrom.y);
}

void CPingDlg::OnTimer(UINT nIDEvent) 
{
	InvalidateRect(m_rcInvalidate);
	CRootDlg::OnTimer(nIDEvent);
}

LRESULT CPingDlg::OnSetStatus(WPARAM wParam, LPARAM lParam)
{
    char* pMsg = (char*)lParam;
	int nCnt = m_lstInfo.GetItemCount();
	int i =  m_lstInfo.InsertItem(nCnt, pMsg, wParam);
	m_lstInfo.EnsureVisible(i, FALSE);
	delete [] pMsg;
	return 0;
}

LRESULT CPingDlg::OnPingEnd(WPARAM, LPARAM)
{
    KillTimer(1);
	m_bDraw = false;
	m_nPos = -1;
	m_bIncrease = true;
	InvalidateRect(m_rcInvalidate);
	GetDlgItem(IDC_BTN_START_PING)->EnableWindow(TRUE);
	KillTimer(1);
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CPingThread

IMPLEMENT_DYNCREATE(CPingThread, CWinThread)

CPingThread::CPingThread()
{
}

CPingThread::~CPingThread()
{
}

BOOL CPingThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CPingThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPingThread, CWinThread)
	//{{AFX_MSG_MAP(CPingThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPingThread message handlers

void CPingThread::StartPing(CPingDlg *pDlg)
{
    m_pDlg = pDlg;
	m_event.SetEvent();
}

int CPingThread::Run() 
{
	while(true)
	{
		int nRet = WaitForSingleObject(m_event.m_hObject, 2000);
		if (nRet == WAIT_TIMEOUT)
			continue;
		CPing ping;
		if (ping.StartPing(m_pDlg))
			break;
	}
	m_pDlg->SendMessage(WM_PING_END, 0, 0);
	return CWinThread::Run();
}

//////////////////////////////////////////////////////////////////////
// CPing Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPing::CPing()
{

}

CPing::~CPing()
{

}

bool CPing::StartPing(CPingDlg *pDlg)
{
    m_pDlg = pDlg;
	SOCKET s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (!pDlg->m_bCheckPing)
	{
		bool bRet = PingSingleMachine(s, pDlg->m_strStartIP);
		if (!bRet)
            PostErrorMsg(pDlg->m_strStartIP + "该主机不可到达");
		else
            PostSuccessMsg(1, pDlg->m_strStartIP + "该主机可以到达");
	}
	else
	{
		map<CString, bool> aHosts;
		GetHosts(pDlg->m_strStartIP, pDlg->m_strEndIP, aHosts);

		GetHostsMac(aHosts);

		map<CString, bool>::iterator it;
		for(it=aHosts.begin(); it!=aHosts.end(); it++)
		{
			bool bRet = PingSingleMachine(s, it->first);
			it->second = bRet;
			if (!bRet)
				PostErrorMsg(it->first + "该主机不可到达");
			else
				PostSuccessMsg(1, it->first + "该主机可以到达");
		}
		for(it=aHosts.begin(); it!=aHosts.end(); it++)
		{
			if (!it->second)
				PostErrorMsg(it->first + "该主机不可到达");
			else
				PostSuccessMsg(1, it->first + "该主机可以到达");
		}
	}
	closesocket(s);
	return true;
}

void CPing::PostErrorMsg(CString strError)
{
    m_pDlg->PostMessage(WM_MSG_STATUS, 0, (LPARAM)AllocBuffer(strError));
}

void CPing::PostSuccessMsg(int index, CString strError)
{
    m_pDlg->PostMessage(WM_MSG_STATUS, index, (LPARAM)AllocBuffer(strError));
}

void CPing::GetHosts(CString strStartIP, CString strEndIP, map<CString, bool>& aHosts)
{
    if (strStartIP == strEndIP)
	{
		aHosts.insert(make_pair(strStartIP, false));
		return;
	}
	int index = strStartIP.ReverseFind('.');
	CString strFore = strStartIP.Left(index+1);
	CString strFrom = strStartIP.Right(strStartIP.GetLength()-1-index);
    CString strTo = strEndIP.Right(strEndIP.GetLength()-1-index);
	int iFrom = atoi(strFrom);
	int iTo = atoi(strTo);
	for(int i=iFrom; i<=iTo; i++)
	{
		CString strKey;
		strKey.Format("%s%d", strFore, i);
        aHosts.insert(make_pair(strKey, false));
	}
}

bool CPing::PingSingleMachine(SOCKET s, CString strIP)
{
    hostent* pHost = gethostbyname(strIP);
	if (pHost == NULL)
	{
		PostSuccessMsg(0, strIP + ":主机找不到");
		return false;
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(strIP);
	addr.sin_port = 0;
	CString str;
	str.Format("Pinging %s [%s] with %d bytes of data:", strIP, strIP, 32);
	PostSuccessMsg(1, str);
	bool bSucceed = false;
	sockaddr_in saSrc;
	unsigned char cTTL;
	DWORD dwTimeSent;
	DWORD dwElapsed;

	for(int i=0; i<m_pDlg->m_iPingTimes; i++)
	{
		SendEchoRequest(s, addr);
		int nRet = WaitForEchoReply(s);
		if (nRet == SOCKET_ERROR)
		{
			PostErrorMsg("select failed");
			break;
		}
		else if (!nRet)
		{
			PostSuccessMsg(3, "Request Timed Out");
			continue;
		}
		dwTimeSent = RecvEchoReply(s, &saSrc, &cTTL);
		dwElapsed = GetTickCount() - dwTimeSent;
		str.Format("Reply[%d] from: %s: bytes=%d time=%ldms TTL=%d", 
				   i+1, inet_ntoa(saSrc.sin_addr), REQ_DATASIZE, dwElapsed, cTTL);
		PostSuccessMsg(2, str);
		bSucceed = true;
		Sleep(1000);
	}
    return bSucceed;
}

void CPing::SendEchoRequest(SOCKET s, sockaddr_in &addr)
{
    //static ECHOREQUEST echoReq;
	static nId = 1;
	static nSeq = 1;
	int nRet;
    char buf[1024] = { 0 };
	int nLen = 1024;
	char* pMsg = buf + sizeof(ICMPHeader);
	for (nRet = 0; nRet < REQ_DATASIZE; nRet++)
		pMsg[nRet] = ' '+nRet;
    _ICMPHeader header(ICMP_TYPE_ECHO_REQUEST, 0, nId++, nSeq++, pMsg, REQ_DATASIZE);
    memcpy(buf, &header, sizeof(_ICMPHeader));
	nRet = sendto(s, buf, sizeof(ICMPHeader) + REQ_DATASIZE, 0, (LPSOCKADDR)&addr, sizeof(SOCKADDR_IN));  
	if (nRet == SOCKET_ERROR) 
		PostErrorMsg("Sentto failed");
}

int CPing::WaitForEchoReply(SOCKET s)
{
    struct timeval Timeout;
	fd_set readfds;

	readfds.fd_count = 1;
	readfds.fd_array[0] = s;
	Timeout.tv_sec = 1;
    Timeout.tv_usec = 0;

	return(select(1, &readfds, NULL, NULL, &Timeout));
}

DWORD CPing::RecvEchoReply(SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL) 
{
	ECHOREPLY echoReply;
	int nRet;
	int nAddrLen = sizeof(struct sockaddr_in);
	nRet = recvfrom(s,(LPSTR)&echoReply,sizeof(ECHOREPLY),0,(LPSOCKADDR)lpsaFrom,&nAddrLen);
	if (nRet == SOCKET_ERROR) 
		PostErrorMsg("recvfrom()");
	*pTTL = echoReply.ipHdr.ipTTL;
	return(echoReply.echoRequest.TimeStamp);   
}

bool CPing::GetMachineMac(DWORD dwAddr, CString& strMac)
{
	UCHAR mac[6];
	memset(mac, 0xff, 6);
	ULONG ulen = 6;
	if (NO_ERROR != SendARP(dwAddr, 0, (ULONG*)mac, &ulen))
		return false;
	strMac.Format("%02X-%02X-%02X-%02X-%02X-%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	return true;
}

void CPing::GetHostsMac(map<CString, bool>& aHosts)
{
    map<CString, pair<CString, CString> > aMacs;
	map<CString, bool>::iterator it;
	CString strMac;
	CString strName;
	hostent* pHost;
	CString strIP;
	in_addr addr;
	for(it=aHosts.begin(); it!=aHosts.end(); it++)
	{
       if (GetMachineMac(inet_addr(it->first), strMac))
	   {
		   pHost = gethostbyname(it->first);
		   if (pHost != NULL)
		   {
			   strName = pHost->h_name;
			   memcpy(&addr.S_un.S_addr, pHost->h_addr_list[0], pHost->h_length);
			   strIP = inet_ntoa(addr);
			   aMacs.insert(make_pair(strName, make_pair(strIP, strMac)));
		   }
	   }
	}
	map<CString, pair<CString, CString> >::iterator it2;
	CMainApp* pApp = (CMainApp*)AfxGetApp();
	pApp->WriteProfileInt("Macs", "Count", aMacs.size());
	CString strKey;
    int i = 0;
	for(it2=aMacs.begin(); it2!=aMacs.end(); it2++)
	{
		strKey.Format("Host#%d", i);
		pApp->WriteProfileString("Macs", strKey, it2->first);
		strKey.Format("IP#%d", i);
		pApp->WriteProfileString("Macs", strKey, it2->second.first);
        strKey.Format("Mac#%d", i);
		pApp->WriteProfileString("Macs", strKey, it2->second.second);
		i ++;
	}
}