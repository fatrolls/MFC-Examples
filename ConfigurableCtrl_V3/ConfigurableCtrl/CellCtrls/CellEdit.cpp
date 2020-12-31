//
// CellEdit.cpp: implementation of the CCellEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CellEdit.h"
#include "..\utilities.h"
#include "Uxtheme.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

DWORD CCellEdit::m_dwEditStyle = CLCS_ACTIVE_FRM_NORMAL | CLCS_INACTIVE_FRM_NORMAL; // this is an assumption

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCellEdit::CCellEdit() : CCellCtrl(), m_ShowCaret(FALSE), m_InvalidateCaret(FALSE), m_InternalAlign(Left) 
{
}

CCellEdit::~CCellEdit()
{
	m_BoldFont.DeleteObject();
	m_Font.DeleteObject();
}

void CCellEdit::InsertItemIntoPopUpMenu(UINT uiItemID)
{
	CString str;
	str.LoadString(uiItemID);
	str = str.Mid(str.Find(_T("\n")) + 1);
	m_PopUpMenu.InsertMenu(-1, MF_BYPOSITION, uiItemID, str);
}

void CCellEdit::Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText)
{
	CCellCtrl::Initialize(hParentWnd, pParentEnabled, strText);

	m_PopUpMenu.CreatePopupMenu();

	InsertItemIntoPopUpMenu(ID_EDIT_UNDO);
	m_PopUpMenu.InsertMenu(-1, MF_BYPOSITION | MF_SEPARATOR);
	InsertItemIntoPopUpMenu(ID_EDIT_CUT);
	InsertItemIntoPopUpMenu(ID_EDIT_COPY);
	InsertItemIntoPopUpMenu(ID_EDIT_PASTE);
	InsertItemIntoPopUpMenu(ID_EDIT_CLEAR);
	m_PopUpMenu.InsertMenu(-1, MF_BYPOSITION | MF_SEPARATOR);
	InsertItemIntoPopUpMenu(ID_EDIT_SELECT_ALL);

	m_strUndoText = m_strText;
}

BOOL CCellEdit::IsCaretInCell(const CPoint &pt)
{
	RECT			rcTxtCop;

	CopyRect(&rcTxtCop, &m_rcTxt);
	InflateRect(&rcTxtCop, 1,0);

	return PtInRect(&rcTxtCop, pt);
}

void CCellEdit::GetLeftRightSelPos(LONG &lLeftSelPos, LONG &lRightSelPos)
{
	lLeftSelPos = min(m_CaretPosDets.m_CharPos, m_CaretPosDets.m_StartSelPos);
	lRightSelPos = max(m_CaretPosDets.m_CharPos, m_CaretPosDets.m_StartSelPos);
}

void CCellEdit::GetSelectedString(CString &str)
{
	LONG lLeftSelPos, lRightSelPos;
	GetLeftRightSelPos(lLeftSelPos, lRightSelPos);
	str = m_strText.Mid(lLeftSelPos, lRightSelPos - lLeftSelPos);
}

