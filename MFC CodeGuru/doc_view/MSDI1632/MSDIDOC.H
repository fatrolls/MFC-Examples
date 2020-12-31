// msdidoc.h : interface of the CMsdiDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CMsdiDoc : public CDocument
{
protected: // create from serialization only
	CMsdiDoc();
	DECLARE_DYNCREATE(CMsdiDoc)

// Attributes

// Operations

// Implementation
public:
	virtual ~CMsdiDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CMsdiDoc)
	afx_msg void OnViewView2();
	afx_msg void OnUpdateViewView2(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
