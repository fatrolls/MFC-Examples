#pragma once

#include "CellDropDown.h"

#define DAY_CH				_T('d')
#define MONTH_CH			_T('M')
#define YEAR_CH				_T('y')
#define MIN_YEAR			1750
#define MAX_YEAR			9999

enum YMD {Year, Month, Day};

struct YMDInfo
{
	YMD m_ymd;
	RECT m_rcBound;
	CString m_strYMD;
	UINT m_uiFirstCharPos, m_uiLastCharPos;
	BOOL m_ChrInput;

	YMDInfo() : m_ymd(Year), m_strYMD(), m_uiFirstCharPos(0), m_uiLastCharPos(0), m_ChrInput(FALSE)
	{
		::ZeroMemory(&m_rcBound, sizeof(RECT)); 		
	}
};

class CCellDateCtrl : public CCellDropDown  
{
public:
	static void SetDateFormat(const CString &strDateFormat);

	CCellDateCtrl();
	virtual ~CCellDateCtrl();
	virtual void DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState = 0);
	virtual int GetMinWidth();
	virtual void AddToCtrlTypeStyle(DWORD dwFlags);
	virtual void RemoveFromCtrlTypeStyle(DWORD dwFlags);
	virtual LONG GetStyle();
	virtual void OnOpenDropDown();
	virtual void GetDropDownBoundingRect(RECT &rc, BOOL downwards /*= TRUE*/);
	virtual void OnSelCloseDropDown(LPARAM lParam);
	virtual void OnSelChangeDropDown(LPARAM lParam);
	virtual void OnKillActive();
	void SetYMD(WORD Y, WORD M, WORD D);
	virtual void OnThemeChanged();
protected:
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText = _T(""));
	BOOL DrawThemeDatePicker(HDC hDc, const LPRECT prcCell);
private:
	static DWORD	m_dwDateCtrlStyle;
	static BOOL		m_DateFormatInitialized, m_StartSeparator;
	static CString  m_DtFormatStr;
	static CStringArray	m_Separators;
	static BOOL CALLBACK InitDateFormatProc(LPTSTR lpDateFormatString, CALID CalId);
	inline static BOOL IsYMD(TCHAR tchar);
	static void ComputeSeparators();
	static void InitializeDateFormat();
	
	CArray<YMDInfo> m_YMDInfoArray;
	int m_YMDActPos;
	SYSTEMTIME m_CellDate;
	BOOL m_YMDDetailsInit;
	CString	m_strDisplay;

	void ValidateYMDItem();
	void ComputeDisplayDate();
	void AddYMDInfo(YMDInfo &ymdInfo, TCHAR YMDch);
	void ComputeYMDDetails();
	void PopulateYMDDetails();
	void ComputeYMDRects(CDC *pDC, const RECT &rcTxt);
	void CorrectDay();
	void UpdateTextDate();
	virtual void OnKillFocus(CWnd* pNewWnd);
};

BOOL CCellDateCtrl::IsYMD(TCHAR tchar)
{
	return tchar == DAY_CH || tchar == MONTH_CH || tchar == YEAR_CH;
}