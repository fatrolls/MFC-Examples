#include "stdafx.h"
#include "PopUpScrollList.h"
#include "CellComboBox.h"
#include "..\utilities.h"
#include "..\ConfigListCtrl.h"

#define DEFAULT_DISPLAYED_ROWS				6
#define DEFAULT_DISPLAYED_ITEM				0

DWORD CCellComboBox::m_dwComboStyle = CLCS_ACTIVE_FRM_NORMAL | CLCS_INACTIVE_FRM_NORMAL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCellComboBox::CCellComboBox() : CCellDropDown(),
					 m_lDisplayedRows(DEFAULT_DISPLAYED_ROWS),
					 m_lSelectedItem(DEFAULT_DISPLAYED_ITEM)
{
	m_pPopUpWnd = new CPopUpScrollList;
	m_eDropDownType = WDDT_ClickAnyWhere;
}

CCellComboBox::~CCellComboBox()
{
	delete m_pPopUpWnd;
	m_pPopUpWnd = NULL;
}

void CCellComboBox::Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText)
{
	CCellCtrl::Initialize(hParentWnd, pParentEnabled, strText);

	CString str = strText;
	int iPosBegin = 0, iPosEnd = 0;

	do
	{
		iPosEnd = str.Find(_T('\n'), iPosBegin);

		if (iPosEnd != -1)
			m_astrItems.Add(str.Mid(iPosBegin, iPosEnd - iPosBegin));
		else
			m_astrItems.Add(str.Mid(iPosBegin));
			
		iPosBegin = iPosEnd + 1;
	}
	while (iPosEnd != -1);

	ASSERT(m_lSelectedItem < m_astrItems.GetSize());
	
	CString strSelectItem = m_astrItems.GetAt(0),
			strItem;

	int iPos;
	m_lSelectedItem = -1;

	if (m_astrItems.GetSize() > 1)
	{
		for (iPos = 1; iPos < m_astrItems.GetSize(); iPos++)
		{
			if (!m_astrItems.GetAt(iPos).CompareNoCase(strSelectItem))
			{
				m_lSelectedItem = iPos;
				break;
			}
		}
		if (m_lSelectedItem != -1)
		{
			m_astrItems.RemoveAt(0);
			m_lSelectedItem--;
		}
	}
	m_strText = (m_lSelectedItem != -1)? m_astrItems[m_lSelectedItem] : _T("");

	((CPopUpScrollList *)m_pPopUpWnd)->Create(m_hParentWnd, this);
}

