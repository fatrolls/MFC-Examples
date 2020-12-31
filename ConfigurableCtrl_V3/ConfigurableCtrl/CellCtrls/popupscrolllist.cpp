//
// popupscrolllist.cpp : implementation file
//

#include "stdafx.h"
#include "..\ConfigListCtrl.h"
#include "popupscrolllist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopUpScrollList

CPopUpScrollList::CPopUpScrollList() : m_lFirstPos(0), m_lSelectedItem(0), m_bActivated(FALSE) 
{
}

CPopUpScrollList::~CPopUpScrollList()
{
}

BEGIN_MESSAGE_MAP(CPopUpScrollList, CListCtrlCellWnd)
	//{{AFX_MSG_MAP(CPopUpScrollList)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopUpScrollList message handlers
void CPopUpScrollList::ResetScrollInfo()
{
	SCROLLINFO si;
	si.cbSize = sizeof(si); 
	si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS | SIF_TRACKPOS; 
	si.nMin   = 0; 
	si.nMax   = m_pCellComboBox->m_astrItems.GetSize() - 1; 
	si.nPage  = m_pCellComboBox->m_lDisplayedRows; 
	si.nPos   = 0; 
	m_ScrollBar.SetScrollInfo(&si);  
}

void CPopUpScrollList::Create(HWND hParentWnd, CCellDropDown *pCellDropDown)
{
	CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|CS_HREDRAW|CS_VREDRAW|CS_PARENTDC,
                                              0,
                                              (HBRUSH) (COLOR_BTNFACE+1), 
                                              0);

	const RECT rect = {0,0,0,0};

	m_hMainCtrlWnd = hParentWnd;

	CreateEx(0, szClassName, _T(""), WS_POPUP, rect, FromHandle(hParentWnd)->GetParent(), 0, NULL);
	
	m_pCellComboBox = dynamic_cast<CCellComboBox *>(pCellDropDown);
	ASSERT(m_pCellComboBox);

	RECT					rcBounding;
	SetRectEmpty(&rcBounding);
	m_ScrollBar.Create(WS_CHILD | WS_VISIBLE | SBS_VERT | SBS_RIGHTALIGN, rcBounding, this , 0);

	ResetScrollInfo();
}

