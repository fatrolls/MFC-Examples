// NotesView.h : interface of the CNotesView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTESVIEW_H__80E35B04_070A_11D4_ACEF_0050BAAB46B1__INCLUDED_)
#define AFX_NOTESVIEW_H__80E35B04_070A_11D4_ACEF_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXNotesEditView.h"

#define CLIENT_TEXT _T("This is a sample how it can look.\r\n\
You can set different types of the bookmarks that will have different look.\r\n\
Up to 256 different images supported. The bookmarks can be added,\r\n\
deleted, or updated. The bookmarks is set on the character basis,\r\n\
not on the line basis. With double click the bookmark may be set on \r\n\
or removed. Select a few lines and press \"Tab\" and the \"Shift-Tab\"\r\n\
to see that it works like Visual Studio. And now move Cursor to the notes area.")

class CNotesView : public COXNotesEditView
{
protected: // create from serialization only
	CNotesView();
	DECLARE_DYNCREATE(CNotesView)

// Attributes
public:
	CNotesDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotesView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNotesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnChangeCursor(HCURSOR* phCursor, UINT nPosition);

// Generated message map functions
protected:
	//{{AFX_MSG(CNotesView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NotesView.cpp
inline CNotesDoc* CNotesView::GetDocument()
   { return (CNotesDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTESVIEW_H__80E35B04_070A_11D4_ACEF_0050BAAB46B1__INCLUDED_)
