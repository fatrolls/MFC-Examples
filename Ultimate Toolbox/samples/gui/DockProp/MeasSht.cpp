// ==========================================================================
// 							Class Implementation : CMeasureSheet
// ==========================================================================

// Source file : MeasSht.cpp

//=================== Dundas Software     ===================================
//
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"		// standard MFC include
#include "MeasSht.h"		// class specification
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeasureSheet

BEGIN_MESSAGE_MAP(CMeasureSheet, COXDockPropertySheet)
	//{{AFX_MSG_MAP(CMeasureSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMeasureSheet::CMeasureSheet() :
	COXDockPropertySheet(_T("Measure Tools")),
	m_measurePage(),
	m_sectionPage()
	{
	AddPage(&m_measurePage);
	AddPage(&m_sectionPage);
	}


void CMeasureSheet::AddOnePage()
	{
	CMeasurePage* pNewMeasurePage = new CMeasurePage(TRUE);
	AddPage(pNewMeasurePage, TRUE);
	}

