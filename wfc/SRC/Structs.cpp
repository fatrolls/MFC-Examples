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
** $Workfile: structs.cpp $
** $Revision: 19 $
** $Modtime: 1/05/00 3:43a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CAccessAllowedEntry::CAccessAllowedEntry()
{
   Empty();
}

CAccessAllowedEntry::CAccessAllowedEntry( const CAccessAllowedEntry& source )
{
   Empty();
   Copy( source );
}

CAccessAllowedEntry::CAccessAllowedEntry( const ACCESS_ALLOWED_ACE * source )
{
   Empty();
   Copy( source );
}

CAccessAllowedEntry::~CAccessAllowedEntry()
{
   Empty();
}

void CAccessAllowedEntry::Copy( const CAccessAllowedEntry& source )
{
   Copy( (const ACCESS_ALLOWED_ACE *) &source );
}

void CAccessAllowedEntry::Copy( const ACCESS_ALLOWED_ACE * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      Header.AceType  = source->Header.AceType;
      Header.AceFlags = source->Header.AceFlags;
      Header.AceSize  = source->Header.AceSize;
      Mask            = source->Mask;
      SidStart        = source->SidStart;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CAccessAllowedEntry::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CAccessAllowedEntry at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   Header.AceType  = " ) << Header.AceType  << TEXT( " (" );

   switch( Header.AceType )
   {
      case ACCESS_ALLOWED_ACE_TYPE:

         dump_context << TEXT( "ACCESS_ALLOWED_ACE_TYPE" );
         break;

      case ACCESS_DENIED_ACE_TYPE:

         dump_context << TEXT( "ACCESS_DENIED_ACE_TYPE" );
         break;

      case SYSTEM_AUDIT_ACE_TYPE:

         dump_context << TEXT( "SYSTEM_AUDIT_ACE_TYPE" );
         break;

      case SYSTEM_ALARM_ACE_TYPE:

         dump_context << TEXT( "SYSTEM_ALARM_ACE_TYPE" );
         break;
   }

   dump_context << TEXT( ")\n" );

   dump_context << TEXT( "   Header.AceFlags = " ) << Header.AceFlags << TEXT( " (" );

   CString temp_string;

   if ( Header.AceFlags & CONTAINER_INHERIT_ACE )
   {
      temp_string = TEXT( "CONTAINER_INHERIT_ACE" );
   }

   if ( Header.AceFlags & INHERIT_ONLY_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "INHERIT_ONLY_ACE" );
   }

   if ( Header.AceFlags & NO_PROPAGATE_INHERIT_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "NO_PROPAGATE_INHERIT_ACE" );
   }

   if ( Header.AceFlags & OBJECT_INHERIT_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "OBJECT_INHERIT_ACE" );
   }

   if ( Header.AceFlags & FAILED_ACCESS_ACE_FLAG )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "FAILED_ACCESS_ACE_FLAG" );
   }

   if ( Header.AceFlags & SUCCESSFUL_ACCESS_ACE_FLAG )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SUCCESSFUL_ACCESS_ACE_FLAG" );
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   Header.AceSize  = " ) << Header.AceSize  << TEXT( "\n" );
   dump_context << TEXT( "   Mask            = " ) << Mask            << TEXT( "\n" );
   dump_context << TEXT( "   SidStart        = " ) << SidStart        << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CAccessAllowedEntry::Empty( void )
{
   // ACE_HEADER
   Header.AceType  = 0;
   Header.AceFlags = 0;
   Header.AceSize  = 0;

   // ACE_MASK
   Mask            = 0;
   SidStart        = 0;
}

CAccessAllowedEntry& CAccessAllowedEntry::operator=( const CAccessAllowedEntry& source )
{
   Copy( source );
   return( *this );
}

CAccessControlEntryHeader::CAccessControlEntryHeader()
{
   Empty();
}

CAccessControlEntryHeader::CAccessControlEntryHeader( const CAccessControlEntryHeader& source )
{
   Empty();
   Copy( source );
}

CAccessControlEntryHeader::CAccessControlEntryHeader( const ACE_HEADER * source )
{
   Empty();
   Copy( source );
}

CAccessControlEntryHeader::~CAccessControlEntryHeader()
{
   Empty();
}

void CAccessControlEntryHeader::Copy( const CAccessControlEntryHeader& source )
{
   Copy( (const ACE_HEADER *) &source );
}

void CAccessControlEntryHeader::Copy( const ACE_HEADER * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      AceType  = source->AceType;
      AceFlags = source->AceFlags;
      AceSize  = source->AceSize;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CAccessControlEntryHeader::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CAccessControlEntryHeader at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   AceType  = " ) << AceType  << TEXT( " (" );

   switch( AceType )
   {
      case ACCESS_ALLOWED_ACE_TYPE:

         dump_context << TEXT( "ACCESS_ALLOWED_ACE_TYPE" );
         break;

      case ACCESS_DENIED_ACE_TYPE:

         dump_context << TEXT( "ACCESS_DENIED_ACE_TYPE" );
         break;

      case SYSTEM_AUDIT_ACE_TYPE:

         dump_context << TEXT( "SYSTEM_AUDIT_ACE_TYPE" );
         break;

      case SYSTEM_ALARM_ACE_TYPE:

         dump_context << TEXT( "SYSTEM_ALARM_ACE_TYPE" );
         break;
   }

   dump_context << TEXT( ")\n" );

   dump_context << TEXT( "   AceFlags = " ) << AceFlags << TEXT( " (" );

   CString temp_string;

   if ( AceFlags & CONTAINER_INHERIT_ACE )
   {
      temp_string = TEXT( "CONTAINER_INHERIT_ACE" );
   }

   if ( AceFlags & INHERIT_ONLY_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "INHERIT_ONLY_ACE" );
   }

   if ( AceFlags & NO_PROPAGATE_INHERIT_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "NO_PROPAGATE_INHERIT_ACE" );
   }

   if ( AceFlags & OBJECT_INHERIT_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "OBJECT_INHERIT_ACE" );
   }

   if ( AceFlags & FAILED_ACCESS_ACE_FLAG )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "FAILED_ACCESS_ACE_FLAG" );
   }

   if ( AceFlags & SUCCESSFUL_ACCESS_ACE_FLAG )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SUCCESSFUL_ACCESS_ACE_FLAG" );
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   AceSize  = " ) << AceSize     << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CAccessControlEntryHeader::Empty( void )
{
   AceType  = 0;
   AceFlags = 0;
   AceSize  = 0;
}

CAccessControlEntryHeader& CAccessControlEntryHeader::operator=( const CAccessControlEntryHeader& source )
{
   Copy( source );
   return( *this );
}

CAccessControlList::CAccessControlList()
{
   Empty();
}

CAccessControlList::CAccessControlList( const CAccessControlList& source )
{
   Empty();
   Copy( source );
}

CAccessControlList::CAccessControlList( const ACL * source )
{
   Empty();
   Copy( source );
}

CAccessControlList::~CAccessControlList()
{
   Empty();
}

void CAccessControlList::Copy( const CAccessControlList& source )
{
   Copy( (const ACL *) &source );
}

void CAccessControlList::Copy( const ACL * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      AclRevision = source->AclRevision;
      Sbz1        = source->Sbz1;
      AclSize     = source->AclSize;
      AceCount    = source->AceCount;
      Sbz2        = source->Sbz1;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CAccessControlList::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CAccessControlList at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   AclRevision = " ) << AclRevision << TEXT( "\n" );
   dump_context << TEXT( "   Sbz1        = " ) << Sbz1        << TEXT( "\n" );
   dump_context << TEXT( "   AclSize     = " ) << AclSize     << TEXT( "\n" );
   dump_context << TEXT( "   AceCount    = " ) << AceCount    << TEXT( "\n" );
   dump_context << TEXT( "   Sbz2        = " ) << Sbz2        << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CAccessControlList::Empty( void )
{
   AclRevision = ACL_REVISION;
   Sbz1        = 0;
   AclSize     = 0;
   AceCount    = 0;
   Sbz2        = 0;
}

CAccessControlList& CAccessControlList::operator=( const CAccessControlList& source )
{
   Copy( source );
   return( *this );
}

CAccessDeniedEntry::CAccessDeniedEntry()
{
   Empty();
}

CAccessDeniedEntry::CAccessDeniedEntry( const CAccessDeniedEntry& source )
{
   Empty();
   Copy( source );
}

CAccessDeniedEntry::CAccessDeniedEntry( const ACCESS_DENIED_ACE * source )
{
   Empty();
   Copy( source );
}

CAccessDeniedEntry::~CAccessDeniedEntry()
{
   Empty();
}

void CAccessDeniedEntry::Copy( const CAccessDeniedEntry& source )
{
   Copy( (const ACCESS_DENIED_ACE *) &source );
}

void CAccessDeniedEntry::Copy( const ACCESS_DENIED_ACE * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      Header.AceType  = source->Header.AceType;
      Header.AceFlags = source->Header.AceFlags;
      Header.AceSize  = source->Header.AceSize;
      Mask            = source->Mask;
      SidStart        = source->SidStart;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CAccessDeniedEntry::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CAccessDeniedEntry at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   Header.AceType  = " ) << Header.AceType  << TEXT( " (" );

   switch( Header.AceType )
   {
      case ACCESS_ALLOWED_ACE_TYPE:

         dump_context << TEXT( "ACCESS_ALLOWED_ACE_TYPE" );
         break;

      case ACCESS_DENIED_ACE_TYPE:

         dump_context << TEXT( "ACCESS_DENIED_ACE_TYPE" );
         break;

      case SYSTEM_AUDIT_ACE_TYPE:

         dump_context << TEXT( "SYSTEM_AUDIT_ACE_TYPE" );
         break;

      case SYSTEM_ALARM_ACE_TYPE:

         dump_context << TEXT( "SYSTEM_ALARM_ACE_TYPE" );
         break;
   }

   dump_context << TEXT( ")\n" );

   dump_context << TEXT( "   Header.AceFlags = " ) << Header.AceFlags << TEXT( " (" );

   CString temp_string;

   if ( Header.AceFlags & CONTAINER_INHERIT_ACE )
   {
      temp_string = TEXT( "CONTAINER_INHERIT_ACE" );
   }

   if ( Header.AceFlags & INHERIT_ONLY_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "INHERIT_ONLY_ACE" );
   }

   if ( Header.AceFlags & NO_PROPAGATE_INHERIT_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "NO_PROPAGATE_INHERIT_ACE" );
   }

   if ( Header.AceFlags & OBJECT_INHERIT_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "OBJECT_INHERIT_ACE" );
   }

   if ( Header.AceFlags & FAILED_ACCESS_ACE_FLAG )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "FAILED_ACCESS_ACE_FLAG" );
   }

   if ( Header.AceFlags & SUCCESSFUL_ACCESS_ACE_FLAG )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SUCCESSFUL_ACCESS_ACE_FLAG" );
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   Header.AceSize  = " ) << Header.AceSize  << TEXT( "\n" );
   dump_context << TEXT( "   Mask            = " ) << Mask            << TEXT( "\n" );
   dump_context << TEXT( "   SidStart        = " ) << SidStart        << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CAccessDeniedEntry::Empty( void )
{
   // ACE_HEADER
   Header.AceType  = 0;
   Header.AceFlags = 0;
   Header.AceSize  = 0;

   // ACE_MASK
   Mask            = 0;
   SidStart        = 0;
}

CAccessDeniedEntry& CAccessDeniedEntry::operator=( const CAccessDeniedEntry& source )
{
   Copy( source );
   return( *this );
}

CBitmapCoreHeader::CBitmapCoreHeader()
{
   Empty();
}

CBitmapCoreHeader::CBitmapCoreHeader( const CBitmapCoreHeader& source )
{
   Empty();
   Copy( source );
}

CBitmapCoreHeader::CBitmapCoreHeader( const tagBITMAPCOREHEADER * source )
{
   Empty();
   Copy( source );
}

CBitmapCoreHeader::~CBitmapCoreHeader()
{
   Empty();
}

void CBitmapCoreHeader::Copy( const CBitmapCoreHeader& source )
{
   Copy( (const CBitmapCoreHeader *) &source );
}

