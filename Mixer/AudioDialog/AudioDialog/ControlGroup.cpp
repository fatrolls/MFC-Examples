// -----------------------------------------------------------------------------
// ControlGroup.cpp
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// Create an array of control groups for the selected mixer and destination. 
// A control group consists of balance, volume, and mute controls. A group 
// is created for the destination and each connection associated with the 
// destination. If there are no controls for a destination or connection, no 
// group is created. 
// -----------------------------------------------------------------------------

#include "StdAfx.h"
#include "Resource.h"
#include "ControlGroup.h"

// -----------------------------------------------------------------------------
CControlGroup::CControlGroup(void)
{
	mpCStaticLabel   = NULL ;
	mpCStaticBal     = NULL ;
	mpCStaticVol     = NULL ;
	mpCSliderCtrlBal = NULL ;
	mpCSliderCtrlVol = NULL ;
	mpCCheckBoxMute  = NULL ;
	mpCtrl_LUT		 = NULL ;
}

// -----------------------------------------------------------------------------
CControlGroup::~CControlGroup(void)
{
	if( mpCStaticLabel   ) delete [] mpCStaticLabel   ;
	if( mpCStaticBal     ) delete [] mpCStaticBal     ;
	if( mpCSliderCtrlBal ) delete [] mpCSliderCtrlBal ;
	if( mpCStaticVol     ) delete [] mpCStaticVol     ;
	if( mpCSliderCtrlVol ) delete [] mpCSliderCtrlVol ;
	if( mpCCheckBoxMute  ) delete [] mpCCheckBoxMute  ; 
	if( mpCtrl_LUT       ) delete [] mpCtrl_LUT		  ; 
}

