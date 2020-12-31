#pragma once

#include "FTPClient.h"
#include "FTPFileTreeCtrl.h"

namespace nsFTP
{
namespace nsView
{

class CFTPBrowseForFileAndFolderDlg : public CDialog
{
   DECLARE_MESSAGE_MAP()
   DECLARE_DYNAMIC(CFTPBrowseForFileAndFolderDlg)
   enum { IDD = IDD_FTP_DLG_BROWSE };
public:
   CFTPBrowseForFileAndFolderDlg(CWnd* pParent = NULL);
   virtual ~CFTPBrowseForFileAndFolderDlg();

   INT_PTR DoModal(nsFTP::CFTPClient* pFTP, bool fFiles=false);
   CString GetFullPath() const;

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();
   void    OnOK();

private:
   nsFTP::CFTPClient*               m_pFTP;
   nsFTP::nsView::CFTPFileTreeCtrl  m_ctrlFtpTree;
   CString                          m_cszFullPath;
   bool                             m_fFiles;
};

};
};