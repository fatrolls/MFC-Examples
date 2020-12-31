// TestPrintFormDoc.h : interface of the CTestPrintFormDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPRINTFORMDOC_H__F206742A_101A_11D2_8432_0000B43382FE__INCLUDED_)
#define AFX_TESTPRINTFORMDOC_H__F206742A_101A_11D2_8432_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CTestPrintFormDoc : public CDocument
{
protected: // create from serialization only
	CTestPrintFormDoc();
	DECLARE_DYNCREATE(CTestPrintFormDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPrintFormDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestPrintFormDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestPrintFormDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPRINTFORMDOC_H__F206742A_101A_11D2_8432_0000B43382FE__INCLUDED_)