void CBitmapCoreHeader::Copy( const tagBITMAPCOREHEADER * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      bcSize     = source->bcSize;
      bcWidth    = source->bcWidth;
      bcHeight   = source->bcHeight;
      bcPlanes   = source->bcPlanes;
      bcBitCount = source->bcBitCount;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CBitmapCoreHeader::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CBitmapCoreHeader at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   bcSize     = " ) << bcSize     << TEXT( "\n" );
   dump_context << TEXT( "   bcWidth    = " ) << bcWidth    << TEXT( "\n" );
   dump_context << TEXT( "   bcHeight   = " ) << bcHeight   << TEXT( "\n" );
   dump_context << TEXT( "   bcPlanes   = " ) << bcPlanes   << TEXT( "\n" );
   dump_context << TEXT( "   bcBitCount = " ) << bcBitCount << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CBitmapCoreHeader::Empty( void )
{
   bcSize     = sizeof( tagBITMAPCOREHEADER );
   bcWidth    = 0;
   bcHeight   = 0;
   bcPlanes   = 0;
   bcBitCount = 0;
}

CBitmapCoreHeader& CBitmapCoreHeader::operator=( const CBitmapCoreHeader& source )
{
   Copy( source );
   return( *this );
}

CBitmapFileHeader::CBitmapFileHeader()
{
   Empty();
}

CBitmapFileHeader::CBitmapFileHeader( const CBitmapFileHeader& source )
{
   Empty();
   Copy( source );
}

CBitmapFileHeader::CBitmapFileHeader( const tagBITMAPFILEHEADER * source )
{
   Empty();
   Copy( source );
}

CBitmapFileHeader::~CBitmapFileHeader()
{
   Empty();
}

void CBitmapFileHeader::Copy( const CBitmapFileHeader& source )
{
   Copy( (const tagBITMAPFILEHEADER *) &source );
}

void CBitmapFileHeader::Copy( const tagBITMAPFILEHEADER * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      bfType      = source->bfType;
      bfSize      = source->bfSize;
      bfReserved1 = source->bfReserved1;
      bfReserved2 = source->bfReserved2;
      bfOffBits   = source->bfOffBits;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CBitmapFileHeader::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CBitmapFileHeader at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   bfType      = " ) << bfType      << TEXT( "\n" );
   dump_context << TEXT( "   bfSize      = " ) << bfSize      << TEXT( "\n" );
   dump_context << TEXT( "   bfReserved1 = " ) << bfReserved1 << TEXT( "\n" );
   dump_context << TEXT( "   bfReserved2 = " ) << bfReserved2 << TEXT( "\n" );
   dump_context << TEXT( "   bfOffBits   = " ) << bfOffBits   << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CBitmapFileHeader::Empty( void )
{
   bfType      = 'BM';
   bfSize      = 0;
   bfReserved1 = 0;
   bfReserved2 = 0;
   bfOffBits   = 0;
}

CBitmapFileHeader& CBitmapFileHeader::operator=( const CBitmapFileHeader& source )
{
   Copy( source );
   return( *this );
}

/*
** CBitmapInfoHeader
*/

CBitmapInfoHeader::CBitmapInfoHeader()
{
   Empty();
}

CBitmapInfoHeader::CBitmapInfoHeader( const CBitmapInfoHeader& source )
{
   Empty();
   Copy( source );
}

CBitmapInfoHeader::CBitmapInfoHeader( const tagBITMAPINFOHEADER * source )
{
   Empty();
   Copy( source );
}

CBitmapInfoHeader::~CBitmapInfoHeader()
{
   Empty();
}

void CBitmapInfoHeader::Copy( const CBitmapInfoHeader& source )
{
   Copy( (const tagBITMAPINFOHEADER * ) &source );
}

void CBitmapInfoHeader::Copy( const tagBITMAPINFOHEADER * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      biSize          = source->biSize;
      biWidth         = source->biWidth;
      biHeight        = source->biHeight;
      biPlanes        = source->biPlanes;
      biBitCount      = source->biBitCount;
      biCompression   = source->biCompression;
      biSizeImage     = source->biSizeImage;
      biXPelsPerMeter = source->biXPelsPerMeter;
      biYPelsPerMeter = source->biYPelsPerMeter;
      biClrUsed       = source->biClrUsed;
      biClrImportant  = source->biClrImportant;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CBitmapInfoHeader::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CBitmapInfoHeader at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   biSize          = " ) << biSize          << TEXT( "\n" );
   dump_context << TEXT( "   biWidth         = " ) << biWidth         << TEXT( "\n" );
   dump_context << TEXT( "   biHeight        = " ) << biHeight        << TEXT( "\n" );
   dump_context << TEXT( "   biPlanes        = " ) << biPlanes        << TEXT( "\n" );
   dump_context << TEXT( "   biBitCount      = " ) << biBitCount      << TEXT( "\n" );
   dump_context << TEXT( "   biCompression   = " ) << biCompression   << TEXT( "\n" );
   dump_context << TEXT( "   biSizeImage     = " ) << biSizeImage     << TEXT( "\n" );
   dump_context << TEXT( "   biXPelsPerMeter = " ) << biXPelsPerMeter << TEXT( "\n" );
   dump_context << TEXT( "   biYPelsPerMeter = " ) << biYPelsPerMeter << TEXT( "\n" );
   dump_context << TEXT( "   biClrUsed       = " ) << biClrUsed       << TEXT( "\n" );
   dump_context << TEXT( "   biClrImportant  = " ) << biClrImportant  << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CBitmapInfoHeader::Empty( void )
{
   biSize          = sizeof( tagBITMAPINFOHEADER );
   biWidth         = 0;
   biHeight        = 0;
   biPlanes        = 0;
   biBitCount      = 0;
   biCompression   = 0;
   biSizeImage     = 0;
   biXPelsPerMeter = 0;
   biYPelsPerMeter = 0;
   biClrUsed       = 0;
   biClrImportant  = 0;
}

CBitmapInfoHeader& CBitmapInfoHeader::operator=( const CBitmapInfoHeader& source )
{
   Copy( source );
   return( *this );
}

/*
** CColorAdjustment
*/

CColorAdjustment::CColorAdjustment()
{
   Empty();
}

CColorAdjustment::CColorAdjustment( const CColorAdjustment& source )
{
   Empty();
   Copy( source );
}

CColorAdjustment::CColorAdjustment( const tagCOLORADJUSTMENT * source )
{
   Empty();
   Copy( source );
}

CColorAdjustment::~CColorAdjustment()
{
   Empty();
}

void CColorAdjustment::Copy( const CColorAdjustment& source )
{
   Copy( (const tagCOLORADJUSTMENT *) &source );
}

void CColorAdjustment::Copy( const tagCOLORADJUSTMENT * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      caSize            = source->caSize;
      caFlags           = source->caFlags;
      caIlluminantIndex = source->caIlluminantIndex;
      caRedGamma        = source->caRedGamma;
      caGreenGamma      = source->caGreenGamma;
      caBlueGamma       = source->caBlueGamma;
      caReferenceBlack  = source->caReferenceBlack;
      caReferenceWhite  = source->caReferenceWhite;
      caContrast        = source->caContrast;
      caBrightness      = source->caBrightness;
      caColorfulness    = source->caColorfulness;
      caRedGreenTint    = source->caRedGreenTint;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CColorAdjustment::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CColorAdjustment at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   caSize =            " ) << caSize             << TEXT( "\n" );
   dump_context << TEXT( "   caFlags =           " ) << caFlags            << TEXT( "\n" );
   dump_context << TEXT( "   caIlluminantIndex = " ) << caIlluminantIndex  << TEXT( "\n" );
   dump_context << TEXT( "   caRedGamma =        " ) << caRedGamma         << TEXT( "\n" );
   dump_context << TEXT( "   caGreenGamma =      " ) << caGreenGamma       << TEXT( "\n" );
   dump_context << TEXT( "   caBlueGamma =       " ) << caBlueGamma        << TEXT( "\n" );
   dump_context << TEXT( "   caReferenceBlack =  " ) << caReferenceBlack   << TEXT( "\n" );
   dump_context << TEXT( "   caReferenceWhite =  " ) << caReferenceWhite   << TEXT( "\n" );
   dump_context << TEXT( "   caContrast =        " ) << caContrast         << TEXT( "\n" );
   dump_context << TEXT( "   caBrightness =      " ) << caBrightness       << TEXT( "\n" );
   dump_context << TEXT( "   caColorfulness =    " ) << caColorfulness     << TEXT( "\n" );
   dump_context << TEXT( "   caRedGreenTint =    " ) << caRedGreenTint     << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CColorAdjustment::Empty( void )
{
   caSize            = sizeof( tagCOLORADJUSTMENT );
   caFlags           = 0;
   caIlluminantIndex = 0;
   caRedGamma        = 0;
   caGreenGamma      = 0;
   caBlueGamma       = 0;
   caReferenceBlack  = 0;
   caReferenceWhite  = 0;
   caContrast        = 0;
   caBrightness      = 0;
   caColorfulness    = 0;
   caRedGreenTint    = 0;
}

CColorAdjustment& CColorAdjustment::operator=( const CColorAdjustment& source )
{
   Copy( source );
   return( *this );
}

/*
** CCommunicationsConfiguration
*/

CCommunicationsConfiguration::CCommunicationsConfiguration()
{
   Empty();
   dwSize        = sizeof( COMMCONFIG );
   dcb.DCBlength = sizeof( DCB );
}

CCommunicationsConfiguration::CCommunicationsConfiguration( const CCommunicationsConfiguration& source )
{
   Empty();
   dwSize        = sizeof( COMMCONFIG );
   dcb.DCBlength = sizeof( DCB );
   Copy( source );
}

CCommunicationsConfiguration::CCommunicationsConfiguration( const COMMCONFIG& source )
{
   Empty();
   dwSize        = sizeof( COMMCONFIG );
   dcb.DCBlength = sizeof( DCB );
   Copy( source );
}

CCommunicationsConfiguration::~CCommunicationsConfiguration()
{
   Empty();
}

void CCommunicationsConfiguration::Copy( const CCommunicationsConfiguration& source )
{
   ASSERT( &source != this );

   if ( &source == this )
   {
      return;
   }

   dwSize    = source.dwSize;
   wVersion  = source.wVersion;
   wReserved = source.wReserved;

   // The device control block

   dcb.DCBlength         = source.dcb.DCBlength;
   dcb.BaudRate          = source.dcb.BaudRate;
   dcb.fBinary           = source.dcb.fBinary;
   dcb.fParity           = source.dcb.fParity;
   dcb.fOutxCtsFlow      = source.dcb.fOutxCtsFlow;
   dcb.fOutxDsrFlow      = source.dcb.fOutxDsrFlow;
   dcb.fDtrControl       = source.dcb.fDtrControl;
   dcb.fDsrSensitivity   = source.dcb.fDsrSensitivity;
   dcb.fTXContinueOnXoff = source.dcb.fTXContinueOnXoff;
   dcb.fOutX             = source.dcb.fOutX;
   dcb.fInX              = source.dcb.fInX;
   dcb.fErrorChar        = source.dcb.fErrorChar;
   dcb.fNull             = source.dcb.fNull;
   dcb.fRtsControl       = source.dcb.fRtsControl;
   dcb.fAbortOnError     = source.dcb.fAbortOnError;
   dcb.fDummy2           = source.dcb.fDummy2;
   dcb.wReserved         = source.dcb.wReserved;
   dcb.XonLim            = source.dcb.XonLim;
   dcb.XoffLim           = source.dcb.XoffLim;
   dcb.ByteSize          = source.dcb.ByteSize;
   dcb.Parity            = source.dcb.Parity;
   dcb.StopBits          = source.dcb.StopBits;
   dcb.XonChar           = source.dcb.XonChar;
   dcb.XoffChar          = source.dcb.XoffChar;
   dcb.ErrorChar         = source.dcb.ErrorChar;
   dcb.EofChar           = source.dcb.EofChar;
   dcb.EvtChar           = source.dcb.EvtChar;
   dcb.wReserved1        = source.dcb.wReserved1;

   dwProviderSubType = source.dwProviderSubType;
   dwProviderOffset  = source.dwProviderOffset;
   dwProviderSize    = source.dwProviderSize;
}

void CCommunicationsConfiguration::Copy( const COMMCONFIG& source )
{
   dwSize    = source.dwSize;
   wVersion  = source.wVersion;
   wReserved = source.wReserved;

   // The device control block

   dcb.DCBlength         = source.dcb.DCBlength;
   dcb.BaudRate          = source.dcb.BaudRate;
   dcb.fBinary           = source.dcb.fBinary;
   dcb.fParity           = source.dcb.fParity;
   dcb.fOutxCtsFlow      = source.dcb.fOutxCtsFlow;
   dcb.fOutxDsrFlow      = source.dcb.fOutxDsrFlow;
   dcb.fDtrControl       = source.dcb.fDtrControl;
   dcb.fDsrSensitivity   = source.dcb.fDsrSensitivity;
   dcb.fTXContinueOnXoff = source.dcb.fTXContinueOnXoff;
   dcb.fOutX             = source.dcb.fOutX;
   dcb.fInX              = source.dcb.fInX;
   dcb.fErrorChar        = source.dcb.fErrorChar;
   dcb.fNull             = source.dcb.fNull;
   dcb.fRtsControl       = source.dcb.fRtsControl;
   dcb.fAbortOnError     = source.dcb.fAbortOnError;
   dcb.fDummy2           = source.dcb.fDummy2;
   dcb.wReserved         = source.dcb.wReserved;
   dcb.XonLim            = source.dcb.XonLim;
   dcb.XoffLim           = source.dcb.XoffLim;
   dcb.ByteSize          = source.dcb.ByteSize;
   dcb.Parity            = source.dcb.Parity;
   dcb.StopBits          = source.dcb.StopBits;
   dcb.XonChar           = source.dcb.XonChar;
   dcb.XoffChar          = source.dcb.XoffChar;
   dcb.ErrorChar         = source.dcb.ErrorChar;
   dcb.EofChar           = source.dcb.EofChar;
   dcb.EvtChar           = source.dcb.EvtChar;
   dcb.wReserved1        = source.dcb.wReserved1;

   dwProviderSubType = source.dwProviderSubType;
   dwProviderOffset  = source.dwProviderOffset;
   dwProviderSize    = source.dwProviderSize;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CCommunicationsConfiguration::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CCommunicationsConfiguration at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   dwSize is            " ) << dwSize            << TEXT( "\n" );
   dump_context << TEXT( "   wVersion is          " ) << wVersion          << TEXT( "\n" );
   dump_context << TEXT( "   wReserved is         " ) << wReserved         << TEXT( "\n" );
   dump_context << TEXT( "   dwProviderSubType is " ) << dwProviderSubType << TEXT( " " );

   switch( dwProviderSubType )
   {
      case PST_FAX:

         dump_context << TEXT( "(PST_FAX)\n" );
         break;

      case PST_LAT:

         dump_context << TEXT( "(PST_LAT)\n" );
         break;

      case PST_MODEM:

         dump_context << TEXT( "(PST_MODEM)\n" );
         break;

      case PST_NETWORK_BRIDGE:

         dump_context << TEXT( "(PST_NETWORK_BRIDGE)\n" );
         break;

      case PST_PARALLELPORT:

         dump_context << TEXT( "(PST_PARALLELPORT)\n" );
         break;

      case PST_RS232:

         dump_context << TEXT( "(PST_RS232)\n" );
         break;

      case PST_RS422:

         dump_context << TEXT( "(PST_RS422)\n" );
         break;

      case PST_RS423:

         dump_context << TEXT( "(PST_RS423)\n" );
         break;

      case PST_RS449:

         dump_context << TEXT( "(PST_RS449)\n" );
         break;

      case PST_SCANNER:

         dump_context << TEXT( "(PST_SCANNER)\n" );
         break;

      case PST_TCPIP_TELNET:

         dump_context << TEXT( "(PST_TCPIP_TELNET)\n" );
         break;

      case PST_UNSPECIFIED:

         dump_context << TEXT( "(PST_UNSPECIFIED)\n" );
         break;

      case PST_X25:

         dump_context << TEXT( "(PST_X25)\n" );
         break;

      default:

         CString debug_string;

         debug_string.Format( TEXT( "(Unknown value %lu)\n" ), dwProviderSubType );
         dump_context << debug_string;
         break;
   }

   dump_context << TEXT( "   dwProviderOffset is  " ) << dwProviderOffset  << TEXT( "\n" );
   dump_context << TEXT( "   dwProviderSize is    " ) << dwProviderSize    << TEXT( "\n" );

   CDeviceControlBlock device_control_block( dcb );

   dump_context << TEXT( "   dcb is " );

   device_control_block.Dump( dump_context );

   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CCommunicationsConfiguration::Empty( void )
{
   dwSize              = 0;
   wVersion            = 0;
   wReserved           = 0;
   dwProviderSubType   = 0;
   dwProviderOffset    = 0;
   dwProviderSize      = 0;
   wcProviderData[ 0 ] = 0;
   ZeroMemory( &dcb, sizeof( dcb ) );
}

CCommunicationsConfiguration& CCommunicationsConfiguration::operator=( const CCommunicationsConfiguration& source )
{
   Copy( source );
   return( *this );
}

CCommunicationsConfiguration& CCommunicationsConfiguration::operator=( const COMMCONFIG& source )
{
   Copy( source );
   return( *this );
}

/*
** CCommunicationProperties
*/

CCommunicationProperties::CCommunicationProperties()
{
   Empty();
}

CCommunicationProperties::CCommunicationProperties( const CCommunicationProperties& source )
{
   Copy( source );
}

CCommunicationProperties::CCommunicationProperties( const _COMMPROP& source )
{
   Copy( source );
}

CCommunicationProperties::~CCommunicationProperties()
{
   Empty();
}

void CCommunicationProperties::ConvertBaudRateToString( const DWORD baud_rate, CString& human_readable_string ) const
{
   switch( baud_rate )
   {
      case BAUD_075:

         human_readable_string = TEXT( "75 bps" );
         break;

      case BAUD_110:

         human_readable_string = TEXT( "110 bps" );
         break;

      case BAUD_134_5:

         human_readable_string = TEXT( "134.5 bps" );
         break;

      case BAUD_150:

         human_readable_string = TEXT( "150 bps" );
         break;

      case BAUD_300:

         human_readable_string = TEXT( "300 bps" );
         break;

      case BAUD_600:

         human_readable_string = TEXT( "600 bps" );
         break;

      case BAUD_1200:

         human_readable_string = TEXT( "1200 bps" );
         break;

      case BAUD_1800:

         human_readable_string = TEXT( "1800 bps" );
         break;

      case BAUD_2400:

         human_readable_string = TEXT( "2400 bps" );
         break;

      case BAUD_4800:

         human_readable_string = TEXT( "4800 bps" );
         break;

      case BAUD_7200:

         human_readable_string = TEXT( "7200 bps" );
         break;

      case BAUD_9600:

         human_readable_string = TEXT( "9600 bps" );
         break;

      case BAUD_14400:

         human_readable_string = TEXT( "14400 bps" );
         break;

      case BAUD_19200:

         human_readable_string = TEXT( "19200 bps" );
         break;

      case BAUD_38400:

         human_readable_string = TEXT( "38400 bps" );
         break;

      case BAUD_56K:

         human_readable_string = TEXT( "56 Kbps" );
         break;

      case BAUD_128K:

         human_readable_string = TEXT( "128 Kbps" );
         break;

      case BAUD_115200:

         human_readable_string = TEXT( "115200 bps" );
         break;

      case BAUD_57600:

         human_readable_string = TEXT( "57600 bps" );
         break;

      case BAUD_USER:

         human_readable_string = TEXT( "Programmable baud rates available" );
         break;

      default:

         human_readable_string.Format( TEXT( "Unknown constant %lu" ), baud_rate );
         break;
   }
}

void CCommunicationProperties::ConvertBaudRateListToString( const DWORD baud_rate, CString& human_readable_string ) const
{
   human_readable_string.Empty();

   if ( baud_rate & BAUD_075 )
   {
      human_readable_string = TEXT( "75 bps" );
   }

   if ( baud_rate & BAUD_110 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "110 bps" );
   }

   if ( baud_rate & BAUD_134_5 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "134.5 bps" );
   }

   if ( baud_rate & BAUD_150 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "150 bps" );
   }

   if ( baud_rate & BAUD_300 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "300 bps" );
   }

   if ( baud_rate & BAUD_600 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "600 bps" );
   }

   if ( baud_rate & BAUD_1200 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "1200 bps" );
   }

   if ( baud_rate & BAUD_1800 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "1800 bps" );
   }

   if ( baud_rate & BAUD_2400 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "2400 bps" );
   }

   if ( baud_rate & BAUD_4800 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "4800 bps" );
   }

   if ( baud_rate & BAUD_7200 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "7200 bps" );
   }

   if ( baud_rate & BAUD_9600 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "9600 bps" );
   }

   if ( baud_rate & BAUD_14400 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "14400 bps" );
   }

   if ( baud_rate & BAUD_19200 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "19200 bps" );
   }

   if ( baud_rate & BAUD_38400 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "38400 bps" );
   }

   if ( baud_rate & BAUD_56K )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "56 Kbps" );
   }

   if ( baud_rate & BAUD_128K )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "128 Kbps" );
   }

   if ( baud_rate & BAUD_115200 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "115200 bps" );
   }

   if ( baud_rate & BAUD_57600 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "57600 bps" );
   }

   if ( baud_rate & BAUD_USER )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string = TEXT( "Programmable baud rates available" );
   }
}

