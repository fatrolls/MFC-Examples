#include "StdAfx.h"
#include "CellTimeCtrl.h"

CString CCellTimeCtrl::m_SystemTimeFormat = _T("");
CString CCellTimeCtrl::m_AM = _T(""); 
CString CCellTimeCtrl::m_PM = _T("");

BOOL CCellTimeCtrl::m_SystemTimeDetailsInitialized = FALSE;

BOOL CALLBACK CCellTimeCtrl::InitSystemTimeFormatProc(LPTSTR lpSystemTimeFormat)
{
	m_SystemTimeFormat = lpSystemTimeFormat;
	return FALSE;
}

void CCellTimeCtrl::InitializeSystemTimeDetails()
{
	VERIFY(EnumTimeFormats(&CCellTimeCtrl::InitSystemTimeFormatProc, LOCALE_USER_DEFAULT, 0));
	TCHAR AM_PM[20]; // Different for different versions of Windows - varies from 9 (ME, 95,98,NT4, 2000) to 15
	VERIFY(GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_S1159, AM_PM, 19));
	m_AM = AM_PM;
	VERIFY(GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_S2359, AM_PM, 19));
	m_PM = AM_PM;
}

CCellTimeCtrl::CCellTimeCtrl(void) : m_TimeFormat(), m_pActiveCellTimeInfo(0)
{
	if (!m_SystemTimeDetailsInitialized)
	{
		m_SystemTimeDetailsInitialized = TRUE;
		InitializeSystemTimeDetails();
	}
	GetLocalTime(&m_Time);
	UpdateTextTime();
	PopulateArrayTimeTags();
}

CCellTimeCtrl::~CCellTimeCtrl(void)
{
	m_CellTimeInfoArray.RemoveAll();
}

int CCellTimeCtrl::GetMinWidth()
{
	CString				strText;
	CSize				szSize;
	int					iMinWidth = 0; 

	CDC *pDC = GetWindowFromHandle()->GetDC();

	if (pDC)
	{
		SelectFont(pDC);
		strText = /*m_strDisplay +*/ _T("i"); // Text is not neatly aligned on left hand side. 
		szSize = pDC->GetTextExtent(strText);
		iMinWidth = szSize.cx + DEFAULT_BUTTON_WIDTH; 
	}
	return iMinWidth;
}

void CCellTimeCtrl::SetTimeFormat(const CString& NewTimeFomat)
{
	m_TimeFormat = NewTimeFomat;
	PopulateArrayTimeTags();
	PopulateArrayTimeValues();
}

void CCellTimeCtrl::PopulateArrayTimeTags()
{
	const CString& TimeFormat = GetTimeFormat();
	int Idx = 0, Len = 0;	
	
	m_CellTimeInfoArray.RemoveAll();
	
	while (Idx != TimeFormat.GetLength())
	{
		CellTimeInfo TimeInfo;

		if (IsCharTag(TimeFormat[Idx]))
		{
			if (Idx + 1 != TimeFormat.GetLength() && TimeFormat[Idx + 1] == TimeFormat[Idx])
			{
				switch (TimeFormat[Idx])
				{
					case CAPHOUR_CH:
						TimeInfo.m_TimeTagType = HHour;
					break;

					case HOUR_CH:
						TimeInfo.m_TimeTagType = hhour;
					break;

					case MIN_CH:
						TimeInfo.m_TimeTagType = mminute;
					break;

					case SEC_CH:
						TimeInfo.m_TimeTagType = ssecond;
					break;

					case T_CH:
						TimeInfo.m_TimeTagType = tt;
					break;
				}
				Idx++;
			}
			else
			{
				switch (TimeFormat[Idx])
				{
					case CAPHOUR_CH:
						TimeInfo.m_TimeTagType = Hour;
					break;

					case HOUR_CH:
						TimeInfo.m_TimeTagType = hour;
					break;

					case MIN_CH:
						TimeInfo.m_TimeTagType = minute;
					break;

					case SEC_CH:
						TimeInfo.m_TimeTagType = second;
					break;

					case T_CH:
						TimeInfo.m_TimeTagType = t;
					break;
				}
			}
			Idx++;
		}
		else
		{
			TimeInfo.m_TimeTagType = separator;
			Len = 1;

			while (Idx + Len != TimeFormat.GetLength() && !IsCharTag(TimeFormat[Idx + Len]))
				Len++;

			TimeInfo.m_Value = TimeFormat.Mid(Idx, Len);

			Idx += Len;
		}
		TimeInfo.m_bIsInput = FALSE;
		m_CellTimeInfoArray.Add(TimeInfo);
	}
	Idx = 0;

	while (Idx < m_CellTimeInfoArray.GetCount() && m_CellTimeInfoArray[Idx].m_TimeTagType == separator)
		Idx++;

	m_pActiveCellTimeInfo = &m_CellTimeInfoArray[Idx];
}

