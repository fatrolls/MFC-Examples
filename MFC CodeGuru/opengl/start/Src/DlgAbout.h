//********************************************
// DlgAbout.h
//********************************************
// pierre.alliez@cnet.francetelecom.fr
// Created :
// Modified
//********************************************

#ifndef _DIALOG_ABOUT_
#define _DIALOG_ABOUT_

#include "resource.h" 

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif // _DIALOG_ABOUT_



