// HttpAnalyzerView.cpp : implementation of the CHttpAnalyzerView class
//

#include "stdafx.h"
#include "HttpAnalyzer.h"

#include "HttpAnalyzerDoc.h"
#include "HttpAnalyzerView.h"

#include "AnalyzerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerView

IMPLEMENT_DYNCREATE(CHttpAnalyzerView, CHtmlView)

BEGIN_MESSAGE_MAP(CHttpAnalyzerView, CHtmlView)
	//{{AFX_MSG_MAP(CHttpAnalyzerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerView construction/destruction

CHttpAnalyzerView::CHttpAnalyzerView()
{
	// TODO: add construction code here

}

CHttpAnalyzerView::~CHttpAnalyzerView()
{
}

BOOL CHttpAnalyzerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerView drawing

void CHttpAnalyzerView::OnDraw(CDC* pDC)
{
	CHttpAnalyzerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CHttpAnalyzerView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	CAnalyzerDlg *_pdlg;
	_pclient=new W3Client();
	_pdlg=new CAnalyzerDlg();

	_pdlg->Create(IDD_ANALYZER);
	_pdlg->ShowWindow(SW_SHOW);		
	_pdlg->_pclient=_pclient;
	_pdlg->_pview=this;
	

}

void CHttpAnalyzerView::doShow(){
	char buf[1024]="\0";

	::GetCurrentDirectory(1024, buf);
	
	CString szurl;

	szurl.Format("%s\\tmp.html", buf);

	Navigate2((const char*)szurl);
}

/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerView diagnostics

#ifdef _DEBUG
void CHttpAnalyzerView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHttpAnalyzerView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHttpAnalyzerDoc* CHttpAnalyzerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHttpAnalyzerDoc)));
	return (CHttpAnalyzerDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CHttpAnalyzerView message handlers
