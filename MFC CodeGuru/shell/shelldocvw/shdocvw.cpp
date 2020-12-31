// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "shdocvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IWebBrowser properties

/////////////////////////////////////////////////////////////////////////////
// IWebBrowser operations

void IWebBrowser::GoBack()
{
	InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser::GoForward()
{
	InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser::GoHome()
{
	InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser::GoSearch()
{
	InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser::Navigate(LPCTSTR URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Flags, TargetFrameName, PostData, Headers);
}

void IWebBrowser::Refresh()
{
	InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser::Refresh2(VARIANT* Level)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Level);
}

void IWebBrowser::Stop()
{
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IWebBrowser::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWebBrowser::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWebBrowser::GetContainer()
{
	LPDISPATCH result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWebBrowser::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IWebBrowser::GetTopLevelContainer()
{
	BOOL result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IWebBrowser::GetType()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IWebBrowser::GetLeft()
{
	long result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowser::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IWebBrowser::GetTop()
{
	long result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowser::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IWebBrowser::GetWidth()
{
	long result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowser::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IWebBrowser::GetHeight()
{
	long result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowser::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IWebBrowser::GetLocationName()
{
	CString result;
	InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IWebBrowser::GetLocationURL()
{
	CString result;
	InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IWebBrowser::GetBusy()
{
	BOOL result;
	InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// DWebBrowserEvents properties

/////////////////////////////////////////////////////////////////////////////
// DWebBrowserEvents operations

void DWebBrowserEvents::BeforeNavigate(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT* PostData, LPCTSTR Headers, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PBOOL;
	InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Flags, TargetFrameName, PostData, Headers, Cancel);
}

void DWebBrowserEvents::NavigateComplete(LPCTSTR URL)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL);
}

void DWebBrowserEvents::StatusTextChange(LPCTSTR Text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text);
}

void DWebBrowserEvents::ProgressChange(long Progress, long ProgressMax)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Progress, ProgressMax);
}

void DWebBrowserEvents::DownloadComplete()
{
	InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DWebBrowserEvents::CommandStateChange(long Command, BOOL Enable)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Command, Enable);
}

void DWebBrowserEvents::DownloadBegin()
{
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DWebBrowserEvents::NewWindow(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT* PostData, LPCTSTR Headers, BOOL* Processed)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PBOOL;
	InvokeHelper(0x6b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Flags, TargetFrameName, PostData, Headers, Processed);
}

void DWebBrowserEvents::TitleChange(LPCTSTR Text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text);
}

void DWebBrowserEvents::FrameBeforeNavigate(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT* PostData, LPCTSTR Headers, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PBOOL;
	InvokeHelper(0xc8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Flags, TargetFrameName, PostData, Headers, Cancel);
}

void DWebBrowserEvents::FrameNavigateComplete(LPCTSTR URL)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL);
}

void DWebBrowserEvents::FrameNewWindow(LPCTSTR URL, long Flags, LPCTSTR TargetFrameName, VARIANT* PostData, LPCTSTR Headers, BOOL* Processed)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_BSTR VTS_PVARIANT VTS_BSTR VTS_PBOOL;
	InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Flags, TargetFrameName, PostData, Headers, Processed);
}

void DWebBrowserEvents::Quit(BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_PBOOL;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Cancel);
}

