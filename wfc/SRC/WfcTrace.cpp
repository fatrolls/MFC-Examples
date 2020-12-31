#include <wfc.h>
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
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: WfcTrace.cpp $
** $Revision: 25 $
** $Modtime: 3/18/00 7:53a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

int   CWfcTrace::Indent  = 0;
BOOL  CWfcTrace::Tracing = TRUE;
DWORD CWfcTrace::Levels  = 1;

CWfcTrace::CWfcTrace( const CString& function_name, DWORD tracing_level )
{
   m_FunctionName = function_name;
   m_TracingLevel = tracing_level;

   if ( Levels & m_TracingLevel )
   {
      if ( Tracing != FALSE )
      {
         m_Indent();

         CString string_to_output( TEXT( "Entering " ) );

         string_to_output += m_FunctionName;
         string_to_output += TEXT( "\n" );

         OutputDebugString( string_to_output );
      }

      Indent += 2;
   }
}

CWfcTrace::~CWfcTrace()
{
   if ( Levels & m_TracingLevel )
   {
      Indent -= 2;

      if ( Tracing != FALSE )
      {
         m_Indent();

         CString string_to_output( TEXT( "Leaving  " ) );

         string_to_output += m_FunctionName;
         string_to_output += TEXT( "\n" );

         OutputDebugString( string_to_output );
      }

      m_FunctionName.Empty();
   }
}

void CWfcTrace::m_Indent( void ) const
{
   if ( ( Levels & m_TracingLevel ) && Tracing != FALSE )
   {
      if ( Indent > 0 )
      {
         CString spaces( TEXT( "" ) );

         int index = 0;

         while( index < Indent )
         {
            spaces += TEXT( " " );
            index++;
         }

         OutputDebugString( spaces );
      }
   }
}

void CWfcTrace::Output( const CString& message ) const
{
   if ( ( Levels & m_TracingLevel ) && Tracing != FALSE )
   {
      m_Indent();

      CString output_string( m_FunctionName );

      output_string += TEXT( " : " );
      output_string += message;

      if ( output_string.GetLength() > 510 )
      {
         output_string = output_string.Left( 510 );
      }

      output_string += TEXT( "\n" );

      OutputDebugString( output_string );
   }
}

void CWfcTrace::Output( const CString& message, const int integer ) const
{
   TCHAR temp_string[ 11 ];

   ::ZeroMemory( temp_string, sizeof( temp_string ) );
   _itot( integer, temp_string, 10 );

   Output( message + temp_string );
}

void CWfcTrace::Output( const CString& message, const UINT integer ) const
{
   Output( message, (ULONG) integer );
}

void CWfcTrace::Output( const CString& message, const long a_long ) const
{
   TCHAR temp_string[ 11 ];

   ::ZeroMemory( temp_string, sizeof( temp_string ) );
   _ltot( a_long, temp_string, 10 );

   Output( message + temp_string );
}

void CWfcTrace::Output( const CString& message, const ULONG a_long ) const
{
   TCHAR temp_string[ 11 ];

   ::ZeroMemory( temp_string, sizeof( temp_string ) );
   _ultot( a_long, temp_string, 10 );

   Output( message + temp_string );
}

void CWfcTrace::Output( const CString& message, const LONGLONG a_long ) const
{
   TCHAR temp_string[ 31 ];

   ::ZeroMemory( temp_string, sizeof( temp_string ) );
   _i64tot( a_long, temp_string, 10 );

   Output( message + temp_string );
}

void CWfcTrace::Output( const CString& message, const ULONGLONG a_long ) const
{
   TCHAR temp_string[ 31 ];

   ::ZeroMemory( temp_string, sizeof( temp_string ) );
   _ui64tot( a_long, temp_string, 10 );

   Output( message + temp_string );
}

