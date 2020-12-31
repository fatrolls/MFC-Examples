// XRayView.cpp : implementation of the CXRayView class
//

#include "stdafx.h"
#include "XRay.h"

#include "XRayDoc.h"
#include "XRayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXRayView

IMPLEMENT_DYNCREATE(CXRayView, CView)

BEGIN_MESSAGE_MAP(CXRayView, CView)
	//{{AFX_MSG_MAP(CXRayView)
	ON_COMMAND(ID_ALPHANONE, OnAlphaNone)
	ON_UPDATE_COMMAND_UI(ID_ALPHANONE, OnUpdateAlphaNone)
	ON_COMMAND(ID_ALPHAALPHA, OnAlphaAlpha)
	ON_UPDATE_COMMAND_UI(ID_ALPHAALPHA, OnUpdateAlphaAlpha)
	ON_COMMAND(ID_ALPHASTIPPLED, OnAlphaStippled)
	ON_UPDATE_COMMAND_UI(ID_ALPHASTIPPLED, OnUpdateAlphaStippled)
	ON_COMMAND(ID_COLOR, OnColor)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE ( MSG_PARENTMOVE, OnParentMove )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXRayView construction/destruction

CXRayView::CXRayView ()
{
	// Create Dib
	m_Layer0.Create ( 200, 200 );
	// Open DrawDib
	m_DrawDib.Open ();
	// Get System Metrics
	m_ScreenX=GetSystemMetrics ( SM_CXSCREEN );
	m_ScreenY=GetSystemMetrics ( SM_CYSCREEN );
	// Set Glass Parameters
	m_Alpha=1;
	m_Color=RGB ( 0, 255, 255 );
}

CXRayView::~CXRayView ()
{
	// Destroy Dib
	m_Layer0.Destroy ();
	// Close DrawDib
	m_DrawDib.Close ();
}

BOOL CXRayView::PreCreateWindow ( CREATESTRUCT& cs )
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow ( cs );
}

/////////////////////////////////////////////////////////////////////////////
// CXRayView drawing

void CXRayView::OnDraw ( CDC* pDC )
{
	// Get the WindowRect
	CRect WinRect;
	GetWindowRect ( &WinRect );
	// Get the DesktopDC
	CWnd *Desktop=GetDesktopWindow ();
	CDC *DesktopDC=Desktop->GetDC ();
	// Paste the Desktop into Layer0
	m_Layer0.PasteDC ( DesktopDC, m_ScreenX-100-WinRect.left,
		m_ScreenY-100-WinRect.top, 200, 200 );
	// Release the DesktopDC
	ReleaseDC ( DesktopDC );
	// Place some Glass over it
	if ( m_Alpha & 0x1 )
		m_Layer0.FillGlass ( GetRValue ( m_Color ), GetGValue ( m_Color ),
			GetBValue ( m_Color ), 128 );
	else if ( m_Alpha & 0x2 )
		m_Layer0.FillStippledGlass ( GetRValue ( m_Color ),
			GetGValue ( m_Color ), GetBValue ( m_Color ) );	

	// Use DrawDib to Draw the Dib to Video Memory, use HalfTone for non TC Systems
	m_DrawDib.DrawDib ( &m_Layer0, pDC->m_hDC, 0,0, 200, 200, DDF_HALFTONE );
}

/////////////////////////////////////////////////////////////////////////////
// CXRayView diagnostics

#ifdef _DEBUG
void CXRayView::AssertValid() const
{
	CView::AssertValid();
}

void CXRayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXRayDoc* CXRayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXRayDoc)));
	return (CXRayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXRayView message handlers

HRESULT CXRayView::OnParentMove ( LPARAM, WPARAM )
{
	// Repaint
	Invalidate ( FALSE );

	return NULL;
}

BOOL CXRayView::OnEraseBkgnd(CDC* pDC) 
{
	// Keep Windows from Erasing the BackGround
	return TRUE;
}

void CXRayView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// Set Window Title
	CXRayDoc *pDoc=GetDocument();
	ASSERT_VALID ( pDoc );
	pDoc->SetTitle ( "XRay" );
}

/////////////////////////////////////////////////////////////////////////////
// CXRayView CommandUI handlers

void CXRayView::OnAlphaNone () 
{
	m_Alpha=0;
	Invalidate ( FALSE );
}

void CXRayView::OnUpdateAlphaNone ( CCmdUI* pCmdUI ) 
{
	if ( !m_Alpha )
		pCmdUI->SetCheck ( 1 );
	else
		pCmdUI->SetCheck ( 0 );
}

void CXRayView::OnAlphaAlpha () 
{
	m_Alpha=1;
	Invalidate ( FALSE );
}

void CXRayView::OnUpdateAlphaAlpha ( CCmdUI* pCmdUI ) 
{
	if ( m_Alpha & 0x1 )
		pCmdUI->SetCheck ( 1 );
	else
		pCmdUI->SetCheck ( 0 );
}

void CXRayView::OnAlphaStippled () 
{
	m_Alpha=2;
	Invalidate ( FALSE );
}

void CXRayView::OnUpdateAlphaStippled ( CCmdUI* pCmdUI ) 
{
	if ( m_Alpha & 0x2 )
		pCmdUI->SetCheck ( 1 );
	else
		pCmdUI->SetCheck ( 0 );
}

void CXRayView::OnColor () 
{
	CColorDialog ColorDialog ( m_Color, 0, this );
	if ( ColorDialog.DoModal () )
	{
		m_Color=ColorDialog.GetColor ();
		Invalidate ( FALSE );
	}
}
