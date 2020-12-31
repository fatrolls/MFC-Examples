// CBaseVarFrame.cpp : implementation of the CBaseVarFrame class
//

#include "stdafx.h"
#include "resource.h"
#include "BaseVarFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseVarFrame
IMPLEMENT_DYNCREATE(CBaseVarFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CBaseVarFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CBaseVarFrame)
	ON_COMMAND(ID_SPLITTER_UNO, OnSplitterUno)
	ON_UPDATE_COMMAND_UI(ID_SPLITTER_UNO, OnUpdateSplitterUno)
	ON_COMMAND(ID_SPLITTER_DUE, OnSplitterDue)
	ON_UPDATE_COMMAND_UI(ID_SPLITTER_DUE, OnUpdateSplitterDue)
	ON_COMMAND(ID_SPLITTER_TRE, OnSplitterTre)
	ON_UPDATE_COMMAND_UI(ID_SPLITTER_TRE, OnUpdateSplitterTre)
	ON_COMMAND(ID_SPLITTER_NESSUNO, OnSplitterNessuno)
	ON_UPDATE_COMMAND_UI(ID_SPLITTER_NESSUNO, OnUpdateSplitterNessuno)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseVarFrame construction/destruction

CBaseVarFrame::CBaseVarFrame()
{
	// TODO: add member initialization code here
m_nStato = 0;
m_pwndSplitter = new CSplitterWnd;	
m_pwndSplitter1 = new CSplitterWnd;
 m_pClass = NULL;
m_pDefaultView = NULL;

}

CBaseVarFrame::~CBaseVarFrame()
{
	if (m_pwndSplitter)
		delete m_pwndSplitter;
	if (m_pwndSplitter1)
		delete m_pwndSplitter1;
}

BOOL CBaseVarFrame::OnCreateClient( LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{

 m_pDefaultView = pContext->m_pNewViewClass;
if (m_pClass == NULL)
OnConfigViews();
 if (!m_nStato)
	 return  CMDIChildWnd::OnCreateClient(lpcs,pContext);
	 CSize s3(0,lpcs->cy/m_nStato);
 	if (!m_pwndSplitter->CreateStatic (this, 1, 2))
				 return FALSE;
    if  (!m_pwndSplitter->CreateView (0,0,pContext->m_pNewViewClass,CSize (192, 0) , pContext))
    return FALSE;
	if (m_nStato > 1)
	{			 if (!m_pwndSplitter1->CreateStatic (m_pwndSplitter, m_nStato,1,WS_CHILD|WS_VISIBLE,m_pwndSplitter->IdFromRowCol(0,1)))
				return FALSE;
	for(int i=0;i<m_nStato;i++)
	m_pwndSplitter1->CreateView (i,0,m_pClass[i],s3,pContext);
}
 else if (!m_pwndSplitter->CreateView(0,1,m_pClass[0],CSize(0,0), pContext))
 return FALSE;
 return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBaseVarFrame diagnostics

#ifdef _DEBUG
void CBaseVarFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CBaseVarFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseVarFrame message handlers

void CBaseVarFrame::OnSplitterUno() 
{
	// TODO: Add your command handler code here
if (m_nStato == 1)
return;
	m_nStato = 1;	
RebuildSpitter();
}

void CBaseVarFrame::OnUpdateSplitterUno(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetRadio(m_nStato == 1);
  pCmdUI->Enable(m_nClass > 0);
}

void CBaseVarFrame::OnSplitterDue() 
{
	// TODO: Add your command handler code here
if (m_nStato == 2)
return;
	m_nStato = 2;	
RebuildSpitter();

}

void CBaseVarFrame::OnUpdateSplitterDue(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetRadio(m_nStato == 2);
  pCmdUI->Enable(m_nClass > 1);

	
}

void CBaseVarFrame::OnSplitterTre() 
{
	// TODO: Add your command handler code here
if (m_nStato == 3)
return;
m_nStato = 3;
RebuildSpitter();	
	
}

void CBaseVarFrame::OnUpdateSplitterTre(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_nStato == 3);
	  pCmdUI->Enable(m_nClass > 2);

}

void CBaseVarFrame::OnSplitterNessuno() 
{
	// TODO: Add your command handler code here
if (m_nStato == 0)
return;
m_nStato = 0;
     CView * pActiveView= GetActiveView();

    CDocument * pDoc= pActiveView->GetDocument();
		pDoc->m_bAutoDelete=FALSE;    
m_pwndSplitter1->DestroyWindow();
m_pwndSplitter->DestroyWindow();
 		delete m_pwndSplitter;
 		delete m_pwndSplitter1;
m_pwndSplitter = new CSplitterWnd;	
m_pwndSplitter1 = new CSplitterWnd;	

		pDoc->m_bAutoDelete=TRUE;    

   CCreateContext context;
   context.m_pNewViewClass= m_pDefaultView;
   context.m_pCurrentDoc=pDoc;
   context.m_pNewDocTemplate=NULL;
   context.m_pLastView=NULL;
   context.m_pCurrentFrame=NULL;


	CView* p = (CView*)CreateView(&context, AFX_IDW_PANE_FIRST);

	 SetActiveView(p);
   p->OnInitialUpdate();
	RecalcLayout();
 
}

void CBaseVarFrame::OnUpdateSplitterNessuno(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_nStato == 0);
	
}

