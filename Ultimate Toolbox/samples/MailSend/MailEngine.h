#ifndef __MAILENGINE_H_
#define __MAILENGINE_H_

#include "OXThreadEngine.h"
#include "OXSendMail.h"
#include "MailCmd.h"

#define MR_MMERR_SUCCESS	0x0000
#define MR_MMERR_LOGON		0x0101
#define MR_MMERR_RECIPIENT	0x0102
#define MR_MMERR_SENT		0x0103
#define MR_MMERR_HOMEID		0x0104


class CMailEngine : public COXThreadEngine
{
// Data Members
public:

protected:
	COXSendMail		m_sendMail;

private:
	static short	defError;

// Member Functions
public:
	CMailEngine();
	virtual ~CMailEngine();

	BOOL LogOn(CString sProfile, CString sPassword);
	void LogOff();
	BOOL IsLoggedOn();
	BOOL Send(CString sMAPIProfile,
			  CString sMAPIPassword,
			  CString sRecipient, 
			  CString sSubject, 
			  CString sContent,
			  const CStringArray& sAttachments,
			  short& nError = defError);


protected:
	virtual void OnExecuteCmd(COXEngineCmd* pCmd);
	virtual void OnThreadDestruction();

	void OnLogOn(CMCLogOn& cmd);
	void OnLogOff(CMCLogOff& cmd);
	void OnSend(CMCSend& cmd);


private:

};

extern CMailEngine theMailEngine;

#endif // __MAILENGINE_H_
