// ===================================================================
//     Class: CUT_SampleServer
//      File: UT_SmplT.h
//   Created: February 22, 1999
//   Revised: 
//   Purpose: Sample server derived class for Help tuorial.
//			  Illustrates the discussion of the server framework in 
//			  the TCPIPSERVER help file.
// Developer: 
// ===================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================

#ifndef _UT_SMPLS_H_
#define _UT_SMPLS_H_


class CUT_SampleServer : public CUT_WSServer {
private:
	// private member declarations

	CUT_SampleServer(const CUT_SampleServer& );
	CUT_SampleServer operator=(const CUT_SampleServer&);

protected:
	// protected member declarations


public:
	// public member declarations

	CUT_SampleServer();

	virtual ~CUT_SampleServer();

	// CUT_WSServer overrides
	virtual CUT_WSThread* CreateInstance();
	virtual void ReleaseInstance(CUT_WSThread * ptr);


	// added methods for entry and exit
	int Start();

};

#endif
