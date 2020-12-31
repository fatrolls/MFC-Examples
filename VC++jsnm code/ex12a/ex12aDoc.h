// ex12aDoc.h : interface of the CEx12aDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX12ADOC_H__4AF8BADD_70BE_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
#define AFX_EX12ADOC_H__4AF8BADD_70BE_11D0_8FDA_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx12aDoc : public CDocument
{
protected: // create from serialization only
	CEx12aDoc();
	DECLARE_DYNCREATE(CEx12aDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx12aDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strText;
	virtual ~CEx12aDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx12aDoc)
	afx_msg void OnEditClearDocument();
	afx_msg void OnUpdateEditClearDocument(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX12ADOC_H__4AF8BADD_70BE_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
