// ToolbarMenuDemoMDIDoc.h : interface of the CToolbarMenuDemoMDIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBARMENUDEMOMDIDOC_H__38474A5C_9DC0_11D1_8BAD_0000B43382FE__INCLUDED_)
#define AFX_TOOLBARMENUDEMOMDIDOC_H__38474A5C_9DC0_11D1_8BAD_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CToolbarMenuDemoMDIDoc : public CDocument
{
protected: // create from serialization only
	CToolbarMenuDemoMDIDoc();
	DECLARE_DYNCREATE(CToolbarMenuDemoMDIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarMenuDemoMDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolbarMenuDemoMDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolbarMenuDemoMDIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARMENUDEMOMDIDOC_H__38474A5C_9DC0_11D1_8BAD_0000B43382FE__INCLUDED_)
