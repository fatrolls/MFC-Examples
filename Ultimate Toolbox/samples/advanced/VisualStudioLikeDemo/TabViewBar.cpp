// TabViewBar.cpp : implementation file
//

#include "stdafx.h"
#include "VisualStudioLikeDemo.h"
#include "TabViewBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabViewBar
//

IMPLEMENT_DYNAMIC(CTabViewBar, COXSizeControlBar);

CTabViewBar::CTabViewBar() 
	: COXSizeControlBar(
	SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
}

CTabViewBar::~CTabViewBar()
{
}



BEGIN_MESSAGE_MAP(CTabViewBar, COXSizeControlBar)
	//{{AFX_MSG_MAP(CTabViewBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTabViewBar message handlers


//-------------------------------------------------------------------
void CTabViewBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	CRect rect;
	GetClientRect(rect);

	m_TabViewContainer.MoveWindow(&rect);
}


//-------------------------------------------------------------------
int CTabViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//-------------------------------------------------------------------
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	
	if(!m_TabViewContainer.Create(this,rect))
		return -1;

	// build page
	if(!m_build.Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),
		&m_TabViewContainer,1))
		return -1;
	m_TabViewContainer.AddPage(&m_build,_T("Build"));

	m_build.AddLine(_T("Generating Code..."));
	m_build.AddLine(_T("Linking..."));
	m_build.AddLine(_T(""));
	m_build.SetTextColor(RGB(255,0,0));
	m_build.AddLine(_T("VisualStudioLikeDemo.exe - 0 error(s), 0 warning(s)"));

	// debug page
	if(!m_debug.Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),
		&m_TabViewContainer,2))
		return -1;
	m_TabViewContainer.AddPage(&m_debug,_T("Debug"));
	m_debug.AddLine(_T("Loaded symbols for 'D:\\Ultimate ToolBox\\Samples\\gui\\VisualStudioLikeDemo\\Debug\\VisualStudioLikeDemo.exe'"));
	m_debug.AddLine(_T("Loaded 'F:\\WINNT\\system32\\NTDLL.DLL', no matching symbolic information found."));
	m_debug.AddLine(_T("Loaded symbols for 'F:\\WINNT\\system32\\MFC42D.DLL'"));
	m_debug.AddLine(_T("Loaded symbols for 'F:\\WINNT\\system32\\MSVCRTD.DLL'"));
	m_debug.AddLine(_T("Loaded 'F:\\WINNT\\system32\\KERNEL32.DLL', no matching symbolic information found."));
	m_debug.AddLine(_T("Loaded 'F:\\WINNT\\system32\\riched32.dll', no matching symbolic information found."));
	m_debug.AddLine(_T("Loaded symbols for 'F:\\WINNT\\system32\\MFCO42D.DLL'"));
	m_debug.AddLine(_T("Loaded 'F:\\WINNT\\system32\\USER32.DLL', no matching symbolic information found."));
	m_debug.AddLine(_T("The thread 0xB1 has exited with code 0 (0x0)."));
	m_debug.AddLine(_T("The program 'D:\\Ultimate ToolBox\\Samples\\gui\\VisualStudioLikeDemo\\Debug\\VisualStudioLikeDemo.exe' has exited with code 0 (0x0)."));

	// Find In Files 1 page
	if(!m_find1.Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),
		&m_TabViewContainer,3))
		return -1;
	m_TabViewContainer.AddPage(&m_find1,_T("Find In Files 1"));
	m_find1.AddLine(_T("Searching for 'class CWnd'..."));
	m_find1.AddLine(_T("F:\\Program Files\\Microsoft Visual Studio\\VC98\\MFC\\Include\\AFXCMN.H(680): friend class CWnd;"));
	m_find1.AddLine(_T("F:\\Program Files\\Microsoft Visual Studio\\VC98\\MFC\\Include\\AFXSTAT_.H(169):class CWnd;"));
	m_find1.AddLine(_T("F:\\Program Files\\Microsoft Visual Studio\\VC98\\MFC\\Include\\AFXWIN.H(86):  class CWnd;                 // a window / HWND wrapper"));
	m_find1.AddLine(_T("F:\\Program Files\\Microsoft Visual Studio\\VC98\\MFC\\Include\\AFXWIN.H(1899):class CWnd : public CCmdTarget"));
	m_find1.AddLine(_T("F:\\Program Files\\Microsoft Visual Studio\\VC98\\MFC\\Include\\AFXWIN.H(3273): friend class CWnd;  // for access to m_bModalDisable"));
	m_find1.AddLine(_T("5 occurrence(s) have been found."));

	// Find In Files 2 page
	if(!m_find2.Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),
		&m_TabViewContainer,4))
		return -1;
	m_TabViewContainer.AddPage(&m_find2,_T("Find In Files 2"));

	// results page
	if(!m_results.Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),
		&m_TabViewContainer,5))
		return -1;
	m_TabViewContainer.AddPage(&m_results,_T("Results"));

	// SQL Debugging page
	if(!m_SQLdebug.Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),
		&m_TabViewContainer,6))
		return -1;
	m_TabViewContainer.AddPage(&m_SQLdebug,_T("SQL Debugging"));

	m_TabViewContainer.SetActivePageIndex(0);
	
	return 0;					
}


BOOL CTabViewBar::Create(CWnd * pParentWnd, 
						 const CString& sTitle/*=_T("TabViewBar")*/,
						 const UINT nID/*=ID_TABVIEWBAR*/)
{
	// register a window class for the control bar
	static CString strWndClass;
	if (strWndClass.IsEmpty())
	{
		strWndClass = AfxRegisterWndClass(CS_DBLCLKS);
	}
	
	return COXSizeControlBar::Create(strWndClass, sTitle,
		WS_VISIBLE|WS_CHILD|CBRS_BOTTOM|WS_CLIPCHILDREN,
		CFrameWnd::rectDefault, pParentWnd, nID);
}



