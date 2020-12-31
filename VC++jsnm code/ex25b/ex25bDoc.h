// ex25bDoc.h : interface of the CEx25bDoc class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_EX25BDOC_H__9C8ABB5D_98B3_11D0_85CF_9992596EDB70__INCLUDED_)
#define AFX_EX25BDOC_H__9C8ABB5D_98B3_11D0_85CF_9992596EDB70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx25bDoc : public CDocument
{
public:
    CDib m_dib;
    BOOL m_bDragHere; // for drags between two wins linked to this doc
protected: // create from serialization only
	CEx25bDoc();
	DECLARE_DYNCREATE(CEx25bDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25bDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
    virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx25bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	//{{AFX_MSG(CEx25bDoc)
    afx_msg void OnEditClearAll();
    afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25BDOC_H__9C8ABB5D_98B3_11D0_85CF_9992596EDB70__INCLUDED_)
