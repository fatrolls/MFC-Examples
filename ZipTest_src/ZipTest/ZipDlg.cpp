// ZipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZipTest.h"
#include "ZipDlg.h"

#include "..\zipunzip\zipper.h"
#include "..\shared\folderdialog.h"
#include "..\shared\filemisc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZipDlg dialog


CZipDlg::CZipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZipDlg)
	m_sFilePath = _T("");
	m_sFolderPath = _T("");
	m_nFileCount = 0;
	m_nFolderCount = 0;
	m_bIgnorePath = FALSE;
	m_nTotalCompSize = 0;
	m_nTotalUncompSize = 0;
	m_bAddToZip = TRUE;
	//}}AFX_DATA_INIT
}


void CZipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZipDlg)
	DDX_Text(pDX, IDC_FILEPATH, m_sFilePath);
	DDX_Text(pDX, IDC_FOLDERPATH, m_sFolderPath);
	DDX_Text(pDX, IDC_FILECOUNT2, m_nFileCount);
	DDX_Text(pDX, IDC_FOLDERCOUNT2, m_nFolderCount);
	DDX_Check(pDX, IDC_IGNOREPATHINFO2, m_bIgnorePath);
	DDX_Text(pDX, IDC_TOTALCOMPSIZE2, m_nTotalCompSize);
	DDX_Text(pDX, IDC_TOTALUNCOMPSIZE2, m_nTotalUncompSize);
	DDX_Check(pDX, IDC_ADDTOZIP, m_bAddToZip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZipDlg, CDialog)
	//{{AFX_MSG_MAP(CZipDlg)
	ON_BN_CLICKED(IDC_BROWSEFILE, OnBrowsefile)
	ON_BN_CLICKED(IDC_BROWSEFOLDER, OnBrowsefolder)
	ON_BN_CLICKED(IDC_ZIP, OnZip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZipDlg message handlers

void CZipDlg::OnBrowsefile() 
{
	UpdateData();

	CFileDialog dialog(TRUE, NULL, m_sFilePath, 0, "All Files (*.*)|*.*||", this);

	if (dialog.DoModal() == IDOK)
	{
		m_sFilePath = dialog.GetFileName();
		m_sFolderPath.Empty();
		UpdateData(FALSE);
	}
}

void CZipDlg::OnBrowsefolder() 
{
	CFolderDialog dialog("Select Folder to Zip", m_sFolderPath, this, BIF_RETURNONLYFSDIRS | BIF_BROWSENOROOTDIR);

	if (dialog.DoModal() == IDOK)
	{
		m_sFolderPath = dialog.GetFolderPath();
		m_sFilePath.Empty();
		UpdateData(FALSE);
	}
}

void CZipDlg::OnZip() 
{
	UpdateData();

	CZipper zip;
	BOOL bRes = FALSE;
	CString sZipPath;

	if (!m_sFilePath.IsEmpty())
	{
		char szDrive[_MAX_DRIVE], szFolder[MAX_PATH], szName[_MAX_FNAME];
		_splitpath(m_sFilePath, szDrive, szFolder, szName, NULL);

		char szZipPath[MAX_PATH];
		_makepath(szZipPath, szDrive, szFolder, szName, "zip");

		CWaitCursor cursor;

		if (zip.OpenZip(szZipPath, NULL, m_bAddToZip == TRUE))
			bRes = zip.AddFileToZip(m_sFilePath);

		sZipPath = szZipPath;
	}	
	else if (!m_sFolderPath.IsEmpty())
	{
		sZipPath = m_sFolderPath + ".zip";

		CWaitCursor cursor;

		bRes = CZipper::ZipFolder(m_sFolderPath, m_bIgnorePath == TRUE);
//		if (zip.OpenZip(sZipPath, NULL, m_bAddToZip == TRUE))
//			bRes = zip.AddFolderToZip(m_sFolderPath, m_bIgnorePath == TRUE);
	}

	zip.CloseZip();

	if (bRes)
	{
		Z_FileInfo zi;
		zip.GetFileInfo(zi);

		m_nFileCount = zi.nFileCount;
		m_nFolderCount = zi.nFolderCount;
		m_nTotalUncompSize = zi.dwUncompressedSize;
		m_nTotalCompSize = (DWORD)GetFileSize(sZipPath);
	}
	else
	{
		m_nFileCount = 0;
		m_nFolderCount = 0;
		m_nTotalUncompSize = 0;
		m_nTotalCompSize = 0;
	}

	UpdateData(FALSE);
}
