#include "stdafx.h"
#include "FTPFileTreeCtrl.h"
#include "resource.h"

using namespace nsFTP;
using namespace nsFTP::nsView;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CFTPFileTreeCtrl, CTreeCtrl)

BEGIN_MESSAGE_MAP(CFTPFileTreeCtrl, CTreeCtrl)
   ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
END_MESSAGE_MAP()

CFTPFileTreeCtrl::CFTPFileTreeCtrl() :
   m_pFTP(NULL),
   m_fFiles(false),
   m_ShellImageList(true, false)
{
}

CFTPFileTreeCtrl::~CFTPFileTreeCtrl()
{
}

bool CFTPFileTreeCtrl::DisplayTree(CFTPClient* pFTP, const CString& cszDisplayName, const CString& cszRootDir, bool fFiles)
{
   ASSERT( pFTP );

   m_pFTP = pFTP;

   m_fFiles  = fFiles;

   DeleteAllItems();

   m_RootInfo.m_cszRoot        = cszRootDir;
   m_RootInfo.m_cszDisplayName = cszDisplayName + _T(" ") + cszRootDir;

   m_RootInfo.m_htiRoot = AddItem(TVI_ROOT, cszDisplayName, true);
   DisplayPath(m_RootInfo.m_htiRoot);
   Expand(m_RootInfo.m_htiRoot, TVE_EXPAND);
   SelectItem(m_RootInfo.m_htiRoot);

   return true;   
}

void CFTPFileTreeCtrl::DisplayPath(HTREEITEM hParent)
{
   CWaitCursor wait;

   TFTPFileStatusShPtrVec vFileList;
   GetDirectoryListing(hParent, vFileList);

   SetRedraw(false);

   std::sort(vFileList.begin(), vFileList.end(), CFTPFileStatusContainerSort(CFTPFileStatusContainerSort::CName(), true, true));

   for( TFTPFileStatusShPtrVec::iterator it = vFileList.begin(); it!=vFileList.end(); it++ )
   {
      if( (*it)->IsCwdPossible() )
      {
         if( !(*it)->IsDot() )
         {
            HTREEITEM hItem = AddItem(hParent, (*it)->Name().c_str(), true);
            // insert dummy element for displaying plus sign
            InsertItem(_T(""), 0, 0, hItem); 
         }
      }
      else if( m_fFiles )
      {
         AddItem(hParent, (*it)->Name().c_str(), false);
      }
   }

   SetRedraw();
}

void CFTPFileTreeCtrl::GetDirectoryListing(HTREEITEM hItem, TFTPFileStatusShPtrVec& vFileList) const
{
   ASSERT( m_pFTP );
   if( m_RootInfo.m_htiRoot == hItem )
      m_pFTP->List(static_cast<LPCTSTR>(m_RootInfo.m_cszRoot), vFileList);
   else
      m_pFTP->List(static_cast<LPCTSTR>(GetFullPath(hItem)), vFileList);
}

HTREEITEM CFTPFileTreeCtrl::AddItem(HTREEITEM hParent, const CString& cszPath, const bool fDir)
{
   int iIcon = 0;
   int iIconSel = 0;

   if( fDir )
   {
      iIcon    = m_ShellImageList.GetFolderIcon(false, true);
      iIconSel = m_ShellImageList.GetFolderIcon(true, true);
   }
   else
   {
      iIcon    = m_ShellImageList.GetImageForExtension(cszPath, true);
      iIconSel = iIcon;
   }

   if( hParent==TVI_ROOT )
      return InsertItem(cszPath, iIcon, iIconSel, hParent);

   return InsertItem(GetSubPath(cszPath), iIcon, iIconSel, hParent);
}

CString CFTPFileTreeCtrl::GetSubPath(const CString& cszPath)
{
   CString cszTemp(cszPath);

   cszTemp.TrimRight(_T('/'));
   int iPos = cszTemp.ReverseFind(_T('/'));
   if( iPos != -1 )
      cszTemp = cszTemp.Mid(iPos + 1);

   return cszTemp;
}