void CCellTimeCtrl::UpdateCellTimeInfoValue(CellTimeInfo &CTI)
{
	WORD TwelveHour;

	if (CTI.m_TimeTagType != separator)
	{
		if ((CTI.m_TimeTagType != tt)
			&& (CTI.m_TimeTagType != t))
		{
			CString Format;
			switch (CTI.m_TimeTagType)
			{
				case HHour: case hhour: case mminute: case ssecond:
					Format = _T("%02d");
				break;
				default:
					Format = _T("%2d");
			}
			switch (CTI.m_TimeTagType)
			{
				case HHour:
				case Hour:
					CTI.m_Value.Format(Format, m_Time.wHour);
				break;

				case hhour:
				case hour:
					TwelveHour = m_Time.wHour;
					if (m_Time.wHour == 0)
						TwelveHour += 12;
					else if (m_Time.wHour > 12)
						TwelveHour -= 12;

					CTI.m_Value.Format(Format, TwelveHour);
				break;

				case mminute:
				case minute:
					CTI.m_Value.Format(Format, m_Time.wMinute);
				break;

				case ssecond:
				case second:
					CTI.m_Value.Format(Format, m_Time.wSecond);
				break;
			}
		}
		else
		{
			if (CTI.m_TimeTagType == tt)
				CTI.m_Value = (m_Time.wHour >= 12)? m_PM : m_AM;
			else
				CTI.m_Value = (m_Time.wHour >= 12)? m_PM[0] : m_AM[0];
		}
	}
}

void CCellTimeCtrl::PopulateArrayTimeValues()
{
	int Idx; 

	for (Idx = 0; Idx < m_CellTimeInfoArray.GetCount(); Idx++)
		UpdateCellTimeInfoValue(m_CellTimeInfoArray[Idx]);
}

void CCellTimeCtrl::Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText  /*= _T("")*/)
{
	CCellSpinCtrl::Initialize(hParentWnd, pParentEnabled, strText);  

	if (_tcslen(strText) == 6)
	{
		CString str = strText;
		m_Time.wHour = _ttoi(str.Left(2));
		m_Time.wMinute = _ttoi(str.Mid(2, 2));
		m_Time.wSecond = _ttoi(str.Right(2));
	}
	UpdateTextTime();
	PopulateArrayTimeValues();
}

void CCellTimeCtrl::ComputeCellTimeInfoRect(CDC *pDC, CellTimeInfo &CTI, LONG &Incr)
{
	CTI.m_rcBound.top = m_rcTxtArea.top; 
	CTI.m_rcBound.bottom = m_rcTxtArea.bottom;

	if (m_rcTxtArea.left + Incr < m_rcTxtArea.right)
		CTI.m_rcBound.left = m_rcTxtArea.left + Incr;
	else
		CTI.m_rcBound.right = m_rcTxtArea.left;

	CSize szSize = CTI.m_TimeTagType == separator || CTI.m_TimeTagType == tt || CTI.m_TimeTagType == t? pDC->GetTextExtent(CTI.m_Value) : pDC->GetTextExtent(_T("00"));
	
	Incr += szSize.cx; 

	if (m_rcTxtArea.left + Incr < m_rcTxtArea.right)
		CTI.m_rcBound.right = m_rcTxtArea.left + Incr;
	else
		CTI.m_rcBound.right = m_rcTxtArea.left;
}

void CCellTimeCtrl::DrawTextArea(CDC *pDC, const LPRECT prcCell, BOOL bHighlighted)
{
	SelectFont(pDC);
	int Idx;
	LONG Incr = 0;

	if (bHighlighted || !m_bActive)
	{
		pDC->SetTextColor(GetSysColor(IsDisabled()? COLOR_GRAYTEXT : bHighlighted? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));

		for (Idx = 0; Idx < m_CellTimeInfoArray.GetCount(); Idx++)
		{
			ComputeCellTimeInfoRect(pDC, m_CellTimeInfoArray[Idx], Incr);
			pDC->DrawText(m_CellTimeInfoArray[Idx].m_Value, &m_CellTimeInfoArray[Idx].m_rcBound, DT_RIGHT | DT_BOTTOM | DT_END_ELLIPSIS);
		}
	}
	else
	{
		for (Idx = 0; Idx < m_CellTimeInfoArray.GetCount(); Idx++)
		{
			ComputeCellTimeInfoRect(pDC, m_CellTimeInfoArray[Idx], Incr);

			if (m_pActiveCellTimeInfo == &m_CellTimeInfoArray[Idx])
			{
				CBrush	HighlightBrush;
				HighlightBrush.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
					
				if (m_CellTimeInfoArray[Idx].m_rcBound.right > m_CellTimeInfoArray[Idx].m_rcBound.left)
					pDC->FillRect(&m_CellTimeInfoArray[Idx].m_rcBound, &HighlightBrush);

				HighlightBrush.DeleteObject();
				pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
			}
			else
				pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
				
			pDC->DrawText(m_CellTimeInfoArray[Idx].m_Value, &m_CellTimeInfoArray[Idx].m_rcBound, DT_RIGHT | DT_BOTTOM | DT_END_ELLIPSIS);
		}
	}
}

