// PhysicalTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "PhysicalTest.h"
#include "PhysicalTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPhysicalTestDlg dialog

CPhysicalTestDlg::CPhysicalTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhysicalTestDlg::IDD, pParent)
	{
	//{{AFX_DATA_INIT(CPhysicalTestDlg)
	m_dConvertedAngle = 0.0;
	m_dConvertedLength = 0.0;
	m_dConvertedTemp = 0.0;
	m_dConvertedTime = 0.0;
	//}}AFX_DATA_INIT
	m_dConvAngle = 0.0;
	m_dConvLength = 0.0;
	m_dConvTemp = 0.0;
	m_dConvTime = 0.0;
	m_nNeededConvAngle = 0;
	m_nNeededConvLength = 0;
	m_nNeededConvTemp = 0;
	m_nNeededConvTime = 0;
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	}

void CPhysicalTestDlg::DoDataExchange(CDataExchange* pDX)
	{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhysicalTestDlg)
	DDX_Control(pDX, IDC_TIME_LIST, m_wndTimeList);
	DDX_Control(pDX, IDC_TEMPERATURE_LIST, m_wndTempList);
	DDX_Control(pDX, IDC_LENGTH_LIST, m_wndLengthList);
	DDX_Control(pDX, IDC_ANGLE_LIST, m_wndAngleList);
	DDX_Control(pDX, IDC_TEMPERATURE, m_wndTemp);
	DDX_Control(pDX, IDC_TIME, m_wndTime);
	DDX_Control(pDX, IDC_LENGTH, m_wndLength);
	DDX_Control(pDX, IDC_ANGLE, m_wndAngle);
	DDX_Text(pDX, IDC_CONVERTED_ANGLE, m_dConvertedAngle);
	DDX_Text(pDX, IDC_CONVERTED_LENGTH, m_dConvertedLength);
	DDX_Text(pDX, IDC_CONVERTED_TEMPERATURE, m_dConvertedTemp);
	DDX_Text(pDX, IDC_CONVERTED_TIME, m_dConvertedTime);
	//}}AFX_DATA_MAP
	// We only want to retrieve data from the control (not put new data in it)
	if (pDX->m_bSaveAndValidate)
		{
		DDX_OXAngleEdit(pDX, IDC_ANGLE, m_dConvAngle, m_nNeededConvAngle);
		DDX_OXLengthEdit(pDX, IDC_LENGTH, m_dConvLength, m_nNeededConvLength);
		DDX_OXTempEdit(pDX, IDC_TEMPERATURE, m_dConvTemp, m_nNeededConvTemp);
		DDX_OXTimeEdit(pDX, IDC_TIME, m_dConvTime, m_nNeededConvTime);
		}
	}

BEGIN_MESSAGE_MAP(CPhysicalTestDlg, CDialog)
	//{{AFX_MSG_MAP(CPhysicalTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONVERT_ANGLE, OnConvertAngle)
	ON_BN_CLICKED(IDC_CONVERT_LENGTH, OnConvertLength)
	ON_BN_CLICKED(IDC_CONVERT_TEMPERATURE, OnConvertTemperature)
	ON_BN_CLICKED(IDC_CONVERT_TIME, OnConvertTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhysicalTestDlg message handlers

BOOL CPhysicalTestDlg::OnInitDialog()
	{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
		{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize the combo boxes
	int nUnitIndex;
	for (nUnitIndex = 0; nUnitIndex < m_wndLength.GetNumberOfUnits(); nUnitIndex++)
		m_wndLengthList.AddString(m_wndLength.GetUnitNames()[nUnitIndex]);
	m_wndLengthList.SetCurSel(m_wndLength.GetDefaultUnit());

	for (nUnitIndex = 0; nUnitIndex < m_wndTime.GetNumberOfUnits(); nUnitIndex++)
		m_wndTimeList.AddString(m_wndTime.GetUnitNames()[nUnitIndex]);
	m_wndTimeList.SetCurSel(m_wndTime.GetDefaultUnit());

	for (nUnitIndex = 0; nUnitIndex < m_wndTemp.GetNumberOfUnits(); nUnitIndex++)
		m_wndTempList.AddString(m_wndTemp.GetUnitNames()[nUnitIndex]);
	m_wndTempList.SetCurSel(m_wndTemp.GetDefaultUnit());

	for (nUnitIndex = 0; nUnitIndex < m_wndAngle.GetNumberOfUnits(); nUnitIndex++)
		m_wndAngleList.AddString(m_wndAngle.GetUnitNames()[nUnitIndex]);
	m_wndAngleList.SetCurSel(m_wndAngle.GetDefaultUnit());	

	//The below lines added to work around a bug in the COXDropEdit
	//implementatioin which causes some controls to be partially hidden
	//when themes are enabled
	m_wndTime.ShowWindow(SW_HIDE);
	m_wndTime.ShowWindow(SW_SHOW);
	m_wndTemp.ShowWindow(SW_HIDE);
	m_wndTemp.ShowWindow(SW_SHOW);
	m_wndLength.ShowWindow(SW_HIDE);
	m_wndLength.ShowWindow(SW_SHOW);
	m_wndAngle.ShowWindow(SW_HIDE);
	m_wndAngle.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPhysicalTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
	{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
		{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
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

void CPhysicalTestDlg::OnPaint() 
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
HCURSOR CPhysicalTestDlg::OnQueryDragIcon()
	{
	return (HCURSOR) m_hIcon;
	}

void CPhysicalTestDlg::OnConvertAngle() 
	{
	m_nNeededConvAngle = m_wndAngleList.GetCurSel();
	if (UpdateData(TRUE))
		{
		m_dConvertedAngle = m_dConvAngle;
		UpdateData(FALSE);
		}
	}

void CPhysicalTestDlg::OnConvertLength() 
	{
	m_nNeededConvLength = m_wndLengthList.GetCurSel();
	if (UpdateData(TRUE))
		{
		m_dConvertedLength = m_dConvLength;
		UpdateData(FALSE);
		}
	}

void CPhysicalTestDlg::OnConvertTemperature() 
	{
	m_nNeededConvTemp = m_wndTempList.GetCurSel();
	if (UpdateData(TRUE))
		{
		m_dConvertedTemp = m_dConvTemp;
		UpdateData(FALSE);
		}
	}

void CPhysicalTestDlg::OnConvertTime() 
	{
	m_nNeededConvTime = m_wndTimeList.GetCurSel();
	if (UpdateData(TRUE))
		{
		m_dConvertedTime = m_dConvTime;
		UpdateData(FALSE);
		}
	}