void CCommunicationProperties::ConvertDataBitsToString( const DWORD data_bits, CString& human_readable_string ) const
{
   human_readable_string.Empty();

   if ( data_bits & DATABITS_5 )
   {
      human_readable_string = TEXT( "5 data bits" );
   }

   if ( data_bits & DATABITS_6 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "6 data bits" );
   }

   if ( data_bits & DATABITS_7 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "7 data bits" );
   }

   if ( data_bits & DATABITS_8 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "8 data bits" );
   }

   if ( data_bits & DATABITS_16 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "16 data bits" );
   }

   if ( data_bits & DATABITS_16X )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Special wide path through serial hardware" );
   }
}

void CCommunicationProperties::ConvertProviderCapabilitiesToString( const DWORD capabilities, CString& human_readable_string ) const
{
   human_readable_string.Empty();

   if ( capabilities & PCF_DTRDSR )
   {
      human_readable_string = TEXT( "DTR/DSR supported" );
   }

   if ( capabilities & PCF_RTSCTS )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "RTS/CTS supported" );
   }

   if ( capabilities & PCF_RLSD )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "RLSD supported" );
   }

   if ( capabilities & PCF_PARITY_CHECK )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Parity checking supported" );
   }

   if ( capabilities & PCF_XONXOFF )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "XON/XOFF supported" );
   }

   if ( capabilities & PCF_SETXCHAR )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Settable XON/XOFF supported" );
   }

   if ( capabilities & PCF_TOTALTIMEOUTS )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Total (elapsed) time-outs supported" );
   }

   if ( capabilities & PCF_INTTIMEOUTS )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Interval time-outs supported" );
   }

   if ( capabilities & PCF_SPECIALCHARS )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Special character support provided" );
   }

   if ( capabilities & PCF_16BITMODE )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Special 16-bit mode supported" );
   }
}

void CCommunicationProperties::ConvertProviderSubtypeToString( const DWORD type, CString& human_readable_string ) const
{
   switch( type )
   {
      case PST_UNSPECIFIED:

         human_readable_string = TEXT( "Unspecified" );
         break;

      case PST_RS232:

         human_readable_string = TEXT( "RS-232 serial port" );
         break;

      case PST_PARALLELPORT:

         human_readable_string = TEXT( "Parallel port" );
         break;

      case PST_RS422:

         human_readable_string = TEXT( "RS-422 port" );
         break;

      case PST_RS423:

         human_readable_string = TEXT( "RS-423 port" );
         break;

      case PST_RS449:

         human_readable_string = TEXT( "RS-449 port" );
         break;

      case PST_MODEM:

         human_readable_string = TEXT( "Modem device" );
         break;

      case PST_FAX:

         human_readable_string = TEXT( "FAX device" );
         break;

      case PST_SCANNER:

         human_readable_string = TEXT( "Scanner device" );
         break;

      case PST_NETWORK_BRIDGE:

         human_readable_string = TEXT( "Unspecified network bridge" );
         break;

      case PST_LAT:

         human_readable_string = TEXT( "LAT protocol" );
         break;

      case PST_TCPIP_TELNET:

         human_readable_string = TEXT( "TCP/IP Telnet protocol" );
         break;

      case PST_X25:

         human_readable_string = TEXT( "X.25 standards" );
         break;

      default:

         human_readable_string.Format( TEXT( "Unknown constant %lu" ), type );
         break;
   }
}

void CCommunicationProperties::ConvertSettableParametersToString( const DWORD parameters, CString& human_readable_string ) const
{
   human_readable_string.Empty();

   if ( parameters & SP_PARITY )
   {
      human_readable_string = TEXT( "Parity" );
   }

   if ( parameters & SP_BAUD )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Baud rate" );
   }

   if ( parameters & SP_DATABITS )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Data bits" );
   }

   if ( parameters & SP_STOPBITS )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Stop bits" );
   }

   if ( parameters & SP_HANDSHAKING )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Handshaking (flow control)" );
   }

   if ( parameters & SP_PARITY_CHECK )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Parity checking" );
   }

   if ( parameters & SP_RLSD )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Receive-line-signal-detect (RLSD)" );
   }
}

void CCommunicationProperties::ConvertStopParityToString( const DWORD stop_parity, CString& human_readable_string ) const
{
   human_readable_string.Empty();

   if ( stop_parity & STOPBITS_10 )
   {
      human_readable_string = TEXT( "1 stop bit" );
   }

   if ( stop_parity & STOPBITS_15 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "1.5 stop bits" );
   }

   if ( stop_parity & STOPBITS_20 )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "2 stop bits" );
   }

   if ( stop_parity & PARITY_NONE )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "No parity" );
   }

   if ( stop_parity & PARITY_ODD )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Odd parity" );
   }

   if ( stop_parity & PARITY_EVEN )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Even parity" );
   }

   if ( stop_parity & PARITY_MARK )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Mark parity" );
   }

   if ( stop_parity & PARITY_SPACE )
   {
      if ( human_readable_string.GetLength() > 0 )
      {
         human_readable_string += TEXT( ", " );
      }

      human_readable_string += TEXT( "Space parity" );
   }
}

void CCommunicationProperties::Copy( const CCommunicationProperties& source )
{
   ASSERT( &source != this );

   if ( &source == this )
   {
      return;
   }

   wPacketLength       = source.wPacketLength;
   wPacketVersion      = source.wPacketVersion;
   dwServiceMask       = source.dwServiceMask;
   dwReserved1         = source.dwReserved1;
   dwMaxTxQueue        = source.dwMaxTxQueue;
   dwMaxRxQueue        = source.dwMaxRxQueue;
   dwMaxBaud           = source.dwMaxBaud;
   dwProvSubType       = source.dwProvSubType;
   dwProvCapabilities  = source.dwProvCapabilities;
   dwSettableParams    = source.dwSettableParams;
   dwSettableBaud      = source.dwSettableBaud;
   wSettableData       = source.wSettableData;
   wSettableStopParity = source.wSettableStopParity;
   dwCurrentTxQueue    = source.dwCurrentTxQueue;
   dwCurrentRxQueue    = source.dwCurrentRxQueue;
   dwProvSpec1         = source.dwProvSpec1;
   dwProvSpec2         = source.dwProvSpec2;
   wcProvChar[ 0 ]     = source.wcProvChar[ 0 ];
}

