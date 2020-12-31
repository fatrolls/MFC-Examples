#include "stdafx.h"
#include "DB.h"
#include "DBDoc.h"
#include "DBView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDBView, CFormView)

BEGIN_MESSAGE_MAP(CDBView, CFormView)
	//{{AFX_MSG_MAP(CDBView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

CDBView::CDBView()
	: CFormView(CDBView::IDD)
{
	//{{AFX_DATA_INIT(CDBView)
	//}}AFX_DATA_INIT
	m_bSizeAvailable=FALSE;
}

CDBView::~CDBView()
{
}

void CDBView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBView)
	//}}AFX_DATA_MAP
}

BOOL CDBView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

BOOL CDBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CDBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CDBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CDBView::OnPrint(CDC* pDC, CPrintInfo*)
{
}

#ifdef _DEBUG
void CDBView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDBView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDBDoc* CDBView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBDoc)));
	return (CDBDoc*)m_pDocument;
}
#endif

void CDBView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);

	if(m_bSizeAvailable == TRUE)
	{
		CRect rectA;
		CRect rectB;
		CRect rectEdit;
		CRect rectStaticGrp;
		CRect rectDlg(0, 0, m_rectA.right+10, m_rectStaticGrp.bottom+10);

		GetDlgItem(IDC_BUTTON_A)->GetClientRect(rectA);
		GetDlgItem(IDC_BUTTON_B)->GetClientRect(rectB);
		GetDlgItem(IDC_EDIT)->GetWindowRect(rectEdit);
		ScreenToClient(rectEdit);
		GetDlgItem(IDC_STATIC_GRP)->GetWindowRect(rectStaticGrp);
		ScreenToClient(rectStaticGrp);

		rectA.OffsetRect(0, m_rectA.top);
		rectB.OffsetRect(0, m_rectB.top);
		if(cx > rectDlg.Width())
		{
			rectA.OffsetRect(cx-(rectDlg.right-m_rectA.left), 0);
			rectB.OffsetRect(cx-(rectDlg.right-m_rectB.left), 0);
			rectEdit.right=cx-(rectDlg.right-m_rectEdit.right);
			rectStaticGrp.right=cx-(rectDlg.right-m_rectStaticGrp.right);
		}
		else
		{
			rectA.OffsetRect(m_rectA.left, 0);
			rectB.OffsetRect(m_rectB.left, 0);
			rectEdit.right=m_rectEdit.right;
			rectStaticGrp.right=m_rectStaticGrp.right;
		}

		if(cy > rectDlg.Height())
		{
			rectEdit.bottom=cy-(rectDlg.bottom-m_rectEdit.bottom);
			rectStaticGrp.top=cy-(rectDlg.bottom-m_rectStaticGrp.top);
			rectStaticGrp.bottom=cy-(rectDlg.bottom-m_rectStaticGrp.bottom);
		}
		else
		{
			rectEdit.bottom=m_rectEdit.bottom;
			rectStaticGrp.top=m_rectStaticGrp.top;
			rectStaticGrp.bottom=m_rectStaticGrp.bottom;
		}

		GetDlgItem(IDC_BUTTON_A)->MoveWindow(rectA);
		GetDlgItem(IDC_BUTTON_B)->MoveWindow(rectB);
		GetDlgItem(IDC_EDIT)->MoveWindow(rectEdit);
		GetDlgItem(IDC_STATIC_GRP)->MoveWindow(rectStaticGrp);
	}
}

void CDBView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	GetDlgItem(IDC_BUTTON_A)->GetWindowRect(m_rectA);
	ScreenToClient(m_rectA);
	GetDlgItem(IDC_BUTTON_B)->GetWindowRect(m_rectB);
	ScreenToClient(m_rectB);
	GetDlgItem(IDC_EDIT)->GetWindowRect(m_rectEdit);
	ScreenToClient(m_rectEdit);
	GetDlgItem(IDC_STATIC_GRP)->GetWindowRect(m_rectStaticGrp);
	ScreenToClient(m_rectStaticGrp);
	
	m_bSizeAvailable=TRUE;	
}
