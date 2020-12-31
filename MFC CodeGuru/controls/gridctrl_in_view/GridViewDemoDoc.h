// GridViewDemoDoc.h : interface of the CGridViewDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDVIEWDEMODOC_H__19E18FBD_DFF6_11D1_8CE7_000000000000__INCLUDED_)
#define AFX_GRIDVIEWDEMODOC_H__19E18FBD_DFF6_11D1_8CE7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGridViewDemoDoc : public CDocument
{
protected: // create from serialization only
	CGridViewDemoDoc();
	DECLARE_DYNCREATE(CGridViewDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridViewDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridViewDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGridViewDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDVIEWDEMODOC_H__19E18FBD_DFF6_11D1_8CE7_000000000000__INCLUDED_)
