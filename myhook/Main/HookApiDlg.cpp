// HookApiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include <winsock2.h>
#include "HookApiDlg.h"
#include "HookApiCommon.h"
#include "ProcessThreadModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CHookApiDlg dialog
IMPLEMENT_DYNCREATE(CHookApiDlg, CRootDlg)

CHookApiDlg::CHookApiDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CHookApiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHookApiDlg)
	m_bCloseRecv = FALSE;
	m_bCloseSend = FALSE;
	m_bTopMost = FALSE;
	m_strDetail = _T("");
	//}}AFX_DATA_INIT
	m_bOpen = FALSE;	// 没有打开
	m_bPause = FALSE;	// 没有暂停
}


void CHookApiDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHookApiDlg)
	DDX_Control(pDX, IDC_LIST_DATA, m_lstData);
	DDX_Control(pDX, IDC_EDIT_SPECIFICDATA, m_edtDeatilData);
	DDX_Control(pDX, IDC_CHECK_TOPMOST, m_btnTopMost);
	DDX_Control(pDX, IDC_CHECK_CLOSESEND, m_btnCloseSend);
	DDX_Control(pDX, IDC_CHECK_CLOSERECV, m_btnCloseRecv);
	DDX_Control(pDX, IDC_BTN_TARGET, m_btnTarget);
	DDX_Control(pDX, IDC_BTN_PAUSE, m_btnPause);
	DDX_Control(pDX, IDC_BTN_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_BTN_CLEAR, m_btnClear);
	DDX_Check(pDX, IDC_CHECK_CLOSERECV, m_bCloseRecv);
	DDX_Check(pDX, IDC_CHECK_CLOSESEND, m_bCloseSend);
	DDX_Check(pDX, IDC_CHECK_TOPMOST, m_bTopMost);
	DDX_Text(pDX, IDC_EDIT_SPECIFICDATA, m_strDetail);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHookApiDlg, CRootDlg)
	//{{AFX_MSG_MAP(CHookApiDlg)
	ON_BN_CLICKED(IDC_BTN_PAUSE, OnBtnPause)
	ON_BN_CLICKED(IDC_CHECK_TOPMOST, OnCheckTopmost)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DATA, OnClickListData)
	ON_BN_CLICKED(IDC_BTN_TARGET, OnBtnTarget)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(HM_RECEIVE, OnReceive)
	ON_MESSAGE(HM_SEND, OnSend)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHookApiDlg message handlers

BOOL CHookApiDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	m_bar.Create(WS_CHILD|WS_VISIBLE|SBS_SIZEGRIP, CRect(0, 0, 0, 0), this, 101);
	m_bar.SetBkColor(RGB(255, 255, 255));
    int wid[] = {250, -1};
	m_bar.SetParts(2, wid);
	m_bar.SetText("挂钩API函数", 1, 0);

	m_lstData.InsertColumn(0, "编号", LVCFMT_LEFT, 38);
	m_lstData.InsertColumn(1, "类型", LVCFMT_LEFT, 80);
	m_lstData.InsertColumn(2, "数据", LVCFMT_LEFT, 150);
    m_lstData.InsertColumn(3, "程序", LVCFMT_LEFT, 100);
	UiControl();
    return TRUE;  
}

void CHookApiDlg::UiControl()
{
	if (m_bOpen)
	{
		m_btnPause.EnableWindow(TRUE);
        m_btnClose.EnableWindow(TRUE);
		if (!m_bPause)
			m_bar.SetText("正在拦截网络数据....", 0, 0);
		else
            m_bar.SetText("暂停拦截网络数据...", 0, 0);
	}
	else
	{
        m_btnPause.EnableWindow(FALSE);
        m_btnClose.EnableWindow(FALSE);
		m_bar.SetText("没有打开目标程序", 0, 0);
	}

	if(m_bPause)
		m_btnPause.SetWindowText("恢复");
	else
		m_btnPause.SetWindowText("暂停");
}

