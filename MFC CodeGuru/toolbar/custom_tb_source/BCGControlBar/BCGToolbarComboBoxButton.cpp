// BCGToolbarComboBoxButton.cpp: implementation of the CBCGToolbarComboBoxButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGToolbar.h"
#include "globals.h"
#include "BCGToolbarComboBoxButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CBCGToolbarComboBoxButton, CBCGToolbarButton, 1)

static const int iComboHeight = 150;
static const int iDefaultSize = 150;
static const int iHorzMargin = 3;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGToolbarComboBoxButton::CBCGToolbarComboBoxButton()
{
	m_dwStyle = WS_CHILD | WS_VISIBLE | CBS_NOINTEGRALHEIGHT | CBS_DROPDOWNLIST | WS_VSCROLL;
	m_iWidth = iDefaultSize;

	Initialize ();
}
//**************************************************************************************
CBCGToolbarComboBoxButton::CBCGToolbarComboBoxButton (UINT uiId,
			int iImage,
			DWORD dwStyle,
			int iWidth) :
			CBCGToolbarButton (uiId, iImage)
{
	m_dwStyle = dwStyle | WS_CHILD | WS_VISIBLE | WS_VSCROLL;
	m_iWidth = (iWidth == 0) ? iDefaultSize : iWidth;

	Initialize ();
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::Initialize ()
{
	LOGFONT lf;
	memset (&lf, 0, sizeof (LOGFONT));

	_tcscpy (lf.lfFaceName, _T ("MS Sans Serif"));
	lf.lfHeight = -6;

	m_Font.CreateFontIndirect (&lf);
}
//**************************************************************************************
CBCGToolbarComboBoxButton::~CBCGToolbarComboBoxButton()
{
	if (m_wndCombo.GetSafeHwnd () != NULL)
	{
		m_wndCombo.DestroyWindow ();
	}
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::CopyFrom (const CBCGToolbarButton& s)
{
	CBCGToolbarButton::CopyFrom (s);
	m_lstItems.RemoveAll ();

	const CBCGToolbarComboBoxButton& src = (const CBCGToolbarComboBoxButton&) s;
	for (POSITION pos = src.m_lstItems.GetHeadPosition (); pos != NULL;)
	{
		m_lstItems.AddTail (src.m_lstItems.GetNext (pos));
	}

	m_dwStyle = src.m_dwStyle;
	m_iWidth = src.m_iWidth;
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::Serialize (CArchive& ar)
{
	CBCGToolbarButton::Serialize (ar);

	if (ar.IsLoading ())
	{
		ar >> m_iWidth;
		m_rect.right = m_rect.left + m_iWidth;
		ar >> m_dwStyle;

		m_lstItems.Serialize (ar);
	}
	else
	{
		ar << m_iWidth;
		ar << m_dwStyle;

		if (m_wndCombo.GetSafeHwnd () != NULL)
		{
			m_lstItems.RemoveAll ();

			for (int i = 0; i < m_wndCombo.GetCount (); i ++)
			{
				CString str;
				m_wndCombo.GetLBText (i, str);

				m_lstItems.AddTail (str);
			}
		}

		m_lstItems.Serialize (ar);
	}
}
//**************************************************************************************
int  CBCGToolbarComboBoxButton::OnCalculateSize (CDC* pDC, const CSize& sizeDefault, BOOL bHorz)
{
	if (bHorz)
	{
		if (m_wndCombo.GetSafeHwnd () != NULL)
		{
			m_wndCombo.ShowWindow (SW_SHOW);
		}

		return m_iWidth;
	}
	else
	{
		if (m_wndCombo.GetSafeHwnd () != NULL)
		{
			m_wndCombo.ShowWindow (SW_HIDE);
		}

		return CBCGToolbarButton::OnCalculateSize (pDC, sizeDefault, bHorz);
	}
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::OnMove ()
{
	if (m_wndCombo.GetSafeHwnd () != NULL &&
		(m_wndCombo.GetStyle () & WS_VISIBLE))
	{
		m_wndCombo.SetWindowPos (NULL, 
			m_rect.left + iHorzMargin, m_rect.top,
			m_rect.Width () - 2 * iHorzMargin, iComboHeight,
			SWP_NOZORDER);

		AdjustRect ();
	}
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::OnSize (int iSize)
{
	m_iWidth = iSize;
	m_rect.right = m_rect.left + m_iWidth;

	if (m_wndCombo.GetSafeHwnd () != NULL &&
		(m_wndCombo.GetStyle () & WS_VISIBLE))
	{
		m_wndCombo.SetWindowPos (NULL, 
			m_rect.left + iHorzMargin, m_rect.top,
			m_rect.Width () - 2 * iHorzMargin, iComboHeight,
								SWP_NOZORDER);
		AdjustRect ();
	}
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::OnChangeParentWnd (CWnd* pWndParent)
{
	ASSERT (pWndParent != NULL);
	ASSERT (pWndParent->GetSafeHwnd () != NULL);

	if (m_wndCombo.GetSafeHwnd () != NULL)
	{
		CWnd* pWndParentCurr = m_wndCombo.GetParent ();
		ASSERT (pWndParentCurr != NULL);

		if (pWndParentCurr->GetSafeHwnd () == pWndParent->GetSafeHwnd ())
		{
			return;
		}

		m_wndCombo.DestroyWindow ();
	}

	CRect rect = m_rect;
	rect.InflateRect (-2, 0);
	rect.bottom = rect.top + iComboHeight;

	m_wndCombo.Create (m_dwStyle, rect, pWndParent, m_nID);

	AdjustRect ();

	m_wndCombo.SetFont (&m_Font);

	for (POSITION pos = m_lstItems.GetHeadPosition (); pos != NULL;)
	{
		CString strItem = m_lstItems.GetNext (pos);
		m_wndCombo.AddString (strItem);
	}

	m_wndCombo.SetCurSel (0);
	m_wndCombo.SetEditSel (-1, 0);
}
//**************************************************************************************
int CBCGToolbarComboBoxButton::AddItem (LPCTSTR lpszItem)
{
	ASSERT (lpszItem != NULL);

	if (m_lstItems.Find (lpszItem) == NULL)
	{
		m_lstItems.AddTail (lpszItem);
	}

	if (m_wndCombo.GetSafeHwnd () != NULL)
	{
		int iIndex = m_wndCombo.FindString (-1, lpszItem);

		if (iIndex == CB_ERR)
		{
			iIndex = m_wndCombo.AddString (lpszItem);
		}

		m_wndCombo.SetCurSel (iIndex);
		m_wndCombo.SetEditSel (-1, 0);
	}

	return m_lstItems.GetCount () - 1;
}
//**************************************************************************************
LPCTSTR CBCGToolbarComboBoxButton::GetItem (int iIndex)
{
	if (iIndex == -1)	// Current selection
	{
		if (m_wndCombo.GetSafeHwnd () == NULL)
		{
			return NULL;
		}

		iIndex = m_wndCombo.GetCurSel ();
	}

	POSITION pos = m_lstItems.FindIndex (iIndex);
	if (pos == NULL)
	{
		return NULL;
	}

	return m_lstItems.GetAt (pos);
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::RemoveAllItems ()
{
	m_lstItems.RemoveAll ();
	if (m_wndCombo.GetSafeHwnd () != NULL)
	{
		m_wndCombo.ResetContent ();
	}
}
//**************************************************************************************
int CBCGToolbarComboBoxButton::GetCount () const
{
	return m_lstItems.GetCount ();
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::AdjustRect ()
{
	if (m_wndCombo.GetSafeHwnd () == NULL ||
		(m_wndCombo.GetStyle () & WS_VISIBLE) == 0)
	{
		return;
	}

	m_wndCombo.GetWindowRect (&m_rect);
	m_wndCombo.ScreenToClient (&m_rect);
	m_wndCombo.MapWindowPoints (m_wndCombo.GetParent (), &m_rect);
	m_rect.InflateRect (iHorzMargin, 0);
}
//**************************************************************************************
BOOL CBCGToolbarComboBoxButton::NotifyCommand (int iNotifyCode)
{
	switch (iNotifyCode)
	{
	case CBN_SELCHANGE:
		return TRUE;
	}

	return FALSE;
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::OnAddToCustomizePage ()
{
	CObList listButtons;	// Existing buttons with the same command ID

	if (CBCGToolBar::GetCommandButtons (m_nID, listButtons) == 0)
	{
		return;
	}

	CBCGToolbarComboBoxButton* pOther = 
		(CBCGToolbarComboBoxButton*) listButtons.GetHead ();
	ASSERT_VALID (pOther);
	ASSERT_KINDOF (CBCGToolbarComboBoxButton, pOther);

	CopyFrom (*pOther);
}
//**************************************************************************************
HBRUSH CBCGToolbarComboBoxButton::OnCtlColor (CDC* pDC, UINT nCtlColor)
{
	pDC->SetTextColor (::GetSysColor (COLOR_WINDOWTEXT));
	pDC->SetBkColor (::GetSysColor (COLOR_WINDOW));

	return globalData.hbrWindow;
}
//**************************************************************************************
void CBCGToolbarComboBoxButton::OnDraw (CDC* pDC, const CRect& rect, CBCGToolBarImages* pImages,
						BOOL bHorz, BOOL bCustomizeMode,
						BOOL bHighlight)
{
	if (m_wndCombo.GetSafeHwnd () == NULL ||
		(m_wndCombo.GetStyle () & WS_VISIBLE) == 0)
	{
		CBCGToolbarButton::OnDraw (pDC, rect, pImages,
							bHorz, bCustomizeMode,
							bHighlight);
	}
}
//**************************************************************************************
BOOL CBCGToolbarComboBoxButton::OnClick (CWnd* pWnd)
{	
	return m_wndCombo.GetSafeHwnd () != NULL &&
			(m_wndCombo.GetStyle () & WS_VISIBLE);
}