void CCommunicationProperties::Copy( const _COMMPROP& source )
{
   wPacketLength       = source.wPacketLength;
   wPacketVersion      = source.wPacketVersion;
   dwServiceMask       = source.dwServiceMask;
   dwReserved1         = source.dwReserved1;
   dwMaxTxQueue        = source.dwMaxTxQueue;
   dwMaxRxQueue        = source.dwMaxRxQueue;
   dwMaxBaud           = source.dwMaxBaud;
   dwProvSubType       = source.dwProvSubType;
   dwProvCapabilities  = source.dwProvCapabilities;
   dwSettableParams    = source.dwSettableParams;
   dwSettableBaud      = source.dwSettableBaud;
   wSettableData       = source.wSettableData;
   wSettableStopParity = source.wSettableStopParity;
   dwCurrentTxQueue    = source.dwCurrentTxQueue;
   dwCurrentRxQueue    = source.dwCurrentRxQueue;
   dwProvSpec1         = source.dwProvSpec1;
   dwProvSpec2         = source.dwProvSpec2;
   wcProvChar[ 0 ]     = source.wcProvChar[ 0 ];
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CCommunicationProperties::Dump( CDumpContext& dump_context ) const
{
   CString temp_string;

   dump_context << TEXT( " a CCommunicationProperties at " ) << (VOID *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   wPacketLength       = " ) << wPacketLength       << TEXT( "\n" );
   dump_context << TEXT( "   wPacketVersion      = " ) << wPacketVersion      << TEXT( "\n" );
   dump_context << TEXT( "   dwServiceMask       = " ) << dwServiceMask       << TEXT( "\n" );
   dump_context << TEXT( "   dwReserved1         = " ) << dwReserved1         << TEXT( "\n" );
   dump_context << TEXT( "   dwMaxTxQueue        = " ) << dwMaxTxQueue        << TEXT( "\n" );
   dump_context << TEXT( "   dwMaxRxQueue        = " ) << dwMaxRxQueue        << TEXT( "\n" );
   ConvertBaudRateToString( dwMaxBaud, temp_string );
   dump_context << TEXT( "   dwMaxBaud           = " ) << dwMaxBaud << TEXT( " (" ) << temp_string << TEXT( ")\n" );
   ConvertProviderSubtypeToString( dwProvSubType, temp_string );
   dump_context << TEXT( "   dwProvSubType       = " ) << dwProvSubType << TEXT( " (" ) << temp_string << TEXT( ")\n" );
   ConvertProviderCapabilitiesToString( dwProvCapabilities, temp_string );
   dump_context << TEXT( "   dwProvCapabilities  = " ) << dwProvCapabilities << TEXT( " (" ) << temp_string << TEXT( ")\n" );
   ConvertSettableParametersToString( dwSettableParams, temp_string );
   dump_context << TEXT( "   dwSettableParams    = " ) << dwSettableParams << TEXT( " (" ) << temp_string << TEXT( ")\n" );
   ConvertBaudRateListToString( dwSettableBaud, temp_string );
   dump_context << TEXT( "   dwSettableBaud      = " ) << dwSettableBaud << TEXT( " (" ) << temp_string << TEXT( ")\n" );
   ConvertDataBitsToString( wSettableData, temp_string );
   dump_context << TEXT( "   wSettableData       = " ) << wSettableData << TEXT( " (" ) << temp_string << TEXT( ")\n" );
   ConvertStopParityToString( wSettableStopParity, temp_string );
   dump_context << TEXT( "   wSettableStopParity = " ) << wSettableStopParity << TEXT( " (" ) << temp_string << TEXT( ")\n" );
   dump_context << TEXT( "   dwCurrentTxQueue    = " ) << dwCurrentTxQueue    << TEXT( "\n" );
   dump_context << TEXT( "   dwCurrentRxQueue    = " ) << dwCurrentRxQueue    << TEXT( "\n" );
   dump_context << TEXT( "   dwProvSpec1         = " ) << dwProvSpec1         << TEXT( "\n" );
   dump_context << TEXT( "   dwProvSpec2         = " ) << dwProvSpec2         << TEXT( "\n" );
   dump_context << TEXT( "   wcProvChar          = " ) << wcProvChar          << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CCommunicationProperties::Empty( void )
{
   wPacketLength       = 0;
   wPacketVersion      = 0;
   dwServiceMask       = 0;
   dwReserved1         = 0;
   dwMaxTxQueue        = 0;
   dwMaxRxQueue        = 0;
   dwMaxBaud           = 0;
   dwProvSubType       = 0;
   dwProvCapabilities  = 0;
   dwSettableParams    = 0;
   dwSettableBaud      = 0;
   wSettableData       = 0;
   wSettableStopParity = 0;
   dwCurrentTxQueue    = 0;
   dwCurrentRxQueue    = 0;
   dwProvSpec1         = 0;
   dwProvSpec2         = 0;
   wcProvChar[ 0 ]     = 0;
}

CCommunicationProperties& CCommunicationProperties::operator=( const CCommunicationProperties& source )
{
   Copy( source );
   return( *this );
}

CCommunicationProperties& CCommunicationProperties::operator=( const _COMMPROP& source )
{
   Copy( source );
   return( *this );
}

/*
** CMemoryStatus
*/

CMemoryStatus::CMemoryStatus()
{
   Empty();
}

CMemoryStatus::CMemoryStatus( const CMemoryStatus& source )
{
   Empty();
   Copy( source );
}

CMemoryStatus::CMemoryStatus( const MEMORYSTATUS * source )
{
   Empty();
   Copy( source );
}

CMemoryStatus::~CMemoryStatus()
{
   Empty();
}

void CMemoryStatus::Copy( const CMemoryStatus& source )
{
   Copy( (const MEMORYSTATUS *) &source );
}

void CMemoryStatus::Copy( const MEMORYSTATUS * source )
{
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      dwLength        = source->dwLength;
      dwMemoryLoad    = source->dwMemoryLoad;
      dwTotalPhys     = source->dwTotalPhys;
      dwAvailPhys     = source->dwAvailPhys;
      dwTotalPageFile = source->dwTotalPageFile;
      dwAvailPageFile = source->dwAvailPageFile;
      dwTotalVirtual  = source->dwTotalVirtual;
      dwAvailVirtual  = source->dwAvailVirtual;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMemoryStatus::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CMemoryStatus at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   dwLength        = " ) << dwLength        << TEXT( "\n" );
   dump_context << TEXT( "   dwMemoryLoad    = " ) << dwMemoryLoad    << TEXT( "\n" );
   dump_context << TEXT( "   dwTotalPhys     = " ) << dwTotalPhys     << TEXT( "\n" );
   dump_context << TEXT( "   dwAvailPhys     = " ) << dwAvailPhys     << TEXT( "\n" );
   dump_context << TEXT( "   dwTotalPageFile = " ) << dwTotalPageFile << TEXT( "\n" );
   dump_context << TEXT( "   dwAvailPageFile = " ) << dwAvailPageFile << TEXT( "\n" );
   dump_context << TEXT( "   dwTotalVirtual  = " ) << dwTotalVirtual  << TEXT( "\n" );
   dump_context << TEXT( "   dwAvailVirtual  = " ) << dwAvailVirtual  << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMemoryStatus::Empty( void )
{
   dwLength        = sizeof( MEMORYSTATUS );
   dwMemoryLoad    = 0;
   dwTotalPhys     = 0;
   dwAvailPhys     = 0;
   dwTotalPageFile = 0;
   dwAvailPageFile = 0;
   dwTotalVirtual  = 0;
   dwAvailVirtual  = 0;
}

CMemoryStatus& CMemoryStatus::operator=( const CMemoryStatus& source )
{
   Copy( source );
   return( *this );
}

/*
** COFStruct
*/

COFStruct::COFStruct()
{
   Empty();
}

COFStruct::COFStruct( const COFStruct& source )
{
   Empty();
   Copy( source );
}

COFStruct::COFStruct( const _OFSTRUCT * source )
{
   Empty();
   Copy( source );
}

COFStruct::~COFStruct()
{
   Empty();
}

void COFStruct::Copy( const COFStruct& source )
{
   Copy( (const _OFSTRUCT *) &source );
}

void COFStruct::Copy( const _OFSTRUCT * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      cBytes     = source->cBytes;
      fFixedDisk = source->fFixedDisk;
      nErrCode   = source->nErrCode;
      Reserved1  = source->Reserved1;
      Reserved2  = source->Reserved2;
      ::strcpy( szPathName, source->szPathName ); // Not a UNICODE string
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void COFStruct::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a COFStruct at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   cBytes     = "   ) << cBytes     << TEXT( "\n" );
   dump_context << TEXT( "   fFixedDisk = "   ) << fFixedDisk << TEXT( "\n" );
   dump_context << TEXT( "   nErrCode   = "   ) << nErrCode   << TEXT( "\n" );
   dump_context << TEXT( "   Reserved1  = "   ) << Reserved1  << TEXT( "\n" );
   dump_context << TEXT( "   Reserved2  = "   ) << Reserved2  << TEXT( "\n" );
   dump_context << TEXT( "   szPathName = \"" ) << szPathName << TEXT( "\"\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void COFStruct::Empty( void )
{
   cBytes     = sizeof( _OFSTRUCT );
   fFixedDisk = 0;
   nErrCode   = 0;
   Reserved1  = 0;
   Reserved2  = 0;

   int index = 0;

   while( index < OFS_MAXPATHNAME )
   {
      szPathName[ index ] = 0;
      index++;
   }
}

COFStruct& COFStruct::operator=( const COFStruct& source )
{
   Copy( source );
   return( *this );
}

/*
** COutlineTextMetricA
*/

COutlineTextMetricA::COutlineTextMetricA()
{
   Empty();
}

COutlineTextMetricA::COutlineTextMetricA( const COutlineTextMetricA& source )
{
   Empty();
   Copy( source );
}

COutlineTextMetricA::COutlineTextMetricA( const _OUTLINETEXTMETRICA * source )
{
   Empty();
   Copy( source );
}

COutlineTextMetricA::~COutlineTextMetricA()
{
   Empty();
}

void COutlineTextMetricA::Copy( const COutlineTextMetricA& source )
{
   Copy( (const _OUTLINETEXTMETRICA *) &source );
}

void COutlineTextMetricA::Copy( const _OUTLINETEXTMETRICA * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      otmSize = source->otmSize;

      // TEXTMETRICA
      otmTextMetrics.tmHeight           = source->otmTextMetrics.tmHeight;
      otmTextMetrics.tmAscent           = source->otmTextMetrics.tmAscent;
      otmTextMetrics.tmDescent          = source->otmTextMetrics.tmDescent;
      otmTextMetrics.tmInternalLeading  = source->otmTextMetrics.tmInternalLeading;
      otmTextMetrics.tmExternalLeading  = source->otmTextMetrics.tmExternalLeading;
      otmTextMetrics.tmAveCharWidth     = source->otmTextMetrics.tmAveCharWidth;
      otmTextMetrics.tmMaxCharWidth     = source->otmTextMetrics.tmMaxCharWidth;
      otmTextMetrics.tmWeight           = source->otmTextMetrics.tmWeight;
      otmTextMetrics.tmOverhang         = source->otmTextMetrics.tmOverhang;
      otmTextMetrics.tmDigitizedAspectX = source->otmTextMetrics.tmDigitizedAspectX;
      otmTextMetrics.tmDigitizedAspectY = source->otmTextMetrics.tmDigitizedAspectY;
      otmTextMetrics.tmFirstChar        = source->otmTextMetrics.tmFirstChar;
      otmTextMetrics.tmLastChar         = source->otmTextMetrics.tmLastChar;
      otmTextMetrics.tmDefaultChar      = source->otmTextMetrics.tmDefaultChar;
      otmTextMetrics.tmBreakChar        = source->otmTextMetrics.tmBreakChar;
      otmTextMetrics.tmItalic           = source->otmTextMetrics.tmItalic;
      otmTextMetrics.tmUnderlined       = source->otmTextMetrics.tmUnderlined;
      otmTextMetrics.tmStruckOut        = source->otmTextMetrics.tmStruckOut;
      otmTextMetrics.tmPitchAndFamily   = source->otmTextMetrics.tmPitchAndFamily;
      otmTextMetrics.tmCharSet          = source->otmTextMetrics.tmCharSet;
   
      otmFiller = source->otmFiller;
   
      // PANOSE
      otmPanoseNumber.bFamilyType      = source->otmPanoseNumber.bFamilyType;
      otmPanoseNumber.bSerifStyle      = source->otmPanoseNumber.bSerifStyle;
      otmPanoseNumber.bWeight          = source->otmPanoseNumber.bWeight;
      otmPanoseNumber.bProportion      = source->otmPanoseNumber.bProportion;
      otmPanoseNumber.bContrast        = source->otmPanoseNumber.bContrast;
      otmPanoseNumber.bStrokeVariation = source->otmPanoseNumber.bStrokeVariation;
      otmPanoseNumber.bArmStyle        = source->otmPanoseNumber.bArmStyle;
      otmPanoseNumber.bLetterform      = source->otmPanoseNumber.bLetterform;
      otmPanoseNumber.bMidline         = source->otmPanoseNumber.bMidline;
      otmPanoseNumber.bXHeight         = source->otmPanoseNumber.bXHeight;

      otmfsSelection    = source->otmfsSelection;
      otmfsType         = source->otmfsType;
      otmsCharSlopeRise = source->otmsCharSlopeRise;
      otmsCharSlopeRun  = source->otmsCharSlopeRun;
      otmItalicAngle    = source->otmItalicAngle;
      otmEMSquare       = source->otmEMSquare;
      otmAscent         = source->otmAscent;
      otmDescent        = source->otmDescent;
      otmLineGap        = source->otmLineGap;
      otmsCapEmHeight   = source->otmsCapEmHeight;
      otmsXHeight       = source->otmsXHeight;
   
      // RECT
      otmrcFontBox.left   = source->otmrcFontBox.left;
      otmrcFontBox.top    = source->otmrcFontBox.top;
      otmrcFontBox.right  = source->otmrcFontBox.right;
      otmrcFontBox.bottom = source->otmrcFontBox.bottom;

      otmMacAscent     = source->otmMacAscent;
      otmMacDescent    = source->otmMacDescent;
      otmMacLineGap    = source->otmMacLineGap;
      otmusMinimumPPEM = source->otmusMinimumPPEM;

      // POINT
      otmptSubscriptSize.x     = source->otmptSubscriptSize.x;
      otmptSubscriptSize.y     = source->otmptSubscriptSize.y;
      otmptSubscriptOffset.x   = source->otmptSubscriptOffset.x;
      otmptSubscriptOffset.y   = source->otmptSubscriptOffset.y;
      otmptSuperscriptSize.x   = source->otmptSuperscriptSize.x;
      otmptSuperscriptSize.y   = source->otmptSuperscriptSize.y;
      otmptSuperscriptOffset.x = source->otmptSuperscriptOffset.x;
      otmptSuperscriptOffset.y = source->otmptSuperscriptOffset.y;

      otmsStrikeoutSize      = source->otmsStrikeoutSize;
      otmsStrikeoutPosition  = source->otmsStrikeoutPosition;
      otmsUnderscoreSize     = source->otmsUnderscoreSize;
      otmsUnderscorePosition = source->otmsUnderscorePosition;
      otmpFamilyName         = source->otmpFamilyName;
      otmpFaceName           = source->otmpFaceName;
      otmpStyleName          = source->otmpStyleName;
      otmpFullName           = source->otmpFullName;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void COutlineTextMetricA::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a COutlineTextMetricA at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   otmSize                           = " ) << otmSize                           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmHeight           = " ) << otmTextMetrics.tmHeight           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmAscent           = " ) << otmTextMetrics.tmAscent           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmDescent          = " ) << otmTextMetrics.tmDescent          << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmInternalLeading  = " ) << otmTextMetrics.tmInternalLeading  << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmExternalLeading  = " ) << otmTextMetrics.tmExternalLeading  << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmAveCharWidth     = " ) << otmTextMetrics.tmAveCharWidth     << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmMaxCharWidth     = " ) << otmTextMetrics.tmMaxCharWidth     << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmWeight           = " ) << otmTextMetrics.tmWeight           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmOverhang         = " ) << otmTextMetrics.tmOverhang         << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmDigitizedAspectX = " ) << otmTextMetrics.tmDigitizedAspectX << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmDigitizedAspectY = " ) << otmTextMetrics.tmDigitizedAspectY << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmFirstChar        = " ) << otmTextMetrics.tmFirstChar        << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmLastChar         = " ) << otmTextMetrics.tmLastChar         << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmDefaultChar      = " ) << otmTextMetrics.tmDefaultChar      << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmBreakChar        = " ) << otmTextMetrics.tmBreakChar        << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmItalic           = " ) << otmTextMetrics.tmItalic           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmUnderlined       = " ) << otmTextMetrics.tmUnderlined       << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmStruckOut        = " ) << otmTextMetrics.tmStruckOut        << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmPitchAndFamily   = " ) << otmTextMetrics.tmPitchAndFamily   << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmCharSet          = " ) << otmTextMetrics.tmCharSet          << TEXT( "\n" );
   dump_context << TEXT( "   otmFiller                         = " ) << otmFiller                         << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bFamilyType       = " ) << otmPanoseNumber.bFamilyType       << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bSerifStyle       = " ) << otmPanoseNumber.bSerifStyle       << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bWeight           = " ) << otmPanoseNumber.bWeight           << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bProportion       = " ) << otmPanoseNumber.bProportion       << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bContrast         = " ) << otmPanoseNumber.bContrast         << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bStrokeVariation  = " ) << otmPanoseNumber.bStrokeVariation  << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bArmStyle         = " ) << otmPanoseNumber.bArmStyle         << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bLetterform       = " ) << otmPanoseNumber.bLetterform       << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bMidline          = " ) << otmPanoseNumber.bMidline          << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bXHeight          = " ) << otmPanoseNumber.bXHeight          << TEXT( "\n" );
   dump_context << TEXT( "   otmfsSelection                    = " ) << otmfsSelection                    << TEXT( "\n" );
   dump_context << TEXT( "   otmfsType                         = " ) << otmfsType                         << TEXT( "\n" );
   dump_context << TEXT( "   otmsCharSlopeRise                 = " ) << otmsCharSlopeRise                 << TEXT( "\n" );
   dump_context << TEXT( "   otmsCharSlopeRun                  = " ) << otmsCharSlopeRun                  << TEXT( "\n" );
   dump_context << TEXT( "   otmItalicAngle                    = " ) << otmItalicAngle                    << TEXT( "\n" );
   dump_context << TEXT( "   otmEMSquare                       = " ) << otmEMSquare                       << TEXT( "\n" );
   dump_context << TEXT( "   otmAscent                         = " ) << otmAscent                         << TEXT( "\n" );
   dump_context << TEXT( "   otmDescent                        = " ) << otmDescent                        << TEXT( "\n" );
   dump_context << TEXT( "   otmLineGap                        = " ) << otmLineGap                        << TEXT( "\n" );
   dump_context << TEXT( "   otmsCapEmHeight                   = " ) << otmsCapEmHeight                   << TEXT( "\n" );
   dump_context << TEXT( "   otmsXHeight                       = " ) << otmsXHeight                       << TEXT( "\n" );
   dump_context << TEXT( "   otmrcFontBox.left                 = " ) << otmrcFontBox.left                 << TEXT( "\n" );
   dump_context << TEXT( "   otmrcFontBox.top                  = " ) << otmrcFontBox.top                  << TEXT( "\n" );
   dump_context << TEXT( "   otmrcFontBox.right                = " ) << otmrcFontBox.right                << TEXT( "\n" );
   dump_context << TEXT( "   otmrcFontBox.bottom               = " ) << otmrcFontBox.bottom               << TEXT( "\n" );
   dump_context << TEXT( "   otmMacAscent                      = " ) << otmMacAscent                      << TEXT( "\n" );
   dump_context << TEXT( "   otmMacDescent                     = " ) << otmMacDescent                     << TEXT( "\n" );
   dump_context << TEXT( "   otmMacLineGap                     = " ) << otmMacLineGap                     << TEXT( "\n" );
   dump_context << TEXT( "   otmusMinimumPPEM                  = " ) << otmusMinimumPPEM                  << TEXT( "\n" );
   dump_context << TEXT( "   otmptSubscriptSize.x              = " ) << otmptSubscriptSize.x              << TEXT( "\n" );
   dump_context << TEXT( "   otmptSubscriptSize.y              = " ) << otmptSubscriptSize.y              << TEXT( "\n" );
   dump_context << TEXT( "   otmptSubscriptOffset.x            = " ) << otmptSubscriptOffset.x            << TEXT( "\n" );
   dump_context << TEXT( "   otmptSubscriptOffset.y            = " ) << otmptSubscriptOffset.y            << TEXT( "\n" );
   dump_context << TEXT( "   otmptSuperscriptSize.x            = " ) << otmptSuperscriptSize.x            << TEXT( "\n" );
   dump_context << TEXT( "   otmptSuperscriptSize.y            = " ) << otmptSuperscriptSize.y            << TEXT( "\n" );
   dump_context << TEXT( "   otmptSuperscriptOffset.x          = " ) << otmptSuperscriptOffset.x          << TEXT( "\n" );
   dump_context << TEXT( "   otmptSuperscriptOffset.y          = " ) << otmptSuperscriptOffset.y          << TEXT( "\n" );
   dump_context << TEXT( "   otmsStrikeoutSize                 = " ) << otmsStrikeoutSize                 << TEXT( "\n" );
   dump_context << TEXT( "   otmsStrikeoutPosition             = " ) << otmsStrikeoutPosition             << TEXT( "\n" );
   dump_context << TEXT( "   otmsUnderscoreSize                = " ) << otmsUnderscoreSize                << TEXT( "\n" );
   dump_context << TEXT( "   otmsUnderscorePosition            = " ) << otmsUnderscorePosition            << TEXT( "\n" );
   dump_context << TEXT( "   otmpFamilyName                    = " ) << otmpFamilyName                    << TEXT( "\n" );
   dump_context << TEXT( "   otmpFaceName                      = " ) << otmpFaceName                      << TEXT( "\n" );
   dump_context << TEXT( "   otmpStyleName                     = " ) << otmpStyleName                     << TEXT( "\n" );
   dump_context << TEXT( "   otmpFullName                      = " ) << otmpFullName                      << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void COutlineTextMetricA::Empty( void )
{
   otmSize = sizeof( _OUTLINETEXTMETRICA );

   // TEXTMETRICA
   otmTextMetrics.tmHeight           = 0;
   otmTextMetrics.tmAscent           = 0;
   otmTextMetrics.tmDescent          = 0;
   otmTextMetrics.tmInternalLeading  = 0;
   otmTextMetrics.tmExternalLeading  = 0;
   otmTextMetrics.tmAveCharWidth     = 0;
   otmTextMetrics.tmMaxCharWidth     = 0;
   otmTextMetrics.tmWeight           = 0;
   otmTextMetrics.tmOverhang         = 0;
   otmTextMetrics.tmDigitizedAspectX = 0;
   otmTextMetrics.tmDigitizedAspectY = 0;
   otmTextMetrics.tmFirstChar        = 0;
   otmTextMetrics.tmLastChar         = 0;
   otmTextMetrics.tmDefaultChar      = 0;
   otmTextMetrics.tmBreakChar        = 0;
   otmTextMetrics.tmItalic           = 0;
   otmTextMetrics.tmUnderlined       = 0;
   otmTextMetrics.tmStruckOut        = 0;
   otmTextMetrics.tmPitchAndFamily   = 0;
   otmTextMetrics.tmCharSet          = 0;

   otmFiller = 0;

   // PANOSE
   otmPanoseNumber.bFamilyType      = 0;
   otmPanoseNumber.bSerifStyle      = 0;
   otmPanoseNumber.bWeight          = 0;
   otmPanoseNumber.bProportion      = 0;
   otmPanoseNumber.bContrast        = 0;
   otmPanoseNumber.bStrokeVariation = 0;
   otmPanoseNumber.bArmStyle        = 0;
   otmPanoseNumber.bLetterform      = 0;
   otmPanoseNumber.bMidline         = 0;
   otmPanoseNumber.bXHeight         = 0;

   otmfsSelection    = 0;
   otmfsType         = 0;
   otmsCharSlopeRise = 0;
   otmsCharSlopeRun  = 0;
   otmItalicAngle    = 0;
   otmEMSquare       = 0;
   otmAscent         = 0;
   otmDescent        = 0;
   otmLineGap        = 0;
   otmsCapEmHeight   = 0;
   otmsXHeight       = 0;

   // RECT
   otmrcFontBox.left   = 0;
   otmrcFontBox.top    = 0;
   otmrcFontBox.right  = 0;
   otmrcFontBox.bottom = 0;

   otmMacAscent     = 0;
   otmMacDescent    = 0;
   otmMacLineGap    = 0;
   otmusMinimumPPEM = 0;

   // POINT
   otmptSubscriptSize.x     = 0;
   otmptSubscriptSize.y     = 0;
   otmptSubscriptOffset.x   = 0;
   otmptSubscriptOffset.y   = 0;
   otmptSuperscriptSize.x   = 0;
   otmptSuperscriptSize.y   = 0;
   otmptSuperscriptOffset.x = 0;
   otmptSuperscriptOffset.y = 0;

   otmsStrikeoutSize      = 0;
   otmsStrikeoutPosition  = 0;
   otmsUnderscoreSize     = 0;
   otmsUnderscorePosition = 0;
   otmpFamilyName         = NULL;
   otmpFaceName           = NULL;
   otmpStyleName          = NULL;
   otmpFullName           = NULL;
}

