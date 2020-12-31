// BillingInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "BillingInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HHOOK g_BIHook = NULL;
CBillingInfoDlg *g_pBIDlg = NULL;

LRESULT FAR PASCAL GetBillingInfoDlgMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	LPMSG lpMsg = (LPMSG)lParam;
	CRect rc;
	
	BOOL bRetVal = FALSE;
	for(int i = 0; i < 7; i++)
	{
		::GetWindowRect(g_pBIDlg->GetComboBoxPtr(i)->GetSafeHwnd(),&rc);
		
		if(!PtInRect(&rc,lpMsg->pt) && (lpMsg->message == WM_LBUTTONDOWN))
		{
			CSkinnedComboBox* pTempComboPtr = g_pBIDlg->GetComboBoxPtr(i);
			if(pTempComboPtr->GetSafeHwnd() != NULL)
			{
				pTempComboPtr->HideDropDown();
				bRetVal = TRUE;
			}
		}
	}

	if (bRetVal)
	{
		return bRetVal;
	}
	else
	{
		return CallNextHookEx(g_BIHook,code,wParam,lParam);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CBillingInfoDlg dialog


CBillingInfoDlg::CBillingInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBillingInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBillingInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCustomerIDStatic				= 0;
	m_pSerialNumberStatic			= 0;
	m_pBillNumberStatic				= 0;
	m_pRateStatic					= 0;
	m_pFrequencyStatic				= 0;
	m_pDateStatic					= 0;
	m_pPaymentModeStatic			= 0;

	m_pCustomerIDCombo				= 0;
	m_pSerialNumberCombo			= 0;
	m_pBillNumberEdit				= 0;
	m_pRateEdit						= 0;
	m_pFrequencyCombo				= 0;
	m_pDateDayCombo					= 0;
	m_pDateMonthCombo				= 0;
	m_pDateYearCombo				= 0;
	m_pPaymentModeCombo				= 0;

	m_pSaveDetailsButton			= 0;
//	m_pTopBandStatic				= 0;
//	m_pBottomBandStatic				= 0;
	m_csCompanyName					= "";
}


void CBillingInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBillingInfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBillingInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CBillingInfoDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBillingInfoDlg message handlers

int CBillingInfoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CClientDC dc(this);
	m_memDC.CreateCompatibleDC(&dc);
	m_memBmp.CreateCompatibleBitmap(&dc,262,672);
	m_memDC.SelectObject(&m_memBmp);
	m_hBackBmp = LoadGIFEng(((CPukamSoftApp*)AfxGetApp())->GetDLLHandle(),MAKEINTRESOURCE(IDB_LN_STRIP),&m_memBmp);
	PaintMemoryDC();
	CreateFontCompany();
	CreateControls();
	InitializeControls();
	
	return 0;
}

BOOL CBillingInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx( WS_EX_APPWINDOW, 0 );

	g_pBIDlg = this;
	g_BIHook = SetWindowsHookEx(WH_GETMESSAGE,GetBillingInfoDlgMsgProc,NULL,GetCurrentThreadId());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBillingInfoDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(&rcClient);
	dc.FillSolidRect(&rcClient,BLACK);
	dc.StretchBlt(266,96,1024,768,&m_memDC,0,0,4,672,SRCCOPY);
	dc.FillSolidRect(CRect(320-3,175-3,950+3,710+3),RGB(32,26,12));
	dc.FillSolidRect(CRect(320,175,950,710),BLACK);
	CFont* pFont = dc.SelectObject(&m_fontCompany);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(229,101,33));
	dc.TextOut(310,105,m_csCompanyName);
	dc.SelectObject(pFont);

	// Do not call CDialog::OnPaint() for painting messages
}

