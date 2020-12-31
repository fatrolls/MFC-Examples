// SeriesPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChartDemo.h"
#include "SeriesPropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeriesPropDlg dialog


CSeriesPropDlg::CSeriesPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeriesPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeriesPropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iHorizAxis = m_iVertAxis = 0;
	m_iSeriesType = 0;
	m_SeriesColour = 0;
	m_iDataType = 0;
	m_fMaxXValue = m_fMinXValue = 0.0;
	m_iPointsNumber = 0;

	m_iRandMinVal = m_iRandMaxVal = 0;
	m_fSineAmplitude = m_fSinePeriod = 0;
	m_fLineSlope = m_fLineOffset = 0;
}


void CSeriesPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeriesPropDlg)
	DDX_Control(pDX, IDC_VERTICALAXIS_COMBO, m_VertAxisCombo);
	DDX_Control(pDX, IDC_HORIZONTALAXIS_COMBO, m_HorizAxisCombo);
	DDX_Control(pDX, IDC_SERIESCOLOUR_BTN, m_ColourSelect);
	DDX_Control(pDX, IDC_SERIESTYPE_COMBO, m_SeriesTypeCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSeriesPropDlg, CDialog)
	//{{AFX_MSG_MAP(CSeriesPropDlg)
	ON_BN_CLICKED(IDC_LINEDATA_RADIO, OnSelectLineData)
	ON_BN_CLICKED(IDC_RANDOMDATA_RADIO, OnSelectRandomData)
	ON_BN_CLICKED(IDC_SINEDATA_RADIO, OnSelectSineData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeriesPropDlg message handlers

void CSeriesPropDlg::OnOK() 
{
	TCHAR szName[255];
	GetDlgItem(IDC_SERIESNAME_EDIT)->GetWindowText(szName,254);
	m_strSeriesName = szName;

	if (_tcscmp(szName,_T("")) == 0)
	{
		MessageBox(_T("You must supply a name"),_T("Error"));
		return;
	}

	m_iSeriesType = m_SeriesTypeCombo.GetCurSel();
	m_SeriesColour = m_ColourSelect.GetColour();
	
	TCHAR szBuff[255];
	GetDlgItem(IDC_MAXXVALUE_EDIT)->GetWindowText(szBuff,254); 
//	m_fMaxXValue = (float)_tstof(szBuff);
	m_fMaxXValue = (float)_tcstod(szBuff, NULL);
	GetDlgItem(IDC_MINXVALUE_EDIT)->GetWindowText(szBuff,254); 
//	m_fMinXValue = (float)_tstof(szBuff);
	m_fMinXValue = (float)_tcstod(szBuff, NULL);
	if (m_fMinXValue > m_fMaxXValue)
	{
		MessageBox(_T("Max X value should be > Min X value"));
		return;
	}

	m_iHorizAxis = m_HorizAxisCombo.GetCurSel();
	m_iVertAxis = m_VertAxisCombo.GetCurSel();

	GetDlgItem(IDC_POINTSNUMBER_EDIT)->GetWindowText(szBuff,254); 
#ifdef UNICODE 
	m_iPointsNumber = _wtoi(szBuff);
#else
	m_iPointsNumber = atoi(szBuff);
#endif
	if (m_iPointsNumber < 2)
	{
		MessageBox(_T("Number of points should be > 2"));
		return;
	}

	if ( ((CButton*)GetDlgItem(IDC_LINEDATA_RADIO))->GetCheck() == 1)
	{
		m_iDataType = 0;
	
		GetDlgItem(IDC_DATAPARAM1_EDIT)->GetWindowText(szBuff,254); 
//		m_fLineSlope = (float)_tstof(szBuff);
		m_fLineSlope = (float)_tcstod(szBuff, NULL);
		GetDlgItem(IDC_DATAPARAM2_EDIT)->GetWindowText(szBuff,254); 
//		m_fLineOffset = (float)_tstof(szBuff);
		m_fLineOffset = (float)_tcstod(szBuff, NULL);
	}
	else if ( ((CButton*)GetDlgItem(IDC_SINEDATA_RADIO))->GetCheck() == 1)
	{
		m_iDataType = 1;
	
		GetDlgItem(IDC_DATAPARAM1_EDIT)->GetWindowText(szBuff,254); 
//		m_fSineAmplitude = (float)_tstof(szBuff);
		m_fSineAmplitude = (float)_tcstod(szBuff, NULL);
		GetDlgItem(IDC_DATAPARAM2_EDIT)->GetWindowText(szBuff,254); 
//		m_fSinePeriod = (float)_tstof(szBuff);
		m_fSinePeriod = (float)_tcstod(szBuff, NULL);
		if (m_fSinePeriod == 0)
		{
			MessageBox(_T("Sine period cannot be 0"),_T("Error"));
			return;
		}
	}
	else
	{
		m_iDataType = 2;
	
#ifdef UNICODE 
	GetDlgItem(IDC_DATAPARAM1_EDIT)->GetWindowText(szBuff,254); 
	m_iRandMinVal = _wtoi(szBuff);
	GetDlgItem(IDC_DATAPARAM2_EDIT)->GetWindowText(szBuff,254); 
	m_iRandMaxVal = _wtoi(szBuff);
#else
	GetDlgItem(IDC_DATAPARAM1_EDIT)->GetWindowText(szBuff,254); 
	m_iRandMinVal = atoi(szBuff);
	GetDlgItem(IDC_DATAPARAM2_EDIT)->GetWindowText(szBuff,254); 
	m_iRandMaxVal = atoi(szBuff);
#endif

		if (m_iRandMaxVal < m_iRandMinVal)
		{
			MessageBox(_T("Max random value should be > Min random value"));
			return;
		}
	}

	CDialog::OnOK();
}

BOOL CSeriesPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SeriesTypeCombo.SetCurSel(0);
	m_HorizAxisCombo.SetCurSel(0);
	m_VertAxisCombo.SetCurSel(0);
	((CButton*)GetDlgItem(IDC_LINEDATA_RADIO))->SetCheck(1);

	GetDlgItem(IDC_MINXVALUE_EDIT)->SetWindowText(_T("0.0")); 
	GetDlgItem(IDC_MAXXVALUE_EDIT)->SetWindowText(_T("100.0")); 

	GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("1.0"));
	GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("0.0"));
	GetDlgItem(IDC_POINTSNUMBER_EDIT)->SetWindowText(_T("100")); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSeriesPropDlg::OnSelectLineData() 
{
	GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Line Slope:"));
	GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Line Offset:"));
	GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("1.0"));
	GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("0.0"));
}

void CSeriesPropDlg::OnSelectRandomData() 
{
	
	GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Min Y value:"));
	GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Max Y value:"));
	GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("0"));
	GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("100"));
}

void CSeriesPropDlg::OnSelectSineData() 
{
	GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Sine Amplitude:"));
	GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Sine Period:"));
	GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("100.0"));
	GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("10.0"));
}
