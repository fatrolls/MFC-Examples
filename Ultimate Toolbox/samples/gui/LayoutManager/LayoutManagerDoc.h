// LayoutManagerDoc.h : interface of the CLayoutManagerDoc class
//

/////////////////////////////////////////////////////////////////////////////

class CLayoutManagerDoc : public CDocument
{
protected: // create from serialization only
	CLayoutManagerDoc();
	DECLARE_DYNCREATE(CLayoutManagerDoc)

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayoutManagerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLayoutManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLayoutManagerDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
