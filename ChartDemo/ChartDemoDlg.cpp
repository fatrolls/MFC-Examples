// ChartDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChartDemo.h"
#include "ChartDemoDlg.h"

#include "ChartLineSerie.h"
#include "ChartPointsSerie.h"
#include "ChartSurfaceSerie.h"
#include "ChartGrid.h"

#include "SeriesPropDlg.h"
#include "LinePropDialog.h"
#include "SurfacePropDialog.h"
#include "PointsPropDialog.h"

#include "ChartBarSerie.h"
#include "ChartLabel.h"

#include "ChartAxisLabel.h"
#include "ChartStandardAxis.h"
#include "ChartDateTimeAxis.h"

#include "ChartCrossHairCursor.h"
#include "ChartDragLineCursor.h"

#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

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
// CChartDemoDlg dialog

CChartDemoDlg::CChartDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChartDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartDemoDlg)
	DDX_Control(pDX, IDC_TITLE_EDIT, m_TitlesEdit);
	DDX_Control(pDX, IDC_SERIES_LIST, m_SeriesList);
	DDX_Control(pDX, IDC_AXISMINVAL_EDIT, m_AxisMinValEdit);
	DDX_Control(pDX, IDC_AXISMAXVAL_EDIT, m_AxisMaxValEdit);
	DDX_Control(pDX, IDC_LEGENDVIS_CHECK, m_LegendVisBtn);
	DDX_Control(pDX, IDC_BKGND_COLBTN, m_BackgndColSel);
	DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChartDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CChartDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADDSERIES, OnAddseries)
	ON_BN_CLICKED(IDC_LEGENDVIS_CHECK, OnLegendVisible)
	ON_BN_CLICKED(IDC_BOTTOMAXIS_RADIO, OnBottomAxisRadio)
	ON_BN_CLICKED(IDC_LEFTAXIS_RADIO, OnLeftAxisRadio)
	ON_BN_CLICKED(IDC_RIGHTAXIS_RADIO, OnRightAxisRadio)
	ON_BN_CLICKED(IDC_TOPAXIS_RADIO, OnTopAxisRadio)
	ON_BN_CLICKED(IDC_AXISAUTOMATIC_CHECK, OnAxisAutomaticCheck)
	ON_BN_CLICKED(IDC_AXISGRIDVIS_CHECK, OnAxisGridVisCheck)
	ON_BN_CLICKED(IDC_AXISVISIBLE_CHECK, OnAxisVisibleCheck)
	ON_BN_CLICKED(IDC_AXISSCROLLBAR_CHECK, OnAxisScrollBarCheck)	
	ON_MESSAGE(CPN_SELENDOK,    OnChangeBckCol)
	ON_EN_KILLFOCUS(IDC_AXISMAXVAL_EDIT, OnChangeAxisMax)
	ON_EN_KILLFOCUS(IDC_AXISMINVAL_EDIT, OnChangeAxisMin)
	ON_BN_CLICKED(IDC_AXISINVERTED_CHECK, OnAxisInvertedCheck)
	ON_EN_KILLFOCUS(IDC_AXISLABEL_EDIT, OnChangeAxisLabel)
	ON_BN_CLICKED(IDC_DELETESERIES, OnDeleteSeries)
	ON_EN_KILLFOCUS(IDC_TITLE_EDIT, OnChangeTitle)
	ON_BN_CLICKED(IDC_PAN_CHECK, OnPanCheck)
	ON_BN_CLICKED(IDC_ZOOM_CHECK, OnZoomCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartDemoDlg message handlers

BOOL CChartDemoDlg::OnInitDialog()
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

	((CButton*)GetDlgItem(IDC_LEFTAXIS_RADIO))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_PAN_CHECK))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_ZOOM_CHECK))->SetCheck(1);

	CChartStandardAxis* pBottomAxis = 
		m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetMinMax(0, 10);
	CChartStandardAxis* pLeftAxis =
		m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetMinMax(0, 10);
	CChartStandardAxis* pTopAxis =
		m_ChartCtrl.CreateStandardAxis(CChartCtrl::TopAxis);
	pTopAxis->SetMinMax(0, 10);
	CChartStandardAxis* pRightAxis =
		m_ChartCtrl.CreateStandardAxis(CChartCtrl::RightAxis);
	pRightAxis->SetMinMax(0, 10);

	OnLeftAxisRadio();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChartDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChartDemoDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChartDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CChartDemoDlg::OnAddseries() 
{
	CSeriesPropDlg PropertiesDlg;
	if (PropertiesDlg.DoModal() == IDCANCEL)
		return;

	int Type = PropertiesDlg.m_iSeriesType;
	TChartString Name = PropertiesDlg.m_strSeriesName;
	COLORREF Color = PropertiesDlg.m_SeriesColour;

	CChartXYSerie* pSeries = NULL;
	switch (Type)
	{
	// Line series
	case 0:
		{
			bool bSecondHorizAxis = (PropertiesDlg.m_iHorizAxis == 1);
			bool bSecondVertAxis = (PropertiesDlg.m_iVertAxis == 1);
			CChartLineSerie* pLineSeries = m_ChartCtrl.CreateLineSerie(bSecondHorizAxis, bSecondVertAxis);
			pSeries = pLineSeries;

			CLinePropDialog LinePropDlg;
			LinePropDlg.DoModal();

			pLineSeries->SetWidth(LinePropDlg.m_iLineWidth);
			pLineSeries->SetPenStyle(LinePropDlg.m_iPenStyle);
		}
		break;

	// Points series
	case 1:
		{
			bool bSecondHorizAxis = (PropertiesDlg.m_iHorizAxis == 1);
			bool bSecondVertAxis = (PropertiesDlg.m_iVertAxis == 1);
			CChartPointsSerie* pPointsSeries = m_ChartCtrl.CreatePointsSerie(bSecondHorizAxis, bSecondVertAxis);
			pSeries = pPointsSeries;

			CPointsPropDialog PointsPropDlg;
			PointsPropDlg.DoModal();

			switch (PointsPropDlg.m_iPointsType)
			{
			case 0:
				pPointsSeries->SetPointType(CChartPointsSerie::ptEllipse);
				break;

			case 1:
				pPointsSeries->SetPointType(CChartPointsSerie::ptRectangle);
				break;

			case 2:
				pPointsSeries->SetPointType(CChartPointsSerie::ptTriangle);
				break;
			}

			pPointsSeries->SetPointSize(PointsPropDlg.m_iPointsWidth,PointsPropDlg.m_iPointsHeight);
		}
		break;

	// Surface series
	case 2:
		{
			bool bSecondHorizAxis = (PropertiesDlg.m_iHorizAxis == 1);
			bool bSecondVertAxis = (PropertiesDlg.m_iVertAxis == 1);
			CChartSurfaceSerie* pSurfSeries = m_ChartCtrl.CreateSurfaceSerie(bSecondHorizAxis, bSecondVertAxis);
			pSeries = pSurfSeries;

			CSurfacePropDialog SurfPropDlg;
			SurfPropDlg.DoModal();

			switch (SurfPropDlg.m_FillStyle)
			{
			case 0:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsSolid);
				break;
			case 1:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchDownDiag);
				break;
			case 2:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchUpDiag);
				break;
			case 3:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchCross);
				break;
			case 4:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchDiagCross);
				break;
			case 5:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchHorizontal);
				break;
			case 6:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchVertical);
				break;
			}

			if (SurfPropDlg.m_iHorizSurf == 0)
				pSurfSeries->SetHorizontal(true);
			else
				pSurfSeries->SetHorizontal(false);
		}
		break;
	}

	pSeries->SetName(Name);
	pSeries->SetColor(Color);

	int NumberPoints = PropertiesDlg.m_iPointsNumber;
	double* XValues = new double[NumberPoints];
	double* YValues = new double[NumberPoints];
	float Step = (PropertiesDlg.m_fMaxXValue - PropertiesDlg.m_fMinXValue)/(NumberPoints - 1);
	float XStart = PropertiesDlg.m_fMinXValue;
	switch (PropertiesDlg.m_iDataType)
	{
	case 0:
		{
			float Slope = PropertiesDlg.m_fLineSlope;
			float Offset = PropertiesDlg.m_fLineOffset;

			for (int i=0;i<NumberPoints;i++)
			{
				XValues[i] = XStart + i * Step;
				YValues[i] = XValues[i] * Slope + Offset;
			}
			pSeries->SetPoints(XValues,YValues,NumberPoints);

		}
		break;

	case 1:
		{
			float Amplitude = PropertiesDlg.m_fSineAmplitude;
			float Period = PropertiesDlg.m_fSinePeriod;

			for (int i=0;i<NumberPoints;i++)
			{
				XValues[i] = XStart + i * Step;
				YValues[i] = Amplitude * (float)sin( 2 * 3.141592 * XValues[i]/Period );
			}
			pSeries->SetPoints(XValues,YValues,NumberPoints);
		}
		break;

	case 2:
		{
			int Min = PropertiesDlg.m_iRandMinVal;
			int Max = PropertiesDlg.m_iRandMaxVal;
			srand((unsigned int)time(NULL));
			for (int i=0;i<NumberPoints;i++)
			{
				XValues[i] = XStart + i * Step;
				YValues[i] = Min + (rand()%(Max-Min));
			}
			pSeries->SetPoints(XValues,YValues,NumberPoints);
		}
		break;
	}
	
	delete[] XValues;
	delete[] YValues;
	m_ChartCtrl.RefreshCtrl();
	int index = m_SeriesList.AddString(Name.c_str());
	m_SeriesList.SetItemData(index, pSeries->GetSerieId());
}

