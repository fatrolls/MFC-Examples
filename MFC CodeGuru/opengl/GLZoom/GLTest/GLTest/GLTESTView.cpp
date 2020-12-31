// GLView.cpp : implementation of the CGLTESTView class
//

#include "stdafx.h"
#include "GLTest.h"

#include "GLTestDoc.h"
#include "GLTestView.h"
#include "mainfrm.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// add support for OpenGL 1.1 if we're using an old header
// These are new PIXELFORMATDESCRIPTOR flags for OpenGL 1.1

#ifndef PFD_GENERIC_ACCELERATED
#define PFD_GENERIC_ACCELERATED		0x00001000
#endif

#ifndef PFD_DEPTH_DONTCARE
#define PFD_DEPTH_DONTCARE			0x20000000
#endif


#define INSTALLABLE_DRIVER_TYPE_MASK  (PFD_GENERIC_ACCELERATED|PFD_GENERIC_FORMAT)


/////////////////////////////////////////////////////////////////////////////
// CGLTESTView

IMPLEMENT_DYNCREATE(CGLTESTView, CView)

BEGIN_MESSAGE_MAP(CGLTESTView, CView)
	//{{AFX_MSG_MAP(CGLTESTView)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ZOOM_WINDOW, OnZoomWindow)
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_ZOOM_PREVIOUS, OnZoomPrevious)
	ON_COMMAND(ID_PAN, OnPan)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_MOVE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_UPDATE_COMMAND_UI(ID_ZOOM_WINDOW, OnUpdateZoomWindow)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_PREVIOUS, OnUpdateZoomPrevious)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CGLTESTView construction/destruction

CGLTESTView::CGLTESTView()
{
	m_StartPoint.east = m_StartPoint.north = m_StartPoint.elev = 0.0;
	m_EndPoint.east = m_EndPoint.north = m_EndPoint.elev = 0.0;
	m_MovePoint.east = m_MovePoint.north = m_MovePoint.elev = 0.0;
	currTool == -1;
	m_FirstPickPoint = FALSE;
	xOrg = -1000;
	yOrg = -1000;
	xMax = 1000;
	yMax = 1000;
	zMax = 500;
	m_CursorPosition.x = -1;
	m_CursorPosition.y = -1;
	m_CanZoomPrev = FALSE;
}

CGLTESTView::~CGLTESTView()
{
}

BOOL CGLTESTView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGLTESTView drawing

void CGLTESTView::OnDraw(CDC* pDC)
{	
	
	HDC hdc;
	HGLRC rc;

	CGLTESTView::GetCurrent(hdc, rc);//Store current rendering and device contexts
	MakeActive();//Make view's rendering context current
	m_CursorPosition.x = -1;
	m_CursorPosition.y = -1;
	CView::OnDraw(pDC);
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	::glPushMatrix();
	RenderScene();
 	::glPopMatrix();
	// Tell OpenGL to flush its pipeline
	::glFinish();

	// Now Swap the buffers
	if ( FALSE == ::SwapBuffers(m_pDC->GetSafeHdc()))
		return;
	SetLimits();
	
	CGLTESTView::SetCurrent(hdc, rc);//Restore last rendering and device contexts
}

/////////////////////////////////////////////////////////////////////////////
// CGLTESTView printing

BOOL CGLTESTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLTESTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLTESTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGLTESTView diagnostics

#ifdef _DEBUG
void CGLTESTView::AssertValid() const
{
	CView::AssertValid();
}

void CGLTESTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLTESTDoc* CGLTESTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLTESTDoc)));
	return (CGLTESTDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLTESTView message handlers

void CGLTESTView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	SetupOrtho(cx, cy);
}


BOOL CGLTESTView::RenderScene()
{
	
	::glColor3d(0.0, 0.0, 1.0);
	::glBegin(GL_LINE_LOOP);
	{
		::glVertex3d(-500.0,-500.0,	0.0);
		::glVertex3d(-500.0,500.0,	0.0);
		::glVertex3d(500.0,500.0,	0.0);
		::glVertex3d(500.0,-500.0,	0.0);

	}
	::glEnd();

	COLOR_STRUCT color;
	color.red = 1.0f;
	color.green = 0.0f;
	color.blue = 0.0f;

	VERTEX circle_vertex;
	circle_vertex.east = 0.0;
	circle_vertex.north = 0.0;
	circle_vertex.elev = 0.0;
	CCircleEntity circle(&color, &circle_vertex, 500);
	circle.Draw();

	return TRUE;
}	

