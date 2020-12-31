//
// UITest.cpp : main source file for UITest.exe
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <crtdbg.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>

// Including the map turns a implementation to STL
//#include <map>
#include <wtlx/ui_update.hpp>

#include "resource.h"
#define ATL_IDW_TOOLBAR1 ATL_IDW_TOOLBAR
#define ATL_IDW_TOOLBAR2 ATL_IDW_TOOLBAR + 1
#define ATL_IDW_BAND1 ATL_IDW_BAND_FIRST
#define ATL_IDW_BAND2 ATL_IDW_BAND_FIRST + 1

#include "UITestView.h"
#include "aboutdlg.h"
#include "ChildFrm.h"
#include "MainFrm.h"


CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
//	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	//ATLASSERT(SUCCEEDED(hRes));

#if (_WIN32_IE >= 0x0300)
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
	BOOL bRet = ::InitCommonControlsEx(&iccx);
	bRet;
	ATLASSERT(bRet);
#else
	::InitCommonControls();
#endif

	HRESULT hr = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hr));


	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	//::CoUninitialize();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return nRet;
}