void CCellEdit::DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState /*= 0*/)
{
	CString			strText;
	CBrush			Brush;
	int				iSavedDC;
	DWORD			dwStyle = GetStyle();

	iSavedDC = pDC->SaveDC();

	HTHEME hTheme = OpenThemeData(m_hParentWnd, _T("Edit"));

	Brush.CreateSolidBrush(GetSysColor(IsDisabled()? COLOR_BTNFACE : COLOR_WINDOW));

	if (hTheme)
	{
		int				StateId;
		HRESULT			hRes = 0;
		
		StateId = GetThemeStateId(EPSN_NORMAL, EPSN_HOT, EPSN_FOCUSED, EPSN_DISABLED);

		hRes = DrawThemeBackground(hTheme, pDC->m_hDC, EP_EDITBORDER_NOSCROLL, StateId, prcCell, NULL);

		StateId = GetThemeStateId(ETS_NORMAL, ETS_HOT, ETS_FOCUSED, ETS_DISABLED);

		RECT rc;
		hRes = GetThemeBackgroundContentRect(hTheme, pDC->m_hDC, EP_EDITTEXT, StateId, prcCell, &rc);

		pDC->FillRect(&rc, &Brush);
	}
	else
		pDC->FillRect(prcCell, &Brush);

	if (uiItemState & (ODS_FOCUS | ODS_SELECTED) && !m_bActive && !IsDisabled())
	{
		CBrush	HighlightBrush;
		CRect	rcHighlight;	
		HighlightBrush.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

		CopyRect(&rcHighlight, prcCell);
		InflateRect(&rcHighlight, -::GetSystemMetrics(SM_CXFIXEDFRAME), -::GetSystemMetrics(SM_CYFIXEDFRAME)); 

		if (rcHighlight.right > rcHighlight.left)
			pDC->FillRect(&rcHighlight, &HighlightBrush);
		
		HighlightBrush.DeleteObject();

		pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		pDC->SetTextColor(GetSysColor(IsDisabled()? COLOR_GRAYTEXT : COLOR_WINDOWTEXT));
	}
	SelectFont(pDC);

	CopyRect(&m_rcTxt, prcCell);
	m_rcTxt.top += ::GetSystemMetrics(SM_CYFIXEDFRAME);
	m_rcTxt.bottom -= ::GetSystemMetrics(SM_CYFIXEDFRAME);
	m_rcTxt.left += ::GetSystemMetrics(SM_CXFIXEDFRAME);
	m_rcTxt.right -= ::GetSystemMetrics(SM_CXFIXEDFRAME);

	ReComputeInternalAlignment(pDC);

	if (m_bActive)
	{
		CString str = m_strText.Mid(m_CaretPosDets.m_StartPos);
		pDC->DrawText(str, &m_rcTxt, (m_InternalAlign == Center? DT_CENTER : (m_InternalAlign == Right? DT_RIGHT : DT_LEFT)) | DT_BOTTOM);
	}
	else
		pDC->DrawText(m_strText, &m_rcTxt, (dwStyle & CLCS_ALIGN_CENTER? DT_CENTER : (dwStyle & CLCS_ALIGN_RIGHT? DT_RIGHT : DT_LEFT))
														| DT_BOTTOM | DT_END_ELLIPSIS);
	
	if (!hTheme)
		DrawFrameCtrl(pDC, prcCell);

	if (m_InvalidateCaret)
	{
		m_InvalidateCaret = FALSE;
		ReCalculateCaret();
	}

	if (m_CaretPosDets.m_StartSelPos != -1 && ((m_CaretPosDets.m_StartSelPos >= m_CaretPosDets.m_StartPos) ||  (m_CaretPosDets.m_CharPos >= m_CaretPosDets.m_StartPos)))
	{
		CBrush			Brush2;
		RECT			rectSelTxt; 
		Brush2.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

		LONG lLeftSelPos, lRightSelPos;

		GetLeftRightSelPos(lLeftSelPos, lRightSelPos);

		lLeftSelPos = max(m_CaretPosDets.m_StartPos, lLeftSelPos);

		rectSelTxt.top = m_rcTxt.top;
		rectSelTxt.bottom = m_rcTxt.bottom - ::GetSystemMetrics(SM_CYFIXEDFRAME);

		CString str;
		CSize sz;

		if (m_InternalAlign == Left)
		{
			str = m_strText.Mid(m_CaretPosDets.m_StartPos, lLeftSelPos - m_CaretPosDets.m_StartPos);
			sz = pDC->GetTextExtent(str);

			rectSelTxt.left = m_rcTxt.left + sz.cx;
			str = m_strText.Mid(lLeftSelPos, lRightSelPos - lLeftSelPos);
			sz = pDC->GetTextExtent(str);

			rectSelTxt.right = rectSelTxt.left + sz.cx;
		}
		else if (m_InternalAlign == Right)
		{
			str = m_strText.Mid(lRightSelPos);
			sz = pDC->GetTextExtent(str);

			rectSelTxt.right = m_rcTxt.right - sz.cx;
			str = m_strText.Mid(lLeftSelPos, lRightSelPos - lLeftSelPos);
			sz = pDC->GetTextExtent(str);

			rectSelTxt.left = rectSelTxt.right - sz.cx;
		}
		else if (m_InternalAlign == Center)
		{
			sz = pDC->GetTextExtent(m_strText);
			int leftgap = m_rcTxt.left + (m_rcTxt.right - m_rcTxt.left - sz.cx)/2;

			str = m_strText.Mid(m_CaretPosDets.m_StartPos, lLeftSelPos - m_CaretPosDets.m_StartPos);
			sz = pDC->GetTextExtent(str);

			rectSelTxt.left = leftgap + sz.cx;
			str = m_strText.Mid(lLeftSelPos, lRightSelPos - lLeftSelPos);
			sz = pDC->GetTextExtent(str);

			rectSelTxt.right = rectSelTxt.left + sz.cx;
		}
		pDC->FillRect(&rectSelTxt, &Brush2);
		pDC->DrawText(str, &rectSelTxt, DT_LEFT | DT_BOTTOM);
		Brush2.DeleteObject();
	}

	CPoint pt = pDC->GetWindow()->GetCaretPos();

	if (IsCaretInCell(pt) && m_bActive)
		ShowCaret();
	else
		HideCaret();

	Brush.DeleteObject();
	pDC->RestoreDC(iSavedDC);
}