BOOL CCellTimeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bRetVal = CCellSpinCtrl::OnKeyDown(nChar, nRepCnt, nFlags);

	if (!bRetVal)
		return FALSE;

	if (nChar == VK_LEFT)
	{
		if (m_pActiveCellTimeInfo)
		{
			OnKillActiveCellInput();
			do
			{
				CellTimeInfo* pPt = (CellTimeInfo*) m_CellTimeInfoArray.GetData();

				if (pPt == m_pActiveCellTimeInfo)
					m_pActiveCellTimeInfo = pPt + m_CellTimeInfoArray.GetCount() - 1;
				else
					m_pActiveCellTimeInfo--;
			}
			while (m_pActiveCellTimeInfo->m_TimeTagType == separator);
		}
		bRetVal = FALSE;
	}
	else if (nChar == VK_RIGHT)
	{
		if (m_pActiveCellTimeInfo)
		{
			OnKillActiveCellInput();
			do
			{
				CellTimeInfo* pPt = (CellTimeInfo*) m_CellTimeInfoArray.GetData();

				if (m_pActiveCellTimeInfo == pPt + m_CellTimeInfoArray.GetCount() - 1)
					m_pActiveCellTimeInfo = pPt;
				else
					m_pActiveCellTimeInfo++;
			}
			while (m_pActiveCellTimeInfo->m_TimeTagType == separator);
		}
		bRetVal = FALSE;
	}
	return bRetVal;
}

BOOL CCellTimeCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bRetVal = CCellSpinCtrl::OnChar(nChar, nRepCnt, nFlags);

	if (isdigit(nChar) && IsNumericField(*m_pActiveCellTimeInfo))
	{
		WORD wNewDigit = nChar - _T('0');
		WORD wOldDigits = (WORD)_ttoi(m_pActiveCellTimeInfo->m_Value);
	
		if (m_pActiveCellTimeInfo->m_bIsInput && (wOldDigits*10 + wNewDigit >= MinTimeValue(*m_pActiveCellTimeInfo)) 
											  && (wOldDigits*10 + wNewDigit <= MaxTimeValue(*m_pActiveCellTimeInfo)))
		{
			m_pActiveCellTimeInfo->m_Value += TCHAR(nChar);
			m_pActiveCellTimeInfo->m_bIsInput = FALSE; // Finished input after 2 chars - to see why necessary:
				// in hh format: type '1', '3' and '1', will have a string "011" and not "11" as expected. 

			// special case for h and hh tags:
			if (m_pActiveCellTimeInfo->m_TimeTagType == hhour || m_pActiveCellTimeInfo->m_TimeTagType == hour)
			{
				WORD wNewEntryDigits = (WORD)_ttoi(m_pActiveCellTimeInfo->m_Value);

				if (!wNewEntryDigits)
					m_pActiveCellTimeInfo->m_Value = _T("12");
				else if (wNewEntryDigits > 12)
				{
					m_Time.wHour = wNewEntryDigits;
					UpdateTextTime();
					PopulateArrayTimeValues();
				}
			}
		}
		else
		{
			m_pActiveCellTimeInfo->m_bIsInput = TRUE;
			m_pActiveCellTimeInfo->m_Value = TCHAR(nChar);
		}
		bRetVal = FALSE;
	}
	else if (m_pActiveCellTimeInfo->m_TimeTagType == tt || m_pActiveCellTimeInfo->m_TimeTagType == t)
	{
		if (toupper(nChar) == toupper(m_AM[0]))
		{
			if (m_Time.wHour >= 12)
			{
				m_Time.wHour -= 12;
				UpdateTextTime();
			}
		
			PopulateArrayTimeValues();
			bRetVal = FALSE;
		}
		else if (toupper(nChar) == toupper(m_PM[0]))
		{
			if (m_Time.wHour < 12)
			{
				m_Time.wHour += 12;
				UpdateTextTime();
			}
		
			PopulateArrayTimeValues();
			bRetVal = FALSE;
		}
	}
	return bRetVal;
}

void CCellTimeCtrl::OnKillActiveCellInput()
{
	m_pActiveCellTimeInfo->m_bIsInput = FALSE;
	WORD wValue = (WORD)_ttoi(m_pActiveCellTimeInfo->m_Value);
	UpdateTimeValue(m_pActiveCellTimeInfo->m_TimeTagType, wValue);
	PopulateArrayTimeValues();
}

