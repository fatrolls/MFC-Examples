// DialogGLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DialogGL.h"
#include "DialogGLDlg.h"

#include "math.h"
#include "mmsystem.h"
#include "resource.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogGLDlg dialog

CDialogGLDlg::CDialogGLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogGLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogGLDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	DragAcceptFiles(TRUE);

	m_hGLContext = NULL;
	m_GLPixelIndex = 0;


	m_xRotate = 0;
	m_yRotate = 0;
	m_Rotate = FALSE;


	m_size = 1.5;
	m_exp = 8;
	m_pixel1 = NULL;

	m_RightButtonDown = FALSE;
	m_LeftButtonDown = FALSE;

	ReadTexture("Sky256.raw");


}

void CDialogGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogGLDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogGLDlg, CDialog)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CDialogGLDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_COMMAND(ID_POPUP_ROTATE, OnPopupRotate)
	ON_COMMAND(ID_POPUP_SIZE_DECREASE, OnPopupSizeDecrease)
	ON_COMMAND(ID_POPUP_SIZE_INCREASE, OnPopupSizeIncrease)
	ON_COMMAND(ID_POPUP_TEXTUREFILE, OnPopupTexturefile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogGLDlg message handlers

BOOL CDialogGLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDialogGLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDialogGLDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting
		RenderScene();
		SwapBuffers(dc.m_ps.hdc);
		CDialog::OnPaint();

	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDialogGLDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


BOOL CDialogGLDlg::SetWindowPixelFormat(HDC hDC)
{
PIXELFORMATDESCRIPTOR pixelDesc;

pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
pixelDesc.nVersion = 1;

pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | 
					PFD_SUPPORT_OPENGL |
					PFD_DOUBLEBUFFER |
					PFD_STEREO_DONTCARE;

pixelDesc.iPixelType = PFD_TYPE_RGBA;
pixelDesc.cColorBits = 32;
pixelDesc.cRedBits = 8;
pixelDesc.cRedShift = 16;
pixelDesc.cGreenBits = 8;
pixelDesc.cGreenShift = 8;
pixelDesc.cBlueBits = 8;
pixelDesc.cBlueShift = 0;
pixelDesc.cAlphaBits = 0;
pixelDesc.cAlphaShift = 0;
pixelDesc.cAccumBits = 64;
pixelDesc.cAccumRedBits = 16;
pixelDesc.cAccumGreenBits = 16;
pixelDesc.cAccumBlueBits = 16;
pixelDesc.cAccumAlphaBits = 0;
pixelDesc.cDepthBits = 32;
pixelDesc.cStencilBits = 8;
pixelDesc.cAuxBuffers = 0;
pixelDesc.iLayerType = PFD_MAIN_PLANE;
pixelDesc.bReserved = 0;
pixelDesc.dwLayerMask = 0;
pixelDesc.dwVisibleMask = 0;
pixelDesc.dwDamageMask = 0;

m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
if(m_GLPixelIndex==0) // Choose default
{
	m_GLPixelIndex = 1;
	if(DescribePixelFormat(hDC,m_GLPixelIndex,
		sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
	{
		return FALSE;
	}
}

if(SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc)==FALSE)
{
	return FALSE;
}

return TRUE;
}


BOOL CDialogGLDlg::CreateViewGLContext(HDC hDC)
{
m_hGLContext = wglCreateContext(hDC);

if(m_hGLContext==NULL)
	return FALSE;

if(wglMakeCurrent(hDC,m_hGLContext)==FALSE)
	return FALSE;



return TRUE;
}



int CDialogGLDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if(SetWindowPixelFormat(hDC)==FALSE)
		return 0;
	
	if(CreateViewGLContext(hDC)==FALSE)
		return 0;

	COLORREF color = ::GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f,
				 (float)GetGValue(color)/255.0f,
				 (float)GetBValue(color)/255.0f,
				 1.0);

	SetTimer(0,10,NULL);
	return 0;
}
	

