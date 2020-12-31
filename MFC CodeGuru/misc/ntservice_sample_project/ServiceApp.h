// ServiceApp.h: interface for the CServiceApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVICEAPP_H__C234F376_E8FC_11D1_A712_000000000000__INCLUDED_)
#define AFX_SERVICEAPP_H__C234F376_E8FC_11D1_A712_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CServiceApp : public CWinApp, public CNTService  
{
	HANDLE	m_hStop;

public:
	CServiceApp();
	virtual ~CServiceApp();

public:
	virtual BOOL InitInstance();
	virtual void Run(DWORD, LPTSTR *);
	virtual void Stop();

};

#endif // !defined(AFX_SERVICEAPP_H__C234F376_E8FC_11D1_A712_000000000000__INCLUDED_)
