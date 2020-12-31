// BorderPickerCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "BorderPickerCtrl.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COLORREF CBorderPickerCtrl::m_defaultBorderStyles[] = 
{
    { ID_BORDER_OUTSIDE },
    { ID_BORDER_TOP },
    { ID_BORDER_BOTTOM },
    { ID_BORDER_LEFT },
    { ID_BORDER_RIGHT },
    { ID_BORDER_ALL },
    { ID_BORDER_INSIDE },
    { ID_BORDER_HORZ_INSIDE },
    { ID_BORDER_VERT_INSIDE },
    { ID_BORDER_NONE }
};

ButtonToolTipIDTable CBorderPickerCtrl::m_defaultArrToolTipText[] = 
{
    { ID_BORDER_OUTSIDE,		IDS_OUTBORDERS	    }, //"Outside Borders"
    { ID_BORDER_TOP,		    IDS_TOPBORDER		}, //"Top Border"
    { ID_BORDER_BOTTOM,		    IDS_BOTTOMBORDER	}, //"Bottom Border"
    { ID_BORDER_LEFT,			IDS_LEFTBORDER      }, //"Left Border"
    { ID_BORDER_RIGHT,		    IDS_RIGHTBORDER     }, //"Right Border"
    { ID_BORDER_ALL,		    IDS_ALLBORDERS      }, //"All Borders"
    { ID_BORDER_INSIDE,			IDS_INSIDEBORDERS   }, //"Inside Borders"
    { ID_BORDER_HORZ_INSIDE,	IDS_HINSIDE			}, //"Horizontal Inside"
    { ID_BORDER_VERT_INSIDE,	IDS_VINSIDE			}, //"Vertical Inside"
    { ID_BORDER_NONE,			IDS_NOBORDERS       } //"No Borders"
};

/////////////////////////////////////////////////////////////////////////////
// CBorderPickerCtrl

CBorderPickerCtrl::CBorderPickerCtrl(UINT nButtons, UINT nRows, DWORD dwDefault,
									 CSize sizeButton, int nIDDefault,
									 int nIDCustom):
	COXPopupBarCtrl(nButtons, nRows, dwDefault, sizeButton, nIDDefault, 
		nIDCustom)
{

}

BEGIN_MESSAGE_MAP(CBorderPickerCtrl, COXPopupBarCtrl)
	//{{AFX_MSG_MAP(CBorderPickerCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CBorderPickerCtrl::Pick(UINT nAlignment, CRect* pParentRect, CSize sizeOffset)
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
		if(!SetButtonDataTable(m_defaultBorderStyles,BORDERPICK_DEFINEDSTYLES))
		{
			return FALSE;
		}
	}
	ASSERT(m_arrData.GetSize()>=(int)m_nButtons);


	// nobody has cared to fill array of tooltip text 
	// then we'll do that using default table
	if(m_arrToolTipText.GetCount()==0)
	{
		if(!SetToolTipTextIDTable(m_defaultArrToolTipText,BORDERPICK_DEFINEDSTYLES))
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
// CBorderPickerCtrl message handlers

// draw button
void CBorderPickerCtrl::DrawButton(CDC* pDC, UINT nIndex)
{
	ASSERT(m_nButtons>0 && m_nButtons<=ID_POPUPBAR_MAX_BUTTONS);
	ASSERT((int)m_nButtons==m_arrButtonRect.GetSize());
	ASSERT((int)m_nButtons<=m_arrData.GetSize());
	ASSERT(nIndex<=m_nButtons);

	ASSERT(m_ilStyles.GetImageCount()>(int)nIndex);
	
	COLORREF clrShadow=::GetSysColor(COLOR_BTNSHADOW);
	CRect rect=m_arrButtonRect[nIndex];

	DrawFrameRect(pDC,rect,nIndex+1);

	CBrush brushFrame(clrShadow);
	rect.DeflateRect(0,1);
	m_ilStyles.Draw(pDC,nIndex,rect.TopLeft(),ILD_TRANSPARENT);
}


int CBorderPickerCtrl::FindImageIndexFromStyle(DWORD dwStyle)
{
	for(int nIndex=0; nIndex<BORDERPICK_DEFINEDSTYLES; nIndex++)
	{
		if(dwStyle==m_defaultBorderStyles[nIndex])
		{
			return nIndex;
		}
	}

	return -1;
}
