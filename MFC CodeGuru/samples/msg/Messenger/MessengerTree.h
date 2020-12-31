// MessengerView.h : interface of the CMessengerTree class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSENGERVIEW_H__3987ADD0_E657_11D1_B802_0060084C3BF4__INCLUDED_)
#define AFX_MESSENGERVIEW_H__3987ADD0_E657_11D1_B802_0060084C3BF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NetworkTreeCtrl.h"

class CMessengerTree : public CView
{
protected: // create from serialization only
	CMessengerTree();
	DECLARE_DYNCREATE(CMessengerTree)

// Attributes
public:

protected:
	CImageList	m_ctlImage;

	CNetworkTreeCtrl m_ctlTree;

// Operations
public:
	void SendTo(LPCSTR pComputerName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessengerTree)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMessengerTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:

	//{{AFX_MSG(CMessengerTree)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnToolsRefreshNetworkTree();
	afx_msg void OnSendButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSENGERVIEW_H__3987ADD0_E657_11D1_B802_0060084C3BF4__INCLUDED_)
