// testdoc.h : interface of the CTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CTestDoc : public CDocument
{
protected: // create from serialization only
	CTestDoc();
	DECLARE_DYNCREATE(CTestDoc)

// Attributes
public:

// Operations
public:

// Implementation
protected:
	CSize           m_sizeDoc;
public:
	CSize GetDocSize() { return m_sizeDoc; }

public:
	virtual void InitDocument();
	virtual ~CTestDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnNewDocument();
	virtual  BOOL  OnOpenDocument(const char* pszPathName);

// Generated message map functions
protected:
	//{{AFX_MSG(CTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