// -----------------------------------------------------------------------------
// Create a new group of controls based on the reference group (bal, vol, mute). 
// destIndex is the mixer destination index number for the control group. 
// -----------------------------------------------------------------------------
int CControlGroup::CreateControls( CMixer* pCMixer, int destIndex, CWnd* pcWnd, 
				int offsetX, int offsetY, unsigned int resourceID )
{
	int n1 ;
	int nRet ;
	CRect cr ;
	int groupIndex = 0 ;
	int connectionIndex ;
	int connectionCount ;
	int nControlCount ;
	MIXERLINE mixerLine ;
	MIXERCONTROL mixerControl ;

	sChannelData channelData ;
	unsigned int nSize ;

	mpCMixer = pCMixer ;
	mDestID  = destIndex ;
	mpcWnd   = pcWnd ;
	mOffsetX = offsetX ;
	mOffsetY = offsetY ;
	nextResourceID = resourceID ;
	CString csTemp ;

	// Allocate memory for all controls 
	connectionCount = pCMixer->GetConnectionCount( destIndex ) ;
	mnGroups = 1 + connectionCount ;
	mpCStaticLabel   = new CStatic[mnGroups] ;
	mpCStaticBal     = new CStatic[mnGroups] ;
	mpCSliderCtrlBal = new CMixerSliderHorz[mnGroups] ;
	mpCStaticVol     = new CStatic[mnGroups] ;
	mpCSliderCtrlVol = new CMixerSliderCtrl[mnGroups] ;
	mpCCheckBoxMute  = new CMixerCheckBoxMute[mnGroups] ;

	// LUT for vol, bal, mute controls
	Ctrl_LUT_Count = mnGroups * 3 ;			
	Ctrl_LUT_Index = 0 ;
	mpCtrl_LUT = new sCtrl_LUT[ Ctrl_LUT_Count ] ;

	groupIndex = 0 ;
	offsetX = -mOffsetX ;	// Set offset to overlay reference control group
	offsetY = -mOffsetY ;

	// ------------- Create destination control group 
	pCMixer->GetDestInfo( destIndex, &mixerLine ) ;
	
	// Set destination title 
	GetDestTargetTypeStr( mixerLine.Target.dwType, csTemp ) ;
	csTemp = TEXT("Destination ") + csTemp ;
	pcWnd->GetDlgItem( IDC_DEST_LABEL_STATIC )->SetWindowTextW( csTemp ) ;

	// Unless there are no destination controls, a destination control group 
	// is always created. 
	nControlCount = pCMixer->GetDestinationControlCount(destIndex) ;
	if( nControlCount != 0 )
	{
		offsetX += mOffsetX ;
		offsetY += mOffsetY ;

		// Set group label
		InitGroupLabel(  mixerLine.szName, groupIndex, offsetX, offsetY ) ;

		// Init balance control
		InitBalanceLabel( TEXT("Balance"), groupIndex, offsetX, offsetY ) ;
		n1 = 0 ;
		do			// Must go through loop at least once to create control 
		{
			pCMixer->GetDestControlMetrics( destIndex, n1, &mixerControl ) ;
			channelData.nChannels = mixerLine.cChannels ;
			nSize = sizeof(channelData.stateData) ;
			pCMixer->GetDestControlState( destIndex, n1, &channelData.stateData, &nSize ) ;
			nRet = InitBalSlider( mixerControl, channelData, groupIndex, offsetX, offsetY ) ;
			if( nRet >= 0 )
				break ;
			n1++ ;
		} while( n1<nControlCount ) ;
		if( mixerLine.cChannels < 2 )
			mpCSliderCtrlBal[groupIndex].EnableWindow( FALSE ) ; 

		// Init volume control
		InitVolLabel( TEXT("Volume"), groupIndex, offsetX, offsetY ) ;
		n1 = 0 ;
		do
		{
			pCMixer->GetDestControlMetrics( destIndex, n1, &mixerControl ) ;
			channelData.nChannels = mixerLine.cChannels ;
			nSize = sizeof(channelData.stateData) ;
			pCMixer->GetDestControlState( destIndex, n1, &channelData.stateData, &nSize ) ;
			if( InitVolSlider( mixerControl, channelData, groupIndex, offsetX, offsetY ) >= 0 )
				break ;
			n1++ ;
		} while( n1<nControlCount ) ;

		// Init mute check box control
		n1 = 0 ;
		do
		{
			pCMixer->GetDestControlMetrics( destIndex, n1, &mixerControl ) ;
			channelData.nChannels = mixerLine.cChannels ;
			nSize = sizeof(channelData.stateData) ;
			pCMixer->GetDestControlState( destIndex, n1, &channelData.stateData, &nSize ) ;
			if( InitCheckBox( mixerControl, channelData, groupIndex, offsetX, offsetY ) >= 0 )
				break ;
			n1++ ;
		} while( n1<nControlCount ) ;
		if( n1 >= nControlCount  &&  nControlCount != 0 )
			mpCCheckBoxMute[groupIndex].EnableWindow( FALSE ) ;
	}

	// ------------- Create destination connection control groups 
	for( connectionIndex=0 ; connectionIndex < connectionCount ; connectionIndex++ )
	{
		pCMixer->GetConnectionInfo( destIndex, connectionIndex, &mixerLine ) ;

		// Unless there are no controls for this connection, a connection 
		// control group is always created. 
		nControlCount = pCMixer->GetConnectionControlCount(destIndex, connectionIndex) ;
		if( nControlCount != 0 )
		{
			groupIndex++ ;
			offsetX += mOffsetX ;
			offsetY += mOffsetY ;

			// Set group label
			InitGroupLabel(  mixerLine.szName, groupIndex, offsetX, offsetY ) ;

			// Init balance control
			InitBalanceLabel( TEXT("Balance"), groupIndex, offsetX, offsetY ) ;

			n1 = 0 ;
			do			// Must go through loop at least once to create control 
			{
				pCMixer->GetConnectionControlMetrics( destIndex, connectionIndex, n1, &mixerControl ) ;
				channelData.nChannels = mixerLine.cChannels ;
				nSize = sizeof(channelData.stateData) ;
				pCMixer->GetConnectionControlState( destIndex, connectionIndex, n1, 
													&channelData.stateData, &nSize ) ;
				nRet = InitBalSlider( mixerControl, channelData, groupIndex, offsetX, offsetY ) ;
				if( nRet >= 0 )
					break ;
				n1++ ;
			} while( n1<nControlCount ) ;
			if( mixerLine.cChannels < 2  ||  nRet < 0 )
				mpCSliderCtrlBal[groupIndex].EnableWindow( FALSE ) ; 

			// Init volume control 
			InitVolLabel( TEXT("Volume"), groupIndex, offsetX, offsetY ) ;
			n1 = 0 ;
			do
			{
				pCMixer->GetConnectionControlMetrics( destIndex, connectionIndex, n1, &mixerControl ) ;
				channelData.nChannels = mixerLine.cChannels ;
				nSize = sizeof(channelData.stateData) ;
				pCMixer->GetConnectionControlState( destIndex, connectionIndex, n1, 
													&channelData.stateData, &nSize ) ;
				if( InitVolSlider( mixerControl, channelData, groupIndex, offsetX, offsetY ) >= 0 )
					break ;
				n1++ ;
			} while( n1<nControlCount ) ;
			if( n1 >= nControlCount )
				mpCSliderCtrlVol[groupIndex].EnableWindow( FALSE ) ;

			// Init mute check box control
			n1 = 0 ;
			do
			{
				pCMixer->GetConnectionControlMetrics( destIndex, connectionIndex, n1, &mixerControl ) ;
				channelData.nChannels = mixerLine.cChannels ;
				nSize = sizeof(channelData.stateData) ;
				pCMixer->GetConnectionControlState( destIndex, connectionIndex, n1, 
													&channelData.stateData, &nSize ) ;
				if( InitCheckBox( mixerControl, channelData, groupIndex, offsetX, offsetY ) >= 0 )
					break ;
				n1++ ;
			} while( n1<nControlCount ) ;
			if( n1 >= nControlCount )
				mpCCheckBoxMute[groupIndex].EnableWindow( FALSE ) ;
		}
	}

	return 0 ;
}

