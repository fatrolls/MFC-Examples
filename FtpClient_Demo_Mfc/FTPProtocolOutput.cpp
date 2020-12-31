#include "stdafx.h"
#include "FTPProtocolOutput.h"
#include "Definements.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace nsFTP;
using namespace nsFTP::nsView;

BEGIN_MESSAGE_MAP(CFTPProtocolOutput, CRichEditCtrl)
END_MESSAGE_MAP()

CFTPProtocolOutput::CFTPProtocolOutput()
{
}

CFTPProtocolOutput::~CFTPProtocolOutput()
{
}

DWORD CALLBACK CFTPProtocolOutput::ProtocolStreamInCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
   CMemFile* pMf = reinterpret_cast<CMemFile*>(dwCookie);
   *pcb = pMf->Read(pbBuff, cb);
   return 0;
}

void CFTPProtocolOutput::OnSendCommand(const tstring& strCommand)
{
   if( strCommand.length()==0 )
      return;

   if( strCommand.length()>4 && strCommand.substr(5)==_T("PASS ") )
      WriteLine(_T("< PASS **********\n"), RGB(0, 0, 255));
   else
      WriteLine(_T("> ") + CString(strCommand.c_str()) + _T("\n"), RGB(0, 0, 255));
}

void CFTPProtocolOutput::OnResponse(const CReply& Reply)
{
   if( Reply.Value().length()==0 )
      return;

   COLORREF crText = RGB(0, 150, 0);
   if( Reply.Code().IsPermanentNegativeCompletionReply() )
      crText = RGB(255, 0, 0);
   else if( Reply.Code().IsTransientNegativeCompletionReply() )
      crText = RGB(200, 200, 0);

   WriteLine(_T("< ") + CString(Reply.Value().c_str()) + _T("\n"), crText);
}

void CFTPProtocolOutput::OnInternalError(const tstring& strErrorMsg, const tstring& strFileName, DWORD dwLineNr)
{
   CString cszMsg;
   cszMsg.Format(_T("%s ==> Datei \"%s\" (%d)"), strErrorMsg.c_str(), strFileName.c_str(), dwLineNr);
   WriteLine(cszMsg, RGB(255, 0, 0));
}

void CFTPProtocolOutput::WriteLine(const CString& cszLine, COLORREF crText)
{
   if( m_hWnd )
   {
      CHARFORMAT cf;
      cf.dwMask    = CFM_BOLD|CFM_COLOR;
      cf.dwEffects = CFE_BOLD;
      cf.crTextColor = crText;

      CMemFile mf;
      mf.Write(nsHelper::CCnv::ConvertToString(tstring(cszLine)).c_str(), cszLine.GetLength());
      mf.SeekToBegin();
   
      SetSelectionCharFormat(cf);

      EDITSTREAM es;
      es.dwCookie = reinterpret_cast<DWORD_PTR>(&mf);
      es.pfnCallback = CFTPProtocolOutput::ProtocolStreamInCallback; 
      StreamIn(SF_TEXT|SFF_SELECTION, es);
      SetSel(-1, -1);
      LineScroll(1);
   }
}
