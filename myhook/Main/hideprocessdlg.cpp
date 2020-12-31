// HideProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "main.h"
#include "HideProcessDlg.h"
#include "DriverTool.h"
#include <winioctl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHideProcessDlg dialog
IMPLEMENT_DYNCREATE(CHideProcessDlg, CRootDlg)

CHideProcessDlg::CHideProcessDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CHideProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHideProcessDlg)
	m_strDriverPath = _T("");
	//}}AFX_DATA_INIT
	m_hDriver = INVALID_HANDLE_VALUE;
}


void CHideProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHideProcessDlg)
	DDX_Control(pDX, IDC_EDIT_DRIVER_PATH, m_edtDriverPath);
	DDX_Control(pDX, IDC_BUTTON1, m_btnTool);
	DDX_Text(pDX, IDC_EDIT_DRIVER_PATH, m_strDriverPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHideProcessDlg, CRootDlg)
	//{{AFX_MSG_MAP(CHideProcessDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHideProcessDlg message handlers

BOOL CHideProcessDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	
	menu.LoadMenu (IDR_MENU_HIDE_PROCESS);
	m_btnTool.m_hMenu = menu.GetSubMenu (0)->GetSafeHmenu ();
	m_btnTool.SizeToContent ();

	m_edtDriverPath.EnableFileBrowseButton("sys", "驱动程序(*.sys)|*.sys||");
	return TRUE;
}

void CHideProcessDlg::OnButton1() 
{
	UpdateData();

	switch (m_btnTool.m_nMenuResult)
	{
	case IDM_INSTALL_DRIVER:
		InstallDriver();
		break;
	case IDM_UNINSTALL_DRIVER:
		UninstallDriver();
		break;
	case IDM_START_DRIVER:
		StartDriver();
		break;
	case IDM_STOP_DRIVER:
		StopDriver();
		break;
	case IDM_OPEN_CONTROL_DEVICE:
		OpenControlDevice();
		break;
	case IDM_HIDE_PROCESS:
		HideProcess();
		break;	
	}
}

void CHideProcessDlg::OpenControlDevice()
{
    if (m_strDriverPath == "")
		return;
    CDriverTool tool;
	m_hDriver = tool.OpenControlDevice(m_strDriverPath);
	if (m_hDriver == INVALID_HANDLE_VALUE)
		AfxMessageBox("打开驱动失败");
	else
		AfxMessageBox("打开驱动成功");
}

void CHideProcessDlg::InstallDriver()
{
	if (m_strDriverPath == "")
		return;
    CDriverTool tool;
	CString strLinkName;
	int index = m_strDriverPath.ReverseFind('\\');
	strLinkName = m_strDriverPath.Right(m_strDriverPath.GetLength()-1-index);
	index = strLinkName.Find(".");
	strLinkName = strLinkName.Left(index);
	if (tool.InstallDriver(m_strDriverPath, strLinkName, false))
		AfxMessageBox("驱动安装成功");
	else
		AfxMessageBox("驱动安装失败");
}

void CHideProcessDlg::UninstallDriver()
{
	if (m_strDriverPath == "")
		return;
    CDriverTool tool;
	if (tool.UnInstallDriver(m_strDriverPath))
		AfxMessageBox("驱动卸载成功");
	else
		AfxMessageBox("驱动卸载失败");
}

void CHideProcessDlg::StartDriver()
{
	if (m_strDriverPath == "")
		return;
	CDriverTool tool;
	if (tool.StartDriver(m_strDriverPath))
		AfxMessageBox("启动驱动成功");
	else
		AfxMessageBox("启动驱动失败");
}

void CHideProcessDlg::StopDriver()
{
	if (m_strDriverPath == "")
		return;
	CDriverTool tool;
	if (tool.StopDriver(m_strDriverPath))
		AfxMessageBox("停止驱动成功");
	else
		AfxMessageBox("停止驱动失败");
}