// -----------------------------------------------------------------------------
// Control group label  - from dest or connection data
void CControlGroup::InitGroupLabel( CString csLabel, int groupIndex, int offsetX, 
								    int offsetY )
{
	CRect cr ;
	CWnd* pCWnd ;
	WINDOWINFO winInfo ;
	CFont* pFont ;

	pCWnd = mpcWnd->GetDlgItem( IDC_STATIC_LABEL ) ; 
	pCWnd->GetWindowInfo( &winInfo ) ;
	pFont = pCWnd->GetFont() ;
	cr = winInfo.rcWindow ;
	mpcWnd->ScreenToClient( &cr ) ;
	cr.MoveToXY( cr.left+offsetX, cr.top+offsetY) ;
	mpCStaticLabel[groupIndex].Create( csLabel, winInfo.dwStyle|WS_VISIBLE, cr, mpcWnd, nextResourceID ) ;
	nextResourceID++ ;
	mpCStaticLabel[groupIndex].SetFont(pFont) ;
}

// -----------------------------------------------------------------------------
// Balance slider label - "Balance" 
void CControlGroup::InitBalanceLabel( CString csText, int groupIndex, int offsetX, 
									  int offsetY ) 
{
	CRect cr ;
	CWnd* pCWnd ;
	WINDOWINFO winInfo ;
	CFont* pFont ;

	pCWnd = mpcWnd->GetDlgItem( IDC_STATIC_BAL ) ; 
	pCWnd->GetWindowInfo( &winInfo ) ;
	pFont = pCWnd->GetFont() ;
	cr = winInfo.rcWindow ;
	mpcWnd->ScreenToClient( &cr ) ;
	cr.MoveToXY( cr.left+offsetX, cr.top+offsetY) ;
	mpCStaticBal[groupIndex].Create( csText, winInfo.dwStyle|WS_VISIBLE, cr, mpcWnd, nextResourceID ) ;
	nextResourceID++ ;
	mpCStaticBal[groupIndex].SetFont(pFont) ;
}

