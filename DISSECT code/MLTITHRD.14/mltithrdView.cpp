// mltithrdView.cpp : implementation of the CMltithrdView class
//

#include "stdafx.h"
#include "mltithrd.h"

#include "mltithrdDoc.h"
#include "mltithrdView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMltithrdView

IMPLEMENT_DYNCREATE(CMltithrdView, CView)

BEGIN_MESSAGE_MAP(CMltithrdView, CView)
        //{{AFX_MSG_MAP(CMltithrdView)
                // NOTE - the ClassWizard will add and remove mapping macros here.
                //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
        // Standard printing commands
        ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
        ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMltithrdView construction/destruction

CMltithrdView::CMltithrdView()
{
        // TODO: add construction code here

}

CMltithrdView::~CMltithrdView()
{
}

BOOL CMltithrdView::PreCreateWindow(CREATESTRUCT& cs)
{
        // TODO: Modify the Window class or styles here by modifying
        //  the CREATESTRUCT cs

        return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMltithrdView drawing

void CMltithrdView::OnDraw(CDC* pDC)
{
        CMltithrdDoc* pDoc = GetDocument();
        ASSERT_VALID(pDoc);

        // TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMltithrdView printing

BOOL CMltithrdView::OnPreparePrinting(CPrintInfo* pInfo)
{
        // default preparation
        return DoPreparePrinting(pInfo);
}

void CMltithrdView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
        // TODO: add extra initialization before printing
}

void CMltithrdView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
        // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMltithrdView diagnostics

#ifdef _DEBUG
void CMltithrdView::AssertValid() const
{
        CView::AssertValid();
}

void CMltithrdView::Dump(CDumpContext& dc) const
{
        CView::Dump(dc);
}

CMltithrdDoc* CMltithrdView::GetDocument() // non-debug version is inline
{
        ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMltithrdDoc)));
        return (CMltithrdDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMltithrdView message handlers

UINT CMltithrdView::ThreadFunc(LPVOID ThreadArg)
{
DWORD dwArg = *(DWORD*)ThreadArg;

    return 0;
}

