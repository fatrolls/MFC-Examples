// StartServiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "StartServiceDlg.h"
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

PROCESS_INFORMATION* CStartServiceDlg::m_pProcInfo = NULL;
int CStartServiceDlg::m_nProcCount;
SERVICE_STATUS          CStartServiceDlg::serviceStatus; 
SERVICE_STATUS_HANDLE   CStartServiceDlg::hServiceStatusHandle; 
char CStartServiceDlg::m_pServiceName[500];

/////////////////////////////////////////////////////////////////////////////
// CStartServiceDlg dialog

IMPLEMENT_DYNCREATE(CStartServiceDlg, CRootDlg)

CStartServiceDlg::CStartServiceDlg(CWnd* pParent /*=NULL*/)
	: CRootDlg(CStartServiceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStartServiceDlg)
	m_uPauseStart = 0;
	m_uPauseEnd = 0;
	m_strExe = _T("");
	m_strCmdLine = _T("");
	m_uInterGap = 0;
	m_strServiceName = _T("");
	m_iLast = -1;
	//}}AFX_DATA_INIT
	m_pProcInfo = NULL;
}

CStartServiceDlg::~CStartServiceDlg()
{
   if (m_pProcInfo != NULL)
	   delete [] m_pProcInfo;
}


void CStartServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartServiceDlg)
	DDX_Control(pDX, IDC_EDIT_EXE, m_edtExe);
	DDX_Control(pDX, IDC_COMBO_USERINTERFACE, m_cmbInterface);
	DDX_Control(pDX, IDC_LIST_EXE, m_ListEXE);
	DDX_Control(pDX, IDC_BTN_SERVICE_MENU, m_btnServiceControl);
	DDX_Text(pDX, IDC_EDIT_PAUSESTART, m_uPauseStart);
	DDV_MinMaxUInt(pDX, m_uPauseStart, 0, 60);
	DDX_Text(pDX, IDC_EDIT_PAUSE_END, m_uPauseEnd);
	DDV_MinMaxUInt(pDX, m_uPauseEnd, 0, 60);
	DDX_Text(pDX, IDC_EDIT_EXE, m_strExe);
	DDX_Text(pDX, IDC_EDIT_COMMANDLINE, m_strCmdLine);
	DDX_Text(pDX, IDC_EDIT_INTERGAP, m_uInterGap);
	DDV_MinMaxUInt(pDX, m_uInterGap, 0, 3600);
	DDX_Text(pDX, IDC_EDIT_SERVICENAME, m_strServiceName);
	DDX_LBIndex(pDX, IDC_LIST_EXE, m_iLast);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartServiceDlg, CRootDlg)
	//{{AFX_MSG_MAP(CStartServiceDlg)
	ON_LBN_SELCHANGE(IDC_LIST_EXE, OnSelchangeListExe)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_CREATE_SETTING_FILE, OnBtnCreateSettingFile)
	ON_BN_CLICKED(IDC_BTN_SERVICE_MENU, OnBtnServiceMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartServiceDlg message handlers

BOOL CStartServiceDlg::OnInitDialog() 
{
	CRootDlg::OnInitDialog();
	
	menu.LoadMenu (IDR_MENU1);
	m_btnServiceControl.m_hMenu = menu.GetSubMenu (0)->GetSafeHmenu ();
	m_btnServiceControl.SizeToContent ();
 
	m_edtExe.EnableFileBrowseButton("*.exe", "*.exe|*.exe||");
	ParseSettingFile();

	for(int i=0; i<m_StartExeInfo.size(); i++)
	{
		StartExeInfo& info = m_StartExeInfo[i];
		m_ListEXE.InsertString(-1, info.strExeFile);
	}
	UpdateData(FALSE);

	if (m_cmbInterface.GetCurSel() == -1)
		m_cmbInterface.SetCurSel(0);
	return TRUE;  
}

void CStartServiceDlg::ParseSettingFile()
{
    CString strSettingFile;
	char buf[500] = {0};
	::GetModuleFileName(NULL, buf, 500);
	PathRemoveFileSpec(buf);
    strSettingFile = buf;
	strSettingFile += "\\配置文件.ini";
	ZeroMemory(buf, 500);
	GetPrivateProfileString("Settings", "ServiceName", "MyService", buf, 500, strSettingFile);
	m_strServiceName = buf;
	m_uInterGap = GetPrivateProfileInt("Settings", "CheckForRun", 0, strSettingFile);
	int nProcCount = GetPrivateProfileInt("Settings", "ProcCount", 0, strSettingFile);
	for(int i=0; i<nProcCount; i++)
	{
		CString Item;
		Item.Format("Process%d", i);
		ZeroMemory(buf, 500);
		GetPrivateProfileString(Item, "CommandLine", "", buf, 500, strSettingFile);
		CString strExe = buf;
		ZeroMemory(buf, 500);
		GetPrivateProfileString(Item, "WorkingDir", "", buf, 500, strSettingFile);
		CString strCmd = buf;
        int b = GetPrivateProfileInt(Item, "UserInterface", 0, strSettingFile);
		int nPauseStart = GetPrivateProfileInt(Item, "PauseStart", 0, strSettingFile);
        int nPauseEnd = GetPrivateProfileInt(Item, "PauseEnd", 0, strSettingFile);
        StartExeInfo info(strExe, strCmd, (bool)b, nPauseStart, nPauseEnd);
		m_StartExeInfo.push_back(info);
	}

}

void CStartServiceDlg::OnSelchangeListExe() 
{
	int iOld = m_iLast;
	UpdateData();
	if (iOld != -1)
	{
        StartExeInfo& info = m_StartExeInfo[iOld];
		info.strCmdLine = m_strCmdLine;
		info.nPauseEnd = m_uPauseEnd;
		info.nPauseStart = m_uPauseStart;
		if (m_cmbInterface.GetCurSel() == 0)
			info.bUserInterface = true;
		else
			info.bUserInterface = false;
	}
    int iCurSel = m_ListEXE.GetCurSel();
	if (iCurSel == -1)
		return;
	StartExeInfo& info = m_StartExeInfo[iCurSel];
	m_strExe = info.strExeFile;
	m_strCmdLine = info.strCmdLine;
	m_uPauseEnd = info.nPauseEnd;
	m_uPauseStart = info.nPauseStart;
	if (info.bUserInterface)
		m_cmbInterface.SetCurSel(0);
	else
		m_cmbInterface.SetCurSel(1);
	UpdateData(FALSE);
}

void CStartServiceDlg::OnBtnDelete() 
{
	int iCurSel = m_ListEXE.GetCurSel();
	if (iCurSel == -1)
		return;
	m_ListEXE.DeleteString(iCurSel);
	m_StartExeInfo.erase(m_StartExeInfo.begin() + iCurSel);
	
	if (iCurSel != m_ListEXE.GetCount())
	{
		m_ListEXE.SetCurSel(-1);
		m_ListEXE.SetCurSel(iCurSel);
	}
	else
	{
        if (m_ListEXE.GetCount() == 0)
		{
			m_uPauseStart = m_uPauseEnd = 0;
			m_cmbInterface.SetCurSel(0);
			m_strCmdLine = m_strExe = "";
		}
		else
		{
            m_ListEXE.SetCurSel(-1);
		    m_ListEXE.SetCurSel(iCurSel-1);
		}
	}
	UpdateData(FALSE);
}

void CStartServiceDlg::OnBtnAdd() 
{
	if (UpdateData() == false)
		return;
	if (m_strExe == "")
	{
		AfxMessageBox("请选择可执行文件");
		return;
	}
	bool b;
	int iCurSel = m_cmbInterface.GetCurSel();
	if (iCurSel == 0)
		b = true;
	else
		b = false;
	StartExeInfo info(m_strExe, m_strCmdLine, b, m_uPauseStart, m_uPauseEnd);
	m_StartExeInfo.push_back(info);
	m_ListEXE.AddString(m_strExe);
	
	m_uPauseStart = m_uPauseEnd = 0;
	m_cmbInterface.SetCurSel(0);
	m_strCmdLine = m_strExe = "";
	UpdateData(FALSE);
}

void CStartServiceDlg::StartExeInfo::OutputToSettingFile(CString Item, CString IniFile)
{
	CString str;
	WritePrivateProfileString(Item, "CommandLine", strExeFile, IniFile);
	WritePrivateProfileString(Item, "WorkingDir", strCmdLine, IniFile);
	if (bUserInterface)
		str = "1";
	else
		str = "0";
	WritePrivateProfileString(Item, "UserInterface", str, IniFile);
	str.Format("%d", nPauseStart);
	WritePrivateProfileString(Item, "PauseStart", str, IniFile);
	str.Format("%d", nPauseEnd);
	WritePrivateProfileString(Item, "PauseEnd", str, IniFile);
}

void CStartServiceDlg::OnBtnCreateSettingFile() 
{
	if (UpdateData() == false)
		return;
	if (m_StartExeInfo.size() == 0)
	{
		AfxMessageBox("请选择要启动的可执行程序");
		return;
	}
	if (m_strServiceName == "")
	{
		AfxMessageBox("请设置服务名称");
		return;
	}

    CString strSettingFile;
	char buf[500] = {0};
	::GetModuleFileName(NULL, buf, 500);
	PathRemoveFileSpec(buf);
    strSettingFile = buf;
	strSettingFile += "\\配置文件.ini";

	DeleteFile(strSettingFile);

	CString str;
	CString Item;

	WritePrivateProfileString("Settings", "ServiceName", m_strServiceName, strSettingFile);
	str.Format("%d", m_uInterGap);
	WritePrivateProfileString("Settings", "CheckForRun", str, strSettingFile);
    str.Format("%d", m_StartExeInfo.size());
	WritePrivateProfileString("Settings", "ProcCount", str, strSettingFile);

	for(int i=0; i<m_StartExeInfo.size(); i++)
	{
		Item.Format("Process%d", i);
		StartExeInfo& info = m_StartExeInfo[i];
		info.OutputToSettingFile(Item, strSettingFile);
	}
}

BOOL CStartServiceDlg::Install(char* pPath, char* pName, BOOL bPrompt) 
{  
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE); 
	if (schSCManager==0) 
	{
		if (bPrompt)
			AfxMessageBox("打开服务控制管理器失败，不能安装服务");
		return FALSE;
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
        if (schService != NULL)
		{
            if (bPrompt)
			   AfxMessageBox("服务已经安装");
			CloseServiceHandle(schService);
			CloseServiceHandle(schSCManager);
			return TRUE;
		}

		schService = CreateService
			( 
			schSCManager,	/* SCManager database      */ 
			pName,			/* name of service         */ 
			pName,			/* service name to display */ 
			SERVICE_ALL_ACCESS,        /* desired access          */ 
			SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS , /* service type            */ 
			SERVICE_AUTO_START,      /* start type              */ 
			SERVICE_ERROR_NORMAL,      /* error control type      */ 
			pPath,			/* service's binary        */ 
			NULL,                      /* no load ordering group  */ 
			NULL,                      /* no tag identifier       */ 
			NULL,                      /* no dependencies         */ 
			NULL,                      /* LocalSystem account     */ 
			NULL
			);     
		BOOL bRet;
		
		if (schService==0)
		{
			bRet = false;
			if (bPrompt)
				AfxMessageBox("安装服务失败");
		}
		else
		{
			bRet = true;
			if (bPrompt)
				AfxMessageBox("安装服务成功");
			CloseServiceHandle(schService);
		}
		CloseServiceHandle(schSCManager);
		return bRet;
	}	
}

