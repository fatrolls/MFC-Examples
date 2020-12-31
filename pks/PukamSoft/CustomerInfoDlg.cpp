// CustomerInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "CustomerInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomerInfoDlg dialog


CCustomerInfoDlg::CCustomerInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomerInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomerInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCustomerIDStatic			= 0;
	m_pCompanyNameStatic		= 0;
	m_pContactPersonStatic		= 0;
	m_pAddress1Static			= 0;
	m_pAddress2Static			= 0;
	m_pPhoneRStatic				= 0;
	m_pPhoneOStatic				= 0;
	m_pCellStatic				= 0;
	m_pFaxStatic				= 0;
	m_pEmailStatic				= 0;

	m_pCustomerIDEdit			= 0;
	m_pCompanyNameEdit			= 0;
	m_pContactPersonEdit		= 0;
	m_pAddress1Edit				= 0;
	m_pAddress2Edit				= 0;
	m_pPhoneREdit				= 0;
	m_pPhoneOEdit				= 0;
	m_pCellEdit					= 0;
	m_pFaxEdit					= 0;
	m_pEmailEdit				= 0;

	m_pSaveDetailsButton		= 0;
	
//	m_pTopBandStatic			= 0;
//	m_pBottomBandStatic			= 0;
}


void CCustomerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomerInfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomerInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomerInfoDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomerInfoDlg message handlers

int CCustomerInfoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);
	m_memBmp.CreateCompatibleBitmap(&dc,262,672);
	m_memDC.SelectObject(&m_memBmp);
	m_hBackBmp = LoadGIFEng(((CPukamSoftApp*)AfxGetApp())->GetDLLHandle(),MAKEINTRESOURCE(IDB_LN_STRIP),&m_memBmp);
//	CreateFontStatic();
	PaintMemoryDC();
	CreateControls();
	InitializeControls();

	return 0;
}

BOOL CCustomerInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx( WS_EX_APPWINDOW, 0 );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomerInfoDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);
	dc.FillSolidRect(&rcClient,BLACK);
	dc.StretchBlt(266,96,1024,768,&m_memDC,0,0,4,672,SRCCOPY);
	dc.FillSolidRect(CRect(320-3,175-3,950+3,710+3),RGB(32,26,12)/*RGB(185,185,185)*/);
	dc.FillSolidRect(CRect(320,175,950,710),BLACK);

#if 0
	dc.SelectObject(&m_fontStatic);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(100,129,199));
	dc.DrawText("Customer ID",11,CRect(357,215-40,357+124,215+16-40),DT_VCENTER|DT_SINGLELINE|DT_EXTERNALLEADING);
#endif
	// Do not call CDialog::OnPaint() for painting messages
}

void CCustomerInfoDlg::CreateControls()
{
	m_pCustomerIDStatic			= new CSkinnedStatic;
	m_pCompanyNameStatic		= new CSkinnedStatic;
	m_pContactPersonStatic		= new CSkinnedStatic;
	m_pAddress1Static			= new CSkinnedStatic;
	m_pAddress2Static			= new CSkinnedStatic;
	m_pPhoneRStatic				= new CSkinnedStatic;
	m_pPhoneOStatic				= new CSkinnedStatic;
	m_pCellStatic				= new CSkinnedStatic;
	m_pFaxStatic				= new CSkinnedStatic;
	m_pEmailStatic				= new CSkinnedStatic;

	m_pCustomerIDEdit			= new CSkinnedEdit;
	m_pCompanyNameEdit			= new CSkinnedEdit;
	m_pContactPersonEdit		= new CSkinnedEdit;
	m_pAddress1Edit				= new CSkinnedEdit;
	m_pAddress2Edit				= new CSkinnedEdit;
	m_pPhoneREdit				= new CSkinnedEdit;
	m_pPhoneOEdit				= new CSkinnedEdit;
	m_pCellEdit					= new CSkinnedEdit;
	m_pFaxEdit					= new CSkinnedEdit;
	m_pEmailEdit				= new CSkinnedEdit;

	m_pSaveDetailsButton		= new CSkinnedButton;
//	m_pTopBandStatic			= new CSkinnedStatic;
//	m_pBottomBandStatic			= new CSkinnedStatic;
}

