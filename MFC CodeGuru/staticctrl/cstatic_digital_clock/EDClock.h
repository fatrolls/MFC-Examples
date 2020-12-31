
#ifndef __MFC_EXT_DIGITCLOCK_H__
#define __MFC_EXT_DIGITCLOCK_H__
// EDClock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXJWDigitClock window

class CXJWDigitClock : public CStatic
{
// Construction
public:
	CXJWDigitClock();
	virtual ~CXJWDigitClock();

// Attributes
public:
	enum CClockStyle { XDC_SECOND, XDC_NOSECOND };
	static COLORREF origin;

// Operations
public:
	CClockStyle GetStyle() const { return m_style;}
	CClockStyle SetStyle(CClockStyle style);
	COLORREF GetColor() const { return m_color;}
	COLORREF SetColor(COLORREF color);
	BOOL GetAlarm() const { return m_bAlarm;}
	BOOL SetAlarm(BOOL bAlarm = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXJWDigitClock)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CXJWDigitClock)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
private:

	BOOL		m_bAlarm;
	COLORREF    m_color;

	UINT		m_w;
	UINT		m_h;
	CClockStyle m_style;
	BITMAP		m_bm;
	UINT		m_nCount;
	HBITMAP		m_hBitmap[12];
	UINT		m_nTimer;

	void		Output(UINT digit, UINT pos);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __MFC_EXT_DIGITCLOCK_H__
