#pragma once

/////////////////////////////////////////////////////////////////////////////
// CListCtrlCellWnd window

class CListCtrlCellWnd : public CWnd
{
// Construction
public:
	CListCtrlCellWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlCellWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlCellWnd();

	// Generated message map functions
	virtual void OnEnter(){Close();};
	void Close();
protected:
	HWND			m_hMainCtrlWnd;
	//{{AFX_MSG(CListCtrlCellWnd)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