void CPopUpScrollList::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	RECT							rcBounding,
									rcTxt,
									rcTxt2;
	CBrush							Brush, BrushSelected, *pBrush;
	LOGBRUSH						LogBrush;
	
	GetClientRect(&rcBounding);
	
	LogBrush.lbStyle = BS_NULL;
	Brush.CreateBrushIndirect(&LogBrush);
	dc.SelectObject(Brush);

	CPen	Pen = CPen(PS_SOLID, 0, IsAppThemed()? RGB(0xAA, 0xAA, 0xAA) : RGB(0, 0, 0));
	dc.SelectObject(Pen);

	dc.Rectangle(&rcBounding);
	Pen.DeleteObject();
	
	Brush.DeleteObject();

	InflateRect(&rcBounding, -::GetSystemMetrics(SM_CXBORDER), -::GetSystemMetrics(SM_CYBORDER));

	if (ShowScrollBar())
	{
		m_ScrollBar.ShowWindow(SW_NORMAL);
		m_ScrollBar.SetWindowPos(NULL, rcBounding.right - ::GetSystemMetrics(SM_CXVSCROLL), rcBounding.top, ::GetSystemMetrics(SM_CXVSCROLL), rcBounding.bottom - rcBounding.top, SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	m_ScrollBar.ShowScrollBar(ShowScrollBar());

	CopyRect(&rcTxt, &rcBounding);

	CWnd *pParentWnd = this->GetParent();
	dc.SelectObject(pParentWnd->GetFont());

	LONG lItems = min(m_pCellComboBox->m_astrItems.GetSize(), m_pCellComboBox->m_lDisplayedRows);
	LONG lItemHeight = lItems? (rcBounding.bottom - rcBounding.top)/lItems : EMPTY_BOX_HEIGHT - 2 * ::GetSystemMetrics(SM_CYBORDER);

	rcTxt.bottom = rcTxt.top + lItemHeight; 

	dc.SetBkMode(TRANSPARENT);
	Brush.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	BrushSelected.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

// If has scroll only
	if (ShowScrollBar())
		rcTxt.right -= ::GetSystemMetrics(SM_CXVSCROLL);

	int iScrollPos = (m_ScrollBar)? m_ScrollBar.GetScrollPos() : 0;

	if (!lItems)
		dc.FillRect(&rcTxt, &Brush);
	
	for (LONG lPos = m_lFirstPos; lPos < m_lFirstPos+lItems; lPos++)
	{
		pBrush = (lPos == m_lSelectedItem)? &BrushSelected : &Brush;
		dc.FillRect(&rcTxt, pBrush);
		CopyRect(&rcTxt2, &rcTxt);
		InflateRect(&rcTxt2, -::GetSystemMetrics(SM_CXFIXEDFRAME), 0);
		rcTxt2.top += ::GetSystemMetrics(SM_CYBORDER);
		m_pCellComboBox->DrawItem(&dc, &rcTxt2, m_pCellComboBox->m_astrItems[lPos+iScrollPos], lPos == m_lSelectedItem);
		OffsetRect(&rcTxt, 0, lItemHeight);
	}
	Brush.DeleteObject();
	BrushSelected.DeleteObject();
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CPopUpScrollList::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SelectAndClose();
	CListCtrlCellWnd::OnLButtonDown(nFlags, point);
}

void CPopUpScrollList::SelectAndClose()
{
	CWnd *pWnd = FromHandle(m_hMainCtrlWnd);

	::SendMessage(pWnd->m_hWnd, WM_CELL_CTRL_MSG, ID_POPUP_SELCLOSE, m_lSelectedItem + m_ScrollBar.GetScrollPos()); 
	ReleaseCapture();

	ShowWindow(SW_HIDE);
}

void CPopUpScrollList::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CListCtrlCellWnd::OnLButtonUp(nFlags, point);
}

void CPopUpScrollList::OnMouseMove(UINT nFlags, CPoint point) 
{
	RECT rcTxt;
	BOOL bPtInRect = FALSE;

	m_pCellComboBox->ActivatePushButton(point);

	GetClientRect(&rcTxt);
	InflateRect(&rcTxt, -::GetSystemMetrics(SM_CXBORDER), -::GetSystemMetrics(SM_CYBORDER));

	if (m_ScrollBar)
		rcTxt.right -= ::GetSystemMetrics(SM_CXVSCROLL);

	LONG lItems = min(m_pCellComboBox->m_astrItems.GetSize(), m_pCellComboBox->m_lDisplayedRows);
	LONG lItemHeight = lItems? (rcTxt.bottom - rcTxt.top)/lItems : EMPTY_BOX_HEIGHT - 2 * ::GetSystemMetrics(SM_CYBORDER);
	rcTxt.bottom = rcTxt.top + lItemHeight;

	LONG lPos;
	for (lPos = m_lFirstPos; lPos < m_lFirstPos+lItems && !bPtInRect; lPos++)
	{
		bPtInRect = PtInRect(&rcTxt, point);
		OffsetRect(&rcTxt, 0, lItemHeight);
	}
	if (bPtInRect)
	{
		LONG lOldPos = m_lSelectedItem;
		m_lSelectedItem = --lPos;
		m_bActivated = TRUE;

		if (lOldPos != lPos)
		{
			GetClientRect(&rcTxt);
			InvalidateRect(&rcTxt, FALSE);
		}
	}
	CListCtrlCellWnd::OnMouseMove(nFlags, point);
}

