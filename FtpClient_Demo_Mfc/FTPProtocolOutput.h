#ifndef INC_FTPPROTOCOLOUTPUT_H
#define INC_FTPPROTOCOLOUTPUT_H

#pragma once

#include "FTPclient.h"

namespace nsFTP
{
namespace nsView
{

/// @brief Shows communication between server and client
class CFTPProtocolOutput : public CRichEditCtrl, public nsFTP::CFTPClient::CNotification
{
   DECLARE_MESSAGE_MAP()
public:
   CFTPProtocolOutput();
   virtual ~CFTPProtocolOutput();
   static DWORD CALLBACK ProtocolStreamInCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

protected:
   virtual void OnInternalError(const tstring& strErrorMsg, const tstring& strFileName, DWORD dwLineNr);
   virtual void OnSendCommand(const tstring& strCommand);
   virtual void OnResponse(const CReply& Reply);

private:
   void WriteLine(const CString& cszLine, COLORREF crText);
};

};
};

#endif // INC_FTPPROTOCOLOUTPUT_H
