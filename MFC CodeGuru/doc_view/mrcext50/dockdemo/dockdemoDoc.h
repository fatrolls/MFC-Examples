// dockdemoDoc.h : interface of the CDockdemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCKDEMODOC_H__10B67B98_85D7_11D1_BAA0_006097DA5345__INCLUDED_)
#define AFX_DOCKDEMODOC_H__10B67B98_85D7_11D1_BAA0_006097DA5345__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDockdemoDoc : public CDocument
{
protected: // create from serialization only
	CDockdemoDoc();
	DECLARE_DYNCREATE(CDockdemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockdemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDockdemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDockdemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCKDEMODOC_H__10B67B98_85D7_11D1_BAA0_006097DA5345__INCLUDED_)
