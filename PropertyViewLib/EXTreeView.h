#if !defined(AFX_NAVIPLOTTREEVIEW_H__A5860809_062A_42C0_A968_4A13DBE328C0__INCLUDED_)
#define AFX_NAVIPLOTTREEVIEW_H__A5860809_062A_42C0_A968_4A13DBE328C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NaviPlotTreeView.h : header file
//
#include "EXTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// EXTreeView view

class EXTreeView : public CView
{

protected:

	EXTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(EXTreeView)

//	void InitTree( ITreeMember* pRoot , int nIconsBitmap );

public:

	EXTreeCtrl m_tree;

public:

	//{{AFX_VIRTUAL(EXTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL


protected:

	virtual ~EXTreeView();

	#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	#endif

protected:

	//{{AFX_MSG(EXTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnEditMoveup();
//	afx_msg void OnEditMovedown();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVIPLOTTREEVIEW_H__A5860809_062A_42C0_A968_4A13DBE328C0__INCLUDED_)
