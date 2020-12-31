// ===================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// AccessSampleThread.h
// ===================================================================
#ifndef _UT_SAMPLE_TEST
#define _UT_SAMPLE_TEST

class CUT_AccessServer;


class CUT_AccessThread : public CUT_WSThread {
	friend CUT_AccessServer;

private:
	// private member declarations 

	// declared private to preclude usage...
	CUT_AccessThread(const CUT_AccessThread& );
	CUT_AccessThread operator=(const CUT_AccessThread&);

protected:
	// protected member declarations


public:
	// public member declarations

	CUT_AccessThread();

	virtual ~CUT_AccessThread();

	// CUT_WSThread Overrides
	virtual void OnConnect();
};

#endif