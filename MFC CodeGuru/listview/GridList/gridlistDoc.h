// gridlistDoc.h : interface of the CGridlistDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDLISTDOC_H__92CA598D_9434_11D1_88D5_444553540000__INCLUDED_)
#define AFX_GRIDLISTDOC_H__92CA598D_9434_11D1_88D5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGridlistDoc : public CDocument
{
protected: // create from serialization only
	CGridlistDoc();
	DECLARE_DYNCREATE(CGridlistDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridlistDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridlistDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGridlistDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDLISTDOC_H__92CA598D_9434_11D1_88D5_444553540000__INCLUDED_)
