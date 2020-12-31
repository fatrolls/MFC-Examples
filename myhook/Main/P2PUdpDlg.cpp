// P2PUdpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "P2pUDPUtility.h"
#include "P2PUdpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CP2PUdpServerDlg dialog
IMPLEMENT_DYNCREATE(CP2PUdpServerDlg, CRootDlg)
IMPLEMENT_DYNCREATE(CP2PUdpClientDlg, CRootDlg)

CP2PUdpServerDlg::CP2PUdpServerDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CP2PUdpServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CP2PUdpServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CP2PUdpServerDlg::~CP2PUdpServerDlg()
{
    delete m_pServer;
}

void CP2PUdpServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CP2PUdpServerDlg)
	DDX_Control(pDX, IDC_LIST_USER, m_lstUser);
	DDX_Control(pDX, IDC_LIST_INFO, m_lstInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CP2PUdpServerDlg, CRootDlg)
	//{{AFX_MSG_MAP(CP2PUdpServerDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CP2PUdpServerDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CP2PUdpClientDlg dialog


CP2PUdpClientDlg::CP2PUdpClientDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CP2PUdpClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CP2PUdpClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CP2PUdpClientDlg::~CP2PUdpClientDlg()
{
    delete m_pClient;
}

void CP2PUdpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CP2PUdpClientDlg)
	DDX_Control(pDX, IDC_LIST_USER, m_lstUser);
	DDX_Control(pDX, IDC_LIST_INFO, m_lstInfo);
	DDX_Control(pDX, IDC_LIST_CONTENT, m_lstContent);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_edtContent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CP2PUdpClientDlg, CRootDlg)
	//{{AFX_MSG_MAP(CP2PUdpClientDlg)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CP2PUdpClientDlg message handlers

BOOL CP2PUdpServerDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
    m_pServer = new CMyP2pUDPServer(this);
	return TRUE; 
}

BOOL CP2PUdpClientDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	m_pClient = new CMyP2pUDPClient(this);	
	return TRUE;  
}

void CP2PUdpServerDlg::SetListBoxPos(CListBox &lstbox)
{
   int iUp, iDown;
   lstbox.GetScrollRange(SB_VERT, &iDown, &iUp);
   lstbox.SetScrollPos(SB_VERT, iUp);
}

void CP2PUdpClientDlg::SetListBoxPos(CListBox &lstbox)
{
   int iUp, iDown;
   lstbox.GetScrollRange(SB_VERT, &iDown, &iUp);
   lstbox.SetScrollPos(SB_VERT, iUp);
}

void CP2PUdpClientDlg::OnBtnSend() 
{
	CString strText;
	m_edtContent.GetWindowText(strText);
	strText.TrimLeft();
	strText.TrimRight();
	if (strText.IsEmpty())
		return;
	int index = m_lstUser.GetCurSel();
	if (index == LB_ERR)
		return;
	HostInfo* pHost = (HostInfo*)m_lstUser.GetItemData(index);
    m_pClient->SendContent(pHost, strText);
}
