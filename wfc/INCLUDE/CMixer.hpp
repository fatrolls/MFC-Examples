#if ! defined( MIXER_API_CLASS_HEADER )

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: CMixer.hpp $
** $Revision: 12 $
** $Modtime: 1/04/00 4:51a $
*/

#define MIXER_API_CLASS_HEADER

class CMixerControlDetailsData
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CMixerControlDetailsData )
#endif // WFC_NO_SERIALIZATION

   public:

      // Construction

      CMixerControlDetailsData();
      CMixerControlDetailsData( const CMixerControlDetailsData&     source );
      CMixerControlDetailsData( const MIXERCONTROLDETAILS_LISTTEXT& source );
      CMixerControlDetailsData( const MIXERCONTROLDETAILS_BOOLEAN&  source );
      CMixerControlDetailsData( const MIXERCONTROLDETAILS_SIGNED&   source );
      CMixerControlDetailsData( const MIXERCONTROLDETAILS_UNSIGNED& source );
      virtual ~CMixerControlDetailsData();

      // Properties

      DWORD   Parameter1;
      DWORD   Parameter2;
      CString Name;

      // Methods

      virtual void Copy( const CMixerControlDetailsData&     source );
      virtual void Copy( const MIXERCONTROLDETAILS_LISTTEXT& source );
      virtual void Copy( const MIXERCONTROLDETAILS_BOOLEAN&  source );
      virtual void Copy( const MIXERCONTROLDETAILS_SIGNED&   source );
      virtual void Copy( const MIXERCONTROLDETAILS_UNSIGNED& source );
      virtual void Empty( void );
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      // Operators

      virtual CMixerControlDetailsData& operator = ( const CMixerControlDetailsData&     source );
      virtual CMixerControlDetailsData& operator = ( const MIXERCONTROLDETAILS_LISTTEXT& source );
      virtual CMixerControlDetailsData& operator = ( const MIXERCONTROLDETAILS_BOOLEAN&  source );
      virtual CMixerControlDetailsData& operator = ( const MIXERCONTROLDETAILS_SIGNED&   source );
      virtual CMixerControlDetailsData& operator = ( const MIXERCONTROLDETAILS_UNSIGNED& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CMixerControlDetails
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CMixerControlDetails )
#endif // WFC_NO_SERIALIZATION

   public:

      // Construction

      CMixerControlDetails();
      CMixerControlDetails( const CMixerControlDetails& source );
      CMixerControlDetails( const MIXERCONTROLDETAILS&  source );
      virtual ~CMixerControlDetails();

      // Properties

      DWORD ID;
      DWORD NumberOfChannels;
      HWND  WindowHandleOfOwner;
      DWORD NumberOfMultipleItemsPerChannel;

      // Methods

      virtual void Copy( const CMixerControlDetails& source );
      virtual void Copy( const MIXERCONTROLDETAILS&  source );
      virtual void Empty( void );

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      // Operators

      virtual CMixerControlDetails& operator = ( const CMixerControlDetails& source );
      virtual CMixerControlDetails& operator = ( const MIXERCONTROLDETAILS&  source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerControl
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CMixerControl )
#endif // WFC_NO_SERIALIZATION

   public:

      // Construction

      CMixerControl();
      CMixerControl( const CMixerControl& source );
      CMixerControl( const MIXERCONTROL&  source );
      virtual ~CMixerControl();

      // Properties

      enum _TypesOfThingys
      {
         typeCustom = MIXERCONTROL_CT_CLASS_CUSTOM,
         typeFader  = MIXERCONTROL_CT_CLASS_FADER,
         typeList   = MIXERCONTROL_CT_CLASS_LIST,
         typeMeter  = MIXERCONTROL_CT_CLASS_METER,
         typeNumber = MIXERCONTROL_CT_CLASS_NUMBER,
         typeSlider = MIXERCONTROL_CT_CLASS_SLIDER,
         typeSwitch = MIXERCONTROL_CT_CLASS_SWITCH,
         typeTime   = MIXERCONTROL_CT_CLASS_TIME
      };

      enum _Thingys
      {
         Custom         = MIXERCONTROL_CONTROLTYPE_CUSTOM,
         Bass           = MIXERCONTROL_CONTROLTYPE_BASS,
         Equalizer      = MIXERCONTROL_CONTROLTYPE_EQUALIZER,
         Fader          = MIXERCONTROL_CONTROLTYPE_FADER,
         Treble         = MIXERCONTROL_CONTROLTYPE_TREBLE,
         Volume         = MIXERCONTROL_CONTROLTYPE_VOLUME,
         Mixer          = MIXERCONTROL_CONTROLTYPE_MIXER,
         MultipleSelect = MIXERCONTROL_CONTROLTYPE_MULTIPLESELECT,
         Mux            = MIXERCONTROL_CONTROLTYPE_MUX,
         SingleSelect   = MIXERCONTROL_CONTROLTYPE_SINGLESELECT,
         BooleanMeter   = MIXERCONTROL_CONTROLTYPE_BOOLEANMETER,
         PeakMeter      = MIXERCONTROL_CONTROLTYPE_PEAKMETER,
         SignedMeter    = MIXERCONTROL_CONTROLTYPE_SIGNEDMETER,
         UnsignedMeter  = MIXERCONTROL_CONTROLTYPE_UNSIGNEDMETER,
         Decibels       = MIXERCONTROL_CONTROLTYPE_DECIBELS,
         Percent        = MIXERCONTROL_CONTROLTYPE_PERCENT,
         Signed         = MIXERCONTROL_CONTROLTYPE_SIGNED,
         Unsigned       = MIXERCONTROL_CONTROLTYPE_UNSIGNED,
         Pan            = MIXERCONTROL_CONTROLTYPE_PAN,
         QSoundPan      = MIXERCONTROL_CONTROLTYPE_QSOUNDPAN,
         Slider         = MIXERCONTROL_CONTROLTYPE_SLIDER,
         Boolean        = MIXERCONTROL_CONTROLTYPE_BOOLEAN,
         Button         = MIXERCONTROL_CONTROLTYPE_BUTTON,
         Loudness       = MIXERCONTROL_CONTROLTYPE_LOUDNESS,
         Mono           = MIXERCONTROL_CONTROLTYPE_MONO,
         Mute           = MIXERCONTROL_CONTROLTYPE_MUTE,
         OnOff          = MIXERCONTROL_CONTROLTYPE_ONOFF,
         StereoEnhance  = MIXERCONTROL_CONTROLTYPE_STEREOENH,
         MicroTime      = MIXERCONTROL_CONTROLTYPE_MICROTIME,
         MilliTime      = MIXERCONTROL_CONTROLTYPE_MILLITIME
      };

      enum _StatusFlags
      {
         statusDisabled = MIXERCONTROL_CONTROLF_DISABLED,
         statusMultiple = MIXERCONTROL_CONTROLF_MULTIPLE,
         statusUniform  = MIXERCONTROL_CONTROLF_UNIFORM
      };

      enum _Units
      {
         unitsCustom   = MIXERCONTROL_CT_UNITS_CUSTOM,
         unitsBoolean  = MIXERCONTROL_CT_UNITS_BOOLEAN,
         unitsSigned   = MIXERCONTROL_CT_UNITS_SIGNED,
         unitsUnsigned = MIXERCONTROL_CT_UNITS_UNSIGNED,
         unitsDecibels = MIXERCONTROL_CT_UNITS_DECIBELS,
         unitsPercent  = MIXERCONTROL_CT_UNITS_PERCENT
      };

      DWORD       ID;
      DWORD       Type;
      DWORD       StatusFlags;
      DWORD       NumberOfItemsPerChannel;
      CString     ShortName;
      CString     Name;
      DWORD       Minimum;
      DWORD       Maximum;
      DWORD       NumberOfSteps;
      DWORD       NumberOfCustomDataBytes;
      CDWordArray Data;

      // Methods

      virtual void  Copy( const CMixerControl& source );
      virtual void  Copy( const MIXERCONTROL& source  );
      virtual void  Empty( void );
      virtual DWORD GetType( void ) const;
      virtual void  GetTypeName( CString& name ) const;
      virtual DWORD GetUnits( void ) const;
      virtual BOOL  IsBooleanUnits(  void ) const;
      virtual BOOL  IsCustom(        void ) const;
      virtual BOOL  IsCustomUnits(   void ) const;
      virtual BOOL  IsDecibelsUnits( void ) const;
      virtual BOOL  IsDisabled(      void ) const;
      virtual BOOL  IsFader(         void ) const;
      virtual BOOL  IsList(          void ) const;
      virtual BOOL  IsMeter(         void ) const;
      virtual BOOL  IsMultiple(      void ) const;
      virtual BOOL  IsNumber(        void ) const;
      virtual BOOL  IsPercentUnits(  void ) const;
      virtual BOOL  IsSignedUnits(   void ) const;
      virtual BOOL  IsSlider(        void ) const;
      virtual BOOL  IsSwitch(        void ) const;
      virtual BOOL  IsTime(          void ) const;
      virtual BOOL  IsUniform(       void ) const;
      virtual BOOL  IsUnsignedUnits( void ) const;

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      // Operators

      virtual CMixerControl& operator = ( const CMixerControl& source );
      virtual CMixerControl& operator = ( const MIXERCONTROL&  source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerLine
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CMixerLine )
#endif // WFC_NO_SERIALIZATION

   public:

      // Construction

      CMixerLine();
      CMixerLine( const CMixerLine& source );
      CMixerLine( const MIXERLINE&  source );
      virtual ~CMixerLine();

      // Properties

      enum _Components
      {
         destinationUndefined  = MIXERLINE_COMPONENTTYPE_DST_UNDEFINED,
         destinationDigital    = MIXERLINE_COMPONENTTYPE_DST_DIGITAL,
         destinationLine       = MIXERLINE_COMPONENTTYPE_DST_LINE,
         destinationMonitor    = MIXERLINE_COMPONENTTYPE_DST_MONITOR,
         destinationSpeakers   = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS,
         destinationHeadphones = MIXERLINE_COMPONENTTYPE_DST_HEADPHONES,
         destinationTelephone  = MIXERLINE_COMPONENTTYPE_DST_TELEPHONE,
         destinationWaveIn     = MIXERLINE_COMPONENTTYPE_DST_WAVEIN,
         destinationVoiceIn    = MIXERLINE_COMPONENTTYPE_DST_VOICEIN,
         sourceUndefined       = MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED,
         sourceDigital         = MIXERLINE_COMPONENTTYPE_SRC_DIGITAL, 
         sourceLine            = MIXERLINE_COMPONENTTYPE_SRC_LINE,
         sourceMicrophone      = MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE,
         sourceSynthesizer     = MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER,
         sourceCompactDisc     = MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC,
         sourceTelephone       = MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE,
         sourcePCSpeaker       = MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER,
         sourceWaveOut         = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT,
         sourceAuxillary       = MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY,
         sourceAnalog          = MIXERLINE_COMPONENTTYPE_SRC_ANALOG
      };

      enum _TargetTypes
      {
         targetUndefined = MIXERLINE_TARGETTYPE_UNDEFINED,
         targetWaveOut   = MIXERLINE_TARGETTYPE_WAVEOUT,
         targetWaveIn    = MIXERLINE_TARGETTYPE_WAVEIN,
         targetMidiOut   = MIXERLINE_TARGETTYPE_MIDIOUT,
         targetMidiIn    = MIXERLINE_TARGETTYPE_MIDIIN,
         targetAuxillary = MIXERLINE_TARGETTYPE_AUX
      };

      enum _Statusses_or_is_it_Stati
      {
         statusActive       = MIXERLINE_LINEF_ACTIVE,
         statusDisconnected = MIXERLINE_LINEF_DISCONNECTED,
         statusSource       = MIXERLINE_LINEF_SOURCE
      };

      DWORD   DestinationNumber;
      DWORD   Source;
      DWORD   ID;
      DWORD   Status;
      DWORD   Reserved;
      DWORD   Component;
      DWORD   NumberOfChannels;
      DWORD   NumberOfConnections;
      DWORD   NumberOfControls;
      CString ShortName;
      CString Name;
      DWORD   Target;
      DWORD   TargetDeviceID;
      DWORD   TargetManufacturer;
      DWORD   TargetProduct;
      DWORD   TargetDriverVersion;
      CString TargetName;

      // Methods

      virtual void Copy( const CMixerLine& source );
      virtual void Copy( const MIXERLINE&  source );
      virtual void Empty( void );
      virtual void GetComponent( CString& component_string ) const;
      virtual void GetStatus( CString& status_string ) const;
      virtual void GetTarget( CString& target_string ) const;
