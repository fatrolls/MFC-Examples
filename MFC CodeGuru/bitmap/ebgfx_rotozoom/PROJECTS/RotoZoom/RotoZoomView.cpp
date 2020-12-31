// RotoZoomView.cpp : implementation of the CRotoZoomView class
//

#include "stdafx.h"
#include "RotoZoom.h"

#include "RotoZoomDoc.h"
#include "RotoZoomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ANIMATIONTIMER 1
#define M_PI 3.14159265358979323846

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomView

IMPLEMENT_DYNCREATE(CRotoZoomView, CView)

BEGIN_MESSAGE_MAP(CRotoZoomView, CView)
	//{{AFX_MSG_MAP(CRotoZoomView)
	ON_COMMAND(ID_MOTIONBLUR, OnMotionBlur)
	ON_UPDATE_COMMAND_UI(ID_MOTIONBLUR, OnUpdateMotionBlur)
	ON_COMMAND(ID_DOUBLESIZE, OnDoubleSize)
	ON_UPDATE_COMMAND_UI(ID_DOUBLESIZE, OnUpdateDoubleSize)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ALPHANONE, OnAlphaNone)
	ON_UPDATE_COMMAND_UI(ID_ALPHANONE, OnUpdateAlphaNone)
	ON_COMMAND(ID_ALPHAALPHA, OnAlphaAlpha)
	ON_UPDATE_COMMAND_UI(ID_ALPHAALPHA, OnUpdateAlphaAlpha)
	ON_COMMAND(ID_ALPHASTIPPLED, OnAlphaStippled)
	ON_UPDATE_COMMAND_UI(ID_ALPHASTIPPLED, OnUpdateAlphaStippled)
	//}}AFX_MSG_MAP
	ON_MESSAGE ( MSG_ISDOUBLESIZE, IsDoubleSize )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomView construction/destruction

CRotoZoomView::CRotoZoomView ()
{
	// Create Dibs
	m_Layer0.Create ( 100, 100 );
	m_Layer1.Create ( 100, 100 );
	m_Tile.Create ( 32, 32 );
	// Fill Tables
	for ( int i=0; i<360; i++ )
	{
		Cosines[i]=float(cos ( i/180.0*M_PI ));
		Sines[i]=float(sin ( i/180.0*M_PI ));
	}
	// Initialize RotoZoom Parameters
	m_Angle=0;
	m_Zoom=1.5f;
	m_ZoomFactor=0.025f;
	m_MotionBlur=FALSE;
	m_DoubleSize=FALSE;
	m_Alpha=0;
}

CRotoZoomView::~CRotoZoomView ()
{
	// Stop Timer
	if ( m_MMTimer )
		timeKillEvent ( m_MMTimer );
	// Destroy Dibs
	m_Layer0.Destroy ();
	m_Tile.Destroy ();
	// Close DrawDib
	m_DrawDib.Close ();
}

BOOL CRotoZoomView::PreCreateWindow ( CREATESTRUCT& cs )
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomView drawing

void CRotoZoomView::OnDraw ( CDC* pDC )
{
	// Use DrawDib to Draw the Dib to Video Memory, use HalfTone for non TC Systems
	if ( m_DoubleSize )
		m_DrawDib.DrawDib ( &m_Layer0, pDC->m_hDC, 0,0, 200, 200, DDF_HALFTONE );
	else
		m_DrawDib.DrawDib ( &m_Layer0, pDC->m_hDC, 0,0, 100, 100, DDF_HALFTONE );
}

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomView diagnostics

#ifdef _DEBUG
void CRotoZoomView::AssertValid() const
{
	CView::AssertValid();
}