void CBillingInfoDlg::CreateControls()
{
	m_pCustomerIDStatic				= new CSkinnedStatic;
	m_pSerialNumberStatic			= new CSkinnedStatic;
	m_pBillNumberStatic				= new CSkinnedStatic;
	m_pRateStatic					= new CSkinnedStatic;
	m_pFrequencyStatic				= new CSkinnedStatic;
	m_pDateStatic					= new CSkinnedStatic;
	m_pPaymentModeStatic			= new CSkinnedStatic;

	m_pCustomerIDCombo				= new CSkinnedComboBox;
	m_pSerialNumberCombo			= new CSkinnedComboBox;
	m_pBillNumberEdit				= new CSkinnedEdit;
	m_pRateEdit						= new CSkinnedEdit;
	m_pFrequencyCombo				= new CSkinnedComboBox;
	m_pDateDayCombo					= new CSkinnedComboBox;
	m_pDateMonthCombo				= new CSkinnedComboBox;
	m_pDateYearCombo				= new CSkinnedComboBox;
	m_pPaymentModeCombo				= new CSkinnedComboBox;

	m_pSaveDetailsButton			= new CSkinnedButton;
//	m_pTopBandStatic				= new CSkinnedStatic;
//	m_pBottomBandStatic				= new CSkinnedStatic;
}

