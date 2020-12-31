// InwardTransactionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PukamSoft.h"
#include "InwardTransactionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HHOOK g_ITHook = NULL;
CInwardTransactionsDlg *g_pITDlg = NULL;

LRESULT FAR PASCAL GetInwardTransactionsDlgMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	LPMSG lpMsg = (LPMSG)lParam;
	CRect rc;
	
	BOOL bRetVal = FALSE;
	for(int i = 0; i < 6; i++)
	{
		::GetWindowRect(g_pITDlg->GetComboBoxPtr(i)->GetSafeHwnd(),&rc);
		
		if(!PtInRect(&rc,lpMsg->pt) && (lpMsg->message == WM_LBUTTONDOWN))
		{
			CSkinnedComboBox* pTempComboPtr = g_pITDlg->GetComboBoxPtr(i);
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
		return CallNextHookEx(g_ITHook,code,wParam,lParam);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CInwardTransactionsDlg dialog


CInwardTransactionsDlg::CInwardTransactionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInwardTransactionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInwardTransactionsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCustomerIDStatic				= 0;
	m_pSerialNumberStatic			= 0;
	m_pDateStatic					= 0;
	m_pCategoryStatic				= 0;
	m_pSizeStatic					= 0;
	m_pWeightStatic					= 0;
	m_pQuantityStatic				= 0;
	m_pStorageLocationStatic		= 0;

	m_pCustomerIDCombo				= 0;
	m_pSerialNumberEdit				= 0;
	m_pDateDayCombo					= 0;
	m_pDateMonthCombo				= 0;
	m_pDateYearCombo				= 0;
	m_pCategoryCombo				= 0;
	m_pSizeEdit						= 0;
	m_pWeightEdit					= 0;
	m_pQuantityEdit					= 0;
	m_pStorageLocationCombo			= 0;
	m_pCategoryEdit					= 0;
	m_pStorageLocationEdit			= 0;

	m_pSaveDetailsButton			= 0;

	m_csCompanyName					= "";
}


void CInwardTransactionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInwardTransactionsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInwardTransactionsDlg, CDialog)
	//{{AFX_MSG_MAP(CInwardTransactionsDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInwardTransactionsDlg message handlers

int CInwardTransactionsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

BOOL CInwardTransactionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx( WS_EX_APPWINDOW, 0 );

	g_pITDlg = this;
	g_ITHook = SetWindowsHookEx(WH_GETMESSAGE,GetInwardTransactionsDlgMsgProc,NULL,GetCurrentThreadId());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInwardTransactionsDlg::OnPaint() 
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
	dc.SetTextColor(RGB(144,212,11));
	dc.TextOut(310,105,m_csCompanyName);
	dc.SelectObject(pFont);
	// Do not call CDialog::OnPaint() for painting messages
}

void CInwardTransactionsDlg::CreateControls()
{
	m_pCustomerIDStatic				= new CSkinnedStatic;
	m_pSerialNumberStatic			= new CSkinnedStatic;
	m_pDateStatic					= new CSkinnedStatic;
	m_pCategoryStatic				= new CSkinnedStatic;
	m_pSizeStatic					= new CSkinnedStatic;
	m_pWeightStatic					= new CSkinnedStatic;
	m_pQuantityStatic				= new CSkinnedStatic;
	m_pStorageLocationStatic		= new CSkinnedStatic;

	m_pCustomerIDCombo				= new CSkinnedComboBox;
	m_pSerialNumberEdit				= new CSkinnedEdit;
	m_pDateDayCombo					= new CSkinnedComboBox;
	m_pDateMonthCombo				= new CSkinnedComboBox;
	m_pDateYearCombo				= new CSkinnedComboBox;
	m_pCategoryCombo				= new CSkinnedComboBox;
	m_pSizeEdit						= new CSkinnedEdit;
	m_pWeightEdit					= new CSkinnedEdit;
	m_pQuantityEdit					= new CSkinnedEdit;
	m_pStorageLocationCombo			= new CSkinnedComboBox;
	m_pCategoryEdit					= new CSkinnedEdit;
	m_pStorageLocationEdit			= new CSkinnedEdit;

	m_pSaveDetailsButton			= new CSkinnedButton;
}

