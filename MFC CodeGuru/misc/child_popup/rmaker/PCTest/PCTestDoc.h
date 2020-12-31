// PCTestDoc.h : interface of the CPCTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCTESTDOC_H__D1BB416D_804D_11D1_80B6_080009CC78D8__INCLUDED_)
#define AFX_PCTESTDOC_H__D1BB416D_804D_11D1_80B6_080009CC78D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CPCTestDoc : public CDocument
{
protected: // create from serialization only
	CPCTestDoc();
	DECLARE_DYNCREATE(CPCTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPCTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPCTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCTESTDOC_H__D1BB416D_804D_11D1_80B6_080009CC78D8__INCLUDED_)