void CBillingInfoDlg::DestroyControls()
{
	if(m_pCustomerIDStatic)
	{
		delete m_pCustomerIDStatic;
		m_pCustomerIDStatic = 0;
	}
	if(m_pSerialNumberStatic)
	{
		delete m_pSerialNumberStatic;
		m_pSerialNumberStatic = 0;
	}
	if(m_pBillNumberStatic)
	{
		delete m_pBillNumberStatic;
		m_pBillNumberStatic = 0;
	}
	if(m_pRateStatic)
	{
		delete m_pRateStatic;
		m_pRateStatic = 0;
	}
	if(m_pFrequencyStatic)
	{
		delete m_pFrequencyStatic;
		m_pFrequencyStatic = 0;
	}
	if(m_pDateStatic)
	{
		delete m_pDateStatic;
		m_pDateStatic = 0;
	}
	if(m_pPaymentModeStatic)
	{
		delete m_pPaymentModeStatic;
		m_pPaymentModeStatic = 0;
	}
	if(m_pCustomerIDCombo)
	{
		delete m_pCustomerIDCombo;
		m_pCustomerIDCombo = 0;
	}
	if(m_pSerialNumberCombo)
	{
		delete m_pSerialNumberCombo;
		m_pSerialNumberCombo = 0;
	}
	if(m_pBillNumberEdit)
	{
		delete m_pBillNumberEdit;
		m_pBillNumberEdit = 0;
	}
	if(m_pRateEdit)
	{
		delete m_pRateEdit;
		m_pRateEdit = 0;
	}
	if(m_pFrequencyCombo)
	{
		delete m_pFrequencyCombo;
		m_pFrequencyCombo = 0;
	}
	if(m_pDateDayCombo)
	{
		delete m_pDateDayCombo;
		m_pDateDayCombo = 0;
	}
	if(m_pDateMonthCombo)
	{
		delete m_pDateMonthCombo;
		m_pDateMonthCombo = 0;
	}
	if(m_pDateYearCombo)
	{
		delete m_pDateYearCombo;
		m_pDateYearCombo = 0;
	}
	if(m_pPaymentModeCombo)
	{
		delete m_pPaymentModeCombo;
		m_pPaymentModeCombo = 0;
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

void CBillingInfoDlg::InitializeControls()
{
//	m_pTopBandStatic->SetImageResource(IDB_BI_TOPBAND);
//	m_pBottomBandStatic->SetImageResource(IDB_MM_BOTTOMBAND);
	m_pCustomerIDStatic->SetImageResource(IDB_BI_CUSTOMERID_STATIC);
	m_pSerialNumberStatic->SetImageResource(IDB_BI_SERIALNUMBER_STATIC);
	m_pBillNumberStatic->SetImageResource(IDB_BI_BILLNUMBER_STATIC);
	m_pRateStatic->SetImageResource(IDB_BI_RATE_STATIC);
	m_pFrequencyStatic->SetImageResource(IDB_BI_FREQUENCY_STATIC);
	m_pDateStatic->SetImageResource(IDB_BI_DATE_STATIC);
	
//	m_pTopBandStatic->CreateSkinControl("",CRect(0,0,1024,114),this,IDC_SKINNEDSTATIC);
//	m_pBottomBandStatic->CreateSkinControl("",CRect(0,748,1024,768),this,IDC_SKINNEDSTATIC);
	m_pCustomerIDStatic->CreateSkinControl("",CRect(357,215,357+124,215+16),this,IDC_SKINNEDSTATIC);
	m_pSerialNumberStatic->CreateSkinControl("",CRect(357,255,357+144,255+16),this,IDC_SKINNEDSTATIC);
	m_pBillNumberStatic->CreateSkinControl("",CRect(357,293,357+119,293+16),this,IDC_SKINNEDSTATIC);
	m_pRateStatic->CreateSkinControl("",CRect(357,333,357+47,333+16),this,IDC_SKINNEDSTATIC);
	m_pFrequencyStatic->CreateSkinControl("",CRect(357,373,357+103,373+20),this,IDC_SKINNEDSTATIC);
	m_pDateStatic->CreateSkinControl("",CRect(357,417,357+47,417+16),this,IDC_SKINNEDSTATIC);

	m_pPaymentModeStatic->SetImageResource(IDB_BI_PAYMENTMODE_STATIC);
	m_pPaymentModeStatic->CreateSkinControl("",CRect(357,454,357+147,454+20),this,IDC_SKINNEDSTATIC);

	m_pPaymentModeCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pPaymentModeCombo->CreateSkinControl("",CRect(600-2,448-1,600+100,448+29+1),this,IDC_PAYMENTMODE_COMBO,90);
	PopulatePaymentModeCombo(m_pPaymentModeCombo);

	m_pDateYearCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pDateYearCombo->CreateSkinControl("",CRect(750-2,411-1,750+80,411+29+1),this,IDC_DATEYEAR_COMBO,120);
	PopulateDateYearCombo(m_pDateYearCombo);

	m_pDateMonthCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pDateMonthCombo->CreateSkinControl("",CRect(670-2,411-1,670+70,411+29+1),this,IDC_DATEMONTH_COMBO,90);
	PopulateDateMonthCombo(m_pDateMonthCombo);

	m_pDateDayCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pDateDayCombo->CreateSkinControl("",CRect(600-2,411-1,600+60,411+29+1),this,IDC_DATEDAY_COMBO,120);
	PopulateDateDayCombo(m_pDateDayCombo);

	m_pFrequencyCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pFrequencyCombo->CreateSkinControl("",CRect(600-2,367-1,600+120,367+29+1),this,IDC_FREQUENCY_COMBO,90);
	PopulateFrequencyCombo(m_pFrequencyCombo);

	m_pRateEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pRateEdit->SetControlType(CONTROL_TYPE_NUMERIC);
	m_pRateEdit->CreateSkinControl("",CRect(600,327,600+100,327+28),this,IDC_RATE_EDIT);

	m_pBillNumberEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pBillNumberEdit->SetControlType(CONTROL_TYPE_NUMERIC);
	m_pBillNumberEdit->CreateSkinControl("",CRect(600,287,600+100,287+28),this,IDC_BILLNUMBER_EDIT);

	m_pSerialNumberCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT);
	m_pSerialNumberCombo->CreateSkinControl("",CRect(600,249,600+100,249+29),this,IDC_SERIALNUMBER_COMBO,90);
	PopulateSerialNumberCombo(m_pSerialNumberCombo);

	m_pCustomerIDCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT);
	m_pCustomerIDCombo->CreateSkinControl("",CRect(600,209,600+100,209+29),this,IDC_CUSTOMERID_COMBO,90);
	PopulateCustomerIDCombo(m_pCustomerIDCombo);

	m_pSaveDetailsButton->SetImageResource(IDB_SAVEDETAILS,IDB_SAVEDETAILS_HOVER,IDB_SAVEDETAILS_HIT);
	m_pSaveDetailsButton->CreateSkinControl("",CRect(766,651,766+168,651+42),this,IDC_SAVEDETAILS_BUTTON);
}

void CBillingInfoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DestroyControls();
	::UnhookWindowsHookEx(g_BIHook);
}

CSkinnedComboBox* CBillingInfoDlg::GetComboBoxPtr(int nIndex)
{
	switch(nIndex)
	{
	case 0:
		return m_pCustomerIDCombo;
	case 1:
		return m_pSerialNumberCombo;
	case 2:
		return m_pFrequencyCombo;
	case 3:
		return m_pDateDayCombo;
	case 4:
		return m_pDateMonthCombo;
	case 5:
		return m_pDateYearCombo;
	case 6:
		return m_pPaymentModeCombo;
	default:
		return NULL;
	}
	
	return NULL;
}

void CBillingInfoDlg::PopulatePaymentModeCombo(CSkinnedComboBox *pPaymentModeCombo)
{
	pPaymentModeCombo->AddString("Cash");
	pPaymentModeCombo->AddString("Cheque");
	pPaymentModeCombo->AddString("DD");
	pPaymentModeCombo->AddString("");
}

void CBillingInfoDlg::PopulateDateYearCombo(CSkinnedComboBox *pDateYearCombo)
{
	CString csYear;

	for (int i = 1975; i <= 2050; i++)
	{
		csYear.Format("%d",i);
		pDateYearCombo->AddString((LPTSTR)(LPCTSTR)csYear);
	}

	csYear.Empty();
	pDateYearCombo->AddString((LPTSTR)(LPCTSTR)csYear);
}

void CBillingInfoDlg::PopulateDateMonthCombo(CSkinnedComboBox *pDateMonthCombo)
{
	pDateMonthCombo->AddString("Jan");
	pDateMonthCombo->AddString("Feb");
	pDateMonthCombo->AddString("Mar");
	pDateMonthCombo->AddString("Apr");
	pDateMonthCombo->AddString("May");
	pDateMonthCombo->AddString("Jun");
	pDateMonthCombo->AddString("Jul");
	pDateMonthCombo->AddString("Aug");
	pDateMonthCombo->AddString("Sep");
	pDateMonthCombo->AddString("Oct");
	pDateMonthCombo->AddString("Nov");
	pDateMonthCombo->AddString("Dec");
	pDateMonthCombo->AddString("");
}

void CBillingInfoDlg::PopulateDateDayCombo(CSkinnedComboBox *pDateDayCombo)
{
	CString csDay;

	for (int i = 1; i <= 31; i++)
	{
		csDay.Format("%d",i);
		pDateDayCombo->AddString((LPTSTR)(LPCTSTR)csDay);
	}

	csDay.Empty();
	pDateDayCombo->AddString((LPTSTR)(LPCTSTR)csDay);
}

void CBillingInfoDlg::PopulateFrequencyCombo(CSkinnedComboBox *pFrequencyCombo)
{
	pFrequencyCombo->AddString("Daily");
	pFrequencyCombo->AddString("Weekly");
	pFrequencyCombo->AddString("Monthly");
	pFrequencyCombo->AddString("Quarterly");
	pFrequencyCombo->AddString("Half-yearly");
	pFrequencyCombo->AddString("Yearly");
	pFrequencyCombo->AddString("");
}

