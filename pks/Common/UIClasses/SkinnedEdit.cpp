// SkinnedEdit.cpp : implementation file
//

#include "stdafx.h"
#include "SkinnedEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinnedEdit

CSkinnedEdit::CSkinnedEdit()
{
	m_nControlType = CONTROL_TYPE_ALPHANUMERIC;
	m_bValidateData = TRUE;
	m_nMaxChars = -1;
	m_nDecimalPlaces = 2;
	m_bBackSpace = FALSE;
	m_brush.CreateSolidBrush(RGB(14,18,23));
}

CSkinnedEdit::~CSkinnedEdit()
{
}


BEGIN_MESSAGE_MAP(CSkinnedEdit, CWnd)
	//{{AFX_MSG_MAP(CSkinnedEdit)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSkinnedEdit message handlers

BOOL CSkinnedEdit::CreateSkinControl(LPCTSTR lpszWindowName, LPRECT lpRect, CWnd *pParentWnd, UINT nControlID, long lFlags)
{
	m_csText = lpszWindowName;
	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;
	m_pParentWnd = pParentWnd;
	m_nControlID = nControlID;
	
	m_csFontName = "Arial";
	m_nFontSize = m_nHeight-12;
	m_nFontStyle = FONT_NORMAL;
	m_crBackgroundColorHover = BLACK;//RGB(255,255,255);
	m_crBackgroundColorPressed = BLACK;//RGB(255,255,255);
	m_crBackgroundColorUnPressed = RGB(14,18,23);
	m_crForegroundColor = BLACK;

	m_lStyle = lFlags;

	DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_TABSTOP;

	if(/*0)//*/m_lStyle & BORDER_STYLE_3D)
	{
		//m_lStyle &= ~BORDER_STYLE_3D;
		if(CWnd::CreateEx(/*WS_EX_STATICEDGE*/NULL,
						NULL, 
						m_csText, 
						dwStyle, 
						*lpRect, 
						pParentWnd, 
						nControlID, 
						NULL))
		{
			CWnd::BringWindowToTop();
			return TRUE;
		}
	}
	else
	{
		if(CWnd::Create(NULL, 
						m_csText, 
						dwStyle, 
						*lpRect, 
						pParentWnd, 
						nControlID, 
						NULL))
		{
			CWnd::BringWindowToTop();
			return TRUE;
		}
	}

	return FALSE;
}

int CSkinnedEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);

	LOGFONT lfFont;

	memset(&lfFont, 0, sizeof(lfFont));
	lstrcpy(lfFont.lfFaceName, m_csFontName);
	lfFont.lfHeight = m_nFontSize*10;
	m_cfFaceTextFont.CreatePointFontIndirect(&lfFont);

	DWORD dwStyle = WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL;

	if(m_lStyle & TEXT_ALIGN_RIGHT)
	{
		dwStyle |= ES_RIGHT;
	}
	m_edit.Create(dwStyle, rect, this, IDC_EDIT_CHILD);
	m_edit.SetFont(&m_cfFaceTextFont, TRUE);

	return 0;
}

BOOL CSkinnedEdit::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		::PostMessage(GetParent()->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_KEYDOWN, m_nControlID), pMsg->wParam);
		break;

	case WM_CHAR:
		{
			CString csData;
			char cBackSpace;
			cBackSpace = pMsg->wParam;
			if(cBackSpace == 8)
			{
				m_bBackSpace = TRUE;
				return 0;
			}
			csData.Format("%c",pMsg->wParam);

			TCHAR szControlText[255];
			m_edit.GetWindowText(szControlText, 255);
			m_csText = szControlText;

			if(m_nMaxChars != -1 && m_csText.GetLength() >= m_nMaxChars )
			{
				return 100;
			}

			if(::IsFieldTypeValid(GetControlType(),csData))
			{
				//checking for multiple decimals and "-" sign
				if( (csData == "." && (m_csText.Find(".") != -1)) || 
					(csData == "-" && ((m_csText.Find("-") != -1)) && GetControlType()==CONTROL_TYPE_PERCENTAGE && GetControlType() != CONTROL_TYPE_EMAIL) )
				{
					return 100;
				}

				return 0;
			}
			else
			{
				//if key pressed is CTRL+C, CTRL+V and CTRL+X
				if(pMsg->wParam == 0x3 || pMsg->wParam == 0x16 || pMsg->wParam == 0x18)
				{
					return 0;
				}
				return 100;
			}
		}
		break;
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CSkinnedEdit::SetControlText(LPCTSTR lpszText)
{
	CString csText = lpszText;
	m_csText = csText;
	m_edit.SetWindowText(csText);
}

void CSkinnedEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	TEXTMETRIC tmText;

	GetClientRect(rect);

	dc.FillSolidRect(rect, RGB(14,18,23));
	dc.SelectObject(&m_cfFaceTextFont);
	dc.SetTextColor(GetTextColor());
	dc.GetTextMetrics(&tmText);
	
	dc.TextOut((tmText.tmInternalLeading)*2+tmText.tmExternalLeading, 0, m_csText);

	// Do not call CWnd::OnPaint() for painting messages
}

void CSkinnedEdit::MoveWindowEng(LPRECT lpRect, BOOL bRedraw, long lFlags)
{
	CRect rect;

	m_nLeft = lpRect->left;
	m_nTop = lpRect->top;
	m_nWidth = lpRect->right - lpRect->left;
	m_nHeight = lpRect->bottom - lpRect->top;

	m_nFontSize = m_nHeight-6;
	PrepareFont();

	m_edit.SetFont(&m_cfFaceTextFont, TRUE);

	MoveWindow(lpRect, bRedraw);

	GetClientRect(rect);
	m_edit.MoveWindow(rect, TRUE);
}

void CSkinnedEdit::MoveWindowEng(int nLeft, int nTop, BOOL bRedraw, long lFlags)
{
	m_nLeft = nLeft;
	m_nTop = nTop;

	MoveWindow(m_nLeft, m_nTop, m_nWidth, m_nHeight, TRUE);
}

LPCTSTR CSkinnedEdit::SetFontName(LPCTSTR lpszFontFaceName)
{
	m_csFontName = lpszFontFaceName;
	PrepareFont();
	m_edit.SetFont(&m_cfFaceTextFont, TRUE);
	Invalidate(TRUE);

	return NULL;
}

CString CSkinnedEdit::GetControlText()
{
	m_edit.GetWindowText(m_csText);

	return m_csText;
}

void CSkinnedEdit::SetEnabled(BOOL bEnable)
{
	m_edit.EnableWindow(bEnable);
	EnableWindow(bEnable);
}

void CSkinnedEdit::ReadOnly(BOOL bReadOnly)
{
	if(bReadOnly)
	{
		char szTemp[255];
		m_edit.GetWindowText(szTemp, 255);
		m_csText = szTemp;
		m_edit.ShowWindow(SW_HIDE);
		Invalidate(TRUE);
	}
	else
	{
		m_edit.ShowWindow(SW_SHOWNORMAL);
	}

	m_bReadonly = bReadOnly;
}

int CSkinnedEdit::SetFontStyle(int nFontStyle)
{
	m_nFontStyle = nFontStyle;
	PrepareFont();
	m_edit.SetFont(&m_cfFaceTextFont, TRUE);

	return 0; //just to be consistant with the base class
}

void CSkinnedEdit::BltEx()
{

}

BOOL CSkinnedEdit::IsReadOnly()
{	
	return m_bReadonly;
}

void CSkinnedEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{		
	CWnd::OnLButtonDown(nFlags, point);
}

void CSkinnedEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	
	m_edit.SetFocus();	
}

void CSkinnedEdit::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);	
}

void CSkinnedEdit::OnDestroy() 
{
	CWnd::OnDestroy();
	
	m_edit.DestroyWindow();
}

void CSkinnedEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
}

BOOL CSkinnedEdit::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	return CWnd::OnNotify(wParam, lParam, pResult);
}

