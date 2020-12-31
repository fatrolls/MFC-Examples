// ChartCtrl.cpp : Implementation of CChartCtrl
#include "stdafx.h"
#include "ChartCtrl.h"
#include "ChartDlg.h"

#ifndef _WIN32_WCE
#pragma comment(lib, "comctl32.lib")
#else
#pragma comment(lib, "commctrl.lib")
#endif


// CChartCtrl
VOID CChartCtrl::ChangeBrushStyleValue(BrushStyle NewStyleValue, int type)
{
	if(type == 1)
	{	  
		switch(NewStyleValue)
 		{
   			case B_SOLID:
  				m_ChartDlg.m_ChartFillStyle_1 = BS_SOLID; 
				break;
  			case B_EMPTY:
  				m_ChartDlg.m_ChartFillStyle_1 = BS_NULL; 
				break;
   			case B_HOLLOW:
 				m_ChartDlg.m_ChartFillStyle_1 = BS_HOLLOW; 
				break;
   			case B_HATCHED:
				m_ChartDlg.m_ChartFillStyle_1 = BS_HATCHED; 
				break;
  			case B_PATTERN:
				m_ChartDlg.m_ChartFillStyle_1 = BS_PATTERN; 
				break;
			case B_INDEXED:
				m_ChartDlg.m_ChartFillStyle_1 = BS_INDEXED; 
				break;
			case B_DIBPATTERN:
				m_ChartDlg.m_ChartFillStyle_1 = BS_DIBPATTERN;
				break;
			case B_DIBPATTERNPT:
				m_ChartDlg.m_ChartFillStyle_1 = BS_DIBPATTERNPT;
				break;
			case B_PATTERN8X8:
				m_ChartDlg.m_ChartFillStyle_1 = BS_PATTERN8X8;
				break;
			case B_DIBPATTERN8X8:
				m_ChartDlg.m_ChartFillStyle_1 = BS_DIBPATTERN8X8;
				break;
			case B_MONOPATTERN:
				m_ChartDlg.m_ChartFillStyle_1 = BS_MONOPATTERN;
				break;
		}
	}
	else if(type == 2)
		switch(NewStyleValue)
		{
   			case B_SOLID:
  				m_ChartDlg.m_ChartFillStyle_2 = BS_SOLID; 
				break;
  			case B_EMPTY:
  				m_ChartDlg.m_ChartFillStyle_2 = BS_NULL; 
				break;
   			case B_HATCHED:
				m_ChartDlg.m_ChartFillStyle_2 = BS_HATCHED; 
				break;
  			case B_PATTERN:
				m_ChartDlg.m_ChartFillStyle_2 = BS_PATTERN; 
			case B_INDEXED:
				m_ChartDlg.m_ChartFillStyle_2 = BS_INDEXED; 
			case B_DIBPATTERN:
				m_ChartDlg.m_ChartFillStyle_2 = BS_DIBPATTERN;
			case B_DIBPATTERNPT:
				m_ChartDlg.m_ChartFillStyle_2 = BS_DIBPATTERNPT;
			case B_PATTERN8X8:
				m_ChartDlg.m_ChartFillStyle_2 = BS_PATTERN8X8;
			case B_DIBPATTERN8X8:
				m_ChartDlg.m_ChartFillStyle_2 = BS_DIBPATTERN8X8;
			case B_MONOPATTERN:
				m_ChartDlg.m_ChartFillStyle_2 = BS_MONOPATTERN;
   			case B_HOLLOW:
 				m_ChartDlg.m_ChartFillStyle_2 = BS_HOLLOW; 
				break;
		}
}
VOID CChartCtrl::ChangeStyleValue(PenStyle NewStyleValue, int type)
{
	if(type == 1)
	{
  		switch(NewStyleValue)
   		{
  			case L_SOLID:
				m_ChartDlg.m_VLineStyle = PS_SOLID; 
				break;
 			case L_DASH:
   				m_ChartDlg.m_VLineStyle = PS_DASH; 
				break;
			case L_DOT:
  				m_ChartDlg.m_VLineStyle = PS_DOT; 
				break;
  			case L_DASHDOT:
				m_ChartDlg.m_VLineStyle = PS_DASHDOT; 
				break;
			case L_DASHDOTDOT:
				m_ChartDlg.m_VLineStyle = PS_DASHDOTDOT; 
				break;
			case L_EMPTY:
				m_ChartDlg.m_VLineStyle = PS_NULL; 
				break;
			case L_INSIDEFRAME:
				m_ChartDlg.m_VLineStyle = PS_INSIDEFRAME;
				break;
			case L_USERSTYLE:
				m_ChartDlg.m_VLineStyle = PS_USERSTYLE;
				break;
		}
	}
	else if(type == 2)
		switch(NewStyleValue)
		{
  			case L_SOLID:
				m_ChartDlg.m_HLineStyle = PS_SOLID; 
				break;
 			case L_DASH:
   				m_ChartDlg.m_HLineStyle = PS_DASH; 
				break;
			case L_DOT:
  				m_ChartDlg.m_HLineStyle = PS_DOT; 
				break;
  			case L_DASHDOT:
				m_ChartDlg.m_HLineStyle = PS_DASHDOT; 
				break;
			case L_DASHDOTDOT:
				m_ChartDlg.m_HLineStyle = PS_DASHDOTDOT; 
				break;
			case L_EMPTY:
				m_ChartDlg.m_HLineStyle = PS_NULL; 
				break;
			case L_INSIDEFRAME:
				m_ChartDlg.m_HLineStyle = PS_INSIDEFRAME;
				break;
			case L_USERSTYLE:
				m_ChartDlg.m_HLineStyle = PS_USERSTYLE;
				break;

		}
}

