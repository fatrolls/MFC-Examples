// AttrDialog.cpp : implementation file
//

#include "stdafx.h"
#include "StatText.h"
#include "AttrDialog.h"

#include "OXStaticText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttrDialog dialog


CAttrDialog::CAttrDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAttrDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAttrDialog)
	m_sCaption = _T("");
	m_sFont = _T("");
	m_BlueVal = 0;
	m_GreenVal = 0;
	m_RedVal = 0;
	m_bkBlueVal = 0;
	m_bkGreenVal = 0;
	m_bkRedVal = 0;
	m_Height = 0;
	m_Bold = TRUE;
	m_Italic = FALSE;
	m_Under = FALSE;
	m_Striked = FALSE;
	m_OffsetVal = 0;
	m_bEmboss = FALSE;
	m_bRaised = FALSE;
	//}}AFX_DATA_INIT
	m_nEllipseMode = 0;
}


void CAttrDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAttrDialog)
	DDX_Control(pDX, IDC_TEST_STATIC, m_TestStatic);
	DDX_Control(pDX, IDC_OFFSET_SPIN, m_OffsetSpin);
	DDX_Control(pDX, IDC_OFFSET_EDIT, m_OffsetEdit);
	DDX_Control(pDX, IDC_HEIGHT_SPIN, m_HeightSpin);
	DDX_Control(pDX, IDC_HEIGHT_EDIT, m_HeightEdit);
	DDX_Control(pDX, IDC_BKRED_SPIN, m_bkRedSpin);
	DDX_Control(pDX, IDC_BKRED_EDIT, m_bkRedEdit);
	DDX_Control(pDX, IDC_BKGREEN_SPIN, m_bkGreenSpin);
	DDX_Control(pDX, IDC_BKGREEN_EDIT, m_bkGreenEdit);
	DDX_Control(pDX, IDC_BKBLUE_SPIN, m_bkBlueSpin);
	DDX_Control(pDX, IDC_BKBLUE_EDIT, m_bkBlueEdit);
	DDX_Control(pDX, IDC_RED_SPIN, m_RedSpin);
	DDX_Control(pDX, IDC_GREEN_SPIN, m_GreenSpin);
	DDX_Control(pDX, IDC_BLUE_SPIN, m_BlueSpin);
	DDX_Control(pDX, IDC_RED_EDIT, m_RedEdit);
	DDX_Control(pDX, IDC_GREEN_EDIT, m_GreenEdit);
	DDX_Control(pDX, IDC_BLUE_EDIT, m_BlueEdit);
	DDX_Text(pDX, IDC_CAPTION_EDIT, m_sCaption);
	DDX_Text(pDX, IDC_FONT_EDIT, m_sFont);
	DDX_Text(pDX, IDC_BLUE_EDIT, m_BlueVal);
	DDV_MinMaxInt(pDX, m_BlueVal, 0, 255);
	DDX_Text(pDX, IDC_GREEN_EDIT, m_GreenVal);
	DDV_MinMaxInt(pDX, m_GreenVal, 0, 255);
	DDX_Text(pDX, IDC_RED_EDIT, m_RedVal);
	DDV_MinMaxInt(pDX, m_RedVal, 0, 255);
	DDX_Text(pDX, IDC_BKBLUE_EDIT, m_bkBlueVal);
	DDV_MinMaxInt(pDX, m_bkBlueVal, 0, 255);
	DDX_Text(pDX, IDC_BKGREEN_EDIT, m_bkGreenVal);
	DDV_MinMaxInt(pDX, m_bkGreenVal, 0, 255);
	DDX_Text(pDX, IDC_BKRED_EDIT, m_bkRedVal);
	DDV_MinMaxInt(pDX, m_bkRedVal, 0, 255);
	DDX_Text(pDX, IDC_HEIGHT_EDIT, m_Height);
	DDV_MinMaxInt(pDX, m_Height, 1, 100);
	DDX_Check(pDX, IDC_BOLD_CHECK, m_Bold);
	DDX_Check(pDX, IDC_ITALIC_CHECK, m_Italic);
	DDX_Check(pDX, IDC_UNDER_CHECK, m_Under);
	DDX_Check(pDX, IDC_STRIKE_CHECK, m_Striked);
	DDX_Text(pDX, IDC_OFFSET_EDIT, m_OffsetVal);
	DDV_MinMaxDWord(pDX, m_OffsetVal, 0, 100);
	DDX_Check(pDX, IDC_EMBOSS_CHECK, m_bEmboss);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAttrDialog, CDialog)
	//{{AFX_MSG_MAP(CAttrDialog)
	ON_BN_CLICKED(IDC_BEGREP_RADIO, OnBegrepRadio)
	ON_BN_CLICKED(IDC_MIDREP_RADIO, OnMidrepRadio)
	ON_BN_CLICKED(IDC_ENDREP_RADIO, OnEndrepRadio)
	ON_BN_CLICKED(IDC_NOREP_RADIO, OnNorepRadio)
	ON_BN_CLICKED(IDC_APPLY_BUTTON, OnApplyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttrDialog message handlers

BOOL CAttrDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_RedSpin.SetBuddy(&m_RedEdit);
	m_RedSpin.SetRange(0, 255);
	m_GreenSpin.SetBuddy(&m_GreenEdit);
	m_GreenSpin.SetRange(0, 255);
	m_BlueSpin.SetBuddy(&m_BlueEdit);
	m_BlueSpin.SetRange(0, 255);

	m_bkRedSpin.SetBuddy(&m_bkRedEdit);
	m_bkRedSpin.SetRange(0, 255);
	m_bkGreenSpin.SetBuddy(&m_bkGreenEdit);
	m_bkGreenSpin.SetRange(0, 255);
	m_bkBlueSpin.SetBuddy(&m_bkBlueEdit);
	m_bkBlueSpin.SetRange(0, 255);

	m_HeightSpin.SetBuddy(&m_HeightEdit);
	m_HeightSpin.SetRange(1, 100);

	m_OffsetSpin.SetBuddy(&m_OffsetEdit);
	m_OffsetSpin.SetRange(0, 100);

	switch ( m_nEllipseMode )
		{
		case OX_BEGIN_ELLIPSES:
			CheckRadioButton(IDC_BEGREP_RADIO, IDC_NOREP_RADIO, IDC_BEGREP_RADIO);
			break;
		case OX_MIDDLE_ELLIPSES:
			CheckRadioButton(IDC_BEGREP_RADIO, IDC_NOREP_RADIO, IDC_MIDREP_RADIO);
			break;
		case OX_END_ELLIPSES:
			CheckRadioButton(IDC_BEGREP_RADIO, IDC_NOREP_RADIO, IDC_ENDREP_RADIO);
			break;
		default:
			CheckRadioButton(IDC_BEGREP_RADIO, IDC_NOREP_RADIO, IDC_NOREP_RADIO);
			break;
		}

	OnApplyButton();

	m_TestStatic.SetStaticEdge();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAttrDialog::OnBegrepRadio() 
{
	m_nEllipseMode = OX_BEGIN_ELLIPSES;
}

void CAttrDialog::OnMidrepRadio() 
{
	m_nEllipseMode = OX_MIDDLE_ELLIPSES;
}

void CAttrDialog::OnEndrepRadio() 
{
	m_nEllipseMode = OX_END_ELLIPSES;
}

void CAttrDialog::OnNorepRadio() 
{
	m_nEllipseMode = OX_NO_ELLIPSES;
}

void CAttrDialog::OnApplyButton() 
	{
	if (!UpdateData(TRUE))
		return;

	m_TestStatic.SetWindowText(m_sCaption);
	m_TestStatic.SetFontName(m_sFont);
	m_TestStatic.SetTextColor(RGB(m_RedVal, m_GreenVal, m_BlueVal));
	m_TestStatic.SetBkColor(RGB(m_bkRedVal, m_bkGreenVal, m_bkBlueVal));
	m_TestStatic.SetFontHeight(m_Height);
	m_TestStatic.SetFontAttr(OX_BOLD_FONT, m_Bold);
	m_TestStatic.SetFontAttr(OX_ITALIC_FONT, m_Italic);
	m_TestStatic.SetFontAttr(OX_UNDERLINED_FONT, m_Under);
	m_TestStatic.SetFontAttr(OX_STRIKED_OUT_FONT, m_Striked);
	m_TestStatic.Set3Doffset(m_OffsetVal);
	m_TestStatic.SetEllipseMode(m_nEllipseMode);
	m_TestStatic.SetEmboss(m_bEmboss, m_bRaised, TRUE);
	}
