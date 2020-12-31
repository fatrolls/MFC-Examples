// BaseVarFrame.h : interface of the CBaseVarFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEVARFRM_H__233727CB_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
#define AFX_BASEVARFRM_H__233727CB_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CBaseVarFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CBaseVarFrame)
public:
	CBaseVarFrame();

// Attributes
private:
	CSplitterWnd* m_pwndSplitter;
	CSplitterWnd* m_pwndSplitter1;
	int m_nStato;
CRuntimeClass** m_pClass;
int m_nClass;
CRuntimeClass* m_pDefaultView;
private:
	BOOL RebuildSpitter();
public:
// Operations
	void ConfigViews(CRuntimeClass** pviews,int nviews,int InitialStato);
public:

// Overrides
protected:
	virtual void OnConfigViews();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseVarFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
 	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBaseVarFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CBaseVarFrame)
	afx_msg void OnSplitterUno();
	afx_msg void OnUpdateSplitterUno(CCmdUI* pCmdUI);
	afx_msg void OnSplitterDue();
	afx_msg void OnUpdateSplitterDue(CCmdUI* pCmdUI);
	afx_msg void OnSplitterTre();
	afx_msg void OnUpdateSplitterTre(CCmdUI* pCmdUI);
	afx_msg void OnSplitterNessuno();
	afx_msg void OnUpdateSplitterNessuno(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEVARFRM_H__233727CB_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
