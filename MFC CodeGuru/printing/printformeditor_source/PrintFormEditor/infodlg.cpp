// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PrintFormEditor.h"
#include "InfoDlg.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog
void GfxGetWhenCompiled(CString &when, const char *cPrefix, const char *cSuffix)
{
	const int numMonth = 12;
	char cMonthName[12][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	char cNull[2] = "\0";

	if (cPrefix == NULL) cPrefix = cNull;
	if (cSuffix == NULL) cSuffix = cNull;

	CString mDate =  __DATE__;

	char cMonth[16];
	int iDay, iYear, iMonth = 1;
	sscanf(mDate, "%s %02d %d", cMonth, &iDay, &iYear);
	for (int t = 0; t < numMonth; t++)
		if (0 == lstrcmpi(cMonth, cMonthName[t])) { iMonth = t+1; break; }

	when.Format("%s%02d/%02d/%d %s %s", cPrefix, iDay, iMonth, iYear, __TIME__, cSuffix);
}

void GfxGetWhenThisCompiled(CString &when, const char *wTime, const char *wDate, const char *cPrefix, const char *cSuffix)
{
	const int numMonth = 12;
	char cMonthName[12][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	char cNull[2] = "\0";

	if (cPrefix == NULL) cPrefix = cNull;
	if (cSuffix == NULL) cSuffix = cNull;

	char cMonth[16];
	int iDay, iYear, iMonth = 1;
	sscanf(wDate, "%s %02d %d", cMonth, &iDay, &iYear);
	for (int t = 0; t < numMonth; t++)
		if (0 == lstrcmpi(cMonth, cMonthName[t])) { iMonth = t+1; break; }

	when.Format("%s%02d/%02d/%d %s %s", cPrefix, iDay, iMonth, iYear, wTime, cSuffix);
}

void GfxGetCPUBuiltFor(CString &cpu)
{
	cpu = "Intel";
	switch(_M_IX86)
	{
	case 300:	cpu += " 80386";			break;
	case 400:	cpu += " 80486";			break;
	case 500:	cpu += " Pentium";			break;
	case 600:	cpu += " Pentium Pro";		break;
	}
}

void GfxGetOSRunning(CString &cs)
{ 
	cs = "";
	OSVERSIONINFO os;
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (::GetVersionEx(&os))
	{
		CString cs1;
		if (os.dwPlatformId == VER_PLATFORM_WIN32_NT) cs += "Windows NT";
		else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) cs += "Windows 95";
		else if (os.dwPlatformId == VER_PLATFORM_WIN32s) cs += "Win32s";
		else cs += "Sistema Operativo non identificato";
		DWORD build = os.dwBuildNumber;
		if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) build = LOWORD(os.dwBuildNumber);
		cs1.Format(" versione %d.%d (Build %d) %s", (int) os.dwMajorVersion, (int) os.dwMinorVersion, (int) build, os.szCSDVersion);
		cs += cs1;
	}
}


bool GfxGetFileVersion(CString &ver, const char * file)
{
	ver = "";
	char csFile[_MAX_PATH];
	if (file && *file) lstrcpy(csFile, file);
	else
	{
		::GetModuleFileName(AfxGetInstanceHandle(), csFile, _MAX_PATH);
		TRACE1("Automatic exe file name: %s\n", csFile);
 	}
	DWORD shit = 1;
	DWORD size = GetFileVersionInfoSize(csFile, &shit);
	if (size == 0) { ver = ""; return false; }

	void * pVer;
	pVer = (void *) GlobalAlloc(GPTR, size);
	ASSERT(pVer);
	if (pVer)
	{ 
		if (GetFileVersionInfo(csFile, 0L, size, pVer))
		{ 
			VS_FIXEDFILEINFO * ppvff;
			UINT vffSize = sizeof(VS_FIXEDFILEINFO);
			if (VerQueryValue(pVer, "\\", (void **) &ppvff, &vffSize))
			{
				WORD w5,w6,w7,w8;
				w5 = HIWORD(ppvff->dwProductVersionMS);
				w6 = LOWORD(ppvff->dwProductVersionMS);
				w7 = HIWORD(ppvff->dwProductVersionLS);
				w8 = LOWORD(ppvff->dwProductVersionLS);
				ver.Format(" %d.%02d.%02d (build %d)", (int) w5, (int) w6, (int) w7, (int) w8);
				if (ppvff->dwFileFlags&VS_FF_DEBUG) ver += " - debug";
				if (ppvff->dwFileFlags&VS_FF_DEBUG && ppvff->dwFileFlags&VS_FF_PRERELEASE) ver += ", ";
				if (!(ppvff->dwFileFlags&VS_FF_DEBUG) && ppvff->dwFileFlags&VS_FF_PRERELEASE) ver += " - ";
				if (ppvff->dwFileFlags&VS_FF_PRERELEASE) ver += "beta";
				GlobalFree((HGLOBAL) pVer);
				return true;
			}
		}
		GlobalFree((HGLOBAL) pVer);
	}
	return false;
}


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 15;
	lf.lfWeight = 700;
	lstrcpy(lf.lfFaceName, "Arial");
	fonTitle.CreateFontIndirect(&lf);
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoDlg)
	ON_BN_CLICKED(IDC_BT_SYSINFO, OnBtSysinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers

void CInfoDlg::OnBtSysinfo() 
{
	HKEY hKey1;
	LONG res = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Shared Tools\\MSInfo",0L,KEY_ALL_ACCESS,&hKey1);
	if (res == ERROR_SUCCESS)
	{
		DWORD bufsize = _MAX_PATH;
		char msinfo[_MAX_PATH];

		res = RegQueryValueEx(hKey1,"Path",0L,0,(LPBYTE)msinfo,(LPDWORD)&bufsize);
		RegCloseKey(hKey1);
		if (res == ERROR_SUCCESS) WinExec(msinfo, SW_SHOW);
	}
}

BOOL CInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char * cMicrosoftSound = new char[_MAX_PATH];
	if (cMicrosoftSound)
	{
		if (GetWindowsDirectory(cMicrosoftSound, _MAX_PATH))
		{
			if (lstrlen(cMicrosoftSound)>0 && cMicrosoftSound[lstrlen(cMicrosoftSound)-1] != '\\')
				lstrcat(cMicrosoftSound, "\\");

			lstrcat(cMicrosoftSound, "Media\\The Microsoft Sound.wav");

			sndPlaySound(cMicrosoftSound, SND_ASYNC|SND_NODEFAULT);
		}
		delete [] cMicrosoftSound;
	}


	GetDlgItem(IDC_TEXT4)->SetFont(&fonTitle, true);

	SetDlgItemText(IDC_TEXT1, "Mr. John Doe");
	SetDlgItemText(IDC_TEXT2, "A.C.M.E. Corporation");
	SetDlgItemText(IDC_TEXT3, "xxxx-xxxx-xxxxxx");
	
	CString csInfo, csResult;
	CString csCPU, csVer;
	GetDlgItemText(IDC_TEXT4, csInfo);

	GfxGetFileVersion(csVer, NULL);
	GfxGetCPUBuiltFor(csCPU);
	csVer += " per ";
	csVer += csCPU;
	csInfo += csVer;

	SetDlgItemText(IDC_TEXT4, csInfo);

	GfxGetWhenThisCompiled(csInfo, __TIME__, __DATE__, "Compilazione:", NULL);
	SetDlgItemText(IDC_TEXT5, csInfo);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
