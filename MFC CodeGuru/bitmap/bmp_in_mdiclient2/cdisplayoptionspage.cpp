#include "stdafx.h"
#include "MdiEx.h"
#include "MainFrm.h"
#include "CDisplayOptionsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayOptionsPage property page

IMPLEMENT_DYNCREATE(CDisplayOptionsPage, CPropertyPage)

CDisplayOptionsPage::CDisplayOptionsPage() : CPropertyPage(CDisplayOptionsPage::IDD)
{
	//{{AFX_DATA_INIT(CDisplayOptionsPage)
	m_backgroundFile = _T("");
	m_useBackgroundFile = FALSE;
	//}}AFX_DATA_INIT
	m_hBitmap = 0;
	m_hPal = 0;
}

CDisplayOptionsPage::~CDisplayOptionsPage()
{
}

void CDisplayOptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayOptionsPage)
	DDX_Control(pDX, IDC_DO_FILEPATH, m_btnFilePath);
	DDX_Control(pDX, IDC_DO_FILE, m_edtBackgroundFile);
	DDX_Control(pDX, IDC_DO_USEFILE, m_btnUseBackgroundFile);
	DDX_Control(pDX, IDC_DO_PREVIEW, m_preview);
	DDX_Control(pDX, IDC_DO_BKGND, m_lbBackground);
	DDX_Text(pDX, IDC_DO_FILE, m_backgroundFile);
	DDX_Check(pDX, IDC_DO_USEFILE, m_useBackgroundFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisplayOptionsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDisplayOptionsPage)
	ON_LBN_SELCHANGE(IDC_DO_BKGND, OnSelchangeDoBkgnd)
	ON_BN_CLICKED(IDC_DO_FILEPATH, OnDoFilepath)
	ON_BN_CLICKED(IDC_DO_USEFILE, OnDoUsefile)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DO_TILE, OnModify)
	ON_BN_CLICKED(IDC_DO_CENTRE, OnModify)
	ON_EN_CHANGE(IDC_DO_FILE, OnModify)
	//}}AFX_MSG_MAP
