
#include "stdafx.h"
#include "DHtmlEditDemo.h"
#include "HrProperties.h"


// Dialog to enter properties of a <HR> (horizontal line)

IMPLEMENT_DYNCREATE(CHrProperties, CDialog)

CHrProperties::CHrProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CHrProperties::IDD, pParent)
{
	ms32_Shade = 0;
}

CHrProperties::~CHrProperties()
{
}

void CHrProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, ms_Width);
	DDX_Text(pDX, IDC_EDIT_SIZE,  ms_Size);
	DDX_Text(pDX, IDC_EDIT_COLOR, ms_Color);
	DDX_CBIndex(pDX, IDC_COMBO_SHADE, ms32_Shade);
}


BEGIN_MESSAGE_MAP(CHrProperties, CDialog)
END_MESSAGE_MAP()





