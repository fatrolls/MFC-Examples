#pragma once

#include "Resource.h"
#include "FTPClient.h"
#include "afxcmn.h"
#include "afxwin.h"

namespace nsFTP
{
namespace nsView
{

class CFTPProgressDlg : public CDialog, public nsFTP::CFTPClient::CNotification
{
   DECLARE_MESSAGE_MAP()
   DECLARE_DYNAMIC(CFTPProgressDlg)
   enum { IDD = IDD_FTP_DLG_PROGRESS };
public:
   class CNotificationBase
   {
   public:
      virtual void OnAbort() {};
   };

   CFTPProgressDlg(CWnd* pParent = NULL);
   virtual ~CFTPProgressDlg();

   void AttachObserver(CNotificationBase* pObserver);
   void DetachObserver(CNotificationBase* pObserver);

protected:
   afx_msg void OnTimer(UINT nIDEvent);
   afx_msg void OnBnClickedCancel();
   CString GetTransferrate(int& iBytesPerSec);

   virtual BOOL OnInitDialog();
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   virtual void OnBytesReceived(const TByteVector& vBuffer, long lReceivedBytes);
   virtual void OnBytesSent(const TByteVector& vBuffer, long lSentBytes);
   virtual void OnPreReceiveFile(const tstring& strSourceFile, const tstring& strTargetFile, long lFileSize);
   virtual void OnPreSendFile(const tstring& strSourceFile, const tstring& strTargetFile, long lFileSize);
   virtual void OnPostReceiveFile(const tstring& strSourceFile, const tstring& strTargetFile, long lFileSize);
   virtual void OnPostSendFile(const tstring& strSourceFile, const tstring& strTargetFile, long lFileSize);

private:
   CProgressCtrl     m_ctrlProgress;
   CAnimateCtrl      m_ctrlAnimate;
   CStatic           m_ctrlFileStatus;
   CStatic           m_ctrlSourceFile;
   CStatic           m_ctrlTargetFile;
   nsHelper::CTimer  m_Timer;
   typedef std::set<CNotificationBase*> TObserverSet;
   TObserverSet m_setObserver;
};

};
};
