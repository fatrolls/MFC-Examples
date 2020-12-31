#include "stdafx.h"
#include "GDI.h"
#include "Percent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPercent::CPercent()
{
	m_nRange=100;
	m_nCurPos=0;
}

CPercent::~CPercent()
{
}


BEGIN_MESSAGE_MAP(CPercent, CStatic)
	//{{AFX_MSG_MAP(CPercent)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPercent::OnPaint() 
{
	CPaintDC dc(this);
	CRect rect;
	CRect rectHalf;
	CString szStr;
	CSize sizeExtent;
	COLORREF colorTextOld;
	COLORREF colorBkOld;
	
	if(m_nRange != 0)
	{
		GetClientRect(rect);
		szStr.Format("%d%%", m_nCurPos*100/m_nRange);
		colorTextOld=dc.SetTextColor(RGB(255, 255, 255));
		colorBkOld=dc.SetBkColor(RGB(0, 0, 255));
		sizeExtent=dc.GetTextExtent(szStr);
		rectHalf=rect;
		rectHalf.right=rect.Width()*m_nCurPos/m_nRange;
		dc.ExtTextOut
		(
			(rect.Width()-sizeExtent.cx)/2,
			(rect.Height()-sizeExtent.cy)/2,
			ETO_OPAQUE|ETO_CLIPPED,
			rectHalf,
			szStr,
			NULL
		);
		rectHalf.left=rectHalf.right+1;
		rectHalf.right=rect.right;
		dc.SetTextColor(RGB(0, 0, 255));
		dc.SetBkColor(RGB(255, 255, 255));
		dc.ExtTextOut
		(
			(rect.Width()-sizeExtent.cx)/2,
			(rect.Height()-sizeExtent.cy)/2,
			ETO_OPAQUE|ETO_CLIPPED,
			rectHalf,
			szStr,
			NULL
		);
		dc.SetTextColor(colorTextOld);
		dc.SetBkColor(colorBkOld);
   	}
}
