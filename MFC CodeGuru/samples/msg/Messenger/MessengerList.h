#if !defined(AFX_MESSENGERLIST_H__63D6B2C4_E8E2_11D1_B803_0060084C3BF4__INCLUDED_)
#define AFX_MESSENGERLIST_H__63D6B2C4_E8E2_11D1_B803_0060084C3BF4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MessengerList.h : header file
//

#include "ListCtrlEx.h"
#include "MAILSLOT.H"	// Added by ClassView
#include "MailMessage.h"

/////////////////////////////////////////////////////////////////////////////
// CMessengerList view

class CMessengerList : public CView
{
protected:
	CMessengerList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMessengerList)

// Attributes
public:

protected:
	UINT m_nTimerID;
	CListCtrlEx m_ctlList;

	CServerMailslot m_ServerMailslot;
	CMailMessage m_MailMessage;

// Operations
protected:
	void AddItem(SMailMessage &msg);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessengerList)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMessengerList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMessengerList)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnListDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSENGERLIST_H__63D6B2C4_E8E2_11D1_B803_0060084C3BF4__INCLUDED_)
