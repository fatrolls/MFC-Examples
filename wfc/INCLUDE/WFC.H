#if ! defined( WIN32_FOUNDATION_CLASSES )

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
** $Workfile: wfc.h $
** $Revision: 65 $
** $Modtime: 5/12/00 3:23p $
*/

#define WIN32_FOUNDATION_CLASSES

#define WFC_RELEASE_NUMBER (45)

#if ( _MSC_VER > 1000 )
#pragma once
#endif // _MSV_VER

#if defined( UNICODE )
#if ! defined( _UNICODE )
#define _UNICODE
#endif // _UNICODE
#endif // UNICODE

#if defined( _UNICODE )
#if ! defined( UNICODE )
#define UNICODE
#endif // UNICODE
#endif // _UNICODE

#if ( WINVER < 0x401 )
#pragma message( "WARNING! You are compiling for a version of NT before 4.0, you may have problems in the RAS stuff." )
#pragma message( "You will probably have problems in the RAS stuff." )
#pragma message( "Don't be suprised is TryEnterCriticalSection fails too." )
#pragma message( "To get rid of this warning, add WINVER=0x401 to the Preprocessor definitions in the project settings." )
#else
#if ! defined( _WIN32_WINNT )
#define _WIN32_WINNT WINVER
#endif // _WIN32_WINNT
#endif // WINVER
/*
** Need to define NO_ANSI_ONLY (an undocumented "feature", someone let the
** children play in the header files again...)
*/

#define NO_ANSIUNI_ONLY

/*
** Yet another undocumented feature we gotta worry about
*/

#if defined( WIN32_LEAN_AND_MEAN )
#undef WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

/*
** Need to un-define VC_EXTRALEAN, another undocumented feature...
*/

#if defined( VC_EXTRALEAN )
#undef VC_EXTRALEAN
#endif // _VC_EXTRALEAN

#if defined( _DEBUG )
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG

#if defined( WFC_STL )
// We are building an MFC-free version of the library

// The STL classes generate a horrendous number of warnings
#pragma warning( push, 3 )

#define WFC_NO_DUMPING
#define WFC_NO_SERIALIZATION

#include <Mfc2Stl.h>

#endif // WFC_STL

/*
** Now setup the linker, we must include our .lib before the
** Microsoft libraries in order to avoid LNK2005 errors
*/

#if ! defined( WFC_NOFORCE_LIBS )
#include <wfc_linker_setup.h>
#endif // WFC_NOFORCE_LIBS

#if ! defined( _WIN32_WINNT )
#define _WIN32_WINNT 0x0400
#endif

#if defined( WFC_STL )

#include <process.h>
#include <time.h>
#include <stdio.h>
#include <stddef.h>
#include <tchar.h>

#else //  defined( WFC_STL )

/*
** Include all the needed MFC stuff
*/

#include <afx.h>
#include <afxwin.h>
#include <afxcoll.h>
#include <afxmt.h>
#include <afxdisp.h> // For COleDateTime

// Thanks go to COLIN N EBERHARDT <phycne@phys-irc.novell.leeds.ac.uk>
// for finding a bug here (I had a trailing semicolon)

#if ( _MSC_VER < 1020 )
#pragma message( "WFC was designed to be compiled with Visual C++ 4.2 or later, some classes won't be compiled" )
#else // _MSC_VER < 1020
#include <afxinet.h>
#endif // _MSC_VER < 1020

#endif // WFC_STL

/*
** Include all the NT stuff
*/

#include <winspool.h>
#include <winperf.h>
#include <winsock.h>

#if ! defined( _WINUSER_ )
#include <winuser.h>
#endif // _WINUSER_

#if ( _MSC_VER > 1000 )
#include <wincrypt.h>
#endif // _MSC_VER

#include <ras.h>
#include <raserror.h>

#if ( _MSC_VER > 1000 )
extern "C" {
#include <rassapi.h>
}
#endif // _MSC_VER

#if ! defined( PDWORD_PTR )
#define PDWORD_PTR LPDWORD
#endif

#include <winuser.h>
#include <lm.h>
#include <lmat.h>
#include <lzexpand.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <math.h> // used in CRandomNumberGenerator
#include <process.h> // used in beginthreadex() in CService
#include <sqltypes.h> // For CSystemTime's support of TIMESTAMP_STRUCT
#include <winioctl.h> // For CVolume stuff
#include <commdlg.h> // For GetFileTitle() in CFile64

#if ! defined( _NTSECAPI_ )
#include <ntsecapi.h>
#endif // _NTSECAPI_

// Thus endeth the Microsoft specific section, let's start our own
// declarations now.

