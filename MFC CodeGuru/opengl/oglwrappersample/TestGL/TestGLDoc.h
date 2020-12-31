// TestGLDoc.h : interface of the CTestGLDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTGLDOC_H__59CED134_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
#define AFX_TESTGLDOC_H__59CED134_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTestGLDoc : public CDocument
{
protected: // create from serialization only
	CTestGLDoc();
	DECLARE_DYNCREATE(CTestGLDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestGLDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestGLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestGLDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGLDOC_H__59CED134_E584_11D1_ACB3_E52ED8AC9002__INCLUDED_)
