// BmpClientDoc.h : interface of the CBmpClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPCLIENTDOC_H__BAF706BD_89CB_11D1_A17A_000000000000__INCLUDED_)
#define AFX_BMPCLIENTDOC_H__BAF706BD_89CB_11D1_A17A_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CBmpClientDoc : public CDocument
{
protected: // create from serialization only
	CBmpClientDoc();
	DECLARE_DYNCREATE(CBmpClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBmpClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBmpClientDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPCLIENTDOC_H__BAF706BD_89CB_11D1_A17A_000000000000__INCLUDED_)
