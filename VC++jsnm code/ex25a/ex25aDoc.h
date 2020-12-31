// ex25aDoc.h : interface of the CEx25aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX25ADOC_H__C4B91633_98AE_11D0_85CF_9992596EDB70__INCLUDED_)
#define AFX_EX25ADOC_H__C4B91633_98AE_11D0_85CF_9992596EDB70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx25aDoc : public CDocument
{
public:
    CDib m_dib;
protected: // create from serialization only
	CEx25aDoc();
	DECLARE_DYNCREATE(CEx25aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
    virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx25aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	//{{AFX_MSG(CEx25aDoc)
    afx_msg void OnEditClearAll();
    afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25ADOC_H__C4B91633_98AE_11D0_85CF_9992596EDB70__INCLUDED_)
