// GroupTalkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "initSock.h"
#include "GroupTalkDlg.h"
#include "GMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CinitSock init;

/////////////////////////////////////////////////////////////////////////////
// CGroupTalkDlg dialog
IMPLEMENT_DYNCREATE(CGroupTalkDlg, CRootDlg)

CGroupTalkDlg::CGroupTalkDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CGroupTalkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupTalkDlg)
	m_strSysMsg = _T("");
	m_iType = 0;
	//}}AFX_DATA_INIT
}

CGroupTalkDlg::~CGroupTalkDlg()
{
    delete m_pTalk;
}


void CGroupTalkDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupTalkDlg)
	DDX_Control(pDX, IDC_USERS, m_cmbUsers);
	DDX_Control(pDX, IDC_SENDMSG, m_edtSendMsg);
	DDX_Control(pDX, IDC_RECORD, m_lstRecord);
	DDX_Text(pDX, IDC_SYSMSG, m_strSysMsg);
	DDX_Radio(pDX, IDC_SELGROUP, m_iType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupTalkDlg, CRootDlg)
	//{{AFX_MSG_MAP(CGroupTalkDlg)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GROUPTALK, OnGroupTalk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupTalkDlg message handlers

BOOL CGroupTalkDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	m_pTalk = new CGroupTalk(this, inet_addr("234.5.6.7"));
	return TRUE;
}

void CGroupTalkDlg::OnClear() 
{
	m_lstRecord.ResetContent();
}

void CGroupTalkDlg::OnSend() 
{
	CString str;
	m_edtSendMsg.GetWindowText(str);
    str.TrimLeft();
	str.TrimRight();
	if (str == "")
		return;
    UpdateData();
	if (m_iType == 0)
		m_pTalk->SendText(str, inet_addr("234.5.6.7"));
	else
	{
		int iCurSel = m_cmbUsers.GetCurSel();
		if (iCurSel == -1)
		{
			//AfxMessageBox("请选择用户");
			AfxGMessageBox(this, "请选择用户",  "提示", MB_OK|MB_ICONINFORMATION, RGB(0, 0, 255));
			return;
		}
		DWORD dwAddr = m_cmbUsers.GetItemData(iCurSel);
		m_pTalk->SendText(str, dwAddr);
	}
	m_edtSendMsg.SetWindowText("");
}

LRESULT CGroupTalkDlg::OnGroupTalk(WPARAM wParam, LPARAM lParam)
{
	UpdateData();
	if (wParam == (WPARAM)-1)
	{
		m_strSysMsg = (LPCTSTR)lParam;
	}
	else
	{
		GT_HDR* pHeader = (GT_HDR*)lParam;
		switch(pHeader->gt_type)
		{
		case MT_JION:
			{
				m_cmbUsers.InsertString(-1, pHeader->szUser);
				m_cmbUsers.SetItemData(m_cmbUsers.GetCount()-1, pHeader->dwAddr);
				char szText[56];
				wsprintf(szText, " 用户：《%s》加入！", pHeader->szUser);
				m_strSysMsg = szText;
			}
			break;
		case MT_LEAVE:
			{
				// 显示给用户
			   char szText[56];
			   wsprintf(szText, " 用户：《%s》离开！", pHeader->szUser);
			   m_strSysMsg = szText;
			   int iIndex = m_cmbUsers.FindStringExact(-1, m_strSysMsg);
			   if (iIndex != -1)
				   m_cmbUsers.DeleteString(iIndex);
			}
			break;
		case MT_MESG:
			{
				char *psz = pHeader->data();
				psz[pHeader->nDataLength] = '\0';
				char szText[1024];
				wsprintf(szText, "【%s 说】", pHeader->szUser);
				strncat(szText, psz, 1024 - strlen(szText));
				m_lstRecord.InsertString(-1, szText);
			}
			break;
		}
	}
	UpdateData(FALSE);
    return 0;
}
