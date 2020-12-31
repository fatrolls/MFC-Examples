// ===================================================================
//     Class: CUT_SampleThread
//      File: UT_SmplT.h
//   Revised: 
//   Purpose: Sample CUT_Thread dervd class for server framework tutorial.
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
#ifndef _UT_SMPLT_H_
#define _UT_SMPLT_H_


class CUT_SampleThread : public CUT_WSThread {
private:
	// private member declarations 

	// declared private to preclude usage...
	CUT_SampleThread(const CUT_SampleThread& );
	CUT_SampleThread operator=(const CUT_SampleThread&);

protected:
	// protected member declarations


public:
	// public member declarations

	CUT_SampleThread();

	virtual ~CUT_SampleThread();

	// CUT_WSThread Overrides
	virtual void OnConnect();
};

#endif