void CCellTimeCtrl::OnKillActive()
{
	CCellSpinCtrl::OnKillActive();
	OnKillActiveCellInput();
}

BOOL CCellTimeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL retVal = CCellSpinCtrl::OnLButtonDown(nFlags, point);

	if (retVal)
	{
		int Idx = -1;
		BOOL Found = FALSE;

		while (!Found && ++Idx < m_CellTimeInfoArray.GetCount())
		{
			if (PtInRect(&m_CellTimeInfoArray[Idx].m_rcBound, point))
			{
				m_pActiveCellTimeInfo = &m_CellTimeInfoArray[Idx];
				Found = TRUE;
			}
		}
		if (m_pActiveCellTimeInfo->m_TimeTagType == separator)
		{
			CellTimeInfo* pPt = (CellTimeInfo*) m_CellTimeInfoArray.GetData();

			if (m_pActiveCellTimeInfo == pPt)
				m_pActiveCellTimeInfo = pPt + m_CellTimeInfoArray.GetCount() - 1;
			else
				m_pActiveCellTimeInfo--;
		}
		if (!Found && PtInRect(&m_rcTxtArea, point))
		{
			CellTimeInfo* pPt = (CellTimeInfo*) m_CellTimeInfoArray.GetData();
			m_pActiveCellTimeInfo = pPt + m_CellTimeInfoArray.GetCount() - 1;
		}
	}
	return retVal;
}

void CCellTimeCtrl::UpdateTextTime()
// updates the underlying time string, as returned by control
// (in standard format HHmmss)
{
	m_strText.Format(_T("%02d%02d%02d"), m_Time.wHour, m_Time.wMinute, m_Time.wSecond);
}

void CCellTimeCtrl::UpdateTimeValue(TimeTagType TTT, int Value)
{
	switch (TTT)
	{
		case HHour:
		case Hour:
			m_Time.wHour = Value;
		break;

		case hhour:
		case hour:
			if (m_Time.wHour >= 12)
				m_Time.wHour = (Value == 12)? 12 : 12 + Value;
			else
				m_Time.wHour = (Value == 12)? 0 : Value;
		break;

		case mminute:
		case minute:
			m_Time.wMinute = Value;
		break;
		case ssecond:
		case second:
			m_Time.wSecond = Value;
		break;
	}
	UpdateTextTime();
}

void CCellTimeCtrl::IncrementTimeValue(TimeTagType TTT, int Value)
{
	Value++;

	switch (TTT)
	{
		case HHour:
		case Hour:
			if (Value == 24)
				Value = 0;
		break;

		case hhour:
		case hour:
			if (Value == 13)
				Value = 1;
		break;

		case mminute:
		case minute:
		case ssecond:
		case second:
			if (Value == 60)
				Value = 0;
		break;
	}
	UpdateTimeValue(TTT, Value);
}

void CCellTimeCtrl::DecrementTimeValue(TimeTagType TTT, int Value)
{
	Value--;

	switch (TTT)
	{
		case HHour:
		case Hour:
			if (Value == -1)
				Value = 23;
		break;

		case hhour:
		case hour:
			if (Value == 0)
				Value = 12;
		break;

		case mminute:
		case minute:
		case ssecond:
		case second:
			if (Value == -1)
				Value = 59;
		break;
	}
	UpdateTimeValue(TTT, Value);
}

void CCellTimeCtrl::IncrementTime(BOOL Increment /*= TRUE*/)
{
	if (m_pActiveCellTimeInfo)
	{
		OnKillActiveCellInput();

		if (m_pActiveCellTimeInfo->m_TimeTagType == t || m_pActiveCellTimeInfo->m_TimeTagType == tt)
		{
			if (m_pActiveCellTimeInfo->m_Value[0] == m_AM[0])
				m_Time.wHour += 12;
			else
				m_Time.wHour -= 12;

			UpdateTextTime();
		}
		else
		{
			int Value = _ttoi((LPCTSTR)m_pActiveCellTimeInfo->m_Value);

			if (Increment)
				IncrementTimeValue(m_pActiveCellTimeInfo->m_TimeTagType, Value);
			else
				DecrementTimeValue(m_pActiveCellTimeInfo->m_TimeTagType, Value);
		}
		PopulateArrayTimeValues();

		CWnd *p = GetWindowFromHandle();

		if (p)
			p->InvalidateRect(&m_rcTxtArea, FALSE);
	}
}

void CCellTimeCtrl::OnIncrement()
{
	IncrementTime();
}

void CCellTimeCtrl::OnDecrement()
{
	IncrementTime(FALSE);
}