COutlineTextMetricA& COutlineTextMetricA::operator=( const COutlineTextMetricA& source )
{
   Copy( source );
   return( *this );
}

COutlineTextMetricW::COutlineTextMetricW()
{
   Empty();
}

COutlineTextMetricW::COutlineTextMetricW( const COutlineTextMetricW& source )
{
   Empty();
   Copy( source );
}

COutlineTextMetricW::COutlineTextMetricW( const _OUTLINETEXTMETRICW * source )
{
   Empty();
   Copy( source );
}

COutlineTextMetricW::~COutlineTextMetricW()
{
   Empty();
}

void COutlineTextMetricW::Copy( const COutlineTextMetricW& source )
{
   Copy( (const _OUTLINETEXTMETRICW *) &source );
}

void COutlineTextMetricW::Copy( const _OUTLINETEXTMETRICW * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      otmSize = source->otmSize;

      // TEXTMETRICA
      otmTextMetrics.tmHeight           = source->otmTextMetrics.tmHeight;
      otmTextMetrics.tmAscent           = source->otmTextMetrics.tmAscent;
      otmTextMetrics.tmDescent          = source->otmTextMetrics.tmDescent;
      otmTextMetrics.tmInternalLeading  = source->otmTextMetrics.tmInternalLeading;
      otmTextMetrics.tmExternalLeading  = source->otmTextMetrics.tmExternalLeading;
      otmTextMetrics.tmAveCharWidth     = source->otmTextMetrics.tmAveCharWidth;
      otmTextMetrics.tmMaxCharWidth     = source->otmTextMetrics.tmMaxCharWidth;
      otmTextMetrics.tmWeight           = source->otmTextMetrics.tmWeight;
      otmTextMetrics.tmOverhang         = source->otmTextMetrics.tmOverhang;
      otmTextMetrics.tmDigitizedAspectX = source->otmTextMetrics.tmDigitizedAspectX;
      otmTextMetrics.tmDigitizedAspectY = source->otmTextMetrics.tmDigitizedAspectY;
      otmTextMetrics.tmFirstChar        = source->otmTextMetrics.tmFirstChar;
      otmTextMetrics.tmLastChar         = source->otmTextMetrics.tmLastChar;
      otmTextMetrics.tmDefaultChar      = source->otmTextMetrics.tmDefaultChar;
      otmTextMetrics.tmBreakChar        = source->otmTextMetrics.tmBreakChar;
      otmTextMetrics.tmItalic           = source->otmTextMetrics.tmItalic;
      otmTextMetrics.tmUnderlined       = source->otmTextMetrics.tmUnderlined;
      otmTextMetrics.tmStruckOut        = source->otmTextMetrics.tmStruckOut;
      otmTextMetrics.tmPitchAndFamily   = source->otmTextMetrics.tmPitchAndFamily;
      otmTextMetrics.tmCharSet          = source->otmTextMetrics.tmCharSet;

      otmFiller = source->otmFiller;

      // PANOSE
      otmPanoseNumber.bFamilyType      = source->otmPanoseNumber.bFamilyType;
      otmPanoseNumber.bSerifStyle      = source->otmPanoseNumber.bSerifStyle;
      otmPanoseNumber.bWeight          = source->otmPanoseNumber.bWeight;
      otmPanoseNumber.bProportion      = source->otmPanoseNumber.bProportion;
      otmPanoseNumber.bContrast        = source->otmPanoseNumber.bContrast;
      otmPanoseNumber.bStrokeVariation = source->otmPanoseNumber.bStrokeVariation;
      otmPanoseNumber.bArmStyle        = source->otmPanoseNumber.bArmStyle;
      otmPanoseNumber.bLetterform      = source->otmPanoseNumber.bLetterform;
      otmPanoseNumber.bMidline         = source->otmPanoseNumber.bMidline;
      otmPanoseNumber.bXHeight         = source->otmPanoseNumber.bXHeight;

      otmfsSelection    = source->otmfsSelection;
      otmfsType         = source->otmfsType;
      otmsCharSlopeRise = source->otmsCharSlopeRise;
      otmsCharSlopeRun  = source->otmsCharSlopeRun;
      otmItalicAngle    = source->otmItalicAngle;
      otmEMSquare       = source->otmEMSquare;
      otmAscent         = source->otmAscent;
      otmDescent        = source->otmDescent;
      otmLineGap        = source->otmLineGap;
      otmsCapEmHeight   = source->otmsCapEmHeight;
      otmsXHeight       = source->otmsXHeight;

      // RECT
      otmrcFontBox.left   = source->otmrcFontBox.left;
      otmrcFontBox.top    = source->otmrcFontBox.top;
      otmrcFontBox.right  = source->otmrcFontBox.right;
      otmrcFontBox.bottom = source->otmrcFontBox.bottom;

      otmMacAscent     = source->otmMacAscent;
      otmMacDescent    = source->otmMacDescent;
      otmMacLineGap    = source->otmMacLineGap;
      otmusMinimumPPEM = source->otmusMinimumPPEM;

      // POINT
      otmptSubscriptSize.x     = source->otmptSubscriptSize.x;
      otmptSubscriptSize.y     = source->otmptSubscriptSize.y;
      otmptSubscriptOffset.x   = source->otmptSubscriptOffset.x;
      otmptSubscriptOffset.y   = source->otmptSubscriptOffset.y;
      otmptSuperscriptSize.x   = source->otmptSuperscriptSize.x;
      otmptSuperscriptSize.y   = source->otmptSuperscriptSize.y;
      otmptSuperscriptOffset.x = source->otmptSuperscriptOffset.x;
      otmptSuperscriptOffset.y = source->otmptSuperscriptOffset.y;

      otmsStrikeoutSize      = source->otmsStrikeoutSize;
      otmsStrikeoutPosition  = source->otmsStrikeoutPosition;
      otmsUnderscoreSize     = source->otmsUnderscoreSize;
      otmsUnderscorePosition = source->otmsUnderscorePosition;
      otmpFamilyName         = source->otmpFamilyName;
      otmpFaceName           = source->otmpFaceName;
      otmpStyleName          = source->otmpStyleName;
      otmpFullName           = source->otmpFullName;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void COutlineTextMetricW::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a COutlineTextMetricW at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   otmSize                           = " ) << otmSize                           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmHeight           = " ) << otmTextMetrics.tmHeight           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmAscent           = " ) << otmTextMetrics.tmAscent           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmDescent          = " ) << otmTextMetrics.tmDescent          << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmInternalLeading  = " ) << otmTextMetrics.tmInternalLeading  << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmExternalLeading  = " ) << otmTextMetrics.tmExternalLeading  << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmAveCharWidth     = " ) << otmTextMetrics.tmAveCharWidth     << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmMaxCharWidth     = " ) << otmTextMetrics.tmMaxCharWidth     << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmWeight           = " ) << otmTextMetrics.tmWeight           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmOverhang         = " ) << otmTextMetrics.tmOverhang         << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmDigitizedAspectX = " ) << otmTextMetrics.tmDigitizedAspectX << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmDigitizedAspectY = " ) << otmTextMetrics.tmDigitizedAspectY << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmFirstChar        = " ) << otmTextMetrics.tmFirstChar        << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmLastChar         = " ) << otmTextMetrics.tmLastChar         << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmDefaultChar      = " ) << otmTextMetrics.tmDefaultChar      << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmBreakChar        = " ) << otmTextMetrics.tmBreakChar        << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmItalic           = " ) << otmTextMetrics.tmItalic           << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmUnderlined       = " ) << otmTextMetrics.tmUnderlined       << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmStruckOut        = " ) << otmTextMetrics.tmStruckOut        << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmPitchAndFamily   = " ) << otmTextMetrics.tmPitchAndFamily   << TEXT( "\n" );
   dump_context << TEXT( "   otmTextMetrics.tmCharSet          = " ) << otmTextMetrics.tmCharSet          << TEXT( "\n" );
   dump_context << TEXT( "   otmFiller                         = " ) << otmFiller                         << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bFamilyType       = " ) << otmPanoseNumber.bFamilyType       << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bSerifStyle       = " ) << otmPanoseNumber.bSerifStyle       << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bWeight           = " ) << otmPanoseNumber.bWeight           << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bProportion       = " ) << otmPanoseNumber.bProportion       << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bContrast         = " ) << otmPanoseNumber.bContrast         << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bStrokeVariation  = " ) << otmPanoseNumber.bStrokeVariation  << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bArmStyle         = " ) << otmPanoseNumber.bArmStyle         << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bLetterform       = " ) << otmPanoseNumber.bLetterform       << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bMidline          = " ) << otmPanoseNumber.bMidline          << TEXT( "\n" );
   dump_context << TEXT( "   otmPanoseNumber.bXHeight          = " ) << otmPanoseNumber.bXHeight          << TEXT( "\n" );
   dump_context << TEXT( "   otmfsSelection                    = " ) << otmfsSelection                    << TEXT( "\n" );
   dump_context << TEXT( "   otmfsType                         = " ) << otmfsType                         << TEXT( "\n" );
   dump_context << TEXT( "   otmsCharSlopeRise                 = " ) << otmsCharSlopeRise                 << TEXT( "\n" );
   dump_context << TEXT( "   otmsCharSlopeRun                  = " ) << otmsCharSlopeRun                  << TEXT( "\n" );
   dump_context << TEXT( "   otmItalicAngle                    = " ) << otmItalicAngle                    << TEXT( "\n" );
   dump_context << TEXT( "   otmEMSquare                       = " ) << otmEMSquare                       << TEXT( "\n" );
   dump_context << TEXT( "   otmAscent                         = " ) << otmAscent                         << TEXT( "\n" );
   dump_context << TEXT( "   otmDescent                        = " ) << otmDescent                        << TEXT( "\n" );
   dump_context << TEXT( "   otmLineGap                        = " ) << otmLineGap                        << TEXT( "\n" );
   dump_context << TEXT( "   otmsCapEmHeight                   = " ) << otmsCapEmHeight                   << TEXT( "\n" );
   dump_context << TEXT( "   otmsXHeight                       = " ) << otmsXHeight                       << TEXT( "\n" );
   dump_context << TEXT( "   otmrcFontBox.left                 = " ) << otmrcFontBox.left                 << TEXT( "\n" );
   dump_context << TEXT( "   otmrcFontBox.top                  = " ) << otmrcFontBox.top                  << TEXT( "\n" );
   dump_context << TEXT( "   otmrcFontBox.right                = " ) << otmrcFontBox.right                << TEXT( "\n" );
   dump_context << TEXT( "   otmrcFontBox.bottom               = " ) << otmrcFontBox.bottom               << TEXT( "\n" );
   dump_context << TEXT( "   otmMacAscent                      = " ) << otmMacAscent                      << TEXT( "\n" );
   dump_context << TEXT( "   otmMacDescent                     = " ) << otmMacDescent                     << TEXT( "\n" );
   dump_context << TEXT( "   otmMacLineGap                     = " ) << otmMacLineGap                     << TEXT( "\n" );
   dump_context << TEXT( "   otmusMinimumPPEM                  = " ) << otmusMinimumPPEM                  << TEXT( "\n" );
   dump_context << TEXT( "   otmptSubscriptSize.x              = " ) << otmptSubscriptSize.x              << TEXT( "\n" );
   dump_context << TEXT( "   otmptSubscriptSize.y              = " ) << otmptSubscriptSize.y              << TEXT( "\n" );
   dump_context << TEXT( "   otmptSubscriptOffset.x            = " ) << otmptSubscriptOffset.x            << TEXT( "\n" );
   dump_context << TEXT( "   otmptSubscriptOffset.y            = " ) << otmptSubscriptOffset.y            << TEXT( "\n" );
   dump_context << TEXT( "   otmptSuperscriptSize.x            = " ) << otmptSuperscriptSize.x            << TEXT( "\n" );
   dump_context << TEXT( "   otmptSuperscriptSize.y            = " ) << otmptSuperscriptSize.y            << TEXT( "\n" );
   dump_context << TEXT( "   otmptSuperscriptOffset.x          = " ) << otmptSuperscriptOffset.x          << TEXT( "\n" );
   dump_context << TEXT( "   otmptSuperscriptOffset.y          = " ) << otmptSuperscriptOffset.y          << TEXT( "\n" );
   dump_context << TEXT( "   otmsStrikeoutSize                 = " ) << otmsStrikeoutSize                 << TEXT( "\n" );
   dump_context << TEXT( "   otmsStrikeoutPosition             = " ) << otmsStrikeoutPosition             << TEXT( "\n" );
   dump_context << TEXT( "   otmsUnderscoreSize                = " ) << otmsUnderscoreSize                << TEXT( "\n" );
   dump_context << TEXT( "   otmsUnderscorePosition            = " ) << otmsUnderscorePosition            << TEXT( "\n" );
   dump_context << TEXT( "   otmpFamilyName                    = " ) << otmpFamilyName                    << TEXT( "\n" );
   dump_context << TEXT( "   otmpFaceName                      = " ) << otmpFaceName                      << TEXT( "\n" );
   dump_context << TEXT( "   otmpStyleName                     = " ) << otmpStyleName                     << TEXT( "\n" );
   dump_context << TEXT( "   otmpFullName                      = " ) << otmpFullName                      << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void COutlineTextMetricW::Empty( void )
{
   otmSize = sizeof( _OUTLINETEXTMETRICW );

   // TEXTMETRICW
   otmTextMetrics.tmHeight           = 0;
   otmTextMetrics.tmAscent           = 0;
   otmTextMetrics.tmDescent          = 0;
   otmTextMetrics.tmInternalLeading  = 0;
   otmTextMetrics.tmExternalLeading  = 0;
   otmTextMetrics.tmAveCharWidth     = 0;
   otmTextMetrics.tmMaxCharWidth     = 0;
   otmTextMetrics.tmWeight           = 0;
   otmTextMetrics.tmOverhang         = 0;
   otmTextMetrics.tmDigitizedAspectX = 0;
   otmTextMetrics.tmDigitizedAspectY = 0;
   otmTextMetrics.tmFirstChar        = 0;
   otmTextMetrics.tmLastChar         = 0;
   otmTextMetrics.tmDefaultChar      = 0;
   otmTextMetrics.tmBreakChar        = 0;
   otmTextMetrics.tmItalic           = 0;
   otmTextMetrics.tmUnderlined       = 0;
   otmTextMetrics.tmStruckOut        = 0;
   otmTextMetrics.tmPitchAndFamily   = 0;
   otmTextMetrics.tmCharSet          = 0;

   otmFiller = 0;

   // PANOSE
   otmPanoseNumber.bFamilyType      = 0;
   otmPanoseNumber.bSerifStyle      = 0;
   otmPanoseNumber.bWeight          = 0;
   otmPanoseNumber.bProportion      = 0;
   otmPanoseNumber.bContrast        = 0;
   otmPanoseNumber.bStrokeVariation = 0;
   otmPanoseNumber.bArmStyle        = 0;
   otmPanoseNumber.bLetterform      = 0;
   otmPanoseNumber.bMidline         = 0;
   otmPanoseNumber.bXHeight         = 0;

   otmfsSelection    = 0;
   otmfsType         = 0;
   otmsCharSlopeRise = 0;
   otmsCharSlopeRun  = 0;
   otmItalicAngle    = 0;
   otmEMSquare       = 0;
   otmAscent         = 0;
   otmDescent        = 0;
   otmLineGap        = 0;
   otmsCapEmHeight   = 0;
   otmsXHeight       = 0;

   // RECT
   otmrcFontBox.left   = 0;
   otmrcFontBox.top    = 0;
   otmrcFontBox.right  = 0;
   otmrcFontBox.bottom = 0;

   otmMacAscent     = 0;
   otmMacDescent    = 0;
   otmMacLineGap    = 0;
   otmusMinimumPPEM = 0;

   // POINT
   otmptSubscriptSize.x     = 0;
   otmptSubscriptSize.y     = 0;
   otmptSubscriptOffset.x   = 0;
   otmptSubscriptOffset.y   = 0;
   otmptSuperscriptSize.x   = 0;
   otmptSuperscriptSize.y   = 0;
   otmptSuperscriptOffset.x = 0;
   otmptSuperscriptOffset.y = 0;

   otmsStrikeoutSize      = 0;
   otmsStrikeoutPosition  = 0;
   otmsUnderscoreSize     = 0;
   otmsUnderscorePosition = 0;
   otmpFamilyName         = NULL;
   otmpFaceName           = NULL;
   otmpStyleName          = NULL;
   otmpFullName           = NULL;
}

