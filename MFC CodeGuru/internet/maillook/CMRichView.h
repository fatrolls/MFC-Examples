#if !defined(AFX_CMRICHVIEW_H__D5D5E429_F1FA_11D1_9447_BC2A94000000__INCLUDED_)
#define AFX_CMRICHVIEW_H__D5D5E429_F1FA_11D1_9447_BC2A94000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CMRichView.h : header file
//
#include <afxrich.h>
/////////////////////////////////////////////////////////////////////////////
// CMRichView view

class CMRichView : public CRichEditView
{
protected: // create from serialization only
	CMRichView();
	DECLARE_DYNCREATE(CMRichView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRichView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMRichView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	//{{AFX_MSG(CMRichView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMRICHVIEW_H__D5D5E429_F1FA_11D1_9447_BC2A94000000__INCLUDED_)
