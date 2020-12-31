// LogMsg.h: interface for the CLogMessage class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __LOGMSG_H__
#define __LOGMSG_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CLogMessage  
{
public:
	BOOL WriteError (const CString& strMessage);
	CLogMessage ();
	virtual ~CLogMessage();

private:
    CStdioFile m_LogFile;
    BOOL  m_bSuccess;
};

#endif // !defined(AFX_LOGMSG_H__AB5CEE07_A955_11D1_B258_006097960BB7__INCLUDED_)
