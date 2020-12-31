// LSPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "LSPDlg.h"
#include "LSPHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLSPDlg dialog
IMPLEMENT_DYNCREATE(CLSPDlg, CRootDlg)

CLSPDlg::CLSPDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CLSPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLSPDlg)
	m_strLSPDllPath = _T("");
	m_strLSPName = _T("");
	m_strInfo = _T("");
	//}}AFX_DATA_INIT
	m_hProtocolDll = NULL;
	m_bNeedFree = false;
}


void CLSPDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLSPDlg)
	DDX_Control(pDX, IDC_EDITINFO, m_edtInfo);
	DDX_Control(pDX, IDC_BTN_LSP, m_btnLsp);
	DDX_Control(pDX, IDC_LISTINFO, m_lstInfo);
	DDX_Control(pDX, IDC_STATIC_PLACE, m_wndPlace);
	DDX_Control(pDX, IDC_EDIT_LSP_DLL_PATH, m_edtLSPDllPath);
	DDX_Text(pDX, IDC_EDIT_LSP_DLL_PATH, m_strLSPDllPath);
	DDX_Text(pDX, IDC_EDIT_LSP_NAME, m_strLSPName);
	DDX_Text(pDX, IDC_EDITINFO, m_strInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLSPDlg, CRootDlg)
	//{{AFX_MSG_MAP(CLSPDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_LSP, OnBtnLsp)
	ON_LBN_SELCHANGE(IDC_LISTINFO, OnSelchangeListinfo)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WH_SEND, OnSend)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LISTINFO, OnDeleteItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLSPDlg message handlers

BOOL CLSPDlg::OnInitDialog() 
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
	m_edtLSPDllPath.EnableFileBrowseButton("dll", "*.dll|*.dll||");
	menu.LoadMenu (IDR_MENU5);
	m_btnLsp.m_hMenu = menu.GetSubMenu (0)->GetSafeHmenu ();
	m_btnLsp.SizeToContent ();
	m_lstInfo.ShowWindow(SW_HIDE);
	return TRUE;  
}

void CLSPDlg::OnDestroy() 
{
	CRootDlg::OnDestroy();
	m_wndPropList.DestroyWindow();	
	if (m_hProtocolDll != NULL && m_bNeedFree)
		FreeLibrary(m_hProtocolDll);
}

CBCGPProp* CLSPDlg::AddGroupProp(CString strName, CBCGPProp* pParent)
{
	CBCGPProp* pProp = new CBCGPProp(_T(strName));
	if (pParent == NULL)
		m_wndPropList.AddProperty(pProp);
	else
		pParent->AddSubItem(pProp);
	return pProp;
}

void CLSPDlg::AddChildProp(CString strName, CString strValue, CBCGPProp* pParent)
{
    CBCGPProp* pProp = new CBCGPProp(_T(strName), (_variant_t)(_bstr_t)strValue, "");
	if (pParent == NULL)
		m_wndPropList.AddProperty(pProp);
	else
		pParent->AddSubItem(pProp);
}

void CLSPDlg::OnBtnInstallLsp() 
{
	UpdateData();
	m_strLSPDllPath.TrimLeft();
	m_strLSPDllPath.TrimRight();
	if (m_strLSPDllPath == "")
	{
		AfxMessageBox("请选择要卸载的LSP Dll文件");
		return;
	}
	m_strLSPName.TrimLeft();
	m_strLSPName.TrimRight();
	if (m_strLSPName == "")
	{
		AfxMessageBox("请输入LSP协议名称");
		return;
	}
	CLSPHelper helper;
	PWCHAR wszLSPName = new WCHAR[m_strLSPName.GetLength()+1];
	ZeroMemory(wszLSPName, (m_strLSPName.GetLength()+1)*2);
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, m_strLSPName.GetBuffer(m_strLSPName.GetLength()), 
		                m_strLSPName.GetLength(), wszLSPName, m_strLSPName.GetLength()+1); 
	PWCHAR wszLSPPath = new WCHAR[m_strLSPDllPath.GetLength()+1];
	ZeroMemory(wszLSPPath, (m_strLSPDllPath.GetLength()+1)*2);
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, m_strLSPDllPath.GetBuffer(m_strLSPDllPath.GetLength()), 
		                m_strLSPDllPath.GetLength(), wszLSPPath, m_strLSPDllPath.GetLength()+1);
	if (helper.InstallProvider(wszLSPName, wszLSPPath))
	{
		OnBtnEnumProtocols();
		AfxMessageBox("安装LSP成功");
	}
	else
        AfxMessageBox("安装LSP失败");
	m_strLSPDllPath.ReleaseBuffer();
	m_strLSPName.ReleaseBuffer();
	delete [] wszLSPName;
    delete [] wszLSPPath;
}

