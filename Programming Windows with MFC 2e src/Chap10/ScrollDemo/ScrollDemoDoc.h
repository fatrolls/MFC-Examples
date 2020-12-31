// ScrollDemoDoc.h : interface of the CScrollDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCROLLDEMODOC_H__DCCF4E0B_9735_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_SCROLLDEMODOC_H__DCCF4E0B_9735_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScrollDemoDoc : public CDocument
{
protected: // create from serialization only
	CScrollDemoDoc();
	DECLARE_DYNCREATE(CScrollDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScrollDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CScrollDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLDEMODOC_H__DCCF4E0B_9735_11D2_8E53_006008A82731__INCLUDED_)