BOOL CStartServiceDlg::UnInstall(char* pName, BOOL bPrompt)
{
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		if (bPrompt)
			AfxMessageBox("打开服务控制管理器失败，不能卸载服务");
		return FALSE;
	}
	else
	{
		BOOL bRet = FALSE;
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0)
		{
			if (bPrompt)
				AfxMessageBox("打开服务失败，服务没有安装");
			bRet = TRUE;
		}
		else
		{
			KillService(pName, FALSE);
			if(!DeleteService(schService)) 
			{
				if (bPrompt)
					AfxMessageBox("删除服务失败，不能卸载");
			}
			else 
			{
				bRet = TRUE;
				if (bPrompt)
					AfxMessageBox("卸载服务成功");
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager);	
		return bRet;
	}
}

void CStartServiceDlg::OnBtnServiceMenu() 
{
	CString strItem;
	UpdateData();

	switch (m_btnServiceControl.m_nMenuResult)
	{
	case IDR_INSTALL_SERVICE:
		{
			if (m_strServiceName == "")
			{
				AfxMessageBox("服务名称不能为空");
				return;
			}
			char buf[500] = {0};
			GetModuleFileName(NULL, buf, 500);
            Install(buf, m_strServiceName.GetBuffer(m_strServiceName.GetLength()));
			m_strServiceName.ReleaseBuffer();
		}
		break;

	case IDR_UNINSTALL_SERVICE:
		if (m_strServiceName == "")
		{
			AfxMessageBox("服务名称不能为空");
			return;
		}
		UnInstall(m_strServiceName.GetBuffer(m_strServiceName.GetLength()));
		m_strServiceName.ReleaseBuffer();
		break;

	case IDR_START_SERVICE:
		{
			if (m_strServiceName == "")
			{
				AfxMessageBox("服务名称不能为空");
				return;
			}
			CString str = "ServiceStart";
			char* p = str.GetBuffer(str.GetLength());
            RunService(m_strServiceName.GetBuffer(m_strServiceName.GetLength()), 1,(char**)&p);
			str.ReleaseBuffer();
			m_strServiceName.ReleaseBuffer();
		}
		break;

	case IDR_STOP_SERVICE:
		if (m_strServiceName == "")
		{
			AfxMessageBox("服务名称不能为空");
			return;
		}
		KillService(m_strServiceName.GetBuffer(m_strServiceName.GetLength()));
	    m_strServiceName.ReleaseBuffer();
		break;
	case IDR_RESTART_SERVICE:
		if (m_strServiceName == "")
		{
			AfxMessageBox("服务名称不能为空");
			return;
		}
		{
			KillService(m_strServiceName.GetBuffer(m_strServiceName.GetLength()));
			m_strServiceName.ReleaseBuffer();
			CString str = "ServiceStart";
			char* p = str.GetBuffer(str.GetLength());
            RunService(m_strServiceName.GetBuffer(m_strServiceName.GetLength()), 1,(char**)&p);
			str.ReleaseBuffer();
			m_strServiceName.ReleaseBuffer();
		}
		break;
	default:
		return;
	}
}