void CLSPDlg::OnBtnRemoveLsp() 
{
/*	CLSPHelper helper;
    helper.RemoveProvider(1067);
	helper.RemoveProvider(1046);*/
	
	
	UpdateData();
	m_strLSPDllPath.TrimLeft();
	m_strLSPDllPath.TrimRight();
	if (m_strLSPDllPath == "")
	{
		AfxMessageBox("请选择要卸载的LSP Dll文件");
		return;
	}
	CLSPHelper helper;
	PWCHAR wszLSPPath = new WCHAR[m_strLSPDllPath.GetLength()+1];
	ZeroMemory(wszLSPPath, (m_strLSPDllPath.GetLength()+1)*2);
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, m_strLSPDllPath.GetBuffer(m_strLSPDllPath.GetLength()), 
		                m_strLSPDllPath.GetLength(), wszLSPPath, m_strLSPDllPath.GetLength());
	if (helper.RemoveProvider(wszLSPPath))
	{
		OnBtnEnumProtocols();
		AfxMessageBox("卸载LSP成功");
	}
	else
        AfxMessageBox("卸载LSP失败");
	m_strLSPDllPath.ReleaseBuffer();
	delete [] wszLSPPath;
}

void CLSPDlg::OnBtnEnumProtocols() 
{
	CLSPHelper helper;
	m_wndPropList.RemoveAll();
	if (!helper.GetProvider(NULL))
		return;
	for(int i=0; i<helper.m_iProtocolNum; i++)
	{
		LPWSAPROTOCOL_INFOW pInfo = helper.m_pProtocolInfo + i;
		CString strKey, strValue;
		strKey.Format("第%d个协议", i+1);
		CBCGPProp* pGroup = AddGroupProp(strKey, NULL);
		strKey = "名称";
		strValue = pInfo->szProtocol;
        AddChildProp(strKey, strValue, pGroup);
		unsigned char* pGuid;
		UuidToString(&pInfo->ProviderId, &pGuid);
		strKey = "GUID";
		strValue = pGuid;
		AddChildProp(strKey, strValue, pGroup);
		strKey = "目录入口ID";
		strValue.Format("%d", pInfo->dwCatalogEntryId);
		AddChildProp(strKey, strValue, pGroup);
		if(pInfo->ProtocolChain.ChainLen > 1)
		{
			CBCGPProp* pChildGroup = AddGroupProp("协议链", pGroup);
			for(int j=0; j<pInfo->ProtocolChain.ChainLen; j++)
			{
				strKey.Format("%d", j);
				strValue.Format("%d", pInfo->ProtocolChain.ChainEntries[j]);
				AddChildProp(strKey, strValue, pChildGroup);
			}
		}
		strKey = "协议类型";
	    switch(pInfo->iProtocol)
		{
		case IPPROTO_IP:
			strValue = "IP";
			break;
		case IPPROTO_TCP:
			strValue = "TCP";
			break;
		case IPPROTO_UDP:
			strValue = "UDP";
			break;
		case IPPROTO_RAW:
			strValue = "RAW";
			break;
		case IPPROTO_ICMP:
			strValue = "ICMP";
			break;
		case IPPROTO_IGMP:
			strValue = "IGMP";
			break;
		default:
			strValue = "其他 ";
			break;
		}
		AddChildProp(strKey, strValue, pGroup);	
		strKey = "Dll路径";
		WCHAR szPath[MAX_PATH] = {0};
		int len = MAX_PATH;
		ZeroMemory(szPath, MAX_PATH);
		if (SOCKET_ERROR == WSCGetProviderPath(&pInfo->ProviderId, szPath, &len, NULL))
			continue;
		len = wcslen(szPath);
		WCHAR szFullPath[MAX_PATH];
		ZeroMemory(szFullPath, MAX_PATH);
		ExpandEnvironmentStringsW(szPath, szFullPath, len+1);
		strValue = szFullPath;
		AddChildProp(strKey, strValue, pGroup);
	}
	m_wndPropList.ExpandAll();
}


