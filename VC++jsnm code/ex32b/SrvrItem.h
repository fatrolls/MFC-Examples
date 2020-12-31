// SrvrItem.h : interface of the CEx32bSrvrItem class
//

class CEx32bSrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CEx32bSrvrItem)

// Constructors
public:
	CEx32bSrvrItem(CEx32bDoc* pContainerDoc);

// Attributes
	CEx32bDoc* GetDocument() const
		{ return (CEx32bDoc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx32bSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CEx32bSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////
