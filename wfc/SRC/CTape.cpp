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
** $Workfile: ctape.cpp $
** $Revision: 29 $
** $Modtime: 3/17/00 4:37p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

/*
** CTapeGetDriveParameters
*/

CTapeGetDriveParameters::CTapeGetDriveParameters()
{
   WFCLTRACEINIT( TEXT( "CTapeGetDriveParameters::CTapeGetDriveParameters()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CTapeGetDriveParameters::CTapeGetDriveParameters( const CTapeGetDriveParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetDriveParameters::CTapeGetDriveParameters( CTapeGetDriveParameters )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CTapeGetDriveParameters::CTapeGetDriveParameters( const TAPE_GET_DRIVE_PARAMETERS * source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetDriveParameters::CTapeGetDriveParameters( TAPE_GET_DRIVE_PARAMETERS )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CTapeGetDriveParameters::~CTapeGetDriveParameters()
{
   WFCLTRACEINIT( TEXT( "CTapeGetDriveParameters::~CTapeGetDriveParameters()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CTapeGetDriveParameters::Copy( const CTapeGetDriveParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetDriveParameters::Copy( const CTapeGetDriveParameters& )" ) );
   Copy( (const TAPE_GET_DRIVE_PARAMETERS *) &source );
}

void CTapeGetDriveParameters::Copy( const TAPE_GET_DRIVE_PARAMETERS * source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetDriveParameters::Copy( const TAPE_GET_DRIVE_PARAMETERS * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ECC                   = source->ECC;
      Compression           = source->Compression;
      DataPadding           = source->DataPadding;
      ReportSetmarks        = source->ReportSetmarks;
      DefaultBlockSize      = source->DefaultBlockSize;
      MaximumBlockSize      = source->MaximumBlockSize;
      MinimumBlockSize      = source->MinimumBlockSize;
      MaximumPartitionCount = source->MaximumPartitionCount;
      FeaturesLow           = source->FeaturesLow;
      FeaturesHigh          = source->FeaturesHigh;
      EOTWarningZoneSize    = source->EOTWarningZoneSize;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CTapeGetDriveParameters::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CTapeGetDriveParameters at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   ECC = "                   ) << ECC                   << TEXT( "\n" );
   dump_context << TEXT( "   Compression = "           ) << Compression           << TEXT( "\n" );
   dump_context << TEXT( "   DataPadding = "           ) << DataPadding           << TEXT( "\n" );
   dump_context << TEXT( "   ReportSetmarks = "        ) << ReportSetmarks        << TEXT( "\n" );
   dump_context << TEXT( "   DefaultBlockSize = "      ) << DefaultBlockSize      << TEXT( "\n" );
   dump_context << TEXT( "   MaximumBlockSize = "      ) << MaximumBlockSize      << TEXT( "\n" );
   dump_context << TEXT( "   MinimumBlockSize = "      ) << MinimumBlockSize      << TEXT( "\n" );
   dump_context << TEXT( "   MaximumPartitionCount = " ) << MaximumPartitionCount << TEXT( "\n" );
   dump_context << TEXT( "   FeaturesLow = "           ) << FeaturesLow           << TEXT( " (" );

   CString temp_string;

   if ( FeaturesLow & TAPE_DRIVE_COMPRESSION )
   {
      temp_string = TEXT( "TAPE_DRIVE_COMPRESSION" );
   }

   if ( FeaturesLow & TAPE_DRIVE_ECC )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_ECC" );
   }

   if ( FeaturesLow & TAPE_DRIVE_EJECT_MEDIA )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_EJECT_MEDIA" );
   }

   if ( FeaturesLow & TAPE_DRIVE_ERASE_BOP_ONLY )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_ERASE_BOP_ONLY" );
   }

   if ( FeaturesLow & TAPE_DRIVE_ERASE_LONG )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_ERASE_LONG" );
   }

   if ( FeaturesLow & TAPE_DRIVE_ERASE_IMMEDIATE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_ERASE_IMMEDIATE" );
   }

   if ( FeaturesLow & TAPE_DRIVE_ERASE_SHORT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_ERASE_SHORT" );
   }

   if ( FeaturesLow & TAPE_DRIVE_FIXED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_FIXED" );
   }

   if ( FeaturesLow & TAPE_DRIVE_FIXED_BLOCK )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_FIXED_BLOCK" );
   }

   if ( FeaturesLow & TAPE_DRIVE_INITIATOR )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_INITIATOR" );
   }

   if ( FeaturesLow & TAPE_DRIVE_PADDING )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_PADDING" );
   }

   if ( FeaturesLow & TAPE_DRIVE_GET_ABSOLUTE_BLK )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_GET_ABSOLUTE_BLK" );
   }

   if ( FeaturesLow & TAPE_DRIVE_GET_LOGICAL_BLK )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_GET_LOGICAL_BLK" );
   }

   if ( FeaturesLow & TAPE_DRIVE_REPORT_SMKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_REPORT_SMKS" );
   }

   if ( FeaturesLow & TAPE_DRIVE_SELECT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SELECT" );
   }

   if ( FeaturesLow & TAPE_DRIVE_SET_EOT_WZ_SIZE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SET_EOT_WZ_SIZE" );
   }

   if ( FeaturesLow & TAPE_DRIVE_TAPE_CAPACITY )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_TAPE_CAPACITY" );
   }

   if ( FeaturesLow & TAPE_DRIVE_TAPE_REMAINING )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_TAPE_REMAINING" );
   }

   if ( FeaturesLow & TAPE_DRIVE_VARIABLE_BLOCK )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_VARIABLE_BLOCK" );
   }

   if ( FeaturesLow & TAPE_DRIVE_WRITE_PROTECT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_WRITE_PROTECT" );
   }

   dump_context << temp_string << TEXT( " )\n" );

   dump_context << TEXT( "   FeaturesHigh = "          ) << FeaturesHigh          << TEXT( " (" );

   DWORD features_high = FeaturesHigh;

   features_high |= TAPE_DRIVE_HIGH_FEATURES;

   temp_string.Empty();

   if ( features_high & TAPE_DRIVE_LOAD_UNLOAD )
   {
      temp_string = TEXT( "TAPE_DRIVE_LOAD_UNLOAD" );
   }

   if ( features_high & TAPE_DRIVE_TENSION )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_TENSION" );
   }

   if ( features_high & TAPE_DRIVE_LOCK_UNLOCK )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_LOCK_UNLOCK" );
   }

   if ( features_high & TAPE_DRIVE_REWIND_IMMEDIATE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_REWIND_IMMEDIATE" );
   }

   if ( features_high & TAPE_DRIVE_SET_BLOCK_SIZE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SET_BLOCK_SIZE" );
   }

   if ( features_high & TAPE_DRIVE_LOAD_UNLD_IMMED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_LOAD_UNLD_IMMED" );
   }

   if ( features_high & TAPE_DRIVE_TENSION_IMMED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_TENSION_IMMED" );
   }

   if ( features_high & TAPE_DRIVE_LOCK_UNLK_IMMED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_LOCK_UNLK_IMMED" );
   }

   if ( features_high & TAPE_DRIVE_SET_ECC )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SET_ECC" );
   }

   if ( features_high & TAPE_DRIVE_SET_COMPRESSION )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SET_COMPRESSION" );
   }

   if ( features_high & TAPE_DRIVE_SET_PADDING )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SET_PADDING" );
   }

   if ( features_high & TAPE_DRIVE_SET_REPORT_SMKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SET_REPORT_SMKS" );
   }

   if ( features_high & TAPE_DRIVE_ABSOLUTE_BLK )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_ABSOLUTE_BLK" );
   }

   if ( features_high & TAPE_DRIVE_ABS_BLK_IMMED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_ABS_BLK_IMMED" );
   }

   if ( features_high & TAPE_DRIVE_LOGICAL_BLK )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_LOGICAL_BLK" );
   }

   if ( features_high & TAPE_DRIVE_LOG_BLK_IMMED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_LOG_BLK_IMMED" );
   }

   if ( features_high & TAPE_DRIVE_END_OF_DATA )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_END_OF_DATA" );
   }

   if ( features_high & TAPE_DRIVE_RELATIVE_BLKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_RELATIVE_BLKS" );
   }

   if ( features_high & TAPE_DRIVE_FILEMARKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_FILEMARKS" );
   }

   if ( features_high & TAPE_DRIVE_SEQUENTIAL_FMKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SEQUENTIAL_FMKS" );
   }

   if ( features_high & TAPE_DRIVE_SETMARKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SETMARKS" );
   }

   if ( features_high & TAPE_DRIVE_SEQUENTIAL_SMKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SEQUENTIAL_SMKS" );
   }

   if ( features_high & TAPE_DRIVE_REVERSE_POSITION )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_REVERSE_POSITION" );
   }

   if ( features_high & TAPE_DRIVE_SPACE_IMMEDIATE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_SPACE_IMMEDIATE" );
   }

   if ( features_high & TAPE_DRIVE_WRITE_SETMARKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_WRITE_SETMARKS" );
   }

   if ( features_high & TAPE_DRIVE_WRITE_FILEMARKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_WRITE_FILEMARKS" );
   }

   if ( features_high & TAPE_DRIVE_WRITE_SHORT_FMKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_WRITE_SHORT_FMKS" );
   }

   if ( features_high & TAPE_DRIVE_WRITE_LONG_FMKS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_WRITE_LONG_FMKS" );
   }

   if ( features_high & TAPE_DRIVE_WRITE_MARK_IMMED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_WRITE_MARK_IMMED" );
   }

   if ( features_high & TAPE_DRIVE_FORMAT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_FORMAT" );
   }

   if ( features_high & TAPE_DRIVE_FORMAT_IMMEDIATE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "TAPE_DRIVE_FORMAT_IMMEDIATE" );
   }

   dump_context << temp_string << TEXT( " )\n" );

   dump_context << TEXT( "   EOTWarningZoneSize = "    ) << EOTWarningZoneSize    << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CTapeGetDriveParameters::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CTapeGetDriveParameters::Empty()" ) );

   ECC                   = 0;
   Compression           = 0;
   DataPadding           = 0;
   ReportSetmarks        = 0;
   DefaultBlockSize      = 0;
   MaximumBlockSize      = 0;
   MinimumBlockSize      = 0;
   MaximumPartitionCount = 0;
   FeaturesLow           = 0;
   FeaturesHigh          = 0;
   EOTWarningZoneSize    = 0;
}

