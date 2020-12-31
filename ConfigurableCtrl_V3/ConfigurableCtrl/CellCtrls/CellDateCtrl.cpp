#include "stdafx.h"
#include "CellDateCtrl.h"
#include "popupcalendar.h"
#include "..\utilities.h"
#include "..\ConfigListCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DWORD CCellDateCtrl::m_dwDateCtrlStyle = CLCS_ACTIVE_FRM_NORMAL | CLCS_INACTIVE_FRM_NORMAL;

BOOL CCellDateCtrl::m_DateFormatInitialized = FALSE;
BOOL CCellDateCtrl::m_StartSeparator = FALSE;
CString CCellDateCtrl::m_DtFormatStr = _T("");
CStringArray CCellDateCtrl::m_Separators;

BOOL CALLBACK CCellDateCtrl::InitDateFormatProc(LPTSTR lpDateFormatString, CALID CalId)
{
	m_DtFormatStr = lpDateFormatString;
	return FALSE;
}

void CCellDateCtrl::ComputeSeparators()
{
	m_Separators.RemoveAll();

	int len = m_DtFormatStr.GetLength(), pos = 1, posStart = 0;

	if (len)
	{
		BOOL WasYMD = IsYMD(m_DtFormatStr[0]);
		m_StartSeparator = !WasYMD;

		for (pos = 1; pos < len; pos++)
		{
			if (WasYMD && !(WasYMD=IsYMD(m_DtFormatStr[pos])))
				posStart = pos;
			else if (!WasYMD && (WasYMD=IsYMD(m_DtFormatStr[pos])))
				m_Separators.Add(m_DtFormatStr.Mid(posStart, pos - posStart));
		}
		if (!IsYMD(m_DtFormatStr[--pos]))
			m_Separators.Add(m_DtFormatStr.Mid(posStart, pos - posStart));
	}
}

void CCellDateCtrl::InitializeDateFormat()
{
	if (!m_DateFormatInitialized)
	{
		VERIFY(EnumDateFormatsEx(&CCellDateCtrl::InitDateFormatProc, LOCALE_USER_DEFAULT, DATE_SHORTDATE));
		m_DateFormatInitialized = TRUE;
		ComputeSeparators();
	}
}

void CCellDateCtrl::SetDateFormat(const CString &strDateFormat)
{
	m_DtFormatStr = strDateFormat;
	ComputeSeparators();
	m_DateFormatInitialized = TRUE;
}

CCellDateCtrl::CCellDateCtrl() : m_YMDActPos(-1), m_YMDDetailsInit(FALSE), m_strDisplay()
{
	InitializeDateFormat();
	m_pPopUpWnd = new CPopupCalendar;
	::ZeroMemory(&m_CellDate, sizeof(SYSTEMTIME)); 
}

CCellDateCtrl::~CCellDateCtrl()
{
	delete m_pPopUpWnd;
}

void CCellDateCtrl::AddYMDInfo(YMDInfo &ymdInfo, TCHAR YMDch)
{
	switch (YMDch)
	{
		case DAY_CH:
			ymdInfo.m_ymd = Day;
		break;
		case MONTH_CH:
			ymdInfo.m_ymd = Month;
		break;
		case YEAR_CH:
			ymdInfo.m_ymd = Year;
		break;
	}
	m_YMDInfoArray.Add(ymdInfo);
}

void CCellDateCtrl::PopulateYMDDetails()
{
	int sepPos = (m_StartSeparator)? 1 : 0,	ymdPos = 0, startPos = (m_StartSeparator)? m_Separators[0].GetLength() : 0, Pos;

	if (m_Separators.GetCount() > sepPos && m_YMDInfoArray.GetCount() > 0)
	{
		while (ymdPos < m_YMDInfoArray.GetCount() && (sepPos < m_Separators.GetCount()))
		{
			Pos = m_strDisplay.Find(m_Separators[sepPos], startPos); 
			if (!m_YMDInfoArray[ymdPos].m_ChrInput)
				m_YMDInfoArray[ymdPos].m_strYMD = m_strDisplay.Mid(startPos, Pos - startPos);
			m_YMDInfoArray[ymdPos].m_uiFirstCharPos = startPos;
			m_YMDInfoArray[ymdPos++].m_uiLastCharPos = Pos - startPos;
			startPos = Pos + m_Separators[sepPos++].GetLength();
		}
		if (ymdPos < m_YMDInfoArray.GetCount())
		{
			if (!m_YMDInfoArray[ymdPos].m_ChrInput)
				m_YMDInfoArray[ymdPos].m_strYMD = m_strDisplay.Right(m_strDisplay.GetLength() - startPos);
			m_YMDInfoArray[ymdPos].m_uiFirstCharPos = startPos;
			m_YMDInfoArray[ymdPos].m_uiLastCharPos = m_strDisplay.GetLength() - 1;
		}
	}
}

