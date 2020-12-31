// MaskedEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExtendedEditControls.h"
#include "MaskedEditDlg.h"  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__ ;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditDlg dialog

CMaskedEditDlg::CMaskedEditDlg() : CPropertyPage(CMaskedEditDlg::IDD)/*, m_editMasked()*/
{
	//{{AFX_DATA_INIT(CMaskedEditDlg)
	m_csPromptChar = _T("");
	m_bAutoTab = FALSE;
	//}}AFX_DATA_INIT
}

void CMaskedEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX) ;
	//{{AFX_DATA_MAP(CMaskedEditDlg)
	DDX_Control(pDX, IDC_STATIC_BOTTOM, m_sepBottom);
	DDX_Control (pDX, IDC_EDIT_TEST  , m_editMasked  ) ;
	DDX_Control (pDX, IDC_COMBO_MASKS, m_comboMasks  ) ;
	DDX_Text    (pDX, IDC_EDIT_PROMPT, m_csPromptChar) ;
	DDV_MaxChars(pDX, m_csPromptChar, 1) ;
	DDX_Check(pDX, IDC_CHECK_AUTOTAB, m_bAutoTab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMaskedEditDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CMaskedEditDlg)
	ON_CBN_SELENDOK  (IDC_COMBO_MASKS, OnSelendokMasks  )
	ON_CBN_EDITCHANGE(IDC_COMBO_MASKS, OnEditchangeMasks)
	ON_EN_CHANGE(IDC_EDIT_PROMPT, OnChangeEditPrompt)
	ON_BN_CLICKED(IDC_BUTTON_EMPTY, OnButtonEmpty)
	ON_BN_CLICKED(IDC_CHECK_AUTOTAB, OnCheckAutotab)
	//}}AFX_MSG_MAP
	ON_NOTIFY(OXMEN_VALIDATE,IDC_EDIT_TEST,OnValidateEditTest)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditDlg message handlers

BOOL CMaskedEditDlg::OnInitDialog()
{
	m_csPromptChar = m_editMasked.GetPromptSymbol() ;
	m_bAutoTab=m_editMasked.GetAutoTab();
	
	CPropertyPage::OnInitDialog() ;
	
	m_comboMasks.AddString ( _T("Digit Test: ###-####") ) ;
	m_comboMasks.AddString ( _T("Decimal Test: ###.###.###.###") ) ;
	m_comboMasks.AddString ( _T("Thousands Test: ##,###.##") ) ;
	m_comboMasks.AddString ( _T("Time Test: ##:##") ) ;
	m_comboMasks.AddString ( _T("Date Test: ##/##/####") ) ;
	// Since the "C" programming language also uses the '\' as an escape character, 
	// you must use two in sequence to equal one switch for masking purposes. 
	m_comboMasks.AddString ( _T("\\Alphanumeric Test: AAAAAAAAAA\\, AAAAAAAA") ) ;
	m_comboMasks.AddString ( _T("\\Alphabetic Test: ????????????????") ) ;
	m_comboMasks.AddString ( _T("Uppercase Test: >>>>>>> ????????") ) ;
	m_comboMasks.AddString ( _T("Lowercase Test: <<<<<<< ????????") ) ;
	m_comboMasks.AddString ( _T("Phone:(###)###-#### Ext:####") ) ;
	m_comboMasks.AddString ( _T("AAA-#######")                  ) ;
	m_comboMasks.AddString ( _T("&####-##-## ##\\:##\\:##")     ) ;
	m_comboMasks.SetCurSel ( 0 ) ;
	OnSelendokMasks() ;
	return TRUE ;
}

void CMaskedEditDlg::OnSelendokMasks()
{
	TRACE(_T("CMaskedEditDlg::OnSelendokMasks()\n"));

	int nSelected = m_comboMasks.GetCurSel() ;
	if ( nSelected >= 0 )
	{
		CString csNewMask ;
		m_comboMasks.GetLBText ( nSelected, csNewMask ) ;
		m_editMasked.SetMask   ( csNewMask ) ;
	}
}

void CMaskedEditDlg::OnEditchangeMasks() 
{
	TRACE(_T("CMaskedEditDlg::OnEditchangeMasks()\n"));
	
	CString csNewMask ;
	m_comboMasks.GetWindowText ( csNewMask ) ;
	m_editMasked.SetMask       ( csNewMask ) ;
}

void CMaskedEditDlg::OnChangeEditPrompt() 
{
	TRACE(_T("CMaskedEditDlg::OnChangeEditPrompt()\n"));
	
	UpdateData ( TRUE ) ;
	if ( m_csPromptChar.GetLength() == 1 )
		m_editMasked.SetPromptSymbol ( m_csPromptChar[0] ) ;
}

void CMaskedEditDlg::OnButtonEmpty() 
{
	// TODO: Add your control notification handler code here
	m_editMasked.EmptyData(TRUE);
	UpdateData ( FALSE ) ;
}

void CMaskedEditDlg::OnCheckAutotab() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_editMasked.SetAutoTab(m_bAutoTab);
}

void CMaskedEditDlg::OnValidateEditTest(NMHDR * pNotifyStruct, LRESULT * result)
{
	LPMENMHDR pMENotifyStruct = (LPMENMHDR)pNotifyStruct;

	UpdateData();

	CString sText=m_editMasked.GetInputData();

	// just as an example: if user typed "345" then typed information is invalid,
	// cursor will be set before first found "345" symbol
	int nPos=sText.Find(_T("345"));
	if(nPos!=-1)
	{
		pMENotifyStruct->bValid=FALSE;
		pMENotifyStruct->nPosition=m_editMasked.LPtoRP(nPos);
	}
	else
	{
		pMENotifyStruct->bValid=TRUE;
		pMENotifyStruct->bDefaultValidation=TRUE;
	}

	*result=0;
}