void CPopUpScrollList::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	SCROLLINFO si;
	pScrollBar->GetScrollInfo(&si);
	int iOldPos = si.nPos;

	switch (nSBCode)
	{
		case SB_LINEUP:				// Value 0 - top scroll button pressed
			si.nPos--;
		break;

		case SB_LINEDOWN:			// Value 1 - bottom scroll button pressed
			si.nPos++;
		break;

		case SB_PAGEUP:				// Value 2 - position above central button pressed
			si.nPos -= m_pCellComboBox->m_lDisplayedRows;
		break;

		case SB_PAGEDOWN:			// Value 3 - position below central button pressed
			si.nPos += m_pCellComboBox->m_lDisplayedRows;
		break;

		case SB_THUMBTRACK:			// Value 5 - if press on central button, this called 1st time
			si.nPos = si.nTrackPos;
		break;

		case SB_THUMBPOSITION:		// Value 4 - ... this called second time.		
		break;

		case SB_ENDSCROLL:			// Value 8 - This always called after any of the other SB codes. 
		break;

		default:
			ASSERT(!_T("Unrecognised SB code."));
			// the nSBCode SB_TOP (=6) and SB_BOTTOM (=7) not dealt with. ASSERT should show if required.
	}
	pScrollBar->SetScrollInfo(&si); // There is boundary correcting code in SetScrollInfo - so need not bother doing it ourselves.
	pScrollBar->GetScrollInfo(&si); // ...but need to collect again the maybe corrected si.nPos for setting selected item.
	
	m_lSelectedItem += iOldPos - si.nPos;

	this->Invalidate(FALSE);
	CListCtrlCellWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CPopUpScrollList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	int nScrollPos = m_ScrollBar.GetScrollPos();

	if (zDelta > 0)// WHEEL_DELTA = 120. zDelta may be 240 for instance.
		nScrollPos--; 
	else if (zDelta < 0)
		nScrollPos++;
	else
		ASSERT(!_T("zDelta value not taken care of."));

	m_ScrollBar.SetScrollPos(nScrollPos);
	int nScrollPos2 = m_ScrollBar.GetScrollPos();

	if (nScrollPos == nScrollPos2)
		m_lSelectedItem += zDelta/WHEEL_DELTA;
	
	Invalidate(FALSE);
	return TRUE;
}

void CPopUpScrollList::OnOpenDropDown()
{
	m_lSelectedItem = m_pCellComboBox->m_lSelectedItem;
	
	if (m_lSelectedItem >= m_pCellComboBox->m_lDisplayedRows)
	{
		int nScrollPos = m_lSelectedItem - m_pCellComboBox->m_lDisplayedRows + 1;
		m_lSelectedItem -= nScrollPos;	
		m_ScrollBar.SetScrollPos(nScrollPos);
	}
	else
		m_ScrollBar.SetScrollPos(0);
}

void CPopUpScrollList::OnEnter()
{
	SelectAndClose();
}

void CPopUpScrollList::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bRetVal = TRUE;
	int nScrollPos = m_ScrollBar.GetScrollPos();

	switch (nChar)
	{
		case VK_PRIOR:
			if (m_lSelectedItem != 0)
				m_lSelectedItem = 0;
			else
				nScrollPos -= m_pCellComboBox->m_lDisplayedRows;
		break;

		case VK_NEXT:
			if (m_lSelectedItem < m_pCellComboBox->m_lDisplayedRows - 1)
				m_lSelectedItem = m_pCellComboBox->m_lDisplayedRows - 1;
			else
				nScrollPos += m_pCellComboBox->m_lDisplayedRows;
		break;

		case VK_END:
			nScrollPos = m_pCellComboBox->m_astrItems.GetSize() - m_pCellComboBox->m_lDisplayedRows;
		break;

		case VK_HOME:
			nScrollPos = 0;
		break;

		case VK_UP:
			(m_lSelectedItem)? m_lSelectedItem-- : nScrollPos--;
		break;

		case VK_DOWN:
			if (m_lSelectedItem < m_pCellComboBox->m_lDisplayedRows - 1)
				m_lSelectedItem++;
			else
				nScrollPos++;
		break;
	}
	m_ScrollBar.SetScrollPos(nScrollPos);
	Invalidate(TRUE);

	CListCtrlCellWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}