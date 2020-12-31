// MsgMapperView.h : interface of the CMsgMapperView class
//


#pragma once
#include "afxwin.h"


class CMsgMapperView : public CEditView
{
protected: // create from serialization only
	CMsgMapperView();
	DECLARE_DYNCREATE(CMsgMapperView)

public:
	enum{ IDD = IDD_MSGMAPPER_FORM };

// Attributes
public:
	CMsgMapperDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMsgMapperView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;

public:

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);


public:
	void ViewRawMessage(void);
public:
	void ViewTextMessage(void);
public:
	void ViewHTMLMessage(void);
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
};

#ifndef _DEBUG  // debug version in MsgMapperView.cpp
inline CMsgMapperDoc* CMsgMapperView::GetDocument() const
   { return reinterpret_cast<CMsgMapperDoc*>(m_pDocument); }
#endif

