// ex11View.h : interface of the CEx11View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX11VIEW_H__289CB96E_3A41_11D1_9774_004033298A13__INCLUDED_)
#define AFX_EX11VIEW_H__289CB96E_3A41_11D1_9774_004033298A13__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MyBtn.h"

class CEx11View : public CFormView
{
protected: // create from serialization only
	CEx11View();
	DECLARE_DYNCREATE(CEx11View)

public:
	//{{AFX_DATA(CEx11View)
	enum{ IDD = IDD_EX11_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CEx11Doc* GetDocument();

	CMyBtn    m_MyBtn;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx11View)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx11View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx11View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex11View.cpp
inline CEx11Doc* CEx11View::GetDocument()
   { return (CEx11Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX11VIEW_H__289CB96E_3A41_11D1_9774_004033298A13__INCLUDED_)