void CHideProcessDlg::HideProcess()
{
   CHideProcessDetailDlg dlg;
   dlg.m_hDriver = m_hDriver;
   dlg.DoModal();
}
/////////////////////////////////////////////////////////////////////////////
// CHideProcessDetailDlg dialog
#define FILE_DEVICE_HIDEPROCESS      0x8000
#define IOCTL_HIDEPROCESS_CLEAR_LIST      CTL_CODE(FILE_DEVICE_HIDEPROCESS, 0, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HIDEPROCESS_ADD_PROCESS    CTL_CODE(FILE_DEVICE_HIDEPROCESS, 1 , METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HIDEPROCESS_DELETE_PROCESS    CTL_CODE(FILE_DEVICE_HIDEPROCESS, 2 , METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HIDEPROCESS_ADD_PROCESS_LIST    CTL_CODE(FILE_DEVICE_HIDEPROCESS, 3 , METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HIDEPROCESS_DELETE_PROCESS_LIST    CTL_CODE(FILE_DEVICE_HIDEPROCESS, 4, METHOD_BUFFERED, FILE_ANY_ACCESS)

CHideProcessDetailDlg::CHideProcessDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHideProcessDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHideProcessDetailDlg)
	m_strPath1 = _T("");
	m_strPath2 = _T("");
	m_strPath3 = _T("");
	m_strPath4 = _T("");
	m_strPath5 = _T("");
	m_strPath6 = _T("");
	//}}AFX_DATA_INIT
	m_hDriver = INVALID_HANDLE_VALUE;
}


void CHideProcessDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHideProcessDetailDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strPath1);
	DDX_Text(pDX, IDC_EDIT2, m_strPath2);
	DDX_Text(pDX, IDC_EDIT3, m_strPath3);
	DDX_Text(pDX, IDC_EDIT4, m_strPath4);
	DDX_Text(pDX, IDC_EDIT5, m_strPath5);
	DDX_Text(pDX, IDC_EDIT6, m_strPath6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHideProcessDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CHideProcessDetailDlg)
	ON_BN_CLICKED(IDC_BTN_HIDE, OnBtnHide)
	ON_BN_CLICKED(IDC_BTN_SHOW, OnBtnShow)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHideProcessDetailDlg message handlers

void CHideProcessDetailDlg::OnBtnHide() 
{
	CStringArray aNames;
	if (!GetProcessName(aNames))
		return;
	int nSize = aNames.GetSize();
	char buf[4096] = { 0 };
    CDriverTool tool;
	PWCHAR wszLSPName;
	int nTotalSize = 0;
	int nLen;
	CString strName;

	if (nSize == 1)
	{
		USHORT* p = (USHORT*)buf;
		strName = aNames[0];
		*p = strName.GetLength();
		p += 1;
		nLen = strName.GetLength();
		wszLSPName = new WCHAR[nLen];
	    ZeroMemory(wszLSPName, nLen*2);
	    MultiByteToWideChar(CP_ACP, MB_COMPOSITE, strName.GetBuffer(nLen), nLen, wszLSPName, nLen);
		strName.ReleaseBuffer();
		memcpy(p, wszLSPName, nLen*2);
		delete [] wszLSPName;
		nTotalSize = sizeof(USHORT) * (nLen+1);
		tool.IoControl(m_hDriver, IOCTL_HIDEPROCESS_ADD_PROCESS, buf, nTotalSize, NULL, 0);
	}
	else
	{
        USHORT* p = (USHORT*)buf;
		*p = nSize;
		p += 1;

		nTotalSize = 1;

		for(int i=0; i<nSize; i++)
		{
            strName = aNames[i];
			nLen = strName.GetLength();
			*p = nLen;
			p += 1;
			wszLSPName = new WCHAR[nLen];
			ZeroMemory(wszLSPName, nLen*2);
			MultiByteToWideChar(CP_ACP, MB_COMPOSITE, strName.GetBuffer(nLen), nLen, wszLSPName, nLen);
			memcpy(p, wszLSPName, nLen*2);
			strName.ReleaseBuffer();
			delete [] wszLSPName;
			nTotalSize += nLen + 1;
			p += (nLen);
		}
		tool.IoControl(m_hDriver, IOCTL_HIDEPROCESS_ADD_PROCESS_LIST, buf, nTotalSize*sizeof(USHORT), NULL, 0);
	}
}