int CCellEdit::GetMinWidth()
{
	CWnd				*pWnd = GetWindowFromHandle();
	CDC					*pDC = pWnd->GetDC();
	int					iSavedDC = pDC->SaveDC();
	CString				strText = m_strText;
	CSize				szSize;
	int					iMinWidth = 0;

	SelectFont(pDC);
	szSize = pDC->GetTextExtent(strText);
	iMinWidth = szSize.cx + 2*::GetSystemMetrics(SM_CXFIXEDFRAME) + ::GetSystemMetrics(SM_CXBORDER);
	pDC->RestoreDC(iSavedDC);

	return iMinWidth;
} 

const RECT &CCellEdit::GetTextRect() const
{
	return m_rcTxt;
}

int CCellEdit::GetRightIncr(CDC *pDC)
{
	int Right_Incr = 0;

	if (m_InternalAlign == Right || m_InternalAlign == Center)
	{
		SIZE size;
		CString str = m_strText.Mid(m_CaretPosDets.m_StartPos);
		::GetTextExtentExPoint(pDC->m_hDC, str, str.GetLength(), m_rcTxt.right - m_rcTxt.left, NULL, NULL, &size);
		
		Right_Incr = m_rcTxt.right - m_rcTxt.left - size.cx;

		if (m_InternalAlign == Center)
			Right_Incr /= 2;
	}
	return Right_Incr;
}

void CCellEdit::ReComputeInternalAlignment(CDC *pDC)
{
	Alignment OldIntAlign = m_InternalAlign;
	m_InternalAlign = Left;

	if (m_dwStyle & CLCS_ALIGN_CENTER || m_dwStyle & CLCS_ALIGN_RIGHT)
	{
		SelectFont(pDC);
		CSize sizeTxt = pDC->GetTextExtent(m_strText);

		if (m_rcTxt.right - m_rcTxt.left > sizeTxt.cx)
		{
			if (m_dwStyle & CLCS_ALIGN_CENTER)
				m_InternalAlign = Center;
			else if (m_dwStyle & CLCS_ALIGN_RIGHT)
				m_InternalAlign = Right;
		}
	}
	if (OldIntAlign != m_InternalAlign)
		ReCalculateCaret();
}

