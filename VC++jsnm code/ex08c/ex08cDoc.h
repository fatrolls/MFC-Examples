#if !defined(EX08CDOC_H__6084D1FB_488C_11D0_8488_00400526305B__INCLUDED_)
#define EX08CDOC_H__6084D1FB_488C_11D0_8488_00400526305B__INCLUDED_

// ex08cDoc.h : interface of the CEx08cDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include "webbrowser.h"

class CEx08cDoc : public CDocument
{
public:
    static const char s_profileInternet[];
    static const char s_profileURLBrowse[];
    static const char s_profileURLSearch[];
	static const char s_engineAltavista[];
	static const char s_engineMagellan[];
	static const char s_engineMicrosoft[];
	static const char s_engineYahoo[];
	bool m_bSearchBackForward;
	bool m_bSearchBusy;
	CWebBrowser m_browse, m_search;
	CString m_strURLBrowse, m_strURLSearch;
protected: // create from serialization only
	CEx08cDoc();
	DECLARE_DYNCREATE(CEx08cDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx08cDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx08cDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx08cDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(EX08CDOC_H__6084D1FB_488C_11D0_8488_00400526305B__INCLUDED)
