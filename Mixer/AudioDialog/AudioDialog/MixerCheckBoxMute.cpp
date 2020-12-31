// -----------------------------------------------------------------------------
// MixerCheckBoxMute.cpp : implementation file
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
#include "MixerCheckBoxMute.h"

// -----------------------------------------------------------------------------
// CMixerCheckBoxMute

IMPLEMENT_DYNAMIC(CMixerCheckBoxMute, CButton)

// -----------------------------------------------------------------------------
CMixerCheckBoxMute::CMixerCheckBoxMute()
{
}

// -----------------------------------------------------------------------------
CMixerCheckBoxMute::~CMixerCheckBoxMute()
{
}

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CMixerCheckBoxMute, CButton)
	ON_CONTROL_REFLECT_EX(BN_CLICKED, &CMixerCheckBoxMute::OnBnClicked)
END_MESSAGE_MAP()

// -----------------------------------------------------------------------------
// CMixerCheckBoxMute message handlers

// -----------------------------------------------------------------------------
BOOL CMixerCheckBoxMute::OnBnClicked()
{
	int n1 = GetDlgCtrlID() ;
	return FALSE ;	// "Send" the message back to the parent windows
	//return TRUE ;	// Don't "Send" the message back to the parent windows
}

// -----------------------------------------------------------------------------
