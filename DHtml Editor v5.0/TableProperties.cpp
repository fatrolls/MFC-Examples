
#include "stdafx.h"
#include "DHtmlEditDemo.h"
#include "TableProperties.h"


// Dialog to enter properties of a <TABLE>

IMPLEMENT_DYNCREATE(CTableProperties, CDialog)

CTableProperties::CTableProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CTableProperties::IDD, pParent)
{
}

CTableProperties::~CTableProperties()
{
}

BEGIN_MESSAGE_MAP(CTableProperties, CDialog)
END_MESSAGE_MAP()

void CTableProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BorderWidth, ms_BorderWidth);
	DDX_Text(pDX, IDC_EDIT_BORDERCOLOR, ms_BorderColor);
	DDX_Text(pDX, IDC_EDIT_BACKGCOLOR,  ms_BackgColor);
	DDX_Text(pDX, IDC_EDIT_WIDTH,       ms_Width);
	DDX_Text(pDX, IDC_EDIT_HEIGHT,      ms_Height);
	DDX_Text(pDX, IDC_EDIT_CELLPADDING, ms_CellPadding);
	DDX_Text(pDX, IDC_EDIT_CELLSPACING, ms_CellSpacing);
	DDX_Control(pDX, IDC_COMBO_RULE, mCtrl_ComboRules);
}

BOOL CTableProperties::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	mCtrl_ComboRules.SetCurSel(mu32_Rules);
	return TRUE;
}

void CTableProperties::OnOK() 
{
	mu32_Rules = mCtrl_ComboRules.GetCurSel();
	
	CDialog::OnOK();
}




