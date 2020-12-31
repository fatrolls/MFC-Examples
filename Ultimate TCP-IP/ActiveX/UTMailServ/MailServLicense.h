//=================================================================
//  class: CMailServLicense
//  File:  MailServLicense.h
//
//  ActiveX control license support
//
//=================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
//=================================================================

#if !defined(AFX_MAILLICENSE_H__C505FAA3_ECB4_11D2_A442_0080C858F182__INCLUDED_)
#define AFX_MAILLICENSE_H__C505FAA3_ECB4_11D2_A442_0080C858F182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FULL_LICENSE_KEY		"49FC0BBE-1EA9-11d3-A487-0080C858F182"
#define RUNTIME_LICENSE_KEY		"49FC0BC1-1EA9-11d3-A487-0080C858F182"


class CMailServLicense  
{
public:
	CMailServLicense();
	virtual ~CMailServLicense();

protected: 
	static BOOL		VerifyLicenseKey(BSTR bstr);
	static BOOL		GetLicenseKey(DWORD dwReserved, BSTR* pBstr);
	static BOOL		IsLicenseValid();

};

#endif // !defined(AFX_FINGERLICENSE_H__C505FAA3_ECB4_11D2_A442_0080C858F182__INCLUDED_)
