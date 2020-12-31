// -----------------------------------------------------------------------------
// DestinationsDialog.cpp : implementation file
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
#include "DestinationsDialog.h"

// CDestinationsDialog dialog

IMPLEMENT_DYNAMIC(CDestinationsDialog, CDialog)

// -----------------------------------------------------------------------------
CDestinationsDialog::CDestinationsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDestinationsDialog::IDD, pParent)
	, ndwDest(0)
{
	nInitComplete = 0 ;
}

// -----------------------------------------------------------------------------
CDestinationsDialog::~CDestinationsDialog()
{
}

// -----------------------------------------------------------------------------
void CDestinationsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_DW_DEST,		mdwDest			);
	DDX_Text(pDX, IDC_STATIC_DW_SOURCE,		mcsDwSource		);
	DDX_Text(pDX, IDC_STATIC_DW_LINE_ID,	mcsLineID		);
	DDX_Text(pDX, IDC_STATIC_FDW_LINE,		mcsFdwLine		);
	DDX_Text(pDX, IDC_STATIC_DW_USER,		mcsDwUser		);
	DDX_Text(pDX, IDC_STATIC_DW_COMP_TYPE,	mcsDwType		);
	DDX_Text(pDX, IDC_STATIC_CCHANNELS,		mcChannels		);
	DDX_Text(pDX, IDC_STATIC_CCONNECTIONS,	mcConnections	);
	DDX_Text(pDX, IDC_STATIC_CCONTROLS,		mcControls		);
	DDX_Text(pDX, IDC_STATIC_SZ_SHORTNAME,	mszShortName	);
	DDX_Text(pDX, IDC_STATIC_SZ_NAME,		mszName			);
	DDX_Text(pDX, IDC_STATIC_DW_TYPE,		mcsDwTargetType	);
	DDX_Text(pDX, IDC_STATIC_DW_DEV_ID,		mcsDwDeviceID	);
	DDX_Text(pDX, IDC_STATIC_WMID,			mwMid			);
	DDX_Text(pDX, IDC_STATIC_WPID,			mwPid			);
	DDX_Text(pDX, IDC_STATIC_VDRV_VER,		mvDriverVersion	);
	DDX_Text(pDX, IDC_STATIC_SZ_PNAME,		mszPname		);
}

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CDestinationsDialog, CDialog)
END_MESSAGE_MAP()

// CDestinationsDialog message handlers

