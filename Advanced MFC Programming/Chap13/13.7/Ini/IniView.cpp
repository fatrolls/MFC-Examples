#include "stdafx.h"
#include "Ini.h"
#include "IniDoc.h"
#include "IniView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CIniView, CView)

BEGIN_MESSAGE_MAP(CIniView, CView)
	//{{AFX_MSG_MAP(CIniView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CIniView::CIniView()
{
}

CIniView::~CIniView()
{
}

BOOL CIniView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CIniView::OnDraw(CDC* pDC)
{
	CIniDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CIniView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CIniView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CIniView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CIniView::AssertValid() const
{
	CView::AssertValid();
}

void CIniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIniDoc* CIniView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIniDoc)));
	return (CIniDoc*)m_pDocument;
}
#endif
