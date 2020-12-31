#include "stdafx.h"
#include "XPStyleButtonST.h"
#include <Windows.h>
#include <Winuser.h>

//#if(WINVER >= 0x0501)
#ifdef	THEMEAPI
#include <tmschema.h>
#else
#define	NO_THEMEAPI_FOUND

#define	BP_PUSHBUTTON	0x00000001
#define	PBS_NORMAL		0x00000001
#define	PBS_HOT			0x00000002
#define	PBS_PRESSED		0x00000003
#define	PBS_DISABLED	0x00000004
#define	PBS_DEFAULTED	0x00000005
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXPStyleButtonST::CXPStyleButtonST()
{
	// No theme helper
	m_pTheme = NULL;
}

CXPStyleButtonST::~CXPStyleButtonST()
{
}

// This function is called every time the button border needs to be painted.
// If the button is in standard (not flat) mode this function will NOT be called.
// This is a virtual function that can be rewritten in CButtonST-derived classes
// to produce a whole range of buttons not available by default.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CXPStyleButtonST::OnDrawBorder(CDC* pDC, LPCRECT pRect)
{
	if (m_pTheme == NULL || m_pTheme->IsAppThemed() == FALSE)
	{
		return CButtonST::OnDrawBorder(pDC, pRect);
	} // if

	return BTNST_OK;
} // End of OnDrawBorder

// This function is called every time the button background needs to be painted.
// If the button is in transparent mode this function will NOT be called.
// This is a virtual function that can be rewritten in CButtonST-derived classes
// to produce a whole range of buttons not available by default.
//
// Parameters:
//		[IN]	pDC
//				Pointer to a CDC object that indicates the device context.
//		[IN]	pRect
//				Pointer to a CRect object that indicates the bounds of the
//				area to be painted.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
DWORD CXPStyleButtonST::OnDrawBackground(CDC* pDC, LPCRECT pRect)
{
	BOOL	bDefaultDraw = FALSE;

	// No theme helper passed
	if (m_pTheme == NULL || m_pTheme->IsAppThemed() == FALSE)
	{
		bDefaultDraw = TRUE;
	} // if
	else
	{
		HTHEME	hTheme = NULL;
		int		iStateId = 0;

		hTheme = m_pTheme->OpenThemeData(GetSafeHwnd(), L"BUTTON");
		if (hTheme)
		{
			iStateId = PBS_NORMAL;								// Normal
			if (m_bIsDefault)		iStateId = PBS_DEFAULTED;	// Default button
			if (m_bMouseOnButton)	iStateId = PBS_HOT;			// Hot
			if (m_bIsPressed)		iStateId = PBS_PRESSED;		// Pressed
			if (m_bIsDisabled)		iStateId = PBS_DISABLED;	// Disabled

			m_pTheme->DrawThemeBackground(hTheme, pDC->GetSafeHdc(), BP_PUSHBUTTON, iStateId, pRect, NULL);
			m_pTheme->CloseThemeData(hTheme);
		} // if
		else
		{
			bDefaultDraw = TRUE;
		} // else
	} // else

	if (bDefaultDraw)
	{
		return CButtonST::OnDrawBackground(pDC, pRect);
	} // if

	return BTNST_OK;
} // End of OnDrawBackground

void CXPStyleButtonST::SetThemeHelper(CThemeHelperST* pTheme)
{
	m_pTheme = pTheme;
} // End of SetThemeHelper

#ifdef	NO_THEMEAPI_FOUND
#undef	NO_THEMEAPI_FOUND
#undef	BP_PUSHBUTTON
#undef	PBS_NORMAL
#undef	PBS_HOT
#undef	PBS_PRESSED
#undef	PBS_DISABLED
#undef	PBS_DEFAULTED
#endif