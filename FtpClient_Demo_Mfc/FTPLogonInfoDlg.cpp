
#include "stdafx.h"
#include "FTPexample.h"
#include "FTPLogonInfoDlg.h"

using namespace nsFTP;
using namespace nsFTP::nsView;

IMPLEMENT_DYNAMIC(CFTPLogonInfoDlg, CDialog)

BEGIN_MESSAGE_MAP(CFTPLogonInfoDlg, CDialog)
   ON_BN_CLICKED(IDC_FIREWALL, OnFirewallStateChanged)
   ON_CBN_SELCHANGE(IDC_TYPE_FIREWALL, OnFirewallStateChanged)
   ON_BN_CLICKED(IDC_ANONYMOUS, OnBnClickedAnonymous)
END_MESSAGE_MAP()

CFTPLogonInfoDlg::CFTPLogonInfoDlg(CWnd* pParent /*=NULL*/) :
   CDialog(CFTPLogonInfoDlg::IDD, pParent),
   m_iHostPort(nsFTP::DEFAULT_FTP_PORT),
   m_iFwPort(nsFTP::DEFAULT_FTP_PORT),
   m_fPassive(false),
   m_fFirewall(false)
{
}

CFTPLogonInfoDlg::~CFTPLogonInfoDlg()
{
}

void CFTPLogonInfoDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);

   DDX_Text(pDX, IDC_HOSTNAME, m_cszHostname);
   DDX_Text(pDX, IDC_PORT, m_iHostPort);
   DDX_Text(pDX, IDC_USER, m_cszUsername);
   DDX_Text(pDX, IDC_PASSWORD, m_cszPassword);
   DDX_Text(pDX, IDC_ACCOUNT, m_cszAccount);
   DDX_Check(pDX, IDC_PASV, m_fPassive);
   DDX_Check(pDX, IDC_FIREWALL, m_fFirewall);
   DDX_Text(pDX, IDC_HOSTNAME_FIREWALL, m_cszFwHostname);
   DDX_Text(pDX, IDC_PORT_FIREWALL, m_iFwPort);
   DDX_Text(pDX, IDC_USER_FIREWALL, m_cszFwUsername);
   DDX_Text(pDX, IDC_PASSWORD_FIREWALL, m_cszFwPassword);
   DDX_Control(pDX, IDC_TYPE_FIREWALL, m_ctrlFirewallType);

   if( pDX->m_bSaveAndValidate )
      m_ctrlFirewallType.GetFirewallType(m_FwType);
   else
      m_ctrlFirewallType.SetFirewallType(m_FwType);

   EnableAll();
}

void CFTPLogonInfoDlg::GetLogonInfo(nsFTP::CLogonInfo& logonInfo) const
{
   logonInfo.SetHost(static_cast<LPCTSTR>(m_cszHostname), static_cast<USHORT>(m_iHostPort), 
                     static_cast<LPCTSTR>(m_cszUsername), static_cast<LPCTSTR>(m_cszPassword),
                     static_cast<LPCTSTR>(m_cszAccount));
   logonInfo.SetFirewall(static_cast<LPCTSTR>(m_cszFwHostname), static_cast<LPCTSTR>(m_cszFwUsername),
                         static_cast<LPCTSTR>(m_cszFwPassword), static_cast<USHORT>(m_iFwPort), 
                         m_fFirewall?m_FwType:CFirewallType::None());
}

void CFTPLogonInfoDlg::SetLogonInfo(const nsFTP::CLogonInfo& logonInfo)
{
   m_fFirewall     = logonInfo.FwType()!=CFirewallType::None();
   m_cszHostname   = logonInfo.Hostname().c_str();
   m_iHostPort     = logonInfo.Hostport();
   m_cszUsername   = logonInfo.Username().c_str();
   m_cszPassword   = logonInfo.Password().c_str();
   m_cszAccount    = logonInfo.Account().c_str();
   m_cszFwHostname = logonInfo.FwHost().c_str();
   m_iFwPort       = logonInfo.FwPort();
   m_cszFwUsername = logonInfo.FwUsername().c_str();
   m_cszFwPassword = logonInfo.FwPassword().c_str();
   m_FwType        = logonInfo.FwType();
}

void CFTPLogonInfoDlg::EnableAll(bool fEnable)
{
   Enable(IDC_HOSTNAME, fEnable);
   Enable(IDC_PORT, fEnable);
   Enable(IDC_USER, fEnable);
   Enable(IDC_PASSWORD, fEnable);
   Enable(IDC_ACCOUNT, fEnable);
   Enable(IDC_PASV, fEnable);
   Enable(IDC_FIREWALL, fEnable);

   if( !m_fFirewall )
      fEnable = false;

   EnableFirewallSettings(fEnable);
}

void CFTPLogonInfoDlg::EnableFirewallSettings(bool fEnable)
{
   Enable(IDC_FRAME_FIREWALL, fEnable);

   Enable(IDC_TYPE_STATIC, fEnable);
   Enable(IDC_TYPE_FIREWALL, fEnable);

   Enable(IDC_HOSTNAME_STATIC, fEnable);
   Enable(IDC_HOSTNAME_FIREWALL, fEnable);

   Enable(IDC_PORT_STATIC, fEnable);
   Enable(IDC_PORT_FIREWALL, fEnable);

   if( fEnable &&
       (m_FwType==CFirewallType::ProxyOpen() ||
        m_FwType==CFirewallType::UserWithNoLogon() ||
        m_FwType==CFirewallType::UserRemoteIDatRemoteHostFireID()) )
   {
      Enable(IDC_USER_STATIC, m_FwType==CFirewallType::UserRemoteIDatRemoteHostFireID());
      Enable(IDC_USER_FIREWALL, m_FwType==CFirewallType::UserRemoteIDatRemoteHostFireID());

      Enable(IDC_PASSWORD_STATIC, false);
      Enable(IDC_PASSWORD_FIREWALL, false);
   }
   else
   {
      Enable(IDC_USER_STATIC, fEnable);
      Enable(IDC_USER_FIREWALL, fEnable);

      Enable(IDC_PASSWORD_STATIC, fEnable);
      Enable(IDC_PASSWORD_FIREWALL, fEnable);
   }
}

void CFTPLogonInfoDlg::Enable(DWORD dwResourceID, bool fEnable)
{
   CWnd* pWnd = DYNAMIC_DOWNCAST(CWnd, GetDlgItem(dwResourceID));
   if( pWnd )
      pWnd->EnableWindow(fEnable);
}

void CFTPLogonInfoDlg::OnFirewallStateChanged()
{
   UpdateData();
}

void CFTPLogonInfoDlg::OnBnClickedAnonymous()
{
   CWnd* pWnd = DYNAMIC_DOWNCAST(CWnd, GetDlgItem(IDC_USER));
   if( pWnd )
      static_cast<CEdit*>(pWnd)->SetWindowText(nsFTP::ANONYMOUS_USER);
}