void CBillingInfoDlg::PopulateSerialNumberCombo(CSkinnedComboBox *pSerialNumberCombo)
{
	CCustomDB* pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();

	if(pdbWrapper != NULL)
	{
		if(pSerialNumberCombo->GetElementCount() > 0)
		{
			pSerialNumberCombo->ClearAllContents();
		}

		TCHAR szFields[64];
		TCHAR szCustomerID[32];
		wsprintf(szFields,"%s","PK_vSerialNumber");
		
		CStringArray csArrayOfSerialNumbers;
		CString csCondition = "";

		if(m_pCustomerIDCombo->GetCurSel() != -1)
		{
			m_pCustomerIDCombo->GetLBText(m_pCustomerIDCombo->GetCurSel(),szCustomerID);
			csCondition.Format("where fk_vCustomerID = '%s'",szCustomerID);
		}

		pdbWrapper->Select("Transactions_Inward",&csArrayOfSerialNumbers,1,szFields,csCondition);

		for(int i=0; i<csArrayOfSerialNumbers.GetSize(); i++)
		{
			pSerialNumberCombo->AddString((char*)(LPCTSTR)csArrayOfSerialNumbers.GetAt(i));
		}
		pSerialNumberCombo->AddString("");
	}
}

void CBillingInfoDlg::PopulateCustomerIDCombo(CSkinnedComboBox *pCustomerIDCombo)
{
	CCustomDB* pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();

	if(pdbWrapper != NULL)
	{
		TCHAR szFields[64];
		wsprintf(szFields,"%s","PK_vCustomerID");
		
		CStringArray csArrayOfCustomerIDs;

		pdbWrapper->Select("Customer_Info",&csArrayOfCustomerIDs,1,szFields);

		for(int i=0; i<csArrayOfCustomerIDs.GetSize(); i++)
		{
			pCustomerIDCombo->AddString((char*)(LPCTSTR)csArrayOfCustomerIDs.GetAt(i));
		}
		pCustomerIDCombo->AddString("");
	}
}

void CBillingInfoDlg::OnSaveDetails()
{
	if(ValidateEntries())
	{
		if(SaveBillingInfo())
		{
			MessageBoxEng(this,MB_MSG_USERDEFINED_INFORMATION,MB_OK_BUTTON,"Billing Info","Billing info is saved!");
			ClearAllControls();
		}
		else
		{
			MessageBoxEng(this,MB_MSG_USERDEFINED_ERROR,MB_OK_BUTTON,"Billing Info","Billing info could not be saved!");
		}
	}
}

