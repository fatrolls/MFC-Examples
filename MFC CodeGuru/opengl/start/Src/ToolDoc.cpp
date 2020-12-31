//********************************************
// ToolDoc.cpp
//********************************************
// The active document, contain a SceneGraph
//********************************************
// pierre.alliez@cnet.francetelecom.fr
// Created : 12/12/97
// Modified
//********************************************


#include "stdafx.h"
#include "math.h"
#include "Tool.h"

#include "ToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolDoc

IMPLEMENT_DYNCREATE(CToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CToolDoc, CDocument)
	//{{AFX_MSG_MAP(CToolDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolDoc construction/destruction

//********************************************
// Constructor
//********************************************
CToolDoc::CToolDoc()
{
}

//********************************************
// Destructor
//********************************************
CToolDoc::~CToolDoc()
{
}

BOOL CToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CToolDoc serialization

void CToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToolDoc diagnostics

#ifdef _DEBUG
void CToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolDoc commands


//////////////////////////////////////////////
//////////////////////////////////////////////
// RENDERING
//////////////////////////////////////////////
//////////////////////////////////////////////

//***********************************************
// RenderScene
//***********************************************
void CToolDoc::RenderScene()
{
	// Default rendering 

	glColor3ub(255,255,255);
	GLUquadricObj*	q = gluNewQuadric();
	gluQuadricDrawStyle(q, GLU_FILL);
	gluQuadricNormals(q, GLU_SMOOTH);
	gluSphere(q, 1.0, 16, 16);
	gluDeleteQuadric(q);

	/*
	float width = 1.0f;
	float step = 0.1f;

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	for(x = -width; x < width; x += step)
		{
			glBegin(GL_QUAD_STRIP); 
			for(z = -width; z < width; z += step)
			{
				float r,g,b;
				g = 0.0f;

				y = (float)sin(3*x)*cos(3*z)/3.0f;
				r = y*3.0f;
				b = 1.0f-y;
				glColor3f(r,g,b);
				glVertex3d(x,y,z);

				y = (float)sin(3*(x+step))*cos(3*z)/3.0f;
				r = y*3.0f;
				b = 1.0f-y;
				glColor3f(r,g,b);
				glVertex3d(x+step,y,z);
			}
			glEnd();
		}
		*/

}