// 2000-03-12
// Thanks go to Nick Britzman for clueing me in on the LMSTR data type
// that is new for Win2000 (NT5). For years (and many bug reports from
// this author that obviously feel on deaf ears), Microsoft has screwed up
// the LanManager API. In NT, you could pass only UNICODE strings even though
// the API's were prototyped to take either ANSI or UNICODE strings. In the
// Jan 2000 Platform SDK, they created a new string type called LMSTR
// (LanManager string). This broke my class library. :-(

#if ! defined( LMSTR )

// We are not compiling with the new LMSTR data type. Let's use the
// old data type

#define LMSTR LPTSTR

#endif // LMSTR

#include <wfcfloat.h> // For UNICODE floating point routines

// 1999-08-17
// Thanks go to Brad Hubbard (hygbradh@mpx.com.au) for finding
// a TCHAR.H bug when using Visual C++ 5.0 (KB Q168433)

#if ( _MSC_VER < 1200 )
#ifdef _UNICODE
   #ifdef  _ttoi64
      #undef  _ttoi64
      #define _ttoi64 _wtoi64
   #endif
#else
   #ifdef  _ttoi64
      #undef  _ttoi64
      #define _ttoi64 _atoi64
   #endif
#endif

#if ! defined( atoi64 )
#define atoi64 _atoi64
#endif // atoi64

#endif // _MSC_VER < 1200

