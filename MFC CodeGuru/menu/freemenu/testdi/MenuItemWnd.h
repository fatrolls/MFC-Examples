#if !defined(AFX_MENUITEMWND_H__6EA700B3_0AF3_11D2_9768_0080C858DB41__INCLUDED_)
#define AFX_MENUITEMWND_H__6EA700B3_0AF3_11D2_9768_0080C858DB41__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MenuItemWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMenuItemWnd window
class CFreeMenu;
class CMenuItemWnd : public CWnd
{
// Construction
public:
	CMenuItemWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuItemWnd)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CFreeMenu * freeMenu;
	virtual ~CMenuItemWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMenuItemWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUITEMWND_H__6EA700B3_0AF3_11D2_9768_0080C858DB41__INCLUDED_)
