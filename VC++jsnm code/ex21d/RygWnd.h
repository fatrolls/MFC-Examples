#if !defined(AFX_RYGWND_H__1AA889D5_9788_11D0_BED2_00C04FC2A0C2__INCLUDED_)
#define AFX_RYGWND_H__1AA889D5_9788_11D0_BED2_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RygWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRygWnd window

#define RYG_SETSTATE WM_USER + 0
#define RYG_GETSTATE WM_USER + 1

LRESULT CALLBACK AFX_EXPORT
	RygWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class CRygWnd : public CWnd
{
private:
	int m_nState; // 0=off, 1=red, 2=yellow, 3=green
	static CRect  s_rect;
	static CPoint s_point;
	static CRect  s_rColor[3];
	static CBrush s_bColor[4];

// Construction
public:
	CRygWnd();
public:
	static BOOL RegisterWndClass(HINSTANCE hInstance);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRygWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRygWnd();

	// Generated message map functions
private:
	void SetMapping(CDC* pDC);
	void UpdateColor(CDC* pDC, int n);
protected:
	//{{AFX_MSG(CRygWnd)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnSetState(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetState(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RYGWND_H__1AA889D5_9788_11D0_BED2_00C04FC2A0C2__INCLUDED_)
