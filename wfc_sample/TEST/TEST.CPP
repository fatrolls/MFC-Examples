#include "test.h"
#pragma hdrstop

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
** Copyright, 1999, Samuel R. Blackburn
**
** $Workfile: TEST.CPP $
** $Revision: 12 $
** $Modtime: 5/16/00 5:58p $
*/

#if defined( UNICODE )
extern "C"
#endif

int _tmain( int /* number_of_command_line_arguments */, LPCTSTR /* command_line_arguments */ [] )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   CString operating_system_version_string;

   wfc_get_operating_system_version_string( operating_system_version_string );

   WFCTRACE( operating_system_version_string );

//   memory();
//   test_CBitArray();
//   test_CEventLog();
//   test_CFileTransferProtocol();
//   test_CJulianDate();
//   test_CLZFile( TEXT( "b:\\ctl3d32.dl_" ) );
//   test_CNetResource();
//   test_CNetSession( NULL );
//   test_CNetwork( NULL );
//   test_CNetwork( TEXT( "ftp" ) );
//   test_CNetworkConnections( NULL );
//   test_CNetworkFiles( NULL );
//   test_CNetworkShares( TEXT( "ftp" ) );
//   test_CNetworkShares( NULL );
//   test_CNetWorkstation( NULL );
//   test_CNetworkUsers( NULL );
//   test_CNetworkUsers( TEXT( "ftp" ) );
//   test_CQueue();
//   test_CReedSolomonErrorCorrectionCode();
//   test_CRandomNumberGenerator();
//   test_CRAS();
//   test_CRegistry();
//   test_CSerialFile();
//   test_CServer( TEXT( "sammy" ) );
//   test_CServer( TEXT( "sammy" ) );
//   test_CServer( TEXT( "\\\\SAMMY" ) );
//   test_CServiceControlManager();
//   test_CXMLDocument();

   // The order in which you place test functions in this array
   // is important. The most basic classes should be first.
   // If one class uses another class internally, the first class
   // should appear above the other in the array. For example,
   // CString is used by CBase64Coding. CString should be tested
   // before CBase64Coding (higher in the list). This way, if
   // CBase64Coding fails, you know it is not a problem with
   // CString. 

   TEST_FUNCTION tests[] = 
   {
      test_CString,
      test_CByteArray,
      test_CDWordArray,
      test_CWordArray,
      test_CUIntArray,
      test_CPtrArray,
      //test_CDataParser,
      test_CBase64Coding,
      test_CQueue,
   };

   int test_number_that_failed = 0;

   CString class_name;

   int loop_index = 0;

   TEST_FUNCTION test_function = (TEST_FUNCTION) NULL;

   bool all_tests_passed = true;

   while( loop_index < DIMENSION_OF( tests ) )
   {
      test_function = tests[ loop_index ];

      if ( test_function( class_name, test_number_that_failed ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "This class failed " ), class_name );
         WFCTRACEVAL( TEXT( "Test number " ), test_number_that_failed );
         _tprintf( TEXT( "%s failed test number %d.\n" ), (LPCTSTR) class_name, test_number_that_failed );
         all_tests_passed = false;
      }
      else
      {
         _tprintf( TEXT( "%s passed %d tests.\n" ), (LPCTSTR) class_name, test_number_that_failed );
      }

      loop_index++;
   }

   if ( all_tests_passed == true )
   {
      _tprintf( TEXT( "All %d classes PASSED!\n" ), (int) DIMENSION_OF( tests ) );
   }
   else
   {
      _tprintf( TEXT( "FAIL!\n" ) );
   }

//   test_CSystemTime();
//   test_CTape( 0 );
//   test_CUUCoding();
//   test_CUniformResourceLocator();

//   CString my_ip_address;

//   CSimpleSocket::GetMyAddress( my_ip_address );

//   WFCTRACEVAL( TEXT( "My IP address is " ), my_ip_address );

   return( EXIT_SUCCESS );
}

LPTSTR BigNumToString( LONG lNum, LPTSTR szBuf )
{
   WORD wNumDigits = 0, wNumChars = 0;

   do
   {
      szBuf[ wNumChars++ ] = (TCHAR) (lNum % 10 + TEXT( '0' ));
      wNumDigits++;
      
      if ( ( wNumDigits % 3 ) == 0 )
      {
         szBuf[ wNumChars++ ] = TEXT( ',' );
      }

      lNum /= 10;
   }
   while( lNum != 0 );

   if ( szBuf[ wNumChars - 1 ] == TEXT( ',' ) )
   {
      szBuf[ wNumChars - 1 ] = 0x00;
   }

   szBuf[ wNumChars ] = 0x00;

   _strrev( szBuf );
   
   return( szBuf );
}

void memory( void )
{
   CMemoryStatus memory_status;

   GlobalMemoryStatus( &memory_status );

#if ! defined( WFC_STL )
   TCHAR szBuf[ 50 ];

   TRACE1( TEXT( "Memory Load:         %-20s\n" ), BigNumToString( memory_status.dwMemoryLoad,    szBuf ) );
   TRACE1( TEXT( "Total Physical:      %-20s\n" ), BigNumToString( memory_status.dwTotalPhys,     szBuf ) );
   TRACE1( TEXT( "Available Physical:  %-20s\n" ), BigNumToString( memory_status.dwAvailPhys,     szBuf ) );
   TRACE1( TEXT( "Total Page File:     %-20s\n" ), BigNumToString( memory_status.dwTotalPageFile, szBuf ) );
   TRACE1( TEXT( "Available Page File: %-20s\n" ), BigNumToString( memory_status.dwAvailPageFile, szBuf ) );
   TRACE1( TEXT( "Total Virtual:       %-20s\n" ), BigNumToString( memory_status.dwTotalVirtual,  szBuf ) );
   TRACE1( TEXT( "Available Virtual:   %-20s\n" ), BigNumToString( memory_status.dwAvailVirtual,  szBuf ) );
#endif // WFC_STL
}

