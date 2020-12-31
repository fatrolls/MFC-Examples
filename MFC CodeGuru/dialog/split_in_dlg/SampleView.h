#if !defined(AFX_SAMPLEVIEW_H__97EC6551_D554_11D1_B1B6_00600863FF0B__INCLUDED_)
#define AFX_SAMPLEVIEW_H__97EC6551_D554_11D1_B1B6_00600863FF0B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SampleView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSampleView view

class CSampleView : public CView
{
protected:
	CSampleView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSampleView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CSampleView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLEVIEW_H__97EC6551_D554_11D1_B1B6_00600863FF0B__INCLUDED_)
