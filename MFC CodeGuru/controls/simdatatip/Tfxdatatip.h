/*
* Configuration control preamble *********************************************
*
* PROJECT:          C++ Library
*
* TITLE:            Data Tip window (aka. enhanced Tooltips)
* FILENAME:         tfxdatatip.h
*
* CREATED:          10 April 1997
* ORIGINATOR:       S.A.J. Wilson
*
*                   (c) Copyright 1997
*                       Technisoft Ltd.
*
******************************************************************************
*                              ISSUE HISTORY                                                               
*
* 10-APR-1997       SAJW
* Issue 0.1         Created 
*
* 18-APR-1997       SAJW
* Issue 1.0         First release
*
******************************************************************************
*/


/*
* Module preamble ************************************************************
*
* NAME:             Data tips
*
* DESCRIPTION:      This module provides the data tips used for displaying
*                   data information to the user in a ToolTip format.
*
* HIERARCHY:        CWnd
*                     |
*                     +---- TFXDataTip
*
* LIMITATIONS:      None
*
* REFERENCES:       None
*
******************************************************************************
*/
#ifndef _tfxdatatip_h__
    #define _tfxdatatip_h__

/*

* Class preamble *************************************************************
*
* NAME:             TFXDataTip
* BASE CLASS(es):   CWnd
*
* DESCRIPTION:      This class provides a DataTip conotrol. This is used to 
*                   display pop-up information on a view to the user. When
*                   a data tip control is enabled, then after the information
*                   has been set the window will be displayed provided that 
*                   the mouse does not move within a specified time delay.
*
*                   Once the tip is visible, then it remains visible until
*                   the user moves the tip outside of a catch area 
*                   immediately around its display position.
*
* PUBLIC INTERFACE:
*   Methods:        constructor     constructs a DataTip window
*                   SetOffset       sets the offset from the cursor position
*                   Create          creates the DataTip window
*                   Set             sets the DataTip information (starts time)
*                   Hide            hides the DataTip window
*
*                   On              turns the DataTip window on/off
*                   IsOn            returns the status of the DataTip
*
*                   SetDelay        sets the delay for all DataTips
*
*   Operators:      none
*
*   Data members:   none
*
******************************************************************************
*                                  REVISION HISTORY                                                               
*
* 18-APR-1997       SAJW    First release
*
******************************************************************************
*/
class TFXDataTip : public CWnd
{
// Construction
public:
	TFXDataTip();

// Attributes
public:
    void SetOffset(long x, long y);
    void SetOffset(CPoint offset);

// Operations
public:
	virtual BOOL Create(CWnd* pParentWnd);
    void Set(CPoint point, const CString& tip);
    void Hide( );

    void On(BOOL on);
    BOOL IsOn( ) const;

// class operations
public:
    static void SetDelay(short delay);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TFXDataTip)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~TFXDataTip();

	// Generated message map functions
protected:
	//{{AFX_MSG(TFXDataTip)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
    void Display( );

protected:
    CWnd*   m_parent;
    CString m_tip;
    CPoint  m_offset;
    CRect   m_captureRect;
    CPoint  m_origin;
    BOOL    m_ready;
    BOOL    m_on;
    UINT    m_timer;

protected:
    static void RegisterWnd( );
    static void Initialise( );

    static BOOL _registered;
    static short _delay;
    static short _count;

    // keyboard hook
    static LRESULT CALLBACK KeyboardHookCallback(int code, WPARAM wParam, LPARAM lParam);	
    static HHOOK _hookProc;
    static TFXDataTip* _current;
};


// inline object methods
inline void TFXDataTip::On(BOOL on)
    { m_on = on; }
inline BOOL TFXDataTip::IsOn( ) const
    { return m_on; }

inline void TFXDataTip::SetOffset(long x, long y)
    { m_offset = CPoint(x, y); }
inline void TFXDataTip::SetOffset(CPoint offset)
    { m_offset = offset; }

// inline methods for class
inline void TFXDataTip::SetDelay(short delay)
    { _delay = delay; }



#endif

