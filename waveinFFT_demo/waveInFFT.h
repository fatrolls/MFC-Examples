// waveInFFT.h : main header file for the WAVEINFFT application
//

#if !defined(AFX_WAVEINFFT_H__79926059_885C_4898_BF2F_9C0B31C2EEC2__INCLUDED_)
#define AFX_WAVEINFFT_H__79926059_885C_4898_BF2F_9C0B31C2EEC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWaveInFFTApp:
// See waveInFFT.cpp for the implementation of this class
//

class CWaveInFFTApp : public CWinApp
{
public:
	CWaveInFFTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveInFFTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWaveInFFTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEINFFT_H__79926059_885C_4898_BF2F_9C0B31C2EEC2__INCLUDED_)