void CWfcTrace::Output( const CString& message, const double a_double ) const
{
   int decimal = 0;
   int sign    = 0;

   char *ascii_string_p = NULL;

   LPCTSTR string_p = NULL;

   ascii_string_p = ::_fcvt( a_double, 7, &decimal, &sign );

#if defined( UNICODE )

   // We need to convert

   WCHAR unicode_string[ 1024 ];

   unicode_string[ 0 ] = 0x00;

   ASCII_to_UNICODE( ascii_string_p, unicode_string );

   string_p = unicode_string;

#else

   // No conversion needed

   string_p = ascii_string_p;

#endif

   CString string( TEXT( "" ) );

   if ( sign != 0 )
   {
      string = TEXT( "-" );
   }

   if ( decimal < 1 )
   {
      string += TEXT( "." );

      int index = 0;

      while( index > decimal )
      {
         string += TEXT( "0" );
         index--;
      }

      string += string_p;
   }
   else if ( decimal >= (int) _tcslen( string_p ) )
   {
      string += string_p;
      string += TEXT( "." );
   }
   else
   {
      int index = 0;

      while( index < decimal )
      {
         string += string_p[ index ];
         index++;
      }

      string += TEXT( "." );

      index = decimal;

      while( index < (int) _tcslen( string_p ) )
      {
         string += string_p[ index ];
         index++;
      }
   }

   Output( message + string );
}

void CWfcTrace::Output( const CString& message, const CString& string ) const
{
   Output( message + string );
}

void CWfcTrace::Output( const CString& message, const VOID * pointer ) const
{
   CString pointer_string;

   pointer_string.Format( TEXT( "%p" ), pointer );

   Output( message + pointer_string );
}

#if ! defined(  WFC_NO_SERIALIZATION )

#if defined( _DEBUG )
void CWfcTrace::Output( const CString& message, const CObject * object_p ) const
#else
void CWfcTrace::Output( const CString&, const CObject * ) const
#endif // _DEBUG
{
   try
   {
#if defined( _DEBUG )
      if ( object_p == NULL )
      {
         Output( message + TEXT( "NULL POINTER!" ) );
      }
      else
      {
         Output( message, *object_p );
      }
#endif // _DEBUG
   }
   catch( ... )
   {
      ;
   }
}

#if defined( _DEBUG )
void CWfcTrace::Output( const CString& message, const CObject& object ) const
#else
void CWfcTrace::Output( const CString& message, const CObject& ) const
#endif // _DEBUG
{
   Output( message + TEXT( " dump:" ) );

#if defined( _DEBUG )

   object.Dump( afxDump );

   CRuntimeClass * runtime_data_p = object.GetRuntimeClass();

   CString class_name;

   try
   {
#if defined( UNICODE )
      ::wfc_convert_lpcstr_to_cstring( runtime_data_p->m_lpszClassName, class_name );
#else
      class_name = runtime_data_p->m_lpszClassName;
#endif

      if ( class_name.Compare( TEXT( "CByteArray" ) ) == 0 )
      {
         // Dump da bytes

         CByteArray * bytes_p = (CByteArray *) &object;

         CString spaces( TEXT( "" ) );

         if ( Indent > 0 )
         {
            int index = 0;

            while( index < Indent )
            {
               spaces += TEXT( " " );
               index++;
            }
         }

         afxDump.HexDump( spaces, bytes_p->GetData(), bytes_p->GetSize(), 20 );
      }
   }
   catch( ... )
   {
      ;
   }

#endif // _DEBUG

   Output( TEXT( "End of " ) + message + TEXT( " dump." ) );
}

#endif // WFC_NO_SERIALIZATION

void CWfcTrace::Output( const CString& message, const LARGE_INTEGER& value ) const
{
   CString pointer_string;

   pointer_string.Format( TEXT( "{ QuadPart=%I64d { LowPart=0x%lX HighPart=0x%lX } }" ),
                          value.QuadPart, value.LowPart, value.HighPart );

   Output( message + pointer_string );
}

void CWfcTrace::Output( const CString& message, const ULARGE_INTEGER& value ) const
{
   CString pointer_string;

   pointer_string.Format( TEXT( "{ QuadPart=%I64u { LowPart=0x%lX HighPart=0x%lX } }" ),
                          value.QuadPart, value.LowPart, value.HighPart );

   Output( message + pointer_string );
}

