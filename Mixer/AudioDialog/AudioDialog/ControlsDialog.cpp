// -----------------------------------------------------------------------------
// ControlsDialog.cpp : implementation file
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
#include "ControlsDialog.h"

// -----------------------------------------------------------------------------
// CControlsDialog dialog

IMPLEMENT_DYNAMIC(CControlsDialog, CDialog)

// -----------------------------------------------------------------------------
CControlsDialog::CControlsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CControlsDialog::IDD, pParent)
{
}

// -----------------------------------------------------------------------------
CControlsDialog::~CControlsDialog()
{
}

// -----------------------------------------------------------------------------
void CControlsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_STATIC_CONTROL_ID       , mdwControlID		 );
	DDX_Text(pDX, IDC_STATIC_CS_CT            , mdwControlType		 );
	DDX_Text(pDX, IDC_STATIC_CS_CT_CLASS      , mcsControlType_Class );
	DDX_Text(pDX, IDC_STATIC_CS_CT_TYPE       , mcsControlType_Type	 );
	DDX_Text(pDX, IDC_STATIC_CS_FDW_CONTROL   , mcsFdwControl		 );
	DDX_Text(pDX, IDC_STATIC_CS_DISABLED      , mcsFwdControl_Dis	 );
	DDX_Text(pDX, IDC_STATIC_CS_MULTIPLE      , mcsFwdControl_Mult	 );
	DDX_Text(pDX, IDC_STATIC_CS_UNIFORM       , mcsFwdControl_Unif	 );
	DDX_Text(pDX, IDC_STATIC_CS_MULTIPLE_ITEMS, mcMultipleItems		 );
	DDX_Text(pDX, IDC_STATIC_CS_SZ_SHORT_NAME , mszShortName		 );
	DDX_Text(pDX, IDC_STATIC_CS_SZ_NAME		  , mszName				 );
	DDX_Text(pDX, IDC_STATIC_BOUNDS_MIN		  , mBoundsMin			 );
	DDX_Text(pDX, IDC_STATIC_BOUNDS_MAX		  , mBoundsMax			 );
	DDX_Text(pDX, IDC_STATIC_METRICS		  , mMetrics			 );
}

// -----------------------------------------------------------------------------
void CControlsDialog::SetDisplayValues( MIXERCONTROL* sMcData )
{
	memcpy( (void*)&mMixerControl, (void*)sMcData, sizeof(MIXERCONTROL) ) ;

	mdwControlID = mMixerControl.dwControlID ;
	mcMultipleItems = mMixerControl.cMultipleItems ;
	mszShortName = mMixerControl.szShortName ;
	mszName = mMixerControl.szName ;
	mBoundsMin = mMixerControl.Bounds.dwMinimum ;
	mBoundsMax = mMixerControl.Bounds.dwMaximum ;
	mMetrics = mMixerControl.Metrics.cSteps ;
	
	SetCustomDlgData() ;
	UpdateData(FALSE) ;
}