// -----------------------------------------------------------------------------
int CDestinationsDialog::SetDisplayValues( MIXERLINE* sData )
{
	mdwDest				= sData->dwDestination		;
    mdwSource			= sData->dwSource			;
    mdwLineID			= sData->dwLineID			;
    mfdwLine			= sData->fdwLine			;
    mdwUser				= (unsigned int)sData->dwUser ;
    mdwComponentType	= sData->dwComponentType	;
    mcChannels			= sData->cChannels			;
    mcConnections		= sData->cConnections		;
    mcControls			= sData->cControls			;
    mszShortName		= sData->szShortName		;
    mszName				= sData->szName				;
	mdwType				= sData->Target.dwType			;
	mdwDeviceID			= sData->Target.dwDeviceID		;
	mwMid				= sData->Target.wMid			;
	mwPid				= sData->Target.wPid			;
	mvDriverVersion		= sData->Target.vDriverVersion	;
	mszPname			= sData->Target.szPname			;

	// Convert formats as required
	mcsDwSource.Format( _T("0x%x"), mdwSource ) ;
	mcsLineID.Format( _T("0x%x"), mdwLineID ) ;

	switch(mfdwLine) {
		case MIXERLINE_LINEF_ACTIVE:		mcsFdwLine = "Active" ; break ;
		case MIXERLINE_LINEF_DISCONNECTED:	mcsFdwLine = "Desconnected" ; break ;
		case MIXERLINE_LINEF_SOURCE:		mcsFdwLine = "Source" ; break ;
		default:
			mcsFdwLine = "Undefined Value" ;
	}

	mcsDwUser.Format( _T("0x%x"), mdwUser ) ;

	switch(mdwComponentType) {
		case MIXERLINE_COMPONENTTYPE_DST_UNDEFINED   : mcsDwType = "Undefined destination - non-std component type"	; break ;
		case MIXERLINE_COMPONENTTYPE_DST_DIGITAL     : mcsDwType = "Digital destination - a CD's digital input"		; break ;
		case MIXERLINE_COMPONENTTYPE_DST_LINE        : mcsDwType = "Line level destination - a CD's line input"		; break ;
		case MIXERLINE_COMPONENTTYPE_DST_MONITOR     : mcsDwType = "Audio line is a destination used for a monitor"	; break ;
		case MIXERLINE_COMPONENTTYPE_DST_SPEAKERS    : mcsDwType = "Destination intended to drive speakers"			; break ;
		case MIXERLINE_COMPONENTTYPE_DST_HEADPHONES  : mcsDwType = "Destination intended to drive Headphones"		; break ;
		case MIXERLINE_COMPONENTTYPE_DST_TELEPHONE   : mcsDwType = "Destination that will be routed to a telephone line" ; break ;
		case MIXERLINE_COMPONENTTYPE_DST_WAVEIN      : mcsDwType = "Destination for wave data - routed to an ADC"	; break ;
		case MIXERLINE_COMPONENTTYPE_DST_VOICEIN     : mcsDwType = "Line is a destination for voice data"			; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED   : mcsDwType = "Undefined source - non-std component type"		; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_DIGITAL     : mcsDwType = "Digital source, digital output from a CD"		; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_LINE        : mcsDwType = "Line-level source - input from external stereo"	; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE  : mcsDwType = "Source originating from a microphone"			; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER : mcsDwType = "Internal synthesizer source - MIDI"				; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC : mcsDwType = "Source originating from an audio CD"			; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE   : mcsDwType = "Source is an incoming telephone line"			; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER   : mcsDwType = "Source originating from PC speaker"				; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT     : mcsDwType = "Source originating from a DAC output"			; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY   : mcsDwType = "source originating from an auxiliary input"		; break ;
		case MIXERLINE_COMPONENTTYPE_SRC_ANALOG      : mcsDwType = "Audio line is an analog source - CD analog output"	; break ;
		default:
			mcsDwType = "Error - value is undefined" ;
	}

	GetDestTargetTypeStr( mdwType, mcsDwTargetType ) ;

	mcsDwDeviceID.Format( _T("0x%x"), mdwDeviceID ) ;

	if( nInitComplete )
		UpdateData( FALSE ) ;

	return 0;
}

// -----------------------------------------------------------------------------
void CDestinationsDialog::GetDestTargetTypeStr( DWORD dwType, CString& strType )
{
		switch( dwType ) 
		{			
			case MIXERLINE_TARGETTYPE_AUX		: strType = "Bound to the auxiliary device"				; break ;
			case MIXERLINE_TARGETTYPE_MIDIIN	: strType = "Bound to the MIDI input device"			; break ;
			case MIXERLINE_TARGETTYPE_MIDIOUT	: strType = "Bound to the MIDI output device"			; break ;
			case MIXERLINE_TARGETTYPE_WAVEIN	: strType = "Bound to the waveform-audio input device"	; break ;
			case MIXERLINE_TARGETTYPE_WAVEOUT	: strType = "Bound to the waveform-audio output device"	; break ;
			case MIXERLINE_TARGETTYPE_UNDEFINED	: strType = "Not bound to a defined media type"			; break ;
			default:
				strType = "Error - value is undefined"	;
	}
}

// -----------------------------------------------------------------------------
BOOL CDestinationsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	nInitComplete = 1 ;
	return TRUE ;
}

// -----------------------------------------------------------------------------

BOOL CDestinationsDialog::DestroyWindow()
{
	nInitComplete = 0 ;
	return CDialog::DestroyWindow();
}

// -----------------------------------------------------------------------------
int CDestinationsDialog::SetTitle( CString szTitle )
{
	SetWindowText( szTitle ) ;
	return 0;
}

// -----------------------------------------------------------------------------
