// btncovw.h : interface of the CBtncolorView class
//
/////////////////////////////////////////////////////////////////////////////

class CBtncolorView : public CView
{
protected: // create from serialization only
	CBtncolorView();
	DECLARE_DYNCREATE(CBtncolorView)

// Attributes
public:
	CBtncolorDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CBtncolorView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBtncolorView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in btncovw.cpp
inline CBtncolorDoc* CBtncolorView::GetDocument()
   { return (CBtncolorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