void CCustomerInfoDlg::DestroyControls()
{
	if(m_pCustomerIDStatic)
	{
		delete m_pCustomerIDStatic;
		m_pCustomerIDStatic = 0;
	}
	if(m_pCompanyNameStatic)
	{
		delete m_pCompanyNameStatic;
		m_pCompanyNameStatic = 0;
	}
	if(m_pContactPersonStatic)
	{
		delete m_pContactPersonStatic;
		m_pContactPersonStatic = 0;
	}
	if(m_pAddress1Static)
	{
		delete m_pAddress1Static;
		m_pAddress1Static = 0;
	}
	if(m_pAddress2Static)
	{
		delete m_pAddress2Static;
		m_pAddress2Static = 0;
	}
	if(m_pPhoneRStatic)
	{
		delete m_pPhoneRStatic;
		m_pPhoneRStatic = 0;
	}
	if(m_pPhoneOStatic)
	{
		delete m_pPhoneOStatic;
		m_pPhoneOStatic = 0;
	}
	if(m_pCellStatic)
	{
		delete m_pCellStatic;
		m_pCellStatic = 0;
	}
	if(m_pFaxStatic)
	{
		delete m_pFaxStatic;
		m_pFaxStatic = 0;
	}
	if(m_pEmailStatic)
	{
		delete m_pEmailStatic;
		m_pEmailStatic = 0;
	}

	if(m_pCustomerIDEdit)
	{
		delete m_pCustomerIDEdit;
		m_pCustomerIDEdit = 0;
	}
	if(m_pCompanyNameEdit)
	{
		delete m_pCompanyNameEdit;
		m_pCompanyNameEdit = 0;
	}
	if(m_pContactPersonEdit)
	{
		delete m_pContactPersonEdit;
		m_pContactPersonEdit = 0;
	}
	if(m_pAddress1Edit)
	{
		delete m_pAddress1Edit;
		m_pAddress1Edit = 0;
	}
	if(m_pAddress2Edit)
	{
		delete m_pAddress2Edit;
		m_pAddress2Edit = 0;
	}
	if(m_pPhoneREdit)
	{
		delete m_pPhoneREdit;
		m_pPhoneREdit = 0;
	}
	if(m_pPhoneOEdit)
	{
		delete m_pPhoneOEdit;
		m_pPhoneOEdit = 0;
	}
	if(m_pCellEdit)
	{
		delete m_pCellEdit;
		m_pCellEdit = 0;
	}
	if(m_pFaxEdit)
	{
		delete m_pFaxEdit;
		m_pFaxEdit = 0;
	}
	if(m_pEmailEdit)
	{
		delete m_pEmailEdit;
		m_pEmailEdit = 0;
	}
	if(m_pSaveDetailsButton)
	{
		delete m_pSaveDetailsButton;
		m_pSaveDetailsButton = 0;
	}
	/*if(m_pTopBandStatic)
	{
		delete m_pTopBandStatic;
		m_pTopBandStatic = 0;
	}
	if(m_pBottomBandStatic)
	{
		delete m_pBottomBandStatic;
		m_pBottomBandStatic = 0;
	}*/
}

