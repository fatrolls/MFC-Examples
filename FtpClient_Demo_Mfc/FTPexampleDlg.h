#pragma once

#include "afxcmn.h"
#include "FTPClient.h"
#include "FTPProtocolOutput.h"
#include "Resource.h"
#include "FTPProgressDlg.h"

class CFTPexampleDlg : public CDialog, public nsFTP::nsView::CFTPProgressDlg::CNotificationBase
{
   DECLARE_MESSAGE_MAP()
   enum { IDD = IDD_FTP_DLG_EXAMPLE };
public:
   CFTPexampleDlg(CWnd* pParent = NULL);
   ~CFTPexampleDlg();

protected:
   virtual void OnCancel();
   virtual void OnAbort();
   virtual void DoDataExchange(CDataExchange* pDX);
   virtual BOOL OnInitDialog();
   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnBnClickedBtnBrowse();
   afx_msg void OnBnClickedBtnLogonInfo();

private:
   HICON                             m_hIcon;
   nsFTP::CFTPClient                 m_FTPClient;
   nsFTP::CLogonInfo                 m_LogonInfo;
   nsFTP::nsView::CFTPProtocolOutput m_ProtocolOutput;
};