BOOL CSkinnedEdit::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch(LOWORD(wParam))
	{
		case IDC_EDIT_CHILD:
			switch(HIWORD(wParam))
			{
			case EN_KILLFOCUS:
				if(GetControlType() == CONTROL_TYPE_CURRENCY || GetControlType() == CONTROL_TYPE_PERCENTAGE)
				{
					ValidateDecimalPlaces();
				}
				::PostMessage(GetParent()->GetSafeHwnd(), WM_USER, MAKEWPARAM(MSG_KILLFOCUS,m_nControlID), 0L);
				return TRUE;
			case EN_SETFOCUS:
				return TRUE;
			case EN_CHANGE:
				return FALSE;
			case EN_UPDATE:
				if(m_bValidateData)
				{					
					if(IsDataValid())
					{
						TCHAR szControlText[255];
						m_edit.GetWindowText(szControlText, 255);
						m_csText = szControlText;
					}
					else
					{						
						m_bValidateData = FALSE;
						m_edit.SetWindowText((LPCTSTR)m_csText);
					}
				}
				else
				{
					m_bValidateData = TRUE;
				}
				return TRUE;
			default:
				break;
			}
			return TRUE;
		default:
				break;
	}
	
	return CWnd::OnCommand(wParam, lParam);
}

void CSkinnedEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSkinnedEdit::SetControlType(UINT nType)
{
	m_nControlType = nType;
}

UINT CSkinnedEdit::GetControlType() const
{
	return m_nControlType;
}

void CSkinnedEdit::SetSel(int nStartChar/*=0*/, int nEndChar/*=-1*/, BOOL bNoScroll/*=FALSE*/)
{
	m_edit.SetSel(nStartChar, nEndChar, bNoScroll);
}

BOOL CSkinnedEdit::IsDataValid()
{
	CString csData;

	TCHAR szControlText[255];
	
	m_edit.GetWindowText(szControlText, 255);
	csData = szControlText;
	csData.Remove(',');
	csData.TrimLeft();
	csData.TrimRight();

	if(!m_bBackSpace && csData.IsEmpty())
	{
		m_bBackSpace = FALSE;
		return FALSE;
	}
	if(::IsFieldTypeValid(GetControlType(),csData))
	{
		//checking for multiple decimals and "-" sign
		if( (csData == "." && (m_csText.Find(".") != -1)) || 
			(csData == "-" && (m_csText.Find("-") != -1) && GetControlType()==CONTROL_TYPE_PERCENTAGE) )
		{
			return FALSE;
		}

		int nPos = csData.Find("-");
		if(nPos != -1 && nPos != 0 && GetControlType()==CONTROL_TYPE_PERCENTAGE)
		{
			return FALSE;
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

void CSkinnedEdit::SetCharLimit(int nMaxChar)
{
	m_nMaxChars = nMaxChar;
}

int CSkinnedEdit::GetCharLimit()
{
	return m_nMaxChars;
}

void CSkinnedEdit::SetDecimalPlaceLimit(int nMaxDecimalPlace)
{
	m_nDecimalPlaces = nMaxDecimalPlace;
}

int CSkinnedEdit::GetDecimalPlaceLimit()
{
	return m_nDecimalPlaces;
}

void CSkinnedEdit::ValidateDecimalPlaces()
{
	double dValue = 0;
	int nPos = m_csText.Find(".");

	if(nPos != -1)
	{
		if((m_csText.GetLength() - nPos) != m_nDecimalPlaces)
		{
			dValue =  atof(m_csText);
			if(m_nDecimalPlaces == 3)
			{
				m_csText.Format("%.03f", dValue);
			}
			else
			{
				m_csText.Format("%.02f", dValue);
			}

			m_edit.SetWindowText((LPTSTR)(LPCTSTR)m_csText);
		}
	}
}

HBRUSH CSkinnedEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr; 

	switch(nCtlColor)
	{
	case CTLCOLOR_EDIT:
		pDC->SetBkColor(RGB(14,18,23));
		pDC->SetTextColor(RGB(232,232,232));
		hbr = (HBRUSH)m_brush;
		break;
	default:
		hbr = CWnd::OnCtlColor(pDC,pWnd,nCtlColor);
		break;
	}

	return hbr;
}