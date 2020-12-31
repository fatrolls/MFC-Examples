#if ! defined( RIFF_CLASS_HEADER )

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
** $Workfile: RIFF.hpp $
** $Revision: 4 $
** $Modtime: 9/11/99 5:44a $
*/

#define RIFF_CLASS_HEADER

class CRIFFChunk
{
   protected:

      DWORD m_ID;
      DWORD m_Length;

      CByteArray m_Payload;

   public:

      CRIFFChunk();
      CRIFFChunk( const CPager& source );

      /*
      ** Destructor should be virtual according to MSJ article in Sept 1992
      ** "Do More with Less Code:..."
      */

      virtual ~CRIFFChunk();

      virtual void  Copy( const CRIFFChunk& source );
      virtual void  Empty( void );
      virtual void  GetID( void ) const;
      virtual void  GetID( CString& id_string ) const;
      virtual void  SetID( const BYTE byte_1, const BYTE byte_2, const BYTE byte_3, const BYTE byte_4 );
      virtual void  SetID( const CString& id_string );

      // Operators

      virtual CRIFFChunk& operator = ( const CRIFFChunk& source );
      
#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // RIFF_CLASS_HEADER
