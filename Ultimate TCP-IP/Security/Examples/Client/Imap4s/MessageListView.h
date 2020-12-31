#if !defined(AFX_MESSAGELISTVIEW_H__1FE0A7E4_27E9_11D3_B75D_00203596449E__INCLUDED_)
#define AFX_MESSAGELISTVIEW_H__1FE0A7E4_27E9_11D3_B75D_00203596449E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageListView.h : header file
//

class CIMAPClientDoc;
/////////////////////////////////////////////////////////////////////////////
// CMessageListView view

#pragma warning ( disable : 4511 4512 ) // VC6 level 4 - copy ctor & op=

class CMessageListView : public CListView
{
protected:
	CMessageListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMessageListView)

// Attributes
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

protected:
		CIMAPClientDoc* GetDocument() const { return (CIMAPClientDoc*)(m_pDocument); }
	
// Implementation
protected:
	virtual ~CMessageListView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void AddMessageEntry(CUT_MsgData * pMessageData);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMessageListView)
	afx_msg void OnDoubleClickItem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 ) // VC6 level 4 - copy ctor & op=

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGELISTVIEW_H__1FE0A7E4_27E9_11D3_B75D_00203596449E__INCLUDED_)
