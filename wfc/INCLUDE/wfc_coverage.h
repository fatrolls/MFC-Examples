#if ! defined( WFC_COVERAGE_HEADER_FILE )

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
** $Workfile: wfc_coverage.h $
** $Revision: 1 $
** $Modtime: 7/15/99 7:00a $
*/

#define WFC_COVERAGE_HEADER_FILE

#if defined( WFC_COVERAGE_ANALYSIS )

// wfc.h already defines these for us so we must undefine them

#undef WFC_COVERAGE_DECLARE
#undef WFC_COVERAGE
#undef WFC_COVERAGE_REPORT
#undef WFC_COVERAGE_SET_NUMBER_OF_POINTS

#define WFC_COVERAGE_DECLARE CDWordArray __wfc_call_count;\
static void __wfc_coverage_report( void )\
{ DWORD loop_index = 0; CString debug_string; while( loop_index < __wfc_call_count.GetSize() )\
{ debug_string.Format( TEXT( "%lu. %lu\n" ), loop_index, __wfc_call_count.GetAt( loop_index ) ) ;\
TRACE( debug_string ); _tprintf( TEXT( "%s" ), (LPCTSTR) debug_string ); loop_index++; } }

#define WFC_COVERAGE( x ) __wfc_call_count.SetAt( x, __wfc_call_count.GetAt( x ) + 1 )
#define WFC_COVERAGE_REPORT() __wfc_coverage_report()
#define WFC_COVERAGE_SET_NUMBER_OF_POINTS( x ) __wfc_call_count.SetSize( x )


#endif // WFC_COVERAGE_ANALYSIS

#endif // WFC_COVERAGE_HEADER_FILE
