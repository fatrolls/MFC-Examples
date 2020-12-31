// ChildFrm.h : interface of the CBaseVariableFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__233727CB_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
#define AFX_CHILDFRM_H__233727CB_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "BaseVarFrame.h"
class CBaseVariableFrame : public CBaseVarFrame
{
	DECLARE_DYNCREATE(CBaseVariableFrame)
private:
	static CRuntimeClass** m_pClass1;
	static int m_nClass1;
	static int m_nStato1;
public:
	CBaseVariableFrame();
	static void SetConfiguration(CRuntimeClass** pviews,int nviews,int InitialStato) { m_pClass1 = pviews;m_nClass1 = nviews;m_nStato1 = InitialStato;}

// Overrides
protected:
	virtual void OnConfigViews();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseVariableFrame)
	//}}AFX_VIRTUAL

// Implementation
	virtual ~CBaseVariableFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CBaseVariableFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__233727CB_8D12_11D1_A7EA_FC1C8DE6EE74__INCLUDED_)
