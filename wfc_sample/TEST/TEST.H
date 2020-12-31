#if ! defined( WINVER )
#define WINVER 0x401
#endif

#include <wfc.h>

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like.
**
** $Workfile: TEST.H $
** $Revision: 12 $
** $Modtime: 5/16/00 5:50p $
*/

// Standard testing functions

typedef BOOL (*TEST_FUNCTION)( CString&, int& );

BOOL test_CBase64Coding( CString& class_name, int& test_number_that_failed );
BOOL test_CByteArray( CString& class_name, int& test_number_that_failed );
BOOL test_CDataParser( CString& class_name, int& test_number_that_failed );
BOOL test_CDWordArray( CString& class_name, int& test_number_that_failed );
BOOL test_CPtrArray( CString& class_name, int& test_number_that_failed );
BOOL test_CString( CString& class_name, int& test_number_that_failed );
BOOL test_CUIntArray( CString& class_name, int& test_number_that_failed );
BOOL test_CWordArray( CString& class_name, int& test_number_that_failed );
BOOL test_CQueue( CString& class_name, int& test_number_that_failed );

void CQueue_stress_test( void );
void memory( void );
void ReportError( DWORD error_code );
void test_CBitArray( void );
void test_CEventLog( void );
void test_CFileTransferProtocol( void );
void test_CJulianDate( void );
void test_CLZFile( LPTSTR lz_file_name );
void test_CNetResource( void );
void test_CNetSession( LPCTSTR machine_name );
void test_CNetwork( LPCTSTR machine_name );
void test_CNetWorkstation( LPCTSTR machine_name );
void test_CNetworkConnections( LPCTSTR machine_name );
void test_CNetworkFiles( LPCTSTR machine_name );
void test_CNetworkShares( LPCTSTR machine_name );
void test_CNetworkUsers( LPCTSTR machine_name );
void test_CRandomNumberGenerator( void );
void test_CReedSolomonErrorCorrectionCode( void );
void test_CRegistry( void );
void test_CRAS( void );
void test_CSerialFile( void );
void test_CServer( LPCTSTR machine_name );
void test_CServiceControlManager( void );
void test_CSystemTime( void );
void test_CTape( UINT tape_drive_number_starting_at_zero );
void test_CUUCoding( void );
void test_CUniformResourceLocator( void );
void test_CXMLDocument( void );

LPTSTR BigNumToString( LONG lNum, LPTSTR string );



