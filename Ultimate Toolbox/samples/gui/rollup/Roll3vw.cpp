// Roll3vw.cpp : implementation of the CRoll32View class
//

#include "stdafx.h"
#include "Roll32.h"

#include "Roll3doc.h"
#include "Roll3vw.h"
#include "example.h"
#include "maxvirtd.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoll32View

IMPLEMENT_DYNCREATE(CRoll32View, CView)

#define new DEBUG_NEW

BEGIN_MESSAGE_MAP(CRoll32View, CView)
	//{{AFX_MSG_MAP(CRoll32View)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_ROLLUP_NOTIFICATION()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoll32View construction/destruction

CRoll32View::CRoll32View()
{
	// TODO: add construction code here

}

CRoll32View::~CRoll32View()
{
}

/////////////////////////////////////////////////////////////////////////////
// CRoll32View drawing

void CRoll32View::OnDraw(CDC* pDC)
{
	CRoll32Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  	CString strOutput = pDoc->m_strTestText;
  	CRect rect;
  	GetClientRect(&rect);
  	
  	pDC->SetTextAlign(TA_CENTER|TA_BOTTOM);
  	pDC->TextOut(rect.Width()/2,rect.Height()/2,strOutput,strOutput.GetLength());
}

/////////////////////////////////////////////////////////////////////////////
// CRoll32View printing

BOOL CRoll32View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRoll32View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRoll32View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRoll32View diagnostics

#ifdef _DEBUG
void CRoll32View::AssertValid() const
{
	CView::AssertValid();
}

void CRoll32View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRoll32Doc* CRoll32View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRoll32Doc)));
	return (CRoll32Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRoll32View message handlers

void CRoll32View::OnDestroy() 
{
	CView::OnDestroy();
	
	CExample *pExample = ((CRoll32App *)AfxGetApp())->GetExampleRollup();
	pExample->ReleaseRecipient(this);
}

void CRoll32View::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	

	// simply set our view as message recipient
	CExample* pExample = ((CRoll32App*)AfxGetApp())->GetExampleRollup();
	if (! pExample->IsOwner( this ))
	{
		pExample->SetRecipient(this);
		pExample->m_strTestEdit = GetDocument()->m_strTestText;
		pExample->RUpdateData(FALSE);
	}

}

BOOL CRoll32View::OnRollupMessage(CWnd* pWndRollup,UINT message,UINT rollupID)
{
	CExample* pExample = ((CRoll32App*)AfxGetApp())->GetExampleRollup();
	if (pExample->GetRollupID() == rollupID)
	{
		switch (message)
		{
			case ID_APPLY:
				GetDocument()->m_strTestText = ((CExample*)pWndRollup)->m_strTestEdit;
				Invalidate();
				break;
			default:
				TRACE2("Unhandled message %d from Rollup %d\n",message,rollupID);
				break;
		}
    }
    // messages from other rollups are being ignored!!!
    return TRUE;
}

void CRoll32View::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);
	CMaxVirtDialog *pMaxVirt = new CMaxVirtDialog(this);
	
	TCHAR achBuffer[64];
	UTBStr::stprintf(achBuffer, 64,_T("MVT: %ld"),::GetTickCount());

	pMaxVirt->CreateRollUp(this,15,achBuffer);
	ClientToScreen(&point);
	pMaxVirt->SetWindowPos(NULL,point.x,point.y,0,0,SWP_NOZORDER|SWP_NOSIZE);
	pMaxVirt->ShowWindow(SW_SHOWNORMAL);

	// if you´re searching for the delete, see maxvirtd.cpp PostNcDestroy
	// and OnCloseRollup
}