// -----------------------------------------------------------------------------
// Always create a balance slider
// Returns -1 if no volume control is found or the mixer control data is bad
int CControlGroup::InitBalSlider( MIXERCONTROL mixerControl, sChannelData channelData, 
								   int groupIndex, int offsetX, int offsetY )
{
	CRect cr ;
	CWnd* pCWnd ;
	WINDOWINFO winInfo ;
	HWND hWnd ;
	int nMin, nMax ;
	int nRet = -1 ;
	CFont* pFont ;

	hWnd = mpCSliderCtrlBal[groupIndex].GetSafeHwnd() ;
	if( !hWnd )	// If this is the first time here, create the bal slider
	{
		pCWnd = mpcWnd->GetDlgItem( IDC_SLIDER_BAL ) ; 
		pCWnd->GetWindowInfo( &winInfo ) ;
		pFont = pCWnd->GetFont() ;
		cr = winInfo.rcWindow ;
		mpcWnd->ScreenToClient( &cr ) ;
		cr.MoveToXY( cr.left+offsetX, cr.top+offsetY) ;
		mpCSliderCtrlBal[groupIndex].Create( winInfo.dwStyle|WS_VISIBLE, cr, mpcWnd, nextResourceID ) ;
		mpCSliderCtrlBal[groupIndex].GetRange( nMin, nMax ) ;
		mpCSliderCtrlBal[groupIndex].SetPos( (nMax-nMin)/2 ) ;
		mpCSliderCtrlBal[groupIndex].SetTic( (nMax-nMin)/2 ) ;
		mpCSliderCtrlBal[groupIndex].SetFont(pFont) ;
		mpCtrl_LUT[Ctrl_LUT_Index].winCtrlID = nextResourceID ;
		mpCtrl_LUT[Ctrl_LUT_Index].CtrlType = Bal ;
		mpCtrl_LUT[Ctrl_LUT_Index].mixerCtrlID = 0xffff ;
		mpCtrl_LUT[Ctrl_LUT_Index].groupIndex = groupIndex ;
		mpCtrl_LUT[Ctrl_LUT_Index++].cWnd = (CWnd*)&mpCSliderCtrlBal[groupIndex] ;
		nextResourceID++ ;
	}

	if( !(mixerControl.dwControlType ^ MIXERCONTROL_CONTROLTYPE_VOLUME) )
	{
		// Set control ranges based on vol (fader) control, etc. 
		mpCSliderCtrlBal[groupIndex].Init( mixerControl, channelData.nChannels, 
												(void*)&channelData.stateData ) ;	
		mpCtrl_LUT[Ctrl_LUT_Index-1].mixerCtrlID = mixerControl.dwControlID ;
		nRet = 1 ;	// Volume control found, success return
	}

	return nRet ; 
}

// -----------------------------------------------------------------------------
// Vertical slider label - "Volume:" 
void CControlGroup::InitVolLabel( CString csText, int groupIndex, int offsetX, 
								 int offsetY ) 
{
	CRect cr ;
	CWnd* pCWnd ;
	WINDOWINFO winInfo ;
	CFont* pFont ;

	pCWnd = mpcWnd->GetDlgItem( IDC_STATIC_VOL ) ; // IDC_STATIC_VOL_TITLE
	pCWnd->GetWindowInfo( &winInfo ) ;
	pFont = pCWnd->GetFont() ;
	cr = winInfo.rcWindow ;
	mpcWnd->ScreenToClient( &cr ) ;
	cr.MoveToXY( cr.left+offsetX, cr.top+offsetY) ;
	mpCStaticVol[groupIndex].Create( csText, winInfo.dwStyle|WS_VISIBLE, cr, mpcWnd, nextResourceID ) ;
	nextResourceID++ ;
	mpCStaticVol[groupIndex].SetFont(pFont) ;
}

