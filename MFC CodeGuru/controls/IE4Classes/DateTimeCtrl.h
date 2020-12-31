#ifndef __DTCTL_H__
#define __DTCTL_H__

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

#ifndef __AFXDISP_H__
  #include <afxdisp.h>
#endif


/////////////////////////////////////////////////////////////////////////////

  class CImageList;
  class CMonthCalCtrl;
  class CDateTimeCtrl;

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtrl

class CDateTimeCtrl : public CWnd
{
  DECLARE_DYNAMIC(CDateTimeCtrl)

// Constructors
public:
  CDateTimeCtrl();
  BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Attributes
public:
  COLORREF GetMonthCalColor(int iColor) const
  { ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, DTM_GETMCCOLOR, (WPARAM) iColor, 0); }
  COLORREF SetMonthCalColor(int iColor, COLORREF ref)
  { ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, DTM_SETMCCOLOR, (WPARAM) iColor, (LPARAM) ref); }
  BOOL SetFormat(LPCTSTR pstrFormat)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, DTM_SETFORMAT, 0, (LPARAM) pstrFormat); }
  CMonthCalCtrl* GetMonthCalCtrl() const
  { ASSERT(::IsWindow(m_hWnd)); return (CMonthCalCtrl*) CWnd::FromHandle((HWND) ::SendMessage(m_hWnd, DTM_GETMONTHCAL, 0, 0)); }
  CFont* GetMonthCalFont() const
  { ASSERT(::IsWindow(m_hWnd)); return CFont::FromHandle((HFONT) ::SendMessage(m_hWnd, DTM_GETMCFONT, 0, 0)); }
  void SetMonthCalFont(HFONT hFont, BOOL bRedraw = TRUE)
  { ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, DTM_SETMCFONT, (WPARAM) hFont, MAKELONG(bRedraw, 0)); }
  BOOL SetRange(const COleDateTime* pMinRange, const COleDateTime* pMaxRange);
  DWORD GetRange(COleDateTime* pMinRange, COleDateTime* pMaxRange) const;
  BOOL SetRange(const CTime* pMinRange, const CTime* pMaxRange);
  DWORD GetRange(CTime* pMinRange, CTime* pMaxRange) const;

// Operations
public:
  BOOL SetTime(const CTime* pTimeNew);
  DWORD GetTime(CTime& timeDest) const;
  BOOL SetTime(const COleDateTime& timeNew);
  BOOL GetTime(COleDateTime& timeDest) const;
  BOOL SetTime(LPSYSTEMTIME pTimeNew = NULL);
  DWORD GetTime(LPSYSTEMTIME pTimeDest) const
  { ASSERT(::IsWindow(m_hWnd)); ASSERT(pTimeDest != NULL); return (DWORD) ::SendMessage(m_hWnd, DTM_GETSYSTEMTIME, 0, (LPARAM) pTimeDest); }

// Overridables
public:
  virtual ~CDateTimeCtrl();
};

/////////////////////////////////////////////////////////////////////////////
// CMonthCalCtrl

class AFX_EXT_CLASS CMonthCalCtrl : public CWnd
{
  DECLARE_DYNAMIC(CMonthCalCtrl)

// Constructors
public:
  CMonthCalCtrl();
  BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
  BOOL Create(DWORD dwStyle, const POINT& pt, CWnd* pParentWnd, UINT nID);

//Attributes
public:
  BOOL GetMinReqRect(RECT* pRect) const
  { ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_GETMINREQRECT, 0, (LPARAM) pRect); }
  int SetMonthDelta(int iDelta)
  { ASSERT(m_hWnd != NULL); return (int) ::SendMessage(m_hWnd, MCM_SETMONTHDELTA, (WPARAM) iDelta, 0); }
  int GetMonthDelta() const
  { ASSERT(m_hWnd != NULL); return (int) ::SendMessage(m_hWnd, MCM_GETMONTHDELTA, 0, 0); }
  BOOL SetFirstDayOfWeek(int iDay, int* lpnOld = NULL);
  int GetFirstDayOfWeek(BOOL* pbLocal = NULL) const;
  COLORREF GetColor(int nRegion) const
  { ASSERT(m_hWnd != NULL); return (COLORREF) ::SendMessage(m_hWnd, MCM_GETCOLOR, (WPARAM) nRegion, 0); }
  COLORREF SetColor(int nRegion, COLORREF ref)
  { ASSERT(m_hWnd != NULL); return (COLORREF) ::SendMessage(m_hWnd, MCM_SETCOLOR, (WPARAM) nRegion, (LPARAM) ref); }
  DWORD HitTest(PMCHITTESTINFO pMCHitTest)
  { ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, MCM_HITTEST, 0, (LPARAM) pMCHitTest); }

