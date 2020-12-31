// $$srvritem_hfile$$.h : interface of the $$SRVRITEM_CLASS$$ class
//

#if !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
#define $$FILE_NAME_SYMBOL$$_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class $$SRVRITEM_CLASS$$ : public $$SRVRITEM_BASE_CLASS$$
{
	DECLARE_DYNAMIC($$SRVRITEM_CLASS$$)

// Constructors
public:
	$$SRVRITEM_CLASS$$($$DOC_CLASS$$* pContainerDoc);

// Attributes
	$$DOC_CLASS$$* GetDocument() const
		{ return ($$DOC_CLASS$$*)$$SRVRITEM_BASE_CLASS$$::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL($$SRVRITEM_CLASS$$)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~$$SRVRITEM_CLASS$$();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// $$INSERT_LOCATION_COMMENT$$

#endif // !defined($$FILE_NAME_SYMBOL$$_INCLUDED_)