BOOL CBaseVarFrame::RebuildSpitter()
{
	CCreateContext context;
    CDocument * pDoc;
 if (m_pwndSplitter->m_hWnd == NULL)
 {
	 CRect r;
	 GetClientRect(r);
CREATESTRUCT s;
s.cy = r.bottom-r.top;
	 CView * pActiveView= GetActiveView();
     pDoc= pActiveView->GetDocument();
	pDoc->m_bAutoDelete=FALSE; 
	   pActiveView->DestroyWindow();
    pDoc->m_bAutoDelete=TRUE;

   context.m_pNewViewClass= m_pDefaultView;
   context.m_pCurrentDoc=pDoc;
   context.m_pNewDocTemplate=NULL;
   context.m_pLastView=NULL;
   context.m_pCurrentFrame=NULL;
  if (!OnCreateClient(&s,&context))
	  return FALSE;
   CView* pV = (CView *)m_pwndSplitter->GetPane(0,0);
   if (pV == NULL)
	   AfxMessageBox("null view");
  SetActiveView(pV);
     pV->OnInitialUpdate();
	 if (m_nStato == 1)
    {
	pV = (CView *)m_pwndSplitter->GetPane(0,1);
     pV->OnInitialUpdate();
	}
	else
		for(int i=0;i< m_nStato;i++)
    {
	pV = (CView *)m_pwndSplitter1->GetPane(i,0);
     pV->OnInitialUpdate();
	}
RecalcLayout();
  return TRUE;
}

 
   // Get pointer to CDocument object so that it can be used in the creation 
   // process of the new view

   CView * pActiveView= GetActiveView();
   if (pActiveView == NULL)
	   AfxMessageBox("noview");
CRect r;
  pActiveView->GetClientRect(r);
  CSize s3(0,0);
   if (m_nStato)
   s3.cy = (r.bottom-r.top)/m_nStato;

 pDoc= pActiveView->GetDocument();
   context.m_pNewViewClass= m_pClass[0];
   context.m_pCurrentDoc=pDoc;
   context.m_pNewDocTemplate=NULL;
   context.m_pLastView=NULL;
   context.m_pCurrentFrame=NULL;

    // set flag so that document will not be deleted when view is destroyed
	pDoc->m_bAutoDelete=FALSE;    
    // Delete existing view 
	int i;

   if (m_pwndSplitter1->m_hWnd)
	   m_pwndSplitter1->DestroyWindow();
  else
	{
   CView* pV = (CView *)m_pwndSplitter->GetPane(0,1);
   pV->DestroyWindow();
	 }

    pDoc->m_bAutoDelete=TRUE;
     if (m_nStato > 1)
	{
       delete m_pwndSplitter1;
	   m_pwndSplitter1 = new CSplitterWnd;	
		if (!m_pwndSplitter1->CreateStatic (m_pwndSplitter, m_nStato,1,WS_CHILD|WS_VISIBLE,m_pwndSplitter->IdFromRowCol(0,1)))
		return FALSE;
	 }
   
   context.m_pNewViewClass= m_pClass[0];
   context.m_pCurrentDoc=pDoc;
   context.m_pNewDocTemplate=NULL;
   context.m_pLastView=NULL;
   context.m_pCurrentFrame=NULL;
if (m_nStato > 1)
   for(i=0;i<m_nStato;i++)
  {
	   m_pwndSplitter1->CreateView(i,0,m_pClass[i],s3, &context);
 
   CView * pNewView= (CView *)m_pwndSplitter1->GetPane(i,0);
   
   	
   pNewView->OnInitialUpdate();
}
else
  {
	
		m_pwndSplitter->CreateView(0,1,m_pClass[0],s3, &context);
 
 		CView * pNewView= (CView *)m_pwndSplitter->GetPane(0,1);
 		pNewView->OnInitialUpdate();
   }
	 SetActiveView((CView*)m_pwndSplitter->GetPane(0,0));

	   m_pwndSplitter->RecalcLayout(); 
 if (m_nStato > 1)
	 m_pwndSplitter1->RecalcLayout(); 
 return TRUE;
}
	void CBaseVarFrame::ConfigViews(CRuntimeClass** pviews,int nviews,int InitialStato)
  {
		m_pClass = pviews;
		m_nClass = nviews;
        m_nStato = InitialStato;
		if (m_nStato >= m_nClass)
			m_nClass = 0;
	}
void CBaseVarFrame::OnConfigViews() 
{
}