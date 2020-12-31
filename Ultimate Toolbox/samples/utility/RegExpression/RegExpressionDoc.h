// RegExpressionDoc.h : interface of the CRegExpressionDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGEXPRESSIONDOC_H__68584122_9E83_11D3_AC4A_0050BAAB46B1__INCLUDED_)
#define AFX_REGEXPRESSIONDOC_H__68584122_9E83_11D3_AC4A_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "OXRegExpression.h"


class CRegExpressionDoc : public CDocument
{
protected: // create from serialization only
	CRegExpressionDoc();
	DECLARE_DYNCREATE(CRegExpressionDoc)

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegExpressionDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRegExpressionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRegExpressionDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGEXPRESSIONDOC_H__68584122_9E83_11D3_AC4A_0050BAAB46B1__INCLUDED_)
