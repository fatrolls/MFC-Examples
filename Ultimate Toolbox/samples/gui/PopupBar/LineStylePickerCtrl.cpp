// LineStylePickerCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "LineStylePickerCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COLORREF CLineStylePickerCtrl::m_defaultLineStyles[] = 
{
    { ID_LINE_1PX },
    { ID_LINE_2PX },
    { ID_LINE_3PX },
    { ID_LINE_4PX },
    { ID_LINE_6PX },
    { ID_LINE_3PX_2LINES },
    { ID_LINE_4PX_2LINES },
    { ID_LINE_4PX_2LINES_REVERSE },
    { ID_LINE_7PX_3LINES }
};

LPCTSTR CLineStylePickerCtrl::m_defaultArrToolTipText[] = 
{
    { _T("1 pix") },
    { _T("2 pix") },
    { _T("3 pix") },
    { _T("4 pix") },
    { _T("6 pix") },
    { _T("3 pix") },
    { _T("4 pix") },
    { _T("4 pix") },
    { _T("7 pix") },
};

/////////////////////////////////////////////////////////////////////////////
// CLineStylePickerCtrl

CLineStylePickerCtrl::CLineStylePickerCtrl(UINT nButtons, 
										   UINT nRows, 
										   DWORD dwDefault,
										   CSize sizeButton, 
										   int nIDDefault,
										   int nIDCustom):
	COXPopupBarCtrl(nButtons, nRows, dwDefault, sizeButton, nIDDefault, 
		nIDCustom)
{
	m_rectEdgeMargin=CRect(2,2,2,2);
}

BEGIN_MESSAGE_MAP(CLineStylePickerCtrl, COXPopupBarCtrl)
	//{{AFX_MSG_MAP(CLineStylePickerCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CLineStylePickerCtrl::Pick(UINT nAlignment, CRect* pParentRect, CSize sizeOffset)
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
		if(!SetButtonDataTable(m_defaultLineStyles,LINESTYLEPICK_DEFINEDSTYLES))
		{
			return FALSE;
		}
	}
	ASSERT(m_arrData.GetSize()>=(int)m_nButtons);


	// force next styles
	SetPopupBarStyle(POPUPBAR_NODEFAULT|POPUPBAR_NOCUSTOM|POPUPBAR_NOTEAROFF);

	return COXPopupBarCtrl::Pick(nAlignment,pParentRect,sizeOffset);
}

////////////////////////////////////
// Attributes

/////////////////////////////////////////////////////////////////////////////
// CLineStylePickerCtrl message handlers

// draw button
void CLineStylePickerCtrl::DrawButton(CDC* pDC, UINT nIndex)
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

	// draw text
	CRect rectText=rect;
	rectText.right=rectText.left+30;
	pDC->DrawText(m_defaultArrToolTipText[nIndex],5,rectText,
		DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	// draw lines
	rect.left+=30;
	rect.right-=2;
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	pDC->SelectObject(&pen);
	switch(nIndex)
	{
	case ID_LINE_1PX:
		{
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2);
			break;
		}
	case ID_LINE_2PX:
		{
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+1);
			break;
		}
	case ID_LINE_3PX:
		{
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2-1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2-1);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+1);
			break;
		}
	case ID_LINE_4PX:
		{
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2-1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2-1);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+1);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+2);
			break;
		}
	case ID_LINE_6PX:
		{
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2-2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2-2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2-1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2-1);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+1);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+3);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+3);
			break;
		}
	case ID_LINE_3PX_2LINES:
		{
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2-1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2-1);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+1);
			break;
		}
	case ID_LINE_4PX_2LINES:
		{
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2-1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2-1);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+1);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+2);
			break;
		}
	case ID_LINE_4PX_2LINES_REVERSE:
		{
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2-1);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2-1);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+2);
			break;
		}
	case ID_LINE_7PX_3LINES:
		{
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2-3);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2-3);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2-2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2-2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+2);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+2);
			pDC->MoveTo(rect.left,rect.top+rect.Height()/2+3);
			pDC->LineTo(rect.right,rect.top+rect.Height()/2+3);
			break;
		}
	default:
		ASSERT(FALSE);
	}

	if(nSaveDC)
		pDC->RestoreDC(nSaveDC);
}