void CHookApiDlg::OnBtnPause() 
{
	UpdateData();
	m_bPause = !m_bPause;
	UiControl();
}

void CHookApiDlg::OnCheckTopmost() 
{
	UpdateData();

	if (m_bTopMost)
		GetParent()->SetWindowPos(CWnd::FromHandle(HWND_TOPMOST), 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOREDRAW);
	else
        GetParent()->SetWindowPos(CWnd::FromHandle(HWND_NOTOPMOST), 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOREDRAW);
}

LRESULT CHookApiDlg::OnReceive(WPARAM wParam, LPARAM lParam)
{
	CShareMemory  sm("IPPACK_RECEIVE", 0, FALSE);
	CMessageData *pData = (CMessageData*)sm.GetBuffer();
    
	if (m_bPause)
		return 0;
    UpdateData();
	if (m_bCloseRecv)
		return 0;
	CString strID;
    int iCount = m_lstData.GetItemCount();
	if (iCount == 30)
	{
		m_lstData.DeleteItem(0);
		iCount = m_lstData.GetItemCount();
		for(int i=0; i<iCount; i++)
		{
			strID.Format("%d", i+1);
			m_lstData.SetItemText(i, 0, strID);
		}
	}

	strID.Format("%d", iCount);
	m_lstData.InsertItem(iCount, strID);
	m_lstData.SetItemText(iCount, 1, "接收");
	m_lstData.SetItemText(iCount, 2, pData->data());
	m_lstData.SetItemText(iCount, 3, pData->szExeName);
	return 0;
}

LRESULT CHookApiDlg::OnSend(WPARAM wParam, LPARAM lParam)
{
	CShareMemory  sm("IPPACK_SEND", 0, FALSE);
	CMessageData *pData = (CMessageData*)sm.GetBuffer();
    
	if (m_bPause)
		return 0;
    UpdateData();
	if (m_bCloseSend)
		return 0;
	CString strID;
    int iCount = m_lstData.GetItemCount();
	if (iCount == 30)
	{
		m_lstData.DeleteItem(0);
		iCount = m_lstData.GetItemCount();
		for(int i=0; i<iCount; i++)
		{
			strID.Format("%d", i+1);
			m_lstData.SetItemText(i, 0, strID);
		}
	}

	strID.Format("%d", iCount);
	m_lstData.InsertItem(iCount, strID);
	m_lstData.SetItemText(iCount, 1, "发送");
	m_lstData.SetItemText(iCount, 2, pData->data());
	m_lstData.SetItemText(iCount, 3, pData->szExeName);
	return 0;
}


void CHookApiDlg::OnBtnClear() 
{
	UpdateData();
	m_lstData.DeleteAllItems();
	m_strDetail = "";
	UpdateData(FALSE);
}

void CHookApiDlg::OnClickListData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	NM_LISTVIEW* pView = (NM_LISTVIEW*)pNMHDR;
	int index = pView->iItem;
	if (index < 0)
	{
		*pResult = 0;
		return;
	}
	char szData[2048] = { 0 };
    m_lstData.GetItemText(index, 2, szData, 2048);
	char* pBuf = new char[strlen(szData)*3+1];
	memset(pBuf, 0, strlen(szData)*3+1);
	char* pTemp = pBuf;
	char* psz = szData;
	for(int i=0; i<strlen(szData); i++, psz++)
	{
		wsprintf(pTemp, "%02x ", (BYTE)(*psz));
		pTemp += 3;
	}
	*pTemp = '\0';
	m_strDetail = pBuf;
	delete[] pBuf;
	*pResult = 0;
	UpdateData(FALSE);
}

void CHookApiDlg::OnBtnTarget() 
{
	CEnumProcessDlg dlg(this);
	// 弹出选择进程对话框
	if(dlg.DoModal() == IDOK)
	{
		// 如果为其它进程安装了钩子，先卸载
		if(m_bOpen)	
		{
			//SetHook(FALSE);
			m_bOpen = false;
			m_bPause = false;
		}
		// 为用户选择进程的主线程安装钩子
		if(SetHook(TRUE, dlg.m_dwThreadID, m_hWnd))
		{
			m_bOpen = TRUE;
			m_bPause = FALSE;
		}
		else
			AfxMessageBox("安装钩子失败");
	}
	// 更新用户界面
	UiControl();
}
/////////////////////////////////////////////////////////////////////////////
// CEnumProcessDlg dialog


