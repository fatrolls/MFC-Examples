///////////////////////////////////////////////////////////////////
//  Header  : HELP1DLG.H
//
//  Purpose : Header for the HELP1DLG dialog used as the main 
//            window of this program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 03-31-96
///////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHelp1Dlg dialog

class CHelp1Dlg : public CDialog
{
public:
   CHelp1Dlg(CWnd* pParent = NULL);   // constructor

   // Dialog Data
   enum { IDD = IDD_HELP1_DIALOG };

protected:
   // Virtual function overrides
   virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support

protected:
   HICON m_hIcon;

   // Overrides
   virtual BOOL OnInitDialog();

   // Message map functions
   afx_msg void OnDestroy();
   afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
   afx_msg void OnBtnHelpClick();

   DECLARE_MESSAGE_MAP()
};
