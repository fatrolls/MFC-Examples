// DragEditDoc.h : interface of the CDragEditDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAGEDITDOC_H__871E3CCC_6359_11D1_8251_444553540000__INCLUDED_)
#define AFX_DRAGEDITDOC_H__871E3CCC_6359_11D1_8251_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDragEditDoc : public CDocument
{
protected: // create from serialization only
	CDragEditDoc();
	DECLARE_DYNCREATE(CDragEditDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragEditDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDragEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDragEditDoc)
	afx_msg void OnFileTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGEDITDOC_H__871E3CCC_6359_11D1_8251_444553540000__INCLUDED_)