void DWebBrowserEvents::WindowMove()
{
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DWebBrowserEvents::WindowResize()
{
	InvokeHelper(0x6e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DWebBrowserEvents::WindowActivate()
{
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DWebBrowserEvents::PropertyChange(LPCTSTR Property_)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Property_);
}


/////////////////////////////////////////////////////////////////////////////
// IWebBrowserApp properties

/////////////////////////////////////////////////////////////////////////////
// IWebBrowserApp operations

void IWebBrowserApp::GoBack()
{
	InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowserApp::GoForward()
{
	InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowserApp::GoHome()
{
	InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowserApp::GoSearch()
{
	InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowserApp::Navigate(LPCTSTR URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Flags, TargetFrameName, PostData, Headers);
}

void IWebBrowserApp::Refresh()
{
	InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowserApp::Refresh2(VARIANT* Level)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Level);
}

void IWebBrowserApp::Stop()
{
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IWebBrowserApp::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWebBrowserApp::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWebBrowserApp::GetContainer()
{
	LPDISPATCH result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWebBrowserApp::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IWebBrowserApp::GetTopLevelContainer()
{
	BOOL result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IWebBrowserApp::GetType()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IWebBrowserApp::GetLeft()
{
	long result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IWebBrowserApp::GetTop()
{
	long result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IWebBrowserApp::GetWidth()
{
	long result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IWebBrowserApp::GetHeight()
{
	long result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IWebBrowserApp::GetLocationName()
{
	CString result;
	InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IWebBrowserApp::GetLocationURL()
{
	CString result;
	InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IWebBrowserApp::GetBusy()
{
	BOOL result;
	InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::Quit()
{
	InvokeHelper(0x12c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowserApp::ClientToWindow(long* pcx, long* pcy)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4;
	InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pcx, pcy);
}

void IWebBrowserApp::PutProperty(LPCTSTR Property_, const VARIANT& vtValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Property_, &vtValue);
}

VARIANT IWebBrowserApp::GetProperty_(LPCTSTR Property_)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Property_);
	return result;
}

CString IWebBrowserApp::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IWebBrowserApp::GetHwnd()
{
	long result;
	InvokeHelper(DISPID_HWND, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IWebBrowserApp::GetFullName()
{
	CString result;
	InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IWebBrowserApp::GetPath()
{
	CString result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IWebBrowserApp::GetVisible()
{
	BOOL result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowserApp::GetStatusBar()
{
	BOOL result;
	InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetStatusBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString IWebBrowserApp::GetStatusText()
{
	CString result;
	InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetStatusText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IWebBrowserApp::GetToolBar()
{
	long result;
	InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetToolBar(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IWebBrowserApp::GetMenuBar()
{
	BOOL result;
	InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetMenuBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowserApp::GetFullScreen()
{
	BOOL result;
	InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowserApp::SetFullScreen(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x197, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IWebBrowser2 properties

/////////////////////////////////////////////////////////////////////////////
// IWebBrowser2 operations

void IWebBrowser2::GoBack()
{
	InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser2::GoForward()
{
	InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser2::GoHome()
{
	InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser2::GoSearch()
{
	InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser2::Navigate(LPCTSTR URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Flags, TargetFrameName, PostData, Headers);
}

void IWebBrowser2::Refresh()
{
	InvokeHelper(DISPID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser2::Refresh2(VARIANT* Level)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Level);
}

void IWebBrowser2::Stop()
{
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IWebBrowser2::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0xc8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWebBrowser2::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWebBrowser2::GetContainer()
{
	LPDISPATCH result;
	InvokeHelper(0xca, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IWebBrowser2::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0xcb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IWebBrowser2::GetTopLevelContainer()
{
	BOOL result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IWebBrowser2::GetType()
{
	CString result;
	InvokeHelper(0xcd, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IWebBrowser2::GetLeft()
{
	long result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IWebBrowser2::GetTop()
{
	long result;
	InvokeHelper(0xcf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xcf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IWebBrowser2::GetWidth()
{
	long result;
	InvokeHelper(0xd0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IWebBrowser2::GetHeight()
{
	long result;
	InvokeHelper(0xd1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IWebBrowser2::GetLocationName()
{
	CString result;
	InvokeHelper(0xd2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IWebBrowser2::GetLocationURL()
{
	CString result;
	InvokeHelper(0xd3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IWebBrowser2::GetBusy()
{
	BOOL result;
	InvokeHelper(0xd4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::Quit()
{
	InvokeHelper(0x12c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IWebBrowser2::ClientToWindow(long* pcx, long* pcy)
{
	static BYTE parms[] =
		VTS_PI4 VTS_PI4;
	InvokeHelper(0x12d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pcx, pcy);
}

void IWebBrowser2::PutProperty(LPCTSTR Property_, const VARIANT& vtValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Property_, &vtValue);
}

VARIANT IWebBrowser2::GetProperty_(LPCTSTR Property_)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Property_);
	return result;
}

CString IWebBrowser2::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IWebBrowser2::GetHwnd()
{
	long result;
	InvokeHelper(DISPID_HWND, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IWebBrowser2::GetFullName()
{
	CString result;
	InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IWebBrowser2::GetPath()
{
	CString result;
	InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IWebBrowser2::GetVisible()
{
	BOOL result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowser2::GetStatusBar()
{
	BOOL result;
	InvokeHelper(0x193, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetStatusBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString IWebBrowser2::GetStatusText()
{
	CString result;
	InvokeHelper(0x194, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetStatusText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x194, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IWebBrowser2::GetToolBar()
{
	long result;
	InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetToolBar(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IWebBrowser2::GetMenuBar()
{
	BOOL result;
	InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetMenuBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x196, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowser2::GetFullScreen()
{
	BOOL result;
	InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetFullScreen(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x197, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IWebBrowser2::Navigate2(VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1f4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Flags, TargetFrameName, PostData, Headers);
}

long IWebBrowser2::QueryStatusWB(long cmdID)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		cmdID);
	return result;
}

void IWebBrowser2::ExecWB(long cmdID, long cmdexecopt, VARIANT* pvaIn, VARIANT* pvaOut)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1f6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 cmdID, cmdexecopt, pvaIn, pvaOut);
}

void IWebBrowser2::ShowBrowserBar(VARIANT* pvaClsid, VARIANT* pvarShow, VARIANT* pvarSize)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1f7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pvaClsid, pvarShow, pvarSize);
}

long IWebBrowser2::GetReadyState()
{
	long result;
	InvokeHelper(DISPID_READYSTATE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL IWebBrowser2::GetOffline()
{
	BOOL result;
	InvokeHelper(0x226, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetOffline(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x226, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowser2::GetSilent()
{
	BOOL result;
	InvokeHelper(0x227, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetSilent(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x227, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowser2::GetRegisterAsBrowser()
{
	BOOL result;
	InvokeHelper(0x228, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetRegisterAsBrowser(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x228, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowser2::GetRegisterAsDropTarget()
{
	BOOL result;
	InvokeHelper(0x229, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetRegisterAsDropTarget(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x229, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowser2::GetTheaterMode()
{
	BOOL result;
	InvokeHelper(0x22a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetTheaterMode(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x22a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowser2::GetAddressBar()
{
	BOOL result;
	InvokeHelper(0x22b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetAddressBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x22b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IWebBrowser2::GetResizable()
{
	BOOL result;
	InvokeHelper(0x22c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IWebBrowser2::SetResizable(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x22c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// DWebBrowserEvents2 properties

/////////////////////////////////////////////////////////////////////////////
// DWebBrowserEvents2 operations

void DWebBrowserEvents2::StatusTextChange(LPCTSTR Text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text);
}

void DWebBrowserEvents2::ProgressChange(long Progress, long ProgressMax)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Progress, ProgressMax);
}

void DWebBrowserEvents2::CommandStateChange(long Command, BOOL Enable)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Command, Enable);
}

void DWebBrowserEvents2::DownloadBegin()
{
	InvokeHelper(0x6a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DWebBrowserEvents2::DownloadComplete()
{
	InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DWebBrowserEvents2::TitleChange(LPCTSTR Text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Text);
}

void DWebBrowserEvents2::PropertyChange(LPCTSTR szProperty)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 szProperty);
}

void DWebBrowserEvents2::BeforeNavigate2(LPDISPATCH pDisp, VARIANT* URL, VARIANT* Flags, VARIANT* TargetFrameName, VARIANT* PostData, VARIANT* Headers, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PBOOL;
	InvokeHelper(0xfa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pDisp, URL, Flags, TargetFrameName, PostData, Headers, Cancel);
}

void DWebBrowserEvents2::NewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
{
	static BYTE parms[] =
		VTS_PDISPATCH VTS_PBOOL;
	InvokeHelper(0xfb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ppDisp, Cancel);
}

void DWebBrowserEvents2::NavigateComplete2(LPDISPATCH pDisp, VARIANT* URL)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PVARIANT;
	InvokeHelper(0xfc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pDisp, URL);
}

void DWebBrowserEvents2::DocumentComplete(LPDISPATCH pDisp, VARIANT* URL)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_PVARIANT;
	InvokeHelper(0x103, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pDisp, URL);
}

void DWebBrowserEvents2::OnQuit()
{
	InvokeHelper(0xfd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DWebBrowserEvents2::OnVisible(BOOL Visible)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xfe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Visible);
}

void DWebBrowserEvents2::OnToolBar(BOOL ToolBar)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xff, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ToolBar);
}

void DWebBrowserEvents2::OnMenuBar(BOOL MenuBar)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x100, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MenuBar);
}

void DWebBrowserEvents2::OnStatusBar(BOOL StatusBar)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x101, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 StatusBar);
}

void DWebBrowserEvents2::OnFullScreen(BOOL FullScreen)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x102, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FullScreen);
}

void DWebBrowserEvents2::OnTheaterMode(BOOL TheaterMode)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x104, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 TheaterMode);
}


/////////////////////////////////////////////////////////////////////////////
// IFolderViewOC properties

/////////////////////////////////////////////////////////////////////////////
// IFolderViewOC operations

void IFolderViewOC::SetFolderView(LPDISPATCH pDisp)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pDisp);
}


/////////////////////////////////////////////////////////////////////////////
// DShellFolderViewEvents properties

/////////////////////////////////////////////////////////////////////////////
// DShellFolderViewEvents operations

void DShellFolderViewEvents::SelectionChanged()
{
	InvokeHelper(0xc8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// DShellWindowsEvents properties

/////////////////////////////////////////////////////////////////////////////
// DShellWindowsEvents operations

void DShellWindowsEvents::WindowRegistered(long lCookie)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lCookie);
}

void DShellWindowsEvents::WindowRevoked(long lCookie)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 lCookie);
}


/////////////////////////////////////////////////////////////////////////////
// IShellWindows properties

/////////////////////////////////////////////////////////////////////////////
// IShellWindows operations

long IShellWindows::GetCount()
{
	long result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IShellWindows::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPUNKNOWN IShellWindows::_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_METHOD, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IShellLinkDual properties

/////////////////////////////////////////////////////////////////////////////
// IShellLinkDual operations

CString IShellLinkDual::GetPath()
{
	CString result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IShellLinkDual::SetPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IShellLinkDual::GetDescription()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IShellLinkDual::SetDescription(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IShellLinkDual::GetWorkingDirectory()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IShellLinkDual::SetWorkingDirectory(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IShellLinkDual::GetArguments()
{
	CString result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IShellLinkDual::SetArguments(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IShellLinkDual::GetHotkey()
{
	long result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IShellLinkDual::SetHotkey(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IShellLinkDual::GetShowCommand()
{
	long result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IShellLinkDual::SetShowCommand(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IShellLinkDual::Resolve(long fFlags)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 fFlags);
}

long IShellLinkDual::GetIconLocation(BSTR* pbs)
{
	long result;
	static BYTE parms[] =
		VTS_PBSTR;
	InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pbs);
	return result;
}

void IShellLinkDual::SetIconLocation(LPCTSTR bs, long iIcon)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bs, iIcon);
}

void IShellLinkDual::Save(const VARIANT& vWhere)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &vWhere);
}


/////////////////////////////////////////////////////////////////////////////
// FolderItemVerb properties

/////////////////////////////////////////////////////////////////////////////
// FolderItemVerb operations

LPDISPATCH FolderItemVerb::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItemVerb::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString FolderItemVerb::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FolderItemVerb::DoIt()
{
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// FolderItemVerbs properties

/////////////////////////////////////////////////////////////////////////////
// FolderItemVerbs operations

long FolderItemVerbs::GetCount()
{
	long result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItemVerbs::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItemVerbs::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItemVerbs::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPUNKNOWN FolderItemVerbs::_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_METHOD, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Folder properties

/////////////////////////////////////////////////////////////////////////////
// Folder operations

CString Folder::GetTitle()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH Folder::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Folder::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Folder::GetParentFolder()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Folder::Items()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH Folder::ParseName(LPCTSTR bName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		bName);
	return result;
}

void Folder::NewFolder(LPCTSTR bName, const VARIANT& vOptions)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bName, &vOptions);
}

void Folder::MoveHere(const VARIANT& vItem, const VARIANT& vOptions)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &vItem, &vOptions);
}

void Folder::CopyHere(const VARIANT& vItem, const VARIANT& vOptions)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &vItem, &vOptions);
}

CString Folder::GetDetailsOf(const VARIANT& vItem, long iColumn)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT VTS_I4;
	InvokeHelper(0x60020009, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		&vItem, iColumn);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// FolderItems properties

/////////////////////////////////////////////////////////////////////////////
// FolderItems operations

long FolderItems::GetCount()
{
	long result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItems::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItems::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItems::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

LPUNKNOWN FolderItems::_NewEnum()
{
	LPUNKNOWN result;
	InvokeHelper(0xfffffffc, DISPATCH_METHOD, VT_UNKNOWN, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// FolderItem properties

/////////////////////////////////////////////////////////////////////////////
// FolderItem operations

LPDISPATCH FolderItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString FolderItem::GetName()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void FolderItem::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString FolderItem::GetPath()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItem::GetGetLink()
{
	LPDISPATCH result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItem::GetGetFolder()
{
	LPDISPATCH result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL FolderItem::GetIsLink()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL FolderItem::GetIsFolder()
{
	BOOL result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL FolderItem::GetIsFileSystem()
{
	BOOL result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL FolderItem::GetIsBrowsable()
{
	BOOL result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

DATE FolderItem::GetModifyDate()
{
	DATE result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_DATE, (void*)&result, NULL);
	return result;
}

void FolderItem::SetModifyDate(DATE newValue)
{
	static BYTE parms[] =
		VTS_DATE;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long FolderItem::GetSize()
{
	long result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString FolderItem::GetType()
{
	CString result;
	InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH FolderItem::Verbs()
{
	LPDISPATCH result;
	InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void FolderItem::InvokeVerb(const VARIANT& vVerb)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020010, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &vVerb);
}


/////////////////////////////////////////////////////////////////////////////
// IShellFolderViewDual properties

/////////////////////////////////////////////////////////////////////////////
// IShellFolderViewDual operations

LPDISPATCH IShellFolderViewDual::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IShellFolderViewDual::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IShellFolderViewDual::GetFolder()
{
	LPDISPATCH result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IShellFolderViewDual::SelectedItems()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IShellFolderViewDual::GetFocusedItem()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IShellFolderViewDual::SelectItem(VARIANT* pvfi, long dwFlags)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_I4;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pvfi, dwFlags);
}

CString IShellFolderViewDual::PopupItemMenu(LPDISPATCH pfi, const VARIANT& vx, const VARIANT& vy)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		pfi, &vx, &vy);
	return result;
}

LPDISPATCH IShellFolderViewDual::GetScript()
{
	LPDISPATCH result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IShellFolderViewDual::GetViewOptions()
{
	long result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IShellDispatch properties

/////////////////////////////////////////////////////////////////////////////
// IShellDispatch operations

LPDISPATCH IShellDispatch::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IShellDispatch::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IShellDispatch::NameSpace(const VARIANT& vDir)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&vDir);
	return result;
}

LPDISPATCH IShellDispatch::BrowseForFolder(long HWND, LPCTSTR Title, long Options, const VARIANT& RootFolder)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_I4 VTS_VARIANT;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		HWND, Title, Options, &RootFolder);
	return result;
}

LPDISPATCH IShellDispatch::Windows()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IShellDispatch::Open(const VARIANT& vDir)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &vDir);
}

void IShellDispatch::Explore(const VARIANT& vDir)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &vDir);
}

void IShellDispatch::MinimizeAll()
{
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::UndoMinimizeALL()
{
	InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::FileRun()
{
	InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::CascadeWindows()
{
	InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::TileVertically()
{
	InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::TileHorizontally()
{
	InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::ShutdownWindows()
{
	InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::Suspend()
{
	InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::EjectPC()
{
	InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::SetTime()
{
	InvokeHelper(0x60020010, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::TrayProperties()
{
	InvokeHelper(0x60020011, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::Help()
{
	InvokeHelper(0x60020012, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::FindFiles()
{
	InvokeHelper(0x60020013, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::FindComputer()
{
	InvokeHelper(0x60020014, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::RefreshMenu()
{
	InvokeHelper(0x60020015, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IShellDispatch::ControlPanelItem(LPCTSTR szDir)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020016, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 szDir);
}


/////////////////////////////////////////////////////////////////////////////
// IShellUIHelper properties

/////////////////////////////////////////////////////////////////////////////
// IShellUIHelper operations

void IShellUIHelper::AddFavorite(LPCTSTR URL, VARIANT* Title)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Title);
}

void IShellUIHelper::AddChannel(LPCTSTR URL)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL);
}

void IShellUIHelper::AddDesktopComponent(LPCTSTR URL, LPCTSTR Type, VARIANT* Left, VARIANT* Top, VARIANT* Width, VARIANT* Height)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, Type, Left, Top, Width, Height);
}

BOOL IShellUIHelper::IsSubscribed(LPCTSTR URL)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		URL);
	return result;
}