CTapeGetDriveParameters& CTapeGetDriveParameters::operator=( const CTapeGetDriveParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetDriveParameters::operator=( CTapeGetDriveParameters )" ) );
   Copy( source );
   return( *this );
}

CTapeGetDriveParameters& CTapeGetDriveParameters::operator=( const TAPE_GET_DRIVE_PARAMETERS& source )
{
   WFCLTRACEINIT( TEXT( "CTapeGetDriveParameters::operator=( TAPE_GET_DRIVE_PARAMETERS )" ) );
   Copy( &source );
   return( *this );
}

/*
** CTapeSetDriveParameters
*/

CTapeSetDriveParameters::CTapeSetDriveParameters()
{
   WFCLTRACEINIT( TEXT( "CTapeSetDriveParameters::CTapeSetDriveParameters()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CTapeSetDriveParameters::CTapeSetDriveParameters( const CTapeSetDriveParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetDriveParameters::CTapeSetDriveParameters( CTapeSetDriveParameters )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CTapeSetDriveParameters::CTapeSetDriveParameters( const TAPE_SET_DRIVE_PARAMETERS * source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetDriveParameters::CTapeSetDriveParameters( TAPE_SET_DRIVE_PARAMETERS )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CTapeSetDriveParameters::~CTapeSetDriveParameters()
{
   WFCLTRACEINIT( TEXT( "CTapeSetDriveParameters::~CTapeSetDriveParameters()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CTapeSetDriveParameters::Copy( const CTapeSetDriveParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetDriveParameters::Copy( const CTapeSetDriveParameters& )" ) );
   Copy( (const TAPE_SET_DRIVE_PARAMETERS * ) &source );
}

void CTapeSetDriveParameters::Copy( const TAPE_SET_DRIVE_PARAMETERS * source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetDriveParameters::Copy( const TAPE_SET_DRIVE_PARAMETERS * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ECC                = source->ECC;
      Compression        = source->Compression;
      ReportSetmarks     = source->ReportSetmarks;
      EOTWarningZoneSize = source->EOTWarningZoneSize;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CTapeSetDriveParameters::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CTapeSetDriveParameters at " )<< (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   ECC = "                ) << ECC                << TEXT( "\n" );
   dump_context << TEXT( "   Compression = "        ) << Compression        << TEXT( "\n" );
   dump_context << TEXT( "   ReportSetmarks = "     ) << ReportSetmarks     << TEXT( "\n" );
   dump_context << TEXT( "   EOTWarningZoneSize = " ) << EOTWarningZoneSize << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CTapeSetDriveParameters::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CTapeSetDriveParameters::Empty()" ) );

   ECC                = 0;
   Compression        = 0;
   DataPadding        = 0;
   ReportSetmarks     = 0;
   EOTWarningZoneSize = 0;
}

CTapeSetDriveParameters& CTapeSetDriveParameters::operator=( const CTapeSetDriveParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetDriveParameters::operator=( CTapeSetDriveParameters )" ) );
   Copy( source );
   return( *this );
}

CTapeSetDriveParameters& CTapeSetDriveParameters::operator=( const TAPE_SET_DRIVE_PARAMETERS& source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetDriveParameters::operator=( TAPE_SET_DRIVE_PARAMETERS )" ) );
   Copy( &source );
   return( *this );
}

/*
** CTapeSetMediaParameters
*/

CTapeSetMediaParameters::CTapeSetMediaParameters()
{
   WFCLTRACEINIT( TEXT( "CTapeSetMediaParameters::CTapeSetMediaParameters()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CTapeSetMediaParameters::CTapeSetMediaParameters( const CTapeSetMediaParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetMediaParameters::CTapeSetMediaParameters( CTapeSetMediaParameters )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CTapeSetMediaParameters::CTapeSetMediaParameters( const TAPE_SET_MEDIA_PARAMETERS * source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetMediaParameters::CTapeSetMediaParameters( TAPE_SET_MEDIA_PARAMETERS )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CTapeSetMediaParameters::~CTapeSetMediaParameters()
{
   WFCLTRACEINIT( TEXT( "CTapeSetMediaParameters::~CTapeSetMediaParameters()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CTapeSetMediaParameters::Copy( const CTapeSetMediaParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetMediaParameters::Copy( const CTapeSetMediaParameters& )" ) );
   Copy( (const TAPE_SET_MEDIA_PARAMETERS *) &source );
}

void CTapeSetMediaParameters::Copy( const TAPE_SET_MEDIA_PARAMETERS * source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetMediaParameters::Copy( const TAPE_SET_MEDIA_PARAMETERS * )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      BlockSize = source->BlockSize;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CTapeSetMediaParameters::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CTapeSetMediaParameters at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   BlockSize = " ) << BlockSize << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CTapeSetMediaParameters::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CTapeSetMediaParameters::Empty()" ) );
   BlockSize = 0;
}

CTapeSetMediaParameters& CTapeSetMediaParameters::operator=( const CTapeSetMediaParameters& source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetMediaParameters::operator=( CTapeSetMediaParameters )" ) );
   Copy( source );
   return( *this );
}

CTapeSetMediaParameters& CTapeSetMediaParameters::operator=( const TAPE_SET_MEDIA_PARAMETERS& source )
{
   WFCLTRACEINIT( TEXT( "CTapeSetMediaParameters::operator=( TAPE_SET_MEDIA_PARAMETERS )" ) );
   Copy( &source );
   return( *this );
}

/*
** CTape
*/

CTape::CTape()
{
   WFCLTRACEINIT( TEXT( "CTape::CTape()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
   m_AutomaticallyClose = FALSE;
}

CTape::~CTape()
{
   WFCLTRACEINIT( TEXT( "CTape::~CTape()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_AutomaticallyClose != FALSE )
   {
      WFCTRACE( TEXT( "Automatically Closing" ) );
      Close();
   }

   m_Initialize();
}

void CTape::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CTape::m_Initialize()" ) );
   m_BackupReadContextPointer  = NULL;
   m_BackupWriteContextPointer = NULL;
}

void CTape::Close( void )
{
   WFCLTRACEINIT( TEXT( "CTape::Close()" ) );

   Unlock();
   Unload();
   GetStatus();

   if ( m_hFile != NULL )
   {
      WFCTRACE( TEXT( "Closing Handle" ) );
      CDummyFile::Close();
   }
}

BOOL CTape::CreatePartition( const TypeOfPartition type_of_partition, 
                             const DWORD           number_of_partitions, 
                             const DWORD           number_of_megabytes_in_each_partition )
{
   WFCLTRACEINIT( TEXT( "CTape::CreatePartition()" ) );

   m_ErrorCode = ::CreateTapePartition( (HANDLE) m_hFile, (DWORD) type_of_partition, number_of_partitions, number_of_megabytes_in_each_partition );

   if ( m_ErrorCode == NO_ERROR )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

BOOL CTape::Erase( const TypeOfErasure type_of_erasure, const BOOL return_immediately )
{
   WFCLTRACEINIT( TEXT( "CTape::Erase()" ) );

   m_ErrorCode = ::EraseTape( (HANDLE) m_hFile, type_of_erasure, return_immediately );

   if ( m_ErrorCode == NO_ERROR )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

BOOL CTape::GetParameters( CTapeGetDriveParameters& parameters )
{
   WFCLTRACEINIT( TEXT( "CTape::GetParameters( CTapeGetDriveParameters& )" ) );

   DWORD size = sizeof( TAPE_GET_DRIVE_PARAMETERS );

   TAPE_GET_DRIVE_PARAMETERS drive_parameters;

   ::ZeroMemory( &drive_parameters, size );

   m_ErrorCode = ::GetTapeParameters( (HANDLE) m_hFile, GET_TAPE_DRIVE_INFORMATION, &size, &drive_parameters );

   if ( m_ErrorCode == NO_ERROR )
   {
      parameters.Copy( &drive_parameters );
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

BOOL CTape::GetParameters( CTapeGetMediaParameters& parameters )
{
   WFCLTRACEINIT( TEXT( "CTape::GetParameters( CTapeGetMediaParameters& )" ) );

   DWORD size = sizeof( TAPE_GET_MEDIA_PARAMETERS );

   TAPE_GET_MEDIA_PARAMETERS media_parameters;

   ::ZeroMemory( &media_parameters, size );

   m_ErrorCode = ::GetTapeParameters( (HANDLE) m_hFile, GET_TAPE_MEDIA_INFORMATION, &size, &media_parameters );

   if ( m_ErrorCode == NO_ERROR )
   {
      parameters.Copy( &media_parameters );
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

BOOL CTape::GetPosition( const Position type_of_position_to_get, DWORD& partition_number, DWORD& position_low, DWORD& position_high )
{
   WFCLTRACEINIT( TEXT( "CTape::GetPosition()" ) );

   m_ErrorCode = ::GetTapePosition( (HANDLE) m_hFile, type_of_position_to_get, &partition_number, &position_low, &position_high );

   if ( m_ErrorCode == NO_ERROR )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

DWORD CTape::GetStatus( void ) const
{
   WFCLTRACEINIT( TEXT( "CTape::GetStatus()" ) );
   return( ::GetTapeStatus( (HANDLE) m_hFile ) );
}

DWORD CTape::GetDriveNumber( void ) const
{
   WFCLTRACEINIT( TEXT( "CTape::GetDriveNumber()" ) );
   return( m_TapeDriveNumberStartingAtZero );
}

BOOL CTape::Mark( const TypeOfMark type_of_mark, const DWORD number_of_marks, const BOOL return_immediately )
{
   WFCLTRACEINIT( TEXT( "CTape::Mark()" ) );

   m_ErrorCode = ::WriteTapemark( (HANDLE) m_hFile, type_of_mark, number_of_marks, return_immediately );

   if ( m_ErrorCode == NO_ERROR )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

BOOL CTape::Load( void )
{
   WFCLTRACEINIT( TEXT( "CTape::Load()" ) );
   return( Prepare( LoadTape ) );
}

BOOL CTape::Lock( void )
{
   WFCLTRACEINIT( TEXT( "CTape::Lock()" ) );
   return( Prepare( LockTape ) );
}

BOOL CTape::Open( const UINT tape_drive_number_starting_at_zero )
{
   WFCLTRACEINIT( TEXT( "CTape::Open()" ) );

   TCHAR tape_drive_name[ MAX_PATH ];

   ::ZeroMemory( tape_drive_name, sizeof( tape_drive_name ) );

   _stprintf( tape_drive_name, TEXT( "\\\\.\\TAPE%u" ), tape_drive_number_starting_at_zero );

   HANDLE file_handle = (HANDLE) INVALID_HANDLE_VALUE;

   file_handle = ::CreateFile( tape_drive_name,
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               0,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL );

   if ( file_handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "Failed" ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }

   m_hFile = (UINT) file_handle;

#if ! defined( WFC_STL )
   m_strFileName = tape_drive_name;
#else
   m_FileName = tape_drive_name;
#endif // WFC_STL

   m_TapeDriveNumberStartingAtZero = tape_drive_number_starting_at_zero;

   GetStatus();
   Lock(); // This will fail, but is doesn't matter...
   GetStatus();

   return( TRUE );
}

BOOL CTape::Prepare( const Operation what_to_do, const BOOL return_immediately )
{
   WFCLTRACEINIT( TEXT( "CTape::Prepare()" ) );

   m_ErrorCode = ::PrepareTape( (HANDLE) m_hFile, what_to_do, return_immediately );

   if ( m_ErrorCode == NO_ERROR )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

BOOL CTape::Read( LPBYTE buffer, const DWORD number_of_bytes_to_read, LPDWORD number_of_bytes_read, BOOL abort, BOOL restore_security_data )
{
   WFCLTRACEINIT( TEXT( "CTape::Read()" ) );

   // We were passed a pointer, don't trust it

   try
   {
      BOOL return_value = ::BackupRead( (HANDLE) m_hFile,
                                        buffer,
                                        number_of_bytes_to_read,
                                        number_of_bytes_read,
                                        abort,
                                        restore_security_data,
                                       &m_BackupReadContextPointer );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CTape::Seek( const DWORD seek_low, const DWORD seek_high, LPDWORD seeked_low, LPDWORD seeked_high )
{
   WFCLTRACEINIT( TEXT( "CTape::Seek()" ) );

   // We were passed a pointer, do not trust it

   try
   {
      BOOL return_value = ::BackupSeek( (HANDLE) m_hFile, seek_low, seek_high, seeked_low, seeked_high, &m_BackupReadContextPointer );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CTape::SetAutomaticallyClose( BOOL auto_close )
{
   WFCLTRACEINIT( TEXT( "CTape::SetAutomaticallyClose()" ) );

   BOOL return_value = m_AutomaticallyClose;

   m_AutomaticallyClose = auto_close;

   return( return_value );
}

BOOL CTape::SetParameters( const CTapeSetMediaParameters& parameters )
{
   WFCLTRACEINIT( TEXT( "CTape::SetParameters( const CTapeSetMediaParameters& )" ) );

   CTapeSetMediaParameters media_parameters( parameters );

   m_ErrorCode = ::SetTapeParameters( (HANDLE) m_hFile, SET_TAPE_MEDIA_INFORMATION, (TAPE_SET_MEDIA_PARAMETERS *) &media_parameters );

   if ( m_ErrorCode == NO_ERROR )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

BOOL CTape::SetParameters( const CTapeSetDriveParameters& parameters )
{
   WFCLTRACEINIT( TEXT( "CTape::SetParameters( const CTapeSetDriveParameters& )" ) );

   CTapeSetDriveParameters drive_parameters( parameters );

   m_ErrorCode = ::SetTapeParameters( (HANDLE) m_hFile, SET_TAPE_DRIVE_INFORMATION, (TAPE_SET_DRIVE_PARAMETERS *) &drive_parameters );

   if ( m_ErrorCode == NO_ERROR )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

BOOL CTape::SetPosition( const PositionMethod how_to_get_there, const DWORD partition_number, const DWORD position_low, const DWORD position_high, const BOOL return_immediately )
{
   WFCLTRACEINIT( TEXT( "CTape::SetPosition()" ) );

   m_ErrorCode = ::SetTapePosition( (HANDLE) m_hFile, how_to_get_there, partition_number, position_low, position_high, return_immediately );

   if ( m_ErrorCode == NO_ERROR )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACE( TEXT( "Failed" ) );
      return( FALSE );
   }
}

BOOL CTape::Unload( void )
{
   WFCLTRACEINIT( TEXT( "CTape::Unload()" ) );
   return( Prepare( UnloadTape ) );
}

BOOL CTape::Unlock( void )
{
   WFCLTRACEINIT( TEXT( "CTape::Unlock()" ) );
   return( Prepare( UnlockTape ) );
}

BOOL CTape::Write( LPBYTE buffer, const DWORD number_of_bytes_to_write, LPDWORD number_of_bytes_written, BOOL abort, BOOL restore_security_data )
{
   WFCLTRACEINIT( TEXT( "CTape::Write()" ) );

   // We were passed a pointer, do not trust it

   try
   {
      BOOL return_value = ::BackupWrite( (HANDLE) m_hFile,
                                         buffer,
                                         number_of_bytes_to_write,
                                         number_of_bytes_written,
                                         abort,
                                         restore_security_data,
                                        &m_BackupWriteContextPointer );
      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CTape</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that encapsulates the Win32 tape backup API.">
</HEAD>

<BODY>

<H1>CTape : <A HREF="DumyFile.htm">CDummyFile</A></H1>
$Revision: 29 $ <BR>
<HR>

<H2>Description</H2>

This class wraps the Tape API of Win32.

<H2>Data Members</H2>

None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the tape drive. Basically calls <B>Prepare</B>( UnloadTape ).

<DT><PRE>BOOL <B>CreatePartition</B>( const TypeOfPartition type_of_partition,
                      const DWORD number_of_partitions,
                      const DWORD number_of_megabytes_in_each_partition )</PRE><DD>
Creates a tape partition. <CODE>type_of_partition</CODE> can be one of the following:

<UL>
<LI>Fixed<LI>Initiator<LI>Select
</UL>

<DT><PRE>BOOL <B>Erase</B>( const TypeOfErasure type_of_erasure, const BOOL return_immediately = FALSE )</PRE><DD>
Erases the tape. <CODE>type_of_erasure</CODE> can be one of the following:
<UL>
<LI>Long<LI>Short
</UL>

<DT><PRE>DWORD <B>GetDriveNumber</B>( void ) const</PRE><DD>
Retrieves the drive number of an opened tape.

<DT><PRE>BOOL <B>GetParameters</B>( CTapeGetDriveParameters&amp; parameters )
BOOL <B>GetParameters</B>( <A HREF="CTapeGetMediaParameters.htm">CTapeGetMediaParameters</A>&amp; parameters )</PRE><DD>
Retrieves either drive parameters or
media parameters.

<DT><PRE>BOOL <B>GetPosition</B>( const Position type_of_position_to_get,
                  DWORD&amp; partition_number,
                  DWORD&amp; position_low,
                  DWORD&amp; position_high )</PRE><DD>
Retrieves the postion of the tape. <CODE>type_of_position_to_get</CODE>
can be one of the following:
<UL>
<LI>Absolute<LI>Logical
</UL>

<DT><PRE>DWORD <B>GetStatus</B>( void ) const</PRE><DD>
Retrieves the status of the tape.

<DT><PRE>BOOL <B>Load</B>( void )</PRE><DD>
Loads a tape.

<DT><PRE>BOOL <B>Lock</B>( void )</PRE><DD>
Locks the tape into place.

<DT><PRE>BOOL <B>Mark</B>( const TypeOfMark type_of_mark, 
           const DWORD      number_of_marks_to_write, 
           const BOOL       return_immediately = FALSE )</PRE><DD>
Makes tape marks. <CODE>type_of_mark</CODE> can be one of the following:
<UL>
<LI>File<LI>LongFile<LI>Set<LI>ShortFile
</UL>

<DT><PRE>BOOL <B>Open</B>( const UINT tape_drive_number_starting_at_zero = 0 )</PRE><DD>
Opens the tape drive number you specify.

<DT><PRE>BOOL <B>Prepare</B>( const Operation what_to_do, const BOOL return_immediately = FALSE )</PRE><DD>
Prepares a tape for reading/writing. <CODE>what_to_do</CODE> can be one of the
following:

<UL>
<LI>FormatTape
<LI>LoadTape
<LI>LockTape
<LI>TensionTape
<LI>UnloadTape
<LI>UnlockTape
</UL>

<DT><PRE>BOOL <B>Read</B>( LPBYTE      buffer, 
           const DWORD number_of_bytes_to_read,
           LPDWORD     number_of_bytes_read,
           BOOL        abort = FALSE,
           BOOL        restore_security_data = TRUE )</PRE><DD>
Reads data from the tape.

<DT><PRE>BOOL <B>Seek</B>( const DWORD seek_low,
           const DWORD seek_high,
           LPDWORD seeked_low,
           LPDWORD seeked_high )</PRE><DD>
Repositions the tape for reading/writing.

<DT><PRE>BOOL <B>SetAutomaticallyClose</B>( BOOL automatically_close )</PRE><DD>
When this is set to TRUE, the tape
drive will be closed when the destructor is called. It returns
the previous setting.

<DT><PRE>BOOL <B>SetParameters</B>( const CTapeSetDriveParameters&amp; parameters )
BOOL <B>SetParameters</B>( cosnt CTapeSetMediaParameters&amp; parameters )</PRE><DD>
Sets either the drive or media parameters.

<DT><PRE>BOOL <B>SetPosition</B>( const PositionMethod how_to_get_there, 
                  const DWORD          partition_number,
                  const DWORD          position_low,
                  const DWORD          position_high,
                  const BOOL           return_immediately = FALSE )</PRE><DD>
Repositions the tape for reading/writing. <CODE>how_to_get_there</CODE>
can be one of the following:

<UL>
<LI>AbsoluteBlock
<LI>LogicalBlock
<LI>Rewind
<LI>EndOfData
<LI>FileMarks
<LI>RelativeBlocks
<LI>SequentialFileMarks
<LI>SequentialSetMarks
<LI>SetMarks
</UL>

<DT><PRE>BOOL <B>Unload</B>( void )</PRE><DD>Ejects the tape.

<DT><PRE>BOOL <B>Unlock</B>( void )</PRE><DD>Unlocks the locking mechanism.

<DT><PRE>BOOL <B>Write</B>( LPBYTE      buffer,
            const DWORD number_of_bytes_to_write,
            LPDWORD     number_of_bytes_written,
            BOOL        abort = FALSE,
            BOOL        restore_security_data = TRUE )</PRE><DD>
Writes data to the tape.

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>

<B>CTape</B> uses the following API's:
<UL>
<LI>BackupRead
<LI>BackupSeek
<LI>BackupWrite
<LI>CreateFile
<LI>CreateTapePartition
<LI>EraseTape
<LI>GetTapeParameters
<LI>GetTapePosition
<LI>GetTapeStatus
<LI>PrepareTape
<LI>SetTapeParameters
<LI>SetTapePosition
<LI>WriteTapemark
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: ctape.cpp $<BR>
$Modtime: 3/17/00 4:37p $
</BODY>

</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CTape=hFile=<m_hFile> name=<m_strFileName.m_pchData,s>
#endif
