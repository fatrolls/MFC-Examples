#if ! defined( VOLUME_CLASS_HEADER )

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
** $Workfile: CVolume.hpp $
** $Revision: 2 $
** $Modtime: 9/11/99 6:01a $
*/

#define VOLUME_CLASS_HEADER

class CVolume
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CVolume( const CVolume& ) {};
      CVolume& operator=( const CVolume& ) { return( *this ); };

   protected:

      HANDLE m_Handle;

      UINT m_DriveType;

      CString m_Name;

      TCHAR m_DriveLetter;

   public:

      CVolume();
      virtual ~CVolume();

      virtual BOOL   AutomaticallyEject( void );
      virtual BOOL   Close( void );
      virtual BOOL   Dismount( void );
      virtual BOOL   Eject( void );
      virtual HANDLE GetHandle( void ) const;
      virtual BOOL   GetType( UINT& drive_type );
      virtual BOOL   Load( void );
      virtual BOOL   Lock( void );
      virtual BOOL   Open( TCHAR drive_letter );
      virtual BOOL   PreventRemoval( BOOL prevent_removal = TRUE );
      virtual BOOL   Unlock( void );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // VOLUME_CLASS_HEADER
