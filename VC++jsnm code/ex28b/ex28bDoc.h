// ex28bDoc.h : interface of the CEx28bDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX28BDOC_H__E38A6DC1_6F02_11D0_860F_D6B8FDE4DD70__INCLUDED_)
#define AFX_EX28BDOC_H__E38A6DC1_6F02_11D0_860F_D6B8FDE4DD70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEx28bDoc : public CDocument
{
protected: // create from serialization only
	CEx28bDoc();
	DECLARE_DYNCREATE(CEx28bDoc)

// Attributes
public:
	CEx28bSet m_ex28bSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx28bDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx28bDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx28bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX28BDOC_H__E38A6DC1_6F02_11D0_860F_D6B8FDE4DD70__INCLUDED_)
