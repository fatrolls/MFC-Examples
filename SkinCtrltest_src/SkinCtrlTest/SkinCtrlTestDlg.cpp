// SkinCtrlTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SkinCtrlTest.h"
#include "SkinCtrlTestDlg.h"
#include "proppage.h"

#include "..\skinwindows\skinctrls.h"
#include "..\skinwindows\skinctrlmgr.h"
#include "..\skinwindows\skinbase.h"
#include "..\shared\roundcorner.h"
#include "..\shared\syscolors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// skin bitmaps
UINT SCROLLALL[IM_LAST] = { IDB_SCROLL_HOT, IDB_SCROLL_COLD, IDB_SCROLL_COLD, IDB_SCROLL_DIS };
UINT BTNLEFT[IM_LAST] = { IDB_BTNLEFT_HOT, IDB_BTNLEFT_COLD, IDB_BTNLEFT_COLD, IDB_BTNLEFT_DIS };
UINT BTNMID[IM_LAST] = { IDB_BTNMID_HOT, IDB_BTNMID_COLD, IDB_BTNMID_COLD, IDB_BTNMID_DIS };
UINT BTNRIGHT[IM_LAST] = { IDB_BTNRIGHT_HOT, IDB_BTNRIGHT_COLD, IDB_BTNRIGHT_COLD, IDB_BTNRIGHT_DIS };
UINT BTNCLIPLEFT[IM_LAST] = { IDB_BTNCLIPLEFT_HOT, IDB_BTNCLIPLEFT_COLD, IDB_BTNCLIPLEFT_COLD, IDB_BTNCLIPLEFT_DIS };
UINT BTNCLIPRIGHT[IM_LAST] = { IDB_BTNCLIPRIGHT_HOT, IDB_BTNCLIPRIGHT_COLD, IDB_BTNCLIPRIGHT_COLD, IDB_BTNCLIPRIGHT_DIS };
UINT SPINUP[IM_LAST] = { IDB_SPINUP_HOT, IDB_SPINUP_COLD, IDB_SPINUP_COLD, IDB_SPINUP_DIS };
UINT SPINDOWN[IM_LAST] = { IDB_SPINDOWN_HOT, IDB_SPINDOWN_COLD, IDB_SPINDOWN_COLD, IDB_SPINDOWN_DIS };
UINT SPINRIGHT[IM_LAST] = { IDB_SPINRIGHT_HOT, IDB_SPINRIGHT_COLD, IDB_SPINRIGHT_COLD, IDB_SPINRIGHT_DIS };
UINT SPINLEFT[IM_LAST] = { IDB_SPINLEFT_HOT, IDB_SPINLEFT_COLD, IDB_SPINLEFT_COLD, IDB_SPINLEFT_DIS };
UINT PROGLEFT[IM_LAST] = { IDB_BTNLEFT_COLD, 0, 0, IDB_BTNLEFT_DIS };
UINT PROGMID[IM_LAST] = { IDB_BTNMID_COLD, 0, 0, IDB_BTNMID_DIS };
UINT PROGRIGHT[IM_LAST] = { IDB_BTNRIGHT_COLD, 0, 0, IDB_BTNRIGHT_DIS };

enum { UNSKINNED, DEFAULTSKIN, BITMAPSKIN, CUSTOMSKIN };

/////////////////////////////////////////////////////////////////////////////
// CSkinCtrlTestDlg dialog

CSkinCtrlTestDlg::CSkinCtrlTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkinCtrlTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkinCtrlTestDlg)
	m_nSkinOption = BITMAPSKIN;
	m_sEdit2 = _T("the quick brown fox\r\njumps over the lazy dog.\r\nthe quick brown fox\r\njumps over the lazy dog.\r\nthe quick brown fox\r\njumps over the lazy dog.\r\nthe quick brown fox\r\njumps over the lazy dog.\r\n");
	m_sRichedit = m_sEdit2;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_crBkgnd = GetSysColor(COLOR_3DFACE);
}

void CSkinCtrlTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkinCtrlTestDlg)
	DDX_Control(pDX, IDC_BUTTON3, m_btn3);
	DDX_Control(pDX, IDC_BUTTON4, m_btn4);
	DDX_Control(pDX, IDC_PROGRESS2, m_progressV);
	DDX_Control(pDX, IDC_COMBO2, m_combo);
	DDX_Control(pDX, IDC_PROGRESS1, m_progressH);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_scrollbar);
	DDX_Control(pDX, IDC_LIST2, m_listbox);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	DDX_Radio(pDX, IDC_UNSKINNED, m_nSkinOption);
	DDX_Text(pDX, IDC_EDIT2, m_sEdit2);
	DDX_Text(pDX, IDC_RICHEDIT1, m_sRichedit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSkinCtrlTestDlg, CDialog)
	//{{AFX_MSG_MAP(CSkinCtrlTestDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_DEFAULTSKIN, OnChangeSkin)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_COMPAREITEM()
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_SETCOLOR, OnSetcolor)
	ON_BN_CLICKED(IDC_BITMAPSKIN, OnChangeSkin)
	ON_BN_CLICKED(IDC_CUSTOMSKIN, OnChangeSkin)
	ON_BN_CLICKED(IDC_UNSKINNED, OnChangeSkin)
	ON_BN_CLICKED(IDC_PROPSHEET, OnPropsheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinCtrlTestDlg message handlers

BOOL CSkinCtrlTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// list ctrl
	m_listctrl.InsertColumn(0, "column1", LVCFMT_LEFT, 100);
	m_listctrl.InsertColumn(1, "column2", LVCFMT_LEFT, 100);
	m_listctrl.InsertColumn(2, "column3", LVCFMT_LEFT, 100);

	for (int nItem = 0; nItem < 30; nItem++)
	{
		CString sItem;
		sItem.Format("Item %d, 1", nItem + 1);
		int nIndex = m_listctrl.InsertItem(nItem, sItem);

		for (int nSubItem = 1; nSubItem < 3; nSubItem++)
		{
			sItem.Format("Item %d, %d", nItem + 1, nSubItem + 1);
			m_listctrl.SetItemText(nIndex, nSubItem, sItem);
		}
	}

	// tree ctrl
	for (nItem = 0; nItem < 10; nItem++)
	{
		CString sItem;
		sItem.Format("Item %d", nItem + 1);
		HTREEITEM hti = m_tree.InsertItem(sItem);

		sItem.Format("Item %d, 1", nItem + 1);
		HTREEITEM htiSub = m_tree.InsertItem(sItem, hti);

		sItem.Format("Item %d, 1, 1", nItem + 1);
		m_tree.InsertItem(sItem, htiSub);

		m_tree.Expand(hti, TVE_EXPAND);
		m_tree.Expand(htiSub, TVE_EXPAND);
	}

	// list/comboboxes
	for (nItem = 0; nItem < 10; nItem++)
	{
		CString sItem;
		sItem.Format("Item %d", nItem + 1);
		m_listbox.AddString(sItem);
		m_combo.AddString(sItem);
	}

	// progressctrl
	m_progressH.SetRange(0, 100);
	m_progressH.SetPos(40);
	m_progressV.SetRange(0, 100);
	m_progressV.SetPos(40);

	// tabctrl
	m_tab.InsertItem(0, "tab1");
	m_tab.InsertItem(1, "tab2");
	m_tab.InsertItem(2, "tab3");

	// scrollbar
	m_scrollbar.SetScrollRange(0, 100);
	m_scrollbar.SetScrollPos(50);

	// radio/checkbtns
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(1);

	// pushbuttons
	CSkinCtrlMgr::ModifyStyle(this, IDC_BUTTON1, 0, SKBS_CLIPRIGHT);
	CSkinCtrlMgr::ModifyStyle(this, IDC_BUTTON2, 0, SKBS_CLIPBOTH);
	CSkinCtrlMgr::ModifyStyle(this, IDC_BUTTON3, 0, SKBS_CLIPLEFT);

	m_btn4.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_btn3.SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP)));

	OnChangeSkin();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSkinCtrlTestDlg::OnBrowse() 
{
	CFileDialog dlg(TRUE);

	dlg.DoModal();
}

void CSkinCtrlTestDlg::OnChangeSkin() 
{
	UpdateData();

	CSkinCtrlMgr::Reset();
	CSkinCtrlMgr::SetColor(COLOR_PARENTBKGND, m_crBkgnd);

	switch (m_nSkinOption)
	{
	case UNSKINNED:
		CSkinCtrlMgr::EnableSkinDraw(FALSE);
		CSkinCtrlMgr::SetRenderer(NULL);
		break;

	case DEFAULTSKIN:
		CSkinCtrlMgr::SetRenderer(NULL);
		CSkinCtrlMgr::EnableSkinDraw(TRUE);
		break;
		
	case BITMAPSKIN:
		CSkinCtrlMgr::EnableSkinDraw(TRUE);
		CSkinCtrlMgr::SetRenderer(NULL);

		// load bitmap resources into skin
		CSkinCtrlMgr::SetControlBitmap(SKCB_SCROLLALL, SCROLLALL, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_BUTTONLEFT, BTNLEFT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_BUTTONMIDDLE, BTNMID, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_BUTTONRIGHT, BTNRIGHT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_HEADERLEFT, BTNLEFT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_HEADERMIDDLE, BTNMID, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_HEADERRIGHT, BTNRIGHT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_PROGRESSLEFT, BTNLEFT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_PROGRESSMIDDLE, BTNMID, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_PROGRESSRIGHT, BTNRIGHT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_SLIDERTHUMBHORZ, SCROLLALL, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_SLIDERTHUMBVERT, SCROLLALL, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_BUTTONCLIPLEFT, BTNCLIPLEFT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_BUTTONCLIPRIGHT, BTNCLIPRIGHT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_SPINUP, SPINUP, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_SPINDOWN, SPINDOWN, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_SPINRIGHT, SPINRIGHT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_SPINLEFT, SPINLEFT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_PROGRESSLEFT, PROGLEFT, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_PROGRESSMIDDLE, PROGMID, 255);
		CSkinCtrlMgr::SetControlBitmap(SKCB_PROGRESSRIGHT, PROGRIGHT, 255);

		CSkinCtrlMgr::RedrawAll();
		break;
		
	case CUSTOMSKIN:
		CSkinCtrlMgr::SetRenderer(this);
		CSkinCtrlMgr::EnableSkinDraw(TRUE);
		break;
	}

	CSkinCtrlMgr::RedrawAll();
}

BOOL CSkinCtrlTestDlg::Draw3dEdge(CDC* pDC, LPRECT pRect, int nEdge, int nState, int nClipping)
{ 
	COLORREF crTopLeft, crBottomRight;
	BOOL bHot = (nState == IM_HOT);

	switch (nEdge)
	{
	case SKCS_CLIENTEDGE:
		crTopLeft = ::GetSysColor(bHot ? COLOR_3DDKSHADOW : COLOR_3DSHADOW);
		crBottomRight = ::GetSysColor(bHot ? COLOR_3DHIGHLIGHT : COLOR_3DSHADOW);
		break;

	case SKCS_BTNEDGE:
		crTopLeft = ::GetSysColor(bHot ? COLOR_3DHIGHLIGHT : COLOR_3DSHADOW);
		crBottomRight = ::GetSysColor(bHot ? COLOR_3DDKSHADOW : COLOR_3DSHADOW);
		break;

	case SKCS_ETCHEDEDGE:
		crTopLeft = ::GetSysColor(COLOR_3DSHADOW);
		crBottomRight = ::GetSysColor(COLOR_3DSHADOW);
		break;

	case SKCS_NOEDGE:
	default:
		return FALSE;
	}

	pDC->Draw3dRect(pRect, crTopLeft, crBottomRight);
	return TRUE;
}

BOOL CSkinCtrlTestDlg::Draw3dRoundEdge(CDC* pDC, LPRECT pRect, int nEdge, int nState)
{ 
	BOOL bHot = (nState == IM_HOT);
	DWORD dwStyle = RC_THIN;
	COLORREF crBkgnd = -1;

	switch (nEdge)
	{
	case SKCS_CLIENTEDGE:
		dwStyle |= bHot ? RC_DOWN : 0;
		crBkgnd = bHot ? -1 : ::GetSysColor(COLOR_3DSHADOW);
		break;

	case SKCS_BTNEDGE:
		dwStyle |= bHot ? RC_UP : 0;
		crBkgnd = bHot ? -1 : ::GetSysColor(COLOR_3DSHADOW);
		break;

	case SKCS_ETCHEDEDGE:
		crBkgnd = ::GetSysColor(COLOR_3DSHADOW);
		break;

	case SKCS_NOEDGE:
	default:
		return FALSE;
	}

	CRoundCorner::Draw(pDC, pRect, (pRect->right - pRect->left) / 2, RC_ALL, dwStyle, crBkgnd);
	return TRUE;
}

BOOL CSkinCtrlTestDlg::Draw3dRect(CDC* pDC, LPRECT pRect, int nEdge, int nState, COLORREF crBkgnd, int nClipping)
{ 
	pDC->FillSolidRect(pRect, crBkgnd);
	Draw3dEdge(pDC, pRect, nEdge, nState, nClipping);

	return TRUE;
}

/*
BOOL CSkinCtrlTestDlg::DrawScrollbarButton(CDC* pDC, LPRECT pRect, int nState) 
{ 
	return FALSE; 
}

BOOL CSkinCtrlTestDlg::DrawScrollbarButtonArrow(CDC* pDC, LPRECT pRect, int nBar, BOOL bBack, int nState) 
{ 
	return FALSE; 
}

BOOL CSkinCtrlTestDlg::DrawSpinButton(CDC* pDC, LPRECT pRect, int nState) 
{ 
	return FALSE; 
}

BOOL CSkinCtrlTestDlg::DrawSpinButtonArrow(CDC* pDC, LPRECT pRect, int nBar, BOOL bBack, int nState) 
{ 
	return FALSE; 
}

BOOL CSkinCtrlTestDlg::DrawPushButton(CDC* pDC, LPRECT pRect, int nState, BOOL bClipLeft, BOOL bClipRight) 
{ 
	return FALSE; 
}

BOOL CSkinCtrlTestDlg::DrawPushButtonText(CDC* pDC, LPRECT pRect, int nState) 
{ 
	return FALSE; 
}

BOOL CSkinCtrlTestDlg::DrawRadioButton(CDC* pDC, LPRECT pRect, int nCheckState, int nState) 
{ 
	return FALSE; 
}

BOOL CSkinCtrlTestDlg::DrawCheckButton(CDC* pDC, LPRECT pRect, int nCheckState, int nState) 
{ 
	return FALSE; 
}
*/

void CSkinCtrlTestDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (nIDCtl == IDC_BUTTON1)
	{
		// fill background
		::SetBkColor(lpDrawItemStruct->hDC, GetSysColor(COLOR_3DFACE));
		::ExtTextOut(lpDrawItemStruct->hDC, 0, 0, ETO_OPAQUE, &lpDrawItemStruct->rcItem, NULL, 0, NULL);

		// draw a small black square
		CRect rect(lpDrawItemStruct->rcItem);
		rect.DeflateRect(13, 6);

		if (lpDrawItemStruct->itemState & (ODS_CHECKED | ODS_SELECTED))
			rect.OffsetRect(1, 1);

		::SetBkColor(lpDrawItemStruct->hDC, 0);
		::ExtTextOut(lpDrawItemStruct->hDC, rect.left, rect.top, ETO_OPAQUE, rect, NULL, 0, NULL);
	}
}

void CSkinCtrlTestDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

int CSkinCtrlTestDlg::OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	return 0;//CDialog::OnCompareItem(nIDCtl, lpCompareItemStruct);
}

void CSkinCtrlTestDlg::OnCheck3() 
{
	GetDlgItem(IDC_BUTTON4)->EnableWindow(((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck());
	
}

void CSkinCtrlTestDlg::OnSetcolor() 
{
	CColorDialog dialog;
	
	dialog.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	dialog.m_cc.rgbResult = m_crBkgnd;

	if (dialog.DoModal() == IDOK)
	{
		m_crBkgnd = dialog.GetColor();

		CSkinCtrlMgr::SetColor(COLOR_PARENTBKGND, m_crBkgnd);
		CSkinCtrlMgr::RedrawAll();
	}
}

void CSkinCtrlTestDlg::OnPropsheet() 
{
	CPropertySheet sheet;
	CPropPage page;

	sheet.AddPage(&page);
	sheet.DoModal();
}
