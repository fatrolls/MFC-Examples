// -----------------------------------------------------------------------------
// MixerCheckBoxMute.h
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

// -----------------------------------------------------------------------------
// CMixerCheckBoxMute

// -----------------------------------------------------------------------------
class CMixerCheckBoxMute : public CButton
{
	DECLARE_DYNAMIC(CMixerCheckBoxMute)

public:
	CMixerCheckBoxMute();
	virtual ~CMixerCheckBoxMute();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg BOOL OnBnClicked();
};

// -----------------------------------------------------------------------------
