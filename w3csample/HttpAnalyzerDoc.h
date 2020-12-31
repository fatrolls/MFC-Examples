// HttpAnalyzerDoc.h : interface of the CHttpAnalyzerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPANALYZERDOC_H__1431FCF8_EA52_47E7_98E6_D637D460741F__INCLUDED_)
#define AFX_HTTPANALYZERDOC_H__1431FCF8_EA52_47E7_98E6_D637D460741F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHttpAnalyzerDoc : public CDocument
{
protected: // create from serialization only
	CHttpAnalyzerDoc();
	DECLARE_DYNCREATE(CHttpAnalyzerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHttpAnalyzerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHttpAnalyzerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHttpAnalyzerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTTPANALYZERDOC_H__1431FCF8_EA52_47E7_98E6_D637D460741F__INCLUDED_)