void CRotoZoomView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRotoZoomDoc* CRotoZoomView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRotoZoomDoc)));
	return (CRotoZoomDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomView message handlers

void CALLBACK TimeProc ( UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2 )
{
	CRotoZoomView *View;

	View=(CRotoZoomView *)dwUser;
	
	for ( int j=-50; j<50; j++ )
	{
		for ( int i=-50; i<50; i++ )
		{
			int x, y;

			// A Combination of a 2d Translation/Rotation/Scale Matrix
			x=int((i*View->Cosines[View->m_Angle]+j*View->Sines[View->m_Angle])*View->m_Zoom)+16;
			y=int((i*View->Sines[View->m_Angle]-j*View->Cosines[View->m_Angle])*View->m_Zoom)+16;
			View->m_Layer0.m_Bits[(j+50)*100+(i+50)]=View->m_Tile.m_Bits[abs(x%View->m_Tile.m_Size.cx)*View->m_Tile.m_Size.cx+abs(y%View->m_Tile.m_Size.cy)];
		}
	}
	View->m_Angle+=5;
	if ( View->m_Angle>=360 )
		View->m_Angle=0;
	View->m_Zoom+=View->m_ZoomFactor;
	if ( View->m_Zoom>=1.5 )
		View->m_ZoomFactor=-0.025f;
	else if ( View->m_Zoom<=0.0 )
		View->m_ZoomFactor=0.025f;

	// Motion Blur
	// Blends the Front Layer with 150/255 % of the Back Layer
	// Then Copies the Front Layer into the Back Layer
	// This way we get an accumulated picture in the Back Layer
	if ( View->m_MotionBlur ) 
	{
		View->m_Layer0.Blend ( &View->m_Layer1, 150 );
		View->m_Layer0.Copy ( &View->m_Layer1 );
	}

	// Alpha Layer
	if ( View->m_Alpha & 0x1 )
		View->m_Layer0.FillGlass ( 0, 255, 255, 128 );
	else if ( View->m_Alpha & 0x2 )
		View->m_Layer0.FillStippledGlass ( 0, 255, 255 );
	
	View->Invalidate ( FALSE );
}

void CRotoZoomView::OnInitialUpdate () 
{
	CView::OnInitialUpdate ();

	// Set Window Title
	CRotoZoomDoc *pDoc=GetDocument();
	ASSERT_VALID ( pDoc );
	pDoc->SetTitle ( "RotoZoom" );

	// Load a nice Image into the Tile
	CBitmap TileBitmap;
	TileBitmap.LoadBitmap ( IDB_TILE );
	m_Tile.SetBitmap ( GetDC (), &TileBitmap );

	// Open DrawDib
	m_DrawDib.Open ();

	// Start Timer
	m_MMTimer=timeSetEvent ( 40, 40, TimeProc, (unsigned long)this, TIME_PERIODIC ); 
}

BOOL CRotoZoomView::OnEraseBkgnd ( CDC* pDC ) 
{
	// Keep Windows from Painting the Background
	return TRUE;
}

HRESULT CRotoZoomView::IsDoubleSize ( WPARAM, LPARAM )
{
	return ( m_DoubleSize );
}

/////////////////////////////////////////////////////////////////////////////
// CRotoZoomView CommandUI handlers

void CRotoZoomView::OnMotionBlur () 
{
	m_MotionBlur=!m_MotionBlur;
}

void CRotoZoomView::OnUpdateMotionBlur ( CCmdUI* pCmdUI ) 
{
	if ( m_MotionBlur )
		pCmdUI->SetCheck ( 1 );
	else
		pCmdUI->SetCheck ( 0 );
}

void CRotoZoomView::OnDoubleSize () 
{
	m_DoubleSize=!m_DoubleSize;

	// Resize Window
	if ( m_DoubleSize )
	{
		CRect WindowRect ( 0, 0, 200, 200 );
		AdjustWindowRect ( &WindowRect, GetParent ()->GetStyle (), TRUE );
		GetParent ()->SetWindowPos ( NULL, 0, 0, WindowRect.Width (), WindowRect.Height (),
			SWP_NOMOVE | SWP_NOZORDER );
	}
	else
	{
		CRect WindowRect ( 0, 0, 100, 100 );
		AdjustWindowRect ( &WindowRect, GetParent ()->GetStyle (), TRUE );
		GetParent ()->SetWindowPos ( NULL, 0, 0, WindowRect.Width (), WindowRect.Height (),
			SWP_NOMOVE | SWP_NOZORDER );
	}
}

void CRotoZoomView::OnUpdateDoubleSize ( CCmdUI* pCmdUI ) 
{
	if ( m_DoubleSize )
		pCmdUI->SetCheck ( 1 );
	else
		pCmdUI->SetCheck ( 0 );
}

void CRotoZoomView::OnAlphaNone() 
{
	m_Alpha=0;
}

void CRotoZoomView::OnUpdateAlphaNone ( CCmdUI* pCmdUI ) 
{
	if ( !m_Alpha )
		pCmdUI->SetCheck ( 1 );
	else
		pCmdUI->SetCheck ( 0 );
}

void CRotoZoomView::OnAlphaAlpha() 
{
	m_Alpha=1;
}

void CRotoZoomView::OnUpdateAlphaAlpha ( CCmdUI* pCmdUI ) 
{
	if ( m_Alpha & 0x1 )
		pCmdUI->SetCheck ( 1 );
	else
		pCmdUI->SetCheck ( 0 );
}

void CRotoZoomView::OnAlphaStippled () 
{
	m_Alpha=2;
}

void CRotoZoomView::OnUpdateAlphaStippled ( CCmdUI* pCmdUI ) 
{
	if ( m_Alpha & 0x2 )
		pCmdUI->SetCheck ( 1 );
	else
		pCmdUI->SetCheck ( 0 );
}