void CInwardTransactionsDlg::DestroyControls()
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
	if(m_pCategoryStatic)
	{
		delete m_pCategoryStatic;
		m_pCategoryStatic = 0;
	}
	if(m_pSizeStatic)
	{
		delete m_pSizeStatic;
		m_pSizeStatic = 0;
	}
	if(m_pWeightStatic)
	{
		delete m_pWeightStatic;
		m_pWeightStatic = 0;
	}
	if(m_pQuantityStatic)
	{
		delete m_pQuantityStatic;
		m_pQuantityStatic = 0;
	}
	if(m_pStorageLocationStatic)
	{
		delete m_pStorageLocationStatic;
		m_pStorageLocationStatic = 0;
	}
	if(m_pCustomerIDCombo)
	{
		delete m_pCustomerIDCombo;
		m_pCustomerIDCombo = 0;
	}
	if(m_pSerialNumberEdit)
	{
		delete m_pSerialNumberEdit;
		m_pSerialNumberEdit = 0;
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
	if(m_pCategoryCombo)
	{
		delete m_pCategoryCombo;
		m_pCategoryCombo = 0;
	}
	if(m_pSizeEdit)
	{
		delete m_pSizeEdit;
		m_pSizeEdit = 0;
	}
	if(m_pWeightEdit)
	{
		delete m_pWeightEdit;
		m_pWeightEdit = 0;
	}
	if(m_pQuantityEdit)
	{
		delete m_pQuantityEdit;
		m_pQuantityEdit = 0;
	}
	if(m_pStorageLocationCombo)
	{
		delete m_pStorageLocationCombo;
		m_pStorageLocationCombo = 0;
	}
	if(m_pCategoryEdit)
	{
		delete m_pCategoryEdit;
		m_pCategoryEdit = 0;
	}
	if(m_pStorageLocationEdit)
	{
		delete m_pStorageLocationEdit;
		m_pStorageLocationEdit = 0;
	}
	if(m_pSaveDetailsButton)
	{
		delete m_pSaveDetailsButton;
		m_pSaveDetailsButton = 0;
	}
}

void CInwardTransactionsDlg::InitializeControls()
{
	m_pCustomerIDStatic->SetImageResource(IDB_IT_CUSTOMERID_STATIC);
	m_pSerialNumberStatic->SetImageResource(IDB_IT_SERIALNUMBER_STATIC);
	m_pDateStatic->SetImageResource(IDB_IT_DATE_STATIC);
	m_pCategoryStatic->SetImageResource(IDB_IT_CATEGORY_STATIC);
	m_pSizeStatic->SetImageResource(IDB_IT_SIZE_STATIC);
	m_pWeightStatic->SetImageResource(IDB_IT_WEIGHT_STATIC);
	m_pQuantityStatic->SetImageResource(IDB_IT_QUANTITY_STATIC);
	m_pStorageLocationStatic->SetImageResource(IDB_IT_STORAGELOCATION_STATIC);

	m_pCustomerIDStatic->CreateSkinControl("",CRect(357,215,357+124,215+16),this,IDC_SKINNEDSTATIC);
	m_pSerialNumberStatic->CreateSkinControl("",CRect(357,255,357+144,255+16),this,IDC_SKINNEDSTATIC);
	m_pDateStatic->CreateSkinControl("",CRect(357,293,357+47,293+16),this,IDC_SKINNEDSTATIC);
	m_pCategoryStatic->CreateSkinControl("",CRect(357,333,357+92,333+20),this,IDC_SKINNEDSTATIC);
	m_pSizeStatic->CreateSkinControl("",CRect(357,377,357+42,377+16),this,IDC_SKINNEDSTATIC);
	m_pWeightStatic->CreateSkinControl("",CRect(357,417,357+69,417+20),this,IDC_SKINNEDSTATIC);
	m_pQuantityStatic->CreateSkinControl("",CRect(357,458,357+85,458+20),this,IDC_SKINNEDSTATIC);
	m_pStorageLocationStatic->CreateSkinControl("",CRect(357,501,357+169,501+20),this,IDC_SKINNEDSTATIC);

	m_pStorageLocationEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pStorageLocationEdit->CreateSkinControl("",CRect(770,495,770+100,495+28),this,IDC_STORAGELOCATION_EDIT);

	m_pQuantityEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pQuantityEdit->SetControlType(CONTROL_TYPE_NUMERIC);
	m_pQuantityEdit->CreateSkinControl("",CRect(600,452,600+80,452+28),this,IDC_QUANTITY_EDIT);

	m_pWeightEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pWeightEdit->SetControlType(CONTROL_TYPE_NUMERIC);
	m_pWeightEdit->CreateSkinControl("",CRect(600,411,600+80,411+28),this,IDC_WEIGHT_EDIT);

	m_pSizeEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pSizeEdit->SetControlType(CONTROL_TYPE_NUMERIC);
	m_pSizeEdit->CreateSkinControl("",CRect(600,371,600+80,371+28),this,IDC_SIZE_EDIT);

	m_pCategoryEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pCategoryEdit->CreateSkinControl("",CRect(700,327,700+100,327+28),this,IDC_CATEGORY_EDIT);

	m_pSerialNumberEdit->SetBackgroundColor(-1,RGB(255,255,255));
	m_pSerialNumberEdit->SetControlType(CONTROL_TYPE_NUMERIC);
	m_pSerialNumberEdit->CreateSkinControl("",CRect(600,249,600+100,249+28),this,IDC_SERIALNUMBER_EDIT);

	m_pStorageLocationCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pStorageLocationCombo->CreateSkinControl("",CRect(600-2,495-1,600+150,495+29+1),this,IDC_STORAGELOCATION_COMBO,120);
	PopulateStorageLocationCombo(m_pStorageLocationCombo);

	m_pCategoryCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pCategoryCombo->CreateSkinControl("",CRect(600-2,327-1,600+80,327+29+1),this,IDC_CATEGORY_COMBO,120);
	PopulateCategoryCombo(m_pCategoryCombo);

	m_pDateYearCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pDateYearCombo->CreateSkinControl("",CRect(750-2,287-1,750+80,287+29+1),this,IDC_DATE_YEAR_COMBO,120);
	PopulateDateYearCombo(m_pDateYearCombo);

	m_pDateMonthCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pDateMonthCombo->CreateSkinControl("",CRect(670-2,287-1,670+70,287+29+1),this,IDC_DATE_MONTH_COMBO,90);
	PopulateDateMonthCombo(m_pDateMonthCombo);

	m_pDateDayCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pDateDayCombo->CreateSkinControl("",CRect(600-2,287-1,600+60,287+29+1),this,IDC_DATE_DAY_COMBO,120);
	PopulateDateDayCombo(m_pDateDayCombo);

	m_pCustomerIDCombo->SetImageResource(IDB_DROPDOWN_NORMAL,IDB_DROPDOWN_HIT,IDB_DROPDOWN_HIT);
	m_pCustomerIDCombo->CreateSkinControl("",CRect(600-2,209-1,600+100,209+29+1),this,IDC_CUSTOMERID_COMBO,90);
	PopulateCustomerIDCombo(m_pCustomerIDCombo);

	m_pSaveDetailsButton->SetImageResource(IDB_SAVEDETAILS,IDB_SAVEDETAILS_HOVER,IDB_SAVEDETAILS_HIT);
	m_pSaveDetailsButton->CreateSkinControl("",CRect(766,651,766+168,651+42),this,IDC_SAVEDETAILS_BUTTON);
}

void CInwardTransactionsDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	DestroyControls();
	::UnhookWindowsHookEx(g_ITHook);
}

CSkinnedComboBox* CInwardTransactionsDlg::GetComboBoxPtr(int nIndex)
{
	switch(nIndex)
	{
	case 0:
		return m_pCustomerIDCombo;
	case 1:
		return m_pDateDayCombo;
	case 2:
		return m_pDateMonthCombo;
	case 3:
		return m_pDateYearCombo;
	case 4:
		return m_pCategoryCombo;
	case 5:
		return m_pStorageLocationCombo;
	default:
		return NULL;
	}
	
	return NULL;
}

void CInwardTransactionsDlg::PopulateDateDayCombo(CSkinnedComboBox *pDateDayCombo)
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

void CInwardTransactionsDlg::PopulateCustomerIDCombo(CSkinnedComboBox *pCustomerIDCombo)
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

void CInwardTransactionsDlg::PopulateDateMonthCombo(CSkinnedComboBox *pDateMonthCombo)
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

void CInwardTransactionsDlg::PopulateDateYearCombo(CSkinnedComboBox *pDateYearCombo)
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

void CInwardTransactionsDlg::PopulateCategoryCombo(CSkinnedComboBox *pCategoryCombo)
{
	CStringArray* pcsCategoryArray = ((CPukamSoftApp*)AfxGetApp())->GetCategories();
	for(int nIndex = 0; nIndex<pcsCategoryArray->GetSize(); nIndex++)
	{
		pCategoryCombo->AddString((char*)(LPCTSTR)pcsCategoryArray->GetAt(nIndex));
	}
	pCategoryCombo->AddString("Other");
	pCategoryCombo->AddString("");
}

void CInwardTransactionsDlg::PopulateStorageLocationCombo(CSkinnedComboBox *pStorageLocationCombo)
{
	CStringArray* pcsStorageLocationArray = ((CPukamSoftApp*)AfxGetApp())->GetStorageLocation();
	for(int nIndex = 0; nIndex<pcsStorageLocationArray->GetSize(); nIndex++)
	{
		pStorageLocationCombo->AddString((char*)(LPCTSTR)pcsStorageLocationArray->GetAt(nIndex));
	}
	pStorageLocationCombo->AddString("Other");
	pStorageLocationCombo->AddString("");
}

void CInwardTransactionsDlg::OnOK()
{

}

