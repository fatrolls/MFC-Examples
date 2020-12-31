// ResLibDoc.h : interface of the CResLibDoc class
//

#include "OXResourceLibrary.h"

/////////////////////////////////////////////////////////////////////////////

class CResLibDoc : public CDocument
{
protected: // create from serialization only
	CResLibDoc();
	DECLARE_DYNCREATE(CResLibDoc)

// Attributes
public:
	COXResourceLibrary m_ResLib;
	CStringArray m_sTypes;
	CStringArray m_sNames;
	CWordArray   m_nLangs;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResLibDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CResLibDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CResLibDoc)
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
