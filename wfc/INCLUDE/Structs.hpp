#if ! defined( STRUCTS_CLASS_HEADER )

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
** $Workfile: structs.hpp $
** $Revision: 14 $
** $Modtime: 1/04/00 5:01a $
*/

#define STRUCTS_CLASS_HEADER

class CAccessAllowedEntry : public _ACCESS_ALLOWED_ACE
{
   public:

      CAccessAllowedEntry();
      CAccessAllowedEntry( const CAccessAllowedEntry& source );
      CAccessAllowedEntry( const ACCESS_ALLOWED_ACE * source );
      virtual ~CAccessAllowedEntry();
      virtual void Copy( const CAccessAllowedEntry& source );
      virtual void Copy( const ACCESS_ALLOWED_ACE * source );
      virtual void Empty( void );
      virtual CAccessAllowedEntry& operator=( const CAccessAllowedEntry& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CAccessControlEntryHeader : public _ACE_HEADER
{
   public:

      CAccessControlEntryHeader();
      CAccessControlEntryHeader( const CAccessControlEntryHeader& source );
      CAccessControlEntryHeader( const ACE_HEADER * source );
      virtual ~CAccessControlEntryHeader();
      virtual void Copy( const CAccessControlEntryHeader& source );
      virtual void Copy( const ACE_HEADER * source );
      virtual void Empty( void );
      virtual CAccessControlEntryHeader& operator=( const CAccessControlEntryHeader& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CAccessControlList : public _ACL
{
   public:

      CAccessControlList();
      CAccessControlList( const CAccessControlList& source );
      CAccessControlList( const ACL * source );
      virtual ~CAccessControlList();
      virtual void Copy( const CAccessControlList& source );
      virtual void Copy( const ACL * source );
      virtual void Empty( void );
      virtual CAccessControlList& operator=( const CAccessControlList& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CAccessDeniedEntry : public _ACCESS_DENIED_ACE
{
   public:

      CAccessDeniedEntry();
      CAccessDeniedEntry( const CAccessDeniedEntry& source );
      CAccessDeniedEntry( const ACCESS_DENIED_ACE * source );
      virtual ~CAccessDeniedEntry();
      virtual void Copy( const CAccessDeniedEntry& source );
      virtual void Copy( const ACCESS_DENIED_ACE * source );
      virtual void Empty( void );
      virtual CAccessDeniedEntry& operator=( const CAccessDeniedEntry& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CBitmapCoreHeader : public tagBITMAPCOREHEADER
{
   public:

      CBitmapCoreHeader();
      CBitmapCoreHeader( const CBitmapCoreHeader& source );
      CBitmapCoreHeader( const tagBITMAPCOREHEADER * source );
      virtual ~CBitmapCoreHeader();
      virtual void Copy( const CBitmapCoreHeader& source );
      virtual void Copy( const tagBITMAPCOREHEADER * source );
      virtual void Empty( void );
      virtual CBitmapCoreHeader& operator=( const CBitmapCoreHeader& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CBitmapFileHeader : public tagBITMAPFILEHEADER
{
   public:

      CBitmapFileHeader();
      CBitmapFileHeader( const CBitmapFileHeader& source );
      CBitmapFileHeader( const tagBITMAPFILEHEADER * source );
      virtual ~CBitmapFileHeader();
      virtual void Copy( const CBitmapFileHeader& source );
      virtual void Copy( const tagBITMAPFILEHEADER * source );
      virtual void Empty( void );
      virtual CBitmapFileHeader& operator=( const CBitmapFileHeader& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CBitmapInfoHeader : public tagBITMAPINFOHEADER
{
   public:

      CBitmapInfoHeader();
      CBitmapInfoHeader( const CBitmapInfoHeader& source );
      CBitmapInfoHeader( const tagBITMAPINFOHEADER * source );
      virtual ~CBitmapInfoHeader();
      virtual void Copy( const CBitmapInfoHeader& source );
      virtual void Copy( const tagBITMAPINFOHEADER * source );
      virtual void Empty( void );
      virtual CBitmapInfoHeader& operator=( const CBitmapInfoHeader& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CColorAdjustment : public tagCOLORADJUSTMENT
{
   public:

      CColorAdjustment();
      CColorAdjustment( const CColorAdjustment& source );
      CColorAdjustment( const tagCOLORADJUSTMENT * source );
      virtual ~CColorAdjustment();
      virtual void Copy( const CColorAdjustment& source );
      virtual void Copy( const tagCOLORADJUSTMENT * source );
      virtual void Empty( void );
      virtual CColorAdjustment& operator=( const CColorAdjustment& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CCommunicationsConfiguration : public _COMMCONFIG
{
   public:

      CCommunicationsConfiguration();
      CCommunicationsConfiguration( const CCommunicationsConfiguration& source );
      CCommunicationsConfiguration( const COMMCONFIG& source );
      virtual ~CCommunicationsConfiguration();

      virtual void Copy( const CCommunicationsConfiguration& source );
      virtual void Copy( const COMMCONFIG& source );
      virtual void Empty( void );

      virtual CCommunicationsConfiguration& operator=( const CCommunicationsConfiguration& source );
      virtual CCommunicationsConfiguration& operator=( const COMMCONFIG& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CCommunicationProperties : public _COMMPROP
{

   public:

      CCommunicationProperties();
      CCommunicationProperties( const CCommunicationProperties& source );
      CCommunicationProperties( const _COMMPROP& source );
      virtual ~CCommunicationProperties();
      virtual void ConvertBaudRateToString( const DWORD baud_rate, CString& human_readable_string ) const;
      virtual void ConvertBaudRateListToString( const DWORD baud_rate, CString& human_readable_string ) const;
      virtual void ConvertDataBitsToString( const DWORD data_bits, CString& human_readable_string ) const;
      virtual void ConvertProviderCapabilitiesToString( const DWORD capabilities, CString& human_readable_string ) const;
      virtual void ConvertProviderSubtypeToString( const DWORD baud_rate, CString& human_readable_string ) const;
      virtual void ConvertSettableParametersToString( const DWORD parameters, CString& human_readable_string ) const;
      virtual void ConvertStopParityToString( const DWORD stop_parity, CString& human_readable_string ) const;
      virtual void Copy( const CCommunicationProperties& source );
      virtual void Copy( const _COMMPROP& source );
      virtual void Empty( void );
      virtual CCommunicationProperties& operator=( const CCommunicationProperties& source );
      virtual CCommunicationProperties& operator=( const _COMMPROP& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class COutlineTextMetricA : public _OUTLINETEXTMETRICA
{
   public:

      COutlineTextMetricA();
      COutlineTextMetricA( const COutlineTextMetricA& source );
      COutlineTextMetricA( const _OUTLINETEXTMETRICA * source );
      virtual ~COutlineTextMetricA();
      virtual void Copy( const COutlineTextMetricA& source );
      virtual void Copy( const _OUTLINETEXTMETRICA * source );
      virtual void Empty( void );
      virtual COutlineTextMetricA& operator=( const COutlineTextMetricA& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class COutlineTextMetricW : public _OUTLINETEXTMETRICW
{
   public:

      COutlineTextMetricW();
      COutlineTextMetricW( const COutlineTextMetricW& source );
      COutlineTextMetricW( const _OUTLINETEXTMETRICW * source );
      virtual ~COutlineTextMetricW();
      virtual void Copy( const COutlineTextMetricW& source );
      virtual void Copy( const _OUTLINETEXTMETRICW * source );
      virtual void Empty( void );
      virtual COutlineTextMetricW& operator=( const COutlineTextMetricW& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

#if defined( UNICODE )
#define COutlineTextMetric COutlineTextMetricW
#else
#define COutlineTextMetric COutlineTextMetricA
#endif // UNICODE

class CPixelFormatDescriptor : public tagPIXELFORMATDESCRIPTOR
{
   public:

      CPixelFormatDescriptor();
      CPixelFormatDescriptor( const CPixelFormatDescriptor& source );
      CPixelFormatDescriptor( const tagPIXELFORMATDESCRIPTOR * source );
      virtual ~CPixelFormatDescriptor();
      virtual void Copy( const CPixelFormatDescriptor& source );
      virtual void Copy( const tagPIXELFORMATDESCRIPTOR * source );
      virtual void Empty( void );
      virtual CPixelFormatDescriptor& operator=( const CPixelFormatDescriptor& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CRasterizerStatus : public _RASTERIZER_STATUS
{
   public:

      CRasterizerStatus();
      virtual ~CRasterizerStatus();
      virtual void Empty( void );
};

class CTextMetricA : public tagTEXTMETRICA
{
   public:

      CTextMetricA();
      CTextMetricA( const CTextMetricA& source );
      CTextMetricA( const tagTEXTMETRICA * source );
      virtual ~CTextMetricA();
      virtual void Copy( const CTextMetricA& source );
      virtual void Copy( const tagTEXTMETRICA * source );
      virtual void Empty( void );
      virtual CTextMetricA& operator=( const CTextMetricA& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CTextMetricW : public tagTEXTMETRICW
{
   public:

      CTextMetricW();
      CTextMetricW( const CTextMetricW& source );
      CTextMetricW( const tagTEXTMETRICW * source );
      virtual ~CTextMetricW();
      virtual void Copy( const CTextMetricW& source );
      virtual void Copy( const tagTEXTMETRICW * source );
      virtual void Empty( void );
      virtual CTextMetricW& operator=( const CTextMetricW& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

#if defined( UNICODE )
#define CTextMetric CTextMetricW
#else
#define CTextMetric CTextMetricA
#endif // UNICODE

class COFStruct : public _OFSTRUCT
{
   public:

      COFStruct();
      COFStruct( const COFStruct& source );
      COFStruct( const _OFSTRUCT * source );
      virtual ~COFStruct();
      virtual void Copy( const COFStruct& source );
      virtual void Copy( const _OFSTRUCT * source );
      virtual void Empty( void );
      virtual COFStruct& operator=( const COFStruct& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CMemoryStatus : public _MEMORYSTATUS
{
   public:

      CMemoryStatus();
      CMemoryStatus( const CMemoryStatus& source );
      CMemoryStatus( const MEMORYSTATUS * source );
      virtual ~CMemoryStatus();
      virtual void Copy( const CMemoryStatus & source );
      virtual void Copy( const MEMORYSTATUS * source );
      virtual void Empty( void );
      virtual CMemoryStatus& operator=( const CMemoryStatus& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CSecurityQualityOfService : public _SECURITY_QUALITY_OF_SERVICE
{
   public:

      CSecurityQualityOfService();
      virtual ~CSecurityQualityOfService();
      virtual void Empty( void );
};

class CPerfCounterDefinition : public _PERF_COUNTER_DEFINITION
{
   public:

      CPerfCounterDefinition();
      virtual ~CPerfCounterDefinition();
      virtual void Empty( void );
};

class CPerfInstanceDefinition : public _PERF_INSTANCE_DEFINITION
{
   public:

      CPerfInstanceDefinition();
      virtual ~CPerfInstanceDefinition();
      virtual void Empty( void );
};

class CWindowPlacement : public tagWINDOWPLACEMENT
{
   public:

      CWindowPlacement();
      CWindowPlacement( const CWindowPlacement& source );
      CWindowPlacement( const tagWINDOWPLACEMENT * source );
      virtual ~CWindowPlacement();
      virtual void Copy( const CWindowPlacement& source );
      virtual void Copy( const tagWINDOWPLACEMENT * source );
      virtual void Empty( void );
      virtual CWindowPlacement& operator=( const CWindowPlacement& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CSecurityAttributes : public _SECURITY_ATTRIBUTES
{
   public:

      CSecurityAttributes();
      virtual ~CSecurityAttributes();
      virtual void Empty( void );
};

class CSystemAuditEntry : public _SYSTEM_AUDIT_ACE
{
   public:

      CSystemAuditEntry();
      CSystemAuditEntry( const CSystemAuditEntry& source );
      CSystemAuditEntry( const _SYSTEM_AUDIT_ACE * source );
      virtual ~CSystemAuditEntry();
      virtual void Copy( const CSystemAuditEntry& source );
      virtual void Copy( const _SYSTEM_AUDIT_ACE * source );
      virtual void Empty( void );
      virtual CSystemAuditEntry& operator=( const CSystemAuditEntry& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

#if defined( _WINUSER_ )

class CFilterKeys : public tagFILTERKEYS
{
   public:

      CFilterKeys()
      {
         ::ZeroMemory( (tagFILTERKEYS *) this, sizeof( tagFILTERKEYS ) );
         cbSize = sizeof( tagFILTERKEYS );
      }

     ~CFilterKeys()
      {
         ::ZeroMemory( (tagFILTERKEYS *) this, sizeof( tagFILTERKEYS ) );
      }
};

class CStickyKeys : public tagSTICKYKEYS
{
   public:

      CStickyKeys()
      {
         ::ZeroMemory( (tagSTICKYKEYS *) this, sizeof( tagSTICKYKEYS ) );
         cbSize = sizeof( tagSTICKYKEYS );
      }

     ~CStickyKeys()
      {
         ::ZeroMemory( (tagSTICKYKEYS *) this, sizeof( tagSTICKYKEYS ) );
      }
};

class CMouseKeys : public tagMOUSEKEYS
{
   public:

      CMouseKeys()
      {
         ::ZeroMemory( (tagMOUSEKEYS *) this, sizeof( tagMOUSEKEYS ) );
         cbSize = sizeof( tagMOUSEKEYS );
      }

     ~CMouseKeys()
      {
         ::ZeroMemory( (tagMOUSEKEYS *) this, sizeof( tagMOUSEKEYS ) );
      }
};

class CToggleKeys : public tagTOGGLEKEYS
{
   public:

      CToggleKeys()
      {
         ::ZeroMemory( (tagTOGGLEKEYS *) this, sizeof( tagTOGGLEKEYS ) );
         cbSize = sizeof( tagTOGGLEKEYS );
      }

     ~CToggleKeys()
      {
         ::ZeroMemory( (tagTOGGLEKEYS *) this, sizeof( tagTOGGLEKEYS ) );
      }
};

class CAccessTimeout : public tagACCESSTIMEOUT
{
   public:

      CAccessTimeout()
      {
         ::ZeroMemory( (tagACCESSTIMEOUT *) this, sizeof( tagACCESSTIMEOUT ) );
         cbSize = sizeof( tagACCESSTIMEOUT );
      }

     ~CAccessTimeout()
      {
         ::ZeroMemory( (tagACCESSTIMEOUT *) this, sizeof( tagACCESSTIMEOUT ) );
      }
};

class CSoundSentryA : public tagSOUNDSENTRYA
{
   public:

      CSoundSentryA()
      {
         ::ZeroMemory( (tagSOUNDSENTRYA *) this, sizeof( tagSOUNDSENTRYA ) );
         cbSize = sizeof( tagSOUNDSENTRYA );
      }

     ~CSoundSentryA()
      {
         ::ZeroMemory( (tagSOUNDSENTRYA *) this, sizeof( tagSOUNDSENTRYA ) );
      }
};

class CSoundSentryW : public tagSOUNDSENTRYW
{
   public:

      CSoundSentryW()
      {
         ::ZeroMemory( (tagSOUNDSENTRYW *) this, sizeof( tagSOUNDSENTRYW ) );
         cbSize = sizeof( tagSOUNDSENTRYW );
      }

     ~CSoundSentryW()
      {
         ::ZeroMemory( (tagSOUNDSENTRYW *) this, sizeof( tagSOUNDSENTRYW ) );
      }
};

#if defined( UNICODE )
#define CSoundSentry CSoundSentryW
#else
#define CSoundSentry CSoundSentryA
#endif // UNICODE

#endif // _WINUSER_

#if defined( _INC_VFW )

class CCompVars : public COMPVARS
{
   public:

      CCompVars()
      {
         ::ZeroMemory( (COMPVARS *) this, sizeof( COMPVARS ) );
         cbSize = sizeof( COMPVARS );
      }

     ~CCompVars()
      {
         ::ZeroMemory( (COMPVARS *) this, sizeof( COMPVARS ) );
      }
};

#endif // _INC_VFW

#if defined( _WINGDI_ )

class CDocInfoA : public _DOCINFOA
{
   public:

      CDocInfoA()
      {
         ::ZeroMemory( (LPDOCINFOA) this, sizeof( DOCINFOA ) );
         cbSize = sizeof( DOCINFOA );
      }

     ~CDocInfoA()
      {
         ::ZeroMemory( (LPDOCINFOA) this, sizeof( DOCINFOA ) );
      }
};

class CDocInfoW : public _DOCINFOW
{
   public:

      CDocInfoW()
      {
         ::ZeroMemory( (LPDOCINFOW) this, sizeof( DOCINFOW ) );
         cbSize = sizeof( DOCINFOW );
      }

     ~CDocInfoW()
      {
         ::ZeroMemory( (LPDOCINFOW) this, sizeof( DOCINFOW ) );
      }
};

#if defined( UNICODE )
#define CDocInfo CDocInfoW
#else
#define CDocInfo CDocInfoA
#endif // UNICODE

#endif // _WINGDI_

class COperatingSystemVersionInformationA : public _OSVERSIONINFOA
{
   public:

      COperatingSystemVersionInformationA()
      {
         ::ZeroMemory( (POSVERSIONINFOA) this, sizeof( OSVERSIONINFOA ) );
         dwOSVersionInfoSize = sizeof( OSVERSIONINFOA );
      }

     ~COperatingSystemVersionInformationA()
      {
         ::ZeroMemory( (POSVERSIONINFOA) this, sizeof( OSVERSIONINFOA ) );
      }

      operator POSVERSIONINFOA(){ return( (POSVERSIONINFOA) this ); };
};

class COperatingSystemVersionInformationW : public _OSVERSIONINFOW
{
   public:

      COperatingSystemVersionInformationW()
      {
         ::ZeroMemory( (POSVERSIONINFOW) this, sizeof( OSVERSIONINFOW ) );
         dwOSVersionInfoSize = sizeof( OSVERSIONINFOW );
      }

     ~COperatingSystemVersionInformationW()
      {
         ::ZeroMemory( (POSVERSIONINFOW) this, sizeof( OSVERSIONINFOW ) );
      }

      operator POSVERSIONINFOW(){ return( (POSVERSIONINFOW) this ); };
};

#if defined( UNICODE )
#define COperatingSystemVersionInformation COperatingSystemVersionInformationW
#else
#define COperatingSystemVersionInformation COperatingSystemVersionInformationA
#endif // UNICODE

#endif // STRUCTS_CLASS_HEADER
