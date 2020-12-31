// dragDoc.h : interface of the CDragDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAGDOC_H__36079C8C_1AF5_11D1_A856_0060977B4134__INCLUDED_)
#define AFX_DRAGDOC_H__36079C8C_1AF5_11D1_A856_0060977B4134__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDragDoc : public CDocument
{
protected: // create from serialization only
	CDragDoc();
	DECLARE_DYNCREATE(CDragDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDragDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDragDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGDOC_H__36079C8C_1AF5_11D1_A856_0060977B4134__INCLUDED_)
