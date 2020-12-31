// UnzipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "UnzipDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnzipDlg dialog

CUnzipDlg::CUnzipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnzipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUnzipDlg)
	m_sZipPath = _T("");
	m_nFileCount = 0;
	m_nFolderCount = 0;
	m_nTotalCompSize = 0;
	m_nTotalUncompSize = 0;
	m_sFileExt = _T("");
	m_bIgnorePath = FALSE;
	//}}AFX_DATA_INIT
}

void CUnzipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnzipDlg)
	DDX_Control(pDX, IDC_DETAILS, m_lcDetails);
	DDX_Text(pDX, IDC_ZIPFILE, m_sZipPath);
	DDX_Text(pDX, IDC_FILECOUNT, m_nFileCount);
	DDX_Text(pDX, IDC_FOLDERCOUNT, m_nFolderCount);
	DDX_Text(pDX, IDC_TOTALCOMPSIZE, m_nTotalCompSize);
	DDX_Text(pDX, IDC_TOTALUNCOMPSIZE, m_nTotalUncompSize);
	DDX_Text(pDX, IDC_FILEEXT, m_sFileExt);
	DDX_Check(pDX, IDC_IGNOREPATHINFO, m_bIgnorePath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUnzipDlg, CDialog)
	//{{AFX_MSG_MAP(CUnzipDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_UNZIP, OnUnzip)
	ON_BN_CLICKED(IDC_UPDATEDETAILS, OnUpdatedetails)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnzipDlg message handlers

BOOL CUnzipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// setup the details columns
	m_lcDetails.InsertColumn(0, "Filename", LVCFMT_LEFT, 200);
	m_lcDetails.InsertColumn(1, "Type", LVCFMT_LEFT, 80);
	m_lcDetails.InsertColumn(2, "Compressed Size", LVCFMT_LEFT, 80);
	m_lcDetails.InsertColumn(3, "Uncompressed Size", LVCFMT_LEFT, 80);
	m_lcDetails.InsertColumn(4, "CRC", LVCFMT_LEFT, 80);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUnzipDlg::OnBrowse() 
{
	UpdateData();

	CFileDialog dialog(TRUE, "zip", m_sZipPath, 0, "Zip Files (*.zip)|*.zip||", this);

	if (dialog.DoModal() == IDOK)
	{
		if (!m_uz.OpenZip(dialog.GetPathName()))
		{
			AfxMessageBox("Not a valid zip file");
			return;
		}
		
		m_sZipPath = dialog.GetPathName();
		UpdateData(FALSE);
	}

	ShowDetails();
}

void CUnzipDlg::OnUnzip() 
{
	DWORD dwTick = GetTickCount();

	UpdateData();

	if (!m_uz.Unzip(m_bIgnorePath == TRUE))
		AfxMessageBox("Unable to unzip file");
	else
		TRACE ("Unzip took %.02f s for %d files", (GetTickCount() - dwTick) / 1000.0f, m_nFileCount);
}

void CUnzipDlg::ShowDetails() 
{
	UpdateData();

	m_lcDetails.DeleteAllItems();

	m_lcDetails.SetItemCount(m_uz.GetFileCount());
	m_lcDetails.UpdateWindow();

	m_nTotalCompSize = 0;
	m_nTotalUncompSize = 0;
	m_nFileCount = 0;
	m_nFolderCount = 0;

	if (m_uz.GotoFirstFile(m_sFileExt))
	{
		do
		{
			UZ_FileInfo info;
			m_uz.GetFileInfo(info);

			CString sText(info.szFileName);
			sText.MakeLower();

			int nIndex = m_lcDetails.InsertItem(m_lcDetails.GetItemCount(), sText);

			m_lcDetails.SetItemText(nIndex, 1, info.bFolder ? "Folder" : "File");

			if (!info.bFolder)
			{
				sText.Format("%d", info.dwCompressedSize);
				m_lcDetails.SetItemText(nIndex, 2, sText);

				sText.Format("%d", info.dwUncompressedSize);
				m_lcDetails.SetItemText(nIndex, 3, sText);

				sText.Format("%08x", info.dwCRC);
				m_lcDetails.SetItemText(nIndex, 4, sText);

				m_nFileCount++;
			}
			else
				m_nFolderCount++;

			m_lcDetails.UpdateWindow();

			m_nTotalCompSize += info.dwCompressedSize;
			m_nTotalUncompSize += info.dwUncompressedSize;

			UpdateData(FALSE);
			UpdateWindow();
		}
		while (m_uz.GotoNextFile(m_sFileExt));
	}
}

void CUnzipDlg::OnUpdatedetails() 
{
	UpdateData();

	ShowDetails();
}
