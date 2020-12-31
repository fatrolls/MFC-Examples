
#include "stdafx.h"
#include "FTPexample.h"
#include "FTPBrowseForFileAndFolder.h"

using namespace nsFTP;
using namespace nsFTP::nsView;

BEGIN_MESSAGE_MAP(CFTPBrowseForFileAndFolderDlg, CDialog)
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CFTPBrowseForFileAndFolderDlg, CDialog)
CFTPBrowseForFileAndFolderDlg::CFTPBrowseForFileAndFolderDlg(CWnd* pParent /*=NULL*/) :
   CDialog(CFTPBrowseForFileAndFolderDlg::IDD, pParent),
   m_fFiles(false)
{
}

CFTPBrowseForFileAndFolderDlg::~CFTPBrowseForFileAndFolderDlg()
{
}

void CFTPBrowseForFileAndFolderDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_FTP_TREE, m_ctrlFtpTree);
}

BOOL CFTPBrowseForFileAndFolderDlg::OnInitDialog()
{
   CDialog::OnInitDialog();
   m_ctrlFtpTree.DisplayTree(m_pFTP, m_pFTP->LastLogonInfo().Hostname().c_str(), _T("/"), m_fFiles);

   return TRUE;
}

INT_PTR CFTPBrowseForFileAndFolderDlg::DoModal(nsFTP::CFTPClient* pFTP, bool fFiles)
{
   m_pFTP = pFTP;
   m_fFiles = fFiles;
   return CDialog::DoModal();
}

CString CFTPBrowseForFileAndFolderDlg::GetFullPath() const
{
   return m_cszFullPath;
}

void CFTPBrowseForFileAndFolderDlg::OnOK()
{
   m_cszFullPath = m_ctrlFtpTree.GetFullPath(m_ctrlFtpTree.GetSelectedItem());
   CDialog::OnOK();
}