void CDialogGLDlg::OnDestroy() 
{
	
	CDialog::OnDestroy();

	if(m_pixel1 != NULL)
		delete [] m_pixel1;

	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);

	if(m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}


	
}

void CDialogGLDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	GLsizei width,height;
	GLdouble aspect;

	width = cx;
	height = cy;

	if(cy==0)
		aspect = (GLdouble)width;
	else
		aspect = (GLdouble)width/(GLdouble)height;

	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,aspect,1,10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glDrawBuffer(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	
}

void CDialogGLDlg::RenderScene()
{

	GLfloat LightAmbient[] =  { 0.1f, 0.1f, 0.1f, 0.1f};
	GLfloat LightDiffuse[] =  { 0.7f, 0.7f, 0.7f, 0.7f};
	GLfloat LightSpecular[] = { 0.5f, 0.5f, 0.5f, 0.1f};
	GLfloat LightPosition0[] = { 0.0f, 0.0f, 5.0f, 0.0f}; 

	GLfloat RedSurface[]   = { 1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat GreenSurface[] = { 0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat BlueSurface[]  = { 0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat WhiteSurface[]  = { 1.0f, 1.0f, 1.0f, 1.0f};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// LIGHT0 parameters
	glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,LightSpecular);
	glLightfv(GL_LIGHT0,GL_POSITION,LightPosition0);
	glEnable(GL_LIGHT0);

	glPushMatrix();

	// Position / translation
	glTranslated(0.0,0.0,-8.0);
	glRotated(m_xRotate, 1.0, 0.0, 0.0);
	glRotated(m_yRotate, 0.0, 1.0, 0.0);

		//glEnable(GL_LINE_SMOOTH);
		//glEnable(GL_POLYGON_SMOOTH);


	// Material aspect
    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_ambient_color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 50.0f };
    GLfloat mat_emission[] = {0.2f, 0.2f, 0.2f, 0.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

  
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);
	//glEnable(GL_POLYGON_SMOOTH);

	// auxSolidBox(1.5,2.0,0.1);

    glShadeModel(GL_SMOOTH);

	float x = m_size;

	if(m_pixel1 != NULL)
		glTexImage2D(GL_TEXTURE_2D,0,3,m_width,m_height,0,GL_RGB,GL_UNSIGNED_BYTE,m_pixel1);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);


	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0, 0.0); glVertex3d( x,  x, x);
		glTexCoord2f(1, 0.0); glVertex3d( x, -x, x);
		glTexCoord2f(1, 1); glVertex3d(  -x, -x, x);
		glTexCoord2f(0.0, 1); glVertex3d(  -x,  x, x);
	glEnd();


	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,-1.0);
		glTexCoord2f(0.0, 0.0); glVertex3d( -x,  x, -x);
		glTexCoord2f(1.0, 0.0); glVertex3d( -x, -x, -x);
		glTexCoord2f(1.0, 1.0); glVertex3d(  x, -x, -x);
		glTexCoord2f(0.0, 1.0); glVertex3d(  x,  x, -x);
	glEnd();


	glBegin(GL_POLYGON);
		glNormal3d(1.0,0.0,0.0);
		glTexCoord2f(0.0, 0.0); glVertex3d( x, x, x);
		glTexCoord2f(1.0, 0.0); glVertex3d( x, x, -x);
		glTexCoord2f(1.0, 1.0); glVertex3d( x, -x, -x);
		glTexCoord2f(0.0, 1.0); glVertex3d( x, -x, x);
	glEnd();


	glBegin(GL_POLYGON);
		glNormal3d(-1.0,0.0,0.0);
		glTexCoord2f(0.0, 0.0); glVertex3d( -x, x, x);
		glTexCoord2f(1.0, 0.0); glVertex3d( -x, x, -x);
		glTexCoord2f(1.0, 1.0); glVertex3d( -x, -x, -x);
		glTexCoord2f(0.0, 1.0); glVertex3d( -x, -x, x);
	glEnd();


	glBegin(GL_POLYGON);
		glNormal3d(0.0,-1.0,0.0);
		glTexCoord2f(0.0, 0.0); glVertex3d( -x, -x, x);
		glTexCoord2f(1.0, 0.0); glVertex3d( x, -x, x);
		glTexCoord2f(1.0, 1.0); glVertex3d( x, -x, -x);
		glTexCoord2f(0.0, 1.0); glVertex3d( -x, -x, -x);
	glEnd();


	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);
		glTexCoord2f(0.0, 0.0); glVertex3d( -x, x, x);
		glTexCoord2f(1.0, 0.0); glVertex3d( x, x, x);
		glTexCoord2f(1.0, 1.0); glVertex3d( x, x, -x);
		glTexCoord2f(0.0, 1.0); glVertex3d( -x, x, -x);
	glEnd();


    glDisable(GL_TEXTURE_2D);

	glPopMatrix();



	// Control sphere
	/*
	glPushMatrix();
	glTranslated(2.5,2.0,-8.0);
	glRotated(m_xRotate, 1.0, 0.0, 0.0);
	glRotated(m_yRotate, 0.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT,GL_LINE);
	glPolygonMode(GL_BACK,GL_LINE);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(1.0);
	auxSolidSphere(0.5f);
	glPopMatrix();*/

}


	




void CDialogGLDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_LeftButtonDown = TRUE;
	m_LeftDownPos = point;
	KillTimer(0);
	CDialog::OnLButtonDown(nFlags, point);
}

void CDialogGLDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_LeftButtonDown = FALSE;
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CDialogGLDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_LeftButtonDown)
	{
		CSize rotate = m_LeftDownPos - point;
		m_LeftDownPos = point;
		m_yRotate -= rotate.cx;
		m_xRotate -= rotate.cy;
		InvalidateRect(NULL,FALSE);
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

void CDialogGLDlg::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_DIALOG_GLDLG));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}


void CDialogGLDlg::Rotate()
{
	m_yRotate -= 2;
	InvalidateRect(NULL,FALSE);
}

void CDialogGLDlg::OnTimer(UINT nIDEvent) 
{
	m_yRotate -= 6;
	m_xRotate -= 4;
	InvalidateRect(NULL,FALSE);
	CDialog::OnTimer(nIDEvent);
}

void CDialogGLDlg::OnPopupRotate() 
{
	SetTimer(0,10,NULL);
}

void CDialogGLDlg::OnPopupSizeDecrease() 
{
	m_size -= 0.1f;
}

void CDialogGLDlg::OnPopupSizeIncrease() 
{
	m_size += 0.1f;
}

//***********************************************
// OnPopupTexturefile
//***********************************************
void CDialogGLDlg::OnPopupTexturefile() 
{
	CFileDialog	dlg(TRUE,"*.raw","*.raw",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"RAW image file (*.raw)",NULL);

	if(dlg.DoModal() == IDOK)
	{
		CString filename = dlg.GetFileName();
		ReadTexture(filename.GetBuffer(255));
		filename.ReleaseBuffer();
	}

}


//***********************************************
// ReadTexture
//***********************************************
void CDialogGLDlg::ReadTexture(char *filename)
{
	m_width = (int)pow(2,m_exp); 
	m_height = (int)pow(2,m_exp);
	m_pixel1 = NULL;

	if(m_pixel1 != NULL)
	{
		delete [] m_pixel1;
		m_pixel1 = NULL;
	}

	m_pixel1 = new BYTE[3*m_width*m_height];

	if(m_pixel1 != NULL)
		ReadTextureFile(filename,m_pixel1,m_width,m_height);
}


//***********************************************
// ReadTextureFile
//***********************************************
BOOL CDialogGLDlg::ReadTextureFile(char *filename,
									BYTE *pData,
									unsigned int width,
									unsigned int height)
{
	if(pData == NULL)
		return FALSE;

	FILE *file;
	file = fopen(filename,"rb");
	if(file == NULL)
		return FALSE;

	int size = fread(pData,1,m_width*height*3,file);

	if(size != (int)(width*height*3))
	{
		fclose(file);
		return FALSE;
	}

	fclose(file);

	return TRUE;
}
