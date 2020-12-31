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
	static HSZ m_hszTopicName;
	static HSZ m_hszTimeItem;
	static HSZ m_hszTextItem;
	static HSZ m_hszPokeItem;
	static HCONV m_hConvServer;
	static TCHAR m_szService[];
	static TCHAR m_szTopic[];
	static TCHAR m_szTimeItem[];
	static TCHAR m_szTextItem[];
	static TCHAR m_szPokeItem[];
	static BOOL m_bAdvise;
	static CString m_szText;
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
	afx_msg void OnDdeDisconnect();
	afx_msg void OnUpdateDdeDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnDdeAdvise();
	afx_msg void OnUpdateDdeAdvise(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_MAINFRM_H__747EBB28_49F6_11D1_9C9A_444553540000__INCLUDED_)
