// SpwDoc.h : interface of the CSpwDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPWDOC_H__D3F202D8_FC3A_11D0_9C9A_444553540000__INCLUDED_)
#define AFX_SPWDOC_H__D3F202D8_FC3A_11D0_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSpwDoc : public CDocument
{
protected: // create from serialization only
	CSpwDoc();
	DECLARE_DYNCREATE(CSpwDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpwDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpwDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSpwDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPWDOC_H__D3F202D8_FC3A_11D0_9C9A_444553540000__INCLUDED_)
