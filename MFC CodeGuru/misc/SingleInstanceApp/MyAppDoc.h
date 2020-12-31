// MyAppDoc.h : interface of the CMyAppDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYAPPDOC_H__F5A19131_E409_11D1_A6DF_00A0C9A23BCD__INCLUDED_)
#define AFX_MYAPPDOC_H__F5A19131_E409_11D1_A6DF_00A0C9A23BCD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMyAppDoc : public CDocument
{
protected: // create from serialization only
	CMyAppDoc();
	DECLARE_DYNCREATE(CMyAppDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAppDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyAppDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYAPPDOC_H__F5A19131_E409_11D1_A6DF_00A0C9A23BCD__INCLUDED_)