#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION
      virtual BOOL IsActive( void ) const;
      virtual BOOL IsDisconnected( void ) const;
      virtual BOOL IsSource( void ) const;

      // Operators

      virtual CMixerLine& operator = ( const CMixerLine& source );
      virtual CMixerLine& operator = ( const MIXERLINE&  source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerCapabilities
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CMixerCapabilities )
#endif // WFC_NO_SERIALIZATION

   public:

      // Construction

      CMixerCapabilities();
      CMixerCapabilities( const CMixerCapabilities& source );
      CMixerCapabilities( const MIXERCAPS&  source );
      virtual ~CMixerCapabilities();

      // Properties

      DWORD   Manufacturer;
      DWORD   Product;
      DWORD   Version;
      CString ProductName;
      DWORD   Support;
      DWORD   NumberOfDestinations;

      // Methods

      virtual void Copy( const CMixerCapabilities& source );
      virtual void Copy( const MIXERCAPS& source );
      virtual void Empty( void );
      virtual BOOL Get( const UINT device_number );

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      // Operators

      virtual CMixerCapabilities& operator = ( const CMixerCapabilities& source );
      virtual CMixerCapabilities& operator = ( const MIXERCAPS&  source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CMixer
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CMixer( const CMixer& ) {};
      CMixer& operator=( const CMixer& ) { return( *this ); };

   protected:

      DWORD m_ErrorCode;

      HMIXER m_Handle;

      UINT m_DeviceID;

   public:

      // Construction

      CMixer();
      virtual ~CMixer();

      // Properties

      enum _Callbacks
      {
         callbackEvent    = CALLBACK_EVENT,
         callbackFunction = CALLBACK_FUNCTION,
         callbackNone     = CALLBACK_NULL,
         callbackTask     = CALLBACK_TASK,
         callbackThread   = CALLBACK_THREAD,
         callbackWindow   = CALLBACK_WINDOW,
      };

      enum _Notifiers
      {
         notifyWindowHandle           = CALLBACK_WINDOW,
         notifyAuxillaryDeviceNumber  = MIXER_OBJECTF_AUX,
         notifyMIDIInputDeviceHandle  = MIXER_OBJECTF_HMIDIIN,
         notifyMIDIOutputDeviceHandle = MIXER_OBJECTF_HMIDIOUT,
         notifyMixerDeviceHandle      = MIXER_OBJECTF_HMIXER,
         notifyWaveInDeviceHandle     = MIXER_OBJECTF_HWAVEIN,
         notifyWaveOutDeviceHandle    = MIXER_OBJECTF_HWAVEOUT,
         notifyMIDIInputNumber        = MIXER_OBJECTF_MIDIIN,
         notifyMIDIOutputNumber       = MIXER_OBJECTF_MIDIOUT,
         notifyMixerNumber            = MIXER_OBJECTF_MIXER,
         notifyWaveInDeviceNumber     = MIXER_OBJECTF_WAVEIN,
         notifyWaveOutDeviceNumber    = MIXER_OBJECTF_WAVEOUT,
      };

      // Methods

      virtual void  Close( void );
      virtual BOOL  Get( CMixerCapabilities& capabilities );
      virtual BOOL  GetAllControls( const CMixerLine& line, CPtrArray& array_of_CMixerControl_pointers );
      virtual BOOL  GetByComponent( const DWORD component, CMixerLine& line );
      virtual BOOL  GetByConnection( const DWORD destination_number, const DWORD source, CMixerLine& line );
      virtual BOOL  GetByDestination( const DWORD destination_number, CMixerLine& line );
      virtual BOOL  GetByID( const DWORD id, CMixerLine& line );
      virtual BOOL  GetControlDetails(  const CMixerLine& line, const CMixerControl& control, CPtrArray& array_of_CMixerControlDetailsDatas_pointers );
      virtual BOOL  GetControlListText( const CMixerLine& line, const CMixerControl& control, CPtrArray& array_of_CMixerControlDetailsDatas_pointers );
      virtual UINT  GetDeviceID( void ) const;
      virtual DWORD GetErrorCode( void ) const;
      virtual void  GetErrorString( CString& error_string ) const;
      virtual HMIXEROBJ GetHandle( void ) const;
      virtual UINT  GetNumberOfDevices( void ) const;
      virtual BOOL  Open( UINT device_id = 0, DWORD what_to_notify = 0, DWORD who_to_notify = 0, DWORD notify_data = 0 );

#if ! defined(  WFC_NO_SERIALIZATION )
      virtual void  Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      virtual BOOL  SetControlDetails( const CMixerLine& line, const CMixerControl& control, const CPtrArray& array_of_pointers );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

// Thus endeth the Mixer API encapsulation objects, now let's put these together to make
// something coherent and easier to use

// Thanks go to Sean Dynan (sdynan@cccgroup.co.uk) for finding a flaw
// in the design of the following class' Open() methods. They weren't
// the same as CMixer's.

class CMixerControlInstance
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
   protected:

      // Properties

      DWORD m_WhatToNotify;
      DWORD m_WhoToNotify;
      DWORD m_NotifyData;

      CMixer        m_Mixer;
      CMixerLine    m_MixerLine;
      CMixerControl m_MixerControl;

   public:

      // Construction

      CMixerControlInstance();
      CMixerControlInstance( const CMixerControlInstance& source );
      virtual ~CMixerControlInstance();

      // Methods

      virtual void  Close( void );
      virtual void  Copy( const CMixerControlInstance& source );
      virtual BOOL  Open( UINT device_id = 0, DWORD what_to_notify = 0, DWORD who_to_notify = 0, DWORD notify_data = 0 );
      virtual void  SetLine( const CMixerLine& line );
      virtual void  SetControl( const CMixerControl& control );

      // Operators

      virtual CMixerControlInstance& operator = ( const CMixerControlInstance& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerSourceSelector : public CMixerControlInstance
{
   protected:

      // Properties

      CPtrArray m_Settings;

      virtual BOOL m_GetSettings( void );
      virtual BOOL m_SetSettings( void );

   public:

      // Construction

      CMixerSourceSelector( const CMixerSourceSelector& source );
      CMixerSourceSelector( const CMixerLine& destination, const CMixerControl& mixer_control );
      virtual ~CMixerSourceSelector();

      // Methods

      virtual void  Copy( const CMixerSourceSelector& source );
      virtual DWORD GetSource( void ) const;
      virtual BOOL  IsSelected( const DWORD source );
      virtual BOOL  Open( UINT device_id = 0, DWORD what_to_notify = 0, DWORD who_to_notify = 0, DWORD notify_data = 0 );
      virtual BOOL  Select( const DWORD source, BOOL selected = TRUE );
      virtual BOOL  Unselect( const DWORD source );

      // Operators

      virtual CMixerSourceSelector& operator = ( const CMixerSourceSelector& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerVolumeControl : public CMixerControlInstance
{
   protected:

      // Properties

      CMixerControlDetailsData m_LeftChannel;
      CMixerControlDetailsData m_RightChannel;
      CMixerControlDetailsData m_BothChannels;

      CPtrArray m_Channels;

      virtual BOOL m_GetAll( void );

   public:

      // Construction

      CMixerVolumeControl();
      CMixerVolumeControl( const CMixerVolumeControl& source );
      virtual ~CMixerVolumeControl();

      // Methods

      virtual void  Copy( const CMixerVolumeControl& source );
      virtual DWORD GetLeftChannelVolume( void );
      virtual DWORD GetMinimum( void ) const;
      virtual DWORD GetMaximum( void ) const;
      virtual DWORD GetRightChannelVolume( void );
      virtual DWORD GetVolume( void );
      virtual BOOL  SetLeftChannelVolume( const DWORD new_volume );
      virtual BOOL  SetRightChannelVolume( const DWORD new_volume );
      virtual BOOL  SetVolume( const DWORD new_volume );

      // Operators

      virtual CMixerVolumeControl& operator = ( const CMixerVolumeControl& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerSwitchControl : public CMixerControlInstance
{
   protected:

      // Properties

      CMixerControlDetailsData m_Switch;

      CPtrArray m_Array;

      virtual BOOL m_GetAll( void );

   public:

      // Construction

      CMixerSwitchControl();
      CMixerSwitchControl( const CMixerSwitchControl& source );
      virtual ~CMixerSwitchControl();

      // Methods

      virtual void Copy( const CMixerSwitchControl& source );
      virtual BOOL GetState( void );
      virtual BOOL SetState( const BOOL turn_it_on = TRUE );
      virtual BOOL TurnOff( void );
      virtual BOOL TurnOn( void );

      // Operators

      virtual CMixerSwitchControl& operator = ( const CMixerSwitchControl& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerSource : public CMixerControlInstance
{
   public:

      // Construction

      CMixerSource();
      CMixerSource( const CMixerSource& source );
      virtual ~CMixerSource();

      // Methods

      virtual void Copy( const CMixerSource& source );
      virtual BOOL GetControl( CMixerVolumeControl& control );
      virtual BOOL Open( UINT device_id = 0, DWORD what_to_notify = 0, DWORD who_to_notify = 0, DWORD notify_data = 0 );

      // Operators

      virtual CMixerSource& operator = ( const CMixerSource& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerDestination : public CMixerControlInstance
{
   protected:

      // Properties

      CMixerSourceSelector * m_SourceSelector_p;

   public:

      // Construction

      CMixerDestination();
      CMixerDestination( const CMixerDestination& source );
      virtual ~CMixerDestination();

      // Methods

      virtual void Copy( const CMixerDestination& source );
      virtual BOOL GetSource( const DWORD CMixerLineSource, CMixerSource& source );
      virtual BOOL IsSourceSelected( const DWORD CMixerLineSource );
      virtual BOOL Open( UINT device_id = 0, DWORD what_to_notify = 0, DWORD who_to_notify = 0, DWORD notify_data = 0 );
      virtual BOOL SelectSource( const DWORD CMixerLineSource, BOOL new_selection = TRUE );
      virtual BOOL UnselectSource( const DWORD CMixerLineSource );

      // Operators

      virtual CMixerDestination& operator = ( const CMixerDestination& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerWaveIn : public CMixerDestination
{
   protected:

      // Properties

      CMixerVolumeControl m_RecordingGain;

   public:

      // Construction

      CMixerWaveIn();
      CMixerWaveIn( const CMixerWaveIn& source );
      virtual ~CMixerWaveIn();

      // Methods

      virtual void  Copy( const CMixerWaveIn& source );
      virtual DWORD GetLeftChannelRecordingGain( void );
      virtual DWORD GetMaximumGain( void ) const;
      virtual DWORD GetMinimumGain( void ) const;
      virtual DWORD GetRecordingGain( void );
      virtual DWORD GetRightChannelRecordingGain( void );
      virtual BOOL  Open( UINT device_id = 0, DWORD what_to_notify = 0, DWORD who_to_notify = 0, DWORD notify_data = 0 );
      virtual BOOL  SetLeftChannelRecordingGain( const DWORD new_level );
      virtual BOOL  SetRecordingGain( const DWORD new_level );
      virtual BOOL  SetRightChannelRecordingGain( const DWORD new_level );

      // Operators

      virtual CMixerWaveIn& operator = ( const CMixerWaveIn& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CMixerSpeakers : public CMixerDestination
{
   protected:

      // Properties

      CMixerVolumeControl m_Volume;
      CMixerSwitchControl m_Mute;

   public:

      // Construction

      CMixerSpeakers();
      CMixerSpeakers( const CMixerSpeakers& source );
      virtual ~CMixerSpeakers();

      // Methods

      virtual void  Copy( const CMixerSpeakers& source );
      virtual DWORD GetLeftChannelVolume( void );
      virtual DWORD GetMaximumVolume( void );
      virtual DWORD GetMinimumVolume( void );
      virtual DWORD GetRightChannelVolume( void );
      virtual DWORD GetVolume( void );
      virtual BOOL  IsMuted( void );
      virtual BOOL  Mute( const BOOL muting = TRUE );
      virtual BOOL  Open( UINT device_id = 0, DWORD what_to_notify = 0, DWORD who_to_notify = 0, DWORD notify_data = 0 );
      virtual BOOL  SetLeftChannelVolume( const DWORD new_level );
      virtual BOOL  SetRightChannelVolume( const DWORD new_level );
      virtual BOOL  SetVolume( const DWORD new_level );
      virtual BOOL  UnMute( void );

      // Operators

      virtual CMixerSpeakers& operator = ( const CMixerSpeakers& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // MIXER_API_CLASS_HEADER
