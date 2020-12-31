// CalcKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalcKey window

#include "oxshape.h"

class CCalcKey : public CWnd, public COXShape
{
	DECLARE_SHAPECLASS(CCalcKey);

private:
	CString m_strTitle;
	BOOL m_bHasFocus;
	BOOL m_bIsPressed;
	COLORREF m_crText;
	COLORREF m_crBk;
	COLORREF m_crAnimText;
	COLORREF m_crAnimBk;

private:
	HWND GetHWND() { return m_hWnd; }
	void FireClick() { GetParent()->SendMessage(WM_COMMAND,
						MAKEWPARAM(GetDlgCtrlID(),BN_CLICKED),
						(LPARAM) m_hWnd); }

// Construction
public:
	CCalcKey();

// Attributes
public:
	void SetColors(COLORREF crText=-1, COLORREF crBk=-1, COLORREF crAnimText=-1, 
							COLORREF crAnimBk=-1);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalcKey)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCalcKey();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCalcKey)
	afx_msg void OnPaint();
	afx_msg LONG OnSetText(WPARAM, LPARAM);
	afx_msg LONG OnGetText(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
