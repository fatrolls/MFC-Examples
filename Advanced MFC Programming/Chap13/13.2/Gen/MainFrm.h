#if !defined(AFX_MAINFRM_H__21AF8643_30FF_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__21AF8643_30FF_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

class CMainFrame : public CFrameWnd
{
protected:
	DECLARE_DYNCREATE(CMainFrame)

public:
	CMainFrame();
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
//	CStatusBar  m_wndStatusBar;
//	CToolBar    m_wndToolBar;

	//{{AFX_MSG(CMainFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAINFRM_H__21AF8643_30FF_11D1_9C9A_444553540000__INCLUDED_)
