#if ! defined ( DATA_PARSER_CLASS_HEADER )

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
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: CDataLocation.hpp $
** $Revision: 3 $
** $Modtime: 3/08/98 12:03p $
*/

#define DATA_PARSER_CLASS_HEADER

class CDataParser
{
   protected:

      BOOL         m_AutomaticallyDelete;
      CByteArray * m_Data;

   private:

      // Don't allow this kind of behavior

      CDataParser( const CDataParser& ){};
      CDataParser& operator=( const CDataParser& ) { return( *this ); };

   public:

      CDataParser();
      virtual ~CDataParser();

      virtual BOOL Initialize( DWORD& parse_point, CByteArray * data, BOOL autodelete = FALSE );
      virtual void Empty( void );
};

#endif // DATA_PARSER_CLASS_HEADER
