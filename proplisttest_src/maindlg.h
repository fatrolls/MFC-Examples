// maindlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__4AFFDC59_AB76_4943_AE28_C443BCBE8D9A__INCLUDED_)
#define AFX_MAINDLG_H__4AFFDC59_AB76_4943_AE28_C443BCBE8D9A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "PropertyList.h"

class CMainDlg : public CDialogImpl<CMainDlg>
{
public:
   enum { IDD = IDD_MAINDLG };

   CFont m_BoldFont;
   CStatic m_prop;
   CComboBox m_combo1;
   CTabCtrl m_tab1;
   CPropertyListCtrl m_list1;

   BEGIN_MSG_MAP(CMainDlg)
      MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
      COMMAND_ID_HANDLER(IDOK, OnOK)
      COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
      NOTIFY_HANDLER(IDC_LIST1, PIN_BROWSE, OnBrowse)
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

      LOGFONT lf = { 0 };
      ::GetObject(GetFont(), sizeof(lf), &lf);
      lf.lfWeight = FW_BOLD;
      m_BoldFont.CreateFontIndirect(&lf);

      m_combo1.Attach(GetDlgItem(IDC_COMBO1));
      m_combo1.AddString(_T("Form - Form1"));
      m_combo1.SetCurSel(0);

      m_prop.Attach(GetDlgItem(IDC_PROPTITLE));
      m_prop.SetFont(m_BoldFont);

      m_tab1.Attach(GetDlgItem(IDC_TAB1));
      TCITEM item = { 0 };
      item.mask = TCIF_TEXT;   
      item.pszText = _T("Alphabetic");
      m_tab1.InsertItem(0, &item);
      item.pszText = _T("Categorized");
      m_tab1.InsertItem(1, &item);
      m_tab1.SetCurSel(1);

      m_list1.SubclassWindow(GetDlgItem(IDC_LIST1));

      m_list1.SetExtendedListStyle(PLS_EX_CATEGORIZED);
      HPROPERTY hAppearance = m_list1.AddItem( PropCreateCategory(_T("Appearance"), 1234) );
      HPROPERTY hName = m_list1.AddItem( PropCreateSimple(_T("Name"), _T("bjarke")) );
      m_list1.AddItem( PropCreateSimple(_T("X"), 123L) );
      m_list1.AddItem( PropCreateSimple(_T("Y"), 456L) );
      m_list1.AddItem( PropCreateCategory(_T("Behaviour")) );
      m_list1.AddItem( PropCreateSimple(_T("Enabled"), false) );
      m_list1.AddItem( PropCreateFileName(_T("Picture"), _T("C:\\Temp\\Test.bmp")) );

      LPCTSTR list[] = { _T("0 - Red"), _T("1 - Blue"), _T("2 - Green"), _T("3 - Yellow"), NULL };
      m_list1.AddItem( PropCreateList(_T("Colors"), list, 2) );

      // Testing control methods
      HPROPERTY hFind = m_list1.FindProperty(_T("Name")); hFind;
      hFind = m_list1.FindProperty(1234); hFind;
      m_list1.SetItemEnabled( hName, FALSE );
      m_list1.SetItemData(hName, 666);
      LPARAM lParam = m_list1.GetItemData(hName); lParam;
      TCHAR szText[32];
      m_list1.GetItemName(hName, szText, 32);
      CComVariant v(L"Form1");
      m_list1.SetItemValue(hName, &v);
      m_list1.CollapseItem(hAppearance);
      m_list1.ExpandItem(hAppearance);

      return TRUE;
   }

   LRESULT OnBrowse(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
   {
      LPNMPROPERTYITEM nmp = (LPNMPROPERTYITEM)pnmh;
      LPCTSTR lpcstrFilter = 
         _T("Bitmap Files (*.bmp)\0*.bmp\0")
         _T("All Files (*.*)\0*.*\0")
         _T("");
      CFileDialog dlg(TRUE, _T("bmp"), _T("C:\\Temp\\Image.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, lpcstrFilter);
      int nRet = dlg.DoModal();
      if(nRet == IDOK) {
         CComVariant v(dlg.m_ofn.lpstrFile);
         m_list1.SetItemValue(nmp->prop, &v);
      }
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

#endif // !defined(AFX_MAINDLG_H__4AFFDC59_AB76_4943_AE28_C443BCBE8D9A__INCLUDED_)
