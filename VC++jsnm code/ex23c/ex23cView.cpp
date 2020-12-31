// ex23cView.cpp : implementation of the CEx23cView class
//

#include "stdafx.h"
#include "ex23c.h"

#include "ex23cDoc.h"
#include "ex23cView.h"
#include "Interface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// {692D03A4-C689-11CE-B337-88EA36DE9E4E}
static const IID IID_IMotion =
{ 0x692d03a4, 0xc689, 0x11ce, { 0xb3, 0x37, 0x88, 0xea, 0x36, 0xde, 0x9e, 0x4e } };

// {692D03A5-C689-11CE-B337-88EA36DE9E4E}
static const IID IID_IVisual =
{ 0x692d03a5, 0xc689, 0x11ce, { 0xb3, 0x37, 0x88, 0xea, 0x36, 0xde, 0x9e, 0x4e } };

/////////////////////////////////////////////////////////////////////////////
// CEx23cView

IMPLEMENT_DYNCREATE(CEx23cView, CView)

BEGIN_MESSAGE_MAP(CEx23cView, CView)
	//{{AFX_MSG_MAP(CEx23cView)
	ON_COMMAND(ID_TEST_SPACESHIP, OnTestSpaceship)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx23cView construction/destruction

CEx23cView::CEx23cView()
{
	// TODO: add construction code here

}

CEx23cView::~CEx23cView()
{
}

BOOL CEx23cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx23cView drawing

void CEx23cView::OnDraw(CDC* pDC)
{
	CEx23cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx23cView diagnostics

#ifdef _DEBUG
void CEx23cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx23cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx23cDoc* CEx23cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx23cDoc)));
	return (CEx23cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx23cView message handlers

void CEx23cView::OnTestSpaceship() 
{
    CLSID clsid;
    LPCLASSFACTORY pClf; 
    LPUNKNOWN pUnk;
    IMotion* pMot;
    IVisual* pVis;
    HRESULT hr;

    if ((hr = ::CLSIDFromProgID(L"Spaceship", &clsid)) != NOERROR) {
        TRACE("unable to find Program ID -- error = %x\n", hr);
        return;
    }
    if ((hr = ::CoGetClassObject(clsid, CLSCTX_INPROC_SERVER,
        NULL, IID_IClassFactory, (void **) &pClf)) != NOERROR) {;
        TRACE("unable to find CLSID -- error = %x\n", hr);
        return;
    }

    pClf->CreateInstance(NULL, IID_IUnknown, (void**) &pUnk);
    pUnk->QueryInterface(IID_IMotion, (void**) &pMot); // All three
    pMot->QueryInterface(IID_IVisual, (void**) &pVis); //  pointers
                                                       //  should work
    TRACE("main: pUnk = %p, pMot = %p, pDis = %p\n", pUnk, pMot, pVis);
    
    // Test all the interface virtual functions
    pMot->Fly();
    int nPos = pMot->GetPosition();
    TRACE("nPos = %d\n", nPos);
    pVis->Display();

    pClf->Release();
    pUnk->Release();
    pMot->Release();
    pVis->Release();
    AfxMessageBox("Test succeeded. See Debug window for output.");
}
