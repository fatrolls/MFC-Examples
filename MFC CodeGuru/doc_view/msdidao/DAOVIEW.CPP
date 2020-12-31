// DoaView.cpp : implementation file
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "DaoSet.h"
#include "DaoDoc.h"
#include "DaoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoView

IMPLEMENT_DYNCREATE(CMSDIDaoView, CFormView)

CMSDIDaoView::CMSDIDaoView()
	: CFormView(CMSDIDaoView::IDD)
{
	//{{AFX_DATA_INIT(CMSDIDaoView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMSDIDaoView::~CMSDIDaoView()
{
}

void CMSDIDaoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMSDIDaoView)
	DDX_Text(pDX, IDC_DATABASE_NAME, m_strName);
	DDX_Text(pDX, IDC_DATABASE_VERSION, m_strVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMSDIDaoView, CFormView)
	//{{AFX_MSG_MAP(CMSDIDaoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMSDIDaoView::OnInitialUpdate() 
{
	CMSDIDaoDoc* pDoc = GetDocument();

	// Fill the form with the database data
	m_strName = pDoc->m_db.GetName();
	m_strVersion = pDoc->m_db.GetVersion();

	CFormView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoView diagnostics

#ifdef _DEBUG
void CMSDIDaoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMSDIDaoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMSDIDaoDoc* CMSDIDaoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMSDIDaoDoc)));
	return (CMSDIDaoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoView message handlers
