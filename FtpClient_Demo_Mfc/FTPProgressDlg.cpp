
#include "stdafx.h"
#include "FTPProgressDlg.h"

using namespace nsFTP;
using namespace nsFTP::nsView;

#ifndef PUMP_MESSAGES
#define PUMP_MESSAGES() \
do \
{ \
   MSG msg; \
   while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) \
   { \
      ::TranslateMessage(&msg); \
      ::DispatchMessage(&msg); \
   } \
   LONG lIdle = 0; \
   while (AfxGetApp()->OnIdle(lIdle ++)); \
}while(0)
#endif

IMPLEMENT_DYNAMIC(CFTPProgressDlg, CDialog)

BEGIN_MESSAGE_MAP(CFTPProgressDlg, CDialog)
   ON_WM_TIMER()
   ON_BN_CLICKED(ID_ABORT_FTP_TRANSFER, OnBnClickedCancel)
END_MESSAGE_MAP()

CFTPProgressDlg::CFTPProgressDlg(CWnd* pParent /*=NULL*/)
   : CDialog(CFTPProgressDlg::IDD, pParent)
{
}

CFTPProgressDlg::~CFTPProgressDlg()
{
   KillTimer(1); 
}

void CFTPProgressDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_PROGRESS_BAR, m_ctrlProgress);
   DDX_Control(pDX, IDC_ANIMATE_FILECOPY, m_ctrlAnimate);
   DDX_Control(pDX, IDC_STATIC_FILESTATUS, m_ctrlFileStatus);
   DDX_Control(pDX, IDC_STATIC_SOURCE_FILE, m_ctrlSourceFile);
   DDX_Control(pDX, IDC_STATIC_TARGET_FILE, m_ctrlTargetFile);

   //m_ctrlProgress.SendMessage(PBM_SETBARCOLOR, 0, RGB(46,211,49));
}

BOOL CFTPProgressDlg::OnInitDialog() 
{
   CDialog::OnInitDialog();

   SetTimer(1, 150, NULL); 

   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

void CFTPProgressDlg::OnTimer(UINT nIDEvent) 
{
   if( nIDEvent==1 )
   {
      int i, iFileSize, iBytesPerSec;
      m_ctrlProgress.GetRange(i, iFileSize);

      CString cszTemp, cszRemaining;
      if( iFileSize<1024 )
         cszTemp.Format(_T("%d Bytes from %d Bytes transferred (%s)."), m_ctrlProgress.GetPos(), iFileSize, GetTransferrate(iBytesPerSec));
      else
         cszTemp.Format(_T("%d KB from %d KB transferred (%s)."), m_ctrlProgress.GetPos()/1024, iFileSize/1024, GetTransferrate(iBytesPerSec));

      if( iBytesPerSec>0 )
      {
         const int iRemainingSec = (iFileSize-m_ctrlProgress.GetPos())/iBytesPerSec;
         if( iRemainingSec<60 )
            cszRemaining.Format(_T(" Remaining time: %d sec"), iRemainingSec);
         else
            cszRemaining.Format(_T(" Remaining time: %d min"), iRemainingSec/60);
      }

      m_ctrlFileStatus.SetWindowText(cszTemp + cszRemaining);
   }

   CDialog::OnTimer(nIDEvent);
}

CString CFTPProgressDlg::GetTransferrate(int& iBytesPerSec)
{
   iBytesPerSec = static_cast<int>(static_cast<double>(m_ctrlProgress.GetPos())/m_Timer.GetElapsedTime());
   CString cszTemp;
   if( iBytesPerSec>1024 )
      cszTemp.Format(_T("%d KB/sec"), iBytesPerSec/1024);
   else
      cszTemp.Format(_T("%d Bytes/sec"), iBytesPerSec);
   return cszTemp;
}

void CFTPProgressDlg::OnBytesReceived(const TByteVector& /*vBuffer*/, long lReceivedBytes)
{
   m_ctrlProgress.OffsetPos(lReceivedBytes);
   PUMP_MESSAGES();
}

void CFTPProgressDlg::OnBytesSent(const TByteVector& /*vBuffer*/, long lSentBytes)
{
   m_ctrlProgress.OffsetPos(lSentBytes);
   PUMP_MESSAGES();
}

void CFTPProgressDlg::OnPreReceiveFile(const tstring& strSourceFile, const tstring& strTargetFile, long lFileSize)
{
   m_ctrlProgress.SetRange32(0, lFileSize);
   PUMP_MESSAGES();
   m_Timer.Restart();
   m_ctrlSourceFile.SetWindowText(CString(_T("Source: ")) + strSourceFile.c_str());
   m_ctrlTargetFile.SetWindowText(CString(_T("Target: ")) + strTargetFile.c_str());
   m_ctrlAnimate.Open(IDR_AVI_DOWNLOAD);
   SetWindowText(_T("Download"));
}

void CFTPProgressDlg::OnPostReceiveFile(const tstring& /*strSourceFile*/, const tstring& /*strTargetFile*/, long /*lFileSize*/)
{
   m_ctrlAnimate.Close();
}

void CFTPProgressDlg::OnPreSendFile(const tstring& strSourceFile, const tstring& strTargetFile, long lFileSize)
{
   m_ctrlProgress.SetRange32(0, lFileSize);
   PUMP_MESSAGES();
   m_Timer.Restart();
   m_ctrlSourceFile.SetWindowText(CString(_T("Source: ")) + strSourceFile.c_str());
   m_ctrlTargetFile.SetWindowText(CString(_T("Target: ")) + strTargetFile.c_str());
   m_ctrlAnimate.Open(IDR_AVI_UPLOAD);
   SetWindowText(_T("Upload"));
}

void CFTPProgressDlg::OnPostSendFile(const tstring& /*strSourceFile*/, const tstring& /*strTargetFile*/, long /*lFileSize*/)
{
   m_ctrlAnimate.Close();
}

void CFTPProgressDlg::AttachObserver(CFTPProgressDlg::CNotificationBase* pObserver)
{
   ASSERT( pObserver );
   if( pObserver )
      m_setObserver.insert(pObserver);
}

void CFTPProgressDlg::DetachObserver(CFTPProgressDlg::CNotificationBase* pObserver)
{
   ASSERT( pObserver );
   if( pObserver )
      m_setObserver.erase(pObserver);
}

void CFTPProgressDlg::OnBnClickedCancel()
{
   for( TObserverSet::const_iterator it=m_setObserver.begin(); it!=m_setObserver.end(); it++ )
      (*it)->OnAbort();

   OnCancel();
}
