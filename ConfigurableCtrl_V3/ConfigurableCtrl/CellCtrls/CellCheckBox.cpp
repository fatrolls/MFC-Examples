#include "stdafx.h"
#include "..\resource.h"
#include "CellCheckBox.h"
#include "..\utilities.h"

#define IMAGE_SIZE			20
#define BOX_SEP				3

CImageList CCellCheckBox::m_CheckBoxImageList;
DWORD CCellCheckBox::m_dwCheckBoxStyle = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCellCheckBox::CCellCheckBox() : CCellButton()
{
	m_dwStyle = CLCS_ALIGN_CENTER;
	::ZeroMemory(&m_rcArea, sizeof(RECT)); 
}

CCellCheckBox::~CCellCheckBox()
{
}

void CCellCheckBox::InitImageList()
{
	if (!m_CheckBoxImageList.m_hImageList)
	{
		m_CheckBoxImageList.Create(IDB_CHECKBOX, IMAGE_SIZE, IMAGE_SIZE, RGB(0xFF, 0x00, 0xFF));
	}
}

void CCellCheckBox::Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText)
{
	CCellCtrl::Initialize(hParentWnd, pParentEnabled, strText);

	if (m_strText[0] != _T('0') && m_strText[0] != _T('1'))
		m_strText = _T("0") + m_strText; // Assume user meant it unchecked if forgot to specify.

	InitImageList();
}

CString CCellCheckBox::GetDisplayedText()
{
	LPCTSTR strText = m_strText;
	return ++strText;
}

BOOL CCellCheckBox::IsChecked()
{
	return (m_strText[0] == _T('1')); 
}

void CCellCheckBox::SetIsChecked(BOOL bChecked)
{
	m_strText.SetAt(0, (bChecked)? _T('1') : _T('0'));
}