void CFTPFileTreeCtrl::OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
   NM_TREEVIEW* pNMTreeView = reinterpret_cast<NM_TREEVIEW*>(pNMHDR);

   if( pNMTreeView->itemNew.state & TVIS_EXPANDED )
   {
      SetRedraw(false);
      HTREEITEM hChild = GetChildItem(pNMTreeView->itemNew.hItem);
      while( hChild )
      {
         DeleteItem( hChild );
         hChild = GetChildItem( pNMTreeView->itemNew.hItem );
      }
      DisplayPath(pNMTreeView->itemNew.hItem);
      SetRedraw();
   }
   else
   {
      // Delete the Items, but leave one there, for 
      // expanding the item next time
      //
      HTREEITEM hChild = GetChildItem(pNMTreeView->itemNew.hItem);
      while( hChild ) 
      {
         DeleteItem( hChild );
         hChild = GetChildItem(pNMTreeView->itemNew.hItem);
      }
      InsertItem(_T(""), pNMTreeView->itemNew.hItem);
   }

   *pResult = 0;
}

CString CFTPFileTreeCtrl::GetFullPath(HTREEITEM hItem) const
{
   CString cszFullPath;

   while( hItem )
   {
      if( hItem == m_RootInfo.m_htiRoot )
      {
         if (m_RootInfo.m_cszRoot.GetLength()>0 && m_RootInfo.m_cszRoot.Right(1)==_T("/"))
            cszFullPath = m_RootInfo.m_cszRoot + cszFullPath;
         else
            cszFullPath = m_RootInfo.m_cszRoot + _T("/") + cszFullPath;
      }
      else
      {
         cszFullPath = GetItemText(hItem) + _T("/") + cszFullPath;
      }
      hItem = GetParentItem(hItem);
   }
   
   cszFullPath.TrimRight(_T("/"));

   return cszFullPath;
}

bool CFTPFileTreeCtrl::SetSelectedPath(const CString& cszPath)
{
   // Setting the Selection in the Tree
   CString cszTempPath(cszPath);
   cszTempPath.Delete(0, m_RootInfo.m_cszRoot.GetLength());
   LPTSTR pszPath = cszTempPath.GetBuffer(0);
   
   SetRedraw(false);

   HTREEITEM hParent = GetChildItem(TVI_ROOT);
   pszPath = _tcstok(pszPath, _T("/"));
   while( pszPath && hParent )
   {
      hParent = SearchChildItem(hParent, pszPath);
      if( hParent )  // Not found!
      {           
         // Info: the notification OnItemExpanded will not called every time 
         // after the call Expand.  You must call Expand with 
         // TVE_COLLAPSE|TVE_COLLAPSERESET to Reset the TVIS_EXPANDEDONCE Flag
         if( GetItemState(hParent, TVIS_EXPANDEDONCE) )
         {
            Expand(hParent, TVE_EXPAND);
            Expand(hParent, TVE_COLLAPSE|TVE_COLLAPSERESET);
            InsertItem(_T(""), hParent);      // insert a blank child-item
         }
         Expand(hParent, TVE_EXPAND);  // now, expand send a notification
      }
      pszPath = _tcstok(NULL, _T("/"));
   }

   SetRedraw();
   cszTempPath.ReleaseBuffer();
   
   if ( hParent ) // Ok the last subpath was found
   {     
      SelectItem(hParent); // select the last expanded item
      EnsureVisible(hParent);
      return true;
   }

   return false;
}

HTREEITEM CFTPFileTreeCtrl::SearchChildItem(HTREEITEM hItem, const CString& cszText)
{
   HTREEITEM hFound = GetChildItem( hItem );
   while( hFound )
   {
      if( GetItemText(hFound).CompareNoCase(cszText)==0 )
         return hFound;
      hFound = GetNextItem(hFound, TVGN_NEXT);
   }
   return NULL;
}

void CFTPFileTreeCtrl::PreSubclassWindow() 
{
   SetImageList(m_ShellImageList.GetSmallImageList(), TVSIL_NORMAL);

   if( GetStyle() & TVS_EDITLABELS ) 
   {
      ModifyStyle(TVS_EDITLABELS, 0); // Don't allow the user to edit ItemLabels
   }

   CTreeCtrl::PreSubclassWindow();
}
