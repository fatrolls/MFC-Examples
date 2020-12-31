// SrvrItem.h : interface of the CEx32aSrvrItem class
//

class CEx32aSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CEx32aSrvrItem)

// Constructors
public:
	CEx32aSrvrItem(CEx32aDoc* pContainerDoc);

// Attributes
	CEx32aDoc* GetDocument() const
		{ return (CEx32aDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx32aSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEx32aSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////