// -----------------------------------------------------------------------------
// Always create a volume slider 
// Returns -1 if no volume control is found or the mixer control data is bad
int CControlGroup::InitVolSlider( MIXERCONTROL mixerControl, sChannelData channelData, 
								  int groupIndex, int offsetX, int offsetY )
{
	CRect cr ;
	CWnd* pCWnd ;
	WINDOWINFO winInfo ;
	HWND hWnd ;
	int nMin, nMax, nPos, n1 ;
	int nRet = -1 ;

	hWnd = mpCSliderCtrlVol[groupIndex].GetSafeHwnd() ;
	if( !hWnd )	// If this is the first time here, create the vol slider
	{
		pCWnd = mpcWnd->GetDlgItem( IDC_SLIDER_VOL ) ;
		pCWnd->GetWindowInfo( &winInfo ) ;
		cr = winInfo.rcWindow ;
		mpcWnd->ScreenToClient( &cr ) ;
		cr.MoveToXY( cr.left+offsetX, cr.top+offsetY) ;
		mpCSliderCtrlVol[groupIndex].Create( winInfo.dwStyle|WS_VISIBLE, cr, mpcWnd, nextResourceID ) ;
		mpCSliderCtrlVol[groupIndex].GetRange( nMin, nMax ) ;
		mpCSliderCtrlVol[groupIndex].SetPos( nMin ) ;
		for( n1=0 ; n1<6 ; n1++ )	// 7 Tics
		{
			nPos = (n1*nMax - n1*nMin)/6 ;
			mpCSliderCtrlVol[groupIndex].SetTic( nPos ) ;
		}
		mpCtrl_LUT[Ctrl_LUT_Index].winCtrlID = nextResourceID ;
		mpCtrl_LUT[Ctrl_LUT_Index].CtrlType = Vol ;
		mpCtrl_LUT[Ctrl_LUT_Index].mixerCtrlID = 0xffff ;
		mpCtrl_LUT[Ctrl_LUT_Index].groupIndex = groupIndex ;
		mpCtrl_LUT[Ctrl_LUT_Index++].cWnd = (CWnd*)&mpCSliderCtrlVol[groupIndex] ;
		nextResourceID++ ;
	}

	if( !(mixerControl.dwControlType ^ MIXERCONTROL_CONTROLTYPE_VOLUME) )
	{
		mpCSliderCtrlVol[groupIndex].Init( mixerControl, channelData.nChannels, 
												(void*)&channelData.stateData ) ;	
		mpCtrl_LUT[Ctrl_LUT_Index-1].mixerCtrlID = mixerControl.dwControlID ;
		nRet = 1 ;	// Volume control found, success return 
	}

	return nRet ; 
}

// -----------------------------------------------------------------------------
// Always create a mute check box. 
int CControlGroup::InitCheckBox( MIXERCONTROL mixerControl, sChannelData channelData, 
								 int groupIndex, int offsetX, int offsetY ) 
{
	CRect cr ;
	CWnd* pCWnd ;
	WINDOWINFO winInfo ;
	HWND hWnd ;
	CFont* pFont ;
	int nRet = -1 ;

	hWnd = mpCCheckBoxMute[groupIndex].GetSafeHwnd() ;
	if( !hWnd )	// If this is the first time here, create the mute check box
	{
		pCWnd = mpcWnd->GetDlgItem( IDC_CHECK_MUTE ) ; 
		pCWnd->GetWindowInfo( &winInfo ) ;
		pFont = pCWnd->GetFont() ;
		cr = winInfo.rcWindow ;
		mpcWnd->ScreenToClient( &cr ) ;
		cr.MoveToXY( cr.left+offsetX, cr.top+offsetY) ;
		mpCCheckBoxMute[groupIndex].Create( TEXT("Mute"), winInfo.dwStyle|WS_VISIBLE, cr, mpcWnd, nextResourceID ) ;
		mpCCheckBoxMute[groupIndex].SetFont(pFont) ;
		mpCtrl_LUT[Ctrl_LUT_Index].winCtrlID = nextResourceID ;
		mpCtrl_LUT[Ctrl_LUT_Index].CtrlType = Mute ;
		mpCtrl_LUT[Ctrl_LUT_Index].mixerCtrlID = 0xffff ;
		mpCtrl_LUT[Ctrl_LUT_Index].groupIndex = groupIndex ;
		mpCtrl_LUT[Ctrl_LUT_Index++].cWnd = (CWnd*)&mpCCheckBoxMute[groupIndex] ;
		nextResourceID++ ;
	}

	if( !(mixerControl.dwControlType ^ MIXERCONTROL_CONTROLTYPE_MUTE) )
	{
		if( channelData.stateData.Left.dwValue > 0 )
			mpCCheckBoxMute[groupIndex].SetCheck( BST_CHECKED ) ;
		
		mpCtrl_LUT[Ctrl_LUT_Index-1].mixerCtrlID = mixerControl.dwControlID ;
		nRet = 1 ;	// Mute found, success return
	}

	return nRet ;	
}

// -----------------------------------------------------------------------------
// Update the windows control state for windows control associated with the 
// passed mixer control ID. Called by the message loop handler for a mixer 
// control change message. 
int CControlGroup::UpdateWinControlState( unsigned int mixerCtrlID ) 
{
	unsigned int n1 ;
	unsigned int nSize ;
	int nRet = 0 ;
	sStateData state ;
	CMixerSliderCtrl*   pVolCtrl  = NULL ;
	CMixerSliderHorz*   pBalCtrl  = NULL ;
	CMixerCheckBoxMute* pMuteCtrl = NULL ;

	// Get control state for the passed mixer ID
	nSize = sizeof(sStateData) ;
	nRet = mpCMixer->GetControlState( mixerCtrlID, &state, &nSize ) ;
	if( nRet < 0 )
		return -1 ;

	// Get the associated windows control
	for( n1=0 ; n1<Ctrl_LUT_Count  ; n1++ )
	{
		if( mpCtrl_LUT[n1].mixerCtrlID == mixerCtrlID )
			break ;
	}

	if( n1 >= Ctrl_LUT_Count )
		return -1 ;				// Control not found

	// Set the windows control state
	GetControlsForID( mpCtrl_LUT[n1].groupIndex, &pVolCtrl, &pBalCtrl, &pMuteCtrl ) ;
	switch( mpCtrl_LUT[n1].CtrlType )
	{
	case Vol:	
	case Bal:
		// Must adjust volume as well as balance
		pVolCtrl->SetCurrentPos( state.Left.dwValue, state.Right.dwValue ) ;
		pBalCtrl->SetCurrentPos( state.Left.dwValue, state.Right.dwValue ) ;
		break ;

	case Mute:
		if( state.Right.dwValue != 0  ||  state.Left.dwValue != 0 )
			pMuteCtrl->SetCheck( BST_CHECKED ) ;
		else
			pMuteCtrl->SetCheck( BST_UNCHECKED ) ;
		break ;
	}

	return 0 ;
}

