// ex32bDoc.h : interface of the CEx32bDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx32bSrvrItem;

class CEx32bDoc : public COleServerDoc
{
public:
	int		m_nPeriod;
protected: // create from serialization only
	CEx32bDoc();
	DECLARE_DYNCREATE(CEx32bDoc)

// Attributes
public:
	CEx32bSrvrItem* GetEmbeddedItem()
		{ return (CEx32bSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx32bDoc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx32bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx32bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
