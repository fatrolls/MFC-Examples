// MingQQ.cpp : main source file for MingQQ.exe
//

#include "stdafx.h"

#include "resource.h"

#include "aboutdlg.h"
#include "MainDlg.h"

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainDlg dlgMain;

	if(dlgMain.Create(NULL) == NULL)
	{
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}

	dlgMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	tstring strFileName = ZYM::CPath::GetAppPath() + _T("ImageOleCtrl.dll");
	BOOL bRet = DllRegisterServer(strFileName.c_str());	// 注册COM组件
	if (!bRet)
	{
		::MessageBox(NULL, _T("COM组件注册失败，应用程序无法完成初始化操作！"), _T("提示"), MB_OK);
		return 0;
	}

	HRESULT hRes = ::OleInitialize(NULL);
	//HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls
	HMODULE hRichEditDll = ::LoadLibrary(CRichEditCtrl::GetLibraryName());	// 加载RichEdit控件DLL

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	CSkinManager::Init();	// 初始化皮肤管理器
	
	tstring strSkinPath = ZYM::CPath::GetAppPath() + _T("Skins\\");	// 设置皮肤文件夹路径
	CSkinManager::GetInstance()->SetSkinPath(strSkinPath.c_str());
	
	CSkinManager::GetInstance()->LoadConfigXml();	// 加载皮肤列表配置文件

	int nRet = Run(lpstrCmdLine, nCmdShow);

	CSkinManager::UnInit();	// 反初始化皮肤管理器

	if (hRichEditDll != NULL)		// 卸载RichEdit控件DLL
	{
		::FreeLibrary(hRichEditDll);
		hRichEditDll = NULL;
	}

	_Module.Term();
	//::CoUninitialize();
	::OleUninitialize();

	return nRet;
}