void CCellCheckBox::DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState /*= 0*/)
{
	POINT							ptCheckBox;
	CBrush							Brush;
	CSize							szSize;
	RECT							rcText;
	int								iSavedDC;

	iSavedDC = pDC->SaveDC();
	::ZeroMemory(&m_rcClickRect, sizeof(RECT)); // or use SetRectEmpty

	CopyRect(&m_rcArea, prcCell);
			
	if (IsDisabled())
	{
		Brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
		pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT)); // or COLOR_INACTIVECAPTION. Seems same
	}
	else if (uiItemState & (ODS_FOCUS | ODS_SELECTED))
	{
		Brush.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		Brush.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
	}
	pDC->FillRect(prcCell, &Brush);

	SelectFont(pDC);

	szSize = pDC->GetTextExtent(GetDisplayedText());
	CopyRect(&rcText, prcCell);

	HTHEME hTheme = OpenThemeData(m_hParentWnd, _T("Button"));

	if (!hTheme)
	{
		szSize.cx += IMAGE_SIZE;	// Have to add the image list width.

		if (szSize.cx > prcCell->right - prcCell->left)
		{
			ptCheckBox.x = prcCell->left;
			rcText.left += IMAGE_SIZE;		
		}
		else
		{
			if (m_dwStyle & CLCS_ALIGN_CENTER)
			{
				ptCheckBox.x = prcCell->left + (prcCell->right - prcCell->left - szSize.cx)/2;
				rcText.left = ptCheckBox.x + IMAGE_SIZE;
				rcText.right = ptCheckBox.x + szSize.cx + 1; // For some reason, have to add 1 for when you have bold, otherwise, displays ellipsis instead 
			}
			else if (m_dwStyle & CLCS_ALIGN_RIGHT)
			{
				if (szSize.cy)
				{
					rcText.right = prcCell->right;
					rcText.left = rcText.right - (szSize.cx + 1);
					ptCheckBox.x = rcText.left - IMAGE_SIZE;
				}
				else
				{
					rcText.right = rcText.left = 0;
					ptCheckBox.x = prcCell->right - IMAGE_SIZE;
				}
			}
			else
			{
				ptCheckBox.x = prcCell->left;
				rcText.left = ptCheckBox.x + IMAGE_SIZE;
				rcText.right = ptCheckBox.x + szSize.cx + 1;
			}
		}
		ptCheckBox.y = prcCell->top;

		if (prcCell->right - prcCell->left >= IMAGE_SIZE)
		{
			int ImageIdx = (IsChecked())? 1:0;
			if (IsDisabled())
				ImageIdx += 2;

			m_CheckBoxImageList.Draw(pDC, ImageIdx, ptCheckBox, ILD_NORMAL);
			
			pDC->DrawText(GetDisplayedText(), &rcText, DT_CENTER | DT_BOTTOM | DT_END_ELLIPSIS);

			m_rcClickRect.left = ptCheckBox.x;
			m_rcClickRect.top = ptCheckBox.y;
			m_rcClickRect.right = ptCheckBox.x + IMAGE_SIZE; 
			m_rcClickRect.bottom = ptCheckBox.y + IMAGE_SIZE;
		}
		else
		{
			rcText.left -= IMAGE_SIZE;
			pDC->DrawText(GetDisplayedText(), &rcText, DT_CENTER | DT_BOTTOM | DT_END_ELLIPSIS);
		}
	}
	else
	{
		int				StateId;
		HRESULT			hRes = 0;
		SIZE			sz;

		if (IsChecked())
			StateId = GetThemeButtonStateId(m_bActive, CBS_CHECKEDNORMAL, CBS_CHECKEDHOT, CBS_CHECKEDPRESSED, CBS_CHECKEDDISABLED);
		else
			StateId = GetThemeButtonStateId(m_bActive, CBS_UNCHECKEDNORMAL, CBS_UNCHECKEDHOT, CBS_UNCHECKEDPRESSED, CBS_UNCHECKEDDISABLED);

		hRes = GetThemePartSize(hTheme, pDC->m_hDC, BP_CHECKBOX, StateId, prcCell, TS_DRAW, &sz);

		szSize.cx += sz.cx + BOX_SEP;	// Have to add the image list width.

		if (szSize.cx > prcCell->right - prcCell->left)
		{
			m_rcClickRect.left = prcCell->left;
			m_rcClickRect.right = prcCell->left + sz.cx;
			rcText.left += sz.cx + BOX_SEP;		
		}
		else
		{
			if (m_dwStyle & CLCS_ALIGN_CENTER)
			{
				m_rcClickRect.left = prcCell->left + (prcCell->right - prcCell->left - szSize.cx)/2;
				m_rcClickRect.right = prcCell->left + (prcCell->right - prcCell->left - szSize.cx)/2 + sz.cx;
			
				rcText.left = m_rcClickRect.left + sz.cx + BOX_SEP;
				rcText.right = m_rcClickRect.left + szSize.cx;
			}
			else if (m_dwStyle & CLCS_ALIGN_RIGHT)
			{
				if (szSize.cy)
				{
					rcText.right = prcCell->right;
					rcText.left = rcText.right - szSize.cx;
					m_rcClickRect.right = rcText.left - BOX_SEP;
				}
				else
				{
					rcText.right = rcText.left = 0;
					m_rcClickRect.right = prcCell->right;
				}
				m_rcClickRect.left = m_rcClickRect.right - sz.cx;
			}
			else
			{
				m_rcClickRect.left = prcCell->left;
				m_rcClickRect.right = prcCell->left + sz.cx;
				rcText.left = m_rcClickRect.left + sz.cx + BOX_SEP;
				rcText.right = m_rcClickRect.left + szSize.cx;
			}
		}
		m_rcClickRect.top = prcCell->top + (prcCell->bottom - prcCell->top - sz.cy)/2;
		m_rcClickRect.bottom = prcCell->top + (prcCell->bottom - prcCell->top - sz.cy)/2 + sz.cy;
		rcText.top = prcCell->top + (prcCell->bottom - prcCell->top - szSize.cy)/2;
		rcText.bottom = prcCell->top + (prcCell->bottom - prcCell->top - sz.cy)/2 + szSize.cy;

		hRes = DrawThemeBackground(hTheme, pDC->m_hDC, BP_CHECKBOX, StateId, &m_rcClickRect, NULL);
		
		pDC->DrawText(GetDisplayedText(), &rcText, DT_CENTER | DT_BOTTOM | DT_END_ELLIPSIS);

		CloseThemeData(hTheme);
	}
	Brush.DeleteObject();
	pDC->RestoreDC(iSavedDC);
}

BOOL CCellCheckBox::OnPressButton(UINT nFlags, CPoint point)
{
	SetIsChecked(!IsChecked());
	return TRUE;
}

void CCellCheckBox::OnEnter()
{
	if (m_bActive)
	{
		SetIsChecked(!IsChecked());
		GetWindowFromHandle()->InvalidateRect(&m_rcClickRect, FALSE);
	}
}

int CCellCheckBox::GetMinWidth()
{
	CDC *pDC;
	int iMinWidth = 0;
	CSize szSize;
	CString strText = GetDisplayedText() + _T("i"); 

	pDC = GetWindowFromHandle()->GetDC();

	SelectFont(pDC);

	if (m_strText != _T(""))
	{
		szSize = pDC->GetTextExtent(strText);
		iMinWidth = szSize.cx;
	}
	iMinWidth += IMAGE_SIZE;
	return iMinWidth;
}

const RECT &CCellCheckBox::GetTextRect() const
{
	return m_rcClickRect;
}

void CCellCheckBox::AddToCtrlTypeStyle(DWORD dwFlags)
{
	m_dwCheckBoxStyle |= dwFlags;
}

void CCellCheckBox::RemoveFromCtrlTypeStyle(DWORD dwFlags)
{
	m_dwCheckBoxStyle &= ~dwFlags;
}

LONG CCellCheckBox::GetStyle()
{
	return m_dwCheckBoxStyle | m_dwStyle;
}