// LookMaSDIDoc.h : interface of the CLookMaSDIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOOKMASDIDOC_H__B5EC07FE_CFAB_11D1_AE93_0004AC31E75C__INCLUDED_)
#define AFX_LOOKMASDIDOC_H__B5EC07FE_CFAB_11D1_AE93_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CLookMaSDIDoc : public CDocument
{
protected: // create from serialization only
	CLookMaSDIDoc();
	DECLARE_DYNCREATE(CLookMaSDIDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLookMaSDIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLookMaSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLookMaSDIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOOKMASDIDOC_H__B5EC07FE_CFAB_11D1_AE93_0004AC31E75C__INCLUDED_)
