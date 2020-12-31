// -----------------------------------------------------------------------------
// MixerCapsDlg.cpp : implementation file
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// -----------------------------------------------------------------------------

#include "stdafx.h"
#include "MixerCapsDlg.h"

// -----------------------------------------------------------------------------
// CMixerCapsDlg dialog

IMPLEMENT_DYNAMIC(CMixerCapsDlg, CDialog)

// -----------------------------------------------------------------------------
CMixerCapsDlg::CMixerCapsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMixerCapsDlg::IDD, pParent)
	, nWMID(0)
	, nWPID(0)
	, dwDriverVer(0)
	, szProdName(_T(""))
	, dwSupport(0)
	, dwDestCount(0)
{
	nInitComplete = 0 ;
}

// -----------------------------------------------------------------------------
CMixerCapsDlg::~CMixerCapsDlg()
{
}

// -----------------------------------------------------------------------------
void CMixerCapsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_WMD, WMID);
	DDX_Control(pDX, IDC_STATIC_WPID, WPID);
	DDX_Control(pDX, IDC_STATIC_DV, DriverVer);
	DDX_Control(pDX, IDC_STATIC_PROD_NAME, ProdName);
	DDX_Control(pDX, IDC_STATIC_SUPPORT, Support);
	DDX_Control(pDX, IDC_STATIC_N_DESTS, DestCount);
	DDX_Text(pDX, IDC_STATIC_WMD, nWMID);
	DDX_Text(pDX, IDC_STATIC_WPID, nWPID);
	DDX_Text(pDX, IDC_STATIC_DV, dwDriverVer);
	DDX_Text(pDX, IDC_STATIC_PROD_NAME, szProdName);
	DDX_Text(pDX, IDC_STATIC_SUPPORT, dwSupport);
	DDX_Text(pDX, IDC_STATIC_N_DESTS, dwDestCount);
}

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CMixerCapsDlg, CDialog)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// -----------------------------------------------------------------------------
// Set the data display fields with the passed MIXERCAPS structure data
int CMixerCapsDlg::SetDisplayValues(MIXERCAPS* MixerCaps)
{
	nWMID		= MixerCaps->wMid ;
	nWPID		= MixerCaps->wPid ;
	dwDriverVer	= MixerCaps->vDriverVersion ;
	szProdName	= MixerCaps->szPname ;
	dwSupport	= MixerCaps->fdwSupport ;
	dwDestCount	= MixerCaps->cDestinations ;

	if( nInitComplete )
		UpdateData( FALSE ) ;

	return 0;
}

// -----------------------------------------------------------------------------
int CMixerCapsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	nInitComplete = 1 ;
	return 0;
}

// -----------------------------------------------------------------------------
void CMixerCapsDlg::OnDestroy()
{
	CDialog::OnDestroy();
	nInitComplete = 0 ;
}

// -----------------------------------------------------------------------------
