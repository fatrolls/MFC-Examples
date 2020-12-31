// mymenuDoc.h : interface of the CMymenuDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMENUDOC_H__3BAD410C_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_)
#define AFX_MYMENUDOC_H__3BAD410C_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMymenuDoc : public CDocument
{
protected: // create from serialization only
	CMymenuDoc();
	DECLARE_DYNCREATE(CMymenuDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMymenuDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMymenuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMymenuDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMENUDOC_H__3BAD410C_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_)
