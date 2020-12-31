#ifndef INC_FTPFILETREECTRL_H
#define INC_FTPFILETREECTRL_H

#include "ShellImageList.h"
#include "FTPClient.h"

namespace nsFTP
{
namespace nsView
{

/// @brief Displays the filetree on a ftp-server.
class CFTPFileTreeCtrl : public CTreeCtrl
{
   DECLARE_MESSAGE_MAP()
   DECLARE_DYNAMIC(CFTPFileTreeCtrl)
public:
   CFTPFileTreeCtrl();
   virtual ~CFTPFileTreeCtrl();

public:
   bool    SetSelectedPath(const CString& cszPath);
   CString GetFullPath(HTREEITEM hItem) const;
   bool    DisplayTree(nsFTP::CFTPClient* pFTP, const CString& cszDisplayName=_T(""), const CString& cszRoot=_T(""), bool fFiles=false);

   protected:
   virtual void PreSubclassWindow();

private:
   CString GetSubPath(const CString& cszPath);
   HTREEITEM SearchChildItem(HTREEITEM hItem, const CString& cszText);
   HTREEITEM AddItem(HTREEITEM hParent, const CString& cszPath, const bool fDir);
   void DisplayPath( HTREEITEM hParent);
   void GetDirectoryListing(HTREEITEM hItem, nsFTP::TFTPFileStatusShPtrVec& vFileList) const;

   afx_msg void OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult);

private:
   struct SRootInfo
   {
      SRootInfo() : m_htiRoot(NULL) {};
      CString                       m_cszRoot;
      CString                       m_cszDisplayName;
      HTREEITEM                     m_htiRoot;
   } m_RootInfo;

   CFTPClient*                      m_pFTP;
   bool                             m_fFiles;

   CShellImageList                  m_ShellImageList;
};

};
};

#endif // INC_FTPFILETREECTRL_H
