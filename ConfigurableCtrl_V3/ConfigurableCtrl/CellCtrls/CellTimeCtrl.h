#pragma once

#include "CellSpinCtrl.h"
#include "..\utilities.h"

#define CAPHOUR_CH		_T('H')
#define HOUR_CH			_T('h')
#define MIN_CH			_T('m')
#define SEC_CH			_T('s')
#define T_CH			_T('t')

class CCellTimeCtrl : public CCellSpinCtrl
{
	static BOOL		m_SystemTimeDetailsInitialized;
	static CString	m_SystemTimeFormat;
	static CString	m_AM, m_PM; 
	static BOOL CALLBACK InitSystemTimeFormatProc(LPTSTR lpSystemTimeFormat);
	static void InitializeSystemTimeDetails();
	CString	m_TimeFormat;

	inline const CString& GetTimeFormat() const;
	inline BOOL IsCharTag(TCHAR chr) const;
public:
	CCellTimeCtrl(void);
	virtual ~CCellTimeCtrl(void);
	void Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText  = _T(""));
	void SetTimeFormat(const CString& NewTimeFomat);
	int GetMinWidth();
protected:
	virtual void OnIncrement();
	virtual void OnDecrement();
	virtual void DrawTextArea(CDC *pDC, const LPRECT prcCell, BOOL bHighlighted);
	virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnKillActive();

	enum TimeTagType {HHour, Hour, hhour, hour, mminute, minute, ssecond, second, tt, t, separator};
	struct CellTimeInfo
	{
		TimeTagType					m_TimeTagType;
		CString						m_Value;
		RECT						m_rcBound;
		BOOL						m_bIsInput;
	};
	CArray<CellTimeInfo> m_CellTimeInfoArray;

	inline WORD MinTimeValue(const CellTimeInfo &CTI) const;
	inline WORD MaxTimeValue(const CellTimeInfo &CTI) const;
	inline BOOL IsNumericField(const CellTimeInfo &CTI) const;

	void IncrementTime(BOOL Increment = TRUE);
	void UpdateTimeValue(TimeTagType TTT, int Value);
	void PopulateArrayTimeTags();
	void PopulateArrayTimeValues();
	void UpdateCellTimeInfoValue(CellTimeInfo &CTI);
	void IncrementTimeValue(TimeTagType TTT, int Value);
	void DecrementTimeValue(TimeTagType TTT, int Value);
	void OnKillActiveCellInput();
	void UpdateTextTime();
	void ComputeCellTimeInfoRect(CDC *pDC, CellTimeInfo &CTI, LONG &Incr);

	SYSTEMTIME m_Time;
	CellTimeInfo				*m_pActiveCellTimeInfo;  
};

inline const CString& CCellTimeCtrl::GetTimeFormat() const
{
	return (m_TimeFormat.IsEmpty()? m_SystemTimeFormat : m_TimeFormat);
}

inline BOOL CCellTimeCtrl::IsCharTag(TCHAR chr) const
{
	return chr == CAPHOUR_CH || chr == HOUR_CH || chr == MIN_CH || chr == SEC_CH || chr == T_CH;
}

inline WORD CCellTimeCtrl::MinTimeValue(const CellTimeInfo &CTI) const
{
	return 0;
}

inline WORD CCellTimeCtrl::MaxTimeValue(const CellTimeInfo &CTI) const
{
	switch (CTI.m_TimeTagType)
	{
		case HHour:
		case Hour:
		case hhour:
		case hour:
			return 23;
		default:
			return 59;
	}
}

inline BOOL CCellTimeCtrl::IsNumericField(const CellTimeInfo &CTI) const
{
	return (CTI.m_TimeTagType == HHour || CTI.m_TimeTagType == Hour || CTI.m_TimeTagType == hhour || CTI.m_TimeTagType == hour
		|| CTI.m_TimeTagType == mminute || CTI.m_TimeTagType == minute || CTI.m_TimeTagType == ssecond || CTI.m_TimeTagType == second);
}

