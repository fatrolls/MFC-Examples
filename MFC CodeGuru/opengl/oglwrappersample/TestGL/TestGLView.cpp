// TestGLView.cpp : implementation of the CTestGLView class
//

#include "stdafx.h"
#include "TestGL.h"

#include "TestGLDoc.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "GLEnabledView.h"
#include "TestGLView.h"
#include "OGLInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestGLView

IMPLEMENT_DYNCREATE(CTestGLView, CGLEnabledView)

BEGIN_MESSAGE_MAP(CTestGLView, CGLEnabledView)
	//{{AFX_MSG_MAP(CTestGLView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_HELP_OGLINFO, OnHelpOglinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGLView construction/destruction

CTestGLView::CTestGLView():
	X_Angle(0.0), Y_Angle(0.0)
{
	// TODO: add construction code here

}

CTestGLView::~CTestGLView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CTestGLView diagnostics

#ifdef _DEBUG
void CTestGLView::AssertValid() const
{
	CGLEnabledView::AssertValid();
}

void CTestGLView::Dump(CDumpContext& dc) const
{
	CGLEnabledView::Dump(dc);
}

CTestGLDoc* CTestGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestGLDoc)));
	return (CTestGLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestGLView message handlers

void CTestGLView::OnDrawGL()
{
	glPushMatrix();
		glRotated(X_Angle,1.0,0.0,0.0);
		glRotated(Y_Angle,0.0,1.0,0.0);
		DrawDispLists();
// draw carthesian axes
		glBegin(GL_LINES);
			// red x axis
			glColor3f(1.f,0.f,0.f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(0.9f,0.1f,0.0f);
			glVertex3f(1.0f,0.0f,0.0f);
			glVertex3f(0.9f,-0.1f,0.0f);
			// green y axis
			glColor3f(0.f,1.f,0.f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
			glVertex3f(0.1f,0.9f,0.0f);
			glVertex3f(0.0f,1.0f,0.0f);
			glVertex3f(-0.1f,0.9f,0.0f);
			// blue z axis
			glColor3f(0.f,0.f,1.f);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f,0.1f,0.9f);
			glVertex3f(0.0f,0.0f,1.0f);
			glVertex3f(0.0f,-0.1f,0.9f);
		glEnd();
	glPopMatrix();
}

void CTestGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
// remember where we clicked
	MouseDownPoint=point;
// capture mouse movements even outside window borders
	SetCapture();
}

void CTestGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
// forget where we clicked
	MouseDownPoint=CPoint(0,0);
// release mouse capture
	ReleaseCapture();
}

void CTestGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
// check if we are holding the left button
	if (GetCapture()==this)
	{
// increment the object rotation angles
		X_Angle+=double(point.y-MouseDownPoint.y)/3.6;
		Y_Angle+=double(point.x-MouseDownPoint.x)/3.6;
// redraw the view
		Invalidate(TRUE);
// update the actual mouse point
		MouseDownPoint=point;
	};
}

void CTestGLView::OnHelpOglinfo() 
{
	COGLInfoDlg dlg;
	int pos=0;
	dlg.m_accel=GetInformation(ACCELERATION);
	dlg.m_rend=GetInformation(RENDERER);
	dlg.m_vendor=GetInformation(VENDOR);
	dlg.m_version=GetInformation(VERSION);
	dlg.m_extensions=GetInformation(EXTENSIONS);
	while ( (pos=dlg.m_extensions.Find(" "))!=-1 )
		dlg.m_extensions.SetAt(pos,'\n');
	dlg.DoModal();	
}

void CTestGLView::OnCreateGL()
{
// perform hidden line/surface removal (enabling Z-Buffer)
	glEnable(GL_DEPTH_TEST);
// set background color to black
	glClearColor(0.f,0.f,0.f,1.0f );
// set clear Z-Buffer value
	glClearDepth(1.0f);
// prepare a RGB cube
	BeginDispList();
		glBegin(GL_QUAD_STRIP);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.3f, 0.3f, 0.3f);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-0.3f, -0.3f, 0.3f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.3f, 0.3f, 0.3f);
            glColor3f(1.0f, 1.0f, 0.0f);
            glVertex3f(0.3f, -0.3f, 0.3f);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(0.3f, 0.3f, -0.3f);
            glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.3f, -0.3f, -0.3f);
			glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.3f, 0.3f, -0.3f);
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex3f(-0.3f, -0.3f,  -0.3f);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.3f, 0.3f, 0.3f);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-0.3f, -0.3f, 0.3f);
		glEnd();
        glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(-0.3f, 0.3f, 0.3f);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.3f, 0.3f, 0.3f);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(0.3f, 0.3f, -0.3f);
			glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.3f, 0.3f, -0.3f);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-0.3f, -0.3f, 0.3f);
			glColor3f(1.0f, 1.0f, 0.0f);
            glVertex3f(0.3f, -0.3f, 0.3f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.3f, -0.3f, -0.3f);
			glColor3f(0.0f, 0.0f, 0.0f);
            glVertex3f(-0.3f, -0.3f,  -0.3f);
        glEnd();
/*		glBegin(GL_QUADS);
			glColor3f(0.3f,.5f,.8f);
			glVertex3f(0.1f,0.1f,.1f);
			glVertex3f(0.6f,.1f,.1f);
			glVertex3f(0.6f,0.6f,.1f);
			glVertex3f(0.1f,0.6f,.1f);
			glColor3f(.3f,1.f,.4f);
			glVertex3f(0.1f,0.1f,.6f);
			glVertex3f(0.6f,.1f,.6f);
			glVertex3f(0.6f,0.6f,.6f);
			glVertex3f(0.1f,0.6f,.6f);
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glColor3f(.4f,.4f,.4f);
			glVertex3f(0.1f,0.1f,.1f);
			glVertex3f(0.1f,0.1f,.6f);
			glColor3f(.6f,.5f,.4f);
			glVertex3f(0.6f,.1f,.1f);
			glVertex3f(0.6f,.1f,.6f);
			glColor3f(.7f,.6f,.8f);
			glVertex3f(0.6f,0.6f,.1f);
			glVertex3f(0.6f,0.6f,.6f);
			glColor3f(1.f,.3f,.5f);
			glVertex3f(0.1f,0.6f,.1f);
			glVertex3f(0.1f,0.6f,.6f);
			glColor3f(.4f,.4f,.4f);
			glVertex3f(0.1f,0.1f,.1f);
			glVertex3f(0.1f,0.1f,.6f);
		glEnd();
*/	EndDispList();
}
