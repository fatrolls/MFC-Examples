// clipexamDoc.h : interface of the CClipExamDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPEXAMDOC_H__DBF687F3_868E_11D1_B99D_00A0C9763A0A__INCLUDED_)
#define AFX_CLIPEXAMDOC_H__DBF687F3_868E_11D1_B99D_00A0C9763A0A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CClipExamDoc : public CDocument
{
protected: // create from serialization only
	CClipExamDoc();
	DECLARE_DYNCREATE(CClipExamDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipExamDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClipExamDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClipExamDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CClipExamDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPEXAMDOC_H__DBF687F3_868E_11D1_B99D_00A0C9763A0A__INCLUDED_)