void CCellEdit::CalculateCaretFromPt(const CPoint &point)
{
	CWnd *pWnd = GetWindowFromHandle();
	CDC *pDC = pWnd->GetDC();
	CFont		Font;	

	int iWidth = point.x - m_rcTxt.left;
	int iCharPos = 0;
	INT *piChWidth;
	SIZE		size; 
	
	SelectFont(pDC);

	int Right_Incr = GetRightIncr(pDC);

	piChWidth = new INT[m_strText.GetLength()];

	iWidth -= Right_Incr;

	if (iWidth > 0)
	{
		CString str = m_strText.Mid(m_CaretPosDets.m_StartPos);
		::GetTextExtentExPoint(pDC->m_hDC, str, str.GetLength(), iWidth, (int*)&iCharPos, piChWidth, &size);
		m_CaretPosDets.m_CharPos = m_CaretPosDets.m_StartPos + iCharPos;
	}
	else
		m_CaretPosDets.m_CharPos = m_CaretPosDets.m_StartPos;

	m_CaretPosDets.m_point.x = (iCharPos)? 
			m_rcTxt.left + Right_Incr + piChWidth[iCharPos - 1] : m_rcTxt.left + Right_Incr;

	m_CaretPosDets.m_point.y = m_rcTxt.top;

	delete[] piChWidth;
	Font.DeleteObject();
}

BOOL CCellEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	(m_bActive)? HideCaret() : m_CaretPosDets.m_StartPos = 0;
	m_CaretPosDets.m_StartSelPos = -1;

	CCellCtrl::OnLButtonDown(nFlags, point);

	CalculateCaretFromPt(point);

	return TRUE;
}

void CCellEdit::OnCaretHandlingLButtonDown(UINT nFlags, CPoint point)
{
	GetWindowFromHandle()->SetCaretPos(m_CaretPosDets.m_point);
	InvalidateCaret();	
}

BOOL CCellEdit::IsPrintableChar(UINT nChar)
{
	return (nChar == VK_BACK || IsKeyDown(VK_CONTROL))? FALSE : TRUE;
}

void CCellEdit::MoveCaretPos(TCHAR ch, BOOL bForward /*= TRUE*/)
{
	CWnd *pWnd = GetWindowFromHandle();

	CDC *pDC = pWnd->GetDC();
	int iSavedDC = pDC->SaveDC();

	SelectFont(pDC);

	CSize sizeTxt = pDC->GetTextExtent(&ch, 1);

	CPoint pt = pWnd->GetCaretPos();

	if (bForward)
	{
		pt.x += sizeTxt.cx;
		m_CaretPosDets.m_CharPos++;
	}
	else
	{
		pt.x -= sizeTxt.cx;
		m_CaretPosDets.m_CharPos--;
	}
	if (!IsCaretInCell(pt))
	{
		if (bForward)
		{
			CString str = m_strText.Left(m_CaretPosDets.m_CharPos);
			str.MakeReverse();

			INT *piChWidth;
			SIZE		size;
			int			iLastCharPos;
		
			piChWidth = new INT[str.GetLength()];

			::GetTextExtentExPoint(pDC->m_hDC, str, str.GetLength(), m_rcTxt.right - m_rcTxt.left, (int*)&iLastCharPos, piChWidth, &size);
		
			// If caret is not last character of string, want to scroll rightwards a bit more... Say up to 3 characters
			if (m_CaretPosDets.m_CharPos < m_strText.GetLength())
			{
				const int MaxRightShift = 3;
				iLastCharPos -= (m_strText.GetLength() - m_CaretPosDets.m_CharPos >= MaxRightShift)? MaxRightShift : 
												m_strText.GetLength() - m_CaretPosDets.m_CharPos;
			}
			m_CaretPosDets.m_StartPos = m_CaretPosDets.m_CharPos - iLastCharPos;
			pt.x = m_rcTxt.left + piChWidth[iLastCharPos - 1];

			delete[] piChWidth;
		}
		else
		{
			if (!m_CaretPosDets.m_CharPos)
			{
				m_CaretPosDets.m_StartPos = m_CaretPosDets.m_CharPos;
				pt.x = m_rcTxt.left;
			}
			else // Again, if caret is not first character of string, want to scroll leftwards a bit more... Say up to 3 characters
			{
				const int MaxLeftShift = 3;
				int LeftShiftStart = (m_CaretPosDets.m_CharPos >= MaxLeftShift)? MaxLeftShift : m_CaretPosDets.m_CharPos;

				CString str = m_strText.Mid(m_CaretPosDets.m_CharPos - LeftShiftStart, LeftShiftStart);

				CSize sizeTxt = pDC->GetTextExtent(str, LeftShiftStart);

				if (sizeTxt.cx <= m_rcTxt.right - m_rcTxt.left)
				{
					m_CaretPosDets.m_StartPos = m_CaretPosDets.m_CharPos - LeftShiftStart;
					pt.x = m_rcTxt.left + sizeTxt.cx;
				}
				else
				{
					m_CaretPosDets.m_StartPos = m_CaretPosDets.m_CharPos;
					pt.x = m_rcTxt.left;
				}
			}
		}
	}
	pWnd->SetCaretPos(pt);

	pDC->RestoreDC(iSavedDC);
}

