// MvTestDoc.h : interface of the CMvTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MVTESTDOC_H__A695B2CA_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
#define AFX_MVTESTDOC_H__A695B2CA_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMvTestDoc : public CDocument
{
protected: // create from serialization only
	CMvTestDoc();
	DECLARE_DYNCREATE(CMvTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMvTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMvTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMvTestDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMvTestDoc)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVTESTDOC_H__A695B2CA_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
