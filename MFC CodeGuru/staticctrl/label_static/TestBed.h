// TestBed.h : main header file for the TESTBED application
//

#if !defined(AFX_TESTBED_H__A4EABEB6_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
#define AFX_TESTBED_H__A4EABEB6_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "Label.h"

/////////////////////////////////////////////////////////////////////////////
// CTestBedApp:
// See TestBed.cpp for the implementation of this class
//

class CTestBedApp : public CWinApp
{
public:
	CTestBedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestBedApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CLabel	m_link;
	CLabel	m_flash;
	CLabel	m_monty;
	CLabel	m_fsize;
	CLabel	m_sunken;
	CLabel	m_border;
	CLabel	m_bold;
	CLabel	m_uline;
	CLabel	m_tcolor;
	CLabel	m_italics;
	CLabel	m_fname;
	CLabel	m_bcolor;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBED_H__A4EABEB6_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