BOOL CStartServiceDlg::RunService(char* pName, int nArg, char** pArg, BOOL bPrompt) 
{ 
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	BOOL bRet = FALSE;
	if (schSCManager==0) 
	{
		if (bPrompt)
			AfxMessageBox("打开服务控制管理器失败，不能启动服务");
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			if (bPrompt)
				AfxMessageBox("打开服务失败，可能服务没有安装");
		}
		else
		{
			CString s = *pArg;
			if(StartService(schService,nArg,(const char**)pArg))
			{
				if (bPrompt)
					AfxMessageBox("启动服务成功");
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				Sleep(1000);
				return TRUE;
			}
			else
			{
				if (GetLastError() == ERROR_SERVICE_ALREADY_RUNNING)
				{
					if (bPrompt)
					   AfxMessageBox("服务已经启动");
					CloseServiceHandle(schService); 
				    CloseServiceHandle(schSCManager); 
					return TRUE;
				}
				else
				{
					if (bPrompt)
					    AfxMessageBox("启动服务失败");
				}
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}

BOOL CStartServiceDlg::KillService(char* pName, BOOL bPrompt) 
{ 
	SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		if (bPrompt)
			AfxMessageBox("打开服务控制管理器失败，不能停止服务");
	}
	else
	{
		SC_HANDLE schService = OpenService( schSCManager, pName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
		   if (bPrompt)	
		      AfxMessageBox("打开服务失败，可能服务没有安装");
		}
		else
		{
			SERVICE_STATUS status;
			if(ControlService(schService,SERVICE_CONTROL_STOP,&status))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager);
				if (bPrompt)
					AfxMessageBox("停止服务成功");
				return TRUE;
			}
			else
			{
				if (bPrompt)
					AfxMessageBox("停止服务失败");
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}

BOOL CStartServiceDlg::StartProcess(int nIndex) 
{ 
	CString strSettingFile;
	char buf[500] = {0};
	::GetModuleFileName(NULL, buf, 500);
	PathRemoveFileSpec(buf);
    strSettingFile = buf;
	strSettingFile += "\\配置文件.ini";

	STARTUPINFO startUpInfo = { sizeof(STARTUPINFO),NULL,"",NULL,0,0,0,0,0,0,0,STARTF_USESHOWWINDOW,0,0,NULL,0,0,0};  
	char pItem[500];
	sprintf(pItem,"Process%d\0",nIndex);
	char pCommandLine[500];
	GetPrivateProfileString(pItem,"CommandLine","",pCommandLine,500,strSettingFile);
	char pUserInterface[500];
	GetPrivateProfileString(pItem,"UserInterface","N",pUserInterface,500,strSettingFile);
	BOOL bUserInterface = (pUserInterface[0]=='y'||pUserInterface[0]=='Y'||pUserInterface[0]=='1')?TRUE:FALSE;
	if(bUserInterface)
	{
		startUpInfo.wShowWindow = SW_SHOW;
		startUpInfo.lpDesktop = NULL;
	}
	else
	{
		startUpInfo.wShowWindow = SW_HIDE;
		startUpInfo.lpDesktop = "";
	}
	char pWorkingDir[500];
	GetPrivateProfileString(pItem,"WorkingDir","",pWorkingDir,500,strSettingFile);
	if(CreateProcess(NULL,pCommandLine,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS,NULL,strlen(pWorkingDir)==0?NULL:pWorkingDir,&startUpInfo,&m_pProcInfo[nIndex]))
	{
		char pPause[500];
		GetPrivateProfileString(pItem,"PauseStart","100",pPause,500,strSettingFile);
		Sleep(atoi(pPause));
		return TRUE;
	}
	else
	{
		CString strError;
		strError.Format("启动程序 %s 失败", pCommandLine);
		AfxMessageBox(strError);
		return FALSE;
	}
}

void CStartServiceDlg::EndProcess(int nIndex) 
{		
	CString strSettingFile;
	char buf[500] = {0};
	::GetModuleFileName(NULL, buf, 500);
	PathRemoveFileSpec(buf);
    strSettingFile = buf;
	strSettingFile += "\\配置文件.ini";
	char pItem[500];
	sprintf(pItem,"Process%d\0",nIndex);
	char pPause[500];
	GetPrivateProfileString(pItem,"PauseEnd","100",pPause,500,strSettingFile);
	int nPauseEnd = atoi(pPause);
	if(nIndex>=0&&nIndex<m_nProcCount)
	{
		if(m_pProcInfo[nIndex].hProcess)
		{
			if(nPauseEnd>0)
			{
				PostThreadMessage(m_pProcInfo[nIndex].dwThreadId,WM_QUIT,0,0);
				Sleep(nPauseEnd);
			}
			TerminateProcess(m_pProcInfo[nIndex].hProcess,0);
		}
	}
}

////////////////////////////////////////////////////////////////////// 
//
// This routine responds to events concerning your service, like start/stop
//
VOID WINAPI CStartServiceDlg::XYNTServiceHandler(DWORD fdwControl)
{
	switch(fdwControl) 
	{
		case SERVICE_CONTROL_STOP:
		case SERVICE_CONTROL_SHUTDOWN:
			serviceStatus.dwWin32ExitCode = 0; 
			serviceStatus.dwCurrentState  = SERVICE_STOPPED; 
			serviceStatus.dwCheckPoint    = 0; 
			serviceStatus.dwWaitHint      = 0;
			{
				for(int i=m_nProcCount-1;i>=0;i--)
				{
					EndProcess(i);
				}			
				SetServiceStatus(hServiceStatusHandle, &serviceStatus);
			}
			return; 
		case SERVICE_CONTROL_PAUSE:
			serviceStatus.dwCurrentState = SERVICE_PAUSED; 
			break;
		case SERVICE_CONTROL_CONTINUE:
			serviceStatus.dwCurrentState = SERVICE_RUNNING; 
			break;
		case SERVICE_CONTROL_INTERROGATE:
			break;
		default: 
			if(fdwControl>=128&&fdwControl<256)
			{
				int nIndex = fdwControl&0x7F;
				if(nIndex>=0&&nIndex<m_nProcCount)
				{
					EndProcess(nIndex);
					StartProcess(nIndex);
				}
				else if(nIndex==127)
				{
					for(int i=m_nProcCount-1;i>=0;i--)
					{
						EndProcess(i);
					}
					for(i=0;i<m_nProcCount;i++)
					{
						StartProcess(i);
					}
				}
			}
	};
    SetServiceStatus(hServiceStatusHandle,  &serviceStatus);
}

////////////////////////////////////////////////////////////////////// 
//
// This routine gets used to start your service
//
VOID WINAPI CStartServiceDlg::XYNTServiceMain( DWORD dwArgc, LPTSTR *lpszArgv )
{
	DWORD   status = 0; 
    DWORD   specificError = 0xfffffff; 
 
    serviceStatus.dwServiceType        = SERVICE_WIN32; 
    serviceStatus.dwCurrentState       = SERVICE_START_PENDING; 
    serviceStatus.dwControlsAccepted   = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE; 
    serviceStatus.dwWin32ExitCode      = 0; 
    serviceStatus.dwServiceSpecificExitCode = 0; 
    serviceStatus.dwCheckPoint         = 0; 
    serviceStatus.dwWaitHint           = 0; 
 
	AfxMessageBox("OK");
	//Sleep(2000);
	
    hServiceStatusHandle = RegisterServiceCtrlHandler(m_pServiceName, XYNTServiceHandler); 
    if (hServiceStatusHandle==0) 
	{
       AfxMessageBox("启动服务失败");
	   return;
	}
    //ERROR_SERVICE_DOES_NOT_EXIST
    // Handle error condition 
	status = GetLastError(); 
    if (status!=NO_ERROR) 
	{ 
        serviceStatus.dwCurrentState       = SERVICE_STOPPED; 
        serviceStatus.dwCheckPoint         = 0; 
        serviceStatus.dwWaitHint           = 0; 
        serviceStatus.dwWin32ExitCode      = status; 
        serviceStatus.dwServiceSpecificExitCode = specificError; 
        SetServiceStatus(hServiceStatusHandle, &serviceStatus); 
        return; 
    } 

    // Initialization complete - report running status 
    serviceStatus.dwCurrentState       = SERVICE_RUNNING; 
    serviceStatus.dwCheckPoint         = 0; 
    serviceStatus.dwWaitHint           = 0;  
    SetServiceStatus(hServiceStatusHandle, &serviceStatus);

	for(int i=0;i<m_nProcCount;i++)
	{
		m_pProcInfo[i].hProcess = 0;
		StartProcess(i);
		//AfxMessageBox("OOO");
	}
	//CWinThread* pThread = AfxBeginThread((AFX_THREADPROC)WorkerProc, NULL);
	//WaitForSingleObject(pThread->m_hThread, INFINITE);
}

UINT WINAPI  CStartServiceDlg::WorkerProc(void* pParam)
{
	CString strSettingFile;
	char buf[500] = {0};
	::GetModuleFileName(NULL, buf, 500);
	PathRemoveFileSpec(buf);
    strSettingFile = buf;
	strSettingFile += "\\配置文件.ini";
	char pCheckProcess[500];
	GetPrivateProfileString("Settings","CheckForRun","60",pCheckProcess, 500,strSettingFile);
	int nCheckProcess = atoi(pCheckProcess);
	
	while(nCheckProcess>0&&m_nProcCount>0)
	{
		::Sleep(1000*60*nCheckProcess);
		for(int i=0;i<m_nProcCount;i++)
		{
			DWORD dwCode;
			if(::GetExitCodeProcess(m_pProcInfo[i].hProcess, &dwCode))
			{
				if(dwCode != STILL_ACTIVE)
				{
					StartProcess(i);
				}
			}
		}
		AfxMessageBox("OK");
	}
	return 0;
}

bool CStartServiceDlg::OnService()
{
    CString strSettingFile;
	char buf[500] = {0};
	::GetModuleFileName(NULL, buf, 500);
	PathRemoveFileSpec(buf);
    strSettingFile = buf;
	strSettingFile += "\\配置文件.ini";
    memset(m_pServiceName, 0, 500);
	GetPrivateProfileString("Settings", "ServiceName", "MyService", m_pServiceName, 500, strSettingFile);
	m_nProcCount = GetPrivateProfileInt("Settings", "ProcCount", 0, strSettingFile);
	
	SERVICE_TABLE_ENTRY   DispatchTable[2];
	DispatchTable[0].lpServiceName = m_pServiceName;
	DispatchTable[0].lpServiceProc = XYNTServiceMain;
	DispatchTable[1].lpServiceProc = NULL;
	DispatchTable[1].lpServiceName = NULL;

	if (m_nProcCount > 0)
		m_pProcInfo = new PROCESS_INFORMATION[m_nProcCount];
	//_beginthread(WorkerProc, 0, NULL);
	BOOL b = StartServiceCtrlDispatcher(DispatchTable);
	if (b)
	{
		//CWinThread* pThread = AfxBeginThread((AFX_THREADPROC)WorkerProc, NULL);
		//WaitForSingleObject(pThread->m_hThread, INFINITE);
	}
	return b;
}

