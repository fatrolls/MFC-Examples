// OutwardTransactionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "OutwardTransactionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HHOOK g_OTHook = NULL;
COutwardTransactionsDlg *g_pOTDlg = NULL;

LRESULT FAR PASCAL GetOutwardTransactionsDlgMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	LPMSG lpMsg = (LPMSG)lParam;
	CRect rc;
	
	BOOL bRetVal = FALSE;
	for(int i = 0; i < 5; i++)
	{
		::GetWindowRect(g_pOTDlg->GetComboBoxPtr(i)->GetSafeHwnd(),&rc);
		
		if(!PtInRect(&rc,lpMsg->pt) && (lpMsg->message == WM_LBUTTONDOWN))
		{
			CSkinnedComboBox* pTempComboPtr = g_pOTDlg->GetComboBoxPtr(i);
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
		return CallNextHookEx(g_OTHook,code,wParam,lParam);
	}
}
/////////////////////////////////////////////////////////////////////////////
// COutwardTransactionsDlg dialog


COutwardTransactionsDlg::COutwardTransactionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COutwardTransactionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COutwardTransactionsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCustomerIDStatic				= 0;
	m_pSerialNumberStatic			= 0;
	m_pDateStatic					= 0;
	m_pGatePassNumberStatic			= 0;
	m_pQuantityStatic				= 0;

	m_pCustomerIDCombo				= 0;
	m_pSerialNumberCombo			= 0;
	m_pDateDayCombo					= 0;
	m_pDateMonthCombo				= 0;
	m_pDateYearCombo				= 0;
	m_pGatePassNumberEdit			= 0;
	m_pQuantityEdit					= 0;

	m_pSaveDetailsButton			= 0;
//	m_pTopBandStatic				= 0;
//	m_pBottomBandStatic				= 0;
	m_csCompanyName					= "";
}


void COutwardTransactionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutwardTransactionsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutwardTransactionsDlg, CDialog)
	//{{AFX_MSG_MAP(COutwardTransactionsDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutwardTransactionsDlg message handlers

int COutwardTransactionsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

BOOL COutwardTransactionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx( WS_EX_APPWINDOW, 0 );

	g_pOTDlg = this;
	g_OTHook = SetWindowsHookEx(WH_GETMESSAGE,GetOutwardTransactionsDlgMsgProc,NULL,GetCurrentThreadId());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COutwardTransactionsDlg::OnPaint() 
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
	dc.SetTextColor(RGB(10,255,250));
	dc.TextOut(310,105,m_csCompanyName);
	dc.SelectObject(pFont);
	// Do not call CDialog::OnPaint() for painting messages
}

void COutwardTransactionsDlg::CreateControls()
{
	m_pCustomerIDStatic				= new CSkinnedStatic;
	m_pSerialNumberStatic			= new CSkinnedStatic;
	m_pDateStatic					= new CSkinnedStatic;
	m_pGatePassNumberStatic			= new CSkinnedStatic;
	m_pQuantityStatic				= new CSkinnedStatic;

	m_pCustomerIDCombo				= new CSkinnedComboBox;
	m_pSerialNumberCombo			= new CSkinnedComboBox;
	m_pDateDayCombo					= new CSkinnedComboBox;
	m_pDateMonthCombo				= new CSkinnedComboBox;
	m_pDateYearCombo				= new CSkinnedComboBox;
	m_pGatePassNumberEdit			= new CSkinnedEdit;
	m_pQuantityEdit					= new CSkinnedEdit;

	m_pSaveDetailsButton			= new CSkinnedButton;
//	m_pTopBandStatic				= new CSkinnedStatic;
//	m_pBottomBandStatic				= new CSkinnedStatic;
}

