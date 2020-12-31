// ChildFrm.cpp : implementation of the CBaseVariableFrame class
//

#include "stdafx.h"
#include "VarSplit.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseVariableFrame
IMPLEMENT_DYNCREATE(CBaseVariableFrame, CBaseVarFrame)

int CBaseVariableFrame::m_nClass1 = 0;
int CBaseVariableFrame::m_nStato1= 0;
CRuntimeClass** CBaseVariableFrame::m_pClass1 = NULL;

BEGIN_MESSAGE_MAP(CBaseVariableFrame, CBaseVarFrame)
	//{{AFX_MSG_MAP(CBaseVariableFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseVariableFrame construction/destruction

CBaseVariableFrame::CBaseVariableFrame()
{
	// TODO: add member initialization code here

}

CBaseVariableFrame::~CBaseVariableFrame()
{
}



/////////////////////////////////////////////////////////////////////////////
// CBaseVariableFrame diagnostics

#ifdef _DEBUG
void CBaseVariableFrame::AssertValid() const
{
	CBaseVarFrame::AssertValid();
}

void CBaseVariableFrame::Dump(CDumpContext& dc) const
{
	CBaseVarFrame::Dump(dc);
}

#endif //_DEBUG

// interface

	void CBaseVariableFrame::OnConfigViews()
{
  ConfigViews(m_pClass1,m_nClass1,m_nStato1);
}
/////////////////////////////////////////////////////////////////////////////
// CBaseVariableFrame message handlers
