///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2006-2008 Ernest Laurentin (http://www.ernzo.com/)
//  File:       WaveOutBase.hpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef WAVEOUTDEVICE_HPP
#define WAVEOUTDEVICE_HPP
#include "WaveBase.hpp"


/// WaveOutCaps struct
struct WaveOutCaps : WAVEOUTCAPS
{
public:
    WaveOutCaps()
    {
        memset(this, 0, Size());
    }

    DWORD GetManufacturerId() const { return wMid; }
    DWORD GetProductId() const { return wPid; }
    MMVERSION GetVersion() const { return vDriverVersion; }
    DWORD GetFormats() const { return dwFormats; }
    WORD GetChannels() const { return wChannels; }
    LPCTSTR GetProductName() { return szPname; }
    UINT Size() const { return sizeof(WAVEOUTCAPS); }
    operator LPWAVEOUTCAPS() { return static_cast<WAVEOUTCAPS*>(this); }
};


/// WaveOutDevice - encapsulate Waveform Audio output API
class WaveOutDevice : public IWaveDevice
{
public:
    WaveOutDevice();
    virtual ~WaveOutDevice();

    virtual bool IsOpen() const;
    virtual DWORD_PTR GetId() const;
    virtual WaveStatus GetDeviceStatus() const;
    virtual HRESULT Open(UINT uDeviceID, const WaveFormat& wfmt);
    virtual HRESULT Close();
    virtual HRESULT Start();
    virtual HRESULT Stop();
    virtual HRESULT Reset();
    virtual HRESULT Pause();
    virtual HRESULT GetPosition(WaveTime& wti) const;
    virtual HRESULT AddBuffer( WaveBuffer& wbuf );
    virtual HRESULT PrepareBuffer( WaveBuffer& wbuf );
    virtual HRESULT UnprepareBuffer( WaveBuffer& wbuf );
    virtual HRESULT SetNotifyHandler(IWaveNotifyHandler* pNotify);

    HRESULT BreakLoop();
    HRESULT SetVolume(DWORD dwVolume);
    HRESULT SetPlaybackRate(DWORD dwRate);

    static  UINT GetDevicesCount();
    static  HRESULT GetDeviceCaps(UINT uDeviceID, WaveOutCaps& woc);
private:
    virtual void ProcessEvent(UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
    static void CALLBACK waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance,
                             DWORD dwParam1, DWORD dwParam2);
private:
    HWAVEOUT             _hWaveOut;     ///< Wave Audio output
    long                 _lDeviceState; ///< Wave state
    IWaveNotifyHandler*  _pWaveNotify;  ///< Audio Event handler
};

#endif //WAVEOUTDEVICE_HPP