// FastTestDoc.h : interface of the CFastTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FASTTESTDOC_H__7137DC97_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
#define AFX_FASTTESTDOC_H__7137DC97_B77C_11D1_AE72_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CFastTestDoc : public CDocument
{
protected: // create from serialization only
	CFastTestDoc();
	DECLARE_DYNCREATE(CFastTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFastTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFastTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFastTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTTESTDOC_H__7137DC97_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