//	ON_MESSAGE(CWN_COLOR_CHANGE, OnModify)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::OnKillActive
// Description	    : 
// Return type		: BOOL 
//
///////////////////////////////////////////////////////////////////////////////
BOOL CDisplayOptionsPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnKillActive();
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::OnSetActive
// Description	    : 
// Return type		: BOOL 
//
///////////////////////////////////////////////////////////////////////////////
BOOL CDisplayOptionsPage::OnSetActive() 
{
	// select the current background
	for (int i = 0 ; i < m_lbBackground.GetCount() ; i++)
	{
		if(m_lbBackground.GetItemData(i) == theApp.m_clientBkgndId)
		{
			m_lbBackground.SetCurSel(i);
			SetBitmap(theApp.m_clientBkgndId);
		}
	}

	CButton *pTile = (CButton*)GetDlgItem(IDC_DO_TILE);
	CButton *pCentre = (CButton*)GetDlgItem(IDC_DO_CENTRE);
	if (theApp.m_useTile)
		pTile->SetCheck(1);
	else
		pCentre->SetCheck(1);

	m_useBackgroundFile = theApp.m_useFileForBkgnd;	
	m_backgroundFile = theApp.m_clientBkgndFilename;

	if (theApp.m_useFileForBkgnd)
	{
		m_edtBackgroundFile.EnableWindow(TRUE);
		m_btnFilePath.EnableWindow(TRUE);
	}
	else
	{
		m_edtBackgroundFile.EnableWindow(FALSE);
		m_btnFilePath.EnableWindow(FALSE);
	}

	UpdateData(FALSE);

	return CPropertyPage::OnSetActive();
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::OnInitDialog
// Description	    : 
// Return type		: BOOL 
//
///////////////////////////////////////////////////////////////////////////////
BOOL CDisplayOptionsPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	int index;
	index = m_lbBackground.AddString("<none>");
	m_lbBackground.SetItemData(index, 0);
	index = m_lbBackground.AddString("Dark Blue");
	m_lbBackground.SetItemData(index, IDB_BACK_BLUE);
	index = m_lbBackground.AddString("Green Marble");
	m_lbBackground.SetItemData(index, IDB_BACK_GREENMARBLE);
	index = m_lbBackground.AddString("Grey Marble");
	m_lbBackground.SetItemData(index, IDB_BACK_GREYMARBLE);
	index = m_lbBackground.AddString("Pink Marble");
	m_lbBackground.SetItemData(index, IDB_BACK_PINKMARBLE);
	index = m_lbBackground.AddString("Grey Stone");
	m_lbBackground.SetItemData(index, IDB_BACK_STONE);

//	m_btnBackgroundColor.AttachButton(IDC_DO_COLOR, this);
//	m_btnBackgroundColor.SetColor(theApp.m_clientBkgndRGB);
//	m_btnBackgroundColor.SetOtherButton(TRUE);
//	m_btnBackgroundColor.SetPaletteRealization(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::OnDoFilepath
// Description	    : 
// Return type		: void 
//
///////////////////////////////////////////////////////////////////////////////
void CDisplayOptionsPage::OnDoFilepath() 
{
	CFileDialog	dlg(TRUE);
	dlg.m_ofn.lpstrFilter = "Bitmap\0*.bmp\0\0";
	dlg.m_ofn.nFilterIndex = 0;
	if (dlg.DoModal() == IDOK)
	{
		m_backgroundFile = dlg.GetPathName();
		UpdateData(FALSE);
		SetModified(TRUE);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::OnDoUsefile
// Description	    : 
// Return type		: void 
//
///////////////////////////////////////////////////////////////////////////////
void CDisplayOptionsPage::OnDoUsefile() 
{
	if (m_btnUseBackgroundFile.GetCheck())
	{
		m_edtBackgroundFile.EnableWindow(TRUE);
		m_btnFilePath.EnableWindow(TRUE);
	}
	else
	{
		m_edtBackgroundFile.EnableWindow(FALSE);
		m_btnFilePath.EnableWindow(FALSE);
	}
	SetModified(TRUE);
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::OnSelchangeDoBkgnd
// Description	    : 
// Return type		: void 
//
///////////////////////////////////////////////////////////////////////////////
void CDisplayOptionsPage::OnSelchangeDoBkgnd() 
{
	int index = m_lbBackground.GetCurSel();
	UINT nID = m_lbBackground.GetItemData(index);


	SetBitmap(nID);

	SetModified(TRUE);

	Invalidate();
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::SetBitmap
// Description	    : 
// Return type		: BOOL 
//
///////////////////////////////////////////////////////////////////////////////
// Argument         : UINT nID
///////////////////////////////////////////////////////////////////////////////
BOOL CDisplayOptionsPage::SetBitmap(UINT nID)
{
	LockWindowUpdate();

	if (m_hBitmap)
	{
		::DeleteObject(m_hBitmap);
		m_hBitmap = 0;
	}
	if (m_hPal)
	{
		::DeleteObject(m_hPal);
		m_hPal = 0;
	}

	HRSRC hRes = ::FindResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(nID),RT_BITMAP);

	if (!hRes)
	{
		UnlockWindowUpdate();
		return FALSE;
	}

	HGLOBAL hGbl = ::LoadResource(AfxGetInstanceHandle(), hRes);
	LPBITMAPINFOHEADER lpBMIH = (LPBITMAPINFOHEADER)::LockResource(hGbl);

	int numColors = (WORD)lpBMIH->biClrUsed;
	if (numColors == 0)
		numColors = 256;

	NPLOGPALETTE npPal = (NPLOGPALETTE)LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) + 
				numColors * sizeof(PALETTEENTRY));

	npPal->palVersion = 0x300;
    npPal->palNumEntries = numColors;

	RGBQUAD FAR *lpRGB = (RGBQUAD FAR *)((LPSTR)lpBMIH + lpBMIH->biSize);

    for (WORD i = 0; i < numColors; i++, lpRGB++)
	{
	    npPal->palPalEntry[i].peRed = lpRGB->rgbRed;
	    npPal->palPalEntry[i].peGreen = lpRGB->rgbGreen;
	    npPal->palPalEntry[i].peBlue = lpRGB->rgbBlue;
	    npPal->palPalEntry[i].peFlags = 0;
	}

	m_hPal = ::CreatePalette((LPLOGPALETTE)npPal);
	LocalFree((HLOCAL)npPal);

    HDC hDC = ::GetDC(NULL);
    HPALETTE hOldPal = SelectPalette(hDC, m_hPal, FALSE);
    RealizePalette(hDC);

	LPSTR lpDIBBits = ((char*)lpBMIH + sizeof(BITMAPINFOHEADER) +  numColors * sizeof(RGBQUAD));

	m_hBitmap = ::CreateDIBitmap(hDC, (LPBITMAPINFOHEADER)lpBMIH, CBM_INIT,
            lpDIBBits, (LPBITMAPINFO)lpBMIH, DIB_RGB_COLORS);

	m_width = lpBMIH->biWidth;
	m_height = lpBMIH->biHeight;

    SelectPalette(hDC, hOldPal, FALSE);
    ::ReleaseDC(NULL, hDC);

	UnlockWindowUpdate();

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::OnPaint
// Description	    : 
// Return type		: void 
//
///////////////////////////////////////////////////////////////////////////////
void CDisplayOptionsPage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	m_preview.GetClientRect(&rect);

	if (m_hBitmap)
	{
		HDC dcMem;
		dcMem = ::CreateCompatibleDC(0);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(dcMem, m_hBitmap);

		HPALETTE hOldPal = SelectPalette(dc.m_hDC, m_hPal, FALSE);
		RealizePalette(dc.m_hDC);

		CPoint pt(rect.left, rect.top);
		m_preview.ClientToScreen(&pt); // Convert our coords to screen coords.
		ScreenToClient(&pt); // Convert to parent's coords.

		if (m_width > 2*rect.Width())
		{
			// We'll do a stretch blt instead
			StretchBlt(dc.m_hDC, pt.x, pt.y, rect.Width(), rect.Height(), 
						dcMem, 0, 0, m_width, m_height, SRCCOPY);		
		}
		else
			for (int nX = 0; nX < rect.Width(); nX += m_width)
				for (int nY = 0; nY < rect.Height(); nY += m_height)
					BitBlt(dc.m_hDC, pt.x + nX, pt.y + nY, 
						   rect.Width() - nX*m_width, 
						   rect.Height() - nY*m_height, dcMem, 0, 0, SRCCOPY);

		SelectPalette(dc.m_hDC, hOldPal, FALSE);
		SelectObject(dcMem, oldBitmap);
	}

}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::OnApply
// Description	    : 
// Return type		: BOOL 
//
///////////////////////////////////////////////////////////////////////////////
BOOL CDisplayOptionsPage::OnApply() 
{
	UpdateData();

	UINT nID = m_lbBackground.GetItemData(m_lbBackground.GetCurSel());
	if (nID != LB_ERR)
		theApp.m_clientBkgndId = nID;

//	theApp.m_clientBkgndRGB = m_btnBackgroundColor.GetColor();
	
	CButton *pTile = (CButton*)GetDlgItem(IDC_DO_TILE);
	if (pTile->GetCheck() == 1)
		theApp.m_useTile = TRUE;
	else
		theApp.m_useTile = FALSE;

	theApp.m_useFileForBkgnd = m_useBackgroundFile;	
	theApp.m_clientBkgndFilename = m_backgroundFile;

	CMainFrame *pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->UpdateClientBackground();

	SetModified(FALSE);

	return CPropertyPage::OnApply();
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CDisplayOptionsPage::OnModify
// Description	    : 
// Return type		: void 
//
///////////////////////////////////////////////////////////////////////////////
void CDisplayOptionsPage::OnModify() 
{
	SetModified(TRUE);	
}
