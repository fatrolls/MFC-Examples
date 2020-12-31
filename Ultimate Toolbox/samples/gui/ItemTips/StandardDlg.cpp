// StandardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ItemTips.h"
#include "StandardDlg.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CStandardDlg, CPropertyPage)

/////////////////////////////////////////////////////////////////////////////
// CStandardDlg dialog


CStandardDlg::CStandardDlg():CPropertyPage(CStandardDlg::IDD)
{
	//{{AFX_DATA_INIT(CStandardDlg)
	m_clrBackground = 0;
	m_sFontName = _T("");
	m_bCustomize = FALSE;
	m_bSmart = FALSE;
	//}}AFX_DATA_INIT

	m_pimagelist=NULL;
	m_pimagelistSmall=NULL;
}

CStandardDlg::~CStandardDlg()
{
	if((HFONT)m_font)
	{
		m_font.DeleteObject();
	}

	if(m_pimagelist)
		delete m_pimagelist;
	if(m_pimagelistSmall)
		delete m_pimagelistSmall;
}


void CStandardDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStandardDlg)
	DDX_Control(pDX, IDC_CHECK_SMART, m_btnSmart);
	DDX_Control(pDX, IDC_BUTTON_TEXTFONT, m_btnTextFont);
	DDX_Control(pDX, IDC_BUTTON_BKCOLOR, m_btnBkColor);
	DDX_Control(pDX, IDC_LIST_STANDARD, m_listStandard);
	DDX_Text(pDX, IDC_EDIT_BKCOLOR, m_clrBackground);
	DDX_Text(pDX, IDC_EDIT_TEXTFONT, m_sFontName);
	DDX_Check(pDX, IDC_CHECK_CUSTOMIZE, m_bCustomize);
	DDX_Check(pDX, IDC_CHECK_SMART, m_bSmart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStandardDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CStandardDlg)
	ON_BN_CLICKED(IDC_BUTTON_BKCOLOR, OnButtonBkcolor)
	ON_BN_CLICKED(IDC_BUTTON_TEXTFONT, OnButtonTextfont)
	ON_BN_CLICKED(IDC_CHECK_CUSTOMIZE, OnCheckCustomize)
	ON_BN_CLICKED(IDC_CHECK_SMART, OnCheckSmart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStandardDlg message handlers

BOOL CStandardDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CItemTipsApp* pApp = (CItemTipsApp*)AfxGetApp();
	srand((unsigned) time(NULL));  // start the random number generator
	m_pimagelist = new CImageList();		
	m_pimagelistSmall = new CImageList();
	ASSERT(m_pimagelist != NULL && m_pimagelistSmall != NULL);    // no serious allocation failure checking
	m_pimagelist->Create(32, 32, TRUE/*bMask*/,	LISTICONCOUNT/*nInitial*/, 4/*nGrow*/);
	m_pimagelistSmall->Create(16, 16, TRUE/*bMask*/, LISTICONCOUNT, 4);
	m_pimagelist->Add(pApp->LoadIcon(IDI_ICONLIST1));
	m_pimagelist->Add(pApp->LoadIcon(IDI_ICONLIST2));
	m_pimagelist->Add(pApp->LoadIcon(IDI_ICONLIST3));
	m_pimagelist->Add(pApp->LoadIcon(IDI_ICONLIST4));
	m_pimagelistSmall->Add(pApp->LoadIcon(IDI_ICONLIST1));
	m_pimagelistSmall->Add(pApp->LoadIcon(IDI_ICONLIST2));
	m_pimagelistSmall->Add(pApp->LoadIcon(IDI_ICONLIST3));
	m_pimagelistSmall->Add(pApp->LoadIcon(IDI_ICONLIST4));

	FillListCtrl();

	m_ItemTip.Attach(&m_listStandard);

	GetVars();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStandardDlg::FillListCtrl()
{
	CRect			rect;
	int				i, iIcon, iItem, iSubItem, iActualItem;
	LV_ITEM			lvitem;
	LV_COLUMN		lvcolumn;
	TCHAR			rgtsz[2][10] = {_T("MAIN ITEM"), _T("SUB_ITEM")};
	CItemTipsApp	*pApp;
	TCHAR			rgtszIconDescrip[LISTICONCOUNT][50], rgtszIconShortDesc[LISTICONCOUNT][12];

	ASSERT(LISTICONCOUNT == 4);
	UTBStr::tcscpy(rgtszIconDescrip[0], 50, _T("Blue Ellipse, Yellow Triangle, Red Rectangle"));
	UTBStr::tcscpy(rgtszIconDescrip[1], 50, _T("Yellow Ellipse, Red Triangle, Blue Rectangle"));
	UTBStr::tcscpy(rgtszIconDescrip[2], 50, _T("Red Ellipse, Blue Triangle, Yellow Rectangle"));
	UTBStr::tcscpy(rgtszIconDescrip[3], 50, _T("Red Ellipse, Yellow Triangle, Blue Rectangle"));

	UTBStr::tcscpy(rgtszIconShortDesc[0], 12, _T("BE, YT, RR"));
	UTBStr::tcscpy(rgtszIconShortDesc[1], 12, _T("YE, RT, BR"));
	UTBStr::tcscpy(rgtszIconShortDesc[2], 12, _T("RE, BT, YR"));
	UTBStr::tcscpy(rgtszIconShortDesc[3], 12, _T("RE, YT, BR"));


	pApp = (CItemTipsApp*)AfxGetApp();
	m_listStandard.SetImageList(m_pimagelist, LVSIL_NORMAL);
	m_listStandard.SetImageList(m_pimagelistSmall, LVSIL_SMALL);
	m_listStandard.GetWindowRect(&rect);

	for (i = 0; i < 2; i++)  // add the columns to the list control
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText = rgtsz[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = rect.Width() * (i + 1) / 3;  // SubItem is twice as large
		m_listStandard.InsertColumn(i, &lvcolumn);  // assumes return value is OK.
	}

	for (iItem = 0; iItem < 500; iItem++)  // will now insert the items and subitems into the list view.
		for (iSubItem = 0; iSubItem < 2; iSubItem++)
		{
			if (iSubItem == 0)
				iIcon = rand() % 4;  // choose the icon and legend for the entry

			lvitem.mask = LVIF_TEXT | (iSubItem == 0 ? LVIF_IMAGE : 0);
			lvitem.iItem = (iSubItem == 0) ? iItem : iActualItem;
			lvitem.iSubItem = iSubItem;
			lvitem.pszText = iSubItem == 0 ? rgtszIconShortDesc[iIcon] : rgtszIconDescrip[iIcon];

			lvitem.iImage = iIcon;
			if (iSubItem == 0)
				iActualItem = m_listStandard.InsertItem(&lvitem);
			else
				m_listStandard.SetItem(&lvitem);
		}
}


void CStandardDlg::OnButtonBkcolor() 
{
	// TODO: Add your control notification handler code here
	
	// use standard CColorDialog to change item tip window's background color
	CColorDialog clrDlg(m_clrBackground);
	if(clrDlg.DoModal()==IDOK)
	{
		m_clrBackground=clrDlg.GetColor();
		UpdateData(FALSE);
	}
}

void CStandardDlg::OnButtonTextfont() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);

	// Use font common dialog to change font and text color
	LOGFONT lf;
	BOOL bLogFont=FALSE;
	if((HFONT)m_font)
	{
		if(m_font.GetLogFont(&lf)!=0)
		{
			bLogFont=TRUE;
		}
	}
	CFontDialog fontDlg(bLogFont ? &lf : NULL);
	fontDlg.m_cf.rgbColors=m_clrText;
	if(fontDlg.DoModal()==IDOK)
	{
		m_clrText=fontDlg.GetColor();
		fontDlg.GetCurrentFont(&lf);
		m_sFontName=lf.lfFaceName;
		if((HFONT)m_font)
		{
			m_font.DeleteObject();
		}
		m_font.CreateFontIndirect(&lf);
		UpdateData(FALSE);
	}
}

