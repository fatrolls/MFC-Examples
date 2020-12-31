// HtmlDoc.h : interface of the CHtmlDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLDOC_H__52442BF0_70A1_11D1_8E9B_4854E827046F__INCLUDED_)
#define AFX_HTMLDOC_H__52442BF0_70A1_11D1_8E9B_4854E827046F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CHtmlDoc : public CDocument
{
protected: // create from serialization only
	CHtmlDoc();
	DECLARE_DYNCREATE(CHtmlDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHtmlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHtmlDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLDOC_H__52442BF0_70A1_11D1_8E9B_4854E827046F__INCLUDED_)
