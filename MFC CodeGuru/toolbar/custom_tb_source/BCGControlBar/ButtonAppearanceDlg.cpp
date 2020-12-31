// ButtonAppearanceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ButtonAppearanceDlg.h"
#include "BCGToolBarImages.h"
#include "BCGToolbarButton.h"
#include "ImageEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonAppearanceDlg dialog


CButtonAppearanceDlg::CButtonAppearanceDlg(
	CBCGToolbarButton* pButton,
	CBCGToolBarImages* pImages,
	CWnd* pParent,
	int iStartImage)
	: CDialog(CButtonAppearanceDlg::IDD, pParent),
	m_pButton (pButton),
	m_pImages (pImages),
	m_iStartImage (iStartImage),
	m_bImage (TRUE),
	m_bText (FALSE)
{
	ASSERT_VALID(m_pButton);
	ASSERT (m_pImages != NULL);

	m_iSelImage = pButton->m_iImage;
	
	m_bImage = pButton->m_bImage;
	m_bText = pButton->m_bText;

	//{{AFX_DATA_INIT(CButtonAppearanceDlg)
	m_strButtonText = _T("");
	m_strButtonDescr = _T("");
	//}}AFX_DATA_INIT
}

CButtonAppearanceDlg::~CButtonAppearanceDlg ()
{
	while (!m_Buttons.IsEmpty ())
	{
		delete m_Buttons.RemoveHead ();
	}	
}

void CButtonAppearanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButtonAppearanceDlg)
	DDX_Control(pDX, IDC_BUTTON_TEXT, m_wndButtonText);
	DDX_Control(pDX, IDC_ADD_IMAGE, m_wndAddImage);
	DDX_Control(pDX, IDC_IMAGE_LIST, m_wndButtonList);
	DDX_Control(pDX, IDC_EDIT_IMAGE, m_wndEditImage);
	DDX_Text(pDX, IDC_BUTTON_TEXT, m_strButtonText);
	DDX_Text(pDX, IDC_BUTTON_DESCR, m_strButtonDescr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CButtonAppearanceDlg, CDialog)
	//{{AFX_MSG_MAP(CButtonAppearanceDlg)
	ON_BN_CLICKED(IDC_ADD_IMAGE, OnAddImage)
	ON_BN_CLICKED(IDC_EDIT_IMAGE, OnEditImage)
	ON_BN_CLICKED(IDC_IMAGE_LIST, OnImageList)
	ON_BN_CLICKED(IDC_IMAGE, OnImage)
	ON_BN_CLICKED(IDC_IMAGE_TEXT, OnImageText)
	ON_BN_CLICKED(IDC_TEXT, OnText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonAppearanceDlg message handlers

void CButtonAppearanceDlg::OnAddImage() 
{
	ASSERT (m_pImages != NULL);
	CSize sizeImage = m_pImages->GetImageSize ();

	CWindowDC	dc (&m_wndButtonList);
	CBitmap 	bitmap;
	CDC 		memDC;	

	memDC.CreateCompatibleDC(&dc);
	
	if (!bitmap.CreateCompatibleBitmap (&dc, sizeImage.cx, sizeImage.cy))
	{
		AfxMessageBox (IDP_CANNT_CREATE_IMAGE);
		return;
	}

	CBitmap* pOldBitmap = memDC.SelectObject (&bitmap);

	CRect rect (0, 0, sizeImage.cx, sizeImage.cy);
	memDC.FillSolidRect (&rect, ::GetSysColor (COLOR_3DFACE));

	memDC.SelectObject (pOldBitmap);

	CImageEditDlg dlg (&bitmap, sizeImage, this);
	if (dlg.DoModal () != IDOK)
	{
		return;
	}

	int iImageIndex = m_pImages->AddImage ((HBITMAP) bitmap);
	if (iImageIndex < 0)
	{
		AfxMessageBox (IDP_CANNT_CREATE_IMAGE);
		return;
	}

	RebuildImageList ();
	m_wndButtonList.SelectButton (iImageIndex);
}
//********************************************************************************
void CButtonAppearanceDlg::OnEditImage() 
{
	ASSERT (m_pImages != NULL);
	ASSERT (m_iSelImage >= 0);

	CSize sizeImage = m_pImages->GetImageSize ();

	CWindowDC	dc (&m_wndButtonList);
	CBitmap 	bitmap;
	CDC 		memDC;
	memDC.CreateCompatibleDC(&dc);
	
	if (!bitmap.CreateCompatibleBitmap (&dc, sizeImage.cx, sizeImage.cy))
	{
		return;
	}

	CBitmap* pOldBitmap = memDC.SelectObject (&bitmap);

	CBCGDrawState ds;
	if (!m_pImages->PrepareDrawImage (ds))
	{
		return;
	}
	m_pImages->Draw (&memDC, 0, 0, CPoint (0, 0), m_iSelImage);
	m_pImages->EndDrawImage (ds);

	memDC.SelectObject (pOldBitmap);

	CImageEditDlg dlg (&bitmap, sizeImage, this);
	if (dlg.DoModal () != IDOK)
	{
		return;
	}

	m_pImages->UpdateImage (m_iSelImage, (HBITMAP) bitmap);
	m_wndButtonList.Invalidate ();
}
//********************************************************************************
void CButtonAppearanceDlg::OnImageList() 
{
	CBCGToolbarButton* pSelButton = m_wndButtonList.GetSelectedButton ();
	m_iSelImage = (pSelButton == NULL) ? -1 : pSelButton->m_iImage;

	m_wndEditImage.EnableWindow (m_iSelImage >= 0);
}
//********************************************************************************
void CButtonAppearanceDlg::OnImage() 
{
	m_bImage = TRUE;
	m_bText = FALSE;

	EnableControls ();
}
//********************************************************************************
void CButtonAppearanceDlg::OnImageText() 
{
	m_bImage = TRUE;
	m_bText = TRUE;

	EnableControls ();
}
//********************************************************************************
void CButtonAppearanceDlg::OnText() 
{
	m_bImage = FALSE;
	m_bText = TRUE;

	EnableControls ();
}
//********************************************************************************
void CButtonAppearanceDlg::OnOK() 
{
	UpdateData ();

	if (m_bImage && m_iSelImage < 0)
	{
		AfxMessageBox (IDP_IMAGE_IS_REQUIRED);
		return;
	}

	if (m_bText && m_strButtonText.IsEmpty ())
	{
		AfxMessageBox (IDP_TEXT_IS_REQUIRED);
		m_wndButtonText.SetFocus ();
		return;
	}

	m_pButton->m_bText = m_bText;
	m_pButton->m_iImage = m_iSelImage;
	m_pButton->m_bImage = m_bImage;
	m_pButton->m_strText = m_strButtonText;

	CDialog::OnOK();
}
//********************************************************************************
BOOL CButtonAppearanceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT (m_pImages != NULL);

	m_wndButtonList.SetImages (m_pImages);
	RebuildImageList ();
	m_wndButtonList.SelectButton (m_iSelImage);

	if (m_bImage)
	{
		if (m_bText)
		{
			CheckDlgButton (IDC_IMAGE_TEXT, TRUE);
		}
		else
		{
			CheckDlgButton (IDC_IMAGE, TRUE);
		}
	}
	else
	{
		ASSERT (m_bText);
		CheckDlgButton (IDC_TEXT, TRUE);
		m_bText = TRUE;

		m_wndButtonList.EnableWindow (FALSE);
	}

	m_strButtonText = m_pButton->m_strText;

	CFrameWnd* pWndFrame = GetParentFrame ();
	if (pWndFrame != NULL)
	{
		pWndFrame->GetMessageString (m_pButton->m_nID,
						m_strButtonDescr);
	}

	EnableControls ();	
	UpdateData (FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//********************************************************************************
void CButtonAppearanceDlg::RebuildImageList ()
{
	while (!m_Buttons.IsEmpty ())
	{
		delete m_Buttons.RemoveHead ();
	}

	m_wndButtonList.RemoveButtons ();

	int iEnd = m_pImages->GetCount () - 1;
	for (int iImage = m_iStartImage; iImage <= iEnd; iImage ++)
	{
		CBCGToolbarButton* pButton = new CBCGToolbarButton;

		pButton->m_iImage = iImage;

		m_wndButtonList.AddButton (pButton);
		m_Buttons.AddTail (pButton);
	}

	m_wndButtonList.Invalidate ();
}
//********************************************************************************
void CButtonAppearanceDlg::EnableControls ()
{
	m_wndButtonList.EnableWindow (m_bImage);

	m_wndAddImage.EnableWindow (m_bImage);
	m_wndEditImage.EnableWindow (m_bImage);

	m_wndButtonText.EnableWindow (m_bText);
}
