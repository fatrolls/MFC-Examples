#if !defined(AFX_DATETIMECTRL_H__D4DC9621_54F2_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_DATETIMECTRL_H__D4DC9621_54F2_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// DateTimeCtrl.h : header file
//
// MFC Wrapper class for the IE3 DateTimePicker control
//
// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
// Copyright (c) 1998.
//
// This code is free
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
// History: 15 April 1998 - Modifications to workaround multiple DTP notifications
//                          causing infinite loops. Added virtual fns for messages.
//
/////////////////////////////////////////////////////////////////////////////

void AFXAPI DDX_DateTime(CDataExchange *pDX, int nIDC, SYSTEMTIME &SysTime);

/////////////////////////////////////////////////////////////////////////////
// CDateTimeCtrl window

class CDateTimeCtrl : public CWnd
{
// Construction 
public:
    CDateTimeCtrl();
    virtual ~CDateTimeCtrl();
    BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Operations
public:
    CTime GetDateTime();
    COleDateTime GetOleDateTime();
    BOOL  SetDateTime(const CTime& time);
    BOOL  SetDateTime(const COleDateTime& time);

// Attributes
public:
    COLORREF SetMonthCalColour(int nColIndex, COLORREF colour);
    COLORREF GetMonthCalColour(int nColIndex);
    BOOL     SetFormat(LPCTSTR szFmt);
    void     SetMonthCalFont(CFont& font, BOOL bRedraw = TRUE);
    CFont*   GetMonthCalFont();
    BOOL     SetRange(CTime* pMinTime, CTime* pMaxTime);
    BOOL     SetRange(COleDateTime* pMinTime, COleDateTime* pMaxTime);
    DWORD    GetRange(CTime* pMinTime, CTime* pMaxTime);
    DWORD    GetRange(COleDateTime* pMinTime, COleDateTime* pMaxTime);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDateTimeCtrl)
    //}}AFX_VIRTUAL
    virtual void DoDateTimeChange();

// Implementation
protected:
    void  SysTimeFromCTime(const CTime& time, SYSTEMTIME *SysTime);
    void  SysTimeFromCOleDateTime(const COleDateTime& time, SYSTEMTIME *SysTime);
    COleDateTime GetSystemTime();
    BOOL  SetSystemTime(const SYSTEMTIME& time);
    BOOL  SetSystemTime(const COleDateTime& time);
    BOOL  SetSystemTime(const CTime& time);

    COleDateTime m_CurrentTime;
    static bool nCommonControlsInitialised;
    BOOL  m_bDroppedDown;

    // Generated message map functions
protected:
    //{{AFX_MSG(CDateTimeCtrl)
    //}}AFX_MSG
    virtual BOOL OnDateTimeChangeNotify(LPNMDATETIMECHANGE dtmh, LRESULT* result);
    virtual BOOL OnDropDown(NMHDR * pNotifyStruct, LRESULT* result);
    virtual BOOL OnCloseUp(NMHDR * pNotifyStruct, LRESULT* result);
    virtual BOOL OnFormat(NMDATETIMEFORMAT* lpNMFormat, LRESULT* pResult);
    virtual BOOL OnFormatQuery(NMDATETIMEFORMATQUERY* lpNMFormat, LRESULT* pResult);
    virtual BOOL OnUserString(NMDATETIMESTRING* lpDTstring, LRESULT* pResult);
    virtual BOOL OnKeyDown(NMDATETIMEWMKEYDOWN* lpDTKeystroke, LRESULT* pResult);

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATETIMECTRL_H__D4DC9621_54F2_11D1_ABBA_00A0243D1382__INCLUDED_)