void CCellEdit::RemoveSelString()
{
	if (m_CaretPosDets.m_StartSelPos != -1)
	{
		LONG lLeftSelPos, lRightSelPos;

		GetLeftRightSelPos(lLeftSelPos, lRightSelPos);

		m_strText.Delete(lLeftSelPos, lRightSelPos - lLeftSelPos);
		m_CaretPosDets.m_CharPos = lLeftSelPos;
		m_CaretPosDets.m_StartSelPos = -1;
		ReCalculateCaret();
	}
}

BOOL CCellEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (IsPrintableChar(nChar))
	{
		if (m_CaretPosDets.m_StartSelPos != -1)
		{
			RemoveSelString();
			m_CaretPosDets.m_StartSelPos = -1;
		}
		m_strText.Insert(m_CaretPosDets.m_CharPos, nChar);

		if (m_InternalAlign == Left)
			MoveCaretPos((TCHAR)nChar);
		else if (m_InternalAlign == Right)
			m_CaretPosDets.m_CharPos++;
		else if (m_InternalAlign == Center)
		{
			m_CaretPosDets.m_CharPos++;
			ReCalculateCaret();
		}
	}
	return FALSE; // Must return FALSE to prevent the call to CListCtrl::OnChar, which will select the row in 
				// which 1st character of 1st item is same as character just typed. This behaviour is obviouly
				// not desired here.
}

void CCellEdit::SelectAll()
{
	m_CaretPosDets.m_StartPos = m_CaretPosDets.m_StartSelPos = 0;
	m_CaretPosDets.m_CharPos = m_strText.GetLength();
	ReCalculateCaret();
}

BOOL CCellEdit::Copy()
{
	BOOL		bRetVal;
	HGLOBAL		hglb; 
	CString		str;

	bRetVal = OpenClipboard(m_hParentWnd);

	if (bRetVal)
	{
		bRetVal = EmptyClipboard(); 

		if (bRetVal && m_CaretPosDets.m_StartSelPos != -1)
		{
			GetSelectedString(str);
			size_t sizeCop = (str.GetLength() + 1) * sizeof(char);

			char *pChrSource;
#ifdef UNICODE
			size_t ConvChars = 0;
			size_t strSize = str.GetLength() + 1;
			pChrSource = new char[strSize];
			wcstombs_s(&ConvChars, pChrSource, strSize, str, _TRUNCATE);
#else
			pChrSource = str.GetBuffer(0);
#endif
			hglb = GlobalAlloc(GMEM_MOVEABLE, sizeCop);

			if (hglb != NULL)
			{
				char *pChrCop;
				pChrCop = (char *)GlobalLock(hglb);
				memcpy(pChrCop, pChrSource, sizeCop);
				GlobalUnlock(hglb);
				SetClipboardData(CF_TEXT, hglb); 
			}
#ifdef UNICODE	
			delete[] pChrSource;
#else
			str.ReleaseBuffer();
#endif
		}
		CloseClipboard();
	}
	return bRetVal;
}

BOOL CCellEdit::Paste()
{
	BOOL		bRetVal;
	HGLOBAL		hglb;
	CString		str;

	bRetVal = IsClipboardFormatAvailable(CF_TEXT);

	if (bRetVal)
	{
		bRetVal = OpenClipboard(m_hParentWnd);

		if (bRetVal)
		{
			hglb = GetClipboardData(CF_TEXT); 

			if (hglb != NULL) 
			{
				RemoveSelString();
#ifdef UNICODE
				char*    pChr; 
				pChr = (char*)GlobalLock(hglb); 
				size_t ChrSize = strlen(pChr) + 1;
				size_t ConvChars = 0;
				wchar_t *pWChr = new wchar_t[ChrSize];
				mbstowcs_s(&ConvChars, pWChr, ChrSize, pChr, _TRUNCATE);
				str = pWChr;
				delete[] pWChr;
#else
				str = (LPCTSTR)GlobalLock(hglb); 
#endif
				m_strText.Insert(m_CaretPosDets.m_CharPos, str);
				m_CaretPosDets.m_CharPos += str.GetLength();
				m_CaretPosDets.m_StartSelPos = -1;

				if (!ShiftTextLeftwards())
					ReCalculateCaret();

    			GlobalUnlock(hglb);
			}
			CloseClipboard(); 
		}
	}
	return bRetVal; 
}

BOOL CCellEdit::Cut()
{
	BOOL bRetVal = Copy();
	RemoveSelString();
	ShiftTextLeftwards();
	return bRetVal; 
}

void CCellEdit::Undo()
{
	CString str;
	str = m_strText;
	m_strText = m_strUndoText;
	m_strUndoText = str;

	int iLen = m_strText.GetLength();
	
	if (m_CaretPosDets.m_CharPos > iLen) m_CaretPosDets.m_CharPos = iLen;
	if (m_CaretPosDets.m_StartPos > iLen) m_CaretPosDets.m_StartPos = iLen;
	if (m_CaretPosDets.m_StartSelPos > iLen) m_CaretPosDets.m_StartSelPos = iLen;

	if (!ShiftTextLeftwards())
		InvalidateCaret();
}

void CCellEdit::ScrollTextToEnd(CDC *pDC)
// Scrolls to end either on pressing 'End' or to prevent an unnecessary gap apprearing (see ShiftTextLeftwards below)
{
	CString str = m_strText;
	str.MakeReverse();

	INT *piChWidth;
	SIZE		size;
	int			iLastCharPos;
		
	piChWidth = new INT[str.GetLength()];

	::GetTextExtentExPoint(pDC->m_hDC, str, str.GetLength(), m_rcTxt.right - m_rcTxt.left, (int*)&iLastCharPos, piChWidth, &size);

	m_CaretPosDets.m_StartPos = m_strText.GetLength() - iLastCharPos;
	InvalidateCaret();
	delete[] piChWidth;
}

BOOL CCellEdit::ShiftTextLeftwards()
// Called when press Delete or Backspace keys or cut/paste/undo/erase. If the displayed text is not showing start of string and you shorten the string length in 
// such a way that there is a gap on right hand side, then you want to scroll text leftwards in order to fill that gap.   
{
	CDC *pDC = GetWindowFromHandle()->GetDC();
	int iSavedDC = pDC->SaveDC();
	BOOL ShiftedRight = FALSE;

	SelectFont(pDC);

	CString strRHS = m_strText.Mid(m_CaretPosDets.m_CharPos);
	CSize szRHS = pDC->GetTextExtent(strRHS);

	if (m_rcTxt.right - m_rcTxt.left > szRHS.cx)
	{
		ShiftedRight = TRUE;
		ScrollTextToEnd(pDC);
	}	
	pDC->RestoreDC(iSavedDC);

	return  ShiftedRight;
}