COutlineTextMetricW& COutlineTextMetricW::operator=( const COutlineTextMetricW& source )
{
   Copy( source );
   return( *this );
}

CPerfCounterDefinition::CPerfCounterDefinition()
{
   Empty();
}

CPerfCounterDefinition::~CPerfCounterDefinition()
{
   Empty();
}

void CPerfCounterDefinition::Empty( void )
{
   ByteLength            = sizeof( PERF_COUNTER_DEFINITION );
   CounterNameTitleIndex = 0;
   CounterNameTitle      = NULL;
   CounterHelpTitleIndex = 0;
   CounterHelpTitle      = NULL;
   DefaultScale          = 0;
   DetailLevel           = 0;
   CounterType           = 0;
   CounterSize           = 0;
   CounterOffset         = 0;
}

CPerfInstanceDefinition::CPerfInstanceDefinition()
{
   Empty();
}

CPerfInstanceDefinition::~CPerfInstanceDefinition()
{
   Empty();
}

void CPerfInstanceDefinition::Empty( void )
{
   ByteLength             = sizeof( PERF_INSTANCE_DEFINITION );
   ParentObjectTitleIndex = 0;
   ParentObjectInstance   = 0;
   UniqueID               = 0;
   NameOffset             = 0;
   NameLength             = 0;
}

