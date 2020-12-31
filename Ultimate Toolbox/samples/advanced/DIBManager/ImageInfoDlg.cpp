// ImageInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dibmanager.h"
#include "ImageInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageInfoDlg dialog


CImageInfoDlg::CImageInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageInfoDlg)
	m_sFileName = _T("");
	m_sFileSize = _T("");
	m_sFileStatus = _T("");
	m_sFormat = _T("");
	m_sHeight = _T("");
	m_sSizeInMemory = _T("");
	m_sType = _T("");
	m_sWidth = _T("");
	//}}AFX_DATA_INIT
}


void CImageInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageInfoDlg)
	DDX_Control(pDX, IDC_FILE_STATUS, m_ctlStaticFileStatus);
	DDX_Text(pDX, IDC_FILE_NAME, m_sFileName);
	DDX_Text(pDX, IDC_FILE_SIZE, m_sFileSize);
	DDX_Text(pDX, IDC_FILE_STATUS, m_sFileStatus);
	DDX_Text(pDX, IDC_FORMAT, m_sFormat);
	DDX_Text(pDX, IDC_HEIGHT, m_sHeight);
	DDX_Text(pDX, IDC_SIZE_IN_MEMORY, m_sSizeInMemory);
	DDX_Text(pDX, IDC_TYPE, m_sType);
	DDX_Text(pDX, IDC_WIDTH, m_sWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CImageInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageInfoDlg message handlers

BOOL CImageInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	// get the name of current file
	m_sFileName=pDoc->m_sNameFile;

	// get the length in bytes of current image on disk
	DWORD dwSize=pDoc->m_dwImageSize;
	// if length in bytes is less than 1 kilobyte then show it in bytes
	// otherwise in kilobytes
	if(dwSize<1024)
	{
		m_sFileSize.Format(_T("%u byte%s"),dwSize,dwSize>1 ? "s" : "");
	}
	else
	{
		m_sFileSize.Format(_T("%u.%1u KB"),dwSize/1024,((dwSize%1024)*10)/1024);
	}

	// get the length in bytes of current image in memory
	DWORD dwSizeInMemory=pDoc->CalcDIBSizeInMemory();
	// if length in bytes is less than 1 kilobyte then show it in bytes
	// otherwise in kilobytes
	if(dwSizeInMemory<1024)
	{
		m_sSizeInMemory.Format(_T("%u byte%s"),dwSizeInMemory,
			dwSizeInMemory>1 ? "s" : "");
	}
	else
	{
		m_sSizeInMemory.Format(_T("%u.%1u KB"),dwSizeInMemory/1024,
			((dwSizeInMemory%1024)*10)/1024);
	}

	// define if document is dirty
	m_sFileStatus.Format(_T("Image has %schanged"),
		pDoc->IsModified() ? _T("") : _T("not ")) ;

	// get image format
	m_sFormat=pDoc->m_tf==CDIBManagerDoc::TF_DIB ? 
		_T("Windows Bitmap") : _T("JPEG Bitmap");

	// get height and width in pixels
	CSize sizeDIB=pDoc->m_dib.GetSize();
	m_sHeight.Format(_T("%u pixel%s"),sizeDIB.cy, sizeDIB.cy>1 ? _T("s") : _T(""));
	m_sWidth.Format(_T("%u pixel%s"),sizeDIB.cx, sizeDIB.cx>1 ? _T("s") : _T(""));

	// define the number of colors used in DIB
	switch(pDoc->m_dib.GetNumBitsPerPixel())
	{
	case 1:
		{
			m_sType=_T("Black & White (1-bit)");
			break;
		}
	case 4:
		{
			m_sType=_T("16 Color (4-bit)");
			break;
		}
	case 8:
		{
			m_sType=_T("256 Color (8-bit)");
			break;
		}
	case 24:
		{
			m_sType=_T("RGB Color (24-bit)");
			break;
		}
	}

 	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
