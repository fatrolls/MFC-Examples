#if ! defined( MICROSOFT_TAPE_CLASS_HEADER )

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
** $Workfile: CMicrosoftTape.hpp $
** $Revision: 9 $
** $Modtime: 1/04/00 4:51a $
*/

#define MICROSOFT_TAPE_CLASS_HEADER

class CMicrosoftTape : public CTape
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CMicrosoftTape( const CMicrosoftTape& ) {};
      CMicrosoftTape& operator=( const CMicrosoftTape& ) { return( *this ); };

   private:

      void m_Initialize( void );

   protected:

      CMTFTape m_TapeHeader;

   public:

      CMicrosoftTape();

      virtual ~CMicrosoftTape();

      virtual void Empty( void );
      virtual BOOL EnumerateSets( void );
      virtual BOOL Open( const UINT tape_drive_number_starting_at_zero );
      virtual BOOL ReadHeader( void );

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      void Dump( CDumpContext& dump_context ) const;

#endif
};

#endif // TAPE_CLASS_HEADER
