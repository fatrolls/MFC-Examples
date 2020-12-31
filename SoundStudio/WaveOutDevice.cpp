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
//  File:       WaveOutDevice.cpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "WaveOutDevice.hpp"

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
WaveOutDevice::WaveOutDevice()
: _hWaveOut(NULL)
, _lDeviceState(waveClosed)
, _pWaveNotify(NULL)
{
}

WaveOutDevice::~WaveOutDevice()
{
    Close();
}

bool WaveOutDevice::IsOpen() const
{
    return ( _hWaveOut != NULL );
}

///////////////////////////////////////////////////////////////////////////////
// GetId
DWORD_PTR WaveOutDevice::GetId() const
{
    DWORD_PTR uID = static_cast<DWORD_PTR>(-1L);
    if ( IsOpen() )
    {
        uID = reinterpret_cast<DWORD_PTR>(_hWaveOut);
    }
    return uID;
}

///////////////////////////////////////////////////////////////////////////////
// GetDeviceStatus
WaveStatus WaveOutDevice::GetDeviceStatus() const
{
    WaveStatus wStatus;
    wStatus = static_cast<WaveStatus>( 
        ::InterlockedCompareExchange(const_cast<LONG*>(&_lDeviceState), waveClosed, waveClosed)
        );
    return wStatus;
}

///////////////////////////////////////////////////////////////////////////////
// Open
HRESULT WaveOutDevice::Open(UINT uDeviceID,
                           const WaveFormat& wfmt)
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED);
    if ( !IsOpen() )
    {
        MMRESULT mmr = waveOutOpen(&_hWaveOut, uDeviceID, const_cast<WaveFormat&>(wfmt),
                                  reinterpret_cast<DWORD_PTR>(WaveOutDevice::waveOutProc),
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
HRESULT WaveOutDevice::Close()
{
    HRESULT hr = S_FALSE;
    if ( IsOpen() )
    {
        hr = Stop();
        MMRESULT mmr = waveOutClose(_hWaveOut);
        if ( mmr == MMSYSERR_NOERROR )
        {
            ::InterlockedExchange(&_lDeviceState, waveClosed);
            _hWaveOut = NULL;
        }
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Start
HRESULT WaveOutDevice::Start()
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutRestart(_hWaveOut);
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
HRESULT WaveOutDevice::Stop()
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutReset(_hWaveOut);
        if ( mmr == MMSYSERR_NOERROR )
        {
            ::InterlockedExchange(&_lDeviceState, waveStopped);
            mmr = waveOutPause(_hWaveOut);
        }
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Reset
HRESULT WaveOutDevice::Reset()
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutReset(_hWaveOut);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Pause
HRESULT WaveOutDevice::Pause()
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutPause(_hWaveOut);
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
HRESULT WaveOutDevice::GetPosition(WaveTime& wti) const
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutGetPosition(_hWaveOut, wti, wti.Size());
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// AddBuffer
HRESULT WaveOutDevice::AddBuffer( WaveBuffer& wbuf )
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutWrite(_hWaveOut, wbuf, wbuf.GetBufferLength());
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// PrepareBuffer
HRESULT WaveOutDevice::PrepareBuffer( WaveBuffer& wbuf )
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutPrepareHeader(_hWaveOut, wbuf, wbuf.Size());
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// UnprepareBuffer
HRESULT WaveOutDevice::UnprepareBuffer( WaveBuffer& wbuf )
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutUnprepareHeader(_hWaveOut, wbuf, wbuf.Size());
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// BreakLoop
HRESULT WaveOutDevice::BreakLoop()
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutBreakLoop(_hWaveOut);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// SetVolume
HRESULT WaveOutDevice::SetVolume(DWORD dwVolume)
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutSetVolume(_hWaveOut, dwVolume);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// SetPlaybackRate
HRESULT WaveOutDevice::SetPlaybackRate(DWORD dwRate)
{
    HRESULT hr = HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE);
    if ( IsOpen() )
    {
        MMRESULT mmr = waveOutSetPlaybackRate(_hWaveOut, dwRate);
        hr = HRESULT_FROM_WIN32(mmr);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// SetNotifyHandler
HRESULT WaveOutDevice::SetNotifyHandler(IWaveNotifyHandler* pNotify)
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
        hr = S_OK;
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ProcessEvent
void WaveOutDevice::ProcessEvent(UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR /*dwParam2*/)
{
    if ( _pWaveNotify != NULL )
    {
        _pWaveNotify->ProcessEvent(this, uMsg, reinterpret_cast<WaveBuffer*>(dwParam1));
    }
}

///////////////////////////////////////////////////////////////////////////////
// waveOutProc
void WaveOutDevice::waveOutProc(HWAVEOUT /*hwo*/,
                         UINT uMsg,
                         DWORD_PTR dwInstance,
                         DWORD dwParam1,
                         DWORD dwParam2)
{
    WaveOutDevice* _this = reinterpret_cast<WaveOutDevice*>( dwInstance );
    if ( _this )
        _this->ProcessEvent(uMsg, dwParam1, dwParam2);
}

///////////////////////////////////////////////////////////////////////////////
// GetDevicesCount
UINT WaveOutDevice::GetDevicesCount()
{
    return waveOutGetNumDevs();
}

///////////////////////////////////////////////////////////////////////////////
// GetDeviceCaps
HRESULT WaveOutDevice::GetDeviceCaps(UINT uDeviceID, WaveOutCaps& woc)
{
    HRESULT hr;
    MMRESULT mmr = waveOutGetDevCaps(uDeviceID, woc, woc.Size());
    hr = HRESULT_FROM_WIN32(mmr);
    return hr;
}
