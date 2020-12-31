// ex07aView.h : interface of the CEx07aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX07AVIEW_H__4A59A8DF_5797_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
#define AFX_EX07AVIEW_H__4A59A8DF_5797_11D0_8FCF_00C04FC2A0C2__INCLUDED_

class CEx07aDialog;

class CEx07aView : public CView
{
private:
	CEx07aDialog* m_pDlg;
protected: // create from serialization only
	CEx07aView();
	DECLARE_DYNCREATE(CEx07aView)

// Attributes
public:
	CEx07aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx07aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx07aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx07aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnGoodbye(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex07aView.cpp
inline CEx07aDoc* CEx07aView::GetDocument()
   { return (CEx07aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX07AVIEW_H__4A59A8DF_5797_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