void CCellDateCtrl::ComputeYMDDetails()
{
	if (!m_YMDDetailsInit)
	{
// If we clear m_YMDInfoArray all the time, the structure may not contain persistent information.
// If we don't clear, there is a possibility that m_DtFormatStr has changed.
// If there is a requirement for handling case of CCellDateCtrl changing, simply also reset 
// m_YMDDetailsInit to FALSE for all instances of CCellDateCtrl each time CCellDateCtrl changes. 
		m_YMDInfoArray.RemoveAll();

		int len = m_DtFormatStr.GetLength(), pos = 1;

		if (len)
		{
			TCHAR YMDch = m_DtFormatStr[0];
			YMDInfo ymdInfo;

			for (pos = 1; pos < len; pos++)
			{
				if (m_DtFormatStr[pos] != YMDch)
				{
					if (IsYMD(YMDch))
						AddYMDInfo(ymdInfo, YMDch);
				}
				YMDch = m_DtFormatStr[pos];
			}
			if (IsYMD(m_DtFormatStr[--pos]))
				AddYMDInfo(ymdInfo, m_DtFormatStr[pos]);
		}
		m_YMDDetailsInit = TRUE;
	}
	PopulateYMDDetails();
}

void CCellDateCtrl::ComputeDisplayDate()
{
	try
	{
		int strLen;
		VERIFY(strLen = GetDateFormat(LOCALE_USER_DEFAULT, 0, &m_CellDate, m_DtFormatStr, 0, 0));
		VERIFY(GetDateFormat(LOCALE_USER_DEFAULT, 0, &m_CellDate,  m_DtFormatStr, m_strDisplay.GetBuffer(strLen), strLen));
		m_strDisplay.ReleaseBuffer();
		ComputeYMDDetails();
	}
	catch (CMemoryException &)
	{
	}
}

void CCellDateCtrl::Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText  /*= _T("")*/)
{
	CCellDropDown::Initialize(hParentWnd, pParentEnabled, strText);  

	CPopupCalendar *pPopUpCalendar = dynamic_cast<CPopupCalendar *>(m_pPopUpWnd);

	if (pPopUpCalendar)
		pPopUpCalendar->Create(m_hParentWnd, this);	

	if (strText[0])
	{
		CString str = strText;
		m_CellDate.wYear = _ttoi(str.Left(4));
		m_CellDate.wMonth = _ttoi(str.Mid(4, 2));
		m_CellDate.wDay = _ttoi(str.Right(2));
	}
	else // set default date to today if no default set
	{
		CTime DateTime = CTime::GetCurrentTime();
		m_CellDate.wDay = DateTime.GetDay();
		m_CellDate.wMonth = DateTime.GetMonth();
		m_CellDate.wYear = DateTime.GetYear();
		UpdateTextDate();
		((CConfigListCtrl*)GetWindowFromHandle())->SetItemValueFromCtrl(this, m_strText);
	}
	ComputeDisplayDate();
}

void CCellDateCtrl::UpdateTextDate()
// updates the underlying date string, as returned by control
// (in standard format YYYYMMDD)
{
	m_strText.Format(_T("%04d%02d%02d"), m_CellDate.wYear, m_CellDate.wMonth, m_CellDate.wDay);
}

