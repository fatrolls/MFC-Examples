// maindlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__D874451F_DFC5_424F_918E_532F2341597E__INCLUDED_)
#define AFX_MAINDLG_H__D874451F_DFC5_424F_918E_532F2341597E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PropertyTree.h"



class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
   enum { IDD = IDD_MAINDLG };

   CImageList m_images;
   CPropertyTreeCtrl m_tree;

   BEGIN_MSG_MAP(CMainDlg)
      MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
      COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
      COMMAND_ID_HANDLER(IDOK, OnOK)
      COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
      REFLECT_NOTIFICATIONS()
   END_MSG_MAP()

   LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
   {
      // center the dialog on the screen
      CenterWindow();

      // set icons
      HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
         IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
      SetIcon(hIcon, TRUE);
      HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
         IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
      SetIcon(hIconSmall, FALSE);

      m_images.Create(IDB_PROPERTYTREE, 16, 1, RGB(255,0,255));
      m_tree.SubclassWindow( GetDlgItem(IDC_TREE1) );
      m_tree.SetImageList(m_images, TVSIL_NORMAL);
      m_tree.SetExtendedTreeStyle(PTS_EX_NOCOLLAPSE);

      LPCTSTR pList[] = { _T("White"), _T("Brown"), _T("Pink"), _T("Yellow"), NULL };
      HTREEITEM hItem, hName, hOpt;
      hItem = m_tree.InsertItem( PropCreateReadOnlyItem(_T("Accessibility")), 13, 13, TVI_ROOT);
         m_tree.InsertItem( PropCreateCheckmark(_T("Always expand ALT text for images")), 0, 0, hItem);
         m_tree.InsertItem( PropCreateCheckmark(_T("Move system caret with focus changes")), 0, 0, hItem);
      hItem = m_tree.InsertItem( PropCreateReadOnlyItem(_T("When searching")), 10, 10, TVI_ROOT);
         hOpt = m_tree.InsertItem( PropCreateOptionCheck(_T("Display results, and go to most likely site")), 0, 0, hItem);
         m_tree.InsertItem( PropCreateOptionCheck(_T("Do not search from the Address bar"), true), 0, 0, hItem);
      hItem = m_tree.InsertItem( PropCreateReadOnlyItem(_T("Misc")), 13, 13, TVI_ROOT);
         hName = m_tree.InsertItem( PropCreateSimple(_T("Name"), _T("Donald")), 11, 11, hItem);
         m_tree.InsertItem( PropCreateSimple(_T("Male"), true), 12, 12, hItem);
         m_tree.InsertItem( PropCreateList(_T("Skin"), pList), 12, 12, hItem);

      TCHAR szBuffer[256];
      m_tree.GetItemText(hName, szBuffer, 256);
      m_tree.SetItemData(hName, 1234);
      LPARAM lParam = m_tree.GetItemData(hName); lParam;
      TVITEM item = { 0 };
      item.hItem = hName;
      item.mask = TVIF_PARAM;
      m_tree.GetItem(&item);
      CComVariant v;
      m_tree.GetItemValue(hName, &v);
      v = L"Donald Duck";
      m_tree.SetItemValue(hName, &v);

      BOOL bCheck = m_tree.GetCheckState(hOpt);
      m_tree.SetCheckState(hOpt, TRUE);
      bCheck = m_tree.GetCheckState(hOpt);

      //m_tree.EnableItem(hName, FALSE);
      //m_tree.EnableItem(hOpt, FALSE);

      return TRUE;
   }

   LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
      dlg.DoModal();
      return 0;
   }

   LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      // TODO: Add validation code 
      EndDialog(wID);
      return 0;
   }

   LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
   {
      EndDialog(wID);
      return 0;
   }
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__D874451F_DFC5_424F_918E_532F2341597E__INCLUDED_)
