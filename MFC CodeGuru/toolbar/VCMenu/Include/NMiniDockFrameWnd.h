#if !defined(AFX_NMINIDOCKFRAMEWND_H__62F28F13_D47F_11D1_B546_0060085C418E__INCLUDED_)
#define AFX_NMINIDOCKFRAMEWND_H__62F28F13_D47F_11D1_B546_0060085C418E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NMiniDockFrameWnd.h : header file
//
#include <afxpriv.h>

/////////////////////////////////////////////////////////////////////////////
// CNMiniDockFrameWnd frame

class CNMiniDockFrameWnd : public CMiniDockFrameWnd
{
	DECLARE_DYNCREATE(CNMiniDockFrameWnd)
protected:
	CNMiniDockFrameWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNMiniDockFrameWnd)
	public:
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNMiniDockFrameWnd();

	// Generated message map functions
	//{{AFX_MSG(CNMiniDockFrameWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NMINIDOCKFRAMEWND_H__62F28F13_D47F_11D1_B546_0060085C418E__INCLUDED_)
