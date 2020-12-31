// WorkspaceTextDoc.h : interface of the CWorkspaceTextDoc class
//
/////////////////////////////////////////////////////////////////////////////
//====================================================================
//===============  Dundas Software ==================================
//===================================================================

class CWorkspaceTextDoc : public CDocument
{
protected: // create from serialization only
	CWorkspaceTextDoc();
	DECLARE_DYNCREATE(CWorkspaceTextDoc)

// Attributes
public:

// Operations
public:
	BOOL SetText(CString sText);
	CString GetText() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceTextDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorkspaceTextDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_sText;

// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceTextDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
