// demo_toolbarDoc.h : interface of the CDemo_toolbarDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO_TOOLBARDOC_H__6F831B2D_0710_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_DEMO_TOOLBARDOC_H__6F831B2D_0710_11D2_AB9F_441100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDemo_toolbarDoc : public CDocument
{
protected: // create from serialization only
	CDemo_toolbarDoc();
	DECLARE_DYNCREATE(CDemo_toolbarDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_toolbarDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemo_toolbarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo_toolbarDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_TOOLBARDOC_H__6F831B2D_0710_11D2_AB9F_441100C10000__INCLUDED_)