void CCellComboBox::DrawItem(CDC *pDC, const LPRECT prcItem, const CString &strLabel, BOOL bSelected /*= FALSE*/, BOOL bDisabled /*= FALSE*/)
{
	pDC->SetTextColor(GetSysColor(bDisabled? COLOR_GRAYTEXT : bSelected? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
	pDC->DrawText(strLabel, prcItem, GetAlignDrawFlag() | DT_BOTTOM | DT_END_ELLIPSIS);
}

void CCellComboBox::DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState /*= 0*/)
{
	CBrush			Brush;
	RECT			rcTxt;
	BOOL			bHighlighted = FALSE;
	int				iSavedDC;

	iSavedDC = pDC->SaveDC();

	Brush.CreateSolidBrush(GetSysColor(IsDisabled()? COLOR_BTNFACE : COLOR_WINDOW));

	pDC->FillRect(prcCell, &Brush);

	BOOL bThemeDrawn = DrawThemeCombobox(pDC->m_hDC, prcCell);

  	if ((uiItemState & (ODS_FOCUS | ODS_SELECTED) && !m_bActive && !IsDisabled()) || (bThemeDrawn && IsDisabled()))
	{
		CBrush	HighlightBrush;
		CRect	rcHighlight;	
		HighlightBrush.CreateSolidBrush(GetSysColor(IsDisabled()? COLOR_BTNFACE : COLOR_HIGHLIGHT));

		CopyRect(&rcHighlight, prcCell);
		InflateRect(&rcHighlight, -::GetSystemMetrics(SM_CXFIXEDFRAME), -::GetSystemMetrics(SM_CYFIXEDFRAME)); 
	
		if (prcCell->right - prcCell->left > GetMinLegalWidth())
			rcHighlight.right -= ::GetSystemMetrics(SM_CXVSCROLL);

		if (rcHighlight.right > rcHighlight.left)
			pDC->FillRect(&rcHighlight, &HighlightBrush);

		HighlightBrush.DeleteObject();

		bHighlighted = TRUE;
	}
	CopyRect(&rcTxt, prcCell);

	InflateRect(&rcTxt, -::GetSystemMetrics(SM_CXFIXEDFRAME), -::GetSystemMetrics(SM_CYFIXEDFRAME));
	rcTxt.right -= ::GetSystemMetrics(SM_CXVSCROLL);

	SelectFont(pDC);
	DrawItem(pDC, &rcTxt, m_strText, bHighlighted, IsDisabled());

	if (!bThemeDrawn)
	{
		CCellDropDown::DrawCtrl(pDC, prcCell, uiItemState);
		m_bPumpActionButtonEffect = TRUE;
	}
	Brush.DeleteObject();
	pDC->RestoreDC(iSavedDC);
}

int CCellComboBox::GetMinWidth()
{
	CString				strText;
	CSize				szSize;
	int					iMinWidth = 0; 

	CDC *pDC = GetWindowFromHandle()->GetDC();

	if (pDC)
	{
		SelectFont(pDC);

		strText = m_strText + _T("i"); // Text is not neatly aligned on left hand side. 
		szSize = pDC->GetTextExtent(strText);
		iMinWidth = szSize.cx + CCellDropDown::GetMinWidth(); 
	}
	return iMinWidth;
}

void CCellComboBox::OnOpenDropDown()
{
	((CPopUpScrollList *)m_pPopUpWnd)->OnOpenDropDown();
}

void CCellComboBox::GetDropDownBoundingRect(RECT &rc, BOOL downwards /*= TRUE*/)
{
	CWnd *pWnd = GetWindowFromHandle();
	CDC *pDC = pWnd->GetDC();

	CopyRect(&rc, &m_rcBounding);

	if (downwards)
	{
		rc.top = rc.bottom;

		if (!m_astrItems.GetSize())
			rc.bottom += EMPTY_BOX_HEIGHT;
		else
		{		
			CSize sz= pDC->GetTextExtent(CString(_T("M")));
			rc.bottom += sz.cy * min(m_lDisplayedRows, m_astrItems.GetSize());
			rc.bottom += 2 * ::GetSystemMetrics(SM_CYBORDER);
		}
	}
	else
	{
		rc.bottom = rc.top;
		
		if (!m_astrItems.GetSize())
			rc.top -= EMPTY_BOX_HEIGHT;
		else
		{
			CSize sz= pDC->GetTextExtent(CString(_T("M")));
			rc.top -= sz.cy * min(m_lDisplayedRows, m_astrItems.GetSize());
			rc.top -= 2 * ::GetSystemMetrics(SM_CYBORDER);
		}
	}
}
void CCellComboBox::OnSelCloseDropDown(LPARAM lParam)
{
	m_lSelectedItem = lParam;
	m_strText = m_astrItems[m_lSelectedItem];
}

BOOL CCellComboBox::OnMouseMove(UINT nFlags, CPoint point)
{
	ActivatePushButton(point);
	return CCellButton::OnMouseMove(nFlags, point);
}

BOOL CCellComboBox::InsertItem(int Idx, LPCTSTR strText)
{
	if (Idx < 0 || Idx > m_astrItems.GetSize())
		return FALSE;

	m_astrItems.InsertAt(Idx, strText);
	((CPopUpScrollList *)m_pPopUpWnd)->ResetScrollInfo();

	return TRUE;
}

BOOL CCellComboBox::SetSelectedItem(LONG lSelectedItem)
{
	if (lSelectedItem < 0 || lSelectedItem >= m_astrItems.GetSize())
		return FALSE;

	m_lSelectedItem = lSelectedItem;
	m_strText = m_astrItems[m_lSelectedItem]; 
	CalculateTextAreaRect();
	GetWindowFromHandle()->InvalidateRect(FALSE);

	((CConfigListCtrl*)GetWindowFromHandle())->SetItemValueFromCtrl(this, m_strText);

	return TRUE;
}

BOOL CCellComboBox::RemoveItem(int Idx)
{
	if (Idx < 0 || Idx >= m_astrItems.GetSize())
		return FALSE;

	if (m_lSelectedItem == Idx)
	{
		m_lSelectedItem = -1;
		m_strText = _T("");
		CalculateTextAreaRect();
		GetWindowFromHandle()->InvalidateRect(FALSE);
		((CConfigListCtrl*)GetWindowFromHandle())->SetItemValueFromCtrl(this, m_strText);
	}
	else if (m_lSelectedItem > Idx)
		m_lSelectedItem--;

	m_astrItems.RemoveAt(Idx);
	((CPopUpScrollList *)m_pPopUpWnd)->ResetScrollInfo();

	return TRUE;
}

void CCellComboBox::AddToCtrlTypeStyle(DWORD dwFlags)
{
	m_dwComboStyle |= dwFlags;
}

void CCellComboBox::RemoveFromCtrlTypeStyle(DWORD dwFlags)
{
	m_dwComboStyle &= ~dwFlags;
}

LONG CCellComboBox::GetStyle()
{
	return m_dwComboStyle | m_dwStyle;
}