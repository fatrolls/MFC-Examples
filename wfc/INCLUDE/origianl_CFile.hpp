#if ! defined( FILE_CLASS_HEADER_FILE )

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
** $Workfile: wfc.h $
** $Revision: 55 $
** $Modtime: 9/05/99 2:07p $
*/

#define FILE_CLASS_HEADER_FILE

#if defined( WFC_STL )

class CFile
{
   private:

      // Don't allow canonical behavior (i.e. don't
      // allow passing of this class by value)

      CFile( const CFile& ) {};
      CFile& operator=( const CFile& ) { return( *this ); };

   protected:

      FILE *  m_File_p;
      BOOL    m_CloseOnDelete;
      CString m_strFileName;

   public:

      // Flag values
      enum OpenFlags
      {
         modeRead =       0x0000,
         modeWrite =      0x0001,
         modeReadWrite =  0x0002,
         modeCreate =     0x1000,
         modeNoTruncate = 0x2000
      };

      enum Attribute
      {
         normal =    0x00,
         readOnly =  0x01,
         hidden =    0x02,
         system =    0x04,
         volume =    0x08,
         directory = 0x10,
         archive =   0x20
      };

      enum SeekPosition
      {
         begin   = 0x0,
         current = 0x1,
         end     = 0x2
      };

      enum { hFileNull = NULL };

      // Constructors

      CFile();
      CFile( const char * file_name, UINT open_flags );
      virtual ~CFile();

      virtual void    Close( void );
      virtual void    Flush( void );
      virtual CString GetFileName( void ) const;
      virtual DWORD   GetLength( void ) const;
      virtual DWORD   GetPosition( void ) const;
      virtual BOOL    Open( const char * FileName, UINT OpenFlags );
      virtual UINT    Read( void * Buffer, UINT Count );
      virtual long    Seek( long Offset, UINT From );
      virtual DWORD   SeekToEnd( void );
      virtual void    SeekToBegin( void );
      virtual void    Write( const void * Buffer, UINT Count );

      operator FILE *() const;
};

#endif // WFC_STL

#endif // FILE_CLASS_HEADER_FILE

