// SerialView.h : interface of the CSerialView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALVIEW_H__172F9586_051F_11D2_88B0_0080C859A484__INCLUDED_)
#define AFX_SERIALVIEW_H__172F9586_051F_11D2_88B0_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define IDM_OUTPUT			(WM_USER + 100)
#define IDM_BACKSPACE		(WM_USER + 101)

class CSerialDoc;

class CSerialView : public CEditView
{
protected: // create from serialization only
	CSerialView();
	DECLARE_DYNCREATE(CSerialView)

// Attributes
public:
	CSerialDoc* GetDocument();

// Operations
public:
	void Output(LPCTSTR pszOutput, ...);
	void Backspace();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSerialView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFont m_font;
	CBrush m_brBkgnd;

	COLORREF m_clrText;
	COLORREF m_clrBkgnd;


// Generated message map functions
protected:
	afx_msg LONG OnOutput(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnBackspace(WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CSerialView)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SerialView.cpp
inline CSerialDoc* CSerialView::GetDocument()
   { return (CSerialDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALVIEW_H__172F9586_051F_11D2_88B0_0080C859A484__INCLUDED_)