void CWfcTrace::Output( const CString& message, const RECT& value ) const
{
   CString pointer_string;

   pointer_string.Format( TEXT( "{ left = %ld top = %ld right = %ld bottom = %ld }" ),
                          value.left, value.top, value.right, value.bottom );

   Output( message + pointer_string );
}

void CWfcTrace::Output( const CString& message, const POINT& value ) const
{
   CString pointer_string;

   pointer_string.Format( TEXT( "{ x = %ld y = %ld }" ),
                          value.x, value.y );

   Output( message + pointer_string );
}

void CWfcTrace::Output( const CString& message, const SIZE& value ) const
{
   CString pointer_string;

   pointer_string.Format( TEXT( "{ cx = %ld cy = %ld }" ),
                          value.cx, value.cy );

   Output( message + pointer_string );
}

void CWfcTrace::OutputBinary( const CString& message, const ULONG a_long ) const
{
   int index = 31;

   CString bit_string( TEXT( "" ) );

   while( index >= 0 )
   {
      if ( bit_test( a_long, index ) == 1 )
      {
         bit_string += TEXT( '1' );
      }
      else
      {
         bit_string += TEXT( '0' );
      }

      if ( index == 24 ||
           index == 16 ||
           index ==  8 )
      {
         bit_string += TEXT( ' ' );
      }

      index--;
   }

   Output( message + bit_string );
}

void CWfcTrace::OutputVariant( const CString& message, const VARIANT& value ) const
{
   OutputVariant( message, &value );
}

void CWfcTrace::OutputVariant( const CString& message, const VARIANT* value ) const
{
   CString data_type;

   DWORD vt = V_VT( value );

   // Types taken from WTYPES.H -- VARENUM data type

   if ( vt & VT_VECTOR )
   {
      data_type = TEXT( "VT_VECTOR" );
   }

   if ( vt & VT_ARRAY )
   {
      if ( data_type.GetLength() > 0 )
      {
         data_type += TEXT( " | " );
      }

      data_type += TEXT( "VT_ARRAY" );
   }

   if ( vt & VT_BYREF )
   {
      if ( data_type.GetLength() > 0 )
      {
         data_type += TEXT( " | " );
      }

      data_type += TEXT( "VT_BYREF" );
   }

   if ( vt & VT_RESERVED )
   {
      if ( data_type.GetLength() > 0 )
      {
         data_type += TEXT( " | " );
      }

      data_type += TEXT( "VT_RESERVED" );
   }

   DWORD basic_type = vt & VT_TYPEMASK;

   switch( basic_type )
   {
      case VT_EMPTY:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_EMPTY" );

         break;

      case VT_NULL:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_NULL" );

         break;

      case VT_I2:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_I2" );

         break;

      case VT_I4:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_I4" );

         break;

      case VT_R4:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_R4" );

         break;

      case VT_R8:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_R8" );

         break;

      case VT_CY:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_CY" );

         break;

      case VT_DATE:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_DATE" );

         break;

      case VT_BSTR:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_BSTR" );

         break;

      case VT_DISPATCH:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_DISPATCH" );

         break;

      case VT_ERROR:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_ERROR" );

         break;

      case VT_BOOL:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_BOOL" );

         break;

      case VT_VARIANT:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_VARIANT" );

         break;

      case VT_UNKNOWN:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_UNKNOWN" );

         break;

      case VT_DECIMAL:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_DECIMAL" );

         break;

      case VT_I1:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_I1" );

         break;

      case VT_UI1:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_UI1" );

         break;

      case VT_UI2:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_UI2" );

         break;

      case VT_UI4:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_UI4" );

         break;

      case VT_I8:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_I8" );

         break;

      case VT_UI8:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_UI8" );

         break;

      case VT_INT:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_INT" );

         break;

      case VT_UINT:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_UINT" );

         break;

      case VT_VOID:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_VOID" );

         break;

      case VT_HRESULT:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_HRESULT" );

         break;

      case VT_PTR:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_PTR" );

         break;

      case VT_SAFEARRAY:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_SAFEARRAY" );

         break;

      case VT_CARRAY:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_CARRAY" );

         break;

      case VT_USERDEFINED:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_USERDEFINED" );

         break;

      case VT_LPSTR:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_LPSTR" );

         break;

      case VT_LPWSTR:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_LPWSTR" );

         break;

      case VT_RECORD:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_RECORD" );

         break;

      case VT_FILETIME:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_FILETIME" );

         break;

      case VT_BLOB:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_BLOB" );

         break;

      case VT_STREAM:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_STREAM" );

         break;

      case VT_STORAGE:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_STORAGE" );

         break;

      case VT_STREAMED_OBJECT:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_STREAMED_OBJECT" );

         break;

      case VT_STORED_OBJECT:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_STORED_OBJECT" );

         break;

      case VT_BLOB_OBJECT:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_BLOB_OBJECT" );

         break;

      case VT_CF:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_CF" );

         break;

      case VT_CLSID:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_CLSID" );

         break;

      case VT_BSTR_BLOB:

         if ( data_type.GetLength() > 0 )
         {
            data_type += TEXT( " | " );
         }

         data_type += TEXT( "VT_BSTR_BLOB" );

         break;

      default:

         {
            CString data_type_string;

            data_type_string.Format( TEXT( "Unknown(%lu)" ), basic_type );

            if ( data_type.GetLength() > 0 )
            {
               data_type += TEXT( " | " );
            }

            data_type += data_type_string;
         }

         break;
   }

   CString variant_message( message );
   
   variant_message += TEXT( "Variant type is " );
   variant_message += data_type;

   Output( variant_message );
}