void CChartDemoDlg::OnLegendVisible() 
{
	if (m_LegendVisBtn.GetCheck() == 1)
		m_ChartCtrl.GetLegend()->SetVisible(true);
	else
		m_ChartCtrl.GetLegend()->SetVisible(false);
	m_ChartCtrl.RefreshCtrl();
}

void CChartDemoDlg::OnBottomAxisRadio() 
{
	CChartAxis* pAxis = m_ChartCtrl.GetBottomAxis();
	if (pAxis->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(0);
	if (pAxis->GetGrid()->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(0);
	if (pAxis->IsAutomatic())
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(0);
	if (pAxis->IsInverted())
		((CButton*)GetDlgItem(IDC_AXISINVERTED_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISINVERTED_CHECK))->SetCheck(0);
	if (pAxis->ScrollBarEnabled())
		((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->SetCheck(0);

	TChartString AxisLabel = pAxis->GetLabel()->GetText();
	GetDlgItem(IDC_AXISLABEL_EDIT)->SetWindowText(AxisLabel.c_str());

	double Min=0, Max=0;
	CString strBuff;
	pAxis->GetMinMax(Min,Max);
	strBuff.Format(_T("%.2f"),Min);
	GetDlgItem(IDC_AXISMINVAL_EDIT)->SetWindowText(strBuff);
	strBuff.Format(_T("%.2f"),Max);
	GetDlgItem(IDC_AXISMAXVAL_EDIT)->SetWindowText(strBuff);
}

void CChartDemoDlg::OnLeftAxisRadio() 
{
	CChartAxis* pAxis = m_ChartCtrl.GetLeftAxis();
	if (pAxis->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(0);
	if (pAxis->GetGrid()->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(0);
	if (pAxis->IsAutomatic())
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(0);
	if (pAxis->IsInverted())
		((CButton*)GetDlgItem(IDC_AXISINVERTED_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISINVERTED_CHECK))->SetCheck(0);
	if (pAxis->ScrollBarEnabled())
		((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->SetCheck(0);

	TChartString AxisLabel = pAxis->GetLabel()->GetText();
	GetDlgItem(IDC_AXISLABEL_EDIT)->SetWindowText(AxisLabel.c_str());

	double Min=0, Max=0;
	CString strBuff;
	pAxis->GetMinMax(Min,Max);
	strBuff.Format(_T("%.2f"),Min);
	GetDlgItem(IDC_AXISMINVAL_EDIT)->SetWindowText(strBuff);
	strBuff.Format(_T("%.2f"),Max);
	GetDlgItem(IDC_AXISMAXVAL_EDIT)->SetWindowText(strBuff);	
}

void CChartDemoDlg::OnRightAxisRadio() 
{
	CChartAxis* pAxis = m_ChartCtrl.GetRightAxis();
	if (pAxis->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(0);
	if (pAxis->GetGrid()->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(0);
	if (pAxis->IsAutomatic())
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(0);
	if (pAxis->IsInverted())
		((CButton*)GetDlgItem(IDC_AXISINVERTED_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISINVERTED_CHECK))->SetCheck(0);
	if (pAxis->ScrollBarEnabled())
		((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->SetCheck(0);

	TChartString AxisLabel = pAxis->GetLabel()->GetText();
	GetDlgItem(IDC_AXISLABEL_EDIT)->SetWindowText(AxisLabel.c_str());

	double Min=0, Max=0;
	CString strBuff;
	pAxis->GetMinMax(Min,Max);
	strBuff.Format(_T("%.2f"),Min);
	GetDlgItem(IDC_AXISMINVAL_EDIT)->SetWindowText(strBuff);
	strBuff.Format(_T("%.2f"),Max);
	GetDlgItem(IDC_AXISMAXVAL_EDIT)->SetWindowText(strBuff);	
}

void CChartDemoDlg::OnTopAxisRadio() 
{
	CChartAxis* pAxis = m_ChartCtrl.GetTopAxis();
	if (pAxis->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(0);
	if (pAxis->GetGrid()->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(0);
	if (pAxis->IsAutomatic())
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(0);
	if (pAxis->IsInverted())
		((CButton*)GetDlgItem(IDC_AXISINVERTED_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISINVERTED_CHECK))->SetCheck(0);
	if (pAxis->ScrollBarEnabled())
		((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->SetCheck(0);

	TChartString AxisLabel = pAxis->GetLabel()->GetText();
	GetDlgItem(IDC_AXISLABEL_EDIT)->SetWindowText(AxisLabel.c_str());

	double Min=0, Max=0;
	CString strBuff;
	pAxis->GetMinMax(Min,Max);
	strBuff.Format(_T("%.2f"),Min);
	GetDlgItem(IDC_AXISMINVAL_EDIT)->SetWindowText(strBuff);
	strBuff.Format(_T("%.2f"),Max);
	GetDlgItem(IDC_AXISMAXVAL_EDIT)->SetWindowText(strBuff);	
}

void CChartDemoDlg::OnAxisAutomaticCheck() 
{
	CChartAxis* pAxis = GetSelectedAxis();
	if ( ((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->GetCheck() == 1)
		pAxis->SetAutomatic(true);
	else
	{
		TCHAR szBuffer[255];
		double MinVal=0, MaxVal=0;
		m_AxisMinValEdit.GetWindowText(szBuffer,254);
//		MinVal = _tstof(szBuffer);
		MinVal = _tcstod(szBuffer, NULL);
		m_AxisMaxValEdit.GetWindowText(szBuffer,254);
//		MaxVal = _tstof(szBuffer);
		MaxVal = _tcstod(szBuffer, NULL);

		if (MinVal > MaxVal)
		{
			MessageBox(_T("MinVal > MaxVal"),_T("Error"),MB_OK);
			((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
			return;
		}
		pAxis->SetAutomatic(false);
		pAxis->SetMinMax(MinVal,MaxVal);
	}
	m_ChartCtrl.RefreshCtrl();
}

void CChartDemoDlg::OnAxisGridVisCheck() 
{
	CChartAxis* pAxis = GetSelectedAxis();
	if ( ((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->GetCheck() == 1)
		pAxis->GetGrid()->SetVisible(true);
	else
		pAxis->GetGrid()->SetVisible(false);
	m_ChartCtrl.RefreshCtrl();
}

void CChartDemoDlg::OnAxisVisibleCheck() 
{
	CChartAxis* pAxis = GetSelectedAxis();
	if ( ((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->GetCheck() == 1)
		pAxis->SetVisible(true);
	else
		pAxis->SetVisible(false);	
	m_ChartCtrl.RefreshCtrl();
}

void CChartDemoDlg::OnAxisInvertedCheck() 
{
	CChartAxis* pAxis = GetSelectedAxis();
	if ( ((CButton*)GetDlgItem(IDC_AXISINVERTED_CHECK))->GetCheck() == 1)
		pAxis->SetInverted(true);
	else
		pAxis->SetInverted(false);	
	m_ChartCtrl.RefreshCtrl();	
}

void CChartDemoDlg::OnAxisScrollBarCheck()
{
	CChartAxis* pAxis = GetSelectedAxis();
	bool bShow = ((CButton*)GetDlgItem(IDC_AXISSCROLLBAR_CHECK))->GetCheck() == 1;
	pAxis->EnableScrollBar(bShow);
}

CChartAxis* CChartDemoDlg::GetSelectedAxis()
{
	if ( ((CButton*)GetDlgItem(IDC_LEFTAXIS_RADIO))->GetCheck() == 1)
		return m_ChartCtrl.GetLeftAxis();
	if ( ((CButton*)GetDlgItem(IDC_BOTTOMAXIS_RADIO))->GetCheck() == 1)
		return m_ChartCtrl.GetBottomAxis();
	if ( ((CButton*)GetDlgItem(IDC_RIGHTAXIS_RADIO))->GetCheck() == 1)
		return m_ChartCtrl.GetRightAxis();
	if ( ((CButton*)GetDlgItem(IDC_TOPAXIS_RADIO))->GetCheck() == 1)
		return m_ChartCtrl.GetTopAxis();

	return NULL;
}

LONG CChartDemoDlg::OnChangeBckCol(UINT , LONG )
{
	COLORREF BackColor = m_BackgndColSel.GetColour();
	m_ChartCtrl.SetBackColor(BackColor);
	m_ChartCtrl.RefreshCtrl();
	return TRUE;
}

void CChartDemoDlg::OnChangeAxisMax() 
{
	CChartAxis* pAxis = GetSelectedAxis();
	TCHAR szBuffer[255];
	double MinVal=0, MaxVal=0;
	m_AxisMinValEdit.GetWindowText(szBuffer,254);
//	MinVal = _tstof(szBuffer);
	MinVal = _tcstod(szBuffer, NULL);
	m_AxisMaxValEdit.GetWindowText(szBuffer,254);
//	MaxVal = _tstof(szBuffer);
	MaxVal = _tcstod(szBuffer, NULL);

	if (MinVal > MaxVal)
	{
		MessageBox(_T("MinVal > MaxVal"),_T("Error"),MB_OK);
		return;
	}
	pAxis->SetMinMax(MinVal,MaxVal);
	
	m_ChartCtrl.RefreshCtrl();
	
}

void CChartDemoDlg::OnChangeAxisMin() 
{
	CChartAxis* pAxis = GetSelectedAxis();
	TCHAR szBuffer[255];
	double MinVal=0, MaxVal=0;
	m_AxisMinValEdit.GetWindowText(szBuffer,254);
//	MinVal = _tstof(szBuffer);
	MinVal = _tcstod(szBuffer, NULL);
	m_AxisMaxValEdit.GetWindowText(szBuffer,254);
//	MaxVal = _tstof(szBuffer);
	MaxVal = _tcstod(szBuffer, NULL);

	if (MinVal > MaxVal)
	{
		MessageBox(_T("MinVal > MaxVal"),_T("Error"),MB_OK);
		return;
	}
	pAxis->SetMinMax(MinVal,MaxVal);
	
	m_ChartCtrl.RefreshCtrl();	
}

void CChartDemoDlg::OnChangeAxisLabel() 
{
	CChartAxis* pAxis = GetSelectedAxis();
	TCHAR szBuffer[255];
	GetDlgItem(IDC_AXISLABEL_EDIT)->GetWindowText(szBuffer,254);
	pAxis->GetLabel()->SetText(szBuffer);
	m_ChartCtrl.RefreshCtrl();	
	
}

void CChartDemoDlg::OnDeleteSeries() 
{
	int Index = m_SeriesList.GetCurSel();
	if (Index == -1)
		return;
	unsigned seriesId = m_SeriesList.GetItemData(Index);

	m_ChartCtrl.RemoveSerie(seriesId);
	m_SeriesList.DeleteString(Index);
}

void CChartDemoDlg::OnChangeTitle() 
{
	int Count = m_TitlesEdit.GetLineCount();
	CChartTitle* pTitle = m_ChartCtrl.GetTitle();
	pTitle->RemoveAll();

	TCHAR szBuff[255];
	for (int i=0;i<Count;i++)
	{
		int Size = m_TitlesEdit.GetLine(i,szBuff);
		szBuff[Size] = '\0';
		pTitle->AddString(szBuff);
	}
		
	m_ChartCtrl.RefreshCtrl();	
}

void CChartDemoDlg::OnPanCheck() 
{
	if ( ((CButton*)GetDlgItem(IDC_PAN_CHECK))->GetCheck() == 1)
		m_ChartCtrl.SetPanEnabled(true);
	else
		m_ChartCtrl.SetPanEnabled(false);	
	
}

void CChartDemoDlg::OnZoomCheck() 
{
	if ( ((CButton*)GetDlgItem(IDC_ZOOM_CHECK))->GetCheck() == 1)
		m_ChartCtrl.SetZoomEnabled(true);
	else
		m_ChartCtrl.SetZoomEnabled(false);	
}