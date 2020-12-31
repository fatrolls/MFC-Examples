///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2008 Ernest Laurentin (http://www.ernzo.com/)
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
//  File:       MultimediaStream.cpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <atlconv.h>
#include "MultimediaStream.hpp"


#pragma comment(lib, "Strmiids.lib")


///////////////////////////////////////////////////////////////////////////////
MMAudioStream::MMAudioStream()
{
    memset(&_wfmt, 0, sizeof(_wfmt));
}

MMAudioStream::~MMAudioStream()
{
    ReleaseMediaStream();
}

///////////////////////////////////////////////////////////////////////////////
// GetWaveFormat
const WAVEFORMATEX& MMAudioStream::GetWaveFormat() const
{
    return _wfmt;
}

///////////////////////////////////////////////////////////////////////////////
// SetMediaStream
HRESULT MMAudioStream::SetMediaStream(IMediaStream* pMediaStream)
{
    HRESULT hr = E_HANDLE;
    if ( pMediaStream )
    {
        hr = pMediaStream->QueryInterface(IID_IAudioMediaStream, (void **)&_pAudioStream);
        if ( SUCCEEDED(hr) )
        {
            hr = _pAudioData.CoCreateInstance(CLSID_AMAudioData, NULL, CLSCTX_INPROC_SERVER);
            if ( SUCCEEDED(hr) )
            {
                hr = _pAudioStream->GetFormat(&_wfmt);
                _pAudioData->SetFormat(&_wfmt);
            }
            else
            {
                _pAudioStream = NULL;
            }
        }
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// ReleaseMediaStream
HRESULT MMAudioStream::ReleaseMediaStream()
{
    HRESULT hr;
    hr = CompletionStatus(COMPSTAT_ABORT);
    if ( SUCCEEDED(hr) )
    {
        _pAudioSample = NULL;
        _pAudioData = NULL;
        _pAudioStream = NULL;
        memset(&_wfmt, 0, sizeof(_wfmt));
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetSampleData
HRESULT MMAudioStream::GetSampleData(LPBYTE pbData, DWORD& dwSize,
                                     DWORD dwFlags /*= COMPSTAT_WAIT*/,
                                     DWORD dwTimeout /*= INFINITE*/)
{
    HRESULT hr = E_INVALIDARG;
    if ( pbData != NULL && dwSize > 0 )
    {
        hr = E_HANDLE;
        if ( _pAudioStream != NULL && _pAudioData != NULL )
        {
            hr = S_OK;
            if ( _pAudioSample == NULL )
            {
                hr = _pAudioStream->CreateSample(_pAudioData, 0, &_pAudioSample);
            }
            if ( SUCCEEDED(hr) )
            {
                hr = _pAudioData->SetBuffer(dwSize, pbData, 0);
                hr = _pAudioSample->Update(SSUPDATE_ASYNC, 0, NULL, NULL);
                if ( hr == MS_S_PENDING ) {
                    hr = _pAudioSample->CompletionStatus(dwFlags, dwTimeout);
                }
                if ( hr == MS_S_ENDOFSTREAM )
                {
                    hr = S_FALSE;
                }
                if ( SUCCEEDED(hr) )
                {
                    _pAudioData->GetInfo(NULL, NULL, &dwSize);
                }
            }
        }
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetSampleTimes
HRESULT MMAudioStream::GetSampleTimes(STREAM_TIME *pStartTime,
                                      STREAM_TIME *pEndTime,
                                      STREAM_TIME *pCurrentTime)
{
    HRESULT hr = E_HANDLE;
    if ( _pAudioSample != NULL )
    {
        hr = _pAudioSample->GetSampleTimes(pStartTime, pEndTime, pCurrentTime);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// CompletionStatus
HRESULT MMAudioStream::CompletionStatus(DWORD dwFlags /*= COMPSTAT_WAIT*/,
                                        DWORD dwTimeout /*= INFINITE*/)
{
    HRESULT hr = E_HANDLE;
    if ( _pAudioSample != NULL )
    {
        hr = _pAudioSample->CompletionStatus(dwFlags, dwTimeout);
        if ( hr == MS_S_ENDOFSTREAM )
        {
            hr = S_FALSE;
        }
    }
    return hr;
}



///////////////////////////////////////////////////////////////////////////////
MultimediaStream::MultimediaStream()
{
}

MultimediaStream::~MultimediaStream()
{
    Terminate();
}

bool MultimediaStream::IsValid() const
{
    return ( _pAMMS.p != NULL );
}

///////////////////////////////////////////////////////////////////////////////
// Initialize
HRESULT MultimediaStream::Initialize(STREAM_TYPE streamType,
                                     DWORD dwFlags,
                                     IGraphBuilder* pFilterGraph)
{
    HRESULT hr = E_ACCESSDENIED;
    if ( !IsValid() )
    {
        hr = _pAMMS.CoCreateInstance(CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER);
        if ( SUCCEEDED(hr) )
        {
            hr = _pAMMS->Initialize(streamType, dwFlags, pFilterGraph);
            if ( SUCCEEDED(hr) )
            {
                hr = _pAMMS->GetFilterGraph(&_pGB);
            }
        }
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Terminate
HRESULT MultimediaStream::Terminate()
{
    HRESULT hr = S_FALSE;
    if ( IsValid() )
    {
        _pAMMS = NULL;
        _pGB = NULL;
        hr = S_OK;
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetFilterGraph
HRESULT MultimediaStream::GetFilterGraph(IGraphBuilder** ppFilterGraph)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        if ( _pGB && ppFilterGraph )
        {
            *ppFilterGraph = _pGB.p;
            (*ppFilterGraph)->AddRef();
            hr = S_OK;
        }
        else if ( _pGB.p != NULL )
        {
            hr = S_FALSE;
        }
        else
        {
            hr = E_POINTER;
        }
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetDuration
HRESULT MultimediaStream::GetDuration(STREAM_TIME* pDuration)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        CComQIPtr<IMultiMediaStream> pMS = _pAMMS;
        hr = pMS->GetDuration(pDuration);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetTime
HRESULT MultimediaStream::GetTime(STREAM_TIME* pCurrentTime)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        CComQIPtr<IMultiMediaStream> pMS = _pAMMS;
        hr = pMS->GetTime(pCurrentTime);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetState
HRESULT MultimediaStream::GetState(STREAM_STATE* pCurrentState)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        CComQIPtr<IMultiMediaStream> pMS = _pAMMS;
        hr = pMS->GetState(pCurrentState);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// SetState
HRESULT MultimediaStream::SetState(STREAM_STATE NewState)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        CComQIPtr<IMultiMediaStream> pMS = _pAMMS;
        hr = pMS->SetState(NewState);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Seek
HRESULT MultimediaStream::Seek(STREAM_TIME seekTime)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        CComQIPtr<IMultiMediaStream> pMS = _pAMMS;
        hr = pMS->Seek(seekTime);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// OpenFile
HRESULT MultimediaStream::OpenFile(LPCTSTR lpszFileName, DWORD dwFlags)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        USES_CONVERSION;
        hr = _pAMMS->OpenFile(T2CW(lpszFileName), dwFlags);
        if ( SUCCEEDED(hr) && _pGB == NULL )
        {
            // check if we can get graph now
            hr = _pAMMS->GetFilterGraph(&_pGB);
        }
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// AddMediaStream
HRESULT MultimediaStream::AddMediaStream(IUnknown* pStreamObject,
                                         const MSPID* pPurposeID,
                                         DWORD dwFlags,
                                         IMediaStream** ppNewStream)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        hr = _pAMMS->AddMediaStream(pStreamObject, pPurposeID, dwFlags, ppNewStream);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// GetMediaStream
HRESULT MultimediaStream::GetMediaStream(REFMSPID idPurpose, IMediaStream** ppMediaStream)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        CComQIPtr<IMultiMediaStream> pMS = _pAMMS;
        hr = pMS->GetMediaStream(idPurpose, ppMediaStream);
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// AddSourceFilter
HRESULT MultimediaStream::AddSourceFilter(LPCTSTR lpszFileName,
                                          LPCTSTR lpszFilterName,
                                          IBaseFilter** ppFilter)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        if ( _pGB != NULL )
        {
            USES_CONVERSION;
            hr = _pGB->AddSourceFilter(T2CW(lpszFileName), T2CW(lpszFilterName), ppFilter);
        }
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// AddFilter
HRESULT MultimediaStream::AddFilter(LPCTSTR lpszFilterName, IBaseFilter* pFilter)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        USES_CONVERSION;
        CComQIPtr<IFilterGraph> pFG = _pGB;
        hr = pFG->AddFilter( pFilter, T2CW(lpszFilterName) );
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// FindFilterByName
HRESULT MultimediaStream::FindFilterByName(LPCTSTR lpszFilterName, IBaseFilter** ppFilter)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        USES_CONVERSION;
        CComQIPtr<IFilterGraph> pFG = _pGB;
        hr = pFG->FindFilterByName( T2CW(lpszFilterName), ppFilter );
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Render
HRESULT MultimediaStream::Render(DWORD dwFlags)
{
    HRESULT hr = E_HANDLE;
    if ( IsValid() )
    {
        hr = _pAMMS->Render(dwFlags);
    }
    return hr;
}
