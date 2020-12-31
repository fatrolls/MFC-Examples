/////////////////////////////////////////////////////////////////
//MyStatusBar.cpp:
//==============
#include "stdafx.h"
#include "ClockStatusBar.h"
#include "Resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CClockStatusBar, CStatusBar)

BEGIN_MESSAGE_MAP(CClockStatusBar, CStatusBar)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, OnUpdateIndicatorTime)
END_MESSAGE_MAP()

CClockStatusBar::CClockStatusBar() : CStatusBar(), m_strClockFormat("%H:%M:%S")
{
}

CClockStatusBar::~CClockStatusBar() {
}

void CClockStatusBar::SetClockFormat(LPCTSTR strClockFormat) {
     m_strClockFormat = strClockFormat;
}

int CClockStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct) {
     // make sure time gets updated every second, even when idle
     CStatusBar::OnCreate(lpCreateStruct);
     SetTimer(ID_INDICATOR_TIME,1000,NULL);
     return 0;
}

void CClockStatusBar::OnUpdateIndicatorTime(CCmdUI* pCmdUI) {
     pCmdUI->Enable(true);
     pCmdUI->SetText(CTime::GetCurrentTime().Format(m_strClockFormat));
}

void CClockStatusBar::OnDestroy() {
     KillTimer(ID_INDICATOR_TIME);
     CStatusBar::OnDestroy();
}