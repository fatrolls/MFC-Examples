// IoCompletePortTalkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "IoCompletePortTalkDlg.h"
#include <winsock2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIoCompletePortTalkDlg dialog

IMPLEMENT_DYNCREATE(CIoCompletePortTalkDlg, CRootDlg)

CIoCompletePortTalkDlg::CIoCompletePortTalkDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CIoCompletePortTalkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIoCompletePortTalkDlg)
	m_strSendMsg = _T("");
	//}}AFX_DATA_INIT
}


void CIoCompletePortTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIoCompletePortTalkDlg)
	DDX_Control(pDX, IDC_LIST_ONLINE_USER, m_lstUsers);
	DDX_Control(pDX, IDC_LIST_RECORD, m_lstRecord);
	DDX_Control(pDX, IDC_EDIT_SEND_MSG, m_edtSendMsg);
	DDX_Text(pDX, IDC_EDIT_SEND_MSG, m_strSendMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIoCompletePortTalkDlg, CRootDlg)
	//{{AFX_MSG_MAP(CIoCompletePortTalkDlg)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIoCompletePortTalkDlg message handlers

BOOL CIoCompletePortTalkDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	m_sSocket = new CIoCompletePortSocket(this);
    return TRUE; 
}

void CIoCompletePortTalkDlg::OnBtnSend() 
{
    UpdateData();
	m_strSendMsg.TrimLeft();
	m_strSendMsg.TrimRight();
	if (m_strSendMsg == "")
		return;
	int iCurSel = m_lstUsers.GetCurSel();
	if (iCurSel == -1)
		return;
	IpAddress* pAddr = (IpAddress*)m_lstUsers.GetItemData(iCurSel);
	m_sSocket->SendMsg(m_strSendMsg, pAddr);
	m_strSendMsg = "";
	UpdateData(FALSE);
}

void CIoCompletePortTalkDlg::OnBtnClear() 
{
	m_lstRecord.ResetContent();
}