void CInwardTransactionsDlg::OnSaveDetails()
{
	if(ValidateEntries())
	{
		if(SaveInwardTransaction())
		{
			MessageBoxEng(this,MB_MSG_USERDEFINED_INFORMATION,MB_OK_BUTTON,"Inward Transaction","Inward Transaction is saved!");
			ClearAllControls();
		}
		else
		{
			MessageBoxEng(this,MB_MSG_USERDEFINED_ERROR,MB_OK_BUTTON,"Inward Transaction","Inward Transaction could not be saved!");
		}
	}	
}

BOOL CInwardTransactionsDlg::SaveInwardTransaction()
{
	BOOL bRet = FALSE;

	CCustomDB* pdbWrapper = ((CPukamSoftApp*)AfxGetApp())->GetConnectionObject();

	if(pdbWrapper != NULL)
	{
		TCHAR szCustomerID[32];
		TCHAR szDay[8];
		int nMonth;
		TCHAR szYear[8];
		TCHAR szCategory[16];
		TCHAR szStorageLocation[16];
		TCHAR szQuantity[16];

		m_pCustomerIDCombo->GetLBText(m_pCustomerIDCombo->GetCurSel(),szCustomerID);
		m_pDateDayCombo->GetLBText(m_pDateDayCombo->GetCurSel(),szDay);
		nMonth = m_pDateMonthCombo->GetCurSel() + 1;
		m_pDateYearCombo->GetLBText(m_pDateYearCombo->GetCurSel(),szYear);
		m_pCategoryCombo->GetLBText(m_pCategoryCombo->GetCurSel(),szCategory);
		if(strcmp(szCategory,"Other") == 0)
		{
			wsprintf(szCategory,"%s",(LPCTSTR)m_pCategoryEdit->GetControlText());
		}
		m_pStorageLocationCombo->GetLBText(m_pStorageLocationCombo->GetCurSel(),szStorageLocation);
		if(strcmp(szStorageLocation,"Other") == 0)
		{
			wsprintf(szStorageLocation,"%s",(LPCTSTR)m_pStorageLocationEdit->GetControlText());
		}
		wsprintf(szQuantity,"%s",(LPCTSTR)m_pQuantityEdit->GetControlText());

		CString csDate;
		csDate.Format("%s/%d/%s",szDay,nMonth,szYear);

		CString csFieldArray = "pk_vSerialNumber,fk_vCustomerID,dtDate,vCategory,vSize,dWeight,nQuantity,vStorageLocation,nBalanceQuantity";	
		CString csValueArray;
		csValueArray.Format("'%s','%s',Format('%s','dd/mm/yyyy'),'%s','%s',%.2f,%d,'%s',%d",
							m_pSerialNumberEdit->GetControlText(),
							szCustomerID,
							csDate,
							szCategory,
							m_pSizeEdit->GetControlText(),
							atof(m_pWeightEdit->GetControlText()),
							atoi(szQuantity),
							szStorageLocation,
							atoi(szQuantity));

		bRet = pdbWrapper->Insert(LPCTSTR("Transactions_Inward"),csFieldArray,csValueArray);
	}

	return bRet;
}

BOOL CInwardTransactionsDlg::ValidateEntries()
{
	BOOL bRet = FALSE;

	bRet = m_pSerialNumberEdit->IsDataValid();

	if(!bRet)
	{
		MessageBoxEng(this,MB_MSG_USERDEFINED_WARNING,MB_OK_BUTTON,"Inward Transaction","Please enter a valid serial number to proceed!");
	}
	return bRet;
}

BOOL CInwardTransactionsDlg::PreTranslateMessage(MSG* pMsg) 
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

void CInwardTransactionsDlg::PaintMemoryDC()
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

void CInwardTransactionsDlg::SetCompanyName(LPCTSTR lpszCompanyName)
{
	m_csCompanyName = lpszCompanyName;
}

void CInwardTransactionsDlg::CreateFontCompany()
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

void CInwardTransactionsDlg::RetrieveAndDisplayCompanyName()
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

void CInwardTransactionsDlg::ClearAllControls()
{
	m_pCustomerIDCombo->SetCurSel(-1);
	m_pDateDayCombo->SetCurSel(-1);
	m_pDateMonthCombo->SetCurSel(-1);
	m_pDateYearCombo->SetCurSel(-1);
	m_pCategoryCombo->SetCurSel(-1);
	m_pStorageLocationCombo->SetCurSel(-1);
	m_pSerialNumberEdit->SetControlText("");
	m_pSizeEdit->SetControlText("");
	m_pWeightEdit->SetControlText("");
	m_pQuantityEdit->SetControlText("");
	m_pCategoryEdit->SetControlText("");
	m_pStorageLocationEdit->SetControlText("");
}
