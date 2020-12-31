// Mapi1Doc.h : interface of the CMapi1Doc class
//
/////////////////////////////////////////////////////////////////////////////

class CMapi1Doc : public CDocument
{
protected: // create from serialization only
	CMapi1Doc();
	DECLARE_DYNCREATE(CMapi1Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapi1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapi1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMapi1Doc)
	afx_msg void OnFileSendMail();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
