// Internet.h: interface for the CInternet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERNET_H__B08C82D2_4F8B_11D1_87C8_00001C302581__INCLUDED_)
#define AFX_INTERNET_H__B08C82D2_4F8B_11D1_87C8_00001C302581__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "wininet.h"

class CWebWorld  
{
public:
	void SetErrorMessage(CString s);
	CString GetWebPage(const CString& Url);
	CWebWorld();
	virtual ~CWebWorld();

private:
	CString m_ErrorMessage;
	HINTERNET m_Session;
};

#endif // !defined(AFX_INTERNET_H__B08C82D2_4F8B_11D1_87C8_00001C302581__INCLUDED_)