BOOL CCellEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bRetVal = TRUE;

	if (m_CaretPosDets.m_StartSelPos != -1 && (nChar == VK_DELETE || nChar == VK_BACK))
	{
		RemoveSelString();
		ShiftTextLeftwards();
	}
	else if (nChar == VK_DELETE)
	{
		m_strText.Delete(m_CaretPosDets.m_CharPos, 1);
		ShiftTextLeftwards();

		if (m_InternalAlign == Right)
			ReCalculateCaret();
	}
	else if (nChar == VK_BACK)
	{
		if (m_CaretPosDets.m_CharPos)
		{
			TCHAR ch = m_strText.GetAt(m_CaretPosDets.m_CharPos-1);
			
			m_strText.Delete(m_CaretPosDets.m_CharPos-1, 1);

			m_CaretPosDets.m_StartSelPos = -1;

			m_CaretPosDets.m_CharPos--;

			if (m_InternalAlign == Left)
			{
				if (!ShiftTextLeftwards())
				{
					m_CaretPosDets.m_CharPos++;
					MoveCaretPos(ch, FALSE);
				}
			}
			else if (m_InternalAlign == Center)
				ReCalculateCaret();
		}
	}
	else if (nChar == VK_LEFT || nChar == VK_UP)
	{
		if (m_CaretPosDets.m_CharPos)
		{
			TCHAR ch = m_strText.GetAt(m_CaretPosDets.m_CharPos-1);
			m_CaretPosDets.m_StartSelPos = -1;
			MoveCaretPos(ch, FALSE);
		}
	}
	else if (nChar == VK_RIGHT || nChar == VK_DOWN)
	{
		if (m_CaretPosDets.m_CharPos < m_strText.GetLength())
		{
			m_CaretPosDets.m_StartSelPos = -1;
			TCHAR ch = m_strText.GetAt(m_CaretPosDets.m_CharPos);
			MoveCaretPos(ch);
		}
	}
	else if (nChar == VK_HOME)
	{
		m_CaretPosDets.m_StartSelPos = -1;
		m_CaretPosDets.m_StartPos = 0;
		m_CaretPosDets.m_CharPos = 0;
		InvalidateCaret();
	}
	else if (nChar == VK_END)
	{
		CDC *pDC = GetWindowFromHandle()->GetDC();
		int iSavedDC = pDC->SaveDC();

		SelectFont(pDC);
		m_CaretPosDets.m_StartSelPos = -1;
		m_CaretPosDets.m_CharPos = m_strText.GetLength();
		ScrollTextToEnd(pDC);

		pDC->RestoreDC(iSavedDC);
	}
	if (nChar == VK_DELETE || nChar == VK_BACK)
		m_CaretPosDets.m_StartSelPos = -1;

	if (IsKeyDown(VK_CONTROL)) // Ctrl + key handling here
	{
		if (nChar == 'a' || nChar == 'A') // select all
			SelectAll();

		if (nChar == 'c' || nChar == 'C') 
			Copy();

		if (nChar == 'x' || nChar == 'X') 
			Cut();

		if (nChar == 'v' || nChar == 'V') 
			Paste();

		if (nChar == 'z' || nChar == 'Z') 
			Undo();
	}
	return bRetVal;
}

void CCellEdit::OnKillActive()
{
	CCellCtrl::OnKillActive(); 
	m_CaretPosDets.m_StartSelPos = -1;
	m_CaretPosDets.m_StartPos = 0;
	HideCaret();
}

void CCellEdit::ReCalculateCaret()
{
	if (m_bActive)
	{
		CWnd *pWnd = GetWindowFromHandle();
		CDC *pDC = pWnd->GetDC();
		int iSavedDC = pDC->SaveDC();

		SelectFont(pDC);

		CString str = m_strText.Mid(m_CaretPosDets.m_StartPos);
		CSize sz = pDC->GetTextExtent(str, m_CaretPosDets.m_CharPos - m_CaretPosDets.m_StartPos);

		int Right_Incr = GetRightIncr(pDC);
		m_CaretPosDets.m_point.x = 	m_rcTxt.left + Right_Incr + sz.cx;
		m_CaretPosDets.m_point.y = m_rcTxt.top;

		if (pWnd->GetFocus() == pWnd) // Make sure focused window is parent of this ctrl. Otherwise, get a messed up caret when click on another control 
		{
			pWnd->SetCaretPos(m_CaretPosDets.m_point);
			ShowCaret();
		}
		pDC->RestoreDC(iSavedDC);
	}
}