CPixelFormatDescriptor::CPixelFormatDescriptor()
{
   Empty();
}

CPixelFormatDescriptor::CPixelFormatDescriptor( const CPixelFormatDescriptor& source )
{
   Empty();
   Copy( source );
}

CPixelFormatDescriptor::CPixelFormatDescriptor( const tagPIXELFORMATDESCRIPTOR * source )
{
   Empty();
   Copy( source );
}

CPixelFormatDescriptor::~CPixelFormatDescriptor()
{
   Empty();
}

void CPixelFormatDescriptor::Copy( const CPixelFormatDescriptor& source )
{
   Copy( (const tagPIXELFORMATDESCRIPTOR *) &source );
}

void CPixelFormatDescriptor::Copy( const tagPIXELFORMATDESCRIPTOR * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      nSize           = source->nSize;
      nVersion        = source->nVersion;
      dwFlags         = source->dwFlags;
      iPixelType      = source->iPixelType;
      cColorBits      = source->cColorBits;
      cRedBits        = source->cRedBits;
      cRedShift       = source->cRedShift;
      cGreenBits      = source->cGreenBits;
      cGreenShift     = source->cGreenShift;
      cBlueBits       = source->cBlueBits;
      cBlueShift      = source->cBlueShift;
      cAlphaBits      = source->cAlphaBits;
      cAlphaShift     = source->cAlphaShift;
      cAccumBits      = source->cAccumBits;
      cAccumRedBits   = source->cAccumRedBits;
      cAccumGreenBits = source->cAccumGreenBits;
      cAccumBlueBits  = source->cAccumBlueBits;
      cAccumAlphaBits = source->cAccumAlphaBits;
      cDepthBits      = source->cDepthBits;
      cStencilBits    = source->cStencilBits;
      cAuxBuffers     = source->cAuxBuffers;
      iLayerType      = source->iLayerType;
      bReserved       = source->bReserved;
      dwLayerMask     = source->dwLayerMask;
      dwVisibleMask   = source->dwVisibleMask;
      dwDamageMask    = source->dwDamageMask;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CPixelFormatDescriptor::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CPixelFormatDescriptor at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   nSize           = " ) << nSize           << TEXT( "\n" );
   dump_context << TEXT( "   nVersion        = " ) << nVersion        << TEXT( "\n" );
   dump_context << TEXT( "   dwFlags         = " ) << dwFlags         << TEXT( " (" );

   CString temp_string;

   if ( dwFlags & PFD_DRAW_TO_WINDOW )
   {
      temp_string = TEXT( "PFD_DRAW_TO_WINDOW" );
   }

   if ( dwFlags & PFD_DRAW_TO_BITMAP )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_DRAW_TO_BITMAP" );
   }

   if ( dwFlags & PFD_SUPPORT_GDI )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_SUPPORT_GDI" );
   }

   if ( dwFlags & PFD_SUPPORT_OPENGL )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_SUPPORT_OPENGL" );
   }

   if ( dwFlags & PFD_GENERIC_ACCELERATED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_GENERIC_ACCELERATED" );
   }

   if ( dwFlags & PFD_GENERIC_FORMAT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_GENERIC_FORMAT" );
   }

   if ( dwFlags & PFD_NEED_PALETTE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_NEED_PALETTE" );
   }

   if ( dwFlags & PFD_NEED_SYSTEM_PALETTE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_NEED_SYSTEM_PALETTE" );
   }

   if ( dwFlags & PFD_DOUBLEBUFFER )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_DOUBLEBUFFER" );
   }

   if ( dwFlags & PFD_STEREO )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_STEREO" );
   }

   if ( dwFlags & PFD_SWAP_LAYER_BUFFERS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "PFD_SWAP_LAYER_BUFFERS" );
   }

   dump_context << temp_string << TEXT( " )\n" );

   dump_context << TEXT( "   iPixelType      = " ) << iPixelType      << TEXT( " (" );

   switch( iPixelType )
   {
      case PFD_TYPE_RGBA:

         temp_string = TEXT( "PFD_TYPE_RGBA" );
         break;

      case PFD_TYPE_COLORINDEX:

         temp_string = TEXT( "PFD_TYPE_COLORINDEX" );
         break;
   }

   dump_context << temp_string << TEXT( " )\n" );

   dump_context << TEXT( "   cColorBits      = " ) << cColorBits      << TEXT( "\n" );
   dump_context << TEXT( "   cRedBits        = " ) << cRedBits        << TEXT( "\n" );
   dump_context << TEXT( "   cRedShift       = " ) << cRedShift       << TEXT( "\n" );
   dump_context << TEXT( "   cGreenBits      = " ) << cGreenBits      << TEXT( "\n" );
   dump_context << TEXT( "   cGreenShift     = " ) << cGreenShift     << TEXT( "\n" );
   dump_context << TEXT( "   cBlueBits       = " ) << cBlueBits       << TEXT( "\n" );
   dump_context << TEXT( "   cBlueShift      = " ) << cBlueShift      << TEXT( "\n" );
   dump_context << TEXT( "   cAlphaBits      = " ) << cAlphaBits      << TEXT( "\n" );
   dump_context << TEXT( "   cAlphaShift     = " ) << cAlphaShift     << TEXT( "\n" );
   dump_context << TEXT( "   cAccumBits      = " ) << cAccumBits      << TEXT( "\n" );
   dump_context << TEXT( "   cAccumRedBits   = " ) << cAccumRedBits   << TEXT( "\n" );
   dump_context << TEXT( "   cAccumGreenBits = " ) << cAccumGreenBits << TEXT( "\n" );
   dump_context << TEXT( "   cAccumBlueBits  = " ) << cAccumBlueBits  << TEXT( "\n" );
   dump_context << TEXT( "   cAccumAlphaBits = " ) << cAccumAlphaBits << TEXT( "\n" );
   dump_context << TEXT( "   cDepthBits      = " ) << cDepthBits      << TEXT( "\n" );
   dump_context << TEXT( "   cStencilBits    = " ) << cStencilBits    << TEXT( "\n" );
   dump_context << TEXT( "   cAuxBuffers     = " ) << cAuxBuffers     << TEXT( "\n" );
   dump_context << TEXT( "   iLayerType      = " ) << iLayerType      << TEXT( "\n" );
   dump_context << TEXT( "   bReserved       = " ) << bReserved       << TEXT( "\n" );
   dump_context << TEXT( "   dwLayerMask     = " ) << dwLayerMask     << TEXT( "\n" );
   dump_context << TEXT( "   dwVisibleMask   = " ) << dwVisibleMask   << TEXT( "\n" );
   dump_context << TEXT( "   dwDamageMask    = " ) << dwDamageMask    << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CPixelFormatDescriptor::Empty( void )
{
   nSize           = sizeof( tagPIXELFORMATDESCRIPTOR );
   nVersion        = 0;
   dwFlags         = 0;
   iPixelType      = 0;
   cColorBits      = 0;
   cRedBits        = 0;
   cRedShift       = 0;
   cGreenBits      = 0;
   cGreenShift     = 0;
   cBlueBits       = 0;
   cBlueShift      = 0;
   cAlphaBits      = 0;
   cAlphaShift     = 0;
   cAccumBits      = 0;
   cAccumRedBits   = 0;
   cAccumGreenBits = 0;
   cAccumBlueBits  = 0;
   cAccumAlphaBits = 0;
   cDepthBits      = 0;
   cStencilBits    = 0;
   cAuxBuffers     = 0;
   iLayerType      = 0;
   bReserved       = 0;
   dwLayerMask     = 0;
   dwVisibleMask   = 0;
   dwDamageMask    = 0;
}

CPixelFormatDescriptor& CPixelFormatDescriptor::operator=( const CPixelFormatDescriptor& source )
{
   Copy( source );
   return( *this );
}

CRasterizerStatus::CRasterizerStatus()
{
   Empty();
}

CRasterizerStatus::~CRasterizerStatus()
{
   Empty();
}

void CRasterizerStatus::Empty( void )
{
   nSize       = sizeof( _RASTERIZER_STATUS );
   wFlags      = 0;
   nLanguageID = 0;
}

CSecurityAttributes::CSecurityAttributes()
{
   Empty();
}

CSecurityAttributes::~CSecurityAttributes()
{
   Empty();
}

void CSecurityAttributes::Empty( void )
{
   nLength              = sizeof( SECURITY_ATTRIBUTES );
   lpSecurityDescriptor = NULL;
   bInheritHandle       = FALSE;
}

CSecurityQualityOfService::CSecurityQualityOfService()
{
   Empty();
}

CSecurityQualityOfService::~CSecurityQualityOfService()
{
   Empty();
}

void CSecurityQualityOfService::Empty( void )
{
   Length = sizeof( SECURITY_QUALITY_OF_SERVICE );

   // SECURITY_IMPERSONATION_LEVEL
   ImpersonationLevel = SecurityAnonymous;
   
   // SECURITY_CONTEXT_TRACKING_MODE
   ContextTrackingMode = FALSE;

   //BOOLEAN
   EffectiveOnly = FALSE;
}

/*
** CSystemAuditEntry
*/

CSystemAuditEntry::CSystemAuditEntry()
{
   Empty();
}

CSystemAuditEntry::CSystemAuditEntry( const CSystemAuditEntry& source )
{
   Empty();
   Copy( source );
}

CSystemAuditEntry::CSystemAuditEntry( const _SYSTEM_AUDIT_ACE * source )
{
   Empty();
   Copy( source );
}

CSystemAuditEntry::~CSystemAuditEntry()
{
   Empty();
}

void CSystemAuditEntry::Copy( const CSystemAuditEntry& source )
{
   Copy( (const _SYSTEM_AUDIT_ACE *) &source );
}

void CSystemAuditEntry::Copy( const _SYSTEM_AUDIT_ACE * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      // ACE_HEADER
      Header.AceType  = source->Header.AceType;
      Header.AceFlags = source->Header.AceFlags;
      Header.AceSize  = source->Header.AceSize;

      // ACCESS_MASK
      Mask            = source->Mask;
      SidStart        = source->SidStart;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CSystemAuditEntry::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CSystemAuditEntry at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   Header.AceType  = " ) << Header.AceType  << TEXT( " (" );

   switch( Header.AceType )
   {
      case ACCESS_ALLOWED_ACE_TYPE:

         dump_context << TEXT( "ACCESS_ALLOWED_ACE_TYPE" );
         break;

      case ACCESS_DENIED_ACE_TYPE:

         dump_context << TEXT( "ACCESS_DENIED_ACE_TYPE" );
         break;

      case SYSTEM_AUDIT_ACE_TYPE:

         dump_context << TEXT( "SYSTEM_AUDIT_ACE_TYPE" );
         break;

      case SYSTEM_ALARM_ACE_TYPE:

         dump_context << TEXT( "SYSTEM_ALARM_ACE_TYPE" );
         break;
   }

   dump_context << TEXT( ")\n" );

   dump_context << TEXT( "   Header.AceFlags = " ) << Header.AceFlags << TEXT( " (" );

   CString temp_string;

   if ( Header.AceFlags & CONTAINER_INHERIT_ACE )
   {
      temp_string = TEXT( "CONTAINER_INHERIT_ACE" );
   }

   if ( Header.AceFlags & INHERIT_ONLY_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "INHERIT_ONLY_ACE" );
   }

   if ( Header.AceFlags & NO_PROPAGATE_INHERIT_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "NO_PROPAGATE_INHERIT_ACE" );
   }

   if ( Header.AceFlags & OBJECT_INHERIT_ACE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "OBJECT_INHERIT_ACE" );
   }

   if ( Header.AceFlags & FAILED_ACCESS_ACE_FLAG )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "FAILED_ACCESS_ACE_FLAG" );
   }

   if ( Header.AceFlags & SUCCESSFUL_ACCESS_ACE_FLAG )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SUCCESSFUL_ACCESS_ACE_FLAG" );
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   Header.AceSize  = " ) << Header.AceSize  << TEXT( "\n" );
   dump_context << TEXT( "   Mask            = " ) << Mask            << TEXT( "\n" );
   dump_context << TEXT( "   SidStart        = " ) << SidStart        << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CSystemAuditEntry::Empty( void )
{
   // ACE_HEADER
   Header.AceType  = 0;
   Header.AceFlags = 0;
   Header.AceSize  = 0;

   // ACCESS_MASK
   Mask            = 0;

   SidStart        = 0;
}

CSystemAuditEntry& CSystemAuditEntry::operator=( const CSystemAuditEntry& source )
{
   Copy( source );
   return( *this );
}

/*
** CTextMetricA
*/

CTextMetricA::CTextMetricA()
{
   Empty();
}

CTextMetricA::CTextMetricA( const CTextMetricA& source )
{
   Empty();
   Copy( source );
}

CTextMetricA::CTextMetricA( const tagTEXTMETRICA * source )
{
   Empty();
   Copy( source );
}

CTextMetricA::~CTextMetricA()
{
   Empty();
}

void CTextMetricA::Copy( const CTextMetricA& source )
{
   Copy( (const tagTEXTMETRICA *) &source );
}