void CHideProcessDetailDlg::OnBtnShow() 
{
	CStringArray aNames;
	if (!GetProcessName(aNames))
		return;
	int nSize = aNames.GetSize();
	char buf[4096] = { 0 };
    CDriverTool tool;
	PWCHAR wszLSPName;
	int nTotalSize = 0;
	int nLen;
	CString strName;

	if (nSize == 1)
	{
		USHORT* p = (USHORT*)buf;
		strName = aNames[0];
		*p = strName.GetLength();
		p += 1;
		nLen = strName.GetLength();
		wszLSPName = new WCHAR[nLen];
	    ZeroMemory(wszLSPName, nLen*2);
	    MultiByteToWideChar(CP_ACP, MB_COMPOSITE, strName.GetBuffer(nLen), nLen, wszLSPName, nLen);
		strName.ReleaseBuffer();
		memcpy(p, wszLSPName, nLen*2);
		delete [] wszLSPName;
		nTotalSize = sizeof(USHORT) * (nLen+1);
		tool.IoControl(m_hDriver, IOCTL_HIDEPROCESS_DELETE_PROCESS, buf, nTotalSize, NULL, 0);
	}
	else
	{
        USHORT* p = (USHORT*)buf;
		*p = nSize;
		p += 1;

		nTotalSize = 1;

		for(int i=0; i<nSize; i++)
		{
            strName = aNames[i];
			nLen = strName.GetLength();
			*p = nLen;
			p += 1;
			wszLSPName = new WCHAR[nLen];
			ZeroMemory(wszLSPName, nLen*2);
			MultiByteToWideChar(CP_ACP, MB_COMPOSITE, strName.GetBuffer(nLen), nLen, wszLSPName, nLen);
			memcpy(p, wszLSPName, nLen*2);
			strName.ReleaseBuffer();
			delete [] wszLSPName;
			nTotalSize += nLen + 1;
			p += (nLen);
		}
		tool.IoControl(m_hDriver, IOCTL_HIDEPROCESS_DELETE_PROCESS_LIST, buf, nTotalSize*sizeof(USHORT), NULL, 0);
	}
}

void CHideProcessDetailDlg::OnBtnClear() 
{
	if (m_hDriver == INVALID_HANDLE_VALUE)
		return;
	m_strPath1 = "";
	m_strPath2 = "";
	m_strPath3 = "";
	m_strPath4 = "";
	m_strPath5 = "";
	m_strPath6 = "";
	UpdateData(FALSE);
	CDriverTool tool;
	tool.IoControl(m_hDriver, IOCTL_HIDEPROCESS_CLEAR_LIST, NULL, 0, NULL, 0);
}

bool CHideProcessDetailDlg::GetProcessName(CStringArray& aNames)
{
	UpdateData();
    aNames.RemoveAll();
    m_strPath1.TrimLeft();
	m_strPath1.TrimRight();
	if (m_strPath1 != "")
		aNames.Add(m_strPath1);
    m_strPath2.TrimLeft();
	m_strPath2.TrimRight();
	if (m_strPath2 != "")
		aNames.Add(m_strPath2);
	m_strPath3.TrimLeft();
	m_strPath3.TrimRight();
	if (m_strPath3 != "")
		aNames.Add(m_strPath3);
	m_strPath4.TrimLeft();
	m_strPath4.TrimRight();
	if (m_strPath4 != "")
		aNames.Add(m_strPath4);
    m_strPath5.TrimLeft();
	m_strPath5.TrimRight();
	if (m_strPath5 != "")
		aNames.Add(m_strPath5);
	m_strPath6.TrimLeft();
	m_strPath6.TrimRight();
	if (m_strPath6 != "")
		aNames.Add(m_strPath6);
	return (aNames.GetSize() > 0);
}
