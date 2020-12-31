///////////////////////////////////////////////////////////
//
//
// MainFrm.cpp : implementation of the CMainFrame class
//
//
///////////////////////////////////////////////////////////
//
// Includes
//
#include "stdafx.h"
#include "objbase.h"
#include <oleauto.h>
#include <stdlib.h> //for rand()
#include <time.h>

// Interface definitions.
#include "Visual_I.h"
#include "World_I.h"
#include "Model_I.h" 
#include "Model_C.h"
#include "Canvas_I.h" //For OnPaint.

// Others 
#include "util.h"
#include "resource.h"
#include "ConfigDlg.h"
#include "MainFrm.h"
#include "Tangram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////
//
// Statics
//
CString CMainFrame::s_strClassName = "" ;

/////////////////////////////////////////////////////////////////////////////
//
// CMainFrame Message Map
//


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////
//
// Constructor
//
CMainFrame::CMainFrame()
:	m_pWorld(NULL),
	m_pSelectedVisual(NULL)
{
	m_sizedDiff.cx = 0.0 ;
	m_sizedDiff.cy = 0.0 ;
}

///////////////////////////////////////////////////////////
//
// Destructor
//
CMainFrame::~CMainFrame()
{
	if (m_pWorld != NULL)
	{
		m_pWorld->Release() ;
	}

	POSITION pos = m_ModelList.GetHeadPosition();
	while( pos != NULL )
	{
		ITangramModel* pITangramModel = m_ModelList.GetNext( pos ) ;
		pITangramModel->Release();
	}
	m_ModelList.RemoveAll();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFrameWnd::PreCreateWindow(cs);
}

///////////////////////////////////////////////////////////
//
// Create - Helper function for creating  the window class
//				and window.
//
BOOL CMainFrame::Create()
{
	if (s_strClassName.IsEmpty())
	{
		s_strClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
											AfxGetApp()->LoadStandardCursor(IDC_ARROW),
											0,
											AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	}

	// Set screen size.
	CClientDC dc(NULL) ;
	int cx = 640 ;
	int cy = 480 ;

	return CWnd::CreateEx(	0, s_strClassName, AfxGetAppName(), 
							WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|
							WS_BORDER|WS_MINIMIZEBOX|WS_VISIBLE,
							0,0, cx, cy, 
							NULL, NULL);
}

///////////////////////////////////////////////////////////
//
// OnCreate
//
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		TRACE0("Could not create main window.\r\n") ;
		return -1;
	}
	
	// Initialize
	CRect aRect ;
	GetClientRect(&aRect) ;
	if (!Initialize(aRect.Width(), aRect.Height()))
	{
		TRACE0("Cannot initialize main window.\r\n") ;
		return -1 ;
	}

	return 0;
}

