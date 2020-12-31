// ScreenGrabber.h : main header file for the SCREENGRABBER application
//

#if !defined(AFX_SCREENGRABBER_H__B53D38E6_8037_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_SCREENGRABBER_H__B53D38E6_8037_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScreenGrabberApp:
// See ScreenGrabber.cpp for the implementation of this class
//

class CScreenGrabberApp : public CWinApp
{
public:
	CScreenGrabberApp();

	CString	m_sHotKey;
	UINT	m_nInitialDelay;
	BOOL	m_bInitialDelay;

	int		m_nRadioCapturedArea;

	BOOL	m_bClipboard;
	BOOL	m_bFile;

	BOOL	m_bMaintainRatio;
	BOOL	m_bResize;
	UINT	m_nHeight;
	UINT	m_nWidth;

	BOOL	m_bAutomaticNaming;
	CString	m_sFileName;
	CString	m_sFileType;
	CString	m_sCaptureDir;

	BOOL	m_bHideIcon;
	BOOL	m_bNotifyEnd;

protected:
	void IniAppVars();
	void SaveAppVars();

	CWnd m_wndInvisible;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenGrabberApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScreenGrabberApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENGRABBER_H__B53D38E6_8037_11D1_A3D5_0080C83F712F__INCLUDED_)
