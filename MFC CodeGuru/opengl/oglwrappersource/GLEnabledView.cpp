/*****************************************************
Copyright Notice

Copyright © Alessandro Falappa

Permission to use, copy, modify, and distribute this software
and its documentation for any purpose is hereby granted without
fee, provided that the above copyright notice, author statement
appear in all copies of this software and related documentation.

THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF
ANY KIND, EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT
LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR FITNESS FOR A
PARTICULAR PURPOSE.

IN NO EVENT SHALL ALESSANDRO FALAPPA BE LIABLE FOR ANY
SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
KIND, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE,
AND ON ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

///////////////////////////////////////////////
History

v 1.0: first version

******************************************************/
// CGLEnabledView.cpp : implementation file version 1.0
//

#include "stdafx.h"
/*******************
 NOTE:
 - These includes below can be moved to stdafx.h to speed up compilation
 - Remember to include the appropriate libraries in the link phase
   (look at Project Settings under the Link tab)
********************/
// MS openGL libraries (link with OPENGL32.LIB and GLU32.LIB)
#include "gl\gl.h"
#include "gl\glu.h"
/* SGI openGL libraries (link with OPENGL.LIB and GLU.LIB)
#include "[path-of-SGI-sdk]\include\gl\gl.h"
#include "[path-of-SGI-sdk]\include\gl\glu.h"
//*/
//#include "afxtempl.h"
#include "GLEnabledView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_LISTS 20
// used to identify a MCD video driver (partial OGL acceleration)
#define INSTALLABLE_DRIVER_TYPE_MASK  (PFD_GENERIC_ACCELERATED|PFD_GENERIC_FORMAT)

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView

IMPLEMENT_DYNCREATE(CGLEnabledView, CView)

CGLEnabledView::CGLEnabledView():
	m_dAspectRatio(1.0), /*m_tesselator(NULL),// this is for future versions*/
	m_InsideDispList(FALSE), m_ExternDispListCall(FALSE)
{
// define a default cursor
	m_hMouseCursor=AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);
// set the disp list vector to all zeros
	for (int c=0;c<MAX_LISTS;c++) m_DispListVector[c]=0;
}

CGLEnabledView::~CGLEnabledView()
{
}


BEGIN_MESSAGE_MAP(CGLEnabledView, CView)
	//{{AFX_MSG_MAP(CGLEnabledView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView drawing

void CGLEnabledView::OnDraw(CDC* pDC)
{
// prepare a semaphore
	static BOOL 	bBusy = FALSE;
// use the semaphore to enter this critic section
	if(bBusy) return;
	bBusy = TRUE;

// specify the target DeviceContext of the subsequent OGL calls
	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// call the virtual drawing procedure (to be overridden by user)
	OnDrawGL();

// execute OGL commands (flush the OGL graphical pipeline)
	glFinish();

// if double buffering is used it's time to swap the buffers
	SwapBuffers(m_pCDC->GetSafeHdc());
	
// turn the semaphore "green"
	bBusy = FALSE;

// free the target DeviceContext (window)
    wglMakeCurrent(NULL,NULL);
}

void CGLEnabledView::OnDrawGL()
{
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
}

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView diagnostics

#ifdef _DEBUG
void CGLEnabledView::AssertValid() const
{
	CView::AssertValid();
}

void CGLEnabledView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
	CString str;
	GetWindowText(str);
	afxDump<<"\nView Parameters\n\tClient Rectangle :"<<m_ClientRect<<"\n\tAspect Ratio :"<<m_dAspectRatio<<"\n";
	afxDump<<"\nWindowTitle :"<<str<<"\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////
// CGLEnabledView Constants

// these are used to construct an equilibrated 256 color palette
unsigned char _threeto8[8] = 
{
	0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};

unsigned char _twoto8[4] = 
{
	0, 0x55, 0xaa, 0xff
};

unsigned char _oneto8[2] = 
{
	0, 255
};