CEnumProcessDlg::CEnumProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEnumProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnumProcessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEnumProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnumProcessDlg)
	DDX_Control(pDX, IDC_PROLIST, m_lstProcess);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnumProcessDlg, CDialog)
	//{{AFX_MSG_MAP(CEnumProcessDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnumProcessDlg message handlers

BOOL CEnumProcessDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_lstProcess.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lstProcess.InsertColumn(0, "进程", LVCFMT_LEFT, 120);
	m_lstProcess.InsertColumn(1, "Pid", LVCFMT_LEFT, 70);
	// 更新进程列表
	UpdateProcess();
	return TRUE;
}

void CEnumProcessDlg::UpdateProcess()
{
    m_lstProcess.DeleteAllItems();
	CProcessThreadModule info;
	info.EnumProcess();
	for(int i=0; i<info.m_dwProcessNum; i++)
	{
        PROCESSENTRY32 entry = info.m_Process[i];
		m_lstProcess.InsertItem(i, entry.szExeFile);
		CString strProcessID;
		strProcessID.Format("%d", entry.th32ProcessID);
		m_lstProcess.SetItemText(i, 1, strProcessID);
		info.EnumThread(entry.th32ProcessID);
		for(int j=0; j<info.m_dwThreadNum; j++)
		{
			THREADENTRY32 ent = info.m_Thread[j];
			if (ent.th32OwnerProcessID == entry.th32ProcessID)
			{
				m_lstProcess.SetItemData(i, (DWORD)ent.th32ThreadID);
				break;
			}
		}
	}
}

void CEnumProcessDlg::OnOK() 
{
	int iCurSel = -1;
    for(int i=0; i<m_lstProcess.GetItemCount(); i++)
	{
		if ((LVIS_SELECTED & m_lstProcess.GetItemState(i, LVIS_SELECTED)) == LVIS_SELECTED)
		{
			iCurSel = i;
			break;
		}
	}
	if (iCurSel == -1)
	{
		AfxMessageBox("请选择程序");
		return;
	}
	char szName[200] = { 0 };
	m_lstProcess.GetItemText(iCurSel, 0, szName, 200);
	m_strExeName = szName;
	m_dwThreadID = m_lstProcess.GetItemData(iCurSel);
	CDialog::OnOK();
}

void CHookApiDlg::OnBtnClose() 
{
    if(m_bOpen)
	{
		SetHook(FALSE);
		m_bOpen = false;
		m_bPause = false;
		OnBtnClear();
	}
	UiControl();	
}



void CHookApiDlg::OnDestroy() 
{
	CRootDlg::OnDestroy();
	if (m_bOpen)
		SetHook(FALSE);	
}

bool CHookApiDlg::SetHook(BOOL bInstall, DWORD dwThreadId, HWND hWndCaller)
{
	CString strDll = "HookApi.dll";
	HMODULE hDll = GetModuleHandle(strDll);
	bool bFree = false;
	if (hDll == NULL)
	{
		hDll = LoadLibrary(strDll);
		bFree = true;
	}

	if (hDll == NULL)
		return false;

	typedef BOOL (WINAPI* PFSetHook)(BOOL bInstall, DWORD dwThreadID, HWND hWndCaller);
	PFSetHook pSetHook = (PFSetHook)GetProcAddress(hDll, "SetHook");
	if (pSetHook == NULL)
	{
		if (bFree)
			FreeLibrary(hDll);
		return false;
	}
	BOOL b = pSetHook(bInstall, dwThreadId, hWndCaller);

	if (!bInstall)
         FreeLibrary(hDll);

	return b;
}
