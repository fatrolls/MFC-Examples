#ifndef STEALTH_FRAME_H
#define STEALTH_FRAME_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StealthFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStealthFrame frame

#ifndef __PERSISTENTFRAMES_H_
	#include "PersistentFrames.h"
#endif

class CStealthFrame : public CPersistentFrameWnd
{
	DECLARE_DYNCREATE(CStealthFrame)
protected:
	CStealthFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CWnd				m_wndOwner;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStealthFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStealthFrame();

	// Generated message map functions
	//{{AFX_MSG(CStealthFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif 