void CGLTESTView::OnLButtonDown(UINT nFlags, CPoint point) 
{

	CView::OnLButtonDown(nFlags, point);
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint viewport[4];
	GLdouble objx, objy, objz;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
	CRect rect;
	GetClientRect(&rect);
	int y = rect.Height() - point.y;
	gluUnProject(point.x, y, 0, 
					modelMatrix, projMatrix, viewport, 
					&objx, &objy, &objz); 

	if(!m_FirstPickPoint)
	{
		switch(currTool)
		{
			case ID_ZOOM_WINDOW:
			{
				m_EndPoint.east = m_StartPoint.east = objx;
				m_EndPoint.north = m_StartPoint.north = objy;
				m_EndPoint.elev = m_StartPoint.elev = objz;
				m_FirstPickPoint = TRUE;
				m_StartPosition.x = m_CursorPosition.x = point.x;
				m_StartPosition.y = m_CursorPosition.y = point.y;
				DrawZoomRect();
				break;

			}
			case ID_PAN:
			{
				m_EndPoint.east = m_StartPoint.east = objx;
				m_EndPoint.north = m_StartPoint.north = objy;
				m_EndPoint.elev = m_StartPoint.elev = objz;
				m_FirstPickPoint = TRUE;
				m_StartPosition.x = m_CursorPosition.x = point.x;
				m_StartPosition.y = m_CursorPosition.y = point.y;
				DrawRubberBand();
				break;

			}

		}
	}
	else
	{
		switch(currTool)
		{
			case ID_ZOOM_WINDOW:
			{
				m_PrevZoomLeft.east = xOrg;
				m_PrevZoomLeft.north = yOrg;
				m_PrevZoomLeft.elev = -zMax;
				m_PrevZoomRight.east = xMax;
				m_PrevZoomRight.north = yMax;
				m_PrevZoomRight.elev = zMax;
				
				m_CursorPosition.x = point.x;
				m_CursorPosition.y = point.y;
				
				DrawZoomRect();			
				m_EndPoint.east = objx;
				m_EndPoint.north = objy;
				m_EndPoint.elev = objz;
				xOrg = min(m_StartPoint.east, m_EndPoint.east);
				xMax = max(m_StartPoint.east, m_EndPoint.east);
				yOrg = min(m_StartPoint.north, m_EndPoint.north);
				yMax = max(m_StartPoint.north, m_EndPoint.north);
				currTool = -1;
				m_FirstPickPoint = FALSE;
				SetupOrtho();
				Invalidate();
				m_CanZoomPrev = TRUE;

				break;
			}
			case ID_PAN:
			{
				m_PrevZoomLeft.east = xOrg;
				m_PrevZoomLeft.north = yOrg;
				m_PrevZoomLeft.elev = -zMax;
				m_PrevZoomRight.east = xMax;
				m_PrevZoomRight.north = yMax;
				m_PrevZoomRight.elev = zMax;
				
				m_CursorPosition.x = point.x;
				m_CursorPosition.y = point.y;
				
				DrawRubberBand();			
				m_EndPoint.east = objx;
				m_EndPoint.north = objy;
				m_EndPoint.elev = objz;
				GLdouble DE = m_EndPoint.east - m_StartPoint.east;
				GLdouble DN = m_EndPoint.north - m_StartPoint.north;
				xOrg -= DE;
				xMax -= DE;
				yOrg -= DN;
				yMax -= DN;
				currTool = -1;
				m_FirstPickPoint = FALSE;
				SetupOrtho();
				Invalidate();
				m_CanZoomPrev = TRUE;

				break;
			}
			default:break;
		}
	}

		
}

void CGLTESTView::OnMouseMove(UINT nFlags, CPoint point) 
{

	CView::OnMouseMove(nFlags, point);
	
	CPoint temp(point);
	ClientToScreen(&temp);

	
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	
	if(currTool == ID_ZOOM_WINDOW)
		if(m_FirstPickPoint)
			DrawZoomRect();

	if(currTool == ID_PAN)
		if(m_FirstPickPoint)
			DrawRubberBand();


	m_CursorPosition.x = point.x;
	m_CursorPosition.y = point.y;
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint viewport[4];
	GLdouble objx, objy, objz;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	CRect rect;
	GetClientRect(&rect);
	point.y = rect.Height() - point.y;
	gluUnProject(point.x, point.y, 0, 
					modelMatrix, projMatrix, viewport, 
					&objx, &objy, &objz);
	
	m_EndPoint.east = m_MovePoint.east = objx;
	m_EndPoint.north = m_MovePoint.north = objy;
	m_EndPoint.elev = m_MovePoint.elev = objz;
	
	if(currTool == ID_ZOOM_WINDOW)
		if(m_FirstPickPoint)
			DrawZoomRect();

	if(currTool == ID_PAN)
		if(m_FirstPickPoint)
			DrawRubberBand();
	
}

