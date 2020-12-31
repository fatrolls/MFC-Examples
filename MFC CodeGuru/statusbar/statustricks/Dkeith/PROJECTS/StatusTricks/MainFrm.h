// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__9823BE32_4C57_11D1_B853_0020AF6F26D6__INCLUDED_)
#define AFX_MAINFRM_H__9823BE32_4C57_11D1_B853_0020AF6F26D6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ColorStatusBar.h"

class CMainFrame : public CMDIFrameWnd
{
protected:
					 DECLARE_DYNAMIC(CMainFrame)

protected:
	CColorStatusBar	 m_wndStatusBar;
	CToolBar		 m_wndToolBar;

public:
					 CMainFrame();
	virtual			~CMainFrame();
#ifdef _DEBUG
	virtual void	 AssertValid() const;
	virtual void	 Dump(CDumpContext& dc) const;
#endif

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL	 PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int		 OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__9823BE32_4C57_11D1_B853_0020AF6F26D6__INCLUDED_)
