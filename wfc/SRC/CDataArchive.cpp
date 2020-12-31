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
** $Workfile: CDataArchive.cpp $
** $Revision: 14 $
** $Modtime: 1/04/00 5:06a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CDataArchive::CDataArchive()
{
   WFCLTRACEINIT( TEXT( "CDataArchive::CDataArchive()" ) );

   m_AmIWriting  = FALSE;
   m_DataChunk_p = NULL;
   m_Position    = 0;
}

CDataArchive::~CDataArchive()
{
   WFCLTRACEINIT( TEXT( "CDataArchive::~CDataArchive()" ) );

   m_AmIWriting  = FALSE;
   m_DataChunk_p = NULL;
   m_Position    = 0;
}

BOOL CDataArchive::IsLoading( void ) const
{
   WFCLTRACEINIT( TEXT( "CDataArchive::IsLoading()" ) );

   if ( m_AmIWriting == FALSE )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CDataArchive::IsStoring( void ) const
{
   WFCLTRACEINIT( TEXT( "CDataArchive::IsStoring()" ) );

   if ( m_AmIWriting != FALSE )
   {
      return( TRUE );
   }

   return( FALSE );
}

void CDataArchive::Read( BYTE& value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( BYTE )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      value = m_DataChunk_p->Data.GetAt( m_Position );
      m_Position++;
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( CByteArray& array )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( CByteArray )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      DWORD number_of_array_entries = 0;

      Read( number_of_array_entries );

      // Make sure there are enough bytes left in the chunk to complete the read
      ASSERT( ( m_Position + number_of_array_entries ) <= (DWORD) m_DataChunk_p->Data.GetSize() );

      if ( ( m_Position + number_of_array_entries ) > (DWORD) m_DataChunk_p->Data.GetSize() )
      {
         array.RemoveAll();
         return;
      }

      array.SetSize( number_of_array_entries );

      const BYTE * buffer = m_DataChunk_p->Data.GetData();

      ::memcpy( array.GetData(), &buffer[ m_Position ], number_of_array_entries );

      m_Position += number_of_array_entries;
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( CDWordArray& array )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( CDWordArray )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      DWORD number_of_array_entries = 0;

      Read( number_of_array_entries );

      // Make sure there are enough bytes left in the chunk to complete the read
      ASSERT( ( m_Position + ( number_of_array_entries * sizeof( DWORD ) ) ) <= (DWORD) m_DataChunk_p->Data.GetSize() );

      if ( ( m_Position + ( number_of_array_entries * sizeof( DWORD ) ) ) > (DWORD) m_DataChunk_p->Data.GetSize() )
      {
         array.RemoveAll();
         return;
      }

      array.SetSize( number_of_array_entries );

      const BYTE * buffer = m_DataChunk_p->Data.GetData();

      ::memcpy( array.GetData(), &buffer[ m_Position ], number_of_array_entries * sizeof( DWORD ) );

      m_Position += ( number_of_array_entries * sizeof( DWORD ) );
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( char& value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( char )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   BYTE character = 0;

   Read( character );

   value = character;
}

void CDataArchive::Read( CStringArray& array )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( CStringArray )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      DWORD number_of_array_entries = 0;

      Read( number_of_array_entries );

      DWORD index = 0;

      CString string;

      while( index < number_of_array_entries )
      {
         Read( string );

         array.Add( string );
         string.Empty();

         index++;
      }
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( CString& value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( CString )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      // Always start with an empty string
      value.Empty();

      TCHAR character = 0;

      Read( character );

      while( character != 0 )
      {
         value += character;
         Read( character );
      }
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( CWordArray& array )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( CWordArray )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      DWORD number_of_array_entries = 0;

      Read( number_of_array_entries );

      // Make sure there are enough bytes left in the chunk to complete the read
      ASSERT( ( m_Position + ( number_of_array_entries * sizeof( WORD ) ) ) <= (DWORD) m_DataChunk_p->Data.GetSize() );

      if ( ( m_Position + ( number_of_array_entries * sizeof( WORD ) ) ) > (DWORD) m_DataChunk_p->Data.GetSize() )
      {
         array.RemoveAll();
         return;
      }

      array.SetSize( number_of_array_entries );

      const BYTE * buffer = m_DataChunk_p->Data.GetData();

      ::memcpy( array.GetData(), &buffer[ m_Position ], number_of_array_entries * sizeof( WORD ) );

      m_Position += ( number_of_array_entries * sizeof( WORD ) );
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( double& value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( double )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      const BYTE * buffer = m_DataChunk_p->Data.GetData();

      value = *( (double *) &buffer[ m_Position ] );
      m_Position += sizeof( double );
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( DWORD& value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( DWORD )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      const BYTE * buffer = m_DataChunk_p->Data.GetData();

      value = *( (DWORD *) &buffer[ m_Position ] );

      WFCTRACEVAL( TEXT( "Read " ), value );
      m_Position += sizeof( DWORD );
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( float& value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( float )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      const BYTE * buffer = m_DataChunk_p->Data.GetData();

      value = *( (float *) &buffer[ m_Position ] );
      m_Position += sizeof( float );
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( LONG& value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( LONG )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      const BYTE * buffer = m_DataChunk_p->Data.GetData();

      value = *( (LONG *) &buffer[ m_Position ] );
      m_Position += sizeof( LONG );
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Read( WORD& value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Read( WORD )" ) );

   if ( m_AmIWriting == TRUE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called ReadFrom() or you passed a NULL to ReadFrom()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      const BYTE * buffer = m_DataChunk_p->Data.GetData();

      value = *( (WORD *) &buffer[ m_Position ] );
      m_Position += sizeof( WORD );
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::ReadFrom( CDataChunk * chunk_p )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::ReadFrom()" ) );

   m_AmIWriting  = FALSE;
   m_DataChunk_p = chunk_p;
   m_Position    = 0;
}

void CDataArchive::Write( BYTE value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( BYTE )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      m_DataChunk_p->Data.Add( value );
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Write( char value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( value )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   BYTE byte = (BYTE) value;

   Write( byte );
}

void CDataArchive::Write( const CByteArray& array )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( CByteArray )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      DWORD number_of_array_entries = array.GetSize();

      Write( number_of_array_entries );

      m_DataChunk_p->Data.Append( array );
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Write( const CDWordArray& array )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( CDWordArray )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   DWORD number_of_array_entries = array.GetSize();

   Write( number_of_array_entries );

   DWORD index = 0;

   while( index < number_of_array_entries )
   {
      Write( array.GetAt( index ) );

      index++;
   }
}

void CDataArchive::Write( const CString& value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( CString )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   DWORD index  = 0;
   DWORD length = value.GetLength();

   while( index < length )
   {
      Write( value.GetAt( index ) );
      index++;
   }

   // NULL terminate

   TCHAR character = 0;

   Write( character );
}

void CDataArchive::Write( const CStringArray& array )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( CStringArray )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   DWORD number_of_array_entries = array.GetSize();

   Write( number_of_array_entries );

   DWORD index = 0;

   while( index < number_of_array_entries )
   {
      Write( array.GetAt( index ) );

      index++;
   }
}

void CDataArchive::Write( const CWordArray& array )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( CWordArray )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   DWORD number_of_array_entries = array.GetSize();

   Write( number_of_array_entries );

   DWORD index = 0;

   while( index < number_of_array_entries )
   {
      Write( array.GetAt( index ) );

      index++;
   }
}

void CDataArchive::Write( double value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( double )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      BYTE * buffer = reinterpret_cast<BYTE *>( &value );

      int index = 0;

      while( index < sizeof( value ) )
      {
         m_DataChunk_p->Data.Add( buffer[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Write( DWORD value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( DWORD )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      BYTE * buffer = reinterpret_cast<BYTE *>( &value );

      int index = 0;

      while( index < sizeof( value ) )
      {
         WFCTRACEVAL( TEXT( "Adding " ), buffer[ index ] );
         m_DataChunk_p->Data.Add( buffer[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Write( float value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( float )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      BYTE * buffer = reinterpret_cast<BYTE *>( &value );

      int index = 0;

      while( index < sizeof( value ) )
      {
         m_DataChunk_p->Data.Add( buffer[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Write( LONG value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( LONG )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      BYTE * buffer = reinterpret_cast<BYTE *>( &value );

      int index = 0;

      while( index < sizeof( value ) )
      {
         m_DataChunk_p->Data.Add( buffer[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::Write( WORD value )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::Write( WORD )" ) );

   if ( m_AmIWriting == FALSE || m_DataChunk_p == NULL )
   {
      WFCTRACE( TEXT( "You haven't called WriteTo() or you passed a NULL to WriteTo()" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      BYTE * buffer = reinterpret_cast<BYTE *>( &value );

      int index = 0;

      while( index < sizeof( value ) )
      {
         m_DataChunk_p->Data.Add( buffer[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      return;
   }
}

void CDataArchive::WriteTo( CDataChunk * chunk_p )
{
   WFCLTRACEINIT( TEXT( "CDataArchive::WriteTo()" ) );

   m_AmIWriting  = TRUE;
   m_DataChunk_p = chunk_p;
   m_Position    = 0;
}

// End of source