void CLSPDlg::OnBtnLsp() 
{
	UpdateData();

	switch (m_btnLsp.m_nMenuResult)
	{
	case IDM_ENUM_PROTOCOL:
		m_wndPropList.ShowWindow(SW_SHOW);
		m_lstInfo.ShowWindow(SW_HIDE);
		m_edtInfo.ShowWindow(SW_HIDE);
		OnBtnEnumProtocols();
		break;
	case IDM_INSTALL_LSP:
		m_wndPropList.ShowWindow(SW_SHOW);
		m_lstInfo.ShowWindow(SW_HIDE);
		m_edtInfo.ShowWindow(SW_HIDE);
		OnBtnInstallLsp();
		break;
	case IDM_REMOVE_LSP:
		m_wndPropList.ShowWindow(SW_SHOW);
		m_lstInfo.ShowWindow(SW_HIDE);
		m_edtInfo.ShowWindow(SW_HIDE);
		OnBtnRemoveLsp();
		break;
	case IDM_HOOK_SOCKET:
		m_wndPropList.ShowWindow(SW_HIDE);
		m_lstInfo.ShowWindow(SW_SHOW);
		m_edtInfo.ShowWindow(SW_SHOW);
		OnHookSocket();
		break;
	case IDM_UNHOOK_SOCKET:
		m_wndPropList.ShowWindow(SW_HIDE);
		m_lstInfo.ShowWindow(SW_SHOW);
		m_edtInfo.ShowWindow(SW_SHOW);
		OnUnhookSocket();
		break;
	default:
		return;
	}
}

void CLSPDlg::OnHookSocket()
{
	UpdateData();
    if (m_hProtocolDll != NULL && m_bNeedFree)
		FreeLibrary(m_hProtocolDll);
	m_hProtocolDll = NULL;
	m_bNeedFree = false;
	m_hProtocolDll = GetModuleHandle(m_strLSPDllPath);
	if (m_hProtocolDll == NULL)
	{
		m_hProtocolDll = LoadLibrary(m_strLSPDllPath);
		if (m_hProtocolDll == NULL)
		{
			AfxMessageBox("装载提供者dll失败");
			return;
		}
		m_bNeedFree = true;
	}
	typedef void (WINAPI* PSetNotifyWindow)(HWND);
    PSetNotifyWindow pFn = (PSetNotifyWindow)GetProcAddress(m_hProtocolDll, "SetNotifyWIndow");
	if (pFn == NULL)
	{
        AfxMessageBox("装载提供者dll失败");
		if (m_hProtocolDll != NULL && m_bNeedFree)
		    FreeLibrary(m_hProtocolDll);
	    m_hProtocolDll = NULL;
		m_bNeedFree = false;
		return;
	}
	pFn(m_hWnd);
}

void CLSPDlg::OnUnhookSocket()
{
	if (m_hProtocolDll == NULL)
		return;
    typedef void (WINAPI* PSetNotifyWindow)(HWND);
    PSetNotifyWindow pFn = (PSetNotifyWindow)GetProcAddress(m_hProtocolDll, "SetNotifyWIndow");
	if (pFn == NULL)
	   return;
	pFn(NULL);
}

LRESULT CLSPDlg::OnSend(WPARAM wParam, LPARAM lParam)
{
    LSPMessage* buf = (LSPMessage*)wParam;
	LSPMessage* pData = new LSPMessage(buf);
	CString strKey;
	if (buf->wszMessage[0] != L'\0')
		strKey = buf->wszMessage;
	else if (buf->wszFunction[0] != L'\0')
		strKey = buf->wszFunction;
	m_lstInfo.InsertString(-1, strKey);
	m_lstInfo.SetItemData(m_lstInfo.GetCount()-1, (DWORD)pData);
	return 0;
}

void CLSPDlg::OnSelchangeListinfo() 
{
	LSPMessage* pMsg;
	int iCurSel = m_lstInfo.GetCurSel();
	if (iCurSel != -1)
        pMsg = (LSPMessage*)m_lstInfo.GetItemData(iCurSel);
	else
		return;
	m_strInfo = "应用程序: ";
	m_strInfo += pMsg->wszExeName;
	m_strInfo += "\r\n";
	m_strInfo += "消息: ";
	m_strInfo += pMsg->wszMessage;
	m_strInfo += "\r\n";
	m_strInfo += "函数: ";
	m_strInfo += pMsg->wszFunction;
	m_strInfo += "\r\n";
	m_strInfo += "参数 : \r\n";
	for(int i=0; i<pMsg->m_iParamCount; i++)
	{
		PWCHAR p = pMsg->GetParamPointer(i);
		m_strInfo += p;
		m_strInfo += "\r\n";
	}
	UpdateData(FALSE);
}

void CLSPDlg::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	LSPMessage* pByte = (LSPMessage*)pNMListView->lParam;
    delete pByte;
	*pResult = 0;
}
