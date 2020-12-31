///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2006-2008 Ernest Laurentin (http://www.ernzo.com/)
//  File:       MixerDevice.hpp
//  Version:    1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef MIXERDEVICE_HPP
#define MIXERDEVICE_HPP
#include <winbase.h>
#include <mmreg.h>
#pragma warning(push)
#pragma warning(disable:4201)
#include <Mmsystem.h>
#pragma warning(pop)


static const UINT INVALID_MIXER_ID = static_cast<UINT>(-1L);

/// MixerControlDetails struct
struct MixerControlDetails : MIXERCONTROLDETAILS
{
public:
    MixerControlDetails()
    {
        memset(this, 0, Size());
        cbStruct = Size();
    }
    UINT Size() const { return sizeof(MIXERCONTROLDETAILS); }
    operator LPMIXERCONTROLDETAILS() { return static_cast<MIXERCONTROLDETAILS *>(this); }
};

/// MixerControl struct
struct MixerControl : MIXERCONTROL
{
public:
    MixerControl()
    {
        memset(this, 0, Size());
        cbStruct = Size();
    }
    UINT Size() const { return sizeof(MIXERCONTROL); }
    operator LPMIXERCONTROL() { return static_cast<MIXERCONTROL *>(this); }
};

/// MixerLineControls struct
struct MixerLineControls : MIXERLINECONTROLS
{
public:
    MixerLineControls()
    {
        memset(this, 0, Size());
        cbStruct = Size();
    }
    UINT Size() const { return sizeof(MIXERLINECONTROLS); }
    operator LPMIXERLINECONTROLS() { return static_cast<MIXERLINECONTROLS *>(this); }
};

/// MixerLineInfo struct
struct MixerLineInfo : MIXERLINE
{
public:
    MixerLineInfo()
    {
        memset(this, 0, Size());
        cbStruct = Size();
    }
    UINT Size() const { return sizeof(MIXERLINE); }
    operator LPMIXERLINE() { return static_cast<MIXERLINE *>(this); }
};

/// MixerCaps struct
struct MixerCaps : MIXERCAPS
{
public:
    MixerCaps()
    {
        memset(this, 0, Size());
    }

	DWORD GetManufacturerId() const { return wMid; }
    DWORD GetProductId() const { return wPid; }
    MMVERSION GetVersion() const { return vDriverVersion; }
    DWORD GetSupportFlag() const { return fdwSupport; }
    DWORD GetDestinations() const { return cDestinations; }
    LPCTSTR GetProductName() { return szPname; }
    UINT Size() const { return sizeof(MIXERCAPS); }
    operator LPMIXERCAPS() { return static_cast<MIXERCAPS *>(this); }
};


/// MixerDevice - encapsulate Audio Mixer Device API
class MixerDevice
{
public:
    MixerDevice();
    ~MixerDevice();
    bool IsOpen() const;
    UINT GetId() const;
    HRESULT Open(UINT uMixerId, DWORD fdwOpen, HWND hWndCallback);
    HRESULT Close();
    HRESULT GetControlDetails(MixerControlDetails& mxcd, DWORD fdwDetails) const;
    HRESULT SetControlDetails(const MixerControlDetails& mxcd, DWORD fdwDetails);
    HRESULT GetLineControls(MixerLineControls& mxlcs, DWORD fdwControls) const;
    HRESULT GetLineInfo(MixerLineInfo& mxli, DWORD fdwInfo) const;
    HRESULT GetDeviceCaps(MixerCaps& mxcaps) const;
    HRESULT MixerMessage(UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

    static UINT GetNumDevices();
    static UINT GetMixerDeviceID(HMIXEROBJ hmxobj, DWORD flags);

private:
    HMIXER  _hMixer;    ///< Mixer handle
};

#endif //MIXERDEVICE_HPP