void CCellDateCtrl::SetYMD(WORD Y, WORD M, WORD D)
{
	m_CellDate.wYear = Y; 
	m_CellDate.wMonth = M; 
	m_CellDate.wDay = D;
	UpdateTextDate();

	ComputeDisplayDate();
}

void CCellDateCtrl::ComputeYMDRects(CDC *pDC, const RECT &rcTxt)
{
	CSize szPreYMD, szYMD;
	CString strPreYMD;

	for (int ymdPos = 0; ymdPos < m_YMDInfoArray.GetCount(); ymdPos++)
	{
		strPreYMD = m_strDisplay.Left(m_YMDInfoArray[ymdPos].m_uiFirstCharPos);
		szPreYMD = pDC->GetTextExtent(strPreYMD);
		szYMD = pDC->GetTextExtent(m_YMDInfoArray[ymdPos].m_strYMD);
		CopyRect(&m_YMDInfoArray[ymdPos].m_rcBound, &rcTxt);
		m_YMDInfoArray[ymdPos].m_rcBound.left = Min(rcTxt.left + szPreYMD.cx, rcTxt.right);
		m_YMDInfoArray[ymdPos].m_rcBound.right = Min(m_YMDInfoArray[ymdPos].m_rcBound.left + szYMD.cx, rcTxt.right);
	}
}

BOOL CCellDateCtrl::DrawThemeDatePicker(HDC hDc, const LPRECT prcCell)
{
	BOOL bThemeDrawn = FALSE;
	HTHEME hTheme = OpenThemeData(m_hParentWnd, _T("DATEPICKER"));
		
	if (hTheme)
	{
		int				StateId;
		HRESULT			hRes = S_OK;
		// Only draw the large date button icon if enough place to draw it...
		LONG			lLargeButtonWidth = ::GetSystemMetrics(SM_CXVSCROLL) + ::GetSystemMetrics(SM_CXSMSIZE);

		if (prcCell->right - prcCell->left > lLargeButtonWidth)
		{
			bThemeDrawn = TRUE;
			m_lButtonOffset = lLargeButtonWidth;

			StateId = GetThemeStateId(DPDB_NORMAL, DPDB_HOT, DPDB_FOCUSED, DPDB_DISABLED);

			VERIFY(!(hRes = DrawThemeBackground(hTheme, hDc, DP_DATEBORDER, StateId, prcCell, NULL)));

			CopyRect(&m_rcClickRect, prcCell);
			m_rcClickRect.left = prcCell->right - m_lButtonOffset;

			StateId = GetThemeButtonStateId(IsPopupOpen(), DPSCBR_NORMAL, DPSCBR_HOT, DPSCBR_PRESSED, DPSCBR_DISABLED);
			VERIFY(!(hRes = DrawThemeBackground(hTheme, hDc, DP_SHOWCALENDARBUTTONRIGHT, StateId, &m_rcClickRect, NULL)));
		}
		else
			m_lButtonOffset = DEFAULT_BUTTON_WIDTH;

		CloseThemeData(hTheme);
	}
	return bThemeDrawn;
}