///////////////////////////////////////////////////////////
//
// Initialize
//
BOOL CMainFrame::Initialize(int cx, int cy)
{
	ASSERT( (cx != 0) && (cy != 0)) ;

	// Which components are in the IWorldComponent Category.
	CConfigDlg dlg;
	if (dlg.DoModal() != IDOK)
	{
		TRACE0("User canceled the dialog box. Fail initialization.\r\n") ;
		return FALSE ;
	}

	// Did the user want to use local or inproc?
	DWORD clsctx = (dlg.m_bLocalModel) ? CLSCTX_LOCAL_SERVER : CLSCTX_INPROC_SERVER ;

	// Create the desired world selected component.
	HRESULT hr = ::CoCreateInstance(	dlg.m_clsid, 
										NULL, 
										CLSCTX_INPROC_SERVER, 
										IID_ITangramWorld, 
										(void**)&m_pWorld) ;
	if (FAILED(hr))
	{
		ErrorMessage("Failed to create the world component.", hr) ;
		return FALSE ;
	}

	// Initialize the world.
	hr = m_pWorld->Initialize(m_hWnd, 20.0, 20.0) ;
	if (FAILED(hr))
	{
		ErrorMessage("Cannot initialize World.\r\n", hr) ;
		m_pWorld->Release() ;
		m_pWorld = NULL ;
		return FALSE ;
	}

	// Create and initialize the tangrams pieces.
	struct PolygonInit{
		int iSides ;
		TangramPoint2d points[4] ;
	};

	PolygonInit polygons[7] = {
		// Sides   Vertex 0     1            2            3
		{ 4,  {{0.0, 0.0 }, {1.0, 0.0 }, {1.0, 1.0 }, {0.0, 1.0 }} }, // Square 
		{ 3,  {{0.0, 0.0 }, {1.0, 0.0 }, {0.0, 1.0 }, {9.9, 9.9 }} }, // Small Triangle
		{ 3,  {{0.0, 0.0 }, {1.0, 0.0 }, {0.0, 1.0 }, {9.9, 9.9 }} }, // Small Triangle
		{ 3,  {{0.0, 0.0 }, {2.0, 0.0 }, {1.0, 1.0 }, {9.9, 9.9 }} }, // Medium Triangle
		{ 3,  {{0.0, 0.0 }, {2.0, 0.0 }, {0.0, 2.0 }, {9.9, 9.9 }} }, // Big Triangle
		{ 3,  {{0.0, 0.0 }, {2.0, 0.0 }, {0.0, 2.0 }, {9.9, 9.9 }} }, // Big Triangle
		{ 4,  {{0.0, 0.0 }, {1.0, 0.0 }, {2.0, 1.0 }, {1.0, 1.0 }} }, // Paralelagram
	};

	double x = 0.0 ;
	ITangramModel* pITangramModel = NULL ;
	for (int i = 0 ; i < 7 ; i ++)
	{
		hr = ::CoCreateInstance(CLSID_TangramModel,
								NULL,
								clsctx , 
								IID_ITangramModel, 
								(void**)&pITangramModel) ;
		if (FAILED(hr))
		{
			ErrorMessage("Failed to create Tangram piece.", hr) ;
			return FALSE ;
		}

		// Set the vertices for this model.
		hr = pITangramModel->SetVertices(polygons[i].iSides, polygons[i].points) ;
		ASSERT_HRESULT(hr) ;

		// Add the interface to the array. 
		m_ModelList.AddTail(pITangramModel) ;

		hr = m_pWorld->CreateVisualForModel(pITangramModel) ;
		ASSERT_HRESULT(hr) ;

		// Get the ITangramTransform interface.
		ITangramTransform* pITangramTransform = NULL ;
		HRESULT hr = pITangramModel->QueryInterface(IID_ITangramTransform, (void**)&pITangramTransform ) ;
		ASSERT_HRESULT(hr) ;
		
		// Place the tangram piece.
		pITangramTransform->Translate(x, 1.0) ;
		x += 2.0  ;

		// We are done with ITangramTransform.
		pITangramTransform->Release() ;

		// OPTIMIZED: We didn't AddRef the interface before putting it into the
		// list. So, do not Release it here. This saves us an AddRef/Release Pairs
		//pITangramModel->Release() ;
	}

	return TRUE ;
}

///////////////////////////////////////////////////////////
//
// PostNcDestroy
//
void CMainFrame::PostNcDestroy() 
{
	delete this ;
}

///////////////////////////////////////////////////////////
//
// OnPaint
//
void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); 

	// Get ICanvas interface pointer.
	ITangramCanvas* pCanvas = NULL ;
	HRESULT hr = m_pWorld->QueryInterface(IID_ITangramCanvas, (void**)&pCanvas) ;
	ASSERT_HRESULT(hr) ;

	// Use it.
	hr = pCanvas->Paint(dc.m_hDC, dc.m_ps.rcPaint) ;
	ASSERT_HRESULT(hr) ;

	// Lose it.
	pCanvas->Release() ;
}

///////////////////////////////////////////////////////////
//
// Handle both left and right button down messages.
//
void CMainFrame::DoButtonDown(UINT nWhichButton, CPoint point) 
{	
	if (m_pSelectedVisual != NULL)
	{
		// User may have pressed right button then left button.
		TRACE0("OnLButtonDown: Visual already selected.\r\n") ;
		return ;
	}

	HRESULT hr = m_pWorld->VisualFromPoint(point, IID_ITangramVisual, (IUnknown**)&m_pSelectedVisual) ; //@
	ASSERT(SUCCEEDED(hr)) ;
	if (hr == S_OK)
	{
		ASSERT(m_pSelectedVisual != NULL) ;
		//
		// Get mouse pointer offset from model's origin.
		//

		// Convert to Model Coordinates.
		TangramPoint2d ptModel ;
		hr = m_pWorld->DeviceToModel(point, &ptModel);
		ASSERT_HRESULT(hr) ;

		// Get the Model's ITrangramTransform interface.
		ITangramTransform* pITangramTransform = NULL ;
		hr = m_pSelectedVisual->GetModel(IID_ITangramTransform, (IUnknown**)&pITangramTransform) ;
		ASSERT_HRESULT(hr) ;

		// Where does the model reside.
		TangramPoint2d ptOrigin ;
		hr = pITangramTransform->GetTranslation(&ptOrigin) ;
		ASSERT_HRESULT(hr) ;
	
		// Release ITangramTransfrom.
		pITangramTransform->Release() ;
		pITangramTransform = NULL ;

		// Get difference between where the mouse clicked and the origin of the piece.
		m_sizedDiff.cx = ptModel.x - ptOrigin.x ; 
		m_sizedDiff.cy = ptModel.y - ptOrigin.y ; 

		// Select the visual.
		hr = m_pWorld->SelectVisual(m_pSelectedVisual, TRUE) ;
		ASSERT_HRESULT(hr) ;

		// Update the display
		hr = m_pWorld->Animate() ;
		ASSERT_HRESULT(hr) ;

		// Capture the mouse.
		SetCapture() ;
		}
	else
	{
		TRACE0("DoButtonDown: PtInVisual returned Null.\r\n") ;
	}
}

/*
void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CMainFrame::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnRButtonDown(nFlags, point);
}

void CMainFrame::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnRButtonUp(nFlags, point);
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CFrameWnd::OnPaletteChanged(pFocusWnd);
	
	// TODO: Add your message handler code here
	
}

BOOL CMainFrame::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
	
	return CFrameWnd::OnQueryNewPalette();
}
*/

///////////////////////////////////////////////////////////
//
// OnLButtonDown Message Handler
//
void CMainFrame::OnLButtonDown(UINT nWhichButton, CPoint point) 
{	
	DoButtonDown(nWhichButton, point) ;
}

///////////////////////////////////////////////////////////
//
// OnLButtonUp Message Handler
//
void CMainFrame::OnLButtonUp(UINT nWhichButton, CPoint point) 
{
	if (::GetCapture() != m_hWnd)
	{
		return ;
	}

	if (m_pSelectedVisual != NULL)
	{
		// De-select the currently selected model.
		HRESULT hr = m_pWorld->SelectVisual(m_pSelectedVisual, FALSE) ; 
		ASSERT_HRESULT(hr) ;

		// Cleanup
		m_pSelectedVisual->Release() ;
		m_pSelectedVisual = NULL ;
	}

	// We don't need the mouse capture any more.
	::ReleaseCapture() ;
}

