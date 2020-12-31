// MessageFoldersView.h : interface of the CMessageFoldersView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEFOLDERSVIEW_H__1FE0A7DC_27E9_11D3_B75D_00203596449E__INCLUDED_)
#define AFX_MESSAGEFOLDERSVIEW_H__1FE0A7DC_27E9_11D3_B75D_00203596449E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMessageFoldersView : public CListView
{
protected: // create from serialization only
	CMessageFoldersView();
	DECLARE_DYNCREATE(CMessageFoldersView)

// Attributes
public:
	CIMAPClientDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageFoldersView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMessageFoldersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMessageFoldersView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MessageFoldersView.cpp
inline CIMAPClientDoc* CMessageFoldersView::GetDocument()
   { return (CIMAPClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEFOLDERSVIEW_H__1FE0A7DC_27E9_11D3_B75D_00203596449E__INCLUDED_)
