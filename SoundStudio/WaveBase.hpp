///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2006-2008 Ernest Laurentin (http://www.ernzo.com/)
//  File:       WaveBase.hpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef WAVEDEVICE_HPP
#define WAVEDEVICE_HPP
#include <winbase.h>
#include <mmreg.h>
#pragma warning(push)
#pragma warning(disable:4201)
#pragma warning(disable:4995)
#include <Mmsystem.h>
#pragma warning(pop)

#pragma comment(lib, "Winmm.lib")


// Default flag, to change this behavior define WAVE_HEAP_FLAGS in stdafx.h
#ifndef WAVE_HEAP_FLAGS
#define WAVE_HEAP_FLAGS (HEAP_ZERO_MEMORY|HEAP_GENERATE_EXCEPTIONS)
#endif

/// WaveBuffer class
struct WaveBuffer : WAVEHDR
{
public:
    WaveBuffer()
    {
        memset(this, 0, Size());
    }
    ~WaveBuffer()
    {
        FreeMemory();
    }
    LPSTR GetBuffer() const { return lpData; }
    DWORD GetBufferLength() const { return dwBufferLength; }
    void SetBufferLength(DWORD bufferLength) { dwBufferLength = bufferLength; }
    DWORD GetBytesRecorded() const { return dwBytesRecorded; }
    void SetBytesRecorded(DWORD bytesRecorded) { dwBytesRecorded = bytesRecorded; }
    DWORD GetFlags() const { return dwFlags; }
    void SetFlags(DWORD flags) { dwFlags = flags; }
    DWORD GetLoops() const { return dwLoops; }
    void SetLoops(DWORD loops) { dwLoops = loops; }
	bool IsDone() const { return (dwFlags&WHDR_DONE)!=0; }
	bool IsPrepared() const { return (dwFlags&WHDR_PREPARED) != 0; }
    WaveBuffer* GetNext() { reinterpret_cast<WaveBuffer*>( lpNext ); }

    bool Allocate(DWORD size);
    void FreeMemory();

    UINT Size() const { return sizeof(WAVEHDR); }
    operator LPWAVEHDR() { return static_cast<WAVEHDR*>(this); }

private:
    WaveBuffer(const WAVEHDR& whdr);    // not allowed
    WaveBuffer(const WaveBuffer& wbuf); // not allowed
};

inline bool WaveBuffer::Allocate(DWORD size)
{
    if ( lpData != 0 )
    {
        lpData = static_cast<LPSTR>( HeapReAlloc(GetProcessHeap(), WAVE_HEAP_FLAGS, lpData, size) );
    }
    else
    {
        lpData = static_cast<LPSTR>( HeapAlloc(GetProcessHeap(), WAVE_HEAP_FLAGS, size) );
    }
    if ( lpData != NULL ) dwBufferLength = size;
    return ( lpData != NULL );
}

inline void WaveBuffer::FreeMemory()
{
    if ( lpData != NULL ) {
        HeapFree(GetProcessHeap(), 0, lpData);
        lpData = NULL; 
    }
}


/// WaveFormat class
struct WaveFormat : WAVEFORMATEX
{
public:
    WaveFormat()
    {
        memset(this, 0, Size());
    }
    WaveFormat(const WAVEFORMATEX& wfmt)
    {
        memcpy(this, &wfmt, Size());
    }
    UINT Size() const { return sizeof(WAVEFORMATEX); }
    operator LPWAVEFORMATEX() { return static_cast<WAVEFORMATEX*>(this); }
};


struct WaveFormatExtensible : WAVEFORMATEXTENSIBLE
{
public:
    WaveFormatExtensible()
    {
        memset(this, 0, Size());
    }
    WaveFormatExtensible(const WAVEFORMATEXTENSIBLE& wfmt)
    {
        memcpy(this, &wfmt, Size());
    }
    UINT Size() const { return sizeof(WAVEFORMATEXTENSIBLE); }
    operator LPWAVEFORMATEX() { return static_cast<WAVEFORMATEX*>(&Format); }
    operator PWAVEFORMATEXTENSIBLE() { return static_cast<WAVEFORMATEXTENSIBLE*>(this); }
};


/// Wave timing information
struct WaveTime : MMTIME
{
public:
    WaveTime()
    {
        memset(this, 0, Size());
    }
    WaveTime(const MMTIME& mmt)
    {
        memcpy(this, &mmt, Size());
    }
    DWORD GetType() const { return wType; }
    void SetType(DWORD type) { wType = type; }
    DWORD GetTimeInfo() const { return u.ms; }
    // time info can be an smpte struct, just cast it to DWORD
    void SetTimeInfo(DWORD info) { u.ms = info; }
    UINT Size() const { return sizeof(MMTIME); }
    operator LPMMTIME() { return static_cast<MMTIME*>(this); }
};


// forward reference
class IWaveNotifyHandler;

enum WaveStatus
{
    waveClosed = 0,  ///< Closed
    waveStopped,     ///< Stopped
    waveStarted,     ///< Started
    wavePaused       ///< Paused
};

/// Wave Device interface
class IWaveDevice
{
public:
    virtual bool IsOpen() const = 0;
    virtual DWORD_PTR GetId() const = 0;
    virtual WaveStatus GetDeviceStatus() const = 0;
    virtual HRESULT Open(UINT uDeviceID, const WaveFormat& wfmt) = 0;
    virtual HRESULT Close() = 0;
    virtual HRESULT Start() = 0;
    virtual HRESULT Stop() = 0;
    virtual HRESULT Reset() = 0;
    virtual HRESULT Pause() = 0;
    virtual HRESULT GetPosition( WaveTime& wti ) const = 0;
    virtual HRESULT AddBuffer( WaveBuffer& wbuf ) = 0;
    virtual HRESULT PrepareBuffer( WaveBuffer& wbuf ) = 0;
    virtual HRESULT UnprepareBuffer( WaveBuffer& wbuf ) = 0;
    virtual HRESULT SetNotifyHandler(IWaveNotifyHandler* pNotify) = 0;
};

/// Wave Device event handler
class IWaveNotifyHandler
{
public:
    virtual void ProcessEvent(IWaveDevice* pDevice, UINT uMsg, WaveBuffer* pwbuf) = 0;
};

#endif //WAVEDEVICE_HPP