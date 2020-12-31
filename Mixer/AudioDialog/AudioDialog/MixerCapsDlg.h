// -----------------------------------------------------------------------------
// MixerCapsDlg.h 
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// -----------------------------------------------------------------------------

#pragma once

#include "afxwin.h"

// -----------------------------------------------------------------------------
// CMixerCapsDlg dialog

// -----------------------------------------------------------------------------
class CMixerCapsDlg : public CDialog
{
	DECLARE_DYNAMIC(CMixerCapsDlg)

public:
	CMixerCapsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMixerCapsDlg();

	// Set the data display fields with the passed MIXERCAPS structure data
	int SetDisplayValues(MIXERCAPS* MixerCaps);

// Dialog Data
	enum { IDD = IDD_MIXER_CAPS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CStatic WMID;
	CStatic WPID;
	CStatic DriverVer;
	CStatic ProdName;
	CStatic Support;
	CStatic DestCount;

	UINT	nWMID;
	UINT	nWPID;
	DWORD	dwDriverVer;
	CString	szProdName;
	DWORD	dwSupport;
	DWORD	dwDestCount;

	int		nInitComplete ;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
} ;

// -----------------------------------------------------------------------------
