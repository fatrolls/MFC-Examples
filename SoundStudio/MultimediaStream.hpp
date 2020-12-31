///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2008 Ernest Laurentin (http://www.ernzo.com/)
//  File:       MultimediaStream.hpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef MULTIMEDIASTREAM_HPP
#define MULTIMEDIASTREAM_HPP
#pragma warning(push)
#pragma warning(disable:4995)
#include <atlbase.h>
#include <Strmif.h>
#include <amstream.h>
#include <mmreg.h>
#pragma warning(pop)

/// MMAudioStream
class MMAudioStream
{
public:
    MMAudioStream();
    ~MMAudioStream();

    const WAVEFORMATEX& GetWaveFormat() const;
    HRESULT SetMediaStream(IMediaStream* pMediaStream);
    HRESULT ReleaseMediaStream();
    HRESULT GetSampleData(LPBYTE pbData, DWORD& dwSize, DWORD dwFlags = COMPSTAT_WAIT, DWORD dwTimeout = INFINITE);
    HRESULT GetSampleTimes(STREAM_TIME *pStartTime, STREAM_TIME *pEndTime, STREAM_TIME *pCurrentTime);
    HRESULT CompletionStatus(DWORD dwFlags = COMPSTAT_WAIT, DWORD dwTimeout = INFINITE);

private:
    WAVEFORMATEX        _wfmt;                  ///< Audio format
    CComPtr<IAudioMediaStream> _pAudioStream;   ///< Audio Stream
    CComPtr<IAudioData>        _pAudioData;     ///< Audio Stream data
    CComPtr<IAudioStreamSample> _pAudioSample;  ///< Audio Stream sample
};


/// Multimediastream class
class MultimediaStream
{
public:
    MultimediaStream();
    ~MultimediaStream();
    bool IsValid() const;
    HRESULT Initialize(STREAM_TYPE streamType, DWORD dwFlags, IGraphBuilder* pFilterGraph);
    HRESULT Terminate();
    HRESULT GetFilterGraph(IGraphBuilder** ppFilterGraph);
    HRESULT GetMediaStream(REFMSPID idPurpose, IMediaStream** ppMediaStream);
    HRESULT GetDuration(STREAM_TIME* pDuration);
    HRESULT GetTime(STREAM_TIME* pCurrentTime);
    HRESULT GetState(STREAM_STATE* pCurrentState);
    HRESULT SetState(STREAM_STATE NewState);
    HRESULT Seek(STREAM_TIME seekTime);
    HRESULT OpenFile(LPCTSTR lpszFileName, DWORD dwFlags);
    HRESULT AddMediaStream(IUnknown* pStreamObject, const MSPID* pPurposeID, DWORD dwFlags, IMediaStream** ppNewStream);
    HRESULT AddSourceFilter(LPCTSTR lpszFileName, LPCTSTR lpszName, IBaseFilter** ppFilter);
    HRESULT AddFilter(LPCTSTR lpszFilterName, IBaseFilter* pFilter);
    HRESULT FindFilterByName(LPCTSTR lpszFilterName, IBaseFilter** ppFilter);
    HRESULT Render(DWORD dwFlags);

private:
    CComPtr<IGraphBuilder> _pGB;            ///< Filter graph
    CComPtr<IAMMultiMediaStream> _pAMMS;    ///< Multimedia stream
};

#endif //MULTIMEDIASTREAM_HPP