void COutwardTransactionsDlg::DestroyControls()
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
	if(m_pDateStatic)
	{
		delete m_pDateStatic;
		m_pDateStatic = 0;
	}
	if(m_pGatePassNumberStatic)
	{
		delete m_pGatePassNumberStatic;
		m_pGatePassNumberStatic = 0;
	}
	if(m_pQuantityStatic)
	{
		delete m_pQuantityStatic;
		m_pQuantityStatic = 0;
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
	if(m_pGatePassNumberEdit)
	{
		delete m_pGatePassNumberEdit;
		m_pGatePassNumberEdit = 0;
	}
	if(m_pQuantityEdit)
	{
		delete m_pQuantityEdit;
		m_pQuantityEdit = 0;
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

void COutwardTransactionsDlg::InitializeControls()
{
//	m_pTopBandStatic->SetImageResource(IDB_OT_TOPBAND);
//	m_pBottomBandStatic->SetImageResource(IDB_MM_BOTTOMBAND);
	m_pCustomerIDStatic->SetImageResource(IDB_OT_CUSTOMERID_STATIC);
	m_pSerialNumberStatic->SetImageResource(IDB_OT_SERIALNUMBER_STATIC);
	m_pDateStatic->SetImageResource(IDB_OT_DATE_STATIC);
	m_pGatePassNumberStatic->SetImageResource(IDB_OT_GATEPASSNUMBER_STATIC);
	m_pQuantityStatic->SetImageResource(IDB_OT_QUANTITY_STATIC);
	
//	m_pTopBandStatic->CreateSkinControl("",CRect(0,0,1024,114),this,IDC_SKINNEDSTATIC);
//	m_pBottomBandStatic->CreateSkinControl("",CRect(0,748,1024,768),this,IDC_SKINNEDSTATIC);
	m_pCustomerIDStatic->CreateSkinControl("",CRect(357,215,357+124,215+16),this,IDC_SKINNEDSTATIC);
	m_pSerialNumberStatic->CreateSkinControl("",CRect(357,255,357+144,255+16),this,IDC_SKINNEDSTATIC);
	m_pDateStatic->CreateSkinControl("",CRect(357,293,357+47,293+16),this,IDC_SKINNEDSTATIC);
	m_pGatePassNumberStatic->CreateSkinControl("",CRect(357,333,357+186,333+16),this,IDC_SKINNEDSTATIC);
	m_pQuantityStatic->CreateSkinControl("",CRect(357,373,357+85,373+20),this,IDC_SKINNEDSTATIC);

	m_pQuantityEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pQuantityEdit->SetControlType(CONTROL_TYPE_NUMERIC);
	m_pQuantityEdit->CreateSkinControl("",CRect(600,367,600+80,367+28),this,IDC_QUANTITY_EDIT);

	m_pGatePassNumberEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pGatePassNumberEdit->SetControlType(CONTROL_TYPE_NUMERIC);
	m_pGatePassNumberEdit->CreateSkinControl("",CRect(600,327,600+80,327+28),this,IDC_GATEPASSNUMBER_EDIT);

	m_pDateYearCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pDateYearCombo->CreateSkinControl("",CRect(750-2,287-1,750+80,287+29+1),this,IDC_DATE_YEAR_COMBO,120);
	PopulateDateYearCombo(m_pDateYearCombo);

	m_pDateMonthCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pDateMonthCombo->CreateSkinControl("",CRect(670-2,287-1,670+70,287+29+1),this,IDC_DATE_MONTH_COMBO,90);
	PopulateDateMonthCombo(m_pDateMonthCombo);

	m_pDateDayCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pDateDayCombo->CreateSkinControl("",CRect(600-2,287-1,600+60,287+29+1),this,IDC_DATE_DAY_COMBO,120);
	PopulateDateDayCombo(m_pDateDayCombo);
	
	m_pSerialNumberCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pSerialNumberCombo->CreateSkinControl("",CRect(600-2,249-1,600+100,249+29+1),this,IDC_SERIALNUMBER_COMBO,90);
	PopulateSerialNumberCombo(m_pSerialNumberCombo);

	m_pCustomerIDCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pCustomerIDCombo->CreateSkinControl("",CRect(600-2,209-1,600+100,209+29+1),this,IDC_CUSTOMERID_COMBO,90);
	PopulateCustomerIDCombo(m_pCustomerIDCombo);

	m_pSaveDetailsButton->SetImageResource(IDB_SAVEDETAILS,IDB_SAVEDETAILS_HOVER,IDB_SAVEDETAILS_HIT);
	m_pSaveDetailsButton->CreateSkinControl("",CRect(766,651,766+168,651+42),this,IDC_SAVEDETAILS_BUTTON);
}

void COutwardTransactionsDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DestroyControls();
	::UnhookWindowsHookEx(g_OTHook);
}

CSkinnedComboBox* COutwardTransactionsDlg::GetComboBoxPtr(int nIndex)
{
	switch(nIndex)
	{
	case 0:
		return m_pCustomerIDCombo;
	case 1:
		return m_pSerialNumberCombo;
	case 2:
		return m_pDateDayCombo;
	case 3:
		return m_pDateMonthCombo;
	case 4:
		return m_pDateYearCombo;
	default:
		return NULL;
	}
	
	return NULL;
}

void COutwardTransactionsDlg::PopulateDateDayCombo(CSkinnedComboBox *pDateDayCombo)
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

void COutwardTransactionsDlg::PopulateCustomerIDCombo(CSkinnedComboBox *pCustomerIDCombo)
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

void COutwardTransactionsDlg::PopulateDateMonthCombo(CSkinnedComboBox *pDateMonthCombo)
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

void COutwardTransactionsDlg::PopulateDateYearCombo(CSkinnedComboBox *pDateYearCombo)
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

void COutwardTransactionsDlg::PopulateSerialNumberCombo(CSkinnedComboBox *pSerialNumberCombo)
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

void COutwardTransactionsDlg::OnSaveDetails()
{
	if(ValidateEntries())
	{
		if(SaveOutwardTransaction())
		{
			MessageBoxEng(this,MB_MSG_USERDEFINED_INFORMATION,MB_OK_BUTTON,"Outward Transaction","Outward Transaction is saved!");
			ClearAllControls();
		}
		else
		{
			MessageBoxEng(this,MB_MSG_USERDEFINED_ERROR,MB_OK_BUTTON,"Outward Transaction","Outward Transaction could not be saved!");
		}
	}
}

BOOL COutwardTransactionsDlg::ValidateEntries()
{
	BOOL bRet = FALSE;

	if(m_pCustomerIDCombo->GetCurSel() == -1)
	{
		MessageBoxEng(this,MB_MSG_USERDEFINED_WARNING,MB_OK_BUTTON,"Outward Transaction","Please select a valid customer ID to proceed!");
	}
	else if(m_pSerialNumberCombo->GetCurSel() == -1)
	{
		MessageBoxEng(this,MB_MSG_USERDEFINED_WARNING,MB_OK_BUTTON,"Outward Transaction","Please select a valid serial number to proceed!");
	}
	else
	{
		bRet = TRUE;
	}

	return bRet;
}

BOOL COutwardTransactionsDlg::SaveOutwardTransaction()
{
	BOOL bRet = FALSE;

	CCustomDB* pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();

	if(pdbWrapper != NULL)
	{
		if(!IsQuantityValid(pdbWrapper))
		{
			MessageBoxEng(this,MB_MSG_USERDEFINED_ERROR,MB_OK_BUTTON,"Outward Transaction","Entered quantity is greater than balance quantity!");
			return FALSE;
		}

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

		CString csFieldArray = "pk_vGatePassNo,fk_vCustomerID,fk_vSerialNumber,dtDate,nQuantity";	
		CString csValueArray;
		csValueArray.Format("'%s','%s','%s',Format('%s','dd/mm/yyyy'),%d",
							m_pGatePassNumberEdit->GetControlText(),
							szCustomerID,
							szSerialNumber,
							csDate,
							atoi(m_pQuantityEdit->GetControlText()));

		bRet = pdbWrapper->Insert(LPCTSTR("Transactions_Outward"),csFieldArray,csValueArray);
	}

	return bRet;
}

BOOL COutwardTransactionsDlg::PreTranslateMessage(MSG* pMsg) 
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

void COutwardTransactionsDlg::OnOK()
{

}

void COutwardTransactionsDlg::PaintMemoryDC()
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

void COutwardTransactionsDlg::SetCompanyName(LPCTSTR lpszCompanyName)
{
	m_csCompanyName = lpszCompanyName;
}

void COutwardTransactionsDlg::CreateFontCompany()
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

void COutwardTransactionsDlg::RetrieveAndDisplayCompanyName()
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

void COutwardTransactionsDlg::ClearAllControls()
{
	m_pCustomerIDCombo->SetCurSel(-1);
	m_pSerialNumberCombo->SetCurSel(-1);
	m_pDateDayCombo->SetCurSel(-1);
	m_pDateMonthCombo->SetCurSel(-1);
	m_pDateYearCombo->SetCurSel(-1);
	m_pGatePassNumberEdit->SetControlText("");
	m_pQuantityEdit->SetControlText("");
}

BOOL COutwardTransactionsDlg::IsQuantityValid(CCustomDB *pdbWrapper)
{
	BOOL bRet = FALSE;

	CString csField = "nBalanceQuantity";
	CStringArray csValueArray;
	TCHAR szSerialNumber[32];
	CString csValue;

	int nEnteredQuantity = atoi(m_pQuantityEdit->GetControlText());
	m_pSerialNumberCombo->GetLBText(m_pSerialNumberCombo->GetCurSel(),szSerialNumber);
	CString csCondition;
	csCondition.Format("Where pk_vSerialNumber = '%s'",szSerialNumber);
	pdbWrapper->Select("Transactions_Inward",&csValueArray,1,(char*)(LPCTSTR)csField,csCondition);
	int nBalanceQuantity = atoi(csValueArray.GetAt(0));
	int nNetQuantity = nBalanceQuantity - nEnteredQuantity;
	if(nNetQuantity >= 0)
	{
		bRet = TRUE;
		csValue.Format("%d",nNetQuantity);
		pdbWrapper->Update("Transactions_Inward",(char*)(LPCTSTR)csField,(char*)(LPCTSTR)csValue,csCondition);
	}

	return bRet;
}
