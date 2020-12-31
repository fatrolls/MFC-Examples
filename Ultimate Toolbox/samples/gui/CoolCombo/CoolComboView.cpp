// CoolComboView.cpp : implementation of the CCoolComboView class
//

#include "stdafx.h"
#include "CoolCombo.h"

#include "CoolComboDoc.h"
#include "CoolComboView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoolComboView

IMPLEMENT_DYNCREATE(CCoolComboView, CFormView)

BEGIN_MESSAGE_MAP(CCoolComboView, CFormView)
	//{{AFX_MSG_MAP(CCoolComboView)
	ON_BN_CLICKED(IDC_CHECK_COOL, OnCheckCool)
	ON_BN_CLICKED(IDC_CHECK_DISABLE, OnCheckDisable)
	ON_BN_CLICKED(IDC_CHECK_DISABLEINTOOLBAR, OnCheckDisableintoolbar)
	ON_EN_CHANGE(IDC_EDIT_TOOLTIPTEXT, OnChangeEditTooltiptext)
	ON_BN_CLICKED(IDC_RADIO_DROPDOWN, OnRadioDropdown)
	ON_BN_CLICKED(IDC_RADIO_DROPDOWNLIST, OnRadioDropdownlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoolComboView construction/destruction

CCoolComboView::CCoolComboView()
	: CFormView(CCoolComboView::IDD)
{
	//{{AFX_DATA_INIT(CCoolComboView)
	m_bCoolState = FALSE;
	m_bDisabled = FALSE;
	m_bDisabledInToolbar = FALSE;
	m_sTooltipText = _T("");
	m_nComboStyle = -1;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CCoolComboView::~CCoolComboView()
{
}

void CCoolComboView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoolComboView)
	DDX_Control(pDX, IDC_SEPARATOR, m_separator);
	DDX_Control(pDX, IDC_HEADING, m_heading);
	DDX_Control(pDX, IDC_COMBO, m_combo);
	DDX_Check(pDX, IDC_CHECK_COOL, m_bCoolState);
	DDX_Check(pDX, IDC_CHECK_DISABLE, m_bDisabled);
	DDX_Check(pDX, IDC_CHECK_DISABLEINTOOLBAR, m_bDisabledInToolbar);
	DDX_Text(pDX, IDC_EDIT_TOOLTIPTEXT, m_sTooltipText);
	DDX_Radio(pDX, IDC_RADIO_DROPDOWN, m_nComboStyle);
	//}}AFX_DATA_MAP
}

BOOL CCoolComboView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CCoolComboView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CMainFrame* pFrame=(CMainFrame*)GetParentFrame();
	ASSERT(pFrame!=NULL);
	pFrame->RecalcLayout();
	ResizeParentToFit();

	PopulateCombo();

	m_heading.SetTextColor(::GetSysColor(COLOR_WINDOW));

	m_sTooltipText=_T("Tooltip for Cool ComboBox");

	m_bCoolState=m_combo.IsInCoolState();
	m_bDisabled=!m_combo.IsWindowEnabled();
	m_bDisabledInToolbar=!pFrame->m_wndToolBar.m_combo.IsWindowEnabled();
	VERIFY(m_combo.SetTooltipText(m_sTooltipText));
	m_nComboStyle=m_combo.GetStyle() & CBS_DROPDOWN ? 0 : 1;

	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CCoolComboView diagnostics

#ifdef _DEBUG
void CCoolComboView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCoolComboView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCoolComboDoc* CCoolComboView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCoolComboDoc)));
	return (CCoolComboDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCoolComboView message handlers

void CCoolComboView::OnCheckCool() 
{
	// TODO: Add your control notification handler code here

	UpdateData();
	m_combo.SetCoolState(m_bCoolState);
}

void CCoolComboView::OnCheckDisable() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	m_combo.EnableWindow(!m_bDisabled);
}

void CCoolComboView::OnCheckDisableintoolbar() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData();
	CMainFrame* pFrame=(CMainFrame*)GetParentFrame();
	ASSERT(pFrame!=NULL);
	pFrame->m_wndToolBar.m_combo.EnableWindow(!m_bDisabledInToolbar);
}

void CCoolComboView::OnChangeEditTooltiptext() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
	UpdateData();
	VERIFY(m_combo.SetTooltipText(m_sTooltipText));
}

void CCoolComboView::OnRadioDropdown() 
{
	// TODO: Add your control notification handler code here
	RecreateCombo(CBS_DROPDOWN,CBS_DROPDOWNLIST);
}

void CCoolComboView::OnRadioDropdownlist() 
{
	// TODO: Add your control notification handler code here
	RecreateCombo(CBS_DROPDOWNLIST,CBS_DROPDOWN);
}


void CCoolComboView::RecreateCombo(const DWORD dwAddStyle, const DWORD dwRemoveStyle) 
{
	DWORD dwStyle=m_combo.GetStyle();
	dwStyle&=~dwRemoveStyle;
	dwStyle|=dwAddStyle;
	CRect rect;
	m_combo.GetWindowRect(rect);
	ScreenToClient(rect);

	CRect rectListBox;
	m_combo.GetDroppedControlRect(rectListBox);
	rect.bottom=rect.top+rectListBox.Height();

	m_combo.DestroyWindow();
	m_combo.Create(dwStyle,rect,this,IDC_COMBO);


	// Restore the font
	m_combo.SetFont(GetFont());

	VERIFY(m_combo.SetTooltipText(m_sTooltipText));

	PopulateCombo();
}


void CCoolComboView::PopulateCombo() 
{
	for(int nIndex=0; nIndex<10; nIndex++)
	{
		CString sText;
		sText.Format(_T("Cool combobox item %d"),nIndex);
		m_combo.AddString(sText);
	}
	m_combo.SendMessage(CB_SETCURSEL,0);
}
