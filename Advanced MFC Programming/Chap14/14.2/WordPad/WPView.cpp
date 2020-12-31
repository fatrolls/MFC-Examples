#include "stdafx.h"
#include "WordPad.h"
#include "WPDoc.h"
#include "CntrItem.h"
#include "WPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CWordPadView, CRichEditView)

BEGIN_MESSAGE_MAP(CWordPadView, CRichEditView)
	//{{AFX_MSG_MAP(CWordPadView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
	ON_COMMAND(ID_BUTTON_FORMATCENTER, CRichEditView::OnParaCenter)
	ON_COMMAND(ID_BUTTON_FORMATRIGHT, CRichEditView::OnParaRight)
	ON_COMMAND(ID_BUTTON_FORMATBOLD, CRichEditView::OnCharBold)
	ON_COMMAND(ID_BUTTON_FORMATUNDER, CRichEditView::OnCharUnderline)
	ON_COMMAND(ID_BUTTON_FORMATITALIC, CRichEditView::OnCharItalic)
	ON_COMMAND(ID_BUTTON_FORMATLEFT, CRichEditView::OnParaLeft)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FORMATBOLD, CRichEditView::OnUpdateCharBold)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FORMATCENTER, CRichEditView::OnUpdateParaCenter)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FORMATITALIC, CRichEditView::OnUpdateCharItalic)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FORMATLEFT, CRichEditView::OnUpdateParaLeft)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FORMATRIGHT, CRichEditView::OnUpdateParaRight)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FORMATUNDER, CRichEditView::OnUpdateCharUnderline)
END_MESSAGE_MAP()

CWordPadView::CWordPadView()
{
}

CWordPadView::~CWordPadView()
{
}

BOOL CWordPadView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CRichEditView::PreCreateWindow(cs);
}

void CWordPadView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();
	SetMargins(CRect(720, 720, 720, 720));
}

BOOL CWordPadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}


void CWordPadView::OnDestroy()
{
   CRichEditView::OnDestroy();
   COleClientItem *pActiveItem=GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}

#ifdef _DEBUG
void CWordPadView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CWordPadView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CWordPadDoc* CWordPadView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWordPadDoc)));
	return (CWordPadDoc*)m_pDocument;
}
#endif
