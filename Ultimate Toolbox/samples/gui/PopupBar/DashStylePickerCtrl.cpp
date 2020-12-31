// DashStylePickerCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DashStylePickerCtrl.h"
#include "Resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_DASH_SOLID				0
#define ID_DASH_DASH				1
#define ID_DASH_DOT					2
#define ID_DASH_DASHDOT				3
#define ID_DASH_DASHDOTDOT			4
COLORREF CDashStylePickerCtrl::m_defaultDashStyles[] = 
{
    { ID_DASH_SOLID },
    { ID_DASH_DASH },
    { ID_DASH_DOT },
    { ID_DASH_DASHDOT },
    { ID_DASH_DASHDOTDOT }
};

ButtonToolTipIDTable CDashStylePickerCtrl::m_defaultArrToolTipText[] = 
{
    { ID_DASH_SOLID,		IDS_SOLID			}, //"Solid"
    { ID_DASH_DASH,		    IDS_DASH			}, //"Dash"
    { ID_DASH_DOT,		    IDS_DOT				}, //"Dot"
    { ID_DASH_DASHDOT,		IDS_DASHDOT			}, //"Dash Dot"
    { ID_DASH_DASHDOTDOT,	IDS_DASHDOTDOT		}  //"Dash Dot Dot"
};

/////////////////////////////////////////////////////////////////////////////
// CDashStylePickerCtrl

CDashStylePickerCtrl::CDashStylePickerCtrl(UINT nButtons, UINT nRows, DWORD dwDefault,
									 CSize sizeButton, int nIDDefault,
									 int nIDCustom):
	COXPopupBarCtrl(nButtons, nRows, dwDefault, sizeButton, nIDDefault, 
		nIDCustom)
{

}

BEGIN_MESSAGE_MAP(CDashStylePickerCtrl, COXPopupBarCtrl)
	//{{AFX_MSG_MAP(CDashStylePickerCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CDashStylePickerCtrl::Pick(UINT nAlignment, CRect* pParentRect, CSize sizeOffset)
{
	ASSERT_VALID(m_pParentWnd);
    ASSERT(::IsWindow(m_pParentWnd->GetSafeHwnd()));
	ASSERT(::IsWindow(m_hWnd));

	ASSERT(m_nButtons<=ID_POPUPBAR_MAX_BUTTONS && m_nButtons>0);
	ASSERT(m_nRows<=ID_POPUPBAR_MAX_BUTTONS && m_nRows>0 && m_nRows<=m_nButtons);

	// nobody has cared to fill array of colors
	// then we'll do that using predefined array
	if(m_arrData.GetSize()==0)
	{
		if(!SetButtonDataTable(m_defaultDashStyles,DASHSTYLEPICK_DEFINEDSTYLES))
		{
			return FALSE;
		}
	}
	ASSERT(m_arrData.GetSize()>=(int)m_nButtons);


	// nobody has cared to fill array of tooltip text 
	// then we'll do that using default table
	if(m_arrToolTipText.GetCount()==0)
	{
		if(!SetToolTipTextIDTable(m_defaultArrToolTipText,DASHSTYLEPICK_DEFINEDSTYLES))
		{
			return FALSE;
		}
	}

	// force next styles
	SetPopupBarStyle(POPUPBAR_NODEFAULT|POPUPBAR_NOCUSTOM|POPUPBAR_NOTEAROFF);

	return COXPopupBarCtrl::Pick(nAlignment,pParentRect,sizeOffset);
}

////////////////////////////////////
// Attributes

/////////////////////////////////////////////////////////////////////////////
// CDashStylePickerCtrl message handlers

// draw button
void CDashStylePickerCtrl::DrawButton(CDC* pDC, UINT nIndex)
{
	ASSERT(m_nButtons>0 && m_nButtons<=ID_POPUPBAR_MAX_BUTTONS);
	ASSERT((int)m_nButtons==m_arrButtonRect.GetSize());
	ASSERT((int)m_nButtons<=m_arrData.GetSize());
	ASSERT(nIndex<=m_nButtons);

	CRect rect=m_arrButtonRect[nIndex];

	DrawFrameRect(pDC,rect,nIndex+1);

	rect.DeflateRect(1,1);

	int nSaveDC=pDC->SaveDC();

	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(GetTextFont());

	// draw lines
	rect.DeflateRect(2,0);

	CPen pen;
	switch(nIndex)
	{
	case ID_DASH_SOLID:
		{
			VERIFY(pen.CreatePen(PS_SOLID,1,RGB(0,0,0)));
			break;
		}
	case ID_DASH_DASH:
		{
			VERIFY(pen.CreatePen(PS_DASH,1,RGB(0,0,0)));
			break;
		}
	case ID_DASH_DOT:
		{
			VERIFY(pen.CreatePen(PS_DOT,1,RGB(0,0,0)));
			break;
		}
	case ID_DASH_DASHDOT:
		{
			VERIFY(pen.CreatePen(PS_DASHDOT,1,RGB(0,0,0)));
			break;
		}
	case ID_DASH_DASHDOTDOT:
		{
			VERIFY(pen.CreatePen(PS_DASHDOTDOT,1,RGB(0,0,0)));
			break;
		}
	default:
		ASSERT(FALSE);
	}

	pDC->SelectObject(&pen);
	
	pDC->MoveTo(rect.left,rect.top+rect.Height()/2-1);
	pDC->LineTo(rect.right,rect.top+rect.Height()/2-1);
	pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
	pDC->LineTo(rect.right,rect.top+rect.Height()/2);
	pDC->MoveTo(rect.left,rect.top+rect.Height()/2+1);
	pDC->LineTo(rect.right,rect.top+rect.Height()/2+1);

	if(nSaveDC)
		pDC->RestoreDC(nSaveDC);
}


