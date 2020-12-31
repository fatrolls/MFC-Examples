#if ! defined( TAPE_CLASS_HEADER )

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
** $Workfile: ctape.hpp $
** $Revision: 12 $
** $Modtime: 1/04/00 4:58a $
*/

#define TAPE_CLASS_HEADER

class CTapeGetDriveParameters : public _TAPE_GET_DRIVE_PARAMETERS
{
   public:

      CTapeGetDriveParameters();
      CTapeGetDriveParameters( const CTapeGetDriveParameters& source );
      CTapeGetDriveParameters( const TAPE_GET_DRIVE_PARAMETERS * source );

      virtual ~CTapeGetDriveParameters();

      virtual void Copy( const CTapeGetDriveParameters& source );
      virtual void Copy( const TAPE_GET_DRIVE_PARAMETERS * source );
      virtual void Empty( void );

      virtual CTapeGetDriveParameters& operator=( const CTapeGetDriveParameters&   source );
      virtual CTapeGetDriveParameters& operator=( const TAPE_GET_DRIVE_PARAMETERS& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CTapeGetMediaParameters : public _TAPE_GET_MEDIA_PARAMETERS
{
   public:

      CTapeGetMediaParameters();
      CTapeGetMediaParameters( const CTapeGetMediaParameters& source );
      CTapeGetMediaParameters( const TAPE_GET_MEDIA_PARAMETERS * source );

      virtual ~CTapeGetMediaParameters();

      virtual void Copy( const CTapeGetMediaParameters& source );
      virtual void Copy( const TAPE_GET_MEDIA_PARAMETERS * source );
      virtual void Empty( void );

      virtual CTapeGetMediaParameters& operator = ( const CTapeGetMediaParameters&   source );
      virtual CTapeGetMediaParameters& operator = ( const TAPE_GET_MEDIA_PARAMETERS& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CTapeSetDriveParameters : public _TAPE_SET_DRIVE_PARAMETERS
{
   public:

      CTapeSetDriveParameters();
      CTapeSetDriveParameters( const CTapeSetDriveParameters& source );
      CTapeSetDriveParameters( const TAPE_SET_DRIVE_PARAMETERS * source );

      virtual ~CTapeSetDriveParameters();

      virtual void Copy( const CTapeSetDriveParameters& source );
      virtual void Copy( const TAPE_SET_DRIVE_PARAMETERS * source );
      virtual void Empty( void );

      virtual CTapeSetDriveParameters& operator=( const CTapeSetDriveParameters&   source );
      virtual CTapeSetDriveParameters& operator=( const TAPE_SET_DRIVE_PARAMETERS& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CTapeSetMediaParameters : public _TAPE_SET_MEDIA_PARAMETERS
{
   public:

      CTapeSetMediaParameters();
      CTapeSetMediaParameters( const CTapeSetMediaParameters& source );
      CTapeSetMediaParameters( const TAPE_SET_MEDIA_PARAMETERS * source );

      virtual ~CTapeSetMediaParameters();

      virtual void Copy( const CTapeSetMediaParameters& source );
      virtual void Copy( const TAPE_SET_MEDIA_PARAMETERS * source );
      virtual void Empty( void );

      virtual CTapeSetMediaParameters& operator=( const CTapeSetMediaParameters&   source );
      virtual CTapeSetMediaParameters& operator=( const TAPE_SET_MEDIA_PARAMETERS& source );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif
};

class CTape : public CDummyFile
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CTape( const CTape& ) {};
      CTape& operator=( const CTape& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      LPVOID m_BackupReadContextPointer;
      LPVOID m_BackupWriteContextPointer;

      BOOL m_AutomaticallyClose;

      DWORD m_TapeDriveNumberStartingAtZero;
      
   public:

      CTape();

      virtual ~CTape();

      enum TypeOfPartition
      {
         Fixed     = TAPE_FIXED_PARTITIONS,
         Initiator = TAPE_INITIATOR_PARTITIONS,
         Select    = TAPE_SELECT_PARTITIONS 
      };

      enum TypeOfErasure
      {
         Long  = TAPE_ERASE_LONG,
         Short = TAPE_ERASE_SHORT
      };

      enum TypeOfMark
      {
         File      = TAPE_FILEMARKS,
         LongFile  = TAPE_LONG_FILEMARKS,
         Set       = TAPE_SETMARKS,
         ShortFile = TAPE_SHORT_FILEMARKS
      };

      enum Position
      {
         Absolute = TAPE_ABSOLUTE_POSITION,
         Logical  = TAPE_LOGICAL_POSITION
      };

      enum PositionMethod
      {
         AbsoluteBlock       = TAPE_ABSOLUTE_BLOCK,
         LogicalBlock        = TAPE_LOGICAL_BLOCK,
         Rewind              = TAPE_REWIND,
         EndOfData           = TAPE_SPACE_END_OF_DATA,
         FileMarks           = TAPE_SPACE_FILEMARKS,
         RelativeBlocks      = TAPE_SPACE_RELATIVE_BLOCKS,
         SequentialFileMarks = TAPE_SPACE_SEQUENTIAL_FMKS,
         SequentialSetMarks  = TAPE_SPACE_SEQUENTIAL_SMKS,
         SetMarks            = TAPE_SPACE_SETMARKS
      };

      enum Operation
      {
         FormatTape  = TAPE_FORMAT,
         LoadTape    = TAPE_LOAD,
         LockTape    = TAPE_LOCK,
         TensionTape = TAPE_TENSION,
         UnloadTape  = TAPE_UNLOAD,
         UnlockTape  = TAPE_UNLOCK
      };

      /*
      ** The Win32 API
      */

      virtual BOOL CreatePartition( const TypeOfPartition type_of_partition,
                                    const DWORD number_of_partitions,
                                    const DWORD number_of_megabytes_in_each_partition ); // CreateTapePartition

      virtual BOOL Erase( const TypeOfErasure type_of_erasure, const BOOL return_immediately = FALSE ); // EraseTape

      virtual BOOL GetParameters( CTapeGetDriveParameters& parameters ); // GetTapeParameters
      virtual BOOL GetParameters( CTapeGetMediaParameters& parameters );

      virtual BOOL GetPosition( const Position type_of_position_to_get,
                                DWORD& partition_number,
                                DWORD& position_low,
                                DWORD& position_high ); // GetTapePosition

      virtual DWORD GetStatus( void ) const; // GetTapeStatus
      virtual DWORD GetDriveNumber( void ) const;

      virtual BOOL Prepare( const Operation what_to_do, const BOOL return_immediately = FALSE ); // PrepareTape

      virtual BOOL SetAutomaticallyClose( BOOL auto_close ); // returns previous setting
      virtual BOOL SetParameters( const CTapeSetDriveParameters& parameters ); // SetTapeParameters
      virtual BOOL SetParameters( const CTapeSetMediaParameters& parameters );

      virtual BOOL SetPosition( const PositionMethod how_to_get_there, 
                                const DWORD          partition_number,
                                const DWORD          position_low,
                                const DWORD          position_high,
                                const BOOL           return_immediately = FALSE ); // SetTapePosition

      virtual BOOL Mark( const TypeOfMark type_of_mark, 
                         const DWORD      number_of_marks_to_write, 
                         const BOOL       return_immediately = FALSE ); // WriteTapemark

      virtual BOOL Read( LPBYTE      buffer, 
                         const DWORD number_of_bytes_to_read,
                         LPDWORD     number_of_bytes_read,
                         BOOL        abort = FALSE,
                         BOOL        restore_security_data = TRUE ); // BackupRead

      virtual BOOL Seek( const DWORD seek_low,
                         const DWORD seek_high,
                         LPDWORD seeked_low,
                         LPDWORD seeked_high ); // BackupSeek

      virtual BOOL Write( LPBYTE      buffer,
                          const DWORD number_of_bytes_to_write,
                          LPDWORD     number_of_bytes_written,
                          BOOL        abort = FALSE,
                          BOOL        restore_security_data = TRUE ); // BackupWrite

      /*
      ** API's to make life easier
      */

      virtual BOOL Open( const UINT tape_drive_number_starting_at_zero = 0 );
      virtual BOOL Load( void );
      virtual BOOL Lock( void );
      virtual BOOL Unload( void );
      virtual BOOL Unlock( void );
      virtual void Close( void ); // Calls Prepare( TAPE_UNLOAD )
};

#endif // TAPE_CLASS_HEADER