// -----------------------------------------------------------------------------
// Format custom MIXERCONTROL data as required
void CControlsDialog::SetCustomDlgData()
{
	CString s1 ;
	DWORD dwCt ;
	DWORD dwFwd ;

	mcsFdwControl.Format( _T("0x%x"), mMixerControl.fdwControl ) ;
	dwFwd = mMixerControl.fdwControl ;

	switch( dwFwd ) 
	{
		case MIXERCONTROL_CONTROLF_UNIFORM  : s1 = _T("MIXERCONTROL_CONTROLF_UNIFORM ") ; break ; 
		case MIXERCONTROL_CONTROLF_MULTIPLE : s1 = _T("MIXERCONTROL_CONTROLF_MULTIPLE") ; break ; 
		case MIXERCONTROL_CONTROLF_DISABLED : s1 = _T("MIXERCONTROL_CONTROLF_DISABLED") ; break ; 	
		default: 
			s1 = _T("Undefined fdwControl value") ;
	}
	mcsFwdControl_Dis.Format(	_T("%s"), s1 ) ; 

	mdwControlType.Format( _T("0x%x"), mMixerControl.dwControlType ) ;

	// Set the Class value for the Control Type
	dwCt = mMixerControl.dwControlType & MIXERCONTROL_CT_CLASS_MASK ;
	switch( dwCt )
	{
		case MIXERCONTROL_CT_CLASS_TIME   : s1 = _T("MIXERCONTROL_CT_CLASS_TIME  ") ; break ; 
		case MIXERCONTROL_CT_CLASS_CUSTOM : s1 = _T("MIXERCONTROL_CT_CLASS_CUSTOM") ; break ; 
		case MIXERCONTROL_CT_CLASS_METER  : s1 = _T("MIXERCONTROL_CT_CLASS_METER ") ; break ; 
		case MIXERCONTROL_CT_CLASS_SWITCH : s1 = _T("MIXERCONTROL_CT_CLASS_SWITCH") ; break ; 
		case MIXERCONTROL_CT_CLASS_NUMBER : s1 = _T("MIXERCONTROL_CT_CLASS_NUMBER") ; break ; 
		case MIXERCONTROL_CT_CLASS_SLIDER : s1 = _T("MIXERCONTROL_CT_CLASS_SLIDER") ; break ; 
		case MIXERCONTROL_CT_CLASS_FADER  : s1 = _T("MIXERCONTROL_CT_CLASS_FADER ") ; break ; 
		case MIXERCONTROL_CT_CLASS_LIST   : s1 = _T("MIXERCONTROL_CT_CLASS_LIST  ") ; break ; 
		default: 
			s1 = _T("Undefined Class") ;
	}
	mcsControlType_Class = s1 ;

	// Set the Type value for the Control Type
	dwCt = mMixerControl.dwControlType ;
	switch( dwCt )
	{
		case MIXERCONTROL_CONTROLTYPE_BASS			 : s1 = _T("MIXERCONTROL_CONTROLTYPE_BASS") ; break ; 
		case MIXERCONTROL_CONTROLTYPE_EQUALIZER		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_EQUALIZER") ; break ;
		case MIXERCONTROL_CONTROLTYPE_FADER			 : s1 = _T("MIXERCONTROL_CONTROLTYPE_FADER") ; break ;
		case MIXERCONTROL_CONTROLTYPE_TREBLE		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_TREBLE") ; break ;
		case MIXERCONTROL_CONTROLTYPE_VOLUME		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_VOLUME") ; break ;
		case MIXERCONTROL_CONTROLTYPE_MIXER			 : s1 = _T("MIXERCONTROL_CONTROLTYPE_MIXER") ; break ;
		case MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT : s1 = _T("MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT") ; break ;
		case MIXERCONTROL_CONTROLTYPE_MUX			 : s1 = _T("MIXERCONTROL_CONTROLTYPE_MUX") ; break ;
		case MIXERCONTROL_CONTROLTYPE_SINGLESELECT	 : s1 = _T("MIXERCONTROL_CONTROLTYPE_SINGLESELECT") ; break ;
		case MIXERCONTROL_CONTROLTYPE_BOOLEANMETER	 : s1 = _T("MIXERCONTROL_CONTROLTYPE_BOOLEANMETER") ; break ;
		case MIXERCONTROL_CONTROLTYPE_PEAKMETER		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_PEAKMETER") ; break ;
		case MIXERCONTROL_CONTROLTYPE_SIGNEDMETER	 : s1 = _T("MIXERCONTROL_CONTROLTYPE_SIGNEDMETER") ; break ;
		case MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER	 : s1 = _T("MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER") ; break ;
		case MIXERCONTROL_CONTROLTYPE_DECIBELS		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_DECIBELS") ; break ;
		case MIXERCONTROL_CONTROLTYPE_PERCENT		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_PERCENT") ; break ;
		case MIXERCONTROL_CONTROLTYPE_SIGNED		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_SIGNED") ; break ;
		case MIXERCONTROL_CONTROLTYPE_UNSIGNED		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_UNSIGNED") ; break ;
		case MIXERCONTROL_CONTROLTYPE_PAN			 : s1 = _T("MIXERCONTROL_CONTROLTYPE_PAN") ; break ;
		case MIXERCONTROL_CONTROLTYPE_QSOUNDPAN		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_QSOUNDPAN") ; break ;
		case MIXERCONTROL_CONTROLTYPE_SLIDER		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_SLIDER") ; break ;
		case MIXERCONTROL_CONTROLTYPE_BOOLEAN		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_BOOLEAN") ; break ;
		case MIXERCONTROL_CONTROLTYPE_BUTTON		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_BUTTON") ; break ;
		case MIXERCONTROL_CONTROLTYPE_LOUDNESS		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_LOUDNESS") ; break ;
		case MIXERCONTROL_CONTROLTYPE_MONO			 : s1 = _T("MIXERCONTROL_CONTROLTYPE_MONO") ; break ;
		case MIXERCONTROL_CONTROLTYPE_MUTE			 : s1 = _T("MIXERCONTROL_CONTROLTYPE_MUTE") ; break ;
		case MIXERCONTROL_CONTROLTYPE_ONOFF			 : s1 = _T("MIXERCONTROL_CONTROLTYPE_ONOFF") ; break ;
		case MIXERCONTROL_CONTROLTYPE_STEREOENH		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_STEREOENH") ; break ;
		case MIXERCONTROL_CONTROLTYPE_MICROTIME		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_MICROTIME") ; break ;
		case MIXERCONTROL_CONTROLTYPE_MILLITIME		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_MILLITIME") ; break ;
		case MIXERCONTROL_CONTROLTYPE_CUSTOM		 : s1 = _T("MIXERCONTROL_CONTROLTYPE_CUSTOM") ; break ;
		default: 
			s1 = _T("Undefined Type") ;	
	}
	mcsControlType_Type = s1 ;							
}

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CControlsDialog, CDialog)
END_MESSAGE_MAP()

// -----------------------------------------------------------------------------
// CControlsDialog message handlers

// -----------------------------------------------------------------------------
void CControlsDialog::SetTitle(CString csTitle)
{
	SetWindowText( csTitle ) ;
}

// -----------------------------------------------------------------------------
