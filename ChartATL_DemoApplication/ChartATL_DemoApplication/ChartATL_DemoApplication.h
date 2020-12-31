// ChartATL_DemoApplication.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CChartATL_DemoApplicationApp:
// See ChartATL_DemoApplication.cpp for the implementation of this class
//

class CChartATL_DemoApplicationApp : public CWinApp
{
public:
	CChartATL_DemoApplicationApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CChartATL_DemoApplicationApp theApp;