void CCellDateCtrl::DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState /*= 0*/)
{
	CBrush			Brush;
	RECT			rcTxt;
	BOOL			bHighlighted = FALSE, bThemeDrawn, bComboTheme = FALSE;
	int				iSavedDC;

	iSavedDC = pDC->SaveDC();
	
	Brush.CreateSolidBrush(GetSysColor(IsDisabled()? COLOR_BTNFACE : COLOR_WINDOW));

	pDC->FillRect(prcCell, &Brush);

	if (!(bThemeDrawn = DrawThemeDatePicker(pDC->m_hDC, prcCell)))
	{
		bThemeDrawn = DrawThemeCombobox(pDC->m_hDC, prcCell);
		bComboTheme = TRUE;
	}
  	if (uiItemState & (ODS_FOCUS | ODS_SELECTED) && !m_bActive && !IsDisabled() || (bComboTheme && IsDisabled()))
	{
		CBrush	HighlightBrush;
		CRect	rcHighlight;	
		HighlightBrush.CreateSolidBrush(GetSysColor(IsDisabled()? COLOR_BTNFACE : COLOR_HIGHLIGHT));

		CopyRect(&rcHighlight, prcCell);
		InflateRect(&rcHighlight, -::GetSystemMetrics(SM_CXFIXEDFRAME), -::GetSystemMetrics(SM_CYFIXEDFRAME)); 
	
		if (prcCell->right - prcCell->left > GetMinLegalWidth())
			rcHighlight.right -= (m_lButtonOffset - ::GetSystemMetrics(SM_CXEDGE));

		if (rcHighlight.right > rcHighlight.left)
			pDC->FillRect(&rcHighlight, &HighlightBrush);

		HighlightBrush.DeleteObject();

		bHighlighted = TRUE;
	}
	CopyRect(&rcTxt, prcCell);

	InflateRect(&rcTxt, -::GetSystemMetrics(SM_CXFIXEDFRAME), -::GetSystemMetrics(SM_CYFIXEDFRAME));

	rcTxt.right -= m_lButtonOffset;

	SelectFont(pDC);

	ComputeYMDRects(pDC, rcTxt);

	if (!m_bActive)
	{
		pDC->SetTextColor(GetSysColor(IsDisabled()? COLOR_GRAYTEXT : bHighlighted? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
		pDC->DrawText(m_strDisplay, &rcTxt, DT_LEFT | DT_BOTTOM | DT_END_ELLIPSIS);
	}
	else
	{
		CBrush	HighlightBrush;
		int sepPos, Pos = 0;
		RECT rcSep;
		CSize szPreSep, szSep;

		HighlightBrush.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));

		if (m_YMDActPos != -1)
			pDC->FillRect(&m_YMDInfoArray[m_YMDActPos].m_rcBound, &HighlightBrush);

		HighlightBrush.DeleteObject();
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
			
		for (sepPos = 0; sepPos < m_Separators.GetCount(); sepPos++)
		{
			Pos = m_strDisplay.Find(m_Separators[sepPos], Pos); 
			CopyRect(&rcSep, &rcTxt);
			szPreSep = pDC->GetTextExtent(m_strDisplay.Left(Pos));
			szSep = pDC->GetTextExtent(m_Separators[sepPos]);
			rcSep.left = Min(rcTxt.left + szPreSep.cx, rcTxt.right);
			rcSep.right = Min(rcSep.left + szSep.cx, rcTxt.right);
			pDC->DrawText(m_Separators[sepPos], &rcSep, DT_LEFT | DT_BOTTOM);
			Pos += m_Separators[sepPos].GetLength();
		}
		for (int ymdPos = 0; ymdPos < m_YMDInfoArray.GetCount(); ymdPos++)
		{
			pDC->SetTextColor(GetSysColor((m_YMDActPos == ymdPos)? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));		
			pDC->DrawText(m_YMDInfoArray[ymdPos].m_strYMD, &m_YMDInfoArray[ymdPos].m_rcBound, DT_LEFT | DT_BOTTOM);
		}
	}

	if (!bThemeDrawn)
		CCellDropDown::DrawCtrl(pDC, prcCell, uiItemState);

	Brush.DeleteObject();
	pDC->RestoreDC(iSavedDC);
}

int CCellDateCtrl::GetMinWidth()
{
	CString				strText;
	CSize				szSize;
	int					iMinWidth = 0; 

	CDC *pDC = GetWindowFromHandle()->GetDC();

	if (pDC)
	{
		SelectFont(pDC);

		strText = m_strDisplay + _T("i"); // Text is not neatly aligned on left hand side. 
		szSize = pDC->GetTextExtent(strText);
		iMinWidth = szSize.cx + CCellDropDown::GetMinWidth(); 
	}
	return iMinWidth;
}

void CCellDateCtrl::ValidateYMDItem()
{
	if (m_YMDActPos != -1 && m_YMDInfoArray[m_YMDActPos].m_ChrInput == TRUE)
	{
		WORD wYMD = (WORD)_ttoi(m_YMDInfoArray[m_YMDActPos].m_strYMD);

		if (m_YMDInfoArray[m_YMDActPos].m_ymd == Year)
		{
			if (wYMD < 100)
			{
				if (wYMD >= 30)
					wYMD += 1900;
				else
					wYMD += 2000;
			}
			if (wYMD >= MIN_YEAR)
				m_CellDate.wYear = wYMD;
		}
		else if (m_YMDInfoArray[m_YMDActPos].m_ymd == Month)
			m_CellDate.wMonth = wYMD;
		else if (m_YMDInfoArray[m_YMDActPos].m_ymd == Day)
			m_CellDate.wDay = wYMD;

		m_YMDInfoArray[m_YMDActPos].m_ChrInput = FALSE;
		CorrectDay();
		UpdateTextDate();
		ComputeDisplayDate();
	}
}

BOOL CCellDateCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CCellDropDown::OnLButtonDown(nFlags, point);

	int ymdPos = 0, leftmost = -1;
	BOOL bOnRect = FALSE;

	if (PtInRect(&m_rcTextArea, point))
	{				
		while (ymdPos < m_YMDInfoArray.GetCount() && !bOnRect)
		{
			if (PtInRect(&m_YMDInfoArray[ymdPos].m_rcBound, point))
			{
				ValidateYMDItem();
				m_YMDActPos = ymdPos;
				bOnRect = TRUE;
			}
			else if (point.x > m_YMDInfoArray[ymdPos].m_rcBound.right)
				leftmost = ymdPos;
	
			ymdPos++;
		}
		if (!bOnRect && leftmost != -1)
		{
			ValidateYMDItem();
			m_YMDActPos = leftmost;
		}
	}
	return TRUE;
}

void CCellDateCtrl::CorrectDay()
{
	if (m_YMDInfoArray[m_YMDActPos].m_ymd == Year)
	{
		if (m_CellDate.wDay == 29)
			m_CellDate.wDay = DateUtils::LastDay(m_CellDate.wMonth, m_CellDate.wYear);
	}
	else if (m_YMDInfoArray[m_YMDActPos].m_ymd == Month)
	{
		m_CellDate.wDay = Min(m_CellDate.wDay, (WORD)DateUtils::LastDay(m_CellDate.wMonth, m_CellDate.wYear));
	}
}

BOOL CCellDateCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bRetVal = TRUE;

	if (nChar == VK_LEFT)
	{
		bRetVal = FALSE;
		ValidateYMDItem();
		--m_YMDActPos;
		if (m_YMDActPos == -1)
			m_YMDActPos = m_YMDInfoArray.GetSize() - 1;
	}
	else if (nChar == VK_RIGHT)
	{
		bRetVal = FALSE;
		ValidateYMDItem();
		++m_YMDActPos;
		if (m_YMDActPos == m_YMDInfoArray.GetSize())
			m_YMDActPos = 0;
	}
	else if (nChar == VK_DOWN && m_YMDActPos != -1)
	{
		if (m_YMDInfoArray[m_YMDActPos].m_ymd == Year)
		{
			if (m_CellDate.wYear > MIN_YEAR)
				m_CellDate.wYear--;
		}
		else if (m_YMDInfoArray[m_YMDActPos].m_ymd == Month)
		{
			m_CellDate.wMonth--;

			if (m_CellDate.wMonth == 0)
				m_CellDate.wMonth = 12;
		}
		else if (m_YMDInfoArray[m_YMDActPos].m_ymd == Day)
		{
			m_CellDate.wDay--;

			if (m_CellDate.wDay == 0)
				m_CellDate.wDay = DateUtils::LastDay(m_CellDate.wMonth, m_CellDate.wYear);
		}
		CorrectDay();
		UpdateTextDate();
		ComputeDisplayDate();
		bRetVal = FALSE;
	}
	else if (nChar == VK_UP && m_YMDActPos != -1)
	{
		if (m_YMDInfoArray[m_YMDActPos].m_ymd == Year)
		{
			if (m_CellDate.wYear < MAX_YEAR)
				m_CellDate.wYear++;
		}
		else if (m_YMDInfoArray[m_YMDActPos].m_ymd == Month)
		{
			m_CellDate.wMonth++;

			if (m_CellDate.wMonth == 13)
				m_CellDate.wMonth = 1;
		}
		else if (m_YMDInfoArray[m_YMDActPos].m_ymd == Day)
		{
			m_CellDate.wDay++;

			if (m_CellDate.wDay > DateUtils::LastDay(m_CellDate.wMonth, m_CellDate.wYear))
				m_CellDate.wDay = 1;
		}
		CorrectDay();
		UpdateTextDate();
		ComputeDisplayDate();
		bRetVal = FALSE;
	}
	else if (isdigit(nChar))
	{
		// Note: not disallowed the non digit displays (ddd, dddd, MMM, MMMM)
		WORD wNewDigit = nChar - _T('0');
		WORD wOldDigits = (WORD)_ttoi(m_YMDInfoArray[m_YMDActPos].m_strYMD);
		WORD wHighVal = 0;
				
		if (m_YMDInfoArray[m_YMDActPos].m_ymd == Year)
			wHighVal = MAX_YEAR;
		else if (m_YMDInfoArray[m_YMDActPos].m_ymd == Month)
			wHighVal = 12;
		else if (m_YMDInfoArray[m_YMDActPos].m_ymd == Day)
			wHighVal = DateUtils::LastDay(m_CellDate.wMonth, m_CellDate.wYear);

		if (m_YMDInfoArray[m_YMDActPos].m_ChrInput && (wOldDigits*10 + wNewDigit <= wHighVal))
			m_YMDInfoArray[m_YMDActPos].m_strYMD += TCHAR(nChar);
		else
		{
			m_YMDInfoArray[m_YMDActPos].m_ChrInput = TRUE;
			m_YMDInfoArray[m_YMDActPos].m_strYMD = TCHAR(nChar);
		}
		bRetVal = FALSE;
	}
	else if (nChar == VK_F4 )
	{
		OnPressButton(nFlags, CPoint(0,0));
		CWnd *p = m_pPopUpWnd->GetFocus();
		p->SetCapture();
	}
	return bRetVal;
}

void CCellDateCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CCellDropDown::OnKillFocus(pNewWnd);
}

void CCellDateCtrl::OnKillActive()
{
	ValidateYMDItem();
	CCellDropDown::OnKillActive();
}

void CCellDateCtrl::AddToCtrlTypeStyle(DWORD dwFlags)
{
	m_dwDateCtrlStyle |= dwFlags;
}

void CCellDateCtrl::RemoveFromCtrlTypeStyle(DWORD dwFlags)
{
	m_dwDateCtrlStyle &= ~dwFlags;
}

LONG CCellDateCtrl::GetStyle()
{
	return m_dwDateCtrlStyle | m_dwStyle;
}

void CCellDateCtrl::OnOpenDropDown()
{
	ValidateYMDItem();

	CPopupCalendar *pPopUpCalendar = dynamic_cast<CPopupCalendar *>(m_pPopUpWnd);

	if (pPopUpCalendar)
		pPopUpCalendar->OpenDropDown(&m_CellDate);
}

void CCellDateCtrl::GetDropDownBoundingRect(RECT &rc, BOOL downwards /*= TRUE*/)
{
	CPopupCalendar *pPopUpCalendar = dynamic_cast<CPopupCalendar *>(m_pPopUpWnd);

	if (pPopUpCalendar)
		pPopUpCalendar->GetBoundingRect(m_rcBounding, rc, downwards);
}

void CCellDateCtrl::OnSelCloseDropDown(LPARAM lParam)
{
	OnSelChangeDropDown(lParam);
}

void CCellDateCtrl::OnSelChangeDropDown(LPARAM lParam)
{
	int iDay, iMonth, iYear;
	DateUtils::GetDMYFromDWord(lParam, iDay, iMonth, iYear);
	SetYMD((WORD)iYear, (WORD)iMonth, (WORD)iDay);
}

void CCellDateCtrl::OnThemeChanged()
{
	m_lButtonOffset = DEFAULT_BUTTON_WIDTH;

	CPopupCalendar *pPopUpCalendar = dynamic_cast<CPopupCalendar *>(m_pPopUpWnd);

	if (pPopUpCalendar)
		pPopUpCalendar->OnThemeChanged();
}