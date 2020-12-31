// MDIDoc.h : interface of the CMDIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef MDIDOC_H
#define MDIDOC_H

class CMDIDoc : public CDocument
{
	DECLARE_DYNCREATE(CMDIDoc)

protected: // create from serialization only
	CMDIDoc();
	virtual ~CMDIDoc();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIDoc)
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDIDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //MDIDOC_H
