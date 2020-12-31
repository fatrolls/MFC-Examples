// LayoutDoc.h : interface of the CLayoutDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYOUTDOC_H__7D955F30_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
#define AFX_LAYOUTDOC_H__7D955F30_0A9F_11D2_88B8_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CLayoutDoc : public CDocument
{
protected: // create from serialization only
	CLayoutDoc();
	DECLARE_DYNCREATE(CLayoutDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayoutDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLayoutDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLayoutDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYOUTDOC_H__7D955F30_0A9F_11D2_88B8_0080C859A484__INCLUDED_)