#if 0
#if ( _MSC_VER > 1000 )
namespace Win32FoundationClasses
{
#endif // _MSC_VER > 1000
#endif // 0

#include "wfctrace.hpp"

#define CARRIAGE_RETURN (13)
#define LINE_FEED       (10)
#define WFC_STANDARD_TIME_FORMAT TEXT( "%H:%M:%S %d %b %Y" ) 

/*
** An easy way to refer to colors . . .
*/

#define BLACK     RGB( 0x00, 0x00, 0x00 )
#define RED       RGB( 0xFF, 0x00, 0x00 )
#define GREEN     RGB( 0x00, 0xFF, 0x00 )
#define YELLOW    RGB( 0xFF, 0xFF, 0x00 )
#define DKGRAY    RGB( 0x7F, 0x7F, 0x7F )
#define DARK_GRAY DKGRAY
#define LTGRAY    RGB( 0xC0, 0xC0, 0xC0 )
#define LIGHT_GRAY LTGRAY
#define DKRED     RGB( 0x7F, 0x00, 0x00 )
#define DARK_RED  DKRED
#define MAGENTA   RGB( 0xFF, 0x00, 0xFF )
#define PURPLE    RGB( 0x7F, 0x00, 0x7F )
#define BLUE      RGB( 0x00, 0x00, 0xFF )
#define DKBLUE    RGB( 0x00, 0x00, 0x7F )
#define DARK_BLUE DKBLUE
#define INDIGO    RGB( 0x00, 0xFF, 0xFF )
#define DKINDIGO  RGB( 0x00, 0x7F, 0x7F )
#define DARK_INDIGO DKINDIGO
#define WHITE     RGB( 0xFF, 0xFF, 0xFF )
#define DKGREEN   RGB( 0x00, 0x7F, 0x00 )
#define DARK_GREEN DKGREEN
#define DKTYELLOW RGB( 0x7F, 0x7F, 0x00 )
#define DARK_YELLOW DKYELLOW
#define LTYELLOW  RGB( 0xFF, 0xFF, 0x7F )
#define LIGHT_YELLOW LTYELLOW

// Bits...

#define BIT_0  (0x1)
#define BIT_1  (0x2)
#define BIT_2  (0x4)
#define BIT_3  (0x8)
#define BIT_4  (0x10)
#define BIT_5  (0x20)
#define BIT_6  (0x40)
#define BIT_7  (0x80)
#define BIT_8  (0x100)
#define BIT_9  (0x200)
#define BIT_10 (0x400)
#define BIT_11 (0x800)
#define BIT_12 (0x1000)
#define BIT_13 (0x2000)
#define BIT_14 (0x4000)
#define BIT_15 (0x8000)
#define BIT_16 (0x10000)
#define BIT_17 (0x20000)
#define BIT_18 (0x40000)
#define BIT_19 (0x80000)
#define BIT_20 (0x100000)
#define BIT_21 (0x200000)
#define BIT_22 (0x400000)
#define BIT_23 (0x800000)
#define BIT_24 (0x1000000)
#define BIT_25 (0x2000000)
#define BIT_26 (0x4000000)
#define BIT_27 (0x8000000)
#define BIT_28 (0x10000000)
#define BIT_29 (0x20000000)
#define BIT_30 (0x40000000)
#define BIT_31 (0x80000000)

void ASCII_to_UNICODE( LPCSTR ansi_string, LPWSTR unicode_string );
void UNICODE_to_ASCII( LPCWSTR unicode_string, LPSTR ansi_string, long number_of_unicode_characters_to_convert = (-1) );
void Convert_NERR_Code_to_String( DWORD error_code, CString& error_message );
void PASCAL wfc_append_text_to_edit_control( HWND edit_control_handle, LPCTSTR text_string );
void PASCAL wfc_convert_lpcstr_to_cstring( const char * source_string, CString& destination_string );
void PASCAL wfc_convert_lpcwstr_to_cstring( LPCWSTR source_string, CString& destination_string );
void PASCAL wfc_convert_lpcstr_to_cstring( const char * source_string, CString& destination_string );

#include "samtf.h"

#if ! defined( BITBOOL )
#define BITBOOL(x) (!(!(x)))
#endif

#if ! defined( bit_set )
#define bit_set(   arg, posn ) ((arg) |= (1L << (posn)))
#endif

#if ! defined( bit_clear )
#define bit_clear( arg, posn ) ((arg) &= ~(1L << (posn)))
#endif

#if ! defined( bit_test )
#define bit_test(  arg, posn ) BITBOOL((arg) & (1L << (posn)))
#endif

#if ! defined( DIMENSION_OF )
#define DIMENSION_OF( argument ) ( sizeof( argument ) / sizeof( *( argument ) ) )
#endif

#if defined( WFC_STL )
#include <CCriticalSection.hpp>
#include <CTimeEx.hpp>
#include <CFile.hpp>
#endif // WFC_STL

#include <CFile64.hpp>

/*
** Structure Helpers
*/

#include <Structs.hpp>
#include <Guards.hpp>

/*
** The Registration Database API
*/

#include <CRegisty.hpp>

/*
** Event Logging
*/

#include <CEventLogRecord.hpp>
#include <CEvntLog.hpp>

#include <CUNC.hpp>
#include <CURL.hpp>

/*
** Remote Access Service
*/

#include <CRASPORT.hpp>
#include <CRAS.hpp>

/*
** CFile stuff
*/

#include <DumyFile.hpp>
#include <Serial.hpp>
#include <Modem.hpp>

/*
** Simple Sockets
*/

#include <sockets.hpp>
#include <lsockets.hpp>
#include <tsockets.hpp>
#include <SockFile.hpp>
#include <CPing.hpp>

/*
** Named Pipes
*/

#include <cnmpipe.hpp>

#include <CBitArray.hpp>
#include <CBase64Coding.hpp>
#include <CUUCoding.hpp>
#include <CQueue.hpp>
#include <CFileTime.hpp>
#include <CSystemTime.hpp>
#include <lzfile.hpp>
#include <PortInformation.hpp>
#include <CNetwork.hpp>
#include <crasadm.hpp>
#include <CServer.hpp>
#include <CNetRsrc.hpp>
#include <CNetSess.hpp>
#include <CNetWkst.hpp>
#include <CNetFile.hpp>
#include <CNetConn.hpp>
#include <CNetShar.hpp>
#include <CNetInfo.hpp>
#include <CNetUser.hpp>
#include <Ovrlpd.hpp>
#include <dcb.hpp>
#include <ServiceConfiguration.hpp>
#include <CService.hpp>
#include <CSvcMgr.hpp>
//#include <CWait.hpp>
#include <CBubble.hpp>

#if ! defined( WFC_STL )
// Sorry, there's no GUI stuff in the STL build of WFC
#include <DrawObj.hpp>
#include <DrawGrid.hpp>
#include <CSquigl.hpp>
#include <CConstellation.hpp>
#endif // WFC_STL

#include <CSMTF.hpp>
#include <CTape.hpp>
#include <CMicrosoftTape.hpp>
#include <Pager.hpp>
#include <SkyWord.hpp>
#include <SprintSpectrum.hpp>
#include <CMixer.hpp>
#include <CCrypto.hpp>
#include <CWeather.hpp>
#include <CRandomNumberGenerator.hpp>
#include <CRandomNumberGenerator2.hpp>
#include <CSuperRandomNumberGenerator.hpp>
#include <CDesktop.hpp>
#include <CGarbageCollector.hpp>
#include <CDataChunk.hpp>
#include <CDataFile.hpp>
#include <CDataMemory.hpp>
#include <CDataSocket.hpp>
#include <CDataArchive.hpp>
#include <CPasswordChangeFilter.hpp>
#include <CReedSolomonErrorCorrectionCode.hpp>
#include <CFileTransferProtocol.hpp>
#include <CNetworkScheduleJob.hpp>
#include <CParsePoint.hpp>
#include <CDataParser.hpp>
#include <CExtensibleMarkupLanguage.hpp>
#include <CXMLArchive.hpp>
#include <CDragQuery.hpp>
#include <CVolume.hpp>
#include <CServiceApplication.hpp>
#include <CPhysicalDiskFile.hpp>
#include <CFileDirectory.hpp>
#include <CMemoryFile.hpp>
#include <CJulianDate.hpp>
#include <CSharedMemoryObject.hpp>
#include <wfc_thread_information_block.h>
#include <wfc_undocumented.h>

// Some new NT5 privileges

#if ! defined( SE_DENY_INTERACTIVE_LOGON_NAME )
#define SE_DENY_INTERACTIVE_LOGON_NAME TEXT( "SeDenyInteractiveLogonRight" )
#endif // SE_DENY_INTERACTIVE_LOGON_NAME

#if ! defined( SE_DENY_NETWORK_LOGON_NAME )
#define SE_DENY_NETWORK_LOGON_NAME TEXT( "SeDenyNetworkLogonRight" )
#endif // SE_DENY_NETWORK_LOGON_NAME

#if ! defined( SE_DENY_BATCH_LOGON_NAME )
#define SE_DENY_BATCH_LOGON_NAME TEXT( "SeDenyBatchLogonRight" )
#endif // SE_DENY_BATCH_LOGON_NAME

#if ! defined( SE_DENY_SERVICE_LOGON_NAME )
#define SE_DENY_SERVICE_LOGON_NAME TEXT( "SeDenyServiceLogonRight" )
#endif // SE_DENY_SERVICE_LOGON_NAME

#if ! defined( SE_UNDOCK_NAME )
#define SE_UNDOCK_NAME TEXT( "SeUndockPrivilege" )
#endif // SE_UNDOCK_NAME

#if ! defined( SE_SYNC_AGENT_NAME )
#define SE_SYNC_AGENT_NAME TEXT( "SeSyncAgentPrivilege" )
#endif // SE_SYNC_AGENT_NAME

#if ! defined( SE_ENABLE_DELEGATION_NAME )
#define SE_ENABLE_DELEGATION_NAME TEXT( "SeEnableDelegationPrivilege" )
#endif // SE_ENABLE_DELEGATION_NAME

// C Helper functions...

BOOL PASCAL wfc_am_i_administrator( void );
BOOL PASCAL wfc_close_handle( HANDLE handle );
BOOL PASCAL wfc_create_hard_link( LPCTSTR new_filename, LPCTSTR existing_filename, LPSECURITY_ATTRIBUTES sa );
BOOL PASCAL wfc_delete_oldest_file( const CString& directory_path );
BOOL PASCAL wfc_enable_privilege( LPCTSTR privilege_name );
BOOL PASCAL wfc_enable_all_privileges( void );
BOOL PASCAL wfc_get_day_of_week( int year_with_century, int month, int day, int& day_of_week );
BOOL PASCAL wfc_get_filename_from_handle( HANDLE file_handle, CString& filename );
BOOL PASCAL wfc_move_file_at_reboot( const CString& existing_file, const CString& file_to_move );
BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, CFileTime&    the_time );
BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, CSystemTime&  the_time );

