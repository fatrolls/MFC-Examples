// StatusBarProperties.cpp : implementation file
//

#include "stdafx.h"
#include "StatusTricks.h"
#include "StatusBarProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusBarProperties dialog


CStatusBarProperties::CStatusBarProperties(CStatusPaneInfo *pane, BOOL bBanner,
										   CWnd* pParent)
	: CDialog(CStatusBarProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatusBarProperties)
	m_sSampleFont = _T("");
	m_bShowBanner = FALSE;
	m_bTransparentText = FALSE;
	m_bHorizontalScrolling = FALSE;
	m_bVerticalScrolling = FALSE;
	m_bClearBackground = FALSE;
	//}}AFX_DATA_INIT

	// remember the properties of the pane we're playing with
	pInfo = pane;
	m_sSampleFont = "Sample Font";
	m_bShowBanner = bBanner;
	m_bTransparentText = pInfo->GetTransparent();
	m_bClearBackground = pInfo->GetClear();
	m_bVerticalScrolling = pInfo->GetVScroll();
	m_bHorizontalScrolling = pInfo->GetHScroll();
}


void CStatusBarProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatusBarProperties)
	DDX_Text(pDX, IDC_SAMPLEFONT, m_sSampleFont);
	DDX_Check(pDX, IDC_SHOWBANNER, m_bShowBanner);
	DDX_Check(pDX, IDC_TRANSPARENTTEXT, m_bTransparentText);
	DDX_Check(pDX, IDC_HORIZONTALSCROLLING, m_bHorizontalScrolling);
	DDX_Check(pDX, IDC_VERTICALSCROLLING, m_bVerticalScrolling);
	DDX_Check(pDX, IDC_CLEARBACKGROUND, m_bClearBackground);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatusBarProperties, CDialog)
	//{{AFX_MSG_MAP(CStatusBarProperties)
	ON_BN_CLICKED(IDC_CHANGECOLORBACK, OnChangecolorback)
	ON_BN_CLICKED(IDC_CHANGECOLORFORE, OnChangecolorfore)
	ON_BN_CLICKED(IDC_CHANGEFONT, OnChangefont)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusBarProperties message handlers

BOOL CStatusBarProperties::OnInitDialog() 
{
	// default processing
	CDialog::OnInitDialog();

	// set the font in the font samples box
	if (pInfo->GetFont())
	{
		GetDlgItem(IDC_SAMPLEFONT)->SetFont(pInfo->GetFont());
	}
	return TRUE;
}

void CStatusBarProperties::OnChangecolorback() 
{
		CColorDialog		*dlg;		// dialog for choosing colors

	// build the dialog
	dlg = new CColorDialog(pInfo->GetBackColor());

	// if user changes the color
	if (dlg->DoModal() == IDOK)
	{
		// change the background color
		pInfo->SetBackColor(dlg->GetColor());
	}

	// kill the dialog
	delete dlg;
}

void CStatusBarProperties::OnChangecolorfore() 
{
		CColorDialog		*dlg;		// dialog for choosing colors

	// build the dialog
	dlg = new CColorDialog(pInfo->GetTextColor());

	// if user changes the color
	if (dlg->DoModal() == IDOK)
	{
		// change the background color
		pInfo->SetTextColor(dlg->GetColor());
	}

	// kill the dialog
	delete dlg;
}

void CStatusBarProperties::OnChangefont() 
{
		CFontDialog		*dlg;		// dialog for changing font
		LOGFONT			 lFont;		// font properties

	// if there is a font associated with the pane we're editing
	if (pInfo->GetFont())
	{
		// pick out the font properties of the font
		pInfo->GetFont()->GetLogFont(&lFont);

		// build the font dialog
		dlg = new CFontDialog(&lFont);

		// if user picks a new font
		if (dlg->DoModal() == IDOK)
		{
			// kill the current font
			GetDlgItem(IDC_SAMPLEFONT)->SetFont(GetFont());
			pInfo->GetFont()->DeleteObject();

			// create the user-specified font
			pInfo->GetFont()->CreateFontIndirect(&lFont);

			// set the font back into the sample control
			GetDlgItem(IDC_SAMPLEFONT)->SetFont(pInfo->GetFont());
		}

		// kill the dialog
		delete dlg;
	}
}

void CStatusBarProperties::OnOK() 
{
	// default processing
	CDialog::OnOK();
}

