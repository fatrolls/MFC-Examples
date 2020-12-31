//---------------------------------------------------------------------------------------
//		ColorStatic.cpp
//
//		Contents:
//			A costum made control to display colorred text
//
//		Environment:
//			Microsoft Windows NT 4.0, Visual C++ 5.0
//
//		Revision 
#include "stdafx.h"
#include "ColorStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
// default contructor
//
CColorStatic::CColorStatic()
{
	m_Font = NULL;
	m_BackgroundColor = RGB(255, 255, 255);	// white color
	m_TextColor = RGB(0, 0, 0);				// black text
	m_brBackgroundBrush.CreateSolidBrush(m_BackgroundColor);
}

//
// contructor for dialog based static controls
//
BOOL CColorStatic::Attach(CWnd* pParent, UINT nID, CFont* font, COLORREF textcolor, COLORREF backgroundcolor)
{
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;

	m_Font = font;
	m_BackgroundColor = backgroundcolor;	
	m_TextColor = textcolor;

	m_brBackgroundBrush.DeleteObject();
	m_brBackgroundBrush.CreateSolidBrush(m_BackgroundColor);

	if (m_Font)
		SetFont(m_Font);

	return TRUE;
}

//
// Destructor
//
CColorStatic::~CColorStatic()
{
	m_brBackgroundBrush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//
// Change the text
//
void CColorStatic::SetText(CString text)
{
	SetWindowText(text);
}

//
// Set the background color of the static control
//
void CColorStatic::SetBkColor(COLORREF color)
{
	m_brBackgroundBrush.DeleteObject();
	m_brBackgroundBrush.CreateSolidBrush(color);
	m_BackgroundColor = color;
	Invalidate();
}

//
// Set the color of the text
//
void CColorStatic::SetTextColor(COLORREF color)
{
	m_TextColor = color;
	Invalidate();
}
   
//
// Respond to the WM_CTLCOLOR message which is called when the control need
// to be painted
//
HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_TextColor);
	pDC->SetBkColor(m_BackgroundColor);
	return (HBRUSH) m_brBackgroundBrush;
}
