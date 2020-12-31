// TestViewAppDoc.h : interface of the CTestViewAppDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEWAPPDOC_H__212B13B7_5FA0_4B16_9EA4_316ECFB46C1E__INCLUDED_)
#define AFX_TESTVIEWAPPDOC_H__212B13B7_5FA0_4B16_9EA4_316ECFB46C1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SomeObject.h"

class CTestViewAppDoc : public CDocument
{
public:

	IPropertyHost* m_pCurrentHost;

	SomeObject0 m_SomeObject0;
	SomeObject1 m_SomeObject1;

protected: // create from serialization only
	CTestViewAppDoc();
	DECLARE_DYNCREATE(CTestViewAppDoc)

// Attributes
public:

	IPropertyHost* GetPropertyHost();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestViewAppDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestViewAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestViewAppDoc)
	afx_msg void OnObject0();
	afx_msg void OnUpdateObject0(CCmdUI* pCmdUI);
	afx_msg void OnObject1();
	afx_msg void OnUpdateObject1(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEWAPPDOC_H__212B13B7_5FA0_4B16_9EA4_316ECFB46C1E__INCLUDED_)
