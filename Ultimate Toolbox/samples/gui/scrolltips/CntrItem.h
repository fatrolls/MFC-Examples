// CntrItem.h : interface of the CScrollTipDemoCntrItem class
//

class CScrollTipDoc;
class CScrollTipEditView;

class CScrollTipDemoCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CScrollTipDemoCntrItem)

// Constructors
public:
	CScrollTipDemoCntrItem(REOBJECT* preo = NULL, CScrollTipDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CScrollTipDoc* GetDocument()
		{ return (CScrollTipDoc*)CRichEditCntrItem::GetDocument(); }
	CScrollTipEditView* GetActiveView()
		{ return (CScrollTipEditView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollTipDemoCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CScrollTipDemoCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
