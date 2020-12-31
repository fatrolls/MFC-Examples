//
// popupcolorbar.cpp : implementation file
//

#include "stdafx.h"
#include "..\ConfigListCtrl.h"
#include "popupcolorbar.h"
#include "CellColorCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	HOR_MARGIN				6
#define VER_MARGIN				6
#define BUTTON_WIDTH			17
#define	BUTTON_HEIGHT			16
#define	HOR_ADJ_MARGIN			(HOR_MARGIN - 2)
#define VER_ADJ_MARGIN			(VER_MARGIN - 2)
#define EXTRA_HEIGHT			29

/////////////////////////////////////////////////////////////////////////////
// CPopupColorBar

CPopupColorBar::CPopupColorBar() : m_ColorColumns(1), m_ColorRows(1), m_HighlightColor(-1), m_SelColor(-1), m_ShowOtherButton(TRUE),
									m_HighlightOtherButton(FALSE), m_ShowOtherColor(FALSE), m_pToolTip(NULL)
{
	m_ColorInfo.Add(COLOR_INFO(0x00000000, _T("Black"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00000080, _T("Burgundy"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00008000, _T("Green"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00008080, _T("Olive"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00800000, _T("Navy Blue"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00800080, _T("Purple"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00808000, _T("Cyan"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00C0C0C0, _T("Silver"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00C0DCC0, _T("Sea Green"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00F0CAA6, _T("Sky Blue"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00F0FBFF, _T("Cream"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00A4A0A0, _T("Grey Green"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00808080, _T("Grey"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x000000FF, _T("Red"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x0000FF00, _T("Lime"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x0000FFFF, _T("Yellow"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00FF0000, _T("Blue"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00FF00FF, _T("Fuchsia"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00FFFF00, _T("Turquoise"), RECT()));
	m_ColorInfo.Add(COLOR_INFO(0x00FFFFFF, _T("White"), RECT()));

	ComputeDetails();
}

void CPopupColorBar::ComputeDetails()
{
	short NumColors = m_ColorInfo.GetCount();

	m_ColorRows = NumColors;

	while (m_ColorRows > m_ColorColumns)
	{
		m_ColorColumns++;
		m_ColorRows = NumColors/m_ColorColumns + ((NumColors%m_ColorColumns)? 1 : 0);
	}

	short ItemColumn = 0, ItemRow = 0, Pos;

	for (Pos = 0; Pos != m_ColorInfo.GetCount(); Pos++)
	{
		ItemColumn = Pos%m_ColorColumns; 
		ItemRow = Pos/m_ColorColumns;

		m_ColorInfo[Pos].m_Rect.left = ItemColumn*BUTTON_WIDTH + HOR_ADJ_MARGIN;
		m_ColorInfo[Pos].m_Rect.top = ItemRow*BUTTON_HEIGHT + VER_ADJ_MARGIN;
		m_ColorInfo[Pos].m_Rect.right = (ItemColumn+1)*BUTTON_WIDTH - 1 + HOR_ADJ_MARGIN;
		m_ColorInfo[Pos].m_Rect.bottom = (ItemRow+1)*BUTTON_HEIGHT - 1 + VER_ADJ_MARGIN;
	}

	if (m_ShowOtherButton)
	{
		m_RectOther.left = HOR_ADJ_MARGIN + 1;
		m_RectOther.top = VER_MARGIN + 2*VER_ADJ_MARGIN + m_ColorRows*BUTTON_HEIGHT;
		m_RectOther.right = HOR_ADJ_MARGIN - 3  + m_ColorColumns*BUTTON_WIDTH;
		m_RectOther.bottom = VER_MARGIN + 2*VER_ADJ_MARGIN + m_ColorRows*BUTTON_HEIGHT + 18;
	}
}

CPopupColorBar::~CPopupColorBar()
{
	delete m_pToolTip;
}

BEGIN_MESSAGE_MAP(CPopupColorBar, CWnd)
	//{{AFX_MSG_MAP(CPopupColorBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupColorBar message handlers

void CPopupColorBar::Create(HWND hParentWnd, CCellColorCtrl *pCellColorCtrl)
{
	CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW|CS_PARENTDC,
                                              0,
                                              (HBRUSH) (COLOR_BTNFACE+1), 
                                              0);
	const RECT rect = {0,0,0,0};

	m_hMainCtrlWnd = hParentWnd;

	if (!CreateEx(0, szClassName, _T(""), WS_POPUP | WS_DLGFRAME, rect, FromHandle(hParentWnd)->GetParent(), 0, NULL))
		TRACE(_T("CPopupColorBar::Create : CreateEx failed!"));

	m_pToolTip = new CToolTipCtrl;

	if(!m_pToolTip->Create(this))
    {
		TRACE("Unable To create ToolTip\n");
		return;
	}
	int i = 135, pos;
	for (pos = 0; pos < m_ColorInfo.GetCount(); pos++)
		m_pToolTip->AddTool(this, m_ColorInfo[pos].m_Name, &m_ColorInfo[pos].m_Rect, ++i);
	
	m_pToolTip->AddTool(this, _T("Other"), &m_RectOther, ++i);

	m_pToolTip->Activate(TRUE);
}

BOOL CPopupColorBar::PreTranslateMessage(MSG* pMsg)
{
     m_pToolTip->RelayEvent(pMsg);
     return CListCtrlCellWnd::PreTranslateMessage(pMsg);
}

void CPopupColorBar::GetBoundingRect(const RECT &rcCellBounding, RECT &rcBounding, BOOL Downwards /*= TRUE*/)
{
	CSize sz = CSize((m_ColorColumns * BUTTON_WIDTH) + (2 * HOR_MARGIN), (m_ColorRows * BUTTON_HEIGHT) + (2 * VER_MARGIN) 
		+ (m_ShowOtherButton? EXTRA_HEIGHT : 0));

	if (Downwards)
	{
		rcBounding.top = rcCellBounding.bottom;
		rcBounding.bottom = rcCellBounding.bottom + sz.cy;
	}
	else
	{
		rcBounding.bottom = rcCellBounding.top;
		rcBounding.top = rcCellBounding.top - sz.cy;	
	}
	
	rcBounding.left = rcCellBounding.left;	
	rcBounding.right = rcCellBounding.left + sz.cx;
}

void CPopupColorBar::OnPaint() 
{
	CPaintDC			dc(this); // device context for painting
	RECT				rcBounding;

	GetClientRect(&rcBounding);

	CRect rectFirst(HOR_MARGIN, VER_MARGIN, HOR_MARGIN + BUTTON_WIDTH, VER_MARGIN + BUTTON_HEIGHT);

	PaintButtons(&dc);
}

void CPopupColorBar::PaintButton(CDC* pDC, CRect Rect, COLORREF ColorRef, LONG status)
{
	if (status)
	{
		CRect RectSel = Rect;
		RectSel.InflateRect(0,0,1,1); 
		if (status & FLAG_COLOR_SELECTED)
			pDC->Draw3dRect(RectSel, afxGlobalData.clrBarShadow, afxGlobalData.clrBarHilite);
		else if (status & FLAG_COLOR_HIGLIGHTED)
			pDC->Draw3dRect(Rect, afxGlobalData.clrBarHilite, afxGlobalData.clrBarShadow);
	}
	CBrush br = CBrush();
	br.CreateSolidBrush(ColorRef);
	CBrush* pOldBrush = pDC->SelectObject(&br);
	Rect.DeflateRect(2, 2);
	pDC->Rectangle(Rect);
	pDC->SelectObject(pOldBrush);
}

void CPopupColorBar::PaintButtons(CDC* pDC)
{
	ASSERT_VALID(pDC);
	ASSERT_VALID(this);

	CPen* pOldPen = (CPen*) pDC->SelectObject(&afxGlobalData.penBarShadow);

	int pos;
	for (pos = 0; pos < m_ColorInfo.GetCount(); pos++)
		PaintButton(pDC, m_ColorInfo[pos].m_Rect, m_ColorInfo[pos].m_ColorRef, m_ColorInfo[pos].m_StatusFlag);

	pDC->SelectObject(pOldPen);

	if (m_ShowOtherButton)
	{
		DrawSeparator(pDC);
		DrawOtherButton(pDC);
	}
}

void CPopupColorBar::DrawSeparator(CDC* pDC)
{
	CRect rectSeparator(HOR_ADJ_MARGIN - 1, VER_MARGIN + 2 + (m_ColorRows * BUTTON_HEIGHT), 
											HOR_ADJ_MARGIN + (m_ColorColumns * BUTTON_WIDTH) - 1, VER_MARGIN + 2 + (m_ColorRows * BUTTON_HEIGHT) + 2);

	pDC->Draw3dRect(rectSeparator, afxGlobalData.clrBtnShadow, afxGlobalData.clrBtnHilite);
}

void CPopupColorBar::DrawOtherButton(CDC* pDC)
{
	if (m_HighlightOtherButton)
		pDC->Draw3dRect(m_RectOther, afxGlobalData.clrBarHilite, afxGlobalData.clrBarShadow);

// Draw label:
	pDC->SetTextColor(afxGlobalData.clrBarText);

	int PrevBackMode = pDC->SetBkMode(TRANSPARENT);
		
	UINT nFormat = DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_CENTER;
	
	CFont* pCurrFont = pDC->SelectObject(&afxGlobalData.fontRegular);
	ENSURE(pCurrFont != NULL);
	
	pDC->DrawText(_T("Other"), &m_RectOther, nFormat);
	pDC->SelectObject(pCurrFont);

	pDC->SetBkMode(PrevBackMode);

	if (m_ShowOtherColor)
	{
		CPen* pOldPen = (CPen*) pDC->SelectObject(&afxGlobalData.penBarShadow);
		PaintButton(pDC, m_RectOtherColor, m_ActiveColor, FLAG_COLOR_SELECTED);
		pDC->SelectObject(pOldPen);
	}
}

short CPopupColorBar::GetColorButtonFromPt(const CPoint& point) 
{
	if (point.x < HOR_ADJ_MARGIN || point.y < VER_ADJ_MARGIN 
		|| point.x > (HOR_ADJ_MARGIN + m_ColorColumns*BUTTON_WIDTH - 1) 
		|| point.y > (VER_ADJ_MARGIN + m_ColorRows*BUTTON_HEIGHT - 1))
	{
		return -1; 
	}
	else
	{
		int Column = (point.x - HOR_ADJ_MARGIN)/BUTTON_WIDTH;
		int Row = (point.y - VER_ADJ_MARGIN)/BUTTON_HEIGHT;
		return Row*m_ColorColumns + Column;
	}
}

void CPopupColorBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	short OldHighlight = m_HighlightColor;

	m_HighlightColor = GetColorButtonFromPt(point);

	if (OldHighlight != m_HighlightColor)
	{
		if (OldHighlight >= 0)
		{
			m_ColorInfo[OldHighlight].m_StatusFlag &= ~FLAG_COLOR_HIGLIGHTED;
			InvalidateRect(&m_ColorInfo[OldHighlight].m_Rect, TRUE);
		}
		if (m_HighlightColor >= 0)
		{
			m_ColorInfo[m_HighlightColor].m_StatusFlag |= FLAG_COLOR_HIGLIGHTED;
			InvalidateRect(&m_ColorInfo[m_HighlightColor].m_Rect, TRUE);
		}
	}

	BOOL WasHighlighted = m_HighlightOtherButton;
	m_HighlightOtherButton = m_RectOther.PtInRect(point);

	if (WasHighlighted != m_HighlightOtherButton)
		InvalidateRect(&m_RectOther, TRUE);

	CWnd::OnMouseMove(nFlags, point);
}

void CPopupColorBar::OpenDropDown(const COLORREF ColorRef)
{
	BOOL PrevShowOtherColor = m_ShowOtherColor, Found = FALSE;
	m_ShowOtherColor = FALSE;
	m_ActiveColor = ColorRef;
	int pos;

	for (pos = 0; pos < m_ColorInfo.GetCount(); pos++)
	{
		if (ColorRef == m_ColorInfo[pos].m_ColorRef)
		{
			m_ColorInfo[pos].m_StatusFlag = FLAG_COLOR_SELECTED;
			Found = TRUE;
			m_SelColor = pos;
		}
		else
			m_ColorInfo[pos].m_StatusFlag =  0;
	}

	if (!Found && m_ShowOtherButton)
		m_ShowOtherColor = TRUE;

	m_HighlightOtherButton = FALSE;

	if (m_ShowOtherButton && (PrevShowOtherColor != m_ShowOtherColor))
	{
		if (m_ShowOtherColor)
		{
			m_RectOtherColor.CopyRect(&m_RectOther);
			m_RectOther.right -= BUTTON_WIDTH;
			m_RectOtherColor.left = m_RectOther.right;
			m_RectOtherColor.right += 3;
			m_RectOtherColor.DeflateRect(2, 1);
		}
		else
			m_RectOther.right += BUTTON_WIDTH;
	}
}

void CPopupColorBar::FireColor(COLORREF ColorRef) 
{
	CWnd *pWnd = FromHandle(m_hMainCtrlWnd);
	::SendMessage(pWnd->m_hWnd, WM_CELL_CTRL_MSG, ID_POPUP_SELCLOSE, ColorRef); 
	ReleaseCapture();
	ShowWindow(SW_HIDE);
}

void CPopupColorBar::DisplayColorDialog()
{
// CMFCColorDialog appears to show memory leaks. See:
// http://social.msdn.microsoft.com/Forums/en-US/vcgeneral/thread/c4346309-eb04-4067-974b-796503d68a89/
// http://jpassing.com/2008/09/01/effective-leak-detection-with-the-debug-crt-and-application-verifier/
	CMFCColorDialog dlg(m_ActiveColor, 0, this);
	// Alternative: (using the old type dialog)
	//CColorDialog dlg(m_ActiveColor, CC_FULLOPEN | CC_ANYCOLOR, this);
	if (dlg.DoModal() == IDOK)
		FireColor(dlg.GetColor()); 
}

void CPopupColorBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp(nFlags, point);

	short Pos = GetColorButtonFromPt(point); 

	if (Pos >= 0)
		FireColor(m_ColorInfo[Pos].m_ColorRef);

	if (m_ShowOtherButton)
	{
		if (m_RectOther.PtInRect(point))
			DisplayColorDialog();

		if (m_ShowOtherColor && m_RectOtherColor.PtInRect(point))
			FireColor(m_ActiveColor); 
	}
}

void CPopupColorBar::OnEnter()
{
	if (m_HighlightColor >= 0)
		FireColor(m_ColorInfo[m_HighlightColor].m_ColorRef);

	if (m_ShowOtherButton && m_HighlightOtherButton)
		DisplayColorDialog();
}

void CPopupColorBar::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bMoved = FALSE;

	if (nChar == VK_END || nChar == VK_HOME || nChar == VK_UP || nChar == VK_DOWN 
		|| nChar == VK_LEFT || nChar == VK_RIGHT)
	{
		if (m_HighlightColor >= 0)
		{
			m_ColorInfo[m_HighlightColor].m_StatusFlag &= ~FLAG_COLOR_HIGLIGHTED;
			InvalidateRect(&m_ColorInfo[m_HighlightColor].m_Rect, TRUE);
		}
		else
		{
			if (m_HighlightOtherButton)
			{
				m_HighlightOtherButton = FALSE;
				InvalidateRect(&m_RectOther, TRUE);
			}
			else if (!m_ShowOtherColor)
				m_HighlightColor = m_SelColor;
		}
		bMoved = TRUE;
	}
	switch (nChar)
	{
		case VK_END:
			m_HighlightColor = m_ColorInfo.GetCount() - 1;
		break;

		case VK_HOME:
			m_HighlightColor = 0;
		break;

		case VK_UP:
			if (m_HighlightColor >= m_ColorColumns)
				m_HighlightColor -= m_ColorColumns;
			else if (m_ShowOtherButton && m_HighlightColor == -1)
				m_HighlightColor = m_ColorInfo.GetCount() - m_ColorColumns;
		break;

		case VK_DOWN:
			if (m_HighlightColor != -1 && m_HighlightColor < m_ColorInfo.GetCount() - m_ColorColumns)
				m_HighlightColor += m_ColorColumns;
			else if (m_ShowOtherButton)
			{
				m_HighlightOtherButton = TRUE;
				m_HighlightColor = -1;
			}
		break;

		case VK_LEFT:
			if (m_HighlightColor % m_ColorColumns)
				--m_HighlightColor;
		break;

		case VK_RIGHT:
			if ((m_HighlightColor + 1) % m_ColorColumns)
				++m_HighlightColor;
		break;
	}

	if (bMoved)
	{
		if (m_HighlightColor != -1)
		{
			m_ColorInfo[m_HighlightColor].m_StatusFlag |= FLAG_COLOR_HIGLIGHTED;
			InvalidateRect(&m_ColorInfo[m_HighlightColor].m_Rect, TRUE);
		}
		else if (m_HighlightOtherButton)
			InvalidateRect(&m_RectOther, TRUE);
	}
	CListCtrlCellWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}