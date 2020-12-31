#include "stdafx.h"
#include "NotePad.h"

#include "NPDoc.h"
#include "NPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CNotePadView, CEditView)

BEGIN_MESSAGE_MAP(CNotePadView, CEditView)
	//{{AFX_MSG_MAP(CNotePadView)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(ID_EDIT_TIMEDATE, OnEditTimedate)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_COMMAND(ID_SEARCH_FIND, CEditView::OnEditFind)
	ON_COMMAND(ID_SEARCH_REPLACE, CEditView::OnEditReplace)
	ON_COMMAND(ID_SEARCH_FINDNEXT, CEditView::OnEditRepeat)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_FIND, CEditView::OnUpdateNeedText)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_REPLACE, CEditView::OnUpdateNeedText)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_FINDNEXT, CEditView::OnUpdateNeedFind)
END_MESSAGE_MAP()

CNotePadView::CNotePadView()
{
}

CNotePadView::~CNotePadView()
{
}

BOOL CNotePadView::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);

	return bPreCreated;
}

void CNotePadView::OnDraw(CDC* pDC)
{
	CNotePadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CNotePadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CEditView::OnPreparePrinting(pInfo);
}

void CNotePadView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CNotePadView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CEditView::OnEndPrinting(pDC, pInfo);
}

#ifdef _DEBUG
void CNotePadView::AssertValid() const
{
	CEditView::AssertValid();
}

void CNotePadView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNotePadDoc *CNotePadView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNotePadDoc)));
	return (CNotePadDoc*)m_pDocument;
}
#endif

void CNotePadView::OnEditSelectall() 
{
	CEdit &edit=GetEditCtrl();
	edit.SetSel(0, -1);
}

void CNotePadView::OnEditTimedate() 
{
	CTime time;
	CString szTime;

	CEdit &edit=GetEditCtrl();
	time=CTime::GetCurrentTime();
	szTime=time.Format("%A, %B %d, %Y");
	edit.ReplaceSel(szTime);
}

void CNotePadView::OnEditDelete() 
{
	CEdit &edit=GetEditCtrl();
	edit.Clear();	
}
