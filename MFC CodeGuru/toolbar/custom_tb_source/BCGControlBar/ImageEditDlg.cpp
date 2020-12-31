// ImageEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ImageEditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageEditDlg dialog


CImageEditDlg::CImageEditDlg(CBitmap* pBitmap, SIZE sizeImage, CWnd* pParent /*=NULL*/)
	: CDialog(CImageEditDlg::IDD, pParent),
	m_pBitmap (pBitmap),
	m_sizeImage (sizeImage)
{
	ASSERT (m_pBitmap != NULL);

	//{{AFX_DATA_INIT(CImageEditDlg)
	//}}AFX_DATA_INIT
}

void CImageEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageEditDlg)
	DDX_Control(pDX, IDC_PASTE, m_wndPasteButton);
	DDX_Control(pDX, IDC_PREVIEW_AREA, m_wndPreview);
	DDX_Control(pDX, IDC_DRAW_AREA, m_wndLargeDrawArea);
	DDX_Control(pDX, IDC_COLORS, m_wndColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageEditDlg, CDialog)
	//{{AFX_MSG_MAP(CImageEditDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_COLORS, OnColors)
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	ON_BN_CLICKED(IDC_PASTE, OnPaste)
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageEditDlg message handlers

BOOL CImageEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_wndLargeDrawArea.SetBitmap (m_pBitmap);
	
	// Define preview area:
	m_wndPreview.GetClientRect (&m_rectPreviewImage);
	m_wndPreview.MapWindowPoints (this, &m_rectPreviewImage);

	m_rectPreviewImage.left = (m_rectPreviewImage.left + m_rectPreviewImage.right - m_sizeImage.cx) / 2;
	m_rectPreviewImage.right = m_rectPreviewImage.left + m_sizeImage.cx;

	m_rectPreviewImage.top = (m_rectPreviewImage.top + m_rectPreviewImage.bottom - m_sizeImage.cy) / 2;
	m_rectPreviewImage.bottom = m_rectPreviewImage.top + m_sizeImage.cy;

	m_rectPreviewFrame = m_rectPreviewImage;
	m_rectPreviewFrame.InflateRect (4, 4);

	m_wndLargeDrawArea.m_rectParentPreviewArea = m_rectPreviewImage;

	COleDataObject data;
	m_wndPasteButton.EnableWindow (
		data.AttachClipboard () &&
		data.IsDataAvailable (CF_BITMAP));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//********************************************************************************
void CImageEditDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	dc.Draw3dRect (&m_rectPreviewFrame,
					::GetSysColor (COLOR_3DHILIGHT),
					::GetSysColor (COLOR_3DSHADOW));

	CBitmap* pbmOld = NULL;
	CDC dcMem;
		
	dcMem.CreateCompatibleDC (&dc);
	pbmOld = dcMem.SelectObject (m_pBitmap);

	dc.BitBlt (m_rectPreviewImage.left, m_rectPreviewImage.top,
				m_sizeImage.cx, m_sizeImage.cy, &dcMem,
				0, 0, SRCCOPY);

	dcMem.SelectObject(pbmOld);
	dcMem.DeleteDC();
}
//********************************************************************************
void CImageEditDlg::OnClear() 
{
	CWindowDC	dc (this);
	CDC 		memDC;	

	memDC.CreateCompatibleDC (&dc);
	
	CBitmap* pOldBitmap = memDC.SelectObject (m_pBitmap);

	CRect rect (0, 0, m_sizeImage.cx, m_sizeImage.cy);
	memDC.FillSolidRect (&rect, ::GetSysColor (COLOR_3DFACE));

	memDC.SelectObject (pOldBitmap);

	InvalidateRect (m_rectPreviewImage);
	m_wndLargeDrawArea.Invalidate ();
}
//********************************************************************************
void CImageEditDlg::OnColors() 
{
	m_wndLargeDrawArea.m_rgbColor = m_wndColor.GetColor ();
}
//********************************************************************************
void CImageEditDlg::OnCopy() 
{
	if (m_pBitmap == NULL)
	{
		return;
	}

	::OpenClipboard (GetSafeHwnd ());
	::EmptyClipboard ();

	::SetClipboardData (CF_BITMAP, m_pBitmap->GetSafeHandle ());
	::CloseClipboard ();

	COleDataObject data;
	m_wndPasteButton.EnableWindow (
		data.AttachClipboard () &&
		data.IsDataAvailable (CF_BITMAP));
}
//********************************************************************************
void CImageEditDlg::OnPaste() 
{
	COleDataObject data;
	if (!data.AttachClipboard ())
	{
		AfxMessageBox (IDP_CANT_PASTE_BITMAP);
		return;
	}

	if (!data.IsDataAvailable (CF_BITMAP))
	{
		AfxMessageBox (IDP_CANT_PASTE_BITMAP);
		return;
	}

	tagSTGMEDIUM dataMedium;
	if (!data.GetData (CF_BITMAP, &dataMedium))
	{
		AfxMessageBox (IDP_CANT_PASTE_BITMAP);
		return;
	}

	CBitmap* pBmpClip = CBitmap::FromHandle (dataMedium.hBitmap);
	if (pBmpClip == NULL)
	{
		AfxMessageBox (IDP_CANT_PASTE_BITMAP);
		return;
	}

	BITMAP bmp;
	pBmpClip->GetBitmap (&bmp);

	if (bmp.bmWidth != m_sizeImage.cx ||
		bmp.bmHeight != m_sizeImage.cy)
	{
		CString strMessage;
		strMessage.Format (IDS_WRONG_IMAGE_SIZE,
						m_sizeImage.cx, m_sizeImage.cy);
		MessageBox (strMessage);
		return;
	}

	CWindowDC	dc (this);
	CDC 		memDCDst;
	CDC 		memDCSrc;

	memDCSrc.CreateCompatibleDC (&dc);
	memDCDst.CreateCompatibleDC (&dc);
	
	CBitmap* pSrcOldBitmap = memDCSrc.SelectObject (pBmpClip);
	if (pSrcOldBitmap == NULL)
	{
		AfxMessageBox (IDP_CANT_PASTE_BITMAP);
		return;
	}

	CBitmap* pDstOldBitmap = memDCDst.SelectObject (m_pBitmap);
	if (pDstOldBitmap == NULL)
	{
		AfxMessageBox (IDP_CANT_PASTE_BITMAP);
		
		memDCSrc.SelectObject (pSrcOldBitmap);
		return;
	}

	memDCDst.BitBlt (0, 0, m_sizeImage.cx, m_sizeImage.cy,
					&memDCSrc, 0, 0, SRCCOPY);

	memDCDst.SelectObject (pDstOldBitmap);
	memDCSrc.SelectObject (pSrcOldBitmap);

	InvalidateRect (m_rectPreviewImage);
	m_wndLargeDrawArea.Invalidate ();
}
//****************************************************************************************
void CImageEditDlg::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CDialog::OnActivateApp(bActive, hTask);
	
	if (bActive)
	{
		COleDataObject data;
		m_wndPasteButton.EnableWindow (
			data.AttachClipboard () &&
			data.IsDataAvailable (CF_BITMAP));
	}
}