void CTextMetricA::Copy( const tagTEXTMETRICA * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      tmHeight           = source->tmHeight;
      tmAscent           = source->tmAscent;
      tmDescent          = source->tmDescent;
      tmInternalLeading  = source->tmInternalLeading;
      tmExternalLeading  = source->tmExternalLeading;
      tmAveCharWidth     = source->tmAveCharWidth;
      tmMaxCharWidth     = source->tmMaxCharWidth;
      tmWeight           = source->tmWeight;
      tmOverhang         = source->tmOverhang;
      tmDigitizedAspectX = source->tmDigitizedAspectX;
      tmDigitizedAspectY = source->tmDigitizedAspectY;
      tmFirstChar        = source->tmFirstChar;
      tmLastChar         = source->tmLastChar;
      tmDefaultChar      = source->tmDefaultChar;
      tmBreakChar        = source->tmBreakChar;
      tmItalic           = source->tmItalic;
      tmUnderlined       = source->tmUnderlined;
      tmStruckOut        = source->tmStruckOut;
      tmPitchAndFamily   = source->tmPitchAndFamily;
      tmCharSet          = source->tmCharSet;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CTextMetricA::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CTextMetricA at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   tmHeight           = " ) << tmHeight           << TEXT( "\n" );
   dump_context << TEXT( "   tmAscent           = " ) << tmAscent           << TEXT( "\n" );
   dump_context << TEXT( "   tmDescent          = " ) << tmDescent          << TEXT( "\n" );
   dump_context << TEXT( "   tmInternalLeading  = " ) << tmInternalLeading  << TEXT( "\n" );
   dump_context << TEXT( "   tmExternalLeading  = " ) << tmExternalLeading  << TEXT( "\n" );
   dump_context << TEXT( "   tmAveCharWidth     = " ) << tmAveCharWidth     << TEXT( "\n" );
   dump_context << TEXT( "   tmMaxCharWidth     = " ) << tmMaxCharWidth     << TEXT( "\n" );
   dump_context << TEXT( "   tmWeight           = " ) << tmWeight           << TEXT( "\n" );
   dump_context << TEXT( "   tmOverhang         = " ) << tmOverhang         << TEXT( "\n" );
   dump_context << TEXT( "   tmDigitizedAspectX = " ) << tmDigitizedAspectX << TEXT( "\n" );
   dump_context << TEXT( "   tmDigitizedAspectY = " ) << tmDigitizedAspectY << TEXT( "\n" );
   dump_context << TEXT( "   tmFirstChar        = " ) << tmFirstChar        << TEXT( "\n" );
   dump_context << TEXT( "   tmLastChar         = " ) << tmLastChar         << TEXT( "\n" );
   dump_context << TEXT( "   tmDefaultChar      = " ) << tmDefaultChar      << TEXT( "\n" );
   dump_context << TEXT( "   tmBreakChar        = " ) << tmBreakChar        << TEXT( "\n" );
   dump_context << TEXT( "   tmItalic           = " ) << tmItalic           << TEXT( "\n" );
   dump_context << TEXT( "   tmUnderlined       = " ) << tmUnderlined       << TEXT( "\n" );
   dump_context << TEXT( "   tmStruckOut        = " ) << tmStruckOut        << TEXT( "\n" );
   dump_context << TEXT( "   tmPitchAndFamily   = " ) << tmPitchAndFamily   << TEXT( "\n" );
   dump_context << TEXT( "   tmCharSet          = " ) << tmCharSet          << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CTextMetricA::Empty( void )
{
   tmHeight           = 0;
   tmAscent           = 0;
   tmDescent          = 0;
   tmInternalLeading  = 0;
   tmExternalLeading  = 0;
   tmAveCharWidth     = 0;
   tmMaxCharWidth     = 0;
   tmWeight           = 0;
   tmOverhang         = 0;
   tmDigitizedAspectX = 0;
   tmDigitizedAspectY = 0;
   tmFirstChar        = 0;
   tmLastChar         = 0;
   tmDefaultChar      = 0;
   tmBreakChar        = 0;
   tmItalic           = 0;
   tmUnderlined       = 0;
   tmStruckOut        = 0;
   tmPitchAndFamily   = 0;
   tmCharSet          = 0;
}

CTextMetricA& CTextMetricA::operator=( const CTextMetricA& source )
{
   Copy( source );
   return( *this );
}

/*
** CTextMetricW
*/

CTextMetricW::CTextMetricW()
{
   Empty();
}

CTextMetricW::CTextMetricW( const CTextMetricW& source )
{
   Empty();
   Copy( source );
}

CTextMetricW::CTextMetricW( const tagTEXTMETRICW * source )
{
   Empty();
   Copy( source );
}

CTextMetricW::~CTextMetricW()
{
   Empty();
}

void CTextMetricW::Copy( const CTextMetricW& source )
{
   Copy( (const tagTEXTMETRICW *) &source );
}

void CTextMetricW::Copy( const tagTEXTMETRICW * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      tmHeight           = source->tmHeight;
      tmAscent           = source->tmAscent;
      tmDescent          = source->tmDescent;
      tmInternalLeading  = source->tmInternalLeading;
      tmExternalLeading  = source->tmExternalLeading;
      tmAveCharWidth     = source->tmAveCharWidth;
      tmMaxCharWidth     = source->tmMaxCharWidth;
      tmWeight           = source->tmWeight;
      tmOverhang         = source->tmOverhang;
      tmDigitizedAspectX = source->tmDigitizedAspectX;
      tmDigitizedAspectY = source->tmDigitizedAspectY;
      tmFirstChar        = source->tmFirstChar;
      tmLastChar         = source->tmLastChar;
      tmDefaultChar      = source->tmDefaultChar;
      tmBreakChar        = source->tmBreakChar;
      tmItalic           = source->tmItalic;
      tmUnderlined       = source->tmUnderlined;
      tmStruckOut        = source->tmStruckOut;
      tmPitchAndFamily   = source->tmPitchAndFamily;
      tmCharSet          = source->tmCharSet;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CTextMetricW::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CTextMetricW at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   tmHeight           = " ) << tmHeight           << TEXT( "\n" );
   dump_context << TEXT( "   tmAscent           = " ) << tmAscent           << TEXT( "\n" );
   dump_context << TEXT( "   tmDescent          = " ) << tmDescent          << TEXT( "\n" );
   dump_context << TEXT( "   tmInternalLeading  = " ) << tmInternalLeading  << TEXT( "\n" );
   dump_context << TEXT( "   tmExternalLeading  = " ) << tmExternalLeading  << TEXT( "\n" );
   dump_context << TEXT( "   tmAveCharWidth     = " ) << tmAveCharWidth     << TEXT( "\n" );
   dump_context << TEXT( "   tmMaxCharWidth     = " ) << tmMaxCharWidth     << TEXT( "\n" );
   dump_context << TEXT( "   tmWeight           = " ) << tmWeight           << TEXT( "\n" );
   dump_context << TEXT( "   tmOverhang         = " ) << tmOverhang         << TEXT( "\n" );
   dump_context << TEXT( "   tmDigitizedAspectX = " ) << tmDigitizedAspectX << TEXT( "\n" );
   dump_context << TEXT( "   tmDigitizedAspectY = " ) << tmDigitizedAspectY << TEXT( "\n" );
   dump_context << TEXT( "   tmFirstChar        = " ) << tmFirstChar        << TEXT( "\n" );
   dump_context << TEXT( "   tmLastChar         = " ) << tmLastChar         << TEXT( "\n" );
   dump_context << TEXT( "   tmDefaultChar      = " ) << tmDefaultChar      << TEXT( "\n" );
   dump_context << TEXT( "   tmBreakChar        = " ) << tmBreakChar        << TEXT( "\n" );
   dump_context << TEXT( "   tmItalic           = " ) << tmItalic           << TEXT( "\n" );
   dump_context << TEXT( "   tmUnderlined       = " ) << tmUnderlined       << TEXT( "\n" );
   dump_context << TEXT( "   tmStruckOut        = " ) << tmStruckOut        << TEXT( "\n" );
   dump_context << TEXT( "   tmPitchAndFamily   = " ) << tmPitchAndFamily   << TEXT( "\n" );
   dump_context << TEXT( "   tmCharSet          = " ) << tmCharSet          << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CTextMetricW::Empty( void )
{
   tmHeight           = 0;
   tmAscent           = 0;
   tmDescent          = 0;
   tmInternalLeading  = 0;
   tmExternalLeading  = 0;
   tmAveCharWidth     = 0;
   tmMaxCharWidth     = 0;
   tmWeight           = 0;
   tmOverhang         = 0;
   tmDigitizedAspectX = 0;
   tmDigitizedAspectY = 0;
   tmFirstChar        = 0;
   tmLastChar         = 0;
   tmDefaultChar      = 0;
   tmBreakChar        = 0;
   tmItalic           = 0;
   tmUnderlined       = 0;
   tmStruckOut        = 0;
   tmPitchAndFamily   = 0;
   tmCharSet          = 0;
}

CTextMetricW& CTextMetricW::operator=( const CTextMetricW& source )
{
   Copy( source );
   return( *this );
}

CWindowPlacement::CWindowPlacement()
{
   Empty();
}

CWindowPlacement::CWindowPlacement( const CWindowPlacement& source )
{
   Empty();
   Copy( source );
}

CWindowPlacement::CWindowPlacement( const tagWINDOWPLACEMENT * source )
{
   Empty();
   Copy( source );
}

CWindowPlacement::~CWindowPlacement()
{
   Empty();
}

void CWindowPlacement::Copy( const CWindowPlacement& source )
{
   Copy( (const tagWINDOWPLACEMENT *) &source );
}

void CWindowPlacement::Copy( const tagWINDOWPLACEMENT * source )
{
   ASSERT( source != NULL );
   ASSERT( source != this );

   if ( source == NULL || source == this )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      length  = source->length;
      flags   = source->flags;
      showCmd = source->showCmd;

      // POINT
      ptMinPosition.x = source->ptMinPosition.x;
      ptMinPosition.y = source->ptMinPosition.y;
      ptMaxPosition.x = source->ptMaxPosition.x;
      ptMaxPosition.y = source->ptMaxPosition.y;

      // RECT
      rcNormalPosition.left   = source->rcNormalPosition.left;
      rcNormalPosition.top    = source->rcNormalPosition.top;
      rcNormalPosition.right  = source->rcNormalPosition.right;
      rcNormalPosition.bottom = source->rcNormalPosition.bottom;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CWindowPlacement::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CWindowPlacement at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   length                  = " ) << length                  << TEXT( "\n" );
   dump_context << TEXT( "   flags                   = " ) << flags                   << TEXT( " (" );

   CString temp_string;

   if ( flags & WPF_SETMINPOSITION )
   {
      temp_string = TEXT( "WPF_SETMINPOSITION" );
   }

   if ( flags & WPF_RESTORETOMAXIMIZED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "WPF_RESTORETOMAXIMIZED" );
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   showCmd                 = " ) << showCmd                 << TEXT( " (" );

   temp_string.Empty();

   switch( showCmd )
   {
      case SW_HIDE:

         temp_string = TEXT( "SW_HIDE" );
         break;

      case SW_MINIMIZE:

         temp_string = TEXT( "SW_MINIMIZE" );
         break;

      case SW_RESTORE:

         temp_string = TEXT( "SW_RESTORE" );
         break;

      case SW_SHOW:

         temp_string = TEXT( "SW_SHOW" );
         break;

      case SW_SHOWMAXIMIZED:

         temp_string = TEXT( "SW_SHOWMAXIMIZED" );
         break;

      case SW_SHOWMINIMIZED:

         temp_string = TEXT( "SW_SHOWMINIMIZED" );
         break;

      case SW_SHOWMINNOACTIVE:

         temp_string = TEXT( "SW_SHOWMINNOACTIVE" );
         break;

      case SW_SHOWNA:

         temp_string = TEXT( "SW_SHOWNA" );
         break;

      case SW_SHOWNOACTIVATE:

         temp_string = TEXT( "SW_SHOWNOACTIVATE" );
         break;

      case SW_SHOWNORMAL:

         temp_string = TEXT( "SW_SHOWNORMAL" );
         break;
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   ptMinPosition.x         = " ) << ptMinPosition.x         << TEXT( "\n" );
   dump_context << TEXT( "   ptMinPosition.y         = " ) << ptMinPosition.y         << TEXT( "\n" );
   dump_context << TEXT( "   ptMaxPosition.x         = " ) << ptMaxPosition.x         << TEXT( "\n" );
   dump_context << TEXT( "   ptMaxPosition.y         = " ) << ptMaxPosition.y         << TEXT( "\n" );
   dump_context << TEXT( "   rcNormalPosition.left   = " ) << rcNormalPosition.left   << TEXT( "\n" );
   dump_context << TEXT( "   rcNormalPosition.top    = " ) << rcNormalPosition.top    << TEXT( "\n" );
   dump_context << TEXT( "   rcNormalPosition.right  = " ) << rcNormalPosition.right  << TEXT( "\n" );
   dump_context << TEXT( "   rcNormalPosition.bottom = " ) << rcNormalPosition.bottom << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CWindowPlacement::Empty( void )
{
   length  = sizeof( tagWINDOWPLACEMENT );
   flags   = 0;
   showCmd = 0;

   // POINT
   ptMinPosition.x = 0;
   ptMinPosition.y = 0;
   ptMaxPosition.x = 0;
   ptMaxPosition.y = 0;

   // RECT
   rcNormalPosition.left   = 0;
   rcNormalPosition.top    = 0;
   rcNormalPosition.right  = 0;
   rcNormalPosition.bottom = 0;
}

CWindowPlacement& CWindowPlacement::operator=( const CWindowPlacement& source )
{
   Copy( source );
   return( *this );
}

// End of source
