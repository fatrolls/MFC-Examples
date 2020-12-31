//
////////////////////////////////////////////////////////////////////////////////
//
// Desciption :
//	CMailCmd class 

// Remark:
//
// Prerequisites (necessary conditions):
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MAILCMD_H_
#define __MAILCMD_H_

enum EMailCmd
{
	mcNothing = 0,
	mcLogOn,
	mcLogOff,
	mcSend
};

class CMailCmd : public COXEngineCmd
{
// Data Members
public:
	EMailCmd		eCmd;
	
protected:

private:

// Member Functions
public:
	CMailCmd(EMailCmd eC = mcNothing, BOOL bSynchrone = TRUE, COXDoneNotifier* pDoneNotifier = NULL) :
		COXEngineCmd(bSynchrone, pDoneNotifier),
		eCmd(eC) {}
	virtual ~CMailCmd() {}
	
protected:

private:
};

class CMCLogOn: public CMailCmd
{
public:
	CString sProfile;
	CString sPassword;
	BOOL	bResult;

	CMCLogOn(CString sProf, CString sPassw) :
		CMailCmd(mcLogOn),
		sProfile(sProf),
		sPassword(sPassw),
		bResult(FALSE) {}
};

class CMCLogOff: public CMailCmd
{
public:
	CMCLogOff() :
		CMailCmd(mcLogOff) {}
};

class CMCSend: public CMailCmd
{
public:
	CString sRecipient;
	CString sSubject;
	CString sContent;
	CStringArray sAttachments;
	short nError;

	CMCSend(CString sRecip,
			CString sSubj,
			CString sCont,
			const CStringArray& sAttatchs) :
		CMailCmd(mcSend),
		sSubject(sSubj),
		sContent(sCont),
		sRecipient(sRecip),
		nError(0)  {
			sAttachments.Copy(sAttatchs);}
};


#endif // __MAILCMD_H_