STDMETHODIMP CChartCtrl::get_BackColor(OLE_COLOR* pVal)
{
	// TODO: Add your implementation code here
	*pVal = (COLORREF) m_ChartDlg.m_BackColor;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_BackColor(OLE_COLOR newVal)
{
	// TODO: Add your implementation code here
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_ChartDlg.m_BackColor = cr;

	return S_OK;
}

STDMETHODIMP CChartCtrl::get_VerticalLineStyle(PenStyle* pVal)
{
	// TODO: Add your implementation code here
	*pVal = V_LineStyle;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_VerticalLineStyle(PenStyle newVal)
{
	// TODO: Add your implementation code here
	V_LineStyle = newVal;

	ChangeStyleValue(V_LineStyle, 1);

	return S_OK;
}

STDMETHODIMP CChartCtrl::get_HorizontalLineStyle(PenStyle* pVal)
{
	// TODO: Add your implementation code here
	*pVal = H_LineStyle;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_HorizontalLineStyle(PenStyle newVal)
{
	// TODO: Add your implementation code here
	H_LineStyle = newVal;
	ChangeStyleValue(H_LineStyle, 2);

	return S_OK;
}
STDMETHODIMP CChartCtrl::get_VerticalLineColor(OLE_COLOR* pVal)
{
	// TODO: Add your implementation code here
	*pVal = (COLORREF) m_ChartDlg.m_VLineColor;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_VerticalLineColor(OLE_COLOR newVal)
{
	// TODO: Add your implementation code here
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_ChartDlg.m_VLineColor = cr;

	return S_OK;
}

STDMETHODIMP CChartCtrl::get_HorizontalLineColor(OLE_COLOR* pVal)
{
	// TODO: Add your implementation code here
	*pVal = (COLORREF) m_ChartDlg.m_HLineColor;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_HorizontalLineColor(OLE_COLOR newVal)
{
	// TODO: Add your implementation code here
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_ChartDlg.m_HLineColor = cr;

	return S_OK;
}

STDMETHODIMP CChartCtrl::get_ChartColor_1(OLE_COLOR* pVal)
{
	// TODO: Add your implementation code here
	*pVal = (COLORREF) m_ChartDlg.m_ChartColor_1;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_ChartColor_1(OLE_COLOR newVal)
{
	// TODO: Add your implementation code here
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_ChartDlg.m_ChartColor_1 = cr;

	return S_OK;
}

STDMETHODIMP CChartCtrl::get_ChartColor_2(OLE_COLOR* pVal)
{
	// TODO: Add your implementation code here
	*pVal = (COLORREF) m_ChartDlg.m_ChartColor_2;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_ChartColor_2(OLE_COLOR newVal)
{
	// TODO: Add your implementation code here
	COLORREF cr;
	int i = OleTranslateColor(newVal,
					NULL,
					&cr);
	if ( i == S_OK)
		m_ChartDlg.m_ChartColor_2 = cr;

	return S_OK;
}

STDMETHODIMP CChartCtrl::get_ChartFillStyle_1(BrushStyle* pVal)
{
	// TODO: Add your implementation code here
	*pVal = FillStyle_1;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_ChartFillStyle_1(BrushStyle newVal)
{
	// TODO: Add your implementation code here
	FillStyle_1 = newVal;
	ChangeBrushStyleValue(FillStyle_1, 1);

	return S_OK;
}

STDMETHODIMP CChartCtrl::get_ChartFillStyle_2(BrushStyle* pVal)
{
	// TODO: Add your implementation code here
	*pVal = FillStyle_2;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_ChartFillStyle_2(BrushStyle newVal)
{
	// TODO: Add your implementation code here
	FillStyle_2 = newVal;
	ChangeBrushStyleValue(FillStyle_2, 2);

	return S_OK;
}


STDMETHODIMP CChartCtrl::UpdateChart(USHORT ChartValue1, USHORT ChartValue2)
{
	m_ChartDlg.m_RxValue = 0;
	m_ChartDlg.m_TxValue = 0;

	if(ChartValue1 > 0)
		m_ChartDlg.m_RxValue = ChartValue1;
	if(ChartValue2 > 0)
		m_ChartDlg.m_TxValue = ChartValue2;

	return S_OK;
}

STDMETHODIMP CChartCtrl::get_RefreshSpeed(USHORT* pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_ChartDlg.m_ChartRefreshSpeed;

	return S_OK;
}

STDMETHODIMP CChartCtrl::put_RefreshSpeed(USHORT newVal)
{
	// TODO: Add your implementation code here
	m_ChartDlg.m_ChartRefreshSpeed = newVal;

	return S_OK;
}

HRESULT CChartCtrl::OnDraw(ATL_DRAWINFO& di)
{
	// TODO: Add your specialized code here and/or call the base class
	RECT& rc = *(RECT*)di.prcBounds;
	HRGN hRgnOld = NULL;

	if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
		hRgnOld = NULL;
	bool bSelectOldRgn = false;

	HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

	if (hRgnNew != NULL)
	{
		bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
	}

	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
	LPCTSTR pszText = _T("NRVS  Sundar :              Animated Chart");
		
	#ifndef _WIN32_WCE
		TextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			pszText,
			lstrlen(pszText));
	#else
		ExtTextOut(di.hdcDraw,
			(rc.left + rc.right) / 2,
			(rc.top + rc.bottom) / 2,
			ETO_OPAQUE,
			NULL,
			pszText,
			ATL::lstrlen(pszText),
			NULL);
	#endif
	if (bSelectOldRgn)
		SelectClipRgn(di.hdcDraw, hRgnOld);

	return __super::OnDraw(di);
}
