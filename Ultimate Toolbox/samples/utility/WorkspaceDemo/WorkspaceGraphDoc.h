// WorkspaceGraphDoc.h : interface of the CWorkspaceGraphDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CWorkspaceGraphDoc : public CDocument
{
protected: // create from serialization only
	CWorkspaceGraphDoc();
	DECLARE_DYNCREATE(CWorkspaceGraphDoc)

// Attributes
public:

// Operations
public:
	BOOL SetColor(COLORREF color);
	COLORREF GetColor() const;
	BOOL SetSides(int nSides);
	int GetSides() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceGraphDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorkspaceGraphDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	COLORREF m_color;
	int m_nSides;

// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceGraphDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
