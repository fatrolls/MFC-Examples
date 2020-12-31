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
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: TCTape.cpp $
** $Revision: 3 $
** $Modtime: 2/01/00 6:47p $
*/

void list_features( DWORD low, DWORD high );

void test_CTape( UINT tape_drive_number_to_test )
{
   WFCTRACEINIT( TEXT( "test_CTape()" ) );

   CMicrosoftTape tape;

   if ( tape.Open( tape_drive_number_to_test ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't open TAPE" ), tape_drive_number_to_test );
      ReportError( tape.GetErrorCode() );
      return;
   }
   else
   {
      WFCTRACE( TEXT( "Tape opened" ) );
   }

   CTapeGetDriveParameters drive_parameters;

   if ( tape.GetParameters( drive_parameters ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't get drive parameters TAPE" ), tape_drive_number_to_test );
      ReportError( tape.GetErrorCode() );
      return;
   }

   WFCTRACE( TEXT( "Drive Parameters:\n" ) );
   WFCTRACEVAL( TEXT( "  ECC                   = " ), ( ( drive_parameters.ECC            != FALSE ) ? TEXT( "True" ) : TEXT( "False" ) ) );
   WFCTRACEVAL( TEXT( "  Compression           = " ), ( ( drive_parameters.Compression    != FALSE ) ? TEXT( "True" ) : TEXT( "False" ) ) );
   WFCTRACEVAL( TEXT( "  DataPadding           = " ), ( ( drive_parameters.DataPadding    != FALSE ) ? TEXT( "True" ) : TEXT( "False" ) ) );
   WFCTRACEVAL( TEXT( "  ReportSetmarks        = " ), ( ( drive_parameters.ReportSetmarks != FALSE ) ? TEXT( "True" ) : TEXT( "False" ) ) );
   WFCTRACEVAL( TEXT( "  DefaultBlockSize      = " ), drive_parameters.DefaultBlockSize );
   WFCTRACEVAL( TEXT( "  MaximumBlockSize      = " ), drive_parameters.MaximumBlockSize );
   WFCTRACEVAL( TEXT( "  MinimumBlockSize      = " ), drive_parameters.MinimumBlockSize );
   WFCTRACEVAL( TEXT( "  MaximumPartitionCount = " ), drive_parameters.MaximumPartitionCount );
   WFCTRACEVAL( TEXT( "  FeaturesLow           = " ), drive_parameters.FeaturesLow );
   WFCTRACEVAL( TEXT( "  FeaturesHigh          = " ), drive_parameters.FeaturesHigh );
   WFCTRACEVAL( TEXT( "  EOTWarningZoneSize    = " ), drive_parameters.EOTWarningZoneSize );

   list_features( drive_parameters.FeaturesLow, drive_parameters.FeaturesHigh );

   CTapeGetMediaParameters media_parameters;

   if ( tape.GetParameters( media_parameters ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't get media parameters TAPE" ), tape_drive_number_to_test );
      ReportError( tape.GetErrorCode() );
      return;
   }
   else
   {
      WFCTRACE( TEXT( "Media Parameters:" ) );
      WFCTRACEVAL( TEXT( "  Capacity.Low   = " ), media_parameters.Capacity.LowPart   );
      WFCTRACEVAL( TEXT( "  Capacity.High  = " ), media_parameters.Capacity.HighPart  );
      WFCTRACEVAL( TEXT( "  Remaining.Low  = " ), media_parameters.Remaining.LowPart  );
      WFCTRACEVAL( TEXT( "  Remaining.High = " ), media_parameters.Remaining.HighPart );
      WFCTRACEVAL( TEXT( "  PartitionCount = " ), media_parameters.PartitionCount     );
      WFCTRACEVAL( TEXT( "  WriteProtected = " ), ( ( media_parameters.WriteProtected != FALSE ) ? TEXT( "True" ) : TEXT( "False" ) ) );
   }

#if defined( _DEBUG ) && ! defined( WFC_STL )
   tape.Dump( afxDump );
#endif
}

void list_features( DWORD low, DWORD high )
{
   WFCTRACEINIT( TEXT( "list_features()" ) );

   if ( low & TAPE_DRIVE_COMPRESSION )
   {
      WFCTRACE( TEXT( "Device supports hardware data compression." ) );
   }

   if ( low & TAPE_DRIVE_ECC )
   {
      WFCTRACE( TEXT( "Device supports hardware error correction.\n" ) );
   }

   if ( low & TAPE_DRIVE_ERASE_BOP_ONLY )
   {
      WFCTRACE( TEXT( "Device performs the erase operation from the beginning-of-partition marker only.\n" ) );
   }

   if ( low & TAPE_DRIVE_ERASE_LONG )
   {
      WFCTRACE( TEXT( "Device performs a long erase operation.\n" ) );
   }

   if ( low & TAPE_DRIVE_ERASE_IMMEDIATE )
   {
      WFCTRACE( TEXT( "Device performs an immediate erase operation that is, it returns when the erase operation begins.\n" ) );
   }

   if ( low & TAPE_DRIVE_ERASE_SHORT )
   {
      WFCTRACE( TEXT( "Device performs a short erase operation.\n" ) );
   }

   if ( low & TAPE_DRIVE_FIXED )
   {
      WFCTRACE( TEXT( "Device creates fixed data partitions.\n" ) );
   }

   if ( low & TAPE_DRIVE_FIXED_BLOCK )
   {
      WFCTRACE( TEXT( "Device supports fixed-length block mode.\n" ) );
   }

   if ( low & TAPE_DRIVE_INITIATOR )
   {
      WFCTRACE( TEXT( "Device creates initiator-defined partitions.\n" ) );
   }

   if ( low & TAPE_DRIVE_PADDING )
   {
      WFCTRACE( TEXT( "Device supports data padding.\n" ) );
   }

   if ( low & TAPE_DRIVE_GET_ABSOLUTE_BLK )
   {
      WFCTRACE( TEXT( "Device provides the current device-specific block address.\n" ) );
   }

   if ( low & TAPE_DRIVE_GET_LOGICAL_BLK )
   {
      WFCTRACE( TEXT( "Device provides the current logical block address (and logical tape partition).\n" ) );
   }

   if ( low & TAPE_DRIVE_REPORT_SMKS )
   {
      WFCTRACE( TEXT( "Device supports setmark reporting.\n" ) );
   }

   if ( low & TAPE_DRIVE_SELECT )
   {
      WFCTRACE( TEXT( "Device creates select data partitions.\n" ) );
   }

   if ( low & TAPE_DRIVE_SET_EOT_WZ_SIZE )
   {
      WFCTRACE( TEXT( "Device supports setting the end-of-medium warning size.\n" ) );
   }

   if ( low & TAPE_DRIVE_TAPE_CAPACITY )
   {
      WFCTRACE( TEXT( "Device returns the maximum capacity of the tape.\n" ) );
   }

   if ( low & TAPE_DRIVE_TAPE_REMAINING )
   {
      WFCTRACE( TEXT( "Device returns the remaining capacity of the tape.\n" ) );
   }

   if ( low & TAPE_DRIVE_VARIABLE_BLOCK )
   {
      WFCTRACE( TEXT( "Device supports variable-length block mode.\n" ) );
   }

   if ( low & TAPE_DRIVE_WRITE_PROTECT )
   {
      WFCTRACE( TEXT( "Device returns an error if the tape is write-enabled or write-protected.\n" ) );
   }

   if ( high & TAPE_DRIVE_ABS_BLK_IMMED )
   {
      WFCTRACE( TEXT( "Device moves the tape to a device-specific block address and returns as soon as the move begins.\n" ) );
   }

   if ( high & TAPE_DRIVE_ABSOLUTE_BLK )
   {
      WFCTRACE( TEXT( "Device moves the tape to a device specific block address.\n" ) );
   }

   if ( high & TAPE_DRIVE_END_OF_DATA )
   {
      WFCTRACE( TEXT( "Device moves the tape to the end-of-data marker in a partition.\n" ) );
   }

   if ( high & TAPE_DRIVE_FILEMARKS )
   {
      WFCTRACE( TEXT( "Device moves the tape forward (or backward) a specified number of filemarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_LOAD_UNLOAD )
   {
      WFCTRACE( TEXT( "Device enables and disables the device for further operations.\n" ) );
   }

   if ( high & TAPE_DRIVE_LOAD_UNLD_IMMED )
   {
      WFCTRACE( TEXT( "Device supports immediate load and unload operations.\n" ) );
   }

   if ( high & TAPE_DRIVE_LOCK_UNLOCK )
   {
      WFCTRACE( TEXT( "Device enables and disables the tape ejection mechanism.\n" ) );
   }

   if ( high & TAPE_DRIVE_LOCK_UNLK_IMMED )
   {
      WFCTRACE( TEXT( "Device supports immediate lock and unlock operations.\n" ) );
   }

   if ( high & TAPE_DRIVE_LOG_BLK_IMMED )
   {
      WFCTRACE( TEXT( "Device moves the tape to a logical block address in a partition and returns as soon as the move begins.\n" ) );
   }

   if ( high & TAPE_DRIVE_LOGICAL_BLK )
   {
      WFCTRACE( TEXT( "Device moves the tape to a logical block address in a partition.\n" ) );
   }

   if ( high & TAPE_DRIVE_RELATIVE_BLKS )
   {
      WFCTRACE( TEXT( "Device moves the tape forward (or backward) a specified number of blocks.\n" ) );
   }

   if ( high & TAPE_DRIVE_REVERSE_POSITION )
   {
      WFCTRACE( TEXT( "Device moves the tape backward over blocks, filemarks, or setmarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_REWIND_IMMEDIATE )
   {
      WFCTRACE( TEXT( "Device supports immediate rewind operation.\n" ) );
   }

   if ( high & TAPE_DRIVE_SEQUENTIAL_FMKS )
   {
      WFCTRACE( TEXT( "Device moves the tape forward (or backward) to the first occurrence of a specified number of consecutive filemarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_SEQUENTIAL_SMKS )
   {
      WFCTRACE( TEXT( "Device moves the tape forward (or backward) to the first occurrence of a specified number of consecutive setmarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_SET_BLOCK_SIZE )
   {
      WFCTRACE( TEXT( "Device supports setting the size of a fixed-length logical block or setting the variable-length block mode.\n" ) );
   }

   if ( high & TAPE_DRIVE_SET_COMPRESSION )
   {
      WFCTRACE( TEXT( "Device enables and disables hardware data compression.\n" ) );
   }

   if ( high & TAPE_DRIVE_SET_ECC )
   {
      WFCTRACE( TEXT( "Device enables and disables hardware error correction.\n" ) );
   }

   if ( high & TAPE_DRIVE_SET_PADDING )
   {
      WFCTRACE( TEXT( "Device enables and disables data padding.\n" ) );
   }

   if ( high & TAPE_DRIVE_SET_REPORT_SMKS )
   {
      WFCTRACE( TEXT( "Device enables and disables the reporting of setmarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_SETMARKS )
   {
      WFCTRACE( TEXT( "Device moves the tape forward (or reverse) a specified number of setmarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_SPACE_IMMEDIATE )
   {
      WFCTRACE( TEXT( "Device supports immediate spacing.\n" ) );
   }

   if ( high & TAPE_DRIVE_TENSION )
   {
      WFCTRACE( TEXT( "Device supports tape tensioning.\n" ) );
   }

   if ( high & TAPE_DRIVE_TENSION_IMMED )
   {
      WFCTRACE( TEXT( "Device supports immediate tape tensioning.\n" ) );
   }

   if ( high & TAPE_DRIVE_WRITE_FILEMARKS )
   {
      WFCTRACE( TEXT( "Device writes filemarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_WRITE_LONG_FMKS )
   {
      WFCTRACE( TEXT( "Device writes long filemarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_WRITE_MARK_IMMED )
   {
      WFCTRACE( TEXT( "Device supports immediate writing of short and long filemarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_WRITE_SETMARKS )
   {
      WFCTRACE( TEXT( "Device writes setmarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_WRITE_SHORT_FMKS )
   {
      WFCTRACE( TEXT( "Device writes short filemarks.\n" ) );
   }

   if ( high & TAPE_DRIVE_FORMAT )
   {
      WFCTRACE( TEXT( "TAPE_DRIVE_FORMAT\n" ) );
   }

   if ( high & TAPE_DRIVE_FORMAT_IMMEDIATE )
   {
      WFCTRACE( TEXT( "TAPE_DRIVE_FORMAT_IMMEDIATE\n" ) );
   }
}
