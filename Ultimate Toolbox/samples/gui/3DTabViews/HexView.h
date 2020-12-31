// HexView.h : header file
//

#ifndef _HEXVIEW_H_
#define _HEXVIEW_H_

//#include "OXTabView.h"

/////////////////////////////////////////////////////////////////////////////
// CHexView view

//class CHexView : public COXTabViewPage<CEditView>
class CHexView : public CEditView
{
protected:
	CHexView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHexView)

// Attributes
public:
	CTabViewsDoc* GetDocument();

// Operations
public:
	virtual ~CHexView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont	m_font;

	void TextToHex(BOOL bForFirstTime=FALSE);
	void AddText(LPCTSTR pszText);

	// Generated message map functions
protected:
	//{{AFX_MSG(CHexView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HexView.cpp
inline CTabViewsDoc* CHexView::GetDocument()
   { return (CTabViewsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

#endif	//	_HEXVIEW_H_
