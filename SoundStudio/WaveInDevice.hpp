///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2006-2008 Ernest Laurentin (http://www.ernzo.com/)
//  File:       WaveInDevice.hpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef WAVEINDEVICE_HPP
#define WAVEINDEVICE_HPP
#include "WaveBase.hpp"


/// WaveInCaps struct
struct WaveInCaps : WAVEINCAPS
{
public:
    WaveInCaps()
    {
        memset(this, 0, Size());
    }

    DWORD GetManufacturerId() const { return wMid; }
    DWORD GetProductId() const { return wPid; }
    MMVERSION GetVersion() const { return vDriverVersion; }
    DWORD GetFormats() const { return dwFormats; }
    WORD GetChannels() const { return wChannels; }
    LPCTSTR GetProductName() const { return szPname; }
    UINT Size() const { return sizeof(WAVEINCAPS); }
    operator LPWAVEINCAPS() { return static_cast<WAVEINCAPS*>(this); }
};

/// WaveInDevice - encapsulate Waveform Audio input API
class WaveInDevice : public IWaveDevice
{
public:
    WaveInDevice();
    virtual ~WaveInDevice();

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

    static  UINT GetDevicesCount();
    static  HRESULT GetDeviceCaps(UINT uDeviceID, WaveInCaps& wic);
private:
    virtual void ProcessEvent(UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2);
    static void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance,
                             DWORD dwParam1, DWORD dwParam2);
private:
    HWAVEIN             _hWaveIn;      ///< Wave Audio Input
    long                _lDeviceState; ///< Wave state
    IWaveNotifyHandler* _pWaveNotify;  ///< Audio Event handler
};

#endif //WAVEINDEVICE_HPP