void CStatusBarProperties::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
		CBrush		 btnBrush;		// brush to paint button with
		CDC			 dc;			// dc for painting
		CRect		 area;			// area to paint color in
		CPen		*pen;			// pen for drawing
		CPen		*oldPen;		// pen already in dc

	// if we're drawing a button
	if (lpDrawItemStruct->CtlType == ODT_BUTTON)
	{
		// connect to the supplied dc
		dc.Attach(lpDrawItemStruct->hDC);

		// empty the specified area
		btnBrush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
		dc.FillRect(&lpDrawItemStruct->rcItem, &btnBrush);
		btnBrush.DeleteObject();

		// handle the brush according to the button being drawn
		switch (nIDCtl)
		{
			case IDC_CHANGECOLORFORE:
				btnBrush.CreateSolidBrush(pInfo->GetTextColor());
				break;

			case IDC_CHANGECOLORBACK:
				btnBrush.CreateSolidBrush(pInfo->GetBackColor());
				break;

			default:
				break;
		}

		// if the button is just sitting there not being pressed
		if (!(lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			// fill the box with the specified color
			area = lpDrawItemStruct->rcItem;
			area.DeflateRect(5, 5);
			dc.FillRect(area, &btnBrush);
			btnBrush.DeleteObject();

			// draw the left and top edges
			pen = new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DHIGHLIGHT));
			oldPen = dc.SelectObject(pen);
			dc.MoveTo(lpDrawItemStruct->rcItem.left,
				lpDrawItemStruct->rcItem.bottom - 1);
			dc.LineTo(lpDrawItemStruct->rcItem.left,
				lpDrawItemStruct->rcItem.top);
			dc.LineTo(lpDrawItemStruct->rcItem.right,
				lpDrawItemStruct->rcItem.top);
			dc.SelectObject(oldPen);
			pen->DeleteObject();
			delete pen;

			// draw the right and bottom edges
			pen = new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
			oldPen = dc.SelectObject(pen);
			dc.MoveTo(lpDrawItemStruct->rcItem.left + 1,
				lpDrawItemStruct->rcItem.bottom - 2);
			dc.LineTo(lpDrawItemStruct->rcItem.right - 2,
				lpDrawItemStruct->rcItem.bottom - 2);
			dc.LineTo(lpDrawItemStruct->rcItem.right - 2,
				lpDrawItemStruct->rcItem.top);
			dc.SelectObject(oldPen);
			pen->DeleteObject();
			delete pen;

			// draw the right and bottom highlights
			pen = new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DDKSHADOW));
			oldPen = dc.SelectObject(pen);
			dc.MoveTo(lpDrawItemStruct->rcItem.left,
				lpDrawItemStruct->rcItem.bottom - 1);
			dc.LineTo(lpDrawItemStruct->rcItem.right,
				lpDrawItemStruct->rcItem.bottom - 1);
			dc.MoveTo(lpDrawItemStruct->rcItem.right - 1,
				lpDrawItemStruct->rcItem.bottom - 1);
			dc.LineTo(lpDrawItemStruct->rcItem.right - 1,
				lpDrawItemStruct->rcItem.top - 1);
			dc.SelectObject(oldPen);
			pen->DeleteObject();
			delete pen;
		}

		// else the button is being pressed
		else
		{
			// fill the box with the specified color
			area = lpDrawItemStruct->rcItem;
			area.DeflateRect(5, 5);
			area.OffsetRect(1, 1);
			dc.FillRect(area, &btnBrush);
			btnBrush.DeleteObject();

			// surround the box with a black rect to indicate selection
			btnBrush.CreateSolidBrush(::GetSysColor(COLOR_3DDKSHADOW));
			dc.FrameRect(&lpDrawItemStruct->rcItem, &btnBrush);
			btnBrush.DeleteObject();

			// draw the left and top edges
			pen = new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
			oldPen = dc.SelectObject(pen);
			dc.MoveTo(lpDrawItemStruct->rcItem.left + 1,
				lpDrawItemStruct->rcItem.bottom -1 );
			dc.LineTo(lpDrawItemStruct->rcItem.left + 1,
				lpDrawItemStruct->rcItem.top + 1);
			dc.LineTo(lpDrawItemStruct->rcItem.right - 1,
				lpDrawItemStruct->rcItem.top + 1);
			dc.SelectObject(oldPen);
			pen->DeleteObject();
			delete pen;
		}
	}

	// default processing
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