BOOL CCellEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	InvalidateCaret();
	return TRUE;
} 

BOOL CCellEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	InvalidateCaret();
	return TRUE;
} 

BOOL CCellEdit::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	InvalidateCaret();
	return TRUE;
}

BOOL CCellEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		if (m_CaretPosDets.m_StartSelPos == -1)
			m_CaretPosDets.m_StartSelPos = m_CaretPosDets.m_CharPos;

		CalculateCaretFromPt(point);

		GetWindowFromHandle()->SetCaretPos(m_CaretPosDets.m_point);
		InvalidateCaret();	
	}
	return TRUE;
}

void CCellEdit::OnResizeColumn()
{
	InvalidateCaret(); // called before window has focus
}

void CCellEdit::OnKillFocus(CWnd* pNewWnd)
{
	m_CaretPosDets.m_StartSelPos = -1;
	m_CaretPosDets.m_StartPos = 0;
	InvalidateCaret();
}

void CCellEdit::OnSetFocus(CWnd* pOldWnd)
{
	GetWindowFromHandle()->SetCaretPos(m_CaretPosDets.m_point);
	m_ShowCaret = FALSE;
	ShowCaret();
} 

void CCellEdit::EnableMenuItems()
{
	UINT			uiEnable;
	CString			strSelectedString;

	if (m_CaretPosDets.m_StartSelPos != -1)
		GetSelectedString(strSelectedString);
	
	uiEnable = (m_strUndoText != m_strText)? MF_ENABLED : MF_GRAYED;
	m_PopUpMenu.EnableMenuItem(ID_EDIT_UNDO, uiEnable);

	uiEnable = (strSelectedString.GetLength())? MF_ENABLED : MF_GRAYED;
	m_PopUpMenu.EnableMenuItem(ID_EDIT_CUT, uiEnable);
	m_PopUpMenu.EnableMenuItem(ID_EDIT_COPY, uiEnable);
	m_PopUpMenu.EnableMenuItem(ID_EDIT_CLEAR, uiEnable);

	uiEnable = IsClipboardFormatAvailable(CF_TEXT)? MF_ENABLED : MF_GRAYED;
	m_PopUpMenu.EnableMenuItem(ID_EDIT_PASTE, uiEnable);

	uiEnable = (m_strText.GetLength() && m_strText.GetLength() != strSelectedString.GetLength())? MF_ENABLED : MF_GRAYED;
	m_PopUpMenu.EnableMenuItem(ID_EDIT_SELECT_ALL, uiEnable);
}

BOOL CCellEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	EnableMenuItems();
	CWnd *pWnd = GetWindowFromHandle();
	pWnd->ClientToScreen(&point);
	m_PopUpMenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, pWnd);
	return TRUE;
}

BOOL CCellEdit::OnCommand(WPARAM wParam, LPARAM lParam)
{
	BOOL bRetVal = FALSE;

	switch (wParam)
	{
		case ID_EDIT_UNDO:
			Undo();
		break;

		case ID_EDIT_CUT:
			Cut();
		break;

		case ID_EDIT_COPY:
			Copy();
		break;

		case ID_EDIT_PASTE:
			Paste();
		break;

		case ID_EDIT_CLEAR:
			RemoveSelString();
			ShiftTextLeftwards();
		break;

		case ID_EDIT_SELECT_ALL:
			SelectAll();
		break;

		default:
			bRetVal = TRUE;
	}
	if (!bRetVal)
		InvalidateCaret();

	return bRetVal;
}	

void CCellEdit::AddToCtrlTypeStyle(DWORD dwFlags)
{
	m_dwEditStyle |= dwFlags;
}

void CCellEdit::RemoveFromCtrlTypeStyle(DWORD dwFlags)
{
	m_dwEditStyle &= ~dwFlags;
}

LONG CCellEdit::GetStyle()
{
	return m_dwEditStyle | m_dwStyle;
}