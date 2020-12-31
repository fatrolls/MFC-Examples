// DateTimeCtrl.cpp : implementation file
//
// MFC Wrapper class for the IE3 DateTimePicker control
// Check out http://www.microsoft.com/msdn/sdk/inetsdk/help/itt/CommCtls/DateTime/DateTime.htm#ch_dtp_make
// for details.
//
//    To use in a dialog:
//      Create a custom control with classname "SysDateTimePick32"
//    You will then need to subclass the custom control (in the InitDialog fn). 
//    eg.
//
//      m_DateTime.SubclassDlgItem(IDC_CUSTOM1, this);
//
//  To use if creating with "Create":
//      call "CDateTimeCtrl::Create(dwStyle, rect, pParentWnd, nID)"
// 
//  DateTime styles:
//
//        DTS_UPDOWN           - use UPDOWN instead of MONTHCAL
//        DTS_SHOWNONE         - allow a NONE selection
//        DTS_SHORTDATEFORMAT  - use the short date format (app must forward WM_WININICHANGE messages)
//        DTS_LONGDATEFORMAT   - use the long date format (app must forward WM_WININICHANGE messages)
//        DTS_TIMEFORMAT       - use the time format (app must forward WM_WININICHANGE messages)
//        DTS_APPCANPARSE      - allow user entered strings (app MUST respond to DTN_USERSTRING)
//        DTS_RIGHTALIGN       - right-align popup instead of left-align it
//
//  For the CDateTimeCtrl::SetFormat(LPCTSTR szFmt) specs, see the functions GetDateFormat 
//  and GetTimeFormat for the format of szFmt.
// 
//  For the Set- and Get-Colour functions, use the following for the nColIndex:
// 
//        MCSC_BACKGROUND   0   // the background color (between months)
//        MCSC_TEXT         1   // the dates
//        MCSC_TITLEBK      2   // background of the title
//        MCSC_TITLETEXT    3      // title text
//        MCSC_MONTHBK      4   // background within the month cal
//        MCSC_TRAILINGTEXT 5   // the text color of header & trailing days
//
// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
// Copyright (c) 1998.
//
// Modified 7 Feb 1998 - bug fix in OnChildNotify (Jim Richardson)
//                     - Added COleDateTime support
//
// This code is free. If the source code in this file is used in any 
// commercial application then an email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to your
// computer, causes your pet cat to fall ill, increases baldness or
// makes you car start emitting strange noises when you start it up.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DateTimeCtrl.h"
    
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Thanks to Tim Gilman (tdgilman@best.com) for this.
void AFXAPI DDX_DateTime(CDataExchange *pDX, int nIDC, SYSTEMTIME &SysTime)
{
    HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
    ASSERT (hWndCtrl != NULL);

    if (pDX->m_bSaveAndValidate)
    {
        ::SendMessage(hWndCtrl, DTM_GETSYSTEMTIME, 0, (LPARAM)&SysTime);
    }
    else // initializing
    {
        ::SendMessage(hWndCtrl, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&SysTime);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtrl

bool CDateTimeCtrl::nCommonControlsInitialised = false;

CDateTimeCtrl::CDateTimeCtrl()
{
    if (!nCommonControlsInitialised)
    {
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_DATE_CLASSES;
        ::InitCommonControlsEx(&icex);
        nCommonControlsInitialised = true;
    }

    m_CurrentTime = COleDateTime::GetCurrentTime();
    m_bDroppedDown = FALSE;
}

CDateTimeCtrl::~CDateTimeCtrl()
{
}

BOOL CDateTimeCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
    return CWnd::Create(DATETIMEPICK_CLASS, "", dwStyle, rect, pParentWnd, nID);
}

BEGIN_MESSAGE_MAP(CDateTimeCtrl, CWnd)
    //{{AFX_MSG_MAP(CDateTimeCtrl)
    //}}AFX_MSG_MAP
    ON_NOTIFY_REFLECT_EX(DTN_DATETIMECHANGE, OnDateTimeChangeNotify)
    ON_NOTIFY_REFLECT_EX(DTN_DROPDOWN,       OnDropDown)
    ON_NOTIFY_REFLECT_EX(DTN_CLOSEUP,        OnCloseUp)
    ON_NOTIFY_REFLECT_EX(DTN_FORMAT,         OnFormat)
    ON_NOTIFY_REFLECT_EX(DTN_FORMATQUERY,    OnFormatQuery)
    ON_NOTIFY_REFLECT_EX(DTN_USERSTRING,     OnUserString)
    ON_NOTIFY_REFLECT_EX(DTN_WMKEYDOWN,      OnKeyDown)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtrl (public) operations

CTime CDateTimeCtrl::GetDateTime() 
{
    SYSTEMTIME SysTime;
    SysTimeFromCOleDateTime(m_CurrentTime, &SysTime);

    return CTime(SysTime); 
}

COleDateTime CDateTimeCtrl::GetOleDateTime() 
{
    return m_CurrentTime; 
}

BOOL CDateTimeCtrl::SetDateTime(const CTime& time)
{
    SYSTEMTIME SysTime;
    SysTimeFromCTime(time, &SysTime);

    m_CurrentTime = SysTime;
    return SetSystemTime(SysTime);
}

BOOL CDateTimeCtrl::SetDateTime(const COleDateTime& time)
{
    m_CurrentTime = time;
    return SetSystemTime(time);
}

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtrl overridable

void CDateTimeCtrl::DoDateTimeChange()
{
    TRACE("In OnDateTimeChange\n");
}

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtrl (protected) implementation

COleDateTime CDateTimeCtrl::GetSystemTime()
{    
    SYSTEMTIME SysTime;
    if (DateTime_GetSystemtime(m_hWnd, &SysTime) == GDT_VALID)
        return COleDateTime(SysTime);
    else
        return COleDateTime::GetCurrentTime();
}

void CDateTimeCtrl::SysTimeFromCOleDateTime(const COleDateTime& time, SYSTEMTIME *SysTime)
{
    SysTime->wYear   = time.GetYear();
    SysTime->wMonth  = time.GetMonth();
    SysTime->wDay    = time.GetDay();
    SysTime->wHour   = time.GetHour();
    SysTime->wMinute = time.GetMinute();
    SysTime->wSecond = time.GetSecond();
    SysTime->wMilliseconds = 0;
}

void CDateTimeCtrl::SysTimeFromCTime(const CTime& time, SYSTEMTIME *SysTime)
{
    SysTime->wYear   = time.GetYear();
    SysTime->wMonth  = time.GetMonth();
    SysTime->wDay    = time.GetDay();
    SysTime->wHour   = time.GetHour();
    SysTime->wMinute = time.GetMinute();
    SysTime->wSecond = time.GetSecond();
    SysTime->wMilliseconds = 0;
}

BOOL CDateTimeCtrl::SetSystemTime(const SYSTEMTIME& time)
{
    return DateTime_SetSystemtime(m_hWnd, GDT_VALID, &time);
}

BOOL CDateTimeCtrl::SetSystemTime(const CTime& time)
{
    SYSTEMTIME SysTime;
    SysTimeFromCTime(time, &SysTime);
    return DateTime_SetSystemtime(m_hWnd, GDT_VALID, &SysTime);
}

BOOL CDateTimeCtrl::SetSystemTime(const COleDateTime& time)
{
    SYSTEMTIME SysTime;
    SysTimeFromCOleDateTime(time, &SysTime);
    return DateTime_SetSystemtime(m_hWnd, GDT_VALID, &SysTime);
}

// See GetDateFormat and GetTimeFormat for the format of szFmt.
BOOL CDateTimeCtrl::SetFormat(LPCTSTR szFmt)
{
    return DateTime_SetFormat(m_hWnd, szFmt);
}

// Posible values for nColIndex:
//    MCSC_BACKGROUND   0   // the background color (between months)
//    MCSC_TEXT         1   // the dates
//    MCSC_TITLEBK      2   // background of the title
//    MCSC_TITLETEXT    3
//    MCSC_MONTHBK      4   // background within the month cal
//    MCSC_TRAILINGTEXT 5   // the text color of header & trailing days

COLORREF CDateTimeCtrl::SetMonthCalColour(int nColIndex, COLORREF colour)
{
    return DateTime_SetMonthCalColor(m_hWnd, nColIndex, colour);
}

COLORREF CDateTimeCtrl::GetMonthCalColour(int nColIndex)
{
    return DateTime_GetMonthCalColor(m_hWnd, nColIndex);
}

void CDateTimeCtrl::SetMonthCalFont(CFont& font, BOOL bRedraw /*=TRUE*/)
{
    DateTime_SetMonthCalFont(m_hWnd, (HFONT)font, bRedraw);
}

CFont* CDateTimeCtrl::GetMonthCalFont()    
{
    return CFont::FromHandle( (HFONT)DateTime_GetMonthCalFont(m_hWnd) );
}

// Returns TRUE if success for both times, FALSE otherwise
BOOL CDateTimeCtrl::SetRange(CTime* pMinTime, CTime* pMaxTime)
{
    SYSTEMTIME SysTimeRange[2];
    int nWhich = 0;

    if (pMinTime) {
        nWhich |= GDTR_MIN;
        SysTimeFromCTime( *pMinTime, &(SysTimeRange[0]) );
    }

    if (pMaxTime) {
        nWhich |= GDTR_MAX;
        SysTimeFromCTime( *pMaxTime, &(SysTimeRange[1]) );
    }

    return DateTime_SetRange(m_hWnd, nWhich, SysTimeRange);
}

// Returns TRUE if success for both times, FALSE otherwise
BOOL CDateTimeCtrl::SetRange(COleDateTime* pMinTime, COleDateTime* pMaxTime)
{
    SYSTEMTIME SysTimeRange[2];
    int nWhich = 0;

    if (pMinTime) {
        nWhich |= GDTR_MIN;
        SysTimeFromCOleDateTime( *pMinTime, &(SysTimeRange[0]) );
    }

    if (pMaxTime) {
        nWhich |= GDTR_MAX;
        SysTimeFromCOleDateTime( *pMaxTime, &(SysTimeRange[1]) );
    }

    return DateTime_SetRange(m_hWnd, nWhich, SysTimeRange);
}

// returns GDTR_MIN|GDTR_MAX if there is a minimum|maximum limit
DWORD CDateTimeCtrl::GetRange(CTime* pMinTime, CTime* pMaxTime)
{
    SYSTEMTIME SysTimeRange[2];
    DWORD result = DateTime_GetRange(m_hWnd, SysTimeRange);

    *pMinTime = CTime(SysTimeRange[0]);    // systime is 0 if no limit
    *pMaxTime = CTime(SysTimeRange[1]);

    return result;
}

// returns GDTR_MIN|GDTR_MAX if there is a minimum|maximum limit
DWORD CDateTimeCtrl::GetRange(COleDateTime* pMinTime, COleDateTime* pMaxTime)
{
    SYSTEMTIME SysTimeRange[2];
    DWORD result = DateTime_GetRange(m_hWnd, SysTimeRange);

    *pMinTime = COleDateTime(SysTimeRange[0]);    // systime is 0 if no limit
    *pMaxTime = COleDateTime(SysTimeRange[1]);

    return result;
}

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtrl notification handlers

BOOL CDateTimeCtrl::OnDropDown(NMHDR* pNotifyStruct, LRESULT* result)
{
    m_bDroppedDown = TRUE;
    return FALSE;    // Let parent handle message
}

BOOL CDateTimeCtrl::OnCloseUp(NMHDR* pNotifyStruct, LRESULT* result)
{
    m_bDroppedDown = FALSE;
    return FALSE;    // Let parent handle message
}

// This traps the DTN_DATETIMECHANGE notification and checks that
// the date/time has actually changed. If it has, then the message
// is passed on to the parent as normal, otherwise it is blocked.
BOOL CDateTimeCtrl::OnDateTimeChangeNotify(NMDATETIMECHANGE *dtmh, LRESULT* pResult)
{
    *pResult = 0;    // docs say we must return 0

    // Check box notification sent here.
    if (dtmh->dwFlags == GDT_NONE)
        TRACE("control Disabled\n");
    else
        TRACE("control Active\n");

    // Has the date changed?
    BOOL bDateChanged = FALSE;
    if (dtmh->dwFlags == GDT_VALID)
    {
        COleDateTime time = GetSystemTime();
        if (time != m_CurrentTime)
        {
            m_CurrentTime = time;
            bDateChanged = TRUE;
            DoDateTimeChange();
        }
    }

    BOOL bUpDownStyle = ((GetStyle() & DTS_UPDOWN) == DTS_UPDOWN);
    if (bUpDownStyle) return FALSE;    // Let parent handle message

    // If the control is NOT a DTS_UPDOWN style (ie it has a drop down)
    // then we need to catch multiple notifications of date changes
    // (this can cause infinite loops). 
    if (m_bDroppedDown)
    {
        if (bDateChanged)
            return TRUE;    // Don't let the parent see the message if not dropped down
        else 
            return FALSE;    // Let parent see message, since date hasn't changed
    }
    else
        return FALSE;        // Let parent handle message
}

BOOL CDateTimeCtrl::OnFormat(NMDATETIMEFORMAT* lpNMFormat, LRESULT* pResult)
{
    *pResult = 0;    // docs say we must return 0
    return FALSE;    // Let parent handle message
}

BOOL CDateTimeCtrl::OnFormatQuery(NMDATETIMEFORMATQUERY* lpDTFormatQuery, LRESULT* pResult)
{
    *pResult = 0;    // docs say we must return 0
    lpDTFormatQuery->szMax = CSize(366,16);    // Must calculate Max time string size
    return FALSE;    // Let parent handle message
}

BOOL CDateTimeCtrl::OnUserString(NMDATETIMESTRING* lpDTstring, LRESULT* pResult)
{
    *pResult = 0;    // docs say we must return 0
    return FALSE;    // Let parent handle message
}

BOOL CDateTimeCtrl::OnKeyDown(NMDATETIMEWMKEYDOWN* lpDTKeystroke, LRESULT* pResult)
{
    *pResult = 0;    // docs say we must return 0
    return FALSE;    // Let parent handle message
}