// -----------------------------------------------------------------------------
// Update the state of a mixer control associated with a windows control. 
// Called by message loop handlers for windows control events
int CControlGroup::UpdateMixerControlState( unsigned int winCtrlID )
{
	unsigned int n1 ;
	unsigned int nSize ;
	int nChecked ;
	int nRet = 0 ;
	DWORD nRange ;	
	DWORD nVol ;	
	sStateData state ;
	CMixerSliderCtrl*   pVolCtrl  = NULL ;
	CMixerSliderHorz*   pBalCtrl  = NULL ;
	CMixerCheckBoxMute* pMuteCtrl = NULL ;

	for( n1=0 ; n1<Ctrl_LUT_Count  ; n1++ )	// Find the control
	{
		if( mpCtrl_LUT[n1].winCtrlID == winCtrlID )
			break ;
	}

	if( n1 >= Ctrl_LUT_Count )
		return -1 ;				// Control not found

	// Control found, update the dwID mixer control
	nSize = sizeof(sStateData) ;
	GetControlsForID( mpCtrl_LUT[n1].groupIndex, &pVolCtrl, &pBalCtrl, &pMuteCtrl ) ;
	state.Right.dwValue = state.Left.dwValue = 0 ;
	switch( mpCtrl_LUT[n1].CtrlType )
	{
	case Vol:	
		// Get windows volume control state info
		pVolCtrl->GetCurrentPos( &nVol, &nRange );
		state.Right.dwValue = state.Left.dwValue = nVol;
		// Update volume for both channels
		pBalCtrl->GetCurrentPos( &state.Left.dwValue, &state.Right.dwValue, (int*)&nRange );
		// Set mixer control state														   
		mpCMixer->SetControlState( mpCtrl_LUT[n1].mixerCtrlID, &state, &nSize ) ;	
		break ;

	case Bal:
		// Vol may have changed, get the control's current channel volume values.
		nRet = mpCMixer->GetControlState( mpCtrl_LUT[n1].mixerCtrlID, &state, &nSize ) ;
		pBalCtrl->GetCurrentPos( &state.Left.dwValue, &state.Right.dwValue, (int*)&nRange );
		nRet = mpCMixer->SetControlState( mpCtrl_LUT[n1].mixerCtrlID, &state, &nSize ) ;	
		break ;

	case Mute:
		nChecked = ((CMixerCheckBoxMute*)mpCtrl_LUT[n1].cWnd)->GetCheck() ;
		state.Right.dwValue = state.Left.dwValue = 0 ;
		if( nChecked == BST_CHECKED ) 
			state.Right.dwValue = state.Left.dwValue = 1 ;
		mpCMixer->SetControlState( mpCtrl_LUT[n1].mixerCtrlID, &state, &nSize ) ;	
		break ;

	default:
		nRet = -1 ;
	} 

	return nRet ;
}

// -----------------------------------------------------------------------------
// Get all controls for a given mixer control ID
int CControlGroup::GetControlsForID( unsigned int groupIndex, CMixerSliderCtrl** pVolCtrl, 
					CMixerSliderHorz** pBalCtrl, CMixerCheckBoxMute** pMuteCtrl )
{
	int nFound = 0 ;
	unsigned int n1 ;
	for( n1=0 ; n1<Ctrl_LUT_Count ; n1++ )
	{
		if( groupIndex == mpCtrl_LUT[n1].groupIndex )
		{
			nFound++ ;
			     if( mpCtrl_LUT[n1].CtrlType == Vol ) *pVolCtrl  = (CMixerSliderCtrl*  )mpCtrl_LUT[n1].cWnd ;
			else if( mpCtrl_LUT[n1].CtrlType == Bal ) *pBalCtrl  = (CMixerSliderHorz*  )mpCtrl_LUT[n1].cWnd ;
			else if( mpCtrl_LUT[n1].CtrlType == Mute) *pMuteCtrl = (CMixerCheckBoxMute*)mpCtrl_LUT[n1].cWnd ;
			if( nFound > 2 )
				break ;
		}
	}
	return nFound ;
}

// -----------------------------------------------------------------------------
void CControlGroup::GetDestTargetTypeStr( DWORD dwType, CString& strType )
{
		switch( dwType ) 
		{			
			case MIXERLINE_TARGETTYPE_AUX		: strType = "bound to the auxiliary device"				; break ;
			case MIXERLINE_TARGETTYPE_MIDIIN	: strType = "bound to the MIDI input device"			; break ;
			case MIXERLINE_TARGETTYPE_MIDIOUT	: strType = "bound to the MIDI output device"			; break ;
			case MIXERLINE_TARGETTYPE_WAVEIN	: strType = "bound to the waveform-audio input device"	; break ;
			case MIXERLINE_TARGETTYPE_WAVEOUT	: strType = "bound to the waveform-audio output device"	; break ;
			case MIXERLINE_TARGETTYPE_UNDEFINED	: strType = "not bound to a defined media type"			; break ;
			default:
				strType = "Error - value is undefined"	;
	}
}

// -----------------------------------------------------------------------------
