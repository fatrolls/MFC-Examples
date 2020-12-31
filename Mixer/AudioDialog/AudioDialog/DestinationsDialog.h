// -----------------------------------------------------------------------------
// DestinationsDialog.h
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
// CDestinationsDialog dialog

// -----------------------------------------------------------------------------
class CDestinationsDialog : public CDialog
{
	DECLARE_DYNAMIC(CDestinationsDialog)

public:
	CDestinationsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDestinationsDialog();

	virtual BOOL OnInitDialog();
	int SetDisplayValues( MIXERLINE* sData );
	int SetTitle(CString szTitle);
	void GetDestTargetTypeStr( DWORD dwType, CString& strType ) ;

// Dialog Data
	enum { IDD = IDD_DESTINATIONS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL DestroyWindow();

	UINT ndwDest;
	int		nInitComplete ;

	DECLARE_MESSAGE_MAP()
	UINT	mdwDest;									
    UINT	mdwSource;											
    UINT	mdwLineID;											
    UINT	mfdwLine;											
    UINT	mdwUser;											
    UINT	mdwComponentType;									
    UINT	mcChannels;										
    UINT	mcConnections;										
    UINT	mcControls;										
    CString mszShortName;				
    CString mszName;					
	UINT	mdwType;			
	UINT	mdwDeviceID;		
	UINT	mwMid;				
	UINT	mwPid;				
	UINT	mvDriverVersion;	
	CString mszPname;

	CString  mcsDwSource;
	CString  mcsLineID;
	CString  mcsFdwLine;
	CString  mcsDwUser;
	CString  mcsDwType;
	CString  mcsDwTargetType;
	CString  mcsDwDeviceID;
} ;

// -----------------------------------------------------------------------------