// Operations
public:
  BOOL SizeMinReq(BOOL bRepaint = TRUE);
  void SetToday(const COleDateTime& refDateTime);
  void SetToday(const CTime* pDateTime);
  void SetToday(const LPSYSTEMTIME pDateTime)
  { ASSERT(m_hWnd != NULL); ::SendMessage(m_hWnd, MCM_SETTODAY, 0, (LPARAM) pDateTime); }
  BOOL GetToday(CTime& refTime) const;
  BOOL GetToday(COleDateTime& refDateTime) const;
  BOOL GetToday(LPSYSTEMTIME pDateTime) const
  { ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_GETTODAY, 0, (LPARAM) pDateTime); }
  BOOL GetCurSel(LPSYSTEMTIME pDateTime) const
  { ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_GETCURSEL, 0, (LPARAM) pDateTime); }
  BOOL SetCurSel(const LPSYSTEMTIME pDateTime)
  { ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_SETCURSEL, 0, (LPARAM) pDateTime); }
  BOOL SetCurSel(const CTime& refDateTime);
  BOOL GetCurSel(CTime& refDateTime) const;
  BOOL SetCurSel(const COleDateTime& refDateTime);
  BOOL GetCurSel(COleDateTime& refDateTime) const;
  BOOL SetDayState(int nMonths, LPMONTHDAYSTATE pStates);
  BOOL SetMaxSelCount(int nMax)
  { ASSERT(m_hWnd != NULL); return (BOOL) ::SendMessage(m_hWnd, MCM_SETMAXSELCOUNT, nMax, 0); }
  int GetMaxSelCount() const
  { ASSERT(m_hWnd != NULL); return (int) ::SendMessage(m_hWnd, MCM_GETMAXSELCOUNT, 0, 0); }
  BOOL SetRange(const COleDateTime* pMinRange, const COleDateTime* pMaxRange);
  DWORD GetRange(COleDateTime* pMinRange, COleDateTime* pMaxRange) const;
  BOOL SetRange(const CTime* pMinRange, const CTime* pMaxRange);
  DWORD GetRange(CTime* pMinRange, CTime* pMaxRange) const;
  BOOL SetRange(const LPSYSTEMTIME pMinRange, const LPSYSTEMTIME pMaxRange);
  DWORD GetRange(LPSYSTEMTIME pMinRange, LPSYSTEMTIME pMaxRange) const;
  int GetMonthRange(COleDateTime& refMinRange, COleDateTime& refMaxRange,
    DWORD dwFlags) const;
  int GetMonthRange(CTime& refMinRange, CTime& refMaxRange,
    DWORD dwFlags) const;
  int GetMonthRange(LPSYSTEMTIME pMinRange, LPSYSTEMTIME pMaxRange,
    DWORD dwFlags) const;
  BOOL SetSelRange(const COleDateTime& pMinRange,
    const COleDateTime& pMaxRange);
  BOOL GetSelRange(COleDateTime& refMinRange,
    COleDateTime& refMaxRange) const;
  BOOL SetSelRange(const CTime& pMinRange, const CTime& pMaxRange);
  BOOL GetSelRange(CTime& refMinRange, CTime& refMaxRange) const;
  BOOL GetSelRange(LPSYSTEMTIME pMinRange, LPSYSTEMTIME pMaxRange) const;
  BOOL SetSelRange(const LPSYSTEMTIME pMinRange,
    const LPSYSTEMTIME pMaxRange);

// Overridables
public:
  virtual ~CMonthCalCtrl();
};

/////////////////////////////////////////////////////////////////////////////
// DDX_ routines

void AFXAPI DDX_DateTimeCtrl(CDataExchange* pDX, int nIDC, COleDateTime& value);
void AFXAPI DDX_DateTimeCtrl(CDataExchange* pDX, int nIDC, CTime& value);
void AFXAPI DDX_MonthCalCtrl(CDataExchange* pDX, int nIDC,
	COleDateTime& value);
void AFXAPI DDX_MonthCalCtrl(CDataExchange* pDX, int nIDC, CTime& value);
void AFXAPI DDV_MinMaxDateTime(CDataExchange* pDX, CTime& refValue,
	const CTime* pMinRange, const CTime* pMaxRange);
void AFXAPI DDV_MinMaxDateTime(CDataExchange* pDX,  COleDateTime& refValue,
	const COleDateTime* pMinRange, const COleDateTime* pMaxRange);
void AFXAPI DDV_MinMaxMonth(CDataExchange* pDX, CTime& refValue,
	const CTime* pMinRange, const CTime* pMaxRange);
void AFXAPI DDV_MinMaxMonth(CDataExchange* pDX, COleDateTime& refValue,
	const COleDateTime* pMinRange, const COleDateTime* pMaxRange);

#endif //__DTCTL_H__

/////////////////////////////////////////////////////////////////////////////
