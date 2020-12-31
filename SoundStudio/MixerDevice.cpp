///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2006-2008 Ernest Laurentin (http://www.ernzo.com/)
//
//  This software is provided 'as-is', without any express or implied
//  warranty. In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source
//  distribution.
//
//  File:       MixerDevice.cpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MixerDevice.hpp"


#pragma comment(lib, "Winmm.lib")

///////////////////////////////////////////////////////////////////////////////
const DWORD MIXER_TYPE_MASK = (MIXER_OBJECTF_HANDLE|MIXER_OBJECTF_MIXER|MIXER_OBJECTF_WAVEOUT|\
                               MIXER_OBJECTF_WAVEIN|MIXER_OBJECTF_MIDIOUT|MIXER_OBJECTF_MIDIIN);


///////////////////////////////////////////////////////////////////////////////
MixerDevice::MixerDevice()
: _hMixer(NULL)
{
}

MixerDevice::~MixerDevice()
{
    Close();
}

bool MixerDevice::IsOpen() const
{
    return (_hMixer != NULL);
}

///////////////////////////////////////////////////////////////////////////////
// GetId
UINT MixerDevice::GetId() const
{
    UINT uMixerId = INVALID_MIXER_ID;
    if ( IsOpen() )
    {
        MMRESULT mmr = mixerGetID(reinterpret_cast<HMIXEROBJ>(_hMixer), &uMixerId, MIXER_OBJECTF_HMIXER);
        (mmr);
    }
    return uMixerId;
}

///////////////////////////////////////////////////////////////////////////////
// Open
HRESULT MixerDevice::Open(UINT uMixerId, DWORD fdwOpen, HWND hWndCallback)
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( !IsOpen() )
    {
        MMRESULT mmr = mixerOpen(&_hMixer, uMixerId, reinterpret_cast<DWORD_PTR>(hWndCallback),
                                 NULL, fdwOpen);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Open
HRESULT MixerDevice::Close()
{
    HRESULT hr = S_FALSE;
    if ( IsOpen() )
    {
        MMRESULT mmr = mixerClose(_hMixer);
        if ( mmr == MMSYSERR_NOERROR )
        {
            _hMixer = NULL;
        }
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetControlDetails
HRESULT MixerDevice::GetControlDetails(MixerControlDetails& mxcd, DWORD fdwDetails) const
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( IsOpen() )
    {
        fdwDetails |= MIXER_OBJECTF_HMIXER;
        MMRESULT mmr = mixerGetControlDetails(reinterpret_cast<HMIXEROBJ>(_hMixer),
                        mxcd, fdwDetails);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// SetControlDetails
HRESULT MixerDevice::SetControlDetails(const MixerControlDetails& mxcd, DWORD fdwDetails)
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( IsOpen() )
    {
        fdwDetails |= MIXER_OBJECTF_HMIXER;
        MMRESULT mmr = mixerSetControlDetails(reinterpret_cast<HMIXEROBJ>(_hMixer),
                        const_cast<MixerControlDetails&>(mxcd), fdwDetails);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetLineControls
HRESULT MixerDevice::GetLineControls(MixerLineControls& mxlcs, DWORD fdwControls) const
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( IsOpen() )
    {
        fdwControls |= MIXER_OBJECTF_HMIXER;
        MMRESULT mmr = mixerGetLineControls(reinterpret_cast<HMIXEROBJ>(_hMixer),
                        mxlcs, fdwControls);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetLineInfo
HRESULT MixerDevice::GetLineInfo(MixerLineInfo& mxli, DWORD fdwInfo) const
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( IsOpen() )
    {
        fdwInfo |= MIXER_OBJECTF_HMIXER;
        MMRESULT mmr = mixerGetLineInfo(reinterpret_cast<HMIXEROBJ>(_hMixer),
                        mxli, fdwInfo);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetDeviceCaps
HRESULT MixerDevice::GetDeviceCaps(MixerCaps& mxcaps) const
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( IsOpen() )
    {
        MMRESULT mmr = mixerGetDevCaps(reinterpret_cast<UINT_PTR>(_hMixer), mxcaps, mxcaps.Size());
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// MixerMessage
HRESULT MixerDevice::MixerMessage(UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( IsOpen() )
    {
        UINT_PTR uMixerId = INVALID_MIXER_ID;
        MMRESULT mmr = mixerGetID(reinterpret_cast<HMIXEROBJ>(_hMixer), &uMixerId, MIXER_OBJECTF_HMIXER);
        if ( mmr == MMSYSERR_NOERROR )
        {
            mmr = mixerMessage(reinterpret_cast<HMIXER>(uMixerId), uMsg, dwParam1, dwParam2);
        }
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetNumDevices
UINT MixerDevice::GetNumDevices()
{
    return mixerGetNumDevs();
}

///////////////////////////////////////////////////////////////////////////////
// GetMixerDeviceID
UINT MixerDevice::GetMixerDeviceID(HMIXEROBJ hmxobj, DWORD flags)
{
    UINT uMixerId = INVALID_MIXER_ID;
    MMRESULT mmr = mixerGetID(hmxobj, &uMixerId, flags);
    (mmr);
    return uMixerId;
}
