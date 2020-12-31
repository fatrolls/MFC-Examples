// FormCommandView.cpp : implementation file
//

#include "stdafx.h"
#include "Tool.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "FormCommandView.h"
#include "ToolDoc.h"
#include "RenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView

IMPLEMENT_DYNCREATE(CFormCommandView, CFormView)

CFormCommandView::CFormCommandView()
: CFormView(CFormCommandView::IDD)
{
	//{{AFX_DATA_INIT(CFormCommandView)
	m_Lighting = TRUE;
	m_Smooth = FALSE;
	m_Antialias = FALSE;
	m_Model = 1;
	m_VRotate = FALSE;
	m_LinkScale = FALSE;
	//}}AFX_DATA_INIT
}

CFormCommandView::~CFormCommandView()
{
}

void CFormCommandView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormCommandView)
	DDX_Control(pDX, IDC_SLIDER_Z, m_SliderScaleZ);
	DDX_Control(pDX, IDC_SLIDER_Y, m_SliderScaleY);
	DDX_Control(pDX, IDC_SLIDER_X, m_SliderScaleX);
	DDX_Control(pDX, IDC_FRAME_COLOR_LIGHT_AMBIENT, m_ControlColorLightAmbient);
	DDX_Control(pDX, IDC_FRAME_COLOR_BACK, m_ControlBackColor);
	DDX_Check(pDX, IDC_CHECK_LIGHTING, m_Lighting);
	DDX_Check(pDX, IDC_CHECK_SMOOTH, m_Smooth);
	DDX_Check(pDX, IDC_CHECK_ANTIALIAS, m_Antialias);
	DDX_Radio(pDX, IDC_RADIO_MODEL_0, m_Model);
	DDX_Check(pDX, IDC_CHECK_VROTATION, m_VRotate);
	DDX_Check(pDX, IDC_CHECK_LINK_SCALE, m_LinkScale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormCommandView, CFormView)
	//{{AFX_MSG_MAP(CFormCommandView)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_RADIO_MODEL_0, OnRadioModel0)
	ON_BN_CLICKED(IDC_RADIO_MODEL_1, OnRadioModel1)
	ON_BN_CLICKED(IDC_RADIO_MODEL_2, OnRadioModel2)
	ON_BN_CLICKED(IDC_CHECK_LIGHTING, OnCheckLighting)
	ON_BN_CLICKED(IDC_CHECK_SMOOTH, OnCheckSmooth)
	ON_BN_CLICKED(IDC_CHECK_VROTATION, OnCheckVrotation)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_LINK_SCALE, OnCheckLinkScale)
	ON_BN_CLICKED(IDC_CHECK_ANTIALIAS, OnCheckAntialias)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormCommandView diagnostics

#ifdef _DEBUG
void CFormCommandView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormCommandView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CToolDoc* CFormCommandView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}

#endif //_DEBUG

//********************************************
// OnPaint
//********************************************
void CFormCommandView::OnPaint() 
{
	// Device context for painting
	CPaintDC dc(this); 
	
	// Options are stored in Application
	CToolApp *pApp = (CToolApp *)AfxGetApp();
	CRect rect;
	
	// Color back
	m_ControlBackColor.GetWindowRect(&rect);	
	ScreenToClient(&rect);
	CBrush BrushBack(pApp->m_OptionColorGlBack);
	dc.FillRect(&rect,&BrushBack);
	
	// Color light ambient
	m_ControlColorLightAmbient.GetWindowRect(&rect);	
	ScreenToClient(&rect);
	CBrush BrushLightAmbient(pApp->m_OptionColorGlLightAmbient);
	dc.FillRect(&rect,&BrushLightAmbient);
}

//********************************************
// OnLButtonUp
//********************************************
void CFormCommandView::OnLButtonUp(UINT nFlags, 
																	 CPoint point) 
{
	CRect rect;
	CToolApp *pApp = (CToolApp *)AfxGetApp();
	
	// Option back color
	m_ControlBackColor.GetWindowRect(&rect);	
	ScreenToClient(&rect);
	if(rect.PtInRect(point))
	{
		CColorDialog dlg(pApp->m_OptionColorGlBack);
		if(dlg.DoModal()==IDOK)
		{
			pApp->m_OptionColorGlBack = dlg.GetColor();	
			CRenderView *pView = (CRenderView *)GetRenderView();
			pView->m_ClearColorRed   = (float)GetRValue(pApp->m_OptionColorGlBack) / 255.0f;
			pView->m_ClearColorGreen = (float)GetGValue(pApp->m_OptionColorGlBack) / 255.0f;
			pView->m_ClearColorBlue  = (float)GetBValue(pApp->m_OptionColorGlBack) / 255.0f;
			this->InvalidateRect(&rect,FALSE);
			pView->InvalidateRect(NULL,FALSE); 
		}
	}
	
	// Option ambient light color
	m_ControlColorLightAmbient.GetWindowRect(&rect);	
	ScreenToClient(&rect);
	if(rect.PtInRect(point))
	{
		CColorDialog dlg(pApp->m_OptionColorGlLightAmbient);
		if(dlg.DoModal()==IDOK)
		{
			pApp->m_OptionColorGlLightAmbient = dlg.GetColor();	
			CRenderView *pView = (CRenderView *)GetRenderView();

			// Refresh Light0
			float r = (float)GetRValue(pApp->m_OptionColorGlLightAmbient) / 255.0f;
			float g = (float)GetGValue(pApp->m_OptionColorGlLightAmbient) / 255.0f;
			float b = (float)GetBValue(pApp->m_OptionColorGlLightAmbient) / 255.0f;
			float	ambientProperties[]  = {r,g,b,1.0f};
			glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);

			// Refresh views
			this->InvalidateRect(&rect,FALSE);
			pView->InvalidateRect(NULL,FALSE); 

		}
	}
	
	
		
	CFormView::OnLButtonUp(nFlags, point);
}


//********************************************
// GetRenderView
//********************************************
CView *CFormCommandView::GetRenderView() 
{
	CToolApp *pApp = (CToolApp *)AfxGetApp();
	CMainFrame *pMainFrame = (CMainFrame *)pApp->m_pMainWnd;
	CChildFrame *pFrame = (CChildFrame *)pMainFrame->GetActiveFrame();
	CView *pView = (CView *)pFrame->m_wndSplitter.GetPane(0,1);
	return pView;
}



//********************************************
// Model
//********************************************
void CFormCommandView::OnRadioModel0() 
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	this->GetRenderView()->InvalidateRect(NULL,FALSE); 
}

void CFormCommandView::OnRadioModel1() 
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	this->GetRenderView()->InvalidateRect(NULL,FALSE); 
}

void CFormCommandView::OnRadioModel2() 
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	this->GetRenderView()->InvalidateRect(NULL,FALSE); 
}

//********************************************
// OnCheckLighting
//********************************************
void CFormCommandView::OnCheckLighting() 
{
	m_Lighting = !m_Lighting;
	if(m_Lighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
	this->GetRenderView()->InvalidateRect(NULL,FALSE); 
}

//********************************************
// OnCheckSmooth
//********************************************
void CFormCommandView::OnCheckSmooth() 
{
	m_Smooth = !m_Smooth;
	if(m_Smooth)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);
	this->GetRenderView()->InvalidateRect(NULL,FALSE); 
}

void CFormCommandView::OnCheckVrotation() 
{
	m_VRotate = !m_VRotate;
	CRenderView *pView = (CRenderView *)GetRenderView();
	if(m_VRotate)
		pView->SetTimer(1,10,NULL);
	else
		pView->KillTimer(1);
}

//********************************************
// OnInitialUpdate
//********************************************
void CFormCommandView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// Slider
	TRACE("Sliders : updating...\n");
	m_SliderScaleX.SetRange(1,100,TRUE);
	m_SliderScaleY.SetRange(1,100,TRUE);
	m_SliderScaleZ.SetRange(1,100,TRUE);

	m_SliderScaleX.SetPos(50);
	m_SliderScaleY.SetPos(50);
	m_SliderScaleZ.SetPos(50);
	
}

//********************************************
// OnHScroll
//********************************************
void CFormCommandView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch( nSBCode )
	{
	case TB_BOTTOM:
		UpdateScale();
		break;
	case TB_ENDTRACK:
		UpdateScale();
		break;
	case TB_LINEDOWN:
		UpdateScale();
		break;
	case TB_LINEUP:
		UpdateScale();
		break;
	case TB_PAGEDOWN:
		UpdateScale();
		break;
	case TB_PAGEUP:
		UpdateScale();
		break;
	case TB_THUMBPOSITION:
		UpdateScale();
		break;
	case TB_THUMBTRACK:
		UpdateScale();
		break;
	case TB_TOP:
		UpdateScale();
		break;
	default:
		{}
	}

	// Update scaling
	GetRenderView()->InvalidateRect(NULL,FALSE); 
	
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CFormCommandView::UpdateScale() 
{
	CRenderView *pView = (CRenderView *)GetRenderView();
	pView->m_xScaling = (float)m_SliderScaleX.GetPos()/50.0f;
	pView->m_yScaling = (float)m_SliderScaleY.GetPos()/50.0f; // TODO : link
	pView->m_zScaling = (float)m_SliderScaleZ.GetPos()/50.0f;

	if(m_LinkScale)
	{
		m_SliderScaleY.SetPos(m_SliderScaleX.GetPos());
		m_SliderScaleZ.SetPos(m_SliderScaleX.GetPos());
		pView->m_yScaling = pView->m_zScaling = pView->m_xScaling;
	}

	return TRUE;
}

void CFormCommandView::OnCheckLinkScale() 
{
	m_LinkScale = !m_LinkScale;	

	if(m_LinkScale)
	{
		CRenderView *pView = (CRenderView *)GetRenderView();
		m_SliderScaleY.SetPos(m_SliderScaleX.GetPos());
		m_SliderScaleZ.SetPos(m_SliderScaleX.GetPos());
		pView->m_yScaling = pView->m_zScaling = pView->m_xScaling;
	}

	m_SliderScaleY.EnableWindow(!m_LinkScale);
	m_SliderScaleZ.EnableWindow(!m_LinkScale);
	GetRenderView()->InvalidateRect(NULL,FALSE); 

}

//********************************************
// OnCheckAntialias
// Toggle antialiased lines
//********************************************
void CFormCommandView::OnCheckAntialias() 
{
	m_Antialias = !m_Antialias;

	if(m_Antialias)
	{
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
		glLineWidth(1.5);
	}
	else
	{
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
		glLineWidth(1.0);
	}
	GetRenderView()->InvalidateRect(NULL,FALSE); 
}
