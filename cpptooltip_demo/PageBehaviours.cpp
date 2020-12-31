// PageBehaviours.cpp : implementation file
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "PageBehaviours.h"
#include "CustomizeTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageBehaviours property page

IMPLEMENT_DYNCREATE(CPageBehaviours, CPropertyPage)

CPageBehaviours::CPageBehaviours() : CPropertyPage(CPageBehaviours::IDD)
{
	//{{AFX_DATA_INIT(CPageBehaviours)
	m_multiple_show = FALSE;
	m_hide_by_left = FALSE;
	m_nohide_over = FALSE;
	m_nohide_by_timer = FALSE;
	m_tracking_mouse = FALSE;
	m_show_time = 0;
	m_hide_time = 0;
	m_fade_in = 0;
	m_fade_out = 0;
	m_debug_mode = FALSE;
	m_animation = 100;
	//}}AFX_DATA_INIT
}

CPageBehaviours::~CPageBehaviours()
{
}

void CPageBehaviours::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageBehaviours)
	DDX_Check(pDX, IDC_CHECK1, m_multiple_show);
	DDX_Check(pDX, IDC_CHECK2, m_hide_by_left);
	DDX_Check(pDX, IDC_CHECK3, m_nohide_over);
	DDX_Check(pDX, IDC_CHECK4, m_nohide_by_timer);
	DDX_Check(pDX, IDC_CHECK5, m_tracking_mouse);
	DDX_Text(pDX, IDC_EDIT1, m_show_time);
	DDX_Text(pDX, IDC_EDIT2, m_hide_time);
	DDX_Text(pDX, IDC_EDIT9, m_fade_in);
	DDX_Text(pDX, IDC_EDIT10, m_fade_out);
	DDX_Check(pDX, IDC_DEBUG_MODE, m_debug_mode);
	DDX_Text(pDX, IDC_EDIT11, m_animation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageBehaviours, CPropertyPage)
	//{{AFX_MSG_MAP(CPageBehaviours)
	ON_BN_CLICKED(IDC_CHECK1, OnChangeBehaviour)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeTimers)
	ON_BN_CLICKED(IDC_DEBUG_MODE, OnDebugMode)
	ON_BN_CLICKED(IDC_CHECK2, OnChangeBehaviour)
	ON_BN_CLICKED(IDC_CHECK3, OnChangeBehaviour)
	ON_BN_CLICKED(IDC_CHECK4, OnChangeBehaviour)
	ON_BN_CLICKED(IDC_CHECK5, OnChangeBehaviour)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeTimers)
	ON_EN_CHANGE(IDC_EDIT9, OnChangeTimers)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeTimers)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeAniStep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageBehaviours message handlers

BOOL CPageBehaviours::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	//Get default behaviour
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	DWORD dwBehaviour = pDialog->m_general.m_tooltip.GetBehaviour();
	m_multiple_show = (dwBehaviour & PPTOOLTIP_MULTIPLE_SHOW) ? TRUE : FALSE;
	m_hide_by_left = (dwBehaviour & PPTOOLTIP_CLOSE_LEAVEWND) ? TRUE : FALSE;
	m_nohide_over = (dwBehaviour & PPTOOLTIP_NOCLOSE_OVER) ? TRUE : FALSE;
	m_nohide_by_timer = (dwBehaviour & PPTOOLTIP_DISABLE_AUTOPOP) ? TRUE : FALSE;
	m_tracking_mouse = (dwBehaviour & PPTOOLTIP_TRACKING_MOUSE) ? TRUE : FALSE;

	//Get default time
	m_show_time = pDialog->m_general.m_tooltip.GetDelayTime(PPTOOLTIP_TIME_INITIAL);
	m_hide_time = pDialog->m_general.m_tooltip.GetDelayTime(PPTOOLTIP_TIME_AUTOPOP);
	m_fade_in = pDialog->m_general.m_tooltip.GetDelayTime(PPTOOLTIP_TIME_FADEIN);
	m_fade_out = pDialog->m_general.m_tooltip.GetDelayTime(PPTOOLTIP_TIME_FADEOUT);

	UpdateData(FALSE);
	OnChangeBehaviour();
	OnChangeTimers();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageBehaviours::OnChangeBehaviour() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	DWORD dwBehaviour = 0;
	if (m_multiple_show) dwBehaviour |= PPTOOLTIP_MULTIPLE_SHOW;
	if (m_hide_by_left) dwBehaviour |= PPTOOLTIP_CLOSE_LEAVEWND;
	if (m_nohide_over) dwBehaviour |= PPTOOLTIP_NOCLOSE_OVER;
	if (m_nohide_by_timer) dwBehaviour |= PPTOOLTIP_DISABLE_AUTOPOP;
	if (m_tracking_mouse) dwBehaviour |= PPTOOLTIP_TRACKING_MOUSE;
	pDialog->m_general.m_tooltip.SetBehaviour(dwBehaviour);
}

void CPageBehaviours::OnChangeTimers() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetDelayTime(PPTOOLTIP_TIME_INITIAL, m_show_time);
	pDialog->m_general.m_tooltip.SetDelayTime(PPTOOLTIP_TIME_AUTOPOP, m_hide_time);
	pDialog->m_general.m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEIN, m_fade_in);
	pDialog->m_general.m_tooltip.SetDelayTime(PPTOOLTIP_TIME_FADEOUT, m_fade_out);
}

void CPageBehaviours::OnDebugMode() 
{
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetDebugMode(m_debug_mode);
}

void CPageBehaviours::OnChangeAniStep() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	CCustomizeTooltip * pDialog = GetTooltipWnd;
	pDialog->m_general.m_tooltip.SetDelayTime(PPTOOLTIP_TIME_ANIMATION, m_animation);
}