static int defaultOverride[13] = 
{
	0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

// Windows Default Palette
static PALETTEENTRY defaultPalEntry[20] = 
{
	{ 0,   0,   0,    0 },
	{ 0x80,0,   0,    0 },
	{ 0,   0x80,0,    0 },
	{ 0x80,0x80,0,    0 },
	{ 0,   0,   0x80, 0 },
	{ 0x80,0,   0x80, 0 },
	{ 0,   0x80,0x80, 0 },
	{ 0xC0,0xC0,0xC0, 0 },

	{ 192, 220, 192,  0 },
	{ 166, 202, 240,  0 },
	{ 255, 251, 240,  0 },
	{ 160, 160, 164,  0 },

	{ 0x80,0x80,0x80, 0 },
	{ 0xFF,0,   0,    0 },
	{ 0,   0xFF,0,    0 },
	{ 0xFF,0xFF,0,    0 },
	{ 0,   0,   0xFF, 0 },
	{ 0xFF,0,   0xFF, 0 },
	{ 0,   0xFF,0xFF, 0 },
	{ 0xFF,0xFF,0xFF, 0 }
};

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView initialization and palette handlers

BOOL CGLEnabledView::bSetupPixelFormat()
{
// define default desired video mode (pixel format)
	static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
        1,								// version number
        PFD_DRAW_TO_WINDOW |			// support window
        PFD_SUPPORT_OPENGL |			// support OpenGL
        PFD_DOUBLEBUFFER,				// double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        16,                             // 32-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
// let the user change some parameters
	BOOL bDoublBuf;
	ColorsNumber cnum;
	ZAccuracy zdepth;
	VideoMode(cnum,zdepth,bDoublBuf);
//set the changes
	if(bDoublBuf) pfd.dwFlags=PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |PFD_DOUBLEBUFFER;
	else pfd.dwFlags=PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	switch(cnum)
	{
	case INDEXED: pfd.cColorBits=8;
	case THOUSANDS: pfd.cColorBits=16;
	case MILLIONS: pfd.cColorBits=24;
	case MILLIONS_WITH_TRANSPARENCY: pfd.cColorBits=32;
	};
	switch(zdepth)
	{
	case NORMAL: pfd.cDepthBits=16;
	case ACCURATE: pfd.cDepthBits=32;
	};

// ask the system for such video mode
    ASSERT(m_pCDC != NULL);
    int pixelformat;
	if ( (pixelformat = ChoosePixelFormat(m_pCDC->GetSafeHdc(), &pfd)) == 0 )
    {
        AfxMessageBox("ChoosePixelFormat failed");
        return FALSE;
    }

// try to set this video mode    
	if (SetPixelFormat(m_pCDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
// the requested video mode is not available so get a default one
        pixelformat = 1;	
		if (DescribePixelFormat(m_pCDC->GetSafeHdc(), pixelformat, sizeof(PIXELFORMATDESCRIPTOR), &pfd)==0)
		{
// neither the requested nor the default are available: fail
			AfxMessageBox("SetPixelFormat failed (no OpenGL compatible video mode)");
			return FALSE;
		}
    }

    return TRUE;
}

void CGLEnabledView::CreateRGBPalette()
{
    PIXELFORMATDESCRIPTOR pfd;
    LOGPALETTE *pPal;
    int n, i;

// get the initially choosen video mode
	n = ::GetPixelFormat(m_pCDC->GetSafeHdc());
    ::DescribePixelFormat(m_pCDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

// if is an indexed one...
    if (pfd.dwFlags & PFD_NEED_PALETTE)
    {
// ... construct an equilibrated palette (3 red bits, 3 green bits, 2 blue bits)
// NOTE: this code is integrally taken from MFC example Cube
		n = 1 << pfd.cColorBits;
        pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + n * sizeof(PALETTEENTRY)];

        ASSERT(pPal != NULL);

        pPal->palVersion = 0x300;
        pPal->palNumEntries = n;
        for (i=0; i<n; i++)
        {
            pPal->palPalEntry[i].peRed=ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
            pPal->palPalEntry[i].peGreen=ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
            pPal->palPalEntry[i].peBlue=ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
            pPal->palPalEntry[i].peFlags=0;
        }

// fix up the palette to include the default Windows palette
        if ((pfd.cColorBits == 8)                           &&
            (pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
            (pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
            (pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6)
           )
        {
			for (i = 1 ; i <= 12 ; i++)
                pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
        }

        m_CurrentPalette.CreatePalette(pPal);
        delete pPal;

// set the palette
        m_pOldPalette=m_pCDC->SelectPalette(&m_CurrentPalette, FALSE);
        m_pCDC->RealizePalette();
    }
}

unsigned char CGLEnabledView::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
    unsigned char val;

    val = (unsigned char) (i >> shift);
    switch (nbits) 
	{

    case 1:
        val &= 0x1;
        return _oneto8[val];
    case 2:
        val &= 0x3;
        return _twoto8[val];
    case 3:
        val &= 0x7;
        return _threeto8[val];

    default:
        return 0;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView message handlers

int CGLEnabledView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1) return -1;
	
// OpenGL rendering context creation
	PIXELFORMATDESCRIPTOR pfd;
    int         n;

// initialize the private member
	m_pCDC= new CClientDC(this);

// choose the requested video mode
    if (!bSetupPixelFormat()) return 0;
	
// ask the system if the video mode is supported
    n=::GetPixelFormat(m_pCDC->GetSafeHdc());
    ::DescribePixelFormat(m_pCDC->GetSafeHdc(),n,sizeof(pfd),&pfd);

// create a palette if the requested video mode has 256 colors (indexed mode)
    CreateRGBPalette();

// link the Win Device Context with the OGL Rendering Context
    m_hRC = wglCreateContext(m_pCDC->GetSafeHdc());

// specify the target DeviceContext (window) of the subsequent OGL calls
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

// performs default setting of rendering mode,etc..
	OnCreateGL();

// free the target DeviceContext (window)
    wglMakeCurrent(NULL,NULL);
	
	return 0;
}

void CGLEnabledView::OnCreateGL()
{
// perform hidden line/surface removal (enabling Z-Buffer)
	glEnable(GL_DEPTH_TEST);

// set background color to black
	glClearColor(0.f,0.f,0.f,1.0f );

// set clear Z-Buffer value
	glClearDepth(1.0f);
}

void CGLEnabledView::OnDestroy() 
{
// specify the target DeviceContext (window) of the subsequent OGL calls
    wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

// remove all display lists
	for (int c=0;c<MAX_LISTS;c++) if(m_DispListVector[c]) glDeleteLists(m_DispListVector[c],1);

// release definitely OGL Rendering Context
	if (m_hRC!=NULL) ::wglDeleteContext(m_hRC);

// Select our palette out of the dc
	CPalette palDefault;
	palDefault.CreateStockObject(DEFAULT_PALETTE);
	m_pCDC->SelectPalette(&palDefault, FALSE);

// destroy Win Device Context
	if(m_pCDC) delete m_pCDC;

// finally call the base function
	CView::OnDestroy();	
}

BOOL CGLEnabledView::PreCreateWindow(CREATESTRUCT& cs) 
{
// these styles are requested by OpenGL
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

// these styles are meant for a use of this class in a MDI application
	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW);

	return CView::PreCreateWindow(cs);
}


BOOL CGLEnabledView::OnEraseBkgnd(CDC* pDC) 
{
// OGL has his own background erasing so tell Windows to skip
	return TRUE;
}

void CGLEnabledView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
// when called with a nonzero window:
	if ( 0 < cx && 0 < cy )
	{
// update the rect and the aspect ratio
		m_ClientRect.right = cx;
		m_ClientRect.bottom = cy;
		m_dAspectRatio=double(cx)/double(cy);

// specify the target DeviceContext of the subsequent OGL calls
		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

// call the virtual sizing procedure (to be overridden by user)
		OnSizeGL(cx,cy);

// free the target DeviceContext (window)
		wglMakeCurrent(NULL,NULL);

// force redraw
		Invalidate(TRUE);
	};
}

void CGLEnabledView::OnSizeGL(int cx, int cy)
{
// set correspondence between window and OGL viewport
		glViewport(0,0,cx,cy);

// update the camera
 		glPushMatrix();
			glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluPerspective(40.0,m_dAspectRatio,0.1f, 10.0f);
				glTranslatef(0.0f,0.0f,-4.f);
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
}

BOOL CGLEnabledView::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
	ASSERT(m_hMouseCursor!=NULL);
	::SetCursor(m_hMouseCursor);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGLEnabledView services

void CGLEnabledView::VideoMode(ColorsNumber &c, ZAccuracy &z, BOOL &dbuf)
{
// set default videomode
	c=MILLIONS;
	z=NORMAL;
	dbuf=TRUE;
}

void CGLEnabledView::SetMouseCursor(HCURSOR mcursor)
{
// set the specified cursor (only if it is a valid one)
	if(mcursor!=NULL) m_hMouseCursor=mcursor;
}

const CString CGLEnabledView::GetInformation(InfoField type)
{
	PIXELFORMATDESCRIPTOR pfd;
	CString str("Not Available");

// Get information about the DC's current pixel format 
	::DescribePixelFormat( m_pCDC->GetSafeHdc(), ::GetPixelFormat(m_pCDC->GetSafeHdc()),sizeof(PIXELFORMATDESCRIPTOR), &pfd ); 

// specify the target DeviceContext of the subsequent OGL calls
	wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);

	switch(type)
	{
// Derive driver information
	case ACCELERATION: if( 0==(INSTALLABLE_DRIVER_TYPE_MASK & pfd.dwFlags) ) str="Fully Accelerated (ICD)"; // fully in hardware (fastest)
						else if (INSTALLABLE_DRIVER_TYPE_MASK==(INSTALLABLE_DRIVER_TYPE_MASK & pfd.dwFlags) ) str="Partially Accelerated (MCD)"; // partially in hardware (pretty fast, maybe..)
							 else str="Not Accelerated (Software)";	// software
						break;
// get the company name responsible for this implementation
	case VENDOR:str=(char*)::glGetString(GL_VENDOR);
				if ( ::glGetError()!=GL_NO_ERROR) str.Format("Not Available");// failed!
				break;
// get the renderer name; this is specific of an hardware configuration
	case RENDERER:str=(char*)::glGetString(GL_RENDERER);
					if ( ::glGetError()!=GL_NO_ERROR) str.Format("Not Available");// failed!
					break;
// get the version
	case VERSION:str=(char*)::glGetString(GL_VERSION);
				if ( ::glGetError()!=GL_NO_ERROR) str.Format("Not Available");// failed!
				break;
// return a space separated list of extensions
	case EXTENSIONS: str=(char*)::glGetString(GL_EXTENSIONS);
				if ( ::glGetError()!=GL_NO_ERROR) str.Format("Not Available");// failed!
				break;
	};

// free the target DeviceContext (window) and return the result
	wglMakeCurrent(NULL,NULL);
	return str;
}

