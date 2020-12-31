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
//  File:       WaveInDevice.cpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "WaveInDevice.hpp"

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
WaveInDevice::WaveInDevice()
: _hWaveIn(NULL)
, _lDeviceState(waveClosed)
, _pWaveNotify(NULL)
{
}

WaveInDevice::~WaveInDevice()
{
    Close();
}

bool WaveInDevice::IsOpen() const
{
    return ( _hWaveIn != NULL );
}

///////////////////////////////////////////////////////////////////////////////
// GetId
DWORD_PTR WaveInDevice::GetId() const
{
    DWORD_PTR uID = static_cast<DWORD_PTR>(-1L);
    if ( IsOpen() )
    {
        uID = reinterpret_cast<DWORD_PTR>(_hWaveIn);
    }
    return uID;
}

///////////////////////////////////////////////////////////////////////////////
// GetDeviceStatus
WaveStatus WaveInDevice::GetDeviceStatus() const
{
    WaveStatus wStatus;
    wStatus = static_cast<WaveStatus>( 
        ::InterlockedCompareExchange(const_cast<LONG*>(&_lDeviceState), waveClosed, waveClosed)
        );
    return wStatus;
}

///////////////////////////////////////////////////////////////////////////////
// Open
HRESULT WaveInDevice::Open(UINT uDeviceID,
                           const WaveFormat& wfmt)
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( !IsOpen() )
    {
        MMRESULT mmr = waveInOpen(&_hWaveIn, uDeviceID, const_cast<WaveFormat&>(wfmt),
                                  reinterpret_cast<DWORD_PTR>(WaveInDevice::waveInProc),
                                  reinterpret_cast<DWORD_PTR>(this),
                                  CALLBACK_FUNCTION);
        if ( mmr == MMSYSERR_NOERROR )
        {
            ::InterlockedExchange(&_lDeviceState, waveStopped);
        }
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Close
HRESULT WaveInDevice::Close()
{
    HRESULT hr = S_FALSE;
    if ( IsOpen() )
    {
        hr = Stop();
        MMRESULT mmr = waveInClose(_hWaveIn);
        if ( mmr == MMSYSERR_NOERROR )
        {
            ::InterlockedExchange(&_lDeviceState, waveClosed);
            _hWaveIn = NULL;
        }
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Start
HRESULT WaveInDevice::Start()
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveInStart(_hWaveIn);
        if ( mmr == MMSYSERR_NOERROR )
        {
            ::InterlockedExchange(&_lDeviceState, waveStarted);
        }
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Stop
HRESULT WaveInDevice::Stop()
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveInReset(_hWaveIn);
        if ( mmr == MMSYSERR_NOERROR )
        {
            ::InterlockedExchange(&_lDeviceState, waveStopped);
            mmr = waveInStop(_hWaveIn);
        }
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Reset
HRESULT WaveInDevice::Reset()
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveInReset(_hWaveIn);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Pause
HRESULT WaveInDevice::Pause()
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        // can't pause input waveform
        MMRESULT mmr = waveInReset(_hWaveIn);
        if ( mmr == MMSYSERR_NOERROR )
        {
            ::InterlockedExchange(&_lDeviceState, wavePaused);
        }
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetPosition
HRESULT WaveInDevice::GetPosition(WaveTime& wti) const
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveInGetPosition(_hWaveIn, wti, wti.Size());
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// AddBuffer
HRESULT WaveInDevice::AddBuffer( WaveBuffer& wbuf )
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveInAddBuffer(_hWaveIn, wbuf, wbuf.Size());
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// PrepareBuffer
HRESULT WaveInDevice::PrepareBuffer( WaveBuffer& wbuf )
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveInPrepareHeader(_hWaveIn, wbuf, wbuf.Size());
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// UnprepareBuffer
HRESULT WaveInDevice::UnprepareBuffer( WaveBuffer& wbuf )
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveInPrepareHeader(_hWaveIn, wbuf, wbuf.Size());
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// SetNotifyHandler
HRESULT WaveInDevice::SetNotifyHandler(IWaveNotifyHandler* pNotify)
{
    // only one handler is supported. Override this or create new member to support list of handlers
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( pNotify != NULL )
    {
        if ( _pWaveNotify == NULL ) {
            ::InterlockedExchangePointer(reinterpret_cast<void**>(&_pWaveNotify), pNotify);
            hr = S_OK;
        }
    }
    else
    {
        ::InterlockedExchangePointer(reinterpret_cast<void**>(&_pWaveNotify), NULL);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ProcessEvent
void WaveInDevice::ProcessEvent(UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR /*dwParam2*/)
{
    if ( _pWaveNotify != NULL )
    {
        _pWaveNotify->ProcessEvent(this, uMsg, reinterpret_cast<WaveBuffer*>(dwParam1));
    }
}

///////////////////////////////////////////////////////////////////////////////
// waveInProc
void WaveInDevice::waveInProc(HWAVEIN /*hwi*/,
                         UINT uMsg,
                         DWORD_PTR dwInstance,
                         DWORD dwParam1,
                         DWORD dwParam2)
{
    WaveInDevice* _this = reinterpret_cast<WaveInDevice*>( dwInstance );
    if ( _this )
        _this->ProcessEvent(uMsg, dwParam1, dwParam2);
}

///////////////////////////////////////////////////////////////////////////////
// GetDevicesCount
UINT WaveInDevice::GetDevicesCount()
{
    return waveInGetNumDevs();
}

///////////////////////////////////////////////////////////////////////////////
// GetDeviceCaps
HRESULT WaveInDevice::GetDeviceCaps(UINT uDeviceID, WaveInCaps& wic)
{
    HRESULT hr;
    MMRESULT mmr = waveInGetDevCaps(uDeviceID, wic, wic.Size());
    hr = HRESULT_FROM_WIN32(mmr);
    return hr;
}
