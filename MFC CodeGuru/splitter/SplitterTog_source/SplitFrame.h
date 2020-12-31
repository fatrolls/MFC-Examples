#if ! defined( __SPLITFRAME_H__ )
#define __SPLITFRAME_H__

#if _MSC_VER >= 1000
	#pragma once
#endif // _MSC_VER >= 1000

/*
** Author: Guy Gascoigne - Piggford
** Internet: guy@wyrdrune.com
**
** You can use this source in any way you like as long as you don't try to sell it.
**
** Any attempt to sell this in source code form must have the permission
** of the original author. You can produce commercial executables with
** this source, but you may not sell it.
**
** Copyright, 1994-98 Guy Gascoigne - Piggford
**
*/

#include "TogSplitterWnd.h"

class CSplitFrame : public CMDIChildWnd
{
	BOOL m_bInitialOrientation;

	CSize m_splitSizes[2];
	CTogSplitterWnd m_wndSplitter;
	CRuntimeClass * m_pView1;
	CRuntimeClass * m_pView2;

protected: // create from serialization / derivation only
	CSplitFrame( CRuntimeClass * pView1, CRuntimeClass * pView2 );
	DECLARE_DYNAMIC(CSplitFrame)

// Attributes
public:

	BOOL BarIsHorizontal() const { return m_wndSplitter.BarIsHorizontal(); }
	void SetInitialOrienation( BOOL bHoriz );

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplitFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	void MakeSplitSizes( BOOL horizBar, CSize & sz1, CSize & sz2 );

// Generated message map functions
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	void viewSomeView( int iView );
	CSize ReadCachedSize( BOOL horizBar );
	void CacheSize();

	//{{AFX_MSG(CSplitFrame)
	afx_msg void OnToggleSplitter();
	afx_msg void OnUpdateToggleSplitter(CCmdUI* pCmdUI);
	afx_msg void OnViewBoth();
	afx_msg void OnViewFirstView();
	afx_msg void OnViewSecondView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.


#endif //__SPLITFRAME_H__
