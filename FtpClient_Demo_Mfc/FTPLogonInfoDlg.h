#pragma once

#include "FTPclient.h"
#include "FTPFirewallTypeComboBox.h"

namespace nsFTP
{
namespace nsView
{

class CFTPLogonInfoDlg : public CDialog
{
   DECLARE_MESSAGE_MAP()
   DECLARE_DYNAMIC(CFTPLogonInfoDlg)
   enum { IDD = IDD_FTP_DLG_LOGON_INFO };
public:
   CFTPLogonInfoDlg(CWnd* pParent = NULL);
   virtual ~CFTPLogonInfoDlg();
   void GetLogonInfo(nsFTP::CLogonInfo& logonInfo) const;
   void SetLogonInfo(const nsFTP::CLogonInfo& logonInfo);
   bool Passive() const { return m_fPassive==TRUE; };

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   void Enable(DWORD dwResourceID, bool fEnable=true);
   void EnableAll(bool fEnable=true);
   void EnableFirewallSettings(bool fEnable=true);

   afx_msg void OnFirewallStateChanged();
   afx_msg void OnBnClickedAnonymous();

private:
   CString                    m_cszHostname;
   int                        m_iHostPort;
   CString                    m_cszUsername;
   CString                    m_cszPassword;
   CString                    m_cszAccount;
   BOOL                       m_fPassive;
   BOOL                       m_fFirewall;
   CString                    m_cszFwHostname;
   int                        m_iFwPort;
   CString                    m_cszFwUsername;
   CString                    m_cszFwPassword;
   CFirewallType              m_FwType;
   CFTPFirewallTypeComboBox   m_ctrlFirewallType;
};

};
};