void CGLTESTView::OnZoomWindow() 
{
	currTool = ID_ZOOM_WINDOW;
	m_FirstPickPoint = FALSE;
	
}


void CGLTESTView::SetupOrtho(int cx, int cy)
{
	
	if ( 0 >= cx || 0 >= cy )
		return;
	GLdouble dx = xMax - xOrg;
	GLdouble dy = yMax - yOrg;
	
	SetupViewport( cx, cy );

	// OK, now save the dimensions of the window, cutting the width in half
	m_width = cx;
	m_height = cy;

	// Now that the dimensions are set up, we can set up the projection
	// matrix. Since we've overridden OnSize(), we need to do it ourselves

	// select the viewing volumn
    ::glMatrixMode ( GL_PROJECTION );
    ::glLoadIdentity ();

	if(fabs(dx) > 0.001 || fabs(dy) > 0.001)
	{		
		if(dx > dy)
		{
			GLdouble dY = dx * m_height / m_width;
			GLdouble yMax = yOrg  + dY;
			::glOrtho( xOrg, xMax, yOrg, yMax, -zMax, zMax);
		}
		else
		{
			GLdouble dX = dy * m_width / m_height;
			GLdouble xMax = xOrg + dX;
			::glOrtho( xOrg, xMax, yOrg, yMax, -zMax, zMax);
		}
	}
	// switch back to the modelview matrix and clear it
	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();

}

void CGLTESTView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
}

void CGLTESTView::SetupOrtho()
{
	
	// Now that the dimensions are set up, we can set up the projection
	// matrix. Since we've overridden OnSize(), we need to do it ourselves
	CRect rect;
	GetClientRect(&rect);

	// OK, now save the dimensions of the window, cutting the width in half
	m_width = rect.Width();
	m_height = rect.Height();

	SetupOrtho(rect.Width(), rect.Height());
}




BOOL CGLTESTView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	return CView::OnSetCursor(pWnd, nHitTest, message);
}


BOOL CGLTESTView::OnEraseBkgnd(CDC* pDC) 
{
	
	return TRUE; // tell Windows not to erase the background
}

void CGLTESTView::OnZoomOut() 
{
	m_PrevZoomLeft.east = xOrg;
	m_PrevZoomLeft.north = yOrg;
	m_PrevZoomLeft.elev = -zMax;
	m_PrevZoomRight.east = xMax;
	m_PrevZoomRight.north = yMax;
	m_PrevZoomRight.elev = zMax;
	m_CanZoomPrev = TRUE;
	
	GLdouble width = xMax - xOrg;
	GLdouble height = yMax - yOrg;
	xOrg = xOrg - width/2;
	xMax = xMax + width/2;
	yOrg = yOrg - width/2;
	yMax = yMax + width/2;
	SetupOrtho();
	Invalidate();
}

void CGLTESTView::OnZoomIn() 
{
	m_PrevZoomLeft.east = xOrg;
	m_PrevZoomLeft.north = yOrg;
	m_PrevZoomLeft.elev = -zMax;
	m_PrevZoomRight.east = xMax;
	m_PrevZoomRight.north = yMax;
	m_PrevZoomRight.elev = zMax;
	m_CanZoomPrev = TRUE;

	GLdouble width = xMax - xOrg;
	GLdouble height = yMax - yOrg;
	xOrg = xOrg + width/4;
	xMax = xMax - width/4;
	yOrg = yOrg + width/4;
	yMax = yMax - width/4;
	SetupOrtho();
	Invalidate();
}

void CGLTESTView::OnZoomPrevious() 
{	
	VERTEX temp1, temp2;
	temp1.east = xOrg;
	temp1.north = yOrg;
	temp1.elev = -zMax;
	temp2.east = xMax;
	temp2.north = yMax;
	temp2.elev = zMax;

	xOrg = m_PrevZoomLeft.east;
	yOrg = m_PrevZoomLeft.north;
	xMax = m_PrevZoomRight.east;
	yMax = m_PrevZoomRight.north;
	zMax = m_PrevZoomRight.elev;
	SetupOrtho();
	Invalidate();
	memcpy(&m_PrevZoomLeft, &temp1, sizeof(VERTEX));
	memcpy(&m_PrevZoomRight, &temp2, sizeof(VERTEX));
}

void CGLTESTView::DrawZoomRect()
{
/*	HDC hdc = wglGetCurrentDC(); 
	CDC* dc = CDC::FromHandle(hdc);
	CPen pen(PS_DOT, 0, RGB(0, 0, 0));
	CPen* oldPen = dc->SelectObject(&pen);
	HBRUSH hbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	CBrush* brush = CBrush::FromHandle(hbrush);
	CBrush* oldBrush = dc->SelectObject(brush);

	dc->SetROP2(R2_XORPEN);
	CRect rect(m_StartPosition.x, m_StartPosition.y,
			m_CursorPosition.x, m_CursorPosition.y);
	dc->DPtoLP(&rect);
	dc->Rectangle(&rect);
	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);
*/
	GLushort pattern;
	GLint repeat;
	::glEnable(GL_LINE_STIPPLE);	
	::glGetIntegerv(GL_LINE_STIPPLE_PATTERN, (GLint*)&pattern);
	::glGetIntegerv(GL_LINE_STIPPLE_REPEAT, &repeat);
	GLushort line_stipple = 4351;
	::glLineStipple(3, line_stipple);
	
	::glDrawBuffer(GL_FRONT);
	GLboolean depthtest = ::glIsEnabled(GL_DEPTH_TEST);
	::glDisable(GL_DEPTH_TEST);
	GLenum depthfunc, logicop;
	::glGetIntegerv(GL_DEPTH_FUNC,(GLint*) &depthfunc);
	::glDepthFunc(GL_LEQUAL);

	::glEnable(GL_COLOR_LOGIC_OP);
	::glGetIntegerv(GL_LOGIC_OP_MODE,(GLint*) &logicop);
	::glLogicOp(GL_XOR);
	::glColor3d(1.0,1.0,0.0);
	::glBegin(GL_LINE_LOOP);
	::glVertex2d(m_StartPoint.east, m_StartPoint.north);
	::glVertex2d(m_EndPoint.east, m_StartPoint.north);
	::glVertex2d(m_EndPoint.east, m_EndPoint.north);
	::glVertex2d(m_StartPoint.east, m_EndPoint.north);
	::glEnd();
	::glDrawBuffer(GL_BACK);
	if(depthtest)
		::glEnable(GL_DEPTH_TEST);
	::glDepthFunc(depthfunc);
	::glLogicOp(logicop);
	::glLineStipple(repeat, pattern);
}

void CGLTESTView::DrawRubberBand()
{
/*	HDC hdc = wglGetCurrentDC(); 
	CDC* dc = CDC::FromHandle(hdc);
	CPen pen(PS_DOT, 0, RGB(0, 0, 0));
	CPen* oldPen = dc->SelectObject(&pen);
	HBRUSH hbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	CBrush* brush = CBrush::FromHandle(hbrush);
	CBrush* oldBrush = dc->SelectObject(brush);
	CPoint point1(m_StartPosition);	
	CPoint point2(m_CursorPosition);
	dc->DPtoLP(&point1);
	dc->DPtoLP(&point2);
	dc->SetROP2(R2_XORPEN);
	dc->MoveTo(point1);
	dc->LineTo(point2);
	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);
*/
	GLushort pattern;
	GLint repeat;
	::glEnable(GL_LINE_STIPPLE);	
	::glGetIntegerv(GL_LINE_STIPPLE_PATTERN, (GLint*)&pattern);
	::glGetIntegerv(GL_LINE_STIPPLE_REPEAT, &repeat);
	::glLineStipple(1, 128);

	::glDrawBuffer(GL_FRONT);
	GLboolean depthtest = ::glIsEnabled(GL_DEPTH_TEST);
	::glDisable(GL_DEPTH_TEST);
	GLenum depthfunc, logicop;
	::glGetIntegerv(GL_DEPTH_FUNC,(GLint*) &depthfunc);
	::glDepthFunc(GL_LEQUAL);

	::glEnable(GL_COLOR_LOGIC_OP);
	::glGetIntegerv(GL_LOGIC_OP_MODE,(GLint*) &logicop);
	::glLogicOp(GL_XOR);
	::glColor3d(1.0,1.0,0.0);
	::glBegin(GL_LINE_STRIP);
	::glVertex2d(m_StartPoint.east, m_StartPoint.north);
	::glVertex2d(m_EndPoint.east, m_EndPoint.north);
	::glEnd();
	::glDrawBuffer(GL_BACK);
	if(depthtest)
		::glEnable(GL_DEPTH_TEST);
	::glDepthFunc(depthfunc);
	::glLogicOp(logicop);
	::glLineStipple(repeat, pattern);

}


BOOL CGLTESTView::PreTranslateMessage(MSG* pMsg) 
{
	
	return CView::PreTranslateMessage(pMsg);
}

void CGLTESTView::OnPan() 
{
	currTool = ID_PAN;
	m_FirstPickPoint = FALSE;
}


int CGLTESTView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	GetParentFrame()->GetWindowText( m_WindowTitle );

	// get rid of that " - Untitled" stuff
	GetParentFrame()->ModifyStyle(FWS_ADDTOTITLE,0);

	InitializeOpenGL();
	
	return 0;
}

void CGLTESTView::OnDestroy() 
{
    CView::OnDestroy();
	if ( FALSE == ::wglDeleteContext( m_hRC ) )
		return;
//	For Color-Index mode, you should reset the palette to the original here

    if ( m_pDC )
	{
        delete m_pDC;
	}
	
}

//////////////////////////////////////////////////////////////////////////////
// InitializeOpenGL
// - just that. This is set up for RGB mode, though I've indicated
// where you would add code for color-index mode.
BOOL CGLTESTView::InitializeOpenGL()
{
	// Can we put this in the constructor?
    m_pDC = new CClientDC(this);

    if ( NULL == m_pDC ) // failure to get DC
		return FALSE;

	if (!SetupPixelFormat())
		{
        return FALSE;
		}

//	For Color-Index mode, you'd probably create your palette here, right
//	after you select the pixel format

    if ( 0 == (m_hRC = ::wglCreateContext( m_pDC->GetSafeHdc() ) ) )
		return FALSE;

    if ( FALSE == MakeActive())
		return FALSE;

	// specify black as clear color
    ::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// specify the back of the buffer as clear depth
    ::glClearDepth(1.0f);
	// enable depth testing
    ::glEnable(GL_DEPTH_TEST);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CGLTESTView::SetupPixelFormat()
{
  static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
          PFD_SUPPORT_OPENGL |			// support OpenGL          
          PFD_DOUBLEBUFFER,				// double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        32,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    
    if ( 0 == (m_PixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) )
        return FALSE;

    if ( FALSE == ::SetPixelFormat(m_pDC->GetSafeHdc(), m_PixelFormat, &pfd) )
        return FALSE;

    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// SetupViewport
BOOL CGLTESTView::SetupViewport( int cx, int cy )
{
	// select the full client area
    ::glViewport(0, 0, cx, cy);

	return TRUE;
}


void CGLTESTView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	if(nChar == VK_ESCAPE)
	{
		if(currTool != -1)
		{
			switch(currTool)
			{
				case ID_ZOOM_WINDOW:DrawZoomRect();
									break;
				case ID_PAN:		DrawRubberBand();
									break;
			}
			currTool = -1;
			m_FirstPickPoint = FALSE;
		}
	}

}

void CGLTESTView::SetLimits()
{
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	GLint viewport[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
		
	
	CRect rect;
	GetClientRect(&rect);
	gluUnProject(0, 0, 0, 
					modelMatrix, projMatrix, viewport, 
					&xOrg, &yOrg, &zMax);	
	gluUnProject(rect.Width(), rect.Height(), 0, 
					modelMatrix, projMatrix, viewport, 
					&xMax, &yMax, &zMax);
	gluUnProject(1, 1, 0, 
					modelMatrix, projMatrix, viewport, 
					&m_PixelX, &m_PixelY, &zMax);
	m_PixelX -= xOrg;
	m_PixelY -= yOrg;
}

void CGLTESTView::OnMove(int x, int y) 
{
	CView::OnMove(x, y);
}

void CGLTESTView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
  
	MakeActive();
}

BOOL CGLTESTView::MakeActive()
{
	return SetCurrent(m_pDC->GetSafeHdc(), m_hRC);
}


void CGLTESTView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);

}

void CGLTESTView::GetCurrent(HDC& hdc, HGLRC& rc) 
{
	hdc = ::wglGetCurrentDC();
	rc =  ::wglGetCurrentContext(); 
} 

BOOL CGLTESTView::SetCurrent(HDC hdc, HGLRC rc) 
{
	if (FALSE == ::wglMakeCurrent(hdc, rc))
		return FALSE;
	return TRUE;
} 

void CGLTESTView::OnUpdateZoomWindow(CCmdUI* pCmdUI) 
{
	GLdouble dx = xMax - xOrg;
	GLdouble dy = yMax - yOrg;
	pCmdUI->Enable(fabs(dx) > 0.001 || fabs(dy) > 0.001);
	
}

void CGLTESTView::OnUpdateZoomPrevious(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_CanZoomPrev);
}
