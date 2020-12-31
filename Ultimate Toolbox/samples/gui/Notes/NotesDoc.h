// NotesDoc.h : interface of the CNotesDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTESDOC_H__80E35B02_070A_11D4_ACEF_0050BAAB46B1__INCLUDED_)
#define AFX_NOTESDOC_H__80E35B02_070A_11D4_ACEF_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNotesDoc : public CDocument
{
protected: // create from serialization only
	CNotesDoc();
	DECLARE_DYNCREATE(CNotesDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotesDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNotesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNotesDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTESDOC_H__80E35B02_070A_11D4_ACEF_0050BAAB46B1__INCLUDED_)