///////////////////////////////////////////////////////////
//
// OnMouseMove Message Handler
//
void CMainFrame::OnMouseMove(UINT nWhichButton, CPoint point) 
{
	if ((::GetCapture() != m_hWnd) ||
		(nWhichButton & (MK_SHIFT | MK_CONTROL))) 
	{
		// Return if another window has captured the mouse or
		// if the SHIFT or CTRL key is pressed, signaling rotation.
		return ;
	}

	// Make sure that mouse is not outside of our client area.
	CRect rectClient ;
	GetClientRect(&rectClient) ;
	if (!rectClient.PtInRect(point))
	{
		return ;
	}

	ASSERT(m_pSelectedVisual != NULL) ;

	// Convert to Model Coordinates.
	TangramPoint2d ptModel ;
	HRESULT hr = m_pWorld->DeviceToModel(point, &ptModel);
	ASSERT_HRESULT(hr) ;

	//Get the Model's ITangramTransfrom interface.
	ITangramTransform* pITangramTransform = NULL ;
	hr = m_pSelectedVisual->GetModel(IID_ITangramTransform, (IUnknown**)&pITangramTransform) ;
	ASSERT_HRESULT(hr) ;

	// Move the model.
	hr = pITangramTransform->Translate(ptModel.x - m_sizedDiff.cx, ptModel.y - m_sizedDiff.cy);
	ASSERT_HRESULT(hr) ;

	// Release the interface.
	pITangramTransform->Release() ;
}

///////////////////////////////////////////////////////////
//
// Rotate using the right mouse button.
//
void CMainFrame::OnRButtonDown(UINT nWhichButton, CPoint point) 
{
	DoButtonDown(nWhichButton, point) ;
}

///////////////////////////////////////////////////////////
//
// Rotate the model. Shift key determines direction.
//
void CMainFrame::OnRButtonUp(UINT nWhichButton, CPoint point) 
{
	if (::GetCapture() != m_hWnd)
	{
		return ;
	}

	if (m_pSelectedVisual != NULL)
	{
		//----- Rotate the shape. -----

		// Check to see of the mouse pointer is still over the same visual.
		ITangramVisual* pSameVisual = NULL ;
		HRESULT hr = m_pWorld->VisualFromPoint(point, IID_ITangramVisual, (IUnknown**)&pSameVisual) ;			
		ASSERT_HRESULT(hr) ;
		ASSERT(pSameVisual != NULL) ;

		if (::InterfacesAreOnSameComponent(m_pSelectedVisual, pSameVisual))
		{
			//Get the Model's ITangramTransform interface.
			ITangramTransform* pITangramTransform = NULL ;
			hr = m_pSelectedVisual->GetModel(IID_ITangramTransform, (IUnknown**)&pITangramTransform);
			ASSERT_HRESULT(hr) ;
			
			// Rotate the model.
			int iRotationDirection = (nWhichButton & MK_SHIFT) ? -1 : 1 ; 
			double dDegrees  ;
			pITangramTransform->GetRotation(&dDegrees) ;
			pITangramTransform->Rotate(dDegrees + 45.0*iRotationDirection);

			// Release ITangramTransform
			pITangramTransform->Release() ;
			pITangramTransform = NULL ;
		}
		
		// Cleanup
		pSameVisual->Release() ;
		pSameVisual = NULL ;

		// De-select the currently selected model.
		hr = m_pWorld->SelectVisual(m_pSelectedVisual, FALSE) ; 
		ASSERT_HRESULT(hr) ;

		// Cleanup
		m_pSelectedVisual->Release() ;
		m_pSelectedVisual = NULL ;
	}

	// We don't need the mouse capture any more.
	::ReleaseCapture() ;
}

///////////////////////////////////////////////////////////
//
// OnPaletteChanged Message Handler
//
void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if (pFocusWnd != this)
	{
		OnQueryNewPalette() ;
	}
}

///////////////////////////////////////////////////////////
//
// QueryNewPalette Message Handler
//
BOOL CMainFrame::OnQueryNewPalette() 
{
	if (m_hWnd == NULL)
	{
		return FALSE ;
	}

	// Get ICanvas interface pointer.
	ITangramCanvas* pCanvas = NULL ;
	HRESULT hr = m_pWorld->QueryInterface(IID_ITangramCanvas, (void**)&pCanvas) ;
	if (SUCCEEDED(hr))
	{
		// Use it.
		hr = pCanvas->OnQueryNewPalette(m_hWnd);

		// Lose it.
		pCanvas->Release() ;
	}
	return SUCCEEDED(hr); 
}