#if ! defined( WFC_STL )
BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, COleDateTime& the_time );
#endif // WFC_STL

BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, CTime&        the_time );

DWORD PASCAL wfc_get_directory_usage_percentage( const CString& directory_path );

#if ! defined( WFC_STL )
// The STL version of WFC uses a macro to accomplish this task
void PASCAL wfc_append_string_to_CByteArray( const CString& string_to_append, CByteArray& bytes );
#endif // WFC_STL

void PASCAL wfc_convert_double_null_terminated_string( const BYTE * buffer, CStringArray& string_array ); // New for 41
void PASCAL wfc_convert_double_null_terminated_UNICODE_string( const WORD * buffer, CStringArray& string_array ); // New for 45
void PASCAL wfc_get_error_string( DWORD error_code, CString& error_string );
void PASCAL wfc_get_executable_directory( CString& directory_name_ending_in_a_slash );
void PASCAL wfc_get_operating_system_version_string( CString& version_string );
void PASCAL wfc_get_web_page( CUniformResourceLocator& url, CStringArray& page_contents );
void PASCAL wfc_start_screen_saver( void );

// Coverage analysis stuff
#define WFC_COVERAGE_DECLARE
#define WFC_COVERAGE( x )
#define WFC_COVERAGE_REPORT()
#define WFC_COVERAGE_SET_NUMBER_OF_POINTS( x )

/*
** Last but not least, let's see if we are building a UNICODE console
** application, if so, we need to do one last thing for the user:
*/

#if defined( _UNICODE )
#if defined( _CONSOLE )
// We're building a console application
#pragma comment( linker, "/ENTRY:wmainCRTStartup" )
#else // _CONSOLE
// We're building a GUI application
#pragma comment( linker, "/ENTRY:wWinMainCRTStartup" )
#endif // _CONSOLE
#endif // _UNICODE

#if 0
#if ( _MSC_VER > 1000 )
// Terminate the namespace declaration
}
#endif // _MSC_VER > 1000
#endif // 0

#pragma warning( disable : 4699 )

#endif // WIN32_FOUNDATION_CLASSES