void CGLEnabledView::DrawDispLists()
{
// check if we are already inside a drawing session
	if(m_hRC==wglGetCurrentContext() && m_pCDC->GetSafeHdc()==wglGetCurrentDC() )
	{
// draw directly all display lists
		for (int c=0;c<MAX_LISTS;c++) if(m_DispListVector[c]) glCallList(m_DispListVector[c]);
	}
	else
	{
// specify the target DeviceContext of the subsequent OGL calls
		wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
// draw all display lists
		for (int c=0;c<MAX_LISTS;c++) if(m_DispListVector[c]) glCallList(m_DispListVector[c]);
// free the target DeviceContext (window)
		wglMakeCurrent(NULL,NULL);
	};
}

void CGLEnabledView::BeginDispList()
{
// check if we aren't inside another couple begin/end
	if(!m_InsideDispList)
	{
// search a free slot
		for (int c=0;m_DispListVector[c]!=0;c++);
// check if we are inside a drawing session or not....
		if(!( m_hRC==wglGetCurrentContext() && m_pCDC->GetSafeHdc()==wglGetCurrentDC() ))
		{
// ...if not specify the target DeviceContext of the subsequent OGL calls
			wglMakeCurrent(m_pCDC->GetSafeHdc(), m_hRC);
// set a warning for EndDispList
			m_ExternDispListCall=TRUE;
		};
// create a handle to the disp list (actually an integer)
		m_DispListVector[c]=glGenLists(1);
// set a semaphore
		m_InsideDispList=TRUE;
// start the disp list: all subsequent OGL calls will be redirected to the list
		glNewList(m_DispListVector[c],GL_COMPILE);
	};
}

void CGLEnabledView::EndDispList()
{
// close the disp list
	glEndList();
// unset the semaphore
	m_InsideDispList=FALSE;
// if beginDispList set the warn free the target DeviceContext
	if(m_ExternDispListCall) wglMakeCurrent(NULL,NULL);
}

/*///////////////////////////////////////////////////////////////////////////
// CGLEnabledView tesselation support
// NOTE: this section is incomplete and will be developed in future versions

// These are the callback wrappers for the tesselator
static void CALLBACK beginWrapper(GLenum type)
{
//	glBegin(type);
	CGLEnabledView::BeginTessCallback(type);
}

static void CALLBACK errorCallback(GLenum errorCode)
{
	const GLubyte *estring;
	CString mexstr;
// get the error descritption from OGL
	estring = gluErrorString(errorCode);
// set-up and show a message box
	mexstr.Format("Tessellation Error: %s\n", estring);
	AfxMessageBox(mexstr,MB_OK | MB_ICONEXCLAMATION);
// replicate mex to debug trace
	TRACE("Tessellation Error: %s\n", estring);
}

static void CALLBACK endWrapper(void)
{
//	glEnd();
	CGLEnabledView::EndTessCallback();
}

static void CALLBACK vertexWrapper(GLvoid *vertex)
{
//	glVertex3dv( (const double *)vertex );
	CGLEnabledView::VertexTessCallback(vertex)
}

static void CALLBACK combineWrapper(GLdouble coords[3], GLdouble *data[4], GLfloat weight[4], GLdouble **dataOut )
{
	GLdouble *vertex;
	vertex = new GLdouble[3];

	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];
	*dataOut = vertex;
	AddGarbage(vertex);
	CGLEnabledView::CombineTessCallback(coords,data,weight,dataOut)
}
*/
