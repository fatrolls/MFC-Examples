///////////////////////////////////////////////////////////////////
//  Header  : FLIPDLG.H
//
//  Purpose : Interface for the CWallFlipDlg class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 06-27-96
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CWallFlipDlg dialog

class CWallFlipDlg : public CDialog
{
public:
   CWallFlipDlg(CWnd* pParent = NULL);   // standard constructor
   void SetRegValue(HKEY hKey, CString strKey, CString strChildKey, 
      CString strChildKeyValue);
   void SetRegValue(HKEY hKey, CString strKey, CString strChildKey, 
      DWORD dwChildKeyValue);

   // Dialog Data
   enum { IDD = IDD_WALLFLIP_DIALOG };
   CButton   m_btnOK;
   CButton   m_btnRemove;
   CButton   m_btnAdd;
   CButton   m_btnAbout;
   CListBox   m_listBitmaps;

protected:
   HICON m_hIcon;
   UINT  m_uNext;

   // Helper method
   void GetRegData();
   
   // Virtual method overrides
   virtual void DoDataExchange(CDataExchange* pDX);   
   virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
   
   // Message map methods
   virtual BOOL OnInitDialog();
   afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
   afx_msg void OnBtnAboutClick();
   afx_msg void OnBtnAddClick();
   afx_msg void OnBtnRemoveClick();
   afx_msg void OnDestroy();
   afx_msg void OnBtnOkClick();

   DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////
