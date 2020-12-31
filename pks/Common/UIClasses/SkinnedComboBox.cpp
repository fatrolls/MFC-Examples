// SkinnedComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "SkinnedComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma optimize("", off)

/////////////////////////////////////////////////////////////////////////////
// CSkinnedComboBox

CSkinnedComboBox::CSkinnedComboBox()
{
	m_bDisplayList = FALSE;
	m_nSelectedItem = -1;
	m_nFontSize = -1;
}

CSkinnedComboBox::~CSkinnedComboBox()
{
}

BEGIN_MESSAGE_MAP(CSkinnedComboBox, CWnd)
	//{{AFX_MSG_MAP(CSkinnedComboBox)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSkinnedComboBox message handlers

int CSkinnedComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	return 0;
}

void CSkinnedComboBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rcClient;

	GetClientRect(rcClient);

	CWnd::OnLButtonDown(nFlags, point);
}

void CSkinnedComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{	
	CWnd::OnLButtonUp(nFlags, point);
}

void CSkinnedComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);
}

BOOL CSkinnedComboBox::CreateSkinControl(LPCTSTR lpszWindowName, 
										 LPRECT lpRect, 
										 CWnd *pParentWnd, 
										 UINT nControlID, 
										 long lFlags)
{
	m_csText = lpszWindowName;
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;
	m_pParentWnd = pParentWnd;
	m_nControlID = nControlID;
	
	m_csFontName = "Arial";
	if(m_nFontSize == -1)
	{
		m_nFontSize = 20;
	}
	m_nFontStyle = FONT_BOLD;
	m_crBackgroundColorHover = RGB(191,215,238);
	m_crBackgroundColorPressed = RGB(200,200,200);
	m_crBackgroundColorUnPressed = RGB(255,255,255);
	m_crForegroundColor = RGB(0,0,0);

	m_lFlags = lFlags;	//height of the listbox

	if(CWnd::Create(NULL, 
					m_csText, 
					WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN, 
					*lpRect,
					pParentWnd, 
					nControlID, 
					NULL))
	{
		if(PrepareFont())
		{
			SetFont(&m_cfFaceTextFont, TRUE);
		}

		m_csButton.SetImageResource(GetUnPressedID(), GetHoverID(), GetPressedID());
		m_nComboHeight = m_nHeight;

		if((m_csButton.CreateSkinControl("",CRect((m_nWidth-1) - COMBOBOX_BUTTON_WIDTH, 2, m_nWidth-1, m_nHeight), this, IDC_COMBOBOX_BUTTON))
			&& (m_csEdit.CreateSkinControl("Combo Edit", CRect(2, 2, m_nWidth - COMBOBOX_BUTTON_WIDTH, m_nHeight-2), this, IDC_COMBOBOX_EDIT, BORDER_STYLE_NONE))
			&& (m_csList.CreateSkinControl("Combo List", CRect(0,m_nHeight,m_nWidth,m_nHeight+m_lFlags), this, IDC_COMBOBOX_LIST/*, FL_LISTBOX_TYPE_COMBOCHILD*/)))
		{
			m_csEdit.SetFontName(m_csFontName);
			m_csEdit.SetFontStyle(m_nFontStyle);
			m_csEdit.SetTextColor(RGB(232,232,232));
			m_csEdit.SetControlText("");
			m_csEdit.SetFontSize(m_nFontSize);
			m_csEdit.ReadOnly(TRUE);
			
			m_csList.SetFontName(m_csFontName);
			m_csList.SetFontStyle(m_nFontStyle);
			m_csList.SetFontSize(m_nFontSize);

			m_csList.SetBackgroundColor(BUTTON_STATE_HOVER, m_crBackgroundColorHover);
			m_csList.SetBackgroundColor(BUTTON_STATE_PRESSED, m_crBackgroundColorPressed);
			m_csList.SetBackgroundColor(BUTTON_STATE_UNPRESSED, m_crBackgroundColorUnPressed);

			BringWindowToTop();
			return TRUE;
		}
	}
	
	return FALSE;
}

void CSkinnedComboBox::AddString(LPTSTR lpszItem)
{
	m_csList.AddString(lpszItem);
}

void CSkinnedComboBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	
	CRect rect;
	GetClientRect(rect);

	if(m_bDisplayList)
	{
		m_csList.ShowWindow(SW_NORMAL);
	}
	else
	{
		m_csList.ShowWindow(SW_HIDE);
	}

	CRect rcClientRect;
	
	GetClientRect(&rcClientRect);

	dc.DrawEdge(&rcClientRect, /*BDR_SUNKENOUTER | EDGE_SUNKEN*/NULL, BF_FLAT);

	m_csList.UpdateWindow();

	// Do not call CWnd::OnPaint() for painting messages
}

void CSkinnedComboBox::MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags)
{
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;

	MoveWindow(lpRect, bRedraw);
}

BOOL CSkinnedComboBox::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
		case WM_USER:
			switch(LOWORD(pMsg->wParam))
			{
				case MSG_COMMAND:
					switch(HIWORD(pMsg->wParam))
					{
						case IDC_COMBOBOX_LIST:
							{
								TCHAR szBuf[255];
								m_nSelectedItem = m_csList.GetCurSel();
								m_csList.GetText(m_nSelectedItem, szBuf);
								m_csEdit.SetTextColor(RGB(232,232,232));
								m_csEdit.SetControlText(szBuf);
								m_csEdit.Invalidate(TRUE);

								m_bDisplayList = FALSE;
								MoveWindowEng(CRect(m_nLeft, m_nTop, m_nLeft+m_nWidth, m_nTop+m_nComboHeight), TRUE);

								::PostMessage(GetParent()->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_SELCHANGE, m_nControlID), 0L);
							}
							break;

						default:
							break;
					}
					return TRUE;

				case MSG_LBUTTONDOWN:
					if(m_nHeight == m_nComboHeight)
					{
						m_bDisplayList = TRUE;
						m_csList.UnselectAll();
						MoveWindowEng(CRect(m_nLeft, m_nTop, m_nLeft+m_nWidth, m_nTop+m_nHeight+m_lFlags), TRUE);
					}
					else
					{
						m_bDisplayList = FALSE;
						MoveWindowEng(CRect(m_nLeft, m_nTop, m_nLeft+m_nWidth, m_nTop+m_nComboHeight), TRUE);
					}
					return TRUE;

				default:
					break;
			}
			break;

		default:
			break;
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}

void CSkinnedComboBox::BltEx()
{

}

void CSkinnedComboBox::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
}

void CSkinnedComboBox::SetButtonImageResource(INT nUnPressedID, INT nHoverID, INT nPressedID, INT nDisabledID)
{
	m_csButton.SetImageResource(nUnPressedID, nHoverID, nPressedID, nDisabledID);
}

LPCTSTR CSkinnedComboBox::SetFontName(LPCTSTR lpszFontFaceName)
{
	m_csList.SetFontName(m_csFontName);

	return SetFontName(m_csFontName);
}

int CSkinnedComboBox::SetFontSize(int nFontSize)
{
	m_nFontSize = nFontSize;
	return m_csList.SetFontSize(nFontSize);
}

int CSkinnedComboBox::SetFontStyle(int nFontStyle)
{
	m_csList.SetFontStyle(m_nFontStyle);

	return SetFontStyle(m_nFontStyle);;
}

void CSkinnedComboBox::SetBackgroundColor(int nBackgroundState, COLORREF crColor)
{
	CSkinControl::SetBackgroundColor(nBackgroundState, crColor);

	m_csList.SetBackgroundColor(nBackgroundState, crColor);
}

int CSkinnedComboBox::GetCurSel()
{
	return m_nSelectedItem;
}

void CSkinnedComboBox::SetCurSel(int nIndex)
{
	TCHAR szBuf[255];
	
	m_nSelectedItem = nIndex;

	if(nIndex == -1)
	{
		m_csEdit.SetTextColor(RGB(232,232,232));
		m_csEdit.SetControlText("");						
		m_csEdit.Invalidate(TRUE);
	}
	else
	{
		m_csList.GetText(m_nSelectedItem, szBuf);
		m_csEdit.SetTextColor(RGB(232,232,232));
		m_csEdit.SetControlText(szBuf);						
		m_csEdit.Invalidate(TRUE);
	}
}

int CSkinnedComboBox::GetLBText(int nIndex, LPTSTR lpszText)
{
	if(nIndex < 0)
	{
		*lpszText = NULL;
		return -1;
	}

	return m_csList.GetText(nIndex, lpszText);
}

void CSkinnedComboBox::HideDropDown()
{
	m_bDisplayList = FALSE;
	MoveWindowEng(CRect(m_nLeft, m_nTop, m_nLeft+m_nWidth, m_nTop+m_nComboHeight), TRUE);
}

void CSkinnedComboBox::SetTextAlignment(int nAlignment)
{
	m_csList.SetTextAlignment(nAlignment);
}

void CSkinnedComboBox::ClearAllContents()
{
	m_csList.ResetContent();
}

int CSkinnedComboBox::GetElementCount()
{
	return m_csList.GetCount();
}
