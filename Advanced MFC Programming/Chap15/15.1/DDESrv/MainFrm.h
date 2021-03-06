#if !defined(AFX_MAINFRM_H__747EBB28_49F6_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_MAINFRM_H__747EBB28_49F6_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "DDEML.H"

#define NUM_TOPICS		2

class CDDESrvView;

class CMainFrame : public CFrameWnd
{
protected:
	static DWORD m_dwInst;
	static HSZ m_hszServiceName;
	static TCHAR m_szService[];
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

public:
	void InitializeDDE();
	static HDDEDATA CALLBACK DdeCallback(UINT, UINT, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD);
	static void Hszize();
	static void UnHszize();
	static CDDESrvView *GetCDDESrvView();
	static void Printf(const char *, ...);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAINFRM_H__747EBB28_49F6_11D1_9C9A_444553540000__INCLUDED_)
