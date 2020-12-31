// HtmlClockDoc.h : interface of the CHtmlClockDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLCLOCKDOC_H__D39825EB_99C0_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_HTMLCLOCKDOC_H__D39825EB_99C0_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHtmlClockDoc : public CDocument
{
protected: // create from serialization only
	CHtmlClockDoc();
	DECLARE_DYNCREATE(CHtmlClockDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlClockDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHtmlClockDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHtmlClockDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLCLOCKDOC_H__D39825EB_99C0_11D2_8E53_006008A82731__INCLUDED_)