void CWfcTrace::ReportError( DWORD error_code )
{
   CString error_string;

   wfc_get_error_string( error_code, error_string );

   CString error_message;

   error_message.Format( TEXT( "ERROR %lu - " ), error_code );
   error_message += error_string;

   Output( error_message );
}

void CWfcTrace::TraceOff( void )
{
   Tracing = FALSE;
}

void CWfcTrace::TraceOn( void )
{
   Tracing = TRUE;
}

void CWfcTrace::TraceAllOff( void )
{
   Tracing = FALSE;
   Indent  = 0;
   Levels  = 0;
}

void CWfcTrace::TraceAllOn( void )
{
   Tracing = TRUE;
   Levels  = 0xFFFFFFFF;
}

void CWfcTrace::TraceLevelOn( DWORD level )
{
   if ( level > 31 )
   {
      level = 31;
   }

   bit_set( Levels, level );
}

void CWfcTrace::TraceLevelOff( DWORD level )
{
   if ( level > 31 )
   {
      level = 31;
   }

   bit_clear( Levels, level );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CWfcTrace</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that makes tracing much easier.">
</HEAD>

<BODY>

<H1>CWfcTrace</H1>
$Revision: 25 $
<HR>

<H2>Description</H2>

This class helps to debug your programs.
It prints out messages when entering and leaving functions. It automatically
indents so you can see which functions called who.
Normally, you will never use this class directly, you will use the
<A HREF="#Macros">macros</A>.
All messages generated by this class are sent to <CODE>OutputDebugString()</CODE>.

<P>

The way I write and debug programs is to have lots and lots of debugging
output. I prefer to have too many debug messages than too few. That way,
I am sure to not miss anything. By having lots of debug output, you can
see how a program really works as opposed to how you <I>think</I> a
program works. I like having twenty pages of debugging output to sift
through so I can see my bugs and the context they present themselves.

<H2>Data Members</H2>

<DL COMPACT>

<DT><PRE>static int <B>Indent</B></PRE><DD>
This value is the number of spaces that will be printed before
each line of output.

<DT><PRE>static DWORD <B>Levels</B></PRE><DD>
This is a bit mask containing which of the 32 levels of debugging are
turned on.

<DT><PRE>static BOOL <B>Tracing</B></PRE><DD>
This boolean determines if any output will be generated.
When TRUE, output (for levels that are on) will be generated.
If FALSE, nothing is outputted.

</DL>

<H2>Constructors</H2>
<DL COMPACT>
<DT><PRE><B>CWfcTrace</B>( const CString&amp; function_name, DWORD tracing_level )</PRE><DD>
You must provide the name and which level this object belongs.

</DL>

<H2>Static Methods</H2>

<DL COMPACT>
<DT><PRE>static void <B>TraceAllOn</B>( void )</PRE><DD>
Turns on all 32 levels of tracing.

<DT><PRE>static void <B>TraceAllOff</B>( void )</PRE><DD>
Turns off all 32 levels of tracing.

<DT><PRE>static void <B>TraceLevelOn</B>( DWORD level )</PRE><DD>
Turns one of the 32 levels of tracing on.

<DT><PRE>static void <B>TraceLevelOff</B>( DWORD level )</PRE><DD>
Turns one of the 32 levels of tracing off.

<DT><PRE>static void <B>TraceOn</B>( void )</PRE><DD>
Allows messages to be printed.

<DT><PRE>static void <B>TraceOff</B>( void )</PRE><DD>
Disallows messages to be printed.

</DL>

<H2>Methods</H2>

<DL COMPACT>
<DT><PRE>void Output( const CString&amp; message ) const
void Output( const CString&amp; message, const int integer ) const
void Output( const CString&amp; message, const UINT integer ) const
void Output( const CString&amp; message, const long a_long ) const
void Output( const CString&amp; message, const ULONG a_long ) const
void Output( const CString&amp; message, const LONGLONG a_long ) const
void Output( const CString&amp; message, const ULONGLONG a_long ) const
void Output( const CString&amp; message, const double a_double ) const
void Output( const CString&amp; message, const CString&amp; string ) const
void Output( const CString&amp; message, const CObject * object ) const
void Output( const CString&amp; message, const VOID * pointer ) const
void Output( const CString&amp; message, const CObject&amp; object ) const
void Output( const CString&amp; message, const LARGE_INTEGER&amp; value ) const
void Output( const CString&amp; message, const ULARGE_INTEGER&amp; value ) const
void Output( const CString&amp; message, const RECT&amp; value ) const
void Output( const CString&amp; message, const POINT&amp; value ) const
void Output( const CString&amp; message, const SIZE&amp; value ) const</PRE><DD>

Would you just look at all the stuff you can output!
I toyed with the idea of putting more data structures (like <CODE>WNDCLASS</CODE>)
but once you start down that road, you get very little return on investment.
So, I stuck with the basic data types.

<DT><PRE>void OutputBinary( const CString&amp; message, const ULONG a_long ) const</PRE><DD>
This allows you to dump the contents of a <CODE>ULONG</CODE> as
bits. This is great for picking apart bit masks.

<DT><PRE>void OutputVariant( const CString&amp; message, const VARIANT& value ) const
void OutputVariant( const CString&amp; message, const VARIANT * value ) const</PRE><DD>
This allows you to dump the contents of a <CODE>VARIANT</CODE>.

<DT><PRE>void ReportError( DWORD error_code )</PRE><DD>
Translates error codes to a humanly readable string.

</DL>

<H2><A NAME="Macros">Macros</A></H2>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;

void print_message( void )
{
   <B>WFCTRACEINIT</B>( TEXT( &quot;print_message()&quot; ) );
   <B>WFCTRACEVAL</B>( TEXT( &quot;Test number &quot; ), 1 );
}

void main( void )
{
   <B>WFCTRACEINIT</B>( TEXT( &quot;main()&quot; ) );

   print_message();
}</CODE></PRE>

Will produce this output:

<PRE><CODE
Entering main()
   Entering print_message()
      print_message() : Test number 1
   Leaving  print_message()
Leaving  main()
</CODE></PRE>

<H2>API's Used</H2>

<B>CWfcTrace</B> uses the following API's:

<UL>
<LI>OutputDebugString
<LI>ZeroMemory
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: WfcTrace.cpp $<BR>
$Modtime: 3/18/00 7:53a $
</BODY>

</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CWfcTrace=name=<m_FunctionName.m_pchData,s>
#endif