BOOL CBillingInfoDlg::ValidateEntries()
{
	BOOL bRet = FALSE;

	if(m_pCustomerIDCombo->GetCurSel() == -1)
	{
		MessageBoxEng(this,MB_MSG_USERDEFINED_WARNING,MB_OK_BUTTON,"Billing Info","Please select a valid customer ID to proceed!");
	}
	else if(m_pSerialNumberCombo->GetCurSel() == -1)
	{
		MessageBoxEng(this,MB_MSG_USERDEFINED_WARNING,MB_OK_BUTTON,"Billing Info","Please select a valid serial number to proceed!");
	}
	else
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL CBillingInfoDlg::SaveBillingInfo()
{
	BOOL bRet = FALSE;

	CCustomDB* pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();

	if(pdbWrapper != NULL)
	{
		TCHAR szCustomerID[32];
		TCHAR szSerialNumber[32];
		TCHAR szDay[8];
		int nMonth;
		TCHAR szYear[8];

		m_pCustomerIDCombo->GetLBText(m_pCustomerIDCombo->GetCurSel(),szCustomerID);
		m_pSerialNumberCombo->GetLBText(m_pSerialNumberCombo->GetCurSel(),szSerialNumber);
		m_pDateDayCombo->GetLBText(m_pDateDayCombo->GetCurSel(),szDay);
		nMonth = m_pDateMonthCombo->GetCurSel() + 1;
		m_pDateYearCombo->GetLBText(m_pDateYearCombo->GetCurSel(),szYear);

		CString csDate;
		csDate.Format("%s/%d/%s",szDay,nMonth,szYear);

		CString csFieldArray = "pk_vBillNumber,fk_vCustomerID,fk_vSerialNumber,dRate,nFrequency,dtDate,nPaymentMode,vChequeDDNumber";	
		CString csValueArray;
		csValueArray.Format("'%s','%s','%s',%.2f,%d,Format('%s','dd/mm/yyyy'),%d,'%s'",
							m_pBillNumberEdit->GetControlText(),
							szCustomerID,
							szSerialNumber,
							atof(m_pRateEdit->GetControlText()),
							m_pFrequencyCombo->GetCurSel(),
							csDate,
							m_pPaymentModeCombo->GetCurSel(),
							"1000temp");

		bRet = pdbWrapper->Insert(LPCTSTR("Billing_Info"),csFieldArray,csValueArray);
	}

	return bRet;
}

BOOL CBillingInfoDlg::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_USER:
		{
			switch(LOWORD(pMsg->wParam))
			{
			case MSG_COMMAND:
				{
					switch(HIWORD(pMsg->wParam))
					{
					case IDC_SAVEDETAILS_BUTTON:
						OnSaveDetails();
						break;
					}
					break;
				}
				
			case MSG_SELCHANGE:
				{
					switch(HIWORD(pMsg->wParam))
					{
					case IDC_CUSTOMERID_COMBO:
						PopulateSerialNumberCombo(m_pSerialNumberCombo);
						RetrieveAndDisplayCompanyName();
						break;
					}
					break;
				}
				
			default:
				break;
			}
			return TRUE;
		}
	default:
		break;
	}	
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CBillingInfoDlg::PaintMemoryDC()
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

void CBillingInfoDlg::SetCompanyName(LPCTSTR lpszCompanyName)
{
	m_csCompanyName = lpszCompanyName;
}

void CBillingInfoDlg::CreateFontCompany()
{
	LOGFONT lf;
	memset(&lf,0,sizeof(lf));
	strcpy(lf.lfFaceName,"Century Gothic");
	lf.lfHeight = 40;
	lf.lfWeight = FW_BOLD;
//	lf.lfOutPrecision = OUT_OUTLINE_PRECIS;
	lf.lfQuality = ANTIALIASED_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_MODERN;
	m_fontCompany.CreateFontIndirect(&lf);
}

void CBillingInfoDlg::RetrieveAndDisplayCompanyName()
{
	CCustomDB* pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();

	if(pdbWrapper != NULL)
	{
		TCHAR szFields[64];
		TCHAR szCustomerID[32];

		wsprintf(szFields,"%s","vCompanyName");
		
		CStringArray csCompanyNameArray;
		CString csCondition = "";

		if(m_pCustomerIDCombo->GetCurSel() != -1)
		{
			m_pCustomerIDCombo->GetLBText(m_pCustomerIDCombo->GetCurSel(),szCustomerID);
			csCondition.Format("where pk_vCustomerID = '%s'",szCustomerID);
		}

		pdbWrapper->Select("Customer_Info",&csCompanyNameArray,1,szFields,csCondition);

		SetCompanyName((LPCTSTR)csCompanyNameArray.GetAt(0));

		InvalidateRect(CRect(200,90,1024,180),TRUE);
	}
}

void CBillingInfoDlg::ClearAllControls()
{
	m_pCustomerIDCombo->SetCurSel(-1);
	m_pSerialNumberCombo->SetCurSel(-1);
	m_pDateDayCombo->SetCurSel(-1);
	m_pDateMonthCombo->SetCurSel(-1);
	m_pDateYearCombo->SetCurSel(-1);
	m_pBillNumberEdit->SetControlText("");
	m_pRateEdit->SetControlText("");
	m_pFrequencyCombo->SetCurSel(-1);
	m_pPaymentModeCombo->SetCurSel(-1);
}
