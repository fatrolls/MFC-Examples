// TreeMenuDemoDoc.h : interface of the CTreeMenuDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREEMENUDEMODOC_H__96C46D8E_E5C6_11D1_92D4_0080C882060B__INCLUDED_)
#define AFX_TREEMENUDEMODOC_H__96C46D8E_E5C6_11D1_92D4_0080C882060B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTreeMenuDemoDoc : public CDocument
{
protected: // create from serialization only
	CTreeMenuDemoDoc();
	DECLARE_DYNCREATE(CTreeMenuDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeMenuDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeMenuDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTreeMenuDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEMENUDEMODOC_H__96C46D8E_E5C6_11D1_92D4_0080C882060B__INCLUDED_)
