// SkinsDemoDoc.h : interface of the CSkinsDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINSDEMODOC_H__5DEE868B_D902_4983_87E2_89DEC3E5E609__INCLUDED_)
#define AFX_SKINSDEMODOC_H__5DEE868B_D902_4983_87E2_89DEC3E5E609__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSkinsDemoDoc : public CDocument
{
protected: // create from serialization only
	CSkinsDemoDoc();
	DECLARE_DYNCREATE(CSkinsDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinsDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkinsDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkinsDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSDEMODOC_H__5DEE868B_D902_4983_87E2_89DEC3E5E609__INCLUDED_)
