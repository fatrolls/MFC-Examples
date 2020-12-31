// OtherDoc.h : interface of the COtherDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTHERDOC_H__3BB8C3C4_8688_11D1_BAA1_006097DA5345__INCLUDED_)
#define AFX_OTHERDOC_H__3BB8C3C4_8688_11D1_BAA1_006097DA5345__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class COtherDoc : public CDocument
{
protected: // create from serialization only
	COtherDoc();
	DECLARE_DYNCREATE(COtherDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COtherDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COtherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COtherDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHERDOC_H__3BB8C3C4_8688_11D1_BAA1_006097DA5345__INCLUDED_)