void CCustomerInfoDlg::InitializeControls()
{
//	m_pTopBandStatic->SetImageResource(IDB_CI_TOPBAND);
//	m_pBottomBandStatic->SetImageResource(IDB_MM_BOTTOMBAND);
	m_pCustomerIDStatic->SetImageResource(IDB_CI_CUSTOMERID_STATIC);
	m_pCompanyNameStatic->SetImageResource(IDB_CI_COMPANYNAME_STATIC);
	m_pContactPersonStatic->SetImageResource(IDB_CI_CONTACTPERSON_STATIC);
	m_pAddress1Static->SetImageResource(IDB_CI_ADDRESS1_STATIC);
	m_pAddress2Static->SetImageResource(IDB_CI_ADDRESS2_STATIC);
	m_pPhoneRStatic->SetImageResource(IDB_CI_PHONER_STATIC);
	m_pPhoneOStatic->SetImageResource(IDB_CI_PHONEO_STATIC);
	m_pCellStatic->SetImageResource(IDB_CI_CELL_STATIC);
	m_pFaxStatic->SetImageResource(IDB_CI_FAX_STATIC);
	m_pEmailStatic->SetImageResource(IDB_CI_EMAIL_STATIC);

	

//	m_pTopBandStatic->CreateSkinControl("",CRect(0,0,1024,114),this,IDC_SKINNEDSTATIC);
//	m_pBottomBandStatic->CreateSkinControl("",CRect(0,748,1024,768),this,IDC_SKINNEDSTATIC);
	m_pCustomerIDStatic->CreateSkinControl("",CRect(357,215,357+124,215+16),this,IDC_SKINNEDSTATIC);
	m_pCompanyNameStatic->CreateSkinControl("",CRect(357,255,357+158,255+20),this,IDC_SKINNEDSTATIC);
	m_pContactPersonStatic->CreateSkinControl("",CRect(357,297,357+152,297+16),this,IDC_SKINNEDSTATIC);
	m_pAddress1Static->CreateSkinControl("",CRect(357,337,357+98,337+16),this,IDC_SKINNEDSTATIC);
	m_pAddress2Static->CreateSkinControl("",CRect(357,377,357+100,377+16),this,IDC_SKINNEDSTATIC);
	m_pPhoneRStatic->CreateSkinControl("",CRect(357,417,357+95,417+20),this,IDC_SKINNEDSTATIC);
	m_pPhoneOStatic->CreateSkinControl("",CRect(357,458,357+96,458+20),this,IDC_SKINNEDSTATIC);
	m_pCellStatic->CreateSkinControl("",CRect(357,501,357+38,501+16),this,IDC_SKINNEDSTATIC);	
	m_pFaxStatic->CreateSkinControl("",CRect(357,541,357+36,541+16),this,IDC_SKINNEDSTATIC);
	m_pEmailStatic->CreateSkinControl("",CRect(357,581,357+55,581+16),this,IDC_SKINNEDSTATIC);

	m_pEmailEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pEmailEdit->SetControlType(CONTROL_TYPE_EMAIL);
	m_pEmailEdit->CreateSkinControl("",CRect(600,575,600+300,575+28),this,IDC_EMAIL_EDIT);

	m_pFaxEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pFaxEdit->SetControlType(CONTROL_TYPE_PHONE);
	m_pFaxEdit->CreateSkinControl("",CRect(600,535,600+120,535+28),this,IDC_FAX_EDIT);

	m_pCellEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pCellEdit->SetControlType(CONTROL_TYPE_PHONE);
	m_pCellEdit->CreateSkinControl("",CRect(600,495,600+150,495+28),this,IDC_CELL_EDIT);

	m_pPhoneOEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pPhoneOEdit->SetControlType(CONTROL_TYPE_PHONE);
	m_pPhoneOEdit->CreateSkinControl("",CRect(600,452,600+120,452+28),this,IDC_PHONEO_EDIT);

	m_pPhoneREdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pPhoneREdit->SetControlType(CONTROL_TYPE_PHONE);
	m_pPhoneREdit->CreateSkinControl("",CRect(600,411,600+120,411+28),this,IDC_PHONER_EDIT);

	m_pAddress2Edit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pAddress2Edit->CreateSkinControl("",CRect(600,371,600+300,371+28),this,IDC_ADDRESS2_EDIT);

	m_pAddress1Edit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pAddress1Edit->CreateSkinControl("",CRect(600,331,600+300,331+28),this,IDC_ADDRESS1_EDIT);

	m_pContactPersonEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pContactPersonEdit->CreateSkinControl("",CRect(600,291,600+200,291+28),this,IDC_CONTACTPERSON_EDIT);

	m_pCompanyNameEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pCompanyNameEdit->CreateSkinControl("",CRect(600,249,600+300,249+28),this,IDC_COMPANYNAME_EDIT);

	m_pCustomerIDEdit->SetBackgroundColor(-1,BLACK/*RGB(255,255,255)*/);
	//m_pCustomerIDEdit->SetForegroundColor(BLACK/*RGB(255,255,255)*/);
	m_pCustomerIDEdit->SetTextColor(WHITE/*RGB(255,255,255)*/);
	m_pCustomerIDEdit->CreateSkinControl("",CRect(600,209,600+70,209+28),this,IDC_CUSTOMERID_EDIT);

	m_pSaveDetailsButton->SetImageResource(IDB_SAVEDETAILS,IDB_SAVEDETAILS_HOVER,IDB_SAVEDETAILS_HOVER);
	m_pSaveDetailsButton->CreateSkinControl("",CRect(766,651,766+168,651+42),this,IDC_SAVEDETAILS_BUTTON);
}

void CCustomerInfoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DestroyControls();	
}

void CCustomerInfoDlg::OnOK()
{
	
}

BOOL CCustomerInfoDlg::SaveCustomerInfo()
{
	BOOL bRet = FALSE;

	CCustomDB* pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();

	if(pdbWrapper != NULL)
	{
		CString csFieldArray = "pk_vCustomerID,vCompanyName,vContactPerson,vAddress1,vAddress2,vPhoneR,vPhoneO,vCell,vFax,vEmail";	
		CString csValueArray;
		csValueArray.Format("'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s'",
							m_pCustomerIDEdit->GetControlText(),
							m_pCompanyNameEdit->GetControlText(),
							m_pContactPersonEdit->GetControlText(),
							m_pAddress1Edit->GetControlText(),
							m_pAddress2Edit->GetControlText(),
							m_pPhoneREdit->GetControlText(),
							m_pPhoneOEdit->GetControlText(),
							m_pCellEdit->GetControlText(),
							m_pFaxEdit->GetControlText(),
							m_pEmailEdit->GetControlText());

		bRet = pdbWrapper->Insert(LPCTSTR("Customer_Info"),csFieldArray,csValueArray);
	}

	return bRet;
}

BOOL CCustomerInfoDlg::ValidateEntries()
{
	BOOL bRet = FALSE;

	bRet = m_pCustomerIDEdit->IsDataValid();

	if(!bRet)
	{
		MessageBoxEng(this,MB_MSG_USERDEFINED_WARNING,MB_OK_BUTTON,"Customer Info","Please enter a valid customer ID to proceed!");
	}

	return bRet;
}

BOOL CCustomerInfoDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		{
			switch(LOWORD(pMsg->wParam))
			{
			case MSG_COMMAND:
				switch(HIWORD(pMsg->wParam))
				{
				case IDC_SAVEDETAILS_BUTTON:
					OnSaveDetails();
					break;
				}
				break;
			}
			return TRUE;
		}
	default:
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CCustomerInfoDlg::OnSaveDetails()
{
	if(ValidateEntries())
	{
		if(SaveCustomerInfo())
		{
			MessageBoxEng(this,MB_MSG_USERDEFINED_INFORMATION,MB_OK_BUTTON,"Customer Info","Customer Information is saved!");
			ClearAllControls();
		}
		else
		{
			MessageBoxEng(this,MB_MSG_USERDEFINED_ERROR,MB_OK_BUTTON,"Customer Info","Customer Information could not be saved!");
		}
	}
}

void CCustomerInfoDlg::PaintMemoryDC()
{
	BITMAP bmpTemp;

	memset(&bmpTemp, 0, sizeof(BITMAP));

	if(m_memDC == NULL)
	{
		return;
	}

	if(m_hBackBmp != NULL)
	{
		::GetObject(m_hBackBmp, sizeof(BITMAP), &bmpTemp);

		::SelectObject(m_memDC.GetSafeHdc(),m_hBackBmp);
	}
}

void CCustomerInfoDlg::CreateFontStatic()
{
	LOGFONT lf;
	memset(&lf,0,sizeof(lf));
	strcpy(lf.lfFaceName,"Arial");
	lf.lfHeight = 24;
	lf.lfWeight = FW_BOLD;
	m_fontStatic.CreateFontIndirect(&lf);
}

void CCustomerInfoDlg::OnCancel()
{

}

void CCustomerInfoDlg::ClearAllControls()
{
	m_pCustomerIDEdit->SetControlText("");
	m_pCompanyNameEdit->SetControlText("");
	m_pContactPersonEdit->SetControlText("");
	m_pAddress1Edit->SetControlText("");
	m_pAddress2Edit->SetControlText("");
	m_pPhoneREdit->SetControlText("");
	m_pPhoneOEdit->SetControlText("");
	m_pCellEdit->SetControlText("");
	m_pFaxEdit->SetControlText("");
	m_pEmailEdit->SetControlText("");
}

