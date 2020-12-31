// -----------------------------------------------------------------------------
// ControlsDialog.h
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

// CControlsDialog dialog

// -----------------------------------------------------------------------------
class CControlsDialog : public CDialog
{
	DECLARE_DYNAMIC(CControlsDialog)

public:
	CControlsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CControlsDialog();

	void SetDisplayValues( MIXERCONTROL* sMcData );
	void SetCustomDlgData() ;
	void SetTitle(CString csTitle) ;

// Dialog Data
	enum { IDD = IDD_CONTROLS_DIALOG };

protected:
	MIXERCONTROL mMixerControl ;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	// 14 Text fields in dialog: 
    UINT	mdwControlID		;	// IDC_STATIC_CONTROL_ID		dw ID value
    CString	mdwControlType		;	// IDC_STATIC_CS_CT				Custom, comprised of a 
	CString	mcsControlType_Class;	// IDC_STATIC_CS_CT_CLASS		Class field and a
	CString mcsControlType_Type	;	// IDC_STATIC_CS_CT_TYPE		Type field
    CString	mcsFdwControl		;	// IDC_STATIC_CS_FDW_CONTROL	Custom, can be any combination of:
	CString	mcsFwdControl_Dis	;	// IDC_STATIC_CS_DISABLED		MIXERCONTROL_CONTROLF_DISABLED
	CString	mcsFwdControl_Mult	;	// IDC_STATIC_CS_MULTIPLE		MIXERCONTROL_CONTROLF_MULTIPLE
	CString	mcsFwdControl_Unif	;	// IDC_STATIC_CS_UNIFORM		MIXERCONTROL_CONTROLF_UNIFORM
    UINT	mcMultipleItems		;	// IDC_STATIC_CS_MULTIPLE_ITEMS	Items per channel 
    CString	mszShortName		;	// IDC_STATIC_CS_SZ_SHORT_NAME  
    CString	mszName				;	// IDC_STATIC_CS_SZ_NAME  
	UINT	mBoundsMin			;	// IDC_STATIC_BOUNDS_MIN  
	UINT	mBoundsMax			;	// IDC_STATIC_BOUNDS_MAX  
	UINT	mMetrics			;	// IDC_STATIC_METRICS			DWORD, cSteps or cbCustomData, 
									//								typically the number of steps in the 
									//								"Bounds" range.
} ;

// -----------------------------------------------------------------------------