void CStandardDlg::OnCheckCustomize() 
{
	// TODO: Add your control notification handler code here
	
	SetVars();

	// detach CListCtrl
	m_ItemTip.Detach();
	// and then attach it again and register callback function depending 
	// on m_bCustomize value
	m_ItemTip.Attach(&m_listStandard,m_bCustomize ? ItemTipHelper : NULL);
}

void CStandardDlg::OnCheckSmart() 
{
	// TODO: Add your control notification handler code here
	
	SetVars();
}

void CStandardDlg::GetVars()
{
	// fill with values from CListCtrl
	m_clrBackground=m_listStandard.GetBkColor();
	m_clrText=m_listStandard.GetTextColor();
	m_sFontName.Empty();

	UpdateData(FALSE);

	ShowControls();
}

void CStandardDlg::SetVars()
{
	UpdateData();
	ShowControls();
}

void CStandardDlg::ShowControls() 
{
	UpdateData(TRUE);

	m_btnBkColor.EnableWindow(m_bCustomize);
	m_btnTextFont.EnableWindow(m_bCustomize);
	m_btnSmart.EnableWindow(m_bCustomize);

	UpdateData(FALSE);
}

// callback function that is called by COXItemTip before display an item tip window
void CALLBACK ItemTipHelper(LPARAM lpSource, LPARAM lpInfo)
{
	// lpSource is a pointer to COXItemTip object
	CWnd* pWnd=((COXItemTip*)lpSource)->GetHookedWnd();
	ASSERT(::IsWindow(pWnd->m_hWnd));
	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CListCtrl)));

	CListCtrl* pListCtrl=(CListCtrl*)pWnd;
	// lpInfo is pointer to NEEDITEMTIPINFO structure
	LPNEEDITEMTIPINFO pnitInfo=(LPNEEDITEMTIPINFO)lpInfo;

	// get CListCtrl parent window 
	CStandardDlg* pParentWnd=(CStandardDlg*)pListCtrl->GetParent();

	if(pnitInfo->result==ID_NIT_SUCCESS)
	{
		if(!pParentWnd->m_bSmart)
		{
			// just change the text & background color and set different font
			pnitInfo->clrText=pParentWnd->m_clrText;
			pnitInfo->clrBackground=pParentWnd->m_clrBackground;
			if((HFONT)pParentWnd->m_font)
			{
				pnitInfo->pFont=(LPARAM)(&pParentWnd->m_font);
			}
		}
		else
		{
			// depending on image associated with the item change the 
			// text and background colors
			LV_ITEM lvitem;
			lvitem.mask=LVIF_IMAGE;
			lvitem.iItem=pnitInfo->row;
			lvitem.iSubItem=0;
			if(pListCtrl->GetItem(&lvitem))
			{
				switch(lvitem.iImage)
				{
				case 0:
					{
						pnitInfo->clrText=COLOR_BLUE;
						pnitInfo->clrBackground=COLOR_YELLOW;
						break;
					}
				case 1:
					{
						pnitInfo->clrText=COLOR_YELLOW;
						pnitInfo->clrBackground=COLOR_RED;
						break;
					}
				case 2:
					{
						pnitInfo->clrText=COLOR_RED;
						pnitInfo->clrBackground=COLOR_BLUE;
						break;
					}
				case 3:
					{
						pnitInfo->clrText=COLOR_RED;
						pnitInfo->clrBackground=COLOR_YELLOW;
						break;
					}
				}
			}
		}
	}
}
