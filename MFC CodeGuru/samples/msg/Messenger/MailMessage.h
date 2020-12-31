#ifndef MAIL_MESSAGE_H
#define MAIL_MESSAGE_H

#ifndef __AFXTEMPL_H__
	#include <afxtempl.h>
#endif

#ifndef __AFXDAO_H
	#include <afxdao.h>
#endif


const int MAX_NAME_SIZE = MAX_COMPUTERNAME_LENGTH + 1;
const int MAX_MESSAGE_SIZE = 250;


//Structure which will be sent down the mailslot
struct SMailMessage
{
  SYSTEMTIME m_SentTime;
  TCHAR m_sSenderName[MAX_NAME_SIZE];
  TCHAR m_sSenderMachine[MAX_NAME_SIZE];
  TCHAR m_sTo[MAX_NAME_SIZE];
  TCHAR m_sMessage[MAX_MESSAGE_SIZE];
};



class CMailMessage
{
	CArray<SMailMessage, SMailMessage&> m_Messages;
public:
	CMailMessage();
	~CMailMessage();

	SMailMessage& operator [](int index);
	int GetSize();
	int Add(SMailMessage& mailMessage);

	// Dao part
public:
	int LoadDAO(LPCSTR szFileName);
	int SaveDAO(LPCSTR szFileName);

private:

private:
	int LoadDAO(CDaoDatabase *pDB);

	int CreateDAO(CDaoDatabase *pDB);
	int DeleteDAO(CDaoDatabase *pDB);
	int SaveDAO(CDaoDatabase *pDB);
};

#endif