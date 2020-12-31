///////////////////////////////////////////////////////////////////
// Module  : HTMLDLG.H
//
// Purpose : The main dialog box interface for the RAWHTML program.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 07-13-96
///////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
// CRawHtmlDlg dialog

class CRawHtmlDlg : public CDialog
{
public:
   CRawHtmlDlg(CWnd* pParent = NULL);   // standard constructor

   // Dialog Data
   enum { IDD = IDD_RAWHTML_DIALOG };

   CButton   m_btnClose;
   CButton   m_btnGo;
   CEdit      m_editUrl;
   CEdit    m_editHtml;

protected:
   // DDX/DDV support
   virtual void DoDataExchange(CDataExchange* pDX);   

protected:
   HICON    m_hIcon;
   CString  m_strServer;
   CString  m_strPath;

   void ParseURL(CString& strUrl);
   void DisplayRawHtml(char* lpszBuffer);

   // Message map methods
   virtual BOOL OnInitDialog();
   afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
   afx_msg void OnBtnGoClicked();